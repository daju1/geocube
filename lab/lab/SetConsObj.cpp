// SetConsObj.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetConsObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetConsObj

IMPLEMENT_DYNAMIC(SetConsObj, CRecordset)

SetConsObj::SetConsObj(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetConsObj)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_ID_CONSIST = 0;
	m_H0 = 0.0;
	m_H1 = 0.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetConsObj::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetConsObj::GetDefaultSQL()
{
	return _T("[ConsObj]");
}

void SetConsObj::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetConsObj)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_CONSIST]"), m_ID_CONSIST);
	RFX_Double(pFX, _T("[H0]"), m_H0);
	RFX_Double(pFX, _T("[H1]"), m_H1);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetConsObj diagnostics

#ifdef _DEBUG
void SetConsObj::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetConsObj::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
