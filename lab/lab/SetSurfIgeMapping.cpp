// SetSurfIgeMapping.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetSurfIgeMapping.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetSurfIgeMapping

IMPLEMENT_DYNAMIC(SetSurfIgeMapping, CRecordset)

SetSurfIgeMapping::SetSurfIgeMapping(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetSurfIgeMapping)
	m_ID_OBJ = 0;
	m_ID_SURF = 0;
	m_ID_IGE = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetSurfIgeMapping::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetSurfIgeMapping::GetDefaultSQL()
{
	return _T("[SurfIgeMapping]");
}

void SetSurfIgeMapping::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetSurfIgeMapping)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetSurfIgeMapping diagnostics

#ifdef _DEBUG
void SetSurfIgeMapping::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetSurfIgeMapping::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
