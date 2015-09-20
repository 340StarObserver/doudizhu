#include "maingame.h"
#include "ui_maingame.h"
#include "clientsocket.h"
#include "index.h"
#include <QPixmap>
#include <QPainter>
#include <QMessageBox>

Maingame::Maingame(int playerID,int head,const QString& user,const QString& pwd,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Maingame)
{
    //配置非ui成员的属性:
    originSelf(playerID%3,head%3,user,pwd);//配置[自己]的编号,头像,用户名,密码
    _canChooseCard=false;                  //一开始无法选中自己的手牌
    _canAction=false;                      //一开始无法点击 出牌按钮
    _canGiveUp=false;                      //一开始无法点击 弃权按钮
    _isFirstChupai=true;                   //是第一次出牌(用来在客户端限制地主一开始弃权过)
    //配置ui成员的属性:
    originWindow();               //初始化窗体
    originStartWar();             //初始化开战标签
    originWaitLabel();            //初始化等待玩家xx出牌标签
    originActLabel();             //初始化出牌成功失败的标签
    originChatWindow();           //初始化聊天栏
    originInfoWindows();          //初始化玩家信息栏
    originOps();                  //初始化操作栏
    originCardLabels();           //初始化手牌标签
    originCardLists();            //初始化三人的出牌区
    originMusic();                //初始化音乐
    originTimer();                //初始化时间控制器和显示标签
    originSocket();               //配置套接字
    ui->setupUi(this);
}

Maingame::~Maingame()
{
    delete ui;
}

//配置[自己]的编号和头像代号
void Maingame::originSelf(int playerID,int head,const QString& user,const QString& pwd)
{
    _self.setID(playerID);
    _self.setHead(head);
    _self.set_User(user);
    _self.set_Pwd(pwd);
}

//初始化窗体的属性
void Maingame::originWindow()
{
    setFixedSize(1024,600);
}

//配置背景
void Maingame::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/image/res/bgp.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//初始化开战标签
void Maingame::originStartWar()
{
    _startWar=new QLabel(this);
    _startWar->setGeometry(240,120,260,200);
    _startWar->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(60);
    font.setBold(true);
    _startWar->setFont(font);
    _startWar->setStyleSheet("color:#880000");
    _startWar->setText("开†战");
    _startWar->hide();
}

//隐藏"开战"标签的槽
void Maingame::hideStartWarLabel()
{
    _startWar->hide();
}

//初始化等待玩家xx出牌标签
void Maingame::originWaitLabel()
{
    _waitLabel=new QLabel(this);
    _waitLabel->setGeometry(262,50,200,40);
    _waitLabel->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    _waitLabel->setFont(font);
    _waitLabel->setStyleSheet("color:#e8e8e8");
    _waitLabel->hide();
}

//初始化出牌成功失败的标签
void Maingame::originActLabel()
{
    QFont font;
    font.setPointSize(15);
    font.setBold(true);
    //配置 出牌成功标签 的属性
    _actSuccessLabel=new QLabel(this);
    _actSuccessLabel->setGeometry(220,435,164,30);
    _actSuccessLabel->setAlignment(Qt::AlignCenter);
    _actSuccessLabel->setFont(font);
    _actSuccessLabel->setStyleSheet("color:#e8e8e8");
    _actSuccessLabel->setText("出牌成功");
    _actSuccessLabel->hide();
    //配置 出牌失败标签 的属性
    _actFailedLabel=new QLabel(this);
    _actFailedLabel->setGeometry(220,435,164,30);
    _actFailedLabel->setAlignment(Qt::AlignCenter);
    _actFailedLabel->setFont(font);
    _actFailedLabel->setStyleSheet("color:#e8e8e8");
    _actFailedLabel->setText("出牌失败");
    _actFailedLabel->hide();
    //配置 其他人出牌成败标签 的属性
    _otherChupai=new QLabel(this);
    _otherChupai->setGeometry(262,50,200,40);
    _otherChupai->setAlignment(Qt::AlignCenter);
    _otherChupai->setFont(font);
    _otherChupai->setStyleSheet("color:#e8e8e8");
    _otherChupai->hide();
}

//隐藏"出牌成功"标签的槽
void Maingame::hideActSuccessLabel()
{
    _actSuccessLabel->hide();
}

//隐藏"出牌失败"标签的槽
void Maingame::hideActFailedLabel()
{
    _actFailedLabel->hide();
}

//隐藏他人出牌反馈标签的槽
void Maingame::hideOtherChupai()
{
    _otherChupai->hide();
}

//初始化聊天栏的属性
void Maingame::originChatWindow()
{
    QLabel * chatback=new QLabel(this);
    chatback->setGeometry(724,0,300,600);
    chatback->setStyleSheet("background-color:#999999");
    _chatwindow=new ChatWindow(this);
    _chatwindow->move(724,0);
}

//初始化玩家信息栏的属性
void Maingame::originInfoWindows()
{
    for(int i=0;i<3;i++)
    {
        _infowindows[i]=new InfoItem(this);
        _box[i]=new QLabel(this);
    }
    int index=_self.getID();
    //_box[i]为信息栏的外围边框
    _box[index]->setGeometry(604,420,120,180);
    _box[(index+1)%3]->setGeometry(504,0,120,180);
    _box[(index+2)%3]->setGeometry(100,0,120,180);
    //设置自己那个信息栏中的编号和头像
    _infowindows[index]->setID(index);
    _infowindows[index]->setHead(_self.getHead());
    //设置三个玩家的信息栏的位置
    _infowindows[index]->move(604,420);
    _infowindows[(index+1)%3]->move(504,0);
    _infowindows[(index+2)%3]->move(100,0);
}

//初始化操作栏
void Maingame::originOps()
{
    //操作栏背景:
    QLabel * opback=new QLabel(this);
    opback->setGeometry(0,420,604,50);
    opback->setStyleSheet("border-top:1px solid #e8e8e8");
    QFont font; font.setPointSize(12);
    //出牌按钮:
    _action=new QPushButton(this);
    _action->setGeometry(90,435,90,30);
    _action->setText("出牌");
    _action->setFont(font);
    _action->installEventFilter(this);
    _action->hide();
    //弃权过按钮:
    _giveUp=new QPushButton(this);
    _giveUp->setGeometry(424,435,90,30);
    _giveUp->setText("弃权");
    _giveUp->setFont(font);
    _giveUp->installEventFilter(this);
    _giveUp->hide();
}

//初始化手牌标签
/*
 * 一开始就创建好20个卡牌标签,并设置每个的位置,隐藏它们
 * //  这样一来之后要显示那张牌,只要更换图片并让它可视就行了,不必重新渲染
 * 设置每张卡牌标签的事件监听
*/
void Maingame::originCardLabels()
{
    for(int i=0;i<20;i++)
    {
        _cardLabels[i]=new QLabel(this);
        _cardLabels[i]->setGeometry(25*i,495,CardList::_WCard,CardList::_HCard);
        _cardLabels[i]->hide();
        _cardLabels[i]->installEventFilter(this);
    }
}

//初始化三人的出牌区
void Maingame::originCardLists()
{
    for(int i=0;i<3;i++)
        _cardlist[i]=new CardList(this);
    int index=_self.getID();
    _cardlist[index]->move(227,310);
    _cardlist[(index+1)%3]->move(454,185);
    _cardlist[(index+2)%3]->move(0,185);
}

//初始化音乐
void Maingame::originMusic()
{
    _musicLabel=new QLabel(this);
    _musicLabel->setGeometry(347,15,30,30);
    _musicLabel->setPixmap(QPixmap(":/image/res/pause.png"));
    _musicLabel->installEventFilter(this);
    _music.setGameSound();
    _music.Bgm->play();
    _music.Bgm->setLoops(QSound::Infinite);
    _isPlayingMusic=true;
}

//初始化出牌时间控制器和显示标签
void Maingame::originTimer()
{
    _timer=new QTimer(this);
    connect(_timer,SIGNAL(timeout()),this,SLOT(on_timer()));
    _restSeconds=30;
    _timerLabel=new QLabel(this);
    _timerLabel->setGeometry(330,360,50,50);
    QFont font;
    font.setPointSize(25);
    font.setBold(true);
    _timerLabel->setFont(font);
    _timerLabel->setAlignment(Qt::AlignCenter);
    _timerLabel->hide();
}

//每秒执行一次的倒计时槽
/*
 * 若还有剩余时间:
 * {
 *    时间减一并更新标签
 *    若时间不足5秒,更换字体颜色
 * }
 * 反之,停止倒计时并隐藏倒计时标签
*/
void Maingame::on_timer()
{
    if(_restSeconds>0)
    {
        _restSeconds--;
        _timerLabel->setText(QString::number(_restSeconds));
        if(_restSeconds<=5)
            _timerLabel->setStyleSheet("color:#ff8833");
    }
    else
        stopDaojishi();
}

//启动倒计时
void Maingame::startDaojishi()
{
    _restSeconds=30;
    _timerLabel->setStyleSheet("color:#003300");
    _timerLabel->setText("30");
    _timerLabel->setVisible(true);
    _timer->start(1000);
}

//停止倒计时 并 隐藏倒计时标签
void Maingame::stopDaojishi()
{
    _timer->stop();
    _timerLabel->hide();
}

//----------------------------------------

//更新我方区域
/*
 *1. 更新手牌的显示
 *2. 更新自己的剩余手牌数量
 *3. 更新自己信息栏中的剩余手牌数标签
*/
void Maingame::reDrawMyRegion()
{
    //先让所有牌都隐藏 并 回到没有弹出的状态
    for(int i=0;i<20;i++)
    {
        _cardLabels[i]->hide();
        _cardLabels[i]->move(25*i,495);
    }
    //然后循环设置手牌中每张牌对应的标签的图片 并 将其可视
    int N=static_cast<int>(_self.getMyCards()->size());
    for(int i=0;i<N;i++)
    {
        _cardLabels[i]->setPixmap(CardList::pictureShot(_self.getMyCards()->at(i)));
        _cardLabels[i]->setVisible(true);
    }
    //更新剩余手牌数
    _eachCardNum[_self.getID()]=N;
    _infowindows[_self.getID()]->setRestCardNum(N);
}

//事件过滤器
/*
 * if 事件源对象是 出牌按钮:
 * {
 *    if 选择要出的牌 为空:
 *       弹出"请先选择要出的牌"对话框
 *    else if 该按钮可用:
 *    {
 *       停止出牌倒计时并隐藏
 *       设置按钮为不可用
 *       设置出牌按钮不可用,弃权按钮不可用,无法点击手牌
 *       发送出牌请求
 *    }
 * }
 * if 事件源对象是 弃权按钮 且该按钮可用
 * {
 *    if 是地主的一开始就弃权
 *       提示地主一开始不能弃权
 *    else:
 *    {
 *       停止出牌倒计时并隐藏
 *       设置按钮为不可用
 *       设置出牌按钮不可用,弃权按钮不可用,无法点击手牌
 *       清空尝试出的牌
 *       发送弃权请求
 *    }
 * }
 * if 事件源对象是 音乐开关标签:
 * {
 *    若当前正播放音乐:{ 停止背景音乐, 设置音乐开关的图像是"打开" }
 *    反之:{ 开启背景音乐, 设置音乐开关的图像是"关闭" }
 *    是否正在播放音乐的标志取反
 * }
 * if 事件源对象是 手牌[i] 且当前可以点击卡牌
 * {
 *    若它相对于父窗口的y轴坐标是495:
 *    {
 *       设置它的y坐标是480(卡牌向上弹出一点点)
 *       将此牌加入 尝试出的牌中
 *    }
 *    反之:
 *    {
 *       设置它的y坐标是495(卡牌向下还原为 未选中状态)
 *       从 尝试出的牌中 移除此牌
 *    }
 * }
*/
bool Maingame::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == _action && event->type()==QEvent::MouseButtonPress)
    {
        if(_self.getTryOut()->size() == 0)
            QMessageBox::warning(this,"warn","please choose cards you want to play",QMessageBox::Ok);
        else if(_canAction)
        {
            stopDaojishi();
            _isFirstChupai=false;
            _canAction=false;
            _canGiveUp=false;
            _canChooseCard=false;
            ClientSocket::getInstance()->sendChupai(_self.getID(),_self.getTryOut()->size(),_self.getValues());
        }
        return true;
    }
    if(obj == _giveUp && event->type()==QEvent::MouseButtonPress && _canGiveUp)
    {
        if(_isFirstChupai && _self.getID()==0)
        {
            QMessageBox::warning(this,"warn","地主一开始不能弃权!",QMessageBox::Ok);
        }
        else
        {
            stopDaojishi();
            _isFirstChupai=false;
            _canAction=false;
            _canGiveUp=false;
            _canChooseCard=false;
            _self.getTryOut()->clear();
            ClientSocket::getInstance()->sendChupai(_self.getID(),0,_self.getValues());
        }
        return true;
    }
    if(obj == _musicLabel && event->type()==QEvent::MouseButtonPress)
    {
        if(_isPlayingMusic)
        {
            _music.Bgm->stop();
            _musicLabel->setPixmap(QPixmap(":/image/res/play.png"));
            _isPlayingMusic=false;
        }
        else
        {
            _music.Bgm->play();
            _musicLabel->setPixmap(QPixmap(":/image/res/pause.png"));
            _isPlayingMusic=true;
        }
        return true;
    }
    for(int i=0;i<20;i++)
    {
        if(obj == _cardLabels[i] && event->type()==QEvent::MouseButtonPress && _canChooseCard)
        {
            if(_cardLabels[i]->pos().y() == 495)
            {
                _cardLabels[i]->move(25*i,480);
                _self.addOneToTryOut(i);
            }
            else
            {
                _cardLabels[i]->move(25*i,495);
                _self.rmOneFromTryOut(i);
            }
            return true;
        }
    }
    return QDialog::eventFilter(obj,event);
}

//----------------------------------------

//配置套接字
/*
 * 获取单例的ClientSocket对象
 * 关联:
 * {
 *   report_BroadCastNum(int,vector<int>&,vector<int>&)信号
 *   report_Progress(bool,int)信号
 *   report_Origin(int,int,vector<int>&)信号
 *   report_Who(int)信号
 *   report_Cards(int,int,vector<int>&)信号
 *   report_ActionFd(bool)信号
 * }
 * 发送enterRoom请求
*/
void Maingame::originSocket()
{
    ClientSocket * cs=ClientSocket::getInstance();
    connect(cs,SIGNAL(report_BroadcastNum(int,vector<int>,vector<int>)),this,SLOT(receive_BroadCastNum(int,vector<int>,vector<int>)));
    connect(cs,SIGNAL(report_Progress(bool,int)),this,SLOT(receive_Progress(bool,int)));
    connect(cs,SIGNAL(report_Origin(int,int,vector<int>)),this,SLOT(receive_Origin(int,int,vector<int>)));
    connect(cs,SIGNAL(report_Who(int)),this,SLOT(receive_Who(int)));
    connect(cs,SIGNAL(report_Cards(int,int,vector<int>)),this,SLOT(receive_Cards(int,int,vector<int>)));
    connect(cs,SIGNAL(report_ActionFd(bool)),this,SLOT(receive_ActionFd(bool)));
    cs->sendEnterRoom(_self.getID());
}

//处理 广播人数的消息
/*
 * 先还原三个玩家的编号和头像为初始状态(参数填-1)
 * 再根据参数设置对应玩家的编号和头像
*/
void Maingame::receive_BroadCastNum(int num, const vector<int> &ids, const vector<int> &heads)
{
    for(int i=0;i<3;i++)
    {
        _infowindows[i]->setID(-1);
        _infowindows[i]->setHead(-1);
    }
    for(int i=0;i<num;i++)
    {
        _infowindows[ids[i]%3]->setID(ids[i]%3);
        _infowindows[ids[i]%3]->setHead(heads[i]%3);
    }
}

//处理 游戏进度的消息
/*
 * 若 state == true(即游戏开始):
 * {
 *    显示"开战"标签
 *    设置单次的计时器,3秒后隐藏
 * }
 * 反之:
 * {
 *    创建游戏结束界面
 *    关联用户的选择(继续游戏or离开游戏)
 * }
*/
void Maingame::receive_Progress(bool state, int winnerID)
{
    if(state)
    {
        _startWar->setVisible(true);
        QTimer::singleShot(3000,this,SLOT(hideStartWarLabel()));
    }
    else
    {
        _frame=NULL;
        if(winnerID==_self.getID() || winnerID*_self.getID()!=0)
            _frame=new GameOverFrame(true,this);
        else
            _frame=new GameOverFrame(false,this);
        _frame->move(172,200);
        connect(_frame,SIGNAL(report_Choose(bool)),this,SLOT(on_choose(bool)));
        _frame->show();
    }
}

//处理 胜负子窗口中 用户的选择(again or exit)的信号 的槽
void Maingame::on_choose(bool res)
{
    //删除胜负子窗口
    GameOverFrame * tmp=_frame;
    tmp->deleteLater();
    _frame=NULL;
    //还原游戏界面为最开始的初始状态
    restore();
    //然后判断:
    //若用户选择again,则关联登陆结果信号 并 发送登陆请求
    //反之关闭界面
    if(res)
    {
        connect(ClientSocket::getInstance(),SIGNAL(report_LoginResult(bool,int,int)),this,SLOT(on_continue(bool,int,int)));
        ClientSocket::getInstance()->sendLogin(_self.get_User(),_self.get_Pwd());
    }
    else
    {
        close();
    }
}

//处理继续游戏时候的登陆结果信号 的槽
/*
 * 若登陆成功:
 * {
 *    设置界面上的一些成员
 *    发送进入游戏房间的请求
 * }
 * 反之,关闭界面
*/
void Maingame::on_continue(bool res, int playerID, int head)
{
    if(res)
    {
        originSelf(playerID,head,_self.get_User(),_self.get_Pwd());
        _infowindows[playerID]->setID(playerID);
        _infowindows[playerID]->setHead(head);
        int index=playerID;
        _cardlist[index]->move(227,310);
        _cardlist[(index+1)%3]->move(454,185);
        _cardlist[(index+2)%3]->move(0,185);
        _box[index]->setGeometry(604,420,120,180);
        _box[(index+1)%3]->setGeometry(504,0,120,180);
        _box[(index+2)%3]->setGeometry(100,0,120,180);
        _infowindows[index]->move(604,420);
        _infowindows[(index+1)%3]->move(504,0);
        _infowindows[(index+2)%3]->move(100,0);
        ClientSocket::getInstance()->sendEnterRoom(playerID);
    }
    else
        close();
}

//还原游戏界面为一开始的初始状态
void Maingame::restore()
{
    _startWar->hide();
    _waitLabel->hide();
    _actSuccessLabel->hide();
    _actFailedLabel->hide();
    _otherChupai->hide();
    _action->hide();
    _giveUp->hide();
    for(int i=0;i<3;i++)
    {
        _box[i]->setStyleSheet("border:0px solid");
        _infowindows[i]->restore();
        _cardlist[i]->clearAll();
        _eachCardNum[i]=0;
    }
    for(int i=0;i<20;i++)
    {
        _cardLabels[i]->hide();
        _cardLabels[i]->move(25*i,495);
    }
    _isFirstChupai=true;
    _canChooseCard=false;
    _canAction=false;
    _canGiveUp=false;
}

//处理 初始牌面的消息
/*
 * 1. 将自己的手牌设置为cards
 * 2. 根据自己的手牌更新自己的手牌区
 * 3. _infowindows[landlordID]中的身份标签设置为地主,剩余牌数标签设置为20
 *    _eachCardNum[landlordID]的值为20
 * 4. _infowindows[(landlordID+1)%3]的身份标签设置为农民,剩余牌数标签设置为17
 *    _eachCardNum[(landlordID+1)%3]的值为17
 *    _infowindows[(landlordID+2)%3]的身份标签设置为农民,剩余牌数标签设置为17
 *    _eachCardNum[(landlordID+2)%3]的值为17
*/
void Maingame::receive_Origin(int landlordID, int num, const vector<int> &cards)
{
    _self.setCards(cards);
    reDrawMyRegion();
    _infowindows[landlordID%3]->setIdentify(true);
    _infowindows[landlordID%3]->setRestCardNum(20);
    _eachCardNum[landlordID%3]=20;
    _infowindows[(landlordID+1)%3]->setIdentify(false);
    _infowindows[(landlordID+1)%3]->setRestCardNum(17);
    _eachCardNum[(landlordID+1)%3]=17;
    _infowindows[(landlordID+2)%3]->setIdentify(false);
    _infowindows[(landlordID+2)%3]->setRestCardNum(17);
    _eachCardNum[(landlordID+2)%3]=17;
}

//处理 轮谁出牌的消息
/*
 * 设置对应玩家的信息栏的边框不同于其他人
 * 若轮到自己出牌:
 * {
 *   清空自己上轮的出牌区中的牌
 *   显示 出牌按钮 和 弃权按钮,并回复它们为可用
 *   恢复手牌为可以选中
 *   开始出牌倒计时
 * }
 * 反之:
 * {
 *   显示"等待玩家xx出牌"标签
 *   隐藏 出牌按钮 和 弃权按钮,并设置它们为不可用
 *   设置手牌为不可选中
 * }
*/
void Maingame::receive_Who(int who)
{
    for(int i=0;i<3;i++)
        _box[i]->setStyleSheet("border:0px solid");
    _box[who%3]->setStyleSheet("border:3px solid #111111");
    if(who == _self.getID())
    {
        _cardlist[_self.getID()]->clearAll();
        _action->setVisible(true);
        _giveUp->setVisible(true);
        _canChooseCard=true;
        _canAction=true;
        _canGiveUp=true;
        startDaojishi();
    }
    else
    {
        _waitLabel->setText(QString("等待玩家").append(QString::number(who)).append("出牌"));
        _waitLabel->setVisible(true);
        _action->hide();
        _giveUp->hide();
        _canChooseCard=false;
        _canAction=false;
        _canGiveUp=false;
    }
}

//处理 某人出牌成功的消息
/*
 * 隐藏"等待玩家xx出牌"标签
 * 更新那人的出牌区
 * 若 playerID和自己的不同
 * {
 *    if num==0: 显示"玩家xx弃权过"标签
 *    else: 显示"玩家xx出牌成功"标签
 *    3秒后让标签消失
 *    若 num 大于零:{
 *       更新_eachCardNum[playerID]
 *       更新_infowindows[playerID]中的剩余手牌数标签
 *    }
 * }
*/
void Maingame::receive_Cards(int playerID, int num, const vector<int> &cards)
{
    _waitLabel->hide();
    _cardlist[playerID%3]->update(cards);
    if(playerID != _self.getID())
    {
        QString str=QString("玩家").append(QString::number(playerID));
        if(num == 0)
            str.append("弃权过");
        else
            str.append("出牌成功");
        _otherChupai->setText(str);
        QTimer::singleShot(3000,this,SLOT(hideOtherChupai()));
        if(num > 0)
        {
            _eachCardNum[playerID%3]=_eachCardNum[playerID%3]-num;
            _infowindows[playerID%3]->setRestCardNum(_eachCardNum[playerID%3]);
        }
    }
}

//处理 自己出牌成败反馈的消息
/*
 * 若 res==true:
 * {
 *    调用Player对象的actionSuccess方法(出牌成功,从手牌中移除尝试出的牌)
 *    根据手牌更新手牌区的显示
 *    显示"出牌成功"标签,并于3秒后消失
 * }
 * 反之:
 * {
 *    调用Player对象的actionFailed方法(出牌失败,将尝试出的牌重新放进手牌)
 *    根据手牌更新手牌区的显示
 *    显示"出牌失败"标签,并于3秒后消失
 *    恢复 出牌按钮,弃权按钮,卡牌标签 为 可以点击
 *    重新开始出牌倒计时
 * }
*/
void Maingame::receive_ActionFd(bool res)
{
    if(res)
    {
        _self.actionSuccess();
        reDrawMyRegion();
        _actSuccessLabel->setVisible(true);
        QTimer::singleShot(3000,this,SLOT(hideActSuccessLabel()));
    }
    else
    {
        _self.actionFailed();
        reDrawMyRegion();
        _actFailedLabel->setVisible(true);
        QTimer::singleShot(3000,this,SLOT(hideActFailedLabel()));
        _canAction=true;
        _canGiveUp=true;
        _canChooseCard=true;
        startDaojishi();
    }
}
