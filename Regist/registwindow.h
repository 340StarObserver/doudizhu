#ifndef REGISTWINDOW_H
#define REGISTWINDOW_H

#include <QWidget>
#include <QTextBrowser>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include "registserver.h"
#include <QString>

namespace Ui {
class RegistWindow;
}

//regist server gui for admin
class RegistWindow : public QWidget
{
    Q_OBJECT

public:
    explicit RegistWindow(QWidget *parent = 0);
    ~RegistWindow();
    bool eventFilter(QObject * obj, QEvent * event);
private:
    void originServer();       //origin the server
    void originWindow();       //origin the window
    void originFdRegion();     //origin the text region for feedback
    void originStateLabel();   //origin the label
    void originConButton();    //origin the button
private slots:
    void autoScroll();         //auto let textbrowser's scroll at the end
    void onReport(const QString& str);//slot for server report
private:
    Ui::RegistWindow *ui;
    bool _isRunning;           //whether the server is running
    RegistServer * _server;    //the server
    QTextBrowser * _fdRegion;  //text region for feedback
    QLabel * _statelabel;      //show whether the server is running
    QPushButton * _control;    //button for start or end the server
};

#endif
