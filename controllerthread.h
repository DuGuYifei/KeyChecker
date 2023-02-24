#ifndef CONTROLLERTHREAD_H
#define CONTROLLERTHREAD_H

#include <windows.h>
#include <QThread>

struct MyData {
    int x;
    int y;
    bool isPressing;
};


class ControllerThread : public QThread
{
private:
    MyData* pData;
    HANDLE hMapFile;
public:
    ControllerThread();
    int createMemory();
protected:
    void run() override;
};

#endif // CONTROLLERTHREAD_H
