#ifndef CUSTOMINTERACTORSTYLE_H
#define CUSTOMINTERACTORSTYLE_H
#include <QDebug>
#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>
#include <QWidget>


#include <vtkActor.h>
#include <vtkAlgorithm.h>
#include <vtkAlgorithmOutput.h>
#include <vtkAssembly.h>
#include <vtkAxesActor.h>
#include <vtkCamera.h>
#include <vtkCallbackCommand.h>
#include <vtkCellPicker.h>
#include <vtkColorTransferFunction.h>
#include <vtkCommand.h>
#include <vtkExecutive.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include "vtkDICOMImageReader.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkInteractorStyleTrackballActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInformation.h>
#include <vtkImageActor.h>
#include "vtkImageData.h"
#include <vtkImagePlaneWidget.h>
#include <vtkImageProperty.h>
#include <vtkInteractorStyleImage.h>
#include <vtkMath.h>
#include <vtkOBJReader.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPlane.h>
#include <vtkPlaneSource.h>
#include <vtkPlaneWidget.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkPropPicker.h>
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
#include "vtkTransform.h"
#include <vtkViewport.h>
#include "vtkVolumeProperty.h"
#include "vtkVolume.h"
#include <vtkVertexGlyphFilter.h>


#include "vtkInteractorObserver.h"
#include "vtkGenericRenderWindowInteractor.h"
#include "vtkEvent.h"

class CustomInteractorStyle : public vtkInteractorStyleImage
{
public:
    static CustomInteractorStyle* New()
    {
        return new  CustomInteractorStyle;
    }
    //vtkTypeMacro(CustomInteractorStyle, vtkInteractorStyleImage);

    virtual void OnMouseMove() override
    {
        if(this->LeftButtonDown)
        {
            return;
        }
//        if (this->State == VTKIS_NONE)
//        {
//            return;
//        }
        if(this->State == VTKIS_DOLLY)
        {
            this->EndWindowLevel();
           // this->Superclass::OnMouseMove();
        // return;
        }

        if (this->LeftButtonDown && this->RightButtonDown)
        {
            // Both buttons are down - handle the dragging event here
            HandleMouseDrag();
          //  this->Superclass::OnMouseMove();
        }


 //****---------------------
        if (this->MiddleButtonDown)
        {
            //return;
            HandleMouseZoom();
        }

//****---------------------
//        int x = this->Interactor->GetEventPosition()[0];
//        int y = this->Interactor->GetEventPosition()[1];

//        switch (this->State)
//        {
//            case VTKIS_PAN:
//                this->FindPokedRenderer(x, y);
//                this->Pan();
//                this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
//                break;
//            case VTKIS_WINDOW_LEVEL:
//                //this->FindPokedRenderer(x, y);
//                //this->WindowLevel();
//                //this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
//                break;
//            case VTKIS_SPIN:
//                this->FindPokedRenderer(x, y);
//                this->Spin();
//                this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
//                break;
//            case VTKIS_ZOOM:
//                this->FindPokedRenderer(x, y);
//                this->Zoom();
//                this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
//                break;
//        }

       this->Superclass::OnMouseMove();
    }

//    virtual void OnLeftButtonDown() override
//    {
//        this->LeftButtonDown = true;
//        if (this->RightButtonDown)
//        {
//            // Both buttons are down - handle the event here
//            HandleBothButtonsDown();
//        }
////        vtkInteractorStyleImage::OnLeftButtonDown();
//    }
//*******-------------------------
        virtual void OnLeftButtonDown() override
        {
            this->LeftButtonDown = true;
        if (this->LeftButtonDown)
        {
            // Both buttons are down - handle the event here
            return;
        }

            if (this->RightButtonDown)
            {
                // Both buttons are down - handle the event here
                HandleBothButtonsDown();
            }
            else{
                return;
            }

    //        vtkInteractorStyleImage::OnLeftButtonDown();
       }


//*******--------------------------


    virtual void OnLeftButtonUp() override
    {
        this->LeftButtonDown = false;
        if (this->State == VTKIS_WINDOW_LEVEL)
        {
            this->EndWindowLevel();
        }
    }


    virtual void OnMiddleButtonDown() override
    {
//        this->FindPokedRenderer(
//            this->Interactor->GetEventPosition()[0],
//            this->Interactor->GetEventPosition()[1]);

//        if (this->CurrentRenderer == nullptr)
//        {
//            return;
//        }

//        this->StartDolly();
//        this->Superclass::OnMiddleButtonDown();
        this->MiddleButtonDown = true;
        this->SetCameraFocalPointAtCursor();
        this->StartZoom();
//        this->InitialMousePosition[0] = this->Interactor->GetEventPosition()[0];
//        this->InitialMousePosition[1] = this->Interactor->GetEventPosition()[1];

     }

    virtual void OnMiddleButtonUp() override
    {
//        if (this->State == VTKIS_DOLLY)
//        {
//            this->EndDolly();
//        }

//        this->Superclass::OnMiddleButtonUp();
        this->MiddleButtonDown = false;

                if (this->State == VTKIS_ZOOM)
                {
                    this->EndZoom();
                }
    }

    virtual void OnRightButtonDown() override
    {
        this->RightButtonDown = true;
        if(this->LeftButtonDown)
        {
            HandleBothButtonsDown();
        }
//        if (this->LeftButtonDown=false)
//        {
//            // Both buttons are down - handle the event here
//            HandleBothButtonsDown();
//        }
//        else
//        {
            // Start pan operation if only the right button is pressed
            this->StartPan();
//            vtkInteractorStyleImage::OnRightButtonDown();

        //}
    }


    virtual void OnRightButtonUp() override
    {
        this->RightButtonDown = false;
        if (this->State == VTKIS_WINDOW_LEVEL)
        {
            this->EndWindowLevel();
        }
        if (this->State == VTKIS_PAN)
        {
            this->EndPan();
        }

//        vtkInteractorStyleImage::OnRightButtonUp();
    }



protected:
    void HandleBothButtonsDown()
    {
        // Start window level adjustment when both buttons are pressed
        this->StartWindowLevel();
    }

    void HandleMouseDrag()
    {
        // Adjust window level during mouse drag when both buttons are pressed
        int x = this->Interactor->GetEventPosition()[0];
        int y = this->Interactor->GetEventPosition()[1];
        this->FindPokedRenderer(x, y);
        this->WindowLevel();
        this->InvokeEvent(vtkCommand::InteractionEvent, nullptr);
    }

    virtual void /*Start*/WindowLevel() override
    {
      if (this->State != VTKIS_NONE)
      {
        return;
      }
      this->StartState(VTKIS_WINDOW_LEVEL);

      // Get the last (the topmost) image
      this->SetCurrentImageNumber(this->CurrentImageNumber);

      if (this->HandleObservers && this->HasObserver(vtkCommand::StartWindowLevelEvent))
      {
        this->InvokeEvent(vtkCommand::StartWindowLevelEvent, this);
      }
      else
      {
        if (this->CurrentImageProperty)
        {
          vtkImageProperty* property = this->CurrentImageProperty;
          this->WindowLevelInitial[0] = property->GetColorWindow();
          this->WindowLevelInitial[1] = property->GetColorLevel();
        }
      }
    }

    //------------------------------------------------------------------------------
    virtual void EndWindowLevel() override
    {
      if (this->State != VTKIS_WINDOW_LEVEL)
      {
        return;
      }
      if (this->HandleObservers)
      {
        this->InvokeEvent(vtkCommand::EndWindowLevelEvent, this);
      }
      this->StopState();
    }

//***********************************************
    void StartZoom()
       {

           // Set the state to zooming
           this->StartState(VTKIS_ZOOM);

           // Optionally, you can capture the initial cursor position here
//           this->InitialMousePosition[0] = this->Interactor->GetEventPosition()[0];
//           this->InitialMousePosition[1] = this->Interactor->GetEventPosition()[1];
       }
    void SetCameraFocalPointAtCursor()
    {

        // Get the current mouse position in screen coordinates
        int x = this->Interactor->GetEventPosition()[0];
        int y = this->Interactor->GetEventPosition()[1];


        vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();
           picker->Pick(x, y, 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

           vtkRenderer* renderer = picker->GetRenderer();

           if (renderer)
                  {
        // Convert the screen coordinates to world coordinates
        double worldCoords[4]; // Homogeneous coordinates (x, y, z, w)
        renderer->SetDisplayPoint(x, y, 0); // Set the display point with a Z depth of 0
        renderer->DisplayToWorld();
        renderer->GetWorldPoint(worldCoords);

        if (worldCoords[3] != 0.0) // Avoid division by zero
        {
            worldCoords[0] /= worldCoords[3];
            worldCoords[1] /= worldCoords[3];
            worldCoords[2] /= worldCoords[3];
        }
        // Set the camera's focal point to the world coordinates under the cursor
        vtkCamera* camera = renderer->GetActiveCamera();
        if (camera)
        {
            camera->SetFocalPoint(worldCoords[0], worldCoords[1], worldCoords[2]);
        }
    }
    }
       void HandleMouseZoom()
       {
           // Get the current cursor position
           int x = this->Interactor->GetEventPosition()[0];
           int y = this->Interactor->GetEventPosition()[1];
           int z = this->Interactor->GetEventPosition()[2];

           // Calculate the difference in the Y direction to determine zoom factor
           int dy = y - this->InitialMousePosition[1];

           // Adjust the zoom level based on the Y movement
           double zoomFactor = 1.0 + dy * 0.01; // Adjust the zoom speed by changing 0.01


           vtkSmartPointer<vtkPropPicker> picker = vtkSmartPointer<vtkPropPicker>::New();

              // Perform the pick using the event position
              picker->Pick(x, y, 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());

              // Get the renderer where the pick occurred
              vtkRenderer* renderer = picker->GetRenderer();
           // Apply the zoom to the camera

           if (renderer)
           {
               vtkCamera* camera = renderer->GetActiveCamera();
               if (camera)
               {
                   camera->Zoom(zoomFactor);
                   renderer->ResetCameraClippingRange();
                   renderer->GetRenderWindow()->Render();
               }
               //renderer->GetRenderWindow()->Render();
           }

           // Update the initial position
           this->InitialMousePosition[0] = x;
           this->InitialMousePosition[1] = y;

           this->InvokeEvent(vtkCommand::EndInteractionEvent, nullptr);
       }

       void EndZoom()
       {
           // End zooming state
           this->StopState();
       }


private:
    bool LeftButtonDown = false;
    bool RightButtonDown = false;
    bool MiddleButtonDown = false;
    int InitialMousePosition[2] = {0, 0};
};


//  vtkStandardNewMacro(CustomInteractorStyle);
#endif // CUSTOMINTERACTORSTYLE_H
