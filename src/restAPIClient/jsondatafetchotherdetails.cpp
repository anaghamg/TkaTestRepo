#include "jsondatafetchotherdetails.h"

jsondatafetchOtherDetails::jsondatafetchOtherDetails(QObject *parent) : QObject(parent)
{
networkmanagerOtherendpoint = new QNetworkAccessManager(this);
connect(networkmanagerOtherendpoint, &QNetworkAccessManager::finished, this, &jsondatafetchOtherDetails::onResultOther);

}

void jsondatafetchOtherDetails::sendRequestOther(const QString &url,QString Anatomy)
{
//    qDebug()<<" request recieved "<<Anatomy;
    m_qstrAnatomy=Anatomy;
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    networkmanagerOtherendpoint->get(request);
}

void jsondatafetchOtherDetails::onResultOther(QNetworkReply *reply)
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

void jsondatafetchOtherDetails::handleConnectionStatus(const QJsonObject &jsonObject)
{
    qDebug()<<"handleConnectionStatus";
}

void jsondatafetchOtherDetails::handleLasers(const QJsonObject &jsonObject)
{
       qDebug()<<"handleLasers";
}

void jsondatafetchOtherDetails::handleCheckPoint(const QJsonObject &jsonObject)
{
    qDebug()<<"handleCheckPoint";
}

void jsondatafetchOtherDetails::handleCameraPoint(const QJsonObject &jsonObject)
{
//    qDebug()<<"jsondatafetchOtherDetails handleCameraData"<<m_qstrAnatomy;

       regdata.fromJson(jsonObject,m_qstrAnatomy);

       // Optionally, print or process the data
//       cameraData.printData();
}
