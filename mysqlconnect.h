#ifndef MYSQLCONNECT_H
#define MYSQLCONNECT_H
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>

class MySqlConnect
{
public:
    QSqlDatabase db;
    QSqlQuery ModSql;
    MySqlConnect();

};

#endif // MYSQLCONNECT_H
