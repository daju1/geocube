// DlgAddingGeoCube.cpp : implementation file
//

#include "../../surfer_connect/stdafx.h"
#include "../resource.h"
#include "DlgAddingGeoCube.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HINSTANCE hInst;

/////////////////////////////////////////////////////////////////////////////
// DlgAddingGeoCube dialog


DlgAddingGeoCube::DlgAddingGeoCube()
{
	//{{AFX_DATA_INIT(DlgAddingGeoCube)
	m_edit_param_name = _T("");
	m_radio_normative_type = -1;
	m_check_full_cube_filling = FALSE;
	//}}AFX_DATA_INIT
}
LRESULT CALLBACK DlgAddingGeoCube::DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static DlgAddingGeoCube * dlg;
	int wmId, wmEvent;

	switch (message) 
	{
		case WM_INITDIALOG :
			{
				dlg = reinterpret_cast<DlgAddingGeoCube *>(lParam);
				if (dlg)
					dlg->InitDialog(hDlg);
			}
			break;
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_RADIO_NORMATIVE:
			case IDC_RADIO_RASCHOTN_85:
			case IDC_RADIO_RASCHOTN_95:
			case IDC_RADIO_RASCHOTN_99:
				{
					if (dlg)
						dlg->RadioButtonHandler(hDlg, IDC_RADIO_NORMATIVE, wmId);
				}
				break;
			case IDC_CHECK_FULL_CUBE_FILLING:
				{
					if (dlg)
					{
						dlg->m_check_full_cube_filling = IsDlgButtonChecked(hDlg, wmId) == BST_CHECKED;
					}
				}
				break;
			case IDOK:
				{
					if (dlg)
						dlg->OkButtonHandler(hDlg);
					EndDialog( hDlg, IDOK );
				}
				break;

			case IDCANCEL :
				EndDialog( hDlg, IDCANCEL );
				break;
			}
			break;

		case WM_CLOSE:
			{
				return DefWindowProc(hDlg, message, wParam, lParam);
			}
			break;
   }
   return 0;
}

void DlgAddingGeoCube::DoModal()
{
	if (IDOK == DialogBoxParam(hInst, 
		MAKEINTRESOURCE(DlgAddingGeoCube::IDD), 
		(HWND)NULL, (DLGPROC)DlgAddingGeoCube::DlgProc, (LPARAM) this)==IDOK) 
	{
	}
}
void DlgAddingGeoCube::RadioButtonHandler(HWND hDlg, int id_group, int id)
{
	m_radio_normative_type = id - id_group;
}


/////////////////////////////////////////////////////////////////////////////
// DlgAddingGeoCube message handlers

void DlgAddingGeoCube::InitDialog(HWND hDlg) 
{
	CheckRadioButton( hDlg,
		IDC_RADIO_NORMATIVE,
		IDC_RADIO_RASCHOTN_99,
		IDC_RADIO_NORMATIVE + m_radio_normative_type);
			
	
	CheckDlgButton(hDlg, IDC_CHECK_FULL_CUBE_FILLING,	
		this->m_check_full_cube_filling);

	SetDlgItemText(hDlg, IDC_STATIC_PARAM_NAME, this->m_edit_param_name);

}
void DlgAddingGeoCube::OkButtonHandler(HWND hDlg) 
{
}