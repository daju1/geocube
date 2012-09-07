// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
#define AFX_GRAPH_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

	//===== �����, ����������� ������� �������� �������
class CGraph
{
public:
	CSize m_SizeTotal;
	int m_yshift;
	//===== ������, ��������������� ������ ����� ����
	TData m_DataX, m_DataY;
	//===== ���������� ����� �������
	Vector<CpVDPoints> & m_vpPoints;
	//===== ������� ������� ���� �������
	CSize m_Size;
	//===== �������� ���������� ������ ����
	CPoint m_Center;
	//===== ��������� � ������������ ����
	CString m_sTitle, m_sX, m_sY;
	//===== ���� ��� ���������
	CPen m_Pen;
	//===== ��� ���� �������
	CFont m_TitleFont, m_Font;
	CFont m_PrintTitleFont, m_PrintFont;
	//===== ������ ����� (������� �� ������)
	int		m_LH;
	//===== ������� ����
	Vector<int>	m_vWidth;
	//===== ���� ����
	Vector<COLORREF> m_vClr;
	//======= ������ ��� ���������� ��������
//	CGraph(){}
	CGraph(Vector<CpVDPoints> & pt, CString sTitle,
					CString sX, CString sY, int yshift, CSize sizeTotal);
	virtual ~CGraph();
	//===== ���������� TData ��� ����� �� ����
	void Scale(TData& data);
	//===== ������� � ���������� ����������� �����
	int MapToLogX (double d);
	int MapToLogY (double d);
	int MapToLogYPrint (double d);
	//===== ����������� � �������� ���������
	void Draw (CDC *pDC, TData& DataX, TData& DataY, bool toScaleX = false, bool toScaleY = false);
	//===== ����������� ����� �����
	void DrawLine(CDC *pDC, bool isPrint);
	//===== ���������� �������� ����� �� ���
	CString MakeLabel(bool bX, double& d);
};

#endif // !defined(AFX_GRAPH_H__7D09E6C6_48C5_4678_9151_FCF46A1B2C47__INCLUDED_)
