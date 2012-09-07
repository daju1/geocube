// SetPodTypyGr.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPodTypyGr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPodTypyGr

IMPLEMENT_DYNAMIC(SetPodTypyGr, CRecordset)

SetPodTypyGr::SetPodTypyGr(bool bUserDefined, CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPodTypyGr)
	m_TYPGR_PCK = 0;
	m_PODTYPGR = 0;
	m_desc = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
	this->m_bUserDefined = bUserDefined;
}


CString SetPodTypyGr::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetPodTypyGr::GetDefaultSQL()
{
	if (this->m_bUserDefined)
		return _T("[PodTypyGrUserDef]");
	else
		return _T("[PodTypyGr]");
}

void SetPodTypyGr::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPodTypyGr)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[TYPGR_PCK]"), m_TYPGR_PCK);
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
long SetPodTypyGr::GetNewPodTypyGr()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_PODTYPGR > id)
				id = this->m_PODTYPGR;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}
void SetPodTypyGr::AddNewRow(long TYPGR_PCK, long PODTYPGR, CString	desc)
{
	this->AddNew();
	this->m_TYPGR_PCK = TYPGR_PCK;
	this->m_PODTYPGR = PODTYPGR;
	this->m_desc = desc;
	this->Update();
}