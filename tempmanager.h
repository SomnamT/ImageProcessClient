#ifndef TEMPMANAGER_H
#define TEMPMANAGER_H

#include <QtCore>

class TempManager
{
public:
    TempManager();

    static QString remove_brace(const QString &);
    static QString get_response_tempfile();
    static QString get_cv_tempfile();
};

#endif // TEMPMANAGER_H
