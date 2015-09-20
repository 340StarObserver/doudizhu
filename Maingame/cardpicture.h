#ifndef CARDPICTURE_H
#define CARDPICTURE_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "card.h"


class CardPicture : public QWidget
{
    Q_OBJECT
public:
    CardPicture(QWidget *parent = 0);
    void setPic(QPixmap& pic);
    void setCard(card& c);
    card getCard();
    void setTurn(bool t);
    bool getTurn();
    void setSelected(bool s);
    bool getSelected();


    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

    QPixmap &getPic();
signals:
    void TellSelected();    //选中信号

private:
    QPixmap m_pic;    //牌正面
    QPixmap m_back;   //牌反面
    bool m_turn;      //翻转
    bool m_selected;  //选中

    card m_card;      //对应的牌

};

#endif // CARDPICTURE_H
