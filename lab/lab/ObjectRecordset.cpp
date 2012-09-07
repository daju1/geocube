// ObjectRecordset.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "ObjectRecordset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CObjectRecordset

IMPLEMENT_DYNAMIC(CObjectRecordset, CRecordset)

CObjectRecordset::CObjectRecordset(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CObjectRecordset)
	m_ID_OBJ = 0;
	m_CONTRACT = _T("");
	m_NAZVA = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CObjectRecordset::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString CObjectRecordset::GetDefaultSQL()
{
	return _T("[Objects]");
}

void CObjectRecordset::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CObjectRecordset)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Text(pFX, _T("[CONTRACT]"), m_CONTRACT);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CObjectRecordset diagnostics

#ifdef _DEBUG
void CObjectRecordset::AssertValid() const
{
	CRecordset::AssertValid();
}

void CObjectRecordset::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
