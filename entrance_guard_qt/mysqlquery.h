#ifndef MYSQLQUERY_H
#define MYSQLQUERY_H

#include <QObject>
#include <QSqlQueryModel>

class MySqlQuery : public QSqlQueryModel
{
public:

    MySqlQuery(QObject *parent);

    QVariant data(const QModelIndex &item, int role=Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
};

#endif // MYSQLQUERY_H
