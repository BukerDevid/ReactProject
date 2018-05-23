#include "mysqlconnect.h"

MySqlConnect::MySqlConnect()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("toor");
    db.setDatabaseName("ux_bd1");
    ModSql = QSqlQuery(db);
}

