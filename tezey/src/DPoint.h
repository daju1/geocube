// DPoint.h: interface for the CDPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_)
#define DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class vdouble;

//====== Новый класс "Вещественная точка"
#ifdef CGRAPH2_ONE_PLOT
class CDPoint
{
public:
	double x;
	double y;		//===== Вещественные координаты

	//====== Конструктор по умолчанию
	CDPoint()
	{
		 x = 0.;
		 y = 0.;
	};
	~CDPoint()
	{
	};

	//====== Конструктор копирования
	CDPoint(const CDPoint& pt)
	{
		x = pt.x;
		y = pt.y; 
	}

	//====== Конструктор с параметрами
	CDPoint(double xx, double yy)
	{
		x = xx;
		y = yy;
	}
	
	//====== Операция умножения (увеличение в n раз)
	CDPoint operator*(int n)
	{
		return CDPoint (x*n,  y*n); 
	}

	//====== Операция присваивания
	CDPoint& operator=(const CDPoint& pt) 
	{
		x = pt.x;	
		y = pt.y;
		return *this;		// Возвращаем свой адрес
	}
	
	//====== Операция сложения двух точек
	CDPoint operator+(CDPoint& pt) 
	{
		return CDPoint(x + pt.x, y + pt.y);
	}
	
	//====== Операция вычитания двух точек
	CDPoint operator-(CDPoint& pt) 
	{
		return CDPoint(x - pt.x, y - pt.y);
	}
	
	// Метод для преобразования к типу CPoint (целая точка)
/*	CPoint ToInt() 
	{
		return CPoint(int(x),int(y));
	}*/
	
	//====== Операция сложения с записью результата
	void operator+=(CDPoint& pt) { x += pt.x;		y += pt.y; }
	
	//====== Операция вычитания с записью результата
	void operator-=(CDPoint& pt) { x -= pt.x;		y -= pt.y; }

	//====== Операция вычисления нормы вектора, заданного точкой
	double operator! () { return fabs(x) + fabs(y); }
};
#else
struct CDPoint
{
	double x;
	double y;
};
#endif

//typedef Vector<CDPoint> VECPTS;

struct CpVDPoints
{
	short toScaleX; // надо ли маснтабировать ось X
	bool toScaleY; // надо ли маснтабировать ось Y
	bool notGist; // not столбиками
	bool bTimeScale; // ось Х - ось времени
	bool toDraw; // надо ли рисовать
	double maxY;
	double minY;
	double maxX;
	double minX;
	char szTitle[255];
	char szXLabel[255];
	char szYLabel[255];
	vdouble* px; // указатель на вектор x 
	vdouble* py; // указатель на вектор y
//	Vector<SYSTEMTIME> *pt; // указатель на вектор времени
};

#endif // !defined(AFX_DPOINT_H__B2179A6F_0586_47CB_8DF6_C7B8D4F15D2C__INCLUDED_)
