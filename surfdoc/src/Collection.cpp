#include "stdafx.h"
#include ".\collection.h"
#include ".\archive.h"
#include "surfdoc.h"
#include "winsurftree.h"

Collection::Collection()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

Collection::Collection(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;
	OnCreate();
}

void Collection::OnCreate(void)
{
	this->m_object_type = Object::object_type::collection;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_objects.OnCreate();
}

Collection::Collection(const Collection & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
Collection& Collection::operator=(const Collection& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

Collection::~Collection(void)
{
}

Object * Collection::AddObject(Object * object)
{
//printf("Collection::AddObject\n");
	if (object)
	{
		this->m_objects.AddMsg(object);
		this->m_objects_ObjectList.Init(this->m_objects, this);
		return &this->m_objects.GetLastMsg();
	}
	return NULL;
}
void Collection::InitObjectList()
{
	this->m_objects_ObjectList.Init(this->m_objects, this);
}
bool Collection::UpdateExtremums()
{
//printf("Collection::UpdateExtremums\n");
	vector<CPoint3> vptmax,vptmin;

	if(this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			if(m_objects.GetCurrentMsg().UpdateExtremums())
			{
				vptmax.push_back(m_objects.GetCurrentMsg().GetMax());
				vptmin.push_back(m_objects.GetCurrentMsg().GetMin());
			}
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	return this->Object::UpdateExtremums(vptmax,vptmin);
}

void Collection::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
//printf("Collection::Zoom\n");	
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().Zoom(
				zoomX,zoomY,zoomZ, 
				x_mean,
				y_mean,
				z_mean
				);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}
HTREEITEM Collection::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	UINT n_objects = this->m_objects.msgSize();	

	sprintf(szItemText, "\"%s\" collection of %d objects",this->GetName().c_str(), n_objects );
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	// HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	HTREEITEM h2 = AddObjectListItem(hwndTV, szItemText, &this->m_objects_ObjectList, h1); 
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().AddItem_ToTree(hwndTV,	h2, s);
		}
		while(this->m_objects.IncrementCurrentMsg());
		return h2;
	}
	return NULL;
}
void Collection::Draw()
{
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().Draw();
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}

void Collection::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().ReDraw();
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}

bool Collection::IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws)
{
	search_radius = fabs(search_radius);

	
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			if(this->m_objects.GetCurrentMsg().IsSelected(
				selected_view_pt, search_radius, ws	))
			{
				return true;
			}
		}
		while(this->m_objects.IncrementCurrentMsg());
	}

	return false;
}

void Collection::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}

void Collection::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}
void Collection::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "Collection" , 0);
}

bool Collection::ColorDialog(void)
{
	return false;
}

COLORREF Collection::GetColor(void)
{
	return COLORREF();
}

void Collection::SetColor(COLORREF color)
{
}

void Collection::CutAndDisvisible(bool positive, double a, double b, double c, double d)
{
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().CutAndDisvisible(positive, a, b, c, d);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}

void Collection::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
{
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().CutXYZandDisvisible(subcube_number, X, Y, Z);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
}

Archive& operator <<(Archive& ar, Collection& ob)
{
//printf("Archive& operator <<(Archive& ar, Collection& ob)\n");
	//ar << *dynamic_cast<Object *>(&ob);
	DWORD version = ob.Object::Serialize(ar);
	switch (version)
	{
	case 1:
		{
			// Objects' vectors
			ar << ob.m_objects;			ar << ob.m_objects_ObjectList;
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
Archive& operator >>(Archive& ar, Collection& ob)
{
//printf("Archive& operator >>(Archive& ar, Collection& ob)\n");
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
			// Objects' vectors
			ar >> ob.m_objects;			ar >> ob.m_objects_ObjectList;
			ob.m_objects_ObjectList.Init(ob.m_objects, &ob);
		}
		break;
	default:
		{
			throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
//printf("Archive& operator >>(Archive& ar, Collection& ob) end\n");
	return ar;
}
