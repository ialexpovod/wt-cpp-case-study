# Author: Alex Povod 2023-01-19 10:36

win32{
# For compiling with Qt Creator
TEMPLATE     = app
# For compiling with Visual Studio
# TEMPLATE      = vcapp
# RC_ICONS      = ./../../rec/logo.ico
TARGET = hello-world-qt-pro

CONFIG -= app_bundle
}


linux-g++ {
TARGET = hello-world-qt-pro
CONFIG += c++14
}

CONFIG += console
CONFIG -= flat
# CONFIG += no_batch
CONFIG += debug_and_release

win32 {
include(./wtconfig_win32.pri)
}

linux-g++ {
include(./wtconfig_unix.pri)
}

QT += core
QT -= gui

# DEFINES      += QT_DLL QT_WEBKITWIDGETS_LIB QT_WIDGETS_LIB QT_XML_LIB
# DESTDIR       = ../../bin/
DESTDIR       = ./bin

# INCLUDEPATH  += ./wtwithqtlib          


SOURCES  += hello-world.cpp
HEADERSS += .

