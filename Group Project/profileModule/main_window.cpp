#include "main_window.h"
#include "ui_mainwindow.h"
#include "userwindow.h"
#include "guestwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    hide();
    userwindow userwindowobj;
    userwindowobj.setModal(true);
    userwindowobj.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    hide();
    guestwindow guestwindowobj;
    guestwindowobj.setModal(true);
    guestwindowobj.exec();
}
