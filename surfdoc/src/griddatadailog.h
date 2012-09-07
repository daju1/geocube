#if !defined(AFX_GRIDDATADAILOG_H__5460C2EB_182A_49EC_91AE_FC01E2D4F352__INCLUDED_)
#define AFX_GRIDDATADAILOG_H__5460C2EB_182A_49EC_91AE_FC01E2D4F352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// griddatadailog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// GridDataDailog dialog

class GridDataDailog : public CDialog
{
// Construction
public:
	GridDataDailog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(GridDataDailog)
	enum { IDD = IDD_DIALOG_GRIDDATA_GRIDDATA };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GridDataDailog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GridDataDailog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDATADAILOG_H__5460C2EB_182A_49EC_91AE_FC01E2D4F352__INCLUDED_)
