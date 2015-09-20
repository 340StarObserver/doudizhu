#ifndef GAMEWORK
#define GAMEWORK

#include "player.h"
#include "cardcombine.h"
#include <vector>
#include <QString>
using std::vector;

//游戏业务类(ok)
class GameWork
{
private:
    Player _players[3];        //三个玩家
    int _onlineNum;            //当前在线人数
    int _whoToCards;           //该谁出牌了(那人的游戏编号,0 or 1 or 2)
    int _lastWho;              //牌局上最大的牌组是谁出的
    CardCombine _lastCombine;  //牌局上最大的牌组
public:
    GameWork();
    //get
    Player * getPlayer(int index);
    int getOnlineNum()const;
    int getWhoToCards()const;
    int getLastWho()const;
    CardCombine getLastCombine();
    //set
    void setPlayer(const Player& player,int index);
    void setOnlinNum(int num);
    void setWhoToCards(int who);
    void setLastWho(int who);
    void setLastCombine(const CardCombine& combine);
    //增加一个玩家
    bool addPlayer(int index,const QString& user,const QString& pwd,uint tt,uint wt,int head);
    //某人出牌(返回值 -1:失败 0:成功但尚未胜利 1:成功且胜利了)
    int someoneAction(int gameID,const vector<int>& cards);
};

#endif
