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
    ../surfdoc/src/AutoBuildProfileDlg.cpp \
    ../surfdoc/src/Archive.cpp \
    ../array/src/Vdouble.cpp \
    ../array/src/slau.cpp \
    ../surfdoc/src/AFile.cpp \
    ../tools/src/filedlg_qt.cpp \
    ../tools/src/errorexit.cpp

HEADERS  += auto_build_3d.h \
    ./../surfdoc/src/AutoProfileBuilding.h \
    picks_search.h \
    ../surfdoc/src/AutoBuildProfileDlg.h \
    ../include/mywindows.h \
    ../array/src/Vdouble.h \
    ../array/src/vect.h \
    ../array/src/Vector.h \
    ../array/src/VectItem.h \
    ../array/src/wav.h \
    ../geometry2D/BraidedNode.h \
    ../array/src/slau.h \
    ../geometry2D/TreeNode.h \
    ../geometry2D/BraidedSearchTree.h \
    ../surfdoc/src/Archive.h \
    ../array/src/sparse_row.h \
    ../array/src/sparse_row_element.h \
    ../array/src/sparse_row_simple.h \
    ../array/src/sparse_row_map.h \
    ../array/src/interp.h \
    ../array/src/ap.h \
    ../array/src/stdafx.h

FORMS    += auto_build_3d.ui

# INCLUDEPATH += "/usr/include/"

INCLUDEPATH += "./"
INCLUDEPATH += "./../include/"

INCLUDEPATH += "./../surfdoc/src/"
INCLUDEPATH += "./../laboratory/src/"
INCLUDEPATH += "./../array/src/"
INCLUDEPATH += "./../tools/src/"


