// ex31cSet.cpp : implementation of the CEx31cSet class
//

#include "stdafx.h"
#include "ex31c.h"
#include "ex31cSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31cSet implementation

IMPLEMENT_DYNAMIC(CEx31cSet, CRecordset)

CEx31cSet::CEx31cSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx31cSet)
	m_InstructorID = _T("");
	m_Name = _T("");
	m_RoomNo = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CEx31cSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CEx31cSet::GetDefaultSQL()
{
	return _T("[Instructor]");
}

void CEx31cSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx31cSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[InstructorID]"), m_InstructorID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[RoomNo]"), m_RoomNo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx31cSet diagnostics

#ifdef _DEBUG
void CEx31cSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEx31cSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
