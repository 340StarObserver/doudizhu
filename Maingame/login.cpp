#include "login.h"
#include "ui_login.h"
#include <QPainter>
#include <QPixmap>
#include <QRegExp>
#include <QMessageBox>
#include "register.h"
#include "clientsocket.h"
#include <QDataStream>
#include "maingame.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    originWindow();        //配置窗体属性
    originLoginLabel();    //配置登陆标签属性
    originAccountLabel();  //配置账号标签属性
    originPwdLabel();      //配置密码标签属性
    originAccountInput();  //配置账号输入框属性
    originPwdInput();      //配置密码输入框属性
    originButtons();       //配置登陆,注册按钮属性
    originSocket();        //配置登陆用的套接字
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

//配置窗体属性
void Login::originWindow()
{
    setFixedSize(800,600);
}
//窗体背景绘制
void Login::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/image/res/bg.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}
//配置登陆标签的属性
void Login::originLoginLabel()
{
    loginLabel=new QLabel(this);
    loginLabel->setGeometry(30,140,600,80);
    QFont font;
    font.setFamily(QStringLiteral("URW Gothic L"));
    font.setPointSize(40);
    font.setBold(true);
    loginLabel->setFont(font);
    loginLabel->setAlignment(Qt::AlignCenter);
    loginLabel->setStyleSheet("color:#333333");
    loginLabel->setText(">斗地主<");
}
//配置账号标签属性
void Login::originAccountLabel()
{
    accountLabel=new QLabel(this);
    accountLabel->setGeometry(80,250,150,50);
    accountLabel->setText("账号 :");
    QFont font;
    font.setFamily(QStringLiteral("URW Gothic L"));
    font.setPointSize(25);
    font.setBold(true);
    accountLabel->setFont(font);
    accountLabel->setStyleSheet("color:#333333");
}
//配置密码标签属性
void Login::originPwdLabel()
{
    passwordLabel=new QLabel(this);
    passwordLabel->setGeometry(80,340,150,50);
    passwordLabel->setText("密码 :");
    QFont font;
    font.setFamily(QStringLiteral("URW Gothic L"));
    font.setPointSize(25);
    font.setBold(true);
    passwordLabel->setFont(font);
    passwordLabel->setStyleSheet("color:#333333");
}
//配置账号输入框属性
void Login::originAccountInput()
{
    accountLineEdit=new QLineEdit(this);
    accountLineEdit->setGeometry(180,252,420,50);
    QFont font;
    font.setFamily(QStringLiteral("URW Gothic L"));
    font.setPointSize(25);
    font.setBold(true);
    accountLineEdit->setFont(font);
    accountLineEdit->setPlaceholderText("input your username");
    accountLineEdit->setMaxLength(8);
    accountLineEdit->setStyleSheet("color:#003333");
}
//配置密码输入框属性
void Login::originPwdInput()
{
    passwordLineEdit=new QLineEdit(this);
    passwordLineEdit->setGeometry(180,342,420,50);
    QFont font;
    font.setFamily(QStringLiteral("URW Gothic L"));
    font.setPointSize(25);
    font.setBold(true);
    passwordLineEdit->setFont(font);
    passwordLineEdit->setPlaceholderText("input your password");
    passwordLineEdit->setMaxLength(9);
    passwordLineEdit->setStyleSheet("color:#003333");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
}
//配置登陆,注册按钮属性
void Login::originButtons()
{
    //登陆按钮:
    _canLogin=true;
    loginBtn=new QPushButton(this);
    loginBtn->setGeometry(200,420,100,40);
    loginBtn->setStyleSheet("background-color:#2b2b2b;color:#ffffff");
    loginBtn->setText("登录");
    QFont font;
    font.setPointSize(20);
    loginBtn->setFont(font);
    loginBtn->setCursor(Qt::PointingHandCursor);
    loginBtn->installEventFilter(this);
    //注册按钮:
    _canRegist=true;
    registerBtn=new QPushButton(this);
    registerBtn->setGeometry(400,420,100,40);
    font.setPointSize(20);
    registerBtn->setFont(font);
    registerBtn->setText("注册");
    registerBtn->setStyleSheet("background-color:#2b2b2b;color:#ffffff");
    registerBtn->setCursor(Qt::PointingHandCursor);
    registerBtn->installEventFilter(this);
}

//校验输入数据合法性(利用正则)
//要求用户名是14级的学号,密码是14级的一卡通
bool Login::checkDataValid()const
{
    QString user=accountLineEdit->text();
    QString pwd=passwordLineEdit->text();
    QRegExp rx1("^\\d{2}[a-z0-9A-Z]{1}14\\d{3}");
    QRegExp rx2("21314\\d{4}");
    return rx1.indexIn(user)==0 && rx2.indexIn(pwd)==0;
}

//配置登陆用的套接字
//当网络层 接收到登陆结果报文 会将信号发送 然后在这里接收
void Login::originSocket()
{
    ClientSocket::getInstance()->setSignals();
    connect(ClientSocket::getInstance(),SIGNAL(report_LoginResult(bool,int,int)),this,SLOT(receive_LoginResult(bool,int,int)));
}

//接收 网络层发出的登陆结果信号 的槽
/*
 *若登陆成功:
 *{
 *  取消 登陆结果信号的关联
 *  {
 *    这里如果不取消关联,那么第一局游戏打完,继续第二轮游戏的时候直接发送登陆请求,
 *    会使得出现两个游戏界面
 *    因为这里close并不是真正删除这个界面,它只是看不见了仍然在等待接收信号
 *  }
 *  关闭此界面
 *  创建游戏界面并打开
 *}
 *反之:{ 弹出提示框, 恢复登陆按钮为可用 }
*/
void Login::receive_LoginResult(bool res, int playerID, int head)
{
    if(res)
    {
        disconnect(ClientSocket::getInstance(),SIGNAL(report_LoginResult(bool,int,int)),this,SLOT(receive_LoginResult(bool,int,int)));
        close();
        Maingame * mainPage=new Maingame(playerID,head,_user,_pwd,NULL);
        mainPage->setWindowTitle("游戏");
        mainPage->show();
    }
    else
    {
        QMessageBox::warning(this,"warning","login failed",QMessageBox::Ok);
        _canLogin=true;
    }
}

//事件过滤器
/*
 * 若是登陆按钮被按下:
 * {
 *   若数据格式合法:
 *   {
 *     若登陆按钮可用: 则设置其为不可用,发送登陆请求
 *   }
 *   反之,弹出提示警告对话框
 * }
 * 若是注册按钮被按下:
 * {
 *   若按钮可用:
 *   {
 *      设置其为不可用
 *      取消登陆结果信号的关联
 *      {
 *         这里如果不取消关联,那么之后从注册界面返回登陆界面 再登陆
 *         会使得出现两个游戏界面
 *         因为这里close并不是真正删除这个界面,它只是看不见了仍然在等待接收信号
 *      }
 *      关闭界面
 *      创建并打开注册界面
 *   }
 * }
*/
bool Login::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==loginBtn && event->type()==QEvent::MouseButtonPress)
    {
        if(checkDataValid())
        {
            if(_canLogin)
            {
                _canLogin=false;
                _user=accountLineEdit->text();
                _pwd=passwordLineEdit->text();
                ClientSocket::getInstance()->sendLogin(_user,_pwd);
            }
        }
        else
        {
            QString warn="user is your studentID\npwd is your cardID";
            QMessageBox::warning(this,"warning",warn,QMessageBox::Ok);
        }
        return true;
    }
    if(obj==registerBtn && event->type()==QEvent::MouseButtonPress && _canRegist)
    {
        _canRegist=false;
        disconnect(ClientSocket::getInstance(),SIGNAL(report_LoginResult(bool,int,int)),this,SLOT(receive_LoginResult(bool,int,int)));
        close();
        Register * newPage=new Register;
        newPage->setWindowTitle("注册");
        newPage->show();
        return true;
    }
    return QDialog::eventFilter(obj,event);
}
//以下两个方法用来实现界面的移动
void Login::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();           // 获得部件当前位置
    this->mousePos = event->globalPos();     // 获得鼠标位置
    this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}
void Login::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}
