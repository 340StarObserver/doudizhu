#include "gamework.h"
#include "card.h"

//构造
GameWork::GameWork()
{
    _onlineNum=0;
    _whoToCards=0;
    _lastWho=-1;
}

//获取某个玩家对象
Player * GameWork::getPlayer(int index)
{
    return &_players[index];
}

//获取当前在线人数
int GameWork::getOnlineNum() const
{
    return _onlineNum;
}

//获取轮谁出牌
int GameWork::getWhoToCards() const
{
    return _whoToCards;
}

//获取当前牌局上最大的牌组是谁出的
int GameWork::getLastWho() const
{
    return _lastWho;
}

//获取当前牌局上最大的牌组
CardCombine GameWork::getLastCombine()
{
    return _lastCombine;
}

//设置某个玩家
void GameWork::setPlayer(const Player &player, int index)
{
    _players[index]=player;
}

//设置当前在线人数
void GameWork::setOnlinNum(int num)
{
    _onlineNum=num;
}

//设置轮谁出牌
void GameWork::setWhoToCards(int who)
{
    _whoToCards=who;
}

//更新当前牌局上最大的牌组是谁出的
void GameWork::setLastWho(int who)
{
    _lastWho=who;
}

//更新当前牌局上最大的牌组
void GameWork::setLastCombine(const CardCombine &combine)
{
    _lastCombine=combine;
}

//增加一个玩家
/*
 * 若当前已经满了3人,则添加失败
 * 反之:
 * {
 *    设置索引为index的玩家属性
 *    属性包括:用户名,密码,总局数,胜利局数,头像代号,游戏编号,身份
 *    在线人数加一
 *    添加成功
 * }
*/
bool GameWork::addPlayer(int index,const QString &user, const QString &pwd, uint tt, uint wt, int head)
{
    if(_onlineNum>=3)
        return false;
    _players[index].setUsername(user);
    _players[index].setPassword(pwd);
    _players[index].setTotaltimes(tt);
    _players[index].setWintimes(wt);
    _players[index].setHead(head);
    _players[index].setGameID(index);
    _players[index].setDizhu(index==0?true:false);
    _onlineNum++;
    return true;
}

//某人出牌
//  (返回值 -1:失败 0:成功但尚未胜利 1:成功且胜利了)
//  参数分别为(第一个参数是出牌玩家的编号 0 or 1 or 2,第二个参数是出的牌)
/*
 * if 轮不到编号为gameID的玩家出牌
 *    则返回-1
 * if 出牌者不是当前牌局上的霸主 且 出牌着弃权
 *    更新轮谁出牌
 *    返回0
 * 利用cards参数构造出一个牌组combine
 * 调用索引为gameID的玩家对象的出牌函数,记录返回值res
 * if res==true:
 * {
 *    更新该轮到谁出牌了
 *    更新牌局上最大的牌组是谁出的
 *    更新牌局上最大的牌组
 *    若该玩家已经没有手牌了
 *        返回1
 *    反之,返回0
 * }
 * 返回 -1
*/
int GameWork::someoneAction(int gameID, const vector<int> &cards)
{
    if(gameID!=_whoToCards)
        return -1;
    if(cards.size()==0 && gameID!=_lastWho){
        //弃权过
        _whoToCards=(gameID+1)%3;
        return 0;
    }
    CardCombine combine;
    unsigned int N=static_cast<unsigned int>(cards.size());
    for(unsigned int i=0;i<N;i++)
        combine.add(Card::form(cards[i]));
    if(_players[gameID].chupai(combine,_lastWho,_lastCombine)){
        _whoToCards=(gameID+1)%3;//更新该轮到谁出牌了
        _lastWho=gameID;         //更新牌局上最大的牌组是谁出的
        _lastCombine=combine;    //更新牌局上最大的牌组
        if(_players[gameID].ifWin())
            return 1;
        return 0;
    }
    return -1;
}
