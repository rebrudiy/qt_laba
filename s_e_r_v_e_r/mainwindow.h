#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int count_of_users = 0;
public slots:
    void set_user_count(bool new_user);
    void some_text(QString str);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
