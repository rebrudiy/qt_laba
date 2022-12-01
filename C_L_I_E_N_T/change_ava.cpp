#include "change_ava.h"
#include "ui_change_ava.h"
#include <QFileDialog>
#
change_ava::change_ava(QWidget *parent,QPixmap a) :
    QDialog(parent),
    pic(a),
    ui(new Ui::change_ava)
{
    ui->setupUi(this);
    pic = pic.scaled(100,100,Qt::KeepAspectRatio);
    ui->label->setPixmap(pic);
}

change_ava::~change_ava()
{
    delete ui;
}

void change_ava::on_pushButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath(), QObject::tr(" (*.png)"));
    pic = QPixmap(path);
    pic = pic.scaled(100,100,Qt::KeepAspectRatio);
    ui->label->setPixmap(pic);
    emit new_ava(path);
}

