#include "tcpserverwidget.h"
#include "databasewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TCPServerWidget w1;
    w1.show();

    return a.exec();
}
