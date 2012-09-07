//#if !defined(AFX_MAPWND_H__76E52685_707A_4B28_995C_76B11948CB5A__INCLUDED_)
//#define AFX_MAPWND_H__76E52685_707A_4B28_995C_76B11948CB5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapWnd window

class KohonenMapWnd /*: public CWnd*/
{
	friend LRESULT APIENTRY KohonenMapWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam);
	HWND hWnd;
	CRITICAL_SECTION CriticalSection;
// Construction
public:
	KohonenMapWnd();
    HWND hwnd; 

// Attributes
private:
	int	m_points;
	double*	m_xPoints;
	double*	m_yPoints;
	double*	m_vxPoints;
	double*	m_vyPoints;
	double 
		m_xMax,
		m_xMin,
		m_yMax,
		m_yMin;

	int	m_wayPoints;
	int m_dx, m_dy;

	double*	m_xWay;
	double*	m_yWay;
	double*	m_vxWay;
	double*	m_vyWay;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Invalidate();
	virtual ~KohonenMapWnd();

	void CreateNewMap(int points);
	void Free();

	int GetPointsCount()
		{ return m_points; };
	void  SetPoints(double* xPoints, double* yPoints);

//	void  SetWay(short* way);
	void  SetWay(double* xPoints, double* yPoints, short count, int dx, int dy);

	int   Save(LPCTSTR szFile);
	int   Load(LPCTSTR szFile);

private:
	void  ReallocWay(short count);
	void  ExtremePoints();

	// Generated message map functions
protected:
//	//{{AFX_MSG(CMapWnd)
	void OnPaint(HWND hwnd);
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_MAPWND_H__76E52685_707A_4B28_995C_76B11948CB5A__INCLUDED_)
