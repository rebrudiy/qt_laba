#include "save_as_xml.h"
#include "ui_save_as_xml.h"
#include <QFile>
#include <QDomDocument>
save_as_xml::save_as_xml(QWidget *parent,QVector<QString> s) :
    QDialog(parent),
    r(s),
    ui(new Ui::save_as_xml)
{
    ui->setupUi(this);
}

save_as_xml::~save_as_xml()
{
    delete ui;
}

void save_as_xml::on_pushButton_clicked()
{
    QFile file;
    file.setFileName("/home/renat/ruka/noga/C_L_I_E_N_T/" + ui->lineEdit->text() + ".xml");
    QTextStream qml_file(&file);
    QDomDocument history;
    QDomElement root = history.createElement("history");
    history.appendChild(root);
    for(int i = 0;i < r.size();i ++){
        QDomElement message = history.createElement("action");
        message.setAttribute("id",i + 1);
        QDomText t1 = history.createTextNode(r[i]);
        message.appendChild(t1);
        root.appendChild(message);
    }
    qml_file << history.toString();
    file.open(QFile::WriteOnly | QFile::Text);
    file.close();

}


void save_as_xml::on_checkBox_stateChanged(int arg1)
{
    if(arg1 != 0){
        ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }else{
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
}

