// BrokenPoligon3D.cpp: implementation of the BrokenPoligon3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrokenPoligon3D.h"
#include "winsurftree.h"
#include "surfdoc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrokenPoligon3D::BrokenPoligon3D()
{
	m_pSurfDoc = NULL;
	OnCreate();
}
BrokenPoligon3D::BrokenPoligon3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
#define BROKEN_POLIGON_VERSION 4
void BrokenPoligon3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::broken_poligon3d;
	this->m_object_version = BROKEN_POLIGON_VERSION;
	this->m_max_object_version = BROKEN_POLIGON_VERSION;

	this->id_ige = -1;
	this->id_umpoz = 0;
}
BrokenPoligon3D::BrokenPoligon3D(const BrokenPoligon3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
BrokenPoligon3D& BrokenPoligon3D::operator=(const BrokenPoligon3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

BrokenPoligon3D::~BrokenPoligon3D()
{

}

bool BrokenPoligon3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			if(m_poligones[n_cut][i].UpdateExtremums())
			{
				vptmax.push_back(m_poligones[n_cut][i].GetMax());
				vptmin.push_back(m_poligones[n_cut][i].GetMin());
			}
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		if(m_poligones[n_cut].UpdateExtremums())
		{
			vptmax.push_back(m_poligones[n_cut].GetMax());
			vptmin.push_back(m_poligones[n_cut].GetMin());
		}
	}
#endif
	return this->Object::UpdateExtremums(vptmax,vptmin);
}
void BrokenPoligon3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].CutAndDisvisible(positive, a, b, c, d);
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].CutAndDisvisible(positive, a, b, c, d);
	}
#endif
}
void BrokenPoligon3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].CutXYZandDisvisible(subcube_number, X, Y, Z);
	}
#endif
}

void BrokenPoligon3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,y_mean,z_mean
				);
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].Zoom(
			zoomX,zoomY,zoomZ, 
			x_mean,y_mean,z_mean
			);
	}
#endif
}
void BrokenPoligon3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
	}
#endif

	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}

}

void BrokenPoligon3D::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].SetLayer(layer);
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].SetLayer(layer);
	}
#endif
}

HTREEITEM BrokenPoligon3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	// Add the item to the tree-view control
	sprintf(szItemText, "broken poligons \"%s\" id_umpoz=%d id_ige=%d", this->GetName().c_str(), this->id_umpoz, this->id_ige);
	Object * pObject = dynamic_cast<Object *> (&m_poligones_ObjectList);
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 

#if USE_UNVISIBLE_CUTTING
	for (size_t n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			sprintf(szItemText, "poli n_cut = %u UserID=%d id_umpoz=%d points=%d \"%s\""
				, n_cut
				, m_poligones[n_cut][i].id_umpoz
				, m_poligones[n_cut][i].GetUserID()
				, m_poligones[n_cut][i].GetPointsNumber()
				, m_poligones[n_cut][i].GetName().c_str()
				);
			Object * pObject = dynamic_cast<Object *> (&m_poligones[n_cut][i]);
			// Add the item to the tree-view control. 
			AddItemToTree(hwndTV, szItemText, pObject, h2); 
		}
	}
#else
	for (size_t n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		sprintf(szItemText, "poli n_cut = %u UserID=%d id_umpoz=%d points=%d \"%s\""
			, n_cut
			, m_poligones[n_cut].id_umpoz
			, m_poligones[n_cut].GetUserID()
			, m_poligones[n_cut].GetPointsNumber()
			, m_poligones[n_cut].GetName().c_str()
			);
		Object * pObject = dynamic_cast<Object *> (&m_poligones[n_cut]);
		// Add the item to the tree-view control. 
		AddItemToTree(hwndTV, szItemText, pObject, h2); 
	}
#endif
	return h2;
}
void BrokenPoligon3D::Draw()
{
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].Draw();
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].Draw();
	}
#endif
}
void BrokenPoligon3D::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	int n_cut;
#if USE_UNVISIBLE_CUTTING
	for (n_cut = 0; n_cut < m_poligones.size(); n_cut++)
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].ReDraw();
		}
	}
#else
	for (n_cut = 0; n_cut < m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n_cut++)
	{
		m_poligones[n_cut].ReDraw();
	}
#endif
}

size_t BrokenPoligon3D::GetPointsNumber()
{
	return 0;// FIX error in the BrokenPoligon3D::UpdateExtremums() and remove this line
}


void BrokenPoligon3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "BrokenPoligon3D" , 0);

}

bool BrokenPoligon3D::ColorDialog(void)
{
	return false;
}

COLORREF BrokenPoligon3D::GetColor(void)
{
	return COLORREF();
}

void BrokenPoligon3D::SetColor(COLORREF color)
{
#if USE_UNVISIBLE_CUTTING
	for(size_t n_cut = 0; n_cut < this->m_poligones.size(); n_cut ++)		
	{
		for (size_t i = 0; i < m_poligones[n_cut].Size(); i++)
		{
			m_poligones[n_cut][i].SetColor(color);
		}
	}
#else
	for(size_t n = 0; n < this->m_poligones.PLANE_MEMBERS_VECTOR_SIZE(); n ++)		
	{
		this->m_poligones[n].SetColor(color);
	}
#endif
}
DWORD BrokenPoligon3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, BrokenPoligon3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
#if USE_UNVISIBLE_CUTTING
	switch (version)
	{
	case 4:
		{
			ar << ob.id_ige;
			ar << ob.id_umpoz;
			ar << ob.m_nCuts;
			ar << ob.m_nDrills;

			// Objects' vectors
			ar << ob.m_poligones;			ar << ob.m_poligones_ObjectList;
		}
		break;
/*	case 3:
		{
			ar << ob.id_ige;
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
			ar << ob.m_poligones;			ar << ob.m_poligones_ObjectList;
		}
		break;*/
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
#else
	switch (version)
	{
	case 3:
		{
			ar << ob.id_ige;
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
			ar << ob.m_poligones;			ar << ob.m_poligones_ObjectList;
		}
		break;
	default:
		{
			throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
#endif
	return ar;
}
Archive& operator >>(Archive& ar, BrokenPoligon3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
#if USE_UNVISIBLE_CUTTING
	switch (ob.m_object_version)
	{
	case 4:
		{
			ar >> ob.id_ige;
			ar >> ob.id_umpoz;
			ar >> ob.m_nCuts;
			ar >> ob.m_nDrills;

			// Objects' vectors
			ar >> ob.m_poligones;			ar >> ob.m_poligones_ObjectList;
			ob.m_poligones_ObjectList.Init_std_vector_Vector(ob.m_poligones, &ob);

			ob.m_object_version = BROKEN_POLIGON_VERSION;
		}
		break;
	case 3:
		{
			ar >> ob.id_ige;
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
			PLANE_MEMBERS_VECTOR<Poligon3D> m_poligones_old;
			ar >> m_poligones_old;

			ob.m_poligones.clear();
			ob.m_poligones.resize(m_poligones_old.Size());

			for (size_t i = 0; i < m_poligones_old.Size(); i++)
			{
				ob.m_poligones[i].resize(1);
				ob.m_poligones[i][0] = m_poligones_old[i];
			}			
			
			ar >> ob.m_poligones_ObjectList;
			ob.m_poligones_ObjectList.Init_std_vector_Vector(ob.m_poligones, &ob);

			ob.m_object_version = BROKEN_POLIGON_VERSION;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
#else
	switch (ob.m_object_version)
	{
	case 4:
	case 3:
		{
			ar >> ob.id_ige;
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
			ar >> ob.m_poligones;			ar >> ob.m_poligones_ObjectList;
			ob.m_poligones_ObjectList.Init1(ob.m_poligones, &ob);

			ob.m_object_version = BROKEN_POLIGON_VERSION;
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
#endif
	return ar;
}

