// SetProbGr2.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetProbGr2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetProbGr2

IMPLEMENT_DYNAMIC(SetProbGr2, CRecordset)

SetProbGr2::SetProbGr2(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetProbGr2)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_H = 0.0;
	m_LAB_N = 0;
	m_ID_KODPROB = 0;
	m_GRUNT_NAME = _T("");
	m_ID_GR = 0;
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetProbGr2::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetProbGr2::GetDefaultSQL()
{
	return _T("[ProbGr]");
}

void SetProbGr2::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetProbGr2)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Long(pFX, _T("[LAB_N]"), m_LAB_N);
	RFX_Long(pFX, _T("[ID_KODPROB]"), m_ID_KODPROB);
	RFX_Text(pFX, _T("[GRUNT_NAME]"), m_GRUNT_NAME);
	RFX_Long(pFX, _T("[ID_GR]"), m_ID_GR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetProbGr2 diagnostics

#ifdef _DEBUG
void SetProbGr2::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetProbGr2::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
