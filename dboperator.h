#ifndef DBOPERATOR_H
#define DBOPERATOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QDebug>

class DBOperator
{ private:
    bool openFlag;
  public:
    QSqlDatabase dbcon;
    DBOperator();
    void DBOpen();
    void DBClose();
    QSqlQuery DBGetData(QString sqlstr);
};

#endif // DBOPERATOR_H
