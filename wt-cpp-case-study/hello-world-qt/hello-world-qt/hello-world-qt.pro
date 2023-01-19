QT       += core
QT       -= gui

INCLUDEPATH  +=  C:\Users\povad_ad\AppData\Local\Programs\Wt\Wt_4_9_0_msvs2019_Windows_x64_SDK\include
LIBS         += -LC:\Users\povad_ad\AppData\Local\Programs\Wt\Wt_4_9_0_msvs2019_Windows_x64_SDK\lib 

win32 {
# For compiling with Qt Creator
# TEMPLATE     = app
# For compiling with Visual Studio
TEMPLATE      = vcapp
# RC_ICONS      = ./../../rec/logo.ico
}


DEPENDPATH   += .
DEFINES      += WIN32 HPDF_DLL QT_NO_KEYWORDS WT_NO_SLOT_MACROS
QMAKE_CXXFLAGS += -DNDEBUG
TARGET = hello-world-qt
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += debug_and_release


SOURCES +=  QtObject.cpp \
            hello.cpp \
            lib/WQApplication.cpp \
            lib/DispatchThread.cpp
HEADERS +=  QtObject.h \
            hello.h \
            lib/DispatchThread.h