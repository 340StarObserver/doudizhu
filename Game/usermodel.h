#ifndef USERMODEL
#define USERMODEL

#include <QString>
#include <QSqlDatabase>

//model for user(ok)
class UserModel
{
private:
    //check the format of username
    static int checkUserName(const QString& username);
    //check the format of password
    static int checkPassword(const QString& password);
    //check the format of data
    static bool checkFormat(const QString& username,const QString& password);
    //connect database
    static QSqlDatabase connect();
    //connect count
    static unsigned int _count;
public:
    //regist a user
    static bool regist(const QString& username,const QString& password,int head);
    //identify user and return history data
    static bool identify(const QString& username,const QString& password,uint * totaltimes,uint
* wintimes,int * head);
    //update user's history data
    static bool updateHistory(const QString& username,const QString& password,bool ifWin);
};

#endif
