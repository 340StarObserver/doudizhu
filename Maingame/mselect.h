#ifndef MSELECT_H
#define MSELECT_H
#include "universal.h"
#include "single.h"
#include <QDialog>
#include <QPushButton>
namespace Ui {
class mselect;
}

class mselect : public QDialog
{
    Q_OBJECT

public:
    explicit mselect(QWidget *parent = 0);
    ~mselect();
public slots:
    void onmission1clicked();
    void onmission2clicked();
    void onmission3clicked();
protected:
    void closeEvent(QCloseEvent *);
private:
    Ui::mselect *ui;
    void initmain();
    void initmissionbuttons();
    QPushButton * _mission1;
    QPushButton * _mission2;
    QPushButton * _mission3;
};

#endif // MSELECT_H
