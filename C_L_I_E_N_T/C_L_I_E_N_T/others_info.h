#ifndef OTHERS_INFO_H
#define OTHERS_INFO_H

#include <QDialog>

namespace Ui {
class others_info;
}

class others_info : public QDialog
{
    Q_OBJECT

public:
    QVector<QString>q1;
    QString path;
    QString date;
    explicit others_info(QWidget *parent,QVector<QString> q);
    ~others_info();

private slots:
    void on_pushButton_clicked();

private:
    Ui::others_info *ui;
signals:
    void f(QString path,QString username);
};

#endif // OTHERS_INFO_H
