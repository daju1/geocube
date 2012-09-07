//SelectLayerDlg.cpp
#include "stdafx.h"
#include "SelectLayerDlg.h"
#include "../../surfdoc/src/SurfDoc.h"

extern HINSTANCE hInst;								// current instance

/*################################################################################################*/

SurfDoc * select_layer_dialog::doc;
HWND select_layer_dialog::hDlg;

BOOL CALLBACK DlgProcSelectLayer(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
	static select_layer_dialog * sel_lay_dlg;
    switch (message) 
    { 
	case WM_INITDIALOG:
		{
printf("select_layer_dialog::WM_INITDIALOG\n");
			sel_lay_dlg = reinterpret_cast<select_layer_dialog *>(lParam);
			sel_lay_dlg->hDlg = hDlg;
			sel_lay_dlg->OnInitDialog();
printf("select_layer_dialog::WM_INITDIALOG 3\n");
		}
		break;
    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
		case IDC_COMBO_SELECT_LAYER:
			{
				sel_lay_dlg->ComboHandler(GetDlgItem(hDlg, IDC_COMBO_SELECT_LAYER));
			}
			break;

		case IDOK: 
			sel_lay_dlg->OkButtonHandler(
				GetDlgItem(hDlg, IDC_COMBO_SELECT_LAYER), 
				GetDlgItem(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME));
			EndDialog(hDlg, wParam);
			return TRUE; 

		case IDCANCEL: 
			sel_lay_dlg->CancelButtonHandler();
			EndDialog(hDlg, wParam);
			return TRUE; 
        } 
		break;
	case WM_DESTROY:
		{
printf("select_layer_dialog::WM_DESTROY delete sel_lay_dlg\n");
			delete sel_lay_dlg;
		}
    } 
    return FALSE; 
} 

select_layer_dialog::select_layer_dialog(SurfDoc * p1, const char * def_str)
{

	doc = p1; 
	if (def_str) strcpy(command, def_str); else command[0] = '\0';
	ok_pressed = false;


	if (DialogBoxParam(hInst, 
         MAKEINTRESOURCE(IDD_SELECT_LAYER_DIALOG), 
         (HWND)NULL, (DLGPROC)DlgProcSelectLayer, (LPARAM)this)==IDOK) 
    {
        // Complete the command; szItemName contains the 
        // name of the item to delete. 
    }

    else 
    {
        // Cancel the command. 
    } 

}

select_layer_dialog::~select_layer_dialog(void)
{
}
void select_layer_dialog::OnInitDialog(void)
{
	SetDlgItemText(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME, this->command);
	ShowWindow(GetDlgItem(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME), 0);
	if (this->doc)
	{
		SendDlgItemMessage( this->hDlg, IDC_COMBO_SELECT_LAYER, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)this->doc->m_defaut_layer.GetName().c_str());

		for (map<int, Layer>::iterator i_layer = this->doc->m_layers.begin(); i_layer != this->doc->m_layers.end(); i_layer++)
		{
			SendDlgItemMessage( this->hDlg, IDC_COMBO_SELECT_LAYER, CB_ADDSTRING, 0,
				(LPARAM)(LPCTSTR)i_layer->second.GetName().c_str());
		}

		SendDlgItemMessage( this->hDlg, IDC_COMBO_SELECT_LAYER, CB_ADDSTRING, 0,
			(LPARAM)(LPCTSTR)"--------  new  -------");

		SendDlgItemMessage( hDlg, IDC_COMBO_SELECT_LAYER, CB_SETCURSEL,
			0,(LPARAM)0 );
	}
}
void select_layer_dialog::ComboHandler(HWND hCombo)
{
	LRESULT icombo = SendMessage( hCombo, CB_GETCURSEL, 0, (LPARAM)0 );
	if (this->doc)
	{
		if (icombo > this->doc->m_layers.size())
		{
			int id = this->doc->GetIDForNewLayer();
			sprintf(this->command, "Layer %d", id);
			SetDlgItemText(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME, this->command);
			ShowWindow(GetDlgItem(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME), 1);
		}
		else
		{
			ShowWindow(GetDlgItem(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME), 0);
		}
	}
}
void select_layer_dialog::OkButtonHandler(HWND hCombo, HWND hEditWnd)
{
	ok_pressed = true;
	GetWindowText(hEditWnd, command, 511);
	LRESULT icombo = SendMessage( hCombo, CB_GETCURSEL, 0, (LPARAM)0 );
	if (doc)
	{
		if (icombo == 0)
		{
			doc->SetSelectedLayer(&doc->m_defaut_layer);
			return;
		}
		if (icombo > 0 && icombo <= doc->m_layers.size())
		{
			size_t i = 1;
			for( map<int, Layer>::iterator it = doc->m_layers.begin(); it != doc->m_layers.end(); it++)
			{
				if (i == icombo)
				{
					doc->SetSelectedLayer(&it->second);
					return;
				}
				else
					i++;

			}
		}
		if (icombo > this->doc->m_layers.size())
		{			
			GetDlgItemText(hDlg, IDC_EDIT_ENTER_NEW_LAYR_NAME, this->command, 511);
			doc->SetSelectedLayer(doc->AddNewLayer(this->command));
			doc->FillLayerList();
			return;
		}	
	}
}
void select_layer_dialog::CancelButtonHandler()
{
	ok_pressed = false;
	if (this->doc)
		this->doc->SetSelectedLayer(NULL);
}


/*################################################################################################*/

// eof