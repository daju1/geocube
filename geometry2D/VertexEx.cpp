#include "StdAfx.h"
#include "./VertexEx.h"

namespace geometry2D
{
	/*
ќбъект класса Vertex может быть сформирован на основе точки или по ее координатам х и у.
*/

VertexEx::VertexEx(double x, double y) : Vertex (x,y)
{
	this->_neighbor_polygon = NULL;
}

VertexEx::VertexEx (const Point &p) :
  Vertex (p)
{
	this->_neighbor_polygon = NULL;
}

} // namespace
