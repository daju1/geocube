// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "xl5en32.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


	
// copied from excel8
LPDISPATCH _Application5::GetWorkbooks()
{
	LPDISPATCH result;
	InvokeHelper(0x23c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
LPDISPATCH _Application5::GetWorksheets()
{
	LPDISPATCH result;
	InvokeHelper(0x1ee, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}
/////////////////////////////////////////////////////////////////////////////
// _Application5 properties

VARIANT _Application5::GetActiveCell()
{
	VARIANT result;
	GetProperty(0x131, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveCell(const VARIANT& propVal)
{
	SetProperty(0x131, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActiveChart()
{
	VARIANT result;
	GetProperty(0xb7, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveChart(const VARIANT& propVal)
{
	SetProperty(0xb7, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActiveDialog()
{
	VARIANT result;
	GetProperty(0x32f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveDialog(const VARIANT& propVal)
{
	SetProperty(0x32f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActiveMenuBar()
{
	VARIANT result;
	GetProperty(0x2f6, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveMenuBar(const VARIANT& propVal)
{
	SetProperty(0x2f6, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActivePrinter()
{
	VARIANT result;
	GetProperty(0x132, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActivePrinter(const VARIANT& propVal)
{
	SetProperty(0x132, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActiveSheet()
{
	VARIANT result;
	GetProperty(0x133, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveSheet(const VARIANT& propVal)
{
	SetProperty(0x133, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActiveWindow()
{
	VARIANT result;
	GetProperty(0x2f7, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveWindow(const VARIANT& propVal)
{
	SetProperty(0x2f7, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetActiveWorkbook()
{
	VARIANT result;
	GetProperty(0x134, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetActiveWorkbook(const VARIANT& propVal)
{
	SetProperty(0x134, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetAlertBeforeOverwriting()
{
	VARIANT result;
	GetProperty(0x3a2, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetAlertBeforeOverwriting(const VARIANT& propVal)
{
	SetProperty(0x3a2, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetAltStartupPath()
{
	VARIANT result;
	GetProperty(0x139, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetAltStartupPath(const VARIANT& propVal)
{
	SetProperty(0x139, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetAskToUpdateLinks()
{
	VARIANT result;
	GetProperty(0x3e0, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetAskToUpdateLinks(const VARIANT& propVal)
{
	SetProperty(0x3e0, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetAutoCorrect()
{
	VARIANT result;
	GetProperty(0x479, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetAutoCorrect(const VARIANT& propVal)
{
	SetProperty(0x479, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetBuild()
{
	VARIANT result;
	GetProperty(0x13a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetBuild(const VARIANT& propVal)
{
	SetProperty(0x13a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCalculateBeforeSave()
{
	VARIANT result;
	GetProperty(0x13b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCalculateBeforeSave(const VARIANT& propVal)
{
	SetProperty(0x13b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCalculation()
{
	VARIANT result;
	GetProperty(0x13c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCalculation(const VARIANT& propVal)
{
	SetProperty(0x13c, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCaller()
{
	VARIANT result;
	GetProperty(0x13d, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCaller(const VARIANT& propVal)
{
	SetProperty(0x13d, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCanPlaySounds()
{
	VARIANT result;
	GetProperty(0x13e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCanPlaySounds(const VARIANT& propVal)
{
	SetProperty(0x13e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCanRecordSounds()
{
	VARIANT result;
	GetProperty(0x13f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCanRecordSounds(const VARIANT& propVal)
{
	SetProperty(0x13f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCaption()
{
	VARIANT result;
	GetProperty(0x8b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCaption(const VARIANT& propVal)
{
	SetProperty(0x8b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCellDragAndDrop()
{
	VARIANT result;
	GetProperty(0x140, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCellDragAndDrop(const VARIANT& propVal)
{
	SetProperty(0x140, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetClipboardFormats()
{
	VARIANT result;
	GetProperty(0x141, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetClipboardFormats(const VARIANT& propVal)
{
	SetProperty(0x141, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetColorButtons()
{
	VARIANT result;
	GetProperty(0x16d, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetColorButtons(const VARIANT& propVal)
{
	SetProperty(0x16d, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCommandUnderlines()
{
	VARIANT result;
	GetProperty(0x143, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCommandUnderlines(const VARIANT& propVal)
{
	SetProperty(0x143, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetConstrainNumeric()
{
	VARIANT result;
	GetProperty(0x144, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetConstrainNumeric(const VARIANT& propVal)
{
	SetProperty(0x144, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCopyObjectsWithCells()
{
	VARIANT result;
	GetProperty(0x3df, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCopyObjectsWithCells(const VARIANT& propVal)
{
	SetProperty(0x3df, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCursor()
{
	VARIANT result;
	GetProperty(0x489, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCursor(const VARIANT& propVal)
{
	SetProperty(0x489, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCustomListCount()
{
	VARIANT result;
	GetProperty(0x313, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCustomListCount(const VARIANT& propVal)
{
	SetProperty(0x313, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetCutCopyMode()
{
	VARIANT result;
	GetProperty(0x14a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetCutCopyMode(const VARIANT& propVal)
{
	SetProperty(0x14a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDataEntryMode()
{
	VARIANT result;
	GetProperty(0x14b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDataEntryMode(const VARIANT& propVal)
{
	SetProperty(0x14b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDDEAppReturnCode()
{
	VARIANT result;
	GetProperty(0x14c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDDEAppReturnCode(const VARIANT& propVal)
{
	SetProperty(0x14c, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDefaultFilePath()
{
	VARIANT result;
	GetProperty(0x40e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDefaultFilePath(const VARIANT& propVal)
{
	SetProperty(0x40e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayAlerts()
{
	VARIANT result;
	GetProperty(0x157, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayAlerts(const VARIANT& propVal)
{
	SetProperty(0x157, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayClipboardWindow()
{
	VARIANT result;
	GetProperty(0x142, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayClipboardWindow(const VARIANT& propVal)
{
	SetProperty(0x142, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayExcel4Menus()
{
	VARIANT result;
	GetProperty(0x39f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayExcel4Menus(const VARIANT& propVal)
{
	SetProperty(0x39f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayFormulaBar()
{
	VARIANT result;
	GetProperty(0x158, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayFormulaBar(const VARIANT& propVal)
{
	SetProperty(0x158, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayFullScreen()
{
	VARIANT result;
	GetProperty(0x425, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayFullScreen(const VARIANT& propVal)
{
	SetProperty(0x425, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayInfoWindow()
{
	VARIANT result;
	GetProperty(0x2fd, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayInfoWindow(const VARIANT& propVal)
{
	SetProperty(0x2fd, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayNoteIndicator()
{
	VARIANT result;
	GetProperty(0x159, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayNoteIndicator(const VARIANT& propVal)
{
	SetProperty(0x159, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayRecentFiles()
{
	VARIANT result;
	GetProperty(0x39e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayRecentFiles(const VARIANT& propVal)
{
	SetProperty(0x39e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayScrollBars()
{
	VARIANT result;
	GetProperty(0x15a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayScrollBars(const VARIANT& propVal)
{
	SetProperty(0x15a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetDisplayStatusBar()
{
	VARIANT result;
	GetProperty(0x15b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetDisplayStatusBar(const VARIANT& propVal)
{
	SetProperty(0x15b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetEditDirectlyInCell()
{
	VARIANT result;
	GetProperty(0x3a1, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetEditDirectlyInCell(const VARIANT& propVal)
{
	SetProperty(0x3a1, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetEnableAnimations()
{
	VARIANT result;
	GetProperty(0x49c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetEnableAnimations(const VARIANT& propVal)
{
	SetProperty(0x49c, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetEnableAutoComplete()
{
	VARIANT result;
	GetProperty(0x49b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetEnableAutoComplete(const VARIANT& propVal)
{
	SetProperty(0x49b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetEnableCancelKey()
{
	VARIANT result;
	GetProperty(0x448, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetEnableCancelKey(const VARIANT& propVal)
{
	SetProperty(0x448, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetEnableTipWizard()
{
	VARIANT result;
	GetProperty(0x428, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetEnableTipWizard(const VARIANT& propVal)
{
	SetProperty(0x428, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetFileConverters()
{
	VARIANT result;
	GetProperty(0x3a3, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetFileConverters(const VARIANT& propVal)
{
	SetProperty(0x3a3, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetFixedDecimal()
{
	VARIANT result;
	GetProperty(0x15f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetFixedDecimal(const VARIANT& propVal)
{
	SetProperty(0x15f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetFixedDecimalPlaces()
{
	VARIANT result;
	GetProperty(0x160, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetFixedDecimalPlaces(const VARIANT& propVal)
{
	SetProperty(0x160, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetHeight()
{
	VARIANT result;
	GetProperty(0x7b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetHeight(const VARIANT& propVal)
{
	SetProperty(0x7b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetIgnoreRemoteRequests()
{
	VARIANT result;
	GetProperty(0x164, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetIgnoreRemoteRequests(const VARIANT& propVal)
{
	SetProperty(0x164, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetInteractive()
{
	VARIANT result;
	GetProperty(0x169, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetInteractive(const VARIANT& propVal)
{
	SetProperty(0x169, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetInternational()
{
	VARIANT result;
	GetProperty(0x16a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetInternational(const VARIANT& propVal)
{
	SetProperty(0x16a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetIteration()
{
	VARIANT result;
	GetProperty(0x16b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetIteration(const VARIANT& propVal)
{
	SetProperty(0x16b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetLargeButtons()
{
	VARIANT result;
	GetProperty(0x16c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetLargeButtons(const VARIANT& propVal)
{
	SetProperty(0x16c, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetLeft()
{
	VARIANT result;
	GetProperty(0x7f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetLeft(const VARIANT& propVal)
{
	SetProperty(0x7f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetLibraryPath()
{
	VARIANT result;
	GetProperty(0x16e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetLibraryPath(const VARIANT& propVal)
{
	SetProperty(0x16e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMailSession()
{
	VARIANT result;
	GetProperty(0x3ae, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMailSession(const VARIANT& propVal)
{
	SetProperty(0x3ae, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMailSystem()
{
	VARIANT result;
	GetProperty(0x3cb, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMailSystem(const VARIANT& propVal)
{
	SetProperty(0x3cb, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMathCoprocessorAvailable()
{
	VARIANT result;
	GetProperty(0x16f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMathCoprocessorAvailable(const VARIANT& propVal)
{
	SetProperty(0x16f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMaxChange()
{
	VARIANT result;
	GetProperty(0x170, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMaxChange(const VARIANT& propVal)
{
	SetProperty(0x170, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMaxIterations()
{
	VARIANT result;
	GetProperty(0x171, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMaxIterations(const VARIANT& propVal)
{
	SetProperty(0x171, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMemoryFree()
{
	VARIANT result;
	GetProperty(0x172, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMemoryFree(const VARIANT& propVal)
{
	SetProperty(0x172, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMemoryTotal()
{
	VARIANT result;
	GetProperty(0x173, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMemoryTotal(const VARIANT& propVal)
{
	SetProperty(0x173, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMemoryUsed()
{
	VARIANT result;
	GetProperty(0x174, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMemoryUsed(const VARIANT& propVal)
{
	SetProperty(0x174, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMouseAvailable()
{
	VARIANT result;
	GetProperty(0x175, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMouseAvailable(const VARIANT& propVal)
{
	SetProperty(0x175, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMoveAfterReturn()
{
	VARIANT result;
	GetProperty(0x176, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMoveAfterReturn(const VARIANT& propVal)
{
	SetProperty(0x176, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetMoveAfterReturnDirection()
{
	VARIANT result;
	GetProperty(0x478, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetMoveAfterReturnDirection(const VARIANT& propVal)
{
	SetProperty(0x478, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetName()
{
	VARIANT result;
	GetProperty(0x6e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetName(const VARIANT& propVal)
{
	SetProperty(0x6e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetNetworkTemplatesPath()
{
	VARIANT result;
	GetProperty(0x184, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetNetworkTemplatesPath(const VARIANT& propVal)
{
	SetProperty(0x184, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnCalculate()
{
	VARIANT result;
	GetProperty(0x271, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnCalculate(const VARIANT& propVal)
{
	SetProperty(0x271, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnData()
{
	VARIANT result;
	GetProperty(0x275, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnData(const VARIANT& propVal)
{
	SetProperty(0x275, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnDoubleClick()
{
	VARIANT result;
	GetProperty(0x274, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnDoubleClick(const VARIANT& propVal)
{
	SetProperty(0x274, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnEntry()
{
	VARIANT result;
	GetProperty(0x273, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnEntry(const VARIANT& propVal)
{
	SetProperty(0x273, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnSheetActivate()
{
	VARIANT result;
	GetProperty(0x407, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnSheetActivate(const VARIANT& propVal)
{
	SetProperty(0x407, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnSheetDeactivate()
{
	VARIANT result;
	GetProperty(0x439, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnSheetDeactivate(const VARIANT& propVal)
{
	SetProperty(0x439, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOnWindow()
{
	VARIANT result;
	GetProperty(0x26f, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOnWindow(const VARIANT& propVal)
{
	SetProperty(0x26f, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOperatingSystem()
{
	VARIANT result;
	GetProperty(0x177, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOperatingSystem(const VARIANT& propVal)
{
	SetProperty(0x177, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetOrganizationName()
{
	VARIANT result;
	GetProperty(0x178, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetOrganizationName(const VARIANT& propVal)
{
	SetProperty(0x178, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetPath()
{
	VARIANT result;
	GetProperty(0x123, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetPath(const VARIANT& propVal)
{
	SetProperty(0x123, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetPathSeparator()
{
	VARIANT result;
	GetProperty(0x179, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetPathSeparator(const VARIANT& propVal)
{
	SetProperty(0x179, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetPreviousSelections()
{
	VARIANT result;
	GetProperty(0x17a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetPreviousSelections(const VARIANT& propVal)
{
	SetProperty(0x17a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetPromptForSummaryInfo()
{
	VARIANT result;
	GetProperty(0x426, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetPromptForSummaryInfo(const VARIANT& propVal)
{
	SetProperty(0x426, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetRecordRelative()
{
	VARIANT result;
	GetProperty(0x17b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetRecordRelative(const VARIANT& propVal)
{
	SetProperty(0x17b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetReferenceStyle()
{
	VARIANT result;
	GetProperty(0x17c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetReferenceStyle(const VARIANT& propVal)
{
	SetProperty(0x17c, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetRegisteredFunctions()
{
	VARIANT result;
	GetProperty(0x307, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetRegisteredFunctions(const VARIANT& propVal)
{
	SetProperty(0x307, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetScreenUpdating()
{
	VARIANT result;
	GetProperty(0x17e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetScreenUpdating(const VARIANT& propVal)
{
	SetProperty(0x17e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetSelection()
{
	VARIANT result;
	GetProperty(0x93, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetSelection(const VARIANT& propVal)
{
	SetProperty(0x93, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetSheetsInNewWorkbook()
{
	VARIANT result;
	GetProperty(0x3e1, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetSheetsInNewWorkbook(const VARIANT& propVal)
{
	SetProperty(0x3e1, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetShowToolTips()
{
	VARIANT result;
	GetProperty(0x183, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetShowToolTips(const VARIANT& propVal)
{
	SetProperty(0x183, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetStandardFont()
{
	VARIANT result;
	GetProperty(0x39c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetStandardFont(const VARIANT& propVal)
{
	SetProperty(0x39c, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetStandardFontSize()
{
	VARIANT result;
	GetProperty(0x39d, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetStandardFontSize(const VARIANT& propVal)
{
	SetProperty(0x39d, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetStartupPath()
{
	VARIANT result;
	GetProperty(0x181, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetStartupPath(const VARIANT& propVal)
{
	SetProperty(0x181, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetStatusBar()
{
	VARIANT result;
	GetProperty(0x182, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetStatusBar(const VARIANT& propVal)
{
	SetProperty(0x182, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetTemplatesPath()
{
	VARIANT result;
	GetProperty(0x17d, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetTemplatesPath(const VARIANT& propVal)
{
	SetProperty(0x17d, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetThisWorkbook()
{
	VARIANT result;
	GetProperty(0x30a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetThisWorkbook(const VARIANT& propVal)
{
	SetProperty(0x30a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetTop()
{
	VARIANT result;
	GetProperty(0x7e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetTop(const VARIANT& propVal)
{
	SetProperty(0x7e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetTransitionMenuKey()
{
	VARIANT result;
	GetProperty(0x136, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetTransitionMenuKey(const VARIANT& propVal)
{
	SetProperty(0x136, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetTransitionMenuKeyAction()
{
	VARIANT result;
	GetProperty(0x137, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetTransitionMenuKeyAction(const VARIANT& propVal)
{
	SetProperty(0x137, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetTransitionNavigKeys()
{
	VARIANT result;
	GetProperty(0x138, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetTransitionNavigKeys(const VARIANT& propVal)
{
	SetProperty(0x138, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetUsableHeight()
{
	VARIANT result;
	GetProperty(0x185, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetUsableHeight(const VARIANT& propVal)
{
	SetProperty(0x185, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetUsableWidth()
{
	VARIANT result;
	GetProperty(0x186, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetUsableWidth(const VARIANT& propVal)
{
	SetProperty(0x186, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetUserName()
{
	VARIANT result;
	GetProperty(0x187, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetUserName(const VARIANT& propVal)
{
	SetProperty(0x187, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetValue()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetValue(const VARIANT& propVal)
{
	SetProperty(0x6, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetVersion()
{
	VARIANT result;
	GetProperty(0x188, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetVersion(const VARIANT& propVal)
{
	SetProperty(0x188, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetVisible()
{
	VARIANT result;
	GetProperty(0x22e, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetVisible(const VARIANT& propVal)
{
	SetProperty(0x22e, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetWidth()
{
	VARIANT result;
	GetProperty(0x7a, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetWidth(const VARIANT& propVal)
{
	SetProperty(0x7a, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetWindowsForPens()
{
	VARIANT result;
	GetProperty(0x18b, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetWindowsForPens(const VARIANT& propVal)
{
	SetProperty(0x18b, VT_VARIANT, &propVal);
}

VARIANT _Application5::GetWindowState()
{
	VARIANT result;
	GetProperty(0x18c, VT_VARIANT, (void*)&result);
	return result;
}

void _Application5::SetWindowState(const VARIANT& propVal)
{
	SetProperty(0x18c, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// _Application5 operations

VARIANT _Application5::_WSFunction(const VARIANT& Range, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, 
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, 
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, 
		const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Range, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

VARIANT _Application5::Acos()
{
	VARIANT result;
	InvokeHelper(0x4063, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Acosh()
{
	VARIANT result;
	InvokeHelper(0x40e9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::ActivateMicrosoftApp(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x447, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::AddChartAutoFormat(const VARIANT& Chart, const VARIANT& Name, const VARIANT& Description)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Chart, &Name, &Description);
	return result;
}

VARIANT _Application5::AddCustomList(const VARIANT& ListArray, const VARIANT& ByRow)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x30c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ListArray, &ByRow);
	return result;
}

VARIANT _Application5::AddIns(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x225, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::And()
{
	VARIANT result;
	InvokeHelper(0x4024, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Asin()
{
	VARIANT result;
	InvokeHelper(0x4062, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Asinh()
{
	VARIANT result;
	InvokeHelper(0x40e8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Atan2()
{
	VARIANT result;
	InvokeHelper(0x4061, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Atanh()
{
	VARIANT result;
	InvokeHelper(0x40ea, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::AveDev()
{
	VARIANT result;
	InvokeHelper(0x410d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Average()
{
	VARIANT result;
	InvokeHelper(0x4005, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::BetaDist()
{
	VARIANT result;
	InvokeHelper(0x410e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::BetaInv()
{
	VARIANT result;
	InvokeHelper(0x4110, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::BinomDist()
{
	VARIANT result;
	InvokeHelper(0x4111, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Calculate()
{
	VARIANT result;
	InvokeHelper(0x117, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Ceiling()
{
	VARIANT result;
	InvokeHelper(0x4120, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xee, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowIndex, &ColumnIndex);
	return result;
}

VARIANT _Application5::CentimetersToPoints(const VARIANT& Centimeters)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x43e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Centimeters);
	return result;
}

VARIANT _Application5::Charts(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x79, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::CheckSpelling(const VARIANT& Word, const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Word, &CustomDictionary, &IgnoreUppercase);
	return result;
}

VARIANT _Application5::ChiDist()
{
	VARIANT result;
	InvokeHelper(0x4112, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::ChiInv()
{
	VARIANT result;
	InvokeHelper(0x4113, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::ChiTest()
{
	VARIANT result;
	InvokeHelper(0x4132, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Choose()
{
	VARIANT result;
	InvokeHelper(0x4064, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Clean()
{
	VARIANT result;
	InvokeHelper(0x40a2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Columns(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Combin()
{
	VARIANT result;
	InvokeHelper(0x4114, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Confidence()
{
	VARIANT result;
	InvokeHelper(0x4115, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::ConvertFormula(const VARIANT& Formula, const VARIANT& FromReferenceStyle, const VARIANT& ToReferenceStyle, const VARIANT& ToAbsolute, const VARIANT& RelativeTo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x145, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Formula, &FromReferenceStyle, &ToReferenceStyle, &ToAbsolute, &RelativeTo);
	return result;
}

VARIANT _Application5::Correl()
{
	VARIANT result;
	InvokeHelper(0x4133, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Cosh()
{
	VARIANT result;
	InvokeHelper(0x40e6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Count()
{
	VARIANT result;
	InvokeHelper(0x4000, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::CountA()
{
	VARIANT result;
	InvokeHelper(0x40a9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::CountBlank()
{
	VARIANT result;
	InvokeHelper(0x415b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::CountIf()
{
	VARIANT result;
	InvokeHelper(0x415a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Covar()
{
	VARIANT result;
	InvokeHelper(0x4134, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::CritBinom()
{
	VARIANT result;
	InvokeHelper(0x4116, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DAverage()
{
	VARIANT result;
	InvokeHelper(0x402a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Days360()
{
	VARIANT result;
	InvokeHelper(0x40dc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Db()
{
	VARIANT result;
	InvokeHelper(0x40f7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DCount()
{
	VARIANT result;
	InvokeHelper(0x4028, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DCountA()
{
	VARIANT result;
	InvokeHelper(0x40c7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Ddb()
{
	VARIANT result;
	InvokeHelper(0x4090, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DDEExecute(const VARIANT& Channel, const VARIANT& String)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x14d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Channel, &String);
	return result;
}

VARIANT _Application5::DDEInitiate(const VARIANT& App, const VARIANT& Topic)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x14e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&App, &Topic);
	return result;
}

VARIANT _Application5::DDEPoke(const VARIANT& Channel, const VARIANT& Item, const VARIANT& Data)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x14f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Channel, &Item, &Data);
	return result;
}

VARIANT _Application5::DDERequest(const VARIANT& Channel, const VARIANT& Item)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x150, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Channel, &Item);
	return result;
}

VARIANT _Application5::DDETerminate(const VARIANT& Channel)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x151, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Channel);
	return result;
}

VARIANT _Application5::Degrees()
{
	VARIANT result;
	InvokeHelper(0x4157, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DeleteChartAutoFormat(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT _Application5::DeleteCustomList(const VARIANT& ListNum)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x30f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ListNum);
	return result;
}

VARIANT _Application5::DevSq()
{
	VARIANT result;
	InvokeHelper(0x413e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DGet()
{
	VARIANT result;
	InvokeHelper(0x40eb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Dialogs(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2f9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::DialogSheets(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2fc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::DMax()
{
	VARIANT result;
	InvokeHelper(0x402c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DMin()
{
	VARIANT result;
	InvokeHelper(0x402b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Dollar()
{
	VARIANT result;
	InvokeHelper(0x400d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DoubleClick()
{
	VARIANT result;
	InvokeHelper(0x15d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DProduct()
{
	VARIANT result;
	InvokeHelper(0x40bd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DStDev()
{
	VARIANT result;
	InvokeHelper(0x402d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DStDevP()
{
	VARIANT result;
	InvokeHelper(0x40c3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DSum()
{
	VARIANT result;
	InvokeHelper(0x4029, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DVar()
{
	VARIANT result;
	InvokeHelper(0x402f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::DVarP()
{
	VARIANT result;
	InvokeHelper(0x40c4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::_Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT _Application5::Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xfffffffb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT _Application5::Even()
{
	VARIANT result;
	InvokeHelper(0x4117, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Excel4IntlMacroSheets(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x245, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Excel4MacroSheets(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x243, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::ExecuteExcel4Macro(const VARIANT& String)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x15e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&String);
	return result;
}

VARIANT _Application5::ExponDist()
{
	VARIANT result;
	InvokeHelper(0x4118, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Fact()
{
	VARIANT result;
	InvokeHelper(0x40b8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::FDist()
{
	VARIANT result;
	InvokeHelper(0x4119, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Find()
{
	VARIANT result;
	InvokeHelper(0x407c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::FindB()
{
	VARIANT result;
	InvokeHelper(0x40cd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::FindFile()
{
	VARIANT result;
	InvokeHelper(0x42c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::FInv()
{
	VARIANT result;
	InvokeHelper(0x411a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Fisher()
{
	VARIANT result;
	InvokeHelper(0x411b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::FisherInv()
{
	VARIANT result;
	InvokeHelper(0x411c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Fixed()
{
	VARIANT result;
	InvokeHelper(0x400e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Floor()
{
	VARIANT result;
	InvokeHelper(0x411d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Forecast()
{
	VARIANT result;
	InvokeHelper(0x4135, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Frequency()
{
	VARIANT result;
	InvokeHelper(0x40fc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::FTest()
{
	VARIANT result;
	InvokeHelper(0x4136, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Fv()
{
	VARIANT result;
	InvokeHelper(0x4039, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::GammaDist()
{
	VARIANT result;
	InvokeHelper(0x411e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::GammaInv()
{
	VARIANT result;
	InvokeHelper(0x411f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::GammaLn()
{
	VARIANT result;
	InvokeHelper(0x410f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::GeoMean()
{
	VARIANT result;
	InvokeHelper(0x413f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::GetCustomListContents(const VARIANT& ListNum)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x312, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ListNum);
	return result;
}

VARIANT _Application5::GetCustomListNum(const VARIANT& ListArray)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x311, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ListArray);
	return result;
}

VARIANT _Application5::GetOpenFilename(const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText, const VARIANT& MultiSelect)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x433, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&FileFilter, &FilterIndex, &Title, &ButtonText, &MultiSelect);
	return result;
}

VARIANT _Application5::GetSaveAsFilename(const VARIANT& InitialFilename, const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x434, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&InitialFilename, &FileFilter, &FilterIndex, &Title, &ButtonText);
	return result;
}

VARIANT _Application5::Goto(const VARIANT& Reference, const VARIANT& Scroll)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1db, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Reference, &Scroll);
	return result;
}

VARIANT _Application5::Growth()
{
	VARIANT result;
	InvokeHelper(0x4034, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::HarMean()
{
	VARIANT result;
	InvokeHelper(0x4140, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Help(const VARIANT& HelpFile, const VARIANT& HelpContextID)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x162, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&HelpFile, &HelpContextID);
	return result;
}

VARIANT _Application5::HLookup()
{
	VARIANT result;
	InvokeHelper(0x4065, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::HypGeomDist()
{
	VARIANT result;
	InvokeHelper(0x4121, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::InchesToPoints(const VARIANT& Inches)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x43f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Inches);
	return result;
}

VARIANT _Application5::Index()
{
	VARIANT result;
	InvokeHelper(0x401d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::InputBox(const VARIANT& Prompt, const VARIANT& Title, const VARIANT& Default, const VARIANT& Left, const VARIANT& Top, const VARIANT& HelpFile, const VARIANT& HelpContextID, const VARIANT& Type)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x165, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Prompt, &Title, &Default, &Left, &Top, &HelpFile, &HelpContextID, &Type);
	return result;
}

VARIANT _Application5::Intercept()
{
	VARIANT result;
	InvokeHelper(0x4137, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Intersect(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2fe, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

VARIANT _Application5::Ipmt()
{
	VARIANT result;
	InvokeHelper(0x40a7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Irr()
{
	VARIANT result;
	InvokeHelper(0x403e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsErr()
{
	VARIANT result;
	InvokeHelper(0x407e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsError()
{
	VARIANT result;
	InvokeHelper(0x4003, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsLogical()
{
	VARIANT result;
	InvokeHelper(0x40c6, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsNA()
{
	VARIANT result;
	InvokeHelper(0x4002, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsNonText()
{
	VARIANT result;
	InvokeHelper(0x40be, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsNumber()
{
	VARIANT result;
	InvokeHelper(0x4080, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Ispmt()
{
	VARIANT result;
	InvokeHelper(0x415e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::IsText()
{
	VARIANT result;
	InvokeHelper(0x407f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Kurt()
{
	VARIANT result;
	InvokeHelper(0x4142, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Large()
{
	VARIANT result;
	InvokeHelper(0x4145, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::LinEst()
{
	VARIANT result;
	InvokeHelper(0x4031, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Ln()
{
	VARIANT result;
	InvokeHelper(0x4016, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Log()
{
	VARIANT result;
	InvokeHelper(0x406d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Log10()
{
	VARIANT result;
	InvokeHelper(0x4017, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::LogEst()
{
	VARIANT result;
	InvokeHelper(0x4033, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::LogInv()
{
	VARIANT result;
	InvokeHelper(0x4123, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::LogNormDist()
{
	VARIANT result;
	InvokeHelper(0x4122, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Lookup()
{
	VARIANT result;
	InvokeHelper(0x401c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MacroOptions(const VARIANT& Macro, const VARIANT& Description, const VARIANT& HasMenu, const VARIANT& MenuText, const VARIANT& HasShortcutKey, const VARIANT& ShortcutKey, const VARIANT& Category, const VARIANT& StatusBar, 
		const VARIANT& HelpContextID, const VARIANT& HelpFile)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x46f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Macro, &Description, &HasMenu, &MenuText, &HasShortcutKey, &ShortcutKey, &Category, &StatusBar, &HelpContextID, &HelpFile);
	return result;
}

VARIANT _Application5::MailLogoff()
{
	VARIANT result;
	InvokeHelper(0x3b1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MailLogon(const VARIANT& Name, const VARIANT& Password, const VARIANT& DownloadNewMail)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3af, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name, &Password, &DownloadNewMail);
	return result;
}

VARIANT _Application5::Match()
{
	VARIANT result;
	InvokeHelper(0x4040, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Max()
{
	VARIANT result;
	InvokeHelper(0x4007, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MDeterm()
{
	VARIANT result;
	InvokeHelper(0x40a3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Median()
{
	VARIANT result;
	InvokeHelper(0x40e3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MenuBars(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x24d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Min()
{
	VARIANT result;
	InvokeHelper(0x4006, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MInverse()
{
	VARIANT result;
	InvokeHelper(0x40a4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MIrr()
{
	VARIANT result;
	InvokeHelper(0x403d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::MMult()
{
	VARIANT result;
	InvokeHelper(0x40a5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Mode()
{
	VARIANT result;
	InvokeHelper(0x414a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Modules(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x246, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1ba, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index, &IndexLocal, &RefersTo);
	return result;
}

VARIANT _Application5::NegBinomDist()
{
	VARIANT result;
	InvokeHelper(0x4124, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::NextLetter()
{
	VARIANT result;
	InvokeHelper(0x3cc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::NormDist()
{
	VARIANT result;
	InvokeHelper(0x4125, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::NormInv()
{
	VARIANT result;
	InvokeHelper(0x4127, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::NormSDist()
{
	VARIANT result;
	InvokeHelper(0x4126, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::NormSInv()
{
	VARIANT result;
	InvokeHelper(0x4128, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::NPer()
{
	VARIANT result;
	InvokeHelper(0x403a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Npv()
{
	VARIANT result;
	InvokeHelper(0x400b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Odd()
{
	VARIANT result;
	InvokeHelper(0x412a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::OnKey(const VARIANT& Key, const VARIANT& Procedure)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x272, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Key, &Procedure);
	return result;
}

VARIANT _Application5::OnRepeat(const VARIANT& Text, const VARIANT& Procedure)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x301, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Text, &Procedure);
	return result;
}

VARIANT _Application5::OnTime(const VARIANT& EarliestTime, const VARIANT& Procedure, const VARIANT& LatestTime, const VARIANT& Schedule)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x270, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&EarliestTime, &Procedure, &LatestTime, &Schedule);
	return result;
}

VARIANT _Application5::OnUndo(const VARIANT& Text, const VARIANT& Procedure)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x302, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Text, &Procedure);
	return result;
}

VARIANT _Application5::Or()
{
	VARIANT result;
	InvokeHelper(0x4025, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Pearson()
{
	VARIANT result;
	InvokeHelper(0x4138, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Percentile()
{
	VARIANT result;
	InvokeHelper(0x4148, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::PercentRank()
{
	VARIANT result;
	InvokeHelper(0x4149, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Permut()
{
	VARIANT result;
	InvokeHelper(0x412b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Pi()
{
	VARIANT result;
	InvokeHelper(0x4013, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Pmt()
{
	VARIANT result;
	InvokeHelper(0x403b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Poisson()
{
	VARIANT result;
	InvokeHelper(0x412c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Power()
{
	VARIANT result;
	InvokeHelper(0x4151, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Ppmt()
{
	VARIANT result;
	InvokeHelper(0x40a8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Prob()
{
	VARIANT result;
	InvokeHelper(0x413d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Product()
{
	VARIANT result;
	InvokeHelper(0x40b7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Proper()
{
	VARIANT result;
	InvokeHelper(0x4072, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Pv()
{
	VARIANT result;
	InvokeHelper(0x4038, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Quartile()
{
	VARIANT result;
	InvokeHelper(0x4147, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Quit()
{
	VARIANT result;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Radians()
{
	VARIANT result;
	InvokeHelper(0x4156, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Range(const VARIANT& Cell1, const VARIANT& Cell2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Cell1, &Cell2);
	return result;
}

VARIANT _Application5::Rank()
{
	VARIANT result;
	InvokeHelper(0x40d8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Rate()
{
	VARIANT result;
	InvokeHelper(0x403c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::RecordMacro(const VARIANT& BasicCode, const VARIANT& XlmCode)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x305, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&BasicCode, &XlmCode);
	return result;
}

VARIANT _Application5::RegisterXLL(const VARIANT& Filename)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename);
	return result;
}

VARIANT _Application5::Repeat()
{
	VARIANT result;
	InvokeHelper(0x12d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Replace()
{
	VARIANT result;
	InvokeHelper(0x4077, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::ReplaceB()
{
	VARIANT result;
	InvokeHelper(0x40cf, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Rept()
{
	VARIANT result;
	InvokeHelper(0x401e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::ResetTipWizard()
{
	VARIANT result;
	InvokeHelper(0x3a0, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Roman()
{
	VARIANT result;
	InvokeHelper(0x4162, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Round()
{
	VARIANT result;
	InvokeHelper(0x401b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::RoundDown()
{
	VARIANT result;
	InvokeHelper(0x40d5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::RoundUp()
{
	VARIANT result;
	InvokeHelper(0x40d4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Rows(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x102, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::RSq()
{
	VARIANT result;
	InvokeHelper(0x4139, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Run(const VARIANT& Macro, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, 
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, 
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, 
		const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Macro, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

VARIANT _Application5::Save(const VARIANT& Filename)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename);
	return result;
}

VARIANT _Application5::Search()
{
	VARIANT result;
	InvokeHelper(0x4052, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SearchB()
{
	VARIANT result;
	InvokeHelper(0x40ce, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SendKeys(const VARIANT& Keys, const VARIANT& Wait)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x17f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Keys, &Wait);
	return result;
}

VARIANT _Application5::SetDefaultChart(const VARIANT& FormatName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xdb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&FormatName);
	return result;
}

VARIANT _Application5::Sheets(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1e5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::ShortcutMenus(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x308, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Sinh()
{
	VARIANT result;
	InvokeHelper(0x40e5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Skew()
{
	VARIANT result;
	InvokeHelper(0x4143, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Sln()
{
	VARIANT result;
	InvokeHelper(0x408e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Slope()
{
	VARIANT result;
	InvokeHelper(0x413b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Small()
{
	VARIANT result;
	InvokeHelper(0x4146, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Standardize()
{
	VARIANT result;
	InvokeHelper(0x4129, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::StDev()
{
	VARIANT result;
	InvokeHelper(0x400c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::StDevP()
{
	VARIANT result;
	InvokeHelper(0x40c1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::StEyx()
{
	VARIANT result;
	InvokeHelper(0x413a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Substitute()
{
	VARIANT result;
	InvokeHelper(0x4078, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Subtotal()
{
	VARIANT result;
	InvokeHelper(0x4158, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Sum()
{
	VARIANT result;
	InvokeHelper(0x4004, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SumIf()
{
	VARIANT result;
	InvokeHelper(0x4159, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SumProduct()
{
	VARIANT result;
	InvokeHelper(0x40e4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SumSq()
{
	VARIANT result;
	InvokeHelper(0x4141, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SumX2MY2()
{
	VARIANT result;
	InvokeHelper(0x4130, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SumX2PY2()
{
	VARIANT result;
	InvokeHelper(0x4131, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::SumXMY2()
{
	VARIANT result;
	InvokeHelper(0x412f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Syd()
{
	VARIANT result;
	InvokeHelper(0x408f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Tanh()
{
	VARIANT result;
	InvokeHelper(0x40e7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::TDist()
{
	VARIANT result;
	InvokeHelper(0x412d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Text()
{
	VARIANT result;
	InvokeHelper(0x4030, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::TInv()
{
	VARIANT result;
	InvokeHelper(0x414c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Toolbars(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x228, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Transpose()
{
	VARIANT result;
	InvokeHelper(0x4053, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Trend()
{
	VARIANT result;
	InvokeHelper(0x4032, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Trim()
{
	VARIANT result;
	InvokeHelper(0x4076, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::TrimMean()
{
	VARIANT result;
	InvokeHelper(0x414b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::TTest()
{
	VARIANT result;
	InvokeHelper(0x413c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Undo()
{
	VARIANT result;
	InvokeHelper(0x12f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Union(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x30b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

VARIANT _Application5::USDollar()
{
	VARIANT result;
	InvokeHelper(0x40cc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Var()
{
	VARIANT result;
	InvokeHelper(0x402e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::VarP()
{
	VARIANT result;
	InvokeHelper(0x40c2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Vdb()
{
	VARIANT result;
	InvokeHelper(0x40de, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::VLookup()
{
	VARIANT result;
	InvokeHelper(0x4066, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Volatile(const VARIANT& Volatile)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x314, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Volatile);
	return result;
}

VARIANT _Application5::Wait(const VARIANT& Time)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x189, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Time);
	return result;
}

VARIANT _Application5::Weekday()
{
	VARIANT result;
	InvokeHelper(0x4046, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Weibull()
{
	VARIANT result;
	InvokeHelper(0x412e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Application5::Windows(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1ae, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Workbooks(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x23c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::Worksheets(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1ee, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Application5::ZTest()
{
	VARIANT result;
	InvokeHelper(0x4144, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}




// copied from excel8
long Workbooks5::GetCountLong()
{
	long result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Workbooks5 properties

VARIANT Workbooks5::GetCount()
{
	VARIANT result;
	GetProperty(0x76, VT_VARIANT, (void*)&result);
	return result;
}

void Workbooks5::SetCount(const VARIANT& propVal)
{
	SetProperty(0x76, VT_VARIANT, &propVal);
}

VARIANT Workbooks5::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void Workbooks5::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT Workbooks5::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void Workbooks5::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Workbooks5 operations

VARIANT Workbooks5::_NewEnum()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Workbooks5::Add(const VARIANT& Template)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Template);
	return result;
}

LPDISPATCH Workbooks5::Add() // added
{
	LPDISPATCH result;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT Workbooks5::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Workbooks5::Close()
{
	VARIANT result;
	InvokeHelper(0x115, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Workbooks5::Item(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Workbooks5::Open(const VARIANT& Filename, const VARIANT& UpdateLinks, const VARIANT& ReadOnly, const VARIANT& Format, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& IgnoreReadOnlyRecommended, const VARIANT& Origin, 
		const VARIANT& Delimiter, const VARIANT& Editable, const VARIANT& Notify, const VARIANT& Converter)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2aa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename, &UpdateLinks, &ReadOnly, &Format, &Password, &WriteResPassword, &IgnoreReadOnlyRecommended, &Origin, &Delimiter, &Editable, &Notify, &Converter);
	return result;
}

VARIANT Workbooks5::Open(const VARIANT& Filename)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2aa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename);
	return result;
}
VARIANT Workbooks5::OpenText(const VARIANT& Filename, const VARIANT& Origin, const VARIANT& StartRow, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, 
		const VARIANT& Comma, const VARIANT& Space, const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2ab, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename, &Origin, &StartRow, &DataType, &TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo);
	return result;
}



/////////////////////////////////////////////////////////////////////////////
// Worksheets5 properties

// copied from excel8

LPDISPATCH Worksheets5::GetItem(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}
/////////////////////////////////////////////////////////////////////////////
// Worksheets5 properties


VARIANT Worksheets5::GetCount()
{
	VARIANT result;
	GetProperty(0x76, VT_VARIANT, (void*)&result);
	return result;
}

void Worksheets5::SetCount(const VARIANT& propVal)
{
	SetProperty(0x76, VT_VARIANT, &propVal);
}

VARIANT Worksheets5::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void Worksheets5::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT Worksheets5::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void Worksheets5::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

VARIANT Worksheets5::GetVisible()
{
	VARIANT result;
	GetProperty(0x22e, VT_VARIANT, (void*)&result);
	return result;
}

void Worksheets5::SetVisible(const VARIANT& propVal)
{
	SetProperty(0x22e, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Worksheets5 operations
// copied from excel8
LPDISPATCH _Worksheet5::GetRange(const VARIANT& Cell1, const VARIANT& Cell2)
{
	LPDISPATCH result;
	static BYTE parms[] = VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, 
		parms,&Cell1, &Cell2);
	return result;
}

LPDISPATCH _Worksheet5::GetRange(const VARIANT& Cell1) // added
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, 
		parms,&Cell1);
	return result;
}
/////////////////////////////////////////////////////////////////////////////
// Worksheets5 operations

VARIANT Worksheets5::_NewEnum()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Worksheets5::Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count, const VARIANT& Type)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Before, &After, &Count, &Type);
	return result;
}

VARIANT Worksheets5::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Worksheets5::Copy(const VARIANT& Before, const VARIANT& After)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Before, &After);
	return result;
}

VARIANT Worksheets5::Delete()
{
	VARIANT result;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Worksheets5::FillAcrossSheets(const VARIANT& Range, const VARIANT& Type)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1d5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Range, &Type);
	return result;
}

VARIANT Worksheets5::Item(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Worksheets5::Move(const VARIANT& Before, const VARIANT& After)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x27d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Before, &After);
	return result;
}

VARIANT Worksheets5::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
	return result;
}

VARIANT Worksheets5::PrintPreview()
{
	VARIANT result;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Worksheets5::Select(const VARIANT& Replace)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Replace);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Worksheet5 properties

VARIANT _Worksheet5::GetAutoFilterMode()
{
	VARIANT result;
	GetProperty(0x318, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetAutoFilterMode(const VARIANT& propVal)
{
	SetProperty(0x318, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetCircularReference()
{
	VARIANT result;
	GetProperty(0x42d, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetCircularReference(const VARIANT& propVal)
{
	SetProperty(0x42d, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetConsolidationFunction()
{
	VARIANT result;
	GetProperty(0x315, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetConsolidationFunction(const VARIANT& propVal)
{
	SetProperty(0x315, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetConsolidationOptions()
{
	VARIANT result;
	GetProperty(0x316, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetConsolidationOptions(const VARIANT& propVal)
{
	SetProperty(0x316, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetConsolidationSources()
{
	VARIANT result;
	GetProperty(0x317, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetConsolidationSources(const VARIANT& propVal)
{
	SetProperty(0x317, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetDisplayAutomaticPageBreaks()
{
	VARIANT result;
	GetProperty(0x283, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetDisplayAutomaticPageBreaks(const VARIANT& propVal)
{
	SetProperty(0x283, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetEnableAutoFilter()
{
	VARIANT result;
	GetProperty(0x484, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetEnableAutoFilter(const VARIANT& propVal)
{
	SetProperty(0x484, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetEnableOutlining()
{
	VARIANT result;
	GetProperty(0x485, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetEnableOutlining(const VARIANT& propVal)
{
	SetProperty(0x485, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetEnablePivotTable()
{
	VARIANT result;
	GetProperty(0x486, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetEnablePivotTable(const VARIANT& propVal)
{
	SetProperty(0x486, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetFilterMode()
{
	VARIANT result;
	GetProperty(0x320, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetFilterMode(const VARIANT& propVal)
{
	SetProperty(0x320, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetIndex()
{
	VARIANT result;
	GetProperty(0x1e6, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetIndex(const VARIANT& propVal)
{
	SetProperty(0x1e6, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetName()
{
	VARIANT result;
	GetProperty(0x6e, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetName(const VARIANT& propVal)
{
	SetProperty(0x6e, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetNext()
{
	VARIANT result;
	GetProperty(0x1f6, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetNext(const VARIANT& propVal)
{
	SetProperty(0x1f6, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOnCalculate()
{
	VARIANT result;
	GetProperty(0x271, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOnCalculate(const VARIANT& propVal)
{
	SetProperty(0x271, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOnData()
{
	VARIANT result;
	GetProperty(0x275, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOnData(const VARIANT& propVal)
{
	SetProperty(0x275, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOnDoubleClick()
{
	VARIANT result;
	GetProperty(0x274, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOnDoubleClick(const VARIANT& propVal)
{
	SetProperty(0x274, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOnEntry()
{
	VARIANT result;
	GetProperty(0x273, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOnEntry(const VARIANT& propVal)
{
	SetProperty(0x273, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOnSheetActivate()
{
	VARIANT result;
	GetProperty(0x407, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOnSheetActivate(const VARIANT& propVal)
{
	SetProperty(0x407, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOnSheetDeactivate()
{
	VARIANT result;
	GetProperty(0x439, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOnSheetDeactivate(const VARIANT& propVal)
{
	SetProperty(0x439, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetOutline()
{
	VARIANT result;
	GetProperty(0x66, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetOutline(const VARIANT& propVal)
{
	SetProperty(0x66, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetPageSetup()
{
	VARIANT result;
	GetProperty(0x3e6, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetPageSetup(const VARIANT& propVal)
{
	SetProperty(0x3e6, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetPrevious()
{
	VARIANT result;
	GetProperty(0x1f7, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetPrevious(const VARIANT& propVal)
{
	SetProperty(0x1f7, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetProtectContents()
{
	VARIANT result;
	GetProperty(0x124, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetProtectContents(const VARIANT& propVal)
{
	SetProperty(0x124, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetProtectDrawingObjects()
{
	VARIANT result;
	GetProperty(0x125, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetProtectDrawingObjects(const VARIANT& propVal)
{
	SetProperty(0x125, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetProtectionMode()
{
	VARIANT result;
	GetProperty(0x487, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetProtectionMode(const VARIANT& propVal)
{
	SetProperty(0x487, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetProtectScenarios()
{
	VARIANT result;
	GetProperty(0x126, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetProtectScenarios(const VARIANT& propVal)
{
	SetProperty(0x126, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetStandardHeight()
{
	VARIANT result;
	GetProperty(0x197, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetStandardHeight(const VARIANT& propVal)
{
	SetProperty(0x197, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetStandardWidth()
{
	VARIANT result;
	GetProperty(0x198, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetStandardWidth(const VARIANT& propVal)
{
	SetProperty(0x198, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetTransitionExpEval()
{
	VARIANT result;
	GetProperty(0x191, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetTransitionExpEval(const VARIANT& propVal)
{
	SetProperty(0x191, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetTransitionFormEntry()
{
	VARIANT result;
	GetProperty(0x192, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetTransitionFormEntry(const VARIANT& propVal)
{
	SetProperty(0x192, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetType()
{
	VARIANT result;
	GetProperty(0x6c, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetType(const VARIANT& propVal)
{
	SetProperty(0x6c, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetUsedRange()
{
	VARIANT result;
	GetProperty(0x19c, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetUsedRange(const VARIANT& propVal)
{
	SetProperty(0x19c, VT_VARIANT, &propVal);
}

VARIANT _Worksheet5::GetVisible()
{
	VARIANT result;
	GetProperty(0x22e, VT_VARIANT, (void*)&result);
	return result;
}

void _Worksheet5::SetVisible(const VARIANT& propVal)
{
	SetProperty(0x22e, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// _Worksheet5 operations

VARIANT _Worksheet5::Activate()
{
	VARIANT result;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::Arcs(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2f8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Buttons(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x22d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Calculate()
{
	VARIANT result;
	InvokeHelper(0x117, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xee, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowIndex, &ColumnIndex);
	return result;
}

VARIANT _Worksheet5::ChartObjects(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x424, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::CheckBoxes(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x338, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&CustomDictionary, &IgnoreUppercase, &AlwaysSuggest);
	return result;
}

VARIANT _Worksheet5::ClearArrows()
{
	VARIANT result;
	InvokeHelper(0x3ca, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::Columns(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Copy(const VARIANT& Before, const VARIANT& After)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Before, &After);
	return result;
}

VARIANT _Worksheet5::Delete()
{
	VARIANT result;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::DrawingObjects(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x58, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Drawings(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x304, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::DropDowns(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x344, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::_Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT _Worksheet5::Evaluate(const VARIANT& Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xfffffffb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Name);
	return result;
}

VARIANT _Worksheet5::GroupBoxes(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x342, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::GroupObjects(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x459, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Labels(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x349, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Lines(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2ff, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::ListBoxes(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x340, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Move(const VARIANT& Before, const VARIANT& After)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x27d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Before, &After);
	return result;
}

VARIANT _Worksheet5::Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1ba, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index, &IndexLocal, &RefersTo);
	return result;
}

VARIANT _Worksheet5::OLEObjects(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x31f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::OptionButtons(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x33a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Ovals(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x321, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Paste(const VARIANT& Destination, const VARIANT& Link)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Destination, &Link);
	return result;
}

VARIANT _Worksheet5::PasteSpecial(const VARIANT& Format, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Format, &Link, &DisplayAsIcon, &IconFileName, &IconIndex, &IconLabel);
	return result;
}

VARIANT _Worksheet5::Pictures(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x303, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::PivotTables(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2b2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::PivotTableWizard(const VARIANT& SourceType, const VARIANT& SourceData, const VARIANT& TableDestination, const VARIANT& TableName, const VARIANT& RowGrand, const VARIANT& ColumnGrand, const VARIANT& SaveData, 
		const VARIANT& HasAutoFormat, const VARIANT& AutoPage, const VARIANT& Reserved)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2ac, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&SourceType, &SourceData, &TableDestination, &TableName, &RowGrand, &ColumnGrand, &SaveData, &HasAutoFormat, &AutoPage, &Reserved);
	return result;
}

VARIANT _Worksheet5::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
	return result;
}

VARIANT _Worksheet5::PrintPreview()
{
	VARIANT result;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Password, &DrawingObjects, &Contents, &Scenarios, &UserInterfaceOnly);
	return result;
}

VARIANT _Worksheet5::Range(const VARIANT& Cell1, const VARIANT& Cell2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Cell1, &Cell2);
	return result;
}

VARIANT _Worksheet5::Rectangles(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x306, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Rows(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x102, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x11c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename, &FileFormat, &Password, &WriteResPassword, &ReadOnlyRecommended, &CreateBackup);
	return result;
}

VARIANT _Worksheet5::Scenarios(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x38c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::ScrollBars(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x33e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Select(const VARIANT& Replace)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Replace);
	return result;
}

void _Worksheet5::Select() // added
{
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT _Worksheet5::SetBackgroundPicture(const VARIANT& Filename)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4a4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Filename);
	return result;
}

VARIANT _Worksheet5::ShowAllData()
{
	VARIANT result;
	InvokeHelper(0x31a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::ShowDataForm()
{
	VARIANT result;
	InvokeHelper(0x199, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT _Worksheet5::Spinners(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x346, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::TextBoxes(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x309, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT _Worksheet5::Unprotect(const VARIANT& Password)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Password);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// Range5 properties

VARIANT Range5::GetAddIndent()
{
	VARIANT result;
	GetProperty(0x427, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetAddIndent(const VARIANT& propVal)
{
	SetProperty(0x427, VT_VARIANT, &propVal);
}

VARIANT Range5::GetColumn()
{
	VARIANT result;
	GetProperty(0xf0, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetColumn(const VARIANT& propVal)
{
	SetProperty(0xf0, VT_VARIANT, &propVal);
}

VARIANT Range5::GetColumnWidth()
{
	VARIANT result;
	GetProperty(0xf2, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetColumnWidth(const VARIANT& propVal)
{
	SetProperty(0xf2, VT_VARIANT, &propVal);
}

VARIANT Range5::GetCount()
{
	VARIANT result;
	GetProperty(0x76, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetCount(const VARIANT& propVal)
{
	SetProperty(0x76, VT_VARIANT, &propVal);
}

VARIANT Range5::GetCreator()
{
	VARIANT result;
	GetProperty(0x95, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetCreator(const VARIANT& propVal)
{
	SetProperty(0x95, VT_VARIANT, &propVal);
}

VARIANT Range5::GetCurrentArray()
{
	VARIANT result;
	GetProperty(0x1f5, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetCurrentArray(const VARIANT& propVal)
{
	SetProperty(0x1f5, VT_VARIANT, &propVal);
}

VARIANT Range5::GetCurrentRegion()
{
	VARIANT result;
	GetProperty(0xf3, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetCurrentRegion(const VARIANT& propVal)
{
	SetProperty(0xf3, VT_VARIANT, &propVal);
}

VARIANT Range5::GetDependents()
{
	VARIANT result;
	GetProperty(0x21f, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetDependents(const VARIANT& propVal)
{
	SetProperty(0x21f, VT_VARIANT, &propVal);
}

VARIANT Range5::GetDirectDependents()
{
	VARIANT result;
	GetProperty(0x221, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetDirectDependents(const VARIANT& propVal)
{
	SetProperty(0x221, VT_VARIANT, &propVal);
}

VARIANT Range5::GetDirectPrecedents()
{
	VARIANT result;
	GetProperty(0x222, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetDirectPrecedents(const VARIANT& propVal)
{
	SetProperty(0x222, VT_VARIANT, &propVal);
}

VARIANT Range5::GetEntireColumn()
{
	VARIANT result;
	GetProperty(0xf6, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetEntireColumn(const VARIANT& propVal)
{
	SetProperty(0xf6, VT_VARIANT, &propVal);
}

VARIANT Range5::GetEntireRow()
{
	VARIANT result;
	GetProperty(0xf7, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetEntireRow(const VARIANT& propVal)
{
	SetProperty(0xf7, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFont()
{
	VARIANT result;
	GetProperty(0x92, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFont(const VARIANT& propVal)
{
	SetProperty(0x92, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFormula()
{
	VARIANT result;
	GetProperty(0x105, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFormula(const VARIANT& propVal)
{
	SetProperty(0x105, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFormulaArray()
{
	VARIANT result;
	GetProperty(0x24a, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFormulaArray(const VARIANT& propVal)
{
	SetProperty(0x24a, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFormulaHidden()
{
	VARIANT result;
	GetProperty(0x106, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFormulaHidden(const VARIANT& propVal)
{
	SetProperty(0x106, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFormulaLocal()
{
	VARIANT result;
	GetProperty(0x107, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFormulaLocal(const VARIANT& propVal)
{
	SetProperty(0x107, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFormulaR1C1()
{
	VARIANT result;
	GetProperty(0x108, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFormulaR1C1(const VARIANT& propVal)
{
	SetProperty(0x108, VT_VARIANT, &propVal);
}

VARIANT Range5::GetFormulaR1C1Local()
{
	VARIANT result;
	GetProperty(0x109, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetFormulaR1C1Local(const VARIANT& propVal)
{
	SetProperty(0x109, VT_VARIANT, &propVal);
}

VARIANT Range5::GetHasArray()
{
	VARIANT result;
	GetProperty(0x10a, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetHasArray(const VARIANT& propVal)
{
	SetProperty(0x10a, VT_VARIANT, &propVal);
}

VARIANT Range5::GetHasFormula()
{
	VARIANT result;
	GetProperty(0x10b, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetHasFormula(const VARIANT& propVal)
{
	SetProperty(0x10b, VT_VARIANT, &propVal);
}

VARIANT Range5::GetHeight()
{
	VARIANT result;
	GetProperty(0x7b, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetHeight(const VARIANT& propVal)
{
	SetProperty(0x7b, VT_VARIANT, &propVal);
}

VARIANT Range5::GetHidden()
{
	VARIANT result;
	GetProperty(0x10c, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetHidden(const VARIANT& propVal)
{
	SetProperty(0x10c, VT_VARIANT, &propVal);
}

VARIANT Range5::GetHorizontalAlignment()
{
	VARIANT result;
	GetProperty(0x88, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetHorizontalAlignment(const VARIANT& propVal)
{
	SetProperty(0x88, VT_VARIANT, &propVal);
}

VARIANT Range5::GetInterior()
{
	VARIANT result;
	GetProperty(0x81, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetInterior(const VARIANT& propVal)
{
	SetProperty(0x81, VT_VARIANT, &propVal);
}

VARIANT Range5::GetLeft()
{
	VARIANT result;
	GetProperty(0x7f, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetLeft(const VARIANT& propVal)
{
	SetProperty(0x7f, VT_VARIANT, &propVal);
}

VARIANT Range5::GetListHeaderRows()
{
	VARIANT result;
	GetProperty(0x4a3, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetListHeaderRows(const VARIANT& propVal)
{
	SetProperty(0x4a3, VT_VARIANT, &propVal);
}

VARIANT Range5::GetLocationInTable()
{
	VARIANT result;
	GetProperty(0x2b3, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetLocationInTable(const VARIANT& propVal)
{
	SetProperty(0x2b3, VT_VARIANT, &propVal);
}

VARIANT Range5::GetLocked()
{
	VARIANT result;
	GetProperty(0x10d, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetLocked(const VARIANT& propVal)
{
	SetProperty(0x10d, VT_VARIANT, &propVal);
}

VARIANT Range5::GetName()
{
	VARIANT result;
	GetProperty(0x6e, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetName(const VARIANT& propVal)
{
	SetProperty(0x6e, VT_VARIANT, &propVal);
}

VARIANT Range5::GetNext()
{
	VARIANT result;
	GetProperty(0x1f6, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetNext(const VARIANT& propVal)
{
	SetProperty(0x1f6, VT_VARIANT, &propVal);
}

VARIANT Range5::GetNumberFormat()
{
	VARIANT result;
	GetProperty(0xc1, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetNumberFormat(const VARIANT& propVal)
{
	SetProperty(0xc1, VT_VARIANT, &propVal);
}

VARIANT Range5::GetNumberFormatLocal()
{
	VARIANT result;
	GetProperty(0x449, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetNumberFormatLocal(const VARIANT& propVal)
{
	SetProperty(0x449, VT_VARIANT, &propVal);
}

VARIANT Range5::GetOrientation()
{
	VARIANT result;
	GetProperty(0x86, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetOrientation(const VARIANT& propVal)
{
	SetProperty(0x86, VT_VARIANT, &propVal);
}

VARIANT Range5::GetOutlineLevel()
{
	VARIANT result;
	GetProperty(0x10f, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetOutlineLevel(const VARIANT& propVal)
{
	SetProperty(0x10f, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPageBreak()
{
	VARIANT result;
	GetProperty(0xff, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPageBreak(const VARIANT& propVal)
{
	SetProperty(0xff, VT_VARIANT, &propVal);
}

VARIANT Range5::GetParent()
{
	VARIANT result;
	GetProperty(0x96, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetParent(const VARIANT& propVal)
{
	SetProperty(0x96, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPivotField()
{
	VARIANT result;
	GetProperty(0x2db, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPivotField(const VARIANT& propVal)
{
	SetProperty(0x2db, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPivotItem()
{
	VARIANT result;
	GetProperty(0x2e4, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPivotItem(const VARIANT& propVal)
{
	SetProperty(0x2e4, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPivotTable()
{
	VARIANT result;
	GetProperty(0x2cc, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPivotTable(const VARIANT& propVal)
{
	SetProperty(0x2cc, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPrecedents()
{
	VARIANT result;
	GetProperty(0x220, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPrecedents(const VARIANT& propVal)
{
	SetProperty(0x220, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPrefixCharacter()
{
	VARIANT result;
	GetProperty(0x1f8, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPrefixCharacter(const VARIANT& propVal)
{
	SetProperty(0x1f8, VT_VARIANT, &propVal);
}

VARIANT Range5::GetPrevious()
{
	VARIANT result;
	GetProperty(0x1f7, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetPrevious(const VARIANT& propVal)
{
	SetProperty(0x1f7, VT_VARIANT, &propVal);
}

VARIANT Range5::GetRow()
{
	VARIANT result;
	GetProperty(0x101, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetRow(const VARIANT& propVal)
{
	SetProperty(0x101, VT_VARIANT, &propVal);
}

VARIANT Range5::GetRowHeight()
{
	VARIANT result;
	GetProperty(0x110, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetRowHeight(const VARIANT& propVal)
{
	SetProperty(0x110, VT_VARIANT, &propVal);
}

VARIANT Range5::GetShowDetail()
{
	VARIANT result;
	GetProperty(0x249, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetShowDetail(const VARIANT& propVal)
{
	SetProperty(0x249, VT_VARIANT, &propVal);
}

VARIANT Range5::GetSoundNote()
{
	VARIANT result;
	GetProperty(0x394, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetSoundNote(const VARIANT& propVal)
{
	SetProperty(0x394, VT_VARIANT, &propVal);
}

VARIANT Range5::GetStyle()
{
	VARIANT result;
	GetProperty(0x104, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetStyle(const VARIANT& propVal)
{
	SetProperty(0x104, VT_VARIANT, &propVal);
}

VARIANT Range5::GetSummary()
{
	VARIANT result;
	GetProperty(0x111, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetSummary(const VARIANT& propVal)
{
	SetProperty(0x111, VT_VARIANT, &propVal);
}

VARIANT Range5::GetText()
{
	VARIANT result;
	GetProperty(0x8a, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetText(const VARIANT& propVal)
{
	SetProperty(0x8a, VT_VARIANT, &propVal);
}

VARIANT Range5::GetTop()
{
	VARIANT result;
	GetProperty(0x7e, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetTop(const VARIANT& propVal)
{
	SetProperty(0x7e, VT_VARIANT, &propVal);
}

VARIANT Range5::GetUseStandardHeight()
{
	VARIANT result;
	GetProperty(0x112, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetUseStandardHeight(const VARIANT& propVal)
{
	SetProperty(0x112, VT_VARIANT, &propVal);
}

VARIANT Range5::GetUseStandardWidth()
{
	VARIANT result;
	GetProperty(0x113, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetUseStandardWidth(const VARIANT& propVal)
{
	SetProperty(0x113, VT_VARIANT, &propVal);
}

VARIANT Range5::GetValue()
{
	VARIANT result;
	GetProperty(0x6, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetValue(const VARIANT& propVal)
{
	SetProperty(0x6, VT_VARIANT, &propVal);
}

VARIANT Range5::GetVerticalAlignment()
{
	VARIANT result;
	GetProperty(0x89, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetVerticalAlignment(const VARIANT& propVal)
{
	SetProperty(0x89, VT_VARIANT, &propVal);
}

VARIANT Range5::GetWidth()
{
	VARIANT result;
	GetProperty(0x7a, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetWidth(const VARIANT& propVal)
{
	SetProperty(0x7a, VT_VARIANT, &propVal);
}

VARIANT Range5::GetWrapText()
{
	VARIANT result;
	GetProperty(0x114, VT_VARIANT, (void*)&result);
	return result;
}

void Range5::SetWrapText(const VARIANT& propVal)
{
	SetProperty(0x114, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// Range5 operations

VARIANT Range5::_Dummy(const VARIANT& Activate, const VARIANT& DirectObject)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Activate, &DirectObject);
	return result;
}

VARIANT Range5::_NewEnum()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Activate()
{
	VARIANT result;
	InvokeHelper(0x130, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Address(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, const VARIANT& ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xec, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowAbsolute, &ColumnAbsolute, &ReferenceStyle, &External, &RelativeTo);
	return result;
}

VARIANT Range5::AddressLocal(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, const VARIANT& ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1b5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowAbsolute, &ColumnAbsolute, &ReferenceStyle, &External, &RelativeTo);
	return result;
}

VARIANT Range5::AdvancedFilter(const VARIANT& Action, const VARIANT& CriteriaRange, const VARIANT& CopyToRange, const VARIANT& Unique)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x36c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Action, &CriteriaRange, &CopyToRange, &Unique);
	return result;
}

VARIANT Range5::Application()
{
	VARIANT result;
	InvokeHelper(0x94, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ApplyNames(const VARIANT& Names, const VARIANT& IgnoreRelativeAbsolute, const VARIANT& UseRowColumnNames, const VARIANT& OmitColumn, const VARIANT& OmitRow, const VARIANT& Order, const VARIANT& AppendLast)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1b9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Names, &IgnoreRelativeAbsolute, &UseRowColumnNames, &OmitColumn, &OmitRow, &Order, &AppendLast);
	return result;
}

VARIANT Range5::ApplyOutlineStyles()
{
	VARIANT result;
	InvokeHelper(0x1c0, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Areas(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x238, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Range5::AutoComplete(const VARIANT& String)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4a1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&String);
	return result;
}

VARIANT Range5::AutoFill(const VARIANT& Destination, const VARIANT& Type)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1c1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Destination, &Type);
	return result;
}

VARIANT Range5::AutoFilter(const VARIANT& Field, const VARIANT& Criteria1, const VARIANT& Operator, const VARIANT& Criteria2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x319, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Field, &Criteria1, &Operator, &Criteria2);
	return result;
}

VARIANT Range5::AutoFit()
{
	VARIANT result;
	InvokeHelper(0xed, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::AutoFormat(const VARIANT& Format, const VARIANT& Number, const VARIANT& Font, const VARIANT& Alignment, const VARIANT& Border, const VARIANT& Pattern, const VARIANT& Width)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x72, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Format, &Number, &Font, &Alignment, &Border, &Pattern, &Width);
	return result;
}

VARIANT Range5::AutoOutline()
{
	VARIANT result;
	InvokeHelper(0x40c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::BorderAround(const VARIANT& LineStyle, const VARIANT& Weight, const VARIANT& ColorIndex, const VARIANT& Color)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x42b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&LineStyle, &Weight, &ColorIndex, &Color);
	return result;
}

VARIANT Range5::Borders(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1b3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Range5::Calculate()
{
	VARIANT result;
	InvokeHelper(0x117, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xee, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowIndex, &ColumnIndex);
	return result;
}

VARIANT Range5::Characters(const VARIANT& Start, const VARIANT& Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x25b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Start, &Length);
	return result;
}

VARIANT Range5::CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&CustomDictionary, &IgnoreUppercase, &AlwaysSuggest);
	return result;
}

VARIANT Range5::Clear()
{
	VARIANT result;
	InvokeHelper(0x6f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ClearContents()
{
	VARIANT result;
	InvokeHelper(0x71, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ClearFormats()
{
	VARIANT result;
	InvokeHelper(0x70, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ClearNotes()
{
	VARIANT result;
	InvokeHelper(0xef, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ClearOutline()
{
	VARIANT result;
	InvokeHelper(0x40d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ColumnDifferences(const VARIANT& Comparison)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1fe, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Comparison);
	return result;
}

VARIANT Range5::Columns(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Range5::Consolidate(const VARIANT& Sources, const VARIANT& Function, const VARIANT& TopRow, const VARIANT& LeftColumn, const VARIANT& CreateLinks)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1e2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Sources, &Function, &TopRow, &LeftColumn, &CreateLinks);
	return result;
}

VARIANT Range5::Copy(const VARIANT& Destination)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x227, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Destination);
	return result;
}

VARIANT Range5::CopyFromRecordset(const VARIANT& Data, const VARIANT& MaxRows, const VARIANT& MaxColumns)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x480, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Data, &MaxRows, &MaxColumns);
	return result;
}

VARIANT Range5::CopyPicture(const VARIANT& Appearance, const VARIANT& Format)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Appearance, &Format);
	return result;
}

VARIANT Range5::CreateNames(const VARIANT& Top, const VARIANT& Left, const VARIANT& Bottom, const VARIANT& Right)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1c9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Top, &Left, &Bottom, &Right);
	return result;
}

VARIANT Range5::CreatePublisher(const VARIANT& Edition, const VARIANT& Appearance, const VARIANT& ContainsPICT, const VARIANT& ContainsBIFF, const VARIANT& ContainsRTF, const VARIANT& ContainsVALU)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1ca, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Edition, &Appearance, &ContainsPICT, &ContainsBIFF, &ContainsRTF, &ContainsVALU);
	return result;
}

VARIANT Range5::Cut(const VARIANT& Destination)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x235, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Destination);
	return result;
}

VARIANT Range5::DataSeries(const VARIANT& Rowcol, const VARIANT& Type, const VARIANT& Date, const VARIANT& Step, const VARIANT& Stop, const VARIANT& Trend)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1d0, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Rowcol, &Type, &Date, &Step, &Stop, &Trend);
	return result;
}

VARIANT Range5::Delete(const VARIANT& Shift)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x75, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Shift);
	return result;
}

VARIANT Range5::DialogBox_()
{
	VARIANT result;
	InvokeHelper(0xf5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::End(const VARIANT& Direction)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1f4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Direction);
	return result;
}

VARIANT Range5::FillDown()
{
	VARIANT result;
	InvokeHelper(0xf8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::FillLeft()
{
	VARIANT result;
	InvokeHelper(0xf9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::FillRight()
{
	VARIANT result;
	InvokeHelper(0xfa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::FillUp()
{
	VARIANT result;
	InvokeHelper(0xfb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Find(const VARIANT& What, const VARIANT& After, const VARIANT& LookIn, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& SearchDirection, const VARIANT& MatchCase, const VARIANT& MatchByte)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x18e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&What, &After, &LookIn, &LookAt, &SearchOrder, &SearchDirection, &MatchCase, &MatchByte);
	return result;
}

VARIANT Range5::FindNext(const VARIANT& After)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x18f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&After);
	return result;
}

VARIANT Range5::FindPrevious(const VARIANT& After)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x190, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&After);
	return result;
}

VARIANT Range5::FunctionWizard()
{
	VARIANT result;
	InvokeHelper(0x23b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::GoalSeek(const VARIANT& Goal, const VARIANT& ChangingCell)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1d8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Goal, &ChangingCell);
	return result;
}

VARIANT Range5::Group(const VARIANT& Start, const VARIANT& End, const VARIANT& By, const VARIANT& Periods)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Start, &End, &By, &Periods);
	return result;
}

VARIANT Range5::Insert(const VARIANT& Shift)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xfc, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Shift);
	return result;
}

VARIANT Range5::Item(const VARIANT& RowIndex, const VARIANT& ColumnIndex)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xaa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowIndex, &ColumnIndex);
	return result;
}

VARIANT Range5::Justify()
{
	VARIANT result;
	InvokeHelper(0x1ef, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ListNames()
{
	VARIANT result;
	InvokeHelper(0xfd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::NavigateArrow(const VARIANT& TowardPrecedent, const VARIANT& ArrowNumber, const VARIANT& LinkNumber)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x408, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&TowardPrecedent, &ArrowNumber, &LinkNumber);
	return result;
}

VARIANT Range5::NoteText(const VARIANT& Text, const VARIANT& Start, const VARIANT& Length)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x467, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Text, &Start, &Length);
	return result;
}

VARIANT Range5::Offset(const VARIANT& RowOffset, const VARIANT& ColumnOffset)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xfe, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowOffset, &ColumnOffset);
	return result;
}

VARIANT Range5::Parse(const VARIANT& ParseLine, const VARIANT& Destination)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1dd, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ParseLine, &Destination);
	return result;
}

VARIANT Range5::PasteSpecial(const VARIANT& Paste, const VARIANT& Operation, const VARIANT& SkipBlanks, const VARIANT& Transpose)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Paste, &Operation, &SkipBlanks, &Transpose);
	return result;
}

VARIANT Range5::PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x389, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate);
	return result;
}

VARIANT Range5::PrintPreview()
{
	VARIANT result;
	InvokeHelper(0x119, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Range(const VARIANT& Cell1, const VARIANT& Cell2)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Cell1, &Cell2);
	return result;
}

VARIANT Range5::RemoveSubtotal()
{
	VARIANT result;
	InvokeHelper(0x373, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Replace(const VARIANT& What, const VARIANT& Replacement, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& MatchCase, const VARIANT& MatchByte)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xe2, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&What, &Replacement, &LookAt, &SearchOrder, &MatchCase, &MatchByte);
	return result;
}

VARIANT Range5::Resize(const VARIANT& RowSize, const VARIANT& ColumnSize)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x100, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowSize, &ColumnSize);
	return result;
}

VARIANT Range5::RowDifferences(const VARIANT& Comparison)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1ff, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Comparison);
	return result;
}

VARIANT Range5::Rows(const VARIANT& Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x102, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Index);
	return result;
}

VARIANT Range5::Run(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT 
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x103, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
	return result;
}

VARIANT Range5::Select()
{
	VARIANT result;
	InvokeHelper(0xeb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Show()
{
	VARIANT result;
	InvokeHelper(0x1f0, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ShowDependents(const VARIANT& Remove)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x36d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Remove);
	return result;
}

VARIANT Range5::ShowErrors()
{
	VARIANT result;
	InvokeHelper(0x36e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::ShowPrecedents(const VARIANT& Remove)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x36f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Remove);
	return result;
}

VARIANT Range5::Sort(const VARIANT& Key1, const VARIANT& Order1, const VARIANT& Key2, const VARIANT& Type, const VARIANT& Order2, const VARIANT& Key3, const VARIANT& Order3, const VARIANT& Header, const VARIANT& OrderCustom, const VARIANT& MatchCase, 
		const VARIANT& Orientation)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x370, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Key1, &Order1, &Key2, &Type, &Order2, &Key3, &Order3, &Header, &OrderCustom, &MatchCase, &Orientation);
	return result;
}

VARIANT Range5::SortSpecial(const VARIANT& SortMethod, const VARIANT& Key1, const VARIANT& Order1, const VARIANT& Type, const VARIANT& Key2, const VARIANT& Order2, const VARIANT& Key3, const VARIANT& Order3, const VARIANT& Header, 
		const VARIANT& OrderCustom, const VARIANT& MatchCase, const VARIANT& Orientation)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x371, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&SortMethod, &Key1, &Order1, &Type, &Key2, &Order2, &Key3, &Order3, &Header, &OrderCustom, &MatchCase, &Orientation);
	return result;
}

VARIANT Range5::SpecialCells(const VARIANT& Type, const VARIANT& Value)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x19a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Type, &Value);
	return result;
}

VARIANT Range5::SubscribeTo(const VARIANT& Edition, const VARIANT& Format)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1e1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Edition, &Format);
	return result;
}

VARIANT Range5::Subtotal(const VARIANT& GroupBy, const VARIANT& Function, const VARIANT& TotalList, const VARIANT& Replace, const VARIANT& PageBreaks, const VARIANT& SummaryBelowData)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x372, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&GroupBy, &Function, &TotalList, &Replace, &PageBreaks, &SummaryBelowData);
	return result;
}

VARIANT Range5::Table(const VARIANT& RowInput, const VARIANT& ColumnInput)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x1f1, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&RowInput, &ColumnInput);
	return result;
}

VARIANT Range5::TextToColumns(const VARIANT& Destination, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, const VARIANT& Comma, const VARIANT& Space, 
		const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x410, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Destination, &DataType, &TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo);
	return result;
}

VARIANT Range5::Ungroup()
{
	VARIANT result;
	InvokeHelper(0xf4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT Range5::Worksheet()
{
	VARIANT result;
	InvokeHelper(0x15c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}
