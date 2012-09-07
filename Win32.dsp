# Microsoft Developer Studio Project File - Name="Win32" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Win32 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Win32.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Win32.mak" CFG="Win32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Win32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "NDEBUG"
# ADD RSC /l 0x422 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"Release/tezeyvar.exe"

!ELSEIF  "$(CFG)" == "Win32 - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /EHsc /EHsc /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x422 /d "_DEBUG"
# ADD RSC /l 0x422 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib glaux.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/tezeyvar.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Win32 - Win32 Release"
# Name "Win32 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "Neuro Sources"

# PROP Default_Filter "cpp"
# Begin Group "Kohonen Sources"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\BrokenPlane3D.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonMeanFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\LayerKohonen.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\NetKohonen.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\NeuronKohonen.cpp
# End Source File
# Begin Source File

SOURCE=.\Object.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectList.cpp
# End Source File
# Begin Source File

SOURCE=.\Poligon3D.cpp
# End Source File
# Begin Source File

SOURCE=.\ThePoint3D.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\kohonen\Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\Net.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\Neuron.cpp
# End Source File
# End Group
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

SOURCE=.\BrokenLine3D.cpp
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

SOURCE=.\ComPort.cpp
# End Source File
# Begin Source File

SOURCE=.\conjgrad.cpp
# End Source File
# Begin Source File

SOURCE=.\datenum.cpp
# End Source File
# Begin Source File

SOURCE=.\dct\DelaunayTriangulation.cpp
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

SOURCE=.\FileFormat.cpp
# End Source File
# Begin Source File

SOURCE=.\generic.cpp
# End Source File
# Begin Source File

SOURCE=.\GLMan.cpp
# End Source File
# Begin Source File

SOURCE=.\GLPrintMan.cpp
# End Source File
# Begin Source File

SOURCE=.\Graph.cpp
# End Source File
# Begin Source File

SOURCE=.\Graph2.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\GraphsView.cpp
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

SOURCE=.\iso.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\KohonenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\kohonen\KohonenMapWnd.cpp
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

SOURCE=.\MessageItem.cpp
# End Source File
# Begin Source File

SOURCE=.\mtools.cpp
# End Source File
# Begin Source File

SOURCE=.\objects.cpp
# End Source File
# Begin Source File

SOURCE=.\palette.cpp
# End Source File
# Begin Source File

SOURCE=.\ParseTimeString.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyotyNnetDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Primitive3D.cpp
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

SOURCE=.\RoomQueueItem.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectLine.cpp
# End Source File
# Begin Source File

SOURCE=.\sorting.cpp
# End Source File
# Begin Source File

SOURCE=.\Sphere3D.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\String3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Surface3D.cpp
# End Source File
# Begin Source File

SOURCE=.\SurfDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\systemnnet.cpp
# End Source File
# Begin Source File

SOURCE=.\texture.cpp
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

SOURCE=.\vdouble.cpp
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

SOURCE=.\wingeoid.cpp
# End Source File
# Begin Source File

SOURCE=.\winmap.cpp
# End Source File
# Begin Source File

SOURCE=.\winplot.cpp
# End Source File
# Begin Source File

SOURCE=.\winsurf.cpp
# End Source File
# Begin Source File

SOURCE=.\winsurfproc.cpp
# End Source File
# Begin Source File

SOURCE=.\winsurftree.cpp
# End Source File
# Begin Source File

SOURCE=.\XYZBuffer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Neuro Headers"

# PROP Default_Filter "h"
# Begin Group "Kohonen Headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\BrokenPlane3D.h
# End Source File
# Begin Source File

SOURCE=.\CommonMeanFileDialog.h
# End Source File
# Begin Source File

SOURCE=.\Drill_3D.h
# End Source File
# Begin Source File

SOURCE=.\kohonen\LayerKohonen.h
# End Source File
# Begin Source File

SOURCE=.\kohonen\NetKohonen.h
# End Source File
# Begin Source File

SOURCE=.\kohonen\NeuronKohonen.h
# End Source File
# Begin Source File

SOURCE=.\Object.h
# End Source File
# Begin Source File

SOURCE=.\ObjectList.h
# End Source File
# Begin Source File

SOURCE=.\Poligon3D.h
# End Source File
# Begin Source File

SOURCE=.\PolyotyNnetDlg.h
# End Source File
# Begin Source File

SOURCE=.\ThePoint3D.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\kohonen\Layer.h
# End Source File
# Begin Source File

SOURCE=.\kohonen\Net.h
# End Source File
# Begin Source File

SOURCE=.\kohonen\Neuron.h
# End Source File
# End Group
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

SOURCE=.\BrokenLine3D.h
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

SOURCE=.\commonOG.h
# End Source File
# Begin Source File

SOURCE=.\ComPort.h
# End Source File
# Begin Source File

SOURCE=.\conjgrad.h
# End Source File
# Begin Source File

SOURCE=.\dct\DelaunayTriangulation.h
# End Source File
# Begin Source File

SOURCE=.\DPoint.h
# End Source File
# Begin Source File

SOURCE=.\DrawListArray.h
# End Source File
# Begin Source File

SOURCE=.\DrawScene.h
# End Source File
# Begin Source File

SOURCE=.\error.h
# End Source File
# Begin Source File

SOURCE=.\filedlg.h
# End Source File
# Begin Source File

SOURCE=.\FileFormat.h
# End Source File
# Begin Source File

SOURCE=.\generic.h
# End Source File
# Begin Source File

SOURCE=.\GLMan.h
# End Source File
# Begin Source File

SOURCE=.\GLPrintMan.h
# End Source File
# Begin Source File

SOURCE=.\Graph.h
# End Source File
# Begin Source File

SOURCE=.\Graph2.h
# End Source File
# Begin Source File

SOURCE=.\GraphsDoc.h
# End Source File
# Begin Source File

SOURCE=.\GraphsView.h
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

SOURCE=.\kohonen\KohonenDlg.h
# End Source File
# Begin Source File

SOURCE=.\kohonen\KohonenMapWnd.h
# End Source File
# Begin Source File

SOURCE=.\Line3D.h
# End Source File
# Begin Source File

SOURCE=.\listfun.h
# End Source File
# Begin Source File

SOURCE=.\matrixes.h
# End Source File
# Begin Source File

SOURCE=.\memory_track.h
# End Source File
# Begin Source File

SOURCE=.\MessageItem.h
# End Source File
# Begin Source File

SOURCE=.\mtools.h
# End Source File
# Begin Source File

SOURCE=.\objects.h
# End Source File
# Begin Source File

SOURCE=.\palette.h
# End Source File
# Begin Source File

SOURCE=.\ParseTimeString.h
# End Source File
# Begin Source File

SOURCE=.\Primitive3D.h
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

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\RoomQueueItem.h
# End Source File
# Begin Source File

SOURCE=.\SelectLine.h
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

SOURCE=.\systemnnet.h
# End Source File
# Begin Source File

SOURCE=.\texture.h
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

SOURCE=.\vdouble.h
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

SOURCE=.\winmap.h
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
# Begin Source File

SOURCE=.\XYZBuffer.h
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

SOURCE=.\generic.ico
# End Source File
# Begin Source File

SOURCE=.\generic.rc
# End Source File
# Begin Source File

SOURCE=.\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\politic_map.bmp
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

SOURCE=.\topomap1.dat
# End Source File
# Begin Source File

SOURCE=.\palette\topomap2.dat
# End Source File
# Begin Source File

SOURCE=.\topomap2.dat
# End Source File
# End Target
# End Project
