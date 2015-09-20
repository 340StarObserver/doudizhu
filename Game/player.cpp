#include "player.h"

//默认构造
Player::Player()
{

}

//获取用户名
QString Player::getUsername()const
{
    return _username;
}

//获取密码
QString Player::getPassword()const
{
    return _password;
}

//获取游戏总局数
uint Player::getTotaltimes()const
{
    return _totaltimes;
}

//获取胜利总局数
uint Player::getWintimes()const
{
    return _wintimes;
}

//获取头像代号
int Player::getHead()const
{
    return _head;
}

//获取游戏时编号
int Player::getGameID()const
{
    return _gameID;
}

//获取身份(true表示是地主 false表示是农民)
bool Player::getIsDizhu()const
{
    return _isDizhu;
}

//获取手牌
vector<Card> Player::getCards()const
{
    return _cards;
}

//将手牌转换为字符串格式
QString Player::cardsToString()const
{
    unsigned int N=static_cast<unsigned int>(_cards.size());
    QString str=QString("player[").append(QString::number(_gameID)).append("]: ");
    for(unsigned int i=0;i<N;i++)
        str.append(_cards[i].toString()).append(",");
    return str;
}

//设置用户名
void Player::setUsername(const QString &username)
{
    _username=username;
}

//设置密码
void Player::setPassword(const QString &password)
{
    _password=password;
}

//设置游戏总局数
void Player::setTotaltimes(uint totaltimes)
{
    _totaltimes=totaltimes;
}

//设置胜利总局数
void Player::setWintimes(uint wintimes)
{
    _wintimes=wintimes;
}

//设置头像代号
void Player::setHead(int head)
{
    _head=head;
}

//设置游戏时编号
void Player::setGameID(int gameID)
{
    _gameID=gameID;
}

//设置身份
void Player::setDizhu(bool ifDizhu)
{
    _isDizhu=ifDizhu;
}

//设置手牌
void Player::setCards(const vector<Card> &cards)
{
    _cards=cards;
}

//清空手牌
void Player::removeCards()
{
	_cards.clear();
}

//增加一张牌到手牌
void Player::addCard(const Card &card)
{
    _cards.push_back(card);
}

//赋值重载
Player & Player::operator = (const Player& player)
{
    _username=player._username;
    _password=player._password;
    _totaltimes=player._totaltimes;
    _wintimes=player._wintimes;
    _head=player._head;
    _gameID=player._gameID;
    _isDizhu=player._isDizhu;
    _cards=player._cards;
    return *this;
}

//whether has such a card
int Player::hasCard(const Card &card)const
{
    unsigned int N=static_cast<unsigned int>(_cards.size());
    for(unsigned int i=0;i<N;i++){
        if(card.totalEqual(_cards[i]))
            return i;
    }
    return -1;
}

//whether has such a combine
bool Player::hasCombine(const CardCombine &combine)const
{
    vector<Card> list=combine.getList();
    unsigned int N=static_cast<unsigned int>(list.size());
    for(unsigned int i=0;i<N;i++){
        if(hasCard(list[i])==-1)
            return false;
    }
    return true;
}

//whether this player win now
bool Player::ifWin()const
{
    return _cards.size()==0;
}

//remove cards
//从现有手牌中移除牌组list
void Player::removeCards(const vector<Card> &list)
{
    unsigned int N=static_cast<unsigned int>(list.size());
    for(unsigned int i=0;i<N;i++){
        int index=hasCard(list[i]);
        if(index!=-1)
            _cards.erase(_cards.begin()+index);
    }
}

//出牌,参数分别表示(自己要出的牌组,牌局上当前最大的牌组是谁出的,牌局上当前最大的牌组)
/*
 * 如果本人手牌中没有 要出的那个牌组,则出牌失败
 * if 自己==牌局上的当前霸主( 即上轮自己出牌后,轮了一圈没人接,又轮到自己了 )
 * {
 *    若自己要出的牌是 弃权过 or 非法牌型
 *      则出牌失败
 *    反之:{ 从自己手牌中移除要出的牌组,出牌成功 }
 * }
 * 反之 if 自己要出的牌组 打得过 牌局上称霸的牌组
 * {
 *    从自己手牌中移除要出的牌组
 *    出牌成功
 * }
 * 反之 出牌失败
*/
bool Player::chupai(CardCombine &selfCC, int thID, CardCombine &thCC)
{
    if(!hasCombine(selfCC))
        return false;
    if(_gameID==thID){
        CardCombine::Type type=selfCC.getType();
        if(type==CardCombine::Type::Guo||type==CardCombine::Type::Unknown)
            return false;
        removeCards(selfCC.getList());
        return true;
    }
    else if(selfCC.compareTo(thCC)==CardCombine::CompareRes::Larger){
        removeCards(selfCC.getList());
        return true;
    }
    return false;
}
