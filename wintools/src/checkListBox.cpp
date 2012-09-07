#include "stdafx.h"
#include "checkListBox.h"

HBITMAP hbmpUnchecked, hbmpChecked; 
HBITMAP hbmpPicture, hbmpOld; 

WNDPROC wpOrigListBoxProc; 

 
 
// Subclass procedure 
LRESULT APIENTRY ListBoxSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
    if (uMsg == WM_LBUTTONDOWN ) 
	{
		unsigned short xPos = LOWORD(lParam); // horizontal position of pointer 
		unsigned short yPos = HIWORD(lParam); // vertical position of pointer 
		
		int nItem = (int)(SendMessage(hwnd, LB_GETTOPINDEX, 0, 0) + yPos / SendMessage(hwnd, LB_GETITEMHEIGHT, 0, 0));
		LONG itemdata = (long)SendMessage(hwnd, LB_GETITEMDATA, nItem, 0); 

		if (itemdata) 
			(itemdata = 0);
		else
			(itemdata = 1);

		SendMessage(hwnd, LB_SETITEMDATA, nItem, (LPARAM)itemdata);
		RECT rect;
		GetClientRect(hwnd,&rect);
		InvalidateRect(hwnd,&rect, true);
	} 
    return CallWindowProc(wpOrigListBoxProc, hwnd, uMsg, 
        wParam, lParam); 
} 

void AddCheckedItem(HWND hwndList, LPSTR lpstr, LPARAM check) 
{ 
    int nItem; 
 
    nItem = (int)SendMessage(hwndList, LB_ADDSTRING, 0,  (LPARAM)(LPCTSTR)lpstr); 
    SendMessage(hwndList, LB_SETITEMDATA, nItem, (LPARAM)check); 
} 
 