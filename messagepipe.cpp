#include "messagepipe.h"
#include <QCoreApplication>


MessagePipe::MessagePipe(LPCSTR name)
{
    // Create named pipe
    hPipe = CreateNamedPipeA(name,
                            PIPE_ACCESS_DUPLEX,
                            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                            PIPE_UNLIMITED_INSTANCES,
                            BUFSIZE,
                            BUFSIZE,
                            0,
                            NULL);
    //    if (hPipe == INVALID_HANDLE_VALUE) {
    //        qDebug() << "Error creating named pipe: " << GetLastError();
    //        return;
    //    }
}

bool MessagePipe::waitConnect()
{
    // Wait for the client to connect
    while (ConnectNamedPipe(hPipe, NULL) != TRUE) {
        if (GetLastError() == ERROR_PIPE_CONNECTED) {
            return false;
        }
    }
    return true;
}

void MessagePipe::writeMsg(const char* message)
{
    // Pipe connected; send message to aother client
    WriteFile(hPipe, message, strlen(message), &dwWritten, NULL);
    FlushFileBuffers(hPipe);
}

void MessagePipe::readMsg()
{
    if(PeekNamedPipe(hPipe, chReadBuf, BUFSIZE * sizeof(TCHAR), NULL, &dwRead, NULL))
    {
        if(dwRead == 0)
            return;
        QString bufMsg = (const char*)chReadBuf;
        if(bufMsg.startsWith("server:"))
            return;
        memset(chReadBuf, 0, sizeof(chReadBuf));
        ReadFile(hPipe, chReadBuf, BUFSIZE * sizeof(TCHAR), &dwRead, NULL);
        // qDebug() << (const char*)chReadBuf;
        emit this->receiveMsg((const char*)chReadBuf);
        if(strcmp((const char*)chReadBuf, "client:已断开") == 0)
            QCoreApplication::quit();
    }
}

MessagePipe::~MessagePipe()
{
    // Disconnect the pipe
    // FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
}
