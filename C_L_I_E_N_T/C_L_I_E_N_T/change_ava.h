#ifndef CHANGE_AVA_H
#define CHANGE_AVA_H
#include <QMainWindow>
#include <QDialog>

namespace Ui {
class change_ava;
}

class change_ava : public QDialog
{
    Q_OBJECT

public:
    QPixmap pic;
    explicit change_ava(QMainWindow *parent,QPixmap a);
    ~change_ava();

private slots:
    void on_pushButton_clicked();

private:
    Ui::change_ava *ui;
signals:
    void new_ava(QString s);
};

#endif // CHANGE_AVA_H
