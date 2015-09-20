#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QByteArray>
#include <QString>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QEvent>
#include <QTextBrowser>
#include <QTextEdit>
#include <vector>
using std::vector;
#include <QUdpSocket>
#include <QPaintEvent>

namespace Ui {
class ChatWindow;
}

//聊天侧边栏(ok)
class ChatWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ChatWindow(QWidget *parent = 0);
    ~ChatWindow();
private:
    //新用户加入的报文装包
    QByteArray pack_Come(const QString & user,const QString & ip)const;
    //响应用户加入的报文装包
    QByteArray pack_ResponseCome(const QString & user,const QString & ip)const;
    //用户离开的报文装包
    QByteArray pack_Leave(const QString & user,const QString & ip)const;
    //聊天内容的报文装包
    QByteArray pack_Talk(const QString & user,const QString & content)const;
    //获得本机ip
    QString getIPv4()const;
    //配置窗体
    void originWindow();
    //配置笑脸标签
    void originZb();
    //配置临时用户名输入框的提示标签
    void originUserLabel();
    //配置临时昵称输入框
    void originInputUser();
    //配置进入聊天室按钮
    void originEnterChat();
    //配置用户列表的显示
    void originRoom();
    //配置所有用户的聊天内容显示
    void originAllContents();
    //配置聊天输入框
    void originInputContent();
    //配置提交聊天内容按钮
    void originSubmit();
    //配置udp套接字
    void originSocket();
    //事件过滤器
    bool eventFilter(QObject * obj, QEvent * event);
    //用户列表ui新增一个聊天者
    void addOne(const QString& user,const QString& ip);
    //用户列表ui删去一个聊天者
    void removeOne(const QString& user,const QString& ip);
    //聊天内容显示框的更新
    void updateAllContents(const QString& user,const QString& str);
    //昵称是否合法
    bool validUsername(const QString& user)const;
    void paintEvent(QPaintEvent * event);
private slots:
    void autoScroll();//聊天内容显示框的自动滚动槽
    void onReadyRead();//收到udp数据的槽
private:
    Ui::ChatWindow *ui;
    //未进入聊天室时的ui部件:
    QLabel * _zb;               //微笑标签
    QLabel * _userLabel;        //临时昵称输入的提示标签
    QLineEdit * _inputUser;     //临时昵称输入框
    QPushButton * _enterChat;   //进入聊天室按钮
    //进入聊天室后的ui部件:
    QLabel * _label1;           //用户列表的用户名字段标签
    QLabel * _label2;           //用户列表的IP字段标签
    QTextBrowser * _room;       //用户列表显示文本快
    QTextBrowser * _allContents;//所有用户的聊天内容文本快
    QTextEdit * _inputContent;  //聊天输入框
    QPushButton * _submit;      //提交聊天内容按钮
    //常量:
    static const int _TypeCome=0;        //报文为新用户加入
    static const int _TypeResponseCome=1;//报文为响应新用户的加入
    static const int _TypeLeave=2;       //报文为用户离开
    static const int _TypeTalk=3;        //报文为用户聊天
    //非ui成员:
    QString _username;        //聊天时的用户名
    vector<QString> _userList;//聊天室内的用户名列表
    vector<QString> _ipList;  //聊天室内的用户ip列表
    QUdpSocket * _sender;     //发送者套接字
    QUdpSocket * _receiver;   //接收者套接字
    quint16 _port;            //端口
};

#endif
