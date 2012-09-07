// ex31bSet.cpp : implementation of the CEx31bSet class
//

#include "stdafx.h"
#include "ex31b.h"
#include "ex31bSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx31bSet implementation

IMPLEMENT_DYNAMIC(CEx31bSet, CRecordset)

CEx31bSet::CEx31bSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CEx31bSet)
	m_InstructorID = _T("");
	m_Name = _T("");
	m_RoomNo = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}

CString CEx31bSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student Registration");
}

CString CEx31bSet::GetDefaultSQL()
{
	return _T("[Instructor]");
}

void CEx31bSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CEx31bSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[InstructorID]"), m_InstructorID);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[RoomNo]"), m_RoomNo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CEx31bSet diagnostics

#ifdef _DEBUG
void CEx31bSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEx31bSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
