#include "server.h"
#include <QBuffer>
#include <QTimer>
#include "new_host.h"
#include "save_as_xml.h"
#include <QApplication>
#include <QFile>
#include <QBuffer>
#include <QLabel>
#include <QScrollBar>
#include <QFileDialog>
Server::Server()
{

    f = new QFile();
    port = 45678;
    ip = "127.0.0.1";
    nextblocksize = 0;
    crypto_key = true;
    window_status = "server off";

}
void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QSslSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QSslSocket::readyRead,this,&Server::slotReadyRead);
    connect(socket,&QSslSocket::disconnected,this,&Server::outcomingDisconnection);
}
void Server::slotReadyRead(){
    socket = (QSslSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        for(;;){
            if(nextblocksize == 0){
                if(socket->bytesAvailable() < 4){
                    break;
                }
                in >> nextblocksize;
            }
            if(socket->bytesAvailable() < nextblocksize){
                break;
            }
            QString request_type;
            in >> request_type;
            request_type = rashifrovat_string(request_type);
            if(request_type == "new_user"){
                Server::User *us = new Server::User;
                QMap<QString,QString> a;
                in >> a;
                us->socket.setSocketDescriptor(socket->socketDescriptor());
                us->connect_date_time = QDateTime::currentDateTime().toString();
                us->user_status = rashifrovat_string(a["user_status"]);
                us->username = rashifrovat_string(a["user_name"]);
                us->user_ip_adress = "127.0.0.1";
                qDebug() << "sfsw";
                QPixmap x;
                in >> x;
                x = QPixmap(rashifrovat_pixmaop(x));
                qDebug() << x << "wchhww";
                us->ava = QPixmap(x);
                qDebug() << us->ava << "sejfwef";
                users.push_back(us);
                window_status = ip + ":" + QString::number(port) + " " + QString::number(users.size());
                emit window_status_changed(window_status);
                SomebodyDisConnected("connected","er");
                emit need_to_print(us->username + "connected to server" + "\n");
                history.push_back(us->username + "connected to server" + "\n");
            }else if(request_type == "new_status"){
                QString new_status;
                in >> new_status;
                new_status = rashifrovat_string(new_status);
                if(users.size() == 1){
                    emit need_to_print(users[0]->username + "status chaned to " + new_status + "\n");
                    history.push_back(users[0]->username + "status chaned to " + new_status + "\n");
                    users[0]->user_status = new_status;
                }else{
                    for(int i = 0;i < users.size();i ++){
                        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                            emit need_to_print(users[i]->username + "status chaned to " + new_status + "\n");
                            history.push_back(users[i]->username + "status chaned to " + new_status + "\n");
                            users[i]->user_status = new_status;
                            break;
                        }
                    }
                }
            }else if(request_type == "new_username"){
                QString new_name;
                in >> new_name;
                new_name = rashifrovat_string(new_name);
                if(users.size() == 1){
                    emit need_to_print(users[0] ->username + "now is " + new_name + "\n");
                    history.push_back(users[0] ->username + "now is " + new_name + "\n");
                    users[0]->username = new_name;
                }
                for(int i = 0;i < users.size();i ++){
                    if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                        emit need_to_print(users[i] ->username + "now is" + new_name + "\n");
                        history.push_back(users[i] ->username + "now is " + new_name + "\n");
                        users[i]->username = new_name;
                        break;
                    }
                }
                SomebodyDisConnected("connected","fs");
            }else if(request_type == "message"){
                QString message;
                in >> message;
                message = rashifrovat_string(message);
                if(users.size() == 1){
                    emit need_to_print(users[0]->username + " Send message\n");
                    history.push_back(users[0]->username + " Send message\n");
                    message += " " + users[0]->username;
                    SomebodyDisConnected("message",message);
                    nextblocksize = 0;
                    return;
                }
                for(int i = 0;i < users.size();i ++){
                    if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                        emit need_to_print(users[i]->username + " Send message\n");
                        history.push_back(users[i]->username + " Send message\n");
                        message += " " + users[i]->username;
                        break;
                    }
                }
                SomebodyDisConnected("message",message);
            }else if(request_type == "new_ava"){
                QPixmap new_ava;
                in >> new_ava;
                new_ava = rashifrovat_pixmaop(new_ava);
                if(users.size() == 1){
                    emit need_to_print(users[0]->username + "ava chaned to \n");
                    history.push_back(users[0]->username + "ava chaned to \n");
                    users[0]->ava = QPixmap(new_ava);
                }else{
                    for(int i = 0;i < users.size();i ++){
                        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                            emit need_to_print(users[i]->username + "ava chaned to \n");
                            history.push_back(users[i]->username + "ava chaned to \n");
                            users[i]->ava  = QPixmap(new_ava);
                            break;
                        }
                    }
                }
                SomebodyDisConnected("connected","a");
            }else if(request_type == "send_image"){
                in >> pip;
                pip = rashifrovat_pixmaop(pip);
                QString usn;
                if(users.size() == 1){
                    usn =users[0]->username;
                }else{
                    for(int i = 0;i <users.size();i++){
                        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                            usn = users[i]->username;
                            break;
                        }
                    }
                }
                SomebodyDisConnected("new_image",usn);
            }else if(request_type == "new_file"){
                qDebug() << "step zero";
                QString usn,path;
                in >> path;
                if(users.size() == 1){
                    usn =users[0]->username;
                }else{
                    for(int i = 0;i <users.size();i++){
                        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                            usn = users[i]->username;
                            break;
                        }
                    }
                }
                SomebodyDisConnected("new_file","sobaka " + usn + " " + path);
            }else if(request_type == "accept"){
                SomebodyDisConnected("accept","fsf");
            }else if(request_type == "current_file"){
                qDebug() << "done gundone";
                QStringList e;
                QString need_to_parse;
                in >> need_to_parse;
                e = need_to_parse.split('^');
                QString path = e[0];
                QString _to = e[1];
                QString _from;
                qDebug() << "path" << " " << path;
                qDebug() << "_to" << " " << _to;
                if(users.size() == 1){
                    _from =users[0]->username;
                }else{
                    for(int i = 0;i <users.size();i++){
                        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                            _from = users[i]->username;
                            break;
                        }
                    }
                }
                SomebodyDisConnected("new_file","koshka^" + _from + "^" + path + "^" + _to);
            }else{
                qDebug() << request_type;
                qDebug()<<"STEP 1";
                QString name;
                in >> name;
                name = rashifrovat_string(name);
                qDebug() << name;
                for(int i = 0;i < users.size();i ++){
                    if(name == users[i]->username){
                        qDebug() << "sTEP 2";
                        SomebodyDisConnected("username",QString::number(i));
                        break;
                    }
                }
            }
            nextblocksize = 0;
            break;
        }
    }else{
        qDebug() << "Error with send";
    }

}

void Server::slotchange_crypto_key()
{
    crypto_key = !crypto_key;
    SomebodyDisConnected("new_crypto","eba");
    for(int i = 0;i < users.size();i ++){
        emit need_to_print(users[i]->username + " leave \n");
        history.push_back(users[i]->username + " leave \n");

    }
    for(int i = 0;i < users.size();i ++){
        emit need_to_print(users[i]->username + " connect \n");
        history.push_back(users[i]->username + " connect \n");
    }

}

void Server::slotchangehost()
{
    new_host *h = new new_host(nullptr,ip,port);
    h->show();
    connect(h,&new_host::new_ip,this,&Server::slotset_ip);
    connect(h,&new_host::new_port,this,&Server::slotset_port);

}

void Server::sloton_server()
{
    window_status = ip + ":" + QString::number(port) + " " + QString::number(users.size());
    emit window_status_changed(window_status);
    if(this->listen(QHostAddress(ip), port)){
        qDebug() << "success";
    }else{
        qDebug() << "Fail";
    }
}

void Server::slotoff_server()
{
    SomebodyDisConnected("stop_server","google");
    history.clear();
    emit need_to_print("clear");
    this->close();
}

void Server::slotexit_server()
{
    SomebodyDisConnected("stop_server","google");
    this->close();
    QApplication::quit();
}

void Server::slotsave_server()
{
    save_as_xml *s = new save_as_xml(nullptr,history);
    s->show();
}


void Server::slotset_port(qint32 q)
{
    window_status = "no work";
    emit window_status_changed(window_status);
    slotoff_server();
    port = q;
}

void Server::slotset_ip(QString s)
{
    ip = s;
    slotoff_server();
    window_status = "no work";
    emit window_status_changed(window_status);
}

void Server::obrabotka(qint32 id)
{
    global_id = id;
    qDebug()<< "canananananananda";
}
void Server::SomebodyDisConnected(QString cond,QString username){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << qint64(0);
    out << cond;
    qDebug() << "ebtipeorpgo epjie";
    if(cond == "connected"){
        QVector<std::pair<QString,QPixmap>>q;
        for(int i = 0;i < users.size();i ++){
            q.push_back({users[i]->username,users[i]->ava});
            qDebug() << users.size();
            qDebug() << users[i]->username << users[i]->ava;
        }
        out << q;
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        qDebug() << users.size();
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
            qDebug() << users[i]->username;
        }
        return;
    }
    if(cond == "new_image"){
        out << pip;
        QString inf = username;
        out << inf;
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        qDebug() << users.size();
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
            qDebug() << users[i]->username;
        }
        return;
    }
    if(cond == "username"){
        qDebug() << "Step 4";
        qint32 ind = username.toInt();
        QVector<QString>q;
        q.push_back(users[ind]->connect_date_time);
        q.push_back(users[ind]->user_status);
        out << q;
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        users[ind]->socket.write(Data);
        nextblocksize = 0;
        return;
    }
    if(cond == "new_crypto"){
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
        }
        return;
    }
    if(cond == "stop_server"){
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
        }
        qDebug() << "zhest";
        return;
    }
    if(cond == "new_file"){
        qDebug() << "step 1";
        QStringList q = username.split(' ');
        if(q[0] == "sobaka"){
        out << q[1] << q[2];
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
        }
        }else{
            QStringList q1 = username.split('^');
            QString _from = q1[1];
            QString _path = q1[2];
            QString _to = q1[3];
            qDebug() << "_from" << _from;
            qDebug() << "_path" << _path;
            qDebug() << "_to" << _to;
            out << q1[1] << q1[2];
            out.device()->seek(0);
            out << qint64(Data.size() - sizeof(qint64));
            for(int i = 0;i < users.size();i ++){
                Controller *r = new Controller(users[i]->connect_date_time,_to,i);
                connect(r,&Controller::to_server,this,&Server::obrabotka);
            }
            users[global_id]->socket.write(Data);
        }
        qDebug() << "zhest";
        return;
    }
    if(cond == "accept"){
        out.device()->seek(0);
        out << qint64(Data.size() - sizeof(qint64));
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
        }
        return;
    }
    QStringList data = username.split(' ');
    QString body_of_message = data[0];
    QString user_name = data[1];
    out << body_of_message;
    out << user_name;
    out.device()->seek(0);
    out << qint64(Data.size() - sizeof(qint64));
    qDebug() << "jooom";
    for(int i = 0;i < users.size();i ++){
      users[i]->socket.write(Data);
    }
}

QString Server::rashifrovat_string(QString s)
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

QPixmap Server::rashifrovat_pixmaop(QPixmap s)
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

void Server::outcomingDisconnection(){
    socket = (QSslSocket*)sender();
    qDebug() << "users ocunt" << users.size();
    if(users.size() == 1){
        emit need_to_print(users[0]->username + " left from server\n");
        history.push_back(users[0]->username + " left from server\n");
        users.removeAt(0);
        window_status = ip + ":" + QString::number(port) + " " + QString::number(users.size());
        emit window_status_changed(window_status);
    }else{
    for(int i = 0;i < users.size();i ++){
        qDebug() << users[i]->socket.socketDescriptor()<< " " <<socket->socketDescriptor() << "\n";

        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
            emit need_to_print(users[i]->username + " left from server\n");
            history.push_back(users[i]->username + " left from server\n");

            users.removeAt(i);
            break;
        }
    }
    window_status = ip + ":" + QString::number(port) + " " + QString::number(users.size());
    emit window_status_changed(window_status);
    }
    qDebug() << "users ocunt" << users.size();
    SomebodyDisConnected("connected","sdfs");
}
