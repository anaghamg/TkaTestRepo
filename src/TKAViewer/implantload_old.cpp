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

}

std::vector<vtkSmartPointer<vtkActor>>ImplantLoad::LoadedImplant(QString m_fem_implant_path,QString m_tib_implant_path)
{
    qDebug()<<"implant pressed:"<<m_fem_implant_path;

    //Femur implant load
    stlReader_Femur->SetFileName(m_fem_implant_path.toStdString().c_str());
    stlReader_Femur->Update();

    //Tibial implant load
    stlReader_Tibia->SetFileName(m_tib_implant_path.toStdString().c_str());
    stlReader_Tibia->Update();

    //Anterior Femur

    mapper_fem_Anter->SetInputData(stlReader_Femur->GetOutput());
    mapper_fem_Anter->ScalarVisibilityOff();
    mapper_fem_Anter->Update();


    actor_fem_Anter->SetMapper(mapper_fem_Anter);
    actor_fem_Anter->SetPosition( 101.4375, 127.218, 35.1704/*104.4375, 127.218, 35.1704*/);
    actor_fem_Anter->GetProperty()->SetColor(0.0, 1.0, 0.0);
    actor_fem_Anter->RotateX(-180);
    actor_fem_Anter->RotateZ(-35);


    //Distal Femur

    mapper_fem_Distal->SetInputData(stlReader_Femur->GetOutput());
    mapper_fem_Distal->ScalarVisibilityOff();
    mapper_fem_Distal->Update();

    actor_fem_Distal->SetMapper(mapper_fem_Distal);
    actor_fem_Distal->SetPosition( 101.4375, 127.218, 35.1704/*104.4375, 127.218, 35.1704*/);
    actor_fem_Distal->GetProperty()->SetColor(0.0, 1.0, 0.0);
    actor_fem_Distal->RotateX(-180);
    actor_fem_Distal->RotateZ(-35);

    //Lateral Femur

    mapper_fem_Lateral->SetInputData(stlReader_Femur->GetOutput());
    mapper_fem_Lateral->ScalarVisibilityOff();
    mapper_fem_Lateral->Update();


    actor_fem_Lateral->SetMapper(mapper_fem_Lateral);
    actor_fem_Lateral->SetPosition( 101.4375, 127.218, 35.1704/*104.4375, 127.218, 35.1704*/);
    actor_fem_Lateral->GetProperty()->SetColor(0.0, 1.0, 0.0);
    actor_fem_Lateral->RotateX(-180);
    actor_fem_Lateral->RotateZ(-35);


    //-------------Anterior Tibia-------------
    mapper_tib_Anter->SetInputData(stlReader_Tibia->GetOutput());
    mapper_tib_Anter->ScalarVisibilityOff();
    mapper_tib_Anter->Update();


    actor_tib_Anter->SetMapper(mapper_tib_Anter);
    actor_tib_Anter->SetPosition( 92.7578, 120.215, 4);
    actor_tib_Anter->GetProperty()->SetColor(0.0, 1.0, 0.0);
    actor_tib_Anter->RotateZ(45);

    //Distal
    mapper_tib_Distal->SetInputData(stlReader_Tibia->GetOutput());
    mapper_tib_Distal->ScalarVisibilityOff();
    mapper_tib_Distal->Update();


    actor_tib_Distal->SetMapper(mapper_tib_Distal);
    actor_tib_Distal->SetPosition( 92.7578, 120.215, 4);
    actor_tib_Distal->GetProperty()->SetColor(0.0, 1.0, 0.0);
    actor_tib_Distal->RotateZ(45);

    //Lateral
    mapper_tib_Lateral->SetInputData(stlReader_Tibia->GetOutput());
    mapper_tib_Lateral->ScalarVisibilityOff();
    mapper_tib_Lateral->Update();


    actor_tib_Lateral->SetMapper(mapper_tib_Lateral);
    actor_tib_Lateral->SetPosition( 92.7578, 120.215, 4);
    actor_tib_Lateral->GetProperty()->SetColor(0.0, 1.0, 0.0);
    actor_tib_Lateral->RotateZ(45);


    //Adding Actors to the vector
    m_ImplantActors.push_back(actor_fem_Anter);
    m_ImplantActors.push_back(actor_fem_Distal);
    m_ImplantActors.push_back(actor_fem_Lateral);

    m_ImplantActors.push_back(actor_tib_Anter);
    m_ImplantActors.push_back(actor_tib_Distal);
    m_ImplantActors.push_back(actor_tib_Lateral);


    return m_ImplantActors;
}
