#-------------------------------------------------
#
# Project created by QtCreator 2016-05-16T19:27:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ManagerSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    mysql.cpp \
    person.cpp \
    record.cpp \
    assoc_person.cpp

HEADERS  += mainwindow.h \
    login.h \
    mysql.h \
    person.h \
    record.h \
    assoc_person.h

FORMS    += mainwindow.ui \
    login.ui

RESOURCES += \
    src.qrc
