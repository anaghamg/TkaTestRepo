#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "src/Viewer/controlbutton.h"
#include "appcommon/vtkincludes.h"
#include <QDir>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();




    ControlButton *m_pqbResetWindow;
    ControlButton *m_pqbSinPaneViewer;
    ControlButton *m_pqbTwoSquarePaneViewer;
    ControlButton *m_pqbEnableAntns;

    ControlButton *m_pqbShowHideScanDetails;
    ControlButton *m_pqbImgFolderLoc;
    ControlButton *m_pqbRotateLeft;
    ControlButton *m_pqbRotateRight;
    ControlButton *m_pqbSendToPACS;
    ControlButton *m_pqbLine;
    ControlButton *m_pqbAngle;
    ControlButton *m_pqbDistance;
    ControlButton *m_pqbClear;
};
#endif // WIDGET_H
