#ifndef CTESTDLLB_H
#define CTESTDLLB_H

#include <QObject>
#include "test_dll_global.h"

class TEST_DLL_EXPORT CTestDllB : public QObject
{
    Q_OBJECT
public:
    explicit CTestDllB(QObject *parent = nullptr);
    void emit_msg(QString msg);
signals:
    void msg_sig(QString msg);
};

#endif // CTESTDLLB_H
