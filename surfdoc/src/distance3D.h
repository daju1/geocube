//#include <windef.h> 
#include "points.h"
#include "../../surfdefs.h" //for OG_DOUBLE_PRECISION
double Distance(double x1, double y1, double x2, double y2);
double Distance(double x1, double y1, double z1, double x2, double y2, double z2);
float Distance(float x1, float y1, float x2, float y2);
#if OG_DOUBLE_PRECISION 
double Distance(CPoint3 pt1, CPoint3 pt2);
double Distance_xy(CPoint3 pt1, CPoint3 pt2);
double Distance(CPoint2 pt1, CPoint2 pt2);
double Distance(CPoint2 pt1, CPoint3 pt2);
#else // float precision
float Distance(CPoint3 pt1, CPoint3 pt2);
float Distance_xy(CPoint3 pt1, CPoint3 pt2);
float Distance(CPoint2 pt1, CPoint2 pt2);
float Distance(CPoint2 pt1, CPoint3 pt2);
#endif /*OG_DOUBLE_PRECISION*/

