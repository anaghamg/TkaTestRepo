#ifndef HIPCENTERAPI_H
#define HIPCENTERAPI_H

#include <QObject>
#include <qnetworkaccessmanager.h>
#include <qjsonarray.h>
#include <QJsonDocument>
#include <qnetworkreply.h>
#include <qjsonobject.h>
#include <qdebug.h>
#include <qnetworkrequest.h>
#include <src/Registration/hipcenterapipoints.h>



class hipcenterapi : public QObject
{
    Q_OBJECT
public:
    explicit hipcenterapi(QObject *parent = nullptr);
    hipcenterapipoints* m_objHipCenterApiPoints;

    void getHipUrl(const QString &url);

signals:

private:
    QNetworkAccessManager *hipCenterApiManager;
    void onFinished(QNetworkReply *reply);


};

#endif // HIPCENTERAPI_H
