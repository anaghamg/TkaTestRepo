#include "threedview.h"

threeDView::threeDView(QWidget *parent) : QWidget(parent)
{
//     this->setAttribute(Qt::WA_NativeWindow);
    Initialize();
}

void threeDView::Initialize()
{
    QVBoxLayout *qvbLayMenuBar= new QVBoxLayout;
    m_qmenubarTDV = new QMenuBar();
    m_qmenubarTDV->setObjectName("m_qmenubar");
  /* m_qmenubarTDV->setStyleSheet("#m_qmenubarTDV{"
                                "border-left:.5px solid #272424;"
                                "border-top:.5px solid #272424;"
                                "border-right:.5px solid #272424;"
                                "background: #000000;}");*/

    m_qmenubarTDV->setLayoutDirection( Qt::RightToLeft);
    m_qacMaximTDV= new  QAction(QIcon(":/res/icons/max1.png"),"");
    connect(m_qacMaximTDV, &QAction::triggered, this, &threeDView:: maxThisTDV);
    m_qacHideTDV=    new QAction(QIcon(":/res/icons/hide1.png"),"");
    connect(m_qacHideTDV, &QAction::triggered, this, &threeDView::hideThisTDV);
    m_qmenubarTDV->addAction(m_qacMaximTDV);
    //    m_qmenubarTDV->addAction(m_qacHideTDV);
    m_qmenubarTDV->addMenu(new QMenu("3D"));

                //qvbLayMenuBar->setMenuBar(m_qmenubarTDV); //commented for TKA

    m_objThreeDRender= new ThreeDRender;
    //    m_objClassThreeD= &ClassThreeD::getInstance();
    qvbLayMenuBar->addWidget(m_objThreeDRender);

    this->setLayout(qvbLayMenuBar);
}

void threeDView::hideThisTDV()
{
    emit hideTDV();
}

void threeDView::maxThisTDV()
{
    emit maxTDV();
    maxFromBut();
}

void threeDView::maxFromBut()
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

