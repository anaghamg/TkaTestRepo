#include "coronalview.h"

CoronalView::CoronalView(QWidget *parent) : QWidget(parent)
{
//     this->setAttribute(Qt::WA_NativeWindow);
    
    Initialize();
}



void CoronalView::Initialize()
{
    
    QVBoxLayout *qvbLayMenuBar= new QVBoxLayout;
    m_qmenubarCoronal = new QMenuBar();
    m_qmenubarCoronal->setObjectName("m_qmenubar");
   /*m_qmenubarCoronal->setStyleSheet("#m_qmenubarCoronal{"
                                    "border-left:.5px solid #272424;"
                                    "border-top:.5px solid #272424;"
                                    "border-right:.5px solid #272424;"
                                    "background: #000000;}");*/

    m_qmenubarCoronal->setLayoutDirection( Qt::RightToLeft);
    m_qacMaximCoronal= new  QAction(QIcon(":/res/icons/max1.png"),"");
    connect(m_qacMaximCoronal, &QAction::triggered, this, &CoronalView:: maxThisCoronal);
    m_qacHideCoronal=    new QAction(QIcon(":/res/icons/hide1.png"),"");
    connect(m_qacHideCoronal, &QAction::triggered, this, &CoronalView::hideThisCoronal);
    m_qmenubarCoronal->addAction(m_qacMaximCoronal);
//    m_qmenubarCoronal->addAction(m_qacHideCoronal);
            //qvbLayMenuBar->setMenuBar(m_qmenubarCoronal); //commented for TKA
    m_qmenubarCoronal->addMenu(new QMenu("Coronal"));
    m_objClassCoronalView= new ClassCoronalView;
//    m_objClassCoronalView= new viewerReslice;
//    m_objClassCoronalView = &ClassCoronalView :: getInstance();

    m_objWidget = new Widget;
QHBoxLayout *horButLay= new QHBoxLayout;
//horButLay->addWidget(m_objWidget,2);
horButLay->addWidget(m_objClassCoronalView);//,98);
    qvbLayMenuBar->addLayout(horButLay);

    this->setLayout(qvbLayMenuBar);
    
    
}

void CoronalView::hideThisCoronal()
{
    emit hideCoronal();
}

void CoronalView::maxThisCoronal()
{
//    emit maxCoronal();
    maxFromBut();
}

void CoronalView::maxFromBut()
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


