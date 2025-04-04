/*
 * File Name : axisdisplayview.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header file of Class for drawing  axes
 * Developer :Divya N S
 * Revision History : 14-8-2024
*/
#ifndef AXISDISPLAYVIEW_H
#define AXISDISPLAYVIEW_H

#include <QObject>
#include <QWidget>

#include "HeaderIncludes.h"
#include "kinematicsclass.h"
class AxisDisplayView : public QWidget
{
    Q_OBJECT
public:
    explicit AxisDisplayView(QWidget *parent = nullptr);

    KinematicsClass * m_objKinematicsClass;

    vtkSmartPointer<vtkAppendPolyData> appendFilter_F =vtkSmartPointer<vtkAppendPolyData>::New();
    vtkSmartPointer<vtkAppendPolyData> appendFilter_T =vtkSmartPointer<vtkAppendPolyData>::New();
    std::vector<vtkSmartPointer<vtkActor>>m_anotpointActors;

    //Femur variables
    vtkSmartPointer<vtkPolyDataMapper> F_anotpointMapper_Ant =  vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> F_anotpointMapper_Dis =  vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> F_anotpointMapper_Lat =  vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> F_anotpointActor_Ant =  vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> F_anotpointActor_Dist =  vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> F_anotpointActor_Lat =  vtkSmartPointer<vtkActor>::New();

    //Tibia variables
    vtkSmartPointer<vtkPolyDataMapper> T_anotpointMapper_Ant =  vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> T_anotpointMapper_Dis =  vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> T_anotpointMapper_Lat =  vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> T_anotpointActor_Ant =  vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> T_anotpointActor_Dist =  vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> T_anotpointActor_Lat =  vtkSmartPointer<vtkActor>::New();


signals:
    void  SignalFemoralMechanicalAxis(vtkPolyData*,vtkPolyData*,vtkPolyData*,vtkPolyData*);
    void  SignalTibialMechanicalAxis(vtkPolyData*,vtkPolyData*);

public slots:
    void DisplayFemoralMechanicalAxis();
    void DisplayTibialMechanicalAxis();
    std::vector<vtkSmartPointer<vtkActor>> DisplayAnotPoints_Slot();

};

#endif // AXISDISPLAYVIEW_H
