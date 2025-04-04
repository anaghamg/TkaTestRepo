#ifndef JSONDATAFETCHWORKER_H
#define JSONDATAFETCHWORKER_H

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
#include <QNetworkRequest>
#include <QThread>
#include <comdef.h>
#include <QTimer>
#include <Eigen/Dense>
class jsonDataFetchWorker : public QObject
{
    Q_OBJECT
public:
    explicit jsonDataFetchWorker(QObject *parent = nullptr);
QNetworkAccessManager *manager;
~jsonDataFetchWorker();
 cameraData *objcameraData;

signals:
    void resultReady();
    void coordFromRefSpace(Eigen::Vector4d);
public slots:
    void doWork();
    void onResultCamera(QNetworkReply *reply);
    void handleCameraData(const QJsonObject &jsonObject);
    void process(QNetworkRequest requestforcamdata);
//    void coordinatesFromRefSpaceSlot(Eigen::Vector4d coord);




};

#endif // JSONDATAFETCHWORKER_H
