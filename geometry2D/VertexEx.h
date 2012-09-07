#pragma once
#include "./vertex.h"

namespace geometry2D
{
	class PolygonEx;
//	enum { CLOCKWISE,  COUNTER_CLOCKWISE};
	//(CLOCKWISE ��� COUNTER_CLOCKWISE � �� ������� ������� ��� ������):

class VertexEx: public Vertex  {
public:
	PolygonEx * _neighbor_polygon; // �������, ������� �� ������� ������� �����
	VertexEx (double x, double y);
	VertexEx (Point&);
	friend class Polygon;
};


} // namespace