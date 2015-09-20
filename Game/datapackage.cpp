#include "datapackage.h"
#include "datatype.h"
#include <QDataStream>
#include <QIODevice>

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

//登陆结果报文装包
//参数分别是(登陆成败,玩家编号,头像代号)
//  其中res为true时,后面两个参数才生效.res为false时后面两参数随便填
QByteArray DataPackage::loginResult(bool res, int playerID, int head)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::LoginResult;
    out<<res;
    if(res)
        out<<playerID<<head;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//广播人数报文装包
//参数分别是(当前在线人数,玩家们的游戏编号数组,玩家们的头像代号数组)
QByteArray DataPackage::broadcastNum(int num, int playerIDS[], int heads[])
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::BroadcastNum;
    out<<num;
    for(int i=0;i<num;i++)
        out<<playerIDS[i]<<heads[i];
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//游戏进度报文装包
//参数分别是(游戏状态,获胜者的编号)
//  其中gameState==true表示游戏开始,此时winnerID不生效,因此该情况下winnerID随便填
//  gameState==false表示游戏结束,此时winnerID才具有实际意义
QByteArray DataPackage::progress(bool gameState, int winnerID)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::Progress;
    out<<gameState;
    if(!gameState)
        out<<winnerID;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//起始牌面报文装包
//参数分别是(地主编号,你的初始牌数,你的牌数组)
//  cards[]中的每一个元素的值域都是[1,54],
//  且按照(黑桃,红桃,梅花,方片)的顺序,以及(A,2,3,4,..Q,K)的顺序
//  53代表小王,54代表大王
QByteArray DataPackage::origin(int landlordID, int num, int cards[])
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::Origin;
    out<<landlordID;
    out<<num;
    for(int i=0;i<num;i++)
        out<<cards[i];
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//轮谁出牌报文装包
//参数表示现在应该轮到出牌的玩家的编号
QByteArray DataPackage::who(int thID)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::Who;
    out<<thID;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//出牌信息报文装包
//参数分别是(出牌的玩家编号,出牌数目,牌数组)
//  当客户端发送出牌请求时,playerID表示该你的游戏编号,cards[]表示你要出的牌
//  当客户端收到广播时,playerID则表示刚才出牌成功的玩家的编号,cards[]表示刚才出牌成功的人出的牌
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

//出牌反馈结果报文装包
//参数表示出牌成功与否,res==true表示出牌成功,反之表示失败
QByteArray DataPackage::actionFeedBack(bool res)
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<DataType::ActionFeedback;
    out<<res;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}
