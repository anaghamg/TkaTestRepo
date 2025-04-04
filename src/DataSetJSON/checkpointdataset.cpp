#include "checkpointdataset.h"

checkPointDataSet::checkPointDataSet(QObject *parent) : QObject(parent)
{

}
// Getter for Femur CheckPoint
checkPointDataSet::checkPoint checkPointDataSet::structFemurCheckPoint() const
{
    return m_structFemurCheckPoint;
}

// Setter for Femur CheckPoint
void checkPointDataSet::setStructFemurCheckPoint(const checkPointDataSet::checkPoint &structFemurCheckPoint)
{
    m_structFemurCheckPoint = structFemurCheckPoint;
}

// Getter for Tibia CheckPoint
checkPointDataSet::checkPoint checkPointDataSet::structTibiaCheckPoint() const
{
    return m_structTibiaCheckPoint;
}

// Setter for Tibia CheckPoint
void checkPointDataSet::setStructTibiaCheckPoint(const checkPointDataSet::checkPoint &structTibiaCheckPoint)
{
    m_structTibiaCheckPoint = structTibiaCheckPoint;
}
