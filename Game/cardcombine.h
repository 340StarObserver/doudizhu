#ifndef CARDCOMBINE
#define CARDCOMBINE

#include <vector>
using std::vector;
#include "card.h"
#include <QString>

//a combination of cards(ok)
class CardCombine
{
private:
    vector<Card> _list;
    //判断牌型:
    bool is_Guo()const;               //过
    bool is_Single()const;            //单牌
    bool is_Shunzi();                 //顺子
    bool shunzi_type1(bool para=true);//( 最大牌不超过A的顺子 )
    bool shunzi_type2(bool para=true);//( 以A开头的顺子 )
    bool shunzi_type3(bool para=true);//( 以2开头的顺子 )
    bool is_Duizi()const;             //对子
    bool is_LianDui();                //连对
    bool is_Three()const;             //三张
    bool is_Three_One();              //三带一
    bool is_Three_Two();              //三带二
    bool is_Four_Two()const;          //四带二
    bool is_Plane();                  //无翅飞机
    bool is_Plane_Single()const;      //飞机带单牌
    bool is_Plane_Dui()const;         //飞机带对子
    bool is_Boom()const;              //普通炸弹
    bool is_KingBoom()const;          //王炸
    //sort this combination
    void combineSort();
public:
    enum Type
    {
        Unknown,                      //非法牌型
        Guo,                          //过
        Single,                       //单张
        Shunzi,                       //顺子
        Duizi,                        //对子
        LianDui,                      //连对
        Three,                        //三张
        Three_One,                    //三带一
        Three_Two,                    //三带二
        Four_Two,                     //四带二
        Plane,                        //无翅飞机
        Plane_Single,                 //飞机带同数量的单张
        Plane_Dui,                    //飞机带同数量的对子
        Boom,                         //炸弹
        KingBoom,                     //王炸
    };
    enum CompareRes
    {
        Smaller,                      //比不过
        Equal,                        //一样大
        Larger,                       //比得过
        CannotCompare,                //无法比较
    };
    CardCombine();                              //constructor
    QString toString()const;                    //toString
    vector<Card> getList()const;                //get the list of cards
    void setList(const vector<Card>& list);     //set the list of cards
    void add(const Card& card);                 //add one card to current combination
    Type getType();                             //返回牌型
    static int priority(Type type);             //计算某牌型的优先级(5,4,3,2,1,值越大越优先级越高)
    Point representPoint(Type type);            //计算代表点数
    CompareRes compareTo(CardCombine& combine); //牌组权值比较
};

#endif
