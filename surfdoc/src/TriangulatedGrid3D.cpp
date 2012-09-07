// TriangulatedGrid3D.cpp: implementation of the TriangulatedGrid3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TriangulatedGrid3D.h"
#include ".\triangulatedgrid3d.h"
#include "winsurftree.h"
#include "surfdoc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TriangulatedGrid3D::TriangulatedGrid3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
TriangulatedGrid3D::TriangulatedGrid3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
TriangulatedGrid3D::TriangulatedGrid3D(const TriangulatedGrid3D & ob)
{
	dynamic_cast<Object*>(this)->Init(ob);
	this->Init(ob);
}
TriangulatedGrid3D& TriangulatedGrid3D::operator=(const TriangulatedGrid3D& ob)
{
	if (this == &ob)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(ob);
	this->Init(ob);

	return *this;
}
TriangulatedGrid3D::~TriangulatedGrid3D()
{

}
void TriangulatedGrid3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "TriangulatedGrid3D" , 0);

}
void TriangulatedGrid3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::triangulated_grid3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	m_lines.OnCreate(0);
	m_ii_lines.OnCreate(0);

	m_trias.OnCreate(0);
	m_ii_trias.OnCreate(0);
}
void TriangulatedGrid3D::AddLine(int i1, int i2, CPoint3* pts, int len, COLORREF color)
{
	InterWellsLine3D line(this->m_pSurfDoc);
	m_lines.AddMsg(&line);
	m_lines.GetLastMsg().InitPoints(pts, len, color);
	m_lines_ObjectList.Init(m_lines, this);

	TWO two;
	m_ii_lines.AddMsg(&two);
	m_ii_lines.GetLastMsg().i1 = i1;
	m_ii_lines.GetLastMsg().i2 = i2;
}
void TriangulatedGrid3D::AddTriangle(int i1, int i2, int i3, CPoint3 v1, CPoint3 v2, CPoint3 v3, COLORREF color)
{
	Triangle3 tri;
	tri.v1 = v1;
	tri.v2 = v2;
	tri.v3 = v3;

	Triangle3D poly(this->m_pSurfDoc);
	m_trias.AddMsg(&poly);
	m_trias.GetLastMsg().Init(tri,color);
	m_trias_ObjectList.Init(m_trias, this);

	TRIA tria;
	m_ii_trias.AddMsg(&tria);
	m_ii_trias.GetLastMsg().i1 = i1;
	m_ii_trias.GetLastMsg().i2 = i2;
	m_ii_trias.GetLastMsg().i3 = i3;
}

void TriangulatedGrid3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
}

void TriangulatedGrid3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
}

bool TriangulatedGrid3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			if (m_lines.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_lines.GetCurrentMsg().GetMax());
				vptmin.push_back(m_lines.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_lines.IncrementCurrentMsg());
	}

	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			if (this->m_trias.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(this->m_trias.GetCurrentMsg().GetMax());
				vptmin.push_back(this->m_trias.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void TriangulatedGrid3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
}
void TriangulatedGrid3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) )
{
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}
void TriangulatedGrid3D::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
}

HTREEITEM TriangulatedGrid3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	UINT	 len	= this->GetPointsNumber();					
	// Add the item to the tree-view control
	sprintf(szItemText, "TriangulatedGrid");	
	// Add the item to the tree-view control
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	{
		// Add the item to the tree-view control
		sprintf(szItemText, "Lines");
		pObject = dynamic_cast<Object *> (&this->m_lines_ObjectList);
		HTREEITEM h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		if (this->m_lines.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_lines.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
			}
			while(this->m_lines.IncrementCurrentMsg());
		}
		// Add the item to the tree-view control
		sprintf(szItemText, "Trias");
		pObject = dynamic_cast<Object *> (&this->m_trias_ObjectList);
		h3 = AddItemToTree(hwndTV, szItemText, pObject, h2);
		//
		if (this->m_trias.SetCurrentMsgOnFirst())
		{
			do
			{
				this->m_trias.GetCurrentMsg().AddItem_ToTree(hwndTV, h3);
			}
			while(this->m_trias.IncrementCurrentMsg());
		}
	}
	return h2;
}

void TriangulatedGrid3D::Draw()
{
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().Draw();
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().Draw();
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
}
void TriangulatedGrid3D::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if (this->m_lines.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_lines.GetCurrentMsg().ReDraw();
		}
		while(this->m_lines.IncrementCurrentMsg());
	}
	if (this->m_trias.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_trias.GetCurrentMsg().ReDraw();
		}
		while(this->m_trias.IncrementCurrentMsg());
	}
}
size_t TriangulatedGrid3D::GetPointsNumber()
{
	return 0;// FIX error in the TriangulatedGrid3D::UpdateExtremums() and remove this line
	return 2*m_lines.msgSize() + 3*m_trias.msgSize();
}
bool TriangulatedGrid3D::ColorDialog(void)
{
	return false;
}

COLORREF TriangulatedGrid3D::GetColor(void)
{
	return COLORREF();
}

void TriangulatedGrid3D::SetColor(COLORREF color)
{
}
DWORD TriangulatedGrid3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, TriangulatedGrid3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 1:
		{
			ar << ob.m_indexes;

			// Objects' vectors

			ar << ob.m_lines;			ar << ob.m_lines_ObjectList;
			ar << ob.m_ii_lines;

			ar << ob.m_trias;			ar << ob.m_trias_ObjectList;
			ar << ob.m_ii_trias;
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
Archive& operator >>(Archive& ar, TriangulatedGrid3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			ar >> ob.m_indexes;

			// Objects' vectors

			ar >> ob.m_lines;			ar >> ob.m_lines_ObjectList;
			ob.m_lines_ObjectList.Init(ob.m_lines, &ob);
			ar >> ob.m_ii_lines;

			ar >> ob.m_trias;			ar >> ob.m_trias_ObjectList;
			ob.m_trias_ObjectList.Init(ob.m_trias, &ob);
			ar >> ob.m_ii_trias;
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

