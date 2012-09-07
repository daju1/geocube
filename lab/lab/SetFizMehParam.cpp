// SetFizMehParam.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetFizMehParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetFizMehParam

IMPLEMENT_DYNAMIC(SetFizMehParam, CRecordset)

SetFizMehParam::SetFizMehParam(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetFizMehParam)
	m_ID_OBJ = 0;
	m_ID_PARAM = 0;
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetFizMehParam::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetFizMehParam::GetDefaultSQL()
{
	return _T("[FizMehParam]");
}

void SetFizMehParam::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetFizMehParam)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_PARAM]"), m_ID_PARAM);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetFizMehParam diagnostics

#ifdef _DEBUG
void SetFizMehParam::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetFizMehParam::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
