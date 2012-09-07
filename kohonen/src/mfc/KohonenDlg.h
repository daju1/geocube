// KohonenDlg.h : header file
//

#if !defined(AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_)
#define AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KohonenMapWnd.h"

/////////////////////////////////////////////////////////////////////////////
// CTSP2Dlg dialog

class KohonenDlg //: public CDialog
{
	friend BOOL CALLBACK DlgProcKohonenNNet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;
	friend LRESULT APIENTRY KohonenMapWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);

	HWND hDlg;
	KohonenMapWnd	m_mapWnd;
	// Construction
public:
	KohonenDlg(int n, double * xp, double * yp);	// standard constructor
	~KohonenDlg();

// Dialog Data
//	//{{AFX_DATA(CTSP2Dlg)
/*	enum { IDD = IDD_TSP2_DIALOG };
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
*/
//	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTSP2Dlg)
	protected:
//	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
private:
	void ShowCitiesCount();
	void Free();
	void EnableControls(BOOL bEnable);

private:
	static DWORD ThreadProc(KohonenDlg* me);
	void ExtremePoints();

protected:
	HICON	m_hIcon;

	int		m_cities;

	double*	m_xPoints;
	double*	m_yPoints;

	double*	m_ixPoints;
	double*	m_iyPoints;

	double 
		m_ixMax,
		m_ixMin,
		m_iyMax,
		m_iyMin;
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
//	//{{AFX_MSG(CTSP2Dlg)
	BOOL OnInitDialog();
	void OnSysCommand(UINT nID, LPARAM lParam);
	void OnPaint();
	HCURSOR OnQueryDragIcon();
	void OnDestroy();
	void OnButtonCreateMap();
	void OnButtonSaveMap();
	void OnButtonLoadMap();
	void OnButtonStart();
	void OnButtonStop();
	void OnSetInfo(WPARAM wParam, LPARAM lParam);
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_)
