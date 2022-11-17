#ifndef HOST_H
#define HOST_H

#include <QDialog>

namespace Ui {
class host;
}

class host : public QDialog
{
    Q_OBJECT

public:
    QString ip;
    qint32 port;
    explicit host(QWidget *parent = nullptr,QString ip = "127.0.0.1",qint32 port = 5678);
    ~host();

private:
    Ui::host *ui;
signals:
    void change_ip(QString s);
    void change_port(qint32 q);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // HOST_H
