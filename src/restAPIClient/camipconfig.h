#ifndef CAMIPCONFIG_H
#define CAMIPCONFIG_H

#include <QObject>
#include <QSettings>
#include <QString>
#include <QDebug>
#include <QDir>
class camIPConfig : public QObject
{
    Q_OBJECT
public:
    explicit camIPConfig(QObject *parent = nullptr);
QString getIpAddressFromIni() ;
signals:

};

#endif // CAMIPCONFIG_H
