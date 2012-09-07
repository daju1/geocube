// MapWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MapWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapWnd

CMapWnd::CMapWnd() : m_xPoints(NULL), m_yPoints(NULL), m_points(0), m_wayPoints(0), m_xWay(NULL), m_yWay(NULL)
{
}

CMapWnd::~CMapWnd()
{
	Free();
}


BEGIN_MESSAGE_MAP(CMapWnd, CWnd)
	//{{AFX_MSG_MAP(CMapWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapWnd message handlers

// ------------------------------------------------------------
// WM_PAINT - paint the window
//
void CMapWnd::OnPaint() 
{
	CPaintDC	dc(this); // device context for painting
	RECT		rc;
	int			i;

	GetClientRect(&rc);

	dc.Rectangle(&rc);


	if (m_points != 0)
	{
		// points
		for (i = 0; i < m_points; i++)
		{
			dc.FillSolidRect(m_xPoints[i] - 2, rc.bottom - (m_yPoints[i] - 2), 5, 5, RGB(0, 192, 0));
		}

		// way
		if (m_wayPoints > 1)
		{
			dc.MoveTo(m_xWay[m_wayPoints - 1], rc.bottom - m_yWay[m_wayPoints - 1]);

			for (i = 0; i < m_wayPoints; i++)
			{
				dc.LineTo(m_xWay[i], rc.bottom - m_yWay[i]);
			}
		}
	}
}



// ------------------------------------------------------------
// create new map
//
void CMapWnd::CreateNewMap(int points)
{
	int		i;
	RECT	rc;

	// free old map
	Free();

	srand(GetTickCount());
	GetClientRect(&rc);
	rc.right	-= 6;
	rc.bottom	-= 6;

	m_points = points;

	m_xPoints	= new short[points];
	m_yPoints	= new short[points];

	for (i = 0; i < points; i++)
	{
		m_xPoints[i] = (rand() % rc.right) + 3;
		m_yPoints[i] = (rand() % rc.bottom) + 3;
	}

	Invalidate();
}



// ------------------------------------------------------------
// free map
//
void CMapWnd::Free()
{
	// free cities
	if (m_xPoints)
	{
		delete [] m_xPoints;
		m_xPoints = NULL;
	}
	if (m_yPoints)
	{
		delete [] m_yPoints;
		m_yPoints = NULL;
	}
	// free way
	if (m_xWay)
	{
		delete [] m_xWay;
		m_xWay = NULL;
	}
	if (m_yWay)
	{
		delete [] m_yWay;
		m_yWay = NULL;
	}

	m_points	= 0;
	m_wayPoints = 0;
}



// ------------------------------------------------------------
// realloc way 
//
void CMapWnd::ReallocWay(short count)
{
	if (m_wayPoints != count)
	{
		// free old
		if (m_wayPoints != 0)
		{
			delete [] m_xWay;
			delete [] m_yWay;
		}

		m_wayPoints = count;

		// alloc new
		m_xWay = new short[m_wayPoints];
		m_yWay = new short[m_wayPoints];
	}
}



// ------------------------------------------------------------
// get points
//
void CMapWnd::GetPoints(short* xPoints, short* yPoints)
{
	memcpy(xPoints, m_xPoints, m_points * sizeof(short));
	memcpy(yPoints, m_yPoints, m_points * sizeof(short));
}



// ------------------------------------------------------------
// set way
//
void CMapWnd::SetWay(short* way)
{
	int		i;

	ReallocWay(m_points);

	// create way of coordinate
	for (i = 0; i < m_wayPoints; i++)
	{
		m_xWay[i] = m_xPoints[way[i]];
		m_yWay[i] = m_yPoints[way[i]];
	}
	Invalidate();
}



// ------------------------------------------------------------
// set way
//
void CMapWnd::SetWay(short* xPoints, short* yPoints, short count)
{
	int		i;

	ReallocWay(count);

	for (i = 0; i < m_wayPoints; i++)
	{
		m_xWay[i] = xPoints[i];
		m_yWay[i] = yPoints[i];
	}
	Invalidate();
}



// ------------------------------------------------------------
// save map
//
int CMapWnd::Save(LPCTSTR szFile)
{
	FILE*		fp;
	short		i;

	// open file
	if ((fp = _tfopen(szFile, _T("w"))) == NULL)
		return 1;

	// save cities count
	_ftprintf(fp, _T("#%d\n"), m_points);

	// save all point
	for (i = 0; i < m_points; i++)
	{
		_ftprintf(fp, _T("%d %d\n"), m_xPoints[i], m_yPoints[i]);
	}

	fclose(fp);

	return 0;
}



// ------------------------------------------------------------
// load map
//
int CMapWnd::Load(LPCTSTR szFile)
{
	FILE*		fp;
	TCHAR*		sz;
	short		i;
	int			x, y, r = 0;

	// open file
	if ((fp = _tfopen(szFile, _T("r"))) == NULL)
		return 1;

	// free previous map
	Free();

	// alloc some memory
	sz = new TCHAR[128];

	// read point count
	if ((_fgetts(sz, 127, fp) != NULL) && (_stscanf(sz, _T("#%d"), &m_points) == 1))
	{
		m_xPoints	= new short[m_points];
		m_yPoints	= new short[m_points];

		// read all the points
		for (i = 0; i < m_points; i++)
		{
			// read & scanf, break if failed
			if ((_fgetts(sz, 127, fp) == NULL) || (_stscanf(sz, _T("%d %d"), &x, &y) != 2))
				break;

			m_xPoints[i] = (short) x;
			m_yPoints[i] = (short) y;
		}

		// free map, if failed
		if (i != m_points)
		{
			Free();
			r = 1;
		}
	}
	else
		r = 1;	// error


	// free file and mem
	fclose(fp);
	delete [] sz;

	// redraw map
	Invalidate();

	return r;
}
