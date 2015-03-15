#-------------------------------------------------
#
# Project created by QtCreator 2015-03-12T20:54:42
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = csvImport
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qsampleclass.cpp \
    qcsvmodel.cpp \
    qdummyclass.cpp

HEADERS  += mainwindow.h \
    qsampleclass.h \
    qcsvmodel.h \
    qdummyclass.h

FORMS    += mainwindow.ui

DEFINES += WRITEABLE_OBJECT
