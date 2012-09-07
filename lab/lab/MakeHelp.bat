@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LAB.HPJ. >"hlp\lab.hm"
echo. >>"hlp\lab.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\lab.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\lab.hm"
echo. >>"hlp\lab.hm"
echo // Prompts (IDP_*) >>"hlp\lab.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\lab.hm"
echo. >>"hlp\lab.hm"
echo // Resources (IDR_*) >>"hlp\lab.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\lab.hm"
echo. >>"hlp\lab.hm"
echo // Dialogs (IDD_*) >>"hlp\lab.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\lab.hm"
echo. >>"hlp\lab.hm"
echo // Frame Controls (IDW_*) >>"hlp\lab.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\lab.hm"
REM -- Make help for Project LAB


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\lab.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\lab.hlp" goto :Error
if not exist "hlp\lab.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\lab.hlp" Debug
if exist Debug\nul copy "hlp\lab.cnt" Debug
if exist Release\nul copy "hlp\lab.hlp" Release
if exist Release\nul copy "hlp\lab.cnt" Release
echo.
goto :done

:Error
echo hlp\lab.hpj(1) : error: Problem encountered creating help file

:done
echo.
