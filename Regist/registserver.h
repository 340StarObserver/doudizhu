#ifndef REGISTSERVER
#define REGISTSERVER

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QAbstractSocket>

//server for regist
class RegistServer : public QTcpServer
{
    Q_OBJECT
private:
    bool _isfree;                                 //whether the server is free
    int _delayTimes;                              //allowed times of delay
    quint16 _blocksize;                           //the size of data from client
    QTcpSocket * _socket;                         //transilation socket
    void delay(int msec);                         //unblock delay
private slots:
    void dealNewConn();                           //slot for newConnection signal
    void onReadyRead();                           //slot for readyread signal
    void onError(QAbstractSocket::SocketError se);//slot for socket error signal
signals:
    void report(const QString& str);              //signal for reporting
public:
    explicit RegistServer(QObject * parent=NULL); //constructor
    void start();                                 //start the server
    void stop();                                  //stop the server
};

#endif

