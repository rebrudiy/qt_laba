#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server s;
    w.setWindowTitle("Server host is 127.0.0.45678 Count of users: " + QString::number(w.count_of_users));
    w.show();
    MainWindow::connect(&s,&Server::users_count_changed,&w,&MainWindow::set_user_count);
    MainWindow::connect(&s,&Server::need_to_print,&w,&MainWindow::some_text);
    return a.exec();
}
