/*
 * File Name : ImplantTransformations.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : header of implanttransformations class
 * Developer :Divya N S
 * Revision History : 06-09-2024
*/
#ifndef IMPLANTTRANSFORMATIONS_H
#define IMPLANTTRANSFORMATIONS_H

#include <QObject>
#include <QWidget>
#include "HeaderIncludes.h"

class ImplantTransformations : public QWidget
{
    Q_OBJECT
public:
    explicit ImplantTransformations(QWidget *parent = nullptr);

    //Variables
    vtkSmartPointer<vtkTransform> Transform_Fem = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> TransformFilter_Fem = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    vtkSmartPointer<vtkTransform> Transform_Tib = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> TransformFilter_Tib = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    vtkSmartPointer<vtkTransform> Transform_SpacerTib = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> TransformFilterSpacer_Tib = vtkSmartPointer<vtkTransformPolyDataFilter>::New();


    bool firstLoadFA = false;
    bool firstLoadFD = false;
    bool firstLoadFL = false;

    bool firstLoadTA = false;
    bool firstLoadTD = false;
    bool firstLoadTL = false;

    bool firstLoadTSA = false;
    bool firstLoadTSD = false;
    bool firstLoadTSL = false;

signals:

public slots:
    //Femur
    void SlotOfFemurimplantTransformationsFA(QString,vtkActor*);
    void SlotOfFemurimplantTransformationsFD(QString,vtkActor*);
    void SlotOfFemurimplantTransformationsFL(QString,vtkActor*);
    //Tibia
    void SlotOfFemurimplantTransformationsTA(QString,vtkActor*);
    void SlotOfFemurimplantTransformationsTD(QString,vtkActor*);
    void SlotOfFemurimplantTransformationsTL(QString,vtkActor*);

    //Tibia
    void SlotOfFemurimplantTransformationsTSpacerA(QString,vtkActor*);
    void SlotOfFemurimplantTransformationsTSpacerD(QString,vtkActor*);
    void SlotOfFemurimplantTransformationsTSpacerL(QString,vtkActor*);


};

#endif // IMPLANTTRANSFORMATIONS_H
