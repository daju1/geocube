#if !defined(AFX_TEST_EXCEL_DIALOG_H__CBF7D67A_5B12_425B_A310_F284765BFE7E__INCLUDED_)
#define AFX_TEST_EXCEL_DIALOG_H__CBF7D67A_5B12_425B_A310_F284765BFE7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Test_Excel_Dialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Test_Excel_Dialog dialog

class Test_Excel_Dialog : public CDialog
{
// Construction
public:
	Test_Excel_Dialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(Test_Excel_Dialog)
	enum { IDD = IDD_DIALOG_TEST_EXCEL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

int DoModal();
HWND PreModal();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Test_Excel_Dialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(Test_Excel_Dialog)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_EXCEL_DIALOG_H__CBF7D67A_5B12_425B_A310_F284765BFE7E__INCLUDED_)
