#if !defined(AFX_WAVEDLG_H__D210793B_8C66_4CF8_84FB_8FD4860F6CE3__INCLUDED_)
#define AFX_WAVEDLG_H__D210793B_8C66_4CF8_84FB_8FD4860F6CE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaveDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaveDlg dialog

class CWaveDlg : public CDialog
{
// Construction
	friend class CGraphsDoc;
	DECLARE_DYNAMIC(CWaveDlg)
public:
//	CButton m_Radio;
	void SetWaveletFilterLength();
	CStatic m_txtWavLen;
	CComboBox m_cmbWavOrder;
	CComboBox m_cmbWavType;
	CComboBox m_cmbWavMaxLevel;
//	CComboBox m_Combo;
	CGraphsDoc* m_pDoc;
	CWaveDlg(CGraphsDoc* p);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWaveDlg)
	enum { IDD = IDD_WAV_PARAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaveDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeComboWavType();
	afx_msg void OnSelchangeComboWavOrder();
	afx_msg void OnWavDisp();
	afx_msg void OnWavEpsilon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEDLG_H__D210793B_8C66_4CF8_84FB_8FD4860F6CE3__INCLUDED_)
