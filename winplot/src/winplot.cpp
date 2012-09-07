
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "../../resource.h"
#include "winplot.h"
#include "..\..\tools\src\filedlg.h"

extern HINSTANCE hInst;   // текущий экземпляр
//extern LPCTSTR lpszAppName;
const char * lpszPlotTitle   = "Plot";
const char * lpszWinPlot   = "WINPLOT";
const char * lpszWinPlotName   = "MyWINPLOT";
extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false);

//#define SCALE_Y 0.6
int BeginWinPlot(MSG &msg, WNDCLASSEX &wc)
{
	// Регистрация класса главного окна приложения.
	//............................................
//	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc   = (WNDPROC)WinPlotProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = sizeof(LONG);
	wc.hInstance     = hInst;
	wc.hIcon         = LoadIcon( hInst, lpszWinPlotName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
//	wc.lpszMenuName  = lpszAppName;
//	wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU_WINPLOT);
	wc.lpszMenuName  = lpszWinPlotName;
	wc.lpszClassName = lpszWinPlot;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = (HICON__ *) LoadImage( hInst, lpszWinPlotName,
								 IMAGE_ICON, 16, 16,
								 LR_DEFAULTCOLOR );

	wc.cbWndExtra    = sizeof(LONG);

	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","WinPlot",0);
			return( FALSE );
		}
	}

	// Регистрация классов дочерних окон MDI.
	//.....................................................
#ifdef USE_OWN_DC
//	wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
#endif
	return (TRUE);
}
WPARAM StartWinPlot(MSG &msg, CGraph2* pGraph2)
{
	HWND hPlotWnd = NULL;
	hPlotWnd = CreateWindow( lpszWinPlot,
                    	lpszPlotTitle,
                    	WS_OVERLAPPEDWINDOW,
                    	CW_USEDEFAULT, 0,
                    	CW_USEDEFAULT, 0,
                    	NULL,
                    	NULL,
                    	hInst,
                    	(void *)pGraph2
                    	);
	if ( !hPlotWnd )
	{
		ErrorExit("CreateWindow");
		MessageBox(0,"!hPlotWnd","WinPlot",0);
		return( FALSE );
	}
	ShowWindow( hPlotWnd, /*nCmdShow*/1 );
	UpdateWindow( hPlotWnd );
	while( GetMessage( &msg, NULL, 0, 0) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	} 
	return( msg.wParam );
}

WPARAM WinPlot(vdouble& x, vdouble& y)
{
	MSG        msg;
	WNDCLASSEX wc;
	if(!BeginWinPlot(msg, wc))
			return( FALSE );
	CGraph2* pGraph2 = new CGraph2(x, y);
	return StartWinPlot(msg, pGraph2);
}
WPARAM WinPlot(Vector<vdouble>& vx, Vector<vdouble>& vy)
{
	MSG        msg;
	WNDCLASSEX wc;
	if(!BeginWinPlot(msg, wc))
			return( FALSE );
	CGraph2* pGraph2 = new CGraph2(vx, vy);
	return StartWinPlot(msg, pGraph2);
}
WPARAM WinPlot(vector<vector<double> >& vx, vector<vector<double> >& vy)
{
	MSG        msg;
	WNDCLASSEX wc;
	if(!BeginWinPlot(msg, wc))
			return( FALSE );
	CGraph2* pGraph2 = new CGraph2(vx, vy);
	return StartWinPlot(msg, pGraph2);
}
WPARAM WinPlot(vector<double>& vx, vector<double>& vy)
{
	MSG        msg;
	WNDCLASSEX wc;
	if(!BeginWinPlot(msg, wc))
			return( FALSE );
	CGraph2* pGraph2 = new CGraph2(vx, vy);
	return StartWinPlot(msg, pGraph2);
}

WPARAM WinPlot(vector<double>& vx, vector<double>& vy, size_t i1, size_t i2)
{
	MSG        msg;
	WNDCLASSEX wc;
	if(!BeginWinPlot(msg, wc))
			return( FALSE );
	CGraph2* pGraph2 = new CGraph2(vx, vy, i1, i2);
	return StartWinPlot(msg, pGraph2);
}
typedef struct
{
	HWND hWnd;
	CGraph2* pGraph2;
	double xMin;
	double xMax;
	double xStep;
	double yMin;
	double yMax;
	double yStep;
} PLOTSCALEDLGDATA, *LPPLOTSCALEDLGDATA;

LRESULT CALLBACK DlgProcPlotScale( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static LPPLOTSCALEDLGDATA lpPlotScaleDlgMem;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			char s[125];
			
			
			lpPlotScaleDlgMem = (LPPLOTSCALEDLGDATA)lParam;

			sprintf(s,"%lf",lpPlotScaleDlgMem->xMin);
			SetDlgItemText(hDlg, IDC_EDIT_SCALE_X_MIN,s);
			sprintf(s,"%lf",lpPlotScaleDlgMem->xMax);
			SetDlgItemText(hDlg, IDC_EDIT_SCALE_X_MAX,s);
			sprintf(s,"%lf",lpPlotScaleDlgMem->xStep);
			SetDlgItemText(hDlg, IDC_EDIT_SCALE_X_STEP,s);

			sprintf(s,"%lf",lpPlotScaleDlgMem->yMin);
			SetDlgItemText(hDlg, IDC_EDIT_SCALE_Y_MIN,s);
			sprintf(s,"%lf",lpPlotScaleDlgMem->yMax);
			SetDlgItemText(hDlg, IDC_EDIT_SCALE_Y_MAX,s);
			sprintf(s,"%lf",lpPlotScaleDlgMem->yStep);
			SetDlgItemText(hDlg, IDC_EDIT_SCALE_Y_STEP,s);

			SendMessage(hDlg, WM_COMMAND, IDC_SCALE_LEFT_RIGHT, 0);
			
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_WINPLOT_LINE_WRITE,
				lpPlotScaleDlgMem->pGraph2->m_bLineWrite ? BST_CHECKED : BST_UNCHECKED );
			//IDC_COMBO_SCALE_LEFT_RIGHT
			//IDC_BUTTON_SCALE_LEFT_RIGHT
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{			
		case IDC_CHECK_WINPLOT_LINE_WRITE:
			{
				lpPlotScaleDlgMem->pGraph2->m_bLineWrite = IsDlgButtonChecked( hDlg, IDC_CHECK_WINPLOT_LINE_WRITE) == BST_CHECKED;
				/*char sss[55];
				sprintf(sss,"%d", lpPlotScaleDlgMem->pGraph2->m_bLineWrite);
				MessageBox(0,sss,"",0);*/
			}
			break;
		case IDC_BUTTON_SCALE_LEFT_RIGHT :
			{
				long iPlot = (long)SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_LEFT_RIGHT, CB_GETCURSEL,
							0,(LPARAM)0 );
				int iplot = 0;
				bool done = false;
				if( lpPlotScaleDlgMem 
					&& lpPlotScaleDlgMem->pGraph2 
					&& lpPlotScaleDlgMem->pGraph2->m_vbYScale.SetCurrentMsgOnFirst() )
				{
					do
					{
						if (iplot == iPlot)
						{
							bool isLeft = lpPlotScaleDlgMem->pGraph2->m_vbYScale.GetCurrentMsg();
							isLeft = isLeft ? false : true;
							lpPlotScaleDlgMem->pGraph2->m_vbYScale.SetCurrentMsg(&isLeft);
						}

						iplot++;
					}
					while(lpPlotScaleDlgMem->pGraph2->m_vbYScale.IncrementCurrentMsg() && !done);
				}
				SendMessage(hDlg, WM_COMMAND, IDC_SCALE_LEFT_RIGHT, iPlot);
				SendMessage(lpPlotScaleDlgMem->hWnd, WM_COMMAND, ID_WINPLOT_SCALE_LEFT_RIGHT,0);

			}
			break;
		case IDC_SCALE_LEFT_RIGHT :
			{
				char ss[125];
				SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_LEFT_RIGHT, CB_RESETCONTENT, 0,0);
				int iplot = 1;
				if( lpPlotScaleDlgMem 
					&& lpPlotScaleDlgMem->pGraph2 
					&& lpPlotScaleDlgMem->pGraph2->m_vbYScale.SetCurrentMsgOnFirst() )
				{
					do
					{
						if (lpPlotScaleDlgMem->pGraph2->m_vbYScale.GetCurrentMsg())
						{
							sprintf(ss,"plot %d right",iplot);
						}
						else
						{
							sprintf(ss,"plot %d left",iplot);
						}

						SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_LEFT_RIGHT, CB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)ss);
						iplot++;
					}
					while(lpPlotScaleDlgMem->pGraph2->m_vbYScale.IncrementCurrentMsg() );
				}
				SendDlgItemMessage( hDlg, IDC_COMBO_SCALE_LEFT_RIGHT, CB_SETCURSEL,
					(WPARAM)lParam,(LPARAM)0 );			
			}
			break;
		case IDOK :
			{
					char str[15];
					
					GetDlgItemText(hDlg, IDC_EDIT_SCALE_X_MIN, str, 14);
					lpPlotScaleDlgMem->xMin = atof(str);

					GetDlgItemText(hDlg, IDC_EDIT_SCALE_X_MAX, str, 14);
					lpPlotScaleDlgMem->xMax = atof(str);

					GetDlgItemText(hDlg, IDC_EDIT_SCALE_X_STEP, str, 14);
					lpPlotScaleDlgMem->xStep = atof(str);

					GetDlgItemText(hDlg, IDC_EDIT_SCALE_Y_MIN, str, 14);
					lpPlotScaleDlgMem->yMin = atof(str);

					GetDlgItemText(hDlg, IDC_EDIT_SCALE_Y_MAX, str, 14);
					lpPlotScaleDlgMem->yMax = atof(str);

					GetDlgItemText(hDlg, IDC_EDIT_SCALE_Y_STEP, str, 14);
					lpPlotScaleDlgMem->yStep = atof(str);

				SendMessage(lpPlotScaleDlgMem->hWnd, WM_COMMAND, ID_WINPLOT_SCALE_OK,0);

				EndDialog( hDlg, IDPRINT );
			}
			break;
		case ID_PLOT_SCALE_DEFAULT:
			{
				SendMessage(lpPlotScaleDlgMem->hWnd, WM_COMMAND, ID_WINPLOT_SCALE_DEFAULT,0);
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


HRESULT OpenPlot(HWND hWnd, CGraph2* pGraph2)
{
    HRESULT hr = S_OK;
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	const int n=255; // length of buffer string line
	char szBuff[n], *p1, *p2, *p3; // buffer string line
	char buf[255];
//	char delimiter = '\t';
	char delimiter = ',';
	double x,y;
	double test_t, test_t0;

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE)
	{
		FILE *stream;
		if ((stream = fopen(ofn.lpstrFile,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Open Plot", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
		int maxj = 0;
		while (!feof(stream))
		{
			fgets(szBuff,n,stream);
			if (!feof(stream))
			{
				p1 = szBuff;
				x = atof(p1);

				int j = 0;

				while( (p2 = strchr(p1, delimiter)) != NULL)
				{
					p1 = p2+1;
					if ( (p3 = strchr(p1, delimiter)) != NULL)
					{
						if (p3-p1 > 1)
						{
							strncpy(buf, p1, p3-p1);
							y = atof(buf);
						}
					}
					else
					{
						if ( (unsigned int)(p1-szBuff+1) < strlen(szBuff))
						{
							y = atof(p1);
						}
					}
					j++;
				}
				if (j > maxj)
					maxj = j;
			}
		}
		pGraph2->clear();
		bool byscale = false;
		for (int j = 0; j < maxj; j++)
		{

//			char str[50];
//			sprintf(str, "byscale = %d", byscale);
//			MessageBox(0,str,"",0);

			pGraph2->m_vPoints.CreateNewVect();
			pGraph2->m_vbYScale.AddMsg(&byscale);
//			byscale ^= true;
		}

		if ((stream = fopen(ofn.lpstrFile,"rt")) == NULL)
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
#if 1
				p1 = szBuff;
				x = atof(p1);

				if (i==0/* && iFile==1*/)
				{
					test_t0 = x;
				}
				else
				{
					test_t = x;
					if (test_t > test_t0)
					{
						test_t0 = test_t;
					}
					else
					{
						char errstr[255];
						sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%lf",
							szBuff, ofn.lpstrFile, (test_t0 - test_t) );
						MessageBox(0,errstr,"import()",0);
					//	break;
					}
				}

				int j = 0;
				double multipl = 1.4;

				while( (p2 = strchr(p1, delimiter)) != NULL)
				{
					p1 = p2+1;
					if ( (p3 = strchr(p1, delimiter)) != NULL)
					{
						if (p3-p1 > 1)
						{
							strncpy(buf, p1, p3-p1);
							y = atof(buf);
							//if (j == 2)
							//	y*=multipl;
							//if (y!=0.0)
								pGraph2->AddPointValue(j,x,y);
						}
					}
					else
					{
						if ( (unsigned int)(p1-szBuff+1) < strlen(szBuff))
						{
							y = atof(p1);
							//if (j == 2)
							//	y*=multipl;

							//if (y!=0.0)
								pGraph2->AddPointValue(j,x,y);
						}
					}
					j++;
				}

#else
				rez = sscanf(szBuff,"%lf %lf",
					&x, &y);
				if (rez == 2 && rez != EOF)
				{
					if (i==0/* && iFile==1*/)
					{
						test_t0 = x;
					}
					else
					{
						test_t = x;
						if (test_t > test_t0)
						{
							test_t0 = test_t;
						}
						else
						{
							char errstr[255];
							sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%lf",
								szBuff, ofn.lpstrFile, (test_t0 - test_t) );
							MessageBox(0,errstr,"import()",0);
						//	break;
						}
					}
					pGraph2->AddPointValue(0,x,y);

				}
				i++;
#endif



			}
		}
		fclose(stream);
	}

    if (FAILED(hr))
    {
        MessageBox( hWnd, "Unabled to open the specified file!", "Open failed!", MB_OK);
    }

    return hr;

}



LRESULT CALLBACK WinPlotProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	static HDC  hMemDC;
	static HBITMAP hBitmap;
	static int bmWidth, bmHeight;

	static HENHMETAFILE hMetaFile = NULL;
	static LPPLOTSCALEDLGDATA	lpPlotScaleDlgData;

   switch( uMsg )
   {
      case WM_CREATE  :
              {
				  hMemDC = NULL;
				  hBitmap = NULL;
				CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
				SetWindowLongPtr(hWnd,	GWLP_USERDATA,(LONG_PTR)pcs->lpCreateParams);
				SendMessage(hWnd, WM_COMMAND, ID_DRAW_METAFILE_PLOT,4);
				//SendMessage(hWnd, WM_COMMAND, ID_DRAW_METAFILE_PLOT,0);

				lpPlotScaleDlgData = (LPPLOTSCALEDLGDATA)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
					sizeof( PLOTSCALEDLGDATA ) );
				lpPlotScaleDlgData->hWnd = hWnd;
				lpPlotScaleDlgData->pGraph2 = (CGraph2*)pcs->lpCreateParams;

              }
              break;
	  case WM_SIZE:
		  {
//			  SendMessage(hWnd, WM_COMMAND, ID_DRAW_BITMAP_PLOT,0);

		  }
		  break;

      case WM_PAINT :
              {
					PAINTSTRUCT  ps;
					RECT        rect;
					BeginPaint( hWnd, &ps );
					GetClientRect(hWnd,&rect);
#if 0
					BitBlt( ps.hdc, 0, 0, rect.right, rect.bottom,
						hMemDC, 0, 0, SRCCOPY );
#else
					PlayEnhMetaFile( ps.hdc, hMetaFile, &rect );
#endif

					EndPaint( hWnd, &ps );
              }
              break;
      case WM_COMMAND :
              switch( LOWORD( wParam ) )
              {
			  case  ID_WINPLOT_SCALE :
				  {
				CGraph2* pGraph2 = 
					(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  pGraph2->GetScale(
						  lpPlotScaleDlgData->xMin,
						  lpPlotScaleDlgData->xMax,
						  lpPlotScaleDlgData->xStep,
						  lpPlotScaleDlgData->yMin,
						  lpPlotScaleDlgData->yMax,
						  lpPlotScaleDlgData->yStep);

					DialogBoxParam( hInst, MAKEINTRESOURCE(IDD_DIALOG_WINPLOT_SCALE), hWnd,
                      (DLGPROC)DlgProcPlotScale,(LPARAM)lpPlotScaleDlgData );
				  }
				  break;
			  case  ID_WINPLOT_SCALE_OK :
				  {
					  CGraph2* pGraph2 = 
					(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  pGraph2->SetScale(
						  lpPlotScaleDlgData->xMin,
						  lpPlotScaleDlgData->xMax,
						  lpPlotScaleDlgData->xStep,
						  lpPlotScaleDlgData->yMin,
						  lpPlotScaleDlgData->yMax,
						  lpPlotScaleDlgData->yStep);
					SendMessage(hWnd, WM_COMMAND, ID_DRAW_METAFILE_PLOT,1);
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case  ID_WINPLOT_SCALE_DEFAULT :
				  {
					  CGraph2* pGraph2 = 
					(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  pGraph2->Scale(SCALE_FLAG_COMMON);
					SendMessage(hWnd, WM_COMMAND, ID_DRAW_METAFILE_PLOT,1);
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case  ID_WINPLOT_SCALE_LEFT_RIGHT :
				  {
					  CGraph2* pGraph2 = 
					(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					SendMessage(hWnd, WM_COMMAND, ID_DRAW_METAFILE_PLOT,0);
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				  }
				  break;
				   
			  case  ID_WINPLOT_FILE_OPEN:
				  {
					  CGraph2* pGraph2 = 
					(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
					  OpenPlot(hWnd, pGraph2 );
//					  SendMessage(hWnd, WM_COMMAND, ID_DRAW_BITMAP_PLOT,0);
				
					  SendMessage(hWnd, WM_COMMAND, ID_DRAW_METAFILE_PLOT,0);
					RECT rect;
					GetClientRect(hWnd,&rect);
					InvalidateRect(hWnd,&rect, true);
				  }
				  break;
			  case  ID_PLOT_SAVE:
				  {
					  SavePlot(hWnd, hMetaFile , "");
				  }
				  break;
                 case ID_DRAW_METAFILE_PLOT :
					 {
						 HDC  hMetaDC;
						 HDC  hRefDC;
						 RECT rect;
						 int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
						 int  iMMPerPelX, iMMPerPelY;

						 hRefDC = GetDC( hWnd );

						 // Вычислить размер клиентской области в единицах 
					 // длины 0,01 мм.
						 //................................................
						 iWidthMM    = GetDeviceCaps(hRefDC, HORZSIZE);
						 iHeightMM   = GetDeviceCaps(hRefDC, VERTSIZE);
						 iWidthPels  = GetDeviceCaps(hRefDC, HORZRES);
						 iHeightPels = GetDeviceCaps(hRefDC, VERTRES);

						 iMMPerPelX = (iWidthMM * 100)/iWidthPels;
						 iMMPerPelY = (iHeightMM * 100)/iHeightPels;

						 GetClientRect(hWnd, &rect);

						RECT rectM;
						rectM.top = 0;
						rectM.left = 0;

						rectM.right = rect.right * iMMPerPelX;
						rectM.bottom = rect.bottom * iMMPerPelY;

						 //rect.right = rect.right * iMMPerPelX;
						 //rect.bottom = rect.bottom * iMMPerPelY;

						 // Создать расширенный метафайл.
						 //.............................
						 hMetaDC = CreateEnhMetaFile( hRefDC, NULL, &rectM,
													  "Plot Metafile" );
						 if ( hMetaDC )
						 {
							CGraph2* pGraph2 = 
								(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
#if 0
							 if(lParam == 0)
							 {
								pGraph2->Scale(SCALE_FLAG_COMMON);
							 }
							pGraph2->Draw(hMetaDC, rect);
							pGraph2->DrawLine(hMetaDC, SCALE_FLAG_COMMON);
#else
							switch (lParam)
							{
							case 0:
								{
									//pGraph2->Scale(SCALE_FLAG_COMMON);
									//pGraph2->Draw(hMetaDC, rect);
									//pGraph2->DrawLine(hMetaDC, SCALE_FLAG_COMMON);

									pGraph2->Scale(SCALE_FLAG_LEFT);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_LEFT);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_LEFT);

									

									pGraph2->Scale(SCALE_FLAG_RIGHT);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_RIGHT);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_RIGHT);

								}
								break;
							case 1: //Вызывается после ручной установки шкалы
								{
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_COMMON);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_COMMON);
								}
								break;
							case 2:
								{
									pGraph2->Scale(SCALE_FLAG_COMMON);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_COMMON);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_COMMON);
								}
								break;
							case 3:
								{
// и так и так работает
#if 0 
									pGraph2->Scale(SCALE_FLAG_COMMON);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_COMMON);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_COMMON, true);
#else
									pGraph2->Scale(SCALE_FLAG_LEFT);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_LEFT);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_LEFT, true);
									

									pGraph2->Scale(SCALE_FLAG_RIGHT);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_RIGHT);
									pGraph2->DrawLine(hMetaDC, SCALE_FLAG_RIGHT, true);
#endif

								}
								break;
							case 4:
								{
									pGraph2->Scale(SCALE_FLAG_COMMON);
									pGraph2->Draw(hMetaDC, rect, SCALE_FLAG_COMMON);
									//pGraph2->DrawLine(hMetaDC, SCALE_FLAG_RIGHT, true);
									pGraph2->DrawPoints(hMetaDC, SCALE_FLAG_COMMON, true);
								}
								break;
							}
#endif
							hMetaFile = CloseEnhMetaFile( hMetaDC );
							if(hMetaFile == NULL)
								ErrorExit("CloseEnhMetaFile");
						 }
						 else
							ErrorExit("CreateEnhMetaFile");

						 ReleaseDC( hWnd, hRefDC );

					 }
					 break;
                 case ID_DRAW_BITMAP_PLOT :
					 {
							HDC  hDC = GetDC( hWnd );
							if (hDC == NULL)
							{
								ErrorExit("GetDC");
								return 0;
							}

							RECT rect;
							GetClientRect(hWnd, &rect);
							bool toSelectObject = false;
							// Создать совместимый контекст устройства.
							//........................
							if (!hMemDC)
							{
								hMemDC = CreateCompatibleDC( hDC );
								if (hMemDC == NULL)
								{
									ErrorExit("CreateCompatibleDC");
									return 0;
								}
								else
									toSelectObject = true;
							}

							if(!hBitmap)
							{

								// Создать совместимое растровое изображение.
								//............................
								hBitmap = CreateCompatibleBitmap( hDC, rect.right, rect.bottom );
								if (hBitmap == NULL)
								{
									ErrorExit("CreateCompatibleBitmap");
									return 0;
								}
								else
									toSelectObject = true;

								bmWidth		= rect.right;
								bmHeight	= rect.bottom;
								//bBitmapCreated = true;

							}
							else
							{
								if (bmWidth != rect.right || bmHeight != rect.bottom)
								{
									if (!DeleteObject( hBitmap ))
									{
										ErrorExit("DeleteObject");
										return 0;
									}
									// Создать совместимое растровое изображение.
									//............................
									hBitmap = CreateCompatibleBitmap( hDC, rect.right, rect.bottom);
									if (hBitmap == NULL)
									{
										ErrorExit("CreateCompatibleBitmap2");
										return 0;
									}
									else
										toSelectObject = true;

									bmWidth		= rect.right;
									bmHeight	= rect.bottom;

								}
							}
							if (toSelectObject)
							{
								// Выбрать растровое изображение для совместимого
								// контекста устройства и начертить на нем
								// графический объект.
								//..............................
								SelectObject( hMemDC, hBitmap );
							}
							HPEN pen = CreatePen(PS_SOLID, 0, RGB(255,255,255));
							SelectObject(hMemDC, pen);
							Rectangle( hMemDC, 0, 0, rect.right, rect.bottom);

							CGraph2* pGraph2 = 
								(CGraph2*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
							 if(lParam == 0)
							 {
								pGraph2->Scale(SCALE_FLAG_COMMON);
							 }
							pGraph2->Draw(hMemDC, rect, SCALE_FLAG_COMMON);
							pGraph2->DrawLine(hMemDC, SCALE_FLAG_COMMON);



					 }
					 break;
                 case ID_WINPLOT_FILE_EXIT :
                        DestroyWindow( hWnd );
                        break;
              }
              break;

      case WM_DESTROY :
		  {	
			  if ( lpPlotScaleDlgData )
				  HeapFree( GetProcessHeap(), 0, lpPlotScaleDlgData );

              PostQuitMessage(0);
		  }
              break;

      default :
            return( DefWindowProc( hWnd, uMsg, wParam, lParam ) );
   }

   return( 0L );
}
