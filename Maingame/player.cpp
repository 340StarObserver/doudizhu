#include "player.h"
#include <QDebug>
#include <algorithm>
using std::sort;
using std::vector;

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

vector<int> *Player::getLandLordCards()
{
    return &_landLordCards;
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

int *Player::getLLCValues() const
{
    unsigned int N =static_cast<unsigned int>(_landLordCards.size());
    int *data2=new int[N+1];
    for(unsigned int i=0;i<N;i++)
        data2[i]=_landLordCards[i];
    return data2;
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

void Player::setLandLordCards(const vector<int> &landLordCards)
{
    qDebug()<<"setlanlordCards:";
    for(int i=0;i<3;i++)
        qDebug()<<landLordCards[i];
    _landLordCards=landLordCards;
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

    QList<card> cards;
    for(int i=0;i<_tryOut.size();i++)
    {
        card *c = new card(card(_tryOut[i]).getPoint(),card(_tryOut[i]).getSuit());
        cards.append(*c);
    }
    HandType type=Hand(cards).getHandType();
    switch(type)
    {
    case Hand_Pass:
        handtype=new QSound(":/sound/res/buyao4.wav" );
        break;
    case Hand_Triple:
        handtype=new QSound(":/sound/res/sange.wav" );
        break;
    case Hand_Triple_Single:
        handtype=new QSound(":/sound/res/sandaiyi.wav" );
        break;
    case Hand_Triple_Pair:
        handtype=new QSound(":/sound/res/sandaiyidui.wav" );
        break;
        /**/
    case Hand_Quad_Two_Single:
        handtype=new QSound(":/sound/res/sidaier.wav" );
        break;
    case Hand_Quad_Pair:
        handtype=new QSound(":/sound/res/sidaier.wav" );
        break;
    case Hand_Plane:
    case Hand_Plane_Two_Single:
    case Hand_Plane_Two_Pair:
        handtype=new QSound(":/sound/res/feiji.wav" );
        break;
    case Hand_Bomb:
        handtype=new QSound(":/sound/res/zhadan.wav" );
        break;
    case Hand_Bomb_Jokers:
        handtype=new QSound(":/sound/res/wangzha.wav" );
        break;
    case Hand_Seq_Single:
        handtype=new QSound(":/sound/res/shunzi.wav" );
        break;
    case Hand_Seq_Pair:
        handtype=new QSound(":/sound/res/liandui.wav" );
        break;

    case Hand_Single:
    {
        switch(cards[0].point)
        {
        case Card_A:
            handtype=new QSound(":/sound/res/1.wav" );
            break;
        case Card_2:
            handtype=new QSound(":/sound/res/2.wav" );
            break;
        case Card_3:
            handtype=new QSound(":/sound/res/3.wav" );
            break;
        case Card_4:
            handtype=new QSound(":/sound/res/4.wav" );
            break;
        case Card_5:
            handtype=new QSound(":/sound/res/5.wav" );
            break;
        case Card_6:
            handtype=new QSound(":/sound/res/6.wav" );
            break;
        case Card_7:
            handtype=new QSound(":/sound/res/7.wav" );
            break;
        case Card_8:
            handtype=new QSound(":/sound/res/8.wav" );
            break;
        case Card_9:
            handtype=new QSound(":/sound/res/9.wav" );
            break;
        case Card_10:
            handtype=new QSound(":/sound/res/10.wav" );
            break;
        case Card_J:
            handtype=new QSound(":/sound/res/11.wav" );
            break;
        case Card_Q:
            handtype=new QSound(":/sound/res/12.wav" );
            break;
        case Card_K:
            handtype=new QSound(":/sound/res/13.wav" );
            break;
        case Card_SJ:
            handtype=new QSound(":/sound/res/14.wav" );
            break;
        case Card_BJ:
            handtype=new QSound(":/sound/res/15.wav" );
            break;

        }
        break;
    }
    case Hand_Pair:
    {
        switch((int)cards[0].point)
        {
        case Card_A:
            handtype=new QSound(":/sound/res/dui1.wav" );
            break;
        case Card_2:
            handtype=new QSound(":/sound/res/dui2.wav" );
            break;
        case Card_3:
            handtype=new QSound(":/sound/res/dui3.wav" );
            break;
        case Card_4:
            handtype=new QSound(":/sound/res/dui4.wav" );
            break;
        case Card_5:
            handtype=new QSound(":/sound/res/dui5.wav" );
            break;
        case Card_6:
            handtype=new QSound(":/sound/res/dui6.wav" );
            break;
        case Card_7:
            handtype=new QSound(":/sound/res/dui7.wav" );
            break;
        case Card_8:
            handtype=new QSound(":/sound/res/dui8.wav" );
            break;
        case Card_9:
            handtype=new QSound(":/sound/res/dui9.wav" );
            break;
        case Card_10:
            handtype=new QSound(":/sound/res/dui10.wav" );
            break;
        case Card_J:
            handtype=new QSound(":/sound/res/dui11.wav" );
            break;
        case Card_Q:
            handtype=new QSound(":/sound/res/dui12.wav" );
            break;
        case Card_K:
            handtype=new QSound(":/sound/res/dui13.wav" );
            break;
        }
        break;
    }

    }
    handtype->play();

    _tryOut.clear();
}

//当收到服务端出牌失败的消息时,调用此方法,清空[尝试出的牌]
void Player::actionFailed()
{
    _tryOut.clear();
}

void Player::callSuccess()
{
    for(int i=0;i<3;i++)
    {
        _cards.insert(_cards.end(),_landLordCards[i]);
    }
    sort(_cards.begin(),_cards.end());
    //播放音乐
    callLandLord = new QSound(":/sound/res/jiaodizhu.wav");
    callLandLord->play();
}

void Player::callFailed()
{
    //播放音乐
    callLandLord = new QSound(":/sound/res/bujiao.wav");
    callLandLord->play();
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
