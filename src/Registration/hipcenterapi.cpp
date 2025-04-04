#include "hipcenterapi.h"

hipcenterapi::hipcenterapi(QObject *parent) : QObject(parent)
{
    hipCenterApiManager = new QNetworkAccessManager(this);
    m_objHipCenterApiPoints = new hipcenterapipoints;
    connect(hipCenterApiManager, &QNetworkAccessManager::finished, this, &hipcenterapi::onFinished);
}


void hipcenterapi::getHipUrl(const QString &url)
{
    QNetworkRequest hipRequest;
    hipRequest.setUrl(QUrl(url));
    hipCenterApiManager->get(hipRequest);
}

void hipcenterapi::onFinished(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "hipcenterapi::Error:" << reply->errorString();
        return;
    }

    QByteArray responseData = reply->readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    QJsonObject jsonObj = jsonDoc.object();
//    qDebug() << "Parsed JSON:" << jsonObj;

    QString connectionStatus = jsonObj.value("ConnectionStatus").toString();
    if (connectionStatus == "1") {
//        qDebug() << "Connection status is 1. Performing data collection";

        QString apiUrlPoints = "http://172.16.101.123:8081/GetCollectedPointCount";
//        QString apiUrlPoints = "http://127.0.0.1:8081/GetCollectedPointCount";
        m_objHipCenterApiPoints->getHipPointsUrl(apiUrlPoints);
    }
    else {
        qDebug()<<" collection status is not 1:: recheck connection";
    }


    reply->deleteLater();
}
