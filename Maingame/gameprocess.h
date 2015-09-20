#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <QWidget>
#include <QTime>
#include <QMap>
#include "robot.h"
#include "userplayer.h"

class GameProcess : public QWidget
{
    Q_OBJECT
public:
    enum GameStatus
    {
        PickingCard,
        CallingLord,
        PlayingHand,
    };

    GameProcess(QWidget *parent = 0);

    void getOneCard(Player* player);                 //添加一张牌到当前玩家的牌组中
    void setCurrentPlayer(Player* player);
    Player* getLeftPlayer();
    Player* getRightPlayer();
    Player* getDownPlayer();

    Player* getCurrentPlayer();
    Player* getNextPlayer();
    Player* getPrevPlayer();

    Player* getHitPlayer();
    void setHitPlayer(Player* player);
    QList<card> getHitCards();

    QList<card> getAllCards();
    void beginPlayHand();
    void InitCards();       //初始化m_allCards
    void Restart();         //重新开始时用的初始化

    GameStatus m_gamestatus;
    QMap<Player*,int> BetList;      //记录玩家和对应的叫分

    int betLeftOrder;
    int betDownOrder;
    int betRightOrder;

signals:
    /*告知MainInterface的信号*/
    void TellGameProcess(GameProcess::GameStatus);
    void TellPlayerStatus(Player* player,Player::PlayerStatus status);
    void TellPlayerPlayHand(Player* player,QList<card> cards);
    void TellPlayerCallLord(Player* player,int bet);

    /*告知Player的信号*/
    void TellHitPlayer(Player* player,QList<card> cards);

public slots:
    void PlayerCallLord(Player* player,int bet);
    void PlayerPlayHand(Player* player,QList<card> cards);

private:
    Robot* m_LeftPlayer;
    Robot* m_RightPlayer;
    UserPlayer* m_DownPlayer;

    Player* m_currentPlayer;        //当前玩家

    QList<card> m_allCards;         //所有牌的card
    Player* m_hitPlayer;            //当前最大牌的玩家
    QList<card> m_hitCards;         //当前最大牌

};

#endif // GAMEPROCESS_H
