#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
}


void MainWindow::some_text(QString str)
{
    if(str == "clear"){
        this->ui->textEdit->clear();
        return;
    }
    this->ui->textEdit->append(str);
}

void MainWindow::set_new_windows_status(QString str)
{
    this->setWindowTitle(str);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_actionchange_key_triggered()
{
    emit new_crypto_key();
}


void MainWindow::on_actionchange_ip_port_triggered()
{
    emit new_hosty();
}


void MainWindow::on_actionon_triggered()
{ 
    emit on_server();
}
void MainWindow::on_actionoff_triggered()
{
    this->setWindowTitle("no work");
    emit  off_server();
}
void MainWindow::on_actionsava_triggered()
{
    emit  save_server();
}
void MainWindow::on_actionexit_triggered()
{
    emit  exit_server();
}

