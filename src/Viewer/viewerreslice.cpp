#include "viewerreslice.h"
vtkStandardNewMacro(CusIntrImageStyle);
viewerReslice::viewerReslice(QWidget *parent) : QWidget(parent)
{
     m_QVTKOpenGLWidgetCom= new QVTKOpenGLWidget;
     m_objWidget = new Widget;
     QHBoxLayout *qlCentral = new QHBoxLayout;
     qlCentral->addWidget(m_objWidget, 3);
     qlCentral->addWidget(m_QVTKOpenGLWidgetCom, 97);
     m_QVTKOpenGLWidgetCom->SetRenderWindow(m_RenderWindowCom);
    m_ResliceImageViewerCom->SetRenderWindow(m_QVTKOpenGLWidgetCom->GetRenderWindow());
    m_QVTKOpenGLWidgetCom->GetRenderWindow()->SetInteractor(m_InteractionCom);
    m_ResliceImageViewerCom->SetupInteractor(m_QVTKOpenGLWidgetCom->GetRenderWindow()->GetInteractor());
     m_ResliceImageViewerCom->GetInteractor()->SetInteractorStyle(m_objCusIntrImageStyle);


//    m_RenderWindowCom->SetInteractor(m_InteractionCom);

//    m_QVTKOpenGLWidgetCom->SetRenderWindow(m_RenderWindowCom);
    //    this->m_VTKWidgetAxial->SetRenderWindow(m_ResliceImageViewerAxial->GetRenderWindow());
//    m_ResliceImageViewerCom->SetRenderWindow(m_QVTKOpenGLWidgetCom->GetRenderWindow());






//     m_objCusIntrImageStyle->AddObserver(vtkCommand::MouseMoveEvent, callback);
//       m_objCusIntrImageStyle->AddObserver(vtkCommand::LeftButtonPressEvent, callback);
//       m_objCusIntrImageStyle->AddObserver(vtkCommand::LeftButtonReleaseEvent, callback);



    connect(m_objWidget->m_pqbDistance, &ControlButton::Selected, this,  &::viewerReslice::MeasureDistanceSelected);

    connect(this, SIGNAL(GraphicalAnnotationClicked()),
            m_objCusIntrImageStyle, SLOT(GraphicalAnnotationSelected()));
    this->setLayout(qlCentral);
}

void viewerReslice::setInput(vtkDICOMImageReader *reader)
{

    m_ReaderCom=reader;
    m_ResliceImageViewerCom->SetInputData(m_ReaderCom->GetOutput());




    int *curSlice= reader->GetDataExtent();

}

void viewerReslice::setCrossHair( int orientation,bool blCrossHair)
{
    if(blCrossHair)
    {
        m_ResliceImageViewerCom->SetResliceCursor(m_ResliceImageViewerCom->GetResliceCursor());
        rep->GetResliceCursorActor()->GetCursorAlgorithm()->SetReslicePlaneNormal(orientation);
        m_ResliceImageViewerCom->GetResliceCursor()->SetHoleWidthInPixels(20);
        m_ResliceImageViewerCom->SetSliceOrientationToXY(); // Axial view
        // m_ResliceImageViewerAxial->SetSliceOrientation(2);
        m_ResliceImageViewerCom->SetResliceModeToOblique();
        m_ResliceImageViewerCom->SetSlice(250);
        m_ResliceImageViewerCom->GetResliceCursorWidget()->SetEnabled(1);
//        m_ResliceImageViewerCom->GetInteractor()->SetInteractorStyle(m_ActorStyleCom);

    }
    renderAll();

}

void viewerReslice::renderAll()
{
    m_ResliceImageViewerCom->Render();
    m_ResliceImageViewerCom->GetRenderer()->ResetCamera();
    m_ResliceImageViewerCom->GetRenderer()->GetActiveCamera()->Zoom(1.2);
    m_ResliceImageViewerCom->GetInteractor()->Initialize();
//    m_InteractionCom->Initialize();
}

void viewerReslice::CreateWin()
{

}

void viewerReslice::MeasureDistanceSelected()
{

    qDebug()<<"MeasureDistanceSelected";

    //    m_pvtkDistanceWidget = vtkSmartPointer<vtkDistanceWidget>::New();
    //    // Create the widget and its representation
    //    m_pPointDistHandleRepresentation2D = vtkSmartPointer<vtkPointHandleRepresentation2D>::New();
    //    m_pvtkDistRepresentation2D = vtkSmartPointer<vtkDistanceRepresentation2D> ::New();
    //    m_pvtkDistRepresentation2D->SetHandleRepresentation(m_pPointDistHandleRepresentation2D);

    //    m_pvtkDistanceWidget->SetInteractor(m_QVTKOpenGLWidgetCom->GetInteractor());
    //    m_pvtkDistanceWidget->CreateDefaultRepresentation();
    //    m_pvtkDistanceWidget->GetRepresentation()->DragableOn();

    //    static_cast<vtkDistanceRepresentation *>(m_pvtkDistanceWidget->GetRepresentation())
    //      ->SetLabelFormat("%-#7.1lf mm");//("%-#6.3g mm");
    //    m_pvtkDistRepresentation2D->GetAxisProperty()->SetColor(255,255,0);//Yellow color
    //    m_pvtkDistRepresentation2D->GetAxis()->GetTitleTextProperty()->SetColor(1,1,0);//Yellow color
    //    m_pvtkDistanceWidget->SetRepresentation(m_pvtkDistRepresentation2D);

    //    m_nDistMeasureEnabled=1;//For Indicating distance Widget is on
    //    m_pvtkDistanceWidget->On();
    emit GraphicalAnnotationClicked();
}
