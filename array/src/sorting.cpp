#include "stdafx.h"
#include "sorting.h"
#include <math.h>
int compare_index_for_sort_decrease( const void *arg1, const void *arg2 )
{
   /* Compare Y: */
   double 
	   v1 = (( index_for_sort* ) arg1)->sort_val,
	   v2 = (( index_for_sort* ) arg2)->sort_val;
   if (v1 < v2)
	   return +1;
   if (v1 > v2)
	   return -1;
   return 0;
}

int compare_index_for_sort( const void *arg1, const void *arg2 )
{
   /* Compare Y: */
   double 
	   v1 = (( index_for_sort* ) arg1)->sort_val,
	   v2 = (( index_for_sort* ) arg2)->sort_val;
   if (v1 < v2)
	   return -1;
   if (v1 > v2)
	   return +1;
   return 0;
}
int compare_X( const void *arg1, const void *arg2 )
{
   /* Compare X: */
   double 
	   x1 = (( COORDINATES* ) arg1)->x,
	   x2 = (( COORDINATES* ) arg2)->x;
   if (x1 < x2)
	   return -1;
   if (x1 == x2)
	   return 0;
   if (x1 > x2)
	   return 1;
   return 0;
}
int compare_Y( const void *arg1, const void *arg2 )
{
   /* Compare Y: */
   double 
	   y1 = (( COORDINATES* ) arg1)->y,
	   y2 = (( COORDINATES* ) arg2)->y;
  
   if (y1 < y2)
	   return -1;
   if (y1 == y2)
	   return 0;
   if (y1 > y2)
	   return 1;
   return 0;
}




int compare4_X( const void *arg1, const void *arg2 )
{
   /* Compare X: */
   double 
	   x1 = (( COORDINATES4* ) arg1)->x,
	   x2 = (( COORDINATES4* ) arg2)->x;
   if (x1 < x2)
	   return -1;
   if (x1 == x2)
	   return 0;
   if (x1 > x2)
	   return 1;
   return 0;
}
int compare4_Y( const void *arg1, const void *arg2 )
{
   /* Compare Y: */
   double 
	   y1 = (( COORDINATES4* ) arg1)->y,
	   y2 = (( COORDINATES4* ) arg2)->y;
  
   if (y1 < y2)
	   return -1;
   if (y1 == y2)
	   return 0;
   if (y1 > y2)
	   return 1;
   return 0;
}



int compare4_Z( const void *arg1, const void *arg2 )
{
   /* Compare Z: */
   double 
	   z1 = (( COORDINATES4* ) arg1)->z,
	   z2 = (( COORDINATES4* ) arg2)->z;
  
   if (z1 < z2)
	   return -1;
   if (z1 == z2)
	   return 0;
   if (z1 > z2)
	   return 1;
   return 0;
}



int compare_int( const void *arg1, const void *arg2 )
{
   /* Compare Y: */
   int 
	   i1 = *(( int* ) arg1),
	   i2 = *(( int* ) arg2);
  
   if (i1 < i2)
	   return -1;
   if (i1 > i2)
	   return 1;
   if (i1 == i2)
	   return 0;
   return 0;
}


/*
int __cdecl compare_YX( const void *arg1, const void *arg2 )
{
   // Compare Y: 
   double 
	   y1 = (( COORDINATES* ) arg1)->y,
	   y2 = (( COORDINATES* ) arg2)->y;
   double 
	   x1 = (( COORDINATES* ) arg1)->x,
	   x2 = (( COORDINATES* ) arg2)->x;
   
   if (y1 < y2)
	   return -1;
   if (y1 == y2)
	   return 0;
   if (y1 > y2)
	   return 1;
   return 0;
}*/
//extern struct COORDINATES;
int Scale(int len, double* v)
{
	double d = 0.0;
	int i;
	for (i = 0; i < len; i++)
	{
		d += v[i]*v[i];
	}
	d = sqrt(d);
	//=========================
	if (d == 0.0)
	{
		//MessageBox(0,"Zero length vector","Scale(double v[3])",0);
		return -1;
	}
	//=========================
	for (i = 0; i < len; i++)
	{
		v[i] /= d;
	}
	return 0;
}
int Scale(vector<double>& v)
{
	int i, len = v.size();
	double d = 0.0;
	for (i = 0; i < len; i++)
	{
		d += v[i]*v[i];
	}
	d = sqrt(d);
	//=========================
	if (d == 0.0)
	{
		//MessageBox(0,"Zero length vector","Scale(double v[3])",0);
		return -1;
	}
	//=========================
	for (i = 0; i < len; i++)
	{
		v[i] /= d;
	}
	return 0;
}
int Center_And_Scale(vector<double>& v)
{
	int i, len = v.size();
	if (len == 0)
	{
		return -1;
	}

	double m = 0.0;
	for (i = 0; i < len; i++)
	{
		m += v[i];
	}
	m /= len;

	for (i = 0; i < len; i++)
	{
		v[i] -= 0;
	}

	double d = 0.0;
	for (i = 0; i < len; i++)
	{
		d += v[i]*v[i];
	}
	d = sqrt(d);
	//=========================
	if (d == 0.0)
	{
		//MessageBox(0,"Zero length vector","Scale(double v[3])",0);
		return -1;
	}
	//=========================
	for (i = 0; i < len; i++)
	{
		v[i] /= d;
	}
	return 0;
}
double Rand(double minBorder, double maxBorder)
{
	return minBorder + (((double)rand()) / RAND_MAX) * (maxBorder - minBorder);
}
double Rand(double x)
{
	//====== Случайное число в диапазоне (-x, x)
	return x - (x + x) * rand() / RAND_MAX;
}
void randpermute(int n, vector<int>& result)
{
	index_for_sort * ifs = new index_for_sort[n];

	result.resize(n);
	int I;
	for ( I = 0; I < n; I++)
	{
		ifs[I].i		= I;
		ifs[I].sort_val	= (double)rand() / RAND_MAX;
	}					
	qsort( (void *)ifs, (size_t)n, sizeof(index_for_sort), compare_index_for_sort );
	for ( I = 0; I < n; I++)
	{
		result[I] = ifs[I].i;
	}
	delete[] ifs;
}

