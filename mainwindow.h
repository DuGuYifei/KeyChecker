#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QProcess>
#include "confirmsendpushbutton.h"
#include "messagelabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    ConfirmSendPushButton* btnConfirm;
    QLineEdit* keyEdit;
    MessageLabel* msgLabel;
    QProcess *wrappeeProcess;
public:
    MainWindow(QWidget *parent = nullptr);
    void startWrappee();
    ~MainWindow();
};
#endif // MAINWINDOW_H
