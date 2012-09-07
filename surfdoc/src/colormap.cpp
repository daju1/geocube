#include "stdafx.h"
#include "colormap.h"

#define XBITMAP2 16 
#define YBITMAP2 16 
 
#define BUFFER MAX_PATH 
 
LPCSTR colormaps[] = {
		"IDR_COLORMAP_SURFER",	
		"IDR_TOPOMAP_DATA1", 
		"IDR_TOPOMAP_DATA2",
		"IDR_CLRMAP",	
		"IDR_COLORMAP_HSV",	
		"IDR_COLORMAP_HOT",	
		"IDR_COLORMAP_GRAY",	
		"IDR_COLORMAP_BONE",	
		"IDR_COLORMAP_COPPER",	
		"IDR_COLORMAP_PINK",		
		"IDR_COLORMAP_WHITE",	
		"IDR_COLORMAP_FLAG",	
		"IDR_COLORMAP_LINES",		
		"IDR_COLORMAP_COLORCUBE",	
		"IDR_COLORMAP_VGA",		
		"IDR_COLORMAP_JET",		
		"IDR_COLORMAP_PRISM",		
		"IDR_COLORMAP_COOL",		
		"IDR_COLORMAP_AUTUMN",		
		"IDR_COLORMAP_SPRING",		
		"IDR_COLORMAP_WINTER",		
		"IDR_COLORMAP_SUMMER"		
};

LPCSTR colormap_strings[] = {
		"SURFER", 
		"TOPOMAP1", 
		"TOPOMAP2",
		"CLRMAP",	
		"HSV",	
		"HOT",	
		"GRAY",	
		"BONE",	
		"COPPER",	
		"PINK",		
		"WHITE",	
		"FLAG",	
		"LINES",		
		"COLORCUBE",	
		"VGA",		
		"JET",		
		"PRISM",		
		"COOL",		
		"AUTUMN",		
		"SPRING",		
		"WINTER",		
		"SUMMER"		
};

WNDPROC wpOrigListBoxProc2; 

 
// Subclass procedure 
LRESULT APIENTRY ListBoxPaletteSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
	static COLORREF acrCustClr[16]; // array of custom colors 
	static DWORD rgbCurrent;        // initial color selection
    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
    if (uMsg == WM_LBUTTONDOWN ) 
	{
/*		unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
		unsigned short yPos = HIWORD(lParam); // vertical position of pointer 
		
		int nItem = SendMessage(hwnd, LB_GETTOPINDEX, 0, 0) + yPos / SendMessage(hwnd, LB_GETITEMHEIGHT, 0, 0);
		LONG itemdata = SendMessage(hwnd, LB_GETITEMDATA, nItem, 0); 


		SendMessage(hwnd, LB_SETITEMDATA, nItem, (LPARAM)itemdata);
		RECT rect;
		GetClientRect(hwnd,&rect);
		InvalidateRect(hwnd,&rect, true);*/
	} 
    if (uMsg == WM_LBUTTONDBLCLK ) 
	{
		unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
		unsigned short yPos = HIWORD(lParam); // vertical position of pointer 
		
		int nItem = (int)(SendMessage(hwnd, LB_GETTOPINDEX, 0, 0) + yPos / SendMessage(hwnd, LB_GETITEMHEIGHT, 0, 0));
		LONG itemdata = (long)SendMessage(hwnd, LB_GETITEMDATA, nItem, 0); 

		CHOOSECOLOR cc;                 // common dialog box structure 
		//HWND hwnd;                      // owner window
		HBRUSH hbrush;                  // brush handle

		rgbCurrent = (COLORREF) itemdata;

		// Initialize CHOOSECOLOR 
		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD) acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;
 
		if (ChooseColor(&cc)==TRUE) {
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
			itemdata = (LONG) rgbCurrent;
		}


		SendMessage(hwnd, LB_SETITEMDATA, nItem, (LPARAM)itemdata);
		RECT rect;
		GetClientRect(hwnd,&rect);
		InvalidateRect(hwnd,&rect, true);
	} 
    return CallWindowProc(wpOrigListBoxProc2, hwnd, uMsg, 
        wParam, lParam); 
} 

void AddCheckedPaletteItem(HWND hwndList, LPSTR lpstr, LPARAM check) 
{ 
    int nItem; 
 
    nItem = (int)SendMessage(hwndList, LB_ADDSTRING, 0,  (LPARAM)(LPCTSTR)lpstr); 
    SendMessage(hwndList, LB_SETITEMDATA, nItem, (LPARAM)check); 
} 
