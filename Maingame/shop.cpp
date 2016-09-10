#include "shop.h"
#include "ui_shop.h"
#include <QDebug>
shop::shop(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::shop)
{
    initmain();
    ui->setupUi(this);
    connect(_skill1,SIGNAL(clicked(bool)),this,SLOT(onskill1clicked()));
    connect(_skill2,SIGNAL(clicked(bool)),this,SLOT(onskill2clicked()));
    connect(_skill3,SIGNAL(clicked(bool)),this,SLOT(onskill3clicked()));
}

shop::~shop()
{
    delete ui;
}

void shop::onskill1clicked()
{
    QMessageBox::StandardButton rb =QMessageBox::question(NULL,"警告","购买 <font color='red'>破釜沉舟</font>技能，将花费<font color='red'>2</font>分!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    {
        if (rb==QMessageBox::Yes&&universal::scores>=2)
        {
            qDebug()<<"破釜沉舟";
            universal::skill1++;
            universal::scores-=2;
            _skill1->setText("破釜沉舟 ("+QString::number(universal::skill1)+")");
        }
        else
        {
            QMessageBox::about(this,tr("购买失败!"),tr("请检查ji'f积分是否不足"));
        }
    }
}

void shop::onskill2clicked()
{
    QMessageBox::StandardButton rb =QMessageBox::question(NULL,"警告","购买 <font color='red'>夜观星象</font>技能，将花费<font color='red'>1</font>分!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    {
        if (rb==QMessageBox::Yes&&universal::scores>=1)
        {
            qDebug()<<"夜观星象";
            universal::skill2++;
            universal::scores-=1;
            _skill2->setText("夜观星象 ("+QString::number(universal::skill2)+")");
        }
        else
        {
            QMessageBox::about(this,tr("购买失败!"),tr("请检查ji'f积分是否不足"));
        }
    }
}

void shop::onskill3clicked()
{
    QMessageBox::StandardButton rb =QMessageBox::question(NULL,"警告","购买 <font color='red'>横扫千军</font>技能，将花费<font color='red'>3</font>分!", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    {
        if (rb==QMessageBox::Yes&&universal::scores>=3)
        {
            qDebug()<<"横扫千军";
            universal::skill3++;
            universal::scores-=3;
            _skill3->setText("横扫千军 ("+QString::number(universal::skill3)+")");
        }
        else
        {
            QMessageBox::about(this,tr("购买失败!"),tr("请检查ji'f积分是否不足"));
        }
    }
}

void shop::initmain()
{
    _skill1=new QPushButton(this);
    QFont font;
    font.setPointSize(10);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _skill1->setFont(font);
    _skill1->setStyleSheet("color:#2b2b2b");
    _skill1->setCursor(Qt::PointingHandCursor);
    _skill1->setText("破釜沉舟 ("+QString::number(universal::skill1)+")");

    _skill2=new QPushButton(this);
    QFont font1;
    font1.setPointSize(10);
    font1.setFamily("Arial Rounded MT Bold");
    font1.setBold(true);
    _skill2->setFont(font1);
    _skill2->setStyleSheet("color:#2b2b2b");
    _skill2->setCursor(Qt::PointingHandCursor);
    _skill2->setText("夜观星象 ("+QString::number(universal::skill2)+")");

    _skill3=new QPushButton(this);

    QFont font2;
    font2.setPointSize(10);
    font2.setFamily("Arial Rounded MT Bold");
    font2.setBold(true);
    _skill3->setFont(font2);
    _skill3->setStyleSheet("color:#2b2b2b");
    _skill3->setCursor(Qt::PointingHandCursor);
    _skill3->setText("横扫千军 ("+QString::number(universal::skill3)+")");

    _skill1->setGeometry(100,20,200,50);
    _skill2->setGeometry(100,120,200,50);
    _skill3->setGeometry(100,220,200,50);
}
