#include "wanjia.h"

Player::Player(QWidget *parent) : QWidget(parent)
{
    m_hitPlayer=NULL;
    m_hitCards.clear();
}

Player::Player(int id, QString name, int score, int level)
{
    m_id=id;
    m_name=name;
    m_score=score;
    m_level=level;
    m_hitPlayer=NULL;
    m_hitCards.clear();
}

void Player::setName(QString name)
{
    m_name=name;
}

QString Player::getName()
{
    return m_name;
}

void Player::setLevel(int level)
{
    m_level=level;
}

int Player::getLevel()
{
    return m_level;
}

void Player::setScore(int s)
{
    m_score=s;
}

int Player::getScore()
{
    return m_score;
}

void Player::setId(int id)
{
    m_id=id;
}

int Player::getId()
{
    return m_id;
}

void Player::setRole(Role role)
{
    m_role=role;
    return;
}

Player::Role Player::getRole()
{
    return m_role;
}

void Player::addCard(card c)
{
    m_cards.append(c);
    return;
}

void Player::removeCard(card c)
{
    m_cards.removeOne(c);
    return;
}

void Player::removeCard(QList<card> &c)
{
    for(int i=0;i<c.size();i++)
        m_cards.removeOne(c[i]);
    return;
}

QList<card>& Player::getCards()
{
    return m_cards;
}

QList<int>& Player::getCardsIntList()
{
    return m_CardsIntList;
}

QList<card> &Player::getCardsToPlay()
{
    return m_cardsToPlay;
}

void Player::sortCard()
{
   qSort(m_cards.begin(),m_cards.end(),qGreater<card>());
   return;
}

void Player::callingLord(int bet)
{
  emit TellCallingLord(this,bet);
}

void Player::playHand(QList<card> cards)
{
    if(!cards.isEmpty())  removeCard(cards);    //从牌组中清除
    emit TellPlayingHand(this,cards);           //发送信号
}

void Player::addCardToPlay(QList<card> cards)
{
    for(int i=0;i<cards.size();i++)
        m_cardsToPlay.append(cards[i]);
}

Player* Player::getHitPlayer()
{
    return m_hitPlayer;
}

void Player::setHitPlayer(Player *player, QList<card> cards)
{
    m_hitPlayer=player;
    m_hitCards=cards;
}

Player* Player::getNextPlayer()
{
    return m_nextPlayer;
}

void Player::setNextPlayer(Player *player)
{
    m_nextPlayer=player;
}

QList<card> Player::getHitCards()
{
    return m_hitCards;
}

void Player::beginCallingLord()
{}

void Player::beginPlayingHand()
{}
