// SetStZond.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetStZond.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetStZond

IMPLEMENT_DYNAMIC(SetStZond, CRecordset)

SetStZond::SetStZond(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetStZond)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_NPP = 0;
	m_TYPGR = 0;
	m_H = 0.0;
	m_q0 = 0.0;
	m_f0 = 0.0;
	m_dH = 0.0;
	m_fsr = 0.0;
	m_bSTAT = 0;
	m_ID_IGE = 0;
	m_pck = 0.0;
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetStZond::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetStZond::GetDefaultSQL()
{
	return _T("[StZond]");
}

void SetStZond::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetStZond)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Long(pFX, _T("[TYPGR]"), m_TYPGR);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Double(pFX, _T("[q0]"), m_q0);
	RFX_Double(pFX, _T("[f0]"), m_f0);
	RFX_Double(pFX, _T("[dH]"), m_dH);
	RFX_Double(pFX, _T("[fsr]"), m_fsr);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	RFX_Long(pFX, _T("[ID_IGE]"), m_ID_IGE);
	RFX_Double(pFX, _T("[pck]"), m_pck);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetStZond diagnostics

#ifdef _DEBUG
void SetStZond::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetStZond::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetStZond::AddNewRow_(long ID_OBJ, long ID_KT, long NPP, long TYPGR, double H, double q0, double f0, double dH, double fsr, BYTE bSTAT, long ID_IGE)
{
	this->AddNew();
	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_KT = ID_KT;
	this->m_NPP = NPP;
	this->m_TYPGR = TYPGR;
	this->m_H = H;
	this->m_q0 = q0;
	this->m_f0 = f0;
	this->m_dH = dH;
	this->m_fsr = fsr;
	this->m_bSTAT = bSTAT;
	this->m_ID_IGE = ID_IGE;

	this->Update();
}