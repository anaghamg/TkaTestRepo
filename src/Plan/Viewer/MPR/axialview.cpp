
#include "axialview.h"

axialView::axialView(QWidget *parent) : QWidget(parent)
{
//     this->setAttribute(Qt::WA_NativeWindow);
    Initialize();
}

void axialView::Initialize()
{    
    QVBoxLayout *qvbLayMenuBar= new QVBoxLayout;
    m_qmenubarAxial = new QMenuBar();
    m_qmenubarAxial->setObjectName("m_qmenubar");
    /* m_qmenubarAxial->setStyleSheet("#m_qmenubarAxial{"
                                   "border-left:.5px solid #595C79;"
                                   "border-top:.5px solid #595C79;"
                                   "border-right:.5px solid #595C79;"
                                   "background: #000000;}");*/

    m_qmenubarAxial->setLayoutDirection( Qt::RightToLeft);
    m_qacMaxim= new  QAction(QIcon(":/res/icons/max1.png"),"");
    connect(m_qacMaxim, &QAction::triggered, this, &axialView::maxThis);
    m_qacHide=    new QAction(QIcon(":/res/icons/hide1.png"),"");
    connect(m_qacHide, &QAction::triggered, this, &axialView::  hideThis);
    m_qmenubarAxial->addAction(m_qacMaxim);
    //    m_qmenubarAxial->addAction(m_qacHide);
                //qvbLayMenuBar->setMenuBar(m_qmenubarAxial); //commented for TKA
    m_qmenubarAxial->addMenu(new QMenu("Axial"));

    //    m_objClassAxialView = &ClassAxialView :: getInstance();
    //     m_objClassAxialView= new viewerReslice;

    m_objClassAxialView= new ClassAxialView;
    m_objWidget = new Widget;
    QHBoxLayout *horButLay= new QHBoxLayout;
//    horButLay->addWidget(m_objWidget,2);
    horButLay->addWidget(m_objClassAxialView);//,98);

    qvbLayMenuBar->addLayout(horButLay);
    this->setLayout(qvbLayMenuBar);    
}

void axialView::hideThis()
{
    qDebug()<<"Clicked hide";
    emit hideAxial();
}

void axialView::maxThis()
{
    qDebug()<<"Clicked max";
//    emit maxAxial();
    maxFromBut();
}

void axialView::maxFromBut()
{
    if(boolMaxStatus)
    {
        this->showNormal();
        boolMaxStatus=false;
    }
    else
    {
        this->showMaximized();
        boolMaxStatus=true;
    }
}
