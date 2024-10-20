#include "widget.h"

#include <QApplication>

static const QString c_style = "CSwitch{"
                               "qproperty-bkg_checked_color:rgb(254,44,85);"
                               "qproperty-bkg_unchecked_color:gray;"
                               "qproperty-bkg_checked_disable_color:black;"
                               "qproperty-bkg_unchecked_disable_color:rgb(50,50,50);"
                               "qproperty-slider_color:white;"
                               "qproperty-slider_disable_color:rgb(100,100,100);"
                               "}";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyleSheet(c_style);
    Widget w;
    w.resize(250, 65);
    w.show();
    return a.exec();
}
