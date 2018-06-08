#-------------------------------------------------
#
# Project created by QtCreator 2017-05-05T20:13:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/usr/local/lib -lsquirrel
LIBS += -L/usr/local/lib -lsqstdlib
QMAKE_CXXFLAGS += -std=c++11

TARGET = JusticeLemon
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    startscene.cpp \

HEADERS  += mainwindow.h \
    char.h \
    building.h \
    btn.h \
    enemy.h \
    startscene.h \
    walk.h \
    particle.h

FORMS    += mainwindow.ui

RESOURCES += \
    IMG/img.qrc

DISTFILES +=

