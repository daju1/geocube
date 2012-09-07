#include "stdafx.h"
#include "../array/src/Vector.h"
#include "../array/src/vdouble.h"

int ReadInputFile(char * fname, vdouble& x, vdouble& y);
int GetDelimiterFromID(int delimID);
int ReadInputFile(char * fname, Vector<vdouble>& vv, int delim);
