#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T20:43:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = thread
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    qthreadread.cpp

HEADERS  += dialog.h \
    qthreadread.h

FORMS    += dialog.ui
