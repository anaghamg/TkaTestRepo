#ifndef VIEWERRESLICE_H
#define VIEWERRESLICE_H

#include <QObject>
#include <QWidget>
#include "appcommon/vtkincludes.h"
#include <vtkResliceCursor.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <QVBoxLayout>
#include <vtkResliceCursorLineRepresentation.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkResliceCursorWidget.h>
#include <vtkResliceCursorActor.h>
#include <vtkResliceCursorPolyDataAlgorithm.h>
//#include "myvtkinteractorstyleimage.h"
#include "cusintrimagestyle.h"
#include "widget.h"
#include <QDebug>
//#include "myvtkcornerannotations.h"
#include <vtkVariant.h>
class viewerReslice : public QWidget
{
    Q_OBJECT
public:
    explicit viewerReslice(QWidget *parent = nullptr);
    vtkSmartPointer<vtkResliceImageViewer>m_ResliceImageViewerCom = vtkSmartPointer<vtkResliceImageViewer>::New();
    vtkSmartPointer<vtkDICOMImageReader> m_ReaderCom = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballActor> m_ActorStyleCom = vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_InteractionCom = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_RenderWindowCom = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    QVTKOpenGLWidget *m_QVTKOpenGLWidgetCom;
    vtkResliceCursorLineRepresentation* rep = vtkResliceCursorLineRepresentation::SafeDownCast(
                m_ResliceImageViewerCom->GetResliceCursorWidget()->GetRepresentation());
    Widget *m_objWidget;

     vtkNew<CusIntrImageStyle> m_objCusIntrImageStyle;
//     vtkNew<MyVtkCornerAnnotations> m_pvtkCAnnotations;
// vtkSmartPointer<vtk> m_RenderWindowCom

     //Measurements
     vtkSmartPointer<vtkAngleRepresentation2D> m_pvtkAngleRepresentation2D;  /*!< vtk representation object for vtk angle widget.*/
     vtkSmartPointer<vtkAngleWidget> m_vtkAngleWidget;                       /*!< vtk angle widget for angle measurement.*/
     vtkSmartPointer<vtkDistanceWidget> m_pvtkDistanceWidget;                /*!< vtk distance widget for distance measurement.*/
     vtkSmartPointer<vtkDistanceWidget> m_pvtkLineWidget;                    /*!< vtk line widget for graphical annotation - draw line.*/
     vtkSmartPointer<vtkDistanceRepresentation2D> m_pvtkDistanceRepresentation2D;    /*!< vtk representation object for vtk distance widget.*/
     vtkSmartPointer<vtkPointHandleRepresentation2D> m_pvtkPointDistHandle2D;        /*!< vtk point handle object for vtk distance widget.*/
     vtkSmartPointer<vtkProperty2D> m_pvtkAxisProperty;                              /*!< vtk axis property.*/
     vtkSmartPointer<vtkPointHandleRepresentation2D> m_pPointDistHandleRepresentation2D; /*!< vtk point handle representation object for vtk distance widget.*/
     vtkSmartPointer<vtkDistanceRepresentation2D> m_pvtkDistRepresentation2D;

     int m_nDistMeasureEnabled;
signals:
void GraphicalAnnotationClicked();
public slots:
   void setInput(vtkDICOMImageReader *reader);
   void setCrossHair(int axial, bool blCrossHair=true);
   void renderAll();
   void CreateWin();
    void MeasureDistanceSelected();

};

#endif // VIEWERRESLICE_H
