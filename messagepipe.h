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
    MessagePipe(LPCSTR name);
    bool waitConnect();
    void writeMsg(const char* message);
    void readMsg();
    ~MessagePipe();

Q_SIGNALS:
    void receiveMsg(QString message);
};

#endif // MESSAGEPIPE_H
