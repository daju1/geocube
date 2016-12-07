// Line3D.cpp: implementation of the Line3D class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Line3D.h"
#include "SurfDoc.h"
//#include "raporto.h"
#include ".\line3d.h"
#include ".\archive.h"
#include "distance3D.h"
#include ".\whatselected.h"
#include "winsurftree.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
Line3D::line3d_draw_mode Line3D::s_line3d_draw_mode = Line3D::line3d_draw_mode::as_thing_lines;

Line3D::Line3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

Line3D::Line3D(SurfDoc *pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
#define LINE3D_VERSION 3
void Line3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::line3d;
	this->m_object_version = LINE3D_VERSION;
	this->m_max_object_version = LINE3D_VERSION;

	this->id_ige = -1;
	this->id_surf = -1;
	this->id_umpoz = 0;
	this->podoshva = 0;

	m_LineWidth = 2.0;
}
Line3D::~Line3D()
{

}


void Line3D::Init(vdouble &x, vdouble &y, vdouble &z, COLORREF color)
{
	if (x.Length() == y.Length() && y.Length() == z.Length())
	{
		m_ptMax.x = x.Max();
		m_ptMax.y = y.Max();
		m_ptMax.z = z.Max();

		m_ptMin.x = x.Min();
		m_ptMin.y = y.Min();
		m_ptMin.z = z.Min();

		Free();
		AllocPoints(z.Length());

		m_color = color;
		CPoint3 pt;
		// складываем данные в документ
		for(UINT i = 0; i < GetPointsNumber(); i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;
			m_vdPoints[i] = pt;
			m_vvPoints[i] = pt;
		}
	}
}
void Line3D::Init(vector<double> &x, vector<double> &y, vector<double> &z, COLORREF color)
{
	if (x.size() == y.size() && y.size() == z.size())
	{
		/*m_ptMax.x = x.Max();
		m_ptMax.y = y.Max();
		m_ptMax.z = z.Max();

		m_ptMin.x = x.Min();
		m_ptMin.y = y.Min();
		m_ptMin.z = z.Min();*/

		Free();
		AllocPoints(z.size());

		m_color = color;
		CPoint3 pt;
		// складываем данные в документ
		for(UINT i = 0; i < GetPointsNumber(); i++)
		{
			pt.x = x[i];
			pt.y = y[i];
			pt.z = z[i];
			pt.bVisible = true;
			m_vdPoints[i] = pt;
			m_vvPoints[i] = pt;
		}
		this->UpdateExtremums();
	}
}
HTREEITEM Line3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	// Add the item to the tree-view control
	sprintf(szItemText, "\"%s\" len = %d color = [%u %u %u]", GetName().c_str(), GetPointsNumber(), GetRValue(m_color), GetGValue(m_color), GetBValue(m_color));
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
void Line3D::Drawing(void)
{
//printf("Line3D::Drawing\n");

	COLORREF color;
	GLfloat LineWidth;
	if (this->m_lParam & OBJECT_FLAG_SELECTED_BIT)
	{
		LineWidth = m_LineWidth+3.0;
		color = RGB(
			(255-GetRValue(m_color))/2,
			0,
			(255-GetBValue(m_color))/2);
	}
	else
	{
		LineWidth = m_LineWidth;
		color = m_color;
	}
	if (this->m_lParam & OBJECT_FLAG_THING_BIT)
		LineWidth = 0.0;

		
	glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
	
	for (UINT i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
	{
		if (
			m_vvPoints[i0].bVisible
			&& m_vvPoints[i1].bVisible && 
			!(m_vdPoints[i0].flag & CPOINT3_FLAG_HIDE_LINE) 
			)
		{
			glLineWidth(m_LineWidth);
			Line3(
				m_vvPoints[i0].x,
				m_vvPoints[i0].y,
				m_vvPoints[i0].z,
				m_vvPoints[i1].x,
				m_vvPoints[i1].y,
				m_vvPoints[i1].z);
		}
	}
	if (Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres
		||
		this->m_lParam & OBJECT_FLAG_SELECTED_BIT)
	{
		for (UINT i = 0; i < GetPointsNumber(); i++)
		{
			if(m_vvPoints[i].bVisible)
			{
				COLORREF sphereColor;
				double sphere_radius;
				if (m_vdPoints[i].flag & CPOINT3_FLAG_SELECTED
					||
					this->m_lParam & OBJECT_FLAG_SELECTED_BIT)
				{
					sphere_radius = m_pSurfDoc->m_sphere_radius;
					sphereColor = RGB(
						(255-GetRValue(m_color))/2,
						0/*(255-GetGValue(m_color))/2*/,
						(255-GetBValue(m_color))/2);
				}
				else
				{
					sphere_radius = m_pSurfDoc->m_sphere_radius;
					sphereColor = m_color;
				}
				if (!(m_vdPoints[i].flag & CPOINT3_FLAG_HIDE))
				{
					glColor3ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor)); 

					GLUquadricObj* pSphere = gluNewQuadric();
					gluQuadricDrawStyle(pSphere, GLU_FILL);
					glPushMatrix();//перейдём к новым координатам, сохранив старые
					
					glTranslated(
						m_vvPoints[i].x, 
						m_vvPoints[i].y, 
						m_vvPoints[i].z
						);

					gluSphere(pSphere, 
						sphere_radius, 
						m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
						m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
						) ;//рисуем сферу 
					glPopMatrix(); //возвращаемся к старым координатам 
					gluDeleteQuadric(pSphere);
				}
				else
				{
					//printf("Has_hide_point i = %d\n", i);
				}
			}
		}
	}
}


#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"

void Line3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, int alpha)
{	
	fGL x1; fGL y1;
	fGL x2; fGL y2;

	v->PreConvertingFromWorldToScreen();

	bool to_fill_circles = Line3D::s_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres
		||
		this->m_lParam & OBJECT_FLAG_SELECTED_BIT;
	
	fGL r = v->lines_points_radius;

	COLORREF color;
	GLfloat LineWidth;
	if (this->m_lParam & OBJECT_FLAG_SELECTED_BIT)
	{
		LineWidth = m_LineWidth+3.0;
		color = RGB(
			(255-GetRValue(m_color))/2,
			0,
			(255-GetBValue(m_color))/2);
	}
	else
	{
		LineWidth = m_LineWidth;
		color = m_color;
	}
	if (this->m_lParam & OBJECT_FLAG_THING_BIT)
		LineWidth = 0.0;

	Color gdi_color(alpha, GetRValue(color),GetGValue(color),GetBValue(color));
	Pen      pen(gdi_color);
	pen.SetWidth(LineWidth);

	double dist_to_plane;
	CPoint2 profile;

	if (0 < GetPointsNumber())
	{
		//Convert3D_To_2D
		on->Projection(m_vdPoints[0], profile, dist_to_plane);
		v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
		if (to_fill_circles&& !(m_vdPoints[0].flag & CPOINT3_FLAG_HIDE)) 
			FillCircle(&graphics, x1, y1, r, gdi_color);
	}

	for (UINT i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
	{
		if (
			m_vvPoints[i0].bVisible
			&& m_vvPoints[i1].bVisible && 
			!(m_vdPoints[i0].flag & CPOINT3_FLAG_HIDE_LINE) 
			)
		{
			//glLineWidth(m_LineWidth);
			
			//Convert3D_To_2D
			on->Projection(m_vdPoints[i0], profile, dist_to_plane);
			v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

			on->Projection(m_vdPoints[i1], profile, dist_to_plane);
			v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

			if (to_fill_circles && !(m_vdPoints[i1].flag & CPOINT3_FLAG_HIDE)) 
				FillCircle(&graphics, x2, y2, r, gdi_color);
				
			graphics.DrawLine(&pen, x1, y1, x2, y2);
		}
	}
}

double getcosinus (CPoint3 p1, CPoint3 p2, CPoint3 p3)
{
	CPoint3 v1,v2;
	v1.x = (p1.x-p2.x);
	v2.x = (p3.x-p2.x);

	v1.y = (p1.y-p2.y);
	v2.y = (p3.y-p2.y);

	v1.z = (p1.z-p2.z);
	v2.z = (p3.z-p2.z);

	return 
		(
		(v1.x)*(v2.x) + 
		(v1.y)*(v2.y) + 
		(v1.z)*(v2.z) 
		) / (
		sqrt((v1.x)*(v1.x)+(v1.y)*(v1.y)+(v1.z)*(v1.z)) * 
		sqrt((v2.x)*(v2.x)+(v2.y)*(v2.y)+(v2.z)*(v2.z)) ) 
		;
}
void Line3D::AngleLocalMin(int n, double cos_boder)
{
	UINT i0, i1, i2;
	int i = 0;
	bool closed;
	if (
		m_vdPoints[0].x == m_vdPoints[GetPointsNumber()-1].x &&
		m_vdPoints[0].y == m_vdPoints[GetPointsNumber()-1].y &&
		m_vdPoints[0].z == m_vdPoints[GetPointsNumber()-1].z 
		)
	{
		closed = true;
	}
	else
		closed = false;

	//for (i0 = 0, i1 = 2, i2 = 4 ; i2 < GetPointsNumber(); i0++, i1++, i2++)
	for (i0 = 0, i1 = 1, i2 = 2 ; i2 < GetPointsNumber(); i0++, i1++, i2++)
	{
		if(m_vdPoints[i0].bVisible
			&& m_vdPoints[i1].bVisible
			&& m_vdPoints[i2].bVisible
			)
		{
			i++;
		}
	}
	if (closed)
		i++;
	int coslen = i;
	vdouble cosinus;
	cosinus.resize(coslen);
	i = 0;
	//for (i0 = 0, i1 = 2, i2 = 4 ; i2 < GetPointsNumber(); i0++, i1++, i2++)
	for (i0 = 0, i1 = 1, i2 = 2 ; i2 < GetPointsNumber(); i0++, i1++, i2++)
	{
		if(m_vdPoints[i0].bVisible
			&& m_vdPoints[i1].bVisible
			&& m_vdPoints[i2].bVisible
			)
		{
			cosinus[i] = getcosinus(m_vdPoints[i0], m_vdPoints[i1], m_vdPoints[i2]);
			i++;
		}
	}
	if (closed)
		cosinus[i] = getcosinus(m_vdPoints[1], m_vdPoints[0], m_vdPoints[GetPointsNumber()-2]);

	vdouble LocMinOfCosinus;
	Vector<int> indexesOfLocMin;

	cosinus.LocalMaximums(n, LocMinOfCosinus,indexesOfLocMin);

	for (i = 0; i < indexesOfLocMin.Size(); i++)
	{
		if (LocMinOfCosinus[i] > cos_boder)
			this->m_pSurfDoc->AddSphere(m_vdPoints[indexesOfLocMin[i] + 1],RGB(0,255,0));

	}
}

// DIME: needed include files.
#include <dime/Model.h>
#include <dime/sections/BlocksSection.h>
#include <dime/tables/LayerTable.h>
#include <dime/dxfwriter.h>
#include "CrdTranslator.h"
bool Line3D::SaveAsDxf(dimeModel * model, dimeBlock * block, CrdTranslator * translator)
{
	if (!model) return false;
	print_line(this, model, block, translator); 
	return true;
}

void Line3D::SavingAsDatOrBln(FILE *fd, DWORD nFilterIndex)
{
	int len = GetPointsNumber();
	if (nFilterIndex == 1)
	{
		if (len)
			fprintf(fd, "%d, %d\n", len, 0);
	}
	for (int i = 0; i < len; i++)
	{			
		fprintf(fd, "%lf, %lf, %lf\n", 
			m_vdPoints[i].x, 
			m_vdPoints[i].y, 
			m_vdPoints[i].z);
	}
}


bool Line3D::SavingAsRazrez(dimeModel * model,  dimeBlock * block, 
							SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
	if (!model) return false;
	CrdTranslator translator;
	if(InitTranslator(translator, sprData, a, b, c, d, minX, minY, minZ, maxX, maxY, maxZ))
		print_line(this, model, block, &translator);
	else
		return false;
	return true;
}
#if 1
void Line3D::SavingAsRazrez(FILE *fd, 
							SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
	CrdTranslator translator;
	if(InitTranslator(translator, sprData, a, b, c, d, minX, minY, minZ, maxX, maxY, maxZ))
		this->SaveAsBln(fd, translator);
}
#else
void Line3D::SavingAsRazrez(FILE *fd, 
							SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ)
{
printf("Line3D::SavingAsRazrez 0\n");
	switch(sprData.export_coordinate_type)
	{
		case SAVE_PROFILE_3D_XYZ:
			{
				this->SaveAsBln(fd);
			}
			break;
		case SAVE_PROFILE_WITH_PROFILE_LEN:
			{
				this->SaveAsBln_with_profile_len(fd, a, b, c, d, minX, minY, minZ, maxX, maxY, maxZ);
			}
			break;
		case SAVE_PROFILE_WITH_NORTH_PROJECTION:
			{
				this->SaveAsBln_YZ(fd);
			}
			break;
		case SAVE_PROFILE_WITH_EAST_PROJECTION:
			{
				this->SaveAsBln_XZ(fd);
			}
			break;
		case SAVE_PROFILE_WITH_GORIZONTAL_PROJECTION:
			{
				this->SaveAsBln_XY(fd);
			}
			break;
		case SAVE_PROFILE_AUTO_SELECT_PROJECTION:
			{
				// определяем преимущественное направление вектора нормали к плоскости
				if (fabs(c) >= fabs(a) && fabs(c) >= fabs(b))
				{
					// доминирует направление вдоль оси Z
					this->SaveAsBln_XY(fd);
				}
				else if (fabs(a) >= fabs(b) && fabs(a) >= fabs(c))
				{
					// доминирует направление вдоль оси X
					this->SaveAsBln_YZ(fd);
				}
				else if (fabs(b) >= fabs(a) && fabs(b) >= fabs(c))
				{
					// доминирует направление вдоль оси Y
					this->SaveAsBln_XZ(fd);
				}
			}
			break;
	}
}
#endif
void Line3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", " Line3D" , 0);

}

void Line3D::Init(const Line3D& ob)
{
	this->m_pSurfDoc	= ob.m_pSurfDoc;
	this->m_LineWidth	= ob.m_LineWidth;

	this->id_ige		= ob.id_ige;
	this->id_umpoz		= ob.id_umpoz;
	this->id_surf		= ob.id_surf;//идентификатор для зранения поверхности в базе
	this->podoshva		= ob.podoshva;
}

Line3D::Line3D(const Line3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

Line3D& Line3D::operator=(const Line3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}
extern int GetVerticalPlaneFromTwoPoints(
								  CPoint2 &pt1, CPoint2 &pt2, //input
								  double &a, double &b, double &c, double &d);//output


int Line3D::WhatSidesOfTwoPoint(short zflag, CPoint3& pt1, CPoint3& pt2)
{
	// решаем проблему - по одинаковые или по разные стороны от данной линии лежат две входные точки
	// задача решается в двумерной проекции - причём входные точки проецируются на плоскость XY независимо от zflag
	// от zflag зависит только какие координаты данной линии будут проецироваться на плоскость, т.е. 
	// в данной функции в зависимости от zflag осуществляется перестановка координат линии, но не входных точек

	bool closed_line = 
		this->GetFirstDocumentPoint().x == this->GetLastDocumentPoint().x &&
		this->GetFirstDocumentPoint().y == this->GetLastDocumentPoint().y &&
		this->GetFirstDocumentPoint().z == this->GetLastDocumentPoint().z 
		;	

	if (pt1.x == pt2.x &&
		pt1.y == pt2.y)
	{
		// входящие точки совпадают
		// а это значит, что две входящие точки лежат по одну сторону от данной линии
		return 1;
	}

	// число пересечений отрезка с линией
	int nCutting = 0;
	bool first_point_on_line = false;
	bool second_point_on_line = false;

	double min_x = min(pt1.x, pt2.x);
	double max_x = max(pt1.x, pt2.x);
	double min_y = min(pt1.y, pt2.y);
	double max_y = max(pt1.y, pt2.y);

	double a2,b2,c2,d2;

	GetVerticalPlaneFromTwoPoints(
							CPoint2(pt1.x, pt1.y), CPoint2(pt2.x, pt2.y), //input
							a2, b2, c2, d2);//output	



	int linelen = this->GetPointsNumber();

	for (int i = 0; i < linelen - 1; i++)
	{
		// начало и конец текущего отрезка
		CPoint3 pt_start = this->GetDocumentPoint(i);
		CPoint3 pt_end = this->GetDocumentPoint(i+1);
		// теперь ищем пересекаются ли два отрезка
		// вычисляем уравнение двух прямых 
		double a1,b1,c1,d1;
		switch(zflag)
		{
		case 0:
			{
				GetVerticalPlaneFromTwoPoints(
										CPoint2(pt_start.x, pt_start.y), CPoint2(pt_end.x, pt_end.y), //input
										a1, b1, c1, d1);//output
			}
			break;
		case 1:
			{
				GetVerticalPlaneFromTwoPoints(
										CPoint2(pt_start.z, pt_start.y), CPoint2(pt_end.z, pt_end.y), //input
										a1, b1, c1, d1);//output
			}
			break;
		case 2:
			{
				GetVerticalPlaneFromTwoPoints(
										CPoint2(pt_start.x, pt_start.z), CPoint2(pt_end.x, pt_end.z), //input
										a1, b1, c1, d1);//output
			}
			break;
		}
		// а теперь решаем систему уравнений с целью найти точку пересечения прямых на которых лежат эти два отрезка
		vdouble M;
		M.resize(2,2);
		vdouble b;
		b.resize(2);

		M(0,0) = a1;	M(0,1) = b1;
		M(1,0) = a2;	M(1,1) = b2;

		b[0] = -d1;
		b[1] = -d2;

		vdouble xy;
		double det;

		M.sls_det(b,xy,det);
		// проверяем прямые на параллельность
		if (det != 0.0)
		{
			// координаты точки пересечения двух отрезков
			double x = xy[0];
			double y = xy[1];  

			double minx;
			double maxx;
			double miny;
			double maxy;

			switch(zflag)
			{
			case 0:
				{
					minx = min(pt_start.x, pt_end.x);
					maxx = max(pt_start.x, pt_end.x);
					miny = min(pt_start.y, pt_end.y);
					maxy = max(pt_start.y, pt_end.y);
				}
				break;
			case 1:
				{
					minx = min(pt_start.z, pt_end.z);
					maxx = max(pt_start.z, pt_end.z);
					miny = min(pt_start.y, pt_end.y);
					maxy = max(pt_start.y, pt_end.y);
				}
				break;
			case 2:
				{
					minx = min(pt_start.x, pt_end.x);
					maxx = max(pt_start.x, pt_end.x);
					miny = min(pt_start.z, pt_end.z);
					maxy = max(pt_start.z, pt_end.z);
				}
				break;
			}

			// флаг того,что точка пересечения режет текущий отрезок
			bool thisCutting = 
				x >= minx && 
				x <= maxx && 

				y >= miny && 
				y <= maxy;	

			// флаг того, что точка пересечения режет продолжение текущего отрезка
			int this_continue_cutting = 0;

			if (i == 0 && !closed_line)
			{
				bool bx,by;
				switch(zflag)
				{
				case 0:
					{
						if (pt_start.x<pt_end.x)
							bx = x <= pt_end.x;
						else
							bx = x >= pt_end.x;

						if (pt_start.y<pt_end.y)
							by = y <= pt_end.y;
						else
							by = y >= pt_end.y;
					}
					break;
				case 1:
					{
						if (pt_start.z<pt_end.z)
							bx = x <= pt_end.z;
						else
							bx = x >= pt_end.z;

						if (pt_start.y<pt_end.y)
							by = y <= pt_end.y;
						else
							by = y >= pt_end.y;
					}
					break;
				case 2:
					{
						if (pt_start.x<pt_end.x)
							bx = x <= pt_end.x;
						else
							bx = x >= pt_end.x;

						if (pt_start.z<pt_end.z)
							by = y <= pt_end.z;
						else
							by = y >= pt_end.z;
					}
					break;
				}

				this_continue_cutting += int(bx && by);
			}
			if (i == int(linelen)-2 && !closed_line)
			{
				bool bx,by;
				switch(zflag)
				{
				case 0:
					{
						if (pt_end.x<pt_start.x)
							bx = x <= pt_start.x;
						else
							bx = x >= pt_start.x;

						if (pt_end.y<pt_start.y)
							by = y <= pt_start.y;
						else
							by = y >= pt_start.y;
					}
					break;
				case 1:
					{
						if (pt_end.z<pt_start.z)
							bx = x <= pt_start.z;
						else
							bx = x >= pt_start.z;

						if (pt_end.y<pt_start.y)
							by = y <= pt_start.y;
						else
							by = y >= pt_start.y;
					}
					break;
				case 2:
					{
						if (pt_end.x<pt_start.x)
							bx = x <= pt_start.x;
						else
							bx = x >= pt_start.x;

						if (pt_end.z<pt_start.z)
							by = y <= pt_start.z;
						else
							by = y >= pt_start.z;
					}
					break;
				}

				this_continue_cutting += int(bx && by);
			}

			if(
				x == pt1.x && y == pt1.y
				)
			{
				// первая из входящих точек лежит на линии -
				// критерий не сработал
				first_point_on_line = true;
			}

			if(
				x == pt2.x && y == pt2.y
				)
			{
				// вторая из входящих точек лежит на линии -
				// критерий не сработал
				second_point_on_line = true;
			}

			//if (to_use_line_continue_cutting)
				thisCutting = thisCutting || (this_continue_cutting > 0);

//if (this_continue_cutting) printf("this_continue_cutting %d i = %d\n", this_continue_cutting, i);

			if(
				//-------------------------------
				thisCutting && 
				//-------------------------------
				x > min_x && 
				x < max_x && 

				y > min_y && 
				y < max_y  
				//-------------------------------
				)
			{
				nCutting++;
			}
		}
	}
	if (first_point_on_line || second_point_on_line)
	{
		if (first_point_on_line && second_point_on_line)
		{
			return 2; // обе точки сели на линию
		}
		else
		{
			if (first_point_on_line)
				return 3; // первая точка села налинию
			if (second_point_on_line)
				return 4; // вторая точка села на линию
		}
	}
	else
	{
		//if (nCutting > 0) printf("nCutting=  %d\n", nCutting);
		if (nCutting%2 == 1)
			// это значит, что данная линия разделяет две входящие точки
			return -1;
		else
			// а это значит, что две входящие точки лежат по одну сторону от данной линии
			return 1;
	}

	return 0;
}
#if 0
void Line3D::FreeMiddlePoints()
{
#if 1
	this->Primitive<CPoint3>::FreeMiddlePoints();
#else
printf("Line3D::FreeMiddlePoints()\n");
	vector<CPoint3>::iterator iter_v;
	vector<CPoint3>::iterator iter_d;
int i = 0;
	for(iter_v = m_vvPoints.begin(), iter_d = m_vdPoints.begin(); 
		iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end(); 
		iter_v++, iter_d++)
	{
printf("Line3D::FreeMiddlePoints() %d\n", i);
		m_vvPoints.erase(iter_v);
		m_vdPoints.erase(iter_d);
		this->m_nPoints--;
		i++;
	}
#endif
}
#endif
void Line3D::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_LINEFREEMIDDLEPOINTS, "&Free Middle Points" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_LINE_CLOSE, "&Close line" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_LINE_UNCLOSE, "&Unclose line" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_LINE_SHOWUNVISIBLE, "&Show Unvisible" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_LINE_HIDEUNVISIBLE, "&Hide Unvisible" );

	
	
#endif /*#if !VIEW_ONLY_VERSION*/
}
DWORD Line3D::Serialize(Archive& ar)
{
	if (ar.IsStoring())
	{
		ar << *this;
	}
	else
	{
		ar >> *this;
	}
	return 0;
}
Archive& operator <<(Archive& ar, Line3D& ob)
{
//printf("Archive& operator <<(Archive& ar, Line3D& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (version)
	{
	case 3:
		{
			ar << ob.podoshva;
		}
	case 2:
		{
			ar << ob.id_ige;
			ar << ob.id_umpoz;
			ar << ob.id_surf;//идентификатор для зранения поверхности в базе
		}
	case 1:
		{
			ar << ob.m_LineWidth;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, Line3D& ob)
{
//printf("Archive& operator >>(Archive& ar, Line3D& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 3:
		{
			ar >> ob.podoshva;
		}
	case 2:
		{
			ar >> ob.id_ige;
			ar >> ob.id_umpoz;
			ar >> ob.id_surf;//идентификатор для зранения поверхности в базе
		}
	case 1:
		{
			ar >> ob.m_LineWidth;
			ob.m_object_version = LINE3D_VERSION;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
	return ar;
}


bool Line3D::GetLineLength(double& ans)
{
	return false;
}


bool Line3D::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	if (!this->IsCheckedEx()) return false;
	search_radius = fabs(search_radius);
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_point
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		for ( size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			bool select = Distance(selected_view_pt, this->GetViewPoint(i) ) 
				<= 
				search_radius;
			if (select)
			{
				ws.Init(dynamic_cast<Object*>(this), 
					WhatSelected::sel_point,
					i,-1,
					selected_view_pt
					//,	this->GetDocumentPoint(i)
					);

				return true;
			}
		}
	}
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_line
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		double a = selected_view_pt.x;
		double b = selected_view_pt.y;
		double c = selected_view_pt.z;
		
		for ( size_t i2 = 1;  i2 < this->GetPointsNumber(); i2++)
		{
			size_t i1 = i2-1;

			double x1 = this->GetViewPoint(i1).x;
			double y1 = this->GetViewPoint(i1).y;
			double z1 = this->GetViewPoint(i1).z;

			double x2 = this->GetViewPoint(i2).x;
			double y2 = this->GetViewPoint(i2).y;
			double z2 = this->GetViewPoint(i2).z;

			double l = x2-x1;
			double m = y2-y1;
			double n = z2-z1;

			double dist_to_line = sqrt(
				pow( (a-x1)*m - (b-y1)*l, 2.) + 
				pow( (b-y1)*n - (c-z1)*m, 2.) + 
				pow( (c-z1)*l - (a-x1)*n, 2.) 
				) / (
				pow( l, 2.) + 
				pow( m, 2.) + 
				pow( n, 2.) 
				);

			//double dist1 = Distance(selected_view_pt, this->GetViewPoint(i1) );
			//double dist2 = Distance(selected_view_pt, this->GetViewPoint(i2) );

			double minx = min(x1,x2);
			double maxx = max(x1,x2);

			double miny = min(y1,y2);
			double maxy = max(y1,y2);

			double minz = min(z1,z2);
			double maxz = max(z1,z2);
#if 1
			bool in_borders = 
				a > minx - search_radius && a < maxx + search_radius &&
				b > miny - search_radius && b < maxy + search_radius &&
				c > minz - search_radius && c < maxz + search_radius;
#else
			bool in_borders = 
				a >= minx && a <= maxx &&
				b >= miny && b <= maxy &&
				c >= minz && c <= maxz;
#endif

			bool selected = dist_to_line < 3*search_radius && 
				//dist1 > search_radius && 
				//dist2 > search_radius &&  
				in_borders;

			if (selected)
			{
				ws.Init(
					dynamic_cast<Object*>(this), 
					WhatSelected::sel_line,
					i1,i2,
					selected_view_pt
					//, this->GetDocumentPoint(i1)
					);

				return true;
			}
		}
	}
	return false;
}


bool Line3D::IsSelectedDoc(CPoint3 selected_doc_pt, 
		double search_radius,
		double & dist_to_object,
		WhatSelected& ws)
{
	bool result = false;
	if (!this->IsCheckedEx()) return result;
	search_radius = fabs(search_radius);
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_point
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		for ( size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			double dist_to_point = Distance(selected_doc_pt, this->GetDocumentPoint(i) );
			
			bool select = dist_to_point	<= search_radius && dist_to_object > dist_to_point;
			

			if (select)
			{
				if (dist_to_object > dist_to_point)
					dist_to_object = dist_to_point;

				ws.Init(dynamic_cast<Object*>(this), 
					WhatSelected::sel_point,
					i,-1,
					selected_doc_pt
					//,	this->GetDocumentPoint(i)
					);

				result = true;
			}
		}
	}
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_line
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		double a = selected_doc_pt.x;
		double b = selected_doc_pt.y;
		double c = selected_doc_pt.z;
		
		for ( size_t i2 = 1;  i2 < this->GetPointsNumber(); i2++)
		{
			size_t i1 = i2-1;

			double x1 = this->GetDocumentPoint(i1).x;
			double y1 = this->GetDocumentPoint(i1).y;
			double z1 = this->GetDocumentPoint(i1).z;

			double x2 = this->GetDocumentPoint(i2).x;
			double y2 = this->GetDocumentPoint(i2).y;
			double z2 = this->GetDocumentPoint(i2).z;

			double l = x2-x1;
			double m = y2-y1;
			double n = z2-z1;

			double dist_to_line = sqrt(
				pow( (a-x1)*m - (b-y1)*l, 2.) + 
				pow( (b-y1)*n - (c-z1)*m, 2.) + 
				pow( (c-z1)*l - (a-x1)*n, 2.) 
				) / (
				pow( l, 2.) + 
				pow( m, 2.) + 
				pow( n, 2.) 
				);

			//double dist1 = Distance(selected_doc_pt, this->GetDocumentPoint(i1) );
			//double dist2 = Distance(selected_doc_pt, this->GetDocumentPoint(i2) );

			double minx = min(x1,x2);
			double maxx = max(x1,x2);

			double miny = min(y1,y2);
			double maxy = max(y1,y2);

			double minz = min(z1,z2);
			double maxz = max(z1,z2);

#if 1
			bool in_borders = 
				a > minx - search_radius && a < maxx + search_radius &&
				b > miny - search_radius && b < maxy + search_radius &&
				c > minz - search_radius && c < maxz + search_radius;
#else
			bool in_borders = 
				a >= minx && a <= maxx &&
				b >= miny && b <= maxy &&
				c >= minz && c <= maxz;
#endif


			bool selected = dist_to_line < 3*search_radius && 
				dist_to_object > dist_to_line &&
				//dist1 > search_radius && 
				//dist2 > search_radius &&  
				in_borders;
			

			if (selected)
			{
				if (dist_to_object > dist_to_line)
					dist_to_object = dist_to_line;
				ws.Init(
					dynamic_cast<Object*>(this), 
					WhatSelected::sel_line,
					i1,i2,
					selected_doc_pt
					//, this->GetDocumentPoint(i1)
					);

				result = true;
			}
		}
	}
	return result;
}

bool Line3D::IsSelectedLine(gdiplus_map_view * gv, Profile3D * on, int mouse_x, int mouse_y, double & dist_to_line_object, WhatSelected& ws)
{
	bool result = false;
	if (!this->IsCheckedEx()) return result;
	double search_radius = fabs(gv->lines_points_radius);
	gv->PreConvertingFromWorldToScreen();
	double dist_to_plane;
	CPoint2 profile;		
	fGL x, y;

	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_point
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		for ( size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			//Convert3D_To_2D
			on->Projection(m_vdPoints[i], profile, dist_to_plane);
			gv->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);	
			double dist_to_point = Distance(mouse_x, mouse_y, x, y);

			bool select = dist_to_line_object > dist_to_point;
			

			if (select)
			{
				if (dist_to_line_object > dist_to_point)
					dist_to_line_object = dist_to_point;
				ws.Init(dynamic_cast<Object*>(this), 
					WhatSelected::sel_point,
					i,-1,
					m_vdPoints[i]
					//,	this->GetDocumentPoint(i)
					);

				result = true;
			}
		}
	}
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_line
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		double a = mouse_x;
		double b = mouse_y;
		float x1, y1, x2, y2;
		if (0 < GetPointsNumber())
		{
			//Convert3D_To_2D
			on->Projection(m_vdPoints[0], profile, dist_to_plane);
			gv->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
		}

		for (UINT i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
		{
			if (
				m_vvPoints[i0].bVisible
				&& m_vvPoints[i1].bVisible && 
				!(m_vdPoints[i0].flag & CPOINT3_FLAG_HIDE_LINE) 
				)
			{
				
				//Convert3D_To_2D
				on->Projection(m_vdPoints[i1], profile, dist_to_plane);
				gv->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);
			{

				double dist_to_line = fabs(
					(a-x1)*(y2-y1) - (b-y1)*(y2-y1)
					) / (
					pow( x2-x1, 2) + 
					pow( y2-y1, 2) 
					);

	/*printf("dist_to_line = %f = %f / %f \n", dist_to_line, (a-x1)*(y2-y1) - (b-y1)*(y2-y1), pow( x2-x1, 2) + 
					pow( y2-y1, 2) );*/

				double minx = min(x1,x2);
				double maxx = max(x1,x2);

				double miny = min(y1,y2);
				double maxy = max(y1,y2);

	#if 1
				bool in_borders = 
					a > minx - search_radius && a < maxx + search_radius &&
					b > miny - search_radius && b < maxy + search_radius ;
	#else
				bool in_borders = 
					a >= minx && a <= maxx &&
					b >= miny && b <= maxy;
	#endif

				bool selected = 
					dist_to_line_object > dist_to_line &&
					in_borders;
				

				if (selected)
				{
					if (dist_to_line_object > dist_to_line)
						dist_to_line_object = dist_to_line;
					ws.Init(
						dynamic_cast<Object*>(this), 
						WhatSelected::sel_line,
						i0,i1,
						m_vdPoints[i0]
						//, this->GetDocumentPoint(i0)
						);

					result = true;
				}
			}					
			}
			x1 = x2;
			y1 = y2;
		}
		

	}
	return result;
}




bool Line3D::FindIntersection(Profile3D * on, CPoint3 pt1, CPoint3 pt2, CPoint3 & pti, int & _i1, int & _i2, int & unvisibles, int & dst_to_vis)
{
	if (!on) return false;

	CPoint3 center;
	center.x = (pt1.x + pt2.x) / 2.0;
	center.y = (pt1.y + pt2.y) / 2.0;
	center.z = (pt1.z + pt2.z) / 2.0; 

	double dist_to_plane;
	CPoint2 profile1;		
	CPoint2 profile2;		
	//Convert3D_To_2D
	on->Projection(pt1, profile1, dist_to_plane);
	on->Projection(pt2, profile2, dist_to_plane);

	double x1 = profile1.x;
	double y1 = profile1.y;

	double x2 = profile2.x;
	double y2 = profile2.y;

	//Находим уравнение прямой проходящих через две точки в виде
	// Ax + By + C = 0
	double A1, B1, C1;

	A1 = y1-y2;
	B1 = x2-x1;
	C1 = x1*(y2-y1)-y1*(x2-x1);

	double current_dist_to_center = DBL_MAX;
	bool result = false;
	CPoint3 _pti;
	int _unvisibles, _dst_to_vis;

	for (size_t i2 = 1;  i2 < this->GetPointsNumber(); i2++)
	{
		size_t i1 = i2-1;

#if 0
		// также используем отрезок на краю бланкования 
		if (!this->GetDocumentPoint(i1).bVisible && !this->GetDocumentPoint(i2).bVisible)
			continue;
#else
		_unvisibles = 0;
		if (!this->GetDocumentPoint(i1).bVisible) ++_unvisibles;
		if (!this->GetDocumentPoint(i2).bVisible) ++_unvisibles;

		_dst_to_vis = 0;
		if (_unvisibles == 2)
		{
			int dst_to_vis_1 = 0;
			for (int __i1 = i1; __i1 >= 0; --__i1, ++dst_to_vis_1)
			{
				if (this->GetDocumentPoint(__i1).bVisible)
					break;
			}
			int dst_to_vis_2 = 0;
			for (int __i2 = i2; __i2 < this->GetPointsNumber(); ++__i2, ++dst_to_vis_2)
			{
				if (this->GetDocumentPoint(__i2).bVisible)
					break;
			}

			_dst_to_vis = min(dst_to_vis_1, dst_to_vis_2);
		}
#endif

		CPoint2 profile_1;		
		CPoint2 profile_2;	

		//Convert3D_To_2D
		on->Projection(this->GetDocumentPoint(i1), profile_1, dist_to_plane);
		on->Projection(this->GetDocumentPoint(i2), profile_2, dist_to_plane);


		double x_1 = profile_1.x;
		double y_1 = profile_1.y;

		double x_2 = profile_2.x;
		double y_2 = profile_2.y;

		//Находим уравнение прямой проходящих через две точки в виде
		// Ax + By + C = 0
		double A2, B2, C2;

		A2 = y_1-y_2;
		B2 = x_2-x_1;
		C2 = x_1*(y_2-y_1)-y_1*(x_2-x_1);

		// Ищем пересечение двух прямых на плоскости
		double det = A1 * B2 - A2 * B1;

		if (fabs(det) > 1e-8)
		{
			double det_x = B1*C2 - C1*B2;
			double det_y = C1*A2 - A1*C2;

			double x = det_x / det;
			double y = det_y / det;						

			if (on->Convert2D_To_3D(CPoint2(x,y), _pti))
			{
				double x1 = this->GetDocumentPoint(i1).x;
				double y1 = this->GetDocumentPoint(i1).y;
				double z1 = this->GetDocumentPoint(i1).z;

				double x2 = this->GetDocumentPoint(i2).x;
				double y2 = this->GetDocumentPoint(i2).y;
				double z2 = this->GetDocumentPoint(i2).z;

				double minx = min(x1,x2);
				double maxx = max(x1,x2);

				double miny = min(y1,y2);
				double maxy = max(y1,y2);

				double minz = min(z1,z2);
				double maxz = max(z1,z2);

				bool in_borders = 
					_pti.x >= minx && _pti.x <= maxx &&
					_pti.y >= miny && _pti.y <= maxy &&
					_pti.z >= minz && _pti.z <= maxz;

				if (in_borders)
				{
					double dist_to_center = Distance_xy(center, _pti);
					if (dist_to_center < current_dist_to_center)
					{
						_i1 = (int)i1;
						_i2 = (int)i2;
						pti = _pti;
						unvisibles = _unvisibles;
						dst_to_vis = _dst_to_vis;

						current_dist_to_center = dist_to_center;
						result = true;
					}
				}
			}
		}
	}
	return result;
}




void Line3D_PrintfProperties(Line3D * ob, vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Line3D");
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "id_surf = %d", ob->id_surf);
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "id_umpos = %d", ob->id_umpoz);
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "id_ige = %d", ob->id_ige);
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "podoshva = %d", ob->podoshva);
	text.push_back(fmtstr(str, NULL, false, true));

	sprintf(str, "\"%s\"", ob->GetName().c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	for (size_t ipoint = 0; ipoint < ob->GetPointsNumber(); ipoint++)
	{		
		sprintf(str, "%d", ipoint);
		text.push_back(fmtstr(str, NULL, false, true));

		sprintf(str, "%f", ob->m_vdPoints[ipoint].x); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		sprintf(str, "%f", ob->m_vdPoints[ipoint].y); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		sprintf(str, "%f", ob->m_vdPoints[ipoint].z); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		sprintf(str, "%d", ob->m_vdPoints[ipoint].bVisible); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));
	}
}

void Line3D::PrintfProperties(vector<fmtstr> & text)
{
	Line3D_PrintfProperties(this, text);
}

void Line3D::PrintfProperties(vector<LabData> & labdata)
{
	labdata.push_back(LabData());
	Line3D_PrintfProperties(this, labdata.back().text);
}
