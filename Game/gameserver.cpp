#include "gameserver.h"
#include "loginbusiness.h"
#include "datapackage.h"
#include "datatype.h"
#include "card.h"
#include "usermodel.h"
#include <QHostAddress>
#include <QByteArray>
#include <cstdlib>
using std::srand;
using std::rand;
#include <ctime>
using std::time;
#include <vector>
using std::vector;

//初始化单例对象
GameServer * GameServer::_instance=NULL;

//获得单例
GameServer * GameServer::getInstance()
{
    if(_instance==NULL)
        _instance=new GameServer();
    return _instance;
}

//删除单例
void GameServer::destroyInstance()
{
    if(_instance){
        delete _instance;
        _instance=NULL;
    }
}

//构造
GameServer::GameServer()
{
    for(int i=0;i<3;i++){
        _socket[i]=NULL;
        _size[i]=0;
    }
    _isGaming=false;
    originTimer();
}

//初始化出牌限时控制器
void GameServer::originTimer()
{
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(autoNext()));
}

//自动轮到下一人出牌
/*
 * 先停止倒计时
 * 更新轮谁出牌
 * 广播轮谁出牌的消息
*/
void GameServer::autoNext()
{
    _timer->stop();
    _gamework.setWhoToCards((_gamework.getWhoToCards()+1)%3);
    sendWho();
}

//析构
//删除当前在线的所有玩家的交互套接字
GameServer::~GameServer()
{
    for(int i=0;i<3;i++){
        if(_socket[i])
            delete _socket[i];
    }
}

//寻找 第一个悬空的套接字的下标(即第一个空位)
int GameServer::emptyIndex()const
{
    int index=0;
    while(index<3 && _socket[index])
        index++;
    return index;
}

//启动服务
/*
 * 开启监听
 * 关联新连接信号
 * 向ui层报告启动服务成败的消息
*/
void GameServer::start()
{
    if(!isListening()){
        if(listen(QHostAddress::Any,3400))
        {
            connect(this,SIGNAL(newConnection()),this,SLOT(dealNewConnect()));
            emit report("start listen port(3400) success");
        }
        else
            emit report("start listen port(3400) failed!");
    }
}

//停止服务
/*
 * 先取消新连接信号的关联
 * 向ui层汇报情况
 * 还原一切成员为初始状态
*/
void GameServer::stop()
{
    if(isListening()){
        disconnect(this,SIGNAL(newConnection()),this,SLOT(dealNewConnect()));
        close();
        emit report("stop listen port(3400)");
        restore();
    }
}

//还原为初始状态(在游戏结束时or关闭服务时 使用)
void GameServer::restore()
{
    _isGaming=false;
	_timer->stop();
    _gamework.setWhoToCards(0);
    _gamework.setLastWho(-1);
    _gamework.setLastCombine(CardCombine());
    for(int i=0;i<3;i++){
        _gamework.getPlayer(i)->operator =(Player());
        _size[i]=0;
        if(_socket[i])
            _socket[i]->disconnectFromHost();
    }
}

//结束游戏
//参数winner==true表示地主方胜利,反之表示农民方胜利
/*
 * 先更新数据库
 * 向ui层报告情况
 * 广播游戏结束报文
 * 还原为初始状态
*/
void GameServer::gameOver(bool winner)
{
    UserModel::updateHistory(_gamework.getPlayer(0)->getUsername(),_gamework.getPlayer(0)->getPassword(),winner);
    UserModel::updateHistory(_gamework.getPlayer(1)->getUsername(),_gamework.getPlayer(1)->getPassword(),!winner);
    UserModel::updateHistory(_gamework.getPlayer(2)->getUsername(),_gamework.getPlayer(2)->getPassword(),!winner);
	emit report(QString("game over,winner: ").append(winner ? "landlord" : "farmers"));
    for(int i=0;i<3;i++){
        if(_socket[i])
            _socket[i]->write(DataPackage::progress(false,winner?0:1));
    }
    restore();
}

//获得游戏业务层
GameWork * GameServer::getGameWork()
{
    return &_gamework;
}

//接受登陆业务的反馈信号
void GameServer::onReport(const QString &str)
{
    emit report(str);//把此信号向上抛给ui层
}

//处理新的连接请求
/*
 * 向ui层汇报情况
 * 使用LoginBusiness对象来代理登陆业务
 * 关联LoginBusiness对象的信号
*/
void GameServer::dealNewConnect()
{
    emit report("receive a new connection");
    QTcpSocket * socket=nextPendingConnection();
    LoginBusiness * lb=new LoginBusiness(socket,this);
    connect(lb,SIGNAL(report(QString)),this,SLOT(onReport(QString)));
}

//增加一个登陆成功的玩家
/*1. 发送report("some one login success")信号
 *2. 将socket加入_socket[]中
 *3. 调用游戏业务层的addPlayer
 *4. 设置socket的信号槽的关联
*/
void GameServer::add(QTcpSocket *socket, const QString &user, const QString &pwd, uint tt, uint wt, int head)
{
    emit report(QString(user).append(" login success"));
    int index=emptyIndex();
    _socket[index]=socket;
    _gamework.addPlayer(index,user,pwd,tt,wt,head);
    switch(index){
    case 0:{
        connect(_socket[index],SIGNAL(readyRead()),this,SLOT(onReadyRead_0()));
        connect(_socket[index],SIGNAL(disconnected()),this,SLOT(onDisconnect_0()));
        break;
    }
    case 1:{
        connect(_socket[index],SIGNAL(readyRead()),this,SLOT(onReadyRead_1()));
        connect(_socket[index],SIGNAL(disconnected()),this,SLOT(onDisconnect_1()));
        break;
    }
    case 2:{
        connect(_socket[index],SIGNAL(readyRead()),this,SLOT(onReadyRead_2()));
        connect(_socket[index],SIGNAL(disconnected()),this,SLOT(onDisconnect_2()));
        break;
    }
    }
}

//游戏开始
/*1. 发送report("game start")信号
 *2. 向所有在线玩家的客户端发送开始游戏进度报文
 *3. 给三个玩家随机分配起始牌面
 *4. 发送report信号,报告每个玩家的牌到ui层
 *5. 向所有在线玩家的客户端发送对应的起始牌面报文
 *6. 设置牌局上最大牌为过,report此信息
 *7. 设置轮到0号出牌,report此信息
 *8. 向所有在线玩家的客户端发送轮谁出牌报文
*/
void GameServer::gameStart()
{
    _isGaming=true;
	for (int i = 0; i < 3; i++)
		_gamework.getPlayer(i)->removeCards();
    //发送report("game start")信号
    emit report("game start!");
    //向所有在线玩家的客户端发送开始游戏进度报文
    for(int i=0;i<3;i++)
        _socket[i]->write(DataPackage::progress(true,-1));
    //给三个玩家随机分配起始牌面
    int origin[54],a1[20],a2[17],a3[17];
    for(int i=0;i<54;i++)
        origin[i]=i+1;
    mixedOrder(origin,54);
    mixedOrder(origin,54);
    mixedOrder(origin,54);
    for(int i=0;i<20;i++){
        _gamework.getPlayer(0)->addCard(Card::form(origin[i]));
        a1[i]=origin[i];
    }
    for(int i=20;i<37;i++){
        _gamework.getPlayer(1)->addCard(Card::form(origin[i]));
        a2[i-20]=origin[i];
    }
    for(int i=37;i<54;i++){
        _gamework.getPlayer(2)->addCard(Card::form(origin[i]));
        a3[i-37]=origin[i];
    }
    //发送report信号,报告每个玩家的牌到ui层
    for(int i=0;i<3;i++)
        emit report(_gamework.getPlayer(i)->cardsToString());
    //向所有在线玩家的客户端发送对应的起始牌面报文
    _socket[0]->write(DataPackage::origin(0,20,a1));
    _socket[1]->write(DataPackage::origin(0,17,a2));
    _socket[2]->write(DataPackage::origin(0,17,a3));
    //设置牌局上最大牌为过,report此信息
    emit report("original the max cardcombine in the game is empty");
    //设置轮到0号出牌,report此信息
    emit report("now it turns to player[0] to chupai");
    //向所有在线玩家的客户端发送轮谁出牌报文
    sendWho();
}

//起始乱序分牌
void GameServer::mixedOrder(int x[], int n)
{
    srand(static_cast<unsigned int>(time(0)));
    int index1,index2,tmp;
    for(int i=0;i<n;i++){
        index1=rand()%54;
        index2=rand()%54;
        tmp=x[index1];
        x[index1]=x[index2];
        x[index2]=tmp;
    }
}

//接收_socket[0]的数据
//此处只能是 进入房间报文 or 出牌报文
//其余报文统统忽略
void GameServer::onReadyRead_0()
{
    QDataStream in(_socket[0]);
    if(_size[0]==0){
        if(_socket[0]->bytesAvailable()<sizeof(quint16))
            return;
        in>>_size[0];
    }
    if(_socket[0]->bytesAvailable()<_size[0])
        return;
    int type;
    in>>type;
    if(type==DataType::Cards)
        deal_Chupai(&in);
    else if(type==DataType::EnterRoom)
        deal_come(&in);
    else{
        emit report("player[0] send invalid data when gaming");
        in.device()->seek(_size[0]);
    }
    _size[0]=0;
    if(_socket[0]->bytesAvailable()>0)
        onReadyRead_0();
}

//接收_socket[1]的数据
//此处只能是 进入房间报文 or 出牌报文
//其余报文统统忽略
void GameServer::onReadyRead_1()
{
    QDataStream in(_socket[1]);
    if(_size[1]==0){
        if(_socket[1]->bytesAvailable()<sizeof(quint16))
            return;
        in>>_size[1];
    }
    if(_socket[1]->bytesAvailable()<_size[1])
        return;
    int type;
    in>>type;
    if(type==DataType::Cards)
        deal_Chupai(&in);
    else if(type==DataType::EnterRoom)
        deal_come(&in);
    else{
        emit report("player[1] send invalid data type when gaming");
        in.device()->seek(_size[1]);
    }
    _size[1]=0;
    if(_socket[1]->bytesAvailable()>0)
        onReadyRead_1();
}

//接收_socket[2]的数据
//此处只能是 进入房间报文 or 出牌报文
//其余报文统统忽略
void GameServer::onReadyRead_2()
{
    QDataStream in(_socket[2]);
    if(_size[2]==0){
        if(_socket[2]->bytesAvailable()<sizeof(quint16))
            return;
        in>>_size[2];
    }
    if(_socket[2]->bytesAvailable()<_size[2])
        return;
    int type;
    in>>type;
    if(type==DataType::Cards)
        deal_Chupai(&in);
    else if(type==DataType::EnterRoom)
        deal_come(&in);
    else{
        emit report("player[2] send invalid data type when gaming");
        in.device()->seek(_size[2]);
    }
    _size[2]=0;
    if(_socket[2]->bytesAvailable()>0)
        onReadyRead_2();
}

//处理玩家0下线
/*
 * 向ui层汇报情况
 * if 还未开始游戏:
 * {
 *    取消对应套接字的信号关联
 *    删除并悬空对应套接字
 *    在线人数-1
 *    对应数据报文大小清零
 *    向所有在线的玩家广播当前在线人数情况
 * }
 * 反之,调用gameover函数
*/
void GameServer::onDisconnect_0()
{
    emit report("player[0] exit");
    if(!_isGaming){
        disconnect(_socket[0],SIGNAL(readyRead()),this,SLOT(onReadyRead_0()));
        disconnect(_socket[0],SIGNAL(disconnected()),this,SLOT(onDisconnect_0()));
        QTcpSocket * tmp=_socket[0];
        tmp->deleteLater();
        _socket[0]=NULL;
        int N=_gamework.getOnlineNum();
        _gamework.setOnlinNum(N-1);
        _size[0]=0;
        broadCast();
    }
    else
        gameOver(false);
}

//处理玩家1下线
/*
 * 向ui层汇报情况
 * if 还未开始游戏:
 * {
 *    取消对应套接字的信号关联
 *    删除并悬空对应套接字
 *    在线人数-1
 *    对应数据报文大小清零
 *    向所有在线的玩家广播当前在线人数情况
 * }
 * 反之,调用gameover函数
*/
void GameServer::onDisconnect_1()
{
    emit report("player[1] exit");
    if(!_isGaming){
        disconnect(_socket[1],SIGNAL(readyRead()),this,SLOT(onReadyRead_1()));
        disconnect(_socket[1],SIGNAL(disconnected()),this,SLOT(onDisconnect_1()));
        QTcpSocket * tmp=_socket[1];
        tmp->deleteLater();
        _socket[1]=NULL;
        int N=_gamework.getOnlineNum();
        _gamework.setOnlinNum(N-1);
        _size[1]=0;
        broadCast();
    }
    else
        gameOver(true);
}

//处理玩家2下线
/*
 * 向ui层汇报情况
 * if 还未开始游戏:
 * {
 *    取消对应套接字的信号关联
 *    删除并悬空对应套接字
 *    在线人数-1
 *    对应数据报文大小清零
 *    向所有在线的玩家广播当前在线人数情况
 * }
 * 反之,调用gameover函数
*/
void GameServer::onDisconnect_2()
{
    emit report("player[2] exit");
    if(!_isGaming){
        disconnect(_socket[2],SIGNAL(readyRead()),this,SLOT(onReadyRead_2()));
        disconnect(_socket[2],SIGNAL(disconnected()),this,SLOT(onDisconnect_2()));
        QTcpSocket * tmp=_socket[2];
        tmp->deleteLater();
        _socket[2]=NULL;
        int N=_gamework.getOnlineNum();
        _gamework.setOnlinNum(N-1);
        _size[2]=0;
        broadCast();
    }
    else
        gameOver(true);
}

//处理玩家进入游戏房间的报文
/*
 * 1.解析出玩家编号
 * 2.向ui层报告 "player[xx] enter game room"
 * 3.向ui层报告 当前在线人数
 * 4.向所有在线玩家的客户端发送广播人数报文
 * 5.若满了三人,调用gameStart方法
*/
void GameServer::deal_come(QDataStream *in)
{
    int playerID;
    *in>>playerID;
    int N=_gamework.getOnlineNum();
    emit report(QString("player[").append(QString::number(playerID)).append("] enter game room"));
    emit report(QString("now online players: ").append(QString::number(N)));
    broadCast();
    if(N>=3)
        gameStart();
}

//向在线玩家广播当前人数
void GameServer::broadCast()
{
    int N=_gamework.getOnlineNum();
    int * ids=new int[N]; int * heads=new int[N];
    int k=0;
    for(int i=0;i<3;i++)
    {
        if(_socket[i])
        {
            ids[k]=_gamework.getPlayer(i)->getGameID();
            heads[k]=_gamework.getPlayer(i)->getHead();
            k++;
        }
    }
    QByteArray bcn=DataPackage::broadcastNum(N,ids,heads);
    delete []ids;
    delete []heads;
    for(int i=0;i<3;i++){
        if(_socket[i])
            _socket[i]->write(bcn);
    }
}

//处理客户端发来的出牌报文
/*
 * 读取出牌者id,出牌数目,然后循环读取他出的牌
 * 向ui层报告xx尝试出xxxx牌
 * 调用游戏逻辑业务层的someoneAction方法 进行 出牌成败的判断
 * 记录上述方法的返回值为fd
 * if fd == -1: ( 即出牌失败 )
 * {
 *    向ui层汇报xx出牌失败的消息
 *    向这个出牌者发送 出牌失败报文
 *    重新开始出牌倒计时
 *    return
 * }
 * 向ui层汇报xx出牌成功的消息
 * 向所有在线的玩家 广播 出牌信息报文
 * if fd == 0 ( 即出牌成功,但此时未分胜负 )
 *    调用sendWho方法
 * 反之: ( 即出牌成功,而且此时已分胜负 )
 *    调用gameover方法
*/
void GameServer::deal_Chupai(QDataStream *in)
{
    _timer->stop();
    int playerID,num,tmpValue;
    vector<int> cards;
    *in>>playerID>>num;
    QString str=QString("player[").append(QString::number(playerID)).append("] try chupai: ");
    for(int i=0;i<num;i++){
        *in>>tmpValue;
        cards.push_back(tmpValue);
        str.append(Card::form(tmpValue).toString()).append(",");
    }
    emit report("receive data for chupai");
    emit report(str);
    int fd=_gamework.someoneAction(playerID,cards);
    if(fd==-1){
        emit report(QString("player[").append(QString::number(playerID)).append("] chupai failed"));
        _socket[playerID]->write(DataPackage::actionFeedBack(false));
        _timer->start(30000);
        return;
    }
    emit report(QString("player[").append(QString::number(playerID)).append("] chupai success"));
    _socket[playerID]->write(DataPackage::actionFeedBack(true));
    int * values=new int[num];
    for(int i=0;i<num;i++)
        values[i]=cards[i];
    QByteArray bytes1=DataPackage::chupai(playerID,num,values);
    delete []values;
    for(int i=0;i<3;i++){
        if(_socket[i])
            _socket[i]->write(bytes1);
    }
    if(fd==0)
        sendWho();
    else
        gameOver(playerID==0?true:false);
}

//广播轮谁出牌
/*
 * 先向所有连着的客户端发送 轮谁出牌的报文
 * 然后开始出牌倒计时
*/
void GameServer::sendWho()
{
    QByteArray bytes=DataPackage::who(_gamework.getWhoToCards());
    for(int i=0;i<3;i++){
        if(_socket[i])
            _socket[i]->write(bytes);
    }
    _timer->start(30000);
}
