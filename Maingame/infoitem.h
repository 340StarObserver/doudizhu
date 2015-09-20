#ifndef INFOITEM_H
#define INFOITEM_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class InfoItem;
}

//玩家信息栏(ok)
class InfoItem : public QWidget
{
    Q_OBJECT
public:
    explicit InfoItem(QWidget *parent = 0);
    ~InfoItem();
    //get:
    int getID()const;               //获取编号
    bool getIdentify()const;        //获取身份
    int getRestCardNum()const;      //获取剩余手牌数量
    int getHead()const;             //获取头像代号
    //set:
    void setID(int ID);             //设置编号
    void setIdentify(bool isDizhu); //设置身份
    void setRestCardNum(int num);   //设置剩余手牌数量
    void setHead(int head);         //设置头像代号
    //restore:
    void restore();                 //还原标签为初始状态
private:
    void originWindow();            //初始化窗体属性
    void originIdLabel();           //初始化编号标签属性
    void originIdentifyLabel();     //初始化身份标签属性
    void originRestCardNumLabel();  //初始化剩余手牌数标签
    void originHeadLabel();         //初始化头像标签
private:
    Ui::InfoItem *ui;
    //ui成员:
    QLabel * _idLabel;              //编号标签
    QLabel * _identifyLabel;        //身份标签
    QLabel * _restCardNumLabel;     //剩余手牌数标签
    QLabel * _headLabel;            //头像标签
    //非ui成员:
    int _ID;                        //编号
    bool _identify;                 //身份(是否是地主)
    int _restCardNum;               //剩余手牌数量
    int _head;                      //头像代号
};

#endif
