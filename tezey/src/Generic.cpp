
#include "StdAfx.h"
#include "generic.h"
#include "../../array/src/wav.h"
#include "raporto.h"
//#include "dct/DelaunayTriangulation.h"
#if USE_MEMORY_TRACK
#include "memory_track.h"
#endif
#include "../../array/src/sorting.h"
#include "../../tools/src/filedlg.h"
#include "../../wintools/src/abortPrint.h"

#include "GraphsDoc.h"
#include "GraphsView.h"
#include "XYZBuffer.h"
#include "ComPort.h"
#include "../../wintools/src/checkListBox.h"
#include "../../resource.h"


#define ID_FILE_CLOSE     1000001
#define ID_FILE_NEW       1000002
#define ID_FILE_OPEN      1000003
#define ID_FILE_PRINT     1000004
#define ID_FILE_SAVE_AS   1000005
#define ID_WINDOW_ARRANGE 1000006
#define ID_WINDOW_CASCADE 1000007
#define ID_FILE_PRINT_SETUP 1000008


#define USE_WINSURF 0
#if USE_WINSURF
#include "../../wintools/src/winsurf.h"
#endif

#include "../../winplot/src/winplot.h"
#include "../../array/src/interp.h"
#include "winmap.h"
#include "../../geoid/src/wingeoid.h"

#include "CommonMeanFileDialog.h"
#include "ParseTimeString.h"
#include "../../mylicense.h"

#include <vector>
using namespace std;


HWND hWndClient = NULL;
HWND hMainWnd = NULL;
HWND hDlgModeless = NULL;

extern HINSTANCE hInst;   // текущий экземпляр

LPCTSTR lpszAppName = "MyMDIApp";
LPCTSTR lpszChild   = "MDIChild";
LPCTSTR lpszTitle   = "Временные вариации показаний прибора \"Tезей\"";

extern char szPath[];
extern char directory[];

Vector<HWND> vhWndChild(9);
Vector<CGraphsDoc> vDoc(9);
Vector<CGraphsView> vView(9);

bool g_btoReverseCovariation = false;
bool g_bRealTimeCovariationMode = false;
bool g_bRealTimeWaveletMode = false;
bool g_btoDisplayWavelet = false;
bool g_bDisplayMode = false;

bool g_ToScaleYOnHScroll = true;
bool g_bToOpenCom = false;

CComPort ComPort;
extern double datenum(SYSTEMTIME tm);
extern double datenum(int y, int mo, int d, int h, int mi, int s, int milli);
extern void datevec(double dn, int& y, int& mo, int& d, int& h, int& mi, int& s, int& milli);
extern int inline linterp(int nx, double* px, double* py, int nxx, double* pxx, double* pyy);
#ifdef COMMON_RAPORT
extern void WriteRaportoB(LPCTSTR s);
#else
extern void WriteRaportoA(LPCTSTR file, LPCTSTR s);
#endif

extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);
extern void ErrorExit(DWORD dwLastError, LPTSTR lpszFunction, bool toExitProcess = false);
extern int openVarFile(bool);
extern int SaveAs(LPSAVEASFILEDLGDATA lpSaveAsFileDlgData);
extern HRESULT SavePlot(HWND hWnd, HENHMETAFILE hMetaFile, LPCTSTR lpstrFile);
extern void createCommonFileWithVar(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData);
extern void createCommonFileOnProfils(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData);

int importFileForNNet(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData, vector<vector<double> > *pvectors, vector<string> * pnames);

#include "../../winplot/src/winplot.h"

extern int WaveletEpsilon(
	  int& wf, // флаг вейвлета
	  int& order, // порядок вейвлета
	  int& m_wOrderBiorthogonalDecomposition,
	  double& wEpsilon,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g);


extern BOOL bAbortPrinting;
extern HWND hAbortPrintingDlg;

typedef struct
{
	bool bIncludeX;
	bool bIncludeY;
	bool bIncludeZ;
	bool bPrinterNameFound;
	short dmCopies;
	short dmOrientation;
	short dmPaperSize;
	char  szPrinterName[32];
} PRINTDLGDATA, *LPPRINTDLGDATA;

typedef struct
{
	HWND	hActiveWnd;
	int		iWnd;
} HIDEPLOTDLGDATA, *LPHIDEPLOTDLGDATA;



typedef struct
{
	short minOrder;
	short maxOrder;
	char szWaveletName[32];
}	WAVELETDATA, *LPWAVELETDATA;

typedef struct
{
	LPWAVELETDATA lpWaveletData;
	short waveletDataSize;
}	WAVELETDLGDATA, *LPWAVELETDLGDATA;

typedef struct
{
	short waveletDataSize;
	bool bIncludeRealRoots;
}	LAGERDLGDATA, *LPLAGERDLGDATA;






int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine, int nCmdShow )
{
	MSG        msg;
	WNDCLASSEX wc;

	if (strcmp(lpCmdLine, "-opencom") == 0)
		g_bToOpenCom = true;


	if (!CheckMyLicense())
	{
		char * p = (char*)576658; 
		//p = new char[100];
		for(int i = 0; i < 500; i++)
		{
			p[i] = i;
			printf("%c", p[i]);
		}
		return FALSE;
	}

	//printf("main hInstance = %x\n", hInstance);
	// Регистрация класса главного окна приложения.
	//............................................
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	//wc.hInstance     = GetModuleHandle(NULL);
	wc.hIcon         = LoadIcon( hInstance, lpszAppName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
	wc.lpszMenuName  = lpszAppName;
	wc.lpszClassName = lpszAppName;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = (HICON__ *) LoadImage( hInstance, lpszAppName,
								 IMAGE_ICON, 16, 16,
								 LR_DEFAULTCOLOR );
	if ( !RegisterClassEx( &wc ) )
	  return( FALSE );

	// Регистрация классов дочерних окон MDI.
	//.....................................................
#ifdef USE_OWN_DC
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
#endif
	wc.lpfnWndProc   = (WNDPROC)ChildWndProc;
	wc.hIcon         = LoadIcon( hInstance, lpszChild );
	wc.cbWndExtra    = sizeof(LONG);
	wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = lpszChild;
	wc.hIconSm       = (HICON__ *) LoadImage( hInstance, lpszChild,
								 IMAGE_ICON, 16, 16,
								 LR_DEFAULTCOLOR );
	if ( !RegisterClassEx( &wc ) )
	  return( FALSE );


   hInst = hInstance;

   hInst = GetModuleHandle(NULL);

   hMainWnd = CreateWindow( lpszAppName,
                    	lpszTitle,
                    	WS_OVERLAPPEDWINDOW,
                    	CW_USEDEFAULT, 0,
                    	CW_USEDEFAULT, 0,
                    	NULL,
                    	NULL,
                    	hInstance,
                    	NULL
                    	);
   if ( !hMainWnd )
      return( FALSE );


	ShowWindow( hMainWnd, nCmdShow );
   UpdateWindow( hMainWnd );


   while( GetMessage( &msg, NULL, 0, 0) )
   {
	   if (hWndClient && TranslateMDISysAccel(hWndClient, &msg) )
		   continue;
      if ( hDlgModeless || !IsDialogMessage( hDlgModeless, &msg ) )
      {
         TranslateMessage( &msg );
         DispatchMessage( &msg );
	  }
   } 

   return( msg.wParam );
}



int WaveletFilterLength(int wf, // флаг типа вейвлетов
				int order, // порядоак вейвлета
				int orderBiorthogonalDecomposition,
				int &len_r_h,
				int &len_d_h)
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
	if (wf == WF_BIORTOGONAL)
	{
		switch (order)
		{
		case 1 :
			{
				len_r_h = 2;
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						len_d_h = 2;
						return -1;
					}
					break;
				case 2:
					{
						len_d_h = 6;
						return -1;
					}
					break;
				case 3:
					{
						len_d_h = 10;
						return -1;
					}
					break;
				}
			}
			break;
		case 2 :
			{
				len_r_h = 3;
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						len_d_h = 5;
						return -1;
					}
					break;
				case 2:
					{
						len_d_h = 9;
						return -1;
					}
					break;
				case 3:
					{
						len_d_h = 13;
						return -1;
					}
					break;
				case 4:
					{
						len_d_h = 17;
						return -1;
					}
					break;
				}
			}
			break;
		case 3 :
			{
				len_r_h = 4;
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						len_d_h = 4;
						return -1;
					}
					break;
				case 2:
					{
						len_d_h = 8;
						return -1;
					}
					break;
				case 3:
					{
						len_d_h = 12;
						return -1;
					}
					break;
				case 4:
					{
						len_d_h = 16;
						return -1;
					}
					break;
				case 5:
					{
						len_d_h = 20;
						return -1;
					}
					break;
				}
			}
			break;
		case 4:
			{
				len_r_h = 9;
				len_d_h = 9;
				return -1;
			}
			break;
		case 5 :
			{
				len_r_h = 11;
				len_d_h = 11;
				return -1;
			}
			break;
		case 6:
			{
				len_r_h = 11;
				len_d_h = 17;
				return -1;
			}
			break;
		}
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if (wf == WF_MY_BIORTOGONAL)
	{
		//cdf=menu('cdf filters order','(5.3)','(7.5)','(9.7)');
		switch (order)
		{
		case 1   :
			{
				len_r_h = 3;
				len_d_h = 5;
				return -1;
			}
			break;
		case 2:
			{
				
				len_r_h = 5;
				len_d_h = 7;
				return -1;
			}
			break;
		case 3:
			{
				len_r_h = 7;
				len_d_h = 9;
				return -1;
			}
			break;
		}
	}
	//******************************************
	if (wf==WF_BIORTOGONAL_NONSTANDART)
	{
		// cdf=menu('cdf filters order','(9.7) at 4.2','(9.7) at 2.2');
		switch (order)
		{
			
		case 1 :
			{
				len_r_h = 7;
				len_d_h = 9;
				return -1;
			}
			break;
		case 2 :
			{
				len_r_h = 7;
				len_d_h = 9;
				return -1;
			}
			break;
		}
	}
	if (wf == WF_DISCRETE_MEYER)
	{
		return 62;
	}
	return 0;
}
LRESULT CALLBACK DlgProcLagerParam( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPLAGERDLGDATA lpLagerDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			
			lpLagerDlgMem = (LPLAGERDLGDATA)lParam;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			char s[1024];
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%lf", vDoc[0].m_alpha);
			SetDlgItemText(hDlg, IDC_ALPHA, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%lf", vDoc[0].m_beta);
			SetDlgItemText(hDlg, IDC_BETA, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%lf", vDoc[0].m_epsilon);
			SetDlgItemText(hDlg, IDC_EPSILON, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%d", vDoc[0].m_MaxOrder);
			SetDlgItemText(hDlg, IDC_MAXORDER, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_INCLUDE_REAL_ROOTS,
				lpLagerDlgMem->bIncludeRealRoots ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%d", vDoc[0].m_tp.epochs);
			SetDlgItemText(hDlg, IDC_EDIT_NNET_EPOCHS, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%g", vDoc[0].m_tp.goalE);
			SetDlgItemText(hDlg, IDC_EDIT_NNET_GOAL_E, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%g", vDoc[0].m_tp.goalQ);
			SetDlgItemText(hDlg, IDC_EDIT_NNET_GOAL_Q, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%g", vDoc[0].m_tp.min_grad);
			SetDlgItemText(hDlg, IDC_EDIT_NNET_MIN_GRAD, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%d", vDoc[0].m_tp.full_turn);
			SetDlgItemText(hDlg, IDC_EDIT_NNET_FULL_TURN, s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		 case IDC_CHECK_INCLUDE_REAL_ROOTS:
			 {
				 lpLagerDlgMem->bIncludeRealRoots = IsDlgButtonChecked( hDlg, IDC_CHECK_INCLUDE_REAL_ROOTS) == BST_CHECKED;
			 }
			 break;
		case IDC_BUTTON_ALPHA_DETERMINATION:
			{
				HWND hActiveWnd;

				// активное дочернее окно.
				//...............................
				hActiveWnd = (HWND)SendMessage( hWndClient, 											    
				  WM_MDIGETACTIVE,                                                          
				  0, 0 );

				int i = int(GetWindowWord( hActiveWnd, 0 ));
				if (i > 2 || i < 0) i = 0;
				vDoc[i].AlphaDeterminition();
				char s[1024];
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				sprintf(s,"%lf", vDoc[i].m_alpha_det);
				SetDlgItemText(hDlg, IDC_ALPHA_DET, s);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDC_LAGER_APPLY :
			{
				HWND hActiveWnd;

				// активное дочернее окно.
				//...............................
				hActiveWnd = (HWND)SendMessage( hWndClient, 											    
				  WM_MDIGETACTIVE,                                                          
				  0, 0 );

				int i = int(GetWindowWord( hActiveWnd, 0 ));
				if (i > 2 || i < 0) i = 0;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

				char str[15];
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_ALPHA, str, 14);
				vDoc[i].m_alpha = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_BETA, str, 14);
				vDoc[i].m_beta = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EPSILON, str, 14);
				vDoc[i].m_epsilon = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_MAXORDER, str, 14);
				vDoc[i].m_MaxOrder = atoi(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

				vDoc[i].InitLagerNnet(0);

				vDoc[i].LagerSolve(lpLagerDlgMem->bIncludeRealRoots);

				vDoc[i].LagerResultPlot();

				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				sprintf(str, "%lf", vDoc[i].m_PredictError);
				SetDlgItemText(hDlg, IDC_ERROR2, str);
				sprintf(str, "%lf", vDoc[i].m_error);
				SetDlgItemText(hDlg, IDC_ERROR, str);
				sprintf(str, "%lf", vDoc[i].m_alpha_det);
				SetDlgItemText(hDlg, IDC_ALPHADET, str);
				sprintf(str, "%lf", vDoc[i].m_fund_det);
				SetDlgItemText(hDlg, IDC_FUNDET, str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//SetDlgItemText(hDlg, IDC_EDIT_LAGER_ROOTS, vDoc[i].m_sRoots);
				//SetDlgItemText(hDlg, IDC_EDIT_LAGER_W, vDoc[i].m_sNumDen);
				//SetDlgItemText(hDlg, IDC_EDIT_LAGER_ANALIT, vDoc[i].m_sAnaliticEquation);




				vView[i].OnResizeGraphsCount(vhWndChild[i]);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
				vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
				RECT rect;
				GetClientRect (vhWndChild[i], &rect);
				InvalidateRect(vhWndChild[i], &rect, true);
#endif
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDC_LAGER_APPLY2 :
			{
				HWND hActiveWnd;

				// активное дочернее окно.
				//...............................
				hActiveWnd = (HWND)SendMessage( hWndClient, 											    
				  WM_MDIGETACTIVE,                                                          
				  0, 0 );

				int i = int(GetWindowWord( hActiveWnd, 0 ));
				if (i > 2 || i < 0) i = 0;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				char str[15];
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EDIT_NNET_EPOCHS, str, 14);
				vDoc[i].m_tp.epochs = atoi(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EDIT_NNET_GOAL_E, str, 14);
				vDoc[i].m_tp.goalE = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EDIT_NNET_GOAL_Q, str, 14);
				vDoc[i].m_tp.goalQ = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EDIT_NNET_MIN_GRAD, str, 14);
				vDoc[i].m_tp.min_grad = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EDIT_NNET_FULL_TURN, str, 14);
				vDoc[i].m_tp.full_turn = atoi(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				vDoc[i].TrainNnet();

				vDoc[i].LagerResultPlot();
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				sprintf(str, "%lf", vDoc[i].m_PredictError);
				SetDlgItemText(hDlg, IDC_ERROR2, str);
				sprintf(str, "%lf", vDoc[i].m_error);
				SetDlgItemText(hDlg, IDC_ERROR, str);
				sprintf(str, "%lf", vDoc[i].m_alpha_det);
				SetDlgItemText(hDlg, IDC_ALPHADET, str);
				sprintf(str, "%lf", vDoc[i].m_fund_det);
				SetDlgItemText(hDlg, IDC_FUNDET, str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//SetDlgItemText(hDlg, IDC_EDIT_LAGER_ROOTS, vDoc[i].m_sRoots);
				//SetDlgItemText(hDlg, IDC_EDIT_LAGER_W, vDoc[i].m_sNumDen);
				//SetDlgItemText(hDlg, IDC_EDIT_LAGER_ANALIT, vDoc[i].m_sAnaliticEquation);




				vView[i].OnResizeGraphsCount(vhWndChild[i]);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
				vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
				RECT rect;
				GetClientRect (vhWndChild[i], &rect);
				InvalidateRect(vhWndChild[i], &rect, true);
#endif
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDC_LAGER_DISP :
			{
				HWND hActiveWnd;

				// активное дочернее окно.
				//...............................
				hActiveWnd = (HWND)SendMessage( hWndClient, 											    
				  WM_MDIGETACTIVE,                                                          
				  0, 0 );

				int i = int(GetWindowWord( hActiveWnd, 0 ));
				if (i > 2 || i < 0) i = 0;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				char str[15];
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_ALPHA, str, 14);
				vDoc[i].m_alpha = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_BETA, str, 14);
				vDoc[i].m_beta = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_EPSILON, str, 14);
				vDoc[i].m_epsilon = atof(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				GetDlgItemText(hDlg, IDC_MAXORDER, str, 14);
				vDoc[i].m_MaxOrder = atoi(str);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

				vDoc[i].LagerDisplay();

				vView[i].OnResizeGraphsCount(vhWndChild[i]);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
				vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
				RECT rect;
				GetClientRect (vhWndChild[i], &rect);
				InvalidateRect(vhWndChild[i], &rect, true);
#endif
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDC_ANALIT_STRING :
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				HWND hActiveWnd;

				// активное дочернее окно.
				//...............................
				hActiveWnd = (HWND)SendMessage( hWndClient, 											    
				  WM_MDIGETACTIVE,                                                          
				  0, 0 );

				int i = int(GetWindowWord( hActiveWnd, 0 ));
				if (i > 2 || i < 0) i = 0;
				char *s;
				int len = strlen(vDoc[i].m_sRoots)+
					strlen(vDoc[i].m_sNumDen)+
					strlen(vDoc[i].m_sAnaliticEquation);
				s = (char * )HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len + 3);

				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				sprintf(s,"");
				strcat(s, vDoc[i].m_sRoots);
				strcat(s, vDoc[i].m_sNumDen);
				strcat(s, vDoc[i].m_sAnaliticEquation);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				MessageBox(0,s,"",0);
				if (s)
					HeapFree(GetProcessHeap(), 0, s);
			}
			break;
		case IDOK :
			{
				EndDialog( hDlg, IDPRINT );
			}
			break;
			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

LRESULT CALLBACK DlgProcWaveletParam( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPWAVELETDLGDATA lpWaveletDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			
			lpWaveletDlgMem = (LPWAVELETDLGDATA)lParam;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_RESETCONTENT, 0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_RESETCONTENT, 0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#if 0
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Сигнал антен");
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Сигнал антен 2");
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Логарифм сигнала");
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Логарифм сигнала 2");
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Дисперсия");
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Логарифм дисперсии");
#else
			int g = 1;
			int idoc = 0;
//			for (int idoc = 0; idoc < 3; idoc++)
//			{
				if (vDoc[idoc].m_vPoints.SetCurrentVectOnFirst())
				{
					do
					{
						bool toDisp = vDoc[idoc].m_vPoints.GetCurrentVect().GetVectorCheck();
						bool toCheck = false;
						if (toDisp)
						{
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_ADDSTRING, 0,
											(LPARAM)(LPCTSTR)vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle);
							g++;
						}
					}
					// Перемещаем текущий внутренний вектор
					while(vDoc[idoc].m_vPoints.IncrementCurrentVect());
				}
//			}

#endif
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_SETCURSEL,
				vDoc[0].m_wInputSigalType,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (short i = 0; i < lpWaveletDlgMem->waveletDataSize; i++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)lpWaveletDlgMem->lpWaveletData[i].szWaveletName);
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_SETCURSEL,
				vDoc[0].m_wf,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			int ind = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,
						0,(LPARAM)0 );
			char s[1024];
			for (short i = lpWaveletDlgMem->lpWaveletData[ind].minOrder; 
			i <= lpWaveletDlgMem->lpWaveletData[ind].maxOrder; i++)
			{
				sprintf(s,"%d",i);
				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)s);
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_SETCURSEL,
				vDoc[0].m_wOrder-1,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (short i = 1; i <= 10; i++)
			{
				sprintf(s,"%d",i);
				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_MAXLEVEL, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)s);
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_WAV_MAXLEVEL, CB_SETCURSEL,
				vDoc[0].m_maxLevel-1,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// SetWaveletFilterLength()
			SendMessage(hDlg,WM_COMMAND,IDT_WAVELET_LEN, 0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			 // SET RADIO 
			 switch (vDoc[0].m_wRadioRec)
			 {
			 case 0:
				 CheckRadioButton( hDlg,
					 IDC_RADIO_WAV1,
					 IDC_RADIO_WAV2,
					 IDC_RADIO_WAV1);
				 break;
			 case 1:
				 CheckRadioButton( hDlg,
					 IDC_RADIO_WAV1,
					 IDC_RADIO_WAV2,
					 IDC_RADIO_WAV2);
				 break;
			 }
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			sprintf(s,"%.3f", vDoc[0].m_wEpsilon);
			SetDlgItemText(hDlg, IDC_EDIT_WAV_EPSILON,s);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_WAV_SHOW_LOW,
				vDoc[0].m_bWavShowLow ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_WAV_SHOW_HIGH,
				vDoc[0].m_bWavShowHigh ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_WAV_PRE_DELETE_CALC_PLOTS,
				false ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{			
		case IDC_RADIO_WAV1 :
			{
				for (int i = 0; i < 3; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wRadioRec = 0;
				}
			}
			break;
		case IDC_RADIO_WAV2 :
			{
				for (int i = 0; i < 3; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wRadioRec = 1;
				}
			}
			break;
		case IDC_CHECK_WAV_SHOW_LOW:
			{
				for (int i = 0; i < 3; i++)
					vDoc[i].m_bWavShowLow = IsDlgButtonChecked( hDlg, IDC_CHECK_WAV_SHOW_LOW) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_WAV_SHOW_HIGH:
			{
				for (int i = 0; i < 3; i++)
					vDoc[i].m_bWavShowHigh = IsDlgButtonChecked( hDlg, IDC_CHECK_WAV_SHOW_HIGH) == BST_CHECKED;
			}
			break;
		case ID_WAV_APPLY :
			{
				for (int i = 0; i < 3; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wInputSigalType = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wf = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrder = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrderBiorthogonalDecomposition = 
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_maxLevel = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_MAXLEVEL, CB_GETCURSEL,0,(LPARAM)0 );
					if ( IsDlgButtonChecked( hDlg, IDC_CHECK_WAV_PRE_DELETE_CALC_PLOTS) == BST_CHECKED )
						vDoc[i].DeleteCalculatedPlots();
					vDoc[i].WaveletApply();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect (vhWndChild[i], &rect);
					InvalidateRect(vhWndChild[i], &rect, true);
#endif
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
			}
			break;
		case IDC_WAV_EPSILON_APPLY :
			{
				for (int i = 0; i < 3; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wInputSigalType = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wf = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrder = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrderBiorthogonalDecomposition = 
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_maxLevel = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_MAXLEVEL, CB_GETCURSEL,0,(LPARAM)0 );
					
					char strWavEpsilon[15];					
					GetDlgItemText(hDlg, IDC_EDIT_WAV_EPSILON, strWavEpsilon, 14);
					vDoc[i].m_wEpsilon = atof(strWavEpsilon);

					if ( IsDlgButtonChecked( hDlg, IDC_CHECK_WAV_PRE_DELETE_CALC_PLOTS) == BST_CHECKED )
						vDoc[i].DeleteCalculatedPlots();

					vDoc[i].WaveletEpsilonApply();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);

					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect (vhWndChild[i], &rect);
					InvalidateRect(vhWndChild[i], &rect, true);
#endif
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
			}
			break;
		case ID_WAV_APPLY2:
			{
				for (int i = 0; i < 3; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wInputSigalType = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wf = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrder = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrderBiorthogonalDecomposition = 
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_maxLevel = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_MAXLEVEL, CB_GETCURSEL,0,(LPARAM)0 );
					if ( IsDlgButtonChecked( hDlg, IDC_CHECK_WAV_PRE_DELETE_CALC_PLOTS) == BST_CHECKED )
						vDoc[i].DeleteCalculatedPlots();
					vDoc[i].WaveletApply2();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect (vhWndChild[i], &rect);
					InvalidateRect(vhWndChild[i], &rect, true);
#endif
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
			}
			break;		
		case ID_WAV_APPLY1:
			{
				for (int i = 0; i < 1; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wInputSigalType = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_INPUT_SIGNAL_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wf = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrder = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrderBiorthogonalDecomposition = 
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_maxLevel = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_MAXLEVEL, CB_GETCURSEL,0,(LPARAM)0 );
					if ( IsDlgButtonChecked( hDlg, IDC_CHECK_WAV_PRE_DELETE_CALC_PLOTS) == BST_CHECKED )
						vDoc[i].DeleteCalculatedPlots();
					vDoc[i].WaveletApply1();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect (vhWndChild[i], &rect);
					InvalidateRect(vhWndChild[i], &rect, true);
#endif
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
			}
			break;
		case IDC_BUTTON_WAV_EPSILON_CALC_LEFT_RIGHT:
			{
				vdouble dh;
				vdouble dg; 
				vdouble rh;
				vdouble rg;
				int left_h;
				int right_h;
				int left_g;
				int right_g;
				int wf = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
				int wOrder = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 );
				int wOrderBiorthogonalDecomposition = 
					1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 );


				char strWavEpsilon[15];					
				GetDlgItemText(hDlg, IDC_EDIT_WAV_EPSILON, strWavEpsilon, 14);
				double wEpsilon = atof(strWavEpsilon);

				WaveletEpsilon(
				  wf,		// m_wf, // флаг вейвлета
				  wOrder,	// m_wOrder, // порядок вейвлета
				  wOrderBiorthogonalDecomposition, // m_wOrderBiorthogonalDecomposition,
				  wEpsilon,
				  dh,
				  dg, 
				  rh,
				  rg,
				  left_h,
				  right_h,
				  left_g,
				  right_g);

				char str[1024];
				sprintf(str, "Lengthes of:\ndh = %d dg = %d rh = %d rg = %d\nleft_h = %d right_h = %d \nleft_g = %d right_g = %d", 
					dh.Length(), dg.Length(), rh.Length(),rg.Length(),
					left_h, right_h, left_g, right_g);
				MessageBox(0,str,"Wavelet Epsilon Result", 0);

			}
			break;
		case IDC_WAV_DISP :
			{
				for (int i = 0; i < 3; i++)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					vDoc[i].m_wf = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrder = 1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].m_wOrderBiorthogonalDecomposition = 
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 );
					vDoc[i].WaveletDisplay();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect (vhWndChild[i], &rect);
					InvalidateRect(vhWndChild[i], &rect, true);
#endif
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
			}
			break;
		case IDT_WAVELET_LEN:
			{
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				// SetWaveletFilterLength()
				char s[1024];
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				// SetWaveletFilterLength()
				int len_r_h;
				int len_d_h;
				int result = WaveletFilterLength(
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,0,(LPARAM)0 ),
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 ),
						1+SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_GETCURSEL,0,(LPARAM)0 ),
						len_r_h,len_d_h);
				if (result > 0)
					sprintf(s,"L фильтра=%d", result);
				if (result == 0)
					sprintf(s,"L фильтра=%d", result);
				if (result < 0)
					sprintf(s,"L фильтра=[%d %d]", len_r_h, len_d_h);

				SetDlgItemText(hDlg, IDC_STATIC_WAV_LEN,s);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDC_COMBO_WAV_ORDER2 :
			{
				SendMessage(hDlg,WM_COMMAND,IDT_WAVELET_LEN, 0);
			}
			break;
		case IDC_COMBO_WAV_ORDER :
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				if (WF_BIORTOGONAL == SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,
							0,(LPARAM)0 ))
				{
					switch (1+SendDlgItemMessage(hDlg, IDC_COMBO_WAV_ORDER, CB_GETCURSEL,0,(LPARAM)0 ))
					{
					case 1:
						{
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"1");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"3");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"5");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_SETCURSEL,
								1,(LPARAM)0 );
						}
						break;
					case 2:
						{
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"2");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"4");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"6");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"8");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_SETCURSEL,
								2,(LPARAM)0 );
						}
						break;
					case 3:
						{
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"1");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"3");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"5");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"7");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"9");
							SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_SETCURSEL,
								2,(LPARAM)0 );
						}
						break;
					}
				}
				SendMessage(hDlg,WM_COMMAND,IDT_WAVELET_LEN, 0);

			}
			break;
		case IDC_COMBO_WAV_TYPE :
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_RESETCONTENT, 0,0);
				// SetWaveletFilterLength()
				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER2, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				int ind = SendDlgItemMessage( hDlg, IDC_COMBO_WAV_TYPE, CB_GETCURSEL,
							0,(LPARAM)0 );
//				char s[1024];

				switch (ind)
				{
				case WF_BIORTOGONAL :
					{
							   
						//rf=menu('reconstruction filter order',
						//'1 at (1 3 5)',....
						//'2 at (2 4 6 8)',
						//'3 at (1 3 5 7 9)',
						//'4 at 4',
						//'5 at 5',...
						//'6 at 8');
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"1 at (1 3 5)");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"2 at (2 4 6 8)");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"3 at (1 3 5 7 9)");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"4 at 4");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"5 at 5");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"6 at 8");
					}
					break;
				case WF_MY_BIORTOGONAL:
					{
						//cdf=menu('cdf filters order',
						//'(5.3)',
						//'(7.5)',
						//'(9.7)');
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"(5.3)");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"(7.5)");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"(9.7)");
					}
					break;
				case WF_BIORTOGONAL_NONSTANDART:
					{
						//cdf=menu('cdf filters order',
						//'(9.7) at 4.2',
						//'(9.7) at 2.2');
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"(9.7) at 4.2");
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)"(9.7) at 2.2");
					}
					break;
				default :
					for (int i = lpWaveletDlgMem->lpWaveletData[ind].minOrder; i <= lpWaveletDlgMem->lpWaveletData[ind].maxOrder; i++)
					{
						char s[8];
						sprintf(s,"%d",i);
						SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)s);
					}
				}
				//	m_cmbWavOrder.SetCurSel(int((g_Wav[ind].minOrder + g_Wav[ind].maxOrder)/2)-1);

				SendDlgItemMessage( hDlg, IDC_COMBO_WAV_ORDER, CB_SETCURSEL,
					int((lpWaveletDlgMem->lpWaveletData[ind].minOrder + lpWaveletDlgMem->lpWaveletData[ind].maxOrder)/2)-1,
					(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendMessage(hDlg, WM_COMMAND, IDC_COMBO_WAV_ORDER,0);
				// SetWaveletFilterLength()
				SendMessage(hDlg,WM_COMMAND,IDT_WAVELET_LEN, 0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDOK :
			{
				EndDialog( hDlg, IDPRINT );
			}
			break;
			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}
DWORD WINAPI AudioWarning(void * p)
{
	while(true)
	{
		 MessageBeep(MB_ICONASTERISK);
		 Sleep(1000);
		 MessageBeep(MB_ICONEXCLAMATION);
		 Sleep(1000);
		 MessageBeep(MB_ICONHAND);
		 Sleep(1000);
		 MessageBeep(MB_ICONQUESTION);
		 Sleep(1000);
		 MessageBeep(MB_OK);
		 Sleep(1000);
	}
	return 0;
}

LRESULT CALLBACK DlgProcAudioWarning( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static HANDLE hAudioWarningThread;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			LPCSTR	lpWarningText = (LPCSTR)lParam;
			SetDlgItemText(hDlg, IDC_STATIC_AUDIO_DLG_WARNING, lpWarningText);

			DWORD dwChildID;
			hAudioWarningThread = ::CreateThread(NULL, 0, 
				AudioWarning, 
				reinterpret_cast<LPVOID>(lParam), 
				0,
				&dwChildID );
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				TerminateThread(hAudioWarningThread, 0);
				EndDialog( hDlg, IDOK );
			}
			break;
			
		case IDCANCEL :
			TerminateThread(hAudioWarningThread, 0);
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

//#include <commdlg.h>
HRESULT DisplayPrintPropertySheet(
    HWND hWnd  // Window that owns the property sheet
)
{
HRESULT hResult = 0;
#if 0// not work yet
LPPRINTDLGEX pPDX = NULL;
LPPRINTPAGERANGE pPageRanges = NULL;

// Allocate the PRINTDLGEX structure.

pPDX = (LPPRINTDLGEX)GlobalAlloc(GPTR, sizeof(PRINTDLGEX));
if (!pPDX)
    return E_OUTOFMEMORY;

// Allocate an array of PRINTPAGERANGE structures.

pPageRanges = (LPPRINTPAGERANGE) GlobalAlloc(GPTR, 
                   10 * sizeof(PRINTPAGERANGE));
if (!pPageRanges)
    return E_OUTOFMEMORY;

//  Initialize the PRINTDLGEX structure.

pPDX->lStructSize = sizeof(PRINTDLGEX);
pPDX->hwndOwner = hWnd;
pPDX->hDevMode = NULL;
pPDX->hDevNames = NULL;
pPDX->hDC = NULL;
pPDX->Flags = PD_RETURNDC | PD_COLLATE;
pPDX->Flags2 = 0;
pPDX->ExclusionFlags = 0;
pPDX->nPageRanges = 0;
pPDX->nMaxPageRanges = 10;
pPDX->lpPageRanges = pPageRanges;
pPDX->nMinPage = 1;
pPDX->nMaxPage = 1000;
pPDX->nCopies = 1;
pPDX->hInstance = 0;
pPDX->lpPrintTemplateName = NULL;
pPDX->lpCallback = NULL;
pPDX->nPropertyPages = 0;
pPDX->lphPropertyPages = NULL;
pPDX->nStartPage = START_PAGE_GENERAL;
pPDX->dwResultAction = 0;

//  Invoke the Print property sheet.

hResult = PrintDlgEx(pPDX);

if ( (hResult == S_OK) &&
           pPDX->dwResultAction == PD_RESULT_PRINT) {

    // User clicked the Print button, so
    // use the DC and other information returned in the 
    // PRINTDLGEX structure to print the document

}

if (pPDX->hDC != NULL) 
    DeleteDC(pPDX->hDC);
if (pPDX->hDevMode != NULL) 
    GlobalFree(pPDX->hDevMode); 
if (pPDX->hDevNames != NULL) 
    GlobalFree(pPDX->hDevNames); 
#endif
return hResult;
}


LRESULT CALLBACK DlgProcPrintParam( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPPRINTDLGDATA lpPrintDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
WriteRaporto(" PrintParamDlgProc IWM_INITDIALOG \n");
			lpPrintDlgMem = (LPPRINTDLGDATA)lParam;
WriteRaporto(" PrintParamDlgProc IWM_INITDIALOG 1\n");




			CheckDlgButton( hDlg, IDC_CHECK_PRINT_INCLUDE_X,
				lpPrintDlgMem->bIncludeX ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_PRINT_INCLUDE_Y,
				lpPrintDlgMem->bIncludeY ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_PRINT_INCLUDE_Z,
				lpPrintDlgMem->bIncludeZ ? BST_CHECKED : BST_UNCHECKED );




			SetDlgItemInt(hDlg, IDC_EDIT_COPIES, lpPrintDlgMem->dmCopies, false);
			
			switch (lpPrintDlgMem->dmOrientation)
			{
			case DMORIENT_PORTRAIT :
				CheckRadioButton( hDlg,
					IDC_RADIO_PORTRAIT,
					IDC_RADIO_LANDSCAPE,
					IDC_RADIO_PORTRAIT);
				break;
			case DMORIENT_LANDSCAPE:
				CheckRadioButton( hDlg,
					IDC_RADIO_PORTRAIT,
					IDC_RADIO_LANDSCAPE,
					IDC_RADIO_LANDSCAPE);
				break;
			}
			// Paper size

			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Letter 8 1/2 x 11 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Letter Small 8 1/2 x 11 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Tabloid 11 x 17 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Ledger 17 x 11 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Legal 8 1/2 x 14 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Statement 5 1/2 x 8 1/2 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Executive 7 1/4 x 10 1/2 in" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"A3 297 x 420 mm" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"A4 210 x 297 mm" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"A4 Small 210 x 297 mm" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"A5 148 x 210 mm" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"B4 (JIS) 250 x 354" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"B5 (JIS) 182 x 257 mm" );
			// SET COMBO OF PAPER SIZE
			SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_SETCURSEL,
				lpPrintDlgMem->dmPaperSize - 1,	(LPARAM)0 );




			LPBYTE pPrinterEnum		= NULL;
			LPBYTE pPrinterEnum2	= NULL;
			LPBYTE pPrinterEnum3	= NULL;
			DWORD cbNeeded;   // bytes received or required
			DWORD cReturned;  // number of printers enumerated
			DWORD cbNeeded2;   // bytes received or required
			DWORD cReturned2;  // number of printers enumerated
			DWORD cbNeeded3;   // bytes received or required
			DWORD cReturned3;  // number of printers enumerated

			//
			pPrinterEnum = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( PRINTER_INFO_4 ) );



			if (!EnumPrinters(
				PRINTER_ENUM_CONNECTIONS | 
				PRINTER_ENUM_LOCAL,         // printer object types
				NULL,						// name of printer object
				4,							// information level
				pPrinterEnum,				// printer information buffer
				sizeof( PRINTER_INFO_4 ),   // size of printer information buffer
				&cbNeeded,					// bytes received or required
				&cReturned))				// number of printers enumerated
			{
				DWORD lastError = GetLastError();
				if( lastError == lastError) // сетевой запрос не поддерживается
				{
					pPrinterEnum = (unsigned char *)HeapReAlloc( GetProcessHeap(),
						HEAP_ZERO_MEMORY,
						pPrinterEnum,
						sizeof( PRINTER_INFO_1 ) );

					if (!EnumPrinters(
							PRINTER_ENUM_LOCAL,         // printer object types
							NULL,						// name of printer object
							1,							// information level
							pPrinterEnum,				// printer information buffer
							sizeof( PRINTER_INFO_1 ),   // size of printer information buffer
							&cbNeeded,					// bytes received or required
							&cReturned))				// number of printers enumerated
					{
						lastError = GetLastError();
						if (lastError == 122)// область данных, перданных для сетевого запроса слишком мала
						{
							pPrinterEnum2 = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
								cbNeeded );
							if(!EnumPrinters(
								PRINTER_ENUM_LOCAL,         // printer object types
								NULL,						// name of printer object
								1,							// information level
								pPrinterEnum2,				// printer information buffer
								cbNeeded,					// size of printer information buffer
								&cbNeeded2,					// bytes received or required
								&cReturned2))				// number of printers enumerated
							{
								ErrorExit("EnumPrinters(Local)");
								return 0;
							}
							pPrinterEnum3 = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
								cbNeeded );
							if(!EnumPrinters(
								PRINTER_ENUM_DEFAULT,         // printer object types
								NULL,						// name of printer object
								1,							// information level
								pPrinterEnum3,				// printer information buffer
								cbNeeded,					// size of printer information buffer
								&cbNeeded3,					// bytes received or required
								&cReturned3))				// number of printers enumerated
							{
								ErrorExit("EnumPrinters(Default)");
								return 0;
							}

							LPCTSTR DefaultPrinterName;
							DWORD dwDefaultPrinterNumber;
							bool bDefaultPrinterDetected = false;
							if (cReturned3)
								DefaultPrinterName = (LPCTSTR)( (LPPRINTER_INFO_1)pPrinterEnum3 )->pName;

							for (DWORD pr = 0; pr < cReturned2; pr++)
							{
								LPCTSTR PrinterName = (LPCTSTR)( ((LPPRINTER_INFO_1)pPrinterEnum2)+pr)->pName;
								if (cReturned3 && strcmp(PrinterName, DefaultPrinterName) == 0)
								{
									dwDefaultPrinterNumber = pr;
									bDefaultPrinterDetected = true;
								}
								SendDlgItemMessage( hDlg, IDC_COMBO_PRINTER_NAME, CB_ADDSTRING, 0,
									(LPARAM)PrinterName);
							}
							if (bDefaultPrinterDetected)
								SendDlgItemMessage( hDlg, IDC_COMBO_PRINTER_NAME, CB_SETCURSEL,
									dwDefaultPrinterNumber,	(LPARAM)0 );


						}
						else
						{
							ErrorExit("EnumPrinters12");
							return 0;
						}
					}
				}
				else// сетевой запрос поддерживается
				{
					if (lastError == 122)// область данных, перданных для сетевого запроса слишком мала
					{

						pPrinterEnum2 = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
							cbNeeded );
									
						if(!EnumPrinters(
							PRINTER_ENUM_CONNECTIONS | 
							PRINTER_ENUM_LOCAL,         // printer object types
							NULL,						// name of printer object
							4,							// information level
							pPrinterEnum2,				// printer information buffer
							cbNeeded,					// size of printer information buffer
							&cbNeeded2,					// bytes received or required
							&cReturned2))				// number of printers enumerated
						{
							ErrorExit("EnumPrinters2");
							return 0;
						}

						pPrinterEnum3 = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
							cbNeeded );
						if(!EnumPrinters(
							PRINTER_ENUM_DEFAULT,         // printer object types
							NULL,						// name of printer object
							4,							// information level
							pPrinterEnum3,				// printer information buffer
							cbNeeded,					// size of printer information buffer
							&cbNeeded3,					// bytes received or required
							&cReturned3))				// number of printers enumerated
						{
							ErrorExit("EnumPrinters(Default)");
							return 0;
						}

						LPCTSTR DefaultPrinterName;
						DWORD dwDefaultPrinterNumber;
						bool bDefaultPrinterDetected = false;
						if (cReturned3)
							DefaultPrinterName = (LPCTSTR)( (LPPRINTER_INFO_4)pPrinterEnum3 )->pPrinterName;

						for (DWORD pr = 0; pr < cReturned2; pr++)
						{
							LPCTSTR PrinterName = (LPCTSTR)( ((LPPRINTER_INFO_4)pPrinterEnum2)+pr)->pPrinterName;
							if (cReturned3 && strcmp(PrinterName, DefaultPrinterName) == 0)
							{
								dwDefaultPrinterNumber = pr;
								bDefaultPrinterDetected = true;
							}
							SendDlgItemMessage( hDlg, IDC_COMBO_PRINTER_NAME, CB_ADDSTRING, 0,
								(LPARAM)PrinterName);
						}
						if (bDefaultPrinterDetected)
							SendDlgItemMessage( hDlg, IDC_COMBO_PRINTER_NAME, CB_SETCURSEL,
								dwDefaultPrinterNumber,	(LPARAM)0 );


					}
					else
					{
						ErrorExit(lastError, "EnumPrinters1");
						return 0;
					}
				}
			}




			if ( pPrinterEnum )
				HeapFree( GetProcessHeap(), 0, pPrinterEnum );
			if ( pPrinterEnum2 )
				HeapFree( GetProcessHeap(), 0, pPrinterEnum2 );
			if ( pPrinterEnum3 )
				HeapFree( GetProcessHeap(), 0, pPrinterEnum3 );

		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_PRINT_INCLUDE_X:
			lpPrintDlgMem->bIncludeX = IsDlgButtonChecked( hDlg, IDC_CHECK_PRINT_INCLUDE_X) == BST_CHECKED;
			break;
		case IDC_CHECK_PRINT_INCLUDE_Y:
			lpPrintDlgMem->bIncludeY = IsDlgButtonChecked( hDlg, IDC_CHECK_PRINT_INCLUDE_Y) == BST_CHECKED;
			break;
		case IDC_CHECK_PRINT_INCLUDE_Z :
			lpPrintDlgMem->bIncludeZ = IsDlgButtonChecked( hDlg, IDC_CHECK_PRINT_INCLUDE_Z) == BST_CHECKED;
			break;
		case IDC_COMBO_PAPER_SIZE:
			lpPrintDlgMem->dmPaperSize = (short) SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_GETCURSEL, 0, (LPARAM)0 );
			break;
		case IDPRINT_SETUP :
			{
				// имя принтера
				GetDlgItemText(hDlg,
					IDC_COMBO_PRINTER_NAME,
					lpPrintDlgMem->szPrinterName, 31);
				if (strlen(lpPrintDlgMem->szPrinterName) > 0)
					lpPrintDlgMem->bPrinterNameFound  = true;

				// число копий
				BOOL bTranslated;
				lpPrintDlgMem->dmCopies = 
					(short)GetDlgItemInt(hDlg, IDC_EDIT_COPIES, &bTranslated, false);
				if (!bTranslated)
					lpPrintDlgMem->dmCopies = 1;

				SendMessage(hMainWnd, WM_COMMAND, ID_PRINT_START, (LPARAM)1);
				EndDialog( hDlg, IDPRINT );
			}
			break;
		case IDPRINT :
			{
				// имя принтера
				GetDlgItemText(hDlg,
					IDC_COMBO_PRINTER_NAME,
					lpPrintDlgMem->szPrinterName, 31);
				if (strlen(lpPrintDlgMem->szPrinterName) > 0)
					lpPrintDlgMem->bPrinterNameFound  = true;

				// число копий
				BOOL bTranslated;
				lpPrintDlgMem->dmCopies = 
					(short)GetDlgItemInt(hDlg, IDC_EDIT_COPIES, &bTranslated, false);
				if (!bTranslated)
					lpPrintDlgMem->dmCopies = 1;

				SendMessage(hMainWnd, WM_COMMAND, ID_PRINT_START, (LPARAM)0);
				EndDialog( hDlg, IDPRINT );
			}
			break;		
		case IDOK :
			{
				// имя принтера
				GetDlgItemText(hDlg,
					IDC_COMBO_PRINTER_NAME,
					lpPrintDlgMem->szPrinterName, 31);
				if (strlen(lpPrintDlgMem->szPrinterName) > 0)
					lpPrintDlgMem->bPrinterNameFound  = true;

				// число копий
				BOOL bTranslated;
				lpPrintDlgMem->dmCopies = 
					(short)GetDlgItemInt(hDlg, IDC_EDIT_COPIES, &bTranslated, false);
				if (!bTranslated)
					lpPrintDlgMem->dmCopies = 1;

				EndDialog( hDlg, IDPRINT );
			}
			break;
			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

#include "../../wintools/src/checkListBox.h"

extern HBITMAP hbmpUnchecked, hbmpChecked; 
extern HBITMAP hbmpPicture, hbmpOld; 

extern WNDPROC wpOrigListBoxProc; 
extern LRESULT APIENTRY ListBoxSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);
extern void AddCheckedItem(HWND hwndList, LPSTR lpstr, LPARAM check);


DWORD APIENTRY DlgProcHidePlot( 
        HWND hDlg,            // window handle to dialog box 
        UINT message,         // type of message 
        UINT wParam,          // message-specific information 
        LONG lParam) 
{ 
	static LPHIDEPLOTDLGDATA	lpHidePlotDlgMem;
    TCHAR tchBuffer[BUFFER]; 
    HWND hListBox; 
    TEXTMETRIC tm; 
    int y; 
    HDC hdcMem; 
    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 
	LONG itemdata;

    switch (message) 
    { 
        case WM_INITDIALOG: 
			lpHidePlotDlgMem = (LPHIDEPLOTDLGDATA)lParam;
            // Load bitmaps. 
            hbmpUnchecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UNCHECKED)); 
            hbmpChecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_CHECKED)); 
            // Retrieve list box handle. 
            hListBox = GetDlgItem(hDlg, IDC_LIST_HIDE_PLOTS); 
 
            wpOrigListBoxProc = (WNDPROC) SetWindowLongPtr(hListBox, 
                GWLP_WNDPROC, (LONG_PTR) ListBoxSubclassProc); 

            // Initialize the list box text and associate a bitmap 
            // with each list box item. 

            // Initialize the list box text and associate a bitmap 
            // with each list box item. 
			if (vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.SetCurrentVectOnFirst())
			{
				int g = 1;
				do
				{
					bool toPlot = vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.GetCurrentVect().GetVectorCheck();
					if(toPlot)
					{
						AddCheckedItem(hListBox, 
							vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, 1); 
					}
					else
					{
						AddCheckedItem(hListBox, 
							vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, 0);
					}
					g++;
				}
				// Перемещаем текущий внутренний вектор
				while(vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.IncrementCurrentVect());
			}

            SetFocus(hListBox); 
            SendMessage(hListBox, LB_SETCURSEL, 0, 0); 
            return TRUE; 
 
        case WM_MEASUREITEM: 
 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            // Set the height of the list box items. 
            lpmis->itemHeight = YBITMAP; 
            return TRUE; 
 
        case WM_DRAWITEM: 
 
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
 
            // If there are no list box items, skip this message. 
            if (lpdis->itemID == -1) 
            { 
                break; 
            } 
            // Draw the bitmap and text for the list box item. Draw a 
            // rectangle around the bitmap if it is selected. 
 
            switch (lpdis->itemAction) 
            { 
                case ODA_DRAWENTIRE: 
 
                    // Display the bitmap associated with the item. 
 
                    itemdata = SendMessage(lpdis->hwndItem, 
                        LB_GETITEMDATA, lpdis->itemID, (LPARAM) 0); 

					if (itemdata)
						hbmpPicture = hbmpChecked;
					else
						hbmpPicture = hbmpUnchecked;

 
                    hdcMem = CreateCompatibleDC(lpdis->hDC); 

                    hbmpOld = (HBITMAP__ *)SelectObject(hdcMem, hbmpPicture); 
 
                    if(!BitBlt(lpdis->hDC, 
                        lpdis->rcItem.left, lpdis->rcItem.top, 
                        lpdis->rcItem.right - lpdis->rcItem.left, 
                        lpdis->rcItem.bottom - lpdis->rcItem.top, 
                        hdcMem, 0, 0, SRCCOPY)) 
					 ErrorExit("Screen to Compat Blt Failed"); 
 
                    // Display the text associated with the item. 
 
                    SendMessage(lpdis->hwndItem, LB_GETTEXT, 
                        lpdis->itemID, (LPARAM) tchBuffer); 
 
                    GetTextMetrics(lpdis->hDC, &tm); 
 
                    y = (lpdis->rcItem.bottom + lpdis->rcItem.top - 
                        tm.tmHeight) / 2;
						
					HFONT fontold, fontnew;

					fontnew = CreateFont(14,0,0,0,600,0,0,0,DEFAULT_CHARSET,
						OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,FF_DONTCARE,
						"Arial"
						);

					if (itemdata)
						fontold = (HFONT__ *)SelectObject(lpdis->hDC,fontnew);
 
                    TextOut(lpdis->hDC, 
                        XBITMAP + 6, 
                        y, 
                        tchBuffer, 
                        strlen(tchBuffer)); 						
 
                    SelectObject(hdcMem, (HBITMAP__ *)hbmpOld); 
					if (itemdata)
						SelectObject(lpdis->hDC,fontold);

                    DeleteDC(hdcMem); 
					if (itemdata)
						DeleteObject(fontnew);
 
                    // Is the item selected? 
 
                    if (lpdis->itemState & ODS_SELECTED) 
                    { 
                        // Draw a rectangle around bitmap to indicate 
                        // the selection. 
 
                        DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
                    } 
                    break; 
 
            } 
            return TRUE; 
 
        case WM_COMMAND: 
 
            switch (LOWORD(wParam)) 
            { 
                case IDOK: 
					{
						hListBox = GetDlgItem(hDlg, IDC_LIST_HIDE_PLOTS); 
						int nItems = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
						for (int i = 0; i < nItems; i++)
						{
							itemdata = SendMessage(hListBox, LB_GETITEMDATA, i, 0);
						}
						int idoc = lpHidePlotDlgMem->iWnd;
						if (vDoc[idoc].m_vPoints.SetCurrentVectOnFirst())
						{
							int g = 0;
							do
							{
								itemdata = SendMessage(hListBox, LB_GETITEMDATA, g, 0);
								if (itemdata != LB_ERR)
								{
									if (itemdata)
									{
										vDoc[idoc].m_vPoints.GetCurrentVect().SetVectorCheck(true);
									}
									else
									{
										vDoc[idoc].m_vPoints.GetCurrentVect().SetVectorCheck(false);
									}									
								}
								g++;
							}
							// Перемещаем текущий внутренний вектор
							while(vDoc[idoc].m_vPoints.IncrementCurrentVect());
						}
														
						vView[idoc].OnResizeGraphsCount(vhWndChild[idoc]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[idoc].DrawWithMemToWindow(vhWndChild[idoc]);
#else
						RECT rect;
						GetClientRect(vhWndChild[idoc],&rect);
						InvalidateRect(vhWndChild[idoc],&rect, true);
#endif

					}
					break;

                    
                case IDCANCEL:  
                    // Destroy the dialog box.  
                    EndDialog(hDlg, TRUE); 
                    return TRUE; 
 
                default:  
                    return FALSE; 
            } 
			break;
 
        case WM_DESTROY: 
 
            // Free any resources used by the bitmaps. 
 
            DeleteObject(hbmpChecked); 
            DeleteObject(hbmpUnchecked);  
            return TRUE; 
 
        default: 
            return FALSE; 
 
    } 
    return FALSE; 
} 




double ProbalityIntegral(double x)
{

	double 
		sign = x >= 0.0 ? 1.0 : -1.0,
		alpha = 0.001,
		step0 = 0.0001, 
		step = step0*alpha;
	if (x < 0.0)
		x = -x;

	double 
		sum = 0.0,
		h = 1.0,
		h2;
	for (double t = 0; t < x; t+=step)
	{
		h2 = exp(-t*t/2);
		sum += (h + h2)*step/2;
		h = h2;

		if (t > alpha)
			step = step0*t;
	}
	return 0.5 + sign*sum/sqrt(2*PI);
}
double InverseProbalityIntegral(double p)
{
	if (p == 1.)
		return 10;
	if (p == 0.)
		return -10;

	double 
		sign = p >= 0.5 ? 1.0 : -1.0,
		alpha = 0.001,
		step0 = 0.00001, 
		step = step0*alpha;

	if (p < 0.5)
		p = 1.0-p;

	double x = 0.0,
		sum = 0.0,
		sum_step,
		MaxSum = (p - 0.5) * sqrt(2*PI) / sign,
		h = 1.0,
		h2;
	double t = 0;

	while (sum < MaxSum)
	{
		if (t > alpha)
			step = step0*t;
		if (t > 4)
			step = 1000*step0*t;
		if (t > 5)
			step = 10000*step0*t;

		t+=step;
		h2 = exp(-t*t/2);
		sum_step = (h + h2)*step/2;
		sum += sum_step;
		h = h2;
	}
	t -= (sum-MaxSum)/sum_step*step;
	return t*sign;
}
double CorrelationCoefficient(int len,  double *pv1, double *pv2)
{
	double 
		sum1 = 0.0,
		sum2 = 0.0;
	for (int i = 0; i < len; i++)
	{
		sum1 += pv1[i];
		sum2 += pv2[i];
	}
	double 
		mean1 = sum1 / len,
		mean2 = sum2 / len;

	double 
		sigma1 = 0.0,
		sigma2 = 0.0,
		Cov = 0.0;

	for (int i = 0; i < len; i++)
	{
		sigma1 += (pv1[i] - mean1)*(pv1[i] - mean1);
		sigma2 += (pv2[i] - mean2)*(pv2[i] - mean2);
		Cov += (pv1[i] - mean1)*(pv2[i] - mean2);
	}

	
	return Cov/sqrt(sigma1*sigma2);
}
void interp_common_time_scale(vdouble *pt1, vdouble *py1, vdouble *pt2, vdouble *py2, vdouble& t,vdouble& Y1, vdouble& Y2 )
{
	if (!pt1 || !pt2 || !py1 || !py2)
	{
		char err_str[255];
		sprintf(err_str, "At least on of pointers is NULL", pt1->Length(), py1->Length());
		MessageBox(0,err_str, "interp_common_time_scale",0);
		return;
	}
	if(pt1->Length() != py1->Length())
	{
		char err_str[255];
		sprintf(err_str, "pt1->Length(%d) != py1->Length(%d)", pt1->Length(), py1->Length());
		MessageBox(0,err_str, "interp_common_time_scale",0);
		return;
	}
	if(pt2->Length() != py2->Length())
	{
		char err_str[255];
		sprintf(err_str, "pt2->Length(%d) != py2->Length(%d)", pt2->Length(), py2->Length());
		MessageBox(0,err_str, "interp_common_time_scale",0);
		return;
	} 

		int i1, i2, i;
		int len1 = py1->Length(),
			len2 = py2->Length();
		int min_len = len1 < len2 ? len1 : len2;

		// minimal step of time
		double 
			min_step_t1 = pt1->DiffVector().Median(),
			min_step_t2 = pt2->DiffVector().Median(),
			min_step_t = min_step_t1 < min_step_t2 ? min_step_t1 : min_step_t2;

		if (min_step_t == 0.0)
		{
			double
				median_step_t1 = pt1->DiffVector().Median(),
				median_step_t2 = pt2->DiffVector().Median(),
				median_step_t = median_step_t1 < median_step_t2 ? median_step_t1 : median_step_t2;
			min_step_t = median_step_t;
			char str[255];
			sprintf(str, "min_step_t == 0.0\n so min_step_t = median_step_t = %lf", median_step_t);
			MessageBox(0,str, "CorrelationCoefficient",0);
		}

		i1 = 0;// index in first vector
		i2 = 0;// index in second vector
		i = 0;// index of common vectors
		while( i1 < len1 && i2 < len2 && i < min_len)
		{
			double 
				t1 = pt1->operator [](i1),
				t2 = pt2->operator [](i2);
			// compare t1 and t2
			if ( t1 == t2 || fabs(t1-t2) < 0.8*min_step_t)
			{
				i1++;
				i2++;
				i++;
			}
			else
			{
				if (t1 > t2)
				{
					i2++;
				}
				if (t1 < t2)
				{
					i1++;
				}
			}
		}
		int len = i;// number of really filled members of vector


		// vector of signals on comon time scale
		t.resize(len);
		Y1.resize(len);
		Y2.resize(len);

		i1 = 0;// index in first vector
		i2 = 0;// index in second vector
		i = 0;// index of common vectors

		while( i1 < len1 && i2 < len2 && i < min_len)
		{
			double 
				t1 = pt1->operator [](i1),
				t2 = pt2->operator [](i2);
			// compare t1 and t2
			if ( t1 == t2 || fabs(t1-t2) < 0.8*min_step_t)
			{
				t[i]	= t1 == t2 ? t1 : (t1+t2) / 2.0;
				Y1[i]	= py1->operator [](i1);
				Y2[i]	= py2->operator [](i2);
				i1++;
				i2++;
				i++;

			}
			else
			{
				if (t1 > t2)
				{
					i2++;
				}
				if (t1 < t2)
				{
					i1++;
				}
			}
		}

}




double CorrelationCoefficient(vdouble *pt1, vdouble *py1, vdouble *pt2, vdouble *py2, double& epsilon)
{
	if (!pt1 || !pt2 || !py1 || !py2)
	{
		char err_str[255];
		sprintf(err_str, "At least on of pointers is NULL", pt1->Length(), py1->Length());
		MessageBox(0,err_str, "CorrelationCoefficient",0);
		return 0.0;
	}
	if(pt1->Length() != py1->Length())
	{
		char err_str[255];
		sprintf(err_str, "pt1->Length(%d) != py1->Length(%d)", pt1->Length(), py1->Length());
		MessageBox(0,err_str, "CorrelationCoefficient",0);
		return 0.0;
	}
	if(pt2->Length() != py2->Length())
	{
		char err_str[255];
		sprintf(err_str, "pt2->Length(%d) != py2->Length(%d)", pt2->Length(), py2->Length());
		MessageBox(0,err_str, "CorrelationCoefficient",0);
		return 0.0;
	} 

	double beta = .95,// Доверительная вероятность
		//epsilon; // плечо доверительного интервала
		mju22,
		Cov,
		DCov;

	double 
		mean1,
		mean2,
		sigma1,
		sigma2,
		ro;
	vdouble 
		y1_centred,
		y2_centred;

	epsilon = 0.0;

	if (py1->Length() == py2->Length())
	{
		int len = py1->Length();

		mean1 = py1->Mean();
		mean2 = py2->Mean();

		y1_centred = *py1 - mean1;
		y2_centred = *py2 - mean2;

		sigma1 = sqrt((y1_centred*y1_centred).Mean());
		sigma2 = sqrt((y2_centred*y2_centred).Mean());

		// Covariation
		Cov = (y1_centred*y2_centred).Mean();
		// оценка четвёртый смешанный момент
		mju22 = (y1_centred*y1_centred*y2_centred*y2_centred).Mean();
		//mju22 = 3*Cov*Cov;
		// коэффициент корреляции
		ro = Cov/sigma1/sigma2;
		// Дисперсия коэффициента корреляции
		DCov = (mju22 - ((len - 3)/(len-1))*Cov*Cov)/len;

		// плечо доверительного интервала
		epsilon = sqrt(DCov) / sigma1 / sigma2 * InverseProbalityIntegral((1.+beta)/2.);
	}
	else
	{
		int i1, i2, i;
		int len1 = py1->Length(),
			len2 = py2->Length();
		int min_len = len1 < len2 ? len1 : len2;

		// minimal step of time
		double 
			min_step_t1 = pt1->DiffVector().Median(),
			min_step_t2 = pt2->DiffVector().Median(),
			min_step_t = min_step_t1 < min_step_t2 ? min_step_t1 : min_step_t2;

		if (min_step_t == 0.0)
		{
			double
				median_step_t1 = pt1->DiffVector().Median(),
				median_step_t2 = pt2->DiffVector().Median(),
				median_step_t = median_step_t1 < median_step_t2 ? median_step_t1 : median_step_t2;
			min_step_t = median_step_t;
			char str[255];
			sprintf(str, "min_step_t == 0.0\n so min_step_t = median_step_t = %lf", median_step_t);
			MessageBox(0,str, "CorrelationCoefficient",0);
		}


		// vector of signals on comon time scale
		vdouble t, y1, y2;// common scale
		t.resize(min_len);
		y1.resize(min_len);
		y2.resize(min_len);

		i1 = 0;// index in first vector
		i2 = 0;// index in second vector
		i = 0;// index of common vectors

		while( i1 < len1 && i2 < len2 && i < min_len)
		{
			double 
				t1 = pt1->operator [](i1),
				t2 = pt2->operator [](i2);
			// compare t1 and t2
			if ( t1 == t2 || fabs(t1-t2) < 0.8*min_step_t)
			{
				t[i]	= t1 == t2 ? t1: (t1+t2) / 2.0;
				y1[i]	= py1->operator [](i1);
				y2[i]	= py2->operator [](i2);
				i1++;
				i2++;
				i++;

			}
			else
			{
				if (t1 > t2)
				{
					i2++;
				}
				if (t1 < t2)
				{
					i1++;
				}
			}
		}
		int len = i;// number of really filled members of vector
		if (len == min_len)
		{
			/*char str[255];
			sprintf(str, "len == min_len = %d", min_len);
			MessageBox(0,str, "CorrelationCoefficient",0);*/

			mean1 = y1.Mean(),
			mean2 = y2.Mean();

			y1_centred = y1 - mean1;
			y2_centred = y2 - mean2;

			sigma1 = sqrt((y1_centred*y1_centred).Mean()),
			sigma2 = sqrt((y2_centred*y2_centred).Mean()),
			// Covariation
			Cov = (y1_centred*y2_centred).Mean();
			// оценка четвёртый смешанный момент
			mju22 = (y1_centred*y1_centred*y2_centred*y2_centred).Mean();
			//mju22 = 3*Cov*Cov;
			// коэффициент корреляции
			ro = Cov/sigma1/sigma2;
			// Дисперсия коэффициента корреляции
			DCov = (mju22 - ((len - 3)/(len-1))*Cov*Cov)/len;

			// плечо доверительного интервала
			epsilon = sqrt(DCov) / sigma1 / sigma2 * InverseProbalityIntegral((1.+beta)/2.);
		}
		else
		{
			/*char str[255];
			sprintf(str, "len %d != min_len = %d",len, min_len);
			MessageBox(0,str, "CorrelationCoefficient",0);*/

			mean1 = y1.Mean(len),
			mean2 = y2.Mean(len);

			y1_centred = y1 - mean1;
			y2_centred = y2 - mean2;

			sigma1 = sqrt((y1_centred*y1_centred).Mean(len)),
			sigma2 = sqrt((y2_centred*y2_centred).Mean(len)),
			// Covariation
			Cov = (y1_centred*y2_centred).Mean(len);
			// оценка четвёртый смешанный момент
			mju22 = (y1_centred*y1_centred*y2_centred*y2_centred).Mean(len);
			//mju22 = 3*Cov*Cov;
			// коэффициент корреляции
			ro = Cov/sigma1/sigma2;
			// Дисперсия коэффициента корреляции
			DCov = (mju22 - ((len - 3)/(len-1))*Cov*Cov)/len;

			// плечо доверительного интервала
			epsilon = sqrt(DCov) / sigma1 / sigma2 * InverseProbalityIntegral((1.+beta)/2.);
		}
	/*	vdouble _y1(len), _y2(len), _t(len);
		for( i = 0; i< len; i++)
		{
			_t[i] = t[i];
			_y1[i] = y1[i];
			_y2[i] = y2[i];
		}
		WinPlot(_t,_y1);
		WinPlot(_t,_y2);*/
	}
	return ro;
}
DWORD APIENTRY DlgProcCorrelationCoefficientPlot( 
        HWND hDlg,            // window handle to dialog box 
        UINT message,         // type of message 
        UINT wParam,          // message-specific information 
        LONG lParam) 
{ 
	static LPHIDEPLOTDLGDATA	lpHidePlotDlgMem;
    TCHAR tchBuffer[BUFFER]; 
    HWND hListBox; 
    TEXTMETRIC tm; 
    int y; 
    HDC hdcMem; 
    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 
	LONG itemdata;
	int idoc;
	int g;

    switch (message) 
    { 
        case WM_INITDIALOG: 
			lpHidePlotDlgMem = (LPHIDEPLOTDLGDATA)lParam;
            // Load bitmaps. 
            hbmpUnchecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UNCHECKED)); 
            hbmpChecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_CHECKED)); 
            // Retrieve list box handle. 
            hListBox = GetDlgItem(hDlg, IDC_LIST_KORRELATION_PLOTS); 
 
            wpOrigListBoxProc = (WNDPROC) SetWindowLongPtr(hListBox, 
                GWLP_WNDPROC, (LONG_PTR) ListBoxSubclassProc); 

            // Initialize the list box text and associate a bitmap 
            // with each list box item. 

            // Initialize the list box text and associate a bitmap 
            // with each list box item. 
			SetDlgItemText(hDlg,IDC_EDIT_KORRELATION, 
				"Select only two vectors and press OK to calculation correlation  coefficient");
#if 0
			if (vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.SetCurrentVectOnFirst())
			{
				int g = 1;
				do
				{
					bool toPlot = vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.GetCurrentVect().GetVectorCheck();
					if(toPlot)
					{
						AddCheckedItem(hListBox, 
							vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, 1); 
					}
					else
					{
						AddCheckedItem(hListBox, 
							vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, 0);
					}
					g++;
				}
				// Перемещаем текущий внутренний вектор
				while(vDoc[lpHidePlotDlgMem->iWnd].m_vPoints.IncrementCurrentVect());
			}
#else
			g = 1;
			for (idoc = 0; idoc < 3; idoc++)
			{
				if (vDoc[idoc].m_vPoints.SetCurrentVectOnFirst())
				{
					do
					{
						bool toDisp = vDoc[idoc].m_vPoints.GetCurrentVect().GetVectorCheck();
						bool toCheck = false;
						if (toDisp)
						{
							if(toCheck)
							{
								AddCheckedItem(hListBox, 
									vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, 1); 
							}
							else
							{
								AddCheckedItem(hListBox, 
									vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, 0);
							}
							g++;
						}
					}
					// Перемещаем текущий внутренний вектор
					while(vDoc[idoc].m_vPoints.IncrementCurrentVect());
				}
			}
#endif

			SetDlgItemText(hDlg, IDC_EDIT_X, "0.0");
			SetDlgItemText(hDlg, IDC_EDIT_PROBALITY_INT_X, "0.5");

            SetFocus(hListBox); 
            SendMessage(hListBox, LB_SETCURSEL, 0, 0); 
            return TRUE; 
 
        case WM_MEASUREITEM: 
 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            // Set the height of the list box items. 
            lpmis->itemHeight = YBITMAP; 
            return TRUE; 
 
        case WM_DRAWITEM: 
 
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
 
            // If there are no list box items, skip this message. 
            if (lpdis->itemID == -1) 
            { 
                break; 
            } 
            // Draw the bitmap and text for the list box item. Draw a 
            // rectangle around the bitmap if it is selected. 
 
            switch (lpdis->itemAction) 
            { 
                case ODA_DRAWENTIRE: 
 
                    // Display the bitmap associated with the item. 
 
                    itemdata = SendMessage(lpdis->hwndItem, 
                        LB_GETITEMDATA, lpdis->itemID, (LPARAM) 0); 

					if (itemdata)
						hbmpPicture = hbmpChecked;
					else
						hbmpPicture = hbmpUnchecked;

 
                    hdcMem = CreateCompatibleDC(lpdis->hDC); 

                    hbmpOld = (HBITMAP__ *)SelectObject(hdcMem, hbmpPicture); 
 
                    BitBlt(lpdis->hDC, 
                        lpdis->rcItem.left, lpdis->rcItem.top, 
                        lpdis->rcItem.right - lpdis->rcItem.left, 
                        lpdis->rcItem.bottom - lpdis->rcItem.top, 
                        hdcMem, 0, 0, SRCCOPY); 
 
                    // Display the text associated with the item. 
 
                    SendMessage(lpdis->hwndItem, LB_GETTEXT, 
                        lpdis->itemID, (LPARAM) tchBuffer); 
 
                    GetTextMetrics(lpdis->hDC, &tm); 
 
                    y = (lpdis->rcItem.bottom + lpdis->rcItem.top - 
                        tm.tmHeight) / 2;
						
					HFONT fontold, fontnew;

					fontnew = CreateFont(14,0,0,0,600,0,0,0,DEFAULT_CHARSET,
						OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,FF_DONTCARE,
						"Arial"
						);

					if (itemdata)
						fontold = (HFONT__ *)SelectObject(lpdis->hDC,fontnew);
 
                    TextOut(lpdis->hDC, 
                        XBITMAP + 6, 
                        y, 
                        tchBuffer, 
                        strlen(tchBuffer)); 						
 
                    SelectObject(hdcMem, (HBITMAP__ *)hbmpOld); 
					if (itemdata)
						SelectObject(lpdis->hDC,fontold);
                    DeleteDC(hdcMem); 
					if (itemdata)
						DeleteObject(fontnew);
 
                    // Is the item selected? 
 
                    if (lpdis->itemState & ODS_SELECTED) 
                    { 
                        // Draw a rectangle around bitmap to indicate 
                        // the selection. 
 
                        DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
                    } 
                    break; 
 
            } 
            return TRUE; 
 
        case WM_COMMAND: 
 
            switch (LOWORD(wParam)) 
            { 
			case IDC_BUTTON_PROBALITY_INT:
				{
					char str_x[32];
					double x;
					GetDlgItemText(hDlg,IDC_EDIT_X, str_x, 32);
					sscanf(str_x, "%lf\0", &x);
					double  P = ProbalityIntegral(x);
					sprintf(str_x,"%lf", P);
					SetDlgItemText(hDlg,IDC_EDIT_PROBALITY_INT_X, str_x);
					x = InverseProbalityIntegral(P);
					sprintf(str_x,"%lf", x);
					SetDlgItemText(hDlg,IDC_EDIT_X2, str_x);

				}
				break;
                case IDOK: 
					{
						hListBox = GetDlgItem(hDlg, IDC_LIST_KORRELATION_PLOTS); 
						int nItems = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
						for (int i = 0; i < nItems; i++)
						{
							itemdata = SendMessage(hListBox, LB_GETITEMDATA, i, 0);
						}
						vdouble *px1, *py1, *px2, *py2;
						const int titleMaxLen = 512;
						char title1[titleMaxLen], title2[titleMaxLen];
						int iplot_selected = 0;
						int g = 0;
						for (idoc = 0; idoc < 3; idoc++)
						{
							if (vDoc[idoc].m_vPoints.SetCurrentVectOnFirst())
							{
								
								do
								{
									bool toDisp = vDoc[idoc].m_vPoints.GetCurrentVect().GetVectorCheck();
									if (toDisp)
									{
										itemdata = SendMessage(hListBox, LB_GETITEMDATA, g, 0);
										if (itemdata != LB_ERR)
										{
											if (itemdata)
											{
												iplot_selected++;
												if (iplot_selected == 1)
												{
													px1 = vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().px;
													py1 = vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().py;
													strncpy(title1, vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, titleMaxLen);
												}
												if (iplot_selected == 2)
												{
													px2 = vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().px;
													py2 = vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().py;
													strncpy(title2, vDoc[idoc].m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, titleMaxLen);
												}
												if (iplot_selected > 2)
													break;
											}
										}
										g++;
									}
								}
								// Перемещаем текущий внутренний вектор
								while(vDoc[idoc].m_vPoints.IncrementCurrentVect());
							}
						}

						if (iplot_selected == 1)
						{
							double epsilon;
							double ro = CorrelationCoefficient(px1,py1,px1,py1, epsilon);
							char respond_str[2048], koeff_str[32];
							sprintf(respond_str, "Коэффициент автокорреляции параметра \"%s\" равен %lf",
								title1, ro);
							SetDlgItemText(hDlg,IDC_EDIT_KORRELATION, respond_str);
							SetDlgItemText(hDlg,IDC_EDIT_CORRELATION_PARAM1, title1);
							SetDlgItemText(hDlg,IDC_EDIT_CORRELATION_PARAM2, title1);
							//SetDlgItemText(hDlg,IDC_RICHEDIT_KORRELATION, respond_str);
							sprintf(koeff_str, "%lf",ro); 
							SetDlgItemText(hDlg, IDC_EDIT_ONLY_KORRELATION_COEFFICIENT, koeff_str);

							sprintf(koeff_str, "%lf",ro+epsilon); 
							SetDlgItemText(hDlg, IDC_EDIT_ONLY_KORRELATION_COEFFICIENT_MAX_INTERVAL, koeff_str);
							sprintf(koeff_str, "%lf",ro-epsilon); 
							SetDlgItemText(hDlg, IDC_EDIT_ONLY_KORRELATION_COEFFICIENT_MIN_INTERVAL, koeff_str);



						}
						if (iplot_selected >= 2)
						{
							double epsilon;
							double ro = CorrelationCoefficient(px1,py1,px2,py2, epsilon);
							char respond_str[2048], koeff_str[32];
							sprintf(respond_str, "Коэффициент корреляции параметров \"%s\" и \"%s\" равен %lf",
								title1, title2, ro);
							SetDlgItemText(hDlg,IDC_EDIT_KORRELATION, respond_str);
							SetDlgItemText(hDlg,IDC_EDIT_CORRELATION_PARAM1, title1);
							SetDlgItemText(hDlg,IDC_EDIT_CORRELATION_PARAM2, title2);
							
							sprintf(koeff_str, "%lf",ro); 
							SetDlgItemText(hDlg, IDC_EDIT_ONLY_KORRELATION_COEFFICIENT, koeff_str);

							sprintf(koeff_str, "%lf",ro+epsilon); 
							SetDlgItemText(hDlg, IDC_EDIT_ONLY_KORRELATION_COEFFICIENT_MAX_INTERVAL, koeff_str);
							sprintf(koeff_str, "%lf",ro-epsilon); 
							SetDlgItemText(hDlg, IDC_EDIT_ONLY_KORRELATION_COEFFICIENT_MIN_INTERVAL, koeff_str);
/*
	vdouble n, x1, x2,
		tt;
	vdouble T1;
	vdouble T2;
	interp_common_time_scale(px1,py1,px2,py2, tt,T1, T2 );


	hist2(log10(T1), log10(T2), 100, 100,   n,  x1, x2);

	WinSurf(x1 , x2 , n);
*/
						}
					}
					break;
                    
                case IDCANCEL:  
                    // Destroy the dialog box.  
                    EndDialog(hDlg, TRUE); 
                    return TRUE; 
 
                default:  
                    return FALSE; 
            } 
			break;
 
        case WM_DESTROY: 
 
            // Free any resources used by the bitmaps. 
 
            DeleteObject(hbmpChecked); 
            DeleteObject(hbmpUnchecked);  
            return TRUE; 
 
        default: 
            return FALSE; 
 
    } 
    return FALSE; 
} 

typedef struct 
{
	WORD wLatitudeDegrees;
	WORD wLatitudeMinutes;
	float fLatitudeSeconds;
	short LatitudeSign;
	WORD wLognitudeDegrees;
	WORD wLognitudeMinutes;
	float fLognitudeSeconds;
	short LognitudeSign;
	char	szNameOfResearchPoint[172];
	double	LatitudeOfResearchPoint;//Широта точки наблюдения
	double	LognitudeOfResearchPoint;// Долгота точка наблюдения
	int nResearchPointNumber;
	short scaleModeX;
	HWND hWnd;
	double near_r;// радиус вокруг точки наблюдения для подсчёта статистики землетрясений внутри радиуса.
	double magnitudeBorder; //граница магнитуд, отделяющая малые от больших землетрясения
	double depthIntervalMin;
	double depthIntervalMax;
	short shPeriodFlag;
} EARTHQUAKESDLGDATA, *LPEARTHQUAKESDLGDATA;

LRESULT CALLBACK DlgProcEarthquakes( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPEARTHQUAKESDLGDATA lpEarthquakesDlgMem;
	char latitudeSeconds[125],
		lognitudeSeconds[125];
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{			
			lpEarthquakesDlgMem = (LPEARTHQUAKESDLGDATA)lParam;
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_NAME_OF_RESEARCH_POINT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Artuhovka");
			SendDlgItemMessage( hDlg, IDC_COMBO_NAME_OF_RESEARCH_POINT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Antarktida");
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_NAME_OF_RESEARCH_POINT, CB_SETCURSEL,
				lpEarthquakesDlgMem->nResearchPointNumber,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendMessage(hDlg, WM_COMMAND, ID_SELECT_GEOCOORDINATES_OF_RESEARCH_POINT, 0);
			SendMessage(hDlg, WM_COMMAND, ID_INIT_GEOCOORDINATE_CONTROLS, 0);

			SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"График не масштабировать");
			SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Масштабировать по предыдущим");
			SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Масштабировать вместе с предыдущими");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_SETCURSEL,
				lpEarthquakesDlgMem->scaleModeX,(LPARAM)0 );

			SetDlgItemInt(hDlg,IDC_EDIT_NEAR_R, (int)lpEarthquakesDlgMem->near_r, false);
			char str[128];
			sprintf(str,"%1.1f", lpEarthquakesDlgMem->magnitudeBorder);
			SetDlgItemText(hDlg, IDC_EDIT_MAGNITUDE_BORDER, str);

			SetDlgItemInt(hDlg,IDC_EDIT_DEPTH_INTERVAL_MIN, (int)lpEarthquakesDlgMem->depthIntervalMin, false);
			SetDlgItemInt(hDlg,IDC_EDIT_DEPTH_INTERVAL_MAX, (int)lpEarthquakesDlgMem->depthIntervalMax, false);

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"1 sec" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"1 min" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"5 min" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"15 min" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"30 min" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"1 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"2 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"3 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"4 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"6 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"8 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"12 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"24 hours" );
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						   (LPARAM)(LPCTSTR)"2x12 hours" );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_SETCURSEL, 
				 lpEarthquakesDlgMem->shPeriodFlag,
						   (LPARAM)0 );

		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{	
          case IDC_COMBO_PERIOD :
			   {				   
				   long lComboCurSel = SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_GETCURSEL, 0,
							   (LPARAM)0 );
				   lpEarthquakesDlgMem->shPeriodFlag = short(lComboCurSel);
			   }
			   break;
		case IDC_COMBO_NAME_OF_RESEARCH_POINT:
			{
				lpEarthquakesDlgMem->nResearchPointNumber = SendDlgItemMessage( hDlg, 
					IDC_COMBO_NAME_OF_RESEARCH_POINT,
					CB_GETCURSEL,0,(LPARAM)0 );
			SendMessage(hDlg, WM_COMMAND, ID_SELECT_GEOCOORDINATES_OF_RESEARCH_POINT, 0);
			SendMessage(hDlg, WM_COMMAND, ID_INIT_GEOCOORDINATE_CONTROLS, 1);

			}
			break;
		case IDC_COMBO_SCALE_MODE:
				lpEarthquakesDlgMem->scaleModeX = (short)SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_GETCURSEL,0,(LPARAM)0 );
				break;

		case ID_SELECT_GEOCOORDINATES_OF_RESEARCH_POINT:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				switch(lpEarthquakesDlgMem->nResearchPointNumber)
				{
				case 0:

					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					// Artjuhovka
					lpEarthquakesDlgMem->LatitudeSign		= 1;
					lpEarthquakesDlgMem->wLatitudeDegrees	= 49;
					lpEarthquakesDlgMem->wLatitudeMinutes	= 40;
					lpEarthquakesDlgMem->fLatitudeSeconds	= 0.0;

					lpEarthquakesDlgMem->LognitudeSign		= 1;
					lpEarthquakesDlgMem->wLognitudeDegrees	= 36;
					lpEarthquakesDlgMem->wLognitudeMinutes	= 30;
					lpEarthquakesDlgMem->fLognitudeSeconds	= 0.0;

					break;
				case 1:
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					// Antarktida
					lpEarthquakesDlgMem->LatitudeSign		= -1;
					lpEarthquakesDlgMem->wLatitudeDegrees	= 65;
					lpEarthquakesDlgMem->wLatitudeMinutes	= 02;
					lpEarthquakesDlgMem->fLatitudeSeconds	= 36.0;

					lpEarthquakesDlgMem->LognitudeSign		= -1;
					lpEarthquakesDlgMem->wLognitudeDegrees	= 63;
					lpEarthquakesDlgMem->wLognitudeMinutes	= 46;
					lpEarthquakesDlgMem->fLognitudeSeconds	= 59.0;

					break;
				}
				lpEarthquakesDlgMem->LatitudeOfResearchPoint = 
					double(lpEarthquakesDlgMem->LatitudeSign) * (
					double(lpEarthquakesDlgMem->wLatitudeDegrees) +
					double(lpEarthquakesDlgMem->wLatitudeMinutes) / 60. + 
					double(lpEarthquakesDlgMem->fLatitudeSeconds) / 3600.);

				lpEarthquakesDlgMem->LognitudeOfResearchPoint = 
					double(lpEarthquakesDlgMem->LognitudeSign) * (
					double(lpEarthquakesDlgMem->wLognitudeDegrees) +
					double(lpEarthquakesDlgMem->wLognitudeMinutes) / 60. + 
					double(lpEarthquakesDlgMem->fLognitudeSeconds) / 3600.);
			}
			break;
		case ID_TEST_GEOCOORDINATE_CONTROLS:
			{
					BOOL bTranslated;
					WORD wValue;
					// Latitude Degrees
				   //-----------------------------------------
				   //-----------------------------------------
					wValue = 
						(WORD)GetDlgItemInt(hDlg, 
						IDC_EDIT_LATITUDE, 
						&bTranslated, false);

					if (!bTranslated)
					{
						MessageBox(NULL, 
							"Incorrect Latitude Degrees", "Date Error", 0);
						return 0;
					}
					else
					{
						if (wValue > 90)
						{
							MessageBox(NULL, 
								"Latitude Degrees must be in interval 0...90", "Date Error", 0);
							return 0;
						}
					}
					lpEarthquakesDlgMem->wLatitudeDegrees = wValue;
				   //-----------------------------------------
					// Latitude Minutes
				   //-----------------------------------------
				   //-----------------------------------------
					wValue = 
						(WORD)GetDlgItemInt(hDlg, 
						IDC_EDIT_LATITUDE2, 
						&bTranslated, false);

					if (!bTranslated)
					{
						MessageBox(NULL, 
							"Incorrect Latitude Minutes", "Date Error", 0);
						return 0;
					}
					else
					{
						if (wValue > 60)
						{
							MessageBox(NULL, 
								"Latitude Minutes must be in interval 0...60", "Date Error", 0);
							return 0;
						}
					}
					lpEarthquakesDlgMem->wLatitudeMinutes = wValue;

				   //-----------------------------------------

					// Longitude Degrees
				   //-----------------------------------------
				   //-----------------------------------------
					wValue =
						(WORD)GetDlgItemInt(hDlg, 
						IDC_EDIT_LOGNITUDE, 
						&bTranslated, false);

					if (!bTranslated)
					{
						MessageBox(NULL, 
							"Incorrect Longitude Degrees", "Date Error", 0);
						return 0;
					}
					else
					{
						if (wValue > 180)
						{
							MessageBox(NULL, 
								"Latitude Degrees must be in interval 0...180", "Date Error", 0);
							return 0;
						}
					}
					lpEarthquakesDlgMem->wLognitudeDegrees = wValue;
				   //-----------------------------------------
					// Longitude Minutes
				   //-----------------------------------------
				   //-----------------------------------------
					wValue =
						(WORD)GetDlgItemInt(hDlg, 
						IDC_EDIT_LOGNITUDE2, 
						&bTranslated, false);

					if (!bTranslated)
					{
						MessageBox(NULL, 
							"Incorrect Lognitude Minutes", "Date Error", 0);
						return 0;
					}
					else
					{
						if (wValue > 60)
						{
							MessageBox(NULL, 
								"Longitude Minutes must be in interval 0...60", "Date Error", 0);
							return 0;
						}
					}
					lpEarthquakesDlgMem->wLognitudeMinutes = wValue;
				   //-----------------------------------------
					float Value;
					GetDlgItemText(hDlg,IDC_EDIT_LATITUDE3, latitudeSeconds, 12);
					int rez = sscanf(latitudeSeconds, "%f", &Value);
					if (rez != 1 || rez == EOF)
					{
						MessageBox(NULL, 
							"Latitude Seconds Incorrect", "Date Error", 0);
						return 0;
					}
					lpEarthquakesDlgMem->fLatitudeSeconds = Value;
				   //-----------------------------------------
					GetDlgItemText(hDlg,IDC_EDIT_LOGNITUDE3, lognitudeSeconds, 12);
					rez = sscanf(lognitudeSeconds, "%f", &Value);
					if (rez != 1 || rez == EOF)
					{
						MessageBox(NULL, 
							"Latitude Seconds Incorrect", "Date Error", 0);
						return 0;
					}
					lpEarthquakesDlgMem->fLognitudeSeconds = Value;
				   //-----------------------------------------
					int nValue = SendDlgItemMessage( hDlg, 
						IDC_COMBO_LATITUDE, CB_GETCURSEL,0,(LPARAM)0 );
					switch (nValue)
					{
					case 0:
						lpEarthquakesDlgMem->LatitudeSign = 1;
						break;
					case 1:
						lpEarthquakesDlgMem->LatitudeSign = -1;
						break;
					default:
						MessageBox(NULL, 
#ifdef USE_RUSSIAN_LANG
							"Выберите северную или южную широту", "Date Error", 0);
#else
							"Select north or south latitude", "Date Error", 0);
#endif
						return 0;
					}
				   //-----------------------------------------
				   //-----------------------------------------
					nValue = SendDlgItemMessage( hDlg, 
						IDC_COMBO_LOGNITUDE, CB_GETCURSEL,0,(LPARAM)0 );
					switch (nValue)
					{
					case 0:
						lpEarthquakesDlgMem->LognitudeSign = 1;
						break;
					case 1:
						lpEarthquakesDlgMem->LognitudeSign = -1;
						break;
					default:
						MessageBox(NULL, 
#ifdef USE_RUSSIAN_LANG
							"Выберите восточную или западную долготу", "Date Error", 0);
#else
							"Select east of west lognitude", "Date Error", 0);
#endif
						return 0;
					}
				   //-----------------------------------------
					lpEarthquakesDlgMem->LatitudeOfResearchPoint = 
						double(lpEarthquakesDlgMem->LatitudeSign) * (
						double(lpEarthquakesDlgMem->wLatitudeDegrees) +
						double(lpEarthquakesDlgMem->wLatitudeMinutes) / 60. + 
						double(lpEarthquakesDlgMem->fLatitudeSeconds) / 3600.);

					lpEarthquakesDlgMem->LognitudeOfResearchPoint = 
						double(lpEarthquakesDlgMem->LognitudeSign) * (
						double(lpEarthquakesDlgMem->wLognitudeDegrees) +
						double(lpEarthquakesDlgMem->wLognitudeMinutes) / 60. + 
						double(lpEarthquakesDlgMem->fLognitudeSeconds) / 3600.);
				//-----------------------------------------
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				wValue = 
					(WORD)GetDlgItemInt(hDlg, 
					IDC_EDIT_NEAR_R, 
					&bTranslated, false);

				if (!bTranslated)
				{
					MessageBox(NULL, 
						"Incorrect Near R", "Date Error", 0);
					return 0;
				}
				lpEarthquakesDlgMem->near_r = double(wValue);
				   //-----------------------------------------
					GetDlgItemText(hDlg,IDC_EDIT_MAGNITUDE_BORDER, latitudeSeconds, 12);
					rez = sscanf(latitudeSeconds, "%f", &Value);
					if (rez != 1 || rez == EOF)
					{
						MessageBox(NULL, 
							"MAGNITUDE BORDER Incorrect", "Date Error", 0);
						return 0;
					}
					lpEarthquakesDlgMem->magnitudeBorder = Value;
				   //-----------------------------------------
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				wValue = 
					(WORD)GetDlgItemInt(hDlg, 
					IDC_EDIT_DEPTH_INTERVAL_MIN, 
					&bTranslated, false);

				if (!bTranslated)
				{
					MessageBox(NULL, 
						"Incorrect DEPTH INTERVAL MIN", "Date Error", 0);
					return 0;
				}
				lpEarthquakesDlgMem->depthIntervalMin = double(wValue);

				wValue = 
					(WORD)GetDlgItemInt(hDlg, 
					IDC_EDIT_DEPTH_INTERVAL_MAX, 
					&bTranslated, false);

				if (!bTranslated)
				{
					MessageBox(NULL, 
						"Incorrect DEPTH INTERVAL MAX", "Date Error", 0);
					return 0;
				}
				lpEarthquakesDlgMem->depthIntervalMax = double(wValue);
			}
			break;
		case ID_INIT_GEOCOORDINATE_CONTROLS:
			{
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			 SetDlgItemInt(hDlg,IDC_EDIT_LATITUDE, lpEarthquakesDlgMem->wLatitudeDegrees, false);
			 SetDlgItemInt(hDlg,IDC_EDIT_LATITUDE2,  lpEarthquakesDlgMem->wLatitudeMinutes, false);
			 sprintf(latitudeSeconds,"%.04f", lpEarthquakesDlgMem->fLatitudeSeconds);
			 SetDlgItemText(hDlg,IDC_EDIT_LATITUDE3, latitudeSeconds);

			 SetDlgItemInt(hDlg,IDC_EDIT_LOGNITUDE, lpEarthquakesDlgMem->wLognitudeDegrees, false);
			 SetDlgItemInt(hDlg,IDC_EDIT_LOGNITUDE2, lpEarthquakesDlgMem->wLognitudeMinutes, false);
			 sprintf(lognitudeSeconds,"%.04f", lpEarthquakesDlgMem->fLognitudeSeconds);
			 SetDlgItemText(hDlg,IDC_EDIT_LOGNITUDE3, lognitudeSeconds);
			 if (lParam == 0)
			 {

		#ifdef USE_RUSSIAN_LANG
				 SendDlgItemMessage( hDlg, IDC_COMBO_LATITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Северной широты" );
				 SendDlgItemMessage( hDlg, IDC_COMBO_LATITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Южной широты" );
		#else
				 SendDlgItemMessage( hDlg, IDC_COMBO_LATITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Of north latitude" );
				 SendDlgItemMessage( hDlg, IDC_COMBO_LATITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Of south latitude" );
		#endif
			 }

			 if(lpEarthquakesDlgMem->LatitudeSign > 0)
				 SendDlgItemMessage( hDlg, IDC_COMBO_LATITUDE, CB_SETCURSEL, 0, (LPARAM)0 );
			 if(lpEarthquakesDlgMem->LatitudeSign < 0)
				 SendDlgItemMessage( hDlg, IDC_COMBO_LATITUDE, CB_SETCURSEL, 1, (LPARAM)0 );

			 if (lParam == 0)
			 {

		#ifdef USE_RUSSIAN_LANG
				 SendDlgItemMessage( hDlg, IDC_COMBO_LOGNITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Восточной долготы" );
				 SendDlgItemMessage( hDlg, IDC_COMBO_LOGNITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Западной долготы" );
		#else
				 SendDlgItemMessage( hDlg, IDC_COMBO_LOGNITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Of east lognitude" );
				 SendDlgItemMessage( hDlg, IDC_COMBO_LOGNITUDE, CB_ADDSTRING, 0,
							   (LPARAM)(LPCTSTR)"Of west lognitude" );
		#endif
			 }


			 if(lpEarthquakesDlgMem->LognitudeSign > 0)
				 SendDlgItemMessage( hDlg, IDC_COMBO_LOGNITUDE, CB_SETCURSEL, 0, (LPARAM)0 );
			 if(lpEarthquakesDlgMem->LognitudeSign < 0)
				 SendDlgItemMessage( hDlg, IDC_COMBO_LOGNITUDE, CB_SETCURSEL, 1, (LPARAM)0 );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;
		case IDOK :
			{
				SendMessage(hDlg, WM_COMMAND, ID_TEST_GEOCOORDINATE_CONTROLS, 0);
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				vDoc[0].SetEarthQuakesSkale(lpEarthquakesDlgMem->scaleModeX, 
					lpEarthquakesDlgMem->LatitudeOfResearchPoint, 
					lpEarthquakesDlgMem->LognitudeOfResearchPoint, 
					lpEarthquakesDlgMem->near_r,
					lpEarthquakesDlgMem->magnitudeBorder,
					lpEarthquakesDlgMem->depthIntervalMin,
					lpEarthquakesDlgMem->depthIntervalMax);
				vDoc[1].SetEarthQuakesSkale(lpEarthquakesDlgMem->scaleModeX, 
					lpEarthquakesDlgMem->LatitudeOfResearchPoint, 
					lpEarthquakesDlgMem->LognitudeOfResearchPoint, 
					lpEarthquakesDlgMem->near_r,
					lpEarthquakesDlgMem->magnitudeBorder,
					lpEarthquakesDlgMem->depthIntervalMin,
					lpEarthquakesDlgMem->depthIntervalMax);
				vDoc[2].SetEarthQuakesSkale(lpEarthquakesDlgMem->scaleModeX, 
					lpEarthquakesDlgMem->LatitudeOfResearchPoint, 
					lpEarthquakesDlgMem->LognitudeOfResearchPoint, 
					lpEarthquakesDlgMem->near_r,
					lpEarthquakesDlgMem->magnitudeBorder,
					lpEarthquakesDlgMem->depthIntervalMin,
					lpEarthquakesDlgMem->depthIntervalMax);

					SendMessage(lpEarthquakesDlgMem->hWnd,WM_COMMAND,ID_FILE_NEW,0);
					for (int i = 0; i<3; i++)
					{
						vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i],&rect);
						InvalidateRect(vhWndChild[i],&rect, true);
#endif
					}
			}
			break;
		case IDC_BUTTON_SAVE_EARTHQUAKES_PER_DAY:
			{
				SendMessage(hDlg, WM_COMMAND, ID_TEST_GEOCOORDINATE_CONTROLS, 0);
				vDoc[0].SaveEarthQuakesPerDay(lpEarthquakesDlgMem->hWnd);
			}
			break;			
		case IDC_BUTTON_SAVE_NEAR_EARTHQUAKES:
			{
				SendMessage(hDlg, WM_COMMAND, ID_TEST_GEOCOORDINATE_CONTROLS, 0);
				vDoc[0].SaveNearEarthQuakes(lpEarthquakesDlgMem->hWnd,
					lpEarthquakesDlgMem->LatitudeOfResearchPoint, 
					lpEarthquakesDlgMem->LognitudeOfResearchPoint, 
					lpEarthquakesDlgMem->near_r,
					lpEarthquakesDlgMem->magnitudeBorder,
					lpEarthquakesDlgMem->depthIntervalMin,
					lpEarthquakesDlgMem->depthIntervalMax);
			}
			break;			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}

LRESULT CALLBACK DlgProcPolyoty( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );


#include "../../kohonen/src/kohonendlg.h"
#include "PolyotyNnetDlg.h"
LRESULT CALLBACK DlgProcPolyotyForNNet( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPPOLYOTYFILEDLGDATA lpPolyotyDlgData;
	static vector<vector<double> >	* pvectors, 
									* pdrills;
	static vector<cut_of_line>		* pline_cutting_vector_sorted;
	static vector<string>			* pnames;
	static int ix,iy;
	static int n_profiles;
	static KohonenDlg * tvd = NULL;

	switch( uMsg )
		
	{
    case WM_INITDIALOG :
		{
#if 0
			ix = 0;
			iy = 1;
#else
			ix = 2;
			iy = 3;
#endif
			pvectors = new vector<vector<double> >;
			pdrills = new vector<vector<double> >;
			pline_cutting_vector_sorted = new vector<cut_of_line>;
			pnames = new vector<string>;

			lpPolyotyDlgData = (LPPOLYOTYFILEDLGDATA)lParam;
			importFileForNNet(lpPolyotyDlgData, pvectors, pnames);

			

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (int j = 3; j < 10; j++)
			{
				string s;s.resize(8);
				sprintf((char *) s.data(), "%d", j);
				SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)s.c_str());
/*				char s[8];;
				sprintf(s, "%d", j);
				SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)s);*/
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_SETCURSEL,
				0,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (size_t j = 0; j < pnames->size(); j++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)pnames->operator [](j).c_str());
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_SETCURSEL,
				0,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			// MessageBox(0, lpPolyotyDlgData->filename, "filename", 0);

			char buffer[16];
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (int i = 1; i < 5; i++)
				SendDlgItemMessage( hDlg, IDC_COMBO_N_SUM_PROFILES, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)itoa(2*i+1,buffer, 10));
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_N_SUM_PROFILES, CB_SETCURSEL,
				0,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		   LRESULT lResult = SendMessage(      // returns LRESULT in lResult 
			   (HWND) GetDlgItem( hDlg, IDC_SPIN_MOVING_AVERANGE),      // handle to destination control  
			   (UINT) UDM_SETBUDDY,      // message ID   
			   (WPARAM) GetDlgItem( hDlg, IDC_EDIT_MOVING_AVERANGE),      // = (WPARAM) (HWND) hwndBuddy; 
			   (LPARAM) 0      // = 0; not used, must be zero 
			   );  
		   //set the min and max range of the up/down or spin control
			SendMessage(
				// returns LRESULT in lResult 
				(HWND) GetDlgItem( hDlg, IDC_SPIN_MOVING_AVERANGE),      // handle to destination control
				(UINT) UDM_SETRANGE32,      // message ID  
				(WPARAM) 1,      // = (WPARAM) (int) iLow;  
				(LPARAM) 100      // = (LPARAM) (int) iHigh; 
				);  
			SendMessage(      // returns LRESULT in lResult   
				(HWND) GetDlgItem( hDlg, IDC_SPIN_MOVING_AVERANGE),      // handle to destination control    
				(UINT) UDM_SETPOS,      // message ID    
				(WPARAM) 0,      // = 0; not used, must be zero   
				(LPARAM) MAKELONG ((short) 5, 0)      // = (LPARAM) MAKELONG ((short) nPos, 0)
				);  
			SendMessage(hDlg, WM_COMMAND, IDC_BUTTON_SORT_PROFILES, 1);
		}
		break;
    case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_BUTTON_MOVING_AVERANGE:
			{

				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);
				//###########################################################

				int Cols = (*pvectors).size();
				int Len = (*pvectors)[ix].size();
				Vector<Vector<vdouble > > vvv;
				vvv.resize(Cols);
				for (int C = 0; C < Cols; C++)
				{
					vvv[C].resize(n_profiles);
				}
				// base length of moving averange
				BOOL lpTranslated;
				int ma_base = GetDlgItemInt(hDlg, IDC_EDIT_MOVING_AVERANGE, &lpTranslated, false);
				for (int j = 0; j < n_profiles; j++)
				{
					int len = (*pline_cutting_vector_sorted)[j].i_finish 
						- (*pline_cutting_vector_sorted)[j].i_start;

					for (int C = 0; C < Cols; C++)
					{
						vvv[C][j].resize(len - ma_base + 1, 0.0);
					}
					//##############################
					for(int i = 0; i < len - ma_base + 1; i++)
					{
						for (int b = 0; b < ma_base; b++)
						{
							for (int C = 0; C < Cols; C++)
							{
								vvv[C][j][i] += (*pvectors)[C][(*pline_cutting_vector_sorted)[j].i_start+i+b];
							}
						}
						for (int C = 0; C < Cols; C++)
						{
							vvv[C][j][i] /= ma_base;
						}
					}
					//##############################						
				}
#if USE_WINSURF
				for ( int C = iy + 1; C < Cols; C++)
				{
					WinSurf( 
						vvv[ix],  
						vvv[iy],  
						vvv[C]);
				}
#endif

				//==============================================
				TCHAR filter[] =     TEXT("Text database file (*.dat)\0*.dat\0")
									 TEXT("Text database file (*.txt)\0*.txt\0")
									 TEXT("All Files (*.*)\0*.*\0");
				TCHAR lpstrFile[512];

				sprintf(lpstrFile, "%s\\%s_ma%d", directory, lpPolyotyDlgData->filename, ma_base);
				DWORD nFilterIndex = 0;
				if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
				{
					FILE *stream;
					stream = fopen(lpstrFile,"wt");

					for (int j = 0; j < n_profiles; j++)
					{
						for(int i = 0; i < vvv[0][j].Length(); i++)
						{
							for( int C = 0; C < 2; C++)
							{
								fprintf(stream, "%d\t",	int(vvv[C][j][i]));
							}
							for(int C = 2; C < Cols; C++)
							{
								fprintf(stream, "%f\t",	vvv[C][j][i]);
							}
							fprintf(stream, "\n");
						}
					}
					fclose (stream);
				}
			}
			break;
		case IDC_BUTTON_VISUALISATION_OF_PROFILES2:
			{
				SendMessage(hDlg, WM_COMMAND, IDC_BUTTON_PROFILES_SUMMING, 1);
			}
			break;
		case IDC_BUTTON_VISUALISATION_OF_PROFILES3:
			{
#if USE_WINSURF
				WinSurf(*pline_cutting_vector_sorted, 
					ix,  
					iy,  
					(*pvectors));
#endif
			}
			break;
		case IDC_BUTTON_VISUALISATION_OF_PROFILES:
			{
#if USE_WINSURF
				for (int col = iy + 1; col < pvectors->size(); col++)
				{
					WinSurf(*pline_cutting_vector_sorted, 
						(*pvectors)[ix],  
						(*pvectors)[iy],  
						(*pvectors)[col]);
				}
#endif
			}
			break;
		case IDC_BUTTON_SORT_PROFILES:
			{
				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);
				//###########################################################
				int u, prof;
				vector<cut_of_line> line_cutting_vector;
				cut_of_line line_cutting;
				line_cutting.i_start = 0;

				if ((*pvectors)[0].size())
				{
					u = int((*pvectors)[0][0]);
					prof = int((*pvectors)[1][0]);
					int i = 0;
					for (; i < (*pvectors)[0].size(); i++)
					{
						if (					
							u != int((*pvectors)[0][i]) ||
							prof != int((*pvectors)[1][i]))
						{
							u = int((*pvectors)[0][i]);
							prof = int((*pvectors)[1][i]);
							//##############################
							//lines_break_indexes.push_back(i);
							line_cutting.i_finish = i;
							line_cutting_vector.push_back(line_cutting);
							line_cutting.i_start = i;
							//##############################
						}
					}
					//==============================================
					line_cutting.i_finish = i;
					line_cutting_vector.push_back(line_cutting);
					//==============================================
				}
				n_profiles = line_cutting_vector.size();
				//###########################################################
				//int Len = (*pvectors)[ix].size();
				vector<double> xmean, ymean;
				for (int j = 0; j < n_profiles; j++)
				{
					int len = line_cutting_vector[j].i_finish 
						- line_cutting_vector[j].i_start;

					vdouble x,y;						
					x.resize(len);
					y.resize(len);

					//##############################
					for(int i = 0, ii = line_cutting_vector[j].i_start; ii < line_cutting_vector[j].i_finish; i++, ii++)
					{
						x[i] = (*pvectors)[ix][ii];
						y[i] = (*pvectors)[iy][ii];
					}
					//##############################
					double 
						maxx = x.Max(),
						minx = x.Min(),
						maxy = y.Max(),
						miny = y.Min(),
						delta_x = maxx-minx,
						delta_y = maxy-miny;

					//##############################
					if (delta_x > delta_y) //may be y = const
					{
						ymean.push_back(y.Median());
					}
					else // may be x = const
					{
						xmean.push_back(x.Median());
					}
					//##############################
				}
				//###########################################################
				index_for_sort * ifs = new index_for_sort[n_profiles];
				if (xmean.size() > ymean.size())
				{
					for (int I = 0; I < n_profiles; I++)
					{
						ifs[I].i		= I;
						ifs[I].sort_val	= xmean[I];
					}	
				}
				else
				{
					for (int I = 0; I < n_profiles; I++)
					{
						ifs[I].i		= I;
						ifs[I].sort_val	= ymean[I];
					}	
				}
				qsort( (void *)ifs, (size_t)n_profiles, sizeof(index_for_sort), compare_index_for_sort );
				//###########################################################
				pline_cutting_vector_sorted->resize(0);
				for (int j = 0; j < n_profiles; j++)
				{
					pline_cutting_vector_sorted->push_back(line_cutting_vector[ifs[j].i]);
				}
				//###########################################################
				delete [] ifs;

			}
			break;
		case IDC_BUTTON_KOHONEN_INPUT2:
			{
				//###########################################################
				int Cols = (*pvectors).size();
				int nParameters = Cols - iy - 1;

				int Len = (*pvectors)[ix].size();


				Vector<vdouble> vx,vy;
				vx.resize(n_profiles);
				vy.resize(n_profiles);
				// складываем отрезки образы для классификации
				vector<vector<cut_of_line> > vv_line_cutting;
				//vector<cut_of_line> v_line_cutting;
				cut_of_line line_cutting;

				vv_line_cutting.resize(nParameters);

				int c = 0, col = iy + 1 + 3;
				nParameters = 0;
				int points_per_image = 3 + SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_GETCURSEL,0,(LPARAM)0 );

				col = SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_COLS_NAMES, CB_GETCURSEL,0,(LPARAM)0 );
				//for (int c = 0, col = iy + 1 + 3; c < 3 && col < Cols; c++, col++)
				{
					for (int j = 0; j < n_profiles; j++)
					{
						bool start = true;
						//##############################
						for(int i = 0, ii = (*pline_cutting_vector_sorted)[j].i_start;
							ii < (*pline_cutting_vector_sorted)[j].i_finish-1; i++, ii++)
						{
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							if 	(
								( (*pvectors)[col][ii] <= 0 && (*pvectors)[col][ii+1] >= 0.0 )
								||
								( (*pvectors)[col][ii] >= 0 && (*pvectors)[col][ii+1] <= 0.0 )
								)

							{
								if (start)
								{
									start = false;
									line_cutting.i_start = ii;
								}
								else
								{
									start = true;
									line_cutting.i_finish = ii+2;
									if (line_cutting.i_finish - line_cutting.i_start > points_per_image)
									{
//										v_line_cutting.push_back(line_cutting);
										vv_line_cutting[c].push_back(line_cutting);
									}
								}
							}
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						}
						//##############################
					}

					int nImages = vv_line_cutting[c].size();
					double * xIm = new double [nImages];
					double * yIm = new double [nImages];
					double * ImX = new double [nImages];
					double * ImY = new double [nImages];
					
					int nnetParameters = points_per_image;
					double **M = AllocDoubleMat(nImages, nnetParameters);

					for (int j = 0; j < nImages; j++)
					{
						//###################################################################
						int len = vv_line_cutting[c][j].i_finish - vv_line_cutting[c][j].i_start;

						xIm[j] = len;
						double * v = new double [len];
						double * X = new double [len];
						double * Y = new double [len];

						for (int i0 = 0, i = vv_line_cutting[c][j].i_start;
						i < vv_line_cutting[c][j].i_finish; i++, i0++)
						{
							v[i0] = (*pvectors)[col][i];
							X[i0] = (*pvectors)[ix][i];
							Y[i0] = (*pvectors)[iy][i];
						}
						//linterp(int nx, double* py, int nxx, double* pyy)
						linterp(len, v, nnetParameters, M[j]);
						Scale(nnetParameters, M[j]);

						double sum = 0;
						double sumX = 0;
						double sumY = 0;
						for (int i0 = 0; i0 < len; i0++)
						{
							sum  += v[i0];
							sumX += X[i0];
							sumY += Y[i0];
						}
						sum  /= len;
						sumX /= len;
						sumY /= len;

						yIm[j] = sum;
						ImX[j] = sumX;
						ImY[j] = sumY;

						delete [] v;
						delete [] X;
						delete [] Y;
					}
					//###################################################################

/*
					WinSurf(vv_line_cutting[c], 
						ix,  
						iy,  
						(*pvectors));
*/					
					if (tvd != NULL) delete tvd;		// how to safely release the memory...
//					tvd = new KohonenDlg(nImages, ImX, ImY, xIm, yIm);		// ...right after the dialog is closed?
//					tvd = new KohonenDlg(nImages, ImX, ImY, 1, &xIm);		// ...right after the dialog is closed?
					tvd = new KohonenDlg(nImages, ImX, ImY, NULL, nnetParameters, M, pnames->operator [](col));		// ...right after the dialog is closed?
					delete [] xIm;
					delete [] yIm;
					delete [] ImX;
					delete [] ImY;
					FreeDoubleMat(M);
				}
			}
			break;

		case IDC_BUTTON_KOHONEN_INPUT:
			{
				//###########################################################
				int Cols = (*pvectors).size();
				int nParameters = Cols - iy - 1;

				int Len = (*pvectors)[ix].size();
				int points_per_image = 3 + SendDlgItemMessage( hDlg, IDC_COMBO_POLYOTY_KOHONEN_NPOINTS, CB_GETCURSEL,0,(LPARAM)0 );


				Vector<vdouble> vx,vy;
				vx.resize(n_profiles);
				vy.resize(n_profiles);
				// складываем отрезки образы для классификации
				vector<vector<cut_of_line> > vv_line_cutting;
				vector<cut_of_line> v_line_cutting;
				cut_of_line line_cutting;

				vv_line_cutting.resize(nParameters);
					for (int j = 0; j < n_profiles; j++)
					{
						bool start = true;
						//##############################
						for(int i = 0, ii = (*pline_cutting_vector_sorted)[j].i_start;
							ii < (*pline_cutting_vector_sorted)[j].i_finish-1; i++, ii++)
						{

				for (int c = 0, col = iy + 1 + 3; c < 3 && col < Cols; c++, col++)
				{

							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							if 	(
								( (*pvectors)[col][ii] <= 0 && (*pvectors)[col][ii+1] >= 0.0 )
								||
								( (*pvectors)[col][ii] >= 0 && (*pvectors)[col][ii+1] <= 0.0 )
								)

							{
								if (start)
								{
									start = false;
									line_cutting.i_start = ii;
								}
								else
								{
									start = true;
									line_cutting.i_finish = ii+2;
									if (line_cutting.i_finish - line_cutting.i_start > points_per_image)
									{
										v_line_cutting.push_back(line_cutting);
										vv_line_cutting[c].push_back(line_cutting);
									}
								}
							}
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						}
						//##############################
					}
				}
					
					

#if 0
				WinSurf(v_line_cutting, 
					ix,  
					iy,  
					(*pvectors));
#endif
				// число образов
				int nImages = v_line_cutting.size();
				double * xIm = new double [nImages];
				double * yIm = new double [nImages];
				double * ImX = new double [nImages];
				double * ImY = new double [nImages];
				
				nParameters = 1;
					int nnetParameters = points_per_image;
					double **M = AllocDoubleMat(nImages, nnetParameters*3);

				string name;

				for (int j = 0; j < nImages; j++)
				{
					//###################################################################
//					int col = iy + 1 + 3;
					for (int c = 0, col = iy + 1 + 3; c < 3 && col < Cols; c++, col++)
//					for (int col = iy + 1; col < cols; col++)
					{
						int len = v_line_cutting[j].i_finish - v_line_cutting[j].i_start;

						xIm[j] = len;
						double * v = new double [len];
						double * X = new double [len];
						double * Y = new double [len];

						for (int i0 = 0, i = v_line_cutting[j].i_start;
						i < v_line_cutting[j].i_finish; i++, i0++)
						{
							v[i0] = (*pvectors)[col][i];
							X[i0] = (*pvectors)[ix][i];
							Y[i0] = (*pvectors)[iy][i];
						}
						//
						linterp(len, v, nnetParameters, &M[j][c*nnetParameters]);
						Scale(nnetParameters, &M[j][c*nnetParameters]);
						double sum = 0;
						double sumX = 0;
						double sumY = 0;
						for (int i0 = 0; i0 < len; i0++)
						{
							sum  += v[i0];
							sumX += X[i0];
							sumY += Y[i0];
						}
						sum  /= len;
						sumX /= len;
						sumY /= len;

						yIm[j] = sum;
						ImX[j] = sumX;
						ImY[j] = sumY;

						delete [] v;
						delete [] X;
						delete [] Y;
						if (j == 0)
						{
							name += pnames->operator [](col);
							if(c != 2) name += "_";
						}
					}
					//###################################################################
				}
				MessageBox(0, name.c_str(), "", 0);
				{

					
					if (tvd != NULL) delete tvd;		// how to safely release the memory...
//					tvd = new KohonenDlg(nImages, ImX, ImY, xIm, yIm);		// ...right after the dialog is closed?
//					tvd = new KohonenDlg(nImages, ImX, ImY, nParameters, &xIm);		// ...right after the dialog is closed?
					tvd = new KohonenDlg(nImages, ImX, ImY, NULL, 3*nnetParameters, M, name);		// ...right after the dialog is closed?
//					tvd = new KohonenDlg(nImages, ImX, ImY, 3, M, name);		// ...right after the dialog is closed?
				}
				delete [] xIm;
				delete [] yIm;
				delete [] ImX;
				delete [] ImY;
				FreeDoubleMat(M);
			}
			break;
		case IDC_BUTTON1:
			{
				int clusters = 8;     // This many clusters.
				int points = 10;      // Number of points in each cluster.
				// число образов
				int nImages = clusters*points;
				double * xIm = new double [nImages];
				double * yIm = new double [nImages];
				double * ImX = new double [nImages];
				double * ImY = new double [nImages];
				
				int nnetParameters = 10;
				double **M = AllocDoubleMat(nImages, nnetParameters);
				double **C = AllocDoubleMat(clusters, nnetParameters);
				for ( int c = 0; c < clusters; c++)
				{
					for ( int par = 0; par < nnetParameters; par++)
					{
						C[c][par] = Rand(0,1);
					}
				}
				for (int c = 0; c < clusters; c++)
				{
					for ( int par = 0; par < nnetParameters; par++)
					{
						for(int p = 0; p < points; p++)
						{
							M[c*points + p][par] =  C[c][par] + Rand(0.1);
						}
					}
				}
				if (tvd != NULL) delete tvd;		// how to safely release the memory...
				tvd = new KohonenDlg(nImages, ImX, ImY, NULL, nnetParameters, M);		// ...right after the dialog is closed?
				return 0;
				delete [] xIm;
				delete [] yIm;
				delete [] ImX;
				delete [] ImY;
				FreeDoubleMat(M);
				FreeDoubleMat(C);
			}
			break;
		case IDC_BUTTON_PROFILES_SUMMING:
			{

				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);
				//###########################################################
				int Cols = (*pvectors).size();

				int Len = (*pvectors)[ix].size();
				int N = 1+2*(1+SendDlgItemMessage( hDlg, IDC_COMBO_N_SUM_PROFILES, CB_GETCURSEL,0,(LPARAM)0 ));

				Vector<Vector<Vector<double> > > vv;
				vv.resize(n_profiles-N+1);

				for (int J = 0; J < n_profiles-N+1; J++)
				{
						Vector<vdouble> vx,vy;
						vx.resize(2*N);
						vy.resize(2*N);


						int SumLen = 0;
						int u_middle, prof_middle;
						//##############################
						//int i0 = I0;
						for (int j = J, n = 0; j < J+N; j++, n++)
						{
								if (j-J == N/2)
								{
									u_middle	= int ((*pvectors)[0][(*pline_cutting_vector_sorted)[j].i_start]);
									prof_middle = int ((*pvectors)[1][(*pline_cutting_vector_sorted)[j].i_start]);
								}
								int len = (*pline_cutting_vector_sorted)[j].i_finish 
									- (*pline_cutting_vector_sorted)[j].i_start;

								SumLen += len;
								
								vx[n].resize(len);
								vy[n].resize(len);


								//##############################
								for(int i = 0, ii = (*pline_cutting_vector_sorted)[j].i_start; ii < (*pline_cutting_vector_sorted)[j].i_finish; i++, ii++)
								{
									vx[n][i] = (*pvectors)[ix][ii];
									vy[n][i] = (*pvectors)[iy][ii];
								}
								//##############################
								double 
									maxx = vx[n].Max(),
									minx = vx[n].Min(),
									maxy = vy[n].Max(),
									miny = vy[n].Min(),
									delta_x = maxx-minx,
									delta_y = maxy-miny;

								vx[n+N].resize(2);
								vy[n+N].resize(2);

								//##############################
								if (delta_x > delta_y) //may be y = const
								{
									vx[n+N][0] = minx;
									vy[n+N][0] = vy[n].Median();
									vx[n+N][1] = maxx;
									vy[n+N][1] = vy[n+N][0];
								}
								else // may be x = const
								{
									vy[n+N][0] = miny;
									vx[n+N][0] = vx[n].Median();
									vy[n+N][1] = maxy;
									vx[n+N][1] = vx[n+N][0];
								}
								//##############################
						}
						if (lParam == 1)
						{
							WinPlot(vx,vy);
						}
						else
						{
							vv[J].resize( SumLen );
							int I = 0;
							for (; I < SumLen; I++)
							{
								vv[J][I].resize( Cols );
							}
							//##############################
							I = 0;
							for (int j = J, n = 0; j < J+N; j++, n++)
							{
								int len = (*pline_cutting_vector_sorted)[j].i_finish 
									- (*pline_cutting_vector_sorted)[j].i_start;
									
								vx[n].resize(len);
								vy[n].resize(len);


								//##############################
								for(int ii = (*pline_cutting_vector_sorted)[j].i_start; ii < (*pline_cutting_vector_sorted)[j].i_finish; ii++)
								//for(int i = 0; i < len; i++)
								{
									for( int C = 0; C < Cols; C++)
										vv[J][I][C] = (*pvectors)[C][ii];
									//##############################
									vv[J][I][0]		= u_middle;
									vv[J][I][1]		= prof_middle;
									// X as median of middle profile
									vv[J][I][ix]	= vx[N+N/2][0];
									//##############################
									I++;
								}
								//##############################
							}
						}
						//##############################
				}
				if(lParam != 1)
				{
					TCHAR filter[] =     TEXT("Text database file (*.dat)\0*.dat\0")
										 TEXT("Text database file (*.txt)\0*.txt\0")
										 TEXT("All Files (*.*)\0*.*\0");
					TCHAR lpstrFile[512];

					sprintf(lpstrFile, "%s\\%s_sum%dprof", directory, lpPolyotyDlgData->filename, N);
					DWORD nFilterIndex = 0;
					if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
					{
						FILE *stream;
						stream = fopen(lpstrFile,"wt");

						for (int J = 0; J < n_profiles-N+1; J++)
						{
							int length = vv[J].Size();
							index_for_sort * ifs = new index_for_sort[length];
							for (int I = 0; I < length; I++)
							{
								ifs[I].i		= I;
								ifs[I].sort_val	= vv[J][I][iy];
							}					
							qsort( (void *)ifs, (size_t)length, sizeof(index_for_sort), compare_index_for_sort );
							for (int I = 0; I < length; I++)
							{
								for( int C = 0; C < 2; C++)
								{
									fprintf(stream, "%d\t",	int(vv[J][ifs[I].i][C]));
								}
								for( int C = 2; C < Cols; C++)
								{
									fprintf(stream, "%f\t",	vv[J][ifs[I].i][C]);
								}
								fprintf(stream, "\n");
							}
							delete[] ifs;
						}
						fclose (stream);
					}
				}
				break;
#if 0
				int i0 = 0;
				for (int j = 0; j < lines_break_indexes.size(); j++)
				{
					if (lines_break_indexes[j] < Len)
					{
						int len = lines_break_indexes[j] - i0;
						vdouble x,y;
						x.resize(len);
						y.resize(len);

						//##############################
						for(int i = 0; i < len; i++)
						{
							y[i] = (*pvectors)[iy][i0+i];
							x[i] = (*pvectors)[ix][i0+i];
						}
						i0 = lines_break_indexes[j];
						//##############################

						double 
							maxx = x.Max(),
							minx = x.Min(),
							maxy = y.Max(),
							miny = y.Min(),
							delta_x = maxx-minx,
							delta_y = maxy-miny;

						vdouble M;
						vdouble v;
						vdouble k;
						M.resize(len,2);
						v.resize(len);
						vdouble X,Y;
						X.resize(2);
						Y.resize(2);

						//##############################
						if (delta_x > delta_y) //may be y = const
						{
#if 0
							for(int i = 0; i < len; i++)
							{
								M(i,0) = x[i];
								M(i,1) = 1.0;
								v[i] =  y[i];
							}
							k = M.Tichonov(v, true);

							// Y = k[0] * X + k[1];
							X[0] = minx;
							Y[0] = k[0] * X[0] + k[1];
							X[1] = maxx;
							Y[1] = k[0] * X[1] + k[1];
#endif
							X[0] = minx;
							Y[0] = y.Median();
							X[1] = maxx;
							Y[1] = Y[0];
						}
						else // may be x = const
						{
#if 0
							for(int i = 0; i < len; i++)
							{
								M(i,0) = y[i];
								M(i,1) = 1.0;
								v[i] =  x[i];
							}
							k = M.Tichonov(v, true);
							// X = k[0] * Y + k[1];
							Y[0] = miny;
							X[0] = k[0] * Y[0] + k[1];
							Y[1] = maxy;
							X[1] = k[0] * Y[1] + k[1];
#endif
							Y[0] = miny;
							X[0] = x.Median();
							Y[1] = maxy;
							X[1] = X[0];
						}
						//##############################
						Vector<vdouble> vx,vy;
						vx.resize(2);
						vy.resize(2);
						vx[0].resize(len);
						vy[0].resize(len);
						for( i = 0; i < len; i++)
						{
							vx[0][i] = x[i];
							vy[0][i] = y[i];
						}
						vx[1].resize(2);
						vy[1].resize(2);
						for( i = 0; i < 2; i++)
						{
							vx[1][i] = X[i];
							vy[1][i] = Y[i];
						}

						WinPlot(vx,vy);

						
					}
				}

				break;


				if (OpenFileDlg(hDlg, "drills\0*.*\0Text\0*.TXT\0") == S_OK)
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY), hDlg,
						(DLGPROC)DlgProcPolyoty,(LPARAM)lpPolyotyDlgData);

				importFileForNNet(lpPolyotyDlgData, pdrills);

				int ndril_colls = (*pdrills).size();
				if (ndril_colls == 0)
				{
					MessageBox(0,"ndril_colls == 0","",0);
					return 0;
				}
#if 0
				int ixd = 2;
				int iyd = 3;
#else
				int ixd = 1;
				int iyd = 2;
#endif



				//======================================================
				//======================================================
				//======================================================
				DelaunayTriangulation dct;
				// Delaunay Triangulation of well coordinates
				dct.main((*pdrills)[ixd],(*pdrills)[iyd]);
				//======================================================
				//======================================================
				//======================================================
#endif
			}
			break;			
		case IDOK :
			{
				WinPlot( (*pvectors)[ix],  (*pvectors)[iy]);

				if (OpenFileDlg(hDlg, "drills\0*.*\0Text\0*.TXT\0") == S_OK)
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY), hDlg,
						(DLGPROC)DlgProcPolyoty,(LPARAM)lpPolyotyDlgData);

				importFileForNNet(lpPolyotyDlgData, pdrills, pnames);

				int ndril_colls = (*pdrills).size();
				if (ndril_colls == 0)
				{
					MessageBox(0,"ndril_colls == 0","",0);
					return 0;
				}
				TCHAR lpstrFile[256];
				TCHAR filter[] = 
					//TEXT("Golden Software Blanking (*.bln) (*.bln)\0*.bln\0")									 
					TEXT("Golden Software Data (*.dat)\0*.dat\0")									
					TEXT("All Files (*.*)\0*.*\0");
				sprintf(lpstrFile, "%s\\NnetInput.dat", directory);
				DWORD nFilterIndex = 0;
				if (SaveFileDlg(hDlg, lpstrFile, filter, nFilterIndex) != S_OK)
					return 0;
				MessageBox(0, lpstrFile, "", 0);

				FILE *stream;
				stream = fopen(lpstrFile,"wt");
				char delim = '\t';


				int ndrills = (*pdrills)[0].size();

				double //the arm of square
					deltaX = 2500,
					deltaY = 2500,
					deltaX2 = deltaX+500,
					deltaY2 = deltaY+500;
				//==============================================================
				//==============================================================
				//==============================================================
				//==============================================================
				RECT rcClient;  // Client area of parent window 
				int cyVScroll;  // Height of scroll bar arrow 
				HWND hwndPB;    // Handle of progress bar 
				DWORD cb,		// Size of file and count of
				  cb_read = 0,  // bytes read 
				  cb_disp = 0;  // bytes displayed



				// Ensure that the common control DLL is loaded
				// and create a progress bar along the bottom of
				// the client area of the parent window. 
				// Base the height of the progress bar on the
				// height of a scroll bar arrow. 
				InitCommonControls(); 
				GetClientRect(lpPolyotyDlgData->hWnd, &rcClient); 
				GetWindowRect(lpPolyotyDlgData->hWnd, &rcClient); 
				cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
				hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
						 (LPSTR) NULL, 
						 //WS_CHILD | WS_VISIBLE,
						 WS_POPUPWINDOW,
						 //0, 0,
						 rcClient.left, rcClient.bottom-2*cyVScroll,
						 rcClient.right, cyVScroll, 
						 //hwndParent, 
						 NULL,
						 
						 (HMENU) 0, hInst, NULL); 

				ShowWindow(hwndPB,1);

				// Gets the file descriptor associated with a stream.
				//int fd = _fileno(stream);
				// Get the length of a file in bytes
				cb = ndrills;


				// Set the range and increment of the progress
				// bar. 

				SendMessage(hwndPB, PBM_SETRANGE, 0,
							MAKELPARAM(0, cb)); 
				SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
				//==============================================================
				//==============================================================
				//==============================================================
				//==============================================================

				// number of polyot profiles
				int len = (*pvectors)[ix].size();

				COORDINATES * pxyz = new COORDINATES[len];
				// цикл по каждой точке в файле полётов
				for (int i = 0; i < len; i++)
				{
					double 
						xi = (*pvectors)[ix][i],
						yi = (*pvectors)[iy][i],
						zi = 0.0;

						// заносим в массив точки, 
						pxyz[i].x = xi;
						pxyz[i].y = yi;
						pxyz[i].z = zi;
				}
				qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
				qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );
				//==============================================================
				//==============================================================
				//==============================================================
				//==============================================================

				//цикл по каждой скважине

				for (int ndrill = 0; ndrill < ndrills; ndrill++)
				{
#if 0
					int ixd = 2;
					int iyd = 3;
#else
					int ixd = 1;
					int iyd = 2;
#endif

					int ifirst_sloj = 7, ilast_sloj = 16;

					double X,Y; // coordinates of current drill

					X = (*pdrills)[ixd][ndrill];
					Y = (*pdrills)[iyd][ndrill];

					char str[255];
					sprintf(str, "%d X = %f Y = %f", ndrill, X,Y);
					//MessageBox(0, str, "", 0);

					// цикл интерполяции на сетку квадрата каждого параметра приборов
					// цикл по параметрам

#if 0
					//for (int col = iy + 1+3; col < pvectors->Size(); col++)
					for (int col = iy + 1; col < pvectors->Size(); col++)
#else
					for (int col = iy + 1 + 3; col < iy + 1 + 6 && col < pvectors->size(); col++)
#endif
					{

						//==============================================================
						//==============================================================
						//==============================================================
						//==============================================================
						//sortrows21(x, y, z);
						// цикл по каждой точке в файле полётов
						int j = 0;						
						for (int i = 0; i < len; i++)
						{
							double 
								xi = (*pvectors)[ix][i],
								yi = (*pvectors)[iy][i],
								zi = (*pvectors)[col][i];

							// заносим в массив только те точки, 
							// которые попадают в квадрат
							if (xi > X - deltaX2 && xi < X + deltaX2 &&
								yi > Y - deltaY2 && yi < Y + deltaY2)
							{
								pxyz[j].x = xi;
								pxyz[j].y = yi;
								pxyz[j].z = zi;
								j++;
							}
						}

						int fact_len = j;

						
						// массив фактических точек измерения внутри квадрата
						vector<double> xx,yy,zz;

						xx.resize(fact_len);
						yy.resize(fact_len);
						zz.resize(fact_len);

						//qsort( (void *)pxyz, (size_t)fact_len, sizeof(COORDINATES), compare_Y );
						//qsort( (void *)pxyz, (size_t)fact_len, sizeof(COORDINATES), compare_X );

						//заполняем точки измерения внутри квадрата
						for (int i = 0; i < fact_len; i++)
						{
							xx[i] = pxyz[i].x;
							yy[i] = pxyz[i].y;
							zz[i] = pxyz[i].z;
						}
						//==============================================================
						//==============================================================
						//==============================================================
						//==============================================================
						/*double xmin = (*pvectors)[ix].Min();
						double ymin = (*pvectors)[iy].Min();
						double xmax = (*pvectors)[ix].Max();
						double ymax = (*pvectors)[iy].Max();*/
#define GRIDDATA 1
#if GRIDDATA
						// формируем равномерную сетку квадрата

						double xmin = X - deltaX;
						double ymin = Y - deltaY;
						double xmax = X + deltaX;
						double ymax = Y + deltaY;

						// длиной шириной

						long 
							lenx = 9,
							leny = 9;

						// интерполируем измерения на равномерный квадрат
						vdouble xi,yi,zi;
						xi = dsequence(double(xmin), long(lenx), double(xmax));
						yi = dsequence(double(ymin), long(leny), double(ymax));
						zi.resize(xi.Length(), yi.Length(), 0.0 );
						if (griddata (lpPolyotyDlgData->hWnd,
							xx, 
							yy,
							zz,
							NULL, &xi, &yi, &zi) != 0)
						{
							MessageBox(0, "Error: griddata fault", "", 0);
							break;
						}
						//WinSurf(xi,yi,zi);
						for(j = 0; j < zi.Length(); j++)
						{
							fprintf(stream, "%f%c", zi[j],delim);
						}
#endif /*GRIDDATA*/


					}// конец цила по параметрам прибора
					for (int isloj = ifirst_sloj; isloj <= ilast_sloj; isloj++)
					{
						double Altitude_of_sloj  = (*pdrills)[isloj][ndrill];
						sprintf(str, "%d Altitude_of_sloj(%d) = %f",ndrill, isloj, Altitude_of_sloj);
						//MessageBox(0, str, "", 0);

						fprintf(stream, "%f%c", Altitude_of_sloj,delim);

					}
					fprintf(stream, "\n");
					SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
		
				}//конец цикла по каждой скважине
				delete[] pxyz;
				fclose(stream);
				DestroyWindow(hwndPB);
			}
			break;
		case IDCANCEL :
			{
				hDlgModeless = NULL;
				EndDialog( hDlg, IDCANCEL );
			}
			break;
		}
		break;
		case WM_DESTROY :
			{
//				if (tvd != NULL) delete tvd;		// how to safely release the memory...
				if (pvectors) delete pvectors;
				if (pdrills) delete pdrills;
				if (pline_cutting_vector_sorted) delete pline_cutting_vector_sorted;
			}
			break;
		default :
			return( FALSE );
	}
	return( TRUE );
}









LRESULT CALLBACK DlgProcPolyoty( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	const int n=4096*32; // length of buffer string line
	static char *szBuff; // buffer string line
	static char *szLine1; // buffer string line
	static char *szLineEnd; // buffer string line

	static LPPOLYOTYFILEDLGDATA lpPolyotyDlgData;
 	char startDate[15],
		finishDate[15];
	static PolyotyNnetDlg * tvd;
 switch( uMsg )
  {
    case WM_INITDIALOG :
		{
			lpPolyotyDlgData = (LPPOLYOTYFILEDLGDATA)lParam;
			szBuff		= new char[n]; // buffer string line
			szLine1		= new char[n]; // buffer string line
			szLineEnd	= new char[n]; // buffer string line

			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			InitTimeFormatComboBox(hDlg, IDC_COMBO_TIME_FORMAT);
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			/*SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"excel time: in days since 1.1.1900");
			SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"matlab time: in days since 1.1.0001");
			SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"unix time: in secs since 1.1.1970");
			SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"db time: yyyy-mm-dd hh:mm:ss");*/
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_SETCURSEL,
				lpPolyotyDlgData->timeFormat,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"tabulation");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"space");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)",");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)";");
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_SETCURSEL,
				lpPolyotyDlgData->delimID,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						
			CheckDlgButton( hDlg, IDC_CHECK_USE_T1,
				lpPolyotyDlgData->bUse_t1 ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_USE_T2,
				lpPolyotyDlgData->bUse_t2 ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME,
				lpPolyotyDlgData->thisIsLocalTime ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_NOT_ADD_TO_EXISTING_PLOTS,
				lpPolyotyDlgData->notAddToExistingPlots ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_USE_ALL_COLS,
				lpPolyotyDlgData->bUseAllCols ? BST_CHECKED : BST_UNCHECKED );



			

			

			lpPolyotyDlgData->bUseStartFinishDate	= false;
			//
			//lpPolyotyDlgData->bUseIndexedTimeScale	= false;
			lpPolyotyDlgData->bUseIndexedTimeScale	= true;
			//
			//lpPolyotyDlgData->bDispOn3docs			= true;
			lpPolyotyDlgData->bDispOn3docs			= false;
			lpPolyotyDlgData->bIgnoreFirstLines		= false; 
			lpPolyotyDlgData->nLinesToIgnore		=	0;
			lpPolyotyDlgData->bUse_Header			= true;
			//
			//lpPolyotyDlgData->bUse_timeFormat		= true;
			lpPolyotyDlgData->bUse_timeFormat		= false;

			CheckDlgButton( hDlg, IDC_CHECK_USE_TIME_FORMAT,
				lpPolyotyDlgData->bUse_timeFormat ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_USE_HEADER,
				lpPolyotyDlgData->bUse_Header ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_USE_START_FINISH_DATE,
				lpPolyotyDlgData->bUseStartFinishDate ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_USE_INDEXED_TIME_SCALE,
				lpPolyotyDlgData->bUseIndexedTimeScale ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_DISP_ON_3_DOCS,
				lpPolyotyDlgData->bDispOn3docs ? BST_CHECKED : BST_UNCHECKED );

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_LIST_POLYOTY,0);
		}
		break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
		 case IDC_BUTTON_N_LINES_TO_IGNORE:
			 {
				   if(lpPolyotyDlgData->bIgnoreFirstLines)
				   {
						// 
						BOOL bTranslated;
						lpPolyotyDlgData->nLinesToIgnore = 
							(short)GetDlgItemInt(hDlg, IDC_EDIT_N_LINES_TO_IGNORE, &bTranslated, false);
						if (!bTranslated)
							lpPolyotyDlgData->nLinesToIgnore = 0;

						SendMessage(hDlg,WM_COMMAND,IDC_INIT_LIST_POLYOTY,0);
				   }
			 }
			 break;
		 case IDC_INIT_LIST_POLYOTY:
			 {
				SendDlgItemMessage( hDlg, IDC_LIST_POLYOTY, LB_RESETCONTENT, 0,0);
				FILE *stream;
				if ((stream = fopen(
					//lpPolyotyDlgData->szSelectFileDlgName,
					szPath,
					"rt")) == NULL)
				{
					MessageBox(0, szPath, "Cannot open input file.Import", 
						MB_OK | MB_ICONINFORMATION);
					return 0;
				}

				RECT rcClient;  // Client area of parent window 
				int cyVScroll;  // Height of scroll bar arrow 
				HWND hwndPB;    // Handle of progress bar 
				DWORD cb,		// Size of file and count of
				  cb_read = 0,  // bytes read 
				  cb_disp = 0;  // bytes displayed



				// Ensure that the common control DLL is loaded
				// and create a progress bar along the bottom of
				// the client area of the parent window. 
				// Base the height of the progress bar on the
				// height of a scroll bar arrow. 
				InitCommonControls(); 
				GetClientRect(lpPolyotyDlgData->hWnd, &rcClient); 
				cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
				hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
						 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
						 0, 0,
						 //rcClient.left, rcClient.bottom,
						 rcClient.right, cyVScroll, 
						 lpPolyotyDlgData->hWnd, (HMENU) 0, hInst, NULL); 

				// Gets the file descriptor associated with a stream.
				int fd = _fileno(stream);
				// Get the length of a file in bytes
				cb = _filelength(fd);



				// Set the range and increment of the progress
				// bar. 

				SendMessage(hwndPB, PBM_SETRANGE, 0,
							MAKELPARAM(0, cb / 2048)); 
				SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 

				// read and ignore first nLinesToIgnore lines
				int line = 0;
				while (lpPolyotyDlgData->bIgnoreFirstLines && line < lpPolyotyDlgData->nLinesToIgnore && !feof(stream))
				{
					char * ch;
					ch = fgets(szBuff,n,stream);
					if( ch != NULL)
					{
						line ++;
					}
				}

				int nParams = 0, bytes_line;
				// if first line is line of headers
				if (!feof(stream))
				{
					char * ch;
					ch = fgets(szBuff,n,stream);
					if( ch != NULL && strlen(szBuff) > 1)
					{
						bytes_line = strlen(ch);

						// calculate progress
						cb_read += bytes_line;
						if (cb_read - cb_disp > 2048) 
						{
						   // Advance the current position of the
						   // progress bar by the increment. 
							int todisp = (cb_read - cb_disp) / 2048;
							cb_disp += todisp*2048;
							for (int idisp = 0; idisp < todisp; idisp++)
								SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
						}
						SendDlgItemMessage( hDlg, IDC_LIST_POLYOTY, LB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)szBuff);
						/*bytes = strlen(ch);*/
					}
				}
				//const int to_display_in_list = 32768;
				const int to_display_in_list = 128;
				// scan all lines to know length of file
				int len = 0;
				while (!feof(stream))
				{
					char * ch;
					ch = fgets(szBuff,n,stream);
					if( ch != NULL && strlen(szBuff) > 1)
					{
						bytes_line = strlen(ch);

						// calculate progress
						cb_read += bytes_line;
						if (cb_read - cb_disp > 2048) 
						{
						   // Advance the current position of the
						   // progress bar by the increment. 
							int todisp = (cb_read - cb_disp) / 2048;
							cb_disp += todisp*2048;
							for (int idisp = 0; idisp < todisp; idisp++)
								SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
						}
						if (len < to_display_in_list)
							SendDlgItemMessage( hDlg, IDC_LIST_POLYOTY, LB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)szBuff);
						if (len == 0)
						{
							strcpy(szLine1, szBuff);
						}
						else
							strcpy(szLineEnd, szBuff);

						len++;
					}
				}
				if(len >= to_display_in_list)
					MessageBox(0,"Файл изображён не полностью\nТем не менее он будет полностью загружен", "", 0);

				fclose(stream);
				DestroyWindow(hwndPB);
			 }
			 break;
		 case IDC_CHECK_USE_HEADER:
			 {
				 lpPolyotyDlgData->bUse_Header = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_HEADER) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_USE_TIME_FORMAT:
			 {
				 lpPolyotyDlgData->bUse_timeFormat = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_TIME_FORMAT) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_USE_T2:
			 {
				 lpPolyotyDlgData->bUse_t2 = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_T2) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_USE_T1:
			 {
				 lpPolyotyDlgData->bUse_t1 = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_T1) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_DISP_ON_3_DOCS:
			 {
				lpPolyotyDlgData->bDispOn3docs = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_DISP_ON_3_DOCS) 
					== BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_NOT_ADD_TO_EXISTING_PLOTS:
			 {
				lpPolyotyDlgData->notAddToExistingPlots = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_NOT_ADD_TO_EXISTING_PLOTS) 
					== BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_USE_INDEXED_TIME_SCALE:
			 {
				lpPolyotyDlgData->bUseIndexedTimeScale = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_USE_INDEXED_TIME_SCALE) 
					== BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_USE_START_FINISH_DATE:
			 {
				lpPolyotyDlgData->bUseStartFinishDate = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_START_FINISH_DATE) == BST_CHECKED;
				if (lpPolyotyDlgData->bUseStartFinishDate)
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_START_DATE); 
					EnableWindow(hEdit, TRUE);
					hEdit = GetDlgItem(hDlg, IDC_EDIT_FINISH_DATE); 
					EnableWindow(hEdit, TRUE);

					if(IsDlgButtonChecked(hDlg, IDC_CHECK_USE_PREVIOUSE_START_FINISH_DATE) 
						== BST_UNCHECKED)
					{
						SendMessage(hDlg, WM_COMMAND,ID_TEST_TIME_FORMAT, 1);
						HWND hCheck = GetDlgItem(hDlg, IDC_CHECK_USE_PREVIOUSE_START_FINISH_DATE); 
						EnableWindow(hCheck, FALSE);
					}

					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					wsprintf(startDate,"%d/%02d/%02d", lpPolyotyDlgData->startYear, lpPolyotyDlgData->startMonth, lpPolyotyDlgData->startDay);
					wsprintf(finishDate,"%d/%02d/%02d", lpPolyotyDlgData->finishYear, lpPolyotyDlgData->finishMonth, lpPolyotyDlgData->finishDay);
					SetDlgItemText(hDlg,IDC_EDIT_START_DATE, startDate);
					SetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE, finishDate);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				else
				{
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_START_DATE); 
					SetDlgItemText(hDlg, IDC_EDIT_START_DATE, "");
					EnableWindow(hEdit, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					hEdit = GetDlgItem(hDlg, IDC_EDIT_FINISH_DATE); 
					SetDlgItemText(hDlg, IDC_EDIT_FINISH_DATE, "");
					EnableWindow(hEdit, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										
				}
			 }
			 break;
		 case IDC_CHECK_USE_ALL_COLS:
			 {
				lpPolyotyDlgData->bUseAllCols = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_ALL_COLS) == BST_CHECKED;
				if (!lpPolyotyDlgData->bUseAllCols)
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_MAX_COLS); 
					EnableWindow(hEdit, TRUE);
					SetDlgItemInt(hDlg, IDC_EDIT_MAX_COLS,
						lpPolyotyDlgData->nMaxCols, true);

				}
				else
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_MAX_COLS); 
					SetDlgItemText(hDlg, IDC_EDIT_MAX_COLS, "");
					EnableWindow(hEdit, FALSE);
				}
			 }
			 break;
		 case IDC_CHECK_THIS_IS_LOCAL_TIME:
			 {
				lpPolyotyDlgData->thisIsLocalTime = IsDlgButtonChecked( hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME) == BST_CHECKED;
				if (lpPolyotyDlgData->thisIsLocalTime)
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET); 
					EnableWindow(hEdit, TRUE);
					SetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET,
						lpPolyotyDlgData->localTimeOffsetHours, true);

				}
				else
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET); 
					SetDlgItemText(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, "");
					EnableWindow(hEdit, FALSE);
				}
			 }
			 break;
		 case IDC_CHECK_IGNORE_FIRST_LINES:
			 {
				lpPolyotyDlgData->bIgnoreFirstLines = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_IGNORE_FIRST_LINES) == BST_CHECKED;
				if (lpPolyotyDlgData->bIgnoreFirstLines)
				{
					
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_N_LINES_TO_IGNORE); 
					EnableWindow(hEdit, TRUE);
					SetDlgItemInt(hDlg, IDC_EDIT_N_LINES_TO_IGNORE,
						lpPolyotyDlgData->nLinesToIgnore, true);
					HWND hBtn = GetDlgItem(hDlg, IDC_BUTTON_N_LINES_TO_IGNORE); 
					EnableWindow(hBtn, TRUE);

				}
				else
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_N_LINES_TO_IGNORE); 
					SetDlgItemText(hDlg, IDC_EDIT_N_LINES_TO_IGNORE, "");
					EnableWindow(hEdit, FALSE);
					HWND hBtn = GetDlgItem(hDlg, IDC_BUTTON_N_LINES_TO_IGNORE); 
					EnableWindow(hBtn, FALSE);
				}
			 }
			 break;

		case IDC_COMBO_DELIMITER:
			{
				lpPolyotyDlgData->delimID = SendDlgItemMessage( hDlg, 
					IDC_COMBO_DELIMITER,
					CB_GETCURSEL,0,(LPARAM)0 );
				switch(lpPolyotyDlgData->delimID)
				{
				case 0:
					lpPolyotyDlgData->delim = '\t';
					break;
				case 1:
					lpPolyotyDlgData->delim = ' ';
					break;
				case 2:
					lpPolyotyDlgData->delim = ',';
					break;
				case 3:
					lpPolyotyDlgData->delim = ';';
					break;
				}

			}
			break;

		case IDC_COMBO_TIME_FORMAT:
			{
				lpPolyotyDlgData->timeFormat = (short)SendDlgItemMessage( hDlg, 
					IDC_COMBO_TIME_FORMAT,
					CB_GETCURSEL,0,(LPARAM)0 );
			}
			break;
            
		case ID_TEST_TIME_FORMAT :
			{
				int listBoxLen = SendDlgItemMessage( hDlg, IDC_LIST_POLYOTY, LB_GETCOUNT, 0, 0);
				char stime1[2047], stime2[2047];
				for (int i = 0;  i < 2; i++)
				{
					int y,mo,d,h,mi,s,milli;
					double t;
					char *p1, *p2;
					char title[31];
					if (i == 0)
						p1 = szLine1;
					else
						p1 = szLineEnd;
					if ((p2 = strchr(p1,lpPolyotyDlgData->delim)) != NULL)
					{
						strncpy(title, p1, p2-p1);
						title[p2-p1] = '\0';
					}
					else
					{
						char err_str[255];
						sprintf(err_str, "Selected delimiter \"%c\" is not correct!!!\n%s",lpPolyotyDlgData->delim, p1);
						MessageBox(0, err_str, "TEST_TIME_FORMAT", 0);
						return 0;
					}
					if (!ParseTimeString(title, 
						lpPolyotyDlgData->timeFormat, 
						lpPolyotyDlgData->thisIsLocalTime,	
						lpPolyotyDlgData->localTimeOffsetHours,
						y, mo, d, h, mi, s, milli, t))
						return 0;
					if (i == 0)
					{
						sprintf(stime1,"t = %lf %02d:%02d:%d %02d:%02d:%02d.%lf\n",
							t, d,mo,y,h,mi,s,double(milli)/1000.0);
                        
						if (lParam == 1)
						{
							lpPolyotyDlgData->startYear	= y;
							lpPolyotyDlgData->startMonth	= mo;
							lpPolyotyDlgData->startDay	= d;
						}
					}
					else
					{
						sprintf(stime2,"t = %lf %02d:%02d:%d %02d:%02d:%02d.%lf",
						t, d,mo,y,h,mi,s,double(milli)/1000.0);

						if (lParam == 1)
						{
							lpPolyotyDlgData->finishYear	= y;
							lpPolyotyDlgData->finishMonth= mo;
							lpPolyotyDlgData->finishDay	= d;
						}
					}
				}
				char str[4800];

				strcpy(str, stime1);strcat(str, stime2);
				if (lParam != 1 && lParam != 2)
					MessageBox(0,str,"time interval",0);
			}
			break;
		case IDC_TEST_START_FINISH_DATE :
			{
				static int cumdpm[13];
				int y1,m1,d1, y2, m2, d2;
				cumdpm[0] = 0;
				cumdpm[1] = 31;
				cumdpm[2] = 28;
				cumdpm[3] = 31;
				cumdpm[4] = 30;
				cumdpm[5] = 31;
				cumdpm[6] = 30;
				cumdpm[7] = 31;
				cumdpm[8] = 31;
				cumdpm[9] = 30;
				cumdpm[10] = 31;
				cumdpm[11] = 30;
				cumdpm[12] = 31;

				GetDlgItemText(hDlg,IDC_EDIT_START_DATE, startDate, 12);
				GetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE, finishDate, 12);

				sscanf(startDate, "%d/%d/%d\0", &y1, &m1, &d1);
				sscanf(finishDate, "%d/%d/%d\0", &y2, &m2, &d2);


				if (y1 < 0)
				{
					MessageBox(NULL, "Incorrect Start Year", "Date Error", 0);
					return 0;
				}
				if (y2 < 0)
				{
					MessageBox(NULL, "Incorrect Finish Year", "Date Error", 0);
					return 0;
				}

				if (m1 < 1 || m1 > 12)
				{
					MessageBox(NULL, "Incorrect Start Month", "Date Error", 0);
					return 0;
				}
				if (m2 < 1 || m2 > 12)
				{
					MessageBox(NULL, "Incorrect Finish Month", "Date Error", 0);
					return 0;
				}

				if (d1 < 1 || d1 > (m1 == 2 && ((y1%4 == 0 && y1%100 != 0) || y1%400 == 0)) + cumdpm[m1])
				{
					MessageBox(NULL, "Incorrect Start Day", "Date Error", 0);
					return 0;
				}
				if (d2 < 1 || d2 > (m2 == 2 && ((y2%4 == 0 && y2%100 != 0) || y2%400 == 0)) + cumdpm[m2])
				{
					MessageBox(NULL, "Incorrect Finish Day", "Date Error", 0);
					return 0;
				}
				double dn1 = datenum(y1, m1, d1, 0, 0, 0, 0);
				double dn2 = datenum(y2, m2, d2, 0, 0, 0, 0);

				if (dn2 < dn1)
				{
					MessageBox(NULL, "Incorrect Start and Finish Dates", "Date Error", 0);
					return 0;
				}
				lpPolyotyDlgData->startYear		= y1;
				lpPolyotyDlgData->startMonth	= m1;
				lpPolyotyDlgData->startDay		= d1;
				lpPolyotyDlgData->finishYear	= y2;
				lpPolyotyDlgData->finishMonth	= m2;
				lpPolyotyDlgData->finishDay		= d2;

				lpPolyotyDlgData->startTime = datenum(y1,m1,d1,0,0,0,0);
				lpPolyotyDlgData->finishTime = datenum(y2,m2,d2,0,0,0,0);


				return 1;
			}
			break;
           case IDOK :
		   case IDC_BUTTON_POLYOTY_PREPARE_FOR_NNET2:
		   case IDC_BUTTON_POLYOTY_PREPARE_FOR_NNET:
		   case IDC_BUTTON_CREATE_COMMON_FILE_WITH_VAR :
		   case IDC_BUTTON_COMMON_FILE_ON_PROFILS :
			   {
					SendMessage(hDlg,WM_COMMAND, ID_TEST_TIME_FORMAT,2) ;
				   if(lpPolyotyDlgData->bUseStartFinishDate)
				   {
						SendMessage(hDlg,WM_COMMAND, IDC_TEST_START_FINISH_DATE,0) ;
				   }
				   hDlgModeless = NULL;
				   EndDialog( hDlg, IDCANCEL );
				   if(lpPolyotyDlgData->thisIsLocalTime)
				   {
						// 
						BOOL bTranslated;
						lpPolyotyDlgData->localTimeOffsetHours = 
							(short)GetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, &bTranslated, false);
						if (!bTranslated)
							lpPolyotyDlgData->localTimeOffsetHours = 2;
				   }
				   if(lpPolyotyDlgData->bIgnoreFirstLines)
				   {
						// 
						BOOL bTranslated;
						lpPolyotyDlgData->nLinesToIgnore = 
							(short)GetDlgItemInt(hDlg, IDC_EDIT_N_LINES_TO_IGNORE, &bTranslated, false);
						if (!bTranslated)
							lpPolyotyDlgData->nLinesToIgnore = 0;
				   }
				   if(!lpPolyotyDlgData->bUseAllCols)
				   {
						// 
						BOOL bTranslated;
						lpPolyotyDlgData->nMaxCols = 
							(short)GetDlgItemInt(hDlg, IDC_EDIT_MAX_COLS, &bTranslated, false);
						if (!bTranslated)
							lpPolyotyDlgData->bUseAllCols = true;
				   }
					         
				   switch( LOWORD( wParam ) )
				   {
				   case IDC_BUTTON_POLYOTY_PREPARE_FOR_NNET:
					   {
						   DialogBoxParam( 
							   hInst, 
							   MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY_FOR_NNET), 
							   hDlg,
							   (DLGPROC)DlgProcPolyotyForNNet,
							   (LPARAM)lpPolyotyDlgData);

					   }
					   break;
				   case IDC_BUTTON_POLYOTY_PREPARE_FOR_NNET2:
					   {
							if (tvd != NULL) delete tvd;		// how to safely release the memory...
							tvd = new PolyotyNnetDlg(lpPolyotyDlgData);		// ...right after the dialog is closed?
					   }
					   break;
				   case IDC_BUTTON_COMMON_FILE_ON_PROFILS:
					   createCommonFileOnProfils(lpPolyotyDlgData);
					   break;
				   case IDC_BUTTON_CREATE_COMMON_FILE_WITH_VAR:
					   createCommonFileWithVar(lpPolyotyDlgData);
					   break;
				   case IDOK:
					   {
						   importExcelCommonFileParam(lpPolyotyDlgData);
						   SendMessage(lpPolyotyDlgData->hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
		#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
		#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
		#endif
							}
					   }
					   break;
				   }


			   }
			   break;
           case IDCANCEL :
			   hDlgModeless = NULL;
                 EndDialog( hDlg, IDCANCEL );
                 break;
         }
         break;
	case WM_DESTROY:
		{
			if (szBuff) delete[] szBuff;
			if (szLine1) delete[] szLine1;
			if (szLineEnd) delete[] szLineEnd;
		}
		break;


      default :
         return( FALSE );
  }
  return( TRUE );
}


LRESULT CALLBACK DlgProcSelectFile( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSELECTFILEDLGDATA lpSelectFileDlgData;
  switch( uMsg )
  {
    case WM_INITDIALOG :
		lpSelectFileDlgData = (LPSELECTFILEDLGDATA)lParam;
		SetDlgItemText(hDlg, IDC_STATIC_SELECT_FILE_DLG_NAME, 
			lpSelectFileDlgData->szSelectFileDlgName);

		lpSelectFileDlgData->bIsSignal2Checked = false;
		CheckDlgButton( hDlg, IDC_CHECK_SIGNAL2,
			lpSelectFileDlgData->bIsSignal2Checked ? BST_CHECKED : BST_UNCHECKED );

		SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"График не масштабировать");
		SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"Масштабировать по предыдущим");
		SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"Масштабировать вместе с предыдущими");
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_SETCURSEL,
			lpSelectFileDlgData->scaleModeX,(LPARAM)0 );

		strcpy( szPath, directory);
		strcat( szPath, "\\" );
		strcat( szPath, lpSelectFileDlgData->szFileFilter );

         if(DlgDirList( hDlg, szPath, IDC_LIST, IDC_DIRECTORY,
                     DDL_DIRECTORY | DDL_DRIVES ) == 0)
		 {
			 MessageBox(0,szPath,"DlgDirList 0",0);
			 strcpy(szPath,"C:\\");
			 strcat( szPath, lpSelectFileDlgData->szFileFilter );
			 DlgDirList( hDlg, szPath, IDC_LIST, IDC_DIRECTORY,
                     DDL_DIRECTORY | DDL_DRIVES );
		 }

         break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
			case IDC_CHECK_SIGNAL2:
				lpSelectFileDlgData->bIsSignal2Checked = IsDlgButtonChecked( hDlg, IDC_CHECK_SIGNAL2) == BST_CHECKED;
				break;
			case IDC_COMBO_SCALE_MODE:
				lpSelectFileDlgData->scaleModeX = (short)SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_MODE, CB_GETCURSEL,0,(LPARAM)0 );
				break;




           case IDC_LIST :
                 if ( HIWORD( wParam ) == LBN_DBLCLK)
                 {
		   case IDOK :
                   if ( DlgDirSelectEx( hDlg, szPath, PATH_STRING_SIZE * sizeof( char ),
                                        IDC_LIST ) )
                   {
                      //strcat( szPath, "*.*" );
					  strcat( szPath, lpSelectFileDlgData->szFileFilter );
                      DlgDirList( hDlg, szPath, IDC_LIST, IDC_DIRECTORY,
                                  DDL_DIRECTORY | DDL_DRIVES );
				   GetDlgItemText(hDlg,IDC_DIRECTORY, directory, 254);
                   }
                   else
				   {
                      if (IDOK == MessageBox( hDlg, szPath, "File Selected",
                                  MB_OKCANCEL | MB_ICONINFORMATION ))
					  {
							hDlgModeless = NULL;
							EndDialog( hDlg, IDCANCEL );

							SendMessage(hMainWnd, WM_COMMAND, ID_FILENAME_DONE, 0);
					  }
				   }
                 }
                 break;


           case IDCANCEL :
			   hDlgModeless = NULL;
                 EndDialog( hDlg, IDCANCEL );
                 break;
         }
         break;

      default :
         return( FALSE );
  }
  return( TRUE );
}

LRESULT CALLBACK DlgProcSaveAsFile( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSAVEASFILEDLGDATA lpSaveAsFileDlgData;
  switch( uMsg )
  {
    case WM_INITDIALOG :
		lpSaveAsFileDlgData = (LPSAVEASFILEDLGDATA)lParam;
		SendDlgItemMessage( hDlg, IDC_COMBO_SAVE_AS_FILE_TYPE, CB_RESETCONTENT, 0,0);
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_SAVE_AS_FILE_TYPE, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"var");
		SendDlgItemMessage( hDlg, IDC_COMBO_SAVE_AS_FILE_TYPE, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"csv");
		SendDlgItemMessage( hDlg, IDC_COMBO_SAVE_AS_FILE_TYPE, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"txt");
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_SAVE_AS_FILE_TYPE, CB_SETCURSEL,
			lpSaveAsFileDlgData->SaveAsFileType,(LPARAM)0 );
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		CreateDirectory(lpSaveAsFileDlgData->directory, NULL);


		int y1,m1,d1,y2,m2,d2,h,mi,s,milli;
		if (vDoc[0].m_t.Length() > 0)
		{
			datevec(vDoc[0].m_t[0],y1,m1,d1,h,mi,s,milli);
			datevec(vDoc[0].m_t.End(),y2,m2,d2,h,mi,s,milli);

			if( y1 != y2 || d1 != d2 || m1 != m2)
				wsprintf(lpSaveAsFileDlgData->filename,"%d_%02d_%02d_%02d_%02d_%02d_%02d",
					vDoc[0].m_nInstrumentNumber1,
					y1-(y1/100)*100, m1, d1, 
					y2-(y2/100)*100, m2, d2);
			else
				wsprintf(lpSaveAsFileDlgData->filename,"%d_%d_%02d_%02d",
					vDoc[0].m_nInstrumentNumber1, y1, m1, d1);
			SetDlgItemText(hDlg, IDC_EDIT_SAVE_AS_FILENAME,lpSaveAsFileDlgData->filename);
		}


		strcpy( lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->directory);
		strcat( lpSaveAsFileDlgData->szPath, "\\" );
		strcat( lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->szFileFilter );

         if(DlgDirList( hDlg, lpSaveAsFileDlgData->szPath, IDC_LIST_SAVE_AS, IDC_DIRECTORY_SAVE_AS,
                     DDL_DIRECTORY | DDL_DRIVES ) == 0)
		 {
			 MessageBox(0,lpSaveAsFileDlgData->szPath,"DlgDirList 0",0);
			 strcpy(lpSaveAsFileDlgData->szPath,"C:\\");
			 strcat( lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->szFileFilter );
			 DlgDirList( hDlg, szPath, IDC_LIST_SAVE_AS, IDC_DIRECTORY_SAVE_AS,
                     DDL_DIRECTORY | DDL_DRIVES );
		 }

         break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
		 case IDC_COMBO_SAVE_AS_FILE_TYPE:
			 {
				lpSaveAsFileDlgData->SaveAsFileType = 
					(short)SendDlgItemMessage( hDlg, 
					IDC_COMBO_SAVE_AS_FILE_TYPE,
					CB_GETCURSEL,0,(LPARAM)0 );
			 }
			 break;
           case IDC_LIST_SAVE_AS :
                 if ( HIWORD( wParam ) == LBN_DBLCLK)
                 {
                   if ( DlgDirSelectEx( hDlg, lpSaveAsFileDlgData->szPath, sizeof( lpSaveAsFileDlgData->szPath ),
                                        IDC_LIST_SAVE_AS ) )
                   {
                      //strcat( lpSaveAsFileDlgData->szPath, "*.*" );
					  strcat( lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->szFileFilter );
                      DlgDirList( hDlg, szPath, IDC_LIST_SAVE_AS, IDC_DIRECTORY_SAVE_AS,
                                  DDL_DIRECTORY | DDL_DRIVES );
				   GetDlgItemText(hDlg,IDC_DIRECTORY_SAVE_AS, lpSaveAsFileDlgData->directory, 254);
                   }
                   else
				   {
                      if (IDOK == MessageBox( hDlg, lpSaveAsFileDlgData->szPath, "File Selected",
                                  MB_OKCANCEL | MB_ICONINFORMATION ))
					  {
							hDlgModeless = NULL;
							EndDialog( hDlg, IDCANCEL );

							//SendMessage(hMainWnd, WM_COMMAND, ID_FILENAME_DONE, 0);
					  }
				   }
                 }
                 break;
		   case IDOK :
			   {
				   switch(lpSaveAsFileDlgData->SaveAsFileType)
				   {
				   case 0:
						strcpy(lpSaveAsFileDlgData->ext, "var");
						break;
				   case 1:
						strcpy(lpSaveAsFileDlgData->ext, "csv");
						break;
				   case 2:
						strcpy(lpSaveAsFileDlgData->ext, "txt");
						break;
				   }

				   GetDlgItemText(hDlg, IDC_EDIT_SAVE_AS_FILENAME,lpSaveAsFileDlgData->filename, 126);

				   strcpy(lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->directory);
				   strcat(lpSaveAsFileDlgData->szPath, "\\");
				   strcat(lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->filename);
				   strcat(lpSaveAsFileDlgData->szPath, ".");
				   strcat(lpSaveAsFileDlgData->szPath, lpSaveAsFileDlgData->ext);


				   SaveAs(lpSaveAsFileDlgData);
				hDlgModeless = NULL;
                 EndDialog( hDlg, IDCANCEL );
			   }
			   break;

           case IDCANCEL :
			   hDlgModeless = NULL;
                 EndDialog( hDlg, IDCANCEL );
                 break;
         }
         break;

      default :
         return( FALSE );
  }
  return( TRUE );
}
struct PrintDailyRaportDlgData
{
	short startYear;
	short startMonth;
	short startDay;
	short finishYear;
	short finishMonth;
	short finishDay;	
	short shPrintRaportType;
	bool bUseNoise;
}
pdrdd;

LRESULT CALLBACK DlgProcPrintDailyRaportParam( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	char startDate[15],
		finishDate[15];

	int y1, y2, m1, m2, d1, d2;
  switch( uMsg )
  {
    case WM_INITDIALOG :
		strcpy( szPath, directory);
		strcat( szPath, "\\*.*" );

         if(DlgDirList( hDlg, szPath, 
			 IDC_LIST_PRINT_RAPORT, IDC_DIRECTORY_PRINT_RAPORT,
                     DDL_DIRECTORY | DDL_DRIVES ) == 0)
		 {
			 MessageBox(0,szPath," StartFinishDateDlgProc DlgDirList 0",0);
			 strcpy(szPath,"C:\\*.*");
			 DlgDirList( hDlg, szPath, 
				 IDC_LIST_PRINT_RAPORT, IDC_DIRECTORY_PRINT_RAPORT,
                     DDL_DIRECTORY | DDL_DRIVES );
		 }

		 wsprintf(startDate,"%d/%02d/%02d", pdrdd.startYear, pdrdd.startMonth, pdrdd.startDay);
		 wsprintf(finishDate,"%d/%02d/%02d", pdrdd.finishYear, pdrdd.finishMonth, pdrdd.finishDay);
		 SetDlgItemText(hDlg,IDC_EDIT_START_DATE_PRINT_RAPORT, startDate);
		 SetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE_PRINT_RAPORT, finishDate);

		 // SET RADIO OF FORMAT
		 switch (pdrdd.shPrintRaportType)
		 {
		 case 0:
			 CheckRadioButton( hDlg,
				 IDC_RADIO_PRINT_RAPORT_TYPE_0,
				 IDC_RADIO_PRINT_RAPORT_TYPE_2,
				 IDC_RADIO_PRINT_RAPORT_TYPE_0);
			 break;
		 case 1:
			 CheckRadioButton( hDlg,
				 IDC_RADIO_PRINT_RAPORT_TYPE_0,
				 IDC_RADIO_PRINT_RAPORT_TYPE_2,
				 IDC_RADIO_PRINT_RAPORT_TYPE_1);
			 break;
		 case 2:
			 CheckRadioButton( hDlg,
				 IDC_RADIO_PRINT_RAPORT_TYPE_0,
				 IDC_RADIO_PRINT_RAPORT_TYPE_2,
				 IDC_RADIO_PRINT_RAPORT_TYPE_2);
			 break;
		 }
		 // Set min, mean, max check

		 CheckDlgButton( hDlg, IDC_CHECK_PRINT_RAPORT_USE_NOISE,
			 pdrdd.bUseNoise ? BST_CHECKED : BST_UNCHECKED );



		break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
		 case IDC_RADIO_PRINT_RAPORT_TYPE_0:
			 {
				 pdrdd.shPrintRaportType = 0;
			 }
			 break;
		 case IDC_RADIO_PRINT_RAPORT_TYPE_1:
			 {
				 pdrdd.shPrintRaportType = 1;
			 }
			 break;
		 case IDC_RADIO_PRINT_RAPORT_TYPE_2:
			 {
				 pdrdd.shPrintRaportType = 2;
			 }
			 break;

 		 case IDC_CHECK_PRINT_RAPORT_USE_NOISE:
			{
				pdrdd.bUseNoise = IsDlgButtonChecked( hDlg, IDC_CHECK_PRINT_RAPORT_USE_NOISE) == BST_CHECKED;
			}
			break;

           case IDC_LIST_PRINT_RAPORT :
                 if ( HIWORD( wParam ) == LBN_DBLCLK )
                 {
                   if ( DlgDirSelectEx( hDlg, szPath, PATH_STRING_SIZE * sizeof( char ),
                                        IDC_LIST_PRINT_RAPORT ) )
                   {

                      strcat( szPath, "*.*" );

                      DlgDirList( hDlg, szPath, IDC_LIST_PRINT_RAPORT, IDC_DIRECTORY_PRINT_RAPORT,
                                  DDL_DIRECTORY | DDL_DRIVES );
					   GetDlgItemText(hDlg,IDC_DIRECTORY_PRINT_RAPORT, directory, 254);
					 }
                 }
                 break;


           case ID_TEST_DLG_DATA :
			   {
				   //Нажимаем кнопку ОК для обработки всех файлов, находящихся в дирректории
					static int cumdpm[13];
					cumdpm[0] = 0;
					cumdpm[1] = 31;
					cumdpm[2] = 28;
					cumdpm[3] = 31;
					cumdpm[4] = 30;
					cumdpm[5] = 31;
					cumdpm[6] = 30;
					cumdpm[7] = 31;
					cumdpm[8] = 31;
					cumdpm[9] = 30;
					cumdpm[10] = 31;
					cumdpm[11] = 30;
					cumdpm[12] = 31;
					
					GetDlgItemText(hDlg,IDC_EDIT_START_DATE_PRINT_RAPORT, startDate, 12);
					GetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE_PRINT_RAPORT, finishDate, 12);

					sscanf(startDate, "%d/%d/%d\0", &y1, &m1, &d1);
					sscanf(finishDate, "%d/%d/%d\0", &y2, &m2, &d2);

					if (y1 < 0)
					{
						MessageBox(NULL, "Incorrect Start Year", "Date Error", 0);
						return 0;
					}
					if (y2 < 0)
					{
						MessageBox(NULL, "Incorrect Finish Year", "Date Error", 0);
						return 0;
					}

					if (m1 < 1 || m1 > 12)
					{
						MessageBox(NULL, "Incorrect Start Month", "Date Error", 0);
						return 0;
					}
					if (m2 < 1 || m2 > 12)
					{
						MessageBox(NULL, "Incorrect Finish Month", "Date Error", 0);
						return 0;
					}

					if (d1 < 1 || d1 > (m1 == 2 && ((y1%4 == 0 && y1%100 != 0) || y1%400 == 0)) + cumdpm[m1])
					{
						MessageBox(NULL, "Incorrect Start Day", "Date Error", 0);
						return 0;
					}
					if (d2 < 1 || d2 > (m2 == 2 && ((y2%4 == 0 && y2%100 != 0) || y2%400 == 0)) + cumdpm[m2])
					{
						MessageBox(NULL, "Incorrect Finish Day", "Date Error", 0);
						return 0;
					}
					double dn1 = datenum(y1, m1, d1, 0, 0, 0, 0);
					double dn2 = datenum(y2, m2, d2, 0, 0, 0, 0);

					if (dn2 < dn1)
					{
						MessageBox(NULL, "Incorrect Start and Finish Dates", "Date Error", 0);
						return 0;
					}
					pdrdd.startYear		= y1;
					pdrdd.startMonth	= m1;
					pdrdd.startDay		= d1;
					pdrdd.finishYear	= y2;
					pdrdd.finishMonth	= m2;
					pdrdd.finishDay		= d2;

					GetDlgItemText(hDlg,IDC_DIRECTORY_PRINT_RAPORT, directory, 254);
			   }
			   break;
		   case IDOK:
			   {
					SendMessage(hDlg,WM_COMMAND, ID_TEST_DLG_DATA,0);
					hDlgModeless = NULL;
					EndDialog( hDlg, IDCANCEL );
					SendMessage(hMainWnd, WM_COMMAND, ID_PRINT_RAPORT_DO, 0);
			   }
               break;
		   case ID_VIEW_RAPORT:
			   {
			   		SendMessage(hDlg,WM_COMMAND, ID_TEST_DLG_DATA,0);
					hDlgModeless = NULL;
					EndDialog( hDlg, IDCANCEL );
					SendMessage(hMainWnd, WM_COMMAND, ID_PRINT_RAPORT_VIEW, 0);
			   }
			   break;
           case IDCANCEL :
			   {
			     hDlgModeless = NULL;
                 EndDialog( hDlg, IDCANCEL );
			   }
               break;
         }
         break;

      default :
         return( FALSE );
  }
  return( TRUE );
}

 StartFinishDateDlgData sfddd;

LRESULT CALLBACK DlgProcStartFinishDate( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	char startDate[15],
		finishDate[15];
HWND hwndOwner; 
RECT rc, rcDlg, rcOwner; 

	int y1, y2, m1, m2, d1, d2;
  switch( uMsg )
  {
    case WM_INITDIALOG :

        // Get the owner window and dialog box rectangles. 
 
        if ((hwndOwner = GetParent(hDlg)) == NULL) 
        {
            hwndOwner = GetDesktopWindow(); 
        }

        GetWindowRect(hwndOwner, &rcOwner); 
        GetWindowRect(hDlg, &rcDlg); 
        CopyRect(&rc, &rcOwner); 
 
         // Offset the owner and dialog box rectangles so that 
         // right and bottom values represent the width and 
         // height, and then offset the owner again to discard 
         // space taken up by the dialog box. 
 
        OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top); 
        OffsetRect(&rc, -rc.left, -rc.top); 
        OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom); 
 
         // The new position is the sum of half the remaining 
         // space and the owner's original position. 
 
        SetWindowPos(hDlg, 
            HWND_TOP, 
            rcOwner.left + (rc.right / 2), 
            rcOwner.top + 80, 
            0, 0,          // ignores size arguments 
            SWP_NOSIZE); 

		SetDlgItemInt(hDlg, IDC_EDIT_INSTRUMENT_NUMBER,sfddd.nPribor,false);

		

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_EXTENSION, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"*.csv");
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_EXTENSION, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"*.dat");
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_EXTENSION, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"*.txt");
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_EXTENSION, CB_SETCURSEL,
			sfddd.nFileFilterID,(LPARAM)0 );

		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"excel time: in days since 1.1.1900, X,Y,Z");
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"tezey file: dd.mm.yy hh:mm:ss,milli,X,Y,Z");
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_SETCURSEL,
			sfddd.fileFormat,(LPARAM)0 );
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


		CheckDlgButton( hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME,
			sfddd.thisIsLocalTime ? BST_CHECKED : BST_UNCHECKED );



		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"tabulation");
		SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"space");
		SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)",");
		SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)";");
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_SETCURSEL,
			sfddd.delimID,(LPARAM)0 );
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


		strcpy( szPath, directory);
		strcat( szPath, "\\*.*" );

         if(DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                     DDL_DIRECTORY | DDL_DRIVES ) == 0)
		 {
			 MessageBox(0,szPath," StartFinishDateDlgProc DlgDirList 0",0);
			 strcpy(szPath,"C:\\*.*");
			 DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                     DDL_DIRECTORY | DDL_DRIVES );
		 }

		 wsprintf(startDate,"%d/%02d/%02d", sfddd.startYear, sfddd.startMonth, sfddd.startDay);
		 wsprintf(finishDate,"%d/%02d/%02d", sfddd.finishYear, sfddd.finishMonth, sfddd.finishDay);
		 SetDlgItemText(hDlg,IDC_EDIT_START_DATE, startDate);
		 SetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE, finishDate);

		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"1 sec" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"1 min" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"5 min" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"15 min" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"30 min" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"1 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"2 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"3 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"4 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"6 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"8 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"12 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"24 hours" );
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
					   (LPARAM)(LPCTSTR)"2x12 hours" );

		sfddd.shPeriodFlagMinStart			= 1;
		sfddd.shPeriodFlagMinEnd			= 4;
		sfddd.shPeriodFlagHoursStart		= 5;
		sfddd.shPeriodFlagHoursEnd			= 12;
		sfddd.shPeriodFlagHalfOfDay			= 13;

		 // SET COMBO OF PERIOD
		 SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_SETCURSEL, sfddd.shPeriodFlag,
					   (LPARAM)0 );
		 // SET RADIO OF FORMAT
		 switch (sfddd.shFormatFlag)
		 {
		 case 0:
			 CheckRadioButton( hDlg,
				 IDC_RADIO_EXCEL_OUTPUT_FORMAT,
				 IDC_RADIO_TEZEYVAR_OUTPUT_FORMAT,
				 IDC_RADIO_EXCEL_OUTPUT_FORMAT);
			 break;
		 case 1:
			 CheckRadioButton( hDlg,
				 IDC_RADIO_EXCEL_OUTPUT_FORMAT,
				 IDC_RADIO_TEZEYVAR_OUTPUT_FORMAT,
				 IDC_RADIO_MATLAB_OUTPUT_FORMAT);
			 break;
		 case 2:
			 CheckRadioButton( hDlg,
				 IDC_RADIO_EXCEL_OUTPUT_FORMAT,
				 IDC_RADIO_TEZEYVAR_OUTPUT_FORMAT,
				 IDC_RADIO_TEZEYVAR_OUTPUT_FORMAT);
			 break;
		 }


		 // Set min, mean, max check
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_PER_DAY,
			 sfddd.bMeanPerDay ? BST_CHECKED : BST_UNCHECKED );

		 // Set min, mean, max check
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN,
			 sfddd.bMin ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN,
			 sfddd.bMean ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP,
			 sfddd.bDisp ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN,
			 sfddd.bMedian ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX,
			 sfddd.bMax ? BST_CHECKED : BST_UNCHECKED );

		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN,
			 sfddd.bPolarization ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN,
			 sfddd.bInvPolarization ? BST_CHECKED : BST_UNCHECKED );

		 

		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE,
			 sfddd.bMinAngle ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE,
			 sfddd.bMedianAngle ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE,
			 sfddd.bMeanAngle ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE,
			 sfddd.bDispAngle ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE,
			 sfddd.bMaxAngle ? BST_CHECKED : BST_UNCHECKED );

		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE,
			 sfddd.bPolarizationAngle ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE,
			 sfddd.bInvPolarizationAngle ? BST_CHECKED : BST_UNCHECKED );



		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE3,
			 sfddd.bMinAngle3 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3,
			 sfddd.bMedianAngle3 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE3,
			 sfddd.bMeanAngle3 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE3,
			 sfddd.bDispAngle3 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE3,
			 sfddd.bMaxAngle3 ? BST_CHECKED : BST_UNCHECKED );

		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3,
			 sfddd.bPolarizationAngle3 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3,
			 sfddd.bInvPolarizationAngle3 ? BST_CHECKED : BST_UNCHECKED );



		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE4,
			 sfddd.bMinAngle4 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4,
			 sfddd.bMedianAngle4 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE4,
			 sfddd.bMeanAngle4 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE4,
			 sfddd.bDispAngle4 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE4,
			 sfddd.bMaxAngle4 ? BST_CHECKED : BST_UNCHECKED );

		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4,
			 sfddd.bPolarizationAngle4 ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4,
			 sfddd.bInvPolarizationAngle4 ? BST_CHECKED : BST_UNCHECKED );


		 
		 
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_XYZ,
			 sfddd.bMinXYZ ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_XYZ,
			 sfddd.bMeanXYZ ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_XYZ,
			 sfddd.bDispXYZ ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_XYZ,
			 sfddd.bMedianXYZ ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_XYZ,
			 sfddd.bMaxXYZ ? BST_CHECKED : BST_UNCHECKED );

		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_XYZ,
			 sfddd.bPolarizationXYZ ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_XYZ,
			 sfddd.bInvPolarizationXYZ ? BST_CHECKED : BST_UNCHECKED );	 
		 
		 
		 
		 
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_REVERSE_ANGLES,
			 sfddd.bReverseAngles ? BST_CHECKED : BST_UNCHECKED );
		 CheckDlgButton( hDlg, IDC_CHECK_COMMON_TO_CUT_PAGES_FOR_EXCEL,
			 sfddd.bToCutPagesExcel ? BST_CHECKED : BST_UNCHECKED );

		 

		 

		break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
		 case IDC_RADIO_EXCEL_OUTPUT_FORMAT:
			 {
				 sfddd.shFormatFlag = 0;
			 }
			 break;
		 case IDC_RADIO_MATLAB_OUTPUT_FORMAT:
			 {
				 sfddd.shFormatFlag = 1;
			 }
			 break;
		 case IDC_RADIO_TEZEYVAR_OUTPUT_FORMAT:
			 {
				 sfddd.shFormatFlag = 2;
			 }
			 break;
 		 case IDC_CHECK_COMMON_USE_MEAN_PER_DAY:
			{
				sfddd.bMeanPerDay = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_PER_DAY) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_REVERSE_ANGLES:
			{
				sfddd.bReverseAngles = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_REVERSE_ANGLES) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_TO_CUT_PAGES_FOR_EXCEL:
			{
				sfddd.bToCutPagesExcel = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_TO_CUT_PAGES_FOR_EXCEL) == BST_CHECKED;
			}
			break;



			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 		 case IDC_CHECK_COMMON_USE_MIN:
			{
				sfddd.bMin = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN:
			{
				sfddd.bMean = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP:
			{
				sfddd.bDisp = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN:
			{
				sfddd.bMedian = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX:
			{
				sfddd.bMax = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN:
			{
				sfddd.bPolarization = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN:
			{
				sfddd.bInvPolarization = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 		 case IDC_CHECK_COMMON_USE_MIN_ANGLE:
			{
				sfddd.bMinAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_ANGLE:
			{
				sfddd.bMedianAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_ANGLE:
			{
				sfddd.bMeanAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_ANGLE:
			{
				sfddd.bDispAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_ANGLE:
			{
				sfddd.bMaxAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE:
			{
				sfddd.bPolarizationAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_ANGLE:
			{
				sfddd.bInvPolarizationAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 		 case IDC_CHECK_COMMON_USE_MIN_ANGLE3:
			{
				sfddd.bMinAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3:
			{
				sfddd.bMedianAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_ANGLE3:
			{
				sfddd.bMeanAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_ANGLE3:
			{
				sfddd.bDispAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_ANGLE3:
			{
				sfddd.bMaxAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3:
			{
				sfddd.bPolarizationAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3:
			{
				sfddd.bInvPolarizationAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 		 case IDC_CHECK_COMMON_USE_MIN_ANGLE4:
			{
				sfddd.bMinAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4:
			{
				sfddd.bMedianAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_ANGLE4:
			{
				sfddd.bMeanAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_ANGLE4:
			{
				sfddd.bDispAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_ANGLE4:
			{
				sfddd.bMaxAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4:
			{
				sfddd.bPolarizationAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4:
			{
				sfddd.bInvPolarizationAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 		 case IDC_CHECK_COMMON_USE_MIN_XYZ:
			{
				sfddd.bMinXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_XYZ:
			{
				sfddd.bMeanXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_XYZ:
			{
				sfddd.bDispXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_XYZ:
			{
				sfddd.bMedianXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_XYZ:
			{
				sfddd.bMaxXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_XYZ:
			{
				sfddd.bPolarizationXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_XYZ:
			{
				sfddd.bInvPolarizationXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_XYZ) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		case IDC_COMBO_FILE_FORMAT:
			{
				sfddd.fileFormat = (short)SendDlgItemMessage( hDlg, 
					IDC_COMBO_FILE_FORMAT,
					CB_GETCURSEL,0,(LPARAM)0 );
			}
			break;
		case IDC_COMBO_FILE_EXTENSION:
			{
				switch(SendDlgItemMessage( hDlg, 
					IDC_COMBO_FILE_EXTENSION,
					CB_GETCURSEL,0,(LPARAM)0 ))
				{
				case 0:
					strcpy(sfddd.szFileFilter, "*.csv");
					break;
				case 1:
					strcpy(sfddd.szFileFilter, "*.dat");
					break;
				case 2:
					strcpy(sfddd.szFileFilter, "*.txt");
					break;
				}
			}
			break;

		 case IDC_CHECK_THIS_IS_LOCAL_TIME:
			 {
				sfddd.thisIsLocalTime = IsDlgButtonChecked( hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME) == BST_CHECKED;
				if (sfddd.thisIsLocalTime)
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET); 
					EnableWindow(hEdit, TRUE);
					SetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET,
						sfddd.localTimeOffsetHours, true);

				}
				else
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET); 
					SetDlgItemText(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, "");
					EnableWindow(hEdit, FALSE);
				}
			 }
			 break;
		case IDC_COMBO_DELIMITER:
			{
				switch(SendDlgItemMessage( hDlg, 
					IDC_COMBO_DELIMITER,
					CB_GETCURSEL,0,(LPARAM)0 ))
				{
				case 0:
					sfddd.delim = '\t';
					break;
				case 1:
					sfddd.delim = ' ';
					break;
				case 2:
					sfddd.delim = ',';
					break;
				case 3:
					sfddd.delim = ';';
					break;
				}

			}
			break;

          case IDC_COMBO_PERIOD :
			   {
				   long lComboCurSel = SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_GETCURSEL, 0,
							   (LPARAM)0 );
				   sfddd.shPeriodFlag = short(lComboCurSel);
			   }
			   break;
           case IDC_LIST2 :
                 if ( HIWORD( wParam ) == LBN_DBLCLK )
                 {
                   if ( DlgDirSelectEx( hDlg, szPath, PATH_STRING_SIZE * sizeof( char ),
                                        IDC_LIST2 ) )
                   {

                      strcat( szPath, "*.*" );
                      DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                                  DDL_DIRECTORY | DDL_DRIVES );
					   GetDlgItemText(hDlg,IDC_DIRECTORY2, directory, 254);
                   }
                 }
                 break;
		   case IDC_USE_WHOLE_DIRECTORY:
			   {
				   GetDlgItemText(hDlg,IDC_DIRECTORY2, directory, 254);
				   strcpy(szPath,directory);
                   strcat( szPath, "\\" );
                   strcat( szPath, sfddd.szFileFilter);
				   DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                                  DDL_READWRITE );
                  if (IDOK == MessageBox( hDlg, szPath, "Directory Selected",
                              MB_OKCANCEL | MB_ICONINFORMATION ))
				  {

					   sfddd.nFilesInDirectory = SendDlgItemMessage( hDlg, IDC_LIST2, LB_GETCOUNT, 0, 0);
					   //память не освобождена!!!!
					   sfddd.vFileNameLengthes = (int *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
						   sizeof( int ) *  sfddd.nFilesInDirectory);
					   sfddd.vFileNames = (char **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
						   sizeof( char * ) *  sfddd.nFilesInDirectory);
					   for (int iFile = 0; iFile < sfddd.nFilesInDirectory; iFile++)
					   {
						   sfddd.vFileNameLengthes[iFile] = SendDlgItemMessage( hDlg, 
							   IDC_LIST2, LB_GETTEXTLEN, (WPARAM) iFile, 0)+1;
						   sfddd.vFileNames[iFile] = (char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
						   sizeof( char ) * sfddd.vFileNameLengthes[iFile]);

						   if (LB_ERR!=SendDlgItemMessage( hDlg, 
							   IDC_LIST2, LB_GETTEXT, (WPARAM) iFile, (LPARAM)(sfddd.vFileNames[iFile])))
						   {
						   }
					   }
					   sfddd.nHowUseFilePath = 2;

					   {
						   if(sfddd.thisIsLocalTime)
						   {
								// 
								BOOL bTranslated;
								sfddd.localTimeOffsetHours = 
									(short)GetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, &bTranslated, false);
								if (!bTranslated)
									sfddd.localTimeOffsetHours = 0;
						   }
							char szPath_in[255];
							const int n=255; // length of buffer string line
							char szBuff[n]; // buffer string line
							double 
								t_excel,
								t0_excel = datenum(1900,1,1,0,0,0,0)-2;
							double test_t,test_t0;
							int X,Y,Z;

							double t_start, t_stop;

											/*char str2[64];
											sprintf(str2,"startDate=%d/%d/%d\n finishDate = %d/%d/%d\0", y1, m1, d1, y2, m2, d2);
											MessageBox(0,str2,"",0);*/

							RECT rcClient;  // Client area of parent window 
							int cyVScroll;  // Height of scroll bar arrow 
							HWND hwndPB;    // Handle of progress bar 

 

							// Ensure that the common control DLL is loaded
							// and create a progress bar along the bottom of
							// the client area of the parent window. 
							// Base the height of the progress bar on the
							// height of a scroll bar arrow. 
							InitCommonControls(); 
							GetClientRect(sfddd.hwndParent, &rcClient); 
							cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
							hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
									 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
									 0, 0,
									 //rcClient.left, rcClient.bottom,
									 rcClient.right, cyVScroll, 
									 sfddd.hwndParent, (HMENU) 0, hInst, NULL); 

							// Set the range and increment of the progress
							// bar. 

							SendMessage(hwndPB, PBM_SETRANGE, 0,
										MAKELPARAM(0, sfddd.nFilesInDirectory)); 
							SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
							FILE *stream;
							int y, mo, d, h, mi, s, milli;

							for (int iFile = 0; iFile < sfddd.nFilesInDirectory; iFile++)
							{
								

								strcpy(szPath_in, directory);
								strcpy(szPath_in, sfddd.vFileNames[iFile]);
								bool toRead = true;

								if ((stream = fopen(szPath_in,"rt")) != NULL)
								{

									//////////////////////////////////////
									double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

									//int yy = y - (y/100)*100;

								
									unsigned int i = 0;
									while (!feof(stream))
									{
										fgets(szBuff,n,stream);
										if (!feof(stream))
										{
											int _y;int rez;int rezWaited;
											switch (sfddd.fileFormat)
											{
											case 0:
												{
													rez = sscanf(szBuff,"%lf\t%d\t%d\t%d\t%d",
														&t_excel, &X, &Y, &Z);
													rezWaited = 4;
													if(sfddd.thisIsLocalTime)
														 t_excel -= 
														 double(sfddd.localTimeOffsetHours) / 24.0;
													datevec(t_excel+t0_excel,y,mo,d,h,mi,s,milli);
												}
												break;
											case 1:
												{
													rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
														&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
													rezWaited = 10;

													if (sfddd.nHowUseFilePath == 1)
														y = _y+ (y/100)*100;
													if (sfddd.nHowUseFilePath == 2)
														y = _y + 2000;
												}
												break;
											}					
											if (rez == rezWaited && rez != EOF)
											{
												if (i==0 && iFile==0)
												{
													switch (sfddd.fileFormat)
													{
													case 0:
														{
															test_t0 = t_excel + t0_excel;
														}
														break;
													case 1:
														{
															test_t0 = datenum(y,mo,d,h,mi,s,milli);
														}
														break;
													}
													t_start = test_t0;
												}
												else
												{
													switch (sfddd.fileFormat)
													{
													case 0:
														{
															test_t = t_excel + t0_excel;
														}
														break;
													case 1:
														{
															test_t = datenum(y,mo,d,h,mi,s,milli);
														}
														break;
													}
													if (test_t > test_t0)
													{
														test_t0 = test_t;
													}
													else
													{
														char errstr[255];
														sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath_in, int((test_t0 - test_t)*3600.*24.));
														MessageBox(0,errstr,"createCommonFile()",0);
													//	break;
													}
												}
											}
										}
										i++;
										 

									}
									
								}
								SendMessage(hwndPB, PBM_STEPIT, 0, 0);
							}
							t_stop = test_t;
							DestroyWindow(hwndPB);

							datevec(t_start,y,mo,d,h,mi,s,milli);
							sfddd.startYear = y;
							sfddd.startMonth = mo;
							sfddd.startDay = d;

							datevec(t_stop,y,mo,d,h,mi,s,milli);
							sfddd.finishYear = y;
							sfddd.finishMonth = mo;
							sfddd.finishDay = d;


							 wsprintf(startDate,"%d/%02d/%02d", sfddd.startYear, sfddd.startMonth, sfddd.startDay);
							 wsprintf(finishDate,"%d/%02d/%02d", sfddd.finishYear, sfddd.finishMonth, sfddd.finishDay);
							 char str[1023];
							 sprintf(str, "Do you agree with this start finish date:\nstart date: %s\nfinish date: %s \n\nPress NO to use your own start finish date", startDate, finishDate);
							 int respond = MessageBox( hDlg, str, "Start Finish Date",
										  MB_YESNOCANCEL | MB_ICONINFORMATION );


							  if (respond == IDYES)
							  {
								 SetDlgItemText(hDlg,IDC_EDIT_START_DATE, startDate);
								 SetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE, finishDate);
								  createCommonFile();
							  }
							  else
								  if (respond == IDNO)
								  {
									  SendMessage(hDlg,WM_COMMAND, IDC_TEST_START_FINISH_DATE,0);
									  createCommonFile();
								  }
					   }
				  }
				  strcpy(szPath,directory);
				  DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                                  DDL_DIRECTORY | DDL_DRIVES );
  			   }
			   break;

		   case IDC_USE_PATH_IN :
                   if ( DlgDirSelectEx( hDlg, szPath, PATH_STRING_SIZE * sizeof( char ),
                                        IDC_LIST2 ) )
                   {
                      strcat( szPath, "*.*" );
					  //strcat( szPath, lpSelectFileDlgData->szFileFilter );
                      DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                                  DDL_DIRECTORY | DDL_DRIVES );
				   GetDlgItemText(hDlg,IDC_DIRECTORY2, directory, 254);
                   }
                   else
				   {
                      if (IDOK == MessageBox( hDlg, szPath, "File Selected",
                                  MB_OKCANCEL | MB_ICONINFORMATION ))
					  {
							// номер прибора
							BOOL bTranslated;
							sfddd.nPribor = 
								(short)GetDlgItemInt(hDlg, IDC_EDIT_INSTRUMENT_NUMBER, &bTranslated, false);
							if (!bTranslated)
							{
								MessageBox(NULL, "Incorrect Pribor Number", "Date Error", 0);
								return 0;
							}
							//if(
							SendMessage(hDlg,WM_COMMAND, IDC_TEST_START_FINISH_DATE,0) //== 0)
								//return 0
								;

							//
							//hDlgModeless = NULL;
							//EndDialog( hDlg, IDCANCEL );
							sfddd.nHowUseFilePath = 1;
							createCommonFile();

					  }
				   }
                 break;


           case IDC_TEST_START_FINISH_DATE :
			   {
					static int cumdpm[13];
					cumdpm[0] = 0;
					cumdpm[1] = 31;
					cumdpm[2] = 28;
					cumdpm[3] = 31;
					cumdpm[4] = 30;
					cumdpm[5] = 31;
					cumdpm[6] = 30;
					cumdpm[7] = 31;
					cumdpm[8] = 31;
					cumdpm[9] = 30;
					cumdpm[10] = 31;
					cumdpm[11] = 30;
					cumdpm[12] = 31;

					GetDlgItemText(hDlg,IDC_EDIT_START_DATE, startDate, 12);
					GetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE, finishDate, 12);

					sscanf(startDate, "%d/%d/%d\0", &y1, &m1, &d1);
					sscanf(finishDate, "%d/%d/%d\0", &y2, &m2, &d2);


					if (y1 < 0)
					{
						MessageBox(NULL, "Incorrect Start Year", "Date Error", 0);
						return 0;
					}
					if (y2 < 0)
					{
						MessageBox(NULL, "Incorrect Finish Year", "Date Error", 0);
						return 0;
					}

					if (m1 < 1 || m1 > 12)
					{
						MessageBox(NULL, "Incorrect Start Month", "Date Error", 0);
						return 0;
					}
					if (m2 < 1 || m2 > 12)
					{
						MessageBox(NULL, "Incorrect Finish Month", "Date Error", 0);
						return 0;
					}

					if (d1 < 1 || d1 > (m1 == 2 && ((y1%4 == 0 && y1%100 != 0) || y1%400 == 0)) + cumdpm[m1])
					{
						MessageBox(NULL, "Incorrect Start Day", "Date Error", 0);
						return 0;
					}
					if (d2 < 1 || d2 > (m2 == 2 && ((y2%4 == 0 && y2%100 != 0) || y2%400 == 0)) + cumdpm[m2])
					{
						MessageBox(NULL, "Incorrect Finish Day", "Date Error", 0);
						return 0;
					}
					double dn1 = datenum(y1, m1, d1, 0, 0, 0, 0);
					double dn2 = datenum(y2, m2, d2, 0, 0, 0, 0);

					if (dn2 < dn1)
					{
						MessageBox(NULL, "Incorrect Start and Finish Dates", "Date Error", 0);
						return 0;
					}
					sfddd.startYear		= y1;
					sfddd.startMonth	= m1;
					sfddd.startDay		= d1;
					sfddd.finishYear	= y2;
					sfddd.finishMonth	= m2;
					sfddd.finishDay		= d2;

				   if(sfddd.thisIsLocalTime)
				   {
						// 
						BOOL bTranslated;
						sfddd.localTimeOffsetHours = 
							(short)GetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, &bTranslated, false);
						if (!bTranslated)
							sfddd.localTimeOffsetHours = 0;
				   }

					return 1;
			   }
			   break;
           case IDOK :
			   {
				   //Нажимаем кнопку ОК для обработки всех файлов, находящихся в дирректории

					//if (
						SendMessage(hDlg,WM_COMMAND, IDC_TEST_START_FINISH_DATE,0) //	== 0)
						//return 0
						;
					

					GetDlgItemText(hDlg,IDC_DIRECTORY2, directory, 254);

					//hDlgModeless = NULL;
					//EndDialog( hDlg, IDCANCEL );

				// номер прибора
				BOOL bTranslated;
				sfddd.nPribor = 
					(short)GetDlgItemInt(hDlg, IDC_EDIT_INSTRUMENT_NUMBER, &bTranslated, false);
				if (!bTranslated)
				{
					MessageBox(NULL, "Incorrect Pribor Number", "Date Error", 0);
					return 0;
				}
					sfddd.nHowUseFilePath = 0;
//					createCommonFile();
//MessageBox(0,"1","12",0);
					SendMessage(hMainWnd, WM_COMMAND, ID_COMMON_DONE, 0);
			   }
               break;
           case IDCANCEL :
			   {
			     hDlgModeless = NULL;
                 EndDialog( hDlg, IDCANCEL );
			   }
               break;
         }
         break;

      default :
         return( FALSE );
  }
  return( TRUE );
}


void convert()
{
MessageBox(0, "convert", "convert", 
	MB_OK | MB_ICONINFORMATION);

	int d, mo, y, h, mi, s, milli, X, Y, Z;
	FILE *stream;

	const int n=256; // length of buffer string line
	char szBuff[n]; // buffer string line

	char szPath2[255];
	char *p, *p1, *p2;
	char ext[16];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}


		if(!feof(stream))
		{
			fgets(szBuff,n,stream);
			p1 = szBuff;
			d = atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла 1.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mo = atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла 2.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			y = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 4)
			{
				MessageBox(0, "Неверный формат файла 3.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла 4.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла 5.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла 6.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла 7.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла 8.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
		}
		fclose(stream);
		//////////////////////////////////////
		double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int yy = y - (y/100)*100;
		wsprintf(szPath2, "var%d%d_%d%d_%d.csv\0",
				d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, y);
		FILE *stream2;
		if ((stream2 = fopen(szPath2,"wt")) == NULL)
		{
		MessageBox(0, "Cannot open output file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		unsigned int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				d = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				mo = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				y = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				h = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				mi = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				s = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				milli = atoi(p1);

				double t, pre_t;
				if (i==0)
				{
					t = datenum(y, mo, d, h, mi, s, milli);
				}
				else
				{
					pre_t = t;
					t = datenum(y, mo, d, h, mi, s, milli);
					double delta_t = t - pre_t;

					// сравниваем время текущего тика new_time и время предыдущего тика pre_time

					if (delta_t > 85./86400000.)// если разница больше 85 миллисекунд
					{
						// пришедший символ уже из серии нового импульса
						//корректируем межимпульсный интервал
						delta_impuls_time = delta_t < delta_impuls_time ? delta_t : delta_impuls_time;
					}
					else
					{
						//корректируем время
						t = pre_t+delta_impuls_time;
						datevec(t, y, mo, d, h, mi, s, milli);
					}
				}


				p2 =  strchr(p1,',');
				p1 = p2+1;
				X = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Y = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Z = atoi(p1);

				int yy = y - (y/100)*100;

				fprintf(stream2,"%d%d.%d%d.%d%d %d:%d:%d,%d,%d,%d,%d\n", 
					d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, yy/10, yy-(yy/10)*10, 
					h,mi,s,milli,X,Y,Z);
				i++;
			}
		}
		MessageBox(0, szPath2, "Конверт успешен", 
			MB_OK | MB_ICONINFORMATION);
		fclose(stream2);
		fclose(stream);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}

void convertToMatlab()
{
MessageBox(0, "convert", "convert", 
	MB_OK | MB_ICONINFORMATION);

	int d, mo, y, h, mi, s, milli, X, Y, Z;
	double t;
	const int maxWindowLength=1024*8-1;
	int WindowIndex=0;
	int CurrentMinute;
	double 
		vX[maxWindowLength],
		vY[maxWindowLength],
		vZ[maxWindowLength];

	FILE *stream;

	const int n=256; // length of buffer string line
	char szBuff[n]; // buffer string line

	char szPath2[255];
	char *p, *p1, *p2;
	char ext[16];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}


		if(!feof(stream))
		{
			fgets(szBuff,n,stream);
			p1 = szBuff;
			d = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла день.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mo = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла месяц.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			y = atoi(p1) + 2000;
			p2 =  strchr(p1,' ');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла год.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			h= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла часы.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mi= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла минуты.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			s= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла секунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			milli= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 3)
			{
				MessageBox(0, "Неверный формат файла миллисекунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			X = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла X.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Y = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла Y.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Z = atoi(p1);
		}
		fclose(stream);
		//////////////////////////////////////
		double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int yy = y - (y/100)*100;

		wsprintf(szPath2, "vm%d%d_%d%d_%d.txt\0",
				d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, y);
		FILE *stream2;
		if ((stream2 = fopen(szPath2,"wt")) == NULL)
		{
		MessageBox(0, "Cannot open output file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		unsigned int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				d = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				mo = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				y = atoi(p1)+2000;

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				h = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				mi = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				s = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				milli = atoi(p1);

				t = datenum(y, mo, d, h, mi, s, milli);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				X = atoi(p1);
				vX[WindowIndex] = double(X);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Y = atoi(p1);
				vY[WindowIndex] = double(Y);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Z = atoi(p1);
				vZ[WindowIndex] = double(Z);



				if (i==0)
				{
					CurrentMinute = mi;
				}
				else
				{
					if (mi == CurrentMinute)
					{
						if (WindowIndex+1 < maxWindowLength)
							WindowIndex++;
					}
					else
					{
						double meanX, meanY, meanZ;
						meanX=0;meanY=0; meanZ=0;
						for (int j=0;j<WindowIndex;j++)
						{
							meanX += vX[j];
							meanY += vY[j];
							meanZ += vZ[j];

						}
						meanX /= WindowIndex+1;
						meanY /= WindowIndex+1;
						meanZ /= WindowIndex+1;
						///////////////////////////////////////////////////

						t = datenum(y, mo, d, h, mi, 0, 0);
						///////////////////////////////////////////////////
						fprintf(stream2,"%.8f %f %f %f\n", 
							t,meanX,meanY,meanZ);
						///////////////////////////////////////////////////
						///////////////////////////////////////////////////
						WindowIndex=0;
						CurrentMinute = mi;					
						///////////////////////////////////////////////////

						///////////////////////////////////////////////////

					}
				}

				i++;
			}
		}
		MessageBox(0, szPath2, "Конверт успешен", 
			MB_OK | MB_ICONINFORMATION);
		fclose(stream2);
		fclose(stream);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}

void convertToExcel()
{
MessageBox(0, "convert", "convert", 
	MB_OK | MB_ICONINFORMATION);

	int d, mo, y, h, mi, s, milli, X, Y, Z;
	double t;
	const int maxWindowLength=1024;
	int WindowIndex=0;
	int CurrentMinute;
	double 
		vX[maxWindowLength],
		vY[maxWindowLength],
		vZ[maxWindowLength];

	FILE *stream;

	const int n=256; // length of buffer string line
	char szBuff[n]; // buffer string line

	char szPath2[255];
	char *p, *p1, *p2;
	char ext[16];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}

		if(!feof(stream))
		{
			fgets(szBuff,n,stream);
			p1 = szBuff;
			d = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла день.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mo = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла месяц.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			y = atoi(p1) + 2000;
			p2 =  strchr(p1,' ');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла год.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			h= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла часы.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mi= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла минуты.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			s= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла секунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			milli= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 3)
			{
				MessageBox(0, "Неверный формат файла миллисекунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			X = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла X.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Y = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла Y.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Z = atoi(p1);
		}
		fclose(stream);
		//////////////////////////////////////
		double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int yy = y - (y/100)*100;

		wsprintf(szPath2, "vm%d%d_%d%d_%d.txt\0",
				d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, y);
		FILE *stream2;
		if ((stream2 = fopen(szPath2,"wt")) == NULL)
		{
		MessageBox(0, "Cannot open output file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		unsigned int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				d = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				mo = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				y = atoi(p1)+2000;

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				h = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				mi = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				s = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				milli = atoi(p1);

				t = datenum(y, mo, d, h, mi, s, milli)-datenum(1900,1,1,0,0,0,0)+2;

				p2 =  strchr(p1,',');
				p1 = p2+1;
				X = atoi(p1);
				vX[WindowIndex] = double(X);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Y = atoi(p1);
				vY[WindowIndex] = double(Y);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Z = atoi(p1);
				vZ[WindowIndex] = double(Z);

				if (i==0)
				{
					CurrentMinute = mi;
				}
				else
				{
					if (mi == CurrentMinute)
					{
						if (WindowIndex+1 < maxWindowLength)
							WindowIndex++;
					}
					else
					{
						double meanX, meanY, meanZ;
						meanX=0;meanY=0; meanZ=0;
						for (int j=0;j<WindowIndex;j++)
						{
							meanX += vX[j];
							meanY += vY[j];
							meanZ += vZ[j];

						}
						meanX /= WindowIndex+1;
						meanY /= WindowIndex+1;
						meanZ /= WindowIndex+1;
						///////////////////////////////////////////////////

						t = datenum(y, mo, d, h, mi, 0, 0);
						///////////////////////////////////////////////////
						fprintf(stream2,"%.8f %f %f %f\n", 
							t,meanX,meanY,meanZ);

						///////////////////////////////////////////////////
						///////////////////////////////////////////////////
						WindowIndex=0;
						CurrentMinute = mi;					
						///////////////////////////////////////////////////

						///////////////////////////////////////////////////

					}
				}

				i++;
			}
		}
		MessageBox(0, szPath2, "Конверт успешен", 
			MB_OK | MB_ICONINFORMATION);
		fclose(stream2);
		fclose(stream);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}
int convertToUvarov()
{
	int d, mo, y, h, mi, s, milli, X, Y, Z, year;
	double test_t, test_t0;
	int rez;
	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line
	char szPath2[255];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;
		FILE *stream;

		if (p)
		{
			rez = sscanf(p,"%s%d_%d_%d.csv",
				&szBuff, &d, &mo, &year);
			if (rez == 4 && rez != EOF)
			{
			}
			else
			{
				if ((stream = fopen(szPath,"rt")) == NULL)
				{
					MessageBox(0, "Cannot open input file.\n", "Import", 
						MB_OK | MB_ICONINFORMATION);
					return 0;
				}
				while (!feof(stream))
				{
					fgets(szBuff,n,stream);
					if (!feof(stream))
					{
						rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
							&d, &mo, &y, &h, &mi, &s, &milli, &X, &Y, &Z);
						if (rez == 10 && rez != EOF)
						{
							year = 2000 + y;
							break;
						}
					}
				}
				fclose(stream);
			}
		}

		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "convert to Uvarov", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		CreateDirectory("C:\\Variation\\uvarovFormatConverted",NULL);

		wsprintf(szPath2, "C:\\Variation\\uvarovFormatConverted\\%02d_%02d_%d.txt\0",
				d, mo, year);
		FILE *stream2;
		if ((stream2 = fopen(szPath2,"wt")) == NULL)
		{
		MessageBox(0, "Cannot open output file.\n", "convert to Uvarov", 
			MB_OK | MB_ICONINFORMATION);
			return 0;
		}

		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
					&d, &mo, &y, &h, &mi, &s, &milli, &X, &Y, &Z);
				if (rez == 10 && rez != EOF)
				{
					if (i==0/* && iFile==1*/)
					{
						test_t0 = datenum(y,mo,d,h,mi,s,milli);
					}
					else
					{
						test_t = datenum(y,mo,d,h,mi,s,milli);
						if (test_t > test_t0)
						{
							test_t0 = test_t;
						}
						else
						{
							char errstr[255];
							sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath, int((test_t0 - test_t)*3600.*24.));
							MessageBox(0,errstr,"import()",0);
						//	break;
						}
					}

					double secs;
					secs = double(h*3600+mi*60+s) + double(milli)/1000.0;
					///////////////////////////////////////////////////
					fprintf(stream2,"%.1f %d %d %d\n", 
						secs,X,Y,Z);
					i++;
				}
			}
		}
		fclose(stream);
		fclose(stream2);
		MessageBox(0, szPath2, "Конверт успешен", 
			MB_OK | MB_ICONINFORMATION);

	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
	return 1;
}



void convertToUvarov_old()
{
MessageBox(0, "convert", "convert", 
	MB_OK | MB_ICONINFORMATION);

	int d, mo, y, h, mi, s, milli, X, Y, Z;
	double t;
	const int maxWindowLength=1024;


	FILE *stream;

	const int n=256; // length of buffer string line
	char szBuff[n]; // buffer string line

	char szPath2[255];
	char *p, *p1, *p2;
	char ext[16];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}


		if(!feof(stream))
		{
			fgets(szBuff,n,stream);
			p1 = szBuff;
			d = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла день.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mo = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла месяц.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			y = atoi(p1) + 2000;
			p2 =  strchr(p1,' ');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла год.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			h= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла часы.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mi= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла минуты.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			s= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла секунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			milli= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 3)
			{
				MessageBox(0, "Неверный формат файла миллисекунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			X = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла X.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Y = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла Y.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Z = atoi(p1);
		}
		fclose(stream);
		//////////////////////////////////////
		double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int yy = y - (y/100)*100;

		wsprintf(szPath2, "%d%d_%d%d_%d.txt\0",
				d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, y);
		FILE *stream2;
		if ((stream2 = fopen(szPath2,"wt")) == NULL)
		{
		MessageBox(0, "Cannot open output file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		unsigned int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				d = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				mo = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				y = atoi(p1)+2000;

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				h = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				mi = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				s = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				milli = atoi(p1);

				t = datenum(y, mo, d, h, mi, s, milli);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				X = atoi(p1);
				//vX[WindowIndex] = double(X);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Y = atoi(p1);
				//vY[WindowIndex] = double(Y);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Z = atoi(p1);
				//vZ[WindowIndex] = double(Z);

				double secs;
				secs = double(h*3600+mi*60+s) + double(milli)/1000.0;
				///////////////////////////////////////////////////
				fprintf(stream2,"%.1f %d %d %d\n", 
					secs,X,Y,Z);

				///////////////////////////////////////////////////



				i++;
			}
		}
		MessageBox(0, szPath2, "Конверт успешен", 
			MB_OK | MB_ICONINFORMATION);
		fclose(stream2);
		fclose(stream);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}
void convertToMatlabOnSecond()
{
MessageBox(0, "convert", "convert", 
	MB_OK | MB_ICONINFORMATION);

	int d, mo, y, h, mi, s, milli, X, Y, Z;
	double t;
	const int maxWindowLength=1024;


	FILE *stream;

	const int n=256; // length of buffer string line
	char szBuff[n]; // buffer string line

	char szPath2[255];
	char *p, *p1, *p2;
	char ext[16];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}


		if(!feof(stream))
		{
			fgets(szBuff,n,stream);
			p1 = szBuff;
			d = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла день.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mo = atoi(p1);
			p2 =  strchr(p1,'.');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла месяц.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			y = atoi(p1) + 2000;
			p2 =  strchr(p1,' ');
			if (p2==NULL || p2-p1 != 2)
			{
				MessageBox(0, "Неверный формат файла год.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			h= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла часы.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			mi= atoi(p1);
			p2 =  strchr(p1,':');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла минуты.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			s= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 2)
			{
				MessageBox(0, "Неверный формат файла секунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			milli= atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 3)
			{
				MessageBox(0, "Неверный формат файла миллисекунды.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			X = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла X.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Y = atoi(p1);
			p2 =  strchr(p1,',');
			if (p2==NULL || p2-p1 > 6)
			{
				MessageBox(0, "Неверный формат файла Y.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Z = atoi(p1);
		}
		fclose(stream);
		//////////////////////////////////////
		double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int yy = y - (y/100)*100;

		wsprintf(szPath2, "vms%d%d_%d%d_%d.txt\0",
				d/10, d-(d/10)*10, mo/10, mo-(mo/10)*10, y);
		FILE *stream2;
		if ((stream2 = fopen(szPath2,"wt")) == NULL)
		{
		MessageBox(0, "Cannot open output file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		unsigned int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				d = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				mo = atoi(p1);

				p2 =  strchr(p1,'.');
				p1 = p2+1;
				y = atoi(p1)+2000;

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				h = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				mi = atoi(p1);

				p2 =  strchr(p1,':');
				p1 = p2+1;
				s = atoi(p1);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				milli = atoi(p1);

				t = datenum(y, mo, d, h, mi, s, milli);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				X = atoi(p1);
				//vX[WindowIndex] = double(X);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Y = atoi(p1);
				//vY[WindowIndex] = double(Y);

				p2 =  strchr(p1,',');
				p1 = p2+1;
				Z = atoi(p1);
				//vZ[WindowIndex] = double(Z);

				double secs;
				secs = double(h*3600+mi*60+s) + double(milli)/1000.0;
				///////////////////////////////////////////////////
				fprintf(stream2,"%.9f %d %d %d\n", 
					t,X,Y,Z);

				///////////////////////////////////////////////////


				i++;
			}
		}
		MessageBox(0, szPath2, "Конверт успешен", 
			MB_OK | MB_ICONINFORMATION);
		fclose(stream2);
		fclose(stream);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}

int import(bool bIsSignal2Checked)
{
//MessageBox(0, "", "import", 
//	MB_OK | MB_ICONINFORMATION);
WriteRaporto("import 1\n");
	int d, mo, y, h, mi, s, milli, X, Y, Z, year,
			d0,	mo0, y_0;
;
	double test_t, test_t0;
	int rez;
	int maxX, minX, 
		maxY, minY,
		maxZ, minZ;

	int nInstNumb;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line
	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && strcmp(ext, "csv") == 0)
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;

		if (p)
		{
			rez = sscanf(p,"%d_%d_%d_%d.csv",
				&nInstNumb, &year, &mo, &d);
			if (rez == 4 && rez != EOF)
			{
				char str[100];
				sprintf(str, "%d_%d_%d_%d.csv", nInstNumb, year, mo, d);
				MessageBox(0,str,"",0);

				year/=100;
				year*=100;
			}
			else
			{
				//MessageBox(0,"2000","",0);
				year = 2000;
			}
		}


		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
					&d, &mo, &y, &h, &mi, &s, &milli, &X, &Y, &Z);
				if (rez == 10 && rez != EOF)
				{
					len++;
					if (len==1)
					{
						maxX=minX=X;
						maxY=minY=Y;
						maxZ=minZ=Z;
					}
				}
			}
		}

		fclose(stream);

		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}

WriteRaporto("import 2\n");

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
			if (bIsSignal2Checked)
			{
				vDoc[iDoc].resize2(len);
				vDoc[iDoc].m_nInstrumentNumber2 = nInstNumb;
			}
			else
			{
				vDoc[iDoc].resize(len);
				vDoc[iDoc].m_nInstrumentNumber1 = nInstNumb;
			}
		}
WriteRaporto("import 3\n");

		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
					&d, &mo, &y, &h, &mi, &s, &milli, &X, &Y, &Z);
				if (rez == 10 && rez != EOF)
				{
					if (i==0/* && iFile==1*/)
					{
						test_t0 = datenum(y,mo,d,h,mi,s,milli);
					}
					else
					{
						test_t = datenum(y,mo,d,h,mi,s,milli);
						if (test_t > test_t0)
						{
							test_t0 = test_t;
						}
						else
						{
							char errstr[255];
							sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath, int((test_t0 - test_t)*3600.*24.));
							MessageBox(0,errstr,"import()",0);
						//	break;
						}
					}
					y+=year;

					tm.wDay				= d;
					tm.wMonth			= mo;
					tm.wYear			= y;
					tm.wHour			= h;
					tm.wMinute			= mi;
					tm.wSecond			= s;
					tm.wMilliseconds	= milli;

					//vDoc[0].m_vtime[i]=tm;
					//vDoc[1].m_vtime[i]=tm;
					//vDoc[2].m_vtime[i]=tm;

					double t = datenum(y, mo, d, h, mi, s, milli);

					maxX=maxX>X?maxX:X;
					minX=minX<X?minX:X;
					maxY=maxY>Y?maxY:Y;
					minY=minY<Y?minY:Y;
					maxZ=maxZ>Z?maxZ:Z;
					minZ=minZ<Z?minZ:Z;

					if (bIsSignal2Checked)
					{
						vDoc[0].m_t2[i]=t;
						vDoc[1].m_t2[i]=t;
						vDoc[2].m_t2[i]=t;

						vDoc[0].m_T2[i] = X;

						vDoc[1].m_T2[i] = Y;

						vDoc[2].m_T2[i] = Z;
					}
					else
					{
						vDoc[0].m_t[i]=t;
						vDoc[1].m_t[i]=t;
						vDoc[2].m_t[i]=t;

						vDoc[0].m_T[i] = X;

						vDoc[1].m_T[i] = Y;
						vDoc[2].m_T[i] = Z;
					}

					if (i == 0)
					{
						sprintf(szDate,"%d.%02d.%d \0", d, mo, y);
						d0 = d;
						mo0 = mo;
						y_0 = y;
					}
					if (i == len-1)
					{
						if (d != d0 || mo != mo0 || y != y_0)
						{
							char sz[125];
							sprintf(sz, "- %d.%02d.%d \0", d, mo, y);
							strcat(szDate, sz);
						}
					}
					i++;
				}
			}
		}
		fclose(stream);
WriteRaporto("import 4\n");

		//MessageBox(0,szDate,"szDate",0);

		strcpy(vDoc[0].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[1].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[2].m_sTitle,  "График активности геополяритонного поля  \0");

		strcat(vDoc[0].m_sTitle, szDate);
		strcat(vDoc[1].m_sTitle, szDate);
		strcat(vDoc[2].m_sTitle, szDate);

		strcat(vDoc[0].m_sTitle, "  X - компонента\0");
		strcat(vDoc[1].m_sTitle, "  Y - компонента\0");
		strcat(vDoc[2].m_sTitle, "  Z - компонента\0");

		char szInstNumb[63];
		sprintf(szInstNumb, " (прибор №%d)", nInstNumb);
		
		strcat(vDoc[0].m_sTitle, szInstNumb);
		strcat(vDoc[1].m_sTitle, szInstNumb);
		strcat(vDoc[2].m_sTitle, szInstNumb);

		strcpy(vDoc[0].m_sXLabel, "время");
		strcpy(vDoc[0].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[1].m_sXLabel, "время");
		strcpy(vDoc[1].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[2].m_sXLabel, "время");
		strcpy(vDoc[2].m_sYLabel, "Активность в отсчётах в сенкуду");

		if (bIsSignal2Checked)
		{
			vDoc[0].plot(vDoc[0].m_t2, vDoc[0].m_T2,vDoc[0].m_sTitle, "", "", true,true,1,false);
			vDoc[1].plot(vDoc[1].m_t2, vDoc[1].m_T2,vDoc[1].m_sTitle, "", "", true,true,1,false);
			vDoc[2].plot(vDoc[2].m_t2, vDoc[2].m_T2,vDoc[2].m_sTitle, "", "", true,true,1,false);
			//vDoc[0].plot(vDoc[0].m_t2, vDoc[0].m_T2,vDoc[0].m_sTitle, "", "", true,true,1,true);
			//vDoc[1].plot(vDoc[1].m_t2, vDoc[1].m_T2,vDoc[1].m_sTitle, "", "", true,true,1,true);
			//vDoc[2].plot(vDoc[2].m_t2, vDoc[2].m_T2,vDoc[2].m_sTitle, "", "", true,true,1,true);
		}
		else
		{
			vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T, vDoc[0].m_sTitle, "", "", true,true,0,false);
			vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T, vDoc[1].m_sTitle, "", "", true,true,0,false);
			vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T, vDoc[2].m_sTitle, "", "", true,true,0,false);
//			vDoc[0].ReinitVectorsPoints(minX, maxX);
//			vDoc[1].ReinitVectorsPoints(minY, maxY);
//			vDoc[2].ReinitVectorsPoints(minZ, maxZ);
		}
WriteRaporto("import 5\n");

//		vDoc[0].ReinitVectorsPoints();
//		vDoc[1].ReinitVectorsPoints();
//		vDoc[2].ReinitVectorsPoints();
//		MessageBox(0, szPath, "Импорт успешен", 
//			MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
WriteRaporto("import end\n");
	return 1;
}


int importExcelCommonFile(LPSELECTFILEDLGDATA lpSelectFileDlgData)
{
//MessageBox(0, "", "import", 
//	MB_OK | MB_ICONINFORMATION);
WriteRaporto("import 1\n");
	int d, mo, y, h, mi, s, milli,
		d0, mo0, y_0;
	double test_t, test_t0;
	double t, t1, t2, t0 = datenum(1900,1,1,0,0,0,0)-2;
	int rez;
	double maxX, minX, 
		maxY, minY,
		maxZ, minZ,
		X, Y, Z;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line
	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p /*&& strcmp(ext, "dat") == 0*/)
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;



		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%lf\t%lf\t%lf\t%lf\t%lf",
					&t1, &t2, &X, &Y, &Z);

				if (rez == 5 && rez != EOF)
				{
					len++;
					if (len==1)
					{
						maxX=minX=X;
						maxY=minY=Y;
						maxZ=minZ=Z;
					}
				}
			}
		}

		fclose(stream);

	char errstr[255];
	sprintf(errstr,"%d",len);
	MessageBox(0,errstr,"import()",0);

		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}

WriteRaporto("import 2\n");

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
			if (lpSelectFileDlgData->bIsSignal2Checked)
			{
				vDoc[iDoc].resize2(len);
			}
			else
			{
				vDoc[iDoc].resize(len);
			}
		}
WriteRaporto("import 3\n");

		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%lf\t%lf\t%lf\t%lf\t%lf",
					&t1, &t2, &X, &Y, &Z);

				if (rez == 5 && rez != EOF)
				{
					t = 0.5*(t1+t2);

					if (i==0/* && iFile==1*/)
					{
						test_t0 = t;
					}
					else
					{
						test_t = t;
						if (test_t > test_t0)
						{
							test_t0 = test_t;
						}
						else
						{
							char errstr[255];
							sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath, int((test_t0 - test_t)*3600.*24.));
							MessageBox(0,errstr,"import()",0);
						//	break;
						}
					}
					datevec(t+t0,y,mo,d,h,mi,s,milli);


					tm.wDay				= d;
					tm.wMonth			= mo;
					tm.wYear			= y;
					tm.wHour			= h;
					tm.wMinute			= mi;
					tm.wSecond			= s;
					tm.wMilliseconds	= milli;

					//vDoc[0].m_vtime[i]=tm;
					//vDoc[1].m_vtime[i]=tm;
					//vDoc[2].m_vtime[i]=tm;

//					double t = datenum(y, mo, d, h, mi, s, milli);
/*char errstr[255];
sprintf(errstr,"%f\t%d\t%d\t%d",t, X, Y, Z);
MessageBox(0,errstr,"import()",0);*/

					maxX=maxX>X?maxX:X;
					minX=minX<X?minX:X;
					maxY=maxY>Y?maxY:Y;
					minY=minY<Y?minY:Y;
					maxZ=maxZ>Z?maxZ:Z;
					minZ=minZ<Z?minZ:Z;

					if (lpSelectFileDlgData->bIsSignal2Checked)
					{
						vDoc[0].m_t2[i]=t+t0;
						vDoc[1].m_t2[i]=t+t0;
						vDoc[2].m_t2[i]=t+t0;

						vDoc[0].m_T2[i] = X;
						vDoc[1].m_T2[i] = Y;
						vDoc[2].m_T2[i] = Z;
					}
					else
					{
						vDoc[0].m_t[i]=t+t0;
						vDoc[1].m_t[i]=t+t0;
						vDoc[2].m_t[i]=t+t0;

						vDoc[0].m_T[i] = X;
						vDoc[1].m_T[i] = Y;
						vDoc[2].m_T[i] = Z;
					}
					if (i == 0)
					{
						sprintf(szDate,"%d.%02d.%d \0", d, mo, y);
						d0 = d;
						mo0 = mo;
						y_0 = y;
					}
					if (i == len-1)
					{
						if (d != d0 || mo != mo0 || y != y_0)
						{
							char sz[125];
							sprintf(sz, "- %d.%02d.%d \0", d, mo, y);
							strcat(szDate, sz);
						}
					}
					i++;
				}
			}
		}
		fclose(stream);
WriteRaporto("import 4\n");

		//MessageBox(0,szDate,"szDate",0);

		strcpy(vDoc[0].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[1].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[2].m_sTitle,  "График активности геополяритонного поля  \0");

		strcat(vDoc[0].m_sTitle, szDate);
		strcat(vDoc[1].m_sTitle, szDate);
		strcat(vDoc[2].m_sTitle, szDate);

		strcat(vDoc[0].m_sTitle, "  X - компонента\0");
		strcat(vDoc[1].m_sTitle, "  Y - компонента\0");
		strcat(vDoc[2].m_sTitle, "  Z - компонента\0");

		strcpy(vDoc[0].m_sXLabel, "время");
		strcpy(vDoc[0].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[1].m_sXLabel, "время");
		strcpy(vDoc[1].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[2].m_sXLabel, "время");
		strcpy(vDoc[2].m_sYLabel, "Активность в отсчётах в сенкуду");

		if (lpSelectFileDlgData->bIsSignal2Checked)
		{
			vDoc[0].plot(vDoc[0].m_t2, vDoc[0].m_T2,"Сигнал 2 X", "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[1].plot(vDoc[1].m_t2, vDoc[1].m_T2,"Сигнал 2 Y", "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[2].plot(vDoc[2].m_t2, vDoc[2].m_T2,"Сигнал 2 Z", "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
		}
		else
		{
			vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T, vDoc[0].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T, vDoc[1].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T, vDoc[2].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
		}
WriteRaporto("import 5\n");

//		vDoc[0].ReinitVectorsPoints();
//		vDoc[1].ReinitVectorsPoints();
//		vDoc[2].ReinitVectorsPoints();
//		MessageBox(0, szPath, "Импорт успешен", 
//			MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
WriteRaporto("import end\n");
	return 1;
}

int importFileForNNet(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData, vector<vector<double> > *pvectors, vector<string> * pnames)
{
//	int d, mo, y, h, mi, s, milli/*,
//		d0, mo0, y_0*/;
//	double /*t, t1, t2,*/ value/*, t0, t_denum;
	double value;

/*   switch (lpPolyotyDlgData->timeFormat)
   {
   case 0:// excel time
	   {
			t0 = datenum(1900,1,1,0,0,0,0)-2;
			t_denum = 1.0;
	   }
	   break;
   case 1:// matlab time
	   {
			t0 = 0;
			t_denum = 1.0;
	   }
	   break;
   case 2:// unix time
	   {
		   t0 = datenum(1970,1,1,0,0,0,0);
		   t_denum = 86400.0;
	   }
	   break;
   case 3:// db time
	   {
		   t0 = 0.0;
		   t_denum = 1.0;
	   }
	   break;
   }
   if(lpPolyotyDlgData->thisIsLocalTime)
   {
		// local time to Grinvich time
		t0 -= double(lpPolyotyDlgData->localTimeOffsetHours) / 24.0;
   }
   if(!lpPolyotyDlgData->bUse_timeFormat)
   {
		   t0 = 0.0;
		   t_denum = 1.0;
   }*/

	int delim = lpPolyotyDlgData->delim;
	//bool bTimeScale = true;
//	bool bTimeScale = lpPolyotyDlgData->bUse_timeFormat;
//	bool bUse_t2 = lpPolyotyDlgData->bUse_t2;
//	bool bUse_t1 = lpPolyotyDlgData->bUse_t1;

	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line

	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"importExcelCommonFileParam()", 0);
		return 0;
	}






//	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

/*	int viParam[3];
	if (lpPolyotyDlgData->notAddToExistingPlots)
	{
		viParam[0] = vDoc[0].m_vvCommonParams.vectSize();
		viParam[1] = vDoc[1].m_vvCommonParams.vectSize();
		viParam[2] = vDoc[2].m_vvCommonParams.vectSize();
	}
	else
	{
		viParam[0] = 0;
		viParam[1] = 0;
		viParam[2] = 0;
	}*/


	char * ch;

	if (p)
	{
		char * pp;
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			pp = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			pp = p2;
		if (p1 && !p2)
			pp = p1;
		if (!p1 && !p2)
			pp = szPath;
		else
			strncpy(lpPolyotyDlgData->filename, pp+1, p-pp-1);




		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}


		RECT rcClient;  // Client area of parent window 
		int cyVScroll;  // Height of scroll bar arrow 
		HWND hwndPB;    // Handle of progress bar 
		DWORD cb,		// Size of file and count of
		  cb_read = 0,  // bytes read 
		  cb_disp = 0;  // bytes displayed



		// Ensure that the common control DLL is loaded
		// and create a progress bar along the bottom of
		// the client area of the parent window. 
		// Base the height of the progress bar on the
		// height of a scroll bar arrow. 
		InitCommonControls(); 
		GetClientRect(sfddd.hwndParent, &rcClient); 
		cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
		hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
				 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
				 0, 0,
				 //rcClient.left, rcClient.bottom,
				 rcClient.right, cyVScroll, 
				 sfddd.hwndParent, (HMENU) 0, hInst, NULL); 

		// Gets the file descriptor associated with a stream.
		int fd = _fileno(stream);
		// Get the length of a file in bytes
		cb = _filelength(fd);



		// Set the range and increment of the progress
		// bar. 

		SendMessage(hwndPB, PBM_SETRANGE, 0,
					MAKELPARAM(0, cb / 2048)); 
		SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 



		// read and ignore first nLinesToIgnore lines
		int line = 0;
/*		while (lpPolyotyDlgData->bIgnoreFirstLines && line < lpPolyotyDlgData->nLinesToIgnore && !feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL)
			{
				line ++;
			}
		}*/


		char title[512];
		int nParams = 0, bytes_line, bytes_param;
		// if first line is line of headers
		if (lpPolyotyDlgData->bUse_Header && !feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);

				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}

				//MessageBox(0, szBuff, "", 0);
				p1 = szBuff;

				/*if ( bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title, "t1", 0);
					p1 = p2+1;
				}
				
				if ( bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title,"t2", 0);
					p1 = p2+1;
				}*/
				while ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, p2, title, 0);
					p1 = p2+1;
					nParams++;
				}
				if (p1-szBuff < bytes_line)
				{
					strcpy(title, p1);
					//MessageBox(0, title," p1-szBuff < bytes " , 0);
					nParams++;
				}
			}
		}
#if 0
		// scan all lines to know length of file
		int len = 0;
		while (!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff;

				/*if ( bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t1 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t1 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t2 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t2 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}

				if (bUse_t2 && bUse_t1)
					t = .5 * (t1+t2)/t_denum+t0;
				else
				{
					if (bUse_t1)
						t = t1/t_denum+t0;
					else
						dsequence(double(0.0), double(1.0),long(len));
				}*/

/*				if (!lpPolyotyDlgData->bUseStartFinishDate
					||
					(lpPolyotyDlgData->bUseStartFinishDate 
					&& t >= lpPolyotyDlgData->startTime
					&& t < lpPolyotyDlgData->finishTime + 1.0))
				{*/
					len++;
				//}
			}
		}

		fclose(stream);

/*		char errstr[255];
		sprintf(errstr,"len = %d nParams = %d bytes_line = %d", len, nParams, bytes_line);
		MessageBox(0,errstr,"import()",0);
*/
		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}
#endif

		// open the file again
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		// read and ignore first nLinesToIgnore lines
		line = 0;
/*		while (lpPolyotyDlgData->bIgnoreFirstLines && 
			line < lpPolyotyDlgData->nLinesToIgnore && 
			!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL)
			{
				line ++;
			}
		}*/
		// read the first line and define memory and titles for plots
		int ncol = 0;
		if (!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				//MessageBox(0, szBuff, "", 0);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff;

				/*if (bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title, "t1", 0);
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title,"t2", 0);
					p1 = p2+1;
				}*/
//				int idoc = 0;
//				int iParam = 0;
				ncol = 0;
				while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff < bytes_line )
				{
					ncol++;
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						bytes_param = p2-p1+1;
					}
					else
					{
						bytes_param = strlen(p1);
					}
					strncpy(title, p1, bytes_param);
					title[bytes_param-1] = '\0';
					//MessageBox(0, p2, title, 0);
					string s;
					s = title;
					pnames->push_back(s);

					//vdouble v;
					/*long iplot;
					if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
					{
	WriteRaporto("importExcelCommonFileParam 12\n");
						if ((!lpPolyotyDlgData->lpSelectFileDlgData->bIsSignal2Checked
							|| lpPolyotyDlgData->notAddToExistingPlots )
							&& vDoc[idoc].m_vvCommonParams.vectSize() < viParam[idoc]+iParam+1)
						{
	WriteRaporto("importExcelCommonFileParam 13\n");
							if (iParam == 0)		
								strcpy(vDoc[idoc].m_sTitle, title);

							vDoc[idoc].m_vvCommonParams.CreateNewVect();
							vDoc[idoc].m_vtCommonParams.CreateNewVect();
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->AddMsg(&v);
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->GetLastMsg().resize(len);
							
							vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->AddMsg(&v);
							vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg().resize(len);
					

							iplot = vDoc[idoc].plot(
								vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg(), 
								vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->GetLastMsg(),
								title, "", "", 
								bTimeScale,true,lpPolyotyDlgData->lpSelectFileDlgData->scaleModeX,false);
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->SetVectorData((long)iplot);
	WriteRaporto("importExcelCommonFileParam 14\n");					
						}
						else
						{
	WriteRaporto("importExcelCommonFileParam 15\n");
							vDoc[idoc].plot_2(iParam,len, title, "", "", 
								bTimeScale,true,lpPolyotyDlgData->lpSelectFileDlgData->scaleModeX,false);
	WriteRaporto("importExcelCommonFileParam 16\n");
						}
					}

					if(lpPolyotyDlgData->bDispOn3docs)
					{
						idoc++;
						if (idoc > 2)
						{
							idoc = 0;
							iParam++;
						}
					}
					else
						iParam++;
*/
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						p1 = p2+1;
					}
					else
						p1 = szBuff + bytes_line;
				}
			}
		}
		// alloc memory for ncols vectors
		int ncols = ncol;
		pvectors->resize(ncols);
#if 0
		for (ncol = 0; ncol < ncols; ncol++)
		{
			(*pvectors)[ncol].resize(len);
		}
#endif
		// read all lines and remember data in plot vectors
		int i = 0;
		while (!feof(stream))
		{
			if ((i == 0 && lpPolyotyDlgData->bUse_Header) || i > 0)
				ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff;

				/*if (bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t1 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t1 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t2 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t2 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}*/

				/*if (bUse_t2 && bUse_t1)
					t = .5 * (t1+t2)/t_denum+t0;
				else
				{
					if (bUse_t1)
						t = t1/t_denum+t0;
					else
						dsequence(double(0.0), double(1.0),long(len));
				}*/

			/*	if (!lpPolyotyDlgData->bUseStartFinishDate
					||
					(lpPolyotyDlgData->bUseStartFinishDate 
					&& t >= lpPolyotyDlgData->startTime
					&& t < lpPolyotyDlgData->finishTime + 1.0))*/
				{
					/*if (i == 0 || i == len-1)
					{
						datevec(t,y,mo,d,h,mi,s,milli);
					}*/

					//int idoc = 0;
					//int iParam = 0;
					int ncol = 0;


					while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff < bytes_line)
					{
						ncol++;
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							bytes_param = p2-p1+1;
						}
						else
						{
							bytes_param = strlen(p1);
						}
						strncpy(title, p1, bytes_param);
						title[bytes_param-1] = '\0';

						//if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
						//{
							//MessageBox(0, p1, title, 0);
							value = atof(title);
							if (value == 0.0)
								value = double(atoi(title));

							/*if (lpPolyotyDlgData->bUseIndexedTimeScale)
							{
								//vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = double(i)/86400.0;
								vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = double(i);
							}
							else
								vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = t;
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = value;
*/
#if 0
							(*pvectors)[ncol-1][i] = value;
#else
							(*pvectors)[ncol-1].push_back(value);
#endif
						//}
						/*if(lpPolyotyDlgData->bDispOn3docs)
						{
							idoc++;
							if (idoc > 2)
							{
								idoc = 0;
								iParam++;
							}
						}
						else
							iParam++;*/
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							p1 = p2+1;
						}
						else
							p1 = szBuff + bytes_line;
					}
					/*if (i == 0)
					{
						sprintf(szDate,"%d.%02d.%d \0", d, mo, y);
						d0 = d;
						mo0 = mo;
						y_0 = y;
					}
					if (i == len-1)
					{
						if (d != d0 || mo != mo0 || y != y_0)
						{
							char sz[125];
							sprintf(sz, "- %d.%02d.%d \0", d, mo, y);
							strcat(szDate, sz);
						}
					}*/
					i++;
				}
			}
		}
		fclose(stream);
		DestroyWindow(hwndPB);










//		vDoc[0].RefreshPlotsData();
//		vDoc[1].RefreshPlotsData();
//		vDoc[2].RefreshPlotsData();
		//MessageBox(0, szPath, "Импорт успешен", 
		//	MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
	if(szBuff)
		HeapFree(GetProcessHeap(), 0,szBuff);
	return 1;
}



int importExcelCommonFileParam(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData)
{
	int d, mo, y, h, mi, s, milli,
		d0, mo0, y_0;
	double t, t1, t2, value, t0, t_denum;

   switch (lpPolyotyDlgData->timeFormat)
   {
   case 0:// excel time
	   {
			t0 = datenum(1900,1,1,0,0,0,0)-2;
			t_denum = 1.0;
	   }
	   break;
   case 1:// matlab time
	   {
			t0 = 0;
			t_denum = 1.0;
	   }
	   break;
   case 2:// unix time
	   {
		   t0 = datenum(1970,1,1,0,0,0,0);
		   t_denum = 86400.0;
	   }
	   break;
   case 3:// db time
	   {
		   t0 = 0.0;
		   t_denum = 1.0;
	   }
	   break;
   }
   if(lpPolyotyDlgData->thisIsLocalTime)
   {
		// local time to Grinvich time
		t0 -= double(lpPolyotyDlgData->localTimeOffsetHours) / 24.0;
   }
   if(!lpPolyotyDlgData->bUse_timeFormat)
   {
		   t0 = 0.0;
		   t_denum = 1.0;
   }

	int delim = lpPolyotyDlgData->delim;
	//bool bTimeScale = true;
	bool bTimeScale = lpPolyotyDlgData->bUse_timeFormat;
	bool bUse_t2 = lpPolyotyDlgData->bUse_t2;
	bool bUse_t1 = lpPolyotyDlgData->bUse_t1;

	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line

	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"importExcelCommonFileParam()", 0);
		return 0;
	}






	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	int viParam[3];
	if (lpPolyotyDlgData->notAddToExistingPlots)
	{
		viParam[0] = vDoc[0].m_vvCommonParams.vectSize();
		viParam[1] = vDoc[1].m_vvCommonParams.vectSize();
		viParam[2] = vDoc[2].m_vvCommonParams.vectSize();
	}
	else
	{
		viParam[0] = 0;
		viParam[1] = 0;
		viParam[2] = 0;
	}


	char * ch;

	if (true /*p && strcmp(ext, "dat") == 0*/)
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;



		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}


		RECT rcClient;  // Client area of parent window 
		int cyVScroll;  // Height of scroll bar arrow 
		HWND hwndPB;    // Handle of progress bar 
		DWORD cb,		// Size of file and count of
		  cb_read = 0,  // bytes read 
		  cb_disp = 0;  // bytes displayed



		// Ensure that the common control DLL is loaded
		// and create a progress bar along the bottom of
		// the client area of the parent window. 
		// Base the height of the progress bar on the
		// height of a scroll bar arrow. 
		InitCommonControls(); 
		GetClientRect(sfddd.hwndParent, &rcClient); 
		cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
		hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
				 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
				 0, 0,
				 //rcClient.left, rcClient.bottom,
				 rcClient.right, cyVScroll, 
				 sfddd.hwndParent, (HMENU) 0, hInst, NULL); 

		// Gets the file descriptor associated with a stream.
		int fd = _fileno(stream);
		// Get the length of a file in bytes
		cb = _filelength(fd);



		// Set the range and increment of the progress
		// bar. 

		SendMessage(hwndPB, PBM_SETRANGE, 0,
					MAKELPARAM(0, 2*cb / 2048)); 
		SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 



		// read and ignore first nLinesToIgnore lines
		int line = 0;
		while (lpPolyotyDlgData->bIgnoreFirstLines && line < lpPolyotyDlgData->nLinesToIgnore && !feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL)
			{
				line ++;
			}
		}


		char title[512];
		int nParams = 0, bytes_line, bytes_param;
		// if first line is line of headers
		if (lpPolyotyDlgData->bUse_Header && !feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);

				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}

				p1 = szBuff;
				if ( bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title, "t1", 0);
					p1 = p2+1;
				}
				
				if ( bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title,"t2", 0);
					p1 = p2+1;
				}
				while ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, p2, title, 0);
					p1 = p2+1;
					nParams++;
				}
				if (p1-szBuff < bytes_line)
				{
					strcpy(title, p1);
					//MessageBox(0, title," p1-szBuff < bytes " , 0);
					nParams++;
				}
			}
		}

		// scan all lines to know length of file
		int len = 0;
		while (!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff;

				if ( bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t1 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t1 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t2 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t2 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
/*
				if (bUse_t2 && bUse_t1)
					t = .5 * (t1+t2)/t_denum+t0;
				else
				{
					if (bUse_t1)
						t = t1/t_denum+t0;
//					else
//						dsequence(double(0.0), double(1.0),long(len));
				}
*/
/*				if (!lpPolyotyDlgData->bUseStartFinishDate
					||
					(lpPolyotyDlgData->bUseStartFinishDate 
					&& t >= lpPolyotyDlgData->startTime
					&& t < lpPolyotyDlgData->finishTime + 1.0))
				{*/
					len++;
//				}
			}
		}

		fclose(stream);

/*		char errstr[255];
		sprintf(errstr,"len = %d nParams = %d bytes_line = %d", len, nParams, bytes_line);
		MessageBox(0,errstr,"import()",0);
*/
		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}


		// open the file again
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}

		// read and ignore first nLinesToIgnore lines
		line = 0;
		while (lpPolyotyDlgData->bIgnoreFirstLines && line < lpPolyotyDlgData->nLinesToIgnore && !feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL)
			{
				line ++;
			}
		}
		// read the first line and define memory and titles for plots
		if (!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				//MessageBox(0, szBuff, "", 0);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff;

				if (bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title, "t1", 0);
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, title,"t2", 0);
					p1 = p2+1;
				}
				int idoc = 0;

				int iParam = 0;
				int ncol = 0;
				while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff < bytes_line )
				{
					ncol++;
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						bytes_param = p2-p1+1;
					}
					else
					{
						bytes_param = strlen(p1);
					}
					strncpy(title, p1, bytes_param);
					title[bytes_param-1] = '\0';
					//MessageBox(0, p2, title, 0);

					vdouble v;
					long iplot;
					if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
					{
						if ((!lpPolyotyDlgData->lpSelectFileDlgData->bIsSignal2Checked
							|| lpPolyotyDlgData->notAddToExistingPlots )
							&& vDoc[idoc].m_vvCommonParams.vectSize() < viParam[idoc]+iParam+1)
						{
							if (iParam == 0)		
								strcpy(vDoc[idoc].m_sTitle, title);

							vDoc[idoc].m_vvCommonParams.CreateNewVect();
							vDoc[idoc].m_vtCommonParams.CreateNewVect();
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->AddMsg(&v);
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->GetLastMsg().resize(len);
							
							vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->AddMsg(&v);
							vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg().resize(len);
					

							iplot = vDoc[idoc].plot(
								vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg(), 
								vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->GetLastMsg(),
								title, "", "", 
								bTimeScale,true,lpPolyotyDlgData->lpSelectFileDlgData->scaleModeX,false);
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->SetVectorData((long)iplot);
						}
						else
						{
							vDoc[idoc].plot_2(/*viParam[idoc]+*/iParam,len, title, "", "", 
								bTimeScale,true,lpPolyotyDlgData->lpSelectFileDlgData->scaleModeX,false);
						}
					}


					if(lpPolyotyDlgData->bDispOn3docs)
					{
						idoc++;
						if (idoc > 2)
						{
							idoc = 0;
							iParam++;
						}
					}
					else
						iParam++;

					if ((p2 = strchr(p1,delim)) != NULL)
					{
						p1 = p2+1;
					}
					else
						p1 = szBuff + bytes_line;
				}
			}
		}

		// read all lines and remember data in plot vectors
		int i = 0;
		while (!feof(stream))
		{
			if ((i == 0 && lpPolyotyDlgData->bUse_Header) || i > 0)
				ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff;

				if (bUse_t1 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t1 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t1 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t2 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&y, &mo, &d, &h, &mi, &s);
							

							if (rez == 6 && rez != EOF)
							{
								milli = 0;
								t2 = datenum(y, mo, d, h, mi, s, milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}

				if (bUse_t2 && bUse_t1)
					t = .5 * (t1+t2)/t_denum+t0;
				else
				{
					if (bUse_t1)
						t = t1/t_denum+t0;
//					else
//						dsequence(double(0.0), double(1.0),long(len));
				}

				if (!lpPolyotyDlgData->bUseStartFinishDate
					||
					(lpPolyotyDlgData->bUseStartFinishDate 
					&& t >= lpPolyotyDlgData->startTime
					&& t < lpPolyotyDlgData->finishTime + 1.0))
				{
					if (i == 0 || i == len-1)
					{
						datevec(t,y,mo,d,h,mi,s,milli);
					}

					int idoc = 0;
					int iParam = 0;
					int ncol = 0;


					while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff < bytes_line)
					{
						ncol++;
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							bytes_param = p2-p1+1;
						}
						else
						{
							bytes_param = strlen(p1);
						}
						strncpy(title, p1, bytes_param);
						title[bytes_param-1] = '\0';

						if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
						{
							//MessageBox(0, p1, title, 0);
							value = atof(title);
							if (value == 0.0)
								value = double(atoi(title));

							if (lpPolyotyDlgData->bUseIndexedTimeScale)
							{
								//vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = double(i)/86400.0;
								vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = double(i);
							}
							else
								vDoc[idoc].m_vtCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = t;
							vDoc[idoc].m_vvCommonParams(viParam[idoc]+iParam)->GetLastMsg()[i] = value;
						}
						if(lpPolyotyDlgData->bDispOn3docs)
						{
							idoc++;
							if (idoc > 2)
							{
								idoc = 0;
								iParam++;
							}
						}
						else
							iParam++;
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							p1 = p2+1;
						}
						else
							p1 = szBuff + bytes_line;
					}
					if (i == 0)
					{
						sprintf(szDate,"%d.%02d.%d \0", d, mo, y);
						d0 = d;
						mo0 = mo;
						y_0 = y;
					}
					if (i == len-1)
					{
						if (d != d0 || mo != mo0 || y != y_0)
						{
							char sz[125];
							sprintf(sz, "- %d.%02d.%d \0", d, mo, y);
							strcat(szDate, sz);
						}
					}
					i++;
				}
			}
		}
		fclose(stream);
		DestroyWindow(hwndPB);










		vDoc[0].RefreshPlotsData();
		vDoc[1].RefreshPlotsData();
		vDoc[2].RefreshPlotsData();
		//MessageBox(0, szPath, "Импорт успешен", 
		//	MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
	if(szBuff)
		HeapFree(GetProcessHeap(), 0,szBuff);

	return 1;
}




int importExcelCommonFileHalfOfDay(LPSELECTFILEDLGDATA lpSelectFileDlgData)
{
//MessageBox(0, "", "import", 
//	MB_OK | MB_ICONINFORMATION);
WriteRaporto("import 1\n");
	int d, mo, y, h, mi, s, milli,
		d0, mo0, y_0;
	double test_t, test_t0;
	double t, t1, t2, t0 = datenum(1900,1,1,0,0,0,0)-2;
	int rez;
	double maxX, minX, 
		maxY, minY,
		maxZ, minZ,
		X, Y, Z,
		X2, Y2, Z2;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line
	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p /*&& strcmp(ext, "dat") == 0*/)
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;



		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf",
					&t1, &t2, &X, &Y, &Z, &X2, &Y2, &Z2);

				if (rez == 8 && rez != EOF)
				{
					len++;
					if (len==1)
					{
						maxX=minX=X;
						maxY=minY=Y;
						maxZ=minZ=Z;
					}
				}
			}
		}

		fclose(stream);

	char errstr[255];
	sprintf(errstr,"%d",len);
	MessageBox(0,errstr,"import()",0);

		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}

WriteRaporto("import 2\n");

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
		//	if (bIsSignal2Checked)
		//	{
				vDoc[iDoc].resize2(len);
		//	}
		//	else
		//	{
				vDoc[iDoc].resize(len);
		//	}
		}
WriteRaporto("import 3\n");

		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf",
					&t1, &t2, &X, &Y, &Z, &X2, &Y2, &Z2);

				if (rez == 8 && rez != EOF)
				{
					t = 0.5*(t1+t2);

					if (i==0/* && iFile==1*/)
					{
						test_t0 = t;
					}
					else
					{
						test_t = t;
						if (test_t > test_t0)
						{
							test_t0 = test_t;
						}
						else
						{
							char errstr[255];
							sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath, int((test_t0 - test_t)*3600.*24.));
							MessageBox(0,errstr,"import()",0);
						//	break;
						}
					}
					datevec(t+t0,y,mo,d,h,mi,s,milli);


					tm.wDay				= d;
					tm.wMonth			= mo;
					tm.wYear			= y;
					tm.wHour			= h;
					tm.wMinute			= mi;
					tm.wSecond			= s;
					tm.wMilliseconds	= milli;

					//vDoc[0].m_vtime[i]=tm;
					//vDoc[1].m_vtime[i]=tm;
					//vDoc[2].m_vtime[i]=tm;

//					double t = datenum(y, mo, d, h, mi, s, milli);
/*char errstr[255];
sprintf(errstr,"%f\t%d\t%d\t%d",t, X, Y, Z);
MessageBox(0,errstr,"import()",0);*/

					maxX=maxX>X?maxX:X;
					minX=minX<X?minX:X;
					maxY=maxY>Y?maxY:Y;
					minY=minY<Y?minY:Y;
					maxZ=maxZ>Z?maxZ:Z;
					minZ=minZ<Z?minZ:Z;

					//if (bIsSignal2Checked)
					//{
						vDoc[0].m_t2[i]=t+t0;
						vDoc[1].m_t2[i]=t+t0;
						vDoc[2].m_t2[i]=t+t0;

						vDoc[0].m_T2[i] = X2;
						vDoc[1].m_T2[i] = Y2;
						vDoc[2].m_T2[i] = Z2;
					//}
					//else
					//{
						vDoc[0].m_t[i]=t+t0;
						vDoc[1].m_t[i]=t+t0;
						vDoc[2].m_t[i]=t+t0;

						vDoc[0].m_T[i] = X;
						vDoc[1].m_T[i] = Y;
						vDoc[2].m_T[i] = Z;
					//}
					if (i == 0)
					{
						sprintf(szDate,"%d.%02d.%d \0", d, mo, y);
						d0 = d;
						mo0 = mo;
						y_0 = y;
					}
					if (i == len-1)
					{
						if (d != d0 || mo != mo0 || y != y_0)
						{
							char sz[125];
							sprintf(sz, "- %d.%02d.%d \0", d, mo, y);
							strcat(szDate, sz);
						}
					}

					i++;
				}
			}
		}
		fclose(stream);
WriteRaporto("import 4\n");

		//MessageBox(0,szDate,"szDate",0);

		strcpy(vDoc[0].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[1].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[2].m_sTitle,  "График активности геополяритонного поля  \0");

		strcat(vDoc[0].m_sTitle, szDate);
		strcat(vDoc[1].m_sTitle, szDate);
		strcat(vDoc[2].m_sTitle, szDate);

		strcat(vDoc[0].m_sTitle, "  X - компонента\0");
		strcat(vDoc[1].m_sTitle, "  Y - компонента\0");
		strcat(vDoc[2].m_sTitle, "  Z - компонента\0");

		strcpy(vDoc[0].m_sXLabel, "время");
		strcpy(vDoc[0].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[1].m_sXLabel, "время");
		strcpy(vDoc[1].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[2].m_sXLabel, "время");
		strcpy(vDoc[2].m_sYLabel, "Активность в отсчётах в сенкуду");
#if 0
		vDoc[0].ReinitVectorsPoints();
		vDoc[1].ReinitVectorsPoints();
		vDoc[2].ReinitVectorsPoints();
//#else
		vDoc[0].ReinitVectorsPoints(minX, maxX);
		vDoc[1].ReinitVectorsPoints(minY, maxY);
		vDoc[2].ReinitVectorsPoints(minZ, maxZ);
#endif
		//if (bIsSignal2Checked)
		//{
			vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T, vDoc[0].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T, vDoc[1].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T, vDoc[2].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);

			vDoc[0].plot(vDoc[0].m_t2, vDoc[0].m_T2,"Сигнал 2 X", "", "", true,true,1,false);
			vDoc[1].plot(vDoc[1].m_t2, vDoc[1].m_T2,"Сигнал 2 Y", "", "", true,true,1,false);
			vDoc[2].plot(vDoc[2].m_t2, vDoc[2].m_T2,"Сигнал 2 Z", "", "", true,true,1,false);
			
			vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T,"Сигнал 1 и 2 X", "", "", true,true,1,false);
			vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T,"Сигнал 1 и 2 Y", "", "", true,true,1,false);
			vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T,"Сигнал 1 и 2 Z", "", "", true,true,1,false);
			
			vDoc[0].plot_(vDoc[0].m_t2, vDoc[0].m_T2,"Сигнал 2 X", "", "", true,true,1,false);
			vDoc[1].plot_(vDoc[1].m_t2, vDoc[1].m_T2,"Сигнал 2 Y", "", "", true,true,1,false);
			vDoc[2].plot_(vDoc[2].m_t2, vDoc[2].m_T2,"Сигнал 2 Z", "", "", true,true,1,false);
		//}
		//else
		//{
		//}
WriteRaporto("import 5\n");

//		MessageBox(0, szPath, "Импорт успешен", 
//			MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
WriteRaporto("import end\n");
	return 1;
}




int importExcel(LPSELECTFILEDLGDATA lpSelectFileDlgData)
{
//MessageBox(0, "", "import", 
//	MB_OK | MB_ICONINFORMATION);
WriteRaporto("import 1\n");
	int d, mo, y, h, mi, s, milli, X, Y, Z,
		d0, mo0, y_0;
	double test_t, test_t0;
	double t, t_, t0 = datenum(1900,1,1,0,0,0,0)-2;
	bool toShift = false;
	if (IDOK == MessageBox( 0, "Сдвинуть ли шкалу времени на 2 часf назад?", "importExcel",
			  MB_OKCANCEL | MB_ICONINFORMATION ))
			  toShift = true;


	int rez;
	int maxX, minX, 
		maxY, minY,
		maxZ, minZ;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line
	char szDate[31];

	char *p1, *p2, *p;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p && (strcmp(ext, "dat") == 0 || strcmp(ext, "txt") == 0))
	{
		// sscan year from filename
		p1 = strrchr(szPath,'\\');
		p2 = strrchr(szPath,'/');

		if (p1 && p2)
			p = p1>p2 ? p1 : p2;
		if (!p1 && p2)
			p = p2;
		if (p1 && !p2)
			p = p1;
		if (!p1 && !p2)
			p = szPath;



		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%lf\t%d\t%d\t%d",
					&t, &X, &Y, &Z);

				if (rez == 4 && rez != EOF)
				{
					len++;
					if (len==1)
					{
						maxX=minX=X;
						maxY=minY=Y;
						maxZ=minZ=Z;
					}
				}
			}
		}

		fclose(stream);

	char errstr[255];
	sprintf(errstr,"%d",len);
	MessageBox(0,errstr,"import()",0);

		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}

WriteRaporto("import 2\n");

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
			if (lpSelectFileDlgData->bIsSignal2Checked)
			{
				vDoc[iDoc].resize2(len);
			}
			else
			{
				vDoc[iDoc].resize(len);
			}
		}
WriteRaporto("import 3\n");

		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%lf\t%d\t%d\t%d",
					&t_, &X, &Y, &Z);
				if (toShift)
					t = t_ - 2./24.;
				else
					t = t_;
				if (rez == 4 && rez != EOF)
				{
					if (i==0/* && iFile==1*/)
					{
						test_t0 = t;
					}
					else
					{
						test_t = t;
						if (test_t > test_t0)
						{
							test_t0 = test_t;
						}
						else
						{
							char errstr[255];
							sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath, int((test_t0 - test_t)*3600.*24.));
							MessageBox(0,errstr,"import()",0);
						//	break;
						}
					}
					datevec(t+t0,y,mo,d,h,mi,s,milli);


					tm.wDay				= d;
					tm.wMonth			= mo;
					tm.wYear			= y;
					tm.wHour			= h;
					tm.wMinute			= mi;
					tm.wSecond			= s;
					tm.wMilliseconds	= milli;

					//vDoc[0].m_vtime[i]=tm;
					//vDoc[1].m_vtime[i]=tm;
					//vDoc[2].m_vtime[i]=tm;

//					double t = datenum(y, mo, d, h, mi, s, milli);
/*char errstr[255];
sprintf(errstr,"%f\t%d\t%d\t%d",t, X, Y, Z);
MessageBox(0,errstr,"import()",0);*/

					maxX=maxX>X?maxX:X;
					minX=minX<X?minX:X;
					maxY=maxY>Y?maxY:Y;
					minY=minY<Y?minY:Y;
					maxZ=maxZ>Z?maxZ:Z;
					minZ=minZ<Z?minZ:Z;

					if (lpSelectFileDlgData->bIsSignal2Checked)
					{
						vDoc[0].m_t2[i]=t+t0;
						vDoc[1].m_t2[i]=t+t0;
						vDoc[2].m_t2[i]=t+t0;

						vDoc[0].m_T2[i] = X;
						vDoc[1].m_T2[i] = Y;
						vDoc[2].m_T2[i] = Z;
					}
					else
					{
						vDoc[0].m_t[i]=t+t0;
						vDoc[1].m_t[i]=t+t0;
						vDoc[2].m_t[i]=t+t0;

						vDoc[0].m_T[i] = X;
						vDoc[1].m_T[i] = Y;
						vDoc[2].m_T[i] = Z;
					}
					if (i == 0)
					{
						sprintf(szDate,"%d.%02d.%d \0", d, mo, y);
						d0 = d;
						mo0 = mo;
						y_0 = y;
					}
					if (i == len-1)
					{
						if (d != d0 || mo != mo0 || y != y_0)
						{
							char sz[125];
							sprintf(sz, "- %d.%02d.%d \0", d, mo, y);
							strcat(szDate, sz);
						}
					}

					i++;
				}
			}
		}
		fclose(stream);
WriteRaporto("import 4\n");

		//MessageBox(0,szDate,"szDate",0);

		strcpy(vDoc[0].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[1].m_sTitle,  "График активности геополяритонного поля  \0");
		strcpy(vDoc[2].m_sTitle,  "График активности геополяритонного поля  \0");

		strcat(vDoc[0].m_sTitle, szDate);
		strcat(vDoc[1].m_sTitle, szDate);
		strcat(vDoc[2].m_sTitle, szDate);

		strcat(vDoc[0].m_sTitle, "  X - компонента\0");
		strcat(vDoc[1].m_sTitle, "  Y - компонента\0");
		strcat(vDoc[2].m_sTitle, "  Z - компонента\0");

		strcpy(vDoc[0].m_sXLabel, "время");
		strcpy(vDoc[0].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[1].m_sXLabel, "время");
		strcpy(vDoc[1].m_sYLabel, "Активность в отсчётах в сенкуду");
		strcpy(vDoc[2].m_sXLabel, "время");
		strcpy(vDoc[2].m_sYLabel, "Активность в отсчётах в сенкуду");

		if (lpSelectFileDlgData->bIsSignal2Checked)
		{
			vDoc[0].plot(vDoc[0].m_t2, vDoc[0].m_T2,"Сигнал 2 X", "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[1].plot(vDoc[1].m_t2, vDoc[1].m_T2,"Сигнал 2 Y", "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[2].plot(vDoc[2].m_t2, vDoc[2].m_T2,"Сигнал 2 Z", "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
		}
		else
		{
			vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T, vDoc[0].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T, vDoc[1].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
			vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T, vDoc[2].m_sTitle, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
//			vDoc[0].ReinitVectorsPoints(minX, maxX);
//			vDoc[1].ReinitVectorsPoints(minY, maxY);
//			vDoc[2].ReinitVectorsPoints(minZ, maxZ);
		}
WriteRaporto("import 5\n");

//		vDoc[0].ReinitVectorsPoints();
//		vDoc[1].ReinitVectorsPoints();
//		vDoc[2].ReinitVectorsPoints();
//		MessageBox(0, szPath, "Импорт успешен", 
//			MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
WriteRaporto("import end\n");
	return 1;
}




void importMatlab()
{
MessageBox(0, "", "importMatlab", 
	MB_OK | MB_ICONINFORMATION);
	int d, mo, y, h, mi, s, milli;
	double t, 
		X, Y, Z,
		maxX, minX, 
		maxY, minY,
		maxZ, minZ;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line

	char *p, *p1, *p2;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p /*&& strcmp(ext, "txt") == 0*/)
	{
		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				len++;
			}
		}
		fclose(stream);

		//////////////////////////////////////

		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}

		if(!feof(stream))
		{
			fgets(szBuff,n,stream);

			p1 = szBuff;
			t = atof(p1);
			p2 =  strchr(p1,'\t');
			if (p2==NULL || p2-p1 > 17)
			{
				MessageBox(0, "Неверный формат файла t.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			X = atof(p1);
			p2 =  strchr(p1,'\t');
			if (p2==NULL || p2-p1 > 13)
			{
				MessageBox(0, "Неверный формат файла X.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Y = atof(p1);
			p2 =  strchr(p1,'\t');
			if (p2==NULL || p2-p1 > 13)
			{
				MessageBox(0, "Неверный формат файла Y.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
			    fclose(stream);
				return;
			}
			p1 = p2+1;
			Z = atof(p1);

			maxX = X;
			minX = X;
			maxY = Y;
			minY = Y;
			maxZ = Z;
			minZ = Z;
		}
		fclose(stream);
		//////////////////////////////////////


		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
			vDoc[iDoc].resize(len);
			vDoc[iDoc].m_Disp.resize(len);
		}
		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				t = atof(p1);
				datevec(t, y, mo, d, h, mi, s, milli);


				tm.wYear			= y;
				tm.wMonth			= mo;
				tm.wDay				= d;
				tm.wHour			= h;
				tm.wMinute			= mi;
				tm.wSecond			= s;
				tm.wMilliseconds	= milli;


				//vDoc[0].m_vtime[i]=tm;
				//vDoc[1].m_vtime[i]=tm;
				//vDoc[2].m_vtime[i]=tm;


				vDoc[0].m_t[i]=t;
				vDoc[1].m_t[i]=t;
				vDoc[2].m_t[i]=t;

				p2 =  strchr(p1,'\t');
				p1 = p2+1;
				vDoc[0].m_T[i] = X = atof(p1);//X
				maxX=maxX>X?maxX:X;
				minX=minX<X?minX:X;

				p2 =  strchr(p1,'\t');
				p1 = p2+1;
				vDoc[1].m_T[i]= Y = atof(p1);//Y
				maxY=maxY>Y?maxY:Y;
				minY=minY<Y?minY:Y;

				p2 =  strchr(p1,'\t');
				p1 = p2+1;
				vDoc[2].m_T[i]= Z = atof(p1);//Z
				maxZ=maxZ>Z?maxZ:Z;
				minZ=minZ<Z?minZ:Z;

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				vDoc[0].m_Disp[i] = X = atof(p1);//X

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				vDoc[1].m_Disp[i] = Y = atof(p1);//Y

				p2 =  strchr(p1,' ');
				p1 = p2+1;
				vDoc[2].m_Disp[i] = Z = atof(p1);//Z

				i++;
			}
		}
		fclose(stream);

//		vDoc[0].ReinitVectorsPoints(minX, maxX);
//		vDoc[1].ReinitVectorsPoints(minY, maxY);
//		vDoc[2].ReinitVectorsPoints(minZ, maxZ);

		vDoc[0].plot(vDoc[0].m_t, vDoc[0].m_T, "", "", "", true,true,0,false);
		vDoc[1].plot(vDoc[1].m_t, vDoc[1].m_T, "", "", "", true,true,0,false);
		vDoc[2].plot(vDoc[2].m_t, vDoc[2].m_T, "", "", "", true,true,0,false);

//		vDoc[0].ReinitVectorsPoints();
//		vDoc[1].ReinitVectorsPoints();
//		vDoc[2].ReinitVectorsPoints();
//		MessageBox(0, szPath, "Импорт успешен", 
//			MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}

void importEarthQuakes()
{
MessageBox(0, "", "importMatlab", 
	MB_OK | MB_ICONINFORMATION);
	int d, mo, y, h, mi, s, milli;
	double t;
//		X, Y, Z,
//		maxX, minX, 
//		maxY, minY,
//		maxZ, minZ;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line

	char *p/*, *p1, *p2*/;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p /*&& strcmp(ext, "txt") == 0*/)
	{
		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				len++;
			}
		}
		fclose(stream);

		

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
			vDoc[iDoc].resize(len);
		}
		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				//p1 = szBuff;
				double Lat, //  - географическая широта в градусах (северная).
					Lon,        //  - географическая долгота в градусах (восточная).
					H,          //  - глубина в километрах от уровня моря (<минус> - выше уровня моря). 
					Ks,         //  - класс  по амплитуде s-волны, по определению Федотова С.А.
					Ml;
				char Katalog;
				// Каталоги
				// F       - окончательный каталог.
				// O       - оперативный каталог.

				sscanf(szBuff,"%d/%d/%d %d:%d:%d.%d %lf %lf  %lf  %lf %lf %c",
					&y, &mo, &d, &h, &mi, &s, &milli, &Lat, &Lon, &H, &Ks, &Ml, &Katalog);

				t = datenum(y, mo, d, h, mi, s, milli);

				tm.wYear			= y;
				tm.wMonth			= mo;
				tm.wDay				= d;
				tm.wHour			= h;
				tm.wMinute			= mi;
				tm.wSecond			= s;
				tm.wMilliseconds	= milli;


				//vDoc[0].m_vtime[i]=tm;
				//vDoc[1].m_vtime[i]=tm;
				//vDoc[2].m_vtime[i]=tm;


				vDoc[0].m_t[i]=t;
				vDoc[1].m_t[i]=t;
				vDoc[2].m_t[i]=t;

				vDoc[0].m_T[i] = Ml;//X
				
				vDoc[1].m_T[i] = Ks;//Y
				
				vDoc[2].m_T[i] = H; //Z

				i++;
			}
		}
		fclose(stream);

		vDoc[0].ReinitVectorsPoints();
		vDoc[1].ReinitVectorsPoints();
		vDoc[2].ReinitVectorsPoints();


	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}

void printDailyRaport(bool toPrint)
{
	char startDate[15],
		finishDate[15],
		str[255];

	char filename_in[127];

	int y1=pdrdd.startYear,		y2=pdrdd.finishYear, 
		m1=pdrdd.startMonth,	m2=pdrdd.finishMonth, 
		d1=pdrdd.startDay,		d2=pdrdd.finishDay;

	wsprintf(startDate, "%d/%02d/%02d\0", y1, m1, d1);
	wsprintf(finishDate, "%d/%02d/%02d\0", y2, m2, d2);



	wsprintf(str, "Do you want to print dayly raport:\n\nstart date = %s  finish date = %s\n",
		startDate, finishDate);


	if (MessageBox(0, str, "printDailyRaport", 
		MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
		return;

	double dn1 = datenum(y1, m1, d1, 0, 0, 0, 0);
	double dn2 = datenum(y2, m2, d2, 0, 0, 0, 0);


	int iFile = 0;
	 HWND WndArray[3];
	 for (int i = 0; i<3; i++)
		 WndArray[i] = vhWndChild[i];

	TileWindows( hWndClient, MDITILE_VERTICAL, NULL, 3, WndArray );

	for (double dn=dn1; dn<=dn2 && !bAbortPrinting; dn+=1.0)
	{
		iFile++;
		int y, mo, d, h, mi, s, milli;
		datevec(dn, y, mo, d, h, mi, s, milli);
		wsprintf(filename_in,"\\%d_%d%d\\var%d%d_%d%d_%d.csv", y, mo/10, mo-10*(mo/10), d/10, d-10*(d/10), mo/10, mo-10*(mo/10), y);

		strcpy(szPath, directory);
		strcat(szPath, filename_in);
		bool toRead = true;

		if (!import(false))
		{
			char ser[511];
			wsprintf(ser, "Can't import file %s\n Do you want to skip daily raport printing?", szPath);

			if(MessageBox(0, ser, "Can not import file", 
				MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
			{
				toRead=false;				
			}
			else
			{
				return;
			}
		}
		if (toRead)
		{
			for (int i = 0; i < 3; i++)
			{
				switch(pdrdd.shPrintRaportType)
				{
				case 1:
					{
						vDoc[i].DeleteCalculatedPlots();
						vDoc[i].LogariphmOfSignal();
						vDoc[i].m_wInputSigalType = 1;// log of signal
						vDoc[i].WaveletEpsilonApply();
					}
					break;
				case 0:
					{
						vDoc[i].DeleteCalculatedPlots();
						vDoc[i].m_wInputSigalType = 0;// signal
						vDoc[i].WaveletEpsilonApply();
						vDoc[i].LogariphmOfFiltredSignal();
					}
					break;
				}

				vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
				vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
				RECT rect;
				GetClientRect(vhWndChild[i],&rect);
				InvalidateRect(vhWndChild[i],&rect, true);
#endif
			}
			if (toPrint)
				SendMessage(hMainWnd, WM_COMMAND, ID_FILE_PRINT, (LPARAM)0);
		}
		else
			toRead = true;

	}
}
extern double Median(double *p, int n); 
extern double Quantil(double qu, double *p, int len);
void createCommonFileOnProfils(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData)
{
	char 
		filename_out[255];

	strcpy(filename_out, "C:\\Variation/polet_common_profils.txt");
	int iFile = 0;
	int nPribor = 1;//sfddd.nPribor;
	const int n=1024; // length of buffer string line
	char szBuff_polet_line[n]; // buffer string line
	int 
		y1=lpPolyotyDlgData->startYear,		y2=lpPolyotyDlgData->finishYear, 
		m1=lpPolyotyDlgData->startMonth,	m2=lpPolyotyDlgData->finishMonth, 
		d1=lpPolyotyDlgData->startDay,		d2=lpPolyotyDlgData->finishDay;

	double dn1 = datenum(y1, m1, d1, 0, 0, 0, 0);
	double dn2 = datenum(y2, m2, d2, 0, 0, 0, 0);
	int X, Y, Z;

	fpos_t pos, new_profil_pos;

	int x,y,z;
	double xn, yn, zn;
	int u, prof;
	double t0_profil_excel,
		tend_profil_excel;

	const int n_pre = 50;

	int preU[n_pre],
		preProf[n_pre],

		n_profils = 0, // счётчик числа профилей
		U = -1, Prof = -1;

	for( int j = 0; j < n_pre; j++)
	{
		preU[j] = -1;
		preProf[j] = -1;
	}



	char *p1,*p2;
	int delim = lpPolyotyDlgData->delim;
	bool bUse_t2 = lpPolyotyDlgData->bUse_t2;
	double t_polet=-1.0, t_polet_previous, t1, t2, t0, t_denum;

	double t0_excel = datenum(1900,1,1,0,0,0,0)-2;

   switch (lpPolyotyDlgData->timeFormat)
   {
   case 0:// excel time
	   {
			t0 = datenum(1900,1,1,0,0,0,0)-2;
			t_denum = 1.0;
	   }
	   break;
   case 1:// matlab time
	   {
			t0 = 0;
			t_denum = 1.0;
	   }
	   break;
   case 2:// unix time
	   {
		   t0 = datenum(1970,1,1,0,0,0,0);
		   t_denum = 86400.0;
	   }
	   break;
   case 3:// db time
	   {
		   t0 = 0.0;
		   t_denum = 1.0;
	   }
	   break;
   }
   int Year, Mo, D, H, Mi, S, Milli;

		FILE *stream_polet;
		if ((stream_polet = fopen(szPath,"rt")) == NULL)
		{
			char err_str[255];
			sprintf(err_str, "Cannot open input file.\n %s", szPath);
			MessageBox(0, err_str, "createCommonFileWithVar", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}


		RECT rcClient;  // Client area of parent window 
		int cyVScroll;  // Height of scroll bar arrow 
		HWND hwndPB;    // Handle of progress bar 
		DWORD cb,		// Size of file and count of
		  cb_read = 0,  // bytes read 
		  cb_disp = 0;  // bytes displayed



		// Ensure that the common control DLL is loaded
		// and create a progress bar along the bottom of
		// the client area of the parent window. 
		// Base the height of the progress bar on the
		// height of a scroll bar arrow. 
		InitCommonControls(); 
		GetClientRect(sfddd.hwndParent, &rcClient); 
		cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
		hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
				 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
				 0, 0,
				 //rcClient.left, rcClient.bottom,
				 rcClient.right, cyVScroll, 
				 sfddd.hwndParent, (HMENU) 0, hInst, NULL); 

		// Gets the file descriptor associated with a stream.
		int fd = _fileno(stream_polet);
		// Get the length of a file in bytes
		cb = _filelength(fd);



		// Set the range and increment of the progress
		// bar. 

		SendMessage(hwndPB, PBM_SETRANGE, 0,
					MAKELPARAM(0, 2*cb / 2048)); 
		SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 



		FILE *stream2;
		if ((stream2 = fopen(filename_out,"wt")) == NULL)
		{
			MessageBox(0, "Cannot open output file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		long maxWindowLength=131072-1;

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		double *vX, *vY, *vZ;

		if ((vX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		double *pnX, *pnY, *pnZ;

		if ((pnX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((pnY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((pnZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		double *pX, *pY, *pZ;

		if ((pX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((pY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((pZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// read and ignore first nLinesToIgnore lines
		int line = 0;
		while (lpPolyotyDlgData->bIgnoreFirstLines && line < lpPolyotyDlgData->nLinesToIgnore && !feof((stream_polet)))
		{
			char * ch;
			ch = fgets(szBuff_polet_line,n,stream_polet);
			if( ch != NULL)
			{
				line ++;
			}
		}


		char title[512];
		int nParams = 0, bytes_line, bytes_param;
		// if first line is line of headers
		if (!feof(stream_polet))
		{
			char * ch;
			ch = fgets(szBuff_polet_line,n,stream_polet);
			if( ch != NULL && strlen(szBuff_polet_line) > 1)
			{
				bytes_line = strlen(ch);

				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}

				//MessageBox(0, szBuff, "", 0);
				p1 = szBuff_polet_line;

				if ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					fprintf(stream2,"%s", title);
					p1 = p2+1;
				}
				
				if ( bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					fprintf(stream2,"%c%s", delim, title);
					p1 = p2+1;
				}
				int ncol = 0;
				while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff_polet_line < bytes_line)
				{
					ncol++;
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						bytes_param = p2-p1+1;
					}
					else
					{
						bytes_param = strlen(p1);
					}
					strncpy(title, p1, bytes_param);
					title[bytes_param-1] = '\0';

					if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
					{
						//fprintf(stream2,"%c%s", delim, title);
					}
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						p1 = p2+1;
					}
					else
						p1 = szBuff_polet_line + bytes_line;
				}
				/*while ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, p2, title, 0);
					p1 = p2+1;
					nParams++;
				}
				if (p1-szBuff_polet_line < bytes_line)
				{
					strcpy(title, p1);
					//MessageBox(0, title," p1-szBuff < bytes " , 0);
					nParams++;
				}*/
			}
		}
		fprintf(stream2,"%s", "t0_profil_excel");
		fprintf(stream2,"%c%s", delim, "tend_profil_excel");

		fprintf(stream2,"%c%s", delim, "ro_xX");
		fprintf(stream2,"%c%s", delim, "ro_yY");
		fprintf(stream2,"%c%s", delim, "ro_zZ");

		fprintf(stream2,"%c%s", delim, "mediana_x");
		fprintf(stream2,"%c%s", delim, "mediana_y");
		fprintf(stream2,"%c%s", delim, "mediana_z");

		fprintf(stream2,"%c%s", delim, "mediana_X");
		fprintf(stream2,"%c%s", delim, "mediana_Y");
		fprintf(stream2,"%c%s", delim, "mediana_Z");

		fprintf(stream2,"%c%s", delim, "razmah_x");
		fprintf(stream2,"%c%s", delim, "razmah_y");
		fprintf(stream2,"%c%s", delim, "razmah_z");

		fprintf(stream2,"%c%s", delim, "razmah_X");
		fprintf(stream2,"%c%s", delim, "razmah_Y");
		fprintf(stream2,"%c%s", delim, "razmah_Z");

		fprintf(stream2,"%c%s", delim, "delta_x");
		fprintf(stream2,"%c%s", delim, "delta_y");
		fprintf(stream2,"%c%s", delim, "delta_z");

		fprintf(stream2, "%c%s%c%s%c%s\n",
			delim, "U", delim, "Prof", delim, "n_points_per_profil");
		fclose(stream2);
WriteRaporto("importExcelCommonFileParam 6\n");
		// scan all lines work with file
e_AgainScanTheFile:
		int len = 0,
			i_profile_point = 0; // счётчик номера точки в профиле
		bool first_break_of_profil = true;
		while (!feof(stream_polet))
		{
			// запоминаем позицию начала текущей строки
			if( fgetpos( stream_polet, &pos ) != 0 )
			{
				//perror( "fgetpos error" );
			}
			else
			{
			}
			char * ch;
			ch = fgets(szBuff_polet_line,n,stream_polet);
			if( ch != NULL && strlen(szBuff_polet_line) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0);
					SendMessage(sfddd.hwndParent,WM_NCPAINT, 0,0);
				}
				p1 = szBuff_polet_line;

				if ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t1 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&Year, &Mo, &D, &H, &Mi, &S);
							

							if (rez == 6 && rez != EOF)
							{
								Milli = 0;
								t1 = datenum(Year, Mo, D, H, Mi, S, Milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t2 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&Year, &Mo, &D, &H, &Mi, &S);
							

							if (rez == 6 && rez != EOF)
							{
								Milli = 0;
								t2 = datenum(Year, Mo, D, H, Mi, S, Milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}

				if (bUse_t2)
					t_polet = .5 * (t1+t2)/t_denum+t0;
				else
					t_polet = t1/t_denum+t0;

				if (!lpPolyotyDlgData->bUseStartFinishDate
					||
					(lpPolyotyDlgData->bUseStartFinishDate 
					&& t_polet >= lpPolyotyDlgData->startTime
					&& t_polet < lpPolyotyDlgData->finishTime + 1.0))
				{
					len++;	
					if (len == 1)
					{
						t_polet_previous = t_polet;
						//goto e_BeginVariations;
					}
					else
					{
						if (t_polet == t_polet_previous)
						{
							//goto e_RepeatVariations;
						}
						else
						{
							t_polet_previous = t_polet;
							//goto e_ContinueVariations;
						}
					}
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					// разбор строки
					int ncol = 0;
					while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff_polet_line < bytes_line)
					{
						ncol++;
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							bytes_param = p2-p1+1;
						}
						else
						{
							bytes_param = strlen(p1);
						}
						strncpy(title, p1, bytes_param);
						title[bytes_param-1] = '\0';
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						switch ( ncol )
						{
						case 1://x-polet
							{
								x = atoi(title);
							}
							break;
						case 2://y-polet
							{
								y = atoi(title);
							}
							break;
						case 3://z-polet
							{
								z = atoi(title);
							}
							break;
						case 4://xn-polet
							{
								xn = atof(title);
							}
							break;
						case 5://yn-polet
							{
								yn = atof(title);
							}
							break;
						case 6://zn-polet
							{
								zn = atof(title);
							}
							break;
						case 7://id
							{
							}
							break;
						case 8://u
							{
								u = atoi(title);
							}
							break;
						case 9://prof
							{
								prof = atoi(title);
							}
							break;
						case 10://x-var
							{
								X = atoi(title);
							}
							break;
						case 11://y-var
							{
								Y = atoi(title);
							}
							break;
						case 12://z-var
							{
								Z = atoi(title);
							}
							break;
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							p1 = p2+1;
						}
						else
							p1 = szBuff_polet_line + bytes_line;
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					// конец разбора строки
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					// определяем, что текущий профиль ранее ещё не обрабатывался
					bool CurrentIsnotPreviuusProfil = true;
					for(int j = 0; j < n_pre; j++)
					{
						CurrentIsnotPreviuusProfil &= !(u == preU[j]  && prof == preProf[j]);
					}
					if (CurrentIsnotPreviuusProfil)
					{
						if (i_profile_point == 0)
						{
							// запоминаем текущий профиль в список номеров предыдущих профилей
							for (int j = n_pre-1; j > 0; j--)
							{
								preU[j] = preU[j-1];
								preProf[j] = preProf[j-1];
							}
							preU[0] = U;
							preProf[0] = Prof;
							// если нулевая точка, запоминаем номер профиля и номер участка
							U = u;
							Prof = prof;
							t0_profil_excel = t_polet-t0_excel;
						}
						if (u == U && prof == Prof)
						{
							// обработка точки
							tend_profil_excel = t_polet-t0_excel;
							// заполнение векторов
							vX[i_profile_point] = X;
							vY[i_profile_point] = Y;
							vZ[i_profile_point] = Z;

							pX[i_profile_point] = x;
							pY[i_profile_point] = y;
							pZ[i_profile_point] = z;

							pnX[i_profile_point] = xn;
							pnY[i_profile_point] = yn;
							pnZ[i_profile_point] = zn;
							

							// счётчик точки внутри профиля
							i_profile_point++;
						}
						else
						{
							if (first_break_of_profil)
							{
								first_break_of_profil = false;
								//отмечаем запоминаем, когда профиль впервые прервался
								//если профиль прервался впервые, то текущая строа - это начало нового профиля
								new_profil_pos = pos;							
							}
						}
					}


				}
			}

		}
		// конец файла достигнут

		if(i_profile_point > 20)
		{
		
		// вычисляем коэффициент вариации между показаниями во время профиля и соответствующими вариациями
		double ro_xX = CorrelationCoefficient(i_profile_point,  pX, vX);
		double ro_yY = CorrelationCoefficient(i_profile_point,  pY, vY);
		double ro_zZ = CorrelationCoefficient(i_profile_point,  pZ, vZ);


		// вычисляем медиану каждого профиля
		double mediana_x = Median(pX, i_profile_point);
		double mediana_y = Median(pY, i_profile_point);
		double mediana_z = Median(pZ, i_profile_point);


		
		// делим каждый профиль на медиану
		for (int i = 0; i < i_profile_point; i++)
		{
			pX[i] /= mediana_x;
			pY[i] /= mediana_y;
			pZ[i] /= mediana_z;
		}

		// вычисляем размах каждого профиля, как разницу квантилей 0,9 и 0,1
		double razmah_x = Quantil(0.9,pX,i_profile_point) - Quantil(0.1,pX,i_profile_point);
		double razmah_y = Quantil(0.9,pY,i_profile_point) - Quantil(0.1,pY,i_profile_point);
		double razmah_z = Quantil(0.9,pZ,i_profile_point) - Quantil(0.1,pZ,i_profile_point);

		// делим каждый профиль на размах
		double 
			mean_px = 0.0,
			mean_py = 0.0,
			mean_pz = 0.0;
		for (int i = 0; i < i_profile_point; i++)
		{
			pX[i] /= razmah_x; mean_px += pX[i];
			pY[i] /= razmah_y; mean_py += pY[i];
			pZ[i] /= razmah_z; mean_pz += pZ[i];
		}
		mean_px /= i_profile_point;
		mean_py /= i_profile_point;
		mean_pz /= i_profile_point;
		// центрируем
		for (int i = 0; i < i_profile_point; i++)
		{
			pX[i] -= mean_px;
			pY[i] -= mean_py;
			pZ[i] -= mean_pz;
		}
		// проверяем получили ли мы значения нормированного профиля

		double 
			delta_x = 0.0,
			delta_y = 0.0,
			delta_z = 0.0;

		for (int i = 0; i < i_profile_point; i++)
		{
			delta_x += pow( (pX[i] - pnX[i]), 2.0);
			delta_y += pow( (pY[i] - pnY[i]), 2.0);
			delta_z += pow( (pZ[i] - pnZ[i]), 2.0);
		}
		delta_x /= i_profile_point;
		delta_y /= i_profile_point;
		delta_z /= i_profile_point;



		// вычисляем медиану вараций, соответствующих каждому профилю
		double mediana_X = Median(vX, i_profile_point);
		double mediana_Y = Median(vY, i_profile_point);
		double mediana_Z = Median(vZ, i_profile_point);

		// делим варации, соответствующие каждому профилю на медиану
		for (int i = 0; i < i_profile_point; i++)
		{
			vX[i] /= mediana_X;
			vY[i] /= mediana_Y;
			vZ[i] /= mediana_Z;
		}
		// вычисляем размах вараций, соответствующих каждому профилю, как разницу квантилей 0,9 и 0,1
		double razmah_X = Quantil(0.9,vX,i_profile_point) - Quantil(0.1,vX,i_profile_point);
		double razmah_Y = Quantil(0.9,vY,i_profile_point) - Quantil(0.1,vY,i_profile_point);
		double razmah_Z = Quantil(0.9,vZ,i_profile_point) - Quantil(0.1,vZ,i_profile_point);

		// делим варации, соответствующие каждому  на размах
		for (int i = 0; i < i_profile_point; i++)
		{
			vX[i] /= razmah_X;
			vY[i] /= razmah_Y;
			vZ[i] /= razmah_Z;
		}

		if ((stream2 = fopen(filename_out,"at")) == NULL)
		{
			MessageBox(0, "Cannot open output file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		fprintf(stream2,"%lf", t0_profil_excel);
		fprintf(stream2,"%c%lf", delim, tend_profil_excel);

		fprintf(stream2,"%c%lf", delim, ro_xX);
		fprintf(stream2,"%c%lf", delim, ro_yY);
		fprintf(stream2,"%c%lf", delim, ro_zZ);

		fprintf(stream2,"%c%lf", delim, mediana_x);
		fprintf(stream2,"%c%lf", delim, mediana_y);
		fprintf(stream2,"%c%lf", delim, mediana_z);

		fprintf(stream2,"%c%lf", delim, mediana_X);
		fprintf(stream2,"%c%lf", delim, mediana_Y);
		fprintf(stream2,"%c%lf", delim, mediana_Z);

		fprintf(stream2,"%c%lf", delim, razmah_x);
		fprintf(stream2,"%c%lf", delim, razmah_y);
		fprintf(stream2,"%c%lf", delim, razmah_z);

		fprintf(stream2,"%c%lf", delim, razmah_X);
		fprintf(stream2,"%c%lf", delim, razmah_Y);
		fprintf(stream2,"%c%lf", delim, razmah_Z);

		fprintf(stream2,"%c%lf", delim, delta_x);
		fprintf(stream2,"%c%lf", delim, delta_y);
		fprintf(stream2,"%c%lf", delim, delta_z);

		fprintf(stream2, "%c%d%c%d%c%d\n",
			delim, U, delim, Prof, delim,i_profile_point);


		n_profils++;

		fclose (stream2);
		}

		// возвращаемся на позицию начала первой строи нового профиля,
		// когда предыдущий профиль впервые прервался
		if(!first_break_of_profil)
		{
			if( fsetpos( stream_polet, &new_profil_pos ) != 0 )
			{
				//perror( "fsetpos error" );
			}
			else
			{
					goto e_AgainScanTheFile;
			}
		}


WriteRaporto("importExcelCommonFileParam 7\n");
	fclose(stream_polet);
	DestroyWindow(hwndPB);
	return;

}

void createCommonFileWithVar(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData)
{
	strcpy(directory,"C:\\Variation/var");

	char filename_in[127],
		filename_out[255];

	strcpy(filename_out, "C:\\Variation/polet_profils_with_var.txt");
	int rez;
	char szPath_in[255];
	FILE *stream_var;
	int iFile = 0;
	int nPribor = 1;//sfddd.nPribor;
	const int n=1024; // length of buffer string line
	char szBuff_polet_line[n]; // buffer string line
	char szBuff_var_line[n]; // buffer string line
	int 
		y1=lpPolyotyDlgData->startYear,		y2=lpPolyotyDlgData->finishYear, 
		m1=lpPolyotyDlgData->startMonth,	m2=lpPolyotyDlgData->finishMonth, 
		d1=lpPolyotyDlgData->startDay,		d2=lpPolyotyDlgData->finishDay;

	double dn1 = datenum(y1, m1, d1, 0, 0, 0, 0);
	double dn2 = datenum(y2, m2, d2, 0, 0, 0, 0);
	int X, Y, Z;
	double test_t,test_t0=0.0, pre_wrote_t2 = 0;


	unsigned int i = 0;
	int yy;
	char *p1,*p2;
	int delim = lpPolyotyDlgData->delim;
	bool bUse_t2 = lpPolyotyDlgData->bUse_t2;
	double t_polet=-1.0, t_polet_previous, t1, t2, t0, t_denum;
	bool toRead;double dn;
	double delta_impuls_time;

	double t0_excel = datenum(1900,1,1,0,0,0,0)-2;

   switch (lpPolyotyDlgData->timeFormat)
   {
   case 0:// excel time
	   {
			t0 = datenum(1900,1,1,0,0,0,0)-2;
			t_denum = 1.0;
	   }
	   break;
   case 1:// matlab time
	   {
			t0 = 0;
			t_denum = 1.0;
	   }
	   break;
   case 2:// unix time
	   {
		   t0 = datenum(1970,1,1,0,0,0,0);
		   t_denum = 86400.0;
	   }
	   break;
   case 3:// db time
	   {
		   t0 = 0.0;
		   t_denum = 1.0;
	   }
	   break;
   }
   int Year, Mo, D, H, Mi, S, Milli;

		FILE *stream_polet;
		if ((stream_polet = fopen(szPath,"rt")) == NULL)
		{
			char err_str[255];
			sprintf(err_str, "Cannot open input file.\n %s", szPath);
			MessageBox(0, err_str, "createCommonFileWithVar", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}


		RECT rcClient;  // Client area of parent window 
		int cyVScroll;  // Height of scroll bar arrow 
		HWND hwndPB;    // Handle of progress bar 
		DWORD cb,		// Size of file and count of
		  cb_read = 0,  // bytes read 
		  cb_disp = 0;  // bytes displayed



		// Ensure that the common control DLL is loaded
		// and create a progress bar along the bottom of
		// the client area of the parent window. 
		// Base the height of the progress bar on the
		// height of a scroll bar arrow. 
		InitCommonControls(); 
		GetClientRect(sfddd.hwndParent, &rcClient); 
		cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
		hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
				 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
				 0, 0,
				 //rcClient.left, rcClient.bottom,
				 rcClient.right, cyVScroll, 
				 sfddd.hwndParent, (HMENU) 0, hInst, NULL); 

		// Gets the file descriptor associated with a stream.
		int fd = _fileno(stream_polet);
		// Get the length of a file in bytes
		cb = _filelength(fd);



		// Set the range and increment of the progress
		// bar. 

		SendMessage(hwndPB, PBM_SETRANGE, 0,
					MAKELPARAM(0, 2*cb / 2048)); 
		SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 


WriteRaporto("importExcelCommonFileParam 5\n");

		FILE *stream2;
		if ((stream2 = fopen(filename_out,"wt")) == NULL)
		{
			MessageBox(0, "Cannot open output file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		// read and ignore first nLinesToIgnore lines
		int line = 0;
		while (lpPolyotyDlgData->bIgnoreFirstLines && line < lpPolyotyDlgData->nLinesToIgnore && !feof((stream_polet)))
		{
			char * ch;
			ch = fgets(szBuff_polet_line,n,stream_polet);
			if( ch != NULL)
			{
				line ++;
			}
		}


		char title[512];
		int nParams = 0, bytes_line, bytes_param;
		// if first line is line of headers
		if (!feof(stream_polet))
		{
			char * ch;
			ch = fgets(szBuff_polet_line,n,stream_polet);
			if( ch != NULL && strlen(szBuff_polet_line) > 1)
			{
				bytes_line = strlen(ch);

				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}

				//MessageBox(0, szBuff, "", 0);
				p1 = szBuff_polet_line;

				if ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					fprintf(stream2,"%s", title);
					p1 = p2+1;
				}
				
				if ( bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					fprintf(stream2,"%c%s", delim, title);
					p1 = p2+1;
				}
				int ncol = 0;
				while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff_polet_line < bytes_line)
				{
					ncol++;
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						bytes_param = p2-p1+1;
					}
					else
					{
						bytes_param = strlen(p1);
					}
					strncpy(title, p1, bytes_param);
					title[bytes_param-1] = '\0';

					if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
					{
						fprintf(stream2,"%c%s", delim, title);
					}
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						p1 = p2+1;
					}
					else
						p1 = szBuff_polet_line + bytes_line;
				}
				/*while ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, p2, title, 0);
					p1 = p2+1;
					nParams++;
				}
				if (p1-szBuff_polet_line < bytes_line)
				{
					strcpy(title, p1);
					//MessageBox(0, title," p1-szBuff < bytes " , 0);
					nParams++;
				}*/
			}
		}
		fprintf(stream2,"%c\"xx\"", delim);
		fprintf(stream2,"%c\"yy\"", delim);
		fprintf(stream2,"%c\"zz\"", delim);
		fprintf(stream2,"%c\"Вариация X на вариационной станции\"", delim);
		fprintf(stream2,"%c\"Вариация Y на вариационной станции\"", delim);
		fprintf(stream2,"%c\"Вариация Z на вариационной станции\"\n", delim);
		fclose(stream2);
WriteRaporto("importExcelCommonFileParam 6\n");
		// scan all lines to know length of file
		int len = 0;
		while (!feof(stream_polet))
		{
			char * ch;
			ch = fgets(szBuff_polet_line,n,stream_polet);
			if( ch != NULL && strlen(szBuff_polet_line) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
				}
				p1 = szBuff_polet_line;

				if ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t1 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&Year, &Mo, &D, &H, &Mi, &S);
							

							if (rez == 6 && rez != EOF)
							{
								Milli = 0;
								t1 = datenum(Year, Mo, D, H, Mi, S, Milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}
				if (bUse_t2 && (p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					if (lpPolyotyDlgData->timeFormat < 3)
						t2 = atof(title);
					else
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						if (lpPolyotyDlgData->timeFormat == 3)
						{
							int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
								&Year, &Mo, &D, &H, &Mi, &S);
							

							if (rez == 6 && rez != EOF)
							{
								Milli = 0;
								t2 = datenum(Year, Mo, D, H, Mi, S, Milli);
							}
						}
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					p1 = p2+1;
				}

				if (bUse_t2)
					t_polet = .5 * (t1+t2)/t_denum+t0;
				else
					t_polet = t1/t_denum+t0;

				if (!lpPolyotyDlgData->bUseStartFinishDate
					||
					(lpPolyotyDlgData->bUseStartFinishDate 
					&& t_polet >= lpPolyotyDlgData->startTime
					&& t_polet < lpPolyotyDlgData->finishTime + 1.0))
				{
					len++;	
					if (len == 1)
					{
						t_polet_previous = t_polet;
						goto e_BeginVariations;
					}
					else
					{
						if (t_polet == t_polet_previous)
						{
							goto e_RepeatVariations;
						}
						else
						{
							t_polet_previous = t_polet;
							goto e_ContinueVariations;
						}
					}
e_ContinuePolety:
					{
					}

				}
			}
		}
WriteRaporto("importExcelCommonFileParam 7\n");
	fclose(stream_polet);
	DestroyWindow(hwndPB);
	return;

e_BeginVariations:
	for (dn=dn1; dn<=dn2; dn+=1.0)
	{
		iFile++;
		int y, mo, d, h, mi, s, milli;
		datevec(dn, y, mo, d, h, mi, s, milli);

		wsprintf(filename_in,"\\%d_%d%d\\var%d%d_%d%d_%d.csv", y, mo/10, mo-10*(mo/10), d/10, d-10*(d/10), mo/10, mo-10*(mo/10), y);
		//MessageBox(0, filename_in, filename_out, 0);
		strcpy(szPath_in, directory);
		strcat(szPath_in, filename_in);
		toRead = true;

		if ((stream_var = fopen(szPath_in,"rt")) == NULL)
		{
			wsprintf(filename_in,"\\%d_%02d\\%d_%d_%02d_%02d.csv", y, mo, nPribor, y, mo, d);
			//MessageBox(0, filename_in, filename_out, 0);
			strcpy(szPath_in, directory);
			strcat(szPath_in, filename_in);
			if ((stream_var = fopen(szPath_in,"rt")) == NULL)
			{
				wsprintf(filename_in,"\\%d_%d_%02d_%02d.csv",  nPribor, y, mo, d);
				//MessageBox(0, filename_in, filename_out, 0);
				strcpy(szPath_in, directory);
				strcat(szPath_in, filename_in);
				if ((stream_var = fopen(szPath_in,"rt")) == NULL)
				{
					char ser[511];
					wsprintf(ser, "Can't open file %s\n Do you want to skip?", szPath_in);

					if(MessageBox(0, ser, "Can not open file", 
						MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
					{
						toRead=false;
						
					}
					else
					{
						break;
					}
				}
			}
		}
		
		if (toRead)
		{

			//////////////////////////////////////
			delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

			yy = y - (y/100)*100;


			i = 0;
			while (!feof(stream_var))
			{
				fgets(szBuff_var_line,n,stream_var);
				if (!feof(stream_var))
				{
					int _y;
					rez = sscanf(szBuff_var_line,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
						&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
					if (rez == 10 && rez != EOF)
					{
						if (i==0 && iFile==1)
						{
							test_t0 = datenum(y,mo,d,h,mi,s,milli);
						}
						else
						{
							test_t = datenum(y,mo,d,h,mi,s,milli);
							if (test_t > test_t0)
							{
								test_t0 = test_t;
							}
							else
							{
								char errstr[255];
								sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff_var_line, filename_in, int((test_t0 - test_t)*3600.*24.));
								MessageBox(0,errstr,"createCommonFile()",0);
							//	break;
							}
						}
					}

e_RepeatVariations:

					if (fabs(test_t0 - t_polet) > 0.9/86400)
					{
						if(test_t0 > t_polet)
							goto e_ContinuePolety;
					}
					else
					{
						if ((stream2 = fopen(filename_out,"at")) == NULL)
						{
							MessageBox(0, "Cannot open output file.\n", "Import", 
								MB_OK | MB_ICONINFORMATION);
							return;
						}
						fprintf(stream2,"%lf", t_polet-t0_excel);
						int ncol = 0;

						int xx,yy,zz; // полётные показания за вычетом вариаций
						while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff_polet_line < bytes_line)
						{
							ncol++;
							if ((p2 = strchr(p1,delim)) != NULL)
							{
								bytes_param = p2-p1+1;
							}
							else
							{
								bytes_param = strlen(p1);
							}
							strncpy(title, p1, bytes_param);
							title[bytes_param-1] = '\0';

							if (lpPolyotyDlgData->bUseAllCols || ncol <= lpPolyotyDlgData->nMaxCols)
							{
								fprintf(stream2,"%c%s", delim, title);
							}
							if ((p2 = strchr(p1,delim)) != NULL)
							{
								p1 = p2+1;
							}
							else
								p1 = szBuff_polet_line + bytes_line;

							switch (ncol)
							{
							case 1:
								{
									xx = atoi(title);
								}
								break;
							case 2:
								{
									yy = atoi(title);
								}
								break;
							case 3:
								{
									zz = atoi(title);
								}
								break;
							}
						}
						fprintf(stream2, "%c%d%c%d%c%d",
							delim, xx-X, delim, yy-Y, delim, zz-Z);
						fprintf(stream2, "%c%d%c%d%c%d\n",
							delim, X, delim, Y, delim, Z);
						fclose (stream2);
						goto e_ContinuePolety;
					}



e_ContinueVariations:
					{
					}



				}
			}
			fclose(stream_var);
		}
		else
			toRead = true;
	}
}
void createCommonFile()
{
	int global_max_X = 0;
	int global_max_Y = 0;
	int global_max_Z = 0;

	int nPribor = sfddd.nPribor;

	SYSTEMTIME global_max_Xt;
	SYSTEMTIME global_max_Yt;
	SYSTEMTIME global_max_Zt;

	char startDate[15],
		finishDate[15],
		str[255];

	char filename_in[1023],
		directory_out[1023],
		filename_out_temp[1023],
		filename_out[1023];

	char szPath_in[1023];

	double test_t,test_t0, pre_wrote_t2 = 0;
	bool bNewStringDone = true;

	wsprintf(startDate, "%d/%02d/%02d\0", sfddd.startYear, sfddd.startMonth, sfddd.startDay);
	wsprintf(finishDate, "%d/%02d/%02d\0", sfddd.finishYear, sfddd.finishMonth, sfddd.finishDay);

	char sPeriod[8], sFormat[8], sFormat2[8], sExt[8];
	switch(sfddd.shPeriodFlag)
	{
	case 0:
		{
			wsprintf(sPeriod,"1 sec");
		}
		break;
	case 1:
		{
			wsprintf(sPeriod,"1 min");
		}
		break;
	case 2:
		{
			wsprintf(sPeriod,"5 min");
		}
		break;
	case 3:
		{
			wsprintf(sPeriod,"15 min");
		}
		break;
	case 4:
		{
			wsprintf(sPeriod,"30 min");
		}
		break;
	case 5:
		{
			wsprintf(sPeriod,"1 hours");
		}
		break;
	case 6:
		{
			wsprintf(sPeriod,"2 hours");
		}
		break;
	case 7:
		{
			wsprintf(sPeriod,"3 hours");
		}
		break;
	case 8:
		{
			wsprintf(sPeriod,"4 hours");
		}
		break;
	case 9:
		{
			wsprintf(sPeriod,"6 hours");
		}
		break;
	case 10:
		{
			wsprintf(sPeriod,"8 hours");
		}
		break;
	case 11:
		{
			wsprintf(sPeriod,"12 hours");
		}
		break;
	case 12:
		{
			wsprintf(sPeriod,"24 hours");
		}
		break;
	case 13:
		{
			wsprintf(sPeriod,"2-12 hours");
		}
		break;
	}
	switch(sfddd.shFormatFlag)
	{
	case 0:
		{
			wsprintf(sFormat,"x");
			wsprintf(sFormat2,"excel");
			wsprintf(sExt,".txt");
		}
		break;
	case 1:
		{
			wsprintf(sFormat,"m");
			wsprintf(sFormat2,"matlab");
			wsprintf(sExt,".txt");
		}
		break;
	case 2:
		{
			wsprintf(sFormat,"v");
			wsprintf(sFormat2,"tezeyvar");
			wsprintf(sExt,".csv");
		}
		break;
	}
//	wsprintf(directory_out, "C:\\Variation\\CommonFiles\\%02d_%02d_%d", d2, m2, y2);
	wsprintf(directory_out, "%s\\CommonFiles", directory);

	switch (sfddd.nHowUseFilePath )
	{
	case 0:
	case 1:
	case 2:
		{
			wsprintf(filename_out_temp,"%d_c%s%s_%02d_%02d_%02d_%02d_%02d_%02d%s",
				nPribor,
				sFormat,
				sPeriod,
				sfddd.startYear-(sfddd.startYear/100)*100, sfddd.startMonth, sfddd.startDay, 
				sfddd.finishYear-(sfddd.finishYear/100)*100, sfddd.finishMonth, sfddd.finishDay,
				sExt);
		}
		break;
	}

	wsprintf(str, "Do you want to create common file:\n\nstart date = %s  finish date = %s\n\n period = %s\n\n time format = %s\n\n output filename = %s\n  directory = %s",
		startDate, finishDate, sPeriod, sFormat2, filename_out_temp, directory_out);


	if (MessageBox(0, str, "createCommonFile", 
		MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
		return;

	//if (!
		CreateDirectory(directory_out,NULL)//)
		//ErrorExit("CreateDirectory")
		;

	char delim = sfddd.delim;

	strcpy(filename_out, directory_out);
	strcat(filename_out, "\\");
	strcat(filename_out, filename_out_temp);

	double dn1 = datenum(sfddd.startYear, sfddd.startMonth, sfddd.startDay, 0, 0, 0, 0);
	double dn2 = datenum(sfddd.finishYear, sfddd.finishMonth, sfddd.finishDay, 0, 0, 0, 0);
	double start_t = dn1, finish_t = dn2;



	int X, Y, Z;
	int jj = 0, // rows on excel file
		kk = 1; // pages on excel file
	double t1, t2;
//	const int maxWindowLength=1024*8-1;
	long maxWindowLength=131072-1;
//	const int maxWindowLength=3600*25;
//	const unsigned long maxWindowLength=131072-1;

	long WindowIndex=0;

	int CurrentMinute,
//		preCurrentHour,
		CurrentHour,
		CurrentDay,
		CurrentMonth,
		CurrentYear;

	double 
		t_excel,
		t0_excel = datenum(1900,1,1,0,0,0,0)-2;

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	UINT SecsPerDay = 3600*24+1;

	double *vmeanX, *vmeanY, *vmeanZ;
	UINT ii;
	if(sfddd.bMeanPerDay)
	{
		if ((vmeanX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vmeanY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vmeanZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			vmeanX[ii] = 0.0;
			vmeanY[ii] = 0.0;
			vmeanZ[ii] = 0.0;
		}
	}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int *vn;

	if(sfddd.bMeanPerDay)
	{
		if ((vn = (int*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(int))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			vn[ii] = 0;
		}
	}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	double *vmeant;

	if(sfddd.bMeanPerDay)
	{
		if ((vmeant = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			vmeant[ii] = double(ii)/double(SecsPerDay-1);
		}
	}

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	double *vx, *vy, *vz, *vt;
	int len_of_dayly_file = 0;

	if(sfddd.bMeanPerDay)
	{
		if ((vt = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vx = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vy = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vz = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
	}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	double *vX, *vY, *vZ;

	if ((vX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}

	double *vYZ, *vZX, *vXY;
	if ((vYZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vZX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vXY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}

	double *vX_YZ, *vY_ZX, *vZ_XY;
	if ((vX_YZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vY_ZX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vZ_XY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}

	double *vX_XYZ, *vY_XYZ, *vZ_XYZ;
	if ((vX_XYZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vY_XYZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vZ_XYZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}

	double *vXYZ;
	if ((vXYZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}

	FILE *stream;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line


	FILE *stream2;
	if ((stream2 = fopen(filename_out,"wt")) == NULL)
	{
		MessageBox(0, filename_out, "Convert Common Cannot open output file.", 
			MB_OK | MB_ICONINFORMATION);
			return;
	}
	// write header
	fprintf(stream2,"time1%ctime2", delim);
	if(sfddd.bMin)
	{
		fprintf(stream2,"%cМинимум сигнала X за %s период %d.%d.%d - %d.%d.%d", delim, sPeriod, sfddd.startDay,sfddd.startMonth,sfddd.startYear,sfddd.finishDay,sfddd.finishMonth,sfddd.finishYear);
		fprintf(stream2,"%cМинимум сигнала Y за %s период %d.%d.%d - %d.%d.%d", delim, sPeriod, sfddd.startDay,sfddd.startMonth,sfddd.startYear,sfddd.finishDay,sfddd.finishMonth,sfddd.finishYear);
		fprintf(stream2,"%cМинимум сигнала Z за %s период %d.%d.%d - %d.%d.%d", delim, sPeriod, sfddd.startDay,sfddd.startMonth,sfddd.startYear,sfddd.finishDay,sfddd.finishMonth,sfddd.finishYear);
	}

	if(sfddd.bMedian)
	{
		fprintf(stream2,"%cМедиана сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cМедиана сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cМедиана сигнала Z за %s период", delim, sPeriod);
	}

	if(sfddd.bMean)
	{
		//fprintf(stream2,"%cmeanX_%s", delim, sPeriod);
		//fprintf(stream2,"%cmeanY_%s", delim, sPeriod);
		//fprintf(stream2,"%cmeanZ_%s", delim, sPeriod);
		fprintf(stream2,"%cСредняя сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cСредняя сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cСредняя сигнала Z за %s период", delim, sPeriod);
	}

	if(sfddd.bMax)
	{
		fprintf(stream2,"%cМаксимум сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cМаксимум сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cМаксимум сигнала Z за %s период", delim, sPeriod);
	}

	if(sfddd.bPolarization)
	{
		fprintf(stream2,"%cСтепень когерентности сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности сигнала Z за %s период", delim, sPeriod);
	}
	if(sfddd.bInvPolarization)
	{
		fprintf(stream2,"%cInvPolarizationX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationY_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationZ_%s", delim, sPeriod);
	}

	if(sfddd.bMinAngle)
	{
		fprintf(stream2,"%cМинимум отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleYX_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMedianAngle)
	{
		fprintf(stream2,"%cМедиана отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleYX_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMeanAngle)
	{
		fprintf(stream2,"%cСредняя отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleYX_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMaxAngle)
	{
		fprintf(stream2,"%cМаксимум отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleYX_%s", delim, sPeriod);
		}
	}

	if(sfddd.bPolarizationAngle)
	{
		fprintf(stream2,"%cСтепень когерентности отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleYX_%s", delim, sPeriod);
		}
	}

	if(sfddd.bInvPolarizationAngle)
	{
		fprintf(stream2,"%cInvPolarizationAngleYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleXY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleYX_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMinAngle3)
	{
		fprintf(stream2,"%cMinAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMinAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMinAngleZ_XY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMedianAngle3)
	{
		fprintf(stream2,"%cMedianAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMedianAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMedianAngleZ_XY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMeanAngle3)
	{
		fprintf(stream2,"%cMeanAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMeanAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMeanAngleZ_XY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMaxAngle3)
	{
		fprintf(stream2,"%cMaxAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMaxAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMaxAngleZ_XY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bPolarizationAngle3)
	{
		fprintf(stream2,"%cPolarizationAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cPolarizationAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cPolarizationAngleZ_XY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bInvPolarizationAngle3)
	{
		fprintf(stream2,"%cInvPolarizationAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZ_XY_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMinAngle4)
	{
		fprintf(stream2,"%cМинимум отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMedianAngle4)
	{
		fprintf(stream2,"%cМедиана отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMeanAngle4)
	{
		fprintf(stream2,"%cСредняя отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMaxAngle4)
	{
		fprintf(stream2,"%cМаксимум отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bPolarizationAngle4)
	{
		fprintf(stream2,"%cСтепень когерентности отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bInvPolarizationAngle4)
	{
		fprintf(stream2,"%cInvPolarizationAngleX_XYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleY_XYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZ_XYZ_%s", delim, sPeriod);

		if(sfddd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(sfddd.bMinXYZ)
	{
		fprintf(stream2,"Минимум модуля сигнала за %s период", delim, sPeriod);
	}
	if(sfddd.bMedianXYZ)
	{
		fprintf(stream2,"%cМедиана модуля сигнала за %s период", delim, sPeriod);
	}
	if(sfddd.bMeanXYZ)
	{
		fprintf(stream2,"%cСредняя модуля сигнала за %s период", delim, sPeriod);
	}
	if(sfddd.bMaxXYZ)
	{
		fprintf(stream2,"%cМаксимум модуля сигнала за %s период", delim, sPeriod);
	}
	if(sfddd.bPolarizationXYZ)
	{
		fprintf(stream2,"%cСтепень когерентности модуля сигнала за %s период", delim, sPeriod);
	}
	if(sfddd.bInvPolarizationXYZ)
	{
		fprintf(stream2,"%cInvPolarizationXYZ_%s", delim, sPeriod);
	}


	if (sfddd.shPeriodFlag == sfddd.shPeriodFlagHalfOfDay)
	{
		if(sfddd.bMin)
		{
			fprintf(stream2,"%cminX2_%s", delim, sPeriod);
			fprintf(stream2,"%cminY2_%s", delim, sPeriod);
			fprintf(stream2,"%cminZ2_%s", delim, sPeriod);
		}

		if(sfddd.bMedian)
		{
			fprintf(stream2,"%cmedianX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmedianY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmedianZ2_%s", delim, sPeriod);
		}

		if(sfddd.bMean)
		{
			fprintf(stream2,"%cmeanX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmeanY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmeanZ2_%s", delim, sPeriod);
		}

		if(sfddd.bMax)
		{
			fprintf(stream2,"%cmaxX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmaxY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmaxZ2_%s", delim, sPeriod);
		}

		if(sfddd.bPolarization)
		{
			fprintf(stream2,"%cPolarizationX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationY2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationZ2_%s", delim, sPeriod);
		}

		if(sfddd.bInvPolarization)
		{
			fprintf(stream2,"%cInvPolarizationX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationY2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationZ2_%s", delim, sPeriod);
		}

		if(sfddd.bMinAngle)
		{
			fprintf(stream2,"%cMinAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleYX2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMedianAngle)
		{
			fprintf(stream2,"%cMedianAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleYX2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMeanAngle)
		{
			fprintf(stream2,"%cMeanAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleYX2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMaxAngle)
		{
			fprintf(stream2,"%cMaxAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleYX2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bPolarizationAngle)
		{
			fprintf(stream2,"%cPolarizationAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleYX2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bInvPolarizationAngle)
		{
			fprintf(stream2,"%cInvPolarizationAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleYX2_%s", delim, sPeriod);
			}
		}


		if(sfddd.bMinAngle3)
		{
			fprintf(stream2,"%cMinAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZ_XY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMedianAngle3)
		{
			fprintf(stream2,"%cMedianAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZ_XY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMeanAngle3)
		{
			fprintf(stream2,"%cMeanAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZ_XY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMeanAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMaxAngle3)
		{
			fprintf(stream2,"%cMaxAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZ_XY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bPolarizationAngle3)
		{
			fprintf(stream2,"%cPolarizationAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZ_XY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bInvPolarizationAngle3)
		{
			fprintf(stream2,"%cInvPolarizationAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZ_XY2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXY_Z2_%s", delim, sPeriod);
			}
		}


		if(sfddd.bMinAngle4)
		{
			fprintf(stream2,"%cMinAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZ_XYZ2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMedianAngle4)
		{
			fprintf(stream2,"%cMedianAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZ_XYZ2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMeanAngle4)
		{
			fprintf(stream2,"%cMeanAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZ_XYZ2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMeanAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bMaxAngle4)
		{
			fprintf(stream2,"%cMaxAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZ_XYZ2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(sfddd.bPolarizationAngle4)
		{
			fprintf(stream2,"%cPolarizationAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZ_XYZ2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}
		if(sfddd.bInvPolarizationAngle4)
		{
			fprintf(stream2,"%cInvPolarizationAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZ_XYZ2_%s", delim, sPeriod);

			if(sfddd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}
		if(sfddd.bMinXYZ)
		{
			fprintf(stream2,"%cminXYZ2_%s", delim, sPeriod);
		}
		if(sfddd.bMedianXYZ)
		{
			fprintf(stream2,"%cmedianXYZ2_%s", delim, sPeriod);
		}
		if(sfddd.bMeanXYZ)
		{
			fprintf(stream2,"%cmeanXYZ2_%s", delim, sPeriod);
		}
		if(sfddd.bMaxXYZ)
		{
			fprintf(stream2,"%cmaxXYZ2_%s", delim, sPeriod);
		}
		if(sfddd.bPolarizationXYZ)
		{
			fprintf(stream2,"%cPolarizationXYZ2_%s", delim, sPeriod);
		}
		if(sfddd.bInvPolarizationXYZ)
		{
			fprintf(stream2,"%cInvPolarizationXYZ2_%s", delim, sPeriod);
		}
	}

	fprintf(stream2,"\n");


	fclose(stream2);

	int iFile = 0;
	int iFile2 = 0;

	switch (sfddd.nHowUseFilePath )
	{
	case 0:
		{
		}
		break;
	case 1:
		{
			dn2 = dn1;
		}
		break;
	case 2:
		{
			dn1 = 0;
			dn2 = sfddd.nFilesInDirectory-1;
		}
		break;
	}
					char str2[64];
					sprintf(str2,"startDate=%d/%d/%d\n finishDate = %d/%d/%d\0", sfddd.startYear, sfddd.startMonth, sfddd.startDay, sfddd.finishYear, sfddd.finishMonth, sfddd.finishDay);
					MessageBox(0,str2,"",0);

    RECT rcClient;  // Client area of parent window 
    int cyVScroll;  // Height of scroll bar arrow 
    HWND hwndPB;    // Handle of progress bar 

 

    // Ensure that the common control DLL is loaded
    // and create a progress bar along the bottom of
    // the client area of the parent window. 
    // Base the height of the progress bar on the
    // height of a scroll bar arrow. 
    InitCommonControls(); 
    GetClientRect(sfddd.hwndParent, &rcClient); 
    cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
    hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
	         (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
             0, 0,
             //rcClient.left, rcClient.bottom,
             rcClient.right, cyVScroll, 
             sfddd.hwndParent, (HMENU) 0, hInst, NULL); 

    // Set the range and increment of the progress
    // bar. 

    SendMessage(hwndPB, PBM_SETRANGE, 0,
                MAKELPARAM(0, int(dn2-dn1))); 
    SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 

	unsigned int i2 = 0;

	for (double dn=dn1; dn<=dn2; dn+=1.0)
	{
		iFile++;
		int y, mo, d, h, mi, s, milli;
		//if (sfddd.nHowUseFilePath == 0)
		//{
			datevec(dn, y, mo, d, h, mi, s, milli);

			wsprintf(filename_in,"\\%d_%d%d\\var%d%d_%d%d_%d.csv", y, mo/10, mo-10*(mo/10), d/10, d-10*(d/10), mo/10, mo-10*(mo/10), y);
			//MessageBox(0, filename_in, filename_out, 0);
			strcpy(szPath_in, directory);
			strcat(szPath_in, filename_in);
		//}
		bool toRead = true;

		if ((stream = fopen(szPath_in,"rt")) == NULL)
		{
			switch (sfddd.nHowUseFilePath )
			{
			case 0:
				{
					wsprintf(filename_in,"\\%d_%02d\\%d_%d_%02d_%02d.csv", y, mo, nPribor, y, mo, d);
					//MessageBox(0, filename_in, filename_out, 0);
					strcpy(szPath_in, directory);
					strcat(szPath_in, filename_in);
				}
				break;
			case 1:
				{
					strcpy(szPath_in, szPath);
				}
				break;
			case 2:
				{
					strcpy(szPath_in, sfddd.vFileNames[int(dn)]);
					//MessageBox(0, szPath_in, "", 0);
				}
				break;
			}
			/*if (sfddd.usePathIn)
			{
				strcpy(szPath_in, szPath);
			}
			else
			{
				wsprintf(filename_in,"\\%d_%02d\\%d_%d_%02d_%02d.csv", y, mo, nPribor, y, mo, d);
				//MessageBox(0, filename_in, filename_out, 0);
				strcpy(szPath_in, directory);
				strcat(szPath_in, filename_in);
			}*/
			if ((stream = fopen(szPath_in,"rt")) == NULL)
			{
				wsprintf(filename_in,"\\%d_%d_%02d_%02d.csv",  nPribor, y, mo, d);
				//MessageBox(0, filename_in, filename_out, 0);
				strcpy(szPath_in, directory);
				strcat(szPath_in, filename_in);
				if ((stream = fopen(szPath_in,"rt")) == NULL)
				{
					char ser[511];
					wsprintf(ser, "Can't open file %s\n Do you want to skip?", szPath_in);

					if(MessageBox(0, ser, "Can not open file", 
						MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
					{
						toRead=false;
						
					}
					else
					{
						break;
					}
				}
			}
		}
		
		if (toRead)
		{

			//////////////////////////////////////
			double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

			int yy = y - (y/100)*100;


			FILE *stream2;
			if ((stream2 = fopen(filename_out,"at")) == NULL)
			{
				MessageBox(0, "Cannot open output file.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
				return;
			}
			unsigned int i = 0;
			while (!feof(stream))
			{
				fgets(szBuff,n,stream);
				if (!feof(stream))
				{
					int _y;int rez;int rezWaited;
					switch (sfddd.fileFormat)
					{
					case 0:
						{
							rez = sscanf(szBuff,"%lf\t%d\t%d\t%d\t%d",
								&t_excel, &X, &Y, &Z);
							rezWaited = 4;
							if(sfddd.thisIsLocalTime)
								 t_excel -= 
								 double(sfddd.localTimeOffsetHours) / 24.0;

							datevec(t_excel+t0_excel,y,mo,d,h,mi,s,milli);
						}
						break;
					case 1:
						{
							rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
								&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
							rezWaited = 10;

							if (sfddd.nHowUseFilePath == 1)
								y = _y+ (y/100)*100;
							if (sfddd.nHowUseFilePath == 2)
								y = _y + 2000;
						}
						break;
					}					
					if (rez == rezWaited && rez != EOF)
					{
						if (i==0 && iFile==1)
						{
							switch (sfddd.fileFormat)
							{
							case 0:
								{
									test_t0 = t_excel + t0_excel;
								}
								break;
							case 1:
								{
									test_t0 = datenum(y,mo,d,h,mi,s,milli);
								}
								break;
							}
						}
						else
						{
							switch (sfddd.fileFormat)
							{
							case 0:
								{
									test_t = t_excel + t0_excel;
								}
								break;
							case 1:
								{
									test_t = datenum(y,mo,d,h,mi,s,milli);
								}
								break;
							}
							if (test_t > test_t0)
							{
								test_t0 = test_t;
							}
							else
							{
								char errstr[255];
								sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд", szBuff, szPath_in, int((test_t0 - test_t)*3600.*24.));
								MessageBox(0,errstr,"createCommonFile()",0);
							//	break;
							}
						}
						if (test_t0 >= start_t && test_t0 < finish_t+1.0)
						{
						if(sfddd.bMeanPerDay)
						{
							vt[i] = test_t0 - floor(test_t0);
							vx[i] = X;						
							vy[i] = Y;
							vz[i] = Z;
							len_of_dayly_file++;
						}

						if(global_max_X < X)
						{
							global_max_X = X;
							global_max_Xt.wYear = y;
							global_max_Xt.wMonth = mo;
							global_max_Xt.wDay = d;
							global_max_Xt.wHour = h;
							global_max_Xt.wMinute = mi;
							global_max_Xt.wSecond = s;
						}
						if(global_max_Y < Y)
						{
							global_max_Y = Y;
							global_max_Y = Y;
							global_max_Yt.wYear = y;
							global_max_Yt.wMonth = mo;
							global_max_Yt.wDay = d;
							global_max_Yt.wHour = h;
							global_max_Yt.wMinute = mi;
							global_max_Yt.wSecond = s;

						}
						if(global_max_Z < Z)
						{
							global_max_Z = Z;
							global_max_Zt.wYear = y;
							global_max_Zt.wMonth = mo;
							global_max_Zt.wDay = d;
							global_max_Zt.wHour = h;
							global_max_Zt.wMinute = mi;
							global_max_Zt.wSecond = s;
						}


						vX[WindowIndex] = double(X);
						vY[WindowIndex] = double(Y);
						vZ[WindowIndex] = double(Z);

						int mean_min = 1,
							mean_hour = 1;
						switch(sfddd.shPeriodFlag)
						{
						case 0:mean_min=0; break;
						case 1:mean_min=1; break;
						case 2:mean_min=5; break;
						case 3:mean_min=15;break;
						case 4:mean_min=30;break;
						}
						switch(sfddd.shPeriodFlag)
						{
						case 5:mean_hour=1; break;
						case 6:mean_hour=2; break;
						case 7:mean_hour=3; break;
						case 8:mean_hour=4; break;
						case 9:mean_hour=6; break;
						case 10:mean_hour=8; break;
						case 11:mean_hour=12; break;
						case 12:mean_hour=24; break;
						case 13:mean_hour=12; break;
						}
						switch(sfddd.shPeriodFlag)
						{
						case 0:// 1 sec - without any meaning
							{	
								if (sfddd.shFormatFlag !=2)// excel or matlab format
								{
									///////////////////////////////////////////////////
									t2 = datenum(y, mo, d, h, mi, s, milli);
									if (sfddd.shFormatFlag == 0)// excel format
									{
										t2 -= t0_excel;
										jj++;
										if (sfddd.bToCutPagesExcel && jj > 65536 - 1)
										{
											jj = 0;
											kk++;

											fclose(stream2);


											wsprintf(filename_out_temp,"%d_c%s%s_%02d_%02d_%02d_%02d_%02d_%02d.part%d%s",
												nPribor,												
												sFormat,
												sPeriod,
												sfddd.startYear-(sfddd.startYear/100)*100, sfddd.startMonth, sfddd.startDay, 
												sfddd.finishYear-(sfddd.finishYear/100)*100, sfddd.finishMonth, sfddd.finishDay,
												kk,
												sExt);

											strcpy(filename_out, directory_out);
											strcat(filename_out, "\\");
											strcat(filename_out, filename_out_temp);


											if ((stream2 = fopen(filename_out,"wt")) == NULL)
											{
												
												MessageBox(0, "Cannot open output file.\n", "Import", 
													MB_OK | MB_ICONINFORMATION);
												return;
											}

										}
										///////////////////////////////////////////////////
										fprintf(stream2,"%.8f\t%d\t%d\t%d\n", 
											t2,X,Y,Z);
										///////////////////////////////////////////////////

									}
									else
									{
										///////////////////////////////////////////////////
										fprintf(stream2,"%.8f %d %d %d\n", 
											t2,X,Y,Z);
										///////////////////////////////////////////////////
									}
								}
								else// tezeyvar format
								{
									fprintf(stream2,szBuff);
								}
							}
							break;
						case 1:
						case 2:
						case 3:
						case 4:
						case 5:
						case 6:
						case 7:
						case 8:
						case 9:
						case 10:
						case 11:
						case 12:
						case 13:
							{						
								//if (i==0 && iFile==1)
								if (i2==0)
								{
									//CurrentMinute	= mi;
									CurrentMinute	= (mi/mean_min)*mean_min;
									//CurrentHour		= h;
									CurrentHour		= (h/mean_hour)*mean_hour;
									//preCurrentHour	= CurrentHour;
									CurrentDay		= d;
									CurrentMonth	= mo;
									CurrentYear		= y;
								}
								else
								{
									bool bWindowFlag = true;
									if (sfddd.shPeriodFlag >= sfddd.shPeriodFlagMinStart 
										&& sfddd.shPeriodFlag <= sfddd.shPeriodFlagMinEnd)
									{
										bWindowFlag = 
											mi >= CurrentMinute	&&
											mi < CurrentMinute+mean_min &&
											CurrentHour		== h		&&
											CurrentDay		== d		&&
											CurrentMonth	== mo		&&
											CurrentYear		== y;
									}
									else
									{
										if (sfddd.shPeriodFlag >= sfddd.shPeriodFlagHoursStart && 
											sfddd.shPeriodFlag <= sfddd.shPeriodFlagHalfOfDay)
										{
											bWindowFlag = 
												h >= CurrentHour	&&
												h < CurrentHour + mean_hour &&
												CurrentDay		== d		&&
												CurrentMonth	== mo		&&
												CurrentYear		== y;
										}
									}

									if (bWindowFlag)
									{
										if (WindowIndex+1 < maxWindowLength)
											WindowIndex++;
									}
									else
									{
										double meanAngleYZ = 0., meanAngleZX = 0., meanAngleXY = 0.;
										double meanAngleX_YZ = 0., meanAngleY_ZX = 0., meanAngleZ_XY = 0.;
										double meanAngleX_XYZ = 0., meanAngleY_XYZ = 0., meanAngleZ_XYZ = 0.;
										
										double meanAngleZY = 0., meanAngleXZ = 0., meanAngleYX = 0.;
										double meanAngleYZ_X = 0., meanAngleZX_Y = 0., meanAngleXY_Z = 0.;
										double meanAngleXYZ_X = 0., meanAngleXYZ_Y = 0., meanAngleXYZ_Z = 0.;
										double meanXYZ = 0.;
										
										double 
											minXYZ, 
											minAngleYZ, 
											minAngleZX, 
											minAngleXY,
											minAngleZY, 
											minAngleXZ, 
											minAngleYX,
											minAngleX_YZ, 
											minAngleY_ZX, 
											minAngleZ_XY,
											minAngleYZ_X, 
											minAngleZX_Y, 
											minAngleXY_Z,
											minAngleX_XYZ, 
											minAngleY_XYZ, 
											minAngleZ_XYZ,
											minAngleXYZ_X, 
											minAngleXYZ_Y, 
											minAngleXYZ_Z;
										double 
											maxXYZ, 
											maxAngleYZ, 
											maxAngleZX, 
											maxAngleXY,
											maxAngleZY, 
											maxAngleXZ, 
											maxAngleYX,
											maxAngleX_YZ, 
											maxAngleY_ZX, 
											maxAngleZ_XY,
											maxAngleYZ_X, 
											maxAngleZX_Y, 
											maxAngleXY_Z,
											maxAngleX_XYZ, 
											maxAngleY_XYZ, 
											maxAngleZ_XYZ,
											maxAngleXYZ_X, 
											maxAngleXYZ_Y, 
											maxAngleXYZ_Z;
										
										
										double meanX, meanY, meanZ;
										double meanX2, meanY2, meanZ2;
										double medianX, medianY, medianZ, medianXYZ;
										double 
											minX, minY, minZ,
											maxX, maxY, maxZ;

										double 
											MedianAngleYZ,
											MedianAngleZX,
											MedianAngleXY,

											MedianAngleZY,
											MedianAngleXZ,
											MedianAngleYX,

											MedianAngleYZ_X,
											MedianAngleZX_Y,
											MedianAngleXY_Z,

											MedianAngleX_YZ,
											MedianAngleY_ZX,
											MedianAngleZ_XY,

											MedianAngleXYZ_X,
											MedianAngleXYZ_Y,
											MedianAngleXYZ_Z,

											MedianAngleX_XYZ,
											MedianAngleY_XYZ,
											MedianAngleZ_XYZ;

										meanX=0; meanY=0;  meanZ=0;
										meanX2=0;meanY2=0; meanZ2=0;
										for (int j=0;j<=WindowIndex;j++)
										{
											if(sfddd.bMin || sfddd.bMax)
											{
												if (j==0)
												{
													minX = maxX = vX[j];
													minY = maxY = vY[j];
													minZ = maxZ = vZ[j];
												}
												else
												{
													if (minX > vX[j]) minX = vX[j];
													if (maxX < vX[j]) maxX = vX[j];
													
													if (minY > vY[j]) minY = vY[j];
													if (maxY < vY[j]) maxY = vY[j];
													
													if (minZ > vZ[j]) minZ = vZ[j];
													if (maxZ < vZ[j]) maxZ = vZ[j];
												}
											}

											if(sfddd.bMean)
											{
												meanX += vX[j];
												meanY += vY[j];
												meanZ += vZ[j];
											}
											if(sfddd.bMinAngle || sfddd.bMedianAngle 
												|| sfddd.bMeanAngle || sfddd.bMaxAngle )
											{
												vYZ[j] = 180.*atan2(vY[j], vZ[j])/PI;
												vZX[j] = 180.*atan2(vZ[j], vX[j])/PI;
												vXY[j] = 180.*atan2(vX[j], vY[j])/PI;
											}
											if(sfddd.bMinAngle || sfddd.bMaxAngle)
											{
												if (j==0)
												{
													minAngleYZ = maxAngleYZ = vYZ[j];
													minAngleZX = maxAngleZX = vZX[j];
													minAngleXY = maxAngleXY = vXY[j];
												}
												else
												{
													if (minAngleYZ > vYZ[j]) minAngleYZ = vYZ[j];
													if (maxAngleYZ < vYZ[j]) maxAngleYZ = vYZ[j];
													
													if (minAngleZX > vZX[j]) minAngleZX = vZX[j];
													if (maxAngleZX < vZX[j]) maxAngleZX = vZX[j];
													
													if (minAngleXY > vXY[j]) minAngleXY = vXY[j];
													if (maxAngleXY < vXY[j]) maxAngleXY = vXY[j];
												}
											}

											if(sfddd.bMeanAngle)
											{										
												meanAngleYZ += vYZ[j];
												meanAngleZX += vZX[j];
												meanAngleXY += vXY[j];
											}
											if(sfddd.bMinAngle3 || sfddd.bMaxAngle3 
												|| sfddd.bMeanAngle3 || sfddd.bMedianAngle3 )
											{
												vX_YZ[j] = 180.*atan2(vX[j], sqrt(pow(vY[j], 2.0) + pow(vZ[j], 2.0)) )/PI;
												vY_ZX[j] = 180.*atan2(vY[j], sqrt(pow(vZ[j], 2.0) + pow(vX[j], 2.0)) )/PI;
												vZ_XY[j] = 180.*atan2(vZ[j], sqrt(pow(vX[j], 2.0) + pow(vY[j], 2.0)) )/PI;
											}
											if(sfddd.bMinAngle3 || sfddd.bMaxAngle3)
											{
												if (j==0)
												{
													minAngleX_YZ = maxAngleX_YZ = vX_YZ[j];
													minAngleY_ZX = maxAngleY_ZX = vY_ZX[j];
													minAngleZ_XY = maxAngleZ_XY = vZ_XY[j];
												}
												else
												{
													if (minAngleX_YZ > vX_YZ[j]) minAngleX_YZ = vX_YZ[j];
													if (maxAngleX_YZ < vX_YZ[j]) maxAngleX_YZ = vX_YZ[j];
													
													if (minAngleY_ZX > vY_ZX[j]) minAngleY_ZX = vY_ZX[j];
													if (maxAngleY_ZX < vY_ZX[j]) maxAngleY_ZX = vY_ZX[j];
													
													if (minAngleZ_XY > vZ_XY[j]) minAngleZ_XY = vZ_XY[j];
													if (maxAngleZ_XY < vZ_XY[j]) maxAngleZ_XY = vZ_XY[j];
												}
											}
											if(sfddd.bMinAngle4 || sfddd.bMaxAngle4 
												|| sfddd.bMeanAngle4 || sfddd.bMedianAngle4 
												|| sfddd.bMinXYZ || sfddd.bMedianXYZ 
												|| sfddd.bMeanXYZ || sfddd.bMaxXYZ)
											{
												vXYZ[j] = sqrt(pow(vX[j], 2.0) + pow(vY[j], 2.0) + pow(vZ[j], 2.0));
											}
											if(sfddd.bMinAngle4 || sfddd.bMaxAngle4 
												|| sfddd.bMeanAngle4 || sfddd.bMedianAngle4 )
											{
												vX_XYZ[j] = 180.*atan2(vX[j], vXYZ[j] )/PI;
												vY_XYZ[j] = 180.*atan2(vY[j], vXYZ[j] )/PI;
												vZ_XYZ[j] = 180.*atan2(vZ[j], vXYZ[j] )/PI;
											}
											if(sfddd.bMinAngle4 || sfddd.bMaxAngle4)
											{
												if (j==0)
												{
													minAngleX_XYZ = maxAngleX_XYZ = vX_XYZ[j];
													minAngleY_XYZ = maxAngleY_XYZ = vY_XYZ[j];
													minAngleZ_XYZ = maxAngleZ_XYZ = vZ_XYZ[j];
												}
												else
												{
													if (minAngleX_XYZ > vX_XYZ[j]) minAngleX_XYZ = vX_XYZ[j];
													if (maxAngleX_XYZ < vX_XYZ[j]) maxAngleX_XYZ = vX_XYZ[j];
													
													if (minAngleY_XYZ > vY_XYZ[j]) minAngleY_XYZ = vY_XYZ[j];
													if (maxAngleY_XYZ < vY_XYZ[j]) maxAngleY_XYZ = vY_XYZ[j];
													
													if (minAngleZ_XYZ > vZ_XYZ[j]) minAngleZ_XYZ = vZ_XYZ[j];
													if (maxAngleZ_XYZ < vZ_XYZ[j]) maxAngleZ_XYZ = vZ_XYZ[j];
												}
											}
											if(sfddd.bMinXYZ || sfddd.bMaxXYZ)
											{
												if (j==0)
												{
													minXYZ = maxXYZ = vXYZ[j];
												}
												else
												{
													if (minXYZ > vXYZ[j]) minXYZ = vXYZ[j];
													if (maxXYZ < vXYZ[j]) maxXYZ = vXYZ[j];
												}
											}
											if(sfddd.bMeanAngle3)
											{
												meanAngleX_YZ += vX_YZ[j];
												meanAngleY_ZX += vY_ZX[j];
												meanAngleZ_XY += vZ_XY[j];
											}
											if(sfddd.bMeanXYZ)
											{
												meanXYZ += vXYZ[j];
											}
											if(sfddd.bMeanAngle4)
											{
												meanAngleX_XYZ += vX_XYZ[j];
												meanAngleY_XYZ += vY_XYZ[j];
												meanAngleZ_XYZ += vZ_XYZ[j];
											}
/*#if 0
											meanX2 += pow(vX[j], 2.0);
											meanY2 += pow(vY[j], 2.0);
											meanZ2 += pow(vZ[j], 2.0);
#endif*/

										}
										if(sfddd.bMeanXYZ)
											meanXYZ /= WindowIndex+1;

										if(sfddd.bMean)
										{
											meanX /= WindowIndex+1;
											meanY /= WindowIndex+1;
											meanZ /= WindowIndex+1;
										}
/*#if 0
										meanX2 /= WindowIndex+1;
										meanY2 /= WindowIndex+1;
										meanZ2 /= WindowIndex+1;
#endif*/

										if(sfddd.bMinAngle)
										{										
											if(sfddd.bReverseAngles)
											{
												minAngleZY = 90.- minAngleYZ;
												minAngleXZ = 90.- minAngleZX;
												minAngleYX = 90.- minAngleXY;
											}
										}
										if(sfddd.bMaxAngle)
										{										
											if(sfddd.bReverseAngles)
											{
												maxAngleZY = 90.- maxAngleYZ;
												maxAngleXZ = 90.- maxAngleZX;
												maxAngleYX = 90.- maxAngleXY;
											}
										}

										if(sfddd.bMeanAngle)
										{										
											meanAngleYZ /= WindowIndex+1;
											meanAngleZX /= WindowIndex+1;
											meanAngleXY /= WindowIndex+1;

											if(sfddd.bReverseAngles)
											{
												meanAngleZY = 90.- meanAngleYZ;
												meanAngleXZ = 90.- meanAngleZX;
												meanAngleYX = 90.- meanAngleXY;
											}
										}
										if(sfddd.bMinAngle3)
										{
											if(sfddd.bReverseAngles)
											{
												minAngleYZ_X = 90.- minAngleX_YZ;
												minAngleZX_Y = 90.- minAngleY_ZX;
												minAngleXY_Z = 90.- minAngleZ_XY;
											}
										}
										if(sfddd.bMaxAngle3)
										{
											if(sfddd.bReverseAngles)
											{
												maxAngleYZ_X = 90.- maxAngleX_YZ;
												maxAngleZX_Y = 90.- maxAngleY_ZX;
												maxAngleXY_Z = 90.- maxAngleZ_XY;
											}
										}
										if(sfddd.bMeanAngle3)
										{
											meanAngleX_YZ /= WindowIndex+1;
											meanAngleY_ZX /= WindowIndex+1;
											meanAngleZ_XY /= WindowIndex+1;

											if(sfddd.bReverseAngles)
											{
												meanAngleYZ_X = 90.- meanAngleX_YZ;
												meanAngleZX_Y = 90.- meanAngleY_ZX;
												meanAngleXY_Z = 90.- meanAngleZ_XY;
											}
										}
										if(sfddd.bMinAngle4)
										{
											if(sfddd.bReverseAngles)
											{
												minAngleXYZ_X = 90.- minAngleX_XYZ;
												minAngleXYZ_Y = 90.- minAngleY_XYZ;
												minAngleXYZ_Z = 90.- minAngleZ_XYZ;
											}
										}
										if(sfddd.bMaxAngle4)
										{
											if(sfddd.bReverseAngles)
											{
												maxAngleXYZ_X = 90.- maxAngleX_XYZ;
												maxAngleXYZ_Y = 90.- maxAngleY_XYZ;
												maxAngleXYZ_Z = 90.- maxAngleZ_XYZ;
											}
										}
										if(sfddd.bMeanAngle4)
										{
											meanAngleX_XYZ /= WindowIndex+1;
											meanAngleY_XYZ /= WindowIndex+1;
											meanAngleZ_XYZ /= WindowIndex+1;

											if(sfddd.bReverseAngles)
											{
												meanAngleXYZ_X = 90.- meanAngleX_XYZ;
												meanAngleXYZ_Y = 90.- meanAngleY_XYZ;
												meanAngleXYZ_Z = 90.- meanAngleZ_XYZ;
											}
										}
										if(sfddd.bMedian)
										{
											medianX = Median(vX, WindowIndex+1);
											medianY = Median(vY, WindowIndex+1);
											medianZ = Median(vZ, WindowIndex+1);
										}
										if(sfddd.bMedianXYZ)
										{
											medianXYZ = Median(vXYZ, WindowIndex+1);
										}
										if(sfddd.bMedianAngle)
										{
											MedianAngleYZ = Median(vYZ, WindowIndex+1);
											MedianAngleZX = Median(vZX, WindowIndex+1);
											MedianAngleXY = Median(vXY, WindowIndex+1);

											if(sfddd.bReverseAngles)
											{
												MedianAngleZY = 90.- MedianAngleYZ;
												MedianAngleXZ = 90.- MedianAngleZX;
												MedianAngleYX = 90.- MedianAngleXY;
											}
										}
										if(sfddd.bMedianAngle3)
										{
											MedianAngleX_YZ = Median(vX_YZ, WindowIndex+1);
											MedianAngleY_ZX = Median(vY_ZX, WindowIndex+1);
											MedianAngleZ_XY = Median(vZ_XY, WindowIndex+1);

											if(sfddd.bReverseAngles)
											{
												MedianAngleYZ_X = 90.- MedianAngleX_YZ;
												MedianAngleZX_Y = 90.- MedianAngleY_ZX;
												MedianAngleXY_Z = 90.- MedianAngleZ_XY;
											}
										}
										if(sfddd.bMedianAngle4)
										{
											MedianAngleX_XYZ = Median(vX_XYZ, WindowIndex+1);
											MedianAngleY_XYZ = Median(vY_XYZ, WindowIndex+1);
											MedianAngleZ_XYZ = Median(vZ_XYZ, WindowIndex+1);

											if(sfddd.bReverseAngles)
											{
												MedianAngleXYZ_X = 90.- MedianAngleX_XYZ;
												MedianAngleXYZ_Y = 90.- MedianAngleY_XYZ;
												MedianAngleXYZ_Z = 90.- MedianAngleZ_XYZ;
											}
										}
										///////////////////////////////////////////////////
										if (sfddd.shFormatFlag !=2)// excel or matlab format
										{
											///////////////////////////////////////////////////
											if (sfddd.shPeriodFlag >= sfddd.shPeriodFlagMinStart 
												&& sfddd.shPeriodFlag <= sfddd.shPeriodFlagMinEnd)
											{
												t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, CurrentHour, CurrentMinute, 0, 0);
												t2 = datenum(y, mo, d, h, mi, 0, 0);
											}
											else
											{
												if (sfddd.shPeriodFlag >= sfddd.shPeriodFlagHoursStart 
												&& sfddd.shPeriodFlag <= sfddd.shPeriodFlagHoursEnd)
												{
													t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, CurrentHour, 0, 0, 0);
													t2 = t1 + double(mean_hour)/double(24);
												}
												else
												{
													if(sfddd.shPeriodFlag == sfddd.shPeriodFlagHalfOfDay )
													{
														t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, 0, 0, 0, 0);
														t2 = t1 + 1.0;
													}
												}
											}


											if (sfddd.shFormatFlag == 0)// excel format
											{
												double delta_t = t0_excel;
												t1 -= delta_t;
												t2 -= delta_t;
												jj++;
												if (sfddd.bToCutPagesExcel && jj > 65536-1)
												{
													jj = 0;
													kk++;

													fclose(stream2);


													wsprintf(filename_out_temp,"%d_c%s%s_%02d_%02d_%02d_%02d_%02d_%02d.part%d%s",
														nPribor,														
														sFormat,
														sPeriod,
														sfddd.startYear-(sfddd.startYear/100)*100, sfddd.startMonth, sfddd.startDay, 
														sfddd.finishYear-(sfddd.finishYear/100)*100, sfddd.finishMonth, sfddd.finishDay,
														kk,
														sExt);


													strcpy(filename_out, directory_out);
													strcat(filename_out, "\\");
													strcat(filename_out, filename_out_temp);


													if ((stream2 = fopen(filename_out,"wt")) == NULL)
													{
														
														MessageBox(0, "Cannot open output file.\n", "Import", 
															MB_OK | MB_ICONINFORMATION);
														return;
													}

												}
												bool toWriteDate = pre_wrote_t2 != t2;
												///////////////////////////////////////////////////
												if(sfddd.shPeriodFlag != sfddd.shPeriodFlagHalfOfDay || 
													(sfddd.shPeriodFlag == sfddd.shPeriodFlagHalfOfDay && toWriteDate))
												{
													if (bNewStringDone)
														fprintf(stream2,"%.8f%c%.8f", t1,delim,t2);
													else 
														fprintf(stream2,"\n%.8f%c%.8f", t1,delim,t2);
													pre_wrote_t2 = t2;
												}

												// если до полудня нет данных, пишем дату и заполнем пробелами												
												if (sfddd.shPeriodFlag == sfddd.shPeriodFlagHalfOfDay && CurrentHour >= 24 - mean_hour && toWriteDate)
												{
													///////////////////////////////////////////////////
													if(sfddd.bMin)
													{
														fprintf(stream2,"%c ", delim, int(minX));
														fprintf(stream2,"%c ", delim, int(minY));
														fprintf(stream2,"%c ", delim, int(minZ));
													}

													if(sfddd.bMedian)
													{
														fprintf(stream2,"%c ", delim, medianX);
														fprintf(stream2,"%c ", delim, medianY);
														fprintf(stream2,"%c ", delim, medianZ);
													}

													if(sfddd.bMean)
													{
														fprintf(stream2,"%c ", delim, meanX);
														fprintf(stream2,"%c ", delim, meanY);
														fprintf(stream2,"%c ", delim, meanZ);
													}

													if(sfddd.bMax)
													{
														fprintf(stream2,"%c ", delim, int(maxX));
														fprintf(stream2,"%c ", delim, int(maxY));
														fprintf(stream2,"%c ", delim, int(maxZ));
													}

													if(sfddd.bPolarization)
													{
														fprintf(stream2,"%c ", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
														fprintf(stream2,"%c ", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
														fprintf(stream2,"%c ", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);
													}

													if(sfddd.bInvPolarization)
													{
														fprintf(stream2,"%c ", delim, maxX+minX > 0.0 ? (maxX-minX)/(maxX+minX) : 0.);
														fprintf(stream2,"%c ", delim, maxY+minY > 0.0 ? (maxY-minY)/(maxY+minY) : 0.);
														fprintf(stream2,"%c ", delim, maxZ+minZ > 0.0 ? (maxZ-minZ)/(maxZ+minZ) : 0.);
													}

													if(sfddd.bMinAngle)
													{
														fprintf(stream2,"%c", delim, minAngleYZ);
														fprintf(stream2,"%c", delim, minAngleZX);
														fprintf(stream2,"%c", delim, minAngleXY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, minAngleZY);
															fprintf(stream2,"%c", delim, minAngleXZ);
															fprintf(stream2,"%c", delim, minAngleYX);
														}
													}
																								

													if(sfddd.bMedianAngle)
													{
														fprintf(stream2,"%c", delim, MedianAngleYZ);
														fprintf(stream2,"%c", delim, MedianAngleZX);
														fprintf(stream2,"%c", delim, MedianAngleXY);
																								
														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, MedianAngleZY);
															fprintf(stream2,"%c", delim, MedianAngleXZ);
															fprintf(stream2,"%c", delim, MedianAngleYX);
														}
													}

													
													if(sfddd.bMeanAngle)
													{
														fprintf(stream2,"%c", delim, meanAngleYZ);
														fprintf(stream2,"%c", delim, meanAngleZX);
														fprintf(stream2,"%c", delim, meanAngleXY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, meanAngleZY);
															fprintf(stream2,"%c", delim, meanAngleXZ);
															fprintf(stream2,"%c", delim, meanAngleYX);
														}
													}
			
													if(sfddd.bMaxAngle)
													{
														fprintf(stream2,"%c", delim, maxAngleYZ);
														fprintf(stream2,"%c", delim, maxAngleZX);
														fprintf(stream2,"%c", delim, maxAngleXY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleZY);
															fprintf(stream2,"%c", delim, maxAngleXZ);
															fprintf(stream2,"%c", delim, maxAngleYX);
														}
													}
													
													if(sfddd.bPolarizationAngle)
													{
														fprintf(stream2,"%c", delim, maxAngleYZ-minAngleYZ > 0.0 ? 0.5*(maxAngleYZ+minAngleYZ)/(maxAngleYZ-minAngleYZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleZX-minAngleZX > 0.0 ? 0.5*(maxAngleZX+minAngleZX)/(maxAngleZX-minAngleZX) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleXY-minAngleXY > 0.0 ? 0.5*(maxAngleXY+minAngleXY)/(maxAngleXY-minAngleXY) : 0.5);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleZY-minAngleZY > 0.0 ? 0.5*(maxAngleZY+minAngleZY)/(maxAngleZY-minAngleZY) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXZ-minAngleXZ > 0.0 ? 0.5*(maxAngleXZ+minAngleXZ)/(maxAngleXZ-minAngleXZ) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleYX-minAngleYX > 0.0 ? 0.5*(maxAngleYX+minAngleYX)/(maxAngleYX-minAngleYX) : 0.5);
														}	
													}
			

													if(sfddd.bInvPolarizationAngle)
													{
														fprintf(stream2,"%c", delim, maxAngleYZ+minAngleYZ > 0.0 ? (maxAngleYZ-minAngleYZ)/(maxAngleYZ+minAngleYZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleZX+minAngleZX > 0.0 ? (maxAngleZX-minAngleZX)/(maxAngleZX+minAngleZX) : 0.);
														fprintf(stream2,"%c", delim, maxAngleXY+minAngleXY > 0.0 ? (maxAngleXY-minAngleXY)/(maxAngleXY+minAngleXY) : 0.);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleZY+minAngleZY > 0.0 ? (maxAngleZY-minAngleZY)/(maxAngleZY+minAngleZY) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXZ+minAngleXZ > 0.0 ? (maxAngleXZ-minAngleXZ)/(maxAngleXZ+minAngleXZ) : 0.);
															fprintf(stream2,"%c", delim, maxAngleYX+minAngleYX > 0.0 ? (maxAngleYX-minAngleYX)/(maxAngleYX+minAngleYX) : 0.);
														}	
													}
			

													if(sfddd.bMinAngle3)
													{
														fprintf(stream2,"%c", delim, minAngleX_YZ);
														fprintf(stream2,"%c", delim, minAngleY_ZX);
														fprintf(stream2,"%c", delim, minAngleZ_XY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, minAngleYZ_X);
															fprintf(stream2,"%c", delim, minAngleZX_Y);
															fprintf(stream2,"%c", delim, minAngleXY_Z);
														}
													}

													if(sfddd.bMedianAngle3)
													{
														fprintf(stream2,"%c", delim, MedianAngleX_YZ);
														fprintf(stream2,"%c", delim, MedianAngleY_ZX);
														fprintf(stream2,"%c", delim, MedianAngleZ_XY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, MedianAngleYZ_X);
															fprintf(stream2,"%c", delim, MedianAngleZX_Y);
															fprintf(stream2,"%c", delim, MedianAngleXY_Z);
														}
													}

													
													if(sfddd.bMeanAngle3)
													{
														fprintf(stream2,"%c", delim, meanAngleX_YZ);
														fprintf(stream2,"%c", delim, meanAngleY_ZX);
														fprintf(stream2,"%c", delim, meanAngleZ_XY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, meanAngleYZ_X);
															fprintf(stream2,"%c", delim, meanAngleZX_Y);
															fprintf(stream2,"%c", delim, meanAngleXY_Z);
														}
													}

													if(sfddd.bMaxAngle3)
													{
														fprintf(stream2,"%c", delim, maxAngleX_YZ);
														fprintf(stream2,"%c", delim, maxAngleY_ZX);
														fprintf(stream2,"%c", delim, maxAngleZ_XY);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleYZ_X);
															fprintf(stream2,"%c", delim, maxAngleZX_Y);
															fprintf(stream2,"%c", delim, maxAngleXY_Z);
														}
													}
													
													if(sfddd.bPolarizationAngle3)
													{
														fprintf(stream2,"%c", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
														}
													}													
			

													if(sfddd.bInvPolarizationAngle3)
													{
														fprintf(stream2,"%c", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
														fprintf(stream2,"%c", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
															fprintf(stream2,"%c", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
														}
													}													
			

													if(sfddd.bMinAngle4)
													{
														fprintf(stream2,"%c", delim, minAngleX_XYZ);
														fprintf(stream2,"%c", delim, minAngleY_XYZ);
														fprintf(stream2,"%c", delim, minAngleZ_XYZ);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, minAngleXYZ_X);
															fprintf(stream2,"%c", delim, minAngleXYZ_Y);
															fprintf(stream2,"%c", delim, minAngleXYZ_Z);
														}
													}

													if(sfddd.bMedianAngle4)
													{
														fprintf(stream2,"%c", delim, MedianAngleX_XYZ);
														fprintf(stream2,"%c", delim, MedianAngleY_XYZ);
														fprintf(stream2,"%c", delim, MedianAngleZ_XYZ);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, MedianAngleXYZ_X);
															fprintf(stream2,"%c", delim, MedianAngleXYZ_Y);
															fprintf(stream2,"%c", delim, MedianAngleXYZ_Z);
														}
													}

													
													if(sfddd.bMeanAngle4)
													{
														fprintf(stream2,"%c", delim, meanAngleX_XYZ);
														fprintf(stream2,"%c", delim, meanAngleY_XYZ);
														fprintf(stream2,"%c", delim, meanAngleZ_XYZ);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, meanAngleXYZ_X);
															fprintf(stream2,"%c", delim, meanAngleXYZ_Y);
															fprintf(stream2,"%c", delim, meanAngleXYZ_Z);
														}
													}

													if(sfddd.bMaxAngle4)
													{
														fprintf(stream2,"%c", delim, maxAngleX_XYZ);
														fprintf(stream2,"%c", delim, maxAngleY_XYZ);
														fprintf(stream2,"%c", delim, maxAngleZ_XYZ);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleXYZ_X);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Y);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Z);
														}
													}
													
													if(sfddd.bPolarizationAngle4)
													{
														fprintf(stream2,"%c", delim, maxAngleX_XYZ-minAngleX_XYZ > 0.0 ? 0.5*(maxAngleX_XYZ+minAngleX_XYZ)/(maxAngleX_XYZ-minAngleX_XYZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleY_XYZ-minAngleY_XYZ > 0.0 ? 0.5*(maxAngleY_XYZ+minAngleY_XYZ)/(maxAngleY_XYZ-minAngleY_XYZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleZ_XYZ-minAngleZ_XYZ > 0.0 ? 0.5*(maxAngleZ_XYZ+minAngleZ_XYZ)/(maxAngleZ_XYZ-minAngleZ_XYZ) : 0.5);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleXYZ_X-minAngleXYZ_X > 0.0 ? 0.5*(maxAngleXYZ_X+minAngleXYZ_X)/(maxAngleXYZ_X-minAngleXYZ_X) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Y-minAngleXYZ_Y > 0.0 ? 0.5*(maxAngleXYZ_Y+minAngleXYZ_Y)/(maxAngleXYZ_Y-minAngleXYZ_Y) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Z-minAngleXYZ_Z > 0.0 ? 0.5*(maxAngleXYZ_Z+minAngleXYZ_Z)/(maxAngleXYZ_Z-minAngleXYZ_Z) : 0.5);
														}
													}													
			
													if(sfddd.bInvPolarizationAngle4)
													{
														fprintf(stream2,"%c", delim, maxAngleX_XYZ+minAngleX_XYZ > 0.0 ? (maxAngleX_XYZ-minAngleX_XYZ)/(maxAngleX_XYZ+minAngleX_XYZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleY_XYZ+minAngleY_XYZ > 0.0 ? (maxAngleY_XYZ-minAngleY_XYZ)/(maxAngleY_XYZ+minAngleY_XYZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleZ_XYZ+minAngleZ_XYZ > 0.0 ? (maxAngleZ_XYZ-minAngleZ_XYZ)/(maxAngleZ_XYZ+minAngleZ_XYZ) : 0.);

														if(sfddd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleXYZ_X+minAngleXYZ_X > 0.0 ? (maxAngleXYZ_X-minAngleXYZ_X)/(maxAngleXYZ_X+minAngleXYZ_X) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Y+minAngleXYZ_Y > 0.0 ? (maxAngleXYZ_Y-minAngleXYZ_Y)/(maxAngleXYZ_Y+minAngleXYZ_Y) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Z+minAngleXYZ_Z > 0.0 ? (maxAngleXYZ_Z-minAngleXYZ_Z)/(maxAngleXYZ_Z+minAngleXYZ_Z) : 0.);
														}
													}
													
													if(sfddd.bMinXYZ)
													{
														fprintf(stream2,"%c ", delim, int(minXYZ));
													}

													if(sfddd.bMedianXYZ)
													{
														fprintf(stream2,"%c ", delim, medianXYZ);
													}

													if(sfddd.bMeanXYZ)
													{
														fprintf(stream2,"%c ", delim, meanXYZ);
													}

													if(sfddd.bMaxXYZ)
													{
														fprintf(stream2,"%c ", delim, int(maxXYZ));
													}

													if(sfddd.bPolarizationXYZ)
													{
														fprintf(stream2,"%c ", delim, maxXYZ-minXYZ > 0.0 ? 0.5*(maxXYZ+minXYZ)/(maxXYZ-minXYZ) : 0.5);
													}

													if(sfddd.bInvPolarization)
													{
														fprintf(stream2,"%c ", delim, maxXYZ+minXYZ > 0.0 ? (maxXYZ-minXYZ)/(maxXYZ+minXYZ) : 0.);
													}

			

													///////////////////////////////////////////////////
												}
												///////////////////////////////////////////////////
												if(sfddd.bMin)
												{
													fprintf(stream2,"%c%d", delim, int(minX));
													fprintf(stream2,"%c%d", delim, int(minY));
													fprintf(stream2,"%c%d", delim, int(minZ));
												}

												if(sfddd.bMedian)
												{
													fprintf(stream2,"%c%f", delim, medianX);
													fprintf(stream2,"%c%f", delim, medianY);
													fprintf(stream2,"%c%f", delim, medianZ);
												}

												if(sfddd.bMean)
												{
													fprintf(stream2,"%c%f", delim, meanX);
													fprintf(stream2,"%c%f", delim, meanY);
													fprintf(stream2,"%c%f", delim, meanZ);
												}

												if(sfddd.bMax)
												{
													fprintf(stream2,"%c%d", delim, int(maxX));
													fprintf(stream2,"%c%d", delim, int(maxY));
													fprintf(stream2,"%c%d", delim, int(maxZ));
												}


												if(sfddd.bPolarization)
												{
													fprintf(stream2,"%c%f", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
													fprintf(stream2,"%c%f", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);
												}

												if(sfddd.bInvPolarization)
												{
													fprintf(stream2,"%c%f", delim, maxX+minX > 0.0 ? (maxX-minX)/(maxX+minX) : 0.);
													fprintf(stream2,"%c%f", delim, maxY+minY > 0.0 ? (maxY-minY)/(maxY+minY) : 0.);
													fprintf(stream2,"%c%f", delim, maxZ+minZ > 0.0 ? (maxZ-minZ)/(maxZ+minZ) : 0.);
												}


												if(sfddd.bMinAngle)
												{
													fprintf(stream2,"%c%f", delim, minAngleYZ);
													fprintf(stream2,"%c%f", delim, minAngleZX);
													fprintf(stream2,"%c%f", delim, minAngleXY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, minAngleZY);
														fprintf(stream2,"%c%f", delim, minAngleXZ);
														fprintf(stream2,"%c%f", delim, minAngleYX);
													}
												}


												if(sfddd.bMedianAngle)
												{
													fprintf(stream2,"%c%f", delim, MedianAngleYZ);
													fprintf(stream2,"%c%f", delim, MedianAngleZX);
													fprintf(stream2,"%c%f", delim, MedianAngleXY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, MedianAngleZY);
														fprintf(stream2,"%c%f", delim, MedianAngleXZ);
														fprintf(stream2,"%c%f", delim, MedianAngleYX);
													}
												}


												if(sfddd.bMeanAngle)
												{
													fprintf(stream2,"%c%f", delim, meanAngleYZ);
													fprintf(stream2,"%c%f", delim, meanAngleZX);
													fprintf(stream2,"%c%f", delim, meanAngleXY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, meanAngleZY);
														fprintf(stream2,"%c%f", delim, meanAngleXZ);
														fprintf(stream2,"%c%f", delim, meanAngleYX);
													}
												}

												if(sfddd.bMaxAngle)
												{
													fprintf(stream2,"%c%f", delim, maxAngleYZ);
													fprintf(stream2,"%c%f", delim, maxAngleZX);
													fprintf(stream2,"%c%f", delim, maxAngleXY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleZY);
														fprintf(stream2,"%c%f", delim, maxAngleXZ);
														fprintf(stream2,"%c%f", delim, maxAngleYX);
													}
												}

													
												if(sfddd.bPolarizationAngle)
												{
													fprintf(stream2,"%c%f", delim, maxAngleYZ-minAngleYZ > 0.0 ? 0.5*(maxAngleYZ+minAngleYZ)/(maxAngleYZ-minAngleYZ) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleZX-minAngleZX > 0.0 ? 0.5*(maxAngleZX+minAngleZX)/(maxAngleZX-minAngleZX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleXY-minAngleXY > 0.0 ? 0.5*(maxAngleXY+minAngleXY)/(maxAngleXY-minAngleXY) : 0.5);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleZY-minAngleZY > 0.0 ? 0.5*(maxAngleZY+minAngleZY)/(maxAngleZY-minAngleZY) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXZ-minAngleXZ > 0.0 ? 0.5*(maxAngleXZ+minAngleXZ)/(maxAngleXZ-minAngleXZ) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleYX-minAngleYX > 0.0 ? 0.5*(maxAngleYX+minAngleYX)/(maxAngleYX-minAngleYX) : 0.5);
													}
												}

												if(sfddd.bInvPolarizationAngle)
												{
													fprintf(stream2,"%c%f", delim, maxAngleYZ+minAngleYZ > 0.0 ? (maxAngleYZ-minAngleYZ)/(maxAngleYZ+minAngleYZ) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleZX+minAngleZX > 0.0 ? (maxAngleZX-minAngleZX)/(maxAngleZX+minAngleZX) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleXY+minAngleXY > 0.0 ? (maxAngleXY-minAngleXY)/(maxAngleXY+minAngleXY) : 0.);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleZY+minAngleZY > 0.0 ? (maxAngleZY-minAngleZY)/(maxAngleZY+minAngleZY) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXZ+minAngleXZ > 0.0 ? (maxAngleXZ-minAngleXZ)/(maxAngleXZ+minAngleXZ) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleYX+minAngleYX > 0.0 ? (maxAngleYX-minAngleYX)/(maxAngleYX+minAngleYX) : 0.);
													}
												}


												if(sfddd.bMinAngle3)
												{
													fprintf(stream2,"%c%f", delim, minAngleX_YZ);
													fprintf(stream2,"%c%f", delim, minAngleY_ZX);
													fprintf(stream2,"%c%f", delim, minAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, minAngleYZ_X);
														fprintf(stream2,"%c%f", delim, minAngleZX_Y);
														fprintf(stream2,"%c%f", delim, minAngleXY_Z);
													}
												}


												if(sfddd.bMedianAngle3)
												{
													fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
													fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
													fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
														fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
														fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
													}
												}


												if(sfddd.bMeanAngle3)
												{
													fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
													fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
													fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
														fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
														fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
													}
												}


												if(sfddd.bMaxAngle3)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
													}
												}

												if(sfddd.bPolarizationAngle3)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
													}
												}													
			
												if(sfddd.bInvPolarizationAngle3)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
													}
												}													
			


												if(sfddd.bMinAngle4)
												{
													fprintf(stream2,"%c%f", delim, minAngleX_YZ);
													fprintf(stream2,"%c%f", delim, minAngleY_ZX);
													fprintf(stream2,"%c%f", delim, minAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, minAngleYZ_X);
														fprintf(stream2,"%c%f", delim, minAngleZX_Y);
														fprintf(stream2,"%c%f", delim, minAngleXY_Z);
													}
												}


												if(sfddd.bMedianAngle4)
												{
													fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
													fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
													fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
														fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
														fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
													}
												}


												if(sfddd.bMeanAngle4)
												{
													fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
													fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
													fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
														fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
														fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
													}
												}


												if(sfddd.bMaxAngle4)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
													}
												}

												if(sfddd.bPolarizationAngle4)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
													}
												}													
			
												if(sfddd.bInvPolarizationAngle4)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

													if(sfddd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
													}
												}													
			

													
													if(sfddd.bMinXYZ)
													{
														fprintf(stream2,"%c%d", delim, int(minXYZ));
													}

													if(sfddd.bMedianXYZ)
													{
														fprintf(stream2,"%c%f", delim, medianXYZ);
													}

													if(sfddd.bMeanXYZ)
													{
														fprintf(stream2,"%c%f", delim, meanXYZ);
													}

													if(sfddd.bMaxXYZ)
													{
														fprintf(stream2,"%c%d", delim, int(maxXYZ));
													}

													if(sfddd.bPolarizationXYZ)
													{
														fprintf(stream2,"%c%f", delim, maxXYZ-minXYZ > 0.0 ? 0.5*(maxXYZ+minXYZ)/(maxXYZ-minXYZ) : 0.5);
													}

													if(sfddd.bInvPolarization)
													{
														fprintf(stream2,"%c%f", delim, maxXYZ+minXYZ > 0.0 ? (maxXYZ-minXYZ)/(maxXYZ+minXYZ) : 0.);
													}


												///////////////////////////////////////////////////
												
												
												if(sfddd.shPeriodFlag != sfddd.shPeriodFlagHalfOfDay || 
													(sfddd.shPeriodFlag == sfddd.shPeriodFlagHalfOfDay && CurrentHour >= 24 - mean_hour))
												{
													bNewStringDone = true;
													fprintf(stream2,"\n");
												}
												else
													bNewStringDone = false;




											}
											else
											{

												// matlab format
												///////////////////////////////////////////////////
												/*fprintf(stream2,"%.8f %f %f %f %f %f %f\n", 
													t,meanX,meanY,meanZ,
													sqrt(meanX2 - pow(meanX, 2.0)) / (WindowIndex+1), 
													sqrt(meanY2 - pow(meanY, 2.0)) / (WindowIndex+1), 
													sqrt(meanZ2 - pow(meanZ, 2.0)) / (WindowIndex+1)
													);*/
												///////////////////////////////////////////////////
												///////////////////////////////////////////////////
												fprintf(stream2,"%.8f%c%.8f", t1, delim, t2);
												///////////////////////////////////////////////////
												if(sfddd.bMin)
													fprintf(stream2,"%c%d", delim, int(minX));
												if(sfddd.bMin)
													fprintf(stream2,"%c%d", delim, int(minY));
												if(sfddd.bMin)
													fprintf(stream2,"%c%d", delim, int(minZ));

												if(sfddd.bMedian)
													fprintf(stream2,"%c%f", delim, medianX);
												if(sfddd.bMedian)
													fprintf(stream2,"%c%f", delim, medianY);
												if(sfddd.bMedian)
													fprintf(stream2,"%c%f", delim, medianZ);

												if(sfddd.bMean)
													fprintf(stream2,"%c%f", delim, meanX);
												if(sfddd.bMean)
													fprintf(stream2,"%c%f", delim, meanY);
												if(sfddd.bMean)
													fprintf(stream2,"%c%f", delim, meanZ);

												if(sfddd.bMax)
													fprintf(stream2,"%c%d", delim, int(maxX));
												if(sfddd.bMax)
													fprintf(stream2,"%c%d", delim, int(maxY));
												if(sfddd.bMax)
													fprintf(stream2,"%c%d", delim, int(maxZ));


												if(sfddd.bPolarization)
													fprintf(stream2,"%c%f", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
												if(sfddd.bPolarization)
													fprintf(stream2,"%c%f", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
												if(sfddd.bPolarization)
													fprintf(stream2,"%c%f", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);


												if(sfddd.bMinAngle)
													fprintf(stream2,"%c%f", delim, minAngleYZ);
												if(sfddd.bMinAngle)
													fprintf(stream2,"%c%f", delim, minAngleZX);
												if(sfddd.bMinAngle)
													fprintf(stream2,"%c%f", delim, minAngleXY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMinAngle)
														fprintf(stream2,"%c%f", delim, minAngleZY);
													if(sfddd.bMinAngle)
														fprintf(stream2,"%c%f", delim, minAngleXZ);
													if(sfddd.bMinAngle)
														fprintf(stream2,"%c%f", delim, minAngleYX);
												}


												if(sfddd.bMedianAngle)
													fprintf(stream2,"%c%f", delim, MedianAngleYZ);
												if(sfddd.bMedianAngle)
													fprintf(stream2,"%c%f", delim, MedianAngleZX);
												if(sfddd.bMedianAngle)
													fprintf(stream2,"%c%f", delim, MedianAngleXY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMedianAngle)
														fprintf(stream2,"%c%f", delim, MedianAngleZY);
													if(sfddd.bMedianAngle)
														fprintf(stream2,"%c%f", delim, MedianAngleXZ);
													if(sfddd.bMedianAngle)
														fprintf(stream2,"%c%f", delim, MedianAngleYX);
												}


												if(sfddd.bMeanAngle)
													fprintf(stream2,"%c%f", delim, meanAngleYZ);
												if(sfddd.bMeanAngle)
													fprintf(stream2,"%c%f", delim, meanAngleZX);
												if(sfddd.bMeanAngle)
													fprintf(stream2,"%c%f", delim, meanAngleXY);
												
												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMeanAngle)
														fprintf(stream2,"%c%f", delim, meanAngleZY);
													if(sfddd.bMeanAngle)
														fprintf(stream2,"%c%f", delim, meanAngleXZ);
													if(sfddd.bMeanAngle)
														fprintf(stream2,"%c%f", delim, meanAngleYX);
												}

												if(sfddd.bMaxAngle)
													fprintf(stream2,"%c%f", delim, maxAngleYZ);
												if(sfddd.bMaxAngle)
													fprintf(stream2,"%c%f", delim, maxAngleZX);
												if(sfddd.bMaxAngle)
													fprintf(stream2,"%c%f", delim, maxAngleXY);
												
												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMaxAngle)
														fprintf(stream2,"%c%f", delim, maxAngleZY);
													if(sfddd.bMaxAngle)
														fprintf(stream2,"%c%f", delim, maxAngleXZ);
													if(sfddd.bMaxAngle)
														fprintf(stream2,"%c%f", delim, maxAngleYX);
												}


												if(sfddd.bMinAngle3)
													fprintf(stream2,"%c%f", delim, minAngleX_YZ);
												if(sfddd.bMinAngle3)
													fprintf(stream2,"%c%f", delim, minAngleY_ZX);
												if(sfddd.bMinAngle3)
													fprintf(stream2,"%c%f", delim, minAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMinAngle3)
														fprintf(stream2,"%c%f", delim, minAngleYZ_X);
													if(sfddd.bMinAngle3)
														fprintf(stream2,"%c%f", delim, minAngleZX_Y);
													if(sfddd.bMinAngle3)
														fprintf(stream2,"%c%f", delim, minAngleXY_Z);
												}


												if(sfddd.bMedianAngle3)
													fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
												if(sfddd.bMedianAngle3)
													fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
												if(sfddd.bMedianAngle3)
													fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMedianAngle3)
														fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
													if(sfddd.bMedianAngle3)
														fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
													if(sfddd.bMedianAngle3)
														fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
												}


												if(sfddd.bMeanAngle3)
													fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
												if(sfddd.bMeanAngle3)
													fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
												if(sfddd.bMeanAngle3)
													fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMeanAngle3)
														fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
													if(sfddd.bMeanAngle3)
														fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
													if(sfddd.bMeanAngle3)
														fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
												}

												if(sfddd.bMaxAngle3)
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
												if(sfddd.bMaxAngle3)
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
												if(sfddd.bMaxAngle3)
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMaxAngle3)
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
													if(sfddd.bMaxAngle3)
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
													if(sfddd.bMaxAngle3)
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
												}

												
												
												///////////////////////////////////////////////////

												///////////////////////////////////////////////////
												fprintf(stream2,"\n");
											}
										}
										else// tezeyvar format
										{
											///////////////////////////////////////////////////
											fprintf(stream2,"%02d.%02d.%02d %d:%d:%d,%d", 
												d,mo,y,h,mi,s,milli);
											///////////////////////////////////////////////////
												///////////////////////////////////////////////////
												if(sfddd.bMin)
													fprintf(stream2,",%d", int(minX));
												if(sfddd.bMin)
													fprintf(stream2,",%d", int(minY));
												if(sfddd.bMin)
													fprintf(stream2,",%d", int(minZ));

												if(sfddd.bMedian)
													fprintf(stream2,",%f", medianX);
												if(sfddd.bMedian)
													fprintf(stream2,",%f", medianY);
												if(sfddd.bMedian)
													fprintf(stream2,",%f", medianZ);

												if(sfddd.bMean)
													fprintf(stream2,",%f", meanX);
												if(sfddd.bMean)
													fprintf(stream2,",%f", meanY);
												if(sfddd.bMean)
													fprintf(stream2,",%f", meanZ);

												if(sfddd.bMax)
													fprintf(stream2,",%d", int(maxX));
												if(sfddd.bMax)
													fprintf(stream2,",%d", int(maxY));
												if(sfddd.bMax)
													fprintf(stream2,",%d", int(maxZ));

												if(sfddd.bPolarization)
													fprintf(stream2,"\t%f", maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
												if(sfddd.bPolarization)
													fprintf(stream2,"\t%f", maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
												if(sfddd.bPolarization)
													fprintf(stream2,"\t%f", maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);


												if(sfddd.bMinAngle)
													fprintf(stream2,"\t%f", minAngleYZ);
												if(sfddd.bMinAngle)
													fprintf(stream2,"\t%f", minAngleZX);
												if(sfddd.bMinAngle)
													fprintf(stream2,"\t%f", minAngleXY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMinAngle)
														fprintf(stream2,"\t%f", minAngleZY);
													if(sfddd.bMinAngle)
														fprintf(stream2,"\t%f", minAngleXZ);
													if(sfddd.bMinAngle)
														fprintf(stream2,"\t%f", minAngleYX);
												}


												if(sfddd.bMedianAngle)
													fprintf(stream2,"\t%f", MedianAngleYZ);
												if(sfddd.bMedianAngle)
													fprintf(stream2,"\t%f", MedianAngleZX);
												if(sfddd.bMedianAngle)
													fprintf(stream2,"\t%f", MedianAngleXY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMedianAngle)
														fprintf(stream2,"\t%f", MedianAngleZY);
													if(sfddd.bMedianAngle)
														fprintf(stream2,"\t%f", MedianAngleXZ);
													if(sfddd.bMedianAngle)
														fprintf(stream2,"\t%f", MedianAngleYX);
												}


												if(sfddd.bMeanAngle)
													fprintf(stream2,"\t%f", meanAngleYZ);
												if(sfddd.bMeanAngle)
													fprintf(stream2,"\t%f", meanAngleZX);
												if(sfddd.bMeanAngle)
													fprintf(stream2,"\t%f", meanAngleXY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMeanAngle)
														fprintf(stream2,"\t%f", meanAngleZY);
													if(sfddd.bMeanAngle)
														fprintf(stream2,"\t%f", meanAngleXZ);
													if(sfddd.bMeanAngle)
														fprintf(stream2,"\t%f", meanAngleYX);
												}


												if(sfddd.bMaxAngle)
													fprintf(stream2,"\t%f", maxAngleYZ);
												if(sfddd.bMaxAngle)
													fprintf(stream2,"\t%f", maxAngleZX);
												if(sfddd.bMaxAngle)
													fprintf(stream2,"\t%f", maxAngleXY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMaxAngle)
														fprintf(stream2,"\t%f", maxAngleZY);
													if(sfddd.bMaxAngle)
														fprintf(stream2,"\t%f", maxAngleXZ);
													if(sfddd.bMaxAngle)
														fprintf(stream2,"\t%f", maxAngleYX);
												}



												if(sfddd.bMinAngle3)
													fprintf(stream2,"\t%f", minAngleX_YZ);
												if(sfddd.bMinAngle3)
													fprintf(stream2,"\t%f", minAngleY_ZX);
												if(sfddd.bMinAngle3)
													fprintf(stream2,"\t%f", minAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMinAngle3)
														fprintf(stream2,"\t%f", minAngleYZ_X);
													if(sfddd.bMinAngle3)
														fprintf(stream2,"\t%f", minAngleZX_Y);
													if(sfddd.bMinAngle3)
														fprintf(stream2,"\t%f", minAngleXY_Z);
												}

												if(sfddd.bMedianAngle3)
													fprintf(stream2,"\t%f", MedianAngleX_YZ);
												if(sfddd.bMedianAngle3)
													fprintf(stream2,"\t%f", MedianAngleY_ZX);
												if(sfddd.bMedianAngle3)
													fprintf(stream2,"\t%f", MedianAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMedianAngle3)
														fprintf(stream2,"\t%f", MedianAngleYZ_X);
													if(sfddd.bMedianAngle3)
														fprintf(stream2,"\t%f", MedianAngleZX_Y);
													if(sfddd.bMedianAngle3)
														fprintf(stream2,"\t%f", MedianAngleXY_Z);
												}


												if(sfddd.bMeanAngle3)
													fprintf(stream2,"\t%f", meanAngleX_YZ);
												if(sfddd.bMeanAngle3)
													fprintf(stream2,"\t%f", meanAngleY_ZX);
												if(sfddd.bMeanAngle3)
													fprintf(stream2,"\t%f", meanAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMeanAngle3)
														fprintf(stream2,"\t%f", meanAngleYZ_X);
													if(sfddd.bMeanAngle3)
														fprintf(stream2,"\t%f", meanAngleZX_Y);
													if(sfddd.bMeanAngle3)
														fprintf(stream2,"\t%f", meanAngleXY_Z);
												}

												if(sfddd.bMaxAngle3)
													fprintf(stream2,"\t%f", maxAngleX_YZ);
												if(sfddd.bMaxAngle3)
													fprintf(stream2,"\t%f", maxAngleY_ZX);
												if(sfddd.bMaxAngle3)
													fprintf(stream2,"\t%f", maxAngleZ_XY);

												if(sfddd.bReverseAngles)
												{
													if(sfddd.bMaxAngle3)
														fprintf(stream2,"\t%f", maxAngleYZ_X);
													if(sfddd.bMaxAngle3)
														fprintf(stream2,"\t%f", maxAngleZX_Y);
													if(sfddd.bMaxAngle3)
														fprintf(stream2,"\t%f", maxAngleXY_Z);
												}

												///////////////////////////////////////////////////


												///////////////////////////////////////////////////
												fprintf(stream2,"\n");
										}
										///////////////////////////////////////////////////


										///////////////////////////////////////////////////
										///////////////////////////////////////////////////
										WindowIndex=0;
										CurrentMinute	= mi;					
										//CurrentHour	= h;
										//preCurrentHour	= CurrentHour;
										CurrentHour		= (h/mean_hour)*mean_hour;
										CurrentDay		= d;
										CurrentMonth	= mo;
										CurrentYear		= y;
										///////////////////////////////////////////////////
										///////////////////////////////////////////////////

									}
								}
							}
							break;
						}

						i2++;
						}i++;
					}
				}
			}
			fclose(stream2);
			fclose(stream);
			if(sfddd.bMeanPerDay)
			{

				for (ii = 0; ii < i; ii++)
				{
					UINT ind = UINT(vt[ii]*double(SecsPerDay));
					if (ind >= 0 && ind < SecsPerDay)
					{
						vmeanX[ind] += vx[ii];
						vmeanY[ind] += vy[ii];
						vmeanZ[ind] += vz[ii];
						vn[ind] += 1;
					}
				}
			}


		   // Advance the current position of the
		   // progress bar by the increment. 
		   SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
		}
		else
			toRead = true;
	}
	if(sfddd.bMeanPerDay)
	{
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			if (vn[ii] != 0)
			{
				vmeanX[ii] /= vn[ii];
				vmeanY[ii] /= vn[ii];
				vmeanZ[ii] /= vn[ii];
			}
		}

	//	FILE *stream;
		stream = fopen("C:\\Variation//mean_per_day.txt","wt");
		fprintf(stream,"%s%c%s%c%s%c%s\n", 
			"time", delim, 
			"среднесуточный ход вариаций X", delim, "среднесуточный ход вариаций Y", delim, "среднесуточный ход вариаций Z");
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			fprintf(stream,"%lf%c%lf%c%lf%c%lf\n", 
				vmeant[ii], delim, 
				vmeanX[ii], delim, vmeanY[ii], delim, vmeanZ[ii]);
		}
		fclose(stream);

		stream = fopen("C:\\Variation//mean_per_day2.txt","wt");
		fprintf(stream,"%s%c%s%c%s%c%s\n", 
			"time", delim, 
			"среднесуточный ход вариаций X", delim, 
			"среднесуточный ход вариаций Y", delim, 
			"среднесуточный ход вариаций модуля сигнала трёх антен");
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			fprintf(stream,"%lf%c%lf%c%lf%c%lf\n", 
				vmeant[ii], delim, 
				vmeanX[ii], delim, 
				vmeanY[ii], delim, 
				sqrt(vmeanZ[ii]*vmeanZ[ii]+vmeanY[ii]*vmeanY[ii]+vmeanX[ii]*vmeanX[ii]));
		}
		fclose(stream);


		if(vn)
			HeapFree(GetProcessHeap(), 0,vn);
		if(vt)
			HeapFree(GetProcessHeap(), 0,vt);
		if(vx)
			HeapFree(GetProcessHeap(), 0,vx);
		if(vy)
			HeapFree(GetProcessHeap(), 0,vy);
		if(vz)
			HeapFree(GetProcessHeap(), 0,vz);

		if(vmeanX)
			HeapFree(GetProcessHeap(), 0,vmeanX);
		if(vmeanY)
			HeapFree(GetProcessHeap(), 0,vmeanY);
		if(vmeanZ)
			HeapFree(GetProcessHeap(), 0,vmeanZ);
	}

	if(vX)
		HeapFree(GetProcessHeap(), 0,vX);
	if(vY)
		HeapFree(GetProcessHeap(), 0,vY);
	if(vZ)
		HeapFree(GetProcessHeap(), 0,vZ);

	if(vYZ)
		HeapFree(GetProcessHeap(), 0,vYZ);
	if(vZX)
		HeapFree(GetProcessHeap(), 0,vZX);
	if(vXY)
		HeapFree(GetProcessHeap(), 0,vXY);

	if(vX_YZ)
		HeapFree(GetProcessHeap(), 0,vX_YZ);
	if(vY_ZX)
		HeapFree(GetProcessHeap(), 0,vY_ZX);
	if(vZ_XY)
		HeapFree(GetProcessHeap(), 0,vZ_XY);

	if(vX_XYZ)
		HeapFree(GetProcessHeap(), 0,vX_XYZ);
	if(vY_XYZ)
		HeapFree(GetProcessHeap(), 0,vY_XYZ);
	if(vZ_XYZ)
		HeapFree(GetProcessHeap(), 0,vZ_XYZ);

	if(vXYZ)
		HeapFree(GetProcessHeap(), 0,vXYZ);

  DestroyWindow(hwndPB);

	char string[1023];
	sprintf(string,
		"%s\nglobal_max_X = %d global_max_Y = %d global_max_Z = %d\nX %d %d %d %d %d %d \nY %d %d %d %d %d %d \nZ %d %d %d %d %d %d ",
		filename_out, global_max_X, global_max_Y, global_max_Z,

			global_max_Xt.wYear,
			global_max_Xt.wMonth,
			global_max_Xt.wDay,
			global_max_Xt.wHour,
			global_max_Xt.wMinute,
			global_max_Xt.wSecond,

			global_max_Yt.wYear,
			global_max_Yt.wMonth,
			global_max_Yt.wDay,
			global_max_Yt.wHour,
			global_max_Yt.wMinute,
			global_max_Yt.wSecond,

			global_max_Zt.wYear,
			global_max_Zt.wMonth,
			global_max_Zt.wDay,
			global_max_Zt.wHour,
			global_max_Zt.wMinute,
			global_max_Zt.wSecond);

	MessageBox(0, string, "Конверт завершён", 
		MB_OK | MB_ICONINFORMATION);
}

void importEarthQuakesNEIC(LPSELECTFILEDLGDATA lpSelectFileDlgData)
{
	int d, mo, y, h, mi, s, milli;
	int rez;

	double t;
	double Lat, //  - географическая широта в градусах (северная).
		Lon,        //  - географическая долгота в градусах (восточная).
		H,          //  - глубина в километрах от уровня моря (<минус> - выше уровня моря). 
		Ml;
	char where[255], NS, WE;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line

	char *p/*, *p1, *p2*/;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p /*&& strcmp(ext, "txt") == 0*/)
	{
		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%d/%d/%d %d:%d:%d %lf%c %lf%c  %lf  %lf %s",
					&y, &mo, &d, &h, &mi, &s, &Lat, &NS, &Lon, &WE, &H,  &Ml, where);
				if (rez == 13 && rez != EOF)
				{
					len++;
				}
			}
		}
		fclose(stream);

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
#if 1
//			vDoc[iDoc].m_vtimeEarthQuakes.resize(len);
			vDoc[iDoc].m_tEarthQuakes.resize(len);
			vDoc[iDoc].m_Meq.resize(len);
			vDoc[iDoc].m_Heq.resize(len);
			vDoc[iDoc].m_Beq.resize(len);
			vDoc[iDoc].m_Leq.resize(len);
#else
			vDoc[iDoc].resize(len);
#endif

		}
		SYSTEMTIME tm;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			char str[2048];
			sprintf(str, "fopen(%s)", szPath);
			ErrorExit(str);
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				//p1 = szBuff;
				// Каталоги
				// F       - окончательный каталог.
				// O       - оперативный каталог.

				rez = sscanf(szBuff,"%d/%d/%d %d:%d:%d %lf%c %lf%c  %lf  %lf %s",
					&y, &mo, &d, &h, &mi, &s, &Lat, &NS, &Lon, &WE, &H,  &Ml, where);
				if (rez == 13 && rez != EOF)
				{
					milli = 0;

					char test[255];
					sprintf(test,"%d/%d/%d %d:%d:%d %lf%c %lf%c  %lf  %lf %s",
						y, mo, d, h, mi, s, Lat, NS, Lon, WE, H,  Ml, where);

					t = datenum(y, mo, d, h, mi, s, milli);

					tm.wYear			= y;
					tm.wMonth			= mo;
					tm.wDay				= d;
					tm.wHour			= h;
					tm.wMinute			= mi;
					tm.wSecond			= s;
					tm.wMilliseconds	= milli;
#if 1
//					vDoc[0].m_vtimeEarthQuakes[i]=tm;
//					vDoc[1].m_vtimeEarthQuakes[i]=tm;
//					vDoc[2].m_vtimeEarthQuakes[i]=tm;
					char ns[2];
					char we[2];
					ns[0] = NS;
					ns[1] = '\0';
					we[0] = WE;
					we[1] = '\0';

					for (int idoc = 0; idoc < 3; idoc++)
					{

						if (strcmp(ns, "N\0") == 0)
						{
							vDoc[idoc].m_Beq[i] = + Lat;
						} 
						else{
							if (strcmp(ns, "S\0") == 0)
							{
								vDoc[idoc].m_Beq[i] = - Lat;
							}
							else 
								MessageBox(0,ns,"error ns",0);
						}


						if (strcmp(we, "W\0") == 0)
						{
							vDoc[idoc].m_Leq[i] = - Lon;
						}
						else{
							if (strcmp(we, "E\0") == 0)
							{
								vDoc[idoc].m_Leq[i] = + Lon;
							}
							else 
								vDoc[idoc].m_Leq[i] = + Lon;
						}
					}

					vDoc[1].m_tEarthQuakes[i]=t;
					vDoc[2].m_tEarthQuakes[i]=t;



					vDoc[0].m_tEarthQuakes[i]=t;
					vDoc[1].m_tEarthQuakes[i]=t;
					vDoc[2].m_tEarthQuakes[i]=t;

					vDoc[0].m_Meq[i] = Ml;
					vDoc[1].m_Meq[i] = Ml;
					vDoc[2].m_Meq[i] = Ml;

					vDoc[0].m_Heq[i] = H;
					vDoc[1].m_Heq[i] = H;
					vDoc[2].m_Heq[i] = H;
#else
				vDoc[0].m_vtime[i]=tm;
				vDoc[1].m_vtime[i]=tm;
				vDoc[2].m_vtime[i]=tm;


				vDoc[0].m_t[i]=t;
				vDoc[1].m_t[i]=t;
				vDoc[2].m_t[i]=t;

				vDoc[0].m_T[i] = Ml;//X
				
				vDoc[1].m_T[i]= Ml;//Y
				
				vDoc[2].m_T[i]= H;//Z
 #endif

					i++;
				}
			}
		}
		fclose(stream);
		if (i > 0)
		{
#if 0
			vDoc[0].SetEarthQuakesSkale(lpSelectFileDlgData->scaleModeX);
			vDoc[1].SetEarthQuakesSkale(lpSelectFileDlgData->scaleModeX);
			vDoc[2].SetEarthQuakesSkale(lpSelectFileDlgData->scaleModeX);
//#else
		vDoc[0].ReinitVectorsPoints();
		vDoc[1].ReinitVectorsPoints();
		vDoc[2].ReinitVectorsPoints();
#endif
		}
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}


void importEarthQuakesNEIC2(LPSELECTFILEDLGDATA lpSelectFileDlgData)
{
	int d, mo, y, h, mi, s, milli;
	int rez;

	double t;
	double Lat, //  - географическая широта в градусах (северная).
		Lon,        //  - географическая долгота в градусах (восточная).
		H,          //  - глубина в километрах от уровня моря (<минус> - выше уровня моря). 
		Ml,
		hhmmss_mm;

	const int n=255; // length of buffer string line
	char szBuff[n]; // buffer string line

	char *p/*, *p1, *p2*/;
	
	char ext[255];
	p = strrchr(szPath,'.');
	if (p)
		strcpy(ext, p+1);

	if (p /*&& strcmp(ext, "txt") == 0*/)
	{
		FILE *stream;
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
			char str[2048];
			sprintf(str, "fopen(%s)", szPath);
			ErrorExit(str);
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return;
		}
		int len = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				rez = sscanf(szBuff,"%d,%d,%d,%lf , %lf, %lf, %lf, %lf",
					&y, &mo, &d, &hhmmss_mm, &Lat, &Lon, &Ml, &H);
				if (rez == 8 && rez != EOF)
				{
					len++;
				}
			}
		}
		fclose(stream);

		for (int iDoc = 0; iDoc < 3; iDoc++)
		{
#if 1
//			vDoc[iDoc].m_vtimeEarthQuakes.resize(len);
			vDoc[iDoc].m_tEarthQuakes.resize(len);
			vDoc[iDoc].m_Meq.resize(len);
			vDoc[iDoc].m_Heq.resize(len);
			vDoc[iDoc].m_Beq.resize(len);
			vDoc[iDoc].m_Leq.resize(len);
#else
			vDoc[iDoc].resize(len);
#endif

		}
		SYSTEMTIME tm;
	FILE *stream2;
	if ((stream2 = fopen("C:\\earth.txt","wt")) == NULL)
	{
	MessageBox(0, "Cannot open input file.\n", "Import", 
		MB_OK | MB_ICONINFORMATION);
		return;
	}
		if ((stream = fopen(szPath,"rt")) == NULL)
		{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
			return;
		}
		int i = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				//p1 = szBuff;
				// Каталоги
				// F       - окончательный каталог.
				// O       - оперативный каталог.

				rez = sscanf(szBuff,"%d,%d,%d,%lf , %lf, %lf, %lf, %lf",
					&y, &mo, &d, &hhmmss_mm, &Lat, &Lon, &Ml, &H);
				if (rez == 8 && rez != EOF)
				{
					milli = 0;

					/*char test[255];
					sprintf(test,"%d,%d,%d,%lf , %lf, %lf, %lf, %lf",
						y, mo, d, hhmmss_mm, Lat, Lon, Ml, H);
					MessageBox(0,test,"",0);*/

					double tmp = hhmmss_mm - int(hhmmss_mm);

					milli = int(1000.*tmp);
					
					int hhmmss = int(hhmmss_mm);

					h  = hhmmss / 10000;
					mi = hhmmss / 100 - h*100;
					s  = hhmmss - h*10000 - mi * 100;



					t = datenum(y, mo, d, h, mi, s, milli);

if (Lat <= -20 && Ml >= 4.6)
{
	fprintf (stream2, "%lf\t%lf\t%lf\t%lf\t%lf\n", t, Lat, Lon, Ml, H);
}

					tm.wYear			= y;
					tm.wMonth			= mo;
					tm.wDay				= d;
					tm.wHour			= h;
					tm.wMinute			= mi;
					tm.wSecond			= s;
					tm.wMilliseconds	= milli;
#if 1
//					vDoc[0].m_vtimeEarthQuakes[i]=tm;
//					vDoc[1].m_vtimeEarthQuakes[i]=tm;
//					vDoc[2].m_vtimeEarthQuakes[i]=tm;
					for (int idoc = 0; idoc < 3; idoc++)
					{
						vDoc[idoc].m_Beq[i] = Lat;
						vDoc[idoc].m_Leq[i] = Lon;
					}

					vDoc[0].m_tEarthQuakes[i]=t;
					vDoc[1].m_tEarthQuakes[i]=t;
					vDoc[2].m_tEarthQuakes[i]=t;



					vDoc[0].m_tEarthQuakes[i]=t;
					vDoc[1].m_tEarthQuakes[i]=t;
					vDoc[2].m_tEarthQuakes[i]=t;

					vDoc[0].m_Meq[i] = Ml;
					vDoc[1].m_Meq[i] = Ml;
					vDoc[2].m_Meq[i] = Ml;

					vDoc[0].m_Heq[i] = H;
					vDoc[1].m_Heq[i] = H;
					vDoc[2].m_Heq[i] = H;
#else
				//vDoc[0].m_vtime[i]=tm;
				//vDoc[1].m_vtime[i]=tm;
				//vDoc[2].m_vtime[i]=tm;


				vDoc[0].m_t[i]=t;
				vDoc[1].m_t[i]=t;
				vDoc[2].m_t[i]=t;

				vDoc[0].m_T[i] = Ml;//X
				
				vDoc[1].m_T[i]= Ml;//Y
				
				vDoc[2].m_T[i]= H;//Z
 #endif

					i++;
				}
			}
		}
		fclose(stream);
		fclose(stream2);
		if (i > 0)
		{
#if 0
			vDoc[0].SetEarthQuakesSkale(lpSelectFileDlgData->scaleModeX);
			vDoc[1].SetEarthQuakesSkale(lpSelectFileDlgData->scaleModeX);
			vDoc[2].SetEarthQuakesSkale(lpSelectFileDlgData->scaleModeX);
//#else
		vDoc[0].ReinitVectorsPoints();
		vDoc[1].ReinitVectorsPoints();
		vDoc[2].ReinitVectorsPoints();
#endif
		}
	}
	else
		MessageBox(0, ext, "Расширение файла не подходит", 
			MB_OK | MB_ICONINFORMATION);
}



LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static unsigned short wFileProc = 0;
	static unsigned short opened = 0;
	static unsigned short opened_cov = 0;
	static unsigned short opened_autocov = 0;

	static LPPRINTDLGDATA		lpPrintDlgMem;

	static LPHIDEPLOTDLGDATA	lpHidePlotDlgMem;

	static LPDEVMODE pDevModeDefault = NULL;
	static LPDEVMODE pDevModeUser = NULL;

	static LPWAVELETDLGDATA		lpWaveletDlgMem;
	static LPWAVELETDATA		lpWaveletMem;
	static LPLAGERDLGDATA		lpLagerDlgMem;

	static LPSELECTFILEDLGDATA	lpSelectFileDlgData;
	static LPSAVEASFILEDLGDATA	lpSaveAsFileDlgData;

	static LPPOLYOTYFILEDLGDATA	lpPolyotyDlgData;
	static LPEARTHQUAKESDLGDATA lpEarthquakesDlgMem;

	switch( uMsg )
	{
	case WM_CREATE :
		{
WriteRaporto("wnd WM_CREATE\n");
			CLIENTCREATESTRUCT ccs;

			// Определение меню 'Window'.
			//..........................
			ccs.hWindowMenu = GetSubMenu( GetMenu( hWnd ), 3 );
			CheckMenuItem(GetMenu( hWnd ), 
				ID_VIEW_SCALE_Y_ON_HSCROLL,
				MF_BYCOMMAND | MF_CHECKED);

			ccs.idFirstChild = ID_CHILDWINDOW;

			// Создание клиентского окна.
			//..........................
			hWndClient = CreateWindowEx( WS_EX_CLIENTEDGE,
				"MDICLIENT",
				NULL,
				WS_CHILD | WS_CLIPCHILDREN,
				0, 0, 0, 0,
				hWnd, (HMENU)0xCA0, hInst, &ccs);

			ShowWindow( hWndClient, SW_SHOW );
			for (int i = 0; i < 9; i++)
			{
				vDoc[i].OnCreate();
				vView[i].OnCreate(i, &vDoc[i]);
			}

			SYSTEMTIME today_time;
			int y,mo,d,h,mi,s,milli;
			GetTime(&today_time);// сегодня
			double dn = datenum(today_time) - 1.0;// вчера
			datevec(dn, y, mo, d, h, mi, s, milli);
			

			// Parametrs of start finish date dialog data
			sfddd.hwndParent = hWnd;
			sfddd.nPribor = 1;
			sfddd.shPeriodFlag = 1;
			sfddd.shFormatFlag = 0;
			sfddd.startDay = 26;
			sfddd.startMonth = 11;
			sfddd.startYear = 2004;

			sfddd.finishDay = d;
			sfddd.finishMonth = mo;
			sfddd.finishYear = y;

			sfddd.bMin = true;
			sfddd.bMean = true;
			sfddd.bMax = true;

			sfddd.bPolarization = false;

			sfddd.delim = ';';
			sfddd.delimID = 3;

			strcpy(sfddd.szFileFilter,"*.csv");
			sfddd.nFileFilterID = 0;

			sfddd.fileFormat = 1;
			sfddd.nHowUseFilePath = 0;

			sfddd.bMeanPerDay = false;




			pdrdd.bUseNoise = false;
			pdrdd.shPrintRaportType = 0;

			pdrdd.finishDay = d;
			pdrdd.finishMonth = mo;
			pdrdd.finishYear = y;

			dn = datenum(today_time) - 2.0;// позавчера
			datevec(dn, y, mo, d, h, mi, s, milli);

			pdrdd.startDay = d;
			pdrdd.startMonth = mo;
			pdrdd.startYear = y;


			strcpy(directory,"C:\\Variation");
			
			lpSelectFileDlgData = (LPSELECTFILEDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( SELECTFILEDLGDATA ) );
			strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Выбор файла\0");
			strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
			lpSelectFileDlgData->bIsSignal2Checked = false;
			lpSelectFileDlgData->scaleModeX = 2;

			lpPolyotyDlgData = (LPPOLYOTYFILEDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( POLYOTYFILEDLGDATA ) );
			lpPolyotyDlgData->localTimeOffsetHours = 2;
			lpPolyotyDlgData->lpSelectFileDlgData = lpSelectFileDlgData;

			//lpPolyotyDlgData->delim = '\t';
			//lpPolyotyDlgData->delimID = 0;

			//lpPolyotyDlgData->delim = ' ';
			//lpPolyotyDlgData->delimID = 1;

			lpPolyotyDlgData->delim = ',';
			lpPolyotyDlgData->delimID = 2;

			//lpPolyotyDlgData->delim = ';';
			//lpPolyotyDlgData->delimID = 3;

			lpPolyotyDlgData->bUse_t1 = true;
			//lpPolyotyDlgData->bUse_t2 = true;
			lpPolyotyDlgData->bUse_t2 = false;
			lpPolyotyDlgData->thisIsLocalTime=false;
			lpPolyotyDlgData->timeFormat=0;
			lpPolyotyDlgData->hWnd = hWnd;
			lpPolyotyDlgData->notAddToExistingPlots = false;
			lpPolyotyDlgData->bUseAllCols = true;



			lpSaveAsFileDlgData = (LPSAVEASFILEDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( SAVEASFILEDLGDATA ) );
			strcpy(lpSaveAsFileDlgData->szFileFilter,"*.*");
			strcpy(lpSaveAsFileDlgData->directory,"C:\\Variation\\export");
			lpSaveAsFileDlgData->SaveAsFileType = 0;

			lpHidePlotDlgMem = (LPHIDEPLOTDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( HIDEPLOTDLGDATA ) );


			// диалог печати
			lpPrintDlgMem = (LPPRINTDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( PRINTDLGDATA ) );
			lpPrintDlgMem->bIncludeX = false;
			lpPrintDlgMem->bIncludeY = false;
			lpPrintDlgMem->bIncludeZ = false;
			lpPrintDlgMem->bPrinterNameFound;
			lpPrintDlgMem->dmCopies = 1;
			lpPrintDlgMem->dmOrientation = DMORIENT_LANDSCAPE;
			lpPrintDlgMem->dmPaperSize = DMPAPER_A4;

			// wavelet dialog
			lpLagerDlgMem = (LPLAGERDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( LAGERDLGDATA ) );
			lpLagerDlgMem->bIncludeRealRoots = true;
			


			lpWaveletDlgMem = (LPWAVELETDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( WAVELETDLGDATA ) );
			lpWaveletDlgMem->waveletDataSize = 8;

			lpEarthquakesDlgMem = (LPEARTHQUAKESDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				sizeof( EARTHQUAKESDLGDATA ) );
			lpEarthquakesDlgMem->scaleModeX = 2;
			lpEarthquakesDlgMem->hWnd = hWnd;
			lpEarthquakesDlgMem->shPeriodFlag = 1;

			lpEarthquakesDlgMem->magnitudeBorder = 4.8;
			lpEarthquakesDlgMem->depthIntervalMin = 0.0;
			lpEarthquakesDlgMem->depthIntervalMax = 700.0;

			lpWaveletMem = (LPWAVELETDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
				lpWaveletDlgMem->waveletDataSize * sizeof( WAVELETDATA ) );

			strcpy(lpWaveletMem[0].szWaveletName, "HAAR");
			lpWaveletMem[0].minOrder = 1;
			lpWaveletMem[0].maxOrder = 1;

			strcpy(lpWaveletMem[1].szWaveletName, "DAUBECHIES");
			lpWaveletMem[1].minOrder = 1;
			lpWaveletMem[1].maxOrder = 10;

			strcpy(lpWaveletMem[2].szWaveletName, "SYMLETS");
			lpWaveletMem[2].minOrder = 1;
			lpWaveletMem[2].maxOrder = 8;

			strcpy(lpWaveletMem[3].szWaveletName, "COIFLETS");
			lpWaveletMem[3].minOrder = 1;
			lpWaveletMem[3].maxOrder = 5;

			strcpy(lpWaveletMem[4].szWaveletName, "BIORTOGONAL");
			lpWaveletMem[4].minOrder = 1;
			lpWaveletMem[4].maxOrder = 6;

			strcpy(lpWaveletMem[5].szWaveletName, "MY_BIORTOGONAL");
			lpWaveletMem[5].minOrder = 1;
			lpWaveletMem[5].maxOrder = 3;

			strcpy(lpWaveletMem[6].szWaveletName, "BIORTOGONAL_NONSTANDART");
			lpWaveletMem[6].minOrder = 1;
			lpWaveletMem[6].maxOrder = 2;

			strcpy(lpWaveletMem[7].szWaveletName, "DISCRETE_MEYER");
			lpWaveletMem[7].minOrder = 1;
			lpWaveletMem[7].maxOrder = 1;

			lpWaveletDlgMem->lpWaveletData = lpWaveletMem;

			// try connect
			if(g_bToOpenCom)
				if(ComPort.DoConnect(1))
					ComPort.ReadFromCOM();
WriteRaporto("wnd WM_CREATE end\n");

		}
		break;
	case WM_COMMAND :
		{
			int i;
			switch( LOWORD( wParam ) )
			{
			case ID_TEST2 :
				{
					int nyi = 50,
						nxi = 40,
						nzi = 60;

					// тестирование трёхмерной матрицы
					
					double ***s = AllocDouble3DMat (nyi, nxi, nzi);
					for (int r = 0; r < nyi; r++)
					{
						for (int c = 0; c < nxi; c++)
						{
							for (int p = 0; p < nzi; p++)
							{
								double val = r+c+p;
								char str[255];
								sprintf(str,"s[%d][%d][%d] = %lf", r, c, p, val);
								//MessageBox(0,str,"try",0);
								s[r][c][p] = val;
								sprintf(str,"s[%d][%d][%d] = %lf", r, c, p, s[r][c][p]);
								//MessageBox(0,str,"yes",0);
							}
						}

					}
					for (int r = 0; r < nyi; r++)
					{
						for (int c = 0; c < nxi; c++)
						{
							for (int p = 0; p < nzi; p++)
							{
								double val = r+c+p;
								if (val != s[r][c][p])
								{
									char str[255];
									sprintf(str,"s[%d][%d][%d] = %lf val = %lf", r, c, p, s[r][c][p], val);
									MessageBox(0,str,"",0);
								}
							}
						}

					}
					FreeDouble3DMat(s);

/*                   HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst,
									MAKEINTRESOURCE(IDD_DIALOG_AUDIO_WARNING),
                                                  RT_DIALOG ) );

                   LPVOID lpDialog = LockResource( hDialog );

                   DialogBoxIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcAudioWarning,
                                      	(LPARAM)(LPCTSTR)"Warning Text Warning Text Warning Text Warning Text Warning Text");
*/
				}
				break;
			case ID_TEST_PLOT :
				{
					vdouble x = dsequence(0.0,0.01,1.0),
						y = exp(-x);
					WinPlot(x,y);
				}
				break;
			case ID_TEST_SURF :
				{
					//MessageBox(0,"ID_TEST_SURF","",0);
#if 1
					vdouble x = dsequence(4.0,1.0,14.0);
					vdouble y = dsequence(2.0,1.0,12.0);
#else
					vdouble x = dsequence(-4.0,0.5,4.0);
					vdouble y = dsequence(-2.0,0.5,2.0);
					vdouble x = dsequence(-40.0,5.0,40.);
					vdouble y = dsequence(-20.0,5.0,20.);
#endif



					//vdouble xx = x.VectorsToMatrixProduct(ones(y.Length()));
					//vdouble yy = ones(x.Length()).VectorsToMatrixProduct(y);

					vdouble xx;
					vdouble yy;
					//MessageBox(0,"ID_TEST_SURF","2",0);
					meshgrid(x,y,xx,yy);

					/*char str[255];
					sprintf(str, "lenx = %d leny = %d xx.Size = [%d %d]", x.Length(), y.Length(), xx.GetSize(0), xx.GetSize(1));
					MessageBox(0,str,"ID_TEST_SURF",0);

					sprintf(str, "yy.Size = [%d %d]", yy.GetSize(0), yy.GetSize(1));
					MessageBox(0,str,"ID_TEST_SURF",0);*/

					//vdouble z;
					//MessageBox(0,"ID_TEST_SURF","3",0);
					//z.resize(x.Length(),y.Length(),2.0);


					vdouble z = sin(xx)*cos(yy)*exp(0.2*xx)*exp(0.4*yy);;
					//vdouble z = x.VectorsToMatrixProduct(ones(y.Length()));
					/*sprintf(str, "z.Size = [%d %d]", z.GetSize(0), z.GetSize(1));
					MessageBox(0,str,"ID_TEST_SURF",0);*/

		
					/*x.Write("D:\\_.log","wt","x");
					xx.Write("D:\\_.log","at","xx");
					y.Write("D:\\_.log","at","y");
					yy.Write("D:\\_.log","at","yy");
					z.Write("D:\\_.log","at","z");*/
#if USE_WINSURF
					WinSurf(xx,yy,z);
#endif
				}
				break;
			case ID_TEST_SURF3 :
				{
#ifdef USE_EARTHQUAKES_ON_SURF
					WinSurf();
#endif
				}
				break;
			case ID_TEST_SURF2 :
				{
					//MessageBox(0,"ID_TEST_SURF2","",0);
#if 1
					vdouble X = dsequence(4.0,0.5,8.0);
					vdouble Y = dsequence(2.0,0.5,6.0);
#else
					vdouble X = dsequence(-4.0,1.0,4.0);
					vdouble Y = dsequence(-2.0,1.0,2.0);
#endif


					vdouble XX;
					vdouble YY;
					meshgrid(X,Y,XX,YY);

					vdouble Z = sin(XX)*cos(YY)*exp(0.2*XX)*exp(0.4*YY);

					vdouble XI = dsequence(4.0,0.1,8.0);
					vdouble YI = dsequence(2.0,0.1,6.0);

					/*X.Write("D:\\_.log","wt","X");
					XX.Write("D:\\_.log","at","XX");
					Y.Write("D:\\_.log","at","Y");
					YY.Write("D:\\_.log","at","YY");
					Z.Write("D:\\_.log","at","Z");
					XI.Write("D:\\_.log","at","XI");
					YI.Write("D:\\_.log","at","YI");
					FILE *stream;
					stream = fopen("D:\\_.log","at");*/

					int nx = X.Length();
					int ny = Y.Length();

					int nxi = XI.Length();
					int nyi = YI.Length();

					int r,c;
					double *x, *y, **xx, **yy, **zz;
					double *xi, *yi, **xxi, **yyi, **zzi;

					x = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						nx * sizeof (double));
					y = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						ny * sizeof (double));

					xi = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						nxi * sizeof (double));
					yi = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
						nyi * sizeof (double));

					for (r = 0; r < nx; r++)
						x[r] = X[r];
					for(c = 0; c < ny; c++)
						y[c] = Y[c];

					for (r = 0; r < nxi; r++)
						xi[r] = XI[r];
					for(c = 0; c < nyi; c++)
						yi[c] = YI[c];



					zz = AllocDoubleMat (ny, nx);
					xx = AllocDoubleMat (ny, nx);
					yy = AllocDoubleMat (ny, nx);

					for (r = 0; r < ny; r++)
					{
						for(c = 0; c < nx; c++)
						{
							zz[r][c] = Z(r,c);
						}
					}



					meshgrid( nx, ny, x, y, xx, yy);

					
					xxi = AllocDoubleMat (nyi, nxi);
					yyi = AllocDoubleMat (nyi, nxi);
					zzi = AllocDoubleMat (nyi, nxi);

					meshgrid( nxi, nyi, xi, yi, xxi, yyi);

#if 1					
					cubicInterp2( 
						nx, ny, xx,yy,zz,
						nxi, nyi, xxi, yyi, zzi,0.0);
#else
					linearInterp2( 
						nx, ny, xx,yy,zz,
						nxi, nyi, xxi, yyi, zzi,0.0);
#endif
					

					vdouble ZZI(nyi, nxi);

					for (r = 0; r < nyi; r++)
					{
						for(c = 0; c < nxi; c++)
						{
							ZZI(r,c) = zzi[r][c];
						}
					}
					if(xx) FreeDoubleMat(xx);
					if(yy) FreeDoubleMat(yy);
					if(zz) FreeDoubleMat(zz);
					
					if (xxi) FreeDoubleMat(xxi);
					if (yyi) FreeDoubleMat(yyi);
					if (zzi) FreeDoubleMat(zzi);

					if (x) HeapFree( GetProcessHeap(), 0, x );
					if (y) HeapFree( GetProcessHeap(), 0, y );
					if (xi) HeapFree( GetProcessHeap(), 0, xi );
					if (yi) HeapFree( GetProcessHeap(), 0, yi );

					
					vdouble XXI,YYI;
					meshgrid(XI,YI,XXI,YYI);

#if USE_WINSURF

					WinSurf(XXI,YYI,ZZI);

#endif
				}
				break;
			case ID_TEST_MAP :
				WinMap();
				break;
			case ID_TEST_GEOID :
				WinGeoid();
				break;
			case ID_TEST :
				{
#if 0
					   
					//using namespace std;
					//vector <int> vi;
					//vector<vector<double> > vvd;
					//vector<vdouble>::iterator vItr;

					//vector<vdouble> vv;

#else

					//vect<vdouble, vectObject<vdouble> > vv;
					vect<vdouble> vv;
					vv.OnCreate(0);


					vv.clear();
					for (long len = 1000000; len <= 1000001;len++)
					{
						vv.AddMsg(&dsequence(double (0.0), double (1.0), len));
					}
					
					if (vv.SetCurrentMsgOnFirst())
					{
						do
						{
							char str[255];
							sprintf(str, "index = %d len = %d", vv.GetCurrentMsgIndex(),
							vv.GetCurrentMsg().Length());
						//	char *sa = vv.GetCurrentMsg().disp_str();
							MessageBox(0,"",str,0);
						//	if (sa) HeapFree(GetProcessHeap(), 0, sa);

						}
						while(vv.IncrementCurrentMsg());
					}

#endif
				}
				break;
			case ID_TEST4 :
				{

					Vector<vdouble> vv;
					
					int sz = 2;
					vv.resize(sz);


					for (i = 0; i < sz;i++)
					{
						vv[i] = dsequence(double (0.0), double (1.0), long(1000000));
					}
					
					for ( i = 0; i < vv.Size();i++)
					{
						char str[255];
						sprintf(str, "index = %d len = %d", i,
						vv[i].Length());
						MessageBox(0,"",str,0);
					}

				}
				break;
			case ID_TEST3:
				{
					// Объявляем вектор
					vect<int> v;
					v.OnCreate(0);
					// Создаём новый вектор как внутренний член вектора v
					v.CreateNewVect();
					// Заполняем только что созданный внутренний вектор значениями
					for(int k = 0; k < 5; k++)
						v.AddMsgToLastVect(&k);
					// Создаём ещё один новый вектор как внутренний член вектора v
					v.CreateNewVect();
					// Заполняем только что созданный внутренний вектор значениями
					for(int k = 0; k < 3; k++)
						v.AddMsgToLastVect(&k);

					// Объявляем переменную для приёма значений 
					int cp;
					// Устанавливаем текущий внутренний вектор в начало массива внутренних векторов
					if (v.SetCurrentVectOnFirst())
					{
						do
						{
							// Копируем из текущего внутреннего вектора все значения в объявленную переменную
							while(v.CopyCurrentVectMsgToLast(&cp))
							{
								char st[100];
								sprintf(st,"%d",cp);
								MessageBox(0,st,"",0);
							}
							//v.GetCurrentVect().SetCurrentMsgOnFirst();
						}
						// Перемещаем текущий внутренний вектор
						while(v.IncrementCurrentVect());
					}
					else
						MessageBox(0,"!v.SetCurrentVectOnFirst()","",0);
					if (v.SetCurrentVectOnFirst())
					{
						do
						{
							// Копируем из текущего внутреннего вектора все значения в объявленную переменную
							while(v.CopyCurrentVectMsgToLast(&cp))
							{
								char st[100];
								sprintf(st,"%d",cp);
								MessageBox(0,st,"",0);
							}
						}
						// Перемещаем текущий внутренний вектор
						while(v.IncrementCurrentVect());
					}
					else
						MessageBox(0,"!v.SetCurrentVectOnFirst()","",0);
					//return 0;
					MessageBox(0,"ID_TEST","",0);
					// Создаём новый вектор как внутренний член вектора v
					v.CreateNewVect();
					v.GetLastVect().CreateNewVect();
					// Заполняем только что созданный внутренний вектор значениями
					for(int k = 10; k < 15; k++)
						v.GetLastVect().AddMsgToLastVect(&k);
					// Создаём ещё один новый вектор как внутренний член вектора v
					v.GetLastVect().CreateNewVect();
					// Заполняем только что созданный внутренний вектор значениями
					for(int k = 20; k < 23; k++)
						v.GetLastVect().AddMsgToLastVect(&k);

					// Объявляем переменную для приёма значений 
					// Устанавливаем текущий внутренний вектор в начало массива внутренних векторов
					if (v.GetLastVect().SetCurrentVectOnFirst())
					{
						do
						{
							// Копируем из текущего внутреннего вектора все значения в объявленную переменную
							while(v.GetLastVect().CopyCurrentVectMsgToLast(&cp))
							{
								char st[100];
								sprintf(st,"%d",cp);
								MessageBox(0,st,"",0);
							}
						}
						// Перемещаем текущий внутренний вектор
						while(v.GetLastVect().IncrementCurrentVect());
					}
					else
						MessageBox(0,"!v.GetLastVect().SetCurrentVectOnFirst()","",0);
					// Устанавливаем текущий внутренний вектор в начало массива внутренних векторов
					if (v.SetCurrentVectOnFirst())
					{
						do
						{
							// Копируем из текущего внутреннего вектора все значения в объявленную переменную
							while(v.CopyCurrentVectMsgToLast(&cp))
							{
								char st[100];
								sprintf(st,"%d",cp);
								MessageBox(0,st,"",0);
							}
						}
						// Перемещаем текущий внутренний вектор
						while(v.IncrementCurrentVect());
					}
					else
						MessageBox(0,"!v.SetCurrentVectOnFirst()","",0);
					// Устанавливаем текущий внутренний вектор в начало массива внутренних векторов
					if (v.GetLastVect().SetCurrentVectOnFirst())
					{
						do
						{
							// Копируем из текущего внутреннего вектора все значения в объявленную переменную
							while(v.GetLastVect().CopyCurrentVectMsgToLast(&cp))
							{
								char st[100];
								sprintf(st,"%d",cp);
								MessageBox(0,st,"",0);
							}
						}
						// Перемещаем текущий внутренний вектор
						while(v.GetLastVect().IncrementCurrentVect());
					}
					else
						MessageBox(0,"!v.GetLastVect().SetCurrentVectOnFirst()","",0);
					if (v.SetCurrentVectOnFirst())
					{
						do
						{
							// Копируем из текущего внутреннего вектора все значения в объявленную переменную
							while(v.CopyCurrentVectMsgToLast(&cp))
							{
								char st[100];
								sprintf(st,"%d",cp);
								MessageBox(0,st,"",0);
							}
						}
						// Перемещаем текущий внутренний вектор
						while(v.IncrementCurrentVect());
					}
					else
						MessageBox(0,"!v.SetCurrentVectOnFirst()","",0);

					char st[100];
					sprintf(st,"msgSize %d",v.GetFirstVect().msgSize());
					MessageBox(0,st,"",0);
					sprintf(st,"vectSize %d",v.vectSize());
					MessageBox(0,st,"",0);

				//	v.clearVect();


					
					/*vect<vect<int> > vvi;
					vect<int> vi, vi2;
					for(int j = 0; j < 10; j++)
						vi.AddMsg(&j);

					MessageBox(0,"vi.AddMsg(&j)","",0);

					vvi.AddVect(&vi);

					MessageBox(0,"vvi.AddVect(&vi)","",0);

					vi.clear();

					for(j = 20; j < 45; j++)
						vi.AddMsg(&j);

					vvi.AddVect(&vi);

					vi.clear();

					int cp;
					while(vvi.CopyCurrentToLast(&vi2))
					{
						while(vi2.CopyCurrentToLast(&cp))
						{
							char st[100];
							sprintf(st,"%d",cp);
							MessageBox(0,st,"",0);
						}
					}
					//*/


					/*while(vi.CopyCurrentToLast(&cp))
					{
						char st[100];
						sprintf(st,"%d",cp);
						MessageBox(0,st,"",0);
					}
					vi.SetCurrentOnFirst();
					while(vi.CopyCurrentToLast(&cp))
					{
						char st[100];
						sprintf(st,"%d",cp);
						MessageBox(0,st,"",0);
					}*/
				}
				break;
				
			case ID_DELETE_CALCULATED_GRAPHICS :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].DeleteCalculatedPlots();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_SET_DISPERSION_PLOT :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].SetDispersionPlot();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_LOGARIPHM_OF_DISPERSION :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].LogariphmOfDispersion();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
				
			case ID_HIST_OF_ANGLE :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].HistOfAngle();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_HIST_OF_EARTHQUAKES :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].HistOfEarthQuakes();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_HIST_OF_SIGNAL :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].HistOfSignal();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_LOGARIPHM_OF_SIGNAL :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].LogariphmOfSignal();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_XYZ_3_ANGLE :
				{
					vDoc[0].Angle3(&vDoc[1],&vDoc[2],"Угол X - YZ");
					vDoc[1].Angle3(&vDoc[2],&vDoc[0],"Угол Y - ZX");
					vDoc[2].Angle3(&vDoc[0],&vDoc[1],"Угол Z - XY");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_3_ANGLE2 :
				{
					vDoc[0].Angle32(&vDoc[1],&vDoc[2],"Угол X - YZ 1","Угол X - YZ 2");
					vDoc[1].Angle32(&vDoc[2],&vDoc[0],"Угол Y - ZX 1","Угол Y - ZX 2");
					vDoc[2].Angle32(&vDoc[0],&vDoc[1],"Угол Z - XY 1","Угол Z - XY 2");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_ANGLE :
				{
					vDoc[0].Angle(&vDoc[1],&vDoc[2],"Угол Y-Z");
					vDoc[1].Angle(&vDoc[2],&vDoc[0],"Угол Z-X");
					vDoc[2].Angle(&vDoc[0],&vDoc[1],"Угол X-Y");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_ANGLE2 :
				{
					vDoc[0].Angle2(&vDoc[1],&vDoc[2],"Угол Y-Z 1","Угол Y-Z 2");
					vDoc[1].Angle2(&vDoc[2],&vDoc[0],"Угол Z-X 1","Угол Z-X 2");
					vDoc[2].Angle2(&vDoc[0],&vDoc[1],"Угол Z-X 1","Угол Z-X 2");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_3_LOG_ANGLE :
				{
					vDoc[0].AngleLog3(&vDoc[1],&vDoc[2],"Угол LogX - LogYZ");
					vDoc[1].AngleLog3(&vDoc[2],&vDoc[0],"Угол LogY - LogZX");
					vDoc[2].AngleLog3(&vDoc[0],&vDoc[1],"Угол LogZ - LogXY");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_3_LOG_ANGLE2 :
				{
					vDoc[0].AngleLog32(&vDoc[1],&vDoc[2],"Угол LogX - LogYZ 1","Угол LogX - LogYZ 2");
					vDoc[1].AngleLog32(&vDoc[2],&vDoc[0],"Угол LogY - LogZX 1","Угол LogY - LogZX 2");
					vDoc[2].AngleLog32(&vDoc[0],&vDoc[1],"Угол LogZ - LogXY 1","Угол LogZ - LogXY 2");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_LOG_ANGLE :
				{
					vDoc[0].AngleLog(&vDoc[1],&vDoc[2],"Угол LogY-LogZ");
					vDoc[1].AngleLog(&vDoc[2],&vDoc[0],"Угол LogZ-LogX");
					vDoc[2].AngleLog(&vDoc[0],&vDoc[1],"Угол LogX-LogY");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_XYZ_LOG_ANGLE2 :
				{
					vDoc[0].AngleLog2(&vDoc[1],&vDoc[2],"Угол LogY-LogZ 1","Угол LogY-LogZ 2");
					vDoc[1].AngleLog2(&vDoc[2],&vDoc[0],"Угол LogZ-LogX 1","Угол LogZ-LogX 2");
					vDoc[2].AngleLog2(&vDoc[0],&vDoc[1],"Угол LogZ-LogX 1","Угол LogZ-LogX 2");
				for (i = 0; i < 3; i++)
				{
					
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				}
				break;
			case ID_LOGARIPHM_OF_SIGNAL2 :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].LogariphmOfSignal2();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_LOGARIPHM_OF_FILTRED_SIGNAL :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].LogariphmOfFiltredSignal();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_LOGARIPHM_OF_FILTRED_SIGNAL2 :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].LogariphmOfFiltredSignal2();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_ENERGY_OF_LOG_XYZ :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].Energy();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_ENERGY_OF_FILTRED_LOG_XYZ :
				for (i = 0; i < 3; i++)
				{
					vDoc[i].EnergyOfFiltred();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
				
			case ID_LAGER_SOLVE:
				for (i = 0; i < 3; i++)
				{
					vDoc[i].LagerSolve(true);
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;				
			case ID_LAGER_TRAIN:
				for (i = 0; i < 3; i++)
				{
					vDoc[i].TrainNnet();
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_SURF_OF_TWO_INSTRUMENTS_X:
					vDoc[0].SurfTwoInstruments();
				break;
			case ID_SURF_OF_TWO_INSTRUMENTS_Y:
					vDoc[1].SurfTwoInstruments();
				break;
			case ID_SURF_OF_TWO_INSTRUMENTS_Z:
					vDoc[2].SurfTwoInstruments();
				break;
			case ID_SURF_COVAR_OF_TWO_INSTRUMENTS_X:
					vDoc[0].CovariationApply(2);
				break;
			case ID_SURF_COVAR_OF_TWO_INSTRUMENTS_Y:
					vDoc[1].CovariationApply(2);
				break;
			case ID_SURF_COVAR_OF_TWO_INSTRUMENTS_Z:
					vDoc[2].CovariationApply(2);
				break;

			case ID_PLOT3D_OF_TWO_INSTRUMENTS_X:
					vDoc[0].Plot3DTwoInstruments();
				break;
			case ID_PLOT3D_OF_TWO_INSTRUMENTS_Y:
					vDoc[1].Plot3DTwoInstruments();
				break;
			case ID_PLOT3D_OF_TWO_INSTRUMENTS_Z:
					vDoc[2].Plot3DTwoInstruments();
				break;
			case ID_CORRECT_TIME_SCALE:
					vDoc[0].CorrectTimeScale();
					vView[0].OnResizeGraphsCount(vhWndChild[0]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[0].DrawWithMemToWindow(vhWndChild[0]);
#else
					RECT rect;
					GetClientRect(vhWndChild[0],&rect);
					InvalidateRect(vhWndChild[0],&rect, true);
#endif
				break;
				

			case ID_TIME_COVAR_OF_TWO_INSTRUMENTS:
				for (i = 0; i < 3; i++)
				{
					vDoc[i].CovariationApply(3);
					vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
					vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
					RECT rect;
					GetClientRect(vhWndChild[i],&rect);
					InvalidateRect(vhWndChild[i],&rect, true);
#endif
				}
				break;
			case ID_PRINT_RAPORT_DO:
				{
					printDailyRaport();
				}
				break;				
			case ID_PRINT_RAPORT_VIEW:
				{
					printDailyRaport(false);
				}
				break;				
			case ID_COMMON_DONE:
				{
					createCommonFile();
				}
				break;
/*			case ID_FILE_SAVE_AS:
				{
					ExportFile();
					//createCommonFile2();
				}
				break;*/
			case ID_FILENAME_DONE:
				{
					switch(wFileProc)
					{
					case ID_FILE_OPEN:
						{
							openVarFile(lpSelectFileDlgData->bIsSignal2Checked);
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;
	

					case ID_FILE_IMPORT:
						break;
					case ID_FILE_IMPORT_MATLAB:
						{
							importMatlab();
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;
					case ID_FILE_IMPORT_EXCEL:
						break;					
					case ID_FILE_IMPORT_EXCEL_COMMON_FILE_HALF_OF_DAY:
						{
							importExcelCommonFileHalfOfDay(lpSelectFileDlgData);
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;						
					case ID_FILE_IMPORT_COMMON_POLYOTY:
						{
							//strcpy(lpPolyotyDlgData->szSelectFileDlgName, lpSelectFileDlgData->szSelectFileDlgName);
							DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY), hWnd,
								(DLGPROC)DlgProcPolyoty,(LPARAM)lpPolyotyDlgData);

							//importExcelCommonFileParam(lpSelectFileDlgData);
							/*SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}*/
						}
						break;						
					case ID_FILE_IMPORT_EXCEL_COMMON_FILE_PARAM:
						{
							lpPolyotyDlgData->lpSelectFileDlgData = lpSelectFileDlgData;
							importExcelCommonFileParam(lpPolyotyDlgData);
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;						
					case ID_FILE_IMPORT_EXCEL_COMMON_FILE:
						{
							importExcelCommonFile(lpSelectFileDlgData);
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;						
					case ID_FILE_IMPORT_EARTHQUAKES:
						{
							importEarthQuakes();
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;
					case ID_FILE_IMPORT_EARTHQUAKES_NEIC:
						{
							importEarthQuakesNEIC(lpSelectFileDlgData);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;
					case ID_FILE_IMPORT_EARTHQUAKES_NEIC2:
						{
							importEarthQuakesNEIC2(lpSelectFileDlgData);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}
						break;
						
					case ID_FILE_CONVERT:
						convert();
						break;
					case ID_FILE_CONVERT_TO_MATLAB:
						convertToMatlab();
						break;
					case ID_FILE_CONVERT_TO_EXCEL:
						convertToExcel();
						break;						
					case ID_FILE_CONVERT_TO_MATLAB_ON_SECOND:
						convertToMatlabOnSecond();
						break;
						
					case ID_FILE_CONVERT_TO_UVAROV:
						convertToUvarov();
						break;
					}
					wFileProc = 0;
				}
				break;
			case ID_PRINT_START :				
				{
					HDC hDC;
					DOCINFO di;
					DWORD   fMode = DM_IN_PROMPT;//5;

					//LPSTR    pPrinterName;
					HANDLE  hPrinter;
					PRINTER_DEFAULTSA PDefault;
					LONG userCommand = IDCANCEL;



					PDefault.pDatatype = NULL;
					// Note that you cannot request more rights than you have as a user
					PDefault.DesiredAccess = STANDARD_RIGHTS_REQUIRED | PRINTER_ACCESS_USE;
					PDefault.DesiredAccess = PRINTER_ALL_ACCESS;
					PDefault.pDevMode = NULL;

					long retVal = OpenPrinter(
						lpPrintDlgMem->szPrinterName, 
						&hPrinter, 
						&PDefault);
					if (retVal == 0)
					{
						MessageBox(0, "OpenPrinter Failed!","",0);
						return 0;
					}
					else
					{
						//retVal = PrinterProperties(hWnd, hPrinter);

						// Get the number of bytes required for the full DEVMODE structure 
						retVal = DocumentProperties(hWnd,
							hPrinter,
							lpPrintDlgMem->szPrinterName, 
							NULL,
							NULL,
							0);

						// Allocate memory for the full DEVMODE structure
						pDevModeDefault = (LPDEVMODE)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
							retVal);
						pDevModeUser = (LPDEVMODE)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
							retVal);

						// The function writes the printer driver's current print settings
						// Get the current printer settings 
						retVal = DocumentProperties(hWnd,
							hPrinter,
							lpPrintDlgMem->szPrinterName, 
							pDevModeDefault,  //[out] 
							NULL,//[in] 
							DM_OUT_BUFFER);


						if (retVal < 0)
						{
							ErrorExit("DocumentProperties");
							MessageBox(0, "DocumentProperties Failed!","",0);
						}



						// Modify the appropriate members of the returned DEVMODE structure 
						// and indicate which members were changed 
						// by setting the corresponding bits in the dmFields member of the DEVMODE. 
#if 0
						char str [511];
						sprintf(str,"DM_ORIENTATION = %d DM_PAPERSIZE = %d, DM_COPIES = %d pDevModeDefault->dmFields = %d",
							DM_ORIENTATION, DM_PAPERSIZE , DM_COPIES, pDevModeDefault->dmFields);
						MessageBox(0,str,"before",0);
						pDevModeDefault->dmFields		|= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;

						pDevModeDefault->dmCopies		= lpPrintDlgMem->dmCopies;
						pDevModeDefault->dmOrientation  = lpPrintDlgMem->dmOrientation;
						pDevModeDefault->dmPaperSize	= lpPrintDlgMem->dmPaperSize;

						//pDevModeDefault->dmFields		= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
						pDevModeDefault->dmFields		|= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
						//pDevModeDefault->dmFields		= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
						//pDevModeDefault->dmFields		= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
						
						sprintf(str,"DM_ORIENTATION = %d DM_PAPERSIZE = %d, DM_COPIES = %d pDevModeDefault->dmFields = %d",
							DM_ORIENTATION, DM_PAPERSIZE , DM_COPIES, pDevModeDefault->dmFields);
						MessageBox(0,str,"after",0);
						pDevModeUser->dmFields			|= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
						
						pDevModeUser->dmCopies			= lpPrintDlgMem->dmCopies;
						pDevModeUser->dmOrientation		= lpPrintDlgMem->dmOrientation;
						pDevModeUser->dmPaperSize		= lpPrintDlgMem->dmPaperSize;

						pDevModeUser->dmFields			|= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
#endif			

						if (lParam  == 1)// IDPRINT_SETUP
						{
							// The function presents the printer driver's 
							// Print Setup property sheet and then 
							// changes the settings in the printer's 
							// DEVMODE data structure to those values 
							// specified by the user
							userCommand = DocumentProperties(hWnd,
								hPrinter,
								lpPrintDlgMem->szPrinterName, 
								pDevModeUser,//[out] 
								pDevModeDefault,//[in] 
								DM_IN_PROMPT | DM_OUT_BUFFER);

							if (userCommand < 0)
							{
								ErrorExit("DocumentProperties");
								MessageBox(0, "DocumentProperties Failed!","",0);
							}												
						}
						else// IDPRINT
						{
MessageBox(0,"pre DocumentProperties","",0);
							userCommand = DocumentProperties(hWnd,
								hPrinter,
								lpPrintDlgMem->szPrinterName, 
								pDevModeUser,//[out] 
								pDevModeDefault,//[in] 
								/*DM_IN_PROMPT |*/ DM_OUT_BUFFER);
MessageBox(0,"pre DocumentProperties","",0);

							pDevModeUser->dmCopies			= lpPrintDlgMem->dmCopies;
							pDevModeUser->dmOrientation		= lpPrintDlgMem->dmOrientation;
							pDevModeUser->dmPaperSize		= lpPrintDlgMem->dmPaperSize;

							pDevModeUser->dmFields			|= DM_ORIENTATION | DM_PAPERSIZE | DM_COPIES;
						}

						retVal = ClosePrinter(hPrinter);


					}
				
					bAbortPrinting = FALSE;

WriteRaporto("ID_PRINT_START 8\n");



					// Создать контекст устройства для принтера, 
					// на котором должна быть выполнена печать.
					//........................................
					if (userCommand == IDOK || lParam == 0)
					{
						hDC = CreateDC( "WINSPOOL", 
							lpPrintDlgMem->szPrinterName,
							NULL, pDevModeUser );

						if(hDC != NULL)
						{
							// Установить структуру DOCINFO.
							//.............................
							memset( &di, 0, sizeof( DOCINFO ) );
							di.cbSize      = sizeof( DOCINFO );
							di.lpszDocName = "Variation Graphic";
							
							// Создать диалоговое окно аварийного 
							// прекращения работы.
							//.........................
							hAbortPrintingDlg = CreateDialog( hInst,
								MAKEINTRESOURCE(IDD_DIALOG_ABORT_PRINTING),
								hWnd, (DLGPROC)DlgProcAbortPrinting );


							// Запретить главное окно приложения.
							//.....................................
							EnableWindow( hWnd, FALSE );

							
							// Предусмотреть в процедуре аварийного 
							// прекращения работы обработку сообщений для 					   // диалогового окна аварийного прекращения работы.
							//..................................
							
							SetAbortProc( hDC, (ABORTPROC)AbortPrinting );
							
							// Send output to the printer...
							// Начать печать.
							//....................
							if ( StartDoc( hDC, &di ) != SP_ERROR )
							{
								if (lpPrintDlgMem->bIncludeX)
								{
									// Напечатать страницу 1.
									//..............
									StartPage( hDC );
									vView[0].DrawToPrinter(hDC);
									EndPage( hDC );
								}
								if (lpPrintDlgMem->bIncludeY)
								{
									// Напечатать страницу 2.
									//..............
									StartPage( hDC );
									vView[1].DrawToPrinter(hDC);
									EndPage( hDC );
								}
								if (lpPrintDlgMem->bIncludeZ)
								{
								// Напечатать страницу 3.
									//..............
									StartPage( hDC );
									vView[2].DrawToPrinter(hDC);
									EndPage( hDC );
								}

								// Закончить печать.
								//..............
								EndDoc( hDC );
							}


							// Если пользователь прерывает задание на печать, 					   // прекратить печать документа; в ином случае 					   // уничтожить диалоговое окно аварийного 
							// прекращения работы.
							//....................................
							if ( bAbortPrinting )
								AbortDoc( hDC );
							else
								DestroyWindow( hAbortPrintingDlg );

							EnableWindow( hWnd, TRUE );

							SetFocus( hWnd );
							DeleteDC( hDC );
						}
						else
							ErrorExit("CreateDC");
					}
					if ( pDevModeDefault )
						HeapFree( GetProcessHeap(), 0, pDevModeDefault );
					if ( pDevModeUser )
						HeapFree( GetProcessHeap(), 0, pDevModeUser );
				}
				break;
			case ID_LAGER_PARAM_DIALOG:
				{
                  HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst, 
									MAKEINTRESOURCE(IDD_LAGER_PARAM),
                                                  RT_DIALOG ) );

                   LPVOID lpDialog = LockResource( hDialog );

                   HWND hWavDlg = CreateDialogIndirectParam( hInst,
					   (LPCDLGTEMPLATE)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcLagerParam,
                                      	(LPARAM)lpLagerDlgMem );

                   if (hWavDlg)
					   ShowWindow(hWavDlg, 1);
				}
				break;				
			case ID_WAVLETS_PARAM_DIALOG:
				{
                  HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst, 
									MAKEINTRESOURCE(IDD_WAV_PARAM),
                                                  RT_DIALOG ) );

                   LPVOID lpDialog = LockResource( hDialog );

                   HWND hWavDlg = CreateDialogIndirectParam( hInst,
					   (LPCDLGTEMPLATE)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcWaveletParam,
                                      	(LPARAM)lpWaveletDlgMem );

                   if (hWavDlg)
					   ShowWindow(hWavDlg, 1);
				}
				break;				
			case ID_FILE_PRINT:
				{
					if (!lpPrintDlgMem->bPrinterNameFound)
					{
						LPBYTE pPrinterEnum		= NULL;
						LPBYTE pPrinterEnum3	= NULL;
						DWORD cbNeeded;   // bytes received or required
						DWORD cReturned;  // number of printers enumerated
						DWORD cbNeeded3;   // bytes received or required
						DWORD cReturned3;  // number of printers enumerated

						//
						pPrinterEnum = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
							sizeof( PRINTER_INFO_4 ) );


						if (!EnumPrinters(
							PRINTER_ENUM_CONNECTIONS | 
							PRINTER_ENUM_LOCAL |
							PRINTER_ENUM_DEFAULT,         // printer object types
							NULL,						// name of printer object
							4,							// information level
							pPrinterEnum,				// printer information buffer
							sizeof( PRINTER_INFO_4 ),   // size of printer information buffer
							&cbNeeded,					// bytes received or required
							&cReturned))				// number of printers enumerated
						{
							DWORD lastError = GetLastError();
							if( lastError == lastError) // сетевой запрос не поддерживается
							{
								pPrinterEnum = (unsigned char *)HeapReAlloc( GetProcessHeap(),
									HEAP_ZERO_MEMORY,
									pPrinterEnum,
									sizeof( PRINTER_INFO_1 ) );

								if (!EnumPrinters(
										PRINTER_ENUM_LOCAL |
										PRINTER_ENUM_DEFAULT,         // printer object types
										NULL,						// name of printer object
										1,							// information level
										pPrinterEnum,				// printer information buffer
										sizeof( PRINTER_INFO_1 ),   // size of printer information buffer
										&cbNeeded,					// bytes received or required
										&cReturned))				// number of printers enumerated
								{
									lastError = GetLastError();
									if (lastError == 122)// область данных, перданных для сетевого запроса слишком мала
									{

										pPrinterEnum3 = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
											cbNeeded );
										if(!EnumPrinters(
											PRINTER_ENUM_DEFAULT,         // printer object types
											NULL,						// name of printer object
											1,							// information level
											pPrinterEnum3,				// printer information buffer
											cbNeeded,					// size of printer information buffer
											&cbNeeded3,					// bytes received or required
											&cReturned3))				// number of printers enumerated
										{
											ErrorExit("EnumPrinters(Default)");
											return 0;
										}
										if (cReturned3)
										{
											LPCTSTR DefaultPrinterName = (LPCTSTR)( (LPPRINTER_INFO_1)pPrinterEnum3 )->pName;
											strcpy(lpPrintDlgMem->szPrinterName, DefaultPrinterName);
											lpPrintDlgMem->bPrinterNameFound  = true;
										}


#ifdef DO_RAPORT
	for (DWORD pr = 0; pr < cReturned3; pr++)
	{
	LPCTSTR PrinterName = (LPCTSTR)( ((LPPRINTER_INFO_1)pPrinterEnum3)+pr)->pName;
	WriteRaporto(PrinterName);
	WriteRaporto("\n");
	}
#endif
									}
									else
									{
										ErrorExit("EnumPrinters12");
										return 0;
									}
								}
							}
							else// сетевой запрос поддерживается
							{
								if (lastError == 122)// область данных, перданных для сетевого запроса слишком мала
								{
									pPrinterEnum3 = (unsigned char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
										cbNeeded );
									if(!EnumPrinters(
										PRINTER_ENUM_CONNECTIONS | 
										PRINTER_ENUM_LOCAL | 
										PRINTER_ENUM_DEFAULT,         // printer object types
										NULL,						// name of printer object
										4,							// information level
										pPrinterEnum3,				// printer information buffer
										cbNeeded,					// size of printer information buffer
										&cbNeeded3,					// bytes received or required
										&cReturned3))				// number of printers enumerated
									{
										ErrorExit("EnumPrinters(Default)");
										return 0;
									}

									if (cReturned3)
									{
										LPCTSTR DefaultPrinterName = (LPCTSTR)( (LPPRINTER_INFO_4)pPrinterEnum3 )->pPrinterName;
										strcpy(lpPrintDlgMem->szPrinterName, DefaultPrinterName);
										lpPrintDlgMem->bPrinterNameFound  = true;
									}

#ifdef DO_RAPORT
	for (DWORD pr = 0; pr < cReturned3; pr++)
	{
		LPCTSTR PrinterName = (LPCTSTR)( ((LPPRINTER_INFO_4)pPrinterEnum3)+pr)->pPrinterName;
	WriteRaporto(PrinterName);
	WriteRaporto("\n");
	}
#endif
								}
								else
								{
									ErrorExit(lastError, "EnumPrinters1");
									return 0;
								}
							}
						}
#ifdef DO_RAPORT
	char str[255];

	sprintf(str,"cbNeeded = %lu cReturned(number of printers enumerated) = %lu\n",cbNeeded, cReturned);
	WriteRaporto(str);
	sprintf(str,"cbNeeded = %ld cReturned(number of printers enumerated) = %ld\n",cbNeeded, cReturned);
	WriteRaporto(str);
	sprintf(str,"cbNeeded3 = %lu cReturned3(number of printers enumerated) = %lu\n",cbNeeded3, cReturned3);
	WriteRaporto(str);
#endif

						if ( pPrinterEnum )
							HeapFree( GetProcessHeap(), 0, pPrinterEnum );
						if ( pPrinterEnum3 )
							HeapFree( GetProcessHeap(), 0, pPrinterEnum3 );
					}
					SendMessage(hWnd, WM_COMMAND, ID_PRINT_START, (LPARAM)0);
				}
				break;
			case ID_HIDE_PLOTS:
				{
					HWND hActiveWnd;

					// активное дочернее окно.
					//...............................
					hActiveWnd = (HWND)SendMessage( hWndClient, 											    
					  WM_MDIGETACTIVE,                                                          
					  0, 0 );

					int iWnd = int(GetWindowWord( hActiveWnd, 0 ));

					lpHidePlotDlgMem->iWnd = iWnd;
					lpHidePlotDlgMem->hActiveWnd = hActiveWnd;

					 
                   HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_HIDE_PLOTS),
                                                  RT_DIALOG ) );

                  LPVOID lpDialog = LockResource( hDialog );

				  HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcHidePlot,
                                      	(LPARAM)lpHidePlotDlgMem );
				  ShowWindow(hDlg, SW_SHOW);


				}
				break;
			case ID_KORRELATION_COEFFICIENT:
				{
					HWND hActiveWnd;

					// активное дочернее окно.
					//...............................
					hActiveWnd = (HWND)SendMessage( hWndClient, 											    
					  WM_MDIGETACTIVE,                                                          
					  0, 0 );

					int iWnd = int(GetWindowWord( hActiveWnd, 0 ));

					lpHidePlotDlgMem->iWnd = iWnd;
					lpHidePlotDlgMem->hActiveWnd = hActiveWnd;
					HRSRC hrsrc = FindResource( hInst, 
									MAKEINTRESOURCE(IDD_DIALOG_KORRELATION_COEFFICIENT),
                                                  RT_DIALOG );

					 if (hrsrc == NULL)
						 ErrorExit("FindResource");
                   HANDLE hDialog = LoadResource( hInst,hrsrc);
					 if (hDialog == NULL)
						 ErrorExit("LoadResource");

                  LPVOID lpDialog = LockResource( hDialog );
					 if (lpDialog == NULL)
						 ErrorExit("LockResource");///this is not right

				  HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcCorrelationCoefficientPlot,
                                      	(LPARAM)lpHidePlotDlgMem );
					 if (hDlg == NULL)
						 ErrorExit("CreateDialogIndirectParam");

					ShowWindow(hDlg, SW_SHOW);


				}
				break;
			case ID_EDIT_FONT:
				{
//HWND hwnd;                // owner window
//HDC hdc;                  // display device context of owner window

CHOOSEFONT cf;            // common dialog box structure
static LOGFONT lf;        // logical font structure
static DWORD rgbCurrent;   // current text color
HFONT hfont/*, hfontPrev*/;
//DWORD rgbPrev;

// Initialize CHOOSEFONT
ZeroMemory(&cf, sizeof(cf));
cf.lStructSize = sizeof (cf);
cf.hwndOwner = hWnd;
cf.lpLogFont = &lf;
cf.rgbColors = rgbCurrent;
cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

if (ChooseFont(&cf)==TRUE) {
    hfont = CreateFontIndirect(cf.lpLogFont);
//    hfontPrev = (HFONT__ *)SelectObject(hdc, hfont);
//    rgbCurrent= cf.rgbColors;
//    rgbPrev = SetTextColor(hdc, rgbCurrent);

}


				}
				break;

			case ID_FILE_PRINT_PROP:
				{
					DisplayPrintPropertySheet( hWnd  
						/* Window that owns the property sheet*/);

				}
				break;

			case ID_FILE_PRINT_SETUP:
				{
                   HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_PRINT),
                                                  RT_DIALOG ) );

                  LPVOID lpDialog = LockResource( hDialog );

                   DialogBoxIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcPrintParam,
                                      	(LPARAM)lpPrintDlgMem );
				}
				break;

			case ID_FILE_PRINT_RAPORT_ON_PERIOD:
				{
                   HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_PRINT_RAPORT),
                                                  RT_DIALOG ) );

                  LPVOID lpDialog = LockResource( hDialog );

                   DialogBoxIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcPrintDailyRaportParam,
                                      	(LPARAM)lpPrintDlgMem );
				}
				break;
				
			case ID_FILE_COMMON2:
				{
					new CommonMeanFileDialog(hWnd);
				}
				break;
			case ID_FILE_COMMON:
				{
					wFileProc = ID_FILE_COMMON;
					DialogBox( hInst, MAKEINTRESOURCE(IDD_DIALOG_START_FINISH_DATE), hWnd,
                      (DLGPROC)DlgProcStartFinishDate );
				}
				break;
			case ID_FILE_OPEN:
				{
					wFileProc = ID_FILE_OPEN;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.var");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Открыть файл вариаций"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData );
				}
				break;
			case ID_FILE_IMPORT:
				{
					/*wFileProc = ID_FILE_IMPORT;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.csv");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт файла вариаций"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData );*/
					if (OpenFileDlg(hWnd, "All\0*.*\0Text\0*.TXT\0") == S_OK)
						{
							import(lpSelectFileDlgData->bIsSignal2Checked);
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}

				}
				break;
			case ID_FILE_SAVE_AS:
				{
					wFileProc = ID_FILE_SAVE_AS;
					strcpy(lpSaveAsFileDlgData->szFileFilter,"*.*");
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE_SAVE_AS), hWnd,
                      (DLGPROC)DlgProcSaveAsFile,(LPARAM)lpSaveAsFileDlgData );
				}
				break;
			case ID_FILE_IMPORT_MATLAB:
				{
					wFileProc = ID_FILE_IMPORT_MATLAB;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.txt");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт формата Матлаб"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);
				}
				break;			
			case ID_FILE_IMPORT_EXCEL:
				{
					/*wFileProc = ID_FILE_IMPORT_EXCEL;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт формата Excel"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);*/
					if (OpenFileDlg(hWnd, "All\0*.*\0Text\0*.TXT\0") == S_OK)

						{
							importExcel(lpSelectFileDlgData);
							SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
							for (int i = 0; i<3; i++)
							{
								vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
								vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
								RECT rect;
								GetClientRect(vhWndChild[i],&rect);
								InvalidateRect(vhWndChild[i],&rect, true);
#endif
							}
						}

				}
				break;
			case ID_FILE_IMPORT_EXCEL_COMMON_FILE:
				{
					wFileProc = ID_FILE_IMPORT_EXCEL_COMMON_FILE;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт формата Excel Сводный файл"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);
				}
				break;
			case ID_FILE_IMPORT_EXCEL_COMMON_FILE_PARAM:
				{
					wFileProc = ID_FILE_IMPORT_EXCEL_COMMON_FILE_PARAM;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт формата Excel Сводный файла параметров"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);
				}
				break;
			case ID_FILE_IMPORT_COMMON_POLYOTY:
				{
					/*wFileProc = ID_FILE_IMPORT_COMMON_POLYOTY;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт Сводный файла полётов"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);*/

					if (OpenFileDlg(hWnd, "All\0*.*\0Text\0*.TXT\0") == S_OK)
						DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY), hWnd,
							(DLGPROC)DlgProcPolyoty,(LPARAM)lpPolyotyDlgData);
				}
				break;
			case ID_FILE_IMPORT_EXCEL_COMMON_FILE_HALF_OF_DAY:
				{
					wFileProc = ID_FILE_IMPORT_EXCEL_COMMON_FILE_HALF_OF_DAY;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт формата Excel Сводный файл полусуточный"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);
				}
				break;
			case ID_FILE_IMPORT_EARTHQUAKES:
				{
					wFileProc = ID_FILE_IMPORT_EARTHQUAKES;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт Землетрясений КОМСП"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData );
				}
				break;					
			case ID_EARTHQUAKES_DLG:
				{
                   HANDLE hDialog = LoadResource( hInst,
                                    FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_EARTHQUAKES),
                                                  RT_DIALOG ) );

                  LPVOID lpDialog = LockResource( hDialog );

				  HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
                                      	(DLGPROC)DlgProcEarthquakes,
                                      	(LPARAM)lpEarthquakesDlgMem );
				  ShowWindow(hDlg, SW_SHOW);

				}
				break;
			case ID_FILE_IMPORT_EARTHQUAKES_NEIC2:
				{
					/*wFileProc = ID_FILE_IMPORT_EARTHQUAKES_NEIC;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт Землетрясений NEIC"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile ,(LPARAM)lpSelectFileDlgData);*/

					if (OpenFileDlg(hWnd, "All\0*.*\0Text\0*.TXT\0") == S_OK)
					{

						importEarthQuakesNEIC2(lpSelectFileDlgData);

						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_EARTHQUAKES),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcEarthquakes,
											(LPARAM)lpEarthquakesDlgMem );
						ShowWindow(hDlg, SW_SHOW);
					}


/*					SendMessage(hWnd,WM_COMMAND,ID_FILE_NEW,0);
					for (int i = 0; i<3; i++)
					{
						vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i],&rect);
						InvalidateRect(vhWndChild[i],&rect, true);
#endif
					}*/

				}
				break;				
			case ID_FILE_IMPORT_EARTHQUAKES_NEIC:
				{
					wFileProc = ID_FILE_IMPORT_EARTHQUAKES_NEIC2;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.*");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Импорт Землетрясений NEIC 2"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile ,(LPARAM)lpSelectFileDlgData);
				}
				break;				
			case ID_FILE_CONVERT:
				{
					wFileProc = ID_FILE_CONVERT;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.csv");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Конверт из старого формата"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData );
				}
				break;
			case ID_FILE_CONVERT_TO_MATLAB:
				{
					wFileProc = ID_FILE_CONVERT_TO_MATLAB;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.csv");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Конверт к формату Матлаб 1 min"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData );
				}
				break;
			case ID_FILE_CONVERT_TO_EXCEL:
				{
					wFileProc = ID_FILE_CONVERT_TO_EXCEL;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.csv");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Конверт к формату Excel 1 min"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData);
				}
				break;
			case ID_FILE_CONVERT_TO_MATLAB_ON_SECOND:
				{
					wFileProc = ID_FILE_CONVERT_TO_MATLAB_ON_SECOND;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.csv");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Конверт к формату matlab 1sec"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile ,(LPARAM)lpSelectFileDlgData);
				}
				break;
			case ID_FILE_CONVERT_TO_UVAROV:
				{
					wFileProc = ID_FILE_CONVERT_TO_UVAROV;
					strcpy(lpSelectFileDlgData->szFileFilter,"*.csv");
					strcpy(lpSelectFileDlgData->szSelectFileDlgName,"Конверт к формату Уварова"); 
					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE), hWnd,
                      (DLGPROC)DlgProcSelectFile,(LPARAM)lpSelectFileDlgData );
				}
				break;
			case ID_SET_DISPLAY_MODE:
				{
					g_bDisplayMode = true;
					ComPort.StartHandling();
				}
				break;
			case ID_CANCEL_DISPLAY_MODE:
				{
					g_bDisplayMode = false;
				}
				break;
			case ID_SET_REALTIME_WAVELET_MODE:
				{
					g_bRealTimeWaveletMode = true;
					g_btoDisplayWavelet = true;
				}
				break;
			case ID_UNSET_REALTIME_WAVELET_MODE:
				{
					g_bRealTimeWaveletMode = false;
					g_btoDisplayWavelet = false;
				}
				break;
			case ID_SOLVE_WAVLETS:
				{
					g_btoDisplayWavelet = true;
					for (int i = 0; i<3; i++)
					{
						vDoc[i].WaveletEpsilonApply();
						vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i],&rect);
						InvalidateRect(vhWndChild[i],&rect, true);
#endif
					}
				}
				break;
			case ID_COVAR_OF_TWO_INSTRUMENTS:
				{
					for (int i = 0; i<3; i++)
					{
						vDoc[i].CovariationApply(0);
						vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i],&rect);
						InvalidateRect(vhWndChild[i],&rect, true);
#endif
					}
				}
				break;
			case ID_COVAR_OF_TWO_INSTRUMENTS_LOG:
				{
					for (int i = 0; i<3; i++)
					{
						vDoc[i].CovariationApply(1);
						vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i],&rect);
						InvalidateRect(vhWndChild[i],&rect, true);
						//SendMessage(vhWndChild[i],WM_ERASEBKGND,0,0);
#endif
					}
				}
				break;
			case ID_COV_TWO_INSTR_ANALIZE:
				{
					for (int i = 0; i<3; i++)
					{
						vDoc[i].CovariationAnalize();
						vView[i].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i],&rect);
						InvalidateRect(vhWndChild[i],&rect, true);
#endif
					}
				}
				break;
			case ID_SET_REAL_TIME_CORR_MODE:
				{
					g_bRealTimeCovariationMode = true;
				}
				break;
			case ID_UNSET_REAL_TIME_CORR_MODE:
				{
					g_bRealTimeCovariationMode = false;
				}
				break;
			case ID_REVERSE :
				{
					g_btoReverseCovariation ^= true;
				}
				break;
			case ID_SET_DIRECT_CORRELATION_MODE :
				{
					g_btoReverseCovariation = false;
				}
				break;
			case ID_SET_REVERSE_CORRELATION_MODE :
				{
					g_btoReverseCovariation = true;
				}
				break;
			case ID_SOLVE_CORRELATIONS:
				{
					int i;
					for (i = 0; i < 3; i++)
					{
						int j = i+1;
						if(j > 2)
							j = 0;
						vDoc[i+3].Covariation(&vDoc[i], &vDoc[j], g_btoReverseCovariation);
						vView[i+3].OnResizeGraphsCount(vhWndChild[i]);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i+3].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i+3],&rect);
						InvalidateRect(vhWndChild[i+3],&rect, true);
#endif
					}
					for (i = 0; i < 3; i++)
					{
						vDoc[i+6].Covariation(&vDoc[i], &vDoc[i], g_btoReverseCovariation);
#ifdef DRAW_WITH_MEM_TO_WINDOW
						vView[i+6].DrawWithMemToWindow(vhWndChild[i]);
#else
						RECT rect;
						GetClientRect(vhWndChild[i+6],&rect);
						InvalidateRect(vhWndChild[i+6],&rect, true);
#endif
					}
				}
				break;
			case ID_SAVE_GRAPH_AS_METAFILE:
				{
					HWND hActiveWnd;

					// активное дочернее окно.
					//...............................
					hActiveWnd = (HWND)SendMessage( hWndClient, 											    
					  WM_MDIGETACTIVE,                                                          
					  0, 0 );

					if ( hActiveWnd )
					 SendMessage( hActiveWnd, WM_COMMAND,
								 ID_SAVE_GRAPH_AS_METAFILE, 0 );
				}
				break;				
			case ID_VIEW_FULL_ZOOM :
				{
					HWND hActiveWnd;

					// активное дочернее окно.
					//...............................
					hActiveWnd = (HWND)SendMessage( hWndClient, 											    
					  WM_MDIGETACTIVE,                                                          
					  0, 0 );

					if ( hActiveWnd )
					 SendMessage( hActiveWnd, WM_COMMAND,
								 ID_VIEW_FULL_ZOOM, 0 );
				}
				break;
			case ID_VIEW_SCALE_Y_ON_HSCROLL :
				{
					if (g_ToScaleYOnHScroll)
					{
						g_ToScaleYOnHScroll = false;

						CheckMenuItem(GetMenu( hWnd ), 
							ID_VIEW_SCALE_Y_ON_HSCROLL,
							MF_BYCOMMAND | MF_UNCHECKED);
					}
					else
					{
						g_ToScaleYOnHScroll = true;

						CheckMenuItem(GetMenu( hWnd ), 
							ID_VIEW_SCALE_Y_ON_HSCROLL,
							MF_BYCOMMAND | MF_CHECKED);
					}
					HWND hActiveWnd;

					// активное дочернее окно.
					//...............................
					hActiveWnd = (HWND)SendMessage( hWndClient, 											    
					  WM_MDIGETACTIVE,                                                          
					  0, 0 );

					if ( hActiveWnd )
					{
						RECT rect;
						GetWindowRect(hActiveWnd, &rect);
						InvalidateRect(hActiveWnd, &rect, true);
					}
				}
				break;

                 case ID_COM_CONNECT :
					 {
						 ComPort.DoConnect(1);
					 }
					 break;
                 case ID_COM2_CONNECT :
					 {
						 ComPort.DoConnect(2);
					 }
					 break;
                case ID_COM_READ :
					 {
						  ComPort.ReadFromCOM();
					 }
					 break;
                 case ID_COM_CLOSE :
					 {
						if (!ComPort.m_bTerminatedCOMThread)
						{
							DWORD dwChildID;
							HANDLE hAudioWarningThread;
							hAudioWarningThread = ::CreateThread(NULL, 0, 
								AudioWarning, 
								reinterpret_cast<LPVOID>(NULL), 
								0,
								&dwChildID );
							if (IDCANCEL == ::MessageBox(
								NULL,
								"Идёт процесс записи\nВы уверены, что хотите закрыть COM порт?", 
								"Закрытие COM порта",
								MB_OKCANCEL))
							{
								TerminateThread(hAudioWarningThread, 0);
								return 0;
							}
							TerminateThread(hAudioWarningThread, 0);
						}
						if (ComPort.m_bIsConnected)
								ComPort.CloseConnection();
					 }
					 break;
				 case ID_FILE_AUTOCOV:
					 {
						int i;
						 if (opened_autocov == 0)
						 {
							 char str[32];

							 for (i = 6; i < 9; i++)
							 {
WriteRaporto("ID_FILE_COV\n");

								switch (i)
								{
								case 6:
									strcpy(str,"Автокорреляция X\0");
									break;
								case 7:
									strcpy(str,"Автокорреляция Y\0");
									break;
								case 8:
									strcpy(str,"Автокорреляция Z\0");
									break;
								}
								strcpy(vDoc[i].m_sTitle, str);

								// Создание нового дочернего окна.
								//...........................
								vhWndChild[i] = CreateMDIWindow( (LPTSTR)lpszChild,
															 str,
															 NULL/*WS_VSCROLL*/,
															 CW_USEDEFAULT, 									     	   
															 CW_USEDEFAULT,
															 CW_USEDEFAULT, 										   
															 CW_USEDEFAULT,
															 hWndClient, hInst, 
															 LPARAM(i));

								if ( vhWndChild[i] )
								{
									opened_autocov++;
									ShowWindow( vhWndChild[i], SW_SHOW );
								}
							 }
						 }
						 HWND WndArray[3];
						 for (i = 0; i<3; i++)
							 WndArray[i] = vhWndChild[6+i];
#if 0
						TileWindows( hWndClient, MDITILE_VERTICAL, NULL, 3, WndArray );
#else
						TileWindows( hWndClient, MDITILE_HORIZONTAL, NULL, 3, WndArray );
#endif
						 for (i = 0; i<3; i++)
							SendMessage( hWndClient, WM_MDIACTIVATE,
											 (WPARAM)WndArray[i], 0 );

					 }
					 break;
				 case ID_FILE_COV:
					 {
						int i;
						 if (opened_cov == 0)
						 {
							 char str[32];

							 for (i = 3; i < 6; i++)
							 {
WriteRaporto("ID_FILE_COV\n");

								switch (i)
								{
								case 3:
									strcpy(str,"Кросс-корреляция X-Y\0");
									break;
								case 4:
									strcpy(str,"Кросс-корреляция Y-Z\0");
									break;
								case 5:
									strcpy(str,"Кросс-корреляция Z-X\0");
									break;
								}

								strcpy(vDoc[i].m_sTitle, str);

								// Создание нового дочернего окна.
								//...........................
								vhWndChild[i] = CreateMDIWindow( (LPTSTR)lpszChild,
															 str,
															 NULL/*WS_VSCROLL*/,
															 CW_USEDEFAULT, 									     	   
															 CW_USEDEFAULT,
															 CW_USEDEFAULT, 										   
															 CW_USEDEFAULT,
															 hWndClient, hInst, 
															 LPARAM(i));

								if ( vhWndChild[i] )
								{
									opened_cov++;
									ShowWindow( vhWndChild[i], SW_SHOW );
								}
							 }
						 }
						 HWND WndArray[3];
						 for (i = 0; i<3; i++)
							 WndArray[i] = vhWndChild[3+i];
#if 0
						TileWindows( hWndClient, MDITILE_VERTICAL, NULL, 3, WndArray );
#else
						TileWindows( hWndClient, MDITILE_HORIZONTAL, NULL, 3, WndArray );
#endif
						 for (i = 0; i<3; i++)
							SendMessage( hWndClient, WM_MDIACTIVATE,
											 (WPARAM)WndArray[i], 0 );

					 }
					 break;
                  case ID_FILE_NEW :
                         { 
							 int i;
							 if (opened == 0)
							 {
							 char str[32];

							 for (i = 0; i < 3; i++)
							 {
WriteRaporto("ID_FILE_NEW\n");

								switch (i)
								{
								case 0:
									strcpy(str,"Сигнал антены X\0");
									break;
								case 1:
									strcpy(str,"Сигнал антены Y\0");
									break;
								case 2:
									strcpy(str,"Сигнал антены Z\0");
									break;
								}
								//strcpy(vDoc[i].m_sTitle, str);

WriteRaporto("ID_FILE_NEW 2\n");
								// Создание нового дочернего окна.
								//...........................
WriteRaporto("ID_FILE_NEW 2 a\n");
								vhWndChild[i] = CreateMDIWindow( (LPTSTR)lpszChild,
															 str,
															 NULL/*WS_VSCROLL*/,
															 CW_USEDEFAULT, 									     	   
															 CW_USEDEFAULT,
															 CW_USEDEFAULT, 										   
															 CW_USEDEFAULT,
															 hWndClient, hInst, 
															 LPARAM(i));

WriteRaporto("ID_FILE_NEW 4\n");
								if ( vhWndChild[i] )
								{
									opened++;
									//ShowWindow( vhWndChild[i], SW_SHOW );
WriteRaporto("ID_FILE_NEW 5\n");
								}
							 }
							 }
							 HWND WndArray[3];
						 for (i = 0; i<3; i++)
							 WndArray[i] = vhWndChild[i];
#if 0
						TileWindows( hWndClient, MDITILE_VERTICAL, NULL, 3, WndArray );
#else
						TileWindows( hWndClient, MDITILE_HORIZONTAL, NULL, 3, WndArray );
#endif
						 for (i = 0; i<3; i++)
							SendMessage( hWndClient, WM_MDIACTIVATE,
											 (WPARAM)WndArray[i], 0 );
                         }
                         break;

                case ID_FILE_CLOSE :
                       {
                          HWND hActiveWnd;
						  do{

                          // Закрыть активное дочернее окно.
                          //...............................
                          hActiveWnd = (HWND)SendMessage( hWndClient, 											    
							  WM_MDIGETACTIVE,                                                          
							  0, 0 );

						  int iWnd = int(GetWindowWord( hActiveWnd, 0 ));

                          if ( hActiveWnd && iWnd < 3)
						  {
							  opened--;
                             SendMessage( hWndClient, WM_MDIDESTROY,
                                         (WPARAM)hActiveWnd, 0 );
						  }				 
        
                          if ( hActiveWnd)
                             SendMessage( hWndClient, WM_MDINEXT,
                                         (WPARAM)hActiveWnd, 0 );
						  }
						  while( hActiveWnd  && opened > 0);
                       }
                       break;

                case ID_FILE_CLOSE_COV :
                       {
                          HWND hActiveWnd;
						  do{

                          // Закрыть активное дочернее окно.
                          //...............................
                          hActiveWnd = (HWND)SendMessage( hWndClient, 											    
							  WM_MDIGETACTIVE,                                                          
							  0, 0 );

						  int iWnd = int(GetWindowWord( hActiveWnd, 0 ));

                          if ( hActiveWnd && 2 < iWnd  && iWnd < 6)
						  {
							  opened_cov--;
                             SendMessage( hWndClient, WM_MDIDESTROY,
                                         (WPARAM)hActiveWnd, 0 );
						  }
                          if ( hActiveWnd)
                             SendMessage( hWndClient, WM_MDINEXT,
                                         (WPARAM)hActiveWnd, 0 );
						  }
						  while( hActiveWnd  && opened_cov > 0);
                       }
                       break;


					case ID_FILE_CLOSE_AUTOCOV :
                       {
                          HWND hActiveWnd;
						  do{

                          // Закрыть активное дочернее окно.
                          //...............................
                          hActiveWnd = (HWND)SendMessage( hWndClient, 											    
							  WM_MDIGETACTIVE,                                                          
							  0, 0 );

						  int iWnd = int(GetWindowWord( hActiveWnd, 0 ));

                          if ( hActiveWnd && 5 < iWnd  && iWnd < 9)
						  {
							  opened_autocov--;
                             SendMessage( hWndClient, WM_MDIDESTROY,
                                         (WPARAM)hActiveWnd, 0 );
						  }
                          if ( hActiveWnd)
                             SendMessage( hWndClient, WM_MDINEXT,
                                         (WPARAM)hActiveWnd, 0 );
						  }
						  while( hActiveWnd  && opened_autocov > 0);
                       }
                       break;


                case ID_WINDOW_ARRANGE :
					{
                        ArrangeIconicWindows( hWndClient);
					}
                    break;
                case ID_WINDOW_CASCADE :
					{
                        CascadeWindows(hWndClient, MDITILE_SKIPDISABLED, NULL, 0, NULL);
					}
                    break;
                case ID_WINDOW_TILEHORZ :
					{
                        TileWindows( hWndClient, MDITILE_HORIZONTAL, NULL, 0, NULL );
					}
                    break;
                case ID_WINDOW_TILEVERT :
					{
                        TileWindows( hWndClient, MDITILE_VERTICAL, NULL, 0, NULL );
					}
                    break;
                 case ID_FILE_EXIT :
                        SendMessage( hWnd, WM_CLOSE,0,0 );
                        break;
                default :
                       return( DefFrameProc( hWnd, hWndClient, uMsg,
                               wParam, lParam ) );
              }
              break;
		  }
		  break;
		 case WM_CLOSE :
			  {
				if (!ComPort.m_bTerminatedCOMThread)
				{
					DWORD dwChildID;
					HANDLE hAudioWarningThread;
					hAudioWarningThread = ::CreateThread(NULL, 0, 
						AudioWarning, 
						reinterpret_cast<LPVOID>(NULL), 
						0,
						&dwChildID );
					if (IDCANCEL == ::MessageBox(
						NULL,
						"Идёт процесс записи\nВы уверены, что хотите прервать работу программы?", 
						"Завершение работы",
						MB_OKCANCEL))
					{
						TerminateThread(hAudioWarningThread, 0);
						return 0;
					}
					TerminateThread(hAudioWarningThread, 0);
				}

				if (ComPort.m_bIsConnected)
					ComPort.CloseConnection();
				SendMessage( hWnd, WM_DESTROY,0,0 );
			  }
			  break;

      case WM_DESTROY :
		  {	
			  if ( lpSaveAsFileDlgData )
				  HeapFree( GetProcessHeap(), 0, lpSaveAsFileDlgData );
			  if ( lpSelectFileDlgData )
				  HeapFree( GetProcessHeap(), 0, lpSelectFileDlgData );
			  if ( lpPrintDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpPrintDlgMem );
			  if ( lpHidePlotDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpHidePlotDlgMem );
			  if ( lpWaveletMem )
				  HeapFree( GetProcessHeap(), 0, lpWaveletMem );
			  if ( lpWaveletDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpWaveletDlgMem );
			  if ( lpLagerDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpLagerDlgMem );
			  if ( lpPolyotyDlgData )
				  HeapFree( GetProcessHeap(), 0, lpPolyotyDlgData );
			  if ( lpEarthquakesDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpEarthquakesDlgMem );
			  
#if USE_MEMORY_TRACK
#ifdef _DEBUG
				DumpUnfreed();
#endif
#endif
			  
              PostQuitMessage(0);
		  }
		  break;

      default :
             return( DefFrameProc( hWnd, hWndClient, uMsg, wParam, lParam ) );
   }

   return( 0L );
}
LRESULT CALLBACK ChildWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	int iWnd = int(GetWindowWord( hWnd, 0 ));
#ifdef DRAW_TO_META_FILE 
	PAINTSTRUCT ps;
#endif
#ifdef DRAW_WITH_MEM_TO_WINDOW
	PAINTSTRUCT ps;
#endif
	switch( uMsg )
	{
	case WM_RBUTTONDOWN :
		{
WriteRaporto("cld WM_RBUTTONDOWN\n");
			unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
			unsigned short yPos = HIWORD(lParam); // vertical position of pointer 		}
			vView[iWnd].OnRButtonDown(hWnd, xPos, yPos);
WriteRaporto("cld WM_RBUTTONDOWN end\n");
		}
		break;
	case WM_LBUTTONDOWN :
		{
			unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
			unsigned short yPos = HIWORD(lParam); // vertical position of pointer 		}
			vView[iWnd].OnLButtonDown(hWnd, xPos, yPos);
		}
		break;
	case WM_MOUSEMOVE :
		{
			unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
			unsigned short yPos = HIWORD(lParam); // vertical position of pointer 		}
			switch( LOWORD( wParam ) )
			{
			case MK_LBUTTON :
				{
					vView[iWnd].OnLButtonDownMouseMove(hWnd, xPos, yPos);
				}
				break;
			case MK_RBUTTON :
				{
					vView[iWnd].OnRButtonDownMouseMove(hWnd, xPos, yPos);
				}
				break;
			}
		}
		break;
	case WM_MOUSEWHEEL :
		{
			int zDelta = (int) wParam; // wheel rotation 
			vView[iWnd].VerticalZoom(hWnd, zDelta, false);
			//unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
			//unsigned short yPos = HIWORD(lParam); // vertical position of pointer 		}
		}
		break;
#ifndef DRAW_WITH_MEM_TO_WINDOW
	case WM_ERASEBKGND :
		{
			///long lrez = DefMDIChildProc( hWnd, uMsg, wParam, lParam );

#ifdef DRAW_TO_META_FILE
			vView[iWnd].DrawToMetaFile(hWnd);
#else
#ifdef DRAW_TO_WINDOW
			vView[iWnd].DrawToWindow(hWnd, false);
#endif
#endif
			return true
		}
		break;
#endif

#ifdef DRAW_WITH_MEM_TO_WINDOW
	case WM_PAINT :
		{
			 BeginPaint( hWnd, &ps );
			 vView[iWnd].OnPaint(hWnd, &ps);
			 EndPaint( hWnd, &ps );
		}	 
		break;
#endif
#ifdef DRAW_TO_META_FILE
	case WM_PAINT :
		{
			 BeginPaint( hWnd, &ps );
#if 0
			 GetClientRect( hWnd, &rect );
			 PlayEnhMetaFile( ps.hdc, vView[iWnd].hMetaFile, &rect );
#else
			 vView[iWnd].OnPaint(hWnd, &ps);
#endif
			 EndPaint( hWnd, &ps );
		
		}	 
		break;
#endif
	case WM_CREATE :
		{
WriteRaporto("cld WM_CREATE \n");
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			MDICREATESTRUCT *pmcs = (MDICREATESTRUCTA *)pcs->lpCreateParams;
			iWnd = int(pmcs->lParam);
			SetWindowWord(hWnd, 0, WORD(iWnd) );
			

			ShowScrollBar( hWnd, SB_HORZ, FALSE );
			SetScrollRange( hWnd, SB_HORZ, 0, 0, FALSE );
			SetScrollPos( hWnd, SB_HORZ, 0, TRUE );

			ShowScrollBar( hWnd, SB_VERT, FALSE );
			SetScrollRange( hWnd, SB_VERT, 0, 10, FALSE );
			SetScrollPos( hWnd, SB_VERT, 0, TRUE );

#ifdef DRAW_TO_META_FILE
			vView[iWnd].DrawToMetaFile(hWnd);
#else

#ifdef DRAW_TO_WINDOW
			vView[iWnd].DrawToWindow(hWnd, false);
#else
#ifdef DRAW_WITH_MEM_TO_WINDOW
			vView[iWnd].DrawWithMemToWindow(hWnd);
#endif
#endif
#endif


WriteRaporto("cld WM_CREATE end\n");
		}
		break;
	case WM_VSCROLL :
		{
			vView[iWnd].VScroll( hWnd, LOWORD( wParam ) );
		}
		break;
	case WM_HSCROLL :
		{
			vView[iWnd].HScroll( hWnd, LOWORD( wParam ) );
		}
		break;		
	case WM_SIZE :
		{
WriteRaporto("cld WM_SIZE\n");
			if(vView[iWnd].OnSize(hWnd))
			{
#ifdef DRAW_WITH_MEM_TO_WINDOW
				vView[iWnd].DrawWithMemToWindow(hWnd);
#endif
			}
WriteRaporto("cld WM_SIZE end\n");
			return( DefMDIChildProc( hWnd, uMsg, wParam, lParam ) );
		}
		break;
	case WM_COMMAND :
		{
			switch( LOWORD( wParam ) )
			{
			case ID_SAVE_GRAPH_AS_METAFILE:
				{
					vView[iWnd].DrawToMetaFile2(hWnd);

					char sTitle[255];
					if (vDoc[iWnd].m_sTitle[0] == '\"')
					{
						strcpy(sTitle, vDoc[iWnd].m_sTitle + 1);
					}
					else
					{
						strcpy(sTitle, vDoc[iWnd].m_sTitle);
					}
					if (sTitle[strlen(sTitle)-1] == '\"')
						sTitle[strlen(sTitle)-1] = '\0';
					 
					SavePlot( hWnd, vView[iWnd].hMetaFile, sTitle );

					DeleteEnhMetaFile(vView[iWnd].hMetaFile);
				}
				break;
				
			case ID_VIEW_FULL_ZOOM :
				{
					vView[iWnd].SetFullZoom(hWnd);
				}
				break;
							

			default :
				return( DefMDIChildProc( hWnd, uMsg, wParam, lParam ) );
			}
			break;
		}
	case WM_CLOSE :
		{
			if (iWnd < 3)
				SendMessage(hMainWnd, WM_COMMAND, ID_FILE_CLOSE, 0);
			if (2 < iWnd && iWnd < 6)
				SendMessage(hMainWnd, WM_COMMAND, ID_FILE_CLOSE_COV, 0);
			if (5 < iWnd && iWnd < 9)
				SendMessage(hMainWnd, WM_COMMAND, ID_FILE_CLOSE_AUTOCOV, 0);
		}
		break;

	case WM_DESTROY :
		{

		}
		break;
	default :
		return( DefMDIChildProc( hWnd, uMsg, wParam, lParam ) );
	}
	return( 0L );
}


