#ifndef EXECUTESAKS_H
#define EXECUTESAKS_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include <windows.h>
#include <shellapi.h>
#include <QProcess>

class executeSAKS : public QObject
{
    Q_OBJECT
public:
    explicit executeSAKS(QObject *parent = nullptr);

signals:
    void signalSaksDone();
    void signalSaksFailed();

public slots:
    void doSAKS();
    void slotdcmDir(QString st);

private:
    QString dcmPath;

};

#endif // EXECUTESAKS_H
