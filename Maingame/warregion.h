#ifndef WARREGION_H
#define WARREGION_H

#include <QWidget>
#include <QLabel>
#include <vector>
using std::vector;
#include <QPixmap>

namespace Ui {
class WarRegion;
}

//战场区(ok)
//显示当前牌局上称霸的牌组,以及是谁出的
class WarRegion : public QWidget
{
    Q_OBJECT
public:
    explicit WarRegion(QWidget *parent = 0);
    ~WarRegion();
    void setDominateID(int id);                          //设置称霸者的编号
    void addOneCard(int card);                           //向称霸区添加一张牌
    void clearCards();                                   //清空称霸区的牌
    void update(int dominateID,const vector<int>& list); //更新称霸区
    static const int _WCard=80; //单张牌的宽
    static const int _HCard=105;//但张牌的高
    static QPixmap pictureShot(int value);//根据1-54的数字截取对应的牌
private:
    void originWindow();        //初始化窗体
    void originDominateLabel(); //初始化称霸者的编号标签
    void originCardsRegion();   //初始化称霸的牌组区
private:
    Ui::WarRegion *ui;
    //ui成员:
    QLabel * _dominateLabel;    //称霸者的编号标签
    QLabel * _cards[20];        //当前称霸牌局的牌们
    //非ui成员:
    int _num;                   //当前称霸牌局的牌组中的牌数
};

#endif // WARREGION_H
