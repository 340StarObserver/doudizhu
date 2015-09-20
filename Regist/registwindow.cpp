#include "registwindow.h"
#include "ui_registwindow.h"
#include <QFont>
#include <QTextCursor>
#include <QDateTime>

RegistWindow::RegistWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistWindow)
{
    _isRunning = false;
    originServer();      //配置业务层
    originWindow();      //配置窗体属性
    originFdRegion();    //配置信息反馈区域
    originStateLabel();  //配置状态标签
    originConButton();   //配置注册服务开关按钮
    ui->setupUi(this);
}

RegistWindow::~RegistWindow()
{
    delete ui;
}

//事件过滤器(服务开关按钮)
bool RegistWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_control && event->type()==QEvent::MouseButtonPress)
    {
        _isRunning = !_isRunning;
        if(_isRunning){
            _server->start();
            _control->setText("stop");
            _statelabel->setText("regist server is running");
            onReport("regist server start success~~");
        }else{
            _server->stop();
            _control->setText("start");
            _statelabel->setText("regist server is closed");
            onReport("regist server close success");
        }
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

void RegistWindow::originWindow()
{
    setFixedSize(800,600);
    setStyleSheet("background-color:#333333");
}

void RegistWindow::originFdRegion()
{
    QFont font;
    font.setBold(true);
    font.setPointSize(15);
    _fdRegion = new QTextBrowser(this);
    _fdRegion->setGeometry(0,0,800,500);
    _fdRegion->setStyleSheet("color:green;background-color:black;border:3px solid orange");
    _fdRegion->setFont(font);
    connect(_fdRegion,SIGNAL(cursorPositionChanged()),this,SLOT(autoScroll()));
}

//反馈区域文本快的滚动条自动下滑
void RegistWindow::autoScroll()
{
    _fdRegion->moveCursor(QTextCursor::End);
}

void RegistWindow::originStateLabel()
{
    _statelabel = new QLabel(this);
    _statelabel->setGeometry(0,520,500,50);
    _statelabel->setAlignment(Qt::AlignCenter);
    _statelabel->setStyleSheet("color:orange");
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    _statelabel->setFont(font);
}

void RegistWindow::originConButton()
{
    _control = new QPushButton(this);
    _control->setText("start");
    _control->setGeometry(600,530,150,40);
    _control->setStyleSheet("background-color:white");
    QFont font;
    font.setPointSize(25);
    font.setWordSpacing(10);
    font.setBold(true);
    _control->setFont(font);
    _control->setCursor(Qt::PointingHandCursor);
    _control->installEventFilter(this);
}

//配置注册服务业务
void RegistWindow::originServer()
{
    _server = new RegistServer(this);
    connect(_server,SIGNAL(report(QString)),this,SLOT(onReport(QString)));
}

//接收业务层的汇报信号,将业务层报告的信息显示到反馈区域文本快
void RegistWindow::onReport(const QString &str)
{
    QDateTime time = QDateTime::currentDateTime();
    QString ss=time.toString("yyyy-MM-dd hh:mm:ss").append(" : ");
    ss.append(str).append("\n");
    _fdRegion->setText(_fdRegion->toPlainText().append(ss));
}
