/*
    File Name       : classstl.h
    Project Name    : TestSQL
    Created         : 12-03-2024
    Description     : Header file containing implementation for
                      importing and exporting STL using vtk
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#ifndef CLASSSTL_H
#define CLASSSTL_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QDir>
#include <QString>
#include <QFileDialog>

//vtk headers
#include "appcommon/vtkincludes.h"
#include "vtkDICOMImageReader.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "QVTKOpenGLWidget.h"
#include "vtkSTLReader.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSTLWriter.h"
#include "vtkProperty.h"
#include "vtkSphereSource.h"
#include "vtkConeSource.h"

class ClassSTL : public QWidget
{
    Q_OBJECT
public:
    explicit ClassSTL(QWidget *parent = nullptr);

signals:
    void signalSTLFilePath(QString qstrSTLPath);
    void signalLoadStlStatus(bool status);

public slots:
    void GetSTLFilePath();
    void SetSTLFilePath(const QString& qstrSTLPath);
    void ImportSTL(/*QString qstrSTLInput*/);
    void ExportSTL();

private:
    QVTKOpenGLWidget *m_pvtkWidgetSTL;
    vtkNew <vtkGenericOpenGLRenderWindow> m_pvtkOpenGLRenWinSTL;
    vtkNew<vtkRenderer> m_pvtkRendererSTL;
    vtkNew <vtkSTLReader> m_pvtkSTLReader;
    vtkNew <vtkSTLWriter> m_pvtkSTLWriter;
    vtkNew <vtkPolyDataMapper> m_pvtkSTLMapper;
    vtkNew <vtkActor> m_pvtkSTLActor;

    QString m_qstrSTLFilePath;

    QString m_pqstrSTLInput;
    QString m_pqstrSTLOutput;
};

#endif // CLASSSTL_H
