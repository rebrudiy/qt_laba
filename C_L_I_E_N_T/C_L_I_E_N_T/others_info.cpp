#include "others_info.h"
#include "ui_others_info.h"
#include <QFile>
#include <QFileDialog>
#include <QThread>
others_info::others_info(QWidget *parent,QVector<QString> q) :
    QDialog(parent),
    date(q[0]),
    ui(new Ui::others_info)
{
    ui->setupUi(this);
    qDebug() << date << "  " << q[0];
    ui->textEdit->append(q[0]);
    ui->textEdit->append(q[1]);
    ui->textEdit->append("127.0.0.1");
    ui->progressBar->setValue(100);
}

others_info::~others_info()
{
    delete ui;
}

void others_info::on_pushButton_clicked()
{
   path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath());
   ui->progressBar->setValue(33);
   QThread::sleep(1);
   ui->progressBar->setValue(66);
   QThread::sleep(1);
   ui->progressBar->setValue(100);
   QThread::sleep(1);
   qDebug()<< "mraz" << date;
   emit f(path,date);
}

