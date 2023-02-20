#include "messagelabel.h"
#include <QThread>
#include <QTimer>

QThread *MessageLabel::getThread() const
{
    return thread;
}

MessageLabel::MessageLabel(QWidget *parent) : QLabel(parent)
{
    parent->setFixedSize(600, 400);
    parent->move(600, 400);
    this->setGeometry(20,20,parent->width() - 40, parent->height() - 40);
    this->setAlignment(Qt::AlignLeft);

    this->messagePipe = new MessagePipe(L"\\\\.\\pipe\\my_pipe");
    while(!this->messagePipe->waitConnect());
    thread = new QThread(this);
    this->messagePipe->moveToThread(thread);
    connect(thread, &QThread::started, this, &MessageLabel::startTimer);
    connect(messagePipe, &MessagePipe::receiveMsg, this, &MessageLabel::addText);
    thread->start();
    this->show();
}

void MessageLabel::addText(QString text)
{
    msgQue.push_back(text);
    if(msgQue.size() > 10)
        msgQue.pop_front();
    QString sumText;
    for(QString str : msgQue)
        sumText.append(str + "\n");

    this->setText(sumText);
}


void MessageLabel::startTimer()
{
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, messagePipe, &MessagePipe::readMsg);
    timer->start(1000);
}
