/*
    File Name       : dbmanager.cpp
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Source file for connecting to Database, query, retrieval, etc
                      and displaying the database model to GUI.
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#include "dbmanager.h"

DbManager::DbManager(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"*********Start of DbManager ctor";
    InitializeWin();
    qDebug()<<"*********End of DbManager ctor";
}

void DbManager::InitializeWin()
{
    qDebug()<<"*********InitializeWin in DbManager";
    //open existing db
    qDebug()<<"Current dir:"<<  QDir::currentPath();
    QString folderPath = QDir::currentPath()+"/DB";    //set relative path
    QString pathPatientDb = folderPath + "/" + "PatientList.db"; //PatientList.db
    qDebug()<<"Path for DB"<<pathPatientDb;

    m_qsqlPatientDb = QSqlDatabase::addDatabase("QSQLITE");
    m_qsqlPatientDb.setDatabaseName(pathPatientDb);
    qDebug()<<"opened db";
    if(!m_qsqlPatientDb.open())
    {
        qDebug()<<"Connection to DB failed";
        QMessageBox::critical(this, "Cannot open database",
                              "Unable to establish a database connection."
                               "Click Cancel to exit.",QMessageBox::Cancel);
    }
    else
    {
        qDebug()<<"Connected to DB"<<m_qsqlPatientDb.databaseName();
    }

    m_qpsqlTblModel = new QSqlTableModel(this, m_qsqlPatientDb);
    m_qptableView = new QTableView;
  //  m_qptableView->setFixedSize(1300, 400);
    m_qpsqlTblModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    m_qpsqlTblModel->setTable("Patient");
    m_qpsqlTblModel->select();     //to populate the model with data
    m_qptableView->setModel(m_qpsqlTblModel);
    m_qptableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_qptableView->setObjectName("patienttable");

    m_objPatientData = new patientdata;
    m_objImageSelection = new imageselection;

    m_qptableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_qptableView->resizeRowsToContents();
    m_qptableView->setSortingEnabled(false);

    m_qptableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Stretch);
   // m_qptableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    m_qptableView->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    m_qptableView->setShowGrid(true);
    m_qptableView->update();

    //add Edit, View, Delete buttons
    //m_qptableView->setIndexWidget(m_qptableView->model()->index(0,2), new QPushButton);

    m_qlineditKeyword = new QLineEdit;
    m_qlineditKeyword->setPlaceholderText("Search by keyword");
    m_qlineditKeyword->setFixedSize(200,30);
    m_qlineditKeyword->setClearButtonEnabled(true);

    QLabel* lblDateFrom = new QLabel("Date   From :");
    lblDateFrom->setAlignment(Qt::AlignCenter);
    lblDateFrom->setObjectName("pdmlblsearch");
    lblDateFrom->setFixedSize(200,30);
    QLabel* lblDateTo = new QLabel("To");
    lblDateTo->setObjectName("pdmlblsearch");
    lblDateTo->setAlignment(Qt::AlignCenter);
    lblDateTo->setFixedSize(25,30);
    QDateEdit*  dateEditFrom = new QDateEdit;
    dateEditFrom->setStyleSheet("font-size:16px;");
    QDateEdit*  dateEditTo = new QDateEdit;
    dateEditTo->setStyleSheet("font-size:16px;");
    dateEditFrom->setMinimumDate(QDate(1990,01,01));
    dateEditFrom->setFixedSize(120,30);
    dateEditFrom->setToolTip("Select any date from 01-01-1990");
    dateEditTo->setMaximumDate(QDate::currentDate());
    dateEditTo->setFixedSize(120,30);
    dateEditTo->setToolTip("valid date till today");
    dateEditFrom->setDate(QDate(1990,01,01));
    dateEditTo->setDate(QDate::currentDate());


    //added on 11-07-2024
    m_qbtnSearchByKeyword = new QPushButton();
    m_qbtnSearchByKeyword->setFixedSize(40,10);
    m_qbtnSearchByKeyword->setIcon(QIcon(":/res/icons/Search.png"));
    m_qlineditKeyword->setClearButtonEnabled(true);
    //qbtnSearchByKeyword->setToolTip("Search by keyword only");
    m_qbtnSearchByDate = new QPushButton("Filter");
    m_qbtnSearchByDate->setStyleSheet("QPushButton { width: 60px; height: 20px; }");
    m_qbtnSearchByDate->setObjectName("filterbtn");
    m_qbtnSearchByDate->setToolTip("Filter between selected dates");
    m_qbtnSearchByDate->setCheckable(true);

    QHBoxLayout*  topLayout = new QHBoxLayout;
    //topLayout->addStretch(20);
    topLayout->setAlignment(Qt::AlignTop);
    topLayout->addWidget(m_qlineditKeyword, 0, Qt::AlignRight);
    topLayout->addWidget(m_qbtnSearchByKeyword,0, Qt::AlignTop); //added


    dateEditFrom->setEnabled(true);
    dateEditTo->setEnabled(true);
    m_qbtnSearchByDate->setEnabled(true);
    lblDateFrom->setEnabled(true);
    lblDateTo->setEnabled(true);

    //commented on 17-07-2024
    //filter by date
    topLayout->addSpacing(45);
    topLayout->addWidget(lblDateFrom);
    topLayout->addWidget(dateEditFrom);
    topLayout->addWidget(lblDateTo);
    topLayout->addWidget(dateEditTo);
    topLayout->addWidget(m_qbtnSearchByDate,0,Qt::AlignLeft); //added
    QWidget*   topWidget  = new QWidget;
    topWidget->setLayout(topLayout);


    //added by Parvathy

    m_qbtnSelectPatient= new QPushButton("Select");
    m_qbtnSelectPatient->setObjectName("m_SelectButton");
    m_qbtnSelectPatient->setCheckable(true);


    QHBoxLayout*  m_qhblBottomLayout = new QHBoxLayout;
    m_qhblBottomLayout->addWidget(m_qbtnSelectPatient);
    m_qhblBottomLayout->setAlignment(Qt::AlignCenter);

    QWidget*   bottomWidget  = new QWidget;
    bottomWidget->setLayout(m_qhblBottomLayout);


    m_qpvblSearchLayout = new QVBoxLayout;
    m_qpvblSearchLayout->addWidget(topWidget);
    m_qpvblSearchLayout->addWidget(m_qptableView);
    m_qpvblSearchLayout->addWidget(bottomWidget);

    m_qpvblMain = new QVBoxLayout;
    m_qpvblMain->addLayout(m_qpvblSearchLayout,30);

    m_qpvblMain->addLayout(m_objImageSelection->m_qpvblBrowseLayout,20);
    this->setLayout(m_qpvblMain);

    //connect clear(x) signal from qlinedit(seach bar) to restore default tableview
    for (int i(0); i < m_qlineditKeyword->children().size(); ++i)
    {
        QAction *myClearAction(qobject_cast<QAction *>(m_qlineditKeyword->children().at(i)));
        // Connect the triggered signal of the clear action to a slot or lambda function
        if (myClearAction)
        {
            connect(myClearAction, &QAction::triggered, this, &DbManager::ClearFilter);
        }
    }

    //Save the selected patient details to the patient data class
     connect(m_qbtnSelectPatient, &QPushButton::clicked, this, &DbManager::SelectedPatientDetails);

}

void DbManager::GoToPatRegstr(/*const*/ QStringList &qstrList)
{
    m_qstrEdit = qstrList;
    qDebug()<<"GoToPatRegstr in dbmanager "<<m_qstrEdit;
    emit SignalString(m_qstrEdit);
    qDebug()<<"emitted strlist";
}

void DbManager::TempSlot(QString id, QStringList qstrlistDet)
{
    qDebug()<<"TempSlot";
    m_pid = id;
    m_qpstrLstUpdatedDetails = qstrlistDet;
}

void DbManager::SetDBTableModel( QStringList strLstPatientDetails)
{
    qDebug()<<"setDBTableModel";
    m_qpstrLstPatientDetails = strLstPatientDetails;
    qDebug()<<"str values in setDBTableModel : "<<m_qpstrLstPatientDetails;

    QSqlQuery* sqlqry = new QSqlQuery(m_qsqlPatientDb);
    try
    {
        sqlqry->prepare("insert into Patient(ID,NAME,GENDER,Age,DOB,ADDRESS,REFPHYSICIAN,Aadhar) "
                        "VALUES(?,?,?,?,?,?,?,?);");
        qDebug() << "insert into Patient ";
    }
    catch (const std::exception& e)
    {
        qDebug() << "Exception occurred in DB insert"<<e.what();
    }

    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(0));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(1));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(2));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(3));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(4));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(5));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(6));
//    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(7));
    sqlqry->addBindValue( m_qpstrLstPatientDetails.at(7));

    try
    {
        sqlqry->exec();
    }
    catch (const std::exception& e)
    {
         qDebug() << "Exception in query execute";
    }

//    m_qpsqlTblModel->submitAll();
    qDebug()<<m_qpstrLstPatientDetails.at(6)<<m_qpstrLstPatientDetails.at(7);

    m_qpsqlTblModel->select();    // populate the model with data
    m_qptableView->setModel(m_qpsqlTblModel);
    m_qptableView->setShowGrid(true);
    m_qptableView->resizeRowsToContents();
    //sorted by id; ascending
//    m_qptableView->setSortingEnabled(false);//commented
    m_qptableView->update();

    //m_qpstrLstPatientDetails.clear();//

    ////////////
    QMessageBox::information(this, "Saved", "Details saved successfully.");


    qDebug()<<"end of set db model";
}

void DbManager::GetRowContents()
{
    m_objImageSelection->m_qfbrowseframe->hide();
    QItemSelectionModel* selmodel = m_qptableView->selectionModel();
    int rowid = selmodel->currentIndex().row();
    qDebug()<<"Selected rowid"<<rowid;

    QStringList qstrlstSelection;
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,0).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,1).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,2).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,3).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,4).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,5).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,6).data().toString());
//    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,7).data().toString());
    qstrlstSelection.append(m_qpsqlTblModel->index(rowid,7).data().toString());

    qDebug()<<"qstrlist selection"<<qstrlstSelection;

    //added
    //edit pat details in reg ui
    GoToPatRegstr(qstrlstSelection); ////////

    emit selectedRowContents(qstrlstSelection);//, rowid);
}

void DbManager::FilterByKeyword(const QString keyword)
{
    QString qstrkeyword = keyword;
    qDebug()<<"FilterByKeyWord; Obtained keyword"<<qstrkeyword;
    QString filter = QString(
          "ID LIKE '%%1%' OR "
          "NAME LIKE '%%1%' OR "
          "GENDER LIKE '%%1%' OR "
          "Age LIKE '%%1%' OR "
          "DOB LIKE '%%1%' OR "
          "ADDRESS LIKE '%%1%' OR "
          "REFPHYSICIAN LIKE '%%1%' OR "
//          "UID LIKE '%%1%' OR "
          "Aadhar LIKE '%%1%'"
      ).arg(keyword);

    m_qpsqlTblModel->setFilter(filter);
    m_qpsqlTblModel->select();
    m_qptableView->resizeRowsToContents();
    m_qptableView->setShowGrid(true);



    // Check if any rows are returned after filtering
    if (m_qpsqlTblModel->rowCount() == 0) {
        QMessageBox::warning(this, "No Results", "No matching records found.");
    }

}

void DbManager::StartKeywordSearch()
{
    qDebug()<<"StartKeywordSearch";

    QString keyword = m_qlineditKeyword->text().trimmed();
    qDebug()<<"keyword"<<keyword;
    emit SignalSendKeyword(keyword);
}

void DbManager::UpdateDBTable(QString patientid,QStringList qstrUpdate)
{
    qDebug()<<"UpdateDBTable";

    // Get the unique ID for the record you want to update
    QString id = patientid;
    qDebug() << "id to be updated"<<id;

    QStringList qstrlistDetails = qstrUpdate;
    // m_qpstrLstUpdatedDetails = qstrUpdate;
    qDebug()<<"str values in UpdateDBTable : "<<qstrlistDetails;

    TempSlot(id,qstrlistDetails );

    id.clear();
    qstrlistDetails.clear();
}

void DbManager::RefreshTable()
{
     qDebug()<<"RefreshTable";


     QSqlQuery* sqlqry = new QSqlQuery(m_qsqlPatientDb);
     try
     {
         sqlqry->prepare("UPDATE Patient SET NAME = ?, GENDER = ?, Age = ?, DOB = ?, ADDRESS = ?, REFPHYSICIAN = ?, Aadhar = ? WHERE ID = ?;");
         qDebug() << "Prepared update statement";
     }
     catch (const std::exception& e)
     {
         qDebug() << "Exception occurred in DB update prepare" << e.what();
     }

     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(1)); // NAME
     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(2)); // GENDER
     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(3)); // Age
     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(4)); // DOB
     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(5)); // ADDRESS
     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(6)); // REFPHYSICIAN
     sqlqry->addBindValue(m_qpstrLstUpdatedDetails.at(7)); // Aadhar
     sqlqry->addBindValue(m_pid);                    // ID

     qDebug()<<"sqlqry at "<<m_qpstrLstUpdatedDetails.at(7);
     try
     {
         sqlqry->exec();
         qDebug() << "Executed update statement";
     }
     catch (const std::exception& e)
     {
         qDebug() << "Exception in query execute" << e.what();
     }

     // Refresh the table view
     m_qpsqlTblModel->select();    // Repopulate the model with data
     m_qptableView->setModel(m_qpsqlTblModel);
     m_qptableView->setShowGrid(true);
     m_qptableView->update();
     qDebug() << "End of update db model";


//     QMessageBox::information(this, "Updated", "Details Updated successfully.");

     emit  SignalEnableNewReg();

}

void DbManager::ClearFilter()
{
    qDebug()<<"ClearFilter";
    m_qpsqlTblModel->setFilter("");
    m_qpsqlTblModel->select();
    m_qptableView->resizeRowsToContents();
    m_qptableView->setShowGrid(true);
}



void DbManager::SelectedPatientDetails()
{

    QItemSelectionModel* selmodel = m_qptableView->selectionModel();
    int rowid = selmodel->currentIndex().row();
    qDebug()<<"Selected rowid"<<rowid;

    if (rowid > -1)
    {
        qDebug()<<"SelectedPatientDetails";
         m_objImageSelection->m_qfbrowseframe->show();


        QStringList qstrlstSelection;
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,0).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,1).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,2).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,3).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,4).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,5).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,6).data().toString());
        qstrlstSelection.append(m_qpsqlTblModel->index(rowid,7).data().toString());

        qDebug()<<"SelectedPatientDetails"<<qstrlstSelection;

        //Save the details of the patient selected
        m_objPatientData->patientDetails(qstrlstSelection);
    }
    else
    {
         QMessageBox::warning(this, tr("Warning"), tr("Please select a patient"));
    }

}




//void DbManager::DeleteFromDB()
//{
//    qDebug()<<"DeleteFromDB";

//    QSqlQuery* sqlqry = new QSqlQuery(m_qsqlPatientDb);
//    try
//    {
//        sqlqry->prepare("DELETE FROM Patient WHERE ID = ?;");
//        qDebug() << "Prepared DELETE statement";
//    }
//    //    catch (const std::exception& e)
//    //    {
//    //        qDebug() << "Exception occurred in DB DELETE prepare" << e.what();
//    //    }

//    catch (const std::exception& e)
//    {
//        qDebug() << "Exception occurred in DB delete prepare" << e.what();
//        delete sqlqry;
//        return;
//    }


//    sqlqry->addBindValue(m_pid);                    // ID

//    try
//    {
//        if (sqlqry->exec())
//        {
//            qDebug() << "Executed delete statement";
//        }
//        else
//        {
//            qDebug() << "Failed to execute delete statement" << sqlqry->lastError().text();
//        }
//    }
//    catch (const std::exception& e)
//    {
//        qDebug() << "Exception in query execute" << e.what();
//    }

//    delete sqlqry;

//    // Refresh the table view
//    m_qpsqlTblModel->select();    // Repopulate the model with data
//    m_qptableView->setModel(m_qpsqlTblModel);
//    m_qptableView->setShowGrid(true);
//    m_qptableView->update();
//    qDebug() << "End of DELETE db model";

//}
