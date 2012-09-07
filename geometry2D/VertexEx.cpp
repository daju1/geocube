#include "StdAfx.h"
#include ".\vertexEx.h"

namespace geometry2D
{
	/*
Объект класса Vertex может быть сформирован на основе точки или по ее координатам х и у.
*/

VertexEx::VertexEx(double x, double y) : Vertex (x,y)
{
	this->_neighbor_polygon = NULL;
}

VertexEx::VertexEx (Point &p) :
  Vertex (p)
{
	this->_neighbor_polygon = NULL;
}

} // namespace
