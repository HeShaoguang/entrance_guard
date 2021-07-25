#include "databasewidget.h"
#include "ui_databasewidget.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>


DatabaseWidget::DatabaseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DatabaseWidget)
{
    ui->setupUi(this);

    setWindowTitle("门禁数据统计");

    on_buttonGetnew_clicked();
}

DatabaseWidget::~DatabaseWidget()
{
    delete ui;
}

void DatabaseWidget::on_buttonClose_clicked()
{
    this->close();
}

void DatabaseWidget::on_buttonGetnew_clicked()
{
    QSqlDatabase db2 = QSqlDatabase::addDatabase("QMYSQL");
    //连接数据库
    db2.setHostName("127.0.0.1");
    db2.setUserName("root");
    db2.setPassword("guang135792468");
    db2.setDatabaseName("entrance_guard");

    //打开数据库
    if(!db2.open()){
        QMessageBox::warning(this, "错误",db2.lastError().text());
        return;
    }

    model1 = new MySqlQuery(this);
    model2 = new MySqlQuery(this);

    if(ui->buttonChange->text()=="切换为体温过高人员记录和外出时间过长人员记录")
    {
        model1->setQuery("SELECT out_num,card_id,sno,out_time,out_temperature FROM student,goout "
                       "WHERE student.card_id=goout.out_card_id ORDER BY out_num desc");
        model2->setQuery("SELECT in_num,card_id,sno,in_time,howlong,in_temperature FROM student,enter "
                         "WHERE student.card_id=enter.in_card_id ORDER BY in_num desc");

        ui->tableView1->setModel(model1);
        ui->tableView2->setModel(model2);

        ui->tableView1->setColumnWidth(0,40);
        ui->tableView1->setColumnWidth(1,115);
        ui->tableView1->setColumnWidth(2,120);
        ui->tableView1->setColumnWidth(3,110);
        ui->tableView1->setColumnWidth(4,70);

        ui->tableView2->setColumnWidth(0,40);
        ui->tableView2->setColumnWidth(1,85);
        ui->tableView2->setColumnWidth(2,115);
        ui->tableView2->setColumnWidth(3,80);
        ui->tableView2->setColumnWidth(4,80);
        ui->tableView2->setColumnWidth(5,50);

        model1->setHeaderData(0, Qt::Horizontal, "序号");
        model1->setHeaderData(1, Qt::Horizontal, "卡号");
        model1->setHeaderData(2, Qt::Horizontal, "学号");
        model1->setHeaderData(3, Qt::Horizontal, "外出时间");
        model1->setHeaderData(4, Qt::Horizontal, "体温");

        model2->setHeaderData(0, Qt::Horizontal, "序号");
        model2->setHeaderData(1, Qt::Horizontal, "卡号");
        model2->setHeaderData(2, Qt::Horizontal, "学号");
        model2->setHeaderData(3, Qt::Horizontal, "进门时间");
        model2->setHeaderData(4, Qt::Horizontal, "时间间隔");
        model2->setHeaderData(5, Qt::Horizontal, "体温");

    }else
    {
        model1->setQuery("SELECT all_num,all_card_id,sno,all_out_time,all_in_time,all_howlong,all_temperature FROM student,allrecord "
                        "WHERE student.card_id=allrecord.all_card_id AND all_temperature>=25 ORDER BY all_num DESC");
        model2->setQuery("SELECT in_num,in_card_id,sno,in_time,howlong,TIME_TO_SEC(howlong) FROM enter,student WHERE "
                         "enter.in_card_id=student.card_id AND TIME_TO_SEC(howlong)>20 ORDER BY in_num DESC");

        ui->tableView1->setModel(model1);
        ui->tableView2->setModel(model2);

        ui->tableView1->setColumnWidth(0,30);
        ui->tableView1->setColumnWidth(1,70);
        ui->tableView1->setColumnWidth(2,90);
        ui->tableView1->setColumnWidth(3,70);
        ui->tableView1->setColumnWidth(4,70);
        ui->tableView1->setColumnWidth(5,70);
        ui->tableView1->setColumnWidth(6,55);

        ui->tableView2->setColumnWidth(0,40);
        ui->tableView2->setColumnWidth(1,85);
        ui->tableView2->setColumnWidth(2,95);
        ui->tableView2->setColumnWidth(3,80);
        ui->tableView2->setColumnWidth(4,80);
        ui->tableView2->setColumnWidth(5,70);

        model1->setHeaderData(0, Qt::Horizontal, "序号");
        model1->setHeaderData(1, Qt::Horizontal, "卡号");
        model1->setHeaderData(2, Qt::Horizontal, "学号");
        model1->setHeaderData(3, Qt::Horizontal, "外出时间");
        model1->setHeaderData(4, Qt::Horizontal, "进门时间");
        model1->setHeaderData(5, Qt::Horizontal, "时间间隔");
        model1->setHeaderData(6, Qt::Horizontal, "体温");

        model2->setHeaderData(0, Qt::Horizontal, "序号");
        model2->setHeaderData(1, Qt::Horizontal, "卡号");
        model2->setHeaderData(2, Qt::Horizontal, "学号");
        model2->setHeaderData(3, Qt::Horizontal, "进门时间");
        model2->setHeaderData(4, Qt::Horizontal, "时间间隔");
        model2->setHeaderData(5, Qt::Horizontal, "外出秒数");
    }
}

void DatabaseWidget::on_buttonChange_clicked()
{
    if(ui->buttonChange->text()=="切换为体温过高人员记录和外出时间过长人员记录")
    {
        ui->buttonChange->setText("切换为进门记录和出门记录");
        ui->label1->setText("体温过高人员记录:");
        ui->label2->setText("外出时间过长人员记录:");
    }else{
        ui->buttonChange->setText("切换为体温过高人员记录和外出时间过长人员记录");
        ui->label1->setText("进门记录:");
        ui->label2->setText("出门记录:");
    }
    on_buttonGetnew_clicked();
}
