#ifndef SINGLESL_H
#define SINGLESL_H
#include <QPushButton>
#include <QDialog>
#include <QPainter>
#include "universal.h"
#include "single.h"
#include "index.h"
#include "mselect.h"
#include <QMessageBox>
namespace Ui {
class singlesl;
}

class singlesl : public QDialog
{
    Q_OBJECT

public:
    explicit singlesl(QWidget *parent = 0);
    ~singlesl();
    void save();//读取
    void load();//存档

private slots:
    void onnewsclicked();
    void onnewdclicked();
    void onloadclicked();
    void oncloseclicked();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::singlesl *ui;
    void init();
    void paintEvent(QPaintEvent *event);
    void initload();//初始化读取
    void initnews();//初始化选择关卡
    void initnewd();//初始化新游戏

    QPushButton * _load;//读取
    QPushButton * _news;//选择关卡
    QPushButton * _newd;//新游戏
    QPushButton * _close;
};

#endif // SINGLESL_H
