

#include "databasetools.h"

DatabaseTools::DatabaseTools()
{

}

void DatabaseTools::run()
{
    Export_to_Access();
}

/*连接数据库*/
bool DatabaseTools::connect_source_DB(QString dbType)
{
    if(dbType=="sqlserver")
    {
        source_DB = QSqlDatabase::addDatabase("QODBC",cfg.source_dbname);
        source_DB.setDatabaseName(QString("DRIVER={SQL SERVER};"
                                          "SERVER=%1;"
                                          "DATABASE=%2;"
                                          "UID=%3;"
                                          "PWD=%4;").arg(cfg.source_host+","+cfg.source_port)
                                  .arg(cfg.source_dbname)
                                  .arg(cfg.source_username)
                                  .arg(cfg.source_password));
    }else if(dbType=="mysql")
    {
        source_DB = QSqlDatabase::addDatabase("QMYSQL",cfg.source_dbname);
        source_DB.setHostName(cfg.source_host);
        source_DB.setPort(cfg.source_port.toInt());
        source_DB.setDatabaseName(cfg.source_dbname);
        source_DB.setUserName(cfg.source_username);
        source_DB.setPassword(cfg.source_password);
    }else
    {
        return false;
    }

    if (!source_DB.open())
    {
        return false;
    }
    return true;
}

bool DatabaseTools::connect_target_DB()
{
    target_DB = QSqlDatabase::addDatabase("QODBC",cfg.target_dbfile);
    target_DB.setDatabaseName(QString("DRIVER={Microsoft Access Driver (*.mdb)};FIL={MS ACCESS DATABASE};DBQ=%1;").arg(cfg.target_dbfile));
    target_DB.setHostName(cfg.target_host);
    target_DB.setPort(cfg.target_port.toInt());
    target_DB.setUserName(cfg.target_username);
    target_DB.setPassword(cfg.target_password);

    if(!target_DB.open())
    {
        qDebug()<<target_DB.lastError();
        return false;
    }
    return true;
}
//关闭数据库
bool DatabaseTools::close_source_DB()
{
    if(!source_DB.isOpen())
        source_DB.close();
    //QSqlDatabase::removeDatabase(source_DB.connectionName());
    return true;
}
bool DatabaseTools::close_target_DB()
{
    if(!target_DB.isOpen())
        target_DB.close();
    //QSqlDatabase::removeDatabase(target_DB.connectionName());
    return true;
}

//导出数据到access,主方法
void DatabaseTools::Export_to_Access()
{
    cfg.readConfig();//刷新
    bool ret=false;
    ret=connect_source_DB(cfg.source_dbtype);
    if(!ret)
    {
        emit sendMsg(-1,"connect source db '"+cfg.source_dbname+"' fail!"+source_DB.lastError().text());
        close_source_DB();
        close_target_DB();
        return ;
    }
    emit sendMsg(0,"connect source db '"+cfg.source_dbname+"' success.");
    QSqlQuery source_query(source_DB);
//    qDebug()<<"source_query.isActive() "<<source_query.isActive();
//    qDebug()<<"source_query.isValid() "<<source_query.isValid();
//    qDebug()<<"source_query.isSelect() "<<source_query.isSelect();
//    qDebug()<<"source_query.isNull(0) "<<source_query.isNull(0);

    ret=connect_target_DB();
    if(!ret)
    {
        emit sendMsg(-1,"connect target db '"+cfg.target_dbfile+"' fail!"+target_DB.lastError().text());
        close_source_DB();
        close_target_DB();
        return ;
    }
    emit sendMsg(0,"connect target db '"+cfg.target_dbfile+"' success.");

    QSqlQuery target_query(target_DB);
    //qDebug()<<"after instance target_query";
    ret=source_query.exec(cfg.source_sqlstatement);
    if(!ret)
    {
        emit sendMsg(-1,"exec query '"+cfg.source_sqlstatement+"' fail!"+source_query.lastError().text());
        close_source_DB();
        close_target_DB();
        return ;
    }
    emit sendMsg(0,"exec query success,start to export......");

    int success_insert=0,fail_insert=0; //记录插入成功和失败的记录数量

    while(source_query.next())
    {
        int count=source_query.record().count();
        if(count!=cfg.target_columns.count())
        {
            emit sendMsg(-1,"target columns is not same as search results");
            close_source_DB();
            close_target_DB();
            return ;
        }
        QStringList search_list;
        search_list.clear();
        for(int i=0;i<count;i++)
        {
            QString value=source_query.value(i).toString();
            search_list.push_back(value);
            if(i==(count-1))  //查询完一列
            {
                //构造查询语句
                QString columns,values;
                for(int j=0;j<count;j++)
                {
                    if(j!=(count-1))
                    {
                        columns.append(cfg.target_columns.at(j)).append(",");
                        values.append("'"+search_list.at(j)+"'").append(",");
                    }else{
                        columns.append(cfg.target_columns.at(j));
                        values.append("'"+search_list.at(j)+"'");
                    }

                }
                QString insert_sql="insert into "+cfg.target_tablename+"("+columns+") values ("+values+")";
                //qDebug()<<"insert statement:"<<insert_sql;
                //插入一条数据
                ret=target_query.exec(insert_sql);
                if(!ret)
                {
                    emit sendMsg(-1,"exec "+insert_sql+" fail!"+target_query.lastError().text());
                    fail_insert++;
                    //return ;
                }else
                    success_insert++;

            }
        }


    }
    emit sendMsg(1,"Export finished. "+QString::number(success_insert)+" records success, "+QString::number(fail_insert)+" records fail.");

    //关闭数据库
    close_source_DB();
    close_target_DB();
    return ;
}
