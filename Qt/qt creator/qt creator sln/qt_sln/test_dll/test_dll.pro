QT -= gui

TEMPLATE = lib
DEFINES += TEST_DLL_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    test_dll_a.cpp \
    test_dll_b.cpp

HEADERS += \
    test_dll_b.h \
    test_dll_global.h \
    test_dll_a.h

TARGET = test_mydll
DESTDIR = '$$PWD/lib'

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

copy1.path = '$$PWD/../main_pro/includes'
copy1.files += \
    test_dll_b.h \
    test_dll_global.h \
    test_dll_a.h

copy2.path = '$$PWD/../Win32'
copy2.files += '$$PWD/lib/test_mydll.dll'
INSTALLS += copy1 copy2
