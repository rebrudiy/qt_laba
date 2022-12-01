#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QSettings>
#include <QSslSocket>
#include <QListWidgetItem>
#include <QtXml>
#include <QDialogButtonBox>
#include "accept_file.h"
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
    void choose_type(QListWidgetItem *r);
    void on_pushButton_clicked();
    void on_actionSave_triggered();
    void file_obrobotka(QListWidgetItem *r);
    void on_actionchange_ava_triggered();
    void set_ava(QString s);
    void change_background(QListWidgetItem *r);
    void change_info_color(QListWidgetItem * r);
    void change_message_color(QListWidgetItem * r);
    void on_listWidget_2_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_actionchange_background_color_triggered();
    void on_actionchoose_info_color_triggered();
    void on_actionchoose_message_color_triggered();
    void on_actiondisplay_ip_3_triggered();
    void on_actionhide_date_triggered();
    void on_actionclose_progress_bar_triggered();
    void on_actionautomatic_file_reception_triggered();
    void slotformaccept(bool s);
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

public:
    QListWidget *colors_info;
    QListWidget *colors_background;
    QListWidget *colors_of_message;
    bool crypto_key;
    bool socket_cond;
    qint64 nextblocksize;
    Ui::MainWindow *ui;
    QSslSocket *socket;
    QByteArray Data;
    bool counter;
    QString username;
    QString user_status;
    qint64 port;
    QString ip;
    QMap<QListWidgetItem*,QPixmap>show_image;
    QPixmap ava;
    bool isconnected;
    QSettings *setting;
    QVector<QString>history;
    QVector<int>dates;
    QVector<int>ips;
    QVector<int>messages;
    QString local_path;
    QVector<int>usernames;
    QListWidget *q;
    QListWidget *file_obr;
    QListWidgetItem *text,*image,*file;
    bool automatic_reception;
    QMap<QListWidgetItem*,QString>paths;
    QString rashifrovat_string(QString s);
    QPixmap rashifrovat_pixmaop(QPixmap s);
    int cond;
    void uploadsettings();
    void setsetings();
    void sendToServer(QString str,QString str2);
    void update_colors();
};
#endif // MAINWINDOW_H
