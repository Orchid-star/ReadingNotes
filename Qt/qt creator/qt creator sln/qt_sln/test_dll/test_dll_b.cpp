#include "test_dll_b.h"
#include <QDebug>

CTestDllB::CTestDllB(QObject *parent) : QObject(parent)
{

}

void CTestDllB::emit_msg(QString msg)
{
    emit msg_sig(msg);
    qDebug() << "msg_sig emitted";
}
