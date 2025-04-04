/*
    File Name       : Checkpoint.h
    Project Name    : TKA Robotic Surgery
    Created         : 18-11-2024
    Description     : Header file containing declaration for
                      displaying Femur and Tibia Checkpoint images
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/
#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <QObject>
#include <QWidget>
#include <QDir>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QStackedWidget>

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <QVTKOpenGLWidget.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkPNGReader.h>
#include <vtkImageViewer2.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkCamera.h>
#include <vtkTextActor.h>
#include <vtkActor.h>
#include <vtkTextProperty.h>

class Checkpoint : public QWidget
{
    Q_OBJECT
public:
    explicit Checkpoint(QWidget *parent = nullptr);

    QStackedWidget* m_qswCheckpt;
    //void setCheckpointImage(const QString& qstrBone);

signals:

public slots:

private:
    QVTKOpenGLWidget*  m_pvtkWidgetChkptFemur ;
    vtkSmartPointer<vtkImageViewer2> m_pvtkImageviewerFemur = vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGlRenWinFemur = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    QVTKOpenGLWidget*  m_pvtkWidgetChkptTibia ;
    vtkSmartPointer<vtkImageViewer2> m_pvtkImageviewerTibia = vtkSmartPointer<vtkImageViewer2>::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGlRenWinTibia = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


    vtkSmartPointer<vtkRenderWindowInteractor> m_pvtkInter1 = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_pvtkInter2 = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    vtkSmartPointer<vtkTextActor> actorL = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> actorM = vtkSmartPointer<vtkTextActor>::New();

    void setChkptImageFemur();
    void setChkptImageTibia();

    //single implementation
//    QVTKOpenGLWidget*  m_pvtkWidgetChkpt ;
//    vtkSmartPointer<vtkImageViewer2> m_pvtkImageviewer = vtkSmartPointer<vtkImageViewer2>::New();
//    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGlRenWin = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

};

#endif // CHECKPOINT_H
