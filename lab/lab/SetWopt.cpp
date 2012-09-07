// SetWopt.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetWopt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetWopt

IMPLEMENT_DYNAMIC(SetWopt, CRecordset)

SetWopt::SetWopt(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetWopt)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_Wopt = 0.0;
	m_Rod_max = 0.0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetWopt::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetWopt::GetDefaultSQL()
{
	return _T("[Wopt]");
}

void SetWopt::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetWopt)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Date(pFX, _T("[DTVYPROB]"), m_DTVYPROB);
	RFX_Double(pFX, _T("[Wopt]"), m_Wopt);
	RFX_Double(pFX, _T("[Rod_max]"), m_Rod_max);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetWopt diagnostics

#ifdef _DEBUG
void SetWopt::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetWopt::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
