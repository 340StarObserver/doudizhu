#include "missioninfo.h"
#include "ui_missioninfo.h"
#include "universal.h"

missioninfo::missioninfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::missioninfo)
{
    setFixedSize(800*universal::setpix,600*universal::setpix);
    init();
    ui->setupUi(this);
    connect(_bt1,SIGNAL(clicked()),this,SLOT(onbt1clicked()));
}

missioninfo::~missioninfo()
{
    delete ui;
}

void missioninfo::init()
{
    _bt1=new QPushButton(this);
    QFont font;
    font.setPointSize(10);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _bt1->setGeometry(600*universal::setpix,550*universal::setpix,100,50);
    _bt1->setFont(font);
    _bt1->setStyleSheet("color:#2b2b2b");
    _bt1->setCursor(Qt::PointingHandCursor);
    _bt1->setText("开始");
}

void missioninfo::paintEvent(QPaintEvent *event)
{
    QPixmap bk(/*":/img/res/bk.png"*/universal::bgp);
    QPainter painter(this);
    painter.drawPixmap(this->rect(),bk);
}

void missioninfo::onbt1clicked()
{
    close();
}
