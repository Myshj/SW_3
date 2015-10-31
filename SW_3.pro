#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T09:27:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SW_3
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    request.cpp \
    queuerecord.cpp \
    dispatcher.cpp \
    constants.cpp

HEADERS  += mainwindow.h \
    request.h \
    queuerecord.h \
    dispatcher.h \
    constants.h

FORMS    += mainwindow.ui
