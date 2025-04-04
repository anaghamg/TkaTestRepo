#ifndef D3CUSTOMINTERACTORSTYLE_H
#define D3CUSTOMINTERACTORSTYLE_H
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVolume.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkRenderWindow.h>
#include <QDebug>
#include <vtkRendererCollection.h>
#include <vtkTransform.h>

#include <vtkPropPicker.h>
#include <vtkCamera.h>
#include <vtkRenderer.h>

class d3CustomInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
    static d3CustomInteractorStyle* New()
    {
        return new  d3CustomInteractorStyle;
    }
    void SetSurfaceActor(vtkSmartPointer<vtkActor> actor)
        {
            this->SurfaceActor = actor;
        }
    virtual void OnLeftButtonDown() override
       {
           this->LeftButtonDown = true;
//           if (this->RightButtonDown)
//           {
//               qDebug()<<"Left and right";
//               //this->InitialMousePosition = this->GetInteractor()->GetEventPosition();

//               this->AdjustWindowLevel();

//           }
           if(this ->MiddleButtonDown)
           {
                qDebug()<<"Left and middle";
               this->StartRolling();
           }
           else
           {
                qDebug()<<" Left oly";
               this->StartRotate(); // Rotate with left mouse button

           }
          // this->InitialMousePosition = this->GetInteractor()->GetEventPosition();
          vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
       }

       virtual void OnLeftButtonUp() override
       {
           this->LeftButtonDown = false;
//           if (this->RightButtonDown)
//           {
//               this->EndWindowLevelAdjustment();
//           }
        /*   else*/ if (this->MiddleButtonDown)
                   {
                       this->EndRolling();
                   }
           else
           {
               this->EndRotate();
           }
          vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
       }

       virtual void OnRightButtonDown() override
       {
           this->RightButtonDown = true;
//           if (this->LeftButtonDown)
//           {
//                 qDebug()<<" rightandLeft ";
//                 this->InitialMousePosition= this->GetInteractor()->GetEventPosition();

//               this->AdjustWindowLevel();
//           }
//           else
//           {
                qDebug()<<" right only ";
               this->StartPan(); // Pan with right mouse button
 //          }
           //this->InitialMousePosition = this->GetInteractor()->GetEventPosition();
           vtkInteractorStyleTrackballCamera::OnRightButtonDown();

       }

       virtual void OnRightButtonUp() override
       {
           this->RightButtonDown = false;
//           if (this->LeftButtonDown)
//           {
//               this->EndWindowLevelAdjustment();
//           }
//           else
//           {

               this->EndPan();
         //  }
           vtkInteractorStyleTrackballCamera::OnRightButtonUp();
         //  this->Superclass::OnRightButtonUp();
       }

       virtual void OnMouseMove() override
       {

          /* if (this->LeftButtonDown && this->RightButtonDown)
           {
               AdjustWindowLevel();
           }
       else*/ if (this->LeftButtonDown && this->MiddleButtonDown)
                  {
                      this->RollVolume();
                  }
          else if (this->MiddleButtonDown)
           {
               //return;
               HandleMouseZoom();
           }

           else
           {
               vtkInteractorStyleTrackballCamera::OnMouseMove();
           }
         //   this->Superclass::OnMouseMove();
       }

    virtual void OnMiddleButtonDown() override
    {
        this->MiddleButtonDown = true;
        if (this->LeftButtonDown)
               {
                   this->StartRolling();
               }
               else
               {
                 this->SetCameraFocalPointAtCursor();
                 this->StartZoom();
        }
    }
    virtual void OnMiddleButtonUp() override
    {
        this->MiddleButtonDown = false;

        if (this->LeftButtonDown)
               {
                   this->EndRolling();
               }
        else
               {

                if (this->State == VTKIS_ZOOM)
                {
                    this->EndZoom();
                }
        }
    }

protected:
    d3CustomInteractorStyle()
           : LeftButtonDown(false), RightButtonDown(false),MiddleButtonDown(false),/* Volume(nullptr),*/ InitialWindowLevel(127.5), InitialWindowWidth(256) {}

//    void StartWindowLevelAdjustment()

//       {
//           //this->InitialMousePosition = this->GetInteractor()->GetEventPosition();
//           vtkVolumeProperty* volumeProperty = Volume->GetProperty();
//           double range[2];
//           volumeProperty->GetScalarOpacity()->GetRange(range);
//           this->InitialWindowLevel = (range[0] + range[1]) / 2;
//           this->InitialWindowWidth = range[1] - range[0];
//           double windowWidth = range[1] - range[0];
//           qDebug()<<"wind"<<windowWidth;
//       }

//       void EndWindowLevelAdjustment()
//       {

//       }


//       void AdjustWindowLevel()
//       {
//           int* currentMousePosition = this->GetInteractor()->GetEventPosition();
//           int dx = currentMousePosition[0] ;//- InitialMousePosition[0];
//           int dy = currentMousePosition[1] ;//- InitialMousePosition[1];

//           // Adjust window and level based on mouse movement
////           double windowLevel = InitialWindowLevel + dy * 0.1;
////           double windowWidth = InitialWindowWidth + dx * 0.1;

//           double windowLevel = InitialWindowLevel + dy ;//* 0.1;
//           double windowWidth = InitialWindowWidth + dx;// * 0.1;

//           qDebug()<<" InitialMousePosition[0] = "<<InitialMousePositionNew[0]
//                  <<" InitialMousePosition[1]="<<InitialMousePositionNew[1];

//           qDebug()<<" currentMousePosition[0] = "<<currentMousePosition[0]
//                  <<" currentMousePosition[1]="<<currentMousePosition[1];
//           qDebug()<<" windowLevel = "<<windowLevel
//       <<" windowWidth="<<windowWidth;
//           if (Volume)
//           {
//               vtkVolumeProperty* volumeProperty = Volume->GetProperty();
//               volumeProperty->GetRGBTransferFunction()->RemoveAllPoints();
//               volumeProperty->GetRGBTransferFunction()->AddRGBSegment(windowLevel - 0.5 * windowWidth, 0.5, 0.0, 0.0,
//                                                                        windowLevel + 0.5 * windowWidth, 1.0, 1.0, 1.0);
//               volumeProperty->GetScalarOpacity()->RemoveAllPoints();
//               volumeProperty->GetScalarOpacity()->AddSegment(windowLevel - 0.5 * windowWidth, 0.0,
//                                                              windowLevel + 0.5 * windowWidth, 1.0);

//               this->GetInteractor()->GetRenderWindow()->Render();
//                  }
//       }

       void StartZoom()
          {
            this->StartState(VTKIS_ZOOM);
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
              int dy = y - this->InitialMousePositionNew[1];

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
              this->InitialMousePositionNew[0] = x;
              this->InitialMousePositionNew[1] = y;

              this->InvokeEvent(vtkCommand::EndInteractionEvent, nullptr);
          }

          void EndZoom()
          {
              // End zooming state
              this->StopState();
          }


          //*************************
          void StartRolling()
             {
                 // Save the initial mouse position when rolling starts
                 this->InitialMouseRoll[0] = this->GetInteractor()->GetEventPosition()[0];
                 this->InitialMouseRoll[1] = this->GetInteractor()->GetEventPosition()[1];
             }

             void EndRolling()
             {
                 // Stop rolling
             }

             void RollVolume()
             {
                 // Get current mouse position
                 int* currentMousePosition = this->GetInteractor()->GetEventPosition();
                 int dz = currentMousePosition[2] - this->InitialMouseRoll[2];
                 int dx = currentMousePosition[0] - this->InitialMouseRoll[0]; // Mouse movement in X direction
                    int dy = currentMousePosition[1] - this->InitialMouseRoll[1]; // Mouse movement in Y direction


                 // Adjust the camera roll based on horizontal mouse movement
                 vtkRenderer* renderer = this->GetInteractor()->GetRenderWindow()->GetRenderers()->GetFirstRenderer();
                 if (renderer)
                 {
                     vtkCamera* camera = renderer->GetActiveCamera();
                     if (camera)
                     {

                         // Calculate the rotation angle based on mouse movement
                         double rotationAngle = (dx + dy) * 0.5; // Adjust the sensitivity as needed

                             // Get the center of the volume
//                        double* volumeCenter = this->Volume->GetCenter();

//                         // Create a transform to rotate the volume
//                         vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
//                         transform->PostMultiply(); // Ensure the rotation is applied after the current transformation
//                         transform->Translate(-volumeCenter[0], -volumeCenter[1], -volumeCenter[2]);
//                         transform->RotateZ(/*dz*0.5*/rotationAngle); // Rotate around the Z-axis of the volume
//                         transform->Translate(volumeCenter[0], volumeCenter[1], volumeCenter[2]);

//                         if (this->Volume->GetUserTransform())
//                          {
//                              transform->Concatenate(this->Volume->GetUserTransform());
//                          }
camera->Azimuth(-rotationAngle);
camera->Modified();

                         // Apply the transformation to the volume
                         //this->Volume->SetUserTransform(transform);

                       //camera->Roll(dz * 0.5);
                         this->GetInteractor()->GetRenderWindow()->Render();
                     }
                 }

                 // Update the initial mouse position for continuous rolling
                 this->InitialMouseRoll[0] = currentMousePosition[0];
                 this->InitialMouseRoll[1] = currentMousePosition[1];
             }



   private:
       bool LeftButtonDown;
       bool RightButtonDown;
       bool MiddleButtonDown;
       int* InitialMousePosition;
       double InitialWindowLevel;
       double InitialWindowWidth;
  int InitialMousePositionNew[2] = {0, 0};
  int InitialMouseRoll[2]={0,0};
      //vtkSmartPointer<vtkVolume> Volume;
   vtkSmartPointer<vtkActor> SurfaceActor;

};
#endif // D3CUSTOMINTERACTORSTYLE_H
