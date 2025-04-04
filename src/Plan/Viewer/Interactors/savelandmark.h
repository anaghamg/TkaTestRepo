#ifndef SAVELANDMARK_H
#define SAVELANDMARK_H

#include <qobject.h>
#include <array>
#include <qdebug.h>
#include <vtkEventQtSlotConnect.h>
#include <QObject>
#include <QtWidgets>
#include <vtkXMLDataElement.h>
#include <vtkXMLUtilities.h>
#include <vtkSmartPointer.h>
#include <fstream>
#include <sstream>
#include <iostream>

struct annotationValues {
    QString bone_name;
    int anatomyid;
    QString anatomy;
    double x;
    double y;
    double z;
};

class savelandmark : public QWidget
{
    Q_OBJECT
public:
    explicit savelandmark(QWidget *parent = nullptr);

//signals:
//    void signalSavedPoints( QVector<annotationValues> vals);

public slots:
    void slotLandmarkFeatures(QString bone_name, int anatomyid, const QString &anatomy);
    void slotLandmarkPoint(std::array<double, 3> point);

private:
    QString myvtk_bone;
    int myvtk_anatomyid;
    QString myvtk_anatomy;
    std::array<double, 3> landmarkPoint;
    vtkSmartPointer<vtkXMLUtilities> xmlUtilities = vtkSmartPointer<vtkXMLUtilities>::New();
    vtkSmartPointer<vtkXMLDataElement> pointElement = vtkSmartPointer<vtkXMLDataElement>::New();
    vtkSmartPointer<vtkXMLDataElement> root;
    void writeCSV();
    void writeXML();


    //----------Divya Added------------
public:
    //QHash<QString, QVector<double>> getData() const;
    QVector<double>coordVec = {0,0,0};
    double Wcoordinates[3];
    static QHash<QString, QVector<double>> m_PlanningPoints;  // List to store the data
    QString trimmed_anatomyname = "";
    //KinematicsClass *m_objKinematicsClass = new KinematicsClass;
    //KinematicsClass & m_objKinematicsClass;
    QVector<annotationValues> valuesList;


};

#endif // SAVELANDMARK_H
