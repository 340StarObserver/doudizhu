#ifndef SHOP_H
#define SHOP_H
#include "settings.h"
#include <QDialog>
#include <QMessageBox>
namespace Ui {
class shop;
}

class shop : public QDialog
{
    Q_OBJECT

public:
    explicit shop(QWidget *parent = 0);
    ~shop();
public slots:
    void onskill1clicked();
    void onskill2clicked();
    void onskill3clicked();

private:
    Ui::shop *ui;
    void initmain();
    QPushButton * _skill1;
    QPushButton * _skill2;
    QPushButton * _skill3;
};

#endif // SHOP_H
