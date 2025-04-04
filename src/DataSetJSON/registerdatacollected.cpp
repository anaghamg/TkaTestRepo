#include "registerdatacollected.h"

registerDataCollected::registerDataCollected(QObject *parent) : QObject(parent)
{



}

void registerDataCollected::fromJson(const QJsonObject &jsonObj, QString Anatomy)
{
    /// for tool tracking window
    qRegisterMetaType<QList<QVariantMap>>("QList<QVariantMap>");

    if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray())
    {
        QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
        // Iterate over the array of markers
        for (const QJsonValue& value : markersArray) {
            if (value.isObject()) {
                QJsonObject markerObj = value.toObject();

//                                qDebug()<<" identified markers "<<markerObj["MarkerName"].toString();
                if(markerObj["MarkerName"].toString()==QString::number(toolid))
                {
                    if (markerObj.contains("FiducialList") && markerObj["FiducialList"].isArray()) {
                        QJsonArray fiducialArray = markerObj["FiducialList"].toArray();
                        QList<QVariantMap> fiducialsData;

                        for (const QJsonValue& fiducialValue : fiducialArray) {
                            if (fiducialValue.isObject()) {
                                QJsonObject fiducialObj = fiducialValue.toObject();
                                QVariantMap fiducialData;

                                if (fiducialObj.contains("point") && fiducialObj["point"].isObject()) {

                                    QJsonObject pointObj = fiducialObj["point"].toObject();
                                    fiducialData["x"] = pointObj["x"].toDouble();
                                    fiducialData["y"] = pointObj["y"].toDouble();
                                    fiducialData["z"] = pointObj["z"].toDouble();
                                }
                                fiducialData["status"] = fiducialObj["Status"].toBool();
                                fiducialData["radius"] = fiducialObj["Radius"].toDouble();

                                fiducialsData.append(fiducialData);
                            }
                        }
                        emit signalFiducialsTool(fiducialsData);

                    }
                }

                if(markerObj["MarkerName"].toString()==QString::number(femurRef))
                {
                    if (markerObj.contains("FiducialList") && markerObj["FiducialList"].isArray()) {
                        QJsonArray fiducialArray = markerObj["FiducialList"].toArray();
                        QList<QVariantMap> fiducialsData;

                        for (const QJsonValue& fiducialValue : fiducialArray) {
                            if (fiducialValue.isObject()) {
                                QJsonObject fiducialObj = fiducialValue.toObject();
                                QVariantMap fiducialData;

                                if (fiducialObj.contains("point") && fiducialObj["point"].isObject()) {

                                    QJsonObject pointObj = fiducialObj["point"].toObject();
                                    fiducialData["x"] = pointObj["x"].toDouble();
                                    fiducialData["y"] = pointObj["y"].toDouble();
                                    fiducialData["z"] = pointObj["z"].toDouble();
                                }
                                fiducialData["status"] = fiducialObj["Status"].toBool();
                                fiducialData["radius"] = fiducialObj["Radius"].toDouble();

                                fiducialsData.append(fiducialData);
                            }
                        }
                        emit signalFiducialsFemurRef(fiducialsData);
                    }
                }
                if(markerObj["MarkerName"].toString()==QString::number(tibiaRef))
                {
                    if (markerObj.contains("FiducialList") && markerObj["FiducialList"].isArray()) {
                        QJsonArray fiducialArray = markerObj["FiducialList"].toArray();
                        QList<QVariantMap> fiducialsData;

                        for (const QJsonValue& fiducialValue : fiducialArray) {
                            if (fiducialValue.isObject()) {
                                QJsonObject fiducialObj = fiducialValue.toObject();
                                QVariantMap fiducialData;

                                if (fiducialObj.contains("point") && fiducialObj["point"].isObject()) {

                                    QJsonObject pointObj = fiducialObj["point"].toObject();
                                    fiducialData["x"] = pointObj["x"].toDouble();
                                    fiducialData["y"] = pointObj["y"].toDouble();
                                    fiducialData["z"] = pointObj["z"].toDouble();
                                }
                                fiducialData["status"] = fiducialObj["Status"].toBool();
                                fiducialData["radius"] = fiducialObj["Radius"].toDouble();

                                fiducialsData.append(fiducialData);
                            }
                        }
                        emit signalFiducialsTibiaRef(fiducialsData);
                    }
                }
            }
        }
    }

    /// done
    m_qstrAnatomy=Anatomy;
    if(Anatomy=="Femur")
    {
        RegisteredMarkersList registeredMarkersList;
        // Parsing the JSON data
        queryType = jsonObj["QueryType"].toString();
        version = jsonObj["Version"].toString();
        isCameraDataObtained = jsonObj["IsCameraDataObtained"].toBool();
        isShockObtained = jsonObj["ShockObtained"].toBool();
        cameraTilt = jsonObj["CameraTilt"].toDouble();
        timeStamp = jsonObj["TimeStamp"].toDouble();
        connectionStatusFromcam = jsonObj["ConnectionStatus"].toInt();
        InitialisationStatus = jsonObj["InitialisationStatus"].toInt();

        //registred marker list
        if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray() )
        {
            QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
            // Iterate over the array of markers
            for (const QJsonValue& value : markersArray) {
                if (value.isObject()) {
                    QJsonObject markerObj = value.toObject();
                    if(markerObj["MarkerName"].toString()==QString::number(femurRef))
                    {
                        Marker marker;
                        marker.MarkerName  = markerObj["MarkerName"].toString();
                        marker.ErrorStatus = markerObj["ErrorStatus"].toString();
                        marker.ErrorValue = markerObj["ErrorValue"].toDouble();
                        // Access "Top" and "Bottom" objects
                        if (markerObj.contains("Top") && markerObj["Top"].isObject())
                        {

                            QJsonObject topObj = markerObj["Top"].toObject();
                            QJsonObject pointObj = topObj["point"].toObject();
                            QJsonObject scaleObj = topObj["scale"].toObject();
                            QJsonObject rotationObj = topObj["rotation"].toObject();
                            QJsonObject angleObj = topObj["Angle"].toObject();

                            // Fill the Top struct
                            marker.Top.point.x = topObj["point"].toObject()["x"].toDouble();
                            marker.Top.point.y = topObj["point"].toObject()["y"].toDouble();
                            marker.Top.point.z = topObj["point"].toObject()["z"].toDouble();

                            marker.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                            marker.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                            marker.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                            marker.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                            marker.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                            marker.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                            marker.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                            marker.Top.angle.ang = topObj["Angle"].toObject()["ang"].toDouble();

                            Eigen::Quaterniond q( marker.Top.rotation.w, marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z );

                            q.normalize();

                            // Convert the quaternion to a rotation matrix
                            Eigen::Matrix3d rotationMatrix = q.toRotationMatrix();
                            Eigen::Vector3d translation(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            cam2ref_tf_femur = objregTransformation.getCameraToReferenceTransform(rotationMatrix, translation);
                        }
                    }
                }
            }
        }
        //registred marker list
        if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray())
        {
            QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
            // Iterate over the array of markers
            for (const QJsonValue& value : markersArray) {
                if (value.isObject()) {
                    QJsonObject markerObj = value.toObject();

                    if(markerObj["MarkerName"].toString()== QString::number(toolid))
                    {
                        Marker marker;
                        marker.MarkerName  = markerObj["MarkerName"].toString();
                        marker.ErrorStatus = markerObj["ErrorStatus"].toString();
                        marker.ErrorValue = markerObj["ErrorValue"].toDouble();
                        // Access "Top" and "Bottom" objects
                        if (markerObj.contains("Top") && markerObj["Top"].isObject())
                        {

                            QJsonObject topObj = markerObj["Top"].toObject();
                            QJsonObject pointObj = topObj["point"].toObject();
                            QJsonObject scaleObj = topObj["scale"].toObject();
                            QJsonObject rotationObj = topObj["rotation"].toObject();
                            QJsonObject angleObj = topObj["Angle"].toObject();

                            // Fill the Top struct
                            marker.Top.point.x = topObj["point"].toObject()["x"].toDouble();
                            marker.Top.point.y = topObj["point"].toObject()["y"].toDouble();
                            marker.Top.point.z = topObj["point"].toObject()["z"].toDouble();

                            marker.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                            marker.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                            marker.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                            marker.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                            marker.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                            marker.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                            marker.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                            Eigen::Quaterniond quaternion_tool( marker.Top.rotation.w, marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z );
                            quaternion_tool.normalize();
                            Eigen::Vector3d point_cam_space(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            Eigen::Matrix3d rotationMatrix_tool = quaternion_tool.toRotationMatrix();  // Convert to 3x3 rotation matrix
                            Eigen::Matrix4d transformationMatrix_tool_camera = Eigen::Matrix4d::Identity();

                            transformationMatrix_tool_camera.block<3, 3>(0, 0) = rotationMatrix_tool;
                            transformationMatrix_tool_camera.block<3, 1>(0, 3) = point_cam_space;

                            Eigen::Matrix4d reftoolRot = cam2ref_tf_femur * transformationMatrix_tool_camera;

                            QString filepathOout = QDir::currentPath() + "/RegistrationFiles/" + "outputtramatrix_femur.txt";
                            transformMatF = readTransMatFromFile(filepathOout);
                            Eigen::Matrix4d eigenTransformationMatrix = qMatrix4x4ToEigen(transformMatF);
                            Eigen::Matrix4d transformationMatrix_tool_img = eigenTransformationMatrix * reftoolRot;

                            emit signalTrackToolF(transformationMatrix_tool_img);

                            Eigen::Vector4d point_ref_space =objregTransformation.applyTransformation(cam2ref_tf_femur, point_cam_space);
                            saveVectorToFile_Femur(point_ref_space);

                            emit signalRefSpaceCoordsFemur(point_ref_space);

                        }
                    }
                }
            }
        }
    }
    else if(m_qstrAnatomy=="Tibia")
    {
        RegisteredMarkersList registeredMarkersList;
        // Parsing the JSON data
        queryType = jsonObj["QueryType"].toString();
        version = jsonObj["Version"].toString();
        isCameraDataObtained = jsonObj["IsCameraDataObtained"].toBool();
        isShockObtained = jsonObj["ShockObtained"].toBool();
        cameraTilt = jsonObj["CameraTilt"].toDouble();
        timeStamp = jsonObj["TimeStamp"].toDouble();
        connectionStatusFromcam = jsonObj["ConnectionStatus"].toInt();
        InitialisationStatus = jsonObj["InitialisationStatus"].toInt();

        //registred marker list
        if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray())
        {
            QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
            // Iterate over the array of markers
            for (const QJsonValue& value : markersArray) {
                if (value.isObject()) {
                    QJsonObject markerObj = value.toObject();

                    //                    qDebug()<<" markers identified in tibia condition "<<markerObj["MarkerName"].toString();
                    if(markerObj["MarkerName"].toString()==QString::number(tibiaRef))
                    {
                        Marker marker;
                        marker.MarkerName  = markerObj["MarkerName"].toString();
                        marker.ErrorStatus = markerObj["ErrorStatus"].toString();
                        marker.ErrorValue = markerObj["ErrorValue"].toDouble();
                        // Access "Top" and "Bottom" objects
                        if (markerObj.contains("Top") && markerObj["Top"].isObject())
                        {

                            QJsonObject topObj = markerObj["Top"].toObject();
                            QJsonObject pointObj = topObj["point"].toObject();
                            QJsonObject scaleObj = topObj["scale"].toObject();
                            QJsonObject rotationObj = topObj["rotation"].toObject();
                            QJsonObject angleObj = topObj["Angle"].toObject();

                            // Fill the Top struct
                            marker.Top.point.x = topObj["point"].toObject()["x"].toDouble();
                            marker.Top.point.y = topObj["point"].toObject()["y"].toDouble();
                            marker.Top.point.z = topObj["point"].toObject()["z"].toDouble();

                            marker.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                            marker.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                            marker.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                            marker.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                            marker.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                            marker.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                            marker.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                            marker.Top.angle.ang = topObj["Angle"].toObject()["ang"].toDouble();

                            Eigen::Quaterniond q( marker.Top.rotation.w, marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z );

                            q.normalize();

                            // Convert the quaternion to a rotation matrix
                            Eigen::Matrix3d rotationMatrix = q.toRotationMatrix();
                            Eigen::Vector3d translation(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            cam2ref_tf_tibia = objregTransformation.getCameraToReferenceTransform(rotationMatrix, translation);

                        }
                    }
                }
            }
        }
        //registred marker list
        if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray())
        {
            QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
            // Iterate over the array of markers
            for (const QJsonValue& value : markersArray) {
                if (value.isObject()) {
                    QJsonObject markerObj = value.toObject();
                    if(markerObj["MarkerName"].toString()== QString::number(toolid))
                    {
                        Marker marker;
                        marker.MarkerName  = markerObj["MarkerName"].toString();
                        marker.ErrorStatus = markerObj["ErrorStatus"].toString();
                        marker.ErrorValue = markerObj["ErrorValue"].toDouble();
                        // Access "Top" and "Bottom" objects
                        if (markerObj.contains("Top") && markerObj["Top"].isObject())
                        {

                            QJsonObject topObj = markerObj["Top"].toObject();
                            QJsonObject pointObj = topObj["point"].toObject();
                            QJsonObject scaleObj = topObj["scale"].toObject();
                            QJsonObject rotationObj = topObj["rotation"].toObject();
                            QJsonObject angleObj = topObj["Angle"].toObject();

                            // Fill the Top struct
                            marker.Top.point.x = topObj["point"].toObject()["x"].toDouble();
                            marker.Top.point.y = topObj["point"].toObject()["y"].toDouble();
                            marker.Top.point.z = topObj["point"].toObject()["z"].toDouble();

                            marker.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                            marker.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                            marker.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                            marker.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                            marker.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                            marker.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                            marker.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                            Eigen::Quaterniond quaternion_tool( marker.Top.rotation.w, marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z );
                            quaternion_tool.normalize();
                            Eigen::Vector3d point_cam_space(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            Eigen::Matrix3d rotationMatrix_tool = quaternion_tool.toRotationMatrix();  // Convert to 3x3 rotation matrix
                            Eigen::Matrix4d transformationMatrix_tool_camera = Eigen::Matrix4d::Identity();

                            transformationMatrix_tool_camera.block<3, 3>(0, 0) = rotationMatrix_tool;
                            transformationMatrix_tool_camera.block<3, 1>(0, 3) = point_cam_space;

                            Eigen::Matrix4d transformationMatrix_tool_ref = cam2ref_tf_tibia * transformationMatrix_tool_camera;

                            QString filepathOout = QDir::currentPath() + "/RegistrationFiles/" + "outputtramatrix_tibia.txt";

                            transformMatT = readTransMatFromFile(filepathOout);

                            Eigen::Matrix4d eigenTransformationMatrix = qMatrix4x4ToEigen(transformMatT);
                            Eigen::Matrix4d transformationMatrix_tool_img = eigenTransformationMatrix * transformationMatrix_tool_ref;

                            emit signalTrackToolT(transformationMatrix_tool_img);

                            Eigen::Vector4d point_ref_space =objregTransformation.applyTransformation(cam2ref_tf_tibia, point_cam_space);
                            saveVectorToFile_Tibia(point_ref_space);

                            emit signalRefSpaceCoordsTibia(point_ref_space);
                        }
                    }
                }
            }
        }
    }
    else
    {

    }

}
void registerDataCollected::saveVectorToFile_Femur(const Eigen::Vector4d& vector)
{

    static bool firstCall = true; // Static flag to check if this is the first call

    QFile fileOp(filePathOp);

    // Open the file in the desired mode
    QIODevice::OpenMode mode = firstCall ? (QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)
                                         : (QIODevice::Append | QIODevice::Text);

    firstCall = false; // Set to false after the first call

    if (!fileOp.open(mode)) {
        qDebug() << "Unable to open file for writing";
        return;
    }

    QTextStream out(&fileOp);
    out.setRealNumberPrecision(6); // Set precision for floating-point numbers

    // Write the vector to the file
    for (int i = 0; i < 3; ++i) {
        out << vector(i)<<"\n";
        //        if (i < 3) out << " "; // Separate elements with a space
    }

    fileOp.close();
}


void registerDataCollected::saveVectorToFile_Tibia(const Eigen::Vector4d& vector)
{

    static bool firstCall = true; // Static flag to check if this is the first call

    QFile filetb(filePathtb);

    // Open the file in the desired mode
    QIODevice::OpenMode mode = firstCall ? (QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)
                                         : (QIODevice::Append | QIODevice::Text);

    firstCall = false; // Set to false after the first call

    if (!filetb.open(mode)) {
        qDebug() << "Unable to open file for writing";
        return;
    }

    QTextStream out(&filetb);
    out.setRealNumberPrecision(6); // Set precision for floating-point numbers

    // Write the vector to the file
    for (int i = 0; i < 3; ++i) {
        out << vector(i)<<"\n";
        //        if (i < 3) out << " "; // Separate elements with a space
    }

    filetb.close();
}
void registerDataCollected::saveMatrixToFile(const Eigen::Matrix4d& matrix, QString filename)
{
    // Construct file paths correctly by ensuring a separator is present between the directory path and the file name
    QString filePath = QDir::currentPath() + "/RegistrationFiles/"+ filename;
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "Error opening file for writing:" << filePath;
        return;
    }

    QTextStream out(&file);
    out.setRealNumberPrecision(6); // Set precision for floating-point numbers

    // Write the matrix to the file
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            out << matrix(i, j);
            if (j < 3) out << " "; // Separate elements with a space
        }
        out << "\n"; // Newline for next row
    }

    file.close();

    // Now write the marker space coordinates (Tx, Ty, Tz) to a different file
    QString markerFilePath = QDir::currentPath() + "/RegistrationFiles/"+"markerspaceCoord.txt";
    QFile filemc(markerFilePath);

    if (!filemc.open(QIODevice::WriteOnly | QIODevice::Append)) {
        qDebug() << "Error opening file for writing:" << markerFilePath;
        return;
    }

    QTextStream outmc(&filemc);
    outmc.setRealNumberPrecision(6); // Set precision for floating-point numbers

    // Write the translation part (Tx, Ty, Tz)
    outmc << matrix(0, 3) << "\n";  // Tx<< "\n"
    outmc << matrix(1, 3) << "\n";  // Ty
    outmc << matrix(2, 3) << "\n"; // Tz

    filemc.close();
}


void registerDataCollected::appendMarkerDataToFile(const QString& filename, const Marker& marker) {
    QFile file(filename);

    // Open the file in append mode (QIODevice::Append)
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "Failed to open file for appending";
        return;
    }

    QTextStream out(&file);

    // Append the marker's point data
    out << "Point:\n";
    out << "x: " << marker.Top.point.x << "\n";
    out << "y: " << marker.Top.point.y << "\n";
    out << "z: " << marker.Top.point.z << "\n";

    // Append the marker's scale data
    out << "\nScale:\n";
    out << "x: " << marker.Top.scale.x << "\n";
    out << "y: " << marker.Top.scale.y << "\n";
    out << "z: " << marker.Top.scale.z << "\n";

    // Append the marker's rotation data
    out << "\nRotation:\n";
    out << "x: " << marker.Top.rotation.x << "\n";
    out << "y: " << marker.Top.rotation.y << "\n";
    out << "z: " << marker.Top.rotation.z << "\n";
    out << "w: " << marker.Top.rotation.w << "\n";

    // Append the marker's angle data
    out << "\nAngle:\n";
    out << "ang: " << marker.Top.angle.ang << "\n";

    // Optionally, add a separator between entries
    out << "\n---\n";

    // Close the file
    file.close();
}


QMatrix4x4 registerDataCollected::readTransMatFromFile(const QString &filePath)
{
    QFile file(filePath);
    QMatrix4x4 transformationMatrix;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        float matrixValues[16];
        int index = 0;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList values = line.split(' ', QString::SkipEmptyParts);

            for (const QString& value : values) {
                matrixValues[index++] = value.toFloat();
            }
        }
        file.close();

        // Assign the matrix values to QMatrix4x4
        transformationMatrix = QMatrix4x4(matrixValues);
    }
    return transformationMatrix;
}

Eigen::Matrix4d registerDataCollected::qMatrix4x4ToEigen(const QMatrix4x4& qMatrix)
{
    Eigen::Matrix4d eMatrix;

    // Fill the Eigen matrix with values from QMatrix4x4
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            eMatrix(row, col) = qMatrix(row, col);
        }
    }

    return eMatrix;
}
