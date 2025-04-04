#ifndef VIEWERPARENT_H
#define VIEWERPARENT_H

#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include <QStackedWidget>
#include "src/Plan/Viewer/mdiholdermpr.h"
#include "src/Plan/Viewer/Interactors/savelandmark.h"
#include "src/Plan/Viewer/Annotation/annotation.h"

class viewerParent : public QWidget
{
    Q_OBJECT
public:
    explicit viewerParent(QWidget *parent = nullptr);

    Annotation* m_objannotation; //annotation ui class
    mdiHolderMPR *m_objmdiHolderMPR;

    QStackedWidget *m_qswPlanUI;
    QWidget *dummyForDelet;

    void Initialize();
    bool blFirstTime = true;

signals:

public slots:
    void selectMPR();
    void newDataPath(QString path,QString fullpath, QString selKnee);
};

#endif // VIEWERPARENT_H
