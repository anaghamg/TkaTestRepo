#include "reginterfaceclass.h"

RegInterfaceClass::RegInterfaceClass(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"RegInterfaceClass";

    //initialise class objects
    m_objRegUI = new RegistrationUI;
    m_objCheckpt = new Checkpoint;
    m_objRegImplmt = new RegImplementation;
    m_objVerificationUi = new verificationui;

    //add fiducial marker class
    m_objfiducialsWindow = new fiducialswindow;
    m_objRegUI->m_qvtkToolwin->SetRenderWindow(m_objfiducialsWindow->m_openGLToolWin);

    m_qswDisplay = new QStackedWidget;
    m_qswDisplay->insertWidget(0,m_objRegImplmt); //reg implementation class
    m_qswDisplay->insertWidget(1,m_objVerificationUi); //verific widget class
    m_qswDisplay->insertWidget(2,m_objCheckpt); //checkpoint widget class
    m_qswDisplay->setCurrentIndex(2);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_qswDisplay,75);
    mainLayout->addWidget(m_objRegUI,25);
    this->setLayout(mainLayout);

    connect(m_objRegUI, &RegistrationUI::signalTableSelection,
            this,&RegInterfaceClass::itemSelectedInTable);

    connect(m_objRegUI->m_qtbwRegistration,&QTabWidget::currentChanged,
            this,&RegInterfaceClass::regTabChanged);
    regTabChanged(0);  //force emit Femur tab selected signal

    //get which thumbnail was selected
    connect(m_objRegUI, &RegistrationUI::signalThumbnailSelection,
            m_objRegImplmt,&RegImplementation::thumbnailSelected);


    //----------------for surface registration-----------------//

    connect(m_objRegUI->m_qpbBack, &QPushButton::clicked,
            m_objRegImplmt, &RegImplementation::startSurfaceDataCollection);

    connect(m_objRegUI->m_qpbNext, &QPushButton::clicked,
            m_objRegImplmt, &RegImplementation::endSurfaceDataCollection);

    //-----------------end-----------------------------------//


    //signal slot incompatibility error
//    connect(m_objRegImplmt, &RegImplementation::signalVerificationUi,
//            m_objVerificationUi, &verificationui::slotShowTransformedPoints);



    // capture button click,press and release event
    connect(m_objRegUI->m_qpbCaptureReg, &QPushButton::clicked,
            m_objRegImplmt,&RegImplementation::onCaptureClicked);
    connect(m_objRegUI->m_qpbCaptureReg, &QPushButton::pressed,
            m_objRegImplmt,&RegImplementation::onCapturePressed);
    connect(m_objRegUI->m_qpbCaptureReg, &QPushButton::released,
            m_objRegImplmt,&RegImplementation::onCaptureReleased);

//    connect(m_objRegImplmt->objrestAPIController->m_objjsondatafetchworker->objcameraData, &cameraData::signalTrackTool,
//            m_objVerificationUi, &verificationui::setNewCoordOrientRefSpace);
//    connect(m_objRegImplmt->objrestAPIController->m_objjsondatafetchworker->objcameraData,&cameraData::refmarkerCoordMat,
//            m_objVerificationUi, &verificationui::setstltoRef);

}

//checks whether checkpoint/reg/verification is selected
void RegInterfaceClass::itemSelectedInTable(const QString &anatomy, int tableIndex)
{
    // Skip blank rows by adjusting the table index for non-blank items (even indices only: 0, 2, 4...)
    if (tableIndex % 2 == 0)
    {
        tableIndex /= 2;
    }

    qDebug() << "itemSelectedInTable" << anatomy << tableIndex;
    m_objRegImplmt->m_anatomy = anatomy;
    m_objRegImplmt->m_windowID = tableIndex;

    if (m_objRegImplmt->m_anatomy == "Femur" || m_objRegImplmt->m_anatomy == "Tibia")
    {
        m_objRegImplmt->LandmarkNames = m_objRegImplmt->readLandmarkNamesFromFile(m_objRegImplmt->m_anatomy == "Femur" ? m_objRegImplmt->femurLandmarklist : m_objRegImplmt->TibiaLandmarklist);

        switch (tableIndex)
        {
        case 0:  // Checkpoint
            m_objRegUI->m_qswThumbnail->setCurrentIndex(m_objRegImplmt->m_anatomy == "Femur" ? 0 : 0);
            m_objRegUI->m_qswThumbnail->hide();

            m_qswDisplay->setCurrentIndex(2);
            //m_objCheckpt->setCheckpointImage(m_anatomy == "Femur" ? "Femur" : "Tibia");
            m_objCheckpt->m_qswCheckpt->setCurrentIndex(m_objRegImplmt->m_anatomy == "Femur" ? 0 : 1);

            //onCheckpointClicked();//
            m_objRegImplmt->m_regUiLandmarkName = m_objRegImplmt->LandmarkNames[0];
            m_objRegImplmt->savePatientLandmarksToXML();
            break;

        case 1:  // Registration
            m_objRegUI->m_qswThumbnail->setCurrentIndex(m_objRegImplmt->m_anatomy == "Femur" ? 1 : 3);
            m_objRegUI->m_qswThumbnail->show();
            m_qswDisplay->setCurrentIndex(0);
            qDebug()<<"reg selected first time";

            m_objRegImplmt->onRegistrationClicked();
            break;

        case 2:  // Verification
            m_objRegUI->m_qswThumbnail->setCurrentIndex(m_objRegImplmt->m_anatomy == "Femur" ? 2 : 4);
            m_qswDisplay->setCurrentIndex(1);
            m_objRegUI->m_qswThumbnail->show();

            emit m_objRegImplmt->signalVerificationUi(m_objRegImplmt->m_anatomy, 1);
            break;

        default:
            qDebug() << "Warning: Unknown tableIndex" << tableIndex;
            break;
        }
    }
    else
    {
        qDebug() << "Warning: Unknown anatomy" << anatomy;
    }

    update();
}

//    // Restore the last selected index when the tab is switched
void RegInterfaceClass::regTabChanged(int index)
{
    if (index == 0) // Femur Tab
    {
        m_objRegUI->m_qtbwRegistration->setCurrentIndex(0);
        qDebug()<<"Tab changed to Femur**********";
        QModelIndex currentIndex = m_objRegUI->m_qtableviewFemurReg->selectionModel()->currentIndex();
        if (!currentIndex.isValid())
        {
            qDebug() << "Invalid selection in Femur";
            return;
        }
        int selectedRow = currentIndex.row();
        if (selectedRow % 2 == 0)
        {
            selectedRow /= 2;
        }
        //        qDebug()<<"selectedRow in F"<<selectedRow;

        if (selectedRow < 0 || selectedRow > 2) // Assuming only rows 0, 1, and 2 are valid
        {
            qDebug() << "Out-of-range selection for Femur with row" << selectedRow;
            return;
        }
        switch (selectedRow)
        {
        case 0:
            m_objRegUI->m_qswThumbnail->setCurrentIndex(0);
            m_objRegUI->m_qswThumbnail->hide();

            m_qswDisplay->setCurrentIndex(2);
            //m_objCheckpt->setCheckpointImage("Femur");
            m_objCheckpt->m_qswCheckpt->setCurrentIndex(0);
            break;
        case 1:
            m_objRegUI->m_qswThumbnail->setCurrentIndex(1);
            m_objRegUI->m_qswThumbnail->show();
            m_qswDisplay->setCurrentIndex(0);
            //onRegistrationClicked(); //added
            break;
        case 2:
            m_objRegUI->m_qswThumbnail->setCurrentIndex(2);
            m_objRegUI->m_qswThumbnail->show();
            m_qswDisplay->setCurrentIndex(1);
            break;
        }

        //qDebug() << "Thumbnail stack index for Femur:" << m_qswThumbnail->currentIndex();
        emit m_objRegUI->signalTableSelection("Femur", selectedRow * 2);

        m_objRegImplmt->switchData_f();
    }

    else if (index == 1) // Tibia Tab
    {
       m_objRegUI-> m_qtbwRegistration->setCurrentIndex(1);
        qDebug()<<"Tab changed to Tibia********";
        QModelIndex currentIndex = m_objRegUI->m_qtableviewTibiaReg->selectionModel()->currentIndex();
        if (!currentIndex.isValid())
        {
            qDebug() << "Invalid selection in Tibia";
            return;
        }
        int selectedRow = currentIndex.row();
        if (selectedRow % 2 == 0)
        {
            selectedRow /= 2;
        }
        //qDebug()<<"selectedRow in T"<<selectedRow;
        if (selectedRow < 0 || selectedRow > 2) // Assuming only rows 0, 1, and 2 are valid
        {
            qDebug() << "Out-of-range selection for Tibia with row" << selectedRow;
            return;
        }
        switch (selectedRow)
        {
        case 0:
            m_objRegUI->m_qswThumbnail->setCurrentIndex(0);
            m_objRegUI->m_qswThumbnail->hide();
            m_qswDisplay->setCurrentIndex(2);
//            m_objCheckpt->setCheckpointImage("Tibia");
            m_objCheckpt->m_qswCheckpt->setCurrentIndex(1);
            break;
        case 1:
            m_objRegUI->m_qswThumbnail->setCurrentIndex(3);
            m_objRegUI->m_qswThumbnail->show();
            m_qswDisplay->setCurrentIndex(0);
            break;
        case 2:
            m_objRegUI->m_qswThumbnail->setCurrentIndex(4);
            m_objRegUI->m_qswThumbnail->show();
            m_qswDisplay->setCurrentIndex(1);
            break;
        }

        //qDebug() << "Thumbnail stack index for Tibia:" << m_qswThumbnail->currentIndex();
        emit m_objRegUI->signalTableSelection("Tibia", selectedRow * 2);
        m_objRegImplmt->switchData();
    }
}
