#include "singlesl.h"
#include "ui_singlesl.h"
#include <QMessageBox>
#include <QTranslator>
#include <QSqlDatabase>
#include <QSqlQuery>
singlesl::singlesl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::singlesl)
{
    init();
    load();
    setWindowFlags(Qt::FramelessWindowHint);
    initload();
    initnews();
    initnewd();
    //设定载入按钮
    if(universal::mission==2||universal::mission==3)
    {
        _load->setEnabled(true);
    }
    else
        _load->setEnabled(false);
    //选择关卡功能只有在通关后才可用
    if(universal::mission==-1)
        _news->setEnabled(true);
    else
        _news->setEnabled(false);

    ui->setupUi(this);
    connect(_news, SIGNAL(clicked()), this, SLOT(onnewsclicked()));
    connect(_newd, SIGNAL(clicked()), this, SLOT(onnewdclicked()));
    connect(_load, SIGNAL(clicked()), this, SLOT(onloadclicked()));
    connect(_close,SIGNAL(clicked()),this,SLOT(oncloseclicked()));
}

singlesl::~singlesl()
{
    delete ui;
}

void singlesl::save()
{

}

void singlesl::load()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("savegame.db");
        db.open();
        QSqlQuery query(db);
        query.prepare("select mission from save");
        query.exec();
        if(query.next())
        {
            universal::mission = query.value(0).toInt();
        }
       // db.close();
}

void singlesl::onnewsclicked()
{
    hide();
    mselect * newPage=new mselect;
    newPage->setWindowTitle("选择关卡");
    newPage->show();
}

void singlesl::onnewdclicked()
{
    if(universal::mission!=1)
    {
        QMessageBox::StandardButton rb =QMessageBox::question(NULL,"警告","开启新战役 <font color='red'>将抹去之前的一切进度</font>", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        {
            if (rb==QMessageBox::Yes)
            {
                universal::mission=1;
                universal::mistemp=0;
                universal::SingleRole=1;
                hide();
                Single * newPage=new Single;
                newPage->setWindowTitle("单机");
                newPage->show();
            }
        }
    }
    else
    {
        universal::SingleRole=1;
        universal::mistemp=0;
        hide();
        Single * newPage=new Single;
        newPage->setWindowTitle("单机");
        newPage->show();
    }
}

void singlesl::onloadclicked()
{
    universal::SingleRole=1;
    hide();
    Single * newPage=new Single;
    newPage->setWindowTitle("单机");
    newPage->show();
}

void singlesl::oncloseclicked()
{
    close();
}

void singlesl::closeEvent(QCloseEvent *event)
{
            deleteLater();
            Index * newPage=new Index;
            newPage->setWindowTitle("首页");
            newPage->show();
            event->accept();  //接受退出信号，程序退出
}

void singlesl::init()
{
    _close=new QPushButton(this);
    _close->setGeometry(20,300,100,50);
    QFont font;
    font.setPointSize(10);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _close->setFont(font);
    _close->setStyleSheet("color:#2b2b2b");
    _close->setCursor(Qt::PointingHandCursor);
    _close->setText("返回");
}

void singlesl::paintEvent(QPaintEvent * event)
{
    static QPixmap backpic(":/image/res/register.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

void singlesl::initload()
{
    _load=new QPushButton(this);
    _load->setGeometry(20,220,120,50);
    QFont font;
    font.setPointSize(15);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _load->setFont(font);
    _load->setStyleSheet("color:#2b2b2b");
    _load->setCursor(Qt::PointingHandCursor);
    _load->setText("载入游戏");
}

void singlesl::initnewd()
{
    _newd=new QPushButton(this);
    _newd->setGeometry(20,20,120,50);
    QFont font;
    font.setPointSize(15);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _newd->setFont(font);
    _newd->setStyleSheet("color:#2b2b2b");
    _newd->setCursor(Qt::PointingHandCursor);
    _newd->setText("地主战役");
}

void singlesl::initnews()
{
    _news=new QPushButton(this);
    _news->setGeometry(20,120,120,50);
    QFont font;
    font.setPointSize(15);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _news->setFont(font);
    _news->setStyleSheet("color:#2b2b2b");
    _news->setCursor(Qt::PointingHandCursor);
    _news->setText("选择关卡");
}
