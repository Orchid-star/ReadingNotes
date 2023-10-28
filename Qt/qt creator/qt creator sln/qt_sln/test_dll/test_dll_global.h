#ifndef TEST_DLL_GLOBAL_H
#define TEST_DLL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TEST_DLL_LIBRARY)
#  define TEST_DLL_EXPORT Q_DECL_EXPORT
#else
#  define TEST_DLL_EXPORT Q_DECL_IMPORT
#endif

#endif // TEST_DLL_GLOBAL_H
