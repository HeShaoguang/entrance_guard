#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>




TCPServerWidget::TCPServerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCPServerWidget)
{
    ui->setupUi(this);

    setWindowTitle("门禁服务器");

    db = QSqlDatabase::addDatabase("QMYSQL","mainwindow_login");
    //连接数据库
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("guang135792468");
    db.setDatabaseName("entrance_guard");

    //打开数据库
    if(!db.open()){
        QMessageBox::warning(this, "错误",db.lastError().text());
        this->close();
    }

    tcpServer=NULL;
    tcpSocket=NULL;

    tcpServer = new QTcpServer(this);
    tcpServer->listen(QHostAddress("192.168.43.6"),1454);

    connect(tcpServer,&QTcpServer::newConnection,
                [=]()
                {
                    //取出连接好的套接字
                    tcpSocket = tcpServer->nextPendingConnection();
                    //取得对方的IP和断开
                    QString itsip = tcpSocket->peerAddress().toString();
                    qint16 itsport = tcpSocket->peerPort();
                    QString temp = QString("[%1:%2]:成功连接").arg(itsip).arg(itsport);

                    ui->textEditRead->setText(temp);

                    connect(tcpSocket, &QTcpSocket::readyRead,
                            [=]()
                            {
                                QByteArray array = tcpSocket->readAll();
                                ui->textEditRead->append(array);
                                getinformation(array);
                                databasewindow.on_buttonGetnew_clicked();
                            }

                            );
                }

            );
}

TCPServerWidget::~TCPServerWidget()
{
    delete ui;
}

bool TCPServerWidget::checkid(QString checkid)
{
    QString tempid;
    QSqlQuery query(db);
    bool flag = false;
    query.exec("select card_id from student");
    qDebug() << "select card_id from student";
    while(query.next()){
        tempid = query.value(0).toString();
        if(checkid == tempid){
            flag = true;
            break;
        }
    }
    return  flag;
}

QString TCPServerWidget::getid(QString sno)
{
    QString id;
    id = "0not_stu";
    QSqlQuery query(db);
    query.exec("select card_id from student where sno='"+sno+"'");
    qDebug() << "select card_id from student where sno='"+sno+"'";
    while(query.next()){
        id = query.value(0).toString();
    }
    return id;
}

QString TCPServerWidget::gethowlong(QString in_time,QString tempera)
{
    QString howlong1,howlong2;
    QString order1="pass";
    int howlong3,tempera1;
    QSqlQuery query(db);
    query.exec("SELECT TIME_TO_SEC('"+in_time+"')-TIME_TO_SEC(out_time),SEC_TO_TIME(TIME_TO_SEC('"+in_time+"')-TIME_TO_SEC(out_time)) "
                "FROM goout WHERE TIME_TO_SEC(out_time)<=TIME_TO_SEC('"+in_time+"') ORDER BY TIME_TO_SEC(out_time) DESC");
    qDebug() << "SELECT TIME_TO_SEC('"+in_time+"')-TIME_TO_SEC(out_time),SEC_TO_TIME(TIME_TO_SEC('"+in_time+"')-TIME_TO_SEC(out_time)) "
                 "FROM goout WHERE TIME_TO_SEC(out_time)<=TIME_TO_SEC('"+in_time+"') ORDER BY TIME_TO_SEC(out_time) DESC";
    if(query.next()){
        howlong1 = query.value(0).toString();
        howlong2 = query.value(1).toString();
    }else
    {
        howlong1 = "1";
        howlong2 = "00:00:01";
    }

    howlong3 = howlong1.toInt();
    tempera1 = tempera.toInt();
    if(howlong3 > 3)
    {
       order1 = "2time_over";
    }
    if(tempera1>28)
    {
        order1 = "1high_temp";
    }
    if(howlong3 > 3 && tempera1 > 28)
    {
        order1 = "3time_over;high_temp";
    }

    if(order1 == "pass")
    {
        tcpSocket->write(order1.toUtf8().data());
    }else
    {
        tcpSocket->write(order1.toUtf8().data());
    }
    qDebug() << howlong1 <<howlong2 <<order1;

    return howlong2;
}

void TCPServerWidget::getinformation(QByteArray arr)
{
    QString str(arr);
    QString temp,id,time,howlong,temperature,sno;

    //接受到的字符串进行裁剪
    if(str.startsWith("OUT:"))
    {
        temp=str.mid(4);
        id = temp.mid(3,(temp.indexOf(";time.")-3));
        if(checkid(id))
        {
            ui->textEditRead->append(id);
            temp = temp.mid(temp.indexOf(";time."));
            time = temp.mid(6,(temp.indexOf(";temperature.")-6));
            ui->textEditRead->append(time);
            temp = temp.mid(temp.indexOf(";temperature."));
            temperature = temp.mid(13);
            ui->textEditRead->append(temperature);

            QSqlQuery query2(db);
            query2.exec("insert into goout(out_card_id,out_time,out_temperature) values('" + id + "','"+time+"','"+temperature+"')");
            qDebug() << "insert into goout(out_card_id,out_time,out_temperature) values('" + id + "','"+time+"','"+temperature+"')";
        }
        else
        {
           QMessageBox::critical(this,"错误","没有这个id号("+id+")。","确定");
           return;
        }
    }else if(str.startsWith("IN:"))
    {
        temp=str.mid(3);
        id = temp.mid(3,(temp.indexOf(";time.")-3));
        if(checkid(id))
        {
            ui->textEditRead->append(id);
            temp = temp.mid(temp.indexOf(";time."));
            time = temp.mid(6,(temp.indexOf(";howlong.")-6));
            ui->textEditRead->append(time);
            temp = temp.mid(temp.indexOf(";howlong."));
            howlong = temp.mid(9,(temp.indexOf(";temperature.")-9));
            ui->textEditRead->append(howlong);
            temp = temp.mid(temp.indexOf(";temperature."));
            temperature = temp.mid(13);
            ui->textEditRead->append(temperature);

            QSqlQuery query2(db);
            query2.exec("insert into enter(in_card_id,in_time,howlong,in_temperature) values('" + id + "','"+time+"','"+howlong+"','"+temperature+"')");
            qDebug() << "insert into enter(in_card_id,in_time,howlong,in_temperature) values('" + id + "','"+time+"','"+howlong+"','"+temperature+"')";


        }
        else
        {
            QMessageBox::critical(this,"错误","没有这个id号("+id+")。","确定");
            return;
        }

    }else if(str.startsWith("SNOOUT:"))
    {
        temp=str.mid(7);
        sno = temp.mid(4,(temp.indexOf(";time.")-4));
        id = getid(sno);
        if(id == "0not_stu")
        {
            tcpSocket->write(id.toUtf8().data());
        }else
        {
            ui->textEditRead->append(id);
            temp = temp.mid(temp.indexOf(";time."));
            time = temp.mid(6,(temp.indexOf(";temperature.")-6));
            ui->textEditRead->append(time);
            temp = temp.mid(temp.indexOf(";temperature."));
            temperature = temp.mid(13);
            bool ok;
            int temprea = temperature.toInt(&ok);
            QString order;
            if(temprea > 28)
            {
                order = "1high_temp";
                tcpSocket->write(order.toUtf8().data());
            }else
            {
                order = "pass";
                tcpSocket->write(order.toUtf8().data());
            }
            ui->textEditRead->append(temperature);


            QSqlQuery query2(db);
            query2.exec("insert into goout(out_card_id,out_time,out_temperature) values('" + id + "','"+time+"','"+temperature+"')");
            qDebug() << "insert into goout(out_card_id,out_time,out_temperature) values('" + id + "','"+time+"','"+temperature+"')";
        }

    }else if(str.startsWith("SNOIN:"))
    {
        temp=str.mid(6);
        sno = temp.mid(4,(temp.indexOf(";time.")-4));
        id = getid(sno);
        if(id == "0not_stu")
        {
            tcpSocket->write(id.toUtf8().data());
        }else
        {
            ui->textEditRead->append(id);
            temp = temp.mid(temp.indexOf(";time."));
            time = temp.mid(6,(temp.indexOf(";temperature.")-6));
            ui->textEditRead->append(time);
            temp = temp.mid(temp.indexOf(";temperature."));
            temperature = temp.mid(13);
            ui->textEditRead->append(temperature);

            howlong = gethowlong(time,temperature);

            QSqlQuery query2(db);
            query2.exec("insert into enter(in_card_id,in_time,howlong,in_temperature) values('" + id + "','"+time+"','"+howlong+"','"+temperature+"')");
            qDebug() << "insert into enter(in_card_id,in_time,howlong,in_temperature) values('" + id + "','"+time+"','"+howlong+"','"+temperature+"')";
        }
    }else if(str.startsWith("LK:"))
    {
       temp=str.mid(3);
       id = temp.mid(3,(temp.indexOf(";sno.")-3));
       ui->textEditRead->append(id);
       temp = temp.mid(temp.indexOf(";sno."));
       sno = temp.mid(5);
       ui->textEditRead->append(sno);

       QSqlQuery query2(db);
       query2.exec("insert into student(card_id,sno) values('" + id + "','"+sno+"')");
       qDebug() << "insert into student(card_id,sno) values('" + id + "','"+sno+"')";

       QSqlQuery query3(db);
       query3.exec("select card_id from student where sno='"+sno+"'");
       qDebug() << "select card_id from student where sno='"+sno+"'";
       QString idtest;
       while(query3.next()){
           idtest = query3.value(0).toString();
       }

       if(idtest == id)
       {
           QString order4 = "inputsno";
           tcpSocket->write(order4.toUtf8().data());
       }
    }


}

void TCPServerWidget::on_buttonSend_clicked()
{
    if(NULL==tcpSocket)
    {
        return;
    }
    //获取编辑区内容
    QString str = ui->textEditWrite->toPlainText();
    //给对方发送数据
    tcpSocket->write(str.toUtf8().data());
}


void TCPServerWidget::on_buttonShowDB_clicked()
{
    databasewindow.show();
}
