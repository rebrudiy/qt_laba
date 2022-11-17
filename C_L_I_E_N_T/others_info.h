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
    explicit others_info(QWidget *parent,QVector<QString> q);
    ~others_info();

private:
    Ui::others_info *ui;
};

#endif // OTHERS_INFO_H
