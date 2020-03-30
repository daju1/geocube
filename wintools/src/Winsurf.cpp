#include <afxdisp.h>         // MFC core and standard components
#include "../../excel_connect/src/myexcel.h"
#include "../../acad_connect/myacad.h"
#include "../../surfer_connect/mysurfer.h"

#include <winspool.h>         // MFC core and standard components





#include "StdAfx.h"
#include "winsurf.h"
#include "..\..\surfdoc\src\SurfDoc.h"
//#include "raporto.h"
#include "..\..\array\src\sorting.h"
#include "..\..\tools\src\readfile.h"
#include "..\..\surfdoc\src\colormap.h"
#include "..\..\surfdoc\src\DrawScene.h"
#include "GLPrintMan.h"
#include "win32_app.h"
#include "utility.h"
#include "winsurfproc.h"
#include "win32_graphics_view.h"
#include "listfun.h"
#include "..\..\surfdoc\src\grid.h"
#include "..\..\array\src\interp.h"
#include "..\..\array\src\ap.h"
#include "..\..\array\src\fft.h"
#include "..\..\array\src\matrixes.h"
#include "..\..\tools\src\errorexit.h"
#include "..\..\tools\src\filedlg.h"
#include "..\..\tools\src\readfile.h"
#include ".\commandlineparser.h"
#include "checkListBox.h"
#include "..\..\tools\src\listviewtab.h"

#include "..\..\surfdoc\src\whatselected.h"
#include "..\..\surfdoc\src\distance3d.h"
#include "..\..\surfdoc\src\Well_3d.h"
#include "..\..\surfdoc\src\srf.h"

#include "..\..\laboratory\src\LabTrialsTree.h"
#include "..\..\laboratory\src\LabParamTree.h"


#if DFX_LAYER_FROM_OBJECT


#include <dime/Input.h>
#include <dime/Output.h>
#include <dime/Model.h>
#include <dime/State.h>
#include <dime/convert/convert.h>

#endif

#define FOR_DIMA 0


 

 


extern CGLPrintMan print;
extern LOGFONT lf_Label;        // logical font structure

extern int UseGLFont( HDC hDC,  IN CONST LOGFONTA * plf_Label);



char * SelectNameFromPath(const char * path, char * name, size_t len);







extern HINSTANCE hInst;   // ������� ���������
//extern LPCTSTR lpszAppName;
LPCTSTR lpszSurfTitle   = "Geo Cube 01";
LPCTSTR lpszWinSurfParent   = "WINSURF Cube 01";
LPCTSTR lpszWinSurf   = "win surf cube";
LPCTSTR lpszWinSurfName   = "MyWINSurf";
extern char directory[];
extern char szPath[];
extern void sortrows21(vdouble& x, vdouble& y, vdouble& z);

LRESULT CALLBACK DlgProcPrintSurfParam( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
extern int Geo2xyz(double B, double L, double& x, double& y, double& z);

extern BOOL bAbortPrinting;
extern HWND hAbortPrintingDlg;
extern LRESULT CALLBACK DlgProcAbortPrinting( HWND hWnd, UINT message,
                           WPARAM wParam, LPARAM lParam );
extern int CALLBACK AbortPrinting( HDC hdcPrinter, int Code );
extern void InitSphere(int nlist, int alpha);


#ifdef USE_EARTHQUAKES_ON_SURF
#include "GraphsDoc.h"
#include "GraphsView.h"
//#include "XYZBuffer.h"
extern Vector<CGraphsDoc> vDoc;
extern Vector<CGraphsView> vView;
#endif /*USE_EARTHQUAKES_ON_SURF*/

extern HWND CreateATreeView(HWND hwndParent, SurfDoc* pSurfDoc);
extern void Main_OnBeginDrag(HWND hwndTV, LPNMTREEVIEW lpnmtv);
extern void Main_OnMouseMove(HWND hwndParent, HWND hwndTV, LONG xCur, LONG yCur);
extern void Main_OnLButtonUp(void);
extern double Median(double *p, int n); 

#include "../../winplot/src/winplot.h"

#define RGBA(r,g,b,a)   ( (((DWORD)(BYTE)(a))<<24) | RGB(r,g,b))

typedef struct
{
	HWND hWnd;
	bool bPrinterNameFound;
	short dmCopies;
	short dmOrientation;
	short dmPaperSize;
	char  szPrinterName[32];
} PRINTSURFDLGDATA, *LPPRINTSURFDLGDATA;




int BeginWinSurf(WNDCLASSEX &wc)
{
	// ����������� ������ �������� ���� ����������.
	//............................................
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WinSurfParentProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = sizeof(LONG);
	wc.hInstance     = hInst;
	wc.hIcon         = LoadIcon( hInst, lpszWinSurfName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
#if VIEW_ONLY_VERSION
	wc.lpszMenuName  = "MYWINSURF_VIEW_ONLY";
#else
	wc.lpszMenuName  = "MYWINSURF";
#endif
	wc.lpszClassName = lpszWinSurfParent;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = (HICON__ *) LoadImage( hInst, lpszWinSurfName,
								 IMAGE_ICON, 16, 16,
								 LR_DEFAULTCOLOR );


	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// ����� ��� ����������
		{
			MessageBox(0,"!RegisterClassEx","WinSurf",0);
			return( FALSE );
		}
		else
		{
//			MessageBox(0,"����� ��� ����������","WinSurf",0);
		}
	}
	return (TRUE);
}


HWND CreateWinSurfWnd( void * pDoc )
{
#if FOR_DIMA
	HWND hDesktopWindow = GetDesktopWindow();
	RECT rcDesktopWindow;
	GetWindowRect(hDesktopWindow, &rcDesktopWindow);
#endif
	HWND hSurfWnd = NULL;

#if FOR_DIMA
	hSurfWnd = CreateWindow( lpszWinSurfParent,
                    	lpszSurfTitle,
						WS_OVERLAPPED     | 
						WS_CAPTION        | 
						WS_SYSMENU        | 
						WS_THICKFRAME     | 
						WS_MINIMIZEBOX    | 
						//WS_MAXIMIZEBOX	  |
						WS_MAXIMIZE,
						rcDesktopWindow.left, rcDesktopWindow.top,
						rcDesktopWindow.right, rcDesktopWindow.bottom,
                    	NULL,
                    	NULL,
                    	hInst,
                    	(void *)pDoc
                    	);
#else
	hSurfWnd = CreateWindow( lpszWinSurfParent,
                    	lpszSurfTitle,
						WS_OVERLAPPEDWINDOW,
                    	CW_USEDEFAULT, 0,
                    	CW_USEDEFAULT, 0,
                    	NULL,
                    	NULL,
                    	hInst,
                    	(void *)pDoc
                    	);
#endif
   if ( !hSurfWnd )
   {
	   ErrorExit("CreateWindow");
	   MessageBox(0,"!hSurfWnd","WinSurf",0);
	   return( NULL );
   }
	
   ShowWindow( hSurfWnd, /*nCmdShow*/1 );
   UpdateWindow( hSurfWnd );
//   printf("CreateWinSurf(end)\n\n");
   return hSurfWnd;

}

WPARAM StartWinSurfLoop()
{
	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	} 
	return( msg.wParam );
}

WPARAM StartWinSurf(HWND &hSurfWnd, void * pDoc)
{
	hSurfWnd = CreateWinSurfWnd(pDoc);
	return StartWinSurfLoop();
}

WPARAM WinSurf(Vector<int>& lines_break_indexes, vdouble& x, vdouble& y, vdouble& z)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(lines_break_indexes, x, y, z);
	return StartWinSurfLoop();
}
WPARAM WinSurf(vector<int>& lines_break_indexes, vector<double>& x, vector<double>& y, vector<double>& z)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(lines_break_indexes, x, y, z);
	return StartWinSurfLoop();
}
WPARAM WinSurf(vector<cut_of_line>& line_cutting_vector, 
			vector<double>& x, vector<double>& y, vector<double>& z)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(line_cutting_vector, x, y, z);
	return StartWinSurfLoop();
}
WPARAM WinSurf(vector<cut_of_line>& line_cutting_vector, 
			int ix, int iy,
			vector<vector<double> >& data)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(line_cutting_vector, ix, iy, data);
	return StartWinSurfLoop();
}
WPARAM WinSurf()
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	// new win_app() here 
	// -> 	SetNewProject(); 
	// -> new win_project(* win_class_factory::GetInstance());
	// -> new win_class_factory() : graphics_class_factory()
	// 

	// win_project()
	// -> CreateProjectView() -> new win_project_view(prj2) -> LightAdded(); ObjectAdded();

	// win_project()
	// -> AddGraphicsView(NULL, false);

	// project::AddGraphicsView()
	// -> win_class_factory::ProduceGraphicsView() 
	// -> new win_graphics_view(prj2, cam);
	// -> BeginWinGhemical(); view_widget = CreateWinGhemical(this); SendMessage(view_widget, WM_COMMAND, ID_FILE_INITOG2, 0); ConfigureHandler(view_widget);
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	
//	app->work(argc, argv);	
	// ������ ���������� ������ � �������
	CommandLineParser parser;
	parser.DoParsing();
	if (strlen(parser.open_file) > 0)
	{
		// GetExtension from parser.open_file
		char * p = strrchr(parser.open_file,'.');
		if (p)
		{			
			if (strcmp(p, ".cub") == 0)
			{
				app->GetWinProject()->OpenCubeFile(parser.open_file, FILE_NAME_LEN, NULL/*parser.open_file*/);
			}
			else //if (strcmp(p, ".gsf") == 0)
				app->GetWinProject()->OpenFile(parser.open_file, FILE_NAME_LEN, NULL/*parser.open_file*/, false);
		}
		else
			app->GetWinProject()->OpenFile(parser.open_file, FILE_NAME_LEN, NULL/*parser.open_file*/, false);

	}

	return StartWinSurfLoop();

}

WPARAM WinSurf(HWND &hSurfWnd, vdouble& x, vdouble& y, vdouble& z, int type)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(x, y, z, type);
	hSurfWnd = app->GetWinProject()->hSurfWnd;
	return StartWinSurfLoop();
}

WPARAM WinSurf(HWND &hSurfWnd, vector<double>& x, vector<double>& y, vector<double>& z, int type)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(x, y, z, type);
	hSurfWnd = app->GetWinProject()->hSurfWnd;
	return StartWinSurfLoop();
}

WPARAM WinSurf( vdouble& x, vdouble& y, vdouble& z, int type)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
printf("pre InitSurfDoc\n");
	app->GetWinProject()->InitSurfDoc(x, y, z, type);
printf("post InitSurfDoc\n");
	return StartWinSurfLoop();
}
WPARAM WinSurf(Vector<vdouble>& vx, Vector<vdouble>& vy, Vector<vdouble>& vz)
{
	singleton_cleaner<win_app> app_cleaner;
	win_app * app = win_app::GetInstance();  
	app_cleaner.SetInstance(app);

	app->GetWinProject()->SetApp(app);
	app->GetWinProject()->InitSurfDoc(vx, vy, vz);
	return StartWinSurfLoop();
}

typedef double real;
#define NDIM            3
#define FLEX_CHAIN      1
#define LINK_MATR		1
#define  GRID_MEMBRANA	0
int blockSize = 1;
long mols_filelength = 0;
real timeNow;
int stepCount;
int nAtom;
#ifdef FLEX_CHAIN      
int nChain;
int chainLen;
#endif /*FLEX_CHAIN*/

real region[4];
real **r, **rv;
#if GRID_MEMBRANA
  int nGridAtom, nPolyAtom;
#endif /*GRID_MEMBRANA*/

#if LINK_MATR
	int **links, nlinks=0;
#endif /*LINK_MATR*/

int blockNum;
  short *AllocVecS (int size) {
#if 1
    short *v;
    v = (short *)  HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, size * sizeof (short));
    return (v - 1);
#else
    short *v;
    v = (short *) malloc (size * sizeof (short));
    return (v - 1);
#endif
  }
  real **AllocMatR (int size1, int size2) {
#if 1
    real **v;
    int k;
	v = (real **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		size1 * sizeof( real * ) );
    v[0] = (real *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		size1 * size2 * sizeof (real)) - 1;
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v - 1);	
#else
    real **v;
    int k;
    v = (real **) malloc (size1 * sizeof (real *));
    v[0] = (real *) malloc (size1 * size2 * sizeof (real)) - 1;
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v - 1);	
#endif
  }
 void FreeVecS (short *v) {
#if 1
	HeapFree( GetProcessHeap(), 0, v + 1);
#else
    free (v + 1);
#endif
  }
  int **AllocMatI (int size1, int size2) {
#if 1
    int **v, k;
    v = (int **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, size1 * sizeof (int *));
    v[0] = (int *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, size1 * size2 * sizeof (int)) - 1;
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v - 1);
#else
    int **v, k;
    v = (int **) malloc (size1 * sizeof (int *));
    v[0] = (int *) malloc (size1 * size2 * sizeof (int)) - 1;
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v - 1);
#endif
  }

  int GetConfig () {
    int fOk, k, n, fd;
    short *rI;
    fOk = 1;
	FILE *fp;
	if (! (fp = fopen (szPath, "rb"))) fOk = 0;

    if (blockNum == -1) 
	{
    } 
	else 
	{
      fseek (fp, blockNum * blockSize, 0);
      blockNum = blockNum + 1;
    }
    if (fOk) {
		fd = _fileno(fp);
		mols_filelength = _filelength(fd);

      fread (&blockSize, sizeof (int), 1, fp);
      if (feof (fp)) return (0);
      fread (&timeNow, sizeof (real), 1, fp);
      fread (&stepCount, sizeof (int), 1, fp);
      fread (&region[1], sizeof (real), NDIM, fp);
      fread (&nAtom, sizeof (int), 1, fp);
#if GRID_MEMBRANA
      fread (&nGridAtom, sizeof (int), 1, fp);
      fread (&nPolyAtom, sizeof (int), 1, fp);
#endif /*GRID_MEMBRANA*/
#if FLEX_CHAIN || CONSTR_CHAIN
#if LINK_MATR
      fread (&nlinks, sizeof (int), 1, fp);
#else
      fread  (&nChain, sizeof (int), 1, fp);
      fread (&chainLen, sizeof (int), 1, fp);
#endif /*LINK_MATR*/
#endif /*FLEX_CHAIN*/
/*	  char str[1024];
	  sprintf(str, "blockSize = %d timeNow = %lf stepCount=%d region = %lf %lf %lf nAtom = %d nlinks = %d",
		  blockSize,timeNow, stepCount, region[1], region[2], region[3], nAtom, nlinks);
	  MessageBox(0,str, "", 0);
*/
      if (blockNum == -1) 
	  {
		  r  = AllocMatR (NDIM, nAtom);
#if LINK_MATR
		  links = AllocMatI (nlinks, 2);
#endif /*LINK_MATR*/
		  blockNum = 1;
      }
#if LINK_MATR
    for (n = 1; n <= nlinks; n ++) 
	{
        fread (&links[n][1], sizeof (int), 2, fp);
	}
#endif /*LINK_MATR*/

      rI = AllocVecS (nAtom);
      for (k = 1; k <= NDIM; k ++) {
        fread (&rI[1], sizeof (short), nAtom, fp);
        for (n = 1; n <= nAtom; n ++)
           r[k][n] = (rI[n] / 32767. - 0.5) * region[k];
      }
      FreeVecS (rI);
      if (ferror (fp)) fOk = 0;
	  fclose(fp);
    }
    if (! fOk) ErrorExit ("read config data");
    return (1);
  }
  




/*inline double Rand(double x)
{
	//====== ��������� ����� � ��������� (-x, x)
	return x - (x + x) * rand() / RAND_MAX;
}*/
			
typedef struct
{
	SurfDoc* pSurfDoc;
	HWND hWnd;
}	SURFPROPDLGDATA, *LPSURFPROPDLGDATA;


int GetSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
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




int ChooseSurfColor(HWND hwndOwner, COLORREF& color)
{
	static COLORREF acrCustClr[16]; // array of custom colors 
	static DWORD rgbCurrent;        // initial color selection
	CHOOSECOLOR cc;                 // common dialog box structure 
	HBRUSH hbrush;                  // brush handle

	rgbCurrent = color;

	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwndOwner;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc)==TRUE) {
		hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult; 
	}
	else
		return -1;
	color = rgbCurrent;
	return 0;

}

typedef struct
{
//	double zoomCoefZ_XY;
//	bool		m_bEqialZoom;		// ����� ���������� ���������
//	bool		m_bQuad;			// ���� ������������� GL_QUAD
//	GLenum		m_FillMode;		// ����� ���������� ���������
	HWND		hWnd;
	SurfDoc*	pSurfDoc;

}	
SURFCUTSPLANEDLGDATA, *LPSURFCUTSPLANEDLGDATA;
int GetCutsPlaneSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_SLIDER_CUT_PLANE:
		nID = IDC_EDIT_SURF_CUTS_PLANE_D;
		return 0;
	}
	return 0;
}
LRESULT CALLBACK DlgProcSurfCutsPlane( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFCUTSPLANEDLGDATA lpSurfCutsPlaneDlgMem;
	static double m_Pos[11]; 			// ������ ������� ���������
	static unsigned int lastCommand;
	static double min_Dd, max_Dd;
	static double min_Dv, max_Dv;
	

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfCutsPlaneDlgMem = (LPSURFCUTSPLANEDLGDATA)lParam;
			CheckDlgButton(hDlg, IDC_CHECK_FAST_CUTS_PLANE, 
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting);

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_ONE_PLANE_CUTTING_CONTROLS,0);
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_THREE_PLANES_CUTTING_CONTROLS,0);

			SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,0);
			SendMessage(hDlg,WM_COMMAND,INIT_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE,0);
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_CUTS_SLIDER,0);

			SendMessage(hDlg,WM_COMMAND,IDC_ENABLE_ONE_PLANE_CLIPPING_BUTTONS,
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting ? 0 : 1);

			lastCommand = IDC_BUTTON_SURF_CUTS_PLANE;
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetCutsPlaneSliderNum(hwnd, nID);
				double delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
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
					m_Pos[num] = newPos<0 ? 0 : newPos>20000.0 ? 20000.0 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}


				//*****************************************************
				GLdouble * cut_plane;
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v;
				}
				else
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d;
				}
				//*****************************************************
				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				double mu = m_Pos[num]/20000.0;
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v[3] = m_Pos[num]*(max_Dv - min_Dv)/20000.0 + min_Dv;
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d[3] = m_Pos[num]*(max_Dd - min_Dd)/20000.0 + min_Dd;

				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%lf",cut_plane[3]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);
				//====== �������������� ��� � ������ ���������
#if 0
				SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,1);
				SendMessage(hDlg,WM_COMMAND,lastCommand,0);
#else
				SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,0);
#endif				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_ENABLE_ONE_PLANE_CLIPPING_BUTTONS:
			{
				//EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE_SAVE), lParam == 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE), lParam == 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE), lParam == 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE2), lParam == 1);
				
				ShowWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE), lParam == 1);
				ShowWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE), lParam == 1);
				ShowWindow(GetDlgItem(hDlg, IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE2), lParam == 1);
			}
			break;
		case IDC_CHECK_FAST_CUTS_PLANE:
			{
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting = 
					BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_CHECK_FAST_CUTS_PLANE);
				
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_ONE_PLANE_CUTTING_CONTROLS,0);
				SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_DRAW_SURF_CUTS_PLANE,1);
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_CUTS_SLIDER,0);

				SendMessage(hDlg,WM_COMMAND,IDC_ENABLE_ONE_PLANE_CLIPPING_BUTTONS,
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting ? 0 : 1);
			}
			break;
		case IDC_INIT_ONE_PLANE_CUTTING_CONTROLS:
			{
				char str[255];
				//*****************************************************
				GLdouble * cut_plane;
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v;
				}
				else
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d;
				}
				//*****************************************************

				sprintf(str,"%f", cut_plane[0]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_A,str);

				sprintf(str,"%f", cut_plane[1]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_B,str);

				sprintf(str,"%f", cut_plane[2]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_C,str);

				sprintf(str,"%f", cut_plane[3]);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);

				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);

				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
					sprintf(str, "interval of d = [%lf %lf]", min_Dv, max_Dv);	
				else
					sprintf(str, "interval of d = [%lf %lf]", min_Dd, max_Dd);

				SetDlgItemText(hDlg, IDC_STATIC_MIN_MAX_D, str);

				//*****************************************************
			}
			break;
		case IDC_INIT_THREE_PLANES_CUTTING_CONTROLS:
			{
				char str[255];
				//*****************************************************
				lpSurfCutsPlaneDlgMem->pSurfDoc->InitXYZCutsPlanes();
				sprintf(str,"%8.3f",lpSurfCutsPlaneDlgMem->pSurfDoc->m_X);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_X,str);
				sprintf(str,"%8.3f",lpSurfCutsPlaneDlgMem->pSurfDoc->m_Y);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_Y,str);
				sprintf(str,"%8.3f",lpSurfCutsPlaneDlgMem->pSurfDoc->m_Z);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_Z,str);				

				sprintf(str, "min = %8.3f", 
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_xd_min);					
				SetDlgItemText(hDlg, IDC_STATIC_MIN_X, str);

				sprintf(str, "max = %8.3f", 
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_xd_max);					
				SetDlgItemText(hDlg, IDC_STATIC_MAX_X, str);

				sprintf(str, "min = %8.3f", 
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_yd_min);					
				SetDlgItemText(hDlg, IDC_STATIC_MIN_Y, str);

				sprintf(str, "max = %8.3f", 
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_yd_max);					
				SetDlgItemText(hDlg, IDC_STATIC_MAX_Y, str);

				sprintf(str, "min = %8.3f", 
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_zd_min);					
				SetDlgItemText(hDlg, IDC_STATIC_MIN_Z, str);

				sprintf(str, "max = %8.3f", 
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_zd_max);					
				SetDlgItemText(hDlg, IDC_STATIC_MAX_Z, str);
				//*****************************************************
			}
			break;
		case IDC_INIT_SURF_CUTS_SLIDER :
			{					
				//*****************************************************
				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);
				//*****************************************************
				GLdouble * cut_plane;
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v;
				}
				else
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d;
				}
				//*****************************************************
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_CUT_PLANE);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 20000)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== ������ �� ���� ������������
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					for (int i=0; i<1; i++)
					{
						//====== ��������� ������������ ������ pPos
						m_Pos[i] = 20000.0*(cut_plane[3] - min_Dv) / (max_Dv - min_Dv);
					}
				}
				else
				{
					for (int i=0; i<1; i++)
					{
						//====== ��������� ������������ ������ pPos
						m_Pos[i] = 20000.0*(cut_plane[3] - min_Dd) / (max_Dd - min_Dd);
					}
				}

				//====== ������ ��������������� ���������
				UINT IDs[] = 
				{
					IDC_SLIDER_CUT_PLANE
				};

				//====== ���� ������� �� ���� �����������
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== �������� Windows-��������� ���� ��������
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== ���������� ��� �������������
					int num = GetCutsPlaneSliderNum(hwnd, nID);

					// ������� ���������� �������� � ��������� m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					if ( i == 0)
					{
						char s[1024];
						//====== ������� ��������� ������ ������� �������
						sprintf (s, "%8.3f", cut_plane[3]);
						//====== �������� ����� � ���� ������ �� ��������
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
				}
			}
			break;
		case IDC_BUTTON_DRAW_SURF_CUTS_PLANE :
			{
				char str[255];
				GLdouble * cut_plane ;
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v;
				}
				else
				{
					cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d;
				}
				
				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_A,str,1022);				
				cut_plane[0] = atof (str);
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d[0] = cut_plane[0];					
				}
				else
				{
                    lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v[0] = cut_plane[0];
				}
				

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_B,str,1022);
				cut_plane[1] = atof (str);
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d[1] = cut_plane[1]*lpSurfCutsPlaneDlgMem->pSurfDoc->m_zoomCoefXY;					
				}
				else
				{
                    lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v[1] = cut_plane[1]/lpSurfCutsPlaneDlgMem->pSurfDoc->m_zoomCoefXY;
				}

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_C,str,1022);
				cut_plane[2] = atof (str);
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d[2] = cut_plane[2]*lpSurfCutsPlaneDlgMem->pSurfDoc->m_zoomCoefXYZ;
				}
				else
				{
                    lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v[2] = cut_plane[2]/lpSurfCutsPlaneDlgMem->pSurfDoc->m_zoomCoefXYZ;
				}

				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str,1022);
				cut_plane[3] = atof (str);

				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(true, min_Dv, max_Dv);
				lpSurfCutsPlaneDlgMem->pSurfDoc->GetMinMaxDPlaneCoef(false, min_Dd, max_Dd);

				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					//cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v;
					double mu = (cut_plane[3] - min_Dv) / (max_Dv - min_Dv);
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d[3] =
						min_Dd + mu * (max_Dd - min_Dd);
				}
				else
				{
					//cut_plane = lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_d;
					double mu = (cut_plane[3] - min_Dd) / (max_Dd - min_Dd);
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_cut_plane_v[3] =
						min_Dv + mu * (max_Dv - min_Dv);
				}
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					if (cut_plane[3] > max_Dv)
					{
						cut_plane[3] = 
							(min_Dv + max_Dv) / 2.0 +
							(max_Dv - min_Dv) * 0.0;
						sprintf(str,"%lf", cut_plane[3]);
						SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);
					}
					if (cut_plane[3] < min_Dv)
					{
						cut_plane[3] = 
							(min_Dv + max_Dv) / 2.0 -
							(max_Dv - min_Dv) * 0.0;
						sprintf(str,"%lf",cut_plane[3]);
						SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);
					}
				}
				else
				{
					if (cut_plane[3] > max_Dd)
					{
						cut_plane[3] = 
							(min_Dd + max_Dd) / 2.0 +
							(max_Dd - min_Dd) * 0.0;
						sprintf(str,"%lf", cut_plane[3]);
						SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);
					}
					if (cut_plane[3] < min_Dd)
					{
						cut_plane[3] = 
							(min_Dd + max_Dd) / 2.0 -
							(max_Dd - min_Dd) * 0.0;
						sprintf(str,"%lf",cut_plane[3]);
						SetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_D,str);
					}
				}
				
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
					sprintf(str, "interval of d = [%lf %lf]", min_Dv, max_Dv);	
				else
					sprintf(str, "interval of d = [%lf %lf]", min_Dd, max_Dd);	
				
				SetDlgItemText(hDlg, IDC_STATIC_MIN_MAX_D, str);


				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bDrawCutPlane = true;
				DrawCutPlane(lpSurfCutsPlaneDlgMem->pSurfDoc);

				if (lParam == 0)
				{
					SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_CUTS_SLIDER,0);
					//====== �������������� ��� � ������ ���������
					RECT rect;
					GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
					InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
				}
			}
			break;
		case IDC_BUTTON_ERASE_SURF_CUTS_PLANE :
			{			
				glDeleteLists(FIRST_HARD_LIST+2,1);
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bDrawCutPlane = false;

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_BUTTON_SURF_CUTS_PLANE_SAVE:
			{
				if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{

					lpSurfCutsPlaneDlgMem->pSurfDoc->ClearCutlinesPolygones();
					lpSurfCutsPlaneDlgMem->pSurfDoc->Cut(false,true);
					lpSurfCutsPlaneDlgMem->pSurfDoc->ZoomViewCutlinesPolygones();
					lpSurfCutsPlaneDlgMem->pSurfDoc->DrawCutPlaneLines();
					//====== �������������� ��� � ������ ���������
					RECT rect;
					GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
					InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
				}
				lpSurfCutsPlaneDlgMem->pSurfDoc->CutSave(false,true);
			}
			break;
		case IDC_BUTTON_SURF_CUTS_PLANE:
			{
//				GLdouble * cut_plane ;
				/*if (lpSurfCutsPlaneDlgMem->pSurfDoc->m_bFastCutting)
				{
					//====== �������������� ��� � ������ ���������
					RECT rect;
					GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
					InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
				}
				else*/
				{
					lpSurfCutsPlaneDlgMem->pSurfDoc->ClearCutlinesPolygones();
					lpSurfCutsPlaneDlgMem->pSurfDoc->Cut(false,true);
					lpSurfCutsPlaneDlgMem->pSurfDoc->ZoomViewCutlinesPolygones();
					lpSurfCutsPlaneDlgMem->pSurfDoc->DrawCutPlaneLines();
					//====== �������������� ��� � ������ ���������
					RECT rect;
					GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
					InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
				}
		
				lastCommand = IDC_BUTTON_SURF_CUTS_PLANE;

			}
			break;
		case IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE:
			{
				lpSurfCutsPlaneDlgMem->pSurfDoc->ClearCutlinesPolygones();
				lpSurfCutsPlaneDlgMem->pSurfDoc->Cut(true, true);
				lpSurfCutsPlaneDlgMem->pSurfDoc->ZoomViewCutlinesPolygones();
				lpSurfCutsPlaneDlgMem->pSurfDoc->CutAndDisvisible(true);

			
				lastCommand = IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE;
				
				lpSurfCutsPlaneDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
			}
			break;
			
		case IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE2:
			{
				lpSurfCutsPlaneDlgMem->pSurfDoc->ClearCutlinesPolygones();
				lpSurfCutsPlaneDlgMem->pSurfDoc->Cut(true, false);
				lpSurfCutsPlaneDlgMem->pSurfDoc->ZoomViewCutlinesPolygones();
				lpSurfCutsPlaneDlgMem->pSurfDoc->CutAndDisvisible(false);

				
				lpSurfCutsPlaneDlgMem->pSurfDoc->Draw();

				lastCommand = IDC_BUTTON_SURF_CUTS_PLANE_UNVISIBLE2;

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_BUTTON_DRAW_SURF_CUTS_XYZ_PLANES:
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_X,str,1022);
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_X = atof (str);
				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_Y,str,1022);
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_Y = atof (str);
				GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_Z,str,1022);
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_Z = atof (str);

				//lpSurfCutsPlaneDlgMem->pSurfDoc->ZoomView();

				
				//glDeleteLists(FIRST_HARD_LIST+1,N_HARD_LISTS +(GLsizei) lpSurfCutsPlaneDlgMem->pSurfDoc->m_nglLists);
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bDrawXYZCutPlanes = true;
				DrawXYZCutPlanes(lpSurfCutsPlaneDlgMem->pSurfDoc);

				//DrawScene(lpSurfCutsPlaneDlgMem->pSurfDoc, lpSurfCutsPlaneDlgMem->m_bQuad, lpSurfCutsPlaneDlgMem->m_FillMode);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_BUTTON_ERASE_SURF_CUTS_XYZ_PLANES:
			{
				glDeleteLists(FIRST_HARD_LIST+3,1);
				lpSurfCutsPlaneDlgMem->pSurfDoc->m_bDrawXYZCutPlanes = false;

				RECT rect;
				GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE:
			{
				LRESULT q = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE, CB_GETCURSEL,0,(LPARAM)0 );
				char str[1023];
				if(q > 0)
				{
					GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_X,str,1022);
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_X = atof (str);
					GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_Y,str,1022);
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_Y = atof (str);
					GetDlgItemText(hDlg, IDC_EDIT_SURF_CUTS_PLANE_Z,str,1022);
					lpSurfCutsPlaneDlgMem->pSurfDoc->m_Z = atof (str);

					lpSurfCutsPlaneDlgMem->pSurfDoc->ZoomView();
					lpSurfCutsPlaneDlgMem->pSurfDoc->CutXYZandDisvisible(q);					
					lpSurfCutsPlaneDlgMem->pSurfDoc->Draw();

					//====== �������������� ��� � ������ ���������
					RECT rect;
					GetClientRect(lpSurfCutsPlaneDlgMem->hWnd,&rect);
					InvalidateRect(lpSurfCutsPlaneDlgMem->hWnd,&rect, true);
					SendMessage(hDlg,WM_COMMAND,INIT_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE,0);
				}
			}
			break;
		case INIT_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE:
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)"Select subcube number");
				for (int q = 1; q <= 8; q++)
				{
					char qstr[32];
					sprintf(qstr,"disvisible %d-st subcube\0",q);
					SendDlgItemMessage( hDlg, IDC_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)qstr);
				}
				
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_CUTS_XYZ_PLANES_UNVISIBLE, CB_SETCURSEL, 0, 0);
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


 

LRESULT CALLBACK DlgProcSurfPalette( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
    TCHAR tchBuffer[BUFFER]; 
    static HWND hListBox; 
    TEXTMETRIC tm; 
    int y; 
    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 
	LONG itemdata;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_INVERSE_COLORMAP,
				lpSurfDlgMem->pSurfDoc->m_bInverseColormap ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_LOCAL_COLORMAP,
				lpSurfDlgMem->pSurfDoc->m_bLocalColormap ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			SendMessage(hDlg,WM_COMMAND,INIT_COMBO_IDC_COMBO_SURF_COLORMAP,0);
            hListBox = GetDlgItem(hDlg, IDC_LIST_SURF_CREATE_PALETTE); 
 
            wpOrigListBoxProc2 = (WNDPROC) SetWindowLongPtr(hListBox, 
                GWLP_WNDPROC, (LONG_PTR) ListBoxPaletteSubclassProc); 

			SendMessage(hDlg, WM_COMMAND, INIT_SURF_PALETTE, 0);
		}
		break;
	case WM_MEASUREITEM:
		{ 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            // Set the height of the List box items. 
            lpmis->itemHeight = YBITMAP2; 
		}
		break;
	case WM_DRAWITEM: 
		{
            lpdis = (LPDRAWITEMSTRUCT) lParam; 
 
            // If there are no List box items, skip this message. 
            if (lpdis->itemID == -1) 
            { 
                break; 
            } 
            // Draw the bitmap and text for the List box item. Draw a 
            // rectangle around the bitmap if it is selected. 
 
            switch (lpdis->itemAction) 
            { 
			case ODA_SELECT:
			case ODA_FOCUS:
            case ODA_DRAWENTIRE: 
				{ 
                    // Display the bitmap associated with the item. 
 
                    itemdata = SendMessage(lpdis->hwndItem, 
                        LB_GETITEMDATA, lpdis->itemID, (LPARAM) 0); 

					HBRUSH brush =  CreateSolidBrush(
					  (COLORREF) itemdata   // brush color value
					);
					FillRect(lpdis->hDC, &lpdis->rcItem, brush);
					DeleteObject(brush);

                    // Display the text associated with the item. 
 
                    SendMessage(lpdis->hwndItem, LB_GETTEXT, 
                        lpdis->itemID, (LPARAM) tchBuffer); 
 
                    GetTextMetrics(lpdis->hDC, &tm); 
 
                    y = (lpdis->rcItem.bottom + lpdis->rcItem.top - 
                        tm.tmHeight) / 2;
						
 
                    TextOut(lpdis->hDC, 
                        2, 
                        y, 
                        tchBuffer, 
                        strlen(tchBuffer)); 						
 
                    // Is the item selected? 
 
                    if (lpdis->itemState & ODS_SELECTED) 
                    { 
                        // Draw a rectangle around bitmap to indicate 
                        // the selection. 
 
                        DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
                    } 
				}
                break; 
 
            } 
		}
		break;
 
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case INIT_SURF_PALETTE:
			{				
				SendMessage(hListBox, LB_RESETCONTENT, 0, 0); 
				// with each List box item. 
				char item_str[255];
				UINT palette_len = lpSurfDlgMem->pSurfDoc->m_palette.GetLen();
				UINT j = 0;
				if (lpSurfDlgMem->pSurfDoc->m_bInverseColormap)
				{
					for (UINT r = palette_len - 1, j = 0; j < palette_len ; r--, j++)
					{
						sprintf(item_str, "%d", j);
						COLORREF itemcolor = lpSurfDlgMem->pSurfDoc->m_palette.GetColor(r);
						AddCheckedPaletteItem(hListBox, 
							item_str, LONG(itemcolor));
					}
				}
				else
				{
					for (UINT r = 0; r < palette_len; r++)
					{
						sprintf(item_str, "%d", r);
						COLORREF itemcolor = lpSurfDlgMem->pSurfDoc->m_palette.GetColor(r);
						AddCheckedPaletteItem(hListBox, 
							item_str, LONG(itemcolor));
					}
				}
				SetFocus(hListBox); 
				SendMessage(hListBox, LB_SETCURSEL, 0, 0); 
			}
			break;
		case IDC_BUTTON_INTERPOLATE:
			{
				LONG itemdata = SendMessage(hListBox, LB_GETITEMDATA, 0, 0);
				lpSurfDlgMem->pSurfDoc->m_palette.InitFirst(COLORREF (itemdata) ); 
				LONG count_of_items = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				itemdata = SendMessage(hListBox, LB_GETITEMDATA, count_of_items - 1, 0);
				lpSurfDlgMem->pSurfDoc->m_palette.InitLast(COLORREF (itemdata) ); 
				lpSurfDlgMem->pSurfDoc->m_palette.Interpolate();
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);	
			}
			break;
		case IDC_BUTTON_SURF_PALETTE_APPLY:
			{
				LONG count_of_items = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				lpSurfDlgMem->pSurfDoc->m_palette.Free();
				lpSurfDlgMem->pSurfDoc->m_palette.Allocate(count_of_items);
				for ( int i = 0; i < count_of_items; i++)
				{
					LONG itemdata = SendMessage(hListBox, LB_GETITEMDATA, i, 0);
					lpSurfDlgMem->pSurfDoc->m_palette.InitItem(i,COLORREF (itemdata) );
				}
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);	
			}
			break;
		case IDC_BUTTON_SURF_PALETTE_PLOT:
			{
				UINT len = lpSurfDlgMem->pSurfDoc->m_palette.GetLen();
				Vector<vdouble> vx(3), vy(3);
				for (int iv = 0; iv < 3; iv++)
				{
					vx[iv].resize(len);
					vy[iv].resize(len);
					for ( UINT i = 0; i < len; i++)
					{
						COLORREF color = lpSurfDlgMem->pSurfDoc->m_palette.GetColor(i);
						vx[iv][i] = i;
						switch (iv)
						{
						case 0:
							vy[iv][i] = GetRValue(color);
							break;
						case 1:
							vy[iv][i] = GetGValue(color);
							break;
						case 2:
							vy[iv][i] = GetBValue(color);
							break;
						}
					}
				}
				WinPlot(vx,vy);
			}
			break;
		case IDC_BUTTON_SURF_PALETTE_EXTRACT:
			{
				if (lpSurfDlgMem->pSurfDoc->m_palette.GetLen() < 2048)
				{
					lpSurfDlgMem->pSurfDoc->m_palette.Extract(2);
					SendMessage(hDlg, WM_COMMAND, IDOK, 1);
					char str[255];
					sprintf(str, "palette length = %d", lpSurfDlgMem->pSurfDoc->m_palette.GetLen());
					SetDlgItemText(hDlg,IDC_STATIC_SURF_PALETTE_LEN, str);
				}
			}
			break;
		case IDC_CHECK_SURF_LOCAL_COLORMAP:
			{
				lpSurfDlgMem->pSurfDoc->m_bLocalColormap = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_LOCAL_COLORMAP) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);
			}
			break;
		case IDC_CHECK_SURF_INVERSE_COLORMAP:
			{
				lpSurfDlgMem->pSurfDoc->m_bInverseColormap = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_INVERSE_COLORMAP) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDOK, 1);
			}
			break;
		case IDC_COMBO_SURF_COLORMAP:
			{
				int nColormap = 
					SendDlgItemMessage( hDlg, IDC_COMBO_SURF_COLORMAP, 
					CB_GETCURSEL,0,(LPARAM)0 );
				if (nColormap >= 0 && nColormap < 21)
				{
					lpSurfDlgMem->pSurfDoc->m_nColormap = UINT(nColormap);

					char str[255];
					sprintf(str, "%u", lpSurfDlgMem->pSurfDoc->m_nColormap);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_N_COLORMAP, str);

					//SendMessage(hDlg, WM_COMMAND, IDOK, 0);					
				}
			}
			break;
		case INIT_COMBO_IDC_COMBO_SURF_COLORMAP:
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_COLORMAP, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				for (int i = 0; i < 21; i++)
				{					
					SendDlgItemMessage( hDlg, 
						IDC_COMBO_SURF_COLORMAP, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)colormap_strings[i]);
				}
				
				SendDlgItemMessage( hDlg, 
					IDC_COMBO_SURF_COLORMAP, CB_SETCURSEL, 0, lpSurfDlgMem->pSurfDoc->m_nColormap);
			}
			break;
		case IDOK:
			{
				if (lParam != 1)
					//lpSurfDlgMem->pSurfDoc->InitPalette();
					APalette::InitPalette(&lpSurfDlgMem->pSurfDoc->m_palette, lpSurfDlgMem->pSurfDoc->m_nColormap);
				SendMessage(hDlg, WM_COMMAND, INIT_SURF_PALETTE, 0);
				lpSurfDlgMem->pSurfDoc->ZoomView();
				
				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

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



typedef struct
{
//	double zoomCoef_XY;
//	double zoomCoefZ_XY;
//	bool		m_bQuad;			// ���� ������������� GL_QUAD
//	bool		m_bEqialZoomXYZ;		
//	bool		m_bEqialZoomXY;		
//	bool		m_bEqialZoom;		
//	GLenum		m_FillMode;		// ����� ���������� ���������
	HWND		hWnd;
	SurfDoc*	pSurfDoc;

}	
SURFZOOMDLGDATA, *LPSURFZOOMDLGDATA;

LRESULT CALLBACK DlgProcSurfZoom( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_ZOOM_EQUIAL_XYZ,
				lpSurfDlgMem->pSurfDoc->m_bEqialZoomXYZ ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_SURF_ZOOM_EQUIAL_XY,
				lpSurfDlgMem->pSurfDoc->m_bEqialZoomXY ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			SendMessage(hDlg, WM_COMMAND, IDC_INIT_ZOOM_DIALOG, 0);

			
			char str[1023];
			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_zoomCoefXYZ);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ZOOM_XYZ,str);
			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_zoomCoefXY);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ZOOM_XY,str);
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_ZOOM_DIALOG:
			{

				if (lpSurfDlgMem->pSurfDoc->m_bEqialZoomXY)
				{
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					HWND h = GetDlgItem(hDlg, IDC_STATIC_SURF_ZOOM_XY); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_EDIT_SURF_ZOOM_XY); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				else
				{
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					HWND h = GetDlgItem(hDlg, IDC_STATIC_SURF_ZOOM_XY); 
					EnableWindow(h, TRUE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_EDIT_SURF_ZOOM_XY);
					EnableWindow(h, TRUE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				
				
				if (lpSurfDlgMem->pSurfDoc->m_bEqialZoomXYZ)
				{
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					HWND h = GetDlgItem(hDlg, IDC_STATIC_SURF_ZOOM_XYZ); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_EDIT_SURF_ZOOM_XYZ); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_CHECK_SURF_ZOOM_EQUIAL_XY); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_STATIC_SURF_ZOOM_XY); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_EDIT_SURF_ZOOM_XY); 
					EnableWindow(h, FALSE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}
				else
				{
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					HWND h = GetDlgItem(hDlg, IDC_STATIC_SURF_ZOOM_XYZ); 
					EnableWindow(h, TRUE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_EDIT_SURF_ZOOM_XYZ);
					EnableWindow(h, TRUE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					h = GetDlgItem(hDlg, IDC_CHECK_SURF_ZOOM_EQUIAL_XY);
					EnableWindow(h, TRUE);
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				}


			}
			break;
		case IDC_CHECK_SURF_ZOOM_EQUIAL_XYZ:
			{
				lpSurfDlgMem->pSurfDoc->m_bEqialZoomXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_ZOOM_EQUIAL_XYZ) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDC_INIT_ZOOM_DIALOG, 0);
				//SendMessage(hDlg, WM_COMMAND, IDOK, 0);
			}
			break;
		case IDC_CHECK_SURF_ZOOM_EQUIAL_XY:
			{
				lpSurfDlgMem->pSurfDoc->m_bEqialZoomXY = IsDlgButtonChecked( hDlg, IDC_CHECK_SURF_ZOOM_EQUIAL_XY) == BST_CHECKED;
				SendMessage(hDlg, WM_COMMAND, IDC_INIT_ZOOM_DIALOG, 0);
				//SendMessage(hDlg, WM_COMMAND, IDOK, 0);
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_ZOOM_XYZ,str,1022);
				double zoomCoefXYZ = atof (str);
				if (zoomCoefXYZ > 0.0)
					lpSurfDlgMem->pSurfDoc->m_zoomCoefXYZ = zoomCoefXYZ;
				else
					MessageBox(0, "Enter a valid value of zoomCoefZ_XY", "Zoom dialog", 0);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_ZOOM_XY,str,1022);
				double zoomCoefXY = atof (str);
				if (zoomCoefXY > 0.0)
					lpSurfDlgMem->pSurfDoc->m_zoomCoefXY = zoomCoefXY;
				else
					MessageBox(0, "Enter a valid value of zoomCoefXY", "Zoom dialog", 0);

				lpSurfDlgMem->pSurfDoc->SaveZoomToDB();

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();


				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

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

LRESULT CALLBACK DlgProcAbout( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{

		case IDOK :
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


LRESULT CALLBACK DlgProcSurfImportProfile( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
//#if FAST_GRID_LOADING
//	static Grid* pGrid;
//#else
	static CGrid* pCGrid;
//#endif
	static vector<double> *pxMap, *pyMap, *pxProfile, *pyProfile, *pxAcadYscale, *pyAcadYscale;
	static int attachMode;
	static int profileType;
	static int inside;

	static bool create_layers;
	static bool new_bln_profile;
	static bool bln_profile_was_started;

	static bool load_acad_yscale;
	static bool acad_yscale_loaded;
	static double z1w, y1a;
	static double z2w, y2a;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
//#if !FAST_GRID_LOADING
			pCGrid		= new CGrid(hDlg);
//#endif
			pxMap		= new vector<double>();
			pyMap		= new vector<double>();
			pxProfile	= new vector<double>();
			pyProfile	= new vector<double>();

			pxAcadYscale = new vector<double>();
			pyAcadYscale = new vector<double>();
			load_acad_yscale = false;
			acad_yscale_loaded = false;
			z1w						= 0.0;
			y1a						= 0.0;
			z2w						= 1.0;
			y2a						= 1.0;
			CheckDlgButton(hDlg, IDC_CHECK_APPLY_YSCALE, load_acad_yscale);


			switch (lpSurfDlgMem->pSurfDoc->mGridProfilesDirection)
			{
			case GRID_POFILE_DIRECTION_NORTH:
				CheckRadioButton( hDlg,					
					IDC_RADIO_PROFILE_GRID_DIRECTION_NORTH,
					IDC_RADIO_PROFILE_GRID_DIRECTION_EAST,
					IDC_RADIO_PROFILE_GRID_DIRECTION_NORTH);
							 
				break;
			case GRID_POFILE_DIRECTION_EAST:
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_GRID_DIRECTION_NORTH,
					IDC_RADIO_PROFILE_GRID_DIRECTION_EAST,
					IDC_RADIO_PROFILE_GRID_DIRECTION_EAST);
				break;
			}
			profileType = 4;
			switch (profileType)
			{
			case 0:
				CheckRadioButton( hDlg,					
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_GRID);
				break;
			case 1:
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BLN);
				break;
			case 2:
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BLN_ON_MAP);
				break;
			case 3:
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BITMAP);
				break;
			case 4:
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_PLAN);
				break;
			case 5:
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D);
				break;
				
			}
			attachMode = 1;
			switch (attachMode)
			{
			case 0:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_ATTACH_MODE_POINT,
						IDC_RADIO_ATTACH_MODE_LINE,
						IDC_RADIO_ATTACH_MODE_POINT);
				}
				break;
			case 1:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_ATTACH_MODE_POINT,
						IDC_RADIO_ATTACH_MODE_LINE,
						IDC_RADIO_ATTACH_MODE_LINE);
				}
				break;
			}
				
			SendMessage(hDlg, WM_USER+1, attachMode, profileType);
			
			create_layers				= false;
			new_bln_profile				= false;
			bln_profile_was_started		= false;
			ShowWindow(GetDlgItem(hDlg, IDC_CHECK_NEW_PROFILE), 0);
			CheckDlgButton( hDlg, IDC_CHECK_NEW_PROFILE,
				new_bln_profile ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_CREATE_LAYERS,
				create_layers ? BST_CHECKED : BST_UNCHECKED );
		}
		break;
	case WM_USER+1:
		{
			//Profile grid direction
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO_PROFILE_GRID_DIRECTION_NORTH), lParam == 0 || (lParam == 1 && wParam == 0));
			EnableWindow(GetDlgItem(hDlg, IDC_RADIO_PROFILE_GRID_DIRECTION_EAST), lParam == 0 || (lParam == 1 && wParam == 0));
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_GRID_COORDINATE), lParam == 0 || (lParam == 1 && wParam == 0) || lParam == 4 );
			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_APPLY_PROFILE_GRID), lParam == 0 || (lParam == 1 && wParam == 0));
			EnableWindow(GetDlgItem(hDlg, IDC_STATIC_PROFILE_GRID_COORDINATE), lParam == 0 || (lParam == 1 && wParam == 0));
			EnableWindow(GetDlgItem(hDlg, IDC_STATIC_PROFILE_GRID_DIRECTION), lParam == 0 || (lParam == 1 && wParam == 0));

			//Profile file name
			EnableWindow(GetDlgItem(hDlg, IDC_STATIC_PROFILE_FILE_NAME), lParam == 0 || lParam == 1  || lParam == 3 || lParam == 4 || lParam == 5 );
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_FILE_NAME), lParam == 0 || lParam == 1  || lParam == 3 || lParam == 4  || lParam == 5 );
			EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_FILE_NAME), lParam == 0 || lParam == 1  || lParam == 3 || lParam == 4  || lParam == 5 );

			// Attach profile to map coordinate
			EnableWindow(GetDlgItem(hDlg, IDC_STATIC_ATTACH_COORDINATES), lParam == 1 || lParam == 2  || lParam == 3 || lParam == 4 || lParam == 5 );
			
			//Attach line ON MAP Golden Software Blanking (*.bln) file name
			EnableWindow(GetDlgItem(hDlg, IDC_STATIC_ATTACH_ON_MAP),						(lParam == 1 && wParam == 1) || lParam == 2 || lParam == 3 || lParam == 4 || lParam == 5 );
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME_ON_MAP),	(lParam == 1 && wParam == 1) || lParam == 2 || lParam == 3 || lParam == 4 || lParam == 5 );
			EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_MAP_ATTACH_FILE_NAME),			(lParam == 1 && wParam == 1) || lParam == 2 || lParam == 3 || lParam == 4 || lParam == 5 );

			//Attach line ON PROFILE Golden Software Blanking (*.bln) file name
			EnableWindow(GetDlgItem(hDlg, IDC_STATIC_ATTACH_LINE_ON_PROFILE),					(lParam == 1 && wParam == 1) || lParam == 3 || lParam == 5 );
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME),   (lParam == 1 && wParam == 1) || lParam == 3 || lParam == 5 );
			EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME),  (lParam == 1 && wParam == 1) || lParam == 3 || lParam == 5 );

			//Acad Y SCALE Golden Software Blanking (*.bln) file name
			bool show_yscale = (lParam == 1 && wParam == 1) || lParam == 2 || lParam == 3 || lParam == 4 || lParam == 5;
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK_APPLY_YSCALE),						show_yscale);
			ShowWindow(GetDlgItem(hDlg, IDC_STATIC_ACAD_YSCALED_BLN),					load_acad_yscale && show_yscale);
			ShowWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME),			load_acad_yscale && show_yscale);
			ShowWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_ACAD_YSCALE_FILE),			load_acad_yscale && show_yscale);
			ShowWindow(GetDlgItem(hDlg, IDC_STATIC_ACAD_YSCALE),						load_acad_yscale && show_yscale);
			

			//attach mode
			ShowWindow(GetDlgItem(hDlg, IDC_STATIC_ATTACH_MODE), lParam == 1);
			ShowWindow(GetDlgItem(hDlg, IDC_RADIO_ATTACH_MODE_POINT), lParam == 1);
			ShowWindow(GetDlgItem(hDlg, IDC_RADIO_ATTACH_MODE_LINE), lParam == 1);

			//new profile
			ShowWindow(GetDlgItem(hDlg, IDC_CHECK_NEW_PROFILE), (lParam == 1 && wParam == 1));
			CheckDlgButton( hDlg, IDC_CHECK_NEW_PROFILE,
				new_bln_profile ? BST_CHECKED : BST_UNCHECKED );
			EnableWindow(GetDlgItem(hDlg, IDC_CHECK_NEW_PROFILE), bln_profile_was_started );

			// Apply
			EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_APPLY_PROFILE_ATTACHING), (lParam == 1 && wParam == 1) || lParam == 2 || lParam == 3 || lParam == 4 || lParam == 5 );
			
			SetDlgItemText(hDlg, IDC_STATIC_ATTACH_ON_MAP2, "");
			SetDlgItemText(hDlg, IDC_STATIC_ATTACH_LINE_ON_PROFILE2, "");
			SetDlgItemText(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME_ON_MAP, "");
			SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME, "");
			SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, "");
			SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME, "");
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_APPLY_YSCALE:
			{
				load_acad_yscale = IsDlgButtonChecked( hDlg, IDC_CHECK_APPLY_YSCALE) == BST_CHECKED;
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_ATTACH_MODE_POINT:
			{
				attachMode = 0;
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_ATTACH_MODE_LINE:
			{
				attachMode = 1;
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_PROFILE_TYPE_GRID:
			{
				profileType = 0;
				CheckRadioButton( hDlg,					
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_GRID);
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_PROFILE_TYPE_BLN:
			{
				profileType = 1;
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BLN);
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_PROFILE_TYPE_BLN_ON_MAP:
			{
				profileType = 2;
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BLN_ON_MAP);
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_PROFILE_TYPE_BITMAP:
			{
				profileType = 3;
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BITMAP);
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;
		case IDC_RADIO_PROFILE_TYPE_PLAN:
			{
				profileType = 4;
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_PLAN);
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;			
		case IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D:
			{
				profileType = 5;
				CheckRadioButton( hDlg,
					IDC_RADIO_PROFILE_TYPE_GRID,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D,
					IDC_RADIO_PROFILE_TYPE_BMPPROFILE3D);
				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;			
		case IDC_RADIO_PROFILE_GRID_DIRECTION_NORTH:
			{
				lpSurfDlgMem->pSurfDoc->mGridProfilesDirection = GRID_POFILE_DIRECTION_NORTH;
			}
			break;
		case IDC_RADIO_PROFILE_GRID_DIRECTION_EAST:
			{
				lpSurfDlgMem->pSurfDoc->mGridProfilesDirection = GRID_POFILE_DIRECTION_EAST;
			}
			break;
		case IDC_BUTTON_APPLY_PROFILE_GRID:
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_PROFILE_GRID_COORDINATE,str,1022);
				double f = atof (str);

				switch(profileType)
				{
				case 0: // grid
					{	
						vdouble xMap,yMap,xProfile;
						xMap.resize(2);
						yMap.resize(2);
						xProfile.resize(2);

						switch (lpSurfDlgMem->pSurfDoc->mGridProfilesDirection)
						{
						case GRID_POFILE_DIRECTION_NORTH:
							{
								xMap[0]		= f;
								xMap[1]		= f;

								yMap[0]		= pCGrid->GetXMin();
								yMap[1]		= pCGrid->GetYMax();

								xProfile[0] = pCGrid->GetXMin();
								xProfile[1] = pCGrid->GetYMax();
							}
							break;
						case GRID_POFILE_DIRECTION_EAST:
							{
								xMap[0]		= pCGrid->GetXMin();
								xMap[1]		= pCGrid->GetYMax();

								yMap[0]		= f;
								yMap[1]		= f;

								xProfile[0] = pCGrid->GetXMin();
								xProfile[1] = pCGrid->GetYMax();
							}
							break;
						}

						lpSurfDlgMem->pSurfDoc->AddGridProfile(pCGrid, xMap, yMap, xProfile);
						lpSurfDlgMem->pSurfDoc->ConvertGridProfilesTo3D();
					}
					break;
				case 1: // bln
					{
						char lpstrFile[1024];
						GetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile, 1023);
						if (lpSurfDlgMem->pSurfDoc->AddNewBlnProfile(
							lpstrFile, 
							lpstrFile, 
							lpSurfDlgMem->pSurfDoc->mGridProfilesDirection, f) == 0)
						{
							lpSurfDlgMem->pSurfDoc->ConvertBlnProfilesTo3D(create_layers);
						}
					}
					break;
				}
		
								
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();

				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

			}
			break;

		case IDC_BUTTON_APPLY_PROFILE_ATTACHING:
			{
				char lpstrFile[1024];
				GetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile, 1023);
				switch(profileType)
				{
				case 0: // grid
					{	
					}
					break;
				case 1: // bln
					{
						z1w						= 0.0;
						y1a						= 0.0;
						z2w						= 1.0;
						y2a						= 1.0;
						if (acad_yscale_loaded)
						{
							z1w = (*pxAcadYscale)[0], y1a = (*pyAcadYscale)[0];
							z2w = (*pxAcadYscale)[1], y2a = (*pyAcadYscale)[1];
							//lpSurfDlgMem->pSurfDoc->SetLastBlnProfileAcadYscale(z1w, y1a, z2w, y2a);							
						}
						if (bln_profile_was_started && !new_bln_profile)
						{
							if (lpSurfDlgMem->pSurfDoc->AddBlnProfile(lpstrFile, lpstrFile, *pxMap, *pyMap, *pxProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a) == 0)
							{
								lpSurfDlgMem->pSurfDoc->ConvertBlnProfilesTo3D(create_layers);
												
								// init of zoomCoefZ_XY
								lpSurfDlgMem->pSurfDoc->ZoomView();

								lpSurfDlgMem->pSurfDoc->Draw();

								//====== �������������� ��� � ������ ���������
								RECT rect;
								GetClientRect(lpSurfDlgMem->hWnd,&rect);
								InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
							}
						}
						else
						{
							if (lpSurfDlgMem->pSurfDoc->AddNewBlnProfile_db(lpstrFile, lpstrFile, NULL, false, *pxMap, *pyMap, *pxProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a) == 0)
							{

								lpSurfDlgMem->pSurfDoc->ConvertBlnProfilesTo3D(create_layers);

												
								// init of zoomCoefZ_XY
								lpSurfDlgMem->pSurfDoc->ZoomView();

								lpSurfDlgMem->pSurfDoc->Draw();

								//====== �������������� ��� � ������ ���������
								RECT rect;
								GetClientRect(lpSurfDlgMem->hWnd,&rect);
								InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
								//**********************************
								bln_profile_was_started = true;
								new_bln_profile = false;
							}
						}

						acad_yscale_loaded = false;
					}
					break;
				case 2: // bln on map
					{
						if (lpSurfDlgMem->pSurfDoc->AddMapBlnProfile(*pxMap, *pyMap, inside) == 0)
						{
							lpSurfDlgMem->pSurfDoc->CutMapBlnProfile();										

							lpSurfDlgMem->pSurfDoc->Draw();

							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(lpSurfDlgMem->hWnd,&rect);
							InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
							
							EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_APPLY_PROFILE_ATTACHING_SAVE), TRUE );
						}
					}
					break;
				case 3: // bitmap
					{
						if (lpSurfDlgMem->pSurfDoc->AddBitmap(lpstrFile, *pxMap, *pyMap, *pyProfile) == 0)
						{
							lpSurfDlgMem->pSurfDoc->ZoomView();
							lpSurfDlgMem->pSurfDoc->Draw();

							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(lpSurfDlgMem->hWnd,&rect);
							InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);							
						}
					}
					break;
				case 4: // plane
					{
						char str[1023];
						GetDlgItemText(hDlg, IDC_EDIT_PROFILE_GRID_COORDINATE,str,1022);
						double z = atof (str);

						if (lpSurfDlgMem->pSurfDoc->AddBitmap(lpstrFile, *pxMap, *pyMap, z) == 0)
						{
							lpSurfDlgMem->pSurfDoc->ZoomView();
							lpSurfDlgMem->pSurfDoc->Draw();

							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(lpSurfDlgMem->hWnd,&rect);
							InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);							
						}
					}
					break;
				case 5: // bmp profile
					{
						if (lpSurfDlgMem->pSurfDoc->AddBmpProfile(lpstrFile, *pxMap, *pyMap, *pyProfile) == 0)
						{
							lpSurfDlgMem->pSurfDoc->ZoomView();
							lpSurfDlgMem->pSurfDoc->Draw();

							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(lpSurfDlgMem->hWnd,&rect);
							InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);							
						}
					}
					break;
				}
				if (profileType == 1)// if bln
				{
					CheckDlgButton( hDlg, IDC_CHECK_NEW_PROFILE,
						new_bln_profile ? BST_CHECKED : BST_UNCHECKED );
					EnableWindow(GetDlgItem(hDlg, IDC_CHECK_NEW_PROFILE), bln_profile_was_started );

					EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME_ON_MAP), new_bln_profile);
					EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME), new_bln_profile);
					EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_MAP_ATTACH_FILE_NAME), new_bln_profile);
					EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME), new_bln_profile);
					
					EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME), new_bln_profile);
					EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_ACAD_YSCALE_FILE), new_bln_profile);
				}
				else
				{
					SetDlgItemText(hDlg, IDC_STATIC_ATTACH_ON_MAP2, "");
					SetDlgItemText(hDlg, IDC_STATIC_ATTACH_LINE_ON_PROFILE2, "");
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME_ON_MAP, "");
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME, "");
				}
				SetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, "");
			}
			break;
		case IDC_CHECK_CREATE_LAYERS:
			{
				create_layers = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_CREATE_LAYERS) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_NEW_PROFILE:
			{
				new_bln_profile = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_NEW_PROFILE) == BST_CHECKED;
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME_ON_MAP), new_bln_profile);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME), new_bln_profile);
				EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_MAP_ATTACH_FILE_NAME), new_bln_profile);
				EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME), new_bln_profile);
				EnableWindow(GetDlgItem(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME),			load_acad_yscale && new_bln_profile);
				EnableWindow(GetDlgItem(hDlg, IDC_BROSE_PROFILE_ACAD_YSCALE_FILE),			load_acad_yscale && new_bln_profile);
				if (new_bln_profile)
				{
					SetDlgItemText(hDlg, IDC_STATIC_ATTACH_ON_MAP2, "");
					SetDlgItemText(hDlg, IDC_STATIC_ATTACH_LINE_ON_PROFILE2, "");
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME_ON_MAP, "");
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME, "");
					SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, "");
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME, "");
				}
				else
				{
				}
			}
			break;
		case IDC_BROSE_PROFILE_FILE_NAME:
			{
				char lpstrFile[1024];
				lpstrFile[0] = '\0';
				switch(profileType)
				{
				case 0: // grid
					{	
						if (OpenFileDlg(hDlg, "Surfer 7 (*.grd)\0*.grd\0All files \0*.*\0", lpstrFile) == S_OK)
						{	
							SetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile);
							
							Grid * pGrid = new Grid;
							if(ImportSurfer7Grid(lpstrFile,pGrid) == 0)
							{
								pCGrid->Init(pGrid);
								// free 
								FreeGrid(pGrid);
							}
						}
					}
					break;
				case 1: // bln
					{
						TCHAR filter[] =  
							TEXT("AutoCAD DXF (*.dxf)\0*.dxf\0")
							TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
							TEXT("All Files (*.*)\0*.*\0");
						if (OpenFileDlg(hDlg, filter, lpstrFile) == S_OK)
						{	
							SetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile);							
						}
					}
					break;
				case 3: // bitmap
					{
						if (OpenFileDlg(hDlg, "JPEG (*.jpg)\0*.jpg\0All files \0*.*\0", lpstrFile) == S_OK)
						{	
							SetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile);							
						}
					}
					break;
				case 4: // plane
					{
						if (OpenFileDlg(hDlg, "JPEG (*.jpg)\0*.jpg\0All files \0*.*\0", lpstrFile) == S_OK)
						{	
							SetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile);							
						}
					}
					break;
				case 5: // bmp profile
					{
						if (OpenFileDlg(hDlg, "JPEG (*.jpg)\0*.jpg\0All files \0*.*\0", lpstrFile) == S_OK)
						{	
							SetDlgItemText(hDlg, IDC_EDIT_PROFILE_FILE_NAME, lpstrFile);							
						}
					}
					break;
				}
			}
			break;
		case IDC_BROSE_PROFILE_COORDINATE_ATTACH_FILE_NAME:
			{
				char lpstrFile[1024];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Coordinate Attach (*.txt)\0*.txt\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					double f;
					if (0 == ReadCoordinateFromFile(lpstrFile, f))
					{
						char str[128];
						sprintf(str, "%f", f);
						SetDlgItemText(hDlg,IDC_EDIT_PROFILE_GRID_COORDINATE, str);
					}

				}
			}
			break;
		case IDC_BROSE_PROFILE_MAP_ATTACH_FILE_NAME:
			{				
				char lpstrFile[1024];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Map Attach (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_MAP_ATTACH_FILE_NAME, lpstrFile);
					if (ReadBlnFile(lpstrFile, *pxMap,*pyMap, inside ) == 0)
					{
						char str[255];
						sprintf(str, "%d attach points", pxMap->size(), pyMap->size());
						//MessageBox(0, str, "", 0);
						SetDlgItemText(hDlg, IDC_STATIC_ATTACH_ON_MAP2, str);

					}
				}
			}
			break;
		case IDC_BROSE_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME:
			{
				char lpstrFile[1024];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Profile Attach (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ATTACH_LINE_ON_PROFILE_FILE_NAME, lpstrFile);
					int _inside;
					if (ReadBlnFile( lpstrFile, *pxProfile, *pyProfile, _inside ) == 0)
					{
						char str[255];
						sprintf(str, "%d attach points",  pxProfile->size(), pyProfile->size());
						//MessageBox(0, str, "", 0);
						SetDlgItemText(hDlg, IDC_STATIC_ATTACH_LINE_ON_PROFILE2, str);
					}
				}
			}
			break;

		case IDC_BROSE_PROFILE_ACAD_YSCALE_FILE:
			{
				char lpstrFile[1024];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Y Scale (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME, lpstrFile);
					int _inside;
					if (ReadBlnFile( lpstrFile, *pxAcadYscale, *pyAcadYscale, _inside ) == 0)
					{
						char str[255];
						sprintf(str, "%d yscale points",  pxAcadYscale->size(), pyAcadYscale->size());
						//MessageBox(0, str, "", 0);
						SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, str);

						if (pxAcadYscale->size() == 2 && pyAcadYscale->size() == 2)
							acad_yscale_loaded = true;

					}
				}
			}
			break;
		case IDOK :
			{
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();

				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

			}
			break;
			
		case IDCANCEL :
//#if FAST_GRID_LOADING
//			if (pGrid) delete pGrid;
//#else
			if (pCGrid) delete pCGrid;
//#endif
			if (pxMap) delete pxMap;
			if (pyMap) delete pyMap;
			if (pxProfile) delete pxProfile;						
			if (pyProfile) delete pyProfile;	

			if (pxAcadYscale) delete pxAcadYscale;
			if (pyAcadYscale) delete pyAcadYscale;

			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}



LRESULT CALLBACK DlgProcCreateProfileOnWells( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static vector<double> xMap, yMap, xProfile, yProfile, xAcadYscale, yAcadYscale;
	static bool load_acad_yscale;
	static bool acad_yscale_loaded;
	static bool enter_id_insteed_of_wells_names;
	static double z1w, y1a;
	static double z2w, y2a;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			enter_id_insteed_of_wells_names = false;

			load_acad_yscale = false;
			acad_yscale_loaded = false;
			z1w						= 0.0;
			y1a						= 0.0;
			z2w						= 1.0;
			y2a						= 1.0;
			CheckDlgButton(hDlg, IDC_CHECK_APPLY_YSCALE, load_acad_yscale);					
		}
		break;

	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_PROFILE_CREATE_ENTER_WELLS_ID:
			{
				enter_id_insteed_of_wells_names = IsDlgButtonChecked( hDlg, IDC_CHECK_PROFILE_CREATE_ENTER_WELLS_ID) == BST_CHECKED;
				if (enter_id_insteed_of_wells_names)
					SetDlgItemText(hDlg, IDC_STATIC_HOW_WELLS_ENTER, 
					"������� ������ ID_KT �������, ����������� - �������");
				else
					SetDlgItemText(hDlg, IDC_STATIC_HOW_WELLS_ENTER, 
					"������� ������ �������, ����������� - �������");

			}
			break;
			
		case IDC_CHECK_APPLY_YSCALE:
			{
				load_acad_yscale = IsDlgButtonChecked( hDlg, IDC_CHECK_APPLY_YSCALE) == BST_CHECKED;
//				SendMessage(hDlg, WM_USER+1,attachMode,profileType);
			}
			break;

		case IDC_BROSE_PROFILE_ACAD_YSCALE_FILE:
			{
				char lpstrFile[1024];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Y Scale (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					SetDlgItemText(hDlg, IDC_EDIT_PROFILE_ACAD_YSCALE_FILENAME, lpstrFile);
					int _inside;
					if (ReadBlnFile( lpstrFile, xAcadYscale, yAcadYscale, _inside ) == 0)
					{
						char str[255];
						sprintf(str, "%d yscale points",  xAcadYscale.size(), yAcadYscale.size());
						//MessageBox(0, str, "", 0);
						SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, str);

						if (xAcadYscale.size() == 2 && yAcadYscale.size() == 2)
							acad_yscale_loaded = true;
					}
				}
			}
			break;
		case IDOK :
			{
				double xprofile = 0.0;
				CPoint3 ustje, pre;
				char str[4096], s[128];
				GetDlgItemText(hDlg, IDC_EDIT_WELLS_LIST, str, 4095);
				char * p1, *p2;
				p1 = str;
				bool go = true, not_first = false;
				vector<long> v_ID_KT;
				while (go)
				{
					while (*p1 == ' ') p1++;
					p2 = strchr(p1, ',');
					if (p2)
					{
						strncpy(s, p1, p2-p1);
						s[p2-p1]='\0';
						p1 = p2+1;
					}
					else
					{
						go = false;
						strcpy(s, p1);
					}
					Well_3D * well = NULL;
					if (enter_id_insteed_of_wells_names)
						well = lpSurfDlgMem->pSurfDoc->FindWell(long(atoi(s)));
					else
						well = lpSurfDlgMem->pSurfDoc->FindWell(s);

					if (well && well->GetUstje(ustje))
					{		
						if (not_first)
						{
							xprofile += Distance(pre.x, pre.y, ustje.x, ustje.y);
						}
						not_first = true;
						pre = ustje;

						xMap.push_back(ustje.x);
						yMap.push_back(ustje.y);
						xProfile.push_back(xprofile);
						v_ID_KT.push_back(well->GetIdKt());
					}
					else
						printf("Warning: Well\"%s\" not found!!!\n", s);
				}

				SetDlgItemText(hDlg, IDC_EDIT_WELLS_LIST, "");
				
				GetDlgItemText(hDlg, IDC_EDIT_PROFILE_NAME, str, 4095);
				SetDlgItemText(hDlg, IDC_EDIT_PROFILE_NAME, "");

				z1w						= 0.0;
				y1a						= 0.0;
				z2w						= 1.0;
				y2a						= 1.0;

				if (acad_yscale_loaded && xAcadYscale.size() == 2 && yAcadYscale.size() == 2)
				{
					z1w = xAcadYscale[0], y1a = yAcadYscale[0];
					z2w = xAcadYscale[1], y2a = yAcadYscale[1];
					//lpSurfDlgMem->pSurfDoc->SetLastBlnProfileAcadYscale(z1w, y1a, z2w, y2a);							
				}

				if (lpSurfDlgMem->pSurfDoc->AddNewBlnProfile_db(NULL, str, &v_ID_KT, true, xMap, yMap, xProfile, acad_yscale_loaded, z1w, y1a, z2w, y2a, true) == 0)
				{
					lpSurfDlgMem->pSurfDoc->ConvertBlnProfilesTo3D(false);
									
					// init of zoomCoefZ_XY
					lpSurfDlgMem->pSurfDoc->ZoomView();
					lpSurfDlgMem->pSurfDoc->Draw();

					//====== �������������� ��� � ������ ���������
					RECT rect;
					GetClientRect(lpSurfDlgMem->hWnd,&rect);
					InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

					//**********************************
				}
				acad_yscale_loaded = false;

				xMap.clear();
				yMap.clear();
				xProfile.clear();
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


typedef struct
{
	HWND hWnd;
	GLfloat	m_AngleView;		// ���� �����������
	GLfloat	m_xTrans;			// C������� ����� X
	GLfloat	m_yTrans;			// C������� ����� Y
	GLfloat	m_zTrans;			// C������� ����� Z
	GLfloat	m_AngleX;			// ���� �������� ������ ��� X
	GLfloat	m_AngleY;			// ���� �������� ������ ��� Y
	GLfloat	m_AngleZ;			// ���� �������� ������ ��� Z
}	
SURFVIEWDLGDATA, *LPSURFVIEWDLGDATA;

LRESULT CALLBACK DlgProcSurfViewAnglesTranses( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFVIEWDLGDATA lpSurfViewDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfViewDlgMem = (LPSURFVIEWDLGDATA)lParam;
			
			char str[1023];

			sprintf(str,"%lf",lpSurfViewDlgMem->m_AngleX);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ANGLE_X,str);
			sprintf(str,"%lf",lpSurfViewDlgMem->m_AngleY);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ANGLE_Y,str);
			sprintf(str,"%lf",lpSurfViewDlgMem->m_AngleZ);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ANGLE_Z,str);

			sprintf(str,"%lf",lpSurfViewDlgMem->m_xTrans);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_TRANS_X,str);
			sprintf(str,"%lf",lpSurfViewDlgMem->m_yTrans);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_TRANS_Y,str);
			sprintf(str,"%lf",lpSurfViewDlgMem->m_zTrans);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_TRANS_Z,str);

			sprintf(str,"%lf",lpSurfViewDlgMem->m_AngleView);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_FIELD_VIEW_ANGLE,str);


		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				char str[1023];

				GetDlgItemText(hDlg, IDC_EDIT_SURF_ANGLE_X,str,1022);
				lpSurfViewDlgMem->m_AngleX = (float)atof (str);
				GetDlgItemText(hDlg, IDC_EDIT_SURF_ANGLE_Y,str,1022);
				lpSurfViewDlgMem->m_AngleY = (float)atof (str);
				GetDlgItemText(hDlg, IDC_EDIT_SURF_ANGLE_Z,str,1022);
				lpSurfViewDlgMem->m_AngleZ = (float)atof (str);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_TRANS_X,str,1022);
				lpSurfViewDlgMem->m_xTrans = (float)atof (str);
				GetDlgItemText(hDlg, IDC_EDIT_SURF_TRANS_Y,str,1022);
				lpSurfViewDlgMem->m_yTrans = (float)atof (str);
				GetDlgItemText(hDlg, IDC_EDIT_SURF_TRANS_Z,str,1022);
				lpSurfViewDlgMem->m_zTrans = (float)atof (str);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_FIELD_VIEW_ANGLE,str,1022);
				lpSurfViewDlgMem->m_AngleView = (float)atof (str);

				

				SendMessage(lpSurfViewDlgMem->hWnd, WM_COMMAND, IDD_SET_SURF_VIEW_ANGLES_TRANS,0);
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

int GetAlphaSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_SLIDER_SURF_ALPHA:
		nID = IDC_EDIT_SURF_ALPHA;
		return 0;
	case IDC_SLIDER_SURF_ALPHA_PLANE:
		nID = IDC_EDIT_SURF_ALPHA_PLANE;
		return 1;
	case IDC_SLIDER_SURF_ALPHA_GDIPLUS_PROFILES:
		nID = IDC_EDIT_SURF_ALPHA_GDIPLUS_PROFILES;
		return 2;
	}
	return 0;
}

LRESULT CALLBACK DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int m_Pos[11]; 			// ������ ������� ���������
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

		
			char str[1023];
			sprintf(str,"%d",lpSurfDlgMem->pSurfDoc->m_alpha);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA, str);

			sprintf(str,"%d",lpSurfDlgMem->pSurfDoc->m_alpha_plane);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA_PLANE, str);

			sprintf(str,"%d",lpSurfDlgMem->pSurfDoc->m_alpha_gdiplus_profiles);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA_GDIPLUS_PROFILES, str);

			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_razlomThickness);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_RAZLOM_THICKNESS, str);

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

			
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetAlphaSliderNum(hwnd, nID);
				int delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// ���������� �����
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// ������� Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// ������� End
					delta = +255;
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
					m_Pos[num] = newPos<0 ? 0 : newPos>255 ? 255 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				switch (num)
				{
				case 0:
					lpSurfDlgMem->pSurfDoc->m_alpha = m_Pos[num];
					break;
				case 1:
					lpSurfDlgMem->pSurfDoc->m_alpha_plane = m_Pos[num];
					break;
				case 2:
					lpSurfDlgMem->pSurfDoc->m_alpha_gdiplus_profiles = m_Pos[num];
					break;
				}


				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%d",lpSurfDlgMem->pSurfDoc->m_alpha);
				sprintf (s,"%d",m_Pos[num]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);

				hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA_PLANE);
				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);

				hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA_GDIPLUS_PROFILES);
				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== ������ �� ���� ������������
				//for (int i=0; i<2; i++)
					//====== ��������� ������������ ������ pPos
					m_Pos[0] = lpSurfDlgMem->pSurfDoc->m_alpha;
					m_Pos[1] = lpSurfDlgMem->pSurfDoc->m_alpha_plane;
					m_Pos[2] = lpSurfDlgMem->pSurfDoc->m_alpha_gdiplus_profiles;

				//====== ������ ��������������� ���������
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_ALPHA,
					IDC_SLIDER_SURF_ALPHA_PLANE,
					IDC_SLIDER_SURF_ALPHA_GDIPLUS_PROFILES
				};

				//====== ���� ������� �� ���� �����������
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== �������� Windows-��������� ���� ��������
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== ���������� ��� �������������
					int num = GetAlphaSliderNum(hwnd, nID);

					// ������� ���������� �������� � ��������� m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					char s[1024];
					//====== ������� ��������� ������ ������� �������
					sprintf (s,"%d",m_Pos[i]);
					//====== �������� ����� � ���� ������ �� ��������
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);
				}
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA,str,1022);
				int alpha = atoi (str);
				if (alpha >= 0.0)
					lpSurfDlgMem->pSurfDoc->m_alpha = alpha;
				else
					MessageBox(0, "Enter a valid value", "Alpha dialog", 0);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_RAZLOM_THICKNESS,str,1022);
				double thickness = atof (str);
				//if (thickness >= 0.0)
					lpSurfDlgMem->pSurfDoc->m_razlomThickness = thickness;
				//else
				//	MessageBox(0, "Enter a valid value", "Alpha dialog", 0);

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

				
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();


				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

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



int GetSphereRadiusSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_SLIDER_SURF_SPHERE_RADIUS:
		nID = IDC_STATIC_SURF_SPHERE_RADIUS_VALUE;
		return 0;
	}
	return 0;
}

LRESULT CALLBACK DlgProcSurfSphereRadius( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int m_Pos[11]; 			// ������ ������� ���������
	static double max_sphere_radius;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

		
			char str[1023];
			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_sphere_radius);
			SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE, str);

			max_sphere_radius = 2. * lpSurfDlgMem->pSurfDoc->m_sphere_radius;

			sprintf(str,"%lf", max_sphere_radius);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX, str);

			sprintf(str,"%d",lpSurfDlgMem->pSurfDoc->m_sphere_slices);
			SetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES, str);
			sprintf(str,"%d",lpSurfDlgMem->pSurfDoc->m_sphere_stacks);
			SetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS, str);			

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

			
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetSphereRadiusSliderNum(hwnd, nID);
				int delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// ���������� �����
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// ������� Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// ������� End
					delta = +255;
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
					m_Pos[num] = newPos<0 ? 0 : newPos>255 ? 255 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX,str,1022);
				max_sphere_radius = atof (str);

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				lpSurfDlgMem->pSurfDoc->m_sphere_radius = 
					max_sphere_radius * double(m_Pos[num]) / 100.;

				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%lf",lpSurfDlgMem->pSurfDoc->m_sphere_radius);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				int i;
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_SPHERE_RADIUS);

				SendMessage(				// returns LRESULT in lResult
				(HWND) hwnd,				// handle to destination control
				(UINT) TBM_SETRANGE,		// message ID
				(WPARAM) true,				// = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 100)	// = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== ������ �� ���� ������������
				for (i=0; i<1; i++)
					//====== ��������� ������������ ������ pPos
					m_Pos[i] = int(100. *  lpSurfDlgMem->pSurfDoc->m_sphere_radius / max_sphere_radius);

				//====== ������ ��������������� ���������
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_SPHERE_RADIUS
				};

				//====== ���� ������� �� ���� �����������
				for (i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					
					//=== �������� Windows-��������� ���� ��������
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== ���������� ��� �������������
					int num = GetSphereRadiusSliderNum(hwnd, nID);

					// ������� ���������� �������� � ��������� m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					/*char s[1024];
					//====== ������� ��������� ������ ������� �������
					sprintf (s,"%d",m_Pos[i]);
					//====== �������� ����� � ���� ������ �� ��������
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);

					MessageBox(hDlg, s,"",0);*/
					
				}
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX,str,1022);
				max_sphere_radius = atof (str);

				GetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES,str,1022);
				lpSurfDlgMem->pSurfDoc->m_sphere_slices = atoi (str);

				GetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS,str,1022);
				lpSurfDlgMem->pSurfDoc->m_sphere_stacks = atoi (str);

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

								
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();


				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

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

int GetKarotazhScaleSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_SLIDER_SURF_SPHERE_RADIUS:
		nID = IDC_STATIC_SURF_SPHERE_RADIUS_VALUE;
		return 0;
	case IDC_SLIDER_SURF_SPHERE_RADIUS2:
		nID = IDC_STATIC_SURF_SPHERE_RADIUS_VALUE2;
		return 1;
	case IDC_SLIDER_KAROTAZH_ALPHA:
		nID = IDC_EDIT_KAROTAZH_ALPHA;
		return 2;
	}
	return 0;
}

LRESULT CALLBACK DlgProcSurfKarotazhScale( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int m_Pos[11]; 			// ������ ������� ���������
	static double max_karotazh_scale;
	static double max_karotazh_scale_2d;
	static int index;
	static karotazh_list_item::draw_mode_2d draw_mode;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			index = -1;

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_INITIAL_PARAMETERS,0);
		
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)"All karotazhes");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


			for (vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
							it != Well_3D::karotazh_list.end(); it++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)(*it).name.c_str());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_SETCURSEL,
				index+1, (LPARAM)0 );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);
			
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetKarotazhScaleSliderNum(hwnd, nID);
				int delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// ���������� �����
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// ������� Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// ������� End
					delta = +255;
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
					m_Pos[num] = newPos<0 ? 0 : newPos>255 ? 255 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX,str,1022);
				max_karotazh_scale = atof (str);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX2,str,1022);
				max_karotazh_scale_2d = atof (str);

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				switch (num)
				{
				case 0:
					{
						Karotazh::s_scale = 
							max_karotazh_scale * double(m_Pos[num]) / 100.;
						
						if(index < 0)
						{
							for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
								it != Well_3D::karotazh_list.end(); it++)
							{
								(*it).scale = Karotazh::s_scale;
							}
						}
						else
						{
							if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].scale = Karotazh::s_scale;
						}
						//====== �������������� ��������� ������ �������
						char s[1024];
						sprintf (s,"%lf",Karotazh::s_scale);
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
					break;
				case 1:
					{
						Karotazh::s_scale_2d = 
							max_karotazh_scale_2d * double(m_Pos[num]) / 100.;
						
						if(index < 0)
						{
							for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
								it != Well_3D::karotazh_list.end(); it++)
							{
								(*it).scale_2d = Karotazh::s_scale_2d;
							}
						}
						else
						{
							if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].scale_2d = Karotazh::s_scale_2d;
						}
						//====== �������������� ��������� ������ �������
						char s[1024];
						sprintf (s,"%lf",Karotazh::s_scale_2d);
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
					break;
				case 2:
					{
						Karotazh::s_alpha = m_Pos[num];
						if(index < 0)
						{
							for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
								it != Well_3D::karotazh_list.end(); it++)
							{
								(*it).alpha = Karotazh::s_alpha;
							}
						}
						else
						{
							if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].alpha = Karotazh::s_alpha;
						}					
						//====== �������������� ��������� ������ �������
						char s[1024];
						sprintf (s,"%d",Karotazh::s_alpha);
						SetDlgItemText(hDlg, nID, (LPCTSTR)s);
					}
					break;
				}


				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
				//lpSurfDlgMem->pSurfDoc->Draw();
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();



				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_INITIAL_PARAMETERS:
			{
				char str[1023];
				sprintf(str,"%d",Karotazh::slices);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES, str);

				sprintf(str,"%d",Karotazh::stacks);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS, str);	

				sprintf(str,"%d",Karotazh::s_alpha);
				SetDlgItemText(hDlg, IDC_EDIT_KAROTAZH_ALPHA, str);

				sprintf(str,"%lf",Karotazh::s_scale);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE, str);

				sprintf(str,"%lf",Karotazh::s_scale_2d);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE2, str);

				max_karotazh_scale = 2. * Karotazh::s_scale;
				sprintf(str,"%lf", max_karotazh_scale);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX, str);

				max_karotazh_scale_2d = 2. * Karotazh::s_scale_2d;
				sprintf(str,"%lf", max_karotazh_scale_2d);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX2, str);

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_LOGARITHMIC,
					Karotazh::s_logarithmic_scale ? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_FROM_ZERO,
					Karotazh::s_scale_from_zero? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_ON_OFF,
					Karotazh::s_checked? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_DISP_POINT_VALUES,
					Karotazh::s_disp_point_values? BST_CHECKED : BST_UNCHECKED );
				
				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_DISP_POINT_VALUES2,
					Karotazh::s_disp_point_values_2d ? BST_CHECKED : BST_UNCHECKED );
				
				CheckRadioButton( hDlg,
					IDC_RADIO_DRAW_MODE_2D_RIGHT,
					IDC_RADIO_DRAW_MODE_2D_BOTH,
					IDC_RADIO_DRAW_MODE_2D_RIGHT);
			}
			break;
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_SPHERE_RADIUS);

				SendMessage(				// returns LRESULT in lResult
				(HWND) hwnd,				// handle to destination control
				(UINT) TBM_SETRANGE,		// message ID
				(WPARAM) true,				// = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 100)	// = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);

				//=== �������� Windows-��������� ���� ��������
				hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_SPHERE_RADIUS2);

				SendMessage(				// returns LRESULT in lResult
				(HWND) hwnd,				// handle to destination control
				(UINT) TBM_SETRANGE,		// message ID
				(WPARAM) true,				// = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 100)	// = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);

				//=== �������� Windows-��������� ���� ��������
				hwnd = GetDlgItem(hDlg, IDC_SLIDER_KAROTAZH_ALPHA);

				SendMessage(				// returns LRESULT in lResult
				(HWND) hwnd,				// handle to destination control
				(UINT) TBM_SETRANGE,		// message ID
				(WPARAM) true,				// = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)	// = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== ������ �� ���� ������������
				//for (int i=0; i<1; i++)
					//====== ��������� ������������ ������ pPos
					m_Pos[0] = int(100. *  Karotazh::s_scale / max_karotazh_scale);
					m_Pos[1] = int(100. *  Karotazh::s_scale_2d / max_karotazh_scale_2d);
					m_Pos[2] = int(Karotazh::s_alpha);

				//====== ������ ��������������� ���������
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_SPHERE_RADIUS,
					IDC_SLIDER_SURF_SPHERE_RADIUS2,
					IDC_SLIDER_KAROTAZH_ALPHA
				};

				//====== ���� ������� �� ���� �����������
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					
					//=== �������� Windows-��������� ���� ��������
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== ���������� ��� �������������
					int num = GetKarotazhScaleSliderNum(hwnd, nID);

					// ������� ���������� �������� � ��������� m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					/*char s[1024];
					//====== ������� ��������� ������ ������� �������
					sprintf (s,"%d",m_Pos[i]);
					//====== �������� ����� � ���� ������ �� ��������
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);

					MessageBox(hDlg, s,"",0);*/
					
				}
			}
			break;
		case IDC_CHECK_KAROTAZH_ON_OFF:
			{
				Karotazh::s_checked = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_KAROTAZH_ON_OFF) == BST_CHECKED;
				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).checked = Karotazh::s_checked;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].checked = Karotazh::s_checked;
				}

				/*// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
				//lpSurfDlgMem->pSurfDoc->Draw();
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);
				*/
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
			}
			break;
		case IDC_CHECK_KAROTAZH_DISP_POINT_VALUES:
			{
				Karotazh::s_disp_point_values = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_KAROTAZH_DISP_POINT_VALUES) == BST_CHECKED;
				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).disp_point_values = Karotazh::s_disp_point_values;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].disp_point_values = Karotazh::s_disp_point_values;
				}

				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
				//lpSurfDlgMem->pSurfDoc->Draw();
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);
				
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_CHECK_KAROTAZH_DISP_POINT_VALUES2:
			{
				Karotazh::s_disp_point_values_2d = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_KAROTAZH_DISP_POINT_VALUES2) == BST_CHECKED;
				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).disp_point_values_2d = Karotazh::s_disp_point_values_2d;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].disp_point_values_2d = Karotazh::s_disp_point_values_2d;
				}

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
			}
			break;
		case IDC_CHECK_KAROTAZH_SCALE_LOGARITHMIC:
			{
				Karotazh::s_logarithmic_scale = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_KAROTAZH_SCALE_LOGARITHMIC) == BST_CHECKED;
				
				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).logarithmic_scale = Karotazh::s_logarithmic_scale;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].logarithmic_scale = Karotazh::s_logarithmic_scale;
				}

				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
				//lpSurfDlgMem->pSurfDoc->Draw();
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
			}
			break;
		case IDC_CHECK_KAROTAZH_SCALE_FROM_ZERO:
			{
				Karotazh::s_scale_from_zero = 
					IsDlgButtonChecked( hDlg, IDC_CHECK_KAROTAZH_SCALE_FROM_ZERO) == BST_CHECKED;
				
				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).scale_from_zero = Karotazh::s_scale_from_zero;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) Well_3D::karotazh_list[index].scale_from_zero = Karotazh::s_scale_from_zero;
				}

				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
				//lpSurfDlgMem->pSurfDoc->Draw();
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
			}
			break;
		case IDC_RADIO_DRAW_MODE_2D_RIGHT:
				draw_mode = karotazh_list_item::draw_mode_2d::right;
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_DRAW_MODE_2D,0);
				break;
		case IDC_RADIO_DRAW_MODE_2D_LEFT:
				draw_mode = karotazh_list_item::draw_mode_2d::left;
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_DRAW_MODE_2D,0);
				break;
		case IDC_RADIO_DRAW_MODE_2D_BOTH:
				draw_mode = karotazh_list_item::draw_mode_2d::both;
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_DRAW_MODE_2D,0);
				break;
		case IDC_INIT_DRAW_MODE_2D:
			{				
				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).m_draw_mode_2d = draw_mode;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) 
						Well_3D::karotazh_list[index].m_draw_mode_2d = draw_mode;
				}

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
			}
			break;

		case IDC_COMBO_SELECT_KAROTAZH:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_INITIAL_PARAMETERS,0);
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
				if(index < 0)
				{
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) 
					{
						Karotazh::s_scale_from_zero = 
							Well_3D::karotazh_list[index].scale_from_zero;
						Karotazh::s_logarithmic_scale = 
							Well_3D::karotazh_list[index].logarithmic_scale;
						Karotazh::s_scale = 
							Well_3D::karotazh_list[index].scale;
						Karotazh::s_scale_2d = 
							Well_3D::karotazh_list[index].scale_2d;
						Karotazh::s_alpha = 
							Well_3D::karotazh_list[index].alpha;
						Karotazh::s_checked = 
							Well_3D::karotazh_list[index].checked;
						Karotazh::s_disp_point_values = 
							Well_3D::karotazh_list[index].disp_point_values;

						Karotazh::s_disp_point_values_2d = 
							Well_3D::karotazh_list[index].disp_point_values_2d;

						switch (Well_3D::karotazh_list[index].m_draw_mode_2d)
						{
						case karotazh_list_item::draw_mode_2d::right:
							{
								CheckRadioButton( hDlg,
									IDC_RADIO_DRAW_MODE_2D_RIGHT,
									IDC_RADIO_DRAW_MODE_2D_BOTH,
									IDC_RADIO_DRAW_MODE_2D_RIGHT);
							}
							break;
						case karotazh_list_item::draw_mode_2d::left:
							{
								CheckRadioButton( hDlg,
									IDC_RADIO_DRAW_MODE_2D_RIGHT,
									IDC_RADIO_DRAW_MODE_2D_BOTH,
									IDC_RADIO_DRAW_MODE_2D_LEFT);
							}
							break;
						case karotazh_list_item::draw_mode_2d::both:
							{
								CheckRadioButton( hDlg,
									IDC_RADIO_DRAW_MODE_2D_RIGHT,
									IDC_RADIO_DRAW_MODE_2D_BOTH,
									IDC_RADIO_DRAW_MODE_2D_BOTH);
							}
							break;
						}


					}
				}
			}
			break;
		case IDC_BUTTON_SET_KAROTAZH_COLOR:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				if(index < 0)
				{
				}
				else
				{
					if (index < Well_3D::karotazh_list.size()) 
					{
						COLORREF color = Well_3D::karotazh_list[index].color;
						if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
						{
							Well_3D::karotazh_list[index].color = color;
						}
					}
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX,str,1022);
				max_karotazh_scale = atof (str);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_SPHERE_RADIUS_MAX2,str,1022);
				max_karotazh_scale_2d = atof (str);

				GetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES,str,1022);
				Karotazh::slices = atoi (str);

				GetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS,str,1022);
				Karotazh::stacks = atoi (str);

				GetDlgItemText(hDlg, IDC_EDIT_KAROTAZH_ALPHA,str,1022);
				Karotazh::s_alpha = atoi (str);

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

				if(index < 0)
				{
					for(vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
						it != Well_3D::karotazh_list.end(); it++)
					{
						(*it).scale_from_zero = Karotazh::s_scale_from_zero;
						(*it).logarithmic_scale = Karotazh::s_logarithmic_scale;
						(*it).scale = Karotazh::s_scale;
						(*it).scale_2d = Karotazh::s_scale_2d;
						(*it).alpha = Karotazh::s_alpha;
						(*it).checked = Karotazh::s_checked;
						(*it).disp_point_values = Karotazh::s_disp_point_values;
						(*it).disp_point_values_2d = Karotazh::s_disp_point_values_2d;
					}
				}
				else
				{
					if (index < Well_3D::karotazh_list.size())
					{
						Well_3D::karotazh_list[index].scale_from_zero = Karotazh::s_scale_from_zero;
						Well_3D::karotazh_list[index].logarithmic_scale = Karotazh::s_logarithmic_scale;
						Well_3D::karotazh_list[index].scale = Karotazh::s_scale;
						Well_3D::karotazh_list[index].scale_2d = Karotazh::s_scale_2d;
						Well_3D::karotazh_list[index].alpha = Karotazh::s_alpha;
						Well_3D::karotazh_list[index].checked = Karotazh::s_checked;
						Well_3D::karotazh_list[index].disp_point_values = Karotazh::s_disp_point_values;
						Well_3D::karotazh_list[index].disp_point_values_2d = Karotazh::s_disp_point_values_2d;
					}
				}								
				// init of zoomCoefZ_XY
				//lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
				//lpSurfDlgMem->pSurfDoc->Draw();
				ReDrawDrills(lpSurfDlgMem->pSurfDoc);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

				win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
				if (pwin_project) pwin_project->UpdateAllMapViews();
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
#include <windowsx.h>
WNDPROC wpOrigProcDlgProcKarotazhList; 
WNDPROC wpOrigProcWellsDrawList; 
LRESULT CALLBACK DlgProcKarotazhList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndKarotazhList   = NULL;
	int wmId, wmEvent;

	static int context_menu_item;

    if (message == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      // Control wants all keys - All keyboard input     
	} 
	switch (message) 
	{
		case WM_INITDIALOG :
			{
				lpSurfDlgMem = (LPSURFDLGDATA)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				if (lpSurfDlgMem->pSurfDoc)
				{
					 if (lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
					 {
						 hwndKarotazhList = lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.GetWnd();

						 char str[1024];

						 size_t cols = 7;
						 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetCols(cols);

						 vector<int> ColomnsEditing(cols);
						 vector <bool*> vpbColomnsChecked(cols);
						 
						 ColomnsEditing[0] = 1;
						 ColomnsEditing[1] = 1;
						 ColomnsEditing[2] = 0;
						 ColomnsEditing[3] = 0;
						 ColomnsEditing[4] = 0;
						 ColomnsEditing[5] = 1;
						 ColomnsEditing[6] = 0;
						 						
						 for (vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
							 it != Well_3D::karotazh_list.end(); it++)
						 {
							 vpbColomnsChecked[0] = &(*it).checked;
							 vpbColomnsChecked[1] = NULL;
							 vpbColomnsChecked[2] = &(*it).disp_point_values_2d;
							 vpbColomnsChecked[3] = &(*it).scale_from_zero;
							 vpbColomnsChecked[4] = &(*it).logarithmic_scale;
							 vpbColomnsChecked[5] = NULL;
							 vpbColomnsChecked[6] = &(*it).disp_point_values;

							 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.AddRow(LPARAM(0), ColomnsEditing, vpbColomnsChecked);
							 size_t r = lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.Rows()-1;
							 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetItemString(r,0,(*it).name);
							 sprintf(str, "%f", (*it).scale_2d);
							 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetItemString(r,1,str);
							 sprintf(str, "%f", (*it).scale);
							 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetItemString(r,5,str);
						 }
					 }
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(0, "Parametr");
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(1, "Scale2D");
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(2, "Values2D");
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(3, "Base 0");
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(4, "Logarithmic");
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(5, "Scale3D");
					 lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.SetHeaderString(6, "Values3D");
				}	
			}
			break;
#if !USE_LISTVIEW_STANDART_KL 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.OnEndEdit();
					//lpSurfDlgMem->pSurfDoc->UpdateLayersNames();
					bool update2Dview, update3Dview;
					lpSurfDlgMem->pSurfDoc->UpdateKarotazhNames(update2Dview, update3Dview);
					if(update3Dview)
					{
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllGraphicsViews();	
					}
					if(update2Dview)
					{
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
			}
			break; 
#endif
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndKarotazhList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndKarotazhList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				printf("context_menu_item = %d\n", context_menu_item);
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );

				

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.UpdateView();
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < Well_3D::karotazh_list.size()) 
						{
							COLORREF color = Well_3D::karotazh_list[context_menu_item].color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								Well_3D::karotazh_list[context_menu_item].color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllViews();							
							}
						}
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_RIGHT:
				{
					if (context_menu_item >= 0 && context_menu_item < Well_3D::karotazh_list.size())
					{
						Well_3D::karotazh_list[context_menu_item].m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_LEFT:
				{
					if (context_menu_item >= 0 && context_menu_item < Well_3D::karotazh_list.size())
					{
						Well_3D::karotazh_list[context_menu_item].m_draw_mode_2d = karotazh_list_item::draw_mode_2d::left;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();							
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_BOTH:
				{
					if (context_menu_item >= 0 && context_menu_item < Well_3D::karotazh_list.size())
					{
						Well_3D::karotazh_list[context_menu_item].m_draw_mode_2d = karotazh_list_item::draw_mode_2d::both;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			}
			break;

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 100; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_KL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndKarotazhList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_KarotazhListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndKarotazhList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_KarotazhListViewTab.OnNotify(lParam))
							pwin_project->UpdateAllViews();
#if USE_LISTVIEW_STANDART_KL 
						if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
							pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcDlgProcKarotazhList, hwnd, message, 
	   wParam, lParam); 
}
LRESULT CALLBACK DlgProcWellsDrawList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.GetWnd();

					size_t cols = 5;
					lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetCols(cols);

					vector<int> ColomnsEditing(cols);
					vector <bool*> vpbColomnsChecked(cols);
					
					ColomnsEditing[0] = 1;
					ColomnsEditing[1] = 1;
					ColomnsEditing[2] = 0;
					ColomnsEditing[3] = 0;
					ColomnsEditing[4] = 0;

					for (vector<wells_draw_list_item * >::iterator it = Well_3D::wells_draw_list.begin();
						it != Well_3D::wells_draw_list.end(); it++)
					{
						vpbColomnsChecked[0] = &(*it)->check_draw;
						vpbColomnsChecked[1] = NULL;
						vpbColomnsChecked[2] = &(*it)->draw2d_border;
						vpbColomnsChecked[3] = &(*it)->draw2d_label;
						vpbColomnsChecked[4] = &(*it)->draw2d_sloj_name;

						lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.AddRow(LPARAM(0), ColomnsEditing, vpbColomnsChecked);
						size_t r = lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.Rows()-1;
						lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetItemString(r,0,(*it)->my_name);
						sprintf(str, "%0.1f\0", (*it)->draw_width);
						lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetItemString(r,1,str);
					}
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetHeaderString(0, "Colomn name");
				lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetHeaderString(1, "Width");
				lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetHeaderString(2, "Draw border");
				lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetHeaderString(3, "Draw Label");
				lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.SetHeaderString(4, "Draw sloj name");
			}
		}
		break;
#if !USE_LISTVIEW_STANDART_WDL 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateWellDrawListNames();
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break; 
#endif
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.UpdateView();
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_WELLSDRAWLIST_MOVEITEMUP:
				{
					lpSurfDlgMem->pSurfDoc->WellsDrawList_MoveItemUp(context_menu_item);
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();

				}
				break;
			case ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN:
				{
					lpSurfDlgMem->pSurfDoc->WellsDrawList_MoveItemDown(context_menu_item);
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
				break;
			case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < Well_3D::wells_draw_list.size()) 
						{
							COLORREF color = Well_3D::wells_draw_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								Well_3D::wells_draw_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_RIGHT:
				{
					if (context_menu_item >= 0 && context_menu_item < Well_3D::wells_draw_list.size())
					{
						Well_3D::wells_draw_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::right;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_LEFT:
				{
					if (context_menu_item >= 0 && context_menu_item < Well_3D::wells_draw_list.size())
					{
						Well_3D::wells_draw_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::left;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();							
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_BOTH:
				{
					if (context_menu_item >= 0 && context_menu_item < Well_3D::wells_draw_list.size())
					{
						Well_3D::wells_draw_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::both;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			}
			break;

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_WDL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_WellsDrawListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_WellsDrawListViewTab.OnNotify(lParam))
							pwin_project->UpdateAllViews();
#if USE_LISTVIEW_STANDART_WDL 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcWellsDrawList, hwnd, message, 
	   wParam, lParam);
}

LRESULT CALLBACK DlgProcWellsDrawAndKarotazhList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hWndKarotazhList   = NULL;
	static HWND hWndWellsDrawList   = NULL;
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				lpSurfDlgMem = (LPSURFDLGDATA)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				// Retrieve the handle to the Map control. 
				hWndKarotazhList = GetDlgItem(hDlg, IDC_STATIC_KAROTAZH_LIST); 

				// Subclass the picture control. 
				wpOrigProcDlgProcKarotazhList = (WNDPROC) SetWindowLongPtr(hWndKarotazhList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcKarotazhList); 

				SendMessage(hWndKarotazhList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################
				// Retrieve the handle to the Map control. 
				hWndWellsDrawList = GetDlgItem(hDlg, IDC_STATIC_WELLS_DRAW); 

				// Subclass the picture control. 
				wpOrigProcWellsDrawList = (WNDPROC) SetWindowLongPtr(hWndWellsDrawList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcWellsDrawList); 

				SendMessage(hWndWellsDrawList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################			
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}
WNDPROC wpOrigProcSurfacesOrderList; 
WNDPROC wpOrigProcSurfacesBlankOrderList; 
WNDPROC wpOrigProcSurfacesBlankFunctionsList; 
LRESULT CALLBACK DlgProcSurfacesOrderList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.GetWnd();

					size_t cols = 4;
					lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetCols(cols);

					vector<int> ColomnsEditing(cols);
					vector <bool*> vpbColomnsChecked(cols);
					
					ColomnsEditing[0] = 0;
					ColomnsEditing[1] = 0;
					ColomnsEditing[2] = 0;
					ColomnsEditing[3] = 0;

					for (vector<surface_order_list_item * >::iterator it = GeoSurface::surface_order_list.begin();
						it != GeoSurface::surface_order_list.end(); it++)
					{
						vpbColomnsChecked[0] = &(*it)->check;
						vpbColomnsChecked[1] = &(*it)->check2;
						vpbColomnsChecked[2] = NULL;//&(*it)->draw2d_border;
						vpbColomnsChecked[3] = NULL;//&(*it)->draw2d_sloj_name;

						lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.AddRow(LPARAM(0), ColomnsEditing, vpbColomnsChecked);
						size_t r = lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.Rows()-1;
						lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetItemString(r,0,(*it)->my_name);
						//sprintf(str, "%0.1f\0", (*it)->draw_width);
						sprintf(str, "id_surf = %d\0", (*it)->id_surf);
						lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetItemString(r,1,str);
					}
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetHeaderString(0, "��� �����������");
				lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetHeaderString(1, "");
				lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetHeaderString(2, "");
				lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.SetHeaderString(3, "");
			}
		}
		break;
		/*
#if !USE_LISTVIEW_STANDART_SO 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateWellDrawListNames();
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break; 
#endif*/
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				//AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				//AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.UpdateView();
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_WELLSDRAWLIST_MOVEITEMUP:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceOrderList_MoveItemUp(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();

				}
				break;
			case ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceOrderList_MoveItemDown(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();
				}
				break;
			/*case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < GeoSurface::surface_order_list.size()) 
						{
							COLORREF color = GeoSurface::surface_order_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								GeoSurface::surface_order_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_RIGHT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_order_list.size())
					{
						GeoSurface::surface_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::right;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_LEFT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_order_list.size())
					{
						GeoSurface::surface_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::left;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();							
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_BOTH:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_order_list.size())
					{
						GeoSurface::surface_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::both;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;*/
			}
			break;

       /* case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;*/
#if !USE_LISTVIEW_STANDART_SO 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_SurfacesOrderListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_SurfacesOrderListViewTab.OnNotify(lParam))
						{
							pwin_project->SurfaceOrderList_UpdateCheckings();
							//pwin_project->UpdateAllViews();
						}
#if USE_LISTVIEW_STANDART_SO 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcSurfacesOrderList, hwnd, message, 
	   wParam, lParam);
}

LRESULT CALLBACK DlgProcSurfacesBlankOrderList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.GetWnd();

					size_t cols = 7;
					lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetCols(cols);

					vector<int> ColomnsEditing(cols);
					vector <bool*> vpbColomnsChecked(cols);
					
					ColomnsEditing[0] = 0;
					ColomnsEditing[1] = 0;
					ColomnsEditing[2] = 0;
					ColomnsEditing[3] = 0;
					ColomnsEditing[4] = 0;
					ColomnsEditing[5] = 0;
					ColomnsEditing[6] = 0;

					for (vector<surface_blank_order_list_item * >::iterator it = GeoSurface::surface_blank_order_list.begin();
						it != GeoSurface::surface_blank_order_list.end(); it++)
					{
						vpbColomnsChecked[0] = &(*it)->check_blank_me;
						vpbColomnsChecked[1] = &(*it)->check_blank_me_up;
						vpbColomnsChecked[2] = &(*it)->check_blank_me_up_above;
						vpbColomnsChecked[3] = &(*it)->check_blank_me_down;
						vpbColomnsChecked[4] = &(*it)->check_blank_me_down_above;
						vpbColomnsChecked[5] = &(*it)->check_blank_by_me_up;
						vpbColomnsChecked[6] = &(*it)->check_blank_by_me_down;

						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.AddRow(LPARAM(0), ColomnsEditing, vpbColomnsChecked);
						size_t r = lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.Rows()-1;
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetItemString(r,0,(*it)->my_name);
						
						sprintf(str, "id_surf = %d\0", (*it)->id_surf);
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetItemString(r,1,str);
					}
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(0, "��� �����������");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(1, "blank_me_up");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(2, "blank_me_up_above");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(3, "blank_me_down");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(4, "blank_me_down_above");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(5, "blank_by_me_up");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.SetHeaderString(6, "blank_by_me_down");
			}
		}
		break;
		/*
#if !USE_LISTVIEW_STANDART_SBO 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateWellDrawListNames();
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break; 
#endif
			*/
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				/*AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );*/

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.UpdateView();
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_WELLSDRAWLIST_MOVEITEMUP:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceBlankOrderList_MoveItemUp(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();

				}
				break;
			case ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceBlankOrderList_MoveItemDown(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();
				}
				break;
			/*case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < GeoSurface::surface_blank_order_list.size()) 
						{
							COLORREF color = GeoSurface::surface_blank_order_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								GeoSurface::surface_blank_order_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_RIGHT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_blank_order_list.size())
					{
						GeoSurface::surface_blank_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::right;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_LEFT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_blank_order_list.size())
					{
						GeoSurface::surface_blank_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::left;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();							
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_BOTH:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_blank_order_list.size())
					{
						GeoSurface::surface_blank_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::both;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;*/
			}
			break;

        /*case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;*/
#if !USE_LISTVIEW_STANDART_SBO 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_SurfacesBlankOrderListViewTab.OnNotify(lParam))
						{
							pwin_project->SurfaceBlankOrderList_UpdateCheckings();
							//pwin_project->UpdateAllViews();
						}
#if USE_LISTVIEW_STANDART_SBO 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcSurfacesBlankOrderList, hwnd, message, 
	   wParam, lParam);
}

LRESULT CALLBACK DlgProcSurfacesBlankFunctionsList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			//printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.GetWnd();

					size_t cols = 3;
					lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetCols(cols);

					for (vector<surface_blank_functions_list_item * >::iterator it = GeoSurface::surface_blank_functions_list.begin();
						it != GeoSurface::surface_blank_functions_list.end(); it++)
					{
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.AddRow(LPARAM(0), NULL);
						size_t r = lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.Rows()-1;
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetItemString(r, 0, (*it)->name_surf_obj);
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetItemString(r, 1, (*it)->name_surf_param);
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetItemString(r, 2, surface_blank_functions_list_item::get_blank_function_name((*it)->id_blank_fun));
					}
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetHeaderString(0, "����������");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetHeaderString(1, "� �������");
				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.SetHeaderString(2, "�������");
			}
		}
		break;
		/*
#if !USE_LISTVIEW_STANDART_SBF 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_SurfacesBlankOrderListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateWellDrawListNames();
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break; 
#endif
			*/
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_SURFACEBLANKFUNCTIONS_SWAPITEMSURFACES, "Swap Surfaces" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_SURFACEBLANKFUNCTIONS_SWAPITEMMETHOD, "Swap Method" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				/*AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );*/

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.UpdateView();
			}
			break;

		case WM_CHAR :
			{
				if (wParam == 27)//Esc
				{
					int i = ListView_GetSelectionMark(hwndList);
					i;



//					Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
//					if (selected_object)
//						selected_object->DestroyPropertyWindow();
				}
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_SURFACEBLANKFUNCTIONS_SWAPITEMSURFACES:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceBlankFunctionsList_SwapItemSurfaces(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();

				}
				break;
			case ID_TREE_SURFACEBLANKFUNCTIONS_SWAPITEMMETHOD:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceBlankFunctionsList_SwapItemMethod(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();
				}
				break;

			}
			break;

        /*case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;*/
#if !USE_LISTVIEW_STANDART_SBF 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_SurfacesBlankFunctionsListViewTab.OnNotify(lParam))
						{
							pwin_project->SurfaceBlankOrderList_UpdateCheckings();
							//pwin_project->UpdateAllViews();
						}
#if USE_LISTVIEW_STANDART_SBF 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcSurfacesBlankFunctionsList, hwnd, message, 
	   wParam, lParam);
}

LRESULT CALLBACK DlgProcSurfacesOrderLists(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hWndSurfacesOrderList   = NULL;
	static HWND hWndSurfacesBlankOrderList   = NULL;
	static HWND hWndSurfacesBlankFunctionsList   = NULL;
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				lpSurfDlgMem = (LPSURFDLGDATA)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				// Retrieve the handle to the Map control. 
				hWndSurfacesOrderList = GetDlgItem(hDlg, IDC_STATIC_SURFACES_ORDER); 

				// Subclass the picture control. 
				wpOrigProcSurfacesOrderList = (WNDPROC) SetWindowLongPtr(hWndSurfacesOrderList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcSurfacesOrderList); 

				SendMessage(hWndSurfacesOrderList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################
				// Retrieve the handle to the Map control. 
				hWndSurfacesBlankOrderList = GetDlgItem(hDlg, IDC_STATIC_SURFACES_BLANK_ORDER); 

				// Subclass the picture control. 
				wpOrigProcSurfacesBlankOrderList = (WNDPROC) SetWindowLongPtr(hWndSurfacesBlankOrderList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcSurfacesBlankOrderList); 

				SendMessage(hWndSurfacesBlankOrderList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################			
				// Retrieve the handle to the Map control. 
				hWndSurfacesBlankFunctionsList = GetDlgItem(hDlg, IDC_STATIC_SURFACES_BLANK_FUNCTIONS); 

				// Subclass the picture control. 
				wpOrigProcSurfacesBlankFunctionsList = (WNDPROC) SetWindowLongPtr(hWndSurfacesBlankFunctionsList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcSurfacesBlankFunctionsList); 

				SendMessage(hWndSurfacesBlankFunctionsList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################

							
				LRESULT lResult;
				
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				SendDlgItemMessage( hDlg, IDC_COMBO_BLANK_FUN, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				for (int i = 0; i < 3; ++i)
				{
					lResult = SendDlgItemMessage( hDlg, IDC_COMBO_BLANK_FUN, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)surface_blank_functions_list_item::get_blank_function_name(i).c_str());
					SendDlgItemMessage( hDlg, IDC_COMBO_BLANK_FUN, CB_SETITEMDATA, lResult,	i);
				}
				SendDlgItemMessage( hDlg, IDC_COMBO_BLANK_FUN, CB_SETCURSEL, 0, (LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			

				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_OBJ, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_PARAM, CB_RESETCONTENT, 0,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				for (vector<surface_order_list_item *>::iterator 
					it = GeoSurface::surface_order_list.begin();
					it != GeoSurface::surface_order_list.end(); it++)
				{
					if ((*it) && lpSurfDlgMem && lpSurfDlgMem->pSurfDoc)
					{
						GeoSurface * geo_surf = lpSurfDlgMem->pSurfDoc->FindGeoSurface((*it)->id_surf);
						if(geo_surf)
						{

							lResult = SendDlgItemMessage(hDlg, IDC_COMBO_SURF_OBJ, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)geo_surf->GetName().c_str());
							SendDlgItemMessage( hDlg, IDC_COMBO_SURF_OBJ, CB_SETITEMDATA, lResult,
								(LPARAM)(*it)->id_surf);

							lResult = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_PARAM, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)geo_surf->GetName().c_str());
							SendDlgItemMessage( hDlg, IDC_COMBO_SURF_PARAM, CB_SETITEMDATA, lResult,
								(LPARAM)(*it)->id_surf);
						}
					}
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_OBJ, CB_SETCURSEL,	0, (LPARAM)0 );
				SendDlgItemMessage( hDlg, IDC_COMBO_SURF_PARAM, CB_SETCURSEL, 0, (LPARAM)0 );
			}
			break;

		case WM_COMMAND :
			{
				switch( LOWORD( wParam ) )
				{	
				case IDC_BUTTON_DELETE_BLANK_FUN:
					{
	
						if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc) 
						{
							// LVM_GETSELECTIONMARK LVM_GETSELECTIONMARK
							HWND hList = lpSurfDlgMem->pSurfDoc->m_SurfacesBlankFunctionsListViewTab.GetWnd();
							long r = ListView_GetSelectionMark(hList);
							lpSurfDlgMem->pSurfDoc->DeleteSurfaceBlankFunction(r);
						}
						
					}
					break;
				case IDC_BUTTON_GENERATE_BLANK_FUN:
					{
						if (IDYES == MessageBox(hDlg, 
							"�� ������������� ������ �������������\n"
							"����� ������� ����������� �� ���������\n"
							"� ����������� �� ������� ���������� ���������?\n\n"
							" ������ ���������, - ���� � ��� ��� ����\n"
							"�������������� ���� ������ ������� �����������,\n"
							"��������� ��������� ����� ��������\n"
							"��� ������ ��������� ���������", 
							"��������� ������ ������� �����������", MB_YESNO))
						{							
							if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc)
							{
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								for (vector<surface_order_list_item *>::iterator 
									it_param = GeoSurface::surface_order_list.begin();
									it_param != GeoSurface::surface_order_list.end(); it_param++)
								{
									if (*it_param)
									{
										long id_surf_param = (*it_param)->id_surf;
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
										for (vector<surface_order_list_item *>::iterator 
											it_obj = it_param + 1;
											it_obj != GeoSurface::surface_order_list.end(); 
										it_obj++)
										{
											if (*it_obj)
											{
												long id_surf_obj  = (*it_obj)->id_surf;
												BYTE id_blank_fun = 1;//BlankAbove
												lpSurfDlgMem->pSurfDoc->AddSurfaceBlankFunction(id_surf_obj, id_surf_param, id_blank_fun);
											}
										}
										//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@									
									}
								}
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							}
						}
					}
					break;
				case IDC_BUTTON_ADD_BLANK_FUN:
					{
						if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc) 
						{
							LRESULT lResult;
							lResult = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_OBJ, CB_GETCURSEL, 0, (LPARAM)0 );
							long id_surf_obj = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_OBJ, CB_GETITEMDATA, lResult, 0);

							lResult = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_PARAM, CB_GETCURSEL, 0, (LPARAM)0 );
							long id_surf_param = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_PARAM, CB_GETITEMDATA, lResult, 0);

							lResult = SendDlgItemMessage( hDlg, IDC_COMBO_BLANK_FUN, CB_GETCURSEL, 0, (LPARAM)0 );
							long id_blank_fun = SendDlgItemMessage( hDlg, IDC_COMBO_BLANK_FUN, CB_GETITEMDATA, lResult, 0);

							if (id_blank_fun > 0 && id_surf_obj != id_surf_param)
								lpSurfDlgMem->pSurfDoc->AddSurfaceBlankFunction(
								id_surf_obj, id_surf_param, id_blank_fun);


							//win_project* pwin_project = dynamic_cast<win_project*>(
							//lpSurfDlgMem->pSurfDoc);
							//if (pwin_project) pwin_project->UpdateAllViews();
						}
					}
					break;
				case IDC_BUTTON_SURF_AUTO_BLANKING:
					{
						if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc) 
						{
							lpSurfDlgMem->pSurfDoc->SurfacesAutoBlank();
							lpSurfDlgMem->pSurfDoc->ZoomView();
							lpSurfDlgMem->pSurfDoc->Draw();
							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(lpSurfDlgMem->hWnd,&rect);
							InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

							//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
							//if (pwin_project) pwin_project->UpdateAllViews();
						}
					}
					break;
				case IDC_BUTTON_NO_BLANK:
					{
						if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc) 
						{
							lpSurfDlgMem->pSurfDoc->NoBlank(false);
							lpSurfDlgMem->pSurfDoc->ZoomView();
							lpSurfDlgMem->pSurfDoc->Draw();
							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(lpSurfDlgMem->hWnd,&rect);
							InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

							//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
							//if (pwin_project) pwin_project->UpdateAllViews();
						}
					}
					break;
				case IDC_BUTTON_CUTTING:
					{
						lpSurfDlgMem->pSurfDoc->Cutting();
						//lpSurfDlgMem->pSurfDoc->ZoomView();
						//lpSurfDlgMem->pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						//RECT rect;
						//GetClientRect(lpSurfDlgMem->hWnd,&rect);
						//InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
					}
					break;

				}
			}
			break;

			
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}

LRESULT CALLBACK DlgProcLabExcludedList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static SurfDoc * pSurfDoc;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("DlgProcLabExcludedList WM_INITDIALOG hwnd %x\n", hwnd);
			pSurfDoc = (SurfDoc *)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (pSurfDoc)
			{
				if (pSurfDoc->m_LabExcludedListViewTab.Init(hwnd, (LPVOID)pSurfDoc, 0.00, 0.00, 0.00, 0.00, true))
				{
					hwndList = pSurfDoc->m_LabExcludedListViewTab.GetWnd();

					size_t cols = 7;
					pSurfDoc->m_LabExcludedListViewTab.SetCols(cols);

					for (vector<excluded_lab_trial>::iterator it = Laboratory::excluded_trials.begin();
						it != Laboratory::excluded_trials.end(); it++)
					{
						//printf("err\n");
						pSurfDoc->m_LabExcludedListViewTab.AddRow(LPARAM(0), &(*it).check_included);
						size_t r = pSurfDoc->m_LabExcludedListViewTab.Rows()-1;

						pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,0,(*it).vt.GetValueTypeString());
												
						sprintf(str, "%f\0", (*it).v);
						DeleteEndZeros(str);
						pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,1,str);

						
						pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,2,(*it).lab_layer_number);
						pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,3,(*it).labnumer_ID);

						switch((*it).m_mine_working_type)
						{
						case LabNumber::mine_working_type::hole:
							{
								pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,4,"����");
							}
							break;
						case LabNumber::mine_working_type::well:
							{
								pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,4,"���");
							}
							break;
						}

						pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,5,(*it).mine_working_number);
						
						sprintf(str, "%f\0", (*it).depth);
						DeleteEndZeros(str);
						pSurfDoc->m_LabExcludedListViewTab.SetItemString(r,6,str);
					}
				}
				// #############################################################
				// #############################################################
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(0, "��� ��������");
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(1, "��������");
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(2, "����� ���.����");
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(3, "���.�����");
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(4, "��� ���������");
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(5, "����� ���������");
				pSurfDoc->m_LabExcludedListViewTab.SetHeaderString(6, "������� �����");
			}
		}
		break;
#if !USE_LISTVIEW_STANDART_LXL 
		case WM_USER + 3:
			{
				if (pSurfDoc)
				{
					pSurfDoc->m_LabExcludedListViewTab.OnEndEdit();
					pSurfDoc->UpdateLabExcludedListNames();
/*					win_project* pwin_project = dynamic_cast<win_project*>(pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();*/
				}
			}
			break; 
#endif
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < pSurfDoc->m_LabExcludedListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
#if 0
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );
#endif
				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				pSurfDoc->m_LabExcludedListViewTab.UpdateView();
			}
			break;

		/*case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < Well_3D::wells_draw_list.size()) 
						{
							COLORREF color = Well_3D::wells_draw_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								Well_3D::wells_draw_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;

			}
			break;*/

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_LXL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (pSurfDoc)
					{
						pSurfDoc->m_LabExcludedListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_LabExcludedListViewTab.OnNotify(lParam))
						{
							//pwin_project->UpdateAllViews();
							pwin_project->m_laboratory.UpdateExcluded();
							pwin_project->m_laboratory.ReCreateContextWindow();
							//pwin_project->m_laboratory.ReDrawContextWindow();

						}
#if USE_LISTVIEW_STANDART_LXL 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hwnd, message, wParam, lParam);
			}
			break;
   }
   return 0;
}


WNDPROC wpOrigProcLabLayersList; 
WNDPROC wpOrigProcLabErrorsList; 
LRESULT CALLBACK DlgProcLabLayersList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			//printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.GetWnd();

					size_t cols = 4;
					lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetCols(cols);

					for (vector<LabLayer *>::iterator it = lpSurfDlgMem->pSurfDoc->m_laboratory.m_layers.begin();
						it != lpSurfDlgMem->pSurfDoc->m_laboratory.m_layers.end(); it++)
					{
						lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.AddRow(LPARAM(0), &(*it)->check_draw);
						size_t r = lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.Rows()-1;
						
						sprintf(str, "%s\0", (*it)->layer_number.c_str());
#if !CHAR_LAYER_NUMBER_ID
						OemToChar(str, str);						
#endif
						lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetItemString(r,0,str);

						sprintf(str, "%s\0", (*it)->ID.c_str());
#if !CHAR_LAYER_NUMBER_ID
						OemToChar(str, str);						
#endif
						lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetItemString(r,1,str);

						lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetItemString(r,2,(*it)->filename);

						sprintf(str, "%u", (*it)->lab_numbers.size());
						lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetItemString(r,3,str);
					}
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetHeaderString(0, "����� ���.����");
				lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetHeaderString(1, "ID ���.����");
				lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetHeaderString(2, "��� �����");
				lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.SetHeaderString(3, "�-�� ���.�������");
			}
		}
		break;
#if !USE_LISTVIEW_STANDART_LLL 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateLabLayersListNames();
/*					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();*/
				}
			}
			break; 
#endif
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.UpdateView();
			}
			break;

		/*case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < Well_3D::wells_draw_list.size()) 
						{
							COLORREF color = Well_3D::wells_draw_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								Well_3D::wells_draw_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;

			}
			break;*/

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_LLL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_LabLayersListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_LabLayersListViewTab.OnNotify(lParam))
							pwin_project->UpdateAllViews();
#if USE_LISTVIEW_STANDART_LLL 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hwnd, message, wParam, lParam);
			}
			break;
   }
   return CallWindowProc(wpOrigProcLabLayersList, hwnd, message, 
	   wParam, lParam);}

LRESULT CALLBACK DlgProcLabErrorsList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("DlgProcLabErrorsList WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00, false))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.GetWnd();

					size_t cols = 5;
					lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetCols(cols);

					for (vector<error_of_add_new_well_colomn_laboratory_analizes>::iterator it = lpSurfDlgMem->pSurfDoc->lab_errors.begin();
						it != lpSurfDlgMem->pSurfDoc->lab_errors.end(); it++)
					{
						//printf("err\n");
						lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.AddRow(LPARAM(0), NULL);
						size_t r = lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.Rows()-1;
						
						lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetItemString(r,0,(*it).lab_layer_number);
						lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetItemString(r,1,(*it).labnumer_ID);

						switch((*it).m_mine_working_type)
						{
						case LabNumber::mine_working_type::hole:
							{
								lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetItemString(r,2,"����");
							}
							break;
						case LabNumber::mine_working_type::well:
							{
								lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetItemString(r,2,"���");
							}
							break;
						}

						lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetItemString(r,3,(*it).mine_working_number);
						
						sprintf(str, "%f\0", (*it).depth);
						DeleteEndZeros(str);
						lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetItemString(r,4,str);
					}
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetHeaderString(0, "����� ���.����");
				lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetHeaderString(1, "���.�����");
				lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetHeaderString(2, "��� ���������");
				lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetHeaderString(3, "����� ���������");
				lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.SetHeaderString(4, "������� �����");
			}
		}
		break;
#if !USE_LISTVIEW_STANDART_LEL 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateLabErrorsListNames();
/*					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();*/
				}
			}
			break; 
#endif
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
#if 0
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );
#endif
				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.UpdateView();
			}
			break;

		/*case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < Well_3D::wells_draw_list.size()) 
						{
							COLORREF color = Well_3D::wells_draw_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								Well_3D::wells_draw_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;

			}
			break;*/

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_LEL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_LabErrorsListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_LabErrorsListViewTab.OnNotify(lParam))
							pwin_project->UpdateAllViews();
#if USE_LISTVIEW_STANDART_LEL 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hwnd, message, wParam, lParam);
			}
			break;
   }
   return CallWindowProc(wpOrigProcLabErrorsList, hwnd, message, 
	   wParam, lParam);}

LRESULT CALLBACK DlgProcLaboratoryLayersList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hWndLabLayersList   = NULL;
	static HWND hWndLabErrorsList   = NULL;
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				lpSurfDlgMem = (LPSURFDLGDATA)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				// Retrieve the handle to the Map control. 
				hWndLabLayersList = GetDlgItem(hDlg, IDC_STATIC_LAB_LAYERS_LIST); 

				// Subclass the picture control. 
				wpOrigProcLabLayersList = (WNDPROC) SetWindowLongPtr(hWndLabLayersList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcLabLayersList); 

				SendMessage(hWndLabLayersList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################		
				hWndLabErrorsList = GetDlgItem(hDlg, IDC_STATIC_LAB_ERRORS); 

				// Subclass the picture control. 
				wpOrigProcLabErrorsList = (WNDPROC) SetWindowLongPtr(hWndLabErrorsList, 
					GWLP_WNDPROC, (LONG_PTR) DlgProcLabErrorsList); 

				SendMessage(hWndLabErrorsList, WM_INITDIALOG, wParam, lParam);
				// #############################################################
				// #############################################################				
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}

LRESULT CALLBACK DlgProcShtampDefKModul(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				lpSurfDlgMem = (LPSURFDLGDATA)lParam;
				//**************************************
				CheckDlgButton( hDlg, IDC_CHECK_DEF_MODUL_NEW_RASCHETN,
					
					LabLayer::DefModuleNewRaschotnMethod ? BST_CHECKED : BST_UNCHECKED );

/*				switch (CompressionLabTrialResults::algorithm)
				{
				case 1:
					CheckRadioButton( hDlg,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG1,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG4,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG1);
					break;
				case 2:
					CheckRadioButton( hDlg,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG1,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG4,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG2);
					break;
				case 3:
					CheckRadioButton( hDlg,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG1,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG4,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG3);
					break;
				case 4:
					CheckRadioButton( hDlg,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG1,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG4,
						IDC_RADIO__SHTAMP_DEF_MODUL_ALG4);
					break;
				}*/
			}
			break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
			
		case IDC_CHECK_DEF_MODUL_NEW_RASCHETN:
			{
				LabLayer::DefModuleNewRaschotnMethod = IsDlgButtonChecked( hDlg, IDC_CHECK_DEF_MODUL_NEW_RASCHETN) == BST_CHECKED;
				if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc) lpSurfDlgMem->pSurfDoc->m_laboratory.ReCreateContextWindow();
			}
			break;
		/*case IDC_RADIO__SHTAMP_DEF_MODUL_ALG1:
			{
				CompressionLabTrialResults::algorithm = 1;
			}
			break;
		case IDC_RADIO__SHTAMP_DEF_MODUL_ALG2:
			{
				CompressionLabTrialResults::algorithm = 2;
			}
			break;
		case IDC_RADIO__SHTAMP_DEF_MODUL_ALG3:
			{
				CompressionLabTrialResults::algorithm = 3;
			}
			break;		
		case IDC_RADIO__SHTAMP_DEF_MODUL_ALG4:
			{
				CompressionLabTrialResults::algorithm = 4;
			}
			break;*/
		}
		break;
	case WM_CLOSE:
		{
			return DefWindowProc(hDlg, message, wParam, lParam);
		}
		break;
	default :
		return( FALSE );
   }
   return 0;
}


LRESULT CALLBACK DlgProcSurfKarotazhInterpolation( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int index;
	static double minx, miny, minz, maxx, maxy, maxz;
	static int InterpolateKarotazhCubeMethod = 1;
	static Karotazh::linterp_method int_meth;
	static bool to_extrapolate_down = false;
	static karotazh_extrapolate_down ked;

	static bool to_blank_with_Triangulation_Contour = false;
	static bool use_biss = false;
	static bool to_blank_with_loaded_Contour = false;

	static long griddata_app = 0;
	static long griddata_fun_number = 0;


	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			index = -1;

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_INITIAL_PARAMETERS,0);
		
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select karotazh");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
							it != Well_3D::karotazh_list.end(); it++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)(*it).name.c_str());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_SETCURSEL,
				index+1, (LPARAM)0 );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_INITIAL_PARAMETERS:
			{
				char str[1023];
				sprintf(str,"%d",Karotazh::slices);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES, str);

				sprintf(str,"%d",Karotazh::stacks);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS, str);	

				sprintf(str,"%d",Karotazh::s_alpha);
				SetDlgItemText(hDlg, IDC_EDIT_KAROTAZH_ALPHA, str);

				sprintf(str,"%lf",Karotazh::s_scale);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE, str);

				sprintf(str,"%lf",Karotazh::s_scale_2d);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE2, str);


				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_LOGARITHMIC,
					Karotazh::s_logarithmic_scale ? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_FROM_ZERO,
					Karotazh::s_scale_from_zero? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_ON_OFF,
					Karotazh::s_checked? BST_CHECKED : BST_UNCHECKED );
			}
			break;
		case IDC_COMBO_SELECT_KAROTAZH:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				lpSurfDlgMem->pSurfDoc->GetKarotazhCube(index, minx, miny, minz, maxx, maxy, maxz);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_INITIAL_PARAMETERS,0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_BUTTON_SAVE_AS_DAT:
			{
				lpSurfDlgMem->pSurfDoc->KarotazhSaveAsDat(index);
			}
			break;
		case IDC_RADIO_KAROTAZH_INTERPOLATION_METHOD1:
			{
				InterpolateKarotazhCubeMethod = 1;
				bool to_show = true;
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_GRIDDATA_APPLICATION), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_1), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_2), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_3), to_show);	
				//ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_4), to_show);	
				//ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_5), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_EDIT_VARIOGRAM), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_GRIDDATA_FUN), to_show);	
			}
			break;
		case IDC_RADIO_KAROTAZH_INTERPOLATION_METHOD2:
			{
				InterpolateKarotazhCubeMethod = 3;
				bool to_show = false;
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_GRIDDATA_APPLICATION), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_1), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_2), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_3), to_show);	
				//ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_4), to_show);	
				//ShowWindow(GetDlgItem(hDlg,IDC_RADIO_GRIDDATA_APPLICATION_5), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_EDIT_VARIOGRAM), to_show);	
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_GRIDDATA_FUN), to_show);	
			}
			break;
		case IDC_RADIO_LIN_INT_METHOD1:
			{
				int_meth = Karotazh::linterp_method::linear;
			}
			break;
		case IDC_RADIO_LIN_INT_METHOD2:
			{
				int_meth = Karotazh::linterp_method::spline;
			}
			break;

		case IDC_CHECK_KAROTAZH_INTERPOLATION_DOWN:
			{
				to_extrapolate_down = IsDlgButtonChecked( hDlg, IDC_CHECK_KAROTAZH_INTERPOLATION_DOWN) == BST_CHECKED;
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_KAROTAZH_INTERPOLATION_DOWN_METHOD), to_extrapolate_down);				
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_KAROTAZH_INTERPOLATION_DOWN_METHOD0), to_extrapolate_down);				
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_KAROTAZH_INTERPOLATION_DOWN_METHOD1), to_extrapolate_down);				
				ShowWindow(GetDlgItem(hDlg,IDC_RADIO_KAROTAZH_INTERPOLATION_DOWN_METHOD2), to_extrapolate_down);	
				EnableWindow(GetDlgItem(hDlg,IDC_EDIT_KAROTAZH_INTERPOLATION_DOWN_LEN), to_extrapolate_down);	
			}
			break;
		case IDC_RADIO_KAROTAZH_INTERPOLATION_DOWN_METHOD0:
			{
				ked.m_extrapolate_down_method = karotazh_extrapolate_down::extrapolate_down_method::none;
			}
			break;
		case IDC_RADIO_KAROTAZH_INTERPOLATION_DOWN_METHOD1:
			{
				ked.m_extrapolate_down_method = karotazh_extrapolate_down::extrapolate_down_method::with_lowest_value;
			}
			break;
		case IDC_RADIO_KAROTAZH_INTERPOLATION_DOWN_METHOD2:
			{
				ked.m_extrapolate_down_method = karotazh_extrapolate_down::extrapolate_down_method::continue_interpolation;
			}
			break;

		case IDC_CHECK_TO_BLANK_WITH_TRIANGULATION_CONTOUR:
			{
				to_blank_with_Triangulation_Contour = IsDlgButtonChecked( hDlg, IDC_CHECK_TO_BLANK_WITH_TRIANGULATION_CONTOUR) == BST_CHECKED;

				ShowWindow(GetDlgItem(hDlg,IDC_CHECK2_USE_BISS), to_blank_with_Triangulation_Contour);	
				ShowWindow(GetDlgItem(hDlg,IDC_EDIT_BISS_LEN), to_blank_with_Triangulation_Contour);	
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_BISS_LEN), to_blank_with_Triangulation_Contour);	

				ShowWindow(GetDlgItem(hDlg,IDC_CHECK_TO_BLANK_WITH_LOADED_CONTOUR), !to_blank_with_Triangulation_Contour);	
			}
			break;

		case IDC_CHECK2_USE_BISS:
			{
				use_biss = IsDlgButtonChecked( hDlg, IDC_CHECK2_USE_BISS) == BST_CHECKED;
                EnableWindow(GetDlgItem(hDlg,IDC_EDIT_BISS_LEN), use_biss);
			}
			break;

		case IDC_CHECK_TO_BLANK_WITH_LOADED_CONTOUR:
			{
				to_blank_with_loaded_Contour = IsDlgButtonChecked( hDlg, IDC_CHECK_TO_BLANK_WITH_LOADED_CONTOUR) == BST_CHECKED;
			}
			break;



		case IDC_RADIO_GRIDDATA_APPLICATION_1:
		case IDC_RADIO_GRIDDATA_APPLICATION_2:
		case IDC_RADIO_GRIDDATA_APPLICATION_3:
			{
				//if (dlg)
				//	dlg->RadioButtonHandler(hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, wmId);
				//	void griddata_dialog::RadioButtonHandler(HWND hDlg, int id_group, int id)
				//	{
				//		this->m_griddata_application = griddata_dialog::griddata_application(griddata_dialog::griddata_application::gstat_dll + id - id_group);
				griddata_app = 1 + LOWORD( wParam ) - IDC_RADIO_GRIDDATA_APPLICATION_1;
				//      this->InitGriddataDialog(hDlg, false);
				switch( LOWORD( wParam ) )
				{
				//case griddata_dialog::griddata_application::unknown:
				//	//this->InitDialog_unk(hDlg);
				//	break;
				//case griddata_dialog::griddata_application::gstat_dll:
				case IDC_RADIO_GRIDDATA_APPLICATION_1:
					{
						//if (first_time) CheckRadioButton( hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, IDC_RADIO_GRIDDATA_APPLICATION_5, IDC_RADIO_GRIDDATA_APPLICATION_1);
						//this->InitDialog_gstat(hDlg);
						griddata_fun_number = 1;
						//**************************************
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_RESETCONTENT, 0, (LPARAM)0);
							
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"method:  gs; # Gaussian simulation instead of kriging");
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"blocksize: dx=40, dy=40;# 40 $times$ 40 block averages");
					}
					break;
				//case griddata_dialog::griddata_application::surfer_ole:
				case IDC_RADIO_GRIDDATA_APPLICATION_2:
					{
						//if (first_time) CheckRadioButton( hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, IDC_RADIO_GRIDDATA_APPLICATION_5, IDC_RADIO_GRIDDATA_APPLICATION_2);
						//this->InitDialog_surfer(hDlg);
						griddata_fun_number = 1;
						//**************************************
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_RESETCONTENT, 0, (LPARAM)0);

						for (enum SrfGridAlgorithm alg = srfInverseDistance;
							alg <= srfLocalPolynomial; alg++)
						{
							SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
									(LPARAM)(LPCTSTR)SrfGridAlgorithm_toStr(alg));
						}

						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_SETCURSEL, griddata_fun_number, (LPARAM)0);
					}
					break;
				//case griddata_dialog::griddata_application::this_app:
				case IDC_RADIO_GRIDDATA_APPLICATION_3:
					{
						//if (first_time) CheckRadioButton( hDlg, IDC_RADIO_GRIDDATA_APPLICATION_1, IDC_RADIO_GRIDDATA_APPLICATION_5, IDC_RADIO_GRIDDATA_APPLICATION_3);
						//this->InitDialog_my(hDlg);
						griddata_fun_number = -1;
						//**************************************
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_RESETCONTENT, 0, (LPARAM)0);
							
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"0 - griddata_v4");
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"1 - griddata_v4 with GreenFun");
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"2 - griddata_2 with GreenFun dist_fun");
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"3 - griddata_3 with triangulation and interpolation with default parameters");
						SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)"4 - griddata_3 with triangulation and interpolation with default parameters use contour");
					//	SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_ADDSTRING, 0,
					//			(LPARAM)(LPCTSTR)"5 - griddata_3 with triangulation and interpolation");					
					}
					break;
				}
			}
			break;
		case IDC_COMBO_GRIDDATA_FUN:
			{
				//if (dlg)
				//	dlg->GridDataFunComboHandler(hDlg);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				griddata_fun_number = (int)SendDlgItemMessage( hDlg, IDC_COMBO_GRIDDATA_FUN, CB_GETCURSEL,
					0,(LPARAM)0 );		
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}
			break;


		case IDOK :
			{
				if (lpSurfDlgMem && lpSurfDlgMem->pSurfDoc)
				{
					if (!lpSurfDlgMem->pSurfDoc->m_cube_size.Defined())
					{
						//lpSurfDlgMem->pSurfDoc->m_cube_size.Define(minx, miny, minz, maxx, maxy, maxz);
						AfxMessageBox("���������� ������� ����������� ����");
						return 0;
					}
					else
					{
						bool divide_cube_on_1_25 = IsDlgButtonChecked( hDlg, IDC_CHECK_DIVIDE_CUBE_ON_1_25) == BST_CHECKED;
						bool filter_grid_min_max_cube_2d = IsDlgButtonChecked( hDlg, IDC_CHECK_FILTER_GRID_MIN_MAX_CUBE_2D) == BST_CHECKED;
						bool filter_grid_min_max_cube_3d = IsDlgButtonChecked( hDlg, IDC_CHECK_FILTER_GRID_MIN_MAX_CUBE_3D) == BST_CHECKED;
						ked.to_extrapolate_down = to_extrapolate_down;
						if (to_extrapolate_down)
						{
							char str[128];
							GetDlgItemText(hDlg, IDC_EDIT_KAROTAZH_INTERPOLATION_DOWN_LEN, str, 127);
							ked.extrapolation_len = atof(str);
						}		

						double len_biss = 0.0;
						if (to_blank_with_Triangulation_Contour)
						{
							char str[128];
							GetDlgItemText(hDlg, IDC_EDIT_BISS_LEN, str, 127);
							len_biss = atof(str);
						}




						switch(InterpolateKarotazhCubeMethod)
						{
						case 1:
							lpSurfDlgMem->pSurfDoc->InterpolateKarotazhCube(index, 
								divide_cube_on_1_25, int_meth, ked, 
								griddata_app, griddata_fun_number, 
								filter_grid_min_max_cube_2d, filter_grid_min_max_cube_3d,
								to_blank_with_Triangulation_Contour, use_biss, len_biss,
								to_blank_with_loaded_Contour
								);//, minx, miny, minz, maxx, maxy, maxz, dx, dy, dz);
							break;
						case 3:
							lpSurfDlgMem->pSurfDoc->InterpolateKarotazhCube3(index);//, minx, miny, minz, maxx, maxy, maxz, dx, dy, dz);
							break;
						}

						// init of zoomCoefZ_XY
						lpSurfDlgMem->pSurfDoc->ZoomView();
						//lpSurfDlgMem->pSurfDoc->Zoom(lpSurfDlgMem->pSurfDoc->m_drills);
						lpSurfDlgMem->pSurfDoc->Draw();
						//ReDrawDrills(lpSurfDlgMem->pSurfDoc);

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(lpSurfDlgMem->hWnd,&rect);
						InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
					}
				}

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

LRESULT CALLBACK DlgProcSaveBitmap( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static HWND hWnd;
	static bool save_screen;
	static long width, height;
	static double proportion;
	static bool constant_proportions, update_edits;
	static char str[128];

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			hWnd = (HWND)lParam;
			update_edits = true;

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			glReadBuffer(GL_BACK); //  designate buffer to read
			int vp[4];
			glGetIntegerv(GL_VIEWPORT, vp);
			width=vp[2];
			height=vp[3];
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	
			sprintf(str, "%d\0", width);
			SetDlgItemText(hDlg,IDC_EDIT_BITMAP_WIDTH, str);
			sprintf(str, "%d\0", height);
			SetDlgItemText(hDlg,IDC_EDIT_BITMAP_HEIGHT, str);

			proportion = double (width) / double(height);

			printf ("proportion = %f", proportion);

			//IDC_CHECK_CONSTANT_PROPORTIONS
			constant_proportions = false;

			save_screen = false;
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_EDIT_BITMAP_WIDTH:
			{
				//printf("IDC_EDIT_CUBE_SIZE_NLINES_X HIWORD( wParam ) = %d\n", HIWORD( wParam ));

				if (constant_proportions && update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_BITMAP_WIDTH, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						width = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CALC_H, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_FILL_H, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_BITMAP_HEIGHT:
			{
				if (constant_proportions && update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_BITMAP_HEIGHT, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						height = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CALC_W, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_FILL_W, 0), 0);
					}
				}
			}
			break;

		case IDC_BUTTON_CALC_W:
			{
				width = proportion * height;
			}
			break;
		case IDC_BUTTON_CALC_H:
			{
				height = double (width) / proportion;
			}
			break;
		case IDC_BUTTON_FILL_H:
			{
				update_edits = false;
				sprintf(str, "%d", height);
				SetDlgItemText(hDlg, IDC_EDIT_BITMAP_HEIGHT, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_FILL_W:
			{
				update_edits = false;
				sprintf(str, "%d", width);
				SetDlgItemText(hDlg, IDC_EDIT_BITMAP_WIDTH, str);
				update_edits = true;
			}
			break;		

		case IDC_CHECK_CONSTANT_PROPORTIONS:
			{
				constant_proportions = IsDlgButtonChecked( hDlg, IDC_CHECK_CONSTANT_PROPORTIONS) == BST_CHECKED;
				if (constant_proportions)
					proportion = double (width) / double(height);
			}
			break;

		case IDC_CHECK_SAVE_BITMAP_AS_SCREEN:
			{
				save_screen = IsDlgButtonChecked( hDlg, IDC_CHECK_SAVE_BITMAP_AS_SCREEN) == BST_CHECKED;
			}
			break;

		case IDOK :
			{
				char fn[4098];	fn[0] = '\0';
				DWORD nFilterIndex = 0;
				if (SaveFileDlg(hWnd, fn, "Bitmap (*.bmp)\0*.bmp\0All files \0*.*\0", nFilterIndex) == S_OK)
				{
					if (save_screen)
					{
						//Save Screen 					  
						//CGLPrintMan print;					  
						// save
						print.SaveBitmap(fn);
					}
					else
					{

						// ###########################################################
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						// ###########################################################
						if (woglv) 
						{
							//long width  = paper.right - paper.left;
							//long height = paper.bottom - paper.top;

							GetDlgItemText(hDlg,IDC_EDIT_BITMAP_WIDTH, str, 127);
							width  = atoi(str);
							GetDlgItemText(hDlg,IDC_EDIT_BITMAP_HEIGHT, str, 127);
							height = atoi(str);

								//����� ������ �������
							RECT paper;
							paper.left		= 0;
							paper.top		= 0;
							paper.right		= paper.left + width;
							paper.bottom	= paper.top  + height;

							print.toEnableOpenGL	= true;
							print.toReDraw		= true;
							print.toDisableOpenGL	= true;
							  
							  
							//CGLPrintMan print;//������ - ��������
							// ����� ������:
							// 1) ������ ��������� ������� ��� ���������
							// 2) �������� ���������� ������, ����������� � �����
							//	��������� �������� ���������� ������, � ������ ������������
							// 3) ������� ���������� OpenGL, ������� ����� ������ � ������
							print.EnableOpenGL(paper, hWnd, &print.m_hDC, &print.m_hRC);
							// ��������� ������ ��� ������ ��������� ���� � ���������� OpenGL
							// �������� ������� ���������� OpenGL (3) � �������� �������� ��� 
							// �������� ���������� ������ (2), 
							// ������� � ���� ������� ��� ������ � ������ (1)
							print.StartUpdate();
							UseGLFont( print.m_hDC,  &lf_Label);

							// ������ �� ����������� ����� �������� ���������� OpenGL 
							// ������� ����� �������� � ������ ������� print
							  
							SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG2, 0);
							glDrawBuffer(GL_FRONT);
							  

							if (print.toReDraw)
							{
								project * prj = woglv->GetProject();
								SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
								//pSurfDoc->ZoomView();
								//====== ������������ ������ �������� ������
								pSurfDoc->Draw();
							}

							// Set new size of viwport as picture's paper size
							woglv->SetSize(width,height);

							woglv->ExposeEvent();

							// Restore size of viwport as window size
							woglv->ConfigureHandler(hWnd);
						}
						  
						// save
						print.SaveBitmap2(fn);
						print.DisableOpenGL(hWnd, print.m_hDC, print.m_hRC);
						// ������������ ������ ��������� OpenGL
						print.EndUpdate();

					}
				}
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
LRESULT CALLBACK DlgProcSurfKarotazhProjection( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int index_kar;
	static int index_cub;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
//			nx = ny = nz = 50;
			index_kar = -1;
			index_cub = -1;

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

		
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select karotazh");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (vector<karotazh_list_item>::iterator it = Well_3D::karotazh_list.begin();
							it != Well_3D::karotazh_list.end(); it++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)(*it).name.c_str());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_SETCURSEL,
				index_kar+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_SETCURSEL,
				index_cub+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_COMBO_SELECT_KAROTAZH:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_kar = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_KAROTAZH, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_SELECT_CUBE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDOK :
			{
				if (index_kar < 0)
				{
					printf("index_kar(%d) < 0\n", index_kar);
					return FALSE;
				}
				if (index_cub < 0)
				{
					printf("index_cub(%d) < 0\n", index_cub);
					return FALSE;
				}

				lpSurfDlgMem->pSurfDoc->ProjectionKarotazhCube(index_kar, index_cub);


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

LRESULT CALLBACK DlgProcWellsLabDrawMode( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
//			nx = ny = nz = 50;

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

		
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select lab draw mode");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (Well_Laboratory_Analize::label_type lt = Well_Laboratory_Analize::label_type(Well_Laboratory_Analize::label_type::undefined_label_type + 1);
				lt != Well_Laboratory_Analize::label_type::end; lt++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)Well_Laboratory_Analize::LabelTypeToString(lt));
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_SETCURSEL,
				WPARAM(Well_Laboratory_Analize::s_label_type), (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_COMBO_LAB_DRAW_MODE:
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					Well_Laboratory_Analize::s_label_type = Well_Laboratory_Analize::label_type
						(SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_GETCURSEL, 0,(LPARAM)0 ));
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		

					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break;
		case IDOK :
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
LRESULT CALLBACK DlgProcStatZondSvai( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
//			nx = ny = nz = 50;

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

		
			switch(Well_3D::zab_svai_id_snip)
			{
			case 1:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_SNIP_1,
						IDC_RADIO_SNIP_2,
						IDC_RADIO_SNIP_1);
				}
				break;			
			case 2:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_SNIP_1,
						IDC_RADIO_SNIP_2,
						IDC_RADIO_SNIP_2);
				}
				break;
			}


		/*
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select lab draw mode");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			for (Well_Laboratory_Analize::label_type lt = Well_Laboratory_Analize::label_type(Well_Laboratory_Analize::label_type::undefined_label_type + 1);
				lt != Well_Laboratory_Analize::label_type::end; lt++)
			{
				SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_ADDSTRING, 0,
					(LPARAM)(LPCTSTR)Well_Laboratory_Analize::LabelTypeToString(lt));
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_SETCURSEL,
				WPARAM(Well_Laboratory_Analize::s_label_type), (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_RADIO_SNIP_1:
			{
				Well_3D::zab_svai_id_snip = 1;
			}
			break;
		case IDC_RADIO_SNIP_2:
			{
				Well_3D::zab_svai_id_snip = 2;
			}
			break;
			/*case IDC_COMBO_LAB_DRAW_MODE:
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					Well_Laboratory_Analize::s_label_type = Well_Laboratory_Analize::label_type
						(SendDlgItemMessage( hDlg, IDC_COMBO_LAB_DRAW_MODE, CB_GETCURSEL, 0,(LPARAM)0 ));
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@		

					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break;*/
		case IDOK :
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
BOOL CALLBACK DlgProcSavingOfCubeProjectionGrid( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int index_cub;

	static int make_grids_vnahljost;
	static bool convert_to_acad_yscale;
	static bool non_stretched_xscale;

	static char dir[4096];

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			GetCurrentDirectory(4098, dir);
			SetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir);

			index_cub = -1;

			make_grids_vnahljost = true;
			convert_to_acad_yscale = false;
			non_stretched_xscale = true;

			CheckRadioButton( hDlg,
				IDC_RADIO_NAHLJOST_0,
				IDC_RADIO_NAHLJOST_2,
				IDC_RADIO_NAHLJOST_1);

			CheckDlgButton(hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE,	convert_to_acad_yscale);
			CheckDlgButton(hDlg, IDC_CHECK_NON_STRETCHED_X_SCALE,	non_stretched_xscale);

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

			ShowWindow(GetDlgItem(hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE), lpSurfDlgMem->pSurfDoc->GetAcadYscaleLoaded());

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_INITIAL_PARAMETERS,0);
		
		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_SETCURSEL,
				index_cub+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		/*case IDC_BUTTON_LOAD_ACAD_Y_SCALE:
			{
				char lpstrFile[4096];
				lpstrFile[0] = '\0';
				if (OpenFileDlg(hDlg, "Y Scale (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
				{	
					vdouble xAcadYscale,yAcadYscale;
					int _inside;
					if (ReadBlnFile( lpstrFile, xAcadYscale, yAcadYscale, _inside ) == 0)
					{
						char str[255];
						sprintf(str, "%d yscale points\n",  xAcadYscale.Length(), yAcadYscale.Length());
						//MessageBox(0, str, "", 0);
						//SetDlgItemText(hDlg, IDC_STATIC_ACAD_YSCALE, str);
						printf(str);

						if (xAcadYscale.Length() == 2 && yAcadYscale.Length() == 2)
						{
							double z1w = xAcadYscale(0), y1a = yAcadYscale(0);
							double z2w = xAcadYscale(1), y2a = yAcadYscale(1);
							me->SetAcadYscale(z1w, y1a, z2w, y2a);
							ShowWindow(GetDlgItem(hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE), me->GetVcadYscaleLoaded());
						}
					}
				}
			}
			break;*/
		case IDC_RADIO_NAHLJOST_0:
			{
				make_grids_vnahljost = 0;
			}
			break;
		case IDC_RADIO_NAHLJOST_1:
			{
				make_grids_vnahljost = 1;
			}
			break;
		case IDC_RADIO_NAHLJOST_2:
			{
				make_grids_vnahljost = 2;
			}
			break;
		case IDC_CHECK_CONVERT_TO_ACAD_YSCALE:
			{
				convert_to_acad_yscale = IsDlgButtonChecked( hDlg, IDC_CHECK_CONVERT_TO_ACAD_YSCALE) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_NON_STRETCHED_X_SCALE:
			{
				non_stretched_xscale = IsDlgButtonChecked( hDlg, IDC_CHECK_NON_STRETCHED_X_SCALE) == BST_CHECKED;
			}
			break;
		case IDC_INIT_INITIAL_PARAMETERS:
			{
				/*char str[1023];
				sprintf(str,"%d",Karotazh::slices);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_SLICES, str);

				sprintf(str,"%d",Karotazh::stacks);
				SetDlgItemText(hDlg, IDC_EDIT_SPHERE_STACKS, str);	

				sprintf(str,"%d",Karotazh::s_alpha);
				SetDlgItemText(hDlg, IDC_EDIT_KAROTAZH_ALPHA, str);

				sprintf(str,"%lf",Karotazh::s_scale);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_SPHERE_RADIUS_VALUE, str);


				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_LOGARITHMIC,
					Karotazh::s_logarithmic_scale ? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_SCALE_FROM_ZERO,
					Karotazh::s_scale_from_zero? BST_CHECKED : BST_UNCHECKED );

				CheckDlgButton( hDlg, IDC_CHECK_KAROTAZH_ON_OFF,
					Karotazh::s_checked? BST_CHECKED : BST_UNCHECKED );*/
			}
			break;

		case IDC_COMBO_SELECT_CUBE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_BUTTON_BROSE_DIRECTORY:
			{
				GetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir, 4097);
				if (BroseDirDlg(hDlg, dir))
				{
					SetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir);
				}
			}
			break;
		case IDOK :
			{
				Cube4D * cube = NULL;
				int index_c = -1;
				if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
				{
					do
					{
						index_c++;
						if (index_c == index_cub)
						{
							cube = &lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg();
							break;
						}
					}
					while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
				}
				
				if(cube)
				{
					char cubename[4096];
					char * pcub = SelectNameFromPath(cube->GetName().c_str(), cubename, 4096);

					GetDlgItemText(hDlg, IDC_EDIT_DIRECTORY, dir, 4097);

					char dir_out[4098];
					sprintf(dir_out, "%s\\%s\0", dir, pcub);
					CreateDirectory(dir_out, NULL);
					
					lpSurfDlgMem->pSurfDoc->SavingOfCubeProjectionGrid(dir_out, index_cub, make_grids_vnahljost, convert_to_acad_yscale, non_stretched_xscale);
				}
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
BOOL CALLBACK DlgProcProfilesCoordinateGrid( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static double minx, miny, minz, maxx, maxy, maxz;
	static double dx, dy, dz;
	static long nx,ny,nz;
	static char str[4098];
	//static int index_cub;

	static bool update_edits;


	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			update_edits = false;
			SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_DEFAULT, 0), 0);

			//CheckDlgButton(hDlg, IDC_CHECK_NORTH_COORDINATE_PRIORITY, BlnProfilePlane3D::noth_vertical_coordinate_priorirty);
			CheckDlgButton(hDlg, IDC_CHECK_Z_DIRECTION, BlnProfilePlane3D::to_draw_gorizontal);
			CheckDlgButton(hDlg, IDC_CHECK_X_DIRECTION, BlnProfilePlane3D::to_draw_x_vertical);
			CheckDlgButton(hDlg, IDC_CHECK_Y_DIRECTION, BlnProfilePlane3D::to_draw_y_vertical);
			CheckDlgButton(hDlg, IDC_CHECK_USE_GRID_ON_PLANE, BlnProfilePlane3D::use_grid_on_plane);
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_EDIT_CUBE_SIZE_NLINES_X:
			{
				printf("IDC_EDIT_CUBE_SIZE_NLINES_X HIWORD( wParam ) = %d\n", HIWORD( wParam ));

				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						nx = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_NLINES_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						ny = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_NLINES_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						nz = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_SPACING_X:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						dx = atof(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_SPACING_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						dy = atof(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_SPACING_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						dz = atof(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MIN_X:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						minx = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MIN_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						miny = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MIN_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						minz = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MAX_X:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						maxx = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MAX_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						maxy = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MAX_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						maxz = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_CALC_NLINES:
			{
				nx = (long)(maxx-minx)/dx + 1;
				ny = (long)(maxy-miny)/dy + 1;
				nz = (long)(maxz-minz)/dz + 1;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_CALC_SPACING:
			{
				dx = (maxx - minx) / (nx - 1);
				dy = (maxy - miny) / (ny - 1);
				dz = (maxz - minz) / (nz - 1);
			}
			break;			
		case IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS:
			{
				update_edits = false;
				sprintf(str, "%f", minx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_X, str);
				sprintf(str, "%f", miny);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Y, str);
				sprintf(str, "%f", minz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS:
			{
				update_edits = false;
				sprintf(str, "%f", maxx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_X, str);
				sprintf(str, "%f", maxy);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Y, str);
				sprintf(str, "%f", maxz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_FILL_NLINES:
			{			
				update_edits = false;
				sprintf(str, "%ld", nx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_X, str);
				sprintf(str, "%ld", ny);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Y, str);
				sprintf(str, "%ld", nz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_FILL_SPACING:
			{
				update_edits = false;
				sprintf(str, "%f", dx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_X, str);
				sprintf(str, "%f", dy);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Y, str);
				sprintf(str, "%f", dz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Z, str);
				update_edits = true;
			}
			break;

		case IDC_BUTTON_CUBE_SIZE_DEFAULT:
			{				
				minx = floor(lpSurfDlgMem->pSurfDoc->m_xd_min);
				miny = floor(lpSurfDlgMem->pSurfDoc->m_yd_min);
				minz = floor(lpSurfDlgMem->pSurfDoc->m_zd_min);
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);

				maxx = ceil(lpSurfDlgMem->pSurfDoc->m_xd_max);
				maxy = ceil(lpSurfDlgMem->pSurfDoc->m_yd_max);
				maxz = ceil(lpSurfDlgMem->pSurfDoc->m_zd_max);
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
				
				dx = 10;
				dy = 10;
				dz = 1;
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);

				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
			

				//SetDlgItemText(hDlg, IDC_EDITCUBE_SIZE_EXTRACT, "0.0");
			}
			break;
		case IDC_CHECK_USE_GRID_ON_PLANE:
		case IDC_CHECK_NORTH_COORDINATE_PRIORITY:
		case IDC_CHECK_X_DIRECTION:
		case IDC_CHECK_Y_DIRECTION:
		case IDC_CHECK_Z_DIRECTION:
		case IDOK :
			{ 
#if 0
				BlnProfilePlane3D::noth_vertical_coordinate_priorirty = 
					IsDlgButtonChecked( hDlg, 
					IDC_CHECK_NORTH_COORDINATE_PRIORITY) == BST_CHECKED;
#endif
				BlnProfilePlane3D::to_draw_x_vertical = 
					IsDlgButtonChecked( hDlg, 
					IDC_CHECK_X_DIRECTION) == BST_CHECKED;

				BlnProfilePlane3D::to_draw_y_vertical = 
					IsDlgButtonChecked( hDlg, 
					IDC_CHECK_Y_DIRECTION) == BST_CHECKED;

				BlnProfilePlane3D::to_draw_gorizontal = 
					IsDlgButtonChecked( hDlg, 
					IDC_CHECK_Z_DIRECTION) == BST_CHECKED;

				BlnProfilePlane3D::first_x	= minx;
				BlnProfilePlane3D::step_x	= dx;
				BlnProfilePlane3D::last_x	= maxx;

				BlnProfilePlane3D::first_y	= miny;
				BlnProfilePlane3D::step_y	= dy; 
				BlnProfilePlane3D::last_y	= maxy;

				BlnProfilePlane3D::first_z	= minz;
				BlnProfilePlane3D::step_z	= dz; 
				BlnProfilePlane3D::last_z	= maxz;

				BlnProfilePlane3D::use_grid_on_plane = 
					IsDlgButtonChecked( hDlg, 
					IDC_CHECK_USE_GRID_ON_PLANE) == BST_CHECKED;




				if(lpSurfDlgMem->pSurfDoc->m_bln_profiles.SetCurrentMsgOnFirst())
				{
					do
					{
						lpSurfDlgMem->pSurfDoc->m_bln_profiles.GetCurrentMsg().m_plane.ReDraw();
					}
					while(lpSurfDlgMem->pSurfDoc->m_bln_profiles.IncrementCurrentMsg());
				}
				lpSurfDlgMem->pSurfDoc->UpdateAllViews();



			}
			break;

		case IDC_BUTTON_CUBE_SIZE_PRINTF:
			{
				lpSurfDlgMem->pSurfDoc->m_cube_size.Printf();
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



BOOL CALLBACK DlgProcCubeSize( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static double minx, miny, minz, maxx, maxy, maxz;
	static double dx, dy, dz;
	static long nx,ny,nz;
	static char str[4098];
	static int index_cub;

	static bool update_edits;


	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			update_edits = false;
			SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_DEFAULT, 0), 0);
			
			index_cub = -1;
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_SIZE_CUBE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_SIZE_CUBE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_SIZE_CUBE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_SIZE_CUBE, CB_SETCURSEL,
				index_cub+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_BUTTON_CUBE_SIZE_BY_CUBE:
			{
				if (index_cub > -1)
				{
					Cube4D * cube = lpSurfDlgMem->pSurfDoc->FindCube(index_cub);
					if (cube) 
					{
						minx = cube->lattice.grid4Section.xLL;
						miny = cube->lattice.grid4Section.yLL;
						minz = cube->lattice.grid4Section.zLL;
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);

					
						nx = cube->lattice.grid4Section.nCol;
						ny = cube->lattice.grid4Section.nRow;
						nz = cube->lattice.grid4Section.nPag;
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);

						dx = cube->lattice.grid4Section.xSize;
						dy = cube->lattice.grid4Section.ySize;
						dz = cube->lattice.grid4Section.zSize;
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
						
						maxx = minx + dx * (nx - 1);
						maxy = miny + dy * (ny - 1);
						maxz = minz + dz * (nz - 1);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
					}
				}
			}
			break;
		case IDC_COMBO_CUBE_SIZE_CUBE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_CUBE_SIZE_CUBE, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_EDIT_CUBE_SIZE_NLINES_X:
			{
				printf("IDC_EDIT_CUBE_SIZE_NLINES_X HIWORD( wParam ) = %d\n", HIWORD( wParam ));

				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						nx = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_NLINES_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						ny = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_NLINES_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						nz = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_SPACING_X:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						dx = atof(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_SPACING_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						dy = atof(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_SPACING_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						dz = atof(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_NLINES, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MIN_X:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						minx = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MIN_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						miny = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MIN_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						minz = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MAX_X:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_X, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						maxx = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MAX_Y:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Y, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						maxy = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_EDIT_CUBE_SIZE_MAX_Z:
			{
				if (update_edits && HIWORD( wParam ) == EN_CHANGE)
				{
					GetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Z, str, 1023);
					if (strlen(str) && ISNUM(str))
					{
						maxz = atoi(str);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					}
				}
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_CALC_NLINES:
			{
				nx = (long)(maxx-minx)/dx + 1;
				ny = (long)(maxy-miny)/dy + 1;
				nz = (long)(maxz-minz)/dz + 1;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_CALC_SPACING:
			{
				dx = (maxx - minx) / (nx - 1);
				dy = (maxy - miny) / (ny - 1);
				dz = (maxz - minz) / (nz - 1);
			}
			break;			
		case IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS:
			{
				update_edits = false;
				sprintf(str, "%f", minx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_X, str);
				sprintf(str, "%f", miny);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Y, str);
				sprintf(str, "%f", minz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MIN_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS:
			{
				update_edits = false;
				sprintf(str, "%f", maxx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_X, str);
				sprintf(str, "%f", maxy);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Y, str);
				sprintf(str, "%f", maxz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_MAX_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_FILL_NLINES:
			{			
				update_edits = false;
				sprintf(str, "%ld", nx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_X, str);
				sprintf(str, "%ld", ny);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Y, str);
				sprintf(str, "%ld", nz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_NLINES_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_FILL_SPACING:
			{
				update_edits = false;
				sprintf(str, "%f", dx);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_X, str);
				sprintf(str, "%f", dy);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Y, str);
				sprintf(str, "%f", dz);
				SetDlgItemText(hDlg, IDC_EDIT_CUBE_SIZE_SPACING_Z, str);
				update_edits = true;
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_EXTRACT:
			{
				GetDlgItemText(hDlg, IDC_EDITCUBE_SIZE_EXTRACT, str, 1023);

				if (strlen(str) && ISNUM(str))
				{				
					double len_extract_cube = atof(str);
					printf("len_extract_cube = %f\n", len_extract_cube);
					if (len_extract_cube > 0.0)
					{
						minx -= len_extract_cube;
						miny -= len_extract_cube;
						maxx += len_extract_cube;
						maxy += len_extract_cube;
						
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);
						SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
					}
				}
			}
			break;
		case IDC_BUTTON_BY_KAROTAZHY:
			{
				if (lpSurfDlgMem->pSurfDoc->SetExtremums_ByKarotazhy(minx, miny, minz, maxx, maxy, maxz))
				{
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
					nx = 51;
					ny = 51;
					nz = 51;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);

					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
				}
				else
					MessageBox(hDlg, "SetExtremums_ByKarotazhy\nfaults!!!", "Cube Size", 0);
			}
			break;
		case IDC_BUTTON_BY_GRIDDATA:
			{
				if (lpSurfDlgMem->pSurfDoc->SetExtremums_ByGriddata(minx, miny, minz, maxx, maxy, maxz))
				{
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
					nx = 51;
					ny = 51;
					nz = 51;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);

					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
				}
				else
					MessageBox(hDlg, "SetExtremums_ByDriddata\nfaults!!!", "Cube Size", 0);
			}
			break;
		case IDC_BUTTON_CUBE_SIZE_DEFAULT:
			{
				if (lpSurfDlgMem->pSurfDoc->m_cube_size.Defined())
				{
					minx = lpSurfDlgMem->pSurfDoc->m_cube_size.xLL;
					miny = lpSurfDlgMem->pSurfDoc->m_cube_size.yLL;
					minz = lpSurfDlgMem->pSurfDoc->m_cube_size.zLL;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);

					
					nx = lpSurfDlgMem->pSurfDoc->m_cube_size.nCol;
					ny = lpSurfDlgMem->pSurfDoc->m_cube_size.nRow;
					nz = lpSurfDlgMem->pSurfDoc->m_cube_size.nPag;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);

					dx = lpSurfDlgMem->pSurfDoc->m_cube_size.xSize;
					dy = lpSurfDlgMem->pSurfDoc->m_cube_size.ySize;
					dz = lpSurfDlgMem->pSurfDoc->m_cube_size.zSize;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
					
					maxx = minx + dx * (nx - 1);
					maxy = miny + dy * (ny - 1);
					maxz = minz + dz * (nz - 1);
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
				}
				else
				{
					minx = lpSurfDlgMem->pSurfDoc->m_xd_min;
					miny = lpSurfDlgMem->pSurfDoc->m_yd_min;
					minz = lpSurfDlgMem->pSurfDoc->m_zd_min;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MINIMUMS, 0), 0);

					maxx = lpSurfDlgMem->pSurfDoc->m_xd_max;
					maxy = lpSurfDlgMem->pSurfDoc->m_yd_max;
					maxz = lpSurfDlgMem->pSurfDoc->m_zd_max;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_MAXIMUMS, 0), 0);
					
					nx = 51;
					ny = 51;
					nz = 51;
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_NLINES, 0), 0);

					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_CALC_SPACING, 0), 0);
					SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CUBE_SIZE_FILL_SPACING, 0), 0);
				}

				SetDlgItemText(hDlg, IDC_EDITCUBE_SIZE_EXTRACT, "0.0");
			}
			break;
		case IDOK :
			{            
				if (!lpSurfDlgMem->pSurfDoc->m_cube_size.Defined())
				{
					lpSurfDlgMem->pSurfDoc->m_cube_size.Define(nz, ny, nx, minx, miny, minz, dx, dy, dz);
					lpSurfDlgMem->pSurfDoc->SaveCubeSizeToDB();
				}
				else
				{
					sprintf(str, "The cube size is defined\n\n"
						"%f\t%f\t%f\t\t%ld\n"
						"%f\t%f\t%f\t\t%ld\n"
						"%f\t%f\t%f\t\t%ld\n\n"
						"Are you sure to redefine it?\n"
						"by these values:\n\n"
						"%f\t%f\t%f\t\t%ld\n"
						"%f\t%f\t%f\t\t%ld\n"
						"%f\t%f\t%f\t\t%ld\n"
						,
						lpSurfDlgMem->pSurfDoc->m_cube_size.xLL, 
						lpSurfDlgMem->pSurfDoc->m_cube_size.xLL + lpSurfDlgMem->pSurfDoc->m_cube_size.xSize * (lpSurfDlgMem->pSurfDoc->m_cube_size.nCol - 1), 
						lpSurfDlgMem->pSurfDoc->m_cube_size.xSize, 
						lpSurfDlgMem->pSurfDoc->m_cube_size.nCol,

						lpSurfDlgMem->pSurfDoc->m_cube_size.yLL, 
						lpSurfDlgMem->pSurfDoc->m_cube_size.yLL + lpSurfDlgMem->pSurfDoc->m_cube_size.ySize * (lpSurfDlgMem->pSurfDoc->m_cube_size.nRow - 1), 
						lpSurfDlgMem->pSurfDoc->m_cube_size.ySize, 
						lpSurfDlgMem->pSurfDoc->m_cube_size.nRow,

						lpSurfDlgMem->pSurfDoc->m_cube_size.zLL, 
						lpSurfDlgMem->pSurfDoc->m_cube_size.zLL + lpSurfDlgMem->pSurfDoc->m_cube_size.zSize * (lpSurfDlgMem->pSurfDoc->m_cube_size.nPag - 1), 
						lpSurfDlgMem->pSurfDoc->m_cube_size.zSize, 
						lpSurfDlgMem->pSurfDoc->m_cube_size.nPag,

						minx, maxx, dx, nx,
						miny, maxy, dy, ny,
						minz, maxz, dz, nz);

					if (IDYES == MessageBox(hDlg, str, "Cube Size", MB_YESNO))
					{
						lpSurfDlgMem->pSurfDoc->m_cube_size.Define(nz, ny, nx, minx, miny, minz, dx, dy, dz);
						lpSurfDlgMem->pSurfDoc->SaveCubeSizeToDB();
					}
				}
				lpSurfDlgMem->pSurfDoc->m_cube_size.Printf();	
			}
			break;

		case IDC_BUTTON_CUBE_SIZE_UNDEFINE:
			{
				if (lpSurfDlgMem->pSurfDoc->m_cube_size.Defined())
				{
					lpSurfDlgMem->pSurfDoc->m_cube_size.Undefine();
					lpSurfDlgMem->pSurfDoc->UndefineCubeSizeInDB();
				}
			}
			break;

		case IDC_BUTTON_CUBE_SIZE_PRINTF:
			{
				lpSurfDlgMem->pSurfDoc->m_cube_size.Printf();
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
WNDPROC wpOrigProcSurfLithoMappingList; 
WNDPROC wpOrigProcSurfEnGeoMappingList; 
LRESULT CALLBACK DlgProcSurfLithoMappingList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];
	static size_t cols;


	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

			//
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.GetWnd();

					cols = 4;
					lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetCols(cols);
					
					SendMessage(hwnd,WM_USER + 5, 0, 0);
				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetHeaderString(0, "��� �����������");
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetHeaderString(1, "���");
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetHeaderString(2, "�������?");
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetHeaderString(2, "id_surf");
			}

		}
		break;
	case WM_USER + 5:
		{
			//**************************************
			// #############################################################
			// #############################################################

			lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.clear();

			vector<int> ColomnsEditing(cols);
			vector <bool*> vpbColomnsChecked(cols);
			
			ColomnsEditing[0] = 0;
			ColomnsEditing[1] = 0;
			ColomnsEditing[2] = 0;
			ColomnsEditing[3] = 0;

			for (vector<key_grid>::iterator it = lpSurfDlgMem->pSurfDoc->surf_litho_geo_element_mapping.begin();
				it != lpSurfDlgMem->pSurfDoc->surf_litho_geo_element_mapping.end(); it++)
			{
				vpbColomnsChecked[0] = NULL;
				vpbColomnsChecked[1] = NULL;
				vpbColomnsChecked[2] = NULL;
				vpbColomnsChecked[3] = NULL;

				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.AddRow(LPARAM(0), ColomnsEditing, vpbColomnsChecked);
				size_t r = lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.Rows()-1;
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetItemString(r,0,(*it).surfname);
				
				sprintf(str, "%s\0", (*it).key.c_str());
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetItemString(r,1,str);
				
				sprintf(str, "%d\0", (*it).podoshva);
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetItemString(r,2,str);
				
				sprintf(str, "%d\0", (*it).id_surf);
				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.SetItemString(r,2,str);
			}
		}
		break; 
		/*
#if !USE_LISTVIEW_STANDART_SLM 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateWellDrawListNames();
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break; 
#endif*/
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				//AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				//AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				//AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.UpdateView();
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_WELLSDRAWLIST_MOVEITEMUP:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceOrderList_MoveItemUp(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();

				}
				break;
			case ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceOrderList_MoveItemDown(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();
				}
				break;
			/*case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < GeoSurface::surface_order_list.size()) 
						{
							COLORREF color = GeoSurface::surface_order_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								GeoSurface::surface_order_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_RIGHT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_order_list.size())
					{
						GeoSurface::surface_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::right;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_LEFT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_order_list.size())
					{
						GeoSurface::surface_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::left;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();							
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_BOTH:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_order_list.size())
					{
						GeoSurface::surface_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::both;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;*/
			}
			break;

       /* case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;*/
#if !USE_LISTVIEW_STANDART_SLM 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_SurfLithoMappingListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_SurfLithoMappingListViewTab.OnNotify(lParam))
						{
							//pwin_project->SurfaceOrderList_UpdateCheckings();
							//pwin_project->UpdateAllViews();
						}
#if USE_LISTVIEW_STANDART_SLM 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcSurfLithoMappingList, hwnd, message, 
	   wParam, lParam);
}

LRESULT CALLBACK DlgProcSurfEnGeoMappingList(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndList   = NULL;
	int wmId, wmEvent;
	char str[1024];
	static size_t cols;

	static int context_menu_item;

	switch (message) 
	{
	case WM_INITDIALOG :
		{
			printf("WM_INITDIALOG hwnd %x\n", hwnd);
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			if (lpSurfDlgMem->pSurfDoc)
			{
				if (lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.00, 0.00, 0.00, 0.00))
				{
					hwndList = lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.GetWnd();

					cols = 4;
					lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetCols(cols);
					
					SendMessage(hwnd,WM_USER + 5, 0, 0);

				}
				// #############################################################
				// #############################################################
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetHeaderString(0, "��� �����������");
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetHeaderString(1, "���");
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetHeaderString(2, "�������?");
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetHeaderString(3, "id_surf");
			}

		}
		break;
	case WM_USER + 5:
		{
			// #############################################################
			// #############################################################

			lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.clear();

			vector<int> ColomnsEditing(cols);
			vector <bool*> vpbColomnsChecked(cols);
			
			ColomnsEditing[0] = 0;
			ColomnsEditing[1] = 0;
			ColomnsEditing[2] = 0;
			ColomnsEditing[3] = 0;

			for (vector<key_grid>::iterator it = lpSurfDlgMem->pSurfDoc->surf_eng_geo_element_mapping.begin();
				it != lpSurfDlgMem->pSurfDoc->surf_eng_geo_element_mapping.end(); it++)
			{
				vpbColomnsChecked[0] = NULL;
				vpbColomnsChecked[1] = NULL;
				vpbColomnsChecked[2] = NULL;
				vpbColomnsChecked[3] = NULL;


				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.AddRow(LPARAM(0), ColomnsEditing, vpbColomnsChecked);
				size_t r = lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.Rows()-1;
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetItemString(r,0,(*it).surfname);
				
				sprintf(str, "%s\0", (*it).key.c_str());
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetItemString(r,1,str);

				sprintf(str, "%d\0", (*it).podoshva);
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetItemString(r,2,str);				

				sprintf(str, "%d\0", (*it).id_surf);
				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.SetItemString(r,3,str);				
			}
		}
		break; 
		/*
#if !USE_LISTVIEW_STANDART_SEGM 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.OnEndEdit();
					lpSurfDlgMem->pSurfDoc->UpdateWellDrawListNames();
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project) pwin_project->UpdateAllMapViews();
				}
			}
			break; 
#endif
			*/
		case WM_CONTEXTMENU :
			{
				int xPos = GET_X_LPARAM(lParam); 
				int yPos = GET_Y_LPARAM(lParam); 
				RECT rL;
				GetWindowRect(hwndList, &rL);
				for (int i = 0; i < lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.Rows(); i++)
				{
					RECT rc;
					ListView_GetItemRect(hwndList, i, &rc, LVIR_BOUNDS);
					if (yPos > rL.top + rc.top && yPos <= rL.top + rc.bottom)
					{
						context_menu_item = i;
						break;
					}
				}
				//void Object::CreateContextMenu(HWND hWnd, LPARAM lParam)
				HMENU hMenu = CreatePopupMenu();
				// call virtual FillContextMenu
				//this->FillContextMenu(hMenu);
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMUP, "Move Item Up" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN, "Move Item Down" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				/*AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "Border Color" );
				AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_RIGHT, "Right" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_LEFT, "Left" );
				AppendMenu( hMenu, MFT_STRING, ID_TREE_KAROTAZHLIST_BOTH, "Both" );*/

				TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
					TPM_TOPALIGN |
					TPM_LEFTALIGN, 
					LOWORD( lParam ),
					HIWORD( lParam ), 0, hwnd, NULL );
				DestroyMenu( hMenu );

				lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.UpdateView();
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_TREE_WELLSDRAWLIST_MOVEITEMUP:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceBlankOrderList_MoveItemUp(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();

				}
				break;
			case ID_TREE_WELLSDRAWLIST_MOVEITEMDOWN:
				{
					lpSurfDlgMem->pSurfDoc->SurfaceBlankOrderList_MoveItemDown(context_menu_item);
					//win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					//if (pwin_project) pwin_project->UpdateAllMapViews();
				}
				break;
			/*case ID_TREE_COLORDIALOG:
				{
					if(context_menu_item < 0)
					{
					}
					else
					{
						if (context_menu_item < GeoSurface::surface_blank_order_list.size()) 
						{
							COLORREF color = GeoSurface::surface_blank_order_list[context_menu_item]->border_color;
							if (0 == ChooseSurfColor(lpSurfDlgMem->hWnd, color))
							{
								GeoSurface::surface_blank_order_list[context_menu_item]->border_color = color;
								project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
								if (pproject) pproject->UpdateAllMapViews();							
							}
						}
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_RIGHT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_blank_order_list.size())
					{
						GeoSurface::surface_blank_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::right;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_LEFT:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_blank_order_list.size())
					{
						GeoSurface::surface_blank_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::left;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();							
					}
				}
				break;
			case ID_TREE_KAROTAZHLIST_BOTH:
				{
					if (context_menu_item >= 0 && context_menu_item < GeoSurface::surface_blank_order_list.size())
					{
						GeoSurface::surface_blank_order_list[context_menu_item]->m_draw_mode_2d = wells_draw_list_item::draw_mode_2d::both;
						project* pproject = dynamic_cast <project*>(lpSurfDlgMem->pSurfDoc);
						if (pproject) pproject->UpdateAllMapViews();	
					}
				}
				break;*/
			}
			break;

        /*case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 25; 				

				return TRUE; 
			}
			break;*/
#if !USE_LISTVIEW_STANDART_SEGM 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_SurfEnGeoMappingListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						if (pwin_project->m_SurfEnGeoMappingListViewTab.OnNotify(lParam))
						{
							//pwin_project->SurfaceBlankOrderList_UpdateCheckings();
							//pwin_project->UpdateAllViews();
						}
#if USE_LISTVIEW_STANDART_SEGM 
						//if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
						//	pwin_project->UpdateKarotazhNames();
#endif
					}
				}
			}
			break;
   }
   return CallWindowProc(wpOrigProcSurfEnGeoMappingList, hwnd, message, 
	   wParam, lParam);
}

BOOL CALLBACK DlgProcGeoElementMapping( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hWndSurfLithoMappingList   = NULL;
	static HWND hWndSurfEnGeoMappingList   = NULL;


	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			//**************************************
			// #############################################################
			// #############################################################
			// Retrieve the handle to the Map control. 
			hWndSurfLithoMappingList = GetDlgItem(hDlg, IDC_STATIC_SURF_LITO_MAPPING); 

			// Subclass the picture control. 
			wpOrigProcSurfLithoMappingList = (WNDPROC) SetWindowLongPtr(hWndSurfLithoMappingList, 
				GWLP_WNDPROC, (LONG_PTR) DlgProcSurfLithoMappingList); 

			SendMessage(hWndSurfLithoMappingList, WM_INITDIALOG, wParam, lParam);
			// #############################################################
			// #############################################################
			// Retrieve the handle to the Map control. 
			hWndSurfEnGeoMappingList = GetDlgItem(hDlg, IDC_STATIC_SURF_ENGEO_MAPPING); 

			// Subclass the picture control. 
			wpOrigProcSurfEnGeoMappingList = (WNDPROC) SetWindowLongPtr(hWndSurfEnGeoMappingList, 
				GWLP_WNDPROC, (LONG_PTR) DlgProcSurfEnGeoMappingList); 

			SendMessage(hWndSurfEnGeoMappingList, WM_INITDIALOG, wParam, lParam);
			// #############################################################
			// #############################################################			
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{		
		case IDC_BUTTON_LOAD_SURF_LITHOGEOELEMENT_MAPPING_FILE:
			{
				lpSurfDlgMem->pSurfDoc->LoadSurfLithoGeoElementMappingFile();	
				SendMessage(hWndSurfLithoMappingList, WM_USER + 5, 0, 0);
			}
			break;
		/*case IDC_BUTTON_PRINT_SURF_LITHOGEOELEMENT_MAPPING_FILE:
			{
				lpSurfDlgMem->pSurfDoc->PrintSurfLithoGeoElementMapping();	
			}
			break;*/
		case IDC_BUTTON_LOAD_SURF_GEOELEMENT_MAPPING_FILE:
			{
				lpSurfDlgMem->pSurfDoc->LoadSurfEngGeoElementMappingFile();	
				SendMessage(hWndSurfEnGeoMappingList, WM_USER + 5, 0, 0);
			}
			break;
		/*case IDC_BUTTON_PRINT_SURF_GEOELEMENT_MAPPING_FILE:
			{
				lpSurfDlgMem->pSurfDoc->PrintSurfEngGeoElementMapping();	
			}
			break;*/
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



BOOL CALLBACK DlgProcAddGeoCube( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int index_geo_cube_type;
	static EngineerGeoElement::ValueType s_value_type;
	static EngineerGeoElement::GroundDescriptionType s_ground_description_type;
	static EngineerGeoElement::StrengthDescriptionType s_strength_description_type;
	static bool full_geo_cube_filling;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			index_geo_cube_type = -1;
			full_geo_cube_filling = true;

			s_value_type = EngineerGeoElement::ValueType::name;
			s_ground_description_type = EngineerGeoElement::GroundDescriptionType::normative;
			s_strength_description_type = EngineerGeoElement::StrengthDescriptionType::simple;

			lpSurfDlgMem = (LPSURFDLGDATA)lParam;

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton(hDlg, IDC_CHECK_FULL_GEO_CUBE_FILLING,	full_geo_cube_filling);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select parameter type");

			char str[4096];

			for( EngineerGeoElement::ValueType value_type = EngineerGeoElement::ValueType::name; 
				value_type <= EngineerGeoElement::ValueType::specific_cohesion;
				value_type++ )
			{
				sprintf(str, "%s    %s", 
					EngineerGeoElement::ValueTypeToString(value_type),
					EngineerGeoElement::ValueTypeToStringRus(value_type));

					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)str);
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_SETCURSEL,
				index_geo_cube_type+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			
			CheckRadioButton( hDlg,
				IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE,
				IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_CARRY_ABILITY,
				IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE);

			CheckRadioButton( hDlg,
				IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE,
				IDC_RADIO_STRENGTH_DESCRIPTION_ANY,
				IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE);
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{		

		case IDC_CHECK_FULL_GEO_CUBE_FILLING:
			{
				full_geo_cube_filling = IsDlgButtonChecked( hDlg, IDC_CHECK_FULL_GEO_CUBE_FILLING) == BST_CHECKED;
			}
			break;
		case IDC_BUTTON_LOAD_SURF_GEOELEMENT_MAPPING_FILE:
			{
				lpSurfDlgMem->pSurfDoc->LoadSurfEngGeoElementMappingFile();	
			}
			break;
		/*case IDC_BUTTON_PRINT_SURF_GEOELEMENT_MAPPING_FILE:
			{
				lpSurfDlgMem->pSurfDoc->PrintSurfEngGeoElementMapping();	
			}
			break;*/
		case IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE:
			{
				s_strength_description_type 
					= EngineerGeoElement::StrengthDescriptionType::simple;
			}
			break;		
		case IDC_RADIO_STRENGTH_DESCRIPTION_ON_SNIP:
			{
				s_strength_description_type 
					= EngineerGeoElement::StrengthDescriptionType::on_snip;
			}
			break;	
		case IDC_RADIO_STRENGTH_DESCRIPTION_WATER_SATURETED:
			{
				s_strength_description_type 
					= EngineerGeoElement::StrengthDescriptionType::water_saturated;
			}
			break;	
		case IDC_RADIO_STRENGTH_DESCRIPTION_IN_TASK_CONDITION:
			{
				s_strength_description_type 
					= EngineerGeoElement::StrengthDescriptionType::in_task_condition;
			}
			break;	
		case IDC_RADIO_STRENGTH_DESCRIPTION_IN_NATURE_CONDITION:
			{
				s_strength_description_type 
					= EngineerGeoElement::StrengthDescriptionType::in_nature_condition;
			}
			break;	
		case IDC_RADIO_STRENGTH_DESCRIPTION_ANY:
			{
				s_strength_description_type 
					= EngineerGeoElement::StrengthDescriptionType::any;
			}
			break;
		case IDC_RADIO_GROUND_DESCRIPTION_NORMATIVE:
			{
				s_ground_description_type = EngineerGeoElement::GroundDescriptionType
					::normative;
			}
			break;
		case IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_DEFORMATIONS:
			{
				s_ground_description_type = EngineerGeoElement::GroundDescriptionType
					::calculated_on_deformations;
			}
			break;
		case IDC_RADIO_GROUND_DESCRIPTION_CALCULATED_ON_CARRY_ABILITY:
			{
				s_ground_description_type = EngineerGeoElement::GroundDescriptionType
					::calculated_on_carry_ability;
			}
			break;
		case IDC_COMBO_SELECT_GEO_CUBE_TYPE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_geo_cube_type = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_GEO_CUBE_TYPE, CB_GETCURSEL,
							0,(LPARAM)0 );
				
				if (index_geo_cube_type > -1)
				{
					s_value_type = (EngineerGeoElement::ValueType) (index_geo_cube_type);
					
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_SIMPLE), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_ON_SNIP), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_WATER_SATURETED), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_IN_TASK_CONDITION), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_IN_NATURE_CONDITION), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_RADIO_STRENGTH_DESCRIPTION_ANY), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
					ShowWindow(GetDlgItem(hDlg, IDC_STATIC_STRENGTH_DESCRIPTION), EngineerGeoElement::ValueTypeIsStrength(s_value_type));
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDOK :
			{
				if (index_geo_cube_type > -1)
				{
					lpSurfDlgMem->pSurfDoc->AddGeoCube(full_geo_cube_filling, s_value_type, s_ground_description_type, s_strength_description_type);	
				}
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


BOOL CALLBACK DlgProcSuspendedInWaterSpecificGravity( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int index_cub_specific_gravity_of_ground_particles;
	// ����������� ���������� ���������� ����.���� ��.             .75
	static int index_cub_porosity_factor;
	static int type_of_calculation;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{

			//specific_gravity_of_ground_particles


			lpSurfDlgMem = (LPSURFDLGDATA)lParam;


			index_cub_porosity_factor = -1;
			index_cub_specific_gravity_of_ground_particles = -1;

		
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select spec grav of ground particles cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES, CB_SETCURSEL,
				index_cub_specific_gravity_of_ground_particles+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select porosty factor cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR, CB_SETCURSEL,
				index_cub_porosity_factor+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

						
			type_of_calculation = 1;
			switch(type_of_calculation)
			{
			case 1:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_SUSPENDED_IN_WATER_CUBE,
						IDC_RADIO_SUSPENDED_IN_WATER_GEOELEMENT,
						IDC_RADIO_SUSPENDED_IN_WATER_CUBE);
				}
				break;			
			case 2:
				{
					CheckRadioButton( hDlg,
						IDC_RADIO_SUSPENDED_IN_WATER_CUBE,
						IDC_RADIO_SUSPENDED_IN_WATER_GEOELEMENT,
						IDC_RADIO_SUSPENDED_IN_WATER_GEOELEMENT);
				}
				break;
			}

			SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CALCULATION_METHOD_SELECTED, 0), 0);

		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{	
		case IDC_BUTTON_CALCULATION_METHOD_SELECTED:
			{
				ShowWindow(GetDlgItem(hDlg,IDC_STATICSPECIFIC_GRAVITY_OF_GROUND_PARTICLES_CUBE), type_of_calculation == 1);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES), type_of_calculation == 1);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_POROSTY_FACTOR_CUBE), type_of_calculation == 1);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR), type_of_calculation == 1);
			}
			break;
		case IDC_RADIO_SUSPENDED_IN_WATER_CUBE:
			{
				type_of_calculation = 1;
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CALCULATION_METHOD_SELECTED, 0), 0);
			}
			break;
		case IDC_RADIO_SUSPENDED_IN_WATER_GEOELEMENT:
			{
				type_of_calculation = 2;
				SendMessage(hDlg, WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CALCULATION_METHOD_SELECTED, 0), 0);
			}
			break;
		case IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_porosity_factor = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_POROSTY_FACTOR, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;

		case IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_specific_gravity_of_ground_particles = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND_PARTICLES, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;

		case IDOK :
			{
				switch(type_of_calculation)
				{
				case 1:
					{
						lpSurfDlgMem->pSurfDoc->SuspendedInWaterSpecificGravity(
							index_cub_specific_gravity_of_ground_particles,
							index_cub_porosity_factor);
					}
					break;			
				case 2:
					{
						lpSurfDlgMem->pSurfDoc->SuspendedInWaterSpecificGravity();
					}
					break;
				}


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


WNDPROC wpOrigWaterSaturationTabWndProc; 

// Subclass procedure 
LRESULT APIENTRY WaterSaturationTabWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
	static LPSURFDLGDATA lpSurfDlgMem;
	static HWND hwndWaterSaturationList   = NULL;
	int wmId, wmEvent;

    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      // Control wants all keys - All keyboard input     
	} 
	switch (uMsg) 
	{
		case WM_INITDIALOG :
			{
				lpSurfDlgMem = (LPSURFDLGDATA)lParam;
				//**************************************
				// #############################################################
				// #############################################################
				if (lpSurfDlgMem->pSurfDoc)
				{
					 if (lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.Init(hwnd, (LPVOID)lpSurfDlgMem->pSurfDoc, 0.0, 0.0, 0.0, 0.0))
					 {
						 hwndWaterSaturationList = lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.GetWnd();
#if USE_LISTVIEW_STANDART_WSL 
						 lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.SetCols(2);
#else
						 lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.SetCols(3);
#endif
						 						
						lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.SetHeaderString(0, "������� ���������");
						lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.SetHeaderString(1, "���");
						GeoColomn * colomn = lpSurfDlgMem->pSurfDoc->FindGeoColomn(GeoElement::type::engineer_geological);
						if (colomn) 
						{
							for (map<string, GeoElement*>::iterator it = colomn->geo_elements.begin(); it != colomn->geo_elements.end(); it++)
							{		
								if (it->second)
								{
									GeoElement::type t = it->second->m_type;
									
									if (t != colomn->m_type)
									{
										printf("warning: element type  = \"%s\" (%d) not eqial colomn type = \"%s\"(%d)\n",
											GeoElement::GeoElementTypeToString(t), int(t),
											GeoElement::GeoElementTypeToString(colomn->m_type), int(colomn->m_type)
											);
									}

									char str[1024];


									GeoElement * geo = it->second;
									EngineerGeoElement * eng = dynamic_cast<EngineerGeoElement *>(geo);
									if (eng)
									{
										lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.AddRow(LPARAM(0), &eng->WaterSaturation_Checked);
										size_t r = lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.Rows()-1;
										
										sprintf(str, "���-%s\0", eng->GetKey().c_str());
										lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.SetItemString(r, 1, str);

										double v;
										if(eng->GetValue(EngineerGeoElement::ValueType::degree_of_moisture,
											EngineerGeoElement::GroundDescriptionType::normative,
											EngineerGeoElement::StrengthDescriptionType::simple, 
											v))
										{
											sprintf(str, "%f\0", v);
											lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.SetItemString(r, 0, str);
										}
									}
								}
							}
						}
					 }
				}				 

				// #############################################################
				// #############################################################
			}
			break;
#if !USE_LISTVIEW_STANDART_WSL 
		case WM_USER + 3:
			{
				if (lpSurfDlgMem->pSurfDoc)
				{
					lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.OnEndEdit();
					//lpSurfDlgMem->pSurfDoc->UpdateLayersNames();
					//lpSurfDlgMem->pSurfDoc->UpdateKarotazhNames();
					lpSurfDlgMem->pSurfDoc->UpdateWaterSaturation();
				}
			}
			break; 
#endif

        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 100; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_WSL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndWaterSaturationList)
				{
					//LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					//win_project* pwin_project = (win_project*)userdata;
					if (lpSurfDlgMem->pSurfDoc)
					{
						lpSurfDlgMem->pSurfDoc->m_WaterSaturationListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndWaterSaturationList)
				{
					win_project* pwin_project = dynamic_cast<win_project*>(lpSurfDlgMem->pSurfDoc);
					if (pwin_project)
					{
						pwin_project->m_WaterSaturationListViewTab.OnNotify(lParam);
						//pwin_project->UpdateAllViews();
#if USE_LISTVIEW_STANDART_WSL 
						if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
							pwin_project->UpdateWaterSaturation();

#endif
					}
/*					if (
						((LPNMHDR) lParam)->code == NM_CLICK
						||
						((LPNMHDR) lParam)->code == NM_DBLCLK
						)
					{
						RECT rect;
						GetClientRect(hSurfWnd,&rect);
						InvalidateRect(hSurfWnd,&rect, true);
					}*/
				}
			}
			break;
		case WM_CLOSE:
			{
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
			}
			break;
   }
   return CallWindowProc(wpOrigWaterSaturationTabWndProc, hwnd, uMsg, 
	   wParam, lParam); 
} 
BOOL CALLBACK DlgProcSvaiBuroNabivnie( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static int index_cub_internal_friction_angle;
	static int index_cub_specific_gravity_of_ground;
	static int index_surface_of_relief;
	static int index_surface_of_rostverk;
	static int index_cub_fluidity_index;

	static bool use_rostverk_altituda;

	static bool use_water_saturation;
	static int index_cub_specific_gravity_of_suspended_in_water_ground;
	static int index_cub_fluidity_index_of_water_saturated_ground;


	static BuroNabivSvaj::ParamType s_buro_nabiv_svaj_param_type; 
	static BuroNabivSvaj::SvaiType s_buro_nabiv_svaj_svai_type; 
	static int index_buro_nabiv_svaj_param_type;
	static int index_buro_nabiv_svaj_svai_type;

	static bool use_cub_specific_gravity_of_ground;
	static bool use_cub_fluidity_index;

	static HWND hWndWaterSaturationTab;	
		
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;


			index_cub_internal_friction_angle = -1;
			index_cub_specific_gravity_of_ground = -1;
			index_surface_of_relief = -1;
			index_surface_of_rostverk = -1;
			index_cub_fluidity_index = -1;
			index_buro_nabiv_svaj_param_type = -1;
			index_buro_nabiv_svaj_svai_type = -1;

			use_rostverk_altituda = false;

			use_water_saturation = false;
			index_cub_specific_gravity_of_suspended_in_water_ground = -1;
			index_cub_fluidity_index_of_water_saturated_ground = -1;

			use_cub_specific_gravity_of_ground = false;
			use_cub_fluidity_index = false;


			SetDlgItemText(hDlg, IDC_EDIT_D, "0.8\0");
			SetDlgItemText(hDlg, IDC_EDIT_GAMMA_K, "1.4\0");
			
			CheckRadioButton( hDlg,
				IDC_RADIO_SVAI_TYPE_ZABIVNYE,
				IDC_RADIO_SVAI_TYPE_4,
				IDC_RADIO_SVAI_TYPE_BUROVYE);

			s_buro_nabiv_svaj_param_type = BuroNabivSvaj::ParamType::none;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select svai type");

			for( BuroNabivSvaj::SvaiType svai_type = BuroNabivSvaj::SvaiType(BuroNabivSvaj::SvaiType::undefined + 1); 
				svai_type < BuroNabivSvaj::SvaiType::last;
				svai_type++ )
			{
//					SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_ADDSTRING, 0,
//						(LPARAM)(LPCTSTR)BuroNabivSvaj::SvaiTypeToString(svai_type));
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_SETCURSEL,
				index_buro_nabiv_svaj_svai_type+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			s_buro_nabiv_svaj_svai_type = BuroNabivSvaj::SvaiType::undefined;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select result");

			for( BuroNabivSvaj::ParamType param_type = BuroNabivSvaj::ParamType(BuroNabivSvaj::ParamType::none + 1); 
				param_type < BuroNabivSvaj::ParamType::end;
				param_type++ )
			{
					SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)BuroNabivSvaj::ParamTypeToString(param_type));
			}
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_SETCURSEL,
				index_buro_nabiv_svaj_param_type+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select int fric angle cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_SETCURSEL,
				index_cub_internal_friction_angle+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select spec grav of ground cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_SETCURSEL,
				index_cub_specific_gravity_of_ground+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select surface of relief");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			if (lpSurfDlgMem->pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_surfaces.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_surfaces.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_SETCURSEL,
				index_surface_of_relief+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select surface of rostverk");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			if (lpSurfDlgMem->pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_surfaces.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_surfaces.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_SETCURSEL,
				index_surface_of_rostverk+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@	

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select fluidity index cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_SETCURSEL,
				index_cub_fluidity_index+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				

			CheckDlgButton(hDlg, IDC_CHECK_ROSTVERK_ALTITUDA,	use_rostverk_altituda);
			EnableWindow(GetDlgItem(hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK), !use_rostverk_altituda );
			EnableWindow(GetDlgItem(hDlg,IDC_EDIT_ROSTVERK_ALTITUDA), use_rostverk_altituda );



			// Retrieve the handle to the Map control. 
			hWndWaterSaturationTab = GetDlgItem(hDlg, IDC_STATIC_WATER_SATURATION_TAB); 

			// Subclass the picture control. 
			wpOrigWaterSaturationTabWndProc = (WNDPROC) SetWindowLongPtr(hWndWaterSaturationTab, 
				GWLP_WNDPROC, (LONG_PTR) WaterSaturationTabWndSubclassProc); 

			SendMessage(hWndWaterSaturationTab, WM_INITDIALOG, wParam, lParam);

			CheckDlgButton(hDlg, IDC_CHECK_USE_WATER_SATURATION,	use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION), use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION_TAB), use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_USE_WATER_SATURATION), use_water_saturation);

			
			
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), use_water_saturation);
			
			ShowWindow(GetDlgItem(hDlg,IDC_STATIC_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), use_water_saturation);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), use_water_saturation);
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select spec grav of susp in wat ground cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_SETCURSEL,
				index_cub_specific_gravity_of_suspended_in_water_ground+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_RESETCONTENT,0,0);
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Select fluidity index of wat sat ground cube");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			if (lpSurfDlgMem->pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
			{
				do
				{
					SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)lpSurfDlgMem->pSurfDoc->m_cubes.GetCurrentMsg().GetName().c_str());
				}
				while (lpSurfDlgMem->pSurfDoc->m_cubes.IncrementCurrentMsg());
			}
			SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_SETCURSEL,
				index_cub_fluidity_index_of_water_saturated_ground+1, (LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

			CheckDlgButton(hDlg, IDC_CHECK_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND,	use_cub_specific_gravity_of_ground);
			CheckDlgButton(hDlg, IDC_CHECK_SELECT_CUBE_FLUIDITY_INDEX,	use_cub_fluidity_index);
			
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND), use_cub_specific_gravity_of_ground);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX), use_cub_fluidity_index);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), use_cub_specific_gravity_of_ground);
			ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), use_cub_fluidity_index);
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{	
		case IDC_RADIO_SVAI_TYPE_ZABIVNYE:
			{
			}
			break;
		case IDC_RADIO_SVAI_TYPE_BUROVYE:
			{
			}
			break;
		case IDC_CHECK_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND:
			{
				use_cub_specific_gravity_of_ground = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND) == BST_CHECKED;
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND), use_cub_specific_gravity_of_ground);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), use_water_saturation && use_cub_specific_gravity_of_ground);
			}
			break;
		case IDC_CHECK_SELECT_CUBE_FLUIDITY_INDEX:
			{
				use_cub_fluidity_index = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SELECT_CUBE_FLUIDITY_INDEX) == BST_CHECKED;
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX), use_cub_fluidity_index);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), use_water_saturation && use_cub_fluidity_index);
			}
			break;


		case IDC_CHECK_USE_WATER_SATURATION:
			{
				use_water_saturation = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_USE_WATER_SATURATION) == BST_CHECKED;

				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION), use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_WATER_SATURATION_TAB), use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_USE_WATER_SATURATION), use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND), use_water_saturation && use_cub_specific_gravity_of_ground);
				ShowWindow(GetDlgItem(hDlg,IDC_STATIC_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), use_water_saturation);
				ShowWindow(GetDlgItem(hDlg,IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND), use_water_saturation && use_cub_fluidity_index);
			}
			break;
		case IDC_CHECK_ROSTVERK_ALTITUDA:
			{
				use_rostverk_altituda = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_ROSTVERK_ALTITUDA) == BST_CHECKED;

				EnableWindow(GetDlgItem(hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK), !use_rostverk_altituda );
				EnableWindow(GetDlgItem(hDlg,IDC_EDIT_ROSTVERK_ALTITUDA), use_rostverk_altituda );
			}
			break;
		case IDC_COMBO_BURO_NABIV_SVAJ_PARAM:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_buro_nabiv_svaj_param_type = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_PARAM, CB_GETCURSEL,
							0,(LPARAM)0 );
				if (index_buro_nabiv_svaj_param_type > -1)
				{
					s_buro_nabiv_svaj_param_type = 
						(BuroNabivSvaj::ParamType) (index_buro_nabiv_svaj_param_type+1);
				}
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE:
			{
				if (HIWORD(wParam) == CBN_SELCHANGE)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					index_buro_nabiv_svaj_svai_type = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_BURO_NABIV_SVAJ_SVAI_TYPE, CB_GETCURSEL,
								0,(LPARAM)0 );
					if (index_buro_nabiv_svaj_svai_type > -1)
					{
						s_buro_nabiv_svaj_svai_type = 
							(BuroNabivSvaj::SvaiType) (index_buro_nabiv_svaj_svai_type+1);

						string s = "";
						char str[512];

						for( CGround::ground_type gt = CGround::ground_type::Sand; 
							gt <= CGround::ground_type::Clay;
							gt++ )
						{
							//double gamma_cf;
							//if (GetGammaCF(s_buro_nabiv_svaj_svai_type, gt, gamma_cf))
							//{
							//	sprintf(str, "%1.2f                    \0", gamma_cf);
							//	s += str;
							//}
								
						}	
						SetDlgItemText(hDlg, IDC_STATIC_GAMMA_CF, s.c_str());

					}
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
				}
			}
			break;
		case IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_fluidity_index = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_fluidity_index_of_water_saturated_ground = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_FLUIDITY_INDEX_OF_WATER_SATURATED_GROUND, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_SELECT_SURFACE_RELIEF:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_surface_of_relief = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_RELIEF, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;		
		case IDC_COMBO_SELECT_SURFACE_ROSTVERK:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_surface_of_rostverk = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_SURFACE_ROSTVERK, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_specific_gravity_of_ground = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_GROUND, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_specific_gravity_of_suspended_in_water_ground = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_SPECIFIC_GRAVITY_OF_SUSPENDED_IN_WATER_GROUND, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE:
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				index_cub_internal_friction_angle = -1 + SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_CUBE_INTERNAL_FRICTION_ANGLE, CB_GETCURSEL,
							0,(LPARAM)0 );
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@							
			}
			break;
		case IDOK :
			{
				char str [128];
				GetDlgItemText(hDlg, IDC_EDIT_D, str, sizeof(str) / sizeof(char));
				double d = atof(str);

				GetDlgItemText(hDlg, IDC_EDIT_ROSTVERK_ALTITUDA, str, sizeof(str) / sizeof(char));
				double rostverk_altituda = atof(str);

				GetDlgItemText(hDlg, IDC_EDIT_GAMMA_K, str, sizeof(str) / sizeof(char));
				double gamma_k = atof(str);				

				/*lpSurfDlgMem->pSurfDoc->SvaiBuroNabivnie(
					index_cub_internal_friction_angle,
					use_cub_specific_gravity_of_ground,
					index_cub_specific_gravity_of_ground,
					index_surface_of_relief,
					index_surface_of_rostverk,
					use_rostverk_altituda,
					rostverk_altituda,
					use_cub_fluidity_index,
					index_cub_fluidity_index,
					d, 
					s_buro_nabiv_svaj_svai_type,
					s_buro_nabiv_svaj_param_type,
					use_water_saturation,
					index_cub_specific_gravity_of_suspended_in_water_ground,
					index_cub_fluidity_index_of_water_saturated_ground,
					gamma_k,
					true, true, true);*/
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




#include "checkListBox.h"


extern HBITMAP hbmpUnchecked, hbmpChecked; 
extern HBITMAP hbmpPicture, hbmpOld; 

extern WNDPROC wpOrigListBoxProc; 
extern LRESULT APIENTRY ListBoxSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);
extern void AddCheckedItem(HWND hwndList, LPSTR lpstr, LPARAM check);


int GetToPaintSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_SLIDER_SURF_TOPAINT:
		nID = IDC_EDIT_SURF_TOPAINT;
		return 0;
	}
	return 0;
}

LRESULT CALLBACK DlgProcSurfToPaint( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static UINT m_Pos[11]; 			// ������ ������� ���������
	static UINT nObjects;
	static int direction;

	
    TCHAR tchBuffer[BUFFER]; 
    HWND hListBox; 
    TEXTMETRIC tm; 
    int y; 
    HDC hdcMem; 
    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 
	LONG itemdata;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			direction = 0;
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
//			lpSurfDlgMem->pSurfDoc->m_DrawListArray.SetPaintOneObject(true);
			DrawListArray::SetPaintMode(DrawListArray::one);

			nObjects = DrawListArray::GetLinesListNumber();
//			UINT n = lpSurfDlgMem->pSurfDoc->m_DrawListArray.GetObjectToPaint();
//				sprintf(s,"%u",n);
//				SetDlgItemText(hDlg, IDC_EDIT_SURF_TOPAINT, str);
			
			char str[1023];
			sprintf(str,"%u",500);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_TOPAINT_TIMER_MILLISECONDS, str);

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
			//====== �������������� ��� � ������ ���������
			RECT rect;
			GetClientRect(lpSurfDlgMem->hWnd,&rect);
			InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"one");
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"profile");
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"parameter");
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"all");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_SETCURSEL,
				0,(LPARAM)0 );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//##########################################################
            // Load bitmaps. 
            hbmpUnchecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UNCHECKED)); 
            hbmpChecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_CHECKED)); 
            // Retrieve list box handle. 
            hListBox = GetDlgItem(hDlg, IDC_LIST_SURF_TOPAINT); 
 
            wpOrigListBoxProc = (WNDPROC) SetWindowLongPtr(hListBox, 
                GWLP_WNDPROC, (LONG_PTR) ListBoxSubclassProc); 

            // Initialize the list box text and associate a bitmap 
            // with each list box item. 

            // Initialize the list box text and associate a bitmap 
            // with each list box item. 
			UINT nParam = DrawListArray::m_bDrawParam.size();
			for (UINT nparam = 0; nparam < nParam; nparam++)
			{
				char str[255];
				sprintf (str, "param %d", nparam);
				if (DrawListArray::m_bDrawParam[nparam])
				{
					AddCheckedItem(hListBox, str, 1);
				}
				else
				{
					AddCheckedItem(hListBox, str, 0);
				}
			}

            SetFocus(hListBox); 
            SendMessage(hListBox, LB_SETCURSEL, 0, 0); 
			//##########################################################
		}
		break;
        case WM_MEASUREITEM: 
		{ 
            lpmis = (LPMEASUREITEMSTRUCT) lParam; 
            // Set the height of the list box items. 
            lpmis->itemHeight = YBITMAP; 
		}
        break; 
        case WM_DRAWITEM: 
		{
 
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
			case ODA_FOCUS:
				{
					SendMessage(hDlg, WM_COMMAND,IDC_BUTTON_SURF_TOPAINT_PARAM,0);
				}
				break;
                case ODA_DRAWENTIRE: 
				{
 
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
					
				}
                break;  
            } 
		}
        break; 
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetToPaintSliderNum(hwnd, nID);
				int delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// ���������� �����
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// ������� Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// ������� End
					delta = +255;
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
					m_Pos[num] = newPos<0 ? 0 : newPos>(nObjects-1) ? (nObjects-1) : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				//lpSurfDlgMem->pSurfDoc->m_DrawListArray.SetObjectToPaint(m_Pos[num]);
				SendMessage(hDlg, WM_COMMAND, IDOK, m_Pos[num]);

				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%u", m_Pos[num]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				
			}
		}
		break;
	case WM_TIMER:
		{
			switch(wParam)
			{
			case IDT_TIMER_TOPAINT:
				{
					if (direction == -1)
						SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_SURF_TOPAINT_MINUS,0);
					if (direction == +1)
						SendMessage(hDlg,WM_COMMAND,IDC_BUTTON_SURF_TOPAINT_PLUS,0); 
				}
				break;
			}
		}
		break;

	case WM_COMMAND :
	{
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				int i;
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_TOPAINT);

				SendMessage(				// returns LRESULT in lResult
				(HWND) hwnd,				// handle to destination control
				(UINT) TBM_SETRANGE,		// message ID
				(WPARAM) true,				// = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, WORD(nObjects-1))	// = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== ������ �� ���� ������������
				for (i=0; i<1; i++)
					//====== ��������� ������������ ������ pPos
					m_Pos[i] = DrawListArray::GetObjectToPaint();

				//====== ������ ��������������� ���������
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_TOPAINT
				};
				
				char s[1024];
				//====== ���� ������� �� ���� �����������
				for (i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					
					//=== �������� Windows-��������� ���� ��������
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== ���������� ��� �������������
					int num = GetToPaintSliderNum(hwnd, nID);

					// ������� ���������� �������� � ��������� m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					
					//====== ������� ��������� ������ ������� �������
					sprintf (s,"%u",m_Pos[i]);
					//====== �������� ����� � ���� ������ �� ��������
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);					
				}
				sprintf(s,"%u",nObjects);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_TOPAINT_MAX, s);
			}
			break;
		case IDC_COMBO_SURF_TOPAINT:
			{
				int n = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_TOPAINT, CB_GETCURSEL,0,(LPARAM)0 );
				switch(n)
				{
				case 0:
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						DrawListArray::SetPaintMode(
							DrawListArray::one);
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						nObjects = DrawListArray::GetLinesListNumber();
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					break;
				case 1:
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						DrawListArray::SetPaintMode(
							DrawListArray::profile);
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						nObjects = DrawListArray::GetLinesListNumber() 
							/ DrawListArray::GetParametrNumber();
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					break;
				case 2:
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						DrawListArray::SetPaintMode(
							DrawListArray::parameter);
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						DrawListArray::GetParametrNumber();
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					break;
				case 3:
					{
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						DrawListArray::SetPaintMode(
							DrawListArray::all);
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						nObjects = 1;
						// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
					break;
				}
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
			}
			break;
		case IDC_BUTTON_SURF_TOPAINT_START_PLUS:
			{
				BOOL lpTranslated;
				UINT milliseconds = GetDlgItemInt(hDlg, IDC_EDIT_SURF_TOPAINT_TIMER_MILLISECONDS, &lpTranslated, false);

				if (direction == 0 && lpTranslated)
					SetTimer(hDlg,	IDT_TIMER_TOPAINT,
						milliseconds,	                // 10-second interval 
						(TIMERPROC) NULL);     // no timer callback 
				direction = +1;
			}
			break;
		case IDC_BUTTON_SURF_TOPAINT_START_MINUS:
			{
				BOOL lpTranslated;
				UINT milliseconds = GetDlgItemInt(hDlg, IDC_EDIT_SURF_TOPAINT_TIMER_MILLISECONDS, &lpTranslated, false);

				if (direction == 0 && lpTranslated)
					SetTimer(hDlg,	IDT_TIMER_TOPAINT,
						milliseconds,	                // 10-second interval 
						(TIMERPROC) NULL);     // no timer callback 
				direction = -1;
			}
			break;
		case IDC_BUTTON_SURF_TOPAINT_STOP:
			{
				KillTimer(hDlg,	IDT_TIMER_TOPAINT);
				direction = 0;
			}
			break;
		case IDC_BUTTON_SURF_TOPAINT_PLUS:
			{
				UINT n;
				n = DrawListArray::GetObjectToPaint();
				n++;
				if ( n >= 0 && n < nObjects )
				{
					SendMessage(hDlg, WM_COMMAND, IDOK, n);
				}
				else
					KillTimer(hDlg,	IDT_TIMER_TOPAINT);
			}
			break;
		case IDC_BUTTON_SURF_TOPAINT_MINUS:
			{
				UINT n;
				n = DrawListArray::GetObjectToPaint();
				n--;
				if ( n >= 0 && n < nObjects )
				{
					SendMessage(hDlg, WM_COMMAND, IDOK, n);
				}
				else
					KillTimer(hDlg,	IDT_TIMER_TOPAINT);

			}
			break;
		case IDOK :
			{
				PRIMITIVE_PTR points = DrawListArray::SetObjectToPaint(lParam);
				CPoint3 ptmin = points->GetMin();
				CPoint3 ptmax = points->GetMax();
				
				char str[256];

				sprintf(str, "%8.0f %8.0f", ptmin.x, ptmax.x);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_TOPAINT_XMINMAX, str);

				sprintf(str, "%8.0f %8.0f", ptmin.y, ptmax.y);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_TOPAINT_YMINMAX, str);

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

			}
			break;
        case IDC_BUTTON_SURF_TOPAINT_PARAM: 
			{
				hListBox = GetDlgItem(hDlg, IDC_LIST_SURF_TOPAINT); 
				int nItems = SendMessage(hListBox, LB_GETCOUNT, 0, 0);
				for (int i = 0; i < nItems; i++)
				{
					itemdata = SendMessage(hListBox, LB_GETITEMDATA, i, 0);
				}

				UINT nParam = DrawListArray::m_bDrawParam.size();
				for (UINT nparam = 0; nparam < nParam; nparam++)
				{
					itemdata = SendMessage(hListBox, LB_GETITEMDATA, nparam, 0);
					if (itemdata != LB_ERR)
					{
						if (itemdata)
						{
							DrawListArray::m_bDrawParam[nparam] = true;
						}
						else
						{
							DrawListArray::m_bDrawParam[nparam] = false;
						}									
					}
				}

													
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

			}
			break;
	  case ID_VIEW_ZOOM:
		  {
				HANDLE hDialog = LoadResource( hInst,
								FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_ZOOM),
											  RT_DIALOG ) );

				LPVOID lpDialog = LockResource( hDialog );

				HWND hdlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, lpSurfDlgMem->hWnd,
									(DLGPROC)DlgProcSurfZoom,
									(LPARAM)lpSurfDlgMem );
				ShowWindow(hdlg, SW_SHOW);
		  }
		  break;
			
		case IDCANCEL :
//			lpSurfDlgMem->pSurfDoc->m_DrawListArray.SetPaintOneObject(false);
			DrawListArray::SetPaintMode(DrawListArray::all);
			EndDialog( hDlg, IDCANCEL );
			break;
		}
	}
	break;
    case WM_DESTROY: 
		{

			// Free any resources used by the bitmaps. 

			DeleteObject(hbmpChecked); 
			DeleteObject(hbmpUnchecked);  
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}



int GetFiltersSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID �� ���������� hwnd ����������
	//====== � ���������� ������������� �������� ����������
	switch (GetDlgCtrlID(hwnd))
	{
	//====== �������� ������������� ���� ������
	case IDC_SLIDER_SURF_FILTER:
		nID = IDC_EDIT_SURF_FILTER_LEVEL;
		return 0;
	}
	return 0;
}
LRESULT CALLBACK DlgProcSurfFilters( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	static double m_Pos[11]; 			// ������ ������� ���������
	static double ** original = NULL;
	static double ** m_X = NULL;
	static double ** m_Y = NULL;
	static double ** filtred = NULL;
	static long rows, cols;
	static int vert_arm, gor_arm;
	static double filter_level, min_of_original, max_of_original;
	static SurfDoc* pSurfDoc;
	static double xLL; // X coordinate of the lower left corner of the grid
	static double yLL; // Y coordinate of the lower left corner of the grid
	static double xSize; // spacing between adjacent nodes in the X direction (between columns)
	static double ySize; // spacing between adjacent nodes in the Y direction (between rows)
	static double zMin; // minimum Z value within the grid
	static double zMax; // maximum Z value within the grid
	static int ** visible;
	static bool bFilterMode;
	static bool bDisvisible;
	static bool bZeroFiltredPoints;
	static bool bOnesNotFiltredPoints;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
			pSurfDoc = lpSurfDlgMem->pSurfDoc;
		
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ORIGINAL_MATRIX,0);
			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_FILTER_SLIDER,0);

			vert_arm	= 1;
			gor_arm		= 1;	
			
			char str[1023];
			sprintf(str,"%d",vert_arm);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_MEDIAN_FILTER_VERT_ARM, str);

			sprintf(str,"%d",gor_arm);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_MEDIAN_FILTER_GOR_ARM, str);

			bFilterMode = false;					
			CheckDlgButton( hDlg, IDC_CHECK_SURF_FILTER_MODE,
				bFilterMode ? BST_CHECKED : BST_UNCHECKED );

			bDisvisible = false;			
			CheckDlgButton( hDlg, IDC_CHECK_SURF_FILTER_DISVISIBLE,
				bDisvisible ? BST_CHECKED : BST_UNCHECKED );

			bZeroFiltredPoints = false;			
			CheckDlgButton( hDlg, IDC_CHECK_SURF_FILTER_ZERO_FILTRED_POINTS,
				bDisvisible ? BST_CHECKED : BST_UNCHECKED );

			bOnesNotFiltredPoints = false;			
			CheckDlgButton( hDlg, IDC_CHECK_SURF_FILTER_ONES_NOT_FILTRED,
				bOnesNotFiltredPoints ? BST_CHECKED : BST_UNCHECKED );

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@			
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_FILTERS_GRADIENT, CB_RESETCONTENT, 0,0);
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_FILTERS_GRADIENT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"grad X");
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_FILTERS_GRADIENT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"grad Y");
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_FILTERS_GRADIENT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"abs");
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_SURF_FILTERS_GRADIENT, CB_SETCURSEL,
				2,(LPARAM)0 );
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetFiltersSliderNum(hwnd, nID);
				double delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
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
					return (TRUE);
				}

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				filter_level = 
					min_of_original + m_Pos[num] * (max_of_original - min_of_original) / 100.  ;

				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%lf", filter_level);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				
				SendMessage(hDlg,WM_COMMAND,IDC_SURF_FILTER_APPLAY,(LPARAM)bFilterMode);
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_SURF_FILTER_ONES_NOT_FILTRED:
			{
				bOnesNotFiltredPoints = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SURF_FILTER_ONES_NOT_FILTRED) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_SURF_FILTER_ZERO_FILTRED_POINTS:
			{
				bZeroFiltredPoints = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SURF_FILTER_ZERO_FILTRED_POINTS) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_SURF_FILTER_DISVISIBLE:
			{
				bDisvisible = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SURF_FILTER_DISVISIBLE) == BST_CHECKED;
			}
			break;
		case IDC_CHECK_SURF_FILTER_MODE:
			{
				bFilterMode = IsDlgButtonChecked( hDlg, 
					IDC_CHECK_SURF_FILTER_MODE) == BST_CHECKED;
				if (bFilterMode)
				{
					SetDlgItemText(hDlg, IDC_BUTTON_SURF_FILTER_DELETE_NEGATIVE,
						"Delete positive");
					SetDlgItemText(hDlg, IDC_BUTTON_SURF_FILTER_DELETE_UNDER_FILTER_LEVEL,
						"Delete above filter level");
				}
				else
				{
					SetDlgItemText(hDlg, IDC_BUTTON_SURF_FILTER_DELETE_NEGATIVE,
						"Delete negative");
					SetDlgItemText(hDlg, IDC_BUTTON_SURF_FILTER_DELETE_UNDER_FILTER_LEVEL,
						"Delete under filter level");
				}
			}
			break;

		case IDC_INIT_SURF_FILTER_SLIDER :
			{
				int i;
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_FILTER);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 100)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== ������ �� ���� ������������
				for (i=0; i<1; i++)
					//====== ��������� ������������ ������ pPos
					m_Pos[i] = (filter_level - min_of_original) / (max_of_original - min_of_original) * 100.;

				//====== ������ ��������������� ���������
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_FILTER
				};

				//====== ���� ������� �� ���� �����������
				for (i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== �������� Windows-��������� ���� ��������
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== ���������� ��� �������������
					int num = GetFiltersSliderNum(hwnd, nID);

					// ������� ���������� �������� � ��������� m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					char s[1024];
					//====== ������� ��������� ������ ������� �������
					//sprintf (s,"%lf",min_of_original + m_Pos[i] * (max_of_original - min_of_original) / 100. );
					sprintf (s,"%lf",filter_level);
					//====== �������� ����� � ���� ������ �� ��������
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);
				}
			}
			break;
		case IDC_INIT_SURF_ORIGINAL_MATRIX:
			{
//				FILE* stream = fopen ("D://origin.txt","wt");

				if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst()	)
				{
					int s = 0;
					do
					{
						//====== ������� ������������� �������
						UINT	nx = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_lenx,
								ny = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_leny;
						//CPoint3 *ptd;
						//ptd = pSurfDoc->m_surfaces.GetCurrentMsg().m_vdPoints;
						PRIMITIVE_POINTS_PTR(CPoint3) ptd;
						ptd = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
						if (s == 0)
						{
							rows = ny;
							cols = nx;

							m_X = AllocDoubleMat(rows, cols);
							m_Y = AllocDoubleMat(rows, cols);
							original = AllocDoubleMat(rows, cols);
							filtred = AllocDoubleMat(rows, cols);	
							visible = AllocIntegerMat(rows, cols);

//							fprintf(stream, "rows = %d cols = %d\n", rows, cols);
							xLL = ptd[0].x, // X coordinate of the lower left corner of the grid
							yLL = ptd[0].y, // Y coordinate of the lower left corner of the grid
							xSize = 0.; // spacing between adjacent nodes in the X direction (between columns)
							ySize = 0.; // spacing between adjacent nodes in the Y direction (between rows)
						}

						//====== ���� ������� �� ����� ����������� (��� Z)
						for (UINT y=0, i=0;  y<ny;  y++/*, i++*/)
						{
							//====== ���� ������� ����� ��� X
							for (UINT x=0;  x<nx;  x++, i++)
							{
								//=== ����� ��������� ������ �� ����������
								double
									xi = ptd[i].x,
									yi = ptd[i].y,
									zi = ptd[i].z;
								if ( s == 0)
								{
									m_X[y][x] = zi;
									m_Y[y][x] = zi;
									original[y][x] = zi;
									filtred[y][x] = 0.0;
									visible[y][x] = ptd[i].bVisible;
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									if (x == 0 && y == 0)
									{
										ySize -= yi;
										xSize -= xi;
									}
									if (x == 1 && y == 0)
									{
										xSize += xi;
										ySize += yi;
									}
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									if (y == 0 && x == 0)
									{
										ySize -= yi;
										xSize -= xi;
									}
									if (y == 1 && x == 0)
									{
										xSize += xi;
										ySize += yi;
									}
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

									if ( i == 0 )
									{										
										min_of_original = zi;
										max_of_original = zi;
									}
									else
									{
										if (min_of_original > zi)
											min_of_original = zi;
										if (max_of_original < zi)
											max_of_original = zi;
									}
								}

//								fprintf(stream, "i = %d xi = %lf, yi = %lf zi = %lf x = %d y = %d\n", i, xi, yi, zi, x, y);
							}
//							fprintf(stream, "\n");
						}
						s++;

					}
					while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
				}



//				fclose(stream);
				char str[1023];
				sprintf(str,"%lf", min_of_original);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MIN, str);
				sprintf(str,"%lf", max_of_original);
				SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MAX, str);

				filter_level = (min_of_original + max_of_original) / 2.;
				sprintf(str,"%lf", filter_level);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str);
			}
			break;
		case IDC_RESTORE_SURF_WITH_ORIGINAL_MATRIX:
			{

				if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst()
						)
				{
					int s = 0;
					do
					{
						//====== ������� ������������� �������
						//COLORREF surfColor = pSurfDoc->m_surfaces.GetCurrentMsg();
						UINT	nx = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_lenx,
								ny = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_leny;
						//CPoint3 *ptd;
						//ptd = pSurfDoc->m_surfaces.GetCurrentMsg().m_vdPoints;
						PRIMITIVE_POINTS_PTR(CPoint3) ptd;
						ptd = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
						CPoint3 ptmax, ptmin;
						ptmax = pSurfDoc->m_surfaces.GetCurrentMsg().GetMax();
						ptmin = pSurfDoc->m_surfaces.GetCurrentMsg().GetMin();

						//====== ���� ������� �� ����� ����������� (��� Z)
						bool start = true;
						double maxz, minz;
						for (UINT y=0, i=0;  y<ny;  y++/*, i++*/)
						{
							//====== ���� ������� ����� ��� X
							for (UINT x=0;  x<nx;  x++, i++)
							{
								if ( s == 0)
								{
									double f = original[y][x];
									ptd[i].z = f;
									ptd[i].bVisible  = true;
									if (start)
									{
										maxz = minz = f;
										start = false;
									}
									else
									{
										if (maxz < f)
											maxz = f;
										if (minz > f)
											minz = f;
									}
								}
							}
						}
						if (s == 0)
						{
							ptmax.z = maxz;
							ptmin.z = minz;
							pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetMax(ptmax);
							pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetMin(ptmin);
						}
						s++;

					}
					while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
				}
			}
			break;
			
			
		case IDC_BUTTON_RESTORE_WITH_ORIGINAL:
			{
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_ORIGINAL_MATRIX,0);
	
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				
			}
			break;
		case IDC_BUTTON_RESTORE_WITH_FILTRED:
			{
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);
	
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				
			}
			break;
			
		case IDC_RESTORE_SURF_WITH_FILTRED_MATRIX:
			{

				if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst()
						)
				{
					int s = 0;
					do
					{
						//====== ������� ������������� �������
						//COLORREF surfColor = pSurfDoc->m_vSurfColor.GetCurrentMsg();
						UINT	nx = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_lenx,
								ny = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_leny;
						//CPoint3 *ptd;
						//ptd = pSurfDoc->m_surfaces.GetCurrentMsg().m_vdPoints;
						PRIMITIVE_POINTS_PTR(CPoint3) ptd;
						ptd = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
						CPoint3 ptmax, ptmin;
						ptmax = pSurfDoc->m_surfaces.GetCurrentMsg().GetMax();
						ptmin = pSurfDoc->m_surfaces.GetCurrentMsg().GetMin();

						//====== ���� ������� �� ����� ����������� (��� Z)
						bool start = true;
						double maxz, minz;
						for (UINT y=0, i=0;  y<ny;  y++/*, i++*/)
						{
							//====== ���� ������� ����� ��� X
							for (UINT x=0;  x<nx;  x++, i++)
							{
								if ( s == 0)
								{
									double f = filtred[y][x];
									ptd[i].z = f;
									ptd[i].bVisible = visible[y][x] != 0;
									if (start)
									{
										maxz = minz = f;
										start = false;
									}
									else
									{
										if (maxz < f)
											maxz = f;
										if (minz > f)
											minz = f;
									}
								}
							}
						}
						if (s == 0)
						{
							ptmax.z = maxz;
							ptmin.z = minz;
							pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetMax(ptmax);
							pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetMin(ptmin);
						}
						s++;

					}
					while(
						pSurfDoc->m_surfaces.IncrementCurrentMsg()
						);
				}
			}
			break;
			
		case IDC_BUTTON_SURF_FILTER_DELETE_UNDER_FILTER_LEVEL:
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str, 62);
				double filter_level_ = atof (str) ;

				if (filter_level_ >= min_of_original && filter_level_ <= min_of_original)
					filter_level = filter_level_;

				int r, c;
				switch (bFilterMode)
				{					
				case 0:
					{
					for ( r = 0; r < rows; r++){
						for ( c = 0; c < cols; c++){
							if ( original[r][c] < filter_level)
							{
								original[r][c] = filter_level;
								visible[r][c] = bDisvisible ? 0 : 1;
							}
							else
							{
								visible[r][c] = 1;
							}
					}}
					min_of_original = filter_level;

					sprintf(str,"%lf", min_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MIN, str);
					sprintf(str,"%lf", max_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MAX, str);


					filter_level = min_of_original;
					sprintf(str,"%lf", filter_level);
					SetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str);
					}
					break;
				case 1:
					{
					for ( r = 0; r < rows; r++){
						for ( c = 0; c < cols; c++){
							if ( original[r][c] > filter_level)
							{
								original[r][c] = filter_level;
								visible[r][c] = bDisvisible ? 0 : 1;
							}
							else
							{
								visible[r][c] = 1;
							}
					}}
					max_of_original = filter_level;

					sprintf(str,"%lf", min_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MIN, str);
					sprintf(str,"%lf", max_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MAX, str);


					filter_level = max_of_original;
					sprintf(str,"%lf", filter_level);
					SetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str);
					}
					break;
				}


				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_ORIGINAL_MATRIX,0);
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_FILTER_SLIDER,0);

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_BUTTON_SURF_FILTER_DELETE_NEGATIVE:
			{
				int r,c;
				switch (bFilterMode)
				{					
				case 0:
					{
					for ( r = 0; r < rows; r++){
						for ( c = 0; c < cols; c++){
							if ( original[r][c] < 0.0)
							{
								original[r][c] = 0.0;
								visible[r][c] = bDisvisible ? 0 : 1;
							}
							else
							{
								visible[r][c] = 1;
							}
					}}
					min_of_original = 0.0;
					char str[1023];
					sprintf(str,"%lf", min_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MIN, str);
					sprintf(str,"%lf", max_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MAX, str);

					filter_level = min_of_original;
					sprintf(str,"%lf", filter_level);
					SetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str);
					}
					break;
				case 1:
					{
					for ( r = 0; r < rows; r++){
						for ( c = 0; c < cols; c++){
							if ( original[r][c] > 0.0)
							{
								original[r][c] = 0.0;
								visible[r][c] = bDisvisible ? 0 : 1;
							}
							else
							{
								visible[r][c] = 1;
							}
					}}
					max_of_original = 0.0;
					char str[1023];
					sprintf(str,"%lf", min_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MIN, str);
					sprintf(str,"%lf", max_of_original);
					SetDlgItemText(hDlg, IDC_STATIC_SURF_FILTER_LEVEL_MAX, str);

					filter_level = max_of_original;
					sprintf(str,"%lf", filter_level);
					SetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str);
					}
					break;
				}

				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_ORIGINAL_MATRIX,0);
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_FILTER_SLIDER,0);


				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_SURF_FILTER_APPLAY:
			{
				int r,c;
				switch (lParam)
				{					
				case 0:
					{
						for ( r = 0; r < rows; r++){
							for ( c = 0; c < cols; c++){
								if ( original[r][c] > filter_level)
								{
									filtred[r][c] = bOnesNotFiltredPoints ? 1.0 : original[r][c];
									visible[r][c] = 1;
								}
								else
								{
									filtred[r][c] = bZeroFiltredPoints ? 0.0 : filter_level;
									visible[r][c] = bDisvisible ? 0 : 1;
								}
						}}
					}
					break;
				case 1:
					{
						for ( r = 0; r < rows; r++){
							for ( c = 0; c < cols; c++){
								if ( original[r][c] < filter_level)
								{
									filtred[r][c] = bOnesNotFiltredPoints ? 1.0 : original[r][c];
									visible[r][c] = 1;
								}
								else
								{
									filtred[r][c] = bZeroFiltredPoints ? 0.0 : filter_level;
									visible[r][c] = bDisvisible ? 0 : 1;
								}
						}}
					}
					break;
				}
			}
			break;
		case IDC_BUTTON_SURF_FILTERS_GRADIENT:
			{
				int grad_type = SendDlgItemMessage( hDlg, IDC_COMBO_SURF_FILTERS_GRADIENT, CB_GETCURSEL,0,(LPARAM)0 );

				int r,c;
				for ( r = 0; r < rows; r++){
					for ( c = 0; c < cols; c++){
						filtred[r][c] = 0.0;
					}
				}
				switch (grad_type)
				{
				case 0:
					{
						for ( r = 1; r < rows-1; r++){
							for ( c = 1; c < cols-1; c++){

								//double grad_x = (original[r  ][c+1] - original[r  ][c-1]) / (m_X[r  ][c+1] - m_X[r  ][c-1]);
								double grad_x = (original[r  ][c+1] - original[r  ][c-1]);

								filtred[r][c] = grad_x;

							}
						}
					}
					break;
				case 1:
					{
						for ( r = 1; r < rows-1; r++){
							for ( c = 1; c < cols-1; c++){

								//double grad_y = (original[r+1][c  ] - original[r-1][c  ]) / (m_Y[r+1][c  ] - m_Y[r-1][c  ]);
								double grad_y = (original[r+1][c  ] - original[r-1][c  ]);

								filtred[r][c] = grad_y;

							}
						}
					}
					break;
				case 2:
					{
						for ( r = 1; r < rows-1; r++){
							for ( c = 1; c < cols-1; c++){

								//double 					
								//	grad_x = (original[r  ][c+1] - original[r  ][c-1]) / (m_X[r  ][c+1] - m_X[r  ][c-1]),
								//	grad_y = (original[r+1][c  ] - original[r-1][c  ]) / (m_Y[r+1][c  ] - m_Y[r-1][c  ]);
								double 					
									grad_x = (original[r  ][c+1] - original[r  ][c-1]),
									grad_y = (original[r+1][c  ] - original[r-1][c  ]);

								filtred[r][c] = sqrt(grad_x*grad_x + grad_y*grad_y);

							}
						}
					}
					break;
				}
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;
		case IDC_BUTTON_SURF_FILTER_CALCULATE_ABCD_AND_IZO_A:
			{
				int r,c;
				for ( r = 0; r < rows-1; r++){
					for ( c = 0; c < cols-1; c++){
						//�������� ��������� ������������
						vdouble M,Z;
						M.resize(4,4);
						Z.resize(4);

						M(0,0) = 0    *0;		//ptd[i].x * ptd[i].y;
						M(1,0) = 0    *xSize;	//ptd[j].x * ptd[j].y;
						M(2,0) = ySize*xSize;	//ptd[k].x * ptd[k].y;
						M(3,0) = ySize*0;		//ptd[n].x * ptd[n].y;

						M(0,1) = 0;				//ptd[i].x;
						M(1,1) = xSize;			//ptd[j].x;
						M(2,1) = xSize;			//ptd[k].x;
						M(3,1) = 0;				//ptd[n].x;

						M(0,2) = 0;				//ptd[i].y;
						M(1,2) = 0;				//ptd[j].y;
						M(2,2) = ySize;			//ptd[k].y;
						M(3,2) = ySize;			//ptd[n].y;

						M(0,3) = 1.0;
						M(1,3) = 1.0;
						M(2,3) = 1.0;
						M(3,3) = 1.0;
						
						Z[0] = original[r  ][c  ];//ptd[i].z;
						Z[1] = original[r  ][c+1];//ptd[j].z;
						Z[2] = original[r+1][c+1];//ptd[k].z;
						Z[3] = original[r+1][c  ];//ptd[n].z;

						vdouble ABCD;
						double det;
						M.sls_det(Z, ABCD, det, false);

						double 
							A = ABCD[0],
							B = ABCD[1],
							C = ABCD[2],
							D = ABCD[3];

						filtred[r][c] = A;

						//Y = ((B*c+a)*X + (D*c+d))/((A*c)*X + (C*c+b));

						//X = ((C*c+b)*Y + (D*c+d))/((A*c)*Y + (B*c+a));
					}
				}
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str, 62);
				double filter_level_ = atof (str) ;

				if (filter_level_ >= min_of_original && filter_level_ <= max_of_original)
					filter_level = filter_level_;

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_FILTER_SLIDER,0);
				SendMessage(hDlg,WM_COMMAND,IDC_SURF_FILTER_APPLAY,(LPARAM)bFilterMode);
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;
			
		case IDC_BUTTON_SAVE_ORIGINAL_AS_GRID:
			{
				zMin = original[0][0]; // minimum Z value within the grid
				zMax = original[0][0]; // maximum Z value within the grid
				int r,c;
				for ( r = 0; r < rows; r++)
				{
					for ( c = 0; c < cols; c++)
					{
						 if (zMin > original[r][c])
							 zMin = original[r][c];
						 if (zMax < original[r][c])
							 zMax = original[r][c];
					}
				}
				char str[1024];
				sprintf(str,"xLL = %lf, yLL = %lf, xSize = %lf, ySize = %lf, zMin = %lf, zMax = %lf , rows = %d, cols = %d",xLL, yLL, xSize, ySize, zMin, zMax, rows, cols);
				MessageBox(0,str, "",0);

				SaveAsSurferGrid7(hDlg, "original", 
									  rows, 
									  cols, 

									  xLL, // X coordinate of the lower left corner of the grid
									  yLL, // Y coordinate of the lower left corner of the grid
									  xSize, // spacing between adjacent nodes in the X direction (between columns)
									  ySize, // spacing between adjacent nodes in the Y direction (between rows)
									  zMin, // minimum Z value within the grid
									  zMax, // maximum Z value within the grid
									  original, visible);
			}
			break;
		case IDC_BUTTON_SAVE_FILTRED_AS_GRID:
			{
				zMin = filtred[0][0]; // minimum Z value within the grid
				zMax = filtred[0][0]; // maximum Z value within the grid
				int r,c;
				for ( r = 0; r < rows; r++)
				{
					for ( c = 0; c < cols; c++)
					{
						 if (zMin > filtred[r][c])
							 zMin = filtred[r][c];
						 if (zMax < filtred[r][c])
							 zMax = filtred[r][c];
					}
				}
				SaveAsSurferGrid7(hDlg, "filtred", 
									  rows, 
									  cols, 
									  xLL, // X coordinate of the lower left corner of the grid
									  yLL, // Y coordinate of the lower left corner of the grid
									  xSize, // spacing between adjacent nodes in the X direction (between columns)
									  ySize, // spacing between adjacent nodes in the Y direction (between rows)
									  zMin, // minimum Z value within the grid
									  zMax, // maximum Z value within the grid
									  filtred, visible);
			}
			break;
		case IDC_BUTTON_SURF_FILTER_LEVEL_ON_MEDIANA:
			{
				int len = rows*cols;

				double *p = (double *)
					HeapAlloc(GetProcessHeap(), 
					HEAP_ZERO_MEMORY, len*sizeof(double));
				int i, r, c;
				i = 0;
				for ( r = 0; r < rows; r++)
				{
					for ( c = 0; c < cols; c++)
					{
						 p[i] = original[r][c];
						 i++;
					}
				}
				filter_level = Median(p, len);

				char str[1023];
				sprintf(str, "%lf", filter_level);
				SetDlgItemText(hDlg, IDC_EDIT_SURF_FILTER_LEVEL, str);


				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_FILTER_SLIDER,0);
				SendMessage(hDlg,WM_COMMAND,IDC_SURF_FILTER_APPLAY,(LPARAM)bFilterMode);
				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);

				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
			}
			break;


		case IDC_BUTTON_USE_MEDIAN_FILTERING:
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_MEDIAN_FILTER_VERT_ARM, str, 62);
				vert_arm = atoi (str);

				GetDlgItemText(hDlg, IDC_EDIT_SURF_MEDIAN_FILTER_GOR_ARM, str, 62);
				gor_arm = atoi (str);
				int len = (2*vert_arm + 1) * (2*gor_arm + 1);

				double *p = (double *)
					HeapAlloc(GetProcessHeap(), 
					HEAP_ZERO_MEMORY, len*sizeof(double));

				int r, c, ri,ci, i;
				for ( r = 0; r < rows; r++)
				{
					for ( c = 0; c < cols; c++)
					{
						 filtred[r][c] = 0.0;
					}
				}
				for ( r = vert_arm; r < rows - vert_arm; r++)
				{
					for ( c = gor_arm; c < cols - gor_arm; c++)
					{
						i = 0;
						for ( ri = r - vert_arm; ri <= r + vert_arm; ri++){
							for ( ci = c - gor_arm; ci <= c + gor_arm; ci++){
								p[i] = original[ri][ci];
								i++;
						}}
						filtred[r][c] = original[r][c] - Median(p, len);

						if (filtred[r][c] < 0. )
							filtred[r][c] = 0.;

				}}

				for ( r = 1; r < rows - 1; r++)
				{
					for ( c = 1; c < cols - 1; c++)
					{
						 int nb = 
							 int(filtred[r-1][c-1] == 0.0) + 
							 int(filtred[r-1][c  ] == 0.0) + 
							 int(filtred[r-1][c+1] == 0.0) + 
							 int(filtred[r  ][c-1] == 0.0) + 
							 int(filtred[r  ][c+1] == 0.0) + 
							 int(filtred[r+1][c-1] == 0.0) + 
							 int(filtred[r+1][c  ] == 0.0) + 
							 int(filtred[r+1][c+1] == 0.0); 
							 
						if (nb == 8)
							filtred[r][c] = 0.;
					}
				}

				SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_FILTRED_MATRIX,0);


				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				lpSurfDlgMem->pSurfDoc->Draw();
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);


			}
			break;
			
		case IDCANCEL :
				/*//SendMessage(hDlg,WM_COMMAND,IDC_RESTORE_SURF_WITH_ORIGINAL_MATRIX,0);
				//==============================================
				glDeleteLists(FIRST_HARD_LIST+1,N_HARD_LISTS +(GLsizei) lpSurfDlgMem->pSurfDoc->m_nglLists);
				lpSurfDlgMem->pSurfDoc->m_nglLists = 0;								
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();
				DrawScene(lpSurfDlgMem->pSurfDoc, lpSurfDlgMem->m_bQuad, lpSurfDlgMem->m_FillMode);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);*/
				//==============================================
				FreeDoubleMat(m_X);
				FreeDoubleMat(m_Y);
				FreeDoubleMat(original);
				FreeDoubleMat(filtred);
				//==============================================
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}



LRESULT CALLBACK DlgProcSurfIzolines( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFDLGDATA lpSurfDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfDlgMem = (LPSURFDLGDATA)lParam;
//			lpSurfDlgMem->pSurfDoc->SetIzolines();

		
			char str[1023];
//			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_izo_start);
//			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_START, str);

			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_izo_step);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_STEP, str);

//			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_izo_end);
//			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_END, str);

//			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_part);
//			SetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_PART, str);

			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_zd_min);
			SetDlgItemText(hDlg, IDC_STATIC_SURF_ZMIN, str);

			sprintf(str,"%lf",lpSurfDlgMem->pSurfDoc->m_zd_max);
			SetDlgItemText(hDlg, IDC_STATIC_SURF_ZMAX, str);


			SetDlgItemInt(hDlg,IDC_EDIT_SURF_IZO_ANGLE_LOCAL_MIN, 1, false);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_COS_BORDER, "-0.99");

			
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				char str[1023];
/*
				GetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_START,str,1022);
				double v = atof (str);
				if (v >= lpSurfDlgMem->pSurfDoc->m_zd_min)
					lpSurfDlgMem->pSurfDoc->m_izo_start = v;
				else
					MessageBox(0, "Enter a valid value of start", "Izolines dialog", 0);
*/
				GetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_STEP,str,1022);
				double v = atof (str);
				if (v > 0.0)
					lpSurfDlgMem->pSurfDoc->m_izo_step = v;
				else
					MessageBox(0, "Enter a valid value of step", "Izolines dialog", 0);
				
/*				GetDlgItemText(hDlg, IDC_EDIT_SURF_IZO_END,str,1022);
				v = atof (str);
				if (v <= lpSurfDlgMem->pSurfDoc->m_zd_max)
					lpSurfDlgMem->pSurfDoc->m_izo_end = v;
				else
					MessageBox(0, "Enter a valid value of end", "Izolines dialog", 0);
*/
								
				lpSurfDlgMem->pSurfDoc->Izolines();
				// init of zoomCoefZ_XY
				lpSurfDlgMem->pSurfDoc->ZoomView();

				lpSurfDlgMem->pSurfDoc->Draw();

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);

			}
			break;
		case IDC_BUTTON_SURF_SAVE_SPHERES:
			{
				lpSurfDlgMem->pSurfDoc->SpheresSaveAs();
			}
			break;
		case IDC_BUTTON_SURF_IZOLINES_SAVE_AS:
			{
				lpSurfDlgMem->pSurfDoc->IzolinesSaveAs();
			}
			break;
		case IDC_BUTTON_SURF_IZOLINES_ANGLE_LOCAL_MIN:
			{
				lpSurfDlgMem->pSurfDoc->ClearSpheres();
				BOOL Translated;
				UINT n = GetDlgItemInt(hDlg,IDC_EDIT_SURF_IZO_ANGLE_LOCAL_MIN, &Translated, false);
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_COS_BORDER, str, 1022);
				double cos_boder = atof(str);

				if (Translated)
					lpSurfDlgMem->pSurfDoc->AngleLocalMin(n, cos_boder);
				//====== �������������� ��� � ������ ���������
				lpSurfDlgMem->pSurfDoc->ZoomView();


				lpSurfDlgMem->pSurfDoc->Draw();
				RECT rect;
				GetClientRect(lpSurfDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
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


LRESULT CALLBACK DlgProcSurfProp( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFPROPDLGDATA lpSurfPropDlgMem;
	static int m_Pos[11]; 			// ������ ������� ���������
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			int i;
			lpSurfPropDlgMem = (LPSURFPROPDLGDATA)lParam;
			//====== ������ �� ���� ������������
			for (i=0; i<11; i++)
				//====== ��������� ������������ ������ pPos
				m_Pos[i] = lpSurfPropDlgMem->pSurfDoc->m_LightParam[i];

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
			for (i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
			{
				//=== �������� Windows-��������� ���� ��������
				HWND hwnd = GetDlgItem(hDlg, IDs[i]);
				UINT nID;

				//====== ���������� ��� �������������
				int num = GetSliderNum(hwnd, nID);

				// ������� ���������� �������� � ��������� m_Pos[i]
				::SendMessage(hwnd, TBM_SETPOS, TRUE,
								(LPARAM)m_Pos[i]);
				char s[1024];
				//====== ������� ��������� ������ ������� �������
				sprintf (s,"%d",m_Pos[i]);
				//====== �������� ����� � ���� ������ �� ��������
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);
			}
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int num = GetSliderNum(hwnd, nID);
				int delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
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
					return (TRUE);
				}

				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%d",m_Pos[num]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				//====== �������� ��������� � ����� ����
				//m_pView->SetLightParam (num, m_Pos[num]);

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
				lpSurfPropDlgMem->pSurfDoc->m_LightParam[num] = m_Pos[num];
/*
// ���������� ����� ����������� �����
// ������������ ������ �� ������
// ��������� � ������ ������
				project * prj;
				prj = dynamic_cast<project *>(lpSurfPropDlgMem->pSurfDoc);
				if (num >= 0 && num < 3)
				{
					for (i32u n1 = 0;n1 < prj->light_vector.size();n1++)
					{
						//camera * owner = prj->light_vector[n1]->owner;
						//if (owner != NULL && owner != this) continue;
						//prj->light_vector[n1]->SetupLocation();
							
						prj->light_vector[n1]->GetLocData()->zdir[num] = m_Pos[num];
					}
				}
*/
				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfPropDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfPropDlgMem->hWnd,&rect, true);
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				EndDialog( hDlg, IDOK );
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
LRESULT CALLBACK DlgProcPlayMols( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPSURFPROPDLGDATA lpSurfPropDlgMem;
	static int m_Pos; 			// ������ ������� ���������
	static int m_nblocks;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpSurfPropDlgMem = (LPSURFPROPDLGDATA)lParam;
			m_Pos = 0;

			//=== �������� Windows-��������� ���� ��������
			HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_PLAY_MOLS);
			//UINT nID;
			
			m_nblocks = mols_filelength / blockSize;
			m_Pos = int(20000.0*(double(blockNum)/double(m_nblocks)));
			
			SendMessage(    // returns LRESULT in lResult
			(HWND) hwnd,       // handle to destination control
			(UINT) TBM_SETRANGE,    // message ID
			(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
			(LPARAM) MAKELONG (0, 20000)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
			);

			// ������� ���������� �������� � ��������� m_Pos[i]
			::SendMessage(hwnd, TBM_SETPOS, TRUE,
							(LPARAM)m_Pos);
			char s[1024];
			//====== ������� ��������� ������ ������� �������
			sprintf (s,"%d",blockNum);
			//====== �������� ����� � ���� ������ �� ��������
			SetDlgItemText(hDlg, IDC_STATIC_PLAY_MOLS_SLIDER, (LPCTSTR)s);
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-��������� ���� ��������� ��������
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				//UINT nID;

				//=== ���������� ������ � ������� ������� ���������
				int delta, newPos;

				//====== ����������� ��� �������
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// ���������� �����
					m_Pos = nPos;
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
					newPos = m_Pos + delta;
					//====== �����������
					m_Pos = newPos<0 ? 0 : newPos>100 ? 100 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}
				m_nblocks = mols_filelength / blockSize;
				//m_Pos = int(20000.0*(double(blockNum)/double(m_nblocks)));
				blockNum = int((double(m_Pos) / 20000.0) * double(m_nblocks));



				//====== �������������� ��������� ������ �������
				char s[1024];
				sprintf (s,"%d",blockNum);
				SetDlgItemText(hDlg, IDC_STATIC_PLAY_MOLS_SLIDER, (LPCTSTR)s);

				if (blockNum > 0)
					blockNum--;
				GetConfig ();
									
				SendMessage(lpSurfPropDlgMem->hWnd,WM_COMMAND,ID_WINSURF_DRAW_MOLS,0);					

				//====== �������� ��������� � ����� ����
				//m_pView->SetLightParam (num, m_Pos[num]);

				//====== �������������� �������� lp �
				//====== ������������� ��� � ��������� nPos
#if 0
				lpSurfPropDlgMem->pSurfDoc->m_LightParam[num] = m_Pos;
				glDeleteLists(FIRST_HARD_LIST+1,N_HARD_LISTS +(GLsizei) lpSurfPropDlgMem->pSurfDoc->m_nglLists);
				lpSurfPropDlgMem->pSurfDoc->m_nglLists = 0;
				DrawScene(lpSurfPropDlgMem->pSurfDoc, true, 1);

				//====== �������������� ��� � ������ ���������
				RECT rect;
				GetClientRect(lpSurfPropDlgMem->hWnd,&rect);
				InvalidateRect(lpSurfPropDlgMem->hWnd,&rect, true);
#endif
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				EndDialog( hDlg, IDOK );
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

WNDPROC wpOrigTreeWndProc; 
 
// Subclass procedure 
LRESULT APIENTRY TreeWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 

    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      // Control wants all keys - All keyboard input         
	} 
	else
    if (uMsg == WM_RBUTTONDOWN || uMsg == WM_LBUTTONDOWN ) 
	{
		int xPos = LOWORD(lParam); // horizontal position of pointer 
		int yPos = HIWORD(lParam); // vertical position of pointer 		}
		if (xPos > 32768) xPos -= 65536;
		if (yPos > 32768) yPos -= 65536;

		//TreeNode* tn = GetNodeAt( xPos, yPos);
		HTREEITEM htiTarget;  // handle to target item 
		TVHITTESTINFO tvht;  // hit test information 
        // Find out if the pointer is on the item. If it is, 
        // highlight the item as a drop target. 
        tvht.pt.x = xPos; 
        tvht.pt.y = yPos; 
        if ((htiTarget = TreeView_HitTest(hwnd, &tvht)) != NULL) 
        { 
            TreeView_SelectDropTarget(hwnd, htiTarget); 
			SendMessage(GetParent(hwnd), WM_USER, 0, (LPARAM) htiTarget);
		}
	}
    return CallWindowProc(wpOrigTreeWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 


static void __cdecl Checking(HWND /*hwndTreeView*/, HTREEITEM /*hParentItem*/, HTREEITEM /*hItem*/, BOOL bCheck, LPARAM lParam)
{
	Object * pObject = reinterpret_cast<Object *> (lParam);
	
	if (pObject)
	{
		pObject->m_bChecked = bCheck != 0;
		//printf("Checking %s %s %d\n", Object::ObjectTypeToString(pObject->GetObjectType()), pObject->GetName().c_str(), pObject->m_bChecked);
	}
}

LRESULT CALLBACK WinSurfParentProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool to_update_check = false;
static HWND hSurfWnd = NULL;
static HWND hwndTV   = NULL;
static HWND hwndLayerList   = NULL;

static RECT treeRect;
static double treeHeigthPart = 0.5;
static RECT clParentRect;

static long sSplit = 7;
//static bool m_bSplit;
static bool m_bCaptured1;
static bool m_bCaptured2;
HCURSOR hCurs2;     // cursor handles 
static HTREEITEM hCurrentTreeItem;


	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
	switch (message) 
	{
		case WM_CREATE :
			{
				//**************************************
//				m_bSplit = false;
				m_bCaptured1 = false;
				m_bCaptured2 = false;
				//**************************************
				// ������� ����������� ������� ���������� � �������
				// ���������� ���������������, ������� ������� �����
				// ����������� � ������������ � ��������� ����������
				// ������� ������������� ����.
				//.............................................................
				CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;

				SetWindowLongPtr(hWnd,	GWLP_USERDATA,(LONG_PTR)pcs->lpCreateParams);
				

				LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
				win_project* pwin_project = (win_project*)userdata;

				
				// #############################################################
				// #############################################################
				// create left window
				hwndTV = CreateATreeView(hWnd, pwin_project);

				// Subclass the control. 
				wpOrigTreeWndProc = (WNDPROC) SetWindowLongPtr(hwndTV, 
					GWLP_WNDPROC, (LONG_PTR) TreeWndSubclassProc); 

				SetWindowLongPtr(hwndTV, GWLP_USERDATA,(LONG_PTR)pwin_project);

				if (pwin_project)
					pwin_project->hwndTV = hwndTV;
				// #############################################################
				// #############################################################
				if (pwin_project)
				{
					 if (pwin_project->m_LayersListViewTab.Init(hWnd, (LPVOID)pwin_project, 0.0, 0.0, 0.0, 0.0))
					 {
						 //pwin_project->m_LayersListViewTab.resize(3,3);
						 hwndLayerList = pwin_project->m_LayersListViewTab.GetWnd();
#if USE_LISTVIEW_STANDART_LL 
						 pwin_project->m_LayersListViewTab.SetCols(1);
#else
						 pwin_project->m_LayersListViewTab.SetCols(2);
#endif
					 }
				}
				 
/*				wpOrigLayerListProc = (WNDPROC) SetWindowLongPtr(hwndLayerList, 
					GWLP_WNDPROC, (LONG_PTR) ListBoxSubclassProc); */
				// #############################################################
				// #############################################################

				GetWindowRect(hwndTV, &treeRect);
				GetClientRect(hWnd, &clParentRect);

				WNDCLASSEX wc;
				// ����������� ������ �������� ���� ����������.
				//............................................
				wc.style         = CS_HREDRAW | CS_VREDRAW;
				//wc.lpfnWndProc   = (WNDPROC)WinSurfProc;
				wc.lpfnWndProc   = (WNDPROC)WndSurfProc;
				wc.cbClsExtra    = 0;
				wc.cbWndExtra    = sizeof(LONG);
				wc.hInstance     = hInst;
				wc.hIcon         = LoadIcon( hInst, lpszWinSurfName );
				wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
				wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
#if VIEW_ONLY_VERSION
				wc.lpszMenuName  = "MYWINSURF_VIEW_ONLY";
#else
				wc.lpszMenuName  = "MYWINSURF";
#endif
				wc.lpszClassName = lpszWinSurf;
				wc.cbSize        = sizeof(WNDCLASSEX);
				wc.hIconSm       = (HICON__ *) LoadImage( hInst, lpszWinSurfName,
											 IMAGE_ICON, 16, 16,
											 LR_DEFAULTCOLOR );

				//**************************************

				if ( !RegisterClassEx( &wc ) )
				{
					if(1410 != GetLastError())// ����� ��� ����������
					{
						MessageBox(0,"!RegisterClassEx","WinSurf",0);
						//return( FALSE );
						hSurfWnd = CreateWindowEx( 
							WS_EX_CLIENTEDGE,
							"EDIT",
							"Here is the Edit Control\n\n!RegisterClassEx",
							WS_CHILD | WS_BORDER | WS_VISIBLE |
							ES_LEFT | ES_MULTILINE,
							treeRect.right, 0,   	 // ���������� ����� ������� 	
							// ���� ����� �������,
							clParentRect.right - treeRect.right, // ����� �� ���������
							clParentRect.bottom, // ��� ����������� �����.
							hWnd,
							(HMENU) 102, 	 // ������������� �������� 	
							// ����������.
							hInst, NULL );
					}
					else
					{
			//			MessageBox(0,"����� ��� ����������","WinSurf",0);
					}
				}
			}
			break;
		case WM_USER:
			{
				hCurrentTreeItem = (HTREEITEM)lParam;
			}
			break;
		case WM_USER + 1:
			{
				hSurfWnd = *((HWND*)lParam);
				SendMessage(hWnd,  WM_COMMAND, ID_WINSURF_VIEW_TREE_WIDGTH, (LPARAM)(treeRect.right-treeRect.left));
				ShowWindow(hSurfWnd, 1);

			}
			break;
#if !USE_LISTVIEW_STANDART_LL
		case WM_USER + 3:
			{
				LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
				win_project* pwin_project = (win_project*)userdata;
				if (pwin_project)
				{
					pwin_project->m_LayersListViewTab.OnEndEdit();
					pwin_project->UpdateLayersNames();
				}
			}
			break; 
#endif
		case WM_CONTEXTMENU :
			{
				if(hCurrentTreeItem)
				{
					LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
					Object * pObject = reinterpret_cast<Object *> (lParam2);
					if(pObject)pObject->CreateContextMenu(hWnd, lParam);
				}
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:


			switch (wmId)
			{
			case ID_TREE_OBJECTSAVEAS:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam);
						if(pObject)pObject->SaveAs();
					}
				}
				break;

			case ID_TREE_OBJECTDELETE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);

						LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						win_project* pwin_project = (win_project*)userdata;							
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()

						if (pSurfDoc && pSurfDoc->IsThisLineForDraw(pObject))
							pSurfDoc->SetLineForDraw(NULL);

						if (pSurfDoc && pSurfDoc->IsThisGridDataForDraw(pObject))
							pSurfDoc->SetGridDataForDraw(NULL);

						if(pObject && pObject->Delete())
						{
							if (pSurfDoc) 
								TreeView_DeleteMyItem(pSurfDoc->hwndTV, hCurrentTreeItem);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;

			case ID_TREE_OBJECTREDRAW:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);

						if(pObject)
						{
							pObject->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;


			case ID_TREE_OBJECTLISTDELETEUNCHECKED:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						ObjectList * pObjectList = dynamic_cast<ObjectList *>(pObject);
						if(pObjectList && pObjectList->DeleteUnchecked())
						{
							/*LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							pSurfDoc->ZoomView();
							pSurfDoc->Draw();*/

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;

			case ID_TREE_OBJECTLISTDELETECHECKED:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						ObjectList * pObjectList = dynamic_cast<ObjectList *>(pObject);
						if(pObjectList && pObjectList->DeleteChecked())
						{
							/*LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							pSurfDoc->ZoomView();
							pSurfDoc->Draw();*/

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;

			case ID_TREE_COLORDIALOG:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						if(pObject && pObject->ColorDialog())
						{
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) pObject->ReDrawItem_OnTree(pSurfDoc->hwndTV);
							pObject->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
			case ID_TREE_OBJECTTOLAYER:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						if(pObject && pObject->ToLayer())
						{
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
			case ID_TREE_GRIDDATA_GRIDDATA:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GridData * pgriddata = dynamic_cast<GridData *>(pObject);
						if(pgriddata && pgriddata->griddata())
						{
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
			/*case ID_TREE_GRIDDATA_GRIDDATAWITHOLESURFER:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GridData * pgriddata = dynamic_cast<GridData *>(pObject);
						if(pgriddata && pgriddata->griddata_by_surfer())
						{
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;*/
			case ID_TREE_GRIDDATA_ADDDATAFROMDATFILE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GridData * pgriddata = dynamic_cast<GridData *>(pObject);
						if(pgriddata)
						{
							pgriddata->AddDataFromDatFile();
						}
					}
				}
				break;
				
			case ID_TREE_GRIDDATA_SETTODRAW:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GridData * pgriddata = dynamic_cast<GridData *>(pObject);
						if(pgriddata)
						{
							pgriddata->SetToDraw();
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							if (pwin_project)
								pwin_project->UpdateAllViews();

						}
					}
				}
				break;
			case ID_TREE_GRIDDATA_UNSETTODRAW:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GridData * pgriddata = dynamic_cast<GridData *>(pObject);
						if(pgriddata)
						{
							pgriddata->UnsetToDraw();
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							if (pwin_project)
								pwin_project->UpdateAllViews();
						}
					}
				}
				break;
			case ID_TREE_GEOSURFASE_GEOSURFACEIZOLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface && pGeoSurface->Izolines())
						{
							pGeoSurface->Zooming();
							pGeoSurface->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
			case ID_TREE_GEOSURFACE_REBUILDBYGRIDDATA:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface && pGeoSurface->RebuildByGridData())
						{
							pGeoSurface->Zooming();
							//pGeoSurface->ReDrawWithoutTree();
							//pGeoSurface->Draw();

							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;

							if (pwin_project)
							{
								pwin_project->Cutting();
								pwin_project->ZoomView();
								pwin_project->Draw();

							}

							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;				
				
			case ID_TREE_GEOSURFACENOBLANK:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface && pGeoSurface->NoBlank())
						{
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
			case ID_TREE_GEOSURFACELOADBLANKLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface && pGeoSurface->LoadBlankBln())
						{
							pGeoSurface->Zooming();
							pGeoSurface->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;

				
			case ID_TREE_GEOSURFASE_PROJECTBLANKLINESONSURFACE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface && pGeoSurface->ProjectBlankLinesOnSurface())
						{
							pGeoSurface->Zooming();
							pGeoSurface->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;

			case ID_TREE_GEOSURFACEBLANK:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface && pGeoSurface->Blank())
						{
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
			case ID_TREE_GEOSURFACEBLANKONBASEPOINT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						win_project* pwin_project = (win_project*)userdata;

						if (pwin_project)
						{
							CPoint3 pt = pwin_project->ZoomInv(ogl_view::what_selected.GetViewPointOfSelection());
							pt.bVisible = true;
							if (pwin_project->m_spheres.SetCurrentMsgOnLast()) pt = pwin_project->m_spheres.GetCurrentMsg().GetFirstDocumentPoint();

							if(pGeoSurface && pGeoSurface->BlankOnBasePoint(pt))
							{
								RECT rect;
								GetClientRect(hSurfWnd,&rect);
								InvalidateRect(hSurfWnd,&rect, true);
							}
						}
					}
				}
				break;
				
				
			case ID_TREE_GEOSURFACEBLANKWITHOWNCUTLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface)
						{
							pGeoSurface->BlankWithOwnCutlines();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
				
			case ID_TREE_GEOSURFACEBLANKWITHOWNCUTLINESONBASEPOINT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						win_project* pwin_project = (win_project*)userdata;

						if (pwin_project)
						{
							CPoint3 pt = pwin_project->ZoomInv(ogl_view::what_selected.GetViewPointOfSelection());
							pt.bVisible = true;
							if (pwin_project->m_spheres.SetCurrentMsgOnLast()) pt = pwin_project->m_spheres.GetCurrentMsg().GetFirstDocumentPoint();
                        
							if(pGeoSurface)
							{
								pGeoSurface->BlankWithOwnCutlinesOnBasePoint(pt);

								RECT rect;
								GetClientRect(hSurfWnd,&rect);
								InvalidateRect(hSurfWnd,&rect, true);
							}
						}
					}
				}
				break;
				
				
			case ID_TREE_GEOSURFACEBLANKWITHOWNBLANKLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface)
						{
							pGeoSurface->BlankWithOwnBlankLines(true, true, NULL);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
				
			case ID_TREE_GEOSURFACECOPYCUTLINESTOBLANKLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface)
						{
							pGeoSurface->CopyCutlinesToBlankLines();
							pGeoSurface->Zooming();
							pGeoSurface->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
			case ID_TREE_GEOSURFACECOPYCUTPLANELINESTOBLANKLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						if(pGeoSurface)
						{
							pGeoSurface->CopyCutPlaneLinesToBlankLines();
							pGeoSurface->Zooming();
							pGeoSurface->ReDraw();

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;
				
				
			case ID_TREE_GEOSURFACEBLANKOFBLANKLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);
						LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						win_project* pwin_project = (win_project*)userdata;

						if (pwin_project)
						{
							CPoint3 pt = pwin_project->ZoomInv(ogl_view::what_selected.GetViewPointOfSelection());
							pt.bVisible = true;
							if (pwin_project->m_spheres.SetCurrentMsgOnLast()) pt = pwin_project->m_spheres.GetCurrentMsg().GetFirstDocumentPoint();
							
							if(pGeoSurface)
							{
								CPoint3 ptMax, ptMin;
								pGeoSurface->BlankingOfBlankLines(&pt, ptMax, ptMin);

								pGeoSurface->Zooming();
								pGeoSurface->ReDraw();

								RECT rect;
								GetClientRect(hSurfWnd,&rect);
								InvalidateRect(hSurfWnd,&rect, true);
							}
						}
					}
				}
				break;
				
				
			case ID_TREE_GEOSURFACEBLANKWITHOWNBLANKLINESONBASEPOINT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						win_project* pwin_project = (win_project*)userdata;

						if (pwin_project)
						{
							CPoint3 pt = pwin_project->ZoomInv(ogl_view::what_selected.GetViewPointOfSelection());
							pt.bVisible = true;
							if (pwin_project->m_spheres.SetCurrentMsgOnLast()) pt = pwin_project->m_spheres.GetCurrentMsg().GetFirstDocumentPoint();
                        
							if(pGeoSurface)
							{
								pGeoSurface->BlankWithOwnBlankLines(true, true, &pt);

								RECT rect;
								GetClientRect(hSurfWnd,&rect);
								InvalidateRect(hSurfWnd,&rect, true);
							}
						}
					}
				}
				break;
			case ID_TREE_GEOSURFASE_GEOSURFACESAVEBLANKLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						if(pGeoSurface)
						{
							pGeoSurface->SaveBlankLines();
						}
					}
				}
				break;
			
			case ID_TREE_GEOSURFACESAVEASSURFER7GRID:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						if(pGeoSurface)
						{
							pGeoSurface->SaveAsSurfer7Grid();
						}
					}
				}
				break;


			case ID_TREE_GEOSURFASE_GRIDVOLUME:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						if(pGeoSurface)
						{
							pGeoSurface->GridVolume();
						}
					}
				}
				break;

			case ID_TREE_WELL_SAVEZONDINPUT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Well_3D * pWell = dynamic_cast<Well_3D *>(pObject);

						if(pWell)
						{
							pWell->SaveAsZondInput();
						}
					}
				}
				break;

			case ID_TREE_CUBE_SAVEAS3DGRID:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Cube4D * pCube = dynamic_cast<Cube4D *>(pObject);

						if(pCube)
						{
							pCube->SaveAs();
						}
					}
				}
				break;		

			case ID_TREE_GEOSURFACEBUILDCUTLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						if(pGeoSurface)
						{
							pGeoSurface->BuildSurfacesCutlines();
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;				
				
			case ID_TREE_SETCOLORFROMCURRENTWELLSSLOJ:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoSurface * pGeoSurface = dynamic_cast<GeoSurface *>(pObject);

						if(pGeoSurface)
						{
							pGeoSurface->SetColorFromCurrentWellsSloj();
							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;				
				
			case ID_TREE_BLNPROFILE_ADDBROKEPOINTSTOLINES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->AddBrokePointsToLines();
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							if (pwin_project)
								pwin_project->UpdateAllViews();
						}
					}
				}
				break;
				
			case ID_TREE_BLNPROFILE_CUTTING:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->Cutting();
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							if (pwin_project)
							{
								pwin_project->UpdateAllViews();
							}
						}
					}
				}
				break;
				

			case ID_TREE_BLNPROFILE_DXFRAZREZ:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->AutoCADRazres();
						}
					}
				}
				break;
			case ID_TREE_BLNPROFILE_SAVEASRAZREZ:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->SaveAsRazres();
						}
					}
				}
				break;
				
			case ID_TREE_BLNPROFILE_CREATEEMPTYLINEOBJECT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) 
								pSurfDoc->SetLineForDraw(pBlnProfile3D->AddLine());

						}
					}
				}
				break;			
			
			case ID_TREE_BLNPROFILE_EDITATTACHES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							if (pBlnProfile3D->EditAttaches())
							{
								RECT rect;
								GetClientRect(hSurfWnd,&rect);
								InvalidateRect(hSurfWnd,&rect, true);
							}
						}
					}
				}
				break;	
			case ID_TREE_BLNPROFILE_GDIMAP:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->ProduceGDIMap();							
						}
					}
				}
				break;
			case ID_TREE_BLNPROFILE_NONSTRETCHEDGDIVIEW:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Profile3D * pProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pProfile3D)
						{
							pProfile3D->SetNonStretched_ProfileMapAttaches();
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							pwin_project->UpdateAllMapExtremums();
							pwin_project->UpdateAllMapViews();
						}
					}
				}
				break;
			case ID_TREE_BLNPROFILE_STRETCHEDGDIVIEW:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Profile3D * pProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pProfile3D)
						{
							pProfile3D->SetStretched_ProfileMapAttaches();
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							pwin_project->UpdateAllMapExtremums();
							pwin_project->UpdateAllMapViews();
						}
					}
				}
				break;
			case ID_TREE_BLNPROFILE_MAP:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->ProduceMap();
						}
					}
				}
				break;
			case ID_TREE_GEOCOLOMN_ADDNEWGEOELEMENT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoColomn * pGeoColomn = dynamic_cast<GeoColomn *>(pObject);

						if(pGeoColomn)
						{
							pGeoColomn->AddNewGeoElement();							
						}
					}
				}
				break;
			case ID_TREE_GEOCOLOMN_ADDEMPTYGEOELEMENT:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoColomn * pGeoColomn = dynamic_cast<GeoColomn *>(pObject);

						if(pGeoColomn)
						{
							pGeoColomn->AddEmptyGeoElement();							
						}
					}
				}
				break;
				
			case ID_TREE_GEOCOLOMN_TOGRIDDATASURFANDCUTTING:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoColomn * pGeoColomn = dynamic_cast<GeoColomn *>(pObject);

						if(pGeoColomn)
						{
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;

							if (!pwin_project->m_cube_size.Defined())
							{
								//SendMessage(hWnd, ID_GEO_CUBESIZE, 0, 0);
								AfxMessageBox("���������� ������� ����������� ����");
								return 0;
							}

							char str[1048];
							sprintf(str, "���������� %s � ��������:\n"
								"������� YES ��� ������ NO\n",
								GeoElement::GeoElementTypeToString(pGeoColomn->m_type) );
							
							int ans = MessageBox(0,str, "", MB_YESNOCANCEL);
							switch (ans)
							{
							case IDYES:
								{
									pGeoColomn->ToGridData(1);
								}
								break;
							case IDNO:
								{
									pGeoColomn->ToGridData(2);
								}
								break;
							default:
								return 0;
							}		




							//bool useSurfer = IDYES == MessageBox(0, "������ �� �� ������������ ����������� ��������� Surfer?", "GeoSurface::RebuildByGridData()", MB_YESNO);
							bool to_allocate = true;
							griddata_dialog(to_allocate, pwin_project, NULL, hWnd, griddata_dialog::griddata_application::unknown, NULL, true, false);

							pwin_project->Cutting();

							pwin_project->UpdateAllMapExtremums();
							pwin_project->UpdateAllViews();
						}
					}
				}
				break;				
			case ID_TREE_GEOCOLOMN_TOGRIDDATA:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoColomn * pGeoColomn = dynamic_cast<GeoColomn *>(pObject);

						if(pGeoColomn)
						{
							char str[1048];
							sprintf(str, "���������� %s � ��������:\n"
								"������� YES ��� ������ NO\n",
								GeoElement::GeoElementTypeToString(pGeoColomn->m_type));
							int ans = MessageBox(0,str, "", MB_YESNOCANCEL);
							switch (ans)
							{
							case IDYES:
								{
									pGeoColomn->ToGridData(1);
								}
								break;
							case IDNO:
								{
									pGeoColomn->ToGridData(2);
								}
								break;
							}		

						}
					}
				}
				break;		
			case ID_TREE_GEOELEMENT_GROUNDTYPE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						EngineerGeoElement * pGeoElement = dynamic_cast<EngineerGeoElement *>(pObject);

						if(pGeoElement)
						{									
							pGeoElement->GroundType();														
						}
					}
				}
				break;
			case ID_TREE_GEOELEMENT_MINALTITUDETOGRIDDATA:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoElement * pGeoElement = dynamic_cast<GeoElement *>(pObject);

						if(pGeoElement)
						{
							pGeoElement->ToGridData(255);																			
						}
					}
				}
				break;
			case ID_TREE_GEOELEMENT_ADDEMPTYGRIDDATA:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoElement * pGeoElement = dynamic_cast<GeoElement *>(pObject);

						if(pGeoElement)
						{
							char str[1048];
							sprintf(str, "���������� %s � ��������:\n"
								"������� YES ��� ������ NO\n",
								pGeoElement->GetKey().c_str());
							int ans = MessageBox(0,str, "", MB_YESNOCANCEL);
							switch (ans)
							{
							case IDYES:
								{
									pGeoElement->AddEmptyGridData(1);
								}
								break;
							case IDNO:
								{
									pGeoElement->AddEmptyGridData(2);
								}
								break;
							}														
						}
					}
				}
				break;
			case ID_TREE_GEOELEMENT_TOGRIDDATA:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						GeoElement * pGeoElement = dynamic_cast<GeoElement *>(pObject);

						if(pGeoElement)
						{
							char str[1048];
							sprintf(str, "���������� %s � ��������:\n"
								"������� YES ��� ������ NO\n",
								pGeoElement->GetKey().c_str());
							int ans = MessageBox(0,str, "", MB_YESNOCANCEL);
							switch (ans)
							{
							case IDYES:
								{
									pGeoElement->ToGridData(1);
								}
								break;
							case IDNO:
								{
									pGeoElement->ToGridData(2);
								}
								break;
							}														
						}
					}
				}
				break;
			case ID_WELLS_USTJATORELIEFGRIDDATA:
				{
					LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					win_project* pwin_project = (win_project*)userdata;
					SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
					if (pSurfDoc) 
						pSurfDoc->UstjaToReliefGriddata();
				}
				break;
			case ID_LOAD_RELIEF_GRIDDATA:
				{
					LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					win_project* pwin_project = (win_project*)userdata;
					SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
					if (pSurfDoc) 
						pSurfDoc->LoadReliefGriddata();
				}
				break;
			case ID_TREE_BLNPROFILE_SAVEASCUBEPROJECTIONGRIDS:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->SavingOfCubeProjectionGrid();							
						}
					}
				}
				break;
			case ID_TREE_BLNPROFILE_PRINTATTACHES:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						BlnProfile3D * pBlnProfile3D = dynamic_cast<BlnProfile3D *>(pObject);

						if(pBlnProfile3D)
						{
							pBlnProfile3D->PrintAttaches();							
						}
					}
				}
				break;	
			case ID_TREE_LINEFREEMIDDLEPOINTS:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Line3D * pLine3D = dynamic_cast<Line3D *>(pObject);

						if(pLine3D)
						{
							pLine3D->FreeMiddlePoints();
							pLine3D->Zooming();
							pLine3D->ReDraw();

							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) pLine3D->ReDrawItem_OnTree(pSurfDoc->hwndTV);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;			
			case ID_TREE_LINE_SHOWUNVISIBLE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Line3D * pLine3D = dynamic_cast<Line3D *>(pObject);

						if(pLine3D)
						{
							pLine3D->ShowUnvisible();
							pLine3D->ReDrawWithoutTree();

							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) pLine3D->ReDrawItem_OnTree(pSurfDoc->hwndTV);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;			
			case ID_TREE_LINE_HIDEUNVISIBLE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Line3D * pLine3D = dynamic_cast<Line3D *>(pObject);

						if(pLine3D)
						{
							pLine3D->HideUnvisible();
							pLine3D->ReDrawWithoutTree();

							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) pLine3D->ReDrawItem_OnTree(pSurfDoc->hwndTV);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;			
			case ID_TREE_LINE_CLOSE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Line3D * pLine3D = dynamic_cast<Line3D *>(pObject);

						if(pLine3D)
						{
							pLine3D->Close();
							pLine3D->Zooming();
							pLine3D->ReDraw();

							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) pLine3D->ReDrawItem_OnTree(pSurfDoc->hwndTV);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;				
			case ID_TREE_LINE_UNCLOSE:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						Line3D * pLine3D = dynamic_cast<Line3D *>(pObject);

						if(pLine3D)
						{
							pLine3D->UnClose();
							pLine3D->Zooming();
							pLine3D->ReDraw();

							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if (pSurfDoc) pLine3D->ReDrawItem_OnTree(pSurfDoc->hwndTV);

							RECT rect;
							GetClientRect(hSurfWnd,&rect);
							InvalidateRect(hSurfWnd,&rect, true);
						}
					}
				}
				break;	
			case ID_TREE_OBJECTSETNAME:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						if(pObject && pObject->SetNameDlg())
						{
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(pwin_project); // from win_graphics_view::GetProject()
							if(pSurfDoc)
								pObject->ReDrawItem_OnTree(pSurfDoc->hwndTV);
						}
					}
				}
				break;


			case ID_TREE_PROPERTIESDIALOG:
				{
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						if(pObject)pObject->PropertiesDialog();
					}
				}
				break;

			case ID_TREE_PROPERTIES_WINDOW:
				{
					printf("ID_TREE_PROPERTIES_WINDOW\n");
					if(hCurrentTreeItem)
					{
						LPARAM lParam2 = TreeView_GetLParam(hwndTV, hCurrentTreeItem);
						Object * pObject = reinterpret_cast<Object *> (lParam2);
						if(pObject)pObject->PropertyWindow(hWnd);
					}
				}
				break;

			/*case ID_WINSURF_VIEW_TREE:
				{
					hCurs2 = LoadCursor(NULL, IDC_SIZEWE);
					if (hCurs2) SetCursor(hCurs2); 
					//====== ����������� ��������� ����,
					//====== ��������� �� � ���� ����
					SetCapture(hWnd);
					//====== ���������� ���� �������
//					m_bSplit = true;

				}
				break;*/
			case ID_WINSURF_VIEW_TREE_WIDGTH:
				{
					// ���������� ������� ������������� ����. ��������
					// ������� ������������ �������� ���������� � ��������
					// ���������� ���������������, ����� ��� ���������������
					// �������� ���������� �������, �� �� ���������� ���
					// �������� ����������.
					//.........................................................
					long treeWidgth = lParam;

					GetClientRect(hWnd, &clParentRect);
					long treeHeigth = (clParentRect.bottom - clParentRect.top) * treeHeigthPart;
					
					HDWP hdwp = BeginDeferWindowPos(3);
					
					hdwp = DeferWindowPos( hdwp, hwndTV, NULL, 
						0, 0,
						treeWidgth, 
						treeHeigth,
						SWP_NOACTIVATE | SWP_NOZORDER |
						SWP_NOMOVE );

					hdwp = DeferWindowPos( hdwp, hwndLayerList, NULL, 
						0, treeHeigth + sSplit,
						treeWidgth, 
						clParentRect.bottom - treeHeigth - sSplit,
						SWP_NOACTIVATE | SWP_NOZORDER );	
					
					hdwp = DeferWindowPos( hdwp, hSurfWnd, NULL, 
						treeWidgth + sSplit, 0,
						clParentRect.right - treeWidgth - sSplit, 
						clParentRect.bottom,
						SWP_NOACTIVATE | SWP_NOZORDER );
					
					EndDeferWindowPos( hdwp );
				}
				break;
			case ID_WINSURF_VIEW_TREE_HEIGTH:
				{
					// ���������� ������� ������������� ����. ��������
					// ������� ������������ �������� ���������� � ��������
					// ���������� ���������������, ����� ��� ���������������
					// �������� ���������� �������, �� �� ���������� ���
					// �������� ����������.
					//.........................................................
					//long treeWidgth = lParam;

					GetWindowRect(hwndTV, &treeRect);
					long treeWidgth = (treeRect.right - treeRect.left);

					long treeHeigth = lParam;

					GetClientRect(hWnd, &clParentRect);
					
					treeHeigthPart = double(treeHeigth) / double (clParentRect.bottom - clParentRect.top);
					
					HDWP hdwp = BeginDeferWindowPos(3);
					
					hdwp = DeferWindowPos( hdwp, hwndTV, NULL, 
						0, 0,
						treeWidgth, 
						treeHeigth,
						SWP_NOACTIVATE | SWP_NOZORDER |
						SWP_NOMOVE );

					hdwp = DeferWindowPos( hdwp, hwndLayerList, NULL, 
						0, treeHeigth + sSplit,
						treeWidgth, 
						clParentRect.bottom - treeHeigth - sSplit,
						SWP_NOACTIVATE | SWP_NOZORDER );	
					
					hdwp = DeferWindowPos( hdwp, hSurfWnd, NULL, 
						treeWidgth + sSplit, 0,
						clParentRect.right - treeWidgth - sSplit, 
						clParentRect.bottom,
						SWP_NOACTIVATE | SWP_NOZORDER );
					
					EndDeferWindowPos( hdwp );
				}
				break;
			default:
				SendMessage(hSurfWnd, message, wParam, lParam);
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_SIZE :
			  {
//MessageBox(0, "WM_SIZE 0", "Parent", 0);
				  // ���������� ������� ������������� ����. ��������
				  // ������� ������������ �������� ���������� � ��������
				  // ���������� ���������������, ����� ��� ���������������
				  // �������� ���������� �������, �� �� ���������� ���
				  // �������� ����������.
				  //.........................................................
				  GetWindowRect(hwndTV, &treeRect);
				  long treeWidgth = (treeRect.right - treeRect.left);
				  long treeHeigth = HIWORD( lParam ) * treeHeigthPart;

				  HDWP hdwp = BeginDeferWindowPos(3);
				  
				  hdwp = DeferWindowPos( hdwp, hwndTV, NULL, 
					  0, 0,
					  treeWidgth, 
					  treeHeigth,
					  SWP_NOACTIVATE | SWP_NOZORDER |
					  SWP_NOMOVE );

				  hdwp = DeferWindowPos( hdwp, hwndLayerList, NULL, 
					  0, treeHeigth + sSplit,
					  treeWidgth, 
					  HIWORD( lParam ) - treeHeigth - sSplit,
					  SWP_NOACTIVATE | SWP_NOZORDER );		

				  hdwp = DeferWindowPos( hdwp, hSurfWnd, NULL, 
					  treeWidgth + sSplit, 0,
					  LOWORD( lParam ) - treeWidgth - sSplit, 
					  HIWORD( lParam ),
					  SWP_NOACTIVATE | SWP_NOZORDER );
//MessageBox(0, "WM_SIZE 6", "Parent", 0);

				 EndDeferWindowPos( hdwp );
//The EndDeferWindowPos function sends the 
//WM_WINDOWPOSCHANGING and WM_WINDOWPOSCHANGED 
//messages to each window identified in the internal structure. 
//MessageBox(0, "WM_SIZE end", "Parent", 0);
			  }
			  break;
		case WM_LBUTTONDOWN :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				/*if (m_bSplit)
				{
					//====== ������� ���� ������� ����
					m_bSplit = false;
					//====== ��������� ��������� ����
					ReleaseCapture();

				}
				else*/
				{
					GetWindowRect(hwndTV, &treeRect);
					long treeWidgth = (treeRect.right - treeRect.left);

					GetClientRect(hWnd, &clParentRect);
					long treeHeigth = (clParentRect.bottom - clParentRect.top) * treeHeigthPart;


					if (fabs((double)(xPos - treeWidgth - sSplit/2)) < sSplit)
					{
						//====== ����������� ��������� ����,
						//====== ��������� �� � ���� ����
						SetCapture(hWnd);
						//====== ���������� ���� �������
						m_bCaptured1 = true;
						//hCurs2 = LoadCursor(NULL, IDC_SIZEWE);
						//if (hCurs2) SetCursor(hCurs2); 
						//else printf(" !LoadCursor\n");
					}

					if (xPos > 0 && xPos < treeWidgth + sSplit && 
						fabs((double)(yPos - treeHeigth - sSplit/2)) < sSplit)
					{
						//====== ����������� ��������� ����,
						//====== ��������� �� � ���� ����
						SetCapture(hWnd);
						//====== ���������� ���� �������
						m_bCaptured2 = true;


						//hCurs2 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR_DIGITIZE));
						//if (hCurs2) SetCursor(hCurs2); 
						//else ErrorExit(" !LoadCursor\n");
					}				
				}
			}
			break;
		case WM_LBUTTONUP :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				if (m_bCaptured1)
				{
					//====== ������� ���� ������� ����
					m_bCaptured1 = false;
					//====== ��������� ��������� ����
					ReleaseCapture();

					SendMessage(hWnd,  WM_COMMAND, ID_WINSURF_VIEW_TREE_WIDGTH, (LPARAM)xPos);
				}
				if (m_bCaptured2)
				{
					//====== ������� ���� ������� ����
					m_bCaptured2 = false;
					//====== ��������� ��������� ����
					ReleaseCapture();

					SendMessage(hWnd,  WM_COMMAND, ID_WINSURF_VIEW_TREE_HEIGTH, (LPARAM)yPos);
				}			
			}
			break;
		case WM_MOUSEMOVE :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;

				GetWindowRect(hwndTV, &treeRect);
				long treeWidgth = (treeRect.right - treeRect.left);

				GetClientRect(hWnd, &clParentRect);
				long treeHeigth = (clParentRect.bottom - clParentRect.top) * treeHeigthPart;

				if (fabs((double)(xPos - treeWidgth - sSplit/2)) < sSplit)
				{
					hCurs2 = LoadCursor(NULL, IDC_SIZEWE);
					if (hCurs2) SetCursor(hCurs2); 
					//else printf(" !LoadCursor\n");
				}

				if (xPos > 0 && xPos < treeWidgth + sSplit && 
					fabs((double)(yPos - treeHeigth - sSplit/2)) < sSplit)
				{
					// Create a custom cursor at run time. 
					hCurs2 = LoadCursor(NULL, IDC_SIZENS);
					if (hCurs2) SetCursor(hCurs2); 
					//else printf(" !LoadCursor\n");
				}				

				if (fabs((double)(xPos - treeWidgth - sSplit/2)) < sSplit && 
					fabs((double)(yPos - treeHeigth - sSplit/2)) < sSplit)
				{
					// Create a custom cursor at run time. 
					hCurs2 = LoadCursor(NULL, IDC_SIZEALL);
					if (hCurs2) SetCursor(hCurs2); 
					//else printf(" !LoadCursor\n");
				}
				if (m_bCaptured1)
				{
//					SendMessage(hWnd,  WM_COMMAND, ID_WINSURF_VIEW_TREE_WIDGTH, (LPARAM)xPos);
				}
				if (m_bCaptured2)
				{
//					SendMessage(hWnd,  WM_COMMAND, ID_WINSURF_VIEW_TREE_HEIGTH, (LPARAM)xPos);
				}
			}
			break;
        case WM_MEASUREITEM: 
			{
				LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				lpmis->itemHeight = YBITMAP3; 	/// � ����� ���������!!!!!!!!!			
				lpmis->itemWidth = 100; 				

				return TRUE; 
			}
			break;
#if !USE_LISTVIEW_STANDART_LL 
        case WM_DRAWITEM: 
			{	
				LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT) lParam; 				
				// If there are no list box items, skip this message. 
				if (lpdis->itemID == -1) 
				{ 
					break; 
				} 
				if (lpdis->hwndItem == hwndLayerList)
				{
					LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					win_project* pwin_project = (win_project*)userdata;
					if (pwin_project)
					{
						pwin_project->m_LayersListViewTab.OnDrawItem(lpdis);
					}
				}
			}
			break;
#endif
		case WM_NOTIFY:
			{
				if (((LPNMHDR) lParam)->hwndFrom == hwndTV)
				{
					//printf("((LPNMHDR) lParam)->code = %d %u\n", ((LPNMHDR) lParam)->code, ((LPNMHDR) lParam)->code);
					switch (((LPNMHDR) lParam)->code)
					{
//					case 4294967279://NM_SETCURSOR            (NM_FIRST-17)
//						return 0;
					case NM_CUSTOMDRAW: //4294967284:(NM_FIRST-12)
						{	
							if (to_update_check)
							{
								//�������� ������������ ������ � ����� ��������� ��������� m_bCheck ��� ���� ��������
								TreeView_EnumCheckedItems(hwndTV, TVI_ROOT, 0, &Checking);

								LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
								win_project* pwin_project = (win_project*)userdata;
								if(pwin_project)
								{
									pwin_project->UpdateAllMapViews();
								}		
								to_update_check = false;
							}
						}						
						break;

					case NM_CLICK :
						{
							LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
							win_project* pwin_project = (win_project*)userdata;
							if(pwin_project)
							{
								pwin_project->UpdateAllGraphicsViews();
							}
							to_update_check = true;
						}
						break;

					case TVN_SELCHANGING :
						//sprintf(str, "TVN_SELCHANGING\n");
						//WriteRaporto(str);
						break;
					case TVN_SELCHANGED :
						{
							NM_TREEVIEW* p = (NM_TREEVIEW*)lParam;
							hCurrentTreeItem = p->itemNew.hItem;

//							sprintf(str, "TVN_SELCHANGED\n");

							HTREEITEM hCur = p->itemNew.hItem;
							HTREEITEM hPre = p->itemOld.hItem;
							UINT action = p->action;
							/*sprintf(str, 
								"TVN_SELCHANGED "
								"hPre = %x "
								"hCur = %x "
								"action = %u "
								"TVIF_CHILDREN = %d "
								"%s "

								"\n",
								
								hPre, 
								hCur,
								action, 
								p->itemNew.mask & TVIF_CHILDREN,
								p->itemNew.mask & TVIF_TEXT ? p->itemNew.pszText : NULL
								); */
							//WriteRaporto(str);
						}
						break;
					case TVN_GETDISPINFO :
						{
						printf("TVN_GETDISPINFO\n");
						//WriteRaporto(str);
						}						
						break;
					case TVN_SETDISPINFO :
						{
						printf("TVN_SETDISPINFO\n");
						//WriteRaporto(str);
						}
						break;
					case TVN_ITEMEXPANDING :
						//sprintf(str, "TVN_ITEMEXPANDING\n");
						//WriteRaporto(str);
						break;
					case TVN_ITEMEXPANDED :
						//sprintf(str, "TVN_ITEMEXPANDED\n");
						//WriteRaporto(str);
						break;
					case TVN_BEGINDRAG :
						//sprintf(str, "TVN_BEGINDRAG\n");
						//WriteRaporto(str);
						break;
					case TVN_BEGINRDRAG :
						//sprintf(str, "TVN_BEGINRDRAG\n");
						//WriteRaporto(str);
						break;
					case TVN_DELETEITEM :
						//sprintf(str, "TVN_DELETEITEM\n");
						//WriteRaporto(str);
						break;
					case TVN_BEGINLABELEDIT :
						//sprintf(str, "TVN_BEGINLABELEDIT\n");
						//WriteRaporto(str);
						break;
					case TVN_ENDLABELEDIT :
						//sprintf(str, "TVN_ENDLABELEDIT\n");
						//WriteRaporto(str);
						break;
					case TVN_KEYDOWN:
						//sprintf(str, "TVN_KEYDOWN\n");
						//WriteRaporto(str);
						break;
					}

				}
				if (((LPNMHDR) lParam)->hwndFrom == hwndLayerList)
				{
					LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
					win_project* pwin_project = (win_project*)userdata;
					if (pwin_project)
					{
						if (pwin_project->m_LayersListViewTab.OnNotify(lParam))
							pwin_project->UpdateAllViews();
						//printf("((LPNMHDR) lParam)->code = %x = %d = %u LVN_FIRST = %x = %d = %u d = %d\n",((LPNMHDR) lParam)->code, ((LPNMHDR) lParam)->code, ((LPNMHDR) lParam)->code, LVN_FIRST, LVN_FIRST, LVN_FIRST, LVN_FIRST - ((LPNMHDR) lParam)->code);
						//if (((LPNMHDR) lParam)->code == LVN_ITEMCHANGED)
						//if (((LPNMHDR) lParam)->code == LVN_ITEMCHANGING)
						//{
						//	LPNMLISTVIEW pnmv = (LPNMLISTVIEW) lParam;
							
							//printf(
							//	"pnmv->iItem = %d\n"
							//	"pnmv->iSubItem = %d\n"
							//	"pnmv->uNewState = %u\n"
							//	"pnmv->uOldState = %u\n"
							//	"pnmv->uChanged = %u\n"
							//	"pnmv->lParam = %d\n"
							//	,
							//	pnmv->iItem,
							//	pnmv->iSubItem,
							//	pnmv->uNewState,
							//	pnmv->uOldState,
							//	pnmv->uChanged,
							//	pnmv->lParam);
						//	if (pnmv->uNewState == 4096 || pnmv->uNewState == 8192)                                
						//		pwin_project->UpdateAllViews();
						//}
#if USE_LISTVIEW_STANDART_LL 
						if (((LPNMHDR) lParam)->code == LVN_ENDLABELEDIT)
							pwin_project->UpdateLayersNames();
#endif
					}
/*					if (
						((LPNMHDR) lParam)->code == NM_CLICK
						||
						((LPNMHDR) lParam)->code == NM_DBLCLK
						)
					{
						RECT rect;
						GetClientRect(hSurfWnd,&rect);
						InvalidateRect(hSurfWnd,&rect, true);
					}*/
				}
			}
			break;
		case WM_MOUSEWHEEL :
		case WM_KEYDOWN :
		case WM_KEYUP :
		case WM_USER + 2:
			{
				SendMessage(hSurfWnd, message, wParam, lParam);
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
   }
   return 0;
}
LRESULT CALLBACK WinSurfProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static	HGLRC		m_hRC;				// �������� OpenGL
	static	HDC			m_hdc; 			// �������� Windows
	static char * pBitmap;
	static HPALETTE hPalette;
	static int      nColorData;

	static GLfloat	m_dx;				// ����� �������� ����� X
	static GLfloat	m_dy;				// ����� �������� ����� Y
	static GLfloat	m_dz;				// ����� �������� ����� Z
	
	static bool		m_bShiftPressed;	// ������� ������� Shift
	static bool		m_bCtrlPressed;		// ������� ������� Ctrl
	static bool		m_bCaptured;		// ������� ������� ����
	static bool		m_bRightButton;		// ���� ������ ������ ����

//	static bool		m_bQuad;			// ���� ������������� GL_QUAD
//	static bool		m_bEqialZoom;		// ����� ���������� ���������
//	static GLenum		m_FillMode;		// ����� ���������� ���������
	static tagPOINT		m_pt;				// ������� ������� ����
	
	static GLfloat	m_AngleView;		// ���� �����������
	static GLfloat	m_xTrans;			// C������� ����� X
	static GLfloat	m_yTrans;			// C������� ����� Y
	static GLfloat	m_zTrans;			// C������� ����� Z
	static GLfloat	m_AngleX;			// ���� �������� ������ ��� X
	static GLfloat	m_AngleY;			// ���� �������� ������ ��� Y
	static GLfloat	m_AngleZ;			// ���� �������� ������ ��� Z

	static bool		m_bPerspective;		// ���� ������������� ������������� ��������


	static GLuint m_listsNumber;

	static LPSURFPROPDLGDATA lpSurfPropDlgMem;
	static LPDRILLSDLGDATA lpDrillsDlgMem;

	static LPSURFZOOMDLGDATA lpSurfZoomDlgMem;
	static LPSURFCUTSPLANEDLGDATA lpSurfCutsPlaneDlgMem;

	static LPSURFDLGDATA lpSurfDlgMem;

	static LPSURFVIEWDLGDATA lpSurfViewDlgMem;

	
#if FAST_GRID_LOADING	
	static Grid* pGrid;
#else
	static CGrid* pCGrid;
#endif
	static LPPRINTSURFDLGDATA		lpPrintDlgMem;
	static LPDEVMODE pDevModeDefault = NULL;
	static LPDEVMODE pDevModeUser = NULL;
	static COLORREF acrCustClr[16]; // array of custom colors 
	static DWORD rgbCurrent;        // initial color selection
	static int i_eq;

		
	static bool		m_bTree;			// ���� ������������� Tree
		
	static HWND hwndTV;    // handle to tree-view control 
	static GLYPHMETRICSFLOAT m_agmf[256];

	static HFONT m_fontLabel, m_fontLabelPrev;
	//static LOGFONT lf_Label;        // logical font structure
	static DWORD rgbCurrent_fontLabel, rgbPrev_fontLabel;   // current text color

		
	static char* pFileName;
	static char fileNameBuf[4096];
	/*if (hWnd == GetDesktopWindow())
	{
		MessageBox(0, "hWnd == GetDesktopWindow()", "WinSurfProc", 0);
		return 0;
	}*/


   switch( uMsg )
   {
      case WM_CREATE  :
		  {
			  CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;

				SetWindowLongPtr(hWnd,	GWLP_USERDATA,(LONG_PTR)pcs->lpCreateParams);
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

				lpSurfPropDlgMem = (LPSURFPROPDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( SURFPROPDLGDATA ) );
				lpSurfPropDlgMem->pSurfDoc = pSurfDoc;
				lpSurfPropDlgMem->hWnd = hWnd;


				lpDrillsDlgMem = (LPDRILLSDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( DRILLSDLGDATA ) );
				lpDrillsDlgMem->hWnd = hWnd;

 

				lpSurfZoomDlgMem = (LPSURFZOOMDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( SURFZOOMDLGDATA ) );
				lpSurfZoomDlgMem->hWnd = hWnd;
				lpSurfZoomDlgMem->pSurfDoc = pSurfDoc;

				lpSurfViewDlgMem = (LPSURFVIEWDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( SURFVIEWDLGDATA ) );
				lpSurfViewDlgMem->hWnd = hWnd;


				lpSurfDlgMem = (LPSURFDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( SURFDLGDATA ) );
				lpSurfDlgMem->hWnd = hWnd;
				lpSurfDlgMem->pSurfDoc = pSurfDoc;


				lpSurfCutsPlaneDlgMem = (LPSURFCUTSPLANEDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( SURFCUTSPLANEDLGDATA ) );
				lpSurfCutsPlaneDlgMem->hWnd = hWnd;
				lpSurfCutsPlaneDlgMem->pSurfDoc = pSurfDoc;


#if FAST_GRID_LOADING
				pGrid = new Grid;
#else
				pCGrid = new CGrid(hWnd);
#endif

				lpPrintDlgMem = (LPPRINTSURFDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( PRINTSURFDLGDATA ) );

				lpPrintDlgMem->bPrinterNameFound;
				lpPrintDlgMem->dmCopies = 1;
				lpPrintDlgMem->dmOrientation = DMORIENT_LANDSCAPE;
				lpPrintDlgMem->dmPaperSize = DMPAPER_A4;
				lpPrintDlgMem->hWnd = hWnd;

				if (Well_3D::s_use_sloj_names)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_WELLS_DRAWSLOJNAMES,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ),
						ID_WELLS_DRAWSLOJNAMES,
						MF_BYCOMMAND | MF_UNCHECKED);
					
				}

				if (Well_3D::s_show_all_sloi)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_WELLS_SHOWALLSLOI,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ),
						ID_WELLS_SHOWALLSLOI,
						MF_BYCOMMAND | MF_UNCHECKED);
					
				}

				if (LabNumber::context_with_results)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHRESULTS,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHRESULTS,
						MF_BYCOMMAND | MF_UNCHECKED);
				}


				if (LabLayer::context_with_lab_number_trial_list)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST,
						MF_BYCOMMAND | MF_UNCHECKED);
				}


				if (LabLayer::context_with_normatives_by_all_experiences)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES,
						MF_BYCOMMAND | MF_UNCHECKED);
				}



				if (LabLayer::context_with_normatives)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHNORMATIVES,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHNORMATIVES,
						MF_BYCOMMAND | MF_UNCHECKED);
				}


				if (CompressionLabTrialResults::compression_module_e_with_min_sq)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_COMPRESSIONWITHMINSQ,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_COMPRESSIONWITHMINSQ,
						MF_BYCOMMAND | MF_UNCHECKED);
				}


/*				if (CompressionLabTrialResults::use_mavrodi_beta)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_USEMAVRODIBETA,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_USEMAVRODIBETA,
						MF_BYCOMMAND | MF_UNCHECKED);
				}*/

				if (Well_3D::ZondFirstTypeMyMethod)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_ZONDFIRSTTYPEMYMETHOD,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_ZONDFIRSTTYPEMYMETHOD,
						MF_BYCOMMAND | MF_UNCHECKED);
				}

				if (BaseLab::PassportLanguage == BaseLab::language::russian)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_PASSPORTUKRAINIANLANGUAGE,
						MF_BYCOMMAND | MF_UNCHECKED);
				}
				else
				{				
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_PASSPORTUKRAINIANLANGUAGE,
						MF_BYCOMMAND | MF_CHECKED);
				}

				if (LabLayer::context_with_korrelation)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHKORRELATION,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHKORRELATION,
						MF_BYCOMMAND | MF_UNCHECKED);
				}

				

				if (Laboratory::context_with_plot)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHPLOT,
						MF_BYCOMMAND | MF_CHECKED);                    
				}
				else
				{					
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_LAB_CONTEXTWITHPLOT,
						MF_BYCOMMAND | MF_UNCHECKED);
				}

				m_bPerspective = true;

				if (m_bPerspective)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_PERSPECTIVE,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_PERSPECTIVE,
						MF_BYCOMMAND | MF_UNCHECKED);
				}

				if (Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
				{

					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_LINES_DRAW_MODE,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{

					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_LINES_DRAW_MODE,
						MF_BYCOMMAND | MF_UNCHECKED);
				}

				if (Object::CanDisableDepthTest())
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_CANDISABLEDEPTHTEST,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_CANDISABLEDEPTHTEST,
						MF_BYCOMMAND | MF_UNCHECKED);
				}


				if (pSurfDoc->m_bDrawCube)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_DRAWCUBE,
						MF_BYCOMMAND | MF_CHECKED);	
				}						
				else						
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_DRAWCUBE,
						MF_BYCOMMAND | MF_UNCHECKED);						

				}
				if (pSurfDoc->m_bDrawGeoid)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_DRAWGEOID,
						MF_BYCOMMAND | MF_CHECKED);			

				}						
				else						
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_DRAWGEOID,
						MF_BYCOMMAND | MF_UNCHECKED);						
				}

				if (pSurfDoc->m_bDrawStatusString)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_STATUS,
						MF_BYCOMMAND | MF_CHECKED);	
				}						
				else						
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFVIEW_STATUS,
						MF_BYCOMMAND | MF_UNCHECKED);	
				}
				if (pSurfDoc->m_bUseColormapOnSurf)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_SURF_USE_PALETTE,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_SURF_USE_PALETTE,
						MF_BYCOMMAND | MF_UNCHECKED);
				}

				if (GeoSurface::s_bInverse_order_in_the_tree)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ),
						ID_SURFS_INVERSEORDERINTHETREE,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_SURFS_INVERSEORDERINTHETREE,
						MF_BYCOMMAND | MF_UNCHECKED);
				}



				if (pSurfDoc->m_bFlatShading)
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_FLAT_SHADING,
						MF_BYCOMMAND | MF_CHECKED);
				}
				else
				{
					CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
						ID_VIEW_FLAT_SHADING,
						MF_BYCOMMAND | MF_UNCHECKED);
				}
              }
              break;
/*
		case WM_NOTIFY: 
			switch (((LPNMHDR)lParam)->code) 
			{
				case TVN_BEGINDRAG:
					//Main_OnBeginDrag is an application-defined function
					Main_OnBeginDrag(hwndTV, (LPNMTREEVIEW)lParam);
					break;
				
				// Handle other cases here. 
			}
			break; 
*/
		case WM_TIMER:
		{
			switch(wParam)
			{
			case IDT_TIMER_SURF:
			//====== ���� ��� ��� ��� ������
				//====== ����������� ���� ��������
				m_AngleX += m_dy;
				m_AngleY += m_dx;
				//====== ������������ ����� �����
				if (m_AngleX > 360)
					m_AngleX -= 360;
				if (m_AngleX <-360)
					m_AngleX += 360;

				if (m_AngleY > 360)
					m_AngleY -= 360;
				if (m_AngleY <-360)
					m_AngleY += 360;

				//====== ������ ������������ ����
				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
				break;
#ifdef USE_EARTHQUAKES_ON_SURF

			case IDT_TIMER_EARTHQUAKES:
				printf("IDT_TIMER_EARTHQUAKES\t");
				printf("vDoc[0].m_Beq.Length() = %d i_eq = %d\n", vDoc[0].m_Beq.Length(), i_eq);
				  if ( i_eq < vDoc[0].m_Beq.Length())
				  {
						//SendMessage(hWnd,WM_COMMAND,ID_WINSURF_DRAW_EARTHQUAKES,0);
						SendMessage(hWnd,WM_USER+3,0,0);
						i_eq++;
				  }
				else
				{
					KillTimer(hWnd,	IDT_TIMER_EARTHQUAKES);    
				}
				break;
#endif
			case IDT_TIMER_MOLS:
				if (GetConfig ())
				{
					SendMessage(hWnd,WM_COMMAND,ID_WINSURF_DRAW_MOLS,0);					
				}
				else
				{
					KillTimer(hWnd,	IDT_TIMER_MOLS);    
				}
				break;
			}
		}
		break;
		case WM_ERASEBKGND:
			{
				return true;
			}
			break;
#ifdef USE_EARTHQUAKES_ON_SURF
			  case WM_USER+3:
				  {
printf("ID_WINSURF_DRAW_EARTHQUAKES\n");

				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						  if ( i_eq < vDoc[0].m_Beq.Length())
						  {

							  double x,y,z;
							  if (Geo2xyz(vDoc[0].m_Beq[i_eq], vDoc[0].m_Leq[i_eq], x, y, z) == 0)
							  {
								  printf("x = %f y = %f z = %f\n", x,y,z);
								  pSurfDoc->AddSphere(CPoint3(x,y,z,true),RGB(255,0,0));
								  /*pSurfDoc->m_spheres.GetLastMsg().ZoomInv(
									  pSurfDoc->zoomX, pSurfDoc->zoomY, pSurfDoc->zoomZ,
									  pSurfDoc->m_xd_zoom_center,
									  pSurfDoc->m_yd_zoom_center,
									  pSurfDoc->m_zd_zoom_center);*/
								  DrawNewSphere(dynamic_cast<SurfDoc *>(pSurfDoc));
								  pSurfDoc->ZoomView();

							  }
						  }
						  //if (i_eq == 2)
							  

						RECT rect;
						GetClientRect(lpSurfDlgMem->hWnd,&rect);
						InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				  }
				  break;
#endif
		case WM_USER+2:
			{
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

				if ( pSurfDoc )
				{
					pSurfDoc->UpdateZofSpheres(wParam, (int*)lParam);
					pSurfDoc->ZoomView();
					pSurfDoc->Draw();
					RECT rect;
					GetClientRect(hWnd, &rect);
					InvalidateRect(hWnd,&rect, true);
				}
			}

      case WM_PAINT :
              {
                 PAINTSTRUCT  ps;
                 BeginPaint( hWnd, &ps );
#if 0
				// move bottom left, southwest of the red triangle 
//				glRasterPos2f(0.0F, 0.0F); 

				// set up for a string-drawing display List call 
				// Display a string 
//				glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
				// Draw the characters in a string 
				glColor3f(0.5f,0.f,0.f);

 				// Set up transformation to draw the string 
				glTranslatef(-4.0f, -2.0f, -1.0f) ;
				//====== ���������� ������
				//glScalef(2.0f, 2.0f, 2.0f); 
				glScalef(0.5f, 0.5f, 0.5f); 
				// set up for a string-drawing display List call 
//				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

				// Display a string 
				glListBase(FIRST_FONT_LIST_OUTLINES); // Indicates the start of display lists for the glyphs 
				// Draw the characters in a string 
				glCallLists(25, GL_UNSIGNED_BYTE, "Hello Win32 OpenGL World."); 
//#else
				glLoadIdentity(); 
				
				// Display a string 
				glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
				// Draw the characters in a string 
				char str[125];
				sprintf(str, "%d",list_base);
				//glCallLists(12, GL_UNSIGNED_BYTE, "Test string1"); 
				glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 

#endif
				SwapBuffers(m_hdc);

				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
				if (pSurfDoc->m_bDrawStatusString)
				{

					HPEN rectPen;
					HPEN boxPen;
					HFONT hFont;

					HFONT hPrintFont;
					RECT rect;
					GetClientRect(hWnd,&rect);

						//======= ������� ����� ��� ��������� ����
					hFont = CreateFont(12,0,0,0,100,0,0,0,DEFAULT_CHARSET,
								OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY,FF_DONTCARE,"Arial");
					//======= ������� ����� ��� ��������� ����
					hPrintFont = CreateFont(72,0,0,0,100,0,0,0,DEFAULT_CHARSET,
								OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY,FF_DONTCARE,"Arial");


					//====== ������� ������ ���� ��� ����������� �����
					rectPen = CreatePen(PS_SOLID, 0, RGB(255,255,255));
					boxPen = CreatePen(PS_SOLID, 0, RGB(0,0,0));

					//====== � ������� ��������� ����������
					//====== ������ ����� ����, ��� �������������
					
					bool isPrint = GetDeviceCaps(m_hdc, TECHNOLOGY) == DT_RASPRINTER;
					bool isMeta = GetDeviceCaps(m_hdc, TECHNOLOGY) == DT_METAFILE;
					bool isWnd = GetDeviceCaps(m_hdc, TECHNOLOGY) == DT_RASDISPLAY;	
					
					//====== ��������� ���������� ������������ �����
					SelectObject(m_hdc, rectPen);

					int border = 20;

					/*

					Rectangle (m_hdc, 0, 0, rect.right, border);
					Rectangle (m_hdc, 0, 0, border, rect.bottom);
					Rectangle (m_hdc, rect.right-border, 0, rect.right, rect.bottom);
					Rectangle (m_hdc, 0, rect.bottom-border, rect.right, rect.bottom);
					

					SelectObject(m_hdc, boxPen);
					MoveToEx(m_hdc, border, border, NULL);
					LineTo(m_hdc, border, rect.bottom-border);
					LineTo(m_hdc, rect.right-border, rect.bottom-border);
					LineTo(m_hdc, rect.right-border, border);
					LineTo(m_hdc, border, border);
					*/

					//====== ������ ���� � ������������ ������
					SetTextColor(m_hdc, 0);
					SetTextAlign(m_hdc, TA_LEFT | TA_BASELINE);

					//====== �������� �����
					if(!isPrint)
						SelectObject (m_hdc, hFont);
					else
						SelectObject (m_hdc, hPrintFont);

					TEXTMETRIC tm;
					GetTextMetrics(m_hdc, &tm); 
					//m_LH = tm.tmHeight;

					char str_angle[255];
					//sprintf(str_angle, "%3.1f:%3.1f:%3.1f  m_pt.x = %d m_pt.y = %d ",m_AngleX, m_AngleY,m_AngleZ, m_pt.x, m_pt.y );
					sprintf(str_angle, "%3.1f:%3.1f:%3.1f",m_AngleX, m_AngleY,m_AngleZ);
					
					char str_trans[255];
					sprintf(str_trans, "%4.2f:%4.2f:%4.2f",m_xTrans, m_yTrans,m_zTrans);

					//====== ������� ���������� �������	
					//char str[32];
					//wsprintf(str,"Min = " );

					TextOut(m_hdc, 2*border, rect.bottom-border+tm.tmHeight, str_angle, strlen(str_angle));
					TextOut(m_hdc, int(rect.right*.8), rect.bottom-border+tm.tmHeight, str_trans, strlen(str_trans));


					SetTextAlign(m_hdc, TA_CENTER | TA_BASELINE);					

					if(rectPen) 
						DeleteObject(rectPen);
					if(boxPen) 
						DeleteObject(boxPen);
					if(hFont) 
						DeleteObject(hFont);
					if(hPrintFont) 
						DeleteObject(hPrintFont);
				}
				EndPaint( hWnd, &ps );
              }
              break;
			  
		case WM_LBUTTONDBLCLK:
			{
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

				//====== ��������� �������� ������������ ������ �����
				//====== ����� ����� �� ���������� ������ �������
				m_zTrans = -1.5f*(float)pSurfDoc->m_fRangeX;
				m_xTrans = 0.f;
				m_yTrans = 0.f;
			}
			break;
		case WM_RBUTTONDOWN :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//====== ���������� ���� ������� ������ ������
				m_bRightButton = true;

				//====== ������������� ������� �� ����� ������
				//====== ������������� ������
				KillTimer(hWnd,IDT_TIMER_SURF);

				//====== �������� ������ �����������
				m_dx = 0.f;
				m_dy = 0.f;

				//====== ����������� ��������� ����,
				//====== ��������� �� � ���� ����
				SetCapture(hWnd);
				//====== ���������� ���� �������
				m_bCaptured = true;
				//====== ���������� ���������� �������
				m_pt.x = xPos;
				m_pt.y = yPos;
			}
			break;

		case WM_LBUTTONDOWN :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//====== ������������� ������
				KillTimer(hWnd,IDT_TIMER_SURF);

				//====== �������� ������ �����������
				m_dx = 0.f;
				m_dy = 0.f;

				//====== ����������� ��������� ����,
				//====== ��������� �� � ���� ����
				SetCapture(hWnd);
				//====== ���������� ���� �������
				m_bCaptured = true;
				//====== ���������� ���������� �������
				m_pt.x = xPos;
				m_pt.y = yPos;

				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//Main_OnLButtonUp();
				if (m_bCaptured)
				{
					//=== �� ����������� �������� ����� �����������
					//=== �� ���������� ������ ����������������
					if (fabs(m_dx) > 0.5f || fabs(m_dy) > 0.5f)
						//=== �������� ����� ����������� ��������
						SetTimer(hWnd,
						/*m_nView * 2 + 1*/IDT_TIMER_SURF,
						33,	                // 10-second interval 
					(TIMERPROC) NULL);     // no timer callback 

					else
						//=== ��������� ����� ����������� ��������
						KillTimer(hWnd, /*m_nView * 2 +1*/IDT_TIMER_SURF);

					//====== ������� ���� ������� ����
					m_bCaptured = false;
					//====== ��������� ��������� ����
					ReleaseCapture();
				}
			}
			break;
		case WM_RBUTTONUP :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;
				//====== ������ ������ ��������
				m_bRightButton = false;
				//====== ������� ���� ������� ����
				m_bCaptured = false;
				//====== ��������� ��������� ����
				ReleaseCapture();
			}
			break;
		case WM_MOUSEMOVE :
			{
				int xPos = LOWORD(lParam); // horizontal position of pointer 
				int yPos = HIWORD(lParam); // vertical position of pointer 		}
				if (xPos > 32768) xPos -= 65536;
				if (yPos > 32768) yPos -= 65536;

				if( wParam &  MK_LBUTTON)
				{
					//Main_OnMouseMove(hWnd, hwndTV, xPos, yPos);
					if (m_bCaptured)		// ���� ��� ������,
					{
						// ��������� ���������� �������� �������� ��������
						m_dy = float(yPos - m_pt.y)/40.f;
						m_dx = float(xPos - m_pt.x)/40.f;

						//====== ���� ������������ ���� ������ Ctrl,
						if (wParam & MK_CONTROL)
						{
							//=== �������� ������������ ������ �����������
							m_xTrans += m_dx;
							m_yTrans -= m_dy;
						}
						else
						{
							if (wParam & MK_SHIFT )
							{
								m_dz = m_dy + m_dx;
								m_AngleZ += (GLfloat)5.0*m_dz;
							}
							else
							{
								//====== �����, �������� ���� ��������
								m_AngleX += m_dy;
								m_AngleY += m_dx;
							}
						}
						//=== � ����� ������ ���������� ����� ��������� ����
						m_pt.x = xPos;
						m_pt.y = yPos;
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
					}
				}
				else
				{
					if	(wParam &  MK_RBUTTON )
					{
						if (m_bCaptured)		// ���� ��� ������,
						{
							// ��������� ���������� �������� �������� ��������
							m_dy = float(yPos - m_pt.y)/40.f;
							m_dx = float(xPos - m_pt.x)/40.f;

							//====== ���� ������������ ���� ������ Ctrl,
							if (wParam & MK_CONTROL)
							{
								//=== �������� ������������ ������ �����������
								m_xTrans += m_dx;
								m_yTrans -= m_dy;
							}
							else
							{
								if (wParam & MK_SHIFT )
								{
									m_dz = m_dy + m_dx;
									m_AngleZ -= (GLfloat)5.0*m_dz;
								}
								else
								{
									//====== ��������� �������� ������
									m_zTrans += (m_dx + m_dy)/2.f;
								}
							}
							//=== � ����� ������ ���������� ����� ��������� ����
							m_pt.x = xPos;
							m_pt.y = yPos;
							RECT rect;
							GetClientRect(hWnd,&rect);
							InvalidateRect(hWnd,&rect, true);
						}
					}
				}
			}
			break;
		case WM_MOUSEWHEEL :
			{
				int zDelta = (int) wParam; // wheel rotation 
				//vView[iWnd].VerticalZoom(hWnd, zDelta, false);
				//unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
				//unsigned short yPos = HIWORD(lParam); // vertical position of pointer 		}
				m_dz = float(zDelta) / 3000000.f;
				//====== ���� ������������ ���� ������ Ctrl,
				if (wParam & MK_CONTROL)
				{
					//=== �������� ������������ ������ �����������
					m_AngleX += m_dz;
				}
				else
				{
					if (wParam & MK_SHIFT )
					{
						m_AngleY += m_dz;
					}
					else
					{
						m_AngleZ += m_dz;
					}
				}

				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
			}
			break;
		case WM_KEYDOWN :
			{
				//char str[255];
				//sprintf(str,"wParam = %d lParam = %d", wParam, lParam);
				//MessageBox(0,str,"WM_KEYDOWN",0);
				switch (wParam)
				{
				case 16:// Shift
					{
						m_bShiftPressed = true;
					}
					break;
				case 17:// Ctrl
					{
						m_bCtrlPressed = true;
					}
					break;
				case 38:// forword
					{
						m_zTrans += 0.05f;
					}
					break;
				case 40:// back
					{
						m_zTrans -= 0.05f;
					}
					break;
				case 37:// left
					{
						if(m_bShiftPressed)
							m_xTrans += 0.02f;
						else
						{
							if (m_bCtrlPressed)//������� �����
								m_AngleZ -= 0.5f;
							else
							{
								float r = (float)sqrt(m_xTrans*m_xTrans + m_zTrans*m_zTrans);
								float alpha = (float)atan2(m_xTrans, m_zTrans);
								alpha -= 0.01f;
								m_AngleZ -= (float)(0.01f*180.f/PI);
								m_zTrans = (float)(r*cos(alpha));
								m_xTrans = (float)(r*sin(alpha));
							}
						}
					}
					break;
				case 39:// right
					{
						if(m_bShiftPressed)
							m_xTrans -= 0.02f;
						else
						{
							if (m_bCtrlPressed)// ������� ������
								m_AngleZ += 0.5f;
							else
							{
								float r = (float)sqrt(m_xTrans*m_xTrans + m_zTrans*m_zTrans);
								float alpha = (float)atan2(m_xTrans, m_zTrans);
								alpha += 0.01f;
								m_AngleZ +=(float)(0.01f*180.f/PI);
								m_zTrans = (float)(r*cos(alpha));
								m_xTrans = (float)(r*sin(alpha));
							}
						}
					}
					break;
				case 33:// page up
					{
						if(m_bShiftPressed)
							m_AngleX += 0.5f;
						else
						{
							if (m_bCtrlPressed)// ������� ������
								m_AngleY += 0.5f;
							else
								m_yTrans -= 0.02f;
						}
					}
					break;
				case 34:// page down
					{
						if(m_bShiftPressed)
							m_AngleX -= 0.5f;
						else
						{
							if (m_bCtrlPressed)// ������� ������
								m_AngleY -= 0.5f;
							else
								m_yTrans += 0.02f;
						}
					}
					break;
				}

				RECT rect;
				GetClientRect(hWnd,&rect);
				InvalidateRect(hWnd,&rect, true);
			}
			break;

		case WM_KEYUP :
			{
				//char str[255];
				//sprintf(str,"wParam = %d lParam = %d", wParam, lParam);
				//MessageBox(0,str,"WM_KEYUP",0);
				switch (wParam)
				{
				case 16:// Shift
					{
						m_bShiftPressed = false;
					}
					break;
				case 17:// Ctrl
					{
						m_bCtrlPressed = false;
					}
					break;
				}
			}
			break;

      case WM_COMMAND :
		  //printf("WM_COMMAND\n");
              switch( LOWORD( wParam ) )
              {
			  case ID_VIEW_IZOLINES:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_IZOLINES),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfIzolines,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
				  
			  case ID_SURF_FILTERS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_FILTERS),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfFilters,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_VIEW_SPHERE_RADIUS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SPHERE_RADIUS),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfSphereRadius,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_WELLS_KAROTAZHSCALE:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_SCALE),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfKarotazhScale,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;	
			  case ID_PROFILES_SAVEOFCUBEPROJECTIONGRIDS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_CUBE_PROJECTION_ON_PROFILE1),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcSavingOfCubeProjectionGrid,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_WELLS_KAROTAZHINTERPOLATION:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_INTERPOLATION),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfKarotazhInterpolation,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;				  
			  case ID_WELLS_KAROTAZHPROJECTION:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_PROJECTION),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfKarotazhProjection,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;	
			  case ID_WELLS_LABDRAWMODE:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_WELLS_LAB_DRAW_MODE),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcWellsLabDrawMode,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;				  
			  /*case ID_WELLS_STATZOND_SVAI:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_STAT_ZOND_SVAI),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcStatZondSvai,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;*/	

				  

			  case ID_VIEW_SAVEBITMAP_2:
				  {
					  // ###########################################################
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  // ###########################################################
					  if (woglv) 
					  {		
						  HANDLE hDialog = LoadResource( hInst,
							  FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SAVE_BITMAP),													  
							  RT_DIALOG ) );

						  LPVOID lpDialog = LockResource( hDialog );
						  HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
							  (DLGPROC)DlgProcSaveBitmap,
							  (LPARAM)hWnd );
						  ShowWindow(hDlg, SW_SHOW);
					  }
				  }
				  break;

			  case ID_VIEW_SURF_TOPAINT:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_TOPAINT),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfToPaint,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
				  
			  case ID_VIEW_ALPHA:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_ALPHA),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfAlpha,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
				  
			  case IDD_SURF_VIEW_ANGLES_TRANS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_VIEW_ANGLES_TRANS),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfViewAnglesTranses,
											(LPARAM)lpSurfViewDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case IDD_SET_SURF_VIEW_ANGLES_TRANS:
				  {
						m_AngleView		= lpSurfViewDlgMem->m_AngleView;
						m_AngleX		= lpSurfViewDlgMem->m_AngleX;
						m_AngleY		= lpSurfViewDlgMem->m_AngleY;
						m_AngleZ		= lpSurfViewDlgMem->m_AngleZ;
						m_xTrans		= lpSurfViewDlgMem->m_xTrans;
						m_yTrans		= lpSurfViewDlgMem->m_yTrans;
						m_zTrans		= lpSurfViewDlgMem->m_zTrans;

						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						fGL ang[3] = { m_AngleX, m_AngleY, m_AngleZ };

						win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
						if (prj) prj->OrbitObject(dynamic_cast<graphics_view *> (wgrv), ang);

						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_VIEW_ZOOM:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_ZOOM),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfZoom,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_HELP_ABOUTSURFCUBE:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_ABOUTSURFCUBEBOX),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcAbout,
											(LPARAM)lpSurfDlgMem );

						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_SURF_COLORMAP:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_PALETTE),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfPalette,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_VIEW_CUTSPLANE:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_CUTS_PLANE),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfCutsPlane,
											(LPARAM)lpSurfCutsPlaneDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;				  
			  case ID_VIEW_CUTSPLANE3:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_CUTS_PLANE3),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfCutsPlane,
											(LPARAM)lpSurfCutsPlaneDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;				  
			  case ID_SURFVIEW_DRAWGEOID:
				  {	
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc->m_bDrawGeoid)
					  {
							pSurfDoc->m_bDrawGeoid = false;
							// delete geoid
							glDeleteLists(FIRST_HARD_LIST+4,1);

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_DRAWGEOID,
								MF_BYCOMMAND | MF_UNCHECKED);						
					  }						
					  else						
					  {
							pSurfDoc->m_bDrawGeoid = true;
							// draw geoid
							InitSphere(FIRST_HARD_LIST+4, pSurfDoc->m_alpha);

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_DRAWGEOID,
								MF_BYCOMMAND | MF_CHECKED);						
					  }
										

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;				  
			  case ID_SURF_BLANKINGOFGEOCATCHBLANKLINES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->BlankingOfGeoCatchBlankLines();	
					  //DrawGeoCatches(pSurfDoc);
					  pSurfDoc->ZoomView();
					  //pSurfDoc->Draw();
					  DrawGeoCatches(pSurfDoc);
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_BLANKGEOCATCHGORIZONTPLANE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->BlankGeoCatchGorizontPlane();	
					  //DrawGeoCatches(pSurfDoc);
					  //pSurfDoc->ZoomView();
					  //pSurfDoc->Draw();
					  //DrawGeoCatches(pSurfDoc);
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_CREATENEWGEOCATCH:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->CreateNewGeoCatch();	
					  DrawGeoCatches(pSurfDoc);
				  }
				  break;
			  case ID_SURF_INITGEOCATCHGORIZONTPLANE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->InitGeoCatch_GorizontPlane();	
					  pSurfDoc->ZoomView();
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_SURF_SURFACESFAULTSCUTLINES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->SurfacesFaultsCutlines();	
					  pSurfDoc->ZoomView();
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_PROFILES_BUILD_INTERSECTIONS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->BlnProfilesIntersectionsBuild();	
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_SURF_SURFACESBLANK:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->SurfacesBlank();	
					  pSurfDoc->ZoomView();
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_FAULTSBLANK:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->FaultsBlank();	
					  pSurfDoc->ZoomView();
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_BROKENPLANESBLANK:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->BrokenPlanesBlank();	
					  pSurfDoc->ZoomView();
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_NOBLANK:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->NoBlank(true);	
					  pSurfDoc->ZoomView();
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_ADDEMPTYLINEOBJECT:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->SetLineForDraw(pSurfDoc->AddLine());				  
					  AddLastLineToTree(pSurfDoc->hwndTV, pSurfDoc);
				  }
				  break;				  
			  case ID_SURFVIEW_STATUS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc->m_bDrawStatusString)
					  {
							pSurfDoc->m_bDrawStatusString = false;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_STATUS,
								MF_BYCOMMAND | MF_UNCHECKED);						
					  }						
					  else						
					  {
							pSurfDoc->m_bDrawStatusString = true;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_STATUS,
								MF_BYCOMMAND | MF_CHECKED);						
					  }
										

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURFVIEW_DRAWCUBE:
				  {
												
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc->m_bDrawCube)
					  {
							pSurfDoc->m_bDrawCube = false;
							// delete cube
							glDeleteLists(FIRST_HARD_LIST+1,1);

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_DRAWCUBE,
								MF_BYCOMMAND | MF_UNCHECKED);						
					  }						
					  else						
					  {
							pSurfDoc->m_bDrawCube = true;
							// draw cube
							DrawCube(pSurfDoc);

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_DRAWCUBE,
								MF_BYCOMMAND | MF_CHECKED);						
					  }
										

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_SURF_ZEROIFBLANKED:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
						{
							do{
								pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetZeroIfBlanked();
							}				
							while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
						}

						pSurfDoc->ZoomView();
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_DRAWQUADSNUMBERS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
						{
							do{
								pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.DrawQuadsNumbers();
							}				
							while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
						}
						pSurfDoc->ZoomView();
						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_VIEW_FILL_FAULTS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  GLenum  m_FillMode;

						if (pSurfDoc->m_faults.SetCurrentMsgOnFirst())
						{
							do{
								m_FillMode = pSurfDoc->m_faults.GetCurrentMsg().m_surface.GetFillMode();
							}				
							while(pSurfDoc->m_faults.IncrementCurrentMsg());
						}

						if (m_FillMode == GL_FILL)
						{
							if (pSurfDoc->m_faults.SetCurrentMsgOnFirst())
							{
								do{
									pSurfDoc->m_faults.GetCurrentMsg().m_surface.SetFillMode(GL_LINE);
								}				
								while(pSurfDoc->m_faults.IncrementCurrentMsg());
							}

							ModifyMenu(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FILL_FAULTS,
								MF_BYCOMMAND | MF_STRING,
								ID_VIEW_FILL_FAULTS,
								"Line->Points->Fill (faults)"
								);

						}
						else
						if (m_FillMode == GL_LINE)
						{
							if (pSurfDoc->m_faults.SetCurrentMsgOnFirst())
							{
								do{
									pSurfDoc->m_faults.GetCurrentMsg().m_surface.SetFillMode(GL_POINT);
								}				
								while(pSurfDoc->m_faults.IncrementCurrentMsg());
							}
							ModifyMenu(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FILL_FAULTS,
								MF_BYCOMMAND | MF_STRING,
								ID_VIEW_FILL_FAULTS,
								"Points->Fill->Line (faults)"
								);
						}
						else
						if (m_FillMode == GL_POINT)
						{
							if (pSurfDoc->m_faults.SetCurrentMsgOnFirst())
							{
								do{
									pSurfDoc->m_faults.GetCurrentMsg().m_surface.SetFillMode(GL_FILL);
								}				
								while(pSurfDoc->m_faults.IncrementCurrentMsg());
							}
							ModifyMenu(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FILL_FAULTS,
								MF_BYCOMMAND | MF_STRING,
								ID_VIEW_FILL_FAULTS,
								"Fill->Line->Points (faults)"
								);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;
			  case ID_VIEW_FILL:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						GLenum  m_FillMode;

						if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
						{
							do{
								m_FillMode = pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.GetFillMode();
							}				
							while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
						}

						if (m_FillMode == GL_FILL)
						{
							if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
							{
								do{
									pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetFillMode(GL_LINE);
								}				
								while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
							}

							ModifyMenu(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FILL,
								MF_BYCOMMAND | MF_STRING,
								ID_VIEW_FILL,
								"Line->Points->Fill (surfaces)"
								);

						}
						else
						if (m_FillMode == GL_LINE)
						{
							if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
							{
								do{
									pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetFillMode(GL_POINT);
								}				
								while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
							}
							ModifyMenu(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FILL,
								MF_BYCOMMAND | MF_STRING,
								ID_VIEW_FILL,
								"Points->Fill->Line (surfaces)"
								);
						}
						else
						if (m_FillMode == GL_POINT)
						{
							if (pSurfDoc->m_surfaces.SetCurrentMsgOnFirst())
							{
								do{
									pSurfDoc->m_surfaces.GetCurrentMsg().m_surface.SetFillMode(GL_FILL);
								}				
								while(pSurfDoc->m_surfaces.IncrementCurrentMsg());
							}
							ModifyMenu(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FILL,
								MF_BYCOMMAND | MF_STRING,
								ID_VIEW_FILL,
								"Fill->Line->Points (surfaces)"
								);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;
			  case ID_VIEW_SURF_USE_PALETTE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						if (pSurfDoc->m_bUseColormapOnSurf)
						{
							pSurfDoc->m_bUseColormapOnSurf = false;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_SURF_USE_PALETTE,
								MF_BYCOMMAND | MF_UNCHECKED);
						}
						else
						{
							pSurfDoc->m_bUseColormapOnSurf = true;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_SURF_USE_PALETTE,
								MF_BYCOMMAND | MF_CHECKED);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_VIEW_LINES_DRAW_MODE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						if (Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_thing_lines)
						{
							Line3D::s_line3d_draw_mode = Line3D::line3d_draw_mode::as_lines_with_spheres;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_LINES_DRAW_MODE,
								MF_BYCOMMAND | MF_CHECKED);
						}
						else
						{
							Line3D::s_line3d_draw_mode = Line3D::line3d_draw_mode::as_thing_lines;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_LINES_DRAW_MODE,
								MF_BYCOMMAND | MF_UNCHECKED);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_VIEW_CANDISABLEDEPTHTEST:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (Object::CanDisableDepthTest())
						{
							Object::CanDisableDepthTest(false);
							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_CANDISABLEDEPTHTEST,
								MF_BYCOMMAND | MF_UNCHECKED);
						}
						else
						{
							Object::CanDisableDepthTest(true);
							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_CANDISABLEDEPTHTEST,
								MF_BYCOMMAND | MF_CHECKED);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_SURFS_INVERSEORDERINTHETREE:
				  {
					  if (GeoSurface::s_bInverse_order_in_the_tree)
					  {
						  GeoSurface::s_bInverse_order_in_the_tree = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_SURFS_INVERSEORDERINTHETREE,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  
						  GeoSurface::s_bInverse_order_in_the_tree = true;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_SURFS_INVERSEORDERINTHETREE,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->Draw();
					  
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_VIEW_FLAT_SHADING:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						if (pSurfDoc->m_bFlatShading)
						{
							pSurfDoc->m_bFlatShading = false;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FLAT_SHADING,
								MF_BYCOMMAND | MF_UNCHECKED);
						}
						else
						{
							pSurfDoc->m_bFlatShading = true;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_VIEW_FLAT_SHADING,
								MF_BYCOMMAND | MF_CHECKED);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_VIEW_QUAD:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_WELLS_DRAWSLOJNAMES:
				  {
					  if (Well_3D::s_use_sloj_names)
					  {
						  Well_3D::s_use_sloj_names = false;
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_WELLS_DRAWSLOJNAMES,
							  MF_BYCOMMAND | MF_UNCHECKED);	
					  }
					  else
					  {
						  Well_3D::s_use_sloj_names = true;
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_WELLS_DRAWSLOJNAMES,
							  MF_BYCOMMAND | MF_CHECKED);	
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_WELLS_SHOWALLSLOI:
				  {
					  if (Well_3D::s_show_all_sloi)
					  {
						  Well_3D::s_show_all_sloi = false;
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_WELLS_SHOWALLSLOI,
							  MF_BYCOMMAND | MF_UNCHECKED);	
					  }
					  else
					  {
						  Well_3D::s_show_all_sloi = true;
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_WELLS_SHOWALLSLOI,
							  MF_BYCOMMAND | MF_CHECKED);	
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_WELLS_DRAW_ID_KT:
				  {
					  if (Well_3D::s_drawIdKt)
					  {
						  Well_3D::s_drawIdKt = false;
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_WELLS_DRAW_ID_KT,
							  MF_BYCOMMAND | MF_UNCHECKED);	
					  }
					  else
					  {
						  Well_3D::s_drawIdKt = true;
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_WELLS_DRAW_ID_KT,
							  MF_BYCOMMAND | MF_CHECKED);	
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURFVIEW_PERSPECTIVE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						
					  if (m_bPerspective)
						{
							m_bPerspective = false;
							win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
							wgrv->popup_ProjOrthographic(hWnd, NULL);

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_PERSPECTIVE,
								MF_BYCOMMAND | MF_UNCHECKED);
						}
						else
						{
							m_bPerspective = true;

							win_graphics_view * wgrv = dynamic_cast<win_graphics_view *>(woglv);
							wgrv->popup_ProjPerspective(hWnd, NULL);

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_SURFVIEW_PERSPECTIVE,
								MF_BYCOMMAND | MF_CHECKED);
						}
						/*SendMessage(hWnd, WM_SIZE, 0, 0);


						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);*/
				  }
				  break;

			  case ID_WINSURF_VIEW_TREE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						if (m_bTree)
						{
							m_bTree = false;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_WINSURF_VIEW_TREE,
								MF_BYCOMMAND | MF_UNCHECKED);

							DestroyWindow(hwndTV); 
						}
						else
						{
							m_bTree = true;

							CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
								ID_WINSURF_VIEW_TREE,
								MF_BYCOMMAND | MF_CHECKED);

							hwndTV = CreateATreeView(hWnd, pSurfDoc);
						}

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

					  
				  }
				  break;
			  case ID_WINSURF_FILE_PLAY_MOLS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_PLAY_MOLS),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcPlayMols,
											(LPARAM)lpSurfPropDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_SURF_LIGHT_PROP:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_PROP),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfProp,
											(LPARAM)lpSurfPropDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_TREE_LAB_WELLELEMENTPROP:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabWellElementProp();
				  }
				  break;
			  case ID_TREE_LAB_WELLELEMENTPROPSAVE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabWellElementPropSave();
				  }
				  break;

			  case ID_TREE_LAB_PASSPORT:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabWellElementPassport();
				  }
				  break;


			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT0:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT1:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT2:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT3:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_TITLE:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XLABEL:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YLABEL:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_XAXES:
			  case ID_TREE_LAB_WELLELEMENTCONTEXTFONT_PLOT_YAXES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabWellElementPropFont(LOWORD( wParam ));
				  }
				  break;
			  
			  case ID_TREE_LAB_GURVICH_Y_SECOND_DERIVATIVE_LIMIT:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabGurvichYSecondDerivativeLimit();
				  }
				  break;	
			  
			  case ID_TREE_LAB_E_SECOND_DERIVATIVE_LIMIT:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabCompressionESecondDerivativeLimit();
				  }
				  break;	

			  case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabCompressionPressure();
				  }
				  break;
			  case ID_TREE_LAB_LABLAYER_COMPRESSION_PRESSURE_INTERVAL:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabCompressionPressureInterval();
				  }
				  break;
			  case ID_TREE_LAB_WELLELEMENTCONTEXTPLOTHEIGHT:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabWellElementPropPlotHeight();
				  }
				  break;
			  case ID_TREE_LAB_WATERSATURATEDPARTOFFULLWATERCAPACITY:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  prj->LabWaterSaturatedPartOfFullWaterCapacity();
				  }
				  break;
			  case ID_SURF_CLEAR:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearSurf();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;
			  case ID_CLEAR_CLEARGEOCOLOMNS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearGeoColomns();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;

			  case ID_CLEAR_CLEARCUBES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearCubes();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;
			  case ID_SURF_CLEAR_FAULTS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearFaults();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;				  
			  case ID_CLEAR_CLEARIZOLINES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearIzolines();
					  //pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_CLEARCUTLINES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearCutLines();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_CLEARLINES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						
					  pSurfDoc->ClearLines();
					  pSurfDoc->SetLineForDraw(NULL);
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_CLEARSPHERES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearSpheres();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURFTEST_REGISTER:
				  {
					   LONG  lResult;
					   HKEY  hKeyResult = 0;
					   DWORD dwDisposition = 0;
					   CommandLineParser parser;
					   parser.DoParsing();

					   // ������� ��������� ���������� ���������� "Geo Surf Cube Document".
					   //................................
					   lResult = RegCreateKeyEx( HKEY_CLASSES_ROOT,
                       					"Geo Surf Cube Document\\shell\\Open\\command", 0, "",
										REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
								NULL, &hKeyResult, &dwDisposition );

					   // ������������ NotePad ��� �������� ���������.
					   //..................................
					   if ( lResult == ERROR_SUCCESS )
					   {

						   char command[4096];//"NotePad %1"
						   strcpy(command, parser.module);
						   strcat(command, " -open %1");
						   printf("command = %s\n", command);
						 lResult = RegSetValueEx( hKeyResult, NULL, 0, REG_SZ,
							 (const BYTE *)command, DWORD(strlen(command)) );
						 RegCloseKey( hKeyResult );
					   }

					   // ������� ������������ �� ��������� ����������� 
					   // DefaultIcon ��� ��������� Geo Surf Cube Document
					   //.................................
					   lResult = RegCreateKeyEx( HKEY_CLASSES_ROOT,
								 "Geo Surf Cube Document\\DefaultIcon", 0, 
							   "", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS,
								 NULL, &hKeyResult, &dwDisposition );


					   // ���������� ������������ �� ��������� �����������.
					   //......................
					   if ( lResult == ERROR_SUCCESS )
					   {
#if 0
						   char * defaultIcon = "%SystemRoot%\\system32\\shell32.dll,1";
#else

						   char defaultIcon[4096];
						   sprintf(defaultIcon, "%s\\icon1.ico", parser.path);
#endif
						   printf("defaultIcon = %s\n", defaultIcon);
						 lResult = RegSetValueEx( hKeyResult, NULL, 0, REG_SZ,
							 (const BYTE *)defaultIcon,
							   DWORD(strlen(defaultIcon)) );
						 RegCloseKey( hKeyResult );
					   }

					   // ������� ����� � ����������� ����� .gsf.
					   //.......................................
					   lResult = RegCreateKeyEx( HKEY_CLASSES_ROOT, ".gsf",
                       						 0, "", REG_OPTION_NON_VOLATILE,
											 KEY_ALL_ACCESS, NULL, 
									 &hKeyResult, &dwDisposition );

					   // ������� ���������� ����� .gsf � ����� ��������� Geo Surf Cube Document.
					   //..............................
					   if ( lResult == ERROR_SUCCESS )
					   {
						   char * document = "Geo Surf Cube Document";
						 lResult = RegSetValueEx( hKeyResult, NULL, 0, REG_SZ,
                         					(const BYTE *)document, DWORD(strlen(document)) );
						 RegCloseKey( hKeyResult );
					   }

					   // ������� ����� � ����������� ����� .cub.
					   //.......................................
					   lResult = RegCreateKeyEx( HKEY_CLASSES_ROOT, ".cub",
                       						 0, "", REG_OPTION_NON_VOLATILE,
											 KEY_ALL_ACCESS, NULL, 
									 &hKeyResult, &dwDisposition );

					   // ������� ���������� ����� .gsf � ����� ��������� Geo Surf Cube Document.
					   //..............................
					   if ( lResult == ERROR_SUCCESS )
					   {
						   char * document = "Geo Surf Cube Document";
						 lResult = RegSetValueEx( hKeyResult, NULL, 0, REG_SZ,
                         					(const BYTE *)document, DWORD(strlen(document)) );
						 RegCloseKey( hKeyResult );
					   }

					   MessageBox( hWnd,
							"Geo Surf Cube Document (.gsf) has been registered in the registry",
							"RegCreateKeyEx()", MB_OK | MB_ICONINFORMATION );
				  }
				  break;
			  case ID_SURFTEST_UNREGISTER:
				  {
					   HKEY  hKeyResult = 0;
					   LONG  lResult = RegOpenKeyEx( HKEY_CLASSES_ROOT,
                            					 "Geo Surf Cube Document\\shell\\Open\\command", 
									 0, KEY_ALL_ACCESS, &hKeyResult );
					   // ������� ����������� ��������.
					   //......................
					   if ( lResult == ERROR_SUCCESS )
					   {
						 lResult = RegDeleteValue( hKeyResult, NULL );
						 RegCloseKey( hKeyResult );
					   }

					   lResult = RegOpenKeyEx( HKEY_CLASSES_ROOT,
                       					   "Geo Surf Cube Document\\DefaultIcon", 
								   0, KEY_ALL_ACCESS, &hKeyResult );
					   // ������� ����������� ��������.
					   //......................
					   if ( lResult == ERROR_SUCCESS )
					   {
						 lResult = RegDeleteValue( hKeyResult, NULL );
						 RegCloseKey( hKeyResult );
					   }

					   // ������� �����. ��� �������� ������ ���� ������� ����� 
					   // ��������� ������������ ������. ��� �����������, 
					   // ������������� �������� RegDeleteKey().
					   //.....................................................
					   RegDeleteKey( HKEY_CLASSES_ROOT,
									 "Geo Surf Cube Document\\shell\\Open\\command" );
					   RegDeleteKey( HKEY_CLASSES_ROOT, "Geo Surf Cube Document\\shell\\Open" );
					   RegDeleteKey( HKEY_CLASSES_ROOT, "Geo Surf Cube Document\\shell" );
					   RegDeleteKey( HKEY_CLASSES_ROOT, "Geo Surf Cube Document\\DefaultIcon" );
					   RegDeleteKey( HKEY_CLASSES_ROOT, "Geo Surf Cube Document" );
					   RegDeleteKey( HKEY_CLASSES_ROOT, ".gsf" );

					   MessageBox( hWnd,
                    			  "Geo Surf Cube Document (.gsf) has been removed from the registry",
                    			  "RegCreateKeyEx()", MB_OK | MB_ICONINFORMATION );
				  }
				  break;
			  case ID_SURFTEST_CREATEPALLETEFILE:
				  {
					  FILE *stream;
					  const int n= 1024*32;
					  int rows, cols;
					  char szBuff[n];
					  char *p1, *p2;
					  char filename[1024];
					  if (OpenFileDlg(hWnd, "Matlab generated palette files(*.txt)\0*.txt\0All files \0*.*\0", filename) == S_OK)
					  {
						  
						  // open input text file for read
						  if(NULL == (stream = fopen(filename, "rt")))
						  {
							  MessageBox(0,filename, "file not found",0);
							  break;
						  }
						  // replace extension on filename
						  char * p;
						  p = strrchr(filename,'.');
						  if (p) strcpy(p,".dat");


						  // create file for write
						  HANDLE hFile;
						  if(NULL == (hFile = 
							  CreateFile(filename,
							  GENERIC_WRITE, 0, 0, CREATE_ALWAYS,
							  0,0)))
						  {
							 MessageBox(0,filename, "file not found",0);
							 break;
						  }
						  // get rows and cols count
						  fgets(szBuff,n,stream);
						  sscanf(szBuff,"%d %d", &rows, &cols);
						  DWORD wdWritten;
						  WriteFile(hFile,&rows,sizeof(int),&wdWritten,0);
						  WriteFile(hFile,&cols,sizeof(int),&wdWritten,0);
						  for (int r = 0; r<rows; r++)
						  {
							  fgets(szBuff,n,stream);// read row							  
							  p1=szBuff;
							  for(int c = 0; c<cols; c++)
							  {
								  //double data = atof(p1);
								  BYTE data = BYTE(atoi(p1));
								  p2 =  strchr(p1,' ');
								  if (p2==NULL)
								  {
									  MessageBox(0, "�������� ������ �����\n", "", 
										  MB_OK | MB_ICONINFORMATION);
									  fclose(stream);
									  return 0;
								  }
								  p1 = p2+1;
								  //WriteFile(hFile,&data,sizeof(double),&wdWritten,0);
								  WriteFile(hFile,&data,sizeof(BYTE),&wdWritten,0);
							  }
						  }
						  CloseHandle(hFile);
						  fclose(stream);
						  sprintf(szBuff, "����������� �������� ���� ������� ��� �������� � ������� �++:\n%s",
							  filename);
						  MessageBox(0, szBuff, "", MB_OK | MB_ICONINFORMATION);

					 }
				  }
				  break;				  
			  case ID_SURF_CLEARTRIANGLES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearTriangles();


						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURFTEST_FONT2:
				  {
					//======= ������� ����� ��� ��������� ����
					HFONT m_font = CreateFont(8,0,0,0,100,0,0,0,DEFAULT_CHARSET,
								OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
								DEFAULT_QUALITY,FF_DONTCARE,"Arial");
					SelectObject (m_hdc, m_font);


					//====== �������� ������� ��� � �������� ��������
					if ( !wglMakeCurrent (m_hdc, m_hRC))
					{
						MessageBox(hWnd,"wglMakeCurrent::Error","On Create",0);
						return 0;
					}
					if ( !wglUseFontOutlines(m_hdc, 0, 255, FIRST_FONT_LIST_OUTLINES, 0.0f, 0.1f,  
#if 1
								WGL_FONT_POLYGONS, 
#else
								WGL_FONT_LINES,
#endif
								m_agmf))
					{
						ErrorExit("wglUseFontOutlines");
						return 0;
					} 
				  }
				  break;
				  
			  case ID_SURF_CLEARPOLIGONES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearPoligones();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
				  
			  case ID_CLEAR_CLEARKAROTAZHLIST:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearKarotazhList();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_CLEAR_CLEARKAROTAZHY:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearKarotazhy();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_SURF_CLEARDRILLS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						pSurfDoc->ClearDrills();

						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
				  
			  case ID_SURF_CLEARSTRINGS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearStrings();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
				  
				  
			  case ID_CLEAR_CLEARBLNPROFILES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearBlnProfiles();

					  pSurfDoc->SetLineForDraw(NULL);
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

				  
			  case ID_CLEAR_CLEARBITMAPS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearBitmaps();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_CLEAR_CLEARBMPPROFILES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearBmpProfiles();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;


			  case ID_CLEAR_CLEAROBJECTS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearObjects();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_CLEAR_CLEARCOLLECTIONS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearCollections();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_CLEAR_CLEARGRIDDATA:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  pSurfDoc->SetGridDataForDraw(NULL);					  
					  pSurfDoc->ClearGridData();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;


			  case ID_CLEAR_CLEARGEOCATCHES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearGeoCatches();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_CLEAR_CLEARAUTOBUILDPROFILES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearAutoBuildProfiles();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;
				  
			  case ID_CLEAR_CLEARBLANKLINES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearBlankLines();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

				  
			  case ID_CLEAR_CLEARCUTLINESPOLYGONES:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearCutlinesPolygones();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

				  
			  case ID_CLEAR_CLEARPOINTS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearPoints();
					  
					  pSurfDoc->Draw();
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_WINSURF_DRAW:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						int zflag = 0;

						if (lParam == 0)
						{
							zflag = 0;
						}
						else
						{
							int answer = MessageBox(0, 
								"Fault loading\n"
								"Select fault type \n"
								"If x->z (zflag == 1) press YES\n"
								"If y->z (zflag == 2) press NO\n"
								"If z->z (zflag == 3) press CANCEL\n"
								"\n"
								"�������� �������\n"
								"�������� ��� ������ ���������\n"
								"���� Z �������� �� X (zflag == 1) ������� YES\n"
								"���� Z �������� �� Y (zflag == 2) ������� NO\n"
								"���� Z �������� �� Z (zflag == 3) ������� CANCEL\n"
								"������ ��� ���� �������� ��� ��������������� ��������\n"
								"������ ��� - ��� �����������������\n"
								, 								
								"�������� �������", 
								MB_YESNOCANCEL | MB_ICONQUESTION);
							if ( answer == IDYES)
							{
								zflag = 1;
							}
							if ( answer == IDNO)
							{
								zflag = 2;
							}
							if ( answer == IDCANCEL)
							{
								zflag = 3;
							}
						}

						COLORREF color;
						if (lParam == 0)
						{
							color = RGB(255,255,0);
							ChooseSurfColor(hWnd, color);
						}
						else
						{
							color = RGB(255,0,0);
							
						}

						long id_surf = pSurfDoc->GetIDSurfForNewGridDataOrSurface();
						BYTE podoshva = 0; long id_ige = -1;
#if FAST_GRID_LOADING
						pSurfDoc->AddSurf(id_surf, podoshva, id_ige, zflag, pGrid, color);
#else
						pSurfDoc->AddSurf(id_surf, podoshva, zflag, id_ige, pCGrid, color);
#endif

						if (zflag == 0)
						{
							if (pSurfDoc->m_surfaces.SetCurrentMsgOnLast() && pSurfDoc->m_surfaces.msgSize() > 1)
							{								
								DrawNewSurf(pSurfDoc);
							}
							else
							{
								pSurfDoc->ZoomView();
								DrawSurfs(pSurfDoc);
							}

						}
						else
						{
							if (pSurfDoc->m_faults.SetCurrentMsgOnLast() && pSurfDoc->m_faults.msgSize() > 1)
							{
								DrawNewFault(pSurfDoc);
							}
							else
							{
								pSurfDoc->ZoomView();
								DrawFaults(pSurfDoc);
							}
						}
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;
			  case ID_PROFILES_CREATEONWELLS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_PROFILE_CREATE_ON_WELLS),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcCreateProfileOnWells,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_PROFILES_CUTTING:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->Cutting();
					  win_project* pwin_project = dynamic_cast<win_project*>(pSurfDoc);
					  if (pwin_project) pwin_project->UpdateAllViews();
				  }
				  break;
			  case ID_WINSURF_FILE_IMPORT_PROFILE:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURF_IMPORT_PROFILE),
													  RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfImportProfile,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
#if !FAST_GRID_LOADING
			  case ID_WINSURF_FILE_SAVEAS_SURFER7_GRID :
				  {
						if (MessageBox(0, "Do you want to save contured Surfer7 grid?", "Surf", 
							MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
						{
							TCHAR lpstrFile[256];
							sprintf(lpstrFile, "%s\\out7_contured.grd", directory);
							pCGrid->SaveAsSurferGrid7(lpstrFile);
						}
				  }
				  break;
#endif
			  case ID_SURF_FON_COLOR:
				  {
						CHOOSECOLOR cc;                 // common dialog box structure 
						HBRUSH hbrush;                  // brush handle
						//static COLORREF acrCustClr[16]; // array of custom colors 
						//static DWORD rgbCurrent;        // initial color selection

						// Initialize CHOOSECOLOR 
						ZeroMemory(&cc, sizeof(cc));
						cc.lStructSize = sizeof(cc);
						cc.hwndOwner = hWnd;
						cc.lpCustColors = (LPDWORD) acrCustClr;
						cc.rgbResult = rgbCurrent;
						cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
						if (ChooseColor(&cc)==TRUE) {
							hbrush = CreateSolidBrush(cc.rgbResult);
							rgbCurrent = cc.rgbResult; 
						}
						glClearColor (float(GetRValue(rgbCurrent))/255.f, float(GetGValue(rgbCurrent))/255.f,float(GetBValue(rgbCurrent))/255.f, 1.f); 
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;				  
			  case ID_WINSURF_FILE_IMPORT_FAULT_GRID:
				  {
					  						
					  char grd_file[2048];

					  if (OpenFileDlg(hWnd, "Surfer 7 (*.grd)\0*.grd\0All files \0*.*\0", grd_file) == S_OK)
					  {
#if !FAST_GRID_LOADING
						  Grid* pGrid = new Grid;
#endif
						  if (pGrid == NULL) 
						  {
							  MessageBox(0, "pGrid == 0", "ID_WINSURF_FILE_IMPORT_GRID", MB_OK | MB_ICONEXCLAMATION); 
							  return -1;
						  }
						  if(ImportSurfer7Grid(grd_file, pGrid) == 0)
						  {
#if !FAST_GRID_LOADING
								pCGrid->Init(pGrid);
#endif
								SendMessage(hWnd, WM_COMMAND, ID_WINSURF_DRAW, 1);
								// free 
								if (pGrid->gridSection.z) 
								{
									//HeapFree( GetProcessHeap(), 0, pGrid->z); 
									FreeDoubleMat(pGrid->gridSection.z);
									pGrid->gridSection.z = NULL;
								}
								if (pGrid->faultSection.traces)
								{
									delete[] pGrid->faultSection.traces;
									pGrid->faultSection.traces = NULL; 
									pGrid->faultSection.nTraces = 0;
								}								
								if (pGrid->faultSection.vertexes)
								{
									delete[] pGrid->faultSection.vertexes;
									pGrid->faultSection.vertexes = NULL; 
									pGrid->faultSection.nVertices = 0;
								}
						  }						  							  
#if !FAST_GRID_LOADING
						  if (pGrid) delete pGrid;
#endif
					  }
				  }
				  break;
			  case ID_WINSURF_FILE_IMPORT_GRID:
				  {
					  char grd_file[2048];
					  printf("ID_WINSURF_FILE_IMPORT_GRID\n");
					  if (OpenFileDlg(hWnd, "Surfer 7 (*.grd)\0*.grd\0All files \0*.*\0", grd_file) == S_OK)
					  {
						  printf("ID_WINSURF_FILE_IMPORT_GRID 2\n");
#if !FAST_GRID_LOADING
						  Grid* pGrid = new Grid;
#endif
						  if (pGrid == NULL) 
						  {
							  MessageBox(0, "pGrid == 0", "ID_WINSURF_FILE_IMPORT_GRID", MB_OK | MB_ICONEXCLAMATION); 
							  return -1;
						  }
						  printf("ID_WINSURF_FILE_IMPORT_GRID 3\n");
						  if(ImportSurfer7Grid(grd_file,pGrid) == 0)
						  {
							  printf("ID_WINSURF_FILE_IMPORT_GRID 4\n");
#if !FAST_GRID_LOADING
							  //�������� �������� ��� ������������� ������ CGrid
							  pCGrid->Init(pGrid);
#endif
							  SendMessage(hWnd, WM_COMMAND, ID_WINSURF_DRAW, 0);
								// free 
								if (pGrid->gridSection.z) 
								{
									//HeapFree( GetProcessHeap(), 0, pGrid->z); 
									FreeDoubleMat(pGrid->gridSection.z);
									pGrid->gridSection.z = NULL;
								}
								if (pGrid->faultSection.traces)
								{
									delete[] pGrid->faultSection.traces;
									pGrid->faultSection.traces = NULL; 
									pGrid->faultSection.nTraces = 0;
								}								
								if (pGrid->faultSection.vertexes)
								{
									delete[] pGrid->faultSection.vertexes;
									pGrid->faultSection.vertexes = NULL; 
									pGrid->faultSection.nVertices = 0;
								}
						  }		
						  else
							  printf("ImportSurfer7Grid return error\n");
#if !FAST_GRID_LOADING
						  if (pGrid) delete pGrid; 
#endif
					  }
				  }
				  break;
#ifdef USE_EARTHQUAKES_ON_SURF
/*
			  case ID_WINSURF_DRAW_EARTHQUAKES:
				  {
printf("ID_WINSURF_DRAW_EARTHQUAKES\n");

				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						  if ( i_eq < vDoc[0].m_Beq.Length())
						  {

							  double x,y,z;
							  if (Geo2xyz(vDoc[0].m_Beq[i_eq], vDoc[0].m_Leq[i_eq], x, y, z) == 0)
							  {
								  printf("x = %f y = %f z = %f\n", x,y,z);
printf("ID_WINSURF_DRAW_EARTHQUAKES pre glNewList\n");
								pSurfDoc->m_DrawListArray.glNewList();
printf("ID_WINSURF_DRAW_EARTHQUAKES post glNewList\n");
							
								GLUquadricObj* pSphere = gluNewQuadric();
								gluQuadricDrawStyle(pSphere, GLU_FILL);

								glPushMatrix();//������� � ����� �����������, �������� ������
								glTranslated(
										x, 
										y, 
										z
										);
								//COLORREF sphereColor = pSurfDoc->m_vSphereColor.GetCurrentMsg();
								glColor3ub (255,0,0); 

								gluSphere(pSphere, 0.02, 20, 20) ;//������ ����� 
								glPopMatrix(); //������������ � ������ ����������� 
								gluDeleteQuadric(pSphere);
							
							glEndList();
							  }
						  }

						RECT rect;
						GetClientRect(lpSurfDlgMem->hWnd,&rect);
						InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				  }
				  break;*/
#endif
			  case ID_WINSURF_DRAW_MOLS:
				  {
					  vdouble xi,yi,zi;
					  vdouble xl,yl,zl;
#if LINK_MATR
					  xl.resize(2);
					  yl.resize(2);
					  zl.resize(2);
#else
					  xl.resize(chainLen);
					  yl.resize(chainLen);
					  zl.resize(chainLen);
#endif /*LINK_MATR*/

					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  pSurfDoc->ClearLines();
#if LINK_MATR
					  int j1,j2;
						
					  for (int n = 1; n <= nlinks; n ++) 
					  {
						  j1 = links[n][1];
						  j2 = links[n][2];
						  xl[0] = r[1][j1];
						  xl[1] = r[1][j2];

						  yl[0] = r[2][j1];
						  yl[1] = r[2][j2];

						  zl[0] = r[3][j1];
						  zl[1] = r[3][j2];
						  if (fabs(r[1][j1]-r[1][j2]) < 0.5*region[1] &&
							  fabs(r[2][j1]-r[2][j2]) < 0.5*region[2] &&
							  fabs(r[3][j1]-r[3][j2]) < 0.5*region[3] )
							  //;
							  pSurfDoc->AddLine(xl,yl,zl,RGB(0,255,0));
					  }
#else
					  for (int j = 0; j < nChain; j++)
					  {
						  for (int i = 0; i < chainLen; i++)
						  {
							  xl[i] = xi[j*chainLen+i];
							  yl[i] = yi[j*chainLen+i];
							  zl[i] = zi[j*chainLen+i];
						  }
						  pSurfDoc->AddLine(xl,yl,zl,RGB(0,255,0));
					  }
#endif /*LINK_MATR*/
					  pSurfDoc->ClearSpheres();
#if GRID_MEMBRANA
					  ///
					  xi.resize(nGridAtom);
					  yi.resize(nGridAtom);
					  zi.resize(nGridAtom);

					  for (int i = 0; i < nGridAtom; i++)
					  {
						  xi[i] = r[1][i+1];
						  yi[i] = r[2][i+1];
						  zi[i] = r[3][i+1];
					  }

					  pSurfDoc->AddSpheres(xi,yi,zi, RGB(255,0,0));
					  ///
					  ///
					  xi.resize(nPolyAtom);
					  yi.resize(nPolyAtom);
					  zi.resize(nPolyAtom);

					  for (i = 0; i < nPolyAtom; i++)
					  {
						  xi[i] = r[1][nGridAtom+i+1];
						  yi[i] = r[2][nGridAtom+i+1];
						  zi[i] = r[3][nGridAtom+i+1];
					  }

					  pSurfDoc->AddSpheres(xi,yi,zi, RGB(0,255,0));
					  ///
					  xi.resize(nAtom-nGridAtom-nPolyAtom);
					  yi.resize(nAtom-nGridAtom-nPolyAtom);
					  zi.resize(nAtom-nGridAtom-nPolyAtom);

					  for (i = 0; i < nAtom-nGridAtom-nPolyAtom; i++)
					  {
						  xi[i] = r[1][nGridAtom+nPolyAtom+i+1];
						  yi[i] = r[2][nGridAtom+nPolyAtom+i+1];
						  zi[i] = r[3][nGridAtom+nPolyAtom+i+1];
					  }

					  pSurfDoc->AddSpheres(xi,yi,zi, RGB(0,0,255));
					  ///
#else
					  ///
					  xi.resize(nAtom);
					  yi.resize(nAtom);
					  zi.resize(nAtom);

					  for (int i = 0; i < nAtom; i++)
					  {
						  xi[i] = r[1][i+1];
						  yi[i] = r[2][i+1];
						  zi[i] = r[3][i+1];
					  }

					  pSurfDoc->AddSpheres(xi,yi,zi, 236);
#endif /*GRID_MEMBRANA*/
					  pSurfDoc->ZoomView();
					  
					  pSurfDoc->Draw();
					  
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(lpSurfDlgMem->hWnd,&rect);
					  InvalidateRect(lpSurfDlgMem->hWnd,&rect, true);
				  }
				  break;
#ifdef USE_EARTHQUAKES_ON_SURF
			case ID_WINSURF_FILE_STOP_PLAY_EARTHQUAKES:
				{
					KillTimer(hWnd,	IDT_TIMER_EARTHQUAKES);
				}
				break;

			  case ID_WINSURF_FILE_PLAY_EARTHQUAKES:
				  {
				win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
				project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
				SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
											  
					  //char dat_filename[255];
					  if (MessageBox(0, "Do you want to play earthquakes?", "Surf", 
							MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
						{
						  i_eq = 0;
						  printf("vDoc[0].m_Beq.Length() = %d i_eq = %d\n", vDoc[0].m_Beq.Length(), i_eq);
						  if ( i_eq < vDoc[0].m_Beq.Length())
						  {
								SendMessage(hWnd,WM_USER+3,0,0);
								i_eq++;
								SetTimer(hWnd,
									IDT_TIMER_EARTHQUAKES,
									1000,	                // 10-second interval 
									(TIMERPROC) NULL);     // no timer callback 


						  }
					  }
				  													
				  }
				  break;
#endif
			  case ID_WINSURF_FILE_IMPORT_MOLS:
				  {
											  
					  //char dat_filename[255];
					  if (MessageBox(0, "Do you want to load molls?", "Surf", 
							MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
						{
							if (OpenFileDlg(hWnd,"Mols (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
							{
								MessageBox(0, szPath, directory,0);
								/*DWORD dwChildID;
								HANDLE m_hThread = ::CreateThread(NULL, 0, 
									LoadAtomsConfigfile, 
									reinterpret_cast<LPVOID>(lpSurfDlgMem), 
									0,
									&dwChildID );*/

									blockNum = -1;
									if (GetConfig ())
									{
										SendMessage(hWnd,WM_COMMAND,ID_WINSURF_DRAW_MOLS,0);
										  if (MessageBox(0, "Do you want to play molls?", "Surf", 
												MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
											{

													SetTimer(hWnd,
													IDT_TIMER_MOLS,
													1,	                // 10-second interval 
												(TIMERPROC) NULL);     // no timer callback 
											}										
									}
							}
					  }				  													
				  }
				  break;
			  case ID_WELLS_EDGESTRIANGULATION:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->WellsEdgesTriangulation();
						pSurfDoc->WellsEdgesTriangulationPerSloj();

						pSurfDoc->ZoomView();
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case ID_WELLS_INTERWELLSLINESPARAMETERS:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  
					  HANDLE hDialog = LoadResource( hInst,
						  FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_INTER_WELLS_PARAM),
						  RT_DIALOG ) );
					  
					  LPVOID lpDialog = LockResource( hDialog );
					  
					  HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
						  (DLGPROC)DlgProcInterWellsLineToPaint,
						  (LPARAM)pSurfDoc );
					  ShowWindow(hDlg, SW_SHOW);

				  }
				  break;
			  case ID_WELLS_TRIANGULATION:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->WellsTriasTriangulation();

						pSurfDoc->ZoomView();
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;

			  case ID_WINSURF_FILE_IMPORTBITMAP:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
								
						pSurfDoc->AddBitmap();

						pSurfDoc->ZoomView();
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);
				  }
				  break;	
			  case ID_LAB_TRIALTREE:
				  {
#if 0
					  Laboratory * lab = &lpSurfDlgMem->pSurfDoc->m_laboratory;
					  hwndTV = CreateATreeView(NULL, lab);
					  SetWindowLongPtr(hwndTV, GWLP_USERDATA,(LONG_PTR)lab);
					  if (lab)
						  lab->hwndTV = hwndTV;

					  ShowWindow(hwndTV, 1);
#else
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_LAB_TRIAL_TREE),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );
#if 1
						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcLabTrialTree,
											(LPARAM) &lpSurfDlgMem->pSurfDoc->m_laboratory );
#else
						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcLaboratoryTrialTree,
											(LPARAM) &lpSurfDlgMem->pSurfDoc->m_laboratory );
#endif
						ShowWindow(hDlg, SW_SHOW);	
#endif
				  }
				  break;
			  case ID_LAB_PARAMTREE:
				  {
#if 0
					  Laboratory * lab = &lpSurfDlgMem->pSurfDoc->m_laboratory;
					  hwndTV = CreateATreeView_LabParam(NULL, lab);
					  SetWindowLongPtr(hwndTV, GWLP_USERDATA,(LONG_PTR)lab);
					  if (lab)
						  lab->hwndTV = hwndTV;

					  ShowWindow(hwndTV, 1);
#else
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_LAB_PARAM_TREE),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );
#if 1
						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcLabParamTree,
											(LPARAM) &lpSurfDlgMem->pSurfDoc->m_laboratory );
#else
						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcLaboratoryParamTree,
											(LPARAM) &lpSurfDlgMem->pSurfDoc->m_laboratory );
#endif
						ShowWindow(hDlg, SW_SHOW);	
#endif
				  }
				  break;
			  case ID_LAB_EXCLUDEDTRIALSLIST:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->LabExcludedList(hWnd);
				  }
				  break;
			  case ID_LAB_LAYERSLIST:
				  {
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_LAB_LAYERS_LIST),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );
#if 0
						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcLabLayersList,
											(LPARAM) lpSurfDlgMem );
#else
						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcLaboratoryLayersList,
											(LPARAM) lpSurfDlgMem );
#endif
						ShowWindow(hDlg, SW_SHOW);	
				  }
				  break;
			  case ID_LAB_SHTAMPDEFMODUL:
				  {
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_LAB_SHTAMP_DEF_MODUL),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcShtampDefKModul,
											(LPARAM) lpSurfDlgMem );

						ShowWindow(hDlg, SW_SHOW);
				  }
				  break;
			  case ID_SURFTEST_AUTOCADADDINGTOPATFILE:
				  {
				
					  CString s = ";;\n"
						  ";;GeoCube\n"
						  ";;\n"
						  "*alevrolit\n"
						  "0, 0,1, 0,2\n"
						  "60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547\n"
						  "120,0,0,3.4641,2,1.1547,-4.6188,1.1547\n"
						  "60 ,3.4641,0,3.4641,2,-6.6282,.3\n"
						  "120,3.4641,0,3.4641,2,.2,-6.7282\n"
						  "*argilit\n"
						  "0,0,1,0,2\n"
						  "135,0,.3,0,2.8284,2,-3.6569\n"
						  "*brechkia\n"
						  "0,   0,-1, -1.732051,3, .57735,-2.309401,.57735\n"
						  "60,  0,  0, -1.732051,3, -2.309401, 1.154701\n"
						  "120, 0,  0, -1.732051,3, -2.309401, 1.154701\n"
						  "0,   0,1, 0,3,1\n"
						  "*dolomit\n"
						  "0, 0,0, 0,2\n"
						  "90,0,0,2,4,2,-2\n"
						  "90,.5,0,2,4,2,-2\n"
						  "*galka\n"
						  "45,.85,.75,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.85,.45,0,2.121320344,.424264068,-1.697056275\n"
						  "135,1.15,.45,0,2.121320344,.424264068,-1.697056275\n"
						  "135,2.15,.75,0,2.121320344,.424264068,-1.697056275\n"
						  "0,1.15,.45,1.5,1.5,.7,-2.3\n"
						  "0,1.15,1.05,1.5,1.5,.7,-2.3\n"
						  "*glmor\n"
						  "0,2.346926627,2.869551813,5,5,0.306146746,-9.693853254\n"
						  "0,2.346926627,2.130448187,5,5,0.306146746,-9.693853254\n"
						  "45,2.130448187,2.653073373,0,7.071067812,0.306146746,-6.764921066\n"
						  "45,2.653073373,2.130448187,0,7.071067812,0.306146746,-6.764921066\n"
						  "135,2.869551813,2.653073373,0,7.071067812,0.306146746,-6.764921066\n"
						  "135,2.346926627,2.130448187,0,7.071067812,0.306146746,-6.764921066\n"
						  "90,2.130448187,2.346926627,5,5,0.306146746,-9.693853254\n"
						  "90,2.869551813,2.346926627,5,5,0.306146746,-9.693853254\n"
						  "0,-0.076536686,0.184775907,5,5,0.153073373,-9.846926627\n"
						  "0,-0.076536686,-0.184775907,5,5,0.153073373,-9.846926627\n"
						  "45,-0.184775907,0.076536686,0,7.071067812,0.153073373,-6.917994439\n"
						  "45,0.076536686,-0.184775907,0,7.071067812,0.153073373,-6.917994439\n"
						  "135,0.184775907,0.076536686,0,7.071067812,0.153073373,-6.917994439\n"
						  "135,-0.076536686,-0.184775907,0,7.071067812,0.153073373,-6.917994439\n"
						  "90,-0.184775907,-0.076536686,5,5,0.153073373,-9.846926627\n"
						  "90,0.184775907,-0.076536686,5,5,0.153073373,-9.846926627\n"
						  "0,-0.184775907,0,0,10,-0.369551813,9.630448187\n"
						  "0,0,1.25,0,5\n"
						  "0,2.130448187,2.5,0,10,-0.739103626,9.260896374\n"
						  "0,-5.184775907,5,0,10,-0.369551813,9.630448187\n"
						  "0,0,3.75,0,5\n"
						  "0,7.130448187,7.5,0,10,-0.739103626,9.260896374\n"
						  "*granit\n"
						  "0 ,-.325,0,1,1,.65,-1.35\n"
						  "90,0,-.325,1,1,.65,-1.35\n"
						  "*gravelit\n"
						  "0,0,0,5.774,1,.5774,-1.1547,.5774\n"
						  "60,0,0,1.4434,-.5,-3.4641,1.1547\n"
						  "120,0,0,3.1754,-.5,-3.4641,1.1547\n"
						  "*gravij\n"
						  "0,0,.43301,1.732051,3,-.25,.5, -2.714102\n"
						  "0,0,-.43301,1.732051,3,-.25,.5, -2.714102\n"
						  "60,0,0,1.732051,3, .5,-2.964102\n"
						  "60,1,0,1.732051,3,-2.964102,.5\n"
						  "120,0,0,1.732051,3,-2.964102,.5\n"
						  "120,1,0,1.732051,3,.5,-2.964102\n"
						  "*jorstva\n"
						  "0,   0,-1, -1.732051,3, .57735,-2.309401,.57735\n"
						  "60,  0,  0, -1.732051,3, -2.309401, 1.154701\n"
						  "120, 0,  0, -1.732051,3, -2.309401, 1.154701\n"
						  "*kamin\n"
						  "0,.57735,1,2.3094,2,1.1547,-5.7735,1.1547,-1.1547\n"
						  "60,0,0,-2.886751,1,1.1547,-2.3094,1.1547,-4.6188\n"
						  "120,0,0,-6.3508,1,-4.6188,1.1547,-2.3094,1.1547,-9.2376\n"
						  "330,0,0,13,.57735,2,-20,2,-8\n"
						  "*konglomerat\n"
						  "0, 0,1, 0,2\n"
						  "60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547\n"
						  "120,0,0,3.4641,2,1.1547,-4.6188,1.1547\n"
						  "30,2.598,0,2,3.4641,1,-3\n"
						  "30,4.3301,0,2,3.4641,-3,1\n"
						  "150,2.5980,0,2,3.4641,-3,1\n"
						  "150,4.3301,0,2,3.4641,1,-3\n"
						  "*krejda\n"
						  "0, 0,0, 0,.8\n"
						  "90,0,0,.8,1,.8,-.8\n"
						  "*les\n"
						  "90,0,0,1,1.2,-.4,1.6\n"
						  "*mergel\n"
						  "0,0,0,0,.2\n"
						  "45,0,0,0,.28284,.28284,-.28284\n"
						  "*mul\n"
						  "0,0,1.55,0,1.5\n"
						  "45,1.05,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.65,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "135,1.65,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "*nasup\n"
						  "45, 0,0, 0,1.25\n"
						  "135,0,0, 0,1.25\n"
						  "45,.85,.75,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.85,.45,0,2.121320344,.424264068,-1.697056275\n"
						  "135,1.15,.45,0,2.121320344,.424264068,-1.697056275\n"
						  "135,2.15,.75,0,2.121320344,.424264068,-1.697056275\n"
						  "0,1.15,.45,1.5,1.5,.7,-2.3\n"
						  "0,1.15,1.05,1.5,1.5,.7,-2.3\n"
						  "*nasup_glina\n"
						  "0,0,0,1,.5,2,-.7\n"
						  "120,0,0,0,1,10\n"
						  "*nasup_pisok\n"
						  "0,.215685,0,1.13137,1.13137,-.3,.1,-.731371\n"
						  "45,0,0,0,.8,10\n"
						  "135,0,0,0,.8,10\n"
						  "*pisok_gravij\n"
						  "0,1.4962,.5,2,2,.076536686,-1.923463314\n"
						  "0,.4962,1.5,2,2,.076536686,-1.923463314\n"
						  "0,.461731657,.592387953,1,	1,.076536686,-1.923463314\n"
						  "0,.461731657,.407612047,1,1,.076536686,-1.923463314\n"
						  "45,.407612047,.538268343,0,1.414213562,.076536686,-1.337676876\n"
						  "45,.538268343,.407612047,0,1.414213562,.076536686,-1.337676876\n"
						  "135,.592387953,.538268343,0,1.414213562,.076536686,-1.337676876\n"
						  "135,.461731657,.407612047,	0,1.414213562,.076536686,-1.337676876\n"
						  "90,.407612047,.461731657,1,1,.076536686,-1.923463314\n"
						  "90,.592387953,.461731657,1,1,.076536686,-1.923463314\n"
						  "*pisok_krup\n"
						  "45,0,0,0,1,.05,-1\n"
						  "*piskovyk\n"
						  "0, 0,1, 0,2\n"
						  "0,-.05,0,3.4641,2,.1,-1.28564\n"
						  "60 ,0,0,3.4641,2,1.1547,-4.6188,1.1547\n"
						  "120,0,0,3.4641,2,1.1547,-4.6188,1.1547\n"
						  "*roslyna\n"
						  "0,0,0,1.5,2,1.2,-1.8\n"
						  "0,.2,-.3,1.5,2,.8,-2.2\n"
						  "0,.4,-.6,1.5,2,.4,-2.6\n"
						  "90,.6,-1.3,2,1.5,1,-3\n"
						  "53.13,1.3,-1.08,-1.8,2.4,1.3,-1.2\n"
						  "53.13,1.7,-1.3,-1.8,2.4,1.3,-1.2\n"
						  "53.13,2.1,-1.52,-1.8,2.4,1.3,-1.2\n"
						  "*roslynaPND\n"
						  "0,0,0,1.5,2,1.2,-1.8\n"
						  "0,.2,-.3,1.5,2,.8,-2.2\n"
						  "0,.4,-.6,1.5,2,.4,-2.6\n"
						  "90,.6,-1.3,2,1.5,1,-3\n"
						  "*sapropel\n"
						  "45,1.05,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.65,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "135,1.65,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.05,2.4,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.65,2.4,0,2.121320344,.424264068,-1.697056275\n"
						  "135,1.65,2.4,0,2.121320344,.424264068,-1.697056275\n"
						  "*shebin\n"
						  "0,   0,-1, 2.309401, 4, -.57735, 3.464102, -.57735\n"
						  "60,  0,  0, 2.309401, 4, 3.464102, -1.154701\n"
						  "120, 0,  0, 2.309401, 4, 3.464102, -1.154701\n"
						  "*slanec_glina\n"
						  "0,0,0,1,1,2,-2\n"
						  "135,0,0,0,1.41421,1.41421,-1.41421\n"
						  "*suglmore\n"
						  "0,0,0,0,10\n"
						  "0,4.04329142,7.30969883,10,10,1.91341716,-18.08658284\n"
						  "0,4.04329142,2.69030117,10,10,1.91341716,-18.08658284\n"
						  "225,4.04329142,7.30969883,0,14.14214,1.91341716,-12.22872\n"
						  "45,5.95671,2.69030117,0,14.14214,1.91341716,-12.22872\n"
						  "135,7.30969883,5.95670858,0,14.14214,1.91341716,-12.22872\n"
						  "135,4.04329142,2.69030117,0,14.14214,1.91341716,-12.22872\n"
						  "90,2.69030117,4.04329142,10,10,1.91341716,-18.08658284\n"
						  "90,7.30969883,4.04329142,10,10,1.91341716,-18.08658284\n"
						  "*supismor\n"
						  "0,0,0,0,10,7.5,-2.5\n"
						  "0,4.04329142,7.30969883,10,10,1.91341716,-18.08658284\n"
						  "0,4.04329142,2.69030117,10,10,1.91341716,-18.08658284\n"
						  "225,4.04329142,7.30969883,0,14.14214,1.91341716,-12.22872\n"
						  "45,5.95671,2.69030117,0,14.14214,1.91341716,-12.22872\n"
						  "135,7.30969883,5.95670858,0,14.14214,1.91341716,-12.22872\n"
						  "135,4.04329142,2.69030117,0,14.14214,1.91341716,-12.22872\n"
						  "90,2.69030117,4.04329142,10,10,1.91341716,-18.08658284\n"
						  "90,7.30969883,4.04329142,10,10,1.91341716,-18.08658284\n"
						  "*supismorPND\n"
						  "0, 0 ,0, 0, 1, .5, -.5\n"
						  "0, 0,.125,0,1, .5, -.5\n"
						  "*supispidmor\n"
						  "0, 0 ,0, 0, 1, .5, -.5\n"
						  "*torf_sylno\n"
						  "0,0,0,0,1.5\n"
						  "90,.75,0,0,1.5\n"
						  "45,.75,0,0,2.121320344\n"
						  "135,-.75,0,0,2.121320344\n"
						  "*torf_seredno\n"
						  "0,0,0,0,1.5\n"
						  "90,.75,0,0,1.5\n"
						  "45,0,.5,0,2.121320344,.424264068,-1.697056275\n"
						  "135,0,.5,0,2.121320344,.424264068,-1.697056275\n"
						  "*torf_slabo\n"
						  "0,0,0,0,1.5\n"
						  "90,.75,0,0,1.5\n"
						  "45,1.05,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "45,1.65,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "135,1.65,2.1,0,2.121320344,.424264068,-1.697056275\n"
						  "*valun\n"
						  "0,.57735,1,0,2,1.1547,-1.1547\n"
						  "60,0,0,-2.886751,1,1.1547,-2.3094,1.1547,-4.6188\n"
						  "120,0,0,2.886751,1,-4.6188,1.1547,-2.3094,1.1547\n"
						  "*VBK\n"
						  "0,0,0,0,4,1,-.5,1.5\n"
						  "0,0,1,0,4,1,-.5\n"
						  "0,0,-1,0,4,1,-.5\n"
						  "0,1,1.25,0,4,.5,-2.5\n"
						  "0,1,-1.25,0,4,.5,-2.5\n"
						  "90,1,-1.25,4,3,2.5,-1.5\n"
						  "90,1.5,-1.25,4,3,2.5,-1.5\n"
						  "90,2.5,.75,4,3,2.5,-1.5\n"
						  "0,2.5,.75,0,4,.5,-2.5\n"
						  "0,2.5,3.25,0,4,.5,-2.5\n"
						  "90,3,.75,4,3,2.5,-1.5\n"
						  "0,0,2,0,4,2.5,-.5\n"
						  ";;end GeoCube\n";

						  char * memenv;
						  char pat_file[2048];pat_file[0] = '\0';
						  if ((memenv = getenv("APPDATA")) != NULL) 
						  {
							  sprintf(pat_file, "%s\\Autodesk\\", memenv);
						  }

						  if (OpenFileDlg(hWnd,"Autocad Pattern fale (*.pat)\0*.pat\0", pat_file) == S_OK)
						  {
							  FILE * stream = fopen(pat_file, "at");
							  if (stream)
							  {
								  fprintf(stream, s);
								  fclose(stream);
							  }
						  }					  
						  
				  }
				  break;
/*			  case ID_SURFTEST_EXCELEXECUTE1:
				  {
					MyExcel m_excel;
					m_excel.ExcelOleLoad();
					if (m_excel.IsApplicationDispatch())
					{
						try
						{
							m_excel.ExcelOleExecute_2();
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
						printf("!!!!! m_excel.IsApplicationDispatch()\n");

				  }
				  break;*/
			  case ID_SURFTEST_EXCELEXECUTE1:
				  {
					MySurfer m_surfer;
					if (m_surfer.SurferOleLoad() && m_surfer.IsApplicationDispatch())
					{
						try
						{
							m_surfer.SurferOleExecute(NULL);
						}
						catch (CException* pe)
						{
							// catch errors from WinINet 
							TCHAR szErr[4098]; 
							pe->GetErrorMessage(szErr, 4098); 
							AfxMessageBox(szErr);
							pe->Delete();
						}
						m_surfer.SurferOleRelease();
					}
					else
						printf("!!!!! m_surfer.IsApplicationDispatch()\n");

					MyAcad m_acad;
					m_acad.AcadOleLoad();
					if (m_acad.IsApplicationDispatch())
					{
						try
						{
							m_acad.AcadOleExecute(NULL);
						}
						catch (CException* pe)
						{
							// catch errors from WinINet 
							TCHAR szErr[4098]; 
							pe->GetErrorMessage(szErr, 4098); 
							AfxMessageBox(szErr);
							pe->Delete();
						}
						m_acad.AcadOleRelease();
					}
					else
						printf("!!!!! m_acad.IsApplicationDispatch()\n");

					MyExcel m_excel;
					m_excel.ExcelOleLoad();
					if (m_excel.IsApplicationDispatch())
					{
						try
						{
							m_excel.ExcelOleExecute(NULL);
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
						printf("!!!!! m_excel.IsApplicationDispatch()\n");

				  }
				  break;
			  case ID_SURFS_ORDERLISTS:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SURFACES_LIST),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcSurfacesOrderLists,
											(LPARAM) lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);	
				  }
				  break;
			  case ID_WELLS_KAROTAZHLIST:
				  {
#if 0
					  // modal dialog
					if (IDOK == DialogBoxParam(hInst, 
							MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_LIST), 
							(HWND)NULL, (DLGPROC)DlgProcWellsDrawAndKarotazhList, (LPARAM) lpSurfDlgMem)==IDOK) 
					{
					}				
#else
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_KAROTAZH_LIST2),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)DlgProcWellsDrawAndKarotazhList,
											(LPARAM) lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);		
#endif
				  }
				  break;
			  case ID_GRID_GRIDDATAPROPERTIES:
				  {
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_GRIDDATA_PROP),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)GridData::DlgProc,
											(LPARAM)0 );
						ShowWindow(hDlg, SW_SHOW);		
				  }
				  break;
			  case ID_PROFILES_COORDINATEGRID:
				  {
						// modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_PROFILES_COORDINATE_GRID),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcProfilesCoordinateGrid,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);		
				  }
				  break;
			  case ID_GEO_CUBESIZE:
				  {
					  // modeless dialog
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_CUBE_SIZE),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcCubeSize,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);		
				  }
				  break;
			  case ID_GEO_GEOCUBE:
				  {						
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_CUBE_ADD_GEOCUBE),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcAddGeoCube,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);				  
				  }
				  break;
			  case ID_GEO_GEOELEMENTMAPPING:
				  {						
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_GEO_ELEMENT_MAPPING),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcGeoElementMapping,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);				  
				  }
				  break;
			  case ID_GEO_ADDGEOCOLOMN_STRATIGRAFICAL:
			  case ID_GEO_ADDGEOCOLOMN_LITHILOGICAL:
			  case ID_GEO_ADDGEOCOLOMN_ENGINEERGEOLOGICAL:
			  case ID_GEO_ADDGEOCOLOMN_HYDROGEOLOGICAL:
			  case ID_GEO_ADDGEOCOLOMN_LABORATORYEXPLORATION:
			  case ID_GEO_ADDGEOCOLOMN_FIELDEXPLORATION:
			  case ID_GEO_ADDGEOCOLOMN_FAULTS:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
						
						GeoElement::type t = GeoElement::type::undefined_geo_element;
						
						switch( LOWORD( wParam ) )
						{
						case ID_GEO_ADDGEOCOLOMN_STRATIGRAFICAL:
							t = GeoElement::type::stratigrafical;
							break;
						case ID_GEO_ADDGEOCOLOMN_LITHILOGICAL:
							t = GeoElement::type::lithological;
							break;
						case ID_GEO_ADDGEOCOLOMN_ENGINEERGEOLOGICAL:
							t = GeoElement::type::engineer_geological;
							break;
						case ID_GEO_ADDGEOCOLOMN_HYDROGEOLOGICAL:
							t = GeoElement::type::hydro_geological;
							break;
						case ID_GEO_ADDGEOCOLOMN_LABORATORYEXPLORATION:
							t = GeoElement::type::laboratory_exploration;
							break;
						case ID_GEO_ADDGEOCOLOMN_FIELDEXPLORATION:
							t = GeoElement::type::field_exploration;
							break;
						case ID_GEO_ADDGEOCOLOMN_FAULTS:
							t = GeoElement::type::faults;
							break;
						}

						if (pSurfDoc) pSurfDoc->AddGeoColomn(t);				  
						if (pSurfDoc) 
						{
							TreeView_DeleteMyItem(pSurfDoc->hwndTV,pSurfDoc->m_geo_colomns_ObjectList.myTreeItem);
							AddGeoColomnsToTree(pSurfDoc->hwndTV, pSurfDoc);
						}
				  }
				  break;
			  case ID_WELLS_SAVETODB:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->WellsSaveToDB();
				  }
				  break;
			  case ID_WELLS_TESTSVAI:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->TestSvai();		

				  }
				  break;
			  case ID_GEO_SUSPENDEDINWATERSPECIFICGRAVITY:
				  {
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_CUBE_SUSPENDEDINWATERSPECIFICGRAVITY),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcSuspendedInWaterSpecificGravity,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);	
				  }
				  break;

			  case ID_WELLS_RASCHETBURONABIVNYHSVAJ:
				  {
#if 1
					  static BuroNabivSvaj svai;
					  svai.Dialog(lpSurfDlgMem->pSurfDoc);
#else
						HANDLE hDialog = LoadResource( hInst,
										FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_SVAI_BURO_NABIVNIE),
														RT_DIALOG ) );

						LPVOID lpDialog = LockResource( hDialog );

						HWND hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, hWnd,
											(DLGPROC)::DlgProcSvaiBuroNabivnie,
											(LPARAM)lpSurfDlgMem );
						ShowWindow(hDlg, SW_SHOW);	
#endif
				  }
				  break;
			  case ID_WELLS_DETERMINEUDELNOESCEPLENIE:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->DetermineUdelnoeSceplenie();

						pSurfDoc->ZoomView();// �������� !!! ����������� ������ ��������� ��� �������
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						prj->UpdateAllViews();
				  }
				  break;
			  case ID_WELLS_TESTPESOK1ORGLINA1:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->TestPesokOrGlina();	

						pSurfDoc->ZoomView();// �������� !!! ����������� ������ ��������� ��� �������
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						prj->UpdateAllViews();
				  }
				  break;

			  case ID_WELLS_DETERMINEUGOLVNUTRENNEGOTRENIA:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->DetermineUdolVnutrennegoTrenia();	

						pSurfDoc->ZoomView();// �������� !!! ����������� ������ ��������� ��� �������
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						prj->UpdateAllViews();
				  }
				  break;
			  case ID_WELLS_DETERMINEDEFORMATIONMODUL:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->DetermineDeformationModul();	

						pSurfDoc->ZoomView();// �������� !!! ����������� ������ ��������� ��� �������
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						prj->UpdateAllViews();
				  }
				  break;
			  case ID_WELLS_DETERMINEPESOKGLINAFROMPCK:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->DeterminePesokGlinaFromPCK();

						pSurfDoc->ZoomView();// �������� !!! ����������� ������ ��������� ��� �������
						pSurfDoc->Draw();
						//====== �������������� ��� � ������ ���������
						prj->UpdateAllViews();

				  }
				  break;
			  case ID_WELLS_TESTDUBLICATE:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						if (pSurfDoc) pSurfDoc->TestDublicateWells();				  
				  }
				  break;				  
			  case ID_FILE_IMPORTWELLS_LABORATORYANALIZES:
				  {
					  TCHAR lpstrFile[4098];
					  if (OpenFileDlg(hWnd, "Laboratory analizes files (*)\0*.*\0All files \0*.*\0", lpstrFile) == S_OK)
					  {
							win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

							if (pSurfDoc->m_laboratory.ReadLabInputFile(lpstrFile))
							{
								pSurfDoc->m_laboratory.ReCalcProperties(true, true);
								pSurfDoc->m_laboratory.FillLabParameters();
								pSurfDoc->m_laboratory.Normatives();
								pSurfDoc->AddNewWellColomn_LaboratoryAnalizes();
								if (prj) prj->UpdateAllViews();
							}
					  }
				  }
				  break;
			  case ID_LAB_CONTEXTWITHPLOT:
				  {
#if 0
					  if (Laboratory::context_with_plot)
					  {
						  Laboratory::context_with_plot = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHPLOT,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  Laboratory::context_with_plot = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHPLOT,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
#else
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->OnViewPropertywindowwithPlot();
#endif
				  }
				  break;
			  case ID_LAB_CONTEXTWITHNORMATIVES:
				  {
#if 0
					  if (LabLayer::context_with_normatives)
					  {
						  LabLayer::context_with_normatives = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHNORMATIVES,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  LabLayer::context_with_normatives = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHNORMATIVES,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
#else
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->OnViewPropertywindowwithNormatives();
#endif
				  }
				  break;
			  case ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES:
				  {
#if 0
					  if (LabLayer::context_with_normatives_by_all_experiences)
					  {
						  LabLayer::context_with_normatives_by_all_experiences = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  LabLayer::context_with_normatives_by_all_experiences = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHNORMATIVESBYALLEXPERIENCES,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
#else
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->OnViewPropertywindowwithNormativesbyallexperiences();
#endif
				  }
				  break;
			  case ID_LAB_CONTEXTWITHKORRELATION:
				  {
#if 0
					  if (LabLayer::context_with_korrelation)
					  {
						  LabLayer::context_with_korrelation = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHKORRELATION,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  LabLayer::context_with_korrelation = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHKORRELATION,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
#else
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->OnViewPropertywindowwithCorrelation();
#endif
				  }
				  break;
			  case ID_LAB_COMPRESSIONWITHMINSQ:
				  {
					  if (CompressionLabTrialResults::compression_module_e_with_min_sq)
					  {
						  CompressionLabTrialResults::compression_module_e_with_min_sq = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_COMPRESSIONWITHMINSQ,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  CompressionLabTrialResults::compression_module_e_with_min_sq = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_COMPRESSIONWITHMINSQ,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCalcProperties(false,false);
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
				  }
				  break;
			  case ID_LAB_USEMAVRODIBETA:
				  {
/*					  if (CompressionLabTrialResults::use_mavrodi_beta)
					  {
						  CompressionLabTrialResults::use_mavrodi_beta = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_COMPRESSIONWITHMINSQ,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  CompressionLabTrialResults::use_mavrodi_beta = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_COMPRESSIONWITHMINSQ,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCalcProperties(false,false);
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();*/
				  }
				  break;
			  case ID_LAB_ZONDFIRSTTYPEMYMETHOD:
				  {
					  if (Well_3D::ZondFirstTypeMyMethod)
					  {
						  Well_3D::ZondFirstTypeMyMethod = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_ZONDFIRSTTYPEMYMETHOD,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  Well_3D::ZondFirstTypeMyMethod = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_ZONDFIRSTTYPEMYMETHOD,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
				  }
				  break;
			  case ID_LAB_PASSPORTUKRAINIANLANGUAGE:
				  {
					  if (BaseLab::PassportLanguage == BaseLab::language::ukrainian)
					  {
						  BaseLab::PassportLanguage = BaseLab::language::russian;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_PASSPORTUKRAINIANLANGUAGE,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  BaseLab::PassportLanguage = BaseLab::language::ukrainian;
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_PASSPORTUKRAINIANLANGUAGE,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
				  }
				  break;
			  case ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST:
				  {
#if 0
					  if (LabLayer::context_with_lab_number_trial_list)
					  {
						  LabLayer::context_with_lab_number_trial_list = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  LabLayer::context_with_lab_number_trial_list = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXT_WITH_LAB_NUMBER_TRIAL_LIST,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
#else
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->OnViewPropertywindowwithLabnumbertriallist();
#endif
				  }
				  break;
			  case ID_LAB_CONTEXTWITHRESULTS:
				  {
#if 0
					  if (LabNumber::context_with_results)
					  {
						  LabNumber::context_with_results = false;
                          
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHRESULTS,
							  MF_BYCOMMAND | MF_UNCHECKED);
					  }
					  else
					  {
						  LabNumber::context_with_results = true; 
						  
						  CheckMenuItem(GetMenu( GetParent( hWnd ) ), 
							  ID_LAB_CONTEXTWITHRESULTS,
							  MF_BYCOMMAND | MF_CHECKED);
					  }
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->m_laboratory.ReCreateContextWindow();
#else
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  if (pSurfDoc) pSurfDoc->OnViewPropertywindowwithResults();
#endif
				  }
				  break;
			  case ID_FILE_IMPORTWELLS_ZOND_WITH_CORRECT_INPUT:
				  {
					  TCHAR lpstrFile[4098];
					  if (OpenFileDlg(hWnd, "zonds (*)\0*.*\0All files \0*.*\0", lpstrFile) == S_OK)
					  {
							win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

							if (pSurfDoc->ReadZond_CorrectInput_File(lpstrFile))
							{
							}
					  }
				  }
				  break;
			  case ID_FILE_IMPORTWELLS_ZOND_INPUT:
				  {
					  TCHAR lpstrFile[4098];
					  if (OpenFileDlg(hWnd, "zonds (*)\0*.*\0All files \0*.*\0", lpstrFile) == S_OK)
					  {
							win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

							if (pSurfDoc->ReadZondInputFile(lpstrFile))
							{
							}
					  }
				  }
				  break;
			  case ID_FILE_IMPORTWELLS_ZOND:
				  {
					  TCHAR lpstrFile[4098];
					  if (OpenFileDlg(hWnd, "zonds (*.rno)\0*.rno\0All files \0*.*\0", lpstrFile) == S_OK)
					  {
							win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

							if (pSurfDoc->ReadZondOutputFile(lpstrFile))
							{
								pSurfDoc->ZoomView();
								pSurfDoc->Draw();
								//====== �������������� ��� � ������ ���������
								RECT rect;
								GetClientRect(hWnd,&rect);
								InvalidateRect(hWnd,&rect, true);
							}
					  }
				  }
				  break;
			  case ID_FILE_IMPORTWELLSKAROTAZH:
			  case ID_WINSURF_FILE_IMPORT_DRILLS_NEW2:// primitive
			  case ID_WINSURF_FILE_IMPORT_DRILLS_NEW3:// litho well colomns
			  case ID_WINSURF_FILE_IMPORT_DRILLS_NEW4:// eng well colomns
				  {
					  if (OpenFileDlg(hWnd, "Drills (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
					  {
							vector<vector<cell> > * pdrills = new vector<vector<cell> >;
							vector<string> * pnames_of_colomns = new vector<string>;
							char* filename = new char[256];

							int delim = '\t';

							ReadCellFile(hWnd, szPath, NULL, filename, pdrills, pnames_of_colomns, delim );

							lpDrillsDlgMem->pdrills = pdrills;
							lpDrillsDlgMem->pnames_of_colomns = pnames_of_colomns;
							lpDrillsDlgMem->filename = filename;

							lpDrillsDlgMem->types_of_colomns = new vector<int>;
							lpDrillsDlgMem->types_of_colomns->resize(lpDrillsDlgMem->pnames_of_colomns->size());

							lpDrillsDlgMem->colors_of_sloi = new vector<COLORREF>;
							lpDrillsDlgMem->colors_of_sloi->resize(lpDrillsDlgMem->pnames_of_colomns->size());

							lpDrillsDlgMem->checking_of_rows = new vector<int>;
							lpDrillsDlgMem->checking_of_rows->resize(pdrills->size());



							if (IDOK == DialogBoxParam(hInst, 
								 MAKEINTRESOURCE(IDD_DIALOG_DRILLS_LIST), 
								 (HWND)NULL, (DLGPROC)DlgProcDrillsList, (LPARAM)lpDrillsDlgMem)==IDOK) 
							{
								// Complete the command; szItemName contains the 
								// name of the item to delete. 
								win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
								project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
								SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
										
								//pSurfDoc->AddDrills(pdrills);
								switch( LOWORD( wParam ) )
								{
									case ID_WINSURF_FILE_IMPORT_DRILLS_NEW2:// primitive
										pSurfDoc->AddWells(lpDrillsDlgMem, false, false);
										break;
									case ID_WINSURF_FILE_IMPORT_DRILLS_NEW3:// litho well colomns
										pSurfDoc->AddWells(lpDrillsDlgMem, true, false);
										break;									
									case ID_WINSURF_FILE_IMPORT_DRILLS_NEW4:// eng well colomns
										pSurfDoc->AddWells(lpDrillsDlgMem, true, true);
										break;
									case ID_FILE_IMPORTWELLSKAROTAZH:
										pSurfDoc->AddKarotazhy(lpDrillsDlgMem, true);
										break;
								}

								pSurfDoc->ZoomView();
								pSurfDoc->Draw();
								//====== �������������� ��� � ������ ���������
								RECT rect;
								GetClientRect(hWnd,&rect);
								InvalidateRect(hWnd,&rect, true);
							}


							if (pdrills) delete pdrills;
							delete pnames_of_colomns;
							delete[] filename;
							delete lpDrillsDlgMem->types_of_colomns;
							delete lpDrillsDlgMem->colors_of_sloi;
							delete lpDrillsDlgMem->checking_of_rows;
					  }
				  }
				  break;
			  case ID_WINSURF_FILE_IMPORT_DRILLS_NEW:
				  {
					  if (OpenFileDlg(hWnd, "Drills (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
					  {
							vector<vector<cell> > * pdrills = new vector<vector<cell> >;
							vector<string> * pnames = new vector<string>;
							char* filename = new char[256];
							int delim = '\t';

							ReadCellFile(hWnd, szPath, NULL, filename, pdrills, pnames, delim );

							win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
							SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
									
							pSurfDoc->AddWells(pdrills);

							pSurfDoc->ZoomView();
							pSurfDoc->Draw();
							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(hWnd,&rect);
							InvalidateRect(hWnd,&rect, true);

							delete pdrills;
							delete pnames;
							delete[] filename;
					  }
				  }
				  break;
			  case ID_WINSURF_FILE_SCALE_DXF_ON_XY:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->LoadAndScaleDxf_onXY();
				  }
				  break;
			  case ID_WINSURF_FILE_SCALE_DXF_ON_Y:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->LoadAndScaleDxf_onY();
				  }
				  break;
#if DFX_LAYER_FROM_OBJECT
			  case ID_WINSURF_FILE_IMPORT_DXF:
				  {
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->CreateNewDxf();
						if (pSurfDoc->InitLastDxf())
						{
							pSurfDoc->ZoomView();
							pSurfDoc->Draw();
							//====== �������������� ��� � ������ ���������
							RECT rect;
							GetClientRect(hWnd,&rect);
							InvalidateRect(hWnd,&rect, true);
						}

				  }
				  break;
#endif
			  case ID_WINSURF_FILE_IMPORT_BLN:
				  {
					  char lpstrFile[1024];
					  if (OpenFileDlg(hWnd, "Golden Software Blanking (*.bln)\0*.bln\0All files \0*.*\0", lpstrFile) == S_OK)
					  {
						  vector<vector<vector<double> > > vvvd;
						  if (0 == ReadBlnFile(lpstrFile, &vvvd, NULL))
						  {
							  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
							  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
							  if (pSurfDoc)
							  {
								  pSurfDoc->CreateNewCollection();
								  pSurfDoc->m_collections.GetLastMsg().SetName(lpstrFile);
//size_t nlines = vvvd.size();
//printf("nlines = %u\n", nlines);
								  for(size_t nline = 0; nline < vvvd.size(); nline++)
								  {
//size_t npoints = vvvd[nline].size(); 
//printf("npoints = %u\n", npoints);
									  Line3D line(pSurfDoc);
									  for (size_t npoint = 0; npoint < vvvd[nline].size(); npoint++)
									  {
//size_t ndims =  vvvd[nline][npoint].size(); 
//printf("ndims = %u\n", ndims);
										  CPoint3 pt(0.0,0.0,0.0,true);
										  for (size_t ndim = 0; ndim < vvvd[nline][npoint].size(); ndim++)
										  {
											  //printf("vvvd[%u][%u][%u] = %f\n", nline,npoint,ndim, vvvd[nline][npoint][ndim]);
											  switch(ndim)
											  {
											  case 0:
												  pt.x = vvvd[nline][npoint][ndim];
												  break;
											  case 1:
												  pt.y = vvvd[nline][npoint][ndim];
												  break;
											  case 2:
												  pt.z = vvvd[nline][npoint][ndim];
												  break;
											  }
										  }
										  line.PushBack(pt);
									  }
									  pSurfDoc->AddObjectToLastCollection(&line);
								  }
								  pSurfDoc->ZoomView();                                  
								  pSurfDoc->Draw();
								  //====== �������������� ��� � ������ ���������
								  RECT rect;
								  GetClientRect(hWnd,&rect);
								  InvalidateRect(hWnd,&rect, true);
							  }
						  }
					  }
				  }
				  break;
#if !VIEW_ONLY_VERSION
//#if 0

			  case ID_FILE_AUTOBUILDPROFILE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
								  
					  if (pSurfDoc && pSurfDoc->AddAutoBuildProfile())
					  {
						  pSurfDoc->ZoomView();
						  pSurfDoc->Draw();
						  //====== �������������� ��� � ������ ���������
						  RECT rect;
						  GetClientRect(hWnd,&rect);
						  InvalidateRect(hWnd,&rect, true);
					  }
				  }
				  break;

			  case ID_FILE_AUTOBUILDPROFILE1:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
								  
					  if (pSurfDoc && pSurfDoc->AddAutoBuildProfile1())
					  {
						  pSurfDoc->ZoomView();
						  pSurfDoc->Draw();
						  //====== �������������� ��� � ������ ���������
						  RECT rect;
						  GetClientRect(hWnd,&rect);
						  InvalidateRect(hWnd,&rect, true);
					  }
				  }
				  break;
#endif /*!VIEW_ONLY_VERSION*/
			  case ID_WINSURF_FILE_OPEN:
				  {
					  //static char* pFileName;
					  //static char fileNameBuf[4096];
					  TCHAR filter[] =     
						  TEXT("Geo Surf File (*.gsf)\0*.gsf\0")
						  TEXT("All Files (*.*)\0*.*\0");
					  sprintf(fileNameBuf, "\0");
//					  DWORD nFilterIndex = 0;
					  if (OpenFileDlg(0, filter, fileNameBuf) == S_OK)
					  {
						  LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						  win_graphics_view * wgrv = (win_graphics_view *)userdata;
						  project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
						  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						  bool AsImport = false;
						  if(pSurfDoc->OpenFile(fileNameBuf, 4096, NULL, AsImport))
						  {
							  //====== �������������� ��� � ������ ���������
							  RECT rect;
							  GetClientRect(hWnd,&rect);
							  InvalidateRect(hWnd,&rect, true);
						  }

					  }
				  }
				  break;
			  case ID_WINSURF_FILE_OPEN_IMPORT_GSF:
				  {
					  //static char* pFileName;
					  //static char fileNameBuf[4096];
					  TCHAR filter[] =     
						  TEXT("Geo Surf File (*.gsf)\0*.gsf\0")
						  TEXT("All Files (*.*)\0*.*\0");
					  sprintf(fileNameBuf, "\0");
//					  DWORD nFilterIndex = 0;
					  if (OpenFileDlg(0, filter, fileNameBuf) == S_OK)
					  {
						  LONG_PTR userdata = GetWindowLongPtr(hWnd,GWLP_USERDATA);
						  win_graphics_view * wgrv = (win_graphics_view *)userdata;
						  project * prj; if (wgrv) prj = wgrv->GetProject(); else return -1;
						  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						  bool AsImport = true;
						  if(pSurfDoc->OpenFile(fileNameBuf, 4096, NULL, AsImport))
						  {
							  //====== �������������� ��� � ������ ���������
							  RECT rect;
							  GetClientRect(hWnd,&rect);
							  InvalidateRect(hWnd,&rect, true);
						  }
					  }
				  }
				  break;
			  case ID_WINSURF_FILE_SAVE:
				  {
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

					  if (pSurfDoc->current_filename.size() == 0)
					  {
						  SendMessage(hWnd, WM_COMMAND, ID_WINSURF_FILE_SAVEAS, 0);
					  }
					  else
					  {
						  if (pSurfDoc->SaveFile(pSurfDoc->current_filename.c_str(), 4096, NULL))
						  {
						  }
					  }
				  }
				  break;
			  case ID_WINSURF_FILE_SAVEAS:
				  {
					  //static char* pFileName;
					  //static char fileNameBuf[4096];
					  TCHAR filter[] =     
						  TEXT("Geo Surf File (*.gsf)\0*.gsf\0")
						  TEXT("All Files (*.*)\0*.*\0");
					  sprintf(fileNameBuf, "\0");
					  DWORD nFilterIndex = 0;
					  if (SaveFileDlg(0, fileNameBuf, filter, nFilterIndex) == S_OK)
					  {
						  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						  if (pSurfDoc->SaveFile(fileNameBuf, 4096, NULL))
						  {
						  }
					  }
				  }
				  break;
			  case ID_FILE_IMPORT_THIN_CUBE:
				  {
					  char grd_file[2048];
					  if (OpenFileDlg(hWnd, "Cube 3D grid(*.cub)\0*.cub\0All files \0*.*\0", grd_file) == S_OK)
					  {
						  //����� load ����
						  Grid4 * grid = new Grid4;

						  if (0 == ImportSurfer7Grid4(grd_file, grid))
						  {
								//-----------------------------------
								win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
								project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
								SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
								  
								COLORREF color = RGB(255,255,0);
								pSurfDoc->AddThinCube(grid, color);
								  
								if (pSurfDoc->m_cubes.SetCurrentMsgOnLast() && pSurfDoc->m_cubes.msgSize() > 1)
								{		
									DrawNewCube(pSurfDoc);
								}
								else
								{
									pSurfDoc->ZoomView();
									DrawCubes(pSurfDoc);
								}
								//====== �������������� ��� � ������ ���������
								RECT rect;
								GetClientRect(hWnd,&rect);
								InvalidateRect(hWnd,&rect, true);
								//-----------------------------------
								if (grid->grid4Section.v) Free3DMat<double>(grid->grid4Section.v);
						  }
						  delete grid;
					  }
				  }
				  break;
			  case ID_FILE_IMPORTCUBE:
				  {
					  char grd_file[2048];
					  if (OpenFileDlg(hWnd, "Cube 3D grid(*.cub)\0*.cub\0All files \0*.*\0", grd_file) == S_OK)
					  {
						  //����� load ����
						  Grid4 * grid = new Grid4;

						  if (0 == ImportSurfer7Grid4(grd_file, grid))
						  {
								//-----------------------------------
								win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
								project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
								SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
								  
								COLORREF color = RGB(255,255,0);
								pSurfDoc->AddCube(grid, color);
								  
								if (pSurfDoc->m_cubes.SetCurrentMsgOnLast() && pSurfDoc->m_cubes.msgSize() > 1)
								{		
									DrawNewCube(pSurfDoc);
								}
								else
								{
									pSurfDoc->ZoomView();
									DrawCubes(pSurfDoc);
								}
								//====== �������������� ��� � ������ ���������
								RECT rect;
								GetClientRect(hWnd,&rect);
								InvalidateRect(hWnd,&rect, true);
								//-----------------------------------
								if (grid->grid4Section.v) Free3DMat<double>(grid->grid4Section.v);
						  }
						  delete grid;
					  }
				  }
				  break;
			  case ID_SURFTEST_IFFT4TEST:
				  {
					  long N = 64;

cout << "Enter N" << endl;
cin >> N;

					  //����� ��������� ����
					  Grid4 * grid = new Grid4;
					  grid->grid4Section.xLL = 0;
					  grid->grid4Section.yLL = 0;
					  grid->grid4Section.zLL = 0;
					  
					  grid->grid4Section.nPag = N;
					  grid->grid4Section.nRow = N;
					  grid->grid4Section.nCol = N;
					  
					  grid->grid4Section.xSize = 1.0;
					  grid->grid4Section.ySize = 1.0;
					  grid->grid4Section.zSize = 1.0;
					  
					  grid->grid4Section.v = Alloc3DMat<double>(grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
					  grid->grid4Section.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

					  long p,r,c;

cout << "Enter p" << endl;
cin >> p;

cout << "Enter r" << endl;
cin >> r;

cout << "Enter c" << endl;
cin >> c;

double F;
cout << "Enter F" << endl;
cin >> F;

#if 1
					  long p2, r2,c2;

cout << "Enter p2" << endl;
cin >> p2;

cout << "Enter r2" << endl;
cin >> r2;

cout << "Enter c2" << endl;
cin >> c2;

double F2;
cout << "Enter F2" << endl;
cin >> F2;
					  grid->grid4Section.v[p2][r2][c2] = F2;
#endif


					  grid->grid4Section.v[p][r][c] = F;

					  ap::real_1d_array a;
					  a.setbounds( 0, N );
					  bool inversefft = true;

					  for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
					  {
						  for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
						  {
							  for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
							  {
								  a(jj) = grid->grid4Section.v[pp][jj][ii];
							  }
							  realfastfouriertransform(a, N, inversefft);
							  for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
							  {
								  grid->grid4Section.v[pp][jj][ii] = a(jj);
							  }
						  }
						  for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
						  {
							  for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
							  {
								  a(ii) = grid->grid4Section.v[pp][jj][ii];
							  }
							  realfastfouriertransform(a, N, inversefft);
							  for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
							  {
								  grid->grid4Section.v[pp][jj][ii] = a(ii);
							  }
						  }
					  }

					  for (long jj = 0; jj < grid->grid4Section.nRow; jj++)						  
					  {
						  for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
						  {
							  for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
							  {
								  a(pp) = grid->grid4Section.v[pp][jj][ii];
							  }
							  realfastfouriertransform(a, N, inversefft);
							  for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
							  {
								  grid->grid4Section.v[pp][jj][ii] = a(pp);
							  }
						  }
					  }
					  double min_v = DBL_MAX;
					  double max_v = -DBL_MAX;

					  double v_value;

					  for (long pp = 0; pp < grid->grid4Section.nPag; pp++)
					  {
						for (long ii = 0; ii < grid->grid4Section.nCol; ii++)
						{
							for (long jj = 0; jj < grid->grid4Section.nRow; jj++)
							{
								v_value = grid->grid4Section.v[pp][jj][ii];
								if (max_v < v_value) max_v = v_value;
								if (min_v > v_value) min_v = v_value;
							}
						}
					  }
					  grid->grid4Section.vMax = max_v;
					  grid->grid4Section.vMin = min_v;
					  
					  //grid->faultSection.nTraces = 0;
					  //grid->faultSection.nVertices = 0;
					  //grid->faultSection.traces = NULL;
					  //grid->faultSection.vertexes = NULL;
					  //-----------------------------------
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  COLORREF color = RGB(255,255,0); 
					  sprintf(szPath, "ifft_%ld_%ld_%ld_%ld_%f", p, r, c, N, F);
sprintf(szPath, "ifft_%ld_%ld_%ld_%ld_%0.1f_%ld_%ld_%ld_%0.1f", N, p, r, c, F, p2, r2, c2, F2);
					  
pSurfDoc->AddCube(grid, color);
					  if (pSurfDoc->m_cubes.SetCurrentMsgOnLast() && pSurfDoc->m_cubes.msgSize() > 1)
					  {		
						  DrawNewCube(pSurfDoc);
					  }
					  else
					  {
						  pSurfDoc->ZoomView();
						  DrawCubes(pSurfDoc);
					  }
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
					  //-----------------------------------
					  Free3DMat<double>(grid->grid4Section.v);
					  delete grid;
				  }
				  break;
			  case ID_SURFTEST_FFTTEST:
				  {
					  long N = 64;

cout << "Enter N" << endl;
cin >> N;

					  //����� ��������� ����
					  Grid * grid = new Grid;
					  grid->gridSection.xLL = 0;
					  grid->gridSection.yLL = 0;
					  
					  grid->gridSection.nRow = N;
					  grid->gridSection.nCol = N;
					  
					  grid->gridSection.xSize = 1.0;
					  grid->gridSection.ySize = 1.0;
					  
					  grid->gridSection.z = AllocDoubleMat(grid->gridSection.nRow, grid->gridSection.nCol);
					  grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

					  long r,c;

cout << "Enter r" << endl;
cin >> r;

cout << "Enter c" << endl;
cin >> c;

double F;
cout << "Enter F" << endl;
cin >> F;

#if 1
					  long r2,c2;

cout << "Enter r2" << endl;
cin >> r2;

cout << "Enter c2" << endl;
cin >> c2;

double F2;
cout << "Enter F2" << endl;
cin >> F2;
					  grid->gridSection.z[r2][c2] = F2;
#endif


					  grid->gridSection.z[r][c] = F;

					  ap::real_1d_array a;
					  a.setbounds( 0, N );
					  bool inversefft = true;

					  for (long ii = 0; ii < grid->gridSection.nCol; ii++)
					  {
						  for (long jj = 0; jj < grid->gridSection.nRow; jj++)
						  {
							  a(jj) = grid->gridSection.z[jj][ii];
						  }
						  realfastfouriertransform(a, N, inversefft);
						  for (long jj = 0; jj < grid->gridSection.nRow; jj++)
						  {
							  grid->gridSection.z[jj][ii] = a(jj);
						  }
					  }

					  for (long jj = 0; jj < grid->gridSection.nRow; jj++)
					  {
						  for (long ii = 0; ii < grid->gridSection.nCol; ii++)
						  {
							  a(ii) = grid->gridSection.z[jj][ii];
						  }
						  realfastfouriertransform(a, N, inversefft);
						  for (long ii = 0; ii < grid->gridSection.nCol; ii++)
						  {
							  grid->gridSection.z[jj][ii] = a(ii);
						  }
					  }

					  double min_z = DBL_MAX;
					  double max_z = -DBL_MAX;

					  double z_value;

					  for (long ii = 0; ii < grid->gridSection.nCol; ii++)
					  {
						  for (long jj = 0; jj < grid->gridSection.nRow; jj++)
						  {
							  z_value = grid->gridSection.z[jj][ii];
							  if (max_z < z_value) max_z = z_value;
							  if (min_z > z_value) min_z = z_value;
						  }
					  }
					  grid->gridSection.zMax = max_z;
					  grid->gridSection.zMin = min_z;
					  
					  grid->faultSection.nTraces = 0;
					  grid->faultSection.nVertices = 0;
					  grid->faultSection.traces = NULL;
					  grid->faultSection.vertexes = NULL;
					  //-----------------------------------
					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
					  COLORREF color = RGB(255,255,0); int zflag = 0;
					  sprintf(szPath, "ifft_%ld_%ld_%ld_%f", r, c, N, F);
					  sprintf(szPath, "ifft_%ld_%ld_%ld_%0.1f_%ld_%ld_%0.1f", N, r, c, F, r2, c2, F2);
					  
					  long id_surf = pSurfDoc->GetIDSurfForNewGridDataOrSurface();					  
					  BYTE podoshva = 0; long id_ige = -1;
					  pSurfDoc->AddSurf(id_surf, podoshva, id_ige, zflag, grid, color);
					  if (pSurfDoc->m_surfaces.SetCurrentMsgOnLast() && pSurfDoc->m_surfaces.msgSize() > 1)
					  {		
						  DrawNewSurf(pSurfDoc);
					  }
					  else
					  {
						  pSurfDoc->ZoomView();
						  DrawSurfs(pSurfDoc);
					  }
					  //====== �������������� ��� � ������ ���������
					  RECT rect;
					  GetClientRect(hWnd,&rect);
					  InvalidateRect(hWnd,&rect, true);
					  //-----------------------------------
					  FreeDoubleMat(grid->gridSection.z);
					  delete grid;
				  }
				  break;
				case ID_GRID_GRIDDATASAVETODB:
					{
						win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
						project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
						SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

						pSurfDoc->SaveGriddataToDB();

					}
					break;
			  /*case ID_GRID_DATABYSURFER:
				  {		
					  griddata_dialog(lpSurfDlgMem->pSurfDoc, NULL, hWnd, true, NULL, false, false);
				  }
				  break;*/
			  case ID_GRID_DATA:
				  {		
					  bool to_allocate = true;
					  griddata_dialog(to_allocate, lpSurfDlgMem->pSurfDoc, NULL, hWnd, griddata_dialog::griddata_application::unknown, NULL, false, false);
				  }
				  break;
			  case ID_GRID_DATA_OLD:
				  {
					  if (OpenFileDlg(hWnd, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
					  {	
						  vector<vector<double> > * vectors = new vector<vector<double> >;
						  char dat_filename[255];


						  if (ReadDatFile(hWnd, szPath, dat_filename, vectors, NULL) == 0)
						  {
							  char grd_file[1024];
							  TCHAR filter[] =   
								  TEXT("Grid file (*.grd)\0*.grd\0")
								  TEXT("All Files (*.*)\0*.*\0");
							  
							  sprintf(grd_file, "%s", dat_filename);
							  DWORD nFilterIndex = 0;
							  if (SaveFileDlg(0, grd_file, filter, nFilterIndex) == S_OK)
							  {
								  vector<double> VX, VY, VZ;// ������� ��� ���������� ������
								  double min_x = DBL_MAX, min_y = DBL_MAX;
								  double max_x = -DBL_MAX, max_y = -DBL_MAX;
								  for (size_t i = 0; i < vectors->size(); i++)
								  {
									  if ((*vectors)[i].size() < 3)
									  {
										  char error_str[1024];
										  sprintf(error_str, 
											  "There must be at least 3 elements in each row\n"
											  "But at %u row there are %u elements", i, vectors[i].size());
										  MessageBox(hWnd, error_str, "Grid->Data", MB_OK | MB_ICONEXCLAMATION);
										  return -1;
									  }
									  double X = (*vectors)[i][0];
									  double Y = (*vectors)[i][1];
									  double Z = (*vectors)[i][2];
									  
									  VX.push_back(X);
									  VY.push_back(Y);
									  VZ.push_back(Z);
									  
									  if (min_x > X) min_x = X;
									  if (min_y > Y) min_y = Y;
									  if (max_x < X) max_x = X;
									  if (max_y < Y) max_y = Y;
								  }
#if 1
double x_Size = (max_x-min_x);
double y_Size = (max_y-min_y);
min_x -= x_Size/10;
max_x += x_Size/10;
min_y -= y_Size/10;
max_y += y_Size/10;
#endif

								  //����� ��������� ����
								  Grid * grid = new Grid;
								  grid->gridSection.xLL = min_x;
								  grid->gridSection.yLL = min_y;
									  
								  grid->gridSection.nRow = 400;
								  grid->gridSection.nCol = 400;									  

								  double xSize = (max_x-min_x) / (grid->gridSection.nCol-1);
								  double ySize = (max_y-min_y) / (grid->gridSection.nRow-1);

								  if (xSize > ySize) ySize = xSize;
								  else xSize = ySize;

								  grid->gridSection.nCol = (long)(max_x-min_x)/xSize + 1;
								  grid->gridSection.nRow = (long)(max_y-min_y)/ySize + 1;
                                  
								  grid->gridSection.xSize = (max_x-min_x) / (grid->gridSection.nCol-1);
								  grid->gridSection.ySize = (max_y-min_y) / (grid->gridSection.nRow-1);

								  int ( *griddata_fun)(HWND, vector<double>&, vector<double>&, vector<double>&,  Grid *, void *, bool);

								  int griddata_fun_number = 0;
								  
								  cout << "griddata_fun_number [1,2,3]" << endl;
								  cout << "1 - griddata_v4 with GreenFun" << endl;
								  cout << "2 - griddata_2 with any dist_fun" << endl;
								  cout << "3 - griddata_3 with triangulation and interpolation" << endl;
								  cout << "4 - griddata_3 with triangulation and interpolation with default parameters" << endl;
								  cout << "5 - griddata_3 with triangulation and interpolation with default parameters use contour" << endl;
								  cin >> griddata_fun_number;

								  griddata_3_param param3;                                  
								  FillDefaultParam(param3);	



								  void * _param = NULL;
								  switch (griddata_fun_number)
								  {
								  case 1:
									  griddata_fun = griddata_v4;
									  break;
								  case 2:
									  griddata_fun = griddata_2;
									  break;
								  case 3:
									  _param = NULL;
									  griddata_fun = griddata_3;
									  break;
								  case 4:
									  param3.use_contour = false;
									  _param = &param3;									  
									  griddata_fun = griddata_3;
									  break;
								  case 5:
									  param3.use_contour = true;
									  _param = &param3;									  
									  griddata_fun = griddata_3;
									  break;
								  default:
									  return 0;
								  }






								  //griddata(NULL, VX, VY, VZ, grid, NULL, NULL, NULL);
								  //griddata_v4(NULL, VX, VY, VZ, grid);
								  //griddata_2(NULL, VX, VY, VZ, grid);
								  //griddata_3(NULL, VX, VY, VZ, grid);
								  bool to_allocate = true; 
								  if (griddata_fun(NULL, VX, VY, VZ, grid, _param, to_allocate) == 0) 
								  {
									  SaveAsSurfer7Grid(grd_file, grid);
									  //-----------------------------------
									  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
									  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
									  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
									  COLORREF color = RGB(255,255,0); int zflag = 0;
									  strcpy(szPath, grd_file);
									  long id_surf = pSurfDoc->GetIDSurfForNewGridDataOrSurface();
									  BYTE podoshva = 0; long id_ige = -1;
									  pSurfDoc->AddSurf(id_surf, podoshva, id_ige, zflag, grid, color);
									  if (pSurfDoc->m_surfaces.SetCurrentMsgOnLast() && pSurfDoc->m_surfaces.msgSize() > 1)
									  {		
										  DrawNewSurf(pSurfDoc);
									  }
									  else
									  {
										  pSurfDoc->ZoomView();
										  DrawSurfs(pSurfDoc);
									  }
									  //====== �������������� ��� � ������ ���������
									  RECT rect;
									  GetClientRect(hWnd,&rect);
									  InvalidateRect(hWnd,&rect, true);
									  //-----------------------------------
									  FreeDoubleMat(grid->gridSection.z);
								  }
								  delete grid;

							  }
						  }
						  delete vectors;
					  }
				  }
				  break;
			  case ID_WINSURF_FILE_IMPORT:
				  {
					  vdouble xi,yi,zi;
					  vdouble x,y,z;
					  vdouble xc,yc;//������
					  vdouble visible;

					  int zflag = 0;

					  bool countured = false;

					 // char dat_filename[255];

					if (OpenFileDlg(hWnd, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
					{
							/*char * p;
							p = strrchr(szPath,'\\');
							if (p)
								strcpy(dat_filename, p+1);
							else
							{
								p = strrchr(szPath,'/');
								if (p)
									strcpy(dat_filename, p+1);
								else
									strcpy(dat_filename, "dat_file");
							}
							p = strrchr(dat_filename,'.');
							if (p)
								*p = '\0';*/

						if (ReadDatFile(szPath, x, y, z) == 0)
						{
							/*int answer = MessageBox(0, 
							"If you want to create grid as gorisontal surf press YES?\nIf you want to create grid as vertical surf press NO and select X or Y base\nIf yes wait, please", 
							"Surf", MB_YESNOCANCEL | MB_ICONQUESTION);
							if ( answer == IDYES)
							{
								//xi = dsequence(double(x.Min()), long(110), double(x.Max()));
								//yi = dsequence(double(y.Min()), long(100), double(y.Max()));
								xi = dsequence(double(x.Min()), double(40), double(x.Max()));
								yi = dsequence(double(y.Min()), double(40), double(y.Max()));
								zi.resize(xi.Length(), yi.Length(), 0.0 );
								//visible.resize(xi.Length(), yi.Length(), 1.0 );
								if (griddata(hWnd, x, y, z, xi, yi, zi) != 0)
								{
									break;
								}
							}
							if ( answer == IDNO)
							{
								if (x.Max() - x.Min() < y.Max() - y.Min())
									zflag = 2;
								else
									zflag = 1;

								if(zflag == 1)
								{
									xi = dsequence(double(z.Min()), long(50), double(z.Max()));
									yi = dsequence(double(y.Min()), long(50), double(y.Max()));
									//xi = dsequence(double(z.Min()), double(50), double(z.Max()));
									//yi = dsequence(double(y.Min()), double(50), double(y.Max()));
									zi.resize(xi.Length(), yi.Length(), 0.0 );
									//visible.resize(xi.Length(), yi.Length(), 1.0 );
									if (griddata(hWnd, z, y, x, xi, yi, zi) != 0)
									{
										break;
									}
								}
								if(zflag == 2)
								{
									xi = dsequence(double(x.Min()), long(50), double(x.Max()));
									yi = dsequence(double(z.Min()), long(50), double(z.Max()));
									//xi = dsequence(double(x.Min()), double(50), double(x.Max()));
									//yi = dsequence(double(z.Min()), double(50), double(z.Max()));
									zi.resize(xi.Length(), yi.Length(), 0.0 );
									//visible.resize(xi.Length(), yi.Length(), 1.0 );
									if (griddata(hWnd, x, z, y, xi, yi, zi) != 0)
									{
										break;
									}
								}											
							}*/
						}
						else
						{
							MessageBox(0, "Data file was not read", "ReadDatFile", 0);
							break;
						}
					}
					else
						break;

					  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
					  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()


							COLORREF color = 0;
							ChooseSurfColor(hWnd, color);
#if 0
							pSurfDoc->AddSpheres(x,y,z,color);
#else
							pSurfDoc->AddSpheresAsCollection(x,y,z,color, szPath);
#endif

						pSurfDoc->ZoomView();

						pSurfDoc->Draw();

						//====== �������������� ��� � ������ ���������
						RECT rect;
						GetClientRect(hWnd,&rect);
						InvalidateRect(hWnd,&rect, true);

				  }
				  break;
			  case ID_FILE_IMPORT_DIGITAL_MODEL:
				  {
					  long nCol = 1201;// �� ����� *.hdr
					  long nRow = 1681;// �� ����� *.hdr
					  
					  double xLeft = 46.0; double xRight = 56.0;
					  double yLow  = 35.0; double yHigh  = 49.0;
					  double zMin = -1050.61; double zMax = 5398.34;

					  if (OpenFileDlg(hWnd, 
						  "Digital Model Header (*.hdr)\0*.hdr\0"
						  "All files \0*.*\0"
						  ) == S_OK)
					  {	
						  if(ImportDigitalModelHeader(nRow, nCol, xLeft, xRight, yLow, yHigh, zMin, zMax) == 0)
						  {
								if (OpenFileDlg(hWnd, 
									"Surfer 7 (*.dat)\0*.dat\0"
									"All files \0*.*\0"
									) == S_OK)
								{	
									win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
									project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
									SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
				
									double xLL = xLeft;
									double yLL = yLow;
									double xSize = (xRight - xLeft) / (nCol - 1);
									double ySize = (yHigh  - yLow ) / (nRow - 1);

									if(ImportDigitalModel(pGrid, nRow, nCol, xLL, yLL, xSize, ySize, zMin, zMax) == 0)
									{
										COLORREF color = 0;
										ChooseSurfColor(hWnd, color);
										short zflag = 0;
										long id_surf = pSurfDoc->GetIDSurfForNewGridDataOrSurface();
										BYTE podoshva = 0; long id_ige = -1;
			#if FAST_GRID_LOADING
										pSurfDoc->AddSurf(id_surf, podoshva, id_ige, zflag, pGrid, color);
			#else
										pSurfDoc->AddSurf(id_surf, podoshva, id_ige, zflag, pCGrid, color);
			#endif
										// free 
										if (pGrid->gridSection.z) 
										{
											//HeapFree( GetProcessHeap(), 0, pGrid->z); 
											FreeDoubleMat(pGrid->gridSection.z);
											pGrid->gridSection.z = NULL;
										}
										if (pGrid->faultSection.traces)
										{
											delete[] pGrid->faultSection.traces;
											pGrid->faultSection.traces = NULL; 
											pGrid->faultSection.nTraces = 0;
										}								
										if (pGrid->faultSection.vertexes)
										{
											delete[] pGrid->faultSection.vertexes;
											pGrid->faultSection.vertexes = NULL; 
											pGrid->faultSection.nVertices = 0;
										}


										pSurfDoc->ZoomView();
										pSurfDoc->Draw();
										//====== �������������� ��� � ������ ���������
										RECT rect;
										GetClientRect(hWnd,&rect);
										InvalidateRect(hWnd,&rect, true);	
									}
								}
						  }
					  }
				  }
				  break;
				}
				break;

		case WM_DESTROY:
			{
				if (m_hRC)
				{
					wglDeleteContext(m_hRC);
					m_hRC = 0;
				}
			  if ( lpSurfPropDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpSurfPropDlgMem );

			  if ( lpDrillsDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpDrillsDlgMem );

			  if ( lpSurfZoomDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpSurfZoomDlgMem );
			  if ( lpSurfCutsPlaneDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpSurfCutsPlaneDlgMem );
			  if ( lpSurfDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpSurfDlgMem );
			  if ( lpSurfViewDlgMem )
				  HeapFree( GetProcessHeap(), 0, lpSurfViewDlgMem );


#if FAST_GRID_LOADING
			  if (pGrid) delete pGrid; 
#else
			  if (pCGrid) delete pCGrid;
#endif
			  win_ogl_view * woglv = (win_ogl_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA);
			  project * prj; if (woglv) prj = woglv->GetProject(); else return -1;
			  SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()

			  if (pSurfDoc) delete pSurfDoc;

			  if (m_hdc) ReleaseDC(hWnd,m_hdc);


			}
			KillTimer(hWnd,IDT_TIMER_SURF);

			PostQuitMessage(0);
			break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}


// Mesage handler for about box.
LRESULT CALLBACK AboutSurfCube(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
LRESULT CALLBACK DlgProcPrintSurfParam( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPPRINTSURFDLGDATA lpPrintDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			lpPrintDlgMem = (LPPRINTSURFDLGDATA)lParam;








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
				if( lastError == lastError) // ������� ������ �� ��������������
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
						if (lastError == 122)// ������� ������, ��������� ��� �������� ������� ������� ����
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
				else// ������� ������ ��������������
				{
					if (lastError == 122)// ������� ������, ��������� ��� �������� ������� ������� ����
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
						LastErrorExit(lastError, "EnumPrinters1");
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
		case IDC_COMBO_PAPER_SIZE:
			lpPrintDlgMem->dmPaperSize = (short) SendDlgItemMessage( hDlg, IDC_COMBO_PAPER_SIZE, CB_GETCURSEL, 0, (LPARAM)0 );
			break;
		case IDPRINT_SETUP :
			{
				// ��� ��������
				GetDlgItemText(hDlg,
					IDC_COMBO_PRINTER_NAME,
					lpPrintDlgMem->szPrinterName, 31);
				if (strlen(lpPrintDlgMem->szPrinterName) > 0)
					lpPrintDlgMem->bPrinterNameFound  = true;

				// ����� �����
				BOOL bTranslated;
				lpPrintDlgMem->dmCopies = 
					(short)GetDlgItemInt(hDlg, IDC_EDIT_COPIES, &bTranslated, false);
				if (!bTranslated)
					lpPrintDlgMem->dmCopies = 1;

				SendMessage(lpPrintDlgMem->hWnd, WM_COMMAND, ID_PRINT_START, (LPARAM)1);
				EndDialog( hDlg, IDPRINT );
			}
			break;
		case IDPRINT :
			{
				// ��� ��������
				GetDlgItemText(hDlg,
					IDC_COMBO_PRINTER_NAME,
					lpPrintDlgMem->szPrinterName, 31);
				if (strlen(lpPrintDlgMem->szPrinterName) > 0)
					lpPrintDlgMem->bPrinterNameFound  = true;

				// ����� �����
				BOOL bTranslated;
				lpPrintDlgMem->dmCopies = 
					(short)GetDlgItemInt(hDlg, IDC_EDIT_COPIES, &bTranslated, false);
				if (!bTranslated)
					lpPrintDlgMem->dmCopies = 1;

				SendMessage(lpPrintDlgMem->hWnd, WM_COMMAND, ID_PRINT_START, (LPARAM)0);
				EndDialog( hDlg, IDPRINT );
			}
			break;		
		case IDOK :
			{
				// ��� ��������
				GetDlgItemText(hDlg,
					IDC_COMBO_PRINTER_NAME,
					lpPrintDlgMem->szPrinterName, 31);
				if (strlen(lpPrintDlgMem->szPrinterName) > 0)
					lpPrintDlgMem->bPrinterNameFound  = true;

				// ����� �����
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

