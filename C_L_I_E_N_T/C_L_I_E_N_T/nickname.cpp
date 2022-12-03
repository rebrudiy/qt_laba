#include "nickname.h"
#include "ui_nickname.h"

nickname::nickname(QWidget *parent,QString s) :
    QDialog(parent),
    str(s),
    ui(new Ui::nickname)
{
    ui->setupUi(this);
    ui->lineEdit->setText(str);

}

nickname::~nickname()
{
    delete ui;
}
void nickname::on_pushButton_clicked()
{
    str = ui->lineEdit->text();
    emit new_username(ui->lineEdit->text());
}

