// SetShtamp_detail.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetShtamp_detail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetShtamp_detail

IMPLEMENT_DYNAMIC(SetShtamp_detail, CRecordset)

SetShtamp_detail::SetShtamp_detail(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetShtamp_detail)
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


CString SetShtamp_detail::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetShtamp_detail::GetDefaultSQL()
{
	return _T("[Shtamp_Detail]");
}

void SetShtamp_detail::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetShtamp_detail)
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
// SetShtamp_detail diagnostics

#ifdef _DEBUG
void SetShtamp_detail::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetShtamp_detail::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
