#include "controllerthread.h"
#include <Windows.h>
// #include <QDebug>

ControllerThread::ControllerThread()
{

}

int ControllerThread::createMemory()
{
    // 创建共享内存
    hMapFile = CreateFileMappingA(
                INVALID_HANDLE_VALUE,               // 使用无效的句柄
                NULL,                               // 使用默认的安全级别
                PAGE_READWRITE,                     // 允许读写操作
                0,                                  // 共享内存大小，0表示与文件大小相同
                sizeof(MyData),                     // 内存块大小
                u8"ControllerMemeory");             // 共享内存的名字

    if (hMapFile == NULL) {
        // qDebug() << "Failed to create shared memory.";
        return 1;
    }

    // 将共享内存映射到进程的地址空间
    pData = (MyData*)(MapViewOfFile(
                hMapFile,                           // 共享内存的句柄
                FILE_MAP_ALL_ACCESS,                // 允许所有访问权限
                0,                                  // 高位偏移
                0,                                  // 低位偏移
                sizeof(MyData)));                   // 映射的字节数

    if (pData == nullptr)
    {
        // qDebug() << "Failed to map shared memory.";
        CloseHandle(hMapFile);
        return 2;
    }
    else
    {
        pData->x = -1;
        pData->y = -1;
        pData->isPressing = false;
    }
    return 0;
}


void ControllerThread::run()
{
    createMemory();
    int tx = -1, ty = -1;
    // keep reading data from memory
    while (!isInterruptionRequested())
    {
        tx = pData->x;
        ty = pData->y;
        pData->x = -1;
        pData->y = -1;
        if(tx != -1 || ty != -1)
        {
            // qDebug() << pData->x << " " << pData->y;
            tx = -1;
            ty = -1;
        }
        if((GetAsyncKeyState(VK_LBUTTON) & 0x8000) || (GetAsyncKeyState(VK_RBUTTON) & 0x8000))
            pData->isPressing = true;
        else
            pData->isPressing = false;
    }
    // code for cleaning before stop run()
    UnmapViewOfFile(pData);
    CloseHandle(hMapFile);
}
