# Microsoft Developer Studio Project File - Name="libcsf" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libcsf - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libcsf.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libcsf.mak" CFG="libcsf - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libcsf - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libcsf - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libcsf - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\libcsf\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\libcsf.lib"

!ELSEIF  "$(CFG)" == "libcsf - Win32 Debug"

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
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\libcsf\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ  /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\lib\libcsf.lib"

!ENDIF 

# Begin Target

# Name "libcsf - Win32 Release"
# Name "libcsf - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\libcsf\src\_getcell.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\_getrow.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\_gsomece.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\_putcell.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\_rputrow.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\angle.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\attravai.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\attrsize.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\cellsize.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\create2.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\csfglob.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\csfsup.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\delattr.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\dumconv.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\endian.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\filename.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gattrblk.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gattridx.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gcellrep.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gdattype.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\getattr.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\getx0.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gety0.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\ggisfid.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gmaxval.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gminval.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gnrcols.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gnrrows.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gproj.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gputproj.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gvalscal.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gvartype.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\gversion.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\ismv.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\kernlcsf.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\legend.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\mclose.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\mopen.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\moreattr.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\mperror.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\pgisfid.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\pmaxval.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\pminval.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\putallmv.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\putattr.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\putsomec.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\putx0.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\puty0.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\pvalscal.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rattrblk.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rcomp.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rcoords.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rdup2.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\reseterr.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rextend.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rmalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\rrowcol.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\ruseas.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\setangle.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\setmv.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\setvtmv.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\strconst.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\strpad.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\swapio.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\trackmm.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\vs2.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\vsdef.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\vsis.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\vsvers.c
# End Source File
# Begin Source File

SOURCE=..\..\libcsf\src\wattrblk.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\libcsf\src\csfimpl.h
# End Source File
# End Group
# End Target
# End Project
