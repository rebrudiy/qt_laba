#ifndef STATUS_BUTTOM_H
#define STATUS_BUTTOM_H

#include <QDialog>

namespace Ui {
class status_buttom;
}

class status_buttom : public QDialog
{
    Q_OBJECT
public:
    qint32 x = 0;
    QString status;
    explicit status_buttom(QWidget *parent = nullptr,QString s = "fsjfjhsdfpoijsdhsd");
    ~status_buttom();
private:
    Ui::status_buttom *ui;
private slots:
    void on_pushButton_clicked();
signals:
    void send_status(QString s);
};

#endif // STATUS_BUTTOM_H
