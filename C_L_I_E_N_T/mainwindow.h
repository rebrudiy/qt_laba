#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QSettings>
#include <QSslSocket>
#include <QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_actionConnect_triggered();
    void on_actionDisconnect_triggered();
    void on_actionExit_triggered();
    void on_push_button_triggered();
    void on_actionusername_triggered();
    void set_new_usename(QString str);
    void set_new_status(QString str);
    void on_actionhost_triggered();
    void set_new_ip(QString s);
    void set_new_port(qint32 q);
    void on_actionAbout_triggered();
    void slotReadyRead();
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_actionSave_triggered();

public:
    Ui::MainWindow *ui;
    QSslSocket *socket;
    QByteArray Data;
    QString username;
    QString user_status;
    qint64 port;
    QString ip;
    bool isconnected;
    QSettings *setting;
    void uploadsettings();
    void setsetings();
    void sendToServer(QString str,QString str2);
};
#endif // MAINWINDOW_H
