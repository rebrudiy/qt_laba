#include "images.h"
#include "ui_images.h"
#include <QFile>
#include <QDir>
images::images(QWidget *parent,QPixmap s) :
    QDialog(parent),
    som(s),
    ui(new Ui::images)
{
    ui->setupUi(this);
    ui->label->setPixmap(som);
}

images::~images()
{
    delete ui;
}

void images::on_pushButton_clicked()
{
    som.save(("/home/renat/ruka/noga/" + ui->lineEdit->text() + ".png"));
}

