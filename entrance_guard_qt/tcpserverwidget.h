#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QString>
#include "databasewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TCPServerWidget; }
QT_END_NAMESPACE

class TCPServerWidget : public QWidget
{
    Q_OBJECT

public:
    TCPServerWidget(QWidget *parent = nullptr);
    ~TCPServerWidget();

   void getinformation(QByteArray arr);

   bool checkid(QString checkid);

   QString getid(QString sno);
   QString gethowlong(QString in_time,QString tempera);

private slots:
   void on_buttonSend_clicked();

   void on_buttonShowDB_clicked();

private:
    Ui::TCPServerWidget *ui;

    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;

    QSqlDatabase db;

    DatabaseWidget databasewindow;
};
#endif // TCPSERVERWIDGET_H
