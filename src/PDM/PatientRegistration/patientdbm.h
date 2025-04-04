/*
    File Name       : patientdbm.h
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Header file containing implementation for
                      Patient Database Management
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#ifndef PATIENTDBM_H
#define PATIENTDBM_H

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
#include <QStackedWidget>
#include <QMenu>
#include <QTabWidget>
#include <QDateTime>
#include <QLineEdit>
#include <QTimerEvent>

#include "src/PDM/PatientRegistration/patientregistrationui.h"
#include "src/PDM/PatientRegistration/dbmanager.h"
#include "src/PDM/Project/projectwidget.h" //dont delete

class PatientDBM : public QWidget
{
    Q_OBJECT
public:
    explicit PatientDBM(QWidget *parent = nullptr);

    //create class objects
    PatientRegistrationUI *m_objPatientReg;  //registration form
    DbManager *m_objDbManager;  //connect to db, save, retrieve
    ProjectWidget* m_objProject; //project, import data, superimpose

signals:
    void signalNewRegistration();

public slots:

private:

};

#endif // PATIENTDBM_H
