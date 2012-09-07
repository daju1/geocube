# Microsoft Developer Studio Project File - Name="lab" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=lab - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lab.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lab.mak" CFG="lab - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lab - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "lab - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "lab - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 excel_connect.lib /nologo /subsystem:windows /machine:I386 /libpath:"../lib" /libpath:"../../lib"

!ELSEIF  "$(CFG)" == "lab - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x419 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 excel_connect.lib tools.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../../lib"

!ENDIF 

# Begin Target

# Name "lab - Win32 Release"
# Name "lab - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3DDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\3DFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\3DView.cpp
# End Source File
# Begin Source File

SOURCE=.\AreometrGranular.cpp
# End Source File
# Begin Source File

SOURCE=.\AreometrGranularExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ComboProbGrKT.cpp
# End Source File
# Begin Source File

SOURCE=.\CompressionExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\DaoSetGeoObjects.cpp
# End Source File
# Begin Source File

SOURCE=.\DataBaseTalblesList.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTable.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableCilce.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableCompress.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableGranular.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableGrunty.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableIGE.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableKT.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableLito.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTablePalja.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableProp.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTablePtPalja.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTablePtStZond.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableSoils.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableStZond.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableZriz.cpp
# End Source File
# Begin Source File

SOURCE=.\DBTableZriz_tbl.cpp
# End Source File
# Begin Source File

SOURCE=.\DBViewList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCopyGrunty.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIGEList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLabElements.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLanguage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNaborGruntovSetting.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNRows.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPalja.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPCK2Fiz.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProbGr_DblClickMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgProbGrunt.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatings.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSoilName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgStatZond.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZondUstParam.cpp
# End Source File
# Begin Source File

SOURCE=.\EnGeoFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\EnGeoListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\EnGeologyDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\EnGeologyView.cpp
# End Source File
# Begin Source File

SOURCE=.\EnGeoObjectsList.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcelColChar.cpp
# End Source File
# Begin Source File

SOURCE=.\ExcelKTList.cpp
# End Source File
# Begin Source File

SOURCE=.\GranularList.cpp
# End Source File
# Begin Source File

SOURCE=.\GranularListLab.cpp
# End Source File
# Begin Source File

SOURCE=.\KTLabList.cpp
# End Source File
# Begin Source File

SOURCE=.\KTListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\KtSet.cpp
# End Source File
# Begin Source File

SOURCE=.\lab.cpp
# End Source File
# Begin Source File

SOURCE=.\hlp\lab.hpj

!IF  "$(CFG)" == "lab - Win32 Release"

# PROP Ignore_Default_Tool 1
USERDEP__LAB_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Release
TargetName=lab
InputPath=.\hlp\lab.hpj
InputName=lab

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "lab - Win32 Debug"

# PROP Ignore_Default_Tool 1
USERDEP__LAB_H="hlp\AfxCore.rtf"	"hlp\AfxPrint.rtf"	"hlp\$(TargetName).hm"	
# Begin Custom Build - Making help file...
OutDir=.\Debug
TargetName=lab
InputPath=.\hlp\lab.hpj
InputName=lab

"$(OutDir)\$(InputName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /wait hcw /C /E /M "hlp\$(InputName).hpj" 
	if errorlevel 1 goto :Error 
	if not exist "hlp\$(InputName).hlp" goto :Error 
	copy "hlp\$(InputName).hlp" $(OutDir) 
	goto :done 
	:Error 
	echo hlp\$(InputName).hpj(1) : error: 
	type "hlp\$(InputName).log" 
	:done 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\lab.odl
# End Source File
# Begin Source File

SOURCE=.\lab.rc
# End Source File
# Begin Source File

SOURCE=.\labDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LabElementList.cpp
# End Source File
# Begin Source File

SOURCE=.\LabElementsList.cpp
# End Source File
# Begin Source File

SOURCE=.\LabListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\LabObjectsList.cpp
# End Source File
# Begin Source File

SOURCE=.\LaboratoryDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\LaboratoryView.cpp
# End Source File
# Begin Source File

SOURCE=.\labView.cpp
# End Source File
# Begin Source File

SOURCE=.\ListGenezis.cpp
# End Source File
# Begin Source File

SOURCE=.\ListGruntGran.cpp
# End Source File
# Begin Source File

SOURCE=.\ListGrunty.cpp
# End Source File
# Begin Source File

SOURCE=.\ListNaborGruntov.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPalja.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\ObjectRecordset.cpp
# End Source File
# Begin Source File

SOURCE=.\PlotnostChasticExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\PlotnostGruntaExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\PropList.cpp
# End Source File
# Begin Source File

SOURCE=.\SandGranularExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\SetBlankLines.cpp
# End Source File
# Begin Source File

SOURCE=.\SetChemVD.cpp
# End Source File
# Begin Source File

SOURCE=.\SetChemVD_tbl.cpp
# End Source File
# Begin Source File

SOURCE=.\SetCilce.cpp
# End Source File
# Begin Source File

SOURCE=.\SetCilce0.cpp
# End Source File
# Begin Source File

SOURCE=.\SetCompress.cpp
# End Source File
# Begin Source File

SOURCE=.\SetConsObj.cpp
# End Source File
# Begin Source File

SOURCE=.\SetCubeSize.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFizMeh.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFizMehAllParam.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFizMehParam.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFundament.cpp
# End Source File
# Begin Source File

SOURCE=.\SetFundament_tbl.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGenezis.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGeoTables.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGranSklad.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGranSklad1.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGranular.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGranularAll_2.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGridData.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGriddataSurfaces.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGridDataUsedAlgorothms.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGrMain.cpp
# End Source File
# Begin Source File

SOURCE=.\SetGrunty.cpp
# End Source File
# Begin Source File

SOURCE=.\SetIGE.cpp
# End Source File
# Begin Source File

SOURCE=.\SetIGE0.cpp
# End Source File
# Begin Source File

SOURCE=.\SetKT.cpp
# End Source File
# Begin Source File

SOURCE=.\SetLito.cpp
# End Source File
# Begin Source File

SOURCE=.\SetLito0.cpp
# End Source File
# Begin Source File

SOURCE=.\SetObject.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPalja.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPalja1.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_CalcMode.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_CalcModes.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_CalcParams.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_UserCalcModes.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPCK2FizResults.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPCK2FizTable.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPodTypyGr.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPodTypyGrUser.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPolygons.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPres.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPress.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPress_tbl.cpp
# End Source File
# Begin Source File

SOURCE=.\SetProbGr.cpp
# End Source File
# Begin Source File

SOURCE=.\SetProbGr2.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPtPalja.cpp
# End Source File
# Begin Source File

SOURCE=.\SetPtStZond.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRozriz.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRozrizy.cpp
# End Source File
# Begin Source File

SOURCE=.\SetRozrizy1.cpp
# End Source File
# Begin Source File

SOURCE=.\SetShtamp.cpp
# End Source File
# Begin Source File

SOURCE=.\SetShtamp_detail.cpp
# End Source File
# Begin Source File

SOURCE=.\SetStZond.cpp
# End Source File
# Begin Source File

SOURCE=.\SetStZond1.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesBlankFunctions.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesBlankOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesBlankOrder1.cpp
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesOrder.cpp
# End Source File
# Begin Source File

SOURCE=.\SetT_P.cpp
# End Source File
# Begin Source File

SOURCE=.\SetT_V.cpp
# End Source File
# Begin Source File

SOURCE=.\SetUmPoz.cpp
# End Source File
# Begin Source File

SOURCE=.\SetUstanovka.cpp
# End Source File
# Begin Source File

SOURCE=.\SetVoda.cpp
# End Source File
# Begin Source File

SOURCE=.\SetWopt.cpp
# End Source File
# Begin Source File

SOURCE=.\SetWopt_tbl.cpp
# End Source File
# Begin Source File

SOURCE=.\SetZriz.cpp
# End Source File
# Begin Source File

SOURCE=.\SetZriz0.cpp
# End Source File
# Begin Source File

SOURCE=.\SetZriz_tbl.cpp
# End Source File
# Begin Source File

SOURCE=.\SoilsList.cpp
# End Source File
# Begin Source File

SOURCE=.\SoilsListLab.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\tableDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\TableFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\TableSet.cpp
# End Source File
# Begin Source File

SOURCE=.\tableView.cpp
# End Source File
# Begin Source File

SOURCE=.\UstList.cpp
# End Source File
# Begin Source File

SOURCE=.\utExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\VegetableRemainsExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\WlazhnostExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\WLExcel.cpp
# End Source File
# Begin Source File

SOURCE=.\WlpExcel.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\3DDoc.h
# End Source File
# Begin Source File

SOURCE=.\3DFrame.h
# End Source File
# Begin Source File

SOURCE=.\3DView.h
# End Source File
# Begin Source File

SOURCE=.\AreometrGranular.h
# End Source File
# Begin Source File

SOURCE=.\AreometrGranularExcel.h
# End Source File
# Begin Source File

SOURCE=.\ATable.h
# End Source File
# Begin Source File

SOURCE=.\BaseExcel.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ComboProbGrKT.h
# End Source File
# Begin Source File

SOURCE=.\CompressionExcel.h
# End Source File
# Begin Source File

SOURCE=.\DaoSetGeoObjects.h
# End Source File
# Begin Source File

SOURCE=.\DataBaseTalblesList.h
# End Source File
# Begin Source File

SOURCE=.\DBTable.h
# End Source File
# Begin Source File

SOURCE=.\DBTableCilce.h
# End Source File
# Begin Source File

SOURCE=.\DBTableCompress.h
# End Source File
# Begin Source File

SOURCE=.\DBTableGranular.h
# End Source File
# Begin Source File

SOURCE=.\DBTableGrunty.h
# End Source File
# Begin Source File

SOURCE=.\DBTableIGE.h
# End Source File
# Begin Source File

SOURCE=.\DBTableKT.h
# End Source File
# Begin Source File

SOURCE=.\DBTableLito.h
# End Source File
# Begin Source File

SOURCE=.\DBTablePalja.h
# End Source File
# Begin Source File

SOURCE=.\DBTableProp.h
# End Source File
# Begin Source File

SOURCE=.\DBTablePtPalja.h
# End Source File
# Begin Source File

SOURCE=.\DBTablePtStZond.h
# End Source File
# Begin Source File

SOURCE=.\DBTableSoils.h
# End Source File
# Begin Source File

SOURCE=.\DBTableStZond.h
# End Source File
# Begin Source File

SOURCE=.\DBTableZriz.h
# End Source File
# Begin Source File

SOURCE=.\DBTableZriz_tbl.h
# End Source File
# Begin Source File

SOURCE=.\DBViewList.h
# End Source File
# Begin Source File

SOURCE=.\DlgCopyGrunty.h
# End Source File
# Begin Source File

SOURCE=.\DlgIGEList.h
# End Source File
# Begin Source File

SOURCE=.\DlgLabElements.h
# End Source File
# Begin Source File

SOURCE=.\DlgLanguage.h
# End Source File
# Begin Source File

SOURCE=.\DlgNaborGruntovSetting.h
# End Source File
# Begin Source File

SOURCE=.\DlgNRows.h
# End Source File
# Begin Source File

SOURCE=.\DlgPalja.h
# End Source File
# Begin Source File

SOURCE=.\DlgPCK2Fiz.h
# End Source File
# Begin Source File

SOURCE=.\DlgProbGr_DblClickMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgProbGrunt.h
# End Source File
# Begin Source File

SOURCE=.\DlgRepeatings.h
# End Source File
# Begin Source File

SOURCE=.\DlgSoilName.h
# End Source File
# Begin Source File

SOURCE=.\DlgStatZond.h
# End Source File
# Begin Source File

SOURCE=.\DlgZondUstParam.h
# End Source File
# Begin Source File

SOURCE=.\EnGeoFrame.h
# End Source File
# Begin Source File

SOURCE=.\EnGeoListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\EnGeologyDoc.h
# End Source File
# Begin Source File

SOURCE=.\EnGeologyView.h
# End Source File
# Begin Source File

SOURCE=.\EnGeoObjectsList.h
# End Source File
# Begin Source File

SOURCE=.\ExcelColChar.h
# End Source File
# Begin Source File

SOURCE=.\ExcelKTList.h
# End Source File
# Begin Source File

SOURCE=.\GranularList.h
# End Source File
# Begin Source File

SOURCE=.\GranularListLab.h
# End Source File
# Begin Source File

SOURCE=.\KTLabList.h
# End Source File
# Begin Source File

SOURCE=.\KTListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\KtSet.h
# End Source File
# Begin Source File

SOURCE=.\lab.h
# End Source File
# Begin Source File

SOURCE=.\labDoc.h
# End Source File
# Begin Source File

SOURCE=.\LabElementList.h
# End Source File
# Begin Source File

SOURCE=.\LabElementsList.h
# End Source File
# Begin Source File

SOURCE=.\LabListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\LabObjectsList.h
# End Source File
# Begin Source File

SOURCE=.\LaboratoryDoc.h
# End Source File
# Begin Source File

SOURCE=.\LaboratoryView.h
# End Source File
# Begin Source File

SOURCE=.\labView.h
# End Source File
# Begin Source File

SOURCE=.\ListGenezis.h
# End Source File
# Begin Source File

SOURCE=.\ListGruntGran.h
# End Source File
# Begin Source File

SOURCE=.\ListGrunty.h
# End Source File
# Begin Source File

SOURCE=.\ListNaborGruntov.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\MyPalja.h
# End Source File
# Begin Source File

SOURCE=.\ObjectDialog.h
# End Source File
# Begin Source File

SOURCE=.\ObjectRecordset.h
# End Source File
# Begin Source File

SOURCE=.\PlotnostChasticExcel.h
# End Source File
# Begin Source File

SOURCE=.\PlotnostGruntaExcel.h
# End Source File
# Begin Source File

SOURCE=.\PropList.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h

!IF  "$(CFG)" == "lab - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=lab
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "lab - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Making help include file...
TargetName=lab
InputPath=.\Resource.h

"hlp\$(TargetName).hm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	echo. >"hlp\$(TargetName).hm" 
	echo // Commands (ID_* and IDM_*) >>"hlp\$(TargetName).hm" 
	makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Prompts (IDP_*) >>"hlp\$(TargetName).hm" 
	makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Resources (IDR_*) >>"hlp\$(TargetName).hm" 
	makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Dialogs (IDD_*) >>"hlp\$(TargetName).hm" 
	makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\$(TargetName).hm" 
	echo. >>"hlp\$(TargetName).hm" 
	echo // Frame Controls (IDW_*) >>"hlp\$(TargetName).hm" 
	makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\$(TargetName).hm" 
	
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\SandGranularExcel.h
# End Source File
# Begin Source File

SOURCE=.\SetBlankLines.h
# End Source File
# Begin Source File

SOURCE=.\SetChemVD.h
# End Source File
# Begin Source File

SOURCE=.\SetChemVD_tbl.h
# End Source File
# Begin Source File

SOURCE=.\SetCilce.h
# End Source File
# Begin Source File

SOURCE=.\SetCilce0.h
# End Source File
# Begin Source File

SOURCE=.\SetCompress.h
# End Source File
# Begin Source File

SOURCE=.\SetConsObj.h
# End Source File
# Begin Source File

SOURCE=.\SetCubeSize.h
# End Source File
# Begin Source File

SOURCE=.\SetFizMeh.h
# End Source File
# Begin Source File

SOURCE=.\SetFizMehAllParam.h
# End Source File
# Begin Source File

SOURCE=.\SetFizMehParam.h
# End Source File
# Begin Source File

SOURCE=.\SetFundament.h
# End Source File
# Begin Source File

SOURCE=.\SetFundament_tbl.h
# End Source File
# Begin Source File

SOURCE=.\SetGenezis.h
# End Source File
# Begin Source File

SOURCE=.\SetGeoTables.h
# End Source File
# Begin Source File

SOURCE=.\SetGranSklad.h
# End Source File
# Begin Source File

SOURCE=.\SetGranSklad1.h
# End Source File
# Begin Source File

SOURCE=.\SetGranular.h
# End Source File
# Begin Source File

SOURCE=.\SetGranularAll_2.h
# End Source File
# Begin Source File

SOURCE=.\SetGridData.h
# End Source File
# Begin Source File

SOURCE=.\SetGriddataSurfaces.h
# End Source File
# Begin Source File

SOURCE=.\SetGridDataUsedAlgorothms.h
# End Source File
# Begin Source File

SOURCE=.\SetGrMain.h
# End Source File
# Begin Source File

SOURCE=.\SetGrunty.h
# End Source File
# Begin Source File

SOURCE=.\SetIGE.h
# End Source File
# Begin Source File

SOURCE=.\SetIGE0.h
# End Source File
# Begin Source File

SOURCE=.\SetKT.h
# End Source File
# Begin Source File

SOURCE=.\SetLito.h
# End Source File
# Begin Source File

SOURCE=.\SetLito0.h
# End Source File
# Begin Source File

SOURCE=.\SetObject.h
# End Source File
# Begin Source File

SOURCE=.\SetPalja.h
# End Source File
# Begin Source File

SOURCE=.\SetPalja1.h
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_CalcMode.h
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_CalcModes.h
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_CalcParams.h
# End Source File
# Begin Source File

SOURCE=.\SetPCK2Fiz_UserCalcModes.h
# End Source File
# Begin Source File

SOURCE=.\SetPCK2FizResults.h
# End Source File
# Begin Source File

SOURCE=.\SetPCK2FizTable.h
# End Source File
# Begin Source File

SOURCE=.\SetPodTypyGr.h
# End Source File
# Begin Source File

SOURCE=.\SetPodTypyGrUser.h
# End Source File
# Begin Source File

SOURCE=.\SetPolygons.h
# End Source File
# Begin Source File

SOURCE=.\SetPres.h
# End Source File
# Begin Source File

SOURCE=.\SetPress.h
# End Source File
# Begin Source File

SOURCE=.\SetPress_tbl.h
# End Source File
# Begin Source File

SOURCE=.\SetProbGr.h
# End Source File
# Begin Source File

SOURCE=.\SetProbGr2.h
# End Source File
# Begin Source File

SOURCE=.\SetPtPalja.h
# End Source File
# Begin Source File

SOURCE=.\SetPtStZond.h
# End Source File
# Begin Source File

SOURCE=.\SetRozriz.h
# End Source File
# Begin Source File

SOURCE=.\SetRozrizy.h
# End Source File
# Begin Source File

SOURCE=.\SetRozrizy1.h
# End Source File
# Begin Source File

SOURCE=.\SetShtamp.h
# End Source File
# Begin Source File

SOURCE=.\SetShtamp_detail.h
# End Source File
# Begin Source File

SOURCE=.\SetStZond.h
# End Source File
# Begin Source File

SOURCE=.\SetStZond1.h
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesBlankFunctions.h
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesBlankOrder.h
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesBlankOrder1.h
# End Source File
# Begin Source File

SOURCE=.\SetSurfacesOrder.h
# End Source File
# Begin Source File

SOURCE=.\SetT_P.h
# End Source File
# Begin Source File

SOURCE=.\SetT_V.h
# End Source File
# Begin Source File

SOURCE=.\SetUmPoz.h
# End Source File
# Begin Source File

SOURCE=.\SetUstanovka.h
# End Source File
# Begin Source File

SOURCE=.\SetVoda.h
# End Source File
# Begin Source File

SOURCE=.\SetWopt.h
# End Source File
# Begin Source File

SOURCE=.\SetWopt_tbl.h
# End Source File
# Begin Source File

SOURCE=.\SetZriz.h
# End Source File
# Begin Source File

SOURCE=.\SetZriz0.h
# End Source File
# Begin Source File

SOURCE=.\SetZriz_tbl.h
# End Source File
# Begin Source File

SOURCE=.\SoilsList.h
# End Source File
# Begin Source File

SOURCE=.\SoilsListLab.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\tableDoc.h
# End Source File
# Begin Source File

SOURCE=.\TableFrm.h
# End Source File
# Begin Source File

SOURCE=.\TableSet.h
# End Source File
# Begin Source File

SOURCE=.\tableView.h
# End Source File
# Begin Source File

SOURCE=.\UstList.h
# End Source File
# Begin Source File

SOURCE=.\utExcel.h
# End Source File
# Begin Source File

SOURCE=.\VegetableRemainsExcel.h
# End Source File
# Begin Source File

SOURCE=.\WlazhnostExcel.h
# End Source File
# Begin Source File

SOURCE=.\WLExcel.h
# End Source File
# Begin Source File

SOURCE=.\WlpExcel.h
# End Source File
# Begin Source File

SOURCE=.\xl5en32.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\hdricon1.ico
# End Source File
# Begin Source File

SOURCE=.\hdricon2.ico
# End Source File
# Begin Source File

SOURCE=.\iconlist1.ico
# End Source File
# Begin Source File

SOURCE=.\iconlist2.ico
# End Source File
# Begin Source File

SOURCE=.\iconlist3.ico
# End Source File
# Begin Source File

SOURCE=.\iconlist4.ico
# End Source File
# Begin Source File

SOURCE=.\res\lab.ico
# End Source File
# Begin Source File

SOURCE=.\res\lab.rc2
# End Source File
# Begin Source File

SOURCE=.\res\labDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter "cnt;rtf"
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AfxPrint.rtf
# End Source File
# Begin Source File

SOURCE=.\hlp\AppExit.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\lab.cnt

!IF  "$(CFG)" == "lab - Win32 Release"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Release
InputPath=.\hlp\lab.cnt
InputName=lab

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ELSEIF  "$(CFG)" == "lab - Win32 Debug"

# PROP Ignore_Default_Tool 1
# Begin Custom Build - Copying contents file...
OutDir=.\Debug
InputPath=.\hlp\lab.cnt
InputName=lab

"$(OutDir)\$(InputName).cnt" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "hlp\$(InputName).cnt" $(OutDir)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\lab.reg
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
