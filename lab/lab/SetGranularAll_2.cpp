// SetGranularAll_2.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGranularAll_2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGranularAll_2

IMPLEMENT_DYNAMIC(SetGranularAll_2, CRecordset)

SetGranularAll_2::SetGranularAll_2(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGranularAll_2)
	m_ID_GRAN = 0;
	m_NAZVA = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGranularAll_2::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGranularAll_2::GetDefaultSQL()
{
	return _T("[GranularAll_2]");
}

void SetGranularAll_2::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGranularAll_2)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_GRAN]"), m_ID_GRAN);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGranularAll_2 diagnostics

#ifdef _DEBUG
void SetGranularAll_2::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGranularAll_2::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
