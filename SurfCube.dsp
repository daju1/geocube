# Microsoft Developer Studio Project File - Name="SurfCube" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SurfCube - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SurfCube.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SurfCube.mak" CFG="SurfCube - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SurfCube - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SurfCube - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SurfCube - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib comctl32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SurfCube - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SurfCube - Win32 Release"
# Name "SurfCube - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\abortPrint.cpp
# End Source File
# Begin Source File

SOURCE=.\BrokenPlane3D.cpp
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

SOURCE=.\interp.cpp
# End Source File
# Begin Source File

SOURCE=.\Line3D.cpp
# End Source File
# Begin Source File

SOURCE=.\memory_track.cpp
# End Source File
# Begin Source File

SOURCE=.\mtools.cpp
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

SOURCE=.\project.cpp
# End Source File
# Begin Source File

SOURCE=.\raporto.cpp
# End Source File
# Begin Source File

SOURCE=.\readfile.cpp
# End Source File
# Begin Source File

SOURCE=.\sorting.cpp
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

SOURCE=.\ThePoint3D.cpp
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

SOURCE=.\BrokenPlane3D.h
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

SOURCE=.\interp.h
# End Source File
# Begin Source File

SOURCE=.\Line3D.h
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

SOURCE=.\project.h
# End Source File
# Begin Source File

SOURCE=.\raporto.h
# End Source File
# Begin Source File

SOURCE=.\readfile.h
# End Source File
# Begin Source File

SOURCE=.\sorting.h
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

SOURCE=.\ThePoint3D.h
# End Source File
# Begin Source File

SOURCE=.\utility.h
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

SOURCE=.\GENERIC.ICO
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
