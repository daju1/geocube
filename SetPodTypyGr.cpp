// SetPodTypyGr.cpp : implementation file
//

#include "stdafx.h"
#include "generic.h"
#include "SetPodTypyGr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGr

IMPLEMENT_DYNAMIC(SetPodTypyGr, CRecordset)

SetPodTypyGr::SetPodTypyGr(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPodTypyGr)
	m_TYPGR = 0;
	m_PODTYPGR = 0;
	m_desc = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPodTypyGr::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPodTypyGr::GetDefaultSQL()
{
	return _T("[PodTypyGr]");
}

void SetPodTypyGr::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPodTypyGr)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TYPGR]"), m_TYPGR);
	RFX_Long(pFX, _T("[PODTYPGR]"), m_PODTYPGR);
	RFX_Text(pFX, _T("[desc]"), m_desc);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGr diagnostics

#ifdef _DEBUG
void SetPodTypyGr::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPodTypyGr::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
