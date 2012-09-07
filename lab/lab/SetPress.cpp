// SetPress.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetPress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetPress

IMPLEMENT_DYNAMIC(SetPress, CRecordset)

SetPress::SetPress(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetPress)
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetPress::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetPress::GetDefaultSQL()
{
	return _T("");
}

void SetPress::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetPress)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetPress diagnostics

#ifdef _DEBUG
void SetPress::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetPress::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
