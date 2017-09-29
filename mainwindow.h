#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QDir>
#include <QDateTime>

#include "config.h"
#include "configwindow.h"
#include "databasetools.h"
#include "log.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //属性
    config cfg;

private:
    Ui::MainWindow *ui;

    ConfigWindow cWindow;
    DatabaseTools dbTools;



private slots:

    /*显示*/
    void showSlot();

    /*修改配置*/
    void openConfigSlot();

    /*开始导出*/
    void startExportSlot();

    /*显示结果信息*/
    void receiveResult(int state,QString msg);

    /*导出完成*/
    void finishSlot();

};

#endif // MAINWINDOW_H
