# Microsoft Developer Studio Project File - Name="mfcSurfConsole" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=mfcSurfConsole - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mfcSurfConsole.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mfcSurfConsole.mak" CFG="mfcSurfConsole - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mfcSurfConsole - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "mfcSurfConsole - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mfcSurfConsole - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "mfcSurfConsole - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ    /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ    /c
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "mfcSurfConsole - Win32 Release"
# Name "mfcSurfConsole - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\mfcSurfConsole.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\mfcSurfConsole.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=..\bitmap_c.bmp
# End Source File
# Begin Source File

SOURCE=..\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=..\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=..\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=..\GENERIC.ICO
# End Source File
# Begin Source File

SOURCE=..\generic.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\ico00001.ico
# End Source File
# Begin Source File

SOURCE=..\icon1.ico
# End Source File
# Begin Source File

SOURCE=..\politic_map.bmp
# End Source File
# Begin Source File

SOURCE=..\psheetsm.ico
# End Source File
# End Group
# Begin Source File

SOURCE=..\palette\clrmap.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_autumn.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_bone.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_colorcube.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_cool.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_copper.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_flag.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_gray.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_hot.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_hsv.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_jet.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_lines.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_pink.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_prism.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_spring.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_summer.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_surfer.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_vga.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_white.dat
# End Source File
# Begin Source File

SOURCE=..\palette\colormap_winter.dat
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\topo.dat
# End Source File
# Begin Source File

SOURCE=..\palette\topomap1.dat
# End Source File
# Begin Source File

SOURCE=..\palette\topomap2.dat
# End Source File
# End Target
# End Project
