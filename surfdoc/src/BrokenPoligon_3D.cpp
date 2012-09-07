// BrokenPoligon_3D.cpp: implementation of the BrokenPoligon_3D class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BrokenPoligon_3D.h"
#include "winsurftree.h"
#include "surfdoc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BrokenPoligon_3D::BrokenPoligon_3D()
{
	m_pSurfDoc = NULL;
	OnCreate();

}
BrokenPoligon_3D::BrokenPoligon_3D(SurfDoc* pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
	OnCreate();
}
void BrokenPoligon_3D::OnCreate(void)
{
	this->m_object_type = Object::object_type::broken_poligon_3d;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_poligones.OnCreate();
}
BrokenPoligon_3D::BrokenPoligon_3D(const BrokenPoligon_3D & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
BrokenPoligon_3D& BrokenPoligon_3D::operator=(const BrokenPoligon_3D& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}


BrokenPoligon_3D::~BrokenPoligon_3D()
{

}
bool BrokenPoligon_3D::UpdateExtremums()
{
	vector<CPoint3> vptmax,vptmin;

	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			if(m_poligones.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_poligones.GetCurrentMsg().GetMax());
				vptmin.push_back(m_poligones.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}

bool BrokenPoligon_3D::UpdateExtremums(Profile3D * on, bool & start, CPoint2 & profile_min, CPoint2 & profile_max)
{

    if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			if(m_poligones.GetCurrentMsg().UpdateExtremums(on, start, profile_min, profile_max))
			{
			}
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
	return !start;
}

void BrokenPoligon_3D::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}
void BrokenPoligon_3D::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}
void BrokenPoligon_3D::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().Zoom(
			zoomX,zoomY,zoomZ, 
			x_mean,y_mean,z_mean
			);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}
void BrokenPoligon_3D::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
}

void BrokenPoligon_3D::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}

HTREEITEM BrokenPoligon_3D::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	// Add the item to the tree-view control
	sprintf(szItemText, "broken poligon \"%s\"", this->GetName().c_str());
	Object * pObject = dynamic_cast<Object *> (&m_poligones_ObjectList);
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	if (m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			// Add the item to the tree-view control
			sprintf(szItemText, "poli id_umpoz=%d points=%d \"%s\""
				, m_poligones.GetCurrentMsg().id_umpoz
				, m_poligones.GetCurrentMsg().GetPointsNumber()
				, m_poligones.GetCurrentMsg().GetName()
				);
			Object * pObject = dynamic_cast<Object *> (&m_poligones.GetCurrentMsg());
			// Add the item to the tree-view control. 
			AddItemToTree(hwndTV, szItemText, pObject, h2); 
		}
		while(m_poligones.IncrementCurrentMsg());
	}
	return h2;
}
void BrokenPoligon_3D::Draw()
{
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().Draw();
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}
void BrokenPoligon_3D::DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on)
{
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			Poligon3D * pObject = &m_poligones.GetCurrentMsg();
			if(pObject->IsCheckedEx())
				pObject->DrawGDIplus(select_buffer, graphics, v,on);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}


void BrokenPoligon_3D::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if(this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			m_poligones.GetCurrentMsg().ReDraw();
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}
size_t BrokenPoligon_3D::GetPointsNumber()
{
	return 0;// FIX error in the BrokenPoligon_3D::UpdateExtremums() and remove this line
}


void BrokenPoligon_3D::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "BrokenPoligon_3D" , 0);

}

bool BrokenPoligon_3D::ColorDialog(void)
{
	return false;
}

COLORREF BrokenPoligon_3D::GetColor(void)
{
	return COLORREF();
}

void BrokenPoligon_3D::SetColor(COLORREF color)
{
	if (this->m_poligones.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_poligones.GetCurrentMsg().SetColor(color);
		}
		while(this->m_poligones.IncrementCurrentMsg());
	}
}
DWORD BrokenPoligon_3D::Serialize(Archive& ar)
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
Archive& operator <<(Archive& ar, BrokenPoligon_3D& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 1:
		{
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
	return ar;
}
Archive& operator >>(Archive& ar, BrokenPoligon_3D& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			// Objects' vectors
			ar >> ob.m_poligones;				ar >> ob.m_poligones_ObjectList;
			ob.m_poligones_ObjectList.Init(ob.m_poligones, &ob);
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