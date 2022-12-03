#ifndef NICKNAME_H
#define NICKNAME_H

#include <QDialog>

namespace Ui {
class nickname;
}

class nickname : public QDialog
{
    Q_OBJECT

public:
    qint32 x = 0;
    QString str;
    explicit nickname(QWidget *parent = nullptr,QString str = "user");
    ~nickname();

private slots:
    void on_pushButton_clicked();

private:
    Ui::nickname *ui;
signals:
    void new_username(QString str);
};

#endif // NICKNAME_H
