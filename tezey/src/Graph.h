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
	//===== ������� � ��������������� ������������� �����
	int Power;
	//===== ���� ��� X
	bool bX;
	double
		//======= ����������
		Min, Max,
		//======= ��������� (10 � ������� Power)
		Factor,
		//======= ��� ����� ��� (��������)
		Step,
		//======= �������� ���
		dStep,
		//======= ������ � ��������� ���������� (��������)
		Start, End,
		//======= ������ � ��������� ����������
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
	//===== �����, ����������� ������� �������� �������
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
	//===== ������, ��������������� ������ ����� ����
	TData m_DataX, m_DataY;
	//===== ���������� ����� �������
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	vect<CpVDPoints> & m_vPoints;
#else
	Vector<CpVDPoints> & m_vpPoints;
#endif
	//===== ������� ������� ���� �������
	tagSIZE m_Size;
	//===== �������� ���������� ������ ����
	tagPOINT m_Center;
	//===== ��������� � ������������ ����
//	char m_sTitle[100], m_sX[100], m_sY[100];
#ifndef EXTERN_FONTS_AND_PENS
	//===== ���� ��� ���������
	//HPEN boxPen, gridPen, linePen;
	//===== ��� ���� �������
	//HFONT hTitleFont, hFont;
	//HFONT hPrintTitleFont, hPrintFont;
#endif
	//===== ������ ����� (������� �� ������)
	int		m_LH;
	//===== ������� ����
	Vector<int>	m_vWidth;
	//===== ���� ����
	Vector<COLORREF> m_vClr;
	//======= ������ ��� ���������� ��������
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
	//===== ���������� TData ��� ����� �� ����
	void Scale(TData& data, int iFirst = 0, int iLast = 0, bool useTDataMinMaxX = false);
	//===== ������� � ���������� ����������� �����
	int MapToLogX (double d);
	int MapToLogY (double d);
	int MapToLogYPrint (double d);
	//===== ����������� � �������� ���������
	void Draw ( HDC hDC, TData& DataX, TData& DataY, RECT& r, int iFirst, int iLast, 
#ifdef EXTERN_FONTS_AND_PENS
		HPEN& boxPen, HPEN& gridPen, HPEN& linePen, HFONT& hFont, HFONT& hTitleFont, HFONT& hPrintFont, HFONT& hTitlePrintFont, 
#endif
		short toScaleX = 0, bool toScaleY = false, bool isVisible = true);
	//===== ����������� ����� �����
	void DrawLine(HDC hDC, int iFirst, int iLast, HPEN& linePen, bool isPrint);
	//===== ���������� �������� ����� �� ���
	void MakeLabel(bool bX, double& v, char* s);
};

#endif // !defined(AFX_GRAPH_H__39EAEE55_E610_4C2D_B28F_5342174CFE92__INCLUDED_)
