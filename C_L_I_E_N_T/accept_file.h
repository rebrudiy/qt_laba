#ifndef ACCEPT_FILE_H
#define ACCEPT_FILE_H

#include <QDialog>

namespace Ui {
class accept_file;
}

class accept_file : public QDialog
{
    Q_OBJECT

public:
    explicit accept_file(QWidget *parent = nullptr);
    ~accept_file();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();
signals:
    void f(bool);
private:
    Ui::accept_file *ui;
};

#endif // ACCEPT_FILE_H
