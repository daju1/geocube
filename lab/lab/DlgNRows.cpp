// DlgNRows.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgNRows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNRows dialog


CDlgNRows::CDlgNRows(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNRows::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNRows)
	m_edit = _T("");
	//}}AFX_DATA_INIT
	ok_pressed = false;
}


void CDlgNRows::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNRows)
	DDX_Text(pDX, IDC_EDIT_N_ROWS, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNRows, CDialog)
	//{{AFX_MSG_MAP(CDlgNRows)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNRows message handlers

void CDlgNRows::OnOK() 
{
	// TODO: Add extra validation here
	ok_pressed = true;
	
	CDialog::OnOK();
}
