// SetFundament.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetFundament.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetFundament

IMPLEMENT_DYNAMIC(SetFundament, CRecordset)

SetFundament::SetFundament(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetFundament)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PERERIZ = 0;
	m_Z = 0.0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetFundament::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetFundament::GetDefaultSQL()
{
	return _T("[Fundament]");
}

void SetFundament::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetFundament)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PERERIZ]"), m_ID_PERERIZ);
	RFX_Double(pFX, _T("[Z]"), m_Z);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetFundament diagnostics

#ifdef _DEBUG
void SetFundament::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetFundament::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
