
#include "./Point.h"
#include "./PolygonEx.h"


namespace geometry2D
{

enum { INSIDE, OUTSIDE, BOUNDARY };         // ïîëîæåíèå òî÷êè
//     ÂÍÓÒÐÈ, ÂÍÅ,     ÍÀ ÃÐÀÍÈÖÅ
enum { TOUCHING, CROSSING, INESSENTIAL };   // ïîëîæåíèå ðåáðà
//     ÊÀÑÀÒÅËbÍÎÅ, ÏÅÐÅÑÅÊÀÞÙÅÅ, ÍÅÑÓÙÅÑÒÂÅÍÍÎÅ

bool pointInTriangle (Point p, Point a, Point b, Point c);
int pointInPolygon(Point &a, Polygon &p);
int pointInPolygon(Point &a, PolygonEx &p);
int edgeType (Point &a, Edge &e);

}
