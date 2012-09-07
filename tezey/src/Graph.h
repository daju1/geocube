// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__39EAEE55_E610_4C2D_B28F_5342174CFE92__INCLUDED_)
#define AFX_GRAPH_H__39EAEE55_E610_4C2D_B28F_5342174CFE92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DPoint.h"
#include "..\..\array\src\vect.h"
#include "..\..\array\src\Vector.h"

struct TData
{
	//===== Порядок в нормализованном представлении числа
	int Power;
	//===== Флаг оси X
	bool bX;
	double
		//======= Экстремумы
		Min, Max,
		//======= Множитель (10 в степени Power)
		Factor,
		//======= Шаг вдоль оси (мантисса)
		Step,
		//======= Реальный шаг
		dStep,
		//======= Первая и последняя координаты (мантиссы)
		Start, End,
		//======= Первая и последняя координаты
		dStart, dEnd;
};
/*struct cPoint
{
    int  x;
    int  y;
};
struct cSize
{
    int        cx;
    int        cy;
};
struct cRect
{
    int    left;
    int    top;
    int    right;
    int    bottom;
};
*/
	//===== Класс, реализующий функции плоского графика
class CGraph
{
public:
	void MakeTimeLabel(double& t, char * s);
	int m_iLast;
	int m_iFirst;
	double m_SCALE_Y;
	double m_SCALE_X;
	tagSIZE m_SizeTotal;
	double m_yshift;
	//===== Данные, характеризующие данные вдоль осей
	TData m_DataX, m_DataY;
	//===== Контейнеры точек графика
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	vect<CpVDPoints> & m_vPoints;
#else
	Vector<CpVDPoints> & m_vpPoints;
#endif
	//===== Текущие размеры окна графика
	tagSIZE m_Size;
	//===== Экранные координаты центра окна
	tagPOINT m_Center;
	//===== Заголовок и наименования осей
//	char m_sTitle[100], m_sX[100], m_sY[100];
#ifndef EXTERN_FONTS_AND_PENS
	//===== Перо для рисования
	//HPEN boxPen, gridPen, linePen;
	//===== Два типа шрифтов
	//HFONT hTitleFont, hFont;
	//HFONT hPrintTitleFont, hPrintFont;
#endif
	//===== Высота буквы (зависит от шрифта)
	int		m_LH;
	//===== Толщина пера
	Vector<int>	m_vWidth;
	//===== Цвет пера
	Vector<COLORREF> m_vClr;
	//======= Методы для управления графиком
	CGraph(
#ifndef DRAW_OLD_VECTOR_VDPOINTS
		vect<CpVDPoints>& pt, 
#else
		Vector<CpVDPoints>& pt, 
#endif
//		LPSTR sTitle,LPSTR sX, LPSTR sY, 
				double yshift,  double scale_y,
				tagSIZE sizeTotal);
//		CGraph(Vector<CpVDPoints> & pt, CString sTitle,
//					CString sX, CString sY, int yshift, CSize sizeTotal);
	virtual ~CGraph();
	//===== Заполнение TData для любой из осей
	void Scale(TData& data, int iFirst = 0, int iLast = 0, bool useTDataMinMaxX = false);
	//===== Переход к логическим координатам точек
	int MapToLogX (double d);
	int MapToLogY (double d);
	int MapToLogYPrint (double d);
	//===== Изображение в заданном контексте
	void Draw ( HDC hDC, TData& DataX, TData& DataY, RECT& r, int iFirst, int iLast, 
#ifdef EXTERN_FONTS_AND_PENS
		HPEN& boxPen, HPEN& gridPen, HPEN& linePen, HFONT& hFont, HFONT& hTitleFont, HFONT& hPrintFont, HFONT& hTitlePrintFont, 
#endif
		short toScaleX = 0, bool toScaleY = false, bool isVisible = true);
	//===== Изображение одной линии
	void DrawLine(HDC hDC, int iFirst, int iLast, HPEN& linePen, bool isPrint);
	//===== Подготовка цифровой метки на оси
	void MakeLabel(bool bX, double& v, char* s);
};

#endif // !defined(AFX_GRAPH_H__39EAEE55_E610_4C2D_B28F_5342174CFE92__INCLUDED_)
