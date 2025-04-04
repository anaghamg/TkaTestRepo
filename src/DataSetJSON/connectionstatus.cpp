#include "connectionstatus.h"

//connectionStatus::connectionStatus()
//{

//}
// Constructor
connectionStatus::connectionStatus()
    : connectionStat("0"), initialisationStatus("0") {}

// Getters
QString connectionStatus::getConnectionStatus() const {
    return connectionStat;
}

QString connectionStatus::getInitialisationStatus() const {
    return initialisationStatus;
}

// Setters
void connectionStatus::setConnectionStatus(const QString &status) {
    connectionStat = status;
}

void connectionStatus::setInitialisationStatus(const QString &status) {
    initialisationStatus = status;
}

// Method to parse JSON response
void connectionStatus::fromJson(const QJsonObject &json) {
    if (json.contains("ConnectionStatus") && json["ConnectionStatus"].isString()) {
        connectionStat = json["ConnectionStatus"].toString();
    }

    if (json.contains("InitialisationStatus") && json["InitialisationStatus"].isString()) {
        initialisationStatus = json["InitialisationStatus"].toString();
    }
}
// Method to print all information
void connectionStatus::printInfo() const {
    qDebug() << "Connection Status:" << connectionStat;
    qDebug() << "Initialisation Status:" << initialisationStatus;
}
