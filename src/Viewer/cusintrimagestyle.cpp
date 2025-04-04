#include "cusintrimagestyle.h"
#include <QDebug>
#include <QApplication>

#include <sstream>

//CusIntrImageStyle::CusIntrImageStyle(QWidget *parent) : QWidget(parent)
//{

//}

CusIntrImageStyle::CusIntrImageStyle()
{

}

CusIntrImageStyle::~CusIntrImageStyle()
{

}

void CusIntrImageStyle::SetImageViewer(vtkResliceImageViewer *pvtkImageViewer)
{
    //Set image viewer for the interaction syle
     m_pvtkImageViewer = pvtkImageViewer;
     //This is starting step in intializing the interation style.
//     SetDisplayInitialSliceFirst();
//     InitializeStyle();
//     vtkRuler->VisibilityOff();
     //     vtkRulerTextActor->VisibilityOff();
}

void CusIntrImageStyle::SetVtkWidget(QVTKOpenGLWidget *pvtkWidget)
{
     m_pvtkWidget = pvtkWidget;
}

void CusIntrImageStyle::SetConerAntnStatus(bool blCornerAnnotationStatus)
{
    if(blCornerAnnotationStatus)
    {
        m_eCornerAnnotationStatus = CORNER_ANNOTATIONS_ON;
    }
    else
    {
       m_eCornerAnnotationStatus = CORNER_ANNOTATIONS_OFF;
    }
}

void CusIntrImageStyle::getDistMeasurement()
{

}

void CusIntrImageStyle::OnLeftButtonDown()
{
    qDebug()<<"OnLeftButtonDown";
    if(m_eGraphAnnotationEnableStatus == GRAPHICAL_ANNOTATIONS_DISABLED)
    {
        m_eMouseButtonType = LEFT_BUTTON;
        vtkInteractorStyleImage::OnLeftButtonDown();
    }
    Interactor->Render();
}

void CusIntrImageStyle::OnLeftButtonUp()
{
    m_eGraphAnnotationEnableStatus = GRAPHICAL_ANNOTATIONS_DISABLED;
    m_eMouseButtonType = NONE;
    vtkInteractorStyleImage::OnLeftButtonUp();
}

void CusIntrImageStyle::OnMouseMove()
{
     qDebug()<<"OnMouseMove";
     vtkInteractorStyleImage::OnMouseMove();
}

void CusIntrImageStyle::OnMiddleButtonDown()
{
     vtkInteractorStyleImage::OnMiddleButtonDown();
}

void CusIntrImageStyle::OnMiddleButtonUp()
{
     vtkInteractorStyleImage::OnMiddleButtonUp();
}

void CusIntrImageStyle::OnRightButtonDown()
{
     vtkInteractorStyleImage::OnRightButtonDown();
}

void CusIntrImageStyle::OnRightButtonUp()
{
    vtkInteractorStyleImage::OnRightButtonUp();
}

void CusIntrImageStyle::GraphicalAnnotationSelected()
{
     qDebug()<<"GraphicalAnnotationSelected";
      m_eGraphAnnotationEnableStatus = GRAPHICAL_ANNOTATIONS_ENABLED;
}

//void CusIntrImageStyle::SetConerAntn(MyVtkCornerAnnotations *pMyVtkCornerAnnotations)
//{
//     m_pvtkCornerAnnotations = pMyVtkCornerAnnotations;
//}
