#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QDataStream>
#include <QIODevice>
#include <QFont>
#include <QDateTime>
#include <QTextCursor>
#include <QHostInfo>
#include <QHostAddress>
#include <QAbstractSocket>
#include <QList>
#include <QNetworkInterface>
#include <QChar>
#include <QPixmap>
#include <QPainter>

ChatWindow::ChatWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWindow)
{
    originWindow();      //配置窗体
    originZb();          //配置笑脸标签
    originInputUser();   //配置临时昵称输入框
    originEnterChat();   //配置进入聊天室按钮
    originUserLabel();   //配置临时用户名输入框的提示标签
    originRoom();        //配置用户列表的显示
    originAllContents(); //配置所有用户的聊天内容显示
    originInputContent();//配置聊天输入框
    originSubmit();      //配置提交聊天内容按钮
    originSocket();      //配置udp套接字
    ui->setupUi(this);
}

/*
 * 析构时发送"我离开了"的消息
 * 因为进行到窗口的析构函数时,子对象都已经被删除,故而不能使用_sender成员进行发送
*/
ChatWindow::~ChatWindow()
{
    QUdpSocket tmpSocket;
    QByteArray bytes=pack_Leave(_username,getIPv4());
    tmpSocket.writeDatagram(bytes,bytes.length(),QHostAddress::Broadcast,_port);
    delete ui;
}

//新用户加入 报文装包
//参数分别为(临时昵称,用户ip)
QByteArray ChatWindow::pack_Come(const QString &user, const QString &ip) const
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<_TypeCome;
    out<<user;
    out<<ip;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//响应用户加入的报文装包
//参数分别为(临时昵称,用户ip)
QByteArray ChatWindow::pack_ResponseCome(const QString &user, const QString &ip) const
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<_TypeResponseCome;
    out<<user;
    out<<ip;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//用户离开 报文装包
//参数分别为(临时昵称,用户ip)
QByteArray ChatWindow::pack_Leave(const QString &user,const QString &ip) const
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<_TypeLeave;
    out<<user;
    out<<ip;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//用户聊天内容 报文装包
//参数分别为(用户的临时昵称,聊天内容)
QByteArray ChatWindow::pack_Talk(const QString &user, const QString &content) const
{
    QByteArray bytes;
    QDataStream out(&bytes,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out<<(quint16)0;
    out<<_TypeTalk;
    out<<user;
    out<<content;
    out.device()->seek(0);
    out<<(quint16)(bytes.size()-sizeof(quint16));
    return bytes;
}

//获取本机ip(ipv4)
QString ChatWindow::getIPv4()const
{
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
        if(address.protocol() == QAbstractSocket::IPv4Protocol)
            return address.toString();
    }
    return "unknown";
}

//昵称是否合法
/*
 * 不能为空
 * 每位必须是 0-9,A-Z,a-z的字符
*/
bool ChatWindow::validUsername(const QString &user) const
{
    int N=user.length();
    if(N==0)
        return false;
    for(int i=0;i<N;i++){
        QChar c=user.at(i);
        if((c>='0'&&c<='9')||(c>='a'&&c<='z')||(c>='A'&&c<='Z'))
        {}
        else
            return false;
    }
    return true;
}

//事件过滤器
/*
 * 若是"Enter Chat Room"按钮被按下:
 * {
 *   若昵称不合法,显示警告信息并清空昵称输入框
 *   反之:
 *   {
 *     记录临时昵称
 *     隐藏此时显示的所有部件,然后显示聊天时该有的所有部件
 *     在聊天内容文本快上添加"我加入了"的消息记录
 *     将自己的昵称和ip加入到昵称表和ip表中
 *     广播"我来了"的消息
 *   }
 * }
 * 若是"Submit"按钮被按下 且 输入的聊天内容不为空:
 * {
 *   在聊天文本快上添加"自己发送了xxx信息"
 *   清空聊天输入框
 *   广播"我发送了xxx"的消息
 * }
*/
bool ChatWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_enterChat && event->type()==QEvent::MouseButtonPress && _inputUser->text()!="")
    {//若是按下 进入聊天室 按钮
        if(validUsername(_inputUser->text()))  //若昵称合法
        {
            _username=_inputUser->text();      //记录临时昵称
            //隐藏 未进入聊天室时候的 所有ui部件
            _zb->hide();
            _userLabel->hide();
            _inputUser->hide();
            _enterChat->hide();
            //显示 进入聊天室后的 所有ui部件
            _label1->setVisible(true);
            _label2->setVisible(true);
            _room->setVisible(true);
            _allContents->setVisible(true);
            _inputContent->setVisible(true);
            _submit->setVisible(true);
            //在聊天内容文本块中添加"我来了"的消息
            updateAllContents("",QString("!report: ").append(_username).append(" join"));
            //将自己的昵称和ip加入到昵称表和ip表中
            addOne(_username,getIPv4());
            //广播"我来了"的消息
            QByteArray bytes=pack_Come(_username,getIPv4());
            _sender->writeDatagram(bytes,bytes.length(),QHostAddress::Broadcast,_port);
        }else{
            //给出提示
            _userLabel->setText("only allow a-z,A-Z,0-9!");
            _userLabel->setStyleSheet("color:#880000");
            //清理输入框内的内容
            _inputUser->clear();
        }
        return true;
    }
    if(obj==_submit && event->type()==QEvent::MouseButtonPress && _inputContent->toPlainText()!="")
    {//若是按下 提交聊天输入 按钮
        //在聊天文本快上添加"自己发送了xxx信息"
        QString str=_inputContent->toPlainText();
        updateAllContents("[self]",str);
        //清空聊天输入框
        _inputContent->clear();
        //广播"我发送了xxx"的消息
        QByteArray bytes=pack_Talk(_username,str);
        _sender->writeDatagram(bytes,bytes.length(),QHostAddress::Broadcast,_port);
        return true;
    }
    return QWidget::eventFilter(obj,event);
}

//配置窗体属性
void ChatWindow::originWindow()
{
    setFixedSize(300,600);
}

//绘制事件(设置窗口的背景)
void ChatWindow::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/image/res/bgp.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//配置笑脸标签(一开始时候的 呵呵微笑标签)
void ChatWindow::originZb()
{
    _zb=new QLabel(this);
    _zb->setGeometry(10,10,280,190);
    QFont font;font.setPointSize(150);font.setBold(true);
    _zb->setFont(font);
    _zb->setAlignment(Qt::AlignCenter);
    _zb->setText("☺");
    _zb->setStyleSheet("color:#00ff00");
}

//配置临时用户名输入框的提示标签的属性
void ChatWindow::originUserLabel()
{
    _userLabel=new QLabel(this);
    _userLabel->setGeometry(20,230,260,50);
    QFont font;font.setPointSize(15);font.setBold(true);
    _userLabel->setFont(font);
    _userLabel->setText("input username to chat");
    _userLabel->setStyleSheet("color:#e8e8e8");
}

//配置临时昵称输入框属性
void ChatWindow::originInputUser()
{
    _inputUser=new QLineEdit(this);
    _inputUser->setGeometry(20,320,260,50);
    _inputUser->setMaxLength(8);
    QFont font;font.setPointSize(20);font.setBold(true);
    _inputUser->setFont(font);
    _inputUser->setAlignment(Qt::AlignCenter);
    _inputUser->setStyleSheet("background-color:#ffffff;color:#00bfff");
}

//配置进入聊天室按钮的属性
void ChatWindow::originEnterChat()
{
    _enterChat=new QPushButton(this);
    _enterChat->setGeometry(20,450,260,80);
    QFont font;font.setPointSize(20);font.setBold(true);
    _enterChat->setFont(font);
    _enterChat->setText("Enter Chat Room");
    _enterChat->setStyleSheet("background-color:#333333;color:#ffffff");
    _enterChat->setCursor(Qt::PointingHandCursor);
    _enterChat->installEventFilter(this);
}

//配置用户列表显示ui的属性
void ChatWindow::originRoom()
{
    _room=new QTextBrowser(this);
    _room->setGeometry(0,30,300,140);
    QFont font;font.setPointSize(10);font.setBold(true);
    _room->setFont(font);
    _room->setStyleSheet("background-color:#333333;color:#ffffff");
    _room->hide();
    font.setPointSize(15);
    _label1=new QLabel(this);
    _label1->setFont(font);
    _label1->setGeometry(0,0,70,31);
    _label1->setText(" User");
    _label1->setStyleSheet("background-color:#333333;color:#00ff00;border-bottom:2px solid #00ff00;border-right:1px solid #00ff00");
    _label1->hide();
    _label2=new QLabel(this);
    _label2->setFont(font);
    _label2->setGeometry(70,0,230,31);
    _label2->setText("  IP");
    _label2->setStyleSheet("background-color:#333333;color:#00ff00;border-bottom:2px solid #00ff00;border-left:1px solid #00ff00");
    _label2->hide();
}

//用户列表ui新增一个聊天者
/*
 * 1.将用户昵称加入昵称表,将ip加入ip表
 * 2.将这个用户的昵称和ip数据添加到ui上
*/
void ChatWindow::addOne(const QString &user, const QString &ip)
{
    //将用户昵称加入昵称表,将ip加入ip表
    _userList.push_back(user);
    _ipList.push_back(ip);
    //将这个用户的昵称和ip数据添加到ui上
    QString ss=user;
    int N=user.length();
    while(N<8)
    {
        ss.append(" ");
        N++;
    }
    ss.append(" ").append(ip).append("\n");
    _room->setText(_room->toPlainText().append(ss));
}

//用户列表ui删去一个聊天者
/*
 * 1.从昵称表中删除user,从ip表中删除ip
 * 2.清空ui上的用户列表,然后根据昵称表和ip表重新往ui上添加聊天室内的用户数据
 * 3.在聊天内容文本快上添加"某某离开了"的消息记录
*/
void ChatWindow::removeOne(const QString &user,const QString &ip)
{
    //从昵称表中删除user,从ip表中删除ip
    int N=static_cast<int>(_ipList.size());
    int index=-1;
    for(int i=0;i<N;i++)
    {
        if(QString(_ipList[i])==ip)
        {
            index=i;
            break;
        }
    }
    if(index!=-1){ //若原表中有这个用户
        _userList.erase(_userList.begin()+index);
        _ipList.erase(_ipList.begin()+index);
        //清空ui上的用户列表,然后根据昵称表和ip表重新往ui上添加聊天室内的用户数据
        _room->clear();
        for(int i=0;i<N-1;i++)
            addOne(_userList[i],_ipList[i]);
    }
    //在聊天内容文本快上添加"某某离开了"的消息记录
    updateAllContents("",QString("!report: ").append(user).append(" leave"));
}

//配置所有用户的聊天内容显示的属性
void ChatWindow::originAllContents()
{
    _allContents=new QTextBrowser(this);
    _allContents->setGeometry(0,169,300,350);
    QFont font;font.setPointSize(12);font.setBold(true);
    _allContents->setFont(font);
    _allContents->setStyleSheet("border:2px solid #e8e8e8;background-color:#ffffff;color:#333333");
    connect(_allContents,SIGNAL(cursorPositionChanged()),this,SLOT(autoScroll()));
    _allContents->hide();
}

//聊天内容文本块的自动滚动槽
void ChatWindow::autoScroll()
{
    _allContents->moveCursor(QTextCursor::End);
}

//聊天内容显示框的更新
/*
 * 参数分别为(用户,内容)
 * 添加"某某 x时x分x秒 说了什么什么话"的消息 到 聊天文本块
*/
void ChatWindow::updateAllContents(const QString &user, const QString &str)
{
    QDateTime time=QDateTime::currentDateTime();
    QString ss=QString("").append(user).append(" ");
    ss.append(time.toString("hh:mm:ss")).append("\n");
    ss.append(str).append("\n\n");
    _allContents->setText(_allContents->toPlainText().append(ss));
}

//配置聊天输入框的属性
void ChatWindow::originInputContent()
{
    _inputContent=new QTextEdit(this);
    _inputContent->setGeometry(0,518,220,80);
    QFont font;font.setPointSize(12);font.setBold(true);
    _inputContent->setFont(font);
    _inputContent->setStyleSheet("background-color:#e8e8e8;border-top:2px solid");
    _inputContent->setPlaceholderText("input here");
    _inputContent->hide();
}

//配置提交聊天内容按钮的属性
void ChatWindow::originSubmit()
{
    _submit=new QPushButton(this);
    _submit->setGeometry(220,518,80,80);
    QFont font;font.setPointSize(15);font.setBold(true);
    _submit->setFont(font);
    _submit->setText("Submit");
    _submit->setStyleSheet("background-color:#000000;color:#ffffff");
    _submit->setCursor(Qt::PointingHandCursor);
    _submit->hide();
    _submit->installEventFilter(this);
}

//配置udp套接字
void ChatWindow::originSocket()
{
    _port=3998;
    _sender=new QUdpSocket(this);
    _receiver=new QUdpSocket(this);
    _receiver->bind(_port,QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(_receiver,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
}

//收到udp数据的槽
/*1. 收到come报文:
 *   { 加入用户列表,返回receiveCome报文 }
 *2. 收到receiveCome报文:
 *   { 将对方用户名和ip加入用户列表 }
 *3. 收到leave报文:
 *   { 根据对方ip从用户列表去除 }
 *4. 收到talk报文:
 *   { 更新聊天内容 }
*/
void ChatWindow::onReadyRead()
{
    QByteArray bytes;
    bytes.resize(_receiver->pendingDatagramSize());
    _receiver->readDatagram(bytes.data(),bytes.size());
    QDataStream in(&bytes,QIODevice::ReadOnly);
    quint16 size; int type;
    in>>size>>type;
    switch(type)
    {
    case _TypeCome:{
        //收到 某人进入聊天室的消息
        QString user,ip;
        in>>user>>ip;
        if(ip!=getIPv4()){
            //不把本机加入聊天室的消息再次显示到聊天文本块
            //不然就显示两次了
            updateAllContents("",QString("!report: ").append(user).append(" join"));
            addOne(user,ip);
            QByteArray response=pack_ResponseCome(_username,getIPv4());
            _sender->writeDatagram(response,response.length(),QHostAddress::Broadcast,_port);
        }
        break;
    }
    case _TypeResponseCome:{
        //收到 某人响应你的进入 的消息(因为你进入聊天室时会广播消息给所有人)
        QString user,ip;
        in>>user>>ip;
        int N=static_cast<int>(_ipList.size());
        int index=-1;
        for(int i=0;i<N;i++)
        {
            if(QString(_ipList[i])==ip)
            {
                index=i;
                break;
            }
        }
        if(index==-1)
            addOne(user,ip);
        break;
    }
    case _TypeLeave:{
        //收到某人离开聊天室的消息
        QString user,ip;
        in>>user>>ip;
        if(user!="")
            removeOne(user,ip);
        break;
    }
    case _TypeTalk:{
        //收到某人说了什么话的消息
        QString user,str;
        in>>user>>str;
        if(user!=_username)
            updateAllContents(user,str);
        break;
    }
    }
    //递归接收消息
    if(_receiver->pendingDatagramSize()>0)
        onReadyRead();
}
