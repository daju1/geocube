// Triangle3D.cpp: implementation of the Triangle3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Triangle3D.h"
#include "surfdoc.h"
#include "winsurftree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Triangle3D::Triangle3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
Triangle3D::Triangle3D(SurfDoc * pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
void Triangle3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::triangle3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;
}
Triangle3D::~Triangle3D()
{

}



void Triangle3D::Init(Triangle3& tri, COLORREF color)
{
/*		m_ptMax.x = x.Max();
		m_ptMax.y = y.Max();
		m_ptMax.z = z.Max();

		m_ptMin.x = x.Min();
		m_ptMin.y = y.Min();
		m_ptMin.z = z.Min();*/

		Free();
		AllocPoints(3);

		m_color = color;

		m_vdPoints[0] = tri.v1;
		m_vvPoints[0] = tri.v1;

		m_vdPoints[1] = tri.v2;
		m_vvPoints[1] = tri.v2;

		m_vdPoints[2] = tri.v3;
		m_vvPoints[2] = tri.v3;
}
HTREEITEM Triangle3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	sprintf(szItemText, "len = %u color = %u", GetPointsNumber(), m_color);	
	// Add the item to the tree-view control
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	return AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
}
extern bool getNorm(double v1[3], double v2[3], double out[3]);

void Triangle3D::Drawing()
{
	if (m_pSurfDoc)
	{
		//====== Установка режима заполнения
		//====== внутренних точек полигонов
		GLint oldPolygonMode[2];
		glGetIntegerv(GL_POLYGON_MODE, oldPolygonMode);

		glPolygonMode(GL_FRONT_AND_BACK, GetFillMode());

			double d1[3],d2[3],norm[3];
		int len = this->GetPointsNumber();
		if (len == 3)
		{
			//====== Обход вершин осуществляется
			//====== в направлении против часовой стрелки


			d1[0] = m_vvPoints[0].x-m_vvPoints[1].x;
			d1[1] = m_vvPoints[0].y-m_vvPoints[1].y;
			d1[2] = m_vvPoints[0].z-m_vvPoints[1].z;

			d2[0] = m_vvPoints[1].x-m_vvPoints[2].x;
			d2[1] = m_vvPoints[1].y-m_vvPoints[2].y;
			d2[2] = m_vvPoints[1].z-m_vvPoints[2].z;

			getNorm(d1,d2,norm);


			glBegin(GL_TRIANGLES);
			for (int i = 0; i < len; i++)
			{
	#if 0
				double d1[3],d2[3],norm[3];


				//====== Обход вершин осуществляется
				//====== в направлении против часовой стрелки
				int i_minus_1 = i-1;
				int i_plus_1  = i+1;

				if(i == 0)
				{
					i_minus_1 = len-1;
				}
				if (i == len-1)
				{
					i_plus_1  = 0;
				}
				d1[0] = m_vvPoints[i_minus_1].x-m_vvPoints[i].x;
				d1[1] = m_vvPoints[i_minus_1].y-m_vvPoints[i].y;
				d1[2] = m_vvPoints[i_minus_1].z-m_vvPoints[i].z;

				d2[0] = m_vvPoints[i].x-m_vvPoints[i_plus_1].x;
				d2[1] = m_vvPoints[i].y-m_vvPoints[i_plus_1].y;
				d2[2] = m_vvPoints[i].z-m_vvPoints[i_plus_1].z;

				getNorm(d1,d2,norm);
	#endif
				//====== Задание вектора нормали
				if (m_vvPoints[i].bVisible)
				{

					glNormal3dv (norm);
					{
		//				glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha); 
						glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_pSurfDoc->m_alpha_plane); 
		//				glColor4ub (GetRValue(m_color), GetGValue(m_color), GetBValue(m_color), (GLubyte)m_alpha); 
					}
					glVertex3d (m_vvPoints[i].x, m_vvPoints[i].y, m_vvPoints[i].z);
				}
			}
			glEnd();
		}
		glPolygonMode(GL_FRONT_AND_BACK, oldPolygonMode[1]);
	}
}


void Triangle3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "Triangle3D" , 0);
}

void Triangle3D::Init(const Triangle3D& ob)
{
	this->m_pSurfDoc = ob.m_pSurfDoc;
}

Triangle3D::Triangle3D(const Triangle3D& ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);
}

Triangle3D& Triangle3D::operator=(const Triangle3D& ob)
{
	if (this == &ob)
		return *this;

	dynamic_cast<Object*>(this)->Init(ob);
	dynamic_cast<Primitive3D<CPoint3>*  >(this)->Init(ob);
	this->Init(ob);

	return *this;
}

DWORD Triangle3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, Triangle3D& ob)
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
Archive& operator >>(Archive& ar, Triangle3D& ob)
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

