// ex31aSet.cpp : implementation file
//

#include "stdafx.h"
#include "ex31a.h"
#include "ex31aset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31aSet

IMPLEMENT_DYNAMIC(CEx31aSet, CRecordset)

CEx31aSet::CEx31aSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx31aSet)
	m_StudentID = 0;
	m_Name = _T("");
	m_GradYear = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CEx31aSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=База данных MS Access");
//	return _T("ODBC;DSN=Student Registration");
}

CString CEx31aSet::GetDefaultSQL()
{
	return _T("[Student]");
}

void CEx31aSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx31aSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Student].[StudentID]"), m_StudentID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Int(pFX, _T("[GradYear]"), m_GradYear);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx31aSet diagnostics

#ifdef _DEBUG
void CEx31aSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEx31aSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
