#include "regimplementation.h"

QString m_file1Path = QDir::currentPath()+"/RegistrationFiles/" +"sourcePoints.txt";
QFile file_V1Points(m_file1Path);

QString m_file3PathSur = QDir::currentPath()+"/RegistrationFiles/" +"sourcePointsSurface.txt";
QFile file_V3PointsSur(m_file3PathSur);

//QString m_file1Path2 = QDir::currentPath()+"/RegistrationFiles/" +"sourcePointsSTLtibia.txt";
//QFile file_V1Points2(m_file1Path2);

QString m_file2Path = QDir::currentPath() + "/RegistrationFiles/" + "targetPoints.txt";
QFile file_V2Points(m_file2Path);

class  MouseCallback : public vtkCommand
{
    //    Q_OBJECT
public:
    static MouseCallback* New()
    {
        return new MouseCallback;
    }

    void Execute(vtkObject* caller, unsigned long eventId, void* callData) override
    {
        if(eventId == LeftButtonPressEvent)
        {
            vtkRenderWindowInteractor* interactor = dynamic_cast<vtkRenderWindowInteractor*>(caller); //static_cast

            //detect double-clcik event
            if(interactor->GetRepeatCount()==1)
            {
                int vtkX, vtkY;
                interactor->GetEventPosition(vtkX, vtkY); //display coordinates
                qDebug() << "vtkX:" << vtkX << "\t"<< "vtkY:" << vtkY ;//<< "\n" ;

                propPicker->Pick(vtkX, vtkY,0 ,renCbk1);
                propPicker->AddPickList(surfaceActor);
                picked = propPicker->GetPickPosition();
                qDebug()<<"Picked Pos : "<< picked[0] << " " << picked[1] << " " << picked[2] ;//<< "\n" ;
                qDebug()<<m_file1Path;

                if (!file_V1Points.open(QIODevice::WriteOnly |QIODevice::Append| QIODevice::Text))
                {
                    qDebug() << "Error opening file for writing!";
                }
                else
                {
                    //write into text file
                    QTextStream inV1Points(&file_V1Points);
                    //                    QTextStream inV1Points(&file_V1Points2);
                    for (int i = 0; i < 3; ++i)
                    {
                        inV1Points<<picked[i]<< endl;
                    }
                    file_V1Points.close();
                    //                    file_V1Points2.close();
                }
                //render a sphere at pick position
                vtkSmartPointer <vtkSphereSource> sph =  vtkSmartPointer <vtkSphereSource>::New();
                vtkSmartPointer <vtkPolyDataMapper> sphMapper =  vtkSmartPointer <vtkPolyDataMapper>::New();
                sph->SetRadius(3);
                sph->SetThetaResolution(10);
                sph->SetPhiResolution(10);
                sph->SetCenter(picked[0], picked[1], picked[2]);
                sph->Update();
                sphMapper->SetInputConnection(sph->GetOutputPort());
                vtkSmartPointer <vtkActor> sphActor =  vtkSmartPointer <vtkActor>::New();
                sphActor->SetMapper(sphMapper);
                sphActor->GetProperty()->SetColor(0,0,1); //pink 1,0.66,1

                //                    renCbk1->AddActor(sphActor);
                assemblyCbk1->AddPart(sphActor);
                renCbk1->GetRenderWindow()->Render();
            }
        }
    }

    void SetRenderer(vtkSmartPointer <vtkRenderer> ren1)
    {
        renCbk1 = ren1;
    }

    void SetActor(vtkSmartPointer <vtkActor> actor1)
    {
        surfaceActor = actor1;
    }

    void SetAssembly(vtkSmartPointer <vtkAssembly > assmb1)
    {
        assemblyCbk1 = assmb1;
    }

public:

    vtkSmartPointer<vtkPropPicker> propPicker = vtkSmartPointer<vtkPropPicker>::New();  //vtkWorldPointPicker
    double* picked ;
    vtkSmartPointer <vtkRenderer> renCbk1;
    vtkSmartPointer <vtkActor> surfaceActor;
    vtkSmartPointer <vtkAssembly> assemblyCbk1;
};



RegImplementation::RegImplementation(QWidget *parent) : QWidget(parent)
{
    //sw for rendering
    m_pvtkWidget = new QVTKOpenGLWidget; //vtk widget
    m_objHipCenterApi = new hipcenterapi;

    m_pvtkWidget->SetRenderWindow(m_openGlRenWin);
    m_openGlRenWin->AddRenderer(m_pvtkRenderer);
    //set interactor for using callback
    m_pvtkWidget->GetRenderWindow()->SetInteractor(m_pvtkInteractorReg); //comment when using qt slot connector
    m_pvtkWidget->GetRenderWindow()->GetInteractor()->SetInteractorStyle(m_istyle); //added on 01-07-2024


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_pvtkWidget);
    this->setLayout(mainLayout);




    //------------ callback -------------//
    //create an object of the MouseCallback class
    vtkSmartPointer<MouseCallback> obj_MouseCallback =
            vtkSmartPointer<MouseCallback>::New();

    obj_MouseCallback->SetRenderer(m_pvtkRenderer);
    obj_MouseCallback->SetActor(m_pvtkSurfaceActor);
    obj_MouseCallback->SetAssembly(m_pvtkAssembly1);
    //        m_pvtkInteractorReg->AddObserver(vtkCommand::LeftButtonPressEvent,obj_MouseCallback);

    //    m_pvtkRenderer->AddActor(m_pvtkAssembly1);

    /// rupika added
    root = vtkSmartPointer<vtkXMLDataElement>::New();
    root->SetName("PatientPoints");

    loadStlTool();
    //onCheckpointClicked();

    vtkCamera* camera = m_pvtkRenderer->GetActiveCamera();
    camera->GetPosition(initialPosition);
    camera->GetFocalPoint(initialFocalPoint);
    camera->GetViewUp(initialViewUp);


    connect(m_objHipCenterApi->m_objHipCenterApiPoints, &hipcenterapipoints::signalErrorHip,
            this, &RegImplementation::slotErrorHip);
    connect(m_objHipCenterApi->m_objHipCenterApiPoints, &hipcenterapipoints::signalMarkerPositionHip,
            this, &RegImplementation::slotMarkerPositionHip);
    connect(m_objHipCenterApi->m_objHipCenterApiPoints, &hipcenterapipoints::signalHipCenterDone,
            this, &RegImplementation::slotHipCenterDone);

    timerHip = new QTimer(this);
    connect(timerHip, &QTimer::timeout, this, &RegImplementation::executeHipCollection);

    // for surface // rupika
    connect(this, &RegImplementation::signalDrawBoundingBox, this, &RegImplementation::drawBB);

    timerSurface = new QTimer(this);
    connect(timerSurface, &QTimer::timeout, this, &RegImplementation::executeSurfaceCollection);

    connect(&objjsonOtherData.regdata, &registerDataCollected::signalRefSpaceCoordsFemur, this, &RegImplementation::slotRefSpaceCoords_Femur);
    connect(&objjsonOtherData.regdata, &registerDataCollected::signalRefSpaceCoordsTibia, this, &RegImplementation::slotRefSpaceCoords_Tibia);

    connect(this, &RegImplementation::signalToolLocation, this, &RegImplementation::slotToolLocation);

    matrixICP->Identity(); // Start with an identity matrix (replace with actual values if necessary)

    matrixICP->SetElement(0, 0, 1.0);
    matrixICP->SetElement(0, 1, 0.0);
    matrixICP->SetElement(0, 2, 0.0);
    matrixICP->SetElement(0, 3, 0.0); // Translation along X
    matrixICP->SetElement(1, 0, 0.0);
    matrixICP->SetElement(1, 1, 1.0);
    matrixICP->SetElement(1, 2, 0.0);
    matrixICP->SetElement(1, 3, 0.0); // Translation along Y
    matrixICP->SetElement(2, 0, 0.0);
    matrixICP->SetElement(2, 1, 0.0);
    matrixICP->SetElement(2, 2, 1.0);
    matrixICP->SetElement(2, 3, 0.0); // Translation along Z
    matrixICP->SetElement(3, 0, 0.0);
    matrixICP->SetElement(3, 1, 0.0);
    matrixICP->SetElement(3, 2, 0.0);
    matrixICP->SetElement(3, 3, 1.0);

    //    connect(&objjsonOtherData.regdata, &registerDataCollected::signalToolOrientFemur, this, &RegistrationUI::slotToolOrientFemur);
    //    connect(&objjsonOtherData.regdata, &registerDataCollected::signalToolOrientTibia, this, &RegistrationUI::slotToolOrientTibia);

    objrestAPIController= new restAPIController;

    //(moved to reg interface class)
    //        connect(objrestAPIController->m_objjsondatafetchworker->objcameraData, &cameraData::signalTrackTool,
    //                m_objVerificationUi, &verificationui::setNewCoordOrientRefSpace);
    //        connect(objrestAPIController->m_objjsondatafetchworker->objcameraData,&cameraData::refmarkerCoordMat,
    //                m_objVerificationUi, &verificationui::setstltoRef);

//    connect(objrestAPIController->m_objjsondatafetchworker->objcameraData, &cameraData::signalTrackTool,
//            this, &RegImplementation::slotToolOrientFemur);


}

void RegImplementation::thumbnailSelected(QString from, QString item, int landmarkIndex)
{
    qDebug()<<"Obtained thumbnail Selection index"<<from<<item<<landmarkIndex;

    m_landmarkIndex = landmarkIndex;

    if (m_windowID==0)
    {
        m_regUiLandmarkName = LandmarkNames[0];
    }
    else if (m_windowID==1)
    {
        m_regUiLandmarkName = LandmarkNames[m_landmarkIndex];
        onRegistrationClicked();
    }

    if (item=="V"){
        m_pvtkRenderer->RemoveAllViewProps();
        emit signalVerificationUi(m_anatomy, m_landmarkIndex);
    }

    m_pvtkWidget->GetRenderWindow()->Render();
    savePatientLandmarksToXML();
}


void RegImplementation::onCaptureClicked()
{
    qDebug()<<"onCaptureClicked in reg implemtn";
    qDebug()<<"m_landmarkIndex :"<<m_landmarkIndex;

    if(m_landmarkIndex>1&&m_landmarkIndex<9 && m_anatomy == "Femur")
    {
        qDebug()<<"onCaptureClicked Femur";
        objjsonOtherData.sendRequestOther("http://172.16.101.123:8081/GetCameraData", m_anatomy);
    }
    if(m_landmarkIndex>0&&m_landmarkIndex<7 && m_anatomy == "Tibia")
    {
        qDebug()<<"onCaptureClicked Tibia";
        objjsonOtherData.sendRequestOther("http://172.16.101.123:8081/GetCameraData", m_anatomy);
        m_annotPtsSelected.clear(); // clearing arrays before surface collection
        m_landmarkindexVec.clear();
        filtered_ptStorage.clear();
        m_ptStorage.clear();
    }
}


void RegImplementation::switchData()
{
    qDebug()<<" switching data to tibia ... ";
    //    m_qstrTibiaDcm = "D:/Robotic Surgery/POC_FIN/Build/Segmentation_batfile/output/Tibia";

    m_qstrTibiaDcm = "D:/QTProjects/TKA/Build/Segmentation_batfile/output/Tibia";


    m_REGDcmReader->SetDirectoryName(m_qstrTibiaDcm.toStdString().c_str()); // m_qstrTibiaDcm
    m_REGDcmReader->Update();

    double isoValue = -800;
    m_REGSurface->SetInputConnection(m_REGDcmReader->GetOutputPort());
    m_REGSurface->ComputeNormalsOn();
    m_REGSurface->ComputeScalarsOn();
    m_REGSurface->SetValue(0, isoValue);

    m_REGSurfaceMapper->SetInputConnection(m_REGSurface->GetOutputPort());
    m_REGSurfaceMapper->SetScalarVisibility(false);
    m_REGSurfaceMapper->Update();

    m_REGSurfaceActor->SetMapper(m_REGSurfaceMapper);
}


void RegImplementation::getLoadedDicomPath(const QString &qstrDcmFull, const QString &qstrDcmFemur, const QString qstrDcmTibia, const QString qstrselKnee)
{
    m_qstrLoadedDcm = qstrDcmFull;
    m_qstrFemurDcm = qstrDcmFemur;
    m_qstrTibiaDcm = qstrDcmTibia;

    qDebug()<<"getLoadedDicomPath in newclass"<<m_qstrLoadedDcm<<m_qstrFemurDcm<<m_qstrTibiaDcm;

    switchData_f();
}



void RegImplementation::switchData_f()
{
    qDebug()<<" switching data to femur ... ";
    //    m_qstrFemurDcm = "D:/Robotic Surgery/POC_FIN/Build/Segmentation_batfile/output/Femur";
    m_qstrFemurDcm = "D:/QTProjects/TKA/Build/Segmentation_batfile/output/Femur";

    m_REGDcmReader->SetDirectoryName(m_qstrFemurDcm.toStdString().c_str()); // m_qstrTibiaDcm
    m_REGDcmReader->Update();

    double isoValue = -800;
    m_REGSurface->SetInputConnection(m_REGDcmReader->GetOutputPort());
    m_REGSurface->ComputeNormalsOn();
    m_REGSurface->ComputeScalarsOn();
    m_REGSurface->SetValue(0, isoValue);

    m_REGSurfaceMapper->SetInputConnection(m_REGSurface->GetOutputPort());
    m_REGSurfaceMapper->SetScalarVisibility(false);
    m_REGSurfaceMapper->Update();

    m_REGSurfaceActor->SetMapper(m_REGSurfaceMapper);
}

void RegImplementation::getLoadedStlPath(/*const QString &qstrStlFull,*/ const QString &qstrStlFemur, const QString qstrStlTibia)
{
    //m_qstrLoadedStl = qstrStlFull; //full knee
    m_qstrFemurStl = qstrStlFemur;
    m_qstrTibiaStl = qstrStlTibia;
    qDebug()<<"getLoadedStlPath in RegImplementation"<</*m_qstrLoadedStl<<*/m_qstrFemurStl<<m_qstrTibiaStl;

}

QStringList RegImplementation::readLandmarkNamesFromFile(const QString &filePath)
{
    QStringList landmarkNames;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            landmarkNames.append(in.readLine().trimmed());
        }
        file.close();
    } else {
        qDebug() << "Failed to open file:" << filePath;
    }
    return landmarkNames;
}

void RegImplementation::executeSurfaceCollection()
{
    //    qDebug()<<"executing surgace ";
    objjsonOtherData.sendRequestOther("http://172.16.101.123:8081/GetCameraData", m_anatomy);
}


void RegImplementation::drawBB(std::vector<int> m_landmarkindexVec, std::vector<std::array<double, 3>> m_annotPtsSelected)
{
    qDebug()<<" draw bounding box function "<<m_landmarkIndex<<m_anatomy<<m_windowID<<m_regUiLandmarkName;

    std::vector<std::array<double, 3>> bbSizeArray = {
        {40, 80, 10},   // fmr srf 1
        {40, 80, 10},   // fmr srf 2
        {50, 20, 50},   // fmr srf 3
        {50, 20, 50},   // fmr srf 4
        {50, 20, 50},  // fmr srf 5
        {40, 80, 5},   // tb srf 1
        {40, 80, 5},   // tb srf 2
        {50, 20, 50}   // tb srf 3
    };

    vtkSmartPointer<vtkClipPolyData> clipper = vtkSmartPointer<vtkClipPolyData>::New();

    vtkSmartPointer<vtkImplicitBoolean> combinedBB = vtkSmartPointer<vtkImplicitBoolean>::New();
    combinedBB->SetOperationTypeToUnion(); // OR operation

    for (size_t i = 0; i < m_landmarkindexVec.size(); ++i)
    {
        int index = m_landmarkindexVec[i];
        //        qDebug() << "Landmark indices clicked so far: " << index;

        const auto& point = m_annotPtsSelected[i];
        //        qDebug() << "Annotation point for surface registration: " << point[0] << point[1] << point[2];

        vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();

        // Get sizes from bbSizeArray based on the index
        double xLength = bbSizeArray[index][0];
        double yLength = bbSizeArray[index][1];
        double zLength = bbSizeArray[index][2];

        cubeSource->SetCenter(point[0], point[1], point[2]);
        cubeSource->SetXLength(xLength);
        cubeSource->SetYLength(yLength);
        cubeSource->SetZLength(zLength);
        cubeSource->Update();

        double boundsbb[6];
        cubeSource->GetBounds(boundsbb);

        vtkSmartPointer<vtkBox> cubebb = vtkSmartPointer<vtkBox>::New();
        cubebb->SetBounds(boundsbb);

        combinedBB->AddFunction(cubebb);
    }

    // Clip the polydata using vtkClipPolyData
    clipper->SetInputData(m_REGSurface->GetOutput());
    clipper->SetClipFunction(combinedBB);
    clipper->InsideOutOn();
    clipper->Update();

    vtkSmartPointer<vtkPolyData> m_imgPolydata = vtkSmartPointer<vtkPolyData>::New();
    m_imgPolydata = clipper->GetOutput();

    //    qDebug()<<" checking vals 0 "<<m_imgPolydata->GetNumberOfPoints();

    m_imgPolydataAll->DeepCopy(m_imgPolydata);
    qDebug()<<"drawBB:: number of points in image polydata data "<<m_imgPolydataAll->GetNumberOfPoints();

    /// visualise clipped bone surface
    clippedMapper->SetInputData(m_imgPolydata);
    clippedActor->SetMapper(clippedMapper);
    clippedActor->GetProperty()->SetColor(0, 0, 1);

    m_pvtkRenderer->AddActor(clippedActor);

}


void RegImplementation::calculateRMSE(double testPoint[3], double toolLoc[3])
{
    /// rmse calculation
    double diffX = testPoint[0] - toolLoc[0];
    double diffY = testPoint[1] - toolLoc[1];
    double diffZ = testPoint[2] - toolLoc[2];
    double squaredError = diffX * diffX + diffY * diffY + diffZ * diffZ;
    double rmse = std::sqrt(squaredError / 3.0);

    //    qDebug() << " RMSE: " << rmse;
    textAct = QString(" RMSE: %1\n").arg(rmse);
    rmseTextActor->SetInput(textAct.toStdString().c_str());
    rmseTextActor->GetTextProperty()->SetFontSize(24);
    rmseTextActor->GetTextProperty()->SetFontFamilyToArial();
    rmseTextActor->GetTextProperty()->BoldOn();
    rmseTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    rmseTextActor->GetPositionCoordinate()->SetValue(0.5, 0.9);   // Set text position in the window (pixels)
    m_pvtkRenderer->AddActor2D(rmseTextActor);
    /// done

}


void RegImplementation::onCapturePressed()
{
    qDebug()<<" capture button pressed ";

    if (m_landmarkIndex == 1 && m_anatomy == "Femur"){
        qDebug()<<" hip timer start ";
        timerHip->start(25); // was 100
    }
    else if(m_landmarkIndex > 8 && m_anatomy == "Femur")
    {
        icpComputed = false;
        m_isCapturing = true;  // Start capturing points
        m_ptStorage.clear(); //-----------------------------// clear stored points if needed
    }
    else if (m_landmarkIndex > 6 && "Tibia")
    {
        icpComputed = false;
        m_isCapturing = true;  // Start capturing points
        m_ptStorage.clear(); //-----------------------------// clear stored points if needed
    }
}

void RegImplementation::onCaptureReleased()
{
    qDebug()<<" capture button released ";

    if (m_landmarkIndex == 1 && m_anatomy == "Femur"){
        timerHip->stop();
    }

    else if(m_landmarkIndex > 8 && m_landmarkIndex < 13 && m_anatomy == "Femur")
    {
        m_isCapturing = false; // Stop capturing points
        pointCloudTransformation();
    }
    else if (m_landmarkIndex > 6 && m_anatomy == "Tibia"){
        m_isCapturing = false; // Stop capturing points
        pointCloudTransformation();
    }
}

void RegImplementation::noiseFiltering(std::vector<std::array<double, 3>> m_ptStorage)
{
    // Parameters for radius-based filtering
    double radius = 5.0;     // desired radius
    int minNeighbors = 5;    // Minimum number of neighbors within the radius to keep a point

    vtkSmartPointer<vtkPoints> m_surfPts = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> m_surfPolydata = vtkSmartPointer<vtkPolyData>::New();
    for (const auto& pt : m_ptStorage)
    {
        m_surfPts->InsertNextPoint(pt[0], pt[1], pt[2]);
    }
    m_surfPolydata->SetPoints(m_surfPts);

    // Create a vtkPointLocator and build the locator
    auto pointLocator = vtkSmartPointer<vtkPointLocator>::New();
    pointLocator->SetDataSet(m_surfPolydata);
    pointLocator->BuildLocator();

    qDebug() << "Number of stored points: before filtering" << filtered_ptStorage.size();

    // Perform radius-based filtering
    for (vtkIdType i = 0; i < m_surfPolydata->GetNumberOfPoints(); ++i) {
        auto neighbors = vtkSmartPointer<vtkIdList>::New();
        pointLocator->FindPointsWithinRadius(radius, m_surfPolydata->GetPoint(i), neighbors);

        // Check if the point has enough neighbors to be considered non-noisy
        if (neighbors->GetNumberOfIds() >= minNeighbors) {
            // Add the point to the filtered array
            std::array<double, 3> point;
            m_surfPolydata->GetPoint(i, point.data());
            filtered_ptStorage.push_back(point);
        }
    }

    qDebug() << "Number of stored points: after filtering " << filtered_ptStorage.size();
}

void RegImplementation::pointCloudTransformation()
{
    noiseFiltering(m_ptStorage);

    //    qDebug()<<" transforming pointclouds ";
    //    qDebug() << "Number of stored points in filtered_ptStorage:" << filtered_ptStorage.size();

    /// collected points from patient space
    vtkSmartPointer<vtkPoints> m_surfPtsFiltered = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> m_surfPolydataFiltered = vtkSmartPointer<vtkPolyData>::New();
    for (const auto& pt : filtered_ptStorage)
    {
        m_surfPtsFiltered->InsertNextPoint(pt[0], pt[1], pt[2]);
    }
    m_surfPolydataFiltered->SetPoints(m_surfPtsFiltered);

    qDebug()<<" number of points in surface data "<<m_surfPolydataFiltered->GetNumberOfPoints();
    qDebug()<<" number of points in image space "<<m_imgPolydataAll->GetNumberOfPoints();

    /// icp transformation
    vtkSmartPointer<vtkIterativeClosestPointTransform> icp = vtkSmartPointer<vtkIterativeClosestPointTransform>::New();
    icp->SetSource(m_surfPolydataFiltered); // source
    icp->SetTarget(m_imgPolydataAll); // target
    icp->GetLandmarkTransform()->SetModeToRigidBody(); // Can be Affine or Similarity if needed
    icp->SetMaximumNumberOfIterations(500); // Adjust based on required accuracy
    icp->StartByMatchingCentroidsOn();
    icp->SetMeanDistanceMode(0);
    icp->SetCheckMeanDistance(true);
    icp->Modified();
    icp->Update();

    qDebug()<<" icp done in "<<icp->GetNumberOfIterations()<<" iterations";
    qDebug()<<" icp mean distance is "<<icp->GetMeanDistance();

    /// transform each matrix
    matrixICP = icp->GetMatrix();

    m_pvtkRenderer->GetRenderWindow()->Render();
}


void RegImplementation::slotRefSpaceCoords_Femur(Eigen::Vector4d pt)
{
    Eigen::Vector4d transformedHomogenousPoint = trasnformationmatrix_point_femur * pt;

    Eigen::Vector3d transformedPointToolLoc(
                transformedHomogenousPoint.x() / transformedHomogenousPoint.w(),
                transformedHomogenousPoint.y() / transformedHomogenousPoint.w(),
                transformedHomogenousPoint.z() / transformedHomogenousPoint.w());

    double m_refCoordPt[3];
    m_refCoordPt[0] = transformedPointToolLoc.x();
    m_refCoordPt[1] = transformedPointToolLoc.y();
    m_refCoordPt[2] = transformedPointToolLoc.z();

    if(m_landmarkIndex >8){
        emit signalToolLocation(m_refCoordPt);
    }
}

void RegImplementation::slotRefSpaceCoords_Tibia(Eigen::Vector4d pt)
{
    //    qDebug()<<" tibia locations recieved in slot "<<pt[0]<<pt[1]<<pt[2];

    Eigen::Vector4d transformedHomogenousPoint_t = trasnformationmatrix_point_tibia * pt;

    Eigen::Vector3d transformedPointToolLoc_t(
                transformedHomogenousPoint_t.x() / transformedHomogenousPoint_t.w(),
                transformedHomogenousPoint_t.y() / transformedHomogenousPoint_t.w(),
                transformedHomogenousPoint_t.z() / transformedHomogenousPoint_t.w()
                );

    double m_refCoordPt_t[3];
    m_refCoordPt_t[0] = transformedPointToolLoc_t.x();
    m_refCoordPt_t[1] = transformedPointToolLoc_t.y();
    m_refCoordPt_t[2] = transformedPointToolLoc_t.z();

    if(m_landmarkIndex > 6){
        emit signalToolLocation(m_refCoordPt_t);
    }
}

void RegImplementation::slotToolOrientFemur(vtkSmartPointer<vtkTransform> tf_femur,Eigen::Matrix4d m)
{
    vtkTransformToolFemur->RotateZ(90.0);
    vtkTransformToolFemur->SetMatrix(tf_femur->GetMatrix());
    m_stlActorTool->SetUserTransform(vtkTransformToolFemur);
    m_pvtkRenderer->GetRenderWindow()->Render();
}

void RegImplementation::slotToolOrientTibia(Eigen::Matrix4d cam2ref_tf_tibia)
{
    //    qDebug()<<" tool orientation in tibia slot ";

    //    vtkSmartPointer<vtkTransform> vtkTransformTooltibia = vtkSmartPointer<vtkTransform>::New();
    //    vtkSmartPointer<vtkMatrix4x4> newVtkMatrixT = vtkSmartPointer<vtkMatrix4x4>::New();

    //    newVtkMatrixT->Identity();
    //    for (int i = 0; i < 4; ++i)
    //    {
    //        for (int j = 0; j < 4; ++j)
    //        {
    //            newVtkMatrixT->SetElement(i, j, cam2ref_tf_tibia(i, j));
    //        }
    //    }

    //    vtkTransformTooltibia->RotateZ(90.0);
    //    vtkTransformTooltibia->SetMatrix(newVtkMatrixT);

    //    m_pvtkRenderer->GetRenderWindow()->Render();
}



void RegImplementation::slotToolLocation(double pt[3])
{
    vtkSmartPointer<vtkTransform> transfrmPts = vtkSmartPointer<vtkTransform>::New();
    transfrmPts->SetMatrix(matrixICP);
    transfrmPts->TransformPoint(pt, m_toolLocation);

    double tpos[3];
    m_stlActorTool->GetPosition(tpos);
    qDebug()<<" tposition of tool"<<tpos[0]<<tpos[1]<<tpos[2];
    qDebug()<<" actual loc "<<m_toolLocation[0]<<m_toolLocation[1]<<m_toolLocation[2];

    //    ts->SetCenter(m_toolLocation);
    //    ts->SetRadius(4);
    //    tsm->SetInputConnection(ts->GetOutputPort());
    //    tsa->SetMapper(tsm);
    //    tsa->GetProperty()->SetColor(0, 0.0, 1.0);  // color
    //    m_pvtkRenderer->AddActor(tsa);

    calculateRMSE(m_regAnnotationPt, m_toolLocation);

    if (m_isCapturing) {
        m_ptStorage.push_back({m_toolLocation[0], m_toolLocation[1], m_toolLocation[2]}); // m_toolLocation

        /// show points
        vtkSmartPointer<vtkSphereSource> m_surfPt = vtkSmartPointer<vtkSphereSource>::New();
        vtkSmartPointer<vtkPolyDataMapper> m_surfPtMap = vtkSmartPointer<vtkPolyDataMapper>::New();

        m_surfPt->SetCenter(m_toolLocation);
        m_surfPt->SetRadius(1.5);
        m_surfPtMap->SetInputConnection(m_surfPt->GetOutputPort());

        vtkSmartPointer <vtkActor> m_surfPtAct =  vtkSmartPointer <vtkActor>::New();
        m_surfPtAct->SetMapper(m_surfPtMap);
        m_surfPtAct->GetProperty()->SetColor(1, 0.6, 0.6);  // color

        m_pvtkRenderer->AddActor(m_surfPtAct);
    }

    m_pvtkRenderer->GetRenderWindow()->Render();

}


void RegImplementation::onCheckpointClicked()
{
    qDebug()<<" checkpoint window clicked ";
    m_pvtkRenderer->RemoveActor(hipCenterGridassembly);
    m_pvtkRenderer->RemoveActor(m_REGSurfaceActor);
    m_pvtkRenderer->RemoveActor(floorActor);
    m_pvtkRenderer->RemoveActor(fillActor);
    m_pvtkRenderer->RemoveActor(lndmrk_sphereActor);
    m_pvtkRenderer->RemoveActor(m_stlActorTool);
    m_pvtkRenderer->RemoveActor(clippedActor);
    m_pvtkRenderer->RemoveActor(rmseTextActor);
    m_pvtkRenderer->RemoveActor(greenCircle);


    // load stl
    if (m_anatomy=="Femur"){
        qDebug()<<"checkpoint:: loading femur stl ";
        stlFilePath = QDir::currentPath()+"/Plan/Viewer/Human_femur.stl";
    }
    else {
        qDebug()<<"checkpoint:: loading tibia stl";
        stlFilePath = QDir::currentPath()+"/Plan/Viewer/Human_tibia.stl";
    }

    vtkSmartPointer<vtkSTLReader> stlReader = vtkSmartPointer<vtkSTLReader>::New();
    stlReader->SetFileName(stlFilePath.toUtf8().constData());
    stlReader->Update();

    vtkNew<vtkTransform> transform;
    transform->RotateX(0); // femur 180

    vtkNew<vtkTransformPolyDataFilter> transformFilter;
    transformFilter->SetTransform(transform);
    transformFilter->SetInputConnection(stlReader->GetOutputPort());
    transformFilter->Update();

    vtkSmartPointer<vtkPolyDataMapper> boneStlMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    boneStlMapper->SetInputConnection(transformFilter->GetOutputPort());
    boneStlActor->SetMapper(boneStlMapper);

    m_pvtkRenderer->AddActor(boneStlActor);

    //annotation actor to signify Lateral(right)/Medial(left of the screen)
    actorL->SetInput("L");
    actorM->SetInput("M");

    //actorL->SetTextScaleMode(8);
    //actorL->SetDisplayPosition(0,155);
    actorL->GetTextProperty()->SetFontSize(24);
    actorL->GetTextProperty()->SetFontFamilyAsString("Inter");
    actorL->GetTextProperty()->BoldOn();
    actorL->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

    actorM->GetTextProperty()->SetFontSize(24);
    actorM->GetTextProperty()->SetFontFamilyAsString("Inter");
    actorM->GetTextProperty()->BoldOn();
    actorM->GetTextProperty()->SetColor(51.0 / 255.0, 51.0 / 255.0, 51.0 / 255.0); //#333333;

    actorM->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    actorM->GetPositionCoordinate()->SetValue(0.03, 0.5);
    actorL->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    actorL->GetPositionCoordinate()->SetValue(0.97, 0.5);

    m_pvtkRenderer->AddActor(actorL);
    m_pvtkRenderer->AddActor(actorM);

    m_openGlRenWin->AddRenderer(m_pvtkRenderer);
    m_pvtkRenderer->GlobalWarningDisplayOff();
    m_pvtkRenderer->ResetCamera();
    m_openGlRenWin->Render();

    m_pvtkInteractorReg->ReInitialize();
    //    m_pvtkRenderer->GetRenderWindow()->Render();

}

void RegImplementation::landmarkCollection(QString m_regUiLandmarkName)
{
    qDebug()<<"VISUALISING ANNOTATED POINT FOR "<<m_regUiLandmarkName;

    QString savedSTLpts;
    QVector<QVector3D> savedPts;
    lndmrk_sphere->SetRadius(5);
    lndmrk_sphere->SetThetaResolution(10);
    lndmrk_sphere->SetPhiResolution(10);

    // read xml file
    QString filePath = QDir::currentPath() + "/Landmark.xml";
    annotationPoints = parseXMLFile(filePath);

    for (const auto& point : annotationPoints)
    {
        if (point.anatomy == m_regUiLandmarkName) { // Compare anatomy with anatomyName
            std::cout << "MATCHED :: Anatomy: " << point.anatomy.toStdString()
                      << ", X: " << point.x
                      << ", Y: " << point.y
                      << ", Z: " << point.z << std::endl;
            m_regAnnotationPt[0] = point.x;
            m_regAnnotationPt[1] = point.y;
            m_regAnnotationPt[2] = point.z;
        }
    }

    lndmrk_sphere->SetCenter(m_regAnnotationPt);
    lndmrk_sphere->Update();
    lndmrk_sphereMapper->SetInputConnection(lndmrk_sphere->GetOutputPort());
    lndmrk_sphereActor->SetMapper(lndmrk_sphereMapper);
    lndmrk_sphereActor->GetProperty()->SetColor(0,1,0);
    //    m_pvtkRenderer->AddActor(lndmrk_sphereActor);

    m_pvtkRenderer->GetActiveCamera()->SetFocalPoint(m_regAnnotationPt);
    m_pvtkRenderer->GetActiveCamera()->Elevation(45);
    m_pvtkRenderer->ResetCameraClippingRange();

}

void RegImplementation::slotMarkerPositionHip(const QList<double> &markerPosition)
{
    //    qDebug()<<" slot hip recieved "<<markerPosition[0]<<markerPosition[1]<<markerPosition[2];

    if (!m_isFirstValueReceived) {
        m_firstPositionHip = markerPosition;  // Save the first position
        m_isFirstValueReceived = true;     // Set the flag
        qDebug() << "First position saved:" << m_firstPositionHip;
    }

    m_hipMarkerPos[0] = m_firstPositionHip[0] - markerPosition[0];
    m_hipMarkerPos[1] = m_firstPositionHip[1] - markerPosition[1];
    m_hipMarkerPos[2] = m_firstPositionHip[2] - markerPosition[2];

    /// polar coords testing
    double x = m_hipMarkerPos[0];
    double y = m_hipMarkerPos[1];
    double z = m_hipMarkerPos[2];

    vtkSmartPointer<vtkPoints> newPoint = vtkSmartPointer<vtkPoints>::New();
    newPoint->InsertNextPoint(x, y, z);

    // Append the newPoint to the vector of vtkPoints
    markerPtsFromHipApi.push_back(newPoint);

    vtkSmartPointer<vtkSphereSource> m_hipMarkerSph2 = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> m_hipMarkerMapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();

    m_hipMarkerSph2->SetCenter(z, -x, 0); // cartesian coords ///x,z,0
    m_hipMarkerSph2->SetRadius(3);
    m_hipMarkerMapper2->SetInputConnection(m_hipMarkerSph2->GetOutputPort());

    colorHipCenterpoint(z,-x,0);

    vtkSmartPointer <vtkActor> m_hipMarkerActor2 =  vtkSmartPointer <vtkActor>::New();
    m_hipMarkerActor2->SetMapper(m_hipMarkerMapper2);
    m_hipMarkerActor2->GetProperty()->SetColor(1.0, 0.0, 0.0);  // Red color

    m_pvtkRenderer->AddActor(m_hipMarkerActor2);

    m_pvtkRenderer->GetRenderWindow()->Render();
}

void RegImplementation::slotHipCenterDone(const QList<double> &hipcenter)
{
    qDebug()<<" slot hip center location recieved in newclass.cpp"<<hipcenter;
}

// Define a member variable in the class to store the circle actors
void RegImplementation::drawHipCenterUI()
{

    /*******Structured Grid with different cell color *********************/ //parvathy
    const int numSegments = 16;
    const int radius = 200;

    // Create the circles and store them in the circleActors list
    vtkSmartPointer<vtkRegularPolygonSource> circle2 = vtkSmartPointer<vtkRegularPolygonSource>::New();
    circle2->SetNumberOfSides(numSegments);
    circle2->SetRadius(radius-100);
    circle2->SetCenter(0.0, 0.0, 0.0);
    circle2->Update();

    vtkSmartPointer<vtkPolyDataMapper> mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper2->SetInputConnection(circle2->GetOutputPort());

    greenCircle->SetMapper(mapper2);
    greenCircle->GetProperty()->SetColor(0.2,0.2,0.2);
    greenCircle->GetProperty()->SetLineWidth(3);
    greenCircle->GetProperty()->SetEdgeColor(0.0, 1.0, 0.0); // Green line
    greenCircle->GetProperty()->EdgeVisibilityOn(); // Ensure edges are visible

    int radialDivisions = 16;    // Number of radial divisions 4, 16 ok
    int angularDivisions = 16;   // Number of angular divisions 16
    double maxRadius = 250.0;     // Maximum radius of the grid
    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    vtkSmartPointer<vtkStructuredGrid> structuredGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    structuredGrid->SetDimensions(radialDivisions + 1, 5, 1);

    for (int r = 0; r <= radialDivisions; ++r)
    {
        int circleRadius = radius - r * 50;
        for (int a = 0; a <= angularDivisions; ++a)
        {
            double angle = 2.0 * vtkMath::Pi() * double(a) / angularDivisions;
            double x = circleRadius * cos(angle);
            double y = circleRadius * sin(angle);
            double z = 0.0;

            points->InsertNextPoint(x, y, z);
        }
    }

    structuredGrid->SetPoints(points);


    vtkNew<vtkNamedColors> colors;
    size_t nx = 2, ny = 3, nz = 2;

    //Give values to cell whose color needs to be changed according to LUT

    auto numberOfCells =structuredGrid->GetNumberOfCells();

    cellValues->SetNumberOfTuples(structuredGrid->GetNumberOfCells());

    for (size_t i = 0; i < numberOfCells; ++i)
    {
        cellValues->SetValue(i,0);
    }

    // cellValues->SetValue(20, 20);//test

    // Create a grid
    structuredGrid->GetCellData()->SetScalars(cellValues);


    // Create a cell locator to find the cell containing the point
    cellLocator->SetDataSet(structuredGrid);
    cellLocator->BuildLocator();  //

    // Use the cell data

    lut->SetNumberOfTableValues(numberOfCells);
    lut->Build();
    // Assign some specific colors in this case
    lut->SetTableValue(0, 0.2, 0.2, 0.2);//set fill color Grey
    lut->SetTableValue(20, colors->GetColor4d("Yellow").GetData());// cell with value 20 takes yellow color

    // Create a geometry filter to convert the structured grid into a polydata
    vtkSmartPointer<vtkStructuredGridGeometryFilter> geometryFilter = vtkSmartPointer<vtkStructuredGridGeometryFilter>::New();
    geometryFilter->SetInputData(structuredGrid);
    geometryFilter->Update();

    vtkNew<vtkPolyDataMapper> floorMapper;
    floorMapper->SetInputConnection(geometryFilter->GetOutputPort());
    floorMapper->SetLookupTable(lut);
    floorMapper->SetScalarRange(0, numberOfCells - 1);

    // fill grid
    fillActor->SetMapper(floorMapper);
    fillActor->SetPosition(0,0,0);
    fillActor->GetProperty()->SetRepresentationToSurface(); // Set representation to surface
    fillActor->GetProperty()->SetEdgeColor(0.0, 0.0, 0.0);
    fillActor->GetProperty()->EdgeVisibilityOn(); // Ensure edges are visible


    m_pvtkRenderer->AddActor(greenCircle);
    m_pvtkRenderer->AddActor(fillActor);

    m_pvtkRenderer->GetRenderWindow()->Render();


    //anagha added
    qDebug()<<" end of drawing hip center ui";
}

void RegImplementation::colorHipCenterpoint(double x, double y, double z)
{
    qDebug()<<" color hip fn false";

    if (m_isFirstValueReceived){
        qDebug()<<" color hip fn";
        double point[3] = { x, y,z };
        vtkIdType cellId = cellLocator->FindCell(point);

        // Set a value to that cell (for example, setting the value to 100.0)
        if (cellId != -1) {  // Ensure the cell is valid
            cellValues->SetValue(cellId, 20);  // Assign a value to the cell
            cellValues->Modified();
        }
        m_pvtkRenderer->GetRenderWindow()->Render();
    }

}

void RegImplementation::showMarkers()
{
    qDebug()<<" to show markers on right window";
}


void RegImplementation::writeCoordinatesToFile( double m_regAnnotationPt[3])
{
    qDebug()<<" write coords to file "<<m_regAnnotationPt[0]<<m_regAnnotationPt[1]<<m_regAnnotationPt[2];
    QString filepath_loc;
    if(m_anatomy=="Femur")
        filepath_loc= QDir::currentPath()+"/RegistrationFiles/" +"imagespace_coord_femur.txt";
    else if (m_anatomy=="Tibia") {
        filepath_loc= QDir::currentPath()+"/RegistrationFiles/" +"imagespace_coord_tibia.txt";
    }

    static bool firstCall = true; // Static flag to check if this is the first call

    QFile fileIp(filepath_loc);

    // Open the file in the desired mode
    QIODevice::OpenMode mode = firstCall ? (QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)
                                         : (QIODevice::Append | QIODevice::Text);

    firstCall = false; // Set to false after the first call

    if (!fileIp.open(mode)) {
        qDebug() << "Unable to open file for writing";
        return;
    }


    // Create a QTextStream to write to the file
    QTextStream out(&fileIp);

    // Write each coordinate (x, y, z) on a new line
    out << m_regAnnotationPt[0] << "\n";  // Write x
    out << m_regAnnotationPt[1] << "\n";  // Write y
    out << m_regAnnotationPt[2] << "\n";  // Write z

    // Close the file
    fileIp.close();

    qDebug() << "Coordinates written to file successfully.";
}




void RegImplementation::onRegistrationClicked()
{
    //    m_pvtkRenderer->ResetCamera(); //a added


    m_pvtkRenderer->GetActiveCamera()->SetPosition(initialPosition);
    m_pvtkRenderer->GetActiveCamera()->SetFocalPoint(initialFocalPoint);
    m_pvtkRenderer->GetActiveCamera()->SetViewUp(initialViewUp);

    m_pvtkRenderer->RemoveActor(m_stlActorTool);
    m_pvtkRenderer->RemoveActor(clippedActor);
    m_pvtkRenderer->RemoveActor(boneStlActor);
    m_pvtkRenderer->RemoveActor(lndmrk_sphereActor);
    m_pvtkRenderer->RemoveActor(fillActor);
    m_pvtkRenderer->RemoveActor(hipCenterGridassembly);
    m_pvtkRenderer->RemoveActor(greenCircle);

    objrestAPIController->m_objjsondatafetchworker->objcameraData->m_qstrAnatomy = m_anatomy;

    if (m_anatomy == "Femur"){

        objregTransformation.setQstrAnatomy(m_anatomy);

        qDebug()<<"onRegistrationClicked:: window id = "<<m_windowID<<" antomy name = "<<m_anatomy<<" landmark number "<<m_landmarkIndex<<" landmark name ="<<m_regUiLandmarkName;

        if (m_landmarkIndex == 1)
        {
            m_pvtkRenderer->RemoveActor(m_REGSurfaceActor);

            qDebug()<<" LOADING HIP CENTER CALCULATION WINDOW ";

            /// DRAWING CIRCLES AND DIVISIONS
            drawHipCenterUI();
            //            colorHipCenterpoint(100,-100,0);

            m_pvtkRenderer->AddActor(hipCenterGridassembly);

        }else if(m_landmarkIndex >1 &&m_landmarkIndex <5)
        {
            qDebug()<<" LOADING point ANNOTATION BONE 2 - 4";


            m_pvtkRenderer->AddActor(m_REGSurfaceActor);
            landmarkCollection(m_regUiLandmarkName);
            m_pvtkRenderer->AddActor(lndmrk_sphereActor);

            qDebug()<<"LANDMARK POINT : "<<m_regAnnotationPt[0]<<m_regAnnotationPt[1]<<m_regAnnotationPt[2];

            if(m_landmarkIndex==1&&boolnotdoneOne)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneOne=false;
            }

            else if(m_landmarkIndex==2&&boolnotdoneTwo)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneTwo=false;
            }
            else if(m_landmarkIndex==3&&boolnotdoneThree)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneThree=false;
            }
            else if(m_landmarkIndex==4&&boolnotdoneFour)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneFour=false;
            }

        }
        else if(m_landmarkIndex >4 &&m_landmarkIndex <9)
        {
            qDebug()<<" LOADING point ANNOTATION BONE 5-8"<<m_landmarkIndex;
            objregTransformation.rigiTransform();


            m_pvtkRenderer->AddActor(m_REGSurfaceActor);
            landmarkCollection(m_regUiLandmarkName);
            m_pvtkRenderer->AddActor(lndmrk_sphereActor);

            qDebug()<<"LANDMARK POINT5-8 : "<<m_regAnnotationPt[0]<<m_regAnnotationPt[1]<<m_regAnnotationPt[2];
            if(m_landmarkIndex==5&&boolnotdoneFive)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneFive=false;
            }
            if(m_landmarkIndex==6&&boolnotdoneSix)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneSix=false;
            }
            if(m_landmarkIndex==7&&boolnotdoneSeven)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneSeven=false;
            }
            if(m_landmarkIndex==8&&boolnotdoneEight)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolnotdoneEight=false;
            }
        }

        else if(m_landmarkIndex > 8) {


            loadStlTool();
            readPointBasedTransformationMatrixFemur();
            objrestAPIController->InitializedataFetchFromRestAPI();


            qDebug()<<" loading surface rendering testing .... ";

            timerSurface->start(10); // 50 ok

            m_pvtkRenderer->AddActor(m_REGSurfaceActor);
            landmarkCollection(m_regUiLandmarkName);
            m_pvtkRenderer->AddActor(lndmrk_sphereActor);

            std::array<double, 3> point = {m_regAnnotationPt[0], m_regAnnotationPt[1], m_regAnnotationPt[2]};
            m_annotPtsSelected.push_back(point);

            m_landmarkindexVec.push_back(m_landmarkIndex-9);
            // m_landmarkindex - 9 is done to load first row of array in bbsize array which has only 5 rows
            emit signalDrawBoundingBox(m_landmarkindexVec, m_annotPtsSelected);
        }

        else {
            qDebug()<<" no else condition ";
        }
    }


    // tibia condition
    else if (m_anatomy == "Tibia"){
        objregTransformation.setQstrAnatomy(m_anatomy);

        m_pvtkRenderer->RemoveActor(m_stlActorTool);
        m_pvtkRenderer->RemoveActor(lndmrk_sphereActor);

        if (m_landmarkIndex >0 && m_landmarkIndex <5)
        {
            timerSurface->stop();
            qDebug()<<" LOADING point ANNOTATION BONE for TIBIA" <<m_regUiLandmarkName << "index ::"<<m_landmarkIndex;

            m_pvtkRenderer->AddActor(m_REGSurfaceActor);
            landmarkCollection(m_regUiLandmarkName);
            m_pvtkRenderer->AddActor(lndmrk_sphereActor);

            qDebug()<<"LANDMARK POINT : "<<m_regAnnotationPt[0]<<m_regAnnotationPt[1]<<m_regAnnotationPt[2];

            if (m_regAnnotationPt[0] > 0){
                qDebug()<<" adjusting for now ..... change later ";

                if(m_landmarkIndex==1&&boolT1)
                {
                    writeCoordinatesToFile(m_regAnnotationPt);
                    boolT1=false;
                }
                else if(m_landmarkIndex==2&&boolT2)
                {
                    writeCoordinatesToFile(m_regAnnotationPt);
                    boolT2=false;
                }
                else if(m_landmarkIndex==3&&boolT3)
                {
                    writeCoordinatesToFile(m_regAnnotationPt);
                    boolT3=false;
                }
                else if(m_landmarkIndex==4&&boolT4)
                {
                    writeCoordinatesToFile(m_regAnnotationPt);
                    boolT4=false;
                }
            }
        }

        else if (m_landmarkIndex > 4 && m_landmarkIndex <7){

            qDebug()<<" LOADING point ANNOTATION BONE for TIBIA" <<m_regUiLandmarkName << "index ::"<<m_landmarkIndex;

            objregTransformation.rigiTransform();

            m_pvtkRenderer->AddActor(m_REGSurfaceActor);
            landmarkCollection(m_regUiLandmarkName);
            m_pvtkRenderer->AddActor(lndmrk_sphereActor);

            if(m_landmarkIndex==5&&boolT5)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolT5=false;
            }
            else if(m_landmarkIndex==6&&boolT6)
            {
                writeCoordinatesToFile(m_regAnnotationPt);
                boolT6=false;
            }
        }
        else if (m_landmarkIndex > 6) {

            qDebug()<<" testing size "<<m_annotPtsSelected.size();
            qDebug()<<" testing size 1"<<m_landmarkindexVec.size();

            loadStlTool();
            readPointBasedTransformationMatrixTibia();

            qDebug()<<" loading surface rendering testing .... ";

            timerSurface->start(50); // 50 ok

            m_pvtkRenderer->AddActor(m_REGSurfaceActor);
            landmarkCollection(m_regUiLandmarkName);

            std::array<double, 3> point = {m_regAnnotationPt[0], m_regAnnotationPt[1], m_regAnnotationPt[2]};
            m_annotPtsSelected.push_back(point);

            m_landmarkindexVec.push_back((m_landmarkIndex-7)+5);
            qDebug()<<" checking id for boundoing box"<< (m_landmarkIndex-7)+5;
            // m_landmarkindex - 9 is done to load first row of array in bbsize array which has only 5 rows
            emit signalDrawBoundingBox(m_landmarkindexVec, m_annotPtsSelected);
        }
    }


    m_pvtkRenderer->GlobalWarningDisplayOff();
    //m_pvtkRenderer->GetRenderWindow()->Render();
    m_pvtkRenderer->SetInteractive(false);
    //    m_pvtkInteractorReg->ReInitialize();



    m_pvtkRenderer->ResetCamera(); //a added

    m_openGlRenWin->Render();

    m_pvtkWidget->GetRenderWindow()->Render();

}


void RegImplementation::loadStlTool()
{
    qDebug()<<" load stl tool ";
    m_stlReaderTool = vtkSmartPointer<vtkSTLReader>::New();
    QString stlpath = QDir::currentPath()+"/Plan/Viewer/NeedleTracker.stl";

    m_stlReaderTool->SetFileName(stlpath.toStdString().c_str());
    m_stlReaderTool->Update();

    // Step 2: Create a mapper for the STL model
    m_stlMappertool = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_stlMappertool->SetInputConnection(m_stlReaderTool->GetOutputPort());

    // Step 3: Create an actor for the STL tool
    m_stlActorTool = vtkSmartPointer<vtkActor>::New();
    m_stlActorTool->SetMapper(m_stlMappertool);

    m_stlActorTool->GetProperty()->SetColor(1.0, 1.0, 0.0);  // color for the tool
    m_stlActorTool->GetProperty()->SetOpacity(0.8);
    //    m_stlActorTool->SetPosition(100.0, 200.0, 300.0);

    m_pvtkRenderer->AddActor(m_stlActorTool);
}

void RegImplementation::readPointBasedTransformationMatrixFemur()
{
    trasnformationmatrix_point_femur.Identity();
    //    cv::Mat matrix = cv::Mat::eye(4, 4, CV_64F);  // Create a 4x4 identity matrix to store the result
    QString filename=QDir::currentPath()+"/RegistrationFiles/outputtramatrix_femur.txt";
    qDebug()<<"readPointBasedTransformationMatrixFemur"<<filename;
    std::ifstream infile(filename.toStdString());

    if (!infile.is_open()) {
        std::cerr << "Error opening matrix file!" << std::endl;
        return ;
    }

    // Read the matrix values from the file
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            infile >> trasnformationmatrix_point_femur(i, j);
            if (infile.peek() == ',') infile.ignore();
        }
    }

    infile.close();
}


void RegImplementation::readPointBasedTransformationMatrixTibia()
{
    trasnformationmatrix_point_tibia.Identity();
    //    cv::Mat matrix = cv::Mat::eye(4, 4, CV_64F);  // Create a 4x4 identity matrix to store the result
    QString filenamet=QDir::currentPath()+"/RegistrationFiles/outputtramatrix_tibia.txt";
    qDebug()<<"readPointBasedTransformationMatrixFemur"<<filenamet;
    std::ifstream infile(filenamet.toStdString());

    if (!infile.is_open()) {
        std::cerr << "Error opening matrix file!" << std::endl;
        return ;
    }

    // Read the matrix values from the file
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            infile >> trasnformationmatrix_point_tibia(i, j);
            if (infile.peek() == ',') infile.ignore();
        }
    }

    infile.close();
}

void RegImplementation::executeHipCollection()
{
    /// hip center collection is done based on capture button pressed and released event
    QString apiUrlhip = "http://172.16.101.123:8081/HipCenter?data={\"ReferenceMarker\":\"435300\",\"StartDelay\":\"0\",\"MaxPoints\":\"2000\"}";
    m_objHipCenterApi->getHipUrl(apiUrlhip);
}

void RegImplementation::SaveTransformationMatrix()
{
    qDebug()<<"SaveTransformationMatrix";

    // save to file
    QString m_file1Path = QDir::currentPath() + "/RegistrationFiles/" + "transformation_matrix.txt";
    QFile file(m_file1Path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        // Write the matrix values to the file
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                out << M->GetElement(i, j) << " ";
            }
            out << "\n";
        }
        file.close();
    }
}



void RegImplementation::slotErrorHip(double error)
{
    //    qDebug()<<" slot recieved error value for hip "<<error;
    m_hipError = error;

    std::stringstream ss;
    ss << "Error:" << m_hipError;
    textActor->SetInput(ss.str().c_str());
    textActor->SetPosition( 0, 0);
    textActor->GetTextProperty()->SetFontSize(20);
    m_pvtkRenderer->AddActor2D(textActor);
    m_pvtkRenderer->GetRenderWindow()->Render();
}

void RegImplementation::startSurfaceDataCollection()
{
    //    objjsondatacameraforsurface.sendRequestOther("http://172.16.101.123:8081/GetCameraData");

}

void RegImplementation::endSurfaceDataCollection()
{

}


QVector<QVector3D> RegImplementation::readCoordinatesFromFile(const QString &filePath)
{
    QVector<QVector3D> points; // Vector to store points

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error opening file:" << file.errorString();
        return points ;
    }

    QTextStream in(&file);

    double x, y, z;
    int lineNumber = 0;

    while (!in.atEnd()) {
        QString line = in.readLine();
        bool ok;
        double value = line.toDouble(&ok);
        if (ok) {
            // Read x, y, z values
            switch (lineNumber % 3) {
            case 0:
                x = value;
                break;
            case 1:
                y = value;
                break;
            case 2:
                z = value;
                points.append(QVector3D(x, y, z));
                break;
            }
            lineNumber++;
        } else {
            qDebug() << "Invalid value encountered:" << line;
        }
    }
    file.close();
    return  points;
}

void RegImplementation::savePatientLandmarksToXML()
{
    QString cameraSpace = QDir::currentPath() + "/RegistrationFiles/" + "transformed_point.txt";
    QVector<QVector3D> cameraSpaceCoords =  readCoordinatesFromFile(cameraSpace);

    int id = 1;

    if (m_windowID==0)
    {
        landmarkPoint = cameraSpaceCoords[0];

        qDebug()<<" m_landmarkIndex ********* this should point to check point ********** "<<m_regUiLandmarkName;

    }
    else if (m_windowID==1)
    {
        landmarkPoint = cameraSpaceCoords[id]; // m_landmarkIndex
        id++; // for saving values even if landmark id is skipped

        qDebug()<<" m_landmarkIndex "<<m_regUiLandmarkName << m_landmarkIndex <<" here .. ";
    }

    int pointID = root->GetNumberOfNestedElements() + 1;
    vtkSmartPointer<vtkXMLDataElement> pointElement = vtkSmartPointer<vtkXMLDataElement>::New();
    std::string label = "Point" + std::to_string(pointID);
    pointElement->SetName(label.c_str());

    pointElement->SetAttribute("bone_name", m_anatomy.toStdString().c_str());
    pointElement->SetAttribute("landmark_name", m_regUiLandmarkName.toStdString().c_str());
    pointElement->SetDoubleAttribute("x", landmarkPoint[0]);
    pointElement->SetDoubleAttribute("y", landmarkPoint[1]);
    pointElement->SetDoubleAttribute("z", landmarkPoint[2]);

    root->AddNestedElement(pointElement);

    xmlUtilities->WriteElementToFile(root, filename.c_str());
}
