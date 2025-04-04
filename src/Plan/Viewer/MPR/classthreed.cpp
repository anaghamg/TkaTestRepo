#include "classthreed.h"

ClassThreeD::ClassThreeD()
{
    m_VTK3DWidget = new QVTKOpenGLWidget;
    m_VTK3DWidget->SetRenderWindow(m_3DRenderWindow);
    m_3DInteractor->SetInteractorStyle(style);
    m_3DRenderWindow->SetInteractor(m_3DInteractor);
}

void ClassThreeD::ThreeDView(vtkDICOMImageReader *reader){


    int imageDims[3];
    reader->GetOutput()->GetDimensions(imageDims);

    vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
    picker->SetTolerance(0.005);



    volumeMapper->RemoveAllInputs();
    volumeMapper->SetInputConnection(reader->GetOutputPort());
    volumeMapper->SetSampleDistance(0.1);
    volumeMapper->SetAutoAdjustSampleDistances(0);
    volumeMapper->SetBlendModeToComposite();
    volumeMapper->SetSampleDistance(0.1);
    volumeMapper->Update();



    opacityTransferFunction->AddPoint(0, 0.0);
    opacityTransferFunction->AddPoint(30, 0.5); // Skin
    opacityTransferFunction->AddPoint(70, 0.3);
    opacityTransferFunction->AddPoint(125, 0.2);

    // Create transfer mapping scalar value to color
    colorTransferFunction->AddRGBPoint(0, 0.0, 0.0, 0.0);
    colorTransferFunction->AddRGBPoint(30, 1.0, 0.5, 0.3);
    colorTransferFunction->AddRGBPoint(70, 1.0, 0.8, 0.8);
    colorTransferFunction->AddRGBPoint(125, 1.0, 1.0, 0.9);


    // The property describes how the data will look
    vtkSmartPointer<vtkVolumeProperty> volumeProperty = vtkSmartPointer<vtkVolumeProperty>::New();
    volumeProperty->RemoveAllObservers();
    volumeProperty->SetColor(colorTransferFunction);
    volumeProperty->SetScalarOpacity(opacityTransferFunction);
    volumeProperty->ShadeOn();
    volumeProperty->SetInterpolationTypeToLinear();

    // Setting the volume
    volume1->SetMapper(volumeMapper);
    volume1->SetProperty(volumeProperty);
    volume1->Update();




    // Renderer
    m_3DRenderer->AddVolume(volume1);
    //m_3DRenderer->GetActiveCamera()->SetClippingRange(0,1000000);
    m_3DRenderWindow->AddRenderer(m_3DRenderer);

    for (int i = 0; i < 3; i++)
    {
        planeWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();
        planeWidget[i]->SetInteractor(m_3DInteractor);
        planeWidget[i]->SetPicker(picker);
        planeWidget[i]->RestrictPlaneToVolumeOn();
        double color[3] = { 0, 0, 0 };
        color[i] = 1;
        planeWidget[i]->GetPlaneProperty()->SetColor(color);
        color[0] /= 4.0;
        color[1] /= 4.0;
        color[2] /= 4.0;
        //riw[i]->GetRenderer()->SetBackground(color);
        //planeWidget[i]->SetTexturePlaneProperty(ipwProp);
        planeWidget[i]->GetTexturePlaneProperty()->SetOpacity(0.05);
        //planeWidget[i]->SetTextureVisibility(false);
        planeWidget[i]->SetResliceInterpolateToLinear();
        planeWidget[i]->SetInputConnection(reader->GetOutputPort());
        planeWidget[i]->SetPlaneOrientation(i);
        planeWidget[i]->SetSliceIndex(imageDims[i] / 2);
        planeWidget[i]->DisplayTextOn();
        planeWidget[i]->SetDefaultRenderer(m_3DRenderer);
        planeWidget[i]->SetWindowLevel(1358, -27);
        planeWidget[i]->On();
        planeWidget[i]->InteractionOn();
        planeWidget[i]->UpdatePlacement();
    }





    //RenderWindow

    m_3DRenderWindow->GlobalWarningDisplayOff();
    m_3DRenderWindow->Render();

//    m_3DRenderer->GetActiveCamera()->Elevation(90);
        m_3DRenderer->GetActiveCamera()->Azimuth(90);
        m_3DRenderer->GetActiveCamera()->Roll(90);
        m_3DRenderer->GetActiveCamera()->Yaw(-90);



//    m_3DRenderer->GetActiveCamera()->Roll(180);

//    m_3DRenderer->GetActiveCamera()->Yaw(180);




    m_3DRenderer->GetActiveCamera()->Zoom(1.2);
    m_3DRenderer->GetActiveCamera()->SetClippingRange(0.1, 10000);

    m_3DRenderer->ResetCamera();

//    m_3DRenderWindow->Render();
    m_3DInteractor->Initialize();

}

