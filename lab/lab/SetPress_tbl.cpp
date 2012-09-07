// SetPress_tbl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPress_tbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPress_tbl

IMPLEMENT_DYNAMIC(SetPress_tbl, CRecordset)

SetPress_tbl::SetPress_tbl(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPress_tbl)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_SIGMA = 0.0;
	m_DH1 = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPress_tbl::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetPress_tbl::GetDefaultSQL()
{
	return _T("[Pres_tbl]");
}

void SetPress_tbl::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPress_tbl)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Double(pFX, _T("[SIGMA]"), m_SIGMA);
	RFX_Double(pFX, _T("[DH1]"), m_DH1);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPress_tbl diagnostics

#ifdef _DEBUG
void SetPress_tbl::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPress_tbl::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
