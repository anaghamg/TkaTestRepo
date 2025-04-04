#include "patientdata.h"

patientdata::patientdata(QWidget *parent) : QWidget(parent)
{

}

void patientdata::patientDetails(QStringList qstrPatientDetails)
{
    m_pName = qstrPatientDetails.at(1);
    m_pId= qstrPatientDetails.at(0);
    m_pAge = qstrPatientDetails.at(3);
    m_pGender = qstrPatientDetails.at(2);
    m_pDob = qstrPatientDetails.at(4);
    m_pAddress = qstrPatientDetails.at(5);
    m_refPhysician = qstrPatientDetails.at(6);
    m_pUID= qstrPatientDetails.at(7);
}

void patientdata::patientImageData(QString imagepath, QString selectedKnee)
{
    m_pSelectedKnee = selectedKnee;

    qDebug()<<"Image path"<<imagepath;
    reader->SetDirectoryName(imagepath.toUtf8().constData());
    reader->Update();

    twodimageData = reader->GetOutput();//2d image data in a vtkimagedata
    reader->GetWidth();
   int* dimensions = twodimageData->GetDimensions();
   double* spacing =   reader->GetPixelSpacing();
   int width = reader->GetWidth();
   int height = reader->GetHeight();

    /*********************** SR *******************************/


    // Create a Marching Cubes filter
    vtkSmartPointer<vtkMarchingCubes> marchingCubes = vtkSmartPointer<vtkMarchingCubes>::New();
    marchingCubes->SetInputData(reader->GetOutput());
    marchingCubes->SetValue(0, 300); // Set the iso value, adjust as needed 300..

    // Stripper to merge the triangles into polygons
    vtkSmartPointer<vtkStripper> stripper = vtkSmartPointer<vtkStripper>::New();
    stripper->SetInputConnection(marchingCubes->GetOutputPort());
    stripper->Update();

    polyData = stripper->GetOutput();//SR data in polydata



    /*********************** VR *******************************/



   /* volumeMapper->SetInputConnection(reader->GetOutputPort());
    volumeMapper->SetSampleDistance(0.1);
    volumeMapper->SetAutoAdjustSampleDistances(0);
    volumeMapper->SetBlendModeToComposite();
    volumeMapper->Update();

    // Create a volume and set the mapper
   vtkSmartPointer<vtkVolume> volume =  vtkSmartPointer<vtkVolume>::New();
   volume->SetMapper(volumeMapper);

   volumeMapper->SafeDownCast(volume->GetMapper());
   vtkSmartPointer<vtkDataSet> dataset = volumeMapper->GetInput();
   imageData = vtkImageData::SafeDownCast(dataset);



   vtkSmartPointer<vtkRenderer> renderer =    vtkSmartPointer<vtkRenderer>::New();
   vtkSmartPointer<vtkRenderWindow> renderWindow =   vtkSmartPointer<vtkRenderWindow>::New();




      vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper1 = vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
         volumeMapper1->SetInputData(imageData);



         opacityTransferFunction->AddPoint(0, 0.0);
         opacityTransferFunction->AddPoint(30, 0.5); // Skin
         opacityTransferFunction->AddPoint(70, 0.3);
         opacityTransferFunction->AddPoint(125, 0.2);

         // Create transfer mapping scalar value to color
         colorTransferFunction->AddRGBPoint(0, 0.0, 0.0, 0.0);
         colorTransferFunction->AddRGBPoint(30, 1.0, 0.5, 0.3);
         colorTransferFunction->AddRGBPoint(70, 1.0, 0.8, 0.8);
         colorTransferFunction->AddRGBPoint(125, 1.0, 1.0, 0.9);


         // Create a volume property
         vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
         volumeProperty->SetColor(colorTransferFunction);
         volumeProperty->SetScalarOpacity(opacityTransferFunction);
         volumeProperty->SetInterpolationTypeToLinear();

         // Create a volume
         vtkSmartPointer<vtkVolume> volume1 = vtkSmartPointer<vtkVolume>::New();
         volume1->SetMapper(volumeMapper1);
         volume1->SetProperty(volumeProperty);


       //  vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
        //    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
            vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

            renderWindow->AddRenderer(renderer);
            renderWindowInteractor->SetRenderWindow(renderWindow);

            // Add the volume to the scene
            renderer->AddVolume(volume1);
            renderer->SetBackground(.1, .2, .4); // Background color

            // Render and interact
            renderWindow->Render();
            renderWindowInteractor->Start();


*/






   }
