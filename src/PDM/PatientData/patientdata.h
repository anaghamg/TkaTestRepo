#ifndef PATIENTDATA_H
#define PATIENTDATA_H

#include <QWidget>
#include <QtDebug>
#include "appcommon/vtkincludes.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageData.h"
#include "vtkGPUVolumeRayCastMapper.h"
#include "vtkVolumeProperty.h"
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkConnectivityFilter.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkNamedColors.h>
#include <vtkDataSetMapper.h>
#include <vtkLookupTable.h>



class patientdata : public QWidget
{
    Q_OBJECT
public:
    explicit patientdata(QWidget *parent = nullptr);


    QString m_pName;
    QString m_pGender;
    QString m_pDob;
    QString m_pAge;
    QString m_pId;
    QString m_pAddress;
    QString m_refPhysician;
    QString m_pUID;
    QString m_pSelectedKnee;



   vtkSmartPointer<vtkDICOMImageReader> reader = vtkSmartPointer<vtkDICOMImageReader>::New();
   vtkSmartPointer<vtkImageData> twodimageData = vtkSmartPointer<vtkImageData>::New(); 
       vtkSmartPointer<vtkPolyData> polyData  = vtkSmartPointer<vtkPolyData>::New();



   vtkSmartPointer<vtkPiecewiseFunction> opacityTransferFunction = vtkSmartPointer<vtkPiecewiseFunction>::New();

signals:


public slots:
    void patientDetails(QStringList qstrUpdate);
    void patientImageData(QString imagepath, QString selectedKnee);


public slots:
};

#endif // PATIENTDATA_H
