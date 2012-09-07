#pragma once
#include "./point.h"
namespace geometry2D
{
	/*
������� �������������� � ���� ������� ������ Polygon. ����� �������� ��� �������� ������. ������ �� ���, _v, ��������� �� ��������� ������� �������� � ������� ������� ���� ��������. ����������� �������� � ���������� ��������� ���� � �������� ����, ���� � ������� � ����. ������ �� ����� ��������� �� ������� � ���� ��� �� ������� �������. �� ������ �������� ������, _size, �������� ������ ��������:
*/

class Vertex;
class Polygon {
 private:
  Vertex *_v;
  int _size;
  void resize (void);
 public:
  Polygon (void);
  Polygon (Polygon&);
  Polygon (Vertex*);
  ~Polygon (void);
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
  Polygon * split (Vertex*);
};



} // namespace
