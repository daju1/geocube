#pragma once
#include "./node.h"
#include "./point.h"

namespace geometry2D
{
	class Polygon;
	enum { CLOCKWISE,  COUNTER_CLOCKWISE};
	//(CLOCKWISE или COUNTER_CLOCKWISE — по часовой стрелке или против):

class Vertex: public Node, public  Point  {
 public:
	//Polygon * _neighbor_poly; // полигон, который по часовой стрелке слева
  Vertex (double x, double y);
  Vertex (Point&);
  Vertex *cw(void);
  Vertex *ccw(void);
  Vertex *neighbor (int rotation);
  Point point (void);
  Vertex *insert (Vertex* );
  Vertex *remove (void);
  void splice (Vertex*);
  Vertex *split (Vertex*);
  friend class Polygon;

};


} // namespace