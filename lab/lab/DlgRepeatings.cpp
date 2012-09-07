// DlgRepeatings.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DlgRepeatings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatings dialog
	
int CDlgRepeatings::s_repeatings = 2;


CDlgRepeatings::CDlgRepeatings(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRepeatings::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRepeatings)
	m_repeatings = -1;
	//}}AFX_DATA_INIT

	//m_repeatings = CDlgRepeatings::s_repeatings - 2;
	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			m_repeatings = 0;
		}
		break;
	case 3:
		{
			m_repeatings = 1;
		}
		break;
	case 6:
		{
			m_repeatings = 2;
		}
		break;
	}
}


void CDlgRepeatings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRepeatings)
	DDX_Radio(pDX, IDC_RADIO_TWO_REPEATINGS, m_repeatings);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRepeatings, CDialog)
	//{{AFX_MSG_MAP(CDlgRepeatings)
	ON_BN_CLICKED(IDC_RADIO_TWO_REPEATINGS, OnRadioTwoRepeatings)
	ON_BN_CLICKED(IDC_RADIO_THREE_REPEATINGS, OnRadioThreeRepeatings)
	ON_BN_CLICKED(IDC_RADIO_SIX_REPEATINGS, OnRadioSixRepeatings)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatings message handlers

BOOL CDlgRepeatings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRepeatings::OnRadioTwoRepeatings() 
{
	CDlgRepeatings::s_repeatings = 2;	
}

void CDlgRepeatings::OnRadioThreeRepeatings() 
{
	CDlgRepeatings::s_repeatings = 3;	
}

void CDlgRepeatings::OnRadioSixRepeatings() 
{
	CDlgRepeatings::s_repeatings = 6;	
}
