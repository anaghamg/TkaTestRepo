#include "threedrender.h"
#include <QVBoxLayout>
ThreeDRender::ThreeDRender(QWidget *parent) : QWidget(parent)
{
    m_VTK3DWidget = new QVTKOpenGLWidget;
    m_VTK3DWidget->SetRenderWindow(m_3DRenderWindow);
    //m_3DInteractor->SetInteractorStyle(style);
    m_3DRenderWindow->SetInteractor(m_3DInteractor);

    auto callback3D = vtkSmartPointer<vtkCallbackCommand>::New();
    callback3D->SetCallback([](vtkObject* caller, unsigned long eventId, void* clientData, void* callData)
    {
        static_cast<ThreeDRender*>(clientData)->Execute3D(caller, eventId, callData);
    });
    callback3D->SetClientData(this);

    //m_3DRenderWindow->GetInteractor()->AddObserver(vtkCommand::RightButtonPressEvent, callback3D);

    QVBoxLayout *Lay= new QVBoxLayout;
    Lay->addWidget(m_VTK3DWidget);
    this->setLayout(Lay);
}

void ThreeDRender::ThreeDView(vtkDICOMImageReader *reader)
{
    qDebug()<<"Dicom dir in in 3D reader : "<<reader->GetDirectoryName();
    //Parvathy
    //adding the corner annotation
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkCornerAnnotation> cornerAnnotation;
    cornerAnnotation->SetLinearFontScaleFactor(3);
    cornerAnnotation->SetNonlinearFontScaleFactor(1);
    cornerAnnotation->SetMaximumFontSize(20);
    cornerAnnotation->SetText(2, "3D View");
    cornerAnnotation->GetTextProperty()->SetColor(
                colors->GetColor3d("White").GetData());
    cornerAnnotation->GetTextProperty()->BoldOn();

    vtkNew<vtkTextActor> txtActorA;
    txtActorA->GetTextProperty()->SetFontSize(20);
    txtActorA->SetTextScaleModeToNone();
    //txtActorA->SetTextScaleMode(8);
    txtActorA->SetDisplayPosition(0,155);
    txtActorA->SetInput("A");

    vtkNew<vtkTextActor> txtActorP;
    txtActorP->GetTextProperty()->SetFontSize(20);
    txtActorP->SetTextScaleModeToNone();
    // txtActorP->SetTextScaleMode(8);
    txtActorP->SetDisplayPosition(this->width()-5,155);
    txtActorP->SetInput("P");

    vtkNew<vtkTextActor> txtActorS;
    txtActorS->GetTextProperty()->SetFontSize(20);
    txtActorS->SetTextScaleModeToNone();
    //txtActorS->SetTextScaleMode(8);
    txtActorS->SetDisplayPosition(350,350);
    txtActorS->SetInput("S");

    vtkNew<vtkTextActor> txtActorI;
    txtActorI->GetTextProperty()->SetFontSize(20);
    txtActorI->SetTextScaleModeToNone();
    // txtActorI->SetTextScaleMode(8);
    txtActorI->SetDisplayPosition(350,5);
    txtActorI->SetInput("I");

    //------------ surface rendering ------------//

    int imageDims[3];
    reader->GetOutput()->GetDimensions(imageDims);

    vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
    picker->SetTolerance(0.005);

    //modified by anagha 27-09-2024

    // Create a Marching Cubes filter
    //    vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    //    marchingCubes->SetInputData(reader->GetOutput());
    //    marchingCubes->SetValue(0, -700); // Set the iso value, adjust as needed 300 for bone..
    //    marchingCubes->ComputeNormalsOn();
    //    marchingCubes->ComputeScalarsOn();

    //    // Stripper to merge the triangles into polygons
    //    vtkSmartPointer<vtkStripper> stripper = vtkSmartPointer<vtkStripper>::New();
    //    stripper->SetInputConnection(marchingCubes->GetOutputPort());
    //    stripper->Update();

    //    vtkSmartPointer<vtkPolyData> polyData = stripper->GetOutput();

    //    connectivityFilter->SetInputData(polyData);
    //    connectivityFilter->SetExtractionModeToLargestRegion();
    //    connectivityFilter->Update();

    // Visualize
    //    int numberOfRegions = connectivityFilter->GetNumberOfExtractedRegions();
    //    std::cout << "Generated data" << " contains " << numberOfRegions << " regions" << std::endl;

    //    boneLut->SetNumberOfTableValues(std::max(numberOfRegions, 10));
    //    boneLut->Build();

    //    for (auto i = 2; i < numberOfRegions; ++i)
    //    {
    //        boneLut->SetTableValue(i, colors->GetColor4d("Wheat").GetData());
    //    }


    //    //taken from python code
    //    vtkSmartPointer<vtkSmoothPolyDataFilter> smoother = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    //    smoother->SetInputConnection(marchingCubes->GetOutputPort()) ;
    //    smoother->SetNumberOfIterations(50) ;
    //    smoother->SetRelaxationFactor(0.1) ;
    //    smoother->FeatureEdgeSmoothingOff();
    //    smoother->BoundarySmoothingOn() ;
    //    qDebug()<<"3d full data";
    //    smoother->Update();
    //    qDebug()<<"3d full data";

    //    vtkNew<vtkPolyDataMapper> mapper;
    //    //    mapper->SetInputConnection(connectivityFilter->GetOutputPort());
    //    mapper->SetInputConnection(smoother->GetOutputPort());
    //    //    mapper->SetScalarRange(0, connectivityFilter->GetNumberOfExtractedRegions() - 1);
    //    //    mapper->SetLookupTable(boneLut);
    //    mapper->SetScalarVisibility(false);
    //    mapper->Update();

    //    vtkNew<vtkActor> boneActor;
    //    boneActor->SetMapper(mapper);
    //    boneActor->GetProperty()->SetDiffuse(0.8);
    //    boneActor->GetProperty()->SetSpecular(0.3);
    //    boneActor->GetProperty()->SetSpecularPower(60);
    boneActor->SetMapper(mapperfemur);
    m_3DRenderer->AddActor(boneActor);
    m_3DRenderer->AddActor(txtActorP);//parvathy
    m_3DRenderer->AddActor(txtActorA);//parvathy
    m_3DRenderer->AddActor(txtActorS);//parvathy
    m_3DRenderer->AddActor(txtActorI);//parvathy
    m_3DRenderer->AddViewProp(cornerAnnotation);//parvathy
    m_3DRenderWindow->AddRenderer(m_3DRenderer);


    for (int i = 0; i < 3; i++)
    {
        planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
        planeWidget[i]->SetInteractor(m_3DInteractor);
        planeWidget[i]->SetPicker(picker);
        planeWidget[i]->RestrictPlaneToVolumeOn();
        double color[3] = { 0, 0, 0 };
        color[i] = 1;
        planeWidget[i]->GetPlaneProperty()->SetColor(color);
        color[0] /= 4.0;
        color[1] /= 4.0;
        color[2] /= 4.0;
        //riw[i]->GetRenderer()->SetBackground(color);
        //planeWidget[i]->SetTexturePlaneProperty(ipwProp);
        planeWidget[i]->GetTexturePlaneProperty()->SetOpacity(0.05);
        //planeWidget[i]->SetTextureVisibility(false);
        planeWidget[i]->SetResliceInterpolateToLinear();
        planeWidget[i]->SetInputConnection(reader->GetOutputPort());
        planeWidget[i]->SetPlaneOrientation(i);
        planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
        planeWidget[i]->DisplayTextOn();
        planeWidget[i]->SetDefaultRenderer(m_3DRenderer);
        planeWidget[i]->SetWindowLevel(1358, -27);
        //        planeWidget[i]->On();
        //        planeWidget[i]->InteractionOn();
        //        planeWidget[i]->UpdatePlacement();
    }


    //commented by anagha 27092024
    // Load OBJ object
    //    QString FileName = QDir::currentPath()+"/Plan/Viewer/free_head.obj";
    //    QByteArray ba = FileName.toLatin1(); // Or str.toUtf8() for UTF-8 encoding
    //    const char* cstr = ba.data();
    //    objReader->SetFileName(cstr);

    //    objMapper->SetInputConnection(objReader->GetOutputPort());

    //    objActor->SetMapper(objMapper);
    //    //        objActor->GetProperty()->SetColor(1.0, 0.5, 0.0);
    //    objActor->GetProperty()->SetRepresentationToWireframe();

    //    // Apply transformations to align the OBJ actor
    //    transform->Translate(objActor->GetCenter());
    //    transform->RotateWXYZ(-90, 1, 0, 0); // Apply -90 degree pitch
    //    objActor->SetUserTransform(transform);

    //    // Apply the same camera transformations to align the OBJ actor
    //    m_3DRenderer->GetActiveCamera()->Azimuth(90);
    //    m_3DRenderer->GetActiveCamera()->Roll(90);
    //    m_3DRenderer->GetActiveCamera()->Yaw(-90);
    //    m_3DRenderer->GetActiveCamera()->Zoom(1.2);
    //    m_3DRenderer->GetActiveCamera()->SetClippingRange(0.1, 10000);

    //    // Add the OBJ actor to the renderer
    //    m_3DRenderer->AddActor(objActor);

    ////    // Create an orientation marker widget with the OBJ actor
    ////    orientationWidget->SetOrientationMarker(objActor);
    ////    orientationWidget->SetInteractor(m_3DInteractor);
    ////    orientationWidget->SetViewport(0.8, 0.0, 1.0, 0.2); // Bottom right corner
    ////    //    orientationWidget->SetEnabled(1);
    ////    orientationWidget->InteractiveOff();

    m_3DRenderWindow->GlobalWarningDisplayOff();
    m_3DRenderWindow->Render();

    m_3DRenderer->GetActiveCamera()->Elevation(50);
    m_3DRenderer->GetActiveCamera()->Roll(50);

    m_3DRenderer->ResetCamera();

    m_3DInteractor->SetInteractorStyle(adjust);

    m_3DInteractor->Initialize();
}

void ThreeDRender::Execute3D(vtkObject *caller, unsigned long eventId, void *callData)
{
    qDebug()<<" right button pressed in 3D ";

    int axialpickedpt[2];
    m_3DRenderWindow->GetInteractor()->GetEventPosition(axialpickedpt);

    vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
    picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_3DRenderWindow->GetRenderers()->GetFirstRenderer());

    double pickedPosition[3];
    picker->GetPickPosition(pickedPosition);
    std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

    qDebug()<< "Picked position: ("
            << pickedPosition[0] << ", "
            << pickedPosition[1] << ", "
            << pickedPosition[2] << ")" ;

    emit signalPickedPt3D(point);
}
void ThreeDRender::Tibia3D()
{
    m_qstrDcmTibia = QDir::currentPath() + "/Segmentation_batfile/output/Tibia";
    tibiareader->SetDirectoryName(m_qstrDcmTibia.toUtf8().constData());
    qDebug() << "Directory is set correctly:" << m_qstrDcmTibia;
    tibiareader->Update();

    marchingCubestibia->SetInputData(tibiareader->GetOutput());

    double scalarRange[2];
    tibiareader->GetOutput()->GetScalarRange(scalarRange);
    qDebug() << "Scalar range of the femur DICOM data:" << scalarRange[0] << scalarRange[1];

    // marchingCubestibia->SetValue(0, scalarRange[0] + 0.1 * (scalarRange[1] - scalarRange[0]));

    marchingCubestibia->SetValue(0, -800);
    marchingCubestibia->ComputeNormalsOn();
    marchingCubestibia->ComputeScalarsOn();

    //           vtkSmartPointer<vtkSmoothPolyDataFilter> smoothertibia = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    //           smoothertibia->SetInputConnection(marchingCubestibia->GetOutputPort()) ;
    //           smoothertibia->SetNumberOfIterations(50) ;
    //           smoothertibia->SetRelaxationFactor(0.1) ;
    //           smoothertibia->FeatureEdgeSmoothingOff();
    //           smoothertibia->BoundarySmoothingOn() ;
    //           smoothertibia->Update();


    vtkNew<vtkPolyDataMapper> mappertibia;
    mappertibia->SetInputConnection(marchingCubestibia->GetOutputPort());
    mappertibia->SetScalarVisibility(false);
    mappertibia->Update();


    boneActortibia->SetMapper(mappertibia);
    //    boneActortibia->GetProperty()->SetColor(1.0, 0.98, 0.94); // off-white
    boneActortibia->GetProperty()->SetColor(0.9, 0.9, 0.9); //Light Gray

    QString outputFilePath = QDir::currentPath() + "/Segmentation_batfile/output/TibiaModel.stl";
    vtkSmartPointer<vtkSTLWriter> stlWriterTibia = vtkSmartPointer<vtkSTLWriter>::New();
    stlWriterTibia->SetFileName(outputFilePath.toUtf8().constData());
    stlWriterTibia->SetInputConnection(marchingCubestibia->GetOutputPort());
    stlWriterTibia->Write();

}

void ThreeDRender::Femur3D()
{
    m_qstrDcmFemur = QDir::currentPath() + "/Segmentation_batfile/output/Femur";
    QDir dir(m_qstrDcmFemur);
    femurreader->SetDirectoryName(m_qstrDcmFemur.toUtf8().constData());
    qDebug() << "Directory is set correctly:" << m_qstrDcmFemur;
    femurreader->Update();

    marchingCubesfemur->SetInputData(femurreader->GetOutput());
    double scalarRange[2];
    femurreader->GetOutput()->GetScalarRange(scalarRange);
    qDebug() << "Scalar range of the femur DICOM data:" << scalarRange[0] << scalarRange[1];

    //  marchingCubesfemur->SetValue(0, scalarRange[0] + 0.1 * (scalarRange[1] - scalarRange[0]));
    marchingCubesfemur->SetValue(0, -800); // Set the iso value, adjust as needed 300 for bone..
    marchingCubesfemur->ComputeNormalsOn();
    marchingCubesfemur->ComputeScalarsOn();

    //            // Fill the holes in the mesh to close the surface
    //            vtkSmartPointer<vtkFillHolesFilter> fillHolesFilter = vtkSmartPointer<vtkFillHolesFilter>::New();
    //            fillHolesFilter->SetInputConnection(marchingCubesfemur->GetOutputPort());
    //            fillHolesFilter->SetHoleSize(1000.0); // Adjust based on the size of gaps
    //            fillHolesFilter->Update();

//    vtkSmartPointer<vtkSmoothPolyDataFilter> smootherfemur = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
//    smootherfemur->SetInputConnection(marchingCubesfemur->GetOutputPort()) ;
//    smootherfemur->SetNumberOfIterations(200) ;
//    smootherfemur->SetRelaxationFactor(0.1) ;
//    smootherfemur->FeatureEdgeSmoothingOff();
//    smootherfemur->BoundarySmoothingOn() ;
//    smootherfemur->Update();

    //            vtkNew<vtkFeatureEdges> featureEdges;
    //            featureEdges->FeatureEdgesOff();
    //            featureEdges->BoundaryEdgesOn();
    //            featureEdges->NonManifoldEdgesOn();
    //            featureEdges->ManifoldEdgesOff();
    //            featureEdges->SetInputConnection(smootherfemur->GetOutputPort());
    //            featureEdges->Update();

    mapperfemur->SetInputConnection(marchingCubesfemur->GetOutputPort());
    mapperfemur->SetScalarVisibility(false);
    mapperfemur->Update();

    boneActorfemur->SetMapper(mapperfemur);
//    boneActorfemur->GetProperty()->SetColor(1.0, 0.98, 0.94); // off-white
    boneActorfemur->GetProperty()->SetColor(0.9, 0.9, 0.9); //Light Gray

    QString outputFilePath = QDir::currentPath() + "/Segmentation_batfile/output/FemurModel.stl";
    vtkSmartPointer<vtkSTLWriter> stlWriterFemur = vtkSmartPointer<vtkSTLWriter>::New();
    stlWriterFemur->SetFileName(outputFilePath.toUtf8().constData());
    stlWriterFemur->SetInputConnection(marchingCubesfemur->GetOutputPort());
    stlWriterFemur->Write();

    //     vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    //     renderer->SetBackground(0.1, 0.2, 0.3); // Set a background color (optional)


    //     vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    //     renderWindow->AddRenderer(renderer);

    //     vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    //     renderWindowInteractor->SetRenderWindow(renderWindow);


    //     boneActorfemur->GetProperty()->SetColor(1.0, 0.9, 0.8); // Set color for the actor (optional)
    //     renderer->AddActor(boneActorfemur);

    //     renderWindow->Render();
    //     renderWindowInteractor->Initialize();
    //     renderWindowInteractor->Start();

}


vtkSmartPointer<vtkActor> ThreeDRender::GetFemurActor()
{
    qDebug()<<"3d boneActorfemur";
    return boneActorfemur;
}
vtkSmartPointer<vtkActor> ThreeDRender::GetTibiaActor()
{
    qDebug()<<"3d boneActortibia";
    return boneActortibia;
}
void ThreeDRender::RemoveBoneActor() {

    if (m_3DRenderer->HasViewProp(boneActor)) {
        m_3DRenderer->RemoveActor(boneActor);
    }

    if (m_3DRenderer->HasViewProp(boneActortibia)) {
        m_3DRenderer->RemoveActor(boneActortibia);
    }

    if (m_3DRenderer->HasViewProp(boneActorfemur)) {
        m_3DRenderer->RemoveActor(boneActorfemur);
    }

    m_3DRenderWindow->Render();
}

