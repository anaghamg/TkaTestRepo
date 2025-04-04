/*
    File Name       : Checkpoint.cpp
    Project Name    : TKA Robotic Surgery
    Created         : 18-11-2024
    Description     : Source file containing implementation for
                      displaying Femur and Tibia Checkpoint images
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/
#include "checkpoint.h"

Checkpoint::Checkpoint(QWidget *parent) : QWidget(parent)
{
//    m_pvtkWidgetChkpt = new QVTKOpenGLWidget;
//    m_pvtkImageviewer->OffScreenRenderingOn();
//    m_pvtkImageviewer->SetRenderWindow(m_openGlRenWin);
//    m_pvtkWidgetChkpt->SetRenderWindow(m_openGlRenWin);

    m_pvtkWidgetChkptFemur = new QVTKOpenGLWidget;
    m_pvtkImageviewerFemur->OffScreenRenderingOn();
    m_pvtkImageviewerFemur->SetRenderWindow(m_openGlRenWinFemur);
    m_pvtkWidgetChkptFemur->SetRenderWindow(m_openGlRenWinFemur);

    m_pvtkWidgetChkptTibia = new QVTKOpenGLWidget;
    m_pvtkImageviewerTibia->OffScreenRenderingOn();
    m_pvtkImageviewerTibia->SetRenderWindow(m_openGlRenWinTibia);
    m_pvtkWidgetChkptTibia->SetRenderWindow(m_openGlRenWinTibia);


//    m_openGlRenWinFemur->SetInteractor(m_pvtkInter1);
//    m_openGlRenWinTibia->SetInteractor(m_pvtkInter2);

//    //annotation actor to signify Lateral(right)/Medial(left) of the screen
//    actorL->SetInput("L");
//    actorM->SetInput("M");

//    //actorL->SetTextScaleMode(8);
//    //actorL->SetDisplayPosition(0,155);
//    actorL->GetTextProperty()->SetFontSize(24);
//    actorL->GetTextProperty()->SetFontFamilyAsString("Inter");
//    actorL->GetTextProperty()->BoldOn();
//    actorL->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

//    actorM->GetTextProperty()->SetFontSize(24);
//    actorM->GetTextProperty()->SetFontFamilyAsString("Inter");
//    actorM->GetTextProperty()->BoldOn();
//    actorM->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

//    actorM->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
//    actorM->GetPositionCoordinate()->SetValue(0.03, 0.5);
//    //    actorM->GetPositionCoordinate()->SetValue(0.0, 0.5);

//    actorL->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
//    actorL->GetPositionCoordinate()->SetValue(0.97, 0.5);


//    m_pvtkImageviewerFemur->GetRenderer()->AddActor(actorL);
//    m_pvtkImageviewerFemur->GetRenderer()->AddActor(actorM);

//         m_pvtkImageviewerTibia->GetRenderer()->AddActor(actorL);
//         m_pvtkImageviewerTibia->GetRenderer()->AddActor(actorM);



    m_qswCheckpt = new QStackedWidget;
    m_qswCheckpt->insertWidget(0,m_pvtkWidgetChkptFemur);
    m_qswCheckpt->insertWidget(1,m_pvtkWidgetChkptTibia);
    m_qswCheckpt->setCurrentIndex(0);

    setChkptImageFemur();
    setChkptImageTibia();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_qswCheckpt);
    this->setLayout(mainLayout);
}

void Checkpoint::setChkptImageFemur()
{
    m_qswCheckpt->setCurrentIndex(0);


    QString qstrImgpath = QDir::currentPath() + "/CheckpointImage/femur.png";
    qDebug()<<"setChkptImageFemur"<<qstrImgpath;

    if (!QFile::exists(qstrImgpath))
    {
        qDebug() << "Checkpt image not found at path : " << qstrImgpath;
        return;
    }

    vtkSmartPointer<vtkPNGReader> m_pvtkReaderFemur = vtkSmartPointer<vtkPNGReader>::New();
    m_pvtkReaderFemur->SetFileName(qstrImgpath.toStdString().c_str());
    m_pvtkReaderFemur->Update();

    m_pvtkImageviewerFemur->SetInputConnection(m_pvtkReaderFemur->GetOutputPort());

//    //annotation actor to signify Lateral(right)/Medial(left) of the screen
//    actorL->SetInput("L");
//    actorM->SetInput("M");

//    //actorL->SetTextScaleMode(8);
//    //actorL->SetDisplayPosition(0,155);
//    actorL->GetTextProperty()->SetFontSize(24);
//    actorL->GetTextProperty()->SetFontFamilyAsString("Inter");
//    actorL->GetTextProperty()->BoldOn();
//    actorL->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

//    actorM->GetTextProperty()->SetFontSize(24);
//    actorM->GetTextProperty()->SetFontFamilyAsString("Inter");
//    actorM->GetTextProperty()->BoldOn();
//    actorM->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

//    actorM->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
//    actorM->GetPositionCoordinate()->SetValue(0.03, 0.5);
//    actorL->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
//    actorL->GetPositionCoordinate()->SetValue(0.97, 0.5);

//    m_pvtkImageviewerFemur->GetRenderer()->AddActor(actorL);
//    m_pvtkImageviewerFemur->GetRenderer()->AddActor(actorM);

    m_pvtkImageviewerFemur->GetRenderer()->ResetCamera();
    m_pvtkImageviewerFemur->GetRenderer()->GetActiveCamera()->Zoom(1.5);

    m_pvtkImageviewerFemur->Render();
    m_pvtkWidgetChkptFemur->GetRenderWindow()->Render();
}

void Checkpoint::setChkptImageTibia()
{
    m_qswCheckpt->setCurrentIndex(1);

    QString qstrImgpath = QDir::currentPath() + "/CheckpointImage/tibia.png";
    qDebug()<<"setChkptImageTibia"<<qstrImgpath;

    if (!QFile::exists(qstrImgpath))
    {
        qDebug() << "Checkpt image not found at path : " << qstrImgpath;
        return;
    }

    vtkSmartPointer<vtkPNGReader> m_pvtkReaderTibia = vtkSmartPointer<vtkPNGReader>::New();
    m_pvtkReaderTibia->SetFileName(qstrImgpath.toStdString().c_str());
    m_pvtkReaderTibia->Update();

    m_pvtkImageviewerTibia->SetInputConnection(m_pvtkReaderTibia->GetOutputPort());

//    //annotation actor to signify Lateral(right)/Medial(left) of the screen
//    actorL->SetInput("L");
//    actorM->SetInput("M");

//    //actorL->SetTextScaleMode(8);
//    //actorL->SetDisplayPosition(0,155);
//    actorL->GetTextProperty()->SetFontSize(24);
//    actorL->GetTextProperty()->SetFontFamilyAsString("Inter");
//    actorL->GetTextProperty()->BoldOn();
//    actorL->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

//    actorM->GetTextProperty()->SetFontSize(24);
//    actorM->GetTextProperty()->SetFontFamilyAsString("Inter");
//    actorM->GetTextProperty()->BoldOn();
//    actorM->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

//    actorM->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
//    actorM->GetPositionCoordinate()->SetValue(0.03, 0.5);
//    actorL->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
//    actorL->GetPositionCoordinate()->SetValue(0.97, 0.5);

    //        m_pvtkImageviewerTibia->GetRenderer()->AddActor(actorL);
    //        m_pvtkImageviewerTibia->GetRenderer()->AddActor(actorM);

    m_pvtkImageviewerTibia->GetRenderer()->ResetCamera();
    m_pvtkImageviewerTibia->GetRenderer()->GetActiveCamera()->Zoom(1.5);

    m_pvtkImageviewerTibia->Render();
    m_pvtkWidgetChkptTibia->GetRenderWindow()->Render();
}

//will render each time checkpoint is called
//void Checkpoint::setCheckpointImage(const QString &qstrBone)
//{
//    qDebug()<<"setCheckpointImage";
//    QString qstrImgpath;

//    if(qstrBone == "Femur")
//    {
//        qstrImgpath = QDir::currentPath() + "/CheckpointImage/femur.png";
//    }
//    else if (qstrBone == "Tibia")
//    {
//        qstrImgpath = QDir::currentPath() + "/CheckpointImage/tibia.png";
//    }

//    if (!QFile::exists(qstrImgpath))
//    {
//        qDebug() << "Checkpt image not found at path : " << qstrImgpath;
//        return;
//    }

//    qDebug()<<"qstrImgpath"<<qstrImgpath;

//    vtkSmartPointer<vtkPNGReader> m_pvtkPngReader = vtkSmartPointer<vtkPNGReader>::New();
//    m_pvtkPngReader->SetFileName(qstrImgpath.toStdString().c_str());
//    m_pvtkPngReader->Update();
//    m_pvtkImageviewer->SetInputConnection(m_pvtkPngReader->GetOutputPort());
//    m_pvtkImageviewer->GetRenderer()->ResetCamera();
//    m_pvtkImageviewer->GetRenderer()->GetActiveCamera()->Zoom(1.8);
//    m_pvtkImageviewer->Render();
//    m_pvtkWidgetChkpt->GetRenderWindow()->Render();
//}
