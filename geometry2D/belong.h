
#include ".\Point.h"
#include ".\PolygonEx.h"


namespace geometry2D
{

enum { INSIDE, OUTSIDE, BOUNDARY };         // ��������� �����
//     ������, ���,     �� �������
enum { TOUCHING, CROSSING, INESSENTIAL };   // ��������� �����
//     �������b���, ������������, ��������������

bool pointInTriangle (Point p, Point a, Point b, Point c);
int pointInPolygon(Point &a, Polygon &p);
int pointInPolygon(Point &a, PolygonEx &p);
int edgeType (Point &a, Edge &e);

}