#include "configwindow.h"
#include "ui_configwindow.h"

ConfigWindow::ConfigWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigWindow)
{
    ui->setupUi(this);
    //setWindowTitle("--config--");

    showSlot();

    connect(ui->pushButtonSave,&QPushButton::clicked,this,&ConfigWindow::saveSlot);//保存

}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}

/*显示*/
void ConfigWindow::showSlot()
{
    cfg.readConfig();
    QFile file(config::CONFIG_FILE);
    if(!file.open(QIODevice::ReadOnly))
    {
       QMessageBox::information(this,"",config::CONFIG_FILE+" open fail!");
       return ;
    }
    QTextStream in(&file);
    in.setCodec("GBK");
    ui->textEditConfig->setText(in.readAll());
    file.close();
}
/*保存*/
void ConfigWindow::saveSlot()
{
    QFile file(config::CONFIG_FILE);
    if(!file.open(QIODevice::ReadWrite|QIODevice::Truncate|QIODevice::Text))
    {
       QMessageBox::information(this,"",config::CONFIG_FILE+" open fail!");
       return ;
    }
    QTextStream out(&file);
    out.setCodec("GBK");
    out<<ui->textEditConfig->toPlainText();
    file.close();
    close();
}

/*关闭时函数*/
void ConfigWindow::closeEvent(QCloseEvent *event)
{
    emit save_signal();
}
/*打开时函数*/
void ConfigWindow::showEvent(QShowEvent *event)
{
    setWindowTitle(config::CONFIG_FILE);
    showSlot();
}
