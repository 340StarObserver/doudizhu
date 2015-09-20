#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QPaintEvent>
#include <QEvent>
#include <QString>

namespace Ui {
class Login;
}

//登陆首页(ok)
class Login : public QDialog
{
    Q_OBJECT
public:
    explicit Login(QWidget *parent = 0);
    ~Login();
protected:
    void paintEvent(QPaintEvent * event);           //绘制事件
    bool eventFilter(QObject * obj, QEvent * event);//事件过滤器
    //以下两个方法用以实现窗体的拖动
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    void originWindow();                   //配置窗体属性
    void originLoginLabel();               //配置登陆标签属性
    void originAccountLabel();             //配置账号标签属性
    void originPwdLabel();                 //配置密码标签属性
    void originAccountInput();             //配置账号输入框属性
    void originPwdInput();                 //配置密码输入框属性
    void originButtons();                  //配置登陆,注册按钮属性
    void originSocket();                   //配置登陆用的套接字
    bool checkDataValid()const;            //校验输入数据合法性
public slots:
    //接收 网络层发出的登陆结果信号 的槽
    void receive_LoginResult(bool res,int playerID,int head);
private:
    Ui::Login *ui;
    //ui成员:
    QLabel *loginLabel;            //欢迎信息
    QLabel *accountLabel;          //账号标签
    QLabel *passwordLabel;         //密码标签
    QLineEdit *accountLineEdit;    //账号输入框
    QLineEdit *passwordLineEdit;   //密码输入框
    QPushButton *loginBtn;         //登陆按钮
    QPushButton *registerBtn;      //注册按钮
    //非ui成员:
    bool _canLogin;                //登陆按钮是否可用
    bool _canRegist;               //注册按钮是否可用
    QString _user;                 //通过格式校验的 用户名
    QString _pwd;                  //通过格式校验的 密码
    QPoint windowPos;              //窗体位置
    QPoint mousePos;               //鼠标位置
    QPoint dPos;                   //鼠标和窗体位置的差值
};

#endif
