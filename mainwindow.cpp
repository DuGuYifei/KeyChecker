#include "mainwindow.h"
#include <QThread>
#include <QGuiApplication>
#include <QScreen>
#include <string>


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
            &MainWindow::startWrappee);

}

void MainWindow::startWrappee()
{
    msgLabel = new MessageLabel(this);

    QStringList arguments;
    arguments << "";
    wrappeeProcess = new QProcess(this);
    wrappeeProcess->start("test.exe", arguments);
    if(wrappeeProcess->waitForStarted()) {
        msgLabel->addText("Start successfully!");
    }
    else {
        msgLabel->addText("Failed to start process! Please, restart");
    }
    while(!msgLabel->getMessagePipe()->waitConnect());
    msgLabel->getMessagePipe()->writeMsg("test");
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    msgLabel->getMessagePipe()->writeMsg(std::to_string(screenGeometry.width()).c_str());
    msgLabel->getMessagePipe()->writeMsg(std::to_string(screenGeometry.height()).c_str());
}

MainWindow::~MainWindow()
{
    this->wrappeeProcess->kill();
    msgLabel->getThread()->quit();
    msgLabel->getThread()->wait();
}

