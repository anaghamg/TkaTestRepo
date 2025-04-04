/*
 * File Name : ImplantLoad.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header file of Class for loading the implant model
 * Developer :Divya N S
 * Revision History : 28-8-2024
*/
#ifndef IMPLANTLOAD_H
#define IMPLANTLOAD_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include <QDir>
#include "HeaderIncludes.h"


class ImplantLoad : public QWidget
{
    Q_OBJECT
public:
    explicit ImplantLoad(QWidget *parent = nullptr);
    std::vector<vtkSmartPointer<vtkActor>>m_ImplantActors;

    vtkSmartPointer<vtkProperty> Actproperty =vtkSmartPointer<vtkProperty>::New();

    vtkSmartPointer<vtkSTLReader> stlReader_Femur = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkSTLReader> stlReader_Tibia = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkSTLReader> stlReader_TibiaSpacer = vtkSmartPointer<vtkSTLReader>::New();

    //Femur
    vtkSmartPointer<vtkPolyDataMapper> mapper_fem_Anter = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper_fem_Distal = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper_fem_Lateral = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkActor> actor_fem_Anter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actor_fem_Distal = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actor_fem_Lateral = vtkSmartPointer<vtkActor>::New();

    //Tibia
    vtkSmartPointer<vtkPolyDataMapper> mapper_tib_Anter = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper_tib_Distal = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper_tib_Lateral = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkActor> actor_tib_Anter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actor_tib_Distal = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actor_tib_Lateral = vtkSmartPointer<vtkActor>::New();
    //tibia spacerimplant
    vtkSmartPointer<vtkPolyDataMapper> mapper_tibSpacer_Anter = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper_tibSpacer_Distal = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper_tibSpacer_Lateral = vtkSmartPointer<vtkPolyDataMapper>::New();

    vtkSmartPointer<vtkActor> actor_tibSpacer_Anter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actor_tibSpacer_Distal = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> actor_tibSpacer_Lateral = vtkSmartPointer<vtkActor>::New();

//--for patirnt data-------
   // QString m_direc_femoralimplant = QDir::currentPath()+"/Femur_Tibia_dicom/implant/femoral_component.stl";
   // QString m_direc_tibialimplant = QDir::currentPath()+"/Femur_Tibia_dicom/implant/tibial_component v1.stl";
    QString m_direc_spacerimplant = QDir::currentPath()+"/Femur_Tibia_dicom/implant/spacer.stl";
//for phantom data
 QString m_direc_femoralimplant = QDir::currentPath()+"/Femur_Tibia_dicom/implant/Femur_comp_phantom.stl";
 QString m_direc_tibialimplant = QDir::currentPath()+"/Femur_Tibia_dicom/implant/tibia_comp_phantom.stl";


    QString m_FemImplant_1_Path = QDir::currentPath()+"/Femur_Tibia_dicom/implant/femoral_component.stl";
    QString m_TibImplant_1_Path = QDir::currentPath()+"/Femur_Tibia_dicom/implant/tibial_component v1.stl";
    QString m_SpcImplant_1_Path = QDir::currentPath()+"/Femur_Tibia_dicom/implant/spacer.stl";

    QString m_FemImplant_2_Path = QDir::currentPath()+"/Femur_Tibia_dicom/implant/femoral_component.stl";
    QString m_TibImplant_2_Path = QDir::currentPath()+"/Femur_Tibia_dicom/implant/tibial_component v1.stl";
    QString m_SpcImplant_2_Path = QDir::currentPath()+"/Femur_Tibia_dicom/implant/spacer.stl";

    int clickednumber_femur = 0;
    int clickednumber_tibia = 0;
    int clickednumber_poly = 0;
    bool onetime_load =  false;

signals:
public slots:
    std::vector<vtkSmartPointer<vtkActor>> LoadedImplant(double*,double*);
    void AssiginingSTLReaders_Fem(QString);
    void AssiginingSTLReaders_Tib(QString);
    void AssiginingSTLReaders_TibSpc(QString);

    vtkSmartPointer<vtkSTLReader> LoadDifferentSizedImplant_Femur(QString);
    vtkSmartPointer<vtkSTLReader> LoadDifferentSizedImplant_Tibia(QString);
    vtkSmartPointer<vtkSTLReader> LoadDifferentSizedImplant_TibSpacer(QString);




};

#endif // IMPLANTLOAD_H
