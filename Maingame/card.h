#ifndef CARD_H
#define CARD_H

//扑克牌点数
enum CardPoint
{
    Card_Begin,

    Card_3,
    Card_4,
    Card_5,
    Card_6,
    Card_7,
    Card_8,
    Card_9,
    Card_10,
    Card_J,
    Card_Q,
    Card_K,
    Card_A,
    Card_2,

    Card_SJ,
    Card_BJ,

    Card_End
};

//扑克牌花色
enum CardSuit
{
    Suit_Begin,

    Diamond,	// 方块
    Club,		// 梅花
    Heart,		// 红桃
    Spade,		// 黑桃

    Suit_End
};

//出牌类型
enum HandType
{
    Hand_Unknown,			// 未知
    Hand_Pass,				// 过
    Hand_Single,			// 单
    Hand_Pair,				// 对
    Hand_Triple,			// 三个
    Hand_Triple_Single,		// 三带一
    Hand_Triple_Pair,		// 三带二
    Hand_Plane,				// 飞机，555_666
    Hand_Plane_Two_Single,	// 飞机带两单，555_666_3_4
    Hand_Plane_Two_Pair,	// 飞机带两双，555_666_33_44
    Hand_Seq_Single,		// 顺子，34567(8...)
    Hand_Seq_Pair,			// 连对，33_44_55(_66...)
    Hand_Bomb,				// 炸弹
    Hand_Bomb_Jokers,		// 王炸
};

class card
{
public:
    card(CardPoint p=Card_Begin,CardSuit s=Suit_Begin);
    card(int number);   //根据整数创建
    CardPoint point;    //点数
    CardSuit suit;      //花色

    void setPoint(CardPoint p);// 设置点数
    CardPoint getPoint();      // 获取点数
    void setSuit(CardSuit s);  // 设置花色
    CardSuit getSuit();        // 获取花色
};

#endif // CARD_H
