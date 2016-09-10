#include "index.h"
#include "ui_index.h"
#include "login.h"
#include "maininterface.h"
#include "single.h"
#include "settings.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QDebug>
Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    originWindow();         //初始化窗体
    originSingleButton();
    originDanjiButton();    //初始化单击按钮
    originsettingsButton();    //初始化设置按钮
    originLianjiButton();   //初始化联机按钮
    if(universal::loaddb==1)
    {
        load();
        universal::loaddb=0;
    }
    ui->setupUi(this);
}

void Index::load()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("savegame.db");
        db.open();
        QSqlQuery query(db);
        query.prepare("select s1 from save");
        query.exec();
        if(query.next())
        {
            universal::skill1 = query.value(0).toInt();
        }
        query.prepare("select s2 from save");
        query.exec();
        if(query.next())
        {
            universal::skill2 = query.value(0).toInt();
        }
        query.prepare("select s3 from save");
        query.exec();
        if(query.next())
        {
            universal::skill3 = query.value(0).toInt();
        }
        query.prepare("select score from save");
        query.exec();
        if(query.next())
        {
            universal::scores = query.value(0).toInt();
        }
        query.prepare("select streak from save");
        query.exec();
        if(query.next())
        {
            universal::streak = query.value(0).toInt();
        }
        db.close();
        qDebug()<<universal::skill1<<universal::skill2<<universal::skill3<<universal::scores<<universal::streak;
}


Index::~Index()
{
    delete ui;
}

void Index::closeEvent(QCloseEvent *event)
{
    //存储技能进度
    QSqlDatabase db = connect2db();
    QSqlQuery query(db);
    query.prepare("update save set s1="+QString::number(universal::skill1)+", s2="+QString::number(universal::skill2)+", s3="+QString::number(universal::skill3)+", score="+QString::number(universal::scores)+", streak="+QString::number(universal::streak)+" where uid=1;");
    query.exec();
    db.close();
    qDebug()<<"index closed";
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

void Index::originSingleButton()
{
    _Single=new QPushButton(this);
    _Single->setGeometry(20,50,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _Single->setFont(font);
    _Single->setStyleSheet("color:#2b2b2b");
    _Single->setCursor(Qt::PointingHandCursor);
    _Single->setText("战役模式");
    _Single->installEventFilter(this);//设置监听
    _canSingle=true;                  //刚开始可以点击 单击模式按钮
}

//初始化单机按钮
void Index::originDanjiButton()
{
    _danji=new QPushButton(this);
    _danji->setGeometry(20,150,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _danji->setFont(font);
    _danji->setStyleSheet("color:#2b2b2b");
    _danji->setCursor(Qt::PointingHandCursor);
    _danji->setText("单人游戏");
    _danji->installEventFilter(this);//设置监听
    _canDanji=true;                  //刚开始可以点击 单击模式按钮
}

void Index::originsettingsButton()
{
    _settings=new QPushButton(this);
    _settings->setGeometry(20,250,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _settings->setFont(font);
    _settings->setStyleSheet("color:#2b2b2b");
    _settings->setCursor(Qt::PointingHandCursor);
    _settings->setText("游戏设置");
    _settings->installEventFilter(this);//设置监听
    _cansettings=true;
}

//初始化联机按钮
void Index::originLianjiButton()
{
    _lianji=new QPushButton(this);
    _lianji->setGeometry(20,350,400,70);
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _lianji->setFont(font);
    _lianji->setStyleSheet("color:#2b2b2b");
    _lianji->setCursor(Qt::PointingHandCursor);
    _lianji->setText("多人游戏");
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
    if(obj==_Single && event->type()==QEvent::MouseButtonPress && _canSingle)
    {
        _canSingle=false;
        close();
        singlesl * newPage=new singlesl;
        newPage->setWindowTitle("单机");
        newPage->show();
        return true;
    }
    if(obj==_settings && event->type()==QEvent::MouseButtonPress && _cansettings)
    {
        //_cansettings=false;
        //close();
        settings * newPage=new settings;
        newPage->setWindowTitle("设置");
        newPage->exec();
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

QSqlDatabase Index::connect2db()
{
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("savegame.db");
    if (db.open())
    {
        qDebug() << "open success!";
    }
    else
    {
        qDebug() << "open fail";
    }
    return db;
}
