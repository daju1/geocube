// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// ChartObjects10 wrapper class

class ChartObjects10 : public COleDispatchDriver
{
public:
	ChartObjects10() {}		// Calls COleDispatchDriver default constructor
	ChartObjects10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartObjects10(const ChartObjects10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(long Appearance, long Format);
	VARIANT Cut();
	VARIANT Delete();
	LPDISPATCH Duplicate();
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetLeft();
	void SetLeft(double newValue);
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT& newValue);
	BOOL GetPrintObject();
	void SetPrintObject(BOOL bNewValue);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
	double GetTop();
	void SetTop(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	double GetWidth();
	void SetWidth(double newValue);
	LPDISPATCH GetShapeRange();
	BOOL GetRoundedCorners();
	void SetRoundedCorners(BOOL bNewValue);
	LPDISPATCH GetBorder();
	LPDISPATCH GetInterior();
	BOOL GetShadow();
	void SetShadow(BOOL bNewValue);
	LPDISPATCH Add(double Left, double Top, double Width, double Height);
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN _NewEnum();
};
/////////////////////////////////////////////////////////////////////////////
// ChartObject10 wrapper class

class ChartObject10 : public COleDispatchDriver
{
public:
	ChartObject10() {}		// Calls COleDispatchDriver default constructor
	ChartObject10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartObject10(const ChartObject10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetBottomRightCell();
	VARIANT BringToFront();
	VARIANT Copy();
	VARIANT CopyPicture(long Appearance, long Format);
	VARIANT Cut();
	VARIANT Delete();
	LPDISPATCH Duplicate();
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	long GetIndex();
	double GetLeft();
	void SetLeft(double newValue);
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetPlacement();
	void SetPlacement(const VARIANT& newValue);
	BOOL GetPrintObject();
	void SetPrintObject(BOOL bNewValue);
	VARIANT Select(const VARIANT& Replace);
	VARIANT SendToBack();
	double GetTop();
	void SetTop(double newValue);
	LPDISPATCH GetTopLeftCell();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	double GetWidth();
	void SetWidth(double newValue);
	long GetZOrder();
	LPDISPATCH GetShapeRange();
	VARIANT Activate();
	LPDISPATCH GetChart();
	BOOL GetProtectChartObject();
	void SetProtectChartObject(BOOL bNewValue);
	BOOL GetRoundedCorners();
	void SetRoundedCorners(BOOL bNewValue);
	LPDISPATCH GetBorder();
	LPDISPATCH GetInterior();
	BOOL GetShadow();
	void SetShadow(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// _Chart10 wrapper class

class _Chart10 : public COleDispatchDriver
{
public:
	_Chart10() {}		// Calls COleDispatchDriver default constructor
	_Chart10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Chart10(const _Chart10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Activate();
	void Copy(const VARIANT& Before, const VARIANT& After);
	void Delete();
	CString GetCodeName();
	CString Get_CodeName();
	void Set_CodeName(LPCTSTR lpszNewValue);
	long GetIndex();
	void Move(const VARIANT& Before, const VARIANT& After);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNext();
	LPDISPATCH GetPageSetup();
	LPDISPATCH GetPrevious();
	void PrintPreview(const VARIANT& EnableChanges);
	BOOL GetProtectContents();
	BOOL GetProtectDrawingObjects();
	BOOL GetProtectionMode();
	void Select(const VARIANT& Replace);
	void Unprotect(const VARIANT& Password);
	long GetVisible();
	void SetVisible(long nNewValue);
	LPDISPATCH GetShapes();
	LPDISPATCH GetArea3DGroup();
	LPDISPATCH AreaGroups(const VARIANT& Index);
	BOOL GetAutoScaling();
	void SetAutoScaling(BOOL bNewValue);
	LPDISPATCH Axes(const VARIANT& Type, long AxisGroup);
	void SetBackgroundPicture(LPCTSTR Filename);
	LPDISPATCH GetBar3DGroup();
	LPDISPATCH BarGroups(const VARIANT& Index);
	LPDISPATCH GetChartArea();
	LPDISPATCH ChartGroups(const VARIANT& Index);
	LPDISPATCH ChartObjects(const VARIANT& Index);
	LPDISPATCH GetChartTitle();
	void ChartWizard(const VARIANT& Source, const VARIANT& Gallery, const VARIANT& Format, const VARIANT& PlotBy, const VARIANT& CategoryLabels, const VARIANT& SeriesLabels, const VARIANT& HasLegend, const VARIANT& Title, 
		const VARIANT& CategoryTitle, const VARIANT& ValueTitle, const VARIANT& ExtraTitle);
	void CheckSpelling(const VARIANT& CustomDictionary, const VARIANT& IgnoreUppercase, const VARIANT& AlwaysSuggest, const VARIANT& SpellLang);
	LPDISPATCH GetColumn3DGroup();
	LPDISPATCH ColumnGroups(const VARIANT& Index);
	void CopyPicture(long Appearance, long Format, long Size);
	LPDISPATCH GetCorners();
	void CreatePublisher(const VARIANT& Edition, long Appearance, long Size, const VARIANT& ContainsPICT, const VARIANT& ContainsBIFF, const VARIANT& ContainsRTF, const VARIANT& ContainsVALU);
	LPDISPATCH GetDataTable();
	long GetDepthPercent();
	void SetDepthPercent(long nNewValue);
	void Deselect();
	long GetDisplayBlanksAs();
	void SetDisplayBlanksAs(long nNewValue);
	LPDISPATCH DoughnutGroups(const VARIANT& Index);
	long GetElevation();
	void SetElevation(long nNewValue);
	VARIANT Evaluate(const VARIANT& Name);
	VARIANT _Evaluate(const VARIANT& Name);
	LPDISPATCH GetFloor();
	long GetGapDepth();
	void SetGapDepth(long nNewValue);
	VARIANT GetHasAxis(const VARIANT& Index1, const VARIANT& Index2);
	void SetHasAxis(const VARIANT& Index1, const VARIANT& Index2, const VARIANT& newValue);
	BOOL GetHasDataTable();
	void SetHasDataTable(BOOL bNewValue);
	BOOL GetHasLegend();
	void SetHasLegend(BOOL bNewValue);
	BOOL GetHasTitle();
	void SetHasTitle(BOOL bNewValue);
	long GetHeightPercent();
	void SetHeightPercent(long nNewValue);
	LPDISPATCH GetHyperlinks();
	LPDISPATCH GetLegend();
	LPDISPATCH GetLine3DGroup();
	LPDISPATCH LineGroups(const VARIANT& Index);
	LPDISPATCH Location(long Where, const VARIANT& Name);
	LPDISPATCH OLEObjects(const VARIANT& Index);
	void Paste(const VARIANT& Type);
	long GetPerspective();
	void SetPerspective(long nNewValue);
	LPDISPATCH GetPie3DGroup();
	LPDISPATCH PieGroups(const VARIANT& Index);
	LPDISPATCH GetPlotArea();
	BOOL GetPlotVisibleOnly();
	void SetPlotVisibleOnly(BOOL bNewValue);
	LPDISPATCH RadarGroups(const VARIANT& Index);
	VARIANT GetRightAngleAxes();
	void SetRightAngleAxes(const VARIANT& newValue);
	VARIANT GetRotation();
	void SetRotation(const VARIANT& newValue);
	LPDISPATCH SeriesCollection(const VARIANT& Index);
	BOOL GetSizeWithWindow();
	void SetSizeWithWindow(BOOL bNewValue);
	BOOL GetShowWindow();
	void SetShowWindow(BOOL bNewValue);
	LPDISPATCH GetSurfaceGroup();
	long GetChartType();
	void SetChartType(long nNewValue);
	void ApplyCustomType(long ChartType, const VARIANT& TypeName);
	LPDISPATCH GetWalls();
	BOOL GetWallsAndGridlines2D();
	void SetWallsAndGridlines2D(BOOL bNewValue);
	LPDISPATCH XYGroups(const VARIANT& Index);
	long GetBarShape();
	void SetBarShape(long nNewValue);
	long GetPlotBy();
	void SetPlotBy(long nNewValue);
	BOOL GetProtectFormatting();
	void SetProtectFormatting(BOOL bNewValue);
	BOOL GetProtectData();
	void SetProtectData(BOOL bNewValue);
	BOOL GetProtectGoalSeek();
	void SetProtectGoalSeek(BOOL bNewValue);
	BOOL GetProtectSelection();
	void SetProtectSelection(BOOL bNewValue);
	void GetChartElement(long x, long y, long* ElementID, long* Arg1, long* Arg2);
	void SetSourceData(LPDISPATCH Source, const VARIANT& PlotBy);
	BOOL Export(LPCTSTR Filename, const VARIANT& FilterName, const VARIANT& Interactive);
	void Refresh();
	LPDISPATCH GetPivotLayout();
	BOOL GetHasPivotFields();
	void SetHasPivotFields(BOOL bNewValue);
	LPDISPATCH GetScripts();
	void PrintOut(const VARIANT& From, const VARIANT& To, const VARIANT& Copies, const VARIANT& Preview, const VARIANT& ActivePrinter, const VARIANT& PrintToFile, const VARIANT& Collate, const VARIANT& PrToFileName);
	LPDISPATCH GetTab();
	LPDISPATCH GetMailEnvelope();
	void ApplyDataLabels(long Type, const VARIANT& LegendKey, const VARIANT& AutoText, const VARIANT& HasLeaderLines, const VARIANT& ShowSeriesName, const VARIANT& ShowCategoryName, const VARIANT& ShowValue, const VARIANT& ShowPercentage, 
		const VARIANT& ShowBubbleSize, const VARIANT& Separator);
	void SaveAs(LPCTSTR Filename, const VARIANT& FileFormat, const VARIANT& Password, const VARIANT& WriteResPassword, const VARIANT& ReadOnlyRecommended, const VARIANT& CreateBackup, const VARIANT& AddToMru, const VARIANT& TextCodepage, 
		const VARIANT& TextVisualLayout, const VARIANT& Local);
	void Protect(const VARIANT& Password, const VARIANT& DrawingObjects, const VARIANT& Contents, const VARIANT& Scenarios, const VARIANT& UserInterfaceOnly);
};
/////////////////////////////////////////////////////////////////////////////
// ChartArea10 wrapper class

class ChartArea10 : public COleDispatchDriver
{
public:
	ChartArea10() {}		// Calls COleDispatchDriver default constructor
	ChartArea10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ChartArea10(const ChartArea10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	VARIANT Select();
	LPDISPATCH GetBorder();
	VARIANT Clear();
	VARIANT ClearContents();
	VARIANT Copy();
	LPDISPATCH GetFont();
	BOOL GetShadow();
	void SetShadow(BOOL bNewValue);
	VARIANT ClearFormats();
	double GetHeight();
	void SetHeight(double newValue);
	LPDISPATCH GetInterior();
	LPDISPATCH GetFill();
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	VARIANT GetAutoScaleFont();
	void SetAutoScaleFont(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// PlotArea10 wrapper class

class PlotArea10 : public COleDispatchDriver
{
public:
	PlotArea10() {}		// Calls COleDispatchDriver default constructor
	PlotArea10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	PlotArea10(const PlotArea10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	CString GetName();
	VARIANT Select();
	LPDISPATCH GetBorder();
	VARIANT ClearFormats();
	double GetHeight();
	void SetHeight(double newValue);
	LPDISPATCH GetInterior();
	LPDISPATCH GetFill();
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetInsideLeft();
	double GetInsideTop();
	double GetInsideWidth();
	double GetInsideHeight();
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

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Add(const VARIANT& Source, long Rowcol, const VARIANT& SeriesLabels, const VARIANT& CategoryLabels, const VARIANT& Replace);
	long GetCount();
	VARIANT Extend(const VARIANT& Source, const VARIANT& Rowcol, const VARIANT& CategoryLabels);
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN _NewEnum();
	VARIANT Paste(long Rowcol, const VARIANT& SeriesLabels, const VARIANT& CategoryLabels, const VARIANT& Replace, const VARIANT& NewSeries);
	LPDISPATCH NewSeries();
};
/////////////////////////////////////////////////////////////////////////////
// SeriesCollection10 wrapper class

class SeriesCollection10 : public COleDispatchDriver
{
public:
	SeriesCollection10() {}		// Calls COleDispatchDriver default constructor
	SeriesCollection10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	SeriesCollection10(const SeriesCollection10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH Add(const VARIANT& Source, long Rowcol, const VARIANT& SeriesLabels, const VARIANT& CategoryLabels, const VARIANT& Replace);
	long GetCount();
	VARIANT Extend(const VARIANT& Source, const VARIANT& Rowcol, const VARIANT& CategoryLabels);
	LPDISPATCH Item(const VARIANT& Index);
	LPUNKNOWN _NewEnum();
	VARIANT Paste(long Rowcol, const VARIANT& SeriesLabels, const VARIANT& CategoryLabels, const VARIANT& Replace, const VARIANT& NewSeries);
	LPDISPATCH NewSeries();
};
/////////////////////////////////////////////////////////////////////////////
// Series10 wrapper class

class Series10 : public COleDispatchDriver
{
public:
	Series10() {}		// Calls COleDispatchDriver default constructor
	Series10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Series10(const Series10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetAxisGroup();
	void SetAxisGroup(long nNewValue);
	LPDISPATCH GetBorder();
	VARIANT ClearFormats();
	VARIANT Copy();
	LPDISPATCH DataLabels(const VARIANT& Index);
	VARIANT Delete();
	VARIANT ErrorBar(long Direction, long Include, long Type, const VARIANT& Amount, const VARIANT& MinusValues);
	LPDISPATCH GetErrorBars();
	long GetExplosion();
	void SetExplosion(long nNewValue);
	CString GetFormula();
	void SetFormula(LPCTSTR lpszNewValue);
	CString GetFormulaLocal();
	void SetFormulaLocal(LPCTSTR lpszNewValue);
	CString GetFormulaR1C1();
	void SetFormulaR1C1(LPCTSTR lpszNewValue);
	CString GetFormulaR1C1Local();
	void SetFormulaR1C1Local(LPCTSTR lpszNewValue);
	BOOL GetHasDataLabels();
	void SetHasDataLabels(BOOL bNewValue);
	BOOL GetHasErrorBars();
	void SetHasErrorBars(BOOL bNewValue);
	LPDISPATCH GetInterior();
	LPDISPATCH GetFill();
	BOOL GetInvertIfNegative();
	void SetInvertIfNegative(BOOL bNewValue);
	long GetMarkerBackgroundColor();
	void SetMarkerBackgroundColor(long nNewValue);
	long GetMarkerBackgroundColorIndex();
	void SetMarkerBackgroundColorIndex(long nNewValue);
	long GetMarkerForegroundColor();
	void SetMarkerForegroundColor(long nNewValue);
	long GetMarkerForegroundColorIndex();
	void SetMarkerForegroundColorIndex(long nNewValue);
	long GetMarkerSize();
	void SetMarkerSize(long nNewValue);
	long GetMarkerStyle();
	void SetMarkerStyle(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT Paste();
	long GetPictureType();
	void SetPictureType(long nNewValue);
	long GetPictureUnit();
	void SetPictureUnit(long nNewValue);
	long GetPlotOrder();
	void SetPlotOrder(long nNewValue);
	LPDISPATCH Points(const VARIANT& Index);
	VARIANT Select();
	BOOL GetSmooth();
	void SetSmooth(BOOL bNewValue);
	LPDISPATCH Trendlines(const VARIANT& Index);
	long GetType();
	void SetType(long nNewValue);
	long GetChartType();
	void SetChartType(long nNewValue);
	void ApplyCustomType(long ChartType);
	VARIANT GetValues();
	void SetValues(const VARIANT& newValue);
	VARIANT GetXValues();
	void SetXValues(const VARIANT& newValue);
	VARIANT GetBubbleSizes();
	void SetBubbleSizes(const VARIANT& newValue);
	long GetBarShape();
	void SetBarShape(long nNewValue);
	BOOL GetApplyPictToSides();
	void SetApplyPictToSides(BOOL bNewValue);
	BOOL GetApplyPictToFront();
	void SetApplyPictToFront(BOOL bNewValue);
	BOOL GetApplyPictToEnd();
	void SetApplyPictToEnd(BOOL bNewValue);
	BOOL GetHas3DEffect();
	void SetHas3DEffect(BOOL bNewValue);
	BOOL GetShadow();
	void SetShadow(BOOL bNewValue);
	BOOL GetHasLeaderLines();
	void SetHasLeaderLines(BOOL bNewValue);
	LPDISPATCH GetLeaderLines();
	VARIANT ApplyDataLabels(long Type, const VARIANT& LegendKey, const VARIANT& AutoText, const VARIANT& HasLeaderLines, const VARIANT& ShowSeriesName, const VARIANT& ShowCategoryName, const VARIANT& ShowValue, const VARIANT& ShowPercentage, 
		const VARIANT& ShowBubbleSize, const VARIANT& Separator);
};
