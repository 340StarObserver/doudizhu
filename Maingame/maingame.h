#ifndef MAINGAME_H
#define MAINGAME_H

#include <QDialog>
#include <QPaintEvent>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QString>
#include <QTimer>
#include "player.h"
#include "chatwindow.h"
#include "infoitem.h"
#include "gamesound.h"
#include "cardlist.h"
#include "gameoverframe.h"

namespace Ui {
class Maingame;
}

//游戏界面
class Maingame : public QDialog
{
    Q_OBJECT
public:
    explicit Maingame(int playerID,int head,const QString& user,const QString& pwd,QWidget *parent = 0);
    ~Maingame();
private:
    //配置非ui成员的属性:
    void originSelf(int playerID,int head,const QString& user,const QString& pwd);
    //配置ui成员的属性:
    void originWindow();                    //初始化窗体(ok)
    void paintEvent(QPaintEvent *event);    //初始化背景(ok)
    void originStartWar();                  //初始化开战标签(ok)
    void originWaitLabel();                 //初始化等待玩家xx出牌标签(ok)
    void originActLabel();                  //初始化出牌成功失败的标签(ok)
    void originChatWindow();                //初始化聊天栏(ok)
    void originInfoWindows();               //初始化玩家信息栏(ok)
    void originOps();                       //初始化操作栏(ok)
    void originCardLabels();                //初始化手牌标签(ok)
    void originCardLists();                 //初始化三人的出牌区(ok)
    void originMusic();                     //初始化音乐(ok)
    void originTimer();                     //初始化时间控制器和显示标签(ok)
    void originSocket();                    //配置套接字(ok)
    //私有方法:
    void reDrawMyRegion();                  //更新我方区域(ok)
    bool eventFilter(QObject * obj, QEvent * event);//事件过滤器(ok)
    void restore();                         //还原为初始状态(ok)
    void startDaojishi();                   //开始倒计时(ok)
    void stopDaojishi();                    //停止倒计时(ok)
private slots:
    void hideStartWarLabel();               //隐藏"开战"标签的槽(ok)
    void hideActSuccessLabel();             //隐藏"出牌成功"标签的槽(ok)
    void hideActFailedLabel();              //隐藏"出牌失败"标签的槽(ok)
    void hideOtherChupai();                 //隐藏他人出牌反馈标签的槽(ok)
    void on_timer();                        //倒计时槽(ok)
public slots:
    //接收 胜负小窗口中的用户选择(ok)
    void on_choose(bool res);
    //处理 继续游戏(ok)
    void on_continue(bool res,int playerID,int head);
    //处理 广播人数的消息(ok)
    void receive_BroadCastNum(int num,const vector<int>& ids,const vector<int>& heads);
    //处理 游戏进度的消息(ok)
    void receive_Progress(bool state,int winnerID);
    //处理 初始牌面的消息(ok)
    void receive_Origin(int landlordID,int num,const vector<int>& cards);
    //处理 轮谁出牌的消息(ok)
    void receive_Who(int who);
    //处理 某人出牌成功的消息(ok)
    void receive_Cards(int playerID,int num,const vector<int>& cards);
    //处理 自己出牌成败反馈的消息(ok)
    void receive_ActionFd(bool res);
private:
    Ui::Maingame *ui;
    //ui成员:
    //用来提示的:
    QLabel * _startWar;          //开战标签
    QLabel * _waitLabel;         //等待玩家xx出牌标签
    QLabel * _actSuccessLabel;   //出牌成功标签
    QLabel * _actFailedLabel;    //出牌失败标签
    QLabel * _otherChupai;       //其他人出牌的反馈标签
    QLabel * _musicLabel;        //音乐开关标签
    QLabel * _box[3];            //玩家信息栏边框
    QLabel * _timerLabel;        //剩余出牌秒数标签
    //封装模块:
    ChatWindow * _chatwindow;    //聊天侧边栏
    InfoItem * _infowindows[3];  //玩家信息栏
    CardList * _cardlist[3];     //三人的出牌区
    GameOverFrame * _frame;      //胜负框框
    //我方手牌区:
    QPushButton * _action;       //出牌按钮
    QPushButton * _giveUp;       //弃权过按钮
    QLabel * _cardLabels[20];    //手牌标签
    //非ui成员:
    Player _self;                //自己
    int _eachCardNum[3];         //场上所有玩家的手牌数量
    GameSound _music;            //音乐控制器
    bool _isFirstChupai;         //是否是第一次出牌
    bool _isPlayingMusic;        //是否正在播放音乐
    bool _canChooseCard;         //是否可以选中手牌
    bool _canAction;             //是否可以点击 出牌按钮
    bool _canGiveUp;             //是否可以点击 弃权按钮
    QTimer * _timer;             //出牌限时控制器
    int _restSeconds;            //剩余出牌秒数
};

#endif
