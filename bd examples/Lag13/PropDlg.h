#if !defined(AFX_PROPDLG_H__75B9F1E6_E346_4482_94EC_EC5A4CB15DDE__INCLUDED_)
#define AFX_PROPDLG_H__75B9F1E6_E346_4482_94EC_EC5A4CB15DDE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
//#pragma once
// CPropDlg dialog
class COGView;				// Упреждающее объявление


class CPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropDlg)
public:
	COGView *m_pView; 		// Адрес Вида
	int m_Pos[11]; 			// Массив позиций ползунков

	CPropDlg(COGView* p);
// Construction
// Dialog Data
	//{{AFX_DATA(CPropDlg)
	enum { IDD = IDD_PROP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int CPropDlg::GetSliderNum(HWND hwnd, UINT& nID);

	// Generated message map functions
	//{{AFX_MSG(CPropDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnFilename();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPDLG_H__75B9F1E6_E346_4482_94EC_EC5A4CB15DDE__INCLUDED_)
