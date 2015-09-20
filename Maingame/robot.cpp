#include "robot.h"
#include <QThread>
#include <QTime>
#include <QCoreApplication>

Robot::Robot(QWidget* parent):Player(parent)
{}

void Robot::beginPlayingHand()
{
    Method method(this,m_cards);
    QList<card> cards = method.MakeDecision();   //智能获取要出的牌

    QTime dieTime = QTime::currentTime().addMSecs(1000);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    playHand(cards);            //出牌
}

void Robot::beginCallingLord()
{
    int weight = 0;

    Method st(this, m_cards);
    weight += st.GetRangeCards(Card_SJ, Card_BJ).size() * 6;
    int count=0;
    for(int i=0;i<m_cards.size();i++)
        if(m_cards[i].point==Card_2)
            count++;

    weight += count * 3;

    QList<QList<card> > optSeq = st.PickOptimalSeqSingles();
    weight += optSeq.size() * 5;

    QList<card> left = m_cards;
    for(int i=0;i<optSeq.size();i++)
        for(int j=0;j<optSeq[i].size();j++)
            left.removeOne(optSeq[i][j]);

    //	left.Remove(optSeq);
    Method stLeft(this, left);

    QList<QList<card> > bombs = stLeft.FindCardsByCount(4);
    weight += bombs.size() * 5;

    QList<QList<card> > triples = stLeft.FindCardsByCount(3);
    weight += triples.size() * 4;

    QList<QList<card> > pairs = stLeft.FindCardsByCount(2);
    weight += pairs.size() * 1;

    if (weight >= 22)
    {
        callingLord(3);
    }
    else if (weight < 22 && weight >= 18)
    {
        callingLord(2);
    }
    else if (weight > 18 && weight >= 10)
    {
        callingLord(1);
    }
    else
    {
        callingLord(0);
    }
}
