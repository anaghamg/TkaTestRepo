/*
    File Name       : RegistrationUI.cpp
    Project Name    : TKA Robotic Surgery
    Created         : 16-08-2024
    Description     : Source file containing implementation for
                      Registration UI layout
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#include "registrationui.h"

RegistrationUI::RegistrationUI(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"RegistrationUI class";
    SPDLOG_INFO("Inside RegistrationUI");

    m_objCustomTableView = new CustomTableView(CustomTableView::TypeB);
    m_objThumbnailView = new CustomThumbnailView;

    //------------- right panel layout --------------//
    m_qtableviewFemurReg = new QTableView;
    m_qtableviewFemurReg->setStyleSheet("QTableView { background-color: transparent; font-size:20px; font-family-Inter; font-weight:normal; border-color:transparent;}"
                                        "QTableView::item:hover { "
                                        "  background-color:transparent;  border-color:transparent;" // Hover color
                                        "} "
                                        "QTableView::item {    background-color: transparent; border-color:transparent;} "
                                        "QTableView::item:hover {  background-color: transparent; border-color:transparent;} "
                                        "QTableView::item:selected { "
                                        "    background-color: transparent;  border-color:transparent;"  // Selection color
                                        "}");
    m_qtableviewFemurReg->setFixedHeight(200);

    m_qtableviewFemurReg->setRowHeight(0,42);
    m_qtableviewFemurReg->setRowHeight(1,0);
    m_qtableviewFemurReg->setRowHeight(2,42);
    m_qtableviewFemurReg->setRowHeight(3,0);
    m_qtableviewFemurReg->setRowHeight(4,42);

    QVBoxLayout* qvblFemurReg = new QVBoxLayout;
    qvblFemurReg->addSpacing(10);
    qvblFemurReg->addWidget(m_qtableviewFemurReg);
    QWidget* m_qwFemurReg = new QWidget;
    m_qwFemurReg->setLayout(qvblFemurReg);
    m_qwFemurReg->setStyleSheet("QWidget:hover{background-transparent;}");

    m_qtableviewTibiaReg = new QTableView;
    m_qtableviewTibiaReg->setFixedHeight(200);
    m_qtableviewTibiaReg->setStyleSheet("QTableView { background-color: transparent; font-size:20px;font-family-Inter; font-weight:normal;  border-color:transparent;}"
                                        "QTableView::item { background-color: transparent; }"
                                        "QTableView::item:hover { "
                                        "   border-color:transparent;  background-color: transparent; " // Hover color
                                        "} "
                                        "QTableView::item:selected { "
                                        "    border-color:transparent;  background-color: transparent; "  // Selection color
                                        "}");

    m_qtableviewTibiaReg->setRowHeight(0,42);
    m_qtableviewTibiaReg->setRowHeight(1,0);
    m_qtableviewTibiaReg->setRowHeight(2,42);
    m_qtableviewTibiaReg->setRowHeight(3,0);
    m_qtableviewTibiaReg->setRowHeight(4,42);

    QVBoxLayout* qvblTibiaReg = new QVBoxLayout;
    qvblTibiaReg->addSpacing(10);
    qvblTibiaReg->addWidget(m_qtableviewTibiaReg,0,Qt::AlignVCenter);
    QWidget* m_qwTibiaReg = new QWidget;
    m_qwTibiaReg->setLayout(qvblTibiaReg);

    //place the tables into tab widget
    m_qtbwRegistration = new QTabWidget;
    m_qtbwRegistration->setObjectName("RegistrationTab");
    m_qtbwRegistration->tabBar()->setObjectName("AnnotationTabBar");
    //    // m_qtbwRegistration->setStyleSheet("QTabWidget::tab-bar {length:2000px; width:1000px;}");
    m_qtbwRegistration->insertTab(0,m_qwFemurReg,"Femur");
    m_qtbwRegistration->insertTab(1,m_qwTibiaReg,"Tibia");
    m_qtbwRegistration->setCurrentIndex(0);

    m_qpbCaptureReg = new QPushButton("Capture Point");
    m_qpbCaptureReg->setObjectName("capturepointreg");

    //m_qpbCaptureReg->setCheckable(true);

    m_qpbBack = new QPushButton("Back");
    m_qpbNext = new QPushButton("Next");
    m_qpbBack->setObjectName("backButtonreg");
    m_qpbNext->setObjectName("nextButtonreg");

    m_qpbBack->setCheckable(true);
    m_qpbNext->setCheckable(true);

    /// adding progress bar for hip center RUPIKA
    m_progressBar = new QProgressBar;
    m_progressBar->setRange(0, 100);  // Set the range from 0 to 100
    m_progressBar->setValue(0);       // Initial value is 0
    m_progressBar->setGeometry(10, 10, 200, 30); // Set geometry as needed

    QHBoxLayout* qhblBackNext = new QHBoxLayout;
    qhblBackNext->addWidget(m_qpbBack);
    qhblBackNext->addWidget(m_qpbNext);

    QVBoxLayout* qvblReg = new QVBoxLayout;
    qvblReg->addWidget(m_qtbwRegistration,40);
    qvblReg->addWidget(m_progressBar);//rupika
    qvblReg->addSpacing(40);//parvathy
    qvblReg->addWidget(m_qpbCaptureReg,10);
    qvblReg->setSpacing(24);//parvathy
    qvblReg->addLayout(qhblBackNext);

    /// marker window on right --------------------------------------------- rupika
    m_qvtkToolwin = new QVTKOpenGLWidget;
    //m_qvtkToolwin->SetRenderWindow(m_openGLToolWin);
    //m_openGLToolWin->AddRenderer(m_qvtkToolwinRen);
    //showMarkers();

    QSlider* qsliderTrackerIndicator = new QSlider(Qt::Horizontal);
    qsliderTrackerIndicator->setObjectName("sliderReg");

    QLabel* qlblF = new QLabel("F");
    QLabel* qlblP = new QLabel("P");
    qlblF->setAlignment(Qt::AlignCenter);
    qlblP->setAlignment(Qt::AlignCenter);
    qlblF->setObjectName("m_objlblF");
    qlblP->setObjectName("m_objlblP");

    qlblF->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    qlblP->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QHBoxLayout* qhblFT = new QHBoxLayout;
    qhblFT->setContentsMargins(0,0,0,0);
    qhblFT->setSpacing(0);
    qhblFT->setMargin(0);

    qhblFT->addWidget(qlblF);
    qhblFT->addWidget(qlblP);

    QVBoxLayout* qvblRightPanel = new QVBoxLayout;
    qvblRightPanel->setContentsMargins(29,0,29,20);//parvathy
    qvblRightPanel->addLayout(qvblReg,40);
    qvblRightPanel->addWidget(m_qvtkToolwin,25);
    qvblRightPanel->addWidget(qsliderTrackerIndicator,15);
    qvblRightPanel->addLayout(qhblFT,5);

    QFrame* frame_registration = new QFrame;
    frame_registration->setLayout(qvblRightPanel);
    frame_registration->setObjectName("frame_registration");
    frame_registration->setFixedWidth(480);
    QVBoxLayout* qvblframereg = new QVBoxLayout;
    qvblframereg->addWidget(frame_registration);

    //--------------------- left side ---------------------//

    QWidget* qwDummy = new QWidget;
    qwDummy->setObjectName("qwDummy");
    qwDummy->setStyleSheet("#qwDummy {"
                           "background-color: red;"
                           "}");

    m_qtableviewRegFemur = new QListView;
    m_qtableviewVerFemur = new QListView;
    m_qtableviewRegTibia = new QListView;
    m_qtableviewVerTibia = new QListView;

    //-------------- set stack index for right widget --------------//

    m_qswThumbnail = new QStackedWidget;
    m_qswThumbnail->insertWidget(0,qwDummy);
    m_qswThumbnail->insertWidget(1,m_qtableviewRegFemur);
    m_qswThumbnail->insertWidget(2,m_qtableviewVerFemur);
    m_qswThumbnail->insertWidget(3,m_qtableviewRegTibia);    //added 31-10-2024
    m_qswThumbnail->insertWidget(4,m_qtableviewVerTibia);    //added 31-10-2024
    m_qswThumbnail->setCurrentIndex(0);

    m_qswThumbnail->hide();

    m_qswThumbnail->setFixedWidth(170);

    //------------------ main layout-----------------//
    QHBoxLayout* qhblMain = new QHBoxLayout;
    qhblMain->addWidget(m_qswThumbnail,10);
    qhblMain->addLayout(qvblframereg,90);
    this->setLayout(qhblMain);

    //-------------------------------------------------------------------------------
    //customize tableview uisng the custom class
    //right panel table
    m_objCustomTableView->setTableView(m_qtableviewFemurReg);
    m_qtableviewFemurReg->setItemDelegate(m_objCustomTableView);
    m_objCustomTableView->setTableView(m_qtableviewTibiaReg                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               );
    m_qtableviewTibiaReg->setItemDelegate(m_objCustomTableView);

    model1 = new QStandardItemModel;
    model2 = new QStandardItemModel;

    // Populate the table with items
    loadTableViewMenu(m_qtableviewFemurReg, model1, m_qstrFemurMenu);
    loadTableViewMenu(m_qtableviewTibiaReg, model2, m_qstrTibiaMenu);

    //tableview appearance
    setTableViewAppearance(m_qtableviewFemurReg);
    setTableViewAppearance(m_qtableviewTibiaReg);
    //-------------------------------------------------------------------------------

    //------------------ Femur thumbnails---------------//
    modelRegFemur = new QStandardItemModel;
    modelVerFemur = new QStandardItemModel;

    //------------------ Tibia thumbnails---------------//
    modelRegTibia = new QStandardItemModel;
    modelVerTibia = new QStandardItemModel;
    //---------------------------------------------------

    m_qtableviewRegFemur->setModel(modelRegFemur);
    m_qtableviewVerFemur->setModel(modelVerFemur);
    m_qtableviewRegTibia->setModel(modelRegTibia);
    m_qtableviewVerTibia->setModel(modelVerTibia);

    //draw delgate for thumbnail view
    m_qtableviewRegFemur->setItemDelegate(m_objThumbnailView);
    m_qtableviewVerFemur->setItemDelegate(m_objThumbnailView);
    m_qtableviewRegTibia->setItemDelegate(m_objThumbnailView);
    m_qtableviewVerTibia->setItemDelegate(m_objThumbnailView);

    connect(m_qtableviewRegFemur->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &RegistrationUI::onSelectionChanged);
    connect(m_qtableviewVerFemur->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &RegistrationUI::onSelectionChanged);
    connect(m_qtableviewRegTibia->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &RegistrationUI::onSelectionChanged);
    connect(m_qtableviewVerTibia->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &RegistrationUI::onSelectionChanged);

    m_objThumbnailView->setTableView(m_qtableviewRegFemur);
    m_objThumbnailView->setTableView(m_qtableviewVerFemur);
    m_objThumbnailView->setTableView(m_qtableviewRegTibia);
    m_objThumbnailView->setTableView(m_qtableviewVerTibia);

    m_qtableviewRegFemur->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_qtableviewRegFemur->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_qtableviewRegTibia->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_qtableviewRegTibia->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_qtableviewVerFemur->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_qtableviewVerFemur->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_qtableviewVerTibia->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_qtableviewVerTibia->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Configure QListView settings
    QList<QListView*> listViews = { m_qtableviewRegFemur, m_qtableviewVerFemur, m_qtableviewRegTibia ,m_qtableviewVerTibia };
    for (auto listView : listViews)
    {
        listView->setViewMode(QListView::ListMode);
        //         listView->setIconSize(QSize(130, 130));
        listView->setIconSize(QSize(110, 110));
        listView->setUniformItemSizes(true);
        listView->setSpacing(25);//parvathy
    }

    //thumbnail table
    // Load items from the RegistrationThumbnails file
    //femur thumbnail location
    qstrRegFemurThumbnail = QDir::currentPath() +"/thumbnails/registrationscreen/Femur" ;
    qstrVerFemurThumbnail = QDir::currentPath() +"/thumbnails/verificationscreen/Femur" ;
    //tibia thumbnail location
    qstrRegTibiaThumbnail = QDir::currentPath() +"/thumbnails/registrationscreen/Tibia" ;
    qstrVerTibiaThumbnail = QDir::currentPath() +"/thumbnails/verificationscreen/Tibia" ;

    // Set page sizes and current page for each list
    m_pageSize = 5;
    m_currentPage1 = 0;
    m_currentPage2 = 0;
    m_currentPage3 = 0;
    m_currentPage4 = 0;

    // Load files for each list
    loadFilesForList(qstrRegFemurThumbnail, m_fileList1);
    loadFilesForList(qstrVerFemurThumbnail, m_fileList2);
    loadFilesForList(qstrRegTibiaThumbnail, m_fileList3);
    loadFilesForList(qstrVerTibiaThumbnail, m_fileList4);

    // Display the first page for each list
    displayPage(m_currentPage1, m_qtableviewRegFemur,qstrRegFemurThumbnail, modelRegFemur, m_fileList1, m_currentPage1);
    displayPage(m_currentPage2, m_qtableviewVerFemur,qstrVerFemurThumbnail, modelVerFemur, m_fileList2, m_currentPage2);
    displayPage(m_currentPage3, m_qtableviewRegTibia,qstrRegTibiaThumbnail, modelRegTibia, m_fileList3, m_currentPage3);
    displayPage(m_currentPage4, m_qtableviewVerTibia,qstrVerTibiaThumbnail, modelVerTibia, m_fileList4, m_currentPage4);

    //set thumbnail size
    m_qtableviewRegFemur->setObjectName("regthumbnailtable");
    m_qtableviewVerFemur->setObjectName("regthumbnailtable");
    m_qtableviewRegTibia->setObjectName("regthumbnailtable");
    m_qtableviewVerTibia->setObjectName("regthumbnailtable");

    //--------------- right panel connects -----------------//
    connect(m_qtableviewFemurReg->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &RegistrationUI::onTableMenuSelectionChanged);

    connect(m_qtableviewTibiaReg->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &RegistrationUI::onTableMenuSelectionChanged);

    //--------------- thumbnail connects -----------------//
    //femur
    connect(m_qtableviewRegFemur, &QListView::clicked, this, &RegistrationUI::onItemClicked1);
    connect(m_qtableviewVerFemur, &QListView::clicked, this, &RegistrationUI::onItemClicked2);
    //tibia
    connect(m_qtableviewRegTibia, &QListView::clicked, this, &RegistrationUI::onItemClicked3);
    connect(m_qtableviewVerTibia, &QListView::clicked, this, &RegistrationUI::onItemClicked4);

    //on capture click change colour to green
    connect(m_qpbCaptureReg, &QPushButton::clicked,this,&RegistrationUI::onCaptureClicked);
}


void RegistrationUI::loadFilesForList(const QString &path, QFileInfoList &fileList)
{
    QDir dir(path);
    if (dir.exists())
    {
        // Get all "R" image files in the directory
        QFileInfoList unsortedFileList = dir.entryInfoList(QStringList() << "R*.png" << "R*.jpg" << "R*.jpeg", QDir::Files);

        // Sort the file list numerically by the suffix number
        std::sort(unsortedFileList.begin(), unsortedFileList.end(), [](const QFileInfo &a, const QFileInfo &b) {
            QRegularExpression re("R(\\d+)");
            QRegularExpressionMatch matchA = re.match(a.fileName());
            QRegularExpressionMatch matchB = re.match(b.fileName());

            if (matchA.hasMatch() && matchB.hasMatch()) {
                int numA = matchA.captured(1).toInt();
                int numB = matchB.captured(1).toInt();
                return numA < numB;
            }
            return a.fileName() < b.fileName();
        });

        // Store the sorted list
        fileList = unsortedFileList;

        // Debug: Print the sorted filenames
        //        for (const QFileInfo &fileInfo : fileList)
        //        {
        //qDebug() << fileInfo.fileName();
        //        }
    }
}

void RegistrationUI::displayPage(int page, QListView* listView, QString path,QStandardItemModel* model,
                                 QFileInfoList &fileList, int &currentPage)
{
    // Clear the model
    model->clear();

    // Calculate the range of items to display on the current page
    int startIndex = page * (m_pageSize - 2); // Leave 1 spot for U/D
    int endIndex = qMin(startIndex + (m_pageSize - 1), fileList.size());

    // Add "U" icon if it's not the first page
    if (page > 0) {
        //QStandardItem* upItem = new QStandardItem(QIcon(path + "/U.png"), "Up");
        QStandardItem* upItem = new QStandardItem(QIcon(path + "/U.png"), "");
        upItem->setData("U");  // Store data to identify the item as "Up"
        model->appendRow(upItem);

        for (int i = startIndex+1; i < endIndex; ++i)
        {
            QString fileName = fileList[i].fileName();   // Get the full file name (e.g., "R5.png")
            QString baseName = fileList[i].baseName();   // Get only the base name (e.g., "R5")
            //qDebug()<<"filenmae"<<fileName<<baseName;
            QStandardItem* item = new QStandardItem(QIcon(fileList[i].absoluteFilePath()), "");  // Empty text for display
            item->setData(baseName, Qt::UserRole + 2);  // Store the base file name without extension

            model->appendRow(item);
        }

    }
    else
    {
        for (int i = startIndex; i < endIndex; ++i)
        {
            QString fileName = fileList[i].fileName();   // Get the full file name (e.g., "R5.png")
            QString baseName = fileList[i].baseName();   // Get only the base name (e.g., "R5")
            //qDebug()<<"filenmae"<<fileName<<baseName;
            QStandardItem* item = new QStandardItem(QIcon(fileList[i].absoluteFilePath()), "");  // Empty text for display
            item->setData(baseName, Qt::UserRole + 2);  // Store the base file name without extension

            model->appendRow(item);
        }
    }

    // Add "D" icon if it's not the last page
    if (endIndex < fileList.size()) {
        //        QStandardItem* downItem = new QStandardItem(QIcon(path + "/D.png"), "Down");
        QStandardItem* downItem = new QStandardItem(QIcon(path + "/D.png"), "");
        downItem->setData("D");  // Store data to identify the item as "Down"
        model->appendRow(downItem);
    }

    //    //setting first thumbnail as default selected items for F/T
    //        QModelIndex firstIndex = model->index(0, 0); // First row, first column
    //        if (firstIndex.isValid())
    //        {
    //            QItemSelectionModel *selectionModel = listView->selectionModel();
    //            selectionModel->setCurrentIndex(firstIndex, QItemSelectionModel::Select);
    //        }

    //        if(listView == m_qtableviewRegFemur)
    //        {
    //            qDebug()<<"m_qtableviewRegFemur";
    //            emit signalThumbnailSelection("Femur Registration","R", 0);
    //        }





}

void RegistrationUI::onItemClicked1(const QModelIndex &index)
{
    QString data = index.data(Qt::UserRole + 1).toString();

    if (data == "U") {
        if (m_currentPage1 > 0) {
            m_currentPage1--;
            displayPage(m_currentPage1, m_qtableviewRegFemur,qstrRegFemurThumbnail, modelRegFemur, m_fileList1, m_currentPage1);
            if (AllselectedIndexesRegFemur.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewRegFemur,AllselectedIndexesRegFemur, modelRegFemur,m_currentPage1);

            }        }
    } else if (data == "D") {
        if (m_currentPage1 < (m_fileList1.size() - 1) / (m_pageSize - 1)) {
            m_currentPage1++;

            displayPage(m_currentPage1, m_qtableviewRegFemur, qstrRegFemurThumbnail,modelRegFemur, m_fileList1, m_currentPage1);
            if (AllselectedIndexesRegFemur.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewRegFemur,AllselectedIndexesRegFemur, modelRegFemur,m_currentPage1);

            }        }
    }

    else  if (data == "") {
        QString baseName = index.data(Qt::UserRole + 2).toString();  // Get the base file name (e.g., "R5")
        bool ok;
        int itemNumber = baseName.mid(1).toInt(&ok);  // Extract the integer part after "R"

        if (ok) {
            //qDebug() << "Selected thumbnail in femur reg :" << itemNumber;  // Debug output for item number
            emit signalThumbnailSelection("Femur Registration","R", itemNumber);
        } else {
            qDebug() << "Conversion failed for:" << baseName;
        }
    }
}

void RegistrationUI::onItemClicked2(const QModelIndex &index) {
    QString data = index.data(Qt::UserRole + 1).toString();
    if (data == "U") {
        if (m_currentPage2 > 0) {
            m_currentPage2--;
            displayPage(m_currentPage2, m_qtableviewVerFemur,qstrVerFemurThumbnail, modelVerFemur, m_fileList2, m_currentPage2);
            if (AllselectedIndexesVerFemur.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewVerFemur,AllselectedIndexesVerFemur, modelVerFemur,m_currentPage2);

            }        }
    } else if (data == "D") {
        if (m_currentPage2 < (m_fileList2.size() - 1) / (m_pageSize - 1)) {
            m_currentPage2++;
            displayPage(m_currentPage2, m_qtableviewVerFemur,qstrVerFemurThumbnail, modelVerFemur, m_fileList2, m_currentPage2);
            if (AllselectedIndexesVerFemur.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewVerFemur,AllselectedIndexesVerFemur, modelVerFemur,m_currentPage2);

            }        }
    }

    else  if (data == "") {
        QString baseName = index.data(Qt::UserRole + 2).toString();  // Get the base file name (e.g., "R5")
        bool ok;
        int itemNumber = baseName.mid(1).toInt(&ok);  // Extract the integer part after "R"

        if (ok) {
            //qDebug() << "Selected thumbnail in femur ver : " << itemNumber;  // Debug output for item number
            emit signalThumbnailSelection("Femur Verification","V", itemNumber);
        } else {
            qDebug() << "Conversion failed for:" << baseName;
        }
    }
}

void RegistrationUI::onItemClicked3(const QModelIndex &index) {
    QString data = index.data(Qt::UserRole + 1).toString();
    if (data == "U") {
        if (m_currentPage3 > 0) {
            m_currentPage3--;
            displayPage(m_currentPage3, m_qtableviewRegTibia,qstrRegTibiaThumbnail, modelRegTibia, m_fileList3, m_currentPage3);
            if (AllselectedIndexesRegTibia.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewRegTibia,AllselectedIndexesRegTibia, modelRegTibia,m_currentPage3);

            }
        }
    } else if (data == "D") {
        if (m_currentPage3 < (m_fileList3.size() - 1) / (m_pageSize - 1)) {
            m_currentPage3++;
            displayPage(m_currentPage3, m_qtableviewRegTibia,qstrRegTibiaThumbnail, modelRegTibia, m_fileList3, m_currentPage3);
            if (AllselectedIndexesRegTibia.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewRegTibia,AllselectedIndexesRegTibia, modelRegTibia,m_currentPage3);

            }
        }
    }

    else  if (data == "") {
        QString baseName = index.data(Qt::UserRole + 2).toString();  // Get the base file name (e.g., "R5")
        bool ok;
        int itemNumber = baseName.mid(1).toInt(&ok);  // Extract the integer part after "R"

        qDebug()<<" ---------------------------------------------------------- itemNumber"<<itemNumber;
        if (ok) {
            //qDebug() << "Selected thumbnail in tibia reg :" << itemNumber;  // Debug output for item number
            emit signalThumbnailSelection("Tibia Registration","R", itemNumber);
        } else {
            qDebug() << "Conversion failed for:" << baseName;
        }
    }
}

void RegistrationUI::onItemClicked4(const QModelIndex &index) {
    QString data = index.data(Qt::UserRole + 1).toString();
    if (data == "U") {
        if (m_currentPage1 > 0) {
            m_currentPage1--;
            displayPage(m_currentPage1, m_qtableviewVerTibia,qstrVerTibiaThumbnail, modelVerTibia, m_fileList1, m_currentPage1);
            if (AllselectedIndexesVerTibia.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewVerTibia,AllselectedIndexesVerTibia, modelVerTibia,m_currentPage1);

            }        }
    } else if (data == "D") {
        if (m_currentPage1 < (m_fileList1.size() - 1) / (m_pageSize - 1)) {
            m_currentPage1++;
            displayPage(m_currentPage1, m_qtableviewVerTibia,qstrVerTibiaThumbnail, modelVerTibia, m_fileList1, m_currentPage1);
            if (AllselectedIndexesVerTibia.count()>0)
            {
                retainThumbnailItemColour(m_qtableviewVerTibia,AllselectedIndexesVerTibia, modelVerTibia,m_currentPage1);

            }        }
    }
    else  if (data == "") {
        QString baseName = index.data(Qt::UserRole + 2).toString();  // Get the base file name (e.g., "R5")
        bool ok;
        int itemNumber = baseName.mid(1).toInt(&ok);  // Extract the integer part after "R"

        if (ok) {
            //qDebug() << "Selected thumbnail in tibia ver :" << itemNumber;  // Debug output for item number
            emit signalThumbnailSelection("Tibia Verification","V", itemNumber);
        } else {
            qDebug() << "Conversion failed for:" << baseName;
        }
    }
}

void RegistrationUI::loadTableViewMenu(QTableView *tableView, QStandardItemModel *model,
                                       const QVector<QString> &tableItem)
{
    model->setRowCount(5);
    model->setColumnCount(1);

    QStandardItem* item1  = new QStandardItem("Checkpoint");
    QStandardItem* item2  = new QStandardItem("Registration");
    QStandardItem* item3  = new QStandardItem("Verification");

    model->setItem(0,0,item1);
    model->setItem(2,0,item2);
    model->setItem(4,0,item3);

    //parvathy
    for (int i=1; i<5 ;i=i+2)
    {
        QStandardItem* lineImage = new QStandardItem;
        QString imagePath = ":/res/icons/blankrowimage_1.PNG";
        QImage image(imagePath);

        int thumbSize = /*rowht +*/20;

        // Scale the image based on the dynamically determined thumbnail size
        QPixmap scaledPixmap = QPixmap::fromImage(image).scaled(QSize(thumbSize, thumbSize),
                                                                Qt::KeepAspectRatio);
        lineImage->setData(QVariant(scaledPixmap), Qt::DecorationRole);
        model->setItem(i , 0, lineImage);
    }
    tableView->setModel(model);

    //setting checkpoint as default selected items for F/T
    QModelIndex firstIndex = model->index(0, 0); // First row, first column
    if (firstIndex.isValid())
    {
        QItemSelectionModel *selectionModel = tableView->selectionModel();
        selectionModel->setCurrentIndex(firstIndex, QItemSelectionModel::Select);
    }
}

void RegistrationUI::onTableMenuSelectionChanged(const QModelIndex &current,
                                                 const QModelIndex &previous)
{
    Q_UNUSED(previous);

    int index = current.row();
    qDebug()<<"onTableMenuSelectionChanged";
    QItemSelectionModel *selectionModel = qobject_cast<QItemSelectionModel *>(sender());
    if (selectionModel == m_qtableviewFemurReg->selectionModel())
    {
        //m_qtableviewTibiaReg->clearSelection();//commented for now
        emit signalTableSelection("Femur", index);
    }
    else if (selectionModel == m_qtableviewTibiaReg->selectionModel())
    {
        //m_qtableviewFemurReg->clearSelection(); //commented for now
        emit signalTableSelection("Tibia", index);
    }
}

void RegistrationUI::onCaptureClicked()
{
    //femur thumbnail
    changeThumbnailItemColour(m_qtableviewRegFemur, modelRegFemur,m_currentPage1);
    changeThumbnailItemColour(m_qtableviewVerFemur, modelVerFemur, m_currentPage2);

    //tibia thumbnail
    changeThumbnailItemColour(m_qtableviewRegTibia, modelRegTibia, m_currentPage3);
    changeThumbnailItemColour(m_qtableviewVerTibia, modelVerTibia, m_currentPage4);

}

void RegistrationUI::setTableViewAppearance(QTableView *tableView)
{
    tableView->setShowGrid(false);
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->horizontalHeader()->setVisible(false);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setStretchLastSection(true);
    //tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//will stretch fully

    //adjust height to show full contents
    tableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void RegistrationUI::changeTableItemColour(QTableView *tableView, QStandardItemModel* model)
{
    //qDebug()<<"changeTableItemColour";
    QModelIndex selectedIndex = tableView->selectionModel()->currentIndex();
    if(selectedIndex.isValid())
    {
        m_objCustomTableView->setCaptureIndex(selectedIndex);

        int nextRow = selectedIndex.row()+1;
        if(nextRow <= model1->rowCount())
        {
            QModelIndex nextIndex = model1->index(nextRow,0);
            //disabled for now
            //tableView->selectionModel()->setCurrentIndex(nextIndex, QItemSelectionModel::SelectCurrent);
        }
    }
}

void RegistrationUI::changeThumbnailItemColour(QListView *tableView, QStandardItemModel *model, int pgnumber)
{
    QItemSelectionModel* selectionModel = tableView->selectionModel();
    QModelIndex selectedIndex = tableView->selectionModel()->currentIndex();

    if(selectedIndex.isValid())
    {
        QString baseName = selectedIndex.data(Qt::UserRole + 2).toString();  // Get the base file name (e.g., "R5")
        bool ok;
        int itemNumber = baseName.mid(1).toInt(&ok);  // Extract the integer part after "R"
        if (selectionModel == m_qtableviewVerTibia->selectionModel())
        {
            if (AllselectedIndexesVerTibia.contains(pgnumber))
            {
                // If it exists, append the new indexes
                AllselectedIndexesVerTibia[pgnumber].append(itemNumber);
            }
            else
            {
                // If it doesn't exist, create a new QList and insert it
                QList<int> newList;
                newList.append(itemNumber);
                AllselectedIndexesVerTibia.insert(pgnumber, newList);
            }
        }
        if (selectionModel == m_qtableviewRegTibia->selectionModel())
        {
            if (AllselectedIndexesRegTibia.contains(pgnumber)) {
                // If it exists, append the new indexes
                AllselectedIndexesRegTibia[pgnumber].append(itemNumber);
            } else {
                // If it doesn't exist, create a new QList and insert it
                QList<int> newList;
                newList.append(itemNumber);
                AllselectedIndexesRegTibia.insert(pgnumber, newList);
            }
        }
        if (selectionModel == m_qtableviewVerFemur->selectionModel())
        {
            if (AllselectedIndexesVerFemur.contains(pgnumber)) {
                // If it exists, append the new indexes
                AllselectedIndexesVerFemur[pgnumber].append(itemNumber);
            } else {
                // If it doesn't exist, create a new QList and insert it
                QList<int> newList;
                newList.append(itemNumber);
                AllselectedIndexesVerFemur.insert(pgnumber, newList);
            }
        }
        if (selectionModel == m_qtableviewRegFemur->selectionModel())
        {
            if (AllselectedIndexesRegFemur.contains(pgnumber)) {
                // If it exists, append the new indexes
                AllselectedIndexesRegFemur[pgnumber].append(itemNumber);
            } else {
                // If it doesn't exist, create a new QList and insert it
                QList<int> newList;
                newList.append(itemNumber);
                AllselectedIndexesRegFemur.insert(pgnumber, newList);
            }
        }

        m_objThumbnailView->setCaptureIndex(selectedIndex);

        // Emit dataChanged for the selected index so it triggers a repaint of the row
        model->dataChanged(selectedIndex, selectedIndex);

        // Force repaint of the view to update the colors instantly
        tableView->viewport()->update();

        int nextRow = selectedIndex.row() + 1;
        int column = selectedIndex.column(); // Keep the same column

        if(nextRow <= model->rowCount())
        {
            //qDebug()<<"index next row";
            QModelIndex nextIndex = model->index(nextRow,0);
            QVariant nextData = model->data(nextIndex, Qt::UserRole + 2);
            //            //disabled for now
            //            if (nextData.toString() != "")
            //            {
            //                tableView->selectionModel()->setCurrentIndex(nextIndex, QItemSelectionModel::SelectCurrent);
            //            }
        }

        else
        {
            qDebug()<<"thumbnail index not valid";
        }
    }
}

void RegistrationUI::retainThumbnailItemColour(QListView* tableView,QMap<int, QList<int>>& Allselindex, QStandardItemModel *model, int pgnumber)
{
    QStandardItemModel *newmodel = new QStandardItemModel(10, 1); // 10 rows, 2 columns
    QItemSelectionModel* selectionModel = tableView->selectionModel();
    int retainindex;
    if (pgnumber==0)
    {
        const QList<int>& list = Allselindex[0];
        for (int selindex : list)
        {
            retainindex = selindex-1;
            //qDebug() << "Value in the list:" << selindex<<retainindex;
            QModelIndex selectedIndex = model->index(retainindex, 0);
            //qDebug()<<"selectedIndex"<<selectedIndex;
            if(selectedIndex.isValid())
            {
                m_objThumbnailView->setCaptureIndex(selectedIndex);
                // Emit dataChanged for the selected index so it triggers a repaint of the row
                model->dataChanged(selectedIndex, selectedIndex);
                // Force repaint of the view to update the colors instantly
                tableView->viewport()->update();
            }
        }


    }
    else if (pgnumber==1)
    {
        const QList<int>& list = Allselindex[1];
        for (int selindex : list)
        {
            retainindex = selindex-1;
            if (selindex==5 )
            {
                retainindex=1;
            }
            if (selindex==6)
            {
                retainindex=2;
            }
            if (selindex==7  )
            {
                retainindex=3;
            }
            //qDebug() << "Value in the list:" << selindex<<retainindex;
            QModelIndex selectedIndex = model->index(retainindex, 0);
            //qDebug()<<"selectedIndex"<<selectedIndex;
            if(selectedIndex.isValid())
            {
                m_objThumbnailView->setCaptureIndex(selectedIndex);
                // Emit dataChanged for the selected index so it triggers a repaint of the row
                model->dataChanged(selectedIndex, selectedIndex);
                // Force repaint of the view to update the colors instantly
                tableView->viewport()->update();
            }
        }
    }
    else if (pgnumber==2)
    {
        const QList<int>& list = Allselindex[2];
        for (int selindex : list)
        {
            retainindex = selindex-1;
            if (selindex==8 )
            {
                retainindex=1;
            }
            if (selindex==9 )
            {
                retainindex=2;
            }
            if (selindex==10   )
            {
                retainindex=3;
            }
            //qDebug() << "Value in the list:" << selindex<<retainindex;
            QModelIndex selectedIndex = model->index(retainindex, 0);
            //qDebug()<<"selectedIndex"<<selectedIndex;
            if(selectedIndex.isValid())
            {
                m_objThumbnailView->setCaptureIndex(selectedIndex);
                // Emit dataChanged for the selected index so it triggers a repaint of the row
                model->dataChanged(selectedIndex, selectedIndex);
                // Force repaint of the view to update the colors instantly
                tableView->viewport()->update();
            }
        }
    }
    else  if (pgnumber==3) {
        const QList<int>& list = Allselindex[3];
        for (int selindex : list)
        {
            retainindex = selindex-1;
            if (selindex==11)
            {
                retainindex=1;
            }
            if (selindex==12 )
            {
                retainindex=2;
            }
            if (selindex==13  )
            {
                retainindex=3;
            }
            QModelIndex selectedIndex = model->index(retainindex, 0);
            if(selectedIndex.isValid())
            {
                m_objThumbnailView->setCaptureIndex(selectedIndex);
                // Emit dataChanged for the selected index so it triggers a repaint of the row
                model->dataChanged(selectedIndex, selectedIndex);
                // Force repaint of the view to update the colors instantly
                tableView->viewport()->update();
            }
        }
    }
    qDebug()<<"retainindex"<<retainindex;
}

void RegistrationUI::onSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    QItemSelectionModel *selectionModel = qobject_cast<QItemSelectionModel *>(sender());
    if (selectionModel == m_qtableviewRegFemur->selectionModel())
    {
        if (previous.isValid())
        {
            // Emit dataChanged for the previous index to revert to white if not captured
            emit modelRegFemur->dataChanged(previous, previous);
        }
        if (current.isValid())
        {
            // Emit dataChanged for the current index to update the selection
            emit modelRegFemur->dataChanged(current, current);
        }
    }

    else if (selectionModel == m_qtableviewVerFemur->selectionModel())
    {
        if (previous.isValid())
        {
            // Emit dataChanged for the previous index to revert to white if not captured
            emit modelVerFemur->dataChanged(previous, previous);
        }

        if (current.isValid())
        {
            // Emit dataChanged for the current index to update the selection
            emit modelVerFemur->dataChanged(current, current);
        }
    }

    else if (selectionModel == m_qtableviewRegTibia->selectionModel())
    {
        if (previous.isValid())
        {
            // Emit dataChanged for the previous index to revert to white if not captured
            emit modelRegTibia->dataChanged(previous, previous);
        }
        if (current.isValid())
        {
            // Emit dataChanged for the current index to update the selection
            emit modelRegTibia->dataChanged(current, current);
        }
    }


    else if (selectionModel == m_qtableviewVerTibia->selectionModel())
    {
        if (previous.isValid())
        {
            // Emit dataChanged for the previous index to revert to white if not captured
            emit modelVerTibia->dataChanged(previous, previous);
        }
        if (current.isValid())
        {
            // Emit dataChanged for the current index to update the selection
            emit modelVerTibia->dataChanged(current, current);
        }
    }
}

