#include "mainwindow.h"
#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server s;
    w.show();
    w.setWindowTitle("no work");
    MainWindow::connect(&s,&Server::need_to_print,&w,&MainWindow::some_text);
    Server::connect(&w,&MainWindow::new_crypto_key,&s,&Server::slotchange_crypto_key);
    Server::connect(&w,&MainWindow::new_hosty,&s,&Server::slotchangehost);
    Server::connect(&w,&MainWindow::on_server,&s,&Server::sloton_server);
    Server::connect(&w,&MainWindow::off_server,&s,&Server::slotoff_server);
    Server::connect(&w,&MainWindow::exit_server,&s,&Server::slotexit_server);
    Server::connect(&w,&MainWindow::save_server,&s,&Server::slotsave_server);
    MainWindow::connect(&s,&Server::window_status_changed,&w,&MainWindow::set_new_windows_status);
    return a.exec();
}
