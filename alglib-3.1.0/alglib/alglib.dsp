# Microsoft Developer Studio Project File - Name="alglib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=alglib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "alglib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "alglib.mak" CFG="alglib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "alglib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "alglib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "alglib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "alglib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "alglib - Win32 Release"
# Name "alglib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\cpp\src\alglibinternal.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\alglibmisc.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\ap.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\dataanalysis.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\diffequations.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\fasttransforms.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\integration.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\interpolation.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\linalg.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\optimization.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\solvers.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\specialfunctions.cpp
# End Source File
# Begin Source File

SOURCE=..\cpp\src\statistics.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\cpp\src\alglibinternal.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\alglibmisc.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\ap.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\dataanalysis.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\diffequations.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\fasttransforms.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\integration.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\interpolation.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\linalg.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\optimization.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\solvers.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\specialfunctions.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\statistics.h
# End Source File
# Begin Source File

SOURCE=..\cpp\src\stdafx.h
# End Source File
# End Group
# End Target
# End Project
