
#pragma once
#ifndef __POINTS_H__
#define __POINTS_H__

#include "../../surfdefs.h" // define OG_DOUBLE_PRECISION
#if defined (_MSC_VER) && !defined (QT_PROJECT)
#else
#include "mywindows.h"
#endif
#if OG_DOUBLE_PRECISION 
class CPoint4	
{
public:
	double x, y, z, v;	// Координаты точки
	bool bVisible;
	//====== Конструктор по умолчанию
	CPoint4 () { x = y = z = v = 0; bVisible = true;}
	//====== Конструктор с параметрами
	CPoint4 (double c1, double c2, double c3, double c4)
	{
		x = double(c1);
		y = double(c2);
		z = double(c3);
		v = double(c4);
		bVisible = true;
	}
	CPoint4 (double c1, double c2, double c3, double c4, bool bvisible)
	{
		x = double(c1);
		y = double(c2);
		z = double(c3);
		v = double(c4);
		bVisible = bvisible;
	}
	//====== Операция присвоения
	CPoint4& operator=(const CPoint4& pt)
	{
		if (this == &pt)
			return *this;

		x = pt.x;
		y = pt.y;
		z = pt.z;
		v = pt.v;
		bVisible = pt.bVisible;
		return *this;
	}
	bool operator==(const CPoint4& pt)
	{
		return( x == pt.x && y == pt.y && z == pt.z && v == pt.v);
	}
	bool operator!=(const CPoint4& pt)
	{
		return( x != pt.x || y != pt.y || z != pt.z || v != pt.v);
	}
	//====== Операция сдвига в пространстве
	CPoint4& operator+=(const CPoint4& pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		return *this;
	}
	//====== Конструктор копирования
	CPoint4 (const CPoint4& pt)
	{
		*this = pt;
	}
};
#pragma optimize( "dagtp", off )

//class CPoint3;
// CPoint3 flags
#define CPOINT3_FLAG_NONORMAL								0x00000001
#define CPOINT3_FLAG_SELECTED								0x00000002
#define CPOINT3_FLAG_HIDE									0x00000004
#define CPOINT3_FLAG_HIDE_LINE								0x00000008
//#define CPOINT3_FLAG_WELL_PODOSHV_PESOK_NOT_GLIN			0x00000010
#define CPOINT3_FLAG_BLANKED								0x00000020
//#define CPOINT3_FLAG_										0x00000040
//#define CPOINT3_FLAG_										0x00000080

//====== Точка 3D-пространства
class CPoint3	
{
public:
	double x, y, z;	// Координаты точки
	bool bVisible;
	unsigned long flag;
	//====== Конструктор по умолчанию
	CPoint3 () { x = y = z = 0; bVisible = true; flag = 0;}
	//====== Конструктор с параметрами
	CPoint3 (double c1, double c2, double c3)
	{
		x = double(c1);
		y = double(c2);
		z = double(c3);
		bVisible = true;
		flag = 0;
	}
	CPoint3 (double c1, double c2, double c3, bool bvisible)
	{
		x = double(c1);
		y = double(c2);
		z = double(c3);
		bVisible = bvisible;
		flag = 0;
	}
	CPoint3 (double c1, double c2, double c3, bool bvisible, unsigned long f)
	{
		x = double(c1);
		y = double(c2);
		z = double(c3);
		bVisible = bvisible;
		flag = f;
	}
	//====== Операция присвоения
	CPoint3& operator=(const CPoint3& pt)
	{
		if (this == &pt)
			return *this;

		x = pt.x;
		z = pt.z;
		y = pt.y;
		bVisible = pt.bVisible;
		flag = pt.flag;
		return *this;
	}

	bool operator==(const CPoint3& pt)
	{
		return( x == pt.x && y == pt.y && z == pt.z);
	}
	bool operator!=(const CPoint3& pt)
	{
		return( x != pt.x || y != pt.y || z != pt.z);
	}
	void Convert(short zflag)
	{
		double temp;
		switch (zflag)
		{
		case 1:
			{
				temp = z,
				z = x,
				x = temp;
			}
			break;
		case 2:
			{
				temp = z,
				z = y,
				y = temp;
			}
			break;
		}
	}
	CPoint3 ConvertTo(short zflag)
	{
		CPoint3 pt;
		pt.bVisible = bVisible;
		pt.flag = flag;
		switch (zflag)
		{
		case 1:
			{
				pt.x = z;
				pt.y = y;
				pt.z = x;
			}
			break;
		case 2:
			{
				pt.x = x;
				pt.y = z;
				pt.z = y;
			}
			break;
		default:
			{
				pt.x = x;
				pt.y = y;
				pt.z = z;
			}
			break;
		}
		return pt;
	}
	
	//====== Операция сдвига в пространстве
	CPoint3& operator+=(const CPoint3& pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		return *this;
	}
	//====== Конструктор копирования
	CPoint3 (const CPoint3& pt)
	{
		*this = pt;
	}	
	CPoint3 operator+(const CPoint3 & p2)
	{
		CPoint3 p3;
		p3.x = x + p2.x;
		p3.y = y + p2.y;
		p3.z = z + p2.z;
		p3.bVisible = bVisible && p2.bVisible;
		p3.flag = 0;
		return p3;
	}
	CPoint3 operator-(const CPoint3 & p2)
	{
		CPoint3 p3;
		p3.x = x - p2.x;
		p3.y = y - p2.y;
		p3.z = z - p2.z;
		p3.bVisible = bVisible && p2.bVisible;
		p3.flag = 0;
		return p3;
	}
	void InitAsVectorProduct(CPoint3 & a, CPoint3 & b)
	{
		//Если два вектора  и  определены своими прямоугольными декартовыми координатами, 
		//а говоря точнее — представлены в ортонормированном базисе
		//а система координат правая, то их векторное произведение имеет вид
		x = a.y * b.z - a.z * b.y;
		y = a.z * b.x - a.x * b.z;
		z = a.x * b.y - a.y * b.x;
	}
};
#pragma optimize( "dagtp", on )
class CPoint2	
{
public:
	double x, y;	// Координаты точки
	bool bVisible;
	//====== Конструктор по умолчанию
	CPoint2 () { x = y = 0; bVisible = true;}
	//====== Конструктор с параметрами
	CPoint2 (double c1, double c2)
	{
		x = double(c1);
		y = double(c2);
		bVisible = true;
	}
	CPoint2 (double c1, double c2, bool bvisible)
	{
		x = double(c1);
		y = double(c2);
		bVisible = bvisible;
	}
	//====== Операция присвоения
	CPoint2& operator=(const CPoint2& pt)
	{
		if (this == &pt)
			return *this;

		x = pt.x;
		y = pt.y;
		bVisible = pt.bVisible;
		return *this;
	}
	bool operator==(const CPoint2& pt)
	{
		return( x == pt.x && y == pt.y);
	}
	bool operator!=(const CPoint2& pt)
	{
		return( x != pt.x || y != pt.y);
	}	
	//====== Операция сдвига в пространстве
	CPoint2& operator+=(const CPoint2& pt)
	{
		x += pt.x;
		y += pt.y;
		return *this;
	}
	//====== Конструктор копирования
	CPoint2 (const CPoint2& pt)
	{
		*this = pt;
	}
};

#else // float precision
class CPoint4	
{
public:
	float x, y, z, v;	// Координаты точки
	bool bVisible;
	//====== Конструктор по умолчанию
	CPoint4 () { x = y = z = v = 0; bVisible = true;}
	//====== Конструктор с параметрами
	CPoint4 (float c1, float c2, float c3, float c4)
	{
		x = float(c1);
		y = float(c2);
		z = float(c3);
		v = float(c4);
		bVisible = true;
	}
	CPoint4 (float c1, float c2, float c3, float c4, bool bvisible)
	{
		x = float(c1);
		y = float(c2);
		z = float(c3);
		v = float(c4);
		bVisible = bvisible;
	}
	//====== Операция присвоения
	CPoint4& operator=(const CPoint4& pt)
	{
		if (this == &pt)
			return *this;

		x = pt.x;
		y = pt.y;
		z = pt.z;
		v = pt.v;
		bVisible = pt.bVisible;
		return *this;
	}
	bool operator==(const CPoint4& pt)
	{
		return( x == pt.x && y == pt.y && z == pt.z && v == pt.v);
	}
	bool operator!=(const CPoint4& pt)
	{
		return( x != pt.x || y != pt.y || z != pt.z || v != pt.v);
	}
	//====== Операция сдвига в пространстве
	CPoint4& operator+=(const CPoint4& pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		return *this;
	}
	//====== Конструктор копирования
	CPoint4 (const CPoint4& pt)
	{
		*this = pt;
	}
};
//====== Точка 3D-пространства
class CPoint3	
{
public:
	float x, y, z;	// Координаты точки
	bool bVisible;
	//====== Конструктор по умолчанию
	CPoint3 () { x = y = z = 0; bVisible = true;}
	//====== Конструктор с параметрами
	CPoint3 (float c1, float c2, float c3)
	{
		x = float(c1);
		y = float(c2);
		z = float(c3);
		bVisible = true;
	}

	CPoint3 (float c1, float c2, float c3, bool bvisible)
	{
		x = float(c1);
		y = float(c2);
		z = float(c3);
		bVisible = bvisible;
	}

	//====== Операция присвоения
	CPoint3& operator=(const CPoint3& pt)
	{
		if (this == &pt)
			return *this;

		x = pt.x;
		z = pt.z;
		y = pt.y;
		bVisible = pt.bVisible;
		return *this;
	}
	bool operator==(const CPoint3& pt)
	{
		return( x == pt.x && y == pt.y && z == pt.z);
	}
	bool operator!=(const CPoint3& pt)
	{
		return( x != pt.x || y != pt.y || z != pt.z);
	}
	//====== Операция сдвига в пространстве
	CPoint3& operator+=(const CPoint3& pt)
	{
		x += pt.x;
		y += pt.y;
		z += pt.z;
		return *this;
	}	

	//====== Конструктор копирования
	CPoint3 (const CPoint3& pt)
	{
		*this = pt;
	}
};
class CPoint2	
{
public:
	float x, y;	// Координаты точки
	bool bVisible;
	//====== Конструктор по умолчанию
	CPoint2 () { x = y = 0; bVisible = true;}
	//====== Конструктор с параметрами
	CPoint2 (float c1, float c2)
	{
		x = float(c1);
		y = float(c2);
		bVisible = true;
	}
	CPoint2 (float c1, float c2, bool bvisible)
	{
		x = float(c1);
		y = float(c2);
		bVisible = bvisible;
	}
	//====== Операция присвоения
	CPoint2& operator=(const CPoint2& pt)
	{
		if (this == &pt)
			return *this;

		x = pt.x;
		y = pt.y;
		bVisible = pt.bVisible;
		return *this;
	}
	bool operator==(const CPoint2& pt)
	{
		return( x == pt.x && y == pt.y);
	}
	bool operator!=(const CPoint2& pt)
	{
		return( x != pt.x || y != pt.y);
	}	
	//====== Операция сдвига в пространстве
	CPoint2& operator+=(const CPoint2& pt)
	{
		x += pt.x;
		y += pt.y;
		return *this;
	}
	//====== Конструктор копирования
	CPoint2 (const CPoint2& pt)
	{
		*this = pt;
	}
};
struct ProfileAttachPoint	// точка привязки профиля к карте
							// массив таких точек привязки 
							// необходим для функции перевода
							// горизонтальной координаты профиля xPrifile
							// в координаты карты xMap yMap
{
	float 
		xMap, 
		yMap, 
		xPrifile;
	bool 
		bAttached;		// флаг привязки горизонтальной координаты профиля
};
#endif /*OG_DOUBLE_PRECISION*/

struct TWO
{
	//====== Индексы 2-х вершин line,
	unsigned int i1;
	unsigned int i2;
};
struct TRIA
{
	//====== Индексы трех вершин треугольника,
	//====== выбираемых из массива вершин типа VERT
	//====== Порядок обхода - против часовой стрелки
	unsigned int i1;
	unsigned int i2;
	unsigned int i3;
};



//====== Данные о вершине геометрического примитива
struct VERT
{
	CPoint3 v;	// Координаты вершины
	CPoint3 n;	// Координаты нормали
	unsigned long c;		// Цвет вершины
};

//====== Данные о вершине геометрического примитива
struct VERT_TEX
{
	CPoint3 v;	// Координаты вершины
	CPoint3 n;	// Координаты нормали
	unsigned long c;		// Цвет вершины
	CPoint2 t;	// Координаты текстуры
};

struct Triangle3
{
	CPoint3 v1;	// Координаты вершины 1
	CPoint3 v2;	// Координаты вершины 1
	CPoint3 v3;	// Координаты вершины 1
};

struct QUAD
{
	//====== Индексы трех вершин 4-угольника,
	//====== выбираемых из массива вершин типа VERT
	//====== Порядок обхода - против часовой стрелки
	unsigned int i1;
	unsigned int i2;
	unsigned int i3;
	unsigned int i4;
};


#endif
