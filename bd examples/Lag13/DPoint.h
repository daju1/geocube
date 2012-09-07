// DPoint.h: interface for the CDPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_)
#define AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <AFXWIN.H>
//====== ����� ����� "������������ �����"
/*
class CDPoint
{
public:
	double x;
	double y;		//===== ������������ ����������

	//====== ����������� �� ���������
	CDPoint();
	~CDPoint();

	//====== ����������� �����������
	CDPoint(const CDPoint& pt)
	{
		x = pt.x;
		y = pt.y; 
	}

	//====== ����������� � �����������
	CDPoint(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
	
	//====== �������� ��������� (���������� � n ���)
	CDPoint operator*(int n)
	{
		return CDPoint (x*n,  y*n); 
	}

	//====== �������� ������������
	CDPoint& operator=(const CDPoint& pt) 
	{
		x = pt.x;	
		y = pt.y;
		return *this;		// ���������� ���� �����
	}
	
	//====== �������� �������� ���� �����
	CDPoint operator+(CDPoint& pt) 
	{
		return CDPoint(x + pt.x, y + pt.y);
	}
	
	//====== �������� ��������� ���� �����
	CDPoint operator-(CDPoint& pt) 
	{
		return CDPoint(x - pt.x, y - pt.y);
	};
	
	// ����� ��� �������������� � ���� CPoint (����� �����)
	CPoint ToInt() 
	{
		return CPoint(int(x),int(y));
	}
	
	//====== �������� �������� � ������� ����������
	void operator+=(CDPoint& pt) { x += pt.x;		y += pt.y; }
	
	//====== �������� ��������� � ������� ����������
	void operator-=(CDPoint& pt) { x -= pt.x;		y -= pt.y; }

	//====== �������� ���������� ����� �������, ��������� ������
	double operator! () { return fabs(x) + fabs(y); }
};


typedef Vector<CDPoint> VECPTS;
*/

struct CpVDPoints
{
	bool toScaleX:true; // ���� �� �������������� ��� X
	bool toScaleY:true; // ���� �� �������������� ��� Y
	bool toDraw; // ���� �� ��������
	vdouble* px; // ��������� �� ������ x 
	vdouble* py; // ��������� �� ������ y 
};

#endif // !defined(AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_)
