#ifndef AXIALVIEW_H
#define AXIALVIEW_H

#include <QObject>
#include <QWidget>
#include <QMenuBar>
#include <QToolButton>
#include <QSize>
#include <QDir>
#include <QVBoxLayout>
#include <QDebug>
#include "src/Viewer/viewerreslice.h"
#include "src/Viewer/widget.h"
#include "src/Plan/Viewer/MPR/classaxialview.h"



class axialView : public QWidget
{
    Q_OBJECT
public:
    explicit axialView(QWidget *parent = nullptr);
    QAction *m_qacHide;
    QAction *m_qacMaxim;
    QMenuBar* m_qmenubarAxial;
    //    viewerReslice *m_objClassAxialView;
    ClassAxialView *m_objClassAxialView;
    void Initialize();
    static axialView* objaxialViewInstance;
    Widget *m_objWidget;
    bool boolMaxStatus=false;

signals:
    void hideAxial();
    void maxAxial();

public slots:
    void hideThis();
    void maxThis();
    void maxFromBut();

public:

    // deleting copy constructor
    axialView(const axialView& obj)
    = delete;

    static axialView* getInstance()
    {
        if (objaxialViewInstance == NULL)
        {
            objaxialViewInstance = new axialView();
            return objaxialViewInstance;
        }
        else
        {
            return objaxialViewInstance;
        }
    }

};

#endif // AXIALVIEW_H
