#ifndef SETTINGS_H
#define SETTINGS_H
#include <QPushButton>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QDialog>
#include <QButtonGroup>
//#include "index.h"
#include "shop.h"
#include "universal.h"
namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();
    void originpix();
    void originpic();
    void originfont();
    void newshop();
    void init();
    void themes();
    void eeclick(int count);
    int m=1.5;
public slots:
    void onRadioClickpix();
    void onRadioClickpic();
    void onRadioThemeClicked();
    void onCheck1();
    void onCheck2();
    void onCheck3();
    void settingssize(double m);
    void benchmark();
    void reset();
private:
    void paintEvent(QPaintEvent * event);           //绘图事件
    bool eventFilter(QObject *obj, QEvent *event);
    Ui::settings *ui;
    QLabel *_label1;
    QLabel *_label2;
    QLabel *_scores;
    QPushButton * _benchmark;
    QPushButton * _shop;
    QPushButton * _reset;
    QButtonGroup *_btnpix;
    QButtonGroup *_btnpic;
    QButtonGroup *_btntheme;
    QCheckBox *checkbox1 = new QCheckBox ("D&ebug 模式",this);
    QCheckBox *checkbox2 = new QCheckBox ("全屏模式",this);
    QCheckBox *checkbox3 = new QCheckBox ("技能开关",this);
    QRadioButton *radioButton11 = new QRadioButton("800*600", this);
    QRadioButton *radioButton12 = new QRadioButton("1000*750", this);
    QRadioButton *radioButton13 = new QRadioButton("1200*900", this);
    QRadioButton *radioButton21 = new QRadioButton("LOW", this);
    QRadioButton *radioButton22 = new QRadioButton("MEDIUM", this);
    QRadioButton *radioButton23 = new QRadioButton("HIGH", this);
    QRadioButton *radioButton31 = new QRadioButton("默认主题", this);
    QRadioButton *radioButton32 = new QRadioButton("东大主题", this);
    QRadioButton *radioButton33 = new QRadioButton("白色主题", this);
    QRadioButton *radioButton34 = new QRadioButton("舰C主题", this);
};

#endif // SETTINGS_H
