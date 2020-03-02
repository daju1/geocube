#pragma once
#include "./Point.h"
namespace geometry2D
{
	/*
Полигон представляется в виде объекта класса Polygon. Класс содержит два элемента данных. Первый из них, _v, указывает на некоторую вершину полигона — текущую позицию окна полигона. Большинство операций с полигонами относятся либо к текущему окну, либо к вершите в окне. Иногда мы будем ссылаться на вершину в окне как на текущую вершину. Во втором элементе данных, _size, хранится размер полигона:
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
  int size (void) const;
  const Point & point (void) const;
  const Edge edge (void) const;
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
