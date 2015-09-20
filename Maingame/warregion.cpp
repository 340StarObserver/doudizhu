#include "warregion.h"
#include "ui_warregion.h"
#include <QFont>
#include <QString>

WarRegion::WarRegion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WarRegion)
{
    originWindow();        //初始化窗体
    originDominateLabel(); //初始化称霸者的编号标签
    originCardsRegion();   //初始化称霸的牌组区
    ui->setupUi(this);
}

WarRegion::~WarRegion()
{
    delete ui;
}

//初始化窗体
void WarRegion::originWindow()
{
    setFixedSize(260,250);
}

//初始化称霸者的编号标签
void WarRegion::originDominateLabel()
{
    _dominateLabel=new QLabel(this);
    _dominateLabel->setGeometry(0,0,260,40);
    _dominateLabel->setAlignment(Qt::AlignCenter);
    _dominateLabel->setStyleSheet("color:#e8e8e8");
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    _dominateLabel->setFont(font);
}

//初始化称霸的牌组区
/*
 * 1. 创建20个标签,并且全部隐藏
 *    //这样之后添加牌的时候只要修改标签的图像并显示就行了,不用重新渲染
 * 2. 计数器清零
*/
void WarRegion::originCardsRegion()
{
    for(int i=0;i<20;i++)
    {
        _cards[i]=new QLabel(this);
        int localX=(i%10)*20;
        int localY=(i/10)*_HCard+40;
        _cards[i]->setGeometry(localX,localY,_WCard,_HCard);
        _cards[i]->hide();
    }
    _num=0;
}

//设置称霸者的编号
void WarRegion::setDominateID(int id)
{
    if(id == -1)
        _dominateLabel->setText("");
    else
        _dominateLabel->setText(QString("霸主:玩家").append(QString::number(id)));
}

//根据1-54的数字截取对应的牌
QPixmap WarRegion::pictureShot(int value)
{
    //计算小图左上角 在大图中的位置(x,y)
    int x,y;
    if(value == 53){
        x=0;
        y=4*_HCard;
    }
    else if(value == 54){
        x=_WCard;
        y=4*_HCard;
    }
    else{
        x=((value-1)/4)*_WCard;
        y=((value-1)%4)*_HCard;
    }
    //截图小图
    QPixmap pics(":/image/res/card.png");
    QPixmap cardpic=pics.copy(x,y,_WCard,_HCard);
    return cardpic;
}

//向称霸区添加一张牌
//参数∈[1,54],1~4分别是♠A,♥A,♣A,♦A(依次类推),小王是53,大王是54
/*
 * 1. 计算小图左上角 在大图中的位置(x,y)
 * 2. 截取小图
 * 3. 设当前已有N张牌,设置_cards[N]的图像为截取到的小图
 * 4. 显示_cards[N]
 * 5. 牌数加一
*/
void WarRegion::addOneCard(int card)
{
    if(_num>=20)
        return;
    _cards[_num]->setPixmap(pictureShot(card));
    _cards[_num]->setVisible(true);
    _num++;
}

//清空称霸区的牌
/*
 * 隐藏20个标签
 * 计数器清零
*/
void WarRegion::clearCards()
{
    for(int i=0;i<20;i++)
        _cards[i]->hide();
    _num=0;
}

//更新称霸区
void WarRegion::update(int dominateID, const vector<int> &list)
{
    setDominateID(dominateID);
    clearCards();
    int N=static_cast<int>(list.size());
    for(int i=0;i<N;i++)
        addOneCard(list[i]);
}
