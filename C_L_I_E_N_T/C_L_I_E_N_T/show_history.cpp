#include "show_history.h"
#include "ui_show_history.h"
#include <QFile>
#include <QDomDocument>
#include "info.h"
#include <QDesktopServices>
#include <QUrl>
show_history::show_history(QWidget *parent,QListWidget *q,QVector<QString> s) :
    QMainWindow(parent),
    hist(s),
    ui(new Ui::show_history)
{
    ui->setupUi(this);
    ans= new QFile;
    ans->setFileName("/home/renat/ruka/noga/C_L_I_E_N_T/history_of_all.xml");
    if(!ans->exists()){
        ans->open(QFile::WriteOnly | QFile::Text);
        ans->close();
    }
    ans->open(QFile::WriteOnly | QFile::Text);
    QTextStream qml_file(ans);
    QDomDocument history;
    QDomElement root = history.createElement("history");
    history.appendChild(root);
    for(int i = 0;i < hist.size();i ++){
        qDebug() << hist[i];
        QDomElement message = history.createElement("message");
        message.setAttribute("id",i + 1);
        QDomText t1 = history.createTextNode(hist[i]);
        message.appendChild(t1);
        root.appendChild(message);
    }
    qml_file << history.toString();
    ans->close();
    this->setWindowTitle(ans->fileName());
    qDebug() << q->count();
    q->show();
    for(int i = 0;i < q->count();i ++){
        QListWidgetItem *item = q->item(i);
        if(item == nullptr){
            qDebug() << "hren";
        }
        ui->listWidget->addItem(q->item(i));
    }
    for(int i = 0;i < hist.size();i ++){
        QListWidgetItem *it = new QListWidgetItem();
        it->setText(hist[i]);
        ui->listWidget->addItem(it);
    }
}


show_history::~show_history()
{
    delete ui;
}

void show_history::on_actionabout_triggered()
{
    info *i = new info();
    i->show();
}


void show_history::on_actionchat_triggered()
{
    emit again();
    this->close();
}


void show_history::on_actionexit_triggered()
{
    qApp->exit(0);
}


void show_history::on_actionopen_triggered()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(ans->fileName()));

}

