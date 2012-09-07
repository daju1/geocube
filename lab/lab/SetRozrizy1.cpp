// SetRozrizy.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetRozrizy1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetRozrizy

IMPLEMENT_DYNAMIC(SetRozrizy, CRecordset)

SetRozrizy::SetRozrizy(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetRozrizy)
	m_ID_OBJ = 0;
	m_ID_ROZRIZ = 0;
	m_NOMER = _T("");
	m_has_dxf = 0;
	m_fn_dxf = _T("");
	m_acad_yscale_loaded = 0;
	m_z1w = 0.0;
	m_y1a = 0.0;
	m_z2w = 0.0;
	m_y2a = 0.0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetRozrizy::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetRozrizy::GetDefaultSQL()
{
	return _T("[Rozrizy]");
}

void SetRozrizy::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetRozrizy)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[ID_ROZRIZ]"), m_ID_ROZRIZ);
	RFX_Text(pFX, _T("[NOMER]"), m_NOMER);
	RFX_Byte(pFX, _T("[has_dxf]"), m_has_dxf);
	RFX_Text(pFX, _T("[fn_dxf]"), m_fn_dxf);
	RFX_Byte(pFX, _T("[acad_yscale_loaded]"), m_acad_yscale_loaded);
	RFX_Double(pFX, _T("[z1w]"), m_z1w);
	RFX_Double(pFX, _T("[y1a]"), m_y1a);
	RFX_Double(pFX, _T("[z2w]"), m_z2w);
	RFX_Double(pFX, _T("[y2a]"), m_y2a);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetRozrizy diagnostics

#ifdef _DEBUG
void SetRozrizy::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetRozrizy::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

long SetRozrizy::GetNewKeyID()
{
	long id = 0;
	if (!this->IsBOF()) 
	{
		this->MoveFirst();
		while(!this->IsEOF()) 
		{
			if (this->m_ID_ROZRIZ > id)
				id = this->m_ID_ROZRIZ;
			
			this->MoveNext(); // to validate record count
		}
	}
	id++;

	return id;
}
void SetRozrizy::AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NOMER = NOMER;

	this->Update();
}
void SetRozrizy::AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER, CString fn_dxf, double z1w, double y1a, double z2w, double y2a)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NOMER = NOMER;

	m_has_dxf = 1;
	m_fn_dxf = fn_dxf;
	m_acad_yscale_loaded = 1;
	m_z1w = z1w;
	m_y1a = y1a;
	m_z2w = z2w;
	m_y2a = y2a;

	this->Update();
}

void SetRozrizy::AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER, CString fn_dxf)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NOMER = NOMER;

	m_has_dxf = 1;
	m_fn_dxf = fn_dxf;
	m_acad_yscale_loaded = 0;

	this->Update();
}
void SetRozrizy::AddNewRow(long ID_OBJ, long ID_ROZRIZ, CString NOMER, double z1w, double y1a, double z2w, double y2a)
{
	this->AddNew();

	this->m_ID_OBJ = ID_OBJ;
	this->m_ID_ROZRIZ = ID_ROZRIZ;
	this->m_NOMER = NOMER;

	m_has_dxf = 0;
	m_acad_yscale_loaded = 1;
	m_z1w = z1w;
	m_y1a = y1a;
	m_z2w = z2w;
	m_y2a = y2a;

	this->Update();
}