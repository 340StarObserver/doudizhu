#include "index.h"
#include "ui_index.h"
#include "login.h"
#include "maininterface.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>

Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    originWindow();         //初始化窗体
    originDanjiButton();    //初始化单击按钮
    originLianjiButton();   //初始化联机按钮
    ui->setupUi(this);
}

Index::~Index()
{
    delete ui;
}

//初始化窗体
void Index::originWindow()
{
    setFixedSize(800,600);
}

//绘图事件(设置背景)
void Index::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/image/res/register.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//初始化单机按钮
void Index::originDanjiButton()
{
    _danji=new QPushButton(this);
    _danji->setGeometry(200,180,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _danji->setFont(font);
    _danji->setStyleSheet("color:#2b2b2b");
    _danji->setCursor(Qt::PointingHandCursor);
    _danji->setText("Single    Player");
    _danji->installEventFilter(this);//设置监听
    _canDanji=true;                  //刚开始可以点击 单击模式按钮
}

//初始化联机按钮
void Index::originLianjiButton()
{
    _lianji=new QPushButton(this);
    _lianji->setGeometry(200,350,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _lianji->setFont(font);
    _lianji->setStyleSheet("color:#2b2b2b");
    _lianji->setCursor(Qt::PointingHandCursor);
    _lianji->setText("Mutiply Players");
    _lianji->installEventFilter(this);//设置监听
    _canLianji=true;                  //刚开始可以点击 联机模式按钮
}

//事件过滤器
/*
 * 注: 设置按钮可用不可用 是为了 防止连续快速多次点击 造成的多余的事件
 * if 按下 进入单机模式 且 该按钮可用
 * {
 *    设置该按钮不可用
 *    关闭该界面
 *    创建并打开单机界面
 * }
 * if 按下 进入联机模式 且 该按钮可用
 * {
 *    设置该按钮不可用
 *    关闭该界面
 *    创建并打开联机界面
 * }
*/
bool Index::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_danji && event->type()==QEvent::MouseButtonPress && _canDanji)
    {
        _canDanji=false;
        close();
        MainInterface * newPage=new MainInterface;
        newPage->setWindowTitle("单机");
        newPage->show();
        return true;
    }
    if(obj==_lianji && event->type()==QEvent::MouseButtonPress && _canLianji)
    {
        _canLianji=false;
        close();
        Login * newPage=new Login;
        newPage->setWindowTitle("登陆");
        newPage->show();
        return true;
    }
    return QWidget::eventFilter(obj,event);
}
