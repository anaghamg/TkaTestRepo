#ifndef REGINTERFACECLASS_H
#define REGINTERFACECLASS_H

#include <QWidget>
#include <QObject>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QStackedWidget>

#include "appcommon/spdlog/spdlog.h"
#include "src/Registration/registrationui.h"
#include "src/Registration/checkpoint.h"
#include "src/Registration/verificationui.h"
#include "src/Registration/regimplementation.h"
#include "src/Registration/fiducialswindow.h"

class RegInterfaceClass : public QWidget
{
    Q_OBJECT
public:
    explicit RegInterfaceClass(QWidget *parent = nullptr);

    //create class objects
    RegistrationUI* m_objRegUI; //ui layout class
    Checkpoint* m_objCheckpt;
    RegImplementation* m_objRegImplmt;
    verificationui* m_objVerificationUi;

    fiducialswindow* m_objfiducialsWindow;

signals:

public slots:
      void itemSelectedInTable(const QString &anatomy, int tableIndex);
      void regTabChanged(int index);
private:
      QStackedWidget* m_qswDisplay;


};

#endif // REGINTERFACECLASS_H
