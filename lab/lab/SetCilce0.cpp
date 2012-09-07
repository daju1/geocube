// SetCilce0.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetCilce0.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetCilce0

IMPLEMENT_DYNAMIC(SetCilce0, CRecordset)

SetCilce0::SetCilce0(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetCilce0)
	m_ID_OBJ = 0;
	m_M_GRUNTA = 0.0;
	m_M_GRUNTA_POSLE = 0.0;
	m_M_GRUNTA_VYSUSH = 0.0;
	m_M_GRUNTA_ZAMOCH = 0.0;
	m_M_KOLCA = 0.0;
	m_ID_KT = 0;
	m_ID_PROB = 0;
	m_ID_VYPROB = 0;
	m_ID_PHYS_VYPROB = 0;
	m_H = 0.0;
	m_D = 0.0;
	m_nFields = 13;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetCilce0::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetCilce0::GetDefaultSQL()
{
	return _T("[Cilce0]");
}

void SetCilce0::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetCilce0)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Double(pFX, _T("[M_GRUNTA]"), m_M_GRUNTA);
	RFX_Double(pFX, _T("[M_GRUNTA_POSLE]"), m_M_GRUNTA_POSLE);
	RFX_Double(pFX, _T("[M_GRUNTA_VYSUSH]"), m_M_GRUNTA_VYSUSH);
	RFX_Double(pFX, _T("[M_GRUNTA_ZAMOCH]"), m_M_GRUNTA_ZAMOCH);
	RFX_Double(pFX, _T("[M_KOLCA]"), m_M_KOLCA);
	RFX_Long(pFX, _T("[ID_KT]"), m_ID_KT);
	RFX_Long(pFX, _T("[ID_PROB]"), m_ID_PROB);
	RFX_Long(pFX, _T("[ID_PHYS_VYPROB]"), m_ID_PHYS_VYPROB);
	RFX_Long(pFX, _T("[ID_VYPROB]"), m_ID_VYPROB);
	RFX_Long(pFX, _T("[ID_KOLCA]"), m_ID_KOLCA);
	RFX_Double(pFX, _T("[H]"), m_H);
	RFX_Double(pFX, _T("[D]"), m_D);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetCilce0 diagnostics

#ifdef _DEBUG
void SetCilce0::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetCilce0::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
long SetCilce0::GetMaxPhysVyprobID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_PHYS_VYPROB > id)
				id = this->m_ID_PHYS_VYPROB;
			
			this->MoveNext(); // to validate record count
		}
	}
	return id;
}