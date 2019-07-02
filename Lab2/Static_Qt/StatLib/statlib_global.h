#ifndef STATLIB_GLOBAL_H
#define STATLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(STATLIB_LIBRARY)
#  define STATLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define STATLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // STATLIB_GLOBAL_H
