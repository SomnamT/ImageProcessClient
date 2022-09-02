#include "tempmanager.h"

TempManager::TempManager()
{

}

QString TempManager::remove_brace(const QString &input) {
    return input.mid(1, 36);
}

QString TempManager::get_response_tempfile() {

    QString str = "C:\\Users\\26286\\Desktop\\ImageProcess\\ipc_5_9\\image-processing-client\\tmp\\response-" + remove_brace(QUuid::createUuid().toString()) + ".tmp";
    //qDebug() << QDir::currentPath();
    return str;
}

QString TempManager::get_cv_tempfile() {
    //qDebug() << "FUCK";
    QString str = "C:\\Users\\26286\\Desktop\\ImageProcess\\ipc_5_9\\image-processing-client\\tmp\\cv-" + remove_brace(QUuid::createUuid().toString()) + ".tmp.png";

    return str;
}
