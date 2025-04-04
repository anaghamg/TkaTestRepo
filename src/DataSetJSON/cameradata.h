#ifndef CAMERADATA_H
#define CAMERADATA_H

#include <QObject>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QDebug>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "src/Registration/regtransformation.h"
#include <QMatrix4x4>
#include "src/Registration/fiducialstruct.h"

class cameraData: public QObject
{
    Q_OBJECT
public:
    cameraData();
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

    QMatrix4x4 transformMatF;
    QMatrix4x4 transformMatT;

    QVector4D transformedPoint;

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


    // Marker Struct to represent each marker in the RegisteredMarkersList
    struct Marker {
        QString MarkerName;
        QString ErrorStatus;
        double ErrorValue;
        TopBottom Top;
        TopBottom Bottom;
        std::vector<Fiducial> FiducialList;
        std::vector<Point> MarkerBallsList;
    };

    // RegisteredMarkersList Struct to represent the whole list of markers
    struct RegisteredMarkersList {
        std::vector<Marker> markers;
    };
    Eigen::Matrix4d cam2ref_tf_fem ;
    Eigen::Matrix4d cam2ref_tf_tib ;
    QString m_qstrAnatomy;

    QList<QMap<QString, float>> registeredMarkerData; // List of dictionaries
    QList<QMap<QString, QVariant>> fiducialList;      // List of dictionaries for fiducial data
    //    QList<float> fiducialDataList;
    QList<QList<double> > fiducialDataList;
    // Function to parse JSON and populate member variables
    void fromJson(const QJsonObject &jsonObj);

    // Function to print or debug the data (optional)
    void printData() const;// List of floats
    int getInitialisationStatus() const;
    void setInitialisationStatus(int value);
    float getTotalTimeElapsed() const;
    void setTotalTimeElapsed(float value);
    float getTimeStamp() const;
    void setTimeStamp(float value);
    float getCameraTilt() const;
    void setCameraTilt(float value);
    bool getIsShockObtained() const;
    void setIsShockObtained(bool value);
    int getConnectionStatusFromcam() const;
    void setConnectionStatusFromcam(int value);
    bool getIsCameraDataObtained() const;
    void setIsCameraDataObtained(bool value);
    QString getVersion() const;
    void setVersion(const QString &value);
    QString getQueryType() const;
    void setQueryType(const QString &value);
    bool markerOnceTaken=false;
    regTransformation objregTransformation;
    QMatrix4x4 readTransMatFromFile(const QString &filePath);
    Eigen::Matrix4d qMatrix4x4ToEigen(const QMatrix4x4& qMatrix);

signals:
    void trackCoordinateRefSpace(Eigen::Vector4d);
    void signalTrackToolF(vtkSmartPointer<vtkTransform> t,Eigen::Matrix4d m);
    void signalTrackToolT(vtkSmartPointer<vtkTransform> t,Eigen::Matrix4d m);
    void refmarkerCoordMat(Eigen::Matrix4d);
    void signalFiducialsFemurRef(const QList<QVariantMap>& fiducialsData);
    void signalFiducialsTibiaRef(const QList<QVariantMap>& fiducialsData);
    void signalFiducialsTool(const QList<QVariantMap>& fiducialsData);
};

#endif // CAMERADATA_H
