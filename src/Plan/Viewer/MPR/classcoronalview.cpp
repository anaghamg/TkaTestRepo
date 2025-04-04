#include "classcoronalview.h"
#include <QVBoxLayout>

ClassCoronalView::ClassCoronalView(QWidget *parent) : QWidget(parent)
{
    //coronal
    m_QVTKOpenGLWidgetCoronal= new QVTKOpenGLWidget;

    m_ResliceImageViewerCoronal->SetRenderWindow(m_RenderWindowCoronal);
    m_ResliceImageViewerCoronal->SetupInteractor(m_InteractionCoronal);

    m_QVTKOpenGLWidgetCoronal->SetRenderWindow(m_RenderWindowCoronal);
    m_RenderWindowCoronal->SetInteractor(m_InteractionCoronal);

    //uncommented
    m_ResliceImageViewerCoronal->SetupInteractor(m_RenderWindowCoronal->GetInteractor());

    auto callbackCor = vtkSmartPointer<vtkCallbackCommand>::New();
    callbackCor->SetCallback([](vtkObject* caller, unsigned long eventId, void* clientData, void* callData)
    {
        static_cast<ClassCoronalView*>(clientData)->ExecuteCoronal(caller, eventId, callData);
    });
    callbackCor->SetClientData(this);

    //m_RenderWindowCoronal->GetInteractor()->AddObserver(vtkCommand::RightButtonPressEvent, callbackCor);

    QVBoxLayout *LayCoronal= new QVBoxLayout;
    LayCoronal->addWidget(m_QVTKOpenGLWidgetCoronal);
    this->setLayout(LayCoronal);
}

void ClassCoronalView::coronalView(vtkDICOMImageReader *reader,QString selKnee)
{    


    //Parvathy

    //calculate the offset

    int* dims = reader->GetOutput()->GetDimensions(); //get the width
    imgwidth = dims[0];
    double* pxspacing= reader->GetOutput()->GetSpacing();
    pixelspacing= pxspacing[0];
    offsetcoronal = imgwidth * pixelspacing;


    //adding the corner annotation
    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkCornerAnnotation> cornerAnnotation;
    cornerAnnotation->SetLinearFontScaleFactor(3);
    cornerAnnotation->SetNonlinearFontScaleFactor(1);
    cornerAnnotation->SetMaximumFontSize(20);
    cornerAnnotation->SetText(2, "Coronal");
    cornerAnnotation->GetTextProperty()->SetColor(colors->GetColor3d("White").GetData());

    cornerAnnotation->GetTextProperty()->BoldOn();


      vtkNew<vtkTextActor> txtActorL;
      txtActorL->GetTextProperty()->SetFontSize(20);
      txtActorL->SetTextScaleModeToNone();
      //txtActorL->SetDisplayPosition(0,155);
      txtActorL->SetInput("L");


      vtkNew<vtkTextActor> txtActorM;
      txtActorM->GetTextProperty()->SetFontSize(20);
      txtActorM->SetTextScaleModeToNone();
      //txtActorM->SetDisplayPosition(this->width()-5,155);
      txtActorM->SetInput("M");



      txtActorM->SetDisplayPosition(0,155);
      txtActorL->SetDisplayPosition(this->width()-5,155);

       if (selKnee == "Right Knee")
      {

          txtActorM->SetDisplayPosition(this->width()-15,155);
          txtActorL->SetDisplayPosition(0,155);

      }else if(selKnee == "Left Knee")
      {
          txtActorM->SetDisplayPosition(0,155);
          txtActorL->SetDisplayPosition(this->width()-15,155);
      }





      vtkNew<vtkTextActor> txtActorS;
      txtActorS->GetTextProperty()->SetFontSize(20);
      txtActorS->SetTextScaleModeToNone();
      txtActorS->SetDisplayPosition(350,350); //370
      txtActorS->SetInput("S");

      vtkNew<vtkTextActor> txtActorI;
      txtActorI->GetTextProperty()->SetFontSize(20);
      txtActorI->SetTextScaleModeToNone();
      txtActorI->SetDisplayPosition(350,5);
      txtActorI->SetInput("I");


      //Parvathy- for flipping
      vtkSmartPointer<vtkImageFlip> FlipY = vtkSmartPointer<vtkImageFlip>::New();
      FlipY->SetInputData(reader->GetOutput());
      FlipY->SetFilteredAxis(1);
      FlipY->SetFilteredAxis(0);


      FlipY->Update();

      m_ResliceImageViewerCoronal->SetInputData(FlipY->GetOutput());



   // m_ResliceImageViewerCoronal->SetInputData(reader->GetOutput());


    //my code
//    vtkImageData* image = m_ResliceImageViewerCoronal->GetInput();
//    int extent[6];
//    image->GetExtent(extent);
//    double spacing[3];
//    image->GetSpacing(spacing);
//    qDebug()<<"image extent"<<extent[0]<<extent[1]<<extent[2]<<extent[3]<<extent[4]<<extent[5];

//    // Calculate the size of the anatomy/image in physical units
//    double imageSizeX = (extent[1] - extent[0]) * spacing[0]; // Width of the image
//    double imageSizeY = (extent[3] - extent[2]) * spacing[1]; // Height of the image

//    // 2. Get the size of the viewport (physical size)
//    int* windowSize = m_ResliceImageViewerCoronal->GetRenderWindow()->GetSize();
//    double viewportSizeX = windowSize[0]; // Width of the viewport
//    double viewportSizeY = windowSize[1]; // Height of the viewport

//    // 3. Compute the aspect ratios
//    double imageAspectRatio = imageSizeX / imageSizeY;
//    double viewportAspectRatio = viewportSizeX / viewportSizeY;

//    // 4. Set the zoom ratio to 80% of the anatomy with respect to the viewport
//    double zoomFactor = 0.2;
//    double targetScaleX = viewportSizeX * zoomFactor;
//    double targetScaleY = viewportSizeY * zoomFactor;

//    // Depending on the aspect ratio, adjust the camera's parallel scale
//    if (imageAspectRatio > viewportAspectRatio) {
//        // The image is wider than the viewport, so fit based on width
//        m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->SetParallelScale(targetScaleX);
//    } else {
//        // The image is taller than the viewport, so fit based on height
//        m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->SetParallelScale(targetScaleY);
//    }













    // make them all share the same reslice cursor object.
    rep = vtkResliceCursorLineRepresentation::SafeDownCast(
                m_ResliceImageViewerCoronal->GetResliceCursorWidget()->GetRepresentation());
    rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(1);
    m_ResliceImageViewerCoronal->GetResliceCursor()->SetHoleWidthInPixels(10000); // rupika
    m_ResliceImageViewerCoronal->SetSliceOrientationToXZ(); // Coronal view
    m_ResliceImageViewerCoronal->SetResliceModeToOblique();
    m_ResliceImageViewerCoronal->GetResliceCursorWidget()->SetEnabled(1);



    //m_ResliceImageViewerCoronal->Render(); //commented
    m_ResliceImageViewerCoronal->GetRenderer()->ResetCamera(); //commented


//------------ setting zoom ------------------//
    vtkImageData* image = m_ResliceImageViewerCoronal->GetInput();
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
        int* windowSize = m_ResliceImageViewerCoronal->GetRenderWindow()->GetSize();
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
        m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->SetParallelScale(parallelScale);

        qDebug() << "Parallel scale set to:" << parallelScale;

//-------------------------------------------







//    double currentscale = m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->GetParallelScale();
//    m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->SetParallelScale(currentscale/2.5); //0.8

    //01-10-2024 //adjust zoom
    // 5. Reset the camera and clipping range for proper rendering
    //m_ResliceImageViewerCoronal->GetRenderer()->ResetCameraClippingRange();


    //m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->Zoom(2); //prev 1.2
    m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->Roll(-180);
    m_ResliceImageViewerCoronal->GetRenderer()->AddViewProp(cornerAnnotation);//parvathy
    m_ResliceImageViewerCoronal->GetRenderer()->AddActor(txtActorL);//parvathy
    m_ResliceImageViewerCoronal->GetRenderer()->AddActor(txtActorM);//parvathy
    m_ResliceImageViewerCoronal->GetRenderer()->AddActor(txtActorS);//parvathy
    m_ResliceImageViewerCoronal->GetRenderer()->AddActor(txtActorI);//parvathy




    //commented by anagha 27-09-2024

//    QString FileName = QDir::currentPath()+"/Plan/Viewer/free_head.obj";
//    QByteArray ba = FileName.toLatin1(); // Or str.toUtf8() for UTF-8 encoding
//    const char* cstr = ba.data();

//    readerObjCoronal->SetFileName(cstr);
//    readerObjCoronal->Update();
//    //    qDebug()<<"Filename"<<FileName;

//    mapperCoronal->SetInputConnection(readerObjCoronal->GetOutputPort());

//    m_ObjActorCoronal->SetMapper(mapperCoronal);
//    m_ObjActorCoronal->GetProperty()->SetColor(1.0, 0.5, 0.0); // Set your desired color

//    // Apply transformations to align the OBJ actor
//    transformCoronal->Translate(m_ObjActorCoronal->GetCenter());
//    transformCoronal->RotateWXYZ(90, 1, 0, 0);
//    transformCoronal->RotateWXYZ(180, 0, 0, 1);

//    m_ObjActorCoronal->SetUserTransform(transformCoronal);
//    m_ObjActorCoronal->GetProperty()->SetRepresentationToWireframe();

//    m_OrientationMarkerWidgetCoronal->SetOrientationMarker(m_ObjActorCoronal);
//    m_OrientationMarkerWidgetCoronal->SetInteractor(m_InteractionCoronal);
//    m_OrientationMarkerWidgetCoronal->SetViewport(0.8, 0.0, 1.0, 0.2);
////    m_OrientationMarkerWidgetCoronal->SetEnabled(1);
//    m_OrientationMarkerWidgetCoronal->InteractiveOff();

       m_InteractionCoronal->SetInteractorStyle(style_custom);


    m_InteractionCoronal->Initialize();
    m_ResliceImageViewerCoronal->Render();

}

void ClassCoronalView::ExecuteCoronal(vtkObject *caller, unsigned long eventId, void *callData)
{
    // to handle point selection event
    qDebug()<<" right button pressed in coronal ";

    int axialpickedpt[2];
    m_RenderWindowCoronal->GetInteractor()->GetEventPosition(axialpickedpt);

    vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
    picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_RenderWindowCoronal->GetRenderers()->GetFirstRenderer());

    double pickedPosition[3];
    picker->GetPickPosition(pickedPosition);
    std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

    qDebug()<< "Picked position: ("
              << pickedPosition[0] << ", "
              << pickedPosition[1] << ", "
              << pickedPosition[2] << ")" ;

    emit signalPickedPtCoronal(point);
}
