#ifndef MISSIONINFO_H
#define MISSIONINFO_H

#include <QDialog>
#include <QPushButton>
#include <QPainter>
namespace Ui {
class missioninfo;
}

class missioninfo : public QDialog
{
    Q_OBJECT

public:
    explicit missioninfo(QWidget *parent = 0);
    ~missioninfo();
    void init();
    void paintEvent(QPaintEvent *event);
public slots:
    void onbt1clicked();
private:
    Ui::missioninfo *ui;
    QPushButton * _bt1;
};

#endif // MISSIONINFO_H
