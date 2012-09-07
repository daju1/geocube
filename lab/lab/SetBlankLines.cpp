// SetBlankLines.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetBlankLines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetBlankLines

IMPLEMENT_DYNAMIC(SetBlankLines, CRecordset)

SetBlankLines::SetBlankLines(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetBlankLines)
	m_ID_OBJ = 0;
	m_ID_SURF = 0;
	m_ID_LINE = 0;
	m_NPP = 0;
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetBlankLines::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetBlankLines::GetDefaultSQL()
{
	return _T("[BlankLines]");
}

void SetBlankLines::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetBlankLines)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_SURF]"), m_ID_SURF);
	RFX_Long(pFX, _T("[ID_LINE]"), m_ID_LINE);
	RFX_Long(pFX, _T("[NPP]"), m_NPP);
	RFX_Double(pFX, _T("[X]"), m_X);
	RFX_Double(pFX, _T("[Y]"), m_Y);
	RFX_Double(pFX, _T("[Z]"), m_Z);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetBlankLines diagnostics

#ifdef _DEBUG
void SetBlankLines::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetBlankLines::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
