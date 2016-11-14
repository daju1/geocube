#include "stdafx.h"
#include "listfun.h"
#include "..\resource.h"
#include "commctrl.h"
#include "..\..\tools\src\filedlg.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
#if 0
//#if (_WIN32_WINNT >= 0x501)
typedef struct tagNMLVSCROLL
{
    NMHDR   hdr;
    int     dx;
    int     dy;
} NMLVSCROLL, *LPNMLVSCROLL;

#define LVN_BEGINSCROLL          (LVN_FIRST-80)          
#define LVN_ENDSCROLL            (LVN_FIRST-81)
//#endif
#endif
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////

extern int ChooseSurfColor(HWND hwndOwner, COLORREF& color);

extern HINSTANCE hInst;								// current instance

#define BUFFER MAX_PATH 

WNDPROC wpOrigListWndProc; 

extern HBITMAP hbmpUnchecked, hbmpChecked; 
extern HBITMAP hbmpPicture, hbmpOld; 

extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false) ;

#define TEXT_PART 0.25
RECT GetComboBoxRect(RECT * rcHeader)
{
	RECT rcCombo;
	
	rcCombo.left = rcHeader->left+(rcHeader->right - rcHeader->left)*TEXT_PART;
	rcCombo.top = rcHeader->top 
		//+ 3*(rcHD.bottom - rcHD.top)/2
				; 
	rcCombo.right = (rcHeader->right - rcHeader->left - 2)*(1.0-TEXT_PART); 
	rcCombo.bottom = 15*(rcHeader->bottom - rcHeader->top);

	return rcCombo;

}
RECT GetTextRect(RECT * rcHeader)
{
	RECT rcText;
	rcText.top = rcHeader->top + (rcHeader->bottom-rcHeader->top)*0;
	rcText.bottom = rcHeader->bottom;
	rcText.left = rcHeader->left;
	rcText.right = rcHeader->right - (rcHeader->right - rcHeader->left)*(1.0-TEXT_PART);

	return rcText;
}

 
WNDPROC wpOrigEditWndProc;

LRESULT APIENTRY EditWndSubclassProc(
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
		SendMessage(GetParent(hwnd), WM_USER+1,0,0);
	} 
	else
    if (uMsg == WM_CHAR ) 
	{
		if (wParam == 13 )
		{
			SendMessage(GetParent(hwnd), WM_USER+1,0,0);
		}
	} 
		
    return CallWindowProc(wpOrigEditWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 
 
WNDPROC wpOrigComboBoxWndProc;

LRESULT APIENTRY ComboBoxWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) 
{ 
		
	//printf("ComboBoxWndSubclassProc\n");
    
	if (uMsg == WM_GETDLGCODE) 
	{
        return DLGC_WANTALLKEYS ;  // 0x0004      /* Control wants all keys - All keyboard input         */
	} 
	else
    if (uMsg == WM_SIZING ) 
	{
		printf("WM_SIZING\n");
		int column = GetWindowLongPtr(hwnd, GWLP_USERDATA);
	}
	else
    if (uMsg == WM_CHAR ) 
	{
		if (wParam == 13 )
		{
			SendMessage(GetParent(hwnd), WM_USER+2,0,0);
		}
	} 
	/*else
	if (uMsg == WM_NOTIFY)
	{
		printf("ComboBoxWndSubclassProc uMsg == WM_NOTIFY\n");
		switch (((LPNMHDR) lParam)->code)
		{
		case CBN_SELCHANGE:
			{
				printf("CBN_SELCHANGE\n");
			}
			break;
		}
	}*/

	
		
    return CallWindowProc(wpOrigComboBoxWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 

WNDPROC wpOrigHeaderWndProc;

LRESULT APIENTRY HeaderWndSubclassProc(
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
    if (uMsg == WM_SIZING ) 
	{

	}
	else
    if (uMsg == WM_CHAR ) 
	{
		if (wParam == 13 )
		{
			SendMessage(GetParent(hwnd), WM_USER+2,0,0);
		}
	} 
	else
	if (uMsg == WM_COMMAND)
	{
		switch (HIWORD(wParam))
		{
		case CBN_SELCHANGE:
			{
				//icol = LOWORD(wParam)
				SendMessage(GetParent(GetParent(hwnd)), WM_USER+3, LOWORD(wParam), 0);
			}
			break;
		}
	}
		
    return CallWindowProc(wpOrigHeaderWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 



WNDPROC wpOrigListViewWndProc;

// Новый отработчик сообщений ListView1 
LRESULT APIENTRY ListViewWndSubclassProc(
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

		RECT rcText = GetTextRect(&ds->rcItem);

		if(i) 
		{
			::DrawText(ds->hDC,text,i,&rcText,DT_CENTER); 
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

	//Вызываем старый отработчик 
    return CallWindowProc(wpOrigListViewWndProc, hwnd, uMsg, 
        wParam, lParam); 
} 


#define IDCOMBO 11111
#define IDLIST 11112
#define HEADER_IN_FIRST_ROW	1
BOOL CALLBACK DlgProcDrillsList(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    int y; 
    TEXTMETRIC tm; 
    HDC hdcMem; 
	static HWND hList;
	static HWND hWndEdit;
	static HWND hWndComboBox;
	static HWND hwndHD;

	static vector<string>			* headers;
	static vector<vector<string> >	* items;
	static vector<vector<int> >		* checkings;
	static vector<vector<int> >		* editings;
	static int rows, cols;
	static int edit_r, edit_c;

    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 

	static LPDRILLSDLGDATA lpDrillsDlgMem;


    switch (message) 
    { 
	case WM_INITDIALOG:
		{
			int r, c;


			lpDrillsDlgMem = (LPDRILLSDLGDATA) lParam;

			rows = lpDrillsDlgMem->pdrills->size();
			cols = lpDrillsDlgMem->pnames_of_colomns->size();


#if HEADER_IN_FIRST_ROW
			rows++;
#endif
			edit_r = -1;
			edit_c = -1;

			hList = CreateListView (hDlg, 10, 10, 0.97, 0.87);

			SetFocus(hList);

			ShowWindow(hList, 1);
			InitListViewImageLists(hList);

			//--------------------------------------------------------------
			// Subclass the control. 
			wpOrigListViewWndProc = (WNDPROC) SetWindowLongPtr(hList, 
				GWLP_WNDPROC, (LONG_PTR) ListViewWndSubclassProc); 

			//SetWindowLongPtr(hList, GWLP_USERDATA,(LONG_PTR)lParam);
			//--------------------------------------------------------------
			hwndHD = ListView_GetHeader(hList); 
			//--------------------------------------------------------------
			// Subclass the control. 
			wpOrigHeaderWndProc = (WNDPROC) SetWindowLongPtr(hwndHD, 
				GWLP_WNDPROC, (LONG_PTR) HeaderWndSubclassProc); 
			//SetWindowLongPtr(hwndHD, GWLP_USERDATA,(LONG_PTR)cols);
			//SetWindowLong(hwndHD, GWLP_USERDATA,(LONG)hList);

			//--------------------------------------------------------------
            // Load bitmaps. 
            hbmpChecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_CHECKED)); 
            hbmpUnchecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UNCHECKED)); 

			//--------------------------------------------------------------
			//--------------------------------------------------------------

			headers = new vector<string>;
			for (c = 0; c < cols; c++)
			{
				headers->push_back(string());
				headers->back().resize(32);
				sprintf((char *)headers->back().data(), "%s", (*lpDrillsDlgMem->pnames_of_colomns)[c].c_str());				
			}

			items		= new vector<vector<string> >;
			checkings	= new vector<vector<int> >;
			editings	= new vector<vector<int> >;

			items->		resize(rows);
			checkings->	resize(rows);
			editings->	resize(rows);

			for (r = 0; r < rows; r++)
			{
				items->operator		[] (r).resize(cols);
				checkings->operator [] (r).resize(cols);
				editings->operator	[] (r).resize(cols);

				for (c = 0; c < cols; c++)
				{
					(*items)[r][c] .resize(256);
#if HEADER_IN_FIRST_ROW
					if (r == 0)
					{
						if (c < (*lpDrillsDlgMem->pnames_of_colomns).size())
							sprintf((char *)(*items)[r][c].data(), "%s", (*lpDrillsDlgMem->pnames_of_colomns)[c].c_str());
					}
					else
					{
						if (c < (*lpDrillsDlgMem->pdrills)[r-1].size())
#if USE_STRING_IN_THE_CELL
							sprintf((char *)(*items)[r][c].data(), "%s", (*lpDrillsDlgMem->pdrills)[r-1][c].str.c_str());
#else
							sprintf((char *)(*items)[r][c].data(), "%s", (*lpDrillsDlgMem->pdrills)[r-1][c].s);
#endif
					}

#else // HEADER_IN_FIRST_ROW

					if (c < (*lpDrillsDlgMem->pdrills)[r].size())
#if USE_STRING_IN_THE_CELL
						sprintf((char *)(*items)[r][c].data(), "%s", (*lpDrillsDlgMem->pdrills)[r][c].str.c_str());
#else
						sprintf((char *)(*items)[r][c].data(), "%s", (*lpDrillsDlgMem->pdrills)[r][c].s);
#endif

#endif //HEADER_IN_FIRST_ROW

					switch (c)
					{
					case 0:
						{
							(*checkings)[r][c] = 2;
							(*editings)[r][c] = 0;
						}
						break;
					default:
						{
							(*checkings)[r][c] = 0;
							(*editings)[r][c] = 0;
						}
					}
				}
			}

			InitListViewColumns(hList, headers, true);


			LVITEM lvI;
			// Some code to create the list-view control.
			// Initialize LVITEM members that are common to all
			// items. 
			lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE; 
			lvI.state = 0; 
			lvI.stateMask = 0; 
			// first two empty rows
			ListView_InsertItem(hList, &lvI);
			ListView_InsertItem(hList, &lvI);
			// Initialize LVITEM members that are different for each item. 
			for (int index = 0; index < rows; index++)
			{
   				lvI.iItem = index;
				lvI.iImage = index;
				lvI.iImage = 0;
				lvI.iSubItem = 0;
				lvI.pszText = LPSTR_TEXTCALLBACK; // sends an
												  // LVN_GETDISP
												  // message.									  
				if(ListView_InsertItem(hList, &lvI) == -1)
				{
					char str[255];
					sprintf(str, "error %d %d", index, c);
					MessageBox(0,str,"ListView_InsertItem",0);
					return NULL;
				}
			}
		}
		break;

// Because the application specifies LPSTR_TEXTCALLBACK, it
// sends LVN_GETDISPINFO notification messages. The 
// application must process these notification messages and
// supply the text for the subitems.
// The text is stored in a previously listed
// application-defined structure called PETINFO. 
        case WM_MEASUREITEM: 
			{
				lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				printf("WM_MEASUREITEM lpmis->itemHeight %d\n", lpmis->itemHeight);
				printf("WM_MEASUREITEM lpmis->itemWidth %d\n", lpmis->itemWidth);
				lpmis->itemHeight = YBITMAP+100; 				
				//lpmis->itemWidth = 200; 				
				printf("WM_MEASUREITEM lpmis->CtlID == IDLIST = %d\n", lpmis->CtlID == IDLIST);
				printf("WM_MEASUREITEM lpmis->CtlType == ODT_LISTVIEW = %d\n", lpmis->CtlType == ODT_LISTVIEW);
				printf("WM_MEASUREITEM lpmis->itemID = %x %d\n", lpmis->itemID, lpmis->itemID);
				printf("WM_MEASUREITEM itemData = %x %d\n", lpmis->itemData, lpmis->itemData);
				printf("WM_MEASUREITEM wParam %d\n", wParam);
				
				//return TRUE; 
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

				if (lpdis->hwndItem == hList)
				{
					// Draw the bitmap and text for the list box item. Draw a 
					// rectangle around the bitmap if it is selected. 
					
					switch (lpdis->itemAction) 
					{ 
					case ODA_DRAWENTIRE: 
						{
							//Затем в MyListCtrl.cpp в DrawItem (переопределение события WM_DRAWITEM)
							//рисуются все айтемы с сабайтемами, 
							
							// Display the bitmap associated with the item.

							
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
							//checkbox'ы рисуются так:
							
							hdcMem = CreateCompatibleDC(lpdis->hDC); 

							int c, r = lpdis->itemID;
							//int ti = SendMessage(hList, LVM_GETTOPINDEX, 0, 0);

							if(r >= 0)
							{
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								
								// Display the text associated with the item. 
								for (c = 0; c < cols; c++)
								{
									RECT rcItem;
									
									ListView_GetSubItemRect(hList, r, c,
										LVIR_BOUNDS, 
										//LVIR_ICON,
										&rcItem);									
																		
									{
										HDITEM hdm; 
										hdm.mask=HDI_LPARAM; 									
										hdm.lParam=0; 
										

										//Получим стиль заголовка колонки 
										HWND hwndHD = ListView_GetHeader(hList); 
										Header_GetItem(hwndHD, c, &hdm);
										
										//Установим стиль заголовка колонки 
										LPCOLOMNDATA coldata = (LPCOLOMNDATA )hdm.lParam;
										COLORREF color = coldata->color;
#if HEADER_IN_FIRST_ROW
										if (r == 0)
											color = RGB(200, 200, 200);
#endif
										HBRUSH hbrush = CreateSolidBrush(color);
										HBRUSH hbrushOld = (HBRUSH__ *)SelectObject(lpdis->hDC, hbrush);

										FillRect(lpdis->hDC, &rcItem, hbrush);

										SelectObject(lpdis->hDC, hbrushOld);
										DeleteObject(hbrush);
									}									
																		
									GetTextMetrics(lpdis->hDC, &tm); 

									y = (lpdis->rcItem.bottom + lpdis->rcItem.top - 
										tm.tmHeight) / 2;
									
									TextOut(lpdis->hDC, 
										rcItem.left + XBITMAP + 6,
										y, 
										(*items)[r][c].c_str(), 
										strlen((*items)[r][c].c_str())
										);
								}
								
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							

								for (c = 0; c < cols; c++)
								{
									
									RECT rcItem;
									
									ListView_GetSubItemRect(hList, r, c,
										//LVIR_BOUNDS, 
										LVIR_ICON,
										&rcItem);

									if ( (*checkings)[r][c] > 0 )
									{
										if ( (*checkings)[r][c] == 1)
											hbmpPicture = hbmpUnchecked;
										else
											hbmpPicture = hbmpChecked;

										hbmpOld = (HBITMAP__ *)SelectObject(hdcMem, hbmpPicture); 
 
										if(!BitBlt(lpdis->hDC, 
											rcItem.left, rcItem.top, 
											rcItem.right - rcItem.left, 
											rcItem.bottom - rcItem.top, 
										   hdcMem, 0, 0, SRCCOPY)) 
										 ErrorExit("Screen to Compat Blt Failed"); 
									}
								}
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								SelectObject(hdcMem, (HBITMAP__ *)hbmpOld); 
								DeleteDC(hdcMem); 

								// Is the item selected? 
								if (lpdis->itemState & ODS_SELECTED)
								{ 
									// Draw a rectangle around bitmap to indicate 
									// the selection. 
									DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
								} 
							}
#if 1// !HEADER_IN_FIRST_ROW

							if (true)
							{
								RECT rcItem;
								
								ListView_GetSubItemRect(hList, 0, 0,
									LVIR_BOUNDS, 
									&rcItem);
								int HeightHeader = (rcItem.bottom - rcItem.top )*3;
								//Получаем дескриптор заголовка
								HWND hwndHD = ListView_GetHeader(hList); 
								HDITEM hdm; 
								hdm.mask=HDI_FORMAT; 
								for(int i=0; i < cols; i++) 
								{ 
									hdm.fmt=0; 
									//Получим стиль заголовка колонки 
									Header_GetItem(hwndHD,i,&hdm);
									
									if(hdm.fmt&HDF_OWNERDRAW)continue; 
									//Установим стиль заголовка колонки 
									hdm.fmt|=HDF_OWNERDRAW; 
									Header_SetItem(hwndHD,i,&hdm); 
								}
#if 0								
								HWND hEdit = ListView_GetEditControl(hList);

								RECT rcHD; 
								GetWindowRect(hwndHD,&rcHD); 
								RECT rcList; 
								GetWindowRect(hList,&rcList);
								RECT rcEdit; 
								GetWindowRect(hList,&rcEdit);

								printf("rcList %d %d %d %d\n", rcList.left, rcList.right, rcList.top, rcList.bottom);
								printf("rcHD %d %d %d %d\n", rcHD.left, rcHD.right, rcHD.top, rcHD.bottom);
								printf("rcEdit %d %d %d %d\n", rcEdit.left, rcEdit.right, rcEdit.top, rcEdit.bottom);
								
								RECT r; 
								GetWindowRect(hwndHD,&r); 

								//Проверяем высоту заголовка 
								if(r.bottom-r.top!=HeightHeader)
								{
									//Установим высоту заголовка 
	#if 0
									HDWP hdwp = BeginDeferWindowPos(2);
						
									hdwp = DeferWindowPos( hdwp, hwndHD, NULL, 
									//	r.left,r.top, r.right-r.left, HeightHeader,
										rcList.left, rcList.top,
										rcList.right - rcList.left, 
										HeightHeader,
										SWP_NOACTIVATE | SWP_NOZORDER |
										SWP_NOMOVE );
									
									hdwp = DeferWindowPos( hdwp, hList, NULL, 
										rcList.left, rcList.top + HeightHeader,
										rcList.right - rcList.left, 
										rcList.bottom - rcList.top,
										SWP_NOACTIVATE | SWP_NOZORDER );
									
									EndDeferWindowPos( hdwp );
	#else
									SetWindowPos(hwndHD,HWND_TOP,rcList.left-2,rcList.top - 10, rcList.right-rcList.left, HeightHeader,			
										SWP_NOZORDER/*|SWP_NOMOVE*/); 
									/*SetWindowPos(hList,HWND_TOP,rcList.left, rcList.top + HeightHeader,
										rcList.right - rcList.left, 
										rcList.bottom - rcList.top,			
										SWP_NOZORDER|SWP_NOMOVE);*/
	#endif
								}
								
#endif
							}
#endif // !HEADER_IN_FIRST_ROW

						}
						break; 
					}
				} 
			}
			break;
		case WM_USER+1:
			{
				char buff[255];
				GetWindowText(hWndEdit, buff, 254);
				if (edit_r >= 0 && edit_r < rows
					&& 
					edit_c >= 0 && edit_c < cols)
				strcpy((char *)(*items)[edit_r][edit_c].data(), buff);

				DestroyWindow(hWndEdit);
			}
			break; 
		case WM_USER+3:
			{
				// если выбрали колонку как каротаж, 
				// то все последующие колонки 
				// инициализируем как каротаж автоматически!!!
				unsigned int icol = wParam;

				//Получаем дескриптор заголовка
				HWND hwndHD = ListView_GetHeader(hList); 

				HDITEM hdm; 
				hdm.mask=HDI_LPARAM; 
				
				hdm.lParam=0; 
				//Получим стиль заголовка колонки 
				Header_GetItem(hwndHD,icol,&hdm);
				
				//Установим стиль заголовка колонки 
				LPCOLOMNDATA coldata;
				coldata = (LPCOLOMNDATA )hdm.lParam;
				HWND hwndComboBox = (HWND) coldata->hwndComboBox;

				long sel = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);

				if (sel == 9 || sel == 5 || sel == 6)
				{
#if 0
					for (unsigned int c = icol+1; c < cols; c++)
					{	
						HDITEM hdm; 
						hdm.mask=HDI_LPARAM; 
						
						hdm.lParam=0; 
						//Получим стиль заголовка колонки 
						Header_GetItem(hwndHD,c,&hdm);
						
						//Установим стиль заголовка колонки 
						LPCOLOMNDATA coldata;
						coldata = (LPCOLOMNDATA )hdm.lParam;
						HWND hwndComboBox = (HWND) coldata->hwndComboBox;

						SendMessage(hwndComboBox, CB_SETCURSEL, sel, 0);
					}
#endif
				}
			}
			break; 
	case WM_NOTIFY:
			//printf("WM_NOTIFY  code = %x  %d  hwndFrom == hList %d hwndHD %d\n", ((LPNMHDR) lParam)->code, ((LPNMHDR) lParam)->code, ((LPNMHDR) lParam)->hwndFrom == hList, ((LPNMHDR) lParam)->hwndFrom == hwndHD);
		switch (((LPNMHDR) lParam)->code)
		{
		case HDN_ITEMCLICK:
			{	
				LPNMHEADER pnmhd = ((LPNMHEADER) lParam);
				
				HDITEM hdm; 
				hdm.mask=HDI_LPARAM; 				
				hdm.lParam=0; 
				//Получим стиль заголовка колонки 
				Header_GetItem(pnmhd->hdr.hwndFrom,pnmhd->iItem,&hdm);
				
				//Установим стиль заголовка колонки 
				LPCOLOMNDATA coldata;
				coldata = (LPCOLOMNDATA )hdm.lParam;
				HWND hwndComboBox = (HWND) coldata->hwndComboBox;
				ChooseSurfColor(pnmhd->hdr.hwndFrom, coldata->color);

				RECT rcList;
				GetClientRect(hList, &rcList);
				InvalidateRect(hList, &rcList,TRUE);


			}
			break;

		case HDN_ITEMCHANGING:
			{
				LPNMHEADER pnmhd = ((LPNMHEADER) lParam);
				HDITEM hdm; 
				hdm.mask=HDI_LPARAM; 				
				hdm.lParam=0; 
				//Получим стиль заголовка колонки 
				Header_GetItem(pnmhd->hdr.hwndFrom,pnmhd->iItem,&hdm);

				//Установим стиль заголовка колонки 
				LPCOLOMNDATA coldata;
				coldata = (LPCOLOMNDATA )hdm.lParam;
				HWND hwndComboBox = (HWND) coldata->hwndComboBox;
				for (int c = pnmhd->iItem; c < cols; c++)
				{
					RECT rcHD;

					Header_GetItemRect(pnmhd->hdr.hwndFrom, c, &rcHD); 							
	
					HDITEM hdm; 
					hdm.mask=HDI_LPARAM; 
					
					hdm.lParam=0; 
					//Получим стиль заголовка колонки 
					Header_GetItem(pnmhd->hdr.hwndFrom,c,&hdm);
					
					//Установим стиль заголовка колонки 
					LPCOLOMNDATA coldata;
					coldata = (LPCOLOMNDATA )hdm.lParam;
					HWND hwndComboBox = (HWND) coldata->hwndComboBox;
					RECT ComboBoxRect = GetComboBoxRect(&rcHD);

					SetWindowPos(hwndComboBox,
						HWND_BOTTOM,
						ComboBoxRect.left, 
						ComboBoxRect.top, 
						ComboBoxRect.right, 
						ComboBoxRect.bottom,			
						NULL); 

					ShowWindow(hwndComboBox,true);
				}
			}
			break;

		case NM_CLICK :
			{
				LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;

				int  r = lpnmitem->iItem;
				int  c = lpnmitem->iSubItem;
				bool check_not_clicked = true;

				if (r >= 0 && (*checkings)[r][c])
				{
					RECT rcItem;
					RECT rcIcon;
					
					ListView_GetSubItemRect(hList, r, c,
						LVIR_LABEL,
						&rcItem);

					ListView_GetSubItemRect(hList, r, 0,
						LVIR_ICON,
						&rcIcon);


					if (c == 0 ?
						lpnmitem->ptAction.x <= rcIcon.right 
						&&
						lpnmitem->ptAction.x >= rcIcon.left
						:
						lpnmitem->ptAction.x - rcItem.left <= rcIcon.right - rcIcon.left 
						&&
						lpnmitem->ptAction.x - rcItem.left >= 0
						)
					{
						check_not_clicked = false;
						if ((*checkings)[r][c] == 2)
							(*checkings)[r][c] = 1;
						else
							if ((*checkings)[r][c] == 1)
								(*checkings)[r][c] = 2;
					}

					RECT rcClient;
					GetClientRect(hList, &rcClient);
					InvalidateRect(hList, &rcClient, TRUE);
				}

				if (r >= 0 && (*editings)[r][c] && check_not_clicked )
				{
					RECT rcItem;
					RECT rcList;
					RECT rcEdit;

					ListView_GetSubItemRect(hList, r, c,
						//LVIR_SELECTBOUNDS,
						LVIR_LABEL,
						&rcItem);

					GetWindowRect(hList, &rcList);

					//Получаем дескриптор заголовка
					HWND hwndHD = GetDlgItem(hList, 0); 
					
					rcEdit.left = rcList.left + rcItem.left + (c > 0 ? XBITMAP + 6 : 0);
					rcEdit.top = rcList.top + rcItem.top;

					rcEdit.right = rcItem.right - rcItem.left - (c > 0 ? XBITMAP + 6 : 0); //width
					rcEdit.bottom = rcItem.bottom -	rcItem.top;
					
					hWndEdit = CreateWindow ("EDIT", "", 
						WS_TABSTOP | WS_POPUP  | WS_VISIBLE, 
						rcEdit.left, 
						rcEdit.top, // rcItem.bottom + (list view header height)
						rcEdit.right, 
						rcEdit.bottom, 
						hDlg, 
						NULL,
						hInst, NULL); 

					edit_r = r;
					edit_c = c;
					
					ShowWindow(hWndEdit, 1);

					//--------------------------------------------------------------
					// Subclass the control. 
					wpOrigEditWndProc = (WNDPROC) SetWindowLongPtr(hWndEdit, 
						GWLP_WNDPROC, (LONG_PTR) EditWndSubclassProc); 

					SetWindowLongPtr(hWndEdit, GWLP_USERDATA,(LONG_PTR)lParam);
					//--------------------------------------------------------------

					SetWindowText(hWndEdit, (*items)[r][c].c_str() );

				}
			}
			break;

		case LVN_SETDISPINFO :
			{
				MessageBox(0,"LVN_SETDISPINFO","",0);
				//Notifies a list-view control's parent window that it must update 
				//the information it maintains for an item. 
				//This notification message is sent in the form of a WM_NOTIFY message. 
				
				//pnmv = (LPNMLVDISPINFO) lParam; 
				//Pointer to an NMLVDISPINFO structure that specifies information 
				//for the changed item. The item member of this structure is an LVITEM 
				//structure that contains information about the item that was changed. 
				//The pszText member of item contains a valid value, regardless of whether 
				//the LVIF_TEXT flag is set in the mask member of this structure. 
			}
			break;
		case LVN_GETDISPINFO:
			{
				//Sent by a list-view control to its parent window. 
				//It is a request for the parent window to provide information 
				//needed to display or sort a list-view item. This notification 
				//message is sent in the form of a WM_NOTIFY message. 
				
				//pnmv = (LPNMLVDISPINFO) lParam; 
				//Pointer to an NMLVDISPINFO structure. On input, the LVITEM structure 
				//contained in this structure specifies the type of information required 
				//and identifies the item or subitem of interest. Use the LVITEM structure 
				//to return the requested information to the control. If your message 
				//handler sets the LVIF_DI_SETITEM flag in the mask member of the 
				//LVITEM structure, the list-view control stores the requested information 
				//and will not ask for it again.

				
				NMLVDISPINFO * plvdi = ((NMLVDISPINFO *)lParam);
				plvdi->item.pszText = (char *)(*items)[plvdi->item.iItem][plvdi->item.iSubItem].c_str();
//				MessageBox(0,plvdi->item.pszText,"LVN_GETDISPINFO",0);

				// NOTE: in addition to setting pszText to point to 
				// the item text, you could copy the item text into pszText 
				// using StringCchCopy. For example:
				// StringCchCopy(rgPetInfo[plvdi->item.iItem].szKind, 
				//                          sizeof(rgPetInfo[plvdi->item.iItem].szKind), 
				//                          plvdi->item.pszText);
			}
			break;
		case LVN_BEGINLABELEDIT:
			{
	//			MessageBox(0,"LVN_BEGINLABELEDIT","",0);
				//Notifies a list-view control's parent window about 
				//the start of label editing for an item. This notification 
				//message is sent in the form of a WM_NOTIFY message.
				
				//pdi = (LPNMLVDISPINFO) lParam; 
				//Pointer to an NMLVDISPINFO structure. The item member of 
				//this structure is an LVITEM structure whose iItem member 
				//identifies the item being edited. 
			}
			break;
		case LVN_ENDLABELEDIT:
			{
				
				//Notifies a list-view control's parent window about 
				//the end of label editing for an item. This notification 
				//message is sent in the form of a WM_NOTIFY message. 

				//pdi = (LPNMLVDISPINFO) lParam; 
				//Pointer to an NMLVDISPINFO structure. The item member of 
				//this structure is an LVITEM structure whose iItem member 
				//identifies the item being edited. The pszText member of 
				//item contains a valid value when the LVN_ENDLABELEDIT message 
				//is sent, regardless of whether the LVIF_TEXT flag is set in 
				//the mask member of the LVITEM structure. If the user cancels 
				//editing, the pszText member of the LVITEM structure is NULL; 
				//otherwise, pszText is the address of the edited text. 

				NMLVDISPINFO * plvdi = ((NMLVDISPINFO *)lParam);
				if(plvdi->item.mask & LVIF_TEXT && plvdi->item.pszText)
					strcpy((char*)(*items)[plvdi->item.iItem][plvdi->item.iSubItem].data(), plvdi->item.pszText);
			}
			break;
		}
    case WM_COMMAND: 
		switch (LOWORD(wParam)) 
        {
		case IDOK: 
			{
#if HEADER_IN_FIRST_ROW
				int r0 = 1;
#else
				int r0 = 0;
#endif
				for(int r = r0; r < rows; r++)
				{
					lpDrillsDlgMem->checking_of_rows->operator [](r-r0) = 
						checkings->operator [](r).size() ? checkings->operator [](r).operator [](0) : 0;
				}
				//Получаем дескриптор заголовка
				HWND hwndHD = ListView_GetHeader(hList); 
				for (int c = 0; c < cols; c++)
				{
					HDITEM hdm; 
					hdm.mask=HDI_LPARAM; 
					
					hdm.lParam=0; 
					//Получим стиль заголовка колонки 
					Header_GetItem(hwndHD,c,&hdm);
					
					//Установим стиль заголовка колонки 
					LPCOLOMNDATA coldata;
					coldata = (LPCOLOMNDATA )hdm.lParam;
					HWND hwndComboBox = (HWND) coldata->hwndComboBox;

					int sel = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
					printf("c = %d, sel = %d\n", c, sel);
					lpDrillsDlgMem->types_of_colomns->operator [](c) = sel;

					lpDrillsDlgMem->colors_of_sloi->operator [](c) = coldata->color;
				}
				EndDialog(hDlg, wParam); 
			}
			break;
		case IDC_BUTTON_SAVE_COLOMNS_TYPES:
			{
/*
#if HEADER_IN_FIRST_ROW
				int r0 = 1;
#else
				int r0 = 0;
#endif
				for(int r = r0; r < rows; r++)
				{
					lpDrillsDlgMem->checking_of_rows->operator [](r-r0) = 
						checkings->operator [](r).size() ? checkings->operator [](r).operator [](0) : 0;
				}*/
				TCHAR lpstrFile[256];
				TCHAR filter[] =                     
					TEXT("Golden Software Data (*.dat)\0*.dat\0")
					TEXT("All Files (*.*)\0*.*\0");
				
				sprintf(lpstrFile, "\0");
				
				DWORD nFilterIndex = 0;
				if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) == S_OK)
				{
					//Получаем дескриптор заголовка
					FILE *stream;
					stream = fopen(lpstrFile,"wt");
					if (stream)
					{
						HWND hwndHD = ListView_GetHeader(hList); 
						for (int c = 0; c < cols; c++)
						{	
							HDITEM hdm; 
							hdm.mask=HDI_LPARAM; 
							
							hdm.lParam=0; 
							//Получим стиль заголовка колонки 
							Header_GetItem(hwndHD,c,&hdm);
							
							//Установим стиль заголовка колонки 
							LPCOLOMNDATA coldata;
							coldata = (LPCOLOMNDATA )hdm.lParam;
							HWND hwndComboBox = (HWND) coldata->hwndComboBox;

							int sel = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
							printf("c = %d, sel = %d\n", c, sel);
							lpDrillsDlgMem->types_of_colomns->operator [](c) = sel;

							lpDrillsDlgMem->colors_of_sloi->operator [](c) = coldata->color;

							double X = sel;
							double Y = coldata->color;

							fprintf(stream, "%lf, %lf\n", X, Y);
						}
						fclose (stream);
					}
				}
			}
			break;
		case IDC_BUTTON_LOAD_COLOMNS_TYPES:
			{
				char dat_path[4096];
				char dat_filename[4096];
				if (OpenFileDlg(hDlg, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0", dat_path) == S_OK)
				{	
					vector<vector<double> > * vectors = new vector<vector<double> >;
					if (ReadDatFile(hDlg, dat_path, dat_filename, vectors, NULL) == 0)
					{
						//double min_x = DBL_MAX, min_y = DBL_MAX;
						//double max_x = -DBL_MAX, max_y = -DBL_MAX;
						HWND hwndHD = ListView_GetHeader(hList); 
						size_t i = 0;
						int c = 0;						
						for (; i < vectors->size(), c < cols; i++, c++)
						{			
							if ((*vectors)[i].size() < 2)
							{
								char error_str[1024];
								sprintf(error_str, 
									"There must be at least 2 elements in each row\n"
									"But at %u row there are %u elements", i, vectors[i].size());
								MessageBox(hDlg, error_str, "IDC_BUTTON_LOAD_COLOMNS_TYPES", MB_OK | MB_ICONEXCLAMATION);
								return -1;
							}

							double X = (*vectors)[i][0];//int sel
							double Y = (*vectors)[i][1];//COLORREF color

							int sel = int(X);
							COLORREF color = COLORREF(Y);

							HDITEM hdm; 
							hdm.mask=HDI_LPARAM; 
							
							hdm.lParam=0; 
							//Получим стиль заголовка колонки 
							Header_GetItem(hwndHD,c,&hdm);
							
							//Установим стиль заголовка колонки 
							LPCOLOMNDATA coldata;
							coldata = (LPCOLOMNDATA )hdm.lParam;
							HWND hwndComboBox = (HWND) coldata->hwndComboBox;

							SendMessage(hwndComboBox, CB_SETCURSEL, sel, 0);
							printf("c = %d, sel = %d\n", c, sel);
							lpDrillsDlgMem->types_of_colomns->operator [](c) = sel;

							coldata->color = color;
							lpDrillsDlgMem->colors_of_sloi->operator [](c) = coldata->color;

						}
					}
					delete vectors;
				}

			}
			break;
        case IDCANCEL: 
			{
				EndDialog(hDlg, wParam); 
			}
        } 

		break;
	case WM_DESTROY:
		{
			//Получаем дескриптор заголовка
			HWND hwndHD = ListView_GetHeader(hList); 
			for (int c = 0; c < cols; c++)
			{	
				HDITEM hdm; 
				hdm.mask=HDI_LPARAM; 
				
				hdm.lParam=0; 
				//Получим стиль заголовка колонки 
				Header_GetItem(hwndHD,c,&hdm);
				
				//Установим стиль заголовка колонки 
				LPCOLOMNDATA coldata;
				coldata = (LPCOLOMNDATA )hdm.lParam;
				if (coldata) delete coldata;
			}
			delete headers;
		}
    } 
    return FALSE; 
} 
// CreateListView - creates a list-view control in
// report view. 
// Returns the handle to the new control if successful,
// or NULL otherwise. 
// hWndParent - handle to the control's parent window. 

HWND CreateListView (HWND hWndParent, LPVOID lpParam) 
{ 
	HWND hWndListView;
	RECT rcl; 
	INITCOMMONCONTROLSEX icex;
	// Ensure that the common control DLL is loaded. 
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex); 
	// Create the list-view window in report view with label 
	// editing enabled.
	GetClientRect (hWndParent, &rcl); 
	hWndListView = CreateWindow (WC_LISTVIEW, "", 
		WS_CHILD | LVS_REPORT | LVS_EDITLABELS, 
		0, 0, rcl.right - rcl.left, rcl.bottom -
        rcl.top, 
		hWndParent, (HMENU)NULL /*ID_LISTVIEW*/, hInst, lpParam); 
	if (hWndListView == NULL) 
		return NULL; 
}

// CreateListView - creates a list-view control in
// report view. 
// Returns the handle to the new control if successful,
// or NULL otherwise. 
// hWndParent - handle to the control's parent window. 

HWND CreateListView (HWND hwndParent, int x, int y, double part_h, double part_v) 
{ 
printf("CreateListView\n");
	HWND hWndListView;
	RECT rcl; 
	INITCOMMONCONTROLSEX icex;
	
	// Ensure that the common control DLL is loaded. 
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC  = ICC_LISTVIEW_CLASSES;
	InitCommonControlsEx(&icex); 
	// Create the list-view window in report view with label 
	// editing enabled.

	
	GetClientRect (hwndParent, &rcl); 
	//long marge = (rcl.bottom - rcl.top) * double((1.0 - part_v) / 2.0);
	hWndListView = CreateWindowEx (
		WS_EX_CLIENTEDGE | /*LVS_EX_CHECKBOXES |*/ LVS_EX_FULLROWSELECT, 
		WC_LISTVIEW, 
		"", 
        WS_TABSTOP 
		| WS_CHILD 
		| LVS_REPORT 
		| LVS_ICON 
		| LVS_OWNERDATA 
		| LVS_OWNERDRAWFIXED
//		| LBS_OWNERDRAWVARIABLE 
		,
        x, y, 
		part_h * (rcl.right - rcl.left-x), 
		part_v * (rcl.bottom - rcl.top-y), 
        hwndParent, 
		(HMENU)IDLIST,
		hInst, NULL); 
	
	if (hWndListView == NULL) 
		return NULL; 
	else
		return hWndListView;
}

// SetView - sets a list-view's window style to change
// the view. 
// hWndListView - handle to the list-view control. 
// dwView - value specifying the new view style.

VOID SetView(HWND hWndListView, DWORD dwView) 
{ 
	// Retrieve the current window style. 
	DWORD dwStyle = GetWindowLongPtr(hWndListView, GWL_STYLE); 
	// Only set the window style if the view bits have
	// changed. 
	
	if ((dwStyle & LVS_TYPEMASK) != dwView) 
		SetWindowLongPtr(hWndListView, GWL_STYLE, 
		(dwStyle & ~LVS_TYPEMASK) | dwView); 
} 
// InitListViewImageLists - creates image lists for a
// list-view control.
// This function only creates image lists. It does not
// insert the items into the control, which is necessary
// for the control to be visible.   
// Returns TRUE if successful, or FALSE otherwise. 

// hWndListView - handle to the list-view control. 

BOOL InitListViewImageLists(HWND hWndListView) 
{ 
    HICON hiconItem;     // icon for list-view items 
    HIMAGELIST hLarge;   // image list for icon view 
    HIMAGELIST hSmall;   // image list for other views 

// Create the full-sized icon image lists. 
    hLarge = ImageList_Create(GetSystemMetrics(SM_CXICON), 
    GetSystemMetrics(SM_CYICON), ILC_MASK, 1, 1); 
    hSmall = ImageList_Create(GetSystemMetrics(SM_CXSMICON), 
    GetSystemMetrics(SM_CYSMICON), ILC_MASK, 1, 1); 
	
// Add an icon to each image list.  
    hiconItem = LoadIcon(hInst,
	   MAKEINTRESOURCE(IDI_ICON_SURF_CUBE)); 
    ImageList_AddIcon(hLarge, hiconItem); 
    DestroyIcon(hiconItem); 


    hiconItem = LoadIcon(hInst,
	   MAKEINTRESOURCE(IDI_SMALL)); 
    ImageList_AddIcon(hSmall, hiconItem); 
     DestroyIcon(hiconItem); 

/******************************************************
Usually you have multiple icons; therefore, the previous
four lines of code can be inside a loop. The following
code shows such a loop. The icons are defined in the
application's header file as resources, which are
numbered consecutively starting with IDS_FIRSTICON. The
number of icons is defined in the header file as
C_ICONS.

for(index = 0; index < C_ICONS; index++)
    {
    hIconItem = LoadIcon (hInst, MAKEINTRESOURCE
	   (IDS_FIRSTICON + index));
    ImageList_AddIcon(hSmall, hIconItem);
    ImageList_AddIcon(hLarge, hIconItem);
    Destroy(hIconItem);
    }
   *******************************************************/
// Assign the image lists to the list-view control. 
    ListView_SetImageList(hWndListView, hLarge, LVSIL_NORMAL); 
    ListView_SetImageList(hWndListView, hSmall, LVSIL_SMALL); 
    return TRUE; 
} 

// InitListViewColumns - adds columns to a list-view
// control. 
// Returns TRUE if successful, or FALSE otherwise. 
// hWndListView - handle to the list-view control. 
BOOL InitListViewColumns(HWND hWndListView, vector<string> * headers, bool add_combo) 
{ 
	//printf("InitListViewColumns\n");
    char szText[256];     // temporary buffer 
    LVCOLUMN lvc; 
    int iCol; 

// Initialize the LVCOLUMN structure.
// The mask specifies that the format, width, text, and
// subitem members of the structure are valid. 
    lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT |
	  LVCF_SUBITEM; 
	  
// Add the columns. 
    for (iCol = 0; iCol < (*headers).size(); iCol++) 
	{ 
		strcpy(szText, (*headers)[iCol].c_str());
        lvc.iSubItem = iCol;
        lvc.pszText = szText;	
        lvc.cx = 100;     // width of column in pixels

        if ( iCol < 2 )
          {
          lvc.fmt = LVCFMT_LEFT;  // left-aligned column
          }
        else
          { 
          lvc.fmt = LVCFMT_RIGHT; // right-aligned column		                         
          }

		lvc.fmt = LVCFMT_CENTER;

        if (ListView_InsertColumn(hWndListView, iCol,
		        &lvc) == -1) 
            return FALSE; 

		LPCOLOMNDATA coldata;
		coldata = new COLOMNDATA;
		coldata->color = RGB(255,255,255);
		coldata->hwndComboBox = NULL;

		//Получаем дескриптор заголовка
		HWND hwndHD = ListView_GetHeader(hWndListView); 
		RECT rcHD;
		Header_GetItemRect(hwndHD, iCol, &rcHD);

		if (add_combo)
		{
			RECT ComboBoxRect = GetComboBoxRect(&rcHD);

			HWND hWndComboBox = CreateWindow ("COMBOBOX", "", 
				WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST, 
				ComboBoxRect.left,
				ComboBoxRect.top,
				ComboBoxRect.right,
				ComboBoxRect.bottom,
				hwndHD, 
				(HMENU)iCol, //IDCOMBO,
				hInst, NULL); 


			SendMessage(hWndComboBox, CB_RESETCONTENT, 0, 0);
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"not used");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"well ID");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"X");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Y");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Ust.Alt");

			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Pod.Alt");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Pod.Glub");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Zab.Alt");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Zab.Glub");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Karotazh");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"hydro ust");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"hydro pojavl");
			SendMessage(hWndComboBox, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"sloi moschn");
			SendMessage(hWndComboBox, CB_SETCURSEL, 0, 0);

			coldata->hwndComboBox = hWndComboBox;

			//--------------------------------------------------------------
			// Subclass the control. 
			wpOrigComboBoxWndProc = (WNDPROC) SetWindowLongPtr(hWndComboBox, 
				GWLP_WNDPROC, (LONG_PTR) ComboBoxWndSubclassProc);

			SetWindowLongPtr(hWndComboBox, GWLP_USERDATA,(LONG_PTR)iCol);
			//--------------------------------------------------------------
		}
				
				
		HDITEM hdm; 
		hdm.mask=HDI_LPARAM; 			
		hdm.lParam=(LPARAM)coldata;				
		Header_SetItem(hwndHD,iCol,&hdm); 

    } 
	return TRUE; 
} 

int GetItemWorkingArea(HWND hWndListView, int iItem)
{
	UINT     uWorkAreas = 0;
	int      nReturn = -1;
	LPRECT   pRects;
	POINT    pt;
	if(!ListView_GetItemPosition(hWndListView, iItem, &pt))
		return nReturn;
	ListView_GetNumberOfWorkAreas(hWndListView, &uWorkAreas);
	
	if(uWorkAreas)
	{
		pRects = (LPRECT)GlobalAlloc(GPTR, sizeof(RECT) *
			uWorkAreas);
		if(pRects)
		{
			UINT  i;
			
			nReturn = 0;
			
			ListView_GetWorkAreas(hWndListView, uWorkAreas, pRects);
			
			for(i = 0; i < uWorkAreas; i++)
			{
				if(PtInRect((pRects + i), pt))
				{
					nReturn = i;
					break;
				}
			}
			GlobalFree((HGLOBAL)pRects);
		}
	}
	return nReturn;
}

