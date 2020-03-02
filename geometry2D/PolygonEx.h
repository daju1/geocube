#pragma once
#include "./Point.h"
namespace geometry2D
{
	/*
Полигон представляется в виде объекта класса Polygon. Класс содержит два элемента данных. Первый из них, _v, указывает на некоторую вершину полигона — текущую позицию окна полигона. Большинство операций с полигонами относятся либо к текущему окну, либо к вершите в окне. Иногда мы будем ссылаться на вершину в окне как на текущую вершину. Во втором элементе данных, _size, хранится размер полигона:
*/

class Vertex;
class VertexEx;
class PolygonEx {
 private:
  VertexEx *_v;
  int _size;
  void resize (void);
 public:
	 double _r; // для треугольника радиус описанной окружности
	 size_t index;// индекс полигона в списке класс никоим образом не изменяет этот индекс
	 // вся ответсвенность за индексацию лежит на программисте
  PolygonEx (void);
  PolygonEx (PolygonEx&);
  PolygonEx (Vertex*);
  ~PolygonEx (void);
  Vertex *v(void) const;
  int size (void) const;
  const Point & point (void) const;
  Edge edge (void) const;
  Vertex *cw(void);
  Vertex *ccw (void);
  Vertex *neighbor (int rotation);
  Vertex *advance (int rotation);
  Vertex *setV (Vertex*);
  Vertex *insert (Point&);
  void remove (void);
  PolygonEx * split (Vertex*);
  void SetNeighborPolygon(const Edge&,PolygonEx*);
  PolygonEx* GetNeighborPolygon();
};



} // namespace
