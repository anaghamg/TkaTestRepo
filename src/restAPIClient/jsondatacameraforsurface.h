#ifndef JSONDATACAMERAFORSURFACE_H
#define JSONDATACAMERAFORSURFACE_H

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
#include "src/DataSetJSON/surfaceregistrationdata.h"

class jsondatacameraforsurface : public QObject
{
    Q_OBJECT
public:
    explicit jsondatacameraforsurface(QObject *parent = nullptr);
    surfaceRegistrationData objsurfaceRegistrationData;

public slots:
    void sendRequestOther(const QString &url);
    void onResultOther(QNetworkReply *reply);
    void handleConnectionStatus(const QJsonObject &jsonObject);
    void handleLasers(const QJsonObject &jsonObject);
    void handleCheckPoint(const QJsonObject &jsonObject);
    void handleCameraPoint(const QJsonObject &jsonObject);
private:
    QNetworkAccessManager *networkmanagerOtherendpoint;

signals:

};

#endif // JSONDATACAMERAFORSURFACE_H
