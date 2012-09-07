// SetT_P.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetT_P.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetT_P

IMPLEMENT_DYNAMIC(SetT_P, CRecordset)

SetT_P::SetT_P(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetT_P)
	m_ID_OBJ = 0;
	m_ID_ROZRIZ = 0;
	m_N = 0;
	m_iv = 0;
	m_v = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetT_P::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetT_P::GetDefaultSQL()
{
	return _T("[T_P]");
}

void SetT_P::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetT_P)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_ROZRIZ]"), m_ID_ROZRIZ);
	RFX_Long(pFX, _T("[N]"), m_N);
	RFX_Long(pFX, _T("[iv]"), m_iv);
	RFX_Long(pFX, _T("[v]"), m_v);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetT_P diagnostics

#ifdef _DEBUG
void SetT_P::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetT_P::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
