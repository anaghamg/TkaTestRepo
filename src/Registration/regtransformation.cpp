#include "regtransformation.h"
//#include <QDebug>


regTransformation::regTransformation(QObject *parent) : QObject(parent)
{
    qDebug()<<" initialise regTranformation ";
    //    rigiTransform();
}

regTransformation::Matrix4d regTransformation::getTool1InTCS(const regTransformation::Matrix4d &tool1TCS)
{
    //     Matrix4d tool1TCS;

    return tool1TCS;
}

regTransformation::Matrix4d regTransformation::getMarkerInTCS(const regTransformation::Matrix4d &markerTCS)
{
    //    Matrix4d markerTCS;
    return markerTCS;
}

regTransformation::Matrix4d regTransformation::getMarkerToImageTransform()
{
    Matrix4d icsMarker;
    return icsMarker;

}

regTransformation::Matrix4d regTransformation::transformTool1ToMarkerCoordinate(const regTransformation::Matrix4d &tool1TCS, const regTransformation::Matrix4d &markerTCS)
{
    // Compute the inverse of the marker's transformation matrix in TCS
    Matrix4d markerTCSInverse = markerTCS.inverse();

    // Transform Tool1 coordinates to the Marker coordinate system
    Matrix4d tool1InMarker = markerTCSInverse * tool1TCS;

    return tool1InMarker;
}

regTransformation::Matrix4d regTransformation::transformTool1ToImageSpace(const regTransformation::Matrix4d &tool1InMarker, const regTransformation::Matrix4d &icsMarker)
{
    // Transform Tool1 coordinates to the Image Coordinate System (ICS)
    Matrix4d tool1InICS = icsMarker * tool1InMarker;

    return tool1InICS;
}

// Create the transformation matrix from translation and quaternion
Eigen::Matrix4d regTransformation::createTransformationMatrix(double x, double y, double z, double qx, double qy, double qz, double qw)
{
    Eigen::Matrix4d transformationMatrix = Eigen::Matrix4d::Identity();
    Eigen::Quaterniond quaternion(qw, qx, qy, qz);
    Eigen::Matrix3d rotationMatrix = quaternion.toRotationMatrix();
    transformationMatrix.block<3, 3>(0, 0) = rotationMatrix;
    transformationMatrix(0, 3) = x;
    transformationMatrix(1, 3) = y;
    transformationMatrix(2, 3) = z;

    return transformationMatrix;
}

regTransformation::Matrix4d regTransformation::getMarkerToImageTransform(const std::vector<Eigen::Vector3d> &markerPoints, const std::vector<Eigen::Vector3d> &imagePoints)
{
    if (markerPoints.size() != imagePoints.size() || markerPoints.size() < 3) {
        throw std::runtime_error("Number of points in Marker and Image spaces must be the same and at least 3.");
    }

    // Step 1: Compute the centroids of both point sets
    Eigen::Vector3d centroidMarker = Eigen::Vector3d::Zero();
    Eigen::Vector3d centroidImage = Eigen::Vector3d::Zero();

    for (size_t i = 0; i < markerPoints.size(); ++i) {
        centroidMarker += markerPoints[i];
        centroidImage += imagePoints[i];
    }
    centroidMarker /= markerPoints.size();
    centroidImage /= imagePoints.size();

    // Step 2: Subtract the centroids from the points
    std::vector<Eigen::Vector3d> centeredMarkerPoints;
    std::vector<Eigen::Vector3d> centeredImagePoints;

    for (size_t i = 0; i < markerPoints.size(); ++i) {
        centeredMarkerPoints.push_back(markerPoints[i] - centroidMarker);
        centeredImagePoints.push_back(imagePoints[i] - centroidImage);
    }

    // Step 3: Compute the covariance matrix
    Eigen::Matrix3d covarianceMatrix = Eigen::Matrix3d::Zero();
    for (size_t i = 0; i < centeredMarkerPoints.size(); ++i) {
        covarianceMatrix += centeredMarkerPoints[i] * centeredImagePoints[i].transpose();
    }

    // Step 4: Compute the Singular Value Decomposition (SVD)
    Eigen::JacobiSVD<Eigen::Matrix3d> svd(covarianceMatrix, Eigen::ComputeFullU | Eigen::ComputeFullV);
    Eigen::Matrix3d rotation = svd.matrixV() * svd.matrixU().transpose();

    // Handle the reflection case
    if (rotation.determinant() < 0) {
        Eigen::Matrix3d V = svd.matrixV();
        V.col(2) *= -1;
        rotation = V * svd.matrixU().transpose();
    }

    // Step 5: Compute the translation vector
    Eigen::Vector3d translation = centroidImage - rotation * centroidMarker;

    // Step 6: Build the final 4x4 transformation matrix
    Matrix4d transform = Matrix4d::Identity();
    transform.block<3, 3>(0, 0) = rotation;
    transform.block<3, 1>(0, 3) = translation;

    return transform;
}

void regTransformation::rigiTransform()
{
//    m_qstrAnatomy = "FEMUR";
    qDebug()<<"rigiTransform";

    QString source;
    if(m_qstrAnatomy=="Femur")
        source = QDir::currentPath() + "/RegistrationFiles/" + "transformed_point_femur.txt";
    else if(m_qstrAnatomy=="Tibia")
        source = QDir::currentPath() + "/RegistrationFiles/" + "transformed_point_tibia.txt";
    else {

    }
    QString target;
    if(m_qstrAnatomy=="Femur")
        target = QDir::currentPath() + "/RegistrationFiles/" + "imagespace_coord_femur.txt";
    else if(m_qstrAnatomy=="Tibia")
        target = QDir::currentPath() + "/RegistrationFiles/" + "imagespace_coord_tibia.txt";
    else {

    }

    QFile file_source(source);
    qDebug()<<"Spurce"<<source;

//    QString destinationImageSpace = QDir::currentPath() + "/RegistrationFiles/" + "targetPoints.txt";
    QFile file_destination(target);
    qDebug()<<"target"<<target;
    qDebug()<<"GetPickedPoints";

    if (!file_source.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file for writing!";
    }
    else
    {
        QTextStream in(&file_source);
        int lineCount = 0;
        double xvalue, yvalue, zvalue;

        while (!in.atEnd())
        {
            QString line = in.readLine().trimmed(); // Read and trim whitespace

            if (!line.isEmpty())
            {
                switch (lineCount % 3)
                {
                case 0:
                    xvalue = line.toDouble();
                    break;
                case 1:
                    yvalue = line.toDouble();
                    break;
                case 2:
                    zvalue = line.toDouble();
                    //qDebug() << "Read values:" << xvalue << yvalue << zvalue;

                    sourcePoints->InsertNextPoint(xvalue, yvalue, zvalue);
                    sourcePoints->Modified();

                    pickedPointsV1++;

                    break;
                }
                lineCount++;
            }
        }
        file_source.close();
    }

    if (!file_destination.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file for writing!";
    }
    else
    {
        QTextStream in2(&file_destination);
        int lineCount2 = 0;
        double xvalue2, yvalue2, zvalue2;

        while (!in2.atEnd())
        {
            QString line2 = in2.readLine().trimmed(); // Read and trim whitespace
            if (!line2.isEmpty())
            {
                switch (lineCount2 % 3)
                {
                case 0:
                    xvalue2 = line2.toDouble();
                    break;

                case 1:
                    yvalue2 = line2.toDouble();
                    break;

                case 2:
                    zvalue2 = line2.toDouble();
                    //qDebug() << "Read values(V2):" << xvalue2 << yvalue2 << zvalue2;
                    targetPoints->InsertNextPoint(xvalue2, yvalue2, zvalue2);
                    targetPoints->Modified();

                    pickedPointsV2++;
                    break;
                }
                lineCount2++;
            }
        }
        file_destination.close();
    }

    // if equal number of points are selected in both space
    qDebug()<<" number of sets "<<pickedPointsV1<<pickedPointsV2;

    if (pickedPointsV1 == pickedPointsV2)
    {
        qDebug()<<" saving transformation matrix to outputtransmatrix.txt";
        landmarkTransform->SetSourceLandmarks(sourcePoints);
        landmarkTransform->SetTargetLandmarks(targetPoints);
        //        landmarkTransform->SetModeToRigidBody() ;// rotation and traslation only
        landmarkTransform->SetModeToSimilarity(); // rotation and traslation and isotropic scaling (default)
        //        landmarkTransform->SetModeToAffine();
        landmarkTransform->Update();
        //vtkMatrix4x4 *M = landmarkTransform->GetMatrix();
        M = vtkSmartPointer <vtkMatrix4x4> ::New();
        M = landmarkTransform->GetMatrix();

        newTransform->SetMatrix(M);
        newTransform->GlobalWarningDisplayOff();
        newTransform->Update();
        saveVtkTransformToFile(newTransform,"test");
    }
    else
    {
        qDebug()<<"NUMBER OF POINTS PICKED IN PARIENT SPACE AND IMAGE SPACE DOSEN'T MATCH !!! ";
    }
}

void regTransformation::saveVtkTransformToFile(vtkTransform* transform, const QString& filename)
{
    // Get the 4x4 matrix from the vtkTransform
    vtkMatrix4x4* matrix = transform->GetMatrix();

    // Open the file using QFile

   QFile file;
    if(m_qstrAnatomy=="Femur")
        file.setFileName(QDir::currentPath()+"/RegistrationFiles/"+"outputtramatrix_femur.txt");
    else if(m_qstrAnatomy=="Tibia")
        file.setFileName(QDir::currentPath()+"/RegistrationFiles/"+"outputtramatrix_tibia.txt");
    else {

    }


    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error opening file for writing.";
        return;
    }

    // Use QTextStream to write to the file
    QTextStream out(&file);
    out.setRealNumberPrecision(6); // Set precision for floating-point numbers

    // Loop through the matrix and write each value
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out << matrix->GetElement(i, j);
            if (j < 3) {
                out << " "; // Space between values in the same row
            }
        }
        out << "\n"; // Newline for each row
    }
    // Close the file
    file.close();
    qDebug() << " output data writing done ";
}

QString regTransformation::getQstrAnatomy() const
{
    return m_qstrAnatomy;
}

void regTransformation::setQstrAnatomy(const QString &qstrAnatomy)
{
    qDebug()<<" anatomy recieved "<<qstrAnatomy;
    m_qstrAnatomy = qstrAnatomy;
}



void regTransformation::SaveTransformationMatrix()
{
    qDebug()<<"SaveTransformationMatrix";

    // save to file
    QString m_file1Path = QDir::currentPath() + "/RegistrationFiles/" + "transformation_matrix.txt";
    QFile file(m_file1Path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        // Write the matrix values to the file
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                out << M->GetElement(i, j) << " ";
            }
            out << "\n";
        }
        file.close();
    }
}

Eigen::Vector3d regTransformation::getImageSpaceCoord(double x_patient,double y_patient,double z_patient)
{
    Eigen::Matrix4d T_patient_to_image;
    T_patient_to_image = readMatrixFromFile(); // Assume you have this transformation matrix

    // The point in patient space (homogeneous coordinates [x, y, z, 1])
    Eigen::Vector4d point_in_patient_space;
    point_in_patient_space << x_patient, y_patient, z_patient, 1.0; // 1.0 for homogeneous coordinates

    // Apply the transformation to get the corresponding point in image space
    Eigen::Vector4d point_in_image_space = T_patient_to_image * point_in_patient_space;

    // Extract the image space coordinates (x, y, z)
    Eigen::Vector3d point_in_image;
    point_in_image << point_in_image_space(0), point_in_image_space(1), point_in_image_space(2);

    return point_in_image;
}

// Function to read the matrix from a file and return Eigen::Matrix4d
Eigen::Matrix4d regTransformation::readMatrixFromFile()
{
    QString filePath = QDir::currentPath() + "/RegistrationFiles/" + "transformation_matrix.txt";
    Eigen::Matrix4d T_patient_to_image;  // Matrix to store the transformation

    QFile file(filePath);

    // Open the file in read-only mode
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error: Cannot open the file." << std::endl;
        return T_patient_to_image;
    }

    QTextStream in(&file);
    QString line;
    int row = 0;

    // Read each line of the file and fill the matrix
    while (!in.atEnd() && row < 4) {
        line = in.readLine();
        QStringList values = line.split(" ");  // Split by space

        // Ensure there are exactly 4 elements per row
        if (values.size() == 4) {
            T_patient_to_image(row, 0) = values[0].toDouble();
            T_patient_to_image(row, 1) = values[1].toDouble();
            T_patient_to_image(row, 2) = values[2].toDouble();
            T_patient_to_image(row, 3) = values[3].toDouble();
        } else {
            std::cerr << "Error: Malformed matrix in the file." << std::endl;
            break;
        }
        row++;
    }

    // Close the file after reading
    file.close();

    return T_patient_to_image;
}
// Function to convert a quaternion to a rotation matrix
Eigen::Matrix3d regTransformation::quaternionToRotationMatrix(const Eigen::Quaterniond &ref_quat) {
    // Convert quaternion to rotation matrix
    Eigen::Matrix3d ref2cam_r = ref_quat.toRotationMatrix();

    // Transpose the rotation matrix
    return ref2cam_r.transpose(); // Return the transpose
}

// Function to create a transformation matrix (4x4) from a rotation matrix and translation vector
Eigen::Matrix4d regTransformation::composeTransformationMatrix(const Eigen::Matrix3d &rotation_matrix, const Eigen::Vector3d &translation_vector) {
    // Create a 4x4 transformation matrix
    Eigen::Matrix4d transformation_matrix = Eigen::Matrix4d::Identity();

    // Set the upper-left 3x3 part as the rotation matrix
    transformation_matrix.block<3, 3>(0, 0) = rotation_matrix;

    // Set the top-right 3x1 part as the translation vector
    transformation_matrix.block<3, 1>(0, 3) = translation_vector;

    return transformation_matrix; // Return the 4x4 transformation matrix
}

// Function to compute the inverse of the transformation matrix (4x4)
Eigen::Matrix4d regTransformation::invertTransformationMatrix(const Eigen::Matrix4d &transformation_matrix) {
    // Compute the inverse
    return transformation_matrix.inverse();
}

// Main logic combining the functions
Eigen::Matrix4d regTransformation::getCameraToReferenceTransform(Eigen::Matrix3d &rotationMatrix, const Eigen::Vector3d &translation)
{
    Eigen::Matrix4d transformationMatrix = Eigen::Matrix4d::Identity();
    // Set the top-left 3x3 part to the rotation matrix
    transformationMatrix.block<3, 3>(0, 0) = rotationMatrix;

    // Set the top-right 3x1 part to the translation vector
    transformationMatrix.block<3, 1>(0, 3) = translation;

    // Print the transformation matrix
//    std::cout << "Transformation Matrix: \n" << transformationMatrix << std::endl;

    // Step 6: Invert the transformation matrix
    Eigen::Matrix4d inverseTransformationMatrixcamref = transformationMatrix.inverse();

    // Print the inverted transformation matrix
//    std::cout << "Inverted Transformation Matrix: \n" << inverseTransformationMatrixcamref << std::endl;

    return inverseTransformationMatrixcamref;


}
//// Function to apply transformation matrix to a point in camera space
Eigen::Vector4d regTransformation::applyTransformation(const Eigen::Matrix4d &transformation_matrix, const Eigen::Vector3d &point_cam_space) {
    // Convert point to homogeneous coordinates [x, y, z, 1.0]
    Eigen::Vector4d point_cam_homogeneous;
    point_cam_homogeneous << point_cam_space(0), point_cam_space(1), point_cam_space(2), 1.0;

    // Apply the transformation matrix to the point
    Eigen::Vector4d point_ref_space = transformation_matrix * point_cam_homogeneous;

    return point_ref_space; // Return the point in reference space
}

