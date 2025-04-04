#ifndef REGIMPLEMENTATION_H
#define REGIMPLEMENTATION_H

#include <QObject>
#include <QWidget>
#include <QVTKOpenGLWidget.h>
#include <QVTKOpenGLNativeWidget.h>
#include <QVector3D>
#include <QMatrix4x4>
#include <QHBoxLayout>
#include <QFile>
#include <QDebug>
#include <QDomDocument>
#include <iostream>
#include <vector>

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkProperty.h>
#include <vtkStripper.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkLookupTable.h>
#include <vtkNamedColors.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>
#include <vtkSphereSource.h>
#include <vtkLandmarkTransform.h>

#include <vtkCoordinate.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkOBJReader.h>
#include <vtkCellArray.h>
#include <vtkPolyLine.h>
#include <vtkPolyDataMapper2D.h>

#include <vtkCommand.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAssembly.h>
#include <vtkPropPicker.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSTLReader.h>
#include <vtkXMLDataElement.h>
#include <vtkXMLUtilities.h>

#include <vtkTriangleFilter.h>
#include <vtkCleanPolyData.h>
#include <vtkFillHolesFilter.h>
#include <vtkAssembly.h>
#include <vtkTransformPolyDataFilter.h>

#include <vtkStructuredGridGeometryFilter.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkLine.h>
#include <vtkStructuredGrid.h>

#include <vtkGlyph3D.h>
#include <vtkSphereSource.h>

#include <vtkRegularPolygonSource.h>
#include <vtkLineSource.h>
#include <vtkIterativeClosestPointTransform.h>

//deepak
#include <vtkBoundingBox.h>
#include <vtkCubeSource.h>
#include <vtkBoxWidget2.h>
#include <vtkBoxRepresentation.h>

#include <vtkExtractGeometry.h>
#include <vtkBox.h>
#include <vtkGeometryFilter.h>
#include <vtkClipPolyData.h>
#include <vtkVertexGlyphFilter.h>
#include <vtkAppendPolyData.h>
#include <vtkPointLocator.h>
#include <vtkCleanPolyData.h>
#include <vtkImplicitBoolean.h>
#include <vtkCamera.h>

#include <vtkDoubleArray.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkCellLocator.h>

#include <Eigen/Dense>

#include "src/restAPIClient/jsondatafetchotherdetails.h"
#include "appcommon/spdlog/spdlog.h"
#include "src/restAPIClient/restapicontroller.h"
#include "src/Registration/regtransformation.h"
//#include "src/restAPIClient/jsondatacameraforsurface.h"
//#include <src/Plan/Viewer/Interactors/savelandmark.h>
#include <src/restAPIClient/camipconfig.h>
#include "src/Registration/hipcenterapi.h"
#include <src/restAPIClient/camipconfig.h>

struct PointData {
    QString boneName;
    int anatomyID;
    QString anatomy;
    double x, y, z;
};

class RegImplementation : public QWidget
{
    Q_OBJECT
public:
    explicit RegImplementation(QWidget *parent = nullptr);

    hipcenterapi* m_objHipCenterApi;
    restAPIController *objrestAPIController;

    //added 22-10-2024
    QString m_qstrLoadedDcm;     //dicom path
    QString m_qstrLoadedStl;      //sel path

    QString m_qstrFemurDcm;
    QString m_qstrTibiaDcm;

    QString m_qstrFemurStl;
    QString m_qstrTibiaStl;


    void switchData();
    void switchData_f();


    //rupika
    int m_landmarkIndex = 1;
    QString m_anatomy = "Femur";
    int m_windowID = 0;
    QString m_regUiLandmarkName = "Checkpoint";
    void savePatientLandmarksToXML();
    void onRegistrationClicked();
    QStringList LandmarkNames;
    QString femurLandmarklist = QDir::currentPath() + "/RegistrationLandmarks_Femur.txt";
    QString TibiaLandmarklist = QDir::currentPath() + "/RegistrationLandmarks_Tibia.txt";

    QStringList readLandmarkNamesFromFile(const QString &filePath);



private:





signals:
        void signalChkPtWindow(QString anatomy, int windowID, int m_landmarkIndex);//rupika
        void signalVerificationUi(QString anatomy, int id);
        void signalDrawBoundingBox(std::vector<int> m_landmarkindexVec, std::vector<std::array<double, 3>> m_annotPtsSelected);
        void signalToolLocation(double pt[3]);

public slots:
        void thumbnailSelected(QString from,QString item, int landmarkIndex);

        void onCaptureClicked();
        void onCapturePressed();
        void onCaptureReleased();

        void drawBB(std::vector<int> m_landmarkindexVec, std::vector<std::array<double, 3>> m_annotPtsSelected);
        void slotToolLocation(double pt[3]);

        void getLoadedDicomPath(const QString& qstrDcmFull, const QString& qstrDcmFemur, const QString qstrDcmTibia, const QString qsselKnee);
        void getLoadedStlPath(/*const QString& qstrStlFull,*/ const QString& qstrStlFemur, const QString qstrStlTibia);

        void onCheckpointClicked();

        void SaveTransformationMatrix();
        void startSurfaceDataCollection();
        void endSurfaceDataCollection();

        /// for hip center url
        void slotErrorHip(double error);
        void slotMarkerPositionHip(const QList<double> &markerPosition);
        void slotHipCenterDone(const QList<double> &hipcenter);
        //    void setNewCoordFromRefSpace(Eigen::Vector4d coord);

        void slotRefSpaceCoords_Femur(Eigen::Vector4d pt);
        void slotRefSpaceCoords_Tibia(Eigen::Vector4d pt);

    //    void slotToolOrientFemur(Eigen::Matrix4d cam2ref_tf_femur);
        void slotToolOrientFemur(vtkSmartPointer<vtkTransform> t,Eigen::Matrix4d m);
        void slotToolOrientTibia(Eigen::Matrix4d cam2ref_tf_tibia);





private:

        //declare variables here



        //declare vtk objects here



        //declare functions here




        vtkSmartPointer<vtkBoxWidget2> boxWidget = vtkSmartPointer<vtkBoxWidget2>::New();
        int pickedPointsV1 =0;
        int pickedPointsV2 =0;
        vtkNew<vtkLandmarkTransform> landmarkTransform;
        vtkNew<vtkPoints> sourcePoints; //vol 1
        vtkNew<vtkPoints> targetPoints; //vol 2
        vtkNew <vtkTransform> newTransform;
        vtkSmartPointer<vtkMatrix4x4> M;
        jsondatafetchOtherDetails objjsonOtherData;
        //    jsondatacameraforsurface objjsondatacameraforsurface;
        regTransformation objregTransformation ;
        vtkSmartPointer<vtkPoints> m_filteredPointsimagespace = vtkSmartPointer<vtkPoints>::New();
        void landmarkCollection(QString landmarkname);
        double m_regAnnotationPt[3];

        vtkNew <vtkActor> m_pvtkSurfaceActor;
        vtkSmartPointer<vtkDICOMImageReader> m_REGDcmReader= vtkSmartPointer<vtkDICOMImageReader>::New();

        bool boolnotdoneOne=true;
        bool boolnotdoneTwo=true;
        bool boolnotdoneThree=true;
        bool boolnotdoneFour=true;
        bool boolnotdoneFive=true;
        bool boolnotdoneSix=true;
        bool boolnotdoneSeven=true;
        bool boolnotdoneEight=true;
        bool boolnotdoneNine=true;
        bool boolnotdoneTen=true;

        bool boolT1=true;
        bool boolT2=true;
        bool boolT3=true;
        bool boolT4=true;
        bool boolT5=true;
        bool boolT6=true;






    void colorHipCenterpoint(double x, double y, double z);
    vtkSmartPointer<vtkActor> greenCircle = vtkSmartPointer<vtkActor>::New();
    Eigen::Matrix4d transform_otp;

    /// marker window
    QVTKOpenGLWidget* m_qvtkToolwin;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGLToolWin = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkNew<vtkRenderer> m_qvtkToolwinRen;
    void showMarkers();

    vtkSmartPointer<vtkTransform> vtkTransformToolFemur = vtkSmartPointer<vtkTransform>::New();
    vtkSmartPointer<vtkMatrix4x4> newVtkMatrixF = vtkSmartPointer<vtkMatrix4x4>::New();


    vtkSmartPointer<vtkSphereSource> ts = vtkSmartPointer<vtkSphereSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> tsm = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer <vtkActor> tsa =  vtkSmartPointer <vtkActor>::New();

    QVTKOpenGLWidget *m_pvtkWidget;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_openGlRenWin = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    vtkSmartPointer<vtkRenderWindowInteractor> m_pvtkInteractorReg = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_istyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    vtkSmartPointer<vtkDICOMImageReader> m_pvtkDcmReader;
    vtkNew<vtkMarchingCubes> m_pvtkSurface;
    vtkNew <vtkPolyDataMapper> m_pvtkSurfaceMapper;
    vtkNew<vtkRenderer> m_pvtkRenderer;
    vtkNew<vtkRenderer> m_pvtkRendererCrossSection;
    vtkSmartPointer<vtkTextActor> actorL = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> actorM = vtkSmartPointer<vtkTextActor>::New();

    vtkNew<vtkPolyDataConnectivityFilter> connectivityFilter;
    vtkNew<vtkLookupTable> boneLut;
    vtkNew<vtkNamedColors> colors;

    vtkSmartPointer<vtkSphereSource> m_pvtkSphereSource;
    vtkSmartPointer<vtkActor> m_pvtkSphereActor;
    vtkSmartPointer<vtkPolyDataMapper> m_pvtkSphereMapper;

    vtkNew<vtkAssembly> m_pvtkAssembly1;

    vtkNew<vtkDoubleArray> cellValues;
    vtkSmartPointer<vtkCellLocator> cellLocator = vtkSmartPointer<vtkCellLocator>::New();
    vtkNew<vtkLookupTable> lut;


    //rupika
    QVector<QVector3D> readCoordinatesFromFile(const QString &filePath);



    vtkSmartPointer<vtkXMLDataElement> root;
    vtkSmartPointer<vtkXMLUtilities> xmlUtilities = vtkSmartPointer<vtkXMLUtilities>::New();
    QVector3D landmarkPoint;
    const std::string& filename = "PatientLandmarks.xml";
    //    vtkSmartPointer<vtkActor> boneStlActor = vtkSmartPointer<vtkActor>::New();

    QString stlFilePath;

    vtkSmartPointer<vtkDICOMImageReader> m_chkDcmReader= vtkSmartPointer<vtkDICOMImageReader>::New();
    vtkNew<vtkMarchingCubes> m_chkSurface;
    vtkNew <vtkPolyDataMapper> m_chkSurfaceMapper;
    vtkNew <vtkActor> m_chkSurfaceActor;

    vtkNew<vtkActor> floorActor;
    vtkSmartPointer<vtkActor> fillActor = vtkSmartPointer<vtkActor>::New();


    vtkNew<vtkMarchingCubes> m_REGSurface;
    vtkNew <vtkPolyDataMapper> m_REGSurfaceMapper;
    vtkNew <vtkActor> m_REGSurfaceActor;
    std::vector<PointData> annotationPoints ;
    vtkSmartPointer <vtkPolyDataMapper> lndmrk_sphereMapper =  vtkSmartPointer <vtkPolyDataMapper>::New();
    vtkSmartPointer <vtkSphereSource> lndmrk_sphere =  vtkSmartPointer <vtkSphereSource>::New();
    vtkSmartPointer <vtkActor> lndmrk_sphereActor =  vtkSmartPointer <vtkActor>::New();

    double initialPosition[3];
    double initialFocalPoint[3];
    double initialViewUp[3];
    QString kinematicsPath;
    vtkSmartPointer<vtkActor> boneStlActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> boneStlActorTibia = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkActor> boneStlActorFemur = vtkSmartPointer<vtkActor>::New();


    double m_hipError; // hip center error value
    double m_hipMarkerPos[3]; // hip center marker position;
    QTimer* timerHip;
    void executeHipCollection();
    bool m_isFirstValueReceived = false;
    QList<double> m_firstPositionHip;  // To store the first received position
    void drawHipCenterUI();
    vtkSmartPointer<vtkAssembly> hipCenterGridassembly = vtkSmartPointer<vtkAssembly>::New();
    vtkSmartPointer<vtkTextActor> textActor = vtkSmartPointer<vtkTextActor>::New();
    vtkSmartPointer<vtkTextActor> textActorhip = vtkSmartPointer<vtkTextActor>::New();
    bool CheckPointsInGridRegion(const std::vector<vtkSmartPointer<vtkPoints>>& points, double gridRadiusStart, double gridRadiusEnd, double angleStart, double angleEnd);
    void AddYellowBackground(vtkSmartPointer<vtkAssembly> gridAssembly, double gridRadiusStart, double gridRadiusEnd, double angleStart, double angleEnd);
    std::vector<vtkSmartPointer<vtkPoints>> markerPtsFromHipApi;
    std::vector<vtkSmartPointer<vtkActor>> circleActors;



    std::vector<PointData> parseXMLFile(const QString& filePath) {
        std::vector<PointData> pointsList;
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
                PointData point;
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


    /// deepak chettans part
    void writeCoordinatesToFile( double m_regAnnotationPt[3]);

    /// surface rupika
    void loadStlTool();
    vtkSmartPointer<vtkSTLReader> m_stlReaderTool;
    vtkSmartPointer<vtkPolyDataMapper> m_stlMappertool;
    vtkSmartPointer<vtkActor> m_stlActorTool;
    void readPointBasedTransformationMatrixFemur();
    void readPointBasedTransformationMatrixTibia();

    Eigen::Matrix4d trasnformationmatrix_point_femur=  Eigen::Matrix4d::Identity();
    Eigen::Matrix4d trasnformationmatrix_point_tibia=  Eigen::Matrix4d::Identity();

    vtkSmartPointer<vtkTransform> transformMatinImgSpace;


    QTimer* timerSurface;
    void executeSurfaceCollection();
    double m_toolLocation[3];
    std::vector<std::array<double, 3>> m_ptStorage; // Vector to store the points
    bool m_isCapturing = false; // Flag to indicate capture state
    void pointCloudTransformation();
    vtkSmartPointer<vtkMatrix4x4> icpMatrix;
    bool icpComputed = false; // Flag to check if ICP is done
    void calculateRMSE(double testPoint[3], double toolLoc[3]);
    QString textAct;
    vtkSmartPointer<vtkTextActor> rmseTextActor = vtkSmartPointer<vtkTextActor>::New();

    std::vector<vtkSmartPointer<vtkPolyData>> m_imgPolydataList;
    vtkSmartPointer<vtkActor> bbActor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkMatrix4x4> matrixICP = vtkSmartPointer<vtkMatrix4x4>::New();
    double resultH[4] = {0.0, 0.0, 0.0, 0.0};

    void noiseFiltering(std::vector<std::array<double, 3>> m_ptStorage);
    std::vector<std::array<double, 3>> filtered_ptStorage;

    //vtkSmartPointer<vtkCubeSource> cubeSource = vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapperbb = vtkSmartPointer<vtkPolyDataMapper>::New();
    //vtkSmartPointer<vtkBox> clipBox = vtkSmartPointer<vtkBox>::New();
    //vtkSmartPointer<vtkClipPolyData> clipper = vtkSmartPointer<vtkClipPolyData>::New();
    vtkSmartPointer<vtkPolyDataMapper> clippedMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> clippedActor = vtkSmartPointer<vtkActor>::New();

    vtkSmartPointer<vtkPolyData> m_imgPolydataAll = vtkSmartPointer<vtkPolyData>::New();
    vtkSmartPointer<vtkAppendPolyData> appendPolydata = vtkSmartPointer<vtkAppendPolyData>::New();
    std::vector<std::array<double, 3>> accumulatedPointsVec;

    std::vector<int> m_landmarkindexVec;
    std::vector<std::array<double, 3>> m_annotPtsSelected;

};

#endif // REGIMPLEMENTATION_H
