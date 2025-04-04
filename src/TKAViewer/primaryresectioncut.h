/*
 * File Name : primaryresectioncut.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header Class for performing primary cuts
 * Developer :Divya N S
 * Revision History : 8-8-2024
*/
#ifndef PRIMARYRESECTIONCUT_H
#define PRIMARYRESECTIONCUT_H

#include <QObject>
#include <QWidget>

#include <vtkImplicitBoolean.h>
#include <vtkTriangleFilter.h>
#include <vtkSTLWriter.h>
#include "HeaderIncludes.h"

class PrimaryResectionCut : public QWidget
{
    Q_OBJECT
public:

    explicit PrimaryResectionCut(QWidget *parent = nullptr);

    //Variables
    vtkSmartPointer<vtkPlane> clipplane_horizontal = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkPlane> clipplane_vertical = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkPlane> clipplane_vertical_poster = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkPlane> clipplane_chamfercut1 = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkPlane> clipplane_chamfercut2 = vtkSmartPointer<vtkPlane>::New();

    vtkSmartPointer<vtkClipPolyData> clipper_fem = vtkSmartPointer<vtkClipPolyData>::New();
    vtkSmartPointer<vtkClipPolyData> clipper_tib = vtkSmartPointer<vtkClipPolyData>::New();

    vtkSmartPointer<vtkPlaneSource> planeSource_tibia = vtkSmartPointer<vtkPlaneSource>::New();
    vtkSmartPointer<vtkPlaneSource> planeSource_FemHorizontal = vtkSmartPointer<vtkPlaneSource>::New();
    vtkSmartPointer<vtkPlaneSource> planeSource_Femvertical = vtkSmartPointer<vtkPlaneSource>::New();
    vtkSmartPointer<vtkPlaneSource> planeSource_FemverticalPosteriorcut = vtkSmartPointer<vtkPlaneSource>::New();
    vtkSmartPointer<vtkPlaneSource> planeChamfercut1 = vtkSmartPointer<vtkPlaneSource>::New();
    vtkSmartPointer<vtkPlaneSource> planeChamfercut2 = vtkSmartPointer<vtkPlaneSource>::New();

    //--testing  closed surface of cutting--------------
    vtkSmartPointer<vtkAppendPolyData> appendFilter_tib = vtkSmartPointer<vtkAppendPolyData>::New();
     vtkSmartPointer<vtkAppendPolyData> appendFilter_Final = vtkSmartPointer<vtkAppendPolyData>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_tib = vtkSmartPointer<vtkContourTriangulator>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_femposteriorvertical = vtkSmartPointer<vtkContourTriangulator>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_chamfer1 = vtkSmartPointer<vtkContourTriangulator>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_chamfer2 = vtkSmartPointer<vtkContourTriangulator>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_femcombined = vtkSmartPointer<vtkContourTriangulator>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_femhorizontal = vtkSmartPointer<vtkContourTriangulator>::New();
    vtkSmartPointer<vtkContourTriangulator> triangulator_fem = vtkSmartPointer<vtkContourTriangulator>::New();
     vtkSmartPointer<vtkContourTriangulator> triangulator_fem_1 = vtkSmartPointer<vtkContourTriangulator>::New();
     vtkSmartPointer<vtkClipPolyData> clipper_combined = vtkSmartPointer<vtkClipPolyData>::New();

      vtkSmartPointer<vtkPolyData> clipper_testing = vtkSmartPointer<vtkPolyData>::New();
//
  //  vtkSmartPointer<vtkFillHolesFilter> fillholes_tibia = vtkSmartPointer<vtkFillHolesFilter>::New();
    //vtkSmartPointer<vtkFillHolesFilter> fillholes_femur = vtkSmartPointer<vtkFillHolesFilter>::New();
    //vtkSmartPointer<vtkActor> filledEdgesActor = vtkSmartPointer<vtkActor>::New();
    //vtkSmartPointer<vtkFeatureEdges> featureEdges = vtkSmartPointer<vtkFeatureEdges>::New();

 //vtkSmartPointer<vtkPolyData> boundaryPoly =  vtkSmartPointer<vtkPolyData>::New();

    //vtkSmartPointer<vtkPlaneCollection> planecollc_Tib = vtkSmartPointer<vtkPlaneCollection>::New();
    //vtkSmartPointer<vtkClipClosedSurface> closedClipper_Tib = vtkSmartPointer<vtkClipClosedSurface>::New();

    //vtkSmartPointer<vtkPlaneCollection> planecollc_horiz_Fem= vtkSmartPointer<vtkPlaneCollection>::New();
    //vtkSmartPointer<vtkClipClosedSurface> closedClipper_horiz_Fem = vtkSmartPointer<vtkClipClosedSurface>::New();

    bool firsttimecutting_tibia = false;
    bool firsttimecutting_femur = false;

signals:
    void SignalCutdata_tibia(vtkPolyData*,bool);
    void SignalCutdata_femur(vtkPolyData*,bool);

public slots:
    void PrimaryCut_Tibia(vtkPolyData*,bool, double*,double*,double*,QString,QString);
    void PrimaryCut_Femur(vtkPolyData*,bool, double*,double*, double*, double*,double*,QString,QString,QString,QString,double*);

};

#endif // PRIMARYRESECTIONCUT_H
