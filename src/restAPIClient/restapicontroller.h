#ifndef RESTAPICONTROLLER_H
#define RESTAPICONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include "jsondatafetchworker.h"
#include "jsondatafetchotherdetails.h"

class restAPIController : public QObject
{
    Q_OBJECT
public:
    explicit restAPIController(QObject *parent = nullptr);
    void InitializedataFetchFromRestAPI();

signals:
    // Signal to request other endpoints
    void requestOtherEndpoint(const QString &endpoint);
private slots:
    // Triggered when the fetch button is clicked
    void onFetchOtherEndpoint() {
        emit requestOtherEndpoint("getSpecificEndpointData");
    }

    // Handle camera data when received
    void handleCameraData(const QJsonDocument &data) {
        qDebug() << "Camera Data Received: " << data.toJson();
//        QJsonObject jsonObject = data.object();
    }

    // Handle other endpoint data when received
    void handleOtherEndpointData(const QJsonDocument &data) {
        qDebug() << "Other Endpoint Data Received: " << data.toJson();
    }

public:
    jsonDataFetchWorker *m_objjsondatafetchworker;
    QThread *workerThread;
    jsondatafetchOtherDetails *m_objjsondatafetchOtherDetails;

};

#endif // RESTAPICONTROLLER_H
