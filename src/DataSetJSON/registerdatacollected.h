#ifndef REGISTERDATACOLLECTED_H
#define REGISTERDATACOLLECTED_H

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
#include <QFile>
#include <QDir>
#include "src/Registration/regtransformation.h"
#include <Eigen/Dense>
#include "src/Registration/fiducialstruct.h"
#include <QMatrix4x4>

class registerDataCollected : public QObject
{
    Q_OBJECT
public:
    explicit registerDataCollected(QObject *parent = nullptr);
public:
    QString m_qstrAnatomy;
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

    Eigen::Matrix4d cam2ref_tf_femur ;
    Eigen::Matrix4d cam2ref_tf_tibia ;


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
    // Function to parse JSON and populate member variables
    void fromJson(const QJsonObject &jsonObj,QString Anatomy);
    void appendMarkerDataToFile(const QString& filename, const Marker& marker);
    void saveMatrixToFile(const Eigen::Matrix4d& matrix, QString filename);
//    void saveVectorToFile(const Eigen::Vector4d& vector, QString filename);
    void saveVectorToFile_Femur(const Eigen::Vector4d& vector);
    void saveVectorToFile_Tibia(const Eigen::Vector4d& vector);
signals:

    void signalRefSpaceCoordsFemur(Eigen::Vector4d pt);
    void signalRefSpaceCoordsTibia(Eigen::Vector4d pt);

    void signalFiducialsFemurRef(const QList<QVariantMap>& fiducialsData);
    void signalFiducialsTibiaRef(const QList<QVariantMap>& fiducialsData);
    void signalFiducialsTool(const QList<QVariantMap>& fiducialsData);

    void signalTrackToolF(Eigen::Matrix4d t);
    void signalTrackToolT(Eigen::Matrix4d t);


private:
    QMatrix4x4 readTransMatFromFile(const QString &filePath);
    Eigen::Matrix4d qMatrix4x4ToEigen(const QMatrix4x4& qMatrix);

    QMatrix4x4 transformMatF;
    QMatrix4x4 transformMatT;
    QString filename = "transformed_point_femur.txt";
    QString filePathOp = QDir::currentPath() + "/RegistrationFiles/" + filename;
    QString filenametb = "transformed_point_tibia.txt";
    QString filePathtb = QDir::currentPath() + "/RegistrationFiles/" + filenametb;

};

#endif // REGISTERDATACOLLECTED_H
