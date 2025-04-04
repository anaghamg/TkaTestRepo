#include "annotation.h"

Annotation::Annotation(QWidget *parent) : QWidget(parent)
{
    //added by anagha 30-07-2024

    qDebug()<<"Annotation class UI";

    SPDLOG_INFO("Inside annotation");

    //------------- Femur landmark point selection layout-------------//
    m_qtableviewFemurLandmarks = new QTableView;
    m_qtableviewFemurLandmarks->setStyleSheet("QTableView { background-color: transparent; font-size:20px; font-family-Inter; font-weight:normal; border-color:transparent;}"
                                              "QTableView::item:hover { "
                                              "  background-color:transparent;  border-color:transparent;" // Hover color
                                              "} "
                                              "QTableView::item {  margin-top:2px; margin-bottom:2px;  background-color: transparent; border-color:transparent;} "
                                              "QTableView::item:selected { "
                                              "    background-color: transparent;  border-color:transparent;"  // Selection color
                                              "}");
    m_qtableviewFemurLandmarks->setFixedHeight(500);
    //m_qtableviewFemurLandmarks->setContentsMargins(0,0,0,0);

    QVBoxLayout* qvblFemurAnnotation = new QVBoxLayout;
    qvblFemurAnnotation->addSpacing(15);
    qvblFemurAnnotation->addWidget(m_qtableviewFemurLandmarks);
    QWidget* m_qwFemurAnnot = new QWidget;
    m_qwFemurAnnot->setLayout(qvblFemurAnnotation);
    m_qwFemurAnnot->setStyleSheet("QWidget:hover{background-transparent;}");

    //------------- Tibia landmark point selection layout-------------//
    m_qtableviewTibiaLandmarks = new QTableView;
    m_qtableviewTibiaLandmarks->setStyleSheet("QTableView { background-color: transparent; font-size:20px;font-family-Inter; font-weight:normal;  border-color:transparent;}"
                                              "QTableView::item { background-color: transparent; }"
                                              "QTableView::item:hover { "
                                              "   border-color:transparent;  background-color: transparent; " // Hover color
                                              "} "
                                              "QTableView::item:selected { "
                                              "    border-color:transparent;  background-color: transparent; "  // Selection color
                                              "}");
    m_qtableviewTibiaLandmarks->setFixedHeight(550);
    //  m_qtableviewFemurLandmarks->setContentsMargins(0,0,0,0);

    QVBoxLayout* qvblTibiaAnnotation = new QVBoxLayout;
    qvblTibiaAnnotation->addSpacing(15);
    qvblTibiaAnnotation->addWidget(m_qtableviewTibiaLandmarks);
    QWidget* m_qwTibiaAnnot = new QWidget;
    m_qwTibiaAnnot->setLayout(qvblTibiaAnnotation);
    //  m_qwTibiaAnnot->setStyleSheet("QWidget{background-color:transparent; border-color:transparent;}");

    m_objCustomTableView = new CustomTableView(CustomTableView::TypeA);
    m_objCustomTableView->setTableView(m_qtableviewFemurLandmarks);
    m_qtableviewFemurLandmarks->setItemDelegate(m_objCustomTableView);
    m_objCustomTableView->setTableView(m_qtableviewTibiaLandmarks);
    m_qtableviewTibiaLandmarks->setItemDelegate(m_objCustomTableView);


    //    m_qtableviewFemurLandmarks->setColumnWidth(0,1);
    //    m_qtableviewFemurLandmarks->setColumnWidth(1,200);
    //    m_qtableviewFemurLandmarks->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);


    //place the tables into tab widget
    m_qtbwAnnotation = new QTabWidget;
    m_qtbwAnnotation ->setObjectName("AnnotationTabWidget");
    m_qtbwAnnotation->tabBar()->setObjectName("AnnotationTabBar");
    m_qtbwAnnotation->addTab(m_qwFemurAnnot,"Femur"); //femur reg
    m_qtbwAnnotation->addTab(m_qwTibiaAnnot,"Tibia"); //tibia reg
    m_qtbwAnnotation->setCurrentIndex(0);

    m_qpCaptureAnnotation = new QPushButton("Capture Point");
    m_qpCaptureAnnotation->setObjectName("capturepoint");

    m_qpbNext = new QPushButton("Next");
    m_qpbNext->setObjectName("backnextButton");

    m_qpbBack = new QPushButton("Back");
    m_qpbBack->setObjectName("backnextButton");

    //****
    //temp // reset button for mpr
    m_qpbReset= new QPushButton("Reset");
    m_qpbReset->setVisible(true);
    m_qpbReset->hide();

    //***



    m_qpbBack->setCheckable(true);
    m_qpbNext->setCheckable(true);

    QHBoxLayout* qhblBackNext = new QHBoxLayout;
    qhblBackNext->addWidget(m_qpbBack);
    qhblBackNext->addWidget(m_qpbNext);
    qhblBackNext->addWidget(m_qpbReset);

    QWidget *qwdspacer= new QWidget;
    qwdspacer->setObjectName("qwdspacer");
    qwdspacer->setStyleSheet("#qwdspacer"
                             "{background-color:#000000;"
                             "}");


    QVBoxLayout* qvblMain = new QVBoxLayout;
    qvblMain->addWidget(m_qtbwAnnotation,40);
    qvblMain->addWidget(m_qpCaptureAnnotation,10);
    //qvblMain->addWidget(qwdspacer);
    qvblMain->addSpacing(100);
    qvblMain->setContentsMargins(29,0,29,29);
    //this->setLayout(qvblMain);

    QFrame* frame_annotation = new QFrame;
    frame_annotation->setFixedWidth(480);
    frame_annotation->setLayout(qvblMain);
    frame_annotation->setObjectName("frame_annotation");
    QVBoxLayout* qvblframeannot = new QVBoxLayout;
    qvblframeannot->addWidget(frame_annotation);

    this->setLayout(qvblframeannot);

    //tableview appearance
    m_qtableviewFemurLandmarks->setShowGrid(true);
    m_qtableviewFemurLandmarks->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_qtableviewFemurLandmarks->horizontalHeader()->setVisible(false);
    m_qtableviewFemurLandmarks->verticalHeader()->setVisible(false);
    m_qtableviewFemurLandmarks->horizontalHeader()->setStretchLastSection(true);

    m_qtableviewTibiaLandmarks->setShowGrid(true);
    m_qtableviewTibiaLandmarks->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_qtableviewTibiaLandmarks->horizontalHeader()->setVisible(false);
    m_qtableviewTibiaLandmarks->verticalHeader()->setVisible(false);
    m_qtableviewTibiaLandmarks->horizontalHeader()->setStretchLastSection(true);

    //adjust height to show full contents
    m_qtableviewFemurLandmarks->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_qtableviewFemurLandmarks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_qtableviewTibiaLandmarks->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    m_qtableviewTibiaLandmarks->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //-----------------------------------------------

    // Load items from the femur landmark file
    loadItemsFromFile(QDir::currentPath() + "/" + "Femur_landmarks.txt",
                      m_iAnatomyID1, m_anatomy1, m_iNumberOfFemurLandmarks);

    // Load items from the tibia landmark file
    loadItemsFromFile(QDir::currentPath() + "/" + "Tibia_landmarks.txt",
                      m_iAnatomyID2, m_anatomy2, m_iNumberOfTibiaLandmarks);

    model1 = new QStandardItemModel;
    model2 = new QStandardItemModel;

    // Populate the table with items from the files
    populateTableViewWithItems(m_qtableviewFemurLandmarks, model1,
                               m_iAnatomyID1,m_anatomy1);
    populateTableViewWithItems(m_qtableviewTibiaLandmarks, model2,
                               m_iAnatomyID2, m_anatomy2) ;

    connect(m_qtableviewFemurLandmarks->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &Annotation::onTableMenuSelectionChanged);

    connect(m_qtableviewTibiaLandmarks->selectionModel(), &QItemSelectionModel::currentChanged,
            this, &Annotation::onTableMenuSelectionChanged);

//    connect(m_qtableviewFemurLandmarks, &QTableView::clicked, this, &Annotation::onFemurTableClicked);
//    connect(m_qtableviewTibiaLandmarks, &QTableView::clicked, this, &Annotation::onTibiaTableClicked);

    connect(m_qpCaptureAnnotation,&QPushButton::clicked,
            this, &Annotation::OnCaptureClicked);

    connect(m_qtbwAnnotation,&QTabWidget::currentChanged,
            this, &Annotation::annoTabChanged);

    //annoTabChanged(0);

    //    //set width of the radiobutton column
    //    m_qtableviewFemurLandmarks->setColumnWidth(0,300);
    //    m_qtableviewTibiaLandmarks->setColumnWidth(0, 300);

    m_qtableviewFemurLandmarks->setRowHeight(0,42);
    m_qtableviewFemurLandmarks->setRowHeight(1,0);
    m_qtableviewFemurLandmarks->setRowHeight(2,42);
    m_qtableviewFemurLandmarks->setRowHeight(3,0);
    m_qtableviewFemurLandmarks->setRowHeight(4,42);
    m_qtableviewFemurLandmarks->setRowHeight(5,0);
    m_qtableviewFemurLandmarks->setRowHeight(6,42);
    m_qtableviewFemurLandmarks->setRowHeight(7,0);
    m_qtableviewFemurLandmarks->setRowHeight(8,42);
    m_qtableviewFemurLandmarks->setRowHeight(9,0);
    m_qtableviewFemurLandmarks->setRowHeight(10,42);
    m_qtableviewFemurLandmarks->setRowHeight(11,0);
    m_qtableviewFemurLandmarks->setRowHeight(12,42);
    m_qtableviewFemurLandmarks->setRowHeight(13,0);
    m_qtableviewFemurLandmarks->setRowHeight(14,42);
    m_qtableviewFemurLandmarks->setRowHeight(15,0);
    m_qtableviewFemurLandmarks->setRowHeight(16,42);
    m_qtableviewFemurLandmarks->setRowHeight(17,0);
    m_qtableviewFemurLandmarks->setRowHeight(18,42);
    // m_qtableviewFemurLandmarks->setRowHeight(19,7);

    m_qtableviewTibiaLandmarks->setRowHeight(0,42);
    m_qtableviewTibiaLandmarks->setRowHeight(1,0);
    m_qtableviewTibiaLandmarks->setRowHeight(2,42);
    m_qtableviewTibiaLandmarks->setRowHeight(3,0);
    m_qtableviewTibiaLandmarks->setRowHeight(4,42);
    m_qtableviewTibiaLandmarks->setRowHeight(5,0);
    m_qtableviewTibiaLandmarks->setRowHeight(6,42);
    m_qtableviewTibiaLandmarks->setRowHeight(7,0);
    m_qtableviewTibiaLandmarks->setRowHeight(8,42);
    m_qtableviewTibiaLandmarks->setRowHeight(9,0);
    m_qtableviewTibiaLandmarks->setRowHeight(10,42);
    m_qtableviewTibiaLandmarks->setRowHeight(11,0);
    m_qtableviewTibiaLandmarks->setRowHeight(12,42);


    m_qtableviewFemurLandmarks->setObjectName("annottable");
    m_qtableviewTibiaLandmarks->setObjectName("annottable");


    //  initializeTableSelection();



    //    const int rowht = m_qtableviewFemurLandmarks->verticalHeader()->sectionSize(0);
    //    m_qtableviewFemurLandmarks->verticalHeader()->setDefaultSectionSize(rowht);
    //qDebug()<<"row height "<<rowht;


}

void Annotation::loadItemsFromFile(const QString &filePath, QVector<int> &anatomyID,
                                   QVector<QString> &anatomy, int &numOfLandmarks)
{
    qDebug()<<"loadItemsFromFile"<<filePath;

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        // Read the number of items from the first line
        QString firstLine = in.readLine();
        //split first line into two parts uisng colon delimiter
        QStringList firstLineParts = firstLine.split(";");
        if (firstLineParts.size() == 2)
        {
            numOfLandmarks = firstLineParts[1].toInt();
            //qDebug()<<"numOfLandmarks"<<numOfLandmarks;
        }
        // Read the subsequent lines for pointselection id and anatomy names
        while (!in.atEnd())
        {
            QString line = in.readLine();
            QStringList parts = line.split(":");
            if (parts.size() == 2)
            {
                int id = parts[0].toInt();
                QString anatomyName = parts[1];
                //qDebug()<<"point selection id; anatomy"<<id<<anatomyName;
                anatomyID.append(id);
                anatomy.append(anatomyName);
            }
        }
        file.close();
    }

    else
    {
        qDebug() << "Failed to open file:" << filePath;
    }
}



void Annotation::populateTableViewWithItems(QTableView *tableView, QStandardItemModel *model,
                                            const QVector<int> &anatomyID, const QVector<QString> &anatomy)
{
    int originalRowCount = anatomy.size();
    int newRowCount = originalRowCount * 2 - 1; // Total rows considering blank rows between anatomy items
    model->setRowCount(newRowCount);
    model->setColumnCount(1);

    for (int i = 0; i < originalRowCount; ++i)
    {
        int anatomyRow = i * 2;
        QStandardItem *anatomyItem = new QStandardItem(anatomy[i]);
        model->setItem(anatomyRow, 0, anatomyItem);

        // Place blank rows after each anatomy item, except the last one
        if (i < originalRowCount - 1)
        {
            QStandardItem* lineImage = new QStandardItem;
            QString imagePath = ":/res/icons/blankrowimage_1.PNG";
            QImage image(imagePath);

            //  int thumbSize = 63;
            int thumbSize = /*rowht +*/20;
            //qDebug()<<"row height"<<thumbSize;
            //qDebug()<<"m_anatomy id "<<m_iAnatomyID1;
            // Scale the image based on the dynamically determined thumbnail size
            QPixmap scaledPixmap = QPixmap::fromImage(image).scaled(QSize(thumbSize, thumbSize),
                                                                    Qt::KeepAspectRatio);
            lineImage->setData(QVariant(scaledPixmap), Qt::DecorationRole);
            model->setItem(anatomyRow+1 , 0, lineImage);  // Set the blank image in the next row
        }
    }
    tableView->setModel(model);

    //parvathy
    QModelIndex firstIndex = model->index(0, 0); // First row, first column
    if (firstIndex.isValid())
    {
        int index = 0;

        QItemSelectionModel *selectionModel = tableView->selectionModel();
        //qDebug()<<"selection model "<<selectionModel;
        selectionModel->setCurrentIndex(firstIndex, QItemSelectionModel::Select);

        if (selectionModel == m_qtableviewFemurLandmarks->selectionModel())
        {
            m_blFemur = true; m_blTibia = false;
            qDebug()<<"Selected bone name in Annotation :"<<"Femur"<</*<<"landmark id :"<<*/m_iAnatomyID1[0]<</*"landmark name :"<<*/m_anatomy1[0];
            // Emit the signal with the selected anatomy ID and name
            emit signalAnatomyAnnotation("Femur",m_iAnatomyID1[0], m_anatomy1[0]);
        }
    }
}

//parvathy- for checking if point is selected in mpr
void Annotation::slotpointchecked(bool point)
{
    pointchecked = point;
     qDebug()<<"pointchecked in annotation"<<pointchecked;
}


void Annotation::OnCaptureClicked()
{
    qDebug()<<"OnCaptureClicked";


    if (pointchecked)
    {
        if(m_blFemur == true)
        {
            QModelIndex selectedIndex = m_qtableviewFemurLandmarks->selectionModel()->currentIndex();
            if(selectedIndex.isValid())
            {
                m_objCustomTableView->setCaptureIndex(selectedIndex);
                int nextRow = selectedIndex.row() + 2;
                if(nextRow <= model1->rowCount())
                {
                    QModelIndex nextIndex = model1->index(nextRow,0);
                    m_qtableviewFemurLandmarks->selectionModel()->setCurrentIndex(nextIndex, QItemSelectionModel::SelectCurrent);
                }
            }
        }

        else if (m_blTibia == true)
        {
            QModelIndex selectedIndex = m_qtableviewTibiaLandmarks->selectionModel()->currentIndex();
            if(selectedIndex.isValid())
            {
                m_objCustomTableView->setCaptureIndex(selectedIndex);
                int nextRow = selectedIndex.row() + 2;
                if(nextRow <= model2->rowCount())
                {
                    QModelIndex nextIndex = model2->index(nextRow,0);
                    m_qtableviewTibiaLandmarks->selectionModel()->setCurrentIndex(nextIndex, QItemSelectionModel::SelectCurrent);
                }
            }
        }
    }

pointchecked= false;

}

//parvathy
void Annotation::annoTabChanged(int curindex)
{
    qDebug()<<"annoTabChanged"<<curindex;

    if(curindex == 0)
    {
        qDebug()<<"annoTabChanged - femur";
        m_qtbwAnnotation->setCurrentIndex(0);
        m_blFemur = true; m_blTibia = false;

        QModelIndexList selectedIndexes = m_qtableviewFemurLandmarks->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {

            for (const QModelIndex &index : selectedIndexes) {

                int nextRow = index.row();
                //ignore index of blank rows(odd rows)
                if (nextRow % 2 == 0) //annot items are at even indexes(0,2,4..)
                {
                    nextRow = nextRow / 2;
                }
                qDebug()<<"Selected bone name in Annotation : "<<"Femur "<</*"landmark id :"<<*/m_iAnatomyID1[nextRow]<</*"landmark name : "<<*/m_anatomy1[nextRow];
                emit signalAnatomyAnnotation("Femur",m_iAnatomyID1[nextRow], m_anatomy1[nextRow]);
            }
        }
    }

    else if (curindex == 1)
    {
        qDebug()<<"annoTabChanged - tibia";
        m_qtbwAnnotation->setCurrentIndex(1);
        m_blFemur = false; m_blTibia = true;
        QModelIndexList selectedIndexes = m_qtableviewTibiaLandmarks->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {

            for (const QModelIndex &index : selectedIndexes) {

                int nextRow = index.row();
                //ignore index of blank rows(odd rows)
                if (nextRow % 2 == 0) //annot items are at even indexes(0,2,4..)
                {
                    nextRow = nextRow / 2;
                }
                qDebug()<<"Selected bone name in Annotation : "<<"Tibia "/*<<"landmark id :"*/<<m_iAnatomyID2[nextRow]/*<<"landmark name : "*/<<m_anatomy2[nextRow];
                emit signalAnatomyAnnotation("Tibia",m_iAnatomyID2[nextRow], m_anatomy2[nextRow]);
            }
        }
    }
}


void Annotation::onTableMenuSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    int index = current.row();
    //ignore index of blank rows(odd rows)
    if (index % 2 == 0) //annot items are at even indexes(0,2,4..)
    {
        index = index / 2;
    }
    //qDebug()<<"Annot table index : "<<index + 1;

    QItemSelectionModel *selectionModel = qobject_cast<QItemSelectionModel *>(sender());

    //enable interaction(point marking) when an item is selected
    emit signalEnablePointSelection();

    if (selectionModel == m_qtableviewFemurLandmarks->selectionModel())
    {
        m_blFemur = true; m_blTibia = false;

        //m_qtableviewFemurLandmarks->clearSelection();

        if (index >= 0 && index < m_iAnatomyID1.size() && index < m_anatomy1.size())
        {
            qDebug()<<"Selected bone name in Annotation : "<<"Femur "<</*"landmark id :"<<*/m_iAnatomyID1[index]<</*"landmark name :"<<*/m_anatomy1[index];
            //    // Emit the signal with the selected anatomy ID and name
            emit signalAnatomyAnnotation("Femur",m_iAnatomyID1[index], m_anatomy1[index]);
        }
    }

    else if (selectionModel == m_qtableviewTibiaLandmarks->selectionModel())
    {
        m_blFemur = false; m_blTibia = true;

        //m_qtableviewTibiaLandmarks->clearSelection();
        if (index >= 0 && index < m_iAnatomyID2.size() && index < m_anatomy2.size())
        {
            qDebug()<<"Selected bone name in Annotation : "<<"Tibia "<</*"landmark id :"<<*/m_iAnatomyID2[index]<</*"landmark name : "<<*/m_anatomy2[index];
            emit signalAnatomyAnnotation("Tibia",m_iAnatomyID2[index], m_anatomy2[index]);
        }
    }
}

void Annotation::onFemurTableClicked(const QModelIndex &index1)
{
    int index = index1.row();
    //ignore index of blank rows(odd rows)
    if (index % 2 == 0) //annot items are at even indexes(0,2,4..)
    {
        index = index / 2;
    }
    qDebug()<<"Annot table index : "<<index + 1;

    //QItemSelectionModel *selectionModel = qobject_cast<QItemSelectionModel *>(sender());

    //enable interaction(point marking) when an item is selected
    emit signalEnablePointSelection();

//    if (selectionModel == m_qtableviewFemurLandmarks->selectionModel())
//    {
        m_blFemur = true; m_blTibia = false;

        //m_qtableviewFemurLandmarks->clearSelection();

        if (index >= 0 && index < m_iAnatomyID1.size() && index < m_anatomy1.size())
        {
            qDebug()<<"Selected bone name in Annotation : "<<"Femur "<</*"landmark id :"<<*/m_iAnatomyID1[index]<</*"landmark name :"<<*/m_anatomy1[index];
            //    // Emit the signal with the selected anatomy ID and name
            emit signalAnatomyAnnotation("Femur",m_iAnatomyID1[index], m_anatomy1[index]);
        }
   // }
}

void Annotation::onTibiaTableClicked(const QModelIndex &index1)
{
    //Q_UNUSED(previous);

    int index = index1.row();
    //ignore index of blank rows(odd rows)
    if (index % 2 == 0) //annot items are at even indexes(0,2,4..)
    {
        index = index / 2;
    }
    //qDebug()<<"Annot table index : "<<index + 1;

    //QItemSelectionModel *selectionModel = qobject_cast<QItemSelectionModel *>(sender());

    //enable interaction(point marking) when an item is selected
    emit signalEnablePointSelection();


//    else if (selectionModel == m_qtableviewTibiaLandmarks->selectionModel())
//    {
        m_blFemur = false; m_blTibia = true;

        //m_qtableviewTibiaLandmarks->clearSelection();
        if (index >= 0 && index < m_iAnatomyID2.size() && index < m_anatomy2.size())
        {
            qDebug()<<"Selected bone name in Annotation : "<<"Tibia "<</*"landmark id :"<<*/m_iAnatomyID2[index]<</*"landmark name : "<<*/m_anatomy2[index];
            emit signalAnatomyAnnotation("Tibia",m_iAnatomyID2[index], m_anatomy2[index]);
        }
   // }
}
