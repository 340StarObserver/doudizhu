#include "datapackage.h"
#include "datatype.h"
#include <QDataStream>
#include <QIODevice>

//注册信息报文装包
//参数分别是(用户名,密码,头像代号)
QByteArray DataPackage::regist(const QString &username, const QString &password, int head)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<username;
    out<<password;
    out<<head;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//登陆信息报文装包
//参数分别是(用户名,密码)
QByteArray DataPackage::login(const QString &username, const QString &password)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::Login;
    out<<username;
    out<<password;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//出牌信息报文装包
//参数分别是(出牌的玩家编号,出牌数目,牌数组)
QByteArray DataPackage::chupai(int playerID, int num, int cards[])
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::Cards;
    out<<playerID;
    out<<num;
    for(int i=0;i<num;i++)
        out<<cards[i];
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//玩家进入游戏房间报文装包
//参数表示玩家在游戏时的编号
QByteArray DataPackage::enterRoom(int playerID)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::EnterRoom;
    out<<playerID;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}
