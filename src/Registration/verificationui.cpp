#include "verificationui.h"
#include "src/DataSetJSON/cameradata.h"

verificationui::verificationui(QWidget *parent) : QWidget(parent)
{


    //added by anagha
    m_openGlRenWinVerif->AddRenderer(m_verRenderer);
    m_openGlRenWinVerif->AddRenderer(m_verRendererCrossSection);

    m_verRenderer->SetViewport(0,0,1,1);
    m_verRendererCrossSection->SetViewport(0.8,0.8,1,1);
    m_verRendererCrossSection->SetBackground(0.0,0.0,0.0);

    m_pvtkWidgetVerif = new QVTKOpenGLWidget;
    m_pvtkWidgetVerif->SetRenderWindow(m_openGlRenWinVerif);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_pvtkWidgetVerif);
    this->setLayout(mainLayout);

    loadDicomData("Femur");

    planeWidget->SetInteractor(m_openGlRenWinVerif->GetInteractor());
    planeWidget->GetTexturePlaneProperty()->SetOpacity(0);
    planeWidget->SetResliceInterpolateToLinear();
    planeWidget->SetInputConnection(m_verDcmReader->GetOutputPort());
    planeWidget->SetSliceIndex(1);
    planeWidget->SetPlaneOrientation(2);
    planeWidget->DisplayTextOn();
    planeWidget->SetDefaultRenderer(m_verRenderer/*CrossSection*/);
    planeWidget->SetWindowLevel(1500, -500);
//    planeWidget->On();

    planeWidgetReslice->SetInputConnection(planeWidget->GetReslice()->GetOutputPort());
    planeWidgetReslice->Update();

    planeWidgetResliceMapper->SetInputConnection(planeWidgetReslice->GetOutputPort());
    planeWidgetResliceMapper->SetOrientation(2);
    planeWidgetResliceMapper->Update();
    planeSlice2D->SetMapper(planeWidgetResliceMapper);
    planeSlice2D->GetProperty()->SetColorLevel(-1000);
    planeSlice2D->GetProperty()->SetColorWindow(1000);
    planeSlice2D->SetPosition(0,0,0);
    m_verRendererCrossSection->AddViewProp(planeSlice2D);

    vtkCamera* camera = m_verRendererCrossSection->GetActiveCamera();
    camera->GetPosition(initialPosition);
    camera->GetFocalPoint(initialFocalPoint);
    camera->GetViewUp(initialViewUp);

    importstltool();
    //        m_stlActorTool->SetPosition(100,150,500);

    //        qDebug()<<" stl location "<<m_stlActorTool->GetPosition()[0]<<m_stlActorTool->GetPosition()[1]<<m_stlActorTool->GetPosition()[2];

    //        QVector3D coord;
    //        coord[0] = m_stlActorTool->GetPosition()[0];
    //        coord[1] = m_stlActorTool->GetPosition()[1];
    //        coord[2] = m_stlActorTool->GetPosition()[2];
    //        showCrossSection(coord);
    //        calculateRMSE(m_verAnnotationPt, coord);
}


void verificationui::getLoadedDicomPathVer(const QString &qstrDcmFull, const QString &qstrDcmFemur, const QString qstrDcmTibia, const QString qstrselKnee)
{
    QString m_fulldata = qstrDcmFull;
    m_qstrVerFemur = qstrDcmFemur;
    m_qstrVerTibia = qstrDcmTibia;
    QString selKneeSide = qstrselKnee;

    //    loadDicomData("Femur");

    qDebug()<<"getLoadedDicomPath in verificationui"<<m_qstrVerFemur<<m_qstrVerTibia;
}

void verificationui::slotToolOrientFemur(Eigen::Matrix4d  tf_femur)
{
    transformMatStlinRefEigen = tf_femur * stlEigenMatrixTool;

    vtkSmartPointer<vtkMatrix4x4> newVtkMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            newVtkMatrix->SetElement(i, j, transformMatStlinRefEigen(i, j));
        }
    }
    vtkSmartPointer<vtkTransform>   transformMatstlinRef = vtkSmartPointer<vtkTransform>::New();
    transformMatstlinRef->SetMatrix(newVtkMatrix);

    m_stlActorTool->SetUserTransform(transformMatstlinRef);
    m_verRenderer->GetRenderWindow()->Render();

    vtkMatrix4x4* matrix = m_stlActorTool->GetMatrix();

    double position[3] = {
        matrix->GetElement(0, 3),  // X position
        matrix->GetElement(1, 3),  // Y position
        matrix->GetElement(2, 3)   // Z position
    };

//    qDebug() << "STL Position from matrix:" << position[0] << position[1] << position[2];

    QVector3D coord;
    coord[0] = position[0];
    coord[1] = position[1];
    coord[2] = position[2];
    showCrossSection(coord);

    calculateRMSE(m_verAnnotationPt, coord);
}

void verificationui::slotToolOrientTibia(Eigen::Matrix4d  tf_tibia)
{
    transformMatStlinRefEigen = tf_tibia * stlEigenMatrixTool;

    vtkSmartPointer<vtkMatrix4x4> newVtkMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            newVtkMatrix->SetElement(i, j, transformMatStlinRefEigen(i, j));
        }
    }
    vtkSmartPointer<vtkTransform>   transformMatstlinRef = vtkSmartPointer<vtkTransform>::New();
    transformMatstlinRef->SetMatrix(newVtkMatrix);

    m_stlActorTool->SetUserTransform(transformMatstlinRef);
    m_verRenderer->GetRenderWindow()->Render();

    vtkMatrix4x4* matrix = m_stlActorTool->GetMatrix();

    double position[3] = {
        matrix->GetElement(0, 3),  // X position
        matrix->GetElement(1, 3),  // Y position
        matrix->GetElement(2, 3)   // Z position
    };

//    qDebug() << "STL Position from matrix:" << position[0] << position[1] << position[2];

    QVector3D coord;
    coord[0] = position[0];
    coord[1] = position[1];
    coord[2] = position[2];
    showCrossSection(coord);

    calculateRMSE(m_verAnnotationPt, coord);
}

void verificationui::showCrossSection(QVector3D point)
{
    m_verRendererCrossSection->GetActiveCamera()->SetPosition(initialPosition);
    m_verRendererCrossSection->GetActiveCamera()->SetFocalPoint(initialFocalPoint);
    m_verRendererCrossSection->GetActiveCamera()->SetViewUp(initialViewUp);

//    qDebug()<<" show cross setion point "<<point[0]<<point[1]<<point[2];
    double origin[3];
    double spacing[3];

//    qDebug()<<"verificationui::showCrossSection ** number of slices in dicom"<<m_verDcmReader->GetOutput()->GetDimensions()[2];
    m_verDcmReader->GetOutput()->GetSpacing(spacing);
    m_verDcmReader->GetOutput()->GetOrigin(origin);

    // Convert world coordinates to voxel index
    int voxelIndex[3];
    for (int i = 0; i < 3; ++i)
    {
        voxelIndex[i] = static_cast<int>((point[i] - origin[i]) / spacing[i]);
    }

//    qDebug()<<" slice location "<<voxelIndex[0]<<voxelIndex[1]<<voxelIndex[2];

    // axial slice index
    int sliceIndex = voxelIndex[2];

    planeWidget->SetSliceIndex(sliceIndex);
    //    planeWidget->Off();

    // show marked point
    vtkSmartPointer<vtkSphereSource> m_verSphereSourceSlice = vtkSmartPointer<vtkSphereSource>::New();
    m_verSphereSourceSlice->SetCenter(point[0], point[1], 0);
    m_verSphereSourceSlice->SetRadius(3);
    m_verSphereSourceSlice->SetThetaResolution(32);
    m_verSphereSourceSlice->SetPhiResolution(32);

    vtkSmartPointer<vtkPolyDataMapper> m_verSphereMapperSlice = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_verSphereMapperSlice->SetInputConnection(m_verSphereSourceSlice->GetOutputPort());

    m_verSphereActorSlice->SetMapper(m_verSphereMapperSlice);
    m_verSphereActorSlice->GetProperty()->SetColor(1.0, 0.0, 0.0);  // Red color
    m_verRendererCrossSection->AddActor(m_verSphereActorSlice);

    m_verRendererCrossSection->ResetCamera();
    m_verRendererCrossSection->GetActiveCamera()->Zoom(3.5);
    double focus[3];
    m_verRendererCrossSection->GetActiveCamera()->GetFocalPoint(focus);
//    qDebug()<<" focus point of camera "<<focus[0]<<focus[1]<<focus[2];
    m_verRendererCrossSection->GetActiveCamera()->SetFocalPoint(point[0], point[1], 0);

    m_verRendererCrossSection->SetInteractive(false);
//    m_pvtkWidgetVerif->GetRenderWindow()->Render();

}


void verificationui::landmarkCollection(QString LandmarkName)
{
    qDebug()<<"verificationui::VISUALISING ANNOTATED POINT FOR "<<LandmarkName;

    QString savedSTLpts;
    QVector<QVector3D> savedPts;
    m_VerLndSph->SetRadius(5);
    m_VerLndSph->SetThetaResolution(10);
    m_VerLndSph->SetPhiResolution(10);

    // read xml file
    QString filePath = QDir::currentPath() + "/Landmark.xml";
    annotationPointsVer = parseXMLFile(filePath);

    for (const auto& point : annotationPointsVer)
    {
        if (point.anatomy == LandmarkName) { // Compare anatomy with anatomyName
            std::cout << "MATCHED :: Anatomy: " << point.anatomy.toStdString()
                      << ", X: " << point.x
                      << ", Y: " << point.y
                      << ", Z: " << point.z << std::endl;
            m_verAnnotationPt[0] = point.x;
            m_verAnnotationPt[1] = point.y;
            m_verAnnotationPt[2] = point.z;
        }
    }

    m_VerLndSph->SetCenter(m_verAnnotationPt);
    m_VerLndSph->Update();
    m_VerLndSphMapper->SetInputConnection(m_VerLndSph->GetOutputPort());
    m_VerLndSphActor->SetMapper(m_VerLndSphMapper);
    m_VerLndSphActor->GetProperty()->SetColor(0,1,0);
    m_verRenderer->AddActor(m_VerLndSphActor);

    m_verRenderer->GetActiveCamera()->SetFocalPoint(m_verAnnotationPt);
    m_verRenderer->GetActiveCamera()->Elevation(45);
    m_verRenderer->ResetCameraClippingRange();

}

void verificationui::loadDicomData(QString anatomy)
{
    qDebug()<<" loading dicom data ";

    m_qstrVerTibia = "D:/Robotic Surgery/POC_FIN/Build/Segmentation_batfile/output/Tibia";
    m_qstrVerFemur = "D:/Robotic Surgery/POC_FIN/Build/Segmentation_batfile/output/Femur";

    if (anatomy == "Femur"){
        m_verDcmReader->SetDirectoryName(m_qstrVerFemur.toStdString().c_str());
        m_verDcmReader->Update();
    }
    else {
        m_verDcmReader->SetDirectoryName(m_qstrVerTibia.toStdString().c_str());
        m_verDcmReader->Update();
    }


    double isoValue = -800;
    m_verSurface->SetInputConnection(m_verDcmReader->GetOutputPort());
    m_verSurface->ComputeNormalsOn();
    m_verSurface->ComputeScalarsOn();
    m_verSurface->SetValue(0, isoValue);

    m_verSurfaceMapper->SetInputConnection(m_verSurface->GetOutputPort());
    m_verSurfaceMapper->SetScalarVisibility(false);
    m_verSurfaceMapper->Update();

    m_verSurfaceActor->SetMapper(m_verSurfaceMapper);
}

void verificationui::slotShowTransformedPoints(QString anatomy, int id, QString lndmarkname)
{
    loadDicomData(anatomy);

    m_verRenderer->AddActor(m_verSurfaceActor);

//    qDebug()<<" signal recieved in verificationui" <<anatomy <<id <<lndmarkname;

    landmarkCollection(lndmarkname);
    m_pvtkWidgetVerif->GetRenderWindow()->Render();

}




void verificationui::calculateRMSE(double point[3], const QVector3D& referencePoint) {

    double diffX = point[0] - referencePoint.x();
    double diffY = point[1] - referencePoint.y();
    double diffZ = point[2] - referencePoint.z();

    double squaredError = diffX * diffX + diffY * diffY + diffZ * diffZ;
    double rmse = std::sqrt(squaredError / 3.0);

//    qDebug() << " rmse " <<rmse;

    textAct = QString(" RMSE: %1\n").arg(rmse);

    rmseTextActor->SetInput(textAct.toStdString().c_str());
    rmseTextActor->GetTextProperty()->SetFontSize(24);
    rmseTextActor->GetTextProperty()->SetFontFamilyToArial();
    rmseTextActor->GetTextProperty()->BoldOn();
    rmseTextActor->GetPositionCoordinate()->SetCoordinateSystemToNormalizedViewport();
    rmseTextActor->GetPositionCoordinate()->SetValue(0.5, 0.9);                   // Set text position in the window (pixels)

    m_verRenderer->AddActor2D(rmseTextActor);

}


void verificationui::importstltool()
{
    // Step 1: Load the STL file
    m_stlReaderTool = vtkSmartPointer<vtkSTLReader>::New();
    QString stlpath = QDir::currentPath()+"/Plan/Viewer/NeedleTracker.stl";

    m_stlReaderTool->SetFileName(stlpath.toStdString().c_str());
    //    m_stlReaderTool->SetFileName("D:\\TKA\\New folder\\Build\\stl\\reamer\\reamer11001.stl");// Specify the STL file path");
    m_stlReaderTool->Update();

    // Step 2: Create a mapper for the STL model
    m_stlMappertool = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_stlMappertool->SetInputConnection(m_stlReaderTool->GetOutputPort());

    // Step 3: Create an actor for the STL tool
    m_stlActorTool = vtkSmartPointer<vtkActor>::New();
    m_stlActorTool->SetMapper(m_stlMappertool);

    // Optionally, set the appearance of the tool (color, opacity, etc.)
    m_stlActorTool->GetProperty()->SetColor(1.0, 0.0, 0.0);  // Red color for the tool
    m_stlActorTool->GetProperty()->SetOpacity(0.8);


    vtkSmartPointer<vtkTransform> transformrot = vtkSmartPointer<vtkTransform>::New();

    // Rotate the STL by 90 degrees along the X-axis
    transformrot->RotateX(90.0);
    m_stlActorTool->SetUserTransform(transformrot);

    vtkMatrix4x4* transformMatrix = m_stlActorTool->GetMatrix();

    // Print the transformation matrix
    std::cout << "Transformation Matrix: " << std::endl;
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            std::cout << transformMatrix->GetElement(i, j) << " ";
        }
        std::cout << std::endl;
    }
    // Convert to Eigen::Matrix4d
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            stlEigenMatrixTool(i, j) = transformMatrix->GetElement(i, j);
        }
    }
    m_verRenderer->AddActor(m_stlActorTool);


}




