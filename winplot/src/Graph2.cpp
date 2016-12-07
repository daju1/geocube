// Graph.cpp: implementation of the CGraph2 class.
//
//////////////////////////////////////////////////////////////////////


#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "Graph2.h"
#include "..\..\array\src\vdouble.h"
//===== Доля окна, занимаемая графиком
#define SCALE_X 0.6
#define SCALE_Y 0.6
#define S_LEN 256
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//======= Конструктор класса CGraph2
CGraph2::CGraph2()
{
}
CGraph2::CGraph2 (vect<CDPoint>& pt, 
				LPSTR sTitle, LPSTR sX, LPSTR sY
					): m_vPoints(pt)
{
	InitAxes();
	InitFonts();
	InitPens();
	InitLabels(sTitle, sX, sY);
}
CGraph2::CGraph2 (vector<vector<double> > &vx, vector<vector<double> > &vy, LPSTR sTitle, LPSTR sX, LPSTR sY)
{
	size_t iv;
	if (vx.size() != vy.size())
	{
		char s[S_LEN];
		sprintf_s(s, S_LEN, "vx.size(%d) != vy.size(%d)", vx.size(), vy.size() );
		MessageBox(0,s, "CGraph2", 0);
		return;
	}

	for (iv = 0; iv < vx.size(); iv++)
	{
		if( vx[iv].size() != vx[iv].size())
		{
			char s[S_LEN];
			sprintf_s(s, S_LEN, "vx[%d].size(%d) != vx[%d].size(%d)", iv, vx[iv].size(), iv, vx[iv].size() );
			MessageBox(0,s, "CGraph2", 0);
			return;
		}
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vbYScale.OnCreate();
	bool byscale = false;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vPoints.OnCreate();
	for (iv = 0; iv < vx.size(); iv++)
	{
		m_vbYScale.AddMsg(&byscale);
		m_vPoints.CreateNewVect();
		CDPoint point;
		for( size_t i = 0; i < vx[iv].size(); i ++)
		{
			point.x = vx[iv][i]; 
			point.y = vy[iv][i];
			m_vPoints.AddMsgToLastVect(&point);
		}
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_bLineWrite = false;

	InitAxes();
	InitFonts();
	InitPens();
	if (sTitle && sX && sY)
		InitLabels(sTitle, sX, sY);
	else
		InitLabels("График", "x", "y");
}
CGraph2::CGraph2 (Vector<vdouble> &vx, Vector<vdouble> &vy, LPSTR sTitle, LPSTR sX, LPSTR sY)
{
	int iv;
	if (vx.Size() != vy.Size())
	{
		char s[S_LEN];
		sprintf_s(s, S_LEN, "vx.Size(%d) != vy.Size(%d)", vx.Size(), vy.Size() );
		MessageBox(0,s, "CGraph2", 0);
		return;
	}

	for (iv = 0; iv < vx.Size(); iv++)
	{
		if( vx[iv].Length() != vx[iv].Length())
		{
			char s[S_LEN];
			sprintf_s(s, S_LEN, "vx[%d].Length(%d) != vx[%d].Length(%d)", iv, vx[iv].Length(), iv, vx[iv].Length() );
			MessageBox(0,s, "CGraph2", 0);
			return;
		}
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vbYScale.OnCreate();
	bool byscale = false;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vPoints.OnCreate();
	for (iv = 0; iv < vx.Size(); iv++)
	{
		m_vbYScale.AddMsg(&byscale);
		m_vPoints.CreateNewVect();
		CDPoint point;
		for( int i = 0; i < vx[iv].Length(); i ++)
		{
			point.x = vx[iv][i]; 
			point.y = vy[iv][i];
			m_vPoints.AddMsgToLastVect(&point);
		}
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_bLineWrite = false;

	InitAxes();
	InitFonts();
	InitPens();
	if (sTitle && sX && sY)
		InitLabels(sTitle, sX, sY);
	else
		InitLabels("График", "x", "y");
}
CGraph2::CGraph2 (vector<double> &x, vector<double> &y, LPSTR sTitle, LPSTR sX, LPSTR sY)
{
	if( x.size() != y.size())
	{
		char s[S_LEN];
		sprintf_s(s, S_LEN, "x.size(%d) != y.size(%d)", x.size(), y.size() );
		MessageBox(0,s, "CGraph2", 0);
		return;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vbYScale.OnCreate();
	bool byscale = false;
	m_vbYScale.AddMsg(&byscale);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vPoints.OnCreate();
	m_vPoints.CreateNewVect();
	CDPoint point;
	for( size_t i = 0; i < x.size(); i ++)
	{
		point.x = x[i]; 
		point.y = y[i];
		m_vPoints.AddMsgToLastVect(&point);
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_bLineWrite = true;

	InitAxes();
	InitFonts();
	InitPens();
	if (sTitle && sX && sY)
		InitLabels(sTitle, sX, sY);
	else
		InitLabels("График", "x", "y");
}

CGraph2::CGraph2 (vector<double> &x, vector<double> &y, size_t i1, size_t i2, LPSTR sTitle, LPSTR sX, LPSTR sY)
{
	if( x.size() != y.size())
	{
		char s[S_LEN];
		sprintf_s(s, S_LEN, "x.size(%d) != y.size(%d)", x.size(), y.size() );
		MessageBox(0,s, "CGraph2", 0);
		return;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vbYScale.OnCreate();
	bool byscale = false;
#if 1
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vPoints.OnCreate();
	{
		m_vbYScale.AddMsg(&byscale);
		m_vPoints.CreateNewVect();
		CDPoint point;
		for( size_t i = i1; i <= i2; i ++)
		{
			point.x = x[i]; 
			point.y = y[i];
			m_vPoints.AddMsgToLastVect(&point);
		}
	}
	{
		m_vbYScale.AddMsg(&byscale);
		m_vPoints.CreateNewVect();
		CDPoint point;
		for( size_t i = 0; i <= i1; i ++)
		{
			point.x = x[i]; 
			point.y = y[i];
			m_vPoints.AddMsgToLastVect(&point);
		}
	}
	{
		m_vbYScale.AddMsg(&byscale);
		m_vPoints.CreateNewVect();
		CDPoint point;
		for( size_t i = i2; i < x.size(); i ++)
		{
			point.x = x[i]; 
			point.y = y[i];
			m_vPoints.AddMsgToLastVect(&point);
		}
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
#else
	m_vbYScale.AddMsg(&byscale);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vPoints.OnCreate();
	m_vPoints.CreateNewVect();
	CDPoint point;
	//for( size_t i = 0; i < x.size(); i ++)
	for( size_t i = i1; i <= i2; i ++)
	{
		point.x = x[i]; 
		point.y = y[i];
		m_vPoints.AddMsgToLastVect(&point);
	}
#endif
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_bLineWrite = true;

	InitAxes();
	InitFonts();
	InitPens();
	if (sTitle && sX && sY)
		InitLabels(sTitle, sX, sY);
	else
		InitLabels("График", "x", "y");
}

CGraph2::CGraph2 (vdouble &x, vdouble &y, LPSTR sTitle, LPSTR sX, LPSTR sY)
{
	if( x.Length() != y.Length())
	{
		char s[S_LEN];
		sprintf_s(s, S_LEN, "x.Length(%d) != y.Length(%d)", x.Length(), y.Length() );
		MessageBox(0,s, "CGraph2", 0);
		return;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vbYScale.OnCreate();
	bool byscale = false;
	m_vbYScale.AddMsg(&byscale);
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vPoints.OnCreate();
	m_vPoints.CreateNewVect();
	CDPoint point;
	for( int i = 0; i < x.Length(); i ++)
	{
		point.x = x[i]; 
		point.y = y[i];
		m_vPoints.AddMsgToLastVect(&point);
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_bLineWrite = true;

	InitAxes();
	InitFonts();
	InitPens();
	if (sTitle && sX && sY)
		InitLabels(sTitle, sX, sY);
	else
		InitLabels("График", "x", "y");
}

//======= Деструктор 
CGraph2::~CGraph2(){}

//===== Внешняя функция нормировки мантисс шагов сетки
void gScale2 (double span, double& step)
{
	//===== Переменная span определяет диапазон изменения
	//===== значаний одной из координат точек графика
	//===== Вычисляем порядок числа, описывающего диапазон
	int power = int(floor(log10(span)));
	//===== Множитель (zoom factor)
	double factor = pow(10.0, (double)power);
	//===== Мантисса диапазона (теперь 1 < span < 10)
	span /= factor;

	//===== Выбираем стандартный шаг сетки
	if (span<1.99)
//		step=.1;
		step=.2;
	else if (span<2.49)
//		step=.125;
		step=.25;
	else if (span<4.99)
		step=.5;
//		step=.25;
	else if (span<10.)
		step= 1.;
	else
		step = 5.;

	//===== Возвращаем реальный шаг сетки (step*10^power)
	step *= factor; 
}

void CGraph2::Scale (TData& data, double fmin, double fmax, double fstep)
{
	//===== С пустой последовательностью не работаем
	if (m_vPoints.emptyVect())
		return;

	//===== Готовимся искать экстремумы
	data.Max = fmax;
	data.Min = fmin;

	//===== Максимальная амплитуда двух экстремумов 
	double ext = max(fabs(data.Min),fabs(data.Max));

	//===== Искусственно увеличиваем порядок экстремума
	//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
	//===== не переходя к экспоненцеальной форме чисел 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	data.Power = int(floor(power/7.));

	//===== Если число не укладывается в этот диапазон
	if (data.Power != 0)
		//===== то мы восстанавливаем значение порядка
		data.Power = int(floor(power)) - 3;
	//===== Реальный множитель
	data.Factor = pow(10.,data.Power);	

	//===== Диапазон изменения мантиссы
	double span = (data.Max - data.Min)/data.Factor;
	//===== Если он нулевой,
	if (span == 0.)
		span = 0.5; // то искусственно раздвигаем график

	//===== Подбираем стандартный шаг для координатной сетки
	data.Step = fstep;

	//===== Шаг с учетом искусственных преобразований
	data.dStep = data.Step * data.Factor;

	//===== Начальная линия сетки должна быть кратна шагу
	//===== и быть меньше минимума
	data.dStart = data.dStep * int(floor(data.Min/data.dStep));
	data.Start = data.dStart/data.Factor;

	//===== Вычисляем последнюю линию сетки
	for (data.End = data.Start;
		data.End < data.Min/data.Factor + span-1e-10;  
		data.End += data.Step)
		;
	data.dEnd = data.End*data.Factor;
}

void CGraph2::Scale (TData& data)
{
	//===== С пустой последовательностью не работаем
	if (m_vPoints.emptyVect())
		return;


	//===== Готовимся искать экстремумы
	if( m_vPoints.SetCurrentVectOnFirst() )
	{
		if( m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst() )
		{
			if(m_vPoints.GetCurrentVect().GetCurrentMsgIndex() >= 0)
			{
				data.Max = data.bX ? 
					m_vPoints.GetCurrentVect().GetCurrentMsg().x :
					m_vPoints.GetCurrentVect().GetCurrentMsg().y;
			}
		}
	}

	data.Min = data.Max;

	//===== Поиск экстремумов	
	if( m_vPoints.SetCurrentVectOnFirst() )
	{
		do
		{
			if( m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst() )
			{
				do
				{
					if(m_vPoints.GetCurrentVect().GetCurrentMsgIndex() >= 0)
					{
						double d = data.bX ? 
							m_vPoints.GetCurrentVect().GetCurrentMsg().x :
							m_vPoints.GetCurrentVect().GetCurrentMsg().y;

						if (d < data.Min)
							data.Min = d;
						if (d > data.Max)
							data.Max = d;
					}
				}
				while(m_vPoints.GetCurrentVect().IncrementCurrentMsg() );
			}
		}
		while(m_vPoints.IncrementCurrentVect() );
	}

	//===== Максимальная амплитуда двух экстремумов 
	double ext = max(fabs(data.Min),fabs(data.Max));

	//===== Искусственно увеличиваем порядок экстремума
	//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
	//===== не переходя к экспоненцеальной форме чисел 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	data.Power = int(floor(power/7.));

	//===== Если число не укладывается в этот диапазон
	if (data.Power != 0)
		//===== то мы восстанавливаем значение порядка
		data.Power = int(floor(power)) - 3;
	//===== Реальный множитель
	data.Factor = pow(10.,data.Power);	

	//===== Диапазон изменения мантиссы
	double span = (data.Max - data.Min)/data.Factor;
	//===== Если он нулевой,
	if (span == 0.)
		span = 0.5; // то искусственно раздвигаем график

	//===== Подбираем стандартный шаг для координатной сетки
	gScale2 (span, data.Step);

	//===== Шаг с учетом искусственных преобразований
	data.dStep = data.Step * data.Factor;

	//===== Начальная линия сетки должна быть кратна шагу
	//===== и быть меньше минимума
	data.dStart = data.dStep * int(floor(data.Min/data.dStep));
	data.Start = data.dStart/data.Factor;

	//===== Вычисляем последнюю линию сетки
	for (data.End = data.Start;
		data.End < data.Min/data.Factor + span-1e-10;  
		data.End += data.Step)
		;
	data.dEnd = data.End*data.Factor;
}
void CGraph2::Scale (TData& data, UINT flag)
{
	//===== С пустой последовательностью не работаем
	if (m_vPoints.emptyVect())
		return;


	//===== Готовимся искать экстремумы
	bool done = false;
	if( m_vPoints.SetCurrentVectOnFirst() && m_vbYScale.SetCurrentMsgOnFirst() )
	{
		do
		{
			if( m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst() 
				&& ((flag == SCALE_FLAG_COMMON) || (flag == SCALE_FLAG_RIGHT ? m_vbYScale.GetCurrentMsg() : !m_vbYScale.GetCurrentMsg()  ) ))
			{
				do
				{
					if(m_vPoints.GetCurrentVect().GetCurrentMsgIndex() >= 0)
					{
						data.Max = data.bX ? 
							m_vPoints.GetCurrentVect().GetCurrentMsg().x :
							m_vPoints.GetCurrentVect().GetCurrentMsg().y;

						done = true;
					}
				}
				while(m_vPoints.GetCurrentVect().IncrementCurrentMsg() && !done);
			}
		}
		while(m_vPoints.IncrementCurrentVect() && m_vbYScale.IncrementCurrentMsg() && !done);
	}

	data.Min = data.Max;

	//===== Поиск экстремумов	
	if( m_vPoints.SetCurrentVectOnFirst() && m_vbYScale.SetCurrentMsgOnFirst() )
	{
		do
		{
			if( m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst() 
				&& ((flag == SCALE_FLAG_COMMON) || (flag == SCALE_FLAG_RIGHT ? m_vbYScale.GetCurrentMsg() : !m_vbYScale.GetCurrentMsg()  ) ))
			{
				do
				{
					if(m_vPoints.GetCurrentVect().GetCurrentMsgIndex() >= 0)
					{
						double d = data.bX ? 
							m_vPoints.GetCurrentVect().GetCurrentMsg().x :
							m_vPoints.GetCurrentVect().GetCurrentMsg().y;

						if (d < data.Min)
							data.Min = d;
						if (d > data.Max)
							data.Max = d;
					}
				}
				while(m_vPoints.GetCurrentVect().IncrementCurrentMsg() );
			}
		}
		while(m_vPoints.IncrementCurrentVect() && m_vbYScale.IncrementCurrentMsg());
	}

	//===== Максимальная амплитуда двух экстремумов 
	double ext = max(fabs(data.Min),fabs(data.Max));

	//===== Искусственно увеличиваем порядок экстремума
	//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
	//===== не переходя к экспоненцеальной форме чисел 
	double power = ext > 0.? log10(ext) + 3. : 0.;	
	data.Power = int(floor(power/7.));

	//===== Если число не укладывается в этот диапазон
	if (data.Power != 0)
		//===== то мы восстанавливаем значение порядка
		data.Power = int(floor(power)) - 3;
	//===== Реальный множитель
	data.Factor = pow(10.,data.Power);	

	//===== Диапазон изменения мантиссы
	double span = (data.Max - data.Min)/data.Factor;
	//===== Если он нулевой,
	if (span == 0.)
		span = 0.5; // то искусственно раздвигаем график

	//===== Подбираем стандартный шаг для координатной сетки
	gScale2 (span, data.Step);

	//===== Шаг с учетом искусственных преобразований
	data.dStep = data.Step * data.Factor;

	//===== Начальная линия сетки должна быть кратна шагу
	//===== и быть меньше минимума
	data.dStart = data.dStep * int(floor(data.Min/data.dStep));
	data.Start = data.dStart/data.Factor;

	//===== Вычисляем последнюю линию сетки
	for (data.End = data.Start;
		data.End < data.Min/data.Factor + span-1e-10;  
		data.End += data.Step)
		;
	data.dEnd = data.End*data.Factor;
}





int CGraph2::MapToLogX (double d)
{
	return m_Center.x + int (SCALE_X * m_Size.cx * d);
}

int CGraph2::MapToLogY (double d)
{
	return m_Center.y - int (SCALE_Y * m_Size.cy * d);
}




void CGraph2::Draw(HDC hDC,	tagRECT r, UINT flag)
{
	//====== С помощью контекста устройства
	//====== узнаем адрес окна, его использующего
	
	bool isPrint = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER;
	bool isMeta = GetDeviceCaps(hDC, TECHNOLOGY) == DT_METAFILE;
	bool isWnd = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASDISPLAY;

/*	if (isMeta)
		MessageBox(0,"isMeta","",0);
	if (isPrint)
		MessageBox(0,"isPrint","",0);
	if (isWnd)
		MessageBox(0,"isWnd","",0);*/

	if (isPrint)
	{
		r.left = 0;
		r.top = 0;
		r.right = r.left + GetDeviceCaps(hDC, HORZRES);
		r.bottom = r.top + GetDeviceCaps(hDC, VERTRES);
	}

	//====== Уточняем размеры окна
	m_Size.cx = r.right - r.left;
	m_Size.cy = r.bottom - r.top;

	if(!isPrint)
	{
		m_Center.x = m_Size.cx/2;
		m_Center.y = m_Size.cy/2;
//		m_Center.y = m_SizeTotal.cy/2;
	}
	else
	{
		m_Center.x = m_Size.cx/2;
		m_Center.y = m_Size.cy/2;
	}
	
//	int nDC = SaveDC(hDC);
	
	//====== Создаем черное перо для изображения рамки
	HPEN boxPen = CreatePen(PS_SOLID, 0, COLORREF(0));
	HPEN gridPen, linePen;

	if (flag == SCALE_FLAG_RIGHT)
	{
		gridPen = CreatePen(PS_SOLID, 0, RGB(92,200,178));
		linePen = CreatePen(PS_SOLID, 0, RGB(255,100,0));
	}
	else
	{
		gridPen = CreatePen(PS_SOLID, 0, RGB(92,255,178));
		linePen = CreatePen(PS_SOLID, 0, RGB(0,100,255));
	}
	
	SelectObject(hDC, boxPen);

	//====== Преобразуем координаты рамки
	int lt = MapToLogX(-0.5),
		rt = MapToLogX(0.5),
		tp = MapToLogY(0.5),
		bm = MapToLogY(-0.5);

	if (flag != SCALE_FLAG_RIGHT)
		Rectangle (hDC,lt, tp, rt, bm);

	//====== Задаем цвет и выравнивание текста
	SetTextColor(hDC, 0);
	SetTextAlign(hDC, TA_LEFT | TA_BASELINE);
	
	//====== Выбираем шрифт
	if(!isPrint)
		SelectObject (hDC, m_Font);
	else
		SelectObject (hDC, m_Font/*hPrintFont*/);
		
	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm); 
	m_LH = tm.tmHeight;
#if 0
	//====== Вычисляем атрибуты координатных осей
	Scale(m_DataX);
	Scale(m_DataY);
#endif
	//====== Выводим экстремумы функции
#define STR_LEN 32
	char str[STR_LEN];
	sprintf_s(str, STR_LEN, "Min = %c%d.%d\0",
	 m_DataY.Min<0.0?'-':' ', 
	 int(fabs(m_DataY.Min)), 
	 int(pow(10.,3)*(fabs(m_DataY.Min)-double(int(fabs(m_DataY.Min)))))
	 );
	TextOut(hDC, rt+m_LH, tp+m_LH, str, (int)strlen(str));

	sprintf_s(str, STR_LEN, "Max = %c%d.%d\0",
	 m_DataY.Max<0.0?'-':' ', 
	 int(fabs(m_DataY.Max)), 
	 int(pow(10.,3)*(fabs(m_DataY.Max)-double(int(fabs(m_DataY.Max)))))
	);
	TextOut(hDC, rt+m_LH, tp+m_LH+m_LH, str, (int)strlen(str));
		
	//====== Готовимся изображать координатную сетку
	SelectObject(hDC, gridPen);
	SetTextAlign(hDC, TA_CENTER | TA_BASELINE);
	
	//====== Рисуем вертикальные линии сетки
	for (double x = m_DataX.Start;  
			//x < m_DataX.End - m_DataX.Step/2.;
			x <= m_DataX.End ;
			x += m_DataX.Step)
	{
		//====== Нормируем координату x
		double	xn = (x - m_DataX.Start) /
						(m_DataX.End - m_DataX.Start) - 0.5;

		//====== Вычисляем оконную координату
		int xi = MapToLogX(xn);	
		//====== Пропускаем крайние линии,
		//====== так как они совпатают с рамкой
		if (x > m_DataX.Start && x < m_DataX.End)
		{
			MoveToEx(hDC, xi, bm, NULL);
			LineTo(hDC, xi, tp);
		}
		//====== Наносим цифровую метку
		MakeLabel(true,x, str, STR_LEN);
		TextOut(hDC, xi, bm+3*m_LH/2, str,(int)strlen(str));
	}

	//===== Повторяем цикл для горизонтальных линий сетки
	if (flag == SCALE_FLAG_RIGHT)
		SetTextAlign(hDC, TA_LEFT | TA_BASELINE);
	else
		SetTextAlign(hDC, TA_RIGHT | TA_BASELINE);

	for (double y = m_DataY.Start;
//			y < m_DataY.End - m_DataY.Step/2.;
			y <= m_DataY.End;
			y += m_DataY.Step)
	{
		double yn = (y - m_DataY.Start) /
						(m_DataY.End - m_DataY.Start) - 0.5;

		int yi = MapToLogY(yn);
		if (y > m_DataY.Start && y < m_DataY.End)
		{
			MoveToEx(hDC, lt, yi, NULL);
			LineTo(hDC, rt, yi);
		}
		if (y >= m_DataY.Start && y <= m_DataY.End)
		{
			MakeLabel(false, y, str, STR_LEN);

			if (flag == SCALE_FLAG_RIGHT)
				TextOut(hDC, rt+m_LH/2, yi, str, (int)strlen(str));
			else
				TextOut(hDC, lt-m_LH/2, yi, str, (int)strlen(str));
		}
	}
	SelectObject (hDC, m_YLabelFont);
	// ====== Вывод меток осей
	// pDC->TextOut(lt-m_LH/2, tp - m_LH, m_sY);

	TextOut(hDC, 
			lt-m_LH/2 - int(SCALE_X * double(m_Size.cx) * 0.1), 
			tp - m_LH, 
		m_sY, (int)strlen(m_sY)
		);
	SetTextAlign(hDC, TA_LEFT | TA_BASELINE);
	//pDC->TextOut(rt-m_LH, bm + m_LH, m_sX);
	//if(!
	SelectObject (hDC, m_TitleFont);
#if 0
	TextOut(hDC, rt-m_LH, bm + m_LH, 
		m_sX, strlen(m_sX));//)
#else
	TextOut(hDC, rt+m_LH, bm + m_LH, 
		m_sX, (int)strlen(m_sX));//)
#endif

	//====== Вывод заголовка
//	if (m_sTitle.GetLength() > 40)
	//	m_sTitle.Left(40);

	SelectObject(hDC, m_TitleFont);
	SetTextAlign(hDC, TA_CENTER | TA_BASELINE);
	TextOut(hDC, (lt+rt)/2, tp - m_LH, m_sTitle, (int)strlen(m_sTitle));
	
	//====== Вывод линии графика
//	DrawLine(hDC);
	//====== Восстанавливаем инструменты GDI
//	RestoreDC(hDC, nDC);
}

void CGraph2::DrawPoints(HDC hDC, UINT flag, bool useDiffColos)
{
//	int nDC = SaveDC(hDC);
	//====== Уничтожаем старое перо
	if (m_Pen)
		DeleteObject(m_Pen);
	//====== Создаем новое
	//m_Pen = CreatePen(PS_SOLID, m_Width, m_Clr);
	if (flag == SCALE_FLAG_RIGHT)
	{
		m_Pen = CreatePen(PS_SOLID, 1, RGB(255,100,0));
	}
	else
	{
		m_Pen = CreatePen(PS_SOLID, 1, RGB(0,100,255));
	}

	SelectObject(hDC, m_Pen);

	double	x0 = m_DataX.dStart,
			y0 = m_DataY.dStart,
			dx = m_DataX.dEnd - x0,
			dy = m_DataY.dEnd - y0;

	SelectObject(hDC, m_font);
	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm); 
	m_LH = tm.tmHeight;
	int nline = 0;
	if( m_vPoints.SetCurrentVectOnFirst() && m_vbYScale.SetCurrentMsgOnFirst() )
	{
		nline = 0;
		do
		{
			int i = 0;			

			if( m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst() )
			{
				do
				{
					if(m_vPoints.GetCurrentVect().GetCurrentMsgIndex() >= 0)
					{
						double	x = (m_vPoints.GetCurrentVect().GetCurrentMsg().x - x0) / dx - .5,
								y = (m_vPoints.GetCurrentVect().GetCurrentMsg().y - y0) / dy - .5;


						//====== Переход к оконным координатам
						// CPoint pt (MapToLogX(x),MapToLogY(y));
						int xi = MapToLogX(x),
							yi = MapToLogY(y);						
													
						SetPixel(hDC, xi,yi, RGB(0,255,0));

						i++;
					}
				}
				while(m_vPoints.GetCurrentVect().IncrementCurrentMsg() );
			}
			nline++;
		}
		while(m_vPoints.IncrementCurrentVect() && m_vbYScale.IncrementCurrentMsg());
	}
}






void CGraph2::DrawLine(HDC hDC, UINT flag, bool useDiffColos)
{
//	int nDC = SaveDC(hDC);
	//====== Уничтожаем старое перо
	if (m_Pen)
		DeleteObject(m_Pen);
	//====== Создаем новое
	//m_Pen = CreatePen(PS_SOLID, m_Width, m_Clr);
	if (flag == SCALE_FLAG_RIGHT)
	{
		m_Pen = CreatePen(PS_SOLID, 1, RGB(255,100,0));
	}
	else
	{
		m_Pen = CreatePen(PS_SOLID, 1, RGB(0,100,255));
	}

	SelectObject(hDC, m_Pen);

	double	x0 = m_DataX.dStart,
			y0 = m_DataY.dStart,
			dx = m_DataX.dEnd - x0,
			dy = m_DataY.dEnd - y0;

	SelectObject(hDC, m_font);
	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm); 
	m_LH = tm.tmHeight;
	int nline = 0;
	if( m_vPoints.SetCurrentVectOnFirst() && m_vbYScale.SetCurrentMsgOnFirst() )
	{
		nline = 0;
		do
		{
			int i = 0;			
			if (useDiffColos)
			{
				if (nline == 0)
				{
					if (m_Pen)	DeleteObject(m_Pen);
					m_Pen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
				}
				if (nline == 1)
				{
					if (m_Pen)	DeleteObject(m_Pen);
					m_Pen = CreatePen(PS_SOLID, 1, RGB(0,255,0));
				}
				if (nline == 2)
				{
					if (m_Pen)	DeleteObject(m_Pen);
					m_Pen = CreatePen(PS_SOLID, 1, RGB(0,0,255));
				}
				SelectObject(hDC, m_Pen);
			}
			if( m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst() 
				&& ((flag == SCALE_FLAG_COMMON) || (flag == SCALE_FLAG_RIGHT ? m_vbYScale.GetCurrentMsg() : !m_vbYScale.GetCurrentMsg()  ) ))
			{
				do
				{
					if(m_vPoints.GetCurrentVect().GetCurrentMsgIndex() >= 0)
					{
						double	x = (m_vPoints.GetCurrentVect().GetCurrentMsg().x - x0) / dx - .5,
								y = (m_vPoints.GetCurrentVect().GetCurrentMsg().y - y0) / dy - .5;


						//====== Переход к оконным координатам
						// CPoint pt (MapToLogX(x),MapToLogY(y));
						int xi = MapToLogX(x),
							yi = MapToLogY(y);

						
						// line extremums write if need
						if (m_bLineWrite)
						{

							char s[S_LEN];
							if ( i == 0 && m_vPoints.GetCurrentVect().msgSize() > 2)
							{
								if (m_vPoints.GetCurrentVect().GetFirstMsg().y > m_vPoints.GetCurrentVect().GetSecondMsg().y)
								{
									sprintf_s(s, S_LEN,"%.2lf", m_vPoints.GetCurrentVect().GetFirstMsg().y);
									TextOut(hDC, xi, yi - m_LH/2, 
										s, (int)strlen(s));//)
								}
								else
								{
									sprintf_s(s, S_LEN, "%.2lf", m_vPoints.GetCurrentVect().GetFirstMsg().y);
									TextOut(hDC, xi, yi + m_LH, 
										s, (int)strlen(s));//)
								}
							}
							if ( i == m_vPoints.GetCurrentVect().msgSize() - 1 && m_vPoints.GetCurrentVect().msgSize() > 2)
							{
								if (m_vPoints.GetCurrentVect().GetLastMsg().y > m_vPoints.GetCurrentVect().GetPreLastMsg().y)
								{
									sprintf_s(s, S_LEN, "%.2lf", m_vPoints.GetCurrentVect().GetLastMsg().y);
									TextOut(hDC, xi, yi - m_LH/2, 
										s, (int)strlen(s));//)
								}
								else
								{
									sprintf_s(s, S_LEN, "%.2lf", m_vPoints.GetCurrentVect().GetLastMsg().y);
									TextOut(hDC, xi, yi + m_LH, 
										s, (int)strlen(s));//)
								}
							}
							if ( i > 0 && i < m_vPoints.GetCurrentVect().msgSize()-1 )
							{
								if (m_vPoints.GetCurrentVect().GetPreCurrentMsg().y <= m_vPoints.GetCurrentVect().GetCurrentMsg().y 
									&& m_vPoints.GetCurrentVect().GetCurrentMsg().y >= m_vPoints.GetCurrentVect().GetNextCurrentMsg().y)
								{
									sprintf_s(s, S_LEN, "%.2lf", m_vPoints.GetCurrentVect().GetCurrentMsg().y);
									TextOut(hDC, xi, yi - m_LH/2, 
										s, (int)strlen(s));//)
								}
								if (m_vPoints.GetCurrentVect().GetPreCurrentMsg().y >= m_vPoints.GetCurrentVect().GetCurrentMsg().y 
									&& m_vPoints.GetCurrentVect().GetCurrentMsg().y <= m_vPoints.GetCurrentVect().GetNextCurrentMsg().y)
								{
									sprintf_s(s, S_LEN, "%.2lf", m_vPoints.GetCurrentVect().GetCurrentMsg().y);
									TextOut(hDC, xi, yi + m_LH, 
										s, (int)strlen(s));//)
								}
							}

						}
						//====== Если точка первая, то ставим перо
						if (m_vPoints.GetCurrentVect().GetCurrentMsgIndex() ==0)
							MoveToEx(hDC,xi,yi,NULL);
						else
							LineTo(hDC,xi,yi);
						i++;
					}
				}
				while(m_vPoints.GetCurrentVect().IncrementCurrentMsg() );
			}
			nline++;
		}
		while(m_vPoints.IncrementCurrentVect() && m_vbYScale.IncrementCurrentMsg());
	}
}




void CGraph2::MakeLabel(bool bX, double& v, char* s, size_t len)
{
	//====== Сначала делаем грубую прикидку
	//====== Пробуем поместиться в 20 позиций
	//====== Выясняем порядок шага сетки,
	//====== переворачивая его знак (трюк)
	int nDigits = int(ceil(-log10(bX ? m_DataX.Step
									: m_DataY.Step)));
	//====== Если все изменения происходят до запятой,
	//====== то цифры после запятой нас не интересуют
	if (nDigits <= 0)
		nDigits = -1;
	else
	{
		if (bX)
			nDigits++;	// Эстетическая добавка
	}

	if (nDigits <= 0)
	{
		sprintf_s(s, len, "%c%d\0",
			 v<0.0?'-':' ', 
			 int(fabs(v)) 
			);
	}
	else
	{
		sprintf_s(s, len,"%c%d.%d\0",
			 v<0.0?'-':' ', 
			 int(fabs(v)), 
			 int(pow(10.,nDigits)*(fabs(v)-double(int(fabs(v)))))
			);
	}

	//====== Слева усекаем все
//	s.TrimLeft();

	//====== Справа оставляем минимум разрядов
//	s = s.Left(s.Find(".") + nDigits + 1);

	int iPower = bX ? m_DataX.Power : m_DataY.Power;
	//====== Нужен ли порядок?
	if (iPower != 0)
	{
		//====== Нужен, если не поместились в (10^-3, 10^+4)
		const size_t s_add_len = 64;
		char add[s_add_len];
		sprintf_s (add, s_add_len, "·e%d\0",iPower);
		strcat_s(s, len, add);
	}
}


void CGraph2::Scale(UINT flag)
{
	//====== Вычисляем атрибуты координатных осей
	Scale(m_DataX);
	Scale(m_DataY, flag);

}

void CGraph2::GetScale(double &fXmin, double &fXmax, double &fXstep, double &fYmin, double &fYmax, double &fYstep)
{
	fXmax = m_DataX.Max;
	fXmin = m_DataX.Min;
	fXstep = m_DataX.Step;

	fYmax = m_DataY.Max;
	fYmin = m_DataY.Min;
	fYstep = m_DataY.Step;

}
void CGraph2::SetScale(double fXmin, double fXmax, double fXstep, double fYmin, double fYmax, double fYstep)
{
	Scale (m_DataX, fXmin, fXmax, fXstep);
	Scale (m_DataY, fYmin, fYmax, fYstep);
}

void CGraph2::InitFonts()
{
	//======= Создаем шрифт для оцифровки осей
	m_font = CreateFont(12,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= Создаем шрифт для оцифровки осей
	m_Font = CreateFont(14,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= Выясняем вертикальный размер буквы
	//======= Создаем шрифт для вывода заголовка
	m_YLabelFont = CreateFont(12,0,900,900,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
/*	TEXTMETRIC tm;
	HDC hdc;
	SelectObject(hdc, &m_Font);
	GetTextMetrics(hdc, &tm); 
	m_LH = tm.tmHeight;*/
	m_LH = 10;

	//======= Создаем шрифт для вывода заголовка
	m_TitleFont = CreateFont(24,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");


}

void CGraph2::InitPens()
{
	//======= Задаем параметры пера
	m_Clr = RGB(0,0,255);
	m_Width = 2;

}

void CGraph2::InitLabels(LPSTR sTitle, LPSTR sX, LPSTR sY)
{
	strcpy(m_sTitle, sTitle);
	strcpy(m_sX, sX);
	strcpy(m_sY, sY);

}

void CGraph2::InitAxes()
{
	//======= Готовим данные, характеризующие оси координат	ZeroMemory(&m_DataX, sizeof(TData));
	ZeroMemory(&m_DataY, sizeof(TData));
	m_DataX.bX = true;
	m_DataY.bX = false;

}

void CGraph2::clear()
{
	m_vPoints.clearVect();
	m_vPoints.clearMsg();
	m_vbYScale.clearMsg();
}

void CGraph2::AddPointValue(int iVect, double &x, double &y)
{
	if( m_vPoints.SetCurrentVectOnFirst() )
	{
		do
		{
			if(m_vPoints.GetCurrentVectIndex() == iVect)
			{
				CDPoint point;
				point.x = x;
				point.y = y;
				if( m_vPoints.GetCurrentVect().AddMsg(&point) )
				{
				}
			}
		}
		while(m_vPoints.IncrementCurrentVect() );
	}
}
