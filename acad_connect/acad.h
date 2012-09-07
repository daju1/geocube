// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IAcadObject wrapper class

class IAcadObject : public COleDispatchDriver
{
public:
	IAcadObject() {}		// Calls COleDispatchDriver default constructor
	IAcadObject(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadObject(const IAcadObject& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDatabase wrapper class

class IAcadDatabase : public COleDispatchDriver
{
public:
	IAcadDatabase() {}		// Calls COleDispatchDriver default constructor
	IAcadDatabase(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDatabase(const IAcadDatabase& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetModelSpace();
	LPDISPATCH GetPaperSpace();
	LPDISPATCH GetBlocks();
	VARIANT CopyObjects(const VARIANT& Objects, const VARIANT& Owner, VARIANT* IdPairs);
	LPDISPATCH GetGroups();
	LPDISPATCH GetDimStyles();
	LPDISPATCH GetLayers();
	LPDISPATCH GetLinetypes();
	LPDISPATCH GetDictionaries();
	LPDISPATCH GetRegisteredApplications();
	LPDISPATCH GetTextStyles();
	LPDISPATCH GetUserCoordinateSystems();
	LPDISPATCH GetViews();
	LPDISPATCH GetViewports();
	double GetElevationModelSpace();
	void SetElevationModelSpace(double newValue);
	double GetElevationPaperSpace();
	void SetElevationPaperSpace(double newValue);
	VARIANT GetLimits();
	void SetLimits(const VARIANT& newValue);
	LPDISPATCH HandleToObject(LPCTSTR Handle);
	LPDISPATCH ObjectIdToObject(long ObjectID);
	LPDISPATCH GetLayouts();
	LPDISPATCH GetPlotConfigurations();
	LPDISPATCH GetPreferences();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadModelSpace wrapper class

class IAcadModelSpace : public COleDispatchDriver
{
public:
	IAcadModelSpace() {}		// Calls COleDispatchDriver default constructor
	IAcadModelSpace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadModelSpace(const IAcadModelSpace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetOrigin();
	void SetOrigin(const VARIANT& newValue);
	LPDISPATCH AddCustomObject(LPCTSTR ClassName);
	LPDISPATCH Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH Add3DMesh(long M, long N, const VARIANT& PointsMatrix);
	LPDISPATCH Add3DPoly(const VARIANT& PointsArray);
	LPDISPATCH AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle);
	LPDISPATCH AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value);
	LPDISPATCH AddBox(const VARIANT& Origin, double Length, double Width, double Height);
	LPDISPATCH AddCircle(const VARIANT& Center, double Radius);
	LPDISPATCH AddCone(const VARIANT& Center, double BaseRadius, double Height);
	LPDISPATCH AddCylinder(const VARIANT& Center, double Radius, double Height);
	LPDISPATCH AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition);
	LPDISPATCH AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength);
	LPDISPATCH AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle);
	LPDISPATCH AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis);
	LPDISPATCH AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength);
	LPDISPATCH AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio);
	LPDISPATCH AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle);
	LPDISPATCH AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path);
	LPDISPATCH AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type);
	LPDISPATCH AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text);
	LPDISPATCH AddPoint(const VARIANT& Point);
	LPDISPATCH AddLightWeightPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddRay(const VARIANT& Point1, const VARIANT& Point2);
	VARIANT AddRegion(const VARIANT& ObjectList);
	LPDISPATCH AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle);
	LPDISPATCH AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH AddSphere(const VARIANT& Center, double Radius);
	LPDISPATCH AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent);
	LPDISPATCH AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height);
	LPDISPATCH AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction);
	LPDISPATCH AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius);
	LPDISPATCH AddTrace(const VARIANT& PointsArray);
	LPDISPATCH AddWedge(const VARIANT& Center, double Length, double Width, double Height);
	LPDISPATCH AddXline(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation);
	LPDISPATCH AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity);
	LPDISPATCH AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint);
	BOOL GetIsLayout();
	LPDISPATCH GetLayout();
	BOOL GetIsXRef();
	LPDISPATCH AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing);
	LPDISPATCH AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList);
	LPDISPATCH AddMLine(const VARIANT& VertexList);
	LPDISPATCH AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH GetXRefDatabase();
	LPDISPATCH AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay);
	void Unload();
	void Reload();
	void Bind(BOOL bPrefixName);
	void Detach();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadBlock wrapper class

class IAcadBlock : public COleDispatchDriver
{
public:
	IAcadBlock() {}		// Calls COleDispatchDriver default constructor
	IAcadBlock(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadBlock(const IAcadBlock& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetOrigin();
	void SetOrigin(const VARIANT& newValue);
	LPDISPATCH AddCustomObject(LPCTSTR ClassName);
	LPDISPATCH Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH Add3DMesh(long M, long N, const VARIANT& PointsMatrix);
	LPDISPATCH Add3DPoly(const VARIANT& PointsArray);
	LPDISPATCH AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle);
	LPDISPATCH AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value);
	LPDISPATCH AddBox(const VARIANT& Origin, double Length, double Width, double Height);
	LPDISPATCH AddCircle(const VARIANT& Center, double Radius);
	LPDISPATCH AddCone(const VARIANT& Center, double BaseRadius, double Height);
	LPDISPATCH AddCylinder(const VARIANT& Center, double Radius, double Height);
	LPDISPATCH AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition);
	LPDISPATCH AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength);
	LPDISPATCH AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle);
	LPDISPATCH AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis);
	LPDISPATCH AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength);
	LPDISPATCH AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio);
	LPDISPATCH AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle);
	LPDISPATCH AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path);
	LPDISPATCH AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type);
	LPDISPATCH AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text);
	LPDISPATCH AddPoint(const VARIANT& Point);
	LPDISPATCH AddLightWeightPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddRay(const VARIANT& Point1, const VARIANT& Point2);
	VARIANT AddRegion(const VARIANT& ObjectList);
	LPDISPATCH AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle);
	LPDISPATCH AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH AddSphere(const VARIANT& Center, double Radius);
	LPDISPATCH AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent);
	LPDISPATCH AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height);
	LPDISPATCH AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction);
	LPDISPATCH AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius);
	LPDISPATCH AddTrace(const VARIANT& PointsArray);
	LPDISPATCH AddWedge(const VARIANT& Center, double Length, double Width, double Height);
	LPDISPATCH AddXline(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation);
	LPDISPATCH AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity);
	LPDISPATCH AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint);
	BOOL GetIsLayout();
	LPDISPATCH GetLayout();
	BOOL GetIsXRef();
	LPDISPATCH AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing);
	LPDISPATCH AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList);
	LPDISPATCH AddMLine(const VARIANT& VertexList);
	LPDISPATCH AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH GetXRefDatabase();
	LPDISPATCH AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay);
	void Unload();
	void Reload();
	void Bind(BOOL bPrefixName);
	void Detach();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadEntity wrapper class

class IAcadEntity : public COleDispatchDriver
{
public:
	IAcadEntity() {}		// Calls COleDispatchDriver default constructor
	IAcadEntity(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadEntity(const IAcadEntity& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadHyperlinks wrapper class

class IAcadHyperlinks : public COleDispatchDriver
{
public:
	IAcadHyperlinks() {}		// Calls COleDispatchDriver default constructor
	IAcadHyperlinks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadHyperlinks(const IAcadHyperlinks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(long Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH Add(LPCTSTR Name, const VARIANT& Description, const VARIANT& NamedLocation);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadHyperlink wrapper class

class IAcadHyperlink : public COleDispatchDriver
{
public:
	IAcadHyperlink() {}		// Calls COleDispatchDriver default constructor
	IAcadHyperlink(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadHyperlink(const IAcadHyperlink& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetUrl(LPCTSTR lpszNewValue);
	CString GetUrl();
	void SetURLDescription(LPCTSTR lpszNewValue);
	CString GetURLDescription();
	LPDISPATCH GetApplication();
	void Delete();
	void SetURLNamedLocation(LPCTSTR lpszNewValue);
	CString GetURLNamedLocation();
};
/////////////////////////////////////////////////////////////////////////////
// IAcad3DFace wrapper class

class IAcad3DFace : public COleDispatchDriver
{
public:
	IAcad3DFace() {}		// Calls COleDispatchDriver default constructor
	IAcad3DFace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcad3DFace(const IAcad3DFace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	BOOL GetVisibilityEdge1();
	void SetVisibilityEdge1(BOOL bNewValue);
	BOOL GetVisibilityEdge2();
	void SetVisibilityEdge2(BOOL bNewValue);
	BOOL GetVisibilityEdge3();
	void SetVisibilityEdge3(BOOL bNewValue);
	BOOL GetVisibilityEdge4();
	void SetVisibilityEdge4(BOOL bNewValue);
	BOOL GetInvisibleEdge(long Index);
	void SetInvisibleEdge(long Index, BOOL State);
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPolygonMesh wrapper class

class IAcadPolygonMesh : public COleDispatchDriver
{
public:
	IAcadPolygonMesh() {}		// Calls COleDispatchDriver default constructor
	IAcadPolygonMesh(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPolygonMesh(const IAcadPolygonMesh& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	BOOL GetMClose();
	void SetMClose(BOOL bNewValue);
	BOOL GetNClose();
	void SetNClose(BOOL bNewValue);
	long GetMDensity();
	void SetMDensity(long nNewValue);
	long GetNDensity();
	void SetNDensity(long nNewValue);
	long GetMVertexCount();
	long GetNVertexCount();
	long GetType();
	void SetType(long nNewValue);
	void AppendVertex(const VARIANT& vertex);
	VARIANT Explode();
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcad3DPolyline wrapper class

class IAcad3DPolyline : public COleDispatchDriver
{
public:
	IAcad3DPolyline() {}		// Calls COleDispatchDriver default constructor
	IAcad3DPolyline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcad3DPolyline(const IAcad3DPolyline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	void AppendVertex(const VARIANT& vertex);
	VARIANT Explode();
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
	long GetType();
	void SetType(long nNewValue);
	BOOL GetClosed();
	void SetClosed(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadArc wrapper class

class IAcadArc : public COleDispatchDriver
{
public:
	IAcadArc() {}		// Calls COleDispatchDriver default constructor
	IAcadArc(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadArc(const IAcadArc& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetStartPoint();
	VARIANT GetCenter();
	void SetCenter(const VARIANT& newValue);
	VARIANT GetEndPoint();
	double GetRadius();
	void SetRadius(double newValue);
	double GetStartAngle();
	void SetStartAngle(double newValue);
	double GetEndAngle();
	void SetEndAngle(double newValue);
	double GetTotalAngle();
	double GetArcLength();
	double GetThickness();
	void SetThickness(double newValue);
	VARIANT Offset(double Distance);
	double GetArea();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadAttribute wrapper class

class IAcadAttribute : public COleDispatchDriver
{
public:
	IAcadAttribute() {}		// Calls COleDispatchDriver default constructor
	IAcadAttribute(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadAttribute(const IAcadAttribute& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	long GetFieldLength();
	void SetFieldLength(long nNewValue);
	CString GetTagString();
	void SetTagString(LPCTSTR lpszNewValue);
	CString GetPromptString();
	void SetPromptString(LPCTSTR lpszNewValue);
	CString GetTextString();
	void SetTextString(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	double GetObliqueAngle();
	void SetObliqueAngle(double newValue);
	VARIANT GetTextAlignmentPoint();
	void SetTextAlignmentPoint(const VARIANT& newValue);
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	long GetTextGenerationFlag();
	void SetTextGenerationFlag(long nNewValue);
	double GetThickness();
	void SetThickness(double newValue);
	long GetMode();
	void SetMode(long nNewValue);
	BOOL GetUpsideDown();
	void SetUpsideDown(BOOL bNewValue);
	BOOL GetBackward();
	void SetBackward(BOOL bNewValue);
	BOOL GetInvisible();
	void SetInvisible(BOOL bNewValue);
	BOOL GetConstant();
	void SetConstant(BOOL bNewValue);
	BOOL GetVerify();
	void SetVerify(BOOL bNewValue);
	BOOL GetPreset();
	void SetPreset(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcad3DSolid wrapper class

class IAcad3DSolid : public COleDispatchDriver
{
public:
	IAcad3DSolid() {}		// Calls COleDispatchDriver default constructor
	IAcad3DSolid(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcad3DSolid(const IAcad3DSolid& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCentroid();
	VARIANT GetMomentOfInertia();
	VARIANT GetPrincipalDirections();
	VARIANT GetPrincipalMoments();
	VARIANT GetProductOfInertia();
	VARIANT GetRadiiOfGyration();
	double GetVolume();
	void Boolean(long Operation, LPDISPATCH SolidObject);
	LPDISPATCH CheckInterference(LPDISPATCH Object, BOOL CreateInterferenceSolid);
	LPDISPATCH SectionSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	LPDISPATCH SliceSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, BOOL Negative);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadRegion wrapper class

class IAcadRegion : public COleDispatchDriver
{
public:
	IAcadRegion() {}		// Calls COleDispatchDriver default constructor
	IAcadRegion(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadRegion(const IAcadRegion& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	double GetArea();
	VARIANT GetCentroid();
	VARIANT GetMomentOfInertia();
	VARIANT GetNormal();
	double GetPerimeter();
	VARIANT GetPrincipalDirections();
	VARIANT GetPrincipalMoments();
	double GetProductOfInertia();
	VARIANT GetRadiiOfGyration();
	void Boolean(long Operation, LPDISPATCH Object);
	VARIANT Explode();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadCircle wrapper class

class IAcadCircle : public COleDispatchDriver
{
public:
	IAcadCircle() {}		// Calls COleDispatchDriver default constructor
	IAcadCircle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadCircle(const IAcadCircle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCenter();
	void SetCenter(const VARIANT& newValue);
	double GetRadius();
	void SetRadius(double newValue);
	double GetDiameter();
	void SetDiameter(double newValue);
	double GetCircumference();
	void SetCircumference(double newValue);
	double GetArea();
	void SetArea(double newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
	VARIANT Offset(double Distance);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimAligned wrapper class

class IAcadDimAligned : public COleDispatchDriver
{
public:
	IAcadDimAligned() {}		// Calls COleDispatchDriver default constructor
	IAcadDimAligned(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimAligned(const IAcadDimAligned& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	VARIANT GetExtLine1Point();
	void SetExtLine1Point(const VARIANT& newValue);
	VARIANT GetExtLine2Point();
	void SetExtLine2Point(const VARIANT& newValue);
	BOOL GetAltUnits();
	void SetAltUnits(BOOL bNewValue);
	long GetAltUnitsPrecision();
	void SetAltUnitsPrecision(long nNewValue);
	double GetAltUnitsScale();
	void SetAltUnitsScale(double newValue);
	double GetAltRoundDistance();
	void SetAltRoundDistance(double newValue);
	long GetAltTolerancePrecision();
	void SetAltTolerancePrecision(long nNewValue);
	long GetAltUnitsFormat();
	void SetAltUnitsFormat(long nNewValue);
	CString GetAltTextPrefix();
	void SetAltTextPrefix(LPCTSTR lpszNewValue);
	CString GetAltTextSuffix();
	void SetAltTextSuffix(LPCTSTR lpszNewValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetExtensionLineColor();
	void SetExtensionLineColor(long nNewValue);
	long GetPrimaryUnitsPrecision();
	void SetPrimaryUnitsPrecision(long nNewValue);
	double GetDimensionLineExtend();
	void SetDimensionLineExtend(double newValue);
	double GetExtensionLineExtend();
	void SetExtensionLineExtend(double newValue);
	long GetFit();
	void SetFit(long nNewValue);
	long GetFractionFormat();
	void SetFractionFormat(long nNewValue);
	long GetHorizontalTextPosition();
	void SetHorizontalTextPosition(long nNewValue);
	double GetLinearScaleFactor();
	void SetLinearScaleFactor(double newValue);
	long GetUnitsFormat();
	void SetUnitsFormat(long nNewValue);
	long GetExtensionLineWeight();
	void SetExtensionLineWeight(long nNewValue);
	double GetRoundDistance();
	void SetRoundDistance(double newValue);
	BOOL GetDimLine1Suppress();
	void SetDimLine1Suppress(BOOL bNewValue);
	BOOL GetDimLine2Suppress();
	void SetDimLine2Suppress(BOOL bNewValue);
	BOOL GetExtLine1Suppress();
	void SetExtLine1Suppress(BOOL bNewValue);
	BOOL GetExtLine2Suppress();
	void SetExtLine2Suppress(BOOL bNewValue);
	BOOL GetDimLineInside();
	void SetDimLineInside(BOOL bNewValue);
	BOOL GetTextInsideAlign();
	void SetTextInsideAlign(BOOL bNewValue);
	BOOL GetTextInside();
	void SetTextInside(BOOL bNewValue);
	BOOL GetForceLineInside();
	void SetForceLineInside(BOOL bNewValue);
	BOOL GetTextOutsideAlign();
	void SetTextOutsideAlign(BOOL bNewValue);
	double GetExtensionLineOffset();
	void SetExtensionLineOffset(double newValue);
	BOOL GetAltSuppressLeadingZeros();
	void SetAltSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltSuppressTrailingZeros();
	void SetAltSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltSuppressZeroFeet();
	void SetAltSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltSuppressZeroInches();
	void SetAltSuppressZeroInches(BOOL bNewValue);
	BOOL GetAltToleranceSuppressLeadingZeros();
	void SetAltToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressTrailingZeros();
	void SetAltToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroFeet();
	void SetAltToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroInches();
	void SetAltToleranceSuppressZeroInches(BOOL bNewValue);
	BOOL GetSuppressZeroFeet();
	void SetSuppressZeroFeet(BOOL bNewValue);
	BOOL GetSuppressZeroInches();
	void SetSuppressZeroInches(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroFeet();
	void SetToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroInches();
	void SetToleranceSuppressZeroInches(BOOL bNewValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowhead1Type();
	void SetArrowhead1Type(long nNewValue);
	long GetArrowhead2Type();
	void SetArrowhead2Type(long nNewValue);
	double GetMeasurement();
	CString GetArrowhead1Block();
	void SetArrowhead1Block(LPCTSTR lpszNewValue);
	CString GetArrowhead2Block();
	void SetArrowhead2Block(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimension wrapper class

class IAcadDimension : public COleDispatchDriver
{
public:
	IAcadDimension() {}		// Calls COleDispatchDriver default constructor
	IAcadDimension(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimension(const IAcadDimension& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimAngular wrapper class

class IAcadDimAngular : public COleDispatchDriver
{
public:
	IAcadDimAngular() {}		// Calls COleDispatchDriver default constructor
	IAcadDimAngular(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimAngular(const IAcadDimAngular& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	VARIANT GetExtLine1StartPoint();
	void SetExtLine1StartPoint(const VARIANT& newValue);
	VARIANT GetExtLine1EndPoint();
	void SetExtLine1EndPoint(const VARIANT& newValue);
	VARIANT GetExtLine2StartPoint();
	void SetExtLine2StartPoint(const VARIANT& newValue);
	VARIANT GetExtLine2EndPoint();
	void SetExtLine2EndPoint(const VARIANT& newValue);
	long GetAngleFormat();
	void SetAngleFormat(long nNewValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetExtensionLineColor();
	void SetExtensionLineColor(long nNewValue);
	double GetExtensionLineExtend();
	void SetExtensionLineExtend(double newValue);
	long GetFit();
	void SetFit(long nNewValue);
	long GetHorizontalTextPosition();
	void SetHorizontalTextPosition(long nNewValue);
	long GetExtensionLineWeight();
	void SetExtensionLineWeight(long nNewValue);
	BOOL GetDimLine1Suppress();
	void SetDimLine1Suppress(BOOL bNewValue);
	BOOL GetDimLine2Suppress();
	void SetDimLine2Suppress(BOOL bNewValue);
	BOOL GetExtLine1Suppress();
	void SetExtLine1Suppress(BOOL bNewValue);
	BOOL GetExtLine2Suppress();
	void SetExtLine2Suppress(BOOL bNewValue);
	BOOL GetDimLineInside();
	void SetDimLineInside(BOOL bNewValue);
	BOOL GetTextInsideAlign();
	void SetTextInsideAlign(BOOL bNewValue);
	BOOL GetTextInside();
	void SetTextInside(BOOL bNewValue);
	BOOL GetForceLineInside();
	void SetForceLineInside(BOOL bNewValue);
	BOOL GetTextOutsideAlign();
	void SetTextOutsideAlign(BOOL bNewValue);
	long GetTextPrecision();
	void SetTextPrecision(long nNewValue);
	double GetExtensionLineOffset();
	void SetExtensionLineOffset(double newValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowhead1Type();
	void SetArrowhead1Type(long nNewValue);
	long GetArrowhead2Type();
	void SetArrowhead2Type(long nNewValue);
	double GetMeasurement();
	CString GetArrowhead1Block();
	void SetArrowhead1Block(LPCTSTR lpszNewValue);
	CString GetArrowhead2Block();
	void SetArrowhead2Block(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimDiametric wrapper class

class IAcadDimDiametric : public COleDispatchDriver
{
public:
	IAcadDimDiametric() {}		// Calls COleDispatchDriver default constructor
	IAcadDimDiametric(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimDiametric(const IAcadDimDiametric& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	void SetLeaderLength(double newValue);
	BOOL GetAltUnits();
	void SetAltUnits(BOOL bNewValue);
	long GetAltUnitsPrecision();
	void SetAltUnitsPrecision(long nNewValue);
	double GetAltUnitsScale();
	void SetAltUnitsScale(double newValue);
	double GetAltRoundDistance();
	void SetAltRoundDistance(double newValue);
	long GetAltTolerancePrecision();
	void SetAltTolerancePrecision(long nNewValue);
	long GetAltUnitsFormat();
	void SetAltUnitsFormat(long nNewValue);
	CString GetAltTextPrefix();
	void SetAltTextPrefix(LPCTSTR lpszNewValue);
	CString GetAltTextSuffix();
	void SetAltTextSuffix(LPCTSTR lpszNewValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetPrimaryUnitsPrecision();
	void SetPrimaryUnitsPrecision(long nNewValue);
	long GetFractionFormat();
	void SetFractionFormat(long nNewValue);
	long GetFit();
	void SetFit(long nNewValue);
	double GetLinearScaleFactor();
	void SetLinearScaleFactor(double newValue);
	long GetUnitsFormat();
	void SetUnitsFormat(long nNewValue);
	double GetRoundDistance();
	void SetRoundDistance(double newValue);
	BOOL GetDimLine1Suppress();
	void SetDimLine1Suppress(BOOL bNewValue);
	BOOL GetDimLine2Suppress();
	void SetDimLine2Suppress(BOOL bNewValue);
	BOOL GetTextInsideAlign();
	void SetTextInsideAlign(BOOL bNewValue);
	BOOL GetTextInside();
	void SetTextInside(BOOL bNewValue);
	BOOL GetForceLineInside();
	void SetForceLineInside(BOOL bNewValue);
	BOOL GetTextOutsideAlign();
	void SetTextOutsideAlign(BOOL bNewValue);
	long GetCenterType();
	void SetCenterType(long nNewValue);
	double GetCenterMarkSize();
	void SetCenterMarkSize(double newValue);
	BOOL GetAltSuppressLeadingZeros();
	void SetAltSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltSuppressTrailingZeros();
	void SetAltSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltSuppressZeroFeet();
	void SetAltSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltSuppressZeroInches();
	void SetAltSuppressZeroInches(BOOL bNewValue);
	BOOL GetAltToleranceSuppressLeadingZeros();
	void SetAltToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressTrailingZeros();
	void SetAltToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroFeet();
	void SetAltToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroInches();
	void SetAltToleranceSuppressZeroInches(BOOL bNewValue);
	BOOL GetSuppressZeroFeet();
	void SetSuppressZeroFeet(BOOL bNewValue);
	BOOL GetSuppressZeroInches();
	void SetSuppressZeroInches(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroFeet();
	void SetToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroInches();
	void SetToleranceSuppressZeroInches(BOOL bNewValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowhead1Type();
	void SetArrowhead1Type(long nNewValue);
	long GetArrowhead2Type();
	void SetArrowhead2Type(long nNewValue);
	double GetMeasurement();
	CString GetArrowhead1Block();
	void SetArrowhead1Block(LPCTSTR lpszNewValue);
	CString GetArrowhead2Block();
	void SetArrowhead2Block(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimRotated wrapper class

class IAcadDimRotated : public COleDispatchDriver
{
public:
	IAcadDimRotated() {}		// Calls COleDispatchDriver default constructor
	IAcadDimRotated(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimRotated(const IAcadDimRotated& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltUnits();
	void SetAltUnits(BOOL bNewValue);
	long GetAltUnitsPrecision();
	void SetAltUnitsPrecision(long nNewValue);
	double GetAltUnitsScale();
	void SetAltUnitsScale(double newValue);
	double GetAltRoundDistance();
	void SetAltRoundDistance(double newValue);
	long GetAltTolerancePrecision();
	void SetAltTolerancePrecision(long nNewValue);
	long GetAltUnitsFormat();
	void SetAltUnitsFormat(long nNewValue);
	CString GetAltTextPrefix();
	void SetAltTextPrefix(LPCTSTR lpszNewValue);
	CString GetAltTextSuffix();
	void SetAltTextSuffix(LPCTSTR lpszNewValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetExtensionLineColor();
	void SetExtensionLineColor(long nNewValue);
	long GetPrimaryUnitsPrecision();
	void SetPrimaryUnitsPrecision(long nNewValue);
	double GetDimensionLineExtend();
	void SetDimensionLineExtend(double newValue);
	double GetExtensionLineExtend();
	void SetExtensionLineExtend(double newValue);
	long GetFit();
	void SetFit(long nNewValue);
	long GetFractionFormat();
	void SetFractionFormat(long nNewValue);
	long GetHorizontalTextPosition();
	void SetHorizontalTextPosition(long nNewValue);
	double GetLinearScaleFactor();
	void SetLinearScaleFactor(double newValue);
	long GetUnitsFormat();
	void SetUnitsFormat(long nNewValue);
	long GetExtensionLineWeight();
	void SetExtensionLineWeight(long nNewValue);
	double GetRoundDistance();
	void SetRoundDistance(double newValue);
	BOOL GetDimLine1Suppress();
	void SetDimLine1Suppress(BOOL bNewValue);
	BOOL GetDimLine2Suppress();
	void SetDimLine2Suppress(BOOL bNewValue);
	BOOL GetExtLine1Suppress();
	void SetExtLine1Suppress(BOOL bNewValue);
	BOOL GetExtLine2Suppress();
	void SetExtLine2Suppress(BOOL bNewValue);
	BOOL GetDimLineInside();
	void SetDimLineInside(BOOL bNewValue);
	BOOL GetTextInsideAlign();
	void SetTextInsideAlign(BOOL bNewValue);
	BOOL GetTextInside();
	void SetTextInside(BOOL bNewValue);
	BOOL GetForceLineInside();
	void SetForceLineInside(BOOL bNewValue);
	BOOL GetTextOutsideAlign();
	void SetTextOutsideAlign(BOOL bNewValue);
	double GetExtensionLineOffset();
	void SetExtensionLineOffset(double newValue);
	BOOL GetAltSuppressLeadingZeros();
	void SetAltSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltSuppressTrailingZeros();
	void SetAltSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltSuppressZeroFeet();
	void SetAltSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltSuppressZeroInches();
	void SetAltSuppressZeroInches(BOOL bNewValue);
	BOOL GetAltToleranceSuppressLeadingZeros();
	void SetAltToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressTrailingZeros();
	void SetAltToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroFeet();
	void SetAltToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroInches();
	void SetAltToleranceSuppressZeroInches(BOOL bNewValue);
	BOOL GetSuppressZeroFeet();
	void SetSuppressZeroFeet(BOOL bNewValue);
	BOOL GetSuppressZeroInches();
	void SetSuppressZeroInches(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroFeet();
	void SetToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroInches();
	void SetToleranceSuppressZeroInches(BOOL bNewValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowhead1Type();
	void SetArrowhead1Type(long nNewValue);
	long GetArrowhead2Type();
	void SetArrowhead2Type(long nNewValue);
	double GetMeasurement();
	CString GetArrowhead1Block();
	void SetArrowhead1Block(LPCTSTR lpszNewValue);
	CString GetArrowhead2Block();
	void SetArrowhead2Block(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimOrdinate wrapper class

class IAcadDimOrdinate : public COleDispatchDriver
{
public:
	IAcadDimOrdinate() {}		// Calls COleDispatchDriver default constructor
	IAcadDimOrdinate(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimOrdinate(const IAcadDimOrdinate& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltUnits();
	void SetAltUnits(BOOL bNewValue);
	long GetAltUnitsPrecision();
	void SetAltUnitsPrecision(long nNewValue);
	double GetAltUnitsScale();
	void SetAltUnitsScale(double newValue);
	double GetAltRoundDistance();
	void SetAltRoundDistance(double newValue);
	long GetAltTolerancePrecision();
	void SetAltTolerancePrecision(long nNewValue);
	long GetAltUnitsFormat();
	void SetAltUnitsFormat(long nNewValue);
	CString GetAltTextPrefix();
	void SetAltTextPrefix(LPCTSTR lpszNewValue);
	CString GetAltTextSuffix();
	void SetAltTextSuffix(LPCTSTR lpszNewValue);
	long GetExtensionLineColor();
	void SetExtensionLineColor(long nNewValue);
	long GetPrimaryUnitsPrecision();
	void SetPrimaryUnitsPrecision(long nNewValue);
	long GetFractionFormat();
	void SetFractionFormat(long nNewValue);
	double GetLinearScaleFactor();
	void SetLinearScaleFactor(double newValue);
	long GetUnitsFormat();
	void SetUnitsFormat(long nNewValue);
	long GetExtensionLineWeight();
	void SetExtensionLineWeight(long nNewValue);
	double GetRoundDistance();
	void SetRoundDistance(double newValue);
	double GetExtensionLineOffset();
	void SetExtensionLineOffset(double newValue);
	BOOL GetAltSuppressLeadingZeros();
	void SetAltSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltSuppressTrailingZeros();
	void SetAltSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltSuppressZeroFeet();
	void SetAltSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltSuppressZeroInches();
	void SetAltSuppressZeroInches(BOOL bNewValue);
	BOOL GetAltToleranceSuppressLeadingZeros();
	void SetAltToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressTrailingZeros();
	void SetAltToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroFeet();
	void SetAltToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroInches();
	void SetAltToleranceSuppressZeroInches(BOOL bNewValue);
	BOOL GetSuppressZeroFeet();
	void SetSuppressZeroFeet(BOOL bNewValue);
	BOOL GetSuppressZeroInches();
	void SetSuppressZeroInches(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroFeet();
	void SetToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroInches();
	void SetToleranceSuppressZeroInches(BOOL bNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	double GetMeasurement();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimRadial wrapper class

class IAcadDimRadial : public COleDispatchDriver
{
public:
	IAcadDimRadial() {}		// Calls COleDispatchDriver default constructor
	IAcadDimRadial(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimRadial(const IAcadDimRadial& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	void SetLeaderLength(double newValue);
	BOOL GetAltUnits();
	void SetAltUnits(BOOL bNewValue);
	long GetAltUnitsPrecision();
	void SetAltUnitsPrecision(long nNewValue);
	double GetAltUnitsScale();
	void SetAltUnitsScale(double newValue);
	double GetAltRoundDistance();
	void SetAltRoundDistance(double newValue);
	long GetAltTolerancePrecision();
	void SetAltTolerancePrecision(long nNewValue);
	long GetAltUnitsFormat();
	void SetAltUnitsFormat(long nNewValue);
	CString GetAltTextPrefix();
	void SetAltTextPrefix(LPCTSTR lpszNewValue);
	CString GetAltTextSuffix();
	void SetAltTextSuffix(LPCTSTR lpszNewValue);
	long GetCenterType();
	void SetCenterType(long nNewValue);
	double GetCenterMarkSize();
	void SetCenterMarkSize(double newValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetPrimaryUnitsPrecision();
	void SetPrimaryUnitsPrecision(long nNewValue);
	long GetFractionFormat();
	void SetFractionFormat(long nNewValue);
	long GetFit();
	void SetFit(long nNewValue);
	double GetLinearScaleFactor();
	void SetLinearScaleFactor(double newValue);
	long GetUnitsFormat();
	void SetUnitsFormat(long nNewValue);
	double GetRoundDistance();
	void SetRoundDistance(double newValue);
	BOOL GetDimLineSuppress();
	void SetDimLineSuppress(BOOL bNewValue);
	BOOL GetTextInsideAlign();
	void SetTextInsideAlign(BOOL bNewValue);
	BOOL GetTextInside();
	void SetTextInside(BOOL bNewValue);
	BOOL GetForceLineInside();
	void SetForceLineInside(BOOL bNewValue);
	BOOL GetTextOutsideAlign();
	void SetTextOutsideAlign(BOOL bNewValue);
	BOOL GetAltSuppressLeadingZeros();
	void SetAltSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltSuppressTrailingZeros();
	void SetAltSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltSuppressZeroFeet();
	void SetAltSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltSuppressZeroInches();
	void SetAltSuppressZeroInches(BOOL bNewValue);
	BOOL GetAltToleranceSuppressLeadingZeros();
	void SetAltToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressTrailingZeros();
	void SetAltToleranceSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroFeet();
	void SetAltToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetAltToleranceSuppressZeroInches();
	void SetAltToleranceSuppressZeroInches(BOOL bNewValue);
	BOOL GetSuppressZeroFeet();
	void SetSuppressZeroFeet(BOOL bNewValue);
	BOOL GetSuppressZeroInches();
	void SetSuppressZeroInches(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroFeet();
	void SetToleranceSuppressZeroFeet(BOOL bNewValue);
	BOOL GetToleranceSuppressZeroInches();
	void SetToleranceSuppressZeroInches(BOOL bNewValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowheadType();
	void SetArrowheadType(long nNewValue);
	double GetMeasurement();
	CString GetArrowheadBlock();
	void SetArrowheadBlock(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadEllipse wrapper class

class IAcadEllipse : public COleDispatchDriver
{
public:
	IAcadEllipse() {}		// Calls COleDispatchDriver default constructor
	IAcadEllipse(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadEllipse(const IAcadEllipse& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetStartPoint();
	VARIANT GetCenter();
	void SetCenter(const VARIANT& newValue);
	VARIANT GetEndPoint();
	double GetMajorRadius();
	void SetMajorRadius(double newValue);
	double GetMinorRadius();
	void SetMinorRadius(double newValue);
	double GetRadiusRatio();
	void SetRadiusRatio(double newValue);
	double GetStartAngle();
	void SetStartAngle(double newValue);
	double GetEndAngle();
	void SetEndAngle(double newValue);
	double GetStartParameter();
	void SetStartParameter(double newValue);
	double GetEndParameter();
	void SetEndParameter(double newValue);
	VARIANT GetMajorAxis();
	void SetMajorAxis(const VARIANT& newValue);
	VARIANT GetMinorAxis();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetArea();
	VARIANT Offset(double Distance);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLeader wrapper class

class IAcadLeader : public COleDispatchDriver
{
public:
	IAcadLeader() {}		// Calls COleDispatchDriver default constructor
	IAcadLeader(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLeader(const IAcadLeader& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetNormal();
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetType();
	void SetType(long nNewValue);
	void Evaluate();
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
	LPDISPATCH GetAnnotation();
	void SetAnnotation(LPDISPATCH newValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowheadType();
	void SetArrowheadType(long nNewValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetArrowheadBlock();
	void SetArrowheadBlock(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMText wrapper class

class IAcadMText : public COleDispatchDriver
{
public:
	IAcadMText() {}		// Calls COleDispatchDriver default constructor
	IAcadMText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMText(const IAcadMText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	CString GetTextString();
	void SetTextString(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetAttachmentPoint();
	void SetAttachmentPoint(long nNewValue);
	long GetDrawingDirection();
	void SetDrawingDirection(long nNewValue);
	double GetWidth();
	void SetWidth(double newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetLineSpacingFactor();
	void SetLineSpacingFactor(double newValue);
	long GetLineSpacingStyle();
	void SetLineSpacingStyle(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPoint wrapper class

class IAcadPoint : public COleDispatchDriver
{
public:
	IAcadPoint() {}		// Calls COleDispatchDriver default constructor
	IAcadPoint(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPoint(const IAcadPoint& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLWPolyline wrapper class

class IAcadLWPolyline : public COleDispatchDriver
{
public:
	IAcadLWPolyline() {}		// Calls COleDispatchDriver default constructor
	IAcadLWPolyline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLWPolyline(const IAcadLWPolyline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
	void AddVertex(long Index, const VARIANT& vertex);
	VARIANT Explode();
	double GetBulge(long Index);
	void SetBulge(long Index, double bulge);
	void GetWidth(long Index, double* StartWidth, double* EndWidth);
	void SetWidth(long Index, double StartWidth, double EndWidth);
	double GetConstantWidth();
	void SetConstantWidth(double newValue);
	VARIANT Offset(double Distance);
	double GetElevation();
	void SetElevation(double newValue);
	double GetArea();
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
	BOOL GetClosed();
	void SetClosed(BOOL bNewValue);
	BOOL GetLinetypeGeneration();
	void SetLinetypeGeneration(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPolyline wrapper class

class IAcadPolyline : public COleDispatchDriver
{
public:
	IAcadPolyline() {}		// Calls COleDispatchDriver default constructor
	IAcadPolyline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPolyline(const IAcadPolyline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
	void AppendVertex(const VARIANT& vertex);
	VARIANT Explode();
	double GetBulge(long Index);
	void SetBulge(long Index, double bulge);
	void GetWidth(long Index, double* StartWidth, double* EndWidth);
	void SetWidth(long Index, double StartWidth, double EndWidth);
	double GetConstantWidth();
	void SetConstantWidth(double newValue);
	VARIANT Offset(double Distance);
	double GetElevation();
	void SetElevation(double newValue);
	long GetType();
	void SetType(long nNewValue);
	BOOL GetClosed();
	void SetClosed(BOOL bNewValue);
	BOOL GetLinetypeGeneration();
	void SetLinetypeGeneration(BOOL bNewValue);
	double GetArea();
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadRay wrapper class

class IAcadRay : public COleDispatchDriver
{
public:
	IAcadRay() {}		// Calls COleDispatchDriver default constructor
	IAcadRay(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadRay(const IAcadRay& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetBasePoint();
	void SetBasePoint(const VARIANT& newValue);
	VARIANT GetSecondPoint();
	void SetSecondPoint(const VARIANT& newValue);
	VARIANT GetDirectionVector();
	void SetDirectionVector(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadShape wrapper class

class IAcadShape : public COleDispatchDriver
{
public:
	IAcadShape() {}		// Calls COleDispatchDriver default constructor
	IAcadShape(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadShape(const IAcadShape& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	double GetObliqueAngle();
	void SetObliqueAngle(double newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadSolid wrapper class

class IAcadSolid : public COleDispatchDriver
{
public:
	IAcadSolid() {}		// Calls COleDispatchDriver default constructor
	IAcadSolid(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadSolid(const IAcadSolid& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadSpline wrapper class

class IAcadSpline : public COleDispatchDriver
{
public:
	IAcadSpline() {}		// Calls COleDispatchDriver default constructor
	IAcadSpline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadSpline(const IAcadSpline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	long GetNumberOfControlPoints();
	VARIANT GetControlPoints();
	void SetControlPoints(const VARIANT& newValue);
	long GetNumberOfFitPoints();
	VARIANT GetFitPoints();
	void SetFitPoints(const VARIANT& newValue);
	long GetDegree();
	BOOL GetClosed();
	BOOL GetIsPlanar();
	BOOL GetIsRational();
	BOOL GetIsPeriodic();
	VARIANT GetStartTangent();
	void SetStartTangent(const VARIANT& newValue);
	VARIANT GetEndTangent();
	void SetEndTangent(const VARIANT& newValue);
	double GetFitTolerance();
	void SetFitTolerance(double newValue);
	double GetArea();
	void SetControlPoint(long Index, const VARIANT& controlPoint);
	VARIANT GetControlPoint(long Index);
	void SetFitPoint(long Index, const VARIANT& fitPoint);
	VARIANT GetFitPoint(long Index);
	void SetWeight(long Index, double weight);
	double GetWeight(long Index);
	void AddFitPoint(long Index, const VARIANT& fitPoint);
	void DeleteFitPoint(long Index);
	void ElevateOrder(long Order);
	VARIANT Offset(double Distance);
	void PurgeFitData();
	void Reverse();
	VARIANT GetKnots();
	void SetKnots(const VARIANT& newValue);
	VARIANT GetWeights();
	void SetWeights(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadText wrapper class

class IAcadText : public COleDispatchDriver
{
public:
	IAcadText() {}		// Calls COleDispatchDriver default constructor
	IAcadText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadText(const IAcadText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	CString GetTextString();
	void SetTextString(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	double GetObliqueAngle();
	void SetObliqueAngle(double newValue);
	VARIANT GetTextAlignmentPoint();
	void SetTextAlignmentPoint(const VARIANT& newValue);
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	long GetTextGenerationFlag();
	void SetTextGenerationFlag(long nNewValue);
	double GetThickness();
	void SetThickness(double newValue);
	BOOL GetUpsideDown();
	void SetUpsideDown(BOOL bNewValue);
	BOOL GetBackward();
	void SetBackward(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadTolerance wrapper class

class IAcadTolerance : public COleDispatchDriver
{
public:
	IAcadTolerance() {}		// Calls COleDispatchDriver default constructor
	IAcadTolerance(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadTolerance(const IAcadTolerance& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetDirectionVector();
	void SetDirectionVector(const VARIANT& newValue);
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetTextString();
	void SetTextString(LPCTSTR lpszNewValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadTrace wrapper class

class IAcadTrace : public COleDispatchDriver
{
public:
	IAcadTrace() {}		// Calls COleDispatchDriver default constructor
	IAcadTrace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadTrace(const IAcadTrace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadXline wrapper class

class IAcadXline : public COleDispatchDriver
{
public:
	IAcadXline() {}		// Calls COleDispatchDriver default constructor
	IAcadXline(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadXline(const IAcadXline& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetBasePoint();
	void SetBasePoint(const VARIANT& newValue);
	VARIANT GetSecondPoint();
	void SetSecondPoint(const VARIANT& newValue);
	VARIANT GetDirectionVector();
	void SetDirectionVector(const VARIANT& newValue);
	VARIANT Offset(double Distance);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadBlockReference wrapper class

class IAcadBlockReference : public COleDispatchDriver
{
public:
	IAcadBlockReference() {}		// Calls COleDispatchDriver default constructor
	IAcadBlockReference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadBlockReference(const IAcadBlockReference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetXScaleFactor();
	void SetXScaleFactor(double newValue);
	double GetYScaleFactor();
	void SetYScaleFactor(double newValue);
	double GetZScaleFactor();
	void SetZScaleFactor(double newValue);
	VARIANT Explode();
	VARIANT GetAttributes();
	VARIANT GetConstantAttributes();
	BOOL GetHasAttributes();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadHatch wrapper class

class IAcadHatch : public COleDispatchDriver
{
public:
	IAcadHatch() {}		// Calls COleDispatchDriver default constructor
	IAcadHatch(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadHatch(const IAcadHatch& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	long GetNumberOfLoops();
	long GetPatternType();
	CString GetPatternName();
	double GetPatternAngle();
	void SetPatternAngle(double newValue);
	double GetPatternScale();
	void SetPatternScale(double newValue);
	double GetPatternSpace();
	void SetPatternSpace(double newValue);
	long GetISOPenWidth();
	void SetISOPenWidth(long nNewValue);
	BOOL GetPatternDouble();
	void SetPatternDouble(BOOL bNewValue);
	double GetElevation();
	void SetElevation(double newValue);
	BOOL GetAssociativeHatch();
	void SetAssociativeHatch(BOOL bNewValue);
	long GetHatchStyle();
	void SetHatchStyle(long nNewValue);
	void SetPattern(long PatternType, LPCTSTR PatternName);
	void AppendOuterLoop(const VARIANT& ObjectArray);
	void AppendInnerLoop(const VARIANT& ObjectArray);
	void InsertLoopAt(long Index, long LoopType, const VARIANT& ObjectArray);
	void GetLoopAt(long Index, VARIANT* ObjectArray);
	void Evaluate();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadRasterImage wrapper class

class IAcadRasterImage : public COleDispatchDriver
{
public:
	IAcadRasterImage() {}		// Calls COleDispatchDriver default constructor
	IAcadRasterImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadRasterImage(const IAcadRasterImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	long GetBrightness();
	void SetBrightness(long nNewValue);
	long GetContrast();
	void SetContrast(long nNewValue);
	long GetFade();
	void SetFade(long nNewValue);
	VARIANT GetOrigin();
	void SetOrigin(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetImageWidth();
	void SetImageWidth(double newValue);
	double GetImageHeight();
	void SetImageHeight(double newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void SetImageFile(LPCTSTR lpszNewValue);
	CString GetImageFile();
	BOOL GetImageVisibility();
	void SetImageVisibility(BOOL bNewValue);
	BOOL GetClippingEnabled();
	void SetClippingEnabled(BOOL bNewValue);
	BOOL GetTransparency();
	void SetTransparency(BOOL bNewValue);
	void ClipBoundary(const VARIANT& boundry);
	double GetHeight();
	double GetWidth();
	BOOL GetShowRotation();
	void SetShowRotation(BOOL bNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLine wrapper class

class IAcadLine : public COleDispatchDriver
{
public:
	IAcadLine() {}		// Calls COleDispatchDriver default constructor
	IAcadLine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLine(const IAcadLine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetStartPoint();
	void SetStartPoint(const VARIANT& newValue);
	VARIANT GetEndPoint();
	void SetEndPoint(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetThickness();
	void SetThickness(double newValue);
	VARIANT Offset(double Distance);
	VARIANT GetDelta();
	double GetLength();
	double GetAngle();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLayout wrapper class

class IAcadLayout : public COleDispatchDriver
{
public:
	IAcadLayout() {}		// Calls COleDispatchDriver default constructor
	IAcadLayout(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLayout(const IAcadLayout& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetConfigName();
	void SetConfigName(LPCTSTR lpszNewValue);
	CString GetCanonicalMediaName();
	void SetCanonicalMediaName(LPCTSTR lpszNewValue);
	long GetPaperUnits();
	void SetPaperUnits(long nNewValue);
	BOOL GetPlotViewportBorders();
	void SetPlotViewportBorders(BOOL bNewValue);
	BOOL GetShowPlotStyles();
	void SetShowPlotStyles(BOOL bNewValue);
	long GetPlotRotation();
	void SetPlotRotation(long nNewValue);
	BOOL GetCenterPlot();
	void SetCenterPlot(BOOL bNewValue);
	BOOL GetPlotHidden();
	void SetPlotHidden(BOOL bNewValue);
	long GetPlotType();
	void SetPlotType(long nNewValue);
	CString GetViewToPlot();
	void SetViewToPlot(LPCTSTR lpszNewValue);
	BOOL GetUseStandardScale();
	void SetUseStandardScale(BOOL bNewValue);
	long GetStandardScale();
	void SetStandardScale(long nNewValue);
	void GetCustomScale(double* Numerator, double* Denominator);
	void SetCustomScale(double Numerator, double Denominator);
	BOOL GetScaleLineweights();
	void SetScaleLineweights(BOOL bNewValue);
	BOOL GetPlotWithLineweights();
	void SetPlotWithLineweights(BOOL bNewValue);
	BOOL GetPlotViewportsFirst();
	void SetPlotViewportsFirst(BOOL bNewValue);
	CString GetStyleSheet();
	void SetStyleSheet(LPCTSTR lpszNewValue);
	void GetPaperMargins(VARIANT* LowerLeft, VARIANT* UpperRight);
	void GetPaperSize(double* Width, double* Height);
	VARIANT GetPlotOrigin();
	void SetPlotOrigin(const VARIANT& newValue);
	void GetWindowToPlot(VARIANT* LowerLeft, VARIANT* UpperRight);
	void SetWindowToPlot(const VARIANT& LowerLeft, const VARIANT& UpperRight);
	BOOL GetPlotWithPlotStyles();
	void SetPlotWithPlotStyles(BOOL bNewValue);
	BOOL GetModelType();
	void CopyFrom(LPDISPATCH pPlotConfig);
	VARIANT GetCanonicalMediaNames();
	VARIANT GetPlotDeviceNames();
	VARIANT GetPlotStyleTableNames();
	void RefreshPlotDeviceInfo();
	CString GetLocaleMediaName(LPCTSTR Name);
	LPDISPATCH GetBlock();
	long GetTabOrder();
	void SetTabOrder(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPlotConfiguration wrapper class

class IAcadPlotConfiguration : public COleDispatchDriver
{
public:
	IAcadPlotConfiguration() {}		// Calls COleDispatchDriver default constructor
	IAcadPlotConfiguration(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPlotConfiguration(const IAcadPlotConfiguration& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetConfigName();
	void SetConfigName(LPCTSTR lpszNewValue);
	CString GetCanonicalMediaName();
	void SetCanonicalMediaName(LPCTSTR lpszNewValue);
	long GetPaperUnits();
	void SetPaperUnits(long nNewValue);
	BOOL GetPlotViewportBorders();
	void SetPlotViewportBorders(BOOL bNewValue);
	BOOL GetShowPlotStyles();
	void SetShowPlotStyles(BOOL bNewValue);
	long GetPlotRotation();
	void SetPlotRotation(long nNewValue);
	BOOL GetCenterPlot();
	void SetCenterPlot(BOOL bNewValue);
	BOOL GetPlotHidden();
	void SetPlotHidden(BOOL bNewValue);
	long GetPlotType();
	void SetPlotType(long nNewValue);
	CString GetViewToPlot();
	void SetViewToPlot(LPCTSTR lpszNewValue);
	BOOL GetUseStandardScale();
	void SetUseStandardScale(BOOL bNewValue);
	long GetStandardScale();
	void SetStandardScale(long nNewValue);
	void GetCustomScale(double* Numerator, double* Denominator);
	void SetCustomScale(double Numerator, double Denominator);
	BOOL GetScaleLineweights();
	void SetScaleLineweights(BOOL bNewValue);
	BOOL GetPlotWithLineweights();
	void SetPlotWithLineweights(BOOL bNewValue);
	BOOL GetPlotViewportsFirst();
	void SetPlotViewportsFirst(BOOL bNewValue);
	CString GetStyleSheet();
	void SetStyleSheet(LPCTSTR lpszNewValue);
	void GetPaperMargins(VARIANT* LowerLeft, VARIANT* UpperRight);
	void GetPaperSize(double* Width, double* Height);
	VARIANT GetPlotOrigin();
	void SetPlotOrigin(const VARIANT& newValue);
	void GetWindowToPlot(VARIANT* LowerLeft, VARIANT* UpperRight);
	void SetWindowToPlot(const VARIANT& LowerLeft, const VARIANT& UpperRight);
	BOOL GetPlotWithPlotStyles();
	void SetPlotWithPlotStyles(BOOL bNewValue);
	BOOL GetModelType();
	void CopyFrom(LPDISPATCH pPlotConfig);
	VARIANT GetCanonicalMediaNames();
	VARIANT GetPlotDeviceNames();
	VARIANT GetPlotStyleTableNames();
	void RefreshPlotDeviceInfo();
	CString GetLocaleMediaName(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMInsertBlock wrapper class

class IAcadMInsertBlock : public COleDispatchDriver
{
public:
	IAcadMInsertBlock() {}		// Calls COleDispatchDriver default constructor
	IAcadMInsertBlock(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMInsertBlock(const IAcadMInsertBlock& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetXScaleFactor();
	void SetXScaleFactor(double newValue);
	double GetYScaleFactor();
	void SetYScaleFactor(double newValue);
	double GetZScaleFactor();
	void SetZScaleFactor(double newValue);
	VARIANT Explode();
	VARIANT GetAttributes();
	VARIANT GetConstantAttributes();
	BOOL GetHasAttributes();
	void SetColumns(long nNewValue);
	long GetColumns();
	void SetColumnSpacing(double newValue);
	double GetColumnSpacing();
	void SetRows(long nNewValue);
	long GetRows();
	void SetRowSpacing(double newValue);
	double GetRowSpacing();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPolyfaceMesh wrapper class

class IAcadPolyfaceMesh : public COleDispatchDriver
{
public:
	IAcadPolyfaceMesh() {}		// Calls COleDispatchDriver default constructor
	IAcadPolyfaceMesh(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPolyfaceMesh(const IAcadPolyfaceMesh& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	void SetCoordinates(const VARIANT& newValue);
	VARIANT GetCoordinates();
	VARIANT GetCoordinate(long Index);
	void SetCoordinate(long Index, const VARIANT& newValue);
	long GetNumberOfVertices();
	long GetNumberOfFaces();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMLine wrapper class

class IAcadMLine : public COleDispatchDriver
{
public:
	IAcadMLine() {}		// Calls COleDispatchDriver default constructor
	IAcadMLine(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMLine(const IAcadMLine& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	CString GetStyleName();
	VARIANT GetCoordinates();
	void SetCoordinates(const VARIANT& newValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDim3PointAngular wrapper class

class IAcadDim3PointAngular : public COleDispatchDriver
{
public:
	IAcadDim3PointAngular() {}		// Calls COleDispatchDriver default constructor
	IAcadDim3PointAngular(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDim3PointAngular(const IAcadDim3PointAngular& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	VARIANT GetTextPosition();
	void SetTextPosition(const VARIANT& newValue);
	double GetTextRotation();
	void SetTextRotation(double newValue);
	CString GetTextOverride();
	void SetTextOverride(LPCTSTR lpszNewValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	long GetTextColor();
	void SetTextColor(long nNewValue);
	CString GetDecimalSeparator();
	void SetDecimalSeparator(LPCTSTR lpszNewValue);
	double GetTextGap();
	void SetTextGap(double newValue);
	CString GetTextPrefix();
	void SetTextPrefix(LPCTSTR lpszNewValue);
	CString GetTextSuffix();
	void SetTextSuffix(LPCTSTR lpszNewValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	long GetVerticalTextPosition();
	void SetVerticalTextPosition(long nNewValue);
	long GetTolerancePrecision();
	void SetTolerancePrecision(long nNewValue);
	double GetToleranceHeightScale();
	void SetToleranceHeightScale(double newValue);
	double GetToleranceLowerLimit();
	void SetToleranceLowerLimit(double newValue);
	long GetTextMovement();
	void SetTextMovement(long nNewValue);
	long GetToleranceDisplay();
	void SetToleranceDisplay(long nNewValue);
	long GetToleranceJustification();
	void SetToleranceJustification(long nNewValue);
	double GetToleranceUpperLimit();
	void SetToleranceUpperLimit(double newValue);
	CString GetTextStyle();
	void SetTextStyle(LPCTSTR lpszNewValue);
	double GetTextHeight();
	void SetTextHeight(double newValue);
	BOOL GetSuppressLeadingZeros();
	void SetSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetSuppressTrailingZeros();
	void SetSuppressTrailingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressLeadingZeros();
	void SetToleranceSuppressLeadingZeros(BOOL bNewValue);
	BOOL GetToleranceSuppressTrailingZeros();
	void SetToleranceSuppressTrailingZeros(BOOL bNewValue);
	VARIANT GetExtLine1EndPoint();
	void SetExtLine1EndPoint(const VARIANT& newValue);
	VARIANT GetExtLine2EndPoint();
	void SetExtLine2EndPoint(const VARIANT& newValue);
	VARIANT GetAngleVertex();
	void SetAngleVertex(const VARIANT& newValue);
	long GetTextPrecision();
	void SetTextPrecision(long nNewValue);
	long GetAngleFormat();
	void SetAngleFormat(long nNewValue);
	long GetDimensionLineColor();
	void SetDimensionLineColor(long nNewValue);
	long GetExtensionLineColor();
	void SetExtensionLineColor(long nNewValue);
	double GetExtensionLineExtend();
	void SetExtensionLineExtend(double newValue);
	long GetFit();
	void SetFit(long nNewValue);
	long GetHorizontalTextPosition();
	void SetHorizontalTextPosition(long nNewValue);
	long GetExtensionLineWeight();
	void SetExtensionLineWeight(long nNewValue);
	BOOL GetDimLine1Suppress();
	void SetDimLine1Suppress(BOOL bNewValue);
	BOOL GetDimLine2Suppress();
	void SetDimLine2Suppress(BOOL bNewValue);
	BOOL GetExtLine1Suppress();
	void SetExtLine1Suppress(BOOL bNewValue);
	BOOL GetExtLine2Suppress();
	void SetExtLine2Suppress(BOOL bNewValue);
	BOOL GetDimLineInside();
	void SetDimLineInside(BOOL bNewValue);
	BOOL GetTextInsideAlign();
	void SetTextInsideAlign(BOOL bNewValue);
	BOOL GetTextInside();
	void SetTextInside(BOOL bNewValue);
	BOOL GetForceLineInside();
	void SetForceLineInside(BOOL bNewValue);
	BOOL GetTextOutsideAlign();
	void SetTextOutsideAlign(BOOL bNewValue);
	double GetExtensionLineOffset();
	void SetExtensionLineOffset(double newValue);
	long GetDimensionLineWeight();
	void SetDimensionLineWeight(long nNewValue);
	double GetArrowheadSize();
	void SetArrowheadSize(double newValue);
	long GetArrowhead1Type();
	void SetArrowhead1Type(long nNewValue);
	long GetArrowhead2Type();
	void SetArrowhead2Type(long nNewValue);
	double GetMeasurement();
	CString GetArrowhead1Block();
	void SetArrowhead1Block(LPCTSTR lpszNewValue);
	CString GetArrowhead2Block();
	void SetArrowhead2Block(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadExternalReference wrapper class

class IAcadExternalReference : public COleDispatchDriver
{
public:
	IAcadExternalReference() {}		// Calls COleDispatchDriver default constructor
	IAcadExternalReference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadExternalReference(const IAcadExternalReference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetXScaleFactor();
	void SetXScaleFactor(double newValue);
	double GetYScaleFactor();
	void SetYScaleFactor(double newValue);
	double GetZScaleFactor();
	void SetZScaleFactor(double newValue);
	VARIANT Explode();
	VARIANT GetAttributes();
	VARIANT GetConstantAttributes();
	BOOL GetHasAttributes();
	CString GetPath();
	void SetPath(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPaperSpace wrapper class

class IAcadPaperSpace : public COleDispatchDriver
{
public:
	IAcadPaperSpace() {}		// Calls COleDispatchDriver default constructor
	IAcadPaperSpace(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPaperSpace(const IAcadPaperSpace& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetOrigin();
	void SetOrigin(const VARIANT& newValue);
	LPDISPATCH AddCustomObject(LPCTSTR ClassName);
	LPDISPATCH Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH Add3DMesh(long M, long N, const VARIANT& PointsMatrix);
	LPDISPATCH Add3DPoly(const VARIANT& PointsArray);
	LPDISPATCH AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle);
	LPDISPATCH AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value);
	LPDISPATCH AddBox(const VARIANT& Origin, double Length, double Width, double Height);
	LPDISPATCH AddCircle(const VARIANT& Center, double Radius);
	LPDISPATCH AddCone(const VARIANT& Center, double BaseRadius, double Height);
	LPDISPATCH AddCylinder(const VARIANT& Center, double Radius, double Height);
	LPDISPATCH AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition);
	LPDISPATCH AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength);
	LPDISPATCH AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle);
	LPDISPATCH AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis);
	LPDISPATCH AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength);
	LPDISPATCH AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio);
	LPDISPATCH AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height);
	LPDISPATCH AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle);
	LPDISPATCH AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path);
	LPDISPATCH AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type);
	LPDISPATCH AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text);
	LPDISPATCH AddPoint(const VARIANT& Point);
	LPDISPATCH AddLightWeightPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddPolyline(const VARIANT& VerticesList);
	LPDISPATCH AddRay(const VARIANT& Point1, const VARIANT& Point2);
	VARIANT AddRegion(const VARIANT& ObjectList);
	LPDISPATCH AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle);
	LPDISPATCH AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4);
	LPDISPATCH AddSphere(const VARIANT& Center, double Radius);
	LPDISPATCH AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent);
	LPDISPATCH AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height);
	LPDISPATCH AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction);
	LPDISPATCH AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius);
	LPDISPATCH AddTrace(const VARIANT& PointsArray);
	LPDISPATCH AddWedge(const VARIANT& Center, double Length, double Width, double Height);
	LPDISPATCH AddXline(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation);
	LPDISPATCH AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity);
	LPDISPATCH AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle);
	LPDISPATCH AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint);
	BOOL GetIsLayout();
	LPDISPATCH GetLayout();
	BOOL GetIsXRef();
	LPDISPATCH AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing);
	LPDISPATCH AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList);
	LPDISPATCH AddMLine(const VARIANT& VertexList);
	LPDISPATCH AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint);
	LPDISPATCH GetXRefDatabase();
	LPDISPATCH AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay);
	void Unload();
	void Reload();
	void Bind(BOOL bPrefixName);
	void Detach();
	LPDISPATCH AddPViewport(const VARIANT& Center, double Width, double Height);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPViewport wrapper class

class IAcadPViewport : public COleDispatchDriver
{
public:
	IAcadPViewport() {}		// Calls COleDispatchDriver default constructor
	IAcadPViewport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPViewport(const IAcadPViewport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	VARIANT GetCenter();
	void SetCenter(const VARIANT& newValue);
	VARIANT GetDirection();
	void SetDirection(const VARIANT& newValue);
	BOOL GetGridOn();
	void SetGridOn(BOOL bNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	BOOL GetViewportOn();
	void SetViewportOn(BOOL bNewValue);
	BOOL GetClipped();
	BOOL GetDisplayLocked();
	void SetDisplayLocked(BOOL bNewValue);
	long GetStandardScale();
	void SetStandardScale(long nNewValue);
	double GetCustomScale();
	void SetCustomScale(double newValue);
	BOOL GetUCSPerViewport();
	void SetUCSPerViewport(BOOL bNewValue);
	VARIANT GetSnapBasePoint();
	void SetSnapBasePoint(const VARIANT& newValue);
	BOOL GetSnapOn();
	void SetSnapOn(BOOL bNewValue);
	double GetSnapRotationAngle();
	void SetSnapRotationAngle(double newValue);
	BOOL GetUCSIconOn();
	void SetUCSIconOn(BOOL bNewValue);
	BOOL GetUCSIconAtOrigin();
	void SetUCSIconAtOrigin(BOOL bNewValue);
	void GetGridSpacing(double* XSpacing, double* YSpacing);
	void SetGridSpacing(double XSpacing, double YSpacing);
	void GetSnapSpacing(double* XSpacing, double* YSpacing);
	void SetSnapSpacing(double XSpacing, double YSpacing);
	void Display(BOOL bStatus);
	double GetTwistAngle();
	void SetTwistAngle(double newValue);
	double GetLensLength();
	void SetLensLength(double newValue);
	BOOL GetRemoveHiddenLines();
	void SetRemoveHiddenLines(BOOL bNewValue);
	VARIANT GetTarget();
	void SetTarget(const VARIANT& newValue);
	long GetArcSmoothness();
	void SetArcSmoothness(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadBlocks wrapper class

class IAcadBlocks : public COleDispatchDriver
{
public:
	IAcadBlocks() {}		// Calls COleDispatchDriver default constructor
	IAcadBlocks(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadBlocks(const IAcadBlocks& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(const VARIANT& InsertionPoint, LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadGroups wrapper class

class IAcadGroups : public COleDispatchDriver
{
public:
	IAcadGroups() {}		// Calls COleDispatchDriver default constructor
	IAcadGroups(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadGroups(const IAcadGroups& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadGroup wrapper class

class IAcadGroup : public COleDispatchDriver
{
public:
	IAcadGroup() {}		// Calls COleDispatchDriver default constructor
	IAcadGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadGroup(const IAcadGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	void SetColor(long nNewValue);
	void SetLayer(LPCTSTR lpszNewValue);
	void SetLinetype(LPCTSTR lpszNewValue);
	void SetLinetypeScale(double newValue);
	void SetVisible(BOOL bNewValue);
	void Highlight(BOOL HighlightFlag);
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	void SetLineweight(long nNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void AppendItems(const VARIANT& Objects);
	void RemoveItems(const VARIANT& Objects);
	void Update();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimStyles wrapper class

class IAcadDimStyles : public COleDispatchDriver
{
public:
	IAcadDimStyles() {}		// Calls COleDispatchDriver default constructor
	IAcadDimStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimStyles(const IAcadDimStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDimStyle wrapper class

class IAcadDimStyle : public COleDispatchDriver
{
public:
	IAcadDimStyle() {}		// Calls COleDispatchDriver default constructor
	IAcadDimStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDimStyle(const IAcadDimStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void CopyFrom(LPDISPATCH StyleSource);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLayers wrapper class

class IAcadLayers : public COleDispatchDriver
{
public:
	IAcadLayers() {}		// Calls COleDispatchDriver default constructor
	IAcadLayers(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLayers(const IAcadLayers& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLayer wrapper class

class IAcadLayer : public COleDispatchDriver
{
public:
	IAcadLayer() {}		// Calls COleDispatchDriver default constructor
	IAcadLayer(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLayer(const IAcadLayer& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	BOOL GetFreeze();
	void SetFreeze(BOOL bNewValue);
	BOOL GetLayerOn();
	void SetLayerOn(BOOL bNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	BOOL GetLock();
	void SetLock(BOOL bNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetPlottable();
	void SetPlottable(BOOL bNewValue);
	BOOL GetViewportDefault();
	void SetViewportDefault(BOOL bNewValue);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLineTypes wrapper class

class IAcadLineTypes : public COleDispatchDriver
{
public:
	IAcadLineTypes() {}		// Calls COleDispatchDriver default constructor
	IAcadLineTypes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLineTypes(const IAcadLineTypes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
	void Load(LPCTSTR Name, LPCTSTR FileName);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLineType wrapper class

class IAcadLineType : public COleDispatchDriver
{
public:
	IAcadLineType() {}		// Calls COleDispatchDriver default constructor
	IAcadLineType(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLineType(const IAcadLineType& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDictionaries wrapper class

class IAcadDictionaries : public COleDispatchDriver
{
public:
	IAcadDictionaries() {}		// Calls COleDispatchDriver default constructor
	IAcadDictionaries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDictionaries(const IAcadDictionaries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDictionary wrapper class

class IAcadDictionary : public COleDispatchDriver
{
public:
	IAcadDictionary() {}		// Calls COleDispatchDriver default constructor
	IAcadDictionary(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDictionary(const IAcadDictionary& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	LPDISPATCH AddObject(LPCTSTR Keyword, LPCTSTR ObjectName);
	CString GetName(LPDISPATCH Object);
	LPDISPATCH GetObject(LPCTSTR Name);
	LPDISPATCH Remove(LPCTSTR Name);
	void Rename(LPCTSTR OldName, LPCTSTR NewName);
	void Replace(LPCTSTR OldName, LPDISPATCH pObj);
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH AddXRecord(LPCTSTR Keyword);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadXRecord wrapper class

class IAcadXRecord : public COleDispatchDriver
{
public:
	IAcadXRecord() {}		// Calls COleDispatchDriver default constructor
	IAcadXRecord(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadXRecord(const IAcadXRecord& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	void GetXRecordData(VARIANT* XRecordDataType, VARIANT* XRecordDataValue);
	void SetXRecordData(const VARIANT& XRecordDataType, const VARIANT& XRecordDataValue);
	BOOL GetTranslateIDs();
	void SetTranslateIDs(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadRegisteredApplications wrapper class

class IAcadRegisteredApplications : public COleDispatchDriver
{
public:
	IAcadRegisteredApplications() {}		// Calls COleDispatchDriver default constructor
	IAcadRegisteredApplications(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadRegisteredApplications(const IAcadRegisteredApplications& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadRegisteredApplication wrapper class

class IAcadRegisteredApplication : public COleDispatchDriver
{
public:
	IAcadRegisteredApplication() {}		// Calls COleDispatchDriver default constructor
	IAcadRegisteredApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadRegisteredApplication(const IAcadRegisteredApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadTextStyles wrapper class

class IAcadTextStyles : public COleDispatchDriver
{
public:
	IAcadTextStyles() {}		// Calls COleDispatchDriver default constructor
	IAcadTextStyles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadTextStyles(const IAcadTextStyles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadTextStyle wrapper class

class IAcadTextStyle : public COleDispatchDriver
{
public:
	IAcadTextStyle() {}		// Calls COleDispatchDriver default constructor
	IAcadTextStyle(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadTextStyle(const IAcadTextStyle& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetBigFontFile();
	void SetBigFontFile(LPCTSTR lpszNewValue);
	CString GetFontFile();
	void SetFontFile(LPCTSTR lpszNewValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetLastHeight();
	void SetLastHeight(double newValue);
	CString GetName();
	double GetObliqueAngle();
	void SetObliqueAngle(double newValue);
	long GetTextGenerationFlag();
	void SetTextGenerationFlag(long nNewValue);
	double GetWidth();
	void SetWidth(double newValue);
	void GetFont(BSTR* TypeFace, BOOL* Bold, BOOL* Italic, long* Charset, long* PitchAndFamily);
	void SetFont(LPCTSTR TypeFace, BOOL Bold, BOOL Italic, long Charset, long PitchAndFamily);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadUCSs wrapper class

class IAcadUCSs : public COleDispatchDriver
{
public:
	IAcadUCSs() {}		// Calls COleDispatchDriver default constructor
	IAcadUCSs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadUCSs(const IAcadUCSs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(const VARIANT& Origin, const VARIANT& XAxisPoint, const VARIANT& YAxisPoint, LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadUCS wrapper class

class IAcadUCS : public COleDispatchDriver
{
public:
	IAcadUCS() {}		// Calls COleDispatchDriver default constructor
	IAcadUCS(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadUCS(const IAcadUCS& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	VARIANT GetOrigin();
	void SetOrigin(const VARIANT& newValue);
	VARIANT GetXVector();
	void SetXVector(const VARIANT& newValue);
	VARIANT GetYVector();
	void SetYVector(const VARIANT& newValue);
	VARIANT GetUCSMatrix();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadViews wrapper class

class IAcadViews : public COleDispatchDriver
{
public:
	IAcadViews() {}		// Calls COleDispatchDriver default constructor
	IAcadViews(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadViews(const IAcadViews& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadView wrapper class

class IAcadView : public COleDispatchDriver
{
public:
	IAcadView() {}		// Calls COleDispatchDriver default constructor
	IAcadView(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadView(const IAcadView& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	VARIANT GetCenter();
	void SetCenter(const VARIANT& newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	VARIANT GetTarget();
	void SetTarget(const VARIANT& newValue);
	VARIANT GetDirection();
	void SetDirection(const VARIANT& newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadViewports wrapper class

class IAcadViewports : public COleDispatchDriver
{
public:
	IAcadViewports() {}		// Calls COleDispatchDriver default constructor
	IAcadViewports(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadViewports(const IAcadViewports& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
	void DeleteConfiguration(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadViewport wrapper class

class IAcadViewport : public COleDispatchDriver
{
public:
	IAcadViewport() {}		// Calls COleDispatchDriver default constructor
	IAcadViewport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadViewport(const IAcadViewport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	VARIANT GetCenter();
	void SetCenter(const VARIANT& newValue);
	double GetHeight();
	void SetHeight(double newValue);
	double GetWidth();
	void SetWidth(double newValue);
	VARIANT GetTarget();
	void SetTarget(const VARIANT& newValue);
	VARIANT GetDirection();
	void SetDirection(const VARIANT& newValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetGridOn();
	void SetGridOn(BOOL bNewValue);
	BOOL GetOrthoOn();
	void SetOrthoOn(BOOL bNewValue);
	VARIANT GetSnapBasePoint();
	void SetSnapBasePoint(const VARIANT& newValue);
	BOOL GetSnapOn();
	void SetSnapOn(BOOL bNewValue);
	double GetSnapRotationAngle();
	void SetSnapRotationAngle(double newValue);
	BOOL GetUCSIconOn();
	void SetUCSIconOn(BOOL bNewValue);
	BOOL GetUCSIconAtOrigin();
	void SetUCSIconAtOrigin(BOOL bNewValue);
	VARIANT GetLowerLeftCorner();
	VARIANT GetUpperRightCorner();
	void Split(long NumWins);
	void GetGridSpacing(double* XSpacing, double* YSpacing);
	void SetGridSpacing(double XSpacing, double YSpacing);
	void GetSnapSpacing(double* XSpacing, double* YSpacing);
	void SetSnapSpacing(double XSpacing, double YSpacing);
	void SetView(LPDISPATCH View);
	long GetArcSmoothness();
	void SetArcSmoothness(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLayouts wrapper class

class IAcadLayouts : public COleDispatchDriver
{
public:
	IAcadLayouts() {}		// Calls COleDispatchDriver default constructor
	IAcadLayouts(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLayouts(const IAcadLayouts& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPlotConfigurations wrapper class

class IAcadPlotConfigurations : public COleDispatchDriver
{
public:
	IAcadPlotConfigurations() {}		// Calls COleDispatchDriver default constructor
	IAcadPlotConfigurations(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPlotConfigurations(const IAcadPlotConfigurations& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH Add(LPCTSTR Name, const VARIANT& ModelType);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDatabasePreferences wrapper class

class IAcadDatabasePreferences : public COleDispatchDriver
{
public:
	IAcadDatabasePreferences() {}		// Calls COleDispatchDriver default constructor
	IAcadDatabasePreferences(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDatabasePreferences(const IAcadDatabasePreferences& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	BOOL GetSolidFill();
	void SetSolidFill(BOOL bNewValue);
	BOOL GetXRefEdit();
	void SetXRefEdit(BOOL bNewValue);
	BOOL GetXRefLayerVisibility();
	void SetXRefLayerVisibility(BOOL bNewValue);
	BOOL GetOLELaunch();
	void SetOLELaunch(BOOL bNewValue);
	BOOL GetAllowLongSymbolNames();
	void SetAllowLongSymbolNames(BOOL bNewValue);
	BOOL GetObjectSortBySelection();
	void SetObjectSortBySelection(BOOL bNewValue);
	BOOL GetObjectSortBySnap();
	void SetObjectSortBySnap(BOOL bNewValue);
	BOOL GetObjectSortByRedraws();
	void SetObjectSortByRedraws(BOOL bNewValue);
	BOOL GetObjectSortByRegens();
	void SetObjectSortByRegens(BOOL bNewValue);
	BOOL GetObjectSortByPlotting();
	void SetObjectSortByPlotting(BOOL bNewValue);
	BOOL GetObjectSortByPSOutput();
	void SetObjectSortByPSOutput(BOOL bNewValue);
	void SetContourLinesPerSurface(long nNewValue);
	long GetContourLinesPerSurface();
	void SetDisplaySilhouette(BOOL bNewValue);
	BOOL GetDisplaySilhouette();
	void SetMaxActiveViewports(long nNewValue);
	long GetMaxActiveViewports();
	void SetRenderSmoothness(double newValue);
	double GetRenderSmoothness();
	void SetSegmentPerPolyline(long nNewValue);
	long GetSegmentPerPolyline();
	void SetTextFrameDisplay(BOOL bNewValue);
	BOOL GetTextFrameDisplay();
	void SetLineweight(long nNewValue);
	long GetLineweight();
	void SetLineWeightDisplay(BOOL bNewValue);
	BOOL GetLineWeightDisplay();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadIdPair wrapper class

class IAcadIdPair : public COleDispatchDriver
{
public:
	IAcadIdPair() {}		// Calls COleDispatchDriver default constructor
	IAcadIdPair(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadIdPair(const IAcadIdPair& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIsCloned();
	BOOL GetIsOwnerXlated();
	BOOL GetIsPrimary();
	long GetKey();
	long GetValue();
	LPDISPATCH GetApplication();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadAttributeReference wrapper class

class IAcadAttributeReference : public COleDispatchDriver
{
public:
	IAcadAttributeReference() {}		// Calls COleDispatchDriver default constructor
	IAcadAttributeReference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadAttributeReference(const IAcadAttributeReference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetHandle();
	CString GetObjectName();
	void GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue);
	void SetXData(const VARIANT& XDataType, const VARIANT& XDataValue);
	void Delete();
	long GetObjectID();
	LPDISPATCH GetApplication();
	BOOL GetHasExtensionDictionary();
	LPDISPATCH GetExtensionDictionary();
	long GetOwnerID();
	LPDISPATCH GetDocument();
	long GetColor();
	void SetColor(long nNewValue);
	CString GetLayer();
	void SetLayer(LPCTSTR lpszNewValue);
	CString GetLinetype();
	void SetLinetype(LPCTSTR lpszNewValue);
	double GetLinetypeScale();
	void SetLinetypeScale(double newValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	VARIANT ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint);
	VARIANT ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels);
	void Highlight(BOOL HighlightFlag);
	LPDISPATCH Copy();
	void Move(const VARIANT& FromPoint, const VARIANT& ToPoint);
	void Rotate(const VARIANT& BasePoint, double RotationAngle);
	void Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle);
	LPDISPATCH Mirror(const VARIANT& Point1, const VARIANT& Point2);
	LPDISPATCH Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3);
	void ScaleEntity(const VARIANT& BasePoint, double ScaleFactor);
	void TransformBy(const VARIANT& TransformationMatrix);
	void Update();
	void GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint);
	VARIANT IntersectWith(LPDISPATCH IntersectObject, long option);
	CString GetPlotStyleName();
	void SetPlotStyleName(LPCTSTR lpszNewValue);
	long GetLineweight();
	void SetLineweight(long nNewValue);
	LPDISPATCH GetHyperlinks();
	double GetHeight();
	void SetHeight(double newValue);
	VARIANT GetInsertionPoint();
	void SetInsertionPoint(const VARIANT& newValue);
	VARIANT GetNormal();
	void SetNormal(const VARIANT& newValue);
	double GetObliqueAngle();
	void SetObliqueAngle(double newValue);
	double GetRotation();
	void SetRotation(double newValue);
	double GetScaleFactor();
	void SetScaleFactor(double newValue);
	CString GetStyleName();
	void SetStyleName(LPCTSTR lpszNewValue);
	CString GetTagString();
	void SetTagString(LPCTSTR lpszNewValue);
	VARIANT GetTextAlignmentPoint();
	void SetTextAlignmentPoint(const VARIANT& newValue);
	long GetTextGenerationFlag();
	void SetTextGenerationFlag(long nNewValue);
	CString GetTextString();
	void SetTextString(LPCTSTR lpszNewValue);
	double GetThickness();
	void SetThickness(double newValue);
	long GetFieldLength();
	void SetFieldLength(long nNewValue);
	long GetAlignment();
	void SetAlignment(long nNewValue);
	BOOL GetUpsideDown();
	void SetUpsideDown(BOOL bNewValue);
	BOOL GetBackward();
	void SetBackward(BOOL bNewValue);
	BOOL GetInvisible();
	void SetInvisible(BOOL bNewValue);
	BOOL GetConstant();
};
/////////////////////////////////////////////////////////////////////////////
// _DAcadApplicationEvents wrapper class

class _DAcadApplicationEvents : public COleDispatchDriver
{
public:
	_DAcadApplicationEvents() {}		// Calls COleDispatchDriver default constructor
	_DAcadApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DAcadApplicationEvents(const _DAcadApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'SysVarChanged' not emitted because of invalid return type or parameter type
	// method 'NewDrawing' not emitted because of invalid return type or parameter type
	// method 'AppActivate' not emitted because of invalid return type or parameter type
	// method 'AppDeactivate' not emitted because of invalid return type or parameter type
	// method 'WindowMovedOrResized' not emitted because of invalid return type or parameter type
	// method 'BeginModal' not emitted because of invalid return type or parameter type
	// method 'EndModal' not emitted because of invalid return type or parameter type
	// method 'BeginQuit' not emitted because of invalid return type or parameter type
	// method 'BeginFileDrop' not emitted because of invalid return type or parameter type
	// method 'ARXLoaded' not emitted because of invalid return type or parameter type
	// method 'ARXUnloaded' not emitted because of invalid return type or parameter type
	// method 'BeginPlot' not emitted because of invalid return type or parameter type
	// method 'EndPlot' not emitted because of invalid return type or parameter type
	// method 'BeginSave' not emitted because of invalid return type or parameter type
	// method 'EndSave' not emitted because of invalid return type or parameter type
	// method 'BeginOpen' not emitted because of invalid return type or parameter type
	// method 'EndOpen' not emitted because of invalid return type or parameter type
	// method 'BeginCommand' not emitted because of invalid return type or parameter type
	// method 'EndCommand' not emitted because of invalid return type or parameter type
	// method 'BeginLisp' not emitted because of invalid return type or parameter type
	// method 'EndLisp' not emitted because of invalid return type or parameter type
	// method 'LispCancelled' not emitted because of invalid return type or parameter type
	// method 'WindowChanged' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDocument wrapper class

class IAcadDocument : public COleDispatchDriver
{
public:
	IAcadDocument() {}		// Calls COleDispatchDriver default constructor
	IAcadDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDocument(const IAcadDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetModelSpace();
	LPDISPATCH GetPaperSpace();
	LPDISPATCH GetBlocks();
	VARIANT CopyObjects(const VARIANT& Objects, const VARIANT& Owner, VARIANT* IdPairs);
	LPDISPATCH GetGroups();
	LPDISPATCH GetDimStyles();
	LPDISPATCH GetLayers();
	LPDISPATCH GetLinetypes();
	LPDISPATCH GetDictionaries();
	LPDISPATCH GetRegisteredApplications();
	LPDISPATCH GetTextStyles();
	LPDISPATCH GetUserCoordinateSystems();
	LPDISPATCH GetViews();
	LPDISPATCH GetViewports();
	double GetElevationModelSpace();
	void SetElevationModelSpace(double newValue);
	double GetElevationPaperSpace();
	void SetElevationPaperSpace(double newValue);
	VARIANT GetLimits();
	void SetLimits(const VARIANT& newValue);
	LPDISPATCH HandleToObject(LPCTSTR Handle);
	LPDISPATCH ObjectIdToObject(long ObjectID);
	LPDISPATCH GetLayouts();
	LPDISPATCH GetPlotConfigurations();
	LPDISPATCH GetPreferences();
	LPDISPATCH GetPlot();
	LPDISPATCH GetActiveLayer();
	void SetActiveLayer(LPDISPATCH newValue);
	LPDISPATCH GetActiveLinetype();
	void SetActiveLinetype(LPDISPATCH newValue);
	LPDISPATCH GetActiveDimStyle();
	void SetActiveDimStyle(LPDISPATCH newValue);
	LPDISPATCH GetActiveTextStyle();
	void SetActiveTextStyle(LPDISPATCH newValue);
	LPDISPATCH GetActiveUCS();
	void SetActiveUCS(LPDISPATCH newValue);
	LPDISPATCH GetActiveViewport();
	void SetActiveViewport(LPDISPATCH newValue);
	LPDISPATCH GetActivePViewport();
	void SetActivePViewport(LPDISPATCH newValue);
	long GetActiveSpace();
	void SetActiveSpace(long nNewValue);
	LPDISPATCH GetSelectionSets();
	LPDISPATCH GetActiveSelectionSet();
	CString GetFullName();
	CString GetName();
	CString GetPath();
	BOOL GetObjectSnapMode();
	void SetObjectSnapMode(BOOL bNewValue);
	BOOL GetReadOnly();
	BOOL GetSaved();
	BOOL GetMSpace();
	void SetMSpace(BOOL bNewValue);
	LPDISPATCH GetUtility();
	LPDISPATCH Open(LPCTSTR FullName);
	void AuditInfo(BOOL FixErr);
	LPDISPATCH Import(LPCTSTR FileName, const VARIANT& InsertionPoint, double ScaleFactor);
	void Export(LPCTSTR FileName, LPCTSTR Extension, LPDISPATCH SelectionSet);
	LPDISPATCH New(LPCTSTR TemplateFileName);
	void Save();
	void SaveAs(LPCTSTR FullFileName, const VARIANT& SaveAsType);
	void Wblock(LPCTSTR FileName, LPDISPATCH SelectionSet);
	void PurgeAll();
	VARIANT GetVariable(LPCTSTR Name);
	void SetVariable(LPCTSTR Name, const VARIANT& Value);
	void LoadShapeFile(LPCTSTR FullName);
	void Regen(long WhichViewports);
	LPDISPATCH GetPickfirstSelectionSet();
	BOOL GetActive();
	void Activate();
	void Close(const VARIANT& SaveChanges, const VARIANT& FileName);
	void SetWindowState(long nNewValue);
	long GetWindowState();
	void SetWidth(long nNewValue);
	long GetWidth();
	void SetHeight(long nNewValue);
	long GetHeight();
	void SetActiveLayout(LPDISPATCH newValue);
	LPDISPATCH GetActiveLayout();
	void SendCommand(LPCTSTR Command);
	long GetHwnd();
	CString GetWindowTitle();
	LPDISPATCH GetApplication();
	LPDISPATCH GetDatabase();
	void StartUndoMark();
	void EndUndoMark();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPlot wrapper class

class IAcadPlot : public COleDispatchDriver
{
public:
	IAcadPlot() {}		// Calls COleDispatchDriver default constructor
	IAcadPlot(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPlot(const IAcadPlot& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	BOOL GetQuietErrorMode();
	void SetQuietErrorMode(BOOL bNewValue);
	long GetNumberOfCopies();
	void SetNumberOfCopies(long nNewValue);
	BOOL GetBatchPlotProgress();
	void SetBatchPlotProgress(BOOL bNewValue);
	void DisplayPlotPreview(long Preview);
	BOOL PlotToFile(LPCTSTR plotFile, const VARIANT& plotConfig);
	BOOL PlotToDevice(const VARIANT& plotConfig);
	void SetLayoutsToPlot(const VARIANT& layoutList);
	void StartBatchMode(long entryCount);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadApplication wrapper class

class IAcadApplication : public COleDispatchDriver
{
public:
	IAcadApplication() {}		// Calls COleDispatchDriver default constructor
	IAcadApplication(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadApplication(const IAcadApplication& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	CString GetName();
	CString GetCaption();
	LPDISPATCH GetApplication();
	LPDISPATCH GetActiveDocument();
	void SetActiveDocument(LPDISPATCH newValue);
	CString GetFullName();
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetWindowLeft();
	void SetWindowLeft(long nNewValue);
	CString GetPath();
	long GetLocaleId();
	long GetWindowTop();
	void SetWindowTop(long nNewValue);
	CString GetVersion();
	long GetWidth();
	void SetWidth(long nNewValue);
	LPDISPATCH GetPreferences();
	BOOL GetStatusId(LPDISPATCH VportObj);
	VARIANT ListArx();
	void LoadArx(LPCTSTR Name);
	LPDISPATCH GetInterfaceObject(LPCTSTR ProgID);
	void UnloadArx(LPCTSTR Name);
	void Update();
	void Quit();
	LPDISPATCH GetVbe();
	LPDISPATCH GetMenuGroups();
	LPDISPATCH GetMenuBar();
	void LoadDVB(LPCTSTR Name);
	void UnloadDVB(LPCTSTR Name);
	LPDISPATCH GetDocuments();
	void Eval(LPCTSTR Expression);
	long GetWindowState();
	void SetWindowState(long nNewValue);
	void RunMacro(LPCTSTR MacroPath);
	void ZoomExtents();
	void ZoomAll();
	void ZoomCenter(const VARIANT& Center, double Magnify);
	void ZoomScaled(double scale, long ScaleType);
	void ZoomWindow(const VARIANT& LowerLeft, const VARIANT& UpperRight);
	void ZoomPickWindow();
	LPDISPATCH GetAcadState();
	void ZoomPrevious();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferences wrapper class

class IAcadPreferences : public COleDispatchDriver
{
public:
	IAcadPreferences() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferences(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferences(const IAcadPreferences& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetFiles();
	LPDISPATCH GetDisplay();
	LPDISPATCH GetOpenSave();
	LPDISPATCH GetOutput();
	LPDISPATCH GetSystem();
	LPDISPATCH GetUser();
	LPDISPATCH GetDrafting();
	LPDISPATCH GetSelection();
	LPDISPATCH GetProfiles();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesFiles wrapper class

class IAcadPreferencesFiles : public COleDispatchDriver
{
public:
	IAcadPreferencesFiles() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesFiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesFiles(const IAcadPreferencesFiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetSupportPath(LPCTSTR lpszNewValue);
	CString GetSupportPath();
	void SetDriversPath(LPCTSTR lpszNewValue);
	CString GetDriversPath();
	void SetMenuFile(LPCTSTR lpszNewValue);
	CString GetMenuFile();
	void SetHelpFilePath(LPCTSTR lpszNewValue);
	CString GetHelpFilePath();
	void SetDefaultInternetURL(LPCTSTR lpszNewValue);
	CString GetDefaultInternetURL();
	CString GetConfigFile();
	CString GetLicenseServer();
	void SetTextEditor(LPCTSTR lpszNewValue);
	CString GetTextEditor();
	void SetMainDictionary(LPCTSTR lpszNewValue);
	CString GetMainDictionary();
	void SetCustomDictionary(LPCTSTR lpszNewValue);
	CString GetCustomDictionary();
	void SetAltFontFile(LPCTSTR lpszNewValue);
	CString GetAltFontFile();
	void SetFontFileMap(LPCTSTR lpszNewValue);
	CString GetFontFileMap();
	void SetPrintFile(LPCTSTR lpszNewValue);
	CString GetPrintFile();
	void SetPrintSpoolExecutable(LPCTSTR lpszNewValue);
	CString GetPrintSpoolExecutable();
	void SetPostScriptPrologFile(LPCTSTR lpszNewValue);
	CString GetPostScriptPrologFile();
	void SetPrintSpoolerPath(LPCTSTR lpszNewValue);
	CString GetPrintSpoolerPath();
	void SetAutoSavePath(LPCTSTR lpszNewValue);
	CString GetAutoSavePath();
	void SetTemplateDwgPath(LPCTSTR lpszNewValue);
	CString GetTemplateDwgPath();
	void SetLogFilePath(LPCTSTR lpszNewValue);
	CString GetLogFilePath();
	void SetTempFilePath(LPCTSTR lpszNewValue);
	CString GetTempFilePath();
	void SetTempXrefPath(LPCTSTR lpszNewValue);
	CString GetTempXrefPath();
	void SetTextureMapPath(LPCTSTR lpszNewValue);
	CString GetTextureMapPath();
	void SetAltTabletMenuFile(LPCTSTR lpszNewValue);
	CString GetAltTabletMenuFile();
	void SetProjectFilePath(LPCTSTR ProjectName, LPCTSTR ProjectFilePath);
	CString GetProjectFilePath(LPCTSTR ProjectName);
	void SetPrinterConfigPath(LPCTSTR lpszNewValue);
	CString GetPrinterConfigPath();
	void SetPrinterDescPath(LPCTSTR lpszNewValue);
	CString GetPrinterDescPath();
	void SetPrinterStyleSheetPath(LPCTSTR lpszNewValue);
	CString GetPrinterStyleSheetPath();
	void SetWorkspacePath(LPCTSTR lpszNewValue);
	CString GetWorkspacePath();
	void SetObjectARXPath(LPCTSTR lpszNewValue);
	CString GetObjectARXPath();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesDisplay wrapper class

class IAcadPreferencesDisplay : public COleDispatchDriver
{
public:
	IAcadPreferencesDisplay() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesDisplay(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesDisplay(const IAcadPreferencesDisplay& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetLayoutDisplayMargins(BOOL bNewValue);
	BOOL GetLayoutDisplayMargins();
	void SetLayoutDisplayPaper(BOOL bNewValue);
	BOOL GetLayoutDisplayPaper();
	void SetLayoutDisplayPaperShadow(BOOL bNewValue);
	BOOL GetLayoutDisplayPaperShadow();
	void SetLayoutShowPlotSetup(BOOL bNewValue);
	BOOL GetLayoutShowPlotSetup();
	void SetLayoutCreateViewport(BOOL bNewValue);
	BOOL GetLayoutCreateViewport();
	void SetDisplayScrollBars(BOOL bNewValue);
	BOOL GetDisplayScrollBars();
	void SetDisplayScreenMenu(BOOL bNewValue);
	BOOL GetDisplayScreenMenu();
	void SetCursorSize(long nNewValue);
	long GetCursorSize();
	void SetDockedVisibleLines(long nNewValue);
	long GetDockedVisibleLines();
	void SetShowRasterImage(BOOL bNewValue);
	BOOL GetShowRasterImage();
	void SetGraphicsWinModelBackgrndColor(unsigned long newValue);
	unsigned long GetGraphicsWinModelBackgrndColor();
	void SetModelCrosshairColor(unsigned long newValue);
	unsigned long GetModelCrosshairColor();
	void SetGraphicsWinLayoutBackgrndColor(unsigned long newValue);
	unsigned long GetGraphicsWinLayoutBackgrndColor();
	void SetTextWinBackgrndColor(unsigned long newValue);
	unsigned long GetTextWinBackgrndColor();
	void SetTextWinTextColor(unsigned long newValue);
	unsigned long GetTextWinTextColor();
	void SetLayoutCrosshairColor(unsigned long newValue);
	unsigned long GetLayoutCrosshairColor();
	void SetAutoTrackingVecColor(unsigned long newValue);
	unsigned long GetAutoTrackingVecColor();
	void SetTextFont(LPCTSTR lpszNewValue);
	CString GetTextFont();
	void SetTextFontStyle(long nNewValue);
	long GetTextFontStyle();
	void SetTextFontSize(long nNewValue);
	long GetTextFontSize();
	void SetHistoryLines(long nNewValue);
	long GetHistoryLines();
	void SetMaxAutoCADWindow(BOOL bNewValue);
	BOOL GetMaxAutoCADWindow();
	void SetDisplayLayoutTabs(BOOL bNewValue);
	BOOL GetDisplayLayoutTabs();
	void SetImageFrameHighlight(BOOL bNewValue);
	BOOL GetImageFrameHighlight();
	void SetTrueColorImages(BOOL bNewValue);
	BOOL GetTrueColorImages();
	void SetXRefFadeIntensity(long nNewValue);
	long GetXRefFadeIntensity();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesOpenSave wrapper class

class IAcadPreferencesOpenSave : public COleDispatchDriver
{
public:
	IAcadPreferencesOpenSave() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesOpenSave(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesOpenSave(const IAcadPreferencesOpenSave& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetSavePreviewThumbnail(BOOL bNewValue);
	BOOL GetSavePreviewThumbnail();
	void SetIncrementalSavePercent(long nNewValue);
	long GetIncrementalSavePercent();
	void SetAutoSaveInterval(long nNewValue);
	long GetAutoSaveInterval();
	void SetCreateBackup(BOOL bNewValue);
	BOOL GetCreateBackup();
	void SetFullCRCValidation(BOOL bNewValue);
	BOOL GetFullCRCValidation();
	void SetLogFileOn(BOOL bNewValue);
	BOOL GetLogFileOn();
	void SetTempFileExtension(LPCTSTR lpszNewValue);
	CString GetTempFileExtension();
	void SetXrefDemandLoad(long nNewValue);
	long GetXrefDemandLoad();
	void SetDemandLoadARXApp(long nNewValue);
	long GetDemandLoadARXApp();
	void SetProxyImage(long nNewValue);
	long GetProxyImage();
	void SetShowProxyDialogBox(BOOL bNewValue);
	BOOL GetShowProxyDialogBox();
	void SetAutoAudit(BOOL bNewValue);
	BOOL GetAutoAudit();
	void SetSaveAsType(long nNewValue);
	long GetSaveAsType();
	long GetMRUNumber();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesOutput wrapper class

class IAcadPreferencesOutput : public COleDispatchDriver
{
public:
	IAcadPreferencesOutput() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesOutput(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesOutput(const IAcadPreferencesOutput& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetDefaultOutputDevice(LPCTSTR lpszNewValue);
	CString GetDefaultOutputDevice();
	void SetPrinterSpoolAlert(long nNewValue);
	long GetPrinterSpoolAlert();
	void SetPrinterPaperSizeAlert(BOOL bNewValue);
	BOOL GetPrinterPaperSizeAlert();
	void SetPlotLegacy(BOOL bNewValue);
	BOOL GetPlotLegacy();
	void SetOLEQuality(long nNewValue);
	long GetOLEQuality();
	void SetUseLastPlotSettings(BOOL bNewValue);
	BOOL GetUseLastPlotSettings();
	void SetPlotPolicy(long nNewValue);
	long GetPlotPolicy();
	void SetDefaultPlotStyleTable(LPCTSTR lpszNewValue);
	CString GetDefaultPlotStyleTable();
	void SetDefaultPlotStyleForObjects(LPCTSTR lpszNewValue);
	CString GetDefaultPlotStyleForObjects();
	void SetDefaultPlotStyleForLayer(LPCTSTR lpszNewValue);
	CString GetDefaultPlotStyleForLayer();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesSystem wrapper class

class IAcadPreferencesSystem : public COleDispatchDriver
{
public:
	IAcadPreferencesSystem() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesSystem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesSystem(const IAcadPreferencesSystem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetSingleDocumentMode(BOOL bNewValue);
	BOOL GetSingleDocumentMode();
	void SetDisplayOLEScale(BOOL bNewValue);
	BOOL GetDisplayOLEScale();
	void SetStoreSQLIndex(BOOL bNewValue);
	BOOL GetStoreSQLIndex();
	void SetTablesReadOnly(BOOL bNewValue);
	BOOL GetTablesReadOnly();
	void SetEnableStartupDialog(BOOL bNewValue);
	BOOL GetEnableStartupDialog();
	void SetBeepOnError(BOOL bNewValue);
	BOOL GetBeepOnError();
	void SetShowWarningMessages(BOOL bNewValue);
	BOOL GetShowWarningMessages();
	void SetLoadAcadLspInAllDocuments(BOOL bNewValue);
	BOOL GetLoadAcadLspInAllDocuments();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesUser wrapper class

class IAcadPreferencesUser : public COleDispatchDriver
{
public:
	IAcadPreferencesUser() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesUser(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesUser(const IAcadPreferencesUser& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetKeyboardAccelerator(long nNewValue);
	long GetKeyboardAccelerator();
	void SetKeyboardPriority(long nNewValue);
	long GetKeyboardPriority();
	void SetHyperlinkDisplayCursor(BOOL bNewValue);
	BOOL GetHyperlinkDisplayCursor();
	void SetHyperlinkDisplayTooltip(BOOL bNewValue);
	BOOL GetHyperlinkDisplayTooltip();
	void SetADCInsertUnitsDefaultSource(long nNewValue);
	long GetADCInsertUnitsDefaultSource();
	void SetADCInsertUnitsDefaultTarget(long nNewValue);
	long GetADCInsertUnitsDefaultTarget();
	void SetShortCutMenuDisplay(BOOL bNewValue);
	BOOL GetShortCutMenuDisplay();
	void SetSCMDefaultMode(long nNewValue);
	long GetSCMDefaultMode();
	void SetSCMEditMode(long nNewValue);
	long GetSCMEditMode();
	void SetSCMCommandMode(long nNewValue);
	long GetSCMCommandMode();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesDrafting wrapper class

class IAcadPreferencesDrafting : public COleDispatchDriver
{
public:
	IAcadPreferencesDrafting() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesDrafting(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesDrafting(const IAcadPreferencesDrafting& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetAutoSnapMarker(BOOL bNewValue);
	BOOL GetAutoSnapMarker();
	void SetAutoSnapMagnet(BOOL bNewValue);
	BOOL GetAutoSnapMagnet();
	void SetAutoSnapTooltip(BOOL bNewValue);
	BOOL GetAutoSnapTooltip();
	void SetAutoSnapAperture(BOOL bNewValue);
	BOOL GetAutoSnapAperture();
	void SetAutoSnapApertureSize(long nNewValue);
	long GetAutoSnapApertureSize();
	void SetAutoSnapMarkerColor(long nNewValue);
	long GetAutoSnapMarkerColor();
	void SetAutoSnapMarkerSize(long nNewValue);
	long GetAutoSnapMarkerSize();
	void SetPolarTrackingVector(BOOL bNewValue);
	BOOL GetPolarTrackingVector();
	void SetFullScreenTrackingVector(BOOL bNewValue);
	BOOL GetFullScreenTrackingVector();
	void SetAutoTrackTooltip(BOOL bNewValue);
	BOOL GetAutoTrackTooltip();
	void SetAlignmentPointAcquisition(long nNewValue);
	long GetAlignmentPointAcquisition();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesSelection wrapper class

class IAcadPreferencesSelection : public COleDispatchDriver
{
public:
	IAcadPreferencesSelection() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesSelection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesSelection(const IAcadPreferencesSelection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetPickFirst(BOOL bNewValue);
	BOOL GetPickFirst();
	void SetPickAdd(BOOL bNewValue);
	BOOL GetPickAdd();
	void SetPickDrag(BOOL bNewValue);
	BOOL GetPickDrag();
	void SetPickAuto(BOOL bNewValue);
	BOOL GetPickAuto();
	void SetPickBoxSize(long nNewValue);
	long GetPickBoxSize();
	void SetDisplayGrips(BOOL bNewValue);
	BOOL GetDisplayGrips();
	void SetDisplayGripsWithinBlocks(BOOL bNewValue);
	BOOL GetDisplayGripsWithinBlocks();
	void SetGripColorSelected(long nNewValue);
	long GetGripColorSelected();
	void SetGripColorUnselected(long nNewValue);
	long GetGripColorUnselected();
	void SetGripSize(long nNewValue);
	long GetGripSize();
	void SetPickGroup(BOOL bNewValue);
	BOOL GetPickGroup();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesProfiles wrapper class

class IAcadPreferencesProfiles : public COleDispatchDriver
{
public:
	IAcadPreferencesProfiles() {}		// Calls COleDispatchDriver default constructor
	IAcadPreferencesProfiles(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPreferencesProfiles(const IAcadPreferencesProfiles& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	void SetActiveProfile(LPCTSTR lpszNewValue);
	CString GetActiveProfile();
	void ImportProfile(LPCTSTR ProfileName, LPCTSTR RegFile, BOOL IncludePathInfo);
	void ExportProfile(LPCTSTR ProfileName, LPCTSTR RegFile);
	void DeleteProfile(LPCTSTR ProfileName);
	void ResetProfile(LPCTSTR Profile);
	void RenameProfile(LPCTSTR origProfileName, LPCTSTR newProfileName);
	void CopyProfile(LPCTSTR oldProfileName, LPCTSTR newProfileName);
	void GetAllProfileNames(VARIANT* pNames);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroups wrapper class

class IAcadMenuGroups : public COleDispatchDriver
{
public:
	IAcadMenuGroups() {}		// Calls COleDispatchDriver default constructor
	IAcadMenuGroups(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMenuGroups(const IAcadMenuGroups& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Load(LPCTSTR MenuFileName, const VARIANT& BaseMenu);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroup wrapper class

class IAcadMenuGroup : public COleDispatchDriver
{
public:
	IAcadMenuGroup() {}		// Calls COleDispatchDriver default constructor
	IAcadMenuGroup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMenuGroup(const IAcadMenuGroup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	long GetType();
	CString GetMenuFileName();
	LPDISPATCH GetMenus();
	LPDISPATCH GetToolbars();
	void Unload();
	void Save(long MenuFileType);
	void SaveAs(LPCTSTR MenuFileName, long MenuFileType);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenus wrapper class

class IAcadPopupMenus : public COleDispatchDriver
{
public:
	IAcadPopupMenus() {}		// Calls COleDispatchDriver default constructor
	IAcadPopupMenus(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPopupMenus(const IAcadPopupMenus& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	LPDISPATCH Add(LPCTSTR MenuName);
	void InsertMenuInMenuBar(LPCTSTR MenuName, const VARIANT& Index);
	void RemoveMenuFromMenuBar(const VARIANT& Index);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenu wrapper class

class IAcadPopupMenu : public COleDispatchDriver
{
public:
	IAcadPopupMenu() {}		// Calls COleDispatchDriver default constructor
	IAcadPopupMenu(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPopupMenu(const IAcadPopupMenu& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetNameNoMnemonic();
	BOOL GetShortcutMenu();
	BOOL GetOnMenuBar();
	LPDISPATCH AddMenuItem(const VARIANT& Index, LPCTSTR Label, LPCTSTR Macro);
	LPDISPATCH AddSubMenu(const VARIANT& Index, LPCTSTR Label);
	LPDISPATCH AddSeparator(const VARIANT& Index);
	void InsertInMenuBar(const VARIANT& Index);
	void RemoveFromMenuBar();
	CString GetTagString();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenuItem wrapper class

class IAcadPopupMenuItem : public COleDispatchDriver
{
public:
	IAcadPopupMenuItem() {}		// Calls COleDispatchDriver default constructor
	IAcadPopupMenuItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadPopupMenuItem(const IAcadPopupMenuItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetLabel();
	void SetLabel(LPCTSTR lpszNewValue);
	CString GetTagString();
	void SetTagString(LPCTSTR lpszNewValue);
	BOOL GetEnable();
	void SetEnable(BOOL bNewValue);
	BOOL GetCheck();
	void SetCheck(BOOL bNewValue);
	long GetType();
	LPDISPATCH GetSubMenu();
	CString GetMacro();
	void SetMacro(LPCTSTR lpszNewValue);
	long GetIndex();
	CString GetCaption();
	CString GetHelpString();
	void SetHelpString(LPCTSTR lpszNewValue);
	void Delete();
	long GetEndSubMenuLevel();
	void SetEndSubMenuLevel(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadToolbars wrapper class

class IAcadToolbars : public COleDispatchDriver
{
public:
	IAcadToolbars() {}		// Calls COleDispatchDriver default constructor
	IAcadToolbars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadToolbars(const IAcadToolbars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	BOOL GetLargeButtons();
	void SetLargeButtons(BOOL bNewValue);
	LPDISPATCH Add(LPCTSTR ToolbarName);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadToolbar wrapper class

class IAcadToolbar : public COleDispatchDriver
{
public:
	IAcadToolbar() {}		// Calls COleDispatchDriver default constructor
	IAcadToolbar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadToolbar(const IAcadToolbar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetDockStatus();
	BOOL GetLargeButtons();
	long GetLeft();
	void SetLeft(long nNewValue);
	long GetTop();
	void SetTop(long nNewValue);
	long GetWidth();
	long GetHeight();
	long GetFloatingRows();
	void SetFloatingRows(long nNewValue);
	CString GetHelpString();
	void SetHelpString(LPCTSTR lpszNewValue);
	LPDISPATCH AddToolbarButton(const VARIANT& Index, LPCTSTR Name, LPCTSTR HelpString, LPCTSTR Macro, const VARIANT& FlyoutButton);
	LPDISPATCH AddSeparator(const VARIANT& Index);
	void Dock(long Side);
	void Float(long top, long left, long NumberFloatRows);
	void Delete();
	CString GetTagString();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadToolbarItem wrapper class

class IAcadToolbarItem : public COleDispatchDriver
{
public:
	IAcadToolbarItem() {}		// Calls COleDispatchDriver default constructor
	IAcadToolbarItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadToolbarItem(const IAcadToolbarItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetTagString();
	void SetTagString(LPCTSTR lpszNewValue);
	long GetType();
	LPDISPATCH GetFlyout();
	CString GetMacro();
	void SetMacro(LPCTSTR lpszNewValue);
	long GetIndex();
	CString GetHelpString();
	void SetHelpString(LPCTSTR lpszNewValue);
	void GetBitmaps(BSTR* SmallIconName, BSTR* LargeIconName);
	void SetBitmaps(LPCTSTR SmallIconName, LPCTSTR LargeIconName);
	void AttachToolbarToFlyout(LPCTSTR MenuGroupName, LPCTSTR ToolbarName);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadMenuBar wrapper class

class IAcadMenuBar : public COleDispatchDriver
{
public:
	IAcadMenuBar() {}		// Calls COleDispatchDriver default constructor
	IAcadMenuBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadMenuBar(const IAcadMenuBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH GetParent();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadDocuments wrapper class

class IAcadDocuments : public COleDispatchDriver
{
public:
	IAcadDocuments() {}		// Calls COleDispatchDriver default constructor
	IAcadDocuments(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadDocuments(const IAcadDocuments& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH Add(const VARIANT& TemplateName);
	LPDISPATCH Open(LPCTSTR Name, const VARIANT& ReadOnly);
	void Close();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadState wrapper class

class IAcadState : public COleDispatchDriver
{
public:
	IAcadState() {}		// Calls COleDispatchDriver default constructor
	IAcadState(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadState(const IAcadState& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	BOOL GetIsQuiescent();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadSelectionSets wrapper class

class IAcadSelectionSets : public COleDispatchDriver
{
public:
	IAcadSelectionSets() {}		// Calls COleDispatchDriver default constructor
	IAcadSelectionSets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadSelectionSets(const IAcadSelectionSets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	LPDISPATCH GetApplication();
	LPDISPATCH Add(LPCTSTR Name);
};
/////////////////////////////////////////////////////////////////////////////
// IAcadSelectionSet wrapper class

class IAcadSelectionSet : public COleDispatchDriver
{
public:
	IAcadSelectionSet() {}		// Calls COleDispatchDriver default constructor
	IAcadSelectionSet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadSelectionSet(const IAcadSelectionSet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Item(const VARIANT& Index);
	long GetCount();
	CString GetName();
	void Highlight(BOOL bFlag);
	void Erase();
	void Update();
	LPDISPATCH GetApplication();
	void AddItems(const VARIANT& pSelSet);
	void RemoveItems(const VARIANT& Objects);
	void Clear();
	void Select(long Mode, const VARIANT& Point1, const VARIANT& Point2, const VARIANT& FilterType, const VARIANT& FilterData);
	void SelectAtPoint(const VARIANT& Point, const VARIANT& FilterType, const VARIANT& FilterData);
	void SelectByPolygon(long Mode, const VARIANT& PointsList, const VARIANT& FilterType, const VARIANT& FilterData);
	void SelectOnScreen(const VARIANT& FilterType, const VARIANT& FilterData);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// IAcadUtility wrapper class

class IAcadUtility : public COleDispatchDriver
{
public:
	IAcadUtility() {}		// Calls COleDispatchDriver default constructor
	IAcadUtility(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadUtility(const IAcadUtility& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	double AngleToReal(LPCTSTR Angle, long Unit);
	CString AngleToString(double Angle, long Unit, long precision);
	double DistanceToReal(LPCTSTR Distance, long Unit);
	CString RealToString(double Value, long Unit, long precision);
	VARIANT TranslateCoordinates(const VARIANT& Point, long FromCoordSystem, long ToCoordSystem, long Displacement, const VARIANT& OCSNormal);
	void InitializeUserInput(long Bits, const VARIANT& KeyWordList);
	long GetInteger(const VARIANT& Prompt);
	double GetReal(const VARIANT& Prompt);
	CString GetInput();
	CString GetKeyword(const VARIANT& Prompt);
	CString GetString(long HasSpaces, const VARIANT& Prompt);
	double GetAngle(const VARIANT& Point, const VARIANT& Prompt);
	double AngleFromXAxis(const VARIANT& StartPoint, const VARIANT& EndPoint);
	VARIANT GetCorner(const VARIANT& Point, const VARIANT& Prompt);
	double GetDistance(const VARIANT& Point, const VARIANT& Prompt);
	double GetOrientation(const VARIANT& Point, const VARIANT& Prompt);
	VARIANT GetPoint(const VARIANT& Point, const VARIANT& Prompt);
	VARIANT PolarPoint(const VARIANT& Point, double Angle, double Distance);
	// method 'CreateTypedArray' not emitted because of invalid return type or parameter type
	void GetEntity(LPDISPATCH* Object, VARIANT* PickedPoint, const VARIANT& Prompt);
	void Prompt(LPCTSTR Message);
	void GetSubEntity(LPDISPATCH* Object, VARIANT* PickedPoint, VARIANT* transMatrix, VARIANT* ContextData, const VARIANT& Prompt);
	BOOL IsURL(LPCTSTR URL);
	void GetRemoteFile(LPCTSTR URL, BSTR* LocalFile, BOOL IgnoreCache);
	void PutRemoteFile(LPCTSTR URL, LPCTSTR LocalFile);
	BOOL IsRemoteFile(LPCTSTR LocalFile, BSTR* URL);
	BOOL LaunchBrowserDialog(BSTR* SelectedURL, LPCTSTR DialogTitle, LPCTSTR OpenButtonCaption, LPCTSTR StartPageURL, LPCTSTR RegistryRootKey, BOOL OpenButtonAlwaysEnabled);
};
/////////////////////////////////////////////////////////////////////////////
// _DAcadDocumentEvents wrapper class

class _DAcadDocumentEvents : public COleDispatchDriver
{
public:
	_DAcadDocumentEvents() {}		// Calls COleDispatchDriver default constructor
	_DAcadDocumentEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DAcadDocumentEvents(const _DAcadDocumentEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	// method 'BeginSave' not emitted because of invalid return type or parameter type
	// method 'EndSave' not emitted because of invalid return type or parameter type
	// method 'BeginCommand' not emitted because of invalid return type or parameter type
	// method 'EndCommand' not emitted because of invalid return type or parameter type
	// method 'BeginLisp' not emitted because of invalid return type or parameter type
	// method 'EndLisp' not emitted because of invalid return type or parameter type
	// method 'LispCancelled' not emitted because of invalid return type or parameter type
	// method 'SelectionChanged' not emitted because of invalid return type or parameter type
	// method 'Activate' not emitted because of invalid return type or parameter type
	// method 'Deactivate' not emitted because of invalid return type or parameter type
	// method 'BeginRightClick' not emitted because of invalid return type or parameter type
	// method 'BeginShortcutMenuDefault' not emitted because of invalid return type or parameter type
	// method 'BeginShortcutMenuEdit' not emitted because of invalid return type or parameter type
	// method 'BeginShortcutMenuCommand' not emitted because of invalid return type or parameter type
	// method 'BeginShortcutMenuGrip' not emitted because of invalid return type or parameter type
	// method 'BeginShortcutMenuOsnap' not emitted because of invalid return type or parameter type
	// method 'EndShortcutMenu' not emitted because of invalid return type or parameter type
	// method 'BeginDoubleClick' not emitted because of invalid return type or parameter type
	// method 'ObjectAdded' not emitted because of invalid return type or parameter type
	// method 'ObjectErased' not emitted because of invalid return type or parameter type
	// method 'ObjectModified' not emitted because of invalid return type or parameter type
	// method 'BeginPlot' not emitted because of invalid return type or parameter type
	// method 'EndPlot' not emitted because of invalid return type or parameter type
	// method 'WindowMovedOrResized' not emitted because of invalid return type or parameter type
	// method 'LayoutSwitched' not emitted because of invalid return type or parameter type
	// method 'WindowChanged' not emitted because of invalid return type or parameter type
	// method 'BeginClose' not emitted because of invalid return type or parameter type
};
/////////////////////////////////////////////////////////////////////////////
// IAcadLayerStateManager wrapper class

class IAcadLayerStateManager : public COleDispatchDriver
{
public:
	IAcadLayerStateManager() {}		// Calls COleDispatchDriver default constructor
	IAcadLayerStateManager(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IAcadLayerStateManager(const IAcadLayerStateManager& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SetDatabase(LPDISPATCH iHostDb);
	void SetMask(LPCTSTR bsName, long nNewValue);
	long GetMask(LPCTSTR bsName);
	void Save(LPCTSTR bsName, long eMask);
	void Restore(LPCTSTR bsName);
	void Delete(LPCTSTR bsName);
	void Rename(LPCTSTR bsName, LPCTSTR bsNewName);
	void Import(LPCTSTR bsFilename);
	void Export(LPCTSTR bsName, LPCTSTR bsFilename);
};
