#include "surfaceregistrationdata.h"

surfaceRegistrationData::surfaceRegistrationData(QObject *parent) : QObject(parent)
{

}

void surfaceRegistrationData::fromJson(const QJsonObject &jsonObj)
{
    //    qDebug()<<"fromJson-cameraData";

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

        if (jsonObj.contains("FiducialDataList") && jsonObj["FiducialDataList"].isArray() && jsonObj["FiducialDataList"].isArray()) {
            QJsonArray fiducialArray = jsonObj["FiducialDataList"].toArray();

            // Iterate through the array and extract values
            for (const QJsonValue &value : fiducialArray) {
                if (value.isArray()) {
                    QJsonArray pointArray = value.toArray();
                    QList<double> pointList;

                    // Save coordinates to the pointList
                    pointList.append(pointArray[0].toDouble());
                    pointList.append(pointArray[1].toDouble());
                    pointList.append(pointArray[2].toDouble());

                    qDebug()<<" points "<<pointList[0]<<pointList[1]<<pointList[2];

                    // Add the pointList to the fiducialDataList
                    fiducialDataList.append(pointList);
                }
            }
        }

        else {
            qDebug() << "FiducialDataList not found or is not an array";
        }

        //registred marker list
        if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray() && !markerOnceTaken)
        {
            QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
            // Iterate over the array of markers
            for (const QJsonValue& value : markersArray) {
                if (value.isObject()) {
                    QJsonObject markerObj = value.toObject();
                    if(markerObj["MarkerName"].toString()=="435300")
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

                            QFile file(QDir::currentPath()+"/registrationFiles/"+"markerCoodSurface.txt");

                            // Open the file in append mode (QIODevice::Append)
                            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                                qDebug() << "Failed to open file for appending";
                                return;
                            }

                            QTextStream out(&file);
                            out << marker.Top.point.x << "\n";
                            out << marker.Top.point.y << "\n";
                            out << marker.Top.point.z << "\n";
                            file.close();
                            marker.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                            marker.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                            marker.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                            marker.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                            marker.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                            marker.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                            marker.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                            marker.Top.angle.ang = topObj["Angle"].toObject()["ang"].toDouble();

                            QFile fileoth(QDir::currentPath()+"/registrationFiles/"+"markerRotForSurface.txt");

                            // Open the file in append mode (QIODevice::Append)
                            if (!fileoth.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                                qDebug() << "Failed to open file for appending";
                                return;
                            }

                            QTextStream outOth(&fileoth);
                            // Append the marker's scale data
                            outOth << "\nScale:\n";
                            outOth << "x: " << marker.Top.scale.x << "\n";
                            outOth << "y: " << marker.Top.scale.y << "\n";
                            outOth << "z: " << marker.Top.scale.z << "\n";

                            // Append the marker's rotation data
                            outOth << "\nRotation:\n";
                            outOth << "x: " << marker.Top.rotation.x << "\n";
                            outOth << "y: " << marker.Top.rotation.y << "\n";
                            outOth << "z: " << marker.Top.rotation.z << "\n";
                            outOth << "w: " << marker.Top.rotation.w << "\n";

                            // Append the marker's angle data
                            outOth << "\nAngle:\n";
                            outOth << "ang: " << marker.Top.angle.ang << "\n";

                            // Optionally, add a separator between entries
                            outOth << "\n---\n";

                            // Close the file
                            fileoth.close();


                            Eigen::Quaterniond q( marker.Top.rotation.w, marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z );

                            // Normalize the quaternion (important step to ensure it's a valid rotation quaternion)
                            q.normalize();

                            // Convert the quaternion to a rotation matrix
                            Eigen::Matrix3d rotationMatrix = q.toRotationMatrix();
                            Eigen::Vector3d translation(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            //                        Eigen::Quaterniond ref_quat(marker.Top.rotation.w, marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z ); // Identity quaternion as an example
                            //                        Eigen::Vector3d ref_pos(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z); // Example translation vector

                            cam2ref_tf = objregTransformation.getCameraToReferenceTransform(rotationMatrix, translation);

                            //                    markerTransformationMatrix =     objregTransformation.createTransformationMatrix
                            //                                (marker.Top.point.x, marker.Top.point.y, marker.Top.point.z,
                            //                                  marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z,  marker.Top.rotation.w);
                        }

                        //                registeredMarkersList.markers.push_back(marker);
                    }
                }
            }
            markerOnceTaken=true;
        }

        //registred marker list
        if (jsonObj.contains("RegisteredMarkersList") && jsonObj["RegisteredMarkersList"].isArray())
        {
            QJsonArray markersArray = jsonObj["RegisteredMarkersList"].toArray();
            // Iterate over the array of markers
            for (const QJsonValue& value : markersArray) {
                if (value.isObject()) {
                    QJsonObject markerObj = value.toObject();
//                    if(markerObj["MarkerName"].toString()=="11001")
                    if(markerObj["MarkerName"].toString()=="7100098")

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

                            QFile file(QDir::currentPath()+"/registrationFiles/"+"regCoordSurface.txt");

                            // Open the file in append mode (QIODevice::Append)
                            if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                                qDebug() << "Failed to open file for appending";
                                return;
                            }

                            QTextStream out(&file);
                            out << marker.Top.point.x << "\n";
                            out << marker.Top.point.y << "\n";
                            out << marker.Top.point.z << "\n";
                            file.close();
                            marker.Top.scale.x = topObj["scale"].toObject()["x"].toDouble();
                            marker.Top.scale.y = topObj["scale"].toObject()["y"].toDouble();
                            marker.Top.scale.z = topObj["scale"].toObject()["z"].toDouble();

                            marker.Top.rotation.x = topObj["rotation"].toObject()["x"].toDouble();
                            marker.Top.rotation.y = topObj["rotation"].toObject()["y"].toDouble();
                            marker.Top.rotation.z = topObj["rotation"].toObject()["z"].toDouble();
                            marker.Top.rotation.w = topObj["rotation"].toObject()["w"].toDouble();

                            marker.Top.angle.ang = topObj["Angle"].toObject()["ang"].toDouble();

                            QFile fileoth(QDir::currentPath()+"/registrationFiles/"+"regrotscalangleSurface.txt");

                            // Open the file in append mode (QIODevice::Append)
                            if (!fileoth.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
                                qDebug() << "Failed to open file for appending";
                                return;
                            }

                            QTextStream outOth(&fileoth);
                            // Append the marker's scale data
                            outOth << "\nScale:\n";
                            outOth << "x: " << marker.Top.scale.x << "\n";
                            outOth << "y: " << marker.Top.scale.y << "\n";
                            outOth << "z: " << marker.Top.scale.z << "\n";

                            // Append the marker's rotation data
                            outOth << "\nRotation:\n";
                            outOth << "x: " << marker.Top.rotation.x << "\n";
                            outOth << "y: " << marker.Top.rotation.y << "\n";
                            outOth << "z: " << marker.Top.rotation.z << "\n";
                            outOth << "w: " << marker.Top.rotation.w << "\n";

                            // Append the marker's angle data
                            outOth << "\nAngle:\n";
                            outOth << "ang: " << marker.Top.angle.ang << "\n";

                            // Optionally, add a separator between entries
                            outOth << "\n---\n";

                            // Close the file
                            fileoth.close();

                            Eigen::Vector3d point_cam_space(marker.Top.point.x, marker.Top.point.y, marker.Top.point.z);

                            //                        regPointTransformationMatrix =     objregTransformation.createTransformationMatrix
                            //                                     (marker.Top.point.x, marker.Top.point.z, marker.Top.point.y,
                            //                                       marker.Top.rotation.x,  marker.Top.rotation.y,  marker.Top.rotation.z,  marker.Top.rotation.w);


                            //                        Eigen::Matrix4d result = objregTransformation.transformTool1ToMarkerCoordinate(markerTransformationMatrix,regPointTransformationMatrix);

                            Eigen::Vector4d point_ref_space =objregTransformation.applyTransformation(cam2ref_tf, point_cam_space);
//                            qDebug() << "Transformed point:"
//                                     << point_ref_space(0) << point_ref_space(1) << point_ref_space(2) << point_ref_space(3);
                            saveVectorToFile(point_ref_space, "transformed_point_Surface.txt");
                            //
                        }
                    }
                }
            }
        }
}
void surfaceRegistrationData::saveVectorToFile(const Eigen::Vector4d& vector, QString filename)
{
    QString filePath = QDir::currentPath() + "/registrationFiles/" + filename;
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Append)) {
//        qDebug() << "Error opening file for writing:" << filePath;
        return;
    }

    QTextStream out(&file);
    out.setRealNumberPrecision(6); // Set precision for floating-point numbers

    // Write the vector to the file
    for (int i = 0; i < 3; ++i) {
        out << vector(i)<<"\n";
        //        if (i < 3) out << " "; // Separate elements with a space
    }

    file.close();
}
