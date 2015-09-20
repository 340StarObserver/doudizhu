#include "loginbusiness.h"
#include <QDataStream>
#include "datatype.h"
#include "gameserver.h"
#include "usermodel.h"
#include "datapackage.h"

//构造登陆业务
/*
 * 在此业务中临时保存 新连接的那个套接字
 * 数据报文大小清零
 * 关联套接字的信号
*/
LoginBusiness::LoginBusiness(QTcpSocket *socket, QObject *parent):QObject(parent)
{
    _socket=socket;
    _dataSize=0;
    connect(_socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    connect(_socket,SIGNAL(disconnected()),_socket,SLOT(deleteLater()));
}

//读取数据槽
/*
 * 先读取报文的类型
 * 若 报文 不是登陆请求:
 * {
 *    直接驳回,断开连接
 *    向服务端的ui层报告此信息
 * }
 * 反之:
 * {
 *    读取用户名,密码
 *    向ui层报告 谁谁谁尝试登陆
 *    处理登陆数据
 * }
*/
void LoginBusiness::onReadyRead()
{
    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_5_5);
    if(_dataSize==0){
        if(_socket->bytesAvailable()<sizeof(quint16))
            return;
        in>>_dataSize;
    }
    if(_socket->bytesAvailable()<_dataSize)
        return;
    int dataType;
    in>>dataType;
    if(dataType!=DataType::Login){
        emit report("receive invalid data for login,so ignore it");
        _socket->disconnectFromHost();
        return;
    }
    in>>_username>>_password;
    emit report(QString("user: ").append(_username).append(" try login"));
    dealData();
}

//处理接受到的登陆信息数据
//1. 校验登陆数据的正确性
//2. 若信息错误or已经人满:
//   {
//      发送登陆失败的结果报文
//      断开连接
//      将xx登陆失败的消息报告给服务端的ui层
//   }
//   反之:
//   {
//      发送登陆成功的结果报文;
//      取消_socket原来的在本类中信号关联;
//      调用单例GameServer的add方法;
//      悬空_socket;
//   }
void LoginBusiness::dealData()
{
    int curNum=GameServer::getInstance()->getGameWork()->getOnlineNum();
    if(curNum>=3 || !UserModel::identify(_username,_password,&_totaltimes,&_wintimes,&_head))
    {
        _socket->write(DataPackage::loginResult(false,-1,-1));
        _socket->disconnectFromHost();
        emit report(QString(_username).append(" login failed because data is wrong or game server is full of three people"));
        return;
    }
    int gameID=GameServer::getInstance()->emptyIndex();
    _socket->write(DataPackage::loginResult(true,gameID,_head));
    disconnect(_socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    disconnect(_socket,SIGNAL(disconnected()),_socket,SLOT(deleteLater()));
    GameServer::getInstance()->add(_socket,_username,_password,_totaltimes,_wintimes,_head);
    _socket=NULL;
}
