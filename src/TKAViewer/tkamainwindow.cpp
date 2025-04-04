/*
 * File Name : TKAmainwindow.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file: Implementation file of planning module
 * Developer :Divya N S
 * Revision History : 1-8-2024
*/
#include "tkamainwindow.h"
#include <QSettings>
#include <QSettings>
#include <QFile>
#include <QTextStream>

TKAMainWindow::TKAMainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    //Central widget
    centralwidget = new QWidget(this);
    centralwidget->setObjectName("centralwidget");

    //Main grid layout of central widget
    Main_gridLayout = new QGridLayout(centralwidget);
    Main_gridLayout->setContentsMargins(0,0,0,0);
    Main_gridLayout->setObjectName("Main_gridLayout");

    //Stacked widget in Main_gridLayout
    stackedWidget = new QStackedWidget(centralwidget);
    stackedWidget->setObjectName("stackedWidget");


    //Setting up UI
    Main_gridLayout->addWidget(stackedWidget, 0, 0);


    //----------------Center panel---------------------
    frame_centerpanel = new QFrame();
    frame_centerpanel->setObjectName("frame_centerpanel");

    QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(frame_centerpanel->sizePolicy().hasHeightForWidth());

    frame_centerpanel->setSizePolicy(sizePolicy);
    frame_centerpanel->setMinimumSize(QSize(50, 0));
    frame_centerpanel->setFrameShape(QFrame::StyledPanel);
    frame_centerpanel->setFrameShadow(QFrame::Raised);

    //Vertical layout for center panel buttons
    verticalLayout = new QVBoxLayout(frame_centerpanel);
    verticalLayout->setObjectName("verticalLayout");
    verticalLayout->setContentsMargins(-1, 0, -1, -1);
    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
    verticalLayout->addItem(verticalSpacer_3);


    QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);

    //***CTScan icon button***
    pushButton_2D = new QPushButton();
    pushButton_2D->setIcon(QIcon(":/res/icons/CT_Scan.png"));
    pushButton_2D->setIconSize(QSize(75,75));
    pushButton_2D->setObjectName("planningButtonicons");
    pushButton_2D->setCheckable(true);// making the button checkable

    //***Cut icon button***
    pushButton_cut = new QPushButton();
    pushButton_cut->setIcon(QIcon(":/res/icons/cut.png"));
    pushButton_cut->setIconSize(QSize(75,75));
    pushButton_cut->setObjectName("planningButtonicons");
    pushButton_cut->setCheckable(true);

    //***Axis icon button***
    pushButton_axis = new QPushButton();
    pushButton_axis->setIcon(QIcon(":/res/icons/axis.png"));
    pushButton_axis->setIconSize(QSize(55, 55));
    pushButton_axis->setObjectName("planningButtonicons");
    pushButton_axis->setCheckable(true);


    //***Anototation points icon button***
    pushButton_AnotPoint = new QPushButton();
    pushButton_AnotPoint->setIcon(QIcon(":/res/icons/points.png"));
    pushButton_AnotPoint->setIconSize(QSize(55, 55));
    pushButton_AnotPoint->setObjectName("planningButtonicons");
    pushButton_AnotPoint->setCheckable(true);


    //***implant icon button***
    pushButton_implant = new QPushButton();
    pushButton_implant->setIcon(QIcon(":/res/icons/3D_tka.png"));
    pushButton_implant->setIconSize(QSize(55, 55));
    pushButton_implant->setObjectName("planningButtonicons");
    pushButton_implant->setCheckable(true);


    //***Opacity button for semi transparent view and opaque view of bone***
    pushButton_Implantopacity = new QPushButton();
    pushButton_Implantopacity->setIcon(QIcon(":/res/icons/bone_opacity.png"));
    pushButton_Implantopacity->setIconSize(QSize(55, 55));
    pushButton_Implantopacity->setObjectName("planningButtonicons");
    pushButton_Implantopacity->setCheckable(true);
    pushButton_Implantopacity->setEnabled(true);


    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
    verticalLayout->addItem(verticalSpacer_4);

    //------Right panel---------
    frame_rightpanel = new QFrame();
    frame_rightpanel->setObjectName("frameannotation");
    frame_rightpanel->setFixedWidth(480);

    m_qvbrightpanel = new QVBoxLayout(frame_rightpanel);

    QWidget *m_qwcomboboxlayout = new QWidget;

    m_qwcomboboxlayout->setFixedHeight(394);

    //custom combobox manufacturer
    QVBoxLayout *m_qvbmanufaclayout = new QVBoxLayout();
    m_qvbmanufaclayout->setMargin(0);
    QPushButton *m_qpbmanufacturbutton = new QPushButton("Manufacturer");
    m_qpbmanufacturbutton->setObjectName("manufactbtn");
    m_qvbmanufaclayout->addWidget(m_qpbmanufacturbutton, Qt::AlignTop);
    m_qpbmanufacturbutton->setCheckable(true);

    // Create the dropdown view (list)
    QListView *m_qlvmanufaclist = new QListView();
    m_qlvmanufaclist->setVisible(false);
    m_qlvmanufaclist->setObjectName("manumodelList");

    // Populate the list view with items
    QStringList items = {"Smith & Nephew", "Stryker", "Enovis","Medtronic","ConforMIS","Exactech"};
    QStringListModel *model = new QStringListModel(items);
    m_qlvmanufaclist->setModel(model);
    m_qvbmanufaclayout->addWidget(m_qlvmanufaclist);



    //custom combobox model
    QVBoxLayout *m_qvbmodellayout = new QVBoxLayout();
    QPushButton *m_qpbmodelbutton = new QPushButton("Model");
    m_qpbmodelbutton->setObjectName("modelbtn");
    m_qvbmodellayout->addWidget(m_qpbmodelbutton, Qt::AlignTop);
    m_qpbmodelbutton->setCheckable(true);

    // Create the dropdown view (list)
    QListView *m_qlvmodellist = new QListView();
    m_qlvmodellist->setVisible(false);
    m_qlvmodellist->setObjectName("manumodelList");

    // Populate the list view with items
    QStringList itemsmodel = {"Femoral component", "Plastic Spacer", "Tibial Component"};
    QStringListModel *model2 = new QStringListModel(itemsmodel);
    m_qlvmodellist->setModel(model2);

    m_qvbmodellayout->addWidget(m_qlvmodellist);


    QVBoxLayout *m_combolay = new QVBoxLayout;

    m_combolay->addLayout(m_qvbmanufaclayout);
    m_combolay->addLayout(m_qvbmodellayout);
    m_combolay->addStretch();
    m_qwcomboboxlayout->setLayout(m_combolay);



    //Adding the Manufactur and Model buttons in the right pane
    m_qvbrightpanel->addWidget(m_qwcomboboxlayout,Qt::AlignTop);
    //   m_qvbrightpanel->addLayout(m_qvbmodellayout);

    //Tibia label
    label_TibiaSize = new QLabel("Tibia");
    label_TibiaSize->setObjectName("labelPlanningName");


    //Next Button
    pushButton_Next = new QPushButton("Next");
    pushButton_Next->setObjectName("backnextButtonnext");
    pushButton_Next->setCheckable(true);
    pushButton_Next->setAutoExclusive(true);

    //Back Button
    pushButton_Back = new QPushButton("Back");
    pushButton_Back->setObjectName("backnextButtonback");
    pushButton_Back->setCheckable(true);
    pushButton_Back->setAutoExclusive(true);

    //Setting spacers
    verticalSpacer_2 = new QSpacerItem(20, 250, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    // m_qvbrightpanel->addItem(verticalSpacer_2);
    verticalSpacer_5 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
    verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::MinimumExpanding);


    //*** Size adjustment buttons and labels ***

    label_PolySize = new QLabel("Poly");
    label_PolySize->setObjectName("labelPlanningName");

    label_FemurSize = new QLabel("Femur");
    label_FemurSize->setObjectName("labelPlanningName");//parvathy

    verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);

    QFrame *m_qfbtnframe = new QFrame;
    m_qfbtnframe->setObjectName("btnFrame");
    m_qfbtnframe->setFixedHeight(80);

    QHBoxLayout *m_qhbButtonlayout = new QHBoxLayout(m_qfbtnframe);
    m_qhbButtonlayout->addWidget(pushButton_implant,2);
    m_qhbButtonlayout->addWidget(pushButton_cut,2);
    m_qhbButtonlayout->addWidget(pushButton_2D,2);
    m_qhbButtonlayout->addWidget(pushButton_axis,2);
    m_qhbButtonlayout->addWidget(pushButton_AnotPoint,2);
    m_qhbButtonlayout->addWidget(pushButton_Implantopacity,2);
    m_qvbrightpanel->addWidget(m_qfbtnframe);
    m_qvbrightpanel->addItem(verticalSpacer);

    //Pushbuttons for femur size change
    QPushButton *m_qpbfemurin = new QPushButton;
    m_qpbfemurin->setIcon(QIcon(":/res/icons/Plus_circle.png"));
    m_qpbfemurin->setIconSize(QSize(55, 55));
    m_qpbfemurin->setObjectName("m_qpbfemurin");//changed from planningButtons to its button name because in my code calling these buttions via its objectname.
    m_qpbfemurin->setStyleSheet(
                "QPushButton#m_qpbfemurin:checked {background-color:transparent;}"
                "QPushButton#m_qpbfemurin:pressed {background-color:transparent;}"
                );

    QPushButton *m_qpbfemurde = new QPushButton;
    m_qpbfemurde->setIcon(QIcon(":/res/icons/Minus_circle.png"));
    m_qpbfemurde->setIconSize(QSize(55, 55));
    m_qpbfemurde->setObjectName("m_qpbfemurde");//changed from planningButtons to its button name because in my code calling these buttions via its objectname.
    m_qpbfemurde->setStyleSheet(
                "QPushButton#m_qpbfemurde:checked {background-color:transparent;}"
                "QPushButton#m_qpbfemurde:pressed {background-color:transparent;}"
                );

    QLabel *m_qlfemursize = new QLabel("5");
    m_qlfemursize->setObjectName("labelPlanningSize");

    QSpacerItem *m_qsHorizSpacfem = new QSpacerItem(50, 0, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);


    QHBoxLayout *m_qhbfemur = new QHBoxLayout;
    m_qhbfemur->setContentsMargins(0, 0, 30, 0);
    m_qhbfemur->addWidget(label_FemurSize);
    m_qhbfemur->addItem(m_qsHorizSpacfem);
    m_qhbfemur->addWidget(m_qpbfemurde,2,Qt::AlignRight);
    m_qhbfemur->addWidget(m_qlfemursize,1);
    m_qhbfemur->addWidget(m_qpbfemurin,0,Qt::AlignLeft);



    //Pushbuttons for Tibia size change
    QPushButton *m_qpbtibiain = new QPushButton;
    m_qpbtibiain->setIcon(QIcon(":/res/icons/Plus_circle.png"));
    m_qpbtibiain->setIconSize(QSize(55, 55));
    m_qpbtibiain->setObjectName("m_qpbtibiain");//changed from planningButtons to its button name because in my code calling these buttions via its objectname.
    m_qpbtibiain->setStyleSheet(
                "QPushButton#m_qpbtibiain:checked {background-color:transparent;}"
                "QPushButton#m_qpbtibiain:pressed {background-color:transparent;}"
                );

    QPushButton *m_qpbtibiade = new QPushButton;
    m_qpbtibiade->setIcon(QIcon(":/res/icons/Minus_circle.png"));
    m_qpbtibiade->setIconSize(QSize(55, 55));
    m_qpbtibiade->setObjectName("m_qpbtibiade");//changed from planningButtons to its button name because in my code calling these buttions via its objectname.
    m_qpbtibiade->setStyleSheet(
                "QPushButton#m_qpbtibiade:checked {background-color:transparent;}"
                "QPushButton#m_qpbtibiade:pressed {background-color:transparent;}"
                );

    QLabel *m_qltibiasize = new QLabel("4");
    m_qltibiasize->setObjectName("labelPlanningSize");

    QSpacerItem *m_qsHorizSpactib = new QSpacerItem(50, 0, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);

    QHBoxLayout *m_qhbtibia = new QHBoxLayout;
    m_qhbtibia->setContentsMargins(0, 0, 25, 0);
    m_qhbtibia->addWidget(label_TibiaSize);
    m_qhbtibia->addItem(m_qsHorizSpactib);
    m_qhbtibia->addWidget(m_qpbtibiade,2,Qt::AlignRight);
    m_qhbtibia->addWidget(m_qltibiasize,1);
    m_qhbtibia->addWidget(m_qpbtibiain,0,Qt::AlignLeft);


    //Pushbuttons for Poly size change
    QPushButton *m_qpbpolyin = new QPushButton;
    m_qpbpolyin->setIcon(QIcon(":/res/icons/Plus_circle.png"));
    m_qpbpolyin->setIconSize(QSize(55, 55));
    m_qpbpolyin->setObjectName("m_qpbpolyin");//changed from planningButtons to its button name because in my code calling these buttions via its objectname.
    m_qpbpolyin->setStyleSheet(
                "QPushButton#m_qpbpolyin:checked {background-color:transparent;}"
                "QPushButton#m_qpbpolyin:pressed {background-color:transparent;}"
                );
    QPushButton *m_qpbpolyde = new QPushButton;
    m_qpbpolyde->setIcon(QIcon(":/res/icons/Minus_circle.png"));
    m_qpbpolyde->setIconSize(QSize(55, 55));
    m_qpbpolyde->setObjectName("m_qpbpolyde");//changed from planningButtons to its button name because in my code calling these buttions via its objectname.
    m_qpbpolyde->setStyleSheet(
                "QPushButton#m_qpbpolyde:checked {background-color:transparent;}"
                "QPushButton#m_qpbpolyde:pressed {background-color:transparent;}"
                );
    QLabel *m_qlpolysize = new QLabel("8");
    m_qlpolysize->setObjectName("labelPlanningSize");

    QSpacerItem *m_qsHorizSpacpoly = new QSpacerItem(50, 0, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);


    QHBoxLayout *m_qhbpoly = new QHBoxLayout;
    m_qhbpoly->setContentsMargins(0, 0, 25, 0);
    m_qhbpoly->addWidget(label_PolySize);
    m_qhbpoly->addItem(m_qsHorizSpacpoly);
    m_qhbpoly->addWidget(m_qpbpolyde,2,Qt::AlignRight);
    m_qhbpoly->addWidget(m_qlpolysize,1);
    m_qhbpoly->addWidget(m_qpbpolyin,0,Qt::AlignLeft);

    //setting the buttons in the layout
    m_qvbrightpanel->addLayout(m_qhbfemur,Qt::AlignTop);
    m_qvbrightpanel->addLayout(m_qhbtibia,Qt::AlignTop);
    m_qvbrightpanel->addLayout(m_qhbpoly,Qt::AlignTop);

    //Layout for next and back buttons
    QHBoxLayout *m_qhbbackNextbtn = new QHBoxLayout;
    m_qhbbackNextbtn->addWidget(pushButton_Back);
    m_qhbbackNextbtn->addWidget(pushButton_Next);

    //Adding layout to panel
    m_qvbrightpanel->addLayout(m_qhbbackNextbtn);

    //Adding layout to mainwidget
    Main_gridLayout->addWidget(frame_rightpanel, 0, 1);

    this->setCentralWidget(centralwidget);


    //Adding views to main window
    stackedWidget->insertWidget(0,&m_ThreeDView);
    stackedWidget->insertWidget(1,&m_TwoDView);

    //Signal slot connections
    //connect(pushButton_2D,SIGNAL(clicked()),this,SLOT(Switch3DViewSlot()));//commented
    connect(pushButton_cut,SIGNAL(clicked(bool)),&m_ThreeDView,SLOT(PrimarycutFemurandTibia(bool)));
    connect(pushButton_axis,SIGNAL(clicked(bool)),&m_ThreeDView,SLOT(AxisDisplaySlot(bool)));
    connect(pushButton_AnotPoint,SIGNAL(clicked(bool)),&m_ThreeDView,SLOT(UpdateAnatomicalPoint(bool)));
    connect(pushButton_implant,SIGNAL(clicked(bool)),&m_ThreeDView,SLOT(LoadImplant(bool)));

    //For implant component size adjustment
    connect(m_qpbfemurin,SIGNAL(clicked()),&m_ThreeDView,SLOT(FemurComponentSizeAdjustment()));
    connect(m_qpbfemurde,SIGNAL(clicked()),&m_ThreeDView,SLOT(FemurComponentSizeAdjustment()));
    connect(m_qpbtibiain,SIGNAL(clicked()),&m_ThreeDView,SLOT(TibiaComponentSizeAdjustment()));
    connect(m_qpbtibiade,SIGNAL(clicked()),&m_ThreeDView,SLOT(TibiaComponentSizeAdjustment()));
    connect(m_qpbpolyin,SIGNAL(clicked()),&m_ThreeDView,SLOT(SpacerComponentSizeAdjustment()));
    connect(m_qpbpolyde,SIGNAL(clicked()),&m_ThreeDView,SLOT(SpacerComponentSizeAdjustment()));


    //For implant and bone opacities
    connect(pushButton_Implantopacity,SIGNAL(clicked(bool)),&m_ThreeDView,SLOT(AdjustImplantOpacity(bool)));
    //connect(pushButton_Implantopacity,SIGNAL(clicked(bool)),&m_ThreeDView,SLOT(AdjustImplantOpacity(bool)));

    //For enable / disable size adjustment boxes when impalnt is loaded or not
    //connect(&m_ThreeDView, SIGNAL(Enablespinboxes(bool)),this, SLOT(EnableSpinboxes(bool)));

    connect(m_qpbmanufacturbutton, &QPushButton::clicked, this, [this, m_qpbmanufacturbutton,m_qlvmanufaclist]() {

        m_qlvmanufaclist->setVisible(!m_qlvmanufaclist->isVisible());

    });

    connect(m_qpbmodelbutton, &QPushButton::clicked, this, [this, m_qpbmodelbutton,m_qlvmodellist]() {

        m_qlvmodellist->setVisible(!m_qlvmodellist->isVisible());

    });


}
void execute_python_script(const std::string& folder_path, const std::string& script_name) {
    // Construct the command to execute the Python script in the specified directory
    std::string command = "cd " + folder_path + " && python \"" + script_name + "\""; // Use 'python3' if needed

    // Execute the command
    int result = system(command.c_str());

    // Check if the command was successful
    if (result != 0) {
        cerr << "Failed to execute script: " << script_name << endl;
    }
}

TKAMainWindow::~TKAMainWindow()
{

}
void TKAMainWindow::Switch3DViewSlot()
{
    stackedWidget->setCurrentIndex(0);
}

//void TKAMainWindow::EnableSpinboxes(bool value1)
//{
//pushButton_Implantopacity->setEnabled(value1);

//doubleSpinBox_Femur->setEnabled(value1);
//doubleSpinBox_Tibia->setEnabled(value1);
//doubleSpinBo_Poly->setEnabled(value1);
//}
//--added on 26-9-24 to get the femur and tibia data from the patient selected----
void TKAMainWindow::SlotForFemurTibiaPaths(const QString &qstrFemurStl, const QString &qstrTibiaStl)
{
    ///-------------old code----------------
    //    qDebug()<<" fempathstl ="<<qstrFemurStl;
    //    qDebug()<<" tibpathstl ="<<qstrTibiaStl;

    //    m_ThreeDView.m_direc_femur = qstrFemurStl;
    //    m_ThreeDView.m_direc_tibia = qstrTibiaStl;
    //    m_ThreeDView.IntializePlanningWindows();


    //-----Modified on 25-10-24 for new SAKS-----
//    QString SAKS_femurDir = QDir::currentPath() + "/Segmentation_batfile/output_femur_dicom";
//    QString SAKS_tibiaDir = QDir::currentPath() + "/Segmentation_batfile/output_tibia_dicom";

    //m_ThreeDView.m_direc_femur = SAKS_femurDir;
    //m_ThreeDView.m_direc_tibia = SAKS_tibiaDir;
    //m_ThreeDView.IntializePlanningWindows();
}

void TKAMainWindow::PlanningButtonclickedSlot()
{
    //Calling the kinematics module
    //if(Planningclicked_onetime == false)
    {
        QDir dir(QDir::currentPath());

        // Get the parent path (up to the last directory)
        QString parentPath = dir.path();
        parentPath = dir.cdUp() ? dir.path() : QString();

        qDebug() << "Parent path:" << parentPath;

        // Specify the paths to your Python scripts
        std::string folder_path = (parentPath+"/TKA_Kinematics_Ver1.0/code").toStdString();
        std::string script1_name =(parentPath+"/TKA_Kinematics_Ver1.0/code/phantom_femur.py").toStdString();
        std:: string script2_name = (parentPath+"/TKA_Kinematics_Ver1.0/code/phantom_tibia.py").toStdString();

        // Execute both Python scripts
        cout << "Executing script phantom_femur.py..." << endl;
        execute_python_script(folder_path, script1_name);

        cout << "Executing script phantom_tibia.py..." << endl;
        execute_python_script(folder_path, script2_name);

        Planningclicked_onetime = true;

        //Reading the .json files from the knematics module:
        std::string m_femurjsonFilepath = folder_path+"/femur_kinematics.json";
        std::string m_tibiajsonFilepath = folder_path+"/tibia_kinematics.json";
        m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->ReadJsonFromKinematicsModule(QString::fromStdString(m_femurjsonFilepath),
                                                                                              QString::fromStdString(m_tibiajsonFilepath));
        //Setting the label values in planning window from kinematic module
        //*****Femur*****
        //Rotation values
        m_ThreeDView.label_Fem_VarValgValue->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_valgusVarusAngle);
        m_ThreeDView.label_FL_FlexExtenValue->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_flexionExtensionAngle);
        m_ThreeDView.label_FDIntExtValue->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_internalExternalRotationAngle);

        //resection depths
        m_ThreeDView.label_ValueF1->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_medialDistalResectionDepth);
        m_ThreeDView.label_ValueF4->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_lateralDistalResectionDepth);
        m_ThreeDView.label_ValueF11->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_medialPosteriorResectionDepth);
        m_ThreeDView.label_Value21->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Femur_lateralPosteriorResectionDepth);

        //combined depth
        //m_ThreeDView.label_ValueF2->setText();
        //m_ThreeDView.label_ValueF5->setText();

        //*****Tibia*****
        //resection depths
        m_ThreeDView.label_ValueF3->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_medialProximalResectionDepth);
        m_ThreeDView.label_ValueF6->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_lateralProximalResectionDepth);
        m_ThreeDView.label_Value13->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_medialProximalResectionDepth);
        m_ThreeDView.label_Value23->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_lateralProximalResectionDepth);

        //combined depth
        //m_ThreeDView.label_Value12->setText();
        //m_ThreeDView.label_Value22->setText();


        //Rotation values
        m_ThreeDView.label_Tib_VarValgusValue->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_valgusVarusAngle);
        m_ThreeDView.label_Tib_InterExterValue->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_internalExternalRotationAngle);
        m_ThreeDView.label_TibPSlopeValue->setText(m_ThreeDView.m_ObjAxisDisplayView->m_objKinematicsClass->Tibia_Posteriorslope);
    }


}

void TKAMainWindow::Switch2DViewSlot()
{
    stackedWidget->setCurrentIndex(1);
}


