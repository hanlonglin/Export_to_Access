#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    config c;
    if(argc>1)
    {
        //配置config文件
        if(QString(argv[1])=="--config")
            c.setFile(QString::fromLocal8Bit(argv[2]));
        else{
            //std::cout<<"please enter --config [config-file]"<<std::endl;
            //system("pause");
            return 0;
        }
    }

    QApplication a(argc, argv);

    //设置当前路径,exe所在路径
    QDir::setCurrent(QApplication::applicationDirPath());

    MainWindow w;
    w.show();

    return a.exec();
}
