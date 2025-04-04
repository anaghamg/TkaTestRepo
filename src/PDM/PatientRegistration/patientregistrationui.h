/*
    File Name       : patientregistrationui.h
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Header file for GUI implementation for
                      patient registration
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#ifndef PATIENTREGISTRATIONUI_H
#define PATIENTREGISTRATIONUI_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
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

//sql headers
#include "appcommon/sqlite3/sqlite3.h"

#include "QSqlDatabase"
#include "QSqlQuery"
#include "QSqlRecord"
#include "QSqlError"
#include "QSqlQueryModel"
#include "QSqlTableModel"
#include "QListView"
#include "QStringListModel"
#include "QPalette"

class PatientRegistrationUI : public QWidget
{
    Q_OBJECT
public:
    explicit PatientRegistrationUI(QWidget *parent = nullptr);

    void SetPatientDetails(/*const*/ QStringList& qstrList );

    QPushButton *m_qpbSave;
    QPushButton *m_qpbClear ;
    QStringList m_dbstrlist;
    QStringList m_dbstrlistEdit;
    //added
    QPushButton* m_qpbNewReg;
    QPushButton* m_qpbNext;

    QPushButton *m_qpbUpdate ;

    QStringList qstrlstPatDetails;
    QStringList qstrlstUpdatePatientDetails;

    QString dbpatientID;
    void SetDBPatientID(QString id);

    //bool m_bClearedDetails = false;

signals:
     void SendPatientDetails(QStringList qstrPatDetails);

     void UpdatePatientDetails(QString pid, QStringList qstrUpdatedDetails);

     //void SignalClearEntry();

public slots:
    QStringList GetPatientDetails() /*const*/;
    void saveToDB();
    void CalculateAge();
    void SetDobFromAge(/*QString qstrAge*/);
    void EditPatientForm(QStringList qstrPatientReg);

    //------- validation -------//
    void validateInput(const QString &text);

    void validateInputPhysician(const QString &text); //added
    void validateAge(const QString &text);
    void validateAddress(const QString &text);

    //added
    void EnableNewReg();
    void UpdateFromLineEdit();
    void NewRegistration();



private:
    QVBoxLayout *m_qpMainLayout;

    QLineEdit *m_qplineEditPatID;
    QLineEdit *m_qplineEditPatName ;
    QComboBox *m_qpcboxGender;
    QLineEdit *m_qplineEditPatAge;
    QLineEdit *m_qplineEditPatAddress;
    QLineEdit *m_qplineEditRefPhysician;
            //    QLineEdit *m_qplineEditPatUID;
    QLineEdit *m_qplineEditPatAadhar;

    QCalendarWidget* m_qpwDob;
    QLineEdit *m_qplineEditPatDob;
    QDate selectedDob;
    QString m_qpstrPatAge;
    QIntValidator *validator;

    //added on 19-07-2024
    QString m_qpstrPatDob; //



    void ClearAllFields();
};

#endif // PATIENTREGISTRATIONUI_H
