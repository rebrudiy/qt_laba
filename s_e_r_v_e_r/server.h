#ifndef SERVER_H
#define SERVER_H
#include <QVector>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDateTime>
#include <QMap>
#include <QSslSocket>
#include <QPixmap>
#include <QFile>
class Server : public QTcpServer
{
Q_OBJECT
public:
QPixmap pip;
QString window_status;
    qint64 nextblocksize = 0;
    Server();
    QVector<QString>history;
    QTcpSocket *socket;
    bool crypto_key;
    QString ip;
    QFile *f;
    qint32 port;
    class User{
    public:
            bool soglasen;
            QString username;
            QString connect_date_time;
            QString user_status;
            QString user_ip_adress;
            QSslSocket socket;
            qint64 nextblocksize = 0;
            QPixmap ava;
    };
    void SomebodyDisConnected(QString str,QString username);
    QString rashifrovat_string(QString s);
    QPixmap rashifrovat_pixmaop(QPixmap s);
private:
    QVector<User*>users;
    QByteArray Data;
public slots:
    void incomingConnection(qintptr socketDescriptor);
    void outcomingDisconnection();
    void slotReadyRead();
    void slotchange_crypto_key();
    void slotchangehost();
    void sloton_server();
    void slotoff_server();
    void slotexit_server();
    void slotsave_server();
    void slotset_port(qint32 q);
    void slotset_ip(QString s);
signals:
    void window_status_changed(QString s);
    void need_to_print(QString mese);
};

#endif // SERVER_H
