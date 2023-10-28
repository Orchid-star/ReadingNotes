#ifndef CTESTDLLA_H
#define CTESTDLLA_H

#include "test_dll_global.h"
#include <QString>

class TEST_DLL_EXPORT CTestDllA
{
public:
    CTestDllA();

    void echo_msg(QString msg);
};

#endif // CTESTDLLA_H
