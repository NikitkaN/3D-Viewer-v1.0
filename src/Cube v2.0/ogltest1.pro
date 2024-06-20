QT       += core gui openglwidgets

QT += widgets

TARGET = ogltest1
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++17

SOURCES += \
        affine.c \
        main.cpp \
        mainwindow.cpp \
        oglwidget.cpp \
        parser.c

HEADERS += \
        affine.h \
        mainwindow.h \
        oglwidget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    models.qrc

win32-g* {
LIBS += -lopengl32
}

win32-msvc* {
LIBS += lopengl32.lib
}

FORMS += \
    mainwindow.ui

include (QtGif/gifimage/qtgifimage.pri)
