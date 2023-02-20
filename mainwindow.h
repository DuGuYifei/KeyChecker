#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "confirmsendpushbutton.h"
#include "messagelabel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    ConfirmSendPushButton* btnConfirm;
    QLineEdit* keyEdit;
    MessageLabel* msgLabel;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
