// CommonMeanFileDialog.cpp: implementation of the CommonMeanFileDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CommonMeanFileDialog.h"
#include "../../resource.h"
#include "../../wintools/src/listfun.h"
#include "./commonmeanfiledialog.h"
#include "../../tools/src/datenum.h"
#include "../../tools/src/filedlg.h"
#include "../../array/src/matrixes.h"
#include "ParseTimeString.h"

// Заголовок блокнота Wizard
PROPSHEETHEADER psheetHeader;

// Массив описаний страниц блокнота Wizard
PROPSHEETPAGE   psheetPage[3];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern HINSTANCE hInst;
extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess = false) ;



UINT_PTR CALLBACK DlgProcOpenFilesToCommon(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    OpenFilesToCommonData *oftcd;
    LPOPENFILENAME lpOFN;

    switch (message)
    {
        case WM_INITDIALOG:
            // Save off the long pointer to the OPENFILENAME structure.
            SetWindowLongPtr(hDlg, DWLP_USER, (LONG_PTR)lParam);
            lpOFN = (LPOPENFILENAME)lParam;
            oftcd = (OpenFilesToCommonData *)lpOFN->lCustData;
			SendDlgItemMessage(hDlg, IDD_OPEN_FILES_TO_COMMON, BM_SETCHECK, oftcd->bUseWholeDirectory ? BST_CHECKED : BST_UNCHECKED, 0);
            break;

        case WM_DESTROY:
            lpOFN = (LPOPENFILENAME)GetWindowLongPtr(hDlg, DWLP_USER);
            oftcd = (OpenFilesToCommonData *)lpOFN->lCustData;
			oftcd->bUseWholeDirectory = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY));
            break;

        default:
            return FALSE;
    }
    return TRUE;
}

INT_PTR CALLBACK DlgProc1( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	const int n=1023; // length of buffer string line
	static char szBuff[n]; // buffer string line
	static char szLine1[n]; // buffer string line
	static char szLineEnd[n]; // buffer string line
	static CommonMeanFileDialog * lpCommonMeanFileDialog;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			PROPSHEETPAGE * lppsheetPage = (PROPSHEETPAGE *)lParam;
			lpCommonMeanFileDialog = (CommonMeanFileDialog *)lppsheetPage->lParam;
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// -------------------------------------------------------------------
			SendDlgItemMessage(hDlg, IDC_CHECK_DELIMITER_TAB, BM_SETCHECK, 
				lpCommonMeanFileDialog->dd.bTab ? BST_CHECKED : BST_UNCHECKED, 0);
			// -------------------------------------------------------------------
			SendDlgItemMessage(hDlg, IDC_CHECK_DELIMITER_COMMA, BM_SETCHECK, 
				lpCommonMeanFileDialog->dd.bComma ? BST_CHECKED : BST_UNCHECKED, 0);
			// -------------------------------------------------------------------
			SendDlgItemMessage(hDlg, IDC_CHECK_DELIMITER_SPACE, BM_SETCHECK, 
				lpCommonMeanFileDialog->dd.bSpace ? BST_CHECKED : BST_UNCHECKED, 0);
			// -------------------------------------------------------------------
			SendDlgItemMessage(hDlg, IDC_CHECK_DELIMITER_COMMA_POINT, BM_SETCHECK, 
				lpCommonMeanFileDialog->dd.bCommaPoint ? BST_CHECKED : BST_UNCHECKED, 0);
			// -------------------------------------------------------------------
			SendDlgItemMessage(hDlg, IDC_CHECK_DELIMITER_OTHER, BM_SETCHECK, 
				lpCommonMeanFileDialog->dd.bOther ? BST_CHECKED : BST_UNCHECKED, 0);
			EnableWindow(GetDlgItem(hDlg, IDC_EDIT_DELIMITER_OTHER), 
				lpCommonMeanFileDialog->dd.bOther);
			if (lpCommonMeanFileDialog->dd.bOther)
			{								 
				SendDlgItemMessage( hDlg, IDC_EDIT_DELIMITER_OTHER, EM_SETLIMITTEXT,
					1, 0);
				SetFocus(GetDlgItem(hDlg, IDC_EDIT_DELIMITER_OTHER));
			}
			// -------------------------------------------------------------------
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
		break;
	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code)
		{
		case PSN_SETACTIVE:
			{
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_LIST_POLYOTY,0);	
				// Разблокируем кнопку Next
				PropSheet_SetWizButtons(GetParent(hDlg), PSWIZB_NEXT);
			}
			break;
		case PSN_WIZNEXT:
			{
				if (lpCommonMeanFileDialog->dd.bOther)
				{
					char cc[2];
					GetDlgItemText(hDlg, IDC_EDIT_DELIMITER_OTHER, cc,1);
					lpCommonMeanFileDialog->dd.charOther = cc[1];
					char sss[255];sprintf(sss, "%c %d %x\n",
								  lpCommonMeanFileDialog->dd.charOther,
								  lpCommonMeanFileDialog->dd.charOther,
								  lpCommonMeanFileDialog->dd.charOther);
								  
					MessageBox(0,sss,"",0);
					sprintf(sss, "%c %s\n",
						cc[1],
						cc,
						cc[1]);
					
					MessageBox(0,sss,"",0);
				}
			}
			break;
		}
		break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
		 case IDC_INIT_LIST_POLYOTY:
			 {
				 SendDlgItemMessage( hDlg, IDC_LIST_SELECT_FILE_DELIMITER, LB_RESETCONTENT, 0,0);
				 FILE *stream;
				 if ((stream = fopen(
					 lpCommonMeanFileDialog->szFile,
					 "rt")) == NULL)
				 {
					 MessageBox(0, lpCommonMeanFileDialog->szFile, "Cannot open input file.Import", 
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
				 GetClientRect(lpCommonMeanFileDialog->hWnd, &rcClient); 
				 cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
				 hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
					 (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
					 0, 0,
					 //rcClient.left, rcClient.bottom,
					 rcClient.right, cyVScroll, 
					 lpCommonMeanFileDialog->hWnd, (HMENU) 0, hInst, NULL); 
				 
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
				 size_t chars, max_chars = 0;
				 
				 int nParams = 0;
				 size_t bytes_line;
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
						SendDlgItemMessage( hDlg, IDC_LIST_SELECT_FILE_DELIMITER, 
							LB_ADDSTRING, 0,
							(LPARAM)(LPCTSTR)szBuff);
						chars = strlen(ch);if (chars > max_chars) max_chars = chars;
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
							SendDlgItemMessage( hDlg, IDC_LIST_SELECT_FILE_DELIMITER, LB_ADDSTRING, 0,
								(LPARAM)(LPCTSTR)szBuff);
						if (len == 0)
						{
							strcpy(szLine1, szBuff);
						}
						else
							strcpy(szLineEnd, szBuff);

						len++;
						chars = strlen(ch);if (chars > max_chars) max_chars = chars;
					}
				}
				if(len >= to_display_in_list)
					MessageBox(0,"Файл изображён не полностью\nТем не менее он будет полностью загружен", "", 0);

				fclose(stream);
				DestroyWindow(hwndPB);

				SendDlgItemMessage( hDlg, IDC_LIST_SELECT_FILE_DELIMITER, LB_SETHORIZONTALEXTENT,
					max_chars*6, 0);
			 }
			 break;
		 case IDC_CHECK_DELIMITER_TAB:
			 {
				 lpCommonMeanFileDialog->dd.bTab = 
					 IsDlgButtonChecked( hDlg, IDC_CHECK_DELIMITER_TAB) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_DELIMITER_COMMA:
			 {
				 lpCommonMeanFileDialog->dd.bComma = 
					 IsDlgButtonChecked( hDlg, IDC_CHECK_DELIMITER_COMMA) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_DELIMITER_SPACE:
			 {
				 lpCommonMeanFileDialog->dd.bSpace = 
					 IsDlgButtonChecked( hDlg, IDC_CHECK_DELIMITER_SPACE) == BST_CHECKED;
			 }
			 break;
		 case IDC_CHECK_DELIMITER_COMMA_POINT:
			 {
				 lpCommonMeanFileDialog->dd.bCommaPoint = 
					 IsDlgButtonChecked( hDlg, IDC_CHECK_DELIMITER_COMMA_POINT) == BST_CHECKED;
			 }
			 break;			 
		 case IDC_CHECK_DELIMITER_OTHER:
			 {
				 lpCommonMeanFileDialog->dd.bOther = 
					 IsDlgButtonChecked( hDlg, IDC_CHECK_DELIMITER_OTHER) == BST_CHECKED;
				 EnableWindow(GetDlgItem(hDlg, IDC_EDIT_DELIMITER_OTHER), 
					 lpCommonMeanFileDialog->dd.bOther);
				 SendDlgItemMessage( hDlg, IDC_EDIT_DELIMITER_OTHER, EM_SETLIMITTEXT,
					1, 0);
				 if(lpCommonMeanFileDialog->dd.bOther)
					 SetFocus(GetDlgItem(hDlg, IDC_EDIT_DELIMITER_OTHER));
				 else
					 SetDlgItemText(hDlg, IDC_EDIT_DELIMITER_OTHER, "");
			 }
			 break;
		 case IDC_CHECK_USE_MANY_DELIMITERS_AS_ONE:
			 {
				 lpCommonMeanFileDialog->dd.bUseManyDelimitersAsOne = 
					 IsDlgButtonChecked( hDlg, IDC_CHECK_USE_MANY_DELIMITERS_AS_ONE) == BST_CHECKED;
			 }
			 break;
           case IDCANCEL :
			   break;
         }
         break;

      default :
         return( FALSE );
  }
  return( TRUE );
}

void CommonMeanFileDialog::EnableControls2(HWND hDlg, BOOL bEnable)
{
//	EnableWindow(GetDlgItem(hDlg, IDC_STATIC_TIME_FORMAT), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_COMBO_TIME_FORMAT), bEnable);
	EnableWindow(GetDlgItem(hDlg, ID_TEST_TIME_FORMAT), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_STATIC_LOCAL_TIME_OFFSET), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET), bEnable && this->cmfd.thisIsLocalTime);
}
void CommonMeanFileDialog::EnableControls3(HWND hDlg, BOOL bEnable)
{
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE), bEnable);

	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE3), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE3), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE3), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE3), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3), bEnable);

	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE4), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE4), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE4), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE4), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4), bEnable);

	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MIN_XYZ), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEDIAN_XYZ), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MEAN_XYZ), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_DISP_XYZ), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_XYZ), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_XYZ), bEnable);
	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_MAXMIN_XYZ), bEnable);

	EnableWindow(GetDlgItem(hDlg, IDC_CHECK_COMMON_USE_REVERSE_ANGLES), bEnable);	
}

extern WNDPROC wpOrigEditWndProc;
extern WNDPROC wpOrigComboBoxWndProc;
extern WNDPROC wpOrigHeaderWndProc;
extern WNDPROC wpOrigListViewWndProc;

#define IDCOMBO2 11111
#define IDLIST2 11112
#define HEADER_IN_FIRST_ROW2	1
INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
    int y; 
    TEXTMETRIC tm; 
	static HWND hList;
//	static HWND hWndEdit;
	static HWND hWndComboBox;

	static vector<string>			* headers;
	static vector<vector<string> >	* items;

	static size_t rows, cols;
//	static int edit_r, edit_c;

    LPMEASUREITEMSTRUCT lpmis; 
    LPDRAWITEMSTRUCT lpdis; 

	static CommonMeanFileDialog * lpCommonMeanFileDialog;

    switch (message) 
    { 
	case WM_INITDIALOG:
		{
			PROPSHEETPAGE * lppsheetPage = (PROPSHEETPAGE *)lParam;
			lpCommonMeanFileDialog = (CommonMeanFileDialog *)lppsheetPage->lParam;
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"excel time: in days since 1.1.1900\\tX\\tY\\tZ");
			SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"tezey file: dd.mm.yy hh:mm:ss,milli,X,Y,Z");
			SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"Custom fileformat");
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			headers = new vector<string>;
			items	= new vector<vector<string> >;
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
		}
		break;

        case WM_MEASUREITEM: 
			{
				lpmis = (LPMEASUREITEMSTRUCT) lParam; 
				// Set the height of the list box items. 
				//lpmis->itemHeight = YBITMAP+10; 				
				//lpmis->itemWidth = 200; 				
				return TRUE; 
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
							//checkbox'ы рисуются так:

							int r = lpdis->itemID;
							//int ti = SendMessage(hList, LVM_GETTOPINDEX, 0, 0);

							if(r >= 0)
							{
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								
								// Display the text associated with the item. 
								for (int c = 0; c < cols; c++)
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
										//HWND hwndHD = ListView_GetHeader(hList); 
										//Header_GetItem(hwndHD, c, &hdm);
										
										//Установим стиль заголовка колонки 
										//LPCOLOMNDATA coldata = (LPCOLOMNDATA )hdm.lParam;
										//COLORREF color = coldata->color;
#if HEADER_IN_FIRST_ROW2
										//if (r == 0)
										//	color = RGB(200, 200, 200);
#endif
										COLORREF color = RGB(200, 200, 200);
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
										rcItem.left /*+ XBITMAP + 6*/,
										y, 
										(*items)[r][c].c_str(), 
										strlen((*items)[r][c].c_str())
										);
								}
								
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

								// Is the item selected? 
								if (lpdis->itemState & ODS_SELECTED)
								{ 
									// Draw a rectangle around bitmap to indicate 
									// the selection. 
									DrawFocusRect(lpdis->hDC, &lpdis->rcItem); 
								} 
							}
#if !HEADER_IN_FIRST_ROW2
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
							}
#endif // !HEADER_IN_FIRST_ROW2
						}
						break; 
					}
				} 
			}
			break;
	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code)
		{
#if (_WIN32_WINNT >= 0x501)
		case LVN_ENDSCROLL:
			{
				printf("LVN_ENDSCROLL \n");
					RECT rcList;
					GetClientRect(hList, &rcList);
					InvalidateRect(hList, &rcList,TRUE);
			}
			break;
		case LVN_BEGINSCROLL :
			{
				printf("LVN_BEGINSCROLL \n");
			}
			break;
#endif
		case PSN_SETACTIVE:
			{
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendDlgItemMessage( hDlg, IDC_COMBO_FILE_FORMAT, CB_SETCURSEL,
					lpCommonMeanFileDialog->cmfd.fileFormat,(LPARAM)0 );
				lpCommonMeanFileDialog->EnableControls2(hDlg, 
					lpCommonMeanFileDialog->cmfd.fileFormat == 2);
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				CheckDlgButton( hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME,
					lpCommonMeanFileDialog->cmfd.thisIsLocalTime ? BST_CHECKED : BST_UNCHECKED );
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
				SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_SETCURSEL,
					lpCommonMeanFileDialog->cmfd.timeFormat,(LPARAM)0 );
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				SendMessage(hDlg,WM_COMMAND,IDC_INIT_LIST_POLYOTY,0);	
				// Разблокируем кнопк Next и Back, когда страница
				// блокнота Wizard становится активной
				PropSheet_SetWizButtons(GetParent(hDlg), 
					PSWIZB_NEXT /*| PSWIZB_BACK*/);
			}
			break;
		case PSN_WIZNEXT:
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
					//LPCOLOMNDATA coldata;
					//coldata = (LPCOLOMNDATA )hdm.lParam;
					//HWND hwndComboBox = (HWND) coldata->hwndComboBox;

					//int sel = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
					//printf("c = %d, sel = %d\n", c, sel);
					//lpCommonMeanFileDialog->types_of_colomns->operator [](c) = sel;
				}
			}
			break;
		case PSN_WIZBACK:
			{
			}
			break;
		case LVN_GETDISPINFO:
			{
				
				NMLVDISPINFO * plvdi = ((NMLVDISPINFO *)lParam);
				plvdi->item.pszText = (char *)(*items)[plvdi->item.iItem][plvdi->item.iSubItem].c_str();

			}
			break;
		}
    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        {
		case IDC_COMBO_FILE_FORMAT:
			{
				lpCommonMeanFileDialog->cmfd.fileFormat = (short)SendDlgItemMessage( hDlg, 
					IDC_COMBO_FILE_FORMAT,
					CB_GETCURSEL,0,(LPARAM)0 );

				lpCommonMeanFileDialog->EnableControls2(hDlg, 
						lpCommonMeanFileDialog->cmfd.fileFormat == 2);
			}
			break;
		case IDC_CHECK_THIS_IS_LOCAL_TIME:
			{
				lpCommonMeanFileDialog->cmfd.thisIsLocalTime = IsDlgButtonChecked( hDlg, IDC_CHECK_THIS_IS_LOCAL_TIME) == BST_CHECKED;
				if (lpCommonMeanFileDialog->cmfd.thisIsLocalTime)
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET); 
					EnableWindow(hEdit, TRUE);
					SetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET,
						lpCommonMeanFileDialog->cmfd.localTimeOffsetHours, true);

				}
				else
				{
					HWND hEdit = GetDlgItem(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET); 
					SetDlgItemText(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, "");
					EnableWindow(hEdit, FALSE);
				}
			}
			break;
		case IDC_COMBO_TIME_FORMAT:
			{
				lpCommonMeanFileDialog->cmfd.timeFormat = (short)SendDlgItemMessage( hDlg, 
					IDC_COMBO_TIME_FORMAT,
					CB_GETCURSEL,0,(LPARAM)0 );
			}
			break;
		case ID_TEST_TIME_FORMAT :
			{
				int listBoxLen = lpCommonMeanFileDialog->pcells->size();
				char stime1[2047], stime2[2047];
				for (int i = 0;  i < 2; i++)
				{
					int y,mo,d,h,mi,s,milli;
					double t;
					const char* title;

					if (i == 0)
						title = lpCommonMeanFileDialog->pcells->begin()->begin()->str.c_str(); //str.c_str() or str.data() ?
					else
						title = lpCommonMeanFileDialog->pcells->back().begin()->str.c_str();


					if (!ParseTimeString(title, 
						lpCommonMeanFileDialog->cmfd.timeFormat, 
						lpCommonMeanFileDialog->cmfd.thisIsLocalTime,	
						lpCommonMeanFileDialog->cmfd.localTimeOffsetHours,
						y, mo, d, h, mi, s, milli, t))
						return 0;					

					if (i == 0)
					{
						sprintf(stime1,"t = %lf %02d:%02d:%d %02d:%02d:%02d.%lf\n",
							t, d,mo,y,h,mi,s,double(milli)/1000.0);
						if (lParam == 1)
						{
							lpCommonMeanFileDialog->cmfd.startYear	= y;
							lpCommonMeanFileDialog->cmfd.startMonth	= mo;
							lpCommonMeanFileDialog->cmfd.startDay	= d;
						}
					}
					else
					{
						sprintf(stime2,"t = %lf %02d:%02d:%d %02d:%02d:%02d.%lf",
							t, d,mo,y,h,mi,s,double(milli)/1000.0);
						if (lParam == 1)
						{
							lpCommonMeanFileDialog->cmfd.finishYear	= y;
							lpCommonMeanFileDialog->cmfd.finishMonth= mo;
							lpCommonMeanFileDialog->cmfd.finishDay	= d;
						}
					}
				}
				char str[4800];
				strcpy(str, stime1);strcat(str, stime2);
				if (lParam != 1 && lParam != 2)
					MessageBox(0,str,"time interval",0);
			}
			break;


 		case IDC_INIT_LIST_POLYOTY:
			{
				for (int i1 = 0; i1 < (*lpCommonMeanFileDialog->pcells).size(); i1++)
				{
					for (int i2 = 0; i2 < (*lpCommonMeanFileDialog->pcells)[i1].size(); i2++)
					{
						//(*lpCommonMeanFileDialog->pcells)[i1][i2].str.clear();
					}
					(*lpCommonMeanFileDialog->pcells)[i1].clear();
				}
				(*lpCommonMeanFileDialog->pcells).clear();

				for(int i1 = 0; i1 < (*lpCommonMeanFileDialog->pnames_of_colomns).size(); i1++)
				{
					//(*lpCommonMeanFileDialog->pnames_of_colomns)[i1].clear();
				}
				(*lpCommonMeanFileDialog->pnames_of_colomns).clear();

				ReadCellFile(
					lpCommonMeanFileDialog->hWnd, 
					lpCommonMeanFileDialog->szFile, 
					lpCommonMeanFileDialog->filename, 
					lpCommonMeanFileDialog->pcells, 
					lpCommonMeanFileDialog->pnames_of_colomns, 
					lpCommonMeanFileDialog->dd,
					128);


				//lpCommonMeanFileDialog->types_of_colomns->resize(lpCommonMeanFileDialog->pnames_of_colomns->size());


				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						

				rows = lpCommonMeanFileDialog->pcells->size();
				cols = lpCommonMeanFileDialog->pnames_of_colomns->size();

				lpCommonMeanFileDialog->rows = rows;
				lpCommonMeanFileDialog->cols = cols;


	#if HEADER_IN_FIRST_ROW2
				rows++;
	#endif

#if 0
				hList = CreateListView (hDlg, 10, 120, 0.97, 0.95);
#else
				hList = ::GetDlgItem(hDlg, IDC_LIST_OF_CELLS);
				LONG dwStyle = GetWindowLongPtr(hList, GWL_STYLE);
				dwStyle |=  LVS_REPORT | LVS_ICON | LVS_OWNERDATA 
					| LVS_OWNERDRAWFIXED | LBS_OWNERDRAWVARIABLE;
				SetWindowLongPtr(hList, GWL_STYLE, dwStyle);

				LONG dwExStyle = GetWindowLongPtr(hList, GWL_EXSTYLE);
				dwStyle |= WS_EX_CLIENTEDGE | LVS_EX_FULLROWSELECT;
				SetWindowLongPtr(hList, GWL_EXSTYLE, dwStyle);
#endif

				SetFocus(hList);

				ShowWindow(hList, 1);
				InitListViewImageLists(hList);

				//--------------------------------------------------------------
				// Subclass the control. 
				wpOrigListViewWndProc = (WNDPROC) SetWindowLongPtr(hList, 
					GWLP_WNDPROC, (LONG_PTR) ListViewWndSubclassProc); 

				//SetWindowLongPtr(hList, GWLP_USERDATA,(LONG_PTR)lParam);
				//--------------------------------------------------------------
				HWND hwndHD = ListView_GetHeader(hList); 
				//--------------------------------------------------------------
				// Subclass the control. 
				wpOrigHeaderWndProc = (WNDPROC) SetWindowLongPtr(hwndHD, 
					GWLP_WNDPROC, (LONG_PTR) HeaderWndSubclassProc); 
				SetWindowLongPtr(hwndHD, GWLP_USERDATA,(LONG_PTR)cols);

				int c = 0;
				for (; c < cols; c++)
				{
					headers->push_back(string());
					headers->back().resize(32);
					sprintf((char *)headers->back().data(), "%s", 
						(*lpCommonMeanFileDialog->pnames_of_colomns)[c].c_str());				
				}
				items->		resize(rows);

				for (int r = 0; r < rows; r++)
				{
					items->operator		[] (r).resize(cols);

					for (int c = 0; c < cols; c++)
					{
						(*items)[r][c] .resize(256);
	#if HEADER_IN_FIRST_ROW2
						if (r == 0)
						{
							sprintf((char *)(*items)[r][c].data(), "%s", 
								(*lpCommonMeanFileDialog->pnames_of_colomns)[c].c_str());
						}
						else
						{
	#if USE_STRING_IN_THE_CELL
							sprintf((char *)(*items)[r][c].data(), "%s", 
								(*lpCommonMeanFileDialog->pcells)[r-1][c].str.c_str());
	#else
							sprintf((char *)(*items)[r][c].data(), "%s", 
								(*lpCommonMeanFileDialog->pcells)[r-1][c].s);
	#endif
						}
	#else // HEADER_IN_FIRST_ROW2

	#if USE_STRING_IN_THE_CELL
						sprintf((char *)(*items)[r][c].data(), "%s", 
							(*lpCommonMeanFileDialog->pcells)[r][c].str.c_str());
	#else
						sprintf((char *)(*items)[r][c].data(), "%s", 
							(*lpCommonMeanFileDialog-->pcells)[r][c].s);
	#endif

	#endif //HEADER_IN_FIRST_ROW2
					}
				}

				InitListViewColumns(hList, headers, false);


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
        } 
		break;
	case WM_DESTROY:
		{
			if (headers) delete headers;
			if (items) delete items;
		}
    } 
    return FALSE; 
} 


INT_PTR CALLBACK DlgProc3( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	char startDate[15],
		finishDate[15];
	HWND hwndOwner; 
	RECT rc, rcDlg, rcOwner; 
	int y1, y2, m1, m2, d1, d2;
	static CommonMeanFileDialog * lpCommonMeanFileDialog;
	switch( uMsg )
	{
	case WM_NOTIFY:
		switch (((LPNMHDR) lParam)->code)
		{
		case PSN_SETACTIVE:
			{
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
				SendDlgItemMessage( hDlg, IDC_COMBO_TIME_FORMAT, CB_SETCURSEL,
					lpCommonMeanFileDialog->outputTimeFormat,(LPARAM)0 );
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
				lpCommonMeanFileDialog->EnableControls3(hDlg,
					lpCommonMeanFileDialog->cmfd.fileFormat != 2);
				// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
				// SendMessage(hDlg,WM_COMMAND,IDC_INIT_LIST_POLYOTY,0);	
				// Разблокируем кнопку Next
				PropSheet_SetWizButtons(GetParent(hDlg), 
					//PSWIZB_FINISH 
					PSWIZB_NEXT
					/*| PSWIZB_BACK*/);
			}
			break;
		case PSN_WIZNEXT:
		case PSN_WIZFINISH:
			{
				if (lpCommonMeanFileDialog)
				{
					lpCommonMeanFileDialog->oftcd.bUseWholeDirectory = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY));
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
					// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
					if (lpCommonMeanFileDialog->oftcd.bUseWholeDirectory)
					{
						lpCommonMeanFileDialog->UseWholeDirectory(hDlg);
					}
					else
					{
						lpCommonMeanFileDialog->UseTheSelectedFile(hDlg);
					}
				}

			}
			break;
		}
		break;

    case WM_INITDIALOG :
		{
			PROPSHEETPAGE * lppsheetPage = (PROPSHEETPAGE *)lParam;
			lpCommonMeanFileDialog = (CommonMeanFileDialog *)lppsheetPage->lParam;
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			// Get the owner window and dialog box rectangles. 
	 
			if ((hwndOwner = GetParent(GetParent(hDlg))) == NULL) 
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
	 
			SetWindowPos(GetParent(hDlg), 
				HWND_TOP, 
				rcOwner.left + (rc.right / 2), 
				rcOwner.top + 80, 
				0, 0,          // ignores size arguments 
				SWP_NOSIZE); 

			SetDlgItemInt(hDlg, IDC_EDIT_INSTRUMENT_NUMBER,lpCommonMeanFileDialog->cmfd.nPribor,false);
				

			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@						
			SendDlgItemMessage(hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY, BM_SETCHECK, 
				lpCommonMeanFileDialog->oftcd.bUseWholeDirectory ? BST_CHECKED : BST_UNCHECKED, 0);

					
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			InitTimeFormatComboBox(hDlg, IDC_COMBO_TIME_FORMAT);
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
				lpCommonMeanFileDialog->cmfd.delimID,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


			SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)"1 sec" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)"1 min" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)"5 min" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)"15 min" );
			SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_ADDSTRING, 0,
						(LPARAM)(LPCTSTR)"20 min" );
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

			lpCommonMeanFileDialog->cmfd.shPeriodFlagMinStart		= 1;
			lpCommonMeanFileDialog->cmfd.shPeriodFlagMinEnd			= 5;
			lpCommonMeanFileDialog->cmfd.shPeriodFlagHoursStart		= 6;
			lpCommonMeanFileDialog->cmfd.shPeriodFlagHoursEnd		= 13;
			lpCommonMeanFileDialog->cmfd.shPeriodFlagHalfOfDay		= 14;

			// SET COMBO OF PERIOD
			SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_SETCURSEL, 
				lpCommonMeanFileDialog->cmfd.shPeriodFlag,
						(LPARAM)0 );

			// Set min, mean, max check
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_PER_DAY,
				lpCommonMeanFileDialog->cmfd.bMeanPerDay ? BST_CHECKED : BST_UNCHECKED );

			// Set min, mean, max check
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN,
				lpCommonMeanFileDialog->cmfd.bMin ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN,
				lpCommonMeanFileDialog->cmfd.bMean ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP,
				lpCommonMeanFileDialog->cmfd.bDisp ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_ASIM,
				lpCommonMeanFileDialog->cmfd.bAsim ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_EXCESS,
				lpCommonMeanFileDialog->cmfd.bExcess ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN,
				lpCommonMeanFileDialog->cmfd.bMedian ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX,
				lpCommonMeanFileDialog->cmfd.bMax ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN,
				lpCommonMeanFileDialog->cmfd.bPolarization ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN,
				lpCommonMeanFileDialog->cmfd.bInvPolarization ? BST_CHECKED : BST_UNCHECKED );

			 

			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE,
				lpCommonMeanFileDialog->cmfd.bMinAngle ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE,
				lpCommonMeanFileDialog->cmfd.bMedianAngle ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE,
				lpCommonMeanFileDialog->cmfd.bMeanAngle ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE,
				lpCommonMeanFileDialog->cmfd.bDispAngle ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE,
				lpCommonMeanFileDialog->cmfd.bMaxAngle ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE,
				lpCommonMeanFileDialog->cmfd.bPolarizationAngle ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE,
				lpCommonMeanFileDialog->cmfd.bInvPolarizationAngle ? BST_CHECKED : BST_UNCHECKED );



			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bMinAngle3 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bMedianAngle3 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bMeanAngle3 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bDispAngle3 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bMaxAngle3 ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bPolarizationAngle3 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3,
				lpCommonMeanFileDialog->cmfd.bInvPolarizationAngle3 ? BST_CHECKED : BST_UNCHECKED );



			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bMinAngle4 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bMedianAngle4 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bMeanAngle4 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bDispAngle4 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bMaxAngle4 ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bPolarizationAngle4 ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4,
				lpCommonMeanFileDialog->cmfd.bInvPolarizationAngle4 ? BST_CHECKED : BST_UNCHECKED );


			 
			 
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MIN_XYZ,
				lpCommonMeanFileDialog->cmfd.bMinXYZ ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEAN_XYZ,
				lpCommonMeanFileDialog->cmfd.bMeanXYZ ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_DISP_XYZ,
				lpCommonMeanFileDialog->cmfd.bDispXYZ ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_XYZ,
				lpCommonMeanFileDialog->cmfd.bMedianXYZ ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_XYZ,
				lpCommonMeanFileDialog->cmfd.bMaxXYZ ? BST_CHECKED : BST_UNCHECKED );

			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_XYZ,
				lpCommonMeanFileDialog->cmfd.bPolarizationXYZ ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_XYZ,
				lpCommonMeanFileDialog->cmfd.bInvPolarizationXYZ ? BST_CHECKED : BST_UNCHECKED );	 
			 
			 
			 
			 
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_USE_REVERSE_ANGLES,
				lpCommonMeanFileDialog->cmfd.bReverseAngles ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_COMMON_TO_CUT_PAGES_FOR_EXCEL,
				lpCommonMeanFileDialog->cmfd.bToCutPagesExcel ? BST_CHECKED : BST_UNCHECKED );
		}
		break;

    case WM_COMMAND :
         switch( LOWORD( wParam ) )
         {
		 case IDOK:
			 {
				 if (lpCommonMeanFileDialog)
				 {
				 lpCommonMeanFileDialog->oftcd.bUseWholeDirectory = (BST_CHECKED == IsDlgButtonChecked(hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY));
				 // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				 // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				 if (lpCommonMeanFileDialog->oftcd.bUseWholeDirectory)
				 {
					 lpCommonMeanFileDialog->UseWholeDirectory(hDlg);
				 }
				 else
				 {
					 lpCommonMeanFileDialog->UseTheSelectedFile(hDlg);
				 }
				 }
			 }
			 break;
		 case IDC_COMBO_TIME_FORMAT:
			 {
				 lpCommonMeanFileDialog->outputTimeFormat = (short)SendDlgItemMessage( hDlg, 
					 IDC_COMBO_TIME_FORMAT,
					 CB_GETCURSEL,0,(LPARAM)0 );
			 }
			 break;
		 /*case IDC_RADIO_EXCEL_OUTPUT_FORMAT:
			 {
				 lpCommonMeanFileDialog->cmfd.shFormatFlag = 0;
			 }
			 break;
		 case IDC_RADIO_MATLAB_OUTPUT_FORMAT:
			 {
				 lpCommonMeanFileDialog->cmfd.shFormatFlag = 1;
			 }
			 break;
		 case IDC_RADIO_TEZEYVAR_OUTPUT_FORMAT:
			 {
				 lpCommonMeanFileDialog->cmfd.shFormatFlag = 2;
			 }
			 break;*/
 		 case IDC_CHECK_COMMON_USE_MEAN_PER_DAY:
			{
				lpCommonMeanFileDialog->cmfd.bMeanPerDay = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_PER_DAY) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_REVERSE_ANGLES:
			{
				lpCommonMeanFileDialog->cmfd.bReverseAngles = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_REVERSE_ANGLES) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_TO_CUT_PAGES_FOR_EXCEL:
			{
				lpCommonMeanFileDialog->cmfd.bToCutPagesExcel = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_TO_CUT_PAGES_FOR_EXCEL) == BST_CHECKED;
			}
			break;



			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 		 case IDC_CHECK_COMMON_USE_MIN:
			{
				lpCommonMeanFileDialog->cmfd.bMin = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN:
			{
				lpCommonMeanFileDialog->cmfd.bMean = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP:
			{
				lpCommonMeanFileDialog->cmfd.bDisp = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_ASIM:
			{
				lpCommonMeanFileDialog->cmfd.bAsim = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_ASIM) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_EXCESS:
			{
				lpCommonMeanFileDialog->cmfd.bExcess = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_EXCESS) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN:
			{
				lpCommonMeanFileDialog->cmfd.bMedian = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX:
			{
				lpCommonMeanFileDialog->cmfd.bMax = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN:
			{
				lpCommonMeanFileDialog->cmfd.bPolarization = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN:
			{
				lpCommonMeanFileDialog->cmfd.bInvPolarization = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 		 case IDC_CHECK_COMMON_USE_MIN_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bMinAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bMedianAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bMeanAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bDispAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bMaxAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bPolarizationAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_ANGLE:
			{
				lpCommonMeanFileDialog->cmfd.bInvPolarizationAngle = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 		 case IDC_CHECK_COMMON_USE_MIN_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bMinAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bMedianAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bMeanAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bDispAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bMaxAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bPolarizationAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE3) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3:
			{
				lpCommonMeanFileDialog->cmfd.bInvPolarizationAngle3 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE3) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

 		 case IDC_CHECK_COMMON_USE_MIN_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bMinAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bMedianAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bMeanAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bDispAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bMaxAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bPolarizationAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_ANGLE4) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4:
			{
				lpCommonMeanFileDialog->cmfd.bInvPolarizationAngle4 = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_ANGLE4) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
 		 case IDC_CHECK_COMMON_USE_MIN_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bMinXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MIN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEAN_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bMeanXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEAN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_DISP_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bDispXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_DISP_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MEDIAN_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bMedianXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MEDIAN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bMaxXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAX_MIN_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bPolarizationXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAX_MIN_XYZ) == BST_CHECKED;
			}
			break;
 		 case IDC_CHECK_COMMON_USE_MAXMIN_XYZ:
			{
				lpCommonMeanFileDialog->cmfd.bInvPolarizationXYZ = IsDlgButtonChecked( hDlg, IDC_CHECK_COMMON_USE_MAXMIN_XYZ) == BST_CHECKED;
			}
			break;
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

		case IDC_COMBO_DELIMITER:
			{
				switch(SendDlgItemMessage( hDlg, 
					IDC_COMBO_DELIMITER,
					CB_GETCURSEL,0,(LPARAM)0 ))
				{
				case 0:
					lpCommonMeanFileDialog->cmfd.delim = '\t';
					break;
				case 1:
					lpCommonMeanFileDialog->cmfd.delim = ' ';
					break;
				case 2:
					lpCommonMeanFileDialog->cmfd.delim = ',';
					break;
				case 3:
					lpCommonMeanFileDialog->cmfd.delim = ';';
					break;
				}

			}
			break;

          case IDC_COMBO_PERIOD :
			   {
				   long lComboCurSel = SendDlgItemMessage( hDlg, IDC_COMBO_PERIOD, CB_GETCURSEL, 0,
							   (LPARAM)0 );
				   lpCommonMeanFileDialog->cmfd.shPeriodFlag = short(lComboCurSel);
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
					lpCommonMeanFileDialog->cmfd.startYear		= y1;
					lpCommonMeanFileDialog->cmfd.startMonth	= m1;
					lpCommonMeanFileDialog->cmfd.startDay		= d1;
					lpCommonMeanFileDialog->cmfd.finishYear	= y2;
					lpCommonMeanFileDialog->cmfd.finishMonth	= m2;
					lpCommonMeanFileDialog->cmfd.finishDay		= d2;

				   if(lpCommonMeanFileDialog->cmfd.thisIsLocalTime)
				   {
						// 
						BOOL bTranslated;
						lpCommonMeanFileDialog->cmfd.localTimeOffsetHours = 
							(short)GetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, &bTranslated, false);
						if (!bTranslated)
							lpCommonMeanFileDialog->cmfd.localTimeOffsetHours = 0;
				   }

					return 1;
			   }
			   break;
         }
         break;

      default :
         return( FALSE );
  }
  return( TRUE );
}



CommonMeanFileDialog::CommonMeanFileDialog(HWND hwnd)
{
	hWnd = hwnd;

	OnCreate();


	if (OpenFileDlg())
	{

		// Инициализируем страницы блокнота Wizard
		psheetPage[0].dwSize = sizeof(PROPSHEETPAGE);
		psheetPage[0].hInstance = hInst;
		//psheetPage[0].pszIcon = MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE);
		psheetPage[0].dwFlags = PSP_USETITLE | PSP_USEICONID;
		psheetPage[0].pszTemplate = 
			MAKEINTRESOURCE(IDD_DIALOG_SELECT_FILE_DELIMITER);		
		psheetPage[0].pfnDlgProc = DlgProc1;
		psheetPage[0].pszTitle = "Select delimiter";
		psheetPage[0].lParam = (LPARAM)this;

		psheetPage[1].dwSize = sizeof(PROPSHEETPAGE);
		psheetPage[1].hInstance = hInst;
		//psheetPage[1].pszIcon = MAKEINTRESOURCE(IDD_DIALOG_FILE_POLYOTY);
		psheetPage[1].dwFlags = PSP_USETITLE | PSP_USEICONID;
		psheetPage[1].pszTemplate = 
			MAKEINTRESOURCE(IDD_DIALOG_CELL_LIST_PAGE);
		psheetPage[1].pfnDlgProc = DlgProc2;
		psheetPage[1].pszTitle = "Select time format";
		psheetPage[1].lParam = (LPARAM)this;
		
		psheetPage[2].dwSize = sizeof(PROPSHEETPAGE);
		psheetPage[2].hInstance = hInst;
		//      psheetPage[2].pszIcon = MAKEINTRESOURCE(IDI_KEYWORD);
		psheetPage[2].dwFlags = PSP_USETITLE | PSP_USEICONID;
		psheetPage[2].pszTemplate = 
			MAKEINTRESOURCE(IDD_DIALOG_START_FINISH_DATE1);	
		psheetPage[2].pfnDlgProc = DlgProc3;
		psheetPage[2].pszTitle = "Create Common File";
		psheetPage[2].lParam = (LPARAM)this;
		
		// Инициализируем заголовок блокнота Wizard
		psheetHeader.dwSize = sizeof(PROPSHEETHEADER);
		psheetHeader.hInstance = hInst;
		psheetHeader.pszIcon = NULL;
		psheetHeader.dwFlags = PSH_PROPSHEETPAGE | PSH_WIZARD;		
		psheetHeader.hwndParent = hWnd;
		psheetHeader.pszCaption = "Create Common File";
		psheetHeader.nPages = 
			sizeof(psheetPage) / sizeof(PROPSHEETPAGE);
		psheetHeader.ppsp = (LPCPROPSHEETPAGE)&psheetPage;
		
		// Создаем и отображаем блокнот Wizard
		PropertySheet(&psheetHeader);
	}
}

CommonMeanFileDialog::~CommonMeanFileDialog()
{
	if (pcells)					delete pcells;
	if (pnames_of_colomns)		delete pnames_of_colomns;
	if (filename)				delete[] filename;
	if (szBuff)					delete[] szBuff;
	if (szBuff_old)				delete[] szBuff_old;
	if (title)					delete[] title;
}

void CommonMeanFileDialog::createCommonFile()
{
	int global_max_X = 0;
	int global_max_Y = 0;
	int global_max_Z = 0;

	int nPribor = this->cmfd.nPribor;

	SYSTEMTIME global_max_Xt;
	SYSTEMTIME global_max_Yt;
	SYSTEMTIME global_max_Zt;

	char startDate[15],
		finishDate[15];

	char filename_in[1023],
		directory_out[1023],
		filename_out_temp[1023],
		filename_out[1023];

	char szPath_in[1023];

	double test_t,test_t0, pre_wrote_t2 = 0;
	bool bNewStringDone = true;

	wsprintf(startDate, "%d/%02d/%02d\0", this->cmfd.startYear, this->cmfd.startMonth, this->cmfd.startDay);
	wsprintf(finishDate, "%d/%02d/%02d\0", this->cmfd.finishYear, this->cmfd.finishMonth, this->cmfd.finishDay);

	char sPeriod[16], sFormat[16], sFormat2[16], sExt[8];sprintf(sExt, ".txt");
	switch(this->cmfd.shPeriodFlag)
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
			wsprintf(sPeriod,"20 min");
		}
		break;
	case 5:
		{
			wsprintf(sPeriod,"30 min");
		}
		break;
	case 6:
		{
			wsprintf(sPeriod,"1 hours");
		}
		break;
	case 7:
		{
			wsprintf(sPeriod,"2 hours");
		}
		break;
	case 8:
		{
			wsprintf(sPeriod,"3 hours");
		}
		break;
	case 9:
		{
			wsprintf(sPeriod,"4 hours");
		}
		break;
	case 10:
		{
			wsprintf(sPeriod,"6 hours");
		}
		break;
	case 11:
		{
			wsprintf(sPeriod,"8 hours");
		}
		break;
	case 12:
		{
			wsprintf(sPeriod,"12 hours");
		}
		break;
	case 13:
		{
			wsprintf(sPeriod,"24 hours");
		}
		break;
	case 14:
		{
			wsprintf(sPeriod,"2-12 hours");
		}
		break;
	}
	switch(this->outputTimeFormat)
	{
	case 0:
		{
			wsprintf(sFormat,"x");
			wsprintf(sFormat2,"excel");
		}
		break;
	case 1:
		{
			wsprintf(sFormat,"m");
			wsprintf(sFormat2,"matlab");
		}
		break;
	case 2:
		{
			wsprintf(sFormat,"u");
			wsprintf(sFormat2,"unix");
		}
		break;
	case 3:
		{
			wsprintf(sFormat,"db");
			wsprintf(sFormat2,"database");
		}
		break;
	case 4:
		{
			wsprintf(sFormat,"v");
			wsprintf(sFormat2,"tezeyvar");
		}
		break;
	}

	wsprintf(directory_out, "%s\\CommonFiles", directory);

	switch (this->cmfd.nHowUseFilePath )
	{
	case 0:
	case 1:
	case 2:
		{
			wsprintf(filename_out_temp,"%d_c%s%s_%02d_%02d_%02d_%02d_%02d_%02d%s",
				nPribor,
				sFormat,
				sPeriod,
				this->cmfd.startYear-(this->cmfd.startYear/100)*100, this->cmfd.startMonth, this->cmfd.startDay, 
				this->cmfd.finishYear-(this->cmfd.finishYear/100)*100, this->cmfd.finishMonth, this->cmfd.finishDay,
				sExt);
		}
		break;
	}

	CreateDirectory(directory_out,NULL);

	char delim = this->cmfd.delim;

	strcpy(filename_out, directory_out);
	strcat(filename_out, "\\");
	strcat(filename_out, filename_out_temp);

	double dn1 = datenum(this->cmfd.startYear, this->cmfd.startMonth, this->cmfd.startDay, 0, 0, 0, 0);
	double dn2 = datenum(this->cmfd.finishYear, this->cmfd.finishMonth, this->cmfd.finishDay, 0, 0, 0, 0);
	double start_t = dn1, finish_t = dn2;



	int X, Y, Z;
	int jj = 0, // rows on excel file
		kk = 1; // pages on excel file

	double t1, t2;
	long maxWindowLength=131072-1;


	long WindowIndex=0;

	int CurrentMinute,
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
	if(this->cmfd.bMeanPerDay)
	{
		if ((vmeanX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vmeanX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vmeanY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vmeanY - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vmeanZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,SecsPerDay*sizeof(double))) == NULL)
		{
			MessageBox(0, "vmeanZ - Not enough memory",
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

	if(this->cmfd.bMeanPerDay)
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
	double *vmeant = NULL;

	if(this->cmfd.bMeanPerDay)
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

	if(this->cmfd.bMeanPerDay)
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
		MessageBox(0, "vY - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	if ((vZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vZ - Not enough memory",
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


	DWORD nFilterIndex = 0;
	if (SaveFileDlg(hWnd, filename_out, "Text files (*.txt)\0*.txt\0All files \0*.*\0", nFilterIndex) != S_OK)
		return;



	FILE *stream2;
	if ((stream2 = fopen(filename_out,"wt")) == NULL)
	{
		MessageBox(0, filename_out, "Convert Common Cannot open output file.", 
			MB_OK | MB_ICONINFORMATION);
			return;
	}
	// write header
	fprintf(stream2,"time1%ctime2", delim);
	if(this->cmfd.bMin)
	{
		fprintf(stream2,"%cМинимум сигнала X за %s период %d.%d.%d - %d.%d.%d", delim, sPeriod, this->cmfd.startDay,this->cmfd.startMonth,this->cmfd.startYear,this->cmfd.finishDay,this->cmfd.finishMonth,this->cmfd.finishYear);
		fprintf(stream2,"%cМинимум сигнала Y за %s период %d.%d.%d - %d.%d.%d", delim, sPeriod, this->cmfd.startDay,this->cmfd.startMonth,this->cmfd.startYear,this->cmfd.finishDay,this->cmfd.finishMonth,this->cmfd.finishYear);
		fprintf(stream2,"%cМинимум сигнала Z за %s период %d.%d.%d - %d.%d.%d", delim, sPeriod, this->cmfd.startDay,this->cmfd.startMonth,this->cmfd.startYear,this->cmfd.finishDay,this->cmfd.finishMonth,this->cmfd.finishYear);
	}

	if(this->cmfd.bMedian)
	{
		fprintf(stream2,"%cМедиана сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cМедиана сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cМедиана сигнала Z за %s период", delim, sPeriod);
	}

	if(this->cmfd.bMean)
	{
		fprintf(stream2,"%cСредняя сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cСредняя сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cСредняя сигнала Z за %s период", delim, sPeriod);
	}

	if(this->cmfd.bDisp)
	{
		fprintf(stream2,"%cДисперсия сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cДисперсия сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cДисперсия сигнала Z за %s период", delim, sPeriod);
	}

	if(this->cmfd.bAsim)
	{
		fprintf(stream2,"%cАсимметрия сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cАсимметрия сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cАсимметрия сигнала Z за %s период", delim, sPeriod);
	}

	if(this->cmfd.bExcess)
	{
		fprintf(stream2,"%cЭксцесс сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cЭксцесс сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cЭксцесс сигнала Z за %s период", delim, sPeriod);
	}


	if(this->cmfd.bMax)
	{
		fprintf(stream2,"%cМаксимум сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cМаксимум сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cМаксимум сигнала Z за %s период", delim, sPeriod);
	}

	if(this->cmfd.bPolarization)
	{
		fprintf(stream2,"%cСтепень когерентности сигнала X за %s период", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности сигнала Y за %s период", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности сигнала Z за %s период", delim, sPeriod);
	}
	if(this->cmfd.bInvPolarization)
	{
		fprintf(stream2,"%cInvPolarizationX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationY_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationZ_%s", delim, sPeriod);
	}

	if(this->cmfd.bMinAngle)
	{
		fprintf(stream2,"%cМинимум отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMedianAngle)
	{
		fprintf(stream2,"%cМедиана отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMeanAngle)
	{
		fprintf(stream2,"%cСредняя отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMaxAngle)
	{
		fprintf(stream2,"%cМаксимум отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bPolarizationAngle)
	{
		fprintf(stream2,"%cСтепень когерентности отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bInvPolarizationAngle)
	{
		fprintf(stream2,"%cInvPolarizationAngleYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleXY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMinAngle3)
	{
		fprintf(stream2,"%cMinAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMinAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMinAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMedianAngle3)
	{
		fprintf(stream2,"%cMedianAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMedianAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMedianAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMeanAngle3)
	{
		fprintf(stream2,"%cMeanAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMeanAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMeanAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMaxAngle3)
	{
		fprintf(stream2,"%cMaxAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMaxAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMaxAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bPolarizationAngle3)
	{
		fprintf(stream2,"%cPolarizationAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cPolarizationAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cPolarizationAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bInvPolarizationAngle3)
	{
		fprintf(stream2,"%cInvPolarizationAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMinAngle4)
	{
		fprintf(stream2,"%cМинимум отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMedianAngle4)
	{
		fprintf(stream2,"%cМедиана отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMeanAngle4)
	{
		fprintf(stream2,"%cСредняя отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMaxAngle4)
	{
		fprintf(stream2,"%cМаксимум отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bPolarizationAngle4)
	{
		fprintf(stream2,"%cСтепень когерентности отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bInvPolarizationAngle4)
	{
		fprintf(stream2,"%cInvPolarizationAngleX_XYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleY_XYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZ_XYZ_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMinXYZ)
	{
		fprintf(stream2,"Минимум модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bMedianXYZ)
	{
		fprintf(stream2,"%cМедиана модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bMeanXYZ)
	{
		fprintf(stream2,"%cСредняя модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bMaxXYZ)
	{
		fprintf(stream2,"%cМаксимум модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bPolarizationXYZ)
	{
		fprintf(stream2,"%cСтепень когерентности модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bInvPolarizationXYZ)
	{
		fprintf(stream2,"%cInvPolarizationXYZ_%s", delim, sPeriod);
	}


	if (this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay)
	{
		if(this->cmfd.bMin)
		{
			fprintf(stream2,"%cminX2_%s", delim, sPeriod);
			fprintf(stream2,"%cminY2_%s", delim, sPeriod);
			fprintf(stream2,"%cminZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMedian)
		{
			fprintf(stream2,"%cmedianX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmedianY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmedianZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMean)
		{
			fprintf(stream2,"%cmeanX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmeanY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmeanZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bDisp)
		{
			fprintf(stream2,"%cdispX2_%s", delim, sPeriod);
			fprintf(stream2,"%cdispY2_%s", delim, sPeriod);
			fprintf(stream2,"%cdispZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bAsim)
		{
			fprintf(stream2,"%casimX2_%s", delim, sPeriod);
			fprintf(stream2,"%casimY2_%s", delim, sPeriod);
			fprintf(stream2,"%casimZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bExcess)
		{
			fprintf(stream2,"%cexcessX2_%s", delim, sPeriod);
			fprintf(stream2,"%cexcessY2_%s", delim, sPeriod);
			fprintf(stream2,"%cexcessZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMax)
		{
			fprintf(stream2,"%cmaxX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmaxY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmaxZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bPolarization)
		{
			fprintf(stream2,"%cPolarizationX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationY2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bInvPolarization)
		{
			fprintf(stream2,"%cInvPolarizationX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationY2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMinAngle)
		{
			fprintf(stream2,"%cMinAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMedianAngle)
		{
			fprintf(stream2,"%cMedianAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMeanAngle)
		{
			fprintf(stream2,"%cMeanAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMaxAngle)
		{
			fprintf(stream2,"%cMaxAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bPolarizationAngle)
		{
			fprintf(stream2,"%cPolarizationAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bInvPolarizationAngle)
		{
			fprintf(stream2,"%cInvPolarizationAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleYX2_%s", delim, sPeriod);
			}
		}


		if(this->cmfd.bMinAngle3)
		{
			fprintf(stream2,"%cMinAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMedianAngle3)
		{
			fprintf(stream2,"%cMedianAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMeanAngle3)
		{
			fprintf(stream2,"%cMeanAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMeanAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMaxAngle3)
		{
			fprintf(stream2,"%cMaxAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bPolarizationAngle3)
		{
			fprintf(stream2,"%cPolarizationAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bInvPolarizationAngle3)
		{
			fprintf(stream2,"%cInvPolarizationAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXY_Z2_%s", delim, sPeriod);
			}
		}


		if(this->cmfd.bMinAngle4)
		{
			fprintf(stream2,"%cMinAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMedianAngle4)
		{
			fprintf(stream2,"%cMedianAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMeanAngle4)
		{
			fprintf(stream2,"%cMeanAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMeanAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMaxAngle4)
		{
			fprintf(stream2,"%cMaxAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bPolarizationAngle4)
		{
			fprintf(stream2,"%cPolarizationAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}
		if(this->cmfd.bInvPolarizationAngle4)
		{
			fprintf(stream2,"%cInvPolarizationAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}
		if(this->cmfd.bMinXYZ)
		{
			fprintf(stream2,"%cminXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bMedianXYZ)
		{
			fprintf(stream2,"%cmedianXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bMeanXYZ)
		{
			fprintf(stream2,"%cmeanXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bMaxXYZ)
		{
			fprintf(stream2,"%cmaxXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bPolarizationXYZ)
		{
			fprintf(stream2,"%cPolarizationXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bInvPolarizationXYZ)
		{
			fprintf(stream2,"%cInvPolarizationXYZ2_%s", delim, sPeriod);
		}
	}

	fprintf(stream2,"\n");


	fclose(stream2);

	int iFile = 0;
	int iFile2 = 0;

	switch (this->cmfd.nHowUseFilePath )
	{
	case 0:// filenames as drozdov filenme formate which include date inteval
		{
		}
		break;
	case 1:// the selected file
		{
			dn2 = dn1;
		}
		break;
	case 2:// all files in th directory
		{
			dn1 = 0;
			dn2 = this->cmfd.nFilesInDirectory-1;
		}
		break;
	}

    RECT rcClient;  // Client area of parent window 
    int cyVScroll;  // Height of scroll bar arrow 
    HWND hwndPB;    // Handle of progress bar  

    // Ensure that the common control DLL is loaded
    // and create a progress bar along the bottom of
    // the client area of the parent window. 
    // Base the height of the progress bar on the
    // height of a scroll bar arrow. 
    InitCommonControls(); 
    GetClientRect(this->cmfd.hwndParent, &rcClient); 
    cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
    hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
	         (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
             0, 0,
             //rcClient.left, rcClient.bottom,
             rcClient.right, cyVScroll, 
             this->cmfd.hwndParent, (HMENU) 0, hInst, NULL); 

    // Set the range and increment of the progress
    // bar. 

    SendMessage(hwndPB, PBM_SETRANGE, 0,
                MAKELPARAM(0, int(dn2-dn1))); 
    SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 

	unsigned int i2 = 0;
	bool start = true;

	for (double dn=dn1; dn<=dn2; dn+=1.0)
	{
		iFile++;
		int y, mo, d, h, mi, s, milli;

		bool toRead = true;
		
		switch (this->cmfd.nHowUseFilePath )
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
				strcpy(szPath_in, szFile);
			}
			break;
		case 2:
			{
				sprintf(szPath_in, "%s\\%s\0", 
					directory, this->cmfd.vFileNames[int(dn)]);
			}
			break;
		}

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
		
		if (toRead)
		{
			//////////////////////////////////////
			double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

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
					int _y;
					int rez = EOF;
					int rezWaited = EOF;

					switch (this->cmfd.fileFormat)
					{
					case 0:
						{
							rez = sscanf(szBuff,"%lf\t%d\t%d\t%d\t%d",
								&t_excel, &X, &Y, &Z);
							rezWaited = 4;
							if(this->cmfd.thisIsLocalTime)
								 t_excel -= 
								 double(this->cmfd.localTimeOffsetHours) / 24.0;

							datevec(t_excel+t0_excel,y,mo,d,h,mi,s,milli);
						}
						break;
					case 1:
						{
							rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
								&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
							rezWaited = 10;
							if (rez != rezWaited)
							{
								rez = sscanf(szBuff,"%d:%d:%d,%d:%d:%d,%d,%d,%d,%d",
									&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
							}


							if (this->cmfd.nHowUseFilePath == 1)
								y = _y+ (y/100)*100;
							if (this->cmfd.nHowUseFilePath == 2)
								y = _y + 2000;
						}
						break;
					}					
					if (rez == rezWaited && rez != EOF)
					{
						if (start) // (i==0 && iFile==1)
						{
							start = false;
							switch (this->cmfd.fileFormat)
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
							switch (this->cmfd.fileFormat)
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
								sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд\n\nПропустить или завершить процесс?", szBuff, szPath_in, int((test_t0 - test_t)*3600.*24.));
								if (MessageBox(0, errstr, "createCommonFile", 
									MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
								{
									break;
									//fclose(stream2);
									//return;
								}							
							}
						}
						if (test_t0 >= start_t && test_t0 < finish_t+1.0)
						{
						if(this->cmfd.bMeanPerDay)
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
						switch(this->cmfd.shPeriodFlag)
						{
						case 0:mean_min=0; break;
						case 1:mean_min=1; break;
						case 2:mean_min=5; break;
						case 3:mean_min=15;break;
						case 4:mean_min=20;break;
						case 5:mean_min=30;break;
						}
						switch(this->cmfd.shPeriodFlag)
						{
						case 6:mean_hour=1; break;
						case 7:mean_hour=2; break;
						case 8:mean_hour=3; break;
						case 9:mean_hour=4; break;
						case 10:mean_hour=6; break;
						case 11:mean_hour=8; break;
						case 12:mean_hour=12; break;
						case 13:mean_hour=24; break;
						case 14:mean_hour=12; break;
						}
						switch(this->cmfd.shPeriodFlag)
						{
						case 0:// 1 sec - without any meaning
							{	
								///////////////////////////////////////////////////
								t2 = datenum(y, mo, d, h, mi, s, milli);
								printTimeString(stream2, this->outputTimeFormat, t2);
								///////////////////////////////////////////////////
								fprintf(stream2,"%c%d%c%d%c%d\n", delim, 
									X, delim, Y, delim, Z);
								///////////////////////////////////////////////////
								
								// cutting of file
								this->cutting_of_output_file(stream2,
									jj,kk,
									directory_out,filename_out,
									filename_out_temp,nPribor,sFormat,sPeriod,sExt);
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
						case 14:
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
									if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagMinStart 
										&& this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagMinEnd)
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
										if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagHoursStart && 
											this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagHalfOfDay)
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
										
										
										//double meanX2, meanY2, meanZ2;
										double meanX, meanY, meanZ;
										double meanXX, meanYY, meanZZ;
										double meanXXX, meanYYY, meanZZZ;
										double meanXXXX, meanYYYY, meanZZZZ;
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

										meanX=0; meanY=0; meanZ=0;
										meanXX=0; meanYY=0; meanZZ=0;
										meanXXX=0; meanYYY=0; meanZZZ=0;
										meanXXXX=0; meanYYYY=0; meanZZZZ=0;

										for (int j=0;j<=WindowIndex;j++)
										{
											if(this->cmfd.bMin || this->cmfd.bMax)
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

											if(this->cmfd.bMean || this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
											{
												meanX += vX[j];
												meanY += vY[j];
												meanZ += vZ[j];
											}

											if(this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
											{
												meanXX += vX[j]*vX[j];
												meanYY += vY[j]*vY[j];
												meanZZ += vZ[j]*vZ[j];
											}

											if(this->cmfd.bAsim || this->cmfd.bExcess)
											{
												meanXXX += vX[j]*vX[j]*vX[j];
												meanYYY += vY[j]*vY[j]*vY[j];
												meanZZZ += vZ[j]*vZ[j]*vZ[j];
											}

											if(this->cmfd.bExcess)
											{
												meanXXXX += vX[j]*vX[j]*vX[j]*vX[j];
												meanYYYY += vY[j]*vY[j]*vY[j]*vY[j];
												meanZZZZ += vZ[j]*vZ[j]*vZ[j]*vZ[j];
											}

											if(this->cmfd.bMinAngle || this->cmfd.bMedianAngle 
												|| this->cmfd.bMeanAngle || this->cmfd.bMaxAngle )
											{
												vYZ[j] = 180.*atan2(vY[j], vZ[j])/PI;
												vZX[j] = 180.*atan2(vZ[j], vX[j])/PI;
												vXY[j] = 180.*atan2(vX[j], vY[j])/PI;
											}
											if(this->cmfd.bMinAngle || this->cmfd.bMaxAngle)
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

											if(this->cmfd.bMeanAngle)
											{										
												meanAngleYZ += vYZ[j];
												meanAngleZX += vZX[j];
												meanAngleXY += vXY[j];
											}
											if(this->cmfd.bMinAngle3 || this->cmfd.bMaxAngle3 
												|| this->cmfd.bMeanAngle3 || this->cmfd.bMedianAngle3 )
											{
												vX_YZ[j] = 180.*atan2(vX[j], sqrt(pow(vY[j], 2.0) + pow(vZ[j], 2.0)) )/PI;
												vY_ZX[j] = 180.*atan2(vY[j], sqrt(pow(vZ[j], 2.0) + pow(vX[j], 2.0)) )/PI;
												vZ_XY[j] = 180.*atan2(vZ[j], sqrt(pow(vX[j], 2.0) + pow(vY[j], 2.0)) )/PI;
											}
											if(this->cmfd.bMinAngle3 || this->cmfd.bMaxAngle3)
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
											if(this->cmfd.bMinAngle4 || this->cmfd.bMaxAngle4 
												|| this->cmfd.bMeanAngle4 || this->cmfd.bMedianAngle4 
												|| this->cmfd.bMinXYZ || this->cmfd.bMedianXYZ 
												|| this->cmfd.bMeanXYZ || this->cmfd.bMaxXYZ)
											{
												vXYZ[j] = sqrt(pow(vX[j], 2.0) + pow(vY[j], 2.0) + pow(vZ[j], 2.0));
											}
											if(this->cmfd.bMinAngle4 || this->cmfd.bMaxAngle4 
												|| this->cmfd.bMeanAngle4 || this->cmfd.bMedianAngle4 )
											{
												vX_XYZ[j] = 180.*atan2(vX[j], vXYZ[j] )/PI;
												vY_XYZ[j] = 180.*atan2(vY[j], vXYZ[j] )/PI;
												vZ_XYZ[j] = 180.*atan2(vZ[j], vXYZ[j] )/PI;
											}
											if(this->cmfd.bMinAngle4 || this->cmfd.bMaxAngle4)
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
											if(this->cmfd.bMinXYZ || this->cmfd.bMaxXYZ)
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
											if(this->cmfd.bMeanAngle3)
											{
												meanAngleX_YZ += vX_YZ[j];
												meanAngleY_ZX += vY_ZX[j];
												meanAngleZ_XY += vZ_XY[j];
											}
											if(this->cmfd.bMeanXYZ)
											{
												meanXYZ += vXYZ[j];
											}
											if(this->cmfd.bMeanAngle4)
											{
												meanAngleX_XYZ += vX_XYZ[j];
												meanAngleY_XYZ += vY_XYZ[j];
												meanAngleZ_XYZ += vZ_XYZ[j];
											}

										}
										if(this->cmfd.bMeanXYZ)
										{
											meanXYZ /= WindowIndex+1;
										}

										if(this->cmfd.bMean || this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
										{
											meanX /= WindowIndex+1;
											meanY /= WindowIndex+1;
											meanZ /= WindowIndex+1;
										}

										if(this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
										{
											meanXX /= WindowIndex+1;
											meanYY /= WindowIndex+1;
											meanZZ /= WindowIndex+1;
										}

										if(this->cmfd.bAsim || this->cmfd.bExcess)
										{
											meanXXX /= WindowIndex+1;
											meanYYY /= WindowIndex+1;
											meanZZZ /= WindowIndex+1;
										}

										if(this->cmfd.bExcess)
										{
											meanXXXX /= WindowIndex+1;
											meanYYYY /= WindowIndex+1;
											meanZZZZ /= WindowIndex+1;
										}

										if(this->cmfd.bMinAngle)
										{										
											if(this->cmfd.bReverseAngles)
											{
												minAngleZY = 90.- minAngleYZ;
												minAngleXZ = 90.- minAngleZX;
												minAngleYX = 90.- minAngleXY;
											}
										}
										if(this->cmfd.bMaxAngle)
										{										
											if(this->cmfd.bReverseAngles)
											{
												maxAngleZY = 90.- maxAngleYZ;
												maxAngleXZ = 90.- maxAngleZX;
												maxAngleYX = 90.- maxAngleXY;
											}
										}

										if(this->cmfd.bMeanAngle)
										{										
											meanAngleYZ /= WindowIndex+1;
											meanAngleZX /= WindowIndex+1;
											meanAngleXY /= WindowIndex+1;

											if(this->cmfd.bReverseAngles)
											{
												meanAngleZY = 90.- meanAngleYZ;
												meanAngleXZ = 90.- meanAngleZX;
												meanAngleYX = 90.- meanAngleXY;
											}
										}
										if(this->cmfd.bMinAngle3)
										{
											if(this->cmfd.bReverseAngles)
											{
												minAngleYZ_X = 90.- minAngleX_YZ;
												minAngleZX_Y = 90.- minAngleY_ZX;
												minAngleXY_Z = 90.- minAngleZ_XY;
											}
										}
										if(this->cmfd.bMaxAngle3)
										{
											if(this->cmfd.bReverseAngles)
											{
												maxAngleYZ_X = 90.- maxAngleX_YZ;
												maxAngleZX_Y = 90.- maxAngleY_ZX;
												maxAngleXY_Z = 90.- maxAngleZ_XY;
											}
										}
										if(this->cmfd.bMeanAngle3)
										{
											meanAngleX_YZ /= WindowIndex+1;
											meanAngleY_ZX /= WindowIndex+1;
											meanAngleZ_XY /= WindowIndex+1;

											if(this->cmfd.bReverseAngles)
											{
												meanAngleYZ_X = 90.- meanAngleX_YZ;
												meanAngleZX_Y = 90.- meanAngleY_ZX;
												meanAngleXY_Z = 90.- meanAngleZ_XY;
											}
										}
										if(this->cmfd.bMinAngle4)
										{
											if(this->cmfd.bReverseAngles)
											{
												minAngleXYZ_X = 90.- minAngleX_XYZ;
												minAngleXYZ_Y = 90.- minAngleY_XYZ;
												minAngleXYZ_Z = 90.- minAngleZ_XYZ;
											}
										}
										if(this->cmfd.bMaxAngle4)
										{
											if(this->cmfd.bReverseAngles)
											{
												maxAngleXYZ_X = 90.- maxAngleX_XYZ;
												maxAngleXYZ_Y = 90.- maxAngleY_XYZ;
												maxAngleXYZ_Z = 90.- maxAngleZ_XYZ;
											}
										}
										if(this->cmfd.bMeanAngle4)
										{
											meanAngleX_XYZ /= WindowIndex+1;
											meanAngleY_XYZ /= WindowIndex+1;
											meanAngleZ_XYZ /= WindowIndex+1;

											if(this->cmfd.bReverseAngles)
											{
												meanAngleXYZ_X = 90.- meanAngleX_XYZ;
												meanAngleXYZ_Y = 90.- meanAngleY_XYZ;
												meanAngleXYZ_Z = 90.- meanAngleZ_XYZ;
											}
										}
										if(this->cmfd.bMedian)
										{
											medianX = Median(vX, WindowIndex+1);
											medianY = Median(vY, WindowIndex+1);
											medianZ = Median(vZ, WindowIndex+1);
										}
										if(this->cmfd.bMedianXYZ)
										{
											medianXYZ = Median(vXYZ, WindowIndex+1);
										}
										if(this->cmfd.bMedianAngle)
										{
											MedianAngleYZ = Median(vYZ, WindowIndex+1);
											MedianAngleZX = Median(vZX, WindowIndex+1);
											MedianAngleXY = Median(vXY, WindowIndex+1);

											if(this->cmfd.bReverseAngles)
											{
												MedianAngleZY = 90.- MedianAngleYZ;
												MedianAngleXZ = 90.- MedianAngleZX;
												MedianAngleYX = 90.- MedianAngleXY;
											}
										}
										if(this->cmfd.bMedianAngle3)
										{
											MedianAngleX_YZ = Median(vX_YZ, WindowIndex+1);
											MedianAngleY_ZX = Median(vY_ZX, WindowIndex+1);
											MedianAngleZ_XY = Median(vZ_XY, WindowIndex+1);

											if(this->cmfd.bReverseAngles)
											{
												MedianAngleYZ_X = 90.- MedianAngleX_YZ;
												MedianAngleZX_Y = 90.- MedianAngleY_ZX;
												MedianAngleXY_Z = 90.- MedianAngleZ_XY;
											}
										}
										if(this->cmfd.bMedianAngle4)
										{
											MedianAngleX_XYZ = Median(vX_XYZ, WindowIndex+1);
											MedianAngleY_XYZ = Median(vY_XYZ, WindowIndex+1);
											MedianAngleZ_XYZ = Median(vZ_XYZ, WindowIndex+1);

											if(this->cmfd.bReverseAngles)
											{
												MedianAngleXYZ_X = 90.- MedianAngleX_XYZ;
												MedianAngleXYZ_Y = 90.- MedianAngleY_XYZ;
												MedianAngleXYZ_Z = 90.- MedianAngleZ_XYZ;
											}
										}
										///////////////////////////////////////////////////
										//if (this->cmfd.shFormatFlag !=2)// excel or matlab format
										{
											///////////////////////////////////////////////////
											if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagMinStart 
												&& this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagMinEnd)
											{
												t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, CurrentHour, CurrentMinute, 0, 0);
												t2 = datenum(y, mo, d, h, mi, 0, 0);
											}
											else
											{
												if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagHoursStart 
												&& this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagHoursEnd)
												{
													t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, CurrentHour, 0, 0, 0);
													t2 = t1 + double(mean_hour)/double(24);
												}
												else
												{
													if(this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay )
													{
														t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, 0, 0, 0, 0);
														t2 = t1 + 1.0;
													}
												}
											}


											//if (this->cmfd.shFormatFlag == 0)// excel format
											{
												// cutting of file
												this->cutting_of_output_file(stream2,
													jj,kk,
													directory_out,filename_out,
													filename_out_temp,nPribor,sFormat,sPeriod,sExt);

												bool toWriteDate = pre_wrote_t2 != t2;
												///////////////////////////////////////////////////
												if(this->cmfd.shPeriodFlag != this->cmfd.shPeriodFlagHalfOfDay || 
													(this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay && toWriteDate))
												{
													if (bNewStringDone)
													{
														//fprintf(stream2,"%.8f%c%.8f", t1,delim,t2);
													}
													else 
													{
														//fprintf(stream2,"\n%.8f%c%.8f", t1,delim,t2);
														fprintf(stream2,"\n");
													}
													printTimeString(stream2, this->outputTimeFormat, t1);
													fprintf(stream2,"%c", delim);
													printTimeString(stream2, this->outputTimeFormat, t2);
													pre_wrote_t2 = t2;
												}

												// если до полудня нет данных, пишем дату и заполнем пробелами												
												if (this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay && CurrentHour >= 24 - mean_hour && toWriteDate)
												{
													///////////////////////////////////////////////////
													if(this->cmfd.bMin)
													{
														fprintf(stream2,"%c ", delim, int(minX));
														fprintf(stream2,"%c ", delim, int(minY));
														fprintf(stream2,"%c ", delim, int(minZ));
													}

													if(this->cmfd.bMedian)
													{
														fprintf(stream2,"%c ", delim, medianX);
														fprintf(stream2,"%c ", delim, medianY);
														fprintf(stream2,"%c ", delim, medianZ);
													}

													if(this->cmfd.bMean)
													{
														fprintf(stream2,"%c ", delim, meanX);
														fprintf(stream2,"%c ", delim, meanY);
														fprintf(stream2,"%c ", delim, meanZ);
													}

													if(this->cmfd.bDisp)
													{
														fprintf(stream2,"%c ", delim);
														fprintf(stream2,"%c ", delim);
														fprintf(stream2,"%c ", delim);
													}

													if(this->cmfd.bAsim)
													{
														fprintf(stream2,"%c ", delim);
														fprintf(stream2,"%c ", delim);
														fprintf(stream2,"%c ", delim);
													}

													if(this->cmfd.bExcess)
													{
														fprintf(stream2,"%c ", delim);
														fprintf(stream2,"%c ", delim);
														fprintf(stream2,"%c ", delim);
													}

													if(this->cmfd.bMax)
													{
														fprintf(stream2,"%c ", delim, int(maxX));
														fprintf(stream2,"%c ", delim, int(maxY));
														fprintf(stream2,"%c ", delim, int(maxZ));
													}

													if(this->cmfd.bPolarization)
													{
														fprintf(stream2,"%c ", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
														fprintf(stream2,"%c ", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
														fprintf(stream2,"%c ", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);
													}

													if(this->cmfd.bInvPolarization)
													{
														fprintf(stream2,"%c ", delim, maxX+minX > 0.0 ? (maxX-minX)/(maxX+minX) : 0.);
														fprintf(stream2,"%c ", delim, maxY+minY > 0.0 ? (maxY-minY)/(maxY+minY) : 0.);
														fprintf(stream2,"%c ", delim, maxZ+minZ > 0.0 ? (maxZ-minZ)/(maxZ+minZ) : 0.);
													}

													if(this->cmfd.bMinAngle)
													{
														fprintf(stream2,"%c", delim, minAngleYZ);
														fprintf(stream2,"%c", delim, minAngleZX);
														fprintf(stream2,"%c", delim, minAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, minAngleZY);
															fprintf(stream2,"%c", delim, minAngleXZ);
															fprintf(stream2,"%c", delim, minAngleYX);
														}
													}
																								

													if(this->cmfd.bMedianAngle)
													{
														fprintf(stream2,"%c", delim, MedianAngleYZ);
														fprintf(stream2,"%c", delim, MedianAngleZX);
														fprintf(stream2,"%c", delim, MedianAngleXY);
																								
														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, MedianAngleZY);
															fprintf(stream2,"%c", delim, MedianAngleXZ);
															fprintf(stream2,"%c", delim, MedianAngleYX);
														}
													}

													
													if(this->cmfd.bMeanAngle)
													{
														fprintf(stream2,"%c", delim, meanAngleYZ);
														fprintf(stream2,"%c", delim, meanAngleZX);
														fprintf(stream2,"%c", delim, meanAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, meanAngleZY);
															fprintf(stream2,"%c", delim, meanAngleXZ);
															fprintf(stream2,"%c", delim, meanAngleYX);
														}
													}
			
													if(this->cmfd.bMaxAngle)
													{
														fprintf(stream2,"%c", delim, maxAngleYZ);
														fprintf(stream2,"%c", delim, maxAngleZX);
														fprintf(stream2,"%c", delim, maxAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleZY);
															fprintf(stream2,"%c", delim, maxAngleXZ);
															fprintf(stream2,"%c", delim, maxAngleYX);
														}
													}
													
													if(this->cmfd.bPolarizationAngle)
													{
														fprintf(stream2,"%c", delim, maxAngleYZ-minAngleYZ > 0.0 ? 0.5*(maxAngleYZ+minAngleYZ)/(maxAngleYZ-minAngleYZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleZX-minAngleZX > 0.0 ? 0.5*(maxAngleZX+minAngleZX)/(maxAngleZX-minAngleZX) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleXY-minAngleXY > 0.0 ? 0.5*(maxAngleXY+minAngleXY)/(maxAngleXY-minAngleXY) : 0.5);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleZY-minAngleZY > 0.0 ? 0.5*(maxAngleZY+minAngleZY)/(maxAngleZY-minAngleZY) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXZ-minAngleXZ > 0.0 ? 0.5*(maxAngleXZ+minAngleXZ)/(maxAngleXZ-minAngleXZ) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleYX-minAngleYX > 0.0 ? 0.5*(maxAngleYX+minAngleYX)/(maxAngleYX-minAngleYX) : 0.5);
														}	
													}
			

													if(this->cmfd.bInvPolarizationAngle)
													{
														fprintf(stream2,"%c", delim, maxAngleYZ+minAngleYZ > 0.0 ? (maxAngleYZ-minAngleYZ)/(maxAngleYZ+minAngleYZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleZX+minAngleZX > 0.0 ? (maxAngleZX-minAngleZX)/(maxAngleZX+minAngleZX) : 0.);
														fprintf(stream2,"%c", delim, maxAngleXY+minAngleXY > 0.0 ? (maxAngleXY-minAngleXY)/(maxAngleXY+minAngleXY) : 0.);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleZY+minAngleZY > 0.0 ? (maxAngleZY-minAngleZY)/(maxAngleZY+minAngleZY) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXZ+minAngleXZ > 0.0 ? (maxAngleXZ-minAngleXZ)/(maxAngleXZ+minAngleXZ) : 0.);
															fprintf(stream2,"%c", delim, maxAngleYX+minAngleYX > 0.0 ? (maxAngleYX-minAngleYX)/(maxAngleYX+minAngleYX) : 0.);
														}	
													}
			

													if(this->cmfd.bMinAngle3)
													{
														fprintf(stream2,"%c", delim, minAngleX_YZ);
														fprintf(stream2,"%c", delim, minAngleY_ZX);
														fprintf(stream2,"%c", delim, minAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, minAngleYZ_X);
															fprintf(stream2,"%c", delim, minAngleZX_Y);
															fprintf(stream2,"%c", delim, minAngleXY_Z);
														}
													}

													if(this->cmfd.bMedianAngle3)
													{
														fprintf(stream2,"%c", delim, MedianAngleX_YZ);
														fprintf(stream2,"%c", delim, MedianAngleY_ZX);
														fprintf(stream2,"%c", delim, MedianAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, MedianAngleYZ_X);
															fprintf(stream2,"%c", delim, MedianAngleZX_Y);
															fprintf(stream2,"%c", delim, MedianAngleXY_Z);
														}
													}

													
													if(this->cmfd.bMeanAngle3)
													{
														fprintf(stream2,"%c", delim, meanAngleX_YZ);
														fprintf(stream2,"%c", delim, meanAngleY_ZX);
														fprintf(stream2,"%c", delim, meanAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, meanAngleYZ_X);
															fprintf(stream2,"%c", delim, meanAngleZX_Y);
															fprintf(stream2,"%c", delim, meanAngleXY_Z);
														}
													}

													if(this->cmfd.bMaxAngle3)
													{
														fprintf(stream2,"%c", delim, maxAngleX_YZ);
														fprintf(stream2,"%c", delim, maxAngleY_ZX);
														fprintf(stream2,"%c", delim, maxAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleYZ_X);
															fprintf(stream2,"%c", delim, maxAngleZX_Y);
															fprintf(stream2,"%c", delim, maxAngleXY_Z);
														}
													}
													
													if(this->cmfd.bPolarizationAngle3)
													{
														fprintf(stream2,"%c", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
														}
													}													
			

													if(this->cmfd.bInvPolarizationAngle3)
													{
														fprintf(stream2,"%c", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
														fprintf(stream2,"%c", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
															fprintf(stream2,"%c", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
														}
													}													
			

													if(this->cmfd.bMinAngle4)
													{
														fprintf(stream2,"%c", delim, minAngleX_XYZ);
														fprintf(stream2,"%c", delim, minAngleY_XYZ);
														fprintf(stream2,"%c", delim, minAngleZ_XYZ);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, minAngleXYZ_X);
															fprintf(stream2,"%c", delim, minAngleXYZ_Y);
															fprintf(stream2,"%c", delim, minAngleXYZ_Z);
														}
													}

													if(this->cmfd.bMedianAngle4)
													{
														fprintf(stream2,"%c", delim, MedianAngleX_XYZ);
														fprintf(stream2,"%c", delim, MedianAngleY_XYZ);
														fprintf(stream2,"%c", delim, MedianAngleZ_XYZ);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, MedianAngleXYZ_X);
															fprintf(stream2,"%c", delim, MedianAngleXYZ_Y);
															fprintf(stream2,"%c", delim, MedianAngleXYZ_Z);
														}
													}

													
													if(this->cmfd.bMeanAngle4)
													{
														fprintf(stream2,"%c", delim, meanAngleX_XYZ);
														fprintf(stream2,"%c", delim, meanAngleY_XYZ);
														fprintf(stream2,"%c", delim, meanAngleZ_XYZ);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, meanAngleXYZ_X);
															fprintf(stream2,"%c", delim, meanAngleXYZ_Y);
															fprintf(stream2,"%c", delim, meanAngleXYZ_Z);
														}
													}

													if(this->cmfd.bMaxAngle4)
													{
														fprintf(stream2,"%c", delim, maxAngleX_XYZ);
														fprintf(stream2,"%c", delim, maxAngleY_XYZ);
														fprintf(stream2,"%c", delim, maxAngleZ_XYZ);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleXYZ_X);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Y);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Z);
														}
													}
													
													if(this->cmfd.bPolarizationAngle4)
													{
														fprintf(stream2,"%c", delim, maxAngleX_XYZ-minAngleX_XYZ > 0.0 ? 0.5*(maxAngleX_XYZ+minAngleX_XYZ)/(maxAngleX_XYZ-minAngleX_XYZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleY_XYZ-minAngleY_XYZ > 0.0 ? 0.5*(maxAngleY_XYZ+minAngleY_XYZ)/(maxAngleY_XYZ-minAngleY_XYZ) : 0.5);
														fprintf(stream2,"%c", delim, maxAngleZ_XYZ-minAngleZ_XYZ > 0.0 ? 0.5*(maxAngleZ_XYZ+minAngleZ_XYZ)/(maxAngleZ_XYZ-minAngleZ_XYZ) : 0.5);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleXYZ_X-minAngleXYZ_X > 0.0 ? 0.5*(maxAngleXYZ_X+minAngleXYZ_X)/(maxAngleXYZ_X-minAngleXYZ_X) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Y-minAngleXYZ_Y > 0.0 ? 0.5*(maxAngleXYZ_Y+minAngleXYZ_Y)/(maxAngleXYZ_Y-minAngleXYZ_Y) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Z-minAngleXYZ_Z > 0.0 ? 0.5*(maxAngleXYZ_Z+minAngleXYZ_Z)/(maxAngleXYZ_Z-minAngleXYZ_Z) : 0.5);
														}
													}													
			
													if(this->cmfd.bInvPolarizationAngle4)
													{
														fprintf(stream2,"%c", delim, maxAngleX_XYZ+minAngleX_XYZ > 0.0 ? (maxAngleX_XYZ-minAngleX_XYZ)/(maxAngleX_XYZ+minAngleX_XYZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleY_XYZ+minAngleY_XYZ > 0.0 ? (maxAngleY_XYZ-minAngleY_XYZ)/(maxAngleY_XYZ+minAngleY_XYZ) : 0.);
														fprintf(stream2,"%c", delim, maxAngleZ_XYZ+minAngleZ_XYZ > 0.0 ? (maxAngleZ_XYZ-minAngleZ_XYZ)/(maxAngleZ_XYZ+minAngleZ_XYZ) : 0.);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c", delim, maxAngleXYZ_X+minAngleXYZ_X > 0.0 ? (maxAngleXYZ_X-minAngleXYZ_X)/(maxAngleXYZ_X+minAngleXYZ_X) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Y+minAngleXYZ_Y > 0.0 ? (maxAngleXYZ_Y-minAngleXYZ_Y)/(maxAngleXYZ_Y+minAngleXYZ_Y) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXYZ_Z+minAngleXYZ_Z > 0.0 ? (maxAngleXYZ_Z-minAngleXYZ_Z)/(maxAngleXYZ_Z+minAngleXYZ_Z) : 0.);
														}
													}
													
													if(this->cmfd.bMinXYZ)
													{
														fprintf(stream2,"%c ", delim, int(minXYZ));
													}

													if(this->cmfd.bMedianXYZ)
													{
														fprintf(stream2,"%c ", delim, medianXYZ);
													}

													if(this->cmfd.bMeanXYZ)
													{
														fprintf(stream2,"%c ", delim, meanXYZ);
													}

													if(this->cmfd.bMaxXYZ)
													{
														fprintf(stream2,"%c ", delim, int(maxXYZ));
													}

													if(this->cmfd.bPolarizationXYZ)
													{
														fprintf(stream2,"%c ", delim, maxXYZ-minXYZ > 0.0 ? 0.5*(maxXYZ+minXYZ)/(maxXYZ-minXYZ) : 0.5);
													}

													if(this->cmfd.bInvPolarizationXYZ)
													{
														fprintf(stream2,"%c ", delim, maxXYZ+minXYZ > 0.0 ? (maxXYZ-minXYZ)/(maxXYZ+minXYZ) : 0.);
													}

			

													///////////////////////////////////////////////////
												}
												///////////////////////////////////////////////////
												if(this->cmfd.bMin)
												{
													fprintf(stream2,"%c%d", delim, int(minX));
													fprintf(stream2,"%c%d", delim, int(minY));
													fprintf(stream2,"%c%d", delim, int(minZ));
												}

												if(this->cmfd.bMedian)
												{
													fprintf(stream2,"%c%f", delim, medianX);
													fprintf(stream2,"%c%f", delim, medianY);
													fprintf(stream2,"%c%f", delim, medianZ);
												}

												if(this->cmfd.bMean)
												{
													fprintf(stream2,"%c%f", delim, meanX);
													fprintf(stream2,"%c%f", delim, meanY);
													fprintf(stream2,"%c%f", delim, meanZ);
												}

												double mju2_X;//центральный момент второго порядка
												double mju2_Y;//центральный момент второго порядка
												double mju2_Z;//центральный момент второго порядка

												double mju3_X;//центральный момент 3-го порядка
												double mju3_Y;//центральный момент 3-го порядка
												double mju3_Z;//центральный момент 3-го порядка

												double mju4_X;//центральный момент 4-го порядка
												double mju4_Y;//центральный момент 4-го порядка
												double mju4_Z;//центральный момент 4-го порядка

												if (this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
												{
													mju2_X = meanXX - meanX*meanX;
													mju2_Y = meanYY - meanY*meanY;
													mju2_Z = meanZZ - meanZ*meanZ;
												}

												if (this->cmfd.bAsim)
												{
													mju3_X = meanXXX - 3.0*meanXX*meanX + 2.0*meanX*meanX*meanX;
													mju3_Y = meanYYY - 3.0*meanYY*meanY + 2.0*meanY*meanY*meanY;
													mju3_Z = meanZZZ - 3.0*meanZZ*meanZ + 2.0*meanZ*meanZ*meanZ;
												}

												if (this->cmfd.bExcess)
												{
													mju4_X = meanXXXX - 4.0*meanXXX*meanX + 6.0*meanXX*meanX*meanX - 3.0*meanX*meanX*meanX*meanX;
													mju4_Y = meanYYYY - 4.0*meanYYY*meanY + 6.0*meanYY*meanY*meanY - 3.0*meanY*meanY*meanY*meanY;
													mju4_Z = meanZZZZ - 4.0*meanZZZ*meanZ + 6.0*meanZZ*meanZ*meanZ - 3.0*meanZ*meanZ*meanZ*meanZ;
												}

												if(this->cmfd.bDisp)
												{
													fprintf(stream2,"%c%f", delim, mju2_X);
													fprintf(stream2,"%c%f", delim, mju2_Y);
													fprintf(stream2,"%c%f", delim, mju2_Z);
												}

												if(this->cmfd.bAsim)
												{
													fprintf(stream2,"%c%f", delim, mju3_X / (mju2_X * sqrt(mju2_X)) );
													fprintf(stream2,"%c%f", delim, mju3_Y / (mju2_Y * sqrt(mju2_Y)) );
													fprintf(stream2,"%c%f", delim, mju3_Z / (mju2_Z * sqrt(mju2_Z)) );
												}


												if(this->cmfd.bExcess)
												{
													fprintf(stream2,"%c%f", delim, mju4_X / (mju2_X * mju2_X) - 3.0 );
													fprintf(stream2,"%c%f", delim, mju4_Y / (mju2_Y * mju2_Y) - 3.0 );
													fprintf(stream2,"%c%f", delim, mju4_Z / (mju2_Z * mju2_Z) - 3.0 );
												}


												if(this->cmfd.bMax)
												{
													fprintf(stream2,"%c%d", delim, int(maxX));
													fprintf(stream2,"%c%d", delim, int(maxY));
													fprintf(stream2,"%c%d", delim, int(maxZ));
												}


												if(this->cmfd.bPolarization)
												{
													fprintf(stream2,"%c%f", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
													fprintf(stream2,"%c%f", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);
												}

												if(this->cmfd.bInvPolarization)
												{
													fprintf(stream2,"%c%f", delim, maxX+minX > 0.0 ? (maxX-minX)/(maxX+minX) : 0.);
													fprintf(stream2,"%c%f", delim, maxY+minY > 0.0 ? (maxY-minY)/(maxY+minY) : 0.);
													fprintf(stream2,"%c%f", delim, maxZ+minZ > 0.0 ? (maxZ-minZ)/(maxZ+minZ) : 0.);
												}


												if(this->cmfd.bMinAngle)
												{
													fprintf(stream2,"%c%f", delim, minAngleYZ);
													fprintf(stream2,"%c%f", delim, minAngleZX);
													fprintf(stream2,"%c%f", delim, minAngleXY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, minAngleZY);
														fprintf(stream2,"%c%f", delim, minAngleXZ);
														fprintf(stream2,"%c%f", delim, minAngleYX);
													}
												}


												if(this->cmfd.bMedianAngle)
												{
													fprintf(stream2,"%c%f", delim, MedianAngleYZ);
													fprintf(stream2,"%c%f", delim, MedianAngleZX);
													fprintf(stream2,"%c%f", delim, MedianAngleXY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, MedianAngleZY);
														fprintf(stream2,"%c%f", delim, MedianAngleXZ);
														fprintf(stream2,"%c%f", delim, MedianAngleYX);
													}
												}


												if(this->cmfd.bMeanAngle)
												{
													fprintf(stream2,"%c%f", delim, meanAngleYZ);
													fprintf(stream2,"%c%f", delim, meanAngleZX);
													fprintf(stream2,"%c%f", delim, meanAngleXY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, meanAngleZY);
														fprintf(stream2,"%c%f", delim, meanAngleXZ);
														fprintf(stream2,"%c%f", delim, meanAngleYX);
													}
												}

												if(this->cmfd.bMaxAngle)
												{
													fprintf(stream2,"%c%f", delim, maxAngleYZ);
													fprintf(stream2,"%c%f", delim, maxAngleZX);
													fprintf(stream2,"%c%f", delim, maxAngleXY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleZY);
														fprintf(stream2,"%c%f", delim, maxAngleXZ);
														fprintf(stream2,"%c%f", delim, maxAngleYX);
													}
												}

													
												if(this->cmfd.bPolarizationAngle)
												{
													fprintf(stream2,"%c%f", delim, maxAngleYZ-minAngleYZ > 0.0 ? 0.5*(maxAngleYZ+minAngleYZ)/(maxAngleYZ-minAngleYZ) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleZX-minAngleZX > 0.0 ? 0.5*(maxAngleZX+minAngleZX)/(maxAngleZX-minAngleZX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleXY-minAngleXY > 0.0 ? 0.5*(maxAngleXY+minAngleXY)/(maxAngleXY-minAngleXY) : 0.5);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleZY-minAngleZY > 0.0 ? 0.5*(maxAngleZY+minAngleZY)/(maxAngleZY-minAngleZY) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXZ-minAngleXZ > 0.0 ? 0.5*(maxAngleXZ+minAngleXZ)/(maxAngleXZ-minAngleXZ) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleYX-minAngleYX > 0.0 ? 0.5*(maxAngleYX+minAngleYX)/(maxAngleYX-minAngleYX) : 0.5);
													}
												}

												if(this->cmfd.bInvPolarizationAngle)
												{
													fprintf(stream2,"%c%f", delim, maxAngleYZ+minAngleYZ > 0.0 ? (maxAngleYZ-minAngleYZ)/(maxAngleYZ+minAngleYZ) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleZX+minAngleZX > 0.0 ? (maxAngleZX-minAngleZX)/(maxAngleZX+minAngleZX) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleXY+minAngleXY > 0.0 ? (maxAngleXY-minAngleXY)/(maxAngleXY+minAngleXY) : 0.);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleZY+minAngleZY > 0.0 ? (maxAngleZY-minAngleZY)/(maxAngleZY+minAngleZY) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXZ+minAngleXZ > 0.0 ? (maxAngleXZ-minAngleXZ)/(maxAngleXZ+minAngleXZ) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleYX+minAngleYX > 0.0 ? (maxAngleYX-minAngleYX)/(maxAngleYX+minAngleYX) : 0.);
													}
												}


												if(this->cmfd.bMinAngle3)
												{
													fprintf(stream2,"%c%f", delim, minAngleX_YZ);
													fprintf(stream2,"%c%f", delim, minAngleY_ZX);
													fprintf(stream2,"%c%f", delim, minAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, minAngleYZ_X);
														fprintf(stream2,"%c%f", delim, minAngleZX_Y);
														fprintf(stream2,"%c%f", delim, minAngleXY_Z);
													}
												}


												if(this->cmfd.bMedianAngle3)
												{
													fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
													fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
													fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
														fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
														fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
													}
												}


												if(this->cmfd.bMeanAngle3)
												{
													fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
													fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
													fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
														fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
														fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
													}
												}


												if(this->cmfd.bMaxAngle3)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
													}
												}

												if(this->cmfd.bPolarizationAngle3)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
													}
												}													
			
												if(this->cmfd.bInvPolarizationAngle3)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
													}
												}													
			


												if(this->cmfd.bMinAngle4)
												{
													fprintf(stream2,"%c%f", delim, minAngleX_YZ);
													fprintf(stream2,"%c%f", delim, minAngleY_ZX);
													fprintf(stream2,"%c%f", delim, minAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, minAngleYZ_X);
														fprintf(stream2,"%c%f", delim, minAngleZX_Y);
														fprintf(stream2,"%c%f", delim, minAngleXY_Z);
													}
												}


												if(this->cmfd.bMedianAngle4)
												{
													fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
													fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
													fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
														fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
														fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
													}
												}


												if(this->cmfd.bMeanAngle4)
												{
													fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
													fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
													fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
														fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
														fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
													}
												}


												if(this->cmfd.bMaxAngle4)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
													}
												}

												if(this->cmfd.bPolarizationAngle4)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
													}
												}													
			
												if(this->cmfd.bInvPolarizationAngle4)
												{
													fprintf(stream2,"%c%f", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
													fprintf(stream2,"%c%f", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

													if(this->cmfd.bReverseAngles)
													{
														fprintf(stream2,"%c%f", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
													}
												}													
			

													
													if(this->cmfd.bMinXYZ)
													{
														fprintf(stream2,"%c%d", delim, int(minXYZ));
													}

													if(this->cmfd.bMedianXYZ)
													{
														fprintf(stream2,"%c%f", delim, medianXYZ);
													}

													if(this->cmfd.bMeanXYZ)
													{
														fprintf(stream2,"%c%f", delim, meanXYZ);
													}

													if(this->cmfd.bMaxXYZ)
													{
														fprintf(stream2,"%c%d", delim, int(maxXYZ));
													}

													if(this->cmfd.bPolarizationXYZ)
													{
														fprintf(stream2,"%c%f", delim, maxXYZ-minXYZ > 0.0 ? 0.5*(maxXYZ+minXYZ)/(maxXYZ-minXYZ) : 0.5);
													}

													if(this->cmfd.bInvPolarizationXYZ)
													{
														fprintf(stream2,"%c%f", delim, maxXYZ+minXYZ > 0.0 ? (maxXYZ-minXYZ)/(maxXYZ+minXYZ) : 0.);
													}


												///////////////////////////////////////////////////
												
												
												if(this->cmfd.shPeriodFlag != this->cmfd.shPeriodFlagHalfOfDay || 
													(this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay && CurrentHour >= 24 - mean_hour))
												{
													bNewStringDone = true;
													fprintf(stream2,"\n");
												}
												else
													bNewStringDone = false;
											}
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
						}
						i++;
					}
				}
			}
			fclose(stream2);
			fclose(stream);
			if(this->cmfd.bMeanPerDay)
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
		{
			toRead = true;
			MessageBox(0,"toRead = false","",0);
		}
	}
	if(this->cmfd.bMeanPerDay)
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
/*
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
*/
	MessageBox(0, "", "Конверт завершён", 
		MB_OK | MB_ICONINFORMATION);

}


#define USE_MULTIPARAM 0

void CommonMeanFileDialog::createCommonFile2(size_t nInputs)
{
	int global_max_X = 0;
	int global_max_Y = 0;
	int global_max_Z = 0;

	int nPribor = this->cmfd.nPribor;

	SYSTEMTIME global_max_Xt;
	SYSTEMTIME global_max_Yt;
	SYSTEMTIME global_max_Zt;

	char startDate[15],
		finishDate[15];

	char filename_in[1023],
		directory_out[1023],
		filename_out_temp[1023],
		filename_out[1023];

	char szPath_in[1023];

	double test_t,test_t0, pre_wrote_t2 = 0;
	bool bNewStringDone = true;

	wsprintf(startDate, "%d/%02d/%02d\0", this->cmfd.startYear, this->cmfd.startMonth, this->cmfd.startDay);
	wsprintf(finishDate, "%d/%02d/%02d\0", this->cmfd.finishYear, this->cmfd.finishMonth, this->cmfd.finishDay);

	char sPeriod[16], sFormat[16], sFormat2[16], sExt[8]; sprintf(sExt, ".txt");
	switch(this->cmfd.shPeriodFlag)
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
			wsprintf(sPeriod,"20 min");
		}
		break;
	case 5:
		{
			wsprintf(sPeriod,"30 min");
		}
		break;
	case 6:
		{
			wsprintf(sPeriod,"1 hours");
		}
		break;
	case 7:
		{
			wsprintf(sPeriod,"2 hours");
		}
		break;
	case 8:
		{
			wsprintf(sPeriod,"3 hours");
		}
		break;
	case 9:
		{
			wsprintf(sPeriod,"4 hours");
		}
		break;
	case 10:
		{
			wsprintf(sPeriod,"6 hours");
		}
		break;
	case 11:
		{
			wsprintf(sPeriod,"8 hours");
		}
		break;
	case 12:
		{
			wsprintf(sPeriod,"12 hours");
		}
		break;
	case 13:
		{
			wsprintf(sPeriod,"24 hours");
		}
		break;
	case 14:
		{
			wsprintf(sPeriod,"2-12 hours");
		}
		break;
	}
	switch(this->outputTimeFormat)
	{
	case 0:
		{
			wsprintf(sFormat,"x");
			wsprintf(sFormat2,"excel");
		}
		break;
	case 1:
		{
			wsprintf(sFormat,"m");
			wsprintf(sFormat2,"matlab");
		}
		break;
	case 2:
		{
			wsprintf(sFormat,"u");
			wsprintf(sFormat2,"unix");
		}
		break;
	case 3:
		{
			wsprintf(sFormat,"db");
			wsprintf(sFormat2,"database");
		}
		break;
	case 4:
		{
			wsprintf(sFormat,"v");
			wsprintf(sFormat2,"tezeyvar");
		}
		break;
	}

	wsprintf(directory_out, "%s\\CommonFiles", directory);

	switch (this->cmfd.nHowUseFilePath )
	{
	case 0:
	case 1:
	case 2:
		{
			wsprintf(filename_out_temp,"%d_c%s%s_%02d_%02d_%02d_%02d_%02d_%02d%s",
				nPribor,
				sFormat,
				sPeriod,
				this->cmfd.startYear-(this->cmfd.startYear/100)*100, this->cmfd.startMonth, this->cmfd.startDay, 
				this->cmfd.finishYear-(this->cmfd.finishYear/100)*100, this->cmfd.finishMonth, this->cmfd.finishDay,
				sExt);
		}
		break;
	}

		
	CreateDirectory(directory_out,NULL);

	char delim = this->cmfd.delim;

	strcpy(filename_out, directory_out);
	strcat(filename_out, "\\");
	strcat(filename_out, filename_out_temp);

	double dn1 = datenum(this->cmfd.startYear, this->cmfd.startMonth, this->cmfd.startDay, 0, 0, 0, 0);
	double dn2 = datenum(this->cmfd.finishYear, this->cmfd.finishMonth, this->cmfd.finishDay, 0, 0, 0, 0);
	double start_t = dn1, finish_t = dn2;



	double *input; 
	input = new double[nInputs+1];
	if (input == NULL)
	{
		MessageBox(0, "input - Not enough memory",
			"createCommonFile()", 0);
		return;

	}
	int jj = 0, // rows on excel file
		kk = 1; // pages on excel file
	double t1, t2;
	long maxWindowLength=131072-1;

	long WindowIndex=0;

	int CurrentMinute,
		CurrentHour,
		CurrentDay,
		CurrentMonth,
		CurrentYear;

	double 
		t0_excel = datenum(1900,1,1,0,0,0,0)-2;

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	size_t SecsPerDay = 3600*24+1;

	double **vmean;
	UINT ii;
	if(this->cmfd.bMeanPerDay)
	{
		if ((vmean = Alloc2DMat<double>(nInputs, SecsPerDay)) == NULL)
		{
			MessageBox(0, "vmean - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			for (ii = 0; ii < SecsPerDay; ii++)
			{
				vmean[iInput][ii] = 0.0;
			}
		}
	}
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int *vn;

	if(this->cmfd.bMeanPerDay)
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
	double * mean_val = new double[nInputs];
	double * mean_val2 = new double[nInputs];
	double * mean_val3 = new double[nInputs];
	double * mean_val4 = new double[nInputs];

	double * mju2 = new double[nInputs];
	double * mju3 = new double[nInputs];
	double * mju4 = new double[nInputs];

	//double meanX2, meanY2, meanZ2;
	double * median_val = new double[nInputs]; 
	double * min_val = new double[nInputs]; 
	double * max_val = new double[nInputs]; 
		
	double medianXYZ;

	double *vmeant = NULL;

	if(this->cmfd.bMeanPerDay)
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
	//double **vin, *vt;
	//int len_of_dayly_file = 0;

	/*if(this->cmfd.bMeanPerDay)
	{
		if ((vt = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
		if ((vin = Alloc2DMat<double>(nInputs,maxWindowLength)) == NULL)
		{
			MessageBox(0, "vin - Not enough memory",
				"createCommonFile()", 0);
			return;
		}
	}*/
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	double **vIN = NULL;

	if ((vIN = Alloc2DMat<double>(nInputs, maxWindowLength)) == NULL)
	{
		MessageBox(0, "vIN - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
#if USE_MULTIPARAM
	double *vYZ = NULL, *vZX = NULL, *vXY = NULL;
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
#endif
	double *vX_YZ = NULL, *vY_ZX = NULL, *vZ_XY = NULL;
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

	double *vX_XYZ = NULL, *vY_XYZ = NULL, *vZ_XYZ = NULL;
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

	double *vXYZ = NULL;
	if ((vXYZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,maxWindowLength*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}

	FILE *stream = NULL;



	DWORD nFilterIndex = 0;
	if (SaveFileDlg(hWnd, filename_out, "Text files (*.txt)\0*.txt\0All files \0*.*\0", nFilterIndex) != S_OK)
		return;



	FILE *stream2 = NULL;
	if ((stream2 = fopen(filename_out,"wt")) == NULL)
	{
		MessageBox(0, filename_out, "Convert Common Cannot open output file.", 
			MB_OK | MB_ICONINFORMATION);
			return;
	}
	// write header
	fprintf(stream2,"time1%ctime2", delim);
	if(this->cmfd.bMin)
	{
#if 1
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Минимум сигнала %s за %s период ", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);

			fprintf(stream2,"%d.%d.%d - %d.%d.%d\"", 

				this->cmfd.startDay,this->cmfd.startMonth,this->cmfd.startYear
				,this->cmfd.finishDay,this->cmfd.finishMonth,this->cmfd.finishYear
				);
		}
#else
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Минимум сигнала %s за %s период %d.%d.%d - %d.%d.%d\"", 
				(*this->pnames_of_colomns)[iInput+1].c_str(),
				delim, sPeriod
				,this->cmfd.startDay,this->cmfd.startMonth,this->cmfd.startYear
				,this->cmfd.finishDay,this->cmfd.finishMonth,this->cmfd.finishYear
				);
		}
#endif
	}

	if(this->cmfd.bMedian)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Медиана сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}

	if(this->cmfd.bMean)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Средняя сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}

	if(this->cmfd.bDisp)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Дисперсия сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}

	if(this->cmfd.bAsim)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Асимметрия сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}

	if(this->cmfd.bExcess)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Эксцесс сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}
	if(this->cmfd.bMax)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Максимум сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}

	if(this->cmfd.bPolarization)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Степень когерентности сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}
	if(this->cmfd.bInvPolarization)
	{
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			fprintf(stream2,"%c\"Inverce Polarization сигнала %s за %s период\"", 
				delim, (*this->pnames_of_colomns)[iInput+1].c_str(), sPeriod);
		}
	}

	if(this->cmfd.bMinAngle)
	{
		fprintf(stream2,"%cМинимум отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMedianAngle)
	{
		fprintf(stream2,"%cМедиана отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMeanAngle)
	{
		fprintf(stream2,"%cСредняя отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMaxAngle)
	{
		fprintf(stream2,"%cМаксимум отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bPolarizationAngle)
	{
		fprintf(stream2,"%cСтепень когерентности отношения сигналов Y и Z за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигналов Z и X за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигналов X и Y за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bInvPolarizationAngle)
	{
		fprintf(stream2,"%cInvPolarizationAngleYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleXY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleZY_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXZ_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleYX_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMinAngle3)
	{
		fprintf(stream2,"%cMinAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMinAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMinAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMedianAngle3)
	{
		fprintf(stream2,"%cMedianAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMedianAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMedianAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMeanAngle3)
	{
		fprintf(stream2,"%cMeanAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMeanAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMeanAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMaxAngle3)
	{
		fprintf(stream2,"%cMaxAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cMaxAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cMaxAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bPolarizationAngle3)
	{
		fprintf(stream2,"%cPolarizationAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cPolarizationAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cPolarizationAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bInvPolarizationAngle3)
	{
		fprintf(stream2,"%cInvPolarizationAngleX_YZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleY_ZX_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZ_XY_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZX_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXY_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMinAngle4)
	{
		fprintf(stream2,"%cМинимум отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМинимум отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMinAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMedianAngle4)
	{
		fprintf(stream2,"%cМедиана отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМедиана отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMedianAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMeanAngle4)
	{
		fprintf(stream2,"%cСредняя отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСредняя отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMeanAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMaxAngle4)
	{
		fprintf(stream2,"%cМаксимум отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cМаксимум отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cMaxAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bPolarizationAngle4)
	{
		fprintf(stream2,"%cСтепень когерентности отношения сигнала X к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигнала Y к модулю сигнала за %s период выраженного как угол", delim, sPeriod);
		fprintf(stream2,"%cСтепень когерентности отношения сигнала Z к модулю сигнала за %s период выраженного как угол", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cPolarizationAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bInvPolarizationAngle4)
	{
		fprintf(stream2,"%cInvPolarizationAngleX_XYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleY_XYZ_%s", delim, sPeriod);
		fprintf(stream2,"%cInvPolarizationAngleZ_XYZ_%s", delim, sPeriod);

		if(this->cmfd.bReverseAngles)
		{
			fprintf(stream2,"%cInvPolarizationAngleXYZ_X_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXYZ_Y_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXYZ_Z_%s", delim, sPeriod);
		}
	}

	if(this->cmfd.bMinXYZ)
	{
		fprintf(stream2,"Минимум модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bMedianXYZ)
	{
		fprintf(stream2,"%cМедиана модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bMeanXYZ)
	{
		fprintf(stream2,"%cСредняя модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bMaxXYZ)
	{
		fprintf(stream2,"%cМаксимум модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bPolarizationXYZ)
	{
		fprintf(stream2,"%cСтепень когерентности модуля сигнала за %s период", delim, sPeriod);
	}
	if(this->cmfd.bInvPolarizationXYZ)
	{
		fprintf(stream2,"%cInvPolarizationXYZ_%s", delim, sPeriod);
	}


	if (this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay)
	{
		if(this->cmfd.bMin)
		{
			fprintf(stream2,"%cminX2_%s", delim, sPeriod);
			fprintf(stream2,"%cminY2_%s", delim, sPeriod);
			fprintf(stream2,"%cminZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMedian)
		{
			fprintf(stream2,"%cmedianX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmedianY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmedianZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMean)
		{
			fprintf(stream2,"%cmeanX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmeanY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmeanZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bDisp)
		{
			fprintf(stream2,"%cdispX2_%s", delim, sPeriod);
			fprintf(stream2,"%cdispY2_%s", delim, sPeriod);
			fprintf(stream2,"%cdispZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bAsim)
		{
			fprintf(stream2,"%casimX2_%s", delim, sPeriod);
			fprintf(stream2,"%casimY2_%s", delim, sPeriod);
			fprintf(stream2,"%casimZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bExcess)
		{
			fprintf(stream2,"%cexcessX2_%s", delim, sPeriod);
			fprintf(stream2,"%cexcessY2_%s", delim, sPeriod);
			fprintf(stream2,"%cexcessZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMax)
		{
			fprintf(stream2,"%cmaxX2_%s", delim, sPeriod);
			fprintf(stream2,"%cmaxY2_%s", delim, sPeriod);
			fprintf(stream2,"%cmaxZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bPolarization)
		{
			fprintf(stream2,"%cPolarizationX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationY2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bInvPolarization)
		{
			fprintf(stream2,"%cInvPolarizationX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationY2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationZ2_%s", delim, sPeriod);
		}

		if(this->cmfd.bMinAngle)
		{
			fprintf(stream2,"%cMinAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMedianAngle)
		{
			fprintf(stream2,"%cMedianAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMeanAngle)
		{
			fprintf(stream2,"%cMeanAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMaxAngle)
		{
			fprintf(stream2,"%cMaxAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bPolarizationAngle)
		{
			fprintf(stream2,"%cPolarizationAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleYX2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bInvPolarizationAngle)
		{
			fprintf(stream2,"%cInvPolarizationAngleYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleXY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleZY2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXZ2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleYX2_%s", delim, sPeriod);
			}
		}


		if(this->cmfd.bMinAngle3)
		{
			fprintf(stream2,"%cMinAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMedianAngle3)
		{
			fprintf(stream2,"%cMedianAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMeanAngle3)
		{
			fprintf(stream2,"%cMeanAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMeanAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMaxAngle3)
		{
			fprintf(stream2,"%cMaxAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bPolarizationAngle3)
		{
			fprintf(stream2,"%cPolarizationAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXY_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bInvPolarizationAngle3)
		{
			fprintf(stream2,"%cInvPolarizationAngleX_YZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleY_ZX2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZ_XY2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleZX_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXY_Z2_%s", delim, sPeriod);
			}
		}


		if(this->cmfd.bMinAngle4)
		{
			fprintf(stream2,"%cMinAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMinAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMinAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMinAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMedianAngle4)
		{
			fprintf(stream2,"%cMedianAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMedianAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMedianAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMedianAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMeanAngle4)
		{
			fprintf(stream2,"%cMeanAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMeanAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMeanAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMeanAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bMaxAngle4)
		{
			fprintf(stream2,"%cMaxAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cMaxAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cMaxAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cMaxAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}

		if(this->cmfd.bPolarizationAngle4)
		{
			fprintf(stream2,"%cPolarizationAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cPolarizationAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cPolarizationAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cPolarizationAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}
		if(this->cmfd.bInvPolarizationAngle4)
		{
			fprintf(stream2,"%cInvPolarizationAngleX_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleY_XYZ2_%s", delim, sPeriod);
			fprintf(stream2,"%cInvPolarizationAngleZ_XYZ2_%s", delim, sPeriod);

			if(this->cmfd.bReverseAngles)
			{
				fprintf(stream2,"%cInvPolarizationAngleXYZ_X2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXYZ_Y2_%s", delim, sPeriod);
				fprintf(stream2,"%cInvPolarizationAngleXYZ_Z2_%s", delim, sPeriod);
			}
		}
		if(this->cmfd.bMinXYZ)
		{
			fprintf(stream2,"%cminXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bMedianXYZ)
		{
			fprintf(stream2,"%cmedianXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bMeanXYZ)
		{
			fprintf(stream2,"%cmeanXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bMaxXYZ)
		{
			fprintf(stream2,"%cmaxXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bPolarizationXYZ)
		{
			fprintf(stream2,"%cPolarizationXYZ2_%s", delim, sPeriod);
		}
		if(this->cmfd.bInvPolarizationXYZ)
		{
			fprintf(stream2,"%cInvPolarizationXYZ2_%s", delim, sPeriod);
		}
	}

	fprintf(stream2,"\n");


	fclose(stream2);

	int iFile = 0;
	int iFile2 = 0;

	switch (this->cmfd.nHowUseFilePath )
	{
	case 0:// filenames as drozdov filenme formate which include date inteval
		{
		}
		break;
	case 1:// the selected file
		{
			dn2 = dn1;
		}
		break;
	case 2:// all files in th directory
		{
			dn1 = 0;
			dn2 = this->cmfd.nFilesInDirectory-1;
		}
		break;
	}

    RECT rcClient;  // Client area of parent window 
    int cyVScroll;  // Height of scroll bar arrow 
    HWND hwndPB;    // Handle of progress bar 

 

    // Ensure that the common control DLL is loaded
    // and create a progress bar along the bottom of
    // the client area of the parent window. 
    // Base the height of the progress bar on the
    // height of a scroll bar arrow. 
    InitCommonControls(); 
    GetClientRect(this->cmfd.hwndParent, &rcClient); 
    cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
    hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
	         (LPSTR) NULL, WS_CHILD | WS_VISIBLE,
             0, 0,
             //rcClient.left, rcClient.bottom,
             rcClient.right, cyVScroll, 
             this->cmfd.hwndParent, (HMENU) 0, hInst, NULL); 

    // Set the range and increment of the progress
    // bar. 

    SendMessage(hwndPB, PBM_SETRANGE, 0,
                MAKELPARAM(0, int(dn2-dn1))); 
    SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 

	unsigned int i2 = 0;
	bool start = true;

	for (double dn=dn1; dn<=dn2; dn+=1.0)
	{
		iFile++;
		int y, mo, d, h, mi, s, milli;
		bool toRead = true;

		switch (this->cmfd.nHowUseFilePath )
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
				strcpy(szPath_in, szFile);
			}
			break;
		case 2:
			{
				sprintf(szPath_in, "%s\\%s\0", 
					directory, this->cmfd.vFileNames[int(dn)]);
			}
			break;
		}

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
		
		if (toRead)
		{
			//////////////////////////////////////
			double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

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
				char* ch = fgets(szBuff,n,stream);
				if( ch != NULL && strlen(szBuff) > 1)
				{
					size_t bytes_line = strlen(ch);
					vector<string> line_strings;
					ParseLine(i, szBuff, title, bytes_line, dd,  NULL, &line_strings, NULL, input);
					
					const char * time_string = line_strings.begin()->c_str(); 				
					double t;

					if (ParseTimeString(time_string, 
						this->cmfd.timeFormat, 
						this->cmfd.thisIsLocalTime,	
						this->cmfd.localTimeOffsetHours,
						y, mo, d, h, mi, s, milli, t))
					{
						if (start) // (i==0 && iFile==1)
						{	
							start = false;
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
								sprintf(errstr,"Ошибка временной последовательности %s\nимя файла = %s\nразница=%d секунд\n\nПропустить или завершить процесс?", szBuff, szPath_in, int((test_t0 - test_t)*3600.*24.));
								if (MessageBox(0, errstr, "createCommonFile", 
									MB_OKCANCEL | MB_ICONINFORMATION) != IDOK)
								{
									break;
									//fclose(stream2);
									//return;
								}							
							}
						}
						if (test_t0 >= start_t && test_t0 < finish_t+1.0)
						{
							if(this->cmfd.bMeanPerDay)
							{
								double vt_i = test_t0 - floor(test_t0);
								//vx[i] = X;						
								//vy[i] = Y;
								//vz[i] = Z;
								/*for (size_t iInput = 0; iInput < nInputs; iInput++)
								{
									vin[iInput][i] = input[iInput+1];
								}*/
								UINT ind = UINT(vt_i*double(SecsPerDay));
								if (ind >= 0 && ind < SecsPerDay)
								{
									//vmeanX[ind] += vx[ii];
									//vmeanY[ind] += vy[ii];
									//vmeanZ[ind] += vz[ii];
									for (size_t iInput = 0; iInput < nInputs; iInput++)
									{
										vmean[iInput][ind] += input[iInput+1];
									}
									vn[ind] += 1;
								}
						
							}

							if(global_max_X < input[1])
							{
								global_max_X = input[1];
								global_max_Xt.wYear = y;
								global_max_Xt.wMonth = mo;
								global_max_Xt.wDay = d;
								global_max_Xt.wHour = h;
								global_max_Xt.wMinute = mi;
								global_max_Xt.wSecond = s;
							}
							if(global_max_Y < input[2])
							{
								global_max_Y = input[2];
								global_max_Yt.wYear = y;
								global_max_Yt.wMonth = mo;
								global_max_Yt.wDay = d;
								global_max_Yt.wHour = h;
								global_max_Yt.wMinute = mi;
								global_max_Yt.wSecond = s;

							}
							if(global_max_Z < input[3])
							{
								global_max_Z = input[3];
								global_max_Zt.wYear = y;
								global_max_Zt.wMonth = mo;
								global_max_Zt.wDay = d;
								global_max_Zt.wHour = h;
								global_max_Zt.wMinute = mi;
								global_max_Zt.wSecond = s;
							}


							//vX[WindowIndex] = double(X);
							//vY[WindowIndex] = double(Y);
							//vZ[WindowIndex] = double(Z);
							for (size_t iInput = 0; iInput < nInputs; iInput++)
							{
								vIN[iInput][WindowIndex] = input[iInput+1];
							}

							int mean_min = 1,
								mean_hour = 1;
							switch(this->cmfd.shPeriodFlag)
							{
							case 0:mean_min=0; break;
							case 1:mean_min=1; break;
							case 2:mean_min=5; break;
							case 3:mean_min=15;break;
							case 4:mean_min=20;break;
							case 5:mean_min=30;break;
							}
							switch(this->cmfd.shPeriodFlag)
							{
							case 6:mean_hour=1; break;
							case 7:mean_hour=2; break;
							case 8:mean_hour=3; break;
							case 9:mean_hour=4; break;
							case 10:mean_hour=6; break;
							case 11:mean_hour=8; break;
							case 12:mean_hour=12; break;
							case 13:mean_hour=24; break;
							case 14:mean_hour=12; break;
							}
							switch(this->cmfd.shPeriodFlag)
							{
							case 0:// 1 sec - without any meaning
								{	
									///////////////////////////////////////////////////
									t2 = datenum(y, mo, d, h, mi, s, milli);
									printTimeString(stream2, this->outputTimeFormat, t2);
									///////////////////////////////////////////////////
									for (size_t iInput = 0; iInput < nInputs; iInput++)
									{
										fprintf(stream2,"%c%f", delim, input[i+1]);
									}
									fprintf(stream2,"\n");
									///////////////////////////////////////////////////
									
									// cutting of file
									this->cutting_of_output_file(stream2,
										jj,kk,
										directory_out,filename_out,
										filename_out_temp,nPribor,sFormat,sPeriod,sExt);

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
							case 14:
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
										if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagMinStart 
											&& this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagMinEnd)
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
											if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagHoursStart && 
												this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagHalfOfDay)
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
#if USE_MULTIPARAM
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
#endif
											//meanX=0; meanY=0;  meanZ=0;
											for (size_t iInput = 0; iInput < nInputs; iInput++)
											{
												mean_val [iInput] = 0.0;
												mean_val2[iInput] = 0.0;
												mean_val3[iInput] = 0.0;
												mean_val4[iInput] = 0.0;
											}
											//meanX2=0;meanY2=0; meanZ2=0;
											for (int j=0;j<=WindowIndex;j++)
											{
												if(this->cmfd.bMin || this->cmfd.bMax)
												{
													if (j==0)
													{
														//minX = maxX = vX[j];
														//minY = maxY = vY[j];
														//minZ = maxZ = vZ[j];
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															min_val[iInput] = 
																max_val[iInput] = 
																vIN[iInput][j];
														}
													}
													else
													{
														//if (minX > vX[j]) minX = vX[j];
														//if (maxX < vX[j]) maxX = vX[j];
														
														//if (minY > vY[j]) minY = vY[j];
														//if (maxY < vY[j]) maxY = vY[j];
														
														//if (minZ > vZ[j]) minZ = vZ[j];
														//if (maxZ < vZ[j]) maxZ = vZ[j];
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															if(min_val[iInput] > vIN[iInput][j]) min_val[iInput] = vIN[iInput][j];
															if(max_val[iInput] < vIN[iInput][j]) max_val[iInput] = vIN[iInput][j];
														}
													}
												}

												if(this->cmfd.bMean || this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
												{
													//meanX += vX[j];
													//meanY += vY[j];
													//meanZ += vZ[j];
													for (size_t iInput = 0; iInput < nInputs; iInput++)
													{
														mean_val[iInput] += vIN[iInput][j];
													}
												}

												if(this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
												{
													//meanXX += vX[j]*vX[j];
													//meanYY += vY[j]*vY[j];
													//meanZZ += vZ[j]*vZ[j];
													for (size_t iInput = 0; iInput < nInputs; iInput++)
													{
														mean_val2[iInput] += vIN[iInput][j] * vIN[iInput][j];
													}
												}

												if(this->cmfd.bAsim || this->cmfd.bExcess)
												{
													//meanXXX += vX[j]*vX[j]*vX[j];
													//meanYYY += vY[j]*vY[j]*vY[j];
													//meanZZZ += vZ[j]*vZ[j]*vZ[j];
													for (size_t iInput = 0; iInput < nInputs; iInput++)
													{
														mean_val3[iInput] += vIN[iInput][j] * vIN[iInput][j] * vIN[iInput][j];
													}
												}

												if(this->cmfd.bExcess)
												{
													//meanXXXX += vX[j]*vX[j]*vX[j]*vX[j];
													//meanYYYY += vY[j]*vY[j]*vY[j]*vY[j];
													//meanZZZZ += vZ[j]*vZ[j]*vZ[j]*vZ[j];
													for (size_t iInput = 0; iInput < nInputs; iInput++)
													{
														mean_val4[iInput] += vIN[iInput][j] * vIN[iInput][j] * vIN[iInput][j] * vIN[iInput][j];
													}
												}

												if(this->cmfd.bMinAngle || this->cmfd.bMedianAngle 
													|| this->cmfd.bMeanAngle || this->cmfd.bMaxAngle )
												{
	#if USE_MULTIPARAM
													vYZ[j] = 180.*atan2(vY[j], vZ[j])/PI;
													vZX[j] = 180.*atan2(vZ[j], vX[j])/PI;
													vXY[j] = 180.*atan2(vX[j], vY[j])/PI;
	#endif
												}
												if(this->cmfd.bMinAngle || this->cmfd.bMaxAngle)
												{
	#if USE_MULTIPARAM
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
	#endif
												}

												if(this->cmfd.bMeanAngle)
												{										
	#if USE_MULTIPARAM
													meanAngleYZ += vYZ[j];
													meanAngleZX += vZX[j];
													meanAngleXY += vXY[j];
	#endif
												}
												if(this->cmfd.bMinAngle3 || this->cmfd.bMaxAngle3 
													|| this->cmfd.bMeanAngle3 || this->cmfd.bMedianAngle3 )
												{
	#if USE_MULTIPARAM
													vX_YZ[j] = 180.*atan2(vX[j], sqrt(pow(vY[j], 2.0) + pow(vZ[j], 2.0)) )/PI;
													vY_ZX[j] = 180.*atan2(vY[j], sqrt(pow(vZ[j], 2.0) + pow(vX[j], 2.0)) )/PI;
													vZ_XY[j] = 180.*atan2(vZ[j], sqrt(pow(vX[j], 2.0) + pow(vY[j], 2.0)) )/PI;
	#endif
												}
												if(this->cmfd.bMinAngle3 || this->cmfd.bMaxAngle3)
												{
													if (j==0)
													{
#if USE_MULTIPARAM
														minAngleX_YZ = maxAngleX_YZ = vX_YZ[j];
														minAngleY_ZX = maxAngleY_ZX = vY_ZX[j];
														minAngleZ_XY = maxAngleZ_XY = vZ_XY[j];
#endif
													}
													else
													{
#if USE_MULTIPARAM
														if (minAngleX_YZ > vX_YZ[j]) minAngleX_YZ = vX_YZ[j];
														if (maxAngleX_YZ < vX_YZ[j]) maxAngleX_YZ = vX_YZ[j];
														
														if (minAngleY_ZX > vY_ZX[j]) minAngleY_ZX = vY_ZX[j];
														if (maxAngleY_ZX < vY_ZX[j]) maxAngleY_ZX = vY_ZX[j];
														
														if (minAngleZ_XY > vZ_XY[j]) minAngleZ_XY = vZ_XY[j];
														if (maxAngleZ_XY < vZ_XY[j]) maxAngleZ_XY = vZ_XY[j];
#endif
													}
												}
												if(this->cmfd.bMinAngle4 || this->cmfd.bMaxAngle4 
													|| this->cmfd.bMeanAngle4 || this->cmfd.bMedianAngle4 
													|| this->cmfd.bMinXYZ || this->cmfd.bMedianXYZ 
													|| this->cmfd.bMeanXYZ || this->cmfd.bMaxXYZ)
												{
													//vXYZ[j] = sqrt(pow(vX[j], 2.0) + pow(vY[j], 2.0) + pow(vZ[j], 2.0));
													vXYZ[j] = 0.0;
													for (size_t iInput = 0; iInput < nInputs; iInput++)
													{
														vXYZ[j] += pow(vIN[iInput][j], 2.0);
													}
													vXYZ[j] = sqrt(vXYZ[j]);
												}
												if(this->cmfd.bMinAngle4 || this->cmfd.bMaxAngle4 
													|| this->cmfd.bMeanAngle4 || this->cmfd.bMedianAngle4 )
												{
#if USE_MULTIPARAM
													vX_XYZ[j] = 180.*atan2(vX[j], vXYZ[j] )/PI;
													vY_XYZ[j] = 180.*atan2(vY[j], vXYZ[j] )/PI;
													vZ_XYZ[j] = 180.*atan2(vZ[j], vXYZ[j] )/PI;
#endif
												}
												if(this->cmfd.bMinAngle4 || this->cmfd.bMaxAngle4)
												{
													if (j==0)
													{
#if USE_MULTIPARAM
														minAngleX_XYZ = maxAngleX_XYZ = vX_XYZ[j];
														minAngleY_XYZ = maxAngleY_XYZ = vY_XYZ[j];
														minAngleZ_XYZ = maxAngleZ_XYZ = vZ_XYZ[j];
#endif
													}
													else
													{
#if USE_MULTIPARAM
														if (minAngleX_XYZ > vX_XYZ[j]) minAngleX_XYZ = vX_XYZ[j];
														if (maxAngleX_XYZ < vX_XYZ[j]) maxAngleX_XYZ = vX_XYZ[j];
														
														if (minAngleY_XYZ > vY_XYZ[j]) minAngleY_XYZ = vY_XYZ[j];
														if (maxAngleY_XYZ < vY_XYZ[j]) maxAngleY_XYZ = vY_XYZ[j];
														
														if (minAngleZ_XYZ > vZ_XYZ[j]) minAngleZ_XYZ = vZ_XYZ[j];
														if (maxAngleZ_XYZ < vZ_XYZ[j]) maxAngleZ_XYZ = vZ_XYZ[j];
#endif
													}
												}
												if(this->cmfd.bMinXYZ || this->cmfd.bMaxXYZ)
												{
													if (j==0)
													{
#if USE_MULTIPARAM
														minXYZ = maxXYZ = vXYZ[j];
#endif
													}
													else
													{
#if USE_MULTIPARAM
														if (minXYZ > vXYZ[j]) minXYZ = vXYZ[j];
														if (maxXYZ < vXYZ[j]) maxXYZ = vXYZ[j];
#endif
													}
												}
												if(this->cmfd.bMeanAngle3)
												{
#if USE_MULTIPARAM
													meanAngleX_YZ += vX_YZ[j];
													meanAngleY_ZX += vY_ZX[j];
													meanAngleZ_XY += vZ_XY[j];
#endif
												}
												if(this->cmfd.bMeanXYZ)
												{
#if USE_MULTIPARAM
													meanXYZ += vXYZ[j];
#endif
												}
												if(this->cmfd.bMeanAngle4)
												{
#if USE_MULTIPARAM
													meanAngleX_XYZ += vX_XYZ[j];
													meanAngleY_XYZ += vY_XYZ[j];
													meanAngleZ_XYZ += vZ_XYZ[j];
#endif
												}
	/*#if 0
												meanX2 += pow(vX[j], 2.0);
												meanY2 += pow(vY[j], 2.0);
												meanZ2 += pow(vZ[j], 2.0);
	#endif*/

											}
											if(this->cmfd.bMeanXYZ)
											{
#if USE_MULTIPARAM
												meanXYZ /= WindowIndex+1;
#endif
											}

											if(this->cmfd.bMean || this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
											{
												//meanX /= WindowIndex+1;
												//meanY /= WindowIndex+1;
												//meanZ /= WindowIndex+1;
												for (size_t iInput = 0; iInput < nInputs; iInput++)
												{
													mean_val[iInput] /= WindowIndex+1;
												}
											}

											if(this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
											{
												//meanXX /= WindowIndex+1;
												//meanYY /= WindowIndex+1;
												//meanZZ /= WindowIndex+1;
												for (size_t iInput = 0; iInput < nInputs; iInput++)
												{
													mean_val2[iInput] /= WindowIndex+1;
												}
											}
											
											if(this->cmfd.bAsim || this->cmfd.bExcess)
											{
												//meanXXX /= WindowIndex+1;
												//meanYYY /= WindowIndex+1;
												//meanZZZ /= WindowIndex+1;
												for (size_t iInput = 0; iInput < nInputs; iInput++)
												{
													mean_val3[iInput] /= WindowIndex+1;
												}
											}

											if(this->cmfd.bExcess)
											{
												//meanXXXX /= WindowIndex+1;
												//meanYYYY /= WindowIndex+1;
												//meanZZZZ /= WindowIndex+1;
												for (size_t iInput = 0; iInput < nInputs; iInput++)
												{
													mean_val4[iInput] /= WindowIndex+1;
												}
											}

#if USE_MULTIPARAM
											if(this->cmfd.bMinAngle)
											{										
												if(this->cmfd.bReverseAngles)
												{
													minAngleZY = 90.- minAngleYZ;
													minAngleXZ = 90.- minAngleZX;
													minAngleYX = 90.- minAngleXY;
												}
											}
											if(this->cmfd.bMaxAngle)
											{										
												if(this->cmfd.bReverseAngles)
												{
													maxAngleZY = 90.- maxAngleYZ;
													maxAngleXZ = 90.- maxAngleZX;
													maxAngleYX = 90.- maxAngleXY;
												}
											}
#endif
											if(this->cmfd.bMeanAngle)
											{										
#if USE_MULTIPARAM
												meanAngleYZ /= WindowIndex+1;
												meanAngleZX /= WindowIndex+1;
												meanAngleXY /= WindowIndex+1;

												if(this->cmfd.bReverseAngles)
												{
													meanAngleZY = 90.- meanAngleYZ;
													meanAngleXZ = 90.- meanAngleZX;
													meanAngleYX = 90.- meanAngleXY;
												}
#endif
											}
											if(this->cmfd.bMinAngle3)
											{
												if(this->cmfd.bReverseAngles)
												{
#if USE_MULTIPARAM
													minAngleYZ_X = 90.- minAngleX_YZ;
													minAngleZX_Y = 90.- minAngleY_ZX;
													minAngleXY_Z = 90.- minAngleZ_XY;
#endif
												}
											}
											if(this->cmfd.bMaxAngle3)
											{
												if(this->cmfd.bReverseAngles)
												{
#if USE_MULTIPARAM
													maxAngleYZ_X = 90.- maxAngleX_YZ;
													maxAngleZX_Y = 90.- maxAngleY_ZX;
													maxAngleXY_Z = 90.- maxAngleZ_XY;
#endif
												}
											}
											if(this->cmfd.bMeanAngle3)
											{
#if USE_MULTIPARAM
												meanAngleX_YZ /= WindowIndex+1;
												meanAngleY_ZX /= WindowIndex+1;
												meanAngleZ_XY /= WindowIndex+1;

												if(this->cmfd.bReverseAngles)
												{
													meanAngleYZ_X = 90.- meanAngleX_YZ;
													meanAngleZX_Y = 90.- meanAngleY_ZX;
													meanAngleXY_Z = 90.- meanAngleZ_XY;
												}
#endif
											}
											if(this->cmfd.bMinAngle4)
											{
												if(this->cmfd.bReverseAngles)
												{
#if USE_MULTIPARAM
													minAngleXYZ_X = 90.- minAngleX_XYZ;
													minAngleXYZ_Y = 90.- minAngleY_XYZ;
													minAngleXYZ_Z = 90.- minAngleZ_XYZ;
#endif
												}
											}
											if(this->cmfd.bMaxAngle4)
											{
												if(this->cmfd.bReverseAngles)
												{
#if USE_MULTIPARAM
													maxAngleXYZ_X = 90.- maxAngleX_XYZ;
													maxAngleXYZ_Y = 90.- maxAngleY_XYZ;
													maxAngleXYZ_Z = 90.- maxAngleZ_XYZ;
#endif
												}
											}
											if(this->cmfd.bMeanAngle4)
											{
#if USE_MULTIPARAM
												meanAngleX_XYZ /= WindowIndex+1;
												meanAngleY_XYZ /= WindowIndex+1;
												meanAngleZ_XYZ /= WindowIndex+1;

												if(this->cmfd.bReverseAngles)
												{
													meanAngleXYZ_X = 90.- meanAngleX_XYZ;
													meanAngleXYZ_Y = 90.- meanAngleY_XYZ;
													meanAngleXYZ_Z = 90.- meanAngleZ_XYZ;
												}
#endif
											}
											if(this->cmfd.bMedian)
											{
												//medianX = Median(vX, WindowIndex+1);
												//medianY = Median(vY, WindowIndex+1);
												//medianZ = Median(vZ, WindowIndex+1);
												for (size_t iInput = 0; iInput < nInputs; iInput++)
												{
													median_val[iInput] = Median(vIN[iInput], WindowIndex+1);;
												}
											}
											if(this->cmfd.bMedianXYZ)
											{
												medianXYZ = Median(vXYZ, WindowIndex+1);
											}
											if(this->cmfd.bMedianAngle)
											{
#if USE_MULTIPARAM
												MedianAngleYZ = Median(vYZ, WindowIndex+1);
												MedianAngleZX = Median(vZX, WindowIndex+1);
												MedianAngleXY = Median(vXY, WindowIndex+1);

												if(this->cmfd.bReverseAngles)
												{
													MedianAngleZY = 90.- MedianAngleYZ;
													MedianAngleXZ = 90.- MedianAngleZX;
													MedianAngleYX = 90.- MedianAngleXY;
												}
#endif
											}
											if(this->cmfd.bMedianAngle3)
											{
#if USE_MULTIPARAM
												MedianAngleX_YZ = Median(vX_YZ, WindowIndex+1);
												MedianAngleY_ZX = Median(vY_ZX, WindowIndex+1);
												MedianAngleZ_XY = Median(vZ_XY, WindowIndex+1);

												if(this->cmfd.bReverseAngles)
												{
													MedianAngleYZ_X = 90.- MedianAngleX_YZ;
													MedianAngleZX_Y = 90.- MedianAngleY_ZX;
													MedianAngleXY_Z = 90.- MedianAngleZ_XY;
												}
#endif
											}
											if(this->cmfd.bMedianAngle4)
											{
#if USE_MULTIPARAM
												MedianAngleX_XYZ = Median(vX_XYZ, WindowIndex+1);
												MedianAngleY_XYZ = Median(vY_XYZ, WindowIndex+1);
												MedianAngleZ_XYZ = Median(vZ_XYZ, WindowIndex+1);

												if(this->cmfd.bReverseAngles)
												{
													MedianAngleXYZ_X = 90.- MedianAngleX_XYZ;
													MedianAngleXYZ_Y = 90.- MedianAngleY_XYZ;
													MedianAngleXYZ_Z = 90.- MedianAngleZ_XYZ;
												}
#endif
											}
											///////////////////////////////////////////////////
											//if (this->cmfd.shFormatFlag !=2)// excel or matlab format
											{
												///////////////////////////////////////////////////
												if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagMinStart 
													&& this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagMinEnd)
												{
													t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, CurrentHour, CurrentMinute, 0, 0);
													t2 = datenum(y, mo, d, h, mi, 0, 0);
												}
												else
												{
													if (this->cmfd.shPeriodFlag >= this->cmfd.shPeriodFlagHoursStart 
													&& this->cmfd.shPeriodFlag <= this->cmfd.shPeriodFlagHoursEnd)
													{
														t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, CurrentHour, 0, 0, 0);
														t2 = t1 + double(mean_hour)/double(24);
													}
													else
													{
														if(this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay )
														{
															t1 = datenum(CurrentYear, CurrentMonth, CurrentDay, 0, 0, 0, 0);
															t2 = t1 + 1.0;
														}
													}
												}


												//if (this->cmfd.shFormatFlag == 0)// excel format
												{
													// cutting of file
													this->cutting_of_output_file(stream2,
														jj,kk,
														directory_out,filename_out,
														filename_out_temp,nPribor,sFormat,sPeriod,sExt);

													bool toWriteDate = pre_wrote_t2 != t2;
													///////////////////////////////////////////////////
													if(this->cmfd.shPeriodFlag != this->cmfd.shPeriodFlagHalfOfDay || 
														(this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay && toWriteDate))
													{
														if (bNewStringDone)
														{
															//fprintf(stream2,"%.8f%c%.8f", t1,delim,t2);
														}
														else 
														{
															//fprintf(stream2,"\n%.8f%c%.8f", t1,delim,t2);
															fprintf(stream2,"\n");
														}
														printTimeString(stream2, this->outputTimeFormat, t1);
														fprintf(stream2,"%c", delim);
														printTimeString(stream2, this->outputTimeFormat, t2);
														pre_wrote_t2 = t2;
													}

													// если до полудня нет данных, пишем дату и заполнем пробелами												
													if (this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay && CurrentHour >= 24 - mean_hour && toWriteDate)
													{
														///////////////////////////////////////////////////
														if(this->cmfd.bMin)
														{
															//fprintf(stream2,"%c ", delim, int(minX));
															//fprintf(stream2,"%c ", delim, int(minY));
															//fprintf(stream2,"%c ", delim, int(minZ));
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim, int(min_val[iInput]));
															}
														}

														if(this->cmfd.bMedian)
														{
															//fprintf(stream2,"%c ", delim, medianX);
															//fprintf(stream2,"%c ", delim, medianY);
															//fprintf(stream2,"%c ", delim, medianZ);
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim, median_val[iInput]);
															}
														}

														if(this->cmfd.bMean)
														{
															//fprintf(stream2,"%c ", delim, meanX);
															//fprintf(stream2,"%c ", delim, meanY);
															//fprintf(stream2,"%c ", delim, meanZ);
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim, mean_val[iInput]);
															}
														}

														if(this->cmfd.bDisp)
														{
															//fprintf(stream2,"%c ", delim);
															//fprintf(stream2,"%c ", delim);
															//fprintf(stream2,"%c ", delim);
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim);
															}
														}

														if(this->cmfd.bAsim)
														{
															//fprintf(stream2,"%c ", delim);
															//fprintf(stream2,"%c ", delim);
															//fprintf(stream2,"%c ", delim);
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim);
															}
														}

														if(this->cmfd.bExcess)
														{
															//fprintf(stream2,"%c ", delim);
															//fprintf(stream2,"%c ", delim);
															//fprintf(stream2,"%c ", delim);
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim);
															}
														}

														if(this->cmfd.bMax)
														{
															//fprintf(stream2,"%c ", delim, int(maxX));
															//fprintf(stream2,"%c ", delim, int(maxY));
															//fprintf(stream2,"%c ", delim, int(maxZ));
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim, int(max_val[iInput]));
															}
														}

														if(this->cmfd.bPolarization)
														{
															//fprintf(stream2,"%c ", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
															//fprintf(stream2,"%c ", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
															//fprintf(stream2,"%c ", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);
																							
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim, 
																	max_val[iInput]-min_val[iInput] > 0.0 ? 0.5*(max_val[iInput]+min_val[iInput])/(max_val[iInput]-min_val[iInput]) : 0.5);
															}
														}

														if(this->cmfd.bInvPolarization)
														{
															//fprintf(stream2,"%c ", delim, maxX+minX > 0.0 ? (maxX-minX)/(maxX+minX) : 0.);
															//fprintf(stream2,"%c ", delim, maxY+minY > 0.0 ? (maxY-minY)/(maxY+minY) : 0.);
															//fprintf(stream2,"%c ", delim, maxZ+minZ > 0.0 ? (maxZ-minZ)/(maxZ+minZ) : 0.);
																							
															for (size_t iInput = 0; iInput < nInputs; iInput++)
															{
																fprintf(stream2,"%c ", delim, 
																	max_val[iInput]+min_val[iInput] > 0.0 ? 0.5*(max_val[iInput]-min_val[iInput])/(max_val[iInput]+min_val[iInput]) : 0.0);
															}
														}

														if(this->cmfd.bMinAngle)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, minAngleYZ);
															fprintf(stream2,"%c", delim, minAngleZX);
															fprintf(stream2,"%c", delim, minAngleXY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, minAngleZY);
																fprintf(stream2,"%c", delim, minAngleXZ);
																fprintf(stream2,"%c", delim, minAngleYX);
															}
#endif
														}
																									

														if(this->cmfd.bMedianAngle)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, MedianAngleYZ);
															fprintf(stream2,"%c", delim, MedianAngleZX);
															fprintf(stream2,"%c", delim, MedianAngleXY);
																									
															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, MedianAngleZY);
																fprintf(stream2,"%c", delim, MedianAngleXZ);
																fprintf(stream2,"%c", delim, MedianAngleYX);
															}
#endif
														}

														
														if(this->cmfd.bMeanAngle)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, meanAngleYZ);
															fprintf(stream2,"%c", delim, meanAngleZX);
															fprintf(stream2,"%c", delim, meanAngleXY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, meanAngleZY);
																fprintf(stream2,"%c", delim, meanAngleXZ);
																fprintf(stream2,"%c", delim, meanAngleYX);
															}
#endif
														}
				
														if(this->cmfd.bMaxAngle)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleYZ);
															fprintf(stream2,"%c", delim, maxAngleZX);
															fprintf(stream2,"%c", delim, maxAngleXY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleZY);
																fprintf(stream2,"%c", delim, maxAngleXZ);
																fprintf(stream2,"%c", delim, maxAngleYX);
															}
#endif
														}
														
														if(this->cmfd.bPolarizationAngle)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleYZ-minAngleYZ > 0.0 ? 0.5*(maxAngleYZ+minAngleYZ)/(maxAngleYZ-minAngleYZ) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleZX-minAngleZX > 0.0 ? 0.5*(maxAngleZX+minAngleZX)/(maxAngleZX-minAngleZX) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleXY-minAngleXY > 0.0 ? 0.5*(maxAngleXY+minAngleXY)/(maxAngleXY-minAngleXY) : 0.5);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleZY-minAngleZY > 0.0 ? 0.5*(maxAngleZY+minAngleZY)/(maxAngleZY-minAngleZY) : 0.5);
																fprintf(stream2,"%c", delim, maxAngleXZ-minAngleXZ > 0.0 ? 0.5*(maxAngleXZ+minAngleXZ)/(maxAngleXZ-minAngleXZ) : 0.5);
																fprintf(stream2,"%c", delim, maxAngleYX-minAngleYX > 0.0 ? 0.5*(maxAngleYX+minAngleYX)/(maxAngleYX-minAngleYX) : 0.5);
															}
#endif
														}
				

														if(this->cmfd.bInvPolarizationAngle)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleYZ+minAngleYZ > 0.0 ? (maxAngleYZ-minAngleYZ)/(maxAngleYZ+minAngleYZ) : 0.);
															fprintf(stream2,"%c", delim, maxAngleZX+minAngleZX > 0.0 ? (maxAngleZX-minAngleZX)/(maxAngleZX+minAngleZX) : 0.);
															fprintf(stream2,"%c", delim, maxAngleXY+minAngleXY > 0.0 ? (maxAngleXY-minAngleXY)/(maxAngleXY+minAngleXY) : 0.);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleZY+minAngleZY > 0.0 ? (maxAngleZY-minAngleZY)/(maxAngleZY+minAngleZY) : 0.);
																fprintf(stream2,"%c", delim, maxAngleXZ+minAngleXZ > 0.0 ? (maxAngleXZ-minAngleXZ)/(maxAngleXZ+minAngleXZ) : 0.);
																fprintf(stream2,"%c", delim, maxAngleYX+minAngleYX > 0.0 ? (maxAngleYX-minAngleYX)/(maxAngleYX+minAngleYX) : 0.);
															}
#endif
														}
				

														if(this->cmfd.bMinAngle3)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, minAngleX_YZ);
															fprintf(stream2,"%c", delim, minAngleY_ZX);
															fprintf(stream2,"%c", delim, minAngleZ_XY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, minAngleYZ_X);
																fprintf(stream2,"%c", delim, minAngleZX_Y);
																fprintf(stream2,"%c", delim, minAngleXY_Z);
															}
#endif
														}

														if(this->cmfd.bMedianAngle3)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, MedianAngleX_YZ);
															fprintf(stream2,"%c", delim, MedianAngleY_ZX);
															fprintf(stream2,"%c", delim, MedianAngleZ_XY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, MedianAngleYZ_X);
																fprintf(stream2,"%c", delim, MedianAngleZX_Y);
																fprintf(stream2,"%c", delim, MedianAngleXY_Z);
															}
#endif
														}

														
														if(this->cmfd.bMeanAngle3)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, meanAngleX_YZ);
															fprintf(stream2,"%c", delim, meanAngleY_ZX);
															fprintf(stream2,"%c", delim, meanAngleZ_XY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, meanAngleYZ_X);
																fprintf(stream2,"%c", delim, meanAngleZX_Y);
																fprintf(stream2,"%c", delim, meanAngleXY_Z);
															}
#endif
														}

														if(this->cmfd.bMaxAngle3)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleX_YZ);
															fprintf(stream2,"%c", delim, maxAngleY_ZX);
															fprintf(stream2,"%c", delim, maxAngleZ_XY);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleYZ_X);
																fprintf(stream2,"%c", delim, maxAngleZX_Y);
																fprintf(stream2,"%c", delim, maxAngleXY_Z);
															}
#endif
														}
														
														if(this->cmfd.bPolarizationAngle3)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
																fprintf(stream2,"%c", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
																fprintf(stream2,"%c", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
															}
#endif
														}													
				

														if(this->cmfd.bInvPolarizationAngle3)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
															fprintf(stream2,"%c", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
															fprintf(stream2,"%c", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
																fprintf(stream2,"%c", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
																fprintf(stream2,"%c", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
															}
#endif
														}													
				

														if(this->cmfd.bMinAngle4)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, minAngleX_XYZ);
															fprintf(stream2,"%c", delim, minAngleY_XYZ);
															fprintf(stream2,"%c", delim, minAngleZ_XYZ);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, minAngleXYZ_X);
																fprintf(stream2,"%c", delim, minAngleXYZ_Y);
																fprintf(stream2,"%c", delim, minAngleXYZ_Z);
															}
#endif
														}

														if(this->cmfd.bMedianAngle4)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, MedianAngleX_XYZ);
															fprintf(stream2,"%c", delim, MedianAngleY_XYZ);
															fprintf(stream2,"%c", delim, MedianAngleZ_XYZ);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, MedianAngleXYZ_X);
																fprintf(stream2,"%c", delim, MedianAngleXYZ_Y);
																fprintf(stream2,"%c", delim, MedianAngleXYZ_Z);
															}
#endif
														}

														
														if(this->cmfd.bMeanAngle4)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, meanAngleX_XYZ);
															fprintf(stream2,"%c", delim, meanAngleY_XYZ);
															fprintf(stream2,"%c", delim, meanAngleZ_XYZ);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, meanAngleXYZ_X);
																fprintf(stream2,"%c", delim, meanAngleXYZ_Y);
																fprintf(stream2,"%c", delim, meanAngleXYZ_Z);
															}
#endif
														}

														if(this->cmfd.bMaxAngle4)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleX_XYZ);
															fprintf(stream2,"%c", delim, maxAngleY_XYZ);
															fprintf(stream2,"%c", delim, maxAngleZ_XYZ);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleXYZ_X);
																fprintf(stream2,"%c", delim, maxAngleXYZ_Y);
																fprintf(stream2,"%c", delim, maxAngleXYZ_Z);
															}
#endif
														}
														
														if(this->cmfd.bPolarizationAngle4)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleX_XYZ-minAngleX_XYZ > 0.0 ? 0.5*(maxAngleX_XYZ+minAngleX_XYZ)/(maxAngleX_XYZ-minAngleX_XYZ) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleY_XYZ-minAngleY_XYZ > 0.0 ? 0.5*(maxAngleY_XYZ+minAngleY_XYZ)/(maxAngleY_XYZ-minAngleY_XYZ) : 0.5);
															fprintf(stream2,"%c", delim, maxAngleZ_XYZ-minAngleZ_XYZ > 0.0 ? 0.5*(maxAngleZ_XYZ+minAngleZ_XYZ)/(maxAngleZ_XYZ-minAngleZ_XYZ) : 0.5);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleXYZ_X-minAngleXYZ_X > 0.0 ? 0.5*(maxAngleXYZ_X+minAngleXYZ_X)/(maxAngleXYZ_X-minAngleXYZ_X) : 0.5);
																fprintf(stream2,"%c", delim, maxAngleXYZ_Y-minAngleXYZ_Y > 0.0 ? 0.5*(maxAngleXYZ_Y+minAngleXYZ_Y)/(maxAngleXYZ_Y-minAngleXYZ_Y) : 0.5);
																fprintf(stream2,"%c", delim, maxAngleXYZ_Z-minAngleXYZ_Z > 0.0 ? 0.5*(maxAngleXYZ_Z+minAngleXYZ_Z)/(maxAngleXYZ_Z-minAngleXYZ_Z) : 0.5);
															}
#endif
														}													
				
														if(this->cmfd.bInvPolarizationAngle4)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c", delim, maxAngleX_XYZ+minAngleX_XYZ > 0.0 ? (maxAngleX_XYZ-minAngleX_XYZ)/(maxAngleX_XYZ+minAngleX_XYZ) : 0.);
															fprintf(stream2,"%c", delim, maxAngleY_XYZ+minAngleY_XYZ > 0.0 ? (maxAngleY_XYZ-minAngleY_XYZ)/(maxAngleY_XYZ+minAngleY_XYZ) : 0.);
															fprintf(stream2,"%c", delim, maxAngleZ_XYZ+minAngleZ_XYZ > 0.0 ? (maxAngleZ_XYZ-minAngleZ_XYZ)/(maxAngleZ_XYZ+minAngleZ_XYZ) : 0.);

															if(this->cmfd.bReverseAngles)
															{
																fprintf(stream2,"%c", delim, maxAngleXYZ_X+minAngleXYZ_X > 0.0 ? (maxAngleXYZ_X-minAngleXYZ_X)/(maxAngleXYZ_X+minAngleXYZ_X) : 0.);
																fprintf(stream2,"%c", delim, maxAngleXYZ_Y+minAngleXYZ_Y > 0.0 ? (maxAngleXYZ_Y-minAngleXYZ_Y)/(maxAngleXYZ_Y+minAngleXYZ_Y) : 0.);
																fprintf(stream2,"%c", delim, maxAngleXYZ_Z+minAngleXYZ_Z > 0.0 ? (maxAngleXYZ_Z-minAngleXYZ_Z)/(maxAngleXYZ_Z+minAngleXYZ_Z) : 0.);
															}
#endif
														}
														
														if(this->cmfd.bMinXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c ", delim, int(minXYZ));
#endif
														}

														if(this->cmfd.bMedianXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c ", delim, medianXYZ);
#endif
														}

														if(this->cmfd.bMeanXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c ", delim, meanXYZ);
#endif
														}

														if(this->cmfd.bMaxXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c ", delim, int(maxXYZ));
#endif
														}

														if(this->cmfd.bPolarizationXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c ", delim, maxXYZ-minXYZ > 0.0 ? 0.5*(maxXYZ+minXYZ)/(maxXYZ-minXYZ) : 0.5);
#endif														
														}

														if(this->cmfd.bInvPolarizationXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c ", delim, maxXYZ+minXYZ > 0.0 ? (maxXYZ-minXYZ)/(maxXYZ+minXYZ) : 0.);
#endif
														}

				

														///////////////////////////////////////////////////
													}
													///////////////////////////////////////////////////
													if(this->cmfd.bMin)
													{
														//fprintf(stream2,"%c%d", delim, int(minX));
														//fprintf(stream2,"%c%d", delim, int(minY));
														//fprintf(stream2,"%c%d", delim, int(minZ));
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%d", delim, int(min_val[iInput]));
														}
													}

													if(this->cmfd.bMedian)
													{
														//fprintf(stream2,"%c%f", delim, medianX);
														//fprintf(stream2,"%c%f", delim, medianY);
														//fprintf(stream2,"%c%f", delim, medianZ);
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, median_val[iInput]);
														}
													}

													if(this->cmfd.bMean)
													{
														//fprintf(stream2,"%c%f", delim, meanX);
														//fprintf(stream2,"%c%f", delim, meanY);
														//fprintf(stream2,"%c%f", delim, meanZ);
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, mean_val[iInput]);
														}
													}

													/*

													double mju2_X;//центральный момент второго порядка
													double mju2_Y;//центральный момент второго порядка
													double mju2_Z;//центральный момент второго порядка

													double mju3_X;//центральный момент 3-го порядка
													double mju3_Y;//центральный момент 3-го порядка
													double mju3_Z;//центральный момент 3-го порядка

													double mju4_X;//центральный момент 4-го порядка
													double mju4_Y;//центральный момент 4-го порядка
													double mju4_Z;//центральный момент 4-го порядка
													*/

													if (this->cmfd.bDisp || this->cmfd.bAsim || this->cmfd.bExcess)
													{
														//mju2_X = meanXX - meanX*meanX;
														//mju2_Y = meanYY - meanY*meanY;
														//mju2_Z = meanZZ - meanZ*meanZ;
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															mju2[iInput] = mean_val2[iInput] - mean_val[iInput] * mean_val[iInput];
														}
													}

													if (this->cmfd.bAsim)
													{
														//mju3_X = meanXXX - 3.0*meanXX*meanX + 2.0*meanX*meanX*meanX;
														//mju3_Y = meanYYY - 3.0*meanYY*meanY + 2.0*meanY*meanY*meanY;
														//mju3_Z = meanZZZ - 3.0*meanZZ*meanZ + 2.0*meanZ*meanZ*meanZ;
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															mju3[iInput] = 
																mean_val3[iInput] - 
																3.0 * mean_val2[iInput] * mean_val[iInput] + 
																2.0 * mean_val[iInput] * mean_val[iInput] * mean_val[iInput];
														}													
													}

													if (this->cmfd.bExcess)
													{
														//mju4_X = meanXXXX - 4.0*meanXXX*meanX + 6.0*meanXX*meanX*meanX - 3.0*meanX*meanX*meanX*meanX;
														//mju4_Y = meanYYYY - 4.0*meanYYY*meanY + 6.0*meanYY*meanY*meanY - 3.0*meanY*meanY*meanY*meanY;
														//mju4_Z = meanZZZZ - 4.0*meanZZZ*meanZ + 6.0*meanZZ*meanZ*meanZ - 3.0*meanZ*meanZ*meanZ*meanZ;
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															mju4[iInput] = 
																mean_val4[iInput] - 
																4.0 * mean_val3[iInput] * mean_val[iInput] + 
																6.0 * mean_val2[iInput] * mean_val[iInput] * mean_val[iInput] - 
																3.0 * mean_val[iInput] * mean_val[iInput] * mean_val[iInput] * mean_val[iInput];
														}
													}


													if(this->cmfd.bDisp)
													{
														//fprintf(stream2,"%c%f", delim, mju2_X);
														//fprintf(stream2,"%c%f", delim, mju2_Y);
														//fprintf(stream2,"%c%f", delim, mju2_Z);
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, mju2[iInput]);
														}
													}

													if(this->cmfd.bAsim)
													{
														//fprintf(stream2,"%c%f", delim, mju3_X / (mju2_X * sqrt(mju2_X)) );
														//fprintf(stream2,"%c%f", delim, mju3_Y / (mju2_Y * sqrt(mju2_Y)) );
														//fprintf(stream2,"%c%f", delim, mju3_Z / (mju2_Z * sqrt(mju2_Z)) );
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, mju3[iInput] / (mju2[iInput] * sqrt(mju2[iInput])) );
														}													
													}


													if(this->cmfd.bExcess)
													{
														//fprintf(stream2,"%c%f", delim, mju4_X / (mju2_X * mju2_X) - 3.0 );
														//fprintf(stream2,"%c%f", delim, mju4_Y / (mju2_Y * mju2_Y) - 3.0 );
														//fprintf(stream2,"%c%f", delim, mju4_Z / (mju2_Z * mju2_Z) - 3.0 );
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, mju4[iInput] / (mju2[iInput] * mju2[iInput]) - 3.0 );
														}													
													}


													if(this->cmfd.bMax)
													{
														//fprintf(stream2,"%c%d", delim, int(maxX));
														//fprintf(stream2,"%c%d", delim, int(maxY));
														//fprintf(stream2,"%c%d", delim, int(maxZ));																						
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%d", delim, int(max_val[iInput]));
														}
													}


													if(this->cmfd.bPolarization)
													{
														//fprintf(stream2,"%c%f", delim, maxX-minX > 0.0 ? 0.5*(maxX+minX)/(maxX-minX) : 0.5);
														//fprintf(stream2,"%c%f", delim, maxY-minY > 0.0 ? 0.5*(maxY+minY)/(maxY-minY) : 0.5);
														//fprintf(stream2,"%c%f", delim, maxZ-minZ > 0.0 ? 0.5*(maxZ+minZ)/(maxZ-minZ) : 0.5);
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, 
																max_val[iInput]-min_val[iInput] > 0.0 ? 0.5*(max_val[iInput]+min_val[iInput])/(max_val[iInput]-min_val[iInput]) : 0.5);
														}
													}

													if(this->cmfd.bInvPolarization)
													{
														//fprintf(stream2,"%c%f", delim, maxX+minX > 0.0 ? (maxX-minX)/(maxX+minX) : 0.);
														//fprintf(stream2,"%c%f", delim, maxY+minY > 0.0 ? (maxY-minY)/(maxY+minY) : 0.);
														//fprintf(stream2,"%c%f", delim, maxZ+minZ > 0.0 ? (maxZ-minZ)/(maxZ+minZ) : 0.);
														for (size_t iInput = 0; iInput < nInputs; iInput++)
														{
															fprintf(stream2,"%c%f", delim, 
																max_val[iInput]+min_val[iInput] > 0.0 ? 0.5*(max_val[iInput]-min_val[iInput])/(max_val[iInput]+min_val[iInput]) : 0.0);
														}
													}


													if(this->cmfd.bMinAngle)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, minAngleYZ);
														fprintf(stream2,"%c%f", delim, minAngleZX);
														fprintf(stream2,"%c%f", delim, minAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, minAngleZY);
															fprintf(stream2,"%c%f", delim, minAngleXZ);
															fprintf(stream2,"%c%f", delim, minAngleYX);
														}
#endif
													}


													if(this->cmfd.bMedianAngle)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, MedianAngleYZ);
														fprintf(stream2,"%c%f", delim, MedianAngleZX);
														fprintf(stream2,"%c%f", delim, MedianAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, MedianAngleZY);
															fprintf(stream2,"%c%f", delim, MedianAngleXZ);
															fprintf(stream2,"%c%f", delim, MedianAngleYX);
														}
#endif
													}


													if(this->cmfd.bMeanAngle)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, meanAngleYZ);
														fprintf(stream2,"%c%f", delim, meanAngleZX);
														fprintf(stream2,"%c%f", delim, meanAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, meanAngleZY);
															fprintf(stream2,"%c%f", delim, meanAngleXZ);
															fprintf(stream2,"%c%f", delim, meanAngleYX);
														}
#endif
													}

													if(this->cmfd.bMaxAngle)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleYZ);
														fprintf(stream2,"%c%f", delim, maxAngleZX);
														fprintf(stream2,"%c%f", delim, maxAngleXY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleZY);
															fprintf(stream2,"%c%f", delim, maxAngleXZ);
															fprintf(stream2,"%c%f", delim, maxAngleYX);
														}
#endif
													}

														
													if(this->cmfd.bPolarizationAngle)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleYZ-minAngleYZ > 0.0 ? 0.5*(maxAngleYZ+minAngleYZ)/(maxAngleYZ-minAngleYZ) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZX-minAngleZX > 0.0 ? 0.5*(maxAngleZX+minAngleZX)/(maxAngleZX-minAngleZX) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleXY-minAngleXY > 0.0 ? 0.5*(maxAngleXY+minAngleXY)/(maxAngleXY-minAngleXY) : 0.5);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleZY-minAngleZY > 0.0 ? 0.5*(maxAngleZY+minAngleZY)/(maxAngleZY-minAngleZY) : 0.5);
															fprintf(stream2,"%c%f", delim, maxAngleXZ-minAngleXZ > 0.0 ? 0.5*(maxAngleXZ+minAngleXZ)/(maxAngleXZ-minAngleXZ) : 0.5);
															fprintf(stream2,"%c%f", delim, maxAngleYX-minAngleYX > 0.0 ? 0.5*(maxAngleYX+minAngleYX)/(maxAngleYX-minAngleYX) : 0.5);
														}
#endif
													}

													if(this->cmfd.bInvPolarizationAngle)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleYZ+minAngleYZ > 0.0 ? (maxAngleYZ-minAngleYZ)/(maxAngleYZ+minAngleYZ) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZX+minAngleZX > 0.0 ? (maxAngleZX-minAngleZX)/(maxAngleZX+minAngleZX) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleXY+minAngleXY > 0.0 ? (maxAngleXY-minAngleXY)/(maxAngleXY+minAngleXY) : 0.);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleZY+minAngleZY > 0.0 ? (maxAngleZY-minAngleZY)/(maxAngleZY+minAngleZY) : 0.);
															fprintf(stream2,"%c%f", delim, maxAngleXZ+minAngleXZ > 0.0 ? (maxAngleXZ-minAngleXZ)/(maxAngleXZ+minAngleXZ) : 0.);
															fprintf(stream2,"%c%f", delim, maxAngleYX+minAngleYX > 0.0 ? (maxAngleYX-minAngleYX)/(maxAngleYX+minAngleYX) : 0.);
														}
#endif
													}


													if(this->cmfd.bMinAngle3)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, minAngleX_YZ);
														fprintf(stream2,"%c%f", delim, minAngleY_ZX);
														fprintf(stream2,"%c%f", delim, minAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, minAngleYZ_X);
															fprintf(stream2,"%c%f", delim, minAngleZX_Y);
															fprintf(stream2,"%c%f", delim, minAngleXY_Z);
														}
#endif
													}


													if(this->cmfd.bMedianAngle3)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
														fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
														fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
															fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
															fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
														}
#endif
													}


													if(this->cmfd.bMeanAngle3)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
														fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
														fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
															fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
															fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
														}
#endif
													}


													if(this->cmfd.bMaxAngle3)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
														fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
														fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
															fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
															fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
														}
#endif
													}

													if(this->cmfd.bPolarizationAngle3)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
															fprintf(stream2,"%c%f", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
															fprintf(stream2,"%c%f", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
														}
#endif
													}													
				
													if(this->cmfd.bInvPolarizationAngle3)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
															fprintf(stream2,"%c%f", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
															fprintf(stream2,"%c%f", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
														}
#endif
													}													
				


													if(this->cmfd.bMinAngle4)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, minAngleX_YZ);
														fprintf(stream2,"%c%f", delim, minAngleY_ZX);
														fprintf(stream2,"%c%f", delim, minAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, minAngleYZ_X);
															fprintf(stream2,"%c%f", delim, minAngleZX_Y);
															fprintf(stream2,"%c%f", delim, minAngleXY_Z);
														}
#endif
													}


													if(this->cmfd.bMedianAngle4)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, MedianAngleX_YZ);
														fprintf(stream2,"%c%f", delim, MedianAngleY_ZX);
														fprintf(stream2,"%c%f", delim, MedianAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, MedianAngleYZ_X);
															fprintf(stream2,"%c%f", delim, MedianAngleZX_Y);
															fprintf(stream2,"%c%f", delim, MedianAngleXY_Z);
														}
#endif
													}


													if(this->cmfd.bMeanAngle4)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, meanAngleX_YZ);
														fprintf(stream2,"%c%f", delim, meanAngleY_ZX);
														fprintf(stream2,"%c%f", delim, meanAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, meanAngleYZ_X);
															fprintf(stream2,"%c%f", delim, meanAngleZX_Y);
															fprintf(stream2,"%c%f", delim, meanAngleXY_Z);
														}
#endif
													}


													if(this->cmfd.bMaxAngle4)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleX_YZ);
														fprintf(stream2,"%c%f", delim, maxAngleY_ZX);
														fprintf(stream2,"%c%f", delim, maxAngleZ_XY);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleYZ_X);
															fprintf(stream2,"%c%f", delim, maxAngleZX_Y);
															fprintf(stream2,"%c%f", delim, maxAngleXY_Z);
														}
#endif
													}

													if(this->cmfd.bPolarizationAngle4)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleX_YZ-minAngleX_YZ > 0.0 ? 0.5*(maxAngleX_YZ+minAngleX_YZ)/(maxAngleX_YZ-minAngleX_YZ) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleY_ZX-minAngleY_ZX > 0.0 ? 0.5*(maxAngleY_ZX+minAngleY_ZX)/(maxAngleY_ZX-minAngleY_ZX) : 0.5);
														fprintf(stream2,"%c%f", delim, maxAngleZ_XY-minAngleZ_XY > 0.0 ? 0.5*(maxAngleZ_XY+minAngleZ_XY)/(maxAngleZ_XY-minAngleZ_XY) : 0.5);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleYZ_X-minAngleYZ_X > 0.0 ? 0.5*(maxAngleYZ_X+minAngleYZ_X)/(maxAngleYZ_X-minAngleYZ_X) : 0.5);
															fprintf(stream2,"%c%f", delim, maxAngleZX_Y-minAngleZX_Y > 0.0 ? 0.5*(maxAngleZX_Y+minAngleZX_Y)/(maxAngleZX_Y-minAngleZX_Y) : 0.5);
															fprintf(stream2,"%c%f", delim, maxAngleXY_Z-minAngleXY_Z > 0.0 ? 0.5*(maxAngleXY_Z+minAngleXY_Z)/(maxAngleXY_Z-minAngleXY_Z) : 0.5);
														}
#endif
													}													
				
													if(this->cmfd.bInvPolarizationAngle4)
													{
#if USE_MULTIPARAM
														fprintf(stream2,"%c%f", delim, maxAngleX_YZ+minAngleX_YZ > 0.0 ? (maxAngleX_YZ-minAngleX_YZ)/(maxAngleX_YZ+minAngleX_YZ) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleY_ZX+minAngleY_ZX > 0.0 ? (maxAngleY_ZX-minAngleY_ZX)/(maxAngleY_ZX+minAngleY_ZX) : 0.);
														fprintf(stream2,"%c%f", delim, maxAngleZ_XY+minAngleZ_XY > 0.0 ? (maxAngleZ_XY-minAngleZ_XY)/(maxAngleZ_XY+minAngleZ_XY) : 0.);

														if(this->cmfd.bReverseAngles)
														{
															fprintf(stream2,"%c%f", delim, maxAngleYZ_X+minAngleYZ_X > 0.0 ? (maxAngleYZ_X-minAngleYZ_X)/(maxAngleYZ_X+minAngleYZ_X) : 0.);
															fprintf(stream2,"%c%f", delim, maxAngleZX_Y+minAngleZX_Y > 0.0 ? (maxAngleZX_Y-minAngleZX_Y)/(maxAngleZX_Y+minAngleZX_Y) : 0.);
															fprintf(stream2,"%c%f", delim, maxAngleXY_Z+minAngleXY_Z > 0.0 ? (maxAngleXY_Z-minAngleXY_Z)/(maxAngleXY_Z+minAngleXY_Z) : 0.);
														}
#endif
													}													
				

														
														if(this->cmfd.bMinXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c%d", delim, int(minXYZ));
#endif
														}

														if(this->cmfd.bMedianXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c%f", delim, medianXYZ);
#endif
														}

														if(this->cmfd.bMeanXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c%f", delim, meanXYZ);
#endif
														}

														if(this->cmfd.bMaxXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c%d", delim, int(maxXYZ));
#endif
														}

														if(this->cmfd.bPolarizationXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c%f", delim, maxXYZ-minXYZ > 0.0 ? 0.5*(maxXYZ+minXYZ)/(maxXYZ-minXYZ) : 0.5);
#endif
														}

														if(this->cmfd.bInvPolarizationXYZ)
														{
#if USE_MULTIPARAM
															fprintf(stream2,"%c%f", delim, maxXYZ+minXYZ > 0.0 ? (maxXYZ-minXYZ)/(maxXYZ+minXYZ) : 0.);
#endif
														}


													///////////////////////////////////////////////////
													
													
													if(this->cmfd.shPeriodFlag != this->cmfd.shPeriodFlagHalfOfDay || 
														(this->cmfd.shPeriodFlag == this->cmfd.shPeriodFlagHalfOfDay && CurrentHour >= 24 - mean_hour))
													{
														bNewStringDone = true;
														fprintf(stream2,"\n");
													}
													else
														bNewStringDone = false;




												}
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
						}
						i++;
					}
				}
			}
			fclose(stream2);
			fclose(stream);



		   // Advance the current position of the
		   // progress bar by the increment. 
		   SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
		}
		else
		{
			toRead = true;
			MessageBox(0,"toRead = false","",0);
		}
	}
	if(this->cmfd.bMeanPerDay)
	{
		for (ii = 0; ii < SecsPerDay; ii++)
		{
			if (vn[ii] != 0)
			{
				//vmeanX[ii] /= vn[ii];
				//vmeanY[ii] /= vn[ii];
				//vmeanZ[ii] /= vn[ii];
				for (size_t iInput = 0; iInput < nInputs; iInput++)
				{
					vmean[iInput][ii] /= vn[ii];
				}
			}
		}

		char mean_per_day_path[2048];
		sprintf(mean_per_day_path, "%s\\CommonFiles\\mean_per_day.txt", this->directory);
		stream = fopen(mean_per_day_path,"wt");
		if(!stream)
		{
			MessageBox(0, mean_per_day_path, "Сan not open file\n", MB_OK | MB_ICONEXCLAMATION);
			return;
		}

		fprintf(stream,"%s", "time");
		for (size_t iInput = 0; iInput < nInputs; iInput++)
		{
			if(iInput < (*this->pnames_of_colomns).size())
				fprintf(stream,"%c\"%s %s\"",delim,"среднесуточный ход вариаций", 
				(*this->pnames_of_colomns)[iInput+1].c_str());
			else
				fprintf(stream,"%c\"%s param%02d\"",delim,"среднесуточный ход вариаций", 
				iInput);
		}
		fprintf(stream,"%c\"%s\"",delim,"среднесуточный ход вариаций модуля");
		fprintf(stream,"\n");

		for (ii = 0; ii < SecsPerDay; ii++)
		{
			if (vn[ii] != 0)
			{
				//fprintf(stream,"%lf%c%lf%c%lf%c%lf\n", 
				//	vmeant[ii], delim, 
				//	vmeanX[ii], delim, vmeanY[ii], delim, vmeanZ[ii]);
				fprintf(stream,"%lf", vmeant[ii]);
				double module = 0.0;
				for (size_t iInput = 0; iInput < nInputs; iInput++)
				{
					fprintf(stream,"%c%lf", delim, vmean[iInput][ii]);
					module += vmean[iInput][ii] * vmean[iInput][ii];
				}
				fprintf(stream,"%c%lf", delim, sqrt(module));
				fprintf(stream,"\n");
			}
		}
		fclose(stream);

		if(vn)
			HeapFree(GetProcessHeap(), 0,vn);
/*		if(vt)
			HeapFree(GetProcessHeap(), 0,vt);
		if(vin)
			Free2DMat(vin);*/

		if(vmean)
			Free2DMat(vmean);
	}

	if (input) delete[] input;

	if(vIN)
		Free2DMat(vIN);
#if USE_MULTIPARAM
	if(vYZ)
		HeapFree(GetProcessHeap(), 0,vYZ);
	if(vZX)
		HeapFree(GetProcessHeap(), 0,vZX);
	if(vXY)
		HeapFree(GetProcessHeap(), 0,vXY);
#endif
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

	if (mean_val)  delete[] mean_val;
	if (mean_val2) delete[] mean_val2;
	if (mean_val3) delete[] mean_val3;
	if (mean_val4) delete[] mean_val4;

	if (mju2)  delete[] mju2;
	if (mju3)  delete[] mju3;
	if (mju4)  delete[] mju4;

	//double meanX2, meanY2, meanZ2;
	if (median_val)  delete[] median_val;
	if (min_val)  delete[] min_val;
	if (max_val)  delete[] max_val;

	if(vmeant)
		HeapFree(GetProcessHeap(), 0,vmeant);

  DestroyWindow(hwndPB);
/*
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
*/
	MessageBox(0, "", "Конверт завершён", 
		MB_OK | MB_ICONINFORMATION);

}




void CommonMeanFileDialog::cutting_of_output_file(
	FILE * stream2,
	int jj, // rows on excel file
	int kk, // pages on excel file
	char *directory_out,
	char *filename_out,
	char *filename_out_temp,
	int nPribor,
	char *sFormat,
	char *sPeriod,
	char *sExt

		)
{
	jj++;
	if (this->cmfd.bToCutPagesExcel && jj > 65536 - 1)
	{
		jj = 0;
		kk++;

		fclose(stream2);


		wsprintf(filename_out_temp,"%d_c%s%s_%02d_%02d_%02d_%02d_%02d_%02d.part%d%s",
			nPribor,												
			sFormat,
			sPeriod,
			this->cmfd.startYear-(this->cmfd.startYear/100)*100, this->cmfd.startMonth, this->cmfd.startDay, 
			this->cmfd.finishYear-(this->cmfd.finishYear/100)*100, this->cmfd.finishMonth, this->cmfd.finishDay,
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
}
bool CommonMeanFileDialog::TestAndStartHandlingOfInputFiles(HWND hDlg, bool toCorrect_time_sequence)
{
	char startDate[15],
		finishDate[15];

	bool result_of_time_sequence = true;

	this->cmfd.nFilesInDirectory = SendDlgItemMessage( hDlg, IDC_LIST2, LB_GETCOUNT, 0, 0);
	//память не освобождена!!!!
	this->cmfd.vFileNameLengthes = (int *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( int ) *  this->cmfd.nFilesInDirectory);
	this->cmfd.vFileNames = (char **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( char * ) *  this->cmfd.nFilesInDirectory);
	for (int iFile = 0; iFile < this->cmfd.nFilesInDirectory; iFile++)
	{
		this->cmfd.vFileNameLengthes[iFile] = SendDlgItemMessage( hDlg, 
			IDC_LIST2, LB_GETTEXTLEN, (WPARAM) iFile, 0)+1;
		this->cmfd.vFileNames[iFile] = (char *)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		sizeof( char ) * this->cmfd.vFileNameLengthes[iFile]);

		if (LB_ERR!=SendDlgItemMessage( hDlg, 
			IDC_LIST2, LB_GETTEXT, (WPARAM) iFile, (LPARAM)(this->cmfd.vFileNames[iFile])))
		{
		}
		else
		{
		}
	}
	this->cmfd.nHowUseFilePath = 2;

	double *input; 
	size_t nInputs = cols-1;

	input = new double[nInputs+1];
	if (input == NULL)
	{
		MessageBox(0, "input - Not enough memory",
			"createCommonFile()", 0);
		return true;

	}

	if(this->cmfd.thisIsLocalTime)
	{
		// 
		BOOL bTranslated;
		this->cmfd.localTimeOffsetHours = 
			(short)GetDlgItemInt(hDlg, IDC_EDIT_LOCAL_TIME_OFFSET, &bTranslated, false);
		if (!bTranslated)
			this->cmfd.localTimeOffsetHours = 0;
	}

	const unsigned int n = 2048;
	char szPath_in[n];
	char szPath_out[n];
	char directory_out[n];

	double 
		t_excel,
		t0_excel = datenum(1900,1,1,0,0,0,0)-2;
	double test_t,test_t0;
	int X,Y,Z;

	double t_start, t_stop;


	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 



	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(this->cmfd.hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(0, PROGRESS_CLASS,
				(LPSTR) NULL, WS_CHILD | WS_VISIBLE,
				0, 0,
				//rcClient.left, rcClient.bottom,
				rcClient.right, cyVScroll, 
				this->cmfd.hwndParent, (HMENU) 0, hInst, NULL); 

	// Set the range and increment of the progress
	// bar. 

	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, this->cmfd.nFilesInDirectory)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
	FILE *stream;
	int y, mo, d, h, mi, s, milli;
	bool start = true;

	double epsilon = 0.1 /(3600.0*24.0);
	FILE *stream2;
	if (toCorrect_time_sequence)
	{
		sprintf(directory_out, "%s\\CorrectedTimeSequenceFiles", directory);
		CreateDirectory(directory_out,NULL);
	}

	for (int iFile = 0; iFile < this->cmfd.nFilesInDirectory; iFile++)
	{
		sprintf(szPath_in, "%s\\%s", directory, this->cmfd.vFileNames[iFile]);

		if ((stream = fopen(szPath_in,"rt")) == NULL)
		{
			printf("Error fopen szPath_in = %s\n", szPath_in);
		}
		else
		{
			if (toCorrect_time_sequence)
			{
				sprintf(szPath_out, "%s\\%s", directory_out, this->cmfd.vFileNames[iFile]);
				if ((stream2 = fopen(szPath_out,"wt")) == NULL)
				{
					printf("Error fopen szPath_out = %s\n", szPath_out);
				}
			}
			//////////////////////////////////////
			double delta_impuls_time = 10./86400.;//инициализируем межимпульсный интервал как 10 сек.

		
			unsigned int i = 0;
			unsigned int i_old = 0;
			while (!feof(stream))
			{
				char* ch = fgets(szBuff,n,stream);
				if( ch != NULL && strlen(szBuff) > 1)
				{
					
					int _y;
					int rez = -1;
					int rezWaited = -1;

					switch (this->cmfd.fileFormat)
					{
					case 0:
						{
							rez = sscanf(szBuff,"%lf\t%d\t%d\t%d\t%d",
								&t_excel, &X, &Y, &Z);
							rezWaited = 4;
							if(this->cmfd.thisIsLocalTime)
									t_excel -= 
									double(this->cmfd.localTimeOffsetHours) / 24.0;
							datevec(t_excel+t0_excel,y,mo,d,h,mi,s,milli);
						}
						break;
					case 1:
						{
							rez = sscanf(szBuff,"%d.%d.%d %d:%d:%d,%d,%d,%d,%d",
								&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
							rezWaited = 10;
							if (rez != rezWaited)
							{
								rez = sscanf(szBuff,"%d:%d:%d,%d:%d:%d,%d,%d,%d,%d",
									&d, &mo, &_y, &h, &mi, &s, &milli, &X, &Y, &Z);
							}

							if (this->cmfd.nHowUseFilePath == 1)
								y = _y+ (y/100)*100;
							if (this->cmfd.nHowUseFilePath == 2)
								y = _y + 2000;
						}
						break;
					case 2:
						{
							size_t bytes_line = strlen(ch);
							vector<string> line_strings;
							ParseLine(i, szBuff, title, bytes_line, dd,  NULL, &line_strings, NULL, input);
							
							const char * time_string = line_strings.begin()->c_str(); 				
							double t;

							if (ParseTimeString(time_string, 
								this->cmfd.timeFormat, 
								this->cmfd.thisIsLocalTime,	
								this->cmfd.localTimeOffsetHours,
								y, mo, d, h, mi, s, milli, t))
							{
								if (t != 0.0) rez = rezWaited = 1;
							}
						}
						break;
					}	
			
					if (rez == rezWaited && rez != EOF)
					{
						if (start)//(i==0 && iFile==0)
						{
							start = false;
							switch (this->cmfd.fileFormat)
							{
							case 0:
								{
									test_t0 = t_excel + t0_excel;
								}
								break;
							case 1:
							case 2:
								{
									test_t0 = datenum(y,mo,d,h,mi,s,milli);
								}
								break;
							}
							t_start = test_t0;
							strcpy(this->szBuff_old, this->szBuff);
							i_old = i;
							if (toCorrect_time_sequence)
							{
								fprintf(stream2, this->szBuff);
							}
						}
						else
						{
							switch (this->cmfd.fileFormat)
							{
							case 0:
								{
									test_t = t_excel + t0_excel;
								}
								break;
							case 1:
							case 2:
								{
									test_t = datenum(y,mo,d,h,mi,s,milli);
								}
								break;
							}
							if (test_t > test_t0 + epsilon)
							{
								test_t0 = test_t;
								strcpy(this->szBuff_old, this->szBuff);
								if (toCorrect_time_sequence)
								{
									fprintf(stream2, this->szBuff);
								}
								if (this->to_disp_msgbox == 1)
								{
									this->to_disp_msgbox = 0;
									char errstr[2048];
//printf(szPath_in);
									sprintf(errstr,
										"Конец ошибочной временной последовательности\n\n"
										"номер предыдущей строки = %d\n%s\n"
										"номер текущей строки = %d\n%s\n"
										"имя файла = %s\n"
										"разница=%d секунд\n",

										i_old+1, szBuff_old, 
										i+1, szBuff, 
										szPath_in, 
										int((test_t0 - test_t)*3600.*24.));
//printf(szPath_in);
									MessageBox(0, errstr, "createCommonFile",
											MB_OK | MB_ICONINFORMATION);
//printf(szPath_in);
								}
								i_old = i;
							}
							else
							{
								if (!toCorrect_time_sequence)
								{
									char errstr[2048];
									sprintf(errstr,
										"Ошибка временной последовательности\n\n"
										"номер предыдущей строки = %d\n%s\n"
										"номер текущей строки = %d\n%s\n"
										"имя файла = %s\n"
										"разница=%d секунд\n"
										"\n"
										"Нажмите \"Повтор\" для поиска конца\n"
										"ошибочной временной последовательности", 

										i_old+1, szBuff_old, 
										i+1, szBuff, 
										szPath_in, 
										int((test_t0 - test_t)*3600.*24.));


									result_of_time_sequence = false;

									int msgbox_rez_1;
									switch (to_disp_msgbox)
									{
									case 0:
										{
											msgbox_rez_1 = MessageBox(0, errstr, "createCommonFile",
												MB_ABORTRETRYIGNORE | MB_ICONINFORMATION);
											switch(msgbox_rez_1)
											{
											case IDABORT://прерываем выполнение функции
												DestroyWindow(hwndPB);
												return false;
											case IDRETRY:// пробуем найти конец неправильной временной последовательности
												to_disp_msgbox = 1;
												break;
											case IDIGNORE://ничего не меняем
												break;
											}
										}
										break;
									default:
										break;
									}
								}
							}
							t_stop = test_t;
						}
					}
					else
					{
						printf("Error of parsing string %s\n", szBuff);
					}
					i++;
				}
			}					
			fclose(stream);
			if (toCorrect_time_sequence)
				fclose(stream2);
		}
		SendMessage(hwndPB, PBM_STEPIT, 0, 0);
	}
	DestroyWindow(hwndPB);
		
	if (toCorrect_time_sequence)
	{
		char str[1024];
		sprintf(str, "Исправленные файлы созданы в директории\n%s", directory_out);
		MessageBox(this->hWnd, str, "", MB_OK);
		return true;
	}
	if (!result_of_time_sequence)
		return false;

	if (start)
	{
		MessageBox(hWnd, "Error: input files did not opened", "TestInputFiles", MB_OK | MB_ICONEXCLAMATION);
		printf("Error files not opened\n");
	}
	else
	{
		datevec(t_start,y,mo,d,h,mi,s,milli);
		this->cmfd.startYear = y;
		this->cmfd.startMonth = mo;
		this->cmfd.startDay = d;

		datevec(t_stop,y,mo,d,h,mi,s,milli);
		this->cmfd.finishYear = y;
		this->cmfd.finishMonth = mo;
		this->cmfd.finishDay = d;


		wsprintf(startDate,"%d/%02d/%02d", this->cmfd.startYear, this->cmfd.startMonth, this->cmfd.startDay);
		wsprintf(finishDate,"%d/%02d/%02d", this->cmfd.finishYear, this->cmfd.finishMonth, this->cmfd.finishDay);
		char str[1023];
		sprintf(str, "Do you agree with this start finish date:\nstart date: %s\nfinish date: %s \n\nPress NO to use your own start finish date", startDate, finishDate);
		int respond = MessageBox( hDlg, str, "Start Finish Date",
					MB_YESNOCANCEL | MB_ICONINFORMATION );


		if (respond == IDYES)
		{
			SetDlgItemText(hDlg,IDC_EDIT_START_DATE, startDate);
			SetDlgItemText(hDlg,IDC_EDIT_FINISH_DATE, finishDate);
		}
		else
		{
			if (respond == IDNO)
			{
				SendMessage(hDlg,WM_COMMAND, IDC_TEST_START_FINISH_DATE,0);
			}
		}
		if (respond == IDYES || respond == IDNO)
		{
			switch (this->cmfd.fileFormat)
			{
			case 0:
			case 1:
				{
					this->cmfd.nHowUseFilePath = 2;
					this->createCommonFile();
				}
				break;
			case 2:
				{
					this->cmfd.nHowUseFilePath = 2;
					this->createCommonFile2(nInputs);
				}
				break;
			}
		}
	}
	if (input) delete[] input;
	return result_of_time_sequence;
}
void CommonMeanFileDialog::UseWholeDirectory(HWND hDlg)
{
	SetDlgItemText(hDlg,IDC_DIRECTORY2, this->directory);

	strcpy(this->szPath,this->directory);
    strcat(this->szPath, "\\*" );
	strcat(this->szPath, this->cmfd.szFileFilter);
	DlgDirList( hDlg, this->szPath, IDC_LIST2, IDC_DIRECTORY2,
                    DDL_READWRITE );
    if (IDOK == MessageBox( hDlg, szPath, "Directory Selected",
                MB_OKCANCEL | MB_ICONINFORMATION ))
	{
		if (!TestAndStartHandlingOfInputFiles(hDlg, false))
		{
			if(MessageBox(0, "Вы хотите автоматически создать копию исходных файлов \nс исправленной временной последовательностью \nвнутри новой папки?", "createCommonFile",
				MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
			{
				TestAndStartHandlingOfInputFiles(hDlg, true);
			}
		}
	}
/*	strcpy(szPath,directory);
	DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                    DDL_DIRECTORY | DDL_DRIVES );*/
}

void CommonMeanFileDialog::UseTheSelectedFile(HWND hDlg)
{

	SetDlgItemText(hDlg,IDC_DIRECTORY2, this->directory);
	SendDlgItemMessage(hDlg, IDC_LIST2, LB_RESETCONTENT,0,0);
	strcat(this->filename, this->cmfd.szFileFilter);
	SendDlgItemMessage(hDlg, IDC_LIST2, LB_ADDSTRING,0,(LPARAM)filename);

    
	/*if (IDOK == MessageBox( hDlg, szPath, "Directory Selected",
                MB_OKCANCEL | MB_ICONINFORMATION ))*/
	{
		if (!TestAndStartHandlingOfInputFiles(hDlg, false))
		{
			if(MessageBox(0, "Вы хотите автоматически создать копию исходных файлов \nс исправленной временной последовательностью \nвнутри новой папки?", "createCommonFile",
				MB_OKCANCEL | MB_ICONINFORMATION) == IDOK)
			{
				TestAndStartHandlingOfInputFiles(hDlg, true);
			}
		}
	}
	/*strcpy(szPath,directory);
	DlgDirList( hDlg, szPath, IDC_LIST2, IDC_DIRECTORY2,
                    DDL_DIRECTORY | DDL_DRIVES );*/
}

void CommonMeanFileDialog::OnCreate(void)
{
	this->to_disp_msgbox = 0;
	this->outputTimeFormat = 0;

	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	this->cmfd.fileFormat = 0;
	this->cmfd.thisIsLocalTime = false;
	this->cmfd.localTimeOffsetHours = 0;
	this->cmfd.delim = '\t';
	this->cmfd.delimID = 0;
	this->cmfd.shPeriodFlag = 4;
			// Parametrs of start finish date dialog data
	this->cmfd.hwndParent = hWnd;
	this->cmfd.nPribor = 1;
	//this->cmfd.shFormatFlag = 0;// not in use here
	/*
			sfddd.startDay = 26;
			sfddd.startMonth = 11;
			sfddd.startYear = 2004;

			sfddd.finishDay = d;
			sfddd.finishMonth = mo;
			sfddd.finishYear = y;
			*/

	this->cmfd.bMin					= false;
	this->cmfd.bMedian				= false;
	this->cmfd.bMean				= true;
	this->cmfd.bDisp				= true;
	this->cmfd.bAsim				= true;
	this->cmfd.bExcess				= true;
	this->cmfd.bMax					= false;
	this->cmfd.bPolarization		= false;
	this->cmfd.bInvPolarization		= false;

	this->cmfd.bMinAngle				= false;
	this->cmfd.bMedianAngle				= false;
	this->cmfd.bMeanAngle				= false;
	this->cmfd.bDispAngle				= false;
	this->cmfd.bMaxAngle				= false;
	this->cmfd.bPolarizationAngle		= false;
	this->cmfd.bInvPolarizationAngle	= false;

	this->cmfd.bMinAngle3				= false;
	this->cmfd.bMedianAngle3			= false;
	this->cmfd.bMeanAngle3				= false;
	this->cmfd.bDispAngle3				= false;
	this->cmfd.bMaxAngle3				= false;
	this->cmfd.bPolarizationAngle3		= false;
	this->cmfd.bInvPolarizationAngle3	= false;

	this->cmfd.bMinAngle4				= false;
	this->cmfd.bMedianAngle4			= false;
	this->cmfd.bMeanAngle4				= false;
	this->cmfd.bDispAngle4				= false;
	this->cmfd.bMaxAngle4				= false;
	this->cmfd.bPolarizationAngle4		= false;
	this->cmfd.bInvPolarizationAngle4	= false;

	this->cmfd.bMinXYZ					= false;
	this->cmfd.bMedianXYZ				= false;
	this->cmfd.bMeanXYZ					= false;
	this->cmfd.bDispXYZ					= false;
	this->cmfd.bMaxXYZ					= false;
	this->cmfd.bPolarizationXYZ			= false;
	this->cmfd.bInvPolarizationXYZ		= false;

	this->cmfd.bMeanPerDay				= false;
	this->cmfd.bReverseAngles			= false;
	this->cmfd.bToCutPagesExcel			= false;
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
    this->oftcd.bUseWholeDirectory = FALSE;

	this->dd.bTab						= false;
	this->dd.bSpace						= false;
	this->dd.bComma						= false;
	this->dd.bCommaPoint				= false;
	this->dd.bOther						= false;
	this->dd.charOther					= -1;
	this->dd.bUseManyDelimitersAsOne	= false;

	pcells								= new vector<vector<cell> >;
	pnames_of_colomns					= new vector<string>;
	filename							= new char[512];

	n=32000; // length of buffer string line
	szBuff								= new char[n];
	szBuff_old								= new char[n];
	title								= new char[n];
}

bool CommonMeanFileDialog::OpenFileDlg(void)
{
    HRESULT hr = S_OK;
	OPENFILENAME ofn;       // common dialog box structure
	
 			
	TCHAR filter[] =
		TEXT("Comma separated files (*.csv)\0*.csv\0")
		TEXT("Data files (*.dat*)\0*.dat\0")
		TEXT("Text files (*.txt)\0*.txt\0")
		;

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	//
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	//
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.hInstance         = hInst;
   
	ofn.lCustData         = (LPARAM)&this->oftcd;
    ofn.lpfnHook          = DlgProcOpenFilesToCommon;
    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_OPEN_FILES_TO_COMMON);
	ofn.Flags = 
		OFN_PATHMUSTEXIST 
		| OFN_FILEMUSTEXIST
		| OFN_EXPLORER 
		| OFN_ENABLETEMPLATE 
		| OFN_ENABLEHOOK 
		| OFN_ALLOWMULTISELECT
		;

	if (GetOpenFileName(&ofn)==TRUE)
	{
		if (ofn.lpstrFile != NULL)
		{
			this->cmfd.nFilterIndex = ofn.nFilterIndex;
			switch(this->cmfd.nFilterIndex)
			{
			case 1:
				strcpy(this->cmfd.szFileFilter, ".csv");
				break;
			case 2:
				strcpy(this->cmfd.szFileFilter, ".dat");
				break;
			case 3:
				strcpy(this->cmfd.szFileFilter, ".txt");
				break;
			}
			strcpy(filename, ofn.lpstrFile + ofn.nFileOffset);
			strcpy(directory, ofn.lpstrFile);
			if (ofn.nFileOffset > 1) directory[ofn.nFileOffset-1] = '\0';


		}
		return true;
	}
	else
	{
		DWORD dwErr = CommDlgExtendedError();
		LPVOID lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dwErr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
		);
		char str[255];
		sprintf(str, "Ошибка создания окна выбора файла = %d", dwErr);


		::MessageBox(NULL, (LPCTSTR)lpMsgBuf, str, MB_OK);
		switch(dwErr)
		{
		case CDERR_DIALOGFAILURE :
			MessageBox(0,"The dialog box could not be created. ","CommDlgExtendedError",0);
			break;
		case CDERR_FINDRESFAILURE :
			MessageBox(0,"The common dialog box function failed to find a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_INITIALIZATION :
			MessageBox(0,"The common dialog box function failed during initialization. This error often occurs when sufficient memory is not available","CommDlgExtendedError",0);
			break;
		case CDERR_LOADRESFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_LOADSTRFAILURE :
			MessageBox(0,"The common dialog box function failed to load a specified string.","CommDlgExtendedError",0);
			break;
		case CDERR_LOCKRESFAILURE :
			MessageBox(0,"The common dialog box function failed to lock a specified resource.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMALLOCFAILURE :
			MessageBox(0,"The common dialog box function was unable to allocate memory for internal structures.","CommDlgExtendedError",0);
			break;
		case CDERR_MEMLOCKFAILURE :
			MessageBox(0,"The common dialog box function was unable to lock the memory associated with a handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHINSTANCE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding instance handle.","CommDlgExtendedError",0);
			break;
		case CDERR_NOHOOK :
			MessageBox(0,"The ENABLEHOOK flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a pointer to a corresponding hook procedure.","CommDlgExtendedError",0);
			break;
		case CDERR_NOTEMPLATE :
			MessageBox(0,"The ENABLETEMPLATE flag was set in the Flags member of the initialization structure for the corresponding common dialog box, but you failed to provide a corresponding template.","CommDlgExtendedError",0);
			break;
		case CDERR_REGISTERMSGFAIL :
			MessageBox(0,"The RegisterWindowMessage function returned an error code when it was called by the common dialog box function.","CommDlgExtendedError",0);
			break;
		case CDERR_STRUCTSIZE :
			MessageBox(0,"The lStructSize member of the initialization structure for the corresponding common dialog box is invalid.","CommDlgExtendedError",0);
			break;
		case FNERR_BUFFERTOOSMALL :
			short size;
			memcpy(&size, ofn.lpstrFile, 2);
			char str[1024];
			sprintf(str, "The buffer pointed to by the lpstrFile member of the OPENFILENAME structure is too small for the file name specified by the user. The first two bytes of the lpstrFile buffer contain an integer value specifying the size = %d, in TCHARs, required to receive the full name. ", size);
			MessageBox(0, str,"CommDlgExtendedError",0);
			break;
		case FNERR_INVALIDFILENAME :
			{
				char err_str[255];
				sprintf(err_str, "A file name is invalid.\n%s", ofn.lpstrFile );
				MessageBox(0,err_str,"CommDlgExtendedError",0);
			}
			break;
		case FNERR_SUBCLASSFAILURE :
			MessageBox(0,"An attempt to subclass a list box failed because sufficient memory was not available.","CommDlgExtendedError",0);
			break;

		}
	}
	// Display the Open dialog box. 
	return false;
}
