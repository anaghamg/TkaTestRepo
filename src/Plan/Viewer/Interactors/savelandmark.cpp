#include "savelandmark.h"

//---------divya added-----------
// Initialize the static variable
QHash<QString, QVector<double>> savelandmark::m_PlanningPoints;
//------------------------------

// Constructor
savelandmark::savelandmark(QWidget *parent) : QWidget(parent)
{
    // Initialize root only once
    root = vtkSmartPointer<vtkXMLDataElement>::New();
    root->SetName("PickedPoints");

    // Set default values
    myvtk_bone = "Femur";
    myvtk_anatomyid = 1;
    myvtk_anatomy = "Hip Center";

    const std::string& filename = "Landmark.xml";
    QFile fileq(filename.c_str());
    if (fileq.exists()) {
        root = xmlUtilities->ReadElementFromFile(filename.c_str());
        //        qDebug() << "Existing XML file loaded.";
    }

}

void savelandmark::slotLandmarkPoint(std::array<double, 3> point)
{
    qDebug() << "slotLandmarkPoint *** " << point[0] << point[1] << point[2];
    landmarkPoint[0] = point[0];
    landmarkPoint[1] = point[1];
    landmarkPoint[2] = point[2];

    writeXML();
    //    writeCSV();

    //-----------Divya Added------------
    coordVec[0] = point[0];
    coordVec[1] = point[1];
    coordVec[2] = point[2];
    trimmed_anatomyname = myvtk_anatomy.trimmed();
    savelandmark::m_PlanningPoints.insert(trimmed_anatomyname, coordVec);
    //----------------------------
}

void savelandmark::writeXML()
{
    const std::string& filename = "Landmark.xml";
    QDir dir(QDir::currentPath());

    // Get the parent path (up to the last directory)
    QString parentPath = dir.path();
    parentPath = dir.cdUp() ? dir.path() : QString();
    parentPath = parentPath + "/TKA_Kinematics_Ver1.0/code/Landmark.csv";
    qDebug() << "Parent path:" << parentPath ;
    const std::string& csvFilename = parentPath.toStdString();

    bool entryExists = false;
    vtkXMLDataElement* existingPointElement = nullptr;

    // Check if an entry with the same anatomy ID and bone name already exists in XML
    for (int i = 0; i < root->GetNumberOfNestedElements(); ++i) {
        vtkXMLDataElement* element = root->GetNestedElement(i);

        if (element->GetAttribute("anatomyid") && element->GetAttribute("bone_name")) {
            int existingAnatomyID = 0;
            std::string existingBoneName = element->GetAttribute("bone_name");

            element->GetScalarAttribute("anatomyid", existingAnatomyID);

            // Check both bone name and anatomy ID for a match
            if (existingAnatomyID == myvtk_anatomyid && existingBoneName == myvtk_bone.toStdString()) {
                //                qDebug() << "Matching bone and anatomy ID found.";
                entryExists = true;
                existingPointElement = element;
                break;
            }
        }
    }

    // Writing to XML file
    if (entryExists) {
        // Overwrite the existing entry
        existingPointElement->SetAttribute("bone_name", myvtk_bone.toStdString().c_str());
        existingPointElement->SetIntAttribute("anatomyid", myvtk_anatomyid);
        existingPointElement->SetAttribute("anatomy", myvtk_anatomy.toStdString().c_str());
        existingPointElement->SetDoubleAttribute("x", landmarkPoint[0]);
        existingPointElement->SetDoubleAttribute("y", landmarkPoint[1]);
        existingPointElement->SetDoubleAttribute("z", landmarkPoint[2]);


        //        qDebug() << "Updated existing point for bone: " << myvtk_bone << ", anatomy ID: " << myvtk_anatomyid;
    } else {
        // Add a new point element since no matching entry was found
        int pointID = root->GetNumberOfNestedElements() + 1;
        vtkSmartPointer<vtkXMLDataElement> pointElement = vtkSmartPointer<vtkXMLDataElement>::New();
        std::string label = "Point" + std::to_string(pointID);
        pointElement->SetName(label.c_str());

        pointElement->SetAttribute("bone_name", myvtk_bone.toStdString().c_str());
        pointElement->SetIntAttribute("anatomyid", myvtk_anatomyid);
        pointElement->SetAttribute("anatomy", myvtk_anatomy.toStdString().c_str());
        pointElement->SetDoubleAttribute("x", landmarkPoint[0]);
        pointElement->SetDoubleAttribute("y", landmarkPoint[1]);
        pointElement->SetDoubleAttribute("z", landmarkPoint[2]);

        root->AddNestedElement(pointElement);

        //        qDebug() << "Added new point for bone: " << myvtk_bone << ", anatomy ID: " << myvtk_anatomyid;
    }


    // Write the updated root to the XML file
    xmlUtilities->WriteElementToFile(root, filename.c_str());

    // Writing to CSV file
        std::vector<std::string> lines;
        std::ifstream csvFile(csvFilename);
        std::string line;
        bool csvEntryExists = false;

        // Read the CSV file line by line and check if the anatomyid and bone_name already exist
        while (std::getline(csvFile, line)) {
            std::stringstream ss(line);
            std::string anatomy, xStr, yStr, zStr;

            std::getline(ss, anatomy, ',');
            std::getline(ss, xStr, ',');
            std::getline(ss, yStr, ',');
            std::getline(ss, zStr, ',');

            if (anatomy == myvtk_anatomy.toStdString()) {
                // Overwrite the existing line
                std::stringstream newLine;
                newLine << myvtk_anatomy.toStdString() << ","
                        << landmarkPoint[0] << ","
                        << landmarkPoint[1] << ","
                        << landmarkPoint[2];
                lines.push_back(newLine.str());
                csvEntryExists = true;
                qDebug() << "Overwrote line in CSV for bone: " << myvtk_bone << ", anatomy ID: " << myvtk_anatomyid;
            } else {
                lines.push_back(line);  // Keep existing lines as is
            }
        }
        csvFile.close();

        // If the entry didn't exist, add a new line
        if (!csvEntryExists) {
            std::stringstream newLine;
            newLine << myvtk_anatomy.toStdString() << ","
                    << landmarkPoint[0] << ","
                    << landmarkPoint[1] << ","
                    << landmarkPoint[2];
            lines.push_back(newLine.str());

            qDebug() << "Added new line to CSV for bone: " << myvtk_bone << ", anatomy ID: " << myvtk_anatomyid;
        }

        // Write the updated contents back to the CSV file
        std::ofstream outputFile(csvFilename);
        for (const auto& outputLine : lines) {
            outputFile << outputLine << std::endl;
        }
        outputFile.close();


    // saving values to struct
    annotationValues values;
    values.bone_name = myvtk_bone;
    values.anatomyid = myvtk_anatomyid;
    values.anatomy = myvtk_anatomy;
    values.x = landmarkPoint[0];
    values.y = landmarkPoint[1];
    values.z = landmarkPoint[2];


    valuesList.append(values);

}


void savelandmark::slotLandmarkFeatures(QString bone_name, int anatomyid, const QString &anatomy)
{
    qDebug() << "slotLandmarkFeatures ** " << bone_name << anatomyid << anatomy;
    myvtk_bone = bone_name;
    myvtk_anatomyid = anatomyid;
    myvtk_anatomy = anatomy;
}
