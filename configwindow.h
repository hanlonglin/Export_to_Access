#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCloseEvent>
#include <QShowEvent>
#include "config.h"

namespace Ui {
class ConfigWindow;
}

class ConfigWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ConfigWindow(QWidget *parent = 0);
    ~ConfigWindow();

private:
    Ui::ConfigWindow *ui;

    void closeEvent(QCloseEvent *event);

    void showEvent(QShowEvent *event);

private slots:

    /*显示*/
    void showSlot();

    /*保存*/
    void saveSlot();

signals:
    void save_signal();
};

#endif // CONFIGWINDOW_H
