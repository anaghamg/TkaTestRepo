#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

//      m_objSinglePaneViewer= new SinglePaneViewer;
 this->setStyleSheet("background-color: black;");

    m_pqbResetWindow = new ControlButton;
    m_pqbResetWindow->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1resetwindow.png"); /*!< Button for selecting single pane image viewer mode. */
    m_pqbResetWindow->setToolTip("Reset window");

    m_pqbSinPaneViewer          = new ControlButton;
    m_pqbSinPaneViewer->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1sinwin.png"); /*!< Button for selecting single pane image viewer mode. */
    m_pqbSinPaneViewer->setToolTip("Single window");
    m_pqbTwoSquarePaneViewer         = new ControlButton; /*!< Button for selecting four pane image viewer mode. */
    m_pqbTwoSquarePaneViewer->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1fourwin.png");
    m_pqbTwoSquarePaneViewer->setToolTip("Four window");
    m_pqbEnableAntns            = new ControlButton; /*!< Button to enable/disable corner annotations. */
    m_pqbEnableAntns->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1textAntns.png");
    m_pqbEnableAntns->setToolTip("Enable/Disable Corner Annotations");

    m_pqbShowHideScanDetails    = new ControlButton; /*!< Button to enable/disable scan details pane. */
    m_pqbShowHideScanDetails->SetThumbnail(QDir::currentPath()+ "/imageviewerIcon/1showlist.png");
    m_pqbShowHideScanDetails->setToolTip("Show/Hide Sequence List");
    m_pqbImgFolderLoc           = new ControlButton; /*!< Button to set image folder location. */
    m_pqbImgFolderLoc->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1folderopen.png");
    m_pqbImgFolderLoc->setToolTip("Select Image Directory");
    m_pqbRotateLeft             = new ControlButton; /*!< Button to rotate image left. */
    m_pqbRotateLeft->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1rotateleft.png");
    m_pqbRotateLeft->setToolTip("Rotate Image Left");
    m_pqbRotateRight            = new ControlButton; /*!< Button to rotate image right. */
    m_pqbRotateRight->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1rotateright.png");
    m_pqbRotateRight->setToolTip("Rotate Image Right");


    m_pqbSendToPACS             = new ControlButton; /*!< Button to send image to PACS. */
    m_pqbSendToPACS->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1pacssend.png");
    m_pqbSendToPACS->setToolTip("Send to PACS");
    m_pqbLine                   = new ControlButton; /*!< Button to select draw line operation. */
    m_pqbLine->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1line.png");
    m_pqbLine->setToolTip("Draw Line-Graphical Annotation");
    m_pqbAngle                  = new ControlButton; /*!< Button to select draw angle operation. */
    m_pqbAngle->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1angle.png");
    m_pqbAngle->setToolTip("Measure Angle-Graphical Annotation");
    m_pqbDistance               = new ControlButton; /*!< Button to select distance measurement operation. */
    m_pqbDistance->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1distance.png");
    m_pqbDistance->setToolTip("Measure Distance-Graphical Annotation");
    m_pqbClear                  = new ControlButton; /*!< Button to select clear line, angle, distance measurement annotations from viewer. */
    m_pqbClear->SetThumbnail(QDir::currentPath()+"/imageviewerIcon/1clear.png");
    m_pqbClear->setToolTip("Clear Graphical Annotations");


    auto qlControls    = new QVBoxLayout;
    auto wdControls     = new QWidget;
  /*  wdControls->setStyleSheet("background-color: rgba(0, 0, 0, 20%);");*/
  //  wdControls->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #55497b, stop: 0.7 #4c426f, stop: 1.0 #443a62);");

    qlControls->setAlignment(Qt::AlignHCenter |  Qt::AlignTop);
    wdControls->setLayout(qlControls);
    qlControls->setContentsMargins(5, 0, 0, 0);
    qlControls->setSpacing(0);
    qlControls->setMargin(3);


    qlControls->addStretch(10);
    //    qlControls->addSpacing(3);
//    qlControls->addWidget(m_pqbImgFolderLoc, 5, Qt::AlignHCenter |  Qt::AlignTop);
//    qlControls->addWidget(m_pqbShowHideScanDetails, 5, Qt::AlignHCenter |  Qt::AlignTop);
//    qlControls->addWidget(m_pqbSinPaneViewer, 5, Qt::AlignHCenter |  Qt::AlignTop);
//    qlControls->addWidget(m_pqbTwoSquarePaneViewer, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addWidget(m_pqbEnableAntns, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addWidget(m_pqbRotateLeft, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addWidget(m_pqbRotateRight, 5, Qt::AlignHCenter |  Qt::AlignTop);
//    qlControls->addWidget(m_pqbResetWindow, 5, Qt::AlignHCenter |  Qt::AlignTop);
//    qlControls->addWidget(m_pqbSendToPACS, 5, Qt::AlignHCenter |  Qt::AlignTop);
    //    QFrame *sep2 = new QFrame;
    //    sep2->setFrameShape(QFrame::VLine);
    //    sep2->setFrameShadow(QFrame::Sunken);
    //    qlControls->addWidget(sep2, 10, Qt::AlignHCenter);
    qlControls->addStretch(5);
    qlControls->addWidget(m_pqbLine, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addWidget(m_pqbAngle, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addWidget(m_pqbDistance, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addWidget(m_pqbClear, 5, Qt::AlignHCenter |  Qt::AlignTop);
    qlControls->addStretch(40);



//    QWidget *testwd= new QWidget;
//    auto qlCentral = new QHBoxLayout;
//    QWidget *qwidCentral= new QWidget;
//    qwidCentral->setObjectName("qwidCentral");
//    qwidCentral->setStyleSheet("#qwidCentral{background-color: black;}");
//    qwidCentral->setLayout(qlCentral);
//    qlCentral->setAlignment(Qt::AlignHCenter);
//    qlCentral->addWidget(wdControls, 3);
//    qlCentral->addWidget(m_objviewerReslice, 97);
    this->setLayout(qlControls);


}

Widget::~Widget()
{
}

