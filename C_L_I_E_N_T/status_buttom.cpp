#include "status_buttom.h"
#include "ui_status_buttom.h"

status_buttom::status_buttom(QWidget *parent,QString s) :
    QDialog(parent),
    status(s),
    ui(new Ui::status_buttom)
{
    ui->setupUi(this);
    ui->pushButton->setText(s);
    if(s == "not here"){
        x = 1;
    }else if(s == "available"){
        x = 2;
    }else{
        x = 0;
    }
}

status_buttom::~status_buttom()
{
    delete ui;
}

void status_buttom::on_pushButton_clicked()
{
    x ++;
    x %= 3;
    if(x == 1){
        ui->pushButton->setText("not here");
    }else if(x == 2){
        ui->pushButton->setText("do not disturb");
    }else{
        ui->pushButton->setText("available");
    }
    emit send_status(ui->pushButton->text());
}

