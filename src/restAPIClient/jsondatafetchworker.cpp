#include "jsondatafetchworker.h"

jsonDataFetchWorker::jsonDataFetchWorker(QObject *parent) : QObject(parent)
{
    objcameraData = new cameraData;
    qDebug()<<"jsonDataFetchWorker";
    // Initialize COM
        HRESULT result = CoInitialize(NULL);
        if (FAILED(result)) {
            qDebug() << "Failed to initialize COM library";
            return;
        }
    manager = new QNetworkAccessManager(this);
         connect(manager, &QNetworkAccessManager::finished, this, &jsonDataFetchWorker::onResultCamera);
}
jsonDataFetchWorker::~jsonDataFetchWorker()
{
    // Uninitialize COM when done
    CoUninitialize();
}

void jsonDataFetchWorker::doWork()
{
    qDebug()<<"doWork";
//    const QString &url=
    QNetworkRequest request;
    request.setUrl(QUrl("http://172.16.101.123:8081/GetCameraData"));
    process(request);
}

void jsonDataFetchWorker::onResultCamera(QNetworkReply *reply)
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
            } else {
                qDebug() << "Unknown endpoint:" << endpoint;
            }
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        reply->deleteLater();
}

void jsonDataFetchWorker::handleCameraData(const QJsonObject &jsonObject)
{
//    qDebug()<<"handleCameraData";
//    cameraData cameraData;

       objcameraData->fromJson(jsonObject);

    // Optionally, print or process the data
    //       cameraData.printData();
}

void jsonDataFetchWorker::process(QNetworkRequest requestforcamdata)
{
    qDebug() << "Starting request loop";
       QTimer *timer = new QTimer(this);
       connect(timer, &QTimer::timeout, this, [=](){
           manager->get(requestforcamdata);
       });
       timer->start(100); // 1000 ms = 1 second intervals
}
