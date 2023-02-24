#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QProcess>
#include "confirmsendpushbutton.h"
#include "messagelabel.h"
#include "controllerthread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    ConfirmSendPushButton* btnConfirm;
    QLineEdit* keyEdit;
    MessageLabel* msgLabel = nullptr;
    QProcess *wrappeeProcess;
    ControllerThread* controllerThread;
public:
    MainWindow(QWidget *parent = nullptr);
    void startWrappee();
    ~MainWindow();
};
#endif // MAINWINDOW_H
