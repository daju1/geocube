//coordinates.h
#ifndef COORDINATES_H_INCLUDED
#define COORDINATES_H_INCLUDED
struct COORDINATES
{
	double x,y,z;
};
int compare_X( const void *arg1, const void *arg2 );
int compare_Y( const void *arg1, const void *arg2 );
#endif