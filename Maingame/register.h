#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QPaintEvent>
#include <QCloseEvent>

//注册界面(ok)
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = 0);
    ~Register();
protected:
    void paintEvent(QPaintEvent *event);  //绘图
    void originSocket();                  //配置套接字
    void closeEvent(QCloseEvent *event);  //关闭时还原套接字
    bool validData()const;                //判断输入合法性
private slots:
    void accountLineEditslot();
    void passwordLineEditslot(int arg1, int arg2);
    void accountEditingFinishedslot();
    void passwordeditingFinishedslot();
    void repeateditingFinishedslot();
    void radioButtonslot(bool checked);
    void radioButton_2slot(bool checked);
    void radioButton_3slot(bool checked);
    void registerBtnslot();
    void onReadyRead();                    //接收到注册结果报文
    void backBtnslot();
private:
    Ui::Register *ui;
    //ui成员:
    QRadioButton *radioButton_3;
    QRadioButton *radioButton;
    QLabel *aLabel2;
    QLineEdit *passwordLineEdit;           //密码输入框
    QLabel *accountLabel;
    QLabel *accinfoLabe;
    QPushButton *registerButton;           //注册按钮
    QLabel *label;
    QRadioButton *radioButton_2;
    QLabel *headtitleLabel;
    QLabel *aLabel4;
    QLineEdit *repeatLinEdit;              //确认密码输入框
    QLabel *passinfoLabel;
    QLabel *passwordLabel;
    QLabel *repeatLabel;
    QLineEdit *accountLineEdit;            //账号输入框
    QLabel *aLabel1;
    QPushButton *backButton;               //返回按钮
    //非ui成员:
    int _head;                             //头像代号(0 or 1 or 2)
    bool _canRegist;                       //是否可以点击 注册按钮
    bool _canBack;                         //是否可以点击 返回按钮
};

#endif
