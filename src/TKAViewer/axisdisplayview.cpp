/*
 * File Name : axisdisplayview.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Class for drawing  axes in Femur and Tibia
 * Developer :Divya N S
 * Revision History : 14-8-2024
*/
#include "axisdisplayview.h"


AxisDisplayView::AxisDisplayView(QWidget *parent)
    : QWidget{parent}
{
    m_objKinematicsClass = new KinematicsClass;
}

void AxisDisplayView::DisplayFemoralMechanicalAxis()
{
    //Calling the function to get points from annotation module
    m_objKinematicsClass->GetPointsFRomAnnotationmodule();

    //----Mechanical Axis----
    vtkSmartPointer<vtkLineSource> m_femurMechAxis =  vtkSmartPointer<vtkLineSource>::New();
    m_femurMechAxis->SetPoint1(m_objKinematicsClass->m_FemoralMechAxisP1/*75.2834, 155.0, -10.33244*/);
    m_femurMechAxis->SetPoint2(m_objKinematicsClass->m_FemoralMechAxisP2/*75.4386, 155.0, 57*/);
    m_femurMechAxis->Update();


    //----Trans Epicondylar axis(TEA)-----
    vtkSmartPointer<vtkLineSource> m_Fem_TEA =  vtkSmartPointer<vtkLineSource>::New();
    m_Fem_TEA->SetPoint1(m_objKinematicsClass->m_FemoralTEA_P1/*76.9336, 100.508,  58*/);
    m_Fem_TEA->SetPoint2(m_objKinematicsClass->m_FemoralTEA_P2/*123.9336, 147.858,  58*/);
    m_Fem_TEA->Update();


    //----Posterior Condyle Axis(PCA)----
    vtkSmartPointer<vtkLineSource> m_Fem_PCA =  vtkSmartPointer<vtkLineSource>::New();
    m_Fem_PCA->SetPoint1(m_objKinematicsClass->m_FemoralPCA_P1 /*80.7422, 92.898, 58*/);
    m_Fem_PCA->SetPoint2(m_objKinematicsClass->m_FemoralPCA_P2 /*145.596, 123.898, 58*/);
    m_Fem_PCA->Update();

    //----Femoral Component Axis----( line passing through the centre of the femroral component)
    //double centerpoint_Femur[3] = {92.0898, 133.418, 58};

    vtkSmartPointer<vtkLineSource> m_Fem_Compo_axis =  vtkSmartPointer<vtkLineSource>::New();
    m_Fem_Compo_axis->SetPoint1(m_objKinematicsClass->m_FemoralComponentAxis_P1 /*70.007, 103.984, 58*/);
    m_Fem_Compo_axis->SetPoint2(m_objKinematicsClass->m_FemoralComponentAxis_P2/*120.007, 152.777, 58*/);
    m_Fem_Compo_axis->Update();

    //emit signal to update the axes in the render window
    emit SignalFemoralMechanicalAxis(m_femurMechAxis->GetOutput(),m_Fem_TEA->GetOutput(),m_Fem_PCA->GetOutput(),m_Fem_Compo_axis->GetOutput());

}

void AxisDisplayView::DisplayTibialMechanicalAxis()
{
    //m_objKinematicsClass->GetPointsFRomAnnotationmodule();//calling the function to get points from annotation module

    //----Mechanical Axis----
    vtkSmartPointer<vtkLineSource> m_tibiaMechAxis =  vtkSmartPointer<vtkLineSource>::New();
    m_tibiaMechAxis->SetPoint1(m_objKinematicsClass->m_TibialMechanicalAxis_P1/*73.7578, 140.215, 65.7644*/);
    m_tibiaMechAxis->SetPoint2(m_objKinematicsClass->m_TibialMechanicalAxis_P2/*73.7578, 140.215, -4.65979*/);
    m_tibiaMechAxis->Update();


    //----Tibial Plateau plane----
    vtkSmartPointer<vtkLineSource> m_TPL =  vtkSmartPointer<vtkLineSource>::New();
    m_TPL->SetPoint1(m_objKinematicsClass->m_TPL_P1/*52.1094, 106.006, 0*/);
    m_TPL->SetPoint2(m_objKinematicsClass->m_TPL_P2/*105.633, 160.27, 0*/);
    m_TPL->Update();

    emit SignalTibialMechanicalAxis(m_tibiaMechAxis->GetOutput(),m_TPL->GetOutput());
}

std::vector<vtkSmartPointer<vtkActor>> AxisDisplayView::DisplayAnotPoints_Slot()
{
    // m_objKinematicsClass->GetPointsFRomAnnotationmodule();//calling the function to get points from annotation module

    // Create sphere sources Femoral Lateral Posterior Condyle
    vtkSmartPointer<vtkSphereSource> m_FLPC = vtkSmartPointer<vtkSphereSource>::New() ;
    m_FLPC->SetCenter(m_objKinematicsClass->m_FemoralLateralPosteriorCondylePoint/*90.8008, 100.182, 52*/);
    m_FLPC->SetRadius(3);

    // Create sphere sources Femoral Medial Posterior Condyle
    vtkSmartPointer<vtkSphereSource> m_FMPC =vtkSmartPointer<vtkSphereSource>::New();
    m_FMPC->SetCenter(m_objKinematicsClass->m_FemoralMedialPosteriorCondylePoint/*130.273, 120.275, 57*/);
    m_FMPC->SetRadius(3);

    // Create sphere sources Femoral Lateral Distal Condyle
    vtkSmartPointer<vtkSphereSource> m_FLDC =vtkSmartPointer<vtkSphereSource>::New();
    m_FLDC->SetCenter(m_objKinematicsClass->m_femoralLateralDistalCondylePoint/*82.6133, 113.238, 56.7029*/);
    m_FLDC->SetRadius(3);

    // Create sphere sources Femoral Medial Distal Condyle
    vtkSmartPointer<vtkSphereSource> m_FMDC =vtkSmartPointer<vtkSphereSource>::New();
    m_FMDC->SetCenter(m_objKinematicsClass->m_femoralMedialDistalCondylePoint/*110.754, 140.0, 56.9043*/);
    m_FMDC->SetRadius(3);

    //append all these points to a single polydata
    appendFilter_F->AddInputConnection(m_FLPC->GetOutputPort());
    appendFilter_F->AddInputConnection(m_FMPC->GetOutputPort());
    //--commenetd for now----
    appendFilter_F->AddInputConnection(m_FLDC->GetOutputPort());
    appendFilter_F->AddInputConnection(m_FMDC->GetOutputPort());
    //---------------------
    appendFilter_F->Update();

    //Anterior Femur
    F_anotpointMapper_Ant->SetInputData(appendFilter_F->GetOutput());
    F_anotpointMapper_Ant->ScalarVisibilityOff();
    F_anotpointMapper_Ant->Update();

    F_anotpointActor_Ant->SetMapper(F_anotpointMapper_Ant);
    F_anotpointActor_Ant->GetProperty()->SetColor(1,0,1);

    //Distal Femur
    F_anotpointMapper_Dis->SetInputData(appendFilter_F->GetOutput());
    F_anotpointMapper_Dis->ScalarVisibilityOff();
    F_anotpointMapper_Dis->Update();

    F_anotpointActor_Dist->SetMapper(F_anotpointMapper_Dis);
    F_anotpointActor_Dist->GetProperty()->SetColor(1,0,1);

    //Laetral Femur
    F_anotpointMapper_Lat->SetInputData(appendFilter_F->GetOutput());
    F_anotpointMapper_Lat->ScalarVisibilityOff();
    F_anotpointMapper_Lat->Update();

    F_anotpointActor_Lat->SetMapper(F_anotpointMapper_Lat);
    F_anotpointActor_Lat->GetProperty()->SetColor(1,0,1);


    // Create sphere sources Tibial Lateral Plateau
    vtkSmartPointer<vtkSphereSource> m_LP = vtkSmartPointer<vtkSphereSource>::New() ;
    m_LP->SetCenter(m_objKinematicsClass->m_TibialLateralPlateauPoint/*82.207, 106.465, 4.19409*/);
    m_LP->SetRadius(3);

    // Create sphere sources Tibial Medial Plateau
    vtkSmartPointer<vtkSphereSource> m_MP =vtkSmartPointer<vtkSphereSource>::New();
    m_MP->SetCenter(m_objKinematicsClass->m_TibialMedialPlateauPoint/*114.124, 136.541, 4.44063*/);
    m_MP->SetRadius(3);

    //---commented for now--------
    appendFilter_T->AddInputConnection(m_LP->GetOutputPort());
    appendFilter_T->AddInputConnection(m_MP->GetOutputPort());
    appendFilter_T->Update();


    //Anterior Tibia
    T_anotpointMapper_Ant->SetInputData(appendFilter_T->GetOutput());
    T_anotpointMapper_Ant->ScalarVisibilityOff();
    T_anotpointMapper_Ant->Update();

    T_anotpointActor_Ant->SetMapper(T_anotpointMapper_Ant);
    T_anotpointActor_Ant->GetProperty()->SetColor(1,0,1);

    //Distal Tibia
    T_anotpointMapper_Dis->SetInputData(appendFilter_T->GetOutput());
    T_anotpointMapper_Dis->ScalarVisibilityOff();
    T_anotpointMapper_Dis->Update();

    T_anotpointActor_Dist->SetMapper(T_anotpointMapper_Dis);
    T_anotpointActor_Dist->GetProperty()->SetColor(1,0,1);

    //Laetral Tibia
    T_anotpointMapper_Lat->SetInputData(appendFilter_T->GetOutput());
    T_anotpointMapper_Lat->ScalarVisibilityOff();
    T_anotpointMapper_Lat->Update();

    T_anotpointActor_Lat->SetMapper(T_anotpointMapper_Lat);
    T_anotpointActor_Lat->GetProperty()->SetColor(1,0,1);


    //Adding actors
    m_anotpointActors.push_back(F_anotpointActor_Ant);
    m_anotpointActors.push_back(F_anotpointActor_Dist);
    m_anotpointActors.push_back(F_anotpointActor_Lat);
    m_anotpointActors.push_back(T_anotpointActor_Ant);
    m_anotpointActors.push_back(T_anotpointActor_Dist);
    m_anotpointActors.push_back(T_anotpointActor_Lat);


    return m_anotpointActors;
}
