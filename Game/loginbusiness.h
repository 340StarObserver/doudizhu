#ifndef LOGINBUSINESS
#define LOGINBUSINESS

#include <QTcpSocket>
#include <QObject>
#include <QString>

//负责登录业务(ok)
class LoginBusiness : public QObject
{
private:
    Q_OBJECT
    QTcpSocket * _socket; //传输套接字
    quint16 _dataSize;    //读取的字节数
    QString _username;    //用户名
    QString _password;    //密码
    uint _totaltimes;     //游戏总局数
    uint _wintimes;       //获胜局数
    int _head;            //头像代号
signals:
    void report(const QString& str);//向GameServer汇报
private slots:
    void onReadyRead();   //读取数据槽
private:
    void dealData();      //处理接受到的数据
public:
    explicit LoginBusiness(QTcpSocket * socket,QObject * parent);
};

#endif
