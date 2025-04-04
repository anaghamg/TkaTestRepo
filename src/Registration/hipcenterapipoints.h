#ifndef HIPCENTERAPIPOINTS_H
#define HIPCENTERAPIPOINTS_H

#include <QObject>
#include <qnetworkaccessmanager.h>
#include <qjsonarray.h>
#include <QJsonDocument>
#include <qnetworkreply.h>
#include <qjsonobject.h>
#include <qdebug.h>
#include <qnetworkrequest.h>


class hipcenterapipoints : public QObject
{
    Q_OBJECT
public:
    explicit hipcenterapipoints(QObject *parent = nullptr);

    void getHipPointsUrl(const QString &url);


signals:
    void signalErrorHip(double error);
    void signalHipCenterDone(const QList<double> &hipcenter);
    void signalMarkerPositionHip(const QList<double> &markerPosition);


private:
    QNetworkAccessManager *hipCenterPointsApiManager;
    void onFinishedPoints(QNetworkReply *reply);

};

#endif // HIPCENTERAPIPOINTS_H


/*
#include <QObject>
#include <qnetworkaccessmanager.h>
#include <qjsonarray.h>
#include <QJsonDocument>
#include <qnetworkreply.h>
#include <qjsonobject.h>
#include <qdebug.h>
#include <qnetworkrequest.h>



class hipcenterapi : public QObject
{
    Q_OBJECT
public:
    explicit hipcenterapi(QObject *parent = nullptr);

    void getHipUrl(const QString &url);

signals:

private:
    QNetworkAccessManager *hipCenterApiManager;
    void onFinished(QNetworkReply *reply);


};

#endif // HIPCENTERAPI_H
*/
