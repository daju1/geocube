#include "stdafx.h"
#include "..\..\tools\src\errorexit.h"
#include "AbortPrint.h"


extern BOOL bAbortPrinting;
extern HWND hAbortPrintingDlg;
extern HINSTANCE hInst;


// for OnPrint realization
#include "GLPrintMan.h"
#include "win32_graphics_view.h"
#include "..\..\surfdoc\src\DrawScene.h"

extern RECT store_rtMargin;
extern LOGFONT lf_Label;        // logical font structure
extern int UseGLFont( HDC hDC,  IN CONST LOGFONTA * plf_Label);
extern CGLPrintMan print;
void OnPrint(HWND hWnd, HDC hDC, bool bPreview, HDC hprinterDC, RECT * rcPreview) 
{
	RECT paper;
	paper.top		= 0;
	paper.left		= 0;
	paper.bottom	= 0;
	paper.right		= 0;

	int margin_left,
		margin_right,
		margin_top,
		margin_bottom;


	// get size of paper..
#if SLOW_PREVIEW
	if (bPreview) // it's preview..
#else
	if (false) // it's preview..
#endif
	{
		
		// Get the size of the default printer page
		paper.right  = GetDeviceCaps(hprinterDC, HORZRES);
		paper.bottom = GetDeviceCaps(hprinterDC, VERTRES);

		margin_left = store_rtMargin.left *  
			((float) GetDeviceCaps(hprinterDC, HORZRES)) 
			/ 
			((float) (GetDeviceCaps(hprinterDC, HORZSIZE)) * 100);

		margin_right = store_rtMargin.right *  
			((float) GetDeviceCaps(hprinterDC, HORZRES)) 
			/ 
			((float) (GetDeviceCaps(hprinterDC, HORZSIZE)) * 100);

		margin_top = store_rtMargin.top *  
			((float) GetDeviceCaps(hprinterDC, VERTRES)) 
			/ 
			((float) (GetDeviceCaps(hprinterDC, VERTSIZE)) * 100);

		margin_bottom = store_rtMargin.bottom *  
			((float) GetDeviceCaps(hprinterDC, VERTRES)) 
			/ 
			((float) (GetDeviceCaps(hprinterDC, VERTSIZE)) * 100);
	}
	else 
	{ 
		if (bPreview && rcPreview) // it's preview.
		{
			// print to paper
			paper.right  = rcPreview->right - rcPreview->left;
			paper.bottom = rcPreview->bottom - rcPreview->top;

			margin_left = store_rtMargin.left *  
				((float) paper.right) 
				/ 
				((float) (GetDeviceCaps(hprinterDC, HORZSIZE)) * 100);

			margin_right = store_rtMargin.right *  
				((float) paper.right) 
				/ 
				((float) (GetDeviceCaps(hprinterDC, HORZSIZE)) * 100);

			margin_top = store_rtMargin.top *  
				((float) paper.bottom) 
				/ 
				((float) (GetDeviceCaps(hprinterDC, VERTSIZE)) * 100);

			margin_bottom = store_rtMargin.bottom *  
				((float) paper.bottom) 
				/ 
				((float) (GetDeviceCaps(hprinterDC, VERTSIZE)) * 100);
		}
		else
		{
			// print to paper
			paper.right  = GetDeviceCaps(hDC, HORZRES);
			paper.bottom = GetDeviceCaps(hDC, VERTRES);

			margin_left = store_rtMargin.left *  
				((float) paper.right) 
				/ 
				((float) (GetDeviceCaps(hDC, HORZSIZE)) * 100);

			margin_right = store_rtMargin.right *  
				((float) paper.right) 
				/ 
				((float) (GetDeviceCaps(hDC, HORZSIZE)) * 100);

			margin_top = store_rtMargin.top *  
				((float) paper.bottom) 
				/ 
				((float) (GetDeviceCaps(hDC, VERTSIZE)) * 100);

			margin_bottom = store_rtMargin.bottom *  
				((float) paper.bottom) 
				/ 
				((float) (GetDeviceCaps(hDC, VERTSIZE)) * 100);
		}
	}
/*
printf ("OnPrint paper.right  = %d\n", paper.right );
printf ("OnPrint paper.bottom  = %d\n", paper.bottom );

printf ("OnPrint margin_left  = %d\n", margin_left );
printf ("OnPrint margin_right  = %d\n", margin_right );

printf ("OnPrint margin_top  = %d\n", margin_top );
printf ("OnPrint margin_bottom  = %d\n", margin_bottom );
*/
	// white polya
	{			
		HBRUSH hbrush;                  // brush handle
		hbrush = CreateSolidBrush(RGB(255,255,255));
		HBRUSH hbrushOld = (HBRUSH__ *)SelectObject(hDC, hbrush);

		FillRect(hDC, &paper, hbrush);

		SelectObject(hDC, hbrushOld);
		DeleteObject(hbrush);
	}

	RoundRect(hDC, 
		margin_left-1, margin_top-1, 
		paper.right - margin_right+1, paper.bottom - margin_bottom+1, 
		0, 0);

	//////////////////////////////////////////////////////////////////////////////
	long paper_width  = paper.right - paper.left - margin_left - margin_right;
	long paper_height = paper.bottom - paper.top - margin_top - margin_bottom;

	double ar=(double)paper_width/(double)paper_height;

	RECT gl_paper;
	gl_paper.left		= 0;
	gl_paper.top		= 0;

	gl_paper.right		= 1000*ar;
	gl_paper.bottom		= 1000;

	long gl_paper_width=gl_paper.right - gl_paper.left;
	long gl_paper_height=gl_paper.bottom - gl_paper.top;

	int width=((int)(gl_paper_width/4))*4;
	int height=gl_paper_height;

	//CGLPrintMan print;
	print.EnableOpenGL(gl_paper, hWnd, &print.m_hDC, &print.m_hRC);
	
	print.StartUpdate();
	UseGLFont( print.m_hDC,  &lf_Label);
	SendMessage(hWnd, WM_COMMAND, ID_FILE_INITOG2, 0);

	// fon only white to economize printer resource
	glDrawBuffer(GL_FRONT);					  
	glClearColor(1,1,1,0);
	// ###########################################################
	// draw
	win_graphics_view * woglv = 
		(win_graphics_view *)GetWindowLongPtr(hWnd,GWLP_USERDATA); 

	if (woglv) 
	{
		if (print.toReDraw)
		{
			project * prj = woglv->GetProject();
			SurfDoc* pSurfDoc = dynamic_cast<SurfDoc*>(prj); // from win_graphics_view::GetProject()
			//pSurfDoc->ZoomView();
			//====== ‘ормирование списка рисующих команд
			pSurfDoc->Draw();
		}

		// Set new size of viwport as picture's paper size
		woglv->SetSize(width,height);
		//woglv->SetSize(paper_width,paper_height);

		woglv->ExposeEvent();

		// Restore size of viwport as window size			
		woglv->ConfigureHandler(hWnd);
		// ###########################################################
	}

	{


		// transper to printer
		HDC hdc;
		HBITMAP bitmap;

		hdc	= CreateCompatibleDC(hDC);
		bitmap = CreateDIBitmap(hdc, &(print.m_BitmapInfo.bmiHeader),
						CBM_INIT,
						(GLubyte*)print.m_pBitmapBuffer,
						&print.m_BitmapInfo,
						DIB_RGB_COLORS);
		
		HGDIOBJ oldbitmap = SelectObject(hdc, bitmap);

		// ѕроверить режим StretchBlt и установить 		
		// его в случае необходимости.
		//................................................
		if (GetStretchBltMode(hDC) != STRETCH_DELETESCANS)
			SetStretchBltMode( hDC, STRETCH_DELETESCANS );

		BOOL bRet = StretchBlt(hDC,
			margin_left,
			margin_top, // offset 
			paper_width, 
			paper_height,// paper
			print.m_hDC,
			0, 0,
			print. m_BitmapInfo.bmiHeader.biWidth,
			print.m_BitmapInfo.bmiHeader.biHeight,
			SRCCOPY);

		if (oldbitmap != NULL)
			SelectObject(hdc, oldbitmap);

		// Free our bitmap and bitmap device context
		DeleteDC(hdc);
		DeleteObject(bitmap);
	}

	print.DisableOpenGL(hWnd, print.m_hDC, print.m_hRC);
	print.EndUpdate();

	////////////////////////////////////////////////////////////////////////////////
}

// ак получить текущие настройки принтера
//≈динственный способ, получить доступ к текущим настройкам принтеров, 
//это через структуры m_hDevMode и m_hDevNames хран€щимис€ в CWinApp. 
//Ёти члены доступны через структуру PRINTDLG, указатель которой передаЄтс€ 
//в функцию-член GetPrinterDeviceDefaults() класса, 
//наследованного от CWinApp. “ак как возвращаемые значени€ 
//hDevMode и hDevNames €вл€ютс€ переменными HGLOBAL, 
//то дл€ того, чтобы вернуть указатель на структуры необходимо вызывать 
//::GlobalLock(). »спользу€ данный указатель, можно извлечь информацию 
//из структуры, чтобы определить текущее состо€ние принтера. 
//Ѕолее подробно о содержимом этих структур можно посмотреть 
//DEVMODE и DEVNAMES в хелпе по SDK.
	
int BeginPrinting(HWND hWnd, PRINTDLG * pd)
{
	HDC hDC;
	DOCINFO di;
	
	if(!pd->hDevNames)
	{
		MessageBox(0,"!psd->hDevNames","BeginPrinting", 0);
		return -1;
	}

	if(!pd->hDevMode)
	{
		MessageBox(0,"!psd->hDevMode","BeginPrinting", 0);
		return -1;
	}

	// ѕолучаем указатели на две структуры с установками.
	DEVNAMES FAR *lpDevNames =
		(DEVNAMES FAR *)::GlobalLock(pd->hDevNames);
	
	DEVMODE FAR *lpDevMode =
		(DEVMODE FAR *)::GlobalLock(pd->hDevMode);

	
	LPSTR szPrinterName = (LPTSTR)lpDevNames +
		lpDevNames->wDeviceOffset;
	
	LPSTR szDriverName = (LPTSTR)lpDevNames +
		lpDevNames->wDriverOffset;

	LPSTR szOutputPortName = (LPTSTR)lpDevNames +
		lpDevNames->wOutputOffset;

	bAbortPrinting = FALSE;

	// —оздать контекст устройства дл€ принтера, 
	// на котором должна быть выполнена печать.
	//........................................

	{
		hDC = CreateDC( 
			szDriverName,//"WINSPOOL", 
			szPrinterName,
			szOutputPortName, 
			lpDevMode			//pDevModeUser 
			);

		if(hDC != NULL)
		{
			// ”становить структуру DOCINFO.
			//.............................
			memset( &di, 0, sizeof( DOCINFO ) );
			di.cbSize      = sizeof( DOCINFO );
			di.lpszDocName = "Surf cube";
			
			// —оздать диалоговое окно аварийного 
			// прекращени€ работы.
			//.........................
			hAbortPrintingDlg = CreateDialog( hInst,
				MAKEINTRESOURCE(IDD_DIALOG_ABORT_PRINTING),
				hWnd, (DLGPROC)DlgProcAbortPrinting );
			
			// «апретить главное окно приложени€.
			//.....................................
			
			EnableWindow( hWnd, FALSE );
			
			// ѕредусмотреть в процедуре аварийного 
			// прекращени€ работы обработку сообщений дл€ 	
			// диалогового окна аварийного прекращени€ работы.
			//..................................
			
			SetAbortProc( hDC, (ABORTPROC)AbortPrinting );
			// Send output to the printer...
			// Ќачать печать.
			//....................
			
			if ( StartDoc( hDC, &di ) != SP_ERROR )
			{
				// Ќапечатать страницу 1.
				//..............
				StartPage( hDC );
				OnPrint(hWnd, hDC, false, NULL, NULL); // ->remove to CallBack procedure !!!
				EndPage( hDC );
				
				// «акончить печать.
				//..............
				EndDoc( hDC );
			}
			// ≈сли пользователь прерывает задание на печать, 
			// прекратить печать документа; в ином случае 	
			// уничтожить диалоговое окно аварийного 
			// прекращени€ работы.
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
	
	::GlobalUnlock(pd->hDevNames);
	::GlobalUnlock(pd->hDevMode);
	return 0;
}

HDC BeginPrintPreview(PAGESETUPDLG * psd)
{

	HDC hPrintDC;

	if(!psd->hDevNames)
	{
		MessageBox(0,"!psd->hDevNames","BeginPrintPreview", 0);
		return NULL;
	}

	if(!psd->hDevMode)
	{
		MessageBox(0,"!psd->hDevMode","BeginPrintPreview", 0);
		return NULL;
	}

	// ѕолучаем указатели на две структуры с установками.
	DEVNAMES FAR *lpDevNames =
		(DEVNAMES FAR *)::GlobalLock(psd->hDevNames);
	
	DEVMODE FAR *lpDevMode =
		(DEVMODE FAR *)::GlobalLock(psd->hDevMode);

	
	LPSTR szPrinterName = (LPTSTR)lpDevNames +
		lpDevNames->wDeviceOffset;
	
	LPSTR szDriverName = (LPTSTR)lpDevNames +
		lpDevNames->wDriverOffset;

	LPSTR szOutputPortName = (LPTSTR)lpDevNames +
		lpDevNames->wOutputOffset;

	printf("szPrinterName = %s\n", szPrinterName );
	printf("szDriverName = %s\n", szDriverName );
	printf("szOutputPortName = %s\n", szOutputPortName );

	// —оздать контекст устройства дл€ принтера, 
	// на котором должна быть выполнена печать.
	//........................................

	hPrintDC = CreateDC( 
		szDriverName,//"WINSPOOL", 
		szPrinterName,
		szOutputPortName, 
		lpDevMode			//pDevModeUser 
		);

	if(hPrintDC != NULL)
	{	
		return hPrintDC;
	}
	else
		return NULL;

}
		
void EndPrintPreview(HDC hPrintDC, PAGESETUPDLG * psd)
{			
	DeleteDC( hPrintDC );
	
	::GlobalUnlock(psd->hDevNames);
	::GlobalUnlock(psd->hDevMode);
}
