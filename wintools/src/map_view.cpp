#include "stdafx.h"
#include "win32_views.h"	// config.h is here -> we get ENABLE-macros here...
map_view::map_view(Object * ob)
{
	zoom_x = 512;
	zoom_y = 512;

	lines_points_radius = 3.0;

	m_nCurVertPos = 50;
	m_nCurHorzPos = 50;

	this->m_ob = ob;
}
map_view::~map_view()
{
}
void map_view::MouseWhell(float yDelta, float x, float y)
{
	//ConvertFromScreenToWorld должна приводить к одним и тем же мировым точкам


	fGL y_scale_pre = this->GetYScale(); 
	fGL x_scale_pre = this->GetXScale(); 

	float x0_pre = this->x_center - (this->maxx - this->minx)/2 * x_scale_pre; 
	float y0_pre = this->y_center + (this->maxy - this->miny)/2 * y_scale_pre;

	double X_pre = this->minx + (x - x0_pre) / x_scale_pre;			
	double Y_pre = this->miny + (y0_pre - y) / y_scale_pre;

	if (yDelta > 0)
	{
		this->zoom_x *= 1.5;
		this->zoom_y *= 1.5;
	}
	else
	{
		this->zoom_x /= 1.5;
		this->zoom_y /= 1.5;
	}

	fGL y_scale = this->GetYScale(); 
	fGL x_scale = this->GetXScale(); 

	//double X = this->minx + (x - x0) / x_scale;			
	//double Y = this->miny + (y0 - y) / y_scale;

	double X = X_pre, Y = Y_pre;

	//(X - this->minx) = (x - x0) / x_scale;			
	//(Y - this->miny) = (y0 - y) / y_scale;

	//(X - this->minx) * x_scale = x - x0;			
	//(Y - this->miny) * y_scale = y0 - y;

	double x0 = x - (X - this->minx) * x_scale;			
	double y0 = (Y - this->miny) * y_scale + y;

	//float x0 = this->x_center - (this->maxx - this->minx)/2 * x_scale; 
	//float y0 = this->y_center + (this->maxy - this->miny)/2 * y_scale;

	//x0 + (this->maxx - this->minx)/2 * x_scale = this->x_center; 
	//y0 - (this->maxy - this->miny)/2 * y_scale = this->y_center;

	this->x_center = x0 + (this->maxx - this->minx)/2 * x_scale; 
	this->y_center = y0 - (this->maxy - this->miny)/2 * y_scale;
}

void map_view::ConvertFromScreenToWorld(float x, float y, double &X, double &Y)
{
	float x_scale = GetXScale(); 
	float y_scale = GetYScale(); 
	
	float x0 = x_center - (maxx - minx)/2 * x_scale; 
	float y0 = y_center + (maxy - miny)/2 * y_scale;	
			
	//x = x0 + (X - minx) * x_scale;			
	X = minx + (x - x0) / x_scale;			
	//y = y0 - (Y - miny) * y_scale;
	Y = miny + (y0 - y) / y_scale;
}

void map_view::ConvertFromWorldToScreen(double X, double Y, float & x, float & y )
{
	fGL x_scale = GetXScale(); 
	fGL y_scale = GetYScale(); 
	
	fGL x0 = x_center - (maxx - minx)/2 * x_scale; 
	fGL y0 = y_center + (maxy - miny)/2 * y_scale;	
			
	x = x0 + (X - minx) * x_scale;			
	y = y0 - (Y - miny) * y_scale;
}
float map_view::GetYScale()
{
	return float(this->zoom_y / max((this->maxx - this->minx), (this->maxy - this->miny))); 
}

float map_view::GetXScale()
{
	return float(this->zoom_x / max((this->maxx - this->minx), (this->maxy - this->miny))); 
}

void map_view::PreConvertingFromWorldToScreen()
{
	_x_scale = GetXScale(); 
	_y_scale = GetYScale(); 
	
	_x0 = x_center - (maxx - minx)/2 * _x_scale; 
	_y0 = y_center + (maxy - miny)/2 * _y_scale;

	/*printf("win_gdiplus_view::PreConvertingFromWorldToScreen()\n");
	printf("_x_scale = %f _y_scale = %f\n", _x_scale, _y_scale);
	printf("maxx = %f minx = %f\n", maxx, minx);
	printf("maxy = %f miny = %f\n", maxy, miny);
	printf("x_center = %f y_center = %f\n", x_center, y_center);
	printf("_x0 = %f _y0 = %f\n", _x0, _y0);
	printf("\n");*/
}

void map_view::ConvertingFromWorldToScreen(double X, double Y, float & x, float & y )
{			
	x = _x0 + (X - minx) * _x_scale;			
	y = _y0 - (Y - miny) * _y_scale;
}

void map_view::UpdateExtremums(void)
{
	if (this->m_ob)
	{
		CPoint2 profile_max;
		CPoint2 profile_min;

		if(this->m_ob->UpdateExtremums(profile_min, profile_max))
		{
			this->maxx = profile_max.x;
			this->maxy = profile_max.y;
			
			this->minx = profile_min.x;
			this->miny = profile_min.y;
		}
	}
}
bool map_view::calc_select_line(int mouse_x, int mouse_y, CPoint3& pt3)
{
	BlnProfile3D * profile = dynamic_cast<BlnProfile3D *>(this->m_ob);
	if(profile)
	{
		double X,Y;
		this->ConvertFromScreenToWorld(mouse_x, mouse_y, X, Y);
		return profile->Convert2D_To_3D(CPoint2(X,Y), pt3);
	}
	return false;
}

void map_view::VScroll( HWND hWnd, WORD wScroll )
{
	SCROLLINFO si;
	// Использовать функцию GetScrollInfo() для получения информации о 	
	// линейке прокрутки.
	//.......................................
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask  = SIF_ALL;
	GetScrollInfo( hWnd, SB_VERT, &si );
	RECT cltRect;
	GetClientRect( hWnd, &cltRect );
	
	int pageStep = 10;
	if (pageStep<1)
		pageStep=1;
	int lineStep = 1;
	if (lineStep<1)
		lineStep=1;

	switch( wScroll )
	{
	case SB_LINEDOWN :
		if ( m_nCurVertPos <= (int)(si.nMax - si.nPage) )
			m_nCurVertPos += 
			(int)(si.nMax - si.nPage) - m_nCurVertPos < lineStep ?
			(int)(si.nMax - si.nPage) - m_nCurVertPos : lineStep;        
		break;
	case SB_LINEUP :
		if ( m_nCurVertPos > 0 )
			m_nCurVertPos -= 
			lineStep <= m_nCurVertPos ? 
			lineStep : m_nCurVertPos;
		break;
	case SB_PAGEDOWN :
		if ( m_nCurVertPos <= (int)(si.nMax - si.nPage) )
			m_nCurVertPos += 
			(int)(si.nMax - si.nPage) - m_nCurVertPos < pageStep ?
			(int)(si.nMax - si.nPage) - m_nCurVertPos : pageStep;        
		break;
	case SB_PAGEUP :
		if ( m_nCurVertPos > 0 )
			m_nCurVertPos -= pageStep <= m_nCurVertPos
			? pageStep : m_nCurVertPos;
		break;
	case SB_THUMBTRACK :
		m_nCurVertPos -= si.nPos - si.nTrackPos;
		break;
	}	

	si.nPos  = m_nCurVertPos;
	fGL y_scale = this->GetYScale(); 
	double part_y =  2.0 * (double(si.nPos) / double(si.nMax - si.nPage) - 0.5);
	double win_center_y =  (cltRect.bottom + cltRect.top) / 2.0;
	this->y_center = win_center_y - part_y * (this->maxy - this->miny)/2 * y_scale;

	SetScrollInfo( hWnd, SB_VERT, &si, TRUE );
}


void map_view::HScroll( HWND hWnd, WORD wScroll )
{
	SCROLLINFO si;
	// Использовать функцию GetScrollInfo() для получения информации о 	
	// линейке прокрутки.
	//.......................................
	si.cbSize = sizeof( SCROLLINFO );
	si.fMask  = SIF_ALL;
	GetScrollInfo( hWnd, SB_HORZ, &si );
	RECT cltRect;
	GetClientRect( hWnd, &cltRect );
	
	int pageStep = 10;
	if (pageStep<1)
		pageStep=1;
	int lineStep = 1;
	if (lineStep<1)
		lineStep=1;
	switch( wScroll )
	{
	case SB_LINERIGHT :
		if ( m_nCurHorzPos <= (int)(si.nMax - si.nPage) )
			m_nCurHorzPos += 
			(int)(si.nMax - si.nPage) - m_nCurHorzPos < lineStep ?
			(int)(si.nMax - si.nPage) - m_nCurHorzPos : lineStep;
		break;        
	case SB_LINELEFT :
		if ( m_nCurHorzPos > 0 )
			m_nCurHorzPos -= 
			lineStep < m_nCurHorzPos ? 
			lineStep : m_nCurHorzPos;
		break;
	case SB_PAGERIGHT :
		if ( m_nCurHorzPos <= (int)(si.nMax - si.nPage) )
			m_nCurHorzPos += 
			(int)(si.nMax - si.nPage) - m_nCurHorzPos  < pageStep ?
			(int)(si.nMax - si.nPage) - m_nCurHorzPos : pageStep;        
		break;
	case SB_PAGELEFT :
		if ( m_nCurHorzPos > 0 )
			m_nCurHorzPos -= 
			pageStep <= m_nCurHorzPos ? 
			pageStep : m_nCurHorzPos;
		break;
	case SB_THUMBTRACK :
		m_nCurHorzPos -= si.nPos - si.nTrackPos;
		break;
	}
	si.nPos  = m_nCurHorzPos;
	fGL x_scale = this->GetXScale(); 
	double part_x =  2.0 * (double(si.nPos) / double(si.nMax - si.nPage) - 0.5);
	double win_center_x =  (cltRect.right - cltRect.left) / 2.0;
	this->x_center = win_center_x - part_x * (this->maxx - this->minx)/2 * x_scale;
	SetScrollInfo( hWnd, SB_HORZ, &si, TRUE );
}
