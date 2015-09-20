#include "cardpicture.h"


CardPicture::CardPicture(QWidget *parent) : QWidget(parent)
{
    m_turn= false;
    m_selected= false;
    QPixmap pic(":/img/res/card2.png");
    m_back= pic.copy(2*80,4*105,80,105);
}

void CardPicture::setPic(QPixmap& pic)
{
    m_pic = pic;
    resize(m_pic.size());
}

void CardPicture::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    if(m_turn)
        painter.drawPixmap(this->rect(),m_pic);
    else
        painter.drawPixmap(this->rect(),m_back);
}

void CardPicture::setCard(card &c)
{
    m_card=c;
}

card CardPicture::getCard()
{
    return m_card;
}

void CardPicture::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        emit TellSelected();             //鼠标左键点击牌,发出选中信号
}

void CardPicture::setTurn(bool t)
{
    if(m_turn != t)
        m_turn =t;
    return;
}

void CardPicture::setSelected(bool s)
{
    if(m_selected!=s)
        m_selected=s;
    return;
}

bool CardPicture::getSelected()
{
    return m_selected;
}

QPixmap& CardPicture::getPic()
{
    return m_pic;
}
