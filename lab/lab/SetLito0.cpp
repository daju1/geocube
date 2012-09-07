// SetLito0.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetLito0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetLito0

IMPLEMENT_DYNAMIC(SetLito0, CRecordset)

SetLito0::SetLito0(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetLito0)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_IGE = 0;
	m_H0 = 0.0;
	m_H1 = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetLito0::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetLito0::GetDefaultSQL()
{
	return _T("[Lito0]");
}

void SetLito0::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetLito0)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	RFX_Double(pFX, _T("[H0]"), m_H0);
	RFX_Double(pFX, _T("[H1]"), m_H1);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetLito0 diagnostics

#ifdef _DEBUG
void SetLito0::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetLito0::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
