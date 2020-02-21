#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

#include <vector>
using namespace std;

struct COORDINATES
{
	double x,y,z;
};
struct COORDINATES4
{
	double x,y,z,v;
};
struct cut_of_line
{
	int i_start;
	int i_finish;
};

struct index_for_sort
{
	int i;
	double sort_val;
};


int compare_index_for_sort_decrease( const void *arg1, const void *arg2 );
int compare_index_for_sort( const void *arg1, const void *arg2 );

int compare_X( const void *arg1, const void *arg2 );
int compare_Y( const void *arg1, const void *arg2 );

int compare4_X( const void *arg1, const void *arg2 );
int compare4_Y( const void *arg1, const void *arg2 );
int compare4_Z( const void *arg1, const void *arg2 );

int compare_int( const void *arg1, const void *arg2 );
void randpermute(int n, vector<int>& result);
double Rand(double x);
double Rand(double minBorder, double maxBorder);
int Scale(int len, double* v);
int Scale(vector<double>& v);
int Center_And_Scale(vector<double>& v);


#endif
