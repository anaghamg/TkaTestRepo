#ifndef CLASSTHREED_H
#define CLASSTHREED_H

#include "classaxialview.h"


#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>


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


class ClassThreeD
{
public:
    ClassThreeD();

    void ThreeDView(vtkDICOMImageReader *reader);

    QVTKOpenGLWidget *m_VTK3DWidget;
    vtkSmartPointer<vtkDICOMImageReader> m_ReaderThreeD = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkImagePlaneWidget> planeWidget[3];

//
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_3DRenderWindow  =vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();


private:


    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction = vtkSmartPointer<vtkColorTransferFunction>::New();

//    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_3DRenderWindow  =vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();

    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();
    vtkSmartPointer<vtkRenderer> m_3DRenderer = vtkSmartPointer<vtkRenderer>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_3DInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkVolume> volume1 = vtkSmartPointer<vtkVolume>::New();




};

#endif // CLASSTHREED_H
