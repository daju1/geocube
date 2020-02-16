#include "../stdafx.h"
#include ".\listviewtab.h"
#include "commctrl.h"
#include "../../resource.h"
#include "../../tools/src/readfile.h"
#include "../../tools/src/errorexit.h"
#include "../../wintools/src/listfun.h"

#include "../../surfdoc/src/layer.h"

extern HINSTANCE hInst;								// current instance
extern int ChooseSurfColor(HWND hwndOwner, COLORREF& color);

RECT GetTextRect2(RECT * rcHeader)
{
	RECT rcText;
	rcText.top = rcHeader->top + (rcHeader->bottom-rcHeader->top)*0;
	rcText.bottom = rcHeader->bottom;
	rcText.left = rcHeader->left;
	rcText.right = rcHeader->right - (rcHeader->right - rcHeader->left)*(1.0-0.25);

	return rcText;
}

extern HBITMAP hbmpUnchecked, hbmpChecked; 
extern HBITMAP hbmpPicture, hbmpOld; 


WNDPROC wpOrigListViewTabWndProc;

// Новый отработчик сообщений ListView1 
LRESULT APIENTRY ListViewTabWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
	else
	if(uMsg==WM_DRAWITEM) 
	{ 
		//структура с параметрами для рисования 
		DRAWITEMSTRUCT *ds=(DRAWITEMSTRUCT *)lParam; 
		//Номер колонки 
		int column=ds->itemID; 
		//Сохраним контекст 
		int idsave=SaveDC(ds->hDC); 

		//Получим текст заголовка колонки 
		char text[42]={0}; 
		HDITEM hdm; 
		memset(&hdm,0,sizeof(hdm)); 
		hdm.mask=HDI_TEXT; 
		hdm.pszText=text; 
		hdm.cchTextMax=40; 
		Header_GetItem(ds->hwndItem,column,&hdm); 
		//Нарисуем текст 
		int i=strlen(text); 

		//RECT rcText = GetTextRect2(&ds->rcItem);

		if(i) 
		{
			::DrawText(ds->hDC,text,i,&ds->rcItem,DT_CENTER); 
		}
		//восстанавливаем контекст 
		RestoreDC(ds->hDC,idsave);
		return 1; 
	} 
	else
	if (uMsg == LVM_SCROLL)
	{
		printf("LVM_SCROLL\n");
	}
	else
	if (uMsg == WM_WINDOWPOSCHANGING)
	{
MessageBox(0, "WM_WINDOWPOSCHANGING 0", "List", 0);
		long lrez = CallWindowProc(wpOrigListViewTabWndProc, hwnd, uMsg, wParam, lParam);
MessageBox(0, "WM_WINDOWPOSCHANGING end", "List", 0);
		return lrez;
	}
	else
	if (uMsg == WM_WINDOWPOSCHANGED)
	{
MessageBox(0, "WM_WINDOWPOSCHANGED 0", "List", 0);
		long lrez = CallWindowProc(wpOrigListViewTabWndProc, hwnd, uMsg, wParam, lParam);
MessageBox(0, "WM_WINDOWPOSCHANGED end", "List", 0);
		return lrez;
	}

	//Вызываем старый отработчик 
    return CallWindowProc(wpOrigListViewTabWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 

WNDPROC wpOrigEdit_WndProc;

LRESULT APIENTRY EditWnd_SubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
    if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
	else
    if (uMsg == WM_KILLFOCUS ) 
	{
		LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		_ListViewTab_ * tab = reinterpret_cast<_ListViewTab_ *>(ptr);
		if (tab)
		{
			SendMessage(tab->GetWndParent(), WM_USER+3,0,0);
		}
	} 
	else
    if (uMsg == WM_CHAR ) 
	{
		if (wParam == 13 )
		{
			LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
			_ListViewTab_ * tab = reinterpret_cast<_ListViewTab_ *>(ptr);
			if (tab)
			{
				SendMessage(tab->GetWndParent(), WM_USER+3,0,0);
			}
		}
	} 		
    return CallWindowProc(wpOrigEdit_WndProc, hwnd, uMsg, 
        wParam, lParam); 
} 

#define USE_LISTVIEW_STANDART 1
#define _ListViewTab_ ListViewTab 
#include "ListViewTab_cpp.h"

#define USE_LISTVIEW_STANDART 0
#define _ListViewTab_ ListViewTab2 
#include "ListViewTab_cpp.h"