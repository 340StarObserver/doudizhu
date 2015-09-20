#ifndef DATAPACKAGE
#define DATAPACKAGE

#include <QByteArray>
#include <QString>

//客户端报文-装包层(ok)
class DataPackage
{
public:
    //注册信息 报文装包
    static QByteArray regist(const QString& username,const QString& password,int head);
    //登陆信息 报文装包
    static QByteArray login(const QString& username,const QString& password);
    //出牌信息 报文装包
    static QByteArray chupai(int playerID,int num,int cards[]);
    //玩家进入游戏房间 报文装包
    static QByteArray enterRoom(int playerID);
};

#endif
