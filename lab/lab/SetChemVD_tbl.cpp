// SetChemVD_tbl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetChemVD_tbl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetChemVD_tbl

IMPLEMENT_DYNAMIC(SetChemVD_tbl, CRecordset)

SetChemVD_tbl::SetChemVD_tbl(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetChemVD_tbl)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_HORIZONT = 0;
	m_ID_CHEM = 0;
	m_MG = 0.0;
	m_MGECV = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetChemVD_tbl::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetChemVD_tbl::GetDefaultSQL()
{
	return _T("[ChemVD_tbl]");
}

void SetChemVD_tbl::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetChemVD_tbl)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[HORIZONT]"), m_HORIZONT);
	RFX_Long(pFX, _T("[ID_CHEM]"), m_ID_CHEM);
	RFX_Double(pFX, _T("[MG]"), m_MG);
	RFX_Double(pFX, _T("[MGECV]"), m_MGECV);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetChemVD_tbl diagnostics

#ifdef _DEBUG
void SetChemVD_tbl::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetChemVD_tbl::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
