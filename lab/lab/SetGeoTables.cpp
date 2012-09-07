// SetGeoTables.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGeoTables.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGeoTables

IMPLEMENT_DYNAMIC(SetGeoTables, CRecordset)

SetGeoTables::SetGeoTables(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGeoTables)
	m_ID = 0;
	m_NAZVA = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGeoTables::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetGeoTables::GetDefaultSQL()
{
	return _T("[GeoTables]");
}

void SetGeoTables::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGeoTables)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGeoTables diagnostics

#ifdef _DEBUG
void SetGeoTables::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGeoTables::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
