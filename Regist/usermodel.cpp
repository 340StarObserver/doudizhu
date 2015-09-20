#include "usermodel.h"
#include <QRegExp>
#include <QSqlQuery>
#include <QVariant>

//连接计数器
unsigned int UserModel::_count = 0;

//校验用户名的格式(14级学号)
int UserModel::checkUserName(const QString &username)
{
    QRegExp rx("^\\d{2}[a-z0-9A-Z]{1}14\\d{3}");
    return rx.indexIn(username);
}

//校验密码格式(14级密码)
int UserModel::checkPassword(const QString &password)
{
    QRegExp rx("21314\\d{4}");
    return rx.indexIn(password);
}

//校验用户名和密码的格式
bool UserModel::checkFormat(const QString &username, const QString &password)
{
    return UserModel::checkUserName(username)==0 && UserModel::checkPassword(password)==0;
}

//连接数据库
//数据库就在本地
QSqlDatabase UserModel::connect()
{
    _count++;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL",QVariant(_count).toString());
    db.setHostName("localhost");
    db.setDatabaseName("doudizhu");
    db.setUserName("root");
    db.setPassword("");
    return db;
}

//注册一个新账号
//参数分别是(用户名,密码,头像代号)
//若参数的数据格式正确 且 数据表中无相同的用户名,则注册成功
bool UserModel::regist(const QString &username, const QString &password,int head)
{
    if(!UserModel::checkFormat(username,password))
        return false;
    QSqlDatabase db = connect();
    if(!db.open())
        return false;
    QSqlQuery query(db);
    query.setForwardOnly(true);
    QString str="select username from usertable where username=";
    str.append(username);
    query.exec(str);
    if(query.next()){
        db.close();
        return false;
    }
    query.prepare("insert into usertable (username,password,totaltimes,wintimes,head) values (?,?,?,?,?)");
    QVariant x(username),y(password),z1(0),z2(0),z3(head);
    query.addBindValue(x);
    query.addBindValue(y);
    query.addBindValue(z1);
    query.addBindValue(z2);
    query.addBindValue(z3);
    query.exec();
    db.close();
    return true;
}

//用户认证
/*
 * 参数分别是(用户名,密码,总局数指针,胜利局数指针,头像代号指针)
 * 若db中有这个用户:
 * {
 *    利用指针参数来记录 总局数,胜利局数,头像代号
 *    返回true
 * }
 * 反之,返回false
*/
bool UserModel::identify(const QString &username,const QString &password,uint * totaltimes,uint
* wintimes,int * head)
{
    if(!UserModel::checkFormat(username,password))
        return false;
    QSqlDatabase db = connect();
    if(!db.open())
        return false;
    QSqlQuery query(db);
    query.setForwardOnly(true);
    QString str="select totaltimes,wintimes,head from usertable where username=";
    str.append(username);
    str.append("&& password=");
    str.append(password);
    query.exec(str);
    if(query.next()){
        *totaltimes = query.value(0).toUInt();
        *wintimes = query.value(1).toUInt();
        *head = query.value(2).toInt();
        db.close();
        return true;
    }else{
        db.close();
        return false;
    }
}

//更新某人的胜负记录
//参数分别是(用户名,密码,这一局胜利or失败)
//总局数+1,若赢了,则获胜局数也+1
bool UserModel::updateHistory(const QString &username, const QString &password, bool ifWin)
{
    uint x=0,y=0;int z=0;
    if(!identify(username,password,&x,&y,&z))
        return false;
    QSqlDatabase db = connect();
    if(!db.open())
        return false;
    x++;
    if(ifWin) y++;
    QString s1=QString::number(x),s2=QString::number(y);
    QString str=QString("update usertable set totaltimes=%1,wintimes=%2 where username=%3 && password=%4")
            .arg(s1).arg(s2).arg(username).arg(password);
    QSqlQuery query(db);
    if(query.exec(str)){
        db.close();
        return true;
    }else{
        db.close();
        return false;
    }
}
