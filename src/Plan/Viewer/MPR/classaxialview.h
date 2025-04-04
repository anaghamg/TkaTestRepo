#ifndef CLASSAXIALVIEW_H
#define CLASSAXIALVIEW_H

#include <QVTKOpenGLWidget.h>
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
#include <vtkDistanceRepresentation.h>
#include <vtkDistanceWidget.h>
#include <vtkNamedColors.h>
#include <vtkDistanceRepresentation2D.h>
#include <vtkProperty2D.h>
#include <vtkAxisActor2D.h>
#include <vtkTextProperty.h>
#include <vector>


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
#include "vtkEventQtSlotConnect.h"
#include "vtkCommand.h"
#include "QObject"
#include "vtkObject.h"
#include <qdebug.h>
#include <array>
#include "vtkCornerAnnotation.h"
#include "vtkTextActor.h"

//d
#include <QMouseEvent>
#include "src/Plan/Viewer/MPR/CustomInteractorStyle.h"

class ClassAxialView : public QWidget
{
    Q_OBJECT
public:
    explicit ClassAxialView(QWidget *parent = nullptr);

    vtkSmartPointer<vtkResliceImageViewer>m_ResliceImageViewerAxial = vtkSmartPointer<vtkResliceImageViewer>::New();
    vtkSmartPointer<vtkDICOMImageReader> m_ReaderAxial = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballActor> m_ActorStyleAxial = vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_InteractionAxial = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
    void axialView(vtkDICOMImageReader *reader, QString m_qstrselKnee);
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_RenderWindowAxial = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    QVTKOpenGLWidget *m_QVTKOpenGLWidgetAxial;
    vtkResliceCursorLineRepresentation* rep;

    vtkSmartPointer<vtkOBJReader> readerObjAxial = vtkSmartPointer<vtkOBJReader> ::New();
    vtkSmartPointer<vtkPolyDataMapper> mapperAxial = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> m_ObjActorAxial = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkTransform> transformAxial = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkAxesActor> axesAxial = vtkSmartPointer<vtkAxesActor>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> m_OrientationMarkerWidgetAxial = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

    std::vector<vtkSmartPointer<vtkDistanceWidget>> distanceWidgets;

    void ExecuteAxial(vtkObject* caller, unsigned long eventId, void* callData);

    //d
    vtkSmartPointer<CustomInteractorStyle> style_custom = vtkSmartPointer<CustomInteractorStyle>::New();
    double defaultWindow;
    double defaultLevel;


signals:
    void signalPickedPtAxial(std::array<double, 3> point);

    void axeSlice(double* newSlice);//d

public slots:
    void drawDistance();

private:
    bool leftonly;//d


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

            qDebug()<<"***********************testing callback in axial";

            emit signalPickedPtAxial(point);


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
        //           else  if (event->button() == Qt::LeftButton)
        //        {
        //            if(leftonly=true)
        //            {
        //                qDebug() << "Axial left";
        //                int axialPickedPt[2];
        //                           m_RenderWindowAxial->GetInteractor()->GetEventPosition(axialPickedPt);

        //                           // Use a vtkPropPicker to pick the 3D point in the scene
        //                           vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
        //                           picker->Pick(axialPickedPt[0], axialPickedPt[1], 0, m_RenderWindowAxial->GetRenderers()->GetFirstRenderer());

        //                           // Get the picked 3D position
        //                           double pickedPosition[3];
        //                           picker->GetPickPosition(pickedPosition);
        //                           std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

        //                           // Output the picked position
        //                           qDebug() << "Picked position: ("
        //                                    << pickedPosition[0] << ", "
        //                                    << pickedPosition[1] << ", "
        //                                    << pickedPosition[2] << ")";
        //                           emit signalPickedPtAxial(point);

        //            }
        //         }

        QWidget::mousePressEvent(event); // Call the base class to ensure event propagation
    }

    void wheelEvent(QWheelEvent *event) override
    {
        int currentslice=m_ResliceImageViewerAxial->GetSlice();
        int maxSlice = m_ResliceImageViewerAxial->GetSliceMax();
        int minSlice = m_ResliceImageViewerAxial->GetSliceMin();

        if (event->angleDelta().y() > 0) {
            qDebug() << "Mouse wheel rolled up ";
            if (currentslice < maxSlice) {
                m_ResliceImageViewerAxial->SetSlice(currentslice + 1);
                qDebug() << "Moving to next slice: " << currentslice + 1;
            }

        } else {
            qDebug() << "Mouse wheel rolled down ";
            if (currentslice > minSlice) {
                m_ResliceImageViewerAxial->SetSlice(currentslice - 1);
                qDebug() << "Moving to prev slice: " << currentslice - 1;
            }

        }

        double* axe_center;
        axe_center = m_ResliceImageViewerAxial->GetResliceCursor()->GetCenter();
        qDebug() << "axe_center: " <<axe_center[0]<<axe_center[1]<<axe_center[2];
        emit axeSlice(axe_center);

        QWidget::wheelEvent(event);
    }



};

#endif // CLASSAXIALVIEW_H
