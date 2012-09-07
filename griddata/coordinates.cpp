#include "stdafx.h"
#include "coordinates.h"

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
