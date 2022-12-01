#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "status_buttom.h"
#include "host.h"
#include "nickname.h"
#include "info.h"
#include "others_info.h"
#include "save_as.h"
#include "change_ava.h"
#include <QBuffer>
#include <QLabel>
#include <QScrollBar>
#include <QFileDialog>
#include "images.h"
#include <QDesktopServices>
#include "accept_file.h"
#include <QDialogButtonBox>
#include <QMutex>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    colors_info = new QListWidget();
    colors_background = new QListWidget();
    colors_of_message = new QListWidget();
    QListWidgetItem *red = new QListWidgetItem();
    red->setText("red");
    QListWidgetItem *yellow = new QListWidgetItem();
    yellow->setText("yellow");
    QListWidgetItem *green = new QListWidgetItem();
    green->setText("green");
    QListWidgetItem *brown = new QListWidgetItem();
    brown->setText("brown");
    QListWidgetItem *black = new QListWidgetItem();
    black->setText("black");
    QListWidgetItem *white = new QListWidgetItem();
    white->setText("white");
    colors_info->addItem(white);
    colors_info->addItem(red);
    colors_info->addItem(green);
    colors_info->addItem(yellow);
    colors_info->addItem(brown);
    colors_info->addItem(black);
    QListWidgetItem *red2 = new QListWidgetItem();
    red2->setText("red");
    QListWidgetItem *yellow2 = new QListWidgetItem();
    yellow2->setText("yellow");
    QListWidgetItem *green2 = new QListWidgetItem();
    green2->setText("green");
    QListWidgetItem *brown2 = new QListWidgetItem();
    brown2->setText("brown");
    QListWidgetItem *black2 = new QListWidgetItem();
    black2->setText("black");
    QListWidgetItem *white2 = new QListWidgetItem();
    white2->setText("white");
    colors_of_message->addItem(white2);
    colors_of_message->addItem(red2);
    colors_of_message->addItem(green2);
    colors_of_message->addItem(yellow2);
    colors_of_message->addItem(brown2);
    colors_of_message->addItem(black2);
    QListWidgetItem *red1 = new QListWidgetItem();
    red1->setText("red");
    QListWidgetItem *yellow1 = new QListWidgetItem();
    yellow1->setText("yellow");
    QListWidgetItem *green1 = new QListWidgetItem();
    green1->setText("green");
    QListWidgetItem *brown1 = new QListWidgetItem();
    brown1->setText("brown");
    QListWidgetItem *black1 = new QListWidgetItem();
    black1->setText("black");
    QListWidgetItem *white1 = new QListWidgetItem();
    white1->setText("white");
    colors_background->addItem(white1);
    colors_background->addItem(red1);
    colors_background->addItem(green1);
    colors_background->addItem(yellow1);
    colors_background->addItem(brown1);
    colors_background->addItem(black1);
    setting = new QSettings("/home/renat/ruka/noga/C_L_I_E_N_T/setting.ini",QSettings::IniFormat);
    ui->setupUi(this);
    nextblocksize = 0;
    crypto_key = 1;
    isconnected = false;
    ava = QPixmap("/home/renat/Documents/users_image/no_ava.png");
    uploadsettings();
    socket = new QSslSocket();
    socket_cond = true;
    connect(socket,&QSslSocket::readyRead,this,&MainWindow::slotReadyRead);
    connect(socket,&QSslSocket::disconnected,socket,&QSslSocket::deleteLater);
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_2->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listWidget_2->setStyleSheet( "background-color: white");
    qDebug() << ui->listWidget_2->styleSheet() << '\n';
    q = new QListWidget();
        text = new QListWidgetItem("text");
        image = new QListWidgetItem("image");
        file = new QListWidgetItem("file");
        text->setText("text");
        image->setText("image");
        file->setText("file");
        q->addItem(text);
        q->addItem(image);
        q->addItem(file);
        file_obr = new QListWidget;
        QListWidgetItem *save = new QListWidgetItem("save");
        QListWidgetItem *open = new QListWidgetItem("open");
        file_obr->addItem(save);
        file_obr->addItem(open);
        ui->progressBar->setValue(100);
        automatic_reception = false;
         cond = 0;
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
    qDebug() << "frog";
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
    QSslSocket *uy = new QSslSocket;
    delete uy;
    socket = new QSslSocket();
    connect(socket,&QSslSocket::readyRead,this,&MainWindow::slotReadyRead);
    connect(socket,&QSslSocket::disconnected,socket,&QSslSocket::deleteLater);
    ui->listWidget_2->clear();
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
    if(isconnected){on_actionDisconnect_triggered();}
    this->setWindowTitle("nothing to connect");
    ip = s;
    setsetings();
}

void MainWindow::set_new_port(qint32 q)
{
    if(isconnected){on_actionDisconnect_triggered();}
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
    out << qint64(0);
    out << rashifrovat_string(str);
    if(str == "new_user"){
        QMap<QString,QString> q;
        q["user_status"] = rashifrovat_string(user_status);
        q["user_name"] = rashifrovat_string(username);
        out << q;
        out << rashifrovat_pixmaop(ava);
    }else if(str == "new_status"){
        out << rashifrovat_string(user_status);
    }else if(str == "new_username"){
        out << rashifrovat_string(username);
    }else if(str == "message"){
        out << rashifrovat_string(ui->lineEdit->text());
        ui->lineEdit->clear();
    }else if(str == "new_ava"){
        out << rashifrovat_pixmaop(ava);
    }else if(str =="send_image"){
        QPixmap pip(str1);
        out << rashifrovat_pixmaop(pip);
    }else if(str == "new_file"){
        out << str1;
        qDebug() << "step 2";
    }else{
        out << rashifrovat_string(str1);
    }
    out.device()->seek(0);
    out << qint64(Data.size() - sizeof(qint64));
    socket->write(Data);
}

void MainWindow::update_colors()
{
    if(usernames.size() > 1){
        ui->listWidget_2->item(usernames[usernames.size() - 1])->setForeground(ui->listWidget_2->item(usernames[0])->foreground());
    }
    if(ips.size() > 1){
        ui->listWidget_2->item(ips[ips.size() - 1])->setForeground(ui->listWidget_2->item(ips[0])->foreground());
    }
    if(dates.size() > 1){
        ui->listWidget_2->item(dates[dates.size() - 1])->setForeground(ui->listWidget_2->item(dates[0])->foreground());
    }
    if(messages.size() > 1){
        ui->listWidget_2->item(messages[messages.size() - 1])->setForeground(ui->listWidget_2->item(messages[0])->foreground());
    }
}

void MainWindow::slotReadyRead(){
    qDebug() << "kak dela";
    QDataStream in(socket);
    ui->progressBar->setValue(0);
    QThread::sleep(1);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        for(;;){
            if(nextblocksize == 0){
                if(socket->bytesAvailable() < 4){
                    break;
                }
                in >> nextblocksize;
                ui->progressBar->setValue(33);
                QThread::sleep(1);
            }
            if(socket->bytesAvailable() < nextblocksize){
                break;
            }
            ui->progressBar->setValue(66);
            QString status;
            in >> status;
            qDebug() << status << "\n";
            if(status == "connected"){
                QVector<std::pair<QString,QPixmap>> user;
                ui->listWidget->clear();
                qDebug() << "fefws";
                in >> user;
                for(int i = 0;i < user.size();i ++){
                    qDebug() << "qsize";
                    qDebug() << user[i].first << user[i].second;
                    QListWidgetItem *wer = new QListWidgetItem(QIcon(user[i].second),user[i].first);
                    ui->listWidget->addItem(wer);
                }
            }else if(status == "disconnected"){
                ui->listWidget->clear();
            }else if(status == "message"){
                if(cond == 1){
                QString body_of_message,username1;
                in >> body_of_message;
                in >> username1;
                history.push_back("Date/time:" + QDateTime::currentDateTime().toString() + " ip:127.0.0.1 " + "username: " + username1 + " message: " + body_of_message);
                QListWidgetItem *date =   new QListWidgetItem(QDateTime::currentDateTime().toString());
                date->setForeground(Qt::black);
                dates.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(date);
                QListWidgetItem *ip =   new QListWidgetItem("127.0.0.1");
                ip->setForeground(Qt::black);
                ips.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(ip);
                QListWidgetItem *user =   new QListWidgetItem(username1);
                user->setForeground(Qt::black);
                usernames.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(user);
                QListWidgetItem *mes =   new QListWidgetItem(body_of_message);
                mes->setForeground(Qt::black);
                messages.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(mes);
                update_colors();
                }
            }else if(status == "new_crypto"){
                crypto_key = !crypto_key;
            }else if(status == "stop_server"){
               on_actionDisconnect_triggered();
            }else if(status == "new_image"){
                QPixmap pip;
                in >> pip;
                QString username1;
                in >> username1;
                auto label = new QLabel();
                label->setPixmap(pip.scaled(320,240,Qt::IgnoreAspectRatio));
                QListWidgetItem *obj = new QListWidgetItem;
                obj->setSizeHint(label->sizeHint());
                ui->listWidget_2->addItem(obj);
                ui->listWidget_2->setItemWidget(obj,label);
                show_image[obj] = pip;
                QListWidgetItem *date =   new QListWidgetItem(QDateTime::currentDateTime().toString());
                date->setForeground(Qt::black);
                dates.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(date);
                QListWidgetItem *ip =   new QListWidgetItem("127.0.0.1");
                ip->setForeground(Qt::black);
                ips.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(ip);
                QListWidgetItem *user =   new QListWidgetItem(username1);
                user->setForeground(Qt::black);
                usernames.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(user);
                QString h ="Date/time:" + QDateTime::currentDateTime().toString() + " ip:127.0.0.1 " + "username: " + username1;
                h += "\n";
                QByteArray ba;
                ba.clear();
                QBuffer bu(&ba);
                pip.save(&bu, "PNG");
                QString imgBase64 = ba.toBase64();
                h += imgBase64;
                history.push_back(h);
                update_colors();
            }else if(status == "new_file"){
                qDebug() << "step 3";
                QString path,usr;
                in >> usr >> path;
                QFile *file = new QFile(path);
                QListWidgetItem *date = new QListWidgetItem(QDateTime::currentDateTime().toString());
                date->setForeground(Qt::black);
                dates.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(date);
                QListWidgetItem *ip =   new QListWidgetItem("127.0.0.1");
                ip->setForeground(Qt::black);
                ips.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(ip);
                QListWidgetItem *user =   new QListWidgetItem(usr);
                user->setForeground(Qt::black);
                usernames.push_back(ui->listWidget_2->count());
                ui->listWidget_2->addItem(user);
                QString h ="Date/time:" + QDateTime::currentDateTime().toString() + " ip:127.0.0.1 " + "username: " + usr;
                h += "\n";
                update_colors();
                if (file->open(QIODevice::ReadOnly)) {
                    QByteArray fileData = file->readAll();
                    QByteArray hashData = QCryptographicHash::hash(fileData, QCryptographicHash::Md5);
                    h += hashData.toBase64();
                }
                QLabel *qwe = new QLabel;
                qwe->setPixmap(QPixmap("/home/renat/Downloads/rere.png"));
                QListWidgetItem *goog = new QListWidgetItem(QIcon(qwe->pixmap())," ");
                paths[goog] = path;
                ui->listWidget_2->addItem(goog);
                history.push_back(h);
            }else{
                QVector<QString>s;
                in >> s;
                qDebug() << s[0] << " " << s[1];
                others_info *h = new others_info(nullptr,s);
                h->show();
            }
            QThread::sleep(1);
            ui->progressBar->setValue(100);
            nextblocksize = 0;
            cond = 0;
            break;
        }
    }

}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->pushButton->text() == "text"){
    sendToServer("message","afasd");
        qDebug() << "call ili ne call";
    }else if(ui->pushButton->text() == "image"){
        QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath());
        sendToServer("send_image",path);
    }else{
        QString path = QFileDialog::getSaveFileName(0, QObject::tr("Укажите путь для сохранения"), QDir::homePath());
        sendToServer("new_file",path);
        qDebug() << "step 1";
    }
}



void MainWindow::on_pushButton_clicked()
{
    q->show();
    connect(q,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(choose_type(QListWidgetItem*)));
}
void MainWindow::choose_type(QListWidgetItem *r)
{
    ui->pushButton->setText(r->text());
}

void MainWindow::on_actionSave_triggered()
{
    save_as *s  =new save_as(nullptr,history);
    s->show();
}

void MainWindow::on_actionchange_ava_triggered()
{
    change_ava *ch = new change_ava(nullptr,ava);
    ch->show();
    connect(ch,&change_ava::new_ava,this,&MainWindow::set_ava);
}

void MainWindow::set_ava(QString s)
{
    ava = QPixmap(s);
    sendToServer("new_ava","dfds");
}

QString MainWindow::rashifrovat_string(QString s)
{
    QByteArray data;
    data.clear();
    data = s.toUtf8();
    int y = 0;
    if(crypto_key){
        y = 1;
    }
    for(int i = 0;i < data.size();i ++){
        data[i] ^= y;
    }
    return QString(data);
}

QPixmap MainWindow::rashifrovat_pixmaop(QPixmap s)
{
    QByteArray a;
    a.clear();
    QBuffer buffer(&a);
    buffer.open(QIODevice::WriteOnly);
    s.save(&buffer, "PNG");
    int y = 0;
    if(crypto_key){
        y =0;
    }
    for(int i = 0;i < a.size();i ++){
        a[i] ^= y;
    }
    QPixmap ans;
    ans.loadFromData(a,"PNG");
    return ans;
}





void MainWindow::on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)
{
    if(item->text() != " "){
    images *i = new images(nullptr,show_image[item]);
    i->show();
    }else{
        local_path = paths[item];
        qDebug() << local_path << "\n";
        file_obr->show();
        connect(file_obr,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(file_obrobotka(QListWidgetItem*)));
    }
}
void MainWindow::file_obrobotka(QListWidgetItem *r)
{
    if(r->text() == "open"){
            QDesktopServices::openUrl(QUrl::fromLocalFile(local_path));

    }else{
        QFile *filer = new QFile(local_path);
        QStringList qwerty = filer->fileName().split('.');
        QFile *filer2 = new QFile();
        filer2->setFileName("/home/renat/ruka/noga/somefile."+ qwerty[qwerty.size() - 1]);
        QFile::copy(filer->fileName(),filer2->fileName());
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
     sendToServer("info",item->text());
}
void MainWindow::on_actionchange_background_color_triggered(){
    colors_background->show();
    connect(colors_background,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(change_background(QListWidgetItem*)));
}
void MainWindow::change_background(QListWidgetItem *r){
    ui->listWidget_2->setStyleSheet("background-color: " + r->text());
}

void MainWindow::on_actionchoose_info_color_triggered()
{

    colors_info->show();
    connect(colors_info,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(change_info_color(QListWidgetItem*)));
}
void MainWindow::change_info_color(QListWidgetItem *r)
{
    for(int i = 0;i < dates.size();i ++){
        ui->listWidget_2->item(dates[i])->setForeground(QColor(r->text()));
    }
    for(int i = 0;i < ips.size();i ++){
        ui->listWidget_2->item(ips[i])->setForeground(QColor(r->text()));
    }
    for(int i = 0;i < usernames.size();i ++){
        ui->listWidget_2->item(usernames[i])->setForeground(QColor(r->text()));
    }
}

void MainWindow::change_message_color(QListWidgetItem *r)
{
    for(int i = 0;i < messages.size();i ++){
        ui->listWidget_2->item(messages[i])->setForeground(QColor(r->text()));
    }
}

void MainWindow::on_actionchoose_message_color_triggered()
{
    colors_of_message->show();
    connect(colors_of_message,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(change_message_color(QListWidgetItem*)));

}

void MainWindow::on_actiondisplay_ip_3_triggered()
{
    if(!ui->actiondisplay_ip_3->isChecked()){
        qDebug() << "true";
        QBrush color = ui->listWidget_2->item(usernames[0])->foreground();
        for(int i = 0;i < ips.size();i ++){
            ui->listWidget_2->item(ips[i])->setForeground(color);
        }
    }else{
        QStringList q = ui->listWidget_2->styleSheet().split(' ');
        for(int i = 0;i < ips.size();i ++){
            ui->listWidget_2->item(ips[i])->setForeground(QColor(q[1]));
        }
    }
}
void MainWindow::on_actionhide_date_triggered()
{
    if(!ui->actionhide_date->isChecked()){
        qDebug() << "true";
        QBrush color = ui->listWidget_2->item(usernames[0])->foreground();
        for(int i = 0;i < dates.size();i ++){
            ui->listWidget_2->item(dates[i])->setForeground(color);
        }
    }else{
        QStringList q = ui->listWidget_2->styleSheet().split(' ');
        for(int i = 0;i < dates.size();i ++){
            ui->listWidget_2->item(dates[i])->setForeground(QColor(q[1]));
        }
    }
}
void MainWindow::on_actionclose_progress_bar_triggered()
{
    if(ui->actionclose_progress_bar->isChecked()){
        ui->progressBar->hide();
    }else{
        ui->progressBar->show();
    }
}
void MainWindow::on_actionautomatic_file_reception_triggered()
{
    if(ui->actionautomatic_file_reception->isChecked()){
        automatic_reception = true;
        qDebug() << "true";
    }else{
        automatic_reception = false;
        qDebug() << "false";
    }
}

void MainWindow::slotformaccept(bool s)
{
    if(s){
        cond = 1;
    }else{
        cond = 2;
    }
}


void MainWindow::on_buttonBox_accepted()
{
    cond = 1;
}


void MainWindow::on_buttonBox_rejected()
{
    cond = 2;

}

