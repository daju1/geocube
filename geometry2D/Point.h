#pragma once

namespace geometry2D
{
	//Клacc Point содержит элементы данных х и у для хранения координат очки. 
	//Компонентные функции обеспечивают выполнение операций по определению 
	//положения точки относительно заданного отрезка прямой линии и вычисления 
	//расстояния от заданной точки до прямой линии. Дополнительные компонентные 
	//функции рассматривают текущую точку как вектор и перегружают соответствующие 
	//операции для реализации векторной арифметики, используя ключевое слово 
	//operator. Включены также компонентные функции, возвращающие значения 
	//полярного угла и длины.



enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
//    СЛЕВА, СПРАВА, ВПЕРЕДИ, ПОЗАДИ, МЕЖДУ,   НАЧАЛО, КОНЕЦ

class Edge;
class Polygon;

class Point {
public:
	int index;//индекс
  double x;
  double y;
 Point(double _x = 0.0, double _y =0.0, int _index = -1);
 Point(const Point& p)
 {
	 x = p.x; y = p.y; index = p.index;
 }
 Point& operator=(const Point& p)
 {
	 if (this == &p)
		 return *this;
	 x = p.x; y = p.y; index = p.index;
	 return *this;
 }
  
  Point operator+(const Point&);
  Point operator-(const Point&);
  friend Point operator* (double, const Point&);
  
  // возвращает координату х, если в качестве индекса
  // координаты указано значение О, или координату у при индексе 1
  double operator[] (int);
  
  // одинаковы ли точки ?
  int operator== (const Point&) const;
  int operator!= (const Point&) const;
  
  // лексикографический порядок отношений, точка а < точки b,
  // если либо а.х < b.х, либо a.х = b.x и а.у < b.у.  
  int operator< (const Point&) const;
  int operator> (const Point&) const;
  
  bool LessThan (const Point &p, double epsilon) const;
  bool MoreThan (const Point &p, double epsilon) const;

  // Возвращается значение типа перечисления, указывающее на положение
  // точки относительно отрезка
  // enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
  //       СЛЕВА, СПРАВА, ВПЕРЕДИ, ПОЗАДИ, МЕЖДУ,   НАЧАЛО, КОНЕЦ
  int classify(Point&, Point&) const;
  int classify(Edge&) const;  // ребро вместо пары точек
  
  // Угол точки в полярной системе координат
  // возвращает -1, если точка = (0, 0)
  double polarAngle(void); 
  
  double length(void);  
  
  double distance(Edge&) const;
};


double dotProduct(const Point &p, const Point &q);
} // namespace
