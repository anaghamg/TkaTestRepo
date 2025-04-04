#ifndef CUSINTRIMAGESTYLE_H
#define CUSINTRIMAGESTYLE_H

#include <QObject>
#include <QWidget>
#include "appcommon/vtkincludes.h"
#include <QPointer>
#include <vtkInteractorStyleTrackballActor.h>
//#include "myvtkcornerannotations.h"
class CusIntrImageStyle : public QObject, public vtkInteractorStyleImage /*vtkInteractorStyleTrackballActor*/ /*vtkInteractorStyleImage*/
{
    Q_OBJECT
public:
//    explicit CusIntrImageStyle(QWidget *parent = nullptr);
   vtkTypeMacro(CusIntrImageStyle, vtkInteractorStyleImage);
//   vtkTypeMacro(CusIntrImageStyle, vtkInteractorStyleTrackballActor);
    static CusIntrImageStyle* New();
   CusIntrImageStyle();
   ~CusIntrImageStyle();

    void SetImageViewer(vtkResliceImageViewer *pvtkImageViewer);









    vtkResliceImageViewer *m_pvtkImageViewer;
//    MyVtkCornerAnnotations *m_pvtkCornerAnnotations;
    //!Set QVTKWidget
    /*!
     * \brief Set QVTKWidget related to this interactor style class object.
     * \param vtkWgt QVTKWidget related to this class object.
     */
    void SetVtkWidget(QVTKOpenGLWidget *pvtkWidget);

    //!Set MyVtkCornerAnnotations status
    /*!
     * \brief Set whether need to update corner annotations from interaction style image.
     * \param blCornerAnnotationStatus 'true' if needed else 'false'.
     */
    void SetConerAntnStatus(bool blCornerAnnotationStatus);

    //!Set MyVtkCornerAnnotations
    /*!
     * \brief Set MyVtkCornerAnnotations related to this interactor style class object.
     * \param cornerAntns MyVtkCornerAnnotations related to this class object.
     */
//    void SetConerAntn(MyVtkCornerAnnotations *pMyVtkCornerAnnotations);

    vtkDICOMMetaData *m_pvtkDcmMetaData; /*!< vtk DICOM meta data. */
    QVTKOpenGLWidget *m_pvtkWidget;

    void getDistMeasurement();
protected:
     virtual  void OnLeftButtonDown();
virtual  void OnLeftButtonUp();
    virtual void OnMouseMove();





  virtual  void 	OnMiddleButtonDown ();


  virtual  void 	OnMiddleButtonUp ();


  virtual  void 	OnRightButtonDown ();


   virtual void 	OnRightButtonUp ();



private:
     enum {LEFT_BUTTON, RIGHT_BUTTON, MIDDLE_BUTTON, NONE,RIGHT_BUTTON_DOWN} m_eMouseButtonType;
     enum {CORNER_ANNOTATIONS_ON = 1, CORNER_ANNOTATIONS_OFF = 0} m_eCornerAnnotationStatus;
     enum {GRAPHICAL_ANNOTATIONS_ENABLED = 1, GRAPHICAL_ANNOTATIONS_DISABLED = 0} m_eGraphAnnotationEnableStatus;
signals:


public slots:
     void GraphicalAnnotationSelected();

};

#endif // CUSINTRIMAGESTYLE_H
