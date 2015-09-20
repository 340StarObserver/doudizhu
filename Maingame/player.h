#ifndef PLAYER
#define PLAYER

#include <vector>
using std::vector;
#include <QString>

//表示自己这个玩家(ok)
class Player
{
private:
    int _ID;              //编号
    int _head;            //头像代号
    QString _user;        //账号
    QString _pwd;         //密码
    vector<int> _cards;   //手牌
    vector<int> _tryOut;  //尝试出的牌
private:
    int find(int onecard)const;  //从手牌中查找某张牌的下标(找不到则返回-1)
public:
    Player();                    //构造
    //get:
    int getID()const;            //获取 编号
    int getHead()const;          //获取 头像代号
    QString get_User()const;     //获取账号
    QString get_Pwd()const;      //获取密码
    vector<int> * getMyCards();  //获取 手牌
    vector<int> * getTryOut();   //获取 尝试出的牌
    int * getValues()const;      //获取 尝试出的牌
    //set:
    void setID(int ID);                         //设置 编号
    void setHead(int head);                     //设置 头像代号
    void set_User(const QString& user);         //设置账号
    void set_Pwd(const QString& pwd);           //设置密码
    void setCards(const vector<int>& cards);    //设置 手牌
    void setTryOut(const vector<int>& tryOut);  //设置 尝试出的牌
    //functions:
    //从[手牌]中移除[尝试出的牌],并清空[尝试出的牌]
    void actionSuccess();
    //清空[尝试出的牌]
    void actionFailed();
    //当点击第index张手牌,调用此方法,将对应的牌加入[尝试出的牌],但是并不从手牌中移除
    void addOneToTryOut(int index);
    //当又一次点击第index张手牌,调用此方法,将对应的牌从[尝试出的牌]中移除
    void rmOneFromTryOut(int index);
};

#endif
