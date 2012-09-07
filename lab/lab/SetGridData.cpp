// SetGridData.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGridData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGridData

IMPLEMENT_DYNAMIC(SetGridData, CRecordset)

SetGridData::SetGridData(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGridData)
	m_ID_OBJ = 0;
	m_ID_SURF = 0;
	m_ID_POINT = 0;
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGridData::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGridData::GetDefaultSQL()
{
	return _T("[Griddata]");
}

void SetGridData::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGridData)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Long(pFX, _T("[ID_POINT]"), m_ID_POINT);
	RFX_Double(pFX, _T("[X]"), m_X);
	RFX_Double(pFX, _T("[Y]"), m_Y);
	RFX_Double(pFX, _T("[Z]"), m_Z);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGridData diagnostics

#ifdef _DEBUG
void SetGridData::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGridData::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
