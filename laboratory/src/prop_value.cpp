#include "stdafx.h"
#include "float.h"
#include "prop_value.h"

double StatZondData1::GetPCK()
{
	return this->pStatZond->data2.Kg * this->q0 + pStatZond->data2.Bg;
}
double StatZondData1::GetPCB()
{
	return this->pStatZond->data2.Kf * this->f0 + pStatZond->data2.Bf;
}			
double StatZondData1::GetQs()
{
	return this->pStatZond->data2.Kf * this->f0 + pStatZond->data2.Bf;
}			

bool StatZond::GetQs(double h, double & Qs)
{
	if (this->data1.size() && h >= 0.0)
	{
		double min_h = (*this->data1.begin()).h;
		if (h < min_h)
		{
			double mu = h / min_h;
			double Qs_min_h = (*this->data1.begin()).GetQs();
			Qs = mu * Qs_min_h;
			return true;
		}
		else
		{
			for (vector<StatZondData1>::iterator it = this->data1.begin();
				(it+1) != this->data1.end(); it++)
			{		
				double h_0 = (*it).h;
				double h_1 = (*(it+1)).h;

				double Qs_0 = (*it).GetQs();		
				double Qs_1 = (*(it+1)).GetQs();

				if (h >= h_0 && h <= h_1)
				{
					double mu = (h - h_0) / (h_1 - h_0);
					Qs = Qs_0 + mu * (Qs_1 - Qs_0);
					return true;
				}									
			}
		}
	}
	return false;
}