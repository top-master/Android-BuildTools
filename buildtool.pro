TEMPLATE = app
TARGET = builder

QT += core gui

INCLUDEPATH += $$PWD/src

SOURCES +=\
    src/main-builder.cpp \
    src/component/mainview.cpp \
    src/service/appbuildtool.cpp \
    src/feature/build-handler.cpp

HEADERS += \
    src/component/mainview.h \
    src/service/appbuildtool.h \
    src/feature/build-handler.h

FORMS += src/component/mainview.ui

RESOURCES += \
    assets/main.qrc
