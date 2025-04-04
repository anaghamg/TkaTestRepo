#include "cameradata.h"

cameraData::cameraData()
{

}

QString cameraData::getQueryType() const
{
    return queryType;
}

void cameraData::setQueryType(const QString &value)
{
    queryType = value;
}

QString cameraData::getVersion() const
{
    return version;
}

void cameraData::setVersion(const QString &value)
{
    version = value;
}

bool cameraData::getIsCameraDataObtained() const
{
    return isCameraDataObtained;
}

void cameraData::setIsCameraDataObtained(bool value)
{
    isCameraDataObtained = value;
}

int cameraData::getConnectionStatusFromcam() const
{
    return connectionStatusFromcam;
}

void cameraData::setConnectionStatusFromcam(int value)
{
    connectionStatusFromcam = value;
}

bool cameraData::getIsShockObtained() const
{
    return isShockObtained;
}

void cameraData::setIsShockObtained(bool value)
{
    isShockObtained = value;
}

float cameraData::getCameraTilt() const
{
    return cameraTilt;
}

void cameraData::setCameraTilt(float value)
{
    cameraTilt = value;
}

float cameraData::getTimeStamp() const
{
    return timeStamp;
}

void cameraData::setTimeStamp(float value)
{
    timeStamp = value;
}

float cameraData::getTotalTimeElapsed() const
{
    return TotalTimeElapsed;
}

void cameraData::setTotalTimeElapsed(float value)
{
    TotalTimeElapsed = value;
}

int cameraData::getInitialisationStatus() const
{
    return InitialisationStatus;
}

void cameraData::setInitialisationStatus(int value)
{
    InitialisationStatus = value;
}

void cameraData::fromJson(const QJsonObject &jsonObj)
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
    if (m_qstrAnatomy=="Femur")
    {
        //                qDebug()<<" femur anatomy selected in cameraData ";

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

                    if(markerObj["MarkerName"].toString()==QString::number(toolid))
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

                            Eigen::Quaterniond quaternion_tool(marker.Top.rotation.w, marker.Top.rotation.x, marker.Top.rotation.y, marker.Top.rotation.z);  // Note: Eigen's quaternion is w, x, y, z

                            Eigen::Vector3d point_cam_space(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);
                            quaternion_tool.normalize();
                            //                        quaternion_toold.normalize();
                            Eigen::Matrix3d rotationMatrix_tool = quaternion_tool.toRotationMatrix();  // Convert to 3x3 rotation matrix
                            Eigen::Matrix4d transformationMatrix_tool_camera = Eigen::Matrix4d::Identity();

                            transformationMatrix_tool_camera.block<3, 3>(0, 0) = rotationMatrix_tool;
                            transformationMatrix_tool_camera.block<3, 1>(0, 3) = point_cam_space;


                            /**************for real track*************/
                            for (const QJsonValue& valueref : markersArray)
                            {
                                if (valueref.isObject()) {
                                    QJsonObject markerObjref = valueref.toObject();
                                    if(markerObjref["MarkerName"].toString()==QString::number(femurRef))
                                    {
                                        Marker markerref;
                                        markerref.MarkerName  = markerObjref["MarkerName"].toString();
                                        markerref.ErrorStatus = markerObjref["ErrorStatus"].toString();
                                        markerref.ErrorValue = markerObjref["ErrorValue"].toDouble();
                                        // Access "Top" and "Bottom" objects
                                        if (markerObjref.contains("Top") && markerObjref["Top"].isObject())
                                        {

                                            QJsonObject topObj = markerObjref["Top"].toObject();
                                            QJsonObject pointObj = topObj["point"].toObject();
                                            QJsonObject scaleObj = topObj["scale"].toObject();
                                            QJsonObject rotationObj = topObj["rotation"].toObject();
                                            QJsonObject angleObj = topObj["Angle"].toObject();

                                            // Fill the Top struct
                                            markerref.Top.point.x = topObj["point"].toObject()["x"].toDouble();
                                            markerref.Top.point.y = topObj["point"].toObject()["y"].toDouble();
                                            markerref.Top.point.z = topObj["point"].toObject()["z"].toDouble();


                                            markerref.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                                            markerref.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                                            markerref.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                                            markerref.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                                            markerref.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                                            markerref.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                                            markerref.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                                            markerref.Top.angle.ang = topObj["Angle"].toObject()["ang"].toDouble();
                                            Eigen::Quaterniond q( markerref.Top.rotation.w, markerref.Top.rotation.x,  markerref.Top.rotation.y,  markerref.Top.rotation.z );
                                            q.normalize();
                                            Eigen::Matrix3d rotationMatrix = q.toRotationMatrix();
                                            Eigen::Vector3d translation(markerref.Top.point.x, markerref.Top.point.y, markerref.Top.point.z);
                                            cam2ref_tf_fem = objregTransformation.getCameraToReferenceTransform(rotationMatrix, translation);
                                        }
                                    }
                                }
                            }

                            Eigen::Matrix4d transformationMatrix_tool_ref =  cam2ref_tf_fem/*.inverse()*/ *transformationMatrix_tool_camera/*.inverse()*/;

                            QString filepathOout = QDir::currentPath() + "/RegistrationFiles/" + "outputtramatrix_femur.txt";
                            transformMatF = readTransMatFromFile(filepathOout);
                            Eigen::Matrix4d eigenTransformationMatrix = qMatrix4x4ToEigen(transformMatF);
                            Eigen::Matrix4d transformationMatrix_tool_img = eigenTransformationMatrix/*.inverse()*/ * transformationMatrix_tool_ref/*.inverse()*/;
//                            transformationMatrix_tool_img.inverse();
                            vtkSmartPointer<vtkMatrix4x4> vtkTransformMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
                            for (int i = 0; i < 4; i++) {
                                for (int j = 0; j < 4; j++) {
                                    vtkTransformMatrix->SetElement(i, j, transformationMatrix_tool_img(i, j));
                                }
                            }
                            vtkSmartPointer<vtkTransform> vtkTransformTool = vtkSmartPointer<vtkTransform>::New();
                            vtkTransformTool->SetMatrix(vtkTransformMatrix);
                            emit signalTrackToolF(vtkTransformTool,cam2ref_tf_fem);

                        }
                    }
                }
            }
        }
    }
    else if (m_qstrAnatomy=="Tibia")
    {
        //        qDebug()<<" tibia anatomy selected in cameraData ";

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

                            marker.Top.angle.ang = topObj["Angle"].toObject()["ang"].toDouble();

                            Eigen::Quaterniond quaternion_tool(marker.Top.rotation.w, marker.Top.rotation.x, marker.Top.rotation.y, marker.Top.rotation.z);  // Note: Eigen's quaternion is w, x, y, z
                            Eigen::Vector3d point_cam_space(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            quaternion_tool.normalize();

                            Eigen::Matrix3d rotationMatrix_tool = quaternion_tool.toRotationMatrix();  // Convert to 3x3 rotation matrix

                            Eigen::Matrix4d transformationMatrix_tool_camera = Eigen::Matrix4d::Identity();

                            transformationMatrix_tool_camera.block<3, 3>(0, 0) = rotationMatrix_tool;
                            transformationMatrix_tool_camera.block<3, 1>(0, 3) = point_cam_space;
                            for (const QJsonValue& value : markersArray) {
                                if (value.isObject()) {
                                    QJsonObject markerObj = value.toObject();
                                    if(markerObj["MarkerName"].toString()== QString::number(tibiaRef))
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
                                            // Normalize the quaternion (important step to ensure it's a valid rotation quaternion)
                                            q.normalize();
                                            // Convert the quaternion to a rotation matrix
                                            Eigen::Matrix3d rotationMatrix = q.toRotationMatrix();
                                            Eigen::Vector3d translation(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);


                                            cam2ref_tf_tib = objregTransformation.getCameraToReferenceTransform(rotationMatrix, translation);
                                        }



                                    }
                                }
                            }

                            Eigen::Matrix4d transformationMatrix_tool_ref = cam2ref_tf_tib * transformationMatrix_tool_camera;

                            QString filepathOout = QDir::currentPath() + "/RegistrationFiles/" + "outputtramatrix_tibia.txt";

                            transformMatT = readTransMatFromFile(filepathOout);

                            Eigen::Matrix4d eigenTransformationMatrix = qMatrix4x4ToEigen(transformMatT);
                            Eigen::Matrix4d transformationMatrix_tool_img = eigenTransformationMatrix * transformationMatrix_tool_ref;

                            vtkSmartPointer<vtkMatrix4x4> vtkTransformMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
                            for (int i = 0; i < 4; i++) {
                                for (int j = 0; j < 4; j++) {
                                    vtkTransformMatrix->SetElement(i, j, transformationMatrix_tool_img(i, j));
                                }
                            }

                            vtkSmartPointer<vtkTransform> vtkTransformTool = vtkSmartPointer<vtkTransform>::New();
                            vtkTransformTool->SetMatrix(vtkTransformMatrix);

                            emit signalTrackToolT(vtkTransformTool,cam2ref_tf_tib);
                        }
                    }
                }
            }
        }
    }

}



Eigen::Matrix4d cameraData::qMatrix4x4ToEigen(const QMatrix4x4& qMatrix)
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

QMatrix4x4 cameraData::readTransMatFromFile(const QString &filePath)
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
void cameraData::printData() const
{

}
