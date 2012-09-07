// TSP2Dlg.h : header file
//

#if !defined(AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_)
#define AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MapWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CTSP2Dlg dialog

class CTSP2Dlg : public CDialog
{
// Construction
public:
	CTSP2Dlg(CWnd* pParent = NULL);	// standard constructor
	~CTSP2Dlg();

// Dialog Data
	//{{AFX_DATA(CTSP2Dlg)
	enum { IDD = IDD_TSP2_DIALOG };
	CStatic	m_pathStatic;
	CStatic	m_iterationStatic;
	CEdit	m_neuronsEdit;
	CEdit	m_momentumEdit;
	CEdit	m_learnRateEdit;
	CEdit	m_delayEdit;
	CButton	m_createButton;
	CButton	m_loadButton;
	CButton	m_saveButton;
	CButton	m_startButton;
	CButton	m_stopButton;
	CStatic	m_citiesStatic;
	CEdit	m_citiesEdit;
	CMapWnd	m_mapWnd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTSP2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
private:
	void ShowCitiesCount();
	void Free();
	void EnableControls(BOOL bEnable);

private:
	static DWORD ThreadProc(CTSP2Dlg* me);

protected:
	HICON	m_hIcon;

	int		m_cities;

	short*	m_xPoints;
	short*	m_yPoints;

	// thread
	HANDLE		m_thread;
	BOOL		m_stop;

	short		m_neurons;
	float		m_learnRate;
	float		m_momentum;
	long		m_delay;

	long		m_iteration;
	float		m_minTour;

	// Generated message map functions
	//{{AFX_MSG(CTSP2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnButtonCreateMap();
	afx_msg void OnButtonSaveMap();
	afx_msg void OnButtonLoadMap();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	afx_msg void OnSetInfo(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_)
