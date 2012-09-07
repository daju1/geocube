_ListViewTab_::_ListViewTab_()
{	
	this->headers = NULL;
	this->items = NULL;
	this->checkings = NULL;
#if !USE_LISTVIEW_STANDART 
	this->editings = NULL;
#endif
	this->hList = NULL;
	rows = 0;
	cols = 0;
}
bool _ListViewTab_::Init(HWND hwndParent, LPVOID lpParam, double xpart0, double xpart_end, double ypart0, double ypart_end, bool use_check_boxes)
{
//printf ("_ListViewTab_::Init 0\n");
	this->hWndParent = hwndParent;
	this->hList = _ListViewTab_::CreateListView(hWndParent, lpParam, xpart0, xpart_end, ypart0, ypart_end);

	if (hList == NULL)
		return false;

	SetFocus(hList);
	ShowWindow(hList, 1);

#if !USE_LISTVIEW_STANDART 
	_ListViewTab_::InitListViewImageLists(hList);
#endif

#if USE_LISTVIEW_STANDART
	DWORD dwExStyle = 0;
	if (use_check_boxes)
		dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;
	else
		dwExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;
		
	//|LVS_EX_ONECLICKACTIVATE

	ListView_SetExtendedListViewStyle(hList, dwExStyle);
#endif

	//--------------------------------------------------------------
	// Subclass the control. 
	/*wpOrigListViewTabWndProc = (WNDPROC) SetWindowLongPtr(hList, 
		GWLP_WNDPROC, (LONG_PTR) ListViewTabWndSubclassProc); 
*/
	//--------------------------------------------------------------
	// Load bitmaps. 
	hbmpChecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_CHECKED)); 
	hbmpUnchecked = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP_UNCHECKED)); 
	//--------------------------------------------------------------
	//--------------------------------------------------------------
	//--------------------------------------------------------------


	headers		= new vector<string>;
	items		= new vector<vector<string> >;
	checkings	= new vector<vector<bool*> >;
#if !USE_LISTVIEW_STANDART 
	editings	= new vector<vector<int> >;
#endif


	return true;
}

_ListViewTab_::~_ListViewTab_(void)
{
}

HWND _ListViewTab_::CreateListView (HWND hWndParent, LPVOID lpParam, double xpart0, double xpart_end, double ypart0, double ypart_end) 
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
#if USE_LISTVIEW_STANDART
	hWndListView = CreateWindow(
		WC_LISTVIEW, 
		"", 
        WS_TABSTOP 
		| WS_CHILD 
		| LVS_REPORT 
		| WS_BORDER 
		| WS_VISIBLE
		| LVS_NOSORTHEADER
		| LVS_SINGLESEL
		| LVS_EDITLABELS
		,
		xpart0 * (rcl.right - rcl.left), 
		ypart0 * (rcl.bottom - rcl.top), 
		(1-xpart0-xpart_end) * (rcl.right - rcl.left), 
		(1-ypart0-ypart_end) * (rcl.bottom - rcl.top), 
		hWndParent, (HMENU)NULL /*ID_LISTVIEW*/, hInst, lpParam); 
#else
	hWndListView = CreateWindowEx (
		WS_EX_CLIENTEDGE 
		| LVS_EX_FULLROWSELECT, 
		WC_LISTVIEW, 
		"", 
        WS_TABSTOP 
		| WS_CHILD 
		| LVS_REPORT 
		| WS_BORDER 
		| WS_VISIBLE
		| LVS_NOSORTHEADER
		| LVS_SINGLESEL
		| LVS_ICON 
		| LVS_OWNERDATA 
		| LVS_OWNERDRAWFIXED 
		| LBS_OWNERDRAWVARIABLE
		,
		xpart0 * (rcl.right - rcl.left), 
		ypart0 * (rcl.bottom - rcl.top), 
		(1-xpart0) * (rcl.right - rcl.left), 
		(1-ypart0) * (rcl.bottom - rcl.top), 
		hWndParent, (HMENU)NULL /*ID_LISTVIEW*/, hInst, lpParam); 
#endif


	if (hWndListView == NULL) 
		return NULL; 
}

BOOL _ListViewTab_::InitListViewImageLists(HWND hWndListView) 
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


BOOL _ListViewTab_::InitListViewColumns(HWND hWndListView, vector<string> * headers, bool add_combo) 
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

        switch ( iCol)
		{
		case 0:
#if USE_LISTVIEW_STANDART
			lvc.cx = 150;     // width of column in pixels
			lvc.fmt = LVCFMT_LEFT;
#else
			/*if (m_first_colomn_20_pixels)
			{1
				lvc.cx = 20;     // width of column in pixels
				lvc.fmt = LVCFMT_CENTER;
			}
			else*/
				lvc.cx = 150;     // width of column in pixels
				lvc.fmt = LVCFMT_LEFT;
#endif
			//lvc.fmt = LVCFMT_RIGHT; // right-aligned column		                         
			//lvc.fmt = LVCFMT_LEFT;  // left-aligned column
			break;
		default:
			lvc.cx = 150;     // width of column in pixels
			lvc.fmt = LVCFMT_LEFT;  // left-aligned column
			break;
		}

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
		{/*
			RECT ComboBoxRect = GetComboBoxRect(&rcHD);

			hWndComboBox = CreateWindow ("COMBOBOX", "", 
				WS_CHILD | WS_TABSTOP | WS_VISIBLE | CBS_DROPDOWNLIST, 
				ComboBoxRect.left, 
				ComboBoxRect.top, 
				ComboBoxRect.right, 
				ComboBoxRect.bottom,			
				hwndHD, 
				(HMENU)NULL,//IDCOMBO,
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
			SendMessage(hWndComboBox, CB_SETCURSEL, 0, 0);

			coldata->hwndComboBox = hWndComboBox;
			//--------------------------------------------------------------
			// Subclass the control. 
			wpOrigComboBoxWndProc = (WNDPROC) SetWindowLongPtr(hWndComboBox, 
				GWLP_WNDPROC, (LONG_PTR) ComboBoxWndSubclassProc);
	
			SetWindowLongPtr(hWndComboBox, GWLP_USERDATA,(LONG_PTR)iCol);
			//--------------------------------------------------------------*/
		}
				
				
		HDITEM hdm; 
		hdm.mask=HDI_LPARAM; 			
		hdm.lParam=(LPARAM)coldata;				
		Header_SetItem(hwndHD,iCol,&hdm); 
    } 
	return TRUE; 
} 

bool _ListViewTab_::OnNotify(LPARAM lParam)
{
	bool to_update_views = false;
	switch (((LPNMHDR) lParam)->code)
	{
#if !USE_LISTVIEW_STANDART 
	case HDN_ITEMCLICK:
		{	
//printf("HDN_ITEMCLICK\n");
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
#endif
#if !USE_LISTVIEW_STANDART 
	case NM_CLICK :
		{
//printf("_ListViewTab_::OnNotify NM_CLICK\n");
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;

			int  r = lpnmitem->iItem;

			int  c = lpnmitem->iSubItem;
			bool check_not_clicked = true;
			if (r >= 0 && (*checkings)[r][c])
			{
				RECT rcItem;
				RECT rcIcon;
				
				ListView_GetSubItemRect(hList, r, c,
					//LVIR_SELECTBOUNDS,
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
					if ((*checkings)[r][c])
					{
						if (*(*checkings)[r][c])
						{
							*(*checkings)[r][c] = false;
						}
						else
						{
							*(*checkings)[r][c] = true;
						}
					}
					to_update_views = true;
					printf("to_update_views = true;\n");
				}

				RECT rcClient;
				GetClientRect(hList, &rcClient);
				InvalidateRect(hList, &rcClient, TRUE);
			}

			if (r >= 0 && (*editings)[r][c] && check_not_clicked )
			{
				RECT rcItemLabel;
				RECT rcList;
				RECT rcEdit;

				ListView_GetSubItemRect(hList, r, c,
					LVIR_LABEL,
					&rcItemLabel);				
				

				GetWindowRect(hList, &rcList);

				//Получаем дескриптор заголовка
				HWND hwndHD = GetDlgItem(hList, 0); 
				
				rcEdit.left = rcList.left + rcItemLabel.left+2 /*+ (c > 0 ? XBITMAP3 + 6 : 0)*/;
				rcEdit.top = rcList.top + rcItemLabel.top+3;

				rcEdit.right = min(rcItemLabel.right, rcList.right-rcList.left) - rcItemLabel.left - 3/*- (c > 0 ? XBITMAP3 + 6 : 0)*/; //width
				rcEdit.bottom = rcItemLabel.bottom -	rcItemLabel.top-1;
				
				hWndEdit = CreateWindow ("EDIT", "", 
					WS_TABSTOP | WS_POPUP  | WS_VISIBLE, 
					rcEdit.left, 
					rcEdit.top, // rcItem.bottom + (list view header height)
					rcEdit.right, 
					rcEdit.bottom, 
					hWndParent, 
					NULL,
					hInst, NULL); 

				edit_r = r;
				edit_c = c;
				
				ShowWindow(hWndEdit, 1);


				//--------------------------------------------------------------
				// Subclass the control. 
				wpOrigEdit_WndProc = (WNDPROC) SetWindowLongPtr(hWndEdit, 
					GWLP_WNDPROC, (LONG_PTR) EditWnd_SubclassProc); 

				SetWindowLongPtr(hWndEdit, GWLP_USERDATA,(LONG_PTR)this);
				//--------------------------------------------------------------

				SetWindowText(hWndEdit, (*items)[r][c].c_str() );

			}
		}
		break;
#else
	case NM_CLICK :
		{
//printf("_ListViewTab_::OnNotify NM_CLICK\n");
			LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) lParam;

			int r = lpnmitem->iItem;
			int c = lpnmitem->iSubItem;
		}
		break;
#endif
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
#if USE_LISTVIEW_STANDART 
	case LVN_GETDISPINFO:
		{	
			NMLVDISPINFO * plvdi = ((NMLVDISPINFO *)lParam);
			if (plvdi->item.iItem < (*items).size() && plvdi->item.iSubItem < (*items)[plvdi->item.iItem].size())
			{
				plvdi->item.pszText = (char *)(*items)[plvdi->item.iItem][plvdi->item.iSubItem].c_str();
				if(plvdi->item.iItem < rows && (*checkings)[plvdi->item.iItem][0])
				{
					bool check = ListView_GetCheckState(hList, plvdi->item.iItem);
					if (*(*checkings)[plvdi->item.iItem][0] != check)
					{
						*(*checkings)[plvdi->item.iItem][0] = check;
                        to_update_views = true;
					}
				}
			}
			else
			{
				printf("LVN_GETDISPINFO error\n");
				printf("plvdi->item.iItem = %d\t(*items).size() = %d\n", plvdi->item.iItem, (*items).size());
				if (plvdi->item.iItem < (*items).size())
				{
					printf("plvdi->item.iSubItem = %d\t(*items)[plvdi->item.iItem].size() = %d\n", plvdi->item.iSubItem, (*items)[plvdi->item.iItem].size());
				}

			}
		}
		break;
#else
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
#endif
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
			printf("LVN_ENDLABELEDIT plvdi->item.mask = %d plvdi->item.mask & LVIF_TEXT = %d\n", plvdi->item.mask, plvdi->item.mask & LVIF_TEXT);
			if(plvdi->item.mask & LVIF_TEXT && plvdi->item.pszText)
			{
				printf("plvdi->item.pszText = \"%s\"\n", plvdi->item.pszText);
				printf("plvdi->item.iItem = %d\n", plvdi->item.iItem);
				printf("plvdi->item.iSubItem = %d\n", plvdi->item.iSubItem);
				//strcpy((char*)(*items)[plvdi->item.iItem][plvdi->item.iSubItem].data(), plvdi->item.pszText);
				(*items)[plvdi->item.iItem][plvdi->item.iSubItem] = plvdi->item.pszText;
			}
		}
		break;

	}
	return to_update_views;
}
#if !USE_LISTVIEW_STANDART 
void _ListViewTab_::OnDrawItem(LPDRAWITEMSTRUCT lpdis)
{
	if (lpdis->hwndItem == hList)
	{
		// Draw the bitmap and text for the list box item. Draw a 
		// rectangle around the bitmap if it is selected. 
		
		switch (lpdis->itemAction) 
		{ 
		case ODA_DRAWENTIRE: 
			{
				int c;

				//Затем в MyListCtrl.cpp в DrawItem (переопределение события WM_DRAWITEM)
				//рисуются все айтемы с сабайтемами, 
				
				// Display the bitmap associated with the item.

				
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ 
				//checkbox'ы рисуются так:
				
				hdcMem = CreateCompatibleDC(lpdis->hDC); 

				int r = lpdis->itemID;
				//int ti = SendMessage(hList, LVM_GETTOPINDEX, 0, 0);

				if(r >= 0)
				{
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					
					// Display the text associated with the item. 
					for (c = 0; c < cols; c++)
					{
						RECT rcItemBounds;						
						ListView_GetSubItemRect(hList, r, c,
							LVIR_BOUNDS, 
							&rcItemBounds);	

						RECT rcItemLabel;						
						ListView_GetSubItemRect(hList, r, c,
							LVIR_LABEL,
							&rcItemLabel);									
																		
						{
							HDITEM hdm; 
							hdm.mask=HDI_LPARAM; 									
							hdm.lParam=0; 
							

							//Получим стиль заголовка колонки 
							HWND hwndHD = ListView_GetHeader(hList); 
							Header_GetItem(hwndHD, c, &hdm);
							
							//Установим стиль заголовка колонки 
							LPCOLOMNDATA coldata = (LPCOLOMNDATA )hdm.lParam;
							COLORREF color;
							if (coldata)
							{
								color = coldata->color;
							}
							else color = RGB(255,255,255);
/*#if HEADER_IN_FIRST_ROW
							if (r == 0)
								color = RGB(200, 200, 200);
#endif*/
							HBRUSH hbrush = CreateSolidBrush(color);
							HBRUSH hbrushOld = (HBRUSH__ *)SelectObject(lpdis->hDC, hbrush);

							FillRect(lpdis->hDC, &rcItemBounds, hbrush);

							SelectObject(lpdis->hDC, hbrushOld);
							DeleteObject(hbrush);
						}															


						HFONT fontold, fontnewBold, fontnewNotBold;

						fontnewBold = CreateFont(16,0,0,0,600,0,0,0,DEFAULT_CHARSET,
							OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,FF_DONTCARE,
							"Times New Roman"
							);	

						fontnewNotBold = CreateFont(16,0,0,0,200,0,0,0,DEFAULT_CHARSET,
							OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
							DEFAULT_QUALITY,FF_DONTCARE,
							"Times New Roman"
							);	

						if ((*checkings)[r][c])
							x = rcItemBounds.left + XBITMAP3 + 6;
						else
							x = rcItemBounds.left;

						if ((*checkings)[r][0])
						{
							if ( *(*checkings)[r][0])
								fontold = (HFONT__ *)SelectObject(lpdis->hDC,fontnewBold);
							else
								fontold = (HFONT__ *)SelectObject(lpdis->hDC,fontnewNotBold);
						}
						else
							fontold = (HFONT__ *)SelectObject(lpdis->hDC,fontnewNotBold);

						GetTextMetrics(lpdis->hDC, &tm); 
						y = (lpdis->rcItem.bottom + lpdis->rcItem.top - tm.tmHeight) / 2;

							
						long dx = rcItemLabel.right - x;

						strcpy(tmp_str, (*items)[r][c].c_str());	
						int slen = (int)strlen((*items)[r][c].c_str());
						int real_strlen = slen;

						bool first_tri_points = true;

						do
						{
							SIZE sz;						
							if (!GetTextExtentPoint32(lpdis->hDC,           // handle to DC
								tmp_str,  // text string
								real_strlen,      // characters in string
								&sz      // string size
								))
							{
							}

							if (sz.cx > dx)
							{
								if (first_tri_points)
								{
									real_strlen += 2;
									first_tri_points = false;
								}
								else
								{
									real_strlen--;
									if(real_strlen <= 0)
										break;
								}
								tmp_str[real_strlen] = '\0';
								if (real_strlen > 1) tmp_str[real_strlen-1]='.';
								if (real_strlen > 2) tmp_str[real_strlen-2]='.';
								if (real_strlen > 3) tmp_str[real_strlen-3]='.';

							}
							else
							{
								break;
							}

						}
						while(true);
						
						TextOut(lpdis->hDC, 
							x,
							y, 
							tmp_str, 
							real_strlen
							);

						SelectObject (lpdis->hDC,fontold);
						DeleteObject (fontnewNotBold);
						DeleteObject (fontnewBold);
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

						if ( (*checkings)[r][c])
						{
							if ( *(*checkings)[r][c])
								hbmpPicture = hbmpChecked;
							else
								hbmpPicture = hbmpUnchecked;

							hbmpOld = (HBITMAP__ *)SelectObject(hdcMem, hbmpPicture); 

							if(!BitBlt(lpdis->hDC, 
								rcItem.left, rcItem.top+0, 
								rcItem.right - rcItem.left, 
								rcItem.bottom - rcItem.top, 
								hdcMem, 0, 0, SRCCOPY)) 
								//ErrorExit("Screen to Compat Blt Failed")
								printf("Screen to Compat Blt Failed\n");

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
#if !HEADER_IN_FIRST_ROW
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
#endif // !HEADER_IN_FIRST_ROW

			}
			break; 
		}
	} 
}

void _ListViewTab_::OnEndEdit()
{
	char buff[255];
	GetWindowText(hWndEdit, buff, 254);
	if (edit_r >= 0 && edit_r < rows
		&& 
		edit_c >= 0 && edit_c < cols)
	{
		//(*items)[edit_r][edit_c].resize(strlen(buff)+1);
		//strcpy((char *)(*items)[edit_r][edit_c].data(), buff);
		(*items)[edit_r][edit_c] = buff;
	}

	DestroyWindow(hWndEdit);
}

#endif
void _ListViewTab_::UpdateView(void)
{
	if (hList)
	{
		RECT rect;
		GetClientRect(hList, &rect);
		InvalidateRect(hList, &rect, true);
	}
}

void _ListViewTab_::SetCols(size_t c)
{
#if USE_LISTVIEW_STANDART 
	if (items && checkings && headers)
#else
	if (items && checkings && editings && headers)
#endif
	{
		this->rows = 0;
		this->cols = c;

		items->		resize(rows);
		checkings->	resize(rows);
#if !USE_LISTVIEW_STANDART 
		editings->	resize(rows);
#endif
		headers->	resize(cols);
		for (int c = 0; c < cols; c++)
		{
			headers->operator	[] (c).resize(32);
		}

		ListView_DeleteAllItems(hList);
		HWND hwndHD = ListView_GetHeader(hList); 
		int nh = Header_GetItemCount(hwndHD);
		for (int n = nh-1; n >= 0; n--)
		{
			Header_DeleteItem(hwndHD,n);
		}
		//###################################################
		_ListViewTab_::InitListViewColumns(hList, headers, true);
		//###################################################
	}
}
#if 0
void _ListViewTab_::resize(size_t r, size_t c)
{
#if USE_LISTVIEW_STANDART 
	if (items && checkings && headers)
#else
	if (items && checkings && editings && headers)
#endif
	{
		this->rows = r;
		this->cols = c;

		items->		resize(rows);
		checkings->	resize(rows);
#if !USE_LISTVIEW_STANDART 
		editings->	resize(rows);
#endif
		headers->	resize(cols);
		for (int c = 0; c < cols; c++)
		{
			headers->operator	[] (c).resize(32);
		}

		for (int r = 0; r < rows; r++)
		{
			items->operator		[] (r).resize(cols);
			checkings->operator [] (r).resize(cols);
#if !USE_LISTVIEW_STANDART 
			editings->operator	[] (r).resize(cols);
#endif

			for (int c = 0; c < cols; c++)
			{
				(*items)[r][c] .resize(256);

				switch (c)
				{
				case 0:
					{
						(*checkings)[r][c] = NULL;
#if !USE_LISTVIEW_STANDART
						(*editings)[r][c] = 0;
#endif
					}
					break;
				default:
					{
						(*checkings)[r][c] = NULL;
#if !USE_LISTVIEW_STANDART
						(*editings)[r][c] = 1;
#endif
					}
				}
			}
		}
		//###################################################
		ListView_DeleteAllItems(hList);
		HWND hwndHD = ListView_GetHeader(hList); 
		int nh = Header_GetItemCount(hwndHD);
		for (int n = nh-1; n >= 0; n--)
		{
			Header_DeleteItem(hwndHD,n);
		}
		//###################################################
		_ListViewTab_::InitListViewColumns(hList, headers, true);
		//###################################################
		LVITEM lvI;
		// Some code to create the list-view control.
		// Initialize LVITEM members that are common to all
		// items. 
#if USE_LISTVIEW_STANDART 
		lvI.mask = LVIF_TEXT | LVIF_PARAM;
#else
		lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE; 
#endif		
		lvI.lParam = 0; 
		lvI.state = 0; 
		lvI.stateMask = 0; 
		// first two empty rows
		// Initialize LVITEM members that are different for each item. 
		for (int index = 0; index < rows; index++)
		{

   			lvI.iItem = index;
#if !USE_LISTVIEW_STANDART 
			lvI.iImage = index;
			lvI.iImage = 0;
#endif
			lvI.iSubItem = 0;
			lvI.pszText = LPSTR_TEXTCALLBACK; // sends an
												// LVN_GETDISP
												// message.									  
			if(ListView_InsertItem(hList, &lvI) == -1)
			{
				char str[255];
				sprintf(str, "error %d %d", index, c);
				MessageBox(0,str,"ListView_InsertItem",0);
				return;
			}
		}
	//printf ("_ListViewTab_::Init end\n");
	}
}
#endif
void _ListViewTab_::MoveItemUp(int context_menu_item)
{
	if (context_menu_item > 0 && context_menu_item < (int)rows)
	{
		for (int c = 0; c < cols; c++)
		{
			bool * tmp_checking = (*checkings)[context_menu_item][c];
			(*checkings)[context_menu_item][c] = (*checkings)[context_menu_item-1][c];
			(*checkings)[context_menu_item-1][c] = tmp_checking;
			
			string tmp_items = (*items)[context_menu_item][c];
			(*items)[context_menu_item][c] = (*items)[context_menu_item-1][c];
			(*items)[context_menu_item-1][c] = tmp_items;

#if !USE_LISTVIEW_STANDART 
			int tmp_editing = (*editings)[context_menu_item][c];
			(*editings)[context_menu_item][c] = (*editings)[context_menu_item-1][c];
			(*editings)[context_menu_item-1][c] = tmp_editing;
#endif
		}
		UpdateView();
	}
}

void _ListViewTab_::MoveItemDown(int context_menu_item)
{
	if (context_menu_item > -1 && context_menu_item < int(rows)-1)
	{
		for (int c = 0; c < cols; c++)
		{
			bool * tmp_checking = (*checkings)[context_menu_item][c];
			(*checkings)[context_menu_item][c] = (*checkings)[context_menu_item+1][c];
			(*checkings)[context_menu_item+1][c] = tmp_checking;
			
			string tmp_items = (*items)[context_menu_item][c];
			(*items)[context_menu_item][c] = (*items)[context_menu_item+1][c];
			(*items)[context_menu_item+1][c] = tmp_items;
			
#if !USE_LISTVIEW_STANDART 
			int tmp_editing = (*editings)[context_menu_item][c];
			(*editings)[context_menu_item][c] = (*editings)[context_menu_item+1][c];
			(*editings)[context_menu_item+1][c] = tmp_editing;
#endif
		}
		UpdateView();
	}
}

void _ListViewTab_::SetHeaderString(size_t c, string s)
{
	if (headers && c < cols)
	{
		(*this->headers)[c] = s;
		char szText[255];
		strcpy(szText, s.c_str());
		//Получаем дескриптор заголовка
		HWND hwndHD = ListView_GetHeader(hList); 		
		HDITEM hdm; 
		hdm.mask = HDI_TEXT;
		Header_GetItem(hwndHD,c,&hdm); 
		hdm.pszText = szText;
		Header_SetItem(hwndHD,c,&hdm); 
	}
}
void _ListViewTab_::SetItemString(size_t r, size_t c, string s)
{
	if (items && r < rows && c < cols && r < (*this->items).size() && c < (*this->items)[r].size())
	{
		(*this->items)[r][c] = s.c_str();
		ListView_Update(hList, r);
	}
	else
	{
		printf("_ListViewTab_::SetItemString() error\n");
		printf("r = %d\trows = %d\n", r, rows);
		printf("r = %d\t(*items).size() = %d\n", r, (*items).size());
		printf("c = %d\tcols = %d\n", c, cols);
		if (r < (*items).size())
		{
			printf("c = %d\t(*items)[r].size() = %d\n", c, (*items)[r].size());
		}
	}
}

string _ListViewTab_::GetItemString(size_t r, size_t c)
{
	string s;
	if (items && r < rows && c < cols && r < (*this->items).size() && c < (*this->items)[r].size())
	{
		(*this->items)[r][c];
		s = (*this->items)[r][c].c_str();
	}
	else
	{
		printf("_ListViewTab_::GetItemString() error\n");
		printf("r = %d\trows = %d\n", r, rows);
		printf("r = %d\t(*items).size() = %d\n", r, (*items).size());
		printf("c = %d\tcols = %d\n", c, cols);
		if (r < (*items).size())
		{
			printf("c = %d\t(*items)[r].size() = %d\n", c, (*items)[r].size());
		}
	}
	return s;
}

void _ListViewTab_::SetColumnWidth(size_t c, int cx)
{
	if (c < cols)
	{
		ListView_SetColumnWidth(hList, c, cx); 	
	}
}

int _ListViewTab_::GetColumnWidth(size_t c, int cx)
{
	if (c < cols)
	{
		return ListView_GetColumnWidth(hList, c); 	
	}
	return 0;
}

LPARAM _ListViewTab_::GetLParam(size_t r)
{
	if (r < rows)
	{
		LVITEM lvI;
		lvI.mask = LVIF_PARAM | LVIF_STATE;
		lvI.iItem = r;
		lvI.iSubItem = 0;
		if (ListView_GetItem(hList, &lvI))
		{
			LPARAM lParam = lvI.lParam;
			return lParam;
		}
	}
	return 0;
}

void _ListViewTab_::AddRow(LPARAM lParam, bool* pbChecked)
{
#if USE_LISTVIEW_STANDART
	if (items && checkings)
#else
	if (items && checkings && editings)
#endif
	{
		items->		push_back(vector<string>());
		checkings->	push_back(vector<bool*>());
#if !USE_LISTVIEW_STANDART 
		editings->	push_back(vector<int>());
#endif
		int r = rows;

		items->operator		[] (r).resize(cols);
		checkings->operator [] (r).resize(cols);
#if !USE_LISTVIEW_STANDART 
		editings->operator	[] (r).resize(cols);
#endif
		for (int c = 0; c < cols; c++)
		{
			(*items)[r][c] .resize(256);

			switch (c)
			{
			case 0:
				{
					(*checkings)[r][c] = pbChecked;
#if !USE_LISTVIEW_STANDART 
					(*editings)[r][c] = 0;
#endif
				}
				break;
			default:
				{
					(*checkings)[r][c] = NULL;
#if !USE_LISTVIEW_STANDART 
					(*editings)[r][c] = 1;
#endif
				}
			}
		}

		LVITEM lvI;
#if USE_LISTVIEW_STANDART 
		lvI.mask = LVIF_PARAM | LVIF_TEXT;
		lvI.pszText = LPSTR_TEXTCALLBACK; // sends an LVN_GETDISP message.									  
#else
		lvI.mask = LVIF_PARAM;
#endif
		lvI.iItem = rows;
		lvI.lParam = lParam;
//#if !USE_LISTVIEW_STANDART 
		//lvI.iImage = rows;
//		lvI.iImage = 1;
//#endif
		lvI.iSubItem = 0;
		ListView_InsertItem(hList, &lvI);
		//************************************
#if USE_LISTVIEW_STANDART 
		if(pbChecked)
		{
			ListView_SetCheckState(hList, rows, *pbChecked);
		}
#endif
		rows++;
	}
}
#if !USE_LISTVIEW_STANDART 
void _ListViewTab_::AddRow(LPARAM lParam,  
						   vector<int> & ColomnsEditing, 
						   vector <bool*> & vpbColomnsChecked)
{

	if (items && checkings && editings && ColomnsEditing.size() == cols && vpbColomnsChecked.size() == cols)
	{
		items->		push_back(vector<string>());
		checkings->	push_back(vector<bool*>());
		editings->	push_back(vector<int>());
		int r = rows;

		items->operator		[] (r).resize(cols);
		checkings->operator [] (r).resize(cols);
		editings->operator	[] (r).resize(cols);
		for (int c = 0; c < cols; c++)
		{
			(*items)[r][c] .resize(256);
			(*checkings)[r][c] = vpbColomnsChecked[c];
			(*editings)[r][c] = ColomnsEditing[c];
		}

		LVITEM lvI;
#if USE_LISTVIEW_STANDART 
		lvI.mask = LVIF_PARAM | LVIF_TEXT;
		lvI.pszText = LPSTR_TEXTCALLBACK; // sends an LVN_GETDISP message.									  
#else
		lvI.mask = LVIF_PARAM;
#endif
		lvI.iItem = rows;
		lvI.lParam = lParam;
		lvI.iSubItem = 0;
		ListView_InsertItem(hList, &lvI);
		//************************************
		rows++;
	}
}
#endif

void _ListViewTab_::EraseRow(size_t r)
{
#if USE_LISTVIEW_STANDART 
	if (items && checkings && r < rows)
#else
	if (items && checkings && editings && r < rows)
#endif
	{
		vector<vector<string> >::iterator i_it = this->items->begin();
		vector<vector<bool*> >::iterator i_ch = this->checkings->begin();
#if !USE_LISTVIEW_STANDART 
		vector<vector<int> >::iterator i_ed = this->editings->begin();
#endif
		for (size_t _r = 0; _r < r; _r++)            
		{
			i_it++;
			i_ch++;
#if !USE_LISTVIEW_STANDART 
			i_ed++;
#endif
		}
		this->items->erase(i_it);
		this->checkings->erase(i_ch);
#if !USE_LISTVIEW_STANDART 
		this->editings->erase(i_ed);
#endif
		ListView_DeleteItem(hList,r);
		rows--;
	}
}


void _ListViewTab_::clear()
{
#if USE_LISTVIEW_STANDART
	if (items && checkings)
#else
	if (items && checkings && editings)
#endif
	{
		this->items->clear();
		this->checkings->clear();
#if !USE_LISTVIEW_STANDART 
		this->editings->clear();
#endif
		for (size_t r = 0; r < rows; r++)            
		{
			ListView_DeleteItem(hList,0);
		}
		rows = 0;
	}
}



void _ListViewTab_::DeleteRows()
{
	for (size_t r = 0; r < rows; r++)            
	{
		ListView_DeleteItem(hList,0);
	}
	rows = 0;
}

