#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTextBrowser>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include <QEvent>

namespace Ui {
class GameWindow;
}

//the window of game server for admin(ok)
class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow();
    bool eventFilter(QObject * obj, QEvent * event); //时间过滤器
private slots:
    void autoScroll();                               //反馈区滚动条自动下滑
    void onReport(const QString& str);               //接收网络层汇报信号的槽
private:
    void originWindow();                             //初始化窗体属性
    void originFdRegion();                           //初始化反馈区属性
    void originButton();                             //初始化服务开关按钮
    void originLabel();                              //初始化服务状态标签
    void originServer();                             //初始化游戏服务业务层
private:
    Ui::GameWindow *ui;
    QTextBrowser * _fdRegion; //反馈区
    QPushButton * _button;    //开关按钮
    QLabel * _stateLabel;     //状态标签
    bool _isRun;              //服务是否正在运行
};

#endif // GAMEWINDOW_H
