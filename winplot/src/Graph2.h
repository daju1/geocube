// Graph2.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH2_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
#define AFX_GRAPH2_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifdef _MSC_VER
#include "StdAfx.h"
#endif
#include "../../tezey/src/Graph.h"

/*
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
*/
	//===== Класс, реализующий функции плоского графика
class CGraph2
{
public:
	void AddPointValue(int iVect, double &x, double &y);
	void clear();
	void InitAxes();
	void InitLabels(LPSTR sTitle, LPSTR sX, LPSTR sY);
	void InitPens();
	void InitFonts();
	//===== Данные, характеризующие данные вдоль осей
	TData m_DataX, m_DataY;
	//===== Контейнер точек графика
	vect <CDPoint> m_vPoints;
	vect <bool> m_vbYScale;
	//===== Текущие размеры окна графика
	tagSIZE m_Size;
	//===== Экранные координаты центра окна
	tagPOINT m_Center;
	//===== Заголовок и наименования осей
	char m_sTitle[255], m_sX[255], m_sY[255];
	//===== Перо для рисования
	HPEN m_Pen;
	//===== Два типа шрифтов
	HFONT m_TitleFont, m_Font, m_font, m_YLabelFont;
	//===== Высота буквы (зависит от шрифта)
	int		m_LH,
	//===== Толщина пера
			m_Width;
	//===== Цвет пера
	COLORREF m_Clr;
	//======= Методы для управления графиком
	CGraph2();
	CGraph2(vdouble& x, vdouble& y, LPSTR sTitle = NULL, LPSTR sX = NULL, LPSTR sY = NULL);
	CGraph2(Vector<vdouble> &vx, Vector<vdouble> &vy, LPSTR sTitle = NULL, LPSTR sX = NULL, LPSTR sY = NULL);
	CGraph2 (vector<vector<double> > &vx, vector<vector<double> > &vy, LPSTR sTitle = NULL, LPSTR sX = NULL, LPSTR sY = NULL);
	CGraph2 (vector<double> &x, vector<double> &y, LPSTR sTitle = NULL, LPSTR sX = NULL, LPSTR sY = NULL);
	CGraph2 (vector<double> &x, vector<double> &y, size_t i1, size_t i2, LPSTR sTitle = NULL, LPSTR sX = NULL, LPSTR sY = NULL);
	CGraph2(vect<CDPoint>& pt, 
				LPSTR sTitle, LPSTR sX, LPSTR sY
					);
	virtual ~CGraph2();
	//===== Заполнение TData для любой из осей
	void Scale(UINT flag);
	void Scale(TData& data);
	void Scale(TData& data, UINT flag);
	void Scale(TData& data, double fmin, double fmax, double fstep);
	void GetScale(double &fXmin, double &fXmax, double &fXstep, double &fYmin, double &fYmax, double &fYstep);
	void SetScale(double fXmin, double fXmax, double fXstep, double fYmin, double fYmax, double fYstep);
	//===== Переход к логическим координатам точек
	int MapToLogX (double d);
	int MapToLogY (double d);
	//===== Изображение в заданном контексте
	void Draw (HDC hDC,	tagRECT r, UINT flag);
	bool m_bLineWrite;
	//===== Изображение одной линии
	void DrawLine(HDC hDC, UINT flag, bool useDiffColors = false);
	void DrawPoints(HDC hDC, UINT flag, bool useDiffColors = false);
	//===== Подготовка цифровой метки на оси
	void MakeLabel(bool bX, double& v, char* s, size_t len);
};

#endif // !defined(AFX_GRAPH2_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
