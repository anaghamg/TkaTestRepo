#ifndef RESTAPICLIENT_H
#define RESTAPICLIENT_H

#include <QObject>
#include <QWidget>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "src/DataSetJSON/cameradata.h"
class RestAPIClient : public QObject
{
    Q_OBJECT
public:
    explicit RestAPIClient(QObject *parent = nullptr);

signals:

public slots:
    void sendRequest(const QString &url);
    void onResult(QNetworkReply *reply);
    void handleCameraData(const QJsonObject &jsonObject);
    void handleConnectionStatus(const QJsonObject &jsonObject);
    void handleLasers(const QJsonObject &jsonObject);
private:
    QNetworkAccessManager *manager;
};

#endif // RESTAPICLIENT_H
