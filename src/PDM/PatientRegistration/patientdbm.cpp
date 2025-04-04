/*
    File Name       : patientdbm.cpp
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Source file containing implementation for
                      Patient Database Management
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#include "patientdbm.h"

PatientDBM::PatientDBM(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"********Start of PatientDBM UI ctor";

    //initialize class objects
    m_objPatientReg = new PatientRegistrationUI;
    m_objDbManager = new DbManager;
    m_objProject = new ProjectWidget;

    //--------------Main widget-----------//
    QHBoxLayout* qhblPatReg = new QHBoxLayout;
    qhblPatReg->addWidget(m_objPatientReg);
    QWidget*  qwPatReg = new QWidget;
    qwPatReg->setLayout(qhblPatReg);

    QHBoxLayout* qphblPatientPage = new QHBoxLayout;
    qphblPatientPage->addWidget(m_objDbManager,80);
    qphblPatientPage->addWidget(qwPatReg,20);
    qphblPatientPage->setContentsMargins(0,0,0,0);

    QWidget* qpwPatientPage = new QWidget;
    qpwPatientPage->setLayout(qphblPatientPage);

    QVBoxLayout* qpvblMain = new QVBoxLayout;
    qpvblMain ->addWidget(qpwPatientPage);
    this->setLayout(qpvblMain);

    //display patient details from selected row only in next page(Patient page)
    connect(m_objDbManager,&DbManager::selectedRowContents,
            m_objProject, &ProjectWidget::displayPatientDetails);

    //get pat details from pat reg ui and set table model in dbmanager
    connect(m_objPatientReg, &PatientRegistrationUI::SendPatientDetails,
            m_objDbManager,&DbManager::SetDBTableModel);

    //edit pat details
    connect(m_objDbManager, &DbManager::SignalString,
            m_objPatientReg,&PatientRegistrationUI::EditPatientForm);

    connect(m_objDbManager->m_qptableView,&QTableView::clicked,
            m_objDbManager, &DbManager::GetRowContents);

    //added on 12-07-2024
    //-------- filter by keyword ---------//
    connect(m_objDbManager, &DbManager::SignalSendKeyword,
            m_objDbManager, &DbManager::FilterByKeyword);

    connect(m_objDbManager->m_qbtnSearchByKeyword, &QPushButton::clicked,
            m_objDbManager, &DbManager::StartKeywordSearch);


    //added on 17-07-2024
    //-------- update table after editing ---------//
    connect(m_objPatientReg, &PatientRegistrationUI::UpdatePatientDetails,
            m_objDbManager, &DbManager::UpdateDBTable);

    connect(m_objPatientReg->m_qpbUpdate, &QPushButton::clicked,
            m_objDbManager, &DbManager::RefreshTable);

    //enable new reg //23-07-2024
    connect(m_objDbManager, &DbManager::SignalEnableNewReg,
            m_objPatientReg, &PatientRegistrationUI::EnableNewReg);


    //added 24-07-2024
//    connect(m_objPatientReg, &PatientRegistrationUI::SignalClearEntry,
//            m_objDbManager, &DbManager::DeleteFromDB);


    qDebug()<<"*********End of homepage ctor";
}
