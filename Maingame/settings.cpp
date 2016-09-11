#include "settings.h"
#include "ui_settings.h"
#include "universal.h"
#include "index.h"
#include <QPainter>
#include <QTime>
#include <QDebug>
#include <fstream>
#include <QVector>
#include <QMessageBox>
#include <QToolButton>
#include <QDesktopWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
using namespace std;

settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    init();
    newshop();
    settingssize(universal::setpix);
    originpix();
    originpic();
    themes();
    originfont();


    connect(radioButton11, SIGNAL(clicked()), this, SLOT(onRadioClickpix()));
    connect(radioButton12, SIGNAL(clicked()), this, SLOT(onRadioClickpix()));
    connect(radioButton13, SIGNAL(clicked()), this, SLOT(onRadioClickpix()));

    connect(radioButton21, SIGNAL(clicked()), this, SLOT(onRadioClickpic()));
    connect(radioButton22, SIGNAL(clicked()), this, SLOT(onRadioClickpic()));
    connect(radioButton23, SIGNAL(clicked()), this, SLOT(onRadioClickpic()));

    connect(radioButton31, SIGNAL(clicked()), this, SLOT(onRadioThemeClicked()));
    connect(radioButton32, SIGNAL(clicked()), this, SLOT(onRadioThemeClicked()));
    connect(radioButton33, SIGNAL(clicked()), this, SLOT(onRadioThemeClicked()));
    connect(radioButton34, SIGNAL(clicked()), this, SLOT(onRadioThemeClicked()));

    connect(checkbox1,SIGNAL(clicked(bool)),this,SLOT(onCheck1()));
    connect(checkbox2,SIGNAL(clicked(bool)),this,SLOT(onCheck2()));
    connect(checkbox3,SIGNAL(clicked(bool)),this,SLOT(onCheck3()));
    {
        if(universal::debugmode==1)
            checkbox1->setChecked(true);
        else
            checkbox1->setChecked(false);
        if(universal::windowed==0)
            checkbox2->setChecked(true);
        else
            checkbox2->setChecked(false);
        if(universal::_skills==1)
            checkbox3->setChecked(true);
        else
            checkbox3->setChecked(false);
    }

    if(universal::eecount>=0)
        {
    checkbox1->hide();
    checkbox2->hide();
    checkbox3->hide();
    radioButton33->hide();
    radioButton34->hide();
    _shop->hide();
    }
    ui->setupUi(this);
}

settings::~settings()
{
    delete ui;
}

void settings::originpix()
{
    _btnpix = new QButtonGroup(this);
    _btnpix->addButton(radioButton11,0);
    _btnpix->addButton(radioButton12,1);
    _btnpix->addButton(radioButton13,2);
    if(universal::setpix==1)
    radioButton11->setChecked(true);
    if(universal::setpix==1.2)
    radioButton12->setChecked(true);
    if(universal::setpix==1.5)
    radioButton13->setChecked(true);
}

void settings::originpic()
{
    _btnpic = new QButtonGroup(this);
    _btnpic->addButton(radioButton21, 0);
    _btnpic->addButton(radioButton22, 1);
    _btnpic->addButton(radioButton23, 2);
    if(universal::diff==0)
    radioButton21->setChecked(true);
    if(universal::diff==1)
    radioButton22->setChecked(true);
    if(universal::diff==2)
    radioButton23->setChecked(true);
}

void settings::originfont()
{
    radioButton11->setFont(QFont("",20,QFont::Bold));
    radioButton12->setFont(QFont("",20,QFont::Bold));
    radioButton13->setFont(QFont("",20,QFont::Bold));
    radioButton21->setFont(QFont("",20,QFont::Bold));
    radioButton22->setFont(QFont("",20,QFont::Bold));
    radioButton23->setFont(QFont("",20,QFont::Bold));
    radioButton31->setFont(QFont("",20,QFont::Bold));
    radioButton32->setFont(QFont("",20,QFont::Bold));
    radioButton33->setFont(QFont("",20,QFont::Bold));
    radioButton34->setFont(QFont("",20,QFont::Bold));
}

void settings::newshop()
{
        _shop=new QPushButton(this);
        QFont font;
        font.setPointSize(15);
        font.setFamily("Arial Rounded MT Bold");
        font.setBold(true);
        QPixmap iconshop(":/img/res/lord.png");
        _shop->setIcon(iconshop);
        _shop->setFont(font);
        _shop->setStyleSheet("color:#2b2b2b");
        _shop->setCursor(Qt::PointingHandCursor);
        _shop->setText("商城");
        _shop->installEventFilter(this);
}

void settings::init()
{
    _label1=new QLabel(this);
    _label2=new QLabel(this);
    _scores=new QLabel(this);
    _label1->setText("分辨率");
    _label2->setText("难度");
    _scores->setText("积分： "+QString::number(universal::scores));
    _label1->setStyleSheet(QString::fromUtf8("font: 24pt \"Sans Serif\";"));
    _label2->setStyleSheet(QString::fromUtf8("font: 24pt \"Sans Serif\";"));
    _scores->setStyleSheet(QString::fromUtf8("font: 18pt \"OCR A Extended\";"));

    {
        _benchmark=new QPushButton(this);
        QFont font;
        font.setPointSize(20);
        font.setFamily("Arial Rounded MT Bold");
        font.setBold(true);
        _benchmark->setFont(font);
        _benchmark->setStyleSheet("color:#2b2b2b");
        _benchmark->setCursor(Qt::PointingHandCursor);
        _benchmark->setText("性能测试");
        connect(_benchmark,SIGNAL(pressed()),this,SLOT(benchmark()));
    }
    {
        _reset=new QPushButton(this);
        QFont font;
        font.setPointSize(12);
        font.setFamily("Arial Rounded MT Bold");
        font.setBold(true);
        _reset->setFont(font);
        _reset->setStyleSheet("color:#2b2b2b");
        _reset->setCursor(Qt::PointingHandCursor);
        _reset->setText("RESET");
        connect(_reset,SIGNAL(pressed()),this,SLOT(reset()));
    }
}

void settings::themes()
{
    _btntheme = new QButtonGroup(this);
    _btntheme->addButton(radioButton31, 0);
    _btntheme->addButton(radioButton32, 1);
    _btntheme->addButton(radioButton33, 2);
    _btntheme->addButton(radioButton34, 3);
    if(universal::theme==":/img/res/card2.png")
    radioButton31->setChecked(true);
    if(universal::theme==":/img/res/card3.png")
    radioButton32->setChecked(true);
    if(universal::theme==":/img/res/card4.png")
    radioButton33->setChecked(true);
    if(universal::theme==":/img/res/card5.png")
    radioButton34->setChecked(true);
}

void settings::eeclick(int count)
{
    if(count>10)
    {
        checkbox1->show();
        checkbox2->show();
        checkbox3->show();
        radioButton33->show();
        radioButton34->show();
        _shop->show();
        QMessageBox::warning(this,"警告","进入高级模式","确定");
        universal::eecount=-1;
    }
}

void settings::onRadioClickpix()
{
            switch(_btnpix->checkedId())
               {
               case 0:
                   qDebug() << "111";
                   settingssize(1);
                   update();
                   universal::setpix=1;
                   break;
               case 1:
                   qDebug() << "222";
                   settingssize(1.2);
                   universal::setpix=1.2;
                   update();
                   break;
               case 2:
                   qDebug() << "333";
                   settingssize(1.5);
                   universal::setpix=1.5;
                   update();
                   break;
               }
}

void settings::onRadioClickpic()
{
      switch(_btnpic->checkedId())
       {
       case 0:
           qDebug() << "low";
           universal::diff=0;
           break;
       case 1:
           qDebug() << "mid";
           universal::diff=1;
           break;
       case 2:    
           if(universal::eecount>=0)
           {universal::eecount++;
               qDebug()<<"敬请期待";
               eeclick(universal::eecount);}
           if(universal::eecount<0)
           {
               qDebug() << "high";
               universal::diff=2;
           }
           break;
      }
      if(universal::diff==0)
      radioButton21->setChecked(true);
      if(universal::diff==1)
      radioButton22->setChecked(true);
      if(universal::diff==2)
      radioButton23->setChecked(true);
}

void settings::onRadioThemeClicked()
{
    switch(_btntheme->checkedId())
     {
    case 0:
        qDebug() << "默认";
    {
        universal::theme=":/img/res/card2.png";
        universal::playera=":/img/res/farmer.png";
        universal::playerd=":/img/res/lord.png";
        universal::bgp=":/img/res/bk.png";
        universal::mclock=":/img/res/bk.png";
    }
        break;
    case 1:
        qDebug() << "东大";
    {
        universal::theme=":/img/res/card3.png";
        universal::playera=":/img/res/farmer.png";
        universal::playerd=":/img/res/lord.png";
        universal::mclock=":/img/res/clock.png";
        if(universal::eecount<0)
        {
        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("SSAA"),
                                       QString(tr("警告：正在选用东大主题 是否开启SSAA？")),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            universal::bgp=":/img/res/bkseu.jpg";
            qDebug()<<"NO SSAA";
        }
        else if (button == QMessageBox::Yes) {
            QMessageBox::StandardButton button;
            button = QMessageBox::question(this, tr("SSAA"),
                                           QString(tr("警告：正在选用东大主题 是否开启16倍SSAA？")),
                                           QMessageBox::Yes | QMessageBox::No);

            if (button == QMessageBox::No) {
                universal::bgp=":/img/res/ssaa4.jpg";
                qDebug()<<"SSAA4";
            }
            else if (button == QMessageBox::Yes) {
                universal::bgp=":/img/res/ssaa16.jpg";
                qDebug()<<"SSAA!!!";
            }
        }
        }
        else
            universal::bgp=":/img/res/bkseu.jpg";
    }
        break;
    case 2:
        qDebug() << "白色相簿";
    {
        universal::theme=":/img/res/card4.png";
        universal::playera="";
        universal::playerd=":/img/res/lordwa.png";
        universal::bgp=":/img/res/bkwa.jpg";
        universal::mclock=":/img/res/clock.png";
    }
        break;
    case 3:
        qDebug() << "舰队Collection";
    {
        universal::theme=":/img/res/card5.png";
        universal::playera=":/img/res/farmerc.png";
        universal::playerd="";
        universal::bgp=":/img/res/bkc.jpg";
        universal::mclock=":/img/res/timec.gif";
    }
        break;
    }
    if(universal::theme==":/img/res/card2.png")
    radioButton31->setChecked(true);
    if(universal::theme==":/img/res/card3.png")
    radioButton32->setChecked(true);
    if(universal::theme==":/img/res/card4.png")
    radioButton33->setChecked(true);
    if(universal::theme==":/img/res/card5.png")
    radioButton34->setChecked(true);
}

void settings::onCheck1()
{
    if(checkbox1->isChecked())
    {
        qDebug()<<"Debug on";
        universal::debugmode=1;
    }

    if(!checkbox1->isChecked())
    {
        qDebug()<<"Debug off";
        universal::debugmode=0;
    }
}

void settings::onCheck2()
{
    if(checkbox2->isChecked())
    {
        qDebug()<<"Full Screen";
        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect screenrect = desktopWidget->screenGeometry();
        qDebug()<<screenrect.width();
        universal::setpix=screenrect.width()/800.0;
        //qCritical("screenrect.h==%s\n",qPrintable(QString::number(screenrect.height())));
        universal::windowed=0;
    }
    else
    {
        qDebug()<<"get over";
        universal::windowed=1;
        universal::setpix=1.5;
    }
}

void settings::onCheck3()
{
    if(checkbox3->isChecked())
    {
        qDebug()<<"SKILLs ON";
        universal::_skills=1;
    }
    else
    {
        qDebug()<<"SKILLs OFF";
        universal::_skills=0;
    }
}

void settings::settingssize(double m)
{
    this->setFixedSize(800*m,600*m);

    radioButton11->setGeometry(20*m,100*m,160,30);
    radioButton12->setGeometry(20*m,180*m,160,30);
    radioButton13->setGeometry(20*m,260*m,160,30);
    radioButton21->setGeometry(300*m,100*m,160,30);
    radioButton22->setGeometry(300*m,180*m,160,30);
    radioButton23->setGeometry(300*m,260*m,160,30);
    radioButton31->setGeometry(600*m,260*m,160,30);
    radioButton32->setGeometry(600*m,340*m,160,30);
    radioButton33->setGeometry(600*m,420*m,160,30);
    radioButton34->setGeometry(600*m,500*m,160,30);

    _label1->setGeometry(20*m,10*m,160,80);
    _label2->setGeometry(300*m,10*m,160,80);
    _scores->setGeometry(20*m,540*m,160,80);
    checkbox1->setGeometry(600*m,10*m,100,20);
    checkbox2->setGeometry(600*m,60*m,100,20);
    checkbox3->setGeometry(600*m,110*m,100,20);

    _shop->setGeometry(600*m,540*m,120,60);
    _benchmark->move(20*m,360*m);
    _reset->move(20*m,420*m);
}

void settings::benchmark()
{
    qDebug()<<"benchmark";
    QMessageBox::StandardButton rb =QMessageBox::question(NULL,"警告","即将开始进行 <font color='red'>性能测试</font>", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    {
        if (rb==QMessageBox::Yes)
        {
            QTime time;
            time.start();
            uint m=100000;
            fstream f;
            int max=5;
            while(max>2)//cpu部分进行测试
            {

                QVector < uint > pr(8192);
                uint prpoi = 0, poi, subpoi, tmp;

                pr[prpoi] = 2;
                prpoi++;

                for (poi = 3; poi <= m; poi++)
                {
                    if (prpoi == pr.size())
                    {
                        pr.resize(prpoi + 8192);
                    }
                    subpoi = 0;
                    tmp = poi / 2;
                    while (pr[subpoi] < tmp)
                    {
                        if (poi % pr[subpoi] == 0)
                            break;
                        subpoi++;
                    }
                    if (pr[subpoi] >= tmp)
                    {
                        f << poi << endl;
                        pr[prpoi++] = poi;
                    }
                }
                max--;
            }
            while(max>0)//RAM测试部分
            {
                char emptystr[] = " ";
                    bool *is = new bool[m + 1];
                    if (is == NULL)
                        qDebug()<<"RAM ERROR";

                    uint poi, fpoi, n, ctr;

                    // initlize the array:0 and 1 isn't prime
                    for (poi = 0; poi < m; poi++)
                        is[poi] = true;
                    is[0] = false;
                    is[1] = false;

                    // scan start from0
                    for (poi = 0; poi < m; poi++)
                    {
                        // on found a prime
                        if (is[poi])
                        {

                            n = m / poi;
                            fpoi = (poi << 1);
                            f << poi << endl;

                            // int n*poi isn't prime
                            for (ctr = 1; ctr < n; ctr++)
                            {
                                is[fpoi] = false;
                                fpoi += poi;
                            }
                        }
                    }
                    max--;
            }
            double tm=time.elapsed()/1000.0;
            qDebug()<<tm;
            tm=(1/tm)*10000;
            QString text = "测试结果为"+QString::number(tm);
            QMessageBox::about(this,"测试结果",text+"<font color='red'>分</font>");
            if(universal::debugmode)
            {
                universal::scores+=18;
                _scores->setText("积分： "+QString::number(universal::scores));
            }
        }
        else
        {
            qDebug()<<"cancaled";
        }
    }

}

void settings::reset()
{
    qDebug()<<"will reset";
    QMessageBox::StandardButton rb =QMessageBox::question(NULL,"警告","即将重置 <font color='red'>将丢失所有用户数据!!!</font>", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    {
        if (rb==QMessageBox::Yes)
        {
            qDebug()<<"reset!";
            QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE");
            db.setDatabaseName("savegame.db");
            QSqlQuery query(db);
            db.open();
            query.prepare("update save set mission=1, s1=0, s2=0, s3=0, score=0, streak=0 where uid=1;");
            query.exec();
            db.close();
            universal::skill1=0;
            universal::skill2=0;
            universal::skill3=0;
            universal::scores=0;
            universal::streak=0;
            close();
        }
        else
        {
            qDebug()<<"canceled";
        }
    }
}

void settings::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/image/res/settings.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

bool settings::eventFilter(QObject *obj, QEvent *event)
{
    {
        if(obj==_shop && event->type()==QEvent::MouseButtonPress)
        {
            shop * newPage=new shop;
            newPage->setWindowTitle("商城");
            newPage->exec();
            return true;
        }

}
    return QWidget::eventFilter(obj,event);
}
