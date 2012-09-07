# Microsoft Developer Studio Project File - Name="win_gstat" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=win_gstat - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "win_gstat.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "win_gstat.mak" CFG="win_gstat - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "win_gstat - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "win_gstat - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "win_gstat - Win32 Release"

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
# ADD CPP /nologo /W3 /GX /O2 /I "..\libcsf\include" /I "..\meschach" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x419 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libcsf.lib meschach.lib snprintf.lib /nologo /subsystem:console /machine:I386 /libpath:"..\lib"

!ELSEIF  "$(CFG)" == "win_gstat - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\libcsf\include" /I "..\meschach" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib libcsf.lib meschach.lib snprintf.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "win_gstat - Win32 Release"
# Name "win_gstat - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\src\block.c
# End Source File
# Begin Source File

SOURCE=..\src\data.c
# End Source File
# Begin Source File

SOURCE=..\src\direct.c
# End Source File
# Begin Source File

SOURCE=..\src\fig.c
# End Source File
# Begin Source File

SOURCE=..\src\fit.c
# End Source File
# Begin Source File

SOURCE=..\src\getest.c
# End Source File
# Begin Source File

SOURCE=..\src\getopt.c
# End Source File
# Begin Source File

SOURCE=..\src\gls.c
# End Source File
# Begin Source File

SOURCE=..\src\glvars.c
# End Source File
# Begin Source File

SOURCE=..\src\gstat.c
# End Source File
# Begin Source File

SOURCE=..\src\lex.c
# End Source File
# Begin Source File

SOURCE=..\src\lm.c
# End Source File
# Begin Source File

SOURCE=..\src\map2fig.c
# End Source File
# Begin Source File

SOURCE=..\src\map2gd.c
# End Source File
# Begin Source File

SOURCE=..\src\mapio.c
# End Source File
# Begin Source File

SOURCE=..\src\maputils.c
# End Source File
# Begin Source File

SOURCE=..\src\msim.c
# End Source File
# Begin Source File

SOURCE=..\src\nsearch.c
# End Source File
# Begin Source File

SOURCE=..\src\ossfim.c
# End Source File
# Begin Source File

SOURCE=..\src\palet.c
# End Source File
# Begin Source File

SOURCE=..\src\parse.c
# End Source File
# Begin Source File

SOURCE=..\src\plot.c
# End Source File
# Begin Source File

SOURCE=..\src\polygon.c
# End Source File
# Begin Source File

SOURCE=..\src\pqueue.c
# End Source File
# Begin Source File

SOURCE=..\src\predict.c
# End Source File
# Begin Source File

SOURCE=..\src\random.c
# End Source File
# Begin Source File

SOURCE=..\src\read.c
# End Source File
# Begin Source File

SOURCE=..\src\reml.c
# End Source File
# Begin Source File

SOURCE=..\src\report.c
# End Source File
# Begin Source File

SOURCE=..\src\sample.c
# End Source File
# Begin Source File

SOURCE=..\src\select.c
# End Source File
# Begin Source File

SOURCE=..\src\sem.c
# End Source File
# Begin Source File

SOURCE=..\src\sem_main.c
# End Source File
# Begin Source File

SOURCE=..\src\sim.c
# End Source File
# Begin Source File

SOURCE=..\src\stat.c
# End Source File
# Begin Source File

SOURCE=..\src\ui.c
# End Source File
# Begin Source File

SOURCE=..\src\userio.c
# End Source File
# Begin Source File

SOURCE=..\src\utils.c
# End Source File
# Begin Source File

SOURCE=..\src\vario.c
# End Source File
# Begin Source File

SOURCE=..\src\vario_fn.c
# End Source File
# Begin Source File

SOURCE=..\src\vario_io.c
# End Source File
# Begin Source File

SOURCE=..\src\writecmd.c
# End Source File
# Begin Source File

SOURCE=..\src\xvalid.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\src\config.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
