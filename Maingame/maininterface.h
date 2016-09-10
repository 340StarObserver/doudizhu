#ifndef MAININTERFACE_H
#define MAININTERFACE_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QSound>
#include <QCloseEvent>
#include "cardpicture.h"
#include "gameprocess.h"
#include "hand.h"
namespace Ui {
class MainInterface;
}

class MainInterface : public QWidget
{
    Q_OBJECT

public:
    MainInterface(QWidget *parent = 0);
    ~MainInterface();
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
    void on_start_clicked();
    void on_bet0_clicked();
    void on_bet1_clicked();
    void on_bet2_clicked();
    void on_bet3_clicked();


    void on_playhand_clicked();
    void on_pass_clicked();
    void on_continue_clicked();
    void on_tip_clicked();

    void on_skill1_clicked();
    void on_skill2_clicked();
    void on_skill3_clicked();

    void timeDisplay();         //倒数时间显示
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainInterface *ui;
    QLabel * _musicLabel;        //音乐开关标签

    QMap<card,CardPicture*> m_Cards;
    QSet<CardPicture*> m_Selected;
    QList<CardPicture*> m_restThreeCards;    //剩余三张牌

    QPixmap m_cardBackPic;
    QPixmap m_cardBasePic;
    QPixmap m_AllCardsPic;

    QLabel* streakslb;
    QLabel* m_rePickingCards;   //重新发牌标识
    QLabel* m_clock;            //闹钟图标
    QLabel* m_timeLabel;        //显示倒数时间
    QTimer* timer;              //叫地主计时器
    int time;                   //倒数时间
    bool autopass=1;
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
    QPushButton* m_tip;
    QPushButton* m_skill1;
    QPushButton* m_skill2;
    QPushButton* m_skill3;

    /*音效*/
    QSound* shuffleCardsMusic;
    QSound* bkMusic;
    QSound* winMusic;
    QSound* loseMusic;
    QSound* callLordMusic;
    QSound* noCallMusic;
    QSound* handtype;

    bool eventFilter(QObject * obj, QEvent * event);//事件过滤器
    bool _isPlayingMusic;

    bool skill1enabled=0;//破釜沉舟技能指示剂
    bool skill2enabled=0;//夜观星象技能指示剂
};

#endif // MAININTERFACE_H
