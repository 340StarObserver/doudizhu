#ifndef UNIVERSAL_H
#define UNIVERSAL_H
#include <QString>
#include <QFile>

#include <QString>
#include <QSqlDatabase>

class universal
{
public:
    universal();
        static double setpix;//设置屏幕分辨率（800*600的倍数）
        static int diff;//难度设置（0为最简单）
        static bool debugmode;//（debug模式开关）
        static bool windowed;//是否全屏
        static int eecount;//彩蛋（开启高级模式，解锁舰C主题与WA主题，东大主题加入SSAA，允许Debug模式，全屏模式，技能模式）
        static QString theme;//主题设置
        static bool _skills;//技能开关
        static int skill1;//技能1
        static int skill2;//技能2
        static int skill3;//技能3
        //static bool automatic;
        static QString playera;//农民图标
        static QString playerd;//地主图标
        static QString bgp;//背景图片
        static QString mclock;//计时器图片
        static bool SingleRole;//单人战役变量
        static QFile *save;//存档
        static int mission;//任务计数器
        static int mistemp;
        static int scores;
        static int streak;
        static bool loaddb;
};

#endif // UNIVERSAL_H
