#ifndef SAGITALVIEW_H
#define SAGITALVIEW_H

#include <QObject>
#include <QWidget>
#include <QMenuBar>
#include <QToolButton>
#include <QSize>
#include <QDir>
#include <QVBoxLayout>
#include "src/Plan/Viewer/MPR/classsagittalview.h"
#include "src/Viewer/viewerreslice.h"
#include "src/Viewer/widget.h"
class sagitalView : public QWidget
{
    Q_OBJECT
public:
    explicit sagitalView(QWidget *parent = nullptr);
    
    QAction *m_qacHideSagital;
    QAction *m_qacMaximSagital;
    QMenuBar* m_qmenubarSagital;
    ClassSagittalView *m_objClassSagittalView;
//    viewerReslice *m_objClassSagittalView;
    void Initialize();
    Widget *m_objWidget;
//     static sagitalView* objsagitalViewInstance;
    bool boolMaxStatus=false;
signals:
    void hideSagital();
    void maxSagital();

public slots:
    void hideThisSagital();
    void maxThisSagital();
    void maxFromBut();



   public:

   // deleting copy constructor
   sagitalView(const sagitalView& obj)
   = delete;


//   static sagitalView* getInstance()
//   {

//     if (objsagitalViewInstance == NULL)
//     {

//       objsagitalViewInstance = new sagitalView();



//       return objsagitalViewInstance;
//     }
//     else
//     {
//       return objsagitalViewInstance;
//     }
//   }
    
};

#endif // SAGITALVIEW_H
