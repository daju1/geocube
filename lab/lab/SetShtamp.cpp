// SetShtamp.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetShtamp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetShtamp

IMPLEMENT_DYNAMIC(SetShtamp, CRecordset)

SetShtamp::SetShtamp(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetShtamp)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_TRYVALIST = 0.0;
	m_D = 0.0;
	m_P0 = 0.0;
	m_S0 = 0.0;
	m_Pn = 0.0;
	m_Sn = 0.0;
	m_nju = 0.0;
	m_KP = 0.0;
	m_K = 0.0;
	m_q = 0.0;
	m_ID_METHOD = 0;
	m_bSTAT = 0;
	m_nFields = 17;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetShtamp::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetShtamp::GetDefaultSQL()
{
	return _T("[Shtamp]");
}

void SetShtamp::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetShtamp)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Date(pFX, _T("[DTVYPROB]"), m_DTVYPROB);
	RFX_Double(pFX, _T("[TRYVALIST]"), m_TRYVALIST);
	RFX_Double(pFX, _T("[D]"), m_D);
	RFX_Double(pFX, _T("[P0]"), m_P0);
	RFX_Double(pFX, _T("[S0]"), m_S0);
	RFX_Double(pFX, _T("[Pn]"), m_Pn);
	RFX_Double(pFX, _T("[Sn]"), m_Sn);
	RFX_Double(pFX, _T("[nju]"), m_nju);
	RFX_Double(pFX, _T("[KP]"), m_KP);
	RFX_Double(pFX, _T("[K]"), m_K);
	RFX_Double(pFX, _T("[q]"), m_q);
	RFX_Byte(pFX, _T("[ID_METHOD]"), m_ID_METHOD);
	RFX_Byte(pFX, _T("[bSTAT]"), m_bSTAT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetShtamp diagnostics

#ifdef _DEBUG
void SetShtamp::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetShtamp::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
