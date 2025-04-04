#include "imageselection.h"


imageselection::imageselection(QWidget *parent) : QWidget(parent)
{
    m_objPatientData = new patientdata;

    m_qfbrowseframe = new QFrame;
    m_qfbrowseframe->setFrameShape(QFrame::StyledPanel); // Use a styled panel for a custom border
    m_qfbrowseframe->setObjectName("m_qfbrowseframe");

    m_qpvblBrowseLayout = new QVBoxLayout;
    m_qpvblBrowseLayout->setAlignment(Qt::AlignTop);
    m_qvblRadioBtnLayout = new QVBoxLayout;
    m_qrbtnImageLessBtn = new QRadioButton("Image Less");
    m_qrbtnImageLessBtn->setStyleSheet("font-size:18px; font-family:Inter;");
    m_qrbtnImageBasedBtn = new QRadioButton("Image Based");
    m_qrbtnImageBasedBtn->setStyleSheet("font-size:18px; font-family:Inter;");

    QLabel *lblselecetdKnee = new QLabel("Knee Side");
    lblselecetdKnee->setStyleSheet({"border:none; font-size:18px; font-family:Inter;"});

    lblselecetdKnee->setAlignment(Qt::AlignCenter);


    timer = new QTimer();

    m_qcbKnee = new QComboBox;
    m_qcbKnee->setObjectName("kneecomboBox");
    m_qcbKnee->addItem(tr("Select"));
    m_qcbKnee->addItem(tr("Left Knee"));
    m_qcbKnee->addItem(tr("Right Knee"));
    m_qcbKnee->setStyleSheet({"padding:0px; border-radius:0px;font-size:18px; font-family:Inter;"});

    m_qhblcomboboxLayout = new QHBoxLayout;
    m_qhblcomboboxLayout->addWidget(lblselecetdKnee,2);
    m_qhblcomboboxLayout->addWidget(m_qcbKnee,2);

    m_hblWidgetLayout = new QHBoxLayout;
    m_hblWidgetLayout->addLayout(m_qvblRadioBtnLayout,10);

    m_qwDCMWidget = new QVTKOpenGLWidget;
    m_ResliceImageViewer->SetRenderWindow(m_RenderWindow );
    m_qwDCMWidget->GetRenderWindow()->SetInteractor(m_Interaction);
    m_qwDCMWidget->SetRenderWindow(m_ResliceImageViewer->GetRenderWindow());

    m_qwSTLWidget= new QVTKOpenGLWidget;
    m_qwSTLWidget->SetRenderWindow(m_pvtkOpenGLRenWinSTL);

    m_qvblVTKWidgetLayout = new QHBoxLayout;
    m_qvblVTKWidgetLayout->addWidget(m_qwDCMWidget,30);
    m_qvblVTKWidgetLayout->addWidget(m_qwSTLWidget,30);

    m_hblWidgetLayout->addLayout(m_qvblVTKWidgetLayout,30);
    m_qbtnBrowseImage = new QPushButton("Browse");
    m_qbtnBrowseImage->setObjectName("m_SelectButton");
    m_qbtnBrowseImage->setCheckable(true);

    m_qbtnSegmentImage = new QPushButton("Segment");
        m_qbtnSegmentImage->setObjectName("m_SelectButton");
        m_qbtnSegmentImage->setCheckable(true);
        m_qbtnSegmentImage->setVisible(false);

    //    QHBoxLayout* temp = new QHBoxLayout;
    //    temp->addWidget(m_qbtnBrowseImage);

    m_qvblRadioBtnLayout->addWidget(m_qrbtnImageLessBtn);
    m_qvblRadioBtnLayout->addWidget(m_qrbtnImageBasedBtn);
    m_qvblRadioBtnLayout->addLayout(m_qhblcomboboxLayout);
    m_qvblRadioBtnLayout->addWidget(m_qbtnBrowseImage,2,Qt::AlignLeft);
   m_qvblRadioBtnLayout->addWidget(m_qbtnSegmentImage,1,Qt::AlignLeft);
    m_qvblRadioBtnLayout->addWidget(progressBar);

    m_qfbrowseframe->setLayout(m_hblWidgetLayout);
    m_qpvblBrowseLayout->addWidget(m_qfbrowseframe);
    m_qfbrowseframe->hide();

    //Browse button click
    connect(m_qbtnBrowseImage, &QPushButton::clicked, this ,&imageselection::BrowseandLoadImage);

    //Segment button click
    connect(m_qbtnSegmentImage, &QPushButton::clicked, this ,&imageselection::saksExecute);


    m_objWorkerSAKS = new executeSAKS;
    connect(this, &imageselection::signalDcmDir, m_objWorkerSAKS, &executeSAKS::slotdcmDir);

    //connect(timer, &QTimer::timeout, this, &imageselection::LoadDCM);
}


void imageselection::executeSAKSInThread()
{
    // rupika thread test
    startReading();
    workerThreadSaks = new QThread(this);
    m_objWorkerSAKS->moveToThread(workerThreadSaks); // Move the worker to the thread

    connect(workerThreadSaks, &QThread::started, m_objWorkerSAKS, &executeSAKS::doSAKS);
    connect(workerThreadSaks,&QThread::finished, workerThreadSaks, &QThread::quit);



    workerThreadSaks->start();


    if (workerThreadSaks->isFinished()) {
        qDebug() << "Thread completed running.";
    }
}

void imageselection::onWorkFinished()
{

      qDebug() << "onWorkFinished";
    //new saks 26-10-2024

    progressDialog->setValue(98);

    m_qstrDcmFull=m_qsimagePath;
    m_qstrDcmFemur = QDir::currentPath() + "/Segmentation_batfile/output/Femur";
    m_qstrDcmTibia = QDir::currentPath() + "/Segmentation_batfile/output/Tibia";
    setDicomDirectories(m_qstrDcmFull,m_qstrDcmFemur,m_qstrDcmTibia);

    m_qstrStlFemur = QDir::currentPath() + "/Segmentation_batfile/output/FemurModel.stl";
    m_qstrStlTibia = QDir::currentPath() + "/Segmentation_batfile/output/TibiaModel.stl";

    setStlPaths(/*m_qstrStlFull,*/ m_qstrStlFemur, m_qstrStlTibia);

  // Once work is finished, close the dialog
   QMetaObject::invokeMethod(progressDialog, "cancel", Qt::QueuedConnection);
}

void imageselection::BrowseandLoadImage()
{

    m_qsSelectedKnee = m_qcbKnee->currentText();
    if (m_qrbtnImageLessBtn->isChecked()) //Load STL
    {
        m_qsimagePath = QFileDialog::getOpenFileName(this,
                                                     tr("Please select STL file"), "/home/", tr("STL Files (*.stl)"));

        if (!m_qsimagePath.isEmpty()) {
            QDir dir(m_qsimagePath);

            if (dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).isEmpty()) {
                qDebug()<<"STL path"<<m_qsimagePath;
                SPDLOG_INFO("STL Image Selected ");
                LoadSTL();
            }
            else
            {
                // Subfolders found
                QMessageBox::warning(nullptr, "Warning", "The selected directory contains subfolders. Please select a folder without subfolders.");
            }
        }
    }

    else if (m_qrbtnImageBasedBtn->isChecked()) //Load Dicom
    {
        m_qsimagePath = QFileDialog::getExistingDirectory(this, tr("Select Dicom Folder"),
                                                          "/home",
                                                          QFileDialog::ShowDirsOnly
                                                          |QFileDialog::DontResolveSymlinks
                                                          |QFileDialog::DontUseNativeDialog);

        if (!m_qsimagePath.isEmpty()) {

            QString fileType = ".dcm";

            QDir dir(m_qsimagePath);
            if (dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).isEmpty()) {

                // A directory was selected
                qDebug()<<"'Dicom path"<<m_qsimagePath;
                SPDLOG_INFO("DCM Image Selected ");
                m_qbtnSegmentImage->setVisible(true);
                QCoreApplication::processEvents();// Ensure that the UI updates are processed

                emit signalDcmDir(m_qsimagePath);
              //  emit loadImage();


               LoadDCM();

             //   executeSAKSInThread();


                //-------------DICOM------------//
                //new saks 26-10-2024
//                m_qstrDcmFull=m_qsimagePath;
//                m_qstrDcmFemur = QDir::currentPath() + "/Segmentation_batfile/output/Femur";
//                m_qstrDcmTibia = QDir::currentPath() + "/Segmentation_batfile/output/Tibia";

              //  setDicomDirectories(m_qstrDcmFull,m_qstrDcmFemur,m_qstrDcmTibia);

                //-------------STL------------//
                //get segmented femur and tibia from build folder

                //new saks
//                m_qstrStlFemur = QDir::currentPath() + "/Segmentation_batfile/output/phantom_femur_new.stl";
//                m_qstrStlTibia = QDir::currentPath() + "/Segmentation_batfile/output/phantom_tibia_new.stl";

//                setStlPaths(/*m_qstrStlFull,*/ m_qstrStlFemur, m_qstrStlTibia);
            }
            else
            {
                // Subfolders found
                QMessageBox::warning(nullptr, "Warning", "The selected directory contains subfolders. Please select a folder without subfolders.");
            }
        }
    }

    else
    {
        QMessageBox::warning(this, tr("Warning"), tr("Please select any one option"));
        //SPDLOG_WARN("Image not seleceted");
    }

    // QTimer::singleShot(5000, messageBox, &QMessageBox::accept); // 3000 ms = 3 seconds
    m_objPatientData->patientImageData(m_qsimagePath,m_qsSelectedKnee);

}


void imageselection::saksExecute()
{

    QString filePath = QDir::currentPath() + "/Segmentation_batfile/output/progress.txt";

        QFile file(filePath);
        file.remove();


     startReading();
     executeSAKSInThread();

}


void imageselection::LoadDCM()
{
    qDebug()<<"Load DCM"<<m_qsimagePath;

    m_pvtkDcmReader=  vtkSmartPointer<vtkDICOMImageReader> ::New();
    qDebug()<<"Dicom directory in ImportDicom"<<m_qsimagePath;
    m_pvtkDcmReader->SetDirectoryName(m_qsimagePath.toUtf8().constData());
    m_pvtkDcmReader->Update();

    //2D
    m_ResliceImageViewer->SetInputConnection(m_pvtkDcmReader->GetOutputPort());
    m_ResliceImageViewer->SetupInteractor(m_RenderWindow->GetInteractor());

    //******************* WL and WW for PHANTOM data ******************//

    double window = 1500; //1000
    double level = -700; //40
    m_ResliceImageViewer->SetColorWindow(window);
    m_ResliceImageViewer->SetColorLevel(level);

    m_ResliceImageViewer->Render();
    this->update();

    //3D
    mapper->RemoveAllInputs();
    mapper->SetInputConnection(m_pvtkDcmReader->GetOutputPort());
    mapper->SetSampleDistance(0.1);
    mapper->SetAutoAdjustSampleDistances(0);
    mapper->SetBlendModeToComposite();
    mapper->SetSampleDistance(0.1);
    mapper->Update();

    //           opacityFun->AddPoint(0, 0.0);
    //           opacityFun->AddPoint(30, 0.5);
    //           opacityFun->AddPoint(70, 0.3);
    //           opacityFun->AddPoint(125, 0.2);
    //           opacityFun->AddPoint(500, 0.8);
    //           opacityFun->AddPoint(1150, 0.8);
    //           opacityFun->AddPoint(-800, 0.1);
    //           opacityFun->AddPoint(-700, 0.8);//0.8
    //           opacityFun->AddPoint(-500, 0.8);
    //           opacityFun->AddPoint(-200, 0.8);

    //******************* opacity and colour for PHANTOM data ******************//
    opacityFun->AddPoint(-3024, 0.0);
    opacityFun->AddPoint(-1859, 0.0);
    opacityFun->AddPoint(-1296, 0.0);
    opacityFun->AddPoint(-895, 0.0);
    opacityFun->AddPoint(621, 1.0);
    opacityFun->AddPoint(2212, 0.15);
    opacityFun->AddPoint(3492, 1.0);

    opacityFun->AddPoint(100, 1.0);

    // Create transfer mapping scalar value to color
//    volumeColor->AddRGBPoint(0, 0.0, 0.0, 0.0);
//    volumeColor->AddRGBPoint(30, 1.0, 0.5, 0.3);
//    volumeColor->AddRGBPoint(70, 1.0, 0.8, 0.8);
//    volumeColor->AddRGBPoint(125, 1.0, 1.0, 0.9);
//    volumeColor->AddRGBPoint(500, 1.0, 1.0, 0.9);
//    volumeColor->AddRGBPoint(1150, 1.0, 1.0, 0.9);
//    volumeColor->AddRGBPoint(-500, 1.0, 1.0, 0.9);
//    volumeColor->AddRGBPoint(-700, 1.0, 1.0, 0.9);
//    volumeColor->AddRGBPoint(-800, 1.0, 1.0, 0.9);
//    volumeColor->AddRGBPoint(-200, 1.0, 1.0, 0.9);



    volumeColor->AddRGBPoint(-3024, 1.0, 1.0, 1.0);
    volumeColor->AddRGBPoint(-1000, 1.0, 1.0, 1.0);

  //    volumeColor->AddRGBPoint(621, 0.9, 0.9, 0.8);    // White for low-density bone
//    volumeColor->AddRGBPoint(1500, 0.8, 0.8, 0.9);   // Light grey for denser bone
//    volumeColor->AddRGBPoint(2212, 1.0, 1.0, 0.9);   // Slightly yellowish white for dense bone


    volumeColor->AddRGBPoint(621, 0.9, 0.9, 0.8);    // White for low-density bone
    volumeColor->AddRGBPoint(1500, 1.0, 1.0, 1.0);   // Light grey for denser bone
    volumeColor->AddRGBPoint(2212, 1.0, 1.0, 0.9);   // Slightly yellowish white for dense bone
    volumeColor->AddRGBPoint(3492, 1.0, 1.0, 1.0);   // Pure white for very dense bone


    volumeColor->AddRGBPoint(-700, 1.0, 1.0, 1.0);




    property->RemoveAllObservers();
    property->SetColor(volumeColor);
    property->SetScalarOpacity(opacityFun);
    property->ShadeOn();
    property->SetInterpolationTypeToLinear();

    //property->SetAmbient(200, 0.2);
    //property->SetAmbient(200, 1);

    // Setting the volume
    volume->SetMapper(mapper);
    volume->SetProperty(property);
    volume->Update();

    // Add volume to renderer
    renderer->AddVolume(volume);
    renderer->GlobalWarningDisplayOff();

    // Create renderer, render window, and interactor
    m_pvtkOpenGLRenWinSTL->AddRenderer(renderer);

    // Reset camera and render
    //  renderer->GetActiveCamera()->Azimuth(45);
    renderer->GetActiveCamera()->Elevation(50);
    renderer->GetActiveCamera()->Roll(50);
    //renderer->GetActiveCamera()->Zoom(8);

    renderer->ResetCamera();
    m_pvtkOpenGLRenWinSTL->Render();
}

void imageselection::LoadSTL()
{

    qDebug()<<"Load STL"<<m_qsimagePath;
    m_pvtkSTLReader->SetFileName(m_qsimagePath.toUtf8().constData());
    m_pvtkSTLReader->Update();
    m_pvtkSTLMapper->SetInputConnection(m_pvtkSTLReader->GetOutputPort());
    m_pvtkSTLActor->SetMapper(m_pvtkSTLMapper);
    m_pvtkSTLActor->GetProperty()->SetDiffuse(0.8);
    m_pvtkSTLActor->GetProperty()->SetSpecular(0.3);
    m_pvtkSTLActor->GetProperty()->SetSpecularPower(60);


    m_pvtkRendererSTL->AddViewProp(m_pvtkSTLActor);
    m_pvtkOpenGLRenWinSTL->AddRenderer(m_pvtkRendererSTL);
    m_pvtkRendererSTL->ResetCamera();
    m_pvtkOpenGLRenWinSTL->Render();
    this->update();
}

void imageselection::setDicomDirectories(const QString& qstrDcmFull, const QString& qstrDcmFemur, const QString& qstrDcmTibia)
{
    qDebug()<<"setDicomDirectories"<<m_qsSelectedKnee;

    m_qstrDcmFull = qstrDcmFull;
    m_qstrDcmFemur = qstrDcmFemur;
    m_qstrDcmTibia = qstrDcmTibia;

    // emit signalLoadedDicom(m_qstrDcmFull, m_qstrDcmFemur, m_qstrDcmTibia);
    emit signalLoadedDicom(m_qstrDcmFull, m_qstrDcmFemur, m_qstrDcmTibia,m_qsSelectedKnee);
}

void imageselection::setStlPaths(/*const QString& qstrStlFull,*/ const QString &qstrStlFemur, const QString qstrStlTibia)
{
    qDebug()<<"setStlPaths"<<qstrStlFemur<<qstrStlTibia;

    //m_qstrStlFull = qstrStlFull;
    m_qstrStlFemur = qstrStlFemur;
    m_qstrStlTibia = qstrStlTibia;

    emit signalLoadedStl(/*m_qstrStlFull,*/ m_qstrStlFemur, m_qstrStlTibia);
}


void imageselection::updateProgress() {
    // Read status from the text file
    QFile file( QDir::currentPath() +"/Segmentation_batfile/output/progress.txt"); // Replace with your file path

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;


        if (in.readLineInto(&line)) {
            // Use regex to extract the percentage value
            QRegularExpression regex("Progress:\\s*(\\d+\\.\\d+)%");
            QRegularExpressionMatch match = regex.match(line);

            if (match.hasMatch()) {
                // Extract the percentage and convert to int
                QString percentStr = match.captured(1);
                currentProgress = match.captured(1).toDouble();
                 progressDialog->setValue(static_cast<int>(currentProgress));
                //progressBar->setValue(static_cast<int>(currentProgress)); // Update progress bar

            } else {
                qDebug() << "No valid percentage found in the line.";
            }





            file.close();
        } } else {
        qDebug() << "Could not open file for reading.";
    }


    // Stop timer when done (assuming 100% is the end)
    if (currentProgress == 100) {

        timer->stop();
        qDebug()<<"progress completed";


        QtConcurrent::run([this]() {
            onWorkFinished();  // Calling the member function 'onWorkFinished'
        });


    }
}

void imageselection::startReading() {
    qDebug()<<"inside startreading";

        // Create the progress dialog
         if (progressDialog == nullptr) {
         progressDialog = new QProgressDialog("Processing...", "Cancel", 0, 100);
         progressDialog->setWindowModality(Qt::WindowModal);  // Ensure it's modal
         progressDialog->setMinimumDuration(0);  // Show immediately
         progressDialog->setValue(5);
         progressDialog->setLabelText("Loading...");
         progressDialog->setAutoClose(false);
         progressDialog->setCancelButton(nullptr);
         progressDialog->setFixedSize(350,100);




         progressDialog->setStyleSheet("QProgressBar {color: black;text-align:center;"
                                     "    background-color: #e0e0e0;" // Background color
                                       "    border: 2px solid #555555;" // Border
                                        "    border-radius: 5px;" // Rounded corners
                                       "}"
                                       "QProgressBar::chunk {"
                                        "    background-color: #76c7c0;" // Color of the progress chunk

                                        "    border-radius: 5px;" // Rounded corners for the chunk
                                        "}"
                                       "QProgressBar::text {"
                                                              "    color: black; font-size:12px;"
                                                             "}");



                    connect(timer, &QTimer::timeout, this, &imageselection::updateProgress);
                    timer->start(500); // Update every 500ms
         }

}



