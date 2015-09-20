#ifndef CLIENTSOCKET
#define CLIENTSOCKET

#include <QTcpSocket>
#include <QString>
#include <vector>
using std::vector;

//客户端套接字类(ok)
class ClientSocket : public QObject
{
    Q_OBJECT
private:
    QTcpSocket * _socket;                     //套接字
    quint16 _datasize;                        //收到的报文大小
private:
    static char * _configFile;                //配置文件路径
    static QString _regiIP;                   //注册服务IP
    static quint16 _RegistPort;               //注册服务的端口
    static QString _gameIP;                   //游戏服务IP
    static quint16 _GamePort;                 //游戏服务的端口
    static ClientSocket * _instance;          //单例对象
signals:  //这些信号 用来 向ui层报告网络层解析出的数据
    //报告 登陆结果
    void report_LoginResult(bool res,int playerID,int head);
    //报告 广播人数
    void report_BroadcastNum(int num,const vector<int>& ids,const vector<int>& heads);
    //报告 游戏进度
    void report_Progress(bool state,int winnerID);
    //报告 初始牌面
    void report_Origin(int landlordID,int num,const vector<int>& cards);
    //报告 轮谁出牌
    void report_Who(int who);
    //报告 出牌信息
    void report_Cards(int playerID,int num,const vector<int>& cards);
    //报告 出牌反馈
    void report_ActionFd(bool res);
private:
    explicit ClientSocket();                  //构造器
    static void readConfig();                 //读取配置文件
private slots:
    void onReadyRead();                       //接收登陆和游戏时的报文
public:
    static ClientSocket * getInstance();      //获得单例
    static void destroyInstance();            //删除单例
    QTcpSocket * getSocket();                 //获取套接字
    void setSignals();                        //配置套接字的信号槽关联
    void cancelSignals();                     //撤销套接字的信号槽关联
    //发送注册请求
    void sendRegist(const QString& user,const QString& pwd,int head);
    //发送登陆请求
    void sendLogin(const QString& user,const QString& pwd);
    //发送进入游戏房间请求
    void sendEnterRoom(int playerID);
    //发送出牌请求
    void sendChupai(int playerID,int num,int cards[]);
};

#endif
