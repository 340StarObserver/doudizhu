#ifndef GAMESOUND_H
#define GAMESOUND_H
#include<QSound>
//声音类

//（注释的都有，但是都加载的话暂时太慢，测试的时候就先注释了）
class GameSound
{
public:
    GameSound();
    void setGameSound();
    QSound *Bgm;
//    QSound *baojing1;
//    QSound *baojing2;
//    QSound *boom;
//    QSound *buyao;
//    QSound *calllord;
//    QSound *dani;
//    QSound *dawang;
//    QSound *feiji;
//    QSound *givecard;
//    QSound *liandui;
//    QSound *notorder;
//    QSound *plane;
//    QSound *sandaiyi;
//    QSound *sandaiyidui;
    QSound *sendcard;
//    QSound *shunzi;
//    QSound *sidaier;
//    QSound *sidailiangdui;
//    QSound *wangzha;
//    QSound *xiaowang;
//    QSound *yaobuqi;
//    QSound *zhadan;
};

#endif // GAMESOUND_H
