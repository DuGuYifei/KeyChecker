#include "messagepipe.h"
#include <QDebug>

MessagePipe::MessagePipe(LPCWSTR name)
{
    // Create named pipe
    hPipe = CreateNamedPipe(name,
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

void MessagePipe::writeMsg(LPTSTR lpvMessage)
{
    // Pipe connected; send message to aother client
    WriteFile(hPipe, lpvMessage, (lstrlen(lpvMessage) + 1) * sizeof(TCHAR), &dwWritten, NULL);
}

void MessagePipe::readMsg()
{
    if(PeekNamedPipe(hPipe, NULL, 0, NULL, &dwRead, NULL))
    {
        ReadFile(hPipe, chReadBuf, BUFSIZE * sizeof(TCHAR), &dwRead, NULL);
        FlushFileBuffers(hPipe);
        qDebug() << (const char*)chReadBuf;
        emit this->receiveMsg((const char*)chReadBuf);
    }
}

MessagePipe::~MessagePipe()
{
    // Disconnect the pipe
    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
}
