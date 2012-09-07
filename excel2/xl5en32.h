// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _Global wrapper class

class _Global : public COleDispatchDriver
{
public:
	_Global() {}		// Calls COleDispatchDriver default constructor
	_Global(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Global(const _Global& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetActiveCell();
	void SetActiveCell(const VARIANT&);
	VARIANT GetActiveChart();
	void SetActiveChart(const VARIANT&);
	VARIANT GetActiveDialog();
	void SetActiveDialog(const VARIANT&);
	VARIANT GetActiveMenuBar();
	void SetActiveMenuBar(const VARIANT&);
	VARIANT GetActivePrinter();
	void SetActivePrinter(const VARIANT&);
	VARIANT GetActiveSheet();
	void SetActiveSheet(const VARIANT&);
	VARIANT GetActiveWindow();
	void SetActiveWindow(const VARIANT&);
	VARIANT GetActiveWorkbook();
	void SetActiveWorkbook(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDDEAppReturnCode();
	void SetDDEAppReturnCode(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetSelection();
	void SetSelection(const VARIANT&);
	VARIANT GetThisWorkbook();
	void SetThisWorkbook(const VARIANT&);

// Operations
public:
	VARIANT AddIns(const VARIANT& Index);
	VARIANT Application();
	VARIANT Calculate();
	VARIANT Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT Charts(const VARIANT& Index);
	VARIANT Columns(const VARIANT& Index);
	VARIANT DDEExecute(const VARIANT& Channel, const VARIANT& String);
	VARIANT DDEInitiate(const VARIANT& App, const VARIANT& Topic);
	VARIANT DDEPoke(const VARIANT& Channel, const VARIANT& Item, const VARIANT& Data);
	VARIANT DDERequest(const VARIANT& Channel, const VARIANT& Item);
	VARIANT DDETerminate(const VARIANT& Channel);
	VARIANT DialogSheets(const VARIANT& Index);
	VARIANT _Evaluate(const VARIANT& Name);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT Excel4IntlMacroSheets(const VARIANT& Index);
	VARIANT Excel4MacroSheets(const VARIANT& Index);
	VARIANT ExecuteExcel4Macro(const VARIANT& String);
	VARIANT Intersect(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
	VARIANT MenuBars(const VARIANT& Index);
	VARIANT Modules(const VARIANT& Index);
	VARIANT Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo);
	VARIANT Range(const VARIANT& Cell1, const VARIANT& Cell2);
	VARIANT Rows(const VARIANT& Index);
	VARIANT Run(const VARIANT& Macro, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, 
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, 
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, 
		const VARIANT& Arg30);
	VARIANT SendKeys(const VARIANT& Keys, const VARIANT& Wait);
	VARIANT Sheets(const VARIANT& Index);
	VARIANT ShortcutMenus(const VARIANT& Index);
	VARIANT Toolbars(const VARIANT& Index);
	VARIANT Union(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
	VARIANT Windows(const VARIANT& Index);
	VARIANT Workbooks(const VARIANT& Index);
	VARIANT Worksheets(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Application wrapper class

class Application : public COleDispatchDriver
{
public:
	Application() {}		// Calls COleDispatchDriver default constructor
	Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Application(const Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetActiveCell();
	void SetActiveCell(const VARIANT&);
	VARIANT GetActiveChart();
	void SetActiveChart(const VARIANT&);
	VARIANT GetActiveDialog();
	void SetActiveDialog(const VARIANT&);
	VARIANT GetActiveMenuBar();
	void SetActiveMenuBar(const VARIANT&);
	VARIANT GetActivePrinter();
	void SetActivePrinter(const VARIANT&);
	VARIANT GetActiveSheet();
	void SetActiveSheet(const VARIANT&);
	VARIANT GetActiveWindow();
	void SetActiveWindow(const VARIANT&);
	VARIANT GetActiveWorkbook();
	void SetActiveWorkbook(const VARIANT&);
	VARIANT GetAlertBeforeOverwriting();
	void SetAlertBeforeOverwriting(const VARIANT&);
	VARIANT GetAltStartupPath();
	void SetAltStartupPath(const VARIANT&);
	VARIANT GetAskToUpdateLinks();
	void SetAskToUpdateLinks(const VARIANT&);
	VARIANT GetAutoCorrect();
	void SetAutoCorrect(const VARIANT&);
	VARIANT GetBuild();
	void SetBuild(const VARIANT&);
	VARIANT GetCalculateBeforeSave();
	void SetCalculateBeforeSave(const VARIANT&);
	VARIANT GetCalculation();
	void SetCalculation(const VARIANT&);
	VARIANT GetCaller();
	void SetCaller(const VARIANT&);
	VARIANT GetCanPlaySounds();
	void SetCanPlaySounds(const VARIANT&);
	VARIANT GetCanRecordSounds();
	void SetCanRecordSounds(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCellDragAndDrop();
	void SetCellDragAndDrop(const VARIANT&);
	VARIANT GetClipboardFormats();
	void SetClipboardFormats(const VARIANT&);
	VARIANT GetColorButtons();
	void SetColorButtons(const VARIANT&);
	VARIANT GetCommandUnderlines();
	void SetCommandUnderlines(const VARIANT&);
	VARIANT GetConstrainNumeric();
	void SetConstrainNumeric(const VARIANT&);
	VARIANT GetCopyObjectsWithCells();
	void SetCopyObjectsWithCells(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetCursor();
	void SetCursor(const VARIANT&);
	VARIANT GetCustomListCount();
	void SetCustomListCount(const VARIANT&);
	VARIANT GetCutCopyMode();
	void SetCutCopyMode(const VARIANT&);
	VARIANT GetDataEntryMode();
	void SetDataEntryMode(const VARIANT&);
	VARIANT GetDDEAppReturnCode();
	void SetDDEAppReturnCode(const VARIANT&);
	VARIANT GetDefaultFilePath();
	void SetDefaultFilePath(const VARIANT&);
	VARIANT GetDisplayAlerts();
	void SetDisplayAlerts(const VARIANT&);
	VARIANT GetDisplayClipboardWindow();
	void SetDisplayClipboardWindow(const VARIANT&);
	VARIANT GetDisplayExcel4Menus();
	void SetDisplayExcel4Menus(const VARIANT&);
	VARIANT GetDisplayFormulaBar();
	void SetDisplayFormulaBar(const VARIANT&);
	VARIANT GetDisplayFullScreen();
	void SetDisplayFullScreen(const VARIANT&);
	VARIANT GetDisplayInfoWindow();
	void SetDisplayInfoWindow(const VARIANT&);
	VARIANT GetDisplayNoteIndicator();
	void SetDisplayNoteIndicator(const VARIANT&);
	VARIANT GetDisplayRecentFiles();
	void SetDisplayRecentFiles(const VARIANT&);
	VARIANT GetDisplayScrollBars();
	void SetDisplayScrollBars(const VARIANT&);
	VARIANT GetDisplayStatusBar();
	void SetDisplayStatusBar(const VARIANT&);
	VARIANT GetEditDirectlyInCell();
	void SetEditDirectlyInCell(const VARIANT&);
	VARIANT GetEnableAnimations();
	void SetEnableAnimations(const VARIANT&);
	VARIANT GetEnableAutoComplete();
	void SetEnableAutoComplete(const VARIANT&);
	VARIANT GetEnableCancelKey();
	void SetEnableCancelKey(const VARIANT&);
	VARIANT GetEnableTipWizard();
	void SetEnableTipWizard(const VARIANT&);
	VARIANT GetFileConverters();
	void SetFileConverters(const VARIANT&);
	VARIANT GetFixedDecimal();
	void SetFixedDecimal(const VARIANT&);
	VARIANT GetFixedDecimalPlaces();
	void SetFixedDecimalPlaces(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIgnoreRemoteRequests();
	void SetIgnoreRemoteRequests(const VARIANT&);
	VARIANT GetInteractive();
	void SetInteractive(const VARIANT&);
	VARIANT GetInternational();
	void SetInternational(const VARIANT&);
	VARIANT GetIteration();
	void SetIteration(const VARIANT&);
	VARIANT GetLargeButtons();
	void SetLargeButtons(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLibraryPath();
	void SetLibraryPath(const VARIANT&);
	VARIANT GetMailSession();
	void SetMailSession(const VARIANT&);
	VARIANT GetMailSystem();
	void SetMailSystem(const VARIANT&);
	VARIANT GetMathCoprocessorAvailable();
	void SetMathCoprocessorAvailable(const VARIANT&);
	VARIANT GetMaxChange();
	void SetMaxChange(const VARIANT&);
	VARIANT GetMaxIterations();
	void SetMaxIterations(const VARIANT&);
	VARIANT GetMemoryFree();
	void SetMemoryFree(const VARIANT&);
	VARIANT GetMemoryTotal();
	void SetMemoryTotal(const VARIANT&);
	VARIANT GetMemoryUsed();
	void SetMemoryUsed(const VARIANT&);
	VARIANT GetMouseAvailable();
	void SetMouseAvailable(const VARIANT&);
	VARIANT GetMoveAfterReturn();
	void SetMoveAfterReturn(const VARIANT&);
	VARIANT GetMoveAfterReturnDirection();
	void SetMoveAfterReturnDirection(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNetworkTemplatesPath();
	void SetNetworkTemplatesPath(const VARIANT&);
	VARIANT GetOnCalculate();
	void SetOnCalculate(const VARIANT&);
	VARIANT GetOnData();
	void SetOnData(const VARIANT&);
	VARIANT GetOnDoubleClick();
	void SetOnDoubleClick(const VARIANT&);
	VARIANT GetOnEntry();
	void SetOnEntry(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetOnWindow();
	void SetOnWindow(const VARIANT&);
	VARIANT GetOperatingSystem();
	void SetOperatingSystem(const VARIANT&);
	VARIANT GetOrganizationName();
	void SetOrganizationName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPath();
	void SetPath(const VARIANT&);
	VARIANT GetPathSeparator();
	void SetPathSeparator(const VARIANT&);
	VARIANT GetPreviousSelections();
	void SetPreviousSelections(const VARIANT&);
	VARIANT GetPromptForSummaryInfo();
	void SetPromptForSummaryInfo(const VARIANT&);
	VARIANT GetRecordRelative();
	void SetRecordRelative(const VARIANT&);
	VARIANT GetReferenceStyle();
	void SetReferenceStyle(const VARIANT&);
	VARIANT GetRegisteredFunctions();
	void SetRegisteredFunctions(const VARIANT&);
	VARIANT GetScreenUpdating();
	void SetScreenUpdating(const VARIANT&);
	VARIANT GetSelection();
	void SetSelection(const VARIANT&);
	VARIANT GetSheetsInNewWorkbook();
	void SetSheetsInNewWorkbook(const VARIANT&);
	VARIANT GetShowToolTips();
	void SetShowToolTips(const VARIANT&);
	VARIANT GetStandardFont();
	void SetStandardFont(const VARIANT&);
	VARIANT GetStandardFontSize();
	void SetStandardFontSize(const VARIANT&);
	VARIANT GetStartupPath();
	void SetStartupPath(const VARIANT&);
	VARIANT GetStatusBar();
	void SetStatusBar(const VARIANT&);
	VARIANT GetTemplatesPath();
	void SetTemplatesPath(const VARIANT&);
	VARIANT GetThisWorkbook();
	void SetThisWorkbook(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTransitionMenuKey();
	void SetTransitionMenuKey(const VARIANT&);
	VARIANT GetTransitionMenuKeyAction();
	void SetTransitionMenuKeyAction(const VARIANT&);
	VARIANT GetTransitionNavigKeys();
	void SetTransitionNavigKeys(const VARIANT&);
	VARIANT GetUsableHeight();
	void SetUsableHeight(const VARIANT&);
	VARIANT GetUsableWidth();
	void SetUsableWidth(const VARIANT&);
	VARIANT GetUserName();
	void SetUserName(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVersion();
	void SetVersion(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetWindowsForPens();
	void SetWindowsForPens(const VARIANT&);
	VARIANT GetWindowState();
	void SetWindowState(const VARIANT&);

// Operations
public:
	VARIANT _WSFunction(const VARIANT& Range, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, 
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, 
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, 
		const VARIANT& Arg30);
	VARIANT Acos();
	VARIANT Acosh();
	VARIANT ActivateMicrosoftApp(const VARIANT& Index);
	VARIANT AddChartAutoFormat(const VARIANT& Chart, const VARIANT& Name, const VARIANT& Description);
	VARIANT AddCustomList(const VARIANT& ListArray, const VARIANT& ByRow);
	VARIANT AddIns(const VARIANT& Index);
	VARIANT And();
	VARIANT Application_();
	VARIANT Asin();
	VARIANT Asinh();
	VARIANT Atan2();
	VARIANT Atanh();
	VARIANT AveDev();
	VARIANT Average();
	VARIANT BetaDist();
	VARIANT BetaInv();
	VARIANT BinomDist();
	VARIANT Calculate();
	VARIANT Ceiling();
	VARIANT Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT CentimetersToPoints(const VARIANT& Centimeters);
	VARIANT Charts(const VARIANT& Index);
	VARIANT CheckSpelling(const VARIANT& Word, const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase);
	VARIANT ChiDist();
	VARIANT ChiInv();
	VARIANT ChiTest();
	VARIANT Choose();
	VARIANT Clean();
	VARIANT Columns(const VARIANT& Index);
	VARIANT Combin();
	VARIANT Confidence();
	VARIANT ConvertFormula(const VARIANT& Formula, const VARIANT& FromReferenceStyle, const VARIANT& ToReferenceStyle, const VARIANT& ToAbsolute, const VARIANT& RelativeTo);
	VARIANT Correl();
	VARIANT Cosh();
	VARIANT Count();
	VARIANT CountA();
	VARIANT CountBlank();
	VARIANT CountIf();
	VARIANT Covar();
	VARIANT CritBinom();
	VARIANT DAverage();
	VARIANT Days360();
	VARIANT Db();
	VARIANT DCount();
	VARIANT DCountA();
	VARIANT Ddb();
	VARIANT DDEExecute(const VARIANT& Channel, const VARIANT& String);
	VARIANT DDEInitiate(const VARIANT& App, const VARIANT& Topic);
	VARIANT DDEPoke(const VARIANT& Channel, const VARIANT& Item, const VARIANT& Data);
	VARIANT DDERequest(const VARIANT& Channel, const VARIANT& Item);
	VARIANT DDETerminate(const VARIANT& Channel);
	VARIANT Degrees();
	VARIANT DeleteChartAutoFormat(const VARIANT& Name);
	VARIANT DeleteCustomList(const VARIANT& ListNum);
	VARIANT DevSq();
	VARIANT DGet();
	VARIANT Dialogs(const VARIANT& Index);
	VARIANT DialogSheets(const VARIANT& Index);
	VARIANT DMax();
	VARIANT DMin();
	VARIANT Dollar();
	VARIANT DoubleClick();
	VARIANT DProduct();
	VARIANT DStDev();
	VARIANT DStDevP();
	VARIANT DSum();
	VARIANT DVar();
	VARIANT DVarP();
	VARIANT _Evaluate(const VARIANT& Name);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT Even();
	VARIANT Excel4IntlMacroSheets(const VARIANT& Index);
	VARIANT Excel4MacroSheets(const VARIANT& Index);
	VARIANT ExecuteExcel4Macro(const VARIANT& String);
	VARIANT ExponDist();
	VARIANT Fact();
	VARIANT FDist();
	VARIANT Find();
	VARIANT FindB();
	VARIANT FindFile();
	VARIANT FInv();
	VARIANT Fisher();
	VARIANT FisherInv();
	VARIANT Fixed();
	VARIANT Floor();
	VARIANT Forecast();
	VARIANT Frequency();
	VARIANT FTest();
	VARIANT Fv();
	VARIANT GammaDist();
	VARIANT GammaInv();
	VARIANT GammaLn();
	VARIANT GeoMean();
	VARIANT GetCustomListContents(const VARIANT& ListNum);
	VARIANT GetCustomListNum(const VARIANT& ListArray);
	VARIANT GetOpenFilename(const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText, const VARIANT& MultiSelect);
	VARIANT GetSaveAsFilename(const VARIANT& InitialFilename, const VARIANT& FileFilter, const VARIANT& FilterIndex, const VARIANT& Title, const VARIANT& ButtonText);
	VARIANT Goto(const VARIANT& Reference, const VARIANT& Scroll);
	VARIANT Growth();
	VARIANT HarMean();
	VARIANT Help(const VARIANT& HelpFile, const VARIANT& HelpContextID);
	VARIANT HLookup();
	VARIANT HypGeomDist();
	VARIANT InchesToPoints(const VARIANT& Inches);
	VARIANT Index();
	VARIANT InputBox(const VARIANT& Prompt, const VARIANT& Title, const VARIANT& Default, const VARIANT& Left, const VARIANT& Top, const VARIANT& HelpFile, const VARIANT& HelpContextID, const VARIANT& Type);
	VARIANT Intercept();
	VARIANT Intersect(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
	VARIANT Ipmt();
	VARIANT Irr();
	VARIANT IsErr();
	VARIANT IsError();
	VARIANT IsLogical();
	VARIANT IsNA();
	VARIANT IsNonText();
	VARIANT IsNumber();
	VARIANT Ispmt();
	VARIANT IsText();
	VARIANT Kurt();
	VARIANT Large();
	VARIANT LinEst();
	VARIANT Ln();
	VARIANT Log();
	VARIANT Log10();
	VARIANT LogEst();
	VARIANT LogInv();
	VARIANT LogNormDist();
	VARIANT Lookup();
	VARIANT MacroOptions(const VARIANT& Macro, const VARIANT& Description, const VARIANT& HasMenu, const VARIANT& MenuText, const VARIANT& HasShortcutKey, const VARIANT& ShortcutKey, const VARIANT& Category, const VARIANT& StatusBar, 
		const VARIANT& HelpContextID, const VARIANT& HelpFile);
	VARIANT MailLogoff();
	VARIANT MailLogon(const VARIANT& Name, const VARIANT& Password, const VARIANT& DownloadNewMail);
	VARIANT Match();
	VARIANT Max();
	VARIANT MDeterm();
	VARIANT Median();
	VARIANT MenuBars(const VARIANT& Index);
	VARIANT Min();
	VARIANT MInverse();
	VARIANT MIrr();
	VARIANT MMult();
	VARIANT Mode();
	VARIANT Modules(const VARIANT& Index);
	VARIANT Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo);
	VARIANT NegBinomDist();
	VARIANT NextLetter();
	VARIANT NormDist();
	VARIANT NormInv();
	VARIANT NormSDist();
	VARIANT NormSInv();
	VARIANT NPer();
	VARIANT Npv();
	VARIANT Odd();
	VARIANT OnKey(const VARIANT& Key, const VARIANT& Procedure);
	VARIANT OnRepeat(const VARIANT& Text, const VARIANT& Procedure);
	VARIANT OnTime(const VARIANT& EarliestTime, const VARIANT& Procedure, const VARIANT& LatestTime, const VARIANT& Schedule);
	VARIANT OnUndo(const VARIANT& Text, const VARIANT& Procedure);
	VARIANT Or();
	VARIANT Pearson();
	VARIANT Percentile();
	VARIANT PercentRank();
	VARIANT Permut();
	VARIANT Pi();
	VARIANT Pmt();
	VARIANT Poisson();
	VARIANT Power();
	VARIANT Ppmt();
	VARIANT Prob();
	VARIANT Product();
	VARIANT Proper();
	VARIANT Pv();
	VARIANT Quartile();
	VARIANT Quit();
	VARIANT Radians();
	VARIANT Range(const VARIANT& Cell1, const VARIANT& Cell2);
	VARIANT Rank();
	VARIANT Rate();
	VARIANT RecordMacro(const VARIANT& BasicCode, const VARIANT& XlmCode);
	VARIANT RegisterXLL(const VARIANT& Filename);
	VARIANT Repeat();
	VARIANT Replace();
	VARIANT ReplaceB();
	VARIANT Rept();
	VARIANT ResetTipWizard();
	VARIANT Roman();
	VARIANT Round();
	VARIANT RoundDown();
	VARIANT RoundUp();
	VARIANT Rows(const VARIANT& Index);
	VARIANT RSq();
	VARIANT Run(const VARIANT& Macro, const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, 
		const VARIANT& Arg10, const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, 
		const VARIANT& Arg20, const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, 
		const VARIANT& Arg30);
	VARIANT Save(const VARIANT& Filename);
	VARIANT Search();
	VARIANT SearchB();
	VARIANT SendKeys(const VARIANT& Keys, const VARIANT& Wait);
	VARIANT SetDefaultChart(const VARIANT& FormatName);
	VARIANT Sheets(const VARIANT& Index);
	VARIANT ShortcutMenus(const VARIANT& Index);
	VARIANT Sinh();
	VARIANT Skew();
	VARIANT Sln();
	VARIANT Slope();
	VARIANT Small();
	VARIANT Standardize();
	VARIANT StDev();
	VARIANT StDevP();
	VARIANT StEyx();
	VARIANT Substitute();
	VARIANT Subtotal();
	VARIANT Sum();
	VARIANT SumIf();
	VARIANT SumProduct();
	VARIANT SumSq();
	VARIANT SumX2MY2();
	VARIANT SumX2PY2();
	VARIANT SumXMY2();
	VARIANT Syd();
	VARIANT Tanh();
	VARIANT TDist();
	VARIANT Text();
	VARIANT TInv();
	VARIANT Toolbars(const VARIANT& Index);
	VARIANT Transpose();
	VARIANT Trend();
	VARIANT Trim();
	VARIANT TrimMean();
	VARIANT TTest();
	VARIANT Undo();
	VARIANT Union(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
	VARIANT USDollar();
	VARIANT Var();
	VARIANT VarP();
	VARIANT Vdb();
	VARIANT VLookup();
	VARIANT Volatile(const VARIANT& Volatile);
	VARIANT Wait(const VARIANT& Time);
	VARIANT Weekday();
	VARIANT Weibull();
	VARIANT Windows(const VARIANT& Index);
	VARIANT Workbooks(const VARIANT& Index);
	VARIANT Worksheets(const VARIANT& Index);
	VARIANT ZTest();
};
/////////////////////////////////////////////////////////////////////////////
// Style wrapper class

class Style : public COleDispatchDriver
{
public:
	Style() {}		// Calls COleDispatchDriver default constructor
	Style(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Style(const Style& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormulaHidden();
	void SetFormulaHidden(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetIncludeAlignment();
	void SetIncludeAlignment(const VARIANT&);
	VARIANT GetIncludeBorder();
	void SetIncludeBorder(const VARIANT&);
	VARIANT GetIncludeFont();
	void SetIncludeFont(const VARIANT&);
	VARIANT GetIncludeNumber();
	void SetIncludeNumber(const VARIANT&);
	VARIANT GetIncludePatterns();
	void SetIncludePatterns(const VARIANT&);
	VARIANT GetIncludeProtection();
	void SetIncludeProtection(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNameLocal();
	void SetNameLocal(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetNumberFormatLocal();
	void SetNumberFormatLocal(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetWrapText();
	void SetWrapText(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Borders(const VARIANT& Index);
	VARIANT Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Styles wrapper class

class Styles : public COleDispatchDriver
{
public:
	Styles() {}		// Calls COleDispatchDriver default constructor
	Styles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Styles(const Styles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Name, const VARIANT& BasedOn);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
	VARIANT Merge(const VARIANT& Workbook);
};
/////////////////////////////////////////////////////////////////////////////
// Toolbar wrapper class

class Toolbar : public COleDispatchDriver
{
public:
	Toolbar() {}		// Calls COleDispatchDriver default constructor
	Toolbar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Toolbar(const Toolbar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBuiltIn();
	void SetBuiltIn(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPosition();
	void SetPosition(const VARIANT&);
	VARIANT GetProtection();
	void SetProtection(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Reset();
	VARIANT ToolbarButtons(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Toolbars wrapper class

class Toolbars : public COleDispatchDriver
{
public:
	Toolbars() {}		// Calls COleDispatchDriver default constructor
	Toolbars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Toolbars(const Toolbars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Name);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// ToolbarButton wrapper class

class ToolbarButton : public COleDispatchDriver
{
public:
	ToolbarButton() {}		// Calls COleDispatchDriver default constructor
	ToolbarButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ToolbarButton(const ToolbarButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBuiltIn();
	void SetBuiltIn(const VARIANT&);
	VARIANT GetBuiltInFace();
	void SetBuiltInFace(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHelpContextID();
	void SetHelpContextID(const VARIANT&);
	VARIANT GetHelpFile();
	void SetHelpFile(const VARIANT&);
	VARIANT GetId();
	void SetId(const VARIANT&);
	VARIANT GetIsGap();
	void SetIsGap(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPushed();
	void SetPushed(const VARIANT&);
	VARIANT GetStatusBar();
	void SetStatusBar(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Copy(const VARIANT& Toolbar, const VARIANT& Before);
	VARIANT CopyFace();
	VARIANT Delete();
	VARIANT Edit();
	VARIANT Move(const VARIANT& Toolbar, const VARIANT& Before);
	VARIANT PasteFace();
	VARIANT Reset();
};
/////////////////////////////////////////////////////////////////////////////
// ToolbarButtons wrapper class

class ToolbarButtons : public COleDispatchDriver
{
public:
	ToolbarButtons() {}		// Calls COleDispatchDriver default constructor
	ToolbarButtons(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ToolbarButtons(const ToolbarButtons& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Button, const VARIANT& Before, const VARIANT& OnAction, const VARIANT& Pushed, const VARIANT& Enabled, const VARIANT& StatusBar, const VARIANT& HelpFile, const VARIANT& HelpContextID);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// AddIn wrapper class

class AddIn : public COleDispatchDriver
{
public:
	AddIn() {}		// Calls COleDispatchDriver default constructor
	AddIn(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddIn(const AddIn& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAuthor();
	void SetAuthor(const VARIANT&);
	VARIANT GetComments();
	void SetComments(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFullName();
	void SetFullName(const VARIANT&);
	VARIANT GetInstalled();
	void SetInstalled(const VARIANT&);
	VARIANT GetKeywords();
	void SetKeywords(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPath();
	void SetPath(const VARIANT&);
	VARIANT GetSubject();
	void SetSubject(const VARIANT&);
	VARIANT GetTitle();
	void SetTitle(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// AddIns wrapper class

class AddIns : public COleDispatchDriver
{
public:
	AddIns() {}		// Calls COleDispatchDriver default constructor
	AddIns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AddIns(const AddIns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Filename, const VARIANT& CopyFile);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Areas wrapper class

class Areas : public COleDispatchDriver
{
public:
	Areas() {}		// Calls COleDispatchDriver default constructor
	Areas(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Areas(const Areas& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Range wrapper class

class Range : public COleDispatchDriver
{
public:
	Range() {}		// Calls COleDispatchDriver default constructor
	Range(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Range(const Range& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetColumn();
	void SetColumn(const VARIANT&);
	VARIANT GetColumnWidth();
	void SetColumnWidth(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetCurrentArray();
	void SetCurrentArray(const VARIANT&);
	VARIANT GetCurrentRegion();
	void SetCurrentRegion(const VARIANT&);
	VARIANT GetDependents();
	void SetDependents(const VARIANT&);
	VARIANT GetDirectDependents();
	void SetDirectDependents(const VARIANT&);
	VARIANT GetDirectPrecedents();
	void SetDirectPrecedents(const VARIANT&);
	VARIANT GetEntireColumn();
	void SetEntireColumn(const VARIANT&);
	VARIANT GetEntireRow();
	void SetEntireRow(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetFormulaArray();
	void SetFormulaArray(const VARIANT&);
	VARIANT GetFormulaHidden();
	void SetFormulaHidden(const VARIANT&);
	VARIANT GetFormulaLocal();
	void SetFormulaLocal(const VARIANT&);
	VARIANT GetFormulaR1C1();
	void SetFormulaR1C1(const VARIANT&);
	VARIANT GetFormulaR1C1Local();
	void SetFormulaR1C1Local(const VARIANT&);
	VARIANT GetHasArray();
	void SetHasArray(const VARIANT&);
	VARIANT GetHasFormula();
	void SetHasFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHidden();
	void SetHidden(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetListHeaderRows();
	void SetListHeaderRows(const VARIANT&);
	VARIANT GetLocationInTable();
	void SetLocationInTable(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetNumberFormatLocal();
	void SetNumberFormatLocal(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetOutlineLevel();
	void SetOutlineLevel(const VARIANT&);
	VARIANT GetPageBreak();
	void SetPageBreak(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPivotField();
	void SetPivotField(const VARIANT&);
	VARIANT GetPivotItem();
	void SetPivotItem(const VARIANT&);
	VARIANT GetPivotTable();
	void SetPivotTable(const VARIANT&);
	VARIANT GetPrecedents();
	void SetPrecedents(const VARIANT&);
	VARIANT GetPrefixCharacter();
	void SetPrefixCharacter(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetRow();
	void SetRow(const VARIANT&);
	VARIANT GetRowHeight();
	void SetRowHeight(const VARIANT&);
	VARIANT GetShowDetail();
	void SetShowDetail(const VARIANT&);
	VARIANT GetSoundNote();
	void SetSoundNote(const VARIANT&);
	VARIANT GetStyle();
	void SetStyle(const VARIANT&);
	VARIANT GetSummary();
	void SetSummary(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetUseStandardHeight();
	void SetUseStandardHeight(const VARIANT&);
	VARIANT GetUseStandardWidth();
	void SetUseStandardWidth(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetWrapText();
	void SetWrapText(const VARIANT&);

// Operations
public:
	VARIANT _Dummy(const VARIANT& Activate, const VARIANT& DirectObject);
	VARIANT _NewEnum();
	VARIANT Activate();
	VARIANT Address(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, const VARIANT& ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo);
	VARIANT AddressLocal(const VARIANT& RowAbsolute, const VARIANT& ColumnAbsolute, const VARIANT& ReferenceStyle, const VARIANT& External, const VARIANT& RelativeTo);
	VARIANT AdvancedFilter(const VARIANT& Action, const VARIANT& CriteriaRange, const VARIANT& CopyToRange, const VARIANT& Unique);
	VARIANT Application();
	VARIANT ApplyNames(const VARIANT& Names, const VARIANT& IgnoreRelativeAbsolute, const VARIANT& UseRowColumnNames, const VARIANT& OmitColumn, const VARIANT& OmitRow, const VARIANT& Order, const VARIANT& AppendLast);
	VARIANT ApplyOutlineStyles();
	VARIANT Areas(const VARIANT& Index);
	VARIANT AutoComplete(const VARIANT& String);
	VARIANT AutoFill(const VARIANT& Destination, const VARIANT& Type);
	VARIANT AutoFilter(const VARIANT& Field, const VARIANT& Criteria1, const VARIANT& Operator, const VARIANT& Criteria2);
	VARIANT AutoFit();
	VARIANT AutoFormat(const VARIANT& Format, const VARIANT& Number, const VARIANT& Font, const VARIANT& Alignment, const VARIANT& Border, const VARIANT& Pattern, const VARIANT& Width);
	VARIANT AutoOutline();
	VARIANT BorderAround(const VARIANT& LineStyle, const VARIANT& Weight, const VARIANT& ColorIndex, const VARIANT& Color);
	VARIANT Borders(const VARIANT& Index);
	VARIANT Calculate();
	VARIANT Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Clear();
	VARIANT ClearContents();
	VARIANT ClearFormats();
	VARIANT ClearNotes();
	VARIANT ClearOutline();
	VARIANT ColumnDifferences(const VARIANT& Comparison);
	VARIANT Columns(const VARIANT& Index);
	VARIANT Consolidate(const VARIANT& Sources, const VARIANT& Function, const VARIANT& TopRow, const VARIANT& LeftColumn, const VARIANT& CreateLinks);
	VARIANT Copy(const VARIANT& Destination);
	VARIANT CopyFromRecordset(const VARIANT& Data, const VARIANT& MaxRows, const VARIANT& MaxColumns);
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT CreateNames(const VARIANT& Top, const VARIANT& Left, const VARIANT& Bottom, const VARIANT& Right);
	VARIANT CreatePublisher(const VARIANT& Edition, const VARIANT& Appearance, const VARIANT& ContainsPICT, const VARIANT& ContainsBIFF, const VARIANT& ContainsRTF, const VARIANT& ContainsVALU);
	VARIANT Cut(const VARIANT& Destination);
	VARIANT DataSeries(const VARIANT& Rowcol, const VARIANT& Type, const VARIANT& Date, const VARIANT& Step, const VARIANT& Stop, const VARIANT& Trend);
	VARIANT Delete(const VARIANT& Shift);
	VARIANT DialogBox_();
	VARIANT End(const VARIANT& Direction);
	VARIANT FillDown();
	VARIANT FillLeft();
	VARIANT FillRight();
	VARIANT FillUp();
	VARIANT Find(const VARIANT& What, const VARIANT& After, const VARIANT& LookIn, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& SearchDirection, const VARIANT& MatchCase, const VARIANT& MatchByte);
	VARIANT FindNext(const VARIANT& After);
	VARIANT FindPrevious(const VARIANT& After);
	VARIANT FunctionWizard();
	VARIANT GoalSeek(const VARIANT& Goal, const VARIANT& ChangingCell);
	VARIANT Group(const VARIANT& Start, const VARIANT& End, const VARIANT& By, const VARIANT& Periods);
	VARIANT Insert(const VARIANT& Shift);
	VARIANT Item(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT Justify();
	VARIANT ListNames();
	VARIANT NavigateArrow(const VARIANT& TowardPrecedent, const VARIANT& ArrowNumber, const VARIANT& LinkNumber);
	VARIANT NoteText(const VARIANT& Text, const VARIANT& Start, const VARIANT& Length);
	VARIANT Offset(const VARIANT& RowOffset, const VARIANT& ColumnOffset);
	VARIANT Parse(const VARIANT& ParseLine, const VARIANT& Destination);
	VARIANT PasteSpecial(const VARIANT& Paste, const VARIANT& Operation, const VARIANT& SkipBlanks, const VARIANT& Transpose);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Range_(const VARIANT& Cell1, const VARIANT& Cell2);
	VARIANT RemoveSubtotal();
	VARIANT Replace(const VARIANT& What, const VARIANT& Replacement, const VARIANT& LookAt, const VARIANT& SearchOrder, const VARIANT& MatchCase, const VARIANT& MatchByte);
	VARIANT Resize(const VARIANT& RowSize, const VARIANT& ColumnSize);
	VARIANT RowDifferences(const VARIANT& Comparison);
	VARIANT Rows(const VARIANT& Index);
	VARIANT Run(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
	VARIANT Select();
	VARIANT Show();
	VARIANT ShowDependents(const VARIANT& Remove);
	VARIANT ShowErrors();
	VARIANT ShowPrecedents(const VARIANT& Remove);
	VARIANT Sort(const VARIANT& Key1, const VARIANT& Order1, const VARIANT& Key2, const VARIANT& Type, const VARIANT& Order2, const VARIANT& Key3, const VARIANT& Order3, const VARIANT& Header, const VARIANT& OrderCustom, const VARIANT& MatchCase, 
		const VARIANT& Orientation);
	VARIANT SortSpecial(const VARIANT& SortMethod, const VARIANT& Key1, const VARIANT& Order1, const VARIANT& Type, const VARIANT& Key2, const VARIANT& Order2, const VARIANT& Key3, const VARIANT& Order3, const VARIANT& Header, 
		const VARIANT& OrderCustom, const VARIANT& MatchCase, const VARIANT& Orientation);
	VARIANT SpecialCells(const VARIANT& Type, const VARIANT& Value);
	VARIANT SubscribeTo(const VARIANT& Edition, const VARIANT& Format);
	VARIANT Subtotal(const VARIANT& GroupBy, const VARIANT& Function, const VARIANT& TotalList, const VARIANT& Replace, const VARIANT& PageBreaks, const VARIANT& SummaryBelowData);
	VARIANT Table(const VARIANT& RowInput, const VARIANT& ColumnInput);
	VARIANT TextToColumns(const VARIANT& Destination, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, const VARIANT& Comma, const VARIANT& Space, 
		const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo);
	VARIANT Ungroup();
	VARIANT Worksheet();
};
/////////////////////////////////////////////////////////////////////////////
// Workbook wrapper class

class Workbook : public COleDispatchDriver
{
public:
	Workbook() {}		// Calls COleDispatchDriver default constructor
	Workbook(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Workbook(const Workbook& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetActiveChart();
	void SetActiveChart(const VARIANT&);
	VARIANT GetActiveSheet();
	void SetActiveSheet(const VARIANT&);
	VARIANT GetAuthor();
	void SetAuthor(const VARIANT&);
	VARIANT GetColors();
	void SetColors(const VARIANT&);
	VARIANT GetComments();
	void SetComments(const VARIANT&);
	VARIANT GetContainer();
	void SetContainer(const VARIANT&);
	VARIANT GetCreateBackup();
	void SetCreateBackup(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDate1904();
	void SetDate1904(const VARIANT&);
	VARIANT GetDisplayDrawingObjects();
	void SetDisplayDrawingObjects(const VARIANT&);
	VARIANT GetFileFormat();
	void SetFileFormat(const VARIANT&);
	VARIANT GetFullName();
	void SetFullName(const VARIANT&);
	VARIANT GetHasMailer();
	void SetHasMailer(const VARIANT&);
	VARIANT GetHasPassword();
	void SetHasPassword(const VARIANT&);
	VARIANT GetHasRoutingSlip();
	void SetHasRoutingSlip(const VARIANT&);
	VARIANT GetKeywords();
	void SetKeywords(const VARIANT&);
	VARIANT GetMailer();
	void SetMailer(const VARIANT&);
	VARIANT GetMultiUserEditing();
	void SetMultiUserEditing(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnSave();
	void SetOnSave(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPath();
	void SetPath(const VARIANT&);
	VARIANT GetPrecisionAsDisplayed();
	void SetPrecisionAsDisplayed(const VARIANT&);
	VARIANT GetProtectStructure();
	void SetProtectStructure(const VARIANT&);
	VARIANT GetProtectWindows();
	void SetProtectWindows(const VARIANT&);
	VARIANT GetReadOnly();
	void SetReadOnly(const VARIANT&);
	VARIANT GetReadOnlyRecommended();
	void SetReadOnlyRecommended(const VARIANT&);
	VARIANT GetRevisionNumber();
	void SetRevisionNumber(const VARIANT&);
	VARIANT GetRouted();
	void SetRouted(const VARIANT&);
	VARIANT GetRoutingSlip();
	void SetRoutingSlip(const VARIANT&);
	VARIANT GetSaved();
	void SetSaved(const VARIANT&);
	VARIANT GetSaveLinkValues();
	void SetSaveLinkValues(const VARIANT&);
	VARIANT GetShowConflictHistory();
	void SetShowConflictHistory(const VARIANT&);
	VARIANT GetSubject();
	void SetSubject(const VARIANT&);
	VARIANT GetTitle();
	void SetTitle(const VARIANT&);
	VARIANT GetUpdateRemoteReferences();
	void SetUpdateRemoteReferences(const VARIANT&);
	VARIANT GetUserStatus();
	void SetUserStatus(const VARIANT&);
	VARIANT GetWriteReserved();
	void SetWriteReserved(const VARIANT&);
	VARIANT GetWriteReservedBy();
	void SetWriteReservedBy(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT BuiltinDocumentProperties(const VARIANT& Index);
	VARIANT ChangeFileAccess(const VARIANT& Mode, const VARIANT& WritePassword, const VARIANT& Notify);
	VARIANT ChangeLink(const VARIANT& Name, const VARIANT& NewName, const VARIANT& Type);
	VARIANT Charts(const VARIANT& Index);
	VARIANT Close(const VARIANT& SaveChanges, const VARIANT& Filename, const VARIANT& RouteWorkbook);
	VARIANT CustomDocumentProperties(const VARIANT& Index);
	VARIANT DeleteNumberFormat(const VARIANT& NumberFormat);
	VARIANT DialogSheets(const VARIANT& Index);
	VARIANT Excel4IntlMacroSheets(const VARIANT& Index);
	VARIANT Excel4MacroSheets(const VARIANT& Index);
	VARIANT ExclusiveAccess();
	VARIANT ForwardMailer();
	VARIANT LinkInfo(const VARIANT& Name, const VARIANT& LinkInfo, const VARIANT& Type, const VARIANT& EditionRef);
	VARIANT LinkSources(const VARIANT& Type);
	VARIANT Modules(const VARIANT& Index);
	VARIANT Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo);
	VARIANT NewWindow();
	VARIANT OpenLinks(const VARIANT& Name, const VARIANT& ReadOnly, const VARIANT& Type);
	VARIANT Post(const VARIANT& DestName);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Protect(const VARIANT& Password, const VARIANT& Structure, const VARIANT& Windows);
	VARIANT Reply();
	VARIANT ReplyAll();
	VARIANT Route();
	VARIANT RunAutoMacros(const VARIANT& Which);
	VARIANT Save();
	VARIANT SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup, const VARIANT& AccessMode, 
		const VARIANT& ConflictResolution);
	VARIANT SaveCopyAs(const VARIANT& Filename);
	VARIANT SendMail(const VARIANT& Recipients, const VARIANT& Subject, const VARIANT& ReturnReceipt);
	VARIANT SendMailer(const VARIANT& FileFormat, const VARIANT& Priority);
	VARIANT SetLinkOnData(const VARIANT& Name, const VARIANT& Procedure);
	VARIANT Sheets(const VARIANT& Index);
	VARIANT Styles(const VARIANT& Index);
	VARIANT Unprotect(const VARIANT& Password);
	VARIANT UpdateFromFile();
	VARIANT UpdateLink(const VARIANT& Name, const VARIANT& Type);
	VARIANT Windows(const VARIANT& Index);
	VARIANT Worksheets(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Workbooks wrapper class

class Workbooks : public COleDispatchDriver
{
public:
	Workbooks() {}		// Calls COleDispatchDriver default constructor
	Workbooks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Workbooks(const Workbooks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Template);
	VARIANT Application();
	VARIANT Close();
	VARIANT Item(const VARIANT& Index);
	VARIANT Open(const VARIANT& Filename, const VARIANT& UpdateLinks, const VARIANT& ReadOnly, const VARIANT& Format, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& IgnoreReadOnlyRecommended, const VARIANT& Origin, 
		const VARIANT& Delimiter, const VARIANT& Editable, const VARIANT& Notify, const VARIANT& Converter);
	VARIANT OpenText(const VARIANT& Filename, const VARIANT& Origin, const VARIANT& StartRow, const VARIANT& DataType, const VARIANT& TextQualifier, const VARIANT& ConsecutiveDelimiter, const VARIANT& Tab, const VARIANT& Semicolon, 
		const VARIANT& Comma, const VARIANT& Space, const VARIANT& Other, const VARIANT& OtherChar, const VARIANT& FieldInfo);
};
/////////////////////////////////////////////////////////////////////////////
// Sheets wrapper class

class Sheets : public COleDispatchDriver
{
public:
	Sheets() {}		// Calls COleDispatchDriver default constructor
	Sheets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Sheets(const Sheets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count, const VARIANT& Type);
	VARIANT Application();
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT FillAcrossSheets(const VARIANT& Range, const VARIANT& Type);
	VARIANT Item(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Select(const VARIANT& Replace);
};
/////////////////////////////////////////////////////////////////////////////
// Worksheet wrapper class

class Worksheet : public COleDispatchDriver
{
public:
	Worksheet() {}		// Calls COleDispatchDriver default constructor
	Worksheet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Worksheet(const Worksheet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAutoFilterMode();
	void SetAutoFilterMode(const VARIANT&);
	VARIANT GetCircularReference();
	void SetCircularReference(const VARIANT&);
	VARIANT GetConsolidationFunction();
	void SetConsolidationFunction(const VARIANT&);
	VARIANT GetConsolidationOptions();
	void SetConsolidationOptions(const VARIANT&);
	VARIANT GetConsolidationSources();
	void SetConsolidationSources(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplayAutomaticPageBreaks();
	void SetDisplayAutomaticPageBreaks(const VARIANT&);
	VARIANT GetEnableAutoFilter();
	void SetEnableAutoFilter(const VARIANT&);
	VARIANT GetEnableOutlining();
	void SetEnableOutlining(const VARIANT&);
	VARIANT GetEnablePivotTable();
	void SetEnablePivotTable(const VARIANT&);
	VARIANT GetFilterMode();
	void SetFilterMode(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetOnCalculate();
	void SetOnCalculate(const VARIANT&);
	VARIANT GetOnData();
	void SetOnData(const VARIANT&);
	VARIANT GetOnDoubleClick();
	void SetOnDoubleClick(const VARIANT&);
	VARIANT GetOnEntry();
	void SetOnEntry(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetOutline();
	void SetOutline(const VARIANT&);
	VARIANT GetPageSetup();
	void SetPageSetup(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetProtectContents();
	void SetProtectContents(const VARIANT&);
	VARIANT GetProtectDrawingObjects();
	void SetProtectDrawingObjects(const VARIANT&);
	VARIANT GetProtectionMode();
	void SetProtectionMode(const VARIANT&);
	VARIANT GetProtectScenarios();
	void SetProtectScenarios(const VARIANT&);
	VARIANT GetStandardHeight();
	void SetStandardHeight(const VARIANT&);
	VARIANT GetStandardWidth();
	void SetStandardWidth(const VARIANT&);
	VARIANT GetTransitionExpEval();
	void SetTransitionExpEval(const VARIANT&);
	VARIANT GetTransitionFormEntry();
	void SetTransitionFormEntry(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetUsedRange();
	void SetUsedRange(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT Arcs(const VARIANT& Index);
	VARIANT Buttons(const VARIANT& Index);
	VARIANT Calculate();
	VARIANT Cells(const VARIANT& RowIndex, const VARIANT& ColumnIndex);
	VARIANT ChartObjects(const VARIANT& Index);
	VARIANT CheckBoxes(const VARIANT& Index);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT ClearArrows();
	VARIANT Columns(const VARIANT& Index);
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT DrawingObjects(const VARIANT& Index);
	VARIANT Drawings(const VARIANT& Index);
	VARIANT DropDowns(const VARIANT& Index);
	VARIANT _Evaluate(const VARIANT& Name);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT GroupBoxes(const VARIANT& Index);
	VARIANT GroupObjects(const VARIANT& Index);
	VARIANT Labels(const VARIANT& Index);
	VARIANT Lines(const VARIANT& Index);
	VARIANT ListBoxes(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo);
	VARIANT OLEObjects(const VARIANT& Index);
	VARIANT OptionButtons(const VARIANT& Index);
	VARIANT Ovals(const VARIANT& Index);
	VARIANT Paste(const VARIANT& Destination, const VARIANT& Link);
	VARIANT PasteSpecial(const VARIANT& Format, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel);
	VARIANT Pictures(const VARIANT& Index);
	VARIANT PivotTables(const VARIANT& Index);
	VARIANT PivotTableWizard(const VARIANT& SourceType, const VARIANT& SourceData, const VARIANT& TableDestination, const VARIANT& TableName, const VARIANT& RowGrand, const VARIANT& ColumnGrand, const VARIANT& SaveData, 
		const VARIANT& HasAutoFormat, const VARIANT& AutoPage, const VARIANT& Reserved);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly);
	VARIANT Range(const VARIANT& Cell1, const VARIANT& Cell2);
	VARIANT Rectangles(const VARIANT& Index);
	VARIANT Rows(const VARIANT& Index);
	VARIANT SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup);
	VARIANT Scenarios(const VARIANT& Index);
	VARIANT ScrollBars(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SetBackgroundPicture(const VARIANT& Filename);
	VARIANT ShowAllData();
	VARIANT ShowDataForm();
	VARIANT Spinners(const VARIANT& Index);
	VARIANT TextBoxes(const VARIANT& Index);
	VARIANT Unprotect(const VARIANT& Password);
};
/////////////////////////////////////////////////////////////////////////////
// Worksheets wrapper class

class Worksheets : public COleDispatchDriver
{
public:
	Worksheets() {}		// Calls COleDispatchDriver default constructor
	Worksheets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Worksheets(const Worksheets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count, const VARIANT& Type);
	VARIANT Application();
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT FillAcrossSheets(const VARIANT& Range, const VARIANT& Type);
	VARIANT Item(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Select(const VARIANT& Replace);
};
/////////////////////////////////////////////////////////////////////////////
// PivotTable wrapper class

class PivotTable : public COleDispatchDriver
{
public:
	PivotTable() {}		// Calls COleDispatchDriver default constructor
	PivotTable(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PivotTable(const PivotTable& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetColumnFields();
	void SetColumnFields(const VARIANT&);
	VARIANT GetColumnGrand();
	void SetColumnGrand(const VARIANT&);
	VARIANT GetColumnRange();
	void SetColumnRange(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDataBodyRange();
	void SetDataBodyRange(const VARIANT&);
	VARIANT GetDataFields();
	void SetDataFields(const VARIANT&);
	VARIANT GetDataLabelRange();
	void SetDataLabelRange(const VARIANT&);
	VARIANT GetHasAutoFormat();
	void SetHasAutoFormat(const VARIANT&);
	VARIANT GetHiddenFields();
	void SetHiddenFields(const VARIANT&);
	VARIANT GetInnerDetail();
	void SetInnerDetail(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetPageFields();
	void SetPageFields(const VARIANT&);
	VARIANT GetPageRange();
	void SetPageRange(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetRefreshDate();
	void SetRefreshDate(const VARIANT&);
	VARIANT GetRefreshName();
	void SetRefreshName(const VARIANT&);
	VARIANT GetRowFields();
	void SetRowFields(const VARIANT&);
	VARIANT GetRowGrand();
	void SetRowGrand(const VARIANT&);
	VARIANT GetRowRange();
	void SetRowRange(const VARIANT&);
	VARIANT GetSaveData();
	void SetSaveData(const VARIANT&);
	VARIANT GetSourceData();
	void SetSourceData(const VARIANT&);
	VARIANT GetTableRange1();
	void SetTableRange1(const VARIANT&);
	VARIANT GetTableRange2();
	void SetTableRange2(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisibleFields();
	void SetVisibleFields(const VARIANT&);

// Operations
public:
	VARIANT AddFields(const VARIANT& RowFields, const VARIANT& ColumnFields, const VARIANT& PageFields, const VARIANT& AddToTable);
	VARIANT Application();
	VARIANT PivotFields(const VARIANT& Index);
	VARIANT RefreshTable();
	VARIANT ShowPages(const VARIANT& PageField);
};
/////////////////////////////////////////////////////////////////////////////
// PivotTables wrapper class

class PivotTables : public COleDispatchDriver
{
public:
	PivotTables() {}		// Calls COleDispatchDriver default constructor
	PivotTables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PivotTables(const PivotTables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// PivotField wrapper class

class PivotField : public COleDispatchDriver
{
public:
	PivotField() {}		// Calls COleDispatchDriver default constructor
	PivotField(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PivotField(const PivotField& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBaseField();
	void SetBaseField(const VARIANT&);
	VARIANT GetBaseItem();
	void SetBaseItem(const VARIANT&);
	VARIANT GetCalculation();
	void SetCalculation(const VARIANT&);
	VARIANT GetChildField();
	void SetChildField(const VARIANT&);
	VARIANT GetChildItems();
	void SetChildItems(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetCurrentPage();
	void SetCurrentPage(const VARIANT&);
	VARIANT GetDataRange();
	void SetDataRange(const VARIANT&);
	VARIANT GetDataType();
	void SetDataType(const VARIANT&);
	VARIANT GetFunction();
	void SetFunction(const VARIANT&);
	VARIANT GetGroupLevel();
	void SetGroupLevel(const VARIANT&);
	VARIANT GetHiddenItems();
	void SetHiddenItems(const VARIANT&);
	VARIANT GetLabelRange();
	void SetLabelRange(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetParentField();
	void SetParentField(const VARIANT&);
	VARIANT GetParentItems();
	void SetParentItems(const VARIANT&);
	VARIANT GetPosition();
	void SetPosition(const VARIANT&);
	VARIANT GetSourceName();
	void SetSourceName(const VARIANT&);
	VARIANT GetSubtotals();
	void SetSubtotals(const VARIANT&);
	VARIANT GetTotalLevels();
	void SetTotalLevels(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisibleItems();
	void SetVisibleItems(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT PivotItems(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// PivotFields wrapper class

class PivotFields : public COleDispatchDriver
{
public:
	PivotFields() {}		// Calls COleDispatchDriver default constructor
	PivotFields(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PivotFields(const PivotFields& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// PivotItem wrapper class

class PivotItem : public COleDispatchDriver
{
public:
	PivotItem() {}		// Calls COleDispatchDriver default constructor
	PivotItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PivotItem(const PivotItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetChildItems();
	void SetChildItems(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDataRange();
	void SetDataRange(const VARIANT&);
	VARIANT GetLabelRange();
	void SetLabelRange(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetParentItem();
	void SetParentItem(const VARIANT&);
	VARIANT GetParentShowDetail();
	void SetParentShowDetail(const VARIANT&);
	VARIANT GetPosition();
	void SetPosition(const VARIANT&);
	VARIANT GetShowDetail();
	void SetShowDetail(const VARIANT&);
	VARIANT GetSourceName();
	void SetSourceName(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// PivotItems wrapper class

class PivotItems : public COleDispatchDriver
{
public:
	PivotItems() {}		// Calls COleDispatchDriver default constructor
	PivotItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PivotItems(const PivotItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Scenario wrapper class

class Scenario : public COleDispatchDriver
{
public:
	Scenario() {}		// Calls COleDispatchDriver default constructor
	Scenario(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Scenario(const Scenario& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetChangingCells();
	void SetChangingCells(const VARIANT&);
	VARIANT GetComment();
	void SetComment(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetHidden();
	void SetHidden(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetValues();
	void SetValues(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ChangeScenario(const VARIANT& ChangingCells, const VARIANT& Values);
	VARIANT Delete();
	VARIANT Show();
};
/////////////////////////////////////////////////////////////////////////////
// Scenarios wrapper class

class Scenarios : public COleDispatchDriver
{
public:
	Scenarios() {}		// Calls COleDispatchDriver default constructor
	Scenarios(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Scenarios(const Scenarios& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Name, const VARIANT& ChangingCells, const VARIANT& Values, const VARIANT& Comment, const VARIANT& Locked, const VARIANT& Hidden);
	VARIANT Application();
	VARIANT CreateSummary(const VARIANT& ReportType, const VARIANT& ResultCells);
	VARIANT Item(const VARIANT& Index);
	VARIANT Merge(const VARIANT& Source);
};
/////////////////////////////////////////////////////////////////////////////
// MenuBar wrapper class

class MenuBar : public COleDispatchDriver
{
public:
	MenuBar() {}		// Calls COleDispatchDriver default constructor
	MenuBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MenuBar(const MenuBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT BuiltIn();
	VARIANT Delete();
	VARIANT Menus(const VARIANT& Index);
	VARIANT Reset();
};
/////////////////////////////////////////////////////////////////////////////
// MenuBars wrapper class

class MenuBars : public COleDispatchDriver
{
public:
	MenuBars() {}		// Calls COleDispatchDriver default constructor
	MenuBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MenuBars(const MenuBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Name);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Menu wrapper class

class Menu : public COleDispatchDriver
{
public:
	Menu() {}		// Calls COleDispatchDriver default constructor
	Menu(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Menu(const Menu& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT MenuItems(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Menus wrapper class

class Menus : public COleDispatchDriver
{
public:
	Menus() {}		// Calls COleDispatchDriver default constructor
	Menus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Menus(const Menus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Caption, const VARIANT& Before, const VARIANT& Restore);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// MenuItem wrapper class

class MenuItem : public COleDispatchDriver
{
public:
	MenuItem() {}		// Calls COleDispatchDriver default constructor
	MenuItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MenuItem(const MenuItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetChecked();
	void SetChecked(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHelpContextID();
	void SetHelpContextID(const VARIANT&);
	VARIANT GetHelpFile();
	void SetHelpFile(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetStatusBar();
	void SetStatusBar(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
};
/////////////////////////////////////////////////////////////////////////////
// MenuItems wrapper class

class MenuItems : public COleDispatchDriver
{
public:
	MenuItems() {}		// Calls COleDispatchDriver default constructor
	MenuItems(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	MenuItems(const MenuItems& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Caption, const VARIANT& OnAction, const VARIANT& ShortcutKey, const VARIANT& Before, const VARIANT& Restore, const VARIANT& StatusBar, const VARIANT& HelpFile, const VARIANT& HelpContextID);
	VARIANT AddMenu(const VARIANT& Caption, const VARIANT& Before, const VARIANT& Restore);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Window wrapper class

class Window : public COleDispatchDriver
{
public:
	Window() {}		// Calls COleDispatchDriver default constructor
	Window(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Window(const Window& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetActiveCell();
	void SetActiveCell(const VARIANT&);
	VARIANT GetActiveChart();
	void SetActiveChart(const VARIANT&);
	VARIANT GetActivePane();
	void SetActivePane(const VARIANT&);
	VARIANT GetActiveSheet();
	void SetActiveSheet(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplayFormulas();
	void SetDisplayFormulas(const VARIANT&);
	VARIANT GetDisplayGridlines();
	void SetDisplayGridlines(const VARIANT&);
	VARIANT GetDisplayHeadings();
	void SetDisplayHeadings(const VARIANT&);
	VARIANT GetDisplayHorizontalScrollBar();
	void SetDisplayHorizontalScrollBar(const VARIANT&);
	VARIANT GetDisplayOutline();
	void SetDisplayOutline(const VARIANT&);
	VARIANT GetDisplayRightToLeft();
	void SetDisplayRightToLeft(const VARIANT&);
	VARIANT GetDisplayVerticalScrollBar();
	void SetDisplayVerticalScrollBar(const VARIANT&);
	VARIANT GetDisplayWorkbookTabs();
	void SetDisplayWorkbookTabs(const VARIANT&);
	VARIANT GetDisplayZeros();
	void SetDisplayZeros(const VARIANT&);
	VARIANT GetFreezePanes();
	void SetFreezePanes(const VARIANT&);
	VARIANT GetGridlineColor();
	void SetGridlineColor(const VARIANT&);
	VARIANT GetGridlineColorIndex();
	void SetGridlineColorIndex(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetOnWindow();
	void SetOnWindow(const VARIANT&);
	VARIANT GetPageSetup();
	void SetPageSetup(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetRangeSelection();
	void SetRangeSelection(const VARIANT&);
	VARIANT GetScrollColumn();
	void SetScrollColumn(const VARIANT&);
	VARIANT GetScrollRow();
	void SetScrollRow(const VARIANT&);
	VARIANT GetSelectedSheets();
	void SetSelectedSheets(const VARIANT&);
	VARIANT GetSelection();
	void SetSelection(const VARIANT&);
	VARIANT GetSplit();
	void SetSplit(const VARIANT&);
	VARIANT GetSplitColumn();
	void SetSplitColumn(const VARIANT&);
	VARIANT GetSplitHorizontal();
	void SetSplitHorizontal(const VARIANT&);
	VARIANT GetSplitRow();
	void SetSplitRow(const VARIANT&);
	VARIANT GetSplitVertical();
	void SetSplitVertical(const VARIANT&);
	VARIANT GetTabRatio();
	void SetTabRatio(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetUsableHeight();
	void SetUsableHeight(const VARIANT&);
	VARIANT GetUsableWidth();
	void SetUsableWidth(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetVisibleRange();
	void SetVisibleRange(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetWindowNumber();
	void SetWindowNumber(const VARIANT&);
	VARIANT GetWindowState();
	void SetWindowState(const VARIANT&);
	VARIANT GetZoom();
	void SetZoom(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT ActivateNext();
	VARIANT ActivatePrevious();
	VARIANT Application();
	VARIANT Close(const VARIANT& SaveChanges, const VARIANT& Filename, const VARIANT& RouteWorkbook);
	VARIANT LargeScroll(const VARIANT& Down, const VARIANT& Up, const VARIANT& ToRight, const VARIANT& ToLeft);
	VARIANT NewWindow();
	VARIANT Panes(const VARIANT& Index);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT ScrollWorkbookTabs(const VARIANT& Sheets, const VARIANT& Position);
	VARIANT SetInfoDisplay(const VARIANT& Cell, const VARIANT& Formula, const VARIANT& Value, const VARIANT& Format, const VARIANT& Protection, const VARIANT& Names, const VARIANT& Precedents, const VARIANT& Dependents, const VARIANT& Note);
	VARIANT SmallScroll(const VARIANT& Down, const VARIANT& Up, const VARIANT& ToRight, const VARIANT& ToLeft);
};
/////////////////////////////////////////////////////////////////////////////
// Windows wrapper class

class Windows : public COleDispatchDriver
{
public:
	Windows() {}		// Calls COleDispatchDriver default constructor
	Windows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Windows(const Windows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Arrange(const VARIANT& ArrangeStyle, const VARIANT& ActiveWorkbook, const VARIANT& SyncHorizontal, const VARIANT& SyncVertical);
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Pane wrapper class

class Pane : public COleDispatchDriver
{
public:
	Pane() {}		// Calls COleDispatchDriver default constructor
	Pane(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Pane(const Pane& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetScrollColumn();
	void SetScrollColumn(const VARIANT&);
	VARIANT GetScrollRow();
	void SetScrollRow(const VARIANT&);
	VARIANT GetVisibleRange();
	void SetVisibleRange(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT LargeScroll(const VARIANT& Down, const VARIANT& Up, const VARIANT& ToRight, const VARIANT& ToLeft);
	VARIANT SmallScroll(const VARIANT& Down, const VARIANT& Up, const VARIANT& ToRight, const VARIANT& ToLeft);
};
/////////////////////////////////////////////////////////////////////////////
// Panes wrapper class

class Panes : public COleDispatchDriver
{
public:
	Panes() {}		// Calls COleDispatchDriver default constructor
	Panes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Panes(const Panes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Name wrapper class

class Name : public COleDispatchDriver
{
public:
	Name() {}		// Calls COleDispatchDriver default constructor
	Name(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Name(const Name& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCategory();
	void SetCategory(const VARIANT&);
	VARIANT GetCategoryLocal();
	void SetCategoryLocal(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetMacroType();
	void SetMacroType(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNameLocal();
	void SetNameLocal(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetRefersTo();
	void SetRefersTo(const VARIANT&);
	VARIANT GetRefersToLocal();
	void SetRefersToLocal(const VARIANT&);
	VARIANT GetRefersToR1C1();
	void SetRefersToR1C1(const VARIANT&);
	VARIANT GetRefersToR1C1Local();
	void SetRefersToR1C1Local(const VARIANT&);
	VARIANT GetRefersToRange();
	void SetRefersToRange(const VARIANT&);
	VARIANT GetShortcutKey();
	void SetShortcutKey(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
};
/////////////////////////////////////////////////////////////////////////////
// Names wrapper class

class Names : public COleDispatchDriver
{
public:
	Names() {}		// Calls COleDispatchDriver default constructor
	Names(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Names(const Names& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Name, const VARIANT& RefersTo, const VARIANT& Visible, const VARIANT& MacroType, const VARIANT& ShortcutKey, const VARIANT& Category, const VARIANT& NameLocal, const VARIANT& RefersToLocal, 
		const VARIANT& CategoryLocal, const VARIANT& RefersToR1C1, const VARIANT& RefersToR1C1Local);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo);
};
/////////////////////////////////////////////////////////////////////////////
// DrawingObjects wrapper class

class DrawingObjects : public COleDispatchDriver
{
public:
	DrawingObjects() {}		// Calls COleDispatchDriver default constructor
	DrawingObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DrawingObjects(const DrawingObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetArrowHeadLength();
	void SetArrowHeadLength(const VARIANT&);
	VARIANT GetArrowHeadStyle();
	void SetArrowHeadStyle(const VARIANT&);
	VARIANT GetArrowHeadWidth();
	void SetArrowHeadWidth(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCancelButton();
	void SetCancelButton(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDefaultButton();
	void SetDefaultButton(const VARIANT&);
	VARIANT GetDismissButton();
	void SetDismissButton(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetDisplayVerticalScrollBar();
	void SetDisplayVerticalScrollBar(const VARIANT&);
	VARIANT GetDropDownLines();
	void SetDropDownLines(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHelpButton();
	void SetHelpButton(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInputType();
	void SetInputType(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLargeChange();
	void SetLargeChange(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetList();
	void SetList(const VARIANT&);
	VARIANT GetListFillRange();
	void SetListFillRange(const VARIANT&);
	VARIANT GetListIndex();
	void SetListIndex(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetMax();
	void SetMax(const VARIANT&);
	VARIANT GetMin();
	void SetMin(const VARIANT&);
	VARIANT GetMultiLine();
	void SetMultiLine(const VARIANT&);
	VARIANT GetMultiSelect();
	void SetMultiSelect(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetSelected();
	void SetSelected(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetSmallChange();
	void SetSmallChange(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVertices();
	void SetVertices(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT AddItem(const VARIANT& Text, const VARIANT& Index);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT LinkCombo(const VARIANT& Link);
	VARIANT RemoveAllItems();
	VARIANT RemoveItem(const VARIANT& Index, const VARIANT& Count);
	VARIANT Reshape(const VARIANT& Vertex, const VARIANT& Insert, const VARIANT& Left, const VARIANT& Top);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
	VARIANT Ungroup();
};
/////////////////////////////////////////////////////////////////////////////
// GroupObject wrapper class

class GroupObject : public COleDispatchDriver
{
public:
	GroupObject() {}		// Calls COleDispatchDriver default constructor
	GroupObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupObject(const GroupObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetArrowHeadLength();
	void SetArrowHeadLength(const VARIANT&);
	VARIANT GetArrowHeadStyle();
	void SetArrowHeadStyle(const VARIANT&);
	VARIANT GetArrowHeadWidth();
	void SetArrowHeadWidth(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
	VARIANT Ungroup();
};
/////////////////////////////////////////////////////////////////////////////
// GroupObjects wrapper class

class GroupObjects : public COleDispatchDriver
{
public:
	GroupObjects() {}		// Calls COleDispatchDriver default constructor
	GroupObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupObjects(const GroupObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetArrowHeadLength();
	void SetArrowHeadLength(const VARIANT&);
	VARIANT GetArrowHeadStyle();
	void SetArrowHeadStyle(const VARIANT&);
	VARIANT GetArrowHeadWidth();
	void SetArrowHeadWidth(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
	VARIANT Ungroup();
};
/////////////////////////////////////////////////////////////////////////////
// Line wrapper class

class Line : public COleDispatchDriver
{
public:
	Line() {}		// Calls COleDispatchDriver default constructor
	Line(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Line(const Line& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetArrowHeadLength();
	void SetArrowHeadLength(const VARIANT&);
	VARIANT GetArrowHeadStyle();
	void SetArrowHeadStyle(const VARIANT&);
	VARIANT GetArrowHeadWidth();
	void SetArrowHeadWidth(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Lines wrapper class

class Lines : public COleDispatchDriver
{
public:
	Lines() {}		// Calls COleDispatchDriver default constructor
	Lines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Lines(const Lines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetArrowHeadLength();
	void SetArrowHeadLength(const VARIANT&);
	VARIANT GetArrowHeadStyle();
	void SetArrowHeadStyle(const VARIANT&);
	VARIANT GetArrowHeadWidth();
	void SetArrowHeadWidth(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& X1, const VARIANT& Y1, const VARIANT& X2, const VARIANT& Y2);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Rectangle wrapper class

class Rectangle : public COleDispatchDriver
{
public:
	Rectangle() {}		// Calls COleDispatchDriver default constructor
	Rectangle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Rectangle(const Rectangle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Rectangles wrapper class

class Rectangles : public COleDispatchDriver
{
public:
	Rectangles() {}		// Calls COleDispatchDriver default constructor
	Rectangles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Rectangles(const Rectangles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Oval wrapper class

class Oval : public COleDispatchDriver
{
public:
	Oval() {}		// Calls COleDispatchDriver default constructor
	Oval(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Oval(const Oval& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Ovals wrapper class

class Ovals : public COleDispatchDriver
{
public:
	Ovals() {}		// Calls COleDispatchDriver default constructor
	Ovals(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Ovals(const Ovals& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Arc wrapper class

class Arc : public COleDispatchDriver
{
public:
	Arc() {}		// Calls COleDispatchDriver default constructor
	Arc(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Arc(const Arc& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Arcs wrapper class

class Arcs : public COleDispatchDriver
{
public:
	Arcs() {}		// Calls COleDispatchDriver default constructor
	Arcs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Arcs(const Arcs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& X1, const VARIANT& Y1, const VARIANT& X2, const VARIANT& Y2);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// TextBox wrapper class

class TextBox : public COleDispatchDriver
{
public:
	TextBox() {}		// Calls COleDispatchDriver default constructor
	TextBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextBox(const TextBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// TextBoxes wrapper class

class TextBoxes : public COleDispatchDriver
{
public:
	TextBoxes() {}		// Calls COleDispatchDriver default constructor
	TextBoxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TextBoxes(const TextBoxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Picture wrapper class

class Picture : public COleDispatchDriver
{
public:
	Picture() {}		// Calls COleDispatchDriver default constructor
	Picture(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Picture(const Picture& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Pictures wrapper class

class Pictures : public COleDispatchDriver
{
public:
	Pictures() {}		// Calls COleDispatchDriver default constructor
	Pictures(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Pictures(const Pictures& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Insert(const VARIANT& Filename, const VARIANT& Converter);
	VARIANT Item(const VARIANT& Index);
	VARIANT Paste(const VARIANT& Link);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// OLEObject wrapper class

class OLEObject : public COleDispatchDriver
{
public:
	OLEObject() {}		// Calls COleDispatchDriver default constructor
	OLEObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OLEObject(const OLEObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAutoLoad();
	void SetAutoLoad(const VARIANT&);
	VARIANT GetAutoUpdate();
	void SetAutoUpdate(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetObject();
	void SetObject(const VARIANT&);
	VARIANT GetOLEType();
	void SetOLEType(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
	VARIANT Update();
	VARIANT Verb(const VARIANT& Verb);
};
/////////////////////////////////////////////////////////////////////////////
// OLEObjects wrapper class

class OLEObjects : public COleDispatchDriver
{
public:
	OLEObjects() {}		// Calls COleDispatchDriver default constructor
	OLEObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OLEObjects(const OLEObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& ClassType, const VARIANT& Filename, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// ChartObject wrapper class

class ChartObject : public COleDispatchDriver
{
public:
	ChartObject() {}		// Calls COleDispatchDriver default constructor
	ChartObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartObject(const ChartObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetChart();
	void SetChart(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// ChartObjects wrapper class

class ChartObjects : public COleDispatchDriver
{
public:
	ChartObjects() {}		// Calls COleDispatchDriver default constructor
	ChartObjects(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartObjects(const ChartObjects& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetRoundedCorners();
	void SetRoundedCorners(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Drawing wrapper class

class Drawing : public COleDispatchDriver
{
public:
	Drawing() {}		// Calls COleDispatchDriver default constructor
	Drawing(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Drawing(const Drawing& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVertices();
	void SetVertices(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT AddVertex(const VARIANT& Left, const VARIANT& Top);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Reshape(const VARIANT& Vertex, const VARIANT& Insert, const VARIANT& Left, const VARIANT& Top);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Drawings wrapper class

class Drawings : public COleDispatchDriver
{
public:
	Drawings() {}		// Calls COleDispatchDriver default constructor
	Drawings(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Drawings(const Drawings& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& X1, const VARIANT& Y1, const VARIANT& X2, const VARIANT& Y2, const VARIANT& Closed);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Reshape(const VARIANT& Vertex, const VARIANT& Insert, const VARIANT& Left, const VARIANT& Top);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Button wrapper class

class Button : public COleDispatchDriver
{
public:
	Button() {}		// Calls COleDispatchDriver default constructor
	Button(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Button(const Button& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCancelButton();
	void SetCancelButton(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDefaultButton();
	void SetDefaultButton(const VARIANT&);
	VARIANT GetDismissButton();
	void SetDismissButton(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHelpButton();
	void SetHelpButton(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Buttons wrapper class

class Buttons : public COleDispatchDriver
{
public:
	Buttons() {}		// Calls COleDispatchDriver default constructor
	Buttons(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Buttons(const Buttons& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetAddIndent();
	void SetAddIndent(const VARIANT&);
	VARIANT GetAutoSize();
	void SetAutoSize(const VARIANT&);
	VARIANT GetCancelButton();
	void SetCancelButton(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDefaultButton();
	void SetDefaultButton(const VARIANT&);
	VARIANT GetDismissButton();
	void SetDismissButton(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetHelpButton();
	void SetHelpButton(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// EditBox wrapper class

class EditBox : public COleDispatchDriver
{
public:
	EditBox() {}		// Calls COleDispatchDriver default constructor
	EditBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	EditBox(const EditBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplayVerticalScrollBar();
	void SetDisplayVerticalScrollBar(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInputType();
	void SetInputType(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedObject();
	void SetLinkedObject(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMultiLine();
	void SetMultiLine(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPasswordEdit();
	void SetPasswordEdit(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// EditBoxes wrapper class

class EditBoxes : public COleDispatchDriver
{
public:
	EditBoxes() {}		// Calls COleDispatchDriver default constructor
	EditBoxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	EditBoxes(const EditBoxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplayVerticalScrollBar();
	void SetDisplayVerticalScrollBar(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInputType();
	void SetInputType(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMultiLine();
	void SetMultiLine(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPasswordEdit();
	void SetPasswordEdit(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// CheckBox wrapper class

class CheckBox : public COleDispatchDriver
{
public:
	CheckBox() {}		// Calls COleDispatchDriver default constructor
	CheckBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CheckBox(const CheckBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// CheckBoxes wrapper class

class CheckBoxes : public COleDispatchDriver
{
public:
	CheckBoxes() {}		// Calls COleDispatchDriver default constructor
	CheckBoxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CheckBoxes(const CheckBoxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// OptionButton wrapper class

class OptionButton : public COleDispatchDriver
{
public:
	OptionButton() {}		// Calls COleDispatchDriver default constructor
	OptionButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OptionButton(const OptionButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// OptionButtons wrapper class

class OptionButtons : public COleDispatchDriver
{
public:
	OptionButtons() {}		// Calls COleDispatchDriver default constructor
	OptionButtons(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	OptionButtons(const OptionButtons& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Spinner wrapper class

class Spinner : public COleDispatchDriver
{
public:
	Spinner() {}		// Calls COleDispatchDriver default constructor
	Spinner(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Spinner(const Spinner& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMax();
	void SetMax(const VARIANT&);
	VARIANT GetMin();
	void SetMin(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSmallChange();
	void SetSmallChange(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Spinners wrapper class

class Spinners : public COleDispatchDriver
{
public:
	Spinners() {}		// Calls COleDispatchDriver default constructor
	Spinners(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Spinners(const Spinners& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMax();
	void SetMax(const VARIANT&);
	VARIANT GetMin();
	void SetMin(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSmallChange();
	void SetSmallChange(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// ScrollBar wrapper class

class ScrollBar : public COleDispatchDriver
{
public:
	ScrollBar() {}		// Calls COleDispatchDriver default constructor
	ScrollBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ScrollBar(const ScrollBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLargeChange();
	void SetLargeChange(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMax();
	void SetMax(const VARIANT&);
	VARIANT GetMin();
	void SetMin(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSmallChange();
	void SetSmallChange(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// ScrollBars wrapper class

class ScrollBars : public COleDispatchDriver
{
public:
	ScrollBars() {}		// Calls COleDispatchDriver default constructor
	ScrollBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ScrollBars(const ScrollBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLargeChange();
	void SetLargeChange(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMax();
	void SetMax(const VARIANT&);
	VARIANT GetMin();
	void SetMin(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSmallChange();
	void SetSmallChange(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// ListBox wrapper class

class ListBox : public COleDispatchDriver
{
public:
	ListBox() {}		// Calls COleDispatchDriver default constructor
	ListBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListBox(const ListBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLinkedObject();
	void SetLinkedObject(const VARIANT&);
	VARIANT GetList();
	void SetList(const VARIANT&);
	VARIANT GetListCount();
	void SetListCount(const VARIANT&);
	VARIANT GetListFillRange();
	void SetListFillRange(const VARIANT&);
	VARIANT GetListIndex();
	void SetListIndex(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMultiSelect();
	void SetMultiSelect(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSelected();
	void SetSelected(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT AddItem(const VARIANT& Text, const VARIANT& Index);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT RemoveAllItems();
	VARIANT RemoveItem(const VARIANT& Index, const VARIANT& Count);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// ListBoxes wrapper class

class ListBoxes : public COleDispatchDriver
{
public:
	ListBoxes() {}		// Calls COleDispatchDriver default constructor
	ListBoxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ListBoxes(const ListBoxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetList();
	void SetList(const VARIANT&);
	VARIANT GetListFillRange();
	void SetListFillRange(const VARIANT&);
	VARIANT GetListIndex();
	void SetListIndex(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetMultiSelect();
	void SetMultiSelect(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSelected();
	void SetSelected(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT AddItem(const VARIANT& Text, const VARIANT& Index);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT RemoveAllItems();
	VARIANT RemoveItem(const VARIANT& Index, const VARIANT& Count);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// GroupBox wrapper class

class GroupBox : public COleDispatchDriver
{
public:
	GroupBox() {}		// Calls COleDispatchDriver default constructor
	GroupBox(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupBox(const GroupBox& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// GroupBoxes wrapper class

class GroupBoxes : public COleDispatchDriver
{
public:
	GroupBoxes() {}		// Calls COleDispatchDriver default constructor
	GroupBoxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	GroupBoxes(const GroupBoxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// DropDown wrapper class

class DropDown : public COleDispatchDriver
{
public:
	DropDown() {}		// Calls COleDispatchDriver default constructor
	DropDown(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DropDown(const DropDown& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetDropDownLines();
	void SetDropDownLines(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetLinkedObject();
	void SetLinkedObject(const VARIANT&);
	VARIANT GetList();
	void SetList(const VARIANT&);
	VARIANT GetListCount();
	void SetListCount(const VARIANT&);
	VARIANT GetListFillRange();
	void SetListFillRange(const VARIANT&);
	VARIANT GetListIndex();
	void SetListIndex(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSelected();
	void SetSelected(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT AddItem(const VARIANT& Text, const VARIANT& Index);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT RemoveAllItems();
	VARIANT RemoveItem(const VARIANT& Index, const VARIANT& Count);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// DropDowns wrapper class

class DropDowns : public COleDispatchDriver
{
public:
	DropDowns() {}		// Calls COleDispatchDriver default constructor
	DropDowns(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DropDowns(const DropDowns& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDisplay3DShading();
	void SetDisplay3DShading(const VARIANT&);
	VARIANT GetDropDownLines();
	void SetDropDownLines(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLinkedCell();
	void SetLinkedCell(const VARIANT&);
	VARIANT GetList();
	void SetList(const VARIANT&);
	VARIANT GetListFillRange();
	void SetListFillRange(const VARIANT&);
	VARIANT GetListIndex();
	void SetListIndex(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetSelected();
	void SetSelected(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height, const VARIANT& Editable);
	VARIANT AddItem(const VARIANT& Text, const VARIANT& Index);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT RemoveAllItems();
	VARIANT RemoveItem(const VARIANT& Index, const VARIANT& Count);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// DialogFrame wrapper class

class DialogFrame : public COleDispatchDriver
{
public:
	DialogFrame() {}		// Calls COleDispatchDriver default constructor
	DialogFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DialogFrame(const DialogFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Select(const VARIANT& Replace);
};
/////////////////////////////////////////////////////////////////////////////
// Label wrapper class

class Label : public COleDispatchDriver
{
public:
	Label() {}		// Calls COleDispatchDriver default constructor
	Label(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Label(const Label& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetBottomRightCell();
	void SetBottomRightCell(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetTopLeftCell();
	void SetTopLeftCell(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Labels wrapper class

class Labels : public COleDispatchDriver
{
public:
	Labels() {}		// Calls COleDispatchDriver default constructor
	Labels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Labels(const Labels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAccelerator();
	void SetAccelerator(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnabled();
	void SetEnabled(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetLocked();
	void SetLocked(const VARIANT&);
	VARIANT GetLockedText();
	void SetLockedText(const VARIANT&);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPhoneticAccelerator();
	void SetPhoneticAccelerator(const VARIANT&);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT&);
	VARIANT GetPrintObject();
	void SetPrintObject(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);
	VARIANT GetZOrder();
	void SetZOrder(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Left, const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	VARIANT Application();
	VARIANT BringToFront();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy();
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	VARIANT Cut();
	VARIANT Delete();
	VARIANT Duplicate();
	VARIANT Group();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
};
/////////////////////////////////////////////////////////////////////////////
// Interior wrapper class

class Interior : public COleDispatchDriver
{
public:
	Interior() {}		// Calls COleDispatchDriver default constructor
	Interior(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Interior(const Interior& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetColor();
	void SetColor(const VARIANT&);
	VARIANT GetColorIndex();
	void SetColorIndex(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPattern();
	void SetPattern(const VARIANT&);
	VARIANT GetPatternColor();
	void SetPatternColor(const VARIANT&);
	VARIANT GetPatternColorIndex();
	void SetPatternColorIndex(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// SoundNote wrapper class

class SoundNote : public COleDispatchDriver
{
public:
	SoundNote() {}		// Calls COleDispatchDriver default constructor
	SoundNote(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SoundNote(const SoundNote& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Import(const VARIANT& Filename);
	VARIANT Play();
	VARIANT Record();
};
/////////////////////////////////////////////////////////////////////////////
// Characters wrapper class

class Characters : public COleDispatchDriver
{
public:
	Characters() {}		// Calls COleDispatchDriver default constructor
	Characters(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Characters(const Characters& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Insert(const VARIANT& String);
};
/////////////////////////////////////////////////////////////////////////////
// Dialog wrapper class

class Dialog : public COleDispatchDriver
{
public:
	Dialog() {}		// Calls COleDispatchDriver default constructor
	Dialog(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Dialog(const Dialog& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Show(const VARIANT& Arg1, const VARIANT& Arg2, const VARIANT& Arg3, const VARIANT& Arg4, const VARIANT& Arg5, const VARIANT& Arg6, const VARIANT& Arg7, const VARIANT& Arg8, const VARIANT& Arg9, const VARIANT& Arg10, 
		const VARIANT& Arg11, const VARIANT& Arg12, const VARIANT& Arg13, const VARIANT& Arg14, const VARIANT& Arg15, const VARIANT& Arg16, const VARIANT& Arg17, const VARIANT& Arg18, const VARIANT& Arg19, const VARIANT& Arg20, 
		const VARIANT& Arg21, const VARIANT& Arg22, const VARIANT& Arg23, const VARIANT& Arg24, const VARIANT& Arg25, const VARIANT& Arg26, const VARIANT& Arg27, const VARIANT& Arg28, const VARIANT& Arg29, const VARIANT& Arg30);
};
/////////////////////////////////////////////////////////////////////////////
// Dialogs wrapper class

class Dialogs : public COleDispatchDriver
{
public:
	Dialogs() {}		// Calls COleDispatchDriver default constructor
	Dialogs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Dialogs(const Dialogs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Outline wrapper class

class Outline : public COleDispatchDriver
{
public:
	Outline() {}		// Calls COleDispatchDriver default constructor
	Outline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Outline(const Outline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAutomaticStyles();
	void SetAutomaticStyles(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetSummaryColumn();
	void SetSummaryColumn(const VARIANT&);
	VARIANT GetSummaryRow();
	void SetSummaryRow(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ShowLevels(const VARIANT& RowLevels, const VARIANT& ColumnLevels);
};
/////////////////////////////////////////////////////////////////////////////
// RoutingSlip wrapper class

class RoutingSlip : public COleDispatchDriver
{
public:
	RoutingSlip() {}		// Calls COleDispatchDriver default constructor
	RoutingSlip(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	RoutingSlip(const RoutingSlip& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDelivery();
	void SetDelivery(const VARIANT&);
	VARIANT GetMessage();
	void SetMessage(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetRecipients();
	void SetRecipients(const VARIANT&);
	VARIANT GetReturnWhenDone();
	void SetReturnWhenDone(const VARIANT&);
	VARIANT GetStatus();
	void SetStatus(const VARIANT&);
	VARIANT GetSubject();
	void SetSubject(const VARIANT&);
	VARIANT GetTrackStatus();
	void SetTrackStatus(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Reset();
};
/////////////////////////////////////////////////////////////////////////////
// Module wrapper class

class Module : public COleDispatchDriver
{
public:
	Module() {}		// Calls COleDispatchDriver default constructor
	Module(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Module(const Module& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetOnDoubleClick();
	void SetOnDoubleClick(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetPageSetup();
	void SetPageSetup(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetProtectContents();
	void SetProtectContents(const VARIANT&);
	VARIANT GetProtectionMode();
	void SetProtectionMode(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT InsertFile(const VARIANT& Filename, const VARIANT& Merge);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly);
	VARIANT SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup);
	VARIANT Select(const VARIANT& Replace);
	VARIANT Unprotect(const VARIANT& Password);
};
/////////////////////////////////////////////////////////////////////////////
// Modules wrapper class

class Modules : public COleDispatchDriver
{
public:
	Modules() {}		// Calls COleDispatchDriver default constructor
	Modules(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Modules(const Modules& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count);
	VARIANT Application();
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT Item(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT Select(const VARIANT& Replace);
};
/////////////////////////////////////////////////////////////////////////////
// DialogSheet wrapper class

class DialogSheet : public COleDispatchDriver
{
public:
	DialogSheet() {}		// Calls COleDispatchDriver default constructor
	DialogSheet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DialogSheet(const DialogSheet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDefaultButton();
	void SetDefaultButton(const VARIANT&);
	VARIANT GetDialogFrame();
	void SetDialogFrame(const VARIANT&);
	VARIANT GetDisplayAutomaticPageBreaks();
	void SetDisplayAutomaticPageBreaks(const VARIANT&);
	VARIANT GetEnableAutoFilter();
	void SetEnableAutoFilter(const VARIANT&);
	VARIANT GetEnableOutlining();
	void SetEnableOutlining(const VARIANT&);
	VARIANT GetEnablePivotTable();
	void SetEnablePivotTable(const VARIANT&);
	VARIANT GetFocus();
	void SetFocus(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetOnDoubleClick();
	void SetOnDoubleClick(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetPageSetup();
	void SetPageSetup(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetProtectContents();
	void SetProtectContents(const VARIANT&);
	VARIANT GetProtectDrawingObjects();
	void SetProtectDrawingObjects(const VARIANT&);
	VARIANT GetProtectionMode();
	void SetProtectionMode(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT Arcs(const VARIANT& Index);
	VARIANT Buttons(const VARIANT& Index);
	VARIANT ChartObjects(const VARIANT& Index);
	VARIANT CheckBoxes(const VARIANT& Index);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT DrawingObjects(const VARIANT& Index);
	VARIANT Drawings(const VARIANT& Index);
	VARIANT DropDowns(const VARIANT& Index);
	VARIANT EditBoxes(const VARIANT& Index);
	VARIANT _Evaluate(const VARIANT& Name);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT GroupBoxes(const VARIANT& Index);
	VARIANT GroupObjects(const VARIANT& Index);
	VARIANT Hide(const VARIANT& Cancel);
	VARIANT Labels(const VARIANT& Index);
	VARIANT Lines(const VARIANT& Index);
	VARIANT ListBoxes(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT Names(const VARIANT& Index, const VARIANT& IndexLocal, const VARIANT& RefersTo);
	VARIANT OLEObjects(const VARIANT& Index);
	VARIANT OptionButtons(const VARIANT& Index);
	VARIANT Ovals(const VARIANT& Index);
	VARIANT Paste(const VARIANT& Destination, const VARIANT& Link);
	VARIANT PasteSpecial(const VARIANT& Format, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel);
	VARIANT Pictures(const VARIANT& Index);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly);
	VARIANT Rectangles(const VARIANT& Index);
	VARIANT SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup);
	VARIANT ScrollBars(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT Show();
	VARIANT Spinners(const VARIANT& Index);
	VARIANT TextBoxes(const VARIANT& Index);
	VARIANT Unprotect(const VARIANT& Password);
};
/////////////////////////////////////////////////////////////////////////////
// DialogSheets wrapper class

class DialogSheets : public COleDispatchDriver
{
public:
	DialogSheets() {}		// Calls COleDispatchDriver default constructor
	DialogSheets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DialogSheets(const DialogSheets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count);
	VARIANT Application();
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT Item(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Select(const VARIANT& Replace);
};
/////////////////////////////////////////////////////////////////////////////
// PageSetup wrapper class

class PageSetup : public COleDispatchDriver
{
public:
	PageSetup() {}		// Calls COleDispatchDriver default constructor
	PageSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PageSetup(const PageSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBlackAndWhite();
	void SetBlackAndWhite(const VARIANT&);
	VARIANT GetBottomMargin();
	void SetBottomMargin(const VARIANT&);
	VARIANT GetCenterFooter();
	void SetCenterFooter(const VARIANT&);
	VARIANT GetCenterHeader();
	void SetCenterHeader(const VARIANT&);
	VARIANT GetCenterHorizontally();
	void SetCenterHorizontally(const VARIANT&);
	VARIANT GetCenterVertically();
	void SetCenterVertically(const VARIANT&);
	VARIANT GetChartSize();
	void SetChartSize(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDraft();
	void SetDraft(const VARIANT&);
	VARIANT GetFirstPageNumber();
	void SetFirstPageNumber(const VARIANT&);
	VARIANT GetFitToPagesTall();
	void SetFitToPagesTall(const VARIANT&);
	VARIANT GetFitToPagesWide();
	void SetFitToPagesWide(const VARIANT&);
	VARIANT GetFooterMargin();
	void SetFooterMargin(const VARIANT&);
	VARIANT GetHeaderMargin();
	void SetHeaderMargin(const VARIANT&);
	VARIANT GetLeftFooter();
	void SetLeftFooter(const VARIANT&);
	VARIANT GetLeftHeader();
	void SetLeftHeader(const VARIANT&);
	VARIANT GetLeftMargin();
	void SetLeftMargin(const VARIANT&);
	VARIANT GetOrder();
	void SetOrder(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetPaperSize();
	void SetPaperSize(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPrintArea();
	void SetPrintArea(const VARIANT&);
	VARIANT GetPrintGridlines();
	void SetPrintGridlines(const VARIANT&);
	VARIANT GetPrintHeadings();
	void SetPrintHeadings(const VARIANT&);
	VARIANT GetPrintNotes();
	void SetPrintNotes(const VARIANT&);
	VARIANT GetPrintQuality();
	void SetPrintQuality(const VARIANT&);
	VARIANT GetPrintTitleColumns();
	void SetPrintTitleColumns(const VARIANT&);
	VARIANT GetPrintTitleRows();
	void SetPrintTitleRows(const VARIANT&);
	VARIANT GetRightFooter();
	void SetRightFooter(const VARIANT&);
	VARIANT GetRightHeader();
	void SetRightHeader(const VARIANT&);
	VARIANT GetRightMargin();
	void SetRightMargin(const VARIANT&);
	VARIANT GetTopMargin();
	void SetTopMargin(const VARIANT&);
	VARIANT GetZoom();
	void SetZoom(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// Mailer wrapper class

class Mailer : public COleDispatchDriver
{
public:
	Mailer() {}		// Calls COleDispatchDriver default constructor
	Mailer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Mailer(const Mailer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBCCRecipients();
	void SetBCCRecipients(const VARIANT&);
	VARIANT GetCCRecipients();
	void SetCCRecipients(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEnclosures();
	void SetEnclosures(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetReceived();
	void SetReceived(const VARIANT&);
	VARIANT GetSendDateTime();
	void SetSendDateTime(const VARIANT&);
	VARIANT GetSender();
	void SetSender(const VARIANT&);
	VARIANT GetSubject();
	void SetSubject(const VARIANT&);
	VARIANT GetToRecipients();
	void SetToRecipients(const VARIANT&);
	VARIANT GetWhichAddress();
	void SetWhichAddress(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// Font wrapper class

class Font : public COleDispatchDriver
{
public:
	Font() {}		// Calls COleDispatchDriver default constructor
	Font(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Font(const Font& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBackground();
	void SetBackground(const VARIANT&);
	VARIANT GetBold();
	void SetBold(const VARIANT&);
	VARIANT GetColor();
	void SetColor(const VARIANT&);
	VARIANT GetColorIndex();
	void SetColorIndex(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFontStyle();
	void SetFontStyle(const VARIANT&);
	VARIANT GetItalic();
	void SetItalic(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOutlineFont();
	void SetOutlineFont(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetSize();
	void SetSize(const VARIANT&);
	VARIANT GetStrikethrough();
	void SetStrikethrough(const VARIANT&);
	VARIANT GetSubscript();
	void SetSubscript(const VARIANT&);
	VARIANT GetSuperscript();
	void SetSuperscript(const VARIANT&);
	VARIANT GetUnderline();
	void SetUnderline(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// Border wrapper class

class Border : public COleDispatchDriver
{
public:
	Border() {}		// Calls COleDispatchDriver default constructor
	Border(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Border(const Border& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetColor();
	void SetColor(const VARIANT&);
	VARIANT GetColorIndex();
	void SetColorIndex(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetLineStyle();
	void SetLineStyle(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetWeight();
	void SetWeight(const VARIANT&);

// Operations
public:
	VARIANT Application();
};
/////////////////////////////////////////////////////////////////////////////
// Borders wrapper class

class Borders : public COleDispatchDriver
{
public:
	Borders() {}		// Calls COleDispatchDriver default constructor
	Borders(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Borders(const Borders& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetColor();
	void SetColor(const VARIANT&);
	VARIANT GetColorIndex();
	void SetColorIndex(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetLineStyle();
	void SetLineStyle(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetValue();
	void SetValue(const VARIANT&);
	VARIANT GetWeight();
	void SetWeight(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Corners wrapper class

class Corners : public COleDispatchDriver
{
public:
	Corners() {}		// Calls COleDispatchDriver default constructor
	Corners(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Corners(const Corners& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// SeriesLines wrapper class

class SeriesLines : public COleDispatchDriver
{
public:
	SeriesLines() {}		// Calls COleDispatchDriver default constructor
	SeriesLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SeriesLines(const SeriesLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// HiLoLines wrapper class

class HiLoLines : public COleDispatchDriver
{
public:
	HiLoLines() {}		// Calls COleDispatchDriver default constructor
	HiLoLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	HiLoLines(const HiLoLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Gridlines wrapper class

class Gridlines : public COleDispatchDriver
{
public:
	Gridlines() {}		// Calls COleDispatchDriver default constructor
	Gridlines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Gridlines(const Gridlines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// DropLines wrapper class

class DropLines : public COleDispatchDriver
{
public:
	DropLines() {}		// Calls COleDispatchDriver default constructor
	DropLines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DropLines(const DropLines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// ErrorBars wrapper class

class ErrorBars : public COleDispatchDriver
{
public:
	ErrorBars() {}		// Calls COleDispatchDriver default constructor
	ErrorBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ErrorBars(const ErrorBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetEndStyle();
	void SetEndStyle(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ClearFormats();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// UpBars wrapper class

class UpBars : public COleDispatchDriver
{
public:
	UpBars() {}		// Calls COleDispatchDriver default constructor
	UpBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	UpBars(const UpBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// DownBars wrapper class

class DownBars : public COleDispatchDriver
{
public:
	DownBars() {}		// Calls COleDispatchDriver default constructor
	DownBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DownBars(const DownBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// ChartTitle wrapper class

class ChartTitle : public COleDispatchDriver
{
public:
	ChartTitle() {}		// Calls COleDispatchDriver default constructor
	ChartTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartTitle(const ChartTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// AxisTitle wrapper class

class AxisTitle : public COleDispatchDriver
{
public:
	AxisTitle() {}		// Calls COleDispatchDriver default constructor
	AxisTitle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AxisTitle(const AxisTitle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Floor wrapper class

class Floor : public COleDispatchDriver
{
public:
	Floor() {}		// Calls COleDispatchDriver default constructor
	Floor(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Floor(const Floor& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ClearFormats();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Walls wrapper class

class Walls : public COleDispatchDriver
{
public:
	Walls() {}		// Calls COleDispatchDriver default constructor
	Walls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Walls(const Walls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ClearFormats();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// PlotArea wrapper class

class PlotArea : public COleDispatchDriver
{
public:
	PlotArea() {}		// Calls COleDispatchDriver default constructor
	PlotArea(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PlotArea(const PlotArea& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ClearFormats();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// ChartArea wrapper class

class ChartArea : public COleDispatchDriver
{
public:
	ChartArea() {}		// Calls COleDispatchDriver default constructor
	ChartArea(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartArea(const ChartArea& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Clear();
	VARIANT ClearContents();
	VARIANT ClearFormats();
	VARIANT Copy();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Legend wrapper class

class Legend : public COleDispatchDriver
{
public:
	Legend() {}		// Calls COleDispatchDriver default constructor
	Legend(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Legend(const Legend& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHeight();
	void SetHeight(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPosition();
	void SetPosition(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetWidth();
	void SetWidth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT LegendEntries(const VARIANT& Index);
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// TickLabels wrapper class

class TickLabels : public COleDispatchDriver
{
public:
	TickLabels() {}		// Calls COleDispatchDriver default constructor
	TickLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TickLabels(const TickLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetNumberFormatLinked();
	void SetNumberFormatLinked(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Chart wrapper class

class Chart : public COleDispatchDriver
{
public:
	Chart() {}		// Calls COleDispatchDriver default constructor
	Chart(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Chart(const Chart& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetArea3DGroup();
	void SetArea3DGroup(const VARIANT&);
	VARIANT GetAutoScaling();
	void SetAutoScaling(const VARIANT&);
	VARIANT GetBar3DGroup();
	void SetBar3DGroup(const VARIANT&);
	VARIANT GetChartArea();
	void SetChartArea(const VARIANT&);
	VARIANT GetChartTitle();
	void SetChartTitle(const VARIANT&);
	VARIANT GetColumn3DGroup();
	void SetColumn3DGroup(const VARIANT&);
	VARIANT GetCorners();
	void SetCorners(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDepthPercent();
	void SetDepthPercent(const VARIANT&);
	VARIANT GetDisplayBlanksAs();
	void SetDisplayBlanksAs(const VARIANT&);
	VARIANT GetElevation();
	void SetElevation(const VARIANT&);
	VARIANT GetFloor();
	void SetFloor(const VARIANT&);
	VARIANT GetGapDepth();
	void SetGapDepth(const VARIANT&);
	VARIANT GetHasAxis();
	void SetHasAxis(const VARIANT&);
	VARIANT GetHasLegend();
	void SetHasLegend(const VARIANT&);
	VARIANT GetHasTitle();
	void SetHasTitle(const VARIANT&);
	VARIANT GetHeightPercent();
	void SetHeightPercent(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLegend();
	void SetLegend(const VARIANT&);
	VARIANT GetLine3DGroup();
	void SetLine3DGroup(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNext();
	void SetNext(const VARIANT&);
	VARIANT GetOnDoubleClick();
	void SetOnDoubleClick(const VARIANT&);
	VARIANT GetOnSheetActivate();
	void SetOnSheetActivate(const VARIANT&);
	VARIANT GetOnSheetDeactivate();
	void SetOnSheetDeactivate(const VARIANT&);
	VARIANT GetPageSetup();
	void SetPageSetup(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPerspective();
	void SetPerspective(const VARIANT&);
	VARIANT GetPie3DGroup();
	void SetPie3DGroup(const VARIANT&);
	VARIANT GetPlotArea();
	void SetPlotArea(const VARIANT&);
	VARIANT GetPlotVisibleOnly();
	void SetPlotVisibleOnly(const VARIANT&);
	VARIANT GetPrevious();
	void SetPrevious(const VARIANT&);
	VARIANT GetProtectContents();
	void SetProtectContents(const VARIANT&);
	VARIANT GetProtectDrawingObjects();
	void SetProtectDrawingObjects(const VARIANT&);
	VARIANT GetProtectionMode();
	void SetProtectionMode(const VARIANT&);
	VARIANT GetRightAngleAxes();
	void SetRightAngleAxes(const VARIANT&);
	VARIANT GetRotation();
	void SetRotation(const VARIANT&);
	VARIANT GetSizeWithWindow();
	void SetSizeWithWindow(const VARIANT&);
	VARIANT GetSubType();
	void SetSubType(const VARIANT&);
	VARIANT GetSurfaceGroup();
	void SetSurfaceGroup(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);
	VARIANT GetWalls();
	void SetWalls(const VARIANT&);
	VARIANT GetWallsAndGridlines2D();
	void SetWallsAndGridlines2D(const VARIANT&);

// Operations
public:
	VARIANT Activate();
	VARIANT Application();
	VARIANT ApplyDataLabels(const VARIANT& Type, const VARIANT& LegendKey);
	VARIANT Arcs(const VARIANT& Index);
	VARIANT AreaGroups(const VARIANT& Index);
	VARIANT AutoFormat(const VARIANT& Gallery, const VARIANT& Format);
	VARIANT Axes(const VARIANT& Type, const VARIANT& AxisGroup);
	VARIANT BarGroups(const VARIANT& Index);
	VARIANT Buttons(const VARIANT& Index);
	VARIANT ChartGroups(const VARIANT& Index);
	VARIANT ChartObjects(const VARIANT& Index);
	VARIANT ChartWizard(const VARIANT& Source, const VARIANT& Gallery, const VARIANT& Format, const VARIANT& PlotBy, const VARIANT& CategoryLabels, const VARIANT& SeriesLabels, const VARIANT& HasLegend, const VARIANT& Title, 
		const VARIANT& CategoryTitle, const VARIANT& ValueTitle, const VARIANT& ExtraTitle);
	VARIANT CheckBoxes(const VARIANT& Index);
	VARIANT CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest);
	VARIANT ColumnGroups(const VARIANT& Index);
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT CopyPicture(const VARIANT& Appearance, const VARIANT& Format, const VARIANT& Size);
	VARIANT CreatePublisher(const VARIANT& Edition, const VARIANT& Appearance, const VARIANT& Size, const VARIANT& ContainsPICT, const VARIANT& ContainsBIFF, const VARIANT& ContainsRTF, const VARIANT& ContainsVALU);
	VARIANT Delete();
	VARIANT Deselect();
	VARIANT DoughnutGroups(const VARIANT& Index);
	VARIANT DrawingObjects(const VARIANT& Index);
	VARIANT Drawings(const VARIANT& Index);
	VARIANT DropDowns(const VARIANT& Index);
	VARIANT _Evaluate(const VARIANT& Name);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT GroupBoxes(const VARIANT& Index);
	VARIANT GroupObjects(const VARIANT& Index);
	VARIANT Labels(const VARIANT& Index);
	VARIANT LineGroups(const VARIANT& Index);
	VARIANT Lines(const VARIANT& Index);
	VARIANT ListBoxes(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT OLEObjects(const VARIANT& Index);
	VARIANT OptionButtons(const VARIANT& Index);
	VARIANT Ovals(const VARIANT& Index);
	VARIANT Paste(const VARIANT& Type);
	VARIANT Pictures(const VARIANT& Index);
	VARIANT PieGroups(const VARIANT& Index);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly);
	VARIANT RadarGroups(const VARIANT& Index);
	VARIANT Rectangles(const VARIANT& Index);
	VARIANT SaveAs(const VARIANT& Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup);
	VARIANT ScrollBars(const VARIANT& Index);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SeriesCollection(const VARIANT& Index);
	VARIANT SetBackgroundPicture(const VARIANT& Filename);
	VARIANT Spinners(const VARIANT& Index);
	VARIANT TextBoxes(const VARIANT& Index);
	VARIANT Unprotect(const VARIANT& Password);
	VARIANT XYGroups(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Charts wrapper class

class Charts : public COleDispatchDriver
{
public:
	Charts() {}		// Calls COleDispatchDriver default constructor
	Charts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Charts(const Charts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetVisible();
	void SetVisible(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Before, const VARIANT& After, const VARIANT& Count);
	VARIANT Application();
	VARIANT Copy(const VARIANT& Before, const VARIANT& After);
	VARIANT Delete();
	VARIANT Item(const VARIANT& Index);
	VARIANT Move(const VARIANT& Before, const VARIANT& After);
	VARIANT PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate);
	VARIANT PrintPreview();
	VARIANT Select(const VARIANT& Replace);
};
/////////////////////////////////////////////////////////////////////////////
// ChartGroup wrapper class

class ChartGroup : public COleDispatchDriver
{
public:
	ChartGroup() {}		// Calls COleDispatchDriver default constructor
	ChartGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartGroup(const ChartGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAxisGroup();
	void SetAxisGroup(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDoughnutHoleSize();
	void SetDoughnutHoleSize(const VARIANT&);
	VARIANT GetDownBars();
	void SetDownBars(const VARIANT&);
	VARIANT GetDropLines();
	void SetDropLines(const VARIANT&);
	VARIANT GetFirstSliceAngle();
	void SetFirstSliceAngle(const VARIANT&);
	VARIANT GetGapWidth();
	void SetGapWidth(const VARIANT&);
	VARIANT GetHasDropLines();
	void SetHasDropLines(const VARIANT&);
	VARIANT GetHasHiLoLines();
	void SetHasHiLoLines(const VARIANT&);
	VARIANT GetHasRadarAxisLabels();
	void SetHasRadarAxisLabels(const VARIANT&);
	VARIANT GetHasSeriesLines();
	void SetHasSeriesLines(const VARIANT&);
	VARIANT GetHasUpDownBars();
	void SetHasUpDownBars(const VARIANT&);
	VARIANT GetHiLoLines();
	void SetHiLoLines(const VARIANT&);
	VARIANT GetOverlap();
	void SetOverlap(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetRadarAxisLabels();
	void SetRadarAxisLabels(const VARIANT&);
	VARIANT GetSeriesLines();
	void SetSeriesLines(const VARIANT&);
	VARIANT GetSubType();
	void SetSubType(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetUpBars();
	void SetUpBars(const VARIANT&);
	VARIANT GetVaryByCategories();
	void SetVaryByCategories(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT SeriesCollection(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// ChartGroups wrapper class

class ChartGroups : public COleDispatchDriver
{
public:
	ChartGroups() {}		// Calls COleDispatchDriver default constructor
	ChartGroups(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartGroups(const ChartGroups& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Axis wrapper class

class Axis : public COleDispatchDriver
{
public:
	Axis() {}		// Calls COleDispatchDriver default constructor
	Axis(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Axis(const Axis& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAxisBetweenCategories();
	void SetAxisBetweenCategories(const VARIANT&);
	VARIANT GetAxisGroup();
	void SetAxisGroup(const VARIANT&);
	VARIANT GetAxisTitle();
	void SetAxisTitle(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCategoryNames();
	void SetCategoryNames(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetCrosses();
	void SetCrosses(const VARIANT&);
	VARIANT GetCrossesAt();
	void SetCrossesAt(const VARIANT&);
	VARIANT GetHasMajorGridlines();
	void SetHasMajorGridlines(const VARIANT&);
	VARIANT GetHasMinorGridlines();
	void SetHasMinorGridlines(const VARIANT&);
	VARIANT GetHasTitle();
	void SetHasTitle(const VARIANT&);
	VARIANT GetMajorGridlines();
	void SetMajorGridlines(const VARIANT&);
	VARIANT GetMajorTickMark();
	void SetMajorTickMark(const VARIANT&);
	VARIANT GetMajorUnit();
	void SetMajorUnit(const VARIANT&);
	VARIANT GetMajorUnitIsAuto();
	void SetMajorUnitIsAuto(const VARIANT&);
	VARIANT GetMaximumScale();
	void SetMaximumScale(const VARIANT&);
	VARIANT GetMaximumScaleIsAuto();
	void SetMaximumScaleIsAuto(const VARIANT&);
	VARIANT GetMinimumScale();
	void SetMinimumScale(const VARIANT&);
	VARIANT GetMinimumScaleIsAuto();
	void SetMinimumScaleIsAuto(const VARIANT&);
	VARIANT GetMinorGridlines();
	void SetMinorGridlines(const VARIANT&);
	VARIANT GetMinorTickMark();
	void SetMinorTickMark(const VARIANT&);
	VARIANT GetMinorUnit();
	void SetMinorUnit(const VARIANT&);
	VARIANT GetMinorUnitIsAuto();
	void SetMinorUnitIsAuto(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetReversePlotOrder();
	void SetReversePlotOrder(const VARIANT&);
	VARIANT GetScaleType();
	void SetScaleType(const VARIANT&);
	VARIANT GetTickLabelPosition();
	void SetTickLabelPosition(const VARIANT&);
	VARIANT GetTickLabels();
	void SetTickLabels(const VARIANT&);
	VARIANT GetTickLabelSpacing();
	void SetTickLabelSpacing(const VARIANT&);
	VARIANT GetTickMarkSpacing();
	void SetTickMarkSpacing(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Axes wrapper class

class Axes : public COleDispatchDriver
{
public:
	Axes() {}		// Calls COleDispatchDriver default constructor
	Axes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Axes(const Axes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Type, const VARIANT& AxisGroup);
};
/////////////////////////////////////////////////////////////////////////////
// DataLabel wrapper class

class DataLabel : public COleDispatchDriver
{
public:
	DataLabel() {}		// Calls COleDispatchDriver default constructor
	DataLabel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DataLabel(const DataLabel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAutoText();
	void SetAutoText(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCaption();
	void SetCaption(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetLeft();
	void SetLeft(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetNumberFormatLinked();
	void SetNumberFormatLinked(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetShowLegendKey();
	void SetShowLegendKey(const VARIANT&);
	VARIANT GetText();
	void SetText(const VARIANT&);
	VARIANT GetTop();
	void SetTop(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Characters(const VARIANT& Start, const VARIANT& Length);
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// DataLabels wrapper class

class DataLabels : public COleDispatchDriver
{
public:
	DataLabels() {}		// Calls COleDispatchDriver default constructor
	DataLabels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DataLabels(const DataLabels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAutoText();
	void SetAutoText(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetHorizontalAlignment();
	void SetHorizontalAlignment(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNumberFormat();
	void SetNumberFormat(const VARIANT&);
	VARIANT GetNumberFormatLinked();
	void SetNumberFormatLinked(const VARIANT&);
	VARIANT GetOrientation();
	void SetOrientation(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetShadow();
	void SetShadow(const VARIANT&);
	VARIANT GetShowLegendKey();
	void SetShowLegendKey(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetVerticalAlignment();
	void SetVerticalAlignment(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Delete();
	VARIANT Item(const VARIANT& Index);
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Point wrapper class

class Point : public COleDispatchDriver
{
public:
	Point() {}		// Calls COleDispatchDriver default constructor
	Point(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Point(const Point& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDataLabel();
	void SetDataLabel(const VARIANT&);
	VARIANT GetExplosion();
	void SetExplosion(const VARIANT&);
	VARIANT GetHasDataLabel();
	void SetHasDataLabel(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetInvertIfNegative();
	void SetInvertIfNegative(const VARIANT&);
	VARIANT GetMarkerBackgroundColor();
	void SetMarkerBackgroundColor(const VARIANT&);
	VARIANT GetMarkerBackgroundColorIndex();
	void SetMarkerBackgroundColorIndex(const VARIANT&);
	VARIANT GetMarkerForegroundColor();
	void SetMarkerForegroundColor(const VARIANT&);
	VARIANT GetMarkerForegroundColorIndex();
	void SetMarkerForegroundColorIndex(const VARIANT&);
	VARIANT GetMarkerStyle();
	void SetMarkerStyle(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPictureType();
	void SetPictureType(const VARIANT&);
	VARIANT GetPictureUnit();
	void SetPictureUnit(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ApplyDataLabels(const VARIANT& Type, const VARIANT& LegendKey);
	VARIANT ClearFormats();
	VARIANT Copy();
	VARIANT Delete();
	VARIANT Paste();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Points wrapper class

class Points : public COleDispatchDriver
{
public:
	Points() {}		// Calls COleDispatchDriver default constructor
	Points(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Points(const Points& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// Series wrapper class

class Series : public COleDispatchDriver
{
public:
	Series() {}		// Calls COleDispatchDriver default constructor
	Series(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Series(const Series& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetAxisGroup();
	void SetAxisGroup(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetErrorBars();
	void SetErrorBars(const VARIANT&);
	VARIANT GetExplosion();
	void SetExplosion(const VARIANT&);
	VARIANT GetFormula();
	void SetFormula(const VARIANT&);
	VARIANT GetFormulaLocal();
	void SetFormulaLocal(const VARIANT&);
	VARIANT GetFormulaR1C1();
	void SetFormulaR1C1(const VARIANT&);
	VARIANT GetFormulaR1C1Local();
	void SetFormulaR1C1Local(const VARIANT&);
	VARIANT GetHasDataLabels();
	void SetHasDataLabels(const VARIANT&);
	VARIANT GetHasErrorBars();
	void SetHasErrorBars(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetInvertIfNegative();
	void SetInvertIfNegative(const VARIANT&);
	VARIANT GetMarkerBackgroundColor();
	void SetMarkerBackgroundColor(const VARIANT&);
	VARIANT GetMarkerBackgroundColorIndex();
	void SetMarkerBackgroundColorIndex(const VARIANT&);
	VARIANT GetMarkerForegroundColor();
	void SetMarkerForegroundColor(const VARIANT&);
	VARIANT GetMarkerForegroundColorIndex();
	void SetMarkerForegroundColorIndex(const VARIANT&);
	VARIANT GetMarkerStyle();
	void SetMarkerStyle(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPictureType();
	void SetPictureType(const VARIANT&);
	VARIANT GetPictureUnit();
	void SetPictureUnit(const VARIANT&);
	VARIANT GetPlotOrder();
	void SetPlotOrder(const VARIANT&);
	VARIANT GetSmooth();
	void SetSmooth(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);
	VARIANT GetValues();
	void SetValues(const VARIANT&);
	VARIANT GetXValues();
	void SetXValues(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ApplyDataLabels(const VARIANT& Type, const VARIANT& LegendKey);
	VARIANT ClearFormats();
	VARIANT Copy();
	VARIANT DataLabels(const VARIANT& Index);
	VARIANT Delete();
	VARIANT ErrorBar(const VARIANT& Direction, const VARIANT& Include, const VARIANT& Type, const VARIANT& Amount, const VARIANT& MinusValues);
	VARIANT Paste();
	VARIANT Points(const VARIANT& Index);
	VARIANT Select();
	VARIANT Trendlines(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// SeriesCollection wrapper class

class SeriesCollection : public COleDispatchDriver
{
public:
	SeriesCollection() {}		// Calls COleDispatchDriver default constructor
	SeriesCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SeriesCollection(const SeriesCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Source, const VARIANT& Rowcol, const VARIANT& SeriesLabels, const VARIANT& CategoryLabels, const VARIANT& Replace);
	VARIANT Application();
	VARIANT Extend(const VARIANT& Source, const VARIANT& Rowcol, const VARIANT& CategoryLabels);
	VARIANT Item(const VARIANT& Index);
	VARIANT Paste(const VARIANT& Rowcol, const VARIANT& SeriesLabels, const VARIANT& CategoryLabels, const VARIANT& Replace, const VARIANT& NewSeries);
};
/////////////////////////////////////////////////////////////////////////////
// LegendEntry wrapper class

class LegendEntry : public COleDispatchDriver
{
public:
	LegendEntry() {}		// Calls COleDispatchDriver default constructor
	LegendEntry(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LegendEntry(const LegendEntry& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetFont();
	void SetFont(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetLegendKey();
	void SetLegendKey(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// LegendEntries wrapper class

class LegendEntries : public COleDispatchDriver
{
public:
	LegendEntries() {}		// Calls COleDispatchDriver default constructor
	LegendEntries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LegendEntries(const LegendEntries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// LegendKey wrapper class

class LegendKey : public COleDispatchDriver
{
public:
	LegendKey() {}		// Calls COleDispatchDriver default constructor
	LegendKey(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	LegendKey(const LegendKey& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetInterior();
	void SetInterior(const VARIANT&);
	VARIANT GetInvertIfNegative();
	void SetInvertIfNegative(const VARIANT&);
	VARIANT GetMarkerBackgroundColor();
	void SetMarkerBackgroundColor(const VARIANT&);
	VARIANT GetMarkerBackgroundColorIndex();
	void SetMarkerBackgroundColorIndex(const VARIANT&);
	VARIANT GetMarkerForegroundColor();
	void SetMarkerForegroundColor(const VARIANT&);
	VARIANT GetMarkerForegroundColorIndex();
	void SetMarkerForegroundColorIndex(const VARIANT&);
	VARIANT GetMarkerStyle();
	void SetMarkerStyle(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetSmooth();
	void SetSmooth(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ClearFormats();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Trendline wrapper class

class Trendline : public COleDispatchDriver
{
public:
	Trendline() {}		// Calls COleDispatchDriver default constructor
	Trendline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Trendline(const Trendline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetBackward();
	void SetBackward(const VARIANT&);
	VARIANT GetBorder();
	void SetBorder(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetDataLabel();
	void SetDataLabel(const VARIANT&);
	VARIANT GetDisplayEquation();
	void SetDisplayEquation(const VARIANT&);
	VARIANT GetDisplayRSquared();
	void SetDisplayRSquared(const VARIANT&);
	VARIANT GetForward();
	void SetForward(const VARIANT&);
	VARIANT GetIndex();
	void SetIndex(const VARIANT&);
	VARIANT GetIntercept();
	void SetIntercept(const VARIANT&);
	VARIANT GetInterceptIsAuto();
	void SetInterceptIsAuto(const VARIANT&);
	VARIANT GetName();
	void SetName(const VARIANT&);
	VARIANT GetNameIsAuto();
	void SetNameIsAuto(const VARIANT&);
	VARIANT GetOrder();
	void SetOrder(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetPeriod();
	void SetPeriod(const VARIANT&);
	VARIANT GetType();
	void SetType(const VARIANT&);

// Operations
public:
	VARIANT Application();
	VARIANT ClearFormats();
	VARIANT Delete();
	VARIANT Select();
};
/////////////////////////////////////////////////////////////////////////////
// Trendlines wrapper class

class Trendlines : public COleDispatchDriver
{
public:
	Trendlines() {}		// Calls COleDispatchDriver default constructor
	Trendlines(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Trendlines(const Trendlines& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCount();
	void SetCount(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);

// Operations
public:
	VARIANT _NewEnum();
	VARIANT Add(const VARIANT& Type, const VARIANT& Order, const VARIANT& Period, const VARIANT& Forward, const VARIANT& Backward, const VARIANT& Intercept, const VARIANT& DisplayEquation, const VARIANT& DisplayRSquared, const VARIANT& Name);
	VARIANT Application();
	VARIANT Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// AutoCorrect wrapper class

class AutoCorrect : public COleDispatchDriver
{
public:
	AutoCorrect() {}		// Calls COleDispatchDriver default constructor
	AutoCorrect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AutoCorrect(const AutoCorrect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	VARIANT GetCapitalizeNamesOfDays();
	void SetCapitalizeNamesOfDays(const VARIANT&);
	VARIANT GetCreator();
	void SetCreator(const VARIANT&);
	VARIANT GetParent();
	void SetParent(const VARIANT&);
	VARIANT GetReplacementList();
	void SetReplacementList(const VARIANT&);
	VARIANT GetReplaceText();
	void SetReplaceText(const VARIANT&);
	VARIANT GetTwoInitialCapitals();
	void SetTwoInitialCapitals(const VARIANT&);

// Operations
public:
	VARIANT AddReplacement(const VARIANT& What, const VARIANT& Replacement);
	VARIANT Application();
	VARIANT DeleteReplacement(const VARIANT& What);
};
