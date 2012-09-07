#include "StdAfx.h"
#include "DrawScene.h"
#include "SurfDoc.h"

#include "winsurftree.h"
extern void InitSphere(int nlist, int alpha);

void DrawCube(SurfDoc* pSurfDoc)
{
	char str[32], spower[32];
	// отриовка куба и осей
	glNewList(FIRST_HARD_LIST+1, GL_COMPILE);
	//====== Вычисляем атрибуты координатных осей
	pSurfDoc->Scale(pSurfDoc->m_DataX);
	pSurfDoc->Scale(pSurfDoc->m_DataY);
	pSurfDoc->Scale(pSurfDoc->m_DataZ);
	double min_xv, min_yv, min_zv, max_xv, max_yv, max_zv;
	double min_xd, min_yd, min_zd, max_xd, max_yd, max_zd;
	double step_xv, step_yv, step_zv;
#if LARGE_CUBE
	min_xd = pSurfDoc->m_DataX.dStart;
	min_yd = pSurfDoc->m_DataY.dStart;
	min_zd = pSurfDoc->m_DataZ.dStart;

	max_xd = pSurfDoc->m_DataX.dEnd;
	max_yd = pSurfDoc->m_DataY.dEnd;
	max_zd = pSurfDoc->m_DataZ.dEnd;
#else
	/*min_xd = pSurfDoc->m_DataX.Min;
	min_yd = pSurfDoc->m_DataY.Min;
	min_zd = pSurfDoc->m_DataZ.Min;

	max_xd = pSurfDoc->m_DataX.Max;
	max_yd = pSurfDoc->m_DataY.Max;
	max_zd = pSurfDoc->m_DataZ.Max;*/

	min_xd = pSurfDoc->m_xd_min;
	min_yd = pSurfDoc->m_yd_min;
	min_zd = pSurfDoc->m_zd_min;

	max_xd = pSurfDoc->m_xd_max;
	max_yd = pSurfDoc->m_yd_max;
	max_zd = pSurfDoc->m_zd_max;
#endif
		
	pSurfDoc->Document2ViewCoordinates(min_xd, min_yd, min_zd, min_xv, min_yv, min_zv);
	pSurfDoc->Document2ViewCoordinates(max_xd, max_yd, max_zd, max_xv, max_yv, max_zv);
	/*pSurfDoc->Document2ViewCoordinates(
		pSurfDoc->m_DataX.dStep, 
		pSurfDoc->m_DataY.dStep, 
		pSurfDoc->m_DataZ.dStep, 
		step_xv, step_yv, step_zv);*/

	step_xv = 1.0;
	step_yv = 1.0;
	step_zv = 1.0;
	
/*	min_xv = pSurfDoc->m_xv_min;
	min_yv = pSurfDoc->m_yv_min;
	min_zv = pSurfDoc->m_zv_min;

	max_xv = pSurfDoc->m_xv_max;
	max_yv = pSurfDoc->m_yv_max;
	max_zv = pSurfDoc->m_zv_max;*/
		
	glColor3f (0.0f, 0.0f, 0.0f);

	glEnable (GL_LINE_STIPPLE);
	//glLineStipple (1, 0x00FF);		// dash
	//glLineStipple (1, 0x1C47);		// dash/dot/dash
	//glLineStipple (1, 0x0101);		// dot
	//glLineStipple (1, 0x5555);		// dot
	glLineStipple (1, 0x1111);		// dot
	if (pSurfDoc->m_DataX.dStep > 0.0 && pSurfDoc->m_DataX.dEnd > pSurfDoc->m_DataX.dStart)
	//====== Рисуем вертикальные линии сетки
#if 1
	for (double x = pSurfDoc->m_DataX.dStart;  
				x <= pSurfDoc->m_DataX.dEnd/* - pSurfDoc->m_DataX.Step/2.*/;
			x += pSurfDoc->m_DataX.dStep)
#else
	for (double x = min_xd;  
			x <= max_xd/* - pSurfDoc->m_DataX.Step/2.*/;
			x += pSurfDoc->m_DataX.dStep)
#endif
	{
		//====== Нормируем координату x
		//double	xn = (x - m_DataX.Start) /
		//				(m_DataX.End - m_DataX.Start) - 0.5;

		//====== Вычисляем оконную координату
		double xv;	
		pSurfDoc->Document2ViewXCoordinates(x,xv);
		//====== Пропускаем крайние линии,
		//====== так как они совпатают с рамкой
#if LARGE_CUBE
		if (x > pSurfDoc->m_DataX.dStart && x < pSurfDoc->m_DataX.dEnd)
#else
		//if (x >= pSurfDoc->m_DataX.Min && x <= pSurfDoc->m_DataX.Max)
		if (x >= min_xd && x <= max_xd)
#endif
		{
			glColor3f (0.5f, 0.5f, 0.0f);
			Line3(xv, min_yv, min_zv, xv, max_yv, min_zv);
			//Line3d(xv, min_yv, max_zv, xv, max_yv, max_zv);
			//Line3d(xv, min_yv, min_zv, xv, min_yv, max_zv);
			Line3(xv, max_yv, min_zv, xv, max_yv, max_zv);
#if LARGE_CUBE
		}
#endif
		glColor3f (0.0f, 0.0f, 0.0f);			
		Line3(xv, min_yv, min_zv, xv, min_yv - step_yv / 4., min_zv - step_zv / 4.);
		//====== Наносим цифровую метку
		pSurfDoc->MakeLabel(0,x / pSurfDoc->m_DataX.Factor, str, spower);
		// move 
		glRasterPos3d(xv, min_yv - step_yv / 2., min_zv - step_zv / 2.); 
		// set up for a string-drawing display List call 
		// Display a string 
		glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
		// Draw the characters in a string 
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
		//if(!
			//TextOut(hDC, xi, bm+m_LH, str,strlen(str))//)
			//ErrorExit("TextOut", false)
			//;
#if !LARGE_CUBE
		}
#endif
	}

	//====== Наносим цифровую метку
	sprintf(str, "X %s", spower);
	// move 
	glRasterPos3d((max_xv+min_xv)/2., min_yv - step_yv, min_zv - step_zv ); 
	// set up for a string-drawing display List call 
	// Display a string 
	glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
	// Draw the characters in a string 
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 


	if (pSurfDoc->m_DataY.dStep > 0.0 && pSurfDoc->m_DataY.dEnd > pSurfDoc->m_DataY.dStart)
#if 1
	for (double y = pSurfDoc->m_DataY.dStart;  
			y <= pSurfDoc->m_DataY.dEnd/* - pSurfDoc->m_DataY.Step/2.*/;
			y += pSurfDoc->m_DataY.dStep)
#else
	for (double y = min_yd;  
			y <= max_yd/* - pSurfDoc->m_DataY.Step/2.*/;
			y += pSurfDoc->m_DataY.dStep)
#endif
	{
		//====== Нормируем координату y
		//double	xn = (x - m_DataX.Start) /
		//				(m_DataX.End - m_DataX.Start) - 0.5;

		//====== Вычисляем оконную координату
		double yv;	
		pSurfDoc->Document2ViewYCoordinates(y,yv);
		//====== Пропускаем крайние линии,
		//====== так как они совпатают с рамкой
#if LARGE_CUBE
		if (y > pSurfDoc->m_DataY.dStart && y < pSurfDoc->m_DataY.dEnd)
#else
		//if (y >= pSurfDoc->m_DataY.Min && y <= pSurfDoc->m_DataY.Max)
		if (y >= min_yd && y <= max_yd)
#endif
		{
			glColor3f (0.5f, 0.5f, 0.0f);
			Line3(min_xv, yv, min_zv, max_xv, yv, min_zv);
			//Line3d(min_xv, yv, max_zv, max_xv, yv, max_zv);
			//Line3d(min_xv, yv, min_zv, min_xv, yv, max_zv);
			Line3(max_xv, yv, min_zv, max_xv, yv, max_zv);
#if LARGE_CUBE
		}
#endif
		glColor3f (0.0f, 0.0f, 0.0f);
		Line3(min_xv, yv, min_zv, min_xv - step_xv / 4., yv, min_zv - step_zv / 4.);
		//====== Наносим цифровую метку
		pSurfDoc->MakeLabel(1, y / pSurfDoc->m_DataY.Factor, str, spower);
		// move 
		glRasterPos3d(min_xv - step_xv / 2., yv, min_zv - step_zv / 2.); 
		// set up for a string-drawing display List call 
		// Display a string 
		glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
		// Draw the characters in a string 
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
#if !LARGE_CUBE
		}
#endif
	}
	//====== Наносим цифровую метку
	sprintf(str, "Y %s", spower);
	// move 
	glRasterPos3d(min_xv - step_xv , (max_yv+min_yv)/2., min_zv - step_zv ); 
	// set up for a string-drawing display List call 
	// Display a string 
	glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
	// Draw the characters in a string 
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 

	if (pSurfDoc->m_DataZ.dStep > 0.0 && pSurfDoc->m_DataZ.dEnd > pSurfDoc->m_DataZ.dStart)
#if 1
	for (double z = pSurfDoc->m_DataZ.dStart;  
			z <= pSurfDoc->m_DataZ.dEnd/* - pSurfDoc->m_DataZ.Step/2.*/;
			z += pSurfDoc->m_DataZ.dStep)
#else
	for (double z = min_zd;  
			z <= max_zd/* - pSurfDoc->m_DataZ.Step/2.*/;
			z += pSurfDoc->m_DataZ.dStep)
#endif
	{
		//====== Нормируем координату x
		//double	xn = (x - m_DataX.Start) /
		//				(m_DataX.End - m_DataX.Start) - 0.5;

		//====== Вычисляем оконную координату
		double zv;	
		pSurfDoc->Document2ViewZCoordinates(z,zv);
		//====== Пропускаем крайние линии,
		//====== так как они совпатают с рамкой
#if LARGE_CUBE
		if (z > pSurfDoc->m_DataZ.dStart && z < pSurfDoc->m_DataZ.dEnd)
#else
		//if (z >= pSurfDoc->m_DataZ.Min && z <= pSurfDoc->m_DataZ.Max)
		if (z >= min_zd && z <= max_zd)
#endif
		{
			glColor3f (0.5f, 0.5f, 0.0f);
			//Line3d(min_xv, min_yv, zv, max_xv, min_yv, zv);
			Line3(min_xv, max_yv, zv, max_xv, max_yv, zv);
			//Line3d(min_xv, min_yv, zv, min_xv, max_yv, zv);
			Line3(max_xv, min_yv, zv, max_xv, max_yv, zv);
#if LARGE_CUBE
		}
#endif
		glColor3f (0.0f, 0.0f, 0.0f);			
		Line3(min_xv, max_yv, zv, min_xv - step_xv / 4., max_yv + step_yv / 4., zv);
		//====== Наносим цифровую метку
		pSurfDoc->MakeLabel(2,z / pSurfDoc->m_DataZ.Factor, str, spower);
		// move 
		glRasterPos3d(min_xv - step_xv / 2., max_yv + step_yv / 2., zv); 
		// set up for a string-drawing display List call 
		// Display a string 
		glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
		// Draw the characters in a string 
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
#if !LARGE_CUBE
		}
#endif
	}
	//====== Наносим цифровую метку
	sprintf(str, "Z %s", spower);
	// move 
	glRasterPos3d(min_xv - step_xv, max_yv + step_yv, (max_zv+min_zv)/2.); 
	// set up for a string-drawing display List call 
	// Display a string 
	glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
	// Draw the characters in a string 
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 

	glDisable (GL_LINE_STIPPLE);

/*		glBegin(GL_LINES);				
			glColor3f (1.f, 0.0f, 0.f);
		glEnd();

		Line3d(min_x, 0., 0., max_x, 0., 0.);
		Line3d(min_x, 0., 0., min_x, max_y, 0.);
		Line3d(min_x, 0., 0., min_x, 0., max_z);

		glBegin(GL_LINES);				
			glColor3f (0.f, 1.0f, 0.f);
		glEnd();
		Line3d(0., 0., 0., 1., 0., 0.);
		Line3d(0., 0., 0., 0., 1., 0.);
		Line3d(0., 0., 0., 0., 0., 1.);

		*/
/*
	glBegin(GL_POINTS);				
		glColor3f (0.9f, 0.0f, 0.f);
		glVertex3d (min_x,min_y,min_z);		
		glVertex3d (max_x,max_y,max_z);		
		glColor3f (1.0f, 1.0f, 1.f);
	glEnd();*/

				
	glColor3f (0.0f, 0.0f, 0.0f);
	Line3(min_xv, min_yv, min_zv, max_xv, min_yv, min_zv);
	Line3(min_xv, max_yv, min_zv, max_xv, max_yv, min_zv);
	Line3(min_xv, min_yv, min_zv, min_xv, max_yv, min_zv);
	Line3(max_xv, min_yv, min_zv, max_xv, max_yv, min_zv);

	//Line3d(min_xv, min_yv, max_zv, max_xv, min_yv, max_zv);
	Line3(min_xv, max_yv, max_zv, max_xv, max_yv, max_zv);
	//Line3d(min_xv, min_yv, max_zv, min_xv, max_yv, max_zv);
	Line3(max_xv, min_yv, max_zv, max_xv, max_yv, max_zv);

	//Line3d(min_xv, min_yv, min_zv, min_xv, min_yv, max_zv);
	Line3(min_xv, max_yv, min_zv, min_xv, max_yv, max_zv);
	Line3(max_xv, min_yv, min_zv, max_xv, min_yv, max_zv);
	Line3(max_xv, max_yv, min_zv, max_xv, max_yv, max_zv);
	
/*	double axis_len_x = (max_xd - min_xd);
	for 
*/	


	//====== Закрываем список команд OpenGL
	glEndList();
}

void DrawXYZCutPlanes(SurfDoc* pSurfDoc)
{
	glNewList(FIRST_HARD_LIST+3, GL_COMPILE);

	glBegin(GL_LINES);				
		glColor3f (1.f, 0.0f, 0.f);
	glEnd();

	double viewX,viewY,viewZ;
	double min_x, min_y, min_z, max_x, max_y, max_z;

	min_x = pSurfDoc->m_xv_min;
	min_y = pSurfDoc->m_yv_min;
	min_z = pSurfDoc->m_zv_min;

	max_x = pSurfDoc->m_xv_max;
	max_y = pSurfDoc->m_yv_max;
	max_z = pSurfDoc->m_zv_max;

	pSurfDoc->Document2ViewCoordinates(
		pSurfDoc->m_X, pSurfDoc->m_Y, pSurfDoc->m_Z, 
		viewX,viewY,viewZ);

	Line3(min_x, min_y, viewZ, max_x, min_y, viewZ);
	Line3(min_x, max_y, viewZ, max_x, max_y, viewZ);
	Line3(min_x, min_y, viewZ, min_x, max_y, viewZ);
	Line3(max_x, min_y, viewZ, max_x, max_y, viewZ);

	Line3(min_x, viewY, min_z, max_x, viewY, min_z);
	Line3(min_x, viewY, max_z, max_x, viewY, max_z);
	Line3(min_x, viewY, min_z, min_x, viewY, max_z);
	Line3(max_x, viewY, min_z, max_x, viewY, max_z);

	Line3(viewX, min_y, min_z, viewX, max_y, min_z);
	Line3(viewX, min_y, max_z, viewX, max_y, max_z);
	Line3(viewX, min_y, min_z, viewX, min_y, max_z);
	Line3(viewX, max_y, min_z, viewX, max_y, max_z);
	//====== Закрываем список команд OpenGL
	glEndList();
}
void DrawCutPlane(SurfDoc* pSurfDoc)
{
	GLdouble * cut_plane ;
	double x,y,z;
	double xd[4],yd[4],zd[4];
	double 
		x_min, x_max, 
		y_min, y_max, 
		z_min, z_max; 
	int np;
	if (pSurfDoc->m_bFastCutting)
	{
		cut_plane = pSurfDoc->m_cut_plane_v;
		x_min = pSurfDoc->m_xv_min;
		x_max = pSurfDoc->m_xv_max;
		y_min = pSurfDoc->m_yv_min;
		y_max = pSurfDoc->m_yv_max;
		z_min = pSurfDoc->m_zv_min;
		z_max = pSurfDoc->m_zv_max;
	}
	else
	{
		cut_plane = pSurfDoc->m_cut_plane_d;
		x_min = pSurfDoc->m_xd_min;
		x_max = pSurfDoc->m_xd_max;
		y_min = pSurfDoc->m_yd_min;
		y_max = pSurfDoc->m_yd_max;
		z_min = pSurfDoc->m_zd_min;
		z_max = pSurfDoc->m_zd_max;
	}
	// отриовка плоскости сечения
	glNewList(FIRST_HARD_LIST+2, GL_COMPILE);

	glBegin(GL_LINES);				
		glColor3f (1.f, 0.0f, 0.f);
	glEnd();


	for (int iz = 0; iz < 2; iz++)
	{
		if (iz == 0)
		{
			// проекция плоскости сечения на верхнюю грань куба z = m_zd_max
			z = z_max;
		}
		if (iz == 1)
		{
			// проекция плоскости сечения на верхнюю грань куба z = m_zd_min
			z = z_min;
		}
		np = 0;

		if (cut_plane[1] != 0.0)
		{
			// x = m_xd_min
			x = x_min;

			y = - (
				cut_plane[0] * x +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[1];

			if( y_min <= y && y <= y_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
			
			// x = m_xd_max
			x = x_max;

			y = - (
				cut_plane[0] * x +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[1];
			if( y_min <= y && y <= y_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
		}
		if (cut_plane[0] != 0.0)
		{
			// y = m_yd_min
			y = y_min;

			x = - (
				cut_plane[1] * y +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[0];
			if( x_min <= x && x <= x_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
			
			// y = m_yd_max
			y = y_max;

			x = - (
				cut_plane[1] * y +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[0];
			if( x_min <= x && x <= x_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
		}

		if(np >= 2)
		{
			double xv1,yv1,zv1; 
			double xv2,yv2,zv2; 
			if (pSurfDoc->m_bFastCutting)
			{
				xv1 = xd[0];
				yv1 = yd[0];
				zv1 = zd[0];

				xv2 = xd[1];
				yv2 = yd[1];
				zv2 = zd[1];
			}
			else
			{
				pSurfDoc->Document2ViewCoordinates(xd[0], yd[0], zd[0], xv1, yv1, zv1);
				pSurfDoc->Document2ViewCoordinates(xd[1], yd[1], zd[1], xv2, yv2, zv2);
			}
				
			glBegin(GL_LINES);				
				glColor3f (1.f, 1.0f, 0.f);
			glEnd();

			Line3(xv1, yv1, zv1, xv2, yv2, zv2);

			char str[4096];
			sprintf(str, "iz\nxd[0] = %lf, yd[0] = %lf, zd[0] = %lf, xv1 = %lf, yv1 = %lf, zv1 = %lf\nxd[1] = %lf, yd[1] = %lf, zd[1] = %lf, xv2 = %lf, yv2 = %lf, zv2 = %lf\n", 
				xd[0], yd[0], zd[0], xv1, yv1, zv1, xd[1], yd[1], zd[1], xv2, yv2, zv2);
			if(np>=3)
			{
				char str1[1024];
				sprintf(str1,"xd[2] = %lf, yd[2] = %lf, zd[2] = %lf\n", 
					xd[2], yd[2], zd[2]);
				strcat(str, str1);
			}
			if(np>=4)
			{
				char str1[1024];
				sprintf(str1,"xd[3] = %lf, yd[3] = %lf, zd[3] = %lf\n", 
					xd[3], yd[3], zd[3]);
				strcat(str, str1);
			}




		}
	}


	for (int ix = 0; ix < 2; ix++)
	{
		if (ix == 0)
		{
			// проекция плоскости сечения на верхнюю грань куба z = m_zd_max
			x = x_max;
		}
		if (ix == 1)
		{
			// проекция плоскости сечения на верхнюю грань куба z = m_zd_min
			x = x_min;
		}
		np = 0;

		if (cut_plane[2] != 0.0)
		{
			// y = m_yd_min
			y = y_min;

			z = - (
				cut_plane[0] * x +
				cut_plane[1] * y +
				cut_plane[3])
				/ cut_plane[2];

			if( z_min <= z && z <= z_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
			
			// y = m_yd_max
			y = y_max;

			z = - (
				cut_plane[0] * x +
				cut_plane[1] * y +
				cut_plane[3])
				/ cut_plane[2];
			if( z_min <= z && z <= z_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
		}
		if (cut_plane[1] != 0.0)
		{
			// z = m_zd_min
			z = z_min;

			y = - (
				cut_plane[0] * x +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[1];
			if( y_min <= y && y <= y_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
			
			// z = m_zd_max
			z = z_max;

			y = - (
				cut_plane[0] * x +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[1];
			if( y_min <= y && y <= y_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
		}

		if(np >= 2)
		{
			double xv1,yv1,zv1; 
			double xv2,yv2,zv2; 
			if (pSurfDoc->m_bFastCutting)
			{
				xv1 = xd[0];
				yv1 = yd[0];
				zv1 = zd[0];

				xv2 = xd[1];
				yv2 = yd[1];
				zv2 = zd[1];
			}
			else
			{
				pSurfDoc->Document2ViewCoordinates(xd[0], yd[0], zd[0], xv1, yv1, zv1);
				pSurfDoc->Document2ViewCoordinates(xd[1], yd[1], zd[1], xv2, yv2, zv2);
			}
			
			glBegin(GL_LINES);				
				glColor3f (1.f, 1.0f, 0.f);
			glEnd();

			Line3(xv1, yv1, zv1, xv2, yv2, zv2);

			char str[4096];
			sprintf(str, "ix\nxd[0] = %lf, yd[0] = %lf, zd[0] = %lf, xv1 = %lf, yv1 = %lf, zv1 = %lf\nxd[1] = %lf, yd[1] = %lf, zd[1] = %lf, xv2 = %lf, yv2 = %lf, zv2 = %lf\n", 
				xd[0], yd[0], zd[0], xv1, yv1, zv1, xd[1], yd[1], zd[1], xv2, yv2, zv2);
			if(np>=3)
			{
				char str1[1024];
				sprintf(str1,"xd[2] = %lf, yd[2] = %lf, zd[2] = %lf\n", 
					xd[2], yd[2], zd[2]);
				strcat(str, str1);
			}
			if(np>=4)
			{
				char str1[1024];
				sprintf(str1,"xd[3] = %lf, yd[3] = %lf, zd[3] = %lf\n", 
					xd[3], yd[3], zd[3]);
				strcat(str, str1);
			}




		}
	}




	for (int iy = 0; iy < 2; iy++)
	{
		if (iy == 0)
		{
			// проекция плоскости сечения на верхнюю грань куба z = m_zd_max
			y = y_max;
		}
		if (iy == 1)
		{
			// проекция плоскости сечения на верхнюю грань куба z = m_zd_min
			y = y_min;
		}
		np = 0;

		if (cut_plane[2] != 0.0)
		{
			// x = m_xd_min
			x = x_min;

			z = - (
				cut_plane[0] * x +
				cut_plane[1] * y +
				cut_plane[3])
				/ cut_plane[2];

			if( z_min <= z && z <= z_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
			
			// x = m_xd_max
			x = x_max;

			z = - (
				cut_plane[0] * x +
				cut_plane[1] * y +
				cut_plane[3])
				/ cut_plane[2];
			if( z_min <= z && z <= z_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
		}
		if (cut_plane[0] != 0.0)
		{
			// z = m_zd_min
			z = z_min;

			x = - (
				cut_plane[1] * y +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[0];
			if( x_min <= x && x <= x_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
			
			// z = m_zd_max
			z = z_max;

			x = - (
				cut_plane[1] * y +
				cut_plane[2] * z +
				cut_plane[3])
				/ cut_plane[0];
			if( x_min <= x && x <= x_max)
			{
				xd[np] = x; yd[np] = y; zd[np] = z;
				np++;
			}
		}

		if(np >= 2)
		{
			double xv1,yv1,zv1; 
			double xv2,yv2,zv2; 
			if (pSurfDoc->m_bFastCutting)
			{
				xv1 = xd[0];
				yv1 = yd[0];
				zv1 = zd[0];

				xv2 = xd[1];
				yv2 = yd[1];
				zv2 = zd[1];
			}
			else
			{
				pSurfDoc->Document2ViewCoordinates(xd[0], yd[0], zd[0], xv1, yv1, zv1);
				pSurfDoc->Document2ViewCoordinates(xd[1], yd[1], zd[1], xv2, yv2, zv2);
			}
			
			glBegin(GL_LINES);				
				glColor3f (1.f, 1.0f, 0.f);
			glEnd();

			Line3(xv1, yv1, zv1, xv2, yv2, zv2);

			char str[4096];
			sprintf(str, "iy\nxd[0] = %lf, yd[0] = %lf, zd[0] = %lf, xv1 = %lf, yv1 = %lf, zv1 = %lf\nxd[1] = %lf, yd[1] = %lf, zd[1] = %lf, xv2 = %lf, yv2 = %lf, zv2 = %lf\n", 
				xd[0], yd[0], zd[0], xv1, yv1, zv1, xd[1], yd[1], zd[1], xv2, yv2, zv2);
			if(np>=3)
			{
				char str1[1024];
				sprintf(str1,"xd[2] = %lf, yd[2] = %lf, zd[2] = %lf\n", 
					xd[2], yd[2], zd[2]);
				strcat(str, str1);
			}
			if(np>=4)
			{
				char str1[1024];
				sprintf(str1,"xd[3] = %lf, yd[3] = %lf, zd[3] = %lf\n", 
					xd[3], yd[3], zd[3]);
				strcat(str, str1);
			}
			/*char str2[1024];
			sprintf(str2, "m_xd_min = %lf, m_yd_min = %lf, m_zd_min = %lf \nm_xd_max = %lf, m_yd_max = %lf, m_zd_max = %lf\nm_xv_min = %lf, m_yv_min = %lf, m_zv_min = %lf, \nm_xv_max = %lf, m_yv_max = %lf, m_zv_max = %lf\n", 
				pSurfDoc->m_xd_min, y_min, pSurfDoc->m_zd_min, pSurfDoc->m_xd_max, y_max, pSurfDoc->m_zd_max,
				pSurfDoc->m_xv_min, pSurfDoc->m_yv_min, pSurfDoc->m_zv_min, pSurfDoc->m_xv_max, pSurfDoc->m_yv_max, pSurfDoc->m_zv_max);
			strcat(str, str2);
			sprintf(str2, "m_xd_mean = %lf, m_yd_mean = %lf, m_zd_mean = %lf\n", 
				pSurfDoc->m_xd_mean, y_mean, pSurfDoc->m_zd_mean);
			strcat(str, str2);
			char str3[1024];
			sprintf(str3,"a = %lf \nb = %lf \nc = %lf \nd = %lf",
				pSurfDoc->m_a,		
				pSurfDoc->m_b,		
				pSurfDoc->m_c,		
				pSurfDoc->m_d);
			strcat(str, str3);*/


//				MessageBox(0,str, "",0);

		}
	}

	//====== Закрываем список команд OpenGL
	glEndList();
}
int Scale(double v[3])
{
	double d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	if (d == 0.0)
	{
		//MessageBox(0,"Zero length vector","Scale(double v[3])",0);
		return 0;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
	return 1;
}
void getNorm(double v1[3], double v2[3], double out[3])
{
	//вычисляем координаты вектора нормали по формулам векторного произведения
	out[0] = v1[1]*v2[2] - v1[2]*v2[1];
	out[1] = v1[2]*v2[0] - v1[0]*v2[2];
	out[2] = v1[0]*v2[1] - v1[1]*v2[0];
#if 0
	Scale(out);
#else
	double d = sqrt(out[0]*out[0] + out[1]*out[1] + out[2]*out[2]);
	if (d == 0.0)
	{
		char str[1024];
		sprintf(str,"v1[0] =%lf, v1[1] =%lf, v1[2] =%lf, \nv2[0] =%lf, v2[1] =%lf, v2[2] =%lf \nout[0] =%lf,out[1] =%lf,out[2] =%lf",
			v1[0], v1[1], v1[2], v2[0], v2[1], v2[2], out[0], out[1], out[2]);
		//MessageBox(0,str, "Zero length vector Scale(double v[3])",0);
		return;
	}
	out[0] /= d; out[1] /= d; out[2] /= d;
#endif
}

void DrawPolygones(SurfDoc* pSurfDoc/*, GLenum FillMode*/ )
{
	 // добавление 3d string
	if (pSurfDoc) AddPolygonesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_polygones.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_polygones.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_polygones.IncrementCurrentMsg());
	}
}

void DrawTriangles(SurfDoc* pSurfDoc/*, GLenum FillMode*/ )
{
	if (pSurfDoc) AddTrianglesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_triangles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_triangles.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_triangles.IncrementCurrentMsg());
	}
}
void DrawBitmaps(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddBitmapsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_bitmaps.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_bitmaps.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_bitmaps.IncrementCurrentMsg());
	}
}
void DrawBmpProfiles(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddBmpProfilesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_bmp_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_bmp_profiles.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_bmp_profiles.IncrementCurrentMsg());
	}
}
void DrawGeoCatches(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddGeoCatchesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_geo_catches.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_geo_catches.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_geo_catches.IncrementCurrentMsg());
	}
}

void DrawAutoBuildProfiles(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddAutoBuildProfilesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_auto_build_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_auto_build_profiles.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_auto_build_profiles.IncrementCurrentMsg());
	}
}


void DrawGridData(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddGridDataToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_grid_data.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_grid_data.IncrementCurrentMsg());
	}
}
void ReDrawGridData(SurfDoc* pSurfDoc )
{
	if (pSurfDoc->m_grid_data_ObjectList.myTreeItem != NULL)
	{
		TreeView_DeleteMyItem(pSurfDoc->hwndTV, pSurfDoc->m_grid_data_ObjectList.myTreeItem);
	}
	if (pSurfDoc) AddGridDataToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_grid_data.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_grid_data.GetCurrentMsg().ReDraw();
		}
		while(pSurfDoc->m_grid_data.IncrementCurrentMsg());
	}
}

void DrawCubes(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddCubesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_cubes.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_cubes.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_cubes.IncrementCurrentMsg());
	}
}
void DrawNewCube(SurfDoc* pSurfDoc)
{
#if 0
	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем необходимость учета света
	//====== Настройка OpenGL на использование массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//glEnable(GL_NORMALIZE);
	if (pSurfDoc->m_bFlatShading)
		glShadeModel (GL_FLAT);
	else
		glShadeModel (GL_SMOOTH);


#endif
	if (pSurfDoc) AddLastCubeToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_cubes.SetCurrentMsgOnLast())
	{
		pSurfDoc->m_cubes.GetCurrentMsg().UpdateExtremums();
		pSurfDoc->m_cubes.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomX, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pSurfDoc->m_cubes.GetCurrentMsg().Draw();
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}



#if DFX_LAYER_FROM_OBJECT
void DrawDxf(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddDxfToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_dxfConverters.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_dxfConverters.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_dxfConverters.IncrementCurrentMsg());
	}
}
#endif
void DrawObjects(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddObjectsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_objects.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_objects.IncrementCurrentMsg());
	}
}
void DrawCollections(SurfDoc* pSurfDoc )
{
	if (pSurfDoc) AddCollectionsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_collections.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_collections.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_collections.IncrementCurrentMsg());
	}
}
#define DRAW_SURFS_HEADER 1
void DrawNewSurf(SurfDoc* pSurfDoc)
{
#if DRAW_SURFS_HEADER
	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем необходимость учета света
	//====== Настройка OpenGL на использование массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//glEnable(GL_NORMALIZE);
	if (pSurfDoc->m_bFlatShading)
		glShadeModel (GL_FLAT);
	else
		glShadeModel (GL_SMOOTH);


#endif
	if (pSurfDoc) AddLastSurfaceToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_surfaces.SetCurrentMsgOnLast())
	{
		pSurfDoc->m_surfaces.GetCurrentMsg().UpdateExtremums();
		pSurfDoc->m_surfaces.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomX, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pSurfDoc->m_surfaces.GetCurrentMsg().Draw();
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}

void DrawNewFault(SurfDoc* pSurfDoc)
{
#if DRAW_SURFS_HEADER
	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем необходимость учета света
	//====== Настройка OpenGL на использование массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//glEnable(GL_NORMALIZE);
	if (pSurfDoc->m_bFlatShading)
		glShadeModel (GL_FLAT);
	else
		glShadeModel (GL_SMOOTH);


#endif
	if (pSurfDoc) AddLastFaultToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_faults.SetCurrentMsgOnLast())
	{
		pSurfDoc->m_faults.GetCurrentMsg().UpdateExtremums();
		pSurfDoc->m_faults.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomX, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pSurfDoc->m_faults.GetCurrentMsg().Draw();
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}
void DrawSurfs(SurfDoc* pSurfDoc)
{
	printf("DrawSurfs(SurfDoc* pSurfDoc)\n");
#if DRAW_SURFS_HEADER
	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем необходимость учета света
	//====== Настройка OpenGL на использование массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnable(GL_NORMALIZE);
	if (pSurfDoc->m_bFlatShading)
		glShadeModel (GL_FLAT);
	else
		glShadeModel (GL_SMOOTH);


#endif
		
	if (pSurfDoc) AddSurfacesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_surfaces.SetCurrentMsgOnFirst()	)
	{
		do
		{
			pSurfDoc->m_surfaces.GetCurrentMsg().Draw();
		}				
		while(pSurfDoc->m_surfaces.IncrementCurrentMsg() );
	}
	printf("DrawSurfs(SurfDoc* pSurfDoc) end\n");
}

void DrawFaults(SurfDoc* pSurfDoc)
{
	printf("DrawFaults(SurfDoc* pSurfDoc)\n");
#if DRAW_SURFS_HEADER
	//====== Включаемаем необходимость учета света
	glEnable(GL_LIGHTING);
	//====== Включаемаем необходимость учета света
	//====== Настройка OpenGL на использование массивов
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	//glEnable(GL_NORMALIZE);
	if (pSurfDoc->m_bFlatShading)
		glShadeModel (GL_FLAT);
	else
		glShadeModel (GL_SMOOTH);


#endif
	if (pSurfDoc) AddFaultsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_faults.SetCurrentMsgOnFirst()	)
	{
		do
		{
			pSurfDoc->m_faults.GetCurrentMsg().Draw();
		}				
		while(pSurfDoc->m_faults.IncrementCurrentMsg() );
	}
}

void DrawGridProfiles(SurfDoc* pSurfDoc)
{
	 // добавление 3d линии
	if (pSurfDoc) AddGridProfilesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_grid_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_grid_profiles.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_grid_profiles.IncrementCurrentMsg());
	}

}

void DrawCutLines(SurfDoc* pSurfDoc)
{
	 // добавление 3d линии
	if (pSurfDoc) AddCutLinesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_cutlines.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_cutlines.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_cutlines.IncrementCurrentMsg());
	}
}

void DrawBlankLines(SurfDoc* pSurfDoc)
{
	 // добавление 3d линии
	if (pSurfDoc) AddBlankLinesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_blanklines.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_blanklines.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_blanklines.IncrementCurrentMsg());
	}
}
void DrawLines(SurfDoc* pSurfDoc)
{
	 // добавление 3d линии
	if (pSurfDoc) AddLinesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_lines.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_lines.IncrementCurrentMsg());
	}
}

void DrawDrills(SurfDoc* pSurfDoc)
{
	 // добавление 3d линии
	if (pSurfDoc) AddWellsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_drills.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_drills.IncrementCurrentMsg());
	}
}
void ReDrawDrills(SurfDoc* pSurfDoc)
{
	if (pSurfDoc && pSurfDoc->m_drills.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_drills.GetCurrentMsg().ReDraw();
		}
		while(pSurfDoc->m_drills.IncrementCurrentMsg());
	}
}

void DrawStrings(SurfDoc* pSurfDoc)
{
	 // добавление 3d string
	if (pSurfDoc) AddStringsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_strings.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_strings.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_strings.IncrementCurrentMsg());
	}
}
/*
void ReDrawNewLine(SurfDoc* pSurfDoc)
{
	if (pSurfDoc && pSurfDoc->m_lines.SetCurrentMsgOnLast())
	{
		pSurfDoc->m_lines.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomY, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pSurfDoc->m_lines.GetCurrentMsg().ReDraw();
		UpdateLastLineOnTree(pSurfDoc->hwndTV, pSurfDoc);
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}
*/

void DrawNewLine(SurfDoc* pSurfDoc)
{
	if (pSurfDoc) AddLastLineToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_lines.SetCurrentMsgOnLast())
	{
		pSurfDoc->m_lines.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomY, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pSurfDoc->m_lines.GetCurrentMsg().Draw();
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}

void DrawTriaGrid(SurfDoc* pSurfDoc)
{
	if (pSurfDoc) AddTriangulatedGrid3DToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_tria_grid.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_tria_grid.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_tria_grid.IncrementCurrentMsg());
	}
}

void DrawBrokenPlanes(SurfDoc* pSurfDoc)
{
#if BROKEN_PLANE_VECTOR_TYPE
	if (pSurfDoc) AddBrokenPlanesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_brokenPlanes.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_brokenPlanes.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_brokenPlanes.IncrementCurrentMsg());
	}
#else
	if (pSurfDoc) 
		if (pSurfDoc->m_brokenPlanes.size())
			AddBrokenPlanesToTree(pSurfDoc->hwndTV, pSurfDoc);
	vector<BrokenPlane3D>::iterator iter_bp;
	for (iter_bp = pSurfDoc->m_brokenPlanes.begin(); iter_bp != pSurfDoc->m_brokenPlanes.end();iter_bp++)
	{
		 iter_bp->Draw();
	}
#endif
}

void DrawBlnProfiles(SurfDoc* pSurfDoc)
{


	if (pSurfDoc) AddBlnProfilesToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_bln_profiles.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_bln_profiles.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_bln_profiles.IncrementCurrentMsg());
	}
}

void DrawPoints(SurfDoc* pSurfDoc)
{
	if (pSurfDoc) AddPointsToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_points.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_points.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_points.IncrementCurrentMsg());
	}
}
void DrawNewGridDataItem(SurfDoc* pSurfDoc, GridData* pGridData)
{
	if (pGridData) AddLastGridDataToTree(pSurfDoc->hwndTV, pGridData);
	if (pGridData && pGridData->m_input_points.SetCurrentMsgOnLast())
	{
		pGridData->m_input_points.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomY, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pGridData->m_input_points.GetCurrentMsg().Draw();
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}
void DrawNewSphere(SurfDoc* pSurfDoc)
{
	if (pSurfDoc) AddLastSphereToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_spheres.SetCurrentMsgOnLast())
	{
		pSurfDoc->m_spheres.GetCurrentMsg().Zoom(
			pSurfDoc->m_zoomX,
			pSurfDoc->m_zoomY, 
			pSurfDoc->m_zoomZ,
			pSurfDoc->m_xd_zoom_center,
			pSurfDoc->m_yd_zoom_center,
			pSurfDoc->m_zd_zoom_center);
		pSurfDoc->m_spheres.GetCurrentMsg().Draw();
	}
	if (pSurfDoc && pSurfDoc->m_bDrawCube)
	{
		// delete cube
		glDeleteLists(FIRST_HARD_LIST+1,1);
		pSurfDoc->UpdateExtremums();
		DrawCube(pSurfDoc);
	}
}
void DrawSpheres(SurfDoc* pSurfDoc)
{
	if (pSurfDoc) AddSpheresToTree(pSurfDoc->hwndTV, pSurfDoc);
	if (pSurfDoc && pSurfDoc->m_spheres.SetCurrentMsgOnFirst())
	{
		do
		{
			pSurfDoc->m_spheres.GetCurrentMsg().Draw();
		}
		while(pSurfDoc->m_spheres.IncrementCurrentMsg());
	}
}
