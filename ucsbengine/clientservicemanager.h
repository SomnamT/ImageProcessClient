#ifndef CLIENTSERVICEMANAGER_H
#define CLIENTSERVICEMANAGER_H
#include "UCSBEngine_global.h"
#include <QtCore/qglobal.h>

class UCSBENGINE_EXPORT ClientServiceManager
{
public:
    ClientServiceManager();
    QString CallService(QString app_id, QString service_id,  QString input, QString output);

private:
    QString getServiceAddress(QString app_id, QString service_id);
    QString sendMessage(QString address, QString input, QString output);
};

#endif // CLIENTSERVICEMANAGER_H
