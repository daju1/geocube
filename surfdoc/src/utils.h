#ifndef __UTILS_H__
#define __UTILS_H__
//***********************************************************//
// Demo:    PickObject Demo
// Author:  terror
//***********************************************************//
#pragma once
#include <stdlib.h>
#define  NEW_ARRAY_MEM(a,t,c)	{a = NULL; a = new t[c]; memset(a,0,sizeof(t));}
#define  DELETE_ARRAY_MEM(x)	{if (x != NULL) delete []x; x = NULL;}
#define  RND                  ((float)rand()*(1.0f /(float)RAND_MAX))
typedef unsigned int     uint;
typedef unsigned char    byte;
typedef unsigned short   ushort;
typedef unsigned __int64 uint64;
typedef unsigned long    dword;
struct vector3ub
{
	byte v[3];
};
#endif
