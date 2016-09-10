#include "mselect.h"
#include "ui_mselect.h"
#include <QDebug>
mselect::mselect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mselect)
{
    initmain();
    initmissionbuttons();
    ui->setupUi(this);
    connect(_mission1, SIGNAL(clicked()), this, SLOT(onmission1clicked()));
    connect(_mission2, SIGNAL(clicked()), this, SLOT(onmission2clicked()));
    connect(_mission3, SIGNAL(clicked()), this, SLOT(onmission3clicked()));
}

mselect::~mselect()
{
    delete ui;
}

void mselect::onmission1clicked()
{
    qDebug()<<"m1";
    universal::mistemp=1;
    universal::SingleRole=1;
    hide();
    Single * newPage=new Single;
    newPage->setWindowTitle("单机");
    newPage->show();
}

void mselect::onmission2clicked()
{
    qDebug()<<"m2";
    universal::mistemp=2;
    universal::SingleRole=1;
    hide();
    Single * newPage=new Single;
    newPage->setWindowTitle("单机");
    newPage->show();
}

void mselect::onmission3clicked()
{
    qDebug()<<"m3";
    universal::mistemp=3;
    universal::SingleRole=1;
    hide();
    Single * newPage=new Single;
    newPage->setWindowTitle("单机");
    newPage->show();
}

void mselect::initmain()
{//注意：只有完成所有战役之后，才能选择战役！！！

}

void mselect::initmissionbuttons()
{
    _mission1=new QPushButton(this);
    QFont font;
    font.setPointSize(10);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _mission1->setFont(font);
    _mission1->setStyleSheet("color:#2b2b2b");
    _mission1->setCursor(Qt::PointingHandCursor);
    _mission1->setText("第一关");

    _mission2=new QPushButton(this);
    QFont font1;
    font1.setPointSize(10);
    font1.setFamily("Arial Rounded MT Bold");
    font1.setBold(true);
    _mission2->setFont(font1);
    _mission2->setStyleSheet("color:#2b2b2b");
    _mission2->setCursor(Qt::PointingHandCursor);
    _mission2->setText("第二关");

    _mission3=new QPushButton(this);

    QFont font2;
    font2.setPointSize(10);
    font2.setFamily("Arial Rounded MT Bold");
    font2.setBold(true);
    _mission3->setFont(font2);
    _mission3->setStyleSheet("color:#2b2b2b");
    _mission3->setCursor(Qt::PointingHandCursor);
    _mission3->setText("第三关");

    _mission1->setGeometry(100,20,200,50);
    _mission2->setGeometry(100,120,200,50);
    _mission3->setGeometry(100,240,200,50);
}

void mselect::closeEvent(QCloseEvent *event)
{
            deleteLater();
            Index * newPage=new Index;
            newPage->setWindowTitle("首页");
            newPage->show();
            event->accept();  //接受退出信号，程序退出
}
