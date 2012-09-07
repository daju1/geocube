// PropDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "OG.h"
#include "OGView.h"
#include "PropDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropDlg dialog

#if 0
CPropDlg::CPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPropDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
#else
CPropDlg::CPropDlg(COGView* p)
	: CDialog(CPropDlg::IDD, p)
{
	//====== ���������� ����� ����
	m_pView = p;
}
#endif



void CPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPropDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

IMPLEMENT_DYNAMIC(CPropDlg, CDialog)

BEGIN_MESSAGE_MAP(CPropDlg, CDialog)
	//{{AFX_MSG_MAP(CPropDlg)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_FILENAME, OnFilename)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropDlg message handlers


int CPropDlg::GetSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (::GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_XPOS:
		nID = IDC_XPOS_TEXT;
		return 0;
	case IDC_YPOS:
		nID = IDC_YPOS_TEXT;
		return 1;
	case IDC_ZPOS:
		nID = IDC_ZPOS_TEXT;
		return 2;
	case IDC_AMBIENT:
		nID = IDC_AMB_TEXT;
		return 3;
	case IDC_DIFFUSE:
		nID = IDC_DIFFUSE_TEXT;
		return 4;
	case IDC_SPECULAR:
		nID = IDC_SPECULAR_TEXT;
		return 5;
	case IDC_AMBMAT:
		nID = IDC_AMBMAT_TEXT;
		return 6;
	case IDC_DIFFMAT:
		nID = IDC_DIFFMAT_TEXT;
		return 7;
	case IDC_SPECMAT:
		nID = IDC_SPECMAT_TEXT;
		return 8;
	case IDC_SHINE:
		nID = IDC_SHINE_TEXT;
		return 9;
	case IDC_EMISSION:
		nID = IDC_EMISSION_TEXT;
		return 10;
	}
	return 0;
}

/*
void CPropDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
*/
void CPropDlg::OnHScroll(UINT nSBCode, UINT nPos,
					CScrollBar* pScrollBar)
{
	//====== Windows-��������� ���� ��������� ��������
	HWND hwnd = pScrollBar->GetSafeHwnd();

	UINT nID;

	//=== ���������� ������ � ������� ������� ���������
	int num = GetSliderNum(hwnd, nID);
	int delta, newPos;

	//====== ����������� ��� �������
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:		// ���������� �����
		m_Pos[num] = nPos;
		break;
	case SB_LEFT:					// ������� Home
		delta = -100;
		goto New_Pos;
	case SB_RIGHT:				// ������� End
		delta = +100;
		goto New_Pos;
	case SB_LINELEFT:			// ������� <-
		delta = -1;
		goto New_Pos;
	case SB_LINERIGHT:			// ������� ->
		delta = +1;
		goto New_Pos;
	case SB_PAGELEFT:			// ������� PgUp
		delta = -20;
		goto New_Pos;
	case SB_PAGERIGHT:			// ������� PgDn
		delta = +20;
		goto New_Pos;

	New_Pos:						// ����� �����
		//====== ������������� ����� �������� ����������
		newPos = m_Pos[num] + delta;
		//====== �����������
		m_Pos[num] = newPos<0 ? 0 : newPos>100 ? 100 : newPos;
		break;
	case SB_ENDSCROLL:
	default:
		return;
	}

	//====== �������������� ��������� ������ �������
	char s[8];
	sprintf (s,"%d",m_Pos[num]);
	SetDlgItemText(nID, (LPCTSTR)s);

	//====== �������� ��������� � ����� ����
	m_pView->SetLightParam (num, m_Pos[num]);
}



BOOL CPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//====== ��������� ������ ������� ���������� �����
	m_pView->GetLightParams(m_Pos);

	//====== ������ ��������������� ���������
	UINT IDs[] = 
	{
		IDC_XPOS,		IDC_YPOS,		IDC_ZPOS,
		IDC_AMBIENT,
		IDC_DIFFUSE,
		IDC_SPECULAR,
		IDC_AMBMAT,
		IDC_DIFFMAT,
		IDC_SPECMAT,
		IDC_SHINE,
		IDC_EMISSION
	};

	//====== ���� ������� �� ���� �����������
	for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
	{
		//=== �������� Windows-��������� ���� ��������
		HWND hwnd = GetDlgItem(IDs[i])->GetSafeHwnd();
		UINT nID;

		//====== ���������� ��� �������������
		int num = GetSliderNum(hwnd, nID);

		// ������� ���������� �������� � ��������� m_Pos[i]
		::SendMessage(hwnd, TBM_SETPOS, TRUE,
						(LPARAM)m_Pos[i]);
		char s[8];
		//====== ������� ��������� ������ ������� �������
		sprintf (s,"%d",m_Pos[i]);
		//====== �������� ����� � ���� ������ �� ��������
		SetDlgItemText(nID, (LPCTSTR)s);
	}
	ShowWindow(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPropDlg::OnClose() 
{
	//=== �������� ��������� �� ������ ������ ������
	m_pView->m_pDlg = 0;
	//====== ���������� ����
	CDialog::OnClose();
	//====== ����������� ������
	delete this;
}

void CPropDlg::OnFilename() 
{

	//=== ��������� �������� ������ � ������ ������
//	m_pView->ReadData();
}

