#include "hipcenterapipoints.h"

hipcenterapipoints::hipcenterapipoints(QObject *parent) : QObject(parent)
{
    hipCenterPointsApiManager = new QNetworkAccessManager(this);
    connect(hipCenterPointsApiManager, &QNetworkAccessManager::finished, this, &hipcenterapipoints::onFinishedPoints);
}


void hipcenterapipoints::getHipPointsUrl(const QString &url)
{
    QNetworkRequest hipRequest;
    hipRequest.setUrl(QUrl(url));
    hipCenterPointsApiManager->get(hipRequest);
}


void hipcenterapipoints::onFinishedPoints(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "hipcenterapipoints::Error:" << reply->errorString();
        return;
    }

    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    QJsonObject jsonObj = jsonDoc.object();
//    qDebug() << "hipcenterapipoints::Parsed JSON:" << jsonObj;

    // Extract Error and Marker Position
    double error = jsonObj.value("Error").toDouble();
    QJsonArray markerPositionArray = jsonObj.value("Marker Position").toArray();
    QString status = jsonObj.value("Status").toString();
    QJsonArray hipcenterArray = jsonObj.value("Hip Center").toArray();

    QList<double> markerPosition;
    for (const auto &value : markerPositionArray) {
        markerPosition.append(value.toDouble());
    }

    qDebug()<<" status message ::"<<status;
    QList<double> hipcenter;
    if (status=="Done"){
        for (const auto &value : hipcenterArray) {
            hipcenter.append(value.toDouble());
            emit signalHipCenterDone(hipcenter);
        }
    }


    // Emit signals
    emit signalErrorHip(error);
    emit signalMarkerPositionHip(markerPosition);


    reply->deleteLater();
}
