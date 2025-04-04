#ifndef CLASSSAGITTALVIEW_H
#define CLASSSAGITTALVIEW_H



#include <QVTKOpenGLWidget.h>
//#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>
#include <QDir>



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
#include "vtkCornerAnnotation.h"
#include "vtkNamedColors.h"
#include "vtkTextProperty.h"
#include "vtkTextActor.h"

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
#include <QDebug>
#include <array>

#include <QMouseEvent> //d

#include "src/Plan/Viewer/MPR/CustomInteractorStyle.h"//d

class ClassSagittalView : public QWidget
{
    Q_OBJECT
public:
    explicit ClassSagittalView(QWidget *parent = nullptr);
    //ClassSagittalView *m_objsagittalView;
    vtkSmartPointer<vtkResliceImageViewer> m_ResliceImageViewerSagittal= vtkSmartPointer<vtkResliceImageViewer>::New();

    vtkSmartPointer<vtkDICOMImageReader> m_ReaderSagittal = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballActor> actorstyle = vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_InteractionSagittal = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_RenderWindowSagittal = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


    void sagittalView(vtkDICOMImageReader *reader);


//    QVTKOpenGLNativeWidget *m_VTKWidgetSagittal = new QVTKOpenGLNativeWidget();

//    ClassAxialView *m_objaxialView;
    QVTKOpenGLWidget *m_QVTKOpenGLWidgetSagital;


    vtkResliceCursorLineRepresentation* rep;


    vtkSmartPointer<vtkOBJReader> readerObjSagittal = vtkSmartPointer<vtkOBJReader> ::New();
    vtkSmartPointer<vtkPolyDataMapper> mapperSagittal = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> m_ObjActorSagittal = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkTransform> transformSagittal = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkAxesActor> axesSagittal = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> m_OrientationMarkerWidgetSagittal = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

    void ExecuteSagittal(vtkObject *caller, unsigned long eventId, void *callData);
    //d
        vtkSmartPointer<CustomInteractorStyle> style_custom = vtkSmartPointer<CustomInteractorStyle>::New();

        double defaultWindow;
        double defaultLevel;



private:
    bool leftonly;
    bool rightonly;
signals:
    void signalPickedPtSagittal(std::array<double, 3> point);
    void sagSlice(double* sag_center);


    //d
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {


//            if (this->windowState() & Qt::WindowFullScreen)
//            {
                qDebug()<<"1";
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

        // Call the base class implementation
        QWidget::mouseDoubleClickEvent(event);
    }
    void mousePressEvent(QMouseEvent *event) override
        {
        if(event->buttons() & Qt::LeftButton && event->buttons() & Qt::RightButton  )
                    {
                        qDebug()<<"nothing";
                        leftonly= false;
                        rightonly=false;
                        //return;
                        // QWidget::mousePressEvent(event);
                    }

        else if(event->button()== Qt::RightButton)
        {
            if(rightonly==true)
            {
                return;
            }
        }
//           else  if (event->button() == Qt::LeftButton)
//        {
//            if(leftonly=true)
//            {

//                qDebug() << "Sagital Left ";

//                int axialpickedpt[2];
//                m_RenderWindowSagittal->GetInteractor()->GetEventPosition(axialpickedpt);

//                vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
//                picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_RenderWindowSagittal->GetRenderers()->GetFirstRenderer());

//                double pickedPosition[3];
//                picker->GetPickPosition(pickedPosition);
//                std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

//                qDebug()<< "Picked position: ("
//                          << pickedPosition[0] << ", "
//                          << pickedPosition[1] << ", "
//                          << pickedPosition[2] << ")" ;

//                leftonly=false;
//                emit signalPickedPtSagittal(point);

//             leftonly=false;
//}
//            leftonly=false;
//           }


            QWidget::mousePressEvent(event);
        }
            void wheelEvent(QWheelEvent *event) override
               {

                int currentslice=m_ResliceImageViewerSagittal->GetSlice();
                int maxSlice = m_ResliceImageViewerSagittal->GetSliceMax();
                int minSlice = m_ResliceImageViewerSagittal->GetSliceMin();

                   if (event->angleDelta().y() > 0) {
                      // qDebug() << "Mouse wheel rolled up ";
                       if (currentslice < maxSlice) {
                                      m_ResliceImageViewerSagittal->SetSlice(currentslice + 1);
                                      qDebug() << "Moving to next slice: " << currentslice + 1;
                                  }

                   } else {
                     //  qDebug() << "Mouse wheel rolled down ";
                       if (currentslice > minSlice) {
                                      m_ResliceImageViewerSagittal->SetSlice(currentslice - 1);
                                     // qDebug() << "Moving to prev slice: " << currentslice - 1;
                                  }

                   }
//                 vtkImageData* imageData = m_ResliceImageViewerSagittal->GetInput();
//                 double origin[3];
//                    double spacing[3];
//                    imageData->GetOrigin(origin);
//                    imageData->GetSpacing(spacing);
//                     qDebug() << "ori: " <<origin[0]<<origin[1]<<origin[2];
//                      qDebug() << "spac: " <<spacing[0]<<spacing[1]<<spacing[2];

                   double* sag_center;
                   sag_center = m_ResliceImageViewerSagittal->GetResliceCursor()->GetCenter();
                 qDebug() << "sag_center: " <<sag_center[0]<<sag_center[1]<<sag_center[2];
                emit sagSlice(sag_center);

                QWidget::wheelEvent(event);
               }

};

#endif // CLASSSAGITTALVIEW_H
