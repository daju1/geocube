// MapWnd.cpp : implementation file
//

#include "../stdafx.h"
#include "stdafx.h"
#include "KohonenMapWnd.h"


/////////////////////////////////////////////////////////////////////////////
// CMapWnd

KohonenMapWnd::KohonenMapWnd() : 
m_xPoints(NULL), m_yPoints(NULL), 
m_vxPoints(NULL), m_vyPoints(NULL), 
m_points(0), m_wayPoints(0), 
m_xWay(NULL), m_yWay(NULL), 
m_vxWay(NULL), m_vyWay(NULL)
{
	InitializeCriticalSection(&CriticalSection);
}

KohonenMapWnd::~KohonenMapWnd()
{
	Free();
	DeleteCriticalSection(&CriticalSection);
}

/*
BEGIN_MESSAGE_MAP(CMapWnd, CWnd)
	//{{AFX_MSG_MAP(CMapWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
*/

/////////////////////////////////////////////////////////////////////////////
// CMapWnd message handlers

// ------------------------------------------------------------
// WM_PAINT - paint the window
//
void KohonenMapWnd::OnPaint(HWND hwnd) 
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT		rc;	
	int			i;
	hdc = BeginPaint(hwnd, &ps); 

	GetClientRect(hwnd, &rc);
	Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//	char str[255];
//	sprintf(str, "m_points = %d m_wayPoints = %d",m_points, m_wayPoints);
//	TextOut(hdc, 10, 10, str, strlen(str)); 
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if (m_points != 0)
	{
		// points
		for (i = 0; i < m_points; i++)
		{
			m_vxPoints[i] = rc.left + (rc.right - rc.left)*(m_xPoints[i] - m_xMin) / (m_xMax - m_xMin);
			m_vyPoints[i] = rc.top + (rc.bottom - rc.top)*(m_yMax - m_yPoints[i]) / (m_yMax - m_yMin);

			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//			char str[255];
//			sprintf(str, "%d %f %f", i, m_xPoints[i], m_yPoints[i]);
//			TextOut(hdc, -70, i*15, str, strlen(str)); 
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			RECT r;
			HBRUSH hbrush, hbrushOld;
			r.left		= m_vxPoints[i] - 2;
			r.top		= m_vyPoints[i] - 2;
			r.right		= r.left + 5;
			r.bottom	= r.top + 5;
			hbrush = CreateSolidBrush(RGB(0, 192, 0));
			hbrushOld = (HBRUSH__ *)SelectObject(hdc, hbrush);

			FillRect(hdc, &r, hbrush);

			//dc.FillSolidRect(m_xPoints[i] - 2, m_yPoints[i] - 2, 5, 5, RGB(0, 192, 0));
			SelectObject(hdc, hbrushOld);
			DeleteObject(hbrush);
		}

		// way
		if (m_wayPoints > 1)
		{
			for (i = 0; i < m_wayPoints; i++)
			{
				m_vxWay[i] = rc.left + (rc.right - rc.left)*(m_xWay[i] - m_xMin) / (m_xMax - m_xMin);
				m_vyWay[i] = rc.top + (rc.bottom - rc.top)*(m_yMax - m_yWay[i]) / (m_yMax - m_yMin);

				if (m_vxWay[i] <= rc.left) m_vxWay[i] = rc.left+1;
				if (m_vxWay[i] >= rc.right) m_vxWay[i] = rc.right-1;

				if (m_vyWay[i] <= rc.top) m_vyWay[i] = rc.top+1;
				if (m_vyWay[i] >= rc.bottom) m_vyWay[i] = rc.bottom-1;
			}
#if 1
#if 0
			MoveToEx(hdc, m_vxWay[m_wayPoints - 1], m_vyWay[m_wayPoints - 1],
				(LPPOINT) NULL);

			for (i = 0; i < m_wayPoints; i++)
			{
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//				char str[255];
//				sprintf(str, "%d %f %f %f %f", i,  m_xWay[i], m_yWay[i],  m_vxWay[i], m_vyWay[i]);
//				TextOut(hdc, 50, 20+i*20, str, strlen(str)); 
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				LineTo(hdc, m_vxWay[i], m_vyWay[i]);
			}
#else
			for (int y = 0; y < m_dy; y++)
			{	
				i = y*m_dx;
				MoveToEx(hdc, m_vxWay[i], m_vyWay[i],
					(LPPOINT) NULL);		
				for (int x = 1; x < m_dx; x++)
				{
					i = y*m_dx + x;
					LineTo(hdc, m_vxWay[i], m_vyWay[i]);
				}
			}
			for (int x = 0; x < m_dx; x++)
			{	
				i = x*m_dy;
				MoveToEx(hdc, m_vxWay[i], m_vyWay[i],
					(LPPOINT) NULL);		
				for (int y = 1; y < m_dy; y++)
				{
					i = x*m_dy + y;
					LineTo(hdc, m_vxWay[i], m_vyWay[i]);
				}
			}
#endif
//#else
			DWORD dwRadius = 5; 
			float xStartAngle = 0; 
			float xSweepAngle = 360; 

			for (i = 0; i < m_wayPoints; i++)
			{
				MoveToEx(hdc, m_vxWay[i]+dwRadius, m_vyWay[i], (LPPOINT) NULL); 
				AngleArc(
					hdc, 
					m_vxWay[i], 
					m_vyWay[i], 
					dwRadius, 
					xStartAngle, 
					xSweepAngle); 
			}
#endif
		}
	}
	EndPaint(hwnd, &ps); 
}



// ------------------------------------------------------------
// create new map
//
void KohonenMapWnd::CreateNewMap(int points)
{
	int		i;
	RECT	rc;

	// free old map
	Free();

	srand(GetTickCount());
	GetClientRect(hwnd, &rc);
	rc.right	-= 6;
	rc.bottom	-= 6;

	m_points = points;

char str[255];
sprintf(str, "m_points = %d points=%d", m_points, points);
MessageBox(0, str, "CreateMap", 0);

	m_xPoints	= new double[points];
	m_yPoints	= new double[points];

	m_vxPoints	= new double[points];
	m_vyPoints	= new double[points];

	for (i = 0; i < points; i++)
	{
//		m_xPoints[i] = (rand() % rc.right) + 3;
//		m_yPoints[i] = (rand() % rc.bottom) + 3;
	}

	Invalidate();
}



// ------------------------------------------------------------
// free map
//
void KohonenMapWnd::Free()
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
	if (m_vxPoints)
	{
		delete [] m_vxPoints;
		m_vxPoints = NULL;
	}
	if (m_vyPoints)
	{
		delete [] m_vyPoints;
		m_vyPoints = NULL;
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
	if (m_vxWay)
	{
		delete [] m_vxWay;
		m_vxWay = NULL;
	}
	if (m_vyWay)
	{
		delete [] m_vyWay;
		m_vyWay = NULL;
	}

	m_points	= 0;
	m_wayPoints = 0;
}



// ------------------------------------------------------------
// realloc way 
//
void KohonenMapWnd::ReallocWay(short count)
{
	if (m_wayPoints != count)
	{
		// free old
		if (m_wayPoints != 0)
		{
			delete [] m_xWay;
			delete [] m_yWay;
			delete [] m_vxWay;
			delete [] m_vyWay;
		}

		m_wayPoints = count;

		// alloc new
		m_xWay  = new double[m_wayPoints];
		m_yWay  = new double[m_wayPoints];
		m_vxWay = new double[m_wayPoints];
		m_vyWay = new double[m_wayPoints];
	}
}



// ------------------------------------------------------------
// get points
//
void KohonenMapWnd::SetPoints(double* xPoints, double* yPoints)
{
	LeaveCriticalSection(&CriticalSection);
	memcpy(m_xPoints, xPoints, m_points * sizeof(double));
	memcpy(m_yPoints, yPoints, m_points * sizeof(double));
	LeaveCriticalSection(&CriticalSection);
	ExtremePoints();
	Invalidate();
}

void KohonenMapWnd::ExtremePoints()
{
	for (int i = 0; i < m_points; i++)
	{
		if ( i == 0 )
		{
			m_xMax = m_xMin = m_xPoints[i];
			m_yMax = m_yMin = m_yPoints[i];
		}
		else
		{
			if (m_xMax < m_xPoints[i]) m_xMax = m_xPoints[i];
			if (m_xMin > m_xPoints[i]) m_xMin = m_xPoints[i];
			if (m_yMax < m_yPoints[i]) m_yMax = m_yPoints[i];
			if (m_yMin > m_yPoints[i]) m_yMin = m_yPoints[i];
		}
	}
}



// ------------------------------------------------------------
// set way
//
/*/
void KohonenMapWnd::SetWay(short* way)
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
}*/



// ------------------------------------------------------------
// set way
//
void KohonenMapWnd::SetWay(double* xPoints, double* yPoints, short count, int dx, int dy)
{
	int		i;

	this->m_dx = dx;
	this->m_dy = dy;

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
int KohonenMapWnd::Save(LPCTSTR szFile)
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
int KohonenMapWnd::Load(LPCTSTR szFile)
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
		m_xPoints	= new double[m_points];
		m_yPoints	= new double[m_points];

		m_vxPoints	= new double[m_points];
		m_vyPoints	= new double[m_points];

		// read all the points
		for (i = 0; i < m_points; i++)
		{
			// read & scanf, break if failed
			if ((_fgetts(sz, 127, fp) == NULL) || (_stscanf(sz, _T("%d %d"), &x, &y) != 2))
				break;

			m_xPoints[i] = (double) x;
			m_yPoints[i] = (double) y;
		}


		// free map, if failed
		if (i != m_points)
		{
			Free();
			r = 1;
		}
		ExtremePoints();
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

void KohonenMapWnd::Invalidate()
{
	RECT rect;
	GetClientRect(hwnd,&rect);

	rect.top		-= 3;
	rect.bottom		+= 3;
	rect.left		-= 3;
	rect.right		+= 3;

	InvalidateRect(hwnd,&rect, true);
}
