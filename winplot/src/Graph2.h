// Graph2.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH2_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
#define AFX_GRAPH2_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"
#include "..\..\tezey\src\Graph.h"

/*
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
*/
	//===== �����, ����������� ������� �������� �������
class CGraph2
{
public:
	void AddPointValue(int iVect, double &x, double &y);
	void clear();
	void InitAxes();
	void InitLabels(LPSTR sTitle, LPSTR sX, LPSTR sY);
	void InitPens();
	void InitFonts();
	//===== ������, ��������������� ������ ����� ����
	TData m_DataX, m_DataY;
	//===== ��������� ����� �������
	vect <CDPoint> m_vPoints;
	vect <bool> m_vbYScale;
	//===== ������� ������� ���� �������
	tagSIZE m_Size;
	//===== �������� ���������� ������ ����
	tagPOINT m_Center;
	//===== ��������� � ������������ ����
	char m_sTitle[255], m_sX[255], m_sY[255];
	//===== ���� ��� ���������
	HPEN m_Pen;
	//===== ��� ���� �������
	HFONT m_TitleFont, m_Font, m_font, m_YLabelFont;
	//===== ������ ����� (������� �� ������)
	int		m_LH,
	//===== ������� ����
			m_Width;
	//===== ���� ����
	COLORREF m_Clr;
	//======= ������ ��� ���������� ��������
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
	//===== ���������� TData ��� ����� �� ����
	void Scale(UINT flag);
	void Scale(TData& data);
	void Scale(TData& data, UINT flag);
	void Scale(TData& data, double fmin, double fmax, double fstep);
	void GetScale(double &fXmin, double &fXmax, double &fXstep, double &fYmin, double &fYmax, double &fYstep);
	void SetScale(double fXmin, double fXmax, double fXstep, double fYmin, double fYmax, double fYstep);
	//===== ������� � ���������� ����������� �����
	int MapToLogX (double d);
	int MapToLogY (double d);
	//===== ����������� � �������� ���������
	void Draw (HDC hDC,	tagRECT r, UINT flag);
	bool m_bLineWrite;
	//===== ����������� ����� �����
	void DrawLine(HDC hDC, UINT flag, bool useDiffColors = false);
	void DrawPoints(HDC hDC, UINT flag, bool useDiffColors = false);
	//===== ���������� �������� ����� �� ���
	void MakeLabel(bool bX, double& v, char* s);
};

#endif // !defined(AFX_GRAPH2_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
