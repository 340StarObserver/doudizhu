#include "player.h"
#include <algorithm>
using std::sort;

//从手牌中查找某张牌的下标(找不到则返回-1)
int Player::find(int onecard) const
{
    unsigned int N=static_cast<unsigned int>(_cards.size());
    for(unsigned int i=0;i<N;i++)
    {
        if(_cards[i] == onecard)
            return i;
    }
    return -1;
}

//构造
Player::Player()
{

}

//获取 编号
int Player::getID()const
{
    return _ID;
}

//获取 头像代号
int Player::getHead()const
{
    return _head;
}

//获取用户名
QString Player::get_User()const
{
    return _user;
}

//获取密码
QString Player::get_Pwd()const
{
    return _pwd;
}

//获取 手牌
vector<int> * Player::getMyCards()
{
    return &_cards;
}

//获取 尝试出的牌
vector<int> * Player::getTryOut()
{
    return &_tryOut;
}

//获取 尝试出的牌
int * Player::getValues()const
{
    unsigned int N=static_cast<unsigned int>(_tryOut.size());
    int * data=new int[N+1];
    for(unsigned int i=0;i<N;i++)
        data[i]=_tryOut[i];
    return data;
}

//设置 编号
void Player::setID(int ID)
{
    _ID=ID;
}

//设置 头像代号
void Player::setHead(int head)
{
    _head=head;
}

//设置用户名
void Player::set_User(const QString &user)
{
    _user=user;
}

//设置密码
void Player::set_Pwd(const QString &pwd)
{
    _pwd=pwd;
}

//设置 手牌
void Player::setCards(const vector<int> &cards)
{
    _cards=cards;
    sort(_cards.begin(),_cards.end());
}

//设置 尝试出的牌
void Player::setTryOut(const vector<int> &tryOut)
{
    _tryOut=tryOut;
}

//当收到服务端出牌成功的消息时,调用此方法,从[手牌]中移除[尝试出的牌],并清空尝试出的牌
void Player::actionSuccess()
{
    unsigned int N=static_cast<unsigned int>(_tryOut.size());
    for(unsigned int i=0;i<N;i++)
    {
        int index=find(_tryOut[i]);
        if(index != -1)
            _cards.erase(_cards.begin()+index);
    }
    _tryOut.clear();
}

//当收到服务端出牌失败的消息时,调用此方法,清空[尝试出的牌]
void Player::actionFailed()
{
    _tryOut.clear();
}

//当点击第index张手牌,调用此方法,将对应的牌加入[尝试出的牌],但是并不从手牌中移除
void Player::addOneToTryOut(int index)
{
    _tryOut.push_back(_cards[index]);
}

//当又一次点击第index张手牌,调用此方法,将对应的牌从[尝试出的牌]中移除
void Player::rmOneFromTryOut(int index)
{
    unsigned int N=static_cast<unsigned int>(_tryOut.size());
    int k=-1;
    for(unsigned int i=0;i<N;i++){
        if(_tryOut[i] == _cards[index]){
            k=i;
            break;
        }
    }
    if(k != -1)
        _tryOut.erase(_tryOut.begin()+k);
}
