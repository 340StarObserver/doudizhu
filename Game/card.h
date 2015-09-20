#ifndef CARD
#define CARD

#include "huase.h"
#include "point.h"
#include <QString>

//represent a card(ok)
class Card
{
private:
    Huase _huase;
    Point _point;
public:
    Card(const Huase& huase,const Point& point);
    //get
    Huase getHuase()const;
    Point getPoint()const;
    //set
    void setHuase(const Huase& huase);
    void setPoint(const Point& point);
    //operator
    bool operator < (const Card& card)const;   //point  <
    bool operator == (const Card& card)const;  //point ==
    bool operator > (const Card& card)const;   //point >
    bool operator != (const Card& card)const;  //point !=
    bool totalEqual(const Card& card)const;    //point equal and huase equal
    //toString
    QString toString()const;
    //form a card based on a value between 1 and 54
    static Card form(int value);
};


#endif
