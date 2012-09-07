// SetGenezis.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGenezis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGenezis

IMPLEMENT_DYNAMIC(SetGenezis, CRecordset)

SetGenezis::SetGenezis(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGenezis)
	m_ID_GENEZIS = 0;
	m_NAZVA_U = _T("");
	m_NAZVA_R = _T("");
	m_ID_NORMATYV = 0;
	m_ID_GRMAIN = 0;
	m_INDEX = _T("");
	m_R = 0;
	m_G = 0;
	m_B = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGenezis::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGenezis::GetDefaultSQL()
{
	return _T("[Genezis]");
}

void SetGenezis::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGenezis)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_GENEZIS]"), m_ID_GENEZIS);
	RFX_Text(pFX, _T("[NAZVA_U]"), m_NAZVA_U);
	RFX_Text(pFX, _T("[NAZVA_R]"), m_NAZVA_R);
	RFX_Long(pFX, _T("[ID_NORMATYV]"), m_ID_NORMATYV);
	RFX_Long(pFX, _T("[ID_GRMAIN]"), m_ID_GRMAIN);
	RFX_Text(pFX, _T("[INDEX]"), m_INDEX);
	RFX_Byte(pFX, _T("[R]"), m_R);
	RFX_Byte(pFX, _T("[G]"), m_G);
	RFX_Byte(pFX, _T("[B]"), m_B);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGenezis diagnostics

#ifdef _DEBUG
void SetGenezis::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGenezis::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
