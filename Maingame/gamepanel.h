#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QSound>
#include "cardpicture.h"
#include "gameprocess.h"
#include "hand.h"

namespace Ui {
class GamePanel;
}

class GamePanel : public QWidget
{
    Q_OBJECT

public:
    GamePanel(QWidget *parent = 0);
    ~GamePanel();

    void Init();
    void InitCardsMap();//初始化m_Cards


    void CutCardPic(int x,int y,card c);
    void UpdateCards(Player* player);
    void PickingCardsAnimation(Player* player);
    void PlayerStartCallingLord();
    void PlayerStartPlayingHand();
    void paintEvent(QPaintEvent *);

    void ReStart();

public slots:
    void NoOneCallLord();       //没人叫地主
    void StartProcess(GameProcess::GameStatus status);
    void PickingCards();
    void CardSelected();
    void PlayingHand(Player* player, QList<card> cards);
    void CallingLord(Player* player,int bet);
    void SetPlayerStatus(Player* player,Player::PlayerStatus status);

    /*按钮槽*/
    void on_start_clicked(bool state);
    void on_bet0_clicked(bool state);
    void on_bet1_clicked(bool state);
    void on_bet2_clicked(bool state);
    void on_bet3_clicked(bool state);
    void on_playhand_clicked(bool state);
    void on_pass_clicked(bool state);
    void on_continue_clicked(bool state);

private:
    Ui::GamePanel *ui;
    QMap<card,CardPicture*> m_Cards;
    QSet<CardPicture*> m_Selected;
    QList<CardPicture*> m_restThreeCards;    //剩余三张牌

    QPixmap m_cardBackPic;
    QPixmap m_cardBasePic;
    QPixmap m_AllCardsPic;

    QLabel* m_clock;
    CardPicture* m_movingcard;
    CardPicture* m_basecard;

    QPoint m_basecardPos;
    int MoveDistance;                //移动的距离
    QTimer* m_pickingCardTimer;
    GameProcess* m_gameprocess;

    /*按钮*/
    QPushButton* m_start;
    QPushButton* m_bet0;
    QPushButton* m_bet1;
    QPushButton* m_bet2;
    QPushButton* m_bet3;
    QPushButton* m_playhand;
    QPushButton* m_pass;
    QPushButton* m_continue;

    /*音效*/
    QSound* shuffleCardsMusic;
    QSound* bkMusic;
    QSound* winMusic;
    QSound* loseMusic;
    QSound* noCallMusic;
    QSound* callLordMusic;

    QSound* handtype;

};

#endif // GAMEPANEL_H
