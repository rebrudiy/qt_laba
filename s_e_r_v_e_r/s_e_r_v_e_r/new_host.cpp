#include "new_host.h"
#include "ui_new_host.h"

new_host::new_host(QWidget *parent,QString _ip,qint32 _port) :
    QDialog(parent),
    port(_port),
    ip(_ip),
    ui(new Ui::new_host)
{

    ui->setupUi(this);
    ui->lineEdit_2->setText(QString::number(_port));
    ui->lineEdit->setText(_ip);
}

new_host::~new_host()
{
    delete ui;
}

void new_host::on_pushButton_2_clicked()
{
    port = ui->lineEdit_2->text().toInt();
    emit new_port(ui->lineEdit_2->text().toInt());
}

void new_host::on_pushButton_clicked()
{
    ip = ui->lineEdit->text();
    emit new_ip(ui->lineEdit->text());
}

