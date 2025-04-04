/*
 * File Name : KinematicsClass.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header file of Class for getting the information from Kinematics module
 * Developer :Divya N S
 * Revision History : 21-8-2024
*/
#ifndef KINEMATICSCLASS_H
#define KINEMATICSCLASS_H

#include <QObject>
#include <QWidget>
#include <QDebug>
#include "src/Plan/Viewer/Interactors/savelandmark.h"

class KinematicsClass : public QWidget
{
    Q_OBJECT
public:
    explicit KinematicsClass(QWidget *parent = nullptr);

    //Variables:
    double m_FemoralMechAxisP1[3] ;
    double m_FemoralMechAxisP2[3]; //57

    double  m_FemoralTEA_P1[3]  ;//58
    double  m_FemoralTEA_P2[3] ;//58

    double  m_FemoralPCA_P1[3] ;//58
    double  m_FemoralPCA_P2[3];//58

    double  m_FemoralComponentAxis_P1[3]  ;//58
    double  m_FemoralComponentAxis_P2[3] ;//58

    double m_TibialMechanicalAxis_P1[3]  ;
    double m_TibialMechanicalAxis_P2[3] ;

    double m_TPL_P1[3] ;
    double m_TPL_P2[3];

    double m_FemoralLateralPosteriorCondylePoint[3] ;
    double m_FemoralMedialPosteriorCondylePoint[3] ;

    double m_femoralLateralDistalCondylePoint[3] ;//= {176.717, 171.799, 200} ;
    double m_femoralMedialDistalCondylePoint[3]  ;//={130.352, 171.817, 200};

    double m_TibialLateralPlateauPoint[3];// = {138.942, 180.421, 0};
    double m_TibialMedialPlateauPoint[3] ;//= {171.15, 183.112, 0};



    QString Femur_valgusVarusAngle = "";
    QString Femur_internalExternalRotationAngle ="";
    QString Femur_flexionExtensionAngle = "";
    QString Femur_lateralDistalResectionDepth = "";
    QString Femur_medialDistalResectionDepth = "";
    QString Femur_lateralPosteriorResectionDepth = "";
    QString Femur_medialPosteriorResectionDepth = "";

    QString Tibia_valgusVarusAngle = "";
    QString Tibia_internalExternalRotationAngle ="";
    QString Tibia_Posteriorslope = "";
    QString Tibia_lateralProximalResectionDepth = "";
    QString Tibia_medialProximalResectionDepth = "";





public slots:

    void GetPointsFRomAnnotationmodule();
    void ReadJsonFromKinematicsModule(QString ,QString);


signals:

};

#endif // KINEMATICSCLASS_H

//-----------------------old hardcoded values---------------------------------
//    double m_FemoralLateralPosteriorCondylePoint[3] ;//52
//    double m_FemoralMedialPosteriorCondylePoint[3] ;//57

//    double m_femoralLateralDistalCondylePoint[3] ;//56.7029
//    double m_femoralMedialDistalCondylePoint[3] ;//56.9043

//    double m_TibialLateralPlateauPoint[3] ;
//    double m_TibialMedialPlateauPoint[3] ;


//    double m_FemoralMechAxisP1[3] = { 75.2834, 155.0, -10.33244};
//    double m_FemoralMechAxisP2[3] = { 75.4386, 155.0, 62}; //57

//    double  m_FemoralTEA_P1[3] = {76.9336, 100.508,  62} ;//58
//    double  m_FemoralTEA_P2[3] = {123.9336, 147.858,  62};//58

//    double  m_FemoralPCA_P1[3] = {80.7422, 92.898, 62};//58
//    double  m_FemoralPCA_P2[3] = {145.596, 123.898, 62};//58

//    double  m_FemoralComponentAxis_P1[3] = {70.007, 103.984, 62} ;//58
//    double  m_FemoralComponentAxis_P2[3] = {120.007, 152.777, 62};//58

//    double m_TibialMechanicalAxis_P1[3] = {73.7578, 140.215, 65.7644};
//    double m_TibialMechanicalAxis_P2[3] = {73.7578, 140.215, -4.65979};

//    double m_TPL_P1[3] ={52.1094, 106.006, 0};
//    double m_TPL_P2[3] ={105.633, 160.27, 0};

//    double m_FemoralLateralPosteriorCondylePoint[3] ={90.8008, 100.182, 62};//52
//    double m_FemoralMedialPosteriorCondylePoint[3] ={130.273, 120.275, 62};//57

//    double m_femoralLateralDistalCondylePoint[3] = {82.6133, 113.238, 61.7029};//56.7029
//    double m_femoralMedialDistalCondylePoint[3] = {110.754, 140.0, 61.9043};//56.9043

//    double m_TibialLateralPlateauPoint[3] = {82.207, 106.465, 0.19409};
//    double m_TibialMedialPlateauPoint[3] = {114.124, 136.541, 0.44063};


//--------------------------------------------------------------------
