#ifndef FIDUCIALSWINDOW_H
#define FIDUCIALSWINDOW_H

#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkNew.h>
#include <vtkRenderer.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <qdebug.h>
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPropPicker.h>
#include <QMouseEvent>
#include <vtkChartXYZ.h>
#include <vtkContextMouseEvent.h>
#include <vtkContextScene.h>
#include <vtkContextView.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPen.h>
#include <vtkPlotSurface.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTable.h>
#include <vtkVersion.h>
#include <vtkLineSource.h>
#include <vtkGlyph3DMapper.h>
#include <QHBoxLayout>
#include "src/Registration/fiducialstruct.h"


class fiducialswindow : public QWidget
{
    Q_OBJECT
public:
    explicit fiducialswindow(QWidget *parent = nullptr);

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGLToolWin;


signals:

    void signalVisualise();

public slots:
    void slotFiducialsFemurRef(const QList<QVariantMap>& fiducialsData);
    void slotFiducialsTibiaRef(const QList<QVariantMap>& fiducialsData);
    void slotFiducialsTool(const QList<QVariantMap>& fiducialsData);


private:

    QList<vtkSmartPointer<vtkActor>> sphereActorsT;
    QList<vtkSmartPointer<vtkActor>> sphereActorsTib;
    QList<vtkSmartPointer<vtkActor>> sphereActorsF;



    vtkSmartPointer<vtkSphereSource> tst1 = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> tsmt1 = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer <vtkActor> tsat1 =  vtkSmartPointer <vtkActor>::New();


    QVTKOpenGLWidget* m_qvtkToolwin;
    vtkSmartPointer<vtkRenderer> m_qvtkToolwinRenderer;

    void drawQuadrantGraph();

    vtkSmartPointer<vtkPoints> pts1 = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> pd1 = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkSphereSource> ss1 = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkGlyph3DMapper> gm1 = vtkSmartPointer<vtkGlyph3DMapper>::New();
    vtkSmartPointer<vtkActor> pa1 = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkPoints> pts2 = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> pd2 = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkSphereSource> ss2 = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkGlyph3DMapper> gm2 = vtkSmartPointer<vtkGlyph3DMapper>::New();
    vtkSmartPointer<vtkActor> pa2 = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkPoints> pts3 = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkPolyData> pd3 = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkSphereSource> ss3 = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkGlyph3DMapper> gm3 = vtkSmartPointer<vtkGlyph3DMapper>::New();
    vtkSmartPointer<vtkActor> pa3 = vtkSmartPointer<vtkActor>::New();



};

#endif // FIDUCIALSWINDOW_H
