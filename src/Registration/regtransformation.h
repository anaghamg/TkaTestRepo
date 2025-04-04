#ifndef REGTRANSFORMATION_H
#define REGTRANSFORMATION_H

#include <QObject>
#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <vtkCoordinate.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkOBJReader.h>
#include <vtkCellArray.h>
#include <vtkPolyLine.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkLandmarkTransform.h>
#include <vtkTransform.h>
#include <vtkBoxWidget.h>
class regTransformation : public QObject
{
    Q_OBJECT
public:
    explicit regTransformation(QObject *parent = nullptr);
    using Matrix4d = Eigen::Matrix4d;
    Matrix4d getTool1InTCS(const regTransformation::Matrix4d &tool1TCS);
    Matrix4d getMarkerInTCS(const regTransformation::Matrix4d &markerTCS);
    Matrix4d getMarkerToImageTransform();
    Matrix4d transformTool1ToMarkerCoordinate(const Matrix4d& tool1TCS, const Matrix4d& markerTCS);
    Matrix4d transformTool1ToImageSpace(const Matrix4d& tool1InMarker, const Matrix4d& icsMarker);
    Matrix4d getMarkerToImageTransform(const std::vector<Eigen::Vector3d>& markerPoints, const std::vector<Eigen::Vector3d>& imagePoints);
    Eigen::Matrix4d createTransformationMatrix(double x, double y, double z, double qx, double qy, double qz, double qw);
    Eigen::Matrix4d invertTransformationMatrix(const Eigen::Matrix4d &transformation_matrix);
    Eigen::Matrix4d composeTransformationMatrix(const Eigen::Matrix3d &rotation_matrix, const Eigen::Vector3d &translation_vector) ;
    Eigen::Matrix3d quaternionToRotationMatrix(const Eigen::Quaterniond &ref_quat);
void saveVtkTransformToFile(vtkTransform* transform, const QString& filename);
QString m_qstrAnatomy;

Eigen::Vector4d applyTransformation(const Eigen::Matrix4d &transformation_matrix, const Eigen::Vector3d &point_cam_space);

    void rigiTransform();
    void SaveTransformationMatrix();
    Eigen::Matrix4d getCameraToReferenceTransform(Eigen::Matrix3d &ref_quat, const Eigen::Vector3d &translation);
    Eigen::Vector3d getImageSpaceCoord(double x_patient, double y_patient, double z_patient);
    Eigen::Matrix4d readMatrixFromFile();
    int pickedPointsV1 =0;
        int pickedPointsV2 =0;
        vtkNew<vtkLandmarkTransform> landmarkTransform;
        vtkNew<vtkPoints> sourcePoints; //vol 1
        vtkNew<vtkPoints> targetPoints; //vol 2
        vtkNew <vtkTransform> newTransform;

        vtkSmartPointer<vtkMatrix4x4> M;
        QString getQstrAnatomy() const;
        void setQstrAnatomy(const QString &qstrAnatomy);


signals:

};

#endif // REGTRANSFORMATION_H
