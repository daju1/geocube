#pragma once
#include "./point.h"

namespace geometry2D
{
	/*
��������� �������������� ���������� ����������� ������ ����� � ��� ��� ���� �����. ������� ������ ����� p0p1 ������� �� ���� �������� ����� �0 � p1 ������ � �������, �������� ����� ����. ����� ����� ������� ���������� ����� �0 � p1, �� �� ������� � ������������ ������� ������ ����� �0�1. �������� ����� �0 �������� ������� ������������� ������� ������ �����, � ����� p1 � ��� ������. ������ ������������ ������� ������ ����� ����� �������� ������, ���� �� ������������ ����� ������� ���������� ��������. ����� ���������� ����� �������, ��� ���������� ����� �������� ������������� ������ ������ �� ����. ����������� (������������) ������ ����� ������������ ����� ������� � ���������� �� ������ ����� �� ������. ��� �������� ��������������� ������ ������, ������������ � ����� ������ � ���������� ����� ������ �����.

����� Edge (�����, ����� �����)
����� Edge, ����������� ��� ������������� ���� ���� ������ �����. �� ������������ ��������� �������: 
*/
enum { COLLINEAR, PARALLEL, SKEW, SKEW_CROSS, SKEW_NO_CROSS };

	
class Edge {
 public:
  Point org;
  Point dest;
  Edge (Point &_org, Point &_dest);
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
	EdgeEx (Point &_org, Point &_dest);
	EdgeEx (void);
	EdgeEx(const EdgeEx &);
	EdgeEx(const Edge &);
	~EdgeEx (void);
};


} // namespace
