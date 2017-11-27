#-------------------------------------------------
#
# Project created by QtCreator 2017-03-21T19:24:41
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Network
TEMPLATE = app


SOURCES += main.cpp\
    login.cpp \
    registerpage.cpp \
    showresultpage.cpp \
    chatpage.cpp \
    setuppage.cpp \
    addfriend.cpp

HEADERS  += \
    login.h \
    registerpage.h \
    showresultpage.h \
    chatpage.h \
    setuppage.h \
    addfriend.h

FORMS    += \
    login.ui \
    registerpage.ui \
    showresultpage.ui \
    chatpage.ui \
    setuppage.ui \
    addfriend.ui
