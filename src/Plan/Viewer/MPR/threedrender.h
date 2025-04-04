#ifndef THREEDRENDER_H
#define THREEDRENDER_H

#include <QObject>
#include <QWidget>
#include <QVTKOpenGLWidget.h>
//#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>

#include "classaxialview.h"
#include <vtkCamera.h>
#include <vtkCellPicker.h>
#include <vtkColorTransferFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include "vtkDICOMImageReader.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include "vtkImageData.h"
#include "vtkImageReslice.h"
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
#include <vtkAutoInit.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkConnectivityFilter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkDataSetMapper.h>
#include <vtkNamedColors.h>
#include <vtkLookupTable.h>
#include <vtkScalarsToColors.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkSTLWriter.h>
#include "src/Plan/Viewer/MPR/d3CustomInteractorStyle.h"

#include <vtkFillHolesFilter.h>
#include <vtkFeatureEdges.h>


//VTK_MODULE_INIT(vtkRenderingOpenGL2) // VTK was built with vtkRenderingOpenGL2
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
//VTK_MODULE_INIT(vtkRenderingFreeType)

class ThreeDRender : public QWidget
{
    Q_OBJECT
public:
    explicit ThreeDRender(QWidget *parent = nullptr);

    void ThreeDView(vtkDICOMImageReader *reader);

    QVTKOpenGLWidget *m_VTK3DWidget;
    vtkSmartPointer<vtkDICOMImageReader> m_ReaderThreeD = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkImagePlaneWidget> planeWidget[3];
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_3DRenderWindow  =vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderer> m_3DRenderer = vtkSmartPointer<vtkRenderer>::New();

    void Execute3D(vtkObject *caller, unsigned long eventId, void *callData);


signals:
    void signalPickedPt3D(std::array<double, 3> point);
public:
    vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_3DInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkDICOMImageReader> femurreader = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkDICOMImageReader> tibiareader = vtkSmartPointer<vtkDICOMImageReader>::New();

    vtkNew<vtkActor> boneActorfemur;
    vtkNew<vtkActor> boneActortibia;
    vtkSmartPointer<vtkMarchingCubes> marchingCubesfemur = vtkSmartPointer<vtkMarchingCubes>::New();
    vtkSmartPointer<vtkMarchingCubes> marchingCubestibia = vtkSmartPointer<vtkMarchingCubes>::New();
    vtkSmartPointer<vtkActor> GetFemurActor();
    vtkSmartPointer<vtkActor> GetTibiaActor();
    vtkNew<vtkActor> boneActor;
    vtkNew<vtkPolyDataMapper> mapperfemur;
    void Femur3D();
    void Tibia3D();
    void RemoveBoneActor();
    int m_annotTabIndex = 0;

    QString m_qstrDcmFemur;
    QString m_qstrDcmTibia;
private:
    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    //vtkSmartPointer<vtkRenderWindowInteractor> m_3DInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkVolume> volume1 = vtkSmartPointer<vtkVolume>::New();

    vtkSmartPointer<vtkOBJReader> objReader = vtkSmartPointer<vtkOBJReader>::New();
    vtkSmartPointer<vtkActor> objActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkPolyDataMapper> objMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkOrientationMarkerWidget> orientationWidget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
    vtkSmartPointer<vtkCamera> objCamera = vtkSmartPointer<vtkCamera>::New();
    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

    vtkNew<vtkPolyDataConnectivityFilter> connectivityFilter;
    vtkNew<vtkLookupTable> boneLut;
    vtkNew<vtkNamedColors> colors;


//vtkSmartPointer<vtkActor> actor =vtkSmartPointer<vtkActor>::New();
//D
vtkSmartPointer<d3CustomInteractorStyle> adjust =vtkSmartPointer<d3CustomInteractorStyle> ::New();

vtkSmartPointer<vtkActor> actor =vtkSmartPointer<vtkActor>::New();private:
    bool leftonly;
protected:
    //    void mousePressEvent(QMouseEvent *event) override
    //        {
    //            if (event->button() == Qt::LeftButton) {
    //                qDebug() << "ThreeD Left ";

    //                int axialpickedpt[2];
    //                m_3DRenderWindow->GetInteractor()->GetEventPosition(axialpickedpt);

    //                vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
    //                picker->Pick(axialpickedpt[0], axialpickedpt[1], 0, m_3DRenderWindow->GetRenderers()->GetFirstRenderer());

    //                double pickedPosition[3];
    //                picker->GetPickPosition(pickedPosition);
    //                std::array<double, 3> point = {pickedPosition[0], pickedPosition[1], pickedPosition[2]};

    //                qDebug()<< "Picked position: ("
    //                          << pickedPosition[0] << ", "
    //                          << pickedPosition[1] << ", "
    //                          << pickedPosition[2] << ")" ;

    //               emit signalPickedPt3D(point);


    //            } else if (event->button() == Qt::RightButton) {
    //                qDebug() << "ThreeD Right";
    //            }

    //            QWidget::mousePressEvent(event); // Call the base class to ensure event propagation
    //        }

    //        void mouseMoveEvent(QMouseEvent *event) override
    //        {
    //            qDebug() << "Mouse moved to position:" << event->pos();


    //            QWidget::mouseMoveEvent(event);
    //        }

    void mouseDoubleClickEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton)
        {


            //            if (this->windowState() & Qt::WindowFullScreen)
            //            {
            qDebug()<<"1";
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

        QWidget::mousePressEvent(event); // Call the base class to ensure event propagation
    }

};

#endif // THREEDRENDER_H
