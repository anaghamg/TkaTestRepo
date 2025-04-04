/*
    File Name       : classstl.cpp
    Project Name    : TestSQL
    Created         : 12-03-2024
    Description     : Source file containing implementation for
                      importing and exporting STL using vtk
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#include "classstl.h"

ClassSTL::ClassSTL(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"*********Start of ClassSTL ctor";

    m_pvtkWidgetSTL = new QVTKOpenGLWidget;
    m_pvtkWidgetSTL->SetRenderWindow(m_pvtkOpenGLRenWinSTL);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(m_pvtkWidgetSTL);

    qDebug()<<"End of ClassSTL ctor ";
}

void ClassSTL::GetSTLFilePath()
{
    qDebug()<<"GetSTLFilePath";
    QString stlPath = QFileDialog::getOpenFileName(this,
               tr("Please select STL file"), "/home/", tr("STL Files (*.stl)"));

    if(stlPath != "")
    {
        SetSTLFilePath(stlPath);

        emit signalSTLFilePath(stlPath); //pass path to landmark registration class
    }
}

void ClassSTL::SetSTLFilePath(const QString& qstrSTLPath)
{
    m_qstrSTLFilePath = qstrSTLPath;
    qDebug()<<"Filename in SetSTLFilePath"<<m_qstrSTLFilePath;

    ImportSTL();
}

void ClassSTL::ImportSTL(/*QString qstrSTLInput*/)
{
//    qDebug()<<"importSTL"<<"  "<<"Selected STL filename : "<<m_qstrSTLFilePath;
    m_pvtkSTLReader->SetFileName(m_qstrSTLFilePath.toUtf8().constData());
    m_pvtkSTLReader->Update();
    m_pvtkSTLMapper->SetInputConnection(m_pvtkSTLReader->GetOutputPort());
    m_pvtkSTLActor->SetMapper(m_pvtkSTLMapper);
    m_pvtkSTLActor->GetProperty()->SetDiffuse(0.8);
    m_pvtkSTLActor->GetProperty()->SetSpecular(0.3);
    m_pvtkSTLActor->GetProperty()->SetSpecularPower(60);
        //    m_pvtkSTLActor->GetProperty()->SetColor(1,0.66,1); //pink

    m_pvtkRendererSTL->AddViewProp(m_pvtkSTLActor);
    m_pvtkOpenGLRenWinSTL->AddRenderer(m_pvtkRendererSTL);
    m_pvtkRendererSTL->ResetCamera();
    m_pvtkOpenGLRenWinSTL->Render();

    emit signalLoadStlStatus(true);
}

void ClassSTL::ExportSTL()
{
    //exporting polydata to stl format
    qDebug()<<"exportSTL";
    QString qstrSTLOutput = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "/home/untitled.stl",
                               tr("STL Output (*.stl)"));
    QFile fileout(qstrSTLOutput);
    fileout.open(QIODevice::WriteOnly);
    fileout.close();

    m_pqstrSTLOutput = qstrSTLOutput;
    m_pvtkSTLWriter->SetFileName(m_pqstrSTLOutput.toUtf8().constData());
    qDebug()<<"STL output filename"<<m_pvtkSTLWriter->GetFileName();

    //exporting sphere
    vtkNew <vtkSphereSource> sphere;
    m_pvtkSTLWriter->SetInputConnection(sphere->GetOutputPort());
    m_pvtkSTLWriter->Write();
}
