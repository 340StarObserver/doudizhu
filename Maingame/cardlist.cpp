#include "cardlist.h"
#include "ui_cardlist.h"

CardList::CardList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CardList)
{
    originWindow();     //初始化窗体属性
    originLabels();     //初始化卡牌标签属性
    ui->setupUi(this);  //渲染
}

CardList::~CardList()
{
    delete ui;
}

//根据1-54的数字,从大图中 截取 该数字对应的那张牌的小矩形
QPixmap CardList::pictureShot(int value)
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

//初始化窗体的属性
void CardList::originWindow()
{
    setFixedHeight(105);
}

//初始化卡牌标签的属性
/*
 * 一开始就创建好所有的标签,
 * 之后如果需要添加某张牌到该区域内,
 * 只要更改标签内部的图片并显示它即可,
 * 这样就 不需要 重新渲染界面
*/
void CardList::originLabels()
{
    _num=0;
    for(int i=0;i<14;i++)
    {
        _labels[i]=new QLabel(this);
        _labels[i]->setGeometry(14*i,0,_WCard,_HCard);
        _labels[i]->hide();
    }
}

//向区域内增加一张牌
/*
 * 根据当前区域内部卡牌内部的张数,
 * 设置对应位置的标签的图片并显示它
*/
void CardList::addOne(int value)
{
    if(_num>=14)
        return;
    _labels[_num]->setPixmap(pictureShot(value));
    _labels[_num]->setVisible(true);
    _num++;
    setFixedWidth(14*_num+64);
}

//清理区域内所有的牌
//只要隐藏所有卡牌标签并将计数器清零即可
void CardList::clearAll()
{
    for(int i=0;i<14;i++)
        _labels[i]->hide();
    _num=0;
}

//更换区域内所有牌
/*
 * 先清理区域内所有牌
 * 再依次一张张添加进去即可
*/
void CardList::update(const vector<int> &values)
{
    clearAll();
    int N=static_cast<int>(values.size());
    for(int i=0;i<N;i++)
        addOne(values[i]);
}
