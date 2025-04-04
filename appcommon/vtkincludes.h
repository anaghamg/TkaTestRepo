/*
    File Name       : vtkincludes.h
    Project Name    : Reconstruction and UI Software System for "Indigenous Magnetic Resonance Imaging"(IMRI)
    Project Code	: HSG021D
    Created         : 2018/10/01
    Purpose         : As part of Image Viewer section in IMRI GUI.
    Description     : Header file containing vtk class includes info.
    Author(s)       : Ranjith KO
    Version Number  : v1.0
    Revisions       : 0.0
    Remarks         : Nil
    Copyright       : Copyright CDAC Thiruvanathapuram
    Modified        : Deepak M
*/
#ifndef VTKINCLUDES_H
#define VTKINCLUDES_H

#include <vtkVersion.h>
#include <vtkAssemblyPath.h>
#include <vtkCell.h>
#include <vtkCommand.h>
#include <vtkImageData.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
//#include <vtkDICOMImageReader.h>
#include <vtkRenderWindow.h>
#include <vtkAutoInit.h>
#include <vtkCornerAnnotation.h>
#include <vtkImageActor.h>
#include <vtkImageSliceMapper.h>
#include <vtkDICOMReader.h>
#include <vtkDICOMDirectory.h>
#include <vtkStringArray.h>
#include <vtkDICOMItem.h>
#include <vtkObjectFactory.h>
#include <vtkInteractorStyleImage.h>
#include <vtkInteractorStyle.h>
#include <vtkActor2D.h>
#include <vtkTextProperty.h>
#include <vtkTextMapper.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkResliceImageViewer.h>
#include <vtkMedicalImageProperties.h>
#include <vtkCamera.h>
#include <vtkDICOMFileSorter.h>
#include <vtkPropPicker.h>
#include <vtkMath.h>
#include <vtkPointData.h>
#include <vtkDICOMMetaData.h>
#include <vtkImageCast.h>
//For distance measurement Line
#include <vtkDistanceWidget.h>
#include <vtkDistanceRepresentation.h>
//For Angle measurement
#include <vtkAngleWidget.h>
#include <vtkAngleRepresentation2D.h>
#include "vtkDistanceRepresentation2D.h"
#include "vtkPointHandleRepresentation2D.h"
#include "vtkProperty2D.h"
#include <vtkAxisActor2D.h>
#include <vtkLeaderActor2D.h>
#include <vtkLineWidget2.h>
#include <vtkLineRepresentation.h>
#include <vtkImageProperty.h>
#include <vtkScalarsToColors.h>
#include <vtkDICOMItem.h>
#include <vtkPolyData.h>
#include <vtkPlaneWidget.h>
#include <vtkProperty.h>
#include <vtkBorderWidget.h>
#include <vtkTextActor.h>
#include <vtkTextWidget.h>
#include <vtkTextRepresentation.h>
#include <vtkBorderRepresentation.h>
#include <vtkTransform.h>
#include <vtkPoints.h>
#include <vtkWidgetEventTranslator.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVTKOpenGLWidget.h>
#include <vtkJPEGWriter.h>
#include <vtkImageShiftScale.h>
#include <vtkPNGWriter.h>

//added for VR
#include <vtkOpenGLRenderWindow.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include<vtkRenderingVolumeOpenGL2ObjectFactory.h>
#include<vtkRenderingOpenGL2ObjectFactory.h>

#include <vtkAutoInit.h> //added

VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType);

#endif // VTKINCLUDES_H
