#include "status_buttom.h"
#include "ui_status_buttom.h"

status_buttom::status_buttom(QWidget *parent,QString s) :
    QDialog(parent),
    status(s),
    ui(new Ui::status_buttom)
{
    ui->setupUi(this);
    ui->pushButton->setText(status.mid(0,16) + "...");
}

status_buttom::~status_buttom()
{
    delete ui;
}

void status_buttom::on_pushButton_clicked()
{
    status = ui->lineEdit->text();
    ui->pushButton->setText(status);
    emit send_status(ui->lineEdit->text());
    ui->lineEdit->clear();
}

