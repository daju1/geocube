LRESULT CALLBACK DlgProcParentTab( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static HWND hWndTab;
	static HWND hChildDlg;

	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
			hWndTab = TabCreate(hDlg) ;
			TabCtrl_SetCurSel(hWndTab, 0);

			NMHDR nmhdr;
			nmhdr.hwndFrom = hWndTab;
			nmhdr.code = TCN_SELCHANGE;
			SendMessage(hDlg, WM_NOTIFY, 0, (LPARAM)&nmhdr);

		}
		break;
	case WM_NOTIFY:
		if((((NMHDR*)lParam)->hwndFrom)==hWndTab && (((NMHDR*)lParam)->code)==TCN_SELCHANGE)
		{
			int Page = TabCtrl_GetCurSel(hWndTab);
			LPCSTR lpTemplateName = NULL;
			DLGPROC DlgProcTabChild = NULL;
			switch (Page)
			{
			case 0:
				{
					lpTemplateName = MAKEINTRESOURCE(IDD_CHILD_DIALOG1); 
					DlgProcTabChild = DlgProcTabChild1;
				}
				break;
			case 1:
				{
					lpTemplateName = MAKEINTRESOURCE(IDD_CHILD_DIALOG2); 
					DlgProcTabChild = DlgProcTabChild2;
				}
				break;
			case 2:
				{
					lpTemplateName = MAKEINTRESOURCE(IDD_CHILD_DIALOG3); 
				}
				break;
			case 3:
				{
					lpTemplateName = MAKEINTRESOURCE(IDD_CHILD_DIALOG4); 
				}
				break;
			case 4:
				{
					lpTemplateName = MAKEINTRESOURCE(IDD_CHILD_DIALOG5); 
				}
				break;
			case 5:
				{
					lpTemplateName = MAKEINTRESOURCE(IDD_CHILD_DIALOG6); 
				}
				break;
			}

			if (hChildDlg)
				DestroyWindow(hChildDlg);

			if (lpTemplateName)
			{
				hChildDlg=CreateDialog(hInst,lpTemplateName,hWndTab,(DLGPROC)DlgProcTabChild);

				RECT rcTab;
				GetClientRect(hWndTab, &rcTab);
				SetWindowPos(hChildDlg, HWND_TOP, 
					rcTab.left	+ 10, 
					rcTab.top	+ 20, 
					rcTab.right - rcTab.left - 20, 
					rcTab.bottom - rcTab.top - 30,	
					SWP_SHOWWINDOW);

				ShowWindow(hDlg,SW_SHOW);
			}
			return TRUE;
		}
		return FALSE;
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{			
		case IDOK :
			{
				SendMessage(hChildDlg, WM_COMMAND, IDOK, 0);
				EndDialog( hDlg, IDOK );
			}
			break;
		case IDAPPLAY :
			{
				SendMessage(hChildDlg, WM_COMMAND, IDAPPLAY, 0);
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


HWND TabCreate(HWND hwnd) 
{ 
	TC_ITEM tci; 
	RECT Rect; 
	
	memset(&tci,0,sizeof(TC_ITEM)); 
	GetClientRect(hwnd,&Rect); 
	
	HWND hTab=CreateWindow(WC_TABCONTROL,"",WS_CHILD|WS_VISIBLE|WS_TABSTOP,5,5,Rect.right-10, 
		Rect.bottom-50,hwnd,NULL,hInst,NULL); 

	tci.mask=TCIF_TEXT; 
	tci.iImage=-1; 
	tci.pszText="Первая закладка"; 
	TabCtrl_InsertItem(hTab,0,&tci); 

	tci.pszText="Вторая закладка"; 
	TabCtrl_InsertItem(hTab,1,&tci); 

	tci.pszText="Третья закладка"; 
	TabCtrl_InsertItem(hTab,2,&tci); 

	tci.pszText="4я закладка"; 
	TabCtrl_InsertItem(hTab,3,&tci); 

	tci.pszText="5я закладка"; 
	TabCtrl_InsertItem(hTab,4,&tci); 

	tci.pszText="6я закладка"; 
	TabCtrl_InsertItem(hTab,5,&tci); 

	return hTab; 
} 


BOOL CALLBACK DlgProcTabChild1( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				MessageBox(0,"IDOK","DlgProcTabChild1",0);
				EndDialog( hDlg, IDOK );
			}
			break;
		case IDAPPLAY :
			{
				MessageBox(0,"IDAPPLAY","DlgProcTabChild1",0);
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

BOOL CALLBACK DlgProcTabChild2( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDOK :
			{
				MessageBox(0,"IDOK","DlgProcTabChild2",0);
				EndDialog( hDlg, IDOK );
			}
			break;
		case IDAPPLAY :
			{
				MessageBox(0,"IDAPPLAY","DlgProcTabChild2",0);
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

