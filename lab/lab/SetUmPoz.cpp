// SetUmPoz.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetUmPoz.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetUmPoz

IMPLEMENT_DYNAMIC(SetUmPoz, CRecordset)

SetUmPoz::SetUmPoz(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetUmPoz)
	m_ID_UMPOZ = 0;
	m_UMPOZ = _T("");
	m_HATCHACAD = _T("");
	m_Angle = 0.0;
	m_Scale = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetUmPoz::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetUmPoz::GetDefaultSQL()
{
	return _T("[Umpoz]");
}

void SetUmPoz::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetUmPoz)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_UMPOZ]"), m_ID_UMPOZ);
	RFX_Text(pFX, _T("[UMPOZ]"), m_UMPOZ);
	RFX_Text(pFX, _T("[HATCHACAD]"), m_HATCHACAD);
	RFX_Double(pFX, _T("[Angle]"), m_Angle);
	RFX_Double(pFX, _T("[Scale]"), m_Scale);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetUmPoz diagnostics

#ifdef _DEBUG
void SetUmPoz::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetUmPoz::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
