#include "widget.h"

#include "checkbox.h"
#include "switch.h"
#include <QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *p_layout = new QHBoxLayout(this);
    CSwitch *p_check1 = new CSwitch;
    p_layout->addWidget(p_check1);

    CSwitch *p_check2 = new CSwitch;
    p_check2->set_checked(true);
    p_layout->addWidget(p_check2);

    CSwitch *p_check3 = new CSwitch;
    p_check3->setEnabled(false);
    p_layout->addWidget(p_check3);

    CSwitch *p_check4 = new CSwitch;
    p_check4->set_checked(true);
    p_check4->setEnabled(false);
    p_layout->addWidget(p_check4);
}

Widget::~Widget()
{
}

