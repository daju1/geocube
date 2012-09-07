// SetChemVD.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetChemVD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetChemVD

IMPLEMENT_DYNAMIC(SetChemVD, CRecordset)

SetChemVD::SetChemVD(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetChemVD)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_HORIZONT = 0;
	m_PIB = _T("");
	m_COLOR = _T("");
	m_PROZORIST = _T("");
	m_OSAD = _T("");
	m_ZAPAH = _T("");
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetChemVD::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetChemVD::GetDefaultSQL()
{
	return _T("[ChemVD]");
}

void SetChemVD::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetChemVD)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[HORIZONT]"), m_HORIZONT);
	RFX_Date(pFX, _T("[DTLAB]"), m_DTLAB);
	RFX_Text(pFX, _T("[PIB]"), m_PIB);
	RFX_Text(pFX, _T("[COLOR]"), m_COLOR);
	RFX_Text(pFX, _T("[PROZORIST]"), m_PROZORIST);
	RFX_Text(pFX, _T("[OSAD]"), m_OSAD);
	RFX_Text(pFX, _T("[ZAPAH]"), m_ZAPAH);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetChemVD diagnostics

#ifdef _DEBUG
void SetChemVD::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetChemVD::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
