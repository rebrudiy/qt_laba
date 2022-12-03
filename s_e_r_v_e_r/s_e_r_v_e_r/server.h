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
#include <QRunnable>
#include <QThread>
class Worker : public QObject
{
    Q_OBJECT
public:
    QString date;
    QString client_date;
    qint32 id;
    Worker(QString _date,QString _client_date,qint32 _id){
        date =_date;
        client_date = _client_date;
        id = _id;
    }
public slots:
    void doWork() {
        if(date == client_date){
        emit resultReady(true,date,client_date,id);
        }else{
            emit resultReady(false,date,client_date,id);
        }
    }

signals:
    void resultReady(bool ans,QString date,QString client_Date,qint32 id);
};
class Controller : public QObject
{
    Q_OBJECT
    QThread workerThread;
    QString date;
    QString client_date;
    qint32 id;

public:
    Controller(QString _date,QString _client_date,qint32 _id) {
        date = _date;
        client_date = _client_date;
        id = _id;
        Worker *worker = new Worker(date,client_date,id);
        worker->moveToThread(&workerThread);
        connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        connect(this, &Controller::operate, worker, &Worker::doWork);
        connect(worker, &Worker::resultReady, this, &Controller::handleResults);
        workerThread.start();
    }
    ~Controller() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(bool ans,QString date,QString client_Date,qint32 id){
        if(ans){
            emit to_server(id);
        }
    }
signals:
    void operate();
    void to_server(qint32 id);
};
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
    qint32 global_id;
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
public:
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
    void obrabotka(qint32 id);
signals:
    void window_status_changed(QString s);
    void need_to_print(QString mese);
};
#endif // SERVER_H
