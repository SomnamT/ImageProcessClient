#ifndef LOCAL_CONFIG_H
#define LOCAL_CONFIG_H

#include <QtCore>

struct UcsbService {
    QString appId;
    QString serviceId;

    UcsbService(QString appId, QString serviceId) : appId(appId), serviceId(serviceId) {}
};

namespace Config {
    const auto imageDetectionService = UcsbService("2", "01-0001-02-cf57a680");
    const auto movieDetectionService = UcsbService("3", "01-0001-03-aabbccdd");
};
#endif
