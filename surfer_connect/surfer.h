// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IWksRange wrapper class

class IWksRange : public COleDispatchDriver
{
public:
	IWksRange() {}		// Calls COleDispatchDriver default constructor
	IWksRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksRange(const IWksRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	VARIANT GetValue();
	void SetValue(const VARIANT& newValue);
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	long GetRow();
	long GetColumn();
	long GetLastRow();
	long GetLastColumn();
	double GetCount();
	long GetRowCount();
	long GetColumnCount();
	BOOL GetIsEntireRow();
	BOOL GetIsEntireColumn();
	LPDISPATCH GetEntireRow();
	LPDISPATCH GetEntireColumn();
	VARIANT GetColumnWidth();
	void SetColumnWidth(double newValue);
	VARIANT GetRowHeight();
	void SetRowHeight(double newValue);
	LPDISPATCH GetFormat();
	void Clear();
	void Copy();
	void Cut();
	BOOL Paste(BOOL ClipToRange);
	BOOL PasteSpecial(long Format, BOOL ClipToRange);
	void Insert(long Direction);
	void Delete(long Direction);
	void Sort(long Col1, long Order1, long Col2, long Order2, long Col3, long Order3, BOOL Header, BOOL MatchCase);
	LPDISPATCH Statistics(BOOL Sample, BOOL Header, long Flags);
	LPDISPATCH Cells(const VARIANT& Row, const VARIANT& Col, const VARIANT& LastRow, const VARIANT& LastCol);
	LPDISPATCH Rows(const VARIANT& Row1, const VARIANT& Row2);
	LPDISPATCH Columns(const VARIANT& Col1, const VARIANT& Col2);
};
/////////////////////////////////////////////////////////////////////////////
// IWksCellFormat wrapper class

class IWksCellFormat : public COleDispatchDriver
{
public:
	IWksCellFormat() {}		// Calls COleDispatchDriver default constructor
	IWksCellFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksCellFormat(const IWksCellFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	VARIANT GetAlignment();
	void SetAlignment(long nNewValue);
	VARIANT GetBackColor();
	void SetBackColor(long nNewValue);
	VARIANT GetNumericType();
	void SetNumericType(long nNewValue);
	VARIANT GetDigits();
	void SetDigits(short nNewValue);
	VARIANT GetThousands();
	void SetThousands(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IWksStatistics wrapper class

class IWksStatistics : public COleDispatchDriver
{
public:
	IWksStatistics() {}		// Calls COleDispatchDriver default constructor
	IWksStatistics(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksStatistics(const IWksStatistics& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetColumnCount();
	VARIANT GetLabel(long Col);
	VARIANT GetFirstRow(long Col);
	VARIANT GetLastRow(long Col);
	VARIANT GetCount(long Col);
	VARIANT GetMissing(long Col);
	VARIANT GetSum(long Col);
	VARIANT GetMinimum(long Col);
	VARIANT GetMaximum(long Col);
	VARIANT GetRange(long Col);
	VARIANT GetMean(long Col);
	VARIANT GetMedian(long Col);
	VARIANT GetFirstQuartile(long Col);
	VARIANT GetThirdQuartile(long Col);
	VARIANT GetStandardError(long Col);
	VARIANT GetConfidenceInterval95(long Col);
	VARIANT GetConfidenceInterval99(long Col);
	VARIANT GetVariance(long Col);
	VARIANT GetAverageDeviation(long Col);
	VARIANT GetStandardDeviation(long Col);
	VARIANT GetCoefficientOfVariation(long Col);
	VARIANT GetSkewness(long Col);
	VARIANT GetKurtosis(long Col);
	VARIANT GetKSStatistic(long Col);
	VARIANT GetKSCriticalValue90(long Col);
	VARIANT GetKSCriticalValue95(long Col);
	VARIANT GetKSCriticalValue99(long Col);
};
/////////////////////////////////////////////////////////////////////////////
// IWksWindows wrapper class

class IWksWindows : public COleDispatchDriver
{
public:
	IWksWindows() {}		// Calls COleDispatchDriver default constructor
	IWksWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksWindows(const IWksWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Item);
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Add();
};
/////////////////////////////////////////////////////////////////////////////
// IWksPageSetup wrapper class

class IWksPageSetup : public COleDispatchDriver
{
public:
	IWksPageSetup() {}		// Calls COleDispatchDriver default constructor
	IWksPageSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksPageSetup(const IWksPageSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetOrientation();
	void SetOrientation(long nNewValue);
	long GetPaperSize();
	void SetPaperSize(long nNewValue);
	long GetPaperSource();
	void SetPaperSource(long nNewValue);
	long GetFitToPagesAcross();
	void SetFitToPagesAcross(long nNewValue);
	long GetFitToPagesDown();
	void SetFitToPagesDown(long nNewValue);
	long GetAdjustToPercentage();
	void SetAdjustToPercentage(long nNewValue);
	double GetTopMargin();
	void SetTopMargin(double newValue);
	double GetBottomMargin();
	void SetBottomMargin(double newValue);
	double GetLeftMargin();
	void SetLeftMargin(double newValue);
	double GetRightMargin();
	void SetRightMargin(double newValue);
	double GetHeaderMargin();
	void SetHeaderMargin(double newValue);
	double GetFooterMargin();
	void SetFooterMargin(double newValue);
	BOOL GetCenterHorizontally();
	void SetCenterHorizontally(BOOL bNewValue);
	BOOL GetCenterVertically();
	void SetCenterVertically(BOOL bNewValue);
	BOOL GetPrintGridlines();
	void SetPrintGridlines(BOOL bNewValue);
	BOOL GetPrintRowAndColumnHeader();
	void SetPrintRowAndColumnHeader(BOOL bNewValue);
	BOOL GetPrintBlackAndWhite();
	void SetPrintBlackAndWhite(BOOL bNewValue);
	BOOL GetPrintAcrossAndThenDown();
	void SetPrintAcrossAndThenDown(BOOL bNewValue);
	CString GetHeader();
	void SetHeader(LPCTSTR lpszNewValue);
	CString GetFooter();
	void SetFooter(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IApplication wrapper class

class IApplication : public COleDispatchDriver
{
public:
	IApplication() {}		// Calls COleDispatchDriver default constructor
	IApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IApplication(const IApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetFullName();
	CString GetPath();
	CString GetDefaultFilePath();
	void SetDefaultFilePath(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	LPDISPATCH GetActiveDocument();
	LPDISPATCH GetActiveWindow();
	LPDISPATCH GetDocuments();
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	CString GetVersion();
	LPDISPATCH GetWindows();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetShowStatusBar();
	void SetShowStatusBar(BOOL bNewValue);
	void Quit();
	CString GetName();
	LPDISPATCH NewVarioComponent(long VarioType, double Param1, double Param2, double Power, double AnisotropyRatio, double AnisotropyAngle);
	BOOL GridData(LPCTSTR DataFile, long xCol, long yCol, long zCol, const VARIANT& ExclusionFilter, const VARIANT& DupMethod, const VARIANT& xDupTol, const VARIANT& yDupTol, const VARIANT& NumCols, const VARIANT& NumRows, const VARIANT& xMin, 
		const VARIANT& xMax, const VARIANT& yMin, const VARIANT& yMax, const VARIANT& Algorithm, const VARIANT& ShowReport, const VARIANT& SearchEnable, const VARIANT& SearchNumSectors, const VARIANT& SearchRad1, const VARIANT& SearchRad2, 
		const VARIANT& SearchAngle, const VARIANT& SearchMinData, const VARIANT& SearchDataPerSect, const VARIANT& SearchMaxEmpty, const VARIANT& FaultFileName, const VARIANT& BreakFileName, const VARIANT& AnisotropyRatio, 
		const VARIANT& AnisotropyAngle, const VARIANT& IDPower, const VARIANT& IDSmoothing, const VARIANT& KrigType, const VARIANT& KrigDriftType, const VARIANT& KrigStdDevGrid, const VARIANT& KrigVariogram, const VARIANT& MCMaxResidual, 
		const VARIANT& MCMaxIterations, const VARIANT& MCInternalTension, const VARIANT& MCBoundaryTension, const VARIANT& MCRelaxationFactor, const VARIANT& ShepSmoothFactor, const VARIANT& ShepQuadraticNeighbors, 
		const VARIANT& ShepWeightingNeighbors, const VARIANT& ShepRange1, const VARIANT& ShepRange2, const VARIANT& RegrMaxXOrder, const VARIANT& RegrMaxYOrder, const VARIANT& RegrMaxTotalOrder, const VARIANT& RBBasisType, 
		const VARIANT& RBRSquared, LPCTSTR OutGrid, long OutFmt, const VARIANT& SearchMaxData, const VARIANT& KrigStdDevFormat, const VARIANT& DataMetric, const VARIANT& LocalPolyOrder, const VARIANT& LocalPolyPower, 
		const VARIANT& TriangleFileName);
	BOOL GridData(LPCTSTR DataFile, 
		long xCol, long yCol, long zCol, 
		const VARIANT& ExclusionFilter, 
		const VARIANT& DupMethod, 
		const VARIANT& xDupTol, const VARIANT& yDupTol, 
		const VARIANT& NumCols, const VARIANT& NumRows, 
		const VARIANT& xMin, const VARIANT& xMax, 
		const VARIANT& yMin, const VARIANT& yMax, 
		const VARIANT& Algorithm, 
		const VARIANT& ShowReport);
	BOOL GridFunction(LPCTSTR Function, double xMin, double xMax, double xInc, double yMin, double yMax, double yInc, LPCTSTR OutGrid, long OutFmt);
	BOOL GridMath(LPCTSTR Function, LPCTSTR InGridA, LPCTSTR InGridB, LPCTSTR OutGridC, long OutFmt);
	BOOL GridSplineSmooth(LPCTSTR InGrid, long nRow, long nCol, long Method, LPCTSTR OutGrid, long OutFmt);
	BOOL GridBlank(LPCTSTR InGrid, LPCTSTR BlankFile, LPCTSTR OutGrid, long OutFmt);
	BOOL GridConvert(LPCTSTR InGrid, LPCTSTR OutGrid, long OutFmt);
	// method 'GridVolume' not emitted because of invalid return type or parameter type
	BOOL GridSlice(LPCTSTR InGrid, LPCTSTR BlankFile, LPCTSTR OutBlankFile, LPCTSTR OutDataFile, const VARIANT& OutsideVal, const VARIANT& BlankVal);
	LPDISPATCH GridResiduals(LPCTSTR InGrid, LPCTSTR DataFile, long xCol, long yCol, long zCol, long ResidCol);
	BOOL GridTransform(LPCTSTR InGrid, long Operation, double xOffset, double yOffset, double xScale, double yScale, double Rotation, LPCTSTR OutGrid, long OutFmt);
	BOOL GridExtract(LPCTSTR InGrid, long r1, long r2, long rFreq, long c1, long c2, long cFreq, LPCTSTR OutGrid, long OutFmt);
	BOOL GridCalculus(LPCTSTR InGrid, long Operation, double Param1, LPCTSTR OutGrid, long OutFmt);
	LPDISPATCH NewGrid();
	long GetPageUnits();
	void SetPageUnits(long nNewValue);
	BOOL GetBackupFiles();
	void SetBackupFiles(BOOL bNewValue);
	long GetShowToolbars();
	void SetShowToolbars(long nNewValue);
	BOOL GetScreenUpdating();
	void SetScreenUpdating(BOOL bNewValue);
	void SetWindowState(long nNewValue);
	long GetWindowState();
	BOOL GridFilter(LPCTSTR InGrid, long Filter, long EdgeOp, long BlankOp, long NumPasses, double EdgeFill, double BlankFill, long NumRow, long NumCol, const VARIANT& Param1, const VARIANT& Param2, const VARIANT& UserFilter, LPCTSTR OutGrid, 
		long OutFmt);
	// method 'GridMosaic' not emitted because of invalid return type or parameter type
	BOOL CrossValidate(LPCTSTR DataFile, long xCol, long yCol, long zCol, const VARIANT& ExclusionFilter, const VARIANT& DupMethod, const VARIANT& xDupTol, const VARIANT& yDupTol, const VARIANT& NumCols, const VARIANT& NumRows, 
		const VARIANT& xMin, const VARIANT& xMax, const VARIANT& yMin, const VARIANT& yMax, const VARIANT& Algorithm, const VARIANT& ShowReport, const VARIANT& SearchEnable, const VARIANT& SearchNumSectors, const VARIANT& SearchRad1, 
		const VARIANT& SearchRad2, const VARIANT& SearchAngle, const VARIANT& SearchMinData, const VARIANT& SearchDataPerSect, const VARIANT& SearchMaxEmpty, const VARIANT& FaultFileName, const VARIANT& BreakFileName, 
		const VARIANT& AnisotropyRatio, const VARIANT& AnisotropyAngle, const VARIANT& IDPower, const VARIANT& IDSmoothing, const VARIANT& KrigType, const VARIANT& KrigDriftType, const VARIANT& KrigVariogram, const VARIANT& MCMaxResidual, 
		const VARIANT& MCMaxIterations, const VARIANT& MCInternalTension, const VARIANT& MCBoundaryTension, const VARIANT& MCRelaxationFactor, const VARIANT& ShepSmoothFactor, const VARIANT& ShepQuadraticNeighbors, 
		const VARIANT& ShepWeightingNeighbors, const VARIANT& ShepRange1, const VARIANT& ShepRange2, const VARIANT& RegrMaxXOrder, const VARIANT& RegrMaxYOrder, const VARIANT& RegrMaxTotalOrder, const VARIANT& RBBasisType, 
		const VARIANT& RBRSquared, const VARIANT& SearchMaxData, const VARIANT& LocalPolyOrder, const VARIANT& LocalPolyPower, const VARIANT& NumRandomPoints, const VARIANT& xMinValidate, const VARIANT& xMaxValidate, const VARIANT& yMinValidate, 
		const VARIANT& yMaxValidate, const VARIANT& zMinValidate, const VARIANT& zMaxValidate, const VARIANT& xTolValidate, const VARIANT& yTolValidate, const VARIANT& ResultsFile, VARIANT* pResults);
};
/////////////////////////////////////////////////////////////////////////////
// IDocuments wrapper class

class IDocuments : public COleDispatchDriver
{
public:
	IDocuments() {}		// Calls COleDispatchDriver default constructor
	IDocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IDocuments(const IDocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add(long DocType);
	LPDISPATCH Open(LPCTSTR FileName, LPCTSTR Options);
	BOOL SaveAll(BOOL Prompt);
	BOOL CloseAll(long SaveChanges);
};
/////////////////////////////////////////////////////////////////////////////
// IWindows wrapper class

class IWindows : public COleDispatchDriver
{
public:
	IWindows() {}		// Calls COleDispatchDriver default constructor
	IWindows(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWindows(const IWindows& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	void Arrange(long ArrangeType);
};
/////////////////////////////////////////////////////////////////////////////
// IVarioComponent wrapper class

class IVarioComponent : public COleDispatchDriver
{
public:
	IVarioComponent() {}		// Calls COleDispatchDriver default constructor
	IVarioComponent(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVarioComponent(const IVarioComponent& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	double GetParam1();
	double GetParam2();
	double GetPower();
	double GetAnisotropyRatio();
	double GetAnisotropyAngle();
	void Set(long VarioType, double Param1, double Param2, double Power, double AnisotropyRatio, double AnisotropyAngle);
	double GetLowerFitLimit(long Param);
	double GetUpperFitLimit(long Param);
	void SetFitLimits(long Param, double LowerLimit, double UpperLimit);
};
/////////////////////////////////////////////////////////////////////////////
// IWksDocument wrapper class

class IWksDocument : public COleDispatchDriver
{
public:
	IWksDocument() {}		// Calls COleDispatchDriver default constructor
	IWksDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksDocument(const IWksDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetFullName();
	CString GetPath();
	BOOL GetSaved();
	long GetType();
	LPDISPATCH GetWindows();
	long GetIndex();
	void Activate();
	BOOL Save();
	BOOL SaveAs(LPCTSTR FileName, LPCTSTR Options, long FileFormat);
	BOOL Close(long SaveChanges, LPCTSTR FileName);
	LPDISPATCH NewWindow();
	LPDISPATCH GetUsedRange();
	double GetDefaultColumnWidth();
	void SetDefaultColumnWidth(double newValue);
	double GetDefaultRowHeight();
	void SetDefaultRowHeight(double newValue);
	LPDISPATCH GetDefaultFormat();
	LPDISPATCH GetPageSetup();
	void PrintOut(long FromPage, long ToPage, long Copies, BOOL Collate, LPCTSTR Selection, LPCTSTR PrinterName, LPCTSTR PrintToFileName);
	BOOL Merge(LPCTSTR FileName, long Row, const VARIANT& Col, LPCTSTR Options, long FileFormat);
	BOOL Transform(long FirstRow, long LastRow, LPCTSTR Equation);
	LPDISPATCH Cells(const VARIANT& Row, const VARIANT& Col, const VARIANT& LastRow, const VARIANT& LastCol);
	LPDISPATCH Range(const VARIANT& Row, const VARIANT& Col, const VARIANT& LastRow, const VARIANT& LastCol);
	LPDISPATCH Rows(const VARIANT& Row1, const VARIANT& Row2);
	LPDISPATCH Columns(const VARIANT& Col1, const VARIANT& Col2);
};
/////////////////////////////////////////////////////////////////////////////
// IDocument wrapper class

class IDocument : public COleDispatchDriver
{
public:
	IDocument() {}		// Calls COleDispatchDriver default constructor
	IDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IDocument(const IDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetFullName();
	CString GetPath();
	BOOL GetSaved();
	long GetType();
	LPDISPATCH GetWindows();
	long GetIndex();
	void Activate();
	BOOL Save();
	BOOL SaveAs(LPCTSTR FileName, LPCTSTR Options, long FileFormat);
	BOOL Close(long SaveChanges, LPCTSTR FileName);
	LPDISPATCH NewWindow();
};
/////////////////////////////////////////////////////////////////////////////
// IGrid wrapper class

class IGrid : public COleDispatchDriver
{
public:
	IGrid() {}		// Calls COleDispatchDriver default constructor
	IGrid(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IGrid(const IGrid& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetNumRows();
	long GetNumCols();
	double GetXMin();
	void SetXMin(double newValue);
	double GetXMax();
	void SetXMax(double newValue);
	double GetYMin();
	void SetYMin(double newValue);
	double GetYMax();
	void SetYMax(double newValue);
	double GetZMin();
	void SetZMin(double newValue);
	double GetZMax();
	void SetZMax(double newValue);
	double GetXSize();
	double GetYSize();
	CString GetFileName();
	double GetBlankValue();
	void SetBlankValue(double newValue);
	double GetNode(long Row, long Col);
	void SetNode(long Row, long Col, double Value);
	void BlankNode(long Row, long Col);
	BOOL IsBlanked(long Row, long Col);
	double Interpolate(double X, double Y);
	void LoadFile(LPCTSTR FileName, BOOL HeaderOnly);
	void SaveFile(LPCTSTR FileName, long Format);
	void UpdateZLimits();
	void Allocate(long NumRows, long NumCols);
};
/////////////////////////////////////////////////////////////////////////////
// IPlotDocument wrapper class

class IPlotDocument : public COleDispatchDriver
{
public:
	IPlotDocument() {}		// Calls COleDispatchDriver default constructor
	IPlotDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPlotDocument(const IPlotDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	CString GetFullName();
	CString GetPath();
	BOOL GetSaved();
	long GetType();
	LPDISPATCH GetWindows();
	long GetIndex();
	void Activate();
	BOOL Save();
	BOOL SaveAs(LPCTSTR FileName, LPCTSTR Options, long FileFormat);
	BOOL Close(long SaveChanges, LPCTSTR FileName);
	LPDISPATCH NewWindow();
	LPDISPATCH GetShapes();
	LPDISPATCH GetSelection();
	LPDISPATCH GetPageSetup();
	BOOL GetShowObjectManager();
	void SetShowObjectManager(BOOL bNewValue);
	LPDISPATCH Import(LPCTSTR FileName, LPCTSTR Options);
	BOOL Export(LPCTSTR FileName, BOOL SelectionOnly, LPCTSTR Options);
	BOOL PrintOut(const VARIANT& Method, const VARIANT& SelectionOnly, const VARIANT& NumCopies, const VARIANT& Collate, const VARIANT& xOverlap, const VARIANT& yOverlap, const VARIANT& Scale);
	LPDISPATCH GetDefaultLine();
	LPDISPATCH GetDefaultFill();
	LPDISPATCH GetDefaultFont();
	LPDISPATCH GetDefaultSymbol();
};
/////////////////////////////////////////////////////////////////////////////
// IShapes wrapper class

class IShapes : public COleDispatchDriver
{
public:
	IShapes() {}		// Calls COleDispatchDriver default constructor
	IShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShapes(const IShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH AddRectangle(double Left, double Top, double Right, double Bottom, double xRadius, double yRadius);
	LPDISPATCH AddEllipse(double Left, double Top, double Right, double Bottom);
	LPDISPATCH AddSymbol(double X, double Y);
	LPDISPATCH AddText(double X, double Y, LPCTSTR Text);
	LPDISPATCH AddLine(double xBeg, double yBeg, double xEnd, double yEnd);
	// method 'AddPolyLine' not emitted because of invalid return type or parameter type
	// method 'AddPolygon' not emitted because of invalid return type or parameter type
	// method 'AddComplexPolygon' not emitted because of invalid return type or parameter type
	LPDISPATCH AddBaseMap(LPCTSTR ImportFileName, LPCTSTR ImportOptions);
	LPDISPATCH AddContourMap(LPCTSTR GridFileName);
	LPDISPATCH AddPostMap(LPCTSTR DataFileName, long xCol, long yCol, long LabCol, long SymCol, long AngleCol);
	LPDISPATCH AddClassedPostMap(LPCTSTR DataFileName, long xCol, long yCol, long zCol, long LabCol);
	LPDISPATCH AddImageMap(LPCTSTR GridFileName);
	LPDISPATCH AddReliefMap(LPCTSTR GridFileName);
	LPDISPATCH AddVectorMap(LPCTSTR GridFileName1, LPCTSTR GridFileName2, long CoordSys, long AngleSys, long AngleUnits);
	LPDISPATCH AddWireframe(LPCTSTR GridFileName);
	LPDISPATCH AddVariogram(LPCTSTR DataFileName, long xCol, long yCol, long zCol, LPCTSTR ExclusionFilter, long DupMethod, double xDupTol, double yDupTol, long NumAngularDivisions, long NumRadialDivisions, long DetrendMethod, BOOL ShowReport, 
		const VARIANT& MaxLagDistance);
	void SelectAll();
	void BlockSelect(double Left, double Top, double Right, double Bottom);
	void InvertSelection();
	LPDISPATCH Paste(long Format);
	LPDISPATCH AddSurface(LPCTSTR GridFileName);
};
/////////////////////////////////////////////////////////////////////////////
// IRectangle wrapper class

class IRectangle : public COleDispatchDriver
{
public:
	IRectangle() {}		// Calls COleDispatchDriver default constructor
	IRectangle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IRectangle(const IRectangle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetLine();
	LPDISPATCH GetFill();
	double GetXRadius();
	void SetXRadius(double newValue);
	double GetYRadius();
	void SetYRadius(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IShape wrapper class

class IShape : public COleDispatchDriver
{
public:
	IShape() {}		// Calls COleDispatchDriver default constructor
	IShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IShape(const IShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
};
/////////////////////////////////////////////////////////////////////////////
// ILineFormat wrapper class

class ILineFormat : public COleDispatchDriver
{
public:
	ILineFormat() {}		// Calls COleDispatchDriver default constructor
	ILineFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ILineFormat(const ILineFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetForeColor();
	void SetForeColor(long nNewValue);
	CString GetStyle();
	void SetStyle(LPCTSTR lpszNewValue);
	double GetWidth();
	void SetWidth(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IFillFormat wrapper class

class IFillFormat : public COleDispatchDriver
{
public:
	IFillFormat() {}		// Calls COleDispatchDriver default constructor
	IFillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IFillFormat(const IFillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetForeColor();
	void SetForeColor(long nNewValue);
	long GetBackColor();
	void SetBackColor(long nNewValue);
	CString GetPattern();
	void SetPattern(LPCTSTR lpszNewValue);
	BOOL GetTransparent();
	void SetTransparent(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IEllipse wrapper class

class IEllipse : public COleDispatchDriver
{
public:
	IEllipse() {}		// Calls COleDispatchDriver default constructor
	IEllipse(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IEllipse(const IEllipse& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetLine();
	LPDISPATCH GetFill();
};
/////////////////////////////////////////////////////////////////////////////
// ISymbol wrapper class

class ISymbol : public COleDispatchDriver
{
public:
	ISymbol() {}		// Calls COleDispatchDriver default constructor
	ISymbol(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISymbol(const ISymbol& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetMarker();
};
/////////////////////////////////////////////////////////////////////////////
// IMarkerFormat wrapper class

class IMarkerFormat : public COleDispatchDriver
{
public:
	IMarkerFormat() {}		// Calls COleDispatchDriver default constructor
	IMarkerFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMarkerFormat(const IMarkerFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetSet();
	void SetSet(LPCTSTR lpszNewValue);
	long GetIndex();
	void SetIndex(long nNewValue);
	double GetSize();
	void SetSize(double newValue);
	long GetColor();
	void SetColor(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IText wrapper class

class IText : public COleDispatchDriver
{
public:
	IText() {}		// Calls COleDispatchDriver default constructor
	IText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IText(const IText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	LPDISPATCH GetFont();
};
/////////////////////////////////////////////////////////////////////////////
// IFontFormat wrapper class

class IFontFormat : public COleDispatchDriver
{
public:
	IFontFormat() {}		// Calls COleDispatchDriver default constructor
	IFontFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IFontFormat(const IFontFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetFace();
	void SetFace(LPCTSTR lpszNewValue);
	double GetSize();
	void SetSize(double newValue);
	BOOL GetBold();
	void SetBold(BOOL bNewValue);
	BOOL GetItalic();
	void SetItalic(BOOL bNewValue);
	BOOL GetStrikeThrough();
	void SetStrikeThrough(BOOL bNewValue);
	BOOL GetUnderline();
	void SetUnderline(BOOL bNewValue);
	long GetHAlign();
	void SetHAlign(long nNewValue);
	long GetVAlign();
	void SetVAlign(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IPolyline wrapper class

class IPolyline : public COleDispatchDriver
{
public:
	IPolyline() {}		// Calls COleDispatchDriver default constructor
	IPolyline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPolyline(const IPolyline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetLine();
	long GetStartArrow();
	void SetStartArrow(long nNewValue);
	long GetEndArrow();
	void SetEndArrow(long nNewValue);
	double GetArrowScale();
	void SetArrowScale(double newValue);
	// method 'GetVertices' not emitted because of invalid return type or parameter type
	// method 'SetVertices' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IPolygon wrapper class

class IPolygon : public COleDispatchDriver
{
public:
	IPolygon() {}		// Calls COleDispatchDriver default constructor
	IPolygon(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPolygon(const IPolygon& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetLine();
	LPDISPATCH GetFill();
	// method 'GetVertices' not emitted because of invalid return type or parameter type
	// method 'GetPolyCounts' not emitted because of invalid return type or parameter type
	// method 'SetVertices' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IMapFrame wrapper class

class IMapFrame : public COleDispatchDriver
{
public:
	IMapFrame() {}		// Calls COleDispatchDriver default constructor
	IMapFrame(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IMapFrame(const IMapFrame& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetAxes();
	LPDISPATCH GetOverlays();
	LPDISPATCH GetScaleBars();
	double GetXMin();
	double GetXMax();
	double GetYMin();
	double GetYMax();
	LPDISPATCH GetBackgroundLine();
	LPDISPATCH GetBackgroundFill();
	double GetViewRotation();
	void SetViewRotation(double newValue);
	double GetViewTilt();
	void SetViewTilt(double newValue);
	double GetViewDistance();
	void SetViewDistance(double newValue);
	long GetViewProjection();
	void SetViewProjection(long nNewValue);
	double GetXLength();
	void SetXLength(double newValue);
	double GetYLength();
	void SetYLength(double newValue);
	double GetZLength();
	void SetZLength(double newValue);
	double GetXMapPerPU();
	void SetXMapPerPU(double newValue);
	double GetYMapPerPU();
	void SetYMapPerPU(double newValue);
	double GetZMapPerPU();
	void SetZMapPerPU(double newValue);
	double GetViewFOV();
	void SetViewFOV(double newValue);
	void SetLimits(double xMin, double xMax, double yMin, double yMax);
	long GetLightModel();
	void SetLightModel(long nNewValue);
	double GetLightAzimuth();
	void SetLightAzimuth(double newValue);
	double GetLightZenith();
	void SetLightZenith(double newValue);
	long GetAmbientLightColor();
	void SetAmbientLightColor(long nNewValue);
	long GetDiffuseLightColor();
	void SetDiffuseLightColor(long nNewValue);
	long GetSpecularLightColor();
	void SetSpecularLightColor(long nNewValue);
	long GetResampleMethod();
	void SetResampleMethod(long nNewValue);
	long GetOverlayResolution();
	void SetOverlayResolution(long nNewValue);
	long GetColorModulation();
	void SetColorModulation(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAxes wrapper class

class IAxes : public COleDispatchDriver
{
public:
	IAxes() {}		// Calls COleDispatchDriver default constructor
	IAxes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAxes(const IAxes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// IAxis wrapper class

class IAxis : public COleDispatchDriver
{
public:
	IAxis() {}		// Calls COleDispatchDriver default constructor
	IAxis(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAxis(const IAxis& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	long GetAxisType();
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	double GetTitleOffset1();
	void SetTitleOffset1(double newValue);
	double GetTitleOffset2();
	void SetTitleOffset2(double newValue);
	double GetTitleAngle();
	void SetTitleAngle(double newValue);
	LPDISPATCH GetTitleFont();
	long GetAxisPlane();
	void SetAxisPlane(long nNewValue);
	LPDISPATCH GetAxisLine();
	BOOL GetShowLabels();
	void SetShowLabels(BOOL bNewValue);
	double GetLabelAngle();
	void SetLabelAngle(double newValue);
	double GetLabelOffset();
	void SetLabelOffset(double newValue);
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	long GetMinorTickType();
	void SetMinorTickType(long nNewValue);
	double GetMinorTickLength();
	void SetMinorTickLength(double newValue);
	long GetMajorTickType();
	void SetMajorTickType(long nNewValue);
	double GetMajorTickLength();
	void SetMajorTickLength(double newValue);
	long GetMinorTicksPerMajor();
	void SetMinorTicksPerMajor(long nNewValue);
	BOOL GetAutoScale();
	void SetAutoScale(BOOL bNewValue);
	double GetMinimum();
	double GetMaximum();
	double GetMajorInterval();
	double GetFirstMajorTick();
	double GetLastMajorTick();
	double GetCross1();
	double GetCross2();
	BOOL GetShowMajorGridLines();
	void SetShowMajorGridLines(BOOL bNewValue);
	LPDISPATCH GetMajorGridLine();
	BOOL GetShowMinorGridLines();
	void SetShowMinorGridLines(BOOL bNewValue);
	LPDISPATCH GetMinorGridLine();
	void SetScale(const VARIANT& Minimum, const VARIANT& Maximum, const VARIANT& MajorInterval, const VARIANT& FirstMajorTick, const VARIANT& LastMajorTick, const VARIANT& Cross1, const VARIANT& Cross2);
};
/////////////////////////////////////////////////////////////////////////////
// ILabelFormat wrapper class

class ILabelFormat : public COleDispatchDriver
{
public:
	ILabelFormat() {}		// Calls COleDispatchDriver default constructor
	ILabelFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ILabelFormat(const ILabelFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	void SetType(long nNewValue);
	long GetNumDigits();
	void SetNumDigits(long nNewValue);
	BOOL GetThousands();
	void SetThousands(BOOL bNewValue);
	BOOL GetAbsoluteValue();
	void SetAbsoluteValue(BOOL bNewValue);
	CString GetPrefix();
	void SetPrefix(LPCTSTR lpszNewValue);
	CString GetPostfix();
	void SetPostfix(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IOverlays wrapper class

class IOverlays : public COleDispatchDriver
{
public:
	IOverlays() {}		// Calls COleDispatchDriver default constructor
	IOverlays(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IOverlays(const IOverlays& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH BreakApart(LPDISPATCH pOverlay);
};
/////////////////////////////////////////////////////////////////////////////
// IScaleBars wrapper class

class IScaleBars : public COleDispatchDriver
{
public:
	IScaleBars() {}		// Calls COleDispatchDriver default constructor
	IScaleBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IScaleBars(const IScaleBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH Add();
};
/////////////////////////////////////////////////////////////////////////////
// IScaleBar wrapper class

class IScaleBar : public COleDispatchDriver
{
public:
	IScaleBar() {}		// Calls COleDispatchDriver default constructor
	IScaleBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IScaleBar(const IScaleBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	long GetNumCycles();
	void SetNumCycles(long nNewValue);
	double GetCycleSpacing();
	void SetCycleSpacing(double newValue);
	double GetLabelIncrement();
	void SetLabelIncrement(double newValue);
	long GetAxis();
	void SetAxis(long nNewValue);
	LPDISPATCH GetLine();
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	double GetLabelRotation();
	void SetLabelRotation(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IVariogram wrapper class

class IVariogram : public COleDispatchDriver
{
public:
	IVariogram() {}		// Calls COleDispatchDriver default constructor
	IVariogram(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVariogram(const IVariogram& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	double GetLagDirection();
	void SetLagDirection(double newValue);
	double GetLagTolerance();
	void SetLagTolerance(double newValue);
	double GetMaxLagDistance();
	void SetMaxLagDistance(double newValue);
	long GetNumLags();
	void SetNumLags(long nNewValue);
	double GetLagWidth();
	void SetLagWidth(double newValue);
	long GetEstimatorType();
	void SetEstimatorType(long nNewValue);
	double GetVerticalScale();
	void SetVerticalScale(double newValue);
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	LPDISPATCH GetTitleFont();
	BOOL GetShowSymbols();
	void SetShowSymbols(BOOL bNewValue);
	BOOL GetShowExperimental();
	void SetShowExperimental(BOOL bNewValue);
	BOOL GetShowModel();
	void SetShowModel(BOOL bNewValue);
	BOOL GetShowVariance();
	void SetShowVariance(BOOL bNewValue);
	BOOL GetShowSubTitle();
	void SetShowSubTitle(BOOL bNewValue);
	LPDISPATCH GetSubTitleFont();
	BOOL GetShowPairs();
	void SetShowPairs(BOOL bNewValue);
	LPDISPATCH GetPairsFont();
	LPDISPATCH GetSymbol();
	LPDISPATCH GetModelLine();
	LPDISPATCH GetExperimentalLine();
	LPDISPATCH GetVarianceLine();
	VARIANT GetModel();
	void SetModel(const VARIANT& newValue);
	LPDISPATCH GetAxes();
	double Statistics(long Statistic);
	void AutoFit(long FitMethod, double Precision, double MaxDistance, long Iterations);
	BOOL Export(LPCTSTR FileName);
};
/////////////////////////////////////////////////////////////////////////////
// ISelection wrapper class

class ISelection : public COleDispatchDriver
{
public:
	ISelection() {}		// Calls COleDispatchDriver default constructor
	ISelection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISelection(const ISelection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	void SetZOrder(long ZOrder);
	void Rotate(double Angle);
	void DeselectAll();
	LPDISPATCH OverlayMaps();
	BOOL StackMaps();
	void Align(long HorzAlign, long VertAlign);
	LPDISPATCH Combine();
	void Cut();
	void Copy();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// IComposite wrapper class

class IComposite : public COleDispatchDriver
{
public:
	IComposite() {}		// Calls COleDispatchDriver default constructor
	IComposite(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IComposite(const IComposite& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	void BreakApart();
};
/////////////////////////////////////////////////////////////////////////////
// IPageSetup wrapper class

class IPageSetup : public COleDispatchDriver
{
public:
	IPageSetup() {}		// Calls COleDispatchDriver default constructor
	IPageSetup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPageSetup(const IPageSetup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetOrientation();
	void SetOrientation(long nNewValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetLeftMargin();
	void SetLeftMargin(double newValue);
	double GetTopMargin();
	void SetTopMargin(double newValue);
	double GetRightMargin();
	void SetRightMargin(double newValue);
	double GetBottomMargin();
	void SetBottomMargin(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IWindow wrapper class

class IWindow : public COleDispatchDriver
{
public:
	IWindow() {}		// Calls COleDispatchDriver default constructor
	IWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWindow(const IWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetCaption();
	long GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetActive();
	void SetWindowState(long nNewValue);
	long GetWindowState();
	LPDISPATCH GetDocument();
	long GetIndex();
	void Activate();
	BOOL Close(long SaveChanges, LPCTSTR FileName);
};
/////////////////////////////////////////////////////////////////////////////
// IPlotWindow wrapper class

class IPlotWindow : public COleDispatchDriver
{
public:
	IPlotWindow() {}		// Calls COleDispatchDriver default constructor
	IPlotWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPlotWindow(const IPlotWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetCaption();
	long GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetActive();
	void SetWindowState(long nNewValue);
	long GetWindowState();
	LPDISPATCH GetDocument();
	long GetIndex();
	void Activate();
	BOOL Close(long SaveChanges, LPCTSTR FileName);
	BOOL GetAutoRedraw();
	void SetAutoRedraw(BOOL bNewValue);
	BOOL GetShowRulers();
	void SetShowRulers(BOOL bNewValue);
	BOOL GetShowGrid();
	void SetShowGrid(BOOL bNewValue);
	void Redraw();
	void Zoom(long Type);
	void ZoomPoint(double X, double Y, double Scale);
	void ZoomRectangle(double Left, double Top, double Right, double Bottom);
	LPDISPATCH GetHorizontalRuler();
	LPDISPATCH GetVerticalRuler();
	BOOL GetShowPage();
	void SetShowPage(BOOL bNewValue);
	BOOL GetShowMargins();
	void SetShowMargins(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IRuler wrapper class

class IRuler : public COleDispatchDriver
{
public:
	IRuler() {}		// Calls COleDispatchDriver default constructor
	IRuler(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IRuler(const IRuler& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetRulerDivisions();
	void SetRulerDivisions(long nNewValue);
	long GetGridDivisions();
	void SetGridDivisions(long nNewValue);
	BOOL GetSnapToRuler();
	void SetSnapToRuler(BOOL bNewValue);
	BOOL GetShowPosition();
	void SetShowPosition(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IWksWindow wrapper class

class IWksWindow : public COleDispatchDriver
{
public:
	IWksWindow() {}		// Calls COleDispatchDriver default constructor
	IWksWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWksWindow(const IWksWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetCaption();
	long GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetActive();
	void SetWindowState(long nNewValue);
	long GetWindowState();
	LPDISPATCH GetDocument();
	long GetIndex();
	void Activate();
	BOOL Close(long SaveChanges, LPCTSTR FileName);
	VARIANT GetSelection();
	void SetSelection(const VARIANT& newValue);
	LPDISPATCH GetActiveCell();
	void SetActiveCell(const VARIANT& newValue);
	long GetLeftColumn();
	void SetLeftColumn(const VARIANT& newValue);
	long GetTopRow();
	void SetTopRow(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IGridWindow wrapper class

class IGridWindow : public COleDispatchDriver
{
public:
	IGridWindow() {}		// Calls COleDispatchDriver default constructor
	IGridWindow(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IGridWindow(const IGridWindow& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetCaption();
	long GetType();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	BOOL GetActive();
	void SetWindowState(long nNewValue);
	long GetWindowState();
	LPDISPATCH GetDocument();
	long GetIndex();
	void Activate();
	BOOL Close(long SaveChanges, LPCTSTR FileName);
	BOOL GetShowContours();
	void SetShowContours(BOOL bNewValue);
	BOOL GetShowNodes();
	void SetShowNodes(BOOL bNewValue);
	void Redraw();
	void Zoom(long Type);
};
/////////////////////////////////////////////////////////////////////////////
// IColorMap wrapper class

class IColorMap : public COleDispatchDriver
{
public:
	IColorMap() {}		// Calls COleDispatchDriver default constructor
	IColorMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IColorMap(const IColorMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	// method 'GetNodePositions' not emitted because of invalid return type or parameter type
	// method 'GetNodeColors' not emitted because of invalid return type or parameter type
	// method 'SetNodes' not emitted because of invalid return type or parameter type
	void LoadFile(LPCTSTR FileName);
	void SaveFile(LPCTSTR FileName);
	double PosToDat(double Pos);
	double DatToPos(double Dat);
	void SetDataLimits(double DataMin, double DataMax);
	double GetDataMin();
	double GetDataMax();
};
/////////////////////////////////////////////////////////////////////////////
// IBaseMap wrapper class

class IBaseMap : public COleDispatchDriver
{
public:
	IBaseMap() {}		// Calls COleDispatchDriver default constructor
	IBaseMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IBaseMap(const IBaseMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetLine();
	LPDISPATCH GetFill();
	LPDISPATCH GetFont();
	LPDISPATCH GetSymbol();
	double GetXMin();
	double GetXMax();
	double GetYMin();
	double GetYMax();
	CString GetFileName();
	void SetImageLimits(double xMin, double xMax, double yMin, double yMax);
};
/////////////////////////////////////////////////////////////////////////////
// IImageMap wrapper class

class IImageMap : public COleDispatchDriver
{
public:
	IImageMap() {}		// Calls COleDispatchDriver default constructor
	IImageMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IImageMap(const IImageMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetGridFile();
	void SetGridFile(LPCTSTR lpszNewValue);
	BOOL GetInterpolatePixels();
	void SetInterpolatePixels(BOOL bNewValue);
	BOOL GetDitherBitmap();
	void SetDitherBitmap(BOOL bNewValue);
	long GetMissingDataColor();
	void SetMissingDataColor(long nNewValue);
	BOOL GetShowColorScale();
	void SetShowColorScale(BOOL bNewValue);
	LPDISPATCH GetColorScale();
	LPDISPATCH GetColorMap();
	LPDISPATCH GetGrid();
};
/////////////////////////////////////////////////////////////////////////////
// IContinuousColorScale wrapper class

class IContinuousColorScale : public COleDispatchDriver
{
public:
	IContinuousColorScale() {}		// Calls COleDispatchDriver default constructor
	IContinuousColorScale(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IContinuousColorScale(const IContinuousColorScale& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetFrameLine();
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	double GetLabelAngle();
	void SetLabelAngle(double newValue);
	double GetLabelMinimum();
	void SetLabelMinimum(double newValue);
	double GetLabelMaximum();
	void SetLabelMaximum(double newValue);
	double GetLabelInterval();
	void SetLabelInterval(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IReliefMap wrapper class

class IReliefMap : public COleDispatchDriver
{
public:
	IReliefMap() {}		// Calls COleDispatchDriver default constructor
	IReliefMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IReliefMap(const IReliefMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetGridFile();
	void SetGridFile(LPCTSTR lpszNewValue);
	double GetHLightAngle();
	void SetHLightAngle(double newValue);
	double GetVLightAngle();
	void SetVLightAngle(double newValue);
	long GetGradientMethod();
	void SetGradientMethod(long nNewValue);
	long GetShadingMethod();
	void SetShadingMethod(long nNewValue);
	BOOL GetDitherBitmap();
	void SetDitherBitmap(BOOL bNewValue);
	long GetMissingDataColor();
	void SetMissingDataColor(long nNewValue);
	LPDISPATCH GetColorMap();
	double GetZScale();
	void SetZScale(double newValue);
	LPDISPATCH GetGrid();
};
/////////////////////////////////////////////////////////////////////////////
// IContourMap wrapper class

class IContourMap : public COleDispatchDriver
{
public:
	IContourMap() {}		// Calls COleDispatchDriver default constructor
	IContourMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IContourMap(const IContourMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetGridFile();
	void SetGridFile(LPCTSTR lpszNewValue);
	BOOL GetFillContours();
	void SetFillContours(BOOL bNewValue);
	BOOL GetShowColorScale();
	void SetShowColorScale(BOOL bNewValue);
	LPDISPATCH GetColorScale();
	long GetSmoothContours();
	void SetSmoothContours(long nNewValue);
	LPDISPATCH GetBlankLine();
	LPDISPATCH GetBlankFill();
	LPDISPATCH GetLevels();
	double GetLabelTolerance();
	void SetLabelTolerance(double newValue);
	double GetLabelLabelDist();
	void SetLabelLabelDist(double newValue);
	double GetLabelEdgeDist();
	void SetLabelEdgeDist(double newValue);
	BOOL GetOrientLabelsUphill();
	void SetOrientLabelsUphill(BOOL bNewValue);
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	double GetHachLength();
	void SetHachLength(double newValue);
	long GetHachDirection();
	void SetHachDirection(long nNewValue);
	BOOL GetHachClosedOnly();
	void SetHachClosedOnly(BOOL bNewValue);
	LPDISPATCH GetFaultLine();
	LPDISPATCH GetGrid();
	void ExportContours(LPCTSTR FileName, long Format);
};
/////////////////////////////////////////////////////////////////////////////
// IDiscreteColorScale wrapper class

class IDiscreteColorScale : public COleDispatchDriver
{
public:
	IDiscreteColorScale() {}		// Calls COleDispatchDriver default constructor
	IDiscreteColorScale(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IDiscreteColorScale(const IDiscreteColorScale& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetFrameLine();
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	long GetFirstLabel();
	void SetFirstLabel(long nNewValue);
	double GetLabelAngle();
	void SetLabelAngle(double newValue);
	long GetLabelFrequency();
	void SetLabelFrequency(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ILevels wrapper class

class ILevels : public COleDispatchDriver
{
public:
	ILevels() {}		// Calls COleDispatchDriver default constructor
	ILevels(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ILevels(const ILevels& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(long Index);
	// method 'Set' not emitted because of invalid return type or parameter type
	void AutoGenerate(double MinLevel, double MaxLevel, double Interval);
	void LoadFile(LPCTSTR FileName);
	void SaveFile(LPCTSTR FileName);
	void SetLabelFrequency(long FirstIndex, long NumberToSet, long NumberToSkip);
	void SetHachFrequency(long FirstIndex, long NumberToSet, long NumberToSkip);
};
/////////////////////////////////////////////////////////////////////////////
// ILevel wrapper class

class ILevel : public COleDispatchDriver
{
public:
	ILevel() {}		// Calls COleDispatchDriver default constructor
	ILevel(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ILevel(const ILevel& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	double GetValue();
	LPDISPATCH GetLine();
	LPDISPATCH GetFill();
	BOOL GetShowLabel();
	void SetShowLabel(BOOL bNewValue);
	BOOL GetShowHach();
	void SetShowHach(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IPostMap wrapper class

class IPostMap : public COleDispatchDriver
{
public:
	IPostMap() {}		// Calls COleDispatchDriver default constructor
	IPostMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPostMap(const IPostMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetDataFile();
	void SetDataFile(LPCTSTR lpszNewValue);
	long GetXCol();
	void SetXCol(long nNewValue);
	long GetYCol();
	void SetYCol(long nNewValue);
	long GetLabCol();
	void SetLabCol(long nNewValue);
	long GetSymCol();
	void SetSymCol(long nNewValue);
	long GetAngleCol();
	void SetAngleCol(long nNewValue);
	LPDISPATCH GetSymbol();
	double GetSymAngle();
	void SetSymAngle(double newValue);
	long GetSymFrequency();
	void SetSymFrequency(long nNewValue);
	long GetSymSizeMethod();
	double GetLabelLineLength();
	void SetLabelLineLength(double newValue);
	LPDISPATCH GetLabelLine();
	long GetLabelPos();
	void SetLabelPos(long nNewValue);
	double GetLabelXOffset();
	void SetLabelXOffset(double newValue);
	double GetLabelYOffset();
	void SetLabelYOffset(double newValue);
	double GetLabelAngle();
	void SetLabelAngle(double newValue);
	long GetLabelPlane();
	void SetLabelPlane(long nNewValue);
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	long GetHeightCol();
	double GetScaleValue1();
	double GetScaleValue2();
	double GetSymbolHeight1();
	double GetSymbolHeight2();
	void SetInputData(LPCTSTR DataFileName, long xCol, long yCol, long LabCol, long SymCol, long AngleCol);
	void SetSymbolScaling(long Method, const VARIANT& SymbolHeight1, const VARIANT& SymbolHeight2, const VARIANT& ScaleValue1, const VARIANT& ScaleValue2, long HeightCol);
};
/////////////////////////////////////////////////////////////////////////////
// IClassedPostMap wrapper class

class IClassedPostMap : public COleDispatchDriver
{
public:
	IClassedPostMap() {}		// Calls COleDispatchDriver default constructor
	IClassedPostMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IClassedPostMap(const IClassedPostMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetDataFile();
	void SetDataFile(LPCTSTR lpszNewValue);
	long GetXCol();
	void SetXCol(long nNewValue);
	long GetYCol();
	void SetYCol(long nNewValue);
	long GetZCol();
	void SetZCol(long nNewValue);
	long GetLabCol();
	void SetLabCol(long nNewValue);
	double GetSymAngle();
	void SetSymAngle(double newValue);
	long GetSymFrequency();
	void SetSymFrequency(long nNewValue);
	BOOL GetShowLegend();
	void SetShowLegend(BOOL bNewValue);
	LPDISPATCH GetLegend();
	double GetLabelLineLength();
	void SetLabelLineLength(double newValue);
	LPDISPATCH GetLabelLine();
	long GetLabelPos();
	void SetLabelPos(long nNewValue);
	double GetLabelXOffset();
	void SetLabelXOffset(double newValue);
	double GetLabelYOffset();
	void SetLabelYOffset(double newValue);
	double GetLabelAngle();
	void SetLabelAngle(double newValue);
	long GetLabelPlane();
	void SetLabelPlane(long nNewValue);
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	long GetNumClasses();
	void SetNumClasses(long nNewValue);
	long GetBinningMethod();
	void SetBinningMethod(long nNewValue);
	double GetBinLowerLimit(long Index);
	double GetBinUpperLimit(long Index);
	LPDISPATCH GetBinSymbol(long Index);
	double GetBinPercent(long Index);
	long GetBinCount(long Index);
	void SetInputData(LPCTSTR DataFileName, long xCol, long yCol, long zCol, long LabCol);
	// method 'SetBinLimits' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IPostLegend wrapper class

class IPostLegend : public COleDispatchDriver
{
public:
	IPostLegend() {}		// Calls COleDispatchDriver default constructor
	IPostLegend(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IPostLegend(const IPostLegend& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	LPDISPATCH GetTitleFont();
	long GetFrameStyle();
	void SetFrameStyle(long nNewValue);
	double GetMargins();
	void SetMargins(double newValue);
	LPDISPATCH GetFrameLine();
	LPDISPATCH GetFrameFill();
	CString GetTemplate();
	void SetTemplate(LPCTSTR lpszNewValue);
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
	BOOL GetReverseOrder();
	void SetReverseOrder(BOOL bNewValue);
	long GetSymbolSizeMethod();
	void SetSymbolSizeMethod(long nNewValue);
	double GetSymbolSize();
	void SetSymbolSize(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// ILegend wrapper class

class ILegend : public COleDispatchDriver
{
public:
	ILegend() {}		// Calls COleDispatchDriver default constructor
	ILegend(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ILegend(const ILegend& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	LPDISPATCH GetTitleFont();
	long GetFrameStyle();
	void SetFrameStyle(long nNewValue);
	double GetMargins();
	void SetMargins(double newValue);
	LPDISPATCH GetFrameLine();
	LPDISPATCH GetFrameFill();
};
/////////////////////////////////////////////////////////////////////////////
// IVectorMap wrapper class

class IVectorMap : public COleDispatchDriver
{
public:
	IVectorMap() {}		// Calls COleDispatchDriver default constructor
	IVectorMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVectorMap(const IVectorMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetGridFile();
	CString GetAspectGridFile();
	CString GetGradientGridFile();
	long GetCoordinateSystem();
	long GetAngleSystem();
	long GetAngleUnits();
	long GetSymbol();
	void SetSymbol(long nNewValue);
	BOOL GetClipSymbols();
	void SetClipSymbols(BOOL bNewValue);
	LPDISPATCH GetSymbolLine();
	LPDISPATCH GetSymbolFill();
	long GetXFrequency();
	void SetXFrequency(long nNewValue);
	long GetYFrequency();
	void SetYFrequency(long nNewValue);
	long GetColorScaleMethod();
	void SetColorScaleMethod(long nNewValue);
	BOOL GetShowColorScale();
	void SetShowColorScale(BOOL bNewValue);
	LPDISPATCH GetColorScale();
	LPDISPATCH GetColorMap();
	CString GetColorGridFile();
	void SetColorGridFile(LPCTSTR lpszNewValue);
	long GetSymbolOrigin();
	void SetSymbolOrigin(long nNewValue);
	long GetSymbolScaleMethod();
	void SetSymbolScaleMethod(long nNewValue);
	double GetMinMagnitude();
	double GetMaxMagnitude();
	double GetMinShaftLength();
	double GetMaxShaftLength();
	double GetMinHeadLength();
	double GetMaxHeadLength();
	double GetMinSymbolWidth();
	double GetMaxSymbolWidth();
	double GetMinDataMagnitude();
	double GetMaxDataMagnitude();
	BOOL GetShowLegend();
	void SetShowLegend(BOOL bNewValue);
	LPDISPATCH GetLegend();
	void SetInputGrids(LPCTSTR GridFileName1, LPCTSTR GridFileName2, long CoordSys, long AngleSys, long AngleUnits);
	void SetScaling(long Type, double Minimum, double Maximum);
	LPDISPATCH GetAspectGrid();
	LPDISPATCH GetGradientGrid();
	LPDISPATCH GetColorGrid();
	BOOL GetReverseVectors();
	void SetReverseVectors(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IVectorLegend wrapper class

class IVectorLegend : public COleDispatchDriver
{
public:
	IVectorLegend() {}		// Calls COleDispatchDriver default constructor
	IVectorLegend(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IVectorLegend(const IVectorLegend& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	LPDISPATCH GetTitleFont();
	long GetFrameStyle();
	void SetFrameStyle(long nNewValue);
	double GetMargins();
	void SetMargins(double newValue);
	LPDISPATCH GetFrameLine();
	LPDISPATCH GetFrameFill();
	CString GetMagnitudes();
	void SetMagnitudes(LPCTSTR lpszNewValue);
	long GetLayout();
	void SetLayout(long nNewValue);
	LPDISPATCH GetLabelFont();
	LPDISPATCH GetLabelFormat();
};
/////////////////////////////////////////////////////////////////////////////
// IWireframe wrapper class

class IWireframe : public COleDispatchDriver
{
public:
	IWireframe() {}		// Calls COleDispatchDriver default constructor
	IWireframe(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWireframe(const IWireframe& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	CString GetGridFile();
	long GetLineDirection();
	void SetLineDirection(long nNewValue);
	BOOL GetShowUpper();
	void SetShowUpper(BOOL bNewValue);
	BOOL GetShowLower();
	void SetShowLower(BOOL bNewValue);
	BOOL GetShowBase();
	void SetShowBase(BOOL bNewValue);
	BOOL GetShowVerticalLines();
	void SetShowVerticalLines(BOOL bNewValue);
	double GetBaseElevation();
	void SetBaseElevation(double newValue);
	BOOL GetRemoveHiddenLines();
	void SetRemoveHiddenLines(BOOL bNewValue);
	long GetBorder();
	void SetBorder(long nNewValue);
	LPDISPATCH GetXLine();
	LPDISPATCH GetYLine();
	LPDISPATCH GetZLine();
	LPDISPATCH GetBaseLine();
	LPDISPATCH GetZLevels();
	LPDISPATCH GetZoneLevels();
	long GetZoneDirection();
	void SetZoneDirection(long nNewValue);
	BOOL GetShowColorScale();
	void SetShowColorScale(BOOL bNewValue);
	LPDISPATCH GetColorScale();
	LPDISPATCH GetGrid();
};
/////////////////////////////////////////////////////////////////////////////
// ISurface wrapper class

class ISurface : public COleDispatchDriver
{
public:
	ISurface() {}		// Calls COleDispatchDriver default constructor
	ISurface(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ISurface(const ISurface& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetType();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetSelected();
	void SetSelected(BOOL bNewValue);
	double GetLeft();
	void SetLeft(double newValue);
	double GetTop();
	void SetTop(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	void Delete();
	void SetZOrder(long ZOrder);
	void Select();
	void Deselect();
	LPDISPATCH GetGrid();
	LPDISPATCH GetUpperColorMap();
	long GetLowerColor();
	void SetLowerColor(long nNewValue);
	double GetUpperShininess();
	void SetUpperShininess(double newValue);
	BOOL GetBlankMissing();
	void SetBlankMissing(BOOL bNewValue);
	double GetZMissing();
	void SetZMissing(double newValue);
	BOOL GetShowColorScale();
	void SetShowColorScale(BOOL bNewValue);
	LPDISPATCH GetColorScale();
	BOOL GetShowOverlays();
	void SetShowOverlays(BOOL bNewValue);
	BOOL GetShowBase();
	void SetShowBase(BOOL bNewValue);
	LPDISPATCH GetBaseLine();
	LPDISPATCH GetBaseFill();
	long GetXMeshFreq();
	void SetXMeshFreq(long nNewValue);
	LPDISPATCH GetXMeshLine();
	long GetYMeshFreq();
	void SetYMeshFreq(long nNewValue);
	LPDISPATCH GetYMeshLine();
	double GetMeshOffset();
	void SetMeshOffset(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IGLFillFormat wrapper class

class IGLFillFormat : public COleDispatchDriver
{
public:
	IGLFillFormat() {}		// Calls COleDispatchDriver default constructor
	IGLFillFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IGLFillFormat(const IGLFillFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	long GetColor();
	void SetColor(long nNewValue);
	long GetStyle();
	void SetStyle(long nNewValue);
};
