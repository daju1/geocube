// SetWopt_tbl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetWopt_tbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetWopt_tbl

IMPLEMENT_DYNAMIC(SetWopt_tbl, CRecordset)

SetWopt_tbl::SetWopt_tbl(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetWopt_tbl)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_W = 0.0;
	m_Ro = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetWopt_tbl::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetWopt_tbl::GetDefaultSQL()
{
	return _T("[Wopt_tbl]");
}

void SetWopt_tbl::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetWopt_tbl)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Double(pFX, _T("[W]"), m_W);
	RFX_Double(pFX, _T("[Ro]"), m_Ro);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetWopt_tbl diagnostics

#ifdef _DEBUG
void SetWopt_tbl::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetWopt_tbl::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
