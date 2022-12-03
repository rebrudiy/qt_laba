#include "info.h"
#include "ui_info.h"
#include <QPixmap>
info::info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
    QPixmap pic("/home/renat/Downloads/my_team/fhf.png");
    ui->label->setPixmap(pic);
    QString s = "QT version";
    s += QT_VERSION_STR;
    ui->label_3->setText(s);
    ui->label_4->setText("QT build version 6.4.0");
}

info::~info()
{
    delete ui;
}

void info::on_pushButton_clicked()
{
    this->close();
}

