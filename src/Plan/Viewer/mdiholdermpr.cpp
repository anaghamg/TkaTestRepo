#include "mdiholdermpr.h"
#include <QVBoxLayout>
mdiHolderMPR::mdiHolderMPR(QWidget *parent) : QWidget(parent)
{
    m_objsavelandmark = new savelandmark;
    m_qMdiAreaforMPR = new QMdiArea;

    QVBoxLayout *Lay= new QVBoxLayout;
    Lay->addWidget(m_qMdiAreaforMPR);
    this->setLayout(Lay);

    //    setCentralWidget(m_qMdiAreaforMPR);

    m_objthreeDView= new threeDView;
    m_objthreeDView->setObjectName("m_objthreeDView");
    m_objthreeDView->setStyleSheet ( "QWidget#m_objthreeDView"
                                     "{"
                                     "background-color: black;"
                                     "}");
    //    m_objthreeDView=  threeDView:: getInstance();
    connect(m_objthreeDView, &threeDView::hideTDV, this, &mdiHolderMPR::hindTheSubWindow);
    connect(m_objthreeDView, &threeDView::maxTDV, this, &mdiHolderMPR::maxTheSubWindow);

    m_objaxialView = new axialView;
    //    m_objaxialView=  axialView:: getInstance();
    connect(m_objaxialView, &axialView::hideAxial, this, &mdiHolderMPR::hindTheSubWindow);
    connect(m_objaxialView, &axialView::maxAxial, this, &mdiHolderMPR::maxTheSubWindow);

    //    //Axial's Callback
    //    m_objthreeDView->m_objmainpage->cbk->IPW[0] = m_objthreeDView->m_objmainpage->planeWidget[0];
    //    m_objthreeDView->m_objmainpage->cbk->RCW[0] = m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->GetResliceCursorWidget();
    //    m_objaxialView->m_objClassAxialView-> m_ResliceImageViewerAxial->SetResliceCursor(m_objaxialView->m_objClassAxialView-> m_ResliceImageViewerAxial->GetResliceCursor());
    //    m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent,  m_objthreeDView->m_objmainpage->cbk);
    //    m_objthreeDView->m_objmainpage->planeWidget[0]->AddObserver(vtkCommand::InteractionEvent, m_objthreeDView->m_objmainpage->cbk);
    //    m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->AddObserver(vtkResliceImageViewer::SliceChangedEvent, m_objthreeDView->m_objmainpage->cbk);

    m_objCoronalView= new CoronalView;
    //    m_objCoronalView=  CoronalView:: getInstance();
    connect(m_objCoronalView, &CoronalView::hideCoronal, this, &mdiHolderMPR::hindTheSubWindow);
    connect(m_objCoronalView, &CoronalView::maxCoronal, this, &mdiHolderMPR::maxTheSubWindow);

    //    //Coronal's callback
    //    m_objthreeDView->m_objmainpage->cbk->IPW[1] = m_objthreeDView->m_objmainpage->planeWidget[1];
    //    m_objthreeDView->m_objmainpage->cbk->RCW[1] = m_objCoronalView->m_objClassCoronalView ->m_ResliceImageViewerCoronal->GetResliceCursorWidget();
    //    m_objCoronalView->m_objClassCoronalView-> m_ResliceImageViewerCoronal->SetResliceCursor(m_objaxialView->m_objClassAxialView-> m_ResliceImageViewerAxial->GetResliceCursor());
    //    m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent,  m_objthreeDView->m_objmainpage->cbk);
    //    m_objthreeDView->m_objmainpage->planeWidget[1]->AddObserver(vtkCommand::InteractionEvent, m_objthreeDView->m_objmainpage->cbk);
    //    m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->AddObserver(vtkResliceImageViewer::SliceChangedEvent, m_objthreeDView->m_objmainpage->cbk);

    m_objsagitalView= new sagitalView;
    //    m_objsagitalView=  sagitalView :: getInstance();
    connect(m_objsagitalView, &sagitalView::hideSagital, this, &mdiHolderMPR::hindTheSubWindow);
    connect(m_objsagitalView, &sagitalView::maxSagital, this, &mdiHolderMPR::maxTheSubWindow);

    //    //Sagittal's callback
    //    m_objthreeDView->m_objmainpage->cbk->IPW[2] = m_objthreeDView->m_objmainpage->planeWidget[2];
    //    m_objthreeDView->m_objmainpage->cbk->RCW[2] = m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->GetResliceCursorWidget();
    //    m_objsagitalView->m_objClassSagittalView-> m_ResliceImageViewerSagittal->SetResliceCursor(m_objaxialView->m_objClassAxialView-> m_ResliceImageViewerAxial->GetResliceCursor());
    //    m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->GetResliceCursorWidget()->AddObserver(vtkResliceCursorWidget::ResliceAxesChangedEvent,  m_objthreeDView->m_objmainpage->cbk);
    //    m_objthreeDView->m_objmainpage->planeWidget[2]->AddObserver(vtkCommand::InteractionEvent, m_objthreeDView->m_objmainpage->cbk);
    //    m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->AddObserver(vtkResliceImageViewer::SliceChangedEvent, m_objthreeDView->m_objmainpage->cbk);

    m_objsubwindowCustAxial= new subwindowCust;
    m_objsubwindowCustAxial->setObjectName("m_objsubwcust");
    m_objsubwindowCustAxial->setWindowFlags(Qt::WindowTitleHint | Qt::FramelessWindowHint);
    m_objsubwindowCustAxial->setAttribute(Qt::WA_DeleteOnClose);
    m_objsubwindowCustAxial->setStyleSheet("subwindowCust { border-right: 2px solid #1a1a1a;border-bottom: 2px solid #1a1a1a; background: #000000 ;}");
    m_objsubwindowCustAxial->setWidget(m_objaxialView);
    m_listmdisubwindow.append(m_objsubwindowCustAxial);
    //m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustAxial)->setWindowState(Qt::WindowMaximized);
    m_objsubwindowCustAxial->show();
    m_qMdiAreaforMPR->tileSubWindows();
    m_qMdiAreaforMPR->setViewMode(QMdiArea::SubWindowView);
    m_qMdiAreaforMPR->showMaximized();
   // m_qMdiAreaforMPR->adjustSize();

    m_objsubwindowCustCoronal= new subwindowCust();
    m_objsubwindowCustCoronal->setObjectName("m_objsubwcust");
    m_objsubwindowCustCoronal->setStyleSheet("#m_objsubwcust{border-right:2px solid #1a1a1a; background: #000000;}");
    m_objsubwindowCustCoronal->setWindowFlags(Qt::WindowTitleHint | Qt:: FramelessWindowHint);
    m_objsubwindowCustCoronal->setAttribute(Qt::WA_DeleteOnClose);
    m_objsubwindowCustCoronal->setWidget(m_objCoronalView);
    m_listmdisubwindow.append(m_objsubwindowCustCoronal);
    //m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustCoronal)->setWindowState(Qt::WindowMaximized) ;
    m_objsubwindowCustCoronal->show();
    m_qMdiAreaforMPR->tileSubWindows();
    m_qMdiAreaforMPR->setViewMode(QMdiArea::SubWindowView);
    m_qMdiAreaforMPR->showMaximized();
    //m_qMdiAreaforMPR->adjustSize();

    m_objsubwindowCustSagittal= new subwindowCust();
    m_objsubwindowCustSagittal->setObjectName("m_objsubwcust");
   // m_objsubwindowCustSagittal->setStyleSheet("#m_objsubwcust{border-left: 2px solid red background: #000000;}");
    m_objsubwindowCustSagittal->setWindowFlags(Qt::WindowTitleHint | Qt:: FramelessWindowHint);
    m_objsubwindowCustSagittal->setAttribute(Qt::WA_DeleteOnClose);
    m_objsubwindowCustSagittal->setWidget(m_objsagitalView);
    m_listmdisubwindow.append(m_objsubwindowCustSagittal);
    //m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustSagittal)->setWindowState(Qt::WindowMaximized) ;
    m_objsubwindowCustSagittal->show();
    m_qMdiAreaforMPR->tileSubWindows();
    m_qMdiAreaforMPR->setViewMode(QMdiArea::SubWindowView);
    m_qMdiAreaforMPR->showMaximized();
    m_qMdiAreaforMPR->adjustSize();

    m_objsubwindowCustThreeD= new subwindowCust();
    m_objsubwindowCustThreeD->setObjectName("m_objsubwcust");
    m_objsubwindowCustThreeD->setStyleSheet("#m_objsubwcust{border-bottom: 2px solid #1a1a1a; background: #000000;}");
    m_objsubwindowCustThreeD->setWindowFlags(Qt::WindowTitleHint | Qt:: FramelessWindowHint);
    m_objsubwindowCustThreeD->setAttribute(Qt::WA_DeleteOnClose);
    m_objsubwindowCustThreeD->setWidget(m_objthreeDView);
    m_listmdisubwindow.append(m_objsubwindowCustSagittal);
    //m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustThreeD)->setWindowState(Qt::WindowMaximized) ;
    m_objsubwindowCustThreeD->show();
    m_qMdiAreaforMPR->tileSubWindows();
    m_qMdiAreaforMPR->setViewMode(QMdiArea::SubWindowView);
    m_qMdiAreaforMPR->showMaximized();
    m_qMdiAreaforMPR->adjustSize();

    //MPR view order
    m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustSagittal)->setWindowState(Qt::WindowMaximized) ;
    m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustCoronal)->setWindowState(Qt::WindowMaximized) ;
    m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustThreeD)->setWindowState(Qt::WindowMaximized) ;
    m_qMdiAreaforMPR->addSubWindow(m_objsubwindowCustAxial)->setWindowState(Qt::WindowMaximized);




    //setMPRConnections();

    //anagha
     connect(this, &mdiHolderMPR::signalDcmDirectory,
             this,&mdiHolderMPR::setMPRConnections);

    // save picked points from windows to xml
    connect(this, &mdiHolderMPR::signalPickedPt,
            m_objsavelandmark , &savelandmark::slotLandmarkPoint);

    //checking if point is sleceted in coronal view
    connect(m_objCoronalView->m_objClassCoronalView, &ClassCoronalView::pointinCoronal,
            this , &mdiHolderMPR::slotpointincoronal);

    //emit the picked signal from any of the classes(A,C,S,3D) to this slot
    connect(m_objaxialView->m_objClassAxialView, &ClassAxialView::signalPickedPtAxial,
            this , &mdiHolderMPR::updateSlice);
    connect(m_objCoronalView->m_objClassCoronalView, &ClassCoronalView::signalPickedPtCoronal,
            this , &mdiHolderMPR::updateSlice);
    connect(m_objsagitalView->m_objClassSagittalView, &ClassSagittalView::signalPickedPtSagittal,
            this , &mdiHolderMPR::updateSlice);
    connect(m_objthreeDView->m_objThreeDRender, &ThreeDRender::signalPickedPt3D,
            this , &mdiHolderMPR::updateSlice);




//    selectedAnatomies.insert("Femur_1_Hip Centre");//manually add hip center to qset
    slotAnatomyAnnotation("Femur", 1, "Hip Centre");

}

void mdiHolderMPR::setMPRConnections(QString qstrDicomPath, QString fullpath, QString selKnee)
{
    //Main reader
     //m_qstrDcmDir = QDir::currentPath() + "/Plan/Viewer/one_phantom/ScalarVolume_17";

    m_qstrDcmDir = qstrDicomPath; //3d; segmented path
    m_qstrfullpath = fullpath;//acs //fullpath
    m_qstrselKnee = selKnee;

    qDebug()<<"full path "<<fullpath<<qstrDicomPath<<selKnee;


    reader->SetDirectoryName(m_qstrfullpath.toUtf8().constData()); //full 3d
    //reader->SetDirectoryName(m_qstrDcmDir.toUtf8().constData());//only f/t


    qDebug()<<"Dicom dir in setMPRConnections : "<<reader->GetDirectoryName();

    reader->Update();


   //calculate the offset for coronal
    int* dims = reader->GetOutput()->GetDimensions();
    imgwidth = dims[0];
    double* pxspacing= reader->GetOutput()->GetSpacing();
    pixelspacing= pxspacing[0];
    offsetcoronal = imgwidth * pixelspacing;



    qDebug()<<"after 3d update";

//    //load segmented femur/tibia in 3D view
//    m_objthreeDView->m_objThreeDRender->ThreeDView(reader);
//    qDebug()<<"after m_objthreeDView";
    m_objthreeDView->m_objThreeDRender->Femur3D();
    m_objthreeDView->m_objThreeDRender->Tibia3D();
    m_objthreeDView->m_objThreeDRender->ThreeDView(reader);

//        m_objaxialView->m_objClassAxialView->axialView(reader);
//        m_objCoronalView->m_objClassCoronalView->coronalView(reader);
//        m_objsagitalView->m_objClassSagittalView->sagittalView(reader);

    //load unsegmented knee in ACS
  // QString qstrFullknee = QDir::currentPath()+"/Plan/Viewer/right/knee_rt";
     //QString qstrFullknee = QDir::currentPath()+"/Plan/Viewer/ScalarVolume_17";\\phantom
    readerACS->SetDirectoryName(m_qstrfullpath.toUtf8().constData());
    qDebug()<<"Dicom dir in setMPRConnections(ACS) :"<<readerACS->GetDirectoryName();
    readerACS->Update();



    m_objaxialView->m_objClassAxialView->axialView(readerACS,m_qstrselKnee);
    m_objCoronalView->m_objClassCoronalView->coronalView(readerACS,m_qstrselKnee);
    m_objsagitalView->m_objClassSagittalView->sagittalView(readerACS);

    //Axial
    RCW[2] = m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->GetResliceCursorWidget();

    //Coronal

    //commented by dhanyasree
                //m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->SetResliceCursor(m_objaxialView->m_objClassAxialView-> m_ResliceImageViewerAxial->GetResliceCursor());
    RCW[0] = m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->GetResliceCursorWidget();

    //Sagittal
    //commented by dhanyasree
                //m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->SetResliceCursor(m_objaxialView->m_objClassAxialView-> m_ResliceImageViewerAxial->GetResliceCursor());
    RCW[1] = m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->GetResliceCursorWidget();


    //added by anagha  //recheck
        m_objthreeDView->m_objThreeDRender->m_3DRenderWindow->GetInteractor()->Render();


        //d

               sliceCenter1_coronal = RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->GetCenter();
               sliceCenter2_sagittal= RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->GetCenter();
               sliceCenter3_axial =RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->GetCenter();

               qDebug()<<sliceCenter1_coronal[0]<<sliceCenter1_coronal[1]<<sliceCenter1_coronal[2]<<"  coronal";
               qDebug()<<sliceCenter2_sagittal[0]<<sliceCenter2_sagittal[1]<<sliceCenter2_sagittal[2]<<"  sagital";
               qDebug()<<sliceCenter3_axial[0]<<sliceCenter3_axial[1]<<sliceCenter3_axial[2]<<"  axial";

               SliceSlot();


}

void mdiHolderMPR::slotAnatomyAnnotation(QString bone_name, int anatomyid, const QString& anatomy)
{    
    qDebug()<<"***********slotAnatomyAnnotation";

    QString anatomyKey = bone_name + "_" + QString::number(anatomyid) + "_" + anatomy;
    qDebug()<<"anatomyKey"<<anatomyKey;

//    //temp
//    if(bone_name == "Hip Centre")
//    {
//        qDebug()<<"set hip center bool true";
//        isRepeatSelection = true;
//    }



    isRepeatSelection = selectedAnatomies.contains(anatomyKey);

    qDebug() << "isRepeatSelection??"<<isRepeatSelection;



    if (isRepeatSelection)
    {
        qDebug()<<"Parse for "<<bone_name<<anatomyid<<anatomy;

        // If anatomy was previously selected, retrieve the coordinates and update slice
        std::array<double, 3> point = parseXML("Landmark.xml", bone_name, anatomyid, anatomy);

        if (!point.empty())
        {
            qDebug() << "Coordinates found in XML file:" << point[0] << point[1] << point[2];
            updateSlice(point);  // Call updateSlice with only point
        } else {
            qDebug() << "No matching point found in XML for" << bone_name << anatomyid << anatomy;
        }
    }


    else {
        // First-time selection, add to the set
        selectedAnatomies.insert(anatomyKey);
    }
}

void mdiHolderMPR::showCrossHairsAxial(std::array<double, 3> pt, vtkRenderer *renderer)
{
    vtkSmartPointer<vtkAppendPolyData> crosshair_appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    vtkSmartPointer<vtkPolyDataMapper> crosshair_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> crosshair_actor = vtkSmartPointer<vtkActor>::New();

    // Create line sources for the axial crosshair
    axialLine1->SetPoint1(pt[0] - 5.0, pt[1], pt[2]);
    axialLine1->SetPoint2(pt[0] + 5.0, pt[1], pt[2]);

    axialLine2->SetPoint1(pt[0], pt[1] - 5.0, pt[2]);
    axialLine2->SetPoint2(pt[0], pt[1] + 5.0, pt[2]);

    // Append the lines to create combined crosshairs
    crosshair_appendFilter->AddInputConnection(axialLine1->GetOutputPort());
    crosshair_appendFilter->AddInputConnection(axialLine2->GetOutputPort());
    crosshair_appendFilter->Update();

    crosshair_mapper->SetInputConnection(crosshair_appendFilter->GetOutputPort());

    crosshair_actor->SetMapper(crosshair_mapper);
    crosshair_actor->GetProperty()->SetColor(1.0, 1.0, 0.0); // yellow color for the crosshair
    crosshair_actor->GetProperty()->SetLineWidth(3.0);

    renderer->AddActor(crosshair_actor);
    renderer->Render();
}

void mdiHolderMPR::showCrossHairsCoronal(std::array<double, 3> pt, vtkRenderer *renderer)
{
    vtkSmartPointer<vtkAppendPolyData> crosshair_appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    vtkSmartPointer<vtkPolyDataMapper> crosshair_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> crosshair_actor = vtkSmartPointer<vtkActor>::New();


    // Create line sources for the coronal crosshair
    coronalLine1->SetPoint1(offsetcoronal-pt[0] - 5.0, pt[1],pt[2]); // pt[0] - 5.0, 0.0, pt[2] was working! don't know why
    coronalLine1->SetPoint2(offsetcoronal-pt[0] + 5.0, pt[1], pt[2]);

    coronalLine2->SetPoint1(offsetcoronal-pt[0], pt[1], pt[2] - 5.0);
    coronalLine2->SetPoint2(offsetcoronal-pt[0], pt[1], pt[2] + 5.0);

    // Append the lines to create combined crosshairs
    crosshair_appendFilter->AddInputConnection(coronalLine1->GetOutputPort());
    crosshair_appendFilter->AddInputConnection(coronalLine2->GetOutputPort());
    crosshair_appendFilter->Update();

    crosshair_mapper->SetInputConnection(crosshair_appendFilter->GetOutputPort());

    crosshair_actor->SetMapper(crosshair_mapper);
    crosshair_actor->GetProperty()->SetColor(1.0, 1.0, 0.0); // yellow color for the crosshair
    crosshair_actor->GetProperty()->SetLineWidth(3.0);

    renderer->AddActor(crosshair_actor);
    renderer->Render();
}

void mdiHolderMPR::showCrossHairsSagittal(std::array<double, 3> pt, vtkRenderer *renderer)
{
    vtkSmartPointer<vtkAppendPolyData> crosshair_appendFilter = vtkSmartPointer<vtkAppendPolyData>::New();
    vtkSmartPointer<vtkPolyDataMapper> crosshair_mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> crosshair_actor = vtkSmartPointer<vtkActor>::New();

    // Create line sources for the sagittal crosshair
    sagittalLine1->SetPoint1(pt[0], pt[1] - 5.0, pt[2]);
    sagittalLine1->SetPoint2(pt[0], pt[1] + 5.0, pt[2]);

    sagittalLine2->SetPoint1(pt[0], pt[1], pt[2] - 5.0);
    sagittalLine2->SetPoint2(pt[0], pt[1], pt[2] + 5.0);

    // Append the lines to create combined crosshairs
    crosshair_appendFilter->AddInputConnection(sagittalLine1->GetOutputPort());
    crosshair_appendFilter->AddInputConnection(sagittalLine2->GetOutputPort());
    crosshair_appendFilter->Update();

    crosshair_mapper->SetInputConnection(crosshair_appendFilter->GetOutputPort());

    crosshair_actor->SetMapper(crosshair_mapper);
    crosshair_actor->GetProperty()->SetColor(1.0, 1.0, 0.0); // yellow color for the crosshair
    crosshair_actor->GetProperty()->SetLineWidth(3.0);

    renderer->AddActor(crosshair_actor);
    renderer->Render();
}


void mdiHolderMPR::SetDicomDirectory(QString qstrDcmDir,QString fullpath, QString selKnee)
{
    QString dcmPath = qstrDcmDir;
    QString fullPath = fullpath;
    QString SelKnee = selKnee;
    qDebug()<<"SetDicomDirectory in mdiHolderMPR "<<dcmPath<<fullPath;
    emit signalDcmDirectory(dcmPath,fullPath, SelKnee);
}


//checking if poitn

void mdiHolderMPR::slotpointincoronal(bool coronalpoint)
{
    pointincoronal = coronalpoint;
}

//for 3d : draw a sphere at received position
//for acs : set reslice origin to picked pos; pass picked pos to draw crosshair at that loc
//for saving point : emit signal to save in xml file
void mdiHolderMPR::updateSlice(std::array<double, 3> pt)
{
    //parvathy- for checking if point is selected in mpr
   pointchecked = true;
   emit signalpointselected(pointchecked);
   pointchecked = false;

//   if (!isRepeatSelection) {
//          emit signalpointselected(true);
//      }

   //parvathy -//check if point is selected from coronal, if true, subtrct the offset before saving to xml
   if (pointincoronal )
   {
     m_mdiPickedPt ={ offsetcoronal-pt[0],pt[1],pt[2]};
     pointincoronal=false;
   }
   else
   {
     m_mdiPickedPt = pt;
       pointincoronal= false;
   }

    qDebug()<<"Update slice";

    threedpt->SetCenter(pt[0],pt[1],pt[2]);
    threedpt->SetRadius(4.0);
    threedpt_mapper->SetInputConnection(threedpt->GetOutputPort());
    threedpt_actor->SetMapper(threedpt_mapper);
    threedpt_actor->GetProperty()->SetColor(1.0, 0.0, 0.0); // red color
    m_objthreeDView->m_objThreeDRender->m_3DRenderer->AddActor(threedpt_actor);

    for(int i=0; i<3; i++)
    {
        vtkResliceCursor* resliceCursor = RCW[i]->GetResliceCursorRepresentation()->GetResliceCursor();
        resliceCursor->SetCenter(pt[0], pt[1], pt[2]);

        resliceCursor->GetPlane(i)->SetOrigin(pt[0], pt[1], pt[2]);
        resliceCursor->Update();
    }

    showCrossHairsAxial(pt, m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->GetRenderer());
    showCrossHairsCoronal(pt, m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->GetRenderer());
    showCrossHairsSagittal(pt, m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->GetRenderer());

    m_objthreeDView->m_objThreeDRender->m_3DRenderWindow->GetInteractor()->Render();

    RCW[0]->GetInteractor()->Render();
    RCW[1]->GetInteractor()->Render();
    RCW[2]->GetInteractor()->Render();

    // Emit signal only if it is not a repeat selection(to avoid overwriting)
        if (!isRepeatSelection)
        {
            emit signalPickedPt(m_mdiPickedPt);
        }
}







// Function to parse XML and get the XYZ point based on bone name, anatomy ID, and anatomy
std::array<double, 3> mdiHolderMPR::parseXML(const std::string& filename, const QString& boneName,
                                             int anatomyID,  QString anatomy)
{
    qDebug() << "parseXML"<<anatomy;
    std::array<double, 3> point = {};  // Initialize with empty values (0, 0, 0)

    // Load the XML file
    vtkSmartPointer<vtkXMLDataElement> root = vtkXMLUtilities::ReadElementFromFile(filename.c_str());
    if (!root) {
        qDebug() << "Failed to load XML file:" << QString::fromStdString(filename);
        return point;  // Return an empty array if file loading fails
    }

    bool found = false;

    //diff in strings obtained from Annotation table and stored tag in XML file
    //"Hip Centre" and "Hip Center"
    if(anatomy == "Hip Centre")
    {
        qDebug()<<"renaming Hip Centre to Hip Center";
        anatomy.replace("Centre", "Center");
    }

    for (int i = 0; i < root->GetNumberOfNestedElements(); ++i)
    {
        vtkXMLDataElement* element = root->GetNestedElement(i);
        if (!element) continue;

        // Retrieve and compare attributes
        const char* xmlBoneName = element->GetAttribute("bone_name");
        const char* xmlAnatomy = element->GetAttribute("anatomy");
        int xmlAnatomyID = 0;
        element->GetScalarAttribute("anatomyid", xmlAnatomyID);

        // Perform exact match check on all attributes
        if (xmlBoneName && xmlAnatomy &&
            boneName == QString(xmlBoneName) &&
            anatomyID == xmlAnatomyID &&
            anatomy == QString(xmlAnatomy))
            // If all conditions match, retrieve the coordinates
        {
            double x = 0, y = 0, z = 0;
            element->GetScalarAttribute("x", x);
            element->GetScalarAttribute("y", y);
            element->GetScalarAttribute("z", z);

            point = {x, y, z};
            found = true;
            break;
        }
    }

    if (!found) {
        qDebug() << "No matching point found in XML for:" << boneName << anatomyID << anatomy;
    } else {
        qDebug() << "Found coordinates for" << boneName << anatomyID << anatomy << ":" << point[0] << point[1] << point[2];
    }

    return point;
}

void mdiHolderMPR::hindTheSubWindow()
{
    m_qMdiAreaforMPR->activeSubWindow()->hide();
    refreshWindow();
}

void mdiHolderMPR::maxTheSubWindow()
{
    qDebug()<<"MDIEg maxTheSubWindow-Strat";
    if(isActiveSubWinMin)
    {
        qDebug()<<"MDIEg maxTheSubWindow-isActiveSubWinMin";
        m_qMdiAreaforMPR->activeSubWindow()->showMaximized();
        isActiveSubWinMin=false;
    }
    else
    {
        qDebug()<<"MDIEg maxTheSubWindow-isActiveSubWinMin else";
        m_qMdiAreaforMPR->activeSubWindow()->showNormal();
        isActiveSubWinMin=true;
        refreshWindow();
    }
    qDebug()<<"MDIEg maxTheSubWindow-end";
}

void mdiHolderMPR::refreshWindow()
{
    qDebug()<<"MDIEg refreshwindow-Strat";
    m_qMdiAreaforMPR->subWindowList(QMdiArea::CreationOrder);
    m_qMdiAreaforMPR->activateNextSubWindow();
    m_qMdiAreaforMPR->setActivationOrder(QMdiArea::CreationOrder);
    m_qMdiAreaforMPR->tileSubWindows();
    m_qMdiAreaforMPR->setViewMode(QMdiArea::SubWindowView);
    m_qMdiAreaforMPR->showMaximized();
    qDebug()<<"MDIEg refreshwindow-End";
}

void mdiHolderMPR::EnablePointSelection()
{
    //qDebug()<<"Enable point selection";

    //m_blPointSelected = false;

    // to visualise points on windows
//    connect(m_objaxialView->m_objClassAxialView, &ClassAxialView::signalPickedPtAxial,
//            this , &mdiHolderMPR::updateSlice);
//    connect(m_objCoronalView->m_objClassCoronalView, &ClassCoronalView::signalPickedPtCoronal,
//            this , &mdiHolderMPR::updateSlice);
//    connect(m_objsagitalView->m_objClassSagittalView, &ClassSagittalView::signalPickedPtSagittal,
//            this , &mdiHolderMPR::updateSlice);
//    connect(m_objthreeDView->m_objThreeDRender, &ThreeDRender::signalPickedPt3D,
//            this , &mdiHolderMPR::updateSlice);

}

//dhanyasree
void mdiHolderMPR::SliceSlot()
{
    qDebug()<<"SliceSlot";
    connect(m_objaxialView->m_objClassAxialView, &ClassAxialView::axeSlice,
            this , &mdiHolderMPR::sliceChangeByaxial);
    connect(m_objCoronalView->m_objClassCoronalView, &ClassCoronalView::corSlice,
            this , &mdiHolderMPR::sliceChangeBycoronal);
    connect(m_objsagitalView->m_objClassSagittalView, &ClassSagittalView::sagSlice,
            this , &mdiHolderMPR::sliceChangeBysagital);

}
void mdiHolderMPR::sliceChangeByaxial(double* centre)
{

    RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(sliceCenter1_coronal[0],centre[2],sliceCenter1_coronal[2]);
    RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(centre[2],sliceCenter2_sagittal[1],sliceCenter2_sagittal[2]);
    RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(centre[0],centre[1],centre[2]);

    RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();
    RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();
    RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();

    RCW[0]->GetInteractor()->Render();
    RCW[1]->GetInteractor()->Render();
    RCW[2]->GetInteractor()->Render();
}

void mdiHolderMPR::sliceChangeBycoronal(double *centre)
{
    RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(centre[0],centre[1],centre[2]);
    RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(centre[1],sliceCenter2_sagittal[1],sliceCenter2_sagittal[2]);
    RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(sliceCenter3_axial[0],sliceCenter3_axial[1],centre[1]);

    RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();
    RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();
    RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();

    RCW[0]->GetInteractor()->Render();
    RCW[1]->GetInteractor()->Render();
    RCW[2]->GetInteractor()->Render();
}
void mdiHolderMPR::sliceChangeBysagital(double *centre)
{
    RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(sliceCenter1_coronal[0],centre[0],sliceCenter1_coronal[2]);
    RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(centre[0],centre[1],centre[2]);
    RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->SetCenter(sliceCenter3_axial[0],sliceCenter3_axial[1],centre[0]);

    RCW[0]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();
    RCW[1]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();
    RCW[2]->GetResliceCursorRepresentation()->GetResliceCursor()->Update();

    RCW[0]->GetInteractor()->Render();
    RCW[1]->GetInteractor()->Render();
    RCW[2]->GetInteractor()->Render();
}

void mdiHolderMPR::setMPRreset()
{
      m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->GetInteractorStyle()->InvokeEvent(vtkCommand::ResetWindowLevelEvent,this);
      m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->GetInteractorStyle()->InvokeEvent(vtkCommand::ResetWindowLevelEvent,this);
      m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->GetInteractorStyle()->InvokeEvent(vtkCommand::ResetWindowLevelEvent,this);


      m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->Reset();
      m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->Reset();
      m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->Reset();

      m_objCoronalView->m_objClassCoronalView->m_ResliceImageViewerCoronal->GetRenderer()->GetActiveCamera()->Zoom(1.2);
      m_objsagitalView->m_objClassSagittalView->m_ResliceImageViewerSagittal->GetRenderer()->GetActiveCamera()->Zoom(1.2);
      m_objaxialView->m_objClassAxialView->m_ResliceImageViewerAxial->GetRenderer()->GetActiveCamera()->Zoom(1.2);


      RCW[0]->GetInteractor()->Render();
      RCW[1]->GetInteractor()->Render();
      RCW[2]->GetInteractor()->Render();




}
void mdiHolderMPR::ClipTibiaFemur(int index)
{
    qDebug() << "Tibia and femur ready to clip";

//    QString filePath = QDir::currentPath() + "/Segmentation_batfile/slice_counts.txt";
//    QFile file(filePath);

//    QString tibiaSliceCount, femurSliceCount;

//    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        QTextStream in(&file);
//        while (!in.atEnd()) {
//            QString line = in.readLine();
//            if (line.startsWith("Number of slices containing tibia:")) {
//                tibiaSliceCount = line.section(':', 1).trimmed();
//            } else if (line.startsWith("Number of slices containing femur:")) {
//                femurSliceCount = line.section(':', 1).trimmed();
//            }
//        }
//        file.close();
//    }


        m_annotTabIndex = index;

        qDebug()<<"render3d index"<<index;
        if (m_annotTabIndex == 0) {

            qDebug()<<"render3d index for F"<<index;


                m_objthreeDView->m_objThreeDRender->RemoveBoneActor();
            vtkSmartPointer<vtkActor> femurActor = m_objthreeDView->m_objThreeDRender->GetFemurActor();

                m_objthreeDView->m_objThreeDRender->m_3DRenderer->AddActor(femurActor);
                qDebug() <<"femurActor _1";
        }
        else if (m_annotTabIndex == 1) {

            qDebug()<<"render3d index for T"<<index;

            m_objthreeDView->m_objThreeDRender->RemoveBoneActor();
            vtkSmartPointer<vtkActor> tibiaActor = m_objthreeDView->m_objThreeDRender->GetTibiaActor();

                m_objthreeDView->m_objThreeDRender->m_3DRenderer->AddActor(tibiaActor);
                 qDebug() <<"tibiaActor _1";
        }

    m_objthreeDView->m_objThreeDRender->m_3DRenderer->ResetCamera();
    m_objthreeDView->m_objThreeDRender->m_3DRenderWindow->Render();

    m_objthreeDView->m_objThreeDRender->m_3DInteractor->Initialize();
}
