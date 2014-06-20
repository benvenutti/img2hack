#-------------------------------------------------
#
# Project created by QtCreator 2014-06-14T12:10:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = img2hack
TEMPLATE = app


SOURCES += main.cpp\
    view/mainwindow.cpp \
    view/aboutdialog.cpp \
    model/screenmap.cpp \
    model/writer.cpp

HEADERS  += \
    view/mainwindow.h \
    model/hack.h \
    view/aboutdialog.h \
    model/screenmap.h \
    model/writer.h

CONFIG += c++11

FORMS    += view/mainwindow.ui \
    view/aboutdialog.ui

INCLUDEPATH += . /usr/include/ImageMagick

LIBS += -L/usr/lib -lMagick++

RESOURCES += \
    images.qrc
