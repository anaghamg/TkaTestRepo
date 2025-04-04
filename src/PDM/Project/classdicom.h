#ifndef CLASSDICOM_H
#define CLASSDICOM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QFileDialog>

//vtk headers

#include "appcommon/vtkincludes.h"

#include "vtkDICOMImageReader.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "QVTKOpenGLWidget.h"
#include "vtkSTLReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSTLWriter.h"
#include "vtkProperty.h"
#include "vtkSphereSource.h"
#include "vtkConeSource.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageViewer2.h"
#include "vtkDICOMReader.h"
#include "vtkImageData.h"
#include "vtkInteractorStyleImage.h"

#include "vtkResliceImageViewer.h"


class ClassDicom : public QWidget
{
    Q_OBJECT
public:
    explicit ClassDicom(QWidget *parent = nullptr);


signals:
    void signalDicomDirPath(QString qstrDicomPath);

    void signalLoadDicomStatus(bool status);

public slots:
    void GetDicomDirectory();
    void SetDicomDirectory(QString qstrDcmDir);
    void ImportDicom();





private:
    QVTKOpenGLWidget *m_pvtkWidget;
    vtkNew <vtkGenericOpenGLRenderWindow> m_pvtkOpenGLRenWinDcm;
    vtkSmartPointer<vtkDICOMImageReader> m_pvtkDcmReader;

    //vtkNew<vtkImageViewer2> m_pvtkImageViewer;
    vtkNew <vtkRenderWindowInteractor> m_pvtkInter;
    //vtkNew<vtkInteractorStyleImage> m_pvtkiStyle;
    //    vtkNew<MyVtkInteractorStyleImage> m_pMyVtkInteractorStyleImage; /*!< Customised vtkImageViewerStyleImage for the viewer. */

    QString m_qstrDcmDir;


    vtkNew<vtkResliceImageViewer> m_pvtkImageViewer;






    vtkSmartPointer<vtkResliceImageViewer>m_ResliceImageViewer = vtkSmartPointer<vtkResliceImageViewer>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_Interaction = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_RenderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();




};

#endif // CLASSDICOM_H
