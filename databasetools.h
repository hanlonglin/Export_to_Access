#ifndef DATABASETOOLS_H
#define DATABASETOOLS_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVariant>

#include "config.h"

class DatabaseTools:public QThread
{
    Q_OBJECT
public:
    DatabaseTools();

    //属性
    config cfg;

    /*连接数据库*/
    bool connect_source_DB(QString dbType);//sqlserver或mysql

    bool connect_target_DB(); //access

    /*关闭数据库*/
    bool close_source_DB();
    bool close_target_DB();

    /*导出数据到access，主方法*/
    void Export_to_Access();

    //
    void run();

private:

    QSqlDatabase source_DB,target_DB;

signals:

    /*
     state :
          -1:错误信息；
          0：正确信息；
          1：结束信息；
    */
    void sendMsg(int state,QString mes);

};

#endif // DATABASETOOLS_H
