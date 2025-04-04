
/*
 * File Name : KinematicsClass.cpp
 * Version Number: 1
 * Project Code : HTG060D
 * Description of the contents of the file : Class for getting the information from Kinematics module
 * Developer :Divya N S
 * Revision History : 21-8-2024
*/
#include "kinematicsclass.h"
KinematicsClass::KinematicsClass(QWidget *parent)
    : QWidget{parent}
{
    //Getting object of savelandmark class which is used to store the landmarkpoints.

    //m_Objsavelandmark = new savelandmark();

    //            m_FemoralMechAxisP2[3]= ; //57

    //    m_FemoralTEA_P1[3]  = ;//58
    //    m_FemoralTEA_P2[3] = ;//58

    //    m_FemoralPCA_P1[3] = ;//58
    //    m_FemoralPCA_P2[3]= ;//58

    //    m_FemoralComponentAxis_P1[3]  = ;//58
    //    m_FemoralComponentAxis_P2[3] = ;//58

    //    m_TibialMechanicalAxis_P1[3]  = ;
    //    m_TibialMechanicalAxis_P2[3] = ;

    //    m_TPL_P1[3] = ;
    //    m_TPL_P2[3]= ;

    //    m_FemoralLateralPosteriorCondylePoint[3] = ;//52
    //    m_FemoralMedialPosteriorCondylePoint[3] = ;//57

    //    m_femoralLateralDistalCondylePoint[3] = ;//56.7029
    //    m_femoralMedialDistalCondylePoint[3] = ;//56.9043

    //    m_TibialLateralPlateauPoint[3] = ;
    //    m_TibialMedialPlateauPoint[3] = ;


}

void KinematicsClass::GetPointsFRomAnnotationmodule(  )
{
    QHash<QString, QVector<double>> dataHash = savelandmark::m_PlanningPoints;
    //qDebug()<<" dataHash ===="<<dataHash;
    //-----------------------FEMUR------------------------------------
    //********Mechanincal axis femur*************
    QVector<double> FHCvalues = dataHash.value("Hip Center");//Femoral head centre
    m_FemoralMechAxisP1[0] = FHCvalues[0];
    m_FemoralMechAxisP1[1] = FHCvalues[1];
    m_FemoralMechAxisP1[2] = FHCvalues[2];

    QVector<double> FeKneeCentr = dataHash.value("Femoral Knee Centre");
    m_FemoralMechAxisP2[0] = FeKneeCentr[0];
    m_FemoralMechAxisP2[1] = FeKneeCentr[1];
    m_FemoralMechAxisP2[2] = FeKneeCentr[2];
    //qDebug()<<"kinematics module called-------------------"<< dataHash<<FHCvalues[0];

    //********TransEpicondylar axis (TEA) femur*************
    QVector<double> FLEvalues = dataHash.value("Femoral Lateral Epicondyle");
    m_FemoralTEA_P1[0] = FLEvalues[0] ;
    m_FemoralTEA_P1[1] = FLEvalues[1];
    m_FemoralTEA_P1[2] = FLEvalues[2];

    QVector<double> FMEvalues = dataHash.value("Femoral Medial Epicondyle");
    m_FemoralTEA_P2[0]  =  FMEvalues[0];
    m_FemoralTEA_P2[1]  =  FMEvalues[1];
    m_FemoralTEA_P2[2]  =  FMEvalues[2];

    //********Posteriorcondylar axis (PCA) femur*************
    QVector<double> FLPCvalues = dataHash.value("Femoral Lateral Posterior Condyle");
    m_FemoralPCA_P1[0] = FLPCvalues[0];
    m_FemoralPCA_P1[1] = FLPCvalues[1];
    m_FemoralPCA_P1[2] = FLPCvalues[2];

    QVector<double> FMPCvalues = dataHash.value("Femoral Medial Posterior Condyle");
    m_FemoralPCA_P2[0] = FMPCvalues[0];
    m_FemoralPCA_P2[1] = FMPCvalues[1];
    m_FemoralPCA_P2[2] = FMPCvalues[2];

    //********Femoral component line *************
    int femimplant_posterior_width =13;
    double femcomponentcentrepoint[3] ={FeKneeCentr[0] ,FeKneeCentr[1]- femimplant_posterior_width,FeKneeCentr[2]};

    // Set the length (1 cm on each side of p)
    double half_length = 50.0;


    double direction[3] = {1, 0, 0}; // Example direction vector//{0.9189, 0.3927, -0.0428}; ->for old

    // Normalize the direction vector
    double magnitude = std::sqrt(direction[0] * direction[0] +
            direction[1] * direction[1] +
            direction[2] * direction[2]);
    direction[0] /= magnitude;
    direction[1] /= magnitude;
    direction[2] /= magnitude;

    // Calculate start and end points of the line
    double femcomponentstartPoint[3] = {femcomponentcentrepoint[0] - half_length * direction[0],
                                        femcomponentcentrepoint[1]- half_length* direction[1],
                                        femcomponentcentrepoint[2]- half_length* direction[2]};
    double femcomponentendPoint[3] = {femcomponentcentrepoint[0] + half_length * direction[0],
                                      femcomponentcentrepoint[1]+ half_length* direction[1],
                                      femcomponentcentrepoint[2]+ half_length* direction[2]};


    m_FemoralComponentAxis_P1[0] = femcomponentstartPoint[0];
    m_FemoralComponentAxis_P1[1] = femcomponentstartPoint[1];
    m_FemoralComponentAxis_P1[2] = femcomponentstartPoint[2];

    m_FemoralComponentAxis_P2[0] = femcomponentendPoint[0];
    m_FemoralComponentAxis_P2[1] = femcomponentendPoint[1];
    m_FemoralComponentAxis_P2[2] = femcomponentendPoint[2];

    //--Anotomicalpoints-

    m_FemoralLateralPosteriorCondylePoint[0] =  m_FemoralPCA_P1[0];
    m_FemoralLateralPosteriorCondylePoint[1] =  m_FemoralPCA_P1[1];
    m_FemoralLateralPosteriorCondylePoint[2] =  m_FemoralPCA_P1[2];

    m_FemoralMedialPosteriorCondylePoint[0] = m_FemoralPCA_P2[0];
    m_FemoralMedialPosteriorCondylePoint[1] = m_FemoralPCA_P2[1];
    m_FemoralMedialPosteriorCondylePoint[2] = m_FemoralPCA_P2[2];

    QVector<double> FLDCvalues = dataHash.value("Femoral Lateral Distal Condyle");
    m_femoralLateralDistalCondylePoint[0] = FLDCvalues[0];
    m_femoralLateralDistalCondylePoint[1] = FLDCvalues[1];
    m_femoralLateralDistalCondylePoint[2] = FLDCvalues[2];

    QVector<double> FMDCvalues = dataHash.value("Femoral Medial Distal Condyle");
    m_femoralMedialDistalCondylePoint[0] = FMDCvalues[0];
    m_femoralMedialDistalCondylePoint[1] = FMDCvalues[1];
    m_femoralMedialDistalCondylePoint[2] = FMDCvalues[2];


    //-----------------------TIBIA------------------------------------------------------
    //*************Tibial plateau line********************
    QVector<double> LPalues = dataHash.value("Tibial Lateral Plateau");
    m_TPL_P1[0] = LPalues[0];
    m_TPL_P1[1] = LPalues[1];
    m_TPL_P1[2] = LPalues[2];

    QVector<double> MPalues = dataHash.value("Tibial Medial Plateau");
    m_TPL_P2[0]  = MPalues[0];
    m_TPL_P2[1]  = MPalues[1];
    m_TPL_P2[2]  = MPalues[2];

    //*************Anotomical point tibia*************
    m_TibialLateralPlateauPoint[0] = LPalues[0];
    m_TibialLateralPlateauPoint[1] = LPalues[1];
    m_TibialLateralPlateauPoint[2] = LPalues[2];

    m_TibialMedialPlateauPoint[0] = MPalues[0];
    m_TibialMedialPlateauPoint[1] = MPalues[1];
    m_TibialMedialPlateauPoint[2] = MPalues[2];

    //*************Tibial mechanical axis********************
    QVector<double> TKneecnetre = dataHash.value("Tibial Knee Centre");
    m_TibialMechanicalAxis_P1[0] = TKneecnetre[0];
    m_TibialMechanicalAxis_P1[1] = TKneecnetre[1];
    m_TibialMechanicalAxis_P1[2] = TKneecnetre[2];

    QVector<double> tibLatMall = dataHash.value("Tibial Lateral Malleolus");
    QVector<double> tibMedMall = dataHash.value("Tibial Medial Malleolus");
    QVector<double> ankle_center(3);  // To store the mean of the two points

    // Calculate the mean for each coordinate
    for (int i = 0; i < 3; ++i) {
        ankle_center[i] = (tibLatMall[i] + tibMedMall[i]) / 2.0;
    }
    m_TibialMechanicalAxis_P2[0] =  ankle_center[0];
    m_TibialMechanicalAxis_P2[1] =  ankle_center[1];
    m_TibialMechanicalAxis_P2[2] =  ankle_center[2];
}

void KinematicsClass::ReadJsonFromKinematicsModule(QString femurjsonpath, QString tibiajsonpath)
{

    qDebug() << " Reading kinematics module json file = " << femurjsonpath<<tibiajsonpath;
    //**********Reading Femur json file**********
    QFile file_femur(femurjsonpath);
    if (!file_femur.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file.";
    }

    //Read the file content
    QByteArray fileContent_femur = file_femur.readAll();
    file_femur.close();

    // Parse the JSON data
    QJsonDocument jsonDoc_femur = QJsonDocument::fromJson(fileContent_femur);

    // Check if the document is valid
    if (jsonDoc_femur.isNull() || !jsonDoc_femur.isObject()) {
        qWarning() << "Invalid JSON data.";
    }

    // Convert the document into a JSON object
    QJsonObject jsonObj_Femur = jsonDoc_femur.object();


    Femur_valgusVarusAngle = jsonObj_Femur.value("Valgus/Varus angle").toString();
    QString numericPartvalgusVarusAngle = Femur_valgusVarusAngle.split(" ").first();// Extract the numeric part (first part before space)
    Femur_valgusVarusAngle = QString::number(numericPartvalgusVarusAngle.toDouble(), 'f', 2) +  "°"; // Format the number to 2 decimal places

    Femur_internalExternalRotationAngle = jsonObj_Femur.value("Internal/External rotation angle").toString();
    QString numericPartExternalRotationAngle = Femur_internalExternalRotationAngle.split(" ").first();// Extract the numeric part (first part before space)
    Femur_internalExternalRotationAngle = QString::number(numericPartExternalRotationAngle.toDouble(), 'f', 2) +  "°"; // Format the number to 2 decimal places

    Femur_flexionExtensionAngle = jsonObj_Femur.value("Flexion/Extension angle").toString();
    QString numericPartflexionExtensionAngle = Femur_flexionExtensionAngle.split(" ").first();// Extract the numeric part (first part before space)
    Femur_flexionExtensionAngle = QString::number(numericPartflexionExtensionAngle.toDouble(), 'f', 2) +  "°"; // Format the number to 2 decimal places


    Femur_lateralDistalResectionDepth = QString::number(jsonObj_Femur.value("Lateral distal resection depth").toDouble(),'f', 2);
    Femur_medialDistalResectionDepth = QString::number(jsonObj_Femur.value("Medial distal resection depth").toDouble(),'f', 2);
    Femur_lateralPosteriorResectionDepth = QString::number(jsonObj_Femur.value("Lateral posterior resection depth").toDouble(),'f', 2);
    Femur_medialPosteriorResectionDepth = QString::number(jsonObj_Femur.value("Medial posterior resection depth").toDouble(),'f', 2);

    // Print or use the values
    qDebug() <<endl<<"-----FEMUR-----";
    qDebug() << "Valgus/Varus angle:" << Femur_valgusVarusAngle;
    qDebug() << "Internal/External rotation angle:" << Femur_internalExternalRotationAngle;
    qDebug() << "Flexion/Extension angle:" << Femur_flexionExtensionAngle;
    qDebug() << "Lateral distal resection depth:" << Femur_lateralDistalResectionDepth;
    qDebug() << "Medial distal resection depth:" << Femur_medialDistalResectionDepth;
    qDebug() << "Lateral posterior resection depth:" << Femur_lateralPosteriorResectionDepth;
    qDebug() << "Medial posterior resection depth:" << Femur_medialPosteriorResectionDepth;



    //**********Reading Tibia json file**********
    QFile file_tibia(tibiajsonpath);
    if (!file_tibia.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Failed to open file.";
    }

    //Read the file content
    QByteArray fileContent_tibia = file_tibia.readAll();
    file_tibia.close();

    // Parse the JSON data
    QJsonDocument jsonDoc_tibia = QJsonDocument::fromJson(fileContent_tibia);

    // Check if the document is valid
    if (jsonDoc_tibia.isNull() || !jsonDoc_tibia.isObject()) {
        qWarning() << "Invalid JSON data.";
    }

    // Convert the document into a JSON object
    QJsonObject jsonObj_tibia = jsonDoc_tibia.object();

    // Extract the values and store them in QStrings
    Tibia_valgusVarusAngle = jsonObj_tibia.value("Valgus/Varus angle").toString();
    QString numericPartTibia_valgusVarusAngle= Tibia_valgusVarusAngle.split(" ").first();// Extract the numeric part (first part before space)
    Tibia_valgusVarusAngle = QString::number(numericPartTibia_valgusVarusAngle.toDouble(), 'f', 2) +  "°"; // Format the number to 2 decimal places

    Tibia_internalExternalRotationAngle = jsonObj_tibia.value("Internal/External rotation angle").toString();
    QString numericPartTibia_intExtRotAng = Tibia_internalExternalRotationAngle.split(" ").first();// Extract the numeric part (first part before space)
    Tibia_internalExternalRotationAngle = QString::number(numericPartTibia_intExtRotAng.toDouble(), 'f', 2) +  "°"; // Format the number to 2 decimal places


    Tibia_Posteriorslope = jsonObj_tibia.value("Posterior slope").toString();
    double number = Tibia_Posteriorslope.toDouble();
    Tibia_Posteriorslope = QString::number(number, 'f', 2) + "°";

    Tibia_lateralProximalResectionDepth = QString::number(jsonObj_tibia.value("Lateral proximal resection depth").toDouble(),'f', 2);
    Tibia_medialProximalResectionDepth = QString::number(jsonObj_tibia.value("Medial proximal resection depth").toDouble(),'f', 2);


    // Print or use the values
    qDebug() <<endl<<"-----TIBIA-----";
    qDebug() << "Valgus/Varus angle:" << Tibia_valgusVarusAngle;
    qDebug() << "Internal/External rotation angle:" << Tibia_internalExternalRotationAngle;
    qDebug() << "Posterior slope:" << Tibia_Posteriorslope;
    qDebug() << "Lateral proximal resection depth:" << Tibia_lateralProximalResectionDepth;
    qDebug() << "Medial proximal resection depth:" << Tibia_medialProximalResectionDepth;


}
