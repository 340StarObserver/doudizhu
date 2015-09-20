#include "register.h"
#include "ui_register.h"
#include <QPainter>
#include <QPixmap>
#include "login.h"
#include <QString>
#include <QRegExp>
#include "clientsocket.h"
#include <QMessageBox>
#include <QDataStream>

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);

    radioButton_3 = new QRadioButton(this);
    radioButton_3->setGeometry(QRect(520, 350, 120, 90));
    radioButton_3->setStyleSheet(QStringLiteral(""));
    QIcon icon;
    icon.addFile(QStringLiteral(":/image/res/head3.png"), QSize(), QIcon::Normal, QIcon::Off);
    radioButton_3->setIcon(icon);
    radioButton_3->setIconSize(QSize(90, 90));
    radioButton_3->setChecked(true);

    radioButton = new QRadioButton(this);
    radioButton->setGeometry(QRect(220, 350, 120, 90));
    QIcon icon1;
    icon1.addFile(QStringLiteral(":/image/res/head1.png"), QSize(), QIcon::Normal, QIcon::Off);
    radioButton->setIcon(icon1);
    radioButton->setIconSize(QSize(90, 90));
    radioButton->setCheckable(true);
    radioButton->setChecked(false);

    aLabel2 = new QLabel(this);
    aLabel2->setGeometry(QRect(500, 200, 250, 40));
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    font.setFamily("Microsoft YaHei");

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setGeometry(QRect(220, 200, 250, 40));
    passwordLineEdit->setMaxLength(9);
    passwordLineEdit->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setFont(font);

    accountLabel = new QLabel(this);
    accountLabel->setGeometry(QRect(50, 130, 150, 40));
    accountLabel->setText("帐号：");
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    QBrush brush1(QColor(231, 231, 231, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    accountLabel->setPalette(palette);

    accountLabel->setFont(font);

    accinfoLabe = new QLabel(this);
    accinfoLabe->setGeometry(QRect(500, 130, 250, 40));
    accinfoLabe->setFont(font);
    QPalette palette1;
    QBrush brush2(QColor(255, 0, 0, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
    palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
    palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    accinfoLabe->setPalette(palette1);

    _canRegist=true;//一开始可以点击注册按钮
    _canBack=true;  //一开始可以点击返回按钮
    registerButton = new QPushButton(this);
    registerButton->setGeometry(QRect(50, 470, 100, 40));
    backButton=new QPushButton(this);
    backButton->setGeometry(QRect(250,470,100,40));
    QPalette palette2;
    palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette2.setBrush(QPalette::Active, QPalette::Text, brush);
    palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
    palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
    palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
    palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
    registerButton->setPalette(palette2);
    backButton->setPalette(palette2);
    QFont font1;
    font1.setFamily("Microsoft YaHei");
    font1.setBold(true);
    font1.setPointSize(16);
    registerButton->setFont(font1);
    registerButton->setContextMenuPolicy(Qt::DefaultContextMenu);
    registerButton->setCheckable(false);
    registerButton->setAutoDefault(false);
    registerButton->setFlat(false);
    registerButton->setText("submit");
    registerButton->setStyleSheet("color:#2b2b2b");
    registerButton->setCursor(Qt::PointingHandCursor);
    backButton->setFont(font1);
    backButton->setContextMenuPolicy(Qt::DefaultContextMenu);
    backButton->setCheckable(false);
    backButton->setAutoDefault(false);
    backButton->setFlat(false);
    backButton->setText("back");
    backButton->setStyleSheet("color:#2b2b2b");
    backButton->setCursor(Qt::PointingHandCursor);

    label = new QLabel(this);
    label->setGeometry(QRect(200,40,400,60));
    label->setText(">填写信息<");
    label->setAlignment(Qt::AlignCenter);
    QPalette palette3;
    palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    label->setPalette(palette3);
    QFont font2;
    font2.setFamily("Microsoft YaHei");
    font2.setPointSize(26);
    font2.setBold(true);
    label->setFont(font2);
    label->setFrameShape(QFrame::NoFrame);
    label->setFrameShadow(QFrame::Plain);

    radioButton_2 = new QRadioButton(this);
    radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
    radioButton_2->setGeometry(QRect(370, 350, 120, 90));
    radioButton_2->setStyleSheet(QStringLiteral(""));
    QIcon icon2;
    icon2.addFile(QStringLiteral(":/image/res/head2.png"), QSize(), QIcon::Normal, QIcon::Off);
    radioButton_2->setIcon(icon2);
    radioButton_2->setIconSize(QSize(90, 90));
    radioButton_2->setCheckable(true);
    headtitleLabel = new QLabel(this);
    headtitleLabel->setObjectName(QStringLiteral("headtitleLabel"));
    headtitleLabel->setGeometry(QRect(50, 350, 150, 40));
    headtitleLabel->setText("头像：");
    QPalette palette4;
    palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    headtitleLabel->setPalette(palette4);
    headtitleLabel->setFont(font);
    aLabel4 = new QLabel(this);
    aLabel4->setGeometry(QRect(500, 270, 250, 40));
    repeatLinEdit = new QLineEdit(this);
    repeatLinEdit->setGeometry(QRect(220, 270, 250, 40));
    repeatLinEdit->setEchoMode(QLineEdit::Password);
    repeatLinEdit->setMaxLength(9);
    repeatLinEdit->setFont(font);
    passinfoLabel = new QLabel(this);
    passinfoLabel->setGeometry(QRect(500, 200, 250, 40));
    passinfoLabel->setFont(font);
    QPalette palette5;
    palette5.setBrush(QPalette::Active, QPalette::WindowText, brush2);
    palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
    palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    passinfoLabel->setPalette(palette5);
    passwordLabel = new QLabel(this);
    passwordLabel->setGeometry(QRect(50, 200, 150, 40));
    passwordLabel->setText("密码：");
    QPalette palette6;
    palette6.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    passwordLabel->setPalette(palette6);
    passwordLabel->setFont(font);
    repeatLabel = new QLabel(this);
    repeatLabel->setGeometry(QRect(50, 270, 150, 40));
    repeatLabel->setText("重复密码：");
    QPalette palette7;
    palette7.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
    repeatLabel->setPalette(palette7);
    repeatLabel->setFont(font);
    accountLineEdit = new QLineEdit(this);
    accountLineEdit->setGeometry(QRect(220, 130, 250, 40));
    accountLineEdit->setMaxLength(8);
    accountLineEdit->setFont(font);
    QPalette palette8;
    accountLineEdit->setPalette(palette8);
    aLabel1 = new QLabel(this);
    aLabel1->setGeometry(QRect(500, 130, 250, 40));
    //设置tab顺序:
    setTabOrder(backButton,accountLineEdit);
    setTabOrder(accountLineEdit,passwordLineEdit);
    setTabOrder(passwordLineEdit,repeatLinEdit);
    setTabOrder(repeatLinEdit,registerButton);
    setTabOrder(registerButton,backButton);
    //信号关联
    connect(accountLineEdit,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(accountLineEditslot()));
    connect(passwordLineEdit,SIGNAL(cursorPositionChanged(int,int)),this,SLOT(passwordLineEditslot(int,int)));
    connect(accountLineEdit,SIGNAL(editingFinished()),this,SLOT(accountEditingFinishedslot()));
    connect(passwordLineEdit,SIGNAL(editingFinished()),this,SLOT(passwordeditingFinishedslot()));
    connect(repeatLinEdit,SIGNAL(editingFinished()),this,SLOT(repeateditingFinishedslot()));
    connect(radioButton,SIGNAL(toggled(bool)),this,SLOT(radioButtonslot(bool)));
    connect(radioButton_2,SIGNAL(toggled(bool)),this,SLOT(radioButton_2slot(bool)));
    connect(radioButton_3,SIGNAL(toggled(bool)),this,SLOT(radioButton_3slot(bool)));
    connect(registerButton,SIGNAL(clicked()),this,SLOT(registerBtnslot()));
    connect(backButton,SIGNAL(clicked()),this,SLOT(backBtnslot()));
    _head=0;
    originSocket();
}

//配置套接字在注册时的接收槽
void Register::originSocket()
{
    ClientSocket::getInstance()->cancelSignals();
    QTcpSocket * socket=ClientSocket::getInstance()->getSocket();
    connect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

//关闭套接字在注册时的接收槽(在关闭界面时自动调用)
void Register::closeEvent(QCloseEvent *event)
{
    QTcpSocket * socket=ClientSocket::getInstance()->getSocket();
    disconnect(socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

//接收并处理来自服务端的注册结果报文
void Register::onReadyRead()
{
    QTcpSocket * socket=ClientSocket::getInstance()->getSocket();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_5);
    bool res;
    in>>res;
    if(res)
    {
        QMessageBox::about(this,"","regist success");
        close();
        Login * newPage=new Login;
        newPage->show();
    }
    else
    {
        QMessageBox::warning(this,"warning","regist failed",QMessageBox::Ok);
        _canRegist=true;
    }
}

Register::~Register()
{
    delete ui;
}

//注册界面背景
void Register::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/image/res/register.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//帐号输入栏中光标位置改变时,显示提示
void Register::accountLineEditslot()
{
    accinfoLabe->setText("student number");
}

//密码输入栏中光标位置改变时，显示提示
void Register::passwordLineEditslot(int arg1, int arg2)
{
    passinfoLabel->setText("card number");
}

//帐号输入正确，加载勾号，否则叉号
void Register::accountEditingFinishedslot()
{
    accinfoLabe->setText(" ");
    QPixmap pics1(":/image/res/available.png");
    QPixmap pics2(":/image/res/wrong.png");
    if(QRegExp("^\\d{2}[a-z0-9A-Z]{1}14\\d{3}").indexIn(accountLineEdit->text())==0)
        aLabel1->setPixmap(pics1);
    else
        aLabel1->setPixmap(pics2);
}

//密码输入正确，加载勾号，否则叉号
void Register::passwordeditingFinishedslot()
{
    passinfoLabel->setText(" ");
    QPixmap pics1(":/image/res/available.png");
    QPixmap pics2(":/image/res/wrong.png");
    if(QRegExp("21314\\d{4}").indexIn(passwordLineEdit->text())==0)
        aLabel2->setPixmap(pics1);
    else
        aLabel2->setPixmap(pics2);
}

//重复输入密码进行确认，若正确，勾号；否则，叉号
void Register::repeateditingFinishedslot()
{
    QPixmap pics1(":/image/res/available.png");
    QPixmap pics2(":/image/res/wrong.png");
    if(QRegExp("21314\\d{4}").indexIn(repeatLinEdit->text())==0 && passwordLineEdit->text()==repeatLinEdit->text())
        aLabel4->setPixmap(pics1);
    else
       aLabel4->setPixmap(pics2);
}

//选择此头像时，表现开心，否则失望。以下三个槽函数同
//开心头像即牌局胜利后表现，失望头像即牌局失败后表现
void Register::radioButtonslot(bool checked)
{
    QIcon ico1(":/image/res/winner1.png");
    QIcon ico2(":/image/res/loser1.png");
    if(checked)
    {
        radioButton->setIcon(ico1);
        _head=0;
    }
    else radioButton->setIcon(ico2);
}

void Register::radioButton_2slot(bool checked)
{
    QIcon ico1(":/image/res/winner2.png");
    QIcon ico2(":/image/res/loser2.png");
    if(checked)
    {
        radioButton_2->setIcon(ico1);
        _head=1;
    }
    else radioButton_2->setIcon(ico2);
}

void Register::radioButton_3slot(bool checked)
{
    QIcon ico1(":/image/res/winner3.png");
    QIcon ico2(":/image/res/loser3.png");
    if(checked)
    {
        radioButton_3->setIcon(ico1);
        _head=2;
    }
    else radioButton_3->setIcon(ico2);
}

//校验数据合法性
//账号必须是14级的学号,密码和重复密码都必须是14级的一卡通,重复密码等于密码
bool Register::validData()const
{
    QString user=accountLineEdit->text();
    QString pwd=passwordLineEdit->text();
    QString rpwd=repeatLinEdit->text();
    QRegExp re1("^\\d{2}[a-z0-9A-Z]{1}14\\d{3}");
    QRegExp re2("21314\\d{4}");
    if(re1.indexIn(user)!=0)
        return false;
    if(re2.indexIn(pwd)!=0)
        return false;
    if(re2.indexIn(rpwd)!=0)
        return false;
    return pwd==rpwd;
}

//点击注册按钮
void Register::registerBtnslot()
{
    if(validData())
    {
        if(_canRegist)
        {
            _canRegist=false;
            QString user=accountLineEdit->text();
            QString pwd=passwordLineEdit->text();
            ClientSocket::getInstance()->sendRegist(user,pwd,_head);
        }
    }
    else
    {
        QString str="data format wrong!";
        QMessageBox::warning(this,"warning",str,QMessageBox::Ok);
    }
}

void Register::backBtnslot()
{
    if(_canBack)
    {
        _canBack=false;
        close();
        Login *l=new Login;
        l->show();
    }
}
