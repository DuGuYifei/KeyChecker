#include "mainwindow.h"
#include "qthread.h"

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

    // when request pass close the button, and create message label
    connect(btnConfirm,
            &ConfirmSendPushButton::destroyed,
            this,
            [&]()->void{msgLabel = new MessageLabel(this);});

}

MainWindow::~MainWindow()
{
    msgLabel->getThread()->quit();
    msgLabel->getThread()->wait();
}

