#include "card.h"

//构造
Card::Card(const Huase &huase, const Point &point)
{
    setHuase(huase);
    setPoint(point);
}

//获取花色
Huase Card::getHuase()const
{
    return _huase;
}

//获取点数
Point Card::getPoint()const
{
    return _point;
}

//设置花色
void Card::setHuase(const Huase &huase)
{
    _huase=huase;
}

//设置点数
void Card::setPoint(const Point &point)
{
    _point=point;
}

//牌大小比较,点数小的牌就小
bool Card::operator < (const Card& card)const
{
    return _point<card._point;
}

//牌大小比较,点数相等的牌就相等
bool Card::operator == (const Card& card)const
{
    return _point==card._point;
}

//牌大小比较,点数大的牌就大
bool Card::operator > (const Card& card)const
{
    return _point>card._point;
}

//牌大小比较,点数不同的牌就算不一样大
bool Card::operator != (const Card& card)const
{
    return _point!=card._point;
}

//牌全等,花色和点数都相同
bool Card::totalEqual(const Card &card)const
{
    return _point==card._point&&_huase==card._huase;
}

//form a card based on a value between 1 and 54
//按照 ♠A,♥A,♣A,♦A,♠2...的顺序
Card Card::form(int value)
{
    int tmpH=(value-1)%4;
    int tmpP=(value-1)/4;
    Huase huase;
    switch(tmpH){
    case 0:{huase=Huase::HeiTao;break;}
    case 1:{huase=Huase::HongTao;break;}
    case 2:{huase=Huase::MeiHua;break;}
    case 3:{huase=Huase::FangPian;break;}
    }
    Point point;
    switch(tmpP){
    case 0:{point=Point::Card_A;break;}
    case 1:{point=Point::Card_2;break;}
    case 2:{point=Point::Card_3;break;}
    case 3:{point=Point::Card_4;break;}
    case 4:{point=Point::Card_5;break;}
    case 5:{point=Point::Card_6;break;}
    case 6:{point=Point::Card_7;break;}
    case 7:{point=Point::Card_8;break;}
    case 8:{point=Point::Card_9;break;}
    case 9:{point=Point::Card_10;break;}
    case 10:{point=Point::Card_J;break;}
    case 11:{point=Point::Card_Q;break;}
    case 12:{point=Point::Card_K;break;}
    case 13:{point=(value==53?Point::Card_SK:Point::Card_BK);break;}
    }
    return Card(huase,point);
}

//toString
//黑桃用S表示,红桃用H表示,梅花用C表示,方片用D表示
//小王大王没有花色,用S_Ghost,B_Ghost表示
//此函数是为了在服务端的类似于命令行的反馈区域看到每个玩家的起始牌面和出牌信息
QString Card::toString()const
{
    QString str="";
    switch(_huase){
    case Huase::HeiTao:{str.append("S");break;}
    case Huase::HongTao:{str.append("H");break;}
    case Huase::MeiHua:{str.append("C");break;}
    case Huase::FangPian:{str.append("D");break;}
    }
    switch(_point){
    case Point::Card_A:{str.append("A");break;}
    case Point::Card_2:{str.append("2");break;}
    case Point::Card_3:{str.append("3");break;}
    case Point::Card_4:{str.append("4");break;}
    case Point::Card_5:{str.append("5");break;}
    case Point::Card_6:{str.append("6");break;}
    case Point::Card_7:{str.append("7");break;}
    case Point::Card_8:{str.append("8");break;}
    case Point::Card_9:{str.append("9");break;}
    case Point::Card_10:{str.append("10");break;}
    case Point::Card_J:{str.append("J");break;}
    case Point::Card_Q:{str.append("Q");break;}
    case Point::Card_K:{str.append("K");break;}
    case Point::Card_SK:{str="S_Ghost";break;}
    case Point::Card_BK:{str="B_Ghost";break;}
    }
    return str;
}
