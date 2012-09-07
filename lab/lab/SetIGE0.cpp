// SetIGE0.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetIGE0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetIGE0

IMPLEMENT_DYNAMIC(SetIGE0, CRecordset)

SetIGE0::SetIGE0(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetIGE0)
	m_ID_OBJ = 0;
	m_ID_IGE = 0;
	m_ID_GR = 0;
	m_IGE = _T("");
	m_mk = 0.0;
	m_mkz = 0.0;
	m_strat = _T("");
	m_desc0 = _T("");
	m_nFields = 8;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetIGE0::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetIGE0::GetDefaultSQL()
{
	return _T("[IGE0]");
}

void SetIGE0::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetIGE0)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	RFX_Long(pFX, _T("[ID_GR]"), m_ID_GR);
	RFX_Text(pFX, _T("[IGE]"), m_IGE);
	RFX_Double(pFX, _T("[mk]"), m_mk);
	RFX_Double(pFX, _T("[mkz]"), m_mkz);
	RFX_Text(pFX, _T("[strat]"), m_strat);
	RFX_Text(pFX, _T("[desc0]"), m_desc0);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetIGE0 diagnostics

#ifdef _DEBUG
void SetIGE0::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetIGE0::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
