// SetObject.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetObject

IMPLEMENT_DYNAMIC(SetObject, CRecordset)

SetObject::SetObject(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetObject)
	m_ID_OBJ = 0;
	m_CONTRACT = _T("");
	m_NAZVA = _T("");
	m_zoomCoefXYZ = 1.0;
	m_zoomCoefXY = 1.0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetObject::GetDefaultConnect()
{
	return CLabDoc::s_strConnect;
}

CString SetObject::GetDefaultSQL()
{
	return _T("[Objects]");
}

void SetObject::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetObject)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Text(pFX, _T("[CONTRACT]"), m_CONTRACT);
	RFX_Text(pFX, _T("[NAZVA]"), m_NAZVA);
	RFX_Double(pFX, _T("[zoomCoefXYZ]"), m_zoomCoefXYZ);
	RFX_Double(pFX, _T("[zoomCoefXY]"), m_zoomCoefXY);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetObject diagnostics

#ifdef _DEBUG
void SetObject::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetObject::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
