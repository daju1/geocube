// SetSurfLitoMapping.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetSurfLitoMapping.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetSurfLitoMapping

IMPLEMENT_DYNAMIC(SetSurfLitoMapping, CRecordset)

SetSurfLitoMapping::SetSurfLitoMapping(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetSurfLitoMapping)
	m_ID_OBJ = 0;
	m_ID_SURF = 0;
	m_ID_IGE = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetSurfLitoMapping::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetSurfLitoMapping::GetDefaultSQL()
{
	return _T("[SurfLitoMapping]");
}

void SetSurfLitoMapping::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetSurfLitoMapping)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetSurfLitoMapping diagnostics

#ifdef _DEBUG
void SetSurfLitoMapping::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetSurfLitoMapping::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
