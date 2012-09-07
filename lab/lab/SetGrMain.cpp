// SetGrMain.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetGrMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetGrMain

IMPLEMENT_DYNAMIC(SetGrMain, CRecordset)

SetGrMain::SetGrMain(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetGrMain)
	m_ID_GRMAIN = 0;
	m_NAZVA_U = _T("");
	m_NAZVA_R = _T("");
	m_TYPGR = 0;
	m_TYPGR_PCK = 0;
	m_ID_NORMATYV = 0;
	m_ID_GRCONS = 0;
	m_ID_NJU = 0;
	m_ID_UMPOZ = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetGrMain::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetGrMain::GetDefaultSQL()
{
	return _T("[GrMain]");
}

void SetGrMain::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetGrMain)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_GRMAIN]"), m_ID_GRMAIN);
	RFX_Text(pFX, _T("[NAZVA_U]"), m_NAZVA_U);
	RFX_Text(pFX, _T("[NAZVA_R]"), m_NAZVA_R);
	RFX_Long(pFX, _T("[TYPGR]"), m_TYPGR);
	RFX_Long(pFX, _T("[TYPGR_PCK]"), m_TYPGR_PCK);
	RFX_Long(pFX, _T("[ID_NORMATYV]"), m_ID_NORMATYV);
	RFX_Long(pFX, _T("[ID_GRCONS]"), m_ID_GRCONS);
	RFX_Long(pFX, _T("[ID_NJU]"), m_ID_NJU);
	RFX_Long(pFX, _T("[ID_UMPOZ]"), m_ID_UMPOZ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetGrMain diagnostics

#ifdef _DEBUG
void SetGrMain::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetGrMain::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
