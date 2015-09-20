#include "registserver.h"
#include <QHostAddress>
#include <QTime>
#include <QCoreApplication>
#include <QEventLoop>
#include <QDataStream>
#include "usermodel.h"
#include <QByteArray>
#include <QIODevice>

// create the server
RegistServer::RegistServer(QObject *parent):QTcpServer(parent)
{
    _isfree = true;
    _delayTimes = 0;
    _socket = NULL;
}

// start the regist server
void RegistServer::start()
{
    if(!isListening()){
        if(listen(QHostAddress::Any,3910))
        {
            _isfree = true;
            connect(this,SIGNAL(newConnection()),this,SLOT(dealNewConn()));
            emit report("start listen port(3910) success");
        }
        else
            emit report("start listen port(3910) failed!");
    }
}

// stop the regist server
void RegistServer::stop()
{
    if(isListening()){
        disconnect(this,SIGNAL(newConnection()),this,SLOT(dealNewConn()));
        close();
        _isfree = true;
        emit report("stop listen port(3910)");
    }
}

// deal a new connection
void RegistServer::dealNewConn()
{
    emit report("receive a new request");
    while(!_isfree && _delayTimes<10)
    {
        emit report("wait until the server is free");
        _delayTimes++;
        delay(100);
    }
    if(_delayTimes >= 10){
        _delayTimes = 0;
        return;
    }
    _delayTimes = 0;
    _blocksize = 0;
    _isfree = false;
    _socket = nextPendingConnection();
    connect(_socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(_socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onError(QAbstractSocket::SocketError)));
    connect(_socket,SIGNAL(disconnected()),_socket,SLOT(deleteLater()));
}

// unblock delay
void RegistServer::delay(int msec)
{
    QTime t=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<t)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

// slot for socket error
void RegistServer::onError(QAbstractSocket::SocketError se)
{
    emit report("socket error!");
    _isfree = true;
}

// slot for readyread signal
/*
 * 读取用户名,密码,用户选用的头像
 * 将注册结果报文返回给客户端
 * 不管注册成败如何,都断开连接,因为注册不需要长连接
 * 因为断开了连接,所以不必递归接收消息
*/
void RegistServer::onReadyRead()
{
    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_5_5);
    if(_blocksize == 0){
        if(_socket->bytesAvailable()<sizeof(quint16))
            return;
        in>>_blocksize;
    }
    if(_socket->bytesAvailable()<_blocksize)
        return;
    QString user,pwd;
    int head;
    in>>user>>pwd;
    in>>head;
    bool res = UserModel::regist(user,pwd,head);
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<res;
    _socket->write(bytes);
    _socket->disconnectFromHost();
    emit report(QString("regist ").append(res?"success~":"failed!"));
    _isfree = true;
}
