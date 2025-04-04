/*
    File Name       : ProjectWidget.h
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Header file for creation of patient projects, view patient details,
                      import dicom and stl and do landmark registration
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#ifndef PROJECTWIDGET_H
#define PROJECTWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QScrollArea>
#include <QTableView>
#include <QTableWidget>
#include <QHeaderView>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QStackedWidget>
#include <QFileDialog>
#include <QListView>
#include <QSizePolicy>
#include <QFrame>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QGridLayout>
#include <QTreeView>
#include <QStringListModel>
#include <QStandardItemModel>

#include "src/PDM/Project/classstl.h"
#include "src/PDM/Project/classdicom.h"


class ProjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ProjectWidget(QWidget *parent = nullptr);

    //create objects of class
    ClassSTL* m_objClassStl;
    ClassDicom* m_objClassDicom;

    QPushButton* m_qpbNewProject;
    QPushButton* m_qpbOpenProject;
    QWidget* m_qwPatient;
    QWidget* m_qwPjtMenu;
    QWidget* m_qwLoadData;

    QPushButton* m_qpbloadDicom;
    QPushButton* m_qpbloadSTL;

    QString m_qstrSTLPath;
    QString m_qstrDicomPath;

    bool m_blLoadDicom = false;
    bool m_blLoadStl = false;


signals:
    void signalNewProject(QString qstrNewProjPath);
    void signalExistingProject(QString qstrExistingProjPath);
    void signalRecentProject(QString qstrRecentProjPath);

public slots:

    void displayPatientDetails(QStringList qstrPatDetails);
    void OpenNew();
    void OpenExisting();
    void OpenRecent();

private:
    QWidget* m_qpwNewProject;
    QWidget* m_qpwExistingProject;

    QTableView m_qtableViewPatDetails;
    QStandardItemModel m_patDetModel;
};

#endif // PROJECTWIDGET_H
