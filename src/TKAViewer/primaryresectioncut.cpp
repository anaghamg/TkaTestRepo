/*
 * File Name : primaryresectioncut.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Class for performing primary cuts
 * Developer :Divya N S
 * Revision History : 8-8-2024
*/
#include "primaryresectioncut.h"
#include <QDebug>

PrimaryResectionCut::PrimaryResectionCut(QWidget *parent)
    : QWidget{parent}
{

}

void PrimaryResectionCut::PrimaryCut_Tibia(vtkPolyData* /*vtkMarchingCubes*/ surface_tibia,bool clickedval, double* tibia_Spacing, double*TLP, double*TMP, QString resecDepL, QString resecDepM )
{
    //qDebug()<<" resection cut tibia";
    if(firsttimecutting_tibia == false)
    {
        //------For patient data-----------------
        //Get the image bounds
        //        double bounds[6];
        //        //surface_tibia->GetOutput()->GetBounds(bounds);
        //        surface_tibia->GetBounds(bounds);


        //        // Calculate the center of the bounding box
        //        double centerX = (bounds[0] + bounds[1]) / 2.0;
        //        double centerY = (bounds[2] + bounds[3]) / 2.0;
        //        double centerZ = (bounds[4] + bounds[5]) / 2.0;

        //        //Setting a cutting planesource
        //        // Position the plane 6 mm
        //        double planeZT = bounds[0] + 19.0;
        //        planeSource_tibia->SetOrigin( planeZT,centerY - 50.0, centerZ- 50.0  );  //centerZ-45// Set origin relative to center
        //        planeSource_tibia->SetPoint1( planeZT,centerY + 50.0, centerZ - 50.0  );  // Point1 relative to center
        //        planeSource_tibia->SetPoint2( planeZT,centerY - 50.0, centerZ + 50.0  );

        //        planeSource_tibia->SetResolution(50, 50);
        //        planeSource_tibia->Update();
        //----------------------------------------
        //---------for phantom data--------------------

        float resec_depthLateral = resecDepL.toFloat();
        float resec_depthMedial = resecDepM.toFloat();
        double normalVector_chf2[3] = {TMP[0] - TLP[0], TMP[1] - TLP[1], TMP[2] - TLP[2]};
        planeSource_tibia->SetOrigin(TLP[0] , TLP[1],TLP[2]+ resec_depthLateral);
        planeSource_tibia->SetPoint1(TMP[0] , TMP[1],TMP[2]+ resec_depthMedial);
        planeSource_tibia->SetPoint2(TLP[0] , TLP[1]+ normalVector_chf2[0] , TLP[2]+ resec_depthLateral);
        planeSource_tibia->Update();
        //---------------------------------------------

        // Create a horizontal plane (e.g., xy-plane at z=0)
        vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
        plane->SetOrigin(planeSource_tibia->GetOrigin());  // The origin of the plane
        plane->SetNormal(planeSource_tibia->GetNormal());  // The normal points along the z-axis


        //Cutting the bone//--original
        clipper_tib->SetInputData(surface_tibia/*->GetOutput()*/);
        clipper_tib->SetClipFunction(plane);  // Set the clipping plane
        clipper_tib->InsideOutOff();
        clipper_tib->Update();


        //Extract boundary edges of the clipped polydata
        vtkSmartPointer<vtkFeatureEdges> featureEdges_tib = vtkSmartPointer<vtkFeatureEdges>::New();
        featureEdges_tib->SetInputData(clipper_tib->GetOutput());
        featureEdges_tib->BoundaryEdgesOn();
        featureEdges_tib->FeatureEdgesOff();
        featureEdges_tib->ManifoldEdgesOff();
        featureEdges_tib->NonManifoldEdgesOff();
        featureEdges_tib->Update();

        //Fill the extracted boundary
        vtkSmartPointer<vtkPolyData> boundaryEdges_tib = featureEdges_tib->GetOutput();
        //Fill the hole using vtkContourTriangulator
        triangulator_tib->SetInputData(boundaryEdges_tib);
        triangulator_tib->Update();


        //Set color to the filled boundary
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledColor_tib =vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledColor_tib->SetNumberOfComponents(3);
        BoundaryfilledColor_tib->SetNumberOfTuples(triangulator_tib->GetOutput()->GetNumberOfCells());
        BoundaryfilledColor_tib->FillComponent(0, 101);  // Red channel
        BoundaryfilledColor_tib->FillComponent(1, 101);  // Green channel
        BoundaryfilledColor_tib->FillComponent(2, 101);  // Blue channel
        triangulator_tib->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_tib);

        //        for (int i = 0; i < triangulator_tib->GetOutput()->GetNumberOfCells(); i++)
        //        {

        //            float rgb[4] ={101,101,101,255};
        //            BoundaryfilledColor_tib->InsertTuple(i, rgb);
        //        }
        //triangulator_tib->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_tib);
        //triangulator_tib->Update();


        // Create a color array for the clipped polyData
        vtkSmartPointer<vtkUnsignedCharArray> polydata1_color_tib = vtkSmartPointer<vtkUnsignedCharArray>::New();
        polydata1_color_tib->SetNumberOfComponents(3);
        polydata1_color_tib->SetNumberOfTuples(clipper_tib->GetOutput()->GetNumberOfCells());
        polydata1_color_tib->FillComponent(0, 255);  // Red channel
        polydata1_color_tib->FillComponent(1, 255);  // Green channel
        polydata1_color_tib->FillComponent(2, 255);  // Blue channel
        clipper_tib->GetOutput()->GetCellData()->SetScalars(polydata1_color_tib);

        //        for (int i = 0; i < clipper_tib->GetOutput()->GetNumberOfCells(); ++i)
        //        {
        //            float rgb1[4] ={255,255,255,255};//
        //            polydata1_color_tib->InsertTuple(i,rgb1);
        //        }
        // clipper_tib->GetOutput()->GetCellData()->SetScalars(polydata1_color_tib);
        //        //clipper_tib->Update();

        //Appending the surface created and the clipped polydata.
        appendFilter_tib->AddInputData(clipper_tib->GetOutput());
        appendFilter_tib->AddInputData(triangulator_tib->GetOutput());
        appendFilter_tib->Update();


        firsttimecutting_tibia = true;

    }
    emit SignalCutdata_tibia(appendFilter_tib->GetOutput(), clickedval);


}

void PrimaryResectionCut::PrimaryCut_Femur(vtkPolyData /*vtkMarchingCubes*/ * surface_femur,bool clickedV, double* femur_spacing,
                                           double* m_FLE, double*m_FME, double*m_FLPC, double* m_FMPC,
                                           QString m_latDistdepth,QString m_medDistdepth, QString m_latPosterDepth,QString m_medPosterDepth, double* Femkneecenter)
{
    //qDebug()<<" resection cut femur";

    if(firsttimecutting_femur == false)
    {
        //Get the image bounds
        double bounds[6];
        surface_femur->GetBounds(bounds);


        // Calculate the center of the bounding box
        double centerX = (bounds[0] + bounds[1]) / 2.0;
        double centerY = (bounds[2] + bounds[3]) / 2.0;
        double centerZ = (bounds[4] + bounds[5]) / 2.0;

        //----------------------------------setting plane for Horizontal cut(distal femoral cut)----------------------------
        // Position the plane 8 mm
        //---------------------for patient data------------------------------
        //        double planeZ = bounds[1] - 11.0;
        //        planeSource_FemHorizontal->SetOrigin(planeZ, centerY - 50.0, centerZ - 50.0 ); /*65*/ // Set origin relative to center
        //        planeSource_FemHorizontal->SetPoint1(planeZ, centerY + 50.0, centerZ - 50.0 );  // Point1 relative to center
        //        planeSource_FemHorizontal->SetPoint2(planeZ, centerY - 50.0, centerZ + 50.0 );
        //        planeSource_FemHorizontal->SetResolution(20, 20);
        //        planeSource_FemHorizontal->Update();
        //        clipplane_horizontal->SetOrigin(planeSource_FemHorizontal->GetOrigin());  // The origin of the plane
        //        clipplane_horizontal->SetNormal(planeSource_FemHorizontal->GetNormal());  // The normal points along the z-axis
        //----------------for phantom data------------------------------

        float latDistresec_depth = m_latDistdepth.toFloat();
        float medDistresec_depth = m_medDistdepth.toFloat();

        qDebug()<<"distal rec dep Late = "<<latDistresec_depth;
         qDebug()<<"distal rec dep Medi = "<<medDistresec_depth;

        int offset_distal = 40 ;// in order to place the plane at the centre of the anatomy
        double normalVector_chf_distcut[3] = {m_FLE[0] - m_FME[0], m_FLE[1] - m_FME[1], m_FLE[2] - m_FME[2]};
        planeSource_FemHorizontal->SetOrigin(m_FME[0] , m_FME[1]-offset_distal,m_FME[2]+ medDistresec_depth  );
        planeSource_FemHorizontal->SetPoint1(m_FLE[0] , m_FLE[1]-offset_distal,m_FLE[2]+ latDistresec_depth );
        planeSource_FemHorizontal->SetPoint2(m_FME[0] , m_FME[1]-offset_distal+ normalVector_chf_distcut[0] , m_FME[2]+ medDistresec_depth);
        planeSource_FemHorizontal->Update();

        clipplane_horizontal->SetOrigin(planeSource_FemHorizontal->GetOrigin());  // The origin of the plane
        clipplane_horizontal->SetNormal(planeSource_FemHorizontal->GetNormal());  // The normal points along the z-axis

        //--------------------------------setting plane for vertical cut(anterior femur cut-advanced)---------------------------------
        // Position the plane 11 mm
        //--------for patient data-------------------
        //        double planeZ1 = bounds[2] + 25.0; //(since there is patella also, doing it only on femur takes some more than 11)
        //        planeSource_Femvertical->SetOrigin(centerX- 50.0, planeZ1 , centerZ-50);  //*centerY+15*/ Set origin relative to center
        //        planeSource_Femvertical->SetPoint1(centerX+ 50.0 , planeZ1, centerZ-50);  // Point1 relative to center
        //        planeSource_Femvertical->SetPoint2(centerX- 50.0, planeZ1 , centerZ+50);
        //        planeSource_Femvertical->SetResolution(20, 20);
        //        planeSource_Femvertical->Update();


        float latanteriorec_depth = 59 ; //Femkneecenter[1]
        double normalVector_chf_antecut[3] = {m_FMPC[0] - m_FLPC[0], m_FMPC[1] - m_FLPC[1], m_FMPC[2] - m_FLPC[2]};
        planeSource_Femvertical->SetOrigin(m_FLPC[0] , m_FLPC[1]+ latanteriorec_depth,m_FLPC[2]);
        planeSource_Femvertical->SetPoint1(m_FMPC[0] , m_FMPC[1]+ latanteriorec_depth,m_FMPC[2]);
        planeSource_Femvertical->SetPoint2(m_FLPC[0] , m_FLPC[1]+ latanteriorec_depth, m_FLPC[2]+ normalVector_chf_antecut[0]);
        planeSource_Femvertical->Update();


        //setting the plane
        clipplane_vertical->SetOrigin(planeSource_Femvertical->GetOrigin());  // The origin of the plane
        clipplane_vertical->SetNormal(planeSource_Femvertical->GetNormal());  // The normal points along the z-axis


        //---------------------------------------Posterior femur cut (backside of femur cutting)-------------------------------------------
        //-----------for patient data------------
        //        double planeZPost = bounds[3] - 20.0; //(since there is patella also, doing it only on femur takes some more than 11)
        //        planeSource_FemverticalPosteriorcut->SetOrigin(centerX- 50.0, planeZPost , centerZ-50);  //*centerY+15*/ Set origin relative to center
        //        planeSource_FemverticalPosteriorcut->SetPoint1(centerX+ 50.0 , planeZPost, centerZ-50);  // Point1 relative to center
        //        planeSource_FemverticalPosteriorcut->SetPoint2(centerX- 50.0, planeZPost , centerZ+50);
        //        planeSource_FemverticalPosteriorcut->Update();
        //----------for phantom data------------------
        float latPostrec_depth = m_latPosterDepth.toFloat();//18
        float medPostrec_depth = m_medPosterDepth.toFloat();//20.5
        double normalVector_chf_postcut[3] = {m_FMPC[0] - m_FLPC[0], m_FMPC[1] - m_FLPC[1], m_FMPC[2] - m_FLPC[2]};
        planeSource_FemverticalPosteriorcut->SetOrigin(m_FLPC[0] , m_FLPC[1]+ latPostrec_depth,m_FLPC[2] );
        planeSource_FemverticalPosteriorcut->SetPoint1(m_FMPC[0] , m_FMPC[1]+ medPostrec_depth,m_FMPC[2]);
        planeSource_FemverticalPosteriorcut->SetPoint2(m_FLPC[0] , m_FLPC[1]+ latPostrec_depth, m_FLPC[2]+ normalVector_chf_postcut[0]);
        planeSource_FemverticalPosteriorcut->Update();

//        double normalVector_chf_postcut[3] = {m_FLPC[0] - m_FMPC[0], m_FLPC[1] - m_FMPC[1], m_FLPC[2] - m_FMPC[2]};
//        planeSource_FemverticalPosteriorcut->SetOrigin(m_FMPC[0] , m_FMPC[1]+ latPostrec_depth,m_FMPC[2] );
//        planeSource_FemverticalPosteriorcut->SetPoint1(m_FLPC[0] , m_FLPC[1]+ medPostrec_depth,m_FLPC[2]);
//        planeSource_FemverticalPosteriorcut->SetPoint2(m_FMPC[0] , m_FMPC[1]+ latPostrec_depth, m_FMPC[2]+ normalVector_chf_postcut[0]);
//        planeSource_FemverticalPosteriorcut->Update();

        //setting the plane
        clipplane_vertical_poster->SetOrigin(planeSource_FemverticalPosteriorcut->GetOrigin());  // The origin of the plane
        clipplane_vertical_poster->SetNormal(planeSource_FemverticalPosteriorcut->GetNormal());  // The normal points along the z-axis

        //------------chamfer cuts 1----------------------------\--------------------------------------

        //getting the centre of the distal cut plane
        double chamfercutP1[3];
        int distaloffset = 14; //to move the centre point a bit away from centre
        chamfercutP1[0]=  planeSource_FemHorizontal->GetCenter()[0];
        chamfercutP1[1]=  planeSource_FemHorizontal->GetCenter()[1] +distaloffset;
        chamfercutP1[2]=  planeSource_FemHorizontal->GetCenter()[2];
        //getting the center of the posterior cut plane
        int post_offset = 25; //to move the centre point a bit away from centre
        double chamfercutP2[3];
        chamfercutP2[0]=  planeSource_FemverticalPosteriorcut->GetCenter()[0];
        chamfercutP2[1]=  planeSource_FemverticalPosteriorcut->GetCenter()[1]-post_offset;//+post_offset
        chamfercutP2[2]=  planeSource_FemverticalPosteriorcut->GetCenter()[2];

        double normalVector_chamf[3] = {chamfercutP1[0] - chamfercutP2[0], chamfercutP1[1] - chamfercutP2[1], chamfercutP1[2] - chamfercutP2[2]};

        planeChamfercut1->SetOrigin(chamfercutP2[0] , chamfercutP2[1],chamfercutP2[2]);
        planeChamfercut1->SetPoint1(chamfercutP1[0] , chamfercutP1[1],chamfercutP1[2]);
        planeChamfercut1->SetPoint2(chamfercutP2[0]+ normalVector_chamf[1] , chamfercutP2[1] , chamfercutP2[2]);
        planeChamfercut1->Update();


        clipplane_chamfercut1->SetNormal(planeChamfercut1->GetNormal());
        clipplane_chamfercut1->SetOrigin(planeChamfercut1->GetOrigin());

        //--------------------------chamfer cut 2------------------/----------------------------------

        double chamfercutP3[3];
        chamfercutP3[0]=  planeSource_FemHorizontal->GetCenter()[0];
        chamfercutP3[1]=  planeSource_FemHorizontal->GetCenter()[1];//+13
        chamfercutP3[2]=  planeSource_FemHorizontal->GetCenter()[2];

        //getting the center of the anterior cut plane
        int antoffset = 5;
        double chamfercutP4[3];
        chamfercutP4[0] =  planeSource_Femvertical->GetCenter()[0];
        chamfercutP4[1] =  planeSource_Femvertical->GetCenter()[1] + antoffset;
        chamfercutP4[2] =  planeSource_Femvertical->GetCenter()[2];

        double normalVector_chamf2[3] = {chamfercutP3[0] - chamfercutP4[0], chamfercutP3[1] - chamfercutP4[1], chamfercutP3[2] - chamfercutP4[2]};
        planeChamfercut2->SetOrigin(chamfercutP4[0] , chamfercutP4[1],chamfercutP4[2]);
        planeChamfercut2->SetPoint1(chamfercutP3[0] , chamfercutP3[1],chamfercutP3[2]);
        planeChamfercut2->SetPoint2(chamfercutP4[0]+ normalVector_chamf2[1] , chamfercutP4[1] , chamfercutP4[2]);
        planeChamfercut2->Update();


        clipplane_chamfercut2->SetNormal(planeChamfercut2->GetNormal());
        clipplane_chamfercut2->SetOrigin(planeChamfercut2->GetOrigin());

        //double points_chamf[2][3]; //for patientdata
        //        points_chamf[0][0] = 150.389;//135.127;
        //        points_chamf[0][1] = 85.0029;//62.9826;
        //        points_chamf[0][2] = 112.459;//103.581;
        //        points_chamf[1][0] = 137.023;//158.964;
        //        points_chamf[1][1] = 65.5285;//99.1219;
        //        points_chamf[1][2] = 101.733;//122.209;


        //        // cutting by rotating the posterior cut plane to 45 degree
        //        //midpoint of posterior plane
        //        double center_posteriorplane[3] = {
        //            (m_FMPC[0] + m_FLPC[0]) / 2.0,
        //            (m_FMPC[1] + m_FLPC[1]) / 2.0,
        //            (m_FMPC[2] + m_FLPC[2]) / 2.0
        //        };

        //        //midpoint of distal plane
        //        double center_distalplane[3] = {
        //            (m_FMPC[0] + m_FLPC[0]) / 2.0,
        //            (m_FMPC[1] + m_FLPC[1]) / 2.0,
        //            (m_FMPC[2] + m_FLPC[2]) / 2.0
        //        };


        //        double normalVector_chf[3] = {center_posteriorplane[0] - center_distalplane[0], center_posteriorplane[1] - center_distalplane[1], center_posteriorplane[2] - center_distalplane[2]};
        //        planeChamfercut1->SetOrigin(center_distalplane[0] , center_distalplane[1]+ latPostrec_depth,center_distalplane[2]);
        //        planeChamfercut1->SetPoint1(center_posteriorplane[0] , center_posteriorplane[1]+ medPostrec_depth,center_posteriorplane[2]);
        //        planeChamfercut1->SetPoint2(center_distalplane[0] , center_distalplane[1]+ latPostrec_depth, center_distalplane[2]+ normalVector_chf[0]);





        //        //        double angleRad_1 = vtkMath::RadiansFromDegrees(-45.0); // Convert degrees to radians
        //        //        double newNormal_1[3] = {
        //        //            0,
        //        //            std::cos(angleRad_1),std::sin(angleRad_1)

        //        //        };
        //        //        double center_postch[3] = {
        //        //            (m_FMPC[0] + m_FLPC[0]) / 2.0,
        //        //            (m_FMPC[1] + m_FLPC[1]) / 2.0,
        //        //            (m_FMPC[2] + m_FLPC[2]) / 2.0
        //        //        };
        //        //        planeChamfercut1->SetNormal(newNormal_1);
        //        //        planeChamfercut1->SetCenter(center_postch);
        //        planeChamfercut1->Update();
        //        //---------------------for patient data-----------
        //        //        double normalVector_chf[3] = {points_chamf[1][0] - points_chamf[0][0], points_chamf[1][1] - points_chamf[0][1], points_chamf[1][2] - points_chamf[0][2]};
        //        //        planeChamfercut1->SetOrigin(points_chamf[0]);
        //        //        planeChamfercut1->SetPoint1(points_chamf[1]);
        //        //        //planeChamfercut1->SetPoint2(points_chamf[0][0], points_chamf[0][1], points_chamf[0][2] + normalVector_chf[0]);// for patientdata
        //        //        planeChamfercut1->SetPoint2(points_chamf[0][0], points_chamf[0][1]+ normalVector_chf[1], points_chamf[0][2] );// for phantom data

        //        //        planeChamfercut1->Update();
        //        //------------------------------------------------

        // clipplane_chamfercut1->SetNormal(planeChamfercut1->GetNormal());
        //clipplane_chamfercut1->SetOrigin(planeChamfercut1->GetOrigin());

        //--------------------------chamfer cut 2-----------'\' cut-----------------------------------------
        //double points_chamf2[2][3];
        //        points_chamf2[0][0] = 130.102;
        //        points_chamf2[0][1] = 138.5;
        //        points_chamf2[0][2] = 61.13;
        //        points_chamf2[1][0] = 156.435;
        //        points_chamf2[1][1] = 81.5;
        //        points_chamf2[1][2] = 66.041;
        //---------for phantom data-------------


        //        // cutting by rotating the anterior cut plane to 45 degree
        //        double normalVector_chf2[3] = {m_FMPC[0] - m_FLPC[0], m_FMPC[1] - m_FLPC[1], m_FMPC[2] - m_FLPC[2]};
        //        planeChamfercut2->SetOrigin(m_FLPC[0] , m_FLPC[1]+ latanteriorec_depth,m_FLPC[2]);
        //        planeChamfercut2->SetPoint1(m_FMPC[0] , m_FMPC[1]+ latanteriorec_depth,m_FMPC[2]);
        //        planeChamfercut2->SetPoint2(m_FLPC[0] , m_FLPC[1]+ latanteriorec_depth, m_FLPC[2]+ normalVector_chf2[0]);

        //        double angleRad = vtkMath::RadiansFromDegrees(45.0); // Convert degrees to radians
        //        double newNormal[3] = {
        //            0,
        //            std::cos(angleRad),std::sin(angleRad)

        //        };
        //        planeChamfercut2->SetNormal(newNormal);
        //        planeChamfercut2->Update();


        //        //------for patinet data-------------
        //        //        double normalVector_chf2[3] = {points_chamf2[1][0] - points_chamf2[0][0], points_chamf2[1][1] - points_chamf2[0][1], points_chamf2[1][2] - points_chamf2[0][2]};
        //        //        planeChamfercut2->SetOrigin(points_chamf2[0]);
        //        //        planeChamfercut2->SetPoint1(points_chamf2[1]);
        //        //        //planeChamfercut2->SetPoint2(points_chamf2[0][0] , points_chamf2[0][1], points_chamf2[0][2] + normalVector_chf2[0]); //for ptient data
        //        //        planeChamfercut2->SetPoint2(points_chamf2[0][0] , points_chamf2[0][1]+ normalVector_chf2[0], points_chamf2[0][2] ); //for phantom data
        //        //        planeChamfercut2->SetResolution(20,20);
        //        //        planeChamfercut2->Update();
        //        //-----------------------------



        //        clipplane_chamfercut2->SetNormal(planeChamfercut2->GetNormal());
        //        clipplane_chamfercut2->SetOrigin(planeChamfercut2->GetOrigin());


        //******************Applying the clipping planes to the data*********************************

        // ......Cut1...... :
        //Clip the original polydata using the vertical plane  (posterial femoral)
        vtkSmartPointer<vtkClipPolyData> clipper_posteriorvertical = vtkSmartPointer<vtkClipPolyData>::New();
        clipper_posteriorvertical->SetInputData(surface_femur);
        clipper_posteriorvertical->SetClipFunction(clipplane_vertical_poster);  // Set the clipping plane
        clipper_posteriorvertical->InsideOutOn();//  InsideOutOff for patient data
        clipper_posteriorvertical->Update();

        //Closing the clipped data(will not get expected results with vtkFillholesFilter bcz the boundary of the hole can be missing)
        //Extract boundary edges of the clipped polydata
        vtkSmartPointer<vtkFeatureEdges> featureEdgesposteriorvertical = vtkSmartPointer<vtkFeatureEdges>::New();
        featureEdgesposteriorvertical->SetInputData(clipper_posteriorvertical->GetOutput());
        featureEdgesposteriorvertical->BoundaryEdgesOn();
        featureEdgesposteriorvertical->FeatureEdgesOff();
        featureEdgesposteriorvertical->ManifoldEdgesOff();
        featureEdgesposteriorvertical->NonManifoldEdgesOff();
        featureEdgesposteriorvertical->Update();

        //Fill the extracted boundary
        vtkSmartPointer<vtkPolyData> boundaryEdgesposteriorvertical = featureEdgesposteriorvertical->GetOutput();

        // Clean up boundary edges
        vtkSmartPointer<vtkCleanPolyData> cleanEdges = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanEdges->SetInputData(boundaryEdgesposteriorvertical);
        cleanEdges->Update();

        //Fill the hole using vtkContourTriangulator
        triangulator_femposteriorvertical->SetInputData(cleanEdges->GetOutput());
        triangulator_femposteriorvertical->Update();


        //Set color to the filled boundary
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledColorposteriorvertical =vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledColorposteriorvertical->SetNumberOfComponents(3);
        BoundaryfilledColorposteriorvertical->SetNumberOfTuples(triangulator_femposteriorvertical->GetOutput()->GetNumberOfCells());
        BoundaryfilledColorposteriorvertical->FillComponent(0, 101);  // Red channel
        BoundaryfilledColorposteriorvertical->FillComponent(1, 101);  // Green channel
        BoundaryfilledColorposteriorvertical->FillComponent(2, 101);  // Blue channel
        triangulator_femposteriorvertical->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColorposteriorvertical);

        //        for (int i = 0; i < triangulator_femposteriorvertical->GetOutput()->GetNumberOfCells(); i++)
        //        {
        //            float rgb[4] ={101,101,101,255};
        //            BoundaryfilledColorposteriorvertical->InsertTuple(i, rgb);
        //        }
        //        triangulator_femposteriorvertical->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColorposteriorvertical);
        //triangulator_femposteriorvertical->Update();

        //SetColor to the original cut data:
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledOriData1 =vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledOriData1->SetNumberOfComponents(3);
        BoundaryfilledOriData1->SetNumberOfTuples(clipper_posteriorvertical->GetOutput()->GetNumberOfCells());
        BoundaryfilledOriData1->FillComponent(0, 255);  // Red channel
        BoundaryfilledOriData1->FillComponent(1, 255);  // Green channel
        BoundaryfilledOriData1->FillComponent(2, 255);  // Blue channel
        clipper_posteriorvertical->GetOutput()->GetCellData()->SetScalars(BoundaryfilledOriData1);

        //        for (int i = 0; i < clipper_posteriorvertical->GetOutput()->GetNumberOfCells(); i++)
        //        {
        //            float rgb[4] ={255,255,255,255};
        //            BoundaryfilledOriData1->InsertTuple(i, rgb);
        //        }
        //        clipper_posteriorvertical->GetOutput()->GetCellData()->SetScalars(BoundaryfilledOriData1);
        //clipper_posteriorvertical->Update();


        vtkSmartPointer<vtkAppendPolyData> appendFilter_cut1 = vtkSmartPointer<vtkAppendPolyData>::New();
        appendFilter_cut1->AddInputData(clipper_posteriorvertical->GetOutput());
        appendFilter_cut1->AddInputData(triangulator_femposteriorvertical->GetOutput());
        appendFilter_cut1->Update();

        // Clean the appended data to prepare it for the next clip operation
        vtkSmartPointer<vtkCleanPolyData> cleanAppended_cut1 = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanAppended_cut1->SetInputData(appendFilter_cut1->GetOutput());
        cleanAppended_cut1->Update();

        //        // Optionally, use vtkTriangleFilter if non-triangular geometry needs to be handled
        //        vtkSmartPointer<vtkTriangleFilter> triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
        //        triangleFilter->SetInputData(cleanAppended->GetOutput());
        //        triangleFilter->Update();



        //......Cut2...... :

        //--------------testing------------------------
        // Step 3: Create vtkSelectPolyData and set the plane as its clip function
//         vtkSmartPointer<vtkSelectPolyData> selectPolyData = vtkSmartPointer<vtkSelectPolyData>::New();
//         selectPolyData->SetInputData(cleanAppended_cut1->GetOutput());
//         selectPolyData->SetLoop(planeSource_FemHorizontal->GetOutput()->GetPoints());
//         selectPolyData->SetSelectionModeToSmallestRegion();
//         selectPolyData->Update();
         //----------------------------------------


        // Clip the original polydata using the vertical plane  (posterial femoral)
        clipper_combined->SetInputData(cleanAppended_cut1/*clipper_posteriorvertical*/->GetOutput());
        clipper_combined->SetClipFunction(clipplane_vertical);  // Set the clipping plane
        clipper_combined->InsideOutOff();//important  InsideOutOn for patientdata
        clipper_combined->Update();


        //Extract boundary edges of the clipped polydata
        // Clip the original polydata using the vertical plane  (posterial femoral)
        vtkSmartPointer<vtkFeatureEdges> featureEdges_combined = vtkSmartPointer<vtkFeatureEdges>::New();
        featureEdges_combined->SetInputData(clipper_combined->GetOutput());
        featureEdges_combined->BoundaryEdgesOn();
        featureEdges_combined->FeatureEdgesOff();
        featureEdges_combined->ManifoldEdgesOff();
        featureEdges_combined->NonManifoldEdgesOff();
        featureEdges_combined->Update();

        //Fill the extracted boundary
        vtkSmartPointer<vtkPolyData> boundaryEdges_combined= featureEdges_combined->GetOutput();

        //Fill the hole using vtkContourTriangulator
        triangulator_femcombined->SetInputData(boundaryEdges_combined);
        triangulator_femcombined->Update();

        //Set color to the filled boundary
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledColor_combined=vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledColor_combined->SetNumberOfComponents(3);
        BoundaryfilledColor_combined->SetNumberOfTuples(triangulator_femcombined->GetOutput()->GetNumberOfCells());
        BoundaryfilledColor_combined->FillComponent(0, 101);  // Red channel
        BoundaryfilledColor_combined->FillComponent(1, 101);  // Green channel
        BoundaryfilledColor_combined->FillComponent(2, 101);  // Blue channel
        triangulator_femcombined->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_combined);

        //        for (int i = 0; i < triangulator_femcombined->GetOutput()->GetNumberOfCells(); i++)
        //        {
        //            float rgb[4] ={101,101,101,255};
        //            BoundaryfilledColor_combined->InsertTuple(i, rgb);
        //        }
        //        triangulator_femcombined->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_combined);
        //triangulator_femcombined->Update();


        //combinig
        vtkSmartPointer<vtkAppendPolyData> appendFilter_cut2 = vtkSmartPointer<vtkAppendPolyData>::New();
        appendFilter_cut2->AddInputData(clipper_combined->GetOutput());
        appendFilter_cut2->AddInputData(triangulator_femcombined->GetOutput());
        appendFilter_cut2->Update();

        // Clean the appended data to prepare it for the next clip operation
        vtkSmartPointer<vtkCleanPolyData> cleanAppended_cut2 = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanAppended_cut2->SetInputData(appendFilter_cut2->GetOutput());
        cleanAppended_cut2->Update();

        //......Cut3...... :
        //Get the output of the vertical cut polydata and
        //clip that output using the horizontalplane  (distal femoral)
        clipper_fem->SetInputData(cleanAppended_cut2/*clipper_combined*/->GetOutput());
        clipper_fem->SetClipFunction(clipplane_horizontal);  // Set the clipping plane
        clipper_fem->InsideOutOn();//important
        clipper_fem->Update();

        // Clip the original polydata using the vertical plane  (posterial femoral)
        vtkSmartPointer<vtkFeatureEdges> featureEdges_clipper_fem = vtkSmartPointer<vtkFeatureEdges>::New();
        featureEdges_clipper_fem->SetInputData(clipper_fem->GetOutput());
        featureEdges_clipper_fem->BoundaryEdgesOn();
        featureEdges_clipper_fem->FeatureEdgesOff();
        featureEdges_clipper_fem->ManifoldEdgesOff();
        featureEdges_clipper_fem->NonManifoldEdgesOff();
        featureEdges_clipper_fem->Update();

        //Fill the extracted boundary
        vtkSmartPointer<vtkPolyData> boundaryEdges_clipper_fem= featureEdges_clipper_fem->GetOutput();
        //Fill the hole using vtkContourTriangulator
        triangulator_fem_1->SetInputData(boundaryEdges_clipper_fem);
        triangulator_fem_1->Update();

        //Set color to the filled boundary
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledColor_fem_1=vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledColor_fem_1->SetNumberOfComponents(3);
        BoundaryfilledColor_fem_1->SetNumberOfTuples(triangulator_fem_1->GetOutput()->GetNumberOfCells());
        BoundaryfilledColor_fem_1->FillComponent(0, 101);  // Red channel
        BoundaryfilledColor_fem_1->FillComponent(1, 101);  // Green channel
        BoundaryfilledColor_fem_1->FillComponent(2, 101);  // Blue channel
        triangulator_fem_1->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_fem_1);

        //        for (int i = 0; i < triangulator_fem_1->GetOutput()->GetNumberOfCells(); i++)
        //        {
        //            float rgb[4] ={101,101,101,255};
        //            BoundaryfilledColor_fem_1->InsertTuple(i, rgb);
        //        }
        //        triangulator_fem_1->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_fem_1);
        //triangulator_fem_1->Update();

        //combinig
        vtkSmartPointer<vtkAppendPolyData> appendFilter_cut3 = vtkSmartPointer<vtkAppendPolyData>::New();
        appendFilter_cut3->AddInputData(clipper_fem->GetOutput());
        appendFilter_cut3->AddInputData(triangulator_fem_1->GetOutput());
        appendFilter_cut3->Update();

        // Clean the appended data to prepare it for the next clip operation
        vtkSmartPointer<vtkCleanPolyData> cleanAppended_cut3 = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanAppended_cut3->SetInputData(appendFilter_cut3->GetOutput());
        cleanAppended_cut3->Update();



        //......Cut4...... :
        // Clip the original polydata using the vertical plane  (posterial femoral)
        vtkSmartPointer<vtkClipPolyData> clipper_chamfer1 = vtkSmartPointer<vtkClipPolyData>::New();
        clipper_chamfer1->SetInputData(cleanAppended_cut3->GetOutput()/*surface_femur->GetOutput()*/);
        clipper_chamfer1->SetClipFunction(clipplane_chamfercut1);  // Set the clipping plane
        clipper_chamfer1->InsideOutOff();//important  InsideOutOn for patient bone
        clipper_chamfer1->Update();

        //Closing the clipped data
        // Clip the original polydata using the vertical plane  (posterial femoral)
        //Extract boundary edges of the clipped polydata
        vtkSmartPointer<vtkFeatureEdges> featureEdges_chamfer1 = vtkSmartPointer<vtkFeatureEdges>::New();
        featureEdges_chamfer1->SetInputData(clipper_chamfer1->GetOutput());
        featureEdges_chamfer1->BoundaryEdgesOn();
        featureEdges_chamfer1->FeatureEdgesOff();
        featureEdges_chamfer1->ManifoldEdgesOff();
        featureEdges_chamfer1->NonManifoldEdgesOff();
        featureEdges_chamfer1->Update();

        //Fill the extracted boundary
        vtkSmartPointer<vtkPolyData> boundaryEdges_chamfer1 = featureEdges_chamfer1->GetOutput();
        //Fill the hole using vtkContourTriangulator
        triangulator_chamfer1->SetInputData(boundaryEdges_chamfer1);
        triangulator_chamfer1->Update();


        //Set color to the filled boundary
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledColor_chamfer1=vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledColor_chamfer1->SetNumberOfComponents(3);
        BoundaryfilledColor_chamfer1->SetNumberOfTuples(triangulator_chamfer1->GetOutput()->GetNumberOfCells());
        BoundaryfilledColor_chamfer1->FillComponent(0, 101);  // Red channel
        BoundaryfilledColor_chamfer1->FillComponent(1, 101);  // Green channel
        BoundaryfilledColor_chamfer1->FillComponent(2, 101);  // Blue channel
        triangulator_chamfer1->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_chamfer1);
        //        for (int i = 0; i < triangulator_chamfer1->GetOutput()->GetNumberOfCells(); i++)
        //        {
        //            float rgb[4] ={101,101,101,255};
        //            BoundaryfilledColor_chamfer1->InsertTuple(i, rgb);
        //        }
        //        triangulator_chamfer1->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_chamfer1);
        //triangulator_chamfer1->Update();


        //combinig
        vtkSmartPointer<vtkAppendPolyData> appendFilter_cut4 = vtkSmartPointer<vtkAppendPolyData>::New();
        appendFilter_cut4->AddInputData(clipper_chamfer1->GetOutput());
        appendFilter_cut4->AddInputData(triangulator_chamfer1->GetOutput());
        appendFilter_cut4->Update();

        // Clean the appended data to prepare it for the next clip operation
        vtkSmartPointer<vtkCleanPolyData> cleanAppended_cut4 = vtkSmartPointer<vtkCleanPolyData>::New();
        cleanAppended_cut4->SetInputData(appendFilter_cut4->GetOutput());
        cleanAppended_cut4->Update();
        //******************************************************

        //......Cut5...... :
        // Clip the original polydata using the vertical plane  (posterial femoral)
        vtkSmartPointer<vtkClipPolyData> clipper_chamfer2 = vtkSmartPointer<vtkClipPolyData>::New();
        clipper_chamfer2->SetInputData(cleanAppended_cut4->GetOutput()/*surface_femur->GetOutput()*/);
        clipper_chamfer2->SetClipFunction(clipplane_chamfercut2);  // Set the clipping plane
        clipper_chamfer2->InsideOutOff();//InsideOutOff for patientdata
        clipper_chamfer2->Update();

        //Closing the clipped data
        //Extract boundary edges of the clipped polydata
        vtkSmartPointer<vtkClipPolyData> clipper_chamfer2_from3cut = vtkSmartPointer<vtkClipPolyData>::New();
        clipper_chamfer2_from3cut->SetInputData(clipper_chamfer2->GetOutput()/*surface_femur->GetOutput()*/);
        clipper_chamfer2_from3cut->SetClipFunction(clipplane_chamfercut2);  // Set the clipping plane
        clipper_chamfer2_from3cut->InsideOutOff();  //InsideOutOff for patirntdata
        clipper_chamfer2_from3cut->Update();
        vtkSmartPointer<vtkFeatureEdges> featureEdges_chamfer2 = vtkSmartPointer<vtkFeatureEdges>::New();
        featureEdges_chamfer2->SetInputData(clipper_chamfer2_from3cut->GetOutput());
        featureEdges_chamfer2->BoundaryEdgesOn();
        featureEdges_chamfer2->FeatureEdgesOff();
        featureEdges_chamfer2->ManifoldEdgesOff();
        featureEdges_chamfer2->NonManifoldEdgesOff();
        featureEdges_chamfer2->Update();

        //Fill the extracted boundary
        vtkSmartPointer<vtkPolyData> boundaryEdges_chamfer2 = featureEdges_chamfer2->GetOutput();
        //Fill the hole using vtkContourTriangulator
        triangulator_chamfer2->SetInputData(boundaryEdges_chamfer2);
        triangulator_chamfer2->Update();

        //Set color to the filled boundary
        vtkSmartPointer<vtkUnsignedCharArray> BoundaryfilledColor_chamfer2=vtkSmartPointer<vtkUnsignedCharArray>::New();
        BoundaryfilledColor_chamfer2->SetNumberOfComponents(3);
        BoundaryfilledColor_chamfer2->SetNumberOfTuples(triangulator_chamfer2->GetOutput()->GetNumberOfCells());
        BoundaryfilledColor_chamfer2->FillComponent(0, 101);  // Red channel
        BoundaryfilledColor_chamfer2->FillComponent(1, 101);  // Green channel
        BoundaryfilledColor_chamfer2->FillComponent(2, 101);  // Blue channel
        triangulator_chamfer2->GetOutput()->GetCellData()->SetScalars(BoundaryfilledColor_chamfer2);



        //-------------for patient data------------------
        //        appendFilter_Final->AddInputData(clipper_chamfer2_from3cut->GetOutput());
        //        appendFilter_Final->AddInputData(triangulator_chamfer2->GetOutput());
        //        appendFilter_Final->Update();

        //----------for phantom data ---------
        appendFilter_Final->AddInputData(appendFilter_cut3/*clipper_chamfer2_from3cut*//*cleanAppended_cut3*/->GetOutput());

         //appendFilter_Final->AddInputData(planeSource_FemHorizontal->GetOutput());
        //appendFilter_Final->AddInputData(triangulator_chamfer2->GetOutput());
        //  appendFilter_Final->AddInputData(planeChamfercut1->GetOutput());
        //   appendFilter_Final->AddInputData(planeChamfercut2->GetOutput());
        //        appendFilter_Final->AddInputData(planeSource_FemverticalPosteriorcut->GetOutput());
        //appendFilter_Final->AddInputData(planeChamfercut1->GetOutput());
        // appendFilter_Final->AddInputData(planeChamfercut2->GetOutput());
        //appendFilter_Final->AddInputData(triangulator_chamfer2->GetOutput());

        appendFilter_Final->Update();
        //------------------




        //                        vtkSmartPointer<vtkSTLWriter> writwr_stl = vtkSmartPointer<vtkSTLWriter>::New();
        //                        writwr_stl->SetFileTypeToBinary();
        //                        writwr_stl->SetInputData(cleanAppended_cut3->GetOutput());
        //                        writwr_stl->SetFileName("PrimaryCut_femur.stl");
        //                        writwr_stl->Write();


        firsttimecutting_femur = true;
    }
    emit SignalCutdata_femur(appendFilter_Final->GetOutput(), clickedV);
}
