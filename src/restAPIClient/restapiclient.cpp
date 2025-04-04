#include "restapiclient.h"

RestAPIClient::RestAPIClient(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
         connect(manager, &QNetworkAccessManager::finished, this, &RestAPIClient::onResult);

}

void RestAPIClient::sendRequest(const QString &url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    manager->get(request);
}

void RestAPIClient::onResult(QNetworkReply *reply)
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
            if (endpoint == "/GetCameraData") {
                handleCameraData(jsonObject);
            } else if (endpoint == "/GetConnectionStatus") {
                handleConnectionStatus(jsonObject);
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

void RestAPIClient::handleCameraData(const QJsonObject &jsonObject)
{
    qDebug()<<"handleCameraData";
    cameraData cameraData;
       cameraData.fromJson(jsonObject);

       // Optionally, print or process the data
       cameraData.printData();
}

void RestAPIClient::handleConnectionStatus(const QJsonObject &jsonObject)
{
//    // Assuming you have a ConnectionStatus class with setters
//    ConnectionStatus connectionStatus;
//    connectionStatus.setStatus(jsonObject["status"].toString());
//    connectionStatus.setTimestamp(jsonObject["timestamp"].toString());
//    // Save or process connectionStatus as needed
}

void RestAPIClient::handleLasers(const QJsonObject &jsonObject)
{
//    // Assuming you have a Lasers class with setters
//    Lasers lasers;
//    lasers.setPower(jsonObject["power"].toInt());
//    lasers.setMode(jsonObject["mode"].toString());
//    // Save or process lasers as needed
}

