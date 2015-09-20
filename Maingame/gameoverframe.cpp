#include "gameoverframe.h"
#include "ui_gameoverframe.h"
#include <QPixmap>
#include <QFont>
#include<QMovie>

GameOverFrame::GameOverFrame(bool ifWin,QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GameOverFrame)
{
    //初始化窗体属性:
    setFixedSize(380,200);
    QFont font;
    font.setPointSize(15);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    setStyleSheet("background-color:#333333;color:#2b2b2b");
    //初始化胜负标签 && 播放音乐:
    _resLabel=new QLabel(this);
    _resLabel->setGeometry(50,20,380,90);
    QMovie *winMovie=new QMovie(":/image/res/win.gif");
    QMovie *loseMovie=new QMovie(":/image/res/lose.gif");    
    if(ifWin)
    {//若是赢了
//        _resLabel->setPixmap(QPixmap(":/image/res/win1.png"));
        _resLabel->setMovie(winMovie);
        _music=new QSound("win.wav",this);
    }
    else
    {//若是输了
//        _resLabel->setPixmap(QPixmap(":/image/res/lose1.png"));
        _resLabel->setMovie(loseMovie);
        _music=new QSound("lose.wav",this);
    }
    _music->play();
    winMovie->start();
    loseMovie->start();
    //初始化"继续游戏"按钮:
    _canOk=true;
    _ok=new QPushButton(this);
    _ok->setGeometry(60,130,100,40);
    _ok->setFont(font);
    _ok->setText("again");
    _ok->setCursor(Qt::PointingHandCursor);
    _ok->setStyleSheet("background-color:#e8e8e8");
    _ok->installEventFilter(this); //设置监听者
    //初始化"离开游戏"按钮
    _canNo=true;
    _no=new QPushButton(this);
    _no->setGeometry(220,130,100,40);
    _no->setFont(font);
    _no->setText("exit");
    _no->setCursor(Qt::PointingHandCursor);
    _no->setStyleSheet("background-color:#e8e8e8");
    _no->installEventFilter(this); //设置监听者
    //渲染:
    ui->setupUi(this);
}

GameOverFrame::~GameOverFrame()
{
    delete ui;
}

//事件过滤器
/*
 * if 按下 继续游戏按钮 且按钮可用(防止连续快速点击造成多次发送相同信号)
 * {
 *    设置继续游戏按钮为不可用
 *    将用户选择了继续游戏 这个消息 报告给 游戏界面ui层
 *    关闭此界面
 * }
 * if 按下 离开游戏按钮 且按钮可用(防止连续快速点击造成多次发送相同信号)
 * {
 *    设置离开游戏按钮为不可用
 *    将用户选择了离开游戏 这个消息 报告给 游戏界面ui层
 *    关闭此界面
 * }
*/
bool GameOverFrame::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_ok && event->type()==QEvent::MouseButtonPress && _canOk)
    {
        _canOk=false;
        emit report_Choose(true);
        close();
        return true;
    }
    if(obj==_no && event->type()==QEvent::MouseButtonPress && _canNo)
    {
        _canNo=false;
        emit report_Choose(false);
        close();
        return true;
    }
    return QFrame::eventFilter(obj,event);
}
