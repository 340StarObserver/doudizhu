#ifndef CARDLIST_H
#define CARDLIST_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <vector>

using std::vector;

namespace Ui {
class CardList;
}

//某个玩家的出牌区(ok)
class CardList : public QWidget
{
    Q_OBJECT
public:
    explicit CardList(QWidget *parent = 0);
    ~CardList();
public:
    static QPixmap pictureShot(int value); //根据1-54的数字截取对应的牌
    void addOne(int value);                //增加一张牌到出牌区
    void clearAll();                       //清空出牌区所有牌
    void update(const vector<int>& values);//更新出牌区内所有牌
public:
    static const int _WCard=80; //单张牌的宽
    static const int _HCard=105;//单张牌的高
private:
    void originWindow();        //初始化窗体属性
    void originLabels();        //初始化出牌区内的卡牌标签
private:
    Ui::CardList *ui;
    //ui成员:
    QLabel * _labels[14];       //卡牌标签
    //非ui成员:
    int _num;                   //出牌区中当前牌数
};

#endif
