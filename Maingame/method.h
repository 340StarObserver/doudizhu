#ifndef METHOD_H
#define METHOD_H

#include <QWidget>
#include "wanjia.h"
#include "hand.h"
#include <QMap>

class Method
{
public:
    Method(Player* player, QList<card> cards);
    ~Method();

    int CountOfPoint(QList<card> cards, CardPoint point);
    QList<card> MakeDecision();

    QList<card> FindSamePointCards(CardPoint point, int count);// 找出count张点数为point的牌
    QList<QList<card> > FindCardsByCount(int count);// 找出所有点数相同张数为count的牌组
    QList<card> GetRangeCards(CardPoint beginPoint, CardPoint endPoint);// 找出所有在范围内的牌
    QList<card> GetFirstSeqSingleRange();               // 找到能构成顺子的最小起点牌的牌组

    // 在cards中挑出一个顺子，seqInherited记录逐步拨除顺子，allSeqRecord记录所能分离出的顺子
    void PickSeqSingles(QList<QList<QList<card> > >& allSeqRecord, const QList<QList<card> >& seqInherited, QList<card> cards);
    QList<QList<card> > PickOptimalSeqSingles();

    // 按牌型找到若干手牌，beat为true表示要大过hand, beat为false表示不要求大过hand
    QList<QList<card> >  FindHand(Hand hand, bool beat);

    QList<card> PlayFirst();// 主动出牌
    QList<card> PlayBeatHand(Hand hand);// 大过指定牌型
    bool WhetherToBeat(QList<card> &myCards);// 能大过时，判断是打还是放行

protected:
    Player* m_player;
    QList<card> m_cards;
};

#endif // METHOD_H
