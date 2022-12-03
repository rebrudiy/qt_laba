#ifndef SAVE_AS_H
#define SAVE_AS_H
#include <QDialog>
namespace Ui {
class save_as_xml;
}

class save_as_xml : public QDialog
{
    Q_OBJECT

public:
    QVector<QString> r;
    explicit save_as_xml(QWidget *parent,QVector<QString> s);
    ~save_as_xml();

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::save_as_xml *ui;
};

#endif // SAVE_AS_H
