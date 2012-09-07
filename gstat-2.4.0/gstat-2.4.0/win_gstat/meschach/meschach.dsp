# Microsoft Developer Studio Project File - Name="meschach" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=meschach - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "meschach.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "meschach.mak" CFG="meschach - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "meschach - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "meschach - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "meschach - Win32 Release"

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
# ADD LIB32 /nologo /out:"..\..\lib\meschach.lib"

!ELSEIF  "$(CFG)" == "meschach - Win32 Debug"

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
# ADD LIB32 /nologo /out:"..\..\lib\meschach.lib"

!ENDIF 

# Begin Target

# Name "meschach - Win32 Release"
# Name "meschach - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\meschach\chfactor.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\copy.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\err.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\hsehldr.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\init.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\ivecop.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\lufactor.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\machine.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\matop.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\matrixio.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\meminfo.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\memory.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\memstat.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\norm.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\otherio.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\pxop.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\qrfactor.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\solve.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\sparse.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\sparseio.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\spbkp.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\spchfctr.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\splufctr.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\sprow.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\spswap.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\submat.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\vecop.c
# End Source File
# Begin Source File

SOURCE=..\..\meschach\version.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# End Target
# End Project
