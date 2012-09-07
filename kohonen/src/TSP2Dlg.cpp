// TSP2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TSP2.h"
#include "TSP2Dlg.h"

#include <math.h>

#include "NetKohonen.h"

#define WM_SET_INFO		(WM_USER + 10)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define STR_ERROR	_T("error")

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
// CTSP2Dlg dialog

CTSP2Dlg::CTSP2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTSP2Dlg::IDD, pParent), m_xPoints(NULL), m_yPoints(NULL)
{
	//{{AFX_DATA_INIT(CTSP2Dlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CTSP2Dlg::~CTSP2Dlg()
{
	Free();
}

void CTSP2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTSP2Dlg)
	DDX_Control(pDX, IDC_STATIC_PATH, m_pathStatic);
	DDX_Control(pDX, IDC_STATIC_ITERATION, m_iterationStatic);
	DDX_Control(pDX, IDC_EDIT_NEURONS, m_neuronsEdit);
	DDX_Control(pDX, IDC_EDIT_MOMENTUM, m_momentumEdit);
	DDX_Control(pDX, IDC_EDIT_LEARN_RATE, m_learnRateEdit);
	DDX_Control(pDX, IDC_EDIT_DELAY, m_delayEdit);
	DDX_Control(pDX, IDC_BUTTON_CREATE_MAP, m_createButton);
	DDX_Control(pDX, IDC_BUTTON_LOAD_MAP, m_loadButton);
	DDX_Control(pDX, IDC_BUTTON_SAVE_MAP, m_saveButton);
	DDX_Control(pDX, IDC_BUTTON_START, m_startButton);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_stopButton);
	DDX_Control(pDX, IDC_STATIC_CITIES, m_citiesStatic);
	DDX_Control(pDX, IDC_EDIT_CITIES, m_citiesEdit);
	DDX_Control(pDX, IDC_STATIC_MAP, m_mapWnd);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTSP2Dlg, CDialog)
	//{{AFX_MSG_MAP(CTSP2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CREATE_MAP, OnButtonCreateMap)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_MAP, OnButtonSaveMap)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_MAP, OnButtonLoadMap)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_MESSAGE(WM_SET_INFO, OnSetInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTSP2Dlg message handlers

// ------------------------------------------------------------
// WM_INITDIALOG - init the dialog
//
BOOL CTSP2Dlg::OnInitDialog()
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
	
	// default values
	m_citiesEdit.SetWindowText(_T("5"));		// cities
	m_neuronsEdit.SetWindowText(_T("10"));		// neurons
	m_learnRateEdit.SetWindowText(_T("0.5"));	// initial learn rate
	m_momentumEdit.SetWindowText(_T("0.995"));	// momentum
	m_delayEdit.SetWindowText(_T("50"));

	m_thread = NULL;
	m_cities = 0;
	ShowCitiesCount();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



// ------------------------------------------------------------
// WM_DESTROY - destroy the dialog
//
void CTSP2Dlg::OnDestroy() 
{
	if (m_thread != NULL)
	{
		// set signal to stop
		m_stop = TRUE;
		// wait for the thread ends
		WaitForSingleObject(m_thread, INFINITE);
		CloseHandle(m_thread);
	}

	CDialog::OnDestroy();
}



// ------------------------------------------------------------
// on system command
//
void CTSP2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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



// ------------------------------------------------------------
// WM_PAINT - paint the window
//
void CTSP2Dlg::OnPaint() 
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



// ------------------------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
// the minimized window.
// 
HCURSOR CTSP2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



// ------------------------------------------------------------
// on WM_COMMAND
// 
BOOL CTSP2Dlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ((wParam == IDOK) ||
		((wParam == IDCANCEL) && (MessageBox(_T("Exit the programm ?"), NULL, MB_YESNO | MB_ICONQUESTION) == IDNO)))
		return TRUE;
	
	return CDialog::OnCommand(wParam, lParam);
}



// ------------------------------------------------------------
// show current cities count
//
void CTSP2Dlg::ShowCitiesCount()
{
	TCHAR	sz[16];

	// convert to str
	_itot(m_cities, sz, 10);
	// show
	m_citiesStatic.SetWindowText(sz);

	// convert to str
	_itot(m_cities * 2, sz, 10);
	m_neuronsEdit.SetWindowText(sz);


	// enable/disable "Start" button
	m_startButton.EnableWindow(m_cities != 0);
}



// ------------------------------------------------------------
// freeeee...dom
//
void CTSP2Dlg::Free()
{
	if (m_xPoints)
	{
		delete [] m_xPoints;
		m_xPoints = NULL;
	}
	if (m_yPoints)
	{
		delete [] m_yPoints;
		m_yPoints = NULL;
	}
}



// ------------------------------------------------------------
// enable controls
//
void CTSP2Dlg::EnableControls(BOOL bEnable)
{
	m_createButton.EnableWindow(bEnable);
	m_saveButton.EnableWindow(bEnable);
	m_loadButton.EnableWindow(bEnable);
	m_startButton.EnableWindow(bEnable);
	m_stopButton.EnableWindow(!bEnable);
}



// ------------------------------------------------------------
// set info
//
void CTSP2Dlg::OnSetInfo(WPARAM wParam, LPARAM lParam)
{
	TCHAR*	sz1 = new TCHAR[32];
	TCHAR*	sz2 = new TCHAR[32];

	// iteration
	_ltot(m_iteration, sz1, 10);
	// path
	_stprintf(sz2, _T("%g"), m_minTour);

	// iteration
	m_iterationStatic.SetWindowText(sz1);

	// path
	m_pathStatic.SetWindowText(sz2);

	delete [] sz1;
	delete [] sz2;
}



// ------------------------------------------------------------
// on button "Create" map
//
void CTSP2Dlg::OnButtonCreateMap() 
{
	CString		str;
	int			i;

	// cities edit box`s text
	m_citiesEdit.GetWindowText(str);

	// convert it to int
	i = _ttoi(str);
	if ((i <= 3) || (i > 20))
	{
		MessageBox(_T("Cities count must be in range [3, 20]."), STR_ERROR, MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		// create new map
		m_mapWnd.CreateNewMap((m_cities = i));
		
		ShowCitiesCount();
	}
}



// ------------------------------------------------------------
// on button "Save" map
//
void CTSP2Dlg::OnButtonSaveMap() 
{
	CFileDialog		fd(FALSE, NULL, _T("map.tsp"), OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, _T("Traveling Salesman Map (*.tsp)|*.tsp||"), this);

	// check cities count
	if (m_cities == 0)
	{
		MessageBox(_T("Nothing to save"), STR_ERROR, MB_OK | MB_ICONHAND);
	}
	else
	{
		// get file name
		if (fd.DoModal() == IDOK)
		{
			if (m_mapWnd.Save(fd.GetPathName()) != 0)
				MessageBox(_T("Failed saving the map"), STR_ERROR, MB_OK | MB_ICONHAND);
		}
	}
}



// ------------------------------------------------------------
// on button "Load" map
//
void CTSP2Dlg::OnButtonLoadMap() 
{
	CFileDialog		fd(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("Traveling Salesman Map (*.tsp)|*.tsp||"), this);

	// get file name
	if (fd.DoModal() == IDOK)
	{
		if (m_mapWnd.Load(fd.GetPathName()) != 0)
			MessageBox(_T("Failed loading a map"), STR_ERROR, MB_OK | MB_ICONHAND);

		m_cities = m_mapWnd.GetPointsCount();
		ShowCitiesCount();
	}	
}



// ------------------------------------------------------------
// on button "Start"
//
void CTSP2Dlg::OnButtonStart() 
{
	CString	str;
	DWORD	id;

	// free old
	Free();

	// neurons
	m_neuronsEdit.GetWindowText(str);
	m_neurons = _ttoi(str);
	if (m_neurons < m_cities)
	{
//		MessageBox(_T("Neurons count must be al least as cities count"), STR_ERROR, MB_OK | MB_ICONHAND);
//		return;
	}

	// learn rate
	m_learnRateEdit.GetWindowText(str);
	if (_stscanf(str, _T("%f"), &m_learnRate) != 1)
	{
		MessageBox(_T("Invalid initial learn rate"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// momentum
	m_momentumEdit.GetWindowText(str);
	if (_stscanf(str, _T("%f"), &m_momentum) != 1)
	{
		MessageBox(_T("Invalid momentum"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// delay
	m_delayEdit.GetWindowText(str);
	m_delay = _ttoi(str);

	// alloc new
	m_xPoints = new short[m_cities];
	m_yPoints = new short[m_cities];

	m_mapWnd.GetPoints(m_xPoints, m_yPoints);

	EnableControls(FALSE);

	// start thread
	m_stop		= FALSE;
	m_thread	= CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE) ThreadProc,
		(void *) this, 0, &id);
}



// ------------------------------------------------------------
// on button "Stop"
//
void CTSP2Dlg::OnButtonStop() 
{
	if (m_thread != NULL)
	{
		// set signal to stop
		m_stop = TRUE;
		// wait for the thread ends
		WaitForSingleObject(m_thread, INFINITE);
		CloseHandle(m_thread);

		m_thread = NULL;

		EnableControls(TRUE);
	}
}



// ------------------------------------------------------------
// thread function
//
DWORD CTSP2Dlg::ThreadProc(CTSP2Dlg* me)
{
	CNetKohonen		net;
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;

	short*			xPoints		= me->m_xPoints;
	short*			yPoints		= me->m_yPoints;
	int				cities		= me->m_cities;
	int				neurons		= me->m_neurons;

	float			learnRate	= me->m_learnRate;
	float			momentum	= me->m_momentum;
	float			in[2];
	int				i;
	long			delay		= me->m_delay;
	long			iteration	= 0;

	float			noise		= 0.05f;

	short*			xWay = new short[neurons];
	short*			yWay = new short[neurons];
	float			prevx, prevy, path, x, y, dx, dy;

	TCHAR*			sz = new TCHAR[32];

	CNeuron::SetAlfa(0.001f);

	// create net & randomize it
	net.InitEx(2, neurons);
	net.Randomize(150, 0);
	layer = net.GetLayer(0);

	while (!me->m_stop)
	{
		// get last neuron
		neuron	= layer->GetNeuron(neurons - 1);
		path	= 0;
		prevx	= neuron->GetSynapse(0);
		prevy	= neuron->GetSynapse(1);

		// get way
		for (i = 0; i < neurons; i++)
		{
			// get neuron
			neuron = layer->GetNeuron(i);

			// get it`s weights
			xWay[i] = (short) (x = neuron->GetSynapse(0));
			yWay[i] = (short) (y = neuron->GetSynapse(1));

			dx		= prevx - x;
			dy		= prevy - y;
			prevx	= x;
			prevy	= y;

			path += (float) sqrt(dx * dx + dy * dy);
		}
		// show current way
		me->m_mapWnd.SetWay(xWay, yWay, neurons);

		me->m_iteration	= iteration;
		me->m_minTour	= path;

		me->PostMessage(WM_SET_INFO);

		// set learn rate
		net.SetLearnRate(learnRate);

		// get random city
		i = rand() % cities;
		in[0] = xPoints[i];
		in[1] = yPoints[i];

		// add small noise
		in[0] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);
		in[1] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);

		// set net inputs
		net.SetInputs(in);
		net.Propagate();
		net.LearnGaussian();

		// modify learn rate
		learnRate *= momentum;

		iteration++;

		Sleep(delay);
	}

	delete[] xWay;
	delete[] yWay;

	delete[] sz;

	return 0;
}
