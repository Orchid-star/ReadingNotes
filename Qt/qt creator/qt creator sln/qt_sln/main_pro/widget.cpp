#include "widget.h"
#include "test_dll_a.h"
#include "test_dll_b.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    CTestDllA dll_a;
    //dll_a.echo_msg("dll_a");

    CTestDllB dll_b;
    connect(&dll_b, &CTestDllB::msg_sig, this, [&dll_a](QString msg){
        dll_a.echo_msg(msg);
    });

    dll_b.emit_msg("lai ba");
}

Widget::~Widget()
{
}

