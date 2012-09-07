/*################################################################################################*/
#include "stdafx.h"
#include "../resource.h"

#include "lab_cmd_dlg.h"
extern HINSTANCE hInst;

HWND lab_cmd_dlg::dialog;
HWND lab_cmd_dlg::entry;

BOOL CALLBACK DlgProc_Command(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) 
{ 
	static lab_cmd_dlg * cmnd_dlg;
    switch (message) 
    { 
	case WM_INITDIALOG:
		{
//printf("lab_cmd_dlg::WM_INITDIALOG\n");
			cmnd_dlg = reinterpret_cast<lab_cmd_dlg *>(lParam);
//printf("lab_cmd_dlg::WM_INITDIALOG 2\n");
			if (cmnd_dlg) SetDlgItemText(hDlg, IDC_EDIT_COMMAND, cmnd_dlg->command);
//printf("lab_cmd_dlg::WM_INITDIALOG 3\n");
		}
		break;
    case WM_COMMAND: 
        switch (LOWORD(wParam)) 
        { 
            case IDOK: 
				if (cmnd_dlg) cmnd_dlg->OkButtonHandler(GetDlgItem(hDlg, IDC_EDIT_COMMAND));

            case IDCANCEL: 
                EndDialog(hDlg, wParam); 
                return TRUE; 
        } 
		break;
	case WM_DESTROY:
		{
			if (cmnd_dlg && cmnd_dlg->to_process_command)
			{
//printf("lab_cmd_dlg::WM_DESTROY delete cmnd_dlg\n");
				delete cmnd_dlg;
			}
		}
    } 
    return FALSE; 
} 

lab_cmd_dlg::lab_cmd_dlg(const char * def_str)
{

	if (def_str) strcpy(command, def_str); else command[0] = '\0';
	this->to_process_command = true;
	ok_pressed = false;


	if (DialogBoxParam(hInst, 
         MAKEINTRESOURCE(IDD_COMMAND_DIALOG), 
         (HWND)NULL, (DLGPROC)DlgProc_Command, (LPARAM)this)==IDOK) 
    {
        // Complete the command; szItemName contains the 
        // name of the item to delete. 
    }

    else 
    {
        // Cancel the command. 
    } 

}

lab_cmd_dlg::lab_cmd_dlg(const char * def_str, bool to_process)
{
	if (def_str) strcpy(command, def_str); else command[0] = '\0';
	this->to_process_command = to_process;
	ok_pressed = false;

	if (DialogBoxParam(hInst, 
         MAKEINTRESOURCE(IDD_COMMAND_DIALOG), 
         (HWND)NULL, (DLGPROC)DlgProc_Command, (LPARAM)this)==IDOK) 
    {
        // Complete the command; szItemName contains the 
        // name of the item to delete. 
    }

    else 
    {
        // Cancel the command. 
   } 

}

lab_cmd_dlg::~lab_cmd_dlg(void)
{
}
void lab_cmd_dlg::OkButtonHandler(HWND hEditWnd)
{
	ok_pressed = true;
	GetWindowText(hEditWnd, command, 511);
}


/*################################################################################################*/
