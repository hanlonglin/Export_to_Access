#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置当前路径,exe所在路径
    QDir::setCurrent(QApplication::applicationDirPath());

    MainWindow w;
    w.show();

    return a.exec();
}
