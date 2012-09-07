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
  
  Point operator+(Point&);  
  Point operator-(Point&);  
  friend Point operator* (double, Point&);
  
  // возвращает координату х, если в качестве индекса
  // координаты указано значение О, или координату у при индексе 1
  double operator[] (int);
  
  // одинаковы ли точки ?
  int operator== (Point&);
  int operator!= (Point&);
  
  // лексикографический порядок отношений, точка а < точки b,
  // если либо а.х < b.х, либо a.х = b.x и а.у < b.у.  
  int operator< (Point&);
  int operator> (Point&); 
  
  bool LessThan (Point &p, double epsilon);
  bool MoreThan (Point &p, double epsilon);

  // Возвращается значение типа перечисления, указывающее на положение
  // точки относительно отрезка
  // enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
  //       СЛЕВА, СПРАВА, ВПЕРЕДИ, ПОЗАДИ, МЕЖДУ,   НАЧАЛО, КОНЕЦ
  int classify(Point&, Point&);
  int classify(Edge&);  // ребро вместо пары точек
  
  // Угол точки в полярной системе координат
  // возвращает -1, если точка = (0, 0)
  double polarAngle(void); 
  
  double length(void);  
  
  double distance(Edge&);  
};


double dotProduct(Point &p, Point &q);
} // namespace