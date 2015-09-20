#include <QApplication>
#include "registwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    RegistWindow w;
    w.setWindowTitle("regist server monitor");
    w.show();

    return a.exec();
}
