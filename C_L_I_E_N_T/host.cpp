#include "host.h"
#include "ui_host.h"

host::host(QWidget *parent,QString _ip,qint32 _port) :
    QDialog(parent),
    ip(_ip),
    port(_port),
    ui(new Ui::host)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString::number(port));
    ui->lineEdit_2->setText(ip);
}

host::~host()
{
    delete ui;
}

void host::on_pushButton_clicked()
{
    port = ui->lineEdit->text().toInt();
    emit change_port(ui->lineEdit->text().toInt());
}


void host::on_pushButton_2_clicked()
{
    ip = ui->lineEdit_2->text();
    emit change_ip(ui->lineEdit_2->text());
}

