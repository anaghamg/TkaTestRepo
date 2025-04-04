/*
 * File Name : threedview.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Main class of 3D viewer of planning module
 * Developer :Divya N S
 * Revision History : 1-8-2024
*/
#include "tkathreedview.h"
#include <QLabel>

TKAThreeDView::TKAThreeDView(QWidget *parent) :
    QWidget(parent)

{


    QGridLayout *m_gltoplayout = new QGridLayout;


    gridLayout_17 = new QGridLayout();
    gridLayout_17->setObjectName("gridLayout_17");

    gridLayout3D = new QGridLayout();
    gridLayout3D->setObjectName("gridLayout3D");
    gridLayout3D->setRowStretch(0,1);
    gridLayout3D->setRowStretch(1,1);
    gridLayout3D->setRowStretch(2,1);
    gridLayout3D->setColumnStretch(0,1);
    gridLayout3D->setColumnStretch(1,1);
    gridLayout3D->setColumnStretch(2,1);

    gridLayout_AntFem = new QGridLayout();
    //    gridLayout_AntFem->setRowStretch(0,1);
    //    gridLayout_AntFem->setRowStretch(1,1);
    //    gridLayout_AntFem->setRowStretch(2,1);
    //    gridLayout_AntFem->setColumnStretch(0,1);
    //    gridLayout_AntFem->setColumnStretch(1,1);
    //    gridLayout_AntFem->setColumnStretch(2,1);
    gridLayout_AntFem->setObjectName("gridLayout_AntFem");

    TopLeftAnteriorFemur3DWidget = new MyQVTKOpenGLNativeWidget();
    TopLeftAnteriorFemur3DWidget->setObjectName("TopLeftAnteriorFemur3DWidget");
    TopLeftAnteriorFemur3DWidget->setMinimumSize(QSize(350, 350));


    gridLayout_AntFem->addWidget(TopLeftAnteriorFemur3DWidget, 1, 1, 1, 1);

    FAButn_gridLayout = new QGridLayout();
    FAButn_gridLayout->setObjectName("FAButn_gridLayout");

    pushButton_FAright = new QPushButton();
    pushButton_FAright->setObjectName("pushButton_FAright");

    QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setRetainSizeWhenHidden(true);//added on 24-9-2024 important to preserve the layout even when the button is visible or hidden.
    sizePolicy1.setHeightForWidth(pushButton_FAright->sizePolicy().hasHeightForWidth());
    pushButton_FAright->setSizePolicy(sizePolicy1);


    gridLayout_AntFem->addWidget(pushButton_FAright, 1, 2, 1, 1);


    label_Fem_VarValgValue = new QLabel();
    label_Fem_VarValgValue->setContentsMargins(15,0,15,0);
    label_Fem_VarValgValue->setObjectName("label_VarValValue");


    pushButton_FArightdown = new QPushButton();
    pushButton_FArightdown->setObjectName("pushButton_FArightdown");
    sizePolicy1.setHeightForWidth(pushButton_FArightdown->sizePolicy().hasHeightForWidth());
    pushButton_FArightdown->setSizePolicy(sizePolicy1);


    horizontalSpacer1 = new QSpacerItem(5, 0, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
    m_gltoplayout->addItem(horizontalSpacer1, 0, 6, 1, 1);


    gridLayout_AntFem->addWidget(pushButton_FArightdown, 0, 2, 1, 1);


    label_FemVarVal = new QLabel();
    label_FemVarVal->setObjectName("label_VarVal");



    pushButton_FAleftdown = new QPushButton();
    pushButton_FAleftdown->setObjectName("pushButton_FAleftdown");
    sizePolicy1.setHeightForWidth(pushButton_FAleftdown->sizePolicy().hasHeightForWidth());
    pushButton_FAleftdown->setSizePolicy(sizePolicy1);


    gridLayout_AntFem->addWidget(pushButton_FAleftdown, 0,0, 1, 1);


    pushButton_Fem_reset = new QPushButton();
    pushButton_Fem_reset->setObjectName("pushButton_Fem_reset");
    sizePolicy1.setHeightForWidth(pushButton_Fem_reset->sizePolicy().hasHeightForWidth());
    pushButton_Fem_reset->setStyleSheet(m_stylesheetforViewButtons);
    FAButn_gridLayout->addWidget(pushButton_Fem_reset, 0, 0, 1, 1);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

    FAButn_gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);

    pushButton_FAleft = new QPushButton();
    pushButton_FAleft->setObjectName("pushButton_FAleft");
    sizePolicy1.setHeightForWidth(pushButton_FAleft->sizePolicy().hasHeightForWidth());
    pushButton_FAleft->setSizePolicy(sizePolicy1);


    gridLayout_AntFem->addWidget(pushButton_FAleft, 1,0 ,1, 1);


    m_qvbcellayout = new QVBoxLayout;
    m_qhbvaruslbl = new QHBoxLayout;


    pushButton_FAup = new QPushButton();
    pushButton_FAup->setObjectName("pushButton_FAup");
    sizePolicy1.setHeightForWidth(pushButton_FAup->sizePolicy().hasHeightForWidth());
    pushButton_FAup->setSizePolicy(sizePolicy1);

    horizontalSpacer2 = new QSpacerItem(5, 0, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
    m_gltoplayout->addItem(horizontalSpacer2, 0, 2, 1, 1);


    m_qhbvaruslbl->addWidget(label_FemVarVal,2,Qt::AlignRight);
    m_qhbvaruslbl->addWidget(label_Fem_VarValgValue,2,Qt::AlignLeft);


    horizontalSpacer_18 = new QSpacerItem(20, 30, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);


    m_qvbcellayout->addLayout(m_qhbvaruslbl);
    m_qvbcellayout->addWidget(pushButton_FAup,1,Qt::AlignCenter);

    gridLayout_AntFem->addLayout(m_qvbcellayout, 0,1, 1, 1, Qt::AlignCenter);



    horizontalSpacer_13 = new QSpacerItem(8, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);


    label_ValueF1 = new QLabel();
    label_ValueF1->setContentsMargins(15,0,15,0);
    label_ValueF1->setObjectName("labelPlanning");


    label_ValueF4 = new QLabel();
    label_ValueF4->setContentsMargins(15,0,15,0);
    label_ValueF4->setObjectName("labelPlanning");


    pushButton_FAdown = new QPushButton();
    pushButton_FAdown->setObjectName("pushButton_FAdown");
    sizePolicy1.setHeightForWidth(pushButton_FAdown->sizePolicy().hasHeightForWidth());
    pushButton_FAdown->setSizePolicy(sizePolicy1);


    QHBoxLayout *m_qhbAFrow = new QHBoxLayout;

    m_qhbAFrow->addWidget(label_ValueF1,1,Qt::AlignLeft);
    m_qhbAFrow->addWidget(pushButton_FAdown,2,Qt::AlignCenter);
    m_qhbAFrow->addWidget(label_ValueF4,1,Qt::AlignRight);

    gridLayout_AntFem->addLayout(m_qhbAFrow, 2,1, 1, 1,  Qt::AlignCenter);

    gridLayout3D->addLayout(gridLayout_AntFem, 0, 0);


    gridLayout_15 = new QGridLayout();
    gridLayout_15->setColumnStretch(1, 1);   // Column 2 stretch factor (to add space after Column 2)
    gridLayout_15->setColumnStretch(2, 1);   // C
    gridLayout_15->setObjectName("gridLayout_15");

    gridLayout_LatFem = new QGridLayout();
    gridLayout_LatFem->setObjectName("gridLayout_LatFem");
    //Parvathy
    gridLayout_LatFem->setRowStretch(0,1);
    gridLayout_LatFem->setRowStretch(1,1);
    gridLayout_LatFem->setRowStretch(2,1);
    gridLayout_LatFem->setColumnStretch(0,1);
    gridLayout_LatFem->setColumnStretch(1,1);
    gridLayout_LatFem->setColumnStretch(2,1);

    TopRightLateralFemur3DWidget = new MyQVTKOpenGLNativeWidget();
    TopRightLateralFemur3DWidget->setObjectName("TopRightLateralFemur3DWidget");
    TopRightLateralFemur3DWidget->setMinimumSize(QSize(350, 350));


    gridLayout_LatFem->addWidget(TopRightLateralFemur3DWidget, 1,1, 1, 1);



    FLButn_gridLayout = new QGridLayout();
    FLButn_gridLayout->setObjectName("FLButn_gridLayout");

    pushButton_FLup = new QPushButton();
    pushButton_FLup->setObjectName("pushButton_FLup");

    sizePolicy1.setHeightForWidth(pushButton_FLup->sizePolicy().hasHeightForWidth());
    pushButton_FLup->setSizePolicy(sizePolicy1);


    pushButton_FLleftdown = new QPushButton();
    pushButton_FLleftdown->setObjectName("pushButton_FLleftdown");
    sizePolicy1.setHeightForWidth(pushButton_FLleftdown->sizePolicy().hasHeightForWidth());
    pushButton_FLleftdown->setSizePolicy(sizePolicy1);


    gridLayout_LatFem->addWidget(pushButton_FLleftdown, 0, 0, 1, 1);


    label_FLExten = new QLabel();
    label_FLExten->setObjectName("label_VarVal");


    pushButton_FLdown = new QPushButton();
    pushButton_FLdown->setObjectName("pushButton_FLdown");
    gridLayout_LatFem->addWidget(pushButton_FLdown, 2,1, 1, 1,Qt::AlignCenter);


    pushButton_FLleft = new QPushButton();
    pushButton_FLleft->setObjectName("pushButton_FLleft");
    sizePolicy1.setHeightForWidth(pushButton_FLleft->sizePolicy().hasHeightForWidth());
    pushButton_FLleft->setSizePolicy(sizePolicy1);


    gridLayout_LatFem->addWidget(pushButton_FLleft, 1, 0, 1, 1);


    label_FL_FlexExtenValue = new QLabel();
    label_FL_FlexExtenValue->setContentsMargins(15,0,15,0);
    label_FL_FlexExtenValue->setObjectName("label_VarValValue");


    m_qhbflExt= new QHBoxLayout;
    m_qhbflExt->addWidget(label_FLExten,2,Qt::AlignRight);
    m_qhbflExt->addWidget(label_FL_FlexExtenValue,2,Qt::AlignLeft);




    m_qvbFlexextbtn  = new QVBoxLayout;

    m_qvbFlexextbtn->addLayout(m_qhbflExt);
    m_qvbFlexextbtn->addWidget(pushButton_FLup,1, Qt::AlignCenter);
    gridLayout_LatFem->addLayout(m_qvbFlexextbtn, 0, 1, 1, 1, Qt::AlignCenter);



    pushButton_FLright = new QPushButton();
    pushButton_FLright->setObjectName("pushButton_FLright");
    sizePolicy1.setHeightForWidth(pushButton_FLright->sizePolicy().hasHeightForWidth());
    pushButton_FLright->setSizePolicy(sizePolicy1);


    gridLayout_LatFem->addWidget(pushButton_FLright, 1, 2, 1, 1);


    horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
    FLButn_gridLayout->addItem(horizontalSpacer_4, 0, 0, 1, 1);

    pushButton_FLrightdown = new QPushButton();
    pushButton_FLrightdown->setObjectName("pushButton_FLrightdown");
    sizePolicy1.setHeightForWidth(pushButton_FLrightdown->sizePolicy().hasHeightForWidth());
    pushButton_FLrightdown->setSizePolicy(sizePolicy1);

    gridLayout_LatFem->addWidget(pushButton_FLrightdown, 0, 2, 1, 1);




    gridLayout3D->addLayout(gridLayout_LatFem, 0, 2);



    gridLayout_DistFem = new QGridLayout();
    gridLayout_DistFem->setObjectName("gridLayout_DistFem");
    TopMiddleDistalFemur3DWidget = new MyQVTKOpenGLNativeWidget();
    TopMiddleDistalFemur3DWidget->setObjectName("TopMiddleDistalFemur3DWidget");
    TopMiddleDistalFemur3DWidget->setMinimumSize(QSize(350, 350));

    gridLayout_DistFem->addWidget(TopMiddleDistalFemur3DWidget, 1,1, 1, 1);


    label_Value21 = new QLabel();
    label_Value21->setContentsMargins(15,0,15,0);
    label_Value21->setObjectName("labelPlanning");


    label_ValueF11 = new QLabel();
    label_ValueF11->setContentsMargins(15,0,15,0);
    label_ValueF11->setObjectName("labelPlanning");

    horizontalSpacer_19 = new QSpacerItem(8, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);
    pushButton_FDdown = new QPushButton();
    pushButton_FDdown->setObjectName("pushButton_FDdown");
    sizePolicy1.setHeightForWidth(pushButton_FDdown->sizePolicy().hasHeightForWidth());
    pushButton_FDdown->setSizePolicy(sizePolicy1);



    QHBoxLayout *m_qhbDFrowlayout = new QHBoxLayout;
    m_qhbDFrowlayout->addWidget(label_ValueF11, 1, Qt::AlignLeft);
    m_qhbDFrowlayout->addWidget(pushButton_FDdown, 4, Qt::AlignCenter);
    m_qhbDFrowlayout->addWidget(label_Value21, 1, Qt::AlignRight);



    gridLayout_DistFem->addLayout(m_qhbDFrowlayout,2,1,1,1);



    FDButn_gridLayout = new QGridLayout();
    FDButn_gridLayout->setObjectName("FDButn_gridLayout");
    pushButton_FDrightdown = new QPushButton();
    pushButton_FDrightdown->setObjectName("pushButton_FDrightdown");
    sizePolicy1.setHeightForWidth(pushButton_FDrightdown->sizePolicy().hasHeightForWidth());
    pushButton_FDrightdown->setSizePolicy(sizePolicy1);

    gridLayout_DistFem->addWidget(pushButton_FDrightdown, 0, 2, 1, 1);


    pushButton_FDleftdown = new QPushButton();
    pushButton_FDleftdown->setObjectName("pushButton_FDleftdown");
    sizePolicy1.setHeightForWidth(pushButton_FDleftdown->sizePolicy().hasHeightForWidth());
    pushButton_FDleftdown->setSizePolicy(sizePolicy1);

    gridLayout_DistFem->addWidget(pushButton_FDleftdown, 0, 0, 1, 1);


    pushButton_FDup = new QPushButton();
    pushButton_FDup->setObjectName("pushButton_FDup");
    sizePolicy1.setHeightForWidth(pushButton_FDup->sizePolicy().hasHeightForWidth());
    pushButton_FDup->setSizePolicy(sizePolicy1);



    pushButton_FDleft = new QPushButton();
    pushButton_FDleft->setObjectName("pushButton_FDleft");
    sizePolicy1.setHeightForWidth(pushButton_FDleft->sizePolicy().hasHeightForWidth());
    pushButton_FDleft->setSizePolicy(sizePolicy1);

    gridLayout_DistFem->addWidget(pushButton_FDleft, 1, 0, 1, 1);



    label_FDIntExt = new QLabel();
    label_FDIntExt->setObjectName("label_VarVal");


    label_FDIntExtValue = new QLabel();
    label_FDIntExtValue->setContentsMargins(15,0,15,0);
    label_FDIntExtValue->setObjectName("label_VarValValue");


    label_FDIntExtPCA = new QLabel();
    label_FDIntExtPCA->setObjectName("label_VarVal");

    label_FDIntExtPCAValue = new QLabel();
    label_FDIntExtPCAValue->setObjectName("label_VarValValue");


    m_qhbFDIElayout = new QHBoxLayout;
    m_qhbFDIElayout->addWidget(label_FDIntExtPCA,1,Qt::AlignLeft);
    m_qhbFDIElayout->addWidget(label_FDIntExtPCAValue,1);
    m_qhbFDIElayout->addWidget(label_FDIntExt,1, Qt::AlignHCenter);
    m_qhbFDIElayout->addWidget(label_FDIntExtValue,1);


    m_qvbFDlayout = new QVBoxLayout;
    //  m_qvbFDlayout->addWidget(pushButton_FDup,1,Qt::AlignCenter);
    m_qvbFDlayout->addLayout(m_qhbFDIElayout,1);

    gridLayout_DistFem->addLayout(m_qvbFDlayout, 0, 1, 1, 1,Qt::AlignCenter);


    pushButton_FDright = new QPushButton();
    pushButton_FDright->setObjectName("pushButton_FDright");
    sizePolicy1.setHeightForWidth(pushButton_FDright->sizePolicy().hasHeightForWidth());
    pushButton_FDright->setSizePolicy(sizePolicy1);


    gridLayout_DistFem->addWidget(pushButton_FDright, 1, 2, 1, 1);




    gridLayout3D->addLayout(gridLayout_DistFem, 0, 1);



    gridLayout_AntTib = new QGridLayout();
    gridLayout_AntTib->setObjectName("gridLayout_AntTib");
    gridLayout_10 = new QGridLayout();
    gridLayout_10->setObjectName("gridLayout_10");



    label_ValueF5 = new QLabel();
    label_ValueF5->setContentsMargins(15,0,0,0);
    label_ValueF5->setObjectName("labelPlanninggrid15");



    gridLayout_15->addWidget(label_ValueF5, 0,1,1,1, Qt::AlignLeft);

    label_6 = new QLabel();
    label_6->setContentsMargins(0,0,15,0);
    label_6->setObjectName("labelML");

    gridLayout_15->addWidget(label_6, 0,3, Qt::AlignRight);


    label_ValueF3 = new QLabel();
    label_ValueF3->setContentsMargins(15,0,15,0);
    label_ValueF3->setObjectName("labelPlanning");


    label_2 = new QLabel();
    label_2->setObjectName("labelML");

    gridLayout_15->addWidget(label_2, 0, 0,1,1);


    label_ValueF6 = new QLabel();
    label_ValueF6->setContentsMargins(15,0,15,0);
    label_ValueF6->setObjectName("labelPlanning");



    label_ValueF2 = new QLabel();
    label_ValueF2->setContentsMargins(0,0,15,0);
    label_ValueF2->setObjectName("labelPlanninggrid15");


    gridLayout_15->addWidget(label_ValueF2, 0, 2, Qt::AlignRight);


    horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);


    gridLayout3D->addLayout(gridLayout_15, 1,0);//


    TABtn_gridLayout = new QGridLayout();
    TABtn_gridLayout->setObjectName("TABtn_gridLayout");
    label_Tib_VarValgusValue = new QLabel();
    label_Tib_VarValgusValue->setContentsMargins(15,0,15,0);
    label_Tib_VarValgusValue->setObjectName("label_VarValValue");


    pushButton_TAright = new QPushButton();
    pushButton_TAright->setObjectName("pushButton_TAright");
    sizePolicy1.setHeightForWidth(pushButton_TAright->sizePolicy().hasHeightForWidth());
    pushButton_TAright->setSizePolicy(sizePolicy1);


    gridLayout_AntTib->addWidget(pushButton_TAright, 1, 2, 1, 1);//


    horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

    TABtn_gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

    horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

    TABtn_gridLayout->addItem(horizontalSpacer_8, 0, 0, 1, 1);

    pushButton_TAdown = new QPushButton();
    pushButton_TAdown->setObjectName("pushButton_TAdown");
    sizePolicy1.setHeightForWidth(pushButton_TAdown->sizePolicy().hasHeightForWidth());
    pushButton_TAdown->setSizePolicy(sizePolicy1);



    pushButton_TArightdown = new QPushButton();
    pushButton_TArightdown->setObjectName("pushButton_TArightdown");
    sizePolicy1.setHeightForWidth(pushButton_TArightdown->sizePolicy().hasHeightForWidth());
    pushButton_TArightdown->setSizePolicy(sizePolicy1);


    gridLayout_AntTib->addWidget(pushButton_TArightdown, 2, 2, 1, 1);//


    pushButton_TAup = new QPushButton();
    pushButton_TAup->setObjectName("pushButton_TAup");
    sizePolicy1.setHeightForWidth(pushButton_TAup->sizePolicy().hasHeightForWidth());
    pushButton_TAup->setSizePolicy(sizePolicy1);




    pushButton_TAleft = new QPushButton();
    pushButton_TAleft->setObjectName("pushButton_TAleft");
    sizePolicy1.setHeightForWidth(pushButton_TAleft->sizePolicy().hasHeightForWidth());
    pushButton_TAleft->setSizePolicy(sizePolicy1);

    gridLayout_AntTib->addWidget(pushButton_TAleft, 1, 0,1,1);//


    pushButton_TAleftdown = new QPushButton();
    pushButton_TAleftdown->setObjectName("pushButton_TAleftdown");
    sizePolicy1.setHeightForWidth(pushButton_TAleftdown->sizePolicy().hasHeightForWidth());
    pushButton_TAleftdown->setSizePolicy(sizePolicy1);


    gridLayout_AntTib->addWidget(pushButton_TAleftdown, 2, 0, 1, 1);//



    QHBoxLayout *m_qhbATrowLayout = new QHBoxLayout;
    m_qhbATrowLayout->addWidget(label_ValueF3,1, Qt::AlignLeft);
    m_qhbATrowLayout->addWidget(pushButton_TAup,2, Qt::AlignCenter);
    m_qhbATrowLayout->addWidget(label_ValueF6,1, Qt::AlignRight);


    gridLayout_AntTib->addLayout(m_qhbATrowLayout,0,1,1,1);


    label_TibVarVal = new QLabel();
    label_TibVarVal->setObjectName("label_VarVal");


    BottomLeftAnteriorTibia3DWidget = new MyQVTKOpenGLNativeWidget();
    BottomLeftAnteriorTibia3DWidget->setObjectName("BottomLeftAnteriorTibia3DWidget");
    BottomLeftAnteriorTibia3DWidget->setMinimumSize(QSize(350, 350));

    gridLayout_AntTib->addWidget(BottomLeftAnteriorTibia3DWidget, 1, 1);//


    m_qvbtiblayout = new QVBoxLayout;
    m_qhbvaruslbltib = new QHBoxLayout;

    m_qhbvaruslbltib->addWidget(label_TibVarVal,2, Qt::AlignRight);
    m_qhbvaruslbltib->addWidget(label_Tib_VarValgusValue,2, Qt::AlignLeft);
    m_qvbtiblayout->addWidget(pushButton_TAdown,1, Qt::AlignCenter);
    m_qvbtiblayout->addLayout(m_qhbvaruslbltib,2);


    gridLayout_AntTib->addLayout(m_qvbtiblayout, 2, 1, 1, 1, Qt::AlignCenter);



    horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName("horizontalLayout");
    pushButton_Tib_reset_2 = new QPushButton();
    pushButton_Tib_reset_2->setObjectName("pushButton_Tib_reset_2");
    sizePolicy1.setHeightForWidth(pushButton_Tib_reset_2->sizePolicy().hasHeightForWidth());
    pushButton_Tib_reset_2->setSizePolicy(sizePolicy1);

    //horizontalLayout->addWidget(pushButton_Tib_reset_2);

    horizontalSpacer_11 = new QSpacerItem(40, 80, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);

    horizontalLayout->addItem(horizontalSpacer_11);

    gridLayout_10->addItem(horizontalSpacer_11,0,0);

    //  gridLayout3D->addLayout(gridLayout_10, 1, 2,1,1,Qt::AlignCenter);
    gridLayout3D->addLayout(gridLayout_AntTib, 2, 0);


    gridLayout_LatTib = new QGridLayout();
    gridLayout_LatTib->setObjectName("gridLayout_LatTib");
    BottomRightLateralTibia3DWidget = new MyQVTKOpenGLNativeWidget();
    BottomRightLateralTibia3DWidget->setObjectName("BottomRightLateralTibia3DWidget");
    BottomRightLateralTibia3DWidget->setMinimumSize(QSize(350, 350));

    gridLayout_LatTib->addWidget(BottomRightLateralTibia3DWidget, 1,1, 1, 1);



    TLBtn_gridLayout = new QGridLayout();
    TLBtn_gridLayout->setObjectName("TLBtn_gridLayout");
    pushButton_TLup = new QPushButton();
    pushButton_TLup->setObjectName("pushButton_TLup");
    sizePolicy1.setHeightForWidth(pushButton_TLup->sizePolicy().hasHeightForWidth());
    pushButton_TLup->setSizePolicy(sizePolicy1);

    gridLayout_LatTib->addWidget(pushButton_TLup, 0,1, 1, 1, Qt::AlignCenter);


    pushButton_TLright = new QPushButton();
    pushButton_TLright->setObjectName("pushButton_TLright");
    sizePolicy1.setHeightForWidth(pushButton_TLright->sizePolicy().hasHeightForWidth());
    pushButton_TLright->setSizePolicy(sizePolicy1);

    gridLayout_LatTib->addWidget(pushButton_TLright, 1,2, 1, 1);

    label_TibPSlopeValue = new QLabel();
    label_TibPSlopeValue->setContentsMargins(15,0,15,0);
    label_TibPSlopeValue->setObjectName("label_VarValValue");
    label_TibPSlopeValue->setAlignment(Qt::AlignCenter);



    pushButton_TLrightdown = new QPushButton();
    pushButton_TLrightdown->setObjectName("pushButton_TLrightdown");
    sizePolicy1.setHeightForWidth(pushButton_TLrightdown->sizePolicy().hasHeightForWidth());
    pushButton_TLrightdown->setSizePolicy(sizePolicy1);

    gridLayout_LatTib->addWidget(pushButton_TLrightdown, 2,2, 1, 1);

    label_TibPslop = new QLabel();
    label_TibPslop->setObjectName("label_VarVal");


    m_qhbtibSlop = new QHBoxLayout;
    m_qhbtibSlop->addWidget(label_TibPslop,2, Qt::AlignRight);
    m_qhbtibSlop->addWidget(label_TibPSlopeValue,2, Qt::AlignLeft);



    horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);



    pushButton_TLleftdown = new QPushButton();
    pushButton_TLleftdown->setObjectName("pushButton_TLleftdown");
    sizePolicy1.setHeightForWidth(pushButton_TLleftdown->sizePolicy().hasHeightForWidth());
    pushButton_TLleftdown->setSizePolicy(sizePolicy1);

    gridLayout_LatTib->addWidget(pushButton_TLleftdown, 2,0 ,1, 1);//


    pushButton_TLdown = new QPushButton();
    pushButton_TLdown->setObjectName("pushButton_TLdown");
    sizePolicy1.setHeightForWidth(pushButton_TLdown->sizePolicy().hasHeightForWidth());
    pushButton_TLdown->setSizePolicy(sizePolicy1);

    //
    m_qvblattiblay = new QVBoxLayout;
    m_qvblattiblay->addWidget(pushButton_TLdown,1,Qt::AlignCenter);
    m_qvblattiblay->addLayout(m_qhbtibSlop);


    gridLayout_LatTib->addLayout(m_qvblattiblay, 2,1 ,1, 1,Qt::AlignCenter);//


    pushButton_TLleft = new QPushButton();
    pushButton_TLleft->setObjectName("pushButton_TLleft");
    sizePolicy1.setHeightForWidth(pushButton_TLleft->sizePolicy().hasHeightForWidth());
    pushButton_TLleft->setSizePolicy(sizePolicy1);

    gridLayout_LatTib->addWidget(pushButton_TLleft, 1,0 ,1, 1);//

    horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);


    gridLayout_18 = new QGridLayout();
    gridLayout_18->setObjectName("gridLayout_18");

    horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);



    gridLayout3D->addLayout(gridLayout_LatTib, 2, 2);//


    gridLayout_DisTib = new QGridLayout();
    gridLayout_DisTib->setObjectName("gridLayout_DisTib");
    BottomMiddleDistalTibia3DWidget = new MyQVTKOpenGLNativeWidget();
    BottomMiddleDistalTibia3DWidget->setObjectName("BottomMiddleDistalTibia3DWidget");
    BottomMiddleDistalTibia3DWidget->setMinimumSize(QSize(350, 350));

    gridLayout_DisTib->addWidget(BottomMiddleDistalTibia3DWidget, 1,1,1,1);//


    label_16 = new QLabel();
    label_16->setObjectName("labelML");



    TDBtn_gridLayout = new QGridLayout();
    TDBtn_gridLayout->setObjectName("TDBtn_gridLayout");
    pushButton_TDleftdown = new QPushButton();
    pushButton_TDleftdown->setObjectName("pushButton_TDleftdown");
    sizePolicy1.setHeightForWidth(pushButton_TDleftdown->sizePolicy().hasHeightForWidth());
    pushButton_TDleftdown->setSizePolicy(sizePolicy1);

    gridLayout_DisTib->addWidget(pushButton_TDleftdown, 2,0,1,1);


    pushButton_TDup = new QPushButton();
    pushButton_TDup->setObjectName("pushButton_TDup");
    sizePolicy1.setHeightForWidth(pushButton_TDup->sizePolicy().hasHeightForWidth());
    pushButton_TDup->setSizePolicy(sizePolicy1);


    pushButton_TDdown = new QPushButton();
    pushButton_TDdown->setObjectName("pushButton_TDdown");
    sizePolicy1.setHeightForWidth(pushButton_TDdown->sizePolicy().hasHeightForWidth());
    pushButton_TDdown->setSizePolicy(sizePolicy1);



    m_qhblbltibmid = new QHBoxLayout;//


    label_tibExtInt = new QLabel();
    label_tibExtInt->setObjectName("label_VarVal");//

    m_qhblbltibmid->addWidget(label_tibExtInt,2,Qt::AlignRight);


    label_Tib_InterExterValue = new QLabel();
    label_Tib_InterExterValue->setContentsMargins(15,0,15,0);
    label_Tib_InterExterValue->setObjectName("label_VarValValue");
    label_Tib_InterExterValue->setAlignment(Qt::AlignCenter);

    m_qhblbltibmid->addWidget(label_Tib_InterExterValue,2,Qt::AlignLeft);

    horizontalSpacer_6 = new QSpacerItem(20, 50, QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Minimum);

    m_qvbtibmid = new QVBoxLayout;

    m_qvbtibmid->addWidget(pushButton_TDdown,1, Qt::AlignCenter);
    //  m_qvbtibmid->addItem(horizontalSpacer_6);
    m_qvbtibmid->addLayout(m_qhblbltibmid);
    gridLayout_DisTib->addLayout(m_qvbtibmid,2,1,1,1, Qt::AlignCenter);






    pushButton_TDleft = new QPushButton();
    pushButton_TDleft->setObjectName("pushButton_TDleft");
    sizePolicy1.setHeightForWidth(pushButton_TDleft->sizePolicy().hasHeightForWidth());
    pushButton_TDleft->setSizePolicy(sizePolicy1);


    gridLayout_DisTib->addWidget(pushButton_TDleft,1,0,1,1);//


    pushButton_TDrightdown = new QPushButton();
    pushButton_TDrightdown->setObjectName("pushButton_TDrightdown");
    sizePolicy1.setHeightForWidth(pushButton_TDrightdown->sizePolicy().hasHeightForWidth());
    pushButton_TDrightdown->setSizePolicy(sizePolicy1);

    gridLayout_DisTib->addWidget(pushButton_TDrightdown,2,2,1,1);//






    pushButton_TDright = new QPushButton();
    pushButton_TDright->setObjectName("pushButton_TDright");
    sizePolicy1.setHeightForWidth(pushButton_TDright->sizePolicy().hasHeightForWidth());
    pushButton_TDright->setSizePolicy(sizePolicy1);

    gridLayout_DisTib->addWidget(pushButton_TDright,1,2,1,1, Qt::AlignCenter);//


    horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);


    gridLayout_16 = new QGridLayout();
    gridLayout_16->setColumnStretch(1, 1);
    gridLayout_16->setColumnStretch(2, 1);
    gridLayout_16->setObjectName("gridLayout_16");



    label_Value13 = new QLabel();
    label_Value13->setContentsMargins(15,0,15,0);
    label_Value13->setObjectName("labelPlanning");

    label_Value23 = new QLabel();
    label_Value23->setContentsMargins(15,0,15,0);
    label_Value23->setObjectName("labelPlanning");


    //
    QHBoxLayout *m_qhbDTrowLayout = new QHBoxLayout;
    m_qhbDTrowLayout->addWidget(label_Value13,1, Qt::AlignLeft);
    m_qhbDTrowLayout->addWidget(pushButton_TDup,2, Qt::AlignCenter);
    m_qhbDTrowLayout->addWidget(label_Value23,1, Qt::AlignRight);
    gridLayout_DisTib ->addLayout(m_qhbDTrowLayout, 0,1, 1, 1);


    label_Value12 = new QLabel();
    label_Value12->setContentsMargins(15,0,0,0);
    label_Value12->setObjectName("label_Value12");

    gridLayout_16->addWidget(label_Value12, 0,1,1,1, Qt::AlignLeft);//


    label_Value22 = new QLabel();
    label_Value22->setContentsMargins(0,0,30,0);
    label_Value22->setObjectName("label_Value22");

    gridLayout_16->addWidget(label_Value22, 0, 2, Qt::AlignRight);//


    horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);


    label_15 = new QLabel();
    label_15->setObjectName("labelML");

    gridLayout_16->addWidget(label_15, 0, 0,2,1);//


    horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);


    horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);


    gridLayout_16->addWidget(label_16, 0, 3,  Qt::AlignRight);//


    gridLayout3D->addLayout(gridLayout_16, 1,1);


    horizontalLayout_6 = new QHBoxLayout();
    horizontalLayout_6->setObjectName("horizontalLayout_6");
    horizontalSpacer_20 = new QSpacerItem(40, 50, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);
    horizontalLayout_6->addItem(horizontalSpacer_20);

    gridLayout3D->addLayout(gridLayout_DisTib, 2, 1);


    verticalScrollBar_1 = new QScrollBar();
    verticalScrollBar_1->setObjectName("verticalScrollBar_1");
    verticalScrollBar_1->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                         "background-color: rgb(58, 58, 58);"));
    verticalScrollBar_1->setOrientation(Qt::Vertical);


    verticalScrollBar_2 = new QScrollBar();
    verticalScrollBar_2->setObjectName("verticalScrollBar_2");
    verticalScrollBar_2->setOrientation(Qt::Vertical);
    verticalScrollBar_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                         "background-color: rgb(58, 58, 58);"));

    verticalScrollBar_3 = new QScrollBar();
    verticalScrollBar_3->setObjectName("verticalScrollBar_3");
    verticalScrollBar_3->setOrientation(Qt::Vertical);
    verticalScrollBar_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                         "background-color: rgb(58, 58, 58);"));



    pushButton_FAleftdown->setEnabled(false);
    pushButton_FAup->setEnabled(false);
    pushButton_FArightdown->setEnabled(false);
    pushButton_FAleft->setEnabled(false);
    pushButton_FAdown->setEnabled(false);
    pushButton_FAright->setEnabled(false);

    pushButton_FDleftdown->setEnabled(false);
    pushButton_FDup->setEnabled(false);
    pushButton_FDrightdown->setEnabled(false);
    pushButton_FDleft->setEnabled(false);
    pushButton_FDdown->setEnabled(false);
    pushButton_FDright->setEnabled(false);

    pushButton_FLleftdown->setEnabled(false);
    pushButton_FLup->setEnabled(false);
    pushButton_FLrightdown->setEnabled(false);
    pushButton_FLleft->setEnabled(false);
    pushButton_FLdown->setEnabled(false);
    pushButton_FLright->setEnabled(false);


    pushButton_TAleftdown->setEnabled(false);
    pushButton_TAup->setEnabled(false);
    pushButton_TArightdown->setEnabled(false);
    pushButton_TAleft->setEnabled(false);
    pushButton_TAdown->setEnabled(false);
    pushButton_TAright->setEnabled(false);

    pushButton_TDleftdown->setEnabled(false);
    pushButton_TDup->setEnabled(false);
    pushButton_TDrightdown->setEnabled(false);
    pushButton_TDleft->setEnabled(false);
    pushButton_TDdown->setEnabled(false);
    pushButton_TDright->setEnabled(false);

    pushButton_TLleftdown->setEnabled(false);
    pushButton_TLup->setEnabled(false);
    pushButton_TLrightdown->setEnabled(false);
    pushButton_TLleft->setEnabled(false);
    pushButton_TLdown->setEnabled(false);
    pushButton_TLright->setEnabled(false);


    //------------------------------------


    pushButton_FAright->setText(QString(""));
    //label_Fem_VarValgValue->setText( "0.0\302\260");
    pushButton_FArightdown->setText(QString(""));
    label_FemVarVal->setText( "Varus");//
    pushButton_FAleftdown->setText(QString(""));
    pushButton_FAdown->setText(QString(""));
    pushButton_Fem_reset->setText("R");
    pushButton_FAleft->setText(QString(""));
    pushButton_FAup->setText(QString(""));
    pushButton_FLup->setText(QString(""));
    pushButton_FLleftdown->setText(QString(""));
    label_FLExten->setText("Flexion");//
    pushButton_FLdown->setText(QString(""));
    pushButton_FLleft->setText(QString(""));
    //label_FL_FlexExtenValue->setText( "3.0\302\260");
    pushButton_FLright->setText(QString(""));
    pushButton_FLrightdown->setText(QString(""));
    label_ValueF5->setText( "17.0");
    label_6->setText("L");
    label_ValueF3->setText( "9.0");
    label_ValueF1->setText( "9.0");
    label_2->setText( "M");
    label_ValueF4->setText( "9.0");
    label_ValueF6->setText( "9.0");
    label_ValueF2->setText( "17.0");
    //label_Tib_VarValgusValue->setText( "0.0\302\260");
    pushButton_TAright->setText(QString(""));
    pushButton_TAdown->setText(QString(""));
    pushButton_TArightdown->setText(QString(""));
    pushButton_TAup->setText(QString(""));
    pushButton_TAleft->setText(QString(""));
    pushButton_TAleftdown->setText(QString(""));
    label_TibVarVal->setText( "Varus");//
    pushButton_Tib_reset_2->setText( "R");
    pushButton_TLup->setText(QString(""));
    pushButton_TLright->setText(QString(""));
    //label_TibPSlopeValue->setText( "0.0\302\260");
    pushButton_TLrightdown->setText(QString(""));
    label_TibPslop->setText( "P.Slope");
    pushButton_TLleftdown->setText(QString(""));
    pushButton_TLdown->setText(QString(""));
    pushButton_TLleft->setText(QString(""));
    label_16->setText( "L");
    pushButton_TDleftdown->setText(QString(""));
    pushButton_TDup->setText(QString(""));
    label_tibExtInt->setText( "Int.");//
    //label_Tib_InterExterValue->setText( "0.0\302\260");
    pushButton_TDleft->setText(QString(""));
    pushButton_TDrightdown->setText(QString(""));
    pushButton_TDdown->setText(QString(""));
    pushButton_TDright->setText(QString(""));
    label_Value21->setText( "10.0");
    label_Value13->setText( "9.0");
    label_Value23->setText( "9.0");
    label_Value12->setText( "17.0");
    label_Value22->setText( "17.0");
    label_15->setText( "M");
    label_ValueF11->setText( "7.5");
    pushButton_FDrightdown->setText(QString(""));
    pushButton_FDleftdown->setText(QString(""));
    pushButton_FDup->setText(QString(""));
    pushButton_FDdown->setText(QString(""));
    pushButton_FDleft->setText(QString(""));
    label_FDIntExt->setText( "TEA");//
    //label_FDIntExtValue->setText( "3.0\302\260");
    pushButton_FDright->setText(QString(""));
    label_FDIntExtPCAValue->setText( "3.0\302\260");
    label_FDIntExtPCA->setText("Ext PCA");//

    //---------------------------


    this->setLayout(gridLayout3D);

    this->show();


    m_ObjPrimaryResectionCut = new PrimaryResectionCut;
    m_ObjAxisDisplayView = new AxisDisplayView;
    m_ObjImplantLoad = new ImplantLoad;
    m_ObjImplantTransformations = new ImplantTransformations;

    //----signals and slot connections----
    connect(m_ObjPrimaryResectionCut,SIGNAL(SignalCutdata_tibia(vtkPolyData*,bool)),this, SLOT(UpdateTibiaData(vtkPolyData*,bool)));
    connect(m_ObjPrimaryResectionCut,SIGNAL(SignalCutdata_femur(vtkPolyData*,bool)),this, SLOT(UpdateFemurData(vtkPolyData*,bool)));
    connect(m_ObjAxisDisplayView,SIGNAL(SignalFemoralMechanicalAxis(vtkPolyData*,vtkPolyData*,vtkPolyData*,vtkPolyData*)),this, SLOT(UpdateAxisDisplay_Femur(vtkPolyData*,vtkPolyData*,vtkPolyData*,vtkPolyData*)));
    connect(m_ObjAxisDisplayView,SIGNAL(SignalTibialMechanicalAxis(vtkPolyData*,vtkPolyData*)),this, SLOT(UpdateAxisDisplay_Tibia(vtkPolyData*,vtkPolyData*)));

    //Anterior femoral
    connect(pushButton_FAleftdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FAup,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FArightdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FAleft,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FAdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FAright,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    //Distal Femoral
    connect(pushButton_FDleftdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FDup,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FDrightdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FDleft,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FDdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FDright,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    //Lateral Femoral
    connect(pushButton_FLleftdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FLup,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FLrightdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FLleft,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FLdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));
    connect(pushButton_FLright,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantFemur(bool)));



    //Anterior Tibial
    connect(pushButton_TAleftdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TAup,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TArightdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TAleft,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TAdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TAright,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    //Distal  Tibial
    connect(pushButton_TDleftdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TDup,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TDrightdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TDleft,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TDdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TDright,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    //Lateral Tibial
    connect(pushButton_TLleftdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TLup,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TLrightdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TLleft,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TLdown,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));
    connect(pushButton_TLright,SIGNAL(clicked(bool)),this,SLOT(TranslationsofImplantTibia(bool)));



    //-------------for changing button icon on press----------parvathy


   //    //Anterior femoral
       connect(pushButton_FAleftdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FAup,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FArightdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FAleft,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FAdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FAright,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       //Distal Femoral
       connect(pushButton_FDleftdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FDup,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FDrightdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FDleft,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FDdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FDright,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       //Lateral Femoral
       connect(pushButton_FLleftdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FLup,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FLrightdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FLleft,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FLdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_FLright,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);



       //Anterior Tibial
       connect(pushButton_TAleftdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TAup,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TArightdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TAleft,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TAdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TAright,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       //Distal  Tibial
       connect(pushButton_TDleftdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TDup,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TDrightdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TDleft,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TDdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TDright,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       //Lateral Tibial
       connect(pushButton_TLleftdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TLup,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TLrightdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TLleft,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TLdown,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);
       connect(pushButton_TLright,&QPushButton::pressed,this,&TKAThreeDView::TranslationsiconChange);




       //-------------for default button icon on release----------


   //    //Anterior femoral
       connect(pushButton_FAleftdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FAup,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FArightdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FAleft,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FAdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FAright,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       //Distal Femoral
       connect(pushButton_FDleftdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FDup,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FDrightdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FDleft,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FDdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FDright,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       //Lateral Femoral
       connect(pushButton_FLleftdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FLup,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FLrightdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FLleft,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FLdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_FLright,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);



       //Anterior Tibial
       connect(pushButton_TAleftdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TAup,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TArightdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TAleft,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TAdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TAright,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       //Distal  Tibial
       connect(pushButton_TDleftdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TDup,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TDrightdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TDleft,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TDdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TDright,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       //Lateral Tibial
       connect(pushButton_TLleftdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TLup,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TLrightdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TLleft,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TLdown,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);
       connect(pushButton_TLright,&QPushButton::released,this,&TKAThreeDView::Translationsiconrelease);





    //-------------For showing the buttons only when the corresponding view is hovered----------

    pushButton_FArightdown->setHidden(true);
    pushButton_FArightdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FArightdown->setIcon(QIcon(":/res/icons/right_rotate.png"));
    pushButton_FArightdown->setFixedSize(20,20);
    pushButton_FArightdown->setIconSize(QSize(30,30));
    pushButton_FAup->setHidden(true);
    pushButton_FAup->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FAup->setIcon(QIcon(":/res/icons/up_arrow.png"));
    pushButton_FAup->setFixedSize(20,20);
    pushButton_FAup->setIconSize(QSize(30,30));
    pushButton_FAleftdown->setHidden(true);
    pushButton_FAleftdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FAleftdown->setIcon(QIcon(":/res/icons/left_rotate.png"));
    pushButton_FAleftdown->setFixedSize(20,20);
    pushButton_FAleftdown->setIconSize(QSize(30,30));
    pushButton_FAleft->setHidden(true);
    pushButton_FAleft->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FAleft->setIcon(QIcon(":/res/icons/left_arrow.png"));
    pushButton_FAleft->setFixedSize(20,20);
    pushButton_FAleft->setIconSize(QSize(30,30));
    pushButton_FAdown->setHidden(true);
    pushButton_FAdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FAdown->setIcon(QIcon(":/res/icons/down_arrow.png"));
    pushButton_FAdown->setFixedSize(20,20);
    pushButton_FAdown->setIconSize(QSize(30,30));
    pushButton_FAright->setHidden(true);
    pushButton_FAright->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FAright->setIcon(QIcon(":/res/icons/right_arrow.png"));
    pushButton_FAright->setFixedSize(20,20);
    pushButton_FAright->setIconSize(QSize(30,30));


    pushButton_FDrightdown->setIcon(QIcon(":/res/icons/right_rotate.png"));
    pushButton_FDup->setIcon(QIcon(":/res/icons/up_arrow.png"));
    pushButton_FDleftdown->setIcon(QIcon(":/res/icons/left_rotate.png"));
    pushButton_FDleft->setIcon(QIcon(":/res/icons/left_arrow.png"));
    pushButton_FDdown->setIcon(QIcon(":/res/icons/down_arrow.png"));
    pushButton_FDright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    pushButton_FDleftdown->setHidden(true);
    pushButton_FDleftdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FDleftdown->setFixedSize(20,20);
    pushButton_FDleftdown->setIconSize(QSize(30,30));
    pushButton_FDup->setHidden(true);
    pushButton_FDup->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FDup->setFixedSize(20,20);
    pushButton_FDup->setIconSize(QSize(30,30));
    pushButton_FDrightdown->setHidden(true);
    pushButton_FDrightdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FDrightdown->setFixedSize(20,20);
    pushButton_FDrightdown->setIconSize(QSize(30,30));
    pushButton_FDleft->setHidden(true);
    pushButton_FDleft->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FDleft->setFixedSize(20,20);
    pushButton_FDleft->setIconSize(QSize(30,30));
    pushButton_FDdown->setHidden(true);
    pushButton_FDdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FDdown->setFixedSize(20,20);
    pushButton_FDdown->setIconSize(QSize(30,30));
    pushButton_FDright->setHidden(true);
    pushButton_FDright->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FDright->setFixedSize(20,20);
    pushButton_FDright->setIconSize(QSize(30,30));



    pushButton_FLrightdown->setIcon(QIcon(":/res/icons/right_rotate.png"));
    pushButton_FLup->setIcon(QIcon(":/res/icons/up_arrow.png"));
    pushButton_FLleftdown->setIcon(QIcon(":/res/icons/left_rotate.png"));
    pushButton_FLleft->setIcon(QIcon(":/res/icons/left_arrow.png"));
    pushButton_FLdown->setIcon(QIcon(":/res/icons/down_arrow.png"));
    pushButton_FLright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    pushButton_FLleftdown->setHidden(true);
    pushButton_FLleftdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FLleftdown->setFixedSize(20,20);
    pushButton_FLleftdown->setIconSize(QSize(30,30));

    pushButton_FLup->setHidden(true);
    pushButton_FLup->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FLup->setFixedSize(20,20);
    pushButton_FLup->setIconSize(QSize(30,30));

    pushButton_FLrightdown->setHidden(true);
    pushButton_FLrightdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FLrightdown->setFixedSize(20,20);
    pushButton_FLrightdown->setIconSize(QSize(30,30));
    pushButton_FLleft->setHidden(true);
    pushButton_FLleft->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FLleft->setFixedSize(20,20);
    pushButton_FLleft->setIconSize(QSize(30,30));
    pushButton_FLdown->setHidden(true);
    pushButton_FLdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FLdown->setFixedSize(20,20);
    pushButton_FLdown->setIconSize(QSize(30,30));

    pushButton_FLright->setHidden(true);
    pushButton_FLright->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_FLright->setFixedSize(20,20);
    pushButton_FLright->setIconSize(QSize(30,30));

    //    Tibia
    pushButton_TArightdown->setIcon(QIcon(":/res/icons/right_rotate_tib.png"));
    pushButton_TAup->setIcon(QIcon(":/res/icons/up_arrow.png"));
    pushButton_TAleftdown->setIcon(QIcon(":/res/icons/left_rotate_tib.png"));
    pushButton_TAleft->setIcon(QIcon(":/res/icons/left_arrow.png"));
    pushButton_TAdown->setIcon(QIcon(":/res/icons/down_arrow.png"));
    pushButton_TAright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    pushButton_TAleftdown->setHidden(true);
    pushButton_TAleftdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TAleftdown->setFixedSize(20,20);
    pushButton_TAleftdown->setIconSize(QSize(30,30));
    pushButton_TAup->setHidden(true);
    pushButton_TAup->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TAup->setFixedSize(20,20);
    pushButton_TAup->setIconSize(QSize(30,30));
    pushButton_TArightdown->setHidden(true);
    pushButton_TArightdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TArightdown->setFixedSize(20,20);
    pushButton_TArightdown->setIconSize(QSize(30,30));
    pushButton_TAleft->setHidden(true);
    pushButton_TAleft->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TAleft->setFixedSize(20,20);
    pushButton_TAleft->setIconSize(QSize(30,30));
    pushButton_TAdown->setHidden(true);
    pushButton_TAdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TAdown->setFixedSize(20,20);
    pushButton_TAdown->setIconSize(QSize(30,30));

    pushButton_TAright->setHidden(true);
    pushButton_TAright->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TAright->setFixedSize(20,20);
    pushButton_TAright->setIconSize(QSize(30,30));


    pushButton_TDrightdown->setIcon(QIcon(":/res/icons/right_rotate_tib.png"));
    pushButton_TDup->setIcon(QIcon(":/res/icons/up_arrow.png"));
    pushButton_TDleftdown->setIcon(QIcon(":/res/icons/left_rotate_tib.png"));
    pushButton_TDleft->setIcon(QIcon(":/res/icons/left_arrow.png"));
    pushButton_TDdown->setIcon(QIcon(":/res/icons/down_arrow.png"));
    pushButton_TDright->setIcon(QIcon(":/res/icons/right_arrow.png"));


    pushButton_TDleftdown->setHidden(true);
    pushButton_TDleftdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TDleftdown->setFixedSize(20,20);
    pushButton_TDleftdown->setIconSize(QSize(30,30));
    pushButton_TDup->setHidden(true);
    pushButton_TDup->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TDup->setFixedSize(20,20);
    pushButton_TDup->setIconSize(QSize(30,30));
    pushButton_TDrightdown->setHidden(true);
    pushButton_TDrightdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TDrightdown->setFixedSize(20,20);
    pushButton_TDrightdown->setIconSize(QSize(30,30));
    pushButton_TDleft->setHidden(true);
    pushButton_TDleft->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TDleft->setFixedSize(20,20);
    pushButton_TDleft->setIconSize(QSize(30,30));
    pushButton_TDdown->setHidden(true);
    pushButton_TDdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TDdown->setFixedSize(20,20);
    pushButton_TDdown->setIconSize(QSize(30,30));
    pushButton_TDright->setHidden(true);
    pushButton_TDright->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TDright->setFixedSize(20,20);
    pushButton_TDright->setIconSize(QSize(30,30));


    pushButton_TLrightdown->setIcon(QIcon(":/res/icons/right_rotate_tib.png"));
    pushButton_TLup->setIcon(QIcon(":/res/icons/up_arrow.png"));
    pushButton_TLleftdown->setIcon(QIcon(":/res/icons/left_rotate_tib.png"));
    pushButton_TLleft->setIcon(QIcon(":/res/icons/left_arrow.png"));
    pushButton_TLdown->setIcon(QIcon(":/res/icons/down_arrow.png"));
    pushButton_TLright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    pushButton_TLleftdown->setHidden(true);
    pushButton_TLleftdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TLleftdown->setFixedSize(20,20);
    pushButton_TLleftdown->setIconSize(QSize(30,30));
    pushButton_TLup->setHidden(true);
    pushButton_TLup->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TLup->setFixedSize(20,20);
    pushButton_TLup->setIconSize(QSize(30,30));
    pushButton_TLrightdown->setHidden(true);
    pushButton_TLrightdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TLrightdown->setFixedSize(20,20);
    pushButton_TLrightdown->setIconSize(QSize(30,30));
    pushButton_TLleft->setHidden(true);
    pushButton_TLleft->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TLleft->setFixedSize(20,20);
    pushButton_TLleft->setIconSize(QSize(30,30));
    pushButton_TLdown->setHidden(true);
    pushButton_TLdown->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TLdown->setFixedSize(20,20);
    pushButton_TLdown->setIconSize(QSize(30,30));
    pushButton_TLright->setHidden(true);
    pushButton_TLright->setStyleSheet(m_stylesheetforViewButtons);
    pushButton_TLright->setFixedSize(20,20);
    pushButton_TLright->setIconSize(QSize(30,30));


    // Connect hover and click signals to buttons
    //Anterior femur buttons
    connect(TopLeftAnteriorFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorFemButtonsVisibilityTrue);
    connect(TopMiddleDistalFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorFemButtonsVisibilityFalse);
    connect(TopRightLateralFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorFemButtonsVisibilityFalse);
    connect(BottomLeftAnteriorTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorFemButtonsVisibilityFalse);
    connect(BottomMiddleDistalTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorFemButtonsVisibilityFalse);
    connect(BottomRightLateralTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorFemButtonsVisibilityFalse);

    //Distal femur buttons
    connect(TopMiddleDistalFemur3DWidget , &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalFemButtonsVisibilityTrue);
    connect(TopLeftAnteriorFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalFemButtonsVisibilityFalse);
    connect(TopRightLateralFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalFemButtonsVisibilityFalse);
    connect(BottomLeftAnteriorTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalFemButtonsVisibilityFalse);
    connect(BottomMiddleDistalTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalFemButtonsVisibilityFalse);
    connect(BottomRightLateralTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalFemButtonsVisibilityFalse);

    //Lateral femur buttons
    connect(TopRightLateralFemur3DWidget  , &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralFemButtonsVisibilityTrue);
    connect(TopLeftAnteriorFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralFemButtonsVisibilityFalse);
    connect(TopMiddleDistalFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralFemButtonsVisibilityFalse);
    connect(BottomLeftAnteriorTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralFemButtonsVisibilityFalse);
    connect(BottomMiddleDistalTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralFemButtonsVisibilityFalse);
    connect(BottomRightLateralTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralFemButtonsVisibilityFalse);


    //anterior tibia buttons
    connect(BottomLeftAnteriorTibia3DWidget  , &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorTibButtonsVisibilityTrue);
    connect(TopLeftAnteriorFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorTibButtonsVisibilityFalse);
    connect(TopMiddleDistalFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorTibButtonsVisibilityFalse);
    connect(TopRightLateralFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorTibButtonsVisibilityFalse);
    connect(BottomMiddleDistalTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorTibButtonsVisibilityFalse);
    connect(BottomRightLateralTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForAnteriorTibButtonsVisibilityFalse);

    //distal tibia buttons
    connect( BottomMiddleDistalTibia3DWidget   , &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalTibButtonsVisibilityTrue);
    connect(TopLeftAnteriorFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalTibButtonsVisibilityFalse);
    connect(TopMiddleDistalFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalTibButtonsVisibilityFalse);
    connect(TopRightLateralFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalTibButtonsVisibilityFalse);
    connect(BottomLeftAnteriorTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalTibButtonsVisibilityFalse);
    connect(BottomRightLateralTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForDistalTibButtonsVisibilityFalse);

    //lateral tibia buttons
    connect(BottomRightLateralTibia3DWidget   , &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralTibButtonsVisibilityTrue);
    connect(TopLeftAnteriorFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralTibButtonsVisibilityFalse);
    connect(TopMiddleDistalFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralTibButtonsVisibilityFalse);
    connect(TopRightLateralFemur3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralTibButtonsVisibilityFalse);
    connect(BottomMiddleDistalTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralTibButtonsVisibilityFalse);
    connect(BottomLeftAnteriorTibia3DWidget, &MyQVTKOpenGLNativeWidget::hovered, this, &TKAThreeDView::SlotForLateralTibButtonsVisibilityFalse);

    //-------------------------------------------------------------------------------------------------------------

    //---Setting the properties of bone(appeareance)-----
    BoneProperty->SetColor(colors_tka->GetColor4d("snow").GetData()/*0.890, 0.855, 0.788*/ );
    BoneProperty->SetSpecular(0.3);// Higher specular for shininess (0 to 1 range)
    BoneProperty->SetSpecularPower(40);// Higher value for a smaller, sharper highlight
    BoneProperty->SetSpecularColor(.8,.8,.7);

    femur_cutActor_Anterior->SetProperty(BoneProperty);
    femur_cutActor_Distal->SetProperty(BoneProperty);
    femur_cutActor_Lateral->SetProperty(BoneProperty);
    tibia_cutActor_Anterior->SetProperty(BoneProperty);
    tibia_cutActor_Distal->SetProperty(BoneProperty);
    tibia_cutActor_Lateral->SetProperty(BoneProperty);
    //---------------------------------------------------

    for( int i=0;i<6;i++)
    {
        renderWindow_tka[i]=  vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
        renderer_tka[i]=vtkSmartPointer<vtkRenderer>::New();
        interactor_tka[i] =vtkSmartPointer<vtkRenderWindowInteractor>::New();
        style_1[i] = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        customstyle[i] =  vtkSmartPointer<TKACustomInteractorStyle>::New();

        actor_3dtka[i] =vtkSmartPointer<vtkActor>::New();
        actor_3dtka[i]->SetProperty(BoneProperty);//added on 19-9-24
        mapper_3dtka[i] =vtkSmartPointer<vtkPolyDataMapper>::New();
        //        surface[i] = vtkSmartPointer<vtkMarchingCubes>::New();
        //        m_tkaReader[i] =  vtkSmartPointer<vtkDICOMImageReader>::New();
        //        m_extractvoi[i] =  vtkSmartPointer<vtkExtractVOI>::New();
    }


    //===only for testing======


    IntializePlanningWindows();
}
void TKAThreeDView:: IntializePlanningWindows()
{
    //Read the data, camera angle from the configuration file and call the femur and tibia functions from tkathreedviewer
    QSettings settings(config_filename, QSettings::IniFormat);

    // Retrieve all group names
    QStringList groups = settings.childGroups();

    QStringList keyOrder = {"id", "view", "kneepart", "roll", "elevation","azimuth"};
    int firstcheck = 0;
    // Iterate through all groups (tags)
    //QStringList groups = settings.childGroups();
    foreach (const QString &group, groups) {
        settings.beginGroup(group);

        // Create a QString to hold all values in the specified order
        QStringList values;
        foreach (const QString &key, keyOrder) {
            if (settings.contains(key)) {
                QString value = settings.value(key).toString();
                values << value;
            }
        }

        // Join the values with commas
        QStringList tagValues = values;

        // Output the values (you can store or process it as needed)
        qDebug() << tagValues;
        InitializeViewsFemur(tagValues[0],tagValues[1],tagValues[2],tagValues[3],tagValues[4],tagValues[5]);

        settings.endGroup();
    }

}

TKAThreeDView::~TKAThreeDView()
{
    delete  TopRightLateralFemur3DWidget;
    delete  BottomLeftAnteriorTibia3DWidget;
    delete  BottomMiddleDistalTibia3DWidget;
    delete  TopMiddleDistalFemur3DWidget;
    delete  BottomRightLateralTibia3DWidget;
    delete  TopLeftAnteriorFemur3DWidget;
}
void TKAThreeDView::InitializeViewsFemur(QString id, QString view, QString kneepart, QString roll,QString elevation,QString azimuth)
{

    if(firsttimeFlag == false)
    {
        //************Femur*********************
        //-------old code----------------------
        //        m_tkaReaderFemur->SetDirectoryName(m_direc_femur.toStdString().c_str());
        //        m_tkaReaderFemur->Update();
        //        //femur_pixelspacing = m_tkaReaderFemur->GetPixelSpacing();//added 3-9-24

        //        m_extractvoi_Femur->SetInputConnection(m_tkaReaderFemur->GetOutputPort());
        //        //m_extractvoi_Femur->SetVOI(0,497,150,350,0,62);//old
        //        m_extractvoi_Femur->SetVOI(0,497,250,m_tkaReaderFemur->GetOutput()->GetDimensions()[1]-1,0,m_tkaReaderFemur->GetOutput()->GetDimensions()[2]-1);
        //        m_extractvoi_Femur->Update();


        //        surface_Femur->SetInputConnection(m_tkaReaderFemur->GetOutputPort());
        //        //surface_Femur->ComputeNormalsOn();//commented
        //        surface_Femur->SetValue(0, 300);//300
        //        surface_Femur->Update();
        //------------------------------------------

        //-------Added on 25-10-2024---------
        //**************Femur**************************
//        m_tkaReaderFemur_SAKS->SetDirectoryName(m_direc_femur.toStdString().c_str());
//        m_tkaReaderFemur_SAKS->Update();
//        qDebug()<<" planning fem path:"<<m_direc_femur;

//        // Step 2: Apply Marching Cubes for surface extraction
//        vtkSmartPointer<vtkMarchingCubes> marchingCubes_femur = vtkSmartPointer<vtkMarchingCubes>::New();
//        marchingCubes_femur->SetInputData(m_tkaReaderFemur_SAKS->GetOutput());
//        marchingCubes_femur->SetValue(0, -750);
//        marchingCubes_femur->ComputeNormalsOn();
//        marchingCubes_femur->ComputeScalarsOn();
//        marchingCubes_femur->Update();

//        QDir dir(QDir::currentPath());
//        // Get the parent path (up to the last directory)
//        QString parentPath = dir.path();
//        parentPath = dir.cdUp() ? dir.path() : QString();

//        QString femurstlfilepath =parentPath+"/TKA_Kinematics_Ver1.0/code/femur_annotation.stl";
//        // Step 3: Write the polydata as STL
//        vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
//        stlWriter->SetFileName(femurstlfilepath.toStdString().c_str());
//        stlWriter->SetFileTypeToBinary();
//        stlWriter->SetInputConnection(marchingCubes_femur->GetOutputPort());
//        stlWriter->Write();

//        qDebug()<<" femur stl path-------- =" <<femurstlfilepath;
//        //**************Tibia**************************
//        m_tkaReaderTibia_SAKS->SetDirectoryName(m_direc_tibia.toStdString().c_str());
//        m_tkaReaderTibia_SAKS->Update();

//        qDebug()<<" m_direc_tibia-------- =" <<m_direc_tibia;
//        // Step 2: Apply Marching Cubes for surface extraction
//        vtkSmartPointer<vtkMarchingCubes> marchingCubes_tibia= vtkSmartPointer<vtkMarchingCubes>::New();
//        marchingCubes_tibia->SetInputData(m_tkaReaderTibia_SAKS->GetOutput());
//        marchingCubes_tibia->SetValue(0, -750);
//        marchingCubes_tibia->ComputeNormalsOn();
//        marchingCubes_tibia->ComputeScalarsOn();
//        marchingCubes_tibia->Update();


//        QString tibiastlfilepath = parentPath+"/TKA_Kinematics_Ver1.0/code/tibia_annotation.stl";
//        // Step 3: Write the polydata as STL
//        //vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
//        stlWriter->SetFileName(tibiastlfilepath.toStdString().c_str());
//        stlWriter->SetFileTypeToBinary();
//        stlWriter->SetInputConnection(marchingCubes_tibia->GetOutputPort());
//        stlWriter->Write();
        //-----------------------------------

        m_tkaReaderFemur->SetFileName(m_direc_femur.toStdString().c_str());
        //m_tkaReaderFemur->SetFileName(m_direc_femur.toStdString().c_str()); for patient data
        m_tkaReaderFemur->Update();

        // Create the smooth filter
        smoothFilterFemur->SetInputConnection(m_tkaReaderFemur->GetOutputPort());
        smoothFilterFemur->SetNumberOfIterations(50);   // Increase for more smoothing
        smoothFilterFemur->SetRelaxationFactor(0.1);    // Controls how strong the smoothing is (0-1)
        smoothFilterFemur->FeatureEdgeSmoothingOff();   // To avoid smoothing sharp edges
        smoothFilterFemur->BoundarySmoothingOn();       // Smooth boundaries
        smoothFilterFemur->Update();  // Apply the filter

        //surface_Femur->SetInputData(m_tkaReaderFemur->GetOutput());
        //surface_Femur->Update();


        //****************Tibia****************
        //---old----------------
        //        m_tkaReaderTibia->SetDirectoryName(m_direc_tibia.toStdString().c_str());//divya added.
        //        m_tkaReaderTibia->Update();//divya added.
        //        tibia_pixelspacing = m_tkaReaderTibia->GetPixelSpacing();//added 3-9-24


        //        m_extractvoi_Tibia->SetInputConnection(m_tkaReaderTibia->GetOutputPort());
        //        //m_extractvoi_Tibia->SetVOI(0,497,150,350,0,53);//old bone
        //        m_extractvoi_Tibia->SetVOI(0,497,250,m_tkaReaderTibia->GetOutput()->GetDimensions()[1]-1,0,m_tkaReaderTibia->GetOutput()->GetDimensions()[2]-1);
        //        m_extractvoi_Tibia->Update();

        //        surface_Tibia->SetInputConnection(m_extractvoi_Tibia->GetOutputPort());
        //        surface_Tibia->ComputeNormalsOn();
        //        surface_Tibia->SetValue(0, 300);//300
        //        surface_Tibia->Update();
        //---------------

        m_tkaReaderTibia->SetFileName(m_direc_tibia.toStdString().c_str());
        m_tkaReaderTibia->Update();

        // Create the smooth filter
        smoothFilterTibia->SetInputConnection(m_tkaReaderTibia->GetOutputPort());
        smoothFilterTibia->SetNumberOfIterations(50);   // Increase for more smoothing
        smoothFilterTibia->SetRelaxationFactor(0.1);    // Controls how strong the smoothing is (0-1)
        smoothFilterTibia->FeatureEdgeSmoothingOff();   // To avoid smoothing sharp edges
        smoothFilterTibia->BoundarySmoothingOn();       // Smooth boundaries
        smoothFilterTibia->Update();  // Apply the filter


        //surface_Tibia->SetInputData(m_tkaReaderTibia->GetOutput());
        //surface_Tibia->Update();

        firsttimeFlag = true;
    }


    if(view == "Anterior" && kneepart =="Femur")
    {


        qDebug()<<"Chkpt = 2";
        TopLeftAnteriorFemur3DWidget->SetRenderWindow(renderWindow_tka[0]);
        TopLeftAnteriorFemur3DWidget->GetRenderWindow()->AddRenderer(renderer_tka[0]);
        TopLeftAnteriorFemur3DWidget->GetRenderWindow()->SetInteractor(interactor_tka[0]);


        mapper_3dtka[0]->SetInputConnection(smoothFilterFemur->GetOutputPort());
        mapper_3dtka[0]->ScalarVisibilityOff();
        mapper_3dtka[0]->Update();

        actor_3dtka[0]->SetMapper(mapper_3dtka[0]);
        actor_3dtka[0]->SetProperty( BoneProperty );

        double bounds_1[6];
        actor_3dtka[0]->GetBounds(bounds_1);  // bounds: [xmin, xmax, ymin, ymax, zmin, zmax]

        // Calculate the distance from the camera to the bounding box
        double diagonal = sqrt(
                    pow(bounds_1[1] - bounds_1[0], 2) +
                pow(bounds_1[3] - bounds_1[2], 2) +
                pow(bounds_1[5] - bounds_1[4], 2));

        // Set the clipping range
        double nearClip = diagonal * 0.1;  // Near clipping plane should be a fraction of the diagonal
        double farClip = diagonal * 10.0;  // Far clipping plane should be larger

        // Ensure clipping planes are within reasonable bounds
        nearClip = std::max(nearClip, 1.0); // Avoid setting near clipping plane to zero
        farClip = std::max(farClip, nearClip + 1.0); // Ensure far plane is further than near plane


        // renderer->SetBackground(colors->GetColor3d("DarkSlateGray").GetData());

        renderer_tka[0]->AddActor(actor_3dtka[0]);
        renderer_tka[0]->Render();

        renderWindow_tka[0]->AddRenderer(renderer_tka[0]);
        //renderWindow_tka[0]->SetWindowName("MarchingCubes");


        interactor_tka[0]->SetRenderWindow(renderWindow_tka[0]);
        //interactor_tka[0]->SetInteractorStyle(style_1[0]);
        interactor_tka[0]->SetInteractorStyle(customstyle[0]); //testing purpose commented






        renderer_tka[0]->Render();
        renderer_tka[0]->ResetCamera();

        //-----------------------------------------------------------------
        // Calculate the bottom center of the actor (focus on zMin)
        double focalPointX = (bounds_1[1]) / 1.5;  // Bottom in x-axis
        double focalPointY = (bounds_1[2] + bounds_1[3]) / 2.0;  // Center in y-axis
        double focalPointZ = (bounds_1[5] + bounds_1[4]) /2.0;  // Center in z-axis

        //renderer_tka[0]->GetActiveCamera()->SetFocalPoint(focalPointX, focalPointY, focalPointZ); //for patient data
        renderer_tka[0]->GetActiveCamera()->SetFocalPoint(135.548/*117.548*/ ,177.983, 441.373);//for phantom data


        // Adjust the camera position to look at the bottom part of the actor
        // Move the camera up along the z-axis to ensure the actor is fully in view
        double distanceAbove = (bounds_1[1] - bounds_1[0]); // Adjust distance based on actor height
        //renderer_tka[0]->GetActiveCamera()->SetPosition(focalPointX , focalPointY, focalPointZ + distanceAbove);// for patient data
        renderer_tka[0]->GetActiveCamera()->SetPosition(83.4802/*83.4802*/, 338.704 ,433.027);// for phantom data
        renderer_tka[0]->GetActiveCamera()->SetViewUp(0,0,-1);// for phantom data
        //------------------------------------------------------------------

        //renderer_tka[0]->GetActiveCamera()->Zoom(0.7); //80% zoom //for patiient data
        renderer_tka[0]->GetActiveCamera()->Zoom(0.8); ////testing for phantom data


        //--setting initial camera values to the custonstyle variables---------//for patient dataa
        //        customstyle[0]->InitialFocalPoint[0] = focalPointX;
        //        customstyle[0]->InitialFocalPoint[1] = focalPointY;
        //        customstyle[0]->InitialFocalPoint[2] = focalPointZ;
        //        customstyle[0]->InitialPosition[0] = focalPointX;
        //        customstyle[0]->InitialPosition[1] = focalPointY;
        //        customstyle[0]->InitialPosition[2] = focalPointZ + distanceAbove;
        //        customstyle[0]->initialzoom = 0.7;
        //        customstyle[0]->initialRoll = roll.toInt();
        //        customstyle[0]->initialElevation=elevation.toInt();
        //        customstyle[0]->initialAzimuth=azimuth.toInt();
        //        customstyle[0]->initialnearclip=nearClip;
        //        customstyle[0]->initialfarclip=farClip+500;
        //----for  phantom data-----------:
        customstyle[0]->InitialFocalPoint[0] = 135.548;//117.548
        customstyle[0]->InitialFocalPoint[1] = 177.983;
        customstyle[0]->InitialFocalPoint[2] = 441.373;
        customstyle[0]->InitialPosition[0] = 83.4802;
        customstyle[0]->InitialPosition[1] = 338.704;
        customstyle[0]->InitialPosition[2] = 433.027;
        customstyle[0]->initialzoom = 0.8;//0.5
        customstyle[0]->initialRoll = roll.toInt();
        customstyle[0]->initialElevation=elevation.toInt();
        customstyle[0]->initialAzimuth=azimuth.toInt();
        customstyle[0]->initialnearclip=nearClip;
        customstyle[0]->initialfarclip=farClip+500;


        //Anterior femur
        renderer_tka[0]->GetActiveCamera()->Roll(roll.toInt());
        renderer_tka[0]->GetActiveCamera()->Elevation(elevation.toInt());
        renderer_tka[0]->GetActiveCamera()->Azimuth(azimuth.toInt());//added26-9-24

        renderer_tka[0]->GetActiveCamera()->SetClippingRange(nearClip,farClip+500);
        renderer_tka[0]->Render();


        TopLeftAnteriorFemur3DWidget->GetRenderWindow()->Render();
        interactor_tka[0]->Initialize();
        TopLeftAnteriorFemur3DWidget->update();



        // qDebug()<<"Chkpt = 3";
    }
    else if(view == "Distal" && kneepart =="Femur")
    {


        TopMiddleDistalFemur3DWidget->SetRenderWindow(renderWindow_tka[1]);
        TopMiddleDistalFemur3DWidget->GetRenderWindow()->AddRenderer(renderer_tka[1]);
        TopMiddleDistalFemur3DWidget->GetRenderWindow()->SetInteractor(interactor_tka[1]);

        mapper_3dtka[1]->SetInputConnection(smoothFilterFemur->GetOutputPort());
        mapper_3dtka[1]->ScalarVisibilityOff();
        mapper_3dtka[1]->Update();

        actor_3dtka[1]->SetMapper(mapper_3dtka[1]);
        //actor_3dtka[1]->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        double bounds_1[6];
        actor_3dtka[1]->GetBounds(bounds_1);  // bounds: [xmin, xmax, ymin, ymax, zmin, zmax]

        // Calculate the distance from the camera to the bounding box
        double diagonal = sqrt(
                    pow(bounds_1[1] - bounds_1[0], 2) +
                pow(bounds_1[3] - bounds_1[2], 2) +
                pow(bounds_1[5] - bounds_1[4], 2));

        // Set the clipping range
        double nearClip = diagonal * 0.1;  // Near clipping plane should be a fraction of the diagonal
        double farClip = diagonal * 10.0;  // Far clipping plane should be larger

        // Ensure clipping planes are within reasonable bounds
        nearClip = std::max(nearClip, 1.0); // Avoid setting near clipping plane to zero
        farClip = std::max(farClip, nearClip + 1.0); // Ensure far plane is further than near plane

        renderer_tka[1]->AddActor(actor_3dtka[1]);
        renderer_tka[1]->Render();

        renderWindow_tka[1]->AddRenderer(renderer_tka[1]);

        interactor_tka[1]->SetRenderWindow(renderWindow_tka[1]);
        //interactor_tka[1]->SetInteractorStyle(style_1[1]);
        interactor_tka[1]->SetInteractorStyle(customstyle[1]);

        renderer_tka[1]->Render();
        renderer_tka[1]->ResetCamera();

        //-----------------------------------------------------------------
        // Calculate the bottom center of the actor (focus on zMin)
        double focalPointX = ( bounds_1[1]) / 1.3;  // Bottom in x-axis
        double focalPointY = (bounds_1[2] + bounds_1[3]) / 2.0;  // Center in y-axis
        double focalPointZ = (bounds_1[4] + bounds_1[5]) / 2.0;  // Center in z-axis
        //renderer_tka[1]->GetActiveCamera()->SetFocalPoint(focalPointX, focalPointY, focalPointZ);//patient data
        renderer_tka[1]->GetActiveCamera()->SetFocalPoint(/*117.548*/135.548 ,135.983/*177.983*/, 441.373);//for phantom data

        // Adjust the camera position to look at the bottom part of the actor
        // Move the camera up along the z-axis to ensure the actor is fully in view
        double distanceAbove = (bounds_1[1] - bounds_1[0]); // Adjust distance based on actor height
        //renderer_tka[1]->GetActiveCamera()->SetPosition(focalPointX, focalPointY, focalPointZ + distanceAbove);//for or patient data

        renderer_tka[1]->GetActiveCamera()->SetPosition(83.4802, 338.704 ,433.027);// for phantom data
        renderer_tka[1]->GetActiveCamera()->SetViewUp(0,0,-1);// for phantom data
        //------------------------------------------------------------------
        //renderer_tka[1]->GetActiveCamera()->Zoom(0.8); //fro patient data
        renderer_tka[1]->GetActiveCamera()->Zoom(0.9); ////testing for phantom data

        //        //--setting initial camera values to the custonstyle variables---------//for patient data
        //        customstyle[1]->InitialFocalPoint[0] = focalPointX;
        //        customstyle[1]->InitialFocalPoint[1] = focalPointY;
        //        customstyle[1]->InitialFocalPoint[2] = focalPointZ;
        //        customstyle[1]->InitialPosition[0] = focalPointX;
        //        customstyle[1]->InitialPosition[1] = focalPointY;
        //        customstyle[1]->InitialPosition[2] = focalPointZ + distanceAbove;
        //        customstyle[1]->initialzoom = 0.8;
        //        customstyle[1]->initialRoll = roll.toInt();
        //        customstyle[1]->initialElevation=elevation.toInt();
        //        customstyle[1]->initialAzimuth=azimuth.toInt();
        //        customstyle[1]->initialnearclip=nearClip;
        //        customstyle[1]->initialfarclip=farClip+200;

        //----for  phantom data-----------:
        customstyle[1]->InitialFocalPoint[0] = 135.548;//117.548;
        customstyle[1]->InitialFocalPoint[1] = 135.983;//177.983
        customstyle[1]->InitialFocalPoint[2] = 441.373;
        customstyle[1]->InitialPosition[0] = 83.4802;
        customstyle[1]->InitialPosition[1] = 338.704;
        customstyle[1]->InitialPosition[2] = 433.027;
        customstyle[1]->initialzoom = 0.9;//0.8
        customstyle[1]->initialRoll = roll.toInt();
        customstyle[1]->initialElevation=elevation.toInt();
        customstyle[1]->initialAzimuth=azimuth.toInt();
        customstyle[1]->initialnearclip=nearClip;
        customstyle[1]->initialfarclip=farClip+500;



        //Distal femur
        renderer_tka[1]->GetActiveCamera()->Roll(roll.toInt());
        renderer_tka[1]->GetActiveCamera()->Elevation(elevation.toInt());
        renderer_tka[1]->GetActiveCamera()->Azimuth(azimuth.toInt());//added26-9-24


        renderer_tka[1]->GetActiveCamera()->SetClippingRange(nearClip,farClip+200);
        renderer_tka[1]->Render();

        TopMiddleDistalFemur3DWidget->GetRenderWindow()->Render();
        interactor_tka[1]->Initialize();
        TopMiddleDistalFemur3DWidget->update();
    }
    else if(view == "Lateral" && kneepart =="Femur")
    {


        TopRightLateralFemur3DWidget->SetRenderWindow(renderWindow_tka[2]);
        TopRightLateralFemur3DWidget->GetRenderWindow()->AddRenderer(renderer_tka[2]);
        TopRightLateralFemur3DWidget->GetRenderWindow()->SetInteractor(interactor_tka[2]);

        mapper_3dtka[2]->SetInputConnection(smoothFilterFemur->GetOutputPort());
        mapper_3dtka[2]->ScalarVisibilityOff();
        mapper_3dtka[2]->Update();

        actor_3dtka[2]->SetMapper(mapper_3dtka[2]);
        //actor_3dtka[2]->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        double bounds_1[6];
        actor_3dtka[2]->GetBounds(bounds_1);  // bounds: [xmin, xmax, ymin, ymax, zmin, zmax]

        // Calculate the distance from the camera to the bounding box
        double diagonal = sqrt(
                    pow(bounds_1[1] - bounds_1[0], 2) +
                pow(bounds_1[3] - bounds_1[2], 2) +
                pow(bounds_1[5] - bounds_1[4], 2));

        // Set the clipping range
        double nearClip = diagonal * 0.1;  // Near clipping plane should be a fraction of the diagonal
        double farClip = diagonal * 10.0;  // Far clipping plane should be larger

        // Ensure clipping planes are within reasonable bounds
        nearClip = std::max(nearClip, 1.0); // Avoid setting near clipping plane to zero
        farClip = std::max(farClip, nearClip + 1.0); // Ensure far plane is further than near plane

        renderer_tka[2]->AddActor(actor_3dtka[2]);
        renderer_tka[2]->Render();

        renderWindow_tka[2]->AddRenderer(renderer_tka[2]);
        interactor_tka[2]->SetRenderWindow(renderWindow_tka[2]);
        //interactor_tka[2]->SetInteractorStyle(style_1[2]);
        interactor_tka[2]->SetInteractorStyle(customstyle[2]);


        renderer_tka[2]->Render();
        renderer_tka[2]->ResetCamera();

        //-----------------------------------------------------------------
        // Calculate the bottom center of the actor (focus on zMin)
        double focalPointX = ( bounds_1[1]) / 1.5;  // Bottom in x-axis
        double focalPointY = (bounds_1[2] + bounds_1[3]) / 2.0;  // Center in y-axis
        double focalPointZ = (bounds_1[5] + bounds_1[5])/ 2.0;  // Center in z-axis

        //renderer_tka[2]->GetActiveCamera()->SetFocalPoint(focalPointX, focalPointY, focalPointZ);// for patient data

        // Adjust the camera position to look at the bottom part of the actor
        // Move the camera up along the z-axis to ensure the actor is fully in view
        double distanceAbove = (bounds_1[1] - bounds_1[0]); // Adjust distance based on actor height
        //renderer_tka[2]->GetActiveCamera()->SetPosition(focalPointX, focalPointY, focalPointZ + distanceAbove);// for patient data
        //------------------------------------------------------------------

        renderer_tka[2]->GetActiveCamera()->SetFocalPoint(125.548/*117.548*/ ,165.983/*177.983*/, 441.373);//for phantom data
        renderer_tka[2]->GetActiveCamera()->SetPosition(83.4802, 338.704 ,433.027);// for phantom data
        renderer_tka[2]->GetActiveCamera()->SetViewUp(0,0,-1);// for phantom data


        //renderer_tka[2]->GetActiveCamera()->Zoom(0.7);//patient data
        renderer_tka[2]->GetActiveCamera()->Zoom(0.7);//for phantom data//0.5

        //--setting initial camera values to the custonstyle variables---------for patient data
        //        customstyle[2]->InitialFocalPoint[0] = focalPointX;
        //        customstyle[2]->InitialFocalPoint[1] = focalPointY;
        //        customstyle[2]->InitialFocalPoint[2] = focalPointZ;
        //        customstyle[2]->InitialPosition[0] = focalPointX;
        //        customstyle[2]->InitialPosition[1] = focalPointY;
        //        customstyle[2]->InitialPosition[2] = focalPointZ + distanceAbove;
        //        customstyle[2]->initialzoom = 0.7;
        //        customstyle[2]->initialRoll = roll.toInt();
        //        customstyle[2]->initialElevation=elevation.toInt();
        //        customstyle[2]->initialAzimuth=azimuth.toInt();
        //        customstyle[2]->initialnearclip=nearClip;
        //        customstyle[2]->initialfarclip=farClip+200;

        //----for  phantom data-----------:
        customstyle[2]->InitialFocalPoint[0] = 125.548;//117.548
        customstyle[2]->InitialFocalPoint[1] = 165.983;//177.943
        customstyle[2]->InitialFocalPoint[2] = 441.373;
        customstyle[2]->InitialPosition[0] = 83.4802;
        customstyle[2]->InitialPosition[1] = 338.704;
        customstyle[2]->InitialPosition[2] = 433.027;
        customstyle[2]->initialzoom = 0.7;//0.5
        customstyle[2]->initialRoll = roll.toInt();
        customstyle[2]->initialElevation=elevation.toInt();
        customstyle[2]->initialAzimuth=azimuth.toInt();
        customstyle[2]->initialnearclip=nearClip;
        customstyle[2]->initialfarclip=farClip+500;

        //Lateral femur
        renderer_tka[2]->GetActiveCamera()->Roll(roll.toInt());
        renderer_tka[2]->GetActiveCamera()->Elevation(elevation.toInt());
        renderer_tka[2]->GetActiveCamera()->Azimuth(azimuth.toInt());//added26-9-24

        renderer_tka[2]->GetActiveCamera()->SetClippingRange(nearClip,farClip+200);
        renderer_tka[2]->Render();

        TopRightLateralFemur3DWidget->GetRenderWindow()->Render();
        interactor_tka[2]->Initialize();
        TopRightLateralFemur3DWidget->update();
    }
    else if(view == "Anterior" && kneepart =="Tibia")
    {

        BottomLeftAnteriorTibia3DWidget->SetRenderWindow(renderWindow_tka[3]);
        BottomLeftAnteriorTibia3DWidget->GetRenderWindow()->AddRenderer(renderer_tka[3]);
        BottomLeftAnteriorTibia3DWidget->GetRenderWindow()->SetInteractor(interactor_tka[3]);

        mapper_3dtka[3]->SetInputConnection(smoothFilterTibia->GetOutputPort());
        mapper_3dtka[3]->ScalarVisibilityOff();
        mapper_3dtka[3]->Update();


        actor_3dtka[3]->SetMapper(mapper_3dtka[3]);
        //actor_3dtka[3]->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        double bounds_1[6];
        actor_3dtka[3]->GetBounds(bounds_1);  // bounds: [xmin, xmax, ymin, ymax, zmin, zmax]

        // Calculate the distance from the camera to the bounding box
        double diagonal = sqrt(
                    pow(bounds_1[1] - bounds_1[0], 2) +
                pow(bounds_1[3] - bounds_1[2], 2) +
                pow(bounds_1[5] - bounds_1[4], 2));

        // Set the clipping range
        double nearClip = diagonal * 0.1;  // Near clipping plane should be a fraction of the diagonal
        double farClip = diagonal * 10.0;  // Far clipping plane should be larger

        // Ensure clipping planes are within reasonable bounds
        nearClip = std::max(nearClip, 1.0); // Avoid setting near clipping plane to zero
        farClip = std::max(farClip, nearClip + 1.0); // Ensure far plane is further than near plane


        renderer_tka[3]->AddActor(actor_3dtka[3]);
        renderer_tka[3]->Render();

        renderWindow_tka[3]->AddRenderer(renderer_tka[3]);



        interactor_tka[3]->SetRenderWindow(renderWindow_tka[3]);
        //interactor_tka[3]->SetInteractorStyle(style_1[3]);
        interactor_tka[3]->SetInteractorStyle(customstyle[3]);


        renderer_tka[3]->Render();
        renderer_tka[3]->ResetCamera();
        //-----------------------------------------------------------------
        // Calculate the bottom center of the actor (focus on zMin)
        double focalPointX = (bounds_1[1]) / 1.5;  // Center in x-axis
        double focalPointY = (bounds_1[2] + bounds_1[3]) / 2.0;  // Center in y-axis
        double focalPointZ = (bounds_1[4] + bounds_1[5])/  2.0;  // Bottom in z-axis (zmax)

        //renderer_tka[3]->GetActiveCamera()->SetFocalPoint(focalPointX, focalPointY, focalPointZ); // for patient data

        // Adjust the camera position to look at the bottom part of the actor
        // Move the camera up along the z-axis to ensure the actor is fully in view
        double distanceAbove = (bounds_1[1] - bounds_1[0]); // Adjust distance based on actor height
        //renderer_tka[3]->GetActiveCamera()->SetPosition(focalPointX, focalPointY, focalPointZ + distanceAbove); // for patient data
        //------------------------------------------------------------------
        //renderer_tka[3]->GetActiveCamera()->Zoom(0.6);// for patient data
        renderer_tka[3]->GetActiveCamera()->SetFocalPoint(150.054 /*130.054*/ ,189.643, 535.304);//for phantom data
        renderer_tka[3]->GetActiveCamera()->SetPosition(126.878, 348.476, 492.603);// for phantom data
        renderer_tka[3]->GetActiveCamera()->SetViewUp(0,0,-1);// for phantom data


        renderer_tka[3]->GetActiveCamera()->Zoom(0.8);// for phantom data//0.6

        //--setting initial camera values to the custonstyle variables---------
        //        customstyle[3]->InitialFocalPoint[0] = focalPointX;
        //        customstyle[3]->InitialFocalPoint[1] = focalPointY;
        //        customstyle[3]->InitialFocalPoint[2] = focalPointZ;
        //        customstyle[3]->InitialPosition[0] = focalPointX;
        //        customstyle[3]->InitialPosition[1] = focalPointY;
        //        customstyle[3]->InitialPosition[2] = focalPointZ + distanceAbove;
        //        customstyle[3]->initialzoom = 0.6;
        //        customstyle[3]->initialRoll = roll.toInt();
        //        customstyle[3]->initialElevation=elevation.toInt();
        //        customstyle[3]->initialAzimuth=azimuth.toInt();
        //        customstyle[3]->initialnearclip=nearClip;
        //        customstyle[3]->initialfarclip=farClip+200;

        //----for  phantom data-----------:
        customstyle[3]->InitialFocalPoint[0] = 150.054;//130.054
        customstyle[3]->InitialFocalPoint[1] = 189.643;
        customstyle[3]->InitialFocalPoint[2] = 535.304;
        customstyle[3]->InitialPosition[0] = 126.878;
        customstyle[3]->InitialPosition[1] = 348.476;
        customstyle[3]->InitialPosition[2] = 492.603;
        customstyle[3]->initialzoom = 0.8;
        customstyle[3]->initialRoll = roll.toInt();
        customstyle[3]->initialElevation=elevation.toInt();
        customstyle[3]->initialAzimuth=azimuth.toInt();
        customstyle[3]->initialnearclip=nearClip;
        customstyle[3]->initialfarclip=farClip+500;



        //Anterior Tibia
        renderer_tka[3]->GetActiveCamera()->Roll(roll.toInt());
        renderer_tka[3]->GetActiveCamera()->Elevation(elevation.toInt());
        renderer_tka[3]->GetActiveCamera()->Azimuth(azimuth.toInt());//added26-9-24

        renderer_tka[3]->GetActiveCamera()->SetClippingRange(nearClip,farClip+200);
        renderer_tka[3]->Render();

        BottomLeftAnteriorTibia3DWidget->GetRenderWindow()->Render();
        interactor_tka[3]->Initialize();
        BottomLeftAnteriorTibia3DWidget->update();
    }

    else if(view == "Distal" && kneepart =="Tibia")
    {


        BottomMiddleDistalTibia3DWidget->SetRenderWindow(renderWindow_tka[4]);
        BottomMiddleDistalTibia3DWidget->GetRenderWindow()->AddRenderer(renderer_tka[4]);
        BottomMiddleDistalTibia3DWidget->GetRenderWindow()->SetInteractor(interactor_tka[4]);

        mapper_3dtka[4]->SetInputConnection(smoothFilterTibia->GetOutputPort());
        mapper_3dtka[4]->ScalarVisibilityOff();
        mapper_3dtka[4]->Update();


        actor_3dtka[4]->SetMapper(mapper_3dtka[4]);
        //actor_3dtka[4]->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        double bounds_1[6];
        actor_3dtka[4]->GetBounds(bounds_1);  // bounds: [xmin, xmax, ymin, ymax, zmin, zmax]

        // Calculate the distance from the camera to the bounding box
        double diagonal = sqrt(
                    pow(bounds_1[1] - bounds_1[0], 2) +
                pow(bounds_1[3] - bounds_1[2], 2) +
                pow(bounds_1[5] - bounds_1[4], 2));

        // Set the clipping range
        double nearClip = diagonal * 0.1;  // Near clipping plane should be a fraction of the diagonal
        double farClip = diagonal * 10.0;  // Far clipping plane should be larger

        // Ensure clipping planes are within reasonable bounds
        nearClip = std::max(nearClip, 1.0); // Avoid setting near clipping plane to zero
        farClip = std::max(farClip, nearClip + 1.0); // Ensure far plane is further than near plane



        renderer_tka[4]->AddActor(actor_3dtka[4]);
        renderer_tka[4]->Render();

        renderWindow_tka[4]->AddRenderer(renderer_tka[4]);



        interactor_tka[4]->SetRenderWindow(renderWindow_tka[4]);
        //interactor_tka[4]->SetInteractorStyle(style_1[4]);
        interactor_tka[4]->SetInteractorStyle(customstyle[4]);


        renderer_tka[4]->Render();
        renderer_tka[4]->ResetCamera();
        //-----------------------------------------------------------------
        // Calculate the bottom center of the actor (focus on zMin)
        double focalPointX = (bounds_1[1]) / 1.5;  // Center in x-axis
        double focalPointY = (bounds_1[2] + bounds_1[3]) / 2.0;  // Center in y-axis
        double focalPointZ = (bounds_1[4]+bounds_1[5]) / 2.0;  // Bottom in z-axis (zmax)

        //renderer_tka[4]->GetActiveCamera()->SetFocalPoint(focalPointX, focalPointY, focalPointZ);//for patient data

        // Adjust the camera position to look at the bottom part of the actor
        // Move the camera up along the z-axis to ensure the actor is fully in view
        double distanceAbove = (bounds_1[1] - bounds_1[0]); // Adjust distance based on actor height
        //renderer_tka[4]->GetActiveCamera()->SetPosition(focalPointX, focalPointY, focalPointZ + distanceAbove);//for patient data
        //------------------------------------------------------------------

        renderer_tka[4]->GetActiveCamera()->SetFocalPoint(145.054 /*130.054 */,150.643/*189.643*/, 535.304);//for phantom data
        renderer_tka[4]->GetActiveCamera()->SetPosition(139.67, 148.723, 376.262);// for phantom data
        renderer_tka[4]->GetActiveCamera()->SetViewUp(0,0,-1);// for phantom data

        //        renderer_tka[4]->GetActiveCamera()->Zoom(0.6);//for patient data
        renderer_tka[4]->GetActiveCamera()->Zoom(0.8);//for phantom data//0.7


        //--setting initial camera values to the custonstyle variables---------for patient data
        //        customstyle[4]->InitialFocalPoint[0] = focalPointX;
        //        customstyle[4]->InitialFocalPoint[1] = focalPointY;
        //        customstyle[4]->InitialFocalPoint[2] = focalPointZ;
        //        customstyle[4]->InitialPosition[0] = focalPointX;
        //        customstyle[4]->InitialPosition[1] = focalPointY;
        //        customstyle[4]->InitialPosition[2] = focalPointZ + distanceAbove;
        //        customstyle[4]->initialzoom = 0.6;
        //        customstyle[4]->initialRoll = roll.toInt();
        //        customstyle[4]->initialElevation=elevation.toInt();
        //        customstyle[4]->initialAzimuth=azimuth.toInt();
        //        customstyle[4]->initialnearclip=nearClip;
        //        customstyle[4]->initialfarclip=farClip+200;

        //----for  phantom data-----------:
        customstyle[4]->InitialFocalPoint[0] = 145.054;
        customstyle[4]->InitialFocalPoint[1] = 150.643/*189.643*/;
        customstyle[4]->InitialFocalPoint[2] = 535.304;
        customstyle[4]->InitialPosition[0] = 139.67;
        customstyle[4]->InitialPosition[1] = 148.723;
        customstyle[4]->InitialPosition[2] = 376.262;
        customstyle[4]->initialzoom = 0.8;//0.7
        customstyle[4]->initialRoll = roll.toInt();
        customstyle[4]->initialElevation=elevation.toInt();
        customstyle[4]->initialAzimuth=azimuth.toInt();
        customstyle[4]->initialnearclip=nearClip;
        customstyle[4]->initialfarclip=farClip+500;

        //Distal tibia
        renderer_tka[4]->GetActiveCamera()->Roll(roll.toInt());
        renderer_tka[4]->GetActiveCamera()->Elevation(elevation.toInt());
        renderer_tka[4]->GetActiveCamera()->Azimuth(azimuth.toInt());//added26-9-24

        renderer_tka[4]->GetActiveCamera()->SetClippingRange(nearClip,farClip+200);
        renderer_tka[4]->Render();

        BottomMiddleDistalTibia3DWidget->GetRenderWindow()->Render();
        interactor_tka[4]->Initialize();
        BottomMiddleDistalTibia3DWidget->update();
    }

    else if(view == "Lateral" && kneepart =="Tibia")
    {


        BottomRightLateralTibia3DWidget->SetRenderWindow(renderWindow_tka[5]);
        BottomRightLateralTibia3DWidget->GetRenderWindow()->AddRenderer(renderer_tka[5]);
        BottomRightLateralTibia3DWidget->GetRenderWindow()->SetInteractor(interactor_tka[5]);

        mapper_3dtka[5]->SetInputConnection(smoothFilterTibia->GetOutputPort());
        mapper_3dtka[5]->ScalarVisibilityOff();
        mapper_3dtka[5]->Update();

        actor_3dtka[5]->SetMapper(mapper_3dtka[5]);
        //actor_3dtka[5]->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        double bounds_1[6];
        actor_3dtka[5]->GetBounds(bounds_1);  // bounds: [xmin, xmax, ymin, ymax, zmin, zmax]

        // Calculate the distance from the camera to the bounding box
        double diagonal = sqrt(
                    pow(bounds_1[1] - bounds_1[0], 2) +
                pow(bounds_1[3] - bounds_1[2], 2) +
                pow(bounds_1[5] - bounds_1[4], 2));

        // Set the clipping range
        double nearClip = diagonal * 0.1;  // Near clipping plane should be a fraction of the diagonal
        double farClip = diagonal * 10.0;  // Far clipping plane should be larger

        // Ensure clipping planes are within reasonable bounds
        nearClip = std::max(nearClip, 1.0); // Avoid setting near clipping plane to zero
        farClip = std::max(farClip, nearClip + 1.0); // Ensure far plane is further than near plane



        renderer_tka[5]->AddActor(actor_3dtka[5]);
        renderer_tka[5]->Render();

        renderWindow_tka[5]->AddRenderer(renderer_tka[5]);



        interactor_tka[5]->SetRenderWindow(renderWindow_tka[5]);
        //interactor_tka[5]->SetInteractorStyle(style_1[5]);
        interactor_tka[5]->SetInteractorStyle(customstyle[5]);


        renderer_tka[5]->Render();
        renderer_tka[5]->ResetCamera();

        //-----------------------------------------------------------------
        // Calculate the bottom center of the actor (focus on zMin)
        double focalPointX = (bounds_1[1]) / 1.5;  // Center in x-axis
        double focalPointY = (bounds_1[2] + bounds_1[3]) / 2.0;  // Center in y-axis
        double focalPointZ = (bounds_1[4] + bounds_1[5]) / 2.0;  // Bottom in z-axis (zmax)

        //renderer_tka[5]->GetActiveCamera()->SetFocalPoint(focalPointX, focalPointY, focalPointZ);// for patient data

        // Adjust the camera position to look at the bottom part of the actor
        // Move the camera up along the z-axis to ensure the actor is fully in view
        double distanceAbove = (bounds_1[1] - bounds_1[0]); // Adjust distance based on actor height
        //renderer_tka[5]->GetActiveCamera()->SetPosition(focalPointX, focalPointY, focalPointZ + distanceAbove);// for patient dtaa
        //------------------------------------------------------------------
        //renderer_tka[5]->GetActiveCamera()->Zoom(0.6);// for patient data

        renderer_tka[5]->GetActiveCamera()->SetFocalPoint(150.054/*130.054*/ ,150.643/*189.643*/, 535.304);//for phantom data
        renderer_tka[5]->GetActiveCamera()->SetPosition(126.878, 348.476, 492.603);// for phantom data
        renderer_tka[5]->GetActiveCamera()->SetViewUp(0,0,-1);// for phantom data
        renderer_tka[5]->GetActiveCamera()->Zoom(0.9);// for patient data




        //--setting initial camera values to the custonstyle variables------for patient data---
        //        customstyle[5]->InitialFocalPoint[0] = focalPointX;
        //        customstyle[5]->InitialFocalPoint[1] = focalPointY;
        //        customstyle[5]->InitialFocalPoint[2] = focalPointZ;
        //        customstyle[5]->InitialPosition[0] = focalPointX;
        //        customstyle[5]->InitialPosition[1] = focalPointY;
        //        customstyle[5]->InitialPosition[2] = focalPointZ + distanceAbove;
        //        customstyle[5]->initialzoom = 0.6;
        //        customstyle[5]->initialRoll = roll.toInt();
        //        customstyle[5]->initialElevation=elevation.toInt();
        //        customstyle[5]->initialAzimuth=azimuth.toInt();
        //        customstyle[5]->initialnearclip=nearClip;
        //        customstyle[5]->initialfarclip=farClip+200;

        //----for  phantom data-----------:
        customstyle[5]->InitialFocalPoint[0] = 150.054;//130.054
        customstyle[5]->InitialFocalPoint[1] = 150.643;//189.643
        customstyle[5]->InitialFocalPoint[2] = 535.304;
        customstyle[5]->InitialPosition[0] = 126.878;
        customstyle[5]->InitialPosition[1] = 348.476;
        customstyle[5]->InitialPosition[2] = 492.603;
        customstyle[5]->initialzoom = 0.9;
        customstyle[5]->initialRoll = roll.toInt();
        customstyle[5]->initialElevation=elevation.toInt();
        customstyle[5]->initialAzimuth=azimuth.toInt();
        customstyle[5]->initialnearclip=nearClip;
        customstyle[5]->initialfarclip=farClip+500;


        //Lateral tibia
        renderer_tka[5]->GetActiveCamera()->Roll(roll.toInt());
        renderer_tka[5]->GetActiveCamera()->Elevation(elevation.toInt());
        renderer_tka[5]->GetActiveCamera()->Azimuth(azimuth.toInt());//added26-9-24


        renderer_tka[5]->GetActiveCamera()->SetClippingRange(nearClip,farClip+200);
        renderer_tka[5]->Render();

        BottomRightLateralTibia3DWidget->GetRenderWindow()->Render();
        interactor_tka[5]->Initialize();
        BottomRightLateralTibia3DWidget->update();
    }


}

void TKAThreeDView::UpdateTibiaData(vtkPolyData *m_cutdata,bool clickedValue)
{

    if(Cut_firsttime_tibia == false)
    {

        vtkSmartPointer<vtkPolyDataMapper> tibia_cutMapper1 =vtkSmartPointer<vtkPolyDataMapper>::New();
        tibia_cutMapper1->SetInputData(m_cutdata);
        tibia_cutMapper1->ScalarVisibilityOn();
        tibia_cutMapper1->Update();

        vtkSmartPointer<vtkPolyDataMapper> tibia_cutMapper2 =vtkSmartPointer<vtkPolyDataMapper>::New();
        tibia_cutMapper2->SetInputData(m_cutdata);
        tibia_cutMapper2->ScalarVisibilityOn();
        tibia_cutMapper2->Update();

        vtkSmartPointer<vtkPolyDataMapper> tibia_cutMapper3 =vtkSmartPointer<vtkPolyDataMapper>::New();
        tibia_cutMapper3->SetInputData(m_cutdata);
        tibia_cutMapper3->ScalarVisibilityOn();
        tibia_cutMapper3->Update();

        //Actor
        tibia_cutActor_Anterior->SetMapper(tibia_cutMapper1);
        //tibia_cutActor_Anterior->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        tibia_cutActor_Distal->SetMapper(tibia_cutMapper2);


        //tibia_cutActor_Distal->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone
        tibia_cutActor_Lateral->SetMapper(tibia_cutMapper3);
        //tibia_cutActor_Lateral->GetProperty()->SetColor(0.890, 0.855, 0.788);//color of bone



        //actor_3dtka[3]->SetVisibility(false);
        renderer_tka[3]->AddActor(tibia_cutActor_Anterior);
        renderer_tka[3]->Render();
        renderWindow_tka[3]->Render();

        //actor_3dtka[4]->SetVisibility(false);
        renderer_tka[4]->AddActor(tibia_cutActor_Distal);
        renderer_tka[4]->Render();
        renderWindow_tka[4]->Render();

        //actor_3dtka[5]->SetVisibility(false);
        renderer_tka[5]->AddActor(tibia_cutActor_Lateral);
        renderer_tka[5]->Render();
        renderWindow_tka[5]->Render();

        Cut_firsttime_tibia = true;
    }


    if(clickedValue == true)
    {
        //qDebug()<<"cut =  true";
        actor_3dtka[3]->SetVisibility(false);
        tibia_cutActor_Anterior->SetVisibility(true);
        renderer_tka[3]->Render();
        renderWindow_tka[3]->Render();

        actor_3dtka[4]->SetVisibility(false);
        tibia_cutActor_Distal->SetVisibility(true);
        renderer_tka[4]->Render();
        renderWindow_tka[4]->Render();

        actor_3dtka[5]->SetVisibility(false);
        tibia_cutActor_Lateral->SetVisibility(true);
        renderer_tka[5]->Render();
        renderWindow_tka[5]->Render();
    }
    else
    {
        //qDebug()<<"cut =  false";
        actor_3dtka[3]->SetVisibility(true);
        tibia_cutActor_Anterior->SetVisibility(false);
        renderer_tka[3]->Render();
        renderWindow_tka[3]->Render();

        actor_3dtka[4]->SetVisibility(true);
        tibia_cutActor_Distal->SetVisibility(false);
        renderer_tka[4]->Render();
        renderWindow_tka[4]->Render();

        actor_3dtka[5]->SetVisibility(true);
        tibia_cutActor_Lateral->SetVisibility(false);
        renderer_tka[5]->Render();
        renderWindow_tka[5]->Render();
    }
}

void TKAThreeDView::UpdateFemurData(vtkPolyData * m_cutfemur,bool clickedValue)
{

    if(Cut_firsttime_femur == false)
    {

        vtkSmartPointer<vtkPolyDataMapper> femur_cutMapper1 =vtkSmartPointer<vtkPolyDataMapper>::New();
        femur_cutMapper1->SetInputData(m_cutfemur);
        femur_cutMapper1->ScalarVisibilityOn();// to view the colros set using vtkunsignedchararray, this should be ON
        femur_cutMapper1->Update();

        vtkSmartPointer<vtkPolyDataMapper> femur_cutMapper2 =vtkSmartPointer<vtkPolyDataMapper>::New();
        femur_cutMapper2->SetInputData(m_cutfemur);
        femur_cutMapper2->ScalarVisibilityOn(); // to view the colros set using vtkunsignedchararray, this should be ON
        femur_cutMapper2->Update();

        vtkSmartPointer<vtkPolyDataMapper> femur_cutMapper3 =vtkSmartPointer<vtkPolyDataMapper>::New();
        femur_cutMapper3->SetInputData(m_cutfemur);
        femur_cutMapper3->ScalarVisibilityOn();// to view the colros set using vtkunsignedchararray, this should be ON
        femur_cutMapper3->Update();

        //Actor
        femur_cutActor_Anterior->SetMapper(femur_cutMapper1);
        femur_cutActor_Distal->SetMapper(femur_cutMapper2);
        femur_cutActor_Lateral->SetMapper(femur_cutMapper3);


        renderer_tka[0]->AddActor(femur_cutActor_Anterior);
        renderer_tka[0]->Render();
        renderWindow_tka[0]->Render();


        renderer_tka[1]->AddActor(femur_cutActor_Distal);
        renderer_tka[1]->Render();
        renderWindow_tka[1]->Render();


        renderer_tka[2]->AddActor(femur_cutActor_Lateral);
        renderer_tka[2]->Render();
        renderWindow_tka[2]->Render();

        Cut_firsttime_femur = true;
    }


    if(clickedValue == true)
    {
        //qDebug()<<"cut =  true";
        actor_3dtka[0]->SetVisibility(false);
        femur_cutActor_Anterior->SetVisibility(true);
        renderer_tka[0]->Render();
        renderWindow_tka[0]->Render();

        actor_3dtka[1]->SetVisibility(false);
        femur_cutActor_Distal->SetVisibility(true);
        renderer_tka[1]->Render();
        renderWindow_tka[1]->Render();

        actor_3dtka[2]->SetVisibility(false);
        femur_cutActor_Lateral->SetVisibility(true);
        renderer_tka[2]->Render();
        renderWindow_tka[2]->Render();
    }
    else
    {
        //qDebug()<<"cut =  false";
        actor_3dtka[0]->SetVisibility(true);
        femur_cutActor_Anterior->SetVisibility(false);
        renderer_tka[0]->Render();
        renderWindow_tka[0]->Render();

        actor_3dtka[1]->SetVisibility(true);
        femur_cutActor_Distal->SetVisibility(false);
        renderer_tka[1]->Render();
        renderWindow_tka[1]->Render();

        actor_3dtka[2]->SetVisibility(true);
        femur_cutActor_Lateral->SetVisibility(false);
        renderer_tka[2]->Render();
        renderWindow_tka[2]->Render();
    }

}
void TKAThreeDView::PrimarycutFemurandTibia(bool clicked_1)
{

    m_ObjAxisDisplayView->m_objKinematicsClass->GetPointsFRomAnnotationmodule();//added on 21-10-24
    m_ObjPrimaryResectionCut->PrimaryCut_Tibia(smoothFilterTibia->GetOutput(), clicked_1,tibia_pixelspacing,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_TibialLateralPlateauPoint,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_TibialMedialPlateauPoint,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_lateralProximalResectionDepth,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_medialProximalResectionDepth);
    m_ObjPrimaryResectionCut->PrimaryCut_Femur(smoothFilterFemur->GetOutput(),clicked_1,femur_pixelspacing,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_FemoralTEA_P1,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_FemoralTEA_P2,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_FemoralPCA_P1,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_FemoralPCA_P2,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->Femur_lateralDistalResectionDepth,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->Femur_medialDistalResectionDepth,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->Femur_lateralPosteriorResectionDepth,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->Femur_medialPosteriorResectionDepth,
                                               m_ObjAxisDisplayView->m_objKinematicsClass->m_FemoralMechAxisP2);

}

void TKAThreeDView::AxisDisplaySlot(bool clicked)
{
    qDebug()<<"Display axis clicked:"<<clicked;

    if(Axis_firsttime == false)
    {
        m_ObjAxisDisplayView->DisplayFemoralMechanicalAxis();
        m_ObjAxisDisplayView->DisplayTibialMechanicalAxis();
        //Axis_firsttime= true;//commented for now
    }

    if(clicked == true)
    {
        //Femur
        femurMechAxis_ActorAnterior->SetVisibility(true);
        femurMechAxis1_ActorDistal->SetVisibility(true);
        femurMechAxis2_ActorLateral->SetVisibility(true);

        femurTEA_ActorAnterior->SetVisibility(true);
        femurTEA_ActorDistal->SetVisibility(true);
        femurTEA_ActorLateral->SetVisibility(true);

        femurPCA_ActorAnterior->SetVisibility(true);
        femurPCA_ActorDistal->SetVisibility(true);
        femurPCA_ActorLateral->SetVisibility(true);

        femurFemCompAx_ActorAnterior->SetVisibility(true);
        femurFemCompAx_ActorDistal->SetVisibility(true);
        femurFemCompAx_ActorLateral->SetVisibility(true);

        renderer_tka[0]->Render();
        renderWindow_tka[0]->Render();

        renderer_tka[1]->Render();
        renderWindow_tka[1]->Render();

        renderer_tka[2]->Render();
        renderWindow_tka[2]->Render();

        //Tibia
        tibiaMechAxis_ActorAnterior->SetVisibility(true);
        tibiaMechAxis1_ActorDistal->SetVisibility(true);
        tibiaMechAxis2_ActorLateral->SetVisibility(true);
        tibiaTPL_ActorAnterior->SetVisibility(true);
        tibiaTPL_ActorDistal->SetVisibility(true);
        tibiaTPL_ActorLateral->SetVisibility(true);

        renderer_tka[3]->Render();
        renderWindow_tka[3]->Render();

        renderer_tka[4]->Render();
        renderWindow_tka[4]->Render();

        renderer_tka[5]->Render();
        renderWindow_tka[5]->Render();
    }
    else
    {
        //Femur
        femurMechAxis_ActorAnterior->SetVisibility(false);
        femurMechAxis1_ActorDistal->SetVisibility(false);
        femurMechAxis2_ActorLateral->SetVisibility(false);

        femurTEA_ActorAnterior->SetVisibility(false);
        femurTEA_ActorDistal->SetVisibility(false);
        femurTEA_ActorLateral->SetVisibility(false);

        femurPCA_ActorAnterior->SetVisibility(false);
        femurPCA_ActorDistal->SetVisibility(false);
        femurPCA_ActorLateral->SetVisibility(false);

        femurFemCompAx_ActorAnterior->SetVisibility(false);
        femurFemCompAx_ActorDistal->SetVisibility(false);
        femurFemCompAx_ActorLateral->SetVisibility(false);

        renderer_tka[0]->Render();
        renderWindow_tka[0]->Render();

        renderer_tka[1]->Render();
        renderWindow_tka[1]->Render();

        renderer_tka[2]->Render();
        renderWindow_tka[2]->Render();


        //Tibia
        tibiaMechAxis_ActorAnterior->SetVisibility(false);
        tibiaMechAxis1_ActorDistal->SetVisibility(false);
        tibiaMechAxis2_ActorLateral->SetVisibility(false);
        tibiaTPL_ActorAnterior->SetVisibility(false);
        tibiaTPL_ActorDistal->SetVisibility(false);
        tibiaTPL_ActorLateral->SetVisibility(false);

        renderer_tka[3]->Render();
        renderWindow_tka[3]->Render();

        renderer_tka[4]->Render();
        renderWindow_tka[4]->Render();

        renderer_tka[5]->Render();
        renderWindow_tka[5]->Render();
    }

}

void TKAThreeDView::UpdateAxisDisplay_Tibia(vtkPolyData * m_tibialMechaxis,vtkPolyData* m_TPL)
{
    qDebug()<<"updating tibial mech axis----";
    // ---- anterior----
    //Mech axis
    vtkSmartPointer<vtkPolyDataMapper> tibiaMechAxis_mapperAnterior =vtkSmartPointer<vtkPolyDataMapper>::New();
    tibiaMechAxis_mapperAnterior->SetInputData(m_tibialMechaxis);
    tibiaMechAxis_mapperAnterior->Update();

    tibiaMechAxis_ActorAnterior->SetMapper(tibiaMechAxis_mapperAnterior);
    tibiaMechAxis_ActorAnterior->GetProperty()->SetLineWidth(3);
    tibiaMechAxis_ActorAnterior->GetProperty()->SetColor(0.8,0,0);

    //TPL
    vtkSmartPointer<vtkPolyDataMapper> tibiaTPL_mapperAnterior =vtkSmartPointer<vtkPolyDataMapper>::New();
    tibiaTPL_mapperAnterior->SetInputData(m_TPL);
    tibiaTPL_mapperAnterior->Update();

    tibiaTPL_ActorAnterior->SetMapper(tibiaTPL_mapperAnterior);
    tibiaTPL_ActorAnterior->GetProperty()->SetLineWidth(3);
    tibiaTPL_ActorAnterior->GetProperty()->SetColor(0.8,0,0.8);


    // ---- distal----
    //Mech axis
    vtkSmartPointer<vtkPolyDataMapper> tibiaMechAxis_mapperDistal =vtkSmartPointer<vtkPolyDataMapper>::New();
    tibiaMechAxis_mapperDistal->SetInputData(m_tibialMechaxis);
    tibiaMechAxis_mapperDistal->Update();


    tibiaMechAxis1_ActorDistal->SetMapper(tibiaMechAxis_mapperDistal);
    tibiaMechAxis1_ActorDistal->GetProperty()->SetLineWidth(3);
    tibiaMechAxis1_ActorDistal->GetProperty()->SetColor(0.8,0,0);


    //TPL
    vtkSmartPointer<vtkPolyDataMapper> tibiaTPL_mapperDistal =vtkSmartPointer<vtkPolyDataMapper>::New();
    tibiaTPL_mapperDistal->SetInputData(m_TPL);
    tibiaTPL_mapperDistal->Update();

    tibiaTPL_ActorDistal->SetMapper(tibiaTPL_mapperDistal);
    tibiaTPL_ActorDistal->GetProperty()->SetLineWidth(3);
    tibiaTPL_ActorDistal->GetProperty()->SetColor(0.8,0,0.8);


    // ----lateral----
    //Mech axis
    vtkSmartPointer<vtkPolyDataMapper> tibiaMechAxis_mapperLateral =vtkSmartPointer<vtkPolyDataMapper>::New();
    tibiaMechAxis_mapperLateral->SetInputData(m_tibialMechaxis);
    tibiaMechAxis_mapperLateral->Update();


    tibiaMechAxis2_ActorLateral->SetMapper(tibiaMechAxis_mapperLateral);
    tibiaMechAxis2_ActorLateral->GetProperty()->SetLineWidth(3);
    tibiaMechAxis2_ActorLateral->GetProperty()->SetColor(0.8,0,0);

    //TPL
    vtkSmartPointer<vtkPolyDataMapper> tibiaTPL_mapperLateral =vtkSmartPointer<vtkPolyDataMapper>::New();
    tibiaTPL_mapperLateral->SetInputData(m_TPL);
    tibiaTPL_mapperLateral->Update();

    tibiaTPL_ActorLateral->SetMapper(tibiaTPL_mapperLateral);
    tibiaTPL_ActorLateral->GetProperty()->SetLineWidth(3);
    tibiaTPL_ActorLateral->GetProperty()->SetColor(0.8,0,0.8);



    //Render

    renderer_tka[3]->AddActor(tibiaMechAxis_ActorAnterior);
    renderer_tka[3]->AddActor(tibiaTPL_ActorAnterior);
    renderer_tka[3]->Render();
    renderWindow_tka[3]->Render();

    renderer_tka[4]->AddActor(tibiaMechAxis1_ActorDistal);
    renderer_tka[4]->AddActor(tibiaTPL_ActorDistal);
    renderer_tka[4]->Render();
    renderWindow_tka[4]->Render();

    renderer_tka[5]->AddActor(tibiaMechAxis2_ActorLateral);
    renderer_tka[5]->AddActor(tibiaTPL_ActorLateral);
    renderer_tka[5]->Render();
    renderWindow_tka[5]->Render();
}

void TKAThreeDView::UpdateAnatomicalPoint(bool clickval)
{
    if(AnotAxisDisFirstTime == false)
    {

        std::vector<vtkSmartPointer<vtkActor>> m_anoActors_Fem = m_ObjAxisDisplayView->DisplayAnotPoints_Slot();
        m_actorAnotationPointsFemur_Anterior = m_anoActors_Fem[0];
        m_actorAnotationPointsFemur_Distal = m_anoActors_Fem[1];
        m_actorAnotationPointsFemur_Lateral= m_anoActors_Fem[2];

        m_actorAnotationPointsTibia_Anterior = m_anoActors_Fem[3];
        m_actorAnotationPointsTibia_Distal = m_anoActors_Fem[4];
        m_actorAnotationPointsTibia_Lateral= m_anoActors_Fem[5];

        renderer_tka[0]->AddActor(m_actorAnotationPointsFemur_Anterior);
        renderer_tka[0]->Render();
        renderWindow_tka[0]->Render();

        renderer_tka[1]->AddActor(m_actorAnotationPointsFemur_Distal);
        renderer_tka[1]->Render();
        renderWindow_tka[1]->Render();

        renderer_tka[2]->AddActor(m_actorAnotationPointsFemur_Lateral);
        renderer_tka[2]->Render();
        renderWindow_tka[2]->Render();



        renderer_tka[3]->AddActor(m_actorAnotationPointsTibia_Anterior);
        renderer_tka[3]->Render();
        renderWindow_tka[3]->Render();

        renderer_tka[4]->AddActor(m_actorAnotationPointsTibia_Distal);
        renderer_tka[4]->Render();
        renderWindow_tka[4]->Render();

        renderer_tka[5]->AddActor(m_actorAnotationPointsTibia_Lateral);
        renderer_tka[5]->Render();
        renderWindow_tka[5]->Render();

        AnotAxisDisFirstTime = true;
    }
    if(clickval == true)
    {
        m_actorAnotationPointsFemur_Anterior->SetVisibility(true);
        m_actorAnotationPointsFemur_Distal->SetVisibility(true);
        m_actorAnotationPointsFemur_Lateral->SetVisibility(true);

        m_actorAnotationPointsTibia_Anterior->SetVisibility(true);
        m_actorAnotationPointsTibia_Distal->SetVisibility(true);
        m_actorAnotationPointsTibia_Lateral->SetVisibility(true);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }
    else
    {
        m_actorAnotationPointsFemur_Anterior->SetVisibility(false);
        m_actorAnotationPointsFemur_Distal->SetVisibility(false);
        m_actorAnotationPointsFemur_Lateral->SetVisibility(false);

        m_actorAnotationPointsTibia_Anterior->SetVisibility(false);
        m_actorAnotationPointsTibia_Distal->SetVisibility(false);
        m_actorAnotationPointsTibia_Lateral->SetVisibility(false);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }
}
//----For loading the implant----
void TKAThreeDView::LoadImplant(bool clicked)
{


    emit Enablespinboxes(clicked);

    if( clicked == true)
    {

        implantloadButtonClicked = true;

        pushButton_FAleftdown->setEnabled(true);
        pushButton_FAup->setEnabled(true);
        pushButton_FArightdown->setEnabled(true);
        pushButton_FAleft->setEnabled(true);
        pushButton_FAdown->setEnabled(true);
        pushButton_FAright->setEnabled(true);

        pushButton_FDleftdown->setEnabled(true);
        pushButton_FDup->setEnabled(true);
        pushButton_FDrightdown->setEnabled(true);
        pushButton_FDleft->setEnabled(true);
        pushButton_FDdown->setEnabled(true);
        pushButton_FDright->setEnabled(true);

        pushButton_FLleftdown->setEnabled(true);
        pushButton_FLup->setEnabled(true);
        pushButton_FLrightdown->setEnabled(true);
        pushButton_FLleft->setEnabled(true);
        pushButton_FLdown->setEnabled(true);
        pushButton_FLright->setEnabled(true);


        //Tibia
        pushButton_TAleftdown->setEnabled(true);
        pushButton_TAup->setEnabled(true);
        pushButton_TArightdown->setEnabled(true);
        pushButton_TAleft->setEnabled(true);
        pushButton_TAdown->setEnabled(true);
        pushButton_TAright->setEnabled(true);

        pushButton_TDleftdown->setEnabled(true);
        pushButton_TDup->setEnabled(true);
        pushButton_TDrightdown->setEnabled(true);
        pushButton_TDleft->setEnabled(true);
        pushButton_TDdown->setEnabled(true);
        pushButton_TDright->setEnabled(true);

        pushButton_TLleftdown->setEnabled(true);
        pushButton_TLup->setEnabled(true);
        pushButton_TLrightdown->setEnabled(true);
        pushButton_TLleft->setEnabled(true);
        pushButton_TLdown->setEnabled(true);
        pushButton_TLright->setEnabled(true);

    }
    else
    {
        implantloadButtonClicked = false;

        pushButton_FAleftdown->setEnabled(false);
        pushButton_FAup->setEnabled(false);
        pushButton_FArightdown->setEnabled(false);
        pushButton_FAleft->setEnabled(false);
        pushButton_FAdown->setEnabled(false);
        pushButton_FAright->setEnabled(false);

        pushButton_FDleftdown->setEnabled(false);
        pushButton_FDup->setEnabled(false);
        pushButton_FDrightdown->setEnabled(false);
        pushButton_FDleft->setEnabled(false);
        pushButton_FDdown->setEnabled(false);
        pushButton_FDright->setEnabled(false);

        pushButton_FLleftdown->setEnabled(false);
        pushButton_FLup->setEnabled(false);
        pushButton_FLrightdown->setEnabled(false);
        pushButton_FLleft->setEnabled(false);
        pushButton_FLdown->setEnabled(false);
        pushButton_FLright->setEnabled(false);

        //Tibia
        pushButton_TAleftdown->setEnabled(false);
        pushButton_TAup->setEnabled(false);
        pushButton_TArightdown->setEnabled(false);
        pushButton_TAleft->setEnabled(false);
        pushButton_TAdown->setEnabled(false);
        pushButton_TAright->setEnabled(false);

        pushButton_TDleftdown->setEnabled(false);
        pushButton_TDup->setEnabled(false);
        pushButton_TDrightdown->setEnabled(false);
        pushButton_TDleft->setEnabled(false);
        pushButton_TDdown->setEnabled(false);
        pushButton_TDright->setEnabled(false);

        pushButton_TLleftdown->setEnabled(false);
        pushButton_TLup->setEnabled(false);
        pushButton_TLrightdown->setEnabled(false);
        pushButton_TLleft->setEnabled(false);
        pushButton_TLdown->setEnabled(false);
        pushButton_TLright->setEnabled(false);
    }

    if(ImplantLoadingFirstTime == false)
    {
        m_ObjAxisDisplayView->m_objKinematicsClass->GetPointsFRomAnnotationmodule();//added on 21-10-24
        std::vector<vtkSmartPointer<vtkActor>> m_Implants = m_ObjImplantLoad->LoadedImplant(m_ObjAxisDisplayView->m_objKinematicsClass->m_FemoralMechAxisP2,
                                                                                            m_ObjAxisDisplayView->m_objKinematicsClass->m_TibialMechanicalAxis_P1); //femoral knee centre is passed where the implant should be placed
        //qDebug()<<"TKAThreeDView::LoadImplant";
        m_femoral_stlcomponentactor_Anter = m_Implants[0];
        m_femoral_stlcomponentactor_Dist = m_Implants[1];
        m_femoral_stlcomponentactor_Later = m_Implants[2];
        m_tibial_stlcomponentactor_Anter = m_Implants[3];
        m_tibial_stlcomponentactor_Dist= m_Implants[4];
        m_tibial_stlcomponentactor_Later= m_Implants[5];
        m_tibial_stlspacerComponentactor_Anter = m_Implants[6];
        m_tibial_stlspacerComponentactor_Dist = m_Implants[7];
        m_tibial_stlspacerComponentactor_Later = m_Implants[8];


        //m_femoral_stlcomponentactor_Anter->GetProperty()->SetOpacity(0.6);
        renderer_tka[0]->AddActor(m_femoral_stlcomponentactor_Anter);
        renderWindow_tka[0]->Render();

        renderer_tka[1]->AddActor(m_femoral_stlcomponentactor_Dist);
        renderWindow_tka[1]->Render();

        renderer_tka[2]->AddActor(m_femoral_stlcomponentactor_Later);
        renderWindow_tka[2]->Render();

        renderer_tka[3]->AddActor(m_tibial_stlcomponentactor_Anter);
        renderer_tka[3]->AddActor(m_tibial_stlspacerComponentactor_Anter);
        renderWindow_tka[3]->Render();

        renderer_tka[4]->AddActor(m_tibial_stlcomponentactor_Dist);
        renderer_tka[4]->AddActor(m_tibial_stlspacerComponentactor_Dist);
        renderWindow_tka[4]->Render();

        renderer_tka[5]->AddActor(m_tibial_stlcomponentactor_Later);
        renderer_tka[5]->AddActor(m_tibial_stlspacerComponentactor_Later);
        renderWindow_tka[5]->Render();

        ImplantLoadingFirstTime = true;
    }
    if(clicked == true)
    {
        m_femoral_stlcomponentactor_Anter->SetVisibility(true);
        m_femoral_stlcomponentactor_Dist->SetVisibility(true);
        m_femoral_stlcomponentactor_Later->SetVisibility(true);
        m_tibial_stlcomponentactor_Anter->SetVisibility(true);
        m_tibial_stlcomponentactor_Dist->SetVisibility(true);
        m_tibial_stlcomponentactor_Later->SetVisibility(true);
        m_tibial_stlspacerComponentactor_Anter->SetVisibility(true);
        m_tibial_stlspacerComponentactor_Dist->SetVisibility(true);
        m_tibial_stlspacerComponentactor_Later->SetVisibility(true);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();


    }
    else
    {
        m_femoral_stlcomponentactor_Anter->SetVisibility(false);
        m_femoral_stlcomponentactor_Dist->SetVisibility(false);
        m_femoral_stlcomponentactor_Later->SetVisibility(false);
        m_tibial_stlcomponentactor_Anter->SetVisibility(false);
        m_tibial_stlcomponentactor_Dist->SetVisibility(false);
        m_tibial_stlcomponentactor_Later->SetVisibility(false);
        m_tibial_stlspacerComponentactor_Anter->SetVisibility(false);
        m_tibial_stlspacerComponentactor_Dist->SetVisibility(false);
        m_tibial_stlspacerComponentactor_Later->SetVisibility(false);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }
}
//Slot for implant translations Femoral implant
void TKAThreeDView::TranslationsofImplantFemur(bool clickedv0)
{
    // Get the button that sent the signal
    QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
    QString id = button_whichbuttonpressed->objectName();  // Get the button's ID (object name)


    //varus/ valgus rotation by 0.5 degrees
    if(id == "pushButton_FArightdown")
    {
        FemAnterVarVal = FemAnterVarVal + 0.5;
    }
    else if(id == "pushButton_FAleftdown")
    {
        FemAnterVarVal = FemAnterVarVal - 0.5;
    }
    //internal/ external rotation by 0.5 degrees
    else if( id == "pushButton_FDrightdown")
    {
        FemDistInterExter = FemDistInterExter + 0.5;
    }
    else if(id =="pushButton_FDleftdown")
    {
        FemDistInterExter = FemDistInterExter - 0.5;
    }
    //Flexion extension rotation by 0.5 degrees
    else if( id == "pushButton_FLrightdown")
    {
        FemLatFlexExt = FemLatFlexExt + 0.5;
    }
    else if(id =="pushButton_FLleftdown")
    {
        FemLatFlexExt = FemLatFlexExt - 0.5;
    }


    label_Fem_VarValgValue->setText(QString::number(FemAnterVarVal,'f',1)+ "°");
    label_FDIntExtValue->setText(QString::number(FemDistInterExter,'f',1)+ "°");
    label_FL_FlexExtenValue->setText(QString::number(FemLatFlexExt,'f',1)+ "°");

    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsFA(id,m_femoral_stlcomponentactor_Anter);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsFD(id,m_femoral_stlcomponentactor_Dist);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsFL(id,m_femoral_stlcomponentactor_Later);
    renderWindow_tka[0]->Render();
    renderWindow_tka[1]->Render();
    renderWindow_tka[2]->Render();
}

void TKAThreeDView::TranslationsofImplantTibia(bool)
{
    // Get the button that sent the signal
    QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
    QString id = button_whichbuttonpressed->objectName();  // Get the button's ID (object name)


    //varus/ valgus rotation by 0.5 degrees
    if(id == "pushButton_TArightdown")
    {
        TibAnterVarVal = TibAnterVarVal + 0.5;
    }
    else if(id == "pushButton_TAleftdown")
    {
        TibAnterVarVal = TibAnterVarVal - 0.5;
    }
    //internal/ external rotation by 0.5 degrees
    else if( id == "pushButton_TDrightdown")
    {
        TibDistInterExter = TibDistInterExter + 0.5;
    }
    else if(id =="pushButton_TDleftdown")
    {
        TibDistInterExter = TibDistInterExter - 0.5;
    }
    //Flexion extension rotation by 0.5 degrees
    else if( id == "pushButton_TLrightdown")
    {
        TibLatFlexExt = TibLatFlexExt + 0.5;
    }
    else if(id =="pushButton_TLleftdown")
    {
        TibLatFlexExt =TibLatFlexExt - 0.5;
    }


    label_Tib_VarValgusValue->setText(QString::number(TibAnterVarVal,'f',1)+ "°");
    label_Tib_InterExterValue->setText(QString::number(TibDistInterExter,'f',1)+ "°");
    label_TibPSlopeValue->setText(QString::number(TibLatFlexExt,'f',1)+ "°");

    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsTA(id,m_tibial_stlcomponentactor_Anter);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsTD(id,m_tibial_stlcomponentactor_Dist);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsTL(id,m_tibial_stlcomponentactor_Later);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsTSpacerA(id,m_tibial_stlspacerComponentactor_Anter);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsTSpacerD(id,m_tibial_stlspacerComponentactor_Dist);
    m_ObjImplantTransformations->SlotOfFemurimplantTransformationsTSpacerL(id,m_tibial_stlspacerComponentactor_Later);

    renderWindow_tka[3]->Render();
    renderWindow_tka[4]->Render();
    renderWindow_tka[5]->Render();
}
//Size adjustment of femur implant component
void TKAThreeDView::FemurComponentSizeAdjustment()
{
    //qDebug()<<"valuechanged="<<valuechanged;
    if(implantloadButtonClicked == true)
    {
        // Get the button that sent the signal
        QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
        QString id = button_whichbuttonpressed->objectName();
        //qDebug()<<"which button clicked = "<<id;

        vtkSmartPointer<vtkSTLReader>m_mappersinput =  m_ObjImplantLoad->LoadDifferentSizedImplant_Femur(id);

        m_femoral_stlcomponentactor_Anter->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        m_femoral_stlcomponentactor_Dist->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        m_femoral_stlcomponentactor_Later->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();

        //---------------------------for scaling old code---------------------------------
        //        SizeTransform_Femur->Identity();//Resets all transformations
        //        SizeTransform_Femur->Scale(valuechanged,valuechanged,valuechanged);// Scale factor
        //        SizeTransform_Femur->Translate(0, 0, 0);// Move the actor back to its original position
        //        SizeTransform_Femur->Update();

        //        if(implantsizefemurFirstTime == false)
        //        {
        //            SizeTransformTransformFilter_Femur->RemoveAllObservers();
        //            SizeTransformTransformFilter_Femur->SetInputData(m_femoral_stlcomponentactor_Anter->GetMapper()->GetInput());
        //            SizeTransformTransformFilter_Femur->SetTransform(SizeTransform_Femur);
        //            SizeTransformTransformFilter_Femur->Update();

        //            m_femoral_stlcomponentactor_Anter->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Femur->GetOutputPort());
        //            m_femoral_stlcomponentactor_Anter->GetMapper()->Update();

        //            m_femoral_stlcomponentactor_Dist->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Femur->GetOutputPort());
        //            m_femoral_stlcomponentactor_Dist->GetMapper()->Update();

        //            m_femoral_stlcomponentactor_Later->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Femur->GetOutputPort());
        //            m_femoral_stlcomponentactor_Later->GetMapper()->Update();


        //            implantsizefemurFirstTime = true;
        //        }
        //-----------------------------------------------------------------------------



    }
}
//Size adjustment of tibia implant component
void TKAThreeDView::TibiaComponentSizeAdjustment()
{

    if(implantloadButtonClicked == true)
    {
        QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
        QString id = button_whichbuttonpressed->objectName();

        vtkSmartPointer<vtkSTLReader>m_mappersinput =  m_ObjImplantLoad->LoadDifferentSizedImplant_Tibia(id);

        m_tibial_stlcomponentactor_Anter->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        m_tibial_stlcomponentactor_Dist->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        m_tibial_stlcomponentactor_Later->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());

        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();

        //        SizeTransform_Tibia->Identity();//Resets all transformations
        //        SizeTransform_Tibia->Scale(valuechanged,valuechanged,valuechanged);// Scale factor
        //        SizeTransform_Tibia->Translate(0, 0, 0);// Move the actor back to its original position
        //        SizeTransform_Tibia->Update();

        //        if(implantsizetibiaFirstTime == false)
        //        {
        //            SizeTransformTransformFilter_Tibia->RemoveAllObservers();
        //            SizeTransformTransformFilter_Tibia->SetInputData(m_tibial_stlcomponentactor_Anter->GetMapper()->GetInput());
        //            SizeTransformTransformFilter_Tibia->SetTransform(SizeTransform_Tibia);
        //            SizeTransformTransformFilter_Tibia->Update();

        //            m_tibial_stlcomponentactor_Anter->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Tibia->GetOutputPort());
        //            m_tibial_stlcomponentactor_Anter->GetMapper()->Update();

        //            m_tibial_stlcomponentactor_Dist->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Tibia->GetOutputPort());
        //            m_tibial_stlcomponentactor_Dist->GetMapper()->Update();

        //            m_tibial_stlcomponentactor_Later->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Tibia->GetOutputPort());
        //            m_tibial_stlcomponentactor_Later->GetMapper()->Update();

        //            implantsizetibiaFirstTime = true;
        //        }
        //        m_tibial_stlcomponentactor_Anter->Modified();
        //        m_tibial_stlcomponentactor_Dist->Modified();
        //        m_tibial_stlcomponentactor_Later->Modified();

    }
}
//Size adjustment of spacer implant component
void TKAThreeDView::SpacerComponentSizeAdjustment()
{
    if(implantloadButtonClicked == true)
    {
        QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
        QString id = button_whichbuttonpressed->objectName();

        vtkSmartPointer<vtkSTLReader>m_mappersinput =  m_ObjImplantLoad->LoadDifferentSizedImplant_TibSpacer(id);

        m_tibial_stlspacerComponentactor_Anter->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        m_tibial_stlspacerComponentactor_Dist->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        m_tibial_stlspacerComponentactor_Later->GetMapper()->SetInputConnection(m_mappersinput->GetOutputPort());
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
        //        SizeTransform_Spacer->Identity();//Resets all transformations
        //        SizeTransform_Spacer->Scale(valuechanged,valuechanged,valuechanged);// Scale factor
        //        SizeTransform_Spacer->Translate(0, 0, 0);// Move the actor back to its original position
        //        SizeTransform_Spacer->Update();

        //        if(implantsizespacerFirstTime == false)
        //        {
        //            SizeTransformTransformFilter_Spacer->RemoveAllObservers();
        //            SizeTransformTransformFilter_Spacer->SetInputData(m_tibial_stlspacerComponentactor_Anter->GetMapper()->GetInput());
        //            SizeTransformTransformFilter_Spacer->SetTransform(SizeTransform_Spacer);
        //            SizeTransformTransformFilter_Spacer->Update();

        //            m_tibial_stlspacerComponentactor_Anter->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Spacer->GetOutputPort());
        //            m_tibial_stlspacerComponentactor_Anter->GetMapper()->Update();

        //            m_tibial_stlspacerComponentactor_Dist->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Spacer->GetOutputPort());
        //            m_tibial_stlspacerComponentactor_Dist->GetMapper()->Update();

        //            m_tibial_stlspacerComponentactor_Later->GetMapper()->SetInputConnection(SizeTransformTransformFilter_Spacer->GetOutputPort());
        //            m_tibial_stlspacerComponentactor_Later->GetMapper()->Update();

        //            implantsizespacerFirstTime = true;
        //        }
        //        m_tibial_stlspacerComponentactor_Anter->Modified();
        //        m_tibial_stlspacerComponentactor_Dist->Modified();
        //        m_tibial_stlspacerComponentactor_Later->Modified();

    }
}
//--added on 19-9-2024-----
void TKAThreeDView::AdjustBoneOpacity(bool value)
{
    //qDebug()<<"bone opac"<<value;
    if(value == true)
    {
        actor_3dtka[0]->GetProperty()->SetOpacity(0.5);
        actor_3dtka[1]->GetProperty()->SetOpacity(0.5);
        actor_3dtka[2]->GetProperty()->SetOpacity(0.5);
        actor_3dtka[3]->GetProperty()->SetOpacity(0.5);
        actor_3dtka[4]->GetProperty()->SetOpacity(0.5);
        actor_3dtka[5]->GetProperty()->SetOpacity(0.5);

        femur_cutActor_Anterior ->GetProperty()->SetOpacity(0.5);
        femur_cutActor_Distal ->GetProperty()->SetOpacity(0.5);
        femur_cutActor_Lateral ->GetProperty()->SetOpacity(0.5);
        tibia_cutActor_Anterior ->GetProperty()->SetOpacity(0.5);
        tibia_cutActor_Distal ->GetProperty()->SetOpacity(0.5);
        tibia_cutActor_Lateral ->GetProperty()->SetOpacity(0.5);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }
    else
    {
        actor_3dtka[0]->GetProperty()->SetOpacity(1.0);
        actor_3dtka[1]->GetProperty()->SetOpacity(1.0);
        actor_3dtka[2]->GetProperty()->SetOpacity(1.0);
        actor_3dtka[3]->GetProperty()->SetOpacity(1.0);
        actor_3dtka[4]->GetProperty()->SetOpacity(1.0);
        actor_3dtka[5]->GetProperty()->SetOpacity(1.0);

        femur_cutActor_Anterior ->GetProperty()->SetOpacity(1.0);
        femur_cutActor_Distal ->GetProperty()->SetOpacity(1.0);
        femur_cutActor_Lateral ->GetProperty()->SetOpacity(1.0);
        tibia_cutActor_Anterior ->GetProperty()->SetOpacity(1.0);
        tibia_cutActor_Distal ->GetProperty()->SetOpacity(1.0);
        tibia_cutActor_Lateral ->GetProperty()->SetOpacity(1.0);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }


}

void TKAThreeDView::AdjustImplantOpacity(bool value)
{
    //qDebug()<<"impl opac";

    if(value == true)
    {
        m_femoral_stlcomponentactor_Anter->GetProperty()->SetOpacity(0.7);
        m_femoral_stlcomponentactor_Dist->GetProperty()->SetOpacity(0.7);
        m_femoral_stlcomponentactor_Later->GetProperty()->SetOpacity(0.7);

        m_tibial_stlcomponentactor_Anter->GetProperty()->SetOpacity(0.7);
        m_tibial_stlcomponentactor_Dist->GetProperty()->SetOpacity(0.7);
        m_tibial_stlcomponentactor_Later->GetProperty()->SetOpacity(0.7);
        m_tibial_stlspacerComponentactor_Anter->GetProperty()->SetOpacity(0.7);
        m_tibial_stlspacerComponentactor_Dist->GetProperty()->SetOpacity(0.7);
        m_tibial_stlspacerComponentactor_Later->GetProperty()->SetOpacity(0.7);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }
    else
    {
        m_femoral_stlcomponentactor_Anter->GetProperty()->SetOpacity(1.0);
        m_femoral_stlcomponentactor_Dist->GetProperty()->SetOpacity(1.0);
        m_femoral_stlcomponentactor_Later->GetProperty()->SetOpacity(1.0);

        m_tibial_stlcomponentactor_Anter->GetProperty()->SetOpacity(1.0);
        m_tibial_stlcomponentactor_Dist->GetProperty()->SetOpacity(1.0);
        m_tibial_stlcomponentactor_Later->GetProperty()->SetOpacity(1.0);
        m_tibial_stlspacerComponentactor_Anter->GetProperty()->SetOpacity(1.0);
        m_tibial_stlspacerComponentactor_Dist->GetProperty()->SetOpacity(1.0);
        m_tibial_stlspacerComponentactor_Later->GetProperty()->SetOpacity(1.0);

        renderWindow_tka[0]->Render();
        renderWindow_tka[1]->Render();
        renderWindow_tka[2]->Render();
        renderWindow_tka[3]->Render();
        renderWindow_tka[4]->Render();
        renderWindow_tka[5]->Render();
    }


}
void TKAThreeDView::SlotForAnteriorFemButtonsVisibilityTrue()
{
    pushButton_FArightdown->setHidden(false);
    pushButton_FAleftdown->setHidden(false);
    pushButton_FAup->setHidden(false);
    pushButton_FArightdown->setHidden(false);
    pushButton_FAleft->setHidden(false);
    pushButton_FAdown->setHidden(false);
    pushButton_FAright->setHidden(false);
    //Toggling of label and button on hover
    m_qvbcellayout->removeItem(m_qhbvaruslbl);
    m_qvbcellayout->addWidget(pushButton_FAup,1,Qt::AlignCenter);
    m_qvbcellayout->addLayout(m_qhbvaruslbl);
    m_qvbcellayout->update();


}

void TKAThreeDView::SlotForAnteriorFemButtonsVisibilityFalse()
{
    pushButton_FArightdown->setHidden(true);
    pushButton_FAleftdown->setHidden(true);
    pushButton_FAup->setHidden(true);
    pushButton_FArightdown->setHidden(true);
    pushButton_FAleft->setHidden(true);
    pushButton_FAdown->setHidden(true);
    pushButton_FAright->setHidden(true);
    //Toggling of label and button on hover
    m_qvbcellayout->removeWidget(pushButton_FAup);
    m_qvbcellayout->removeItem(m_qhbvaruslbl);
    m_qvbcellayout->addLayout(m_qhbvaruslbl);
    m_qvbcellayout->addWidget(pushButton_FAup);
    m_qvbcellayout->update();
}

void TKAThreeDView::SlotForDistalFemButtonsVisibilityTrue()
{
    pushButton_FDleftdown->setHidden(false);
    pushButton_FDup->setHidden(false);
    pushButton_FDrightdown->setHidden(false);
    pushButton_FDleft->setHidden(false);
    pushButton_FDdown->setHidden(false);
    pushButton_FDright->setHidden(false);
    //Toggling of label and button on hover
    m_qvbFDlayout->removeItem(m_qhbFDIElayout);
    m_qvbFDlayout->addWidget(pushButton_FDup,1,Qt::AlignCenter);
    m_qvbFDlayout->addLayout(m_qhbFDIElayout);
    m_qvbFDlayout->update();

}

void TKAThreeDView::SlotForDistalFemButtonsVisibilityFalse()
{
    pushButton_FDleftdown->setHidden(true);
    pushButton_FDup->setHidden(true);
    pushButton_FDrightdown->setHidden(true);
    pushButton_FDleft->setHidden(true);
    pushButton_FDdown->setHidden(true);
    pushButton_FDright->setHidden(true);
    //Toggling of label and button on hover
    m_qvbFDlayout->removeWidget(pushButton_FDup);
    m_qvbFDlayout->removeItem(m_qhbFDIElayout);
    m_qvbFDlayout->addLayout(m_qhbFDIElayout);
    m_qvbFDlayout->addWidget(pushButton_FDup);
    m_qvbFDlayout->update();
}

void TKAThreeDView::SlotForLateralFemButtonsVisibilityTrue()
{
    pushButton_FLleftdown->setHidden(false);
    pushButton_FLup->setHidden(false);
    pushButton_FLrightdown->setHidden(false);
    pushButton_FLleft->setHidden(false);
    pushButton_FLdown->setHidden(false);
    pushButton_FLright->setHidden(false);
    //Toggling of label and button on hover
    m_qvbFlexextbtn->removeItem(m_qhbflExt);
    m_qvbFlexextbtn->addWidget(pushButton_FLup,1,Qt::AlignCenter);
    m_qvbFlexextbtn->addLayout(m_qhbflExt);
    m_qvbFlexextbtn->update();
}

void TKAThreeDView::SlotForLateralFemButtonsVisibilityFalse()
{
    pushButton_FLleftdown->setHidden(true);
    pushButton_FLup->setHidden(true);
    pushButton_FLrightdown->setHidden(true);
    pushButton_FLleft->setHidden(true);
    pushButton_FLdown->setHidden(true);
    pushButton_FLright->setHidden(true);
    //Toggling of label and button on hover
    m_qvbFlexextbtn->removeWidget(pushButton_FLup);
    m_qvbFlexextbtn->removeItem(m_qhbflExt);
    m_qvbFlexextbtn->addLayout(m_qhbflExt);
    m_qvbFlexextbtn->addWidget(pushButton_FLup);
    m_qvbFlexextbtn->update();
}

void TKAThreeDView::SlotForAnteriorTibButtonsVisibilityTrue()
{
    pushButton_TAleftdown->setHidden(false);
    pushButton_TAup->setHidden(false);
    pushButton_TArightdown->setHidden(false);
    pushButton_TAleft->setHidden(false);
    pushButton_TAdown->setHidden(false);
    pushButton_TAright->setHidden(false);
    //Toggling of label and button on hover
    m_qvbtiblayout->removeItem(m_qhbvaruslbltib);
    m_qvbtiblayout->addLayout(m_qhbvaruslbltib);
    m_qvbtiblayout->addWidget(pushButton_TAdown,1,Qt::AlignCenter);

    m_qvbtiblayout->update();
}

void TKAThreeDView::SlotForAnteriorTibButtonsVisibilityFalse()
{
    pushButton_TAleftdown->setHidden(true);
    pushButton_TAup->setHidden(true);
    pushButton_TArightdown->setHidden(true);
    pushButton_TAleft->setHidden(true);
    pushButton_TAdown->setHidden(true);
    pushButton_TAright->setHidden(true);
    //Toggling of label and button on hover
    m_qvbtiblayout->removeWidget(pushButton_TAdown);
    m_qvbtiblayout->removeItem(m_qhbvaruslbltib);
    m_qvbtiblayout->addWidget(pushButton_TAdown);
    m_qvbtiblayout->addLayout(m_qhbvaruslbltib);
    m_qvbtiblayout->update();
}

void TKAThreeDView::SlotForDistalTibButtonsVisibilityTrue()
{
    pushButton_TDleftdown->setHidden(false);
    pushButton_TDup->setHidden(false);
    pushButton_TDrightdown->setHidden(false);
    pushButton_TDleft->setHidden(false);
    pushButton_TDdown->setHidden(false);
    pushButton_TDright->setHidden(false);
    //Toggling of label and button on hover
    m_qvbtibmid->removeItem(m_qhblbltibmid);
    m_qvbtibmid->addLayout(m_qhblbltibmid);
    m_qvbtibmid->addWidget(pushButton_TDdown,1,Qt::AlignCenter);
    m_qvbtibmid->update();

}

void TKAThreeDView::SlotForDistalTibButtonsVisibilityFalse()
{
    pushButton_TDleftdown->setHidden(true);
    pushButton_TDup->setHidden(true);
    pushButton_TDrightdown->setHidden(true);
    pushButton_TDleft->setHidden(true);
    pushButton_TDdown->setHidden(true);
    pushButton_TDright->setHidden(true);
    //Toggling of label and button on hover
    m_qvbtibmid->removeWidget(pushButton_TDdown);
    m_qvbtibmid->removeItem(m_qhblbltibmid);
    m_qvbtibmid->addWidget(pushButton_TDdown);
    m_qvbtibmid->addLayout(m_qhblbltibmid);

    m_qvbtibmid->update();
}

void TKAThreeDView::SlotForLateralTibButtonsVisibilityTrue()
{
    pushButton_TLleftdown->setHidden(false);
    pushButton_TLup->setHidden(false);
    pushButton_TLrightdown->setHidden(false);
    pushButton_TLleft->setHidden(false);
    pushButton_TLdown->setHidden(false);
    pushButton_TLright->setHidden(false);
    //Toggling of label and button on hover
    m_qvblattiblay->removeItem(m_qhbtibSlop);
    m_qvblattiblay->addLayout(m_qhbtibSlop);
    m_qvblattiblay->addWidget(pushButton_TLdown,1,Qt::AlignCenter);
    m_qvblattiblay->update();

}

void TKAThreeDView::SlotForLateralTibButtonsVisibilityFalse()
{
    pushButton_TLleftdown->setHidden(true);
    pushButton_TLup->setHidden(true);
    pushButton_TLrightdown->setHidden(true);
    pushButton_TLleft->setHidden(true);
    pushButton_TLdown->setHidden(true);
    pushButton_TLright->setHidden(true);
    //Toggling of label and button on hover
    m_qvblattiblay->removeWidget(pushButton_TLdown);
    m_qvblattiblay->removeItem(m_qhbtibSlop);
    m_qvblattiblay->addWidget(pushButton_TLdown);
    m_qvblattiblay->addLayout(m_qhbtibSlop);

    m_qvblattiblay->update();
}

void TKAThreeDView::UpdateAxisDisplay_Femur(vtkPolyData * femoralMechline ,vtkPolyData* m_TEA, vtkPolyData* m_PCA,vtkPolyData* FemoralCompAxis)
{

    //----Anterior----
    //Mech axis
    vtkSmartPointer<vtkPolyDataMapper> femurMechAxis_mapperAnterior =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurMechAxis_mapperAnterior->SetInputData(femoralMechline);
    femurMechAxis_mapperAnterior->Update();

    femurMechAxis_ActorAnterior->SetMapper(femurMechAxis_mapperAnterior);
    femurMechAxis_ActorAnterior->GetProperty()->SetLineWidth(3);
    femurMechAxis_ActorAnterior->GetProperty()->SetColor(0.8,0,0);

    //TEA
    vtkSmartPointer<vtkPolyDataMapper> femurTEA_mapperAnterior =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurTEA_mapperAnterior->SetInputData(m_TEA);
    femurTEA_mapperAnterior->Update();

    femurTEA_ActorAnterior->SetMapper(femurTEA_mapperAnterior);
    femurTEA_ActorAnterior->GetProperty()->SetLineWidth(3);
    femurTEA_ActorAnterior->GetProperty()->SetColor(0.8,0,0.8);

    //PCA
    vtkSmartPointer<vtkPolyDataMapper> femurPCA_mapperAnterior =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurPCA_mapperAnterior->SetInputData(m_PCA);
    femurPCA_mapperAnterior->Update();

    femurPCA_ActorAnterior->SetMapper(femurPCA_mapperAnterior);
    femurPCA_ActorAnterior->GetProperty()->SetLineWidth(3);
    femurPCA_ActorAnterior->GetProperty()->SetColor(0.8,0,0.8);

    //Femoral component axis
    vtkSmartPointer<vtkPolyDataMapper> femurFemoralCompAxis_mapperAnterior =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurFemoralCompAxis_mapperAnterior->SetInputData(FemoralCompAxis);
    femurFemoralCompAxis_mapperAnterior->Update();

    femurFemCompAx_ActorAnterior->SetMapper(femurFemoralCompAxis_mapperAnterior);
    femurFemCompAx_ActorAnterior->GetProperty()->SetLineWidth(3);
    femurFemCompAx_ActorAnterior->GetProperty()->SetColor(0,0.8,0);


    //---- Distal----
    //Mech axis
    vtkSmartPointer<vtkPolyDataMapper> femurMechAxis_mapperDistal =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurMechAxis_mapperDistal->SetInputData(femoralMechline);
    femurMechAxis_mapperDistal->Update();


    femurMechAxis1_ActorDistal->SetMapper(femurMechAxis_mapperDistal);
    femurMechAxis1_ActorDistal->GetProperty()->SetLineWidth(3);
    femurMechAxis1_ActorDistal->GetProperty()->SetColor(0.8,0,0);

    //TEA
    vtkSmartPointer<vtkPolyDataMapper> femurTEA_mapperDistal =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurTEA_mapperDistal->SetInputData(m_TEA);
    femurTEA_mapperDistal->Update();

    femurTEA_ActorDistal->SetMapper(femurTEA_mapperDistal);
    femurTEA_ActorDistal->GetProperty()->SetLineWidth(3);
    femurTEA_ActorDistal->GetProperty()->SetColor(0.8,0,0.8);

    //PCA
    vtkSmartPointer<vtkPolyDataMapper> femurPCA_mapperDistal =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurPCA_mapperDistal->SetInputData(m_PCA);
    femurPCA_mapperDistal->Update();

    femurPCA_ActorDistal->SetMapper(femurPCA_mapperDistal);
    femurPCA_ActorDistal->GetProperty()->SetLineWidth(3);
    femurPCA_ActorDistal->GetProperty()->SetColor(0.8,0,0.8);

    //Femoral component axis
    vtkSmartPointer<vtkPolyDataMapper> femurFemoralCompAxis_mapperDistal =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurFemoralCompAxis_mapperDistal->SetInputData(FemoralCompAxis);
    femurFemoralCompAxis_mapperDistal->Update();

    femurFemCompAx_ActorDistal->SetMapper(femurFemoralCompAxis_mapperDistal);
    femurFemCompAx_ActorDistal->GetProperty()->SetLineWidth(3);
    femurFemCompAx_ActorDistal->GetProperty()->SetColor(0,0.8,0);

    //----Lateral----
    //Mech axis
    vtkSmartPointer<vtkPolyDataMapper> femurMechAxis_mapperLateral =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurMechAxis_mapperLateral->SetInputData(femoralMechline);
    femurMechAxis_mapperLateral->Update();


    femurMechAxis2_ActorLateral->SetMapper(femurMechAxis_mapperLateral);
    femurMechAxis2_ActorLateral->GetProperty()->SetLineWidth(3);
    femurMechAxis2_ActorLateral->GetProperty()->SetColor(0.8,0,0);

    //TEA
    vtkSmartPointer<vtkPolyDataMapper> femurTEA_mapperLateral =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurTEA_mapperLateral->SetInputData(m_TEA);
    femurTEA_mapperLateral->Update();

    femurTEA_ActorLateral->SetMapper(femurTEA_mapperLateral);
    femurTEA_ActorLateral->GetProperty()->SetLineWidth(3);
    femurTEA_ActorLateral->GetProperty()->SetColor(0.8,0,0.8);

    //PCA
    vtkSmartPointer<vtkPolyDataMapper> femurPCA_mapperLateral =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurPCA_mapperLateral->SetInputData(m_PCA);
    femurPCA_mapperLateral->Update();

    femurPCA_ActorLateral->SetMapper(femurPCA_mapperLateral);
    femurPCA_ActorLateral->GetProperty()->SetLineWidth(3);
    femurPCA_ActorLateral->GetProperty()->SetColor(0.8,0,0.8);

    //Femoral component axis
    vtkSmartPointer<vtkPolyDataMapper> femurFemoralCompAxis_mapperLateral =vtkSmartPointer<vtkPolyDataMapper>::New();
    femurFemoralCompAxis_mapperLateral->SetInputData(FemoralCompAxis);
    femurFemoralCompAxis_mapperLateral->Update();

    femurFemCompAx_ActorLateral->SetMapper(femurFemoralCompAxis_mapperLateral);
    femurFemCompAx_ActorLateral->GetProperty()->SetLineWidth(3);
    femurFemCompAx_ActorLateral->GetProperty()->SetColor(0,0.8,0);



    //----Render----
    renderer_tka[0]->AddActor(femurMechAxis_ActorAnterior);
    renderer_tka[0]->AddActor(femurTEA_ActorAnterior);
    renderer_tka[0]->AddActor(femurPCA_ActorAnterior);
    renderer_tka[0]->AddActor(femurFemCompAx_ActorAnterior);
    renderer_tka[0]->Render();
    renderWindow_tka[0]->Render();

    renderer_tka[1]->AddActor(femurMechAxis1_ActorDistal);
    renderer_tka[1]->AddActor(femurTEA_ActorDistal);
    renderer_tka[1]->AddActor(femurPCA_ActorDistal);
    renderer_tka[1]->AddActor(femurFemCompAx_ActorDistal);
    renderer_tka[1]->Render();
    renderWindow_tka[1]->Render();

    renderer_tka[2]->AddActor(femurMechAxis2_ActorLateral);
    renderer_tka[2]->AddActor(femurTEA_ActorLateral);
    renderer_tka[2]->AddActor(femurPCA_ActorLateral);
    renderer_tka[2]->AddActor(femurFemCompAx_ActorLateral);
    renderer_tka[2]->Render();
    renderWindow_tka[2]->Render();
}
//void TKAThreeDView::cameratestvalues()
//{
//    qDebug()<<"view up = "<<renderer_tka[4]->GetActiveCamera()->GetViewUp()[0]
//            <<renderer_tka[4]->GetActiveCamera()->GetViewUp()[1]
//            <<renderer_tka[4]->GetActiveCamera()->GetViewUp()[2];

//    qDebug()<<"focal point  = "<<renderer_tka[4]->GetActiveCamera()->GetFocalPoint()[0]
//            <<renderer_tka[4]->GetActiveCamera()->GetFocalPoint()[1]
//            <<renderer_tka[4]->GetActiveCamera()->GetFocalPoint()[2];

//    qDebug()<<"GetPosition  = "<<renderer_tka[4]->GetActiveCamera()->GetPosition()[0]
//            <<renderer_tka[4]->GetActiveCamera()->GetPosition()[1]
//            <<renderer_tka[4]->GetActiveCamera()->GetPosition()[2];

//    qDebug()<<"GetOrientation  = "<<renderer_tka[4]->GetActiveCamera()->GetOrientation()[0]
//            <<renderer_tka[4]->GetActiveCamera()->GetOrientation()[1]
//            <<renderer_tka[4]->GetActiveCamera()->GetOrientation()[2];

//    qDebug()<<"GetRoll  = "<< renderer_tka[4]->GetActiveCamera()->GetRoll();


//}

void TKAThreeDView::TranslationsiconChange()
{
    QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
    QString id = button_whichbuttonpressed->objectName();  // Get the button's ID (object name)



    if(id == "pushButton_FAleftdown")
    {
       pushButton_FAleftdown->setIcon(QIcon(":/res/icons/exit_slight_left_sel.png"));
    } else  if(id == "pushButton_FArightdown")
    {
       pushButton_FArightdown->setIcon(QIcon(":/res/icons/exit_slight_right_sel.png"));

    }
    else  if(id == "pushButton_FAup")
    {
        pushButton_FAup->setIcon(QIcon(":/res/icons/up_sel.png"));

    }
    else  if(id == "pushButton_FAright")
    {
        pushButton_FAright->setIcon(QIcon(":/res/icons/right_sel.png"));

    }
    else  if(id == "pushButton_FAleft")
    {
        pushButton_FAleft->setIcon(QIcon(":/res/icons/left_sel.png"));

    }
    else  if(id == "pushButton_FAdown")
    {
        pushButton_FAdown->setIcon(QIcon(":/res/icons/down_sel.png"));


    }else  if(id == "pushButton_FDleftdown")
    {
        pushButton_FDleftdown->setIcon(QIcon(":/res/icons/exit_slight_left_sel.png"));
    } else  if(id == "pushButton_FDrightdown")
    {
        pushButton_FDrightdown->setIcon(QIcon(":/res/icons/exit_slight_right_sel.png"));

    }
    else  if(id == "pushButton_FDup")
    {
        pushButton_FDup->setIcon(QIcon(":/res/icons/up_sel.png"));

    }
    else  if(id == "pushButton_FDright")
    {
        pushButton_FDright->setIcon(QIcon(":/res/icons/right_sel.png"));

    }
    else  if(id == "pushButton_FDleft")
    {
        pushButton_FDleft->setIcon(QIcon(":/res/icons/left_sel.png"));

    }
    else  if(id == "pushButton_FDdown")
    {
        pushButton_FDdown->setIcon(QIcon(":/res/icons/down_sel.png"));


    }else  if(id == "pushButton_FLleftdown")
    {
        pushButton_FLleftdown->setIcon(QIcon(":/res/icons/exit_slight_left_sel.png"));
    } else  if(id == "pushButton_FLrightdown")
    {
        pushButton_FLrightdown->setIcon(QIcon(":/res/icons/exit_slight_right_sel.png"));

    }
    else  if(id == "pushButton_FLup")
    {
        pushButton_FLup->setIcon(QIcon(":/res/icons/up_sel.png"));

    }
    else  if(id == "pushButton_FLright")
    {
        pushButton_FLright->setIcon(QIcon(":/res/icons/right_sel.png"));

    }
    else  if(id == "pushButton_FLleft")
    {
        pushButton_FLleft->setIcon(QIcon(":/res/icons/left_sel.png"));

    }
    else  if(id == "pushButton_FLdown")
    {
        pushButton_FLdown->setIcon(QIcon(":/res/icons/down_sel.png"));
    }else  if(id == "pushButton_TAleftdown")
    {
       pushButton_TAleftdown->setIcon(QIcon(":/res/icons/exit_slight_lefttib_sel.png"));
    } else  if(id == "pushButton_TArightdown")
    {
       pushButton_TArightdown->setIcon(QIcon(":/res/icons/exit_slight_rttib_sel.png"));

    }
    else  if(id == "pushButton_TAup")
    {
        pushButton_TAup->setIcon(QIcon(":/res/icons/up_sel.png"));

    }
    else  if(id == "pushButton_TAright")
    {
        pushButton_TAright->setIcon(QIcon(":/res/icons/right_sel.png"));

    }
    else  if(id == "pushButton_TAleft")
    {
        pushButton_TAleft->setIcon(QIcon(":/res/icons/left_sel.png"));

    }
    else  if(id == "pushButton_FAdown")
    {
        pushButton_TAdown->setIcon(QIcon(":/res/icons/down_sel.png"));


    }else  if(id == "pushButton_TDleftdown")
    {
        pushButton_TDleftdown->setIcon(QIcon(":/res/icons/exit_slight_lefttib_sel.png"));
    } else  if(id == "pushButton_TDrightdown")
    {
        pushButton_TDrightdown->setIcon(QIcon(":/res/icons/exit_slight_rttib_sel.png"));

    }
    else  if(id == "pushButton_TDup")
    {
        pushButton_TDup->setIcon(QIcon(":/res/icons/up_sel.png"));

    }
    else  if(id == "pushButton_TDright")
    {
        pushButton_TDright->setIcon(QIcon(":/res/icons/right_sel.png"));

    }
    else  if(id == "pushButton_TDleft")
    {
        pushButton_TDleft->setIcon(QIcon(":/res/icons/left_sel.png"));

    }
    else  if(id == "pushButton_TDdown")
    {
        pushButton_TDdown->setIcon(QIcon(":/res/icons/down_sel.png"));


    }else  if(id == "pushButton_TLleftdown")
    {
        pushButton_TLleftdown->setIcon(QIcon(":/res/icons/exit_slight_lefttib_sel.png"));
    } else  if(id == "pushButton_TLrightdown")
    {
        pushButton_TLrightdown->setIcon(QIcon(":/res/icons/exit_slight_rttib_sel.png"));

    }
    else  if(id == "pushButton_TLup")
    {
        pushButton_TLup->setIcon(QIcon(":/res/icons/up_sel.png"));

    }
    else  if(id == "pushButton_TLright")
    {
        pushButton_TLright->setIcon(QIcon(":/res/icons/right_sel.png"));

    }
    else  if(id == "pushButton_TLleft")
    {
        pushButton_TLleft->setIcon(QIcon(":/res/icons/left_sel.png"));

    }
    else  if(id == "pushButton_TLdown")
    {
        pushButton_TLdown->setIcon(QIcon(":/res/icons/down_sel.png"));
    }





}



void TKAThreeDView::Translationsiconrelease()
{
    QPushButton *button_whichbuttonpressed = qobject_cast<QPushButton *>(sender());
    QString id = button_whichbuttonpressed->objectName();  // Get the button's ID (object name)



    if(id == "pushButton_FAleftdown")
    {
       pushButton_FAleftdown->setIcon(QIcon(":/res/icons/left_rotate.png"));

    } else  if(id == "pushButton_FArightdown")
    {
       pushButton_FArightdown->setIcon(QIcon(":/res/icons/right_rotate.png"));

    }
    else  if(id == "pushButton_FAup")
    {
        pushButton_FAup->setIcon(QIcon(":/res/icons/up_arrow.png"));

    }
    else  if(id == "pushButton_FAright")
    {
        pushButton_FAright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    }
    else  if(id == "pushButton_FAleft")
    {
        pushButton_FAleft->setIcon(QIcon(":/res/icons/left_arrow.png"));

    }
    else  if(id == "pushButton_FAdown")
    {
        pushButton_FAdown->setIcon(QIcon(":/res/icons/down_arrow.png"));

    }else  if(id == "pushButton_FDleftdown")
    {
       pushButton_FDleftdown->setIcon(QIcon(":/res/icons/left_rotate.png"));

    } else  if(id == "pushButton_FDrightdown")
    {
       pushButton_FDrightdown->setIcon(QIcon(":/res/icons/right_rotate.png"));

    }
    else  if(id == "pushButton_FDup")
    {
        pushButton_FDup->setIcon(QIcon(":/res/icons/up_arrow.png"));

    }
    else  if(id == "pushButton_FDright")
    {
        pushButton_FDright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    }
    else  if(id == "pushButton_FDleft")
    {
        pushButton_FDleft->setIcon(QIcon(":/res/icons/left_arrow.png"));

    }
    else  if(id == "pushButton_FDdown")
    {
        pushButton_FDdown->setIcon(QIcon(":/res/icons/down_arrow.png"));

    }else  if(id == "pushButton_FLleftdown")
    {
       pushButton_FLleftdown->setIcon(QIcon(":/res/icons/left_rotate.png"));

    } else  if(id == "pushButton_FLrightdown")
    {
       pushButton_FLrightdown->setIcon(QIcon(":/res/icons/right_rotate.png"));

    }
    else  if(id == "pushButton_FLup")
    {
        pushButton_FLup->setIcon(QIcon(":/res/icons/up_arrow.png"));

    }
    else  if(id == "pushButton_FLright")
    {
        pushButton_FLright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    }
    else  if(id == "pushButton_FLleft")
    {
        pushButton_FLleft->setIcon(QIcon(":/res/icons/left_arrow.png"));

    }
    else  if(id == "pushButton_FLdown")
    {
        pushButton_FLdown->setIcon(QIcon(":/res/icons/down_arrow.png"));

    } else if(id == "pushButton_TAleftdown")
    {
       pushButton_TAleftdown->setIcon(QIcon(":/res/icons/left_rotate_tib.png"));

    } else  if(id == "pushButton_TArightdown")
    {
       pushButton_TArightdown->setIcon(QIcon(":/res/icons/right_rotate_tib.png"));

    }
    else  if(id == "pushButton_TAup")
    {
        pushButton_TAup->setIcon(QIcon(":/res/icons/up_arrow.png"));

    }
    else  if(id == "pushButton_TAright")
    {
        pushButton_TAright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    }
    else  if(id == "pushButton_TAleft")
    {
        pushButton_TAleft->setIcon(QIcon(":/res/icons/left_arrow.png"));

    }
    else  if(id == "pushButton_TAdown")
    {
        pushButton_TAdown->setIcon(QIcon(":/res/icons/down_arrow.png"));

    }else  if(id == "pushButton_TDleftdown")
    {
       pushButton_TDleftdown->setIcon(QIcon(":/res/icons/left_rotate_tib.png"));

    } else  if(id == "pushButton_TDrightdown")
    {
       pushButton_TDrightdown->setIcon(QIcon(":/res/icons/right_rotate_tib.png"));

    }
    else  if(id == "pushButton_TDup")
    {
        pushButton_TDup->setIcon(QIcon(":/res/icons/up_arrow.png"));

    }
    else  if(id == "pushButton_TDright")
    {
        pushButton_TDright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    }
    else  if(id == "pushButton_TDleft")
    {
        pushButton_TDleft->setIcon(QIcon(":/res/icons/left_arrow.png"));

    }
    else  if(id == "pushButton_TDdown")
    {
        pushButton_TDdown->setIcon(QIcon(":/res/icons/down_arrow.png"));

    }else  if(id == "pushButton_TLleftdown")
    {
       pushButton_TLleftdown->setIcon(QIcon(":/res/icons/left_rotate_tib.png"));

    } else  if(id == "pushButton_TLrightdown")
    {
       pushButton_TLrightdown->setIcon(QIcon(":/res/icons/right_rotate_tib.png"));

    }
    else  if(id == "pushButton_TLup")
    {
        pushButton_TLup->setIcon(QIcon(":/res/icons/up_arrow.png"));

    }
    else  if(id == "pushButton_TLright")
    {
        pushButton_TLright->setIcon(QIcon(":/res/icons/right_arrow.png"));

    }
    else  if(id == "pushButton_TLleft")
    {
        pushButton_TLleft->setIcon(QIcon(":/res/icons/left_arrow.png"));

    }
    else  if(id == "pushButton_TLdown")
    {
        pushButton_TLdown->setIcon(QIcon(":/res/icons/down_arrow.png"));

    }
}
