#ifndef CONNECTIONSTATUS_H
#define CONNECTIONSTATUS_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QDebug>
class connectionStatus
{
public:
    connectionStatus();
    // Getters
        QString getConnectionStatus() const;
        QString getInitialisationStatus() const;

        // Setters
        void setConnectionStatus(const QString &status);
        void setInitialisationStatus(const QString &status);

        // Method to parse JSON response
        void fromJson(const QJsonObject &json);
        // Method to print all information
           void printInfo() const;

    private:
        QString connectionStat;
        QString initialisationStatus;
};

#endif // CONNECTIONSTATUS_H
