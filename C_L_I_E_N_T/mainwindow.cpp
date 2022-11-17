#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "status_buttom.h"
#include "host.h"
#include "nickname.h"
#include "info.h"
#include "others_info.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setting = new QSettings("/home/renat/ruka/noga/C_L_I_E_N_T/setting.ini",QSettings::IniFormat);
    ui->setupUi(this);
    isconnected = false;
    uploadsettings();
    socket = new QSslSocket();
    connect(socket,&QSslSocket::readyRead,this,&MainWindow::slotReadyRead);
    connect(socket,&QSslSocket::disconnected,socket,&QSslSocket::deleteLater);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    if(isconnected){
        socket->disconnectFromHost();
    }
    delete ui;
}
void MainWindow::on_actionConnect_triggered()
{
    if(!isconnected){
    socket->connectToHost(ip,port);
    isconnected = true;
    sendToServer("new_user","sgfs");
    this->setWindowTitle("connected to " + ip + ":" + QString::number(port) + " userstatus " + user_status);
    }
}

void MainWindow::on_actionDisconnect_triggered()
{
    if(isconnected){
    socket->disconnectFromHost();
    this->setWindowTitle("nothing to connect");
    isconnected = false;
    ui->textBrowser->clear();
    ui->listWidget->clear();
    }
}


void MainWindow::on_actionExit_triggered()
{
    qApp->exit(0);
}


void MainWindow::on_push_button_triggered()
{
    status_buttom *st = new status_buttom(nullptr,user_status);
    st->show();
    connect(st,&status_buttom::send_status,this,&MainWindow::set_new_status);
}
void MainWindow::on_actionusername_triggered()
{
    nickname *n = new nickname(nullptr,username);
    n->show();
    connect(n,&nickname::new_username,this,&MainWindow::set_new_usename);
}
void MainWindow::on_actionhost_triggered()
{
    host *h = new host(nullptr,ip,port);
    h->show();
    connect(h,&host::change_ip,this,&MainWindow::set_new_ip);
    connect(h,&host::change_port,this,&MainWindow::set_new_port);
}
void MainWindow::set_new_usename(QString str)
{
    username = str;
    sendToServer("new_username","safsdf");
    setsetings();
}

void MainWindow::set_new_status(QString str)
{
    user_status = str;
    setting->setValue("status",str);
    if(isconnected){
        this->setWindowTitle("connected to " + ip + ":" + QString::number(port) + " userstatus " + user_status);
    }else{
        this->setWindowTitle("nothing to connect");
    }
    setsetings();
    sendToServer("new_status","fsfsd");
}
void MainWindow::set_new_ip(QString s)
{
    if(isconnected){socket->disconnectFromHost();}
    this->setWindowTitle("nothing to connect");
    ip = s;
    setsetings();
}

void MainWindow::set_new_port(qint32 q)
{
    if(isconnected){socket->disconnectFromHost();}
    this->setWindowTitle("nothing to connect");
    port = q;
    setsetings();
}


void MainWindow::on_actionAbout_triggered()
{
    info *in = new info;
    in->show();
}
void MainWindow::uploadsettings()
{
    ip = setting->value("ip").toString();
    username = setting->value("username").toString();
    user_status = setting->value("status").toString();
    port = setting->value("port").toInt();
}

void MainWindow::setsetings()
{
    setting->setValue("ip",ip);
    setting->setValue("port",port);
    setting->setValue("username",username);
    setting->setValue("status",user_status);
}

void MainWindow::sendToServer(QString str,QString str1)
{
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out << str;
    if(str == "new_user"){
        QMap<QString,QString> q;
        q["user_status"] = user_status;
        q["user_name"] = username;
        out << q;
    }else if(str == "new_status"){
        out << user_status;
    }else if(str == "new_username"){
        out << username;
    }else if(str == "message"){
        out << ui->lineEdit->text();
        ui->lineEdit->clear();
    }else{
        out << str1;
    }
    socket->write(Data);
    }
void MainWindow::slotReadyRead(){
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        QString status;
        in >> status;
        qDebug() << status << "\n";
        if(status == "connected"){
            QVector<QString> user;
            ui->listWidget->clear();
            qDebug() << "fefws";
            in >> user;
            for(int i = 0;i < user.size();i ++){
                qDebug() << "qsize";
                ui->listWidget->addItem(user[i]);
            }
        }else if(status == "disconnected"){
            ui->listWidget->clear();
        }else if(status == "message"){
            QString message;
            in >> message;
            ui->textBrowser->append(message);
        }else{
            QVector<QString>s;
            in >> s;
            qDebug() << s[0] << " " << s[1];
            others_info *h = new others_info(nullptr,s);
            h->show();
        }
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    sendToServer("message","afasd");
}


void MainWindow::on_pushButton_clicked()
{
    foreach (QListWidgetItem *y, ui->listWidget->selectedItems()) {
        QString hr = y->text();
        sendToServer("info",hr);
        socket->write(Data);
    }
}


void MainWindow::on_actionSave_triggered()
{

}

