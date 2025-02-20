#include "dboperator.h"

DBOperator::DBOperator()
{}

// 添加MySql数据库
void DBOperator::DBOpen()
{
    // "first" 连接已经存在
    if (QSqlDatabase::contains("first"))
    {
        dbcon = QSqlDatabase::database("first");
    }
    // "first" 连接不存在，创建新的连接
    else {
        dbcon = QSqlDatabase::addDatabase("QMYSQL", "first");  // 指定了连接名
        // 连接数据库
        dbcon.setHostName("127.0.0.1");  //数据库服务器IP
        dbcon.setUserName("root");    //数据库用户名
        dbcon.setPassword("hwy123123");  //密码
        dbcon.setDatabaseName("lms");  //使用哪个数据库
        // 打开数据库
        if (dbcon.open() == false)
        {
            qDebug() << "错误, Library 数据库文件打开失败！" << dbcon.lastError().text();
            return;
        }
    }
}

void DBOperator::DBClose()
{
    dbcon.close();
    QSqlDatabase::removeDatabase("first");
}

QSqlQuery DBOperator::DBGetData(QString sqlstr)
{
    QSqlQuery query = QSqlQuery(dbcon);
    query.exec(sqlstr);
    return query;
}
