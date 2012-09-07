// ThePoint3D.cpp: implementation of the ThePoint3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ThePoint3D.h"
#include "SurfDoc.h"
#include "distance3D.h"
#include ".\whatselected.h"
#include "winsurftree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ThePoint3D::ThePoint3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

ThePoint3D::ThePoint3D(SurfDoc *pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
#define THEPOINT3D_VERSION 2
void ThePoint3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::thepoint3d;
	this->m_object_version = THEPOINT3D_VERSION;
	this->m_max_object_version = THEPOINT3D_VERSION;

	id_point = -1;
}
ThePoint3D::~ThePoint3D()
{

}


void ThePoint3D::Init(SurfDoc *pSurfDoc, CPoint3 pt)
{
	m_pSurfDoc = pSurfDoc;

	Free();
	AllocPoints(1);
	m_vvPoints[0] = pt;
	m_vdPoints[0] = pt;
}

HTREEITEM ThePoint3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	if(GetPointsNumber())
	{
		CPoint3 pt = GetFirstDocumentPoint();
		sprintf(szItemText, "%s%f,%f,%f", s, pt.x, pt.y, pt.z);
	}
	else
		sprintf(szItemText, "%sNULL point", s);
	// Add the item to the tree-view control
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
GLfloat ThePoint3D::point_size = 3.0;
void ThePoint3D::Drawing()
{
	if (m_pSurfDoc)
	{
#if 1
		//glPointSize(1.0);
		glPointSize(ThePoint3D::point_size);
		//glPushName(GLNAME_MD_TYPE1); glPushName((i32u) & (* it1));
		
		glBegin(GL_POINTS);
		glColor3ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)); 
		//glVertex3fv((* it1).GetCRD(n1));
		if (this->GetPointsNumber())
		{
			glVertex3d (m_vvPoints[0].x, 
						m_vvPoints[0].y, 
						m_vvPoints[0].z);
		}
		glEnd();
		
		//glPopName(); glPopName();
#else
		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

		if (this->GetPointsNumber())
		{
			if (m_vvPoints[0].bVisible)
			{
				glColor3ub (GetRValue(m_color),GetGValue(m_color),GetBValue(m_color)); 

				GLUquadricObj* pSphere = gluNewQuadric();
				gluQuadricDrawStyle(pSphere, GLU_FILL);
				glPushMatrix();//перейдём к новым координатам, сохранив старые
				
				glTranslated(
					m_vvPoints[0].x, 
					m_vvPoints[0].y, 
					m_vvPoints[0].z
					);


				gluSphere(pSphere, 
					m_pSurfDoc->m_sphere_radius, 
					m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
					m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
					) ;//рисуем сферу 
				glPopMatrix(); //возвращаемся к старым координатам 
				gluDeleteQuadric(pSphere);
			}
#if DISVISIBLE_AS_ALPHA
			else
			{
				glColor4ub (255,255,255, DISVISIBLE_ALPHA);				

				GLUquadricObj* pSphere = gluNewQuadric();
				gluQuadricDrawStyle(pSphere, GLU_FILL);
				glPushMatrix();//перейдём к новым координатам, сохранив старые
				
				glTranslated(
					m_vvPoints[0].x, 
					m_vvPoints[0].y, 
					m_vvPoints[0].z
					);


				gluSphere(pSphere, 
					m_pSurfDoc->m_sphere_radius, 
					m_pSurfDoc->m_sphere_slices, //The number of subdivisions around the z-axis (similar to lines of longitude). 					
					m_pSurfDoc->m_sphere_stacks  //The number of subdivisions along the z-axis (similar to lines of latitude). 
					) ;//рисуем сферу 
				glPopMatrix(); //возвращаемся к старым координатам 
				gluDeleteQuadric(pSphere);
			}
#endif
		}
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
#endif
	}
}

#include "../../wintools\src\project.h"
#include "../../wintools\src\win32_map_views.h"

void ThePoint3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{	
	double epsilon = 1.0e-2;
//	double epsilon = 3.0;

	fGL x; fGL y;

	v->PreConvertingFromWorldToScreen();


	fGL r = v->lines_points_radius;

	COLORREF color = m_color;
	Color gdi_color(255, GetRValue(color),GetGValue(color),GetBValue(color));
	Pen      pen(gdi_color);

	double dist_to_plane;
	CPoint2 profile;

	if (this->GetPointsNumber())
	{
		CPoint3 in = this->m_vdPoints[0];
		on->Projection(in, profile, dist_to_plane);
		if(fabs(dist_to_plane) <= epsilon)
		{
			v->ConvertingFromWorldToScreen(profile.x, profile.y, x, y);
			//DrawCircle(&graphics, x, y, r, gdi_color);
			FillCircle(&graphics, x, y, r, gdi_color);
		}
	}

}



bool ThePoint3D::OnProfile(Profile3D * on)
{	
	double dist_to_plane;
	CPoint2 profile;

	if (GetPointsNumber() < 1) return false;

	//Convert3D_To_2D
	on->Projection(m_vdPoints[0], profile, dist_to_plane);
	return fabs(dist_to_plane) <= 1.0e-8;
}

bool ThePoint3D::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	if (!this->IsCheckedEx()) return false;
	search_radius = fabs(search_radius);
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
				);
			return true;
		}
	}
	return false;
}
void ThePoint3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "ThePoint3D" , 0);
}

void ThePoint3D::Init(const ThePoint3D& ob)
{
	this->m_pSurfDoc = ob.m_pSurfDoc;
}

ThePoint3D::ThePoint3D(const ThePoint3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

ThePoint3D& ThePoint3D::operator=(const ThePoint3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD ThePoint3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, ThePoint3D& ob)
{
	//printf("Archive& operator <<(Archive& ar, ThePoint3D& ob) ob.m_object_version = %d\n", ob.m_object_version);
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);

	switch (version)
	{
	case 2:
		{
			ar << ob.id_point;
		}
	case 1:
		{
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
Archive& operator >>(Archive& ar, ThePoint3D& ob)
{
	//printf("Archive& operator >>(Archive& ar, ThePoint3D& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	//printf("ob.m_object_version = %d\n", ob.m_object_version);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 2:
		{
			ar >> ob.id_point;
		}
	case 1:
		{
			ob.m_object_version = THEPOINT3D_VERSION;
		}
		break;
	default:
		{
			//printf("Archive& operator >>(Archive& ar, ThePoint3D& ob) throw!!!\n");
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
	return ar;
}

