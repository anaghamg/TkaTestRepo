#ifndef SURFACEREGISTRATIONDATA_H
#define SURFACEREGISTRATIONDATA_H

#include <QObject>
#include <Eigen/Dense>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <string>
#include <vector>
#include <QFile>
#include <QDir>
#include "src/Registration/regtransformation.h"

class surfaceRegistrationData : public QObject
{
    Q_OBJECT
public:
    explicit surfaceRegistrationData(QObject *parent = nullptr);
    void fromJson(const QJsonObject &jsonObj);
     void saveVectorToFile(const Eigen::Vector4d& vector, QString filename);
public:
    QString queryType;
    QString version;
    bool isCameraDataObtained;
    int connectionStatusFromcam;
    bool isShockObtained;
    int InitialisationStatus;
    float cameraTilt;
    float timeStamp;
    float TotalTimeElapsed;
    regTransformation objregTransformation;
    Eigen::Matrix4d regPointTransformationMatrix;
    Eigen::Matrix4d markerTransformationMatrix;
    Eigen::Matrix4d cam2ref_tf ;
    bool markerOnceTaken=false;

    struct Point {
        double x;
        double y;
        double z;
    };

    // Rotation Struct to represent quaternion (x, y, z, w)
    struct Rotation {
        double x;
        double y;
        double z;
        double w;
    };

    // Angle Struct to represent angle value
    struct Angle {
        double ang;
    };

    // Top and Bottom Structs to represent the top and bottom parts of the markers
    struct TopBottom {
        Point point;
        Point point1;
        Point point2;
        Point point3;
        Point point4;
        Point point5;
        Point point6;
        Point scale;
        Rotation rotation;
        Angle angle;
    };

    // Fiducial Struct to represent each fiducial in the FiducialList
    struct Fiducial {
        Point point;
        bool Status;
        double Radius;
    };

    // Marker Struct to represent each marker in the RegisteredMarkersList
    struct Marker {
        QString MarkerName;
        QString ErrorStatus;
        double ErrorValue;
        TopBottom Top;
        TopBottom Bottom;
        std::vector<Fiducial> FiducialList;
        std::vector<Point> MarkerBallsList;
    }regp1,regp2,regp3,regp4,regp5,regp6,regp7,regp8;

    // RegisteredMarkersList Struct to represent the whole list of markers
    struct RegisteredMarkersList {
        std::vector<Marker> markers;
    };

    QList<QMap<QString, float>> registeredMarkerData; // List of dictionaries
    QList<QMap<QString, QVariant>> fiducialList;      // List of dictionaries for fiducial data
    //    QList<float> fiducialDataList;
    QList<QList<double> > fiducialDataList;
signals:

};

#endif // SURFACEREGISTRATIONDATA_H
