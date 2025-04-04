/*
    File Name       : RegistrationUI.h
    Project Name    : TKA Robotic Surgery
    Created         : 16-08-2024
    Description     : Header file containing implementation for
                      Registration UI layout
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#ifndef REGISTRATIONUI_H
#define REGISTRATIONUI_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QDebug>
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QFile>
#include <QFileDialog>
#include <QRadioButton>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QFont>
#include <QSizePolicy>
#include <QSlider>
#include <QStackedWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QSlider>
#include <QVTKOpenGLWidget.h>

#include "src/Plan/Viewer/Annotation/customtableview.h"
#include "src/Registration/customthumbnailview.h"
#include "appcommon/spdlog/spdlog.h"

class RegistrationUI : public QWidget
{
    Q_OBJECT
public:
    explicit RegistrationUI(QWidget *parent = nullptr);

    //create class objects
    CustomTableView* m_objCustomTableView;
    CustomThumbnailView* m_objThumbnailView;

    QStackedWidget* m_qswThumbnail;
    QTabWidget* m_qtbwRegistration;
    QProgressBar* m_progressBar;
    QVTKOpenGLWidget* m_qvtkToolwin;

    QPushButton* m_qpbBack;
    QPushButton* m_qpbNext;
    QPushButton* m_qpbCaptureReg;


    //tableview for right panel
    QTableView* m_qtableviewFemurReg;
    QTableView* m_qtableviewTibiaReg;
    QStandardItemModel *model1;
    QStandardItemModel *model2;

signals:
    //signal to specify whether Femur/Tibia selected ; checkpoint/registration/verification
    void signalTableSelection(QString from,int tableItem);
    //signal to specify thumbnails selected
    void signalThumbnailSelection(QString from, QString item,int tableItem);




public slots:
    //void thumbnailSelected(QString from,QString item, int landmarkIndex);
    void onCaptureClicked();
    void onSelectionChanged(const QModelIndex &current, const QModelIndex &previous);




private slots:
    void onItemClicked1(const QModelIndex &index);
    void onItemClicked2(const QModelIndex &index);
    void onItemClicked3(const QModelIndex &index);
    void onItemClicked4(const QModelIndex &index);



private:


//    //tableview for right panel
//    QTableView* m_qtableviewFemurReg;
//    QTableView* m_qtableviewTibiaReg;
//    QStandardItemModel *model1;
//    QStandardItemModel *model2;

    //tableview for thumbnail
    QListView* m_qtableviewRegFemur;
    QListView* m_qtableviewVerFemur;
    QStandardItemModel *modelRegFemur;
    QStandardItemModel *modelVerFemur;

    QListView* m_qtableviewRegTibia;
    QListView* m_qtableviewVerTibia;
    QStandardItemModel *modelRegTibia;
    QStandardItemModel *modelVerTibia;

    QString qstrRegFemurThumbnail;
    QString qstrVerFemurThumbnail;
    QString qstrRegTibiaThumbnail;
    QString qstrVerTibiaThumbnail;

    int m_currentPage1;
    int m_currentPage2;
    int m_currentPage3;
    int m_currentPage4;

    int m_pageSize;

    QFileInfoList m_fileList1;
    QFileInfoList m_fileList2;
    QFileInfoList m_fileList3;
    QFileInfoList m_fileList4;

    QModelIndex initialThumbIndex; //set first thumbnail as selected

    void loadFilesForList(const QString &path, QFileInfoList &fileList);
    void displayPage(int page, QListView* listView, QString path, QStandardItemModel* model, QFileInfoList &fileList, int &currentPage);

    QVector<QString> m_qstrFemurMenu;
    QVector<QString> m_qstrTibiaMenu;






    //parvathy
    QModelIndex m_femurAllSelectedIndex;
    QMap<int, QList<int>> AllselectedIndexesRegFemur;
    QMap<int, QList<int>> AllselectedIndexesVerFemur;
    QMap<int, QList<int>> AllselectedIndexesRegTibia;
    QMap<int, QList<int>> AllselectedIndexesVerTibia;
    QAbstractItemModel* Allmodel;




    void loadTableViewMenu(QTableView *tableView, QStandardItemModel *model,
                           const QVector<QString> &tableItem);
    //load thumbnail with reg and ver thumbnail icons loaded from folder
    void  populateTableViewWithItems(QTableView *tableView, QStandardItemModel *model,
                                     const QString& folderPath);
    void onTableMenuSelectionChanged(const QModelIndex &current, const QModelIndex &previous);
    void onThumbnailSelectedChanged(const QModelIndex &current, const QModelIndex &previous);
    void setTableViewAppearance(QTableView *tableView);
    void changeTableItemColour(QTableView* tableView,QStandardItemModel* model);

    void changeThumbnailItemColour(QListView* tableView,QStandardItemModel* model, int pgnumber);
    void retainThumbnailItemColour(QListView* tableView, QMap<int, QList<int>>& AllselectedIndexes ,QStandardItemModel *model, int pgnumber);



};

#endif // REGISTRATIONUI_H
