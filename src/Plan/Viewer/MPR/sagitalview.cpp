#include "sagitalview.h"

sagitalView::sagitalView(QWidget *parent) : QWidget(parent)
{
    Initialize();
}

void sagitalView::Initialize()
{
//     this->setAttribute(Qt::WA_NativeWindow);
    QVBoxLayout *qvbLayMenuBar= new QVBoxLayout;
    m_qmenubarSagital = new QMenuBar();
    m_qmenubarSagital->setObjectName("m_qmenubar");
  /* m_qmenubarSagital->setStyleSheet("#m_qmenubarSagital{"
                                    "border-left:.5px solid #272424;"
                                    "border-top:.5px solid #272424;"
                                    "border-right:.5px solid #272424;"
                                    "background: #000000;}");*/

    m_qmenubarSagital->setLayoutDirection( Qt::RightToLeft);
    m_qacMaximSagital= new  QAction(QIcon(":/res/icons/max1.png"),"");
    connect(m_qacMaximSagital, &QAction::triggered, this, &sagitalView:: maxThisSagital);
    m_qacHideSagital=    new QAction(QIcon(":/res/icons/hide1.png"),"");
    connect(m_qacHideSagital, &QAction::triggered, this, &sagitalView::hideThisSagital);
    m_qmenubarSagital->addAction(m_qacMaximSagital);
//    m_qmenubarSagital->addAction(m_qacHideSagital);
            //qvbLayMenuBar->setMenuBar(m_qmenubarSagital); //commented for TKA
     m_qmenubarSagital->addMenu(new QMenu("Sagittal"));
    m_objClassSagittalView= new ClassSagittalView;

    m_objWidget = new Widget;
QHBoxLayout *horButLay= new QHBoxLayout;
//horButLay->addWidget(m_objWidget,2);
horButLay->addWidget(m_objClassSagittalView);//,98);
//    m_objClassSagittalView = new viewerReslice;
//    m_objClassSagittalView= &ClassSagittalView::getInstance();
    qvbLayMenuBar->addLayout(horButLay);
    
    this->setLayout(qvbLayMenuBar);
    
    
}

void sagitalView::hideThisSagital()
{
    emit hideSagital();
}

void sagitalView::maxThisSagital()
{
//    emit maxSagital();
    maxFromBut();
}

void sagitalView::maxFromBut()
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


