#include "server.h"
Server::Server()
{
    if(this->listen(QHostAddress::Any, 45678)){
        qDebug() << "success";
    }else{
        qDebug() << "Fail";
    }
}
void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QSslSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QSslSocket::readyRead,this,&Server::slotReadyRead);
    connect(socket,&QSslSocket::disconnected,this,&Server::outcomingDisconnection);
    emit users_count_changed(true);
}
void Server::slotReadyRead(){
    socket = (QSslSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if(in.status() == QDataStream::Ok){
        QString request_type;
        in >> request_type;
        qDebug() << request_type;
        if(request_type == "new_user"){
            Server::User *us = new Server::User;
            QMap<QString,QString> a;
            in >> a;
            us->socket.setSocketDescriptor(socket->socketDescriptor());
            us->connect_date_time = QDateTime::currentDateTime().toString();
            us->user_status = a["user_status"];
            us->username = a["user_name"];
            us->user_ip_adress = "127.0.0.1";
            users.push_back(us);
            SomebodyDisConnected("connected","er");
            emit need_to_print(us->username + "connected to server" + "\n");
        }else if(request_type == "new_status"){
            QString new_status;
            in >> new_status;
            if(users.size() == 1){
                emit need_to_print(users[0]->username + "status chaned to " + new_status + "\n");
                users[0]->user_status = new_status;
            }else{
            for(int i = 0;i < users.size();i ++){
                if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                    emit need_to_print(users[i]->username + "status chaned to " + new_status + "\n");
                    users[i]->user_status = new_status;
                    break;
                }
            }
            }
        }else if(request_type == "new_username"){
            QString new_name;
            in >> new_name;
            if(users.size() == 1){
                emit need_to_print(users[0] ->username + "now is " + new_name + "\n");
                users[0]->username = new_name;
            }
            for(int i = 0;i < users.size();i ++){
                if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                    emit need_to_print(users[i] ->username + "now is" + new_name + "\n");
                    users[i]->username = new_name;
                    break;
                }
            }
            SomebodyDisConnected("connected","fs");
        }else if(request_type == "message"){
            QString message;
            in >> message;
            QString g;
            g += "Current date/time: " + QDateTime::currentDateTime().toString() + "\n";
            g += "ip adress 127.0.0.1\n";
            if(users.size() == 1){
                emit need_to_print(users[0]->username + " Send message\n");
                g+= "Username: " + users[0]->username + "\n";
                g+= "Message " + message + "\n";
                SomebodyDisConnected("message",g);
                return;
            }
            for(int i = 0;i < users.size();i ++){
                if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
                    emit need_to_print(users[i]->username + " Send message\n");
                    g+= "Username: " + users[i]->username + "\n";
                    g+= "Message " + message + "\n";
                    break;
                }
            }
            SomebodyDisConnected("message",g);
        }else{
            qDebug() << request_type;
            qDebug()<<"STEP 1";
            QString name;
            in >> name;
            qDebug() << name;
            for(int i = 0;i < users.size();i ++){
                if(name == users[i]->username){
                    qDebug() << "sTEP 2";
                    SomebodyDisConnected("username",QString::number(i));
                    break;
                }
            }
        }
    }else{
        qDebug() << "Error with send";
    }

}
void Server::SomebodyDisConnected(QString cond,QString username){
    Data.clear();
    QDataStream out(&Data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << cond;
    qDebug() << "ebtipeorpgo epjie";
    if(cond == "connected"){
        QVector<QString>q;
        for(int i = 0;i < users.size();i ++){
            q.push_back(users[i]->username);
            qDebug() << users.size();
        }
        out << q;
        for(int i = 0;i < users.size();i ++){
            users[i]->socket.write(Data);
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
        users[ind]->socket.write(Data);
        return;
    }
    out << username;
    qDebug() << "jooom";
    for(int i = 0;i < users.size();i ++){
      users[i]->socket.write(Data);
  }
}

void Server::outcomingDisconnection(){
    socket = (QSslSocket*)sender();
    if(users.size() == 1){
        emit need_to_print(users[0]->username + " left from server\n");
        users.removeAt(0);
    }
    for(int i = 0;i < users.size();i ++){
        qDebug() << users[i]->socket.socketDescriptor()<< " " <<socket->socketDescriptor() << "\n";

        if(users[i]->socket.socketDescriptor() == socket->socketDescriptor()){
            emit need_to_print(users[i]->username + " left from server\n");
            users.removeAt(i);
            break;
        }
    }
    SomebodyDisConnected("connected","sdfs");
    emit users_count_changed(false);
}
