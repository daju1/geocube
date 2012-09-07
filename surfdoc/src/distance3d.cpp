#include "stdafx.h"
#include "distance3D.h"
//#include "math.h"
double Distance(double x1, double y1, double x2, double y2)
{
	return sqrt
		( 
		(x1 - x2)*(x1 - x2) +
		(y1 - y2)*(y1 - y2)
		);
}
double Distance(double x1, double y1, double z1, double x2, double y2, double z2)
{
	return sqrt
		( 
		(x1 - x2)*(x1 - x2) +
		(y1 - y2)*(y1 - y2) +
		(z1 - z2)*(z1 - z2)
		);
}

float Distance(float x1, float y1, float x2, float y2)
{
	return sqrt
		( 
		(x1 - x2)*(x1 - x2) +
		(y1 - y2)*(y1 - y2)
		);
}
#if OG_DOUBLE_PRECISION 
double Distance(CPoint3 pt1, CPoint3 pt2)
{
	return sqrt( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) +
		(pt1.z - pt2.z)*(pt1.z - pt2.z) );
}
double Distance_xy(CPoint3 pt1, CPoint3 pt2)
{
	return sqrt( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) );
}
double Distance(CPoint2 pt1, CPoint2 pt2)
{
	return sqrt( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) );
}
double Distance(CPoint2 pt1, CPoint3 pt2)
{
	return sqrt( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) );
}
#else // float precision
float Distance(CPoint3 pt1, CPoint3 pt2)
{
	return sqrtf( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) +
		(pt1.z - pt2.z)*(pt1.z - pt2.z) );
}
float Distance_xy(CPoint3 pt1, CPoint3 pt2)
{
	return sqrtf( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) );
}
float Distance(CPoint2 pt1, CPoint2 pt2)
{
	return sqrt( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) );
}
float Distance(CPoint2 pt1, CPoint3 pt2)
{
	return sqrt( 
		(pt1.x - pt2.x)*(pt1.x - pt2.x) +
		(pt1.y - pt2.y)*(pt1.y - pt2.y) );
}
#endif /*OG_DOUBLE_PRECISION*/

