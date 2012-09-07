// BrokenLine3D.cpp: implementation of the BrokenLine3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrokenLine3D.h"
#include "winsurftree.h"
#include "surfdoc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrokenLine3D::BrokenLine3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
BrokenLine3D::BrokenLine3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
#define BROKEN_LINE_3D_VERSION 3
void BrokenLine3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::broken_line3d;
	this->m_object_version = BROKEN_LINE_3D_VERSION;
	this->m_max_object_version = BROKEN_LINE_3D_VERSION;

	this->id_umpoz = 0;
	this->id_ige = -1;
	this->podoshva = 0;
}
BrokenLine3D::BrokenLine3D(const BrokenLine3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
BrokenLine3D& BrokenLine3D::operator=(const BrokenLine3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}


BrokenLine3D::~BrokenLine3D()
{

}
bool BrokenLine3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		if (m_lines[n_cut].UpdateExtremums())
		{
			vptmax.push_back(m_lines[n_cut].GetMax());
			vptmin.push_back(m_lines[n_cut].GetMin());
		}
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void BrokenLine3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].Zoom(
			zoomX,zoomY,zoomZ, 
			x_mean,y_mean,z_mean
			);
	}
}
void BrokenLine3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].CutAndDisvisible(positive,a,b,c,d);
	}
}
void BrokenLine3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].CutXYZandDisvisible(subcube_number, X, Y, Z);
	}
}
HTREEITEM BrokenLine3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	// Add the item to the tree-view control
	//sprintf(szItemText, "Lines n_surf = %d", n_surf);
	sprintf(szItemText, "Lines \"%s\" n_surf=%d id_umpoz=%d", this->GetName().c_str(), this->n_surf, this->id_umpoz);
	Object * pObject = dynamic_cast<Object *> (&m_lines_ObjectList);
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1);

	for (size_t n_cut = 0; n_cut < m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		// Add the item to the tree-view control
		size_t len = m_lines[n_cut].GetPointsNumber();
		sprintf(szItemText, "\"%s\"n_cut = %u len = %u id_ige=%d podoshva=%x", m_lines[n_cut].GetName().c_str(), n_cut, len, m_lines[n_cut].id_ige, m_lines[n_cut].podoshva);

		Object * pObject = dynamic_cast<Object *> (&m_lines[n_cut]);
		// Add the item to the tree-view control. 
		AddItemToTree(hwndTV, szItemText, pObject, h2); 
	}
	return h2;

}
	

void BrokenLine3D::Draw()
{
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].Draw();
	}
}
void BrokenLine3D::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].ReDraw();
	}
}
void BrokenLine3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
	}

	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}

}
void BrokenLine3D::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
	int n_cut;
	for (n_cut = 0; n_cut < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		this->m_lines[n_cut].SetLayer(layer);
	}
}
size_t BrokenLine3D::GetPointsNumber()
{
	return 0;// FIX error in the BrokenLine3D::UpdateExtremums() and remove this line
}


void BrokenLine3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "BrokenLine3D" , 0);

}

bool BrokenLine3D::ColorDialog(void)
{
	return false;
}

COLORREF BrokenLine3D::GetColor(void)
{
	return COLORREF();
}

void BrokenLine3D::SetColor(COLORREF color)
{
	for(size_t nline = 0; nline < this->m_lines.PLANE_MEMBERS_VECTOR_SIZE(); nline ++)		
	{
		this->m_lines[nline].SetColor(color);
	}
}
DWORD BrokenLine3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, BrokenLine3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 3:
		{
			ar << ob.n_surf;
		}
	case 2:
		{
			ar << ob.id_umpoz;
		}
	case 1:
		{
			ar << ob.m_nCuts;
			ar << ob.m_nDrills;

			// Objects' vectors
			ar << ob.m_lines;		ar << ob.m_lines_ObjectList;

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
Archive& operator >>(Archive& ar, BrokenLine3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 3:
		{
			ar >> ob.n_surf;
		}
	case 2:
		{
			ar >> ob.id_umpoz;
		}
	case 1:
		{
			ar >> ob.m_nCuts;
			ar >> ob.m_nDrills;

			// Objects' vectors
			ar >> ob.m_lines;			ar >> ob.m_lines_ObjectList;
			ob.m_lines_ObjectList.Init1(ob.m_lines, &ob);
	
			ob.m_object_version = BROKEN_LINE_3D_VERSION;

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

