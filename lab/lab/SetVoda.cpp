// SetVoda.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetVoda.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetVoda

IMPLEMENT_DYNAMIC(SetVoda, CRecordset)

SetVoda::SetVoda(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetVoda)
	m_ID_OBJ = 0;
	m_ID_KT = 0;
	m_HORIZONT = 0;
	m_HV_Z = 0.0;
	m_HV_V = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetVoda::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetVoda::GetDefaultSQL()
{
	return _T("[Voda]");
}

void SetVoda::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetVoda)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[HORIZONT]"), m_HORIZONT);
	RFX_Double(pFX, _T("[HV_Z]"), m_HV_Z);
	RFX_Double(pFX, _T("[HV_V]"), m_HV_V);
	RFX_Date(pFX, _T("[DV]"), m_DV);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetVoda diagnostics

#ifdef _DEBUG
void SetVoda::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetVoda::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetVoda::AddNewRow(long ID_OBJ, long ID_KT, long HORIZONT, double HV_Z, double HV_V, CTime time)
{
	this->AddNew();

	m_ID_OBJ = ID_OBJ;
	m_ID_KT = ID_KT;
	m_HORIZONT = HORIZONT;
	m_HV_Z = HV_Z;
	m_HV_V = HV_V;
	m_DV = time;

	this->Update();
}

void SetVoda::AddNewRow(long ID_OBJ, long ID_KT, long HORIZONT, double HV_Z, double HV_V)
{
	this->AddNew();

	m_ID_OBJ = ID_OBJ;
	m_ID_KT = ID_KT;
	m_HORIZONT = HORIZONT;
	m_HV_Z = HV_Z;
	m_HV_V = HV_V;

	this->Update();
}