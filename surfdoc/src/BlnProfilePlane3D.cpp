// BlnProfilePlane3D.cpp: implementation of the BlnProfilePlane3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BlnProfilePlane3D.h"
#include "SurfDoc.h"
#include ".\blnprofileplane3d.h"
#include "winsurftree.h"

//#include "atlstr.h"

extern HINSTANCE hInst;   // текущий экземпляр
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int GetVerticalPlaneFromTwoPoints(
								  CPoint2 &pt1, CPoint2 &pt2, //input
								  double &a, double &b, double &c, double &d);//output

//bool BlnProfilePlane3D::noth_vertical_coordinate_priorirty = true;



double BlnProfilePlane3D::step_x = 1000; 
double BlnProfilePlane3D::step_y = 1000; 
double BlnProfilePlane3D::step_z = 100; 

double BlnProfilePlane3D::first_x = 0;
double BlnProfilePlane3D::first_y = 0;
double BlnProfilePlane3D::first_z = 0;

double BlnProfilePlane3D::last_x = -100;
double BlnProfilePlane3D::last_y = -100;
double BlnProfilePlane3D::last_z = -100;

bool BlnProfilePlane3D::use_grid_on_plane = false;
bool BlnProfilePlane3D::to_draw_x_vertical = true;
bool BlnProfilePlane3D::to_draw_y_vertical = true;
bool BlnProfilePlane3D::to_draw_gorizontal = true;

bool ProfileIntersection::s_draw_lines_z		= true;
bool ProfileIntersection::s_draw_lines_names	= true;
bool ProfileIntersection::s_draw_profile_name	= true;

void DeleteEndZeros(wchar_t * str);


ProfileIntersection::ProfileIntersection()
{
	x = y = xv = yv = 0.0;

	z.resize(0);
	zv.resize(0);
	names.resize(0);
}
ProfileIntersection::ProfileIntersection(const ProfileIntersection &pi)
{
	this->Init(pi);
}
ProfileIntersection& ProfileIntersection::operator=(const ProfileIntersection& pi)
{
	if (this == &pi)
	{
		return *this;
	}

	this->Init(pi);

	return *this;
}
ProfileIntersection::~ProfileIntersection()
{
}

void ProfileIntersection::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	xv = zoomX * (x - x_mean);
	yv = zoomY * (y - y_mean); 

	this->max_zv = zoomZ * (max_z - z_mean);
	this->min_zv = zoomZ * (min_z - z_mean);
}

void ProfileIntersection::Drawing()
{
printf(
	   "ProfileIntersection::Drawing()\n");

	GLfloat m_LineWidth = 0.1;

	double m_vshift = 0.05;

	COLORREF line_color = RGB(0,255,0);							
	glLineWidth(m_LineWidth);
	glColor3ub (GetRValue(line_color),GetGValue(line_color),GetBValue(line_color)); 

	Line3(
		xv, 
		yv, 
		min_zv,
		xv, 
		yv,	
		max_zv);

			
	printf ("min_zv = %f max_zv = %f \n", min_zv, max_zv);


	char buff[256];
	sprintf(buff, "%s\0", this->name.c_str());
	//glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
	//====== Наносим метку 
	// move 
	glRasterPos3d(xv, yv, max_zv + m_vshift ); 
	// set up for a string-drawing display List call 
	// Display a string 
	glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
	// Draw the characters in a string 
	glCallLists(strlen(buff), GL_UNSIGNED_BYTE, buff); 

	for(size_t i = 0; i < this->zv.size(); i++)
	{
		glPointSize(5.0);
		//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));

		COLORREF color = this->colors[i];

		
		glBegin(GL_POINTS);
		glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
		//glVertex3fv((* it1).GetCRD(n1));

		glVertex3d (xv, 
					yv, 
					this->zv[i]);

		printf ("xv = %f yv = %f zv[%d] =  %f %f color = %d\n", xv, yv, i, zv[i], z[i], color);

		glEnd();
		
		//glPopName(); glPopName();
		if (true)
		{
			sprintf(buff, "%s\0", this->names[i].c_str());
			//====== Наносим метку 
			// move 
			glRasterPos3d(xv, yv, this->zv[i]); 
			// set up for a string-drawing display List call 
			// Display a string 
			glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
			// Draw the characters in a string 
			glCallLists(strlen(buff), GL_UNSIGNED_BYTE, buff); 
		}
	}
}




#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"

void ProfileIntersection::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{	
	fGL x1; fGL y1;
	fGL x2; fGL y2;

	v->PreConvertingFromWorldToScreen();

	//double m_vshift = 0.05;

	COLORREF line_color = RGB(0,255,0);							

	Color gdi_color(255, GetRValue(line_color),GetGValue(line_color),GetBValue(line_color));
	Pen      pen(gdi_color);

	double dist_to_plane;
	CPoint2 profile;


	//Convert3D_To_2D
	on->Projection(CPoint3(x,y,min_z), profile, dist_to_plane);
	v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
	//if (to_fill_circles&& !(m_vdPoints[0].flag & CPOINT3_FLAG_HIDE)) 
	//	FillCircle(&graphics, x1, y1, r, gdi_color);
		
	//Convert3D_To_2D
	on->Projection(CPoint3(x,y,max_z), profile, dist_to_plane);
	v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);
	//if (to_fill_circles && !(m_vdPoints[i1].flag & CPOINT3_FLAG_HIDE)) 
	//	FillCircle(&graphics, x2, y2, r, gdi_color);
		
	graphics.DrawLine(&pen, x1, y1, x2, y2);

			
	SolidBrush  brush(gdi_color);
	FontFamily  fontFamily(L"Times New Roman");
	Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);


	const size_t wlen = 2 + 2 * strlen(this->name.c_str());
	WCHAR * wb = new WCHAR[wlen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->name.c_str(), -1, wb, wlen );
	PointF      pointF(x2 - 0.25*font.GetHeight(&graphics) * wcslen(wb), y2 - 1.5 * font.GetHeight(&graphics));                                    
	graphics.DrawString(wb, -1, &font, pointF, &brush);
	delete wb;

	double r = 5;
	for(size_t i = 0; i < this->zv.size(); i++)
	{
		COLORREF color = this->colors[i];
		Color gdicolor(255, GetRValue(color),GetGValue(color),GetBValue(color));


		float _x,_y;
		//Convert3D_To_2D
		on->Projection(CPoint3(x,y,this->z[i]), profile, dist_to_plane);
		v->ConvertingFromWorldToScreen(profile.x, profile.y, _x, _y);
		FillCircle(&graphics, _x, _y, r, gdicolor);

		if (true)
		{
			SolidBrush  brush(gdicolor);
			FontFamily  fontFamily(L"Times New Roman");
			Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);

			const size_t wlen = 2 + 2 * strlen(this->names[i].c_str());
			WCHAR * wb = new WCHAR[wlen];
			MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, this->names[i].c_str(), -1, wb, wlen );
			PointF      pointF(_x + 0.5*font.GetHeight(&graphics), _y/* - font.GetHeight(&graphics)/2*/);                                    
			graphics.DrawString(wb, -1, &font, pointF, &brush);
			delete wb;
		}
	}
}

BlnProfilePlane3D::BlnProfilePlane3D()
{
	this->m_bChecked = false;
	OnCreate();
}

void BlnProfilePlane3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::bln_profile_plane3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	m_vdplaneBlnProfiles.OnCreate(0);
	m_vvplaneBlnProfiles.OnCreate(0);

	this->m_intersections.OnCreate();

	this->m_toDisableDepthTest = true;
}

BlnProfilePlane3D::BlnProfilePlane3D(const BlnProfilePlane3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
BlnProfilePlane3D& BlnProfilePlane3D::operator=(const BlnProfilePlane3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

BlnProfilePlane3D::~BlnProfilePlane3D()
{

}
void BlnProfilePlane3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
}
void BlnProfilePlane3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
}


void BlnProfilePlane3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_intersections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_intersections.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_intersections.IncrementCurrentMsg());
	}
	if (m_vdplaneBlnProfiles.SetCurrentMsgOnFirst() 
		&& m_vvplaneBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = m_vdplaneBlnProfiles.GetCurrentMsgLen();
			CPoint3 *ptv, *ptd;
			ptd = m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			ptv = m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			for (int ipoint = 0; ipoint < len; ipoint++)
			{							
				ptv[ipoint].bVisible = ptd[ipoint].bVisible;

				ptv[ipoint].z = 
					zoomZ * (ptd[ipoint].z - z_mean);
				ptv[ipoint].y = 
					zoomY * (ptd[ipoint].y - y_mean);
				ptv[ipoint].x = 
					zoomX * (ptd[ipoint].x - x_mean);
			}
		}
		while(m_vdplaneBlnProfiles.IncrementCurrentMsg()
			&& m_vvplaneBlnProfiles.IncrementCurrentMsg());
	}
}
bool BlnProfilePlane3D::UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max)
{
	double dist_to_plane;		
	CPoint2 profile;
	if (m_vdplaneBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = m_vdplaneBlnProfiles.GetCurrentMsgLen();
			CPoint3 *ptd;
			ptd = m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			for (int ipoint = 0; ipoint < len; ipoint++)
			{
				on->Projection(ptd[ipoint], profile, dist_to_plane);
				if (start)
				{
					profile_max.x = profile_min.x = profile.x;
					profile_max.y = profile_min.y = profile.y;
					start = false;
				}
				else
				{
					if (profile_min.x > profile.x) profile_min.x = profile.x;
					if (profile_max.x < profile.x) profile_max.x = profile.x;

					if (profile_min.y > profile.y) profile_min.y = profile.y;
					if (profile_max.y < profile.y) profile_max.y = profile.y;
				}
			}
		}
		while(m_vdplaneBlnProfiles.IncrementCurrentMsg());
	}



	return !start;
}


extern void ProfileAttaching(double xProfile, int& ipoint, int lenMapAttach, ProfileAttachPoint *ptpa, double& xMap, double& yMap );
extern void ProfileAttaching(double xProfile, int& ipoint, vector<ProfileAttachPoint> & ptpa, double& xMap, double& yMap );

void BlnProfilePlane3D::Build(CPoint2 pt2min, CPoint2 pt2max, vector<ProfileAttachPoint> & ptpa)
{
	printf(" BlnProfilePlane3D::Build\n");
	size_t lenMapAttach = ptpa.size();
	int ipoint = 0;
	// теперь формируем трёхмерное изображение плоскости разреза
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	CPoint3 pt3max, pt3min;
	ProfileAttaching(pt2max.x, ipoint, ptpa, pt3max.x, pt3max.y );
	pt3max.z = pt2max.y;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ProfileAttaching(pt2min.x, ipoint, ptpa, pt3min.x, pt3min.y );
	pt3min.z = pt2min.y;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	size_t planelen = (lenMapAttach+2)*2;
	CPoint3 * pt3plane = new CPoint3[planelen];
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[0].bVisible	= true;
	pt3plane[0].x			= pt3min.x;
	pt3plane[0].y			= pt3min.y;
	pt3plane[0].z			= pt3min.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[1].bVisible	= true;
	pt3plane[1].x			= pt3min.x;
	pt3plane[1].y			= pt3min.y;
	pt3plane[1].z			= pt3max.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	for (size_t ima = 0; ima < lenMapAttach; ima++)
	{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		pt3plane[2+ima*2].bVisible	= true;
		pt3plane[2+ima*2].x			= ptpa[ima].xMap;
		pt3plane[2+ima*2].y			= ptpa[ima].yMap;
		pt3plane[2+ima*2].z			= pt3min.z;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		pt3plane[3+ima*2].bVisible	= true;
		pt3plane[3+ima*2].x			= ptpa[ima].xMap;
		pt3plane[3+ima*2].y			= ptpa[ima].yMap;
		pt3plane[3+ima*2].z			= pt3max.z;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[2+lenMapAttach*2].bVisible	= true;
	pt3plane[2+lenMapAttach*2].x			= pt3max.x;
	pt3plane[2+lenMapAttach*2].y			= pt3max.y;
	pt3plane[2+lenMapAttach*2].z			= pt3min.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[3+lenMapAttach*2].bVisible	= true;
	pt3plane[3+lenMapAttach*2].x			= pt3max.x;
	pt3plane[3+lenMapAttach*2].y			= pt3max.y;
	pt3plane[3+lenMapAttach*2].z			= pt3max.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vdplaneBlnProfiles.AddMsg(pt3plane, planelen);
	m_vvplaneBlnProfiles.AddMsg(pt3plane, planelen);
	if (pt3plane) delete[] pt3plane;
}

void BlnProfilePlane3D::Build(CPoint2 pt2min, CPoint2 pt2max, int lenMapAttach, ProfileAttachPoint * ptpa)
{
	printf(" BlnProfilePlane3D::Build\n");
	int ipoint = 0;
	// теперь формируем трёхмерное изображение плоскости разреза
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	CPoint3 pt3max, pt3min;
	ProfileAttaching(pt2max.x, ipoint, lenMapAttach, ptpa, pt3max.x, pt3max.y );
	pt3max.z = pt2max.y;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	ProfileAttaching(pt2min.x, ipoint, lenMapAttach, ptpa, pt3min.x, pt3min.y );
	pt3min.z = pt2min.y;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	int planelen = (lenMapAttach+2)*2;
	CPoint3 * pt3plane = new CPoint3[planelen];
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[0].bVisible	= true;
	pt3plane[0].x			= pt3min.x;
	pt3plane[0].y			= pt3min.y;
	pt3plane[0].z			= pt3min.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[1].bVisible	= true;
	pt3plane[1].x			= pt3min.x;
	pt3plane[1].y			= pt3min.y;
	pt3plane[1].z			= pt3max.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	for (int ima = 0; ima < lenMapAttach; ima++)
	{
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		pt3plane[2+ima*2].bVisible	= true;
		pt3plane[2+ima*2].x			= ptpa[ima].xMap;
		pt3plane[2+ima*2].y			= ptpa[ima].yMap;
		pt3plane[2+ima*2].z			= pt3min.z;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		pt3plane[3+ima*2].bVisible	= true;
		pt3plane[3+ima*2].x			= ptpa[ima].xMap;
		pt3plane[3+ima*2].y			= ptpa[ima].yMap;
		pt3plane[3+ima*2].z			= pt3max.z;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[2+lenMapAttach*2].bVisible	= true;
	pt3plane[2+lenMapAttach*2].x			= pt3max.x;
	pt3plane[2+lenMapAttach*2].y			= pt3max.y;
	pt3plane[2+lenMapAttach*2].z			= pt3min.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	pt3plane[3+lenMapAttach*2].bVisible	= true;
	pt3plane[3+lenMapAttach*2].x			= pt3max.x;
	pt3plane[3+lenMapAttach*2].y			= pt3max.y;
	pt3plane[3+lenMapAttach*2].z			= pt3max.z;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	m_vdplaneBlnProfiles.AddMsg(pt3plane, planelen);
	m_vvplaneBlnProfiles.AddMsg(pt3plane, planelen);
	if (pt3plane) delete[] pt3plane;
}

HTREEITEM BlnProfilePlane3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	sprintf(szItemText, "plane");
	Object * pObject = dynamic_cast<Object *> (this);
	pObject->m_bChecked = false;
	return AddItemToTree(hwndTV, szItemText, pObject, h1);
}

extern void getNorm(double v1[3], double v2[3], double out[3]);
void BlnProfilePlane3D::Draw()
{
	m_nglListNumber = DrawListArray::glNewList();
	Drawing();
	glEndList();
}

void BlnProfilePlane3D::ReDraw(void)
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);

	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
		::glNewList(m_nglListNumber, GL_COMPILE);
	}
	else
		m_nglListNumber = DrawListArray::glNewList();

	Drawing();
	glEndList();
}
void BlnProfilePlane3D::Drawing()
{
//printf(" BlnProfilePlane3D::Draw(m_pSurfDoc = %x)\n", m_pSurfDoc);
	if (this->m_intersections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_intersections.GetCurrentMsg().Drawing();
		}
		while(this->m_intersections.IncrementCurrentMsg());
	}

	if (m_pSurfDoc)
	{
	//printf(" BlnProfilePlane3D::Drawing\n");
		//====== Настройка OpenGL на использование массивов
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		if (m_pSurfDoc->m_bFlatShading)
			glShadeModel (GL_FLAT);
		else
			glShadeModel (GL_SMOOTH);
//printf(" BlnProfilePlane3D::Drawing msgSize = %d\n",  this->m_vvplaneBlnProfiles.msgSize());

		if ( 
			this->m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
			&&
			this->m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
			)
		{
			int len = this->m_vvplaneBlnProfiles.GetCurrentMsgLen();

			CPoint3 *ptv;
			CPoint3 *ptd;
			ptv = this->m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			ptd = this->m_vdplaneBlnProfiles.GetCurrentMsgPtr();

			//====== Захват памяти под динамические массивы
			VERT *Vert = new VERT[len];
			QUAD *Quad = new QUAD[(len/2)-1];
			int q;
			do
			{
#define SHOW_PRIVJAZKI 1
#if SHOW_PRIVJAZKI
				for (int i = 0; i < len; i++)
				{
					glColor3ub (255,0,0); 

					GLUquadricObj* pSphere = gluNewQuadric();
					gluQuadricDrawStyle(pSphere, GLU_FILL);
					glPushMatrix();//перейдём к новым координатам, сохранив старые
					
					glTranslated(
						ptv[i].x, 
						ptv[i].y, 
						ptv[i].z
						);

					gluSphere(pSphere, 
						m_pSurfDoc->m_sphere_radius, 
						m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
						m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
						) ;//рисуем сферу 
					glPopMatrix(); //возвращаемся к старым координатам 
					gluDeleteQuadric(pSphere);	
				}
#endif				//=============================================
				for (int i = 0; i + 2 < len - 1; i+=2)
				{							
					//ptv[i].bVisible;
					//ptv[i].z;
					//ptv[i].y;
					//ptv[i].x;
					//===== Вычисление вектора нормали
					double d1[3], d2[3], norm[3];
					d1[0] = ptv[i+1].x-ptv[i].x;
					d1[1] = ptv[i+1].y-ptv[i].y;
					d1[2] = ptv[i+1].z-ptv[i].z;

					d2[0] = ptv[i].x-ptv[i+2].x;
					d2[1] = ptv[i].y-ptv[i+2].y;
					d2[2] = ptv[i].z-ptv[i+2].z;

					getNorm(d1,d2,norm);
					CPoint3 n = CPoint3(norm[0],norm[1],norm[2]);
						
					COLORREF  planeColor = RGBA (255,255,255, (GLubyte)m_pSurfDoc->m_alpha_plane); 
					//COLORREF  planeColor = RGBA (255,255,255, 50); 

					Vert[i].c	= planeColor;
					Vert[i+1].c = planeColor;

					//====== Задание вектора нормали
					Vert[i].n	= n;
					Vert[i+1].n = n;
					Vert[i].v	= ptv[i];
					Vert[i+1].v = ptv[i+1];

					if( i == len - 4)
					{
						Vert[i+2].n	= n;
						Vert[i+3].n = n;
						Vert[i+2].v = ptv[i+2];
						Vert[i+3].v = ptv[i+3];
						Vert[i+2].c	= planeColor;
						Vert[i+3].c = planeColor;
					}

					q = i/2;
					Quad[q].i1 = i;
					Quad[q].i2 = i+1;
					Quad[q].i3 = i+3;
					Quad[q].i4 = i+2;

					//построение координатных линий внутри плоскости
					if (BlnProfilePlane3D::use_grid_on_plane)
					{
						/*printf("i   = %d [%f %f %f]\n", i  , ptd[i  ].x,ptd[i  ].y,ptd[i  ].z);
						printf("i+1 = %d [%f %f %f]\n", i+1, ptd[i+1].x,ptd[i+1].y,ptd[i+1].z);
						printf("i+2 = %d [%f %f %f]\n", i+2, ptd[i+2].x,ptd[i+2].y,ptd[i+2].z);
						printf("i+3 = %d [%f %f %f]\n", i+3, ptd[i+3].x,ptd[i+3].y,ptd[i+3].z);
						printf("\n");*/

						// получим сперва уравнение плоскости в пространстве
						double A,B,C,D;
						CPoint2 p1,p2;
						p1.x = ptd[i].x;   p1.y = ptd[i].y;
						p2.x = ptd[i+2].x; p2.y = ptd[i+2].y;
						if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
						{
							double 
								min_x = min(ptd[i].x,ptd[i+2].x),
								max_x = max(ptd[i].x,ptd[i+2].x),

								min_y = min(ptd[i].y,ptd[i+2].y),
								max_y = max(ptd[i].y,ptd[i+2].y),

								min_z = min(ptd[i].z,ptd[i+1].z),
								max_z = max(ptd[i].z,ptd[i+1].z);

							double 
								min_xv = m_pSurfDoc->m_zoomX * (min_x - m_pSurfDoc->m_xd_zoom_center), 
								min_yv = m_pSurfDoc->m_zoomY * (min_y - m_pSurfDoc->m_yd_zoom_center), 
								min_zv = m_pSurfDoc->m_zoomZ * (min_z - m_pSurfDoc->m_zd_zoom_center);
							double 
								max_xv = m_pSurfDoc->m_zoomX * (max_x - m_pSurfDoc->m_xd_zoom_center), 
								max_yv = m_pSurfDoc->m_zoomY * (max_y - m_pSurfDoc->m_yd_zoom_center), 
								max_zv = m_pSurfDoc->m_zoomZ * (max_z - m_pSurfDoc->m_zd_zoom_center);

							double start_x, start_y, start_z; 
							double finish_x, finish_y, finish_z; 

							start_x = step_x*ceil((min_x-first_x)/step_x) + first_x;
							start_y = step_y*ceil((min_y-first_y)/step_y) + first_y;
							start_z = step_z*ceil((min_z-first_z)/step_z) + first_z;

							finish_x = min(max_x, last_x);
							finish_y = min(max_y, last_y);
							finish_z = min(max_z, last_z);

							//start_z = step_z*floor(max_z/step_z) -*/ first_z;

							GLfloat m_LineWidth = 0.1;

							double m_vshift = 0.05;

							COLORREF line_color = RGB(0,0,255);							
							glLineWidth(m_LineWidth);
							glColor3ub (GetRValue(line_color),GetGValue(line_color),GetBValue(line_color)); 
							
							int gor_lines = (finish_z - start_z)/step_z;
							if (gor_lines <= 500 && to_draw_gorizontal)// бывает зависает отрисовка в этом цикле если большой разброс по вертикали
							{
								// проводим горизонтальные линий
								for (double zd = start_z; zd <= finish_z; zd += step_z)
								{
									//printf("zd = %f\n", zd);
									// ищем линию пересечения нашей плоскости 
									//  A*x + B*y + C*z + D = 0
									// с плоскостью 
									//  z = zd
									// решаем уравнение
									//  A*xd + B*y + C*z + D = 0
									// в точках
									//  x = p1.x и x = p2.x
									//  y = p1.y и y = p2.y
									double zv = m_pSurfDoc->m_zoomZ * (zd  - m_pSurfDoc->m_zd_zoom_center);


									double xv1 = m_pSurfDoc->m_zoomX * (p1.x  - m_pSurfDoc->m_xd_zoom_center);
									double xv2 = m_pSurfDoc->m_zoomX * (p2.x  - m_pSurfDoc->m_xd_zoom_center);
									double yv1 = m_pSurfDoc->m_zoomY * (p1.y - m_pSurfDoc->m_yd_zoom_center);
									double yv2 = m_pSurfDoc->m_zoomY * (p2.y - m_pSurfDoc->m_yd_zoom_center);
									Line3(
										xv1, 
										yv1, 
										zv,
										xv2, 
										yv2,	
										zv);

									char buff[256];
									sprintf(buff, "%f\0", zd);
									DeleteEndZeros(buff);
									//glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
									//====== Наносим метку 
									// move 
									glRasterPos3d(xv1, 
										yv1, 
										zv - m_vshift ); 
									// set up for a string-drawing display List call 
									// Display a string 
									glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
									// Draw the characters in a string 
									glCallLists(strlen(buff), GL_UNSIGNED_BYTE, buff); 
								}

							}

							// проводим вертикальные линии

#if 0
							bool y_vertical_drawing = start_y < finish_y;
							bool x_vertical_drawing = start_x < finish_x;

							bool to_draw_x_vertical;
							bool to_draw_y_vertical;
							
							if (x_vertical_drawing && y_vertical_drawing)
							{
								if (noth_vertical_coordinate_priorirty)
								{
									to_draw_x_vertical = false;
									to_draw_y_vertical = true;
								}
								else
								{
									to_draw_x_vertical = true;
									to_draw_y_vertical = false;
								}
							}
							else
							{
								to_draw_x_vertical = x_vertical_drawing;
								to_draw_y_vertical = y_vertical_drawing;
							}
#endif
							if (to_draw_y_vertical)
							{
								for (double yd = start_y; yd <= finish_y; yd += step_y)
								{
									//printf("yd = %f\n", yd);
									// ищем линию пересечения нашей плоскости 
									//  A*x + B*y + C*z + D = 0
									// с плоскостью 
									//  y = yd
									// решаем уравнение
									//  A*xd + B*y + C*z + D = 0
									// в точках
									//  z = min_z и z = max_z
									double xd1 = - (B*yd + C*min_z + D)/A;
									double xd2 = - (B*yd + C*max_z + D)/A;
									double yv   = m_pSurfDoc->m_zoomY * (yd   - m_pSurfDoc->m_yd_zoom_center);
									double xv1  = m_pSurfDoc->m_zoomX * (xd1  - m_pSurfDoc->m_xd_zoom_center);
									double xv2  = m_pSurfDoc->m_zoomX * (xd2  - m_pSurfDoc->m_xd_zoom_center);
									Line3(
										xv1, 
										yv, 
										min_zv,
										xv2, 
										yv,	
										max_zv);

									char buff[256];
									sprintf(buff, "Y=%f\0", yd);
									DeleteEndZeros(buff);
									//glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
									//====== Наносим метку 
									// move 
									glRasterPos3d(xv1, yv, min_zv - m_vshift ); 
									// set up for a string-drawing display List call 
									// Display a string 
									glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
									// Draw the characters in a string 
									glCallLists(strlen(buff), GL_UNSIGNED_BYTE, buff); 
								}
							}
							

							if (to_draw_x_vertical)
							{
								for (double xd = start_x; xd < finish_x; xd += step_x)
								{
									//printf("xd = %f\n", xd);
									// ищем линию пересечения нашей плоскости 
									//  A*x + B*y + C*z + D = 0
									// с плоскостью 
									//  x = xd
									// решаем уравнение
									//  A*xd + B*y + C*z + D = 0
									// в точках
									//  z = min_z и z = max_z
									double yd1 = - (A*xd + C*min_z + D)/B;
									double yd2 = - (A*xd + C*max_z + D)/B;
									double xv  = m_pSurfDoc->m_zoomX * (xd  - m_pSurfDoc->m_xd_zoom_center);
									double yv1 = m_pSurfDoc->m_zoomY * (yd1 - m_pSurfDoc->m_yd_zoom_center);
									double yv2 = m_pSurfDoc->m_zoomY * (yd2 - m_pSurfDoc->m_yd_zoom_center);
									Line3(
										xv, 
										yv1, 
										min_zv,
										xv, 
										yv2,	
										max_zv);

									char buff[256];
									sprintf(buff, "X=%f\0", xd);
									DeleteEndZeros(buff);
									//glColor3ub (GetRValue(color),GetGValue(color),GetBValue(color)); 
									//====== Наносим метку 
									// move 
									glRasterPos3d(xv, yv1, min_zv - m_vshift ); 
									// set up for a string-drawing display List call 
									// Display a string 
									glListBase(FIRST_FONT_LIST_BITMAPS); // Indicates the start of display lists for the glyphs 
									// Draw the characters in a string 
									glCallLists(strlen(buff), GL_UNSIGNED_BYTE, buff); 
								}
							}
						}							
					}
				}
			}
			while( 
				this->m_vvplaneBlnProfiles.IncrementCurrentMsg()
				&&
				this->m_vdplaneBlnProfiles.IncrementCurrentMsg()
				);
			//====== Задание адресов трех массивов (вершин,
			//====== нормалей и цветов),
			//====== а также шага перемещения по ним
			glVertexPointer(3, GL_PRECISION, sizeof(VERT), &Vert->v);
			glNormalPointer(GL_PRECISION, sizeof(VERT), &Vert->n);
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT),
															&Vert->c);
			//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
			q = len/2-1;
			//====== Формирование списка рисующих команд
				glDrawElements(GL_QUADS, 4*q/*nx*ny*4*/,
									GL_UNSIGNED_INT, Quad);
			//glEndList();
			
			//== Освобождение памяти, так как список сформирован
			delete [] Vert;
			delete [] Quad;
		}
	}

}
#define UNICODE
void BlnProfilePlane3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{	
	if (this->m_intersections.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_intersections.GetCurrentMsg().DrawGDIplus(select_buffer, graphics, v,on);
		}
		while(this->m_intersections.IncrementCurrentMsg());
	}

	v->PreConvertingFromWorldToScreen();
	fGL r = v->lines_points_radius;

	if (m_pSurfDoc)
	{
		if ( 
			this->m_vvplaneBlnProfiles.SetCurrentMsgOnFirst() 
			&&
			this->m_vdplaneBlnProfiles.SetCurrentMsgOnFirst()
			)
		{
			int len = this->m_vvplaneBlnProfiles.GetCurrentMsgLen();

			//CPoint3 *ptv;
			CPoint3 *ptd;
			//ptv = this->m_vvplaneBlnProfiles.GetCurrentMsgPtr();
			ptd = this->m_vdplaneBlnProfiles.GetCurrentMsgPtr();

			//====== Захват памяти под динамические массивы
			//VERT *Vert = new VERT[len];
			//QUAD *Quad = new QUAD[(len/2)-1];
			int q;
			do
			{
#if SHOW_PRIVJAZKI
				double dist_to_plane;
				CPoint2 profile;
				Color gdi_priv_color(255, 255,0,0);
				float x,y;
				for (int i = 0; i < len; i++)
				{
					//Convert3D_To_2D
					on->Projection(ptd[i], profile, dist_to_plane);
					v->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);
					FillCircle(&graphics, x, y, r, gdi_priv_color);
				}
#endif				//=============================================
				//for (int i = 0; i + 2 < len - 1; i+=2)
				if (len > 0)
				{							

					
					//построение координатных линий внутри плоскости
					if (BlnProfilePlane3D::use_grid_on_plane)
					{

						//glLineWidth(m_LineWidth);
						//Color gdi_line_color((BYTE)m_alpha_plane, 0,0,255);
						//Color gdi_line_color((GLubyte)m_alpha_plane, 0,0,255);

						BYTE a = m_pSurfDoc->m_alpha_plane;
						
						Color gdi_line_color(a, 0,0,255);
						Pen      line_pen(gdi_line_color);

						   
						SolidBrush  brush(Color(255, 0, 0, 255));
						FontFamily  fontFamily(L"Times New Roman");
						Font        font(&fontFamily, 10, FontStyleRegular, UnitPixel);
						

						float x1,y1;
						float x2,y2;

						// проводим горизонтальные линий
						if (to_draw_gorizontal)
						{
							double 
								min_x = min(ptd[0].x,ptd[len-1].x),
								max_x = max(ptd[0].x,ptd[len-1].x),

								min_y = min(ptd[0].y,ptd[len-1].y),
								max_y = max(ptd[0].y,ptd[len-1].y),

								min_z = min(ptd[0].z,ptd[len-1].z),
								max_z = max(ptd[0].z,ptd[len-1].z);

							double start_x, start_y, start_z; 
							double finish_x, finish_y, finish_z; 

							start_x = step_x*ceil((min_x-first_x)/step_x) + first_x;
							start_y = step_y*ceil((min_y-first_y)/step_y) + first_y;
							start_z = step_z*ceil((min_z-first_z)/step_z) + first_z;

							finish_x = min(max_x, last_x);
							finish_y = min(max_y, last_y);
							finish_z = min(max_z, last_z);

							GLfloat m_LineWidth = 0.1;

							double m_vshift = 0.05;

							int gor_lines = (finish_z - start_z)/step_z;
							if (gor_lines <= 500)// бывает зависает отрисовка в этом цикле если большой разброс по вертикали
							{
								// проводим горизонтальные линий
								for (double zd = start_z; zd <= finish_z; zd += step_z)
								{
									//printf("zd = %f\n", zd);
									// ищем линию пересечения нашей плоскости 
									//  A*x + B*y + C*z + D = 0
									// с плоскостью 
									//  z = zd
									// решаем уравнение
									//  A*xd + B*y + C*z + D = 0
									// в точках
									//  x = p1.x и x = p2.x
									//  y = p1.y и y = p2.y

									//Convert3D_To_2D
									CPoint3 pt3;
									//pt3 = ptd[i]; pt3.z = zd;
									pt3 = ptd[0]; pt3.z = zd;
									on->Projection(pt3, profile, dist_to_plane);
									v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
									//pt3 = ptd[i+2]; pt3.z = zd;
									pt3 = ptd[len-1]; pt3.z = zd;
									on->Projection(pt3, profile, dist_to_plane);
									v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);
									graphics.DrawLine(&line_pen, x1, y1, x2, y2);								

									char buff[256];
									sprintf(buff, "%f\0", zd);
									DeleteEndZeros(buff);

									wchar_t str[256];
									wsprintfW(str, L"%S\0", buff);

									PointF      pointF(x1 - 0.5*font.GetHeight(&graphics) * wcslen(str), y1 - font.GetHeight(&graphics)/2);                                    
									graphics.DrawString(str, -1, &font, pointF, &brush);

								}
							}
						}							

						for (int i = 0; i + 2 < len - 1; i+=2)
						{
							// получим сперва уравнение плоскости в пространстве
							double A,B,C,D;
							CPoint2 p1,p2;
							p1.x = ptd[i].x;   p1.y = ptd[i].y;
							p2.x = ptd[i+2].x; p2.y = ptd[i+2].y;
							if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
							{
								double 
									min_x = min(ptd[i].x,ptd[i+2].x),
									max_x = max(ptd[i].x,ptd[i+2].x),

									min_y = min(ptd[i].y,ptd[i+2].y),
									max_y = max(ptd[i].y,ptd[i+2].y),

									min_z = min(ptd[i].z,ptd[i+1].z),
									max_z = max(ptd[i].z,ptd[i+1].z);

								//printf("min_x = %f max_x = %f\n", min_x, max_x);
								//printf("min_y = %f max_y = %f\n", min_y, max_y);
								//printf("min_z = %f max_z = %f\n", min_z, max_z);


								double start_x, start_y, start_z; 
								double finish_x, finish_y, finish_z; 

								start_x = step_x*ceil((min_x-first_x)/step_x) + first_x;
								start_y = step_y*ceil((min_y-first_y)/step_y) + first_y;
								start_z = step_z*ceil((min_z-first_z)/step_z) + first_z;

								finish_x = min(max_x, last_x);
								finish_y = min(max_y, last_y);
								finish_z = min(max_z, last_z);

								GLfloat m_LineWidth = 0.1;

								double m_vshift = 0.05;

								// проводим вертикальные линии
#if 0
								bool y_vertical_drawing = start_y < finish_y;
								bool x_vertical_drawing = start_x < finish_x;

								bool to_draw_x_vertical;
								bool to_draw_y_vertical;
								
								if (x_vertical_drawing && y_vertical_drawing)
								{
									if (noth_vertical_coordinate_priorirty)
									{
										to_draw_x_vertical = false;
										to_draw_y_vertical = true;
									}
									else
									{
										to_draw_x_vertical = true;
										to_draw_y_vertical = false;
									}
								}
								else
								{
									to_draw_x_vertical = x_vertical_drawing;
									to_draw_y_vertical = y_vertical_drawing;
								}
#endif
								if (to_draw_y_vertical)
								{
									//printf("to_draw_y_vertical\n");
									for (double yd = start_y; yd <= finish_y; yd += step_y)
									{
										//printf("yd = %f\n", yd);
										// ищем линию пересечения нашей плоскости 
										//  A*x + B*y + C*z + D = 0
										// с плоскостью 
										//  y = yd
										// решаем уравнение
										//  A*xd + B*y + C*z + D = 0
										// в точках
										//  z = min_z и z = max_z
										double xd1 = - (B*yd + C*min_z + D)/A;
										double xd2 = - (B*yd + C*max_z + D)/A;
										/*double yv   = m_pSurfDoc->m_zoomY * (yd   - m_pSurfDoc->m_yd_zoom_center);
										double xv1  = m_pSurfDoc->m_zoomX * (xd1  - m_pSurfDoc->m_xd_zoom_center);
										double xv2  = m_pSurfDoc->m_zoomX * (xd2  - m_pSurfDoc->m_xd_zoom_center);
										Line3(
											xv1, 
											yv, 
											min_zv,
											xv2, 
											yv,	
											max_zv);*/

										//Convert3D_To_2D
										CPoint3 pt3;
										pt3.x = xd1;
										pt3.y = yd;
										pt3.z = min_z;
										on->Projection(pt3, profile, dist_to_plane);
										v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
										pt3.x = xd2;
										pt3.y = yd;
										pt3.z = max_z;
										on->Projection(pt3, profile, dist_to_plane);
										v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);
										graphics.DrawLine(&line_pen, x1, y1, x2, y2);


										char buff[256];
										sprintf(buff, "Y=%f\0", yd);
										DeleteEndZeros(buff);

										wchar_t str[256];
										wsprintfW(str, L"%S\0", buff);

										PointF      pointF(x1 - 0.25*font.GetHeight(&graphics) * wcslen(str), y1 + font.GetHeight(&graphics)/2);                                    
										graphics.DrawString(str, -1, &font, pointF, &brush);
									}
								}
								

								if (to_draw_x_vertical)
								{
									//printf("to_draw_x_vertical\n");
									for (double xd = start_x; xd <= finish_x; xd += step_x)
									{
										//printf("xd = %f\n", xd);
										// ищем линию пересечения нашей плоскости 
										//  A*x + B*y + C*z + D = 0
										// с плоскостью 
										//  x = xd
										// решаем уравнение
										//  A*xd + B*y + C*z + D = 0
										// в точках
										//  z = min_z и z = max_z
										double yd1 = - (A*xd + C*min_z + D)/B;
										double yd2 = - (A*xd + C*max_z + D)/B;
										/*double xv  = m_pSurfDoc->m_zoomX * (xd  - m_pSurfDoc->m_xd_zoom_center);
										double yv1 = m_pSurfDoc->m_zoomY * (yd1 - m_pSurfDoc->m_yd_zoom_center);
										double yv2 = m_pSurfDoc->m_zoomY * (yd2 - m_pSurfDoc->m_yd_zoom_center);
										Line3(
											xv, 
											yv1, 
											min_zv,
											xv, 
											yv2,	
											max_zv);*/

										//Convert3D_To_2D
										CPoint3 pt3;
										pt3.x = xd;
										pt3.y = yd1;
										pt3.z = min_z;
										on->Projection(pt3, profile, dist_to_plane);
										v->ConvertingFromWorldToScreen(profile.x, profile.y, x1, y1);
										pt3.x = xd;
										pt3.y = yd2;
										pt3.z = max_z;
										on->Projection(pt3, profile, dist_to_plane);
										v->ConvertingFromWorldToScreen(profile.x, profile.y, x2, y2);
										graphics.DrawLine(&line_pen, x1, y1, x2, y2);


										char buff[256];
										sprintf(buff, "X=%f\0", xd);
										DeleteEndZeros(buff);

										wchar_t str[256];
										wsprintfW(str, L"%S\0", buff);

										PointF      pointF(x1 - 0.25*font.GetHeight(&graphics) * wcslen(str), y1 + font.GetHeight(&graphics)/2);                                    
										graphics.DrawString(str, -1, &font, pointF, &brush);
									}
								}
							}							
						}
					}
				}
			}
			while( 
				this->m_vvplaneBlnProfiles.IncrementCurrentMsg()
				&&
				this->m_vdplaneBlnProfiles.IncrementCurrentMsg()
				);

		}
	}
}


void BlnProfilePlane3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
void BlnProfilePlane3D::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
}



size_t BlnProfilePlane3D::GetPointsNumber()
{
	return this->m_vdplaneBlnProfiles.msgSize();
}

int BlnProfilePlane3D::GetAlphaSliderNum(HWND hwnd, UINT& nID)
{
	//====== GetDlgCtrlID по известному hwnd определяет
	//====== и возвращает идентификатор элемента управления
	switch (GetDlgCtrlID(hwnd))
	{
	//====== Выясняем идентификатор окна справа
	case IDC_SLIDER_SURF_ALPHA_PLANE:
		nID = IDC_EDIT_SURF_ALPHA_PLANE;
		return 0;
	}
	return 0;
}

BOOL CALLBACK BlnProfilePlane3D::DlgProcSurfAlpha( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static BlnProfilePlane3D * me;
	static int m_Pos[11]; 			// Массив позиций ползунков
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	


			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (BlnProfilePlane3D *)lPage->lParam;

			char str[1023];
			sprintf(str,"%d",me->m_alpha);
			SetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA_PLANE, str);

			SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);			
		}
		break;
	case WM_HSCROLL :
		{
			if (lParam)
			{
				int nPos = HIWORD (wParam);
				//====== Windows-описатель окна активного ползунка
				HWND hwnd = reinterpret_cast<HWND> (lParam);

				UINT nID;

				//=== Определяем индекс в массиве позиций ползунков
				int num = GetAlphaSliderNum(hwnd, nID);
				int delta, newPos;

				//====== Анализируем код события
				switch ( LOWORD( wParam ) )
				{
				case SB_THUMBTRACK:
				case SB_THUMBPOSITION:		// Управление мышью
					m_Pos[num] = nPos;
					break;
				case SB_LEFT:					// Клавиша Home
					delta = -255;
					goto New_Pos;
				case SB_RIGHT:				// Клавиша End
					delta = +255;
					goto New_Pos;
				case SB_LINELEFT:			// Клавиша <-
					delta = -1;
					goto New_Pos;
				case SB_LINERIGHT:			// Клавиша ->
					delta = +1;
					goto New_Pos;
				case SB_PAGELEFT:			// Клавиша PgUp
					delta = -20;
					goto New_Pos;
				case SB_PAGERIGHT:			// Клавиша PgDn
					delta = +20;
					goto New_Pos;

				New_Pos:						// Общая ветвь
					//====== Устанавливаем новое значение регулятора
					newPos = m_Pos[num] + delta;
					//====== Ограничения
					m_Pos[num] = newPos<0 ? 0 : newPos>255 ? 255 : newPos;
					break;
				case SB_ENDSCROLL:
				default:
					return (TRUE);
				}

				//====== Синхронизируем параметр lp и
				//====== устанавливаем его в положение nPos
				switch (num)
				{
				case 0:
					me->m_alpha = m_Pos[num];
					break;
				}


				//====== Синхронизируем текстовый аналог позиции
				char s[1024];
				sprintf (s,"%d",me->m_alpha);
				sprintf (s,"%d",m_Pos[num]);
				SetDlgItemText(hDlg, nID, (LPCTSTR)s);

				// init of zoomCoefZ_XY
				//me->m_pSurfDoc->ZoomView();
				me->m_pSurfDoc->Draw();
				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
				
			}
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_INIT_SURF_ALPHA_SLIDER :
			{
				//=== Добываем Windows-описатель окна ползунка
				HWND hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				hwnd = GetDlgItem(hDlg, IDC_SLIDER_SURF_ALPHA_PLANE);

				SendMessage(    // returns LRESULT in lResult
				(HWND) hwnd,       // handle to destination control
				(UINT) TBM_SETRANGE,    // message ID
				(WPARAM) true,          // = (WPARAM) (BOOL) fRedraw
				(LPARAM) MAKELONG (0, 255)              // = (LPARAM) MAKELONG (lMinimum, lMaximum)
				);
				//====== Проход по всем регулировкам
				//for (int i=0; i<2; i++)
					//====== Заполняем транспортный массив pPos
					m_Pos[0] = me->m_alpha;

				//====== Массив идентификаторов ползунков
				UINT IDs[] = 
				{
					IDC_SLIDER_SURF_ALPHA_PLANE,
				};

				//====== Цикл прохода по всем регуляторам
				for (int i=0; i<sizeof(IDs)/sizeof(IDs[0]); i++)
				{
					//=== Добываем Windows-описатель окна ползунка
					HWND hwnd = GetDlgItem(hDlg, IDs[i]);
					UINT nID;

					//====== Определяем его идентификатор
					int num = BlnProfilePlane3D::GetAlphaSliderNum(hwnd, nID);

					// Требуем установить ползунок в положение m_Pos[i]
					::SendMessage(hwnd, TBM_SETPOS, TRUE,
									(LPARAM)m_Pos[i]);
					char s[1024];
					//====== Готовим текстовый аналог текущей позиции
					sprintf (s,"%d",m_Pos[i]);
					//====== Помещаем текст в окно справа от ползунка
					SetDlgItemText(hDlg, nID, (LPCTSTR)s);
				}
			}
			break;
		case IDOK :
			{
				char str[1023];
				GetDlgItemText(hDlg, IDC_EDIT_SURF_ALPHA_PLANE,str,1022);
				int alpha = atoi (str);
				if (alpha >= 0.0 && alpha <= 255)
					me->m_alpha = alpha;
				else
					MessageBox(0, "Enter a valid value", "Alpha dialog", 0);

//				GetDlgItemText(hDlg, IDC_EDIT_SURF_RAZLOM_THICKNESS,str,1022);
//				double thickness = atof (str);
				//if (thickness >= 0.0)
//					me->m_pSurfDoc->m_razlomThickness = thickness;
				//else
				//	MessageBox(0, "Enter a valid value", "Alpha dialog", 0);

				SendMessage(hDlg,WM_COMMAND,IDC_INIT_SURF_ALPHA_SLIDER,0);

				
				// init of zoomCoefZ_XY
				me->m_pSurfDoc->ZoomView();


				me->m_pSurfDoc->Draw();

				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);

			}
			break;
			
		case IDCANCEL :
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
		
		default :
			
			return( FALSE );
	}
	return( TRUE );
}


BOOL CALLBACK BlnProfilePlane3D::DlgProcDrawModes( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam )
{
	static BlnProfilePlane3D * me;
	switch( uMsg )
	{
    case WM_INITDIALOG :
		{	
			PROPSHEETPAGE *lPage = (PROPSHEETPAGE*)lParam;
			me = (BlnProfilePlane3D *)lPage->lParam;
		/*
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			CheckDlgButton( hDlg, IDC_CHECK_ISOSURFACE,
				me->draw_as_one_isosurface ? BST_CHECKED : BST_UNCHECKED );
			CheckDlgButton( hDlg, IDC_CHECK_MANY_ISOSURFACES,
				me->draw_as_many_isosurfaces ? BST_CHECKED : BST_UNCHECKED );
			//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
		}
		break;
	case WM_COMMAND :
		switch( LOWORD( wParam ) )
		{
		case IDC_CHECK_ISOSURFACE:
			{
				//me->draw_as_one_isosurface = IsDlgButtonChecked( hDlg, IDC_CHECK_ISOSURFACE) == BST_CHECKED;
				me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
			}
			break;
		case IDC_CHECK_MANY_ISOSURFACES:
			{
				//me->draw_as_many_isosurfaces = IsDlgButtonChecked( hDlg, IDC_CHECK_MANY_ISOSURFACES) == BST_CHECKED;
				me->ReDraw();
				//====== Перерисовываем Вид с учетом изменений
				RECT rect;
				GetClientRect(me->m_pSurfDoc->hSurfWnd,&rect);
				InvalidateRect(me->m_pSurfDoc->hSurfWnd,&rect, true);
			}
			break;
		}
		break;	
	default :	
		return( FALSE );
	}
	return( TRUE );
}

void BlnProfilePlane3D::PropertiesDialog()
{
    // Ensure that the common control DLL is loaded. 
	// InitCommonControls(); 
	// Инициализируем страницы блокнота  


	psheetPage[0].dwSize = sizeof(PROPSHEETPAGE);
	psheetPage[0].hInstance = hInst;
//	psheetPage[0].pszIcon = MAKEINTRESOURCE(IDI_TAB);
	psheetPage[0].pszIcon = NULL;
	psheetPage[0].dwFlags = PSP_USETITLE/* | PSP_USEICONID*/;
	psheetPage[0].pszTemplate = MAKEINTRESOURCE(IDD_DIALOG_BLN_PROFILE_PLANE_DRAW_MODES);
	psheetPage[0].pfnDlgProc = BlnProfilePlane3D::DlgProcDrawModes;
	psheetPage[0].pszTitle = "Draw Modes";
	psheetPage[0].lParam = (LPARAM)this;
	// Добавляем страницу в блокнот, сохраняя ее
	// идентификатор в массиве hPage
	hPage[0] = CreatePropertySheetPage(&psheetPage[0]);

	// Инициализируем заголовок блокнота
	psheetHeader.dwSize = sizeof(PROPSHEETHEADER);
	psheetHeader.hInstance = hInst;
	psheetHeader.pszIcon = MAKEINTRESOURCE(IDI_APPICONSM);
	psheetHeader.dwFlags = PSH_USEICONID;
	psheetHeader.hwndParent = this->m_pSurfDoc->hwndTV;
	psheetHeader.hwndParent = this->m_pSurfDoc->hSurfWnd;
	psheetHeader.hwndParent = NULL;
	psheetHeader.pszCaption = "BlnProfilePlane3D Properties";
	psheetHeader.nPages = 
	sizeof(psheetPage) / sizeof(PROPSHEETPAGE);
	psheetHeader.phpage = (HPROPSHEETPAGE FAR  *)&hPage[0];

	// Создаем и отображаем блокнот
	PropertySheet(&psheetHeader);

	//For a modeless property sheet, your message loop should use 
	//PSM_ISDIALOGMESSAGE to pass messages to the property sheet dialog box. 
	//Your message loop should use PSM_GETCURRENTPAGEHWND to determine when 
	//to destroy the dialog box. When the user clicks the OK or Cancel button, 
	//PSM_GETCURRENTPAGEHWND returns NULL. You can then use the DestroyWindow 
	//function to destroy the dialog box.


}
bool BlnProfilePlane3D::ColorDialog(void)
{
	return false;
}

COLORREF BlnProfilePlane3D::GetColor(void)
{
	return COLORREF();
}

void BlnProfilePlane3D::SetColor(COLORREF color)
{
}
Archive& operator <<(Archive& ar, BlnProfilePlane3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
//printf("Archive& operator <<(Archive& ar, BlnProfilePlane3D& ob) version = %d\n", version);
	switch (version)
	{
	case 1:
		{
			ar << ob.m_alpha;
			ar << ob.m_vdplaneBlnProfiles;
			ar << ob.m_vvplaneBlnProfiles;
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
Archive& operator >>(Archive& ar, BlnProfilePlane3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_alpha;
			ar >> ob.m_vdplaneBlnProfiles;
			ar >> ob.m_vvplaneBlnProfiles;
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


bool BlnProfilePlane3D::Projection(CPoint3& in, CPoint3& out)
{
	double t_temp = DBL_MAX;
	bool result = false;
	printf("BlnProfilePlane3D::Projection\n");
	if ( this->m_vdplaneBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = this->m_vdplaneBlnProfiles.GetCurrentMsgLen();

			CPoint3 *ptd;
			ptd = this->m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			//=============================================
			for (int i = 0; i + 2 < len - 1; i+=2)
			{	
				//printf("BlnProfilePlane3D::Projection i = %d\n", i);
				double A,B,C,D;
				CPoint2 p1,p2;
				p1.x = ptd[i].x;   p1.y = ptd[i].y;
				p2.x = ptd[i+2].x; p2.y = ptd[i+2].y;
				if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
				{
					//printf("BlnProfilePlane3D::Projection 1\n");
					double t = -(A*in.x + B*in.y + C*in.z + D)
						/
						(A*A + B*B + C*C);

					if (fabs(t) < t_temp)
					{
						t_temp = fabs(t);
						//printf("BlnProfilePlane3D::Projection t = %f\n", t);
						out.x = in.x + A*t;
						out.y = in.y + B*t;
						out.z = in.z + C*t;
						//printf("out = [%f %f %f]\n", out.x,out.y,out.z);
						result = true;
					}
				}			
			}
		}
		while( this->m_vdplaneBlnProfiles.IncrementCurrentMsg());
	}
						
	//printf("BlnProfilePlane3D::Projection return false\n");
	return result;
}


bool BlnProfilePlane3D::Projection_old(CPoint3& in, CPoint3& out)
{
	printf("BlnProfilePlane3D::Projection\n");
	if ( this->m_vdplaneBlnProfiles.SetCurrentMsgOnFirst())
	{
		do
		{
			int len = this->m_vdplaneBlnProfiles.GetCurrentMsgLen();

			CPoint3 *ptd;
			ptd = this->m_vdplaneBlnProfiles.GetCurrentMsgPtr();
			//=============================================
			for (int i = 0; i + 2 < len - 1; i+=2)
			{	
				//printf("BlnProfilePlane3D::Projection i = %d\n", i);
				double A,B,C,D;
				CPoint2 p1,p2;
				p1.x = ptd[i].x;   p1.y = ptd[i].y;
				p2.x = ptd[i+2].x; p2.y = ptd[i+2].y;
				if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
				{
					//printf("BlnProfilePlane3D::Projection 1\n");
					double t = -(A*in.x + B*in.y + C*in.z + D)
						/
						(A*A + B*B + C*C);
					//printf("BlnProfilePlane3D::Projection t = %f\n", t);
					out.x = in.x + A*t;
					out.y = in.y + B*t;
					out.z = in.z + C*t;
					//printf("out = [%f %f %f]\n", out.x,out.y,out.z);
					double 
						minx = min(ptd[i].x,ptd[i+2].x),
						maxx = max(ptd[i].x,ptd[i+2].x),

						miny = min(ptd[i].y,ptd[i+2].y),
						maxy = max(ptd[i].y,ptd[i+2].y),

						minz = min(ptd[i].z,ptd[i+1].z),
						maxz = max(ptd[i].z,ptd[i+1].z);

					if (
						out.x >= minx && out.x <= maxx && 
						out.y >= miny && out.y <= maxy && 
						out.z >= minz && out.z <= maxz)
					{
						printf("BlnProfilePlane3D::Projection return true\n");
						return true;
					}
				}			
			}
		}
		while( this->m_vdplaneBlnProfiles.IncrementCurrentMsg());

	}
						
	printf("BlnProfilePlane3D::Projection return false\n");
	return false;
}

void BlnProfilePlane3D::clear(void)
{
	this->m_vdplaneBlnProfiles.clear();
	this->m_vvplaneBlnProfiles.clear();
}
