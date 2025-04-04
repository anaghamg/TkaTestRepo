/*
 * File Name : TKAthreedview.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header of 3D viewer of planning module
 * Developer :Divya N S
 * Revision History : 1-8-2024
*/
#ifndef TKATHREEDVIEW_H
#define TKATHREEDVIEW_H


#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkInteractionStyle);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

#include <QWidget>
#include <QtCore/QVariant>
#include <QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>
#include <QVBoxLayout>

#include "HeaderIncludes.h"
#include "primaryresectioncut.h"
#include "axisdisplayview.h"
#include "implantload.h"
#include "implanttransformations.h"
#include "vtkCamera.h"

class TKAThreeDView;

////-----class for capturing the hovering events when mouse id over the corresponding QVTKOpenGLNativeWidget-------------
///

class MyQVTKOpenGLNativeWidget : public QVTKOpenGLNativeWidget
{
    Q_OBJECT

public:
    explicit MyQVTKOpenGLNativeWidget(QWidget *parent = nullptr) : QVTKOpenGLNativeWidget(parent) {}

signals:
    void hovered();   // Signal for mouse hover
    void unhovered(); // Signal for mouse leave


protected:
    // Handle mouse hover event
    void enterEvent(QEvent *event) override {
        emit hovered();
        QVTKOpenGLNativeWidget::enterEvent(event);
    }

    // Handle mouse leave event
    void leaveEvent(QEvent *event) override {
        emit unhovered();
        QVTKOpenGLNativeWidget::leaveEvent(event);
    }

};

class TKAThreeDView : public QWidget
{
    Q_OBJECT

public:
    explicit TKAThreeDView(QWidget *parent = nullptr);
    ~TKAThreeDView();

    //QString config_filename = QDir::currentPath()+"//Config_TKA//config_3D.ini";
    QString config_filename = QDir::currentPath()+"//Config_TKA//config_3D_Phantom.ini";

    //    QString m_direc_femur =QDir::currentPath()+"/Femur_Tibia_dicom/Femur";
    //    QString m_direc_tibia =QDir::currentPath()+"/Femur_Tibia_dicom/Tibia";

    //QString m_direc_femur = QDir::currentPath()+"/Femur_Tibia_dicom/femur_lt_bone";
    //QString m_direc_tibia = QDir::currentPath()+"/Femur_Tibia_dicom/tibia_lt_bone";

    //QString m_direc_femur = "D:/DivyaNair/RoboticTKA/Qt_Code/TKA_SVN_LATEST/Build/Segmentation_batfile/femur.stl";//"";
    //QString m_direc_tibia = "D:/DivyaNair/RoboticTKA/Qt_Code/TKA_SVN_LATEST/Build/Segmentation_batfile/tibia.stl";


    /////////////////////////phantom data------------------------------------------------
     //QString m_direc_femur = "D:/DivyaNair/RoboticTKA/Qt_Code/TKA_SVN_LATEST/TKA_Kinematics_Ver1.0/code/femur_annotation.stl";//"";
     //QString m_direc_tibia = "D:/DivyaNair/RoboticTKA/Qt_Code/TKA_SVN_LATEST/TKA_Kinematics_Ver1.0/code/tibia_annotation.stl";


    //    QString SAKS_femurDir = QDir::currentPath() + "/Segmentation_batfile/output_femur_dicom";
    //    QString SAKS_tibiaDir = QDir::currentPath() + "/Segmentation_batfile/output_tibia_dicom";

     QString m_direc_femur = QDir::currentPath() + "/Segmentation_batfile/output/FemurModel.stl";
     QString m_direc_tibia = QDir::currentPath() + "/Segmentation_batfile/output/TibiaModel.stl";

     //QString m_direc_femur_test = "D:/DivyaNair/RoboticTKA/Qt_Code/TKA_SVN_LATEST/TKA_Kinematics_Ver1.0/femur_annotation.stl";//"";
    // QString m_direc_tibia_test = "D:/DivyaNair/RoboticTKA/Qt_Code/TKA_SVN_LATEST/TKA_Kinematics_Ver1.0/tibia_annotation.stl";



    QGridLayout *gridLayout3D;
    MyQVTKOpenGLNativeWidget *TopRightLateralFemur3DWidget;
    MyQVTKOpenGLNativeWidget *BottomLeftAnteriorTibia3DWidget;
    MyQVTKOpenGLNativeWidget *BottomMiddleDistalTibia3DWidget;
    MyQVTKOpenGLNativeWidget *TopMiddleDistalFemur3DWidget;
    MyQVTKOpenGLNativeWidget *BottomRightLateralTibia3DWidget;
    MyQVTKOpenGLNativeWidget *TopLeftAnteriorFemur3DWidget;

    //---Added 5-9-24---------
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout_17;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_AntFem;
    QGridLayout *gridLayout_LatFem;
    QGridLayout *gridLayout_DistFem;
    QGridLayout *gridLayout_AntTib;
    QGridLayout *gridLayout_LatTib;
    QGridLayout * gridLayout_DisTib;
    QSpacerItem *horizontalSpacer_22;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *horizontalSpacer_20;
    QGridLayout *FAButn_gridLayout;
    QPushButton *pushButton_FAright;
    QLabel *label_Fem_VarValgValue;
    QPushButton *pushButton_FArightdown;
    QLabel *label_FemVarVal;
    QPushButton *pushButton_FAleftdown;
    QPushButton *pushButton_FAdown;
    QPushButton *pushButton_Fem_reset;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer1;//parvathy
    QSpacerItem *horizontalSpacer2;//parvathy
    QSpacerItem *verticalSpacer1;//parvathy
    QPushButton *pushButton_FAleft;
    QPushButton *pushButton_FAup;
    QSpacerItem *horizontalSpacer_13;
    QGridLayout *gridLayout_9;
    QGridLayout *FLButn_gridLayout;
    QPushButton *pushButton_FLup;
    QPushButton *pushButton_FLleftdown;
    QLabel *label_FLExten;
    QPushButton *pushButton_FLdown;
    QPushButton *pushButton_FLleft;
    QLabel *label_FL_FlexExtenValue;
    QPushButton *pushButton_FLright;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_FLrightdown;
    QSpacerItem *horizontalSpacer_19;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_15;
    QLabel *label_ValueF5;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_6;
    QLabel *label_ValueF3;
    QLabel *label_ValueF1;
    QLabel *label_2;
    QLabel *label_ValueF4;
    QLabel *label_ValueF6;
    QLabel *label_ValueF2;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_12;
    QGridLayout *TABtn_gridLayout;
    QLabel *label_Tib_VarValgusValue;
    QPushButton *pushButton_TAright;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_TAdown;
    QPushButton *pushButton_TArightdown;
    QPushButton *pushButton_TAup;
    QPushButton *pushButton_TAleft;
    QPushButton *pushButton_TAleftdown;
    QLabel *label_TibVarVal;
    QHBoxLayout *horizontalLayout;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_Tib_reset_2;
    QSpacerItem *horizontalSpacer_11;
    QGridLayout *gridLayout_12;
    QGridLayout *TLBtn_gridLayout;
    QPushButton *pushButton_TLup;
    QPushButton *pushButton_TLright;
    QLabel *label_TibPSlopeValue;
    QPushButton *pushButton_TLrightdown;
    QLabel *label_TibPslop;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_TLleftdown;
    QPushButton *pushButton_TLdown;
    QPushButton *pushButton_TLleft;
    QSpacerItem *horizontalSpacer_14;
    QGridLayout *gridLayout_18;
    QGridLayout *gridLayout_11;
    QLabel *label_16;
    QGridLayout *TDBtn_gridLayout;
    QPushButton *pushButton_TDleftdown;
    QPushButton *pushButton_TDup;
    QLabel *label_tibExtInt;
    QLabel *label_Tib_InterExterValue;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_TDleft;
    QPushButton *pushButton_TDrightdown;
    QPushButton *pushButton_TDdown;
    QPushButton *pushButton_TDright;
    QSpacerItem *horizontalSpacer_9;
    QGridLayout *gridLayout_16;
    QLabel *label_Value21;
    QLabel *label_Value13;
    QLabel *label_Value23;
    QLabel *label_Value12;
    QLabel *label_Value22;
    QSpacerItem *horizontalSpacer_15;
    QLabel *label_15;
    QSpacerItem *horizontalSpacer_16;
    QLabel *label_ValueF11;
    QSpacerItem *horizontalSpacer_17;
    QGridLayout *gridLayout_8;
    QGridLayout *FDButn_gridLayout;
    QPushButton *pushButton_FDrightdown;
    QPushButton *pushButton_FDleftdown;
    QPushButton *pushButton_FDup;
    QPushButton *pushButton_FDdown;
    QPushButton *pushButton_FDleft;
    QLabel *label_FDIntExt;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_FDIntExtValue;
    QPushButton *pushButton_FDright;
    QSpacerItem *horizontalSpacer_18;
    QScrollBar *verticalScrollBar_1;
    QScrollBar *verticalScrollBar_2;
    QScrollBar *verticalScrollBar_3;
    QWidget *page_2;
    QFrame *frame_centerpanel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_4;
    QFrame *frame_rightpanel;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_Next;
    QComboBox *comboBox_Models;
    //QDoubleSpinBox *doubleSpinBox_Femur;
    QLabel *label_PolySize;
    QComboBox *comboBox_Manufacturer;
    QSpacerItem *verticalSpacer;
    //QDoubleSpinBox *doubleSpinBo_Poly;
    //QDoubleSpinBox *doubleSpinBox_Tibia;
    QPushButton *pushButton_Back;
    QLabel *label_FemurSize;
    QLabel *label_TibiaSize;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;

    //added ob 10-9-2024
    QLabel *label_FDIntExtPCA;
    QLabel *label_FDIntExtPCAValue;

    //parvathy
    QVBoxLayout *m_qvbcellayout;
    QHBoxLayout *m_qhbvaruslbl;
    QVBoxLayout *m_qvbFDlayout;
    QHBoxLayout *m_qhbFDIElayout;
    QVBoxLayout *m_qvbFlexextbtn ;
    QHBoxLayout *m_qhbflExt;
    QVBoxLayout *m_qvbtiblayout;
    QHBoxLayout *m_qhbvaruslbltib;
    QVBoxLayout *m_qvbtibmid;
    QHBoxLayout *m_qhblbltibmid ;
    QVBoxLayout *m_qvblattiblay;
    QHBoxLayout *m_qhbtibSlop;

    //------------------------

    vtkSmartPointer<vtkProperty> BoneProperty =  vtkSmartPointer<vtkProperty>::New();

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow_tka[6];
    vtkSmartPointer<vtkRenderer> renderer_tka[6];
    vtkSmartPointer<vtkRenderWindowInteractor> interactor_tka[6];
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>  style_1[6];

    vtkSmartPointer<vtkActor> actor_3dtka[6];
    vtkSmartPointer<vtkPolyDataMapper> mapper_3dtka[6];

    vtkSmartPointer<vtkDICOMImageReader> m_tkaReaderFemur_SAKS = vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkSmartPointer<vtkDICOMImageReader> m_tkaReaderTibia_SAKS =vtkSmartPointer<vtkDICOMImageReader>::New();

    vtkSmartPointer<vtkSTLReader> m_tkaReaderFemur = vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkSTLReader> m_tkaReaderTibia =vtkSmartPointer<vtkSTLReader>::New();
    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilterFemur = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();
    vtkSmartPointer<vtkSmoothPolyDataFilter> smoothFilterTibia = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();

    vtkSmartPointer<vtkExtractVOI> m_extractvoi_Femur =vtkSmartPointer<vtkExtractVOI>::New();
    vtkSmartPointer<vtkExtractVOI> m_extractvoi_Tibia =vtkSmartPointer<vtkExtractVOI>::New();
    //vtkSmartPointer<vtkMarchingCubes> surface_Femur =  vtkSmartPointer<vtkMarchingCubes>::New();
    // vtkSmartPointer<vtkMarchingCubes> surface_Tibia =  vtkSmartPointer<vtkMarchingCubes>::New();
    vtkSmartPointer<vtkImplicitModeller> implicitModeller = vtkSmartPointer<vtkImplicitModeller>::New();


    //----Femur----
    vtkSmartPointer<vtkActor> femurMechAxis_ActorAnterior= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurMechAxis1_ActorDistal= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurMechAxis2_ActorLateral= vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> femurTEA_ActorAnterior= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurTEA_ActorDistal= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurTEA_ActorLateral= vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> femurPCA_ActorAnterior= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurPCA_ActorDistal= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurPCA_ActorLateral= vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> femurFemCompAx_ActorAnterior= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurFemCompAx_ActorDistal= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femurFemCompAx_ActorLateral= vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> femur_cutActor_Anterior =vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femur_cutActor_Distal =vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> femur_cutActor_Lateral =vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> m_femoral_stlcomponentactor_Anter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_femoral_stlcomponentactor_Dist = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_femoral_stlcomponentactor_Later = vtkSmartPointer<vtkActor>::New();


    //----Tibia----
    vtkSmartPointer<vtkActor> tibiaMechAxis_ActorAnterior= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> tibiaMechAxis1_ActorDistal= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> tibiaMechAxis2_ActorLateral= vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> tibiaTPL_ActorAnterior= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> tibiaTPL_ActorDistal= vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> tibiaTPL_ActorLateral= vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> tibia_cutActor_Anterior =vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> tibia_cutActor_Distal =vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> tibia_cutActor_Lateral =vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> m_tibial_stlcomponentactor_Anter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_tibial_stlcomponentactor_Dist = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_tibial_stlcomponentactor_Later = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_tibial_stlspacerComponentactor_Anter = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_tibial_stlspacerComponentactor_Dist = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_tibial_stlspacerComponentactor_Later = vtkSmartPointer<vtkActor>::New();


    //annotation points
    vtkSmartPointer<vtkActor> m_actorAnotationPointsFemur_Anterior =   vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_actorAnotationPointsFemur_Distal =   vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_actorAnotationPointsFemur_Lateral =   vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkActor> m_actorAnotationPointsTibia_Anterior =   vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_actorAnotationPointsTibia_Distal =   vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> m_actorAnotationPointsTibia_Lateral =   vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkTransform> SizeTransform_Femur = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> SizeTransformTransformFilter_Femur = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    vtkSmartPointer<vtkTransform> SizeTransform_Tibia = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> SizeTransformTransformFilter_Tibia = vtkSmartPointer<vtkTransformPolyDataFilter>::New();

    vtkSmartPointer<vtkTransform> SizeTransform_Spacer = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkTransformPolyDataFilter> SizeTransformTransformFilter_Spacer = vtkSmartPointer<vtkTransformPolyDataFilter>::New();



    PrimaryResectionCut *m_ObjPrimaryResectionCut= nullptr;
    AxisDisplayView *m_ObjAxisDisplayView = nullptr;
    ImplantLoad * m_ObjImplantLoad = nullptr;
    ImplantTransformations * m_ObjImplantTransformations = nullptr;






    bool firsttimeFlag = false;
    bool Axis_firsttime = false;
    bool Cut_firsttime_tibia = false;
    bool Cut_firsttime_femur = false;
    bool AnotAxisDisFirstTime = false;
    bool ImplantLoadingFirstTime = false;
    bool implantloadButtonClicked = false;
    bool implantsizefemurFirstTime = false;
    bool implantsizetibiaFirstTime = false;
    bool implantsizespacerFirstTime = false;
    double *femur_pixelspacing;
    double *tibia_pixelspacing;

    //for femur
    float FemAnterVarVal = 0.0;
    float FemDistInterExter = 3.0;
    float FemLatFlexExt = 3.0;

    //for tibia
    float TibAnterVarVal = 0.0;
    float TibDistInterExter = 3.0;
    float TibLatFlexExt = 3.0;
    QString m_stylesheetforViewButtons =  "min-width: 15px;"
                                            "min-height: 15px;"
                                            "icon-size: 16px; background-color:transparent;";
    vtkNew<vtkNamedColors> colors_tka;


public slots:

    void InitializeViewsFemur(QString id, QString view, QString kneepart, QString roll,QString elevation,QString azimuth);
    void UpdateTibiaData(vtkPolyData*,bool);
    void UpdateFemurData(vtkPolyData*,bool);
    void PrimarycutFemurandTibia(bool);
    void AxisDisplaySlot(bool);
    void UpdateAxisDisplay_Femur(vtkPolyData*,vtkPolyData*,vtkPolyData*,vtkPolyData* );
    void UpdateAxisDisplay_Tibia(vtkPolyData*,vtkPolyData*);
    void UpdateAnatomicalPoint(bool);
    void LoadImplant(bool);
    void TranslationsofImplantFemur(bool);
    void TranslationsofImplantTibia(bool);
    void FemurComponentSizeAdjustment();
    void TibiaComponentSizeAdjustment();
    void SpacerComponentSizeAdjustment();
    void AdjustBoneOpacity(bool);
    void AdjustImplantOpacity(bool);
    void IntializePlanningWindows();
    //--added on 24-09-2024---------
    void SlotForAnteriorFemButtonsVisibilityTrue();
    void SlotForAnteriorFemButtonsVisibilityFalse();
    void SlotForDistalFemButtonsVisibilityTrue();
    void SlotForDistalFemButtonsVisibilityFalse();
    void SlotForLateralFemButtonsVisibilityTrue();
    void SlotForLateralFemButtonsVisibilityFalse();
    void SlotForAnteriorTibButtonsVisibilityTrue();
    void SlotForAnteriorTibButtonsVisibilityFalse();
    void SlotForDistalTibButtonsVisibilityTrue();
    void SlotForDistalTibButtonsVisibilityFalse();
    void SlotForLateralTibButtonsVisibilityTrue();
    void SlotForLateralTibButtonsVisibilityFalse();

    //testing
    //void cameratestvalues();



    void TranslationsiconChange();
    void Translationsiconrelease();

signals:

    void Enablespinboxes(bool);

private:
    //--Custom ineteractor style to reset the rotation when mouse is released------
    class TKACustomInteractorStyle : public vtkInteractorStyleTrackballCamera
    {
    public:

        static TKACustomInteractorStyle* New()
        {
            return new  TKACustomInteractorStyle;
        }
        vtkTypeMacro(TKACustomInteractorStyle, vtkInteractorStyleTrackballCamera);

        virtual void OnLeftButtonUp() override
        {
            // Reset the camera position, focal point, and view up vector on mouse release
            this->GetCurrentRenderer()->ResetCamera();
            vtkCamera* camera = this->GetCurrentRenderer()->GetActiveCamera();
            //qDebug()<<"viewup = = "<< camera->GetViewUp()[0]<<camera->GetViewUp()[1]<<camera->GetViewUp()[2];
            //camera->SetViewUp(0, 0, 0);//patient data
             camera->SetViewUp(0, 0, -1);//phantom data
            camera->SetFocalPoint(this->InitialFocalPoint);
            camera->SetPosition(this->InitialPosition);
            camera->Zoom(initialzoom);
            camera->Roll(initialRoll);
            camera->Elevation(initialElevation);
            camera->Azimuth(initialAzimuth);
            camera->SetClippingRange(initialnearclip,initialfarclip);

            camera->Modified();


            // Re-render the window to reflect changes
            this->GetCurrentRenderer()->GetRenderWindow()->Render();

            // Forward events
            vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
        }

    public:
        double InitialPosition[3];    // Store initial camera position
        double InitialFocalPoint[3];  // Store initial camera focal point
        float initialRoll;
        float initialElevation;
        float initialAzimuth;
        float initialnearclip;
        float initialfarclip;
        float initialzoom;
    };


    vtkSmartPointer<TKACustomInteractorStyle> customstyle[6];
};

#endif // TKATHREEDVIEW_H
