// SetGrunty.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGrunty.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGrunty

IMPLEMENT_DYNAMIC(SetGrunty, CRecordset)

SetGrunty::SetGrunty(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGrunty)
	m_ID_OBJ = 0;
	m_ID_GR = 0;
	m_NAZVA_U = _T("");
	m_NAZVA_R = _T("");
	m_TYPGR = 0;
	m_TYPGR_PCK = 0;
	m_ID_NORMATYV = 0;
	m_ID_GRCONS = 0;
	m_ID_UKLAD = 0;
	m_ID_NJU = 0;
	m_ID_GRMAIN = 0;
	m_ID_UMPOZ = 0;
	m_ID_GENEZIS = 0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGrunty::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetGrunty::GetDefaultSQL()
{
	return _T("[Grunty]");
}

void SetGrunty::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGrunty)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_GR]"), m_ID_GR);
	RFX_Text(pFX, _T("[NAZVA_U]"), m_NAZVA_U);
	RFX_Text(pFX, _T("[NAZVA_R]"), m_NAZVA_R);
	RFX_Long(pFX, _T("[TYPGR]"), m_TYPGR);
	RFX_Long(pFX, _T("[TYPGR_PCK]"), m_TYPGR_PCK);
	RFX_Long(pFX, _T("[ID_NORMATYV]"), m_ID_NORMATYV);
	RFX_Long(pFX, _T("[ID_GRCONS]"), m_ID_GRCONS);
	RFX_Long(pFX, _T("[ID_UKLAD]"), m_ID_UKLAD);
	RFX_Long(pFX, _T("[ID_NJU]"), m_ID_NJU);
	RFX_Long(pFX, _T("[ID_GRMAIN]"), m_ID_GRMAIN);
	RFX_Long(pFX, _T("[ID_UMPOZ]"), m_ID_UMPOZ);
	RFX_Long(pFX, _T("[ID_GENEZIS]"), m_ID_GENEZIS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGrunty diagnostics

#ifdef _DEBUG
void SetGrunty::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGrunty::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetGrunty::AddNewRow(long ID_OBJ, long ID_GR, CString NAZVA_U, CString NAZVA_R, long TYPGR, long TYPGR_PCK, long ID_NORMATYV, long ID_GRCONS, long ID_UKLAD, long ID_NJU, long ID_GRMAIN, long ID_UMPOZ, long ID_GENEZIS)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_GR = ID_GR;
	this->m_NAZVA_U = NAZVA_U;
	this->m_NAZVA_R = NAZVA_R;
	this->m_TYPGR = TYPGR;
	this->m_TYPGR_PCK = TYPGR_PCK;
	this->m_ID_NORMATYV = ID_NORMATYV;
	this->m_ID_GRCONS = ID_GRCONS;
	this->m_ID_UKLAD = ID_UKLAD;
	this->m_ID_NJU = ID_NJU;
	this->m_ID_GRMAIN = ID_GRMAIN;
	this->m_ID_UMPOZ = ID_UMPOZ;
	this->m_ID_GENEZIS = ID_GENEZIS;

	this->Update();
}

