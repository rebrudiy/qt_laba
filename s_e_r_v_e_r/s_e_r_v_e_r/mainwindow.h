#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int count_of_users = 0;
public slots:
    void some_text(QString str);
    void set_new_windows_status(QString str);
private slots:
    void on_actionchange_key_triggered();
    void on_actionchange_ip_port_triggered();

    void on_actionon_triggered();

    void on_actionoff_triggered();

    void on_actionsava_triggered();

    void on_actionexit_triggered();
signals:
    void new_crypto_key();
    void new_hosty();
    void on_server();
    void off_server();
    void exit_server();
    void save_server();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
