#include "confirmsendpushbutton.h"
#include <QEventLoop>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QNetworkInterface>
#include <QJsonDocument>
#include <QNetworkReply>

#define CHECK_IN_URL "http://localhost:8089/api/keys/key-check"

QString getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    int cnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < cnt; i++)
    {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    return strMacAddr;
}

void handleReply(QNetworkReply* reply)
{
    QMessageBox messageBox;
    qDebug() << reply->error();
    if(reply->error() == QNetworkReply::ContentNotFoundError)
    {
        messageBox.setText("Invalid key");
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
    else if(reply->error() == QNetworkReply::ContentAccessDenied)
    {
        const QByteArray reply_data = reply->readAll();
        messageBox.setText(reply_data);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
    else if(reply->error() == QNetworkReply::NoError)
    {
        const QByteArray reply_data = reply->readAll();
        messageBox.setText(reply_data);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
    else
    {
        messageBox.setText(&"Error type: " [reply->error()]);
        messageBox.setDefaultButton(QMessageBox::Ok);
        messageBox.exec();
    }
}

ConfirmSendPushButton::ConfirmSendPushButton(const QString &text, QWidget *parent, QLineEdit* keyEdit) :QPushButton(text, parent)
{
    this->keyEdit = keyEdit;
    manager = new QNetworkAccessManager(this);
    connect(this, &ConfirmSendPushButton::clicked, this, &ConfirmSendPushButton::clickEvents);
}

void ConfirmSendPushButton::clickEvents()
{
    // url
    QUrl url(CHECK_IN_URL);
    QNetworkRequest request(url);

    // requestbody
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=utf-8");
    QJsonObject requestJson;
    requestJson.insert("key_str", keyEdit->text());
    requestJson.insert("mac_hash", getHostMacAddress());
    QJsonDocument requestDoc;
    requestDoc.setObject(requestJson);
    QByteArray requestBody = requestDoc.toJson(QJsonDocument::Compact);

    // send request
    QNetworkReply* reply = manager->put(request, requestBody);
    QMessageBox messageBox(QMessageBox::Information, "", "Checking...", QMessageBox::Cancel);
    connect(reply, &QNetworkReply::finished, &messageBox, &QMessageBox::close);
    messageBox.exec();

    handleReply(reply);
}
