// GPS_CRDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GPS_CRD.h"
#include "GPS_CRDDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPS_CRDDlg dialog

CGPS_CRDDlg::CGPS_CRDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGPS_CRDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGPS_CRDDlg)
	m_edit_gps_fn = _T("");
	m_edit_pribor_fn = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGPS_CRDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGPS_CRDDlg)
	DDX_Control(pDX, IDC_BUTTON_CALC, m_button_calc);
	DDX_Control(pDX, IDC_BUTTON_CLOSE, m_button_close);
	DDX_Control(pDX, IDC_BUTTON_LOAD_FILES, m_button_load_files);
	DDX_Text(pDX, IDC_EDIT_GPS_FN, m_edit_gps_fn);
	DDX_Text(pDX, IDC_EDIT_PRIBOR_FN, m_edit_pribor_fn);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGPS_CRDDlg, CDialog)
	//{{AFX_MSG_MAP(CGPS_CRDDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GPS_BROSE, OnButtonGpsBrose)
	ON_BN_CLICKED(IDC_BUTTON_PRIBOR_BROSE, OnButtonPriborBrose)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FILES, OnButtonLoadFiles)
	ON_BN_CLICKED(IDC_BUTTON_CALC, OnButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGPS_CRDDlg message handlers

BOOL CGPS_CRDDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	this->m_button_load_files.EnableWindow(false);
	this->m_button_calc.EnableWindow(false);
	this->m_button_close.EnableWindow(false);
		
	gps_fn_loaded = false;
	pribor_fn_loaded = false;

	gps_ole_loaded = false;
	pribor_ole_loaded = false;
	out_ole_loaded = false;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGPS_CRDDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGPS_CRDDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGPS_CRDDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGPS_CRDDlg::OnButtonGpsBrose() 
{
	CFileDialog dlg(TRUE, ".xls", "*.xls");
	if (dlg.DoModal() == IDCANCEL) return;
	this->m_edit_gps_fn = dlg.GetPathName();

	this->UpdateData(false);
	gps_fn_loaded = true;

	this->m_button_load_files.EnableWindow(gps_fn_loaded && pribor_fn_loaded);
}

void CGPS_CRDDlg::OnButtonPriborBrose() 
{

	CFileDialog dlg(TRUE, ".xls", "*.xls");
	if (dlg.DoModal() == IDCANCEL) return;
	this->m_edit_pribor_fn = dlg.GetPathName();

	this->UpdateData(false);
	pribor_fn_loaded = true;

	this->m_button_load_files.EnableWindow(gps_fn_loaded && pribor_fn_loaded);
}

void CGPS_CRDDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CGPS_CRDDlg::OnButtonLoadFiles() 
{

	this->LoadExcelFile(this->m_excel_gps, this->m_edit_gps_fn, gps_ole_loaded);
	this->LoadExcelFile(this->m_excel_pribor, this->m_edit_pribor_fn, pribor_ole_loaded);

	this->m_button_calc.EnableWindow();
}
void CGPS_CRDDlg::LoadExcelFile(MyExcel &m_excel, const char * fn, bool & ole_loaded)
{
	m_excel.ExcelOleLoad();
	if (m_excel.IsApplicationDispatch())
	{
		try
		{
			m_excel.ExcelOleExecute(fn);
			ole_loaded = true;

			//m_excel.m_workbook.Save();
		}

		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();

			printf("catched\n");
			m_excel.ExcelOleRelease();
		}
	}
	else
	{
		AfxMessageBox("!!!!! m_excel.IsApplicationDispatch()\n");
	}
	
}

void CGPS_CRDDlg::OnButtonCalc() 
{
	this->LoadExcelFile(this->m_excel_out, NULL, out_ole_loaded);
	char S[64];


	char letter = 'A';
	int fr = 2;
	for (int r = fr; ;r++)
	{
		LPDISPATCH pRange; 
		Range10    m_range;

		sprintf(S, "A%d", r);

		VERIFY(pRange = m_excel_pribor.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		VARIANT pribor_time = m_range.GetValue();
		m_range.ReleaseDispatch();

		CString s_pribor_time;
		double f_pribor_time;

		bool s_time_got = false;
		bool f_time_got = false;

		if (pribor_time.vt == VT_R8)
		{
			f_pribor_time = pribor_time.dblVal;
			f_time_got = true;
		}
		else
		if (pribor_time.vt == VT_BSTR)
		{
			s_pribor_time = pribor_time.bstrVal;
			s_time_got = true;
		}

		if (!s_time_got && !f_time_got)
			break;



	}

	/*for (int n = 0; ; )
	{
		double val;

			long LAB_N;
			sprintf(S, "%c%d", letter, fr+n);
			if (!ExcelRange_GetValue(m_excel, S, val))
			{
				fr += rows_per_page;
				letter = first_letter;
				n = 0;
				sprintf(S, "%c%d", letter, fr+3);
				if (!ExcelRange_GetValue(m_excel, S, val))
				{
					break;
				}
				else
				{
					LAB_N = long(val);
				}
			}
	}*/

	this->m_button_close.EnableWindow();
}

void CGPS_CRDDlg::OnButtonClose() 
{
	this->CloseExcelFile(this->m_excel_gps,		this->gps_ole_loaded);
	this->CloseExcelFile(this->m_excel_pribor,	this->pribor_ole_loaded);
	this->CloseExcelFile(this->m_excel_out,		this->out_ole_loaded, false);

	this->m_button_calc.EnableWindow(false);
	this->m_button_close.EnableWindow(false);
}
void CGPS_CRDDlg::CloseExcelFile(MyExcel &m_excel, bool & ole_loaded, bool to_close)
{
	if (ole_loaded)
	{
		ole_loaded = false;
		if (m_excel.IsApplicationDispatch())
		{
			try
			{
				//m_excel.m_workbook.Save();
				if (to_close) m_excel.m_workbook.Close();
				//m_excel.m_app.Quit();
			}
			catch (CException* pe)
			{
				// catch errors from WinINet 
				TCHAR szErr[4098]; 
				pe->GetErrorMessage(szErr, 4098); 
				AfxMessageBox(szErr);
				pe->Delete();

			}
			m_excel.ExcelOleRelease();
		}
		else
		{
			AfxMessageBox("!!!!! m_excel.IsApplicationDispatch()\n");
		}
	}
}

void CGPS_CRDDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	this->CloseExcelFile(this->m_excel_gps,		this->gps_ole_loaded);
	this->CloseExcelFile(this->m_excel_pribor,	this->pribor_ole_loaded);
	this->CloseExcelFile(this->m_excel_out,		this->out_ole_loaded, false);
	
	CoUninitialize();

}
