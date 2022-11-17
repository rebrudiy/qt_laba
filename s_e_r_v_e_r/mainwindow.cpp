#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);  
}
void MainWindow::set_user_count(bool new_user){
    if(new_user){
        count_of_users ++;
    }else{
        count_of_users --;
    }
    this->setWindowTitle("Server host is 127.0.0.1:45678 Count of users: " + QString::number(this->count_of_users));
}

void MainWindow::some_text(QString str)
{
    this->ui->textEdit->append(str);
}
MainWindow::~MainWindow()
{
    delete ui;
}

