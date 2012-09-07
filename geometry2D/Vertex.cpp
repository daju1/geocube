#include "StdAfx.h"
#include ".\vertex.h"

namespace geometry2D
{
	/*
������ ������ Vertex ����� ���� ����������� �� ������ ����� ��� �� �� ����������� � � �.
*/

Vertex::Vertex(double x, double y) : Point (x,y)
{
}

Vertex::Vertex (Point &p) :
  Point (p)
{
}
/*
������������ ������� cw � ccw ���������� ��������� �� ������������� � ��������������� ������� ������� ��������������.
*/
Vertex *Vertex::cw(void)
{
  return (Vertex*)_next;
}

Vertex *Vertex::ccw(void)
{
  return (Vertex*)_prev;
}
/*
������������ ������� neighbor ��������, ����� �� ������� ��������� ���������� rotation, ��������� ���� �� �������� ���� ������������ CLOCKWISE ��� COUNTER_CLOCKWISE
*/
Vertex *Vertex::neighbor (int rotation)
{
  return ((rotation == CLOCKWISE) ? cw() : ccw());
}
/*
������������ ������� point ���������� ����� �� ���������, � ������� ��������� ������� �������
*/
Point Vertex::point(void)
{
  return  *((Point*)this);
}
/*
������������ ������� insert , remove � splice ������������� ����� ��������, ������������ � ������� ������ Node.
*/
Vertex *Vertex::insert (Vertex *v)
{
  return (Vertex *) (Node::insert (v));
}

Vertex *Vertex::remove (void)
{
  return (Vertex *) (Node::remove ());
}
void Vertex::splice (Vertex *b)
{
  Node::splice (b);
}
/*
�������, ��� � �������� insert � remove ����� ������� ������������ �������������� ������������ �������� � ���� ���������_��_Vert��. ����� �������������� ���������� ����� ������, ��� ���� C++ �� ����� ������������� ������������� ��������� �� �������� ������, ����� ������� �� ������ ������������ ������. ������� ����������� � ���, ��� ���������� ����� C++ �� ����� ���� ��������� � ���, ��� ������� ������ ������������ ������, �� ������� ����� �������, ��������� ������ �������� ������ �� ����������� ������ ���� ������ ������� ������������ ������ (��, � ������ �������, ���������� ����� C++ ������������� ����������� ��������� �� ����������� ����� ��� �������� �� ������ �������� ������, ��������� ������ ������ ������������ ������ �������� ������ ���� ������ �������� ������).

��������� ������������ ������� Vertex::split ����� ���������� ��������� ����.
*/

Vertex * Vertex::split(Vertex* b)
{
	// ��������� b� ����� �������� b
	Vertex *bp = b->ccw()->insert(new Vertex(b->point()));
	insert(new Vertex(point()));

	// ��������� �� ����� ������� �������
	splice(bp);
	return bp;
}
} // namespace
