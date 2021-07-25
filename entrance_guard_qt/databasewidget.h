#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQueryModel>
#include <mysqlquery.h>



namespace Ui {
class DatabaseWidget;
}

class DatabaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseWidget(QWidget *parent = nullptr);
    ~DatabaseWidget();

    void on_buttonGetnew_clicked();

private slots:
    void on_buttonClose_clicked();



    void on_buttonChange_clicked();


private:
    Ui::DatabaseWidget *ui;

    //QSqlDatabase db2;
    //QSqlQueryModel *model1,*model2;
    MySqlQuery *model1,*model2;
};

#endif // DATABASEWIDGET_H
