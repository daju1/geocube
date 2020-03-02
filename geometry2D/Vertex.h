#pragma once
#include "./Node.h"
#include "./Point.h"

namespace geometry2D
{
	class Polygon;
	enum { CLOCKWISE,  COUNTER_CLOCKWISE};
	//(CLOCKWISE или COUNTER_CLOCKWISE — по часовой стрелке или против):

class Vertex: public Node, public  Point  {
 public:
	//Polygon * _neighbor_poly; // полигон, который по часовой стрелке слева
  Vertex (double x, double y);
  Vertex (const Point&);
  Vertex *cw(void);
  Vertex *ccw(void);
  Vertex *neighbor (int rotation);
  const Point & point (void) const;
  Vertex *insert (Vertex* );
  Vertex *remove (void);
  void splice (Vertex*);
  Vertex *split (Vertex*);
  friend class Polygon;

};


} // namespace
