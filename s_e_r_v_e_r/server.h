#ifndef SERVER_H
#define SERVER_H
#include <QVector>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
#include <QMap>
#include <QSslSocket>
class Server : public QTcpServer
{
Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    class User{
    public:
            QString username;
            QString connect_date_time;
            QString user_status;
            QString user_ip_adress;
            QSslSocket socket;
    };
    void SomebodyDisConnected(QString str,QString username);
private:
    QVector<User*>users;
    QByteArray Data;
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void outcomingDisconnection();
    void slotReadyRead();
signals:
    void users_count_changed(bool newuser);
    void need_to_print(QString mese);
};

#endif // SERVER_H
