#include <QApplication>
#include "index.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Index w;
    w.setWindowTitle("首页");
    w.show();

    return a.exec();
}
