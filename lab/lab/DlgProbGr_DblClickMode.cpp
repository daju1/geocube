// DlgProbGr_DblClickMode.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgProbGr_DblClickMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProbGr_DblClickMode dialog


CDlgProbGr_DblClickMode::CDlgProbGr_DblClickMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProbGr_DblClickMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProbGr_DblClickMode)
	m_radio = -1;
	//}}AFX_DATA_INIT
	m_radio = CDlgProbGr_DblClickMode::selected_mode;
}


void CDlgProbGr_DblClickMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProbGr_DblClickMode)
	DDX_Radio(pDX, IDC_RADIO_LAB_NUMBER, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProbGr_DblClickMode, CDialog)
	//{{AFX_MSG_MAP(CDlgProbGr_DblClickMode)
	ON_BN_CLICKED(IDC_RADIO_LAB_NUMBER, OnRadioLabNumber)
	ON_BN_CLICKED(IDC_RADIO_GRUNT_NAME, OnRadioGruntName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProbGr_DblClickMode message handlers
int CDlgProbGr_DblClickMode::selected_mode = 0;
void CDlgProbGr_DblClickMode::OnRadioLabNumber() 
{
	// TODO: Add your control notification handler code here
	CDlgProbGr_DblClickMode::selected_mode = 0;
	
}

void CDlgProbGr_DblClickMode::OnRadioGruntName() 
{
	// TODO: Add your control notification handler code here
	CDlgProbGr_DblClickMode::selected_mode = 1;
	
}
