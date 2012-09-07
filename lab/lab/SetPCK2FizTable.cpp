// SetPCK2FizTable.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPCK2FizTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPCK2FizTable

IMPLEMENT_DYNAMIC(SetPCK2FizTable, CRecordset)

SetPCK2FizTable::SetPCK2FizTable(bool bUserDefined, CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPCK2FizTable)
	m_ID_CALC_METHOD = 0;
	m_PCK = 0.0;
	m_PCB = 0.0;
	m_PAR = 0.0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	this->m_bUserDefined = bUserDefined;
}


CString SetPCK2FizTable::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPCK2FizTable::GetDefaultSQL()
{
	if (this->m_bUserDefined)
		return _T("[PCK2FizTable_UserDefined]");
	else
		return _T("[PCK2FizTable]");
}

void SetPCK2FizTable::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPCK2FizTable)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_CALC_METHOD]"), m_ID_CALC_METHOD);
	RFX_Double(pFX, _T("[PCK]"), m_PCK);
	RFX_Double(pFX, _T("[PCB]"), m_PCB);
	RFX_Double(pFX, _T("[PAR]"), m_PAR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPCK2FizTable diagnostics

#ifdef _DEBUG
void SetPCK2FizTable::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPCK2FizTable::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
