/*
 * File Name : twodview.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Implementation of 2D viewer of planning module
 * Developer :Divya N S
 * Revision History : 1-8-2024
*/
#include "tkatwodview.h"
#include <QLabel>

TKATwoDView::TKATwoDView(QWidget *parent) :
    QWidget(parent)

{
    this->resize(983, 661);



    //Setting Up the Widget
    gridLayout2D = new QGridLayout();
    gridLayout2D->setObjectName("gridLayout2D");


    TopRightLateralFemur2DWidget = new QOpenGLWidget(this);
    TopRightLateralFemur2DWidget->setObjectName("TopRightLateralFemur2DWidget");

    gridLayout2D->addWidget(TopRightLateralFemur2DWidget, 0, 2, 1, 1);

    BottomLeftAnteriorTibia2DWidget = new QOpenGLWidget(this);
    BottomLeftAnteriorTibia2DWidget->setObjectName("BottomLeftAnteriorTibia2DWidget");

    gridLayout2D->addWidget(BottomLeftAnteriorTibia2DWidget, 1, 0, 1, 1);

    BottomMiddleDistalTibia2DWidget = new QOpenGLWidget(this);
    BottomMiddleDistalTibia2DWidget->setObjectName("BottomMiddleDistalTibia2DWidget");

    gridLayout2D->addWidget(BottomMiddleDistalTibia2DWidget, 1, 1, 1, 1);

    TopMiddleDistalFemur2DWidget = new QOpenGLWidget(this);
    TopMiddleDistalFemur2DWidget->setObjectName("TopMiddleDistalFemur2DWidget");

    gridLayout2D->addWidget(TopMiddleDistalFemur2DWidget, 0, 1, 1, 1);

    BottomRightLateralTibia2DWidget = new QOpenGLWidget(this);
    BottomRightLateralTibia2DWidget->setObjectName("BottomRightLateralTibia2DWidget");

    gridLayout2D->addWidget(BottomRightLateralTibia2DWidget, 1, 2, 1, 1);

    TopLeftAnteriorFemur2DWidget = new QOpenGLWidget(this);
    TopLeftAnteriorFemur2DWidget->setObjectName("TopLeftAnteriorFemur2DWidget");

    gridLayout2D->addWidget(TopLeftAnteriorFemur2DWidget, 0, 0, 1, 1);


    this->setLayout(gridLayout2D);
}

TKATwoDView::~TKATwoDView()
{

}
