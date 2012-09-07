
#include <dime/util/Linear.h>

#include "../stdafx.h"
#include "../points.h"
#include "dimevec3f2cpoint3.h"

void dimevec3f2cpoint3(dimeVec3f& v, CPoint3& pt)
{
	pt.bVisible = true;
	pt.x = v.x;
	pt.y = v.y;
	pt.z = v.z;
	pt.flag = 0;
}
