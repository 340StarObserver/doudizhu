#ifndef ROBOT_H
#define ROBOT_H

#include <QWidget>
#include <QThread>
#include "wanjia.h"
#include "method.h"


class Robot:public Player
{
public:
    Robot(QWidget* parent);
    void beginPlayingHand();
    void beginCallingLord();
};

#endif // ROBOT_H
