#ifndef IMAGESELECTION_H
#define IMAGESELECTION_H

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QStackedWidget>
#include <QComboBox>
#include <QLabel>
#include <QProgressBar>
#include "vtkSTLReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSTLWriter.h"
#include "vtkOpenGLGPUVolumeRayCastMapper.h"
#include "src/PDM/PatientData/patientdata.h"
#include "appcommon/spdlog/spdlog.h"
#include <QDir>
#include <qprocess.h>
#include <windows.h>
#include <shellapi.h>  // For ShellExecute function
#include <QThread>
#include "src/PDM/PatientRegistration/executesaks.h"
#include <QMessageBox>
#include <QProgressDialog>
#include <QtConcurrent>


class imageselection : public QWidget
{
    Q_OBJECT
public:
    explicit imageselection(QWidget *parent = nullptr);


    //create class objects
    patientdata *m_objPatientData;
    executeSAKS *m_objWorkerSAKS;

    QProgressBar *progressBar;
    QProgressDialog *progressDialog;
    QProgressDialog *progressDialogimage;

    QPushButton* m_qbtnBrowseImage;
    QPushButton* m_qbtnSegmentImage;
    QRadioButton* m_qrbtnImageLessBtn;
    QRadioButton* m_qrbtnImageBasedBtn;


    QVBoxLayout *m_qpvblBrowseLayout;
    QVBoxLayout *m_qvblRadioBtnLayout;
    QHBoxLayout *m_qvblVTKWidgetLayout;
    QHBoxLayout *m_qhblcomboboxLayout;
    QHBoxLayout *m_hblWidgetLayout;
    QString m_qsimagePath;
    QVTKOpenGLWidget *m_qwDCMWidget;
    QVTKOpenGLWidget *m_qwSTLWidget;
    QStackedWidget *m_qsStackedWidget;
    QComboBox *m_qcbKnee;
    QString m_qsSelectedKnee;
    double currentProgress = 0;


   QFrame *m_qfbrowseframe;


   vtkNew <vtkGenericOpenGLRenderWindow> m_pvtkOpenGLRenWinDcm;
   vtkSmartPointer<vtkDICOMImageReader> m_pvtkDcmReader;
   vtkNew <vtkRenderWindowInteractor> m_pvtkInter;
   vtkNew<vtkResliceImageViewer> m_pvtkImageViewer;
   vtkSmartPointer<vtkResliceImageViewer>m_ResliceImageViewer = vtkSmartPointer<vtkResliceImageViewer>::New();
   vtkSmartPointer<vtkRenderWindowInteractor> m_Interaction = vtkSmartPointer<vtkRenderWindowInteractor> ::New();
   vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_RenderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
   vtkNew <vtkGenericOpenGLRenderWindow> m_pvtkOpenGLRenWinSTL;

   vtkNew<vtkRenderer> m_pvtkRendererSTL;
   vtkNew <vtkSTLReader> m_pvtkSTLReader;
   vtkNew <vtkSTLWriter> m_pvtkSTLWriter;
   vtkNew <vtkPolyDataMapper> m_pvtkSTLMapper;
   vtkNew <vtkActor> m_pvtkSTLActor;
   vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper> mapper =   vtkSmartPointer<vtkOpenGLGPUVolumeRayCastMapper>::New();
   vtkSmartPointer<vtkColorTransferFunction> volumeColor=vtkSmartPointer<vtkColorTransferFunction>::New();
   vtkSmartPointer<vtkPiecewiseFunction> opacityFun  = vtkSmartPointer<vtkPiecewiseFunction>::New();
   vtkSmartPointer<vtkVolumeProperty> property = vtkSmartPointer<vtkVolumeProperty>::New();
   vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
   vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();



   QString m_qstrDcmFull; //full dicom dir
   QString m_qstrDcmFemur; //femur dir
   QString m_qstrDcmTibia; //tibia dir

   QString m_qstrStlFull; //full knee stl
   QString m_qstrStlFemur; //femur stl
   QString m_qstrStlTibia; //tibia stl
   QTimer *timer;
   QTimer *closeTimer;


signals:

   //anagha  //for testing
   void signalLoadedDicom(const QString& qstrDcmFull, const QString& qstrDcmFemur, const QString qstrDcmTibia,const QString qstrselKnee);
   void signalLoadedStl(const QString& m_qstrStlFemur, const QString& m_qstrStlTibia);


   void signalDcmDir(QString st);
   void  workFinished();
   void  loadImage();





public slots:
    void BrowseandLoadImage();
    void saksExecute();
    void LoadDCM();
    void LoadSTL();

    void setDicomDirectories(const QString& qstrDcmFull, const QString& qstrDcmFemur, const QString& qstrDcmTibia);
       void setStlPaths(/*const QString& qstrStlFull,*/ const QString &qstrStlFemur, const QString qstrStlTibia) ;



    void updateProgress();
    void startReading();
    void onWorkFinished();


private:

    void executeSAKSInThread();
    QThread *workerThreadSaks;


};

#endif // IMAGESELECTION_H
