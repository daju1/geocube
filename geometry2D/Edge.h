#pragma once
#include "./Point.h"

namespace geometry2D
{
	/*
Множество геометрических алгоритмов затрагивает прямые линии в той или иной форме. Отрезок прямой линии p0p1 состоит из двух концевых точек р0 и p1 вместе с точками, лежащими между ними. Когда важен порядок следования точек р0 и p1, то мы говорим о направленном отрезке прямой линии р0р1. Концевая точка р0 является началом направленного отрезка прямой линии, а точка p1 — его концом. Обычно направленный отрезок прямой линии будем называть ребром, если он представляет собой сторону некоторого полигона. Ребро направлено таким образом, что внутренняя часть полигона располагается всегда справа от него. Бесконечная (направленная) прямая линия определяется двумя точками и направлена от первой точки ко второй. Луч является полубесконечной прямой линией, начинающейся в точке начала и проходящей через вторую точку.

Класс Edge (Ребро, любые линии)
Класс Edge, применяется для представления всех форм прямых линий. Он определяется следующим образом: 
*/
enum { COLLINEAR, PARALLEL, SKEW, SKEW_CROSS, SKEW_NO_CROSS };

	
class Edge {
 public:
  Point org;
  Point dest;
  Edge (const Point &_org, const Point &_dest);
  Edge (void);
  Edge &rot (void);
  Edge &flip (void);
  Point point (double);
  int intersect (Edge&, double&);
  int cross (Edge&, double&);
  bool isVertical(void);
  double slope(void);
  double y(double);
};

class PolygonEx;

class EdgeEx : public Edge {
protected:
	PolygonEx * _lpoly;
	PolygonEx * _rpoly;
public:
	PolygonEx * LeftPolygon();
	PolygonEx * RightPolygon();
	void LeftPolygon(PolygonEx * );
	void RightPolygon(PolygonEx * );
    EdgeEx (const Point &_org, const Point &_dest);
	EdgeEx (void);
	EdgeEx(const EdgeEx &);
	EdgeEx(const Edge &);
	~EdgeEx (void);
};


} // namespace
