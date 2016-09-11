#ifndef DATAPACKAGE
#define DATAPACKAGE

#include <QByteArray>
#include <QString>
#include <vector>
using std::vector;
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
    //轮谁叫地主报文装包
    static QByteArray whoCall(int thID,const vector<int>& landLordCards);
    //出牌信息报文装包
    static QByteArray chupai(int playerID,int num,int cards[]);
    //叫地主信息报文装包
    static QByteArray jiaodizhu(int playerID, bool isCall,int landLordCards[]);
    //出牌结果反馈报文装包
    static QByteArray actionFeedBack(bool res);
    //叫地主结果反馈报文装包
    static QByteArray callFeedBack(bool isCall/*, int landLordCards[]*/);
    //注册信息 报文装包
    static QByteArray regist(const QString& username,const QString& password,int head);
    //玩家进入游戏房间 报文装包
    static QByteArray enterRoom(int playerID);
};

#endif
