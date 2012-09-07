
#include ".\Point.h"
#include ".\PolygonEx.h"


namespace geometry2D
{

enum { INSIDE, OUTSIDE, BOUNDARY };         // положение точки
//     ВНУТРИ, ВНЕ,     НА ГРАНИЦЕ
enum { TOUCHING, CROSSING, INESSENTIAL };   // положение ребра
//     КАСАТЕЛbНОЕ, ПЕРЕСЕКАЮЩЕЕ, НЕСУЩЕСТВЕННОЕ

bool pointInTriangle (Point p, Point a, Point b, Point c);
int pointInPolygon(Point &a, Polygon &p);
int pointInPolygon(Point &a, PolygonEx &p);
int edgeType (Point &a, Edge &e);

}