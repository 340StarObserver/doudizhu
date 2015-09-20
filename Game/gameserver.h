#ifndef GAMESERVER
#define GAMESERVER

#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include <QDataStream>
#include <QTimer>
#include "gamework.h"

//游戏服务
class GameServer : public QTcpServer
{
private:
    Q_OBJECT
    QTcpSocket * _socket[3];           //三个登陆成功的交互套接字
    GameWork _gamework;                //游戏业务层
    bool _isGaming;                    //是否在游戏中
    quint16 _size[3];                  //接收到的数据大小
    static GameServer * _instance;     //单例
    QTimer * _timer;                   //出牌限时控制器
private:
    explicit GameServer();             //构造
    void originTimer();                //初始化出牌限时控制器
    void sendWho();                    //广播轮谁出牌
    void mixedOrder(int x[],int n);    //乱序
    void gameStart();                  //开始游戏
    void gameOver(bool winner);        //结束游戏
    void restore();                    //还原为初始状态
    void deal_come(QDataStream * in);  //处理玩家进入游戏房间报文
    void broadCast();                  //向在线玩家广播当前人数
    void deal_Chupai(QDataStream * in);//处理出牌报文
signals:
    void report(const QString& str);   //向ui层报告情况
private slots:
    void dealNewConnect();             //处理新的连接请求
    void onReport(const QString& str); //接受登陆业务的反馈信号
    void onReadyRead_0();              //接收_socket[0]的数据
    void onReadyRead_1();              //接收_socket[1]的数据
    void onReadyRead_2();              //接收_socket[2]的数据
    void onDisconnect_0();             // 玩家0下线
    void onDisconnect_1();             // 玩家1下线
    void onDisconnect_2();             // 玩家2下线
    void autoNext();                   // 自动轮到下一人出牌
public:
    ~GameServer();                     //析构
    void start();                      //启动服务
    void stop();                       //停止服务
    GameWork * getGameWork();          //获得游戏业务层
    static GameServer * getInstance(); //获得单例
    static void destroyInstance();     //删除单例
    int emptyIndex()const;             //第一个悬空的socket的下标
    //增加一个登陆成功的玩家
    void add(QTcpSocket * socket,const QString& user,const QString& pwd,uint tt,uint wt,int head);
};

#endif
