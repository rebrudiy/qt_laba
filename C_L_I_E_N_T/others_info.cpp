#include "others_info.h"
#include "ui_others_info.h"

others_info::others_info(QWidget *parent,QVector<QString> q) :
    QDialog(parent),
    ui(new Ui::others_info)
{
    ui->setupUi(this);
    ui->textEdit->append(q[0]);
    ui->textEdit->append(q[1]);
    ui->textEdit->append("127.0.0.1");
}

others_info::~others_info()
{
    delete ui;
}
