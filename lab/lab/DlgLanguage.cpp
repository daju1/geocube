// DlgLanguage.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgLanguage.h"


#include "../../laboratory/src/BaseLab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage dialog


CDlgLanguage::CDlgLanguage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLanguage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLanguage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLanguage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLanguage)
	DDX_Control(pDX, IDC_COMBO_LANGUAGE, m_combo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLanguage, CDialog)
	//{{AFX_MSG_MAP(CDlgLanguage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLanguage message handlers

BOOL CDlgLanguage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_combo.ResetContent();
	this->m_combo.AddString( "Русский" );
	this->m_combo.AddString( "Украинский" );
		
	switch (BaseLab::PassportLanguage)
	{
	case BaseLab::language::russian:
		{
			this->m_combo.SetCurSel(0);
		}
		break;
	case BaseLab::language::ukrainian:
		{
			this->m_combo.SetCurSel(1);
		}
		break;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLanguage::OnOK() 
{
	// TODO: Add extra validation here
	int i = this->m_combo.GetCurSel();
	switch (i)
	{
	case 0:
		{
			BaseLab::PassportLanguage = BaseLab::language::russian;
		}
		break;
	case 1:
		{
			BaseLab::PassportLanguage = BaseLab::language::ukrainian;
		}
		break;
	}
	CDialog::OnOK();
}
