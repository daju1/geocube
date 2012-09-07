#include "stdafx.h"
#include "MyDialog.h"
#include "resource.h"
#include "cderr.h"

extern HINSTANCE hInst;								// current instance

LRESULT CALLBACK MyDlgProc( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static MyDlg * dlg;

	switch( uMsg )
		
	{
    case WM_INITDIALOG :
		{
			dlg = reinterpret_cast<MyDlg *>(lParam);
			if(dlg)
			{
				dlg->hDlg = hDlg;
				dlg->OnInitDialog();
			}
		}
		break;
    case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
			/*
		case IDC_RADIO1:
			{
				if(dlg) 
				{
					dlg->m_ab.locals_algorithms_type = 
						auto_build_parametrs::locals_algorithms::the_simple;
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), false);
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), false);
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), false);
				}
			}
			break;
		case IDC_RADIO2:
			{
				if(dlg) 
				{
					dlg->m_ab.locals_algorithms_type = 
						auto_build_parametrs::locals_algorithms::on_the_second_derivatives;
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL), true);
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), true);
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_STATIC_PEREGIB_KRUTIZNA_QUANTIL), true);
				}
			}
			break;
		case IDC_RADIO4:
			{
				if(dlg) 
				{
					dlg->m_ab.m_gradient_type = 
						auto_build_parametrs::gradient_type::the_dividitial;
				}
			}
			break;
		case IDC_RADIO5:
			{
				if(dlg) 
				{
					dlg->m_ab.m_gradient_type = 
						auto_build_parametrs::gradient_type::the_differential;
				}
			}
			break;		
		case IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL:
			{
				if(dlg) 
				{
					dlg->m_ab.allow_sd_limit_quantil = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL) == BST_CHECKED;
					EnableWindow(GetDlgItem(dlg->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL), dlg->m_ab.allow_sd_limit_quantil);
				}
			}
			break;

		case IDC_CHECK_POVTOR_ZAPRET:
			{
				if(dlg) 
				{
					dlg->m_ab.use_repeat_points = IsDlgButtonChecked( hDlg, IDC_CHECK_POVTOR_ZAPRET) 
						!= BST_CHECKED;
					EnableWindow(GetDlgItem(dlg->hDlg, IDC_EDIT_POVTOR_ZAPRET), !dlg->m_ab.use_repeat_points);
				}
			}
			break;
		case IDC_CHECK_USE_NUM_COL:
			{
				if(dlg) 
				{
					dlg->m_ab.use_num_col = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_NUM_COL) == BST_CHECKED;
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_EDIT_NUM_COLOMNS), dlg->m_ab.use_num_col);
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_BUTTON_BROSE_NUM_COLOMNS), dlg->m_ab.use_num_col);
					
					if (dlg->m_ab.use_num_col)
					{
						char str[4096];
						sprintf(str, "%s", dlg->m_ab.num_col_filename);
						SetDlgItemText(dlg->hDlg, IDC_EDIT_NUM_COLOMNS, str);
					}
						
					dlg->num_col_file_selected = false;
				}
			}
			break;
		case IDC_CHECK_USE_WHOLE_DIRECTORY:
			{
				if(dlg) 
				{
					dlg->m_ab.use_whole_directory = 
						IsDlgButtonChecked( hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY) == BST_CHECKED;
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_DIRECTORY2), 
						dlg->m_ab.use_whole_directory);
					ShowWindow(GetDlgItem(dlg->hDlg, IDC_LIST2), 
						dlg->m_ab.use_whole_directory);
				}
			}
			break;
		case IDC_COMBO_DELIMITER:
			{								
				if(dlg) 
				{
					switch(SendDlgItemMessage( hDlg, 
						IDC_COMBO_DELIMITER,
						CB_GETCURSEL,0,(LPARAM)0 ))
					{
					case 0:
						dlg->m_ab.delim = ',';
						break;
					case 1:
						dlg->m_ab.delim = ';';
						break;
					case 2:
						dlg->m_ab.delim = '\t';
						break;
					case 3:
						dlg->m_ab.delim = ' ';
						break;
					}
				}
			}
			break;
		case IDC_CHECK_USE_LOCALS:
			{
				if(dlg) 
				{
					dlg->ShowWindows_RelatedWith_CheckUseLocals();
				}
			}
			break;
		case IDC_CHECK_DIMA_AFTER_LOCALS:
		case IDC_CHECK_1_AFTER_LOCALS:
			{
				if(dlg) 
				{
					dlg->ShowWindows_RelatedWith_Windows_Cycles2();
				}			
			}
			// do not break here!!!
		case IDC_CHECK_DIMA:
		case IDC_CHECK_1:
			{
				if(dlg) 
				{
					dlg->ShowWindows_RelatedWith_Windows_Cycles();
				}
			}
			break;
		case IDC_BUTTON_BROSE_NUM_COLOMNS:
			{
				if(dlg) 
				{
					dlg->OnButtonBroseNumColomn();
				}
			}
			break;
*/
		case IDC_BUTTON_LOAD_OLE_EXCEL:
			{
				if(dlg) 
				{
					dlg->m_excel.ExcelOleLoad();
				}
			}
			break;

		case IDC_BUTTON_EXECUTE:
			{
				if(dlg && dlg->m_excel.IsApplicationDispatch()) 
				{
//					dlg->m_excel.ExcelOleExecute();
				}
			}
			break;

		case IDC_BUTTON_EXECUTE2:
			{
				if(dlg && dlg->m_excel.IsApplicationDispatch()) 
				{					 
					//dlg->m_excel.ExcelOleExecute_2();
				}
			}
			break;
		case IDC_BUTTON_EXECUTE_1:
			{
				if(dlg) 
				{
					dlg->m_excel.ExcelOleLoad();
					if ( dlg->m_excel.IsApplicationDispatch() )
					{
						try
						{
//							dlg->m_excel.ExcelOleExecute();
						}
						catch(...)
						{
						}

						dlg->m_excel.ExcelOleRelease();
					}
				}
			}
			break;
		case IDC_BUTTON_EXECUTE_2:
			{
				if(dlg) 
				{
					dlg->m_excel.ExcelOleLoad();
					if ( dlg->m_excel.IsApplicationDispatch() )
					{
						try
						{
//							dlg->m_excel.ExcelOleExecute_2();
						}
						catch(...)
						{
						}
						dlg->m_excel.ExcelOleRelease();
					}
				}
			}
			break;
		case IDC_BUTTON_EXCEL_OLE_RELEASE:
			{
				if(dlg && dlg->m_excel.IsApplicationDispatch()) 
				{					 
					dlg->m_excel.ExcelOleRelease();
				}
			}
			break;

		case IDOK :
			{
				if (dlg) dlg->OnButtonOK();
			}
			break;
		case IDCANCEL :
			{
//				hDlgModeless = NULL;
				EndDialog( hDlg, IDCANCEL );
			}
			break;
		}
		break;
		case WM_DESTROY :
			{
				if (dlg) dlg->OnDestroy();
			}
			break;
		default :
			return( FALSE );
	}
	return( TRUE );
}


MyDlg::MyDlg(bool _consol)
{
	consol = _consol;

	if (consol)
	{
		DialogBoxParam( 
		   hInst, 
		   MAKEINTRESOURCE(IDD_DIALOG_TEST_EXCEL), 
		   NULL,
		   (DLGPROC)MyDlgProc,
		   (LPARAM)this);
	}
	else
	{
		HANDLE hDialog = LoadResource( hInst,
						FindResource( hInst, MAKEINTRESOURCE(IDD_DIALOG_TEST_EXCEL),
										RT_DIALOG ) );

		LPVOID lpDialog = LockResource( hDialog );

		hDlg = CreateDialogIndirectParam( hInst, (DLGTEMPLATE *)lpDialog, NULL,
							(DLGPROC)MyDlgProc,
							(LPARAM)this );
		ShowWindow(hDlg, SW_SHOW);
	}

}

MyDlg::~MyDlg()
{

}

void MyDlg::OnInitDialog()
{
//	char str[1024];
	///////////////////////////////////////////////
/*	sprintf(str, "%f", this->m_ab.k);
	SetDlgItemText(this->hDlg, IDC_EDIT_GLUBINA_K, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.quantil_naklony);
	SetDlgItemText(this->hDlg, IDC_EDIT_NAKLON_QUANTIL, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.peregib_krutizna_quantil);
	SetDlgItemText(this->hDlg, IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.win_velonsity);
	SetDlgItemText(this->hDlg, IDC_EDIT_WIN_STEP_VELONSITY, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.minimum_of_signal);
	SetDlgItemText(this->hDlg, IDC_EDIT_MINIMUM_OF_SIGNAL, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.limit_dima);
	SetDlgItemText(this->hDlg, IDC_EDIT_LIMIT_DIMA, str);
	///////////////////////////////////////////////
	sprintf(str, "%f", this->m_ab.limit_1);
	SetDlgItemText(this->hDlg, IDC_EDIT_LIMIT_1, str);
	///////////////////////////////////////////////

	sprintf(str, "%d", this->m_ab.n);
	SetDlgItemText(this->hDlg, IDC_EDIT_POVTOR_ZAPRET, str);
	///////////////////////////////////////////////

	

	
	

	
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_DIMA, this->m_ab.use_window_cycles_algorithm_dima);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_1, this->m_ab.use_window_cycles_algorithm_1);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_LOCALS, this->m_ab.use_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_DIMA_AFTER_LOCALS, this->m_ab.use_window_cycles_algorithm_dima_after_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_1_AFTER_LOCALS, this->m_ab.use_window_cycles_algorithm_1_after_locals);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL, this->m_ab.allow_sd_limit_quantil);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_POVTOR_ZAPRET, !this->m_ab.use_repeat_points);
	EnableWindow(GetDlgItem(this->hDlg, IDC_EDIT_POVTOR_ZAPRET), !this->m_ab.use_repeat_points);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_NUM_COL, this->m_ab.use_num_col);
	ShowWindow(GetDlgItem(this->hDlg, IDC_EDIT_NUM_COLOMNS), this->m_ab.use_num_col);
	ShowWindow(GetDlgItem(this->hDlg, IDC_BUTTON_BROSE_NUM_COLOMNS), this->m_ab.use_num_col);
	sprintf(str, "%s", this->m_ab.num_col_filename);
	SetDlgItemText(this->hDlg, IDC_EDIT_NUM_COLOMNS, str);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_USE_WHOLE_DIRECTORY, this->m_ab.use_whole_directory);
	ShowWindow(GetDlgItem(this->hDlg, IDC_DIRECTORY2), 
		this->m_ab.use_whole_directory);
	ShowWindow(GetDlgItem(this->hDlg, IDC_LIST2), 
		this->m_ab.use_whole_directory);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN, this->m_ab.use_min);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MAX, this->m_ab.use_max);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN_MAX, this->m_ab.use_min_max);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN2, this->m_ab.use_min_2);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MAX2, this->m_ab.use_max_2);
	///////////////////////////////////////////////
	CheckDlgButton(this->hDlg, IDC_CHECK_LOCAL_MIN_MAX2, this->m_ab.use_min_max_2);
	///////////////////////////////////////////////

	switch (this->m_ab.m_gradient_type)
	{
	case auto_build_parametrs::gradient_type::the_dividitial:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO4,
				IDC_RADIO6,
				IDC_RADIO4);
		}
		break;
	case auto_build_parametrs::gradient_type::the_differential:
		{
			CheckRadioButton( hDlg,
				IDC_RADIO4,
				IDC_RADIO6,
				IDC_RADIO5);
		}
		break;
	}


	this->ShowWindows_RelatedWith_CheckUseLocals();
	this->ShowWindows_RelatedWith_Windows_Cycles();
	


	for(size_t j = 0; j < 3; j++)
	{
		sprintf(str, "%u", j);
		SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J , CB_ADDSTRING, 0, (LPARAM)str);
		SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2, CB_ADDSTRING, 0, (LPARAM)str);
	}

	SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J , CB_SETCURSEL, this->m_ab.start_j1, (LPARAM)0 );
	SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2, CB_SETCURSEL, this->m_ab.start_j2, (LPARAM)0 );

	num_col_file_selected = false;



			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)",");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)";");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"tabulation");
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)"space");
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			SendDlgItemMessage( hDlg, IDC_COMBO_DELIMITER, CB_SETCURSEL,
				0,(LPARAM)0 );
			// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    // Retrieve the handle to the Map control. 
    this->m_plotWnd.hwnd = GetDlgItem(hDlg, IDC_STATIC_AUTOBUILD_PROFILE); 

    // Subclass the edit control. 
    wpOrigAutoBuildProfileWndProc = (WNDPROC) SetWindowLongPtr(this->m_plotWnd.hwnd, 
        GWLP_WNDPROC, (LONG_PTR) AutoBuildProfileWndSubclassProc); 

	SetWindowLongPtr(this->m_plotWnd.hwnd, GWLP_USERDATA,(LONG_PTR)this);

*/

}

void MyDlg::OnButtonOK()
{
//	char str[125];
	///////////////////////////////////////////////
/*	GetDlgItemText(this->hDlg,IDC_EDIT_GLUBINA_K, str, 124);
	this->m_ab.k = atof(str);
printf("this->m_ab.k = %f\n", this->m_ab.k);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_NAKLON_QUANTIL, str, 124);
	this->m_ab.quantil_naklony = atof(str);
printf("this->m_ab.quantil_naklony = %f\n", this->m_ab.quantil_naklony);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_PEREGIB_KRUTIZNA_QUANTIL, str, 124);
	this->m_ab.peregib_krutizna_quantil = atof(str);
printf("this->m_ab.peregib_krutizna_quantil = %f\n", this->m_ab.peregib_krutizna_quantil);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_WIN_STEP_VELONSITY, str, 124);
	this->m_ab.win_velonsity = atof(str);
printf("this->m_ab.win_velonsity = %f\n", this->m_ab.win_velonsity);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_MINIMUM_OF_SIGNAL, str, 124);
	this->m_ab.minimum_of_signal = atof(str);
printf("this->m_ab.minimum_of_signal = %f\n", this->m_ab.minimum_of_signal);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_LIMIT_DIMA, str, 124);
	this->m_ab.limit_dima = atof(str);
printf("this->m_ab.limit_dima = %f\n", this->m_ab.limit_dima);
	///////////////////////////////////////////////
	GetDlgItemText(this->hDlg,IDC_EDIT_LIMIT_1, str, 124);
	this->m_ab.limit_1 = atof(str);
printf("this->m_ab.limit_1 = %f\n", this->m_ab.limit_1);
	///////////////////////////////////////////////


	GetDlgItemText(this->hDlg,IDC_EDIT_POVTOR_ZAPRET, str, 124);
	this->m_ab.n = atoi(str);
printf("this->m_ab.n = %d\n", this->m_ab.n);
	///////////////////////////////////////////////




	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima = IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_dima = %d\n", this->m_ab.use_window_cycles_algorithm_dima);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1 = IsDlgButtonChecked( hDlg, IDC_CHECK_1) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_1 = %d\n", this->m_ab.use_window_cycles_algorithm_1);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_dima_after_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_DIMA_AFTER_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_dima_after_locals = %d\n", this->m_ab.use_window_cycles_algorithm_dima_after_locals);
	///////////////////////////////////////////////
	this->m_ab.use_window_cycles_algorithm_1_after_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_1_AFTER_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_window_cycles_algorithm_1_after_locals = %d\n", this->m_ab.use_window_cycles_algorithm_1_after_locals);

	///////////////////////////////////////////////
	this->m_ab.use_locals = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_LOCALS) == BST_CHECKED;
printf("this->m_ab.use_locals = %d\n", this->m_ab.use_locals);
	///////////////////////////////////////////////
	this->m_ab.allow_sd_limit_quantil = IsDlgButtonChecked( hDlg, IDC_CHECK_USE_PEREGIB_KRUTIZNA_QUANTIL) == BST_CHECKED;
printf("this->m_ab.allow_sd_limit_quantil = %d\n", this->m_ab.allow_sd_limit_quantil);
	///////////////////////////////////////////////


	///////////////////////////////////////////////
	this->m_ab.use_repeat_points = IsDlgButtonChecked( hDlg, IDC_CHECK_POVTOR_ZAPRET) 
		!= BST_CHECKED;
printf("this->m_ab.use_repeat_points = %d\n", this->m_ab.use_repeat_points);
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	this->m_ab.use_max = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MAX) == BST_CHECKED;
printf("this->m_ab.use_max = %d\n", m_ab.use_max);
	///////////////////////////////////////////////
	this->m_ab.use_max_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MAX2) == BST_CHECKED;
printf("this->m_ab.use_max_2 = %d\n", m_ab.use_max_2);
	///////////////////////////////////////////////
	this->m_ab.use_min = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN) == BST_CHECKED;
printf("this->m_ab.use_min = %d\n", m_ab.use_min);
	///////////////////////////////////////////////
	this->m_ab.use_min_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN2) == BST_CHECKED;
printf("this->m_ab.use_min_2 = %d\n", m_ab.use_min_2);
	///////////////////////////////////////////////
	this->m_ab.use_min_max = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN_MAX) == BST_CHECKED;
printf("this->m_ab.use_min_max = %d\n", m_ab.use_min_max);
	///////////////////////////////////////////////
	this->m_ab.use_min_max_2 = IsDlgButtonChecked( hDlg, IDC_CHECK_LOCAL_MIN_MAX2) == BST_CHECKED;
printf("this->m_ab.use_min_max_2 = %d\n", m_ab.use_min_max_2);
	///////////////////////////////////////////////


	this->m_ab.start_j1 = SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J ,	CB_GETCURSEL,0,(LPARAM)0 );
	this->m_ab.start_j2 = SendDlgItemMessage( hDlg, IDC_COMBO_LOCALS_START_J2,	CB_GETCURSEL,0,(LPARAM)0 );
printf("this->m_ab.start_j1 = %d\n", this->m_ab.start_j1);
printf("this->m_ab.start_j2 = %d\n", this->m_ab.start_j2);


	if (this->m_ab.use_num_col && !num_col_file_selected)
	{
		MessageBox(hDlg, "Вы не выбрали имя файла с номерами колонок","MyDlg",0);
		return;
	}

	if (this->m_ab.use_whole_directory)
	{
		UseWholeDirectory();
	}
	else
	{
		AutoBuildProfile_main(consol, p_auto_build_profile, this->m_ab);
	}*/
}

void MyDlg::OnButtonBroseNumColomn()
{
/*	if (::OpenFileDlg(hDlg, 
		"Data (*.dat)\0*.dat\0"
		"CSV (*.csv)\0*.csv\0"
		"All files \0*.*\0") == S_OK)

	{
		strcpy(this->m_ab.num_col_filename,::szPath);
		SetDlgItemText(this->hDlg, IDC_EDIT_NUM_COLOMNS, this->m_ab.num_col_filename);
		num_col_file_selected = true;
	}*/
}

void MyDlg::OnDestroy()
{
	m_excel.ExcelOleRelease();
}

bool MyDlg::OpenFileDialog(void)
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
   
//	ofn.lCustData         = (LPARAM)&this->oftcd;
//    ofn.lpfnHook          = DlgProcOpenFilesToCommon;
//    ofn.lpTemplateName    = MAKEINTRESOURCE(IDD_OPEN_FILES_TO_COMMON);
	ofn.Flags = 
		OFN_PATHMUSTEXIST 
		| OFN_FILEMUSTEXIST
		| OFN_EXPLORER 
//		| OFN_ENABLETEMPLATE 
//		| OFN_ENABLEHOOK 
		| OFN_ALLOWMULTISELECT
		;

	if (GetOpenFileName(&ofn)==TRUE)
	{
		if (ofn.lpstrFile != NULL)
		{
/*			this->m_files_in_dir.nFilterIndex = ofn.nFilterIndex;
			switch(this->m_files_in_dir.nFilterIndex)
			{
			case 1:
				strcpy(this->m_files_in_dir.szFileFilter, "*.csv");
				break;
			case 2:
				strcpy(this->m_files_in_dir.szFileFilter, "*.dat");
				break;
			case 3:
				strcpy(this->m_files_in_dir.szFileFilter, "*.txt");
				break;
			}
			strcpy(filename, ofn.lpstrFile + ofn.nFileOffset);
			strcpy(this->directory, ofn.lpstrFile);
			if (ofn.nFileOffset > 1) this->directory[ofn.nFileOffset-1] = '\0';
*/

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
