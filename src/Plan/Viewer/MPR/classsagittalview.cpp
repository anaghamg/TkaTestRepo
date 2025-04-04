#include "classsagittalview.h"
#include <QVBoxLayout>
ClassSagittalView::ClassSagittalView(QWidget *parent) : QWidget(parent)
{
    //Sagittal
    m_QVTKOpenGLWidgetSagital= new QVTKOpenGLWidget;

    m_ResliceImageViewerSagittal->SetRenderWindow(m_RenderWindowSagittal);
    m_ResliceImageViewerSagittal->SetupInteractor(m_InteractionSagittal);

    m_QVTKOpenGLWidgetSagital->SetRenderWindow(m_RenderWindowSagittal);
    m_RenderWindowSagittal->SetInteractor(m_InteractionSagittal);

    m_ResliceImageViewerSagittal->SetupInteractor(m_RenderWindowSagittal->GetInteractor());

    auto callbackSag = vtkSmartPointer<vtkCallbackCommand>::New();
    callbackSag->SetCallback([](vtkObject* caller, unsigned long eventId, void* clientData, void* callData)
    {
        static_cast<ClassSagittalView*>(clientData)->ExecuteSagittal(caller, eventId, callData);
    });
    callbackSag->SetClientData(this);

   // m_RenderWindowSagittal->GetInteractor()->AddObserver(vtkCommand::RightButtonPressEvent, callbackSag);

    QVBoxLayout *LaySaggital= new QVBoxLayout;
    LaySaggital->addWidget(m_QVTKOpenGLWidgetSagital);
    this->setLayout(LaySaggital);
}

void ClassSagittalView::sagittalView(vtkDICOMImageReader *reader){


    //Parvathy
     //adding the corner annotation
      vtkNew<vtkNamedColors> colors;
      vtkNew<vtkCornerAnnotation> cornerAnnotation;
      cornerAnnotation->SetLinearFontScaleFactor(3);
      cornerAnnotation->SetNonlinearFontScaleFactor(1);
      cornerAnnotation->SetMaximumFontSize(20);
      cornerAnnotation->SetText(2, "Sagittal");
      cornerAnnotation->GetTextProperty()->SetColor(
           colors->GetColor3d("White").GetData());
      cornerAnnotation->GetTextProperty()->BoldOn();


      vtkNew<vtkTextActor> txtActorA;
      txtActorA->GetTextProperty()->SetFontSize(20);
      txtActorA->SetTextScaleModeToNone();
      txtActorA->SetDisplayPosition(0,155);
      txtActorA->SetInput("A");

      vtkNew<vtkTextActor> txtActorP;
      txtActorP->GetTextProperty()->SetFontSize(20);
      txtActorP->SetTextScaleModeToNone();
      txtActorP->SetDisplayPosition(this->width()-5,155);
      txtActorP->SetInput("P");

      vtkNew<vtkTextActor> txtActorS;
      txtActorS->GetTextProperty()->SetFontSize(20);
      txtActorS->SetTextScaleModeToNone();
      txtActorS->SetDisplayPosition(350,370);
      txtActorS->SetInput("S");

      vtkNew<vtkTextActor> txtActorI;
      txtActorI->GetTextProperty()->SetFontSize(20);
      txtActorI->SetTextScaleModeToNone();
      txtActorI->SetDisplayPosition(350,5);
       txtActorI->SetInput("I");




    m_ResliceImageViewerSagittal->SetInputData(reader->GetOutput());

    rep = vtkResliceCursorLineRepresentation::SafeDownCast(
                m_ResliceImageViewerSagittal->GetResliceCursorWidget()->GetRepresentation());

    rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(0);

    m_ResliceImageViewerSagittal->GetResliceCursor()->SetHoleWidthInPixels(10000); // rupika

    m_ResliceImageViewerSagittal->SetSliceOrientationToYZ(); // Sagittal view

    m_ResliceImageViewerSagittal->SetResliceModeToOblique();
    m_ResliceImageViewerSagittal->GetResliceCursorWidget()->SetEnabled(1);

    m_ResliceImageViewerSagittal->GetRenderer()->ResetCamera();


    //------------ setting zoom ------------------//
        vtkImageData* image = m_ResliceImageViewerSagittal->GetInput();
            if (!image) {
                qDebug() << "No image data!";
                return;
            }

            int extent[6];
            image->GetExtent(extent);
            double spacing[3];
            image->GetSpacing(spacing);
            qDebug() << "Image extent:" << extent[0] << extent[1] << extent[2] << extent[3] << extent[4] << extent[5];

            // Calculate the size of the anatomy/image in physical units
            double imageSizeX = (extent[1] - extent[0] + 1) * spacing[0]; // Width of the image
            double imageSizeY = (extent[3] - extent[2] + 1) * spacing[1]; // Height of the image

            // Get the size of the viewport (physical size)
            int* windowSize = m_ResliceImageViewerSagittal->GetRenderWindow()->GetSize();
            double viewportSizeX = windowSize[0]; // Width of the viewport
            double viewportSizeY = windowSize[1]; // Height of the viewport

            // Compute the aspect ratios
            double imageAspectRatio = imageSizeX / imageSizeY;
            double viewportAspectRatio = viewportSizeX / viewportSizeY;

            // Define the zoom ratio (80%)
            double zoomFactor = 0.8;

            // Calculate the target parallel scale for consistent zooming
            double parallelScale = 0.0;
            if (imageAspectRatio > viewportAspectRatio) {
                // Image is wider than the viewport, scale based on width
                parallelScale = (imageSizeX / 2.0) / viewportAspectRatio;
            } else {
                // Image is taller than the viewport, scale based on height
                parallelScale = imageSizeY / 2.0;
            }

            // Apply the zoom factor
            parallelScale *= zoomFactor;

            // Set the parallel scale to the camera
            m_ResliceImageViewerSagittal->GetRenderer()->GetActiveCamera()->SetParallelScale(parallelScale);

            qDebug() << "Parallel scale set to:" << parallelScale;

    //-------------------------------------------


















   // m_ResliceImageViewerSagittal->GetRenderer()->GetActiveCamera()->Zoom(1.2);


            m_ResliceImageViewerSagittal->GetRenderer()->GetActiveCamera()->Roll(-180);
    m_ResliceImageViewerSagittal->GetRenderer()->AddViewProp(cornerAnnotation);//parvathy
    m_ResliceImageViewerSagittal->GetRenderer()->AddActor(txtActorA);//parvathy
    m_ResliceImageViewerSagittal->GetRenderer()->AddActor(txtActorP);//parvathy
    m_ResliceImageViewerSagittal->GetRenderer()->AddActor(txtActorS);//parvathy
    m_ResliceImageViewerSagittal->GetRenderer()->AddActor(txtActorI);//parvathy


    //commented by anagha 27-09-2024
//    // Load and set up the OBJ model
//    QString FileName = QDir::currentPath()+"/Plan/Viewer/free_head.obj";
//    QByteArray ba = FileName.toLatin1(); // Or str.toUtf8() for UTF-8 encoding
//    const char* cstr = ba.data();

//    readerObjSagittal->SetFileName(cstr);
//    readerObjSagittal->Update();

//    mapperSagittal->SetInputConnection(readerObjSagittal->GetOutputPort());

//    m_ObjActorSagittal->SetMapper(mapperSagittal);
//    m_ObjActorSagittal->GetProperty()->SetColor(1.0, 0.5, 0.0); // Set your desired color
//    m_ObjActorSagittal->SetVisibility(true);

//    transformSagittal->Translate(m_ObjActorSagittal->GetCenter());
//    transformSagittal->RotateWXYZ(-90, 1, 0, 0); // Apply -90 degree pitch
//    m_ObjActorSagittal->SetUserTransform(transformSagittal);
//    m_ObjActorSagittal->GetProperty()->SetRepresentationToWireframe();

//    m_OrientationMarkerWidgetSagittal->SetOrientationMarker(m_ObjActorSagittal);
//    m_OrientationMarkerWidgetSagittal->SetInteractor(m_InteractionSagittal);
//    m_OrientationMarkerWidgetSagittal->SetViewport(0.8, 0.0, 1.0, 0.2);
////    m_OrientationMarkerWidgetSagittal->SetEnabled(1);
//    m_OrientationMarkerWidgetSagittal->InteractiveOff();

    //d
    m_InteractionSagittal->SetInteractorStyle(style_custom);

    m_InteractionSagittal->Initialize();
    m_ResliceImageViewerSagittal->Render();
}


void ClassSagittalView::ExecuteSagittal(vtkObject *caller, unsigned long eventId, void *callData)
{
    // to handle point selection event
    qDebug()<<" right button pressed in sagittal ";

    int axialpickedpt[2];
    m_RenderWindowSagittal->GetInteractor()->GetEventPosition(axialpickedpt);

    vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
    picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_RenderWindowSagittal->GetRenderers()->GetFirstRenderer());

    double pickedPosition[3];
    picker->GetPickPosition(pickedPosition);
    std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

    qDebug()<< "Picked position: ("
              << pickedPosition[0] << ", "
              << pickedPosition[1] << ", "
              << pickedPosition[2] << ")" ;

    emit signalPickedPtSagittal(point);
}
