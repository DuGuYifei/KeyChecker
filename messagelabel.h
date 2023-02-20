#ifndef MESSAGELABEL_H
#define MESSAGELABEL_H

#include <QLabel>
#include <QQueue>
#include "messagepipe.h"

class MessageLabel : public QLabel
{
private:
    QQueue<QString> msgQue;
    MessagePipe* messagePipe;
    QThread* thread;
public:
    MessageLabel(QWidget* parent = nullptr);
    void connectPipe();
    void addText(QString text);
    void startTimer();
    QThread *getThread() const;
};

#endif // MESSAGELABEL_H
