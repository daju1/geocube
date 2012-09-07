// SetFizMehAllParam.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetFizMehAllParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetFizMehAllParam

IMPLEMENT_DYNAMIC(SetFizMehAllParam, CRecordset)

SetFizMehAllParam::SetFizMehAllParam(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetFizMehAllParam)
	m_ID_PARAM = 0;
	m_NAZVA_U = _T("");
	m_NAZVA_R = _T("");
	m_bDEFAULT = 0;
	m_bIN = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetFizMehAllParam::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetFizMehAllParam::GetDefaultSQL()
{
	return _T("[FizMehAllParam]");
}

void SetFizMehAllParam::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetFizMehAllParam)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_PARAM]"), m_ID_PARAM);
	RFX_Text(pFX, _T("[NAZVA_U]"), m_NAZVA_U);
	RFX_Text(pFX, _T("[NAZVA_R]"), m_NAZVA_R);
	RFX_Byte(pFX, _T("[bDEFAULT]"), m_bDEFAULT);
	RFX_Byte(pFX, _T("[bIN]"), m_bIN);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetFizMehAllParam diagnostics

#ifdef _DEBUG
void SetFizMehAllParam::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetFizMehAllParam::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
