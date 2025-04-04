#ifndef CLASSCORONALVIEW_H
#define CLASSCORONALVIEW_H

//#include "classaxialview.h"

#include <QVTKOpenGLWidget.h>
//#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include <QDir>
#include <QDebug>

#include <vtkCamera.h>
#include <vtkCellPicker.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include "vtkDICOMImageReader.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include "vtkImageData.h"
#include <vtkImagePlaneWidget.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkPlaneWidget.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkResliceCursor.h>
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursorRepresentation.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceImageViewer.h"
#include "vtkSmartPointer.h"
#include "vtkVolumeProperty.h"
#include "vtkVolume.h"

#include <vtkActor.h>
#include <vtkAlgorithm.h>
#include <vtkAlgorithmOutput.h>
#include <vtkAssembly.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCallbackCommand.h>
#include <vtkCellPicker.h>
#include <vtkColorTransferFunction.h>
#include <vtkCommand.h>
#include <vtkExecutive.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include "vtkDICOMImageReader.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInformation.h>
#include "vtkImageData.h"
#include <vtkImagePlaneWidget.h>
#include <vtkInteractorStyleImage.h>
#include <vtkMath.h>
#include <vtkOBJReader.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkPlaneWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPropPicker.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkResliceCursor.h>
#include "vtkResliceCursorActor.h"
#include "vtkResliceCursorLineRepresentation.h"
#include "vtkResliceCursorPolyDataAlgorithm.h"
#include "vtkResliceCursorRepresentation.h"
#include "vtkResliceCursorWidget.h"
#include "vtkResliceImageViewer.h"
#include "vtkSmartPointer.h"
#include "vtkTransform.h"
#include <vtkViewport.h>
#include "vtkVolumeProperty.h"
#include "vtkVolume.h"
#include <vtkEventQtSlotConnect.h>
#include <array>
#include "vtkCornerAnnotation.h"
#include "vtkNamedColors.h"
#include "vtkTextProperty.h"
#include "vtkTextActor.h"
#include "vtkImageFlip.h"

//d
#include <QMouseEvent>
#include "src/Plan/Viewer/MPR/CustomInteractorStyle.h"

class ClassCoronalView : public QWidget
{
    Q_OBJECT
public:
    explicit ClassCoronalView(QWidget *parent = nullptr);

    vtkSmartPointer<vtkResliceImageViewer>m_ResliceImageViewerCoronal = vtkSmartPointer<vtkResliceImageViewer>::New();
    vtkSmartPointer<vtkDICOMImageReader> m_ReaderCoronal = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballActor> m_ActorStyleCoronal = vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_InteractionCoronal = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_RenderWindowCoronal = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    void coronalView(vtkDICOMImageReader *reader, QString selKnee);
    QVTKOpenGLWidget *m_QVTKOpenGLWidgetCoronal;

    vtkResliceCursorLineRepresentation* rep;

    vtkSmartPointer<vtkOBJReader> readerObjCoronal = vtkSmartPointer<vtkOBJReader> ::New();
    vtkSmartPointer<vtkPolyDataMapper> mapperCoronal = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> m_ObjActorCoronal = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkTransform> transformCoronal = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkAxesActor> axesCoronal = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> m_OrientationMarkerWidgetCoronal = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

    void ExecuteCoronal(vtkObject* caller, unsigned long eventId, void* callData);


    //d
       vtkSmartPointer<CustomInteractorStyle> style_custom = vtkSmartPointer<CustomInteractorStyle> ::New();
       double defaultWindow;
       double defaultLevel;
       int imgwidth;
       double pixelspacing;
       double offsetcoronal;

signals:
    void signalPickedPtCoronal(std::array<double, 3> point );
    void  pointinCoronal(bool coronal);

    //d
    void corSlice(double* newslice);



    //d
private:
    bool leftonly;
    bool coronal = false;

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {


//            if (this->windowState() & Qt::WindowFullScreen)
//            {
                qDebug()<<"1";
                int axialpickedpt[2];
                                m_RenderWindowCoronal->GetInteractor()->GetEventPosition(axialpickedpt);

                                vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
                                picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_RenderWindowCoronal->GetRenderers()->GetFirstRenderer());

                                double pickedPosition[3];
                                picker->GetPickPosition(pickedPosition);

                               // std::array<double, 3> point = {286-pickedPosition[0], pickedPosition[1], pickedPosition[2]};
                                 std::array<double, 3> point = {offsetcoronal-pickedPosition[0], pickedPosition[1], pickedPosition[2]};

                                qDebug()<< "Picked position: ("
                                          << pickedPosition[0] << ", "
                                          << pickedPosition[1] << ", "
                                          << pickedPosition[2] << ")" ;

                                qDebug()<< "Picked point coronal: ("
                                          << point[0] << ", "
                                          << point[1] << ", "
                                          << point[2] << ")" ;

                          emit pointinCoronal(true);

                         emit signalPickedPtCoronal(point);

//            }
//            else
//            {
//                qDebug()<<"2";
//            }
        }

        // Call the base class implementation
        QWidget::mouseDoubleClickEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override
        {
        if(event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton  )
        {
            qDebug()<<"nothing";
            leftonly= false;
            //return;
        }
//        else  if (event->button() == Qt::LeftButton)
//            {
//            if(leftonly=true)
//                {
//                qDebug() << "Coronal Left ";
//                int axialpickedpt[2];
//                m_RenderWindowCoronal->GetInteractor()->GetEventPosition(axialpickedpt);

//                vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
//                picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_RenderWindowCoronal->GetRenderers()->GetFirstRenderer());

//                double pickedPosition[3];
//                picker->GetPickPosition(pickedPosition);
//                std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

//                qDebug()<< "Picked position: ("
//                          << pickedPosition[0] << ", "
//                          << pickedPosition[1] << ", "
//                          << pickedPosition[2] << ")" ;

//         emit signalPickedPtCoronal(point);
//            }

//        }
            QWidget::mousePressEvent(event); // Call the base class to ensure event propagation
        }


                     void wheelEvent(QWheelEvent *event) override
                           {
                            int currentslice=m_ResliceImageViewerCoronal->GetSlice();
                            int maxSlice = m_ResliceImageViewerCoronal->GetSliceMax();
                            int minSlice = m_ResliceImageViewerCoronal->GetSliceMin();

                               if (event->angleDelta().y() > 0) {
                                 // qDebug() << "Mouse wheel rolled up ";
                                   if (currentslice < maxSlice) {
                                                  m_ResliceImageViewerCoronal->SetSlice(currentslice + 1);
                                                  qDebug() << "Moving to next slice: " << currentslice + 1;
                                              }

                               } else {
                                 //  qDebug() << "Mouse wheel rolled down ";
                                   if (currentslice > minSlice) {
                                                  m_ResliceImageViewerCoronal->SetSlice(currentslice - 1);
                                                //  qDebug() << "Moving to prev slice: " << currentslice - 1;
                                              }

                               }
                               double* cor_center;
                               cor_center = m_ResliceImageViewerCoronal->GetResliceCursor()->GetCenter();
                             qDebug() << "cor_center: " <<cor_center[0]<<cor_center[1]<<cor_center[2];
                               emit corSlice(cor_center);


                               QWidget::wheelEvent(event);
                           }
};

#endif // CLASSCORONALVIEW_H
