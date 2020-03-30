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
    ../tools/src/errorexit.cpp \
    ../array/src/matrixes.cpp \
    ../src/mywindows.cpp \
    ../surfdoc/src/Grid.cpp \
    ../surfdoc/src/cube.cpp \
    ../array/src/fft.cpp \
    ../array/src/sorting.cpp \
    ../tools/src/readfile.cpp \
    ../array/src/korrelation.cpp \
    ../geometry2D/Node.cpp \
    ../array/src/wav.cpp \
    ../array/src/interp.cpp \
    ../geometry2D/VertexEx.cpp \
    ../geometry2D/Vertex.cpp \
    ../geometry2D/RandomizedSearchTree.cpp \
    ../geometry2D/RandomizedNode.cpp \
    ../geometry2D/PolygonEx.cpp \
    ../geometry2D/Polygon.cpp \
    ../geometry2D/Point.cpp \
    ../geometry2D/ListNode.cpp \
    ../geometry2D/List.cpp \
    ../geometry2D/Edge.cpp \
    ../geometry2D/delaunay.cpp \
    ../geometry2D/belong.cpp \
    ../array/src/Vector.cpp \
    ../surfdoc/src/AutoBuildProfileWnd.cpp \
    ../alglib-3.1.0/cpp/src/specialfunctions.cpp \
    ../alglib-3.1.0/cpp/src/alglibinternal.cpp \
    ../alglib-3.1.0/cpp/src/alglibmisc.cpp \
    ../alglib-3.1.0/cpp/src/ap.cpp \
    ../alglib-3.1.0/cpp/src/dataanalysis.cpp \
    ../alglib-3.1.0/cpp/src/diffequations.cpp \
    ../alglib-3.1.0/cpp/src/fasttransforms.cpp \
    ../alglib-3.1.0/cpp/src/integration.cpp \
    ../alglib-3.1.0/cpp/src/interpolation.cpp \
    ../alglib-3.1.0/cpp/src/linalg.cpp \
    ../alglib-3.1.0/cpp/src/optimization.cpp \
    ../alglib-3.1.0/cpp/src/solvers.cpp \
    ../alglib-3.1.0/cpp/src/statistics.cpp \
    ../array/src/LocalExtremumsFiltering.cpp

HEADERS  += auto_build_3d.h \
    ../tools/src/filedlg.h \
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
    ../array/src/stdafx.h \
    ../surfdoc/src/AFile.h \
    ../geometry2D/Node.h \
    ../geometry2D/belong.h \
    ../geometry2D/delaunay.h \
    ../geometry2D/Edge.h \
    ../geometry2D/List.h \
    ../geometry2D/ListNode.h \
    ../geometry2D/Point.h \
    ../geometry2D/Polygon.h \
    ../geometry2D/PolygonEx.h \
    ../geometry2D/RandomizedNode.h \
    ../geometry2D/RandomizedSearchTree.h \
    ../geometry2D/SearchTree.h \
    ../geometry2D/Vertex.h \
    ../geometry2D/VertexEx.h \
    ../surfdoc/src/Grid.h \
    ../surfdoc/src/Primitive3D.h \
    ../array/src/COMPLEX.H \
    ../array/src/LAGERFUN.H \
    ../array/src/SEQUENCE.H

FORMS    += auto_build_3d.ui

# INCLUDEPATH += "/usr/include/"

INCLUDEPATH += "./"
INCLUDEPATH += "./../include/"

INCLUDEPATH += "./../surfdoc/src/"
INCLUDEPATH += "./../laboratory/src/"
INCLUDEPATH += "./../array/src/"
INCLUDEPATH += "./../tools/src/"

QMAKE_CXXFLAGS += -DQT_PROJECT


