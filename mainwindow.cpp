#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    keyEdit = new QLineEdit("Please input your key", this);
    btnConfirm = new ConfirmSendPushButton("Confirm", this, keyEdit);
    keyEdit->setFixedSize(400, 20);
    keyEdit->move(50,50);
    btnConfirm->move(460, 48);
    btnConfirm->setFixedSize(100, 24);
    this->setFixedSize(640, 100);
}

MainWindow::~MainWindow()
{
}

