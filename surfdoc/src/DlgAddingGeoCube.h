#if !defined(AFX_DLGADDINGGEOCUBE_H__E6DE96CC_F12E_4393_8275_0AB65C7211EE__INCLUDED_)
#define AFX_DLGADDINGGEOCUBE_H__E6DE96CC_F12E_4393_8275_0AB65C7211EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAddingGeoCube.h : header file
//
#include "../stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// DlgAddingGeoCube dialog

class DlgAddingGeoCube// : public CDialog
{
// Construction
public:
	DlgAddingGeoCube();   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAddingGeoCube)
	enum { IDD = IDD_DIALOG_ADDING_GEO_CUBE };
	CString	m_edit_param_name;
	int		m_radio_normative_type;
	BOOL	m_check_full_cube_filling;
	bool ob_button_pressed;
	//}}AFX_DATA

	static LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void DoModal();
	void RadioButtonHandler(HWND hDlg, int id_group, int id);
	void InitDialog(HWND hDlg);
	void OkButtonHandler(HWND hDlg);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDINGGEOCUBE_H__E6DE96CC_F12E_4393_8275_0AB65C7211EE__INCLUDED_)
