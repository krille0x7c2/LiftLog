#-------------------------------------------------
#
# Project created by QtCreator 2017-01-04T07:54:08
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Liftlog
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dbmanager.cpp \
    fitnesscalculator.cpp \
    lift.cpp \
    chartview.cpp \
    chart.cpp

HEADERS  += mainwindow.h \
    dbmanager.h \
    fitnesscalculator.h \
    lift.h \
    chartview.h \
    chart.h

FORMS    += mainwindow.ui

RESOURCES += \
    database.qrc
