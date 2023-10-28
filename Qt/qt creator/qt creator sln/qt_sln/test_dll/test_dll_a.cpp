#include "test_dll_a.h"
#include <QDebug>

CTestDllA::CTestDllA()
{
}

void CTestDllA::echo_msg(QString msg)
{
    qDebug() << "msg from CTestDllA:" << msg;
}
