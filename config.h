#ifndef CONFIG_H
#define CONFIG_H
#include <QSettings>
#include <QDebug>


static const QString CONFIG_SOURCE_SECTION="Source";
static const QString CONFIG_SOURCE_DBTYPE="dbtype";
static const QString CONFIG_SOURCE_HOST="host";
static const QString CONFIG_SOURCE_PORT="port";
static const QString CONFIG_SOURCE_DBNAME="dbname";
static const QString CONFIG_SOURCE_USERNAME="username";
static const QString CONFIG_SOURCE_PASSWORD="password";
static const QString CONFIG_SOURCE_SQLSTATEMENT="sqlstatement";

static const QString CONFIG_TARGET_SECTION="Target";
static const QString CONFIG_TARGET_HOST="host";
static const QString CONFIG_TARGET_PORT="post";
static const QString CONFIG_TARGET_DBFILE="dbfile";
static const QString CONFIG_TARGET_USERNAME="username";
static const QString CONFIG_TARGET_PASSWORD="password";
static const QString CONFIG_TARGET_TABLENAME="tablename";
static const QString CONFIG_TARGET_COLUMNS="columns";




class config
{
public:
    config();

    static QString CONFIG_FILE; //全局变量

    void readConfig();

    void setFile(QString file);


    QString source_dbtype;
    QString source_host;
    QString source_port;
    QString source_dbname;
    QString source_username;
    QString source_password;
    QString source_sqlstatement;

    QString target_host;
    QString target_port;
    QString target_dbfile;
    QString target_username;
    QString target_password;
    QString target_tablename;
    QStringList target_columns;
};

#endif // CONFIG_H
