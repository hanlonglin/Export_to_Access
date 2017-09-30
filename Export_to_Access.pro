#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T10:13:52
#
#-------------------------------------------------

QT       += core gui
QT       += sql
RC_ICONS = access.ico

VERSION = 1.0.0.4

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Export_to_Access
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    configwindow.cpp \
    databasetools.cpp \
    log.cpp

HEADERS  += mainwindow.h \
    config.h \
    configwindow.h \
    databasetools.h \
    log.h

FORMS    += mainwindow.ui \
    configwindow.ui
