#ifndef UCSBENGINE_GLOBAL_H
#define UCSBENGINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UCSBENGINE_LIBRARY)
#  define UCSBENGINE_EXPORT Q_DECL_EXPORT
#else
#  define UCSBENGINE_EXPORT Q_DECL_IMPORT
#endif

#endif // UCSBENGINE_GLOBAL_H
