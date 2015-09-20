#include <QApplication>
#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameWindow gw;
    gw.setWindowTitle("game server");
    gw.show();

    return a.exec();
}
