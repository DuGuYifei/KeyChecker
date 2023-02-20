#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "confirmsendpushbutton.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    ConfirmSendPushButton* btnConfirm;
    QLineEdit* keyEdit;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
