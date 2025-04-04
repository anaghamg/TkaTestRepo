#include "classdicom.h"

ClassDicom::ClassDicom(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"Start of ClassDicom ctor";

    //    m_pvtkWidget = new QVTKOpenGLWidget;
    //    m_pvtkWidget->SetRenderWindow(m_pvtkOpenGLRenWinDcm);
    //    m_pvtkImageViewer->OffScreenRenderingOn();
    //    m_pvtkImageViewer->SetRenderWindow(m_pvtkWidget->GetRenderWindow());

    //      m_ResliceImageViewer->SetRenderWindow(m_RenderWindow );
    //      this->m_pvtkWidget->GetRenderWindow()->SetInteractor(m_Interaction);

    //      //
    //       this->m_pvtkWidget->SetRenderWindow(m_ResliceImageViewer->GetRenderWindow());
    //       m_ResliceImageViewer->SetupInteractor(this->m_pvtkWidget->GetRenderWindow()->GetInteractor());



    //      //m_pvtkImageViewer->SetupInteractor(m_pvtkWidget->GetInteractor());

    //    m_pvtkImageViewer->GetRenderer()->GlobalWarningDisplayOff();     //remove popup warnings

    //    QHBoxLayout *mainLayout = new QHBoxLayout;
    //    mainLayout->addWidget(m_pvtkWidget);
    //    this->setLayout(mainLayout);

    //    qDebug()<<"End of Classdicom ctor";








    m_pvtkWidget = new QVTKOpenGLWidget;
//    m_pvtkWidget->SetRenderWindow(m_pvtkOpenGLRenWin);
    m_pvtkImageViewer->OffScreenRenderingOn();
//    m_pvtkImageViewer->SetRenderWindow(m_pvtkWidget->GetRenderWindow());



    m_ResliceImageViewer->SetRenderWindow(m_RenderWindow );
    this->m_pvtkWidget->GetRenderWindow()->SetInteractor(m_Interaction);


    //
    this->m_pvtkWidget->SetRenderWindow(m_ResliceImageViewer->GetRenderWindow());
    m_ResliceImageViewer->SetupInteractor(this->m_pvtkWidget->GetRenderWindow()->GetInteractor());
    // m_pvtkImageViewer->SetupInteractor(m_pvtkWidget->GetInteractor());

    m_pvtkImageViewer->GetRenderer()->GlobalWarningDisplayOff();

    //    qDebug()<<"Classdicom 2";

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_pvtkWidget);
    this->setLayout(mainLayout);

    //    connect(this,&ClassDicom::DicomDirPath,
    //            this,&ClassDicom::ImportDicom);

    qDebug()<<"End of Classdicom ctor";



}

void ClassDicom::GetDicomDirectory()
{
    qDebug()<<"GetDicomDirectory in ClassDicom";
    QString qstrDir = QFileDialog::getExistingDirectory(this, tr("Select Dicom Folder"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        |QFileDialog::DontResolveSymlinks
                                                        |QFileDialog::DontUseNativeDialog);
    if(qstrDir != "")
    {
        SetDicomDirectory(qstrDir);

        emit signalDicomDirPath(qstrDir);
    }
    qDebug()<<"Emitted Dicom directory from ClassDicom";
}

void ClassDicom::SetDicomDirectory(QString qstrDcmDir)
{
    m_qstrDcmDir = qstrDcmDir;
    qDebug()<<"SetDicomDirectoy in ClassDicom : "<<m_qstrDcmDir;
    ImportDicom();
}

void ClassDicom::ImportDicom()
{
    m_pvtkDcmReader=  vtkSmartPointer<vtkDICOMImageReader> ::New();
    qDebug()<<"Dicom directory in ImportDicom"<<m_qstrDcmDir;
    m_pvtkDcmReader->SetDirectoryName(m_qstrDcmDir.toUtf8().constData());
    m_pvtkDcmReader->Update();
   // m_pvtkImageViewer->SetInputConnection(m_pvtkDcmReader->GetOutputPort());

//    m_pvtkImageViewer->GetRenderer()->ResetCamera();
//    m_pvtkImageViewer->Render();
//    m_pvtkWidget->GetInteractor()->Initialize();
//    qDebug()<<"finished ImportDicom........ ";


    m_ResliceImageViewer->SetInputData(m_pvtkDcmReader->GetOutput());
         // make them all share the same reslice cursor object.
 //        m_ResliceImageViewer->GetResliceCursor()->SetHoleWidthInPixels(1000);


 //        m_ResliceImageViewer->SetSliceOrientationToXY(); //     view


 //        m_ResliceImageViewer->SetResliceModeToOblique();
 //        m_ResliceImageViewer->SetSlice(250);
 //        m_ResliceImageViewer->GetResliceCursorWidget()->SetEnabled(1);
 //        m_ResliceImageViewer   ->GetInteractor()->SetInteractorStyle(m_ActorStyle   );



 //        double window = 1000;
 //        double level = 40;
 //        m_ResliceImageViewer   ->SetColorWindow(window);
 //        m_ResliceImageViewer   ->SetColorLevel(level);



         m_ResliceImageViewer->Render();

 //        m_ResliceImageViewer->GetRenderer()->ResetCamera();


//         m_ResliceImageViewer->GetRenderer()->GetActiveCamera()->Zoom(1.2);


         m_Interaction->Initialize();

 //        m_pvtkWidget->GetInteractor()->Initialize();





    emit signalLoadDicomStatus(true);
}
