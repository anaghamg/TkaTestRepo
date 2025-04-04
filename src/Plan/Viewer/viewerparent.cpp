#include "viewerparent.h"

viewerParent::viewerParent(QWidget *parent) : QWidget(parent)
{
    //   this->setAttribute(Qt::WA_NativeWindow);
    this->setObjectName("viewerParentobj");
    this->setStyleSheet ( "QWidget#viewerParentobj"
                          "{"
                          "border: 1"
                          "px transparent black;"
                          "background-color: black;}");
    Initialize();
}

void viewerParent::Initialize()
{
    dummyForDelet= new QWidget;
    dummyForDelet->setObjectName("dummyForDelet");
    dummyForDelet->setStyleSheet ( "#dummyForDelet"
                                   "{"
                                   "background-color: black;}");

    m_objannotation = new Annotation;  //layout for F,T annotation
    m_objmdiHolderMPR= new mdiHolderMPR;

    m_qswPlanUI = new QStackedWidget;
    m_qswPlanUI->insertWidget(0,dummyForDelet);
    m_qswPlanUI->insertWidget(1,m_objmdiHolderMPR);
    m_qswPlanUI->setCurrentIndex(1); //0  //anagha


    QHBoxLayout *qhblTabHold= new QHBoxLayout;
    qhblTabHold->addWidget(m_qswPlanUI,80);
    qhblTabHold->addWidget(m_objannotation,20);
    qhblTabHold->setContentsMargins(0,0,0,0);
    this->setLayout(qhblTabHold);

    //added by anagha 31-07-2024
    connect(m_objannotation,&Annotation::signalEnablePointSelection,
            m_objmdiHolderMPR, &mdiHolderMPR::EnablePointSelection);

    //slot to receive whether Femur/Tibia selected ; landmark point id, landmark name
    connect(m_objannotation,&Annotation::signalAnatomyAnnotation,
            m_objmdiHolderMPR,&mdiHolderMPR::slotAnatomyAnnotation);

    connect(m_objannotation,&Annotation::signalAnatomyAnnotation,
            m_objmdiHolderMPR->m_objsavelandmark, &savelandmark::slotLandmarkFeatures);

    connect(m_objmdiHolderMPR,&mdiHolderMPR::signalpointselected,
            m_objannotation, &Annotation::slotpointchecked);//parvathy- for checking if point is selected in mpr

    //dhanyasree //mpr wl/ww reset
    // connect(/*m_objplanBut->*/m_objannotation->m_qpbReset,&QPushButton::clicked,this->m_objmdiHolderMPR,&mdiHolderMPR::setMPRreset);

}

void viewerParent::selectMPR()
{
    m_qswPlanUI->setCurrentIndex(1) ;
}

void viewerParent::newDataPath(QString segpath,QString fullpath, QString selKnee)
{
    if(blFirstTime)
    {
        qDebug()<<"blFirstTime = true";

        blFirstTime=false;
        m_objmdiHolderMPR->SetDicomDirectory(segpath,fullpath, selKnee);
        m_qswPlanUI->setCurrentIndex(1);
    }
    else
    {
        qDebug()<<"blFirstTime = false";
        m_qswPlanUI->insertWidget(2,new QWidget);
        m_qswPlanUI->insertWidget(1,new QWidget);
        delete m_objmdiHolderMPR;

        m_objmdiHolderMPR= new mdiHolderMPR;

        m_qswPlanUI->insertWidget(1,m_objmdiHolderMPR);
        m_objmdiHolderMPR->SetDicomDirectory(segpath,fullpath, selKnee);
        m_qswPlanUI->setCurrentIndex(1);

        connect(m_objannotation,&Annotation::signalEnablePointSelection,
                m_objmdiHolderMPR, &mdiHolderMPR::EnablePointSelection);

        //slot to receive whether Femur/Tibia selected ; landmark point id, landmark name
        connect(m_objannotation,&Annotation::signalAnatomyAnnotation,
                m_objmdiHolderMPR,&mdiHolderMPR::slotAnatomyAnnotation);

        connect(m_objannotation,&Annotation::signalAnatomyAnnotation,
                m_objmdiHolderMPR->m_objsavelandmark, &savelandmark::slotLandmarkFeatures);

    }
}
