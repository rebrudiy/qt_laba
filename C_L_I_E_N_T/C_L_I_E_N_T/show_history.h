#ifndef SHOW_HISTORY_H
#define SHOW_HISTORY_H
#include <QListWidget>
#include <QMainWindow>
#include <QFile>
namespace Ui {
class show_history;
}

class show_history : public QMainWindow
{
    Q_OBJECT

public:

    show_history(QWidget *parent,QListWidget *s,QVector<QString> r);
    QVector<QString>hist;
    QFile *ans;
    ~show_history();
signals:
    void again();
private slots:
    void on_actionabout_triggered();

    void on_actionchat_triggered();

    void on_actionexit_triggered();

    void on_actionopen_triggered();

private:
    Ui::show_history *ui;
};

#endif // SHOW_HISTORY_H
