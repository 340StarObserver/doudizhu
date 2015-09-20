#ifndef DATAPACKAGE
#define DATAPACKAGE

#include <QByteArray>
#include <QString>

//数据报文-装包层(ok)
class DataPackage
{
public:
    //登陆信息报文装包
    static QByteArray login(const QString& username,const QString& password);
    //登陆结果报文装包
    static QByteArray loginResult(bool res,int playerID,int head);
    //广播人数报文装包
    static QByteArray broadcastNum(int num,int playerIDS[],int heads[]);
    //游戏进度报文装包
    static QByteArray progress(bool gameState,int winnerID);
    //起始牌面报文装包
    static QByteArray origin(int landlordID,int num,int cards[]);
    //轮谁出牌报文装包
    static QByteArray who(int thID);
    //出牌信息报文装包
    static QByteArray chupai(int playerID,int num,int cards[]);
    //出牌结果反馈报文装包
    static QByteArray actionFeedBack(bool res);
};

#endif
