#include "clientsocket.h"
#include "datapackage.h"
#include <QHostAddress>
#include "datatype.h"
#include <QDataStream>
#include <fstream>
using std::ifstream;
using std::ios_base;
#include <string>
using std::string;

//静态单例初始化
ClientSocket * ClientSocket::_instance=NULL;

//初始化配置文件,游戏IP,注册IP,游戏端口,注册端口
char * ClientSocket::_configFile="config.txt";
QString ClientSocket::_gameIP="223.3.81.190";
QString ClientSocket::_regiIP="223.3.81.190";
quint16 ClientSocket::_GamePort=3400;
quint16 ClientSocket::_RegistPort=3910;

//构造器
ClientSocket::ClientSocket()
{
    _socket=new QTcpSocket(this); //创建套接字
    _datasize=0;                  //接收数据大小清零
    readConfig();                 //读取配置文件
}

//获得单例
ClientSocket * ClientSocket::getInstance()
{
    if(_instance == NULL)
        _instance=new ClientSocket();
    return _instance;
}

//删除单例
void ClientSocket::destroyInstance()
{
    if(_instance){
        delete _instance;
        _instance=NULL;
    }
}

//读取配置
/*
 * 若打开配置文件成功
 * {
 *    依次读取 游戏服务器地址,注册服务器地址,游戏服务器端口,注册服务器端口
 *    关闭文件
 * }
 * 反之,采用默认的服务器地址和端口号
*/
void ClientSocket::readConfig()
{
    ifstream infile;
    infile.open(_configFile,ios_base::in);
    if(infile.is_open())
    {
        string gameIP,registIP;
        int gamePort,registPort;
        infile>>gameIP;
        infile>>registIP;
        infile>>gamePort;
        infile>>registPort;
        _gameIP=QString(gameIP.c_str());
        _regiIP=QString(registIP.c_str());
        _GamePort=(quint16)gamePort;
        _RegistPort=(quint16)registPort;
        infile.close();
    }
    else
    {
        _gameIP="223.3.81.190";
        _regiIP="223.3.81.190";
        _GamePort=3400;
        _RegistPort=3910;
    }
}

//获取套接字
QTcpSocket * ClientSocket::getSocket()
{
    return _socket;
}

//发送注册请求
/*
 * 参数分别为(用户名,密码,采用的头像代号)
 * 因为注册的时候,服务端不管注册成功如何都会断开连接,所以每次都要重连
*/
void ClientSocket::sendRegist(const QString &user, const QString &pwd, int head)
{
    _socket->connectToHost(QHostAddress(_regiIP),_RegistPort);
    _socket->write(DataPackage::regist(user,pwd,head));
}

//发送登陆请求
/*
 * 参数分别为(用户名,密码)
 * 因为  登陆成功的时候 服务端会 保持连接
 * 因为  登陆失败的时候 服务端会 断开连接
 * 故而  每次进行登陆请求:要么是第一次,要么是以前登陆失败了,所以每次都要进行重连
*/
void ClientSocket::sendLogin(const QString &user, const QString &pwd)
{
    _socket->connectToHost(QHostAddress(_gameIP),_GamePort);
    _socket->write(DataPackage::login(user,pwd));
}

//发送进入游戏房间请求
/*
 * 参数为(服务端在你登陆成功后 给你返回的 一个玩家编号)
 * 因为  进入游戏界面(即登陆成功后)才会发出此请求
 * 所以  此时肯定是和服务端保持连接的,不必重连
*/
void ClientSocket::sendEnterRoom(int playerID)
{
    _socket->write(DataPackage::enterRoom(playerID));
}

//发送出牌请求
/*
 * 参数为(玩家编号,出牌数量,牌数组)
 * 因为  游戏中才会发送出牌请求
 * 所以  出牌的时候肯定是和服务端保持连接的,不必重连
*/
void ClientSocket::sendChupai(int playerID, int num, int cards[])
{
    _socket->write(DataPackage::chupai(playerID,num,cards));
}

//配置套接字的信号槽关联(在进入登陆界面时调用)
void ClientSocket::setSignals()
{
    connect(_socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

//撤销套接字的信号槽关联(在进入注册界面时调用,因为注册服务是单独的,不使用这里的onReadyRead槽)
void ClientSocket::cancelSignals()
{
    disconnect(_socket,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

//接收登陆和游戏时的报文
/*
 * 1. 分不同种类的报文 来 解析数据
 * 2. 将数据 通过信号 报告给ui层(让ui层来决定应该怎样更新界面)
 * 3. 递归接收报文
*/
void ClientSocket::onReadyRead()
{
    QDataStream in(_socket);
    in.setVersion(QDataStream::Qt_5_5);
    if(_datasize == 0){
        if(_socket->bytesAvailable() < sizeof(quint16))
            return;
        in>>_datasize;
    }
    if(_socket->bytesAvailable() < _datasize)
        return;
    int type;
    in>>type;
    //判断报文的类型:
    switch(type)
    {
    case DataType::LoginResult:{
        //若报文 是 登陆结果
        bool res; int id=-1,head=-1;
        in>>res;
        //若登陆成功,则读取后台传来的玩家编号和你的头像代号(头像为你注册时选择的)
        if(res)
            in>>id>>head;
        //将此消息 报告 给ui层
        emit report_LoginResult(res,id,head);
        break;
    }
    case DataType::BroadcastNum:{
        //若报文 是 广播人数
        int num; vector<int> ids,heads;
        //读取当前在线人数
        in>>num;
        //循环读取当前在线玩家的编号和头像
        for(int i=0;i<num;i++){
            int t1,t2;
            in>>t1>>t2;
            ids.push_back(t1);
            heads.push_back(t2);
        }
        //将此消息 报告 给ui层
        emit report_BroadcastNum(num,ids,heads);
        break;
    }
    case DataType::Progress:{
        //若报文 是 游戏进度
        bool state; int winnerID=-1;
        //读取游戏进度
        //state==true表示游戏开始,此时没有winnerID(获胜者)
        //state==false表示游戏结束,此时有winnerID
        in>>state;
        //若游戏结束了,读取获胜者
        if(!state)
            in>>winnerID;
        //将此消息 报告 给ui层
        emit report_Progress(state,winnerID);
        break;
    }
    case DataType::Origin:{
        //若报文 是 初始牌面
        int landlordID,num,tmp; vector<int> cards;
        //读取地主编号 和 你的初始牌数
        in>>landlordID>>num;
        //循环读取你的牌
        for(int i=0;i<num;i++){
            in>>tmp;
            cards.push_back(tmp);
        }
        //将此消息 报告 给ui层
        emit report_Origin(landlordID,num,cards);
        break;
    }
    case DataType::Who:{
        //若报文 是 轮谁出牌
        int id;
        //读取轮谁出牌
        in>>id;
        //将此消息 报告 给ui层
        emit report_Who(id);
        break;
    }
    case DataType::Cards:{
        //若报文 是 某玩家出了什么牌
        int id,num,tmp; vector<int> cards;
        //读取 出牌玩家的编号 和 出的牌数
        in>>id>>num;
        //循环读取他出的牌
        for(int i=0;i<num;i++){
            in>>tmp;
            cards.push_back(tmp);
        }
        //将此消息 报告 给ui层
        emit report_Cards(id,num,cards);
        break;
    }
    case DataType::ActionFeedback:{
        //若报文 是 出牌成败
        bool res;
        //读取 出牌成败
        in>>res;
        //将此消息 报告 给ui层
        emit report_ActionFd(res);
        break;
    }
    }
    //递归接收报文
    _datasize=0;
    if(_socket->bytesAvailable() > 0)
        onReadyRead();
}
