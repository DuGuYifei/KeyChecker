#ifndef MESSAGEPIPE_H
#define MESSAGEPIPE_H

#include <QObject>
#include <windows.h>

const int BUFSIZE = 1024;

class MessagePipe : public QObject
{
    Q_OBJECT
private:
    HANDLE hPipe;
    TCHAR chReadBuf[BUFSIZE];
    DWORD dwRead, dwWritten;

public:
    MessagePipe(LPCWSTR name);
    bool waitConnect();
    void writeMsg(LPTSTR lpvMessage);
    void readMsg();
    ~MessagePipe();

Q_SIGNALS:
    void receiveMsg(QString lpvMessage);
};

#endif // MESSAGEPIPE_H
