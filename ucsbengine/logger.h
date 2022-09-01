#ifndef LOGGER_H
#define LOGGER_H
#include "UCSBEngine_global.h"
#include <QtCore/qglobal.h>
#include<QEventLoopLocker>
#include <QtNetwork/QNetworkAccessManager>
#include <QBoxLayout>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QUrl>
#include<QMessageBox>
#include<QProgressDialog>
#include<QJsonObject>
#include<QJsonDocument>
#include<QLabel>
// xiaorliu-start
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QMainWindow>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>
#include<QNetworkRequest>
#include<QNetworkReply>
#include<QUrl>
#include<QLabel>
#include<QProgressDialog>

class UCSBENGINE_EXPORT Logger
{
public:
    Logger();
    void info(QString clientName, QString content);
    void warn(QString clientName, QString content);
    void error(QString clientName, QString content);
    void critical(QString clientName, QString content);
private:
    void sendMessage(QString type, QString clientName, QString content);
};

#endif // LOGGER_H
