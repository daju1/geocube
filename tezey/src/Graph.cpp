// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "Graph.h"
#include "raporto.h"
#include "../../array/src/vdouble.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//#define WriteRaporto(s)  WriteRaportoB(s)
//#define WriteRaporto(s)  MessageBox(0,s,"",0)
//extern void WriteRaportoB(LPCTSTR s);

extern void datevec(double dn, int& y, int& mo, int& d, int& h, int& mi, int& s, int& milli);
extern void numdate(double dn, int& h, int& mi, int& s, int& milli);
//extern void ErrorExit(LPTSTR lpszFunction, bool toExitProcess);
extern bool g_ToScaleYOnHScroll;
//===== Доля окна, занимаемая графиком
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//======= Конструктор класса CGraph
CGraph::CGraph (
#ifndef DRAW_OLD_VECTOR_VDPOINTS
				vect<CpVDPoints>& pt, 
#else
				Vector<CpVDPoints>& pt, 
#endif
//				LPSTR sTitle,
//				LPSTR sX, LPSTR sY,
				double yshift, double scale_y,
				tagSIZE sizeTotal)
#ifndef DRAW_OLD_VECTOR_VDPOINTS
				: m_vPoints(pt)
#else
				: m_vpPoints(pt)
#endif
{
	m_SCALE_X = 0.75;
	m_SCALE_Y = scale_y;//0.22/6;0.036666666666
	m_SizeTotal = sizeTotal;
	m_yshift = yshift;
	//======= Готовим данные, характеризующие оси координат	ZeroMemory(&m_DataX, sizeof(TData));
	ZeroMemory(&m_DataY, sizeof(TData));
	ZeroMemory(&m_DataX, sizeof(TData));
	m_DataX.bX = true;
	m_DataY.bX = false;

//	strcpy(m_sTitle, sTitle);
//	strcpy(m_sX, sX);
//	strcpy(m_sY, sY);

	//======= Выясняем вертикальный размер буквы
//	TEXTMETRIC tm;
//	HDC hdc;
//	SelectObject(hdc, &m_Font);
//	GetTextMetrics(hdc, &tm); 
//	m_LH = tm.tmHeight;
	m_LH = 10;

	int nGraphs = 10;
	m_vClr.resize(nGraphs);
	//======= Задаем параметры пера
	for (int n = 0; n < nGraphs; n++)
	{
		switch(n)
		{
		case 0:	*(m_vClr.data+n) = RGB(100,100,0);break;//Open
		case 1:	*(m_vClr.data+n) = RGB(255,0,0);break;//High
		case 2:	*(m_vClr.data+n) = RGB(0,0,255);break;//Low
		case 3:	*(m_vClr.data+n) = RGB(0,255,0);break;//Close
		case 4:	*(m_vClr.data+n) = RGB(255,0,0);break;
		case 5:	*(m_vClr.data+n) = RGB(255,0,0);break;
		case 6:	*(m_vClr.data+n) = RGB(100,100,0);break;
		case 7:	*(m_vClr.data+n) = RGB(100,100,0);break;
		case 8:	*(m_vClr.data+n) = RGB(0,0,0);break;
		case 9:	*(m_vClr.data+n) = RGB(0,0,0);break;
		default:*(m_vClr.data+n) = RGB(0,0,0);break;
		}
	}
	m_vWidth.resize(nGraphs);
	for (int n = 0; n < nGraphs; n++)
	{
		switch(n)
		{
		case 0:	*(m_vWidth.data+n) = 1;break;
		case 1:	*(m_vWidth.data+n) = 1;break;
		case 2:	*(m_vWidth.data+n) = 1;break;
		case 3:	*(m_vWidth.data+n) = 1;break;
		case 4:	*(m_vWidth.data+n) = 1;break;
		case 5:	*(m_vWidth.data+n) = 1;break;
		case 6:	*(m_vWidth.data+n) = 1;break;
		case 7:	*(m_vWidth.data+n) = 1;break;
		case 8:	*(m_vWidth.data+n) = 1;break;
		case 9:	*(m_vWidth.data+n) = 1;break;
		default:*(m_vWidth.data+n) = 1;break;
		}
	}
}

//======= Деструктор 
CGraph::~CGraph()
{
}

//===== Внешняя функция нормировки мантисс шагов сетки
void gScale (double span, double& step)
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
		step=.2;
	else if (span<2.49)
		step=.25;
	else if (span<4.99)
		step=.5;
	else if (span<10.)
		step= 1.;
	else
		step = 5.;

	//===== Возвращаем реальный шаг сетки (step*10^power)
	step *= factor; 
	step *= 2; 
}
//===== Внешняя функция нормировки мантисс шагов сетки
void gTimeScale (double span, double& step)
{
	//===== Переменная span определяет диапазон изменения
	//===== значаний одной из координат точек графика
	//===== Вычисляем порядок числа, описывающего диапазон
//	int power = int(floor(log10(span)));
	//===== Множитель (zoom factor)
//	double factor = pow(10.0, (double)power);

	//===== Мантисса диапазона (теперь 1 < span < 10)
//	span /= factor;

	//===== Выбираем стандартный шаг сетки
	if (span<=1./24/60/4.)// меньше 15 сек
		step=1./24./60/60.; //1 сек

	else if (span<=1./24/60.)// меньше 1 мин
		step=1./24./60/12.; //5 сек

	else if (span<=1./24/12.)// меньше 5 мин
		step=1./24./60/4.; //15 сек

	else if (span<=1./24/4.)// меньше 15 мин
		step=1./24./60.; // 1 минута

	else if (span<=1./24.)//меньше часа
		step=1./24/12.;// 5 мин

	else if (span<=1./12.)//меньше 2 часов
		step=1./24/4.;// 15 мин

	else if (span<=1./4.)//меньше 6 часов
		step=1./24/2.;// 30 мин

	else if (span<=1./2.)//меньше 12 часов
		step=1./24.;// 60 мин

	else if (span<=1.0)// меньше суток
		step=1./12.;//2 часа

	else if (span<=2.0)// меньше 2 суток
		step=1./6.;// 4 часа

	else if (span<=3.0)// меньше 3 суток
		step=1./3.;//8 часов

	else if (span<=10.0)// меньше 3 суток
		step=.5;//12 часов

	else if (span<=60.0)// меньше 60 суток
		step=1.;// сутки

	else if (span<=180.0)// меньше 60 суток
		step=7.;// неделя

	else if (span<=365.0)// меньше 60 суток
		step=28.;// неделя
	else
		step = floor(span/25);


	//===== Возвращаем реальный шаг сетки (step*10^power)
//	step *= factor; 
//	step *= 2; 
}

void CGraph::Scale (TData& data, int iFirst, int iLast, bool useTDataMinMaxX)
{
WriteRaporto("Scale 1\n");
		//===== Готовимся искать экстремумы
	
	double Max,
		Min, minX, maxX;
	if (useTDataMinMaxX)
	{
		minX = data.Min;
		maxX = data.Max;
	}
	int i = 0;
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	bool findfirst = true;
	if (m_vPoints.SetCurrentMsgOnFirst())
	{
		bool bIncremented;
		do
		{
			if (m_vPoints.GetCurrentMsg().toDraw 
				&& HSCROLL_LENGTH - iFirst - iLast > 0 
				&& m_vPoints.GetCurrentMsg().py->Length() > 0)
			{
				double lengthX;
				if (useTDataMinMaxX)
					lengthX = maxX - minX;
				else					
					lengthX = m_vPoints.GetCurrentMsg().maxX - m_vPoints.GetCurrentMsg().minX;
				if (g_ToScaleYOnHScroll)
				{
					double epsilonX = lengthX / double(HSCROLL_LENGTH);

					double minx;
					double maxx;
					if (useTDataMinMaxX)
						minx=minX + epsilonX * double(iFirst);
					else
						minx=m_vPoints.GetCurrentMsg().minX + epsilonX * double(iFirst);

					if (useTDataMinMaxX)
						maxx=maxX - epsilonX * double(iLast) ;
					else
						maxx=m_vPoints.GetCurrentMsg().maxX - epsilonX * double(iLast) ;
#ifdef DO_RAPORT
char str[255];
sprintf(str,"Scale minx = %f maxx = %f epsilonX = %fb m_vPoints.GetCurrentMsg().minX %f m_vPoints.GetCurrentMsg().maxX %f\n",
		minx, maxx, epsilonX, m_vPoints.GetCurrentMsg().minX, m_vPoints.GetCurrentMsg().maxX);
WriteRaporto(str);
#endif					
					if(data.bX)
					{
						data.Min = minx ;
						data.Max = maxx ;
					}
					else //if(!data.bX)
					{
						// ориентировочное определение начального и крайнего индексов
						int i1,i2, len=m_vPoints.GetCurrentMsg().px->m_length;

						i1 = int(double(len)  *       double(iFirst)/double(HSCROLL_LENGTH));
						i2 = int(double(len-1)*(1.0 - double(iLast) /double(HSCROLL_LENGTH)));
						// подстройка начального индекса
						double mnx = m_vPoints.GetCurrentMsg().px->operator [](i1);
						if (mnx > minx+epsilonX)
						{
							bool decrement;
							do
							{
								if(i1>0)
								{
									decrement = true;
									i1--;
									mnx = m_vPoints.GetCurrentMsg().px->operator [](i1);
								}
								else
									decrement = false;

							}
							while( mnx > minx+epsilonX && decrement );
						}
						else
						{
							if (mnx < minx-epsilonX)
							{
								bool inrement;
								do
								{
									if(i1<len-2)
									{
										inrement = true;
										i1++;
										mnx = m_vPoints.GetCurrentMsg().px->operator [](i1);
									}
									else
										inrement = false;
								}
								while( mnx < minx-epsilonX && inrement );
							}
						}
						// подстройка крайнего правого индекса
						double mxx = m_vPoints.GetCurrentMsg().px->operator [](i2);
						if (mxx > maxx+epsilonX)
						{
							bool decrement;
							do
							{
								if(i2>1)
								{
									decrement = true;
									i2--;
									mxx = m_vPoints.GetCurrentMsg().px->operator [](i2);
								}
								else
									decrement = false;
							}
							while( mxx > maxx+epsilonX && decrement );
						}
						else
						{
							if (mxx < maxx-epsilonX)
							{
								bool inrement;
								do
								{
									if(i2<len-1)
									{
										inrement = true;
										i2++;
										mxx = m_vPoints.GetCurrentMsg().px->operator [](i2);
									}
									else
										inrement = false;
								}
								while( mxx < maxx-epsilonX && inrement );
							}
						}
#ifdef DO_RAPORT
sprintf(str,"Scale i1 = %d i2 = %d len = %d\n",
		i1,i2,len);
WriteRaporto(str);
#endif
						// вычисление максимума и минимума Y
						data.Min = m_vPoints.GetCurrentMsg().py->MinFromTo(i1,i2);
						data.Max = m_vPoints.GetCurrentMsg().py->MaxFromTo(i1,i2);
					}
				}
				else
				{
					data.Min = data.bX ? 
						useTDataMinMaxX ? minX + lengthX * double(iFirst)/double(HSCROLL_LENGTH) : m_vPoints.GetCurrentMsg().minX + lengthX * double(iFirst)/double(HSCROLL_LENGTH) 
						: m_vPoints.GetCurrentMsg().minY;
					data.Max = data.bX ? 
						useTDataMinMaxX ? maxX - lengthX * double(iLast) /double(HSCROLL_LENGTH) : m_vPoints.GetCurrentMsg().maxX - lengthX * double(iLast) /double(HSCROLL_LENGTH) 
						: m_vPoints.GetCurrentMsg().maxY;
				}			
				findfirst = false;
			}
			bIncremented = m_vPoints.IncrementCurrentMsg();
		}
		while(bIncremented && findfirst);
WriteRaporto("Scale bIncremented && findfirst\n");
		if (bIncremented)
		{
			do
			{
				if (m_vPoints.GetCurrentMsg().toDraw 
					&& HSCROLL_LENGTH - iFirst - iLast > 0 
					&& m_vPoints.GetCurrentMsg().py->Length() > 0)
				{
					double lengthX;
					if (useTDataMinMaxX)
						lengthX = maxX - minX;
					else					
						lengthX = m_vPoints.GetCurrentMsg().maxX - m_vPoints.GetCurrentMsg().minX;
					if (g_ToScaleYOnHScroll)
					{
						double epsilonX = lengthX / double(HSCROLL_LENGTH);
						double minx;
						double maxx;
						if (useTDataMinMaxX)
							minx=minX + epsilonX * double(iFirst);
						else
							minx=m_vPoints.GetCurrentMsg().minX + epsilonX * double(iFirst);

						if (useTDataMinMaxX)
							maxx=maxX - epsilonX * double(iLast) ;
						else
							maxx=m_vPoints.GetCurrentMsg().maxX - epsilonX * double(iLast) ;
						if(data.bX)
						{
							Min = minx ;
							Max = maxx ;
						}
						else //if(!data.bX)
						{
							// ориентировочное определение начального и крайнего индексов
							int i1,i2, len=m_vPoints.GetCurrentMsg().px->m_length;

							i1 = int(double(len)  *       double(iFirst)/double(HSCROLL_LENGTH));
							i2 = int(double(len-1)*(1.0 - double(iLast) /double(HSCROLL_LENGTH)));
							
							// подстройка начального индекса
							double mnx = m_vPoints.GetCurrentMsg().px->operator [](i1);
							if (mnx > minx+epsilonX)
							{
								bool decrement;
								do
								{
									if(i1>0)
									{
										decrement = true;
										i1--;
										mnx = m_vPoints.GetCurrentMsg().px->operator [](i1);
									}
									else
										decrement = false;

								}
								while( mnx > minx+epsilonX && decrement );
							}
							else
							{
								if (mnx < minx-epsilonX)
								{
									bool inrement;
									do
									{
										if(i1<len-2)
										{
											inrement = true;
											i1++;
											mnx = m_vPoints.GetCurrentMsg().px->operator [](i1);
										}
										else
											inrement = false;
									}
									while( mnx < minx-epsilonX && inrement );
								}
							}
							// подстройка крайнего правого индекса
							double mxx = m_vPoints.GetCurrentMsg().px->operator [](i2);
							if (mxx > maxx+epsilonX)
							{
								bool decrement;
								do
								{
									if(i2>1)
									{
										decrement = true;
										i2--;
										mxx = m_vPoints.GetCurrentMsg().px->operator [](i2);
									}
									else
										decrement = false;

								}
								while( mxx > maxx+epsilonX && decrement );
							}
							else
							{
								if (mxx < maxx-epsilonX)
								{
									bool inrement;
									do
									{
										if(i2<len-1)
										{
											inrement = true;
											i2++;
											mxx = m_vPoints.GetCurrentMsg().px->operator [](i2);
										}
										else
											inrement = false;
									}
									while( mxx < maxx-epsilonX && inrement );
								}
							}
							// вычисление максимума и минимума Y
							Min = m_vPoints.GetCurrentMsg().py->MinFromTo(i1,i2);
							Max = m_vPoints.GetCurrentMsg().py->MaxFromTo(i1,i2);
						}
					}
					else
					{
						data.Min = data.bX ? 
							useTDataMinMaxX ? minX + lengthX * double(iFirst)/double(HSCROLL_LENGTH) : m_vPoints.GetCurrentMsg().minX + lengthX * double(iFirst)/double(HSCROLL_LENGTH) 
							: m_vPoints.GetCurrentMsg().minY;
						data.Max = data.bX ? 
							useTDataMinMaxX ? maxX - lengthX * double(iLast) /double(HSCROLL_LENGTH) : m_vPoints.GetCurrentMsg().maxX - lengthX * double(iLast) /double(HSCROLL_LENGTH) 
							: m_vPoints.GetCurrentMsg().maxY;
					}
					//
					data.Max = data.Max > Max ? data.Max : Max;
					data.Min = data.Min < Min ? data.Min : Min;
				}
			}
			// Перемещаем текущий внутренний вектор
			while(m_vPoints.IncrementCurrentMsg());
WriteRaporto("Scale while(m_vPoints.IncrementCurrentMsg());\n");
		}
#else
	bool findfirst = true;
	do
	{
		if ((m_vpPoints.data+i)->toDraw 
			&& HSCROLL_LENGTH - iFirst - iLast > 0 
			&& (m_vpPoints.data+i)->py->Length() > 0)
		{

#ifndef DRAW_SCALE_FAST_X_MAXMIN
			data.Max = data.bX ? (m_vpPoints.data+i)->px->Max(iFirst, iLast) : (m_vpPoints.data+i)->maxY;
			data.Min = data.bX ? (m_vpPoints.data+i)->px->Min(iFirst, iLast) : (m_vpPoints.data+i)->minY;
#else
			double lengthX = (m_vpPoints.data+i)->maxX - (m_vpPoints.data+i)->minX;
			if (g_ToScaleYOnHScroll)
			{
				double epsilonX = lengthX / double(HSCROLL_LENGTH);
				double minx=(m_vpPoints.data+i)->minX + epsilonX * double(iFirst);
				double maxx=(m_vpPoints.data+i)->maxX - epsilonX * double(iLast) ;
				
				if(data.bX)
				{
					data.Min = minx ;
					data.Max = maxx ;
				}
				else //if(!data.bX)
				{
					// ориентировочное определение начального и крайнего индексов
					int i1,i2, len=(m_vpPoints.data+i)->px->m_length;

					i1 = int(double(len)  *       double(iFirst)/double(HSCROLL_LENGTH));
					i2 = int(double(len-1)*(1.0 - double(iLast) /double(HSCROLL_LENGTH)));
					
					// подстройка начального индекса
					double mnx = (m_vpPoints.data+i)->px->operator [](i1);
					if (mnx > minx+epsilonX)
					{
						bool decrement;
						do
						{
							if(i1>0)
							{
								decrement = true;
								i1--;
								mnx = (m_vpPoints.data+i)->px->operator [](i1);
							}
							else
								decrement = false;

						}
						while( mnx > minx+epsilonX && decrement );
					}
					else
					{
						if (mnx < minx-epsilonX)
						{
							bool inrement;
							do
							{
								if(i1<len-2)
								{
									inrement = true;
									i1++;
									mnx = (m_vpPoints.data+i)->px->operator [](i1);
								}
								else
									inrement = false;
							}
							while( mnx < minx-epsilonX && inrement );
						}
					}
					// подстройка крайнего правого индекса
					double mxx = (m_vpPoints.data+i)->px->operator [](i2);
					if (mxx > maxx+epsilonX)
					{
						bool decrement;
						do
						{
							if(i2>1)
							{
								decrement = true;
								i2--;
								mxx = (m_vpPoints.data+i)->px->operator [](i2);
							}
							else
								decrement = false;

						}
						while( mxx > maxx+epsilonX && decrement );
					}
					else
					{
						if (mxx < maxx-epsilonX)
						{
							bool inrement;
							do
							{
								if(i2<len-1)
								{
									inrement = true;
									i2++;
									mxx = (m_vpPoints.data+i)->px->operator [](i2);
								}
								else
									inrement = false;
							}
							while( mxx < maxx-epsilonX && inrement );
						}
					}
					// вычисление максимума и минимума Y
					data.Min = (m_vpPoints.data+i)->py->MinFromTo(i1,i2);
					data.Max = (m_vpPoints.data+i)->py->MaxFromTo(i1,i2);
				}
			}
			else
			{
				data.Min = data.bX ? (m_vpPoints.data+i)->minX + lengthX * double(iFirst)/double(HSCROLL_LENGTH) : (m_vpPoints.data+i)->minY;
				data.Max = data.bX ? (m_vpPoints.data+i)->maxX - lengthX * double(iLast) /double(HSCROLL_LENGTH) : (m_vpPoints.data+i)->maxY;
			}
#endif
			
			findfirst = false;
		}
		i++;
	}
	while (i < m_vpPoints.Size() && findfirst);

	for(int n = i; n < m_vpPoints.Size(); n++)
	{
		if ((m_vpPoints.data+n)->toDraw 
			&& HSCROLL_LENGTH - iFirst - iLast > 0 
			&& (m_vpPoints.data+n)->py->Length() > 0)
		{

#ifndef DRAW_SCALE_FAST_X_MAXMIN
			Max = data.bX ? (m_vpPoints.data+n)->px->Max(iFirst, iLast) : (m_vpPoints.data+n)->maxY;
			Min = data.bX ? (m_vpPoints.data+n)->px->Min(iFirst, iLast) : (m_vpPoints.data+n)->minY;
#else
			double lengthX = ((m_vpPoints.data+n)->maxX - (m_vpPoints.data+n)->minX);
			Min = data.bX ? (m_vpPoints.data+n)->minX + lengthX * double(iFirst)/double(HSCROLL_LENGTH) : (m_vpPoints.data+n)->minY;
			Max = data.bX ? (m_vpPoints.data+n)->maxX - lengthX * double(iLast) /double(HSCROLL_LENGTH) : (m_vpPoints.data+n)->maxY;
#endif
			data.Max = data.Max > Max ? data.Max : Max;
			data.Min = data.Min < Min ? data.Min : Min;
		}
	}
#endif
	if (!data.bX)
	{
WriteRaporto("Scale (!data.bX) \n");
		//====== Выводим экстремумы функции	

		//===== Максимальная амплитуда двух экстремумов 
		double ext = max(fabs(data.Min),fabs(data.Max));

		//===== Искусственно увеличиваем порядок экстремума
		//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
		//===== не переходя к экспоненцеальной форме чисел 
		double power = ext > 0.? log10(ext) + 2. : 0.;	
		data.Power = int(floor(power/7.));

		//===== Если число не укладывается в этот диапазон
		if (data.Power != 0)
			//===== то мы восстанавливаем значение порядка
			data.Power = int(floor(power)) - 2;
		//===== Реальный множитель
		data.Factor = pow(10.0, data.Power);	

		//===== Диапазон изменения мантиссы
		double span = (data.Max - data.Min)/data.Factor;
		//===== Если он нулевой,
		if (fabs(span) < 0.001)
			span = 0.5; // то искусственно раздвигаем график

		//===== Подбираем стандартный шаг для координатной сетки
		gScale (span, data.Step);

		//===== Шаг с учетом искусственных преобразований
		data.dStep = data.Step * data.Factor;

		//===== Начальная линия сетки должна быть кратна шагу
		//===== и быть меньше минимума

		data.dStart = data.dStep * int(floor(data.Min/data.dStep));
		data.Start = data.dStart/data.Factor;

		//===== Вычисляем последнюю линию сетки
#ifdef DO_RAPORT
char str[255];
sprintf(str, 
		"span %f, data.Start %f, data.Step %f, data.dStep %f, data.Min %f ,data.Max %f, data.Factor %f, data.Min/data.Factor %f",
		span, data.Start, data.Step, data.dStep, data.Min, data.Max, data.Factor, data.Min/data.Factor);
WriteRaporto(str);
#endif
#if 1
		for (data.End = data.Start;
			data.End < data.Min/data.Factor + span - 1e-10;  
			data.End += data.Step)
			;
#else
		data.End = data.Start 
			+ int((data.Min/data.Factor + span - 1e-10) / data.Step+1)
			* data.Step;
#endif

		//data.End = data.Start + data.Step * int(floor((data.Max-data.Min)/data.dStep));
		data.dEnd = data.End*data.Factor;
WriteRaporto("Scale (!data.bX) }\n");

	}
	else
	{
WriteRaporto("Scale else(!data.bX) }\n");
		//====== Выводим экстремумы функции	

		//===== Максимальная амплитуда двух экстремумов 
		double ext = max(fabs(data.Min),fabs(data.Max));

		//===== Искусственно увеличиваем порядок экстремума
		//===== на 3 единицы, так как мы хотим покрыть 7 порядков,
		//===== не переходя к экспоненцеальной форме чисел 
		//double power = ext > 0.? log10(ext) + 2. : 0.;	
		data.Power = 0;

		//===== Реальный множитель
		data.Factor = 1.;	

		//===== Диапазон изменения мантиссы
		double span = data.Max - data.Min;
		if (fabs(span) < 1./24/3600.)
		span = 1./24/3600.; // то искусственно раздвигаем график

		//===== Подбираем стандартный шаг для координатной сетки
		gTimeScale (span, data.Step);

		//===== Шаг с учетом искусственных преобразований
		data.dStep = data.Step;

		//===== Начальная линия сетки должна быть кратна шагу
		//===== и быть меньше минимума
#if 1
		data.dStart = data.dStep * int(floor(data.Min/data.dStep));
		data.Start = data.dStart;
#else
		if( data.Min >= 0.)
		{
			data.Start = data.Step * int(data.Min/data.Step-0.5);
		}
		else
		{
			data.Start = - data.Step * int((-data.Min)/data.Step+0.5);
		}
#endif
#if 0
		char str[255];
		sprintf(str, "data.Start = %lf data.Step = %lf data.Min = %lf",
			data.Start, data.Step, data.Min);
		MessageBox(0,str,"",0);
#endif
	//	data.Start = data.Min;
		data.dStart = data.Start;

		//===== Вычисляем последнюю линию сетки
#if 1
		data.End = data.Start + data.Step * int(ceil((data.Max-data.Start)/data.dStep));
		data.dEnd = data.End;
#else
		if( data.Max >= 0.)
		{
			data.End = data.Step * int(data.Max/data.Step+1.0);
		}
		else
		{
			data.End = - data.Step * int((-data.Max)/data.Step-1.0);
		}

	//	data.dEnd = data.Max;
		data.dEnd = data.End;
#endif

#if 0
		char str2[255];
		sprintf(str2, "data.End = %lf data.Step = %lf data.Max = %lf",
			data.End, data.Step, data.Max);
		MessageBox(0,str2,"",0);
#endif
	
#ifdef DO_RAPORT
char str[255];
sprintf(str, 
		"span %f, data.Start %f, data.Step %f, data.dStep %f, data.Min %f ,data.Max %f, data.Factor %f, data.Min/data.Factor %f",
		span, data.Start, data
		.Step, data.dStep, data.Min, data.Max, data.Factor, data.Min/data.Factor);
WriteRaporto(str);
WriteRaporto("Scale else(!data.bX) end\n");
#endif

	
	
	}
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	}
#endif
WriteRaporto("Scale end\n");

}
#if 1
int CGraph::MapToLogX (double d)
{
	return int(m_Center.x + m_SCALE_X * m_Size.cx * d);
}

int CGraph::MapToLogY (double d)
{
	return int(/*m_Center.y*/ - m_SCALE_Y/* * m_SizeTotal.cy*/ * d + m_yshift);
}
int CGraph::MapToLogYPrint (double d)
{
//	return int(/*m_Center.y*/ - m_SCALE_Y /** m_Size.cy*/ * d + m_yshift * m_Size.cy / m_SizeTotal.cy);
	return int(/*m_Center.y*/ - m_SCALE_Y/m_SizeTotal.cy* m_Size.cy * d + m_yshift * m_Size.cy / m_SizeTotal.cy);
}
#else
int CGraph::MapToLogX (double d)
{
	return (int)m_Center.x + int (m_SCALE_X * m_Size.cx * d);
}
int CGraph::MapToLogY (double d)
{
	return /*(int)m_Center.y*/ - int (m_SCALE_Y /** m_SizeTotal.cy*/ * d) + (int)m_yshift;
}
int CGraph::MapToLogYPrint (double d)
{
	return /*(int)m_Center.y*/ - int (m_SCALE_Y /** m_Size.cy*/ * d) + (int)m_yshift * m_Size.cy / m_SizeTotal.cy;
}
#endif
void CGraph::Draw (HDC hDC, TData& DataX, TData& DataY, RECT& r, int iFirst, int iLast,
#ifdef EXTERN_FONTS_AND_PENS
	HPEN& boxPen, HPEN& gridPen, HPEN& linePen, HFONT& hFont, HFONT& hTitleFont, HFONT& hPrintFont, HFONT& hPrintTitleFont, 
#endif
	short toScaleX, bool toScaleY, bool isVisible)
{
WriteRaporto("Draw 1\n");
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if (m_vPoints.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_vPoints.GetCurrentMsg().toDraw)
			{
				if (m_vPoints.GetCurrentMsg().px->m_length != m_vPoints.GetCurrentMsg().py->m_length)
				{
					char errstr[200];
					wsprintf(errstr, "Error using CGraph::Draw()\n Number of line = %i\n px -> m_length (%i) != py -> m_length (%i)\n",
						m_vPoints.GetCurrentMsgIndex(), m_vPoints.GetCurrentMsg().px->m_length, m_vPoints.GetCurrentMsg().py->m_length);
#ifdef DO_RAPORT
	WriteRaporto(errstr);
#endif
					MessageBox(NULL,errstr,"CGraph::Draw",MB_OK);
					return;
					// AfxThrowUserException();
				}
			}
		}
		while(m_vPoints.IncrementCurrentMsg());
	}
#else
	for (int n = 0; n < m_vpPoints.Size(); n++)
	{
		if ((m_vpPoints.data+n)->toDraw)
		{
			if ((m_vpPoints.data+n)->px->m_length != (m_vpPoints.data+n)->py->m_length)
			{
#ifdef DO_RAPORT
				char errstr[200];
				wsprintf(errstr, "Error using CGraph::Draw()\n Number of line = %i\n px -> m_length (%i) != py -> m_length (%i)\n",
					n, (m_vpPoints.data+n)->px -> m_length, (m_vpPoints.data+n)->py -> m_length);
WriteRaporto(errstr);
#endif
				MessageBox(NULL,errstr,"CGraph::Draw",MB_OK);
				return;
				// AfxThrowUserException();
			}
		}
	}
#endif
WriteRaporto("Draw 1 1\n");
/*char ss[60];
sprintf(ss,
		"iFirst = %d iLast = %d iFirst + iLast = %d\n ",
		iFirst, iLast, iFirst + iLast);
WriteRaporto(ss);*/
#ifndef EXTERN_FONTS_AND_PENS

//char ss[16];
//sprintf(ss,"%d",GetMapMode(hDC));
//MessageBox(0,ss,"",0);
	// MM_TEXT;1;
 //   SetMapMode(hDC, MM_TEXT);

	HPEN boxPen;
	HPEN gridPen;
	HPEN linePen;
	HFONT hFont;
	HFONT hTitleFont;
	HFONT hYLabelFont;

	HFONT hPrintFont;
	HFONT hPrintTitleFont;
	HFONT hPrintYLabelFont;

		//======= Создаем шрифт для оцифровки осей
	hFont = CreateFont(12,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");
	//======= Создаем шрифт для оцифровки осей
	hPrintFont = CreateFont(72,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS,CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Arial");

	//======= Создаем шрифт для вывода заголовка
	hTitleFont = CreateFont(14,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	//======= Создаем шрифт для вывода заголовка
	hPrintTitleFont = CreateFont(150,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");

	//======= Создаем шрифт для вывода заголовка
	hYLabelFont = CreateFont(12,0,900,900,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");
	//======= Создаем шрифт для вывода заголовка
	hPrintYLabelFont = CreateFont(100,0,900,900,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");

	//====== Создаем черное перо для изображения рамки
	boxPen = CreatePen(PS_SOLID, 0, COLORREF(0));
	gridPen = CreatePen(PS_SOLID, 0, RGB(92,200,178));
	linePen = CreatePen(PS_SOLID, 2, RGB(255,100,0));
#endif

	//====== С помощью контекста устройства
	//====== узнаем адрес окна, его использующего
//	tagRECT r;
WriteRaporto("Draw 2\n");
	
	bool isPrint = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASPRINTER;
	bool isMeta = GetDeviceCaps(hDC, TECHNOLOGY) == DT_METAFILE;
	bool isWnd = GetDeviceCaps(hDC, TECHNOLOGY) == DT_RASDISPLAY;
WriteRaporto("Draw 3\n");
	
	if (isPrint)
	{
		r.left = 0;
		r.top = 0;
		r.right = r.left + GetDeviceCaps(hDC, HORZRES);
		r.bottom = r.top + GetDeviceCaps(hDC, VERTRES);
	}
//WriteRaporto("Draw 4\n");

	//====== Уточняем размеры окна
	m_Size.cx = r.right - r.left;
	m_Size.cy = r.bottom - r.top;
WriteRaporto("Draw 5\n");

	if(!isPrint)
	{
		m_Center.x = m_Size.cx/2;
		m_Center.y = m_SizeTotal.cy/2;
	}
	else
	{
		m_Center.x = m_Size.cx/2;
		m_Center.y = m_Size.cy/2;
	}
//WriteRaporto("Draw 6\n");
	if (toScaleX==1)
	{
		// Атрибуты координатных осей используем готовые с предыдущего графика
		m_DataX = DataX;
	}
	if (toScaleX==2)
	{
		//====== Вычисляем атрибуты координатных осей
#if 1
		m_DataX.Min = DataX.Min;
		m_DataX.Max = DataX.Max;
		Scale(m_DataX, iFirst, iLast, true);
#else
		Scale(m_DataX, iFirst, iLast);
#endif
//		DataX = m_DataX;
	}
	if (toScaleX==0)
	{
		//====== Вычисляем атрибуты координатных осей
		Scale(m_DataX, iFirst, iLast);
		DataX = m_DataX;
	}
	if (toScaleX==3)
	{
		//====== Вычисляем атрибуты координатных осей
		Scale(m_DataX, iFirst, iLast);
	}
	if (toScaleY)
	{
		//====== Вычисляем атрибуты координатных осей
		Scale(m_DataY, iFirst, iLast);
		// Если вычисленный интервал находится внутри такового с предыдущего графика
		if (m_DataY.Max < DataY.Max && m_DataY.Min > DataY.Min)
		//if (m_DataY.End < DataY.End && m_DataY.Start > DataY.Start)
			// Атрибуты координатных осей используем готовые с предыдущего графика
			m_DataY = DataY;
	}
	else
	{
		//====== Вычисляем атрибуты координатных осей
		Scale(m_DataY, iFirst, iLast);
		DataY = m_DataY;
	}
WriteRaporto("Draw 13\n");
	if (!isVisible){
WriteRaporto("Draw 13 !isVisible return\n");
		return;
	}
//	if(!isPrint && !(m_yshift>0 && m_yshift<r.bottom))
//		return;

//	int nDC = SaveDC(hDC);

	//====== Преобразуем координаты рамки
	int lt = MapToLogX(-0.5),
		rt = MapToLogX(0.5),
		tp = isPrint ? MapToLogYPrint(0.5) : MapToLogY(0.5),
		bm = isPrint ? MapToLogYPrint(-0.5) : MapToLogY(-0.5);
WriteRaporto("Draw 7\n");

//	if ( (tp + bm) / 2  < r.top || (tp + bm) / 2 > r.bottom)
//		return;

	
			
	SelectObject(hDC, boxPen);

WriteRaporto("Draw 8\n");

	//if(!
		Rectangle (hDC, lt, tp, rt, bm)//)
		//ErrorExit("Rectangle", false)
		;

WriteRaporto("Draw 9\n");

	//====== Задаем цвет и выравнивание текста
	//if(CLR_INVALID == 
		SetTextColor(hDC, 0)//)
		//ErrorExit("SetTextColor", false)
		;
	//if(GDI_ERROR == 
		SetTextAlign(hDC, TA_LEFT | TA_BASELINE)//)
		//ErrorExit("SetTextAlign", false)
		;
WriteRaporto("Draw 10\n");
	
WriteRaporto("Draw 11\n");
	//====== Выбираем шрифт
	if(!isPrint)
		SelectObject (hDC, hFont);
	else
		SelectObject (hDC, hPrintFont);

	TEXTMETRIC tm;
	GetTextMetrics(hDC, &tm); 
	m_LH = tm.tmHeight;

WriteRaporto("Draw 12\n");


	//====== Выводим экстремумы функции	
	char str[32];
	wsprintf(str,"Min = %c%d.%d\0",
	 m_DataY.Min<0.0?'-':' ', 
	 int(fabs(m_DataY.Min)), 
	 int(pow(10.,3)*(fabs(m_DataY.Min)-double(int(fabs(m_DataY.Min)))))
	 );
WriteRaporto("Draw 14\n");

	//if(!
		TextOut(hDC, rt+m_LH, tp+m_LH, str, strlen(str))//)
		//ErrorExit("TextOut",false)
		;
WriteRaporto("Draw 15\n");

	wsprintf(str,"Max = %c%d.%d\0",
	 m_DataY.Max<0.0?'-':' ', 
	 int(fabs(m_DataY.Max)), 
	 int(pow(10.,3)*(fabs(m_DataY.Max)-double(int(fabs(m_DataY.Max)))))
	);
WriteRaporto("Draw 16\n");

	//if(!
		TextOut(hDC, rt+m_LH, tp+m_LH+m_LH, str, strlen(str))//)
		//ErrorExit("TextOut", false)
		;

WriteRaporto("Draw 17\n");
		
	//====== Готовимся изображать координатную сетку
	SelectObject(hDC, gridPen);

	//if(GDI_ERROR == 
		SetTextAlign(hDC, TA_CENTER | TA_BASELINE)//)
		//ErrorExit("SetTextAlign", false)
		;

WriteRaporto("Draw 18\n");
	if (! m_vPoints.GetFirstMsg().bTimeScale )
	{
		//====== Рисуем вертикальные линии сетки
		for (double x = m_DataX.Start;  
				x < m_DataX.End - m_DataX.Step/2.;
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
			MakeLabel(true,x, str);

			//if(!
				TextOut(hDC, xi, bm+m_LH, str,strlen(str))//)
				//ErrorExit("TextOut", false)
				;
		}
	}
	else
	{

#ifdef DO_RAPORT
WriteRaporto("Draw 19\n");
char errstr[200];
sprintf(errstr, "m_DataX.Start = %f\nm_DataX.End = %f\nm_DataX.Step = %f\n",
		m_DataX.Start,m_DataX.End,m_DataX.Step);
WriteRaporto(errstr);
#endif

		//====== Рисуем вертикальные линии сетки
		for (double x = m_DataX.Start;  
				x < m_DataX.End - m_DataX.Step/2.;
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
			MakeTimeLabel(x, str);

			//if(!
				TextOut(hDC, xi, bm+m_LH, str,strlen(str))//)
				//ErrorExit("TextOut", false)
				;
		}
	}
WriteRaporto("Draw 19 2\n");

	//===== Повторяем цикл для горизонтальных линий сетки
	//if(GDI_ERROR == 
		SetTextAlign(hDC, TA_RIGHT | TA_BASELINE)//)
		//ErrorExit("SetTextAlign", false)
		;
	for (double y = m_DataY.Start;
			y < m_DataY.End - m_DataY.Step/2.;
			y += m_DataY.Step)
	{
		double yn = (y - m_DataY.Start) /
						(m_DataY.End - m_DataY.Start) - 0.5;

		int yi = isPrint ? MapToLogYPrint(yn) : MapToLogY(yn) ;
		if (y > m_DataY.Start && y < m_DataY.End)
		{
			MoveToEx(hDC, lt, yi, NULL);
			LineTo(hDC, rt, yi);
			MakeLabel(false, y, str);
			TextOut(hDC, lt-m_LH/2, yi, str, strlen(str));
		}
	}
WriteRaporto("Draw 20\n");


	//====== Выбираем шрифт
	if(!isPrint)
		SelectObject(hDC, hYLabelFont);
	else
		SelectObject(hDC, hPrintYLabelFont);

	//====== Вывод меток осей
	//if(!
		TextOut(hDC, lt-m_LH/2 - int(m_SCALE_X * double(m_Size.cx) * 0.1), tp - m_LH, 
		m_vPoints.GetFirstMsg().szYLabel, strlen(m_vPoints.GetFirstMsg().szYLabel)
		)//)
		//ErrorExit("TextOut", false)
		;

	//====== Выбираем шрифт
	if(!isPrint)
		SelectObject(hDC, hFont);
	else
		SelectObject(hDC, hPrintFont);

	
	//if(GDI_ERROR == 
		SetTextAlign(hDC, TA_LEFT | TA_BASELINE)//)
		//ErrorExit("SetTextAlign", false)
		;
	//if(!
	TextOut(hDC, rt-m_LH, bm + m_LH, 
		m_vPoints.GetFirstMsg().szXLabel, strlen(m_vPoints.GetFirstMsg().szXLabel))//)
		//m_sX, strlen(m_sX)))
		//ErrorExit("TextOut", false)
		;

WriteRaporto("Draw 21\n");

	//====== Вывод заголовка
//	if (m_sTitle.GetLength() > 40)
//		m_sTitle.Left(40);

WriteRaporto("Draw 22\n");

	//====== Выбираем шрифт
	if(!isPrint)
		SelectObject(hDC, hTitleFont);
	else
		SelectObject(hDC, hPrintTitleFont);
WriteRaporto("Draw 22 1\n");


	//if(GDI_ERROR == 
		SetTextAlign(hDC, TA_CENTER | TA_BASELINE)//)
		//ErrorExit("SetTextAlign", false)
		;


		TextOut(hDC, (lt+rt)/2, tp - m_LH,
			m_vPoints.GetFirstMsg().szTitle, strlen(m_vPoints.GetFirstMsg().szTitle));
WriteRaporto("Draw 22 16\n");


	
	//====== Вывод линии графика
	DrawLine(hDC, iFirst, iLast, linePen,  isPrint);

	
#ifndef EXTERN_FONTS_AND_PENS

	if(linePen) 
		DeleteObject(linePen);
	if(boxPen) 
		DeleteObject(boxPen);
	if(gridPen) 
		DeleteObject(gridPen);
	if(hTitleFont) 
		DeleteObject(hTitleFont);
	if(hFont) 
		DeleteObject(hFont);
	if(hPrintTitleFont) 
		DeleteObject(hPrintTitleFont);
	if(hPrintFont) 
		DeleteObject(hPrintFont);
#endif

WriteRaporto("Draw end\n");
}
#ifndef DRAW_OLD_VECTOR_VDPOINTS
void CGraph::DrawLine(HDC hDC, int iFirst, int iLast, HPEN& linePen, bool isPrint)
{
	int iline = 0;
WriteRaporto("DrawLine 1\n");
	int logx, logy;
	if (m_vPoints.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_vPoints.GetCurrentMsg().toDraw)
			{
				iline++;
				//====== Уничтожаем старое перо
				//====== Создаем новое

				if (iline > 1)
				{
					DeleteObject(linePen);
					COLORREF color;
					switch(iline)
					{
					case 2:
						color = RGB(0,100,0);
						break;
					case 3:
						color = RGB(0,0,100);
						break;
					case 4:
						color = RGB(100,100,0);
						break;
					case 5:
						color = RGB(0,100,100);
						break;
					case 6:
						color = RGB(100,0,100);
						break;
					default:
						color = RGB(100,100,100);
						break;
					}


					linePen = CreatePen(PS_SOLID, 1, color);

				}
				SelectObject(hDC, linePen);

				double	x0 = m_DataX.dStart,
						y0 = m_DataY.dStart,
						dx = m_DataX.dEnd - x0,
						dy = m_DataY.dEnd - y0;

				int i=0;
				double Ax, Bx, Ay, By;

				Ax = m_SCALE_X*m_Size.cx/dx;
				Bx = m_Center.x - m_SCALE_X*m_Size.cx*(x0/dx+.5);

				if (isPrint)
				{
#if 0
					Ay = m_SCALE_Y/**m_Size.cy*//dy;
					By = /*m_Center.y +*/ m_SCALE_Y/**m_Size.cy*/*(y0/dy+.5);
#else
					Ay = m_SCALE_Y * m_Size.cy / m_SizeTotal.cy/dy;
					By = /*m_Center.y +*/ m_SCALE_Y * m_Size.cy / m_SizeTotal.cy*(y0/dy+.5);
#endif
					By += m_yshift * m_Size.cy / m_SizeTotal.cy;
					//By += isPrint ? m_yshift * m_Size.cy / m_SizeTotal.cy : m_yshift;
				}
				else
				{
					Ay = m_SCALE_Y/**m_SizeTotal.cy*//dy;
					By = /*m_Center.y +*/ m_SCALE_Y/**m_SizeTotal.cy*/*(y0/dy+.5);
					By += m_yshift;
					//By += isPrint ? m_yshift * m_Size.cy / m_SizeTotal.cy : m_yshift;
				}

				//====== Нормируем координаты
	#ifndef DRAW_LINE_SIMPLE_LINEAR
				double	x = (*(m_vPoints.GetCurrentMsg().px->pD+i) - x0) / dx - .5,
						y = (*(m_vPoints.GetCurrentMsg().py->pD+i) - y0) / dy - .5;

				int logx = MapToLogX(x);
				int logy = isPrint ? MapToLogYPrint(y) : MapToLogY(y);
	#else
				logx = int(*(m_vPoints.GetCurrentMsg().px->pD+i) * Ax + Bx); 
				logy = int(By - *(m_vPoints.GetCurrentMsg().py->pD+i) * Ay); 
				//logy0= int(By - (0) * Ay); 
	#endif
				double xx;

				//====== Переход к оконным координатам
				//====== Если точка первая, то ставим перо

				bool firstPoint = true;

				int len = m_vPoints.GetCurrentMsg().px->Length();

				
				for (i=0;  i < len;  i++)
				{
					xx = *(m_vPoints.GetCurrentMsg().px->pD+i);
					if ( xx >= m_DataX.dStart
						&& xx <= m_DataX.dEnd)
					{
						//====== Нормируем координаты

		#ifndef DRAW_LINE_SIMPLE_LINEAR
						//====== Нормируем координаты
						//x = (*((m_vpPoints.data+n)->px->pD+i) - x0) / dx - .5;
						x = ( xx - x0) / dx - .5;
						y = (*(m_vPoints.GetCurrentMsg().py->pD+i) - y0) / dy - .5;

						logx = MapToLogX(x);
						logy = isPrint ? MapToLogYPrint(y) : MapToLogY(y);
		#else
						//logx = int(*((m_vpPoints.data+n)->px->pD+i) * Ax + Bx); 
						logx = int( xx * Ax + Bx); 
						logy = int(By - *(m_vPoints.GetCurrentMsg().py->pD+i) * Ay); 
		#endif

						//====== Переход к оконным координатам
						//====== Если точка первая, то ставим перо
						if(m_vPoints.GetCurrentMsg().notGist)
						{
							if(firstPoint)
							{
								MoveToEx(hDC,logx,logy,NULL);
								firstPoint = false;
							}
							else
								LineTo(hDC, logx, logy);
						}
						else
						{
							MoveToEx(hDC, logx, int(By), NULL);
							LineTo(hDC, logx, logy);
						}
					}
				}
				char str[256];
				sprintf(str,"len = %d\0", len);
				TextOut(hDC, logx+50, logy, str, strlen(str));
			}
		}
		while(m_vPoints.IncrementCurrentMsg());
	}
WriteRaporto("DrawLine end\n");
}
#else
void CGraph::DrawLine(HDC hDC, int iFirst, int iLast, HPEN& linePen, bool isPrint)
{
WriteRaporto("DrawLine 1\n");
	int logx, logy;
	for(int n = 0; n <  m_vpPoints.Size(); n++)
	{
		if ((m_vpPoints.data+n)->toDraw)
		{
			//====== Уничтожаем старое перо
			//====== Создаем новое

			SelectObject(hDC, linePen);

			double	x0 = m_DataX.dStart,
					y0 = m_DataY.dStart,
					dx = m_DataX.dEnd - x0,
					dy = m_DataY.dEnd - y0;

			int i=0;
			double Ax, Bx, Ay, By;

			Ax = m_SCALE_X*m_Size.cx/dx;
			Bx = m_Center.x - m_SCALE_X*m_Size.cx*(x0/dx+.5);

			if (isPrint)
			{
				Ay = m_SCALE_Y/**m_Size.cy*//dy;
				By = /*m_Center.y +*/ m_SCALE_Y/**m_Size.cy*/*(y0/dy+.5);
				By += m_yshift * m_Size.cy / m_SizeTotal.cy;
				//By += isPrint ? m_yshift * m_Size.cy / m_SizeTotal.cy : m_yshift;
			}
			else
			{
				Ay = m_SCALE_Y/**m_SizeTotal.cy*//dy;
				By = /*m_Center.y +*/ m_SCALE_Y/**m_SizeTotal.cy*/*(y0/dy+.5);
				By += m_yshift;
				//By += isPrint ? m_yshift * m_Size.cy / m_SizeTotal.cy : m_yshift;
			}

			//====== Нормируем координаты
#ifndef DRAW_LINE_SIMPLE_LINEAR
			double	x = (*((m_vpPoints.data+n)->px->pD+i) - x0) / dx - .5,
					y = (*((m_vpPoints.data+n)->py->pD+i) - y0) / dy - .5;

			int logx = MapToLogX(x);
			int logy = isPrint ? MapToLogYPrint(y) : MapToLogY(y);
#else
			logx = int(*((m_vpPoints.data+n)->px->pD+i) * Ax + Bx); 
			logy = int(By - *((m_vpPoints.data+n)->py->pD+i) * Ay); 
			//logy0= int(By - (0) * Ay); 
#endif
			double xx;

			//====== Переход к оконным координатам
			//====== Если точка первая, то ставим перо

			bool firstPoint = true;

			
			for (i=0;  i < (m_vpPoints.data+n)->px->Length();  i++)
			{
				xx = *((m_vpPoints.data+n)->px->pD+i);
				if ( xx >= m_DataX.dStart
					&& xx <= m_DataX.dEnd)
				{
					//====== Нормируем координаты

	#ifndef DRAW_LINE_SIMPLE_LINEAR
					//====== Нормируем координаты
					//x = (*((m_vpPoints.data+n)->px->pD+i) - x0) / dx - .5;
					x = ( xx - x0) / dx - .5;
					y = (*((m_vpPoints.data+n)->py->pD+i) - y0) / dy - .5;

					logx = MapToLogX(x);
					logy = isPrint ? MapToLogYPrint(y) : MapToLogY(y);
	#else
					//logx = int(*((m_vpPoints.data+n)->px->pD+i) * Ax + Bx); 
					logx = int( xx * Ax + Bx); 
					logy = int(By - *((m_vpPoints.data+n)->py->pD+i) * Ay); 
	#endif

					//====== Переход к оконным координатам
					//====== Если точка первая, то ставим перо
					if((m_vpPoints.data+n)->notGist)
					{
						if(firstPoint)
						{
							MoveToEx(hDC,logx,logy,NULL);
							firstPoint = false;
						}
						else
							LineTo(hDC, logx, logy);
					}
					else
					{
						MoveToEx(hDC, logx, int(By), NULL);
						LineTo(hDC, logx, logy);
					}
				}
			}
		}
	}
WriteRaporto("DrawLine end\n");
}
#endif



void CGraph::MakeLabel(bool bX, double& v, char* s)
{
//WriteRaporto("MakeLabel\n");
/*	wsprintf(s, "0.0\0");
	if (v == 0.)
		return;
*/
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
		wsprintf(s,"%c%d\0",
			 v<0.0?'-':' ', 
			 int(fabs(v)) 
			);
	}
	else
	{
		wsprintf(s,"%c%d.%d\0",
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
		char add[32];
		wsprintf (add, "·e%d\0",iPower);
		strcat(s, add);
	}
//WriteRaporto("MakeLabel end\n");
}

void CGraph::MakeTimeLabel(double& t, char * s)
{
//	static int j = 0;
WriteRaporto("MakeTimeLabel\n");
	int h, mi, sec, y, d, mo, milli;
	if (m_DataX.Step < 0.5)
	{

		numdate(t, h, mi, sec, milli);
		if (milli > 499)
			numdate(t+1./86400.0/2., h, mi, sec, milli);

		wsprintf(s,"%d:%d:%d\0",
			 h, 
			 mi, 
			 sec
			);
	}
	else
	{
		if (m_DataX.Step == 0.5)
		{
			datevec(t,y, mo, d, h, mi, sec, milli);
			wsprintf(s,"%d %d:%d:%d\0",
				 d,h, 
				 mi, 
				 sec
				);
		}
		if (m_DataX.Step > 0.5 && m_DataX.Step < 7 )
		{
			datevec(t,y, mo, d, h, mi, sec, milli);
			wsprintf(s,"%d\0",
				 d
				);
		}
		if (m_DataX.Step >= 7 )
		{
			datevec(t,y, mo, d, h, mi, sec, milli);
	//		if(j%2 == 0)
			wsprintf(s,"%d.%02d\0",
				 d, mo
				);
	/*		else
				wsprintf(s,"%d\0",
					 y
					);
			j++;*/
		}

	}
WriteRaporto("MakeTimeLabel end\n");
}
