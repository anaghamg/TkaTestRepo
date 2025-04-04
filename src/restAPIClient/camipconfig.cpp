#include "camipconfig.h"

camIPConfig::camIPConfig(QObject *parent) : QObject(parent)
{

}
QString camIPConfig::getIpAddressFromIni()
{
    QString filepath = QDir::currentPath()+"/Config_TKA/config_restAPIIP.ini";

        // Initialize QSettings with the .ini file path
        QSettings settings(filepath, QSettings::IniFormat);

        // Retrieve the IP address from the .ini file
        QString ipAddress = settings.value("Network/IP", "").toString();

        return ipAddress;
    }
