// Well_3D.cpp: implementation of the Well_3D class.
//
//////////////////////////////////////////////////////////////////////
#include "../../surfer_connect/StdAfx.h"
#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>			// MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#include "../../stdafx.h"
#include "Well_3D.h"
//#include "../../raporto.h"
#include "SurfDoc.h"
#include ".\well_3d.h"
#include "../../surfdefs.h"
#include "winsurftree.h"

#include "../../array/src/spline3.h"
#include "distance3D.h"
#include ".\whatselected.h"
#include "../tools/src/errorexit.h"

#include "../../lab/lab/labdoc.h"

#include <winnls.h>

int Karotazh::slices = 10;
int Karotazh::stacks = 1;

bool Karotazh::s_logarithmic_scale = false;
bool Karotazh::s_scale_from_zero = false;
double Karotazh::s_scale = 0.1;
double Karotazh::s_scale_2d = 1.0;
int Karotazh::s_alpha = 125;
bool Karotazh::s_checked = true;
bool Karotazh::s_disp_point_values = false;
bool Karotazh::s_disp_point_values_2d = false;


vector<karotazh_list_item> Well_3D::karotazh_list;


vector<wells_draw_list_item *> Well_3D::wells_draw_list;


bool Well_3D::draw2d_center = true;
COLORREF Well_3D::center_color = RGB(0,0,0);
DashStyle Well_3D::dashStyle = DashStyleDashDot;
float Well_3D::dashOffset = 20;

	
void InitWellDrawList()
{
//	Well_3D::wells_draw_list.push_back(wells_draw_list_item(WellElement::type::primitive_ref, false, 8.f));
}
//bool Well_3D::draw_primitive	= false;
//bool Well_3D::draw_ige			= true;
//bool Well_3D::draw_hydro		= false;
//bool Well_3D::draw_issand		= false;

float Well_3D::width_karotazh = 2.f;
//float Well_3D::width_primitive = 8.f;
//float Well_3D::width_ige = 4.f;
//float Well_3D::width_hydro = 2.f;
//float Well_3D::width_issand = 2.f;

Karotazh::Karotazh() //: Primitive3D<CPoint4>()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
Karotazh::Karotazh(SurfDoc * pSurfDoc) //: Primitive3D<CPoint4>()
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
Karotazh::Karotazh(SurfDoc * pSurfDoc, const char * _name) //: Primitive3D<CPoint4>()
{
	m_pSurfDoc = pSurfDoc;
	name = _name;
	OnCreate();
}

void Karotazh::OnCreate(void)
{
	this->m_object_type = Object::object_type::karotazh;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_bIsPrimitive3 = false;
	this->m_bIsPrimitive4 = true;

	m_color = 0;

	this->m_min_v = DBL_MAX;
	this->m_max_v = -DBL_MAX;
	this->m_index = -1;
}

void Karotazh::Init(const Karotazh& ob)
{
	this->m_min_v = ob.m_min_v;
	this->m_max_v = ob.m_max_v;
	this->m_index = ob.m_index;
}

Karotazh::Karotazh(const Karotazh& ob) : Primitive3D<CPoint4>(ob) 
{
	this->Object::Init(ob);
	this->Primitive3D<CPoint4>::Init(ob);
	this->Init(ob);
}

Karotazh& Karotazh::operator=(const Karotazh& ob)
{
	if (this == &ob)
		return *this;

	this->Object::Init(ob);
	this->Primitive3D<CPoint4>::Init(ob);
	this->Init(ob);

	return *this;
}

HTREEITEM Karotazh::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	sprintf(szItemText, "Karotazh %s len = %d color = %u", 
		GetName().c_str(), GetPointsNumber(), m_color);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}

void Karotazh::Drawing()
{
	if (m_pSurfDoc)
	{
		if (GetPointsNumber() > 0 && m_vvPoints[0].bVisible)
		{
			if (this->m_index < Well_3D::karotazh_list.size() && Well_3D::karotazh_list[this->m_index].disp_point_values)
			{
				for (size_t i = 0; i < GetPointsNumber(); i++)
				{
					if(m_vvPoints[i].bVisible)
					{
						{
							//glPointSize(1.0);
							glPointSize(ThePoint3D::point_size);
							//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
							
							glBegin(GL_POINTS);
							//glColor3ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)); 
							glColor3ub (255,0,0); 
							//glVertex3fv((* it1).GetCRD(n1));

							glVertex3d (m_vvPoints[i].x, 
										m_vvPoints[i].y, 
										m_vvPoints[i].z);

							glEnd();
							
							//glPopName(); glPopName();
						}

						char str[1024];
						if ( Well_3D::karotazh_list[this->m_index].logarithmic_scale)
							sprintf(str, "%f\0", log10(m_vdPoints[i].v));
						else
							sprintf(str, "%f\0", m_vdPoints[i].v);

						int j = strlen(str)-1;
						while (j > 0 && str[j] == '0') str[j--] = '\0';

						// label color
						COLORREF color = RGB(0,0,255);
						::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку
						// sprintf(str, "X %s", spower);
						// move 
						glRasterPos3d(m_vvPoints[i].x, m_vvPoints[i].y, m_vvPoints[i].z ); 
						// set up for a string-drawing display List call 
						// Display a string 
						glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
						// Draw the characters in a string 
						glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

					}
				}
			}
			
			if (this->m_index < Well_3D::karotazh_list.size())
			{
				m_color = Well_3D::karotazh_list[this->m_index].color;
				m_alpha = Well_3D::karotazh_list[this->m_index].alpha;
			}

			glColor4ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color), (GLubyte)m_alpha); 

			GLUquadricObj* pCylinder = gluNewQuadric();
			gluQuadricDrawStyle(pCylinder, GLU_FILL);
			gluQuadricNormals(pCylinder,GLU_SMOOTH);
			
			for (size_t i0 = 1, i1 = 2 ; i1 < GetPointsNumber(); i0++, i1++)
			{
				if(m_vvPoints[i0].bVisible
					&& m_vvPoints[i1].bVisible)
				{
					/*Line3(
						m_vvPoints[i1].x, 
						m_vvPoints[i1].y, 
						m_vvPoints[i1].z,
						m_vvPoints[i0].x, 
						m_vvPoints[i0].y,	
						m_vvPoints[i0].z);*/

					GLdouble height = m_vvPoints[i0].z - m_vvPoints[i1].z;
					GLdouble top_radius = m_vvPoints[i0].v;
					GLdouble base_radius = m_vvPoints[i1].v;

					//printf("height = %f, base_radius = %f, top_radius = %f\n", 
					//	height, base_radius, top_radius);

					glPushMatrix();//перейдём к новым координатам, сохранив старые
					//glRotated(5.0, 0.0, 1.0, 5.0);//повернём
					glTranslated(m_vvPoints[i1].x, m_vvPoints[i1].y, m_vvPoints[i1].z);
					gluCylinder(pCylinder, base_radius, top_radius, height, Karotazh::slices, Karotazh::stacks);
					glPopMatrix(); //возвращаемся к старым координатам 
				}
			}

			gluDeleteQuadric(pCylinder);
		}
	}
}



#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"

double Karotazh::Zoom_GDIplus(double vd)
{
		
	double vmin, vv;

	if (this->m_index < 0 || this->m_index >= Well_3D::karotazh_list.size())
		return 0.0;

	if (Well_3D::karotazh_list[this->m_index].scale_from_zero)
	{
		vmin = 0.0;
		if (Well_3D::karotazh_list[this->m_index].vmin < 0.0)
		{
			char str[1024];
			sprintf(str, "Can not Scale from zero because VMIN = %f < 0.0\n", Well_3D::karotazh_list[this->m_index].vmin);
			printf(str);
			MessageBox(0, str, "Karotazh::Zoom", 0);

			vmin = Well_3D::karotazh_list[this->m_index].vmin;
		}
	}
	else vmin = Well_3D::karotazh_list[this->m_index].vmin;

	/*printf("Karotazh::Zoom index = %d vmin = %f scale_from_zero = %d logarithmic_scale = %d scale = %f\n", 
		this->m_index, 
		vmin, 
		Well_3D::karotazh_list[this->m_index].scale_from_zero,
		Well_3D::karotazh_list[this->m_index].logarithmic_scale,
		Well_3D::karotazh_list[this->m_index].scale);*/

	
	vv = 				
		Well_3D::karotazh_list[this->m_index].scale_2d * (Well_3D::karotazh_list[this->m_index].logarithmic_scale ?
		log10(vd - vmin ) / log10(Well_3D::karotazh_list[this->m_index].vmax - vmin)
		:
		(vd - vmin ) / (Well_3D::karotazh_list[this->m_index].vmax - vmin)
		);

			
		
	return vv;


}

void Karotazh::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	if (GetPointsNumber() < 2) return;

	v->PreConvertingFromWorldToScreen();
	
	fGL r = v->lines_points_radius;


	if (m_pSurfDoc)
	{
		if (GetPointsNumber() > 0 && m_vvPoints[0].bVisible)
		{
			if (this->m_index < Well_3D::karotazh_list.size())
			{
				m_color = Well_3D::karotazh_list[this->m_index].color;
				m_alpha = Well_3D::karotazh_list[this->m_index].alpha;
			}
			
			for (size_t i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
			{
				if(m_vvPoints[i0].bVisible
					&& m_vvPoints[i1].bVisible)
				{
					//COLORREF color = 0;
					Color gdi_color(m_alpha, GetRValue(m_color),GetGValue(m_color),GetBValue(m_color));
					Pen      pen(gdi_color);							
					pen.SetWidth(Well_3D::width_karotazh);	

					//Convert3D_To_2D
					on->Projection(m_vdPoints[i1], profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

					//Convert3D_To_2D
					on->Projection(m_vdPoints[i0], profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

					if (this->m_index >= 0 && this->m_index < Well_3D::karotazh_list.size())
					{
						GLdouble top_radius = 100. * this->Zoom_GDIplus(m_vdPoints[i0].v) * v->get_x_scale();
						GLdouble base_radius = 100. * this->Zoom_GDIplus(m_vdPoints[i1].v) * v->get_x_scale();
						
						if (Well_3D::karotazh_list[this->m_index].m_draw_mode_2d == karotazh_list_item::draw_mode_2d::right
							||
							Well_3D::karotazh_list[this->m_index].m_draw_mode_2d == karotazh_list_item::draw_mode_2d::both)
							graphics.DrawLine(&pen, x1 + base_radius, y1, x2 + top_radius, y2);

						if (Well_3D::karotazh_list[this->m_index].m_draw_mode_2d == karotazh_list_item::draw_mode_2d::left
							||
							Well_3D::karotazh_list[this->m_index].m_draw_mode_2d == karotazh_list_item::draw_mode_2d::both)
							graphics.DrawLine(&pen, x1 - base_radius, y1, x2 - top_radius, y2);
						
						if (Well_3D::karotazh_list[this->m_index].disp_point_values_2d)
						{
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							size_t i = i1;

							char str[128];
							if (Well_3D::karotazh_list[this->m_index].logarithmic_scale)
								sprintf(str, "%f\0", log10(m_vdPoints[i].v));
							else
								sprintf(str, "%f\0", m_vdPoints[i].v);

							int j = strlen(str)-1;
							while (j > 0 && str[j] == '0') str[j--] = '\0';

							if (str[strlen(str)-1] == '.')
								str[strlen(str)-1] = '\0';
				
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//====== Наносим цифровую метку устья
							SolidBrush  brush(Color(/*m_alpha*/ 255, GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)));
							FontFamily  fontFamily(L"Times New Roman");
							Font        font(&fontFamily, 9, FontStyleRegular, UnitPixel);
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							double x_label;
							switch(Well_3D::karotazh_list[this->m_index].m_draw_mode_2d)
							{
							case karotazh_list_item::draw_mode_2d::both:
							case karotazh_list_item::draw_mode_2d::right:
								{
									x_label = x1 + base_radius + font.GetHeight(&graphics);
								}
								break;
							case karotazh_list_item::draw_mode_2d::left:
								{
									x_label = x1 - base_radius - (strlen(str) + 2) * font.GetHeight(&graphics) * 0.5;
								}
								break;
							}
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

							const size_t wlen = 2 + 2 * strlen(str);
							WCHAR * wb = new WCHAR[wlen];
							MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wb, wlen );
							graphics.DrawString(wb, -1, &font, PointF(x_label, y1), &brush);
							delete wb;
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
							//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						}
					}
				}
			}
		}
	}
}

void Karotazh::GetKarotazhCube(double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz)
{
	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		if(m_vdPoints[i].bVisible)
		{
			if ( minx > m_vdPoints[i].x)  minx = m_vdPoints[i].x;
			if ( miny > m_vdPoints[i].y)  miny = m_vdPoints[i].y;
			if ( minz > m_vdPoints[i].z)  minz = m_vdPoints[i].z;

			if ( maxx < m_vdPoints[i].x)  maxx = m_vdPoints[i].x;
			if ( maxy < m_vdPoints[i].y)  maxy = m_vdPoints[i].y;
			if ( maxz < m_vdPoints[i].z)  maxz = m_vdPoints[i].z;
		}
	}
}
#include "../../winplot/src/winplot.h"
int __cdecl compare_CPoint2_X( const void *arg1, const void *arg2 )
{
   /* Compare X: */
   double 
	   x1 = (( CPoint2* ) arg1)->x,
	   x2 = (( CPoint2* ) arg2)->x;
   if (x1 < x2)
	   return -1;
   if (x1 == x2)
	   return 0;
   if (x1 > x2)
	   return 1;
   return 0;
}
void Karotazh::PutKarotazhSlicesPoint(Karotazh::linterp_method int_meth, vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked)
{
	switch(int_meth)
	{
	case Karotazh::linterp_method::linear:
		PutKarotazhSlicesPoint_Linear(vks, ked);
		break;
	case Karotazh::linterp_method::spline:
		PutKarotazhSlicesPoint_Spline(vks, ked);
		break;
	}
}
	
void Karotazh::PutKarotazhPoints(vector<double> & vxk, vector<double> & vyk, vector<double> & vzk, vector<double> & vvk)
{
	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		vxk.push_back(m_vdPoints[i].x);
		vyk.push_back(m_vdPoints[i].y);
		vzk.push_back(m_vdPoints[i].z);
		vvk.push_back(m_vdPoints[i].v);
	}
}

void Karotazh::PutKarotazhSlicesPoint_Linear(vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked)
{

	vector<vector<double> > xx(2), yy(2);



	ap::real_1d_array x;
	ap::real_1d_array y;

	int n = int (GetPointsNumber())-1;
		
	printf("Karotazh::PutKarotazhSlicesPoint %d\n", n);

	if (n < 1) return;

	double min_z = DBL_MAX;
	double max_z = -DBL_MAX;

	double lowest_value;

	double X,Y;
	X = m_vdPoints[0].x;
	Y = m_vdPoints[0].y;
	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		if (min_z > m_vdPoints[i].z) {min_z = m_vdPoints[i].z; lowest_value = m_vdPoints[i].v;}
		if (max_z < m_vdPoints[i].z) max_z = m_vdPoints[i].z;		
	}


	x.setbounds(0, n);
	y.setbounds(0, n);
	
	CPoint2 * vp2 = new CPoint2[GetPointsNumber()];

	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		vp2[i].x = m_vdPoints[i].z;
		if ( Well_3D::karotazh_list[this->m_index].logarithmic_scale)
		{
			vp2[i].y = log10(m_vdPoints[i].v);
		}	
		else
			vp2[i].y = m_vdPoints[i].v;
	}
	qsort((void *)vp2,GetPointsNumber(), sizeof(CPoint2), compare_CPoint2_X);

	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		x(i) = vp2[i].x;
		y(i) = vp2[i].y;
		xx[0].push_back(x(i));
		yy[0].push_back(y(i));

		printf("x(%u) = %f y(%u) = %f\n", i, x(i), i, y(i));
	}
	delete[] vp2;


	for (vector<karotazh_slice>::iterator it = vks.begin(); it != vks.end(); it++)
	{
		if ( (*it).z >= min_z && (*it).z <= max_z)
		{
			int j = 1;
			while (j <= n && x(j) < (*it).z)
			{
				j++;
			}
			double alfa = ((*it).z-x(j-1))/(x(j)-x(j-1));
			double v = y(j-1) + alfa * (y(j) - y(j-1));

			(*it).vv.push_back(v);
			(*it).vx.push_back(X);
			(*it).vy.push_back(Y);

			xx[1].push_back((*it).z);
			yy[1].push_back(v);
		}
		else if (ked.to_extrapolate_down)
		{
			switch(ked.m_extrapolate_down_method)
			{
			case karotazh_extrapolate_down::extrapolate_down_method::with_lowest_value:
				{
					if ( (*it).z < min_z && (*it).z >= min_z - ked.extrapolation_len)
					{
						(*it).vv.push_back(lowest_value);
						(*it).vx.push_back(X);
						(*it).vy.push_back(Y);

						xx[1].push_back((*it).z);
						yy[1].push_back(lowest_value);
					}
				}
				break;
			case karotazh_extrapolate_down::extrapolate_down_method::continue_interpolation:
				{
					if ( (*it).z < min_z && (*it).z >= min_z - ked.extrapolation_len)
					{
						int j = 1;
						while (j <= n && x(j) < (*it).z)
						{
							j++;
						}
						double alfa = ((*it).z-x(j-1))/(x(j)-x(j-1));
						double v = y(j-1) + alfa * (y(j) - y(j-1));

						(*it).vv.push_back(v);
						(*it).vx.push_back(X);
						(*it).vy.push_back(Y);

						xx[1].push_back((*it).z);
						yy[1].push_back(v);
					}
				}
				break;
			}
		}
	}

	//WinPlot(xx,yy);
}


void Karotazh::PutKarotazhSlicesPoint_Spline(vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked)
{
	vector<vector<double> > xx(2), yy(2);



	ap::real_1d_array x;
	ap::real_1d_array y;

	int n = int (GetPointsNumber())-1;
		
	printf("Karotazh::PutKarotazhSlicesPoint %d\n", n);

	if (n < 1) return;

	double min_z = DBL_MAX;
	double max_z = -DBL_MAX;
	double lowest_value;
	double X,Y;
	X = m_vdPoints[0].x;
	Y = m_vdPoints[0].y;
	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		if (min_z > m_vdPoints[i].z) {min_z = m_vdPoints[i].z; lowest_value = m_vdPoints[i].v;}
		if (max_z < m_vdPoints[i].z) max_z = m_vdPoints[i].z;		
	}


	x.setbounds(0, n);
	y.setbounds(0, n);
	
	CPoint2 * vp2 = new CPoint2[GetPointsNumber()];

	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		vp2[i].x = m_vdPoints[i].z;
		if ( Well_3D::karotazh_list[this->m_index].logarithmic_scale)
		{
			vp2[i].y = log10(m_vdPoints[i].v);
		}	
		else
			vp2[i].y = m_vdPoints[i].v;
	}
	qsort((void *)vp2,GetPointsNumber(), sizeof(CPoint2), compare_CPoint2_X);

	for (size_t i = 0; i < GetPointsNumber(); i++)
	{
		x(i) = vp2[i].x;
		y(i) = vp2[i].y;
		xx[0].push_back(x(i));
		yy[0].push_back(y(i));

		printf("x(%u) = %f y(%u) = %f\n", i, x(i), i, y(i));
	}
	delete[] vp2;

#if 1
	int diffn = 2;
	double boundl = 0.0;
	double boundr = 0.0;
#else
	int diffn = 1;
	double boundl = (y(1) - y(0)) / (x(1) - x(0));
	double boundr = (y(n) - y(n-1)) / (x(n) - x(n-1));
#endif
	ap::real_2d_array ctbl;
	spline3buildtable(n,diffn,x,y,boundl,boundr,ctbl);
	for (vector<karotazh_slice>::iterator it = vks.begin(); it != vks.end(); it++)
	{
		if ( (*it).z >= min_z && (*it).z <= max_z)
		{
			double v = spline3interpolate(n, ctbl, (*it).z);
			(*it).vv.push_back(v);
			(*it).vx.push_back(X);
			(*it).vy.push_back(Y);

			xx[1].push_back((*it).z);
			yy[1].push_back(v);
		}
		else if (ked.to_extrapolate_down)
		{
			switch(ked.m_extrapolate_down_method)
			{
			case karotazh_extrapolate_down::extrapolate_down_method::with_lowest_value:
				{
					if ( (*it).z < min_z && (*it).z >= min_z - ked.extrapolation_len)
					{
						(*it).vv.push_back(lowest_value);
						(*it).vx.push_back(X);
						(*it).vy.push_back(Y);

						xx[1].push_back((*it).z);
						yy[1].push_back(lowest_value);
					}
				}
				break;
			case karotazh_extrapolate_down::extrapolate_down_method::continue_interpolation:
				{
					if ( (*it).z < min_z && (*it).z >= min_z - ked.extrapolation_len)
					{
						double v = spline3interpolate(n, ctbl, (*it).z);

						(*it).vv.push_back(v);
						(*it).vx.push_back(X);
						(*it).vy.push_back(Y);

						xx[1].push_back((*it).z);
						yy[1].push_back(v);
					}
				}
				break;
			}
		}
	}
	//WinPlot(xx,yy);
}


void Karotazh::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "Karotazh" , 0);

}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

int Well_3D::s_sloj_number_to_save = -1;
bool Well_3D::s_use_sloj_names = true;
bool Well_3D::s_show_all_sloi = false;

Well_3D::Well_3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
Well_3D::Well_3D(SurfDoc * pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
void Well_3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::well_3d;
	this->m_object_version = 4;
	this->m_max_object_version = 4;

	m_color = 0;
	m_type = 1;

	this->m_karotazhy.OnCreate();

	if (this->m_pSurfDoc && this->m_pSurfDoc->m_wdli_primitive)
	{
		AddNewWellColomn(WellElement::type::primitive_ref, this->m_pSurfDoc->m_wdli_primitive);
	}
	if (this->m_pSurfDoc && this->m_pSurfDoc->m_wdli_laboratory)
	{
		AddNewWellColomn(WellElement::type::laboratory_analizes, this->m_pSurfDoc->m_wdli_laboratory);
	}

	m_nglListNumber_Primitive = 0;

	this->m_id_kt				= -1;
	this->m_kt_idtyp			= -1;
	this->m_id_bur_type			= -1;
	this->m_d_bur = 0;
	this->m_data_bur = "";

	this->m_w                   = 1.0; 


}
	
void Well_3D::ClearKarotazhy()
{
	this->m_karotazhy.clear();
}

int Well_3D::GetKarotazhIndex(const char * name)
{
	int kar_index = -1;

	for (int i = 0; i < Well_3D::karotazh_list.size(); i++)
	{
		if (strcmp(karotazh_list[i].name.c_str(), name) == 0)
		{
			kar_index = i;
			break;
		}
	}

	return kar_index;
}

Well_3D::~Well_3D()
{
	if (m_nglListNumber_Primitive > 0)
	{
		::glDeleteLists(m_nglListNumber_Primitive,1);
	}
	m_nglListNumber_Primitive = 0;
}

int Well_3D::CompareWellID(Well_3D& ob)
{
#if USE_STRING_IN_THE_CELL
	return strcmp(this->sID.c_str(), ob.sID.c_str());
#else
	return strcmp(this->sID, ob.sID);
#endif
}
void Well_3D::AddNewWellColomn_LaboratoryAnalizes()
{
	WellColomn * wc = FindWellColomn(WellElement::type::laboratory_analizes);
	if (!wc)
	{
		int ind = -1;
		if (this->m_pSurfDoc && this->m_pSurfDoc->m_wdli_laboratory)
		{
			ind = AddNewWellColomn(WellElement::type::laboratory_analizes, this->m_pSurfDoc->m_wdli_laboratory);
		}
		if (ind > -1)
		{
			wc = &this->well_colomns[ind];
		}
	}
	wc->clear();
}
/*WellColomn * Well_3D::AddWellColomn(WellElement::type t)
{
	WellColomn * wc = FindWellColomn(t);
	if (wc) return wc;

	return this->AddNewWellColomn(t);
}*/
int Well_3D::AddNewWellColomn(WellElement::type t, wells_draw_list_item * wdli)
{
	this->well_colomns.push_back(WellColomn(t, this, wdli));
	return this->well_colomns.size()-1;
	//return &well_colomns[this->well_colomns.size()-1];
}
bool Well_3D::WellInit2(vector<vector<cell> >::iterator pdrill,
				   vector<cell> * karotazh_glubin,
					vector<int> * types_of_colomns,
					vector<string> * pnames_of_colomns,
					vector<COLORREF> * colors_of_sloi,
					char* filename,
					wells_draw_list_item * wdli_podoshva, bool is_ige,
					wells_draw_list_item * wdli_hydro,
					bool  to_realloc)
{

	if (!wdli_podoshva) to_realloc = true;

	//printf("Well_3D::Init\n");
	m_type = 2;
	double X,Y;
	if (to_realloc)
	{
		this->Free();this->m_vColor.clear();this->m_vstrSloiNames.clear();
		// две точки - первая устье, вторая - забой
		this->AllocPoints(2);
		this->m_vColor.resize(2,RGB(0,0,0));
		this->m_vstrSloiNames.resize(2);
	}

	this->m_vstrSloiNames[0] = "zaboj";
	this->m_vstrSloiNames[1] = "ustje";


	//printf("m_vstrSloiNames.size() = %d\n", m_vstrSloiNames.size());

	m_vdPoints[0].bVisible = true;
	m_vdPoints[1].bVisible = true;
	m_vvPoints[0].bVisible = true;
	m_vvPoints[1].bVisible = true;

	// determine colomns types
	vector<int>::iterator iter_types_col;
	UINT icol;
	// итератор по ячейкам таблицы
	vector<cell>::iterator iter_cell;
	vector<cell>::iterator iter_karotazh_glubin;
	bool to_init_zaboj_as_ustje = true;
	bool ustje_is_determined = false;

	int kar_index = -1;

	if (karotazh_glubin)
	{
		m_karotazhy.AddMsg(&Karotazh(this->m_pSurfDoc, filename));
		kar_index = Well_3D::karotazh_list.size()-1;					
		m_karotazhy.GetLastMsg().m_index = kar_index;
	}

	int i_colomn_podoshva = -1;
	if (wdli_podoshva)
	{
		if(is_ige)
			i_colomn_podoshva = this->AddNewWellColomn(WellElement::type::IGE_podoshva, wdli_podoshva);
		else
			i_colomn_podoshva = this->AddNewWellColomn(WellElement::type::litho_podoshva, wdli_podoshva);
	}
	int i_colomn_hydro_projavlenie = -1;
	if (wdli_hydro)
		i_colomn_hydro_projavlenie = this->AddNewWellColomn(WellElement::type::hydro_projavlenie, wdli_hydro);


	WellColomn * w_colomn_podoshva = NULL;
	WellColomn * w_colomn_hydro_projavlenie = NULL;
	if (i_colomn_podoshva > -1)
		w_colomn_podoshva = &this->well_colomns[i_colomn_podoshva];
	if (i_colomn_hydro_projavlenie > -1)
		w_colomn_hydro_projavlenie = &this->well_colomns[i_colomn_hydro_projavlenie];


	double zk = DBL_MAX;//кровля
	
			
	if (karotazh_glubin) iter_karotazh_glubin = karotazh_glubin->begin(); 

	for( 
		iter_types_col = types_of_colomns->begin(), 
			icol = 0, 
			iter_cell = pdrill->begin();

		iter_types_col != types_of_colomns->end() && 
			iter_cell != pdrill->end() &&
			(karotazh_glubin ? iter_karotazh_glubin != karotazh_glubin->end() : true); 

		iter_types_col++, 
			icol++, 
			iter_cell++ 
		)
	{

		cell temp = *iter_cell;
		switch (*iter_types_col)
		{
		case 0:
			{
				// this colomn not used
			}
			break;
		case 1:
			{
				// this colomn have well ID value
				// ncol_well_id = icol;
#if USE_STRING_IN_THE_CELL
				sID = temp.str;
#else
				size_t len_of_str = min(CELL_S_N_CHARS - 1, strlen(temp.s));
				strncpy(sID,
					temp.s,
					len_of_str);
				sID[len_of_str] = '\0';
#endif
			}
			break;
		case 2://X
			{
				X = temp.value;
				m_vdPoints[0].x = temp.value;
				m_vvPoints[0].x = temp.value;
				m_vdPoints[1].x = temp.value;
				m_vvPoints[1].x = temp.value;
			}
			break;
		case 3://Y
			{
				Y = temp.value;
				m_vdPoints[0].y = temp.value;
				m_vvPoints[0].y = temp.value;
				m_vdPoints[1].y = temp.value;
				m_vvPoints[1].y = temp.value;
			}
			break;
		case 4://ustje altitude
			{
				m_vdPoints[1].z = temp.value;
				m_vvPoints[1].z = temp.value;
				if(to_init_zaboj_as_ustje)
				{
					//инициализируем забой на случай если не дана глубина забоя
					m_vdPoints[0].z = temp.value;
					m_vvPoints[0].z = temp.value;
				}
				zk = temp.value;
				ustje_is_determined = true;
			}
			break;
		case 5://sloi podoshva altitude
			{
				CPoint3 pt;
#if USE_STRING_IN_THE_CELL
				size_t slen = strlen(temp.str.c_str());
#else
				size_t slen = strlen(temp.s);
#endif
				if (slen > 0)
				{
					//this cell not empty
					pt.bVisible = true;
					pt.z		= temp.value;
					pt.x		= X;
					pt.y		= Y;

					if (m_vdPoints[0].z > pt.z)
						m_vdPoints[0].z = pt.z;
				}
				else
				{
					//this cell is empty
					pt.bVisible = false;
				}
				if (w_colomn_podoshva)
				{
					printf("w_colomn_ige_podoshva->GetWellElementType() = %d\n",(int)w_colomn_podoshva->GetWellElementType());
					if (slen > 0)
					{
						char str[512];
						strcpy(str,pnames_of_colomns->operator [](icol).c_str());
						// deleting ""
						char * p = str;
						while ( (*p) == '"') p++;
						while (p[strlen(p)-1] == '"') p[strlen(p)-1] = '\0';
						WellElement * w_elem = w_colomn_podoshva->AddNewWellElement(p);
						if (w_elem)
						{
							Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(w_elem);
							if (wlitp)
							{
								wlitp->color = icol < colors_of_sloi->size() ? colors_of_sloi->operator [](icol) : RGB(255,255,255);
								wlitp->zk = zk;
								wlitp->zp = pt.z;
							}

							Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>(w_elem);
							if (wigep)
							{
								wigep->color = icol < colors_of_sloi->size() ? colors_of_sloi->operator [](icol) : RGB(255,255,255);
								wigep->zk = zk;
								wigep->zp = pt.z;
							}
						}
					}
				}
				else
				{
					this->PushBack(pt);
					this->m_vstrSloiNames.push_back(pnames_of_colomns->operator [](icol) );
	printf("pnames_of_colomns->operator [](icol) = %s this->m_vstrSloiNames.size() = %d\n", pnames_of_colomns->operator [](icol).c_str(), this->m_vstrSloiNames.size());
					this->m_vColor.push_back(colors_of_sloi->operator [](icol) );

				}
				if (slen > 0)
				{	
					zk = temp.value;
				}
			}
			break;
		case 6://sloi podoshva glubina
			{
				if (!ustje_is_determined)
				{
					MessageBox(0, "ustje is not determined!!!\nDetermine ustje first!", "Well_3D::Init",0);
					return false;
				}
				CPoint3 pt;
#if USE_STRING_IN_THE_CELL
				size_t slen = strlen(temp.str.c_str());
#else
				size_t slen = strlen(temp.s);
#endif
				if (slen > 0)
				{
					//this cell not empty
					pt.bVisible = true;
					pt.z		= m_vdPoints[1].z - temp.value;
					pt.x		= X;
					pt.y		= Y;

					if (m_vdPoints[0].z > pt.z)
						m_vdPoints[0].z = pt.z;
				}
				else
				{
					//this cell is empty
					pt.bVisible = false;
				}
				if (w_colomn_podoshva)
				{
					printf("w_colomn_podoshva->GetWellElementType() = %d\n",(int)w_colomn_podoshva->GetWellElementType());
					if (slen > 0)
					{
						char str[512];
						strcpy(str,pnames_of_colomns->operator [](icol).c_str());
						// deleting ""
						char * p = str;
						while ( (*p) == '"') p++;
						while (p[strlen(p)-1] == '"') p[strlen(p)-1] = '\0';
						WellElement * w_elem = w_colomn_podoshva->AddNewWellElement(p);
						if (w_elem)
						{
							Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(w_elem);
							if (wlitp)
							{
								wlitp->color = icol < colors_of_sloi->size() ? colors_of_sloi->operator [](icol) : RGB(255,255,255);
								wlitp->zk = zk;
								wlitp->zp = pt.z;
							}

							Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>(w_elem);
							if (wigep)
							{
								wigep->color = icol < colors_of_sloi->size() ? colors_of_sloi->operator [](icol) : RGB(255,255,255);
								wigep->zk = zk;
								wigep->zp = pt.z;

								//printf("wigep->z = %f\n", wigep->z);
								//printf("wigep->GetNameID() = %s\n", wigep->GetNameID().c_str());
							}
						}
					}
				}
				else
				{
					this->PushBack(pt);
					this->m_vstrSloiNames.push_back(pnames_of_colomns->operator [](icol) );
					this->m_vColor.push_back(colors_of_sloi->operator [](icol) );
				}
				if (slen > 0)
				{	
					zk = m_vdPoints[1].z - temp.value;
				}
			}
			break;
		case 7://zaboj altitude
			{
				to_init_zaboj_as_ustje = false;
				m_vdPoints[0].z = temp.value;
				m_vvPoints[0].z = temp.value;
				this->m_vColor[0] = colors_of_sloi->operator [](icol);
			}
			break;
		case 8://zaboj glubina
			{
				if (!ustje_is_determined)
				{
					MessageBox(0, "ustje is not determined!!!\nDetermine ustje first!", "Well_3D::Init",0);
					return false;
				}				
				to_init_zaboj_as_ustje = false;
				m_vdPoints[0].z = m_vdPoints[1].z - temp.value;
				m_vvPoints[0].z = m_vdPoints[1].z - temp.value;
				this->m_vColor[0] = colors_of_sloi->operator [](icol);
			}
			break;
		case 9:// karotazh
			{
				if (!ustje_is_determined)
				{
					MessageBox(0, "ustje is not determined!!!\nDetermine ustje first!", "Well_3D::Init",0);
					return false;
				}
				if (!karotazh_glubin)
				{
					MessageBox(0, "karotazh_glubin is not determined!!!\nDetermine karotazh_glubin first!", "Well_3D::Init",0);
					return false;
				}					
				
#if USE_STRING_IN_THE_CELL
				size_t slen = strlen(temp.str.c_str());
				size_t slen_kg = strlen((*iter_karotazh_glubin).str.c_str());
#else
				size_t slen = strlen(temp.s);
				size_t slen_kg = strlen((*iter_karotazh_glubin).s);
#endif
				if (slen > 0 && slen_kg > 0)
				{

					//this cells not empty
					CPoint4     pt;
					pt.bVisible = true;
					pt.v		= temp.value;
					pt.z		= m_vdPoints[1].z - (*iter_karotazh_glubin).value;
					pt.x		= X;
					pt.y		= Y;

					if (Well_3D::karotazh_list[kar_index].vmax < pt.v)
						Well_3D::karotazh_list[kar_index].vmax = pt.v;
					
					if (Well_3D::karotazh_list[kar_index].vmin > pt.v)
						Well_3D::karotazh_list[kar_index].vmin = pt.v;

					m_karotazhy.GetLastMsg().PushBack(pt);
					
					if (m_vdPoints[0].z > pt.z)
						m_vdPoints[0].z = pt.z;
				}

			}
			break;
		case 10:
		case 11:
			{
#if USE_STRING_IN_THE_CELL
				size_t slen = strlen(temp.str.c_str());
#else
				size_t slen = strlen(temp.s);
#endif
				if (w_colomn_hydro_projavlenie)
				{
					if (slen > 0)
					{
						WellElement * w_elem = w_colomn_hydro_projavlenie->AddNewWellElement(pnames_of_colomns->operator [](icol));
						if (w_elem)
						{
							Well_Hydro_Projavlenie * whydp = dynamic_cast<Well_Hydro_Projavlenie *>(w_elem);
							if (whydp)
							{
								//whydp->color = colors_of_sloi->operator [](icol);
								whydp->zp = temp.value;
								switch (*iter_types_col)
								{
								case 10:
									whydp->ustanovlen = true;
									break;
								case 11:
									whydp->ustanovlen = false;
									break;
								}
							}
						}
					}
				}
			}

			break;
		}
		if (karotazh_glubin)
			iter_karotazh_glubin++;

	}
	for(UINT i = 0; i < this->GetPointsNumber(); i++)
	{
		this->m_vdPoints[i].x = X;
		this->m_vvPoints[i].x = X;
		this->m_vdPoints[i].y = Y;
		this->m_vvPoints[i].y = Y;
	}
	return true;

}


void Well_3D::WellsSaveToDB()
{
	if (this->m_pSurfDoc && this->m_pSurfDoc->GetLabDoc())
	{
		CPoint3 ustje;
		if (this->GetUstje(ustje))
		{
			long ID_TYP = 0;

			CString nazva = sID.c_str();
			if (0 == nazva.Find('"'))
				nazva = nazva.Mid(1);

			int len = nazva.GetLength();
			if (nazva.Find('"') == nazva.GetLength() - 1)
				nazva = nazva.Left(len-1);

			this->m_id_kt = this->m_pSurfDoc->GetLabDoc()->AddKT(this->m_pSurfDoc->Get_ID_OBJ(), ID_TYP, nazva, ustje.x, ustje.y, ustje.z);


			for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
				it_c != this->well_colomns.end(); it_c++)
			{
				if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
				{
					(*it_c).SaveIGEToDB(this->m_id_kt, ustje.z);
				}
				if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
				{
					(*it_c).SaveLitoToDB(this->m_id_kt, ustje.z);
				}
			}
		}
	}
}
void Well_3D::Insert(size_t i_where, CPoint3 pt)
{
	printf("void Well_3D::Insert(size_t i_where = %d, CPoint3 pt)\n", i_where);
	printf("this->GetPointsNumber() = %d\n", this->GetPointsNumber());
	printf("this->m_vstrSloiNames.size() = %d\n", this->m_vstrSloiNames.size());
	printf("this->m_vColor.size() = %d\n", this->m_vColor.size());

	if (i_where > 1 &&
		i_where <= this->GetPointsNumber() &&
		i_where <= this->m_vstrSloiNames.size() &&
		i_where <= this->m_vColor.size() 
		)
	{

		this->Primitive3D<CPoint3>::Insert(i_where, pt);
	
		vector<string>::iterator iter_name = m_vstrSloiNames.begin();
		vector<COLORREF>::iterator iter_color = m_vColor.begin();

		m_vstrSloiNames.insert(iter_name+i_where, string(""));
		m_vColor.insert(iter_color+i_where, RGB(0,0,0));

		//ResetPesokGlinaCheredovanie();

	}
}


void Well_3D::ErasePoint(size_t i)
{
	// erase sloj
	if (i < this->GetPointsNumber() && i >= 2)
	{
		this->Primitive3D<CPoint3>::ErasePoint(i);

				
		vector<string>::iterator iter_name;
		vector<COLORREF>::iterator iter_color;

		size_t j = 0;
		for(
			iter_name = m_vstrSloiNames.begin(),
			iter_color = m_vColor.begin();
			
				iter_name != m_vstrSloiNames.end() &&
				iter_color != m_vColor.end()
				; 
			
				iter_name++,
				iter_color++,
				j++)
		{
			if (i == j)
			{
				m_vstrSloiNames.erase(iter_name);
				m_vColor.erase(iter_color);
				break;
			}
		}

		//ResetPesokGlinaCheredovanie();
	}
}
void Well_3D::WritePesokGlinaCheredovanie(FILE * out)
{
	/*CPoint3 ustje;
	if(this->GetUstje(ustje) && out)
	{
		for (size_t i = 2; i < this->GetPointsNumber();	i++)
		{
			CPoint3 pt = this->GetDocumentPoint(i);
			bool is_pesok = pt.flag & CPOINT3_FLAG_WELL_PODOSHV_PESOK_NOT_GLIN;
			double glubina = ustje.z - pt.z;
			fprintf(out, "%0.1f ", glubina);
		}
		fprintf(out, "0.0\n");
	}*/

	bool first = true;

	WellColomn * wc = this->FindWellColomn(WellElement::type::isSand_podoshva);
	if (wc)
	{
		CPoint3 ustje, pt;
		if (this->GetUstje(ustje))
		{
			pt = ustje;
			for (vector<WellElement*>::iterator it = wc->well_elements.begin();
				it != wc->well_elements.end(); it++)
			{
				if ((*it))
				{
					Well_IsSand_Podoshva * wissp = dynamic_cast<Well_IsSand_Podoshva *>((*it));
					if (wissp)
					{
						pt.z = wissp->GetZp();	
						bool is_pesok = wissp->isSand;
						double glubina = ustje.z - pt.z;
						if (first)
						{
							first = false;
							// Если сверху залегает глина,
							// на устье ставим подошву песка
							if (!is_pesok)
							{
								fprintf(out, "0.0 ", glubina);
							}
						}
						fprintf(out, "%0.1f ", glubina);
					}
				}
			}
			fprintf(out, "0.0\n");
		}
	}
}

void Well_3D::ResetPesokGlinaCheredovanie()
{
#if 0	
	const char * name;
	const char * pes = "pesok\0";
	const char * glin = "glina\0";

	for (size_t i = 2; 
		i < this->GetPointsNumber()	&&
		i < this->m_vColor.size() &&
		i < m_vstrSloiNames.size();
	i++)
	{
		bool is_pesok = i%2 == 0;

		CPoint3 & pt = this->GetDocumentPoint(i);
		COLORREF & c = this->m_vColor[i];
		if (is_pesok)
		{
			// включаем бит песка
			pt.flag |= CPOINT3_FLAG_WELL_PODOSHV_PESOK_NOT_GLIN;
			c = RGB(225,225,0);//жёлтый
			name = pes;
		}
		else
		{
			// выключаем бит песка
			pt.flag &= ~CPOINT3_FLAG_WELL_PODOSHV_PESOK_NOT_GLIN;
			c = RGB(128,64,0);//коричневый
			name = glin;
		}
		this->m_vstrSloiNames[i] = string(name);
	}
#else
	int i = 2;
	WellColomn * wc = this->FindWellColomn(WellElement::type::isSand_podoshva);
	if (wc)
	{
		for (vector<WellElement*>::iterator it = wc->well_elements.begin();
			it != wc->well_elements.end(); it++, i++)
		{
			if ((*it))
			{
				Well_IsSand_Podoshva * wissp = dynamic_cast<Well_IsSand_Podoshva *>((*it));
				if (wissp)
				{
					bool is_pesok = i%2 == 0;
					wissp->isSand = is_pesok;
				}
			}
		}
	}
#endif

}
bool Well_3D::PutPesokOrGlinaPodosnvaOld(bool is_pesok, double glubina_podoshvy)
{
	CPoint3 pt;
	COLORREF c;						
	const char * name;
	const char * pes = "pesok\0";
	const char * glin = "glina\0";

	if (is_pesok)
	{
		// включаем бит песка
		//pt.flag |= CPOINT3_FLAG_WELL_PODOSHV_PESOK_NOT_GLIN;
		c = RGB(225,225,0);//жёлтый
		name = pes;
	}
	else
	{
		// выключаем бит песка
		//pt.flag &= ~CPOINT3_FLAG_WELL_PODOSHV_PESOK_NOT_GLIN;
		c = RGB(128,64,0);//коричневый
		name = glin;
	}
	
	//case 6://sloi podoshva glubina
	CPoint3 ustje;
	if (this->GetUstje(ustje))
	{
		if (true)
		{
			//this cell not empty
			pt.bVisible = true;
			pt.z		= ustje.z - glubina_podoshvy;
			pt.x		= ustje.x;
			pt.y		= ustje.y;
		}
		else
		{
			//this cell is empty
			pt.bVisible = false;
		}						
		this->PushBack(pt);
		this->m_vstrSloiNames.push_back(name);
		this->m_vColor.push_back(c);
		return true;
	}
	return false;
}
bool Well_3D::PutPesokOrGlinaPodosnva(bool is_pesok, double glubina_podoshvy, WellColomn * w_colomn_issand)
{
	printf("Well_3D(%s)::PutPesokOrGlinaPodosnva(bool is_pesok(%d), double glubina_podoshvy(%f), WellColomn * w_colomn_issand(%x)", this->GetIDString(), is_pesok, glubina_podoshvy, w_colomn_issand);
	
	//CPoint3 pt;
	const char * name;
	const char * pes = "pesok\0";
	const char * glin = "glina\0";
	char ID[1024];

	if (is_pesok)
	{
		name = pes;
	}
	else
	{
		name = glin;
	}

	CPoint3 ustje;
	if (this->GetUstje(ustje))
	{
		if (w_colomn_issand)
		{
			sprintf(ID, "%s%u", name, w_colomn_issand->well_elements.size());
			WellElement * w_elem = w_colomn_issand->AddNewWellElement(ID);
			if (w_elem)
			{
				Well_IsSand_Podoshva * wissp = dynamic_cast<Well_IsSand_Podoshva *>(w_elem);
				if (wissp)
				{
					wissp->zp = ustje.z - glubina_podoshvy;
					wissp->isSand = is_pesok;
					printf("wissp->zp = %f\n", wissp->zp);
					return true;
				}
			}
		}		
	}
	return false;
}
bool Well_3D::IsPesokOrGlina(double z, bool & is_pesok)
{
	WellColomn * wc = this->FindWellColomn(WellElement::type::isSand_podoshva);
	if (wc)
	{
		double z_pre;
		CPoint3 ustje, pt;
		if (this->GetUstje(ustje))
		{
			z_pre = ustje.z;
			pt = ustje;
			for (vector<WellElement*>::iterator it = wc->well_elements.begin();
				it != wc->well_elements.end(); it++)
			{
				if ((*it))
				{
					Well_IsSand_Podoshva * wissp = dynamic_cast<Well_IsSand_Podoshva *>((*it));
					if (wissp)
					{						
						pt.z = wissp->GetZp();	
						if ( z_pre >= z && z > pt.z)
						{
							is_pesok = wissp->isSand;
							printf("Well_3D::IsPesokOrGlina(double z = %f, bool & is_pesok = %d) \n", z, is_pesok);
							return true;
						}
						z_pre = pt.z;
					}
				}
			}
		}
	}
	return false;
}
bool Well_3D::GetTypGrunt_from_db_lito(double glubina_ot_ustja, long & typgr)
{	
	if (this->m_db_lito.data_filled)
	{
		for (vector<db_lito_data>::iterator it_lit = this->m_db_lito.data1.begin();
			it_lit != this->m_db_lito.data1.end(); it_lit++)
		{
			if (glubina_ot_ustja >= (*it_lit).h0 && glubina_ot_ustja <= (*it_lit).h1)
			{
				//(*it_lit).id_ige;

				if (this->m_pSurfDoc)
				{
					bool found = false;
					for (vector<IGE_Data>::iterator it_ige = this->m_pSurfDoc->m_db_ige.data.begin();
						it_ige != this->m_pSurfDoc->m_db_ige.data.end(); it_ige++)
					{
						if ((*it_ige).ige_filled && (*it_ige).grunt_filled && (*it_ige).ige.id_ige == (*it_lit).id_ige)
						{
							typgr = (*it_ige).grunt.typgr;
							return true;							
						}
					}	
				}
			}
		}
	}

	return false;
}
bool Well_3D::GetTypGrunt_from_db_lito(double glubina_ot_ustja_0, double glubina_ot_ustja_1, 
									   bool & have_bound_in_the_interval, 
									   double & glubina_ot_ustja_of_bound_in_the_interval,
									   long & typgr_0, long & typgr_1, 
									   long & typgr)
{
	
	if (this->m_db_lito.data_filled)
	{
		long id_ige_0, id_ige_1;
		bool found_0 = false;
		bool found_1 = false;
		for (vector<db_lito_data>::iterator it_lit = this->m_db_lito.data1.begin();
			it_lit != this->m_db_lito.data1.end(); it_lit++)
		{
			if (glubina_ot_ustja_0 >= (*it_lit).h0 && glubina_ot_ustja_0 <= (*it_lit).h1)
			{
				id_ige_0 = (*it_lit).id_ige;

				if (this->m_pSurfDoc)
				{
					for (vector<IGE_Data>::iterator it_ige = this->m_pSurfDoc->m_db_ige.data.begin();
						it_ige != this->m_pSurfDoc->m_db_ige.data.end(); it_ige++)
					{
						if ((*it_ige).ige_filled && (*it_ige).grunt_filled && (*it_ige).ige.id_ige == (*it_lit).id_ige)
						{
							typgr_0 = (*it_ige).grunt.typgr;
							found_0 = true;							
						}
					}	
				}
			}
		}
		for (vector<db_lito_data>::iterator it_lit = this->m_db_lito.data1.begin();
			it_lit != this->m_db_lito.data1.end(); it_lit++)
		{
			if (glubina_ot_ustja_1 >= (*it_lit).h0 && glubina_ot_ustja_1 <= (*it_lit).h1)
			{
				id_ige_1 = (*it_lit).id_ige;

				if (this->m_pSurfDoc)
				{
					for (vector<IGE_Data>::iterator it_ige = this->m_pSurfDoc->m_db_ige.data.begin();
						it_ige != this->m_pSurfDoc->m_db_ige.data.end(); it_ige++)
					{
						if ((*it_ige).ige_filled && (*it_ige).grunt_filled && (*it_ige).ige.id_ige == (*it_lit).id_ige)
						{
							glubina_ot_ustja_of_bound_in_the_interval = (*it_lit).h0;
							typgr_1 = (*it_ige).grunt.typgr;
							found_1 = true;							
						}
					}	
				}
			}
		}
		if (found_0 && found_1)
		{
			if (id_ige_0 == id_ige_1)
			{
				have_bound_in_the_interval = false;
				typgr = typgr_0;
			}
			else
			{
				if (typgr_0 == typgr_1)
				{
					have_bound_in_the_interval = false;
					typgr = typgr_0;
				}
				else
				{
					have_bound_in_the_interval = true;
				}
			}
			return true;
		}
	}

	return false;
}
Karotazh * Well_3D::AddKarotazh(int kar_index)
{
	Karotazh * added = NULL;

	if (kar_index >= 0 && kar_index < Well_3D::karotazh_list.size())
	{
		m_karotazhy.AddMsg(&Karotazh(this->m_pSurfDoc, Well_3D::karotazh_list[kar_index].name.c_str()));
		m_karotazhy.GetLastMsg().m_index = kar_index;
		added = &m_karotazhy.GetLastMsg();
	}

	return added;
}

Karotazh * Well_3D::GetKarotazh(int kar_index)
{
	Karotazh * found = NULL;

	if (this->m_karotazhy.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_karotazhy.GetCurrentMsg().m_index == kar_index)
			{
				found = &m_karotazhy.GetCurrentMsg();
			}
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}

	return found;
}
bool FindMeanPCK_0(Karotazh * karotazh_pck, CPoint3 & ustje, double glubina, double d, double & mean_pck)
{
	//найти усреднённое рск на участке глубин 
	// от (glubina - d) до (glubina + 4*d)
	
	int ik1 = -1, ik2 = -1;

	for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()); ik++)
	{
		double glubina_pck = ustje.z - karotazh_pck->GetDocumentPoint(ik).z;
		//printf("glubina_pck = %f\n", glubina_pck);

		if (glubina_pck <= glubina - d)
			ik1 = ik;
	}
	for(int ik = int(karotazh_pck->GetPointsNumber()) - 1; ik >= 0 ; ik--)
	{
		double glubina_pck = ustje.z - karotazh_pck->GetDocumentPoint(ik).z;
		//printf("glubina_pck = %f\n", glubina_pck);

		if (glubina_pck >= glubina + 4 * d)
			ik2 = ik;
	}
	if (ik1 > -1 && ik2 > -1)
	{
		// вычисляем интеграл методом трапеции

		// первая трапеция интеграла
		double glubina_pck_ik1			= ustje.z - karotazh_pck->GetDocumentPoint( ik1 ).z;
		double glubina_pck_ik1_plus1	= ustje.z - karotazh_pck->GetDocumentPoint(ik1+1).z;
		
		double mu1 = ((glubina - d) - glubina_pck_ik1) / (glubina_pck_ik1_plus1 - glubina_pck_ik1);

		double pck_ik1			= karotazh_pck->GetDocumentPoint( ik1 ).v;
		double pck_ik1_plus1	= karotazh_pck->GetDocumentPoint(ik1+1).v;

		double pck_glubina_minus_d = pck_ik1 + mu1 * (pck_ik1_plus1 - pck_ik1);

		double dh1 = glubina_pck_ik1_plus1 - (glubina - d);
		double dS1 = 0.5 * dh1 * (pck_glubina_minus_d + pck_ik1_plus1);

		// нижняя трапеция интеграла
		double glubina_pck_ik2			= ustje.z - karotazh_pck->GetDocumentPoint( ik2 ).z;
		double glubina_pck_ik2_minus1	= ustje.z - karotazh_pck->GetDocumentPoint(ik2-1).z;
		
		double mu2 = ((glubina + 4*d) - glubina_pck_ik2_minus1) / (glubina_pck_ik2 - glubina_pck_ik2_minus1);

		double pck_ik2			= karotazh_pck->GetDocumentPoint( ik2 ).v;
		double pck_ik2_minus1	= karotazh_pck->GetDocumentPoint(ik2-1).v;

		double pck_glubina_plus_4d = pck_ik2_minus1 + mu2 * (pck_ik2 - pck_ik2_minus1);

		double dh2 = (glubina + 4*d) - glubina_pck_ik2_minus1;
		double dS2 = 0.5 * dh2 * (pck_glubina_plus_4d + pck_ik2_minus1);

		double S = dS1 + dS2;
		double h = dh1 + dh2;
		// промежуточные трапеции
		for (int ik = ik1+1; ik < ik2-1; ik++)
		{
			double glubina_pck_ik		= ustje.z - karotazh_pck->GetDocumentPoint( ik ).z;
			double glubina_pck_ik_plus1	= ustje.z - karotazh_pck->GetDocumentPoint(ik+1).z;
			
			double pck_ik		= karotazh_pck->GetDocumentPoint( ik ).v;
			double pck_ik_plus1	= karotazh_pck->GetDocumentPoint(ik+1).v;
			
			double dh = glubina_pck_ik_plus1 - glubina_pck_ik;
			double dS = 0.5 * dh * (pck_ik_plus1 + pck_ik);
			
			S += dS;
			h += dh;
		}
		if (h > 0.0)
		{
			mean_pck = S / h;
			return true;
		}
	}
	return false;
}
#define USE_DB_GRUNT_TYPE 0
#define USE_DB_PSK_EDINICY 1
void Well_3D::DetermineDeformationModul()
{
	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
	if (karotazh_pck)
	{

		int kar_index_def_mod = Well_3D::GetKarotazhIndex(DEFORMATION_MODUL_KAR_NAME);
		Karotazh * karotazh_def_mod = this->GetKarotazh(kar_index_def_mod);
		
		if (!karotazh_def_mod)
			karotazh_def_mod = this->AddKarotazh(kar_index_def_mod);


		if (karotazh_def_mod)
		{
			karotazh_def_mod->Free();

			for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()); ik++)
			{
				double z_pck = karotazh_pck->GetDocumentPoint(ik).z;
				double pck   = karotazh_pck->GetDocumentPoint(ik).v;

				CPoint4 pt_def_mod;
				pt_def_mod.bVisible = true;
				pt_def_mod.x = karotazh_pck->GetDocumentPoint(ik).x;
				pt_def_mod.y = karotazh_pck->GetDocumentPoint(ik).y;
				pt_def_mod.z = karotazh_pck->GetDocumentPoint(ik).z;

				bool is_pesok;
#if USE_DB_GRUNT_TYPE
				long typgr;
				if (this->GetTypGrunt_from_db_lito(z_pck, typgr))
				{
					is_pesok = typgr == 1;
#else
				if (this->IsPesokOrGlina(z_pck, is_pesok))
				{
#endif
					printf("is_pesok = %d\n", is_pesok);
					double E;
#if USE_DB_PSK_EDINICY
					double qs = pck;//в базе pck уже в МПа
#else
					double qs = pck/100.;//перевод из тс/м^2 в МПа
#endif
					if (is_pesok)
					{
						E = 2.69 * qs + 7.45; //(4.34) стр.77
					}
					else
					{
						E = 7 * qs; // (4.32)  стр.77
					}

					pt_def_mod.v = E;

					if (Well_3D::karotazh_list[kar_index_def_mod].vmax < pt_def_mod.v)
						Well_3D::karotazh_list[kar_index_def_mod].vmax = pt_def_mod.v;
					
					if (Well_3D::karotazh_list[kar_index_def_mod].vmin > pt_def_mod.v)
						Well_3D::karotazh_list[kar_index_def_mod].vmin = pt_def_mod.v;

					karotazh_def_mod->PushBack(pt_def_mod);

				}
			}
		}
	}
}
void Well_3D::EraseSloi()
{
	while (this->GetPointsNumber() > 2)
	{
		this->ErasePoint(this->GetPointsNumber() - 1);
	}
}
void Well_3D::DeterminePesokGlinaFromPCK(wells_draw_list_item * wdli_issand)
{
	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
		
	CPoint3 ustje;
	if (karotazh_pck && this->GetUstje(ustje))
	{

		int i_colomn_issand = -1;
		if (wdli_issand)
			i_colomn_issand = this->AddNewWellColomn(WellElement::type::isSand_podoshva, wdli_issand);

		WellColomn * w_colomn_issand = NULL;
		if (i_colomn_issand > -1)
			w_colomn_issand = &this->well_colomns[i_colomn_issand];

		bool is_pesok = true;
		//граница pck
#if USE_DB_PSK_EDINICY
	double pck_level_200 = 2.0;//в базе pck дано в МПа
#else
	double pck_level_200 = 200.0;;//в старых файлах пакета ГЕОЛОГИЯ pck дано в тс/м^2
#endif

		if (karotazh_pck->GetPointsNumber() > 1)
		{

			double z_pck0 = karotazh_pck->GetDocumentPoint(0).z;
			double pck0   = karotazh_pck->GetDocumentPoint(0).v;

			double z_pck1 = karotazh_pck->GetDocumentPoint(1).z;
			double pck1   = karotazh_pck->GetDocumentPoint(1).v;

			// Если сверху залегает глина,
			// на устье ставим подошву песка

			if (pck0 < pck_level_200 && pck1 < pck_level_200)
			{
				this->PutPesokOrGlinaPodosnva(true, 0.0, w_colomn_issand);
				is_pesok = false;
			}
		}

		for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()) - 1; ik++)
		{
			double z_pck1 = karotazh_pck->GetDocumentPoint(ik).z;
			double pck1   = karotazh_pck->GetDocumentPoint(ik).v;

			double z_pck2 = karotazh_pck->GetDocumentPoint(ik+1).z;
			double pck2   = karotazh_pck->GetDocumentPoint(ik+1).v;

			if (pck1 >= pck_level_200 && pck2 >= pck_level_200)
			{
				// мы в песке
				is_pesok = true;
			}
			if (pck1 < pck_level_200 && pck2 < pck_level_200)
			{
				// мы в глине
				is_pesok = false;
			}
			if (pck1 < pck_level_200 && pck2 >= pck_level_200)
			{
				// мы прошли подошву глины
				this->PutPesokOrGlinaPodosnva(false, ustje.z - 0.5 * (z_pck1 + z_pck2), w_colomn_issand);
				is_pesok = true;
			}			
			if (pck1 >= pck_level_200 && pck2 < pck_level_200)
			{
				// мы прошли подошву песка
				this->PutPesokOrGlinaPodosnva(true, ustje.z - 0.5 * (z_pck1 + z_pck2), w_colomn_issand);
				is_pesok = false;
			}	
		}
		if (karotazh_pck->GetPointsNumber() > 1)
		{

			double z_pck_end = karotazh_pck->GetDocumentPoint(karotazh_pck->GetPointsNumber() - 1).z;
			double pck_end   = karotazh_pck->GetDocumentPoint(karotazh_pck->GetPointsNumber() - 1).v;

			this->PutPesokOrGlinaPodosnva(is_pesok, 0.1 + ustje.z - z_pck_end, w_colomn_issand);
		}
	}
}
void Well_3D::DetermineUdelnoeSceplenie()
{
	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
	if (karotazh_pck)
	{

		int kar_index_scepl = Well_3D::GetKarotazhIndex(UDELNOE_SCEPLENIE_KAR_NAME);
		Karotazh * karotazh_scepl = this->GetKarotazh(kar_index_scepl);
		
		if (!karotazh_scepl)
			karotazh_scepl = this->AddKarotazh(kar_index_scepl);


		if (karotazh_scepl)
		{
			karotazh_scepl->Free();
			for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()); ik++)
			{
				double z_pck = karotazh_pck->GetDocumentPoint(ik).z;
				double pck   = karotazh_pck->GetDocumentPoint(ik).v;

				CPoint4 pt_scepl;
				pt_scepl.bVisible = true;
				pt_scepl.x = karotazh_pck->GetDocumentPoint(ik).x;
				pt_scepl.y = karotazh_pck->GetDocumentPoint(ik).y;
				pt_scepl.z = karotazh_pck->GetDocumentPoint(ik).z;

				bool is_pesok;
#if USE_DB_GRUNT_TYPE
				long typgr;
				if (this->GetTypGrunt_from_db_lito(z_pck, typgr))
				{
					is_pesok = typgr == 1;
#else
				if (this->IsPesokOrGlina(z_pck, is_pesok))
				{
#endif
					printf("is_pesok = %d\n", is_pesok);
					double c;
#if USE_DB_PSK_EDINICY
					double qs = pck;//в базе pck уже в МПа
#else
					double qs = pck/100.;//перевод из тс/м^2 в МПа
#endif

					if (is_pesok)
					{
						//таб 4.12, стр.80
						//мелкий песок
						//1.5,	0
						//3,	0.001
						//5,	0.002
						//8,	0.003
						//15,	0.004
						//27.5,	0.005
						//50,	0.006
						double vqs[] = {1.5, 3, 5, 8, 15, 27.5, 50};
						double vc[] = {0, 0.001, 0.002, 0.003, 0.004, 0.005, 0.006};
						int j = 1;
						int n = 7;
						while (j < n-1 && vqs[j] < qs)
						{
								j = j+1;
						}
						double alfa = (qs-vqs[j-1])/(vqs[j]-vqs[j-1]);
						c = vc[j-1]+alfa*(vc[j]-vc[j-1]);
					}
					else
					{
						c = 0.0116 * qs + 0.0125; // (4.37)  стр.81
					}

					pt_scepl.v = c;

					if (Well_3D::karotazh_list[kar_index_scepl].vmax < pt_scepl.v)
						Well_3D::karotazh_list[kar_index_scepl].vmax = pt_scepl.v;
					
					if (Well_3D::karotazh_list[kar_index_scepl].vmin > pt_scepl.v)
						Well_3D::karotazh_list[kar_index_scepl].vmin = pt_scepl.v;

					karotazh_scepl->PushBack(pt_scepl);

				}
			}
		}
	}
}
void Well_3D::DetermineUdolVnutrennegoTrenia()
{
	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
	if (karotazh_pck)
	{

		int kar_index_ugol = Well_3D::GetKarotazhIndex(UGOL_VNUTRENNEGO_TRENIA_KAR_NAME);
		Karotazh * karotazh_ugol = this->GetKarotazh(kar_index_ugol);
		
		if (!karotazh_ugol)
			karotazh_ugol = this->AddKarotazh(kar_index_ugol);


		if (karotazh_ugol)
		{
			karotazh_ugol->Free();
			for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()); ik++)
			{
				double z_pck = karotazh_pck->GetDocumentPoint(ik).z;
				double pck   = karotazh_pck->GetDocumentPoint(ik).v;

				CPoint4 pt_ugol;
				pt_ugol.bVisible = true;
				pt_ugol.x = karotazh_pck->GetDocumentPoint(ik).x;
				pt_ugol.y = karotazh_pck->GetDocumentPoint(ik).y;
				pt_ugol.z = karotazh_pck->GetDocumentPoint(ik).z;

				bool is_pesok;
#if USE_DB_GRUNT_TYPE
				long typgr;
				if (this->GetTypGrunt_from_db_lito(z_pck, typgr))
				{
					is_pesok = typgr == 1;
#else
				if (this->IsPesokOrGlina(z_pck, is_pesok))
				{
#endif
					printf("is_pesok = %d\n", is_pesok);
					double fi;
#if USE_DB_PSK_EDINICY
					double qs = pck;//в базе pck уже в МПа
#else
					double qs = pck/100.;//перевод из тс/м^2 в МПа
#endif
					
					if (is_pesok)
					{
						//таб 4.12, стр.80
						//мелкий песок
						//1.5,	28
						//3,	30
						//5,	32
						//8,	34
						//15,	36
						//27.5,	37(36)
						//50,	38

						double vqs[] = {1.5, 3, 5, 8, 15, 27.5, 50};
						double vfi[] = {28, 30, 32, 34, 36, 37, 38};
						int j = 1;
						int n = 7;
						while (j < n-1 && vqs[j] < qs)
						{
								j = j+1;
						}
						double alfa = (qs-vqs[j-1])/(vqs[j]-vqs[j-1]);
						fi = vfi[j-1]+alfa*(vfi[j]-vfi[j-1]);
						
					}
					else
					{
						fi = 180*atan(0.045 * qs + 0.26)/M_PI; // (4.36)  стр.81
					}

					pt_ugol.v = fi;

					if (Well_3D::karotazh_list[kar_index_ugol].vmax < pt_ugol.v)
						Well_3D::karotazh_list[kar_index_ugol].vmax = pt_ugol.v;
					
					if (Well_3D::karotazh_list[kar_index_ugol].vmin > pt_ugol.v)
						Well_3D::karotazh_list[kar_index_ugol].vmin = pt_ugol.v;

					karotazh_ugol->PushBack(pt_ugol);

				}
			}
		}
	}
}

void Well_3D::TestPesokOrGlina()
{
	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
	if (karotazh_pck)
	{

		int kar_index_pes = Well_3D::GetKarotazhIndex(TEST_PESOK_OR_GLINA_KAR_NAME);
		Karotazh * karotazh_pes = this->GetKarotazh(kar_index_pes);
		
		if (!karotazh_pes)
			karotazh_pes = this->AddKarotazh(kar_index_pes);


		if (karotazh_pes)
		{
			karotazh_pes->Free();
			for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()); ik++)
			{
				double z_pck = karotazh_pck->GetDocumentPoint(ik).z;
				double pck   = karotazh_pck->GetDocumentPoint(ik).v;

				CPoint4 pt_pes;
				pt_pes.bVisible = true;
				pt_pes.x = karotazh_pck->GetDocumentPoint(ik).x;
				pt_pes.y = karotazh_pck->GetDocumentPoint(ik).y;
				pt_pes.z = karotazh_pck->GetDocumentPoint(ik).z;

				bool is_pesok;
#if USE_DB_GRUNT_TYPE
				long typgr;
				if (this->GetTypGrunt_from_db_lito(z_pck, typgr))
				{
					is_pesok = typgr == 1;
#else
				if (this->IsPesokOrGlina(z_pck, is_pesok))
				{
#endif
					printf("is_pesok = %d\n", is_pesok);
					double fi;
					
					if (is_pesok)
					{
						fi = -1.0;						
					}
					else
					{
						fi = +1.0; 
					}

					pt_pes.v = fi;

					if (Well_3D::karotazh_list[kar_index_pes].vmax < pt_pes.v)
						Well_3D::karotazh_list[kar_index_pes].vmax = pt_pes.v;
					
					if (Well_3D::karotazh_list[kar_index_pes].vmin > pt_pes.v)
						Well_3D::karotazh_list[kar_index_pes].vmin = pt_pes.v;

					karotazh_pes->PushBack(pt_pes);

				}
			}
		}
	}
}

bool FindMeanPCK(Karotazh * karotazh_pck, CPoint3 & ustje, double glubina, double d, double & mean_pck)
{
	//найти усреднённое рск на участке глубин 
	// от (glubina - d) до (glubina + 4*d)
	
	int ik1 = -1, ik2 = -1;

	double glub_up = glubina - d;
	//double glub_up = glubina;
	double glub_dw = glubina + 4 * d;

	for(int ik = 0; ik < int(karotazh_pck->GetPointsNumber()); ik++)
	{
		double glubina_pck = ustje.z - karotazh_pck->GetDocumentPoint(ik).z;
		//printf("glubina_pck = %f\n", glubina_pck);

		if (glubina_pck <= glub_up)
			ik1 = ik;
	}
	for(int ik = int(karotazh_pck->GetPointsNumber()) - 1; ik >= 0 ; ik--)
	{
		double glubina_pck = ustje.z - karotazh_pck->GetDocumentPoint(ik).z;
		//printf("glubina_pck = %f\n", glubina_pck);

		if (glubina_pck >= glub_dw)
			ik2 = ik;
	}
	if (ik1 > -1 && ik2 > -1)
	{
		// вычисляем интеграл методом трапеции

		// первая трапеция интеграла
		double glubina_pck_ik1			= ustje.z - karotazh_pck->GetDocumentPoint( ik1 ).z;
		double glubina_pck_ik1_plus1	= ustje.z - karotazh_pck->GetDocumentPoint(ik1+1).z;
		
		double mu1 = (glub_up - glubina_pck_ik1) / (glubina_pck_ik1_plus1 - glubina_pck_ik1);

		double pck_ik1			= karotazh_pck->GetDocumentPoint( ik1 ).v;
		double pck_ik1_plus1	= karotazh_pck->GetDocumentPoint(ik1+1).v;

		double pck_glubina_minus_d = pck_ik1 + mu1 * (pck_ik1_plus1 - pck_ik1);

		double dh1 = glubina_pck_ik1_plus1 - glub_up;
		double dS1 = 0.5 * dh1 * (pck_glubina_minus_d + pck_ik1_plus1);

		// нижняя трапеция интеграла
		double glubina_pck_ik2			= ustje.z - karotazh_pck->GetDocumentPoint( ik2 ).z;
		double glubina_pck_ik2_minus1	= ustje.z - karotazh_pck->GetDocumentPoint(ik2-1).z;
		
		double mu2 = (glub_dw - glubina_pck_ik2_minus1) / (glubina_pck_ik2 - glubina_pck_ik2_minus1);

		double pck_ik2			= karotazh_pck->GetDocumentPoint( ik2 ).v;
		double pck_ik2_minus1	= karotazh_pck->GetDocumentPoint(ik2-1).v;

		double pck_glubina_plus_4d = pck_ik2_minus1 + mu2 * (pck_ik2 - pck_ik2_minus1);

		double dh2 = glub_dw - glubina_pck_ik2_minus1;
		double dS2 = 0.5 * dh2 * (pck_glubina_plus_4d + pck_ik2_minus1);

		double S = dS1 + dS2;
		double h = dh1 + dh2;
		// промежуточные трапеции
		for (int ik = ik1+1; ik < ik2-1; ik++)
		{
			double glubina_pck_ik		= ustje.z - karotazh_pck->GetDocumentPoint( ik ).z;
			double glubina_pck_ik_plus1	= ustje.z - karotazh_pck->GetDocumentPoint(ik+1).z;
			
			double pck_ik		= karotazh_pck->GetDocumentPoint( ik ).v;
			double pck_ik_plus1	= karotazh_pck->GetDocumentPoint(ik+1).v;
			
			double dh = glubina_pck_ik_plus1 - glubina_pck_ik;
			double dS = 0.5 * dh * (pck_ik_plus1 + pck_ik);
			
			S += dS;
			h += dh;
		}
		if (h > 0.0)
		{
			mean_pck = S / h;
			return true;
		}
	}
	return false;
}
bool Well_3D::FindIntegralPCB(Karotazh * karotazh_pcb, CPoint3 & ustje, double glubina, double & fh)
{
	//найти усреднённое рск на участке глубин 
	// от (glubina - d) до (glubina + 4*d)
	
	int ik1, ik2;

	fh = 0;

	for(ik1 = 0, ik2 = 1; ik2 < int(karotazh_pcb->GetPointsNumber()); ik1++, ik2++)
	{
		double glubina_pcb = ustje.z - karotazh_pcb->GetDocumentPoint(ik2).z;
		if (glubina_pcb > glubina)
			break;

		double dh = karotazh_pcb->GetDocumentPoint(ik1).z - karotazh_pcb->GetDocumentPoint(ik2).z;

		double fs1 = karotazh_pcb->GetDocumentPoint(ik1).v;
		double fs2 = karotazh_pcb->GetDocumentPoint(ik2).v;

		double beta2_fs1, beta2_fs2;

		double fs0 = 1.0; // 1 тс/м^2 = 0.01 МПа //0.01 МПа;  стр.67

		bool is_pesok1;
		if (this->IsPesokOrGlina(karotazh_pcb->GetDocumentPoint(ik1).z, is_pesok1))
		{
			double beta2;
			if (is_pesok1)
			{
				beta2 = 0.90 - 0.46 * log10(fs1/fs0);// (4.16) стр.66
			}
			else
			{
				beta2 = 1.31 - 0.93 * log10(fs1/fs0);// (4.18) стр.67
			}
			beta2_fs1 = beta2 * fs1;

		}
		else return false;

		bool is_pesok2;
		if (this->IsPesokOrGlina(karotazh_pcb->GetDocumentPoint(ik2).z, is_pesok2))
		{
			double beta2;
			if (is_pesok2)
			{
				beta2 = 0.90 - 0.46 * log10(fs2/fs0);// (4.16) стр.66
			}
			else
			{
				beta2 = 1.31 - 0.93 * log10(fs2/fs0);// (4.18) стр.67
			}
			beta2_fs2 = beta2 * fs2;
		}
		else return false;

		double beta2_fs = 0.5 * (beta2_fs1 + beta2_fs2);
		double dfh = beta2_fs * dh;
		fh += dfh;
	}

	return true;
}
void Well_3D::TestSvai()
{
	printf("Well_3D::TestSvai(%s)\n", this->GetIDString());

	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	int kar_index_pcb = Well_3D::GetKarotazhIndex(PCB_KAR_NAME);
	int kar_index_pck_pcb = Well_3D::GetKarotazhIndex(PCB_PCK_KAR_NAME);

	int kar_index_svai_20 = Well_3D::GetKarotazhIndex(SVAI_20_20_KAR_NAME);
	int kar_index_svai_25 = Well_3D::GetKarotazhIndex(SVAI_25_25_KAR_NAME);
	int kar_index_svai_30 = Well_3D::GetKarotazhIndex(SVAI_30_30_KAR_NAME);
	int kar_index_svai_35 = Well_3D::GetKarotazhIndex(SVAI_35_35_KAR_NAME);
	int kar_index_svai_40 = Well_3D::GetKarotazhIndex(SVAI_40_40_KAR_NAME);

	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
	Karotazh * karotazh_pcb = this->GetKarotazh(kar_index_pcb);
	Karotazh * karotazh_pck_pcb = this->GetKarotazh(kar_index_pck_pcb);
	Karotazh * karotazh_svai_20 = this->GetKarotazh(kar_index_svai_20);
	Karotazh * karotazh_svai_25 = this->GetKarotazh(kar_index_svai_25);
	Karotazh * karotazh_svai_30 = this->GetKarotazh(kar_index_svai_30);
	Karotazh * karotazh_svai_35 = this->GetKarotazh(kar_index_svai_35);
	Karotazh * karotazh_svai_40 = this->GetKarotazh(kar_index_svai_40);

					
	double d = 0.4;
	Karotazh * karotazh_svai_ = karotazh_svai_40;
	
	CPoint3 ustje;

	if (karotazh_pck && karotazh_pcb && GetUstje(ustje))
	{
		int kar_index_test_svai = Well_3D::GetKarotazhIndex("TestSvai");
		Karotazh * karotazh_test_svai = this->GetKarotazh(kar_index_test_svai);
		
		if (!karotazh_test_svai)
			karotazh_test_svai = this->AddKarotazh(kar_index_test_svai);

		int kar_index_RA = Well_3D::GetKarotazhIndex("RA");
		Karotazh * karotazh_RA = this->GetKarotazh(kar_index_RA);
		
		if (!karotazh_RA)
			karotazh_RA = this->AddKarotazh(kar_index_RA);

		int kar_index_fuh = Well_3D::GetKarotazhIndex("fuh");
		Karotazh * karotazh_fuh = this->GetKarotazh(kar_index_fuh);
		
		if (!karotazh_fuh)
			karotazh_fuh = this->AddKarotazh(kar_index_fuh);


		if (karotazh_test_svai && karotazh_RA && karotazh_fuh)
		{
			karotazh_test_svai->Free();
			karotazh_RA->Free();

			if (karotazh_svai_)
			{
				for (size_t is = 0; is < karotazh_svai_->GetPointsNumber(); is++)
				{
					double A = d*d;
					double u = 4*d;
					double glubina = ustje.z - karotazh_svai_->GetDocumentPoint(is).z;
					
					printf("glubina = %f\t", glubina);
					double mean_pck;
					if (FindMeanPCK(karotazh_pck, ustje, glubina, d, mean_pck))
					{
						// Л.Г.Мариупольский 
						// Исследования грунтов для проектирования свайных фундаментов
						// Москва, Стройиздат, 1989
						double qs = mean_pck;
#if USE_DB_PSK_EDINICY
						double qs0 = 1.0;// мы уже перевели pck в МПа (как в базе) 
#else
						double qs0 = 100.0;// 100 тс/м^2 = 1 МПа
#endif
						double beta1 = 0.6 + 1.14 * qs0/qs; // (4.10) стр.62
						bool is_pesok;
						if (this->IsPesokOrGlina(karotazh_svai_->GetDocumentPoint(is).z, is_pesok))
						{
							printf("is_pesok = %d\n", is_pesok);
							//double qs = pck/100.;//перевод из тс/м^2 в МПа
							
							if (is_pesok)
							{
								beta1 = 1.27 - 0.73 * log10(qs/qs0);// (4.15) стр.66
							}
							else
							{
								beta1 = 1.01 - 0.7 * log10(qs/qs0);// (4.17) стр.67
							}
						}


						double R = beta1 * qs; // (4.7) стр.60

						double RA = R*A;

						printf ("RA = %f sv20 = %f\n", RA, karotazh_svai_->GetDocumentPoint(is).v);


						double fh;
						if(!this->FindIntegralPCB(karotazh_pcb, ustje, glubina, fh))
						{
						}

						double Fu = RA + fh * u; //(4.6) стр.59


						CPoint4 pt_test;
						pt_test.bVisible = true;
						pt_test.x = karotazh_svai_->GetDocumentPoint(is).x;
						pt_test.y = karotazh_svai_->GetDocumentPoint(is).y;
						pt_test.z = karotazh_svai_->GetDocumentPoint(is).z;
						pt_test.v = Fu;

						if (Well_3D::karotazh_list[kar_index_test_svai].vmax < pt_test.v)
							Well_3D::karotazh_list[kar_index_test_svai].vmax = pt_test.v;
						
						if (Well_3D::karotazh_list[kar_index_test_svai].vmin > pt_test.v)
							Well_3D::karotazh_list[kar_index_test_svai].vmin = pt_test.v;

						karotazh_test_svai->PushBack(pt_test);


						CPoint4 pt_RA;
						pt_RA.bVisible = true;
						pt_RA.x = karotazh_svai_->GetDocumentPoint(is).x;
						pt_RA.y = karotazh_svai_->GetDocumentPoint(is).y;
						pt_RA.z = karotazh_svai_->GetDocumentPoint(is).z;
						pt_RA.v = RA;

						if (Well_3D::karotazh_list[kar_index_RA].vmax < pt_RA.v)
							Well_3D::karotazh_list[kar_index_RA].vmax = pt_RA.v;
						
						if (Well_3D::karotazh_list[kar_index_RA].vmin > pt_RA.v)
							Well_3D::karotazh_list[kar_index_RA].vmin = pt_RA.v;

						karotazh_RA->PushBack(pt_RA);


						CPoint4 pt_fuh;
						pt_fuh.bVisible = true;
						pt_fuh.x = karotazh_svai_->GetDocumentPoint(is).x;
						pt_fuh.y = karotazh_svai_->GetDocumentPoint(is).y;
						pt_fuh.z = karotazh_svai_->GetDocumentPoint(is).z;
						pt_fuh.v = fh*u;

						if (Well_3D::karotazh_list[kar_index_fuh].vmax < pt_fuh.v)
							Well_3D::karotazh_list[kar_index_fuh].vmax = pt_fuh.v;
						
						if (Well_3D::karotazh_list[kar_index_fuh].vmin > pt_fuh.v)
							Well_3D::karotazh_list[kar_index_fuh].vmin = pt_fuh.v;

						karotazh_fuh->PushBack(pt_fuh);

					}
					else
						printf("\n");
				}
			}
		}
	}
}

void Well_3D::AddPtStZond(
	long id_ust,
	double glyb,
	const char * ust_name,
	long typ_zond, long n_shema,
	double Kg, double Kf, double Bg, double Bf, double shtanga_d)
{
	StatZondData2 data;
	data.id_ust = id_ust;
	data.glyb = glyb;

	data.ust_name = ust_name;
	data.typ_zond = typ_zond;
	data.n_shema = n_shema;

	data.Kg = Kg;
	data.Kf = Kf;
	data.Bg = Bg;
	data.Bf = Bf;

	data.shtanga_d = shtanga_d;

	this->m_stat_zond.Add(data);
}
void Well_3D::AddStZond(
	long npp, long typgr,
	double h, double q0, double f0, 
	double dh, double fsr, 
	unsigned char bStat,
	long id_ige, double pck
	)
{
	StatZondData1 data;
	data.npp = npp;
	data.typgr = typgr;
	data.h = h;
	data.q0 = q0;
	data.f0 = f0;
	data.dh = dh;
	data.fsr = fsr;
	data.bStat = bStat;
	data.id_ige = id_ige;
	data.pck = pck;

	this->m_stat_zond.Add(data);
}
void Well_3D::AddPCK2FizResults(long npp, long id_calc_param, double param)
{
	PCK2FizResultsData data;
	data.npp = npp;
	data.id_calc_param = id_calc_param;
	data.param = param;

	this->m_pck2fiz_results.Add(id_calc_param, data);
}

void Well_3D::ApplyStZond()
{
	int kar_index;
	for (vector<StatZondData1>::iterator it = this->m_stat_zond.data1.begin();
		it != this->m_stat_zond.data1.end(); it++)
	{
		double h = (*it).h;
		kar_index = Well_3D::GetKarotazhIndex(DYNAMOMETR_KAR_NAME);
		this->AddPointToKarotazh(kar_index, (*it).q0, h);

		kar_index = Well_3D::GetKarotazhIndex(MANOMETR_KAR_NAME);
		this->AddPointToKarotazh(kar_index, (*it).f0, h);

		double q = (*it).GetPCK();
		double f = (*it).GetPCB();

		kar_index = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
		this->AddPointToKarotazh(kar_index, q, h);

		kar_index = Well_3D::GetKarotazhIndex(PCB_KAR_NAME);
		this->AddPointToKarotazh(kar_index, f, h);

		kar_index = Well_3D::GetKarotazhIndex(PCB_PCK_KAR_NAME);
		this->AddPointToKarotazh(kar_index, f/q, h);


		long npp = (*it).npp;
		if (this->m_pSurfDoc)
		{
			for (vector<PCK2FizParamsData>::iterator it_par = this->m_pSurfDoc->m_pck2fiz_params.datas.begin();
				it_par != this->m_pSurfDoc->m_pck2fiz_params.datas.end(); it_par++)
			{
				//(*it_par).desc;
				kar_index = Well_3D::GetKarotazhIndex((*it_par).calc_param.c_str());
				map<long, PCK2FizResult>::iterator it_res = this->m_pck2fiz_results.datas.find((*it_par).id_calc_param);
				if (it_res != this->m_pck2fiz_results.datas.end())
				{
					map<long, PCK2FizResultsData>::iterator it_val = (*it_res).second.datas.find(npp);
					if (it_val != (*it_res).second.datas.end())
					{
						this->AddPointToKarotazh(kar_index, (*it_val).second.param, h);
					}
				}
			}
		}
	}
}
void Well_3D::Palja(
	double h, double qc, double beta1, double Rs, double fs, double beta2, double f, double RsA, double fhu, double Fu)
{
	PaljaData1 data;
	data.h = h;
	data.qc = qc;
	data.beta1 = beta1;
	data.Rs = Rs;
	data.fs = fs;
	data.beta2 = beta2;
	data.f = f;
	data.RsA = RsA;
	data.fhu = fhu;
	data.Fu			= Fu;

	this->m_palja.Add(data);
}

void Well_3D::PtPalja(
	long id_typ,
	double pereriz_x, double pereriz_y, double A, double u, double glyb, double RsA, double fhu, double pz,
	long id_snip, double Fu)
{
	PaljaData2 data;
	data.id_typ		= id_typ;
	data.pereriz_x	= pereriz_x;
	data.pereriz_y	= pereriz_y;
	data.A			= A;
	data.u			= u;
	data.glyb		= glyb;
	data.RsA		= RsA;
	data.fhu		= fhu;
	data.pz			= pz;
	data.id_snip	= id_snip;
	data.Fu			= Fu;

	this->m_palja.Add(data);

}
void Well_3D::ApplyPalja()
{
	//здесь вставаить перевод несущей способности свай в каротажи
	//чтобы затем из каротажей готовить куб
	for (vector<PaljaData1>::iterator it = this->m_palja.data1.begin();
		it != this->m_palja.data1.end(); it++)
	{
		int kar_index = Well_3D::GetKarotazhIndex(PALJA_DB_KAR_NAME);
		this->AddPointToKarotazh(kar_index, (*it).Fu, (*it).h);

	}


}

void Well_3D::Lito0(long id_ige, double h0, double h1)
{
	db_lito_data data;
	data.id_ige		= id_ige;
	data.h0			= h0;
	data.h1			= h1;
	this->m_db_lito0.Add(data);
}
void Well_3D::Lito(long id_ige, double h0, double h1)
{
	db_lito_data data;
	data.id_ige		= id_ige;
	data.h0			= h0;
	data.h1			= h1;
	this->m_db_lito.Add(data);
}
void Well_3D::Apply_Lito0()
{
	//bUnEdited = true;
	CPoint3 ustje;
	if (this->m_pSurfDoc && this->GetUstje(ustje))
	{
		WellColomn * w_colomn_podoshva = NULL;
		w_colomn_podoshva = 
			this->FindWellColomn(WellElement::type::litho_podoshva);
		if (w_colomn_podoshva)
		{
			for(vector<db_lito_data>::iterator it_lito = this->m_db_lito0.data1.begin();
				it_lito != this->m_db_lito0.data1.end(); it_lito++)
			{
				for (vector<IGE_Data>::iterator it_ige = 
					this->m_pSurfDoc->m_db_ige0.data.begin();
					it_ige != this->m_pSurfDoc->m_db_ige0.data.end();
					it_ige++)
				{
					if ((*it_ige).ige_filled && (*it_ige).ige.id_ige == (*it_lito).id_ige)
					{
						WellElement * w_elem = w_colomn_podoshva->AddNewWellElement((*it_ige).ige.ige);
						if (w_elem)
						{
							Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(w_elem);
							if (wlitp)
							{
								string key = (*it_ige).ige.ige;
								wlitp->key = key;
								wlitp->zk = ustje.z - (*it_lito).h0;
								wlitp->zp = ustje.z - (*it_lito).h1;

								double zaboj_altituda;
								if (this->GetZaboj(zaboj_altituda) && zaboj_altituda > wlitp->zp)
									this->SetZaboj(wlitp->zp);

								if ((*it_ige).grunt_filled)
								{
									long id_genezis = (*it_ige).grunt.id_genezis;
									map<long, genezis_data>::iterator found_genezis = this->m_pSurfDoc->m_db_genezis.data1.find(id_genezis);
									if (found_genezis != this->m_pSurfDoc->m_db_genezis.data1.end())
									{
										BYTE r = (*found_genezis).second.r;
										BYTE g = (*found_genezis).second.g;
										BYTE b = (*found_genezis).second.b;

										wlitp->color = RGB(r,g,b);
									}

									long id_umpoz = (*it_ige).grunt.id_umpoz;
									map<long, umpoz_data>::iterator found_umpoz = this->m_pSurfDoc->m_db_umpoz.data1.find(id_umpoz);
									if (found_umpoz != this->m_pSurfDoc->m_db_umpoz.data1.end())
									{
										wlitp->id_umpoz		= (*found_umpoz).second.id_umpoz;
										wlitp->umpoz		= (*found_umpoz).second.umpoz;
										wlitp->hatchacad	= (*found_umpoz).second.hatchacad;
										wlitp->angle		= (*found_umpoz).second.angle;
										wlitp->scale		= (*found_umpoz).second.scale;
									}
								}							
							}
						}
						break;
					}
				}
			}
		}
	}
}
void Well_3D::ApplyLito_well_lito_podoshva()
{
	//bUnEdited = true;
	CPoint3 ustje;
	if (this->m_pSurfDoc && this->GetUstje(ustje))
	{
		WellColomn * w_colomn_podoshva = NULL;
		w_colomn_podoshva = 
			this->FindWellColomn(WellElement::type::litho_podoshva);
		if (w_colomn_podoshva)
		{
			for(vector<db_lito_data>::iterator it_lito = this->m_db_lito.data1.begin();
				it_lito != this->m_db_lito.data1.end(); it_lito++)
			{
				for (vector<IGE_Data>::iterator it_ige = 
					this->m_pSurfDoc->m_db_ige.data.begin();
					it_ige != this->m_pSurfDoc->m_db_ige.data.end();
					it_ige++)
				{
					if ((*it_ige).ige_filled && (*it_ige).ige.id_ige == (*it_lito).id_ige)
					{
						WellElement * w_elem = w_colomn_podoshva->AddNewWellElement((*it_ige).ige.ige);
						if (w_elem)
						{
							Well_Litho_Podoshva * wlitp = dynamic_cast<Well_Litho_Podoshva *>(w_elem);
							if (wlitp)
							{
								string key = (*it_ige).ige.ige;
								wlitp->key = key;
								wlitp->id_ige = (*it_ige).ige.id_ige;
								wlitp->zk = ustje.z - (*it_lito).h0;
								wlitp->zp = ustje.z - (*it_lito).h1;

								double zaboj_altituda;
								if (this->GetZaboj(zaboj_altituda) && zaboj_altituda > wlitp->zp)
									this->SetZaboj(wlitp->zp);

								if ((*it_ige).grunt_filled)
								{
									long id_genezis = (*it_ige).grunt.id_genezis;
									map<long, genezis_data>::iterator found_genezis = this->m_pSurfDoc->m_db_genezis.data1.find(id_genezis);
									if (found_genezis != this->m_pSurfDoc->m_db_genezis.data1.end())
									{
										BYTE r = (*found_genezis).second.r;
										BYTE g = (*found_genezis).second.g;
										BYTE b = (*found_genezis).second.b;

										wlitp->color = RGB(r,g,b);
									}

									long id_umpoz = (*it_ige).grunt.id_umpoz;
									map<long, umpoz_data>::iterator found_umpoz = this->m_pSurfDoc->m_db_umpoz.data1.find(id_umpoz);
									if (found_umpoz != this->m_pSurfDoc->m_db_umpoz.data1.end())
									{
										wlitp->id_umpoz		= (*found_umpoz).second.id_umpoz;
										wlitp->umpoz		= (*found_umpoz).second.umpoz;
										wlitp->hatchacad	= (*found_umpoz).second.hatchacad;
										wlitp->angle		= (*found_umpoz).second.angle;
										wlitp->scale		= (*found_umpoz).second.scale;
									}
								}							
							}
						}
						break;
					}
				}
			}
		}
	}
}
void Well_3D::ApplyLito_well_ige_podoshva()
{
	//bUnEdited = false;
	CPoint3 ustje;
	if (this->m_pSurfDoc && this->GetUstje(ustje))
	{
		WellColomn * w_colomn_podoshva = NULL;
		w_colomn_podoshva = 
			this->FindWellColomn(WellElement::type::IGE_podoshva);
		if (w_colomn_podoshva)
		{
			for(vector<db_lito_data>::iterator it_lito = this->m_db_lito.data1.begin();
				it_lito != this->m_db_lito.data1.end(); it_lito++)
			{
				for (vector<IGE_Data>::iterator it_ige = 
					this->m_pSurfDoc->m_db_ige.data.begin();
					it_ige != this->m_pSurfDoc->m_db_ige.data.end();
					it_ige++)
				{
					if ((*it_ige).ige_filled && (*it_ige).ige.id_ige == (*it_lito).id_ige)
					{
						WellElement * w_elem = w_colomn_podoshva->AddNewWellElement((*it_ige).ige.ige);
						if (w_elem)
						{
							Well_IGE_Podoshva * wigep = dynamic_cast<Well_IGE_Podoshva *>(w_elem);
							if (wigep)
							{
								string key = (*it_ige).ige.ige;
								wigep->key = key;
								wigep->id_ige = (*it_ige).ige.id_ige;

								wigep->zk = ustje.z - (*it_lito).h0;
								wigep->zp = ustje.z - (*it_lito).h1;

								double zaboj_altituda;
								if (this->GetZaboj(zaboj_altituda) && zaboj_altituda > wigep->zp)
									this->SetZaboj(wigep->zp);

								if ((*it_ige).grunt_filled)
								{
									long id_genezis = (*it_ige).grunt.id_genezis;
									map<long, genezis_data>::iterator found_genezis = this->m_pSurfDoc->m_db_genezis.data1.find(id_genezis);
									if (found_genezis != this->m_pSurfDoc->m_db_genezis.data1.end())
									{
										BYTE r = (*found_genezis).second.r;
										BYTE g = (*found_genezis).second.g;
										BYTE b = (*found_genezis).second.b;

										wigep->color = RGB(r,g,b);
									}
									long id_umpoz = (*it_ige).grunt.id_umpoz;
									map<long, umpoz_data>::iterator found_umpoz = this->m_pSurfDoc->m_db_umpoz.data1.find(id_umpoz);
									if (found_umpoz != this->m_pSurfDoc->m_db_umpoz.data1.end())
									{
										wigep->id_umpoz		= (*found_umpoz).second.id_umpoz;
										wigep->umpoz		= (*found_umpoz).second.umpoz;
										wigep->hatchacad	= (*found_umpoz).second.hatchacad;
										wigep->angle		= (*found_umpoz).second.angle;
										wigep->scale		= (*found_umpoz).second.scale;
									}
								}

								// GridDataPointRef
                                // как инициализировать ссылку на гриддату
								//wigep->grid_data_point_zk;
								//wigep->grid_data_point_zp;

								if (this->m_pSurfDoc)
								{
									double epsilon = 1e-6;// 1 mm

									bool to_find_zk_gd = true;
									bool to_find_zp_gd = true;

									bool found_zk_gd = false;
									bool found_zp_gd = false;

									for (map<long, db_griddata_surf>::iterator 
										it_gd_srf = this->m_pSurfDoc->m_db_griddata.datas.begin();
										it_gd_srf != this->m_pSurfDoc->m_db_griddata.datas.end();
										it_gd_srf++)
									{
										for (map<long, db_griddata_item>::iterator 
											it_gd_item = (*it_gd_srf).second.data1.begin();
											it_gd_item != (*it_gd_srf).second.data1.end();
										it_gd_item++)
										{
											if (to_find_zk_gd)
											{
												double dist_to_zk = Distance(
													(*it_gd_item).second.x,
													(*it_gd_item).second.y,
													(*it_gd_item).second.z,
													ustje.x,
													ustje.y,
													wigep->zk);

												if (dist_to_zk < epsilon)
												{
													to_find_zk_gd = false;
													found_zk_gd = true;													
													
													wigep->grid_data_point_zk.id_point = 
														(*it_gd_item).second.id_point;
													wigep->grid_data_point_zk.id_surf =
														(*it_gd_item).second.id_surf;
												}
											}

											if (to_find_zp_gd)
											{
												double dist_to_zp = Distance(
													(*it_gd_item).second.x,
													(*it_gd_item).second.y,
													(*it_gd_item).second.z,
													ustje.x,
													ustje.y,
													wigep->zp);

												if (dist_to_zp < epsilon)
												{
													to_find_zp_gd = false;
													found_zp_gd = true;													
													
													wigep->grid_data_point_zp.id_point = 
														(*it_gd_item).second.id_point;
													wigep->grid_data_point_zp.id_surf =
														(*it_gd_item).second.id_surf;
												}
											}

											if (found_zk_gd && found_zp_gd)
												goto e_grid_data_point_inited;

										}
									}
e_grid_data_point_inited:
									;
								}

							}
						}
						break;
					}
				}
			}
		}
	}
}
void Well_3D::Voda(long horizont,
	double hv_z, double hv_v,
	SYSTEMTIME dv)
{
	db_voda_data data;
	data.horizont		= horizont;
	data.hv_z			= hv_z;
	data.hv_v			= hv_v;
	data.dv				= dv;
	this->m_db_voda.Add(data);
}
void Well_3D::ApplyVoda()
{
	CPoint3 ustje;
	if (this->GetUstje(ustje))
	{
		WellColomn * w_colomn_hydro_projavlenie = NULL;
		w_colomn_hydro_projavlenie = this->FindWellColomn(WellElement::type::hydro_projavlenie);
		if (w_colomn_hydro_projavlenie)
		{
			for(vector<db_voda_data>::iterator it = this->m_db_voda.data1.begin();
				it != this->m_db_voda.data1.end(); it++)
			{
				long gorizont = (*it).horizont;
				char str[128];
				sprintf(str, "горизонт %d вода появилась", gorizont);
				WellElement * w_elem = w_colomn_hydro_projavlenie->AddNewWellElement(str);
				if (w_elem)
				{
					Well_Hydro_Projavlenie * whydp = dynamic_cast<Well_Hydro_Projavlenie *>(w_elem);
					if (whydp)
					{
						whydp->zp = ustje.z - (*it).hv_z;
						whydp->ustanovlen = false;
						whydp->horizont = gorizont;
					}
				}
				sprintf(str, "горизонт %d вода установилась", gorizont);
				w_elem = w_colomn_hydro_projavlenie->AddNewWellElement(str);
				if (w_elem)
				{
					Well_Hydro_Projavlenie * whydp = dynamic_cast<Well_Hydro_Projavlenie *>(w_elem);
					if (whydp)
					{
						whydp->zp = ustje.z - (*it).hv_v;
						whydp->ustanovlen = true;
						whydp->horizont = gorizont;
					}
				}
			}
		}
	}
}

void Well_3D::TestSvai2()
{
	printf("Well_3D::TestSvai(%s)\n", this->GetIDString());
	int kar_index_pck = Well_3D::GetKarotazhIndex(PCK_KAR_NAME);
	int kar_index_pcb = Well_3D::GetKarotazhIndex(PCB_KAR_NAME);
	int kar_index_pck_pcb = Well_3D::GetKarotazhIndex(PCB_PCK_KAR_NAME);

	int kar_index_svai_20 = Well_3D::GetKarotazhIndex(SVAI_20_20_KAR_NAME);
	int kar_index_svai_25 = Well_3D::GetKarotazhIndex(SVAI_25_25_KAR_NAME);
	int kar_index_svai_30 = Well_3D::GetKarotazhIndex(SVAI_30_30_KAR_NAME);
	int kar_index_svai_35 = Well_3D::GetKarotazhIndex(SVAI_35_35_KAR_NAME);
	int kar_index_svai_40 = Well_3D::GetKarotazhIndex(SVAI_40_40_KAR_NAME);

	Karotazh * karotazh_pck = this->GetKarotazh(kar_index_pck);
	Karotazh * karotazh_pcb = this->GetKarotazh(kar_index_pcb);
	Karotazh * karotazh_pck_pcb = this->GetKarotazh(kar_index_pck_pcb);
	Karotazh * karotazh_svai_20 = this->GetKarotazh(kar_index_svai_20);
	Karotazh * karotazh_svai_25 = this->GetKarotazh(kar_index_svai_25);
	Karotazh * karotazh_svai_30 = this->GetKarotazh(kar_index_svai_30);
	Karotazh * karotazh_svai_35 = this->GetKarotazh(kar_index_svai_35);
	Karotazh * karotazh_svai_40 = this->GetKarotazh(kar_index_svai_40);

					
	double d = 0.4;
	Karotazh * karotazh_svai_ = karotazh_svai_40;
	
	CPoint3 ustje;

	if (karotazh_pck && karotazh_pcb && GetUstje(ustje))
	{
		int kar_index_test_svai = Well_3D::GetKarotazhIndex("TestSvai");
		Karotazh * karotazh_test_svai = this->GetKarotazh(kar_index_test_svai);
		
		if (!karotazh_test_svai)
			karotazh_test_svai = this->AddKarotazh(kar_index_test_svai);

		int kar_index_RA = Well_3D::GetKarotazhIndex("RA");
		Karotazh * karotazh_RA = this->GetKarotazh(kar_index_RA);
		
		if (!karotazh_RA)
			karotazh_RA = this->AddKarotazh(kar_index_RA);

		int kar_index_fuh = Well_3D::GetKarotazhIndex("fuh");
		Karotazh * karotazh_fuh = this->GetKarotazh(kar_index_fuh);
		
		if (!karotazh_fuh)
			karotazh_fuh = this->AddKarotazh(kar_index_fuh);


		if (karotazh_test_svai && karotazh_RA && karotazh_fuh)
		{
			karotazh_test_svai->Free();
			karotazh_RA->Free();

			if (karotazh_svai_)
			{
				for (size_t is = 0; is < karotazh_svai_->GetPointsNumber(); is++)
				{
					double A = d*d;
					double u = 4*d;
					double glubina = ustje.z - karotazh_svai_->GetDocumentPoint(is).z;
					
					printf("glubina = %f\t", glubina);
					double mean_pck;
					if (FindMeanPCK(karotazh_pck, ustje, glubina, d, mean_pck))
					{
						// Л.Г.Мариупольский 
						// Исследования грунтов для проектирования свайных фундаментов
						// Москва, Стройиздат, 1989
						double qs = mean_pck;
#if USE_DB_PSK_EDINICY
						double qs0 = 1.0;// мы уже перевели pck в МПа (как в базе) 
#else
						double qs0 = 100.0;// 100 тс/м^2 = 1 МПа
#endif
						double beta1 = 0.6 + 1.14 * qs0/qs; // (4.10) стр.62
						bool is_pesok;
						if (this->IsPesokOrGlina(karotazh_svai_->GetDocumentPoint(is).z, is_pesok))
						{
							printf("is_pesok = %d\n", is_pesok);
							//double qs = pck/100.;//перевод из тс/м^2 в МПа
							
							if (is_pesok)
							{
								beta1 = 1.27 - 0.73 * log10(qs/qs0);// (4.15) стр.66
							}
							else
							{
								beta1 = 1.01 - 0.7 * log10(qs/qs0);// (4.17) стр.67
							}
						}


						double R = beta1 * qs; // (4.7) стр.60

						double RA = R*A;

						printf ("RA = %f sv20 = %f\n", RA, karotazh_svai_->GetDocumentPoint(is).v);


						double fh;
						if(!this->FindIntegralPCB(karotazh_pcb, ustje, glubina, fh))
						{
						}

						double Fu = RA + fh * u; //(4.6) стр.59


						CPoint4 pt_test;
						pt_test.bVisible = true;
						pt_test.x = karotazh_svai_->GetDocumentPoint(is).x;
						pt_test.y = karotazh_svai_->GetDocumentPoint(is).y;
						pt_test.z = karotazh_svai_->GetDocumentPoint(is).z;
						pt_test.v = Fu;

						if (Well_3D::karotazh_list[kar_index_test_svai].vmax < pt_test.v)
							Well_3D::karotazh_list[kar_index_test_svai].vmax = pt_test.v;
						
						if (Well_3D::karotazh_list[kar_index_test_svai].vmin > pt_test.v)
							Well_3D::karotazh_list[kar_index_test_svai].vmin = pt_test.v;

						karotazh_test_svai->PushBack(pt_test);


						CPoint4 pt_RA;
						pt_RA.bVisible = true;
						pt_RA.x = karotazh_svai_->GetDocumentPoint(is).x;
						pt_RA.y = karotazh_svai_->GetDocumentPoint(is).y;
						pt_RA.z = karotazh_svai_->GetDocumentPoint(is).z;
						pt_RA.v = RA;

						if (Well_3D::karotazh_list[kar_index_RA].vmax < pt_RA.v)
							Well_3D::karotazh_list[kar_index_RA].vmax = pt_RA.v;
						
						if (Well_3D::karotazh_list[kar_index_RA].vmin > pt_RA.v)
							Well_3D::karotazh_list[kar_index_RA].vmin = pt_RA.v;

						karotazh_RA->PushBack(pt_RA);


						CPoint4 pt_fuh;
						pt_fuh.bVisible = true;
						pt_fuh.x = karotazh_svai_->GetDocumentPoint(is).x;
						pt_fuh.y = karotazh_svai_->GetDocumentPoint(is).y;
						pt_fuh.z = karotazh_svai_->GetDocumentPoint(is).z;
						pt_fuh.v = fh*u;

						if (Well_3D::karotazh_list[kar_index_fuh].vmax < pt_fuh.v)
							Well_3D::karotazh_list[kar_index_fuh].vmax = pt_fuh.v;
						
						if (Well_3D::karotazh_list[kar_index_fuh].vmin > pt_fuh.v)
							Well_3D::karotazh_list[kar_index_fuh].vmin = pt_fuh.v;

						karotazh_fuh->PushBack(pt_fuh);

					}
					else
						printf("\n");
				}
			}
		}
	}
}

bool Well_3D::AddPointToKarotazh(int kar_index, double value, double glubina)
{
	//printf("Well_3D::AddPointToKarotazh(int kar_index = %d, double value = %f, double glubina = %f)\n", kar_index, value, glubina);
	
	if (kar_index >= 0 && kar_index < Well_3D::karotazh_list.size())
	{
		Karotazh * karotazh = this->GetKarotazh(kar_index);
		if (!karotazh)
			karotazh = this->AddKarotazh(kar_index);

		CPoint3 ustje;
		
		if (karotazh && GetUstje(ustje))
		{
			//this cells not empty
			CPoint4     pt;
			pt.bVisible = true;
			pt.v		= value;
			pt.z		= ustje.z - glubina;
			pt.x		= ustje.x;
			pt.y		= ustje.y;

			if (karotazh->Repeated3(pt) == -1)
			{
				if (Well_3D::karotazh_list[kar_index].vmax < pt.v)
					Well_3D::karotazh_list[kar_index].vmax = pt.v;
				
				if (Well_3D::karotazh_list[kar_index].vmin > pt.v)
					Well_3D::karotazh_list[kar_index].vmin = pt.v;

				karotazh->PushBack(pt);

				return true;
			}
			else
			{
				char str2[4096];
				sprintf(str2, "Well_3D::AddPointToKarotazh(kar_index = %d, value = %f, glubina = %f)\0", kar_index, value, glubina);
				char str1[4096];
				sprintf(str1, "Well \"%s\" Repeate Karotazh \"%s\" Point\0", this->GetIDString(), karotazh_list[kar_index].name.c_str());
				MessageBox(0, str1, str2, 0);
				return false;
			}
		}
		
	}
	return false;
}
bool Well_3D::GetUstje(CPoint3 & pt3)
{
	if (this->GetPointsNumber()>1)
	{
		pt3 = m_vdPoints[1];
		return true;
	}
	return false;
}
bool Well_3D::GetZaboj(CPoint3 & pt3)
{
	if (this->GetPointsNumber()>1)
	{
		pt3 = m_vdPoints[0];
		return true;
	}
	return false;
}
void Well_3D::SetZaboj(double altituda)
{
	if (this->GetPointsNumber()>1)
	{
		//инициализируем забой
		m_vdPoints[0].z = altituda;
		m_vvPoints[0].z = altituda;
	}
}
bool Well_3D::GetZaboj(double &altituda)
{
	if (this->GetPointsNumber()>1)
	{
		//забой
		altituda = m_vdPoints[0].z;
		return true;
	}
	return false;
}

void Well_3D::WellInit1(vector<vector<cell> >::iterator pdrill)
{
	m_type = 1;
	Free();
	// две точки - первая устье, вторая - забой
	AllocPoints(2);
	m_vdPoints[0].bVisible = true;
	m_vdPoints[1].bVisible = true;
	m_vvPoints[0].bVisible = true;
	m_vvPoints[1].bVisible = true;
	// итератор по ячейкам таблицы
	vector<cell>::iterator Iter;
	for ( Iter = pdrill->begin(); Iter != pdrill->end(); Iter++)
	{
		cell temp;
		temp = *Iter;
		switch(temp.col)
		{
		case 0://id drill
			{
#if USE_STRING_IN_THE_CELL
				sID = temp.str;
#else
				int len_of_str = min(CELL_S_N_CHARS - 1, strlen(temp.s));
				strncpy(sID,
					temp.s,
					len_of_str);
				sID[len_of_str] = '\0';
#endif
			}
		case 1://X
			{
				m_vdPoints[0].x = temp.value;
				m_vvPoints[0].x = temp.value;
				m_vdPoints[1].x = temp.value;
				m_vvPoints[1].x = temp.value;
			}
			break;
		case 2://Y
			{
				m_vdPoints[0].y = temp.value;
				m_vvPoints[0].y = temp.value;
				m_vdPoints[1].y = temp.value;
				m_vvPoints[1].y = temp.value;
			}
			break;
		case 3://ustje altitude
			{
				m_vdPoints[1].z = temp.value;
				m_vvPoints[1].z = temp.value;
				//инициализируем забой на случай если не дана глубина забоя
				m_vdPoints[0].z = temp.value;
				m_vvPoints[0].z = temp.value;
			}
			break;
		case 4://zaboj altitude
			{
				m_vdPoints[0].z = temp.value;
				m_vvPoints[0].z = temp.value;
			}
			break;

		}
	}
}

void Well_3D::WellInit(long id_kt,
					   const char * _name, long kt_idtyp, double X, double Y, double ustje, double zaboj, long id_bur_type, long d_bur, string data_bur)
{

	char well_id[128];
	//sprintf(well_id, "%ld", id_kt);
	sprintf(well_id, "%s", _name);
	sID = well_id;

	this->name = _name;

	m_id_kt = id_kt;// ID комплексной точки
	m_kt_idtyp = kt_idtyp;//тип комплексной точки

	m_id_bur_type = id_bur_type; // способ бурения
	m_d_bur = d_bur; // диаметр бурения
	m_data_bur = data_bur; // дата бурения

	m_type = 1;
	Free();
	// две точки - первая устье, вторая - забой
	AllocPoints(2);
	m_vdPoints[0].bVisible = true;
	m_vdPoints[1].bVisible = true;
	m_vvPoints[0].bVisible = true;
	m_vvPoints[1].bVisible = true;




	m_vdPoints[0].x = X;
	m_vvPoints[0].x = X;
	m_vdPoints[1].x = X;
	m_vvPoints[1].x = X;


	m_vdPoints[0].y = Y;
	m_vvPoints[0].y = Y;
	m_vdPoints[1].y = Y;
	m_vvPoints[1].y = Y;


	m_vdPoints[1].z = ustje;
	m_vvPoints[1].z = ustje;
	//инициализируем забой на случай если не дана глубина забоя
	m_vdPoints[0].z = ustje;
	m_vvPoints[0].z = ustje;


	m_vdPoints[0].z = zaboj;
	m_vvPoints[0].z = zaboj;
}

HTREEITEM Well_3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	sprintf(szItemText, "ID_KT = %d name = %s len = %d color = %u", 
		m_id_kt, 
		this->GetName().c_str(), 
		GetPointsNumber(), 
		m_color);
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	return h2;
}
void Karotazh::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	this->Primitive3D<CPoint4>::Zoom(
		zoomX,zoomY,zoomZ, 
		x_mean,
		y_mean,
		z_mean
		);

		
	double vmin;

	if (this->m_index < 0 || this->m_index >= Well_3D::karotazh_list.size())
		return;
		
	if (Well_3D::karotazh_list[this->m_index].scale_from_zero)
	{
		vmin = 0.0;
		if (Well_3D::karotazh_list[this->m_index].vmin < 0.0)
		{
			char str[1024];
			sprintf(str, "Can not Scale from zero because VMIN = %f < 0.0\n", Well_3D::karotazh_list[this->m_index].vmin);
			printf(str);
			MessageBox(0, str, "Karotazh::Zoom", 0);

			vmin = Well_3D::karotazh_list[this->m_index].vmin;
		}
	}
	else vmin = Well_3D::karotazh_list[this->m_index].vmin;

	/*printf("Karotazh::Zoom index = %d vmin = %f scale_from_zero = %d logarithmic_scale = %d scale = %f\n", 
		this->m_index, 
		vmin, 
		Well_3D::karotazh_list[this->m_index].scale_from_zero,
		Well_3D::karotazh_list[this->m_index].logarithmic_scale,
		Well_3D::karotazh_list[this->m_index].scale);*/

	for (size_t ipoint = 0; ipoint < this->GetPointsNumber(); ipoint++)
	{		
		m_vvPoints[ipoint].v = 				
			Well_3D::karotazh_list[this->m_index].scale * (Well_3D::karotazh_list[this->m_index].logarithmic_scale ?
			log10(m_vdPoints[ipoint].v - vmin ) / log10(Well_3D::karotazh_list[this->m_index].vmax - vmin)
			:
			(m_vdPoints[ipoint].v - vmin ) / (Well_3D::karotazh_list[this->m_index].vmax - vmin)
			);
	}

}
bool Karotazh::SaveAsDat(FILE * stream)
{
	if (stream)
	{
		for(size_t i = 0; i < this->GetPointsNumber(); i++)
		{
			fprintf(stream, "%lf, %lf, %lf, %lf, %d, %s\n", 
				this->GetDocumentPoint(i).x,
				this->GetDocumentPoint(i).y,
				this->GetDocumentPoint(i).z,
				this->GetDocumentPoint(i).v,
				m_index,
				m_index >= 0 && m_index < Well_3D::karotazh_list.size() ? Well_3D::karotazh_list[m_index].name.c_str() : ""
				);
		}
		return true;
	}
	return false;
}



bool Karotazh::UpdateExtremums()
{
	//		printf("Karotazh::UpdateExtremums() index = %d points = %u\n", this->m_index, this->GetPointsNumber());
	bool start = true;
	for (size_t ipoint = 0; ipoint < this->GetPointsNumber(); ipoint++)
	{		
		//if(this->m_index == 10)printf("m_vdPoints[ipoint].v = %f\n", m_vdPoints[ipoint].v);
		if (start)
		{
			m_min_v = m_max_v = m_vdPoints[ipoint].v;
			start = false;
		}
		else
		{
			if (m_min_v > m_vdPoints[ipoint].v) m_min_v = m_vdPoints[ipoint].v;
			if (m_max_v < m_vdPoints[ipoint].v) m_max_v = m_vdPoints[ipoint].v;
		}
	}
	bool result = !start && this->Primitive3D<CPoint4>::UpdateExtremums();

	/*printf("Karotazh::UpdateExtremums() index = %d  m_ptMin = [%f %f %f] m_ptMax = [%f %f %f] m_min_v, m_max_v[%f %f]\n", 
		this->m_index,
		
		this->m_ptMin.x,
		this->m_ptMin.y,
		this->m_ptMin.z,

		this->m_ptMax.x,
		this->m_ptMax.y,
		this->m_ptMax.z,

		m_min_v, m_max_v
		);*/

	return result;
}
bool Well_3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;
		
	if (this->Primitive3D<CPoint3>::UpdateExtremums())
	{
		vptmax.push_back(this->GetMax());
		vptmin.push_back(this->GetMin());
	}

	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_karotazhy.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_karotazhy.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void Well_3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	this->Primitive3D<CPoint3>::Zoom(
		zoomX,zoomY,zoomZ, 
		x_mean,
		y_mean,
		z_mean
		);

	if (this->m_karotazhy.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_karotazhy.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}


bool Well_3D::OnProfile(Profile3D * on)
{	
	double dist_to_plane;
	CPoint2 profile;

	if (GetPointsNumber() < 2) return false;

	//Convert3D_To_2D
	on->Projection(m_vdPoints[1], profile, dist_to_plane);//ustje altitude
	return dist_to_plane == 0.0;
}
bool Well_3D::IsSelectedWell(gdiplus_map_view * gv, Profile3D * on, int mouse_x, int mouse_y, double & dist_to_line_object, WhatSelected& ws)
{
	bool result = false;
	if (!this->IsCheckedEx()) return result;
	double search_radius = fabs(gv->lines_points_radius);
	gv->PreConvertingFromWorldToScreen();
	double dist_to_plane;
	CPoint2 profile;		
	fGL x, y;
#if 0
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_lito//		||		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element
		)
	{
		WellColomn * Lito_WellColomn = NULL;
		for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
			it_c != this->well_colomns.end(); it_c++)
		{
			if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
			{
				Lito_WellColomn = &(*it_c);
			}
		}

		if ( Lito_WellColomn )
		{
			CPoint3 ustje, pt;
			if (this->GetUstje(ustje))
			{
				pt = ustje;

				int i = 0;
				for (vector<WellElement*>::iterator it_lito = Lito_WellColomn->well_elements.begin();
					it_lito != Lito_WellColomn->well_elements.end(); it_lito++, i++)
				{
					if (*it_lito)
					{
						pt.z = (*it_lito)->GetZp();
						//Convert3D_To_2D
						on->Projection(pt, profile, dist_to_plane);
						gv->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);

						double dist_to_point = Distance(mouse_x, mouse_y, x, y);

						bool select = dist_to_line_object > dist_to_point;
						

						if (select)
						{
							if (dist_to_line_object > dist_to_point)
								dist_to_line_object = dist_to_point;
							ws.Init(dynamic_cast<Object*>(this), 
								WhatSelected::sel_lito,
								i,-1,
								pt
								);

							result = true;
						}
					}
				}
			}
		}
	}	
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_ige//		||		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element
		)
	{
		WellColomn * IGE_WellColomn = NULL;
		for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
			it_c != this->well_colomns.end(); it_c++)
		{
			if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
			{
				IGE_WellColomn = &(*it_c);
			}
		}

		if ( IGE_WellColomn )
		{
			CPoint3 ustje, pt;
			if (this->GetUstje(ustje))
			{
				pt = ustje;

				int i = 0;
				for (vector<WellElement*>::iterator it_ige = IGE_WellColomn->well_elements.begin();
					it_ige != IGE_WellColomn->well_elements.end(); it_ige++, i++)
				{
					if (*it_ige)
					{
						pt.z = (*it_ige)->GetZp();
						//Convert3D_To_2D
						on->Projection(pt, profile, dist_to_plane);
						gv->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);

						double dist_to_point = Distance(mouse_x, mouse_y, x, y);

						bool select = dist_to_line_object > dist_to_point;
						

						if (select)
						{
							if (dist_to_line_object > dist_to_point)
								dist_to_line_object = dist_to_point;
							ws.Init(dynamic_cast<Object*>(this), 
								WhatSelected::sel_ige,
								i,-1,
								pt
								);

							result = true;
						}
					}
				}
			}
		}
	}	
#endif
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_lito_ige//		||		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element
		)
	{
		double epsilon = 1e-8;
		WellColomn * Lito_WellColomn = NULL;
		WellColomn * IGE_WellColomn = NULL;
		for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
			it_c != this->well_colomns.end(); it_c++)
		{
			if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
			{
				IGE_WellColomn = &(*it_c);
			}
			if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
			{
				Lito_WellColomn = &(*it_c);
			}
		}

		if ( Lito_WellColomn && IGE_WellColomn)
		{
			CPoint3 ustje, pt;
			if (this->GetUstje(ustje))
			{
				pt = ustje;
				double __dist_to_line_object_lito = dist_to_line_object;
				bool result_lito = false;

				int i_ige = -1, i_lito = -1;
				int i = 0;
				for (vector<WellElement*>::iterator it_lito = Lito_WellColomn->well_elements.begin();
					it_lito != Lito_WellColomn->well_elements.end(); it_lito++, i++)
				{
					if (*it_lito)
					{
						pt.z = (*it_lito)->GetZp();
						//Convert3D_To_2D
						on->Projection(pt, profile, dist_to_plane);
						gv->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);

						double dist_to_point = Distance(mouse_x, mouse_y, x, y);

						bool select = __dist_to_line_object_lito > dist_to_point;
						

						if (select)
						{
							if (__dist_to_line_object_lito > dist_to_point)
								__dist_to_line_object_lito = dist_to_point;
							ws.Init(dynamic_cast<Object*>(this), 
								WhatSelected::sel_lito_ige,
								i,-1,
								pt
								);
							i_lito = i;

							result_lito = true;
						}
					}
				}

				double __dist_to_line_object_ige = dist_to_line_object;
				bool result_ige = false;
				i = 0;
				for (vector<WellElement*>::iterator it_ige = IGE_WellColomn->well_elements.begin();
					it_ige != IGE_WellColomn->well_elements.end(); it_ige++, i++)
				{
					if (*it_ige)
					{
						pt.z = (*it_ige)->GetZp();
						//Convert3D_To_2D
						on->Projection(pt, profile, dist_to_plane);
						gv->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);

						double dist_to_point = Distance(mouse_x, mouse_y, x, y);

						bool select = __dist_to_line_object_ige > dist_to_point;
						

						if (select)
						{
							if (__dist_to_line_object_ige > dist_to_point)
								__dist_to_line_object_ige = dist_to_point;
							ws.Init(dynamic_cast<Object*>(this), 
								WhatSelected::sel_lito_ige,
								i,-1,
								pt
								);

							i_ige = i;
							result_ige = true;
						}
					}
				}

				if (fabs (__dist_to_line_object_lito - __dist_to_line_object_ige) < epsilon)
				{
					dist_to_line_object = 0.5 * (__dist_to_line_object_lito + __dist_to_line_object_ige);
					result = result_ige && result_lito && (i_ige == i_lito);
				}
			}
		}

	}	
	if (ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_point
		||
		ws.m_what_to_select == WhatSelected::selected_objects_element_type::sel_no_element)
	{
		for ( size_t i = 1; i < this->GetPointsNumber(); i++)
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
		if (1 < GetPointsNumber())
		{
			//Convert3D_To_2D
			on->Projection(m_vdPoints[1], profile, dist_to_plane);//ustje altitude
			gv->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
		}

		for (UINT i0 = 1, i1 = 2 ; i1 < GetPointsNumber(); i0++, i1++)
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
void Well_3D::SetWellElementsIGEkeys()
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
		{
			(*it_c).SetWellElementsIGEkeys();
		}
	}
}
void Well_3D::SetColorFromIGE()
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
		{
			(*it_c).SetColorFromIGE();
		}
	}
}
void Well_3D::SetWellElementsLithoKeys()
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
		{
			(*it_c).SetWellElementsLithoKeys();
		}
	}
}
void Well_3D::SetColorFromLitho()
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
		{
			(*it_c).SetColorFromLitho();
		}
	}
}
int Well_3D::LithoPodoshvaHowMany(string geo_element_key)
{
	int n = 0;		
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
		{
			n = (*it_c).LithoPodoshvaHowMany(geo_element_key);
 
		}
	}

	return n;
}
void Well_3D::LithoPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse)
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::litho_podoshva)
		{
			(*it_c).LithoPodoshvaToGridData(isurf, podoshva, geo_element_key, pData, reverse);
		}
	}
}

int Well_3D::IGEPodoshvaHowMany(string geo_element_key)
{
	int n = 0;	
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
		{
			n = (*it_c).IGEPodoshvaHowMany(geo_element_key);
		}
	}

	return n;
}
void Well_3D::IGEZabojToGridData(string geo_element_key, GridData * pData)
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
		{
			(*it_c).IGEZabojToGridData(geo_element_key, pData);
		}
	}
}
void Well_3D::IGEPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse)
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
		{
			(*it_c).IGEPodoshvaToGridData(isurf, podoshva, geo_element_key, pData, reverse);
		}
	}
}

void Well_3D::HydroProjavlenieHowMany(map<long, long> &gorizonts, bool ust)
{
	for (vector<WellColomn>::reverse_iterator it_c = this->well_colomns.rbegin();
		it_c != this->well_colomns.rend(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::hydro_projavlenie)
		{
			(*it_c).HydroProjavlenieHowMany(gorizonts, ust);
		}
	}
}

void Well_3D::HydroProjavlenieToGridData(long horizont, bool ust, GridData * pData)
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ( (*it_c).GetWellElementType() == WellElement::type::hydro_projavlenie)
		{
			(*it_c).HydroProjavlenieToGridData(horizont, ust, pData);
		}
	}
}

void Well_3D::UstjaToReliefGriddata(GridData * pData, COLORREF color)
{
	CPoint3 ustje;
	if (this->GetUstje(ustje))
	{
		pData->AddInput(ustje, color);
	}
}

void Well_3D::Drawing_Primitive(wells_draw_list_item * wdli)
{
#if 1
	if (m_pSurfDoc)
	{		
		double vshift = 0.025;

		if (m_type == 1)
		{

			if (GetPointsNumber() > 0 && m_vvPoints[0].bVisible)
			{

				glColor3ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)); 
/*
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//====== Наносим цифровую метку устья
				// sprintf(str, "X %s", spower);
				// move 
				glRasterPos3d(m_vvPoints[1].x, m_vvPoints[1].y, m_vvPoints[1].z + vshift ); 
				// set up for a string-drawing display List call 
				// Display a string 
				glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
				// Draw the characters in a string 
				#if USE_STRING_IN_THE_CELL
					glCallLists(strlen(this->sID.c_str()), GL_UNSIGNED_BYTE, this->sID.c_str()); 
				#else
					glCallLists(strlen(this->sID), GL_UNSIGNED_BYTE, this->sID); 
				#endif
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				glListBase(0);
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/
				for (UINT i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
				{
					if(m_vvPoints[i0].bVisible
						&& m_vvPoints[i1].bVisible)
					{
					Line3(
						m_vvPoints[i1].x, 
						m_vvPoints[i1].y, 
						m_vvPoints[i1].z,
						m_vvPoints[i0].x, 
						m_vvPoints[i0].y,	
						m_vvPoints[i0].z);
					}
				}
				/*
				if (GetPointsNumber() > 1)
				{
					//int n = GetPointsNumber() - 1;
					if(m_vdPoints[1].z != m_vdPoints[0].z)
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку забоя
						char str[16];
						sprintf(str, "%d", (int)(m_vdPoints[1].z - m_vdPoints[0].z));
						// move 
						glRasterPos3d(m_vvPoints[0].x, m_vvPoints[0].y, m_vvPoints[0].z - vshift ); 
						// set up for a string-drawing display List call 
						// Display a string 
						glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
						// Draw the characters in a string 
						glCallLists(strlen(str), GL_UNSIGNED_BYTE, str); 
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						glListBase(0);
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
				}*/
			}
		}
		else
		{
			/*if (GetPointsNumber() > 1 && m_vvPoints[1].bVisible)
			{
				// label color
				COLORREF color = RGB(0,0,255);
				::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//====== Наносим цифровую метку устья
				// sprintf(str, "X %s", spower);
				// move 
				glRasterPos3d(m_vvPoints[1].x, m_vvPoints[1].y, m_vvPoints[1].z + vshift ); 
				// set up for a string-drawing display List call 
				// Display a string 
				glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
				// Draw the characters in a string 
				#if USE_STRING_IN_THE_CELL
					glCallLists(strlen(this->sID.c_str()), GL_UNSIGNED_BYTE, this->sID.c_str()); 
				#else
					glCallLists(strlen(this->sID), GL_UNSIGNED_BYTE, this->sID); 
				#endif
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			}*/
			UINT i1, i2, i_last_visible = -1;
			i1 = 1;//first posible point
			// on enter in the cycle 
			// check if first point is vivible
			while(!this->m_vdPoints[i1].bVisible && i1 + 1 < this->GetPointsNumber())
			{
				i1++;
			}
			if (this->m_vdPoints[i1].bVisible)
			{
				i_last_visible = i1;
				i2 = i1 + 1; 
				while (i2 < this->GetPointsNumber())
				{
					// test if the second point is visible
					while(!this->m_vdPoints[i2].bVisible && i2 + 1 < this->GetPointsNumber())
					{
						i2++;
					}
					if (this->m_vdPoints[i2].bVisible)
					{
						i_last_visible = i2;
						if(m_vvPoints[i1].bVisible && m_vvPoints[i2].bVisible)
						{
							COLORREF color = this->m_vColor[i2];
							::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
							
							glLineWidth(2.0);
							Line3(
								m_vvPoints[i1].x, 
								m_vvPoints[i1].y, 
								m_vvPoints[i1].z,
								m_vvPoints[i2].x, 
								m_vvPoints[i2].y,	
								m_vvPoints[i2].z);

							UINT i_sphere = i2;

							if (i_sphere == Well_3D::s_sloj_number_to_save
								|| Well_3D::s_show_all_sloi)// или если показываем все слои
							{
								//отметим слой для сохранения в виде шариков

								COLORREF sphereColor = this->m_vColor[i_sphere];
							
								glColor3ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor)); 

								GLUquadricObj* pSphere = gluNewQuadric();
								gluQuadricDrawStyle(pSphere, GLU_FILL);
								glPushMatrix();//перейдём к новым координатам, сохранив старые
								
								glTranslated(
									m_vvPoints[i_sphere].x, 
									m_vvPoints[i_sphere].y, 
									m_vvPoints[i_sphere].z
									);

								gluSphere(pSphere, 
									m_pSurfDoc->m_sphere_radius, 
									m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
									m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
									) ;//рисуем сферу 
								glPopMatrix(); //возвращаемся к старым координатам 
								gluDeleteQuadric(pSphere);							
							}

							if (Well_3D::s_use_sloj_names)
							{
								int i_sloj = i2;
								printf("this->m_vstrSloiNames.size() = %d i_sloj = %d\n", this->m_vstrSloiNames.size(), i_sloj);
								if (i_sloj > 0 && i_sloj < this->m_vstrSloiNames.size())
								{
									// label color
									COLORREF color = RGB(0,0,255);
									::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//====== Наносим цифровую метку устья
									// sprintf(str, "X %s", spower);
									// move 
									glRasterPos3d(m_vvPoints[i2].x, m_vvPoints[i2].y, m_vvPoints[i2].z ); 
									// set up for a string-drawing display List call 
									// Display a string 
									glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
									// Draw the characters in a string 
									glCallLists(strlen(this->m_vstrSloiNames[i_sloj].c_str()), 
										GL_UNSIGNED_BYTE, this->m_vstrSloiNames[i_sloj].c_str()); 
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								}
							}
						}
					}
					i1 = i2; i2 = i1 + 1;
				}
				if(i_last_visible > 0)
				{
					if(this->m_vdPoints[0].bVisible && this->m_vdPoints[i_last_visible].bVisible)
					{
						if(this->m_vvPoints[0].bVisible && this->m_vvPoints[i_last_visible].bVisible)
						{
							COLORREF color;
							if (i_last_visible+1 == this->GetPointsNumber())
								color = this->m_vColor[0];
							else
								color = this->m_vColor[i_last_visible+1];

							::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
							glLineWidth(2.0);
							Line3(
								m_vvPoints[i_last_visible].x, 
								m_vvPoints[i_last_visible].y, 
								m_vvPoints[i_last_visible].z,
								m_vvPoints[0].x, 
								m_vvPoints[0].y,	
								m_vvPoints[0].z);
						}
					}
				}
			}			
		}
	}
#else
	float width = wdli ? wdli->draw_width : 2.0;
	
//printf("Well_3D::DrawGDIplus_Primitive() well = %s\n", this->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	if (GetPointsNumber() < 2) return;

	Graphics graphics(v->GetHDC());
	v->PreConvertingFromWorldToScreen();
	
	fGL r = v->lines_points_radius;
	if (m_pSurfDoc)
	{		
		double vshift = 0.025;

		if (m_type == 1)
		{
			if (GetPointsNumber() > 0 && m_vvPoints[0].bVisible)
			{
				//Convert3D_To_2D
				//on->Projection(m_vdPoints[1], profile, dist_to_plane);//ustje altitude
				//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);				
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//====== Наносим цифровую метку устья
				//SolidBrush  brush(Color(255, 0, 0, 255));
				//FontFamily  fontFamily(L"Times New Roman");
				//Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

				//const size_t wlen = 2 + 2 * strlen(this->sID.c_str());
				//WCHAR * wb = new WCHAR[wlen];
				//MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->sID.c_str(), -1, wb, wlen );
				//graphics.DrawString(wb, -1, &font, PointF(x1, y1-20.0f), &brush);
				//delete wb;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

				for (UINT i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
				{
					if(m_vvPoints[i0].bVisible
						&& m_vvPoints[i1].bVisible)
					{
						COLORREF color = 0;
						Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
						Pen      pen(gdi_color);							
						pen.SetWidth(width);	

						//Convert3D_To_2D
						on->Projection(m_vdPoints[i1], profile, dist_to_plane);
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

						//Convert3D_To_2D
						on->Projection(m_vdPoints[i0], profile, dist_to_plane);
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

						graphics.DrawLine(&pen, x1, y1, x2, y2);					
					}
				}
				if (GetPointsNumber() > 1)
				{
					//int n = GetPointsNumber() - 1;
					if(m_vdPoints[1].z != m_vdPoints[0].z)
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку забоя
						wchar_t wstr[16];
						wsprintfW(wstr, L"%d\0", (int)(m_vdPoints[1].z - m_vdPoints[0].z));
						//Convert3D_To_2D
						on->Projection(m_vdPoints[0], profile, dist_to_plane);
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);				
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 12, FontStyleRegular, UnitPixel);

						graphics.DrawString(wstr, -1, &font, PointF(x1, y1), &brush);
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
				}
			}
		}
		else
		{

			UINT i1, i2, i_last_visible = -1;
			i1 = 1;//first posible point
			// on enter in the cycle 
			// check if first point is vivible
			while(!this->m_vdPoints[i1].bVisible && i1 + 1 < this->GetPointsNumber())
			{
				i1++;
			}
			if (this->m_vdPoints[i1].bVisible)
			{
				i_last_visible = i1;
				i2 = i1 + 1; 
				while (i2 < this->GetPointsNumber())
				{
					// test if the second point is visible
					while(!this->m_vdPoints[i2].bVisible && i2 + 1 < this->GetPointsNumber())
					{
						i2++;
					}
					if (this->m_vdPoints[i2].bVisible)
					{
						i_last_visible = i2;
						if(m_vvPoints[i1].bVisible && m_vvPoints[i2].bVisible)
						{
							COLORREF color = this->m_vColor[i2];

							//Convert3D_To_2D
							on->Projection(m_vdPoints[i1], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

							//Convert3D_To_2D
							on->Projection(m_vdPoints[i2], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

							Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
							Pen   pen(gdi_color);
								
							if (!wdli)
							{
								pen.SetWidth(width);
								graphics.DrawLine(&pen, x1, y1, x2, y2);
							}
							else
							{
								Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
								Pen   pen_border(border_color);
								switch(wdli->m_draw_mode_2d)
								{
								case wells_draw_list_item::left:
									{
										pen.SetWidth(0.5*width);	
										graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
										if(wdli->draw2d_border)
											graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	

									}
									break;
								case wells_draw_list_item::draw_mode_2d::right:
									{
										pen.SetWidth(0.5*width);	
										graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
										if(wdli->draw2d_border)
											graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
									}
									break;
								case wells_draw_list_item::draw_mode_2d::both:
									{
										pen.SetWidth(width);	
										graphics.DrawLine(&pen, x1, y1, x2, y2);	
										if(wdli->draw2d_border)
										{
											graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
											graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
										}
									}
									break;
								}

							}



							UINT i_sphere = i2;

							if (i_sphere == Well_3D::s_sloj_number_to_save
								|| Well_3D::s_show_all_sloi)// или если показываем все слои
							{
								//отметим слой для сохранения в виде шариков

								COLORREF sphereColor = this->m_vColor[i_sphere];
								Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
								Pen      sphere_pen(gdi_color);
							

								//Convert3D_To_2D
								on->Projection(m_vdPoints[i_sphere], profile, dist_to_plane);
								v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
								FillCircle(&graphics, x1, y1, r, sphere_color);							
								DrawCircle(&graphics, x1, y1, r, Color(255, 0,0,0));							
							}

							if (Well_3D::s_use_sloj_names)
							{
								int i_sloj = i2;
								//printf("this->m_vstrSloiNames.size() = %d i_sloj = %d\n", this->m_vstrSloiNames.size(), i_sloj);
								if (i_sloj > 0 && i_sloj < this->m_vstrSloiNames.size())
								{									
									//Convert3D_To_2D
									on->Projection(m_vdPoints[i2], profile, dist_to_plane);
									v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
									if(dist_to_plane != 0.0) return;				
									
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//====== Наносим цифровую метку устья
									SolidBrush  brush(Color(255, 0, 0, 255));
									FontFamily  fontFamily(L"Times New Roman");
									Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

									const size_t wlen = 2 + 2 * strlen(this->m_vstrSloiNames[i_sloj].c_str());
									WCHAR * wb = new WCHAR[wlen];
									MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->m_vstrSloiNames[i_sloj].c_str(), -1, wb, wlen );
									graphics.DrawString(wb, -1, &font, PointF(x1, y1), &brush);
									delete wb;
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								}
							}
						}
					}
					i1 = i2; i2 = i1 + 1;
				}
#if 0
				if(i_last_visible > 0)
				{
					if(this->m_vdPoints[0].bVisible && this->m_vdPoints[i_last_visible].bVisible)
					{
						if(this->m_vvPoints[0].bVisible && this->m_vvPoints[i_last_visible].bVisible)
						{
							COLORREF color;
							if (i_last_visible+1 == this->GetPointsNumber())
								color = this->m_vColor[0];
							else
								color = this->m_vColor[i_last_visible+1];

							Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
							Pen      pen(gdi_color);							
							pen.SetWidth(Well_3D::primitive_width);	

							//Convert3D_To_2D
							on->Projection(m_vdPoints[i_last_visible], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

							//Convert3D_To_2D
							on->Projection(m_vdPoints[0], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

							graphics.DrawLine(&pen, x1, y1, x2, y2);						}
					}
				}
#endif
			}			
		}
	}
#endif
}
void Well_3D::DrawGDIplus_Primitive(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, wells_draw_list_item * wdli)
{
	float width = wdli ? wdli->draw_width : 2.0;
	
//printf("Well_3D::DrawGDIplus_Primitive() well = %s\n", this->GetIDString());
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	if (GetPointsNumber() < 2) return;

	v->PreConvertingFromWorldToScreen();
	
	fGL r = v->lines_points_radius;
	if (m_pSurfDoc)
	{		
		double vshift = 0.025;

		if (m_type == 1)
		{
			if (GetPointsNumber() > 0 && m_vvPoints[0].bVisible)
			{
				//Convert3D_To_2D
				//on->Projection(m_vdPoints[1], profile, dist_to_plane);
				//v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);				
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//====== Наносим цифровую метку устья
				//SolidBrush  brush(Color(255, 0, 0, 255));
				//FontFamily  fontFamily(L"Times New Roman");
				//Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

				//const size_t wlen = 2 + 2 * strlen(this->sID.c_str());
				//WCHAR * wb = new WCHAR[wlen];
				//MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->sID.c_str(), -1, wb, wlen );
				//graphics.DrawString(wb, -1, &font, PointF(x1, y1-20.0f), &brush);
				//delete wb;
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
				//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

				for (UINT i0 = 0, i1 = 1 ; i1 < GetPointsNumber(); i0++, i1++)
				{
					if(m_vvPoints[i0].bVisible
						&& m_vvPoints[i1].bVisible)
					{
						COLORREF color = 0;
						Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
						Pen      pen(gdi_color);							
						pen.SetWidth(width);	

						//Convert3D_To_2D
						on->Projection(m_vdPoints[i1], profile, dist_to_plane);
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

						//Convert3D_To_2D
						on->Projection(m_vdPoints[i0], profile, dist_to_plane);
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

						graphics.DrawLine(&pen, x1, y1, x2, y2);					
					}
				}
				if (GetPointsNumber() > 1)
				{
					//int n = GetPointsNumber() - 1;
					if(m_vdPoints[1].z != m_vdPoints[0].z)
					{
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку забоя
						wchar_t wstr[16];
						wsprintfW(wstr, L"%d\0", (int)(m_vdPoints[1].z - m_vdPoints[0].z));
						//Convert3D_To_2D
						on->Projection(m_vdPoints[0], profile, dist_to_plane);//zaboj altitude
						v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);				
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//====== Наносим цифровую метку устья
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 12, FontStyleRegular, UnitPixel);

						graphics.DrawString(wstr, -1, &font, PointF(x1, y1), &brush);
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
					}
				}
			}
		}
		else
		{

			UINT i1, i2, i_last_visible = -1;
			i1 = 1;//first posible point
			// on enter in the cycle 
			// check if first point is vivible
			while(!this->m_vdPoints[i1].bVisible && i1 + 1 < this->GetPointsNumber())
			{
				i1++;
			}
			if (this->m_vdPoints[i1].bVisible)
			{
				i_last_visible = i1;
				i2 = i1 + 1; 
				while (i2 < this->GetPointsNumber())
				{
					// test if the second point is visible
					while(!this->m_vdPoints[i2].bVisible && i2 + 1 < this->GetPointsNumber())
					{
						i2++;
					}
					if (this->m_vdPoints[i2].bVisible)
					{
						i_last_visible = i2;
						if(m_vvPoints[i1].bVisible && m_vvPoints[i2].bVisible)
						{
							COLORREF color = this->m_vColor[i2];

							//Convert3D_To_2D
							on->Projection(m_vdPoints[i1], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

							//Convert3D_To_2D
							on->Projection(m_vdPoints[i2], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

							Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
							Pen   pen(gdi_color);
								
							if (!wdli)
							{
								pen.SetWidth(width);
								graphics.DrawLine(&pen, x1, y1, x2, y2);
							}
							else
							{
								Color border_color(255, GetRValue(wdli->border_color),GetGValue(wdli->border_color),GetBValue(wdli->border_color));
								Pen   pen_border(border_color);
								switch(wdli->m_draw_mode_2d)
								{
								case wells_draw_list_item::left:
									{
										pen.SetWidth(0.5*width);	
										graphics.DrawLine(&pen, x1-0.25*width, y1, x2-0.25*width, y2);	
										if(wdli->draw2d_border)
											graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	

									}
									break;
								case wells_draw_list_item::draw_mode_2d::right:
									{
										pen.SetWidth(0.5*width);	
										graphics.DrawLine(&pen, x1+0.25*width, y1, x2+0.25*width, y2);	
										if(wdli->draw2d_border)
											graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
									}
									break;
								case wells_draw_list_item::draw_mode_2d::both:
									{
										pen.SetWidth(width);	
										graphics.DrawLine(&pen, x1, y1, x2, y2);	
										if(wdli->draw2d_border)
										{
											graphics.DrawLine(&pen_border, x1-0.5*width, y1, x2-0.5*width, y2);	
											graphics.DrawLine(&pen_border, x1+0.5*width, y1, x2+0.5*width, y2);	
										}
									}
									break;
								}

							}



							UINT i_sphere = i2;

							if (i_sphere == Well_3D::s_sloj_number_to_save
								|| Well_3D::s_show_all_sloi)// или если показываем все слои
							{
								//отметим слой для сохранения в виде шариков

								COLORREF sphereColor = this->m_vColor[i_sphere];
								Color sphere_color(255, GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor));
								Pen      sphere_pen(gdi_color);
							

								//Convert3D_To_2D
								on->Projection(m_vdPoints[i_sphere], profile, dist_to_plane);
								v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
								FillCircle(&graphics, x1, y1, r, sphere_color);							
								DrawCircle(&graphics, x1, y1, r, Color(255, 0,0,0));							
							}

							if (Well_3D::s_use_sloj_names)
							{
								int i_sloj = i2;
								//printf("this->m_vstrSloiNames.size() = %d i_sloj = %d\n", this->m_vstrSloiNames.size(), i_sloj);
								if (i_sloj > 0 && i_sloj < this->m_vstrSloiNames.size())
								{									
									//Convert3D_To_2D
									on->Projection(m_vdPoints[i2], profile, dist_to_plane);
									v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
									if(dist_to_plane != 0.0) return;				
									
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//====== Наносим цифровую метку устья
									SolidBrush  brush(Color(255, 0, 0, 255));
									FontFamily  fontFamily(L"Times New Roman");
									Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

									const size_t wlen = 2 + 2 * strlen(this->m_vstrSloiNames[i_sloj].c_str());
									WCHAR * wb = new WCHAR[wlen];
									MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->m_vstrSloiNames[i_sloj].c_str(), -1, wb, wlen );
									graphics.DrawString(wb, -1, &font, PointF(x1, y1), &brush);
									delete wb;
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
									//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
								}
							}
						}
					}
					i1 = i2; i2 = i1 + 1;
				}
#if 0
				if(i_last_visible > 0)
				{
					if(this->m_vdPoints[0].bVisible && this->m_vdPoints[i_last_visible].bVisible)
					{
						if(this->m_vvPoints[0].bVisible && this->m_vvPoints[i_last_visible].bVisible)
						{
							COLORREF color;
							if (i_last_visible+1 == this->GetPointsNumber())
								color = this->m_vColor[0];
							else
								color = this->m_vColor[i_last_visible+1];

							Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
							Pen      pen(gdi_color);							
							pen.SetWidth(Well_3D::primitive_width);	

							//Convert3D_To_2D
							on->Projection(m_vdPoints[i_last_visible], profile, dist_to_plane);
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

							//Convert3D_To_2D
							on->Projection(m_vdPoints[0], profile, dist_to_plane);//zaboj altitude
							v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

							graphics.DrawLine(&pen, x1, y1, x2, y2);						}
					}
				}
#endif
			}			
		}
	}
}

void Well_3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{	
	double dist_to_plane;
	CPoint2 profile;

	fGL x1; fGL y1;
	fGL x2; fGL y2;

	v->PreConvertingFromWorldToScreen();

	//Convert3D_To_2D
	on->Projection(m_vdPoints[1], profile, dist_to_plane);//ustje altitude
	if(dist_to_plane != 0.0) return;


	if (GetPointsNumber() > 1 && m_vvPoints[1].bVisible)
	{
		//Convert3D_To_2D
		on->Projection(m_vdPoints[1], profile, dist_to_plane);//ustje altitude
		v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
		
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//====== Наносим цифровую метку устья
		SolidBrush  brush(Color(255, 0, 0, 255));
		FontFamily  fontFamily(L"Times New Roman");
		Font        font(&fontFamily, 12, FontStyleRegular, UnitPixel);

		const int wlen = 2 + 2 * (int)strlen(this->sID.c_str());
		WCHAR * wb = new WCHAR[wlen];
		MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->sID.c_str(), -1, wb, wlen );
		graphics.DrawString(wb, -1, &font, PointF(x1, y1-20.0f), &brush);
		delete wb;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}

#if 0
	if (this->m_pSurfDoc && this->m_pSurfDoc->need_to_set_wel_element_ige_keys)
	{
		for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
			it_c != this->well_colomns.end(); it_c++)
		{
			if ( (*it_c).GetWellElementType() == WellElement::type::IGE_podoshva)
			{
				(*it_c).SetWellElementsIGEkeys();
			}
		}
	}
#endif

	for(vector<wells_draw_list_item *>::reverse_iterator it = Well_3D::wells_draw_list.rbegin();it != Well_3D::wells_draw_list.rend(); it++)
	{
		if ( (*it) )
		{
			WellColomn * wc = this->FindWellColomn((*it)->id);
			if (wc)	wc->DrawGDIplus(select_buffer, graphics, v, on, this);
		}
	}


	//if (Well_3D::draw_hydro)		DrawGDIplus_Hydro(v, on);
	//if (Well_3D::draw_primitive)	DrawGDIplus_Primitive(v, on);
	//if (Well_3D::draw_issand)		DrawGDIplus_IsSand(v, on);
	//if (Well_3D::draw_ige)		DrawGDIplus_IGE(v, on);

	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_index > -1 && 
				this->m_karotazhy.GetCurrentMsg().m_index < Well_3D::karotazh_list.size() &&
				Well_3D::karotazh_list[this->m_karotazhy.GetCurrentMsg().m_index].checked)
				this->m_karotazhy.GetCurrentMsg().DrawGDIplus(select_buffer, graphics, v, on);
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}

	if(Well_3D::draw2d_center)
	{
		//Convert3D_To_2D
		on->Projection(m_vdPoints[1], profile, dist_to_plane);//ustje altitude
		v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);

		//Convert3D_To_2D
		on->Projection(m_vdPoints[0], profile, dist_to_plane);
		v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);

		Color center_col(255, GetRValue(Well_3D::center_color),GetGValue(Well_3D::center_color),GetBValue(Well_3D::center_color));
		Pen   pen_center(center_col);
		pen_center.SetDashStyle(Well_3D::dashStyle);
		pen_center.SetDashOffset(Well_3D::dashOffset);

		graphics.DrawLine(&pen_center, x1, y1, x2, y2); 
	}
}
void Well_3D::UpdateWellColomnsByWellsDraw()
{
	//m_wdli_primitive;
	size_t r = 0;
	for (vector<wells_draw_list_item *>::iterator it = Well_3D::wells_draw_list.begin();
		it != Well_3D::wells_draw_list.end(); it++, r++)
	{
		if (*it)
		{
			WellColomn * wc = this->FindWellColomn((*it)->id);
			if (wc) wc->m_wdli = (*it);
		}
	}
}

bool Well_3D::IsWellElement(const WellElement * p1)
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ((*it_c).IsWellElement(p1))
		{
			return true;
		}
	}
	return false;
}

void Well_3D::ReinitWellColomnsPointers()
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		(*it_c).InitWell(this);

	}
}

WellColomn * Well_3D::FindWellColomn(int wdli_id)
{
	for (vector<WellColomn>::iterator it_c = this->well_colomns.begin();
		it_c != this->well_colomns.end(); it_c++)
	{
		if ((*it_c).m_wdli_id == wdli_id)
		{
			return &(*it_c);
		}
	}
	return NULL;
}


WellColomn * Well_3D::FindWellColomn(WellElement::type t)
{
	for (vector<WellColomn>::iterator it = this->well_colomns.begin();
		it != this->well_colomns.end(); it++)
	{
		if (t == (*it).GetType())
		{
			return &(*it);
		}
	}
	return NULL;
}
void Well_3D::ReDraw_Primitive(wells_draw_list_item * wdli)
{
	if (m_nglListNumber_Primitive > 0)
	{
		::glDeleteLists(m_nglListNumber_Primitive,1);
		::glNewList(m_nglListNumber_Primitive, GL_COMPILE);
	}
	else
		m_nglListNumber_Primitive = DrawListArray::glNewList();

	this->Drawing_Primitive(wdli);
			
	glEndList();	
}
void Well_3D::Draw_Primitive(wells_draw_list_item * wdli)
{
	m_nglListNumber_Primitive = DrawListArray::glNewList();
	this->Drawing_Primitive(wdli);
	glEndList();	
}

void Well_3D::Draw()
{
	this->Primitive3D <CPoint3>::Draw();

	for(vector<wells_draw_list_item *>::reverse_iterator it = Well_3D::wells_draw_list.rbegin();it != Well_3D::wells_draw_list.rend(); it++)
	{
		if ( (*it) )
		{
			WellColomn * wc = this->FindWellColomn((*it)->id);
			if (wc)	wc->Draw(this);
		}
	}
	
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			this->m_karotazhy.GetCurrentMsg().Primitive3D <CPoint4>::Draw();
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}

void Well_3D::ReDraw(void)
{
	this->Primitive3D <CPoint3>::ReDraw();

	for(vector<wells_draw_list_item *>::reverse_iterator it = Well_3D::wells_draw_list.rbegin();it != Well_3D::wells_draw_list.rend(); it++)
	{
		if ( (*it) )
		{
			WellColomn * wc = this->FindWellColomn((*it)->id);
			if (wc)	wc->ReDraw(this);
		}
	}

	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_nglListNumber > 0)
			{
				::glDeleteLists(this->m_karotazhy.GetCurrentMsg().m_nglListNumber,1);
				::glNewList(this->m_karotazhy.GetCurrentMsg().m_nglListNumber, GL_COMPILE);
			}
			else
				this->m_karotazhy.GetCurrentMsg().m_nglListNumber = DrawListArray::glNewList();
			
			this->m_karotazhy.GetCurrentMsg().Drawing();
			glEndList();
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}

void Well_3D::OnPaint()
{
	this->Object::OnPaint();
	
	for(vector<wells_draw_list_item *>::reverse_iterator it = Well_3D::wells_draw_list.rbegin();it != Well_3D::wells_draw_list.rend(); it++)
	{
		if ( (*it) )
		{
			WellColomn * wc = this->FindWellColomn((*it)->id);
			if (wc && wc->m_wdli && wc->m_wdli->check_draw)
				wc->OnPaint(this);
		}
	}
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_index > -1 && 
				this->m_karotazhy.GetCurrentMsg().m_index < Well_3D::karotazh_list.size() &&
				Well_3D::karotazh_list[this->m_karotazhy.GetCurrentMsg().m_index].checked)
				this->m_karotazhy.GetCurrentMsg().Object::OnPaint();
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}

void Well_3D::OnPaintPrimitive()
{
	if (m_nglListNumber_Primitive > 0)
	{
		::glCallList(m_nglListNumber_Primitive);
	}
}

void Well_3D::GetKarotazhCube(int index, double & minx, double & miny, double & minz, double & maxx, double & maxy, double & maxz)
{

	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_index == index)
				this->m_karotazhy.GetCurrentMsg().GetKarotazhCube(minx, miny, minz, maxx, maxy, maxz);
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}

void Well_3D::PutKarotazhSlicesPoint(Karotazh::linterp_method int_meth, int index,vector<karotazh_slice> & vks, karotazh_extrapolate_down & ked)
{
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_index == index)
				this->m_karotazhy.GetCurrentMsg().PutKarotazhSlicesPoint(int_meth, vks, ked);
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}
void Well_3D::PutKarotazhPoints(int index, vector<double> & vxk, vector<double> & vyk, vector<double> & vzk, vector<double> & vvk)
{
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_index == index)
				this->m_karotazhy.GetCurrentMsg().PutKarotazhPoints(vxk, vyk, vzk, vvk);
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}
void Well_3D::KarotazhProjection(int index, Cube4D & cube)
{
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (this->m_karotazhy.GetCurrentMsg().m_index == index)
				cube.Projection(this->m_karotazhy.GetCurrentMsg());
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
}



void Well_3D::Drawing()
{
	if (m_pSurfDoc)
	{
		double vshift = 0.025;
		if (GetPointsNumber() > 1 && m_vvPoints[1].bVisible)
		{
			// label color
			COLORREF color = RGB(0,0,255);
			::glColor3ub(GetRValue(color),GetGValue(color),GetBValue(color));
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//====== Наносим цифровую метку устья
			// sprintf(str, "X %s", spower);
			// move 
			glRasterPos3d(m_vvPoints[1].x, m_vvPoints[1].y, m_vvPoints[1].z + vshift ); 
			// set up for a string-drawing display List call 
			// Display a string 
			glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
			// Draw the characters in a string 
			#if USE_STRING_IN_THE_CELL
				glCallLists(strlen(this->sID.c_str()), GL_UNSIGNED_BYTE, this->sID.c_str()); 
			#else
				glCallLists(strlen(this->sID), GL_UNSIGNED_BYTE, this->sID); 
			#endif
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		}
	}
}


bool Well_3D::SaveAsDat(FILE * stream)
{
	if (stream)
	{
		if (Well_3D::s_sloj_number_to_save == -1)
		{
			PRIMITIVE_POINTS_PTR(CPoint3) ptd	= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
			for(int i = 0; i < this->GetPointsNumber(); i++)
			{
				if (ptd[i].bVisible)
					fprintf(stream, "%lf, %lf, %lf\n", 
						ptd[i].x, 
						ptd[i].y, 
						ptd[i].z);
			}
		}
		else
		{
			if (Well_3D::s_sloj_number_to_save >= 0 || Well_3D::s_sloj_number_to_save < this->GetPointsNumber())
			{
				PRIMITIVE_POINTS_PTR(CPoint3) ptd	= this->m_vdPoints PRIMITIVE_POINTS_PTR_BEGIN;
				int i = Well_3D::s_sloj_number_to_save;
				{
					if (ptd[i].bVisible)
						fprintf(stream, "%lf, %lf, %lf\n", 
							ptd[i].x, 
							ptd[i].y, 
							ptd[i].z);
				}
			}
		}
		return true;
	}
	return false;
}
void Well_3D::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_WELL_SAVEZONDINPUT, "&Save Zond Input" );
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
#endif /*!VIEW_ONLY_VERSION*/
}
int Well_3D::WriteZondInput_FileLine(FILE * out, char* szBuff, int type_line)
{
	static int i_zond_point = 0;

	//printf("ParseZondFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);
	//printf(szBuff);
	switch(type_line)
	{
	case 1:
		{
			//name of object
			sprintf(szBuff, "%s\n", this->m_pSurfDoc ? this->m_pSurfDoc->m_laboratory.object_name.c_str() : "");
			CharToOem(szBuff,szBuff);
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 2:
		{
			//  archive number
			sprintf(szBuff, "%d\n", this->m_pSurfDoc ? this->m_pSurfDoc->m_laboratory.id_obj : 0);
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 3:
		{
			//12 1 1024 1016 1023 1008 1001 1002 1003 1004 1005 1007 1015 1020
			int delim = ' ';
			// разделитель пробел
			// количество точек зондирования (<= 100)
			// признак печати графика 1- печатать график, 2 - не печатать
			// номера точек зондирования (целые числа) занимают несколько строк в зависимости от их количества
			sprintf(szBuff, "1 1 %d\n", this->m_id_kt);
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 4:
		{
			printf(szBuff);
			//  договор (8 символов)
			// тип установки (8 символов)
			// (допускается 832-5 832-7 979 59)
			// К1 постоянная динамометра для установок С-979, СП-59 или
			// тарировочный коэффициент для РСК для установки С-832
			// К2 постоянная маноометра для установок С-979, СП-59 или
			// тарировочный коэффициент к РСб для установки С-832
			// договор и тип установки набиваются без разделителей
			// После К1 записывается запятая, после К2 - запятая
			// max размер К1 и К2 F5.2, запятая после К1 и К2 ставится, если 
			// число занимает менее 5 знаков

			char tmp[1024];
			sprintf(tmp, "%s", this->m_pSurfDoc ? this->m_pSurfDoc->m_laboratory.contract.c_str() : "");
			tmp[8] = '\0';
			fprintf(out, "%s", tmp);
			for (size_t i = strlen(tmp); i < 8; i++)
				fprintf(out, " ", tmp);

			
			printf("dogovor = \"%s\"\n", tmp);

			switch (this->m_stat_zond.data2.id_ust)
			{
			case 1:
				sprintf(tmp, "832-5   ");
				break;
			case 2:
				sprintf(tmp, "979     ");
				break;
			case 3:
				sprintf(tmp, "979     ");
				break;
			case 4:
				sprintf(tmp, "59      ");
				break;
			case 5:
				sprintf(tmp, "832-5   ");
				break;
			}

			tmp[8] = '\0';
			fprintf(out, "%s", tmp);

			/*printf("ustanovka = \"%s\"\n", tmp);

			if (strncmp(tmp, "832-7", 5) == 0)
				return 2;
			if (strncmp(tmp, "832-5", 5) == 0)
				printf ("pika-5!!!\n");*/

			if (this->m_stat_zond.data2.typ_zond == 1)
				sprintf(tmp, "%0.3f,%0.3f,\0", this->m_stat_zond.data2.Kg, 1.0*1000*this->m_stat_zond.data2.Kf);
			else
				sprintf(tmp, "%0.3f,%0.3f,\0", this->m_stat_zond.data2.Kg, 1.0*this->m_stat_zond.data2.Kf);
			//sprintf(tmp, "1.0,10.0,\0", this->m_stat_zond.data2.Kg, this->m_stat_zond.data2.Kf);
			fprintf(out, "%s\n", tmp);
	

			return 1;
		}
		break;
	case 5:
		{
			// разделитель пробел
			// К3 "место нуля" для каждой точки зондирования для установок 
			// С-979, СП-59 или для установок С-832 : значение 5 или 7
			sprintf(szBuff, "0.0\n");
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 6:
		{
			// разделитель пробел
			// К4 ростверк в метрах для каждой точки зондирования
			// (должен быть кратен 0.2м)
			CPoint3 ustje;
			if (this->GetUstje(ustje))
			{
				double glubina_rostverka = ustje.z - this->m_palja.data2.pz;
				sprintf(szBuff, "%0.1f\n", glubina_rostverka);
			}
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 7:
		{
			// разделитель пробел
			// начальная глубина для каждой точки зондирования
			// (должна быть кратна 0.2)

			if (this->m_stat_zond.data1.size()>1)
			{
				sprintf(szBuff, "%0.1f\n", (*this->m_stat_zond.data1.begin()).h - (*(this->m_stat_zond.data1.begin()+1)).dh);
			}
			fprintf(out, "%s", szBuff);		

			return 1;
		}
		break;
	case 8:
		{
			// разделитель пробел
			// только для С-832 (пика 7)
			// К5 "место нуля" при расчёте РСК для каждой точки 

			//  589.2498003. 43131-01 90 01 стр. 227
			sprintf(szBuff, "%0.1f\n", this->m_stat_zond.data2.Bg);
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 9:
		{
			// разделитель пробел
			// только для С-832 (пика 7)
			// К6 "место нуля" при расчёте РСБ для каждой точки 
			sprintf(szBuff, "%0.1f\n", this->m_stat_zond.data2.Bf);
			fprintf(out, "%s", szBuff);		
			return 1;
		}
		break;
	case 10:
		{
			printf(szBuff);
			// последующие строки для каждой точки разделитель пробел
			// показания динамометра и манометра для каждого шага (шаг постоянный 0,2м) 
			// при этом показание динамометра должно быть целым числом
			// Это можно делать с помощью коэффициента К1, а манометра с точкой
			// глубина не вводится, предполагается, что показания начинаются с глубины 0,2 м
			// с шагом 0,2
			// но не более чем до 25м (40м)
			//  признак конца данных по скважине два нуля

			int i = 0;
			bool nl;
			for (vector<StatZondData1>::iterator it = this->m_stat_zond.data1.begin();
				it != this->m_stat_zond.data1.end(); it++)
			{
				i++;
				fprintf(out, "%d %0.2f ", int(10*(*it).q0), (*it).f0/10.0);	
				if (!(i%5))
				{
					fprintf(out, "\n");
					nl = true;
				}
				else
				{
					nl = false;
				}
			}
			if (!nl) fprintf(out, "\n");
			fprintf(out, "0 0.0\n");
			return 1;
		}
		break;
	case 11:
		{
			printf(szBuff);
			// глубины подошв песчаных и пылевато-глиистых грунтов
			// обязательно на первом месте подошва песчаного грунта
			// если его нет, набивается начальная глубина, если начальная глубина 
			// 0 набивать 0. (с точкой)

			long typgr = 1;//sand first
			double h1 = 0.0;

			if (this->m_db_lito.data_filled)
			{
				for (vector<db_lito_data>::iterator it_lit = this->m_db_lito.data1.begin();
					it_lit != this->m_db_lito.data1.end(); it_lit++)
				{
					if (this->m_pSurfDoc)
					{
						for (vector<IGE_Data>::iterator it_ige = this->m_pSurfDoc->m_db_ige.data.begin();
							it_ige != this->m_pSurfDoc->m_db_ige.data.end(); it_ige++)
						{
							if ((*it_ige).ige_filled && (*it_ige).grunt_filled && (*it_ige).ige.id_ige == (*it_lit).id_ige)
							{
								if (typgr != (*it_ige).grunt.typgr)
								{
									fprintf(out, "%0.1f ", (*it_lit).h0);
								}
								h1 = (*it_lit).h1;
							}
						}	
					}
				}
			}
			fprintf(out, "%0.1f ", h1);
			fprintf(out, "0.0\n");

			return 1;
		}
		break;
	default:
		return 3;
	}
	return -1;
}

void Well_3D::SaveAsZondInput()
{
	TCHAR lpstrFile[4098];
	sprintf(lpstrFile, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, "zond input (*)\0*.*\0All files \0*.*\0", nFilterIndex) == S_OK)
	{
		const int n=16384; // length of buffer string line
		char* szBuff; // buffer string line
		if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
		{
			MessageBox(0, "vX - Not enough memory",
				"Well_3D::SaveAsZondInput()", 0);
			return;
		}

		char out_file[4098];
		sprintf(out_file, "%s\0", lpstrFile);
		printf("out_file = \"%s\"\n", out_file);

		FILE * out;
		if ((out = fopen(out_file,"wt")) == NULL)
		{
			printf("!out\n");

			char errstr[2048];
			sprintf(errstr, "Well_3D::SaveAsZondInput()::fopen(%s)", out_file);
			ErrorExit(errstr);
			return;
		}

		bool to_write  = true;

		int type_line = 1;

		bool pika_7 = false;
		bool propusk_8_9_strok = true;
		if (pika_7)
			propusk_8_9_strok = false;

		while (to_write)
		{
			int res = WriteZondInput_FileLine(out, szBuff, type_line);

			type_line++;

			if(propusk_8_9_strok && type_line == 8)
			{
				type_line = 10;
			}

			if(type_line == 12)
			{
				to_write = false;
			}
			printf("type_line = %d\n", type_line);
		}

		if(out) fclose(out);
	}
}

void Well_3D::PrintfProperties(vector<LabData> & labdata)
{
	labdata.push_back(LabData());
	this->PrintfProperties(labdata.back().text);
}
bool linterp(int n, double* vx, double* vy, double x, double &y);

bool linterp_bounded(int n, double* vx, double* vy, double x, double &y)
{
	bool res = linterp(n, vx, vy, x, y);

	if (x < vx[0])
		y = vy[0];

	if (x > vx[n-1])
		y = vy[n-1];

	return res;
}

double GetBeta1_mariupolsky(long typ_zond, long typgr, double qs)
{
	//double qs0 = 100.0;// 100 тс/м^2 = 1 МПа
	double qs0 = 1.0;// 100 тс/м^2 = 1 МПа

	double beta1 = 0.0;

	if (typ_zond == 1)
	{
		beta1 = 0.6 + 1.14 * qs0/qs; // (4.10) стр.62  Зонд I типа

		// а если по нижней границе 95% интервала
		//beta1 = 0.9329 - 0.0479 * qs; //(qs в МПа)
	}
	else if (
		typ_zond == 2 || 
		typ_zond == 3)
	{
		switch (typgr)
		{
		case 1://песчаный
			{
				beta1 = 1.27 - 0.73 * log10(qs/qs0);// (4.15) стр.66
			}
			break;
		case 2://пылевато-глинистый
			{
				beta1 = 1.01 - 0.7 * log10(qs/qs0);// (4.17) стр.67
			}
			break;
		}
//		beta1 = 0.97 - 0.53 * log10(qs/qs0); // (4.19) стр.67
	}
	return beta1;
}
double GetBeta1_mariupolsky(long typgr, double qs)
{
	// Мариупольский стр 67 таб 4.6
	// qs - входящий параметр сопротивление грунта под конусом в МПа
	// коэффициент 
	double beta1 = 0.0;

	switch (typgr)
	{
	case 1:
		{
			// массив сопротивлений грунта под конусом 
			double vqs[] = { 1.0, 2.0, 5.0, 8.0, 10.0, 15.0, 20.0};
			// Зонд I типа
			// Зонд II и III типа
			double vb1[] = {1.27, 1.05, 0.76, 0.61, 0.54, 0.41, 0.32};
			linterp_bounded(7, vqs, vb1, qs, beta1);
		}
		break;
	case 2:
		{
			// массив сопротивлений грунта под конусом 
			double vqs[] = { 1.0, 2.0, 5.0, 8.0, 10.0};
			// Зонд I типа
			// Зонд II и III типа
			double vb1[] = {1.01, 0.80, 0.53, 0.38, 0.31};
			linterp_bounded(5, vqs, vb1, qs, beta1);
		}
		break;
	}
	return beta1;
}




double GetBeta1(double qs, long id_snip)
{
	// qs - входящий параметр сопротивление грунта под конусом в МПа
	// коэффициент 
	double beta1 = 0.0;
#if 0
	//Мариупольский стр 67 табл 4.6
	// массив сопротивлений грунта под конусом 
	double vqs[] = { 1.0, 2.0, 5.0, 8.0, 10.0, 15.0, 20.0};
	// Зонд I типа
	// Зонд II и III типа
	double vb1[] = {0.97, 0.81, 0.60, 0.49, 0.44, 0.33, 0.28};
	linterp_bounded(7, vqs, vb1, qs, beta1);
#else
	// СНиП 2.02.03-85
	// массив сопротивлений грунта под конусом 
	double vqs[] = { 1.0, 2.5, 5.0, 7.5, 10.0, 15.0, 20.0, 30.0};
	// Зонд I типа
	// Зонд II и III типа
	double vb1[] = {0.90, 0.80, 0.65, 0.55, 0.45, 0.35, 0.30, 0.20};
	switch (id_snip)
	{
	case 1:// СНиП 2.02.03-85
		linterp_bounded(8, vqs, vb1, qs, beta1);
		break;
	case 2://СП 50-102-2003
		// По СП 50-102-2003 последний элемент обрезан
		linterp_bounded(7, vqs, vb1, qs, beta1);
		break;
	}
	
#endif
	return beta1;
}



bool FindMeanPCK_ceil_meaning(StatZond & stat_zond, double glubina_ot_ustja, double d, double & mean_pck)
{
	//найти усреднённое рск на участке глубин 
	// от (glubina - d) до (glubina + 4*d)

	// путём усреднения численных значений РСК граничащих с интервалом интервал



	double max_palja_h_ot_ustja = stat_zond.data2.glyb - 4 * d;

	if (glubina_ot_ustja <= max_palja_h_ot_ustja && stat_zond.data1.size())
	{
		double S = 0.0;
		double i = 0.0;

		int flag = 0;

		double glub_up = glubina_ot_ustja - d;
		if (glub_up < stat_zond.data1[0].h)
			return false;

		double glub_dw = glubina_ot_ustja + 4 * d;

		size_t j_up = 0;
		size_t j_dw = 0;

		for (size_t j = 1; j < stat_zond.data1.size(); j++)
		{
			double h_0 = stat_zond.data1[j-1].h;
			double h_1 = stat_zond.data1[j].h;

			if (glub_up >= h_0 && glub_up < h_1)
			{
				j_up = j-1;
			}
			if (glub_dw > h_0 && glub_dw <= h_1)
			{
				j_dw = j;
			}
		}
		for (size_t j = j_up; j <= j_dw; j++)
		{
			i += 1.0;
			S += stat_zond.data1[j].GetPCK();
		}

		mean_pck = S / i;
		return true;
	}
	return false;
}

bool FindMeanPCK_simple_meaning(StatZond & stat_zond, double glubina_ot_ustja, double d, double & mean_pck)
{
	//найти усреднённое рск на участке глубин 
	// от (glubina - d) до (glubina + 4*d)

	// путём простого усреднения численных значений РСК попадающих в интервал

	double max_palja_h_ot_ustja = stat_zond.data2.glyb - 4 * d;

	if (glubina_ot_ustja <= max_palja_h_ot_ustja && stat_zond.data1.size())
	{
		double S = 0.0;
		double i = 0.0;

		int flag = 0;

		double glub_up = glubina_ot_ustja - d;
		if (glub_up < stat_zond.data1[0].h)
			return false;

		double glub_dw = glubina_ot_ustja + 4 * d;

		for (vector<StatZondData1>::iterator it = stat_zond.data1.begin();
			it != stat_zond.data1.end(); it++)
		{		
			double q = (*it).GetPCK();

			double h = (*it).h;

			switch (flag)
			{
			case 0:
				{
                    if (glub_up <= h)
					{
						i += 1.0;
						S += q;

						flag = 1;
					}
				}
				break;
			case 1:
				{
					if (glub_dw > h)
					{
						i += 1.0;
						S += q;
					}
					else
					{
						if (glub_dw == h)
						{
							i += 1.0;
							S += q;
						}
						mean_pck = S / i;

						return true;
					}
				}
				break;
			}
		}
	}
	return false;
}

bool FindMeanPCK_by_integral(StatZond & stat_zond, double glubina_ot_ustja, double d, bool trapec, bool hvosty, double & mean_pck)
{
	//найти усреднённое рск на участке глубин 
	// от (glubina - d) до (glubina + 4*d)

	// путём интегрирования методом трапеций или методом прямоугольников

	double max_palja_h_ot_ustja = stat_zond.data2.glyb - 4 * d;

	if (glubina_ot_ustja <= max_palja_h_ot_ustja && stat_zond.data1.size())
	{
		double S = 0.0;
		double h = 0.0;

		int flag = 0;

		double glub_up = glubina_ot_ustja - d;
		if (glub_up < stat_zond.data1[0].h)
			return false;

		double glub_dw = glubina_ot_ustja + 4 * d;

		for (vector<StatZondData1>::iterator it = stat_zond.data1.begin();
			(it+1) != stat_zond.data1.end(); it++)
		{		
			double q_0 =(*it).GetPCK();
			//double f_0 = stat_zond.data2.Kf * (*it).f0 + stat_zond.data2.Bf;
			
			double q_1 = (*(it+1)).GetPCK();
			//double f_1 = stat_zond.data2.Kf * (*(it+1)).f0 + stat_zond.data2.Bf;

			double h_0 = (*it).h;
			double h_1 = (*(it+1)).h;
			double dh = h_1 - h_0;

			switch (flag)
			{
			case 0:
				{
                    if (glub_up >= h_0 && glub_up <= h_1)
					{
						if (hvosty)
						{
							double mu = (glub_up - h_0) / (h_1 - h_0);
							double q_ = q_0 + mu * (q_1 - q_0);

							h += h_1 - glub_up;
							if (trapec)
								S += 0.5 * (h_1 - glub_up) * (q_ + q_1);
							else
								S += (h_1 - glub_up) * q_1;
						}


						flag = 1;
					}
				}
				break;
			case 1:
				{
					if (glub_dw > h_1)
					{
						h += h_1 - h_0;
						if (trapec)
							S += 0.5 * (h_1 - h_0) * (q_0 + q_1);
						else
							S += (h_1 - h_0) * q_1;
					}
					else
					{
						if (hvosty)
						{
							double mu = (glub_dw - h_0) / (h_1 - h_0);
							double q_ = q_0 + mu * (q_1 - q_0);

							h += glub_dw - h_0;
							if (trapec)
								S += 0.5 * (glub_dw - h_0) * (q_ + q_0);
							else
								S += (glub_dw - h_0) * q_;
						}

						mean_pck = S / h;

						return true;
					}
				}
				break;
			}
		}
	}
	return false;
}
long g_FindMeanPCK_id_method = 2;
bool FindMeanPCK(StatZond & stat_zond, double glubina_ot_ustja, double d, double & mean_pck, long id_method)
{
	switch (id_method)
	{
	case 1:
		return FindMeanPCK_simple_meaning(stat_zond,glubina_ot_ustja, d, mean_pck);
	case 2:
		return FindMeanPCK_ceil_meaning(stat_zond,glubina_ot_ustja, d, mean_pck);
	case 3:
		return FindMeanPCK_by_integral(stat_zond,glubina_ot_ustja, d, false, true, mean_pck);
	case 4:
		return FindMeanPCK_by_integral(stat_zond,glubina_ot_ustja, d, true, true, mean_pck);
	case 5:
		return FindMeanPCK_by_integral(stat_zond,glubina_ot_ustja, d, false, false, mean_pck);
	case 6:
		return FindMeanPCK_by_integral(stat_zond,glubina_ot_ustja, d, true, false, mean_pck);
	}
}

double GetBeta2_mariupolsky(long typ_zond, long typgr, double fs)
{
	// fs - входящий параметр бокового сопротивления в кПа

	//double fs0 = 1.0; // 1 тс/м^2 = 0.01 МПа //0.01 МПа;  стр.67
	double fs0 = 10.; // 10 кПа = 0.01 МПа //0.01 МПа;  стр.67

	// коэффициент 
	double beta2 = 0.0;

	switch (typgr)
	{
	case 1://песчаный
		{
			switch (typ_zond)
			{
			case 1:
				{
					beta2 = 1.15 + 4.3 * (fs0 / fs); // (4.11) стр. 62
				}
				break;
			case 2:
			case 3:
				{
					beta2 = 0.90 - 0.46 * log10(fs/fs0);// (4.16) стр.66
				}
				break;
			}
		}
		break;
	case 2://пылевато-глинистый
		{
			switch (typ_zond)
			{
			case 1:
				{
					beta2 = 0.53 + 2.7 * (fs0 / fs); // (4.12) стр. 62
				}
				break;
			case 2:
			case 3:
				{
					beta2 = 1.31 - 0.93 * log10(fs/fs0);// (4.18) стр.67	
				}
				break;
			}
		}
		break;
	}
	return beta2;
}

double GetBeta2(long typ_zond, long typgr, double fs, long id_snip)
{
	// fs - входящий параметр бокового сопротивления в кПа
	// массив сопротивлений грунта на боковой поверхности 
	double vfs[] = { 20.0,  40.0,  60.0,  80.0,  100.0, 120.0 };

	// коэффициент 
	double beta2 = 0.0;

	// Зонд I типа

	// СНиП 2.02.03-85
	double vb2_sand1_2_02_03_85[]  = {2.40, 1.65, 1.20, 1.00, 0.85, 0.75};
	double vb2_clay1_2_02_03_85[]  = {1.50, 1.00, 0.75, 0.60, 0.50, 0.40};

	//СП 50-102-2003
	double vb2_sand_or_clay_1_50_102_2003[]  = {0.8, 0.75, 0.70, 0.65, 0.60, 0.50};
	//double vb2_clay1_50_102_2003[]  = {0.8, 0.75, 0.70, 0.65, 0.60, 0.50};


	// Зонд II и III типа

	//СП 50-102-2003
	double vbi_sand23_50_102_2003[] = {0.75, 0.60, 0.55, 0.50, 0.50, 0.50};
	double vbi_clay23_50_102_2003[] = {1.00, 0.75, 0.60, 0.45, 0.40};

	// СНиП 2.02.03-85
	double vbi_sand23_2_02_03_85[] = {0.75, 0.60, 0.55, 0.50, 0.45, 0.40};
	double vbi_clay23_2_02_03_85[] = {1.00, 0.75, 0.60, 0.45, 0.40, 0.30};

	//Мариупольский стр 67 табл 4.6
	double vbi_sand23_mariupolski[] = {0.76, 0.62, 0.54, 0.48, 0.44, 0.40};
	double vbi_clay23_mariupolski[] = {1.03, 0.75, 0.59, 0.47, 0.38, 0.31};

	switch (id_snip)
	{
	case 1:// СНиП 2.02.03-85 
		{
			switch (typgr)
			{
			case 1://песчаный
				{
					switch (typ_zond)
					{
					case 1:
						{
							// СНиП 2.02.03-85
							linterp_bounded(6, vfs, vb2_sand1_2_02_03_85, fs, beta2);
						}
						break;
					case 2:
					case 3:
						{
							// СНиП 2.02.03-85
							linterp_bounded(6, vfs, vbi_sand23_2_02_03_85, fs, beta2);							
						}
						break;
					}
				}
				break;
			case 2://пылевато-глинистый
				{
					switch (typ_zond)
					{
					case 1:
						{
							// СНиП 2.02.03-85
							linterp_bounded(6, vfs, vb2_clay1_2_02_03_85, fs, beta2);
						}
						break;
					case 2:
					case 3:
						{
							// СНиП 2.02.03-85
							linterp_bounded(6, vfs, vbi_clay23_2_02_03_85, fs, beta2);							
						}
						break;
					}
				}
				break;
			}
		}
		break;
	case 2://СП 50-102-2003
		{
			switch (typ_zond)
			{
			case 1:
				{
					switch (typgr)
					{
					case 0:
					case 1://песчаный
					case 2://пылевато-глинистый
					default: // независимо от типа грунта
						{				
							//СП 50-102-2003                
							linterp_bounded(6, vfs, vb2_sand_or_clay_1_50_102_2003, fs, beta2);				
						}
						break;	
					}
				}
				break;
			case 2:
			case 3:
				{
					switch (typgr)
					{
					case 1://песчаный
						{

							//СП 50-102-2003
							linterp_bounded(6, vfs, vbi_sand23_50_102_2003, fs, beta2);							
						
						}
						break;
					case 2://пылевато-глинистый
						{				
							//СП 50-102-2003
							linterp_bounded(5, vfs, vbi_clay23_50_102_2003, fs, beta2);	
						}
						break;
					}
				}
				break;
			}					
		}
		break;
	}
	return beta2;
}

bool Well_3D::FindIntegralPCB(double glubina_rostverka, double glubina_ot_ustja, double & fh, long id_snip, bool razbivka_na_tolschi, long typ_grunt_1_zond_type, double & beta2, double & fs)
{	
	beta2 = 0.0;
	fs = 0.0;
	switch (this->m_stat_zond.data2.typ_zond)
	{
	case 1:
		{
			switch (id_snip)
			{
			case 1:// СНиП 2.02.03-85
				{
					bool res = FindIntegralPCB_1_my_method_grunt_type_by_IGE(razbivka_na_tolschi, typ_grunt_1_zond_type, glubina_rostverka, glubina_ot_ustja, fh, beta2, fs);
					if (!res)
						res = FindIntegralPCB_1_my_method_grunt_type_by_stat_zond_table(razbivka_na_tolschi, typ_grunt_1_zond_type,glubina_rostverka, glubina_ot_ustja, fh, beta2, fs);
					return res;

				}
				break;
			case 2://СП 50-102-2003
				{
					long typgr = 0;
					return FindIntegralPCB_1(id_snip, typgr, false, 0.0, 0.0, glubina_rostverka, glubina_ot_ustja, fh, beta2, fs);
				}
				break;
			}
		}
		break;
	case 2:
	case 3:
		{
			return FindIntegralPCB_23_by_fsr_tab(glubina_rostverka, glubina_ot_ustja, fh, id_snip);
			//return FindIntegralPCB_23_by_integral(glubina_rostverka, glubina_ot_ustja, fh, id_snip);
		}
	}
	return false;
}
// первый тип зонда интегрирование отдельно песчаных и пылевато-глинистых толщ 
// актуально для СНиП 2.02.03-85
// но не имеет смысла для СП 50-102-2003
bool Well_3D::ZondFirstTypeMyMethod = true;

bool CalcIntegralPCB_by_sum_tolsch(long id_snip, StatZond & stat_zond, vector<grunt_tolscha> & v_grunt_tolscha_1, double & fh)
{
	fh = 0.0;
	if (v_grunt_tolscha_1.size() < 2) 
	{
		return false;
	}
	vector<grunt_tolscha>  v_grunt_tolscha_2;
	v_grunt_tolscha_2.push_back(v_grunt_tolscha_1[0]);
	size_t i_pushed = 0;
	for (size_t i = 2; i < v_grunt_tolscha_1.size(); i++)
	{
		long typgr_0 = v_grunt_tolscha_1[i-1].m_typgr;
		long typgr_1 = v_grunt_tolscha_1[i].m_typgr;
		if (typgr_0 != typgr_1)
		{
			v_grunt_tolscha_2.push_back(v_grunt_tolscha_1[i]);
			i_pushed = i;
		}
	}
	if (i_pushed != v_grunt_tolscha_1.size()-1)
	{
		v_grunt_tolscha_2.push_back(v_grunt_tolscha_1.back());
	}

	for (size_t i = 1; i < v_grunt_tolscha_2.size(); i++)
	{
		double Qs_0, Qs_1;
		double dh = v_grunt_tolscha_2[i].m_h_pod - v_grunt_tolscha_2[i-1].m_h_pod;

		if (stat_zond.GetQs(v_grunt_tolscha_2[i-1].m_h_pod, Qs_0) 
			&& stat_zond.GetQs(v_grunt_tolscha_2[i].m_h_pod, Qs_1))
		{
			double fs = (Qs_1 - Qs_0) / (dh * PI * stat_zond.data2.shtanga_d); // кПа
			double beta2 = GetBeta2(stat_zond.data2.typ_zond, v_grunt_tolscha_2[i].m_typgr, fs, id_snip);
			fh += beta2 * dh * fs;
		}
	}
	return true;
}
bool Well_3D::FindIntegralPCB_1_select_method(long id_snip, 
								 bool razbivka_na_tolschi, long typ_grunt_1_zond_type, 
								 vector<grunt_tolscha> & v_grunt_tolscha,
								 double typgr_1_sum_tolshina,
								 double typgr_2_sum_tolshina,
								 double glubina_rostverka, double glubina_ot_ustja, 
								 double & fh, double & beta2, double & fs)
{
	if (razbivka_na_tolschi)
		return CalcIntegralPCB_by_sum_tolsch(id_snip, this->m_stat_zond, v_grunt_tolscha, fh);
	else
	{
		long typgr = 0;
		bool use_typgr_part = false;
		double sum_tolshina = typgr_1_sum_tolshina + typgr_2_sum_tolshina;
		double typgr_1_part = typgr_1_sum_tolshina / sum_tolshina; // доля песчаной толщи
		double typgr_2_part = typgr_2_sum_tolshina / sum_tolshina; // доля пылевато-глинистой толщи
		switch (typ_grunt_1_zond_type)
		{
		case 1:
			{
				typgr = typgr_1_sum_tolshina > typgr_2_sum_tolshina ? 1 : 2;
			}
			break;
		case 2:
			{
				typgr = v_grunt_tolscha.back().m_typgr;
			}
			break;
		case 3:
			{
				if (typgr_2_part > 0.0)
					typgr = 2;
			}
			break;
		case 4:
			{
				use_typgr_part = true;
			}
			break;
		}
		return this->FindIntegralPCB_1(id_snip, typgr, use_typgr_part, typgr_1_part, typgr_2_part, glubina_rostverka, glubina_ot_ustja, fh, beta2, fs);
	}
}


bool Well_3D::FindIntegralPCB_1_my_method_grunt_type_by_IGE(bool razbivka_na_tolschi, long typ_grunt_1_zond_type, double glubina_rostverka, double glubina_ot_ustja, double & fh, double & beta2, double & fs)
{
	// только для 
	// СНиП 2.02.03-85
	long id_snip = 1;
	// тип грунта берётся из разбивки по ИГЭ
	vector<grunt_tolscha> v_grunt_tolscha;
	//заполняем вектор грунтовых толщ
	bool to_fill = true;
	if (to_fill)
	{
		grunt_tolscha gt;
		gt.m_h_pod = glubina_rostverka;
		gt.m_typgr = 0;
//		gt.m_Qs_determined = m_stat_zond.GetQs(glubina_rostverka, gt.Qs);
		v_grunt_tolscha.push_back(gt);
	}	

	double typgr_1_sum_tolshina = 0.0;
	double typgr_2_sum_tolshina = 0.0;

	if (this->m_db_lito.data_filled)
	{
		for (vector<db_lito_data>::iterator it_lit = this->m_db_lito.data1.begin();
			it_lit != this->m_db_lito.data1.end(); it_lit++)
		{
			double h0 = (*it_lit).h0;
			double h1 = (*it_lit).h1;
	
			if (this->m_pSurfDoc)
			{
				bool found = false;
				for (vector<IGE_Data>::iterator it_ige = this->m_pSurfDoc->m_db_ige.data.begin();
					it_ige != this->m_pSurfDoc->m_db_ige.data.end(); it_ige++)
				{
					if ((*it_ige).ige_filled && (*it_ige).grunt_filled && (*it_ige).ige.id_ige == (*it_lit).id_ige)
					{
						long typgr = (*it_ige).grunt.typgr;

						if (h1 > glubina_rostverka)
						{
							if (h1 < glubina_ot_ustja)
							{
								grunt_tolscha gt;
								gt.m_h_pod = h1;
								gt.m_typgr = typgr;
//								gt.m_Qs_determined = m_stat_zond.GetQs(h1, gt.Qs);
								v_grunt_tolscha.push_back(gt);

								switch (typgr)
								{
								case 1:
									{
										typgr_1_sum_tolshina += h1 - h0;
									}
									break;
								case 2:
									{
										typgr_2_sum_tolshina += h1 - h0;
									}
									break;
								}
							}
							else
							{
								if (to_fill)
								{
									grunt_tolscha gt;
									gt.m_h_pod = glubina_ot_ustja;
									gt.m_typgr = typgr;
//									gt.m_Qs_determined = m_stat_zond.GetQs(glubina_ot_ustja, gt.Qs);
									v_grunt_tolscha.push_back(gt);
									switch (typgr)
									{
									case 1:
										{
											typgr_1_sum_tolshina += glubina_ot_ustja - h0;
										}
										break;
									case 2:
										{
											typgr_2_sum_tolshina += glubina_ot_ustja - h0;
										}
										break;
									}
								}
								to_fill = false;
							}
						}												
					}
				}	
			}		
		}
	}
	else
		return false;

	return FindIntegralPCB_1_select_method(id_snip, 
		razbivka_na_tolschi, typ_grunt_1_zond_type, 
		v_grunt_tolscha,
		typgr_1_sum_tolshina,
		typgr_2_sum_tolshina,
		glubina_rostverka, glubina_ot_ustja,
		fh, beta2, fs);
}
bool Well_3D::FindIntegralPCB_1_my_method_grunt_type_by_stat_zond_table(bool razbivka_na_tolschi, long typ_grunt_1_zond_type, double glubina_rostverka, double glubina_ot_ustja, double & fh, double & beta2, double & fs)
{	
	// только для 
	// СНиП 2.02.03-85
	long id_snip = 1;
	// тип грунта берётся из таблицы статзондирования

	vector<grunt_tolscha> v_grunt_tolscha;
	//заполняем вектор грунтовых толщ
	bool to_fill = true;
	if (to_fill)
	{
		grunt_tolscha gt;
		gt.m_h_pod = glubina_rostverka;
		gt.m_typgr = 0;
//		gt.m_Qs_determined = m_stat_zond.GetQs(glubina_rostverka, gt.Qs);
		v_grunt_tolscha.push_back(gt);
	}	

	double typgr_1_sum_tolshina = 0.0;
	double typgr_2_sum_tolshina = 0.0; 
	for (size_t i = 0; i + 1 < m_stat_zond.data1.size(); i++)
	{

	//for (vector<StatZondData1>::iterator it = m_stat_zond.data1.begin();
	//	(it+1) != m_stat_zond.data1.end(); it++)
	//{		
	//	double h_0 = (*it).h;
	//	double h_1 = (*(it+1)).h;

	//	long typgr_0 = (*it).typgr;
	//	long typgr_1 = (*(it+1)).typgr;

		double h_0 = m_stat_zond.data1[i].h;
		double h_1 = m_stat_zond.data1[i+1].h;

		long typgr_0 = m_stat_zond.data1[i].typgr;
		long typgr_1 = m_stat_zond.data1[i+1].typgr;

		// ищем подошву по признаку изменения типа грунта
		if (typgr_0 != typgr_1
			||
			//или если мы дошли до конца 
			i + 2 == m_stat_zond.data1.size())
		{
			double h_pod = typgr_0 != typgr_1 ? 0.5 * (h_0 + h_1) : h_1;
			if (h_pod > glubina_rostverka)
			{
				if (h_pod < glubina_ot_ustja)
				{
					grunt_tolscha gt;
					gt.m_h_pod = h_pod;
					gt.m_typgr = typgr_0;
//					gt.m_Qs_determined = m_stat_zond.GetQs(h_pod, gt.Qs);
					switch (typgr_0)
					{
					case 1:
						{
							typgr_1_sum_tolshina += h_pod - v_grunt_tolscha.back().m_h_pod;
						}
						break;
					case 2:
						{
							typgr_2_sum_tolshina += h_pod - v_grunt_tolscha.back().m_h_pod;
						}
						break;
					}					
					v_grunt_tolscha.push_back(gt);

				}
				else
				{
					if (to_fill)
					{
						grunt_tolscha gt;
						gt.m_h_pod = glubina_ot_ustja;
						gt.m_typgr = typgr_0;
//						gt.m_Qs_determined = m_stat_zond.GetQs(glubina_ot_ustja, gt.Qs);
						switch (typgr_0)
						{
						case 1:
							{
								typgr_1_sum_tolshina += glubina_ot_ustja - v_grunt_tolscha.back().m_h_pod;
							}
							break;
						case 2:
							{
								typgr_2_sum_tolshina += glubina_ot_ustja - v_grunt_tolscha.back().m_h_pod;
							}
							break;
						}					
						v_grunt_tolscha.push_back(gt);
					}
					to_fill = false;
				}
			}
		}
	}
	return FindIntegralPCB_1_select_method(id_snip, 
		razbivka_na_tolschi, typ_grunt_1_zond_type, 
		v_grunt_tolscha,
		typgr_1_sum_tolshina,
		typgr_2_sum_tolshina,
		glubina_rostverka, glubina_ot_ustja,
		fh, beta2, fs);
}

bool Well_3D::FindIntegralPCB_1(long id_snip, long typgr, bool use_typgr_part, double typgr_1_part, double typgr_2_part, double glubina_rostverka, double glubina_ot_ustja, double & fh, double & beta2, double & fs)
{	
	// первый тип зонда интегрирование без разделения песчаных и пылевато-глинистых толщ 
	
	// актуально для СП 50-102-2003 (id_snip = 2) при этом //long typgr = 0; // независимо от типа грунта
	

	fh = 0.0;
	if (glubina_rostverka >= 0.0 && glubina_ot_ustja > 0.0)
	{
		double Qs_rostverk, Qs;
		if (m_stat_zond.GetQs(glubina_rostverka, Qs_rostverk) && m_stat_zond.GetQs(glubina_ot_ustja, Qs))
		{
			fs = (Qs - Qs_rostverk) / ((glubina_ot_ustja - glubina_rostverka) * PI * this->m_stat_zond.data2.shtanga_d); // кПа
			
			if (use_typgr_part)
			{
				double beta2_1 = GetBeta2(this->m_stat_zond.data2.typ_zond, 1, fs, id_snip);
				double beta2_2 = GetBeta2(this->m_stat_zond.data2.typ_zond, 2, fs, id_snip);

				beta2 = typgr_1_part * beta2_1 + typgr_2_part * beta2_2;
			}
			else
                beta2 = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr, fs, id_snip);

			fh += beta2 * (glubina_ot_ustja - glubina_rostverka) * fs;
		}
	}
	return true;
}
bool Well_3D::FindIntegralPCB_23_by_fsr_tab(double glubina_rostverka, double glubina_ot_ustja, double & fh, long id_snip)
{	
	fh = 0.0;

	int flag = 0;
	for (vector<StatZondData1>::iterator it = m_stat_zond.data1.begin();
		(it+1) != m_stat_zond.data1.end() && flag < 2; it++)
	{		
		double f_0 = (*it).GetPCB();
		double f_1 =(*(it+1)).GetPCB();
		
		//fsr = 0.5 * (f_0 + f_1);
		double fsr = m_stat_zond.data2.Kf * (*(it+1)).fsr + m_stat_zond.data2.Bf;


		double h_0 = (*it).h;
		double h_1 = (*(it+1)).h;
		double dh = (*(it+1)).dh;

		long typgr = (*(it+1)).typgr; 

		switch (flag)
		{
		case 0:
			{
 				if (glubina_rostverka <= h_0)
				{
					double betai = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr, fsr, id_snip);
					fh += betai * dh * fsr;
					flag = 1;
				}
			}
			break;
		case 1:
			{
				if (glubina_ot_ustja >= h_1)
				{
					double betai = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr, fsr, id_snip);
					fh += betai * dh * fsr;
				}
				else
				{
					flag = 2;
				}
			}
			break;
		}

	}

	return true;
}
bool Well_3D::FindIntegralPCB_23_by_integral(double glubina_rostverka, double glubina_ot_ustja, double & fh, long id_snip)
{	
	int flag = 0;
	fh = 0.0;

	for (vector<StatZondData1>::iterator it = m_stat_zond.data1.begin();
		(it+1) != m_stat_zond.data1.end() && flag < 2; it++)
	{		
		double f_0 = (*it).GetPCB();
		double f_1 =(*(it+1)).GetPCB();

		double h_0 = (*it).h;
		double h_1 = (*(it+1)).h;
		double dh = h_1 - h_0;


#if 1
		long typgr_0 = (*it).typgr;
		long typgr_1 = (*(it+1)).typgr;

		double betai_0 = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr_0, f_0, id_snip);
		double betai_f_0 = betai_0 * f_0;

		double betai_1 = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr_1, f_1, id_snip);
		double betai_f_1 = betai_1 * f_1;

#else
		double betai_f_0, betai_f_1;
		long typgr_0;
		if (this->GetTypGrunt_from_db_lito(h_0, typgr_0))
		{
			double betai = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr_0, f_0);
			betai_f_0 = betai * f_0;

			//char str[4098];
			//sprintf(str, "beta2_f_0 = %f", beta2_f_0);
			//MessageBox(0,str, "1", 0);
		}
		else
		{
			char str[4098];
			sprintf(str, "glubina_ot_ustja = %f h_0 = %f h_1 = %f flag = %d", glubina_ot_ustja, h_0, h_1, flag);
			MessageBox(0,str, "!GetTypGrunt_from_db_lito 0", 0);
			betai_f_0 = 0.0;
		}

		long typgr_1;
		if (this->GetTypGrunt_from_db_lito(h_1, typgr_1))
		{
			double betai = GetBeta2(this->m_stat_zond.data2.typ_zond, typgr_1, f_1);
			betai_f_1 = betai * f_1;

			//char str[4098];
			//sprintf(str, "beta2_f_1 = %f", beta2_f_1);
			//MessageBox(0,str, "1", 0);
		}
		else
		{
			char str[4098];
			sprintf(str, "glubina_ot_ustja = %f h_0 = %f h_1 = %f flag = %d", glubina_ot_ustja, h_0, h_1, flag);
			MessageBox(0,str, "!GetTypGrunt_from_db_lito 1", 0);
			betai_f_1 = 0.0;
		}
#endif
#define TRAPEC 1
#define USE_LOW 1
		switch (flag)
		{
		case 0:
			{
 				if (glubina_rostverka <= h_0)
				{
#if TRAPEC 
					fh += 0.5 * (h_1 - h_0) * (betai_f_0 + betai_f_1);		
#else
#if USE_LOW
					fh += (h_1 - h_0) * betai_f_1;	
#else
					fh += (h_1 - h_0) * betai_f_0;	
#endif
#endif
					flag = 1;
				}
				else if (glubina_rostverka >= h_0 && glubina_rostverka <= h_1)
				{
					double mu = (glubina_rostverka - h_0) / (h_1 - h_0);
					double betai_f_ = betai_f_0 + mu * (betai_f_1 - betai_f_0);

#if TRAPEC 
					fh +=  0.5 * (h_1 - glubina_rostverka) * (betai_f_ + betai_f_1);
#else
#if USE_LOW
					fh +=  (h_1 - glubina_rostverka) * betai_f_1;
#else
					fh +=  (h_1 - glubina_rostverka) * betai_f_;
#endif
#endif
					flag = 1;
				}
				else
				{
					char str[4098];
					sprintf(str, "glubina_rostverka = %f h_0 = %f h_1 = %f flag = %d", glubina_rostverka, h_0, h_1, flag);
					MessageBox(0,str, "else", 0);
				}
			}
			break;
		case 1:
			{
				if (glubina_ot_ustja > h_1)
				{
#if TRAPEC 
					fh += 0.5 * (h_1 - h_0) * (betai_f_0 + betai_f_1);
#else
#if USE_LOW
					fh += (h_1 - h_0) * betai_f_1;		
#else
					fh += (h_1 - h_0) * betai_f_0;		
#endif
#endif
				}
				else
				{
					double mu = (glubina_ot_ustja - h_0) / (h_1 - h_0);
					double betai_f_ = betai_f_0 + mu * (betai_f_1 - betai_f_0);

#if TRAPEC 
					fh += 0.5 * (glubina_ot_ustja - h_0) * (betai_f_0 + betai_f_);
#else
#if USE_LOW
					fh += (glubina_ot_ustja - h_0) * betai_f_;
#else
					fh += (glubina_ot_ustja - h_0) * betai_f_0;
#endif
#endif
					flag = 2;
				}
			}
			break;
		}
	}
	return true;
}
long Well_3D::zab_svai_id_snip = 1;
void Well_3D::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Well_3D id");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->GetIDString());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "Well_3D GetPointsNumber()");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->GetPointsNumber());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "Well_3D m_vstrSloiNames.size()");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->m_vstrSloiNames.size());
	text.push_back(fmtstr(str, NULL, true, true));


	sprintf(str, "Well_3D m_vColor.size()");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->m_vColor.size());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "Well_3D well_colomns.size()");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->well_colomns.size());
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "ID комплексной точки");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->m_id_kt);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "тип комплексной точки");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->m_kt_idtyp);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "способ бурения");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->m_id_bur_type);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "диаметр бурения");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%d", this->m_d_bur);
	text.push_back(fmtstr(str, NULL, true, true));

	sprintf(str, "дата бурения");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "%s", this->m_data_bur.c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	for (vector<WellColomn>::iterator it = this->well_colomns.begin();
		it != this->well_colomns.end(); it++)
	{
		//printf("well colomn of type \"%s\"\n", WellElement::WellElementTypeToString((*it).first));

		(*it).PrintfProperties(text);
	
	}
#if 0
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			this->m_karotazhy.GetCurrentMsg().PrintfProperties(text);
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
#endif

	//максимальное число точек в каротажах
	bool start = true;
	size_t npoints = 0;
	if (this->m_karotazhy.SetCurrentMsgOnFirst() )
	{
		do
		{
			if (start)
			{
				npoints = this->m_karotazhy.GetCurrentMsg().GetPointsNumber();
				start = false;
			}
			else
			{
				if (npoints < this->m_karotazhy.GetCurrentMsg().GetPointsNumber())
					npoints = this->m_karotazhy.GetCurrentMsg().GetPointsNumber();
			}			
		}
		while(this->m_karotazhy.IncrementCurrentMsg());
	}
	// заголовки каротажей
	{
		text.push_back(fmtstr("", NULL, false, true));

		if (this->m_karotazhy.SetCurrentMsgOnFirst() )
		{
			do
			{
				sprintf(str, "%s", this->m_karotazhy.GetCurrentMsg().GetName().c_str()); 
				text.push_back(fmtstr(str, NULL, false, true));
			}
			while(this->m_karotazhy.IncrementCurrentMsg());
		}
		text.push_back(fmtstr("", NULL, true, true));
	}
	//строки таблицы картажей
	for (size_t ipoint = 0; ipoint < npoints; ipoint++)
	{	
		sprintf(str, "%d", ipoint);
		text.push_back(fmtstr(str, NULL, false, true));

		if (this->m_karotazhy.SetCurrentMsgOnFirst() )
		{
			do
			{
				if (ipoint < this->m_karotazhy.GetCurrentMsg().GetPointsNumber())
				{
					double v = this->m_karotazhy.GetCurrentMsg().GetDocumentPoint(ipoint).v;
					sprintf(str, "%f", v); DeleteEndZeros(str);
					text.push_back(fmtstr(str, NULL, false, true));
				}
				else
				{
					text.push_back(fmtstr(" ", NULL, false, true));
				}
			}
			while(this->m_karotazhy.IncrementCurrentMsg());
		}
		text.push_back(fmtstr("", NULL, true, true));
	}

	if (this->m_stat_zond.data1_filled)
	{
		sprintf(str, "Установка %s", this->m_stat_zond.data2.ust_name.c_str()); 
		text.push_back(fmtstr(str, NULL, false, true));
		
		sprintf(str, "Тип зонда %d", this->m_stat_zond.data2.typ_zond);
		text.push_back(fmtstr(str, NULL, false, true));
			
		sprintf(str, "Диам.шт. %f", this->m_stat_zond.data2.shtanga_d); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));

		sprintf(str, "Kg = %f", this->m_stat_zond.data2.Kg); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		
		sprintf(str, "Kf = %f", this->m_stat_zond.data2.Kf); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));

		sprintf(str, "Bg = %f", this->m_stat_zond.data2.Bg); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
		
		sprintf(str, "Bf = %f", this->m_stat_zond.data2.Bf); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));

		sprintf(str, "Глубина %f", this->m_stat_zond.data2.glyb); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, false, true));
			

		sprintf(str, "Нач.глуб %f", this->m_stat_zond.data2.nach_glyb); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));
			

		text.push_back(fmtstr("Глубина,м", NULL, false, true));
		text.push_back(fmtstr("typgr", NULL, false, true));
		text.push_back(fmtstr("q0, МПа", NULL, false, true));
		text.push_back(fmtstr("f0, кПа", NULL, false, true));
		text.push_back(fmtstr("q, МПа", NULL, false, true));
		text.push_back(fmtstr("f, кПа", NULL, false, true));
			
		text.push_back(fmtstr("", NULL, true, true));

		for (vector<StatZondData1>::iterator it = this->m_stat_zond.data1.begin();
			it != this->m_stat_zond.data1.end(); it++)
		{		
			sprintf(str, "%f", (*it).h); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%d", (*it).typgr);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).q0); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).f0); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			double q = this->m_stat_zond.data2.Kg * (*it).q0 + this->m_stat_zond.data2.Bg;
			double f = this->m_stat_zond.data2.Kf * (*it).f0 + this->m_stat_zond.data2.Bf;
			
			sprintf(str, "%f", q); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", f); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			text.push_back(fmtstr("", NULL, true, true));
		}
	}

	if (this->m_palja.data2_filled)
	{
		char sv[128];
		sprintf(sv, "%f", this->m_palja.data2.pz); 
		DeleteEndZeros(sv);


		sprintf(str, "Абсолютная отметка ростверка %s м", sv); 
		text.push_back(fmtstr(str, NULL, true, true));

		if (this->m_palja.data2.id_typ == 1)
		{
			sprintf(sv, "%f", this->m_palja.data2.pereriz_x); 
			DeleteEndZeros(sv);
			sprintf(str, "Радиус круглой сваи %s м", sv); 
			text.push_back(fmtstr(str, NULL, true, true));
		}
		else
		{
			sprintf(sv, "%f", this->m_palja.data2.pereriz_x); 
			DeleteEndZeros(sv);
			char sy[128];
			sprintf(sy, "%f", this->m_palja.data2.pereriz_y); 
			DeleteEndZeros(sy);
			sprintf(str, "Разрез сваи %s x %s, м", sv, sy); 
			text.push_back(fmtstr(str, NULL, true, true));
		}
			
			
		sprintf(sv, "%f", this->m_palja.data2.A); 
		DeleteEndZeros(sv);
		sprintf(str, "А %s м", sv);
		text.push_back(fmtstr(str, NULL, false, true));

		sprintf(sv, "%f", this->m_palja.data2.u); 
		DeleteEndZeros(sv);
		sprintf(str, "u %s м", sv);
		text.push_back(fmtstr(str, NULL, true, true));
		
		sprintf(sv, "%f", this->m_palja.data2.RsA); 
		DeleteEndZeros(sv);
		sprintf(str, "RsA %s м", sv);
		text.push_back(fmtstr(str, NULL, false, true));
		
		sprintf(sv, "%f", this->m_palja.data2.fhu); 
		DeleteEndZeros(sv);
		sprintf(str, "fhu %s м", sv);
		text.push_back(fmtstr(str, NULL, true, true));
		
		sprintf(sv, "%f", this->m_palja.data2.glyb); 
		DeleteEndZeros(sv);
		sprintf(str, "Глубина %s м", sv);
		text.push_back(fmtstr(str, NULL, true, true));


		text.push_back(fmtstr("Абс.отм.остр.сваи,м", NULL, false, true));
		text.push_back(fmtstr("Глубина,м", NULL, false, true));
		text.push_back(fmtstr("Лоб.сопр., кН", NULL, false, true));
		text.push_back(fmtstr("Бок.сопр., кН", NULL, false, true));
		text.push_back(fmtstr("Общ.сопр., кН", NULL, false, true));
			
		text.push_back(fmtstr("", NULL, true, true));

		for (vector<PaljaData1>::iterator it = this->m_palja.data1.begin();
			it != this->m_palja.data1.end(); it++)
		{		
			sprintf(str, "%f", this->m_palja.data2.pz - (*it).h); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).h); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).RsA); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).fhu); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).RsA + (*it).fhu); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			text.push_back(fmtstr("", NULL, true, true));
		}
	}

	if (this->m_palja.data1_filled)
	{
		char sv[128];
		char sy[128];

		double A;
		double u;
		double d; //диаметр, ширина или большая сторона сечения сваи

		sprintf(sv, "%f", this->m_palja.data2.pz); 
		DeleteEndZeros(sv);
		sprintf(str, "Далее мой расчёт: Абсолютная отметка ростверка %s м", sv); 
		text.push_back(fmtstr(str, NULL, true, true));

		if (this->m_palja.data2.id_typ == 1)
		{

			double r = this->m_palja.data2.pereriz_x;
			d = 2.0 * r;

			A = PI * r * r;
			u = 2.0 * PI * r;

			sprintf(sv, "%f", r); 
			DeleteEndZeros(sv);
			sprintf(str, "Радиус круглой сваи %s, м", sv); 
			text.push_back(fmtstr(str, NULL, true, true));
			
		}
		else
		{
			d = max(this->m_palja.data2.pereriz_x, this->m_palja.data2.pereriz_y);
			A = this->m_palja.data2.pereriz_x * this->m_palja.data2.pereriz_y;
			u = 2.0 * (this->m_palja.data2.pereriz_x + this->m_palja.data2.pereriz_y);

			sprintf(sv, "%f", this->m_palja.data2.pereriz_x); 
			DeleteEndZeros(sv);
			sprintf(sy, "%f", this->m_palja.data2.pereriz_y); 
			DeleteEndZeros(sy);
			sprintf(str, "Разрез сваи %s x %s м", sv, sy); 
			text.push_back(fmtstr(str, NULL, true, true));
		}
#define COMPARE_WITH_WENGEO_PALJA 0
			
			
#if COMPARE_WITH_WENGEO_PALJA
		sprintf(sv, "%f", this->m_palja.data2.A); 
		DeleteEndZeros(sv);

		sprintf(sy, "%f", A); 
		DeleteEndZeros(sy);

		sprintf(str, "А %s %s м", sv, sy);
		text.push_back(fmtstr(str, NULL, false, true));
#else
		sprintf(sv, "%f", A); 
		DeleteEndZeros(sv);
		sprintf(str, "А %s м", sv);
		text.push_back(fmtstr(str, NULL, false, true));
#endif

#if COMPARE_WITH_WENGEO_PALJA

		sprintf(sv, "%f", this->m_palja.data2.u); 
		DeleteEndZeros(sv);
		sprintf(sy, "%f", u); 
		DeleteEndZeros(sy);


		sprintf(str, "u %s %s м", sv, sy);
		text.push_back(fmtstr(str, NULL, true, true));
		
		sprintf(sv, "%f", this->m_palja.data2.RsA); 
		DeleteEndZeros(sv);
		sprintf(str, "RsA %s м", sv);
		text.push_back(fmtstr(str, NULL, false, true));
		
		sprintf(sv, "%f", this->m_palja.data2.fhu); 
		DeleteEndZeros(sv);
		sprintf(str, "fhu %s м", sv);
		text.push_back(fmtstr(str, NULL, true, true));
		
		sprintf(sv, "%f", this->m_palja.data2.glyb); 
		DeleteEndZeros(sv);
		sprintf(str, "Глубина %s м", sv);
		text.push_back(fmtstr(str, NULL, true, true));
#else
		sprintf(sv, "%f", u); 
		DeleteEndZeros(sv);

		sprintf(str, "u %s м", sv);
		text.push_back(fmtstr(str, NULL, true, true));
#endif

		text.push_back(fmtstr("Абс.отм.остр.сваи,м", NULL, false, true));
		text.push_back(fmtstr("Глуб. от роств.,м", NULL, false, true));
		text.push_back(fmtstr("Ср.сопр.кон.,МПа", NULL, false, true));
		text.push_back(fmtstr("Бета 1", NULL, false, true));
		text.push_back(fmtstr("Сопр.под.ниж.кон.сваи,МПа", NULL, false, true));
		text.push_back(fmtstr("Лоб.сопр., кН", NULL, false, true));

		text.push_back(fmtstr("Бок.сопр., кН", NULL, false, true));
		text.push_back(fmtstr("Общ.сопр., кН", NULL, false, true));
			
		text.push_back(fmtstr("", NULL, true, true));

		CPoint3 ustje;
		if (this->GetUstje(ustje))
		{
			double max_palja_h_ot_ustja = m_stat_zond.data2.glyb - 4 * d;
printf("max_palja_h_ot_ustja %f = m_stat_zond.data2.glyb %f - 4 * d %f\n", max_palja_h_ot_ustja, m_stat_zond.data2.glyb, d); 
			double glubina_rostverka = ustje.z - this->m_palja.data2.pz;
#if !COMPARE_WITH_WENGEO_PALJA
			double max_palja_h_ot_rostverka = max_palja_h_ot_ustja - glubina_rostverka;
			bool go = true;
			for (double glubina_ot_rostverka = 1.0; 
				go; 
				glubina_ot_rostverka += (max_palja_h_ot_rostverka - glubina_ot_rostverka > 1.0 ? 1.0 : max_palja_h_ot_rostverka - glubina_ot_rostverka))
			{
				go = glubina_ot_rostverka < max_palja_h_ot_rostverka;
printf("go %d = glubina_ot_rostverka %f < max_palja_h_ot_rostverka%f\n", go, glubina_ot_rostverka, max_palja_h_ot_rostverka); 

#else
			for (vector<PaljaData1>::iterator it = this->m_palja.data1.begin();
				it != this->m_palja.data1.end(); it++)
			{	
				double glubina_ot_rostverka = (*it).h;
#endif

				double glubina_ot_ustja = glubina_ot_rostverka + glubina_rostverka;
				double mean_pck;

				sprintf(str, "%f", this->m_palja.data2.pz - glubina_ot_rostverka); DeleteEndZeros(str);
				text.push_back(fmtstr(str, NULL, false, true));

				sprintf(str, "%f", glubina_ot_rostverka); DeleteEndZeros(str);
				text.push_back(fmtstr(str, NULL, false, true));

				long id_snip = Well_3D::zab_svai_id_snip;
				long id_method = g_FindMeanPCK_id_method;

				if (FindMeanPCK(this->m_stat_zond, glubina_ot_ustja, d, mean_pck, id_method))
				{
					// Л.Г.Мариупольский 
					// Исследования грунтов для проектирования свайных фундаментов
					// Москва, Стройиздат, 1989
					double qs = mean_pck;
					

					long typgr;
					if (this->GetTypGrunt_from_db_lito(glubina_ot_ustja, typgr))
					{
						double beta1_mariupolsky = GetBeta1_mariupolsky(this->m_stat_zond.data2.typ_zond, typgr, qs);
					}
#if 0
					double beta1 = GetBeta1_mariupolsky(typgr, qs);
#else
					double beta1 = GetBeta1(qs, id_snip);
#endif
					double R = beta1 * qs; // (4.7) стр.60

					double RA = 1000.*R*A;


#if COMPARE_WITH_WENGEO_PALJA
					sprintf(str, "%f %f", RA, RA / (*it).RsA); DeleteEndZeros(str);
					text.push_back(fmtstr(str, NULL, false, true));
#else
					sprintf(str, "%f", qs); DeleteEndZeros(str);
					text.push_back(fmtstr(str, NULL, false, true));

					sprintf(str, "%f", beta1); DeleteEndZeros(str);
					text.push_back(fmtstr(str, NULL, false, true));

					sprintf(str, "%f", R); DeleteEndZeros(str);
					text.push_back(fmtstr(str, NULL, false, true));

					sprintf(str, "%f", RA); DeleteEndZeros(str);
					text.push_back(fmtstr(str, NULL, false, true));
#endif

					double fh;

					double beta2;
					double fs;
					bool razbivka_na_tolschi = false;
					long typ_grunt_1_zond_type = 1;
					if(this->FindIntegralPCB(glubina_rostverka, glubina_ot_ustja, fh, id_snip, razbivka_na_tolschi,typ_grunt_1_zond_type, beta2, fs))
					{
#if COMPARE_WITH_WENGEO_PALJA
						sprintf(str, "%f %f", fh * u,  fh * u / (*it).fhu); DeleteEndZeros(str);
#else
						sprintf(str, "%f", fh * u); DeleteEndZeros(str);
#endif
						text.push_back(fmtstr(str, NULL, false, true));

						double Fu = 0.0;
						switch (id_snip)
						{
						case 1:
							Fu = RA + fh * u; //(4.6) стр.59
							break;
						case 2:
							Fu = 0.4 * RA + 0.8 * fh * u; //(4.6) стр.59
							break;
						}

						sprintf(str, "%f", Fu); DeleteEndZeros(str);
						text.push_back(fmtstr(str, NULL, false, true));

						text.push_back(fmtstr("", NULL, true, true));

					}

					text.push_back(fmtstr("", NULL, true, true));
				}
				else
					text.push_back(fmtstr("", NULL, true, true));

			}
		}
	}


	if (this->m_db_lito.data_filled)
	{
		text.push_back(fmtstr("id_ige", NULL, false, true));
		text.push_back(fmtstr("Глубина,м", NULL, false, true));
		text.push_back(fmtstr("Глубина,м", NULL, false, true));			
		text.push_back(fmtstr("", NULL, true, true));

		for (vector<db_lito_data>::iterator it = m_db_lito.data1.begin();
			it != m_db_lito.data1.end(); it++)
		{		
			sprintf(str, "%d", (*it).id_ige);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).h0); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			sprintf(str, "%f", (*it).h1); DeleteEndZeros(str);
			text.push_back(fmtstr(str, NULL, false, true));

			text.push_back(fmtstr("", NULL, true, true));
		}
	}
}


void Karotazh::PrintfProperties(vector<fmtstr> & text)
{
	char str[4098];

	sprintf(str, "Karotazh");
	text.push_back(fmtstr(str, NULL, false, true));
	sprintf(str, "\"%s\"", this->GetName().c_str());
	text.push_back(fmtstr(str, NULL, true, true));

	for (size_t ipoint = 0; ipoint < this->GetPointsNumber(); ipoint++)
	{		
		sprintf(str, "%d", ipoint);
		text.push_back(fmtstr(str, NULL, false, true));
		sprintf(str, "%f", m_vdPoints[ipoint].v); DeleteEndZeros(str);
		text.push_back(fmtstr(str, NULL, true, true));
	}

}



void Well_3D::PropertiesDialog()
{
	printf("Well_3D::Properties id = \"%s\"\n", this->GetIDString());
	
	printf("this->GetPointsNumber() = %d\n", this->GetPointsNumber());
	printf("this->m_vstrSloiNames.size() = %d\n", this->m_vstrSloiNames.size());
	printf("this->m_vColor.size() = %d\n", this->m_vColor.size());
	printf("this->well_colomns.size() = %d\n", this->well_colomns.size());


	for (vector<WellColomn>::iterator it = this->well_colomns.begin();
		it != this->well_colomns.end(); it++)
	{
		//printf("well colomn of type \"%s\"\n", WellElement::WellElementTypeToString((*it).first));

		(*it).PrintfProperties();
	
	}

	MessageBox(0, "PropertiesDialog", "Well_3D" , 0);

}

void Well_3D::Init(const Well_3D& ob)
{
	this->m_pSurfDoc			= ob.m_pSurfDoc;
	this->m_type				= ob.m_type;
	this->m_vColor				= ob.m_vColor;
	this->m_vstrSloiNames		= ob.m_vstrSloiNames;
#if USE_STRING_IN_THE_CELL
	//string	sID;
	this->sID					= ob.sID;
#else
	//char sID[CELL_S_N_CHARS];
	strncpy(sID,ob.sID,CELL_S_N_CHARS);
#endif
	this->m_karotazhy			= ob.m_karotazhy;

	this->well_colomns			= ob.well_colomns;

	this->m_id_kt				= ob.m_id_kt;// ID комплексной точки
	this->m_kt_idtyp			= ob.m_kt_idtyp;//тип комплексной точки
	this->m_id_bur_type			= ob.m_id_bur_type; // способ бурения
	this->m_d_bur				= ob.m_d_bur; // диаметр бурения
	this->m_data_bur			= ob.m_data_bur; // дата бурения

	this->m_stat_zond			= ob.m_stat_zond;
	this->m_palja				= ob.m_palja;
	this->m_db_lito0			= ob.m_db_lito0;
	this->m_db_lito				= ob.m_db_lito;
	this->m_db_voda				= ob.m_db_voda;

}

Well_3D::Well_3D(const Well_3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

Well_3D& Well_3D::operator=(const Well_3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD Well_3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, Well_3D& ob)
{
	DWORD version = ob.Object::Serialize(ar);
	ob.Primitive3D<CPoint3>::Primitive_Serialize(ar);

	switch (version)
	{
	case 4:
		{
			ar << ob.m_id_kt; // ID комплексной точки
			ar << ob.m_kt_idtyp; //тип комплексной точки
			ar << ob.m_id_bur_type; // способ бурения
			ar << ob.m_d_bur; // диаметр бурения
			ar << ob.m_data_bur; // дата бурения
		}
	case 3:
		{
			ar << ob.well_colomns;
		}
	case 2:
		{
			ar << ob.m_karotazhy;
		}
		// do not break here
	case 1:
		{
			ar << ob.m_type;
			ar << ob.m_vColor;
			ar << ob.sID;
			ar << ob.m_vstrSloiNames;
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
Archive& operator >>(Archive& ar, Well_3D& ob)
{
	ob.Object::Serialize(ar);
	ob.Primitive3D<CPoint3>::Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 4:
		{
			ar >> ob.m_id_kt; // ID комплексной точки
			ar >> ob.m_kt_idtyp; //тип комплексной точки
			ar >> ob.m_id_bur_type; // способ бурения
			ar >> ob.m_d_bur; // диаметр бурения
			ar >> ob.m_data_bur; // дата бурения
		}
	case 3:
		{
			ar >> ob.well_colomns;
			for (vector<WellColomn>::iterator it = ob.well_colomns.begin();
				it != ob.well_colomns.end(); it++)
			{
				(*it).InitWell(&ob);
				(*it).InitDoc((SurfDoc*)ob.GetDoc());
			}
		}
	case 2:
		{
			ar >> ob.m_karotazhy;
		}
		// do not break here
	case 1:
		{
			ob.m_object_version = 4;



			ar >> ob.m_type;
			ar >> ob.m_vColor;
			ar >> ob.sID;
			ar >> ob.m_vstrSloiNames;
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

DWORD Karotazh::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, Karotazh& ob)
{

	DWORD version = ob.Object::Serialize(ar);
	ob.Primitive3D<CPoint4>::Primitive_Serialize(ar);
	
	switch (version)
	{
	case 1:
		{
			ar << ob.m_index;
			ar << ob.m_min_v;
			ar << ob.m_max_v;
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
	
Archive& operator >>(Archive& ar, Karotazh& ob)
{
	
	ob.Object::Serialize(ar);
	ob.Primitive3D<CPoint4>::Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_index;
			ar >> ob.m_min_v;
			ar >> ob.m_max_v;
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

Archive& operator <<(Archive& ar, karotazh_list_item& ob)
{
	ar << ob.version;
	switch (ob.version)
	{
	case 3:
		{
			ar << ob.scale_2d;

			int ob_m_draw_mode_2d = ob.m_draw_mode_2d;
			ar << ob_m_draw_mode_2d;

			ar << ob.disp_point_values;
			ar << ob.disp_point_values_2d;
		}
	case 2:
		{
			ar << ob.index;
		}
	case 1:
		{
			ar << ob.name;

			ar << ob.vmin;
			ar << ob.vmax;

			ar << ob.color;
			ar << ob.alpha;

			ar << ob.checked;

			ar << ob.scale;
			ar << ob.logarithmic_scale;
			ar << ob.scale_from_zero;
		}
		break;
	}
	return ar;
}
	
Archive& operator >>(Archive& ar, karotazh_list_item& ob)
{
	ar >> ob.version;
	switch (ob.version)
	{
	case 3:
		{
			ar >> ob.scale_2d;

			int ob_m_draw_mode_2d;
			ar >> ob_m_draw_mode_2d;
			ob.m_draw_mode_2d = karotazh_list_item::draw_mode_2d(ob_m_draw_mode_2d);

			ar >> ob.disp_point_values;
			ar >> ob.disp_point_values_2d;
		}
	case 2:
		{
			if (ob.version == 2)
			{
				// for version 3 
				ob.scale_2d = 1.0;
				ob.m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
				ob.disp_point_values = false;
				ob.disp_point_values_2d = false;

				ob.version = 3;
			}
			ar >> ob.index;
		}
	case 1:
		{
			if (ob.version == 1)
			{
				// for version 3 
				ob.scale_2d = 1.0;
				ob.m_draw_mode_2d = karotazh_list_item::draw_mode_2d::right;
				ob.disp_point_values = false;
				ob.disp_point_values_2d = false;

				// for version 2
				ob.index = -1;

				ob.version = 3;
			}

			ar >> ob.name;

			ar >> ob.vmin;
			ar >> ob.vmax;

			ar >> ob.color;
			ar >> ob.alpha;

			ar >> ob.checked;

			ar >> ob.scale;
			ar >> ob.logarithmic_scale;
			ar >> ob.scale_from_zero;
		}
		break;
	}

	return ar;
}


