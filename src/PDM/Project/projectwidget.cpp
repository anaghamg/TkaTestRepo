/*
    File Name       : ProjectWidget.cpp
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Source file implementing creation of patient projects, view patient details,
                      import dicom and stl and do landmark registration
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#include "projectwidget.h"

ProjectWidget::ProjectWidget(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"*********Start of ProjectWidget ctor";

    //---------------------- Patient Details Tab ----------------------//
    QLabel *qlblPatDetails = new QLabel;
    qlblPatDetails->setText("Patient Details");
    QLabel *qlblPatHistory = new QLabel;
    qlblPatHistory->setText("Patient History");
    QTableView* qtablePatHistory = new QTableView;
    QVBoxLayout* qvblPatient = new QVBoxLayout;
    qvblPatient->addWidget(qlblPatDetails);
    qvblPatient->addWidget(&m_qtableViewPatDetails);
    qvblPatient->addWidget(qlblPatHistory);
    qvblPatient->addWidget(qtablePatHistory);
    m_qwPatient = new QWidget;
    m_qwPatient->setLayout(qvblPatient);
    //---------------------- End of -----------------------------//


    //----------------------- Project Tab ----------------------------//
    m_qpbNewProject = new QPushButton("New Project");
    m_qpbNewProject->setEnabled(true);
    m_qpbOpenProject = new QPushButton("Open Project");
    m_qpbOpenProject->setEnabled(true);
    m_qpbNewProject->setFixedSize(450,50);
    m_qpbOpenProject->setFixedSize(450,50);
    QVBoxLayout*  qpvblProj = new QVBoxLayout;
    qpvblProj->addWidget(m_qpbNewProject);
    qpvblProj->addWidget(m_qpbOpenProject);
    qpvblProj->setAlignment(Qt::AlignVCenter |  Qt::AlignHCenter);
    QWidget* qpwProj = new QWidget;
    qpwProj->setLayout(qpvblProj);

    QLabel *qlblRecentProject = new QLabel;
    qlblRecentProject->setText("Recent projects");
    QTableView* qplstRecentPrjts = new QTableView;

    QVBoxLayout*   qpvblProject = new QVBoxLayout;
    qpvblProject->addWidget(qpwProj);
    qpvblProject->addWidget(qlblRecentProject);
    qpvblProject->addWidget(qplstRecentPrjts);
    m_qwPjtMenu = new QWidget;
    m_qwPjtMenu->setLayout(qpvblProject);
    //---------------------- End of -----------------------------//


    //--------------------- Import Tab -----------------------//
    //--------Left panel(menu)----------//
    m_qpbloadDicom = new QPushButton("Dicom");
    m_qpbloadDicom->setStyleSheet("QPushButton{width:100px;}");
    m_qpbloadDicom->setToolTip("Load Dicom Directory");
    m_qpbloadSTL = new QPushButton("STL");
    m_qpbloadSTL->setStyleSheet("QPushButton{width:100px;}");
    m_qpbloadSTL->setToolTip("Load STL Model");

    m_qpbloadDicom->setFixedSize(70,30);
    m_qpbloadSTL->setFixedSize(70,30);

    QVBoxLayout* qpvblloadDataMenu = new QVBoxLayout;
    qpvblloadDataMenu->addWidget(m_qpbloadDicom);
    qpvblloadDataMenu->addWidget(m_qpbloadSTL);
    qpvblloadDataMenu->setAlignment(Qt::AlignLeft);
    QWidget* qpwLoadDataMenu = new QWidget;
    qpwLoadDataMenu->setLayout(qpvblloadDataMenu);

    //---------right panel(display)--------//
    //initialize class objects
    m_objClassDicom = new ClassDicom; //2d
    m_objClassStl = new ClassSTL;

    QHBoxLayout* qhblDicomStl = new QHBoxLayout;
    qhblDicomStl->addWidget(m_objClassDicom);
    qhblDicomStl->addWidget(m_objClassStl);
    QWidget* qwDicomStl = new QWidget;
    qwDicomStl->setLayout(qhblDicomStl);

    QHBoxLayout* qphblloadData = new QHBoxLayout;
    qphblloadData->addWidget(qpwLoadDataMenu);
    qphblloadData->addWidget(qwDicomStl);
    m_qwLoadData = new QWidget;
    m_qwLoadData->setLayout(qphblloadData);

    //---------------------- End of -----------------------------//

    //open new project
    connect(m_qpbNewProject,&QPushButton::clicked,
            this, &ProjectWidget::OpenNew);

    //open existing project
    connect(m_qpbOpenProject,&QPushButton::clicked,
            this, &ProjectWidget::OpenExisting);

    //load STL
    connect(m_qpbloadSTL,&QPushButton::clicked,
            m_objClassStl,&ClassSTL::GetSTLFilePath);

    //load Dicom
    connect(m_qpbloadDicom,&QPushButton::clicked,
            m_objClassDicom,&ClassDicom::GetDicomDirectory);


//    connect(m_objClassDicom,&ClassDicom::signalLoadDicomStatus,
//            this,&ProjectWidget::setLoadDicomStatus);

//    connect(m_objClassStl,&ClassSTL::signalLoadStlStatus,
//            this, &ProjectWidget::setLoadStlStatus);

    qDebug()<<"End of ProjectWidget ctor";
}

void ProjectWidget::OpenNew()
{
    qDebug()<<"Create New";
    //store new project file in selected path in xml format
    QString qstrNewProjPath = QFileDialog::getSaveFileName(this, tr("Create new project"),
                                                           "/home/untitled.xml",
                                                           tr("Project File (*.xml)"));

    QFile fileout(qstrNewProjPath);
    fileout.open(QIODevice::WriteOnly);
    fileout.close();
    qDebug()<<"XML file"<<qstrNewProjPath;
    emit signalNewProject(qstrNewProjPath);
    qDebug()<<"finished opening new project";
}

void ProjectWidget::OpenExisting()
{
    qDebug()<<"OpenExisting";
    //open existing project file in xml format
    QString qstrExistingProjPath =  QFileDialog::getOpenFileName(this,tr("Please select project file"), "/home/", tr("All Files (*.xml)"));
    qDebug()<<"Selected path of existing project : "<<qstrExistingProjPath;
    emit signalExistingProject(qstrExistingProjPath);
    qDebug()<<"finished opening existing project";
}

void ProjectWidget::OpenRecent()
{
     qDebug()<<"OpenRecent";
     //open recent project file in xml format
     QString qstrRecentProjPath; //select from list view
     qDebug()<<"Selected path of recently opened project : "<<qstrRecentProjPath;
     emit signalRecentProject(qstrRecentProjPath);
     qDebug()<<"finished opening recent project";
}

void ProjectWidget::displayPatientDetails(QStringList qstrPatDetails)
{
    QStringList qstrlist = qstrPatDetails;
    qDebug()<<"DisplayPatientDetails"<<qstrlist;

    int rowCount = 1;
    int colCount = 8;
    m_patDetModel.setRowCount(rowCount);
    m_patDetModel.setColumnCount(colCount);
    for (int row=0;row<rowCount;row++)
    {
        for (int col=0;col<colCount;col++)
        {
            QModelIndex index = m_patDetModel.index(row, col);
            m_patDetModel.setData(index, qstrPatDetails.at(col));
        }
    }
    m_qtableViewPatDetails.setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_qtableViewPatDetails.setTabKeyNavigation(true); //default
    m_qtableViewPatDetails.resizeRowsToContents();
    m_patDetModel.setHeaderData(0, Qt::Horizontal,"PatientID");
    m_patDetModel.setHeaderData(1, Qt::Horizontal,"Name");
    m_patDetModel.setHeaderData(2, Qt::Horizontal,"Gender");
    m_patDetModel.setHeaderData(3, Qt::Horizontal,"Age");
    m_patDetModel.setHeaderData(4, Qt::Horizontal,"DOB");
    m_patDetModel.setHeaderData(5, Qt::Horizontal,"Address");
    m_patDetModel.setHeaderData(6, Qt::Horizontal,"Ref.Physician");
    m_patDetModel.setHeaderData(7, Qt::Horizontal,"Aadhaar");

    m_qtableViewPatDetails.setModel(&m_patDetModel);
    m_qtableViewPatDetails.resizeRowsToContents();

    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
    m_qtableViewPatDetails.horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    m_qtableViewPatDetails.setShowGrid(true);

    m_qtableViewPatDetails.update();
}
