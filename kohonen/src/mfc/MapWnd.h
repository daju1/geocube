#if !defined(AFX_MAPWND_H__76E52685_707A_4B28_995C_76B11948CB5A__INCLUDED_)
#define AFX_MAPWND_H__76E52685_707A_4B28_995C_76B11948CB5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MapWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMapWnd window

class CMapWnd : public CWnd
{
// Construction
public:
	CMapWnd();

// Attributes
private:
	short	m_points;
	short*	m_xPoints;
	short*	m_yPoints;

	short	m_wayPoints;
	short*	m_xWay;
	short*	m_yWay;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapWnd();

	void CreateNewMap(int points);
	void Free();

	short GetPointsCount()
		{ return m_points; };
	void  GetPoints(short* xPoints, short* yPoints);

	void  SetWay(short* way);
	void  SetWay(short* xPoints, short* yPoints, short count);

	int   Save(LPCTSTR szFile);
	int   Load(LPCTSTR szFile);

private:
	void  ReallocWay(short count);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMapWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPWND_H__76E52685_707A_4B28_995C_76B11948CB5A__INCLUDED_)
