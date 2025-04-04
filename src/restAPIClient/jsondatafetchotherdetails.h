#ifndef JSONDATAFETCHOTHERDETAILS_H
#define JSONDATAFETCHOTHERDETAILS_H

#include <QObject>
#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include "src/DataSetJSON/registerdatacollected.h"
class jsondatafetchOtherDetails : public QObject
{
    Q_OBJECT
public:
    explicit jsondatafetchOtherDetails(QObject *parent = nullptr);

    registerDataCollected regdata;
    QString m_qstrAnatomy;

public slots:
    void sendRequestOther(const QString &url, QString Anatomy);
    void onResultOther(QNetworkReply *reply);
    void handleConnectionStatus(const QJsonObject &jsonObject);
    void handleLasers(const QJsonObject &jsonObject);
    void handleCheckPoint(const QJsonObject &jsonObject);
    void handleCameraPoint(const QJsonObject &jsonObject);
signals:
private:
    QNetworkAccessManager *networkmanagerOtherendpoint;
};

#endif // JSONDATAFETCHOTHERDETAILS_H
