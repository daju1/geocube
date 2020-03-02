//korrelation.cpp
#include "StdAfx.h"
#include "korrelation.h"
double korr_koeff(int wlen, double *w0, double *w1)
{
	// начинаем расчЄт коррел¤ционного коэффициента											
	//
	// вычисл¤ем матожидание в каждом из окон
	double m_0 = 0.0, m_1 = 0.0;
	//int n_0 = 0, n_1 = 0;
	for (int w = 0; w < wlen; w++)
	{	
		m_0 += w0[w];		
		m_1 += w1[w];		
	}
	m_0 /= wlen;
	m_1 /= wlen;

	// вычисл¤ем дисперсию и среднеквадратичное отклонение в каждом из окон
	double D_0 = 0.0, D_1 = 0.0;										
	for (int w = 0; w < wlen; w++)
	{
		D_0 += (w0[w]-m_0)*(w0[w]-m_0);                                            
		D_1 += (w1[w]-m_1)*(w1[w]-m_1);
	}
	D_0 /= wlen;
	D_1 /= wlen;

	double sigma_0 = sqrt(D_0);
	double sigma_1 = sqrt(D_1);
	// рассчитываем коррел¤ционный коэффициент
	double K_0_1 = 0.0;
	for (int w = 0; w < wlen; w++)
	{
		K_0_1 += (w0[w]-m_0)*(w1[w]-m_1);
	}
	K_0_1 /= wlen;
	double k_0_1 = K_0_1 / (sigma_0*sigma_1);
	return k_0_1;
}