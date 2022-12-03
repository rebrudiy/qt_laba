#include "accept_file.h"
#include "ui_accept_file.h"

accept_file::accept_file(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::accept_file)
{
    ui->setupUi(this);
}

accept_file::~accept_file()
{
    delete ui;
}

void accept_file::on_buttonBox_accepted()

{
    emit f(true);
    this->close();
}


void accept_file::on_buttonBox_rejected()
{
    emit f(false);
    this->close();
}

