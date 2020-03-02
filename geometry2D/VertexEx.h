#pragma once
#include "./Vertex.h"

namespace geometry2D
{
	class PolygonEx;
//	enum { CLOCKWISE,  COUNTER_CLOCKWISE};
	//(CLOCKWISE или COUNTER_CLOCKWISE — по часовой стрелке или против):

class VertexEx: public Vertex  {
public:
	PolygonEx * _neighbor_polygon; // полигон, который по часовой стрелке слева
	VertexEx (double x, double y);
    VertexEx (const Point&);
	friend class Polygon;
};


} // namespace
