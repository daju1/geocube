# Microsoft Developer Studio Project File - Name="SurfConsole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=SurfConsole - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SurfConsole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SurfConsole.mak" CFG="SurfConsole - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SurfConsole - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "SurfConsole - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SurfConsole - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /c
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib comctl32.lib jpeg.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "SurfConsole - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib comctl32.lib jpeg.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SurfConsole - Win32 Release"
# Name "SurfConsole - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\abortPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\BlnProfile3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BlnProfilePlane3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Bmp3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpProfile3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BrokenLine3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BrokenPlane3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BrokenPoligon3D.cpp
# End Source File
# Begin Source File

SOURCE=.\BrokenPoligon_3D.cpp
# End Source File
# Begin Source File

SOURCE=.\camera.cpp
# End Source File
# Begin Source File

SOURCE=.\checkListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\colormap.cpp
# End Source File
# Begin Source File

SOURCE=.\conjgrad.cpp
# End Source File
# Begin Source File

SOURCE=.\dct\DelaunayTriangulation.cpp
# End Source File
# Begin Source File

SOURCE=.\distance3d.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddingGeoCube.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawListArray.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawScene.cpp
# End Source File
# Begin Source File

SOURCE=.\Drill_3D.cpp
# End Source File
# Begin Source File

SOURCE=.\error.cpp
# End Source File
# Begin Source File

SOURCE=.\filedlg.cpp
# End Source File
# Begin Source File

SOURCE=.\generic.rc
# End Source File
# Begin Source File

SOURCE=.\GLMan.cpp
# End Source File
# Begin Source File

SOURCE=.\GLPrintMan.cpp
# End Source File
# Begin Source File

SOURCE=.\Graph2.cpp
# End Source File
# Begin Source File

SOURCE=.\Grid.cpp
# End Source File
# Begin Source File

SOURCE=.\GridProfile3D.cpp
# End Source File
# Begin Source File

SOURCE=.\interp.cpp
# End Source File
# Begin Source File

SOURCE=.\InterWellsLine3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Line3D.cpp
# End Source File
# Begin Source File

SOURCE=.\listfun.cpp
# End Source File
# Begin Source File

SOURCE=.\matrixes.cpp
# End Source File
# Begin Source File

SOURCE=.\memory_track.cpp
# End Source File
# Begin Source File

SOURCE=.\mtools.cpp
# End Source File
# Begin Source File

SOURCE=.\mylicense.cpp
# End Source File
# Begin Source File

SOURCE=.\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectList.cpp
# End Source File
# Begin Source File

SOURCE=.\objects.cpp
# End Source File
# Begin Source File

SOURCE=.\palette.cpp
# End Source File
# Begin Source File

SOURCE=.\Poligon3D.cpp
# End Source File
# Begin Source File

SOURCE=.\print.cpp
# End Source File
# Begin Source File

SOURCE=.\PrintDlgBox.cpp
# End Source File
# Begin Source File

SOURCE=.\project.cpp
# End Source File
# Begin Source File

SOURCE=.\raporto.cpp
# End Source File
# Begin Source File

SOURCE=.\readfile.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectLine.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPodTypyGr.cpp
# End Source File
# Begin Source File

SOURCE=.\sorting.cpp
# End Source File
# Begin Source File

SOURCE=.\Sphere3D.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\String3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Surface3D.cpp
# End Source File
# Begin Source File

SOURCE=.\SurfCube.cpp
# End Source File
# Begin Source File

SOURCE=.\SurfDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\tabfun
# End Source File
# Begin Source File

SOURCE=.\texture.cpp
# End Source File
# Begin Source File

SOURCE=.\tga.cpp
# End Source File
# Begin Source File

SOURCE=.\ThePoint3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Triangle3D.cpp
# End Source File
# Begin Source File

SOURCE=.\TriangulatedGrid3D.cpp
# End Source File
# Begin Source File

SOURCE=.\utility.cpp
# End Source File
# Begin Source File

SOURCE=.\Vdouble.cpp
# End Source File
# Begin Source File

SOURCE=.\vect.cpp
# End Source File
# Begin Source File

SOURCE=.\VectItem.cpp
# End Source File
# Begin Source File

SOURCE=.\Vector.cpp
# End Source File
# Begin Source File

SOURCE=.\views.cpp
# End Source File
# Begin Source File

SOURCE=.\wav.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_app.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_graphics_view.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_plot_views.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_project.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_project_view.cpp
# End Source File
# Begin Source File

SOURCE=.\win32_views.cpp
# End Source File
# Begin Source File

SOURCE=.\Wingeoid.cpp
# End Source File
# Begin Source File

SOURCE=.\winplot.cpp
# End Source File
# Begin Source File

SOURCE=.\Winsurf.cpp
# End Source File
# Begin Source File

SOURCE=.\winsurfproc.cpp
# End Source File
# Begin Source File

SOURCE=.\winsurftree.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\abortPrint.h
# End Source File
# Begin Source File

SOURCE=.\BlnProfile3D.h
# End Source File
# Begin Source File

SOURCE=.\BlnProfilePlane3D.h
# End Source File
# Begin Source File

SOURCE=.\Bmp3D.h
# End Source File
# Begin Source File

SOURCE=.\BmpProfile3D.h
# End Source File
# Begin Source File

SOURCE=.\BrokenLine3D.h
# End Source File
# Begin Source File

SOURCE=.\BrokenPlane3D.h
# End Source File
# Begin Source File

SOURCE=.\BrokenPoligon3D.h
# End Source File
# Begin Source File

SOURCE=.\BrokenPoligon_3D.h
# End Source File
# Begin Source File

SOURCE=.\camera.h
# End Source File
# Begin Source File

SOURCE=.\checkListBox.h
# End Source File
# Begin Source File

SOURCE=.\colormap.h
# End Source File
# Begin Source File

SOURCE=.\conjgrad.h
# End Source File
# Begin Source File

SOURCE=.\dct\DelaunayTriangulation.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddingGeoCube.h
# End Source File
# Begin Source File

SOURCE=.\DrawListArray.h
# End Source File
# Begin Source File

SOURCE=.\DrawScene.h
# End Source File
# Begin Source File

SOURCE=.\Drill_3D.h
# End Source File
# Begin Source File

SOURCE=.\error.h
# End Source File
# Begin Source File

SOURCE=.\filedlg.h
# End Source File
# Begin Source File

SOURCE=.\GLMan.h
# End Source File
# Begin Source File

SOURCE=.\GLPrintMan.h
# End Source File
# Begin Source File

SOURCE=.\Graph2.h
# End Source File
# Begin Source File

SOURCE=.\Grid.h
# End Source File
# Begin Source File

SOURCE=.\GridProfile3D.h
# End Source File
# Begin Source File

SOURCE=.\interp.h
# End Source File
# Begin Source File

SOURCE=.\InterWellsLine3D.h
# End Source File
# Begin Source File

SOURCE=.\Line3D.h
# End Source File
# Begin Source File

SOURCE=.\listfun.h
# End Source File
# Begin Source File

SOURCE=.\memory_track.h
# End Source File
# Begin Source File

SOURCE=.\mtools.h
# End Source File
# Begin Source File

SOURCE=.\Object.h
# End Source File
# Begin Source File

SOURCE=.\ObjectList.h
# End Source File
# Begin Source File

SOURCE=.\objects.h
# End Source File
# Begin Source File

SOURCE=.\palette.h
# End Source File
# Begin Source File

SOURCE=.\Poligon3D.h
# End Source File
# Begin Source File

SOURCE=.\print.h
# End Source File
# Begin Source File

SOURCE=.\PrintDlgBox.h
# End Source File
# Begin Source File

SOURCE=.\project.h
# End Source File
# Begin Source File

SOURCE=.\raporto.h
# End Source File
# Begin Source File

SOURCE=.\readfile.h
# End Source File
# Begin Source File

SOURCE=.\SelectLine.h
# End Source File
# Begin Source File

SOURCE=.\SetPodTypyGr.h
# End Source File
# Begin Source File

SOURCE=.\sorting.h
# End Source File
# Begin Source File

SOURCE=.\Sphere3D.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\String3D.h
# End Source File
# Begin Source File

SOURCE=.\Surface3D.h
# End Source File
# Begin Source File

SOURCE=.\SurfDoc.h
# End Source File
# Begin Source File

SOURCE=.\tabfun.h
# End Source File
# Begin Source File

SOURCE=.\texture.h
# End Source File
# Begin Source File

SOURCE=.\tga.h
# End Source File
# Begin Source File

SOURCE=.\ThePoint3D.h
# End Source File
# Begin Source File

SOURCE=.\Triangle3D.h
# End Source File
# Begin Source File

SOURCE=.\TriangulatedGrid3D.h
# End Source File
# Begin Source File

SOURCE=.\utility.h
# End Source File
# Begin Source File

SOURCE=.\v3d.h
# End Source File
# Begin Source File

SOURCE=.\Vdouble.h
# End Source File
# Begin Source File

SOURCE=.\vect.h
# End Source File
# Begin Source File

SOURCE=.\VectItem.h
# End Source File
# Begin Source File

SOURCE=.\Vector.h
# End Source File
# Begin Source File

SOURCE=.\views.h
# End Source File
# Begin Source File

SOURCE=.\wav.h
# End Source File
# Begin Source File

SOURCE=.\win32_app.h
# End Source File
# Begin Source File

SOURCE=.\win32_dialog.h
# End Source File
# Begin Source File

SOURCE=.\win32_graphics_view.h
# End Source File
# Begin Source File

SOURCE=.\win32_plot_views.h
# End Source File
# Begin Source File

SOURCE=.\win32_project.h
# End Source File
# Begin Source File

SOURCE=.\win32_project_view.h
# End Source File
# Begin Source File

SOURCE=.\win32_views.h
# End Source File
# Begin Source File

SOURCE=.\wingeoid.h
# End Source File
# Begin Source File

SOURCE=.\winplot.h
# End Source File
# Begin Source File

SOURCE=.\winsurf.h
# End Source File
# Begin Source File

SOURCE=.\winsurfproc.h
# End Source File
# Begin Source File

SOURCE=.\winsurftree.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\bitmap_c.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\geoid\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\GENERIC.ICO
# End Source File
# Begin Source File

SOURCE=.\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\psheetsm.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\palette\clrmap.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_autumn.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_bone.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_colorcube.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_cool.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_copper.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_flag.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_gray.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_hot.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_hsv.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_jet.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_lines.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_pink.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_prism.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_spring.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_summer.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_surfer.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_vga.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_white.dat
# End Source File
# Begin Source File

SOURCE=.\palette\colormap_winter.dat
# End Source File
# Begin Source File

SOURCE=.\topo.dat
# End Source File
# Begin Source File

SOURCE=.\palette\topomap1.dat
# End Source File
# Begin Source File

SOURCE=.\palette\topomap2.dat
# End Source File
# End Target
# End Project
