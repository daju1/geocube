// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graphs.h"
#include "Graph.h"

//===== ���� ����, ���������� ��������
#define SCALE_X 0.75
#define SCALE_Y 0.22/6
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//======= ����������� ������ CGraph
CGraph::CGraph (Vector<CpVDPoints>& pt, 
				CString sTitle,
				CString sX, CString sY,
				int yshift, 
				CSize sizeTotal): m_vpPoints(pt)
{
	m_SizeTotal = sizeTotal;
	m_yshift = yshift;
	// ����� ��������
	//======= ������� ������, ��������������� ��� ���������	ZeroMemory(&m_DataX, sizeof(TData));
	ZeroMemory(&m_DataY, sizeof(TData));
	m_DataX.bX = true;
	m_DataY.bX = false;
	m_sTitle = sTitle;
	m_sX = sX;
	m_sY = sY;

	//======= ������� ����� ��� ��������� ����
	m_Font.CreateFont(12,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= ������� ����� ��� ��������� ����
	m_PrintFont.CreateFont(36,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= �������� ������������ ������ �����
	TEXTMETRIC tm;
	CClientDC dc(0);
	dc.SelectObject(&m_Font);
	dc.GetTextMetrics(&tm); 
	m_LH = tm.tmHeight;

	//======= ������� ����� ��� ������ ���������
	m_TitleFont.CreateFont(16,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	//======= ������� ����� ��� ������ ���������
	m_PrintTitleFont.CreateFont(150,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	int nGraphs = 10;
	m_vClr.resize(nGraphs);
	//======= ������ ��������� ����
	for (int n = 0; n < nGraphs; n++)
	{
		switch(n)
		{
		case 0:	m_vClr[n] = RGB(100,100,0);break;//Open
		case 1:	m_vClr[n] = RGB(255,0,0);break;//High
		case 2:	m_vClr[n] = RGB(0,0,255);break;//Low
		case 3:	m_vClr[n] = RGB(0,255,0);break;//Close
		case 4:	m_vClr[n] = RGB(255,0,0);break;
		case 5:	m_vClr[n] = RGB(255,0,0);break;
		case 6:	m_vClr[n] = RGB(100,100,0);break;
		case 7:	m_vClr[n] = RGB(100,100,0);break;
		case 8:	m_vClr[n] = RGB(0,0,0);break;
		case 9:	m_vClr[n] = RGB(0,0,0);break;
		default:m_vClr[n] = RGB(0,0,0);break;
		}
	}
	m_vWidth.resize(nGraphs);
	for ( n = 0; n < nGraphs; n++)
	{
		switch(n)
		{
		case 0:	m_vWidth[n] = 1;break;
		case 1:	m_vWidth[n] = 1;break;
		case 2:	m_vWidth[n] = 1;break;
		case 3:	m_vWidth[n] = 1;break;
		case 4:	m_vWidth[n] = 1;break;
		case 5:	m_vWidth[n] = 1;break;
		case 6:	m_vWidth[n] = 1;break;
		case 7:	m_vWidth[n] = 1;break;
		case 8:	m_vWidth[n] = 1;break;
		case 9:	m_vWidth[n] = 1;break;
		default:m_vWidth[n] = 1;break;
		}
	}
}

//======= ���������� 
CGraph::~CGraph(){}

//===== ������� ������� ���������� ������� ����� �����
void gScale (double span, double& step)
{
	//===== ���������� span ���������� �������� ���������
	//===== �������� ����� �� ��������� ����� �������
	//===== ��������� ������� �����, ������������ ��������
	int power = int(floor(log10(span)));
	//===== ��������� (zoom factor)
	double factor = pow(10, power);
	//===== �������� ��������� (������ 1 < span < 10)
	span /= factor;

	//===== �������� ����������� ��� �����
	if (span<1.99)
		step=.2;
	else if (span<2.49)
		step=.25;
	else if (span<4.99)
		step=.5;
	else if (span<10.)
		step= 1.;

	//===== ���������� �������� ��� ����� (step*10^power)
	step *= factor; 
}

void CGraph::Scale (TData& data)
{
	//===== � ������ ������������������� �� ��������
//	if (m_vPoints.empty())
//		return;
		//===== ��������� ������ ����������
	
	double Max,
		Min;
	int i = 0;
	bool findfirst = true;
	do
	{
		if (m_vpPoints[i].toDraw && m_vpPoints[i].px->Length() > 0 && m_vpPoints[i].py->Length() > 0)
		{
			data.Max = data.bX ? m_vpPoints[i].px->Max() : m_vpPoints[i].py->Max();
			data.Min = data.bX ? m_vpPoints[i].px->Min() : m_vpPoints[i].py->Min();
			findfirst = false;
		}
		i++;
	}
	while (i < m_vpPoints.Size() && findfirst);

	for(int n = i; n < m_vpPoints.Size(); n++)
	{
		if (m_vpPoints[n].toDraw && m_vpPoints[n].px->Length() > 0 && m_vpPoints[n].py->Length() > 0)
		{
			Max = data.bX ? m_vpPoints[n].px->Max() : m_vpPoints[n].py->Max();
			Min = data.bX ? m_vpPoints[n].px->Min() : m_vpPoints[n].py->Min();
			data.Max = data.Max > Max ? data.Max : Max;
			data.Min = data.Min < Min ? data.Min : Min;
		}
	}

	//====== ������� ���������� �������	

	//===== ������������ ��������� ���� ����������� 
	double ext = max(fabs(data.Min),fabs(data.Max));

	//===== ������������ ����������� ������� ����������
	//===== �� 3 �������, ��� ��� �� ����� ������� 7 ��������,
	//===== �� �������� � ���������������� ����� ����� 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	data.Power = int(floor(power/7.));

	//===== ���� ����� �� ������������ � ���� ��������
	if (data.Power != 0)
		//===== �� �� ��������������� �������� �������
		data.Power = int(floor(power)) - 3;
	//===== �������� ���������
	data.Factor = pow(10,data.Power);	

	//===== �������� ��������� ��������
	double span = (data.Max - data.Min)/data.Factor;
	//===== ���� �� �������,
	if (fabs(span) < 0.001)
		span = 0.5; // �� ������������ ���������� ������

	//===== ��������� ����������� ��� ��� ������������ �����
	gScale (span, data.Step);

	//===== ��� � ������ ������������� ��������������
	data.dStep = data.Step * data.Factor;

	//===== ��������� ����� ����� ������ ���� ������ ����
	//===== � ���� ������ ��������
	data.dStart = data.dStep * int(floor(data.Min/data.dStep));
	data.Start = data.dStart/data.Factor;

	//===== ��������� ��������� ����� �����
	for (data.End = data.Start;
		data.End < data.Min/data.Factor + span-1e-10;  
		data.End += data.Step)
		;
	data.dEnd = data.End*data.Factor;
}

int CGraph::MapToLogX (double d)
{
	return m_Center.x + int (SCALE_X * m_Size.cx * d);
}

int CGraph::MapToLogY (double d)
{
	return m_Center.y - int (SCALE_Y * m_SizeTotal.cy * d) + m_yshift;
}
int CGraph::MapToLogYPrint (double d)
{
	return m_Center.y - int (SCALE_Y * m_Size.cy * d) + m_yshift * m_Size.cy / m_SizeTotal.cy;
}

void CGraph::Draw (CDC *pDC, TData& DataX, TData& DataY, bool toScaleX, bool toScaleY)
{
	for (int n = 0; n < m_vpPoints.Size(); n++)
	{
		if (m_vpPoints [n].toDraw)
		{
			if (m_vpPoints [n].px -> m_length != m_vpPoints [n].py -> m_length)
			{
				CString errstr;
				errstr.Format(" Number of line = %i\n px -> m_length (%i) != py -> m_length (%i)\n",
					n, m_vpPoints [n].px -> m_length, m_vpPoints [n].py -> m_length);
				AfxMessageBox("Error using CGraph::Draw()\n" + errstr);
				return;
				// AfxThrowUserException();
			}
		}
	}
	//====== � ������� ��������� ����������
	//====== ������ ����� ����, ��� �������������
	CRect r;
	
	bool isPrint = pDC->IsPrinting() != 0;
	if(!isPrint)
	{
		CWnd *pWnd = pDC->GetWindow();
		pWnd->GetClientRect(&r);
	}
	else
	{
		r.left = 20;
		r.top = 20;
		r.right = r.left + pDC->GetDeviceCaps(HORZRES);
		r.bottom = r.top + pDC->GetDeviceCaps(VERTRES);
	}

	//====== �������� ������� ����
	m_Size = r.Size();
	if(!isPrint)
	{
		m_Center = CPoint(m_Size.cx/2, m_SizeTotal.cy/2);
	}
	else
	{
		m_Center = CPoint(m_Size.cx/2, m_Size.cy/2);
	}
	int nDC = pDC->SaveDC();
	
	//====== ������� ������ ���� ��� ����������� �����
	CPen pen(PS_SOLID, 0, COLORREF(0));
	pDC->SelectObject(&pen);

	//====== ����������� ���������� �����
	int lt = MapToLogX(-0.5),
		rt = MapToLogX(0.5),
		tp = isPrint ? MapToLogYPrint(0.5) : MapToLogY(0.5),
		bm = isPrint ? MapToLogYPrint(-0.5) : MapToLogY(-0.5);

	pDC->Rectangle (lt, tp, rt, bm);

	//====== ������ ���� � ������������ ������
	pDC->SetTextColor(0);
	pDC->SetTextAlign(TA_LEFT | TA_BASELINE);
	
	//====== �������� �����
	if(!isPrint)
		pDC->SelectObject (&m_Font);
	else
		pDC->SelectObject (&m_PrintFont);

	if (toScaleX)
	{
		// �������� ������������ ���� ���������� ������� � ����������� �������
		m_DataX = DataX;
	}
	else
	{
		//====== ��������� �������� ������������ ����
		Scale(m_DataX);
		DataX = m_DataX;
	}
	if (toScaleY)
	{
		// �������� ������������ ���� ���������� ������� � ����������� �������
		m_DataY = DataY;
	}
	else
	{
		//====== ��������� �������� ������������ ����
		Scale(m_DataY);
		DataY = m_DataY;
	}

	//====== ������� ���������� �������	
	CString s;
	s.Format("Min = %.3g",m_DataY.Min);
	pDC->TextOut(rt+m_LH, tp+m_LH, s);

	s.Format("Max = %.3g",m_DataY.Max);
	pDC->TextOut(rt+m_LH, tp+m_LH+m_LH, s);
		
	//====== ��������� ���������� ������������ �����
	CPen gridPen(PS_SOLID, 0, RGB(92,200,178));
	pDC->SelectObject(&gridPen);
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	
	//====== ������ ������������ ����� �����
	for (double x = m_DataX.Start;  
			x < m_DataX.End - m_DataX.Step/2.;
			x += m_DataX.Step)
	{
		//====== ��������� ���������� x
		double	xn = (x - m_DataX.Start) /
						(m_DataX.End - m_DataX.Start) - 0.5;

		//====== ��������� ������� ����������
		int xi = MapToLogX(xn);	
		//====== ���������� ������� �����,
		//====== ��� ��� ��� ��������� � ������
		if (x > m_DataX.Start && x < m_DataX.End)
		{
			pDC->MoveTo(xi, bm);
			pDC->LineTo(xi, tp);
		}
		//====== ������� �������� �����
		pDC->TextOut(xi, bm+m_LH, MakeLabel(true, x));
	}

	//===== ��������� ���� ��� �������������� ����� �����
	pDC->SetTextAlign(TA_RIGHT | TA_BASELINE);
	for (double y = m_DataY.Start;
			y < m_DataY.End - m_DataY.Step/2.;
			y += m_DataY.Step)
	{
		double yn = (y - m_DataY.Start) /
						(m_DataY.End - m_DataY.Start) - 0.5;

		int yi = isPrint ? MapToLogYPrint(yn) : MapToLogY(yn) ;
		if (y > m_DataY.Start && y < m_DataY.End)
		{
			pDC->MoveTo(lt, yi);
			pDC->LineTo(rt, yi);
			pDC->TextOut(lt-m_LH/2, yi, MakeLabel(false, y));
		}
	}

	//====== ����� ����� ����
	pDC->TextOut(lt-m_LH/2, tp - m_LH, m_sY);
	pDC->SetTextAlign(TA_LEFT | TA_BASELINE);
	pDC->TextOut(rt-m_LH, bm + m_LH, m_sX);

	//====== ����� ���������
	if (m_sTitle.GetLength() > 40)
		m_sTitle.Left(40);


	//====== �������� �����
	if(!isPrint)
		pDC->SelectObject(&m_TitleFont);
	else
		pDC->SelectObject(&m_PrintTitleFont);
	pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
	pDC->TextOut((lt+rt)/2, tp - m_LH, m_sTitle);
	
	//====== ����� ����� �������
	DrawLine(pDC, isPrint);
	//====== ��������������� ����������� GDI
	pDC->RestoreDC(nDC);
}



void CGraph::DrawLine(CDC *pDC, bool isPrint)
{
	for(int n = 0; n <  m_vpPoints.Size(); n++)
	{
		if (m_vpPoints[n].toDraw)
		{
			//====== ���������� ������ ����
			if (m_Pen.m_hObject)
				m_Pen.DeleteObject();
			//====== ������� �����
			m_Pen.CreatePen(PS_SOLID, m_vWidth[n], m_vClr[n]);

			pDC->SelectObject(&m_Pen);

			double	x0 = m_DataX.dStart,
					y0 = m_DataY.dStart,
					dx = m_DataX.dEnd - x0,
					dy = m_DataY.dEnd - y0;

			for (int i=0;  i < m_vpPoints[n].px->Length();  i++)
			{
				//====== ��������� ����������
				double	x = (m_vpPoints[n].px->operator[](i) - x0) / dx - .5,
						y = (m_vpPoints[n].py->operator[](i) - y0) / dy - .5;


				//====== ������� � ������� �����������
				CPoint pt (MapToLogX(x),isPrint ? MapToLogYPrint(y) : MapToLogY(y));
				//====== ���� ����� ������, �� ������ ����
				if (i==0)
					pDC->MoveTo(pt);
				else
					pDC->LineTo(pt);
			}
		}
	}
}



CString CGraph::MakeLabel(bool bX, double& v)
{
	CString s = "0.0";
	if (v == 0.)
		return s;

	//====== ������� ������ ������ ��������
	//====== ������� ����������� � 20 �������
	s.Format("%20.10f",v);
	//====== �������� ������� ���� �����,
	//====== ������������� ��� ���� (����)
	int nDigits = int(ceil(-log10(bX ? m_DataX.Step
									: m_DataY.Step)));
	//====== ���� ��� ��������� ���������� �� �������,
	//====== �� ����� ����� ������� ��� �� ����������
	if (nDigits <= 0)
		nDigits = -1;
	else
		if (bX)
			nDigits++;	// ������������ �������

	//====== ����� ������� ���
	s.TrimLeft();

	//====== ������ ��������� ������� ��������
	s = s.Left(s.Find(".") + nDigits + 1);

	int iPower = bX ? m_DataX.Power : m_DataY.Power;
	//====== ����� �� �������?
	if (iPower != 0)
	{
		//====== �����, ���� �� ����������� � (10^-3, 10^+4)
		CString add;
		add.Format("�e%+d",iPower);
		s += add;
	}
	return s;
}
