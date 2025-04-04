#include "classaxialview.h"
#include <QVBoxLayout>
#include <QDebug>

ClassAxialView::ClassAxialView(QWidget *parent) : QWidget(parent)
{
    //Axial
    m_ResliceImageViewerAxial->SetRenderWindow(m_RenderWindowAxial);
    m_ResliceImageViewerAxial->SetupInteractor(m_InteractionAxial);


    m_QVTKOpenGLWidgetAxial= new QVTKOpenGLWidget;
    m_QVTKOpenGLWidgetAxial->SetRenderWindow(m_RenderWindowAxial);
    //m_QVTKOpenGLWidgetAxial->setBaseSize(688,463);
    m_RenderWindowAxial->SetInteractor(m_InteractionAxial);

    m_ResliceImageViewerAxial->SetupInteractor(m_RenderWindowAxial->GetInteractor());

    auto callback = vtkSmartPointer<vtkCallbackCommand>::New();
    callback->SetCallback([](vtkObject* caller, unsigned long eventId, void* clientData, void* callData)
    {
        static_cast<ClassAxialView*>(clientData)->ExecuteAxial(caller, eventId, callData);
    });
    callback->SetClientData(this);

    //m_RenderWindowAxial->GetInteractor()->AddObserver(vtkCommand::RightButtonPressEvent, callback);

    QVBoxLayout *LayAxial= new QVBoxLayout;
    LayAxial->addWidget(m_QVTKOpenGLWidgetAxial);
    this->setLayout(LayAxial);
}


//this is not used ; instead QT mouse event is used for callback
void ClassAxialView::ExecuteAxial(vtkObject* caller, unsigned long eventId, void* callData)
{
    // to handle point selection event
    qDebug()<<" right button pressed in axial ";

    int axialpickedpt[2];
    m_RenderWindowAxial->GetInteractor()->GetEventPosition(axialpickedpt);

    vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
    picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_RenderWindowAxial->GetRenderers()->GetFirstRenderer());

    double pickedPosition[3];
    picker->GetPickPosition(pickedPosition);
    std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

    qDebug()<< "Picked position: ("
              << pickedPosition[0] << ", "
              << pickedPosition[1] << ", "
              << pickedPosition[2] << ")" ;

    emit signalPickedPtAxial(point);
    qDebug()<<"***********************testing callback in axial";


}

void ClassAxialView::axialView(vtkDICOMImageReader *reader, QString selKnee)
{


   //Parvathy
    //adding the corner annotation
     vtkNew<vtkNamedColors> colors;
     vtkNew<vtkCornerAnnotation> cornerAnnotation;
     cornerAnnotation->SetLinearFontScaleFactor(3);
     cornerAnnotation->SetNonlinearFontScaleFactor(1);
     cornerAnnotation->SetMaximumFontSize(20);
     cornerAnnotation->SetText(2, "Transverse");
     cornerAnnotation->GetTextProperty()->SetColor(
          colors->GetColor3d("White").GetData());
     cornerAnnotation->GetTextProperty()->BoldOn();



     vtkNew<vtkTextActor> txtActorL;
     txtActorL->GetTextProperty()->SetFontSize(20);
     txtActorL->SetTextScaleModeToNone();
    // txtActorL->SetTextScaleMode(3);   
     txtActorL->SetInput("L");

     vtkNew<vtkTextActor> txtActorM;
     txtActorM->GetTextProperty()->SetFontSize(20);
     txtActorM->SetTextScaleModeToNone();
     //txtActorM->SetTextScaleMode(3);    
     txtActorM->SetInput("M");

     vtkNew<vtkTextActor> txtActorA;
     txtActorA->GetTextProperty()->SetFontSize(20);
     txtActorA->SetTextScaleModeToNone();
    // txtActorA->SetTextScaleMode(3);
     txtActorA->SetDisplayPosition(350,350);
     txtActorA->SetInput("A");

     vtkNew<vtkTextActor> txtActorP;
     txtActorP->GetTextProperty()->SetFontSize(20);
     txtActorP->SetTextScaleModeToNone();
    // txtActorP->SetTextScaleMode(3);
     txtActorP->SetDisplayPosition(350,5);
     txtActorP->SetInput("P");



//works but opposit positions
//          if (selKnee == "Right Knee")
//          {
//              txtActorM->SetDisplayPosition(0,155);
//              txtActorL->SetDisplayPosition(this->width()-15,155);

//          }else if(selKnee == "Left Knee")
//          {
//              txtActorM->SetDisplayPosition(this->width()-15,155);
//              txtActorL->SetDisplayPosition(0,155);
//          }



     if (selKnee == "Right Knee")
     {
         txtActorL->SetDisplayPosition(0,155);
         txtActorM->SetDisplayPosition(this->width()-15,155);

     }else if(selKnee == "Left Knee")
     {
         txtActorL->SetDisplayPosition(this->width()-15,155);
         txtActorM->SetDisplayPosition(0,155);
     }






//     if (selKnee == "left Knee")
//     {
//         //txtActorM->SetDisplayPosition(0,155);
//         txtActorM->SetDisplayPosition(0,70);
//         txtActorL->SetDisplayPosition(this->width()-15,155);

//     }else if(selKnee == "Right Knee")
//     {
//         txtActorM->SetDisplayPosition(this->width()-15,155);
//         txtActorL->SetDisplayPosition(0,155);
//     }


     //      if (selKnee == "Left Knee")
     //      {
     //          txtActorM->SetDisplayPosition(0,155);
     //          txtActorL->SetDisplayPosition(this->width()-15,155);

     //      }else if(selKnee == "Right Knee")
     //      {
     //          txtActorM->SetDisplayPosition(this->width()-15,155);
     //          txtActorL->SetDisplayPosition(0,155);
     //      }





    m_ResliceImageViewerAxial->SetInputData(reader->GetOutput());

    rep = vtkResliceCursorLineRepresentation::SafeDownCast(
                m_ResliceImageViewerAxial->GetResliceCursorWidget()->GetRepresentation());
    rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(2);
//    rep->GetResliceCursorActor()->VisibilityOff();

    //added
    m_ResliceImageViewerAxial->SetResliceCursor(m_ResliceImageViewerAxial->GetResliceCursor());

    m_ResliceImageViewerAxial->GetResliceCursor()->SetHoleWidthInPixels(10000); // changed from 20 to 500 rupika
    m_ResliceImageViewerAxial->SetSliceOrientationToXY();
    m_ResliceImageViewerAxial->SetResliceModeToOblique();
    m_ResliceImageViewerAxial->GetResliceCursorWidget()->SetEnabled(1);

    // Render the reslice image viewer
    m_ResliceImageViewerAxial->Render();

    m_ResliceImageViewerAxial->GetRenderer()->ResetCamera();



        //------------ setting zoom ------------------//
            vtkImageData* image = m_ResliceImageViewerAxial->GetInput();
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
                int* windowSize = m_ResliceImageViewerAxial->GetRenderWindow()->GetSize();
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
                m_ResliceImageViewerAxial->GetRenderer()->GetActiveCamera()->SetParallelScale(parallelScale);

                qDebug() << "Parallel scale set to:" << parallelScale;

        //-------------------------------------------









    //m_ResliceImageViewerAxial->GetRenderer()->GetActiveCamera()->Zoom(1.2);


    m_ResliceImageViewerAxial->GetRenderer()->AddViewProp(cornerAnnotation);//parvathy
    m_ResliceImageViewerAxial->GetRenderer()->AddActor(txtActorL);//parvathy
    m_ResliceImageViewerAxial->GetRenderer()->AddActor(txtActorM);//parvathy
    m_ResliceImageViewerAxial->GetRenderer()->AddActor(txtActorA);//parvathy
    m_ResliceImageViewerAxial->GetRenderer()->AddActor(txtActorP);//parvathy


    //commented by anagha 27-09-2024

//    // Load and set up the OBJ model
//    QString FileName = QDir::currentPath()+"/Plan/Viewer/free_head.obj";
//    QByteArray ba = FileName.toLatin1(); // Or str.toUtf8() for UTF-8 encoding
//    const char* cstr = ba.data();
//    readerObjAxial->SetFileName(cstr);
//    readerObjAxial->Update();

//    mapperAxial->SetInputConnection(readerObjAxial->GetOutputPort());

//    m_ObjActorAxial->SetMapper(mapperAxial);
//    m_ObjActorAxial->GetProperty()->SetColor(1.0, 0.5, 0.0);
//    m_ObjActorAxial->SetVisibility(true);

//    // Apply transformations to align the OBJ actor
//    transformAxial->Translate(m_ObjActorAxial->GetCenter());
//    transformAxial->RotateWXYZ(90, 1, 0, 0);
//    transformAxial->RotateWXYZ(180, 0, 1, 0);
//    m_ObjActorAxial->SetUserTransform(transformAxial);
//    m_ObjActorAxial->GetProperty()->SetRepresentationToWireframe();

//    // Set up the orientation marker widget
//    m_OrientationMarkerWidgetAxial->SetOrientationMarker(m_ObjActorAxial);
//    m_OrientationMarkerWidgetAxial->SetInteractor(m_InteractionAxial);
//    m_OrientationMarkerWidgetAxial->SetViewport(0.8, 0.0, 1.0, 0.2);// Change the viewport as needed
////    m_OrientationMarkerWidgetAxial->SetEnabled(1);
//    m_OrientationMarkerWidgetAxial->InteractiveOff();


    //d
      m_InteractionAxial->SetInteractorStyle(style_custom);


    // Render everything
    m_RenderWindowAxial->Render();
    m_InteractionAxial->Initialize();
    //m_VTKWidgetAxial->show();
}

void ClassAxialView::drawDistance()
{
    qDebug()<<"drawDistance";
    qDebug() << "MeasureDistanceSelected";

    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    distanceWidget->SetInteractor(m_RenderWindowAxial->GetInteractor());

    vtkSmartPointer<vtkDistanceRepresentation2D> representation = vtkSmartPointer<vtkDistanceRepresentation2D>::New();
    distanceWidget->SetRepresentation(representation);

    // Set initial placement (this can be adjusted based on specific needs)
    double pos1[]={0.0, 0.0, 0.0};
    double pos2[]={100.0, 100.0, 0.0};
    //      representation->SetPoint1WorldPosition(pos1);
    //      representation->SetPoint2WorldPosition(pos2);

    representation->SetPoint1DisplayPosition(pos1);
    representation->SetPoint1DisplayPosition(pos2);

    //    vtkNew<vtkDistanceWidget> distanceWidget;
    //      distanceWidget->SetInteractor(m_RenderWindowAxial->GetInteractor());
    //      distanceWidget->CreateDefaultRepresentation();
    //      static_cast<vtkDistanceRepresentation*>(distanceWidget->GetRepresentation())
    //          ->SetLabelFormat("%-#6.3g mm");
    distanceWidget->On();

    //    // Create a new distance widget each time the button is clicked
    //    vtkSmartPointer<vtkDistanceWidget> distanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    //    vtkSmartPointer<vtkPointHandleRepresentation2D> pointHandleRepresentation2D = vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
    //    vtkSmartPointer<vtkDistanceRepresentation2D> distanceRepresentation2D = vtkSmartPointer<vtkDistanceRepresentation2D>::New();

    //    distanceRepresentation2D->SetHandleRepresentation(pointHandleRepresentation2D);
    //    distanceWidget->SetInteractor(m_QVTKOpenGLWidgetAxial->GetInteractor());
    //    distanceWidget->SetRepresentation(distanceRepresentation2D);

    //    distanceWidget->GetRepresentation()->DragableOn();
    //    static_cast<vtkDistanceRepresentation *>(distanceWidget->GetRepresentation())->SetLabelFormat("%-#7.1lf mm");
    //    distanceRepresentation2D->GetAxisProperty()->SetColor(255, 255, 0);
    //    distanceRepresentation2D->GetAxis()->GetTitleTextProperty()->SetColor(1, 1, 0);



    //    m_distanceWidgets.push_back(distanceWidget);

    //    // Activate the widget
    //    distanceWidget->On();

    //     m_ResliceImageViewerAxial->GetRenderer()->ResetCamera();
    m_InteractionAxial->Initialize();
    m_InteractionAxial->Start();
    m_ResliceImageViewerAxial->Render();
    distanceWidgets.push_back(distanceWidget);

    // emit GraphicalAnnotationClicked();
}


