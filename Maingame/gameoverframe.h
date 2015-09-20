#ifndef GAMEOVERFRAME_H
#define GAMEOVERFRAME_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QSound>

namespace Ui {
class GameOverFrame;
}

//游戏结束界面
class GameOverFrame : public QFrame
{
    Q_OBJECT
public:
    explicit GameOverFrame(bool ifWin,QWidget *parent = 0);
    ~GameOverFrame();
signals:
    //向游戏界面报告用户的选择(res==true继续 ,res==false离开)
    void report_Choose(bool res);
private:
    bool eventFilter(QObject * obj, QEvent * event);//事件过滤器
private:
    Ui::GameOverFrame *ui;
    //ui成员:
    QLabel * _resLabel;      //胜负标签
    QPushButton * _ok;       //继续游戏按钮
    QPushButton * _no;       //离开游戏按钮
    //非ui成员:
    QSound * _music;         //音效控制器
    bool _canOk;             //是否可以点击 继续游戏按钮
    bool _canNo;             //是否可以点击 离开游戏按钮
};

#endif
