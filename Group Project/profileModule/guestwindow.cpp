#include "guestwindow.h"
#include "ui_guestwindow.h"

guestwindow::guestwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::guestwindow)
{
    ui->setupUi(this);
}

guestwindow::~guestwindow()
{
    delete ui;
}
