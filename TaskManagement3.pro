TEMPLATE = app

QT += qml quick core

CONFIG += c++11

SOURCES += main.cpp \
    foo.cpp \
    rctask.cpp \
    rrtask.cpp \
    sctask.cpp \
    srtask.cpp \
    taskmanager.cpp \
    task.cpp \
    catagory.cpp \
    goalview.cpp \
    pane.cpp \
    taskcontainer.cpp \
    date.cpp \
    panemanager.cpp \
    settings.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    foo.h \
    rctask.h \
    rrtask.h \
    sctask.h \
    srtask.h \
    taskmanager.h \
    task.h \
    catagory.h \
    goalview.h \
    pane.h \
    taskcontainer.h \
    date.h \
    panemanager.h \
    settings.h

DISTFILES +=
