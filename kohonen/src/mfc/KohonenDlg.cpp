// KohonenDlg.cpp : implementation file
//

#include "stdafx.h"

#include "KohonenDlg.h"
#include "NetKohonen.h"

#define WM_SET_INFO		(WM_USER + 10)


#define STR_ERROR	_T("error")

WNDPROC wpOrigMapWndProc; 
 
// Subclass procedure 
LRESULT APIENTRY KohonenMapWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 

    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
    if (uMsg == WM_PAINT ) 
	{
		KohonenDlg * nnet_dlg = 
			(KohonenDlg *)GetWindowLong(hwnd,GWL_USERDATA);
		nnet_dlg->m_mapWnd.OnPaint(hwnd);
	} 
    return CallWindowProc(wpOrigMapWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 

/////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK DlgProcKohonenNNet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
	static KohonenDlg * nnet_dlg;
    switch (message) 
    { 
	case WM_INITDIALOG:
		{
			nnet_dlg = reinterpret_cast<KohonenDlg *>(lParam);
			nnet_dlg->hDlg = hDlg;
			nnet_dlg->OnInitDialog();
		}
		break;
	case WM_SET_INFO:
		{
			nnet_dlg->OnSetInfo(0,0);
		}
		break;
    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        {
		case IDC_BUTTON_KOHONEN_START:
			{
				nnet_dlg->OnButtonStart();
			}
			break;
		case IDC_BUTTON_KOHONEN_STOP:
			{
				nnet_dlg->OnButtonStop();
			}
			break;
/*		case IDC_BUTTON_TRAJ_VIEW_BEGIN:
			{
				nnet_dlg->handler_ButtonBegin(NULL, nnet_dlg);
			}
			break;
		case IDC_BUTTON_TRAJ_VIEW_PREV:
			{
				nnet_dlg->handler_ButtonPrev(NULL, nnet_dlg);
			}
			break;
		case IDC_BUTTON_TRAJ_VIEW_PLAY:
			{
				DWORD dwChildID;
				HANDLE hThread;
				hThread = ::CreateThread(NULL, 0, 
					traj_dlg->handler_ButtonPlay, 
					reinterpret_cast<LPVOID>(traj_dlg), 
					0,
					&dwChildID );
			}
			break;
		case IDC_BUTTON_TRAJ_VIEW_NEXT:
			{
				traj_dlg->handler_ButtonNext(NULL, traj_dlg);
			}
			break;
		case IDC_BUTTON_TRAJ_VIEW_END:
			{
				traj_dlg->handler_ButtonEnd(NULL, traj_dlg);
			}
			break;*/
		case IDOK: 

        case IDCANCEL: 
            EndDialog(hDlg, wParam); 
            return TRUE; 
        } 
		break;
	case WM_DESTROY:
		{
            // Remove the subclass from the map control. 
            SetWindowLong(nnet_dlg->m_mapWnd.hwnd, GWL_WNDPROC, 
                (LONG) wpOrigMapWndProc); 
			nnet_dlg->OnDestroy();
			delete nnet_dlg;
		}
    } 
    return FALSE; 
} 

extern HINSTANCE hInst;   // текущий экземпл€р


/////////////////////////////////////////////////////////////////////////////
// KohonenDlg dialog
void KohonenDlg::ExtremePoints()
{
	for (int i = 0; i < m_cities; i++)
	{
		if ( i == 0 )
		{
			m_ixMax = m_ixMin = m_ixPoints[i];
			m_iyMax = m_iyMin = m_iyPoints[i];
		}
		else
		{
			if (m_ixMax < m_ixPoints[i]) m_ixMax = m_ixPoints[i];
			if (m_ixMin > m_ixPoints[i]) m_ixMin = m_ixPoints[i];
			if (m_iyMax < m_iyPoints[i]) m_iyMax = m_iyPoints[i];
			if (m_iyMin > m_iyPoints[i]) m_iyMin = m_iyPoints[i];
		}
	}
}

KohonenDlg::KohonenDlg(int n, double * xp, double * yp)
{
	m_cities = n;
	// alloc new
	m_xPoints = new double[m_cities];
	m_yPoints = new double[m_cities];
	m_ixPoints = new double[m_cities];
	m_iyPoints = new double[m_cities];
	for (int i = 0; i < m_cities; i++)
	{
		m_ixPoints[i] = xp[i];
		m_iyPoints[i] = yp[i];
	}
	ExtremePoints();
	// переводим входы в интервал от 0 до 100
	for ( i = 0; i < m_cities; i++)
	{
		m_xPoints[i] = 0. + (100. - 0.)*(m_ixPoints[i] - m_ixMin) / (m_ixMax - m_ixMin);
		m_yPoints[i] = 0. + (100. - 0.)*(m_iyPoints[i] - m_iyMin) / (m_iyMax - m_iyMin);

		m_xPoints[i] = m_ixPoints[i];
		m_yPoints[i] = m_iyPoints[i];
	}
	//
	HANDLE hDialog = LoadResource( hInst,
					FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KOHONEN),
								  RT_DIALOG ) );

	LPVOID lpDialog = LockResource( hDialog );

	HWND hdlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, 
		NULL/*hWnd*/,
		(DLGPROC)DlgProcKohonenNNet,
		(LPARAM)this );
	ShowWindow(hdlg, SW_SHOW);
}

KohonenDlg::~KohonenDlg()
{
	Free();
}

/////////////////////////////////////////////////////////////////////////////
// KohonenDlg message handlers

// ------------------------------------------------------------
// WM_INITDIALOG - init the dialog
//
BOOL KohonenDlg::OnInitDialog()
{
//	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
//	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
//	ASSERT(IDM_ABOUTBOX < 0xF000);

/*	CMenu* pSysMenu = GetSystemMenu(FALSE);
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
*/
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_NEURONS, _T("10") );		// neurons
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_LEARN_RATE, _T("0.5") );	// initial learn rate
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_MOMENTUM, _T("0.999") );	// momentum
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DELAY, _T("10") );	

    // Retrieve the handle to the Map control. 
    this->m_mapWnd.hwnd = GetDlgItem(hDlg, IDC_STATIC_KOHONEN_MAP); 

    // Subclass the control. 
    wpOrigMapWndProc = (WNDPROC) SetWindowLong(this->m_mapWnd.hwnd, 
        GWL_WNDPROC, (LONG) KohonenMapWndSubclassProc); 

	SetWindowLong(this->m_mapWnd.hwnd, GWL_USERDATA,(LONG)this);

	char str[255];
	sprintf(str, " hDlg = %x", hDlg);
	MessageBox(0,str,"OnInitDialog",0);

	m_thread = NULL;
	ShowCitiesCount();
	OnButtonCreateMap();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}



// ------------------------------------------------------------
// WM_DESTROY - destroy the dialog
//
void KohonenDlg::OnDestroy() 
{
	if (m_thread != NULL)
	{
		// set signal to stop
		m_stop = TRUE;
		// wait for the thread ends
		WaitForSingleObject(m_thread, INFINITE);
		CloseHandle(m_thread);
	}

//	CDialog::OnDestroy();
}



// ------------------------------------------------------------
// on system command
//
/*void KohonenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
*/


// ------------------------------------------------------------
// WM_PAINT - paint the window
//
/*void KohonenDlg::OnPaint() 
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
}*/



// ------------------------------------------------------------
// The system calls this to obtain the cursor to display while the user drags
// the minimized window.
// 
HCURSOR KohonenDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



// ------------------------------------------------------------
// on WM_COMMAND
// 
/*
BOOL KohonenDlg::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if ((wParam == IDOK) ||
		((wParam == IDCANCEL) && (MessageBox(_T("Exit the programm ?"), NULL, MB_YESNO | MB_ICONQUESTION) == IDNO)))
		return TRUE;
	
	return CDialog::OnCommand(wParam, lParam);
}*/



// ------------------------------------------------------------
// show current cities count
//
void KohonenDlg::ShowCitiesCount()
{
	char str[255];
	sprintf(str, " hDlg = %x", hDlg);
	MessageBox(0,str,"ShowCitiesCount",0);
	TCHAR	sz[16];
	// convert to str
	_itot(m_cities, sz, 10);
	// show
	//	m_citiesStatic.SetWindowText(sz);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_N_INPUT_VECTORS, sz);
	// convert to str
	_itot(m_cities * 2, sz, 10);
	//	m_neuronsEdit.SetWindowText(sz);


	// enable/disable "Start" button
	//	m_startButton.EnableWindow(m_cities != 0);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_START), m_cities != 0);
}



// ------------------------------------------------------------
// freeeee...dom
//
void KohonenDlg::Free()
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
void KohonenDlg::EnableControls(BOOL bEnable)
{
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_KOHONEN_N_INPUT_VECTORS), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_START), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_STOP), !bEnable);
//	m_createButton.EnableWindow(bEnable);
//	m_saveButton.EnableWindow(bEnable);
//	m_loadButton.EnableWindow(bEnable);
//	m_startButton.EnableWindow(bEnable);
//	m_stopButton.EnableWindow(!bEnable);
}



// ------------------------------------------------------------
// set info
//
void KohonenDlg::OnSetInfo(WPARAM wParam, LPARAM lParam)
{
	TCHAR*	sz1 = new TCHAR[32];
	TCHAR*	sz2 = new TCHAR[32];

	// iteration
	_ltot(m_iteration, sz1, 10);
	// path
	_stprintf(sz2, _T("%g"), m_minTour);

	// iteration
//	m_iterationStatic.SetWindowText(sz1);
	SetDlgItemText(hDlg,IDC_STATIC_KOHONEN_ITERATIONS, sz1);

	// path
//	m_pathStatic.SetWindowText(sz2);
	SetDlgItemText(hDlg,IDC_STATIC_KOHONEN_PATH, sz2);

	delete [] sz1;
	delete [] sz2;
}



// ------------------------------------------------------------
// on button "Create" map
//
void KohonenDlg::OnButtonCreateMap() 
{
	char		str[255];
	int			i;

	// cities edit box`s text
	//m_citiesEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_N_INPUT_VECTORS, str,sizeof(str));

	// convert it to int
	i = _ttoi(str);
	if ((i <= 3) /*|| (i > 20)*/)
	{
		MessageBox(hDlg, _T("Cities count must be more than 3."), STR_ERROR, MB_OK | MB_ICONINFORMATION);
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
void KohonenDlg::OnButtonSaveMap() 
{
/*	CFileDialog		fd(FALSE, NULL, _T("map.tsp"), OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, _T("Traveling Salesman Map (*.tsp)|*.tsp||"), this);

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
	}*/
}



// ------------------------------------------------------------
// on button "Load" map
//
void KohonenDlg::OnButtonLoadMap() 
{
/*	CFileDialog		fd(TRUE, NULL, NULL, OFN_FILEMUSTEXIST, _T("Traveling Salesman Map (*.tsp)|*.tsp||"), this);

	// get file name
	if (fd.DoModal() == IDOK)
	{
		if (m_mapWnd.Load(fd.GetPathName()) != 0)
			MessageBox(_T("Failed loading a map"), STR_ERROR, MB_OK | MB_ICONHAND);

		m_cities = m_mapWnd.GetPointsCount();
		ShowCitiesCount();
	}*/	
}



// ------------------------------------------------------------
// on button "Start"
//
void KohonenDlg::OnButtonStart() 
{

	DWORD	id;
//	CString	str;
	char str[255];

	// free old
	// Free();
	// neurons
	//	m_neuronsEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_NEURONS, str, sizeof(str));
	m_neurons = _ttoi(str);

	// learn rate
	//	m_learnRateEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_LEARN_RATE, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_learnRate) != 1)
	{
		MessageBox(hDlg, _T("Invalid initial learn rate"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// momentum
	//	m_momentumEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_MOMENTUM, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_momentum) != 1)
	{
		MessageBox(hDlg, _T("Invalid momentum"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// delay
	//	m_delayEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DELAY, str, sizeof(str));
	m_delay = _ttoi(str);
	m_mapWnd.SetPoints(m_xPoints, m_yPoints);

	EnableControls(FALSE);

	// start thread
	m_stop		= FALSE;
	m_thread	= CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE) ThreadProc,
		(void *) this, 0, &id);
}



// ------------------------------------------------------------
// on button "Stop"
//
void KohonenDlg::OnButtonStop() 
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
DWORD KohonenDlg::ThreadProc(KohonenDlg* me)
{
	CNetKohonen		net;
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;

	double*			xPoints		= me->m_xPoints;
	double*			yPoints		= me->m_yPoints;
	int				cities		= me->m_cities;
	int				neurons		= me->m_neurons;

	float			learnRate	= me->m_learnRate;
	float			momentum	= me->m_momentum;
	float			in[2];
	int				i;
	long			delay		= me->m_delay;
	long			iteration	= 0;

	float			noise		= 0.05f;

	double*			xWay = new double[neurons];
	double*			yWay = new double[neurons];
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
			xWay[i] = (float) (x = neuron->GetSynapse(0));
			yWay[i] = (float) (y = neuron->GetSynapse(1));

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

//		me->PostMessage(WM_SET_INFO);
		PostMessage(me->hDlg,WM_SET_INFO, 0, 0);

		// set learn rate
		net.SetLearnRate(learnRate);
		// get random city
		i = rand() % cities;
		in[0] = xPoints[i];
		in[1] = yPoints[i];

		// add small noise
//		in[0] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);
//		in[1] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);

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
