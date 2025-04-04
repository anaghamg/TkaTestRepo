#ifndef THREEDVIEW_H
#define THREEDVIEW_H

#include <QObject>
#include <QWidget>
#include <QMenuBar>
#include <QToolButton>
#include <QSize>
#include <QDir>
#include <QVBoxLayout>
#include "src/Plan/Viewer/MPR/threedrender.h"

class threeDView : public QWidget
{
    Q_OBJECT
public:
    explicit threeDView(QWidget *parent = nullptr);

    QAction *m_qacHideTDV;
    QAction *m_qacMaximTDV;
    QMenuBar* m_qmenubarTDV;
    ThreeDRender *m_objThreeDRender;
    //      static threeDView* objthreeDViewInstance;
    //       static threeDView &getInstance();
    void Initialize();
    bool boolMaxStatus=false;

signals:
    void hideTDV();
    void maxTDV();

public slots:
    void hideThisTDV();
    void maxThisTDV();
    void maxFromBut();

public:

    // // deleting copy constructor
    // threeDView(const threeDView& obj)
    //   = delete;


    // static threeDView* getInstance()
    //   {

    //     if (objthreeDViewInstance == NULL)



    //     {

    //       objthreeDViewInstance = new threeDView();



    //       return objthreeDViewInstance;
    //     }
    //     else
    //     {
    //       return objthreeDViewInstance;
    //     }
    //   }
};



#endif // THREEDVIEW_H
