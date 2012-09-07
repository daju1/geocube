#pragma once
#include "./point.h"
namespace geometry2D
{
	/*
������� �������������� � ���� ������� ������ Polygon. ����� �������� ��� �������� ������. ������ �� ���, _v, ��������� �� ��������� ������� �������� � ������� ������� ���� ��������. ����������� �������� � ���������� ��������� ���� � �������� ����, ���� � ������� � ����. ������ �� ����� ��������� �� ������� � ���� ��� �� ������� �������. �� ������ �������� ������, _size, �������� ������ ��������:
*/

class Vertex;
class VertexEx;
class PolygonEx {
 private:
  VertexEx *_v;
  int _size;
  void resize (void);
 public:
	 double _r; // ��� ������������ ������ ��������� ����������
	 size_t index;// ������ �������� � ������ ����� ������ ������� �� �������� ���� ������
	 // ��� �������������� �� ���������� ����� �� ������������
  PolygonEx (void);
  PolygonEx (PolygonEx&);
  PolygonEx (Vertex*);
  ~PolygonEx (void);
  Vertex *v(void);
  int size (void);
  Point point (void);
  Edge edge (void);
  Vertex *cw(void);
  Vertex *ccw (void);
  Vertex *neighbor (int rotation);
  Vertex *advance (int rotation);
  Vertex *setV (Vertex*);
  Vertex *insert (Point&);
  void remove (void);
  PolygonEx * split (Vertex*);
  void SetNeighborPolygon(Edge *,PolygonEx*);
  PolygonEx* GetNeighborPolygon();
};



} // namespace
