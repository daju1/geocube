// SetT_V.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetT_V.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetT_V

IMPLEMENT_DYNAMIC(SetT_V, CRecordset)

SetT_V::SetT_V(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetT_V)
	m_ID_OBJ = 0;
	m_ID_ROZRIZ = 0;
	m_ID_KT = 0;
	m_N = 0;
	m_id_ige = 0;
	m_pos_L = 0;
	m_pos_T = 0;
	m_pos_R = 0;
	m_pos_B = 0;
	m_iPerehid = 0;
	m_X = 0.0;
	m_Y = 0.0;
	m_typ = 0;
	m_Name = _T("");
	m_nFields = 14;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetT_V::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetT_V::GetDefaultSQL()
{
	return _T("[T_V]");
}

void SetT_V::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetT_V)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_ROZRIZ]"), m_ID_ROZRIZ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[N]"), m_N);
	RFX_Long(pFX, _T("[id_ige]"), m_id_ige);
	RFX_Long(pFX, _T("[pos_L]"), m_pos_L);
	RFX_Long(pFX, _T("[pos_T]"), m_pos_T);
	RFX_Long(pFX, _T("[pos_R]"), m_pos_R);
	RFX_Long(pFX, _T("[pos_B]"), m_pos_B);
	RFX_Long(pFX, _T("[iPerehid]"), m_iPerehid);
	RFX_Double(pFX, _T("[X]"), m_X);
	RFX_Double(pFX, _T("[Y]"), m_Y);
	RFX_Byte(pFX, _T("[typ]"), m_typ);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetT_V diagnostics

#ifdef _DEBUG
void SetT_V::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetT_V::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
