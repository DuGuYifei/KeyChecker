#ifndef CONFIRMSENDPUSHBUTTON_H
#define CONFIRMSENDPUSHBUTTON_H

#include <QPushButton>
#include <QLineEdit>
#include <QNetworkAccessManager>

class ConfirmSendPushButton : public QPushButton
{
private:
    QLineEdit* keyEdit;
    QNetworkAccessManager* manager;
public:
    ConfirmSendPushButton(const QString &text, QWidget *parent = nullptr, QLineEdit* keyEdit = nullptr);
    void clickEvents();
};

#endif // CONFIRMSENDPUSHBUTTON_H
