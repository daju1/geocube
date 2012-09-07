// SetPres.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPres

IMPLEMENT_DYNAMIC(SetPres, CRecordset)

SetPres::SetPres(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPres)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_L = 0.0;
	m_b = 0.0;
	m_P0 = 0.0;
	m_S0 = 0.0;
	m_Pn = 0.0;
	m_Sn = 0.0;
	m_nju = 0.0;
	m_K = 0.0;
	m_w = 0.0;
	m_bSTAT = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPres::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetPres::GetDefaultSQL()
{
	return _T("[Pres]");
}

void SetPres::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPres)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Date(pFX, _T("[DTVYPROB]"), m_DTVYPROB);
	RFX_Double(pFX, _T("[L]"), m_L);
	RFX_Double(pFX, _T("[b]"), m_b);
	RFX_Double(pFX, _T("[P0]"), m_P0);
	RFX_Double(pFX, _T("[S0]"), m_S0);
	RFX_Double(pFX, _T("[Pn]"), m_Pn);
	RFX_Double(pFX, _T("[Sn]"), m_Sn);
	RFX_Double(pFX, _T("[nju]"), m_nju);
	RFX_Double(pFX, _T("[K]"), m_K);
	RFX_Double(pFX, _T("[w]"), m_w);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPres diagnostics

#ifdef _DEBUG
void SetPres::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPres::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
