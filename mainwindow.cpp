#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("mysql/sqlserver导入access"));

    showSlot();
    ui->dockWidgetResult->hide();

    connect(ui->pushButtonChangeSourceSql,&QPushButton::clicked,this,&MainWindow::openConfigSlot);//打开配置文件
    connect(ui->pushButtonChangeTargetColumns,&QPushButton::clicked,this,&MainWindow::openConfigSlot);//打开配置文件
    connect(ui->actionOpenConfig,&QAction::triggered,this,&MainWindow::openConfigSlot);//打开配置文件
    connect(ui->actionOpenDocWindow,&QAction::triggered,ui->dockWidgetResult,&QDockWidget::show);//显示结果界面
    connect(&cWindow,&ConfigWindow::save_signal,this,&MainWindow::showSlot);//刷新显示
    connect(ui->pushButtonStartExport,&QPushButton::clicked,this,&MainWindow::startExportSlot);//开始导出
    connect(&dbTools,&DatabaseTools::sendMsg,this,&MainWindow::receiveResult);//显示结果
    connect(&dbTools,&DatabaseTools::finished,this,&MainWindow::finishSlot);//导出完成
    connect(ui->toolButtonClear,&QToolButton::clicked,
            [=]()
    {
          ui->textBrowserResult->clear();
    });//清空结果信息


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*显示*/
void MainWindow::showSlot()
{
    cfg.readConfig();//刷新
    if(!cfg.source_host.isEmpty())
        ui->labelSourceHost->setText(cfg.source_host);
    if(!cfg.source_dbname.isEmpty())
        ui->labeldbSourceDbName->setText(cfg.source_dbname);
    if(!cfg.source_sqlstatement.isEmpty())
        ui->textBrowserSourceSql->setText(cfg.source_sqlstatement);

    if(!cfg.target_host.isEmpty())
        ui->labelTargetHost->setText(cfg.target_host);
    if(!cfg.target_dbfile.isEmpty())
        ui->labelTargetDbName->setText(cfg.target_dbfile);
    if(cfg.target_columns.count()!=0)
    {
        ui->textBrowserTargetColumn->clear();
        for(QString column:cfg.target_columns)
        {
            ui->textBrowserTargetColumn->append(column);
        }
    }
    //connect(ui->textBrowserResult,&QTextBrowser::textChanged,ui->textBrowserResult,&QTextBrowser::)
}

/*打开配置文件*/
void MainWindow::openConfigSlot()
{
    cWindow.show();
}

/*开始导出*/
void MainWindow::startExportSlot()
{
    QString time=QDateTime::currentDateTime().toString("----yyyy/MM/dd hh:mm:ss");
    ui->dockWidgetResult->show();
    ui->pushButtonStartExport->setEnabled(false);
    ui->textBrowserResult->append("<span style='color:black;'>---------------------------------------------------------"+time+"</span>");
    //ui->textBrowserResult->append("---------------------------------------------------------"+time+"");
    //开始写日志
    Log::writeLog("--------------Start Export----------------------------------------------------");
    dbTools.start();
}

/*显示结果*/
void MainWindow::receiveResult(int state ,QString msg)
{

    if(state==-1)
        ui->textBrowserResult->append("<span style='color:red;'>"+msg+"</span>");
    else if(state==0)
        ui->textBrowserResult->append("<span style='color:blue;'>"+msg+"</span>");
    else
        ui->textBrowserResult->append("<span style='color:green;'>"+msg+"</span>");

    //写入日志
    Log::writeLog(msg.toStdString());
}

/*导出完成*/
void MainWindow::finishSlot()
{
    ui->pushButtonStartExport->setEnabled(true);
}
