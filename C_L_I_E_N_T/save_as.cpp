#include "save_as.h"
#include "ui_save_as.h"
#include <QFile>
#include <QDomDocument>
save_as::save_as(QWidget *parent,QVector<QString> s) :
    QDialog(parent),
    r(s),
    ui(new Ui::save_as)
{
    ui->setupUi(this);
}

save_as::~save_as()
{
    delete ui;
}

void save_as::on_pushButton_clicked()
{
    QFile *file = new QFile;
    file->setFileName("/home/renat/ruka/noga/C_L_I_E_N_T/" + ui->lineEdit->text() + ".xml");
    if(!file->exists()){
        file->open(QFile::WriteOnly | QFile::Text);
        file->close();
    }
    file->open(QFile::WriteOnly | QFile::Text);
    QTextStream qml_file(file);
    QDomDocument history;
    QDomElement root = history.createElement("history");
    history.appendChild(root);
    for(int i = 0;i < r.size();i ++){
        qDebug() << r[i];
        QDomElement message = history.createElement("message");
        message.setAttribute("id",i + 1);
        QDomText t1 = history.createTextNode(r[i]);
        message.appendChild(t1);
        root.appendChild(message);
    }
    qml_file << history.toString();
    file->close();

}


void save_as::on_checkBox_stateChanged(int arg1)
{
    if(arg1 != 0){
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }else{
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
}

