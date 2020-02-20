#pragma once
#ifndef __COMMON_OG_H__
#define __COMMON_OG_H__

#include <GL/gl.h>
#include <GL/glu.h>

#include "surfdefs.h" //for define OG_DOUBLE_PRECISION

#if OG_DOUBLE_PRECISION 
#define GL_PRECISION GL_DOUBLE
#else // float precision
#define GL_PRECISION GL_FLOAT
#endif /*OG_DOUBLE_PRECISION*/

#if OG_DOUBLE_PRECISION 
#define Line3(x1,y1,z1,x2,y2,z2)		\
	glBegin(GL_LINES);				\
		glVertex3d ((x1),(y1),(z1));		\
		glVertex3d ((x2),(y2),(z2));		\
	glEnd();
#else // float precision
#define Line3(x1,y1,z1,x2,y2,z2)		\
	glBegin(GL_LINES);				\
		glVertex3f ((x1),(y1),(z1));		\
		glVertex3f ((x2),(y2),(z2));		\
	glEnd();
#endif /*OG_DOUBLE_PRECISION*/

#endif
