#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QFont>
#include <QDateTime>
#include "gameserver.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    _isRun=false;       //起初服务不在运行
    originWindow();     //配置窗体属性
    originFdRegion();   //配置反馈区
    originButton();     //配置开关按钮
    originLabel();      //配置状态标签
    originServer();     //配置游戏业务层
    ui->setupUi(this);  //渲染
}

//析构时,删除单例的游戏业务层
GameWindow::~GameWindow()
{
    GameServer::destroyInstance();
    delete ui;
}

//配置窗体属性
void GameWindow::originWindow()
{
    setFixedSize(800,600);
    setStyleSheet("background-color:#999999");
}

//配置反馈区
void GameWindow::originFdRegion()
{
    QFont font;
    font.setPointSize(16);
    _fdRegion = new QTextBrowser(this);
    _fdRegion->setGeometry(0,0,800,500);
    _fdRegion->setStyleSheet("color:green;background-color:black;border:2px solid orange");
    _fdRegion->setFont(font);
    connect(_fdRegion,SIGNAL(cursorPositionChanged()),this,SLOT(autoScroll()));
}

//反馈区滚动条自动下滑
void GameWindow::autoScroll()
{
    _fdRegion->moveCursor(QTextCursor::End);
}

//接收业务层的汇报信号,并将信息添加到反馈区
void GameWindow::onReport(const QString &str)
{
    QDateTime time = QDateTime::currentDateTime();
    QString ss=time.toString("yyyy-MM-dd hh:mm:ss").append(" : ");
    ss.append(str).append("\n");
    _fdRegion->setText(_fdRegion->toPlainText().append(ss));
}

//配置开关按钮
void GameWindow::originButton()
{
    _button = new QPushButton(this);
    _button->setText("start");
    _button->setGeometry(600,515,150,70);
    _button->setStyleSheet("color:white;background-color:#333333");
    QFont font;
    font.setPointSize(30);
    font.setWordSpacing(15);
    font.setBold(true);
    _button->setFont(font);
    _button->setCursor(Qt::PointingHandCursor);
    _button->installEventFilter(this);
}

//配置状态标签
void GameWindow::originLabel()
{
    _stateLabel = new QLabel(this);
    _stateLabel->setGeometry(20,525,560,50);
    QFont font;
    font.setPointSize(30);
    _stateLabel->setFont(font);
}

//配置游戏业务层
void GameWindow::originServer()
{
    GameServer * server=GameServer::getInstance();
    connect(server,SIGNAL(report(QString)),this,SLOT(onReport(QString)));
}

//事件过滤器(服务开关按钮)
bool GameWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_button && event->type()==QEvent::MouseButtonPress){
        if(_isRun){
            _isRun=false;
            _button->setText("start");
            _stateLabel->setText("server is sleep");
            onReport("game server stop");
            GameServer::getInstance()->stop();
        }else{
            _isRun=true;
            _button->setText("stop");
            _stateLabel->setText("server is running");
            onReport("game server start");
            GameServer::getInstance()->start();
        }
        return true;
    }
    return QWidget::eventFilter(obj,event);
}
