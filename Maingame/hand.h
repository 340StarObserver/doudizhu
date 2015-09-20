#ifndef HAND_H
#define HAND_H

#include"card.h"
#include<QList>

//用以判断牌型
//用以判断某个牌组 能否打过 另一个牌组
class Hand
{
public:
    //默认构造
    Hand();
    //转换构造
    Hand(QList<card> cards);
    //根据牌型,代表点数,顺子个数进行构造
    Hand(HandType type, CardPoint base, int extra);
    bool Defeat(Hand &hand);                    //判断牌组能否打败另一个牌组
    void DefineHandType();                      //判断牌型
    void InitByCardsList(QList<card> cardList); //根据牌组初始化三个容器
    HandType getHandType();      //获取牌型
    int getBasePoint();          //获取代表点数
    int getExtra();              //获取顺子个数
private:
    HandType m_handtype;         //牌型
    int m_basepoint;             //代表点数
    int m_extra;                 //顺子中的牌数
    QList<CardPoint> m_oneCard;  //单牌容器
    QList<CardPoint> m_twoCard;  //对子容器
    QList<CardPoint> m_threeCard;//三张容器
    QList<CardPoint> m_fourCard; //炸弹容器
};

#endif // HAND_H
