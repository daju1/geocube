// SetCubeSize.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetCubeSize.h"

#include "../../surfdoc/src/Grid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SetCubeSize

IMPLEMENT_DYNAMIC(SetCubeSize, CRecordset)

SetCubeSize::SetCubeSize(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SetCubeSize)
	m_ID_OBJ = 0;
	m_nPag = 0;
	m_nRow = 0;
	m_nCol = 0;
	m_xLL = 0.0;
	m_yLL = 0.0;
	m_zLL = 0.0;
	m_xSize = 0.0;
	m_ySize = 0.0;
	m_zSize = 0.0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SetCubeSize::GetDefaultConnect()
{
	return _T("ODBC;DSN=Wen Geo DB");
}

CString SetCubeSize::GetDefaultSQL()
{
	return _T("[CubeSize]");
}

void SetCubeSize::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SetCubeSize)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID_OBJ]"), m_ID_OBJ);
	RFX_Long(pFX, _T("[nPag]"), m_nPag);
	RFX_Long(pFX, _T("[nRow]"), m_nRow);
	RFX_Long(pFX, _T("[nCol]"), m_nCol);
	RFX_Double(pFX, _T("[xLL]"), m_xLL);
	RFX_Double(pFX, _T("[yLL]"), m_yLL);
	RFX_Double(pFX, _T("[zLL]"), m_zLL);
	RFX_Double(pFX, _T("[xSize]"), m_xSize);
	RFX_Double(pFX, _T("[ySize]"), m_ySize);
	RFX_Double(pFX, _T("[zSize]"), m_zSize);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SetCubeSize diagnostics

#ifdef _DEBUG
void SetCubeSize::AssertValid() const
{
	CRecordset::AssertValid();
}

void SetCubeSize::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void SetCubeSize::Init(CubeSize & cube_size)
{
	m_nPag = cube_size.nPag;
	m_nRow = cube_size.nRow;
	m_nCol = cube_size.nCol;
	m_xLL = cube_size.xLL;
	m_yLL = cube_size.yLL;
	m_zLL = cube_size.zLL;
	m_xSize = cube_size.xSize;
	m_ySize = cube_size.ySize;
	m_zSize = cube_size.zSize;
}