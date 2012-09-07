// KtSet.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "KtSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKtSet

IMPLEMENT_DYNAMIC(CKtSet, CRecordset)

CKtSet::CKtSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CKtSet)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_NAZVA = _T("");
	m_X = 0.0;
	m_Y = 0.0;
	m_Z = 0.0;
	m_ID_TYP = 0;
	m_ID_BUR = 0;
	m_D_BUR = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CKtSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString CKtSet::GetDefaultSQL()
{
	return _T("[KT]");
}

void CKtSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CKtSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	RFX_Double(pFX, _T("[X]"), m_X);
	RFX_Double(pFX, _T("[Y]"), m_Y);
	RFX_Double(pFX, _T("[Z]"), m_Z);
	RFX_Long(pFX, _T("[ID_TYP]"), m_ID_TYP);
	RFX_Long(pFX, _T("[ID_BUR]"), m_ID_BUR);
	RFX_Long(pFX, _T("[D_BUR]"), m_D_BUR);
	RFX_Date(pFX, _T("[DTBUR]"), m_DTBUR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CKtSet diagnostics

#ifdef _DEBUG
void CKtSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CKtSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
