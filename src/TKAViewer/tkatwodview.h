/*
 * File Name : TKAtwodview.h
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Header of 2D viewer of planning module
 * Developer :Divya N S
 * Revision History : 1-8-2024
*/
#ifndef TKATWODVIEW_H
#define TKATWODVIEW_H

#include <QWidget>
#include <QtCore/QVariant>
#include <QOpenGLWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

class TKATwoDView;


class TKATwoDView : public QWidget
{
    Q_OBJECT

public:
    explicit TKATwoDView(QWidget *parent = nullptr);
    ~TKATwoDView();

    QGridLayout *gridLayout2D;
    QOpenGLWidget *TopRightLateralFemur2DWidget;
    QOpenGLWidget *BottomLeftAnteriorTibia2DWidget;
    QOpenGLWidget *BottomMiddleDistalTibia2DWidget;
    QOpenGLWidget *TopMiddleDistalFemur2DWidget;
    QOpenGLWidget *BottomRightLateralTibia2DWidget;
    QOpenGLWidget *TopLeftAnteriorFemur2DWidget;

};

#endif // TKATWODVIEW_H
