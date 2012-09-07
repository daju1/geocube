// KohonenDlg.h : header file
//

#if !defined(AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_)
#define AFX_TSP2DLG_H__D57F2D22_6FC5_4CB4_9C57_E608AC261093__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "KohonenMapWnd.h"
#include "NetKohonen.h"

/////////////////////////////////////////////////////////////////////////////
// CTSP2Dlg dialog

class KohonenDlg //: public CDialog
{
	HWND hSurfWnd;
	string m_name;
	friend BOOL CALLBACK DlgProcKohonenNNet(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) ;
	friend LRESULT APIENTRY KohonenMapWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);

	HWND hDlg;
	KohonenMapWnd	m_mapWnd;
	short m_type;
	bool m_bInited;
	static bool s_toCreateSurfWindowOnThread;
	static bool s_WinnersGot;
	// Construction
public:
	static DWORD ShowSpheres(KohonenDlg* me);
	static DWORD SurfResults(KohonenDlg* me);
	void ClassesSaveAs();
	void ResultsSaveAs();
	//void PointsSaveAs();
	static DWORD GetWinners(KohonenDlg * me, float * in);
	KohonenDlg::KohonenDlg(vector<double>& X, vector<double>& Y, vector<double>& Z, vector<vector<double> >& MM, string name, bool modal);	// standard constructor
	KohonenDlg(int n, double *X, double *Y, double *Z, double * xp, double * yp, bool modal = false);	// standard constructor
	KohonenDlg(int nExamples, double *X, double *Y, double *Z, int nParameters, double ** p, string name = "", bool modal = false);	// standard constructor
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


	double ZoomParameterIn(double in, int n);
	double ZoomParameterOut(double in, int n);
	void ZoomParameterIn();

private:
	static DWORD ThreadProc(KohonenDlg* me);
	void ExtremeParameterPoints();

protected:
	HICON	m_hIcon;

	int		m_examples;
	int		m_nParameters;
	// geocoordinates if input points
	double*	m_X;
	double*	m_Y;
	double*	m_Z;

//	double*	m_xPoints;
//	double*	m_yPoints;

//	double*	m_ixPoints;
//	double*	m_iyPoints;

	double**	m_Points;
	double**	m_inPoints;

	int*    m_winners;

	int m_j0, m_j1;

//	double 
//		m_ixMax,
//		m_ixMin,
//		m_iyMax,
//		m_iyMin;

	double 
		*m_inMax,
		*m_inMin;

	float 
		*m_minOfPoints,
		*m_maxOfPoints;
	// thread
	HANDLE		m_thread;
	BOOL		m_stop;

	short		m_neurons;
	int			m_dx;
	int			m_dy;

	float		m_learnRate;
	float		m_momentum;

	float		m_learnRateDistance;
	float		m_momentumDistance;

	float		m_learnRateConscience;
	float		m_momentumConscience;

	CNetKohonen	m_net;

	float		m_net_learnRate;
	float		m_net_momentum;

	float		m_net_learnRateDistance;
	float		m_net_momentumDistance;

	float		m_net_learnRateConscience;
	float		m_net_momentumConscience;

	long		m_delay;

	long		m_iteration;
	float		m_minTour;

	void RangeOfPoints();

	// Generated message map functions
//	//{{AFX_MSG(CTSP2Dlg)
	BOOL OnInitDialog();
	void InitParams(bool firstly = true);
	void OnSysCommand(UINT nID, LPARAM lParam);
	//void OnPaint();
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
