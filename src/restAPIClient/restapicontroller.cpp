#include "restapicontroller.h"

restAPIController::restAPIController(QObject *parent) : QObject(parent)
{
    m_objjsondatafetchworker= new jsonDataFetchWorker;
    workerThread = new QThread(this);
    m_objjsondatafetchworker->moveToThread(workerThread);
    connect(workerThread, &QThread::started, m_objjsondatafetchworker, &jsonDataFetchWorker::doWork);
}

void restAPIController::InitializedataFetchFromRestAPI()
{
//    QString url = "http://127.0.0.1:8081/CheckPoint?data={\"ToolMarker\":\"518\",\"ReferenceMarker\":\"81\",\"Type\":\"1\",\"StartDelay\":\"0\",\"Fiducialless\":true}";
//    m_objjsondatafetchOtherDetails= new jsondatafetchOtherDetails;
//    m_objjsondatafetchOtherDetails->sendRequestOther(url);





    workerThread->start();

}
