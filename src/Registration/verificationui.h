#ifndef VERIFICATIONUI_H
#define VERIFICATIONUI_H

#include <QWidget>
#include <QDebug>
#include <QDir>
#include <QHBoxLayout>
#include <QMatrix4x4>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkPolyDataMapper.h>
#include <vtkStripper.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <QVTKOpenGLWidget.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkImageData.h>
#include <vtkImageReslice.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkCamera.h>
#include <Eigen/Dense>
#include "src/restAPIClient/restapicontroller.h"
#include <vtkSphereWidget.h>
#include <vtkSTLReader.h>
#include <vtkAxesActor.h>

#include <vtkImagePlaneWidget.h>
#include <vtkImageViewer2.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMatrix4x4.h>
#include <vtkExtractVOI.h>
#include <vtkPlaneSource.h>
#include <vtkTexture.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageProperty.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <QDir>
#include <QDomDocument>


struct PointDataVer {
    QString boneName;
    int anatomyID;
    QString anatomy;
    double x, y, z;
};

class verificationui : public QWidget
{
    Q_OBJECT
public:
    explicit verificationui(QWidget *parent = nullptr);

    vtkNew<vtkRenderer> m_verRenderer;
//    restAPIController *objrestAPIController;


    vtkNew<vtkRenderer> m_verRendererCrossSection;
    QVTKOpenGLWidget* m_pvtkWidgetVerif;
    QMatrix4x4 transformMatGlobal;
    bool firstTrack=true;
    vtkSmartPointer<vtkSTLReader> m_stlReaderTool;
    vtkSmartPointer<vtkPolyDataMapper> m_stlMappertool;
     vtkSmartPointer<vtkActor> m_stlActorTool;

signals:

public slots:
    void slotShowTransformedPoints(QString anatomy, int id, QString lndmarkname);

    void importstltool();

   void getLoadedDicomPathVer(const QString &qstrDcmFull, const QString &qstrDcmFemur, const QString qstrDcmTibia, const QString qstrselKnee);
   void slotToolOrientFemur(Eigen::Matrix4d m);
   void slotToolOrientTibia(Eigen::Matrix4d m);

private:
    vtkSmartPointer<vtkSphereSource> m_verSphereSource;
     vtkSmartPointer<vtkSphereSource> m_verSphereSourceTrack;
     vtkSmartPointer<vtkTransform> vtkTransformToolFemur = vtkSmartPointer<vtkTransform>::New();
     vtkSmartPointer<vtkTransform> vtkTransformToolTibia = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkPolyDataMapper> m_verSphereMapper;
    vtkSmartPointer<vtkActor> m_verSphereActor;

//    QVector<QVector3D> readCoordinatesFromFile(const QString& filePath);
//    QMatrix4x4 readTransMatFromFile(const QString& filePath);
//    QVector<QVector3D> transformCoordinates(const QVector<QVector3D>& patientCoords, const QMatrix4x4& transformMatrix);

//    vtkSmartPointer<vtkDICOMImageReader> m_verDcmReader;
    vtkSmartPointer<vtkDICOMImageReader> m_verDcmReader= vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkNew<vtkMarchingCubes> m_verSurface;
     vtkNew <vtkPolyDataMapper> m_verSurfaceMapper;

    vtkNew <vtkActor> m_verSurfaceActor;

    vtkNew<vtkPolyDataConnectivityFilter> connectivityFilter;
    vtkNew<vtkLookupTable> boneLut;
    vtkNew<vtkNamedColors> colors;

    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGlRenWinVerif = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    void showCrossSection(QVector3D coord);
    QMatrix4x4 transformMat;
    QVector4D transformedPoint;
    QString m_verstrDcmDir;
    vtkSmartPointer<vtkSphereWidget> sphereWidget;
    vtkSmartPointer<vtkAxesActor> stlToolAxes;
    vtkSmartPointer<vtkMatrix4x4> matrixtool;
    Eigen::Matrix4d stlEigenMatrixTool;
    Eigen::Matrix4d refSpaceTransformationMatrix;
    vtkSmartPointer<vtkTransform> transformMatstlinRef;
    Eigen::Matrix4d transformMatStlinRefEigen;
    vtkSmartPointer<vtkImagePlaneWidget> planeWidget = vtkSmartPointer<vtkImagePlaneWidget>::New();

    QString m_qstrVerFemur;
    QString m_qstrVerTibia;
    void landmarkCollection(QString m_regUiLandmarkName);
    std::vector<PointDataVer> annotationPointsVer ;
    vtkSmartPointer <vtkPolyDataMapper> m_VerLndSphMapper =  vtkSmartPointer <vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> m_verSphereActorSlice = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkImageActor> imgActorCross = vtkSmartPointer<vtkImageActor>::New();
    vtkSmartPointer<vtkImageReslice> planeWidgetReslice = vtkSmartPointer<vtkImageReslice>::New();
    vtkSmartPointer<vtkImageSliceMapper> planeWidgetResliceMapper = vtkSmartPointer<vtkImageSliceMapper>::New();
    vtkSmartPointer<vtkImageSlice> planeSlice2D = vtkSmartPointer<vtkImageSlice>::New();

    void calculateRMSE(double points[3], const QVector3D& referencePoint);
    vtkSmartPointer<vtkActor> m_verMinRMSESphereActor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkTextActor> rmseTextActor = vtkSmartPointer<vtkTextActor>::New();

    vtkSmartPointer <vtkSphereSource> m_VerLndSph =  vtkSmartPointer <vtkSphereSource>::New();
    vtkSmartPointer <vtkActor> m_VerLndSphActor =  vtkSmartPointer <vtkActor>::New();
    double m_verAnnotationPt[3];
    void loadDicomData(QString anatomy);
    double initialPosition[3];
    double initialFocalPoint[3];
    double initialViewUp[3];

QString textAct;

    std::vector<PointDataVer> parseXMLFile(const QString& filePath) {
        std::vector<PointDataVer> pointsList;
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Failed to open file";
            return pointsList;
        }

        QDomDocument doc;
        if (!doc.setContent(&file)) {
            qDebug() << "Failed to parse XML";
            file.close();
            return pointsList;
        }
        file.close();

        QDomElement root = doc.documentElement(); // <PickedPoints> element
        QDomNodeList pointNodes = root.childNodes(); // All child nodes (Point1, Point2, ...)

        // Iterate through each point node (Point1, Point2, ..., PointN)
        for (int i = 0; i < pointNodes.count(); ++i) {
            QDomElement pointElem = pointNodes.at(i).toElement();
            if (!pointElem.isNull()) {
                PointDataVer point;
                point.boneName = pointElem.attribute("bone_name");
                point.anatomyID = pointElem.attribute("anatomyid").toInt();
                point.anatomy = pointElem.attribute("anatomy");
                point.x = pointElem.attribute("x").toDouble();
                point.y = pointElem.attribute("y").toDouble();
                point.z = pointElem.attribute("z").toDouble();

                // Add point to the list
                pointsList.push_back(point);
            }
        }

        return pointsList;
    }


};

#endif // VERIFICATIONUI_H
