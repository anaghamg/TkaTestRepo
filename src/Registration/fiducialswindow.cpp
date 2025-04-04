#include "fiducialswindow.h"



fiducialswindow::fiducialswindow(QWidget *parent) : QWidget(parent)
{
    qDebug()<<" fiducial markers windpw ";
    m_qvtkToolwin = new QVTKOpenGLWidget;
    m_openGLToolWin = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    m_qvtkToolwinRenderer = vtkSmartPointer<vtkRenderer>::New();

    m_qvtkToolwin->SetRenderWindow(m_openGLToolWin);
    m_openGLToolWin->AddRenderer(m_qvtkToolwinRenderer);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(m_qvtkToolwin);
    this->setLayout(mainLayout);

    drawQuadrantGraph();

}

void fiducialswindow::slotFiducialsFemurRef(const QList<QVariantMap>& fiducialsData)
{
    while (sphereActorsF.size() < fiducialsData.size()) {
        qDebug()<<" creating actors ";
        auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();

        auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(sphereSource->GetOutputPort());

        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        m_qvtkToolwinRenderer->AddActor(actor);
        sphereActorsF.append(actor);
    }

    while (sphereActorsF.size() > fiducialsData.size()) {
        auto actor = sphereActorsF.takeLast();
        m_qvtkToolwinRenderer->RemoveActor(actor);
    }

    // Update positions and radii
    for (int i = 0; i < fiducialsData.size(); ++i) {
//        qDebug()<<" setting position ";

        const QVariantMap& fiducial = fiducialsData[i];
        double x = fiducial["x"].toDouble();
        double y = fiducial["y"].toDouble();
        double z = fiducial["z"].toDouble();
        double radius = fiducial["radius"].toDouble();
        bool status = fiducial["status"].toBool();

        auto sphereSource = vtkSphereSource::SafeDownCast(sphereActorsF[i]->GetMapper()->GetInputAlgorithm());
        if (sphereSource) {
            sphereSource->SetRadius(radius);
            sphereSource->Update();
        }
        sphereActorsF[i]->SetPosition(x, y, z);
        if (status){
            sphereActorsF[i]->GetProperty()->SetColor(0.0, 1.0, 0.0); // true = yellow
        }
        else if (!status){
            sphereActorsF[i]->GetProperty()->SetColor(1.0, 0.0, 0.0); // false = red
        }
    }

    m_qvtkToolwinRenderer->GetRenderWindow()->Render();
}

void fiducialswindow::slotFiducialsTibiaRef(const QList<QVariantMap>& fiducialsData)
{
    while (sphereActorsTib.size() < fiducialsData.size()) {
        auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();

        auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(sphereSource->GetOutputPort());

        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        m_qvtkToolwinRenderer->AddActor(actor);
        sphereActorsTib.append(actor);
    }

    while (sphereActorsTib.size() > fiducialsData.size()) {
        auto actor = sphereActorsTib.takeLast();
        m_qvtkToolwinRenderer->RemoveActor(actor);
    }

    // Update positions and radii
    for (int i = 0; i < fiducialsData.size(); ++i) {
        const QVariantMap& fiducial = fiducialsData[i];
        double x = fiducial["x"].toDouble();
        double y = fiducial["y"].toDouble();
        double z = fiducial["z"].toDouble();
        double radius = fiducial["radius"].toDouble();
        bool status = fiducial["status"].toBool();

        auto sphereSource = vtkSphereSource::SafeDownCast(sphereActorsTib[i]->GetMapper()->GetInputAlgorithm());
        if (sphereSource) {
            sphereSource->SetRadius(radius);
            sphereSource->Update();
        }

        sphereActorsTib[i]->SetPosition(x, y, z);
        if (status){
            sphereActorsTib[i]->GetProperty()->SetColor(1.0, 1.0, 0.0); // true = yellow
        }
        else if (!status){
            sphereActorsTib[i]->GetProperty()->SetColor(1.0, 0.0, 0.0); // false = red
        }
    }
    m_qvtkToolwinRenderer->GetRenderWindow()->Render();

}

void fiducialswindow::slotFiducialsTool(const QList<QVariantMap>& fiducialsData)
{
    while (sphereActorsT.size() < fiducialsData.size()) {
        auto sphereSource = vtkSmartPointer<vtkSphereSource>::New();

        auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(sphereSource->GetOutputPort());

        auto actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);

        m_qvtkToolwinRenderer->AddActor(actor);
        sphereActorsT.append(actor);
    }

    while (sphereActorsT.size() > fiducialsData.size()) {
        auto actor = sphereActorsT.takeLast();
        m_qvtkToolwinRenderer->RemoveActor(actor);
    }

    // Update positions and radii
    for (int i = 0; i < fiducialsData.size(); ++i) {
        const QVariantMap& fiducial = fiducialsData[i];
        double x = fiducial["x"].toDouble();
        double y = fiducial["y"].toDouble();
        double z = fiducial["z"].toDouble();
        double radius = fiducial["radius"].toDouble();
        bool status = fiducial["status"].toBool();

        auto sphereSource = vtkSphereSource::SafeDownCast(sphereActorsT[i]->GetMapper()->GetInputAlgorithm());
        if (sphereSource) {
            sphereSource->SetRadius(radius);
            sphereSource->Update();
        }

        sphereActorsT[i]->SetPosition(x, y, z);  // Remove duplicate SetPosition
        if (status) {
            sphereActorsT[i]->GetProperty()->SetColor(1.0, 1.0, 0.0); // Yellow (R=1, G=1, B=0)
        } else {
            sphereActorsT[i]->GetProperty()->SetColor(1.0, 0.0, 0.0); // Red
        }
    }

    // Add this line to force a render update
    m_qvtkToolwinRenderer->GetRenderWindow()->Render();

}



void fiducialswindow::drawQuadrantGraph()
{
    vtkSmartPointer<vtkNamedColors> colors = vtkSmartPointer<vtkNamedColors>::New();

    vtkSmartPointer<vtkLineSource> xAxis = vtkSmartPointer<vtkLineSource>::New();
    xAxis->SetPoint1(-1000.0, 0.0, 0.0);
    xAxis->SetPoint2(1000.0, 0.0, 0.0);

    vtkSmartPointer<vtkPolyDataMapper> xAxisMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    xAxisMapper->SetInputConnection(xAxis->GetOutputPort());

    vtkSmartPointer<vtkActor> xAxisActor = vtkSmartPointer<vtkActor>::New();
    xAxisActor->SetMapper(xAxisMapper);
    xAxisActor->GetProperty()->SetColor(0.2, 0.2, 0.2);
    xAxisActor->GetProperty()->SetLineWidth(2);

    vtkSmartPointer<vtkLineSource> yAxis = vtkSmartPointer<vtkLineSource>::New();
    yAxis->SetPoint1(0.0, -1000.0, 0.0);
    yAxis->SetPoint2(0.0, 1000.0, 0.0);

    vtkSmartPointer<vtkPolyDataMapper> yAxisMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    yAxisMapper->SetInputConnection(yAxis->GetOutputPort());

    vtkSmartPointer<vtkActor> yAxisActor = vtkSmartPointer<vtkActor>::New();
    yAxisActor->SetMapper(yAxisMapper);
    yAxisActor->GetProperty()->SetColor(0.2, 0.2, 0.2);
    yAxisActor->GetProperty()->SetLineWidth(2);

    //    m_qvtkToolwinRenderer->AddActor(xAxisActor);
    //    m_qvtkToolwinRenderer->AddActor(yAxisActor);

    m_qvtkToolwinRenderer->SetBackground(colors->GetColor3d("Black").GetData());

}
