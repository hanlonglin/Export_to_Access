#include "config.h"

QString config::CONFIG_FILE="config.ini";

config::config()
{
    readConfig();
}


void config::readConfig()
{
    if(config::CONFIG_FILE.isEmpty())
    {
        qDebug()<<"config is null";
        config::CONFIG_FILE="config.ini";
    }
    QSettings *setting =new QSettings(config::CONFIG_FILE,QSettings::IniFormat);
    setting->setIniCodec("GBK");
    source_dbtype=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_DBTYPE).toString();
    source_host=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_HOST).toString();
    source_port=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_PORT).toString();
    source_dbname=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_DBNAME).toString();
    source_username=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_USERNAME).toString();
    source_password=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_PASSWORD).toString();
    source_sqlstatement=setting->value(CONFIG_SOURCE_SECTION+"/"+CONFIG_SOURCE_SQLSTATEMENT).toString();

    target_host=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_HOST).toString();
    target_port=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_PORT).toString();
    target_dbfile=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_DBFILE).toString();
    target_username=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_USERNAME).toString();
    target_password=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_PASSWORD).toString();
    target_tablename=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_TABLENAME).toString();
    target_columns=setting->value(CONFIG_TARGET_SECTION+"/"+CONFIG_TARGET_COLUMNS).toString().split("|");
    delete setting;
}

void config::setFile(QString file)
{
    config::CONFIG_FILE=file;
}
