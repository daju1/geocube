

#include "stdafx.h"
#include "Sphere3D.h"
#include "SurfDoc.h"
#include "distance3D.h"
#include ".\whatselected.h"
#include "winsurftree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Sphere3D::Sphere3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

Sphere3D::Sphere3D(SurfDoc *pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
void Sphere3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::sphere3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}

Sphere3D::~Sphere3D()
{

}


void Sphere3D::Init(SurfDoc *pSurfDoc, CPoint3 pt)
{
	m_pSurfDoc = pSurfDoc;

	Free();
	AllocPoints(1);
	m_vvPoints[0] = pt;
	m_vdPoints[0] = pt;
}

HTREEITEM Sphere3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	if(GetPointsNumber())
	{
		CPoint3 pt = GetFirstDocumentPoint();
		sprintf(szItemText, "%f,%f,%f", pt.x, pt.y, pt.z);
	}
	else
		sprintf(szItemText, "NULL point");
	// Add the item to the tree-view control
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}

void Sphere3D::Drawing()
{
	//printf("Sphere3D::Drawing()\n");
	if (m_pSurfDoc)
	{
		//printf("Sphere3D::Drawing() if (m_pSurfDoc) \n");
		double 
			maxz = m_pSurfDoc->m_Spheres_max_z,
			minz = m_pSurfDoc->m_Spheres_min_z,
			delta_z = maxz - minz;

		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

		if (this->GetPointsNumber())
		{
			if (m_vvPoints[0].bVisible)
			{
				COLORREF sphereColor = m_color;
				if (m_pSurfDoc->m_bUseColormapOnSurf)
				{
					UINT
						color_i;
					int palette_len = m_pSurfDoc->m_palette.GetLen()-1;

					double
						zdi = this->GetFirstDocumentPoint().z;

					if (m_pSurfDoc->m_bInverseColormap)
					{
						color_i = UINT(0.5+(maxz - zdi) / (delta_z) * double(palette_len)); 

					}
					else
					{
						color_i = UINT(0.5+(zdi - minz) / (delta_z) * double(palette_len)); 
					}

					sphereColor = m_pSurfDoc->m_palette.GetColor(color_i);
				}
				glColor3ub (GetRValue(sphereColor),GetGValue(sphereColor),GetBValue(sphereColor)); 

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
	}
}
bool Sphere3D::IsSelected(CPoint3 selected_view_pt, 
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

void Sphere3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "Sphere3D" , 0);
}

void Sphere3D::Init(const Sphere3D& ob)
{
	this->m_pSurfDoc = ob.m_pSurfDoc;
}

Sphere3D::Sphere3D(const Sphere3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

Sphere3D& Sphere3D::operator=(const Sphere3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD Sphere3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, Sphere3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (version)
	{
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
Archive& operator >>(Archive& ar, Sphere3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	dynamic_cast<Primitive3D<CPoint3> *>(&ob)->Primitive_Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
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

