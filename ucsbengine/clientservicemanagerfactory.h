#ifndef CLIENTSERVICEMANAGERFACTORY_H
#define CLIENTSERVICEMANAGERFACTORY_H
#include "UCSBEngine_global.h"
#include <QtCore/qglobal.h>

#include"clientservicemanager.h"

class UCSBENGINE_EXPORT ClientServiceManagerFactory
{
public:
    static ClientServiceManagerFactory* GetInstance()
    {
         if ( instance == nullptr )
             instance = new ClientServiceManagerFactory();
         return instance;
    }
    static ClientServiceManagerFactory* instance;
    ClientServiceManagerFactory();
    ClientServiceManager* CreateClientServiceManager();
};

#endif // CLIENTSERVICEMANAGERFACTORY_H
