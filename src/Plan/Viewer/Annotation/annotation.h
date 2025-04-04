#ifndef ANNOTATION_H
#define ANNOTATION_H

#include <QWidget>
#include <QObject>
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
#include <QStringListModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QFont>
#include <QSizePolicy>
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QSizePolicy>

#include "src/Plan/Viewer/Annotation/customtableview.h"
#include "appcommon/spdlog/spdlog.h"

//added 30-07-2024 for TKA
class Annotation : public QWidget
{
    Q_OBJECT
public:
    explicit Annotation(QWidget *parent = nullptr);

    bool m_blFemur = true;
    bool m_blTibia = true;

    bool pointchecked = false;

    QPushButton *m_qpbReset; //dhanyasree
    QTabWidget* m_qtbwAnnotation;


signals:
    //enable interaction when an item is selected
    ////not fully done //once interaction starts, cannot disable
    void signalEnablePointSelection();

    //signal to specify whether Femur/Tibia selected ; landmark point id, landmark name
    void signalAnatomyAnnotation(QString from, int anatomyid, const QString& anatomy);

public slots:
    void OnCaptureClicked();
    void onTableMenuSelectionChanged(const QModelIndex &current, const QModelIndex &previous);
    void onFemurTableClicked(const QModelIndex &index1);
    void onTibiaTableClicked(const QModelIndex &index1);


    void annoTabChanged(int index);
    void slotpointchecked(bool pointchecked);

private:
    QPushButton* m_qpCaptureAnnotation;
    QPushButton* m_qpbNext;
    QPushButton* m_qpbBack;

    CustomTableView* m_objCustomTableView;

    int m_iNumberOfFemurLandmarks;
    int m_iNumberOfTibiaLandmarks;

    QVector<int> m_iAnatomyID1;
    QVector<QString> m_anatomy1;//anatomical point

    QVector<int> m_iAnatomyID2;
    QVector<QString> m_anatomy2;//anatomical point

    QTableView* m_qtableviewFemurLandmarks;
    QTableView* m_qtableviewTibiaLandmarks;

    QStandardItemModel *model1;
    QStandardItemModel *model2;

    void loadItemsFromFile(const QString &filePath, QVector<int> &anatomyID, QVector<QString> &anatomy, int &numOfLandmarks);

    void populateTableViewWithItems(QTableView *tableView, QStandardItemModel *model,
                  const QVector<int> &anatomyID, const QVector<QString> &anatomy);




    QModelIndex m_femurSelectedIndex;  // To store the last selected index for Femur
    QModelIndex m_tibiaSelectedIndex;  // To store the last selected index for Tibia




    void initializeTableSelection();

};

#endif // ANNOTATION_H
