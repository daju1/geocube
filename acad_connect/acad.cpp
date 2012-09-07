// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "acad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IAcadObject properties

/////////////////////////////////////////////////////////////////////////////
// IAcadObject operations

CString IAcadObject::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadObject::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadObject::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadObject::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadObject::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadObject::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadObject::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadObject::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadObject::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadObject::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadObject::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDatabase properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDatabase operations

LPDISPATCH IAcadDatabase::GetModelSpace()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetPaperSpace()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetBlocks()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDatabase::CopyObjects(const VARIANT& Objects, const VARIANT& Owner, VARIANT* IdPairs)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Objects, &Owner, IdPairs);
	return result;
}

LPDISPATCH IAcadDatabase::GetGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetDimStyles()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetLayers()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetLinetypes()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetDictionaries()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetRegisteredApplications()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetTextStyles()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetUserCoordinateSystems()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetViews()
{
	LPDISPATCH result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetViewports()
{
	LPDISPATCH result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

double IAcadDatabase::GetElevationModelSpace()
{
	double result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDatabase::SetElevationModelSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDatabase::GetElevationPaperSpace()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDatabase::SetElevationPaperSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDatabase::GetLimits()
{
	VARIANT result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDatabase::SetLimits(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadDatabase::HandleToObject(LPCTSTR Handle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Handle);
	return result;
}

LPDISPATCH IAcadDatabase::ObjectIdToObject(long ObjectID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ObjectID);
	return result;
}

LPDISPATCH IAcadDatabase::GetLayouts()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetPlotConfigurations()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDatabase::GetPreferences()
{
	LPDISPATCH result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadModelSpace properties

/////////////////////////////////////////////////////////////////////////////
// IAcadModelSpace operations

CString IAcadModelSpace::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadModelSpace::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadModelSpace::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadModelSpace::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadModelSpace::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadModelSpace::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadModelSpace::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadModelSpace::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadModelSpace::GetCount()
{
	long result;
	InvokeHelper(0x600, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadModelSpace::GetName()
{
	CString result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadModelSpace::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadModelSpace::GetOrigin()
{
	VARIANT result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadModelSpace::SetOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadModelSpace::AddCustomObject(LPCTSTR ClassName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x603, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ClassName);
	return result;
}

LPDISPATCH IAcadModelSpace::Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x604, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadModelSpace::Add3DMesh(long M, long N, const VARIANT& PointsMatrix)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x605, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		M, N, &PointsMatrix);
	return result;
}

LPDISPATCH IAcadModelSpace::Add3DPoly(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x606, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadModelSpace::AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x607, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, StartAngle, EndAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R8 VTS_I4 VTS_BSTR VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x608, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Height, Mode, Prompt, &InsertionPoint, Tag, Value);
	return result;
}

LPDISPATCH IAcadModelSpace::AddBox(const VARIANT& Origin, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x609, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Origin, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddCircle(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x60a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadModelSpace::AddCone(const VARIANT& Center, double BaseRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, BaseRadius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddCylinder(const VARIANT& Center, double Radius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &TextPosition);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x60f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ChordPoint, &FarChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x610, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &DimLineLocation, RotationAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x611, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&DefinitionPoint, &LeaderEndPoint, UseXAxis);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x612, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &ChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadModelSpace::AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x613, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &MajorAxis, RadiusRatio);
	return result;
}

LPDISPATCH IAcadModelSpace::AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x614, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x615, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_R8 VTS_R8;
	InvokeHelper(0x616, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Height, TaperAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0x617, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Path);
	return result;
}

LPDISPATCH IAcadModelSpace::AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_DISPATCH VTS_I4;
	InvokeHelper(0x618, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, Annotation, Type);
	return result;
}

LPDISPATCH IAcadModelSpace::AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_BSTR;
	InvokeHelper(0x619, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Width, Text);
	return result;
}

LPDISPATCH IAcadModelSpace::AddPoint(const VARIANT& Point)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point);
	return result;
}

LPDISPATCH IAcadModelSpace::AddLightWeightPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddRay(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x61d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

VARIANT IAcadModelSpace::AddRegion(const VARIANT& ObjectList)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ObjectList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x61f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, &AxisPoint, &AxisDir, Angle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x620, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x621, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadModelSpace::AddSphere(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x622, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadModelSpace::AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x623, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, &StartTangent, &EndTangent);
	return result;
}

LPDISPATCH IAcadModelSpace::AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8;
	InvokeHelper(0x624, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TextString, &InsertionPoint, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x625, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Text, &InsertionPoint, &Direction);
	return result;
}

LPDISPATCH IAcadModelSpace::AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x626, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, TorusRadius, TubeRadius);
	return result;
}

LPDISPATCH IAcadModelSpace::AddTrace(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x627, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadModelSpace::AddWedge(const VARIANT& Center, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x628, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadModelSpace::AddXline(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x629, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadModelSpace::InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x62a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation);
	return result;
}

LPDISPATCH IAcadModelSpace::AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BOOL;
	InvokeHelper(0x62b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PatternType, PatternName, Associativity);
	return result;
}

LPDISPATCH IAcadModelSpace::AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x62c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		imageFileName, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadModelSpace::AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x62d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&StartPoint, &EndPoint);
	return result;
}

BOOL IAcadModelSpace::GetIsLayout()
{
	BOOL result;
	InvokeHelper(0x62e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::GetLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x62f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadModelSpace::GetIsXRef()
{
	BOOL result;
	InvokeHelper(0x630, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x631, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation, NumRows, NumColumns, RowSpacing, ColumnSpacing);
	return result;
}

LPDISPATCH IAcadModelSpace::AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x632, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList, &FaceList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddMLine(const VARIANT& VertexList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x633, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList);
	return result;
}

LPDISPATCH IAcadModelSpace::AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x634, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadModelSpace::GetXRefDatabase()
{
	LPDISPATCH result;
	InvokeHelper(0x635, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadModelSpace::AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BOOL;
	InvokeHelper(0x636, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PathName, Name, &InsertionPoint, Xscale, Yscale, Zscale, Rotation, bOverlay);
	return result;
}

void IAcadModelSpace::Unload()
{
	InvokeHelper(0x637, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadModelSpace::Reload()
{
	InvokeHelper(0x638, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadModelSpace::Bind(BOOL bPrefixName)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x639, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bPrefixName);
}

void IAcadModelSpace::Detach()
{
	InvokeHelper(0x63a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadBlock properties

/////////////////////////////////////////////////////////////////////////////
// IAcadBlock operations

CString IAcadBlock::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadBlock::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlock::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadBlock::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadBlock::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadBlock::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadBlock::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadBlock::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadBlock::GetCount()
{
	long result;
	InvokeHelper(0x600, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadBlock::GetName()
{
	CString result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlock::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadBlock::GetOrigin()
{
	VARIANT result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadBlock::SetOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadBlock::AddCustomObject(LPCTSTR ClassName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x603, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ClassName);
	return result;
}

LPDISPATCH IAcadBlock::Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x604, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadBlock::Add3DMesh(long M, long N, const VARIANT& PointsMatrix)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x605, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		M, N, &PointsMatrix);
	return result;
}

LPDISPATCH IAcadBlock::Add3DPoly(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x606, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadBlock::AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x607, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, StartAngle, EndAngle);
	return result;
}

LPDISPATCH IAcadBlock::AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R8 VTS_I4 VTS_BSTR VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x608, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Height, Mode, Prompt, &InsertionPoint, Tag, Value);
	return result;
}

LPDISPATCH IAcadBlock::AddBox(const VARIANT& Origin, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x609, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Origin, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddCircle(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x60a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadBlock::AddCone(const VARIANT& Center, double BaseRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, BaseRadius, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddCylinder(const VARIANT& Center, double Radius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &TextPosition);
	return result;
}

LPDISPATCH IAcadBlock::AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadBlock::AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x60f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ChordPoint, &FarChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadBlock::AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x610, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &DimLineLocation, RotationAngle);
	return result;
}

LPDISPATCH IAcadBlock::AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x611, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&DefinitionPoint, &LeaderEndPoint, UseXAxis);
	return result;
}

LPDISPATCH IAcadBlock::AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x612, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &ChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadBlock::AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x613, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &MajorAxis, RadiusRatio);
	return result;
}

LPDISPATCH IAcadBlock::AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x614, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x615, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_R8 VTS_R8;
	InvokeHelper(0x616, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Height, TaperAngle);
	return result;
}

LPDISPATCH IAcadBlock::AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0x617, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Path);
	return result;
}

LPDISPATCH IAcadBlock::AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_DISPATCH VTS_I4;
	InvokeHelper(0x618, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, Annotation, Type);
	return result;
}

LPDISPATCH IAcadBlock::AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_BSTR;
	InvokeHelper(0x619, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Width, Text);
	return result;
}

LPDISPATCH IAcadBlock::AddPoint(const VARIANT& Point)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point);
	return result;
}

LPDISPATCH IAcadBlock::AddLightWeightPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadBlock::AddPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadBlock::AddRay(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x61d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

VARIANT IAcadBlock::AddRegion(const VARIANT& ObjectList)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ObjectList);
	return result;
}

LPDISPATCH IAcadBlock::AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x61f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, &AxisPoint, &AxisDir, Angle);
	return result;
}

LPDISPATCH IAcadBlock::AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x620, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadBlock::AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x621, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadBlock::AddSphere(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x622, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadBlock::AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x623, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, &StartTangent, &EndTangent);
	return result;
}

LPDISPATCH IAcadBlock::AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8;
	InvokeHelper(0x624, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TextString, &InsertionPoint, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x625, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Text, &InsertionPoint, &Direction);
	return result;
}

LPDISPATCH IAcadBlock::AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x626, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, TorusRadius, TubeRadius);
	return result;
}

LPDISPATCH IAcadBlock::AddTrace(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x627, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadBlock::AddWedge(const VARIANT& Center, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x628, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadBlock::AddXline(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x629, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadBlock::InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x62a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation);
	return result;
}

LPDISPATCH IAcadBlock::AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BOOL;
	InvokeHelper(0x62b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PatternType, PatternName, Associativity);
	return result;
}

LPDISPATCH IAcadBlock::AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x62c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		imageFileName, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadBlock::AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x62d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&StartPoint, &EndPoint);
	return result;
}

BOOL IAcadBlock::GetIsLayout()
{
	BOOL result;
	InvokeHelper(0x62e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::GetLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x62f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadBlock::GetIsXRef()
{
	BOOL result;
	InvokeHelper(0x630, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x631, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation, NumRows, NumColumns, RowSpacing, ColumnSpacing);
	return result;
}

LPDISPATCH IAcadBlock::AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x632, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList, &FaceList);
	return result;
}

LPDISPATCH IAcadBlock::AddMLine(const VARIANT& VertexList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x633, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList);
	return result;
}

LPDISPATCH IAcadBlock::AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x634, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadBlock::GetXRefDatabase()
{
	LPDISPATCH result;
	InvokeHelper(0x635, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlock::AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BOOL;
	InvokeHelper(0x636, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PathName, Name, &InsertionPoint, Xscale, Yscale, Zscale, Rotation, bOverlay);
	return result;
}

void IAcadBlock::Unload()
{
	InvokeHelper(0x637, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadBlock::Reload()
{
	InvokeHelper(0x638, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadBlock::Bind(BOOL bPrefixName)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x639, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bPrefixName);
}

void IAcadBlock::Detach()
{
	InvokeHelper(0x63a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadEntity properties

/////////////////////////////////////////////////////////////////////////////
// IAcadEntity operations

CString IAcadEntity::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadEntity::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEntity::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadEntity::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadEntity::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadEntity::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadEntity::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadEntity::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadEntity::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadEntity::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadEntity::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadEntity::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadEntity::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadEntity::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadEntity::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadEntity::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadEntity::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadEntity::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadEntity::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadEntity::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadEntity::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadEntity::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadEntity::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadEntity::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadEntity::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadEntity::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadEntity::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadEntity::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadEntity::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadEntity::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadEntity::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadEntity::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadEntity::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadEntity::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadHyperlinks properties

/////////////////////////////////////////////////////////////////////////////
// IAcadHyperlinks operations

LPDISPATCH IAcadHyperlinks::Item(long Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Index);
	return result;
}

long IAcadHyperlinks::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadHyperlinks::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadHyperlinks::Add(LPCTSTR Name, const VARIANT& Description, const VARIANT& NamedLocation)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &Description, &NamedLocation);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadHyperlink properties

/////////////////////////////////////////////////////////////////////////////
// IAcadHyperlink operations

void IAcadHyperlink::SetUrl(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadHyperlink::GetUrl()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadHyperlink::SetURLDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadHyperlink::GetURLDescription()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadHyperlink::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadHyperlink::Delete()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadHyperlink::SetURLNamedLocation(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadHyperlink::GetURLNamedLocation()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcad3DFace properties

/////////////////////////////////////////////////////////////////////////////
// IAcad3DFace operations

CString IAcad3DFace::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcad3DFace::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcad3DFace::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcad3DFace::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcad3DFace::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DFace::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcad3DFace::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DFace::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcad3DFace::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DFace::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcad3DFace::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcad3DFace::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcad3DFace::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcad3DFace::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcad3DFace::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcad3DFace::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcad3DFace::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcad3DFace::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcad3DFace::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcad3DFace::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcad3DFace::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcad3DFace::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcad3DFace::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcad3DFace::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcad3DFace::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcad3DFace::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcad3DFace::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcad3DFace::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcad3DFace::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcad3DFace::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcad3DFace::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DFace::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL IAcad3DFace::GetVisibilityEdge1()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetVisibilityEdge1(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcad3DFace::GetVisibilityEdge2()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetVisibilityEdge2(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcad3DFace::GetVisibilityEdge3()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetVisibilityEdge3(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcad3DFace::GetVisibilityEdge4()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DFace::SetVisibilityEdge4(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcad3DFace::GetInvisibleEdge(long Index)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		Index);
	return result;
}

void IAcad3DFace::SetInvisibleEdge(long Index, BOOL State)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, State);
}

VARIANT IAcad3DFace::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcad3DFace::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPolygonMesh properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPolygonMesh operations

CString IAcadPolygonMesh::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPolygonMesh::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPolygonMesh::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPolygonMesh::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPolygonMesh::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolygonMesh::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPolygonMesh::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolygonMesh::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPolygonMesh::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolygonMesh::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPolygonMesh::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadPolygonMesh::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPolygonMesh::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadPolygonMesh::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPolygonMesh::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPolygonMesh::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadPolygonMesh::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadPolygonMesh::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadPolygonMesh::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadPolygonMesh::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadPolygonMesh::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadPolygonMesh::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadPolygonMesh::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadPolygonMesh::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadPolygonMesh::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadPolygonMesh::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPolygonMesh::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadPolygonMesh::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadPolygonMesh::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPolygonMesh::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadPolygonMesh::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPolygonMesh::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL IAcadPolygonMesh::GetMClose()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetMClose(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPolygonMesh::GetNClose()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetNClose(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPolygonMesh::GetMDensity()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetMDensity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPolygonMesh::GetNDensity()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetNDensity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPolygonMesh::GetMVertexCount()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadPolygonMesh::GetNVertexCount()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadPolygonMesh::GetType()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolygonMesh::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadPolygonMesh::AppendVertex(const VARIANT& vertex)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vertex);
}

VARIANT IAcadPolygonMesh::Explode()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPolygonMesh::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadPolygonMesh::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcad3DPolyline properties

/////////////////////////////////////////////////////////////////////////////
// IAcad3DPolyline operations

CString IAcad3DPolyline::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcad3DPolyline::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcad3DPolyline::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcad3DPolyline::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcad3DPolyline::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DPolyline::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcad3DPolyline::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DPolyline::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcad3DPolyline::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DPolyline::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcad3DPolyline::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcad3DPolyline::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcad3DPolyline::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcad3DPolyline::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcad3DPolyline::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcad3DPolyline::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcad3DPolyline::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcad3DPolyline::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcad3DPolyline::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcad3DPolyline::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcad3DPolyline::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcad3DPolyline::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcad3DPolyline::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcad3DPolyline::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcad3DPolyline::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcad3DPolyline::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcad3DPolyline::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcad3DPolyline::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcad3DPolyline::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcad3DPolyline::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcad3DPolyline::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DPolyline::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IAcad3DPolyline::AppendVertex(const VARIANT& vertex)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vertex);
}

VARIANT IAcad3DPolyline::Explode()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DPolyline::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcad3DPolyline::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}

long IAcad3DPolyline::GetType()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcad3DPolyline::GetClosed()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DPolyline::SetClosed(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadArc properties

/////////////////////////////////////////////////////////////////////////////
// IAcadArc operations

CString IAcadArc::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadArc::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadArc::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadArc::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadArc::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadArc::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadArc::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadArc::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadArc::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadArc::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadArc::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadArc::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadArc::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadArc::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadArc::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadArc::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadArc::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadArc::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadArc::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadArc::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadArc::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadArc::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadArc::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadArc::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadArc::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadArc::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadArc::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadArc::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadArc::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadArc::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadArc::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadArc::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadArc::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadArc::GetStartPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadArc::GetCenter()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetCenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadArc::GetEndPoint()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadArc::GetRadius()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetRadius(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadArc::GetStartAngle()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetStartAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadArc::GetEndAngle()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetEndAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadArc::GetTotalAngle()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double IAcadArc::GetArcLength()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double IAcadArc::GetThickness()
{
	double result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadArc::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}

double IAcadArc::GetArea()
{
	double result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadArc::GetNormal()
{
	VARIANT result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadArc::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadAttribute properties

/////////////////////////////////////////////////////////////////////////////
// IAcadAttribute operations

CString IAcadAttribute::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadAttribute::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadAttribute::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadAttribute::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadAttribute::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadAttribute::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadAttribute::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadAttribute::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadAttribute::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadAttribute::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadAttribute::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadAttribute::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadAttribute::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadAttribute::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadAttribute::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadAttribute::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadAttribute::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadAttribute::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadAttribute::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadAttribute::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadAttribute::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadAttribute::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadAttribute::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadAttribute::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadAttribute::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadAttribute::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadAttribute::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadAttribute::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadAttribute::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadAttribute::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadAttribute::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadAttribute::GetFieldLength()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetFieldLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadAttribute::GetTagString()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetTagString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadAttribute::GetPromptString()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetPromptString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadAttribute::GetTextString()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetTextString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadAttribute::GetStyleName()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadAttribute::GetAlignment()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadAttribute::GetHeight()
{
	double result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadAttribute::GetRotation()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadAttribute::GetScaleFactor()
{
	double result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadAttribute::GetObliqueAngle()
{
	double result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetObliqueAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadAttribute::GetTextAlignmentPoint()
{
	VARIANT result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetTextAlignmentPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadAttribute::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadAttribute::GetNormal()
{
	VARIANT result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadAttribute::GetTextGenerationFlag()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetTextGenerationFlag(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadAttribute::GetThickness()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadAttribute::GetMode()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadAttribute::GetUpsideDown()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetUpsideDown(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttribute::GetBackward()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetBackward(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttribute::GetInvisible()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetInvisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttribute::GetConstant()
{
	BOOL result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetConstant(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttribute::GetVerify()
{
	BOOL result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetVerify(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttribute::GetPreset()
{
	BOOL result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttribute::SetPreset(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcad3DSolid properties

/////////////////////////////////////////////////////////////////////////////
// IAcad3DSolid operations

CString IAcad3DSolid::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcad3DSolid::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcad3DSolid::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcad3DSolid::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcad3DSolid::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DSolid::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcad3DSolid::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DSolid::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcad3DSolid::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcad3DSolid::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcad3DSolid::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcad3DSolid::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcad3DSolid::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcad3DSolid::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcad3DSolid::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcad3DSolid::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcad3DSolid::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcad3DSolid::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcad3DSolid::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcad3DSolid::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcad3DSolid::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcad3DSolid::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcad3DSolid::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcad3DSolid::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcad3DSolid::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcad3DSolid::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcad3DSolid::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcad3DSolid::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcad3DSolid::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcad3DSolid::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcad3DSolid::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DSolid::GetCentroid()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DSolid::GetMomentOfInertia()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DSolid::GetPrincipalDirections()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DSolid::GetPrincipalMoments()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DSolid::GetProductOfInertia()
{
	VARIANT result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcad3DSolid::GetRadiiOfGyration()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcad3DSolid::GetVolume()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcad3DSolid::Boolean(long Operation, LPDISPATCH SolidObject)
{
	static BYTE parms[] =
		VTS_I4 VTS_DISPATCH;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Operation, SolidObject);
}

LPDISPATCH IAcad3DSolid::CheckInterference(LPDISPATCH Object, BOOL CreateInterferenceSolid)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Object, CreateInterferenceSolid);
	return result;
}

LPDISPATCH IAcad3DSolid::SectionSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

LPDISPATCH IAcad3DSolid::SliceSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, BOOL Negative)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, Negative);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadRegion properties

/////////////////////////////////////////////////////////////////////////////
// IAcadRegion operations

CString IAcadRegion::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadRegion::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegion::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadRegion::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadRegion::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadRegion::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegion::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadRegion::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegion::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRegion::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegion::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRegion::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadRegion::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadRegion::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadRegion::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadRegion::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadRegion::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadRegion::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadRegion::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadRegion::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadRegion::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadRegion::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadRegion::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadRegion::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadRegion::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadRegion::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadRegion::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadRegion::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadRegion::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadRegion::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadRegion::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadRegion::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRegion::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadRegion::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

double IAcadRegion::GetArea()
{
	double result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRegion::GetCentroid()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRegion::GetMomentOfInertia()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRegion::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadRegion::GetPerimeter()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRegion::GetPrincipalDirections()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRegion::GetPrincipalMoments()
{
	VARIANT result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadRegion::GetProductOfInertia()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRegion::GetRadiiOfGyration()
{
	VARIANT result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadRegion::Boolean(long Operation, LPDISPATCH Object)
{
	static BYTE parms[] =
		VTS_I4 VTS_DISPATCH;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Operation, Object);
}

VARIANT IAcadRegion::Explode()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadCircle properties

/////////////////////////////////////////////////////////////////////////////
// IAcadCircle operations

CString IAcadCircle::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadCircle::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadCircle::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadCircle::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadCircle::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadCircle::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadCircle::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadCircle::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadCircle::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadCircle::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadCircle::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadCircle::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadCircle::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadCircle::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadCircle::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadCircle::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadCircle::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadCircle::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadCircle::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadCircle::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadCircle::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadCircle::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadCircle::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadCircle::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadCircle::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadCircle::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadCircle::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadCircle::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadCircle::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadCircle::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadCircle::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadCircle::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadCircle::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadCircle::GetCenter()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetCenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadCircle::GetRadius()
{
	double result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetRadius(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadCircle::GetDiameter()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetDiameter(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadCircle::GetCircumference()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetCircumference(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadCircle::GetArea()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetArea(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadCircle::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadCircle::GetThickness()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadCircle::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadCircle::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimAligned properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimAligned operations

CString IAcadDimAligned::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimAligned::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimAligned::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimAligned::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimAligned::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimAligned::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimAligned::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimAligned::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimAligned::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimAligned::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimAligned::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimAligned::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAligned::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAligned::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimAligned::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimAligned::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimAligned::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimAligned::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimAligned::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimAligned::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimAligned::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimAligned::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimAligned::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimAligned::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimAligned::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimAligned::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimAligned::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimAligned::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimAligned::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimAligned::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimAligned::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimAligned::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimAligned::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimAligned::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimAligned::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimAligned::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAligned::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimAligned::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimAligned::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAligned::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimAligned::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAligned::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAligned::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAligned::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimAligned::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAligned::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimAligned::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAligned::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimAligned::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimAligned::GetExtLine1Point()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtLine1Point(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadDimAligned::GetExtLine2Point()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtLine2Point(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL IAcadDimAligned::GetAltUnits()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltUnits(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimAligned::GetAltUnitsPrecision()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetAltUnitsScale()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltUnitsScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimAligned::GetAltRoundDistance()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAligned::GetAltTolerancePrecision()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetAltUnitsFormat()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimAligned::GetAltTextPrefix()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAligned::GetAltTextSuffix()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimAligned::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetExtensionLineColor()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetPrimaryUnitsPrecision()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetPrimaryUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetDimensionLineExtend()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDimensionLineExtend(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimAligned::GetExtensionLineExtend()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtensionLineExtend(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAligned::GetFit()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetFractionFormat()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetFractionFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetHorizontalTextPosition()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetHorizontalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetLinearScaleFactor()
{
	double result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetLinearScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAligned::GetUnitsFormat()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetExtensionLineWeight()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetRoundDistance()
{
	double result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimAligned::GetDimLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDimLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetDimLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDimLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetExtLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetExtLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetDimLineInside()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDimLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetTextInsideAlign()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextInsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetTextInside()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetForceLineInside()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetForceLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetTextOutsideAlign()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetTextOutsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadDimAligned::GetExtensionLineOffset()
{
	double result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetExtensionLineOffset(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimAligned::GetAltSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetAltToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetAltToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAligned::GetToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimAligned::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAligned::GetArrowhead1Type()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetArrowhead1Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAligned::GetArrowhead2Type()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetArrowhead2Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAligned::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

CString IAcadDimAligned::GetArrowhead1Block()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetArrowhead1Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAligned::GetArrowhead2Block()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAligned::SetArrowhead2Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimension properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimension operations

CString IAcadDimension::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimension::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimension::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimension::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimension::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimension::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimension::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimension::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimension::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimension::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimension::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimension::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimension::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimension::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimension::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimension::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimension::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimension::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimension::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimension::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimension::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimension::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimension::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimension::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimension::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimension::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimension::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimension::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimension::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimension::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimension::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimension::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimension::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimension::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimension::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimension::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimension::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimension::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimension::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimension::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimension::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimension::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimension::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimension::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimension::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimension::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimension::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimension::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimension::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimension::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimension::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimension::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimension::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimension::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimension::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimension::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimension::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimension::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimension::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimAngular properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimAngular operations

CString IAcadDimAngular::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimAngular::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimAngular::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimAngular::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimAngular::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimAngular::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimAngular::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimAngular::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimAngular::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimAngular::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimAngular::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimAngular::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAngular::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAngular::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimAngular::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimAngular::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimAngular::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimAngular::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimAngular::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimAngular::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimAngular::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimAngular::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimAngular::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimAngular::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimAngular::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimAngular::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimAngular::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimAngular::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimAngular::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimAngular::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimAngular::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimAngular::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimAngular::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimAngular::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimAngular::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimAngular::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAngular::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimAngular::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimAngular::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAngular::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimAngular::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAngular::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAngular::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAngular::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAngular::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimAngular::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAngular::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAngular::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimAngular::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimAngular::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimAngular::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimAngular::GetExtLine1StartPoint()
{
	VARIANT result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtLine1StartPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadDimAngular::GetExtLine1EndPoint()
{
	VARIANT result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtLine1EndPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadDimAngular::GetExtLine2StartPoint()
{
	VARIANT result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtLine2StartPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x27, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadDimAngular::GetExtLine2EndPoint()
{
	VARIANT result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtLine2EndPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadDimAngular::GetAngleFormat()
{
	long result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetAngleFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetExtensionLineColor()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAngular::GetExtensionLineExtend()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtensionLineExtend(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAngular::GetFit()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetHorizontalTextPosition()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetHorizontalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetExtensionLineWeight()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadDimAngular::GetDimLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetDimLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetDimLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetDimLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetExtLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetExtLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetDimLineInside()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetDimLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetTextInsideAlign()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextInsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetTextInside()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetForceLineInside()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetForceLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimAngular::GetTextOutsideAlign()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextOutsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimAngular::GetTextPrecision()
{
	long result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetTextPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAngular::GetExtensionLineOffset()
{
	double result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetExtensionLineOffset(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAngular::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAngular::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimAngular::GetArrowhead1Type()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetArrowhead1Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimAngular::GetArrowhead2Type()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetArrowhead2Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimAngular::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

CString IAcadDimAngular::GetArrowhead1Block()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetArrowhead1Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimAngular::GetArrowhead2Block()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimAngular::SetArrowhead2Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimDiametric properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimDiametric operations

CString IAcadDimDiametric::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimDiametric::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimDiametric::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimDiametric::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimDiametric::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimDiametric::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimDiametric::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimDiametric::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimDiametric::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimDiametric::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimDiametric::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimDiametric::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimDiametric::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimDiametric::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimDiametric::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimDiametric::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimDiametric::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimDiametric::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimDiametric::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimDiametric::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimDiametric::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimDiametric::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimDiametric::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimDiametric::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimDiametric::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimDiametric::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimDiametric::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimDiametric::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimDiametric::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimDiametric::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimDiametric::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimDiametric::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimDiametric::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimDiametric::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimDiametric::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimDiametric::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimDiametric::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimDiametric::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimDiametric::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimDiametric::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimDiametric::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimDiametric::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimDiametric::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimDiametric::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimDiametric::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimDiametric::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimDiametric::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimDiametric::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimDiametric::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadDimDiametric::SetLeaderLength(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimDiametric::GetAltUnits()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltUnits(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimDiametric::GetAltUnitsPrecision()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetAltUnitsScale()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltUnitsScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimDiametric::GetAltRoundDistance()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimDiametric::GetAltTolerancePrecision()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetAltUnitsFormat()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimDiametric::GetAltTextPrefix()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimDiametric::GetAltTextSuffix()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimDiametric::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetPrimaryUnitsPrecision()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetPrimaryUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetFractionFormat()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetFractionFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetFit()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetLinearScaleFactor()
{
	double result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetLinearScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimDiametric::GetUnitsFormat()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetRoundDistance()
{
	double result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimDiametric::GetDimLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetDimLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetDimLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetDimLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetTextInsideAlign()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextInsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetTextInside()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetForceLineInside()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetForceLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetTextOutsideAlign()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetTextOutsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimDiametric::GetCenterType()
{
	long result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetCenterType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetCenterMarkSize()
{
	double result;
	InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetCenterMarkSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimDiametric::GetAltSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetAltToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetAltToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimDiametric::GetToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimDiametric::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimDiametric::GetArrowhead1Type()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetArrowhead1Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimDiametric::GetArrowhead2Type()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetArrowhead2Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimDiametric::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

CString IAcadDimDiametric::GetArrowhead1Block()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetArrowhead1Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimDiametric::GetArrowhead2Block()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimDiametric::SetArrowhead2Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimRotated properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimRotated operations

CString IAcadDimRotated::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimRotated::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimRotated::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimRotated::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimRotated::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimRotated::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimRotated::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimRotated::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimRotated::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimRotated::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimRotated::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimRotated::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRotated::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRotated::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRotated::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimRotated::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimRotated::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimRotated::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimRotated::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimRotated::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimRotated::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimRotated::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimRotated::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimRotated::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimRotated::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimRotated::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimRotated::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimRotated::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimRotated::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimRotated::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimRotated::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimRotated::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimRotated::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimRotated::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimRotated::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimRotated::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRotated::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimRotated::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimRotated::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRotated::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimRotated::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRotated::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRotated::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRotated::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimRotated::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRotated::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimRotated::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRotated::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRotated::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltUnits()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltUnits(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimRotated::GetAltUnitsPrecision()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetAltUnitsScale()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltUnitsScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimRotated::GetAltRoundDistance()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRotated::GetAltTolerancePrecision()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetAltUnitsFormat()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimRotated::GetAltTextPrefix()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRotated::GetAltTextSuffix()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimRotated::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetExtensionLineColor()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetExtensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetPrimaryUnitsPrecision()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetPrimaryUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetDimensionLineExtend()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDimensionLineExtend(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimRotated::GetExtensionLineExtend()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetExtensionLineExtend(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRotated::GetFit()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetFractionFormat()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetFractionFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetHorizontalTextPosition()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetHorizontalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetLinearScaleFactor()
{
	double result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetLinearScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRotated::GetUnitsFormat()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetExtensionLineWeight()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetExtensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetRoundDistance()
{
	double result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRotated::GetDimLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDimLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetDimLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDimLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetExtLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetExtLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetExtLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetExtLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetDimLineInside()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDimLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetTextInsideAlign()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextInsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetTextInside()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetForceLineInside()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetForceLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetTextOutsideAlign()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetTextOutsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadDimRotated::GetExtensionLineOffset()
{
	double result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetExtensionLineOffset(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRotated::GetAltSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetAltToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetAltToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRotated::GetToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimRotated::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRotated::GetArrowhead1Type()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetArrowhead1Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRotated::GetArrowhead2Type()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetArrowhead2Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRotated::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

CString IAcadDimRotated::GetArrowhead1Block()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetArrowhead1Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRotated::GetArrowhead2Block()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRotated::SetArrowhead2Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimOrdinate properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimOrdinate operations

CString IAcadDimOrdinate::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimOrdinate::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimOrdinate::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimOrdinate::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimOrdinate::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimOrdinate::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimOrdinate::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimOrdinate::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimOrdinate::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimOrdinate::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimOrdinate::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimOrdinate::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimOrdinate::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimOrdinate::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimOrdinate::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimOrdinate::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimOrdinate::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimOrdinate::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimOrdinate::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimOrdinate::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimOrdinate::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimOrdinate::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimOrdinate::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimOrdinate::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimOrdinate::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimOrdinate::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimOrdinate::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimOrdinate::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimOrdinate::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimOrdinate::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimOrdinate::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimOrdinate::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimOrdinate::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimOrdinate::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimOrdinate::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimOrdinate::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimOrdinate::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimOrdinate::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimOrdinate::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimOrdinate::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimOrdinate::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimOrdinate::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimOrdinate::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimOrdinate::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimOrdinate::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimOrdinate::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimOrdinate::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimOrdinate::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimOrdinate::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimOrdinate::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimOrdinate::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltUnits()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltUnits(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimOrdinate::GetAltUnitsPrecision()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimOrdinate::GetAltUnitsScale()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltUnitsScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimOrdinate::GetAltRoundDistance()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimOrdinate::GetAltTolerancePrecision()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetAltUnitsFormat()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimOrdinate::GetAltTextPrefix()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimOrdinate::GetAltTextSuffix()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimOrdinate::GetExtensionLineColor()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetExtensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetPrimaryUnitsPrecision()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetPrimaryUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetFractionFormat()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetFractionFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimOrdinate::GetLinearScaleFactor()
{
	double result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetLinearScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimOrdinate::GetUnitsFormat()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimOrdinate::GetExtensionLineWeight()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetExtensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimOrdinate::GetRoundDistance()
{
	double result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimOrdinate::GetExtensionLineOffset()
{
	double result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetExtensionLineOffset(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimOrdinate::GetAltSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetAltToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetAltToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimOrdinate::GetToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadDimOrdinate::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimOrdinate::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimOrdinate::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimRadial properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimRadial operations

CString IAcadDimRadial::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimRadial::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimRadial::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimRadial::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimRadial::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimRadial::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimRadial::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimRadial::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimRadial::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimRadial::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimRadial::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimRadial::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRadial::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRadial::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRadial::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDimRadial::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDimRadial::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDimRadial::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDimRadial::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDimRadial::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDimRadial::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDimRadial::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDimRadial::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDimRadial::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDimRadial::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDimRadial::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDimRadial::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDimRadial::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDimRadial::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimRadial::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDimRadial::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDimRadial::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimRadial::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDimRadial::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDimRadial::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimRadial::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRadial::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimRadial::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimRadial::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRadial::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimRadial::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRadial::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRadial::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRadial::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimRadial::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRadial::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDimRadial::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDimRadial::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRadial::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadDimRadial::SetLeaderLength(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRadial::GetAltUnits()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltUnits(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimRadial::GetAltUnitsPrecision()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetAltUnitsScale()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltUnitsScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDimRadial::GetAltRoundDistance()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRadial::GetAltTolerancePrecision()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetAltUnitsFormat()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDimRadial::GetAltTextPrefix()
{
	CString result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDimRadial::GetAltTextSuffix()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDimRadial::GetCenterType()
{
	long result;
	InvokeHelper(0x2b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetCenterType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetCenterMarkSize()
{
	double result;
	InvokeHelper(0x2c, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetCenterMarkSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRadial::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetPrimaryUnitsPrecision()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetPrimaryUnitsPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetFractionFormat()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetFractionFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDimRadial::GetFit()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetLinearScaleFactor()
{
	double result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetLinearScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRadial::GetUnitsFormat()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetUnitsFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetRoundDistance()
{
	double result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetRoundDistance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDimRadial::GetDimLineSuppress()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetDimLineSuppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetTextInsideAlign()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextInsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetTextInside()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetForceLineInside()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetForceLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetTextOutsideAlign()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetTextOutsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x30, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x32, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x33, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x34, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x34, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x35, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x35, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x36, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x36, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetAltToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetAltToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x37, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x38, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x39, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x39, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetToleranceSuppressZeroFeet()
{
	BOOL result;
	InvokeHelper(0x3a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceSuppressZeroFeet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDimRadial::GetToleranceSuppressZeroInches()
{
	BOOL result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetToleranceSuppressZeroInches(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadDimRadial::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDimRadial::GetArrowheadType()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetArrowheadType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDimRadial::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

CString IAcadDimRadial::GetArrowheadBlock()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimRadial::SetArrowheadBlock(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadEllipse properties

/////////////////////////////////////////////////////////////////////////////
// IAcadEllipse operations

CString IAcadEllipse::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadEllipse::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadEllipse::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadEllipse::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadEllipse::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadEllipse::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadEllipse::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadEllipse::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadEllipse::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadEllipse::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadEllipse::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadEllipse::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadEllipse::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadEllipse::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadEllipse::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadEllipse::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadEllipse::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadEllipse::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadEllipse::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadEllipse::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadEllipse::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadEllipse::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadEllipse::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadEllipse::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadEllipse::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadEllipse::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadEllipse::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadEllipse::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadEllipse::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadEllipse::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadEllipse::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadEllipse::GetStartPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadEllipse::GetCenter()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetCenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadEllipse::GetEndPoint()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadEllipse::GetMajorRadius()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetMajorRadius(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadEllipse::GetMinorRadius()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetMinorRadius(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadEllipse::GetRadiusRatio()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetRadiusRatio(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadEllipse::GetStartAngle()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetStartAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadEllipse::GetEndAngle()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetEndAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadEllipse::GetStartParameter()
{
	double result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetStartParameter(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadEllipse::GetEndParameter()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetEndParameter(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadEllipse::GetMajorAxis()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetMajorAxis(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadEllipse::GetMinorAxis()
{
	VARIANT result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadEllipse::GetNormal()
{
	VARIANT result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadEllipse::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadEllipse::GetArea()
{
	double result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadEllipse::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLeader properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLeader operations

CString IAcadLeader::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLeader::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLeader::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLeader::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLeader::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLeader::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLeader::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLeader::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLeader::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLeader::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLeader::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLeader::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadLeader::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadLeader::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadLeader::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadLeader::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadLeader::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadLeader::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadLeader::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadLeader::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadLeader::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadLeader::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadLeader::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadLeader::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadLeader::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadLeader::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadLeader::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadLeader::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadLeader::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadLeader::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadLeader::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadLeader::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadLeader::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadLeader::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x40, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadLeader::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

CString IAcadLeader::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadLeader::GetType()
{
	long result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadLeader::Evaluate()
{
	InvokeHelper(0x42, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT IAcadLeader::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadLeader::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x43, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}

LPDISPATCH IAcadLeader::GetAnnotation()
{
	LPDISPATCH result;
	InvokeHelper(0x44, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetAnnotation(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x44, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadLeader::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x607, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x607, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadLeader::GetArrowheadType()
{
	long result;
	InvokeHelper(0x45, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetArrowheadType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x45, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadLeader::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadLeader::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x60e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadLeader::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadLeader::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadLeader::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadLeader::GetArrowheadBlock()
{
	CString result;
	InvokeHelper(0x46, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLeader::SetArrowheadBlock(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x46, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMText properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMText operations

CString IAcadMText::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadMText::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMText::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadMText::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadMText::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadMText::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMText::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadMText::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMText::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadMText::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMText::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadMText::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadMText::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadMText::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadMText::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadMText::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadMText::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadMText::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadMText::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadMText::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadMText::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadMText::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadMText::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadMText::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadMText::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadMText::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadMText::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadMText::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadMText::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadMText::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadMText::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadMText::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadMText::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadMText::GetTextString()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetTextString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadMText::GetStyleName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadMText::GetAttachmentPoint()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetAttachmentPoint(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadMText::GetDrawingDirection()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetDrawingDirection(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadMText::GetWidth()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMText::GetHeight()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMText::GetRotation()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadMText::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadMText::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadMText::GetLineSpacingFactor()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetLineSpacingFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadMText::GetLineSpacingStyle()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMText::SetLineSpacingStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPoint properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPoint operations

CString IAcadPoint::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPoint::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPoint::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPoint::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPoint::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPoint::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPoint::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPoint::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPoint::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPoint::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPoint::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPoint::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadPoint::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPoint::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadPoint::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPoint::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPoint::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadPoint::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadPoint::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadPoint::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPoint::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadPoint::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadPoint::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadPoint::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadPoint::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadPoint::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadPoint::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadPoint::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPoint::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadPoint::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadPoint::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPoint::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadPoint::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPoint::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadPoint::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadPoint::GetThickness()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPoint::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLWPolyline properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLWPolyline operations

CString IAcadLWPolyline::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLWPolyline::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLWPolyline::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLWPolyline::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLWPolyline::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLWPolyline::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLWPolyline::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLWPolyline::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLWPolyline::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLWPolyline::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLWPolyline::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadLWPolyline::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadLWPolyline::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadLWPolyline::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadLWPolyline::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadLWPolyline::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadLWPolyline::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadLWPolyline::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadLWPolyline::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadLWPolyline::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadLWPolyline::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadLWPolyline::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadLWPolyline::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadLWPolyline::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadLWPolyline::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadLWPolyline::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadLWPolyline::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadLWPolyline::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadLWPolyline::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadLWPolyline::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadLWPolyline::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadLWPolyline::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadLWPolyline::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadLWPolyline::GetThickness()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IAcadLWPolyline::AddVertex(long Index, const VARIANT& vertex)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, &vertex);
}

VARIANT IAcadLWPolyline::Explode()
{
	VARIANT result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadLWPolyline::GetBulge(long Index)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Index);
	return result;
}

void IAcadLWPolyline::SetBulge(long Index, double bulge)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, bulge);
}

void IAcadLWPolyline::GetWidth(long Index, double* StartWidth, double* EndWidth)
{
	static BYTE parms[] =
		VTS_I4 VTS_PR8 VTS_PR8;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, StartWidth, EndWidth);
}

void IAcadLWPolyline::SetWidth(long Index, double StartWidth, double EndWidth)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, StartWidth, EndWidth);
}

double IAcadLWPolyline::GetConstantWidth()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetConstantWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadLWPolyline::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}

double IAcadLWPolyline::GetElevation()
{
	double result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetElevation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadLWPolyline::GetArea()
{
	double result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadLWPolyline::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadLWPolyline::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}

BOOL IAcadLWPolyline::GetClosed()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetClosed(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLWPolyline::GetLinetypeGeneration()
{
	BOOL result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLWPolyline::SetLinetypeGeneration(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPolyline properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPolyline operations

CString IAcadPolyline::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPolyline::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPolyline::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPolyline::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPolyline::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolyline::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPolyline::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolyline::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPolyline::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolyline::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPolyline::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadPolyline::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPolyline::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadPolyline::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPolyline::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPolyline::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadPolyline::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadPolyline::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadPolyline::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadPolyline::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadPolyline::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadPolyline::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadPolyline::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadPolyline::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadPolyline::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadPolyline::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPolyline::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadPolyline::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadPolyline::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPolyline::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadPolyline::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPolyline::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadPolyline::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadPolyline::GetThickness()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IAcadPolyline::AppendVertex(const VARIANT& vertex)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &vertex);
}

VARIANT IAcadPolyline::Explode()
{
	VARIANT result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadPolyline::GetBulge(long Index)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Index);
	return result;
}

void IAcadPolyline::SetBulge(long Index, double bulge)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, bulge);
}

void IAcadPolyline::GetWidth(long Index, double* StartWidth, double* EndWidth)
{
	static BYTE parms[] =
		VTS_I4 VTS_PR8 VTS_PR8;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, StartWidth, EndWidth);
}

void IAcadPolyline::SetWidth(long Index, double StartWidth, double EndWidth)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_R8;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, StartWidth, EndWidth);
}

double IAcadPolyline::GetConstantWidth()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetConstantWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadPolyline::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}

double IAcadPolyline::GetElevation()
{
	double result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetElevation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadPolyline::GetType()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadPolyline::GetClosed()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetClosed(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPolyline::GetLinetypeGeneration()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolyline::SetLinetypeGeneration(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadPolyline::GetArea()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPolyline::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadPolyline::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadRay properties

/////////////////////////////////////////////////////////////////////////////
// IAcadRay operations

CString IAcadRay::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadRay::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRay::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadRay::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadRay::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadRay::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRay::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadRay::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRay::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRay::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRay::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRay::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadRay::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadRay::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadRay::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadRay::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadRay::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadRay::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadRay::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadRay::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadRay::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadRay::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadRay::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadRay::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadRay::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadRay::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadRay::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadRay::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadRay::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadRay::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadRay::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadRay::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadRay::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadRay::GetBasePoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetBasePoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadRay::GetSecondPoint()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetSecondPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadRay::GetDirectionVector()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadRay::SetDirectionVector(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadShape properties

/////////////////////////////////////////////////////////////////////////////
// IAcadShape operations

CString IAcadShape::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadShape::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadShape::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadShape::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadShape::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadShape::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadShape::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadShape::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadShape::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadShape::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadShape::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadShape::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadShape::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadShape::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadShape::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadShape::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadShape::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadShape::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadShape::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadShape::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadShape::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadShape::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadShape::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadShape::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadShape::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadShape::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadShape::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadShape::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadShape::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadShape::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadShape::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadShape::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadShape::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadShape::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadShape::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadShape::GetHeight()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadShape::GetRotation()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadShape::GetScaleFactor()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadShape::GetObliqueAngle()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetObliqueAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadShape::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadShape::GetThickness()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadShape::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadSolid properties

/////////////////////////////////////////////////////////////////////////////
// IAcadSolid operations

CString IAcadSolid::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadSolid::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSolid::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadSolid::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadSolid::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadSolid::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSolid::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadSolid::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSolid::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadSolid::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSolid::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadSolid::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadSolid::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadSolid::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadSolid::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadSolid::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadSolid::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadSolid::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadSolid::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadSolid::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadSolid::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadSolid::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadSolid::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadSolid::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadSolid::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadSolid::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadSolid::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadSolid::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadSolid::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadSolid::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadSolid::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadSolid::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadSolid::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadSolid::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadSolid::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadSolid::GetThickness()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadSolid::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadSolid::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadSolid::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadSpline properties

/////////////////////////////////////////////////////////////////////////////
// IAcadSpline operations

CString IAcadSpline::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadSpline::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSpline::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadSpline::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadSpline::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadSpline::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSpline::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadSpline::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSpline::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadSpline::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSpline::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadSpline::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadSpline::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadSpline::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadSpline::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadSpline::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadSpline::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadSpline::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadSpline::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadSpline::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadSpline::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadSpline::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadSpline::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadSpline::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadSpline::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadSpline::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadSpline::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadSpline::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadSpline::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadSpline::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadSpline::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadSpline::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadSpline::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadSpline::GetNumberOfControlPoints()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT IAcadSpline::GetControlPoints()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetControlPoints(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadSpline::GetNumberOfFitPoints()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

VARIANT IAcadSpline::GetFitPoints()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetFitPoints(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadSpline::GetDegree()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL IAcadSpline::GetClosed()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadSpline::GetIsPlanar()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadSpline::GetIsRational()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadSpline::GetIsPeriodic()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

VARIANT IAcadSpline::GetStartTangent()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetStartTangent(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadSpline::GetEndTangent()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetEndTangent(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadSpline::GetFitTolerance()
{
	double result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetFitTolerance(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadSpline::GetArea()
{
	double result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetControlPoint(long Index, const VARIANT& controlPoint)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, &controlPoint);
}

VARIANT IAcadSpline::GetControlPoint(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadSpline::SetFitPoint(long Index, const VARIANT& fitPoint)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, &fitPoint);
}

VARIANT IAcadSpline::GetFitPoint(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadSpline::SetWeight(long Index, double weight)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, weight);
}

double IAcadSpline::GetWeight(long Index)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Index);
	return result;
}

void IAcadSpline::AddFitPoint(long Index, const VARIANT& fitPoint)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, &fitPoint);
}

void IAcadSpline::DeleteFitPoint(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void IAcadSpline::ElevateOrder(long Order)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Order);
}

VARIANT IAcadSpline::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}

void IAcadSpline::PurgeFitData()
{
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadSpline::Reverse()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT IAcadSpline::GetKnots()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetKnots(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadSpline::GetWeights()
{
	VARIANT result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadSpline::SetWeights(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadText properties

/////////////////////////////////////////////////////////////////////////////
// IAcadText operations

CString IAcadText::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadText::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadText::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadText::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadText::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadText::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadText::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadText::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadText::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadText::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadText::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadText::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadText::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadText::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadText::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadText::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadText::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadText::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadText::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadText::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadText::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadText::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadText::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadText::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadText::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadText::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadText::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadText::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadText::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadText::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadText::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadText::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadText::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadText::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadText::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadText::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadText::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadText::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadText::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadText::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadText::GetTextString()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadText::SetTextString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadText::GetStyleName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadText::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadText::GetAlignment()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadText::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadText::GetHeight()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadText::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadText::GetRotation()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadText::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadText::GetScaleFactor()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadText::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadText::GetObliqueAngle()
{
	double result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadText::SetObliqueAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadText::GetTextAlignmentPoint()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadText::SetTextAlignmentPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadText::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadText::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadText::GetNormal()
{
	VARIANT result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadText::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadText::GetTextGenerationFlag()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadText::SetTextGenerationFlag(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadText::GetThickness()
{
	double result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadText::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadText::GetUpsideDown()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadText::SetUpsideDown(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadText::GetBackward()
{
	BOOL result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadText::SetBackward(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadTolerance properties

/////////////////////////////////////////////////////////////////////////////
// IAcadTolerance operations

CString IAcadTolerance::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadTolerance::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadTolerance::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadTolerance::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadTolerance::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTolerance::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadTolerance::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTolerance::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadTolerance::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTolerance::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadTolerance::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadTolerance::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadTolerance::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadTolerance::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadTolerance::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadTolerance::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadTolerance::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadTolerance::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadTolerance::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadTolerance::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadTolerance::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadTolerance::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadTolerance::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadTolerance::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadTolerance::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadTolerance::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadTolerance::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadTolerance::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadTolerance::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadTolerance::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadTolerance::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadTolerance::GetDirectionVector()
{
	VARIANT result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetDirectionVector(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadTolerance::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x51, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x51, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadTolerance::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x52, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x52, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadTolerance::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadTolerance::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadTolerance::GetTextString()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetTextString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadTolerance::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadTolerance::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadTolerance::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadTolerance::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTolerance::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadTrace properties

/////////////////////////////////////////////////////////////////////////////
// IAcadTrace operations

CString IAcadTrace::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadTrace::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTrace::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadTrace::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadTrace::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadTrace::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTrace::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadTrace::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTrace::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadTrace::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTrace::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadTrace::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadTrace::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadTrace::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadTrace::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadTrace::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadTrace::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadTrace::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadTrace::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadTrace::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadTrace::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadTrace::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadTrace::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadTrace::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadTrace::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadTrace::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadTrace::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadTrace::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadTrace::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadTrace::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadTrace::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadTrace::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadTrace::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadTrace::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadTrace::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadTrace::GetThickness()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTrace::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadTrace::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadTrace::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadXline properties

/////////////////////////////////////////////////////////////////////////////
// IAcadXline operations

CString IAcadXline::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadXline::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadXline::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadXline::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadXline::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadXline::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadXline::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadXline::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadXline::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadXline::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadXline::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadXline::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadXline::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadXline::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadXline::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadXline::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadXline::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadXline::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadXline::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadXline::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadXline::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadXline::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadXline::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadXline::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadXline::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadXline::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadXline::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadXline::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadXline::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadXline::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadXline::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadXline::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadXline::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadXline::GetBasePoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetBasePoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadXline::GetSecondPoint()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetSecondPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadXline::GetDirectionVector()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadXline::SetDirectionVector(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadXline::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadBlockReference properties

/////////////////////////////////////////////////////////////////////////////
// IAcadBlockReference operations

CString IAcadBlockReference::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadBlockReference::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadBlockReference::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadBlockReference::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadBlockReference::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlockReference::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadBlockReference::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlockReference::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadBlockReference::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlockReference::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadBlockReference::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadBlockReference::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadBlockReference::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadBlockReference::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadBlockReference::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadBlockReference::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadBlockReference::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadBlockReference::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadBlockReference::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadBlockReference::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadBlockReference::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadBlockReference::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadBlockReference::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadBlockReference::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadBlockReference::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadBlockReference::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadBlockReference::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadBlockReference::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadBlockReference::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadBlockReference::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadBlockReference::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadBlockReference::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadBlockReference::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadBlockReference::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadBlockReference::GetRotation()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadBlockReference::GetXScaleFactor()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetXScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadBlockReference::GetYScaleFactor()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetYScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadBlockReference::GetZScaleFactor()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadBlockReference::SetZScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadBlockReference::Explode()
{
	VARIANT result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadBlockReference::GetAttributes()
{
	VARIANT result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadBlockReference::GetConstantAttributes()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL IAcadBlockReference::GetHasAttributes()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadHatch properties

/////////////////////////////////////////////////////////////////////////////
// IAcadHatch operations

CString IAcadHatch::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadHatch::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadHatch::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadHatch::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadHatch::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadHatch::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadHatch::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadHatch::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadHatch::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadHatch::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadHatch::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadHatch::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadHatch::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadHatch::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadHatch::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadHatch::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadHatch::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadHatch::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadHatch::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadHatch::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadHatch::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadHatch::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadHatch::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadHatch::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadHatch::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadHatch::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadHatch::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadHatch::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadHatch::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadHatch::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadHatch::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadHatch::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadHatch::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadHatch::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadHatch::GetNumberOfLoops()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadHatch::GetPatternType()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadHatch::GetPatternName()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

double IAcadHatch::GetPatternAngle()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetPatternAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadHatch::GetPatternScale()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetPatternScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadHatch::GetPatternSpace()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetPatternSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadHatch::GetISOPenWidth()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetISOPenWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadHatch::GetPatternDouble()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetPatternDouble(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadHatch::GetElevation()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetElevation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadHatch::GetAssociativeHatch()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetAssociativeHatch(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadHatch::GetHatchStyle()
{
	long result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadHatch::SetHatchStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadHatch::SetPattern(long PatternType, LPCTSTR PatternName)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 PatternType, PatternName);
}

void IAcadHatch::AppendOuterLoop(const VARIANT& ObjectArray)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &ObjectArray);
}

void IAcadHatch::AppendInnerLoop(const VARIANT& ObjectArray)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &ObjectArray);
}

void IAcadHatch::InsertLoopAt(long Index, long LoopType, const VARIANT& ObjectArray)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, LoopType, &ObjectArray);
}

void IAcadHatch::GetLoopAt(long Index, VARIANT* ObjectArray)
{
	static BYTE parms[] =
		VTS_I4 VTS_PVARIANT;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, ObjectArray);
}

void IAcadHatch::Evaluate()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadRasterImage properties

/////////////////////////////////////////////////////////////////////////////
// IAcadRasterImage operations

CString IAcadRasterImage::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadRasterImage::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadRasterImage::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadRasterImage::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadRasterImage::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRasterImage::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadRasterImage::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRasterImage::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRasterImage::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRasterImage::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRasterImage::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadRasterImage::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadRasterImage::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadRasterImage::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadRasterImage::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadRasterImage::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadRasterImage::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadRasterImage::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadRasterImage::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadRasterImage::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadRasterImage::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadRasterImage::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadRasterImage::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadRasterImage::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadRasterImage::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadRasterImage::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadRasterImage::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadRasterImage::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadRasterImage::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadRasterImage::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadRasterImage::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRasterImage::GetBrightness()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetBrightness(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadRasterImage::GetContrast()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetContrast(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadRasterImage::GetFade()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetFade(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

VARIANT IAcadRasterImage::GetOrigin()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadRasterImage::GetRotation()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadRasterImage::GetImageWidth()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetImageWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadRasterImage::GetImageHeight()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetImageHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadRasterImage::GetName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadRasterImage::SetImageFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadRasterImage::GetImageFile()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IAcadRasterImage::GetImageVisibility()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetImageVisibility(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadRasterImage::GetClippingEnabled()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetClippingEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadRasterImage::GetTransparency()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetTransparency(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadRasterImage::ClipBoundary(const VARIANT& boundry)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &boundry);
}

double IAcadRasterImage::GetHeight()
{
	double result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double IAcadRasterImage::GetWidth()
{
	double result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

BOOL IAcadRasterImage::GetShowRotation()
{
	BOOL result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetShowRotation(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadRasterImage::GetScaleFactor()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadRasterImage::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLine properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLine operations

CString IAcadLine::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLine::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLine::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLine::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLine::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLine::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLine::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLine::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLine::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLine::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLine::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLine::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadLine::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadLine::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadLine::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadLine::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadLine::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadLine::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadLine::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadLine::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadLine::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadLine::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadLine::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadLine::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadLine::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadLine::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadLine::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadLine::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadLine::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadLine::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadLine::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadLine::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadLine::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadLine::GetStartPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetStartPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadLine::GetEndPoint()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetEndPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadLine::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadLine::GetThickness()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadLine::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadLine::Offset(double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Distance);
	return result;
}

VARIANT IAcadLine::GetDelta()
{
	VARIANT result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

double IAcadLine::GetLength()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

double IAcadLine::GetAngle()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLayout properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLayout operations

CString IAcadLayout::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLayout::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayout::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLayout::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLayout::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLayout::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayout::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLayout::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayout::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLayout::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayout::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadLayout::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadLayout::GetConfigName()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetConfigName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadLayout::GetCanonicalMediaName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetCanonicalMediaName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadLayout::GetPaperUnits()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPaperUnits(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadLayout::GetPlotViewportBorders()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotViewportBorders(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayout::GetShowPlotStyles()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetShowPlotStyles(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadLayout::GetPlotRotation()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotRotation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadLayout::GetCenterPlot()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetCenterPlot(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayout::GetPlotHidden()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotHidden(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadLayout::GetPlotType()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadLayout::GetViewToPlot()
{
	CString result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetViewToPlot(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadLayout::GetUseStandardScale()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetUseStandardScale(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadLayout::GetStandardScale()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetStandardScale(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadLayout::GetCustomScale(double* Numerator, double* Denominator)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Numerator, Denominator);
}

void IAcadLayout::SetCustomScale(double Numerator, double Denominator)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Numerator, Denominator);
}

BOOL IAcadLayout::GetScaleLineweights()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetScaleLineweights(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayout::GetPlotWithLineweights()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotWithLineweights(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayout::GetPlotViewportsFirst()
{
	BOOL result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotViewportsFirst(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadLayout::GetStyleSheet()
{
	CString result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetStyleSheet(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadLayout::GetPaperMargins(VARIANT* LowerLeft, VARIANT* UpperRight)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 LowerLeft, UpperRight);
}

void IAcadLayout::GetPaperSize(double* Width, double* Height)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Width, Height);
}

VARIANT IAcadLayout::GetPlotOrigin()
{
	VARIANT result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IAcadLayout::GetWindowToPlot(VARIANT* LowerLeft, VARIANT* UpperRight)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 LowerLeft, UpperRight);
}

void IAcadLayout::SetWindowToPlot(const VARIANT& LowerLeft, const VARIANT& UpperRight)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &LowerLeft, &UpperRight);
}

BOOL IAcadLayout::GetPlotWithPlotStyles()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetPlotWithPlotStyles(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayout::GetModelType()
{
	BOOL result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayout::CopyFrom(LPDISPATCH pPlotConfig)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pPlotConfig);
}

VARIANT IAcadLayout::GetCanonicalMediaNames()
{
	VARIANT result;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadLayout::GetPlotDeviceNames()
{
	VARIANT result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadLayout::GetPlotStyleTableNames()
{
	VARIANT result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadLayout::RefreshPlotDeviceInfo()
{
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IAcadLayout::GetLocaleMediaName(LPCTSTR Name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Name);
	return result;
}

LPDISPATCH IAcadLayout::GetBlock()
{
	LPDISPATCH result;
	InvokeHelper(0x30, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLayout::GetTabOrder()
{
	long result;
	InvokeHelper(0x31, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayout::SetTabOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x31, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPlotConfiguration properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPlotConfiguration operations

CString IAcadPlotConfiguration::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPlotConfiguration::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPlotConfiguration::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPlotConfiguration::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPlotConfiguration::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfiguration::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPlotConfiguration::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfiguration::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPlotConfiguration::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfiguration::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPlotConfiguration::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPlotConfiguration::GetConfigName()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetConfigName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPlotConfiguration::GetCanonicalMediaName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetCanonicalMediaName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPlotConfiguration::GetPaperUnits()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPaperUnits(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadPlotConfiguration::GetPlotViewportBorders()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotViewportBorders(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPlotConfiguration::GetShowPlotStyles()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetShowPlotStyles(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPlotConfiguration::GetPlotRotation()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotRotation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadPlotConfiguration::GetCenterPlot()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetCenterPlot(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPlotConfiguration::GetPlotHidden()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotHidden(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPlotConfiguration::GetPlotType()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadPlotConfiguration::GetViewToPlot()
{
	CString result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetViewToPlot(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadPlotConfiguration::GetUseStandardScale()
{
	BOOL result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetUseStandardScale(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPlotConfiguration::GetStandardScale()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetStandardScale(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadPlotConfiguration::GetCustomScale(double* Numerator, double* Denominator)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Numerator, Denominator);
}

void IAcadPlotConfiguration::SetCustomScale(double Numerator, double Denominator)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Numerator, Denominator);
}

BOOL IAcadPlotConfiguration::GetScaleLineweights()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetScaleLineweights(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPlotConfiguration::GetPlotWithLineweights()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotWithLineweights(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPlotConfiguration::GetPlotViewportsFirst()
{
	BOOL result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotViewportsFirst(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadPlotConfiguration::GetStyleSheet()
{
	CString result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetStyleSheet(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadPlotConfiguration::GetPaperMargins(VARIANT* LowerLeft, VARIANT* UpperRight)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 LowerLeft, UpperRight);
}

void IAcadPlotConfiguration::GetPaperSize(double* Width, double* Height)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Width, Height);
}

VARIANT IAcadPlotConfiguration::GetPlotOrigin()
{
	VARIANT result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

void IAcadPlotConfiguration::GetWindowToPlot(VARIANT* LowerLeft, VARIANT* UpperRight)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 LowerLeft, UpperRight);
}

void IAcadPlotConfiguration::SetWindowToPlot(const VARIANT& LowerLeft, const VARIANT& UpperRight)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &LowerLeft, &UpperRight);
}

BOOL IAcadPlotConfiguration::GetPlotWithPlotStyles()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::SetPlotWithPlotStyles(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPlotConfiguration::GetModelType()
{
	BOOL result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::CopyFrom(LPDISPATCH pPlotConfig)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pPlotConfig);
}

VARIANT IAcadPlotConfiguration::GetCanonicalMediaNames()
{
	VARIANT result;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPlotConfiguration::GetPlotDeviceNames()
{
	VARIANT result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPlotConfiguration::GetPlotStyleTableNames()
{
	VARIANT result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfiguration::RefreshPlotDeviceInfo()
{
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IAcadPlotConfiguration::GetLocaleMediaName(LPCTSTR Name)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMInsertBlock properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMInsertBlock operations

CString IAcadMInsertBlock::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadMInsertBlock::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadMInsertBlock::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadMInsertBlock::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadMInsertBlock::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMInsertBlock::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadMInsertBlock::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMInsertBlock::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadMInsertBlock::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMInsertBlock::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadMInsertBlock::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadMInsertBlock::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadMInsertBlock::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadMInsertBlock::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadMInsertBlock::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadMInsertBlock::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadMInsertBlock::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadMInsertBlock::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadMInsertBlock::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadMInsertBlock::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadMInsertBlock::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadMInsertBlock::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadMInsertBlock::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadMInsertBlock::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadMInsertBlock::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadMInsertBlock::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadMInsertBlock::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadMInsertBlock::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadMInsertBlock::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadMInsertBlock::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadMInsertBlock::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadMInsertBlock::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadMInsertBlock::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadMInsertBlock::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadMInsertBlock::GetRotation()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMInsertBlock::GetXScaleFactor()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetXScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMInsertBlock::GetYScaleFactor()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetYScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMInsertBlock::GetZScaleFactor()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetZScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadMInsertBlock::Explode()
{
	VARIANT result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadMInsertBlock::GetAttributes()
{
	VARIANT result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadMInsertBlock::GetConstantAttributes()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL IAcadMInsertBlock::GetHasAttributes()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetColumns(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadMInsertBlock::GetColumns()
{
	long result;
	InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetColumnSpacing(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x101, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMInsertBlock::GetColumnSpacing()
{
	double result;
	InvokeHelper(0x101, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x102, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadMInsertBlock::GetRows()
{
	long result;
	InvokeHelper(0x102, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMInsertBlock::SetRowSpacing(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x103, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadMInsertBlock::GetRowSpacing()
{
	double result;
	InvokeHelper(0x103, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPolyfaceMesh properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPolyfaceMesh operations

CString IAcadPolyfaceMesh::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPolyfaceMesh::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPolyfaceMesh::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPolyfaceMesh::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPolyfaceMesh::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolyfaceMesh::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPolyfaceMesh::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolyfaceMesh::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPolyfaceMesh::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPolyfaceMesh::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPolyfaceMesh::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadPolyfaceMesh::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPolyfaceMesh::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadPolyfaceMesh::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPolyfaceMesh::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPolyfaceMesh::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadPolyfaceMesh::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadPolyfaceMesh::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadPolyfaceMesh::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadPolyfaceMesh::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadPolyfaceMesh::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadPolyfaceMesh::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadPolyfaceMesh::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadPolyfaceMesh::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadPolyfaceMesh::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadPolyfaceMesh::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPolyfaceMesh::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadPolyfaceMesh::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadPolyfaceMesh::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPolyfaceMesh::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadPolyfaceMesh::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPolyfaceMesh::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadPolyfaceMesh::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPolyfaceMesh::GetCoordinate(long Index)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms,
		Index);
	return result;
}

void IAcadPolyfaceMesh::SetCoordinate(long Index, const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, &newValue);
}

long IAcadPolyfaceMesh::GetNumberOfVertices()
{
	long result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadPolyfaceMesh::GetNumberOfFaces()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMLine properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMLine operations

CString IAcadMLine::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadMLine::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMLine::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadMLine::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadMLine::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadMLine::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMLine::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadMLine::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMLine::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadMLine::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMLine::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadMLine::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadMLine::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadMLine::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadMLine::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadMLine::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadMLine::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadMLine::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadMLine::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadMLine::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadMLine::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadMLine::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadMLine::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadMLine::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadMLine::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadMLine::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadMLine::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadMLine::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadMLine::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadMLine::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadMLine::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadMLine::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadMLine::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadMLine::GetStyleName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

VARIANT IAcadMLine::GetCoordinates()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadMLine::SetCoordinates(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDim3PointAngular properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDim3PointAngular operations

CString IAcadDim3PointAngular::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDim3PointAngular::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDim3PointAngular::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDim3PointAngular::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDim3PointAngular::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDim3PointAngular::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDim3PointAngular::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDim3PointAngular::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDim3PointAngular::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDim3PointAngular::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDim3PointAngular::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDim3PointAngular::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDim3PointAngular::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDim3PointAngular::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDim3PointAngular::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDim3PointAngular::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadDim3PointAngular::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadDim3PointAngular::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadDim3PointAngular::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadDim3PointAngular::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadDim3PointAngular::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadDim3PointAngular::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadDim3PointAngular::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadDim3PointAngular::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadDim3PointAngular::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadDim3PointAngular::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDim3PointAngular::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadDim3PointAngular::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadDim3PointAngular::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDim3PointAngular::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDim3PointAngular::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDim3PointAngular::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDim3PointAngular::GetRotation()
{
	double result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDim3PointAngular::GetTextPosition()
{
	VARIANT result;
	InvokeHelper(0x603, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextPosition(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x603, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadDim3PointAngular::GetTextRotation()
{
	double result;
	InvokeHelper(0x604, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x604, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDim3PointAngular::GetTextOverride()
{
	CString result;
	InvokeHelper(0x605, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextOverride(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x605, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDim3PointAngular::GetStyleName()
{
	CString result;
	InvokeHelper(0x606, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x606, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadDim3PointAngular::GetTextColor()
{
	long result;
	InvokeHelper(0x60a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadDim3PointAngular::GetDecimalSeparator()
{
	CString result;
	InvokeHelper(0x60c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetDecimalSeparator(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDim3PointAngular::GetTextGap()
{
	double result;
	InvokeHelper(0x60d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextGap(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x60d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDim3PointAngular::GetTextPrefix()
{
	CString result;
	InvokeHelper(0x60f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextPrefix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDim3PointAngular::GetTextSuffix()
{
	CString result;
	InvokeHelper(0x610, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextSuffix(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x610, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDim3PointAngular::GetScaleFactor()
{
	double result;
	InvokeHelper(0x611, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x611, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDim3PointAngular::GetVerticalTextPosition()
{
	long result;
	InvokeHelper(0x612, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetVerticalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x612, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetTolerancePrecision()
{
	long result;
	InvokeHelper(0x613, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTolerancePrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x613, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDim3PointAngular::GetToleranceHeightScale()
{
	double result;
	InvokeHelper(0x614, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceHeightScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x614, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDim3PointAngular::GetToleranceLowerLimit()
{
	double result;
	InvokeHelper(0x615, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceLowerLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x615, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDim3PointAngular::GetTextMovement()
{
	long result;
	InvokeHelper(0x616, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextMovement(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x616, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetToleranceDisplay()
{
	long result;
	InvokeHelper(0x617, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceDisplay(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x617, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetToleranceJustification()
{
	long result;
	InvokeHelper(0x618, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceJustification(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x618, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDim3PointAngular::GetToleranceUpperLimit()
{
	double result;
	InvokeHelper(0x619, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceUpperLimit(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x619, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadDim3PointAngular::GetTextStyle()
{
	CString result;
	InvokeHelper(0x61a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextStyle(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x61a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadDim3PointAngular::GetTextHeight()
{
	double result;
	InvokeHelper(0x61b, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x61b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadDim3PointAngular::GetSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x61d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x61e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x61e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetToleranceSuppressLeadingZeros()
{
	BOOL result;
	InvokeHelper(0x621, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceSuppressLeadingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x621, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetToleranceSuppressTrailingZeros()
{
	BOOL result;
	InvokeHelper(0x622, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetToleranceSuppressTrailingZeros(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x622, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadDim3PointAngular::GetExtLine1EndPoint()
{
	VARIANT result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtLine1EndPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x26, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadDim3PointAngular::GetExtLine2EndPoint()
{
	VARIANT result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtLine2EndPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadDim3PointAngular::GetAngleVertex()
{
	VARIANT result;
	InvokeHelper(0x2d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetAngleVertex(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadDim3PointAngular::GetTextPrecision()
{
	long result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextPrecision(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x24, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetAngleFormat()
{
	long result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetAngleFormat(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x29, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetDimensionLineColor()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetDimensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetExtensionLineColor()
{
	long result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtensionLineColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDim3PointAngular::GetExtensionLineExtend()
{
	double result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtensionLineExtend(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDim3PointAngular::GetFit()
{
	long result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetFit(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetHorizontalTextPosition()
{
	long result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetHorizontalTextPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x14, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetExtensionLineWeight()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadDim3PointAngular::GetDimLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetDimLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetDimLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetDimLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetExtLine1Suppress()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtLine1Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetExtLine2Suppress()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtLine2Suppress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetDimLineInside()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetDimLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetTextInsideAlign()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextInsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetTextInside()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetForceLineInside()
{
	BOOL result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetForceLineInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDim3PointAngular::GetTextOutsideAlign()
{
	BOOL result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetTextOutsideAlign(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadDim3PointAngular::GetExtensionLineOffset()
{
	double result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetExtensionLineOffset(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDim3PointAngular::GetDimensionLineWeight()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetDimensionLineWeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDim3PointAngular::GetArrowheadSize()
{
	double result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetArrowheadSize(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDim3PointAngular::GetArrowhead1Type()
{
	long result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetArrowhead1Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDim3PointAngular::GetArrowhead2Type()
{
	long result;
	InvokeHelper(0x3f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetArrowhead2Type(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadDim3PointAngular::GetMeasurement()
{
	double result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

CString IAcadDim3PointAngular::GetArrowhead1Block()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetArrowhead1Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x41, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadDim3PointAngular::GetArrowhead2Block()
{
	CString result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDim3PointAngular::SetArrowhead2Block(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x42, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadExternalReference properties

/////////////////////////////////////////////////////////////////////////////
// IAcadExternalReference operations

CString IAcadExternalReference::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadExternalReference::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadExternalReference::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadExternalReference::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadExternalReference::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadExternalReference::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadExternalReference::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadExternalReference::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadExternalReference::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadExternalReference::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadExternalReference::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadExternalReference::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadExternalReference::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadExternalReference::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadExternalReference::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadExternalReference::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadExternalReference::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadExternalReference::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadExternalReference::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadExternalReference::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadExternalReference::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadExternalReference::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadExternalReference::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadExternalReference::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadExternalReference::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadExternalReference::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadExternalReference::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadExternalReference::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadExternalReference::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadExternalReference::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadExternalReference::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadExternalReference::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadExternalReference::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadExternalReference::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadExternalReference::GetRotation()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadExternalReference::GetXScaleFactor()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetXScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadExternalReference::GetYScaleFactor()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetYScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadExternalReference::GetZScaleFactor()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetZScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadExternalReference::Explode()
{
	VARIANT result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadExternalReference::GetAttributes()
{
	VARIANT result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadExternalReference::GetConstantAttributes()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

BOOL IAcadExternalReference::GetHasAttributes()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IAcadExternalReference::GetPath()
{
	CString result;
	InvokeHelper(0x100, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadExternalReference::SetPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x100, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPaperSpace properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPaperSpace operations

CString IAcadPaperSpace::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPaperSpace::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPaperSpace::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPaperSpace::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPaperSpace::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPaperSpace::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPaperSpace::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPaperSpace::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadPaperSpace::GetCount()
{
	long result;
	InvokeHelper(0x600, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadPaperSpace::GetName()
{
	CString result;
	InvokeHelper(0x601, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPaperSpace::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x601, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadPaperSpace::GetOrigin()
{
	VARIANT result;
	InvokeHelper(0x602, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPaperSpace::SetOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x602, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadPaperSpace::AddCustomObject(LPCTSTR ClassName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x603, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ClassName);
	return result;
}

LPDISPATCH IAcadPaperSpace::Add3DFace(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x604, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadPaperSpace::Add3DMesh(long M, long N, const VARIANT& PointsMatrix)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x605, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		M, N, &PointsMatrix);
	return result;
}

LPDISPATCH IAcadPaperSpace::Add3DPoly(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x606, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddArc(const VARIANT& Center, double Radius, double StartAngle, double EndAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x607, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, StartAngle, EndAngle);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddAttribute(double Height, long Mode, LPCTSTR Prompt, const VARIANT& InsertionPoint, LPCTSTR Tag, LPCTSTR Value)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_R8 VTS_I4 VTS_BSTR VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x608, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Height, Mode, Prompt, &InsertionPoint, Tag, Value);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddBox(const VARIANT& Origin, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x609, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Origin, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddCircle(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x60a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddCone(const VARIANT& Center, double BaseRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, BaseRadius, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddCylinder(const VARIANT& Center, double Radius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDimAligned(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& TextPosition)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &TextPosition);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDimAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDimDiametric(const VARIANT& ChordPoint, const VARIANT& FarChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x60f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ChordPoint, &FarChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDimRotated(const VARIANT& ExtLine1Point, const VARIANT& ExtLine2Point, const VARIANT& DimLineLocation, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x610, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&ExtLine1Point, &ExtLine2Point, &DimLineLocation, RotationAngle);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDimOrdinate(const VARIANT& DefinitionPoint, const VARIANT& LeaderEndPoint, long UseXAxis)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_I4;
	InvokeHelper(0x611, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&DefinitionPoint, &LeaderEndPoint, UseXAxis);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDimRadial(const VARIANT& Center, const VARIANT& ChordPoint, double LeaderLength)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x612, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &ChordPoint, LeaderLength);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddEllipse(const VARIANT& Center, const VARIANT& MajorAxis, double RadiusRatio)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x613, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, &MajorAxis, RadiusRatio);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddEllipticalCone(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x614, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddEllipticalCylinder(const VARIANT& Center, double MajorRadius, double MinorRadius, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x615, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, MajorRadius, MinorRadius, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddExtrudedSolid(LPDISPATCH Profile, double Height, double TaperAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_R8 VTS_R8;
	InvokeHelper(0x616, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Height, TaperAngle);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddExtrudedSolidAlongPath(LPDISPATCH Profile, LPDISPATCH Path)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_DISPATCH;
	InvokeHelper(0x617, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, Path);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddLeader(const VARIANT& PointsArray, LPDISPATCH Annotation, long Type)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_DISPATCH VTS_I4;
	InvokeHelper(0x618, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, Annotation, Type);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddMText(const VARIANT& InsertionPoint, double Width, LPCTSTR Text)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_BSTR;
	InvokeHelper(0x619, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Width, Text);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddPoint(const VARIANT& Point)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddLightWeightPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddPolyline(const VARIANT& VerticesList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VerticesList);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddRay(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x61d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

VARIANT IAcadPaperSpace::AddRegion(const VARIANT& ObjectList)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x61e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&ObjectList);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddRevolvedSolid(LPDISPATCH Profile, const VARIANT& AxisPoint, const VARIANT& AxisDir, double Angle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x61f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Profile, &AxisPoint, &AxisDir, Angle);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddShape(LPCTSTR Name, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x620, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddSolid(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3, const VARIANT& Point4)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x621, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3, &Point4);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddSphere(const VARIANT& Center, double Radius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x622, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Radius);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddSpline(const VARIANT& PointsArray, const VARIANT& StartTangent, const VARIANT& EndTangent)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x623, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray, &StartTangent, &EndTangent);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddText(LPCTSTR TextString, const VARIANT& InsertionPoint, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8;
	InvokeHelper(0x624, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TextString, &InsertionPoint, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddTolerance(LPCTSTR Text, const VARIANT& InsertionPoint, const VARIANT& Direction)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x625, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Text, &InsertionPoint, &Direction);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddTorus(const VARIANT& Center, double TorusRadius, double TubeRadius)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x626, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, TorusRadius, TubeRadius);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddTrace(const VARIANT& PointsArray)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x627, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&PointsArray);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddWedge(const VARIANT& Center, double Length, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x628, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Length, Width, Height);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddXline(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x629, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadPaperSpace::InsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x62a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddHatch(long PatternType, LPCTSTR PatternName, BOOL Associativity)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_BOOL;
	InvokeHelper(0x62b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PatternType, PatternName, Associativity);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddRaster(LPCTSTR imageFileName, const VARIANT& InsertionPoint, double ScaleFactor, double RotationAngle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x62c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		imageFileName, &InsertionPoint, ScaleFactor, RotationAngle);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddLine(const VARIANT& StartPoint, const VARIANT& EndPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x62d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&StartPoint, &EndPoint);
	return result;
}

BOOL IAcadPaperSpace::GetIsLayout()
{
	BOOL result;
	InvokeHelper(0x62e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::GetLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x62f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPaperSpace::GetIsXRef()
{
	BOOL result;
	InvokeHelper(0x630, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddMInsertBlock(const VARIANT& InsertionPoint, LPCTSTR Name, double Xscale, double Yscale, double Zscale, double Rotation, long NumRows, long NumColumns, long RowSpacing, long ColumnSpacing)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x631, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name, Xscale, Yscale, Zscale, Rotation, NumRows, NumColumns, RowSpacing, ColumnSpacing);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddPolyfaceMesh(const VARIANT& VertexList, const VARIANT& FaceList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x632, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList, &FaceList);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddMLine(const VARIANT& VertexList)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x633, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&VertexList);
	return result;
}

LPDISPATCH IAcadPaperSpace::AddDim3PointAngular(const VARIANT& AngleVertex, const VARIANT& FirstEndPoint, const VARIANT& SecondEndPoint, const VARIANT& TextPoint)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x634, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&AngleVertex, &FirstEndPoint, &SecondEndPoint, &TextPoint);
	return result;
}

LPDISPATCH IAcadPaperSpace::GetXRefDatabase()
{
	LPDISPATCH result;
	InvokeHelper(0x635, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPaperSpace::AttachExternalReference(LPCTSTR PathName, LPCTSTR Name, const VARIANT& InsertionPoint, double Xscale, double Yscale, double Zscale, double Rotation, BOOL bOverlay)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_VARIANT VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_BOOL;
	InvokeHelper(0x636, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		PathName, Name, &InsertionPoint, Xscale, Yscale, Zscale, Rotation, bOverlay);
	return result;
}

void IAcadPaperSpace::Unload()
{
	InvokeHelper(0x637, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPaperSpace::Reload()
{
	InvokeHelper(0x638, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPaperSpace::Bind(BOOL bPrefixName)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x639, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bPrefixName);
}

void IAcadPaperSpace::Detach()
{
	InvokeHelper(0x63a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IAcadPaperSpace::AddPViewport(const VARIANT& Center, double Width, double Height)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Center, Width, Height);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPViewport properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPViewport operations

CString IAcadPViewport::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPViewport::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPViewport::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPViewport::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPViewport::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPViewport::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPViewport::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPViewport::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPViewport::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPViewport::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPViewport::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadPViewport::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPViewport::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadPViewport::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPViewport::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPViewport::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadPViewport::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadPViewport::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadPViewport::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadPViewport::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadPViewport::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadPViewport::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadPViewport::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadPViewport::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadPViewport::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadPViewport::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadPViewport::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadPViewport::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadPViewport::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPViewport::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadPViewport::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadPViewport::GetCenter()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetCenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadPViewport::GetDirection()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetDirection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL IAcadPViewport::GetGridOn()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetGridOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadPViewport::GetHeight()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadPViewport::GetWidth()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPViewport::GetViewportOn()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetViewportOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPViewport::GetClipped()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadPViewport::GetDisplayLocked()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetDisplayLocked(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPViewport::GetStandardScale()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetStandardScale(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadPViewport::GetCustomScale()
{
	double result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetCustomScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPViewport::GetUCSPerViewport()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetUCSPerViewport(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPViewport::GetSnapBasePoint()
{
	VARIANT result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetSnapBasePoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL IAcadPViewport::GetSnapOn()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetSnapOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadPViewport::GetSnapRotationAngle()
{
	double result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetSnapRotationAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPViewport::GetUCSIconOn()
{
	BOOL result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetUCSIconOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPViewport::GetUCSIconAtOrigin()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetUCSIconAtOrigin(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadPViewport::GetGridSpacing(double* XSpacing, double* YSpacing)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadPViewport::SetGridSpacing(double XSpacing, double YSpacing)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadPViewport::GetSnapSpacing(double* XSpacing, double* YSpacing)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadPViewport::SetSnapSpacing(double XSpacing, double YSpacing)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadPViewport::Display(BOOL bStatus)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bStatus);
}

double IAcadPViewport::GetTwistAngle()
{
	double result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetTwistAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadPViewport::GetLensLength()
{
	double result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetLensLength(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadPViewport::GetRemoveHiddenLines()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetRemoveHiddenLines(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadPViewport::GetTarget()
{
	VARIANT result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetTarget(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadPViewport::GetArcSmoothness()
{
	long result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPViewport::SetArcSmoothness(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadBlocks properties

/////////////////////////////////////////////////////////////////////////////
// IAcadBlocks operations

CString IAcadBlocks::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadBlocks::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadBlocks::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadBlocks::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadBlocks::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadBlocks::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlocks::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadBlocks::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlocks::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadBlocks::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlocks::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlocks::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadBlocks::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadBlocks::Add(const VARIANT& InsertionPoint, LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&InsertionPoint, Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadGroups properties

/////////////////////////////////////////////////////////////////////////////
// IAcadGroups operations

CString IAcadGroups::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadGroups::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadGroups::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadGroups::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadGroups::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadGroups::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroups::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadGroups::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroups::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadGroups::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroups::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroups::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadGroups::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroups::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadGroup properties

/////////////////////////////////////////////////////////////////////////////
// IAcadGroup operations

CString IAcadGroup::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadGroup::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadGroup::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadGroup::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadGroup::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadGroup::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroup::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadGroup::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroup::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadGroup::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroup::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadGroup::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadGroup::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadGroup::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadGroup::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadGroup::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadGroup::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IAcadGroup::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadGroup::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

void IAcadGroup::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadGroup::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadGroup::GetName()
{
	CString result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadGroup::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadGroup::AppendItems(const VARIANT& Objects)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Objects);
}

void IAcadGroup::RemoveItems(const VARIANT& Objects)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Objects);
}

void IAcadGroup::Update()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimStyles properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimStyles operations

CString IAcadDimStyles::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimStyles::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimStyles::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimStyles::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimStyles::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimStyles::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyles::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimStyles::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyles::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimStyles::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyles::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyles::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadDimStyles::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyles::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDimStyle properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDimStyle operations

CString IAcadDimStyle::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDimStyle::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimStyle::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDimStyle::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDimStyle::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDimStyle::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyle::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDimStyle::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyle::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDimStyle::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDimStyle::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadDimStyle::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDimStyle::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadDimStyle::CopyFrom(LPDISPATCH StyleSource)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StyleSource);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLayers properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLayers operations

CString IAcadLayers::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLayers::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayers::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLayers::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLayers::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLayers::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayers::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLayers::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayers::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLayers::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayers::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayers::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadLayers::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayers::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLayer properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLayer operations

CString IAcadLayer::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLayer::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayer::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLayer::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLayer::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLayer::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayer::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLayer::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayer::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLayer::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayer::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLayer::GetColor()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadLayer::GetFreeze()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetFreeze(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayer::GetLayerOn()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetLayerOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadLayer::GetLinetype()
{
	CString result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadLayer::GetLock()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetLock(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadLayer::GetName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadLayer::GetPlottable()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetPlottable(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadLayer::GetViewportDefault()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetViewportDefault(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadLayer::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadLayer::GetLineweight()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadLayer::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLineTypes properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLineTypes operations

CString IAcadLineTypes::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLineTypes::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLineTypes::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLineTypes::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLineTypes::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLineTypes::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineTypes::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLineTypes::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineTypes::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLineTypes::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineTypes::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineTypes::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadLineTypes::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineTypes::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}

void IAcadLineTypes::Load(LPCTSTR Name, LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, FileName);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLineType properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLineType operations

CString IAcadLineType::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLineType::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLineType::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLineType::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLineType::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLineType::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineType::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLineType::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineType::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLineType::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLineType::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadLineType::GetDescription()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLineType::SetDescription(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadLineType::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLineType::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDictionaries properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDictionaries operations

CString IAcadDictionaries::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDictionaries::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDictionaries::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDictionaries::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDictionaries::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDictionaries::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionaries::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDictionaries::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionaries::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDictionaries::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionaries::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionaries::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadDictionaries::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionaries::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDictionary properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDictionary operations

CString IAcadDictionary::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDictionary::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDictionary::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadDictionary::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadDictionary::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadDictionary::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionary::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDictionary::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionary::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadDictionary::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionary::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadDictionary::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadDictionary::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH IAcadDictionary::AddObject(LPCTSTR Keyword, LPCTSTR ObjectName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Keyword, ObjectName);
	return result;
}

CString IAcadDictionary::GetName(LPDISPATCH Object)
{
	CString result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Object);
	return result;
}

LPDISPATCH IAcadDictionary::GetObject(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}

LPDISPATCH IAcadDictionary::Remove(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}

void IAcadDictionary::Rename(LPCTSTR OldName, LPCTSTR NewName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 OldName, NewName);
}

void IAcadDictionary::Replace(LPCTSTR OldName, LPDISPATCH pObj)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 OldName, pObj);
}

LPDISPATCH IAcadDictionary::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadDictionary::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDictionary::AddXRecord(LPCTSTR Keyword)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Keyword);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadXRecord properties

/////////////////////////////////////////////////////////////////////////////
// IAcadXRecord operations

CString IAcadXRecord::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadXRecord::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadXRecord::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadXRecord::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadXRecord::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadXRecord::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadXRecord::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadXRecord::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadXRecord::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadXRecord::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadXRecord::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadXRecord::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadXRecord::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadXRecord::GetXRecordData(VARIANT* XRecordDataType, VARIANT* XRecordDataValue)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XRecordDataType, XRecordDataValue);
}

void IAcadXRecord::SetXRecordData(const VARIANT& XRecordDataType, const VARIANT& XRecordDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XRecordDataType, &XRecordDataValue);
}

BOOL IAcadXRecord::GetTranslateIDs()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadXRecord::SetTranslateIDs(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadRegisteredApplications properties

/////////////////////////////////////////////////////////////////////////////
// IAcadRegisteredApplications operations

CString IAcadRegisteredApplications::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadRegisteredApplications::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegisteredApplications::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadRegisteredApplications::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadRegisteredApplications::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadRegisteredApplications::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplications::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadRegisteredApplications::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplications::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRegisteredApplications::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplications::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplications::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadRegisteredApplications::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplications::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadRegisteredApplication properties

/////////////////////////////////////////////////////////////////////////////
// IAcadRegisteredApplication operations

CString IAcadRegisteredApplication::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadRegisteredApplication::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegisteredApplication::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadRegisteredApplication::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadRegisteredApplication::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadRegisteredApplication::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplication::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadRegisteredApplication::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplication::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadRegisteredApplication::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadRegisteredApplication::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadRegisteredApplication::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadRegisteredApplication::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadTextStyles properties

/////////////////////////////////////////////////////////////////////////////
// IAcadTextStyles operations

CString IAcadTextStyles::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadTextStyles::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTextStyles::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadTextStyles::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadTextStyles::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadTextStyles::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyles::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadTextStyles::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyles::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadTextStyles::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyles::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyles::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadTextStyles::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyles::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadTextStyle properties

/////////////////////////////////////////////////////////////////////////////
// IAcadTextStyle operations

CString IAcadTextStyle::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadTextStyle::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadTextStyle::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadTextStyle::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadTextStyle::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyle::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadTextStyle::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyle::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadTextStyle::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadTextStyle::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadTextStyle::GetBigFontFile()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetBigFontFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadTextStyle::GetFontFile()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetFontFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadTextStyle::GetHeight()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadTextStyle::GetLastHeight()
{
	double result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetLastHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadTextStyle::GetName()
{
	CString result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

double IAcadTextStyle::GetObliqueAngle()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetObliqueAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadTextStyle::GetTextGenerationFlag()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetTextGenerationFlag(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double IAcadTextStyle::GetWidth()
{
	double result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadTextStyle::SetWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void IAcadTextStyle::GetFont(BSTR* TypeFace, BOOL* Bold, BOOL* Italic, long* Charset, long* PitchAndFamily)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBOOL VTS_PBOOL VTS_PI4 VTS_PI4;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 TypeFace, Bold, Italic, Charset, PitchAndFamily);
}

void IAcadTextStyle::SetFont(LPCTSTR TypeFace, BOOL Bold, BOOL Italic, long Charset, long PitchAndFamily)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_BOOL VTS_I4 VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 TypeFace, Bold, Italic, Charset, PitchAndFamily);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadUCSs properties

/////////////////////////////////////////////////////////////////////////////
// IAcadUCSs operations

CString IAcadUCSs::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadUCSs::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadUCSs::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadUCSs::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadUCSs::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadUCSs::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCSs::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadUCSs::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCSs::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadUCSs::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCSs::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCSs::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadUCSs::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCSs::Add(const VARIANT& Origin, const VARIANT& XAxisPoint, const VARIANT& YAxisPoint, LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Origin, &XAxisPoint, &YAxisPoint, Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadUCS properties

/////////////////////////////////////////////////////////////////////////////
// IAcadUCS operations

CString IAcadUCS::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadUCS::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadUCS::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadUCS::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadUCS::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadUCS::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCS::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadUCS::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCS::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadUCS::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadUCS::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadUCS::GetName()
{
	CString result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadUCS::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadUCS::GetOrigin()
{
	VARIANT result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadUCS::SetOrigin(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadUCS::GetXVector()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadUCS::SetXVector(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadUCS::GetYVector()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadUCS::SetYVector(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadUCS::GetUCSMatrix()
{
	VARIANT result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadViews properties

/////////////////////////////////////////////////////////////////////////////
// IAcadViews operations

CString IAcadViews::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadViews::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadViews::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadViews::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadViews::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadViews::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViews::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadViews::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViews::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadViews::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViews::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViews::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadViews::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViews::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadView properties

/////////////////////////////////////////////////////////////////////////////
// IAcadView operations

CString IAcadView::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadView::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadView::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadView::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadView::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadView::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadView::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadView::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadView::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadView::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadView::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadView::GetCenter()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadView::SetCenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadView::GetHeight()
{
	double result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadView::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadView::GetWidth()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadView::SetWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadView::GetTarget()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadView::SetTarget(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadView::GetDirection()
{
	VARIANT result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadView::SetDirection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadView::GetName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadView::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadViewports properties

/////////////////////////////////////////////////////////////////////////////
// IAcadViewports operations

CString IAcadViewports::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadViewports::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadViewports::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadViewports::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadViewports::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadViewports::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewports::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadViewports::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewports::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadViewports::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewports::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewports::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadViewports::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewports::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}

void IAcadViewports::DeleteConfiguration(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadViewport properties

/////////////////////////////////////////////////////////////////////////////
// IAcadViewport operations

CString IAcadViewport::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadViewport::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadViewport::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadViewport::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadViewport::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadViewport::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewport::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadViewport::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewport::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadViewport::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadViewport::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadViewport::GetCenter()
{
	VARIANT result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetCenter(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadViewport::GetHeight()
{
	double result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadViewport::GetWidth()
{
	double result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetWidth(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadViewport::GetTarget()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetTarget(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadViewport::GetDirection()
{
	VARIANT result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetDirection(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

CString IAcadViewport::GetName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadViewport::GetGridOn()
{
	BOOL result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetGridOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadViewport::GetOrthoOn()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetOrthoOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadViewport::GetSnapBasePoint()
{
	VARIANT result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetSnapBasePoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

BOOL IAcadViewport::GetSnapOn()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetSnapOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double IAcadViewport::GetSnapRotationAngle()
{
	double result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetSnapRotationAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadViewport::GetUCSIconOn()
{
	BOOL result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetUCSIconOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadViewport::GetUCSIconAtOrigin()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetUCSIconAtOrigin(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadViewport::GetLowerLeftCorner()
{
	VARIANT result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

VARIANT IAcadViewport::GetUpperRightCorner()
{
	VARIANT result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadViewport::Split(long NumWins)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumWins);
}

void IAcadViewport::GetGridSpacing(double* XSpacing, double* YSpacing)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadViewport::SetGridSpacing(double XSpacing, double YSpacing)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadViewport::GetSnapSpacing(double* XSpacing, double* YSpacing)
{
	static BYTE parms[] =
		VTS_PR8 VTS_PR8;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadViewport::SetSnapSpacing(double XSpacing, double YSpacing)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 XSpacing, YSpacing);
}

void IAcadViewport::SetView(LPDISPATCH View)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 View);
}

long IAcadViewport::GetArcSmoothness()
{
	long result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadViewport::SetArcSmoothness(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadLayouts properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLayouts operations

CString IAcadLayouts::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadLayouts::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadLayouts::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadLayouts::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadLayouts::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadLayouts::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayouts::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadLayouts::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayouts::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadLayouts::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayouts::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayouts::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadLayouts::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadLayouts::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPlotConfigurations properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPlotConfigurations operations

CString IAcadPlotConfigurations::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPlotConfigurations::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPlotConfigurations::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadPlotConfigurations::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadPlotConfigurations::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPlotConfigurations::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfigurations::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPlotConfigurations::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfigurations::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadPlotConfigurations::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfigurations::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfigurations::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadPlotConfigurations::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPlotConfigurations::Add(LPCTSTR Name, const VARIANT& ModelType)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &ModelType);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDatabasePreferences properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDatabasePreferences operations

LPDISPATCH IAcadDatabasePreferences::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDatabasePreferences::GetSolidFill()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetSolidFill(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetXRefEdit()
{
	BOOL result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetXRefEdit(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetXRefLayerVisibility()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetXRefLayerVisibility(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetOLELaunch()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetOLELaunch(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetAllowLongSymbolNames()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetAllowLongSymbolNames(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetObjectSortBySelection()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetObjectSortBySelection(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetObjectSortBySnap()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetObjectSortBySnap(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetObjectSortByRedraws()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetObjectSortByRedraws(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetObjectSortByRegens()
{
	BOOL result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetObjectSortByRegens(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetObjectSortByPlotting()
{
	BOOL result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetObjectSortByPlotting(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetObjectSortByPSOutput()
{
	BOOL result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetObjectSortByPSOutput(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadDatabasePreferences::SetContourLinesPerSurface(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDatabasePreferences::GetContourLinesPerSurface()
{
	long result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetDisplaySilhouette(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x15, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetDisplaySilhouette()
{
	BOOL result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetMaxActiveViewports(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDatabasePreferences::GetMaxActiveViewports()
{
	long result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetRenderSmoothness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x17, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDatabasePreferences::GetRenderSmoothness()
{
	double result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetSegmentPerPolyline(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDatabasePreferences::GetSegmentPerPolyline()
{
	long result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetTextFrameDisplay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetTextFrameDisplay()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDatabasePreferences::GetLineweight()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDatabasePreferences::SetLineWeightDisplay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDatabasePreferences::GetLineWeightDisplay()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadIdPair properties

/////////////////////////////////////////////////////////////////////////////
// IAcadIdPair operations

BOOL IAcadIdPair::GetIsCloned()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadIdPair::GetIsOwnerXlated()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadIdPair::GetIsPrimary()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long IAcadIdPair::GetKey()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadIdPair::GetValue()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadIdPair::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadAttributeReference properties

/////////////////////////////////////////////////////////////////////////////
// IAcadAttributeReference operations

CString IAcadAttributeReference::GetHandle()
{
	CString result;
	InvokeHelper(0x400, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadAttributeReference::GetObjectName()
{
	CString result;
	InvokeHelper(0x401, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::GetXData(LPCTSTR AppName, VARIANT* XDataType, VARIANT* XDataValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x402, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppName, XDataType, XDataValue);
}

void IAcadAttributeReference::SetXData(const VARIANT& XDataType, const VARIANT& XDataValue)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x403, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XDataType, &XDataValue);
}

void IAcadAttributeReference::Delete()
{
	InvokeHelper(0x404, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadAttributeReference::GetObjectID()
{
	long result;
	InvokeHelper(0x405, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadAttributeReference::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x406, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadAttributeReference::GetHasExtensionDictionary()
{
	BOOL result;
	InvokeHelper(0x408, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadAttributeReference::GetExtensionDictionary()
{
	LPDISPATCH result;
	InvokeHelper(0x409, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadAttributeReference::GetOwnerID()
{
	long result;
	InvokeHelper(0x40a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadAttributeReference::GetDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x40b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

long IAcadAttributeReference::GetColor()
{
	long result;
	InvokeHelper(0x500, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x500, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadAttributeReference::GetLayer()
{
	CString result;
	InvokeHelper(0x501, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x501, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadAttributeReference::GetLinetype()
{
	CString result;
	InvokeHelper(0x502, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetLinetype(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x502, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadAttributeReference::GetLinetypeScale()
{
	double result;
	InvokeHelper(0x503, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetLinetypeScale(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x503, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL IAcadAttributeReference::GetVisible()
{
	BOOL result;
	InvokeHelper(0x504, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x504, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

VARIANT IAcadAttributeReference::ArrayPolar(long NumberOfObjects, double AngleToFill, const VARIANT& CenterPoint)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_R8 VTS_VARIANT;
	InvokeHelper(0x505, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfObjects, AngleToFill, &CenterPoint);
	return result;
}

VARIANT IAcadAttributeReference::ArrayRectangular(long NumberOfRows, long NumberOfColumns, long NumberOfLevels, double DistBetweenRows, double DistBetweenCols, double DistBetweenLevels)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0x506, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		NumberOfRows, NumberOfColumns, NumberOfLevels, DistBetweenRows, DistBetweenCols, DistBetweenLevels);
	return result;
}

void IAcadAttributeReference::Highlight(BOOL HighlightFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x507, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 HighlightFlag);
}

LPDISPATCH IAcadAttributeReference::Copy()
{
	LPDISPATCH result;
	InvokeHelper(0x508, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::Move(const VARIANT& FromPoint, const VARIANT& ToPoint)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x509, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FromPoint, &ToPoint);
}

void IAcadAttributeReference::Rotate(const VARIANT& BasePoint, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, RotationAngle);
}

void IAcadAttributeReference::Rotate3D(const VARIANT& Point1, const VARIANT& Point2, double RotationAngle)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_R8;
	InvokeHelper(0x50b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point1, &Point2, RotationAngle);
}

LPDISPATCH IAcadAttributeReference::Mirror(const VARIANT& Point1, const VARIANT& Point2)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2);
	return result;
}

LPDISPATCH IAcadAttributeReference::Mirror3D(const VARIANT& Point1, const VARIANT& Point2, const VARIANT& point3)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x50d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Point1, &Point2, &point3);
	return result;
}

void IAcadAttributeReference::ScaleEntity(const VARIANT& BasePoint, double ScaleFactor)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x50e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &BasePoint, ScaleFactor);
}

void IAcadAttributeReference::TransformBy(const VARIANT& TransformationMatrix)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x50f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &TransformationMatrix);
}

void IAcadAttributeReference::Update()
{
	InvokeHelper(0x510, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadAttributeReference::GetBoundingBox(VARIANT* MinPoint, VARIANT* MaxPoint)
{
	static BYTE parms[] =
		VTS_PVARIANT VTS_PVARIANT;
	InvokeHelper(0x511, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MinPoint, MaxPoint);
}

VARIANT IAcadAttributeReference::IntersectWith(LPDISPATCH IntersectObject, long option)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_DISPATCH VTS_I4;
	InvokeHelper(0x512, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		IntersectObject, option);
	return result;
}

CString IAcadAttributeReference::GetPlotStyleName()
{
	CString result;
	InvokeHelper(0x513, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetPlotStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x513, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadAttributeReference::GetLineweight()
{
	long result;
	InvokeHelper(0x514, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetLineweight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x514, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadAttributeReference::GetHyperlinks()
{
	LPDISPATCH result;
	InvokeHelper(0x515, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

double IAcadAttributeReference::GetHeight()
{
	double result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetHeight(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadAttributeReference::GetInsertionPoint()
{
	VARIANT result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetInsertionPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

VARIANT IAcadAttributeReference::GetNormal()
{
	VARIANT result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetNormal(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

double IAcadAttributeReference::GetObliqueAngle()
{
	double result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetObliqueAngle(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadAttributeReference::GetRotation()
{
	double result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetRotation(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadAttributeReference::GetScaleFactor()
{
	double result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetScaleFactor(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadAttributeReference::GetStyleName()
{
	CString result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetStyleName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadAttributeReference::GetTagString()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetTagString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

VARIANT IAcadAttributeReference::GetTextAlignmentPoint()
{
	VARIANT result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetTextAlignmentPoint(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

long IAcadAttributeReference::GetTextGenerationFlag()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetTextGenerationFlag(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadAttributeReference::GetTextString()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetTextString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

double IAcadAttributeReference::GetThickness()
{
	double result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetThickness(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadAttributeReference::GetFieldLength()
{
	long result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetFieldLength(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadAttributeReference::GetAlignment()
{
	long result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadAttributeReference::GetUpsideDown()
{
	BOOL result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetUpsideDown(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttributeReference::GetBackward()
{
	BOOL result;
	InvokeHelper(0x12, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetBackward(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttributeReference::GetInvisible()
{
	BOOL result;
	InvokeHelper(0x13, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadAttributeReference::SetInvisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x13, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadAttributeReference::GetConstant()
{
	BOOL result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _DAcadApplicationEvents properties

/////////////////////////////////////////////////////////////////////////////
// _DAcadApplicationEvents operations


/////////////////////////////////////////////////////////////////////////////
// IAcadDocument properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDocument operations

LPDISPATCH IAcadDocument::GetModelSpace()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPaperSpace()
{
	LPDISPATCH result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetBlocks()
{
	LPDISPATCH result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

VARIANT IAcadDocument::CopyObjects(const VARIANT& Objects, const VARIANT& Owner, VARIANT* IdPairs)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_PVARIANT;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Objects, &Owner, IdPairs);
	return result;
}

LPDISPATCH IAcadDocument::GetGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetDimStyles()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetLayers()
{
	LPDISPATCH result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetLinetypes()
{
	LPDISPATCH result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetDictionaries()
{
	LPDISPATCH result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetRegisteredApplications()
{
	LPDISPATCH result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetTextStyles()
{
	LPDISPATCH result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetUserCoordinateSystems()
{
	LPDISPATCH result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetViews()
{
	LPDISPATCH result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetViewports()
{
	LPDISPATCH result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

double IAcadDocument::GetElevationModelSpace()
{
	double result;
	InvokeHelper(0xf, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetElevationModelSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0xf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double IAcadDocument::GetElevationPaperSpace()
{
	double result;
	InvokeHelper(0x10, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetElevationPaperSpace(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

VARIANT IAcadDocument::GetLimits()
{
	VARIANT result;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetLimits(const VARIANT& newValue)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x11, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 &newValue);
}

LPDISPATCH IAcadDocument::HandleToObject(LPCTSTR Handle)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Handle);
	return result;
}

LPDISPATCH IAcadDocument::ObjectIdToObject(long ObjectID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ObjectID);
	return result;
}

LPDISPATCH IAcadDocument::GetLayouts()
{
	LPDISPATCH result;
	InvokeHelper(0x14, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPlotConfigurations()
{
	LPDISPATCH result;
	InvokeHelper(0x15, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPreferences()
{
	LPDISPATCH result;
	InvokeHelper(0x16, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetPlot()
{
	LPDISPATCH result;
	InvokeHelper(0x17, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetActiveLayer()
{
	LPDISPATCH result;
	InvokeHelper(0x18, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveLayer(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x18, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveLinetype()
{
	LPDISPATCH result;
	InvokeHelper(0x19, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveLinetype(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x19, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveDimStyle()
{
	LPDISPATCH result;
	InvokeHelper(0x1a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveDimStyle(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveTextStyle()
{
	LPDISPATCH result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveTextStyle(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveUCS()
{
	LPDISPATCH result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveUCS(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveViewport()
{
	LPDISPATCH result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveViewport(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActivePViewport()
{
	LPDISPATCH result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActivePViewport(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long IAcadDocument::GetActiveSpace()
{
	long result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveSpace(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadDocument::GetSelectionSets()
{
	LPDISPATCH result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetActiveSelectionSet()
{
	LPDISPATCH result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetFullName()
{
	CString result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetName()
{
	CString result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetPath()
{
	CString result;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetObjectSnapMode()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetObjectSnapMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x25, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadDocument::GetReadOnly()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetSaved()
{
	BOOL result;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetMSpace()
{
	BOOL result;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetMSpace(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x28, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH IAcadDocument::GetUtility()
{
	LPDISPATCH result;
	InvokeHelper(0x29, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::Open(LPCTSTR FullName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FullName);
	return result;
}

void IAcadDocument::AuditInfo(BOOL FixErr)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FixErr);
}

LPDISPATCH IAcadDocument::Import(LPCTSTR FileName, const VARIANT& InsertionPoint, double ScaleFactor)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT VTS_R8;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		FileName, &InsertionPoint, ScaleFactor);
	return result;
}

void IAcadDocument::Export(LPCTSTR FileName, LPCTSTR Extension, LPDISPATCH SelectionSet)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, Extension, SelectionSet);
}

LPDISPATCH IAcadDocument::New(LPCTSTR TemplateFileName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		TemplateFileName);
	return result;
}

void IAcadDocument::Save()
{
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDocument::SaveAs(LPCTSTR FullFileName, const VARIANT& SaveAsType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullFileName, &SaveAsType);
}

void IAcadDocument::Wblock(LPCTSTR FileName, LPDISPATCH SelectionSet)
{
	static BYTE parms[] =
		VTS_BSTR VTS_DISPATCH;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, SelectionSet);
}

void IAcadDocument::PurgeAll()
{
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

VARIANT IAcadDocument::GetVariable(LPCTSTR Name)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		Name);
	return result;
}

void IAcadDocument::SetVariable(LPCTSTR Name, const VARIANT& Value)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name, &Value);
}

void IAcadDocument::LoadShapeFile(LPCTSTR FullName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FullName);
}

void IAcadDocument::Regen(long WhichViewports)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 WhichViewports);
}

LPDISPATCH IAcadDocument::GetPickfirstSelectionSet()
{
	LPDISPATCH result;
	InvokeHelper(0x37, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadDocument::GetActive()
{
	BOOL result;
	InvokeHelper(0x38, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadDocument::Activate()
{
	InvokeHelper(0x39, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDocument::Close(const VARIANT& SaveChanges, const VARIANT& FileName)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &SaveChanges, &FileName);
}

void IAcadDocument::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDocument::GetWindowState()
{
	long result;
	InvokeHelper(0x3b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDocument::GetWidth()
{
	long result;
	InvokeHelper(0x3c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadDocument::GetHeight()
{
	long result;
	InvokeHelper(0x3d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SetActiveLayout(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x3e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

LPDISPATCH IAcadDocument::GetActiveLayout()
{
	LPDISPATCH result;
	InvokeHelper(0x3e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::SendCommand(LPCTSTR Command)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x3f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Command);
}

long IAcadDocument::GetHwnd()
{
	long result;
	InvokeHelper(0x40, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadDocument::GetWindowTitle()
{
	CString result;
	InvokeHelper(0x41, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x42, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocument::GetDatabase()
{
	LPDISPATCH result;
	InvokeHelper(0x43, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadDocument::StartUndoMark()
{
	InvokeHelper(0x44, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadDocument::EndUndoMark()
{
	InvokeHelper(0x45, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPlot properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPlot operations

LPDISPATCH IAcadPlot::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadPlot::GetQuietErrorMode()
{
	BOOL result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlot::SetQuietErrorMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPlot::GetNumberOfCopies()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPlot::SetNumberOfCopies(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL IAcadPlot::GetBatchPlotProgress()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPlot::SetBatchPlotProgress(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void IAcadPlot::DisplayPlotPreview(long Preview)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Preview);
}

BOOL IAcadPlot::PlotToFile(LPCTSTR plotFile, const VARIANT& plotConfig)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		plotFile, &plotConfig);
	return result;
}

BOOL IAcadPlot::PlotToDevice(const VARIANT& plotConfig)
{
	BOOL result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		&plotConfig);
	return result;
}

void IAcadPlot::SetLayoutsToPlot(const VARIANT& layoutList)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &layoutList);
}

void IAcadPlot::StartBatchMode(long entryCount)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 entryCount);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadApplication properties

/////////////////////////////////////////////////////////////////////////////
// IAcadApplication operations

BOOL IAcadApplication::GetVisible()
{
	BOOL result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString IAcadApplication::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadApplication::GetCaption()
{
	CString result;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetActiveDocument()
{
	LPDISPATCH result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetActiveDocument(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CString IAcadApplication::GetFullName()
{
	CString result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetHeight()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetHeight(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadApplication::GetWindowLeft()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWindowLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadApplication::GetPath()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetLocaleId()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetWindowTop()
{
	long result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWindowTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadApplication::GetVersion()
{
	CString result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadApplication::GetWidth()
{
	long result;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

LPDISPATCH IAcadApplication::GetPreferences()
{
	LPDISPATCH result;
	InvokeHelper(0xe, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadApplication::GetStatusId(LPDISPATCH VportObj)
{
	BOOL result;
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x11, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, parms,
		VportObj);
	return result;
}

VARIANT IAcadApplication::ListArx()
{
	VARIANT result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
	return result;
}

void IAcadApplication::LoadArx(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

LPDISPATCH IAcadApplication::GetInterfaceObject(LPCTSTR ProgID)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ProgID);
	return result;
}

void IAcadApplication::UnloadArx(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void IAcadApplication::Update()
{
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadApplication::Quit()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IAcadApplication::GetVbe()
{
	LPDISPATCH result;
	InvokeHelper(0x1b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetMenuGroups()
{
	LPDISPATCH result;
	InvokeHelper(0x1c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadApplication::GetMenuBar()
{
	LPDISPATCH result;
	InvokeHelper(0x1d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::LoadDVB(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

void IAcadApplication::UnloadDVB(LPCTSTR Name)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Name);
}

LPDISPATCH IAcadApplication::GetDocuments()
{
	LPDISPATCH result;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::Eval(LPCTSTR Expression)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Expression);
}

long IAcadApplication::GetWindowState()
{
	long result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadApplication::SetWindowState(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void IAcadApplication::RunMacro(LPCTSTR MacroPath)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MacroPath);
}

void IAcadApplication::ZoomExtents()
{
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadApplication::ZoomAll()
{
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadApplication::ZoomCenter(const VARIANT& Center, double Magnify)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_R8;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Center, Magnify);
}

void IAcadApplication::ZoomScaled(double scale, long ScaleType)
{
	static BYTE parms[] =
		VTS_R8 VTS_I4;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 scale, ScaleType);
}

void IAcadApplication::ZoomWindow(const VARIANT& LowerLeft, const VARIANT& UpperRight)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &LowerLeft, &UpperRight);
}

void IAcadApplication::ZoomPickWindow()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IAcadApplication::GetAcadState()
{
	LPDISPATCH result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadApplication::ZoomPrevious()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferences properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferences operations

LPDISPATCH IAcadPreferences::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetFiles()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetDisplay()
{
	LPDISPATCH result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetOpenSave()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetOutput()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetSystem()
{
	LPDISPATCH result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetUser()
{
	LPDISPATCH result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetDrafting()
{
	LPDISPATCH result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetSelection()
{
	LPDISPATCH result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPreferences::GetProfiles()
{
	LPDISPATCH result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesFiles properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesFiles operations

LPDISPATCH IAcadPreferencesFiles::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetSupportPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetSupportPath()
{
	CString result;
	InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetDriversPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetDriversPath()
{
	CString result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetMenuFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetMenuFile()
{
	CString result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetHelpFilePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetHelpFilePath()
{
	CString result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetDefaultInternetURL(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetDefaultInternetURL()
{
	CString result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPreferencesFiles::GetConfigFile()
{
	CString result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPreferencesFiles::GetLicenseServer()
{
	CString result;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetTextEditor(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetTextEditor()
{
	CString result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetMainDictionary(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetMainDictionary()
{
	CString result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetCustomDictionary(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetCustomDictionary()
{
	CString result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetAltFontFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetAltFontFile()
{
	CString result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetFontFileMap(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetFontFileMap()
{
	CString result;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetPrintFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPrintFile()
{
	CString result;
	InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetPrintSpoolExecutable(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPrintSpoolExecutable()
{
	CString result;
	InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetPostScriptPrologFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPostScriptPrologFile()
{
	CString result;
	InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetPrintSpoolerPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPrintSpoolerPath()
{
	CString result;
	InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetAutoSavePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetAutoSavePath()
{
	CString result;
	InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetTemplateDwgPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetTemplateDwgPath()
{
	CString result;
	InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetLogFilePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetLogFilePath()
{
	CString result;
	InvokeHelper(0x60020023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetTempFilePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetTempFilePath()
{
	CString result;
	InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetTempXrefPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetTempXrefPath()
{
	CString result;
	InvokeHelper(0x60020027, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetTextureMapPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetTextureMapPath()
{
	CString result;
	InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetAltTabletMenuFile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetAltTabletMenuFile()
{
	CString result;
	InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetProjectFilePath(LPCTSTR ProjectName, LPCTSTR ProjectFilePath)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6002002d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ProjectName, ProjectFilePath);
}

CString IAcadPreferencesFiles::GetProjectFilePath(LPCTSTR ProjectName)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002002e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		ProjectName);
	return result;
}

void IAcadPreferencesFiles::SetPrinterConfigPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002002f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPrinterConfigPath()
{
	CString result;
	InvokeHelper(0x6002002f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetPrinterDescPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020031, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPrinterDescPath()
{
	CString result;
	InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetPrinterStyleSheetPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020033, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetPrinterStyleSheetPath()
{
	CString result;
	InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetWorkspacePath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020035, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetWorkspacePath()
{
	CString result;
	InvokeHelper(0x60020035, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesFiles::SetObjectARXPath(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020037, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesFiles::GetObjectARXPath()
{
	CString result;
	InvokeHelper(0x60020037, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesDisplay properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesDisplay operations

LPDISPATCH IAcadPreferencesDisplay::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetLayoutDisplayMargins(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetLayoutDisplayMargins()
{
	BOOL result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetLayoutDisplayPaper(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetLayoutDisplayPaper()
{
	BOOL result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetLayoutDisplayPaperShadow(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetLayoutDisplayPaperShadow()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetLayoutShowPlotSetup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetLayoutShowPlotSetup()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetLayoutCreateViewport(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetLayoutCreateViewport()
{
	BOOL result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetDisplayScrollBars(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetDisplayScrollBars()
{
	BOOL result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetDisplayScreenMenu(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetDisplayScreenMenu()
{
	BOOL result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetCursorSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDisplay::GetCursorSize()
{
	long result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetDockedVisibleLines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDisplay::GetDockedVisibleLines()
{
	long result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetShowRasterImage(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetShowRasterImage()
{
	BOOL result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetGraphicsWinModelBackgrndColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetGraphicsWinModelBackgrndColor()
{
	unsigned long result;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetModelCrosshairColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetModelCrosshairColor()
{
	unsigned long result;
	InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetGraphicsWinLayoutBackgrndColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetGraphicsWinLayoutBackgrndColor()
{
	unsigned long result;
	InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetTextWinBackgrndColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002001b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetTextWinBackgrndColor()
{
	unsigned long result;
	InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetTextWinTextColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002001d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetTextWinTextColor()
{
	unsigned long result;
	InvokeHelper(0x6002001d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetLayoutCrosshairColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002001f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetLayoutCrosshairColor()
{
	unsigned long result;
	InvokeHelper(0x6002001f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetAutoTrackingVecColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020021, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long IAcadPreferencesDisplay::GetAutoTrackingVecColor()
{
	unsigned long result;
	InvokeHelper(0x60020021, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetTextFont(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020023, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesDisplay::GetTextFont()
{
	CString result;
	InvokeHelper(0x60020023, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetTextFontStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020025, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDisplay::GetTextFontStyle()
{
	long result;
	InvokeHelper(0x60020025, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetTextFontSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020027, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDisplay::GetTextFontSize()
{
	long result;
	InvokeHelper(0x60020027, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetHistoryLines(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020029, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDisplay::GetHistoryLines()
{
	long result;
	InvokeHelper(0x60020029, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetMaxAutoCADWindow(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002002b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetMaxAutoCADWindow()
{
	BOOL result;
	InvokeHelper(0x6002002b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetDisplayLayoutTabs(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002002d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetDisplayLayoutTabs()
{
	BOOL result;
	InvokeHelper(0x6002002d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetImageFrameHighlight(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002002f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetImageFrameHighlight()
{
	BOOL result;
	InvokeHelper(0x6002002f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetTrueColorImages(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020031, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDisplay::GetTrueColorImages()
{
	BOOL result;
	InvokeHelper(0x60020031, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDisplay::SetXRefFadeIntensity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020033, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDisplay::GetXRefFadeIntensity()
{
	long result;
	InvokeHelper(0x60020033, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesOpenSave properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesOpenSave operations

LPDISPATCH IAcadPreferencesOpenSave::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetSavePreviewThumbnail(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOpenSave::GetSavePreviewThumbnail()
{
	BOOL result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetIncrementalSavePercent(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOpenSave::GetIncrementalSavePercent()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetAutoSaveInterval(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOpenSave::GetAutoSaveInterval()
{
	long result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetCreateBackup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOpenSave::GetCreateBackup()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetFullCRCValidation(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOpenSave::GetFullCRCValidation()
{
	BOOL result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetLogFileOn(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOpenSave::GetLogFileOn()
{
	BOOL result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetTempFileExtension(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesOpenSave::GetTempFileExtension()
{
	CString result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetXrefDemandLoad(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOpenSave::GetXrefDemandLoad()
{
	long result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetDemandLoadARXApp(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOpenSave::GetDemandLoadARXApp()
{
	long result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetProxyImage(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOpenSave::GetProxyImage()
{
	long result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetShowProxyDialogBox(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOpenSave::GetShowProxyDialogBox()
{
	BOOL result;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetAutoAudit(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOpenSave::GetAutoAudit()
{
	BOOL result;
	InvokeHelper(0x60020017, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOpenSave::SetSaveAsType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOpenSave::GetSaveAsType()
{
	long result;
	InvokeHelper(0x60020019, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadPreferencesOpenSave::GetMRUNumber()
{
	long result;
	InvokeHelper(0x6002001b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesOutput properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesOutput operations

LPDISPATCH IAcadPreferencesOutput::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetDefaultOutputDevice(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesOutput::GetDefaultOutputDevice()
{
	CString result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetPrinterSpoolAlert(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOutput::GetPrinterSpoolAlert()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetPrinterPaperSizeAlert(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOutput::GetPrinterPaperSizeAlert()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetPlotLegacy(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOutput::GetPlotLegacy()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetOLEQuality(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOutput::GetOLEQuality()
{
	long result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetUseLastPlotSettings(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesOutput::GetUseLastPlotSettings()
{
	BOOL result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetPlotPolicy(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesOutput::GetPlotPolicy()
{
	long result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetDefaultPlotStyleTable(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesOutput::GetDefaultPlotStyleTable()
{
	CString result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetDefaultPlotStyleForObjects(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesOutput::GetDefaultPlotStyleForObjects()
{
	CString result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesOutput::SetDefaultPlotStyleForLayer(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesOutput::GetDefaultPlotStyleForLayer()
{
	CString result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesSystem properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesSystem operations

LPDISPATCH IAcadPreferencesSystem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetSingleDocumentMode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetSingleDocumentMode()
{
	BOOL result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetDisplayOLEScale(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetDisplayOLEScale()
{
	BOOL result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetStoreSQLIndex(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetStoreSQLIndex()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetTablesReadOnly(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetTablesReadOnly()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetEnableStartupDialog(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetEnableStartupDialog()
{
	BOOL result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetBeepOnError(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetBeepOnError()
{
	BOOL result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetShowWarningMessages(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetShowWarningMessages()
{
	BOOL result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSystem::SetLoadAcadLspInAllDocuments(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSystem::GetLoadAcadLspInAllDocuments()
{
	BOOL result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesUser properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesUser operations

LPDISPATCH IAcadPreferencesUser::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetKeyboardAccelerator(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetKeyboardAccelerator()
{
	long result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetKeyboardPriority(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetKeyboardPriority()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetHyperlinkDisplayCursor(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesUser::GetHyperlinkDisplayCursor()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetHyperlinkDisplayTooltip(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesUser::GetHyperlinkDisplayTooltip()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetADCInsertUnitsDefaultSource(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetADCInsertUnitsDefaultSource()
{
	long result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetADCInsertUnitsDefaultTarget(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetADCInsertUnitsDefaultTarget()
{
	long result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetShortCutMenuDisplay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesUser::GetShortCutMenuDisplay()
{
	BOOL result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetSCMDefaultMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetSCMDefaultMode()
{
	long result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetSCMEditMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetSCMEditMode()
{
	long result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesUser::SetSCMCommandMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesUser::GetSCMCommandMode()
{
	long result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesDrafting properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesDrafting operations

LPDISPATCH IAcadPreferencesDrafting::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapMarker(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetAutoSnapMarker()
{
	BOOL result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapMagnet(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetAutoSnapMagnet()
{
	BOOL result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapTooltip(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetAutoSnapTooltip()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapAperture(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetAutoSnapAperture()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapApertureSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDrafting::GetAutoSnapApertureSize()
{
	long result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapMarkerColor(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDrafting::GetAutoSnapMarkerColor()
{
	long result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoSnapMarkerSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDrafting::GetAutoSnapMarkerSize()
{
	long result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetPolarTrackingVector(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetPolarTrackingVector()
{
	BOOL result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetFullScreenTrackingVector(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetFullScreenTrackingVector()
{
	BOOL result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAutoTrackTooltip(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesDrafting::GetAutoTrackTooltip()
{
	BOOL result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesDrafting::SetAlignmentPointAcquisition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesDrafting::GetAlignmentPointAcquisition()
{
	long result;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesSelection properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesSelection operations

LPDISPATCH IAcadPreferencesSelection::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetPickFirst(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetPickFirst()
{
	BOOL result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetPickAdd(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetPickAdd()
{
	BOOL result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetPickDrag(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetPickDrag()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetPickAuto(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetPickAuto()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetPickBoxSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesSelection::GetPickBoxSize()
{
	long result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetDisplayGrips(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetDisplayGrips()
{
	BOOL result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetDisplayGripsWithinBlocks(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetDisplayGripsWithinBlocks()
{
	BOOL result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetGripColorSelected(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesSelection::GetGripColorSelected()
{
	long result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetGripColorUnselected(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesSelection::GetGripColorUnselected()
{
	long result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetGripSize(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadPreferencesSelection::GetGripSize()
{
	long result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesSelection::SetPickGroup(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPreferencesSelection::GetPickGroup()
{
	BOOL result;
	InvokeHelper(0x60020015, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesProfiles properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPreferencesProfiles operations

LPDISPATCH IAcadPreferencesProfiles::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesProfiles::SetActiveProfile(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPreferencesProfiles::GetActiveProfile()
{
	CString result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPreferencesProfiles::ImportProfile(LPCTSTR ProfileName, LPCTSTR RegFile, BOOL IncludePathInfo)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ProfileName, RegFile, IncludePathInfo);
}

void IAcadPreferencesProfiles::ExportProfile(LPCTSTR ProfileName, LPCTSTR RegFile)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ProfileName, RegFile);
}

void IAcadPreferencesProfiles::DeleteProfile(LPCTSTR ProfileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ProfileName);
}

void IAcadPreferencesProfiles::ResetProfile(LPCTSTR Profile)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Profile);
}

void IAcadPreferencesProfiles::RenameProfile(LPCTSTR origProfileName, LPCTSTR newProfileName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 origProfileName, newProfileName);
}

void IAcadPreferencesProfiles::CopyProfile(LPCTSTR oldProfileName, LPCTSTR newProfileName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 oldProfileName, newProfileName);
}

void IAcadPreferencesProfiles::GetAllProfileNames(VARIANT* pNames)
{
	static BYTE parms[] =
		VTS_PVARIANT;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pNames);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroups properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroups operations

LPDISPATCH IAcadMenuGroups::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadMenuGroups::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroups::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroups::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroups::Load(LPCTSTR MenuFileName, const VARIANT& BaseMenu)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		MenuFileName, &BaseMenu);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroup properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMenuGroup operations

LPDISPATCH IAcadMenuGroup::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroup::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadMenuGroup::GetName()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

long IAcadMenuGroup::GetType()
{
	long result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadMenuGroup::GetMenuFileName()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroup::GetMenus()
{
	LPDISPATCH result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuGroup::GetToolbars()
{
	LPDISPATCH result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadMenuGroup::Unload()
{
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadMenuGroup::Save(long MenuFileType)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuFileType);
}

void IAcadMenuGroup::SaveAs(LPCTSTR MenuFileName, long MenuFileType)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuFileName, MenuFileType);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenus properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenus operations

LPDISPATCH IAcadPopupMenus::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadPopupMenus::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenus::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenus::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenus::Add(LPCTSTR MenuName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		MenuName);
	return result;
}

void IAcadPopupMenus::InsertMenuInMenuBar(LPCTSTR MenuName, const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuName, &Index);
}

void IAcadPopupMenus::RemoveMenuFromMenuBar(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenu properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenu operations

LPDISPATCH IAcadPopupMenu::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadPopupMenu::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenu::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenu::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenu::GetName()
{
	CString result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenu::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPopupMenu::GetNameNoMnemonic()
{
	CString result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IAcadPopupMenu::GetShortcutMenu()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IAcadPopupMenu::GetOnMenuBar()
{
	BOOL result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenu::AddMenuItem(const VARIANT& Index, LPCTSTR Label, LPCTSTR Macro)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index, Label, Macro);
	return result;
}

LPDISPATCH IAcadPopupMenu::AddSubMenu(const VARIANT& Index, LPCTSTR Label)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index, Label);
	return result;
}

LPDISPATCH IAcadPopupMenu::AddSeparator(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void IAcadPopupMenu::InsertInMenuBar(const VARIANT& Index)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Index);
}

void IAcadPopupMenu::RemoveFromMenuBar()
{
	InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IAcadPopupMenu::GetTagString()
{
	CString result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenuItem properties

/////////////////////////////////////////////////////////////////////////////
// IAcadPopupMenuItem operations

LPDISPATCH IAcadPopupMenuItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenuItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetLabel()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetLabel(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadPopupMenuItem::GetTagString()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetTagString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadPopupMenuItem::GetEnable()
{
	BOOL result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetEnable(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL IAcadPopupMenuItem::GetCheck()
{
	BOOL result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetCheck(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadPopupMenuItem::GetType()
{
	long result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadPopupMenuItem::GetSubMenu()
{
	LPDISPATCH result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetMacro()
{
	CString result;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetMacro(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadPopupMenuItem::GetIndex()
{
	long result;
	InvokeHelper(0x6002000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetCaption()
{
	CString result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadPopupMenuItem::GetHelpString()
{
	CString result;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetHelpString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadPopupMenuItem::Delete()
{
	InvokeHelper(0x60020012, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long IAcadPopupMenuItem::GetEndSubMenuLevel()
{
	long result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadPopupMenuItem::SetEndSubMenuLevel(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadToolbars properties

/////////////////////////////////////////////////////////////////////////////
// IAcadToolbars operations

LPDISPATCH IAcadToolbars::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadToolbars::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadToolbars::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadToolbars::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadToolbars::GetLargeButtons()
{
	BOOL result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadToolbars::SetLargeButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

LPDISPATCH IAcadToolbars::Add(LPCTSTR ToolbarName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		ToolbarName);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadToolbar properties

/////////////////////////////////////////////////////////////////////////////
// IAcadToolbar operations

LPDISPATCH IAcadToolbar::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadToolbar::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadToolbar::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadToolbar::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadToolbar::GetName()
{
	CString result;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadToolbar::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL IAcadToolbar::GetVisible()
{
	BOOL result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IAcadToolbar::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long IAcadToolbar::GetDockStatus()
{
	long result;
	InvokeHelper(0x60020009, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

BOOL IAcadToolbar::GetLargeButtons()
{
	BOOL result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

long IAcadToolbar::GetLeft()
{
	long result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadToolbar::SetLeft(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadToolbar::GetTop()
{
	long result;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadToolbar::SetTop(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6002000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long IAcadToolbar::GetWidth()
{
	long result;
	InvokeHelper(0x6002000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadToolbar::GetHeight()
{
	long result;
	InvokeHelper(0x60020010, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long IAcadToolbar::GetFloatingRows()
{
	long result;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void IAcadToolbar::SetFloatingRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString IAcadToolbar::GetHelpString()
{
	CString result;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadToolbar::SetHelpString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

LPDISPATCH IAcadToolbar::AddToolbarButton(const VARIANT& Index, LPCTSTR Name, LPCTSTR HelpString, LPCTSTR Macro, const VARIANT& FlyoutButton)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index, Name, HelpString, Macro, &FlyoutButton);
	return result;
}

LPDISPATCH IAcadToolbar::AddSeparator(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

void IAcadToolbar::Dock(long Side)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Side);
}

void IAcadToolbar::Float(long top, long left, long NumberFloatRows)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 top, left, NumberFloatRows);
}

void IAcadToolbar::Delete()
{
	InvokeHelper(0x60020019, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IAcadToolbar::GetTagString()
{
	CString result;
	InvokeHelper(0x6002001a, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadToolbarItem properties

/////////////////////////////////////////////////////////////////////////////
// IAcadToolbarItem operations

LPDISPATCH IAcadToolbarItem::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020000, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadToolbarItem::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadToolbarItem::GetName()
{
	CString result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadToolbarItem::SetName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString IAcadToolbarItem::GetTagString()
{
	CString result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadToolbarItem::SetTagString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadToolbarItem::GetType()
{
	long result;
	InvokeHelper(0x60020006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadToolbarItem::GetFlyout()
{
	LPDISPATCH result;
	InvokeHelper(0x60020007, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

CString IAcadToolbarItem::GetMacro()
{
	CString result;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadToolbarItem::SetMacro(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long IAcadToolbarItem::GetIndex()
{
	long result;
	InvokeHelper(0x6002000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadToolbarItem::GetHelpString()
{
	CString result;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadToolbarItem::SetHelpString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6002000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

void IAcadToolbarItem::GetBitmaps(BSTR* SmallIconName, BSTR* LargeIconName)
{
	static BYTE parms[] =
		VTS_PBSTR VTS_PBSTR;
	InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SmallIconName, LargeIconName);
}

void IAcadToolbarItem::SetBitmaps(LPCTSTR SmallIconName, LPCTSTR LargeIconName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 SmallIconName, LargeIconName);
}

void IAcadToolbarItem::AttachToolbarToFlyout(LPCTSTR MenuGroupName, LPCTSTR ToolbarName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MenuGroupName, ToolbarName);
}

void IAcadToolbarItem::Delete()
{
	InvokeHelper(0x60020010, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadMenuBar properties

/////////////////////////////////////////////////////////////////////////////
// IAcadMenuBar operations

LPDISPATCH IAcadMenuBar::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadMenuBar::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuBar::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadMenuBar::GetParent()
{
	LPDISPATCH result;
	InvokeHelper(0x60020004, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadDocuments properties

/////////////////////////////////////////////////////////////////////////////
// IAcadDocuments operations

LPDISPATCH IAcadDocuments::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadDocuments::GetCount()
{
	long result;
	InvokeHelper(0x60020002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocuments::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadDocuments::Add(const VARIANT& TemplateName)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&TemplateName);
	return result;
}

LPDISPATCH IAcadDocuments::Open(LPCTSTR Name, const VARIANT& ReadOnly)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR VTS_VARIANT;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name, &ReadOnly);
	return result;
}

void IAcadDocuments::Close()
{
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadState properties

/////////////////////////////////////////////////////////////////////////////
// IAcadState operations

LPDISPATCH IAcadState::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

BOOL IAcadState::GetIsQuiescent()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadSelectionSets properties

/////////////////////////////////////////////////////////////////////////////
// IAcadSelectionSets operations

LPDISPATCH IAcadSelectionSets::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadSelectionSets::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSelectionSets::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x60020003, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

LPDISPATCH IAcadSelectionSets::Add(LPCTSTR Name)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		Name);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IAcadSelectionSet properties

/////////////////////////////////////////////////////////////////////////////
// IAcadSelectionSet operations

LPDISPATCH IAcadSelectionSet::Item(const VARIANT& Index)
{
	LPDISPATCH result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms,
		&Index);
	return result;
}

long IAcadSelectionSet::GetCount()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

CString IAcadSelectionSet::GetName()
{
	CString result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IAcadSelectionSet::Highlight(BOOL bFlag)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bFlag);
}

void IAcadSelectionSet::Erase()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadSelectionSet::Update()
{
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

LPDISPATCH IAcadSelectionSet::GetApplication()
{
	LPDISPATCH result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
	return result;
}

void IAcadSelectionSet::AddItems(const VARIANT& pSelSet)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &pSelSet);
}

void IAcadSelectionSet::RemoveItems(const VARIANT& Objects)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Objects);
}

void IAcadSelectionSet::Clear()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IAcadSelectionSet::Select(long Mode, const VARIANT& Point1, const VARIANT& Point2, const VARIANT& FilterType, const VARIANT& FilterData)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Mode, &Point1, &Point2, &FilterType, &FilterData);
}

void IAcadSelectionSet::SelectAtPoint(const VARIANT& Point, const VARIANT& FilterType, const VARIANT& FilterData)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Point, &FilterType, &FilterData);
}

void IAcadSelectionSet::SelectByPolygon(long Mode, const VARIANT& PointsList, const VARIANT& FilterType, const VARIANT& FilterData)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Mode, &PointsList, &FilterType, &FilterData);
}

void IAcadSelectionSet::SelectOnScreen(const VARIANT& FilterType, const VARIANT& FilterData)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &FilterType, &FilterData);
}

void IAcadSelectionSet::Delete()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// IAcadUtility properties

/////////////////////////////////////////////////////////////////////////////
// IAcadUtility operations

double IAcadUtility::AngleToReal(LPCTSTR Angle, long Unit)
{
	double result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020000, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Angle, Unit);
	return result;
}

CString IAcadUtility::AngleToString(double Angle, long Unit, long precision)
{
	CString result;
	static BYTE parms[] =
		VTS_R8 VTS_I4 VTS_I4;
	InvokeHelper(0x60020001, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Angle, Unit, precision);
	return result;
}

double IAcadUtility::DistanceToReal(LPCTSTR Distance, long Unit)
{
	double result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020002, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		Distance, Unit);
	return result;
}

CString IAcadUtility::RealToString(double Value, long Unit, long precision)
{
	CString result;
	static BYTE parms[] =
		VTS_R8 VTS_I4 VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Value, Unit, precision);
	return result;
}

VARIANT IAcadUtility::TranslateCoordinates(const VARIANT& Point, long FromCoordSystem, long ToCoordSystem, long Displacement, const VARIANT& OCSNormal)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_I4 VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Point, FromCoordSystem, ToCoordSystem, Displacement, &OCSNormal);
	return result;
}

void IAcadUtility::InitializeUserInput(long Bits, const VARIANT& KeyWordList)
{
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Bits, &KeyWordList);
}

long IAcadUtility::GetInteger(const VARIANT& Prompt)
{
	long result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		&Prompt);
	return result;
}

double IAcadUtility::GetReal(const VARIANT& Prompt)
{
	double result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		&Prompt);
	return result;
}

CString IAcadUtility::GetInput()
{
	CString result;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IAcadUtility::GetKeyword(const VARIANT& Prompt)
{
	CString result;
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x60020009, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		&Prompt);
	return result;
}

CString IAcadUtility::GetString(long HasSpaces, const VARIANT& Prompt)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_VARIANT;
	InvokeHelper(0x6002000a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		HasSpaces, &Prompt);
	return result;
}

double IAcadUtility::GetAngle(const VARIANT& Point, const VARIANT& Prompt)
{
	double result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6002000b, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		&Point, &Prompt);
	return result;
}

double IAcadUtility::AngleFromXAxis(const VARIANT& StartPoint, const VARIANT& EndPoint)
{
	double result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6002000c, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		&StartPoint, &EndPoint);
	return result;
}

VARIANT IAcadUtility::GetCorner(const VARIANT& Point, const VARIANT& Prompt)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6002000d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Point, &Prompt);
	return result;
}

double IAcadUtility::GetDistance(const VARIANT& Point, const VARIANT& Prompt)
{
	double result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6002000e, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		&Point, &Prompt);
	return result;
}

double IAcadUtility::GetOrientation(const VARIANT& Point, const VARIANT& Prompt)
{
	double result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x6002000f, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		&Point, &Prompt);
	return result;
}

VARIANT IAcadUtility::GetPoint(const VARIANT& Point, const VARIANT& Prompt)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x60020010, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Point, &Prompt);
	return result;
}

VARIANT IAcadUtility::PolarPoint(const VARIANT& Point, double Angle, double Distance)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_VARIANT VTS_R8 VTS_R8;
	InvokeHelper(0x60020011, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		&Point, Angle, Distance);
	return result;
}

void IAcadUtility::GetEntity(LPDISPATCH* Object, VARIANT* PickedPoint, const VARIANT& Prompt)
{
	static BYTE parms[] =
		VTS_PDISPATCH VTS_PVARIANT VTS_VARIANT;
	InvokeHelper(0x60020013, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Object, PickedPoint, &Prompt);
}

void IAcadUtility::Prompt(LPCTSTR Message)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020014, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Message);
}

void IAcadUtility::GetSubEntity(LPDISPATCH* Object, VARIANT* PickedPoint, VARIANT* transMatrix, VARIANT* ContextData, const VARIANT& Prompt)
{
	static BYTE parms[] =
		VTS_PDISPATCH VTS_PVARIANT VTS_PVARIANT VTS_PVARIANT VTS_VARIANT;
	InvokeHelper(0x60020015, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Object, PickedPoint, transMatrix, ContextData, &Prompt);
}

BOOL IAcadUtility::IsURL(LPCTSTR URL)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020016, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		URL);
	return result;
}

void IAcadUtility::GetRemoteFile(LPCTSTR URL, BSTR* LocalFile, BOOL IgnoreCache)
{
	static BYTE parms[] =
		VTS_BSTR VTS_PBSTR VTS_BOOL;
	InvokeHelper(0x60020017, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, LocalFile, IgnoreCache);
}

void IAcadUtility::PutRemoteFile(LPCTSTR URL, LPCTSTR LocalFile)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020018, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 URL, LocalFile);
}

BOOL IAcadUtility::IsRemoteFile(LPCTSTR LocalFile, BSTR* URL)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_PBSTR;
	InvokeHelper(0x60020019, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		LocalFile, URL);
	return result;
}

BOOL IAcadUtility::LaunchBrowserDialog(BSTR* SelectedURL, LPCTSTR DialogTitle, LPCTSTR OpenButtonCaption, LPCTSTR StartPageURL, LPCTSTR RegistryRootKey, BOOL OpenButtonAlwaysEnabled)
{
	BOOL result;
	static BYTE parms[] =
		VTS_PBSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL;
	InvokeHelper(0x6002001a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		SelectedURL, DialogTitle, OpenButtonCaption, StartPageURL, RegistryRootKey, OpenButtonAlwaysEnabled);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _DAcadDocumentEvents properties

/////////////////////////////////////////////////////////////////////////////
// _DAcadDocumentEvents operations


/////////////////////////////////////////////////////////////////////////////
// IAcadLayerStateManager properties

/////////////////////////////////////////////////////////////////////////////
// IAcadLayerStateManager operations

void IAcadLayerStateManager::SetDatabase(LPDISPATCH iHostDb)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 iHostDb);
}

void IAcadLayerStateManager::SetMask(LPCTSTR bsName, long nNewValue)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bsName, nNewValue);
}

long IAcadLayerStateManager::GetMask(LPCTSTR bsName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms,
		bsName);
	return result;
}

void IAcadLayerStateManager::Save(LPCTSTR bsName, long eMask)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60020003, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsName, eMask);
}

void IAcadLayerStateManager::Restore(LPCTSTR bsName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020004, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsName);
}

void IAcadLayerStateManager::Delete(LPCTSTR bsName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsName);
}

void IAcadLayerStateManager::Rename(LPCTSTR bsName, LPCTSTR bsNewName)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020006, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsName, bsNewName);
}

void IAcadLayerStateManager::Import(LPCTSTR bsFilename)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x60020007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsFilename);
}

void IAcadLayerStateManager::Export(LPCTSTR bsName, LPCTSTR bsFilename)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR;
	InvokeHelper(0x60020008, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bsName, bsFilename);
}
