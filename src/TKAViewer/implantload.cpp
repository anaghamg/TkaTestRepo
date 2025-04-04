/*
 * File Name : ImplantLoad.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header file of Class for loading the implant model
 * Developer :Divya N S
 * Revision History : 28-8-2024
*/
#include "implantload.h"

ImplantLoad::ImplantLoad(QWidget *parent)
    : QWidget{parent}
{

    Actproperty->SetColor(0.50, 0.55, 0.60);  // Set to a metallic-like color (e.g., light gray)
    Actproperty->SetSpecular(1.0);         // Full specular reflection for shininess
    Actproperty->SetSpecularPower(50);     // Higher value for smaller, sharper highlights
    Actproperty->SetDiffuse(0.5);          // Reduce diffuse to increase the metallic effect
    Actproperty->SetAmbient(0.5);// Increase ambient for a more reflective appearance


}

std::vector<vtkSmartPointer<vtkActor>>ImplantLoad::LoadedImplant(double* femoralkneecenter,double* tibialkneecenter)
{
    //qDebug()<<" implnt cebter-----------" <<femoralkneecenter[0] << femoralkneecenter[1]<<femoralkneecenter[2];
    //qDebug()<<"implant pressed:"<<m_fem_implant_path;


    int femimplant_distal_width  = 8;
    int femimplant_posterior_width =13;
    int tibialimplantthick = 15;
    //---------testing------------
//    femoralkneecenter[0] = 141.559;
//    femoralkneecenter[1] = 170.652;
//    femoralkneecenter[2] = 484.25;

//    tibialkneecenter[0]= 144.293;
//    tibialkneecenter[1]= 155.023;
//    tibialkneecenter[2]= 500.023 ;
    //----------------------------
    femoralkneecenter[1] = femoralkneecenter[1];// -femimplant_posterior_width;
    femoralkneecenter[2] = femoralkneecenter[2] /*-femimplant_distal_width*/;


    tibialkneecenter[2]=tibialkneecenter[2];//+tibialimplantthick ;
            //-----------------------

    AssiginingSTLReaders_Fem(m_direc_femoralimplant);
    AssiginingSTLReaders_Tib(m_direc_tibialimplant);
    AssiginingSTLReaders_TibSpc(m_direc_spacerimplant);

    //-----------phantom data---------------------------------------
    // Create a scaling transform
    vtkSmartPointer<vtkTransform> scale_transform =  vtkSmartPointer<vtkTransform>::New();
    scale_transform->Scale(0.5, 0.5, 0.5);

    // Apply the scaling transform to the polydata
    vtkSmartPointer<vtkTransformPolyDataFilter> transform_filter =  vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transform_filter->SetInputData(stlReader_Femur->GetOutput());
    transform_filter->SetTransform(scale_transform);
    transform_filter->Update();

    // Create a rotation transform
    vtkSmartPointer<vtkTransform> rotation_transform =  vtkSmartPointer<vtkTransform>::New();
    rotation_transform->RotateY(-90);
    rotation_transform->RotateX(90);//270
    rotation_transform->RotateZ(180);

    // Apply the rotation transform to the scaled polydata
    vtkSmartPointer<vtkTransformPolyDataFilter> rotate_filter =  vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    rotate_filter->SetInputConnection(transform_filter->GetOutputPort());
    rotate_filter->SetTransform(rotation_transform);
    rotate_filter->Update();


    vtkSmartPointer<vtkTransform> translation_transform =  vtkSmartPointer<vtkTransform>::New();
    translation_transform->Translate(femoralkneecenter);
    //-------------------------------------------------


    //Anterior Femur
    //mapper_fem_Anter->SetInputData(stlReader_Femur->GetOutput());// fr patient data
    mapper_fem_Anter->SetInputData(rotate_filter->GetOutput());// fr phantom data
    mapper_fem_Anter->ScalarVisibilityOff();
    mapper_fem_Anter->Update();


    actor_fem_Anter->SetMapper(mapper_fem_Anter);
    //actor_fem_Anter->SetPosition(135, 90, 80/*for patientdata*/); //(left/right, front/back, top/bottom)
    actor_fem_Anter->SetUserTransform(translation_transform);//// f0r phantom data--------------
    actor_fem_Anter->SetProperty(Actproperty);
    // actor_fem_Anter->RotateY(-90);// for patient data
    //actor_fem_Anter->RotateX(-180);// for phantom data
    //actor_fem_Anter->RotateZ(-20);// for phantom data


    //-----------Distal Femur----------------
    //mapper_fem_Distal->SetInputData(stlReader_Femur->GetOutput());
    mapper_fem_Distal->SetInputData(rotate_filter->GetOutput());
    mapper_fem_Distal->ScalarVisibilityOff();
    mapper_fem_Distal->Update();

    actor_fem_Distal->SetMapper(mapper_fem_Distal);
    actor_fem_Distal->SetUserTransform(translation_transform);
    //actor_fem_Distal->SetPosition(  135, 90, 80 /*for patient data*/);/
    //actor_fem_Distal->SetPosition(femoralkneecenter[0], femoralkneecenter[1], femoralkneecenter[2]);//for phantom knee data
    actor_fem_Distal->SetProperty(Actproperty);
    //actor_fem_Distal->RotateY(-90);//for patient data


    //----Lateral Femur----
    //mapper_fem_Lateral->SetInputData(stlReader_Femur->GetOutput());
    mapper_fem_Lateral->SetInputData(rotate_filter->GetOutput());
    mapper_fem_Lateral->ScalarVisibilityOff();
    mapper_fem_Lateral->Update();


    actor_fem_Lateral->SetMapper(mapper_fem_Lateral);
    actor_fem_Lateral->SetUserTransform(translation_transform);
    //actor_fem_Lateral->SetPosition( 135, 90, 80  /*for patient data*/);
    //actor_fem_Lateral->SetPosition(femoralkneecenter[0], femoralkneecenter[1], femoralkneecenter[2]);//for phantom knee data

    actor_fem_Lateral->SetProperty(Actproperty);
    //actor_fem_Lateral->RotateY(-90);
    //actor_fem_Lateral->RotateX(-180);//old
    //actor_fem_Lateral->RotateZ(-35);//for old bone


    //*************************************Anterior Tibia***************************************************

    //-----------phantom data---------------------------------------
    // Create a scaling transform
    vtkSmartPointer<vtkTransform> scale_transform_tibia =  vtkSmartPointer<vtkTransform>::New();
    scale_transform_tibia->Scale(0.5, 0.5, 0.5);

    // Apply the scaling transform to the polydata
    vtkSmartPointer<vtkTransformPolyDataFilter> transform_filter_tibia =  vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    transform_filter_tibia->SetInputData(stlReader_Tibia->GetOutput());
    transform_filter_tibia->SetTransform(scale_transform_tibia);
    transform_filter_tibia->Update();

    // Create a rotation transform
    vtkSmartPointer<vtkTransform> rotation_transform_tib =  vtkSmartPointer<vtkTransform>::New();
    rotation_transform_tib->RotateY(-90);
    rotation_transform_tib->RotateX(90);//270
    //rotation_transform->RotateZ(180);

    // Apply the rotation transform to the scaled polydata
    vtkSmartPointer<vtkTransformPolyDataFilter> rotate_filter_tib =  vtkSmartPointer<vtkTransformPolyDataFilter>::New();
    rotate_filter_tib->SetInputConnection(transform_filter_tibia->GetOutputPort());
    rotate_filter_tib->SetTransform(rotation_transform_tib);
    rotate_filter_tib->Update();


    vtkSmartPointer<vtkTransform> translation_transform_tib =  vtkSmartPointer<vtkTransform>::New();
    translation_transform_tib->Translate(tibialkneecenter);
    //-------------------------------------------------



    mapper_tib_Anter->SetInputData(rotate_filter_tib->GetOutput());
    mapper_tib_Anter->ScalarVisibilityOff();
    mapper_tib_Anter->Update();
    //adding the spacer
    mapper_tibSpacer_Anter->SetInputData(stlReader_TibiaSpacer->GetOutput());
    mapper_tibSpacer_Anter->ScalarVisibilityOff();
    mapper_tibSpacer_Anter->Update();



    actor_tib_Anter->SetMapper(mapper_tib_Anter);
    //actor_tib_Anter->SetPosition( 170, 90,75/*156.575, 175.757, 3*/); //156.575, 175.757, 10
    actor_tib_Anter->SetUserTransform(translation_transform_tib);
    //actor_tib_Anter->RotateY(90);
    //actor_tib_Anter->RotateZ(180);
    //actor_tib_Anter->GetProperty()->SetColor(0.65,0.66,0.67/*0.0, 1.0, 0.0*/);
    actor_tib_Anter->SetProperty(Actproperty);
    actor_tibSpacer_Anter->SetMapper(mapper_tibSpacer_Anter);
    actor_tibSpacer_Anter->SetPosition( 170, 95,75/*156.575, 175.757, 3*/); //156.575, 175.757, 10
    actor_tibSpacer_Anter->GetProperty()->SetColor(1,1,1);
    actor_tibSpacer_Anter->RotateY(90);
    actor_tibSpacer_Anter->RotateZ(180);
    actor_tibSpacer_Anter->RotateX(180);

    //Distal Tibia
    mapper_tib_Distal->SetInputData(rotate_filter_tib->GetOutput());
    mapper_tib_Distal->ScalarVisibilityOff();
    mapper_tib_Distal->Update();

    mapper_tibSpacer_Distal->SetInputData(stlReader_TibiaSpacer->GetOutput());
    mapper_tibSpacer_Distal->ScalarVisibilityOff();
    mapper_tibSpacer_Distal->Update();


    actor_tib_Distal->SetMapper(mapper_tib_Distal);
//    actor_tib_Distal->SetPosition( 170, 90,75/*156.575, 175.757, 3*/);//170, 95,75
    actor_tib_Distal->SetUserTransform(translation_transform_tib) ;
    //actor_tib_Distal->RotateY(90);
    //actor_tib_Distal->RotateZ(180);

    //actor_tib_Distal->GetProperty()->SetColor(0.65,0.66,0.67/*0.0, 1.0, 0.0*/);
    actor_tib_Distal->SetProperty(Actproperty);
    actor_tibSpacer_Distal->SetMapper(mapper_tibSpacer_Distal);
    actor_tibSpacer_Distal->SetPosition( 170, 95,75/*156.575, 175.757, 3*/);
    actor_tibSpacer_Distal->GetProperty()->SetColor(1,1,1);
    actor_tibSpacer_Distal->RotateY(90);
    actor_tibSpacer_Distal->RotateZ(180);
    actor_tibSpacer_Distal->RotateX(180);

    //Lateral Tibia
    mapper_tib_Lateral->SetInputData(rotate_filter_tib->GetOutput());
    mapper_tib_Lateral->ScalarVisibilityOff();
    mapper_tib_Lateral->Update();

    mapper_tibSpacer_Lateral->SetInputData(stlReader_TibiaSpacer->GetOutput());
    mapper_tibSpacer_Lateral->ScalarVisibilityOff();
    mapper_tibSpacer_Lateral->Update();


    actor_tib_Lateral->SetMapper(mapper_tib_Lateral);
    //actor_tib_Lateral->SetPosition( 170, 90,75/*156.575, 175.757, 3*/);
    actor_tib_Lateral->SetUserTransform(translation_transform_tib);
    //actor_tib_Lateral->RotateY(90);
    //actor_tib_Lateral->RotateZ(180);
    //actor_tib_Lateral->GetProperty()->SetColor(0.65,0.66,0.67 /*0.0, 1.0, 0.0*/);
    actor_tib_Lateral->SetProperty(Actproperty);
    actor_tibSpacer_Lateral->SetMapper(mapper_tibSpacer_Lateral);
    actor_tibSpacer_Lateral->SetPosition( 170, 95,75/*156.575, 175.757, 3*/);//170, 95,75
    actor_tibSpacer_Lateral->GetProperty()->SetColor(1,1,1);
    actor_tibSpacer_Lateral->RotateY(90);
    actor_tibSpacer_Lateral->RotateZ(180);
    actor_tibSpacer_Lateral->RotateX(180);


    //Adding Actors to the vector
    m_ImplantActors.push_back(actor_fem_Anter);
    m_ImplantActors.push_back(actor_fem_Distal);
    m_ImplantActors.push_back(actor_fem_Lateral);

    m_ImplantActors.push_back(actor_tib_Anter);
    m_ImplantActors.push_back(actor_tib_Distal);
    m_ImplantActors.push_back(actor_tib_Lateral);

    m_ImplantActors.push_back(actor_tibSpacer_Anter);
    m_ImplantActors.push_back(actor_tibSpacer_Distal);
    m_ImplantActors.push_back(actor_tibSpacer_Lateral);


    return m_ImplantActors;
}
//Function to load the stl implants
void ImplantLoad::AssiginingSTLReaders_Fem(QString Femurpath)
{
    //Femoral implant load
    stlReader_Femur->SetFileName(Femurpath.toStdString().c_str());
    stlReader_Femur->Update();
}

void ImplantLoad::AssiginingSTLReaders_Tib(QString Tibiapath)
{

    //Tibial implant load
    stlReader_Tibia->SetFileName(Tibiapath.toStdString().c_str());
    stlReader_Tibia->Update();
}

void ImplantLoad::AssiginingSTLReaders_TibSpc(QString Spacerpath)
{
    //Tibialspacer implant load
    stlReader_TibiaSpacer->SetFileName(Spacerpath.toStdString().c_str());
    stlReader_TibiaSpacer->Update();
}



vtkSmartPointer<vtkSTLReader> ImplantLoad::LoadDifferentSizedImplant_Femur(QString btnname)
{
    if(btnname == "m_qpbfemurin")//if + in femur is clicked
    {

        clickednumber_femur = clickednumber_femur + 1;
        if(clickednumber_femur >= 3)
            clickednumber_femur = 3;
        //qDebug()<<"m_qpbfemurin = "<<clickednumber_femur;

    }
    else if(btnname == "m_qpbfemurde")//if - in femur is clicked
    {
        clickednumber_femur = clickednumber_femur - 1;
        if(clickednumber_femur <= 0)
            clickednumber_femur = 1;

        //qDebug()<<"m_qpbfemurde = "<<clickednumber_femur;
    }


    if(clickednumber_femur == 1)
    {

        //Femur implant load
        AssiginingSTLReaders_Fem(m_direc_femoralimplant);

    }
    else if(clickednumber_femur == 2)
    {
        //qDebug()<<"boxval = 2";
        //Femur implant load
        AssiginingSTLReaders_Fem(m_SpcImplant_1_Path);

    }
    else if(clickednumber_femur == 3)
    {
        //qDebug()<<"boxval = 3";
        //Femur implant load
        AssiginingSTLReaders_Fem(m_TibImplant_1_Path);

    }


    return  stlReader_Femur;
}

vtkSmartPointer<vtkSTLReader> ImplantLoad::LoadDifferentSizedImplant_Tibia(QString btnname)
{
    if(btnname == "m_qpbtibiain")//if + in tibia is clicked
    {

        clickednumber_tibia = clickednumber_tibia + 1;
        if(clickednumber_tibia >= 3)
            clickednumber_tibia = 3;
        //qDebug()<<"m_qpbtibiain = "<<clickednumber_tibia;

    }
    else if(btnname == "m_qpbtibiade")//if - in tibia is clicked
    {
        clickednumber_tibia = clickednumber_tibia - 1;
        if(clickednumber_tibia <= 0)
            clickednumber_tibia = 1;

        //qDebug()<<"m_qpbtibiade = "<<clickednumber_tibia;
    }

    if(clickednumber_tibia == 1)
    {
        // qDebug()<<"boxval = 1";
        //Femur implant load
        AssiginingSTLReaders_Tib(m_direc_tibialimplant);

    }
    else if(clickednumber_tibia == 2)
    {
        //qDebug()<<"boxval = 2";
        //Femur implant load
        AssiginingSTLReaders_Tib(m_SpcImplant_1_Path);

    }
    else if(clickednumber_tibia == 3)
    {
        //qDebug()<<"boxval = 3";
        //Femur implant load
        AssiginingSTLReaders_Tib(m_TibImplant_1_Path);

    }
    return  stlReader_Tibia;
}

vtkSmartPointer<vtkSTLReader> ImplantLoad::LoadDifferentSizedImplant_TibSpacer(QString btnname)
{
    if(btnname == "m_qpbpolyin")//if + in poly is clicked
    {

        clickednumber_poly = clickednumber_poly + 1;
        if(clickednumber_poly >= 3)
            clickednumber_poly = 3;
        //qDebug()<<"m_qpbpolyin = "<<clickednumber_poly;

    }
    else if(btnname == "m_qpbpolyde")//if - in poly is clicked
    {
        clickednumber_poly = clickednumber_poly - 1;
        if(clickednumber_poly <= 0)
            clickednumber_poly = 1;

        //qDebug()<<"m_qpbpolyde = "<<clickednumber_poly;
    }

    if(clickednumber_poly == 1)
    {
        // qDebug()<<"boxval = 1";
        //Femur implant load
        AssiginingSTLReaders_TibSpc(m_direc_spacerimplant);

    }
    else if(clickednumber_poly == 2)
    {
        //qDebug()<<"boxval = 2";
        //Femur implant load
        AssiginingSTLReaders_TibSpc(m_TibImplant_2_Path);

    }
    else if(clickednumber_poly == 3)
    {
        //qDebug()<<"boxval = 3";
        //Femur implant load
        AssiginingSTLReaders_TibSpc(m_FemImplant_2_Path);

    }
    return stlReader_TibiaSpacer;
}

