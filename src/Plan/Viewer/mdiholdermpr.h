#ifndef MDIHOLDERMPR_H
#define MDIHOLDERMPR_H

#include <QMainWindow>
#include <QObject>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QVBoxLayout>
#include "src/Plan/Viewer/subwindowcust.h"
#include "src/Plan/Viewer/MPR/axialview.h"
#include "src/Plan/Viewer/MPR/sagitalview.h"
#include "src/Plan/Viewer/MPR/coronalview.h"
#include "src/Plan/Viewer/MPR/threedview.h"
#include "appcommon/vtkincludes.h"

#include "vtkInteractorStyleImage.h"
//added on 30-07-2024
#include <vtkEventQtSlotConnect.h>
#include "src/Plan/Viewer/Interactors/savelandmark.h"
#include <vtkSphereSource.h>
#include <vtkAppendPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkLineSource.h>
#include <QStatusBar>

class mdiHolderMPR : public QWidget
{
    Q_OBJECT
public:
    explicit mdiHolderMPR(QWidget *parent = nullptr);

    QMdiArea *m_qMdiAreaforMPR;
    subwindowCust *m_objsubwcustMPR;
    bool startnow=false;
    bool isActiveSubWinMin=true;

    subwindowCust *m_objsubwindowCustAxial;
    subwindowCust *m_objsubwindowCustCoronal;
    subwindowCust *m_objsubwindowCustSagittal;
    subwindowCust *m_objsubwindowCustThreeD;

    axialView *m_objaxialView;
    CoronalView *m_objCoronalView;
    sagitalView *m_objsagitalView;
    threeDView *m_objthreeDView;
    savelandmark *m_objsavelandmark;

    QList <subwindowCust *> m_listmdisubwindow;

    vtkSmartPointer<vtkDICOMImageReader> readerACS = vtkSmartPointer<vtkDICOMImageReader>::New();

    vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkImageReslice> m_imgReslice0  = vtkSmartPointer<vtkImageReslice>::New();
    vtkSmartPointer<vtkImageReslice> m_imgReslice1  = vtkSmartPointer<vtkImageReslice>::New();
    vtkSmartPointer<vtkImageReslice> m_imgReslice2  = vtkSmartPointer<vtkImageReslice>::New();

    //void setMPRConnections();

    void setMPRConnections(QString qstrDicomPath, QString fullpath, QString selKnee);     //modified by anagha

    //bool m_boolfirst=true;

    //added by anagha
    QString m_qstrDcmDir;
    QString m_qstrfullpath;
    QString m_qstrselKnee;//parvathy
    void SetDicomDirectory(QString qstrDcmDir,QString fullpath, QString selKnee);
    void slotAnatomyAnnotation(QString from, int anatomyid, const QString &anatomy);
    QSet<QString> selectedAnatomies;  // To store unique anatomy keys



    std::array<double, 3> parseXML(const std::string& filename, const QString& boneName, int anatomyID,
                                    QString anatomy) ;
    bool isRepeatSelection = false;  // to check if the landmark item was already selected





    vtkResliceCursorWidget *RCW[3];
    vtkSmartPointer<vtkDICOMImageReader> m_vtkDICOMImageReaderMPR = vtkSmartPointer<vtkDICOMImageReader>::New();

    void updateSlice(std::array<double, 3> pt); //rupika  
    void showCrossHairsAxial(std::array<double,3> pt, vtkRenderer* renderer);
    void showCrossHairsCoronal(std::array<double,3> pt, vtkRenderer* renderer);
    void showCrossHairsSagittal(std::array<double,3> pt, vtkRenderer* renderer);

    //dhanyasree
    void sliceChangeByaxial(double*  centre);
    void sliceChangeBycoronal(double*  centre);
    void sliceChangeBysagital(double*  centre);
    double * sliceCenter1_coronal;
    double *sliceCenter2_sagittal;
    double *sliceCenter3_axial;

    bool firstflag =false;

    void setMPRreset();

    //kiran
    void ClipTibiaFemur(int index); //for clipping the tibia and femur in 3D
    int m_annotTabIndex = 0;
    int m_sliceindex = 0;

    bool pointchecked = false;
    bool pointincoronal = false;
    int imgwidth;
    double pixelspacing;
    double offsetcoronal;


signals:
    void signalDcmDirectory(QString qstrDcmDir, QString fullpath, QString SelKnee);  //added by anagha
    void signalPickedPt(std::array<double, 3> pt); //rupika
    void  signalpointselected(bool pointchecked); //parvathy

public slots:
    void hindTheSubWindow();
    void maxTheSubWindow();
    void refreshWindow();

    void SliceSlot(); //dhanyasree
    void EnablePointSelection();    //added by anagha
    void slotpointincoronal(bool pointcoronal);

private:
    //rupika
    vtkSmartPointer<vtkAssembly> assembly =vtkSmartPointer<vtkAssembly>::New();
    void ReadDICOMSeries(const std::string& directory, int seriesNumber);

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();

    void OnLeftButtonDown(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);

    vtkSmartPointer<vtkLineSource> axialLine1 = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkLineSource> axialLine2 = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkLineSource> coronalLine1 = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkLineSource> coronalLine2 = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkLineSource> sagittalLine1 = vtkSmartPointer<vtkLineSource>::New();
    vtkSmartPointer<vtkLineSource> sagittalLine2 = vtkSmartPointer<vtkLineSource>::New();

    vtkSmartPointer<vtkSphereSource> threedpt = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> threedpt_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> threedpt_actor = vtkSmartPointer<vtkActor>::New();

    std::array<double,3> m_mdiPickedPt;
    std::array<double,3> m_mditransformedPt;
};

#endif // MDIHOLDERMPR_H
