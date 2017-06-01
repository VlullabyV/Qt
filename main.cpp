#include "ex1.h"
#include <QApplication>
#include <QtNetwork/QUdpSocket>
//Qt5新写法
#include<QtNetwork/QHostAddress>


int main(int argc, char *argv[])
{   
    QApplication a(argc, argv);
    ex1 w;
    w.show();
    return a.exec();
}
