#include "jsondatacameraforsurface.h"

jsondatacameraforsurface::jsondatacameraforsurface(QObject *parent) : QObject(parent)
{
    networkmanagerOtherendpoint = new QNetworkAccessManager(this);
    connect(networkmanagerOtherendpoint, &QNetworkAccessManager::finished, this, &jsondatacameraforsurface::onResultOther);

}
void jsondatacameraforsurface::sendRequestOther(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    networkmanagerOtherendpoint->get(request);
}

void jsondatacameraforsurface::onResultOther(QNetworkReply *reply)
{
    QString endpoint = reply->url().path();
//     qDebug() << "endpoint:" << endpoint;

        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
//            qDebug() << "Response:" << response;

            // Parse JSON if necessary
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
            QJsonObject jsonObject = jsonResponse.object();

            // Call appropriate getter and setter based on the endpoint
            if (endpoint == "/CheckPoint") {
                handleCheckPoint(jsonObject);
            } else if (endpoint == "/GetConnectionStatus") {
                handleConnectionStatus(jsonObject);
            }else if (endpoint == "/GetCameraData") {
                handleCameraPoint(jsonObject);
            } else if (endpoint == "/Lasers") {
                handleLasers(jsonObject);
            } else {
                qDebug() << "Unknown endpoint:" << endpoint;
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        reply->deleteLater();
}

void jsondatacameraforsurface::handleConnectionStatus(const QJsonObject &jsonObject)
{
    qDebug()<<"handleConnectionStatus";
}

void jsondatacameraforsurface::handleLasers(const QJsonObject &jsonObject)
{
       qDebug()<<"handleLasers";
}

void jsondatacameraforsurface::handleCheckPoint(const QJsonObject &jsonObject)
{
    qDebug()<<"handleCheckPoint";
}

void jsondatacameraforsurface::handleCameraPoint(const QJsonObject &jsonObject)
{
//    qDebug()<<"jsondatafetchOtherDetails handleCameraData";

       objsurfaceRegistrationData.fromJson(jsonObject);

       // Optionally, print or process the data
//       cameraData.printData();
}
