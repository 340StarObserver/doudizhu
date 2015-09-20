#ifndef DATATYPE
#define DATATYPE

//数据报文的类型(ok)
class DataType
{
public:
    const static int Login=1;           //登陆
    const static int LoginResult=2;     //登陆成败结果
    const static int BroadcastNum=3;    //广播人数
    const static int Progress=4;        //游戏进度
    const static int Origin=5;          //初始牌面
    const static int Who=6;             //轮谁出牌
    const static int Cards=7;           //出牌信息
    const static int ActionFeedback=8;  //出牌成败结果
    const static int EnterRoom=9;       //进入游戏房间
};

#endif
