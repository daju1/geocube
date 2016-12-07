// KohonenDlg.cpp : implementation file
//

//#include "../stdafx.h"
#include "stdafx.h"
#include "../resource.h"

#include <vector>
#include <string>
using namespace std ;

#include "../../array/src/vdouble.h"
#include "../../array/src/matrixes.h"
#include "../../array/src/interp.h"

#include "KohonenDlg.h"
#include "NetKohonen.h"
#include "../../wintools/src/winsurf.h"


#include "../../wintools/src/win32_app.h"
#include "../../wintools/src/utility.h"
#include "../../wintools/src/winsurf.h"


#define WM_SET_INFO		(WM_USER + 10)


#define STR_ERROR	_T("error")

bool KohonenDlg::s_toCreateSurfWindowOnThread	= false;
bool KohonenDlg::s_WinnersGot					= false;

WNDPROC wpOrigMapWndProc; 

extern void randpermute(int n, vector<int>& result);

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
			(KohonenDlg *)GetWindowLongPtr(hwnd,GWLP_USERDATA);
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
		case IDC_BUTTON_KOHONEN_SAVE_RESULT:
			{
				nnet_dlg->ResultsSaveAs();
			}
			break;
		case IDC_BUTTON_KOHONEN_SURF_RESULT:
			{
				//if(nnet_dlg->m_thread == NULL)
				//{
				//	if(nnet_dlg->hSurfWnd == NULL)
				//	{
#if 1
						DWORD	id;
						CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)  KohonenDlg::ShowSpheres,
							(void *) nnet_dlg, 0, &id);
#else
						KohonenDlg::SurfResults(nnet_dlg);
#endif
				//	}
				//}
				//else
				//{
				//	if(nnet_dlg->hSurfWnd == NULL)
				//	{
				//		KohonenDlg::s_toCreateSurfWindowOnThread = true;
				//	}
				//}
			}
			break;
		case IDC_BUTTON_KOHONEN_SAVE_CLASESS:
			{
				nnet_dlg->ClassesSaveAs();
			}
			break;
		/*case IDC_BUTTON_KOHONEN_SAVE_POINTS:
			{
				nnet_dlg->PointsSaveAs();
			}
			break;*/
		case IDC_COMBO_KOHONEN_MAP_J0:
			{
				nnet_dlg->m_j0 = 
					SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J0, CB_GETCURSEL,0,(LPARAM)0 );
				if (nnet_dlg->m_j0 >= 0 && nnet_dlg->m_j0 < nnet_dlg->m_nParameters)
					nnet_dlg->m_mapWnd.SetPoints(nnet_dlg->m_Points[nnet_dlg->m_j0], nnet_dlg->m_Points[nnet_dlg->m_j1]);
				else
					MessageBox(0, "IDC_COMBO_KOHONEN_MAP_J0","",0);
			}
			break;
		case IDC_COMBO_KOHONEN_MAP_J1:
			{
				nnet_dlg->m_j1 = 
					SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J1, CB_GETCURSEL,0,(LPARAM)0 );
				if (nnet_dlg->m_j1 >= 0 && nnet_dlg->m_j1 < nnet_dlg->m_nParameters)
					nnet_dlg->m_mapWnd.SetPoints(nnet_dlg->m_Points[nnet_dlg->m_j0], nnet_dlg->m_Points[nnet_dlg->m_j1]);
				else
					MessageBox(0, "IDC_COMBO_KOHONEN_MAP_J1","",0);
			}
			break;
		case IDOK :
			{
				EndDialog( hDlg, 0 );
			}
			break;
			
		case IDCANCEL :
			nnet_dlg->OnButtonStop();
			EndDialog( hDlg, IDCANCEL );
			break;
        } 
		break;
	case WM_DESTROY:
		{
            // Remove the subclass from the map control. 
            SetWindowLongPtr(nnet_dlg->m_mapWnd.hwnd, GWLP_WNDPROC, 
                (LONG_PTR) wpOrigMapWndProc); 
			nnet_dlg->OnDestroy();
			delete nnet_dlg;
		}
    } 
    return FALSE; 
} 

extern HINSTANCE hInst;   // текущий экземпл€р


/////////////////////////////////////////////////////////////////////////////
// KohonenDlg dialog
void KohonenDlg::ExtremeParameterPoints()
{
	for (int i = 0; i < m_examples; i++)
	{
		if ( i == 0 )
		{
			for (int j = 0; j < m_nParameters; j++)
			{
				m_inMax[j] = m_inMin[j] = m_inPoints[j][i];
			}
		}
		else
		{
			for (int j = 0; j < m_nParameters; j++)
			{
				if (m_inMax[j] < m_inPoints[j][i]) m_inMax[j] = m_inPoints[j][i];
				if (m_inMin[j] > m_inPoints[j][i]) m_inMin[j] = m_inPoints[j][i];
			}
		}
	}
}
//DEL void KohonenDlg::ExtremePoints()
//DEL {
//DEL 	for (int i = 0; i < m_examples; i++)
//DEL 	{
//DEL 		if ( i == 0 )
//DEL 		{
//DEL 			m_ixMax = m_ixMin = m_ixPoints[i];
//DEL 			m_iyMax = m_iyMin = m_iyPoints[i];
//DEL 		}
//DEL 		else
//DEL 		{
//DEL 			if (m_ixMax < m_ixPoints[i]) m_ixMax = m_ixPoints[i];
//DEL 			if (m_ixMin > m_ixPoints[i]) m_ixMin = m_ixPoints[i];
//DEL 			if (m_iyMax < m_iyPoints[i]) m_iyMax = m_iyPoints[i];
//DEL 			if (m_iyMin > m_iyPoints[i]) m_iyMin = m_iyPoints[i];
//DEL 		}
//DEL 	}
//DEL }

double KohonenDlg::ZoomParameterIn(double v, int j)
{
	return 0. + (100. - 0.)*(v - m_inMin[j]) / (m_inMax[j] - m_inMin[j]);
}
//DEL double KohonenDlg::ZoomIn(double v, int n)
//DEL {
//DEL 	switch(n)
//DEL 	{
//DEL 	case 0:
//DEL 		{
//DEL 			return 0. + (100. - 0.)*(v - m_ixMin) / (m_ixMax - m_ixMin);
//DEL 		}
//DEL 		break;
//DEL 	case 1:
//DEL 		{
//DEL 			return 0. + (100. - 0.)*(v - m_iyMin) / (m_iyMax - m_iyMin);
//DEL 		}
//DEL 		break;
//DEL 	}
//DEL 	return 0.0;
//DEL }
double KohonenDlg::ZoomParameterOut(double v, int j)
{
	return m_inMin[j] + (m_inMax[j] - m_inMin[j])*(v - 0.) / (100. - 0.);
}
//DEL double KohonenDlg::ZoomOut(double v, int n)
//DEL {
//DEL 	switch(n)
//DEL 	{
//DEL 	case 0:
//DEL 		{
//DEL 			return m_ixMin + (m_ixMax - m_ixMin)*(v - 0.) / (100. - 0.);
//DEL 		}
//DEL 		break;
//DEL 	case 1:
//DEL 		{
//DEL 			return m_iyMin + (m_iyMax - m_iyMin)*(v - 0.) / (100. - 0.);
//DEL 		}
//DEL 		break;
//DEL 	}
//DEL 	return 0.0;
//DEL }

void KohonenDlg::ZoomParameterIn()
{
	for ( int i = 0; i < m_examples; i++)
	{
		for (int j = 0; j < m_nParameters; j++)
			m_Points[j][i] = ZoomParameterIn(m_inPoints[j][i], j);
	}
}

void KohonenDlg::RangeOfPoints()
{
	for (int j = 0; j < m_nParameters; j++)
	{
		for ( int i = 0; i < m_examples; i++)
		{
			if (i == 0)
			{
				m_minOfPoints[j] = m_maxOfPoints[j] = m_Points[j][i];
			}
			else
			{
				if ( m_minOfPoints[j] > m_Points[j][i] ) m_minOfPoints[j] = m_Points[j][i];
				if ( m_maxOfPoints[j] < m_Points[j][i] ) m_maxOfPoints[j] = m_Points[j][i];
			}
		}
	}
}

//DEL void KohonenDlg::ZoomIn()
//DEL {
//DEL 	for ( int i = 0; i < m_examples; i++)
//DEL 	{
//DEL //		m_xPoints[i] = 0. + (100. - 0.)*(m_ixPoints[i] - m_ixMin) / (m_ixMax - m_ixMin);
//DEL //		m_yPoints[i] = 0. + (100. - 0.)*(m_iyPoints[i] - m_iyMin) / (m_iyMax - m_iyMin);
//DEL 
//DEL 		m_xPoints[i] = ZoomIn(m_ixPoints[i], 0);
//DEL 		m_yPoints[i] = ZoomIn(m_iyPoints[i], 1);
//DEL 
//DEL //		m_xPoints[i] = m_ixPoints[i];
//DEL //		m_yPoints[i] = m_iyPoints[i];
//DEL 	}
//DEL }
KohonenDlg::KohonenDlg(vector<double>& X, vector<double>& Y, vector<double>& Z, vector<vector<double> >& MM, string name, bool modal)	// standard constructor
{
	printf("KohonenDlg::KohonenDlg\n");

	m_examples = MM.size();

	if (m_examples == 0)
	{
		MessageBox(0,"Error\nm_examples == 0", "KohonenDlg::KohonenDlg", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	if (
		m_examples != X.size() ||
		m_examples != Y.size() ||
		m_examples != Z.size())
	{
		MessageBox(0,
			"Error\n"
			"m_examples != X.size() ||\n"
			"m_examples != Y.size() ||\n"
			"m_examples != Z.size()", 
			"KohonenDlg::KohonenDlg", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


	m_bInited = false;
	hSurfWnd = NULL;
	m_name = name;
	int nch;
	while ((nch = m_name.find('\"')) != -1)
	{
		m_name.erase(nch,1);
	}

	m_nParameters = MM[0].size();

	m_j0 = 0;
	m_j1 = m_nParameters > 1 ? 1 : 0;

	// alloc new
	m_X = new double[m_examples];
	m_Y = new double[m_examples];
	m_Z = new double[m_examples];

	m_inMax = new double[m_nParameters];
	m_inMin = new double[m_nParameters];

	m_minOfPoints = new float[m_nParameters];
	m_maxOfPoints = new float[m_nParameters];

	m_Points   = AllocDoubleMat(m_nParameters, m_examples);
	m_inPoints = AllocDoubleMat(m_nParameters, m_examples);

	m_winners = new int[m_examples];
	//
	for (int i = 0; i < m_examples; i++)
	{
		for (int j = 0; j < m_nParameters; j++)
		{
			m_inPoints[j][i] = MM[i][j];
			/*if (p[j][i] > 1.0)
				printf("p[%d][%d] = %lf\n", j, i, p[j][i]);*/
		}
		// geocoordinates if input points
		m_X[i] = X[i];
		m_Y[i] = Y[i];
		m_Z[i] = Z[i];

		printf(
			"X[%d] = %lf"
			"Y[%d] = %lf"
			"Z[%d] = %lf"
			"\n"
			, i, X[i]
			, i, Y[i]
			, i, Z[i]
			);
	}
	ExtremeParameterPoints();
	// переводим входы в интервал от 0 до 100
	ZoomParameterIn();
	RangeOfPoints();
	if (modal)
	{
		DialogBoxParam( 
			hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_KOHONEN), 
			NULL,
			(DLGPROC)DlgProcKohonenNNet,
			(LPARAM)this);
	}
	else
	{
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
}


KohonenDlg::KohonenDlg(int nExamples, double *X, double *Y, double *Z, int nParameters, double ** p, string name, bool modal)	// standard constructor
{
	printf("KohonenDlg::KohonenDlg\n");

	m_bInited = false;
	hSurfWnd = NULL;
	m_name = name;
	int nch;
	while ((nch = m_name.find('\"')) != -1)
	{
		m_name.erase(nch,1);
	}

	m_examples = nExamples;
	m_nParameters = nParameters;

	m_j0 = 0;
	m_j1 = nParameters > 1 ? 1 : 0;

	// alloc new
	m_X = new double[m_examples];
	m_Y = new double[m_examples];
	m_Z = new double[m_examples];

	m_inMax = new double[m_nParameters];
	m_inMin = new double[m_nParameters];

	m_minOfPoints = new float[m_nParameters];
	m_maxOfPoints = new float[m_nParameters];

	m_Points   = AllocDoubleMat(m_nParameters, m_examples);
	m_inPoints = AllocDoubleMat(m_nParameters, m_examples);

	m_winners = new int[m_examples];
	//
	for (int i = 0; i < m_examples; i++)
	{
		for (int j = 0; j < m_nParameters; j++)
		{
			m_inPoints[j][i] = p[j][i];
			/*if (p[j][i] > 1.0)
				printf("p[%d][%d] = %lf\n", j, i, p[j][i]);*/
		}
		// geocoordinates if input points
		m_X[i] = X[i];
		m_Y[i] = Y[i];
		m_Z[i] = Z ? Z[i] : 0.0;

		printf(
			"X[%d] = %lf"
			"Y[%d] = %lf"
			"Z[%d] = %lf"
			"\n"
			, i, X[i]
			, i, Y[i]
			, i, Z[i]
			);
	}
	ExtremeParameterPoints();
	// переводим входы в интервал от 0 до 100
	ZoomParameterIn();
	RangeOfPoints();
	if (modal)
	{
		DialogBoxParam( 
			hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_KOHONEN), 
			NULL,
			(DLGPROC)DlgProcKohonenNNet,
			(LPARAM)this);
	}
	else
	{
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
}

KohonenDlg::KohonenDlg(int n, double *X, double *Y, double *Z, double * xp, double * yp, bool modal)
{
	m_bInited = false;
	hSurfWnd = NULL;
	m_examples = n;
	m_nParameters = 2;
	// alloc new
	m_X = new double[m_examples];
	m_Y = new double[m_examples];
	m_Z = new double[m_examples];

	m_inMax = new double[m_nParameters];
	m_inMin = new double[m_nParameters];

	m_minOfPoints = new float[m_nParameters];
	m_maxOfPoints = new float[m_nParameters];

	m_Points   = AllocDoubleMat(m_nParameters, m_examples);
	m_inPoints = AllocDoubleMat(m_nParameters, m_examples);

	m_j0 = 0;
	m_j1 = 1;

//	m_xPoints = new double[m_examples];
//	m_yPoints = new double[m_examples];
//	m_ixPoints = new double[m_examples];
//	m_iyPoints = new double[m_examples];


	m_winners = new int[m_examples];
	//
	for (int i = 0; i < m_examples; i++)
	{
		//m_ixPoints[i] = xp[i];
		//m_iyPoints[i] = yp[i];
		m_inPoints[0][i] = xp[i];
		m_inPoints[1][i] = yp[i];
		// geocoordinates if input points
		m_X[i] = X[i];
		m_Y[i] = Y[i];
		m_Z[i] = Z ? Z[i] : 0.0;
	}
	ExtremeParameterPoints();
	// переводим входы в интервал от 0 до 100
	ZoomParameterIn();
	RangeOfPoints();
	if (modal)
	{
		DialogBoxParam( 
			hInst, 
			MAKEINTRESOURCE(IDD_DIALOG_KOHONEN), 
			NULL,
			(DLGPROC)DlgProcKohonenNNet,
			(LPARAM)this);
	}
	else
	{
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
	int j;
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

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J0, CB_RESETCONTENT, 0,0);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	for (j = 0; j < m_nParameters; j++)
	{
		char str[16];
		sprintf_s(str, 16, "%d", j);
		SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J0, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)str);
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J0, CB_SETCURSEL,
		m_j0,(LPARAM)0 );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J1, CB_RESETCONTENT, 0,0);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	for ( j = 0; j < m_nParameters; j++)
	{
		char str[16];
		sprintf_s(str, 16, "%d", j);
		SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J1, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)str);
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_MAP_J1, CB_SETCURSEL,
		m_j1,(LPARAM)0 );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_RESETCONTENT, 0,0);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"Gaussian");
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"Conscience");
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"Gaussian+Conscience");
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"Gaussian 2");
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"Conscience 2");
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"Gaussian+Conscience 2");
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_SETCURSEL,
		0,(LPARAM)0 );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_SURF_RESULT_TYPE, CB_RESETCONTENT, 0,0);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_SURF_RESULT_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"griddata");
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_SURF_RESULT_TYPE, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"spheres");
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_SURF_RESULT_TYPE, CB_SETCURSEL,
		1,(LPARAM)0 );
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	

	InitParams();


    // Retrieve the handle to the Map control. 
    this->m_mapWnd.hwnd = GetDlgItem(hDlg, IDC_STATIC_KOHONEN_MAP); 

    // Subclass the edit control. 
    wpOrigMapWndProc = (WNDPROC) SetWindowLongPtr(this->m_mapWnd.hwnd, 
        GWLP_WNDPROC, (LONG_PTR) KohonenMapWndSubclassProc); 

	SetWindowLongPtr(this->m_mapWnd.hwnd, GWLP_USERDATA,(LONG_PTR)this);


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
	TCHAR	sz[16];
	// convert to str
	_itot(m_examples, sz, 10);
	// show
	//	m_citiesStatic.SetWindowText(sz);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_N_INPUT_VECTORS, sz);
	// convert to str
//	_itot(m_examples * 2, sz, 10);
	//	m_neuronsEdit.SetWindowText(sz);


	// enable/disable "Start" button
	//	m_startButton.EnableWindow(m_examples != 0);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_START), m_examples != 0);
}



// ------------------------------------------------------------
// freeeee...dom
//
void KohonenDlg::Free()
{
/*	if (m_xPoints)
	{
		delete [] m_xPoints;
		m_xPoints = NULL;
	}
	if (m_yPoints)
	{
		delete [] m_yPoints;
		m_yPoints = NULL;
	}
	if (m_ixPoints)
	{
		delete [] m_ixPoints;
		m_ixPoints = NULL;
	}
	if (m_iyPoints)
	{
		delete [] m_iyPoints;
		m_iyPoints = NULL;
	}*/
	if (m_X)
	{
		delete [] m_X;
		m_X = NULL;
	}
	if (m_Y)
	{
		delete [] m_Y;
		m_Y = NULL;
	}	
	if (m_Z)
	{
		delete [] m_Z;
		m_Z = NULL;
	}
	if(m_winners)
	{
		delete [] m_winners;
		m_winners = NULL;
	}
	if (m_Points)
	{	 
		FreeDoubleMat(m_Points);
		m_Points = NULL;
	}
	if (m_inPoints)
	{	 
		FreeDoubleMat(m_inPoints);
		m_inPoints = NULL;
	}
	if(m_minOfPoints)
	{
		delete [] m_minOfPoints;
		m_minOfPoints = NULL;
	}
	if(m_maxOfPoints)
	{
		delete [] m_maxOfPoints;
		m_maxOfPoints = NULL;
	}
}



// ------------------------------------------------------------
// enable controls
//
void KohonenDlg::EnableControls(BOOL bEnable)
{
/*	static HMENU hMenu;
	if(!bEnable)
	{
		hMenu = GetSystemMenu(hDlg,TRUE);
		SetMenu(hDlg, NULL);
	}
	else
	{
		SetMenu(hDlg, hMenu);
	}*/

//	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_SURF_RESULT), bEnable);
	//EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_SAVE_POINTS), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_SAVE_CLASESS), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_SAVE_RESULT), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_KOHONEN_N_INPUT_VECTORS), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_START), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_KOHONEN_STOP), !bEnable);
//	m_createButton.EnableWindow(bEnable);
//	m_saveButton.EnableWindow(bEnable);
//	m_loadButton.EnableWindow(bEnable);
//	m_startButton.EnableWindow(bEnable);
//	m_stopButton.EnableWindow(!bEnable);
}

void KohonenDlg::InitParams(bool firstly)
{
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_NEURONS, _T("10") );		// neurons
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_NEURONS_DY, _T("10") );		// neurons
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DELAY, _T("10") );
	if (firstly)
	{

		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_LEARN_RATE, _T("0.1") );	// initial learn rate
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_LEARN_RATE, _T("0.1") );	// initial learn rate
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_LEARN_RATE, _T("0.0001") );	// initial learn rate

		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_MOMENTUM, _T("0.99") );	// momentum
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_MOMENTUM, _T("0.90") );	// momentum
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_MOMENTUM, _T("0.99") );	// momentum

	}
	else
	{
		TCHAR*	sz1 = new TCHAR[32];
		TCHAR*	sz2 = new TCHAR[32];

		sprintf(sz1, "%f", m_learnRate);
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_LEARN_RATE, sz1 );	// initial learn rate
		sprintf(sz2, "%f", m_momentum);
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_MOMENTUM, sz2 );	// momentum

		sprintf(sz1, "%f", m_learnRateDistance);
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_LEARN_RATE, sz1 );	// initial learn rate
		sprintf(sz2, "%f", m_momentumDistance);
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_MOMENTUM, sz2 );	// momentum

		sprintf(sz1, "%f", m_learnRateConscience);
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_LEARN_RATE, sz1 );	// initial learn rate
		sprintf(sz2, "%f", m_momentumConscience);
		SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_MOMENTUM, sz2 );	// momentum

		delete [] sz1;
		delete [] sz2;
	}
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

	sprintf(sz1, "%f", m_net_learnRate);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_LEARN_RATE, sz1 );	// initial learn rate
	sprintf(sz2, "%f", m_net_momentum);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_MOMENTUM, sz2 );	// momentum

	sprintf(sz1, "%f", m_net_learnRateDistance);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_LEARN_RATE, sz1 );	// initial learn rate
	sprintf(sz2, "%f", m_net_momentumDistance);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_MOMENTUM, sz2 );	// momentum

	sprintf(sz1, "%f", m_net_learnRateConscience);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_LEARN_RATE, sz1 );	// initial learn rate
	sprintf(sz2, "%f", m_net_momentumConscience);
	SetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_MOMENTUM, sz2 );	// momentum


	if (hSurfWnd)
	{
		SendMessage(hSurfWnd, WM_USER+2, (WPARAM)m_examples, (LPARAM) m_winners);
	}
	else
	{
		if (KohonenDlg::s_toCreateSurfWindowOnThread && KohonenDlg::s_WinnersGot)
		{
			DWORD	id;
			CreateThread(NULL, 1024, (LPTHREAD_START_ROUTINE)  ShowSpheres,
				(void *) this, 0, &id);
			KohonenDlg::s_toCreateSurfWindowOnThread	= false;
			KohonenDlg::s_WinnersGot					= false;
		}

	}

	delete [] sz1;
	delete [] sz2;
}



// ------------------------------------------------------------
// on button "Create" map
//
void KohonenDlg::OnButtonCreateMap() 
{
	m_mapWnd.CreateNewMap(m_examples);
	/*
	char		str[255];
	int			i;

	// cities edit box`s text
	//m_citiesEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_N_INPUT_VECTORS, str,sizeof(str));

	// convert it to int
	i = _ttoi(str);
	if ((i <= 3) || (i > 20))
	{
		MessageBox(hDlg, _T("Cities count must be more than 3."), STR_ERROR, MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		//(m_examples = i)
		// create new map
		
//		ShowCitiesCount();
	}*/
}



// ------------------------------------------------------------
// on button "Save" map
//
void KohonenDlg::OnButtonSaveMap() 
{
/*	CFileDialog		fd(FALSE, NULL, _T("map.tsp"), OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT, _T("Traveling Salesman Map (*.tsp)|*.tsp||"), this);

	// check cities count
	if (m_examples == 0)
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

		m_examples = m_mapWnd.GetPointsCount();
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
	m_dx = _ttoi(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_NEURONS_DY, str, sizeof(str));
	m_dy = _ttoi(str);
	m_neurons = m_dx * m_dy;

	// Conscience learn rate
	//	m_learnRateEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_LEARN_RATE, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_learnRateConscience) != 1)
	{
		MessageBox(hDlg, _T("Invalid initial learn rate"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}
	// Distance learn rate
	//	m_learnRateEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_LEARN_RATE, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_learnRateDistance) != 1)
	{
		MessageBox(hDlg, _T("Invalid initial learn rate"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}
	// learn rate
	//	m_learnRateEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_LEARN_RATE, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_learnRate) != 1)
	{
		MessageBox(hDlg, _T("Invalid initial learn rate"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}

	// Conscience momentum
	//	m_momentumEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_CONSCIENCE_MOMENTUM, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_momentumConscience) != 1)
	{
		MessageBox(hDlg, _T("Invalid momentum"), STR_ERROR, MB_OK | MB_ICONHAND);
		return;
	}
	// Distance momentum
	//	m_momentumEdit.GetWindowText(str);
	GetDlgItemText(hDlg, IDC_EDIT_KOHONEN_DISTANCE_MOMENTUM, str, sizeof(str));
	if (_stscanf(str, _T("%f"), &m_momentumDistance) != 1)
	{
		MessageBox(hDlg, _T("Invalid momentum"), STR_ERROR, MB_OK | MB_ICONHAND);
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


//	m_mapWnd.SetPoints(m_xPoints, m_yPoints);
	m_mapWnd.SetPoints(m_Points[m_j0], m_Points[m_j1]);


	
	m_type = SendDlgItemMessage( hDlg, IDC_COMBO_KOHONEN_TYPE, CB_GETCURSEL,0,(LPARAM)0 );

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
		WaitForSingleObject(m_thread, 2000);
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
	int j;
//	CNetKohonen		net;
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;

//	double*			xPoints		= me->m_xPoints;
//	double*			yPoints		= me->m_yPoints;

	double**		Points		= me->m_Points;

	int				cities		= me->m_examples;
	int				neurons		= me->m_neurons;

	float			learnRate	= me->m_learnRate;
	float			momentum	= me->m_momentum;

	float			learnRateDistance	= me->m_learnRateDistance;
	float			momentumDistance	= me->m_momentumDistance;

	float			learnRateConscience	= me->m_learnRateConscience;
	float			momentumConscience	= me->m_momentumConscience;

	int				nParameters = me->m_nParameters;

//	float			in[2];
	float*			in = new float [nParameters];
	int				i;
	long			delay		= me->m_delay;
	long			iteration	= 0;

	float			noise		= 0.05f;

//	double*			xWay = new double[neurons];
//	double*			yWay = new double[neurons];

	double **		Way = AllocDoubleMat(nParameters, neurons);

	double			
					//prevx, prevy, 
					pathj,path; 
					//x, y, 
					//dx, dy;
	double			*prevv		= new double [nParameters],
					*v			= new double [nParameters],
					*dv			= new double [nParameters];



	TCHAR*			sz = new TCHAR[32];

	CNeuron::SetAlfa(0.001f);

	// create net & randomize it
	me->m_net.InitEx(nParameters, neurons);
//	me->m_net.Randomize(150, 0);

//	if (! me->m_bInited)
	{
		//me->m_net.MidInit(me->m_minOfPoints, me->m_maxOfPoints);
		me->m_net.RandInit(me->m_minOfPoints, me->m_maxOfPoints);
		float bias = exp(1.0 - log(1.0 / neurons));
		me->m_net.BiasInit(bias);
		me->m_bInited = true;
	}

	layer = me->m_net.GetLayer(0);

	layer->SetDimension(me->m_dx, me->m_dy);
	vector<int> input_order;
	vector<int>::iterator Itr;



	while (!me->m_stop)
	{
		me->m_type = SendDlgItemMessage( me->hDlg, IDC_COMBO_KOHONEN_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
		bool add_noise = IsDlgButtonChecked( me->hDlg, IDC_CHECK_KOHONEN_ADD_SMALL_NOISE) 
				== BST_CHECKED;
		// get last neuron
		neuron	= layer->GetNeuron(neurons - 1);
		path	= 0;
		//prevx	= neuron->GetSynapse(0);
		//prevy	= neuron->GetSynapse(1);
		for (j = 0; j < nParameters; j++)
		{
			prevv[j] = neuron->GetSynapse(j);
		}

		// get way
		for (i = 0; i < neurons; i++)
		{
			// get neuron
			neuron = layer->GetNeuron(i);

			// get it`s weights
			//xWay[i] = (float) (x = neuron->GetSynapse(0));
			//yWay[i] = (float) (y = neuron->GetSynapse(1));

			//dx		= prevx - x;
			//dy		= prevy - y;
			//prevx	= x;
			//prevy	= y;
			pathj = 0.0;
			for (j = 0; j < nParameters; j++)
			{
				Way[j][i] = (float) (v[j] = neuron->GetSynapse(j));
				dv[j]	  = prevv[j] - v[j];
				prevv[j]  = v[j];
				pathj	 += dv[j]*dv[j];
			}

			//path += (float) sqrt(dx * dx + dy * dy);
			path += sqrt(pathj);
		}
		// show current way
		//me->m_mapWnd.SetWay(xWay, yWay, neurons);
		me->m_mapWnd.SetWay(Way[me->m_j0], Way[me->m_j1], neurons, me->m_dx, me->m_dy);


		me->m_iteration	= iteration;
		me->m_minTour	= path;

//		me->PostMessage(WM_SET_INFO);

		// set learn rate
		me->m_net.SetLearnRate(learnRate);
		me->m_net.SetLearnRateDistance(learnRateDistance);
		me->m_net.SetLearnRateConscience(learnRateConscience);
		if (me->m_type < 3)
		{
			// get random city
			randpermute(cities, input_order);
			for ( Itr = input_order.begin(); Itr != input_order.end(); Itr++)
			{
				//in[0] = xPoints[i];
				//in[1] = yPoints[i];

				// add small noise
		//		in[0] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);
		//		in[1] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);

				for ( j = 0; j < nParameters; j++)
				{
					in[j] = Points[j][*Itr];
					if (add_noise)
						in[j] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);
				}

				// set net inputs
				me->m_net.SetInputs(in);
				me->m_net.Propagate();
				switch (me->m_type)
				{
				case 0:
					{
						me->m_net.LearnGaussian();
					}
					break;
				case 1:
					{
						me->m_net.LearnConscience();
					}
					break;
				case 2:
					{
						me->m_net.LearnGaussianConscience();
					}
					break;
				}
			}
		}
		else
		{
			switch (me->m_type)
			{
			case 3:
				{
					me->m_net.LearningGaussian(nParameters, cities, Points, add_noise);
				}
				break;
			case 4:
				{
					me->m_net.LearningConscience(nParameters, cities, Points, add_noise);
				}
				break;
			case 5:
				{
					//me->m_net.LearningGaussianConscience(nParameters, cities, Points, add_noise);
				}
				break;
			}
		}
		// modify learn rate
		learnRate *= momentum;
		learnRateDistance *= momentumDistance;
		learnRateConscience *= momentumConscience;

		iteration++;

//		if (iteration % 100 == 0)
//			DistanceMomentum -= 0.001f;

//		if (iteration % 100 == 0)
//			momentum -= 0.001f;

		me->m_net_momentum = momentum;
		me->m_net_learnRate = learnRate;

		me->m_net_momentumDistance = momentumDistance;
		me->m_net_learnRateDistance = learnRateDistance;

		me->m_net_momentumConscience = momentumConscience;
		me->m_net_learnRateConscience = learnRateConscience;

		if ( me->hSurfWnd || KohonenDlg::s_toCreateSurfWindowOnThread)
		{
			GetWinners(me,in);
			KohonenDlg::s_WinnersGot = true;
		}

		SendMessage(me->hDlg, WM_SET_INFO, 0, 0);

		Sleep(delay);
	}
	GetWinners(me, in);
	FreeDoubleMat(Way);

	delete [] in;
	delete [] prevv;
	delete [] v;
	delete [] dv;

	delete [] sz;

	me->InitParams(false);

	return 0;
}

DWORD KohonenDlg::GetWinners(KohonenDlg * me, float * in)
{
	for (int i = 0; i < me->m_examples; i++)
	{
		//in[0] = xPoints[i];
		//in[1] = yPoints[i];
		for (int j = 0; j < me->m_nParameters; j++)
		{
			in[j] = me->m_Points[j][i];
		}
		// set net inputs
		me->m_net.SetInputs(in);
		me->m_net.Propagate();
		switch (me->m_type)
		{
		case 3:
		case 0:
			{
				me->m_winners[i] = me->m_net.GetGaussianWinner();
			}
			break;
		case 4:
		case 1:
			{
				me->m_winners[i] = me->m_net.GetConscienceWinner();
			}
			break;
		case 5:
		case 2:
			{
				me->m_winners[i] = me->m_net.GetGaussianConscienceWinner();
			}
		}
	}
	return 0;
}
extern char directory[];
extern HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex);

void KohonenDlg::ResultsSaveAs()
{
	TCHAR lpstrFile[1024];
	TCHAR filter[] =     
                         TEXT("Golden Software Data (*.dat)\0*.dat\0")
                         TEXT("Golden Software Data Files (*.dat)\0*.dat\0")
                         //TEXT("All Files (*.*)\0*.*\0")
						 ;

	if (m_dy != 1)
		sprintf(lpstrFile, "%s\\klasters_%s_%d_%d", directory, m_name.c_str(), m_dx, m_dy);
	else
		sprintf(lpstrFile, "%s\\klasters_%s_%d", directory, m_name.c_str(), m_neurons);

	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return;
	switch (nFilterIndex)
	{
	case 1:
		{
            FILE *dat;
			CLayerKohonen*	layer;
//			CNeuronKohonen*	neuron;
			dat = fopen(lpstrFile,"wt");
			//  3d линии
			fprintf(dat, "X,Y,Z,i_winner");
			/*for(int j = 0; j < m_nParameters; j++)
			{
			fprintf(dat, ",Synapse%d",j);            
			}*/
			fprintf(dat, "\n");	
			layer = m_net.GetLayer(0);
			for (int i = 0; i < m_examples; i++)
			{
				fprintf(dat, "%f,%f,%f,", m_X[i], m_Y[i], m_Z[i]);
				fprintf(dat, "%d",  m_winners[i]);
				/*neuron = layer->GetNeuron(m_winners[i]);
		for(int j = 0; j < m_nParameters; j++)
		{
			fprintf(dat, ",%f", ZoomParameterOut(neuron->GetSynapse(j),j));		
		}*/
				fprintf(dat, "\n");		
			}
			fclose(dat);
		}
		break;
	case 2:
		{
			CLayerKohonen*	layer;
			layer = m_net.GetLayer(0);
			ulong rang = layer->GetRang();

			FILE ** dats = new FILE*[rang];

			for (ulong r = 0; r < rang; r++)
			{
				char filename[1024];
				strcpy(filename, lpstrFile);
				char * p = strrchr(filename,'.');
				if (p)
					sprintf(p, "_klast_%03u.dat", r);
				else
				{
					char end[256];
					sprintf(end, "_klast_%03u.dat", r);
					strcat(filename, end);
				}
				dats[r] = fopen(filename,"wt");
			}		
			for (int i = 0; i < m_examples; i++)
			{
				if (m_winners[i] > 0 && m_winners[i] < (int)rang)
				{
					fprintf(dats[m_winners[i]], "%f,%f,%f,", m_X[i], m_Y[i], m_Z[i]);
					fprintf(dats[m_winners[i]], "%d",  m_winners[i]);
					fprintf(dats[m_winners[i]], "\n");	
				}					
			}	
			for (ulong r = 0; r < rang; r++)
			{
				fclose(dats[r]);
			}	
			delete [] dats;
		}
		break;
	}
}

void KohonenDlg::ClassesSaveAs()
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     
                         TEXT("Golden Software Data (*.dat)\0*.dat\0")
                         TEXT("All Files (*.*)\0*.*\0");

	if (m_dy != 1)
		sprintf(lpstrFile, "%s\\classes_%s_%d_%d", directory, m_name.c_str(), m_dx, m_dy);
	else
		sprintf(lpstrFile, "%s\\classes_%s_%d", directory, m_name.c_str(), m_neurons);

	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return;
	FILE *dat;
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	dat = fopen(lpstrFile,"wt");
	//  3d линии
	fprintf(dat, "ti_winner");
	for(int j = 0; j < m_nParameters; j++)
	{
		fprintf(dat, ",Synapse%d",j);		
	}
	fprintf(dat, "\n");	
	
	layer = m_net.GetLayer(0);
	
	for (int i = 0; i < layer->GetRang(); i++)
	{
		fprintf(dat, "%d",  i);
		neuron = layer->GetNeuron(i);
		for(int j = 0; j < m_nParameters; j++)
		{
			fprintf(dat, ",%f", ZoomParameterOut(neuron->GetSynapse(j),j));		
		}
		fprintf(dat, "\n");		
	}
	fclose(dat);
}

/*void KohonenDlg::PointsSaveAs()
{
	TCHAR lpstrFile[256];
	TCHAR filter[] =     
                         TEXT("Golden Software Data (*.dat)\0*.dat\0")
                         TEXT("All Files (*.*)\0*.*\0");

	if (m_dy != 1)
		sprintf(lpstrFile, "%s\\points_%s_%d_%d", directory, m_name.c_str(), m_dx, m_dy);
	else
		sprintf(lpstrFile, "%s\\points_%s_%d", directory, m_name.c_str(), m_neurons);

	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return;
	FILE *dat;
	dat = fopen(lpstrFile,"wt");
	//  3d линии
//	for(int j = 0; j < m_nParameters; j++)
//	{
//		if (j != 0) fprintf(dat, "\t");
//		fprintf(dat, "Param%d",j);		
//	}
//	fprintf(dat, "\n");	
//	
	for ( int i = 0; i < m_examples; i++)
	{
		for (int j = 0; j < m_nParameters; j++)
		{
			if (j != 0) fprintf(dat, ",");
			fprintf(dat, "%f", m_Points[j][i]);
		}
		fprintf(dat, "\n");		
	}	
	fclose(dat);
}*/
extern int SaveAsSurferGrid7(HWND hWnd, LPCTSTR lpstrFile, vdouble& xi, vdouble& yi, vdouble& zi, vdouble& visible);
DWORD KohonenDlg::SurfResults(KohonenDlg* me)
{
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	vdouble xi,yi,zi;
	vector<double> x,y,z;
	double xmin = DBL_MAX, ymin = DBL_MAX, zmin = DBL_MAX;
	double xmax = -DBL_MAX, ymax = -DBL_MAX, zmax = -DBL_MAX;
	//@@@@@@@@@@@@@@@@@
	x.resize(me->m_examples);
	y.resize(me->m_examples);
	z.resize(me->m_examples);
	//@@@@@@@@@@@@@@@@@
	vdouble visible;
	//@@@@@@@@@@@@@@@@@
	//  3d линии
	layer = me->m_net.GetLayer(0);
	for (int i = 0; i < me->m_examples; i++)
	{
		x[i] = me->m_X[i], y[i] = me->m_Y[i];
		z[i] = me->m_winners[i];

		if (xmin > x[i]) xmin = x[i];
		if (xmax < x[i]) xmax = x[i];

		if (ymin > y[i]) ymin = y[i];
		if (ymax < y[i]) ymax = y[i];

		if (zmin > z[i]) zmin = z[i];
		if (zmax < z[i]) zmax = z[i];

		neuron = layer->GetNeuron(me->m_winners[i]);
		for(int j = 0; j < me->m_nParameters; j++)
		{
			me->ZoomParameterOut(neuron->GetSynapse(j),j);		
		}
	}
	int type = SendDlgItemMessage( me->hDlg, IDC_COMBO_KOHONEN_SURF_RESULT_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
	if(type == 0)
	{

		//xi = dsequence(double(x.Min()), long(110), double(x.Max()));
		//yi = dsequence(double(y.Min()), long(100), double(y.Max()));
		xi = dsequence(double(xmin), double(200), double(xmax));
		yi = dsequence(double(ymin), double(200), double(ymax));
		zi.resize(xi.Length(), yi.Length(), 0.0 );
		//visible.resize(xi.Length(), yi.Length(), 1.0 );
		if (griddata(me->hDlg, x, y, z, NULL, &xi, &yi, &zi) != 0)
		{
			return -1;
		}

		if (MessageBox(0, "Do you want to save v4 grid?", "Surf", 
			MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			TCHAR lpstrFile[256];
			sprintf(lpstrFile, "%s\\v4.grd", directory);
			SaveAsSurferGrid7(me->hDlg, lpstrFile, xi, yi, zi, visible);
		}

	/*	if (MessageBox(0, "Do you want to izo dat file points in spheres?", "Surf", 
			MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			COLORREF color = 0;
			ChooseSurfColor(hWnd, color);
			pSurfDoc->AddSpheres(x,y,z,color);
		}*/

		//pSurfDoc->AddLine(x,y,z);
	/*	if (MessageBox(0, "Do you want to izo grid?", "Surf", 
			MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
		{
			COLORREF color = 0;
			ChooseSurfColor(hWnd, color);
			pSurfDoc->AddSurf(zflag,xi,yi,zi, visible, color);
		}*/

		WinSurf(xi,yi,zi);
	}
	else
	{
		 WinSurf(me->hSurfWnd, x,y,z,1);
	}
	return 0;
}

DWORD KohonenDlg::ShowSpheres(KohonenDlg* me)
{
#if 0
	CLayerKohonen*	layer;
	vdouble xi,yi,zi;
	vdouble x,y,z;
	//@@@@@@@@@@@@@@@@@
	x.resize(me->m_examples);
	y.resize(me->m_examples);
	z.resize(me->m_examples);
	//@@@@@@@@@@@@@@@@@
	vdouble visible;
	//@@@@@@@@@@@@@@@@@
	layer = me->m_net.GetLayer(0);
	for (int i = 0; i < me->m_examples; i++)
	{
		x[i] = me->m_X[i], y[i] = me->m_Y[i];
		z[i] = me->m_winners[i];
	}
	WinSurf(me->hSurfWnd, x,y,z,1);
	return 0;
#else
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);


	
	CLayerKohonen*	layer;
	layer = me->m_net.GetLayer(0);
	ulong rang = layer->GetRang();

	Collection ** collections = new Collection*[rang];

	for (ulong r = 0; r < rang; r++)
	{
		collections[r] = app->GetWinProject()->CreateNewCollection();
		char name[256];
		sprintf(name, "%u", r);
		collections[r]->SetName(name);
	}

	int palette_len = app->GetWinProject()->m_palette.GetLen();
	for (int i = 0; i < me->m_examples; i++)
	{

		Sphere3D sphere;		
		sphere.Init((SurfDoc*)app->GetWinProject(), CPoint3(me->m_X[i], me->m_Y[i], me->m_Z[i]));
		
		double palette_part = double(me->m_winners[i]) / double(palette_len);
		COLORREF color = app->GetWinProject()->m_palette.GetColor(palette_part);
		sphere.SetColor(color);
		
		if (me->m_winners[i] > 0 && me->m_winners[i] < (int)rang)
		{
			collections[me->m_winners[i]]->AddObject(&sphere);
		}					
	}

	delete [] collections;

	app->GetWinProject()->ZoomView();

	return StartWinSurfLoop();
#endif
}
