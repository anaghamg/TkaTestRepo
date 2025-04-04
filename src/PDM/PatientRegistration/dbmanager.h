/*
    File Name       : dbmanager.h
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Header file for connecting to Database, query, retrieval, etc
                      and displaying the database model to GUI.
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QTableView>
#include <QTableWidget>
#include <QHeaderView>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QDate>
#include <QDateTime>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QComboBox>
#include <QStackedWidget>
#include <QStandardItemModel>
#include <QFileDialog>

//sql headers
#include "appcommon/sqlite3/sqlite3.h"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSortFilterProxyModel"
#include "QSqlError"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "QListView"
#include "QStringListModel"
#include "QAction"


#include "src/PDM/PatientData/patientdata.h"
#include "src/PDM/PatientRegistration/imageselection.h"

class DbManager : public QWidget
{
    Q_OBJECT
public:
    explicit DbManager(QWidget *parent = nullptr);

    void InitializeWin();
    void GoToPatRegstr(/*const*/ QStringList &qstrList);

    //create class objects
    patientdata *m_objPatientData;
    imageselection *m_objImageSelection;

    QPushButton* m_qbtnSearchByKeyword;
    QPushButton* m_qbtnSearchByDate;
    QPushButton* m_qbtnSelectPatient;
    QPushButton* m_qbtnBrowseImage;
    QRadioButton* m_qrbtnImageLessBtn;
    QRadioButton* m_qrbtnImageBasedBtn;
    QLineEdit* m_qlineditKeyword;
    QTableView* m_qptableView ;
    QString m_qsimagePath;

    //QSortFilterProxyModel* m_qsortFilter;
    void TempSlot(QString id, QStringList qstrlistDet); //

signals:
    void SignalString(QStringList qstrEdit);
    void selectedRowContents(QStringList qstrSelection);//, int rowid);

    void SignalSendKeyword(const QString keyword);

    void SignalEnableNewReg();

public slots:
    void SetDBTableModel( QStringList strdbList);
    void GetRowContents();

    //added on 12-07-2024
    void FilterByKeyword(const QString keyword);
    void StartKeywordSearch();

    void UpdateDBTable(QString patientid,QStringList qstrUpdate);
    void RefreshTable(); //on clikcing Update button
    void ClearFilter();
    void SelectedPatientDetails();

    //void DeleteFromDB();


private:

    QSqlDatabase m_qsqlPatientDb;

    QString m_pName;
    QString m_pGender;
    QString m_pDob;
    QString m_pAge;
    QString m_pId;
    QString m_pAddress;
    QString m_refPhysician;

    QSqlTableModel* m_qpsqlTblModel ;
    QStringList  m_qpstrLstPatientDetails;
    QStringList m_qstrEdit;

    QVBoxLayout *m_qpvblMain;
    QVBoxLayout *m_qpvblSearchLayout;
    QVBoxLayout *m_qpvblBrowseLayout;
    QVBoxLayout *m_qhblRadioBtnLayout;
    QHBoxLayout *m_hblMainPage;

   QFrame *m_qfbrowseframe;

    QStringList  m_qpstrLstUpdatedDetails;
    QString m_pid;


};

#endif // DBMANAGER_H
