// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// Shapes10 wrapper class

class Shapes10 : public COleDispatchDriver
{
public:
	Shapes10() {}		// Calls COleDispatchDriver default constructor
	Shapes10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shapes10(const Shapes10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	long GetCount();
	LPDISPATCH Item(const VARIANT& Index);
	LPDISPATCH _Default(const VARIANT& Index);
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY);
	LPDISPATCH AddCurve(const VARIANT& SafeArrayOfPoints);
	LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height);
	LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY);
	LPDISPATCH AddPicture(LPCTSTR Filename, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height);
	LPDISPATCH AddPolyline(const VARIANT& SafeArrayOfPoints);
	LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height);
	LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top);
	LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height);
	LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1);
	LPDISPATCH GetRange(const VARIANT& Index);
	void SelectAll();
	LPDISPATCH AddFormControl(long Type, long Left, long Top, long Width, long Height);
	LPDISPATCH AddOLEObject(const VARIANT& ClassType, const VARIANT& Filename, const VARIANT& Link, const VARIANT& DisplayAsIcon, const VARIANT& IconFileName, const VARIANT& IconIndex, const VARIANT& IconLabel, const VARIANT& Left, 
		const VARIANT& Top, const VARIANT& Width, const VARIANT& Height);
	LPDISPATCH AddDiagram(long Type, float Left, float Top, float Width, float Height);
};
/////////////////////////////////////////////////////////////////////////////
// Diagram10 wrapper class

class Diagram10 : public COleDispatchDriver
{
public:
	Diagram10() {}		// Calls COleDispatchDriver default constructor
	Diagram10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Diagram10(const Diagram10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	LPDISPATCH GetNodes();
	long GetType();
	long GetAutoLayout();
	void SetAutoLayout(long nNewValue);
	long GetReverse();
	void SetReverse(long nNewValue);
	long GetAutoFormat();
	void SetAutoFormat(long nNewValue);
	void Convert(long Type);
};
/////////////////////////////////////////////////////////////////////////////
// Shape10 wrapper class

class Shape10 : public COleDispatchDriver
{
public:
	Shape10() {}		// Calls COleDispatchDriver default constructor
	Shape10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Shape10(const Shape10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH GetParent();
	void Apply();
	void Delete();
	LPDISPATCH Duplicate();
	void Flip(long FlipCmd);
	void IncrementLeft(float Increment);
	void IncrementRotation(float Increment);
	void IncrementTop(float Increment);
	void PickUp();
	void RerouteConnections();
	void ScaleHeight(float Factor, long RelativeToOriginalSize, const VARIANT& Scale);
	void ScaleWidth(float Factor, long RelativeToOriginalSize, const VARIANT& Scale);
	void Select(const VARIANT& Replace);
	void SetShapesDefaultProperties();
	LPDISPATCH Ungroup();
	void ZOrder(long ZOrderCmd);
	LPDISPATCH GetAdjustments();
	LPDISPATCH GetTextFrame();
	long GetAutoShapeType();
	void SetAutoShapeType(long nNewValue);
	LPDISPATCH GetCallout();
	long GetConnectionSiteCount();
	long GetConnector();
	LPDISPATCH GetConnectorFormat();
	LPDISPATCH GetFill();
	LPDISPATCH GetGroupItems();
	float GetHeight();
	void SetHeight(float newValue);
	long GetHorizontalFlip();
	float GetLeft();
	void SetLeft(float newValue);
	LPDISPATCH GetLine();
	long GetLockAspectRatio();
	void SetLockAspectRatio(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH GetNodes();
	float GetRotation();
	void SetRotation(float newValue);
	LPDISPATCH GetPictureFormat();
	LPDISPATCH GetShadow();
	LPDISPATCH GetTextEffect();
	LPDISPATCH GetThreeD();
	float GetTop();
	void SetTop(float newValue);
	long GetType();
	long GetVerticalFlip();
	VARIANT GetVertices();
	long GetVisible();
	void SetVisible(long nNewValue);
	float GetWidth();
	void SetWidth(float newValue);
	long GetZOrderPosition();
	LPDISPATCH GetHyperlink();
	long GetBlackWhiteMode();
	void SetBlackWhiteMode(long nNewValue);
	CString GetOnAction();
	void SetOnAction(LPCTSTR lpszNewValue);
	BOOL GetLocked();
	void SetLocked(BOOL bNewValue);
	LPDISPATCH GetTopLeftCell();
	LPDISPATCH GetBottomRightCell();
	long GetPlacement();
	void SetPlacement(long nNewValue);
	void Copy();
	void Cut();
	void CopyPicture(const VARIANT& Appearance, const VARIANT& Format);
	LPDISPATCH GetControlFormat();
	LPDISPATCH GetLinkFormat();
	LPDISPATCH GetOLEFormat();
	long GetFormControlType();
	CString GetAlternativeText();
	void SetAlternativeText(LPCTSTR lpszNewValue);
	LPDISPATCH GetScript();
	LPDISPATCH GetDiagramNode();
	long GetHasDiagramNode();
	LPDISPATCH GetDiagram();
	long GetHasDiagram();
	long GetChild();
	LPDISPATCH GetParentGroup();
	long GetId();
};
/////////////////////////////////////////////////////////////////////////////
// Shapes10 wrapper class


/////////////////////////////////////////////////////////////////////////////
// Shape10 wrapper class


/////////////////////////////////////////////////////////////////////////////
// Diagram10 wrapper class


/////////////////////////////////////////////////////////////////////////////
// DiagramNodes wrapper class

class DiagramNodes : public COleDispatchDriver
{
public:
	DiagramNodes() {}		// Calls COleDispatchDriver default constructor
	DiagramNodes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DiagramNodes(const DiagramNodes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(const VARIANT& Index);
	void SelectAll();
	LPDISPATCH GetParent();
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// DiagramNodes10 wrapper class

class DiagramNodes10 : public COleDispatchDriver
{
public:
	DiagramNodes10() {}		// Calls COleDispatchDriver default constructor
	DiagramNodes10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DiagramNodes10(const DiagramNodes10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPUNKNOWN Get_NewEnum();
	LPDISPATCH Item(const VARIANT& Index);
	void SelectAll();
	LPDISPATCH GetParent();
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// DiagramNode10 wrapper class

class DiagramNode10 : public COleDispatchDriver
{
public:
	DiagramNode10() {}		// Calls COleDispatchDriver default constructor
	DiagramNode10(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DiagramNode10(const DiagramNode10& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	long GetCreator();
	LPDISPATCH AddNode(long pos, long nodeType);
	void Delete();
	void MoveNode(LPDISPATCH pTargetNode, long pos);
	void ReplaceNode(LPDISPATCH pTargetNode);
	void SwapNode(LPDISPATCH pTargetNode, BOOL swapChildren);
	LPDISPATCH CloneNode(BOOL copyChildren, LPDISPATCH pTargetNode, long pos);
	void TransferChildren(LPDISPATCH pReceivingNode);
	LPDISPATCH NextNode();
	LPDISPATCH PrevNode();
	LPDISPATCH GetParent();
	LPDISPATCH GetChildren();
	LPDISPATCH GetShape();
	LPDISPATCH GetRoot();
	LPDISPATCH GetDiagram();
	long GetLayout();
	void SetLayout(long nNewValue);
	LPDISPATCH GetTextShape();
};
