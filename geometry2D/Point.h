#pragma once

namespace geometry2D
{
	//��acc Point �������� �������� ������ � � � ��� �������� ��������� ����. 
	//������������ ������� ������������ ���������� �������� �� ����������� 
	//��������� ����� ������������ ��������� ������� ������ ����� � ���������� 
	//���������� �� �������� ����� �� ������ �����. �������������� ������������ 
	//������� ������������� ������� ����� ��� ������ � ����������� ��������������� 
	//�������� ��� ���������� ��������� ����������, ��������� �������� ����� 
	//operator. �������� ����� ������������ �������, ������������ �������� 
	//��������� ���� � �����.



enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
//    �����, ������, �������, ������, �����,   ������, �����

class Edge;
class Polygon;

class Point {
public:
	int index;//������
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
  
  // ���������� ���������� �, ���� � �������� �������
  // ���������� ������� �������� �, ��� ���������� � ��� ������� 1
  double operator[] (int);
  
  // ��������� �� ����� ?
  int operator== (Point&);
  int operator!= (Point&);
  
  // ������������������ ������� ���������, ����� � < ����� b,
  // ���� ���� �.� < b.�, ���� a.� = b.x � �.� < b.�.  
  int operator< (Point&);
  int operator> (Point&); 
  
  bool LessThan (Point &p, double epsilon);
  bool MoreThan (Point &p, double epsilon);

  // ������������ �������� ���� ������������, ����������� �� ���������
  // ����� ������������ �������
  // enum {LEFT,  RIGHT,  BEYOND,  BEHIND, BETWEEN, ORIGIN, DESTINATION};
  //       �����, ������, �������, ������, �����,   ������, �����
  int classify(Point&, Point&);
  int classify(Edge&);  // ����� ������ ���� �����
  
  // ���� ����� � �������� ������� ���������
  // ���������� -1, ���� ����� = (0, 0)
  double polarAngle(void); 
  
  double length(void);  
  
  double distance(Edge&);  
};


double dotProduct(Point &p, Point &q);
} // namespace