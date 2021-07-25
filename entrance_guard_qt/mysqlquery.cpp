#include "mysqlquery.h"

#include <QSqlQuery>
#include <QDebug>
MySqlQuery::MySqlQuery(QObject *parent) : QSqlQueryModel(parent)
{

}
//
Qt::ItemFlags MySqlQuery::flags(
       const QModelIndex &index) const //返回表格是否可更改的标志
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column()!=6&&index.column()!=7) //可编辑状态
       flags |= Qt::ItemIsEditable;
    return flags;
}
//更改数据显示样式-性别-出生日期
QVariant MySqlQuery::data(const QModelIndex &index, int role) const
{

    QVariant value=QSqlQueryModel::data(index,role);

    if(role==Qt::DisplayRole &&(index.column()==3||index.column()==4||index.column()==5))
    {
        value=value.toString();
        //qDebug() << value.toString();
        return value;
    }

    return value;

}

