// SetPtStZond.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPtStZond.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPtStZond

IMPLEMENT_DYNAMIC(SetPtStZond, CRecordset)

SetPtStZond::SetPtStZond(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPtStZond)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_UST = 0;
	m_GLYB = 0.0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPtStZond::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetPtStZond::GetDefaultSQL()
{
	return _T("[PtStZond]");
}

void SetPtStZond::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPtStZond)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_UST]"), m_ID_UST);
	RFX_Double(pFX, _T("[GLYB]"), m_GLYB);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPtStZond diagnostics

#ifdef _DEBUG
void SetPtStZond::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPtStZond::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
void SetPtStZond::AddNewRow(long ID_OBJ, long ID_KT, long ID_UST, double GLYB)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_ID_UST = ID_UST;
	this->m_GLYB = GLYB;

	this->Update();
}