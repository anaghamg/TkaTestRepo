#ifndef CORONALVIEW_H
#define CORONALVIEW_H

#include <QObject>
#include <QWidget>
#include <QMenuBar>
#include <QToolButton>
#include <QSize>
#include <QDir>
#include <QVBoxLayout>
#include "src/Plan/Viewer/MPR/classcoronalview.h"
#include "src/Viewer/viewerreslice.h"
#include "src/Viewer/widget.h"
class CoronalView : public QWidget
{
    Q_OBJECT
public:
    explicit CoronalView(QWidget *parent = nullptr);

    QAction *m_qacHideCoronal;
    QAction *m_qacMaximCoronal;
    QMenuBar* m_qmenubarCoronal;
    ClassCoronalView *m_objClassCoronalView;
//    viewerReslice *m_objClassCoronalView;
    void Initialize();
Widget *m_objWidget;
    static CoronalView* objCoronalViewInstance;
    bool boolMaxStatus=false;
signals:
    void hideCoronal();
    void maxCoronal();

public slots:
 void hideThisCoronal();
 void maxThisCoronal();

 void maxFromBut();

public:

// deleting copy constructor
CoronalView(const CoronalView& obj)
= delete;


static CoronalView* getInstance()
{

  if (objCoronalViewInstance == NULL)
  {

    objCoronalViewInstance = new CoronalView();



    return objCoronalViewInstance;
  }
  else
  {
    return objCoronalViewInstance;
  }
}


};

#endif // CORONALVIEW_H
