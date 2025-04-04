#ifndef CHECKPOINTDATASET_H
#define CHECKPOINTDATASET_H

#include <QObject>

class checkPointDataSet : public QObject
{
    Q_OBJECT
public:
    explicit checkPointDataSet(QObject *parent = nullptr);
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

        // checkPoint struct
        struct checkPoint {
            QString MarkerName;
            QString ErrorStatus;
            double ErrorValue;
            TopBottom Top;
            TopBottom Bottom;
        } m_structFemurCheckPoint, m_structTibiaCheckPoint;

        // Getters and setters for Tibia and Femur CheckPoint structs
        checkPoint structTibiaCheckPoint() const;
        void setStructTibiaCheckPoint(const checkPoint& structTibiaCheckPoint);

        checkPoint structFemurCheckPoint() const;
        void setStructFemurCheckPoint(const checkPoint& structFemurCheckPoint);
signals:

};

#endif // CHECKPOINTDATASET_H
