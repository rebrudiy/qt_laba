#ifndef IMAGES_H
#define IMAGES_H

#include <QDialog>

namespace Ui {
class images;
}

class images : public QDialog
{
    Q_OBJECT

public:
    QPixmap som;
    explicit images(QWidget *parent,QPixmap s);
    ~images();

private slots:
    void on_pushButton_clicked();

private:
    Ui::images *ui;
};

#endif // IMAGES_H
