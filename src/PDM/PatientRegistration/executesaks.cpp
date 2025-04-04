#include "executesaks.h"

executeSAKS::executeSAKS(QObject *parent) : QObject(parent)
{

}


void executeSAKS::doSAKS()
{

    qDebug()<<" SAKS WORKER THREAD :: STARTED ";

    //            QString batFilePath = QDir::currentPath() + "/Segmentation_batfile/SAKS.bat";
    //            qDebug() << "QString batFilePath" << batFilePath;

    //            QStringList arguments;
    //            arguments << dcmPath;

    //            LPCWSTR operation = L"open";
    //            LPCWSTR file = reinterpret_cast<LPCWSTR>(batFilePath.utf16());
    //            LPCWSTR params = reinterpret_cast<LPCWSTR>(dcmPath.utf16());

    //            QString workingDirectory = QDir::currentPath() + "/Segmentation_batfile";
    //            LPCWSTR workingDir = reinterpret_cast<LPCWSTR>(workingDirectory.utf16());

    //            HINSTANCE result = ShellExecute(NULL, operation, file, params, workingDir, SW_HIDE);

    //            if ((int)result <= 32) {
    //                qDebug() << "Error: Failed to execute batch file. Error code:" << (int)result;
    //            } else {
    //                qDebug()<<" Executing ..";
    //            }



    /// using qprocess approach to run asynchronously
    QProcess process;
    QString batFilePath = QDir::currentPath() + "/Segmentation_batfile/SAKS.bat";
    QString workingDirectory = QDir::currentPath() + "/Segmentation_batfile";

    process.setWorkingDirectory(workingDirectory);

    // Start the batch file asynchronously
    process.start(batFilePath, QStringList() << dcmPath);

    if (!process.waitForStarted()) {
        qDebug() << "Error: Failed to start batch file.";
        return;
    }

    // Wait for the process to finish
    process.waitForFinished(-1);
    //    process.waitForFinished(5000);  // Waits for 5 seconds

    if (process.exitStatus() == QProcess::NormalExit) {
        qDebug() << "Batch file executed successfully.";
    } else {
        qDebug() << "Error: Batch file execution failed.";
    }

    /// done
    qDebug()<<" SAKS WORKER THREAD :: ENDED ";
}


void executeSAKS::slotdcmDir(QString st){

    qDebug()<<" SIGNAL RECIEVED :: Dicom path"<<st;

    dcmPath = st;
}
