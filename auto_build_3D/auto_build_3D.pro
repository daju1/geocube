#-------------------------------------------------
#
# Project created by QtCreator 2020-02-19T11:50:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = auto_build_3D
TEMPLATE = app


SOURCES += main.cpp\
        auto_build_3d.cpp \
    ./../surfdoc/src/AutoProfileBuilding.cpp \
    ../surfdoc/src/AutoBuildProfileDlg.cpp

HEADERS  += auto_build_3d.h \
    ./../surfdoc/src/AutoProfileBuilding.h \
    picks_search.h \
    ../surfdoc/src/AutoBuildProfileDlg.h \
    ../include/mywindows.h

FORMS    += auto_build_3d.ui

# INCLUDEPATH += "/usr/include/"

INCLUDEPATH += "./"
INCLUDEPATH += "./../include/"

INCLUDEPATH += "./../surfdoc/src/"
INCLUDEPATH += "./../laboratory/src/"
INCLUDEPATH += "./../array/src/"
INCLUDEPATH += "./../tools/src/"


