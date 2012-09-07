// SetPodTypyGrUserDef.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPodTypyGrUserDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGrUserDef

IMPLEMENT_DYNAMIC(SetPodTypyGrUserDef, CRecordset)

SetPodTypyGrUserDef::SetPodTypyGrUserDef(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPodTypyGrUserDef)
	m_TYPGR = 0;
	m_PODTYPGR = 0;
	m_desc = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPodTypyGrUserDef::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPodTypyGrUserDef::GetDefaultSQL()
{
	return _T("[PodTypyGrUserDef]");
}

void SetPodTypyGrUserDef::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPodTypyGrUserDef)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TYPGR]"), m_TYPGR);
	RFX_Long(pFX, _T("[PODTYPGR]"), m_PODTYPGR);
	RFX_Text(pFX, _T("[desc]"), m_desc);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGrUserDef diagnostics

#ifdef _DEBUG
void SetPodTypyGrUserDef::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPodTypyGrUserDef::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
