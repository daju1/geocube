//Displaying the Print Dialog Box
//This topic describes sample code that displays a Print dialog box so a user can select options for printing a document. The sample code first initializes a PRINTDLG structure, and then calls the PrintDlg function to display the dialog box. 

//This example sets the PD_RETURNDC flag in the Flags member of the PRINTDLG structure. This causes PrintDlg to return a device context handle for the selected printer in the hDC member. You can use the handle to render output on the printer. 

//On input, the sample code sets the hDevMode and hDevNames members to NULL. If the function returns TRUE, these members return handles to and DEVNAMES structures containing the user's input and information about the printer. You can use this information to prepare the output to be sent to the selected printer. 
#include "stdafx.h"
#include "PrintDlgBox.h"
#include "GLPrintMan.h"
#include "print.h"
#include "Commdlg.h"
 
extern HINSTANCE hInst;
extern CGLPrintMan print;

#define USE_HOOK 0

#if USE_HOOK
unsigned int CALLBACK PrintHookProc(HWND hdlg,
    UINT uiMsg,
    WPARAM wParam,
    LPARAM lParam
)
{
    if (uiMsg == WM_INITDIALOG) 
    { 
        // Манипулируя прерываниями системной ловушки управляем некоторыми элементами окна 
        // для примера отключим кнопку "Свойства". 
        HWND HPropButton = GetDlgItem(hdlg, psh2); 
        EnableWindow(HPropButton, false); 
    } 
    return 0L; 
}
#endif
HGLOBAL store_hDevMode = NULL;
HGLOBAL store_hDevNames = NULL;

RECT	store_rtMargin;
// сотые доли миллиметра

void Print(HWND hwnd)
{
	PRINTDLG pd;
	
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = hwnd;
	pd.hDevMode    = store_hDevMode;     // Don't forget to free or store hDevMode
	pd.hDevNames   = store_hDevNames;     // Don't forget to free or store hDevNames

	
	// GDI calls to render output.
	// что нибудб печатаем... 
	BeginPrinting(hwnd, &pd);

//	store_hDevMode = pd.hDevMode;
//	store_hDevNames = pd.hDevNames;
}

void PrintDefault(HWND hwnd)
{
	PRINTDLG pd;
	
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = hwnd;
	pd.hDevMode    = store_hDevMode;     // Don't forget to free or store hDevMode
	pd.hDevNames   = store_hDevNames;     // Don't forget to free or store hDevNames
	pd.Flags       = 
		  PD_RETURNDEFAULT
		; 

	
	if (PrintDlg(&pd)==TRUE) 
	{
		// GDI calls to render output.
		// что нибудб печатаем... 
		BeginPrinting(hwnd, &pd);

		store_hDevMode = pd.hDevMode;
		store_hDevNames = pd.hDevNames;
	}	
}
void DisplayPrintSurfDialogBox(HWND hwnd)
{
	PRINTDLG pd;
	
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = hwnd;
	pd.hDevMode    = store_hDevMode;     // Don't forget to free or store hDevMode
	pd.hDevNames   = store_hDevNames;     // Don't forget to free or store hDevNames
	pd.Flags       = 
		  PD_RETURNDC 
		| PD_HIDEPRINTTOFILE  
		| PD_NOPAGENUMS
		| PD_NOSELECTION
#if USE_HOOK
		| PD_ENABLEPRINTHOOK
#endif
		; 
	pd.nCopies     = 1;
	pd.nFromPage   = 0xFFFF; 
	pd.nToPage     = 0xFFFF; 
	pd.nMinPage    = 1; 
	pd.nMaxPage    = 0xFFFF; 

	//Для того чтобы перерисовать стандартный диалог
	//pd.lpPrintTemplateName = "";
	//pd.hInstance = hInst;

#if USE_HOOK
	pd.lpfnPrintHook = /*(LPSETUPHOOKPROC)*/PrintHookProc;
#endif
	
	if (PrintDlg(&pd)==TRUE) 
	{
		// GDI calls to render output.
		// что нибудб печатаем... 
		BeginPrinting(hwnd, &pd);

		store_hDevMode = pd.hDevMode;
		store_hDevNames = pd.hDevNames;

	}

	DWORD dwError = CommDlgExtendedError();

	if (dwError)
	{
		LPVOID lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwError,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);


		switch(dwError)
		{
		case CDERR_FINDRESFAILURE :
		case CDERR_INITIALIZATION :
		case CDERR_LOADRESFAILURE :
		case CDERR_LOADSTRFAILURE :
		case CDERR_LOCKRESFAILURE :
		case CDERR_MEMALLOCFAILURE :
		case CDERR_MEMLOCKFAILURE :
		case CDERR_NOHINSTANCE :
		case CDERR_NOHOOK :
		case CDERR_NOTEMPLATE :
		case CDERR_STRUCTSIZE :
		case PDERR_CREATEICFAILURE :
		case PDERR_DEFAULTDIFFERENT :
		case PDERR_DNDMMISMATCH :
		case PDERR_GETDEVMODEFAIL: 
		case PDERR_INITFAILURE :
		case PDERR_LOADDRVFAILURE :
		case PDERR_NODEFAULTPRN :
		case PDERR_NODEVICES :
		case PDERR_PARSEFAILURE :
		case PDERR_PRINTERNOTFOUND :
		case PDERR_RETDEFFAILURE :
			break;
		}

		char str[100];
		sprintf(str, "DisplayPrintDialogBox dwError = %x",dwError);
		::MessageBox(NULL, (LPCTSTR)lpMsgBuf, str, MB_OK);
	}

    // Delete DC when done.
    DeleteDC(pd.hDC);
}

//Using the Print Property Sheet
//This topic describes sample code that displays a Print property sheet so a user can select options for printing a document. The sample code first allocates and initializes a PRINTDLGEX structure, then calls the PrintDlgEx function to display the property sheet. 

//The sample code sets the PD_RETURNDC flag in the Flags member of the PRINTDLG structure. This causes the PrintDlgEx function to return a device context handle for the selected printer in the hDC member. You can use the handle in functions such as that render output sent to the printer. 

//On input, the sample code sets the hDevMode and hDevNames members to NULL. If the function returns S_OK, these members return handles to and DEVNAMES structures containing the user's input and information about the printer. You can use this information to prepare the output to be sent to the selected printer. 

//After the printing operation has been completed, the sample code frees the DEVMODE and DEVNAMES buffers and calls the function to delete the device context.
#if 0

HRESULT DisplayPrintPropertySheet(
    HWND hWnd  // Window that owns the property sheet
)
{
HRESULT hResult;
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

return hResult;
}

#endif

//Setting Up the Printed Page
//This topic describes sample code that displays 
//a Page Setup dialog box so a user can select 
//the attributes of the printed page, such as the paper type, 
//paper source, page orientation, and page margins. 
//The sample code first initializes a PAGESETUPDLG structure, 
//and then calls the PageSetupDlg function to display the dialog box. 

//This example sets the PSD_MARGINS flag in the Flags member 
//and uses the rtMargin member to specify the initial margin values. 
//It sets the PSD_INTHOUSANDTHSOFINCHES flag to ensure 
//that the dialog box expresses margin dimensions in thousandths of an inch. 

//On input, the sample code sets the hDevMode and hDevNames members to NULL. If the function returns TRUE, the function uses these members to return handles to and DEVNAMES structures containing the user's input and information about the printer. You can use this information to prepare the output to be sent to the selected printer. 

//The example also enables a PagePaintHook hook procedure to customize drawing of the contents of the sample page. 

void SurfPrintedPageSetup(HWND hwnd)   // owner window

{
	PAGESETUPDLG psd;    // common dialog box structure

	// Initialize PAGESETUPDLG
	ZeroMemory(&psd, sizeof(psd));
	psd.lStructSize = sizeof(psd);
	psd.hwndOwner   = hwnd;
	psd.hDevMode    = store_hDevMode; // Don't forget to free or store hDevMode
	psd.hDevNames   = store_hDevNames; // Don't forget to free or store hDevNames
	psd.Flags       = 
		PSD_MARGINS |
		PSD_INHUNDREDTHSOFMILLIMETERS | 
		PSD_ENABLEPAGEPAINTHOOK; 

	psd.rtMargin.top = store_rtMargin.top;
	psd.rtMargin.left = store_rtMargin.left;
	psd.rtMargin.right = store_rtMargin.right;
	psd.rtMargin.bottom = store_rtMargin.bottom;
	
	psd.lpfnPagePaintHook = PaintHook;

	if (PageSetupDlg(&psd)==TRUE) {
		// check paper size and margin values here
		store_hDevMode = psd.hDevMode;
		store_hDevNames = psd.hDevNames;

		// сотые доли миллиметра
		store_rtMargin.top = psd.rtMargin.top;
		store_rtMargin.left = psd.rtMargin.left;
		store_rtMargin.right = psd.rtMargin.right;
		store_rtMargin.bottom = psd.rtMargin.bottom;
	}
}

//The following example shows a sample PagePaintHook 
//hook procedure that draws the margin rectangle in the sample page area:

unsigned int CALLBACK PaintHook(HWND hwndDlg, UINT uMsg, WPARAM wParam,
    LPARAM lParam) 
{ 
    LPRECT lprc; 
    COLORREF crMargRect; 
    HDC hdc, hdcOld; 
 
    switch (uMsg) { 
 
        // Drawing the margin rectangle. 
        case WM_PSD_MARGINRECT: 
            hdc = (HDC) wParam; 
            lprc = (LPRECT) lParam; 
 
            // Get the system highlight color. 
            crMargRect = GetSysColor(COLOR_HIGHLIGHT); 
 
            // Create a dash-dot pen of the system highlight color and 
            // select it into the DC of the sample page. 
            hdcOld = (HDC)SelectObject(hdc, CreatePen(PS_DASHDOT, .5, 
                crMargRect)); 
 
            // Draw the margin rectangle. 
            Rectangle(hdc, lprc->left, lprc->top, lprc->right, 
                lprc->bottom); 
 
            // Restore the previous pen to the DC. 
            SelectObject(hdc, hdcOld); 
            return TRUE; 
 
        default: 
            return FALSE; 
    } 
    return TRUE; 
}

	
PAGESETUPDLG print_preview_psd;    // common dialog box structure

LRESULT CALLBACK WndProcSurfPrintPreview(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	static	HGLRC		m_hRC;				// Контекст OpenGL
	static	HDC			m_hdc; 			// Контекст Windows

	static	void* m_pBitmapBuffer; // buffer to store bitmap (RGB, RGB , RGB etc..)
	static	BITMAPINFO m_BitmapInfo;
	static	HDC hPrintDC;
	static	HBITMAP m_hDib; // bitmap handle
	static	HDC hMemDC;
	static	RECT paper;
	static	RECT wnd_paper;

	static	HWND hWndSurf;

	switch (message) 
	{
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_UPDATE:
				{
					RECT rcClient;
					GetClientRect(hWnd, &rcClient);
					InvalidateRect(hWnd, &rcClient, TRUE);
				}
				break;
			case ID_PRINT:
				{
					Print(hWndSurf);
				}
				break;
			case ID_CLOSE:
				{
					DestroyWindow(hWnd);
				}
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_CREATE  :
		{
			//##################################################
			print.toEnableOpenGL	= true;
			print.toReDraw			= true;
			print.toDisableOpenGL	= false;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLongPtr(hWnd,	GWLP_USERDATA,(LONG_PTR)pcs->lpCreateParams);

			hWndSurf = *((HWND *)pcs->lpCreateParams);
			//##################################################
			hPrintDC = BeginPrintPreview(&print_preview_psd);
			//##################################################
			paper.top		= 0;
			paper.left		= 0;
			paper.bottom	= 0;
			paper.right		= 0;

			// Get the size of the default printer page
			paper.right  = GetDeviceCaps(hPrintDC, HORZRES);
			paper.bottom = GetDeviceCaps(hPrintDC, VERTRES);

printf ("WM_CREATE paper.right  = %d\n", paper.right );
printf ("WM_CREATE paper.bottom  = %d\n", paper.bottom );

			//////////////////////////////////////////////////////////////////////////////
			long paper_width  = paper.right - paper.left;
			long paper_height = paper.bottom - paper.top;

printf ("WM_CREATE paper_width  = %d\n", paper_width );
printf ("WM_CREATE paper_height  = %d\n", paper_height );

			double ar=(double)paper_width/(double)paper_height;

printf ("WM_CREATE ar  = %f\n", ar );

			wnd_paper.left		= 0;
			wnd_paper.top		= 0;

			wnd_paper.right		= 1200*ar;
			wnd_paper.bottom	= 1200;

			long wnd_paper_width=wnd_paper.right - wnd_paper.left;
			long wnd_paper_height=wnd_paper.bottom - wnd_paper.top;

printf ("WM_CREATE wnd_paper_width  = %d\n", wnd_paper_width );
printf ("WM_CREATE wnd_paper_height  = %d\n", wnd_paper_height );

			int width=((int)(wnd_paper_width/4))*4;
			int height=wnd_paper_height;

printf ("WM_CREATE width  = %d\n", width );
printf ("WM_CREATE height  = %d\n", height );

			wnd_paper.right		= width;
			wnd_paper.bottom	= height;


			// prepare bitmap
			m_pBitmapBuffer=NULL; // buffer to store bitmap (RGB, RGB , RGB etc..)

			// First of all, initialize the bitmap header information...
			memset(&m_BitmapInfo, 0, sizeof(BITMAPINFO));
			m_BitmapInfo.bmiHeader.biSize		= sizeof(BITMAPINFOHEADER);

#if SLOW_PREVIEW
			m_BitmapInfo.bmiHeader.biWidth		= paper.right - paper.left;
			m_BitmapInfo.bmiHeader.biHeight		= paper.bottom - paper.top;
#else
			m_BitmapInfo.bmiHeader.biWidth		= width;
			m_BitmapInfo.bmiHeader.biHeight		= height;
#endif
			m_BitmapInfo.bmiHeader.biPlanes		= 1;
			m_BitmapInfo.bmiHeader.biBitCount		= 32;
			m_BitmapInfo.bmiHeader.biCompression	= BI_RGB;

			m_BitmapInfo.bmiHeader.biSizeImage	=
				m_BitmapInfo.bmiHeader.biWidth * 
				m_BitmapInfo.bmiHeader.biHeight * 
				m_BitmapInfo.bmiHeader.biBitCount / 8;

			// create Device Independent Bitmap (containing full RGB information regardless of graphic system)
			HDC hTmpDC;
			hTmpDC=::GetDC(hWndSurf);
			m_hDib= CreateDIBSection(hTmpDC, &m_BitmapInfo, DIB_RGB_COLORS, &m_pBitmapBuffer, NULL, (DWORD) 0);
			// now, we got bitmap to draw , buffer is pBitmapBuffer

			// create memory device context
			hMemDC=CreateCompatibleDC(hTmpDC);
			if (hMemDC==NULL) throw "CreateCompatibleDC: Error";
			
			// connect memeory device context with bitmap
			if (SelectObject(hMemDC, m_hDib)==NULL) throw "SelectObject: Error" ;

			::ReleaseDC(hWndSurf, hTmpDC);
			
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here..
			// create memory device context

			RECT rcClient;
			GetClientRect(hWnd, &rcClient);

			float scaleX = 
				(float)(rcClient.right - rcClient.left-50)
				/
				(float)(paper.right - paper.left);

			float scaleY = 
				(float)(rcClient.bottom - rcClient.top-50)
				/
				(float)(paper.bottom - paper.top);

			float scale = min(scaleX, scaleY);

			LONG width = scale * (paper.right - paper.left);
			LONG height = scale * (paper.bottom - paper.top);
/*
printf ("WM_PAINT width  = %d\n", width );
printf ("WM_PAINT height  = %d\n", height );
*/
			LONG left = (rcClient.right - rcClient.left - width) / 2;
			LONG top  = (rcClient.bottom - rcClient.top - height) / 2;
/*
printf ("WM_PAINT left  = %d\n", left );
printf ("WM_PAINT top  = %d\n", top );
*/
			// draw the page
			{			
				HBRUSH hbrushGray;                  
				HBRUSH hbrushWhite;                  
				hbrushGray = CreateSolidBrush(RGB(150,150,150));
				hbrushWhite = CreateSolidBrush(RGB(255,255,255));
				HBRUSH hbrushOld = (HBRUSH__ *)SelectObject(ps.hdc, hbrushGray);

				HPEN pen = (HPEN__ *)CreatePen(PS_SOLID, 0, COLORREF(0));
				HPEN penOld = (HPEN__ *)SelectObject(ps.hdc, pen);

				LONG shiftv = 4;
				LONG shiftg = 5;

				RECT r;
				r.left			= left - 1 + shiftg;
				r.right			= left + width + 2 + shiftg;

				r.top			= top - 1 - shiftv;
				r.bottom		= top + height + 2 - shiftv;

				FillRect(ps.hdc, &r, hbrushGray);

				RoundRect(ps.hdc, 
					left-1, top-1, 
					left + width+2, top + height+2, 
					0, 0);

				r.left			= left;
				r.right			= left + width;

				r.top			= top;
				r.bottom		= top + height;

				SelectObject(ps.hdc, hbrushWhite);

				FillRect(ps.hdc, &r, hbrushWhite);


				SelectObject(ps.hdc, hbrushOld);
				SelectObject(ps.hdc, penOld);

				DeleteObject(hbrushGray);
				DeleteObject(hbrushWhite);

				DeleteObject(pen);
			}


			OnPrint(hWndSurf, hMemDC, true, hPrintDC, &wnd_paper); // ->remove to CallBack procedure !!!
			//##################################################
			print.toEnableOpenGL	= false;
			print.toReDraw			= false;
			print.toDisableOpenGL	= false;
			//##################################################
/*
printf ("WM_PAINT left  = %d\n", left );
printf ("WM_PAINT top  = %d\n", top );

printf ("WM_PAINT width  = %d\n", width );
printf ("WM_PAINT height  = %d\n", height );

printf ("WM_PAINT m_BitmapInfo.bmiHeader.biWidth  = %d\n", m_BitmapInfo.bmiHeader.biWidth );
printf ("WM_PAINT m_BitmapInfo.bmiHeader.biHeight  = %d\n", m_BitmapInfo.bmiHeader.biHeight );
*/
			StretchBlt( 
				ps.hdc, 
				left, top, 
				width, height,
				hMemDC, 
				0, 0, 
				m_BitmapInfo.bmiHeader.biWidth,
				m_BitmapInfo.bmiHeader.biHeight,
				SRCCOPY );

			EndPaint(hWnd, &ps);
		}
		break;
		
	case WM_DESTROY:
		{
			//##################################################
			print.toEnableOpenGL	= false;
			print.toReDraw			= false;
			print.toDisableOpenGL	= true;
			//##################################################
			OnPrint(hWndSurf, hMemDC, true, hPrintDC, &wnd_paper); // ->remove to CallBack procedure !!!
			//##################################################
			print.toEnableOpenGL	= true;
			print.toReDraw			= true;
			print.toDisableOpenGL	= true;
			//##################################################
			DeleteDC( hMemDC );
			//if (m_pBitmapBuffer) delete m_pBitmapBuffer;
			if (m_pBitmapBuffer) HeapFree(GetProcessHeap(), 0, m_pBitmapBuffer);

			DeleteObject(m_hDib); // delete DIB
			EndPrintPreview(hPrintDC, &print_preview_psd);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
#include "../resource.h"
extern LPCTSTR lpszWinSurfName;

void PrintPreview(HWND hwnd)
{
	printf("PrintPreview(HWND hwnd) = %x\n", hwnd);
	WNDCLASSEX wc;
	// Регистрация класса главного окна приложения.
	//............................................
	//........................................................................
	wc.style         	= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   	= (WNDPROC)WndProcSurfPrintPreview;
	wc.cbClsExtra    	= 0;
	wc.cbWndExtra    	= 0;
	wc.hInstance     	= hInst;
	wc.hIcon         	= LoadIcon (hInst, lpszWinSurfName);
	wc.hCursor       	= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground 	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName		= MAKEINTRESOURCE( IDR_MENU_SURF_PRINT_PREVIEW);
	wc.lpszClassName	= "Surf Cube Print Preview";
	wc.cbSize        	= sizeof(WNDCLASSEX);
	wc.hIconSm       	= (HICON__ *)LoadImage(hInst, lpszWinSurfName, IMAGE_ICON, 16, 	
						16, LR_DEFAULTCOLOR );

	//**************************************

	if ( !RegisterClassEx( &wc ) )
	{
		DWORD dwError = GetLastError();
		if(1410 != dwError)// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","PrintPreview",0);
			LPVOID lpMsgBuf;

			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				dwError,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
			);
			char str[100];
			sprintf(str, "RegisterClassEx dwError = %x",dwError);
			::MessageBox(NULL, (LPCTSTR)lpMsgBuf, str, MB_OK);
		}
		else
		{
			// MessageBox(0,"класс уже существует","WinSurf",0);
		}
	}
	bool toPreview = false;

	// Initialize PAGESETUPDLG
	ZeroMemory(&print_preview_psd, sizeof(print_preview_psd));
	print_preview_psd.lStructSize = sizeof(print_preview_psd);
	print_preview_psd.hwndOwner   = hwnd;
	print_preview_psd.hDevMode    = store_hDevMode; // Don't forget to free or store hDevMode
	print_preview_psd.hDevNames   = store_hDevNames; // Don't forget to free or store hDevNames

	print_preview_psd.Flags       = 
		PSD_RETURNDEFAULT; 

	print_preview_psd.rtMargin.top = store_rtMargin.top;
	print_preview_psd.rtMargin.left = store_rtMargin.left;
	print_preview_psd.rtMargin.right = store_rtMargin.right;
	print_preview_psd.rtMargin.bottom = store_rtMargin.bottom;


	if (PageSetupDlg(&print_preview_psd)==TRUE) 
	{	
		// GDI calls to render output.
		// что нибудб печатаем... 
		// check paper size and margin values here
		store_hDevMode = print_preview_psd.hDevMode;
		store_hDevNames = print_preview_psd.hDevNames;

		// сотые доли миллиметра
		store_rtMargin.top = print_preview_psd.rtMargin.top;
		store_rtMargin.left = print_preview_psd.rtMargin.left;
		store_rtMargin.right = print_preview_psd.rtMargin.right;
		store_rtMargin.bottom = print_preview_psd.rtMargin.bottom;

		toPreview = true;
	}

	RECT r;
	GetWindowRect(hwnd, &r);

	LONG W = r.right - r.left;
	LONG H = r.bottom - r.top;
	LONG w = W/4;
	LONG h = H/2;



	HWND hPreviewWnd = CreateWindow( "Surf Cube Print Preview",
		"Print Preview",
		WS_OVERLAPPEDWINDOW,
		r.left+W-w, r.top+H-h,
		w, h,
		hwnd,		
		NULL,
		hInst,
		(void *) &hwnd
		//(void *) GetWindowLongPtr(hwnd,GWLP_USERDATA)
		);

	if( ! hPreviewWnd)
	{
		MessageBox(0,"! hPreviewWnd","",0);
	}

	ShowWindow(hPreviewWnd, 1);
}