#include "infoitem.h"
#include "ui_infoitem.h"
#include <QFont>
#include <QString>
#include <QPixmap>

InfoItem::InfoItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoItem)
{
    originWindow();            //初始化窗体属性
    originIdLabel();           //初始化编号标签属性
    originIdentifyLabel();     //初始化身份标签属性
    originRestCardNumLabel();  //初始化剩余手牌数标签
    originHeadLabel();         //初始化头像标签
    ui->setupUi(this);
}

InfoItem::~InfoItem()
{
    delete ui;
}

//初始化窗体属性
void InfoItem::originWindow()
{
    setFixedSize(120,180);
    setStyleSheet("color:#ff8833");
}

//初始化编号标签属性
void InfoItem::originIdLabel()
{
    _idLabel=new QLabel(this);
    _idLabel->setGeometry(0,0,120,30);
    _idLabel->setAlignment(Qt::AlignCenter);
    QFont font; font.setPointSize(15); font.setBold(true);
    _idLabel->setFont(font);
    _idLabel->setText("");
}

//初始化身份标签属性
void InfoItem::originIdentifyLabel()
{
    _identifyLabel=new QLabel(this);
    _identifyLabel->setGeometry(0,150,60,30);
    _identifyLabel->setAlignment(Qt::AlignCenter);
    QFont font; font.setPointSize(15); font.setBold(true);
    _identifyLabel->setFont(font);
    _identifyLabel->setText("");
}

//初始化剩余手牌数标签
void InfoItem::originRestCardNumLabel()
{
    _restCardNumLabel=new QLabel(this);
    _restCardNumLabel->setGeometry(60,150,60,30);
    _restCardNumLabel->setAlignment(Qt::AlignCenter);
    QFont font; font.setPointSize(15); font.setBold(true);
    _restCardNumLabel->setFont(font);
    _restCardNumLabel->setText("");
}

//初始化头像标签
void InfoItem::originHeadLabel()
{
    _headLabel=new QLabel(this);
    _headLabel->setGeometry(0,30,120,120);
    _headLabel->setAlignment(Qt::AlignCenter);
    QFont font; font.setPointSize(60); font.setBold(true);
    _headLabel->setFont(font);
    _headLabel->setText("?");
}

//获取编号
int InfoItem::getID()const
{
    return _ID;
}

//获取身份
bool InfoItem::getIdentify()const
{
    return _identify;
}

//获取剩余手牌数量
int InfoItem::getRestCardNum()const
{
    return _restCardNum;
}

//获取头像代号
int InfoItem::getHead()const
{
    return _head;
}

//设置编号
//设置为-1则会还原为初始状态
void InfoItem::setID(int ID)
{
    _ID=ID;
    if(_ID != -1)
        _idLabel->setText(QString("玩家").append(QString::number(_ID)));
    else
        _idLabel->setText("");
}

//设置身份
void InfoItem::setIdentify(bool isDizhu)
{
    _identify=isDizhu;
    _identifyLabel->setText(_identify?"地主":"农民");
}

//设置剩余手牌数量
/*
 * 更新剩余手牌数量
 * 更新对应的标签
 * 若剩余不足5张,则让标签的字体变大变红,以此醒目
*/
void InfoItem::setRestCardNum(int num)
{
    _restCardNum=num;
    _restCardNumLabel->setText(QString::number(_restCardNum));
    if(_restCardNum < 5)
    {
        QFont font;
        font.setPointSize(25);
        _restCardNumLabel->setFont(font);
        _restCardNumLabel->setStyleSheet("color:#880000");
    }
}

//设置头像代号
/*
 * 因为注册的时候只提供了三个头像作为选择,所以头像代号∈[0,2]
 * 若参数填-1,则设置头像标签为初始状态
*/
void InfoItem::setHead(int head)
{
    _head=head;
    switch(_head)
    {
    case -1:{ _headLabel->setPixmap(QPixmap()); _headLabel->setText("?"); break; }
    case 0:{ _headLabel->setPixmap(QPixmap(":/image/res/head1.png")); break; }
    case 1:{ _headLabel->setPixmap(QPixmap(":/image/res/head2.png")); break; }
    case 2:{ _headLabel->setPixmap(QPixmap(":/image/res/head3.png")); break; }
    }
}

//还原标签为默认状态
/*
 * ( 当玩家掉线时,调用此函数让那个玩家的信息栏还原为初始状态,以此让其他用户知道他掉了 )
 * 将 编号标签,头像标签,身份标签,剩余手牌数标签 还原为初始状态
*/
void InfoItem::restore()
{
    QFont font; font.setPointSize(15); font.setBold(true);
    _idLabel->setText("");
    _identifyLabel->setText("");
    _restCardNumLabel->setText("");
    _restCardNumLabel->setFont(font);
    _restCardNumLabel->setStyleSheet("color:#ff8833");
    _headLabel->setPixmap(QPixmap());
    _headLabel->setText("?");
    _headLabel->setFont(font);
    _headLabel->setStyleSheet("color:#ff8833");
}
