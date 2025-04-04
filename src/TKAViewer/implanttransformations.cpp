/*
 * File Name : ImplantTransformations.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : To do transformations of the implant like rotate,Pan, size adjustment
 * Developer :Divya N S
 * Revision History : 06-09-2024
*/
#include "implanttransformations.h"
#include <QDebug>

ImplantTransformations::ImplantTransformations(QWidget *parent)
    : QWidget{parent}
{

}

//******************Femoral Component************************************
//Anterior Femur rotation and translations
void ImplantTransformations::SlotOfFemurimplantTransformationsFA(QString m_Btnname,vtkActor* fem_ant_Imp_Actor)
{
    //qDebug()<<"btnme"<<m_Btnname;

    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_FAleftdown")
    {
        Transform_Fem->RemoveAllObservers();
        //Transform_Fem->RotateZ(-0.5);//Setup the transform for   rotation(0.5°)
        Transform_Fem->RotateY(0.5);
        Transform_Fem->Update();
    }
    else if(m_Btnname == "pushButton_FArightdown")
    {
        Transform_Fem->RemoveAllObservers();
        //Transform_Fem->RotateZ(0.5);//Setup the transform for valgus rotation(0.5°)
        Transform_Fem->RotateY(-0.5);
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FAup")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,0.0,-0.5);//Setup the transform for proximal panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FAright")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.5,0.0,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FAdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,0.0,0.5);//Setup the transform for distal panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FAleft")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(-0.5,0.0,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_Fem->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadFA == false)
    {
        TransformFilter_Fem->RemoveAllObservers();
        TransformFilter_Fem->SetInputData(fem_ant_Imp_Actor->GetMapper()->GetInput());
        TransformFilter_Fem->SetTransform( Transform_Fem);
        TransformFilter_Fem->Update();

        //Update the mapper
        fem_ant_Imp_Actor->GetMapper()->SetInputConnection( TransformFilter_Fem->GetOutputPort());
        fem_ant_Imp_Actor->GetMapper()->Update();
        firstLoadFA = true;
    }

    //Update the Actor
    fem_ant_Imp_Actor->Modified();

}

//Distal Femur rotation and translations
void ImplantTransformations::SlotOfFemurimplantTransformationsFD(QString m_Btnname,vtkActor* fem_dist_Imp_Actor)
{
    //qDebug()<<"btnme"<<m_Btnname;

    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_FDleftdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->RotateZ(0.5);//Setup the transform for  internal rotation(0.5°)
        Transform_Fem->Update();
    }
    else if(m_Btnname == "pushButton_FDrightdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->RotateZ(-0.5);//Setup the transform for external rotation (0.5°)
        Transform_Fem->Update();

    }
    else if(m_Btnname =="pushButton_FDup")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,0.5,0.0);//Setup the transform for proximal panning (0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FDright")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.5,0.0,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FDdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,-0.5,0.0);//Setup the transform for distal panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FDleft")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(-0.5,0.0,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_Fem->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadFD == false)
    {
        TransformFilter_Fem->RemoveAllObservers();
        TransformFilter_Fem->SetInputData(fem_dist_Imp_Actor->GetMapper()->GetInput());
        TransformFilter_Fem->SetTransform( Transform_Fem);
        TransformFilter_Fem->Update();

        //Update the mapper
        fem_dist_Imp_Actor->GetMapper()->SetInputConnection( TransformFilter_Fem->GetOutputPort());
        fem_dist_Imp_Actor->GetMapper()->Update();
        firstLoadFD = true;
    }

    //Update the Actor
    fem_dist_Imp_Actor->Modified();
}

//Lateral Femoral Rotations and tranlslations
void ImplantTransformations::SlotOfFemurimplantTransformationsFL(QString m_Btnname,vtkActor* fem_late_Imp_Actor)
{
    //qDebug()<<"btnme"<<m_Btnname;

    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_FLleftdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->RotateX(0.5);//Setup the transform for  flexion rotation(0.5°)
        Transform_Fem->Update();
    }
    else if(m_Btnname == "pushButton_FLrightdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->RotateX(-0.5);//Setup the transform for extension rotation (0.5°)
        Transform_Fem->Update();

    }
    else if(m_Btnname =="pushButton_FLup")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,0.0,-0.5);//Setup the transform for proximal panning (0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FLright")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,-0.5,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FLdown")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,0.0,0.5);//Setup the transform for distal panning(0.5mm)
        Transform_Fem->Update();
    }
    else if(m_Btnname =="pushButton_FLleft")
    {
        Transform_Fem->RemoveAllObservers();
        Transform_Fem->Translate(0.0,0.5,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_Fem->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadFL == false)
    {
        TransformFilter_Fem->RemoveAllObservers();
        TransformFilter_Fem->SetInputData(fem_late_Imp_Actor->GetMapper()->GetInput());
        TransformFilter_Fem->SetTransform( Transform_Fem);
        TransformFilter_Fem->Update();

        //Update the mapper
        fem_late_Imp_Actor->GetMapper()->SetInputConnection( TransformFilter_Fem->GetOutputPort());
        fem_late_Imp_Actor->GetMapper()->Update();
        firstLoadFL = true;
    }

    //Update the Actor
    fem_late_Imp_Actor->Modified();
}

//********************Tibial component*************************
//Anterior Tibial Rotations and tranlslations
void ImplantTransformations::SlotOfFemurimplantTransformationsTA(QString m_Btnname,vtkActor* tib_ant_Imp_Actor)
{
    // qDebug()<<"btnme="<<m_Btnname;
    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_TAleftdown")
    {
        Transform_Tib->RemoveAllObservers();
        //Transform_Tib->RotateZ(0.5);//Setup the transform for  Varus rotation(0.5°)
        Transform_Tib->RotateY(-0.5);//Setup the transform for  Varus rotation(0.5°)
        Transform_Tib->Update();
    }
    else if(m_Btnname == "pushButton_TArightdown")
    {
        Transform_Tib->RemoveAllObservers();
        //Transform_Tib->RotateZ(-0.5);//Setup the transform for Valgus rotation (0.5°)
        Transform_Tib->RotateY(0.5);//Setup the transform for Valgus rotation (0.5°)
        Transform_Tib->Update();

    }
    else if(m_Btnname =="pushButton_TAup")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,0.0,-0.5);//Setup the transform for proximal panning (0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TAright")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.5,0.0,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TAdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,0.0,0.5);//Setup the transform for distal panning(0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TAleft")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(-0.5,0.0,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_Tib->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadTA == false)
    {
        TransformFilter_Tib->RemoveAllObservers();
        TransformFilter_Tib->SetInputData(tib_ant_Imp_Actor->GetMapper()->GetInput());
        TransformFilter_Tib->SetTransform( Transform_Tib);
        TransformFilter_Tib->Update();

        //Update the mapper
        tib_ant_Imp_Actor->GetMapper()->SetInputConnection(TransformFilter_Tib->GetOutputPort());
        tib_ant_Imp_Actor->GetMapper()->Update();

        firstLoadTA = true;
    }

    //Update the Actor
    tib_ant_Imp_Actor->Modified();
}

//DISTAL Tibial Rotations and tranlslations
void ImplantTransformations::SlotOfFemurimplantTransformationsTD(QString m_Btnname,vtkActor* tib_dist_Imp_Actor)
{
    //qDebug()<<"btnme="<<m_Btnname;
    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_TDleftdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->RotateZ(0.5);//Setup the transform for  internal rotation(0.5°)
        Transform_Tib->Update();
    }
    else if(m_Btnname == "pushButton_TDrightdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->RotateZ(-0.5);//Setup the transform for external rotation (0.5°)
        Transform_Tib->Update();

    }
    else if(m_Btnname =="pushButton_TDup")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,-0.5,0.0);//Setup the transform for proximal panning (0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TDright")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.5,0.0,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TDdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,0.5,0.0);//Setup the transform for distal panning(0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TDleft")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(-0.5,0.0,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_Tib->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadTD == false)
    {
        TransformFilter_Tib->RemoveAllObservers();
        TransformFilter_Tib->SetInputData(tib_dist_Imp_Actor->GetMapper()->GetInput());
        TransformFilter_Tib->SetTransform( Transform_Tib);
        TransformFilter_Tib->Update();


        //Update the mapper
        tib_dist_Imp_Actor->GetMapper()->SetInputConnection( TransformFilter_Tib->GetOutputPort());
        tib_dist_Imp_Actor->GetMapper()->Update();

        firstLoadTD = true;
    }

    //Update the Actor
    tib_dist_Imp_Actor->Modified();
}

//Lateral Tibial Rotations and tranlslations
void ImplantTransformations::SlotOfFemurimplantTransformationsTL(QString m_Btnname,vtkActor* tib_lat_Imp_Actor)
{
    //qDebug()<<"btnme="<<m_Btnname;
    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_TLleftdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->RotateX(-0.5);//Setup the transform for  Flexion rotation(0.5°)
        Transform_Tib->Update();
    }
    else if(m_Btnname == "pushButton_TLrightdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->RotateX(0.5);//Setup the transform for extension rotation (0.5°)
        Transform_Tib->Update();

    }
    else if(m_Btnname =="pushButton_TLup")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,0.0,-0.5);//Setup the transform for proximal panning (0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TLright")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,-0.5,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TLdown")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,0.0,0.5);//Setup the transform for distal panning(0.5mm)
        Transform_Tib->Update();
    }
    else if(m_Btnname =="pushButton_TLleft")
    {
        Transform_Tib->RemoveAllObservers();
        Transform_Tib->Translate(0.0,0.5,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_Tib->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadTL == false)
    {
        TransformFilter_Tib->RemoveAllObservers();
        TransformFilter_Tib->SetInputData(tib_lat_Imp_Actor->GetMapper()->GetInput());
        TransformFilter_Tib->SetTransform( Transform_Tib);
        TransformFilter_Tib->Update();


        //Update the mapper
        tib_lat_Imp_Actor->GetMapper()->SetInputConnection( TransformFilter_Tib->GetOutputPort());
        tib_lat_Imp_Actor->GetMapper()->Update();
        firstLoadTL = true;
    }

    //Update the Actor
    tib_lat_Imp_Actor->Modified();
}
//*******************************Spacer component******************************

void ImplantTransformations::SlotOfFemurimplantTransformationsTSpacerA(QString m_Btnname,vtkActor* tib_ant_SpacerImp_Actor)
{
    // qDebug()<<"btnme="<<m_Btnname;
    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_TAleftdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        //Transform_SpacerTib->RotateZ(-0.5);//Setup the transform for  Varus rotation(0.5°)
        Transform_SpacerTib->RotateY(0.5);//Setup the transform for  Varus rotation(0.5°)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname == "pushButton_TArightdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        // Transform_SpacerTib->RotateZ(0.5);//Setup the transform for Valgus rotation (0.5°)
        Transform_SpacerTib->RotateY(-0.5);//Setup the transform for Valgus rotation (0.5°)
        Transform_SpacerTib->Update();

    }
    else if(m_Btnname =="pushButton_TAup")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,0.0,0.5);//Setup the transform for proximal panning (0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TAright")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.5,0.0,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TAdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,0.0,-0.5);//Setup the transform for distal panning(0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TAleft")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(-0.5,0.0,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_SpacerTib->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadTSA == false)
    {


        TransformFilterSpacer_Tib->RemoveAllObservers();
        TransformFilterSpacer_Tib->SetInputData(tib_ant_SpacerImp_Actor->GetMapper()->GetInput());
        TransformFilterSpacer_Tib->SetTransform( Transform_SpacerTib);
        TransformFilterSpacer_Tib->Update();

        //Update the mapper
        tib_ant_SpacerImp_Actor->GetMapper()->SetInputConnection(TransformFilterSpacer_Tib->GetOutputPort());
        tib_ant_SpacerImp_Actor->GetMapper()->Update();
        firstLoadTSA = true;
    }

    //Update the Actor
    tib_ant_SpacerImp_Actor->Modified();
}

//DISTAL Tibial Rotations and tranlslations
void ImplantTransformations::SlotOfFemurimplantTransformationsTSpacerD(QString m_Btnname,vtkActor* tib_dist_SpacerImp_Actor)
{
    //qDebug()<<"btnme="<<m_Btnname;
    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_TDleftdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->RotateZ(-0.5);//Setup the transform for  internal rotation(0.5°)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname == "pushButton_TDrightdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->RotateZ(0.5);//Setup the transform for external rotation (0.5°)
        Transform_SpacerTib->Update();

    }
    else if(m_Btnname =="pushButton_TDup")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,0.5,0.0);//Setup the transform for proximal panning (0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TDright")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.5,0.0,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TDdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,-0.5,0.0);//Setup the transform for distal panning(0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TDleft")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(-0.5,0.0,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_SpacerTib->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadTSD == false)
    {


        TransformFilterSpacer_Tib->RemoveAllObservers();
        TransformFilterSpacer_Tib->SetInputData(tib_dist_SpacerImp_Actor->GetMapper()->GetInput());
        TransformFilterSpacer_Tib->SetTransform(  Transform_SpacerTib);
        TransformFilterSpacer_Tib->Update();

        //Update the mapper

        tib_dist_SpacerImp_Actor->GetMapper()->SetInputConnection(TransformFilterSpacer_Tib->GetOutputPort());
        tib_dist_SpacerImp_Actor->GetMapper()->Update();
        firstLoadTSD = true;
    }

    //Update the Actor
    tib_dist_SpacerImp_Actor->Modified();
}

//Lateral Tibial Rotations and tranlslations
void ImplantTransformations::SlotOfFemurimplantTransformationsTSpacerL(QString m_Btnname,vtkActor* tib_lat_SpacerImp_Actor)
{
    //qDebug()<<"btnme="<<m_Btnname;
    // Check Which button is pressed and apply translation / rotation based on that
    if(m_Btnname == "pushButton_TLleftdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->RotateX(-0.5);//Setup the transform for  Flexion rotation(0.5°)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname == "pushButton_TLrightdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->RotateX(0.5);//Setup the transform for extension rotation (0.5°)
        Transform_SpacerTib->Update();

    }
    else if(m_Btnname =="pushButton_TLup")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,0.0,0.5);//Setup the transform for proximal panning (0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TLright")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,0.5,0.0);//Setup the transform for Medial panning(0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TLdown")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,0.0,-0.5);//Setup the transform for distal panning(0.5mm)
        Transform_SpacerTib->Update();
    }
    else if(m_Btnname =="pushButton_TLleft")
    {
        Transform_SpacerTib->RemoveAllObservers();
        Transform_SpacerTib->Translate(0.0,-0.5,0.0);//Setup the transform for Lateral panning(0.5mm)
        Transform_SpacerTib->Update();
    }

    // Apply the rotation/Panning to the knee implant
    if(firstLoadTSL == false)
    {

        TransformFilterSpacer_Tib->RemoveAllObservers();
        TransformFilterSpacer_Tib->SetInputData(tib_lat_SpacerImp_Actor->GetMapper()->GetInput());
        TransformFilterSpacer_Tib->SetTransform(  Transform_SpacerTib);
        TransformFilterSpacer_Tib->Update();

        //Update the mapper
        tib_lat_SpacerImp_Actor->GetMapper()->SetInputConnection(TransformFilterSpacer_Tib->GetOutputPort());
        tib_lat_SpacerImp_Actor->GetMapper()->Update();
        firstLoadTSL = true;
    }

    //Update the Actor
    tib_lat_SpacerImp_Actor->Modified();
}
//*******************************Size adjustments******************************
