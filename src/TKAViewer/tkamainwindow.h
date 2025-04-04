/*
 * File Name : TKAmainwindow.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header of Main Class of planning module
 * Developer :Divya N S
 * Revision History : 1-8-2024
*/
#ifndef TKAMAINWINDOW_H
#define TKAMAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QObject>
#include "vtkAutoInit.h"

//VTK_MODULE_INIT(vtkRenderingOpenGL2) // VTK was built with vtkRenderingOpenGL2
//VTK_MODULE_INIT(vtkInteractionStyle)
//VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2)
//VTK_MODULE_INIT(vtkRenderingFreeType)  // VTK was built with vtkRenderingFreeType, so initialize module.

#include "tkathreedview.h"
#include "tkatwodview.h"



class TKAMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    TKAMainWindow(QWidget *parent = nullptr);
    ~TKAMainWindow();

    //Variables
    QString config_filename = QDir::currentPath()+"//Config_TKA//config_3D.ini";

private:

    //Variables
    TKAThreeDView m_ThreeDView;
    TKATwoDView m_TwoDView;

    //QPushButton *pushButton_Boneopacity;
    QPushButton *pushButton_Implantopacity;
    QWidget *centralwidget;
    QGridLayout *Main_gridLayout;
    QStackedWidget *stackedWidget;
    QGridLayout *gridLayout_3;
    QFrame *frame_centerpanel;
    QFrame *frame_rightpanel;
    QFrame *frame_bottompanel;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_15;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2D;
    //QPushButton *pushButton_3D;
    QPushButton *pushButton_cut;
    QPushButton *pushButton_axis;
    QPushButton *pushButton_AnotPoint;
    QPushButton *pushButton_implant;
    QComboBox *comboBox_Models;
    QLabel *label_TibiaSize;
    QLabel *label_FemurSize;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *doubleSpinBox_Femur;
    QDoubleSpinBox *doubleSpinBo_Poly;
    QLabel *label_PolySize;
    QDoubleSpinBox *doubleSpinBox_Tibia;
    QComboBox *comboBox_Manufacturer;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusbar;
    QComboBox *m_comboManfacturer;

    QVBoxLayout *m_qvbrightpanel;
    bool spacerVisible = true;

    //---Added on 5-9-2024-----
    QPushButton *pushButton_Next;
    QPushButton *pushButton_Back;

    //---------------------
bool Planningclicked_onetime = false;  //testing  true for now, change back to false

public slots:
    void Switch2DViewSlot();
    void Switch3DViewSlot();
    // void EnableSpinboxes(bool);
    void SlotForFemurTibiaPaths(const QString& qstrFemurStl, const QString& qstrTibiaStl);//added on 26-9-24
    void PlanningButtonclickedSlot();//added on 17-10-2024


};
#endif // TKAMAINWINDOW_H
