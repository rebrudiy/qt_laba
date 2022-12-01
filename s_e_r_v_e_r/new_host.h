#ifndef NEW_HOST_H
#define NEW_HOST_H

#include <QDialog>

namespace Ui {
class new_host;
}

class new_host : public QDialog
{
    Q_OBJECT

public:
    qint32 port;
    QString ip;
    explicit new_host(QWidget *parentr,QString ip,qint32 port);
    ~new_host();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void new_port(qint32 q);
    void new_ip(QString q);
private:
    Ui::new_host *ui;
};

#endif // NEW_HOST_H
