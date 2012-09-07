// WaveDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Graphs.h"
#include "GraphsDoc.h"
#include "WaveDlg.h"
#include "Wavelet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int WaveletFilterLength(int wf, // флаг типа вейвлетов
				int order // порядоак вейвлета
)
{
	if (wf==WF_HAAR)
	{
		return 2;
	}
	if (wf==WF_DAUBECHIES)
	{
		return 2*order;
	}

	if (wf==WF_SYMLETS)
	{
		return 2*order;
	}
	if (wf == WF_COIFLETS)
	{
		return 6*order;
	}
	if (wf == WF_DISCRETE_MEYER)
	{
		return 62;
	}
	return 0;
}

extern Wavelets g_Wav[8];
/////////////////////////////////////////////////////////////////////////////
// CWaveDlg dialog
IMPLEMENT_DYNAMIC(CWaveDlg, CDialog)


CWaveDlg::CWaveDlg(CGraphsDoc* p)
//	: CDialog(CWaveDlg::IDD)
{
	m_pDoc = p;
	//{{AFX_DATA_INIT(CWaveDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CWaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveDlg)
	DDX_Radio(pDX, IDC_RADIO_WAV1, m_pDoc->m_radioRec);
	
	DDX_Text(pDX, IDC_EDIT_WAV_EPSILON, m_pDoc->m_wEpsilon);
	DDX_Control(pDX, IDC_STATIC_WAV_LEN, m_txtWavLen);
	DDX_Control(pDX, IDC_COMBO_WAV_TYPE, m_cmbWavType);
	DDX_Control(pDX, IDC_COMBO_WAV_ORDER, m_cmbWavOrder);
	DDX_Control(pDX, IDC_COMBO_WAV_MAXLEVEL, m_cmbWavMaxLevel);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaveDlg, CDialog)
	//{{AFX_MSG_MAP(CWaveDlg)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_WAV_TYPE, OnSelchangeComboWavType)
	ON_CBN_SELCHANGE(IDC_COMBO_WAV_ORDER, OnSelchangeComboWavOrder)
	ON_BN_CLICKED(IDC_WAV_DISP, OnWavDisp)
	ON_BN_CLICKED(IDC_WAV_EPSILON, OnWavEpsilon)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveDlg message handlers

BOOL CWaveDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	CRect r,r1,r2;
	//===== С помощью контекста устройства
	//===== узнаем размеры всего экрана
	CClientDC dc(this);
	int w = dc.GetDeviceCaps(HORZRES);
	int h = dc.GetDeviceCaps(VERTRES);

	//===== Узнаем размеры окна диалога
	GetWindowRect(&r);
	//===== Смещаем его вправо и вниз
	r.OffsetRect(w-r.right-10,h-r.bottom-30);
	MoveWindow(&r);



	m_cmbWavType.ResetContent();
	m_cmbWavOrder.ResetContent();
	for (int i = 0; i < 8; i++)
	{
		m_cmbWavType.AddString((LPCTSTR)g_Wav[i].name);
	}
	m_cmbWavType.SetCurSel(m_pDoc->m_wf-1);

	int ind = m_cmbWavType.GetCurSel();
	CString s;
	for (i = g_Wav[ind].minOrder; i <= g_Wav[ind].maxOrder; i++)
	{
		s.Format("%d",i);
		m_cmbWavOrder.AddString((LPCTSTR)s);
	}
	m_cmbWavOrder.SetCurSel(m_pDoc->m_wOrder-1);

	for (i = 1; i <= 10; i++)
	{
		s.Format("%d",i);
		m_cmbWavMaxLevel.AddString((LPCTSTR)s);
	}
	m_cmbWavMaxLevel.SetCurSel(m_pDoc->m_maxLevel-1);
	SetWaveletFilterLength();



	ShowWindow(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWaveDlg::OnCancel() 
{
	CDialog::OnCancel();
	//====== Закрываем немодальный диалог
	m_pDoc->m_pWaveDlg = 0;
	DestroyWindow();
	
}

void CWaveDlg::OnOK() 
{

	UpdateData();

	m_pDoc->m_wf = m_cmbWavType.GetCurSel()+1;
	m_pDoc->m_wOrder = m_cmbWavOrder.GetCurSel()+1;
	m_pDoc->m_maxLevel = m_cmbWavMaxLevel.GetCurSel()+1;

	m_pDoc->WaveletApply();

	UpdateData(false);

/*
	CDialog::OnOK();
	m_pDoc->m_pWaveDlg = 0;
	DestroyWindow();*/

}

void CWaveDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
void CWaveDlg::PostNcDestroy() 
{
	delete this;
	CDialog::PostNcDestroy();
}

void CWaveDlg::OnSelchangeComboWavType() 
{
	m_cmbWavOrder.ResetContent();
	int ind = m_cmbWavType.GetCurSel();
	CString s;
	for (int i = g_Wav[ind].minOrder; i <= g_Wav[ind].maxOrder; i++)
	{
		s.Format("%d",i);
		m_cmbWavOrder.AddString((LPCTSTR)s);
	}
//	m_cmbWavOrder.SetCurSel(int((g_Wav[ind].minOrder + g_Wav[ind].maxOrder)/2)-1);
	SetWaveletFilterLength();	
}

void CWaveDlg::OnSelchangeComboWavOrder() 
{
	SetWaveletFilterLength();	
}

void CWaveDlg::SetWaveletFilterLength()
{
	CString s;
	s.Format("L фильтра=%d", WaveletFilterLength(m_cmbWavType.GetCurSel()+1, 
		m_cmbWavOrder.GetCurSel()+1));
	m_txtWavLen.SetWindowText((LPCTSTR)s);

}

void CWaveDlg::OnWavDisp() 
{
	m_pDoc->m_wf = m_cmbWavType.GetCurSel()+1;
	m_pDoc->m_wOrder = m_cmbWavOrder.GetCurSel()+1;
	m_pDoc->WaveletDisplay();
	
}

void CWaveDlg::OnWavEpsilon() 
{
	
	m_pDoc->m_wf = m_cmbWavType.GetCurSel()+1;
	m_pDoc->m_wOrder = m_cmbWavOrder.GetCurSel()+1;
	m_pDoc->m_maxLevel = m_cmbWavMaxLevel.GetCurSel()+1;

	UpdateData();
	//====== Заново решаем систему и выводим график
	m_pDoc->WaveletEpsilonApply();
	UpdateData(false);
	
}
