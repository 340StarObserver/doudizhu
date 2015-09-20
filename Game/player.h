#ifndef PLAYER
#define PLAYER

#include <QString>
#include "cardcombine.h"

//玩家类(ok)
class Player
{
private:
    //about personal data
    QString _username;          //username of this player
    QString _password;          //password of this player
    uint _totaltimes;           //total game times of this player
    uint _wintimes;             //win game times of this player
    int _head;                  //the head portrait of this player
    //about current game data
    int _gameID;                //player id in current game
    bool _isDizhu;              //whether this player is dizhu
    vector<Card> _cards;        //the cards which this player has now
private:
    int hasCard(const Card& card)const;                //whether has such a card
    bool hasCombine(const CardCombine& combine)const;  //whether has such a combine
    void removeCards(const vector<Card>& list);        //remove cards
public:
    Player();
    //get
    QString getUsername()const;                   //get username
    QString getPassword()const;                   //get password
    uint getTotaltimes()const;                    //get total game times
    uint getWintimes()const;                      //get win game times
    int getHead()const;                           //get head
    int getGameID()const;                         //get playerID
    bool getIsDizhu()const;                       //get if is landlord
    vector<Card> getCards()const;                 //get hand cards
    QString cardsToString()const;                 //hand cards to string
    //set
    void setUsername(const QString& username);    //set username
    void setPassword(const QString& password);    //set password
    void setTotaltimes(uint totaltimes);          //set total game times
    void setWintimes(uint wintimes);              //set win game times
    void setHead(int head);                       //set head
    void setGameID(int gameID);                   //set playerID
    void setDizhu(bool ifDizhu);                  //set if is landlord
    void setCards(const vector<Card>& cards);     //set hand cards
    void addCard(const Card& card);               //add one card to hand cards
    void removeCards();                           //remove all hand cards
    Player & operator = (const Player& player);   //operator =
    //whether this player win now
    bool ifWin()const;
    //出牌,参数分别表示(自己要出的牌组,牌局上当前最大的牌组是谁出的,牌局上当前最大的牌组)
    bool chupai(CardCombine& selfCC,int thID,CardCombine& thCC);
};

#endif
