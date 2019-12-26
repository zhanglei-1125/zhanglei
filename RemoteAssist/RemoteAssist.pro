QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteAssist
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

SOURCES += \
        main.cpp \
        mainwindow.cpp\
    seekhelpwidget.cpp \
    helpotherswidget.cpp


HEADERS += \
    mainwindow.h \
    seekhelpwidget.h \
    helpotherswidget.h

RESOURCES += \
    remoteassist.qrc






