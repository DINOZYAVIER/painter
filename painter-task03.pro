QT += core gui widgets

CONFIG += c++11

TARGET = Painter
TEMPLATE = app

# Generate make file only for certain build type
CONFIG -= debug_and_release

# Set app version
REV = $$system(git rev-list --count HEAD)
BUILD_VERSION = 0.1.0.$$REV
VERSION = $$BUILD_VERSION

INCLUDEPATH += \
    $$PWD/sources/

SOURCES += \
    sources/customlabel.cpp \
    sources/main.cpp \
    sources/mainwindow.cpp

HEADERS += \
    sources/customlabel.h \
    sources/mainwindow.h \
    sources/precompiled.h

FORMS += \
    forms/mainwindow.ui

win32: PLATFORM = "windows"
linux: PLATFORM = "linux"
macx:  PLATFORM = "mac"

CONFIG( debug, debug|release ) {
    # Debug
    BUILD_CONFIG = "debug"
} else {
    # Release
    BUILD_CONFIG = "release"
}

DESTDIR = $$PWD/bin/$${PLATFORM}_$${BUILD_CONFIG}/

# Deployment
win32 {
    DEPLOY_TARGET = $$shell_quote($$DESTDIR/$${TARGET}.exe)
    DEPLOY_COMMAND = windeployqt --no-compiler-runtime --no-opengl-sw
    QMAKE_TARGET_COMPANY = NixSolutions LLC
    QMAKE_TARGET_PRODUCT = Painter App
    QMAKE_TARGET_DESCRIPTION = Painter App
    QMAKE_TARGET_COPYRIGHT = "NixSolutions LLC \\251 2020"
}

macx {
    DEPLOY_TARGET = $$shell_quote($$DESTDIR/$${TARGET}.app)
    DEPLOY_COMMAND = macdeployqt
}

win32|macx {
    # Generate release
    CONFIG(release, debug|release): QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
}

RESOURCES += \
    resources/resource.qrc
