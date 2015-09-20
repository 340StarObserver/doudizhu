#ifndef WANJIA_H
#define WANJIA_H

#include <QWidget>
#include <QSet>
#include "card.h"
#include <QLabel>

inline bool operator == (const card c1,const card c2)
{
    return (c1.point==c2.point)&&(c1.suit==c2.suit);
}

inline uint qHash(const card& c)
{
    return c.point * 100 + c.suit;
}

inline bool operator <(const card c1,const card c2)
{
    if(c1.point==c2.point)
        return c1.suit<c2.suit;
    else
        return c1.point<c2.point;
}


class Player : public QWidget
{
    Q_OBJECT

public:
    enum Role
    {
        Farmer,
        Lord
    };

    enum PlayerStatus
    {
       waitingCallingLord,
       waitingPlayingHand,
       winning,
    };

    Player(QWidget *parent = 0);
    Player(int id=0,QString name="Unknown", int score=0, int level=0);

    void setName(QString name);
    QString getName();
    void setScore(int s);
    int getScore();
    void setLevel(int l);
    int getLevel();
    void setId(int id);
    int getId();

    void setBet(int bet);
    int getBet();

    void setRole(Role role);
    Role getRole();

    void sortCard();            //牌排序
    void addCard(card c);       //添加牌
    void removeCard(card c);    //清除牌
    void removeCard(QList<card> &c);

    void callingLord(int bet);
    void playHand(QList<card> cards);
    QList<card>& getCards();
    QList<int>& getCardsIntList();
    QList<card>& getCardsToPlay();

    void addCardToPlay(QList<card> cards);
    Player* getHitPlayer();
    QList<card> getHitCards();
    Player* getNextPlayer();
    void setNextPlayer(Player* player);

    virtual void beginPlayingHand();
    virtual void beginCallingLord();

    QLabel* passLabel;
    QLabel* betLabel;
    QLabel* roleLabel;

    int m_betOrder;
signals:
    void TellCallingLord(Player* player,int bet);
    void TellPlayingHand(Player* player,QList<card> cards);

public slots:
    void setHitPlayer(Player* player,QList<card> cards);

protected:
    int m_id;
    QString m_name;
    int m_score;
    int m_level;
    Role m_role;

    Player* m_nextPlayer;
    Player* m_hitPlayer;
    QList<card> m_hitCards;

    QList<card> m_cards;             //牌组
    QList<int> m_CardsIntList;       //整数数组

    QList<card> m_cardsToPlay;       //要打出去的牌
    QList<card> m_lastPlayedCards;   //上次出牌
    PlayerStatus m_playerStatus;     //玩家状态

};

#endif // WANJIA_H
