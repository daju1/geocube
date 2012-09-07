#include "stdafx.h"
#include ".\FastCollection.h"
#include ".\archive.h"
#include "surfdoc.h"
#include "winsurftree.h"

FastCollection::FastCollection()
{
	m_pSurfDoc = NULL;
	OnCreate();
}

FastCollection::FastCollection(SurfDoc* pSurfDoc)
{
	this->m_pSurfDoc				= pSurfDoc;
	OnCreate();
}

void FastCollection::OnCreate(void)
{
	this->m_object_type = Object::object_type::fast_collection;
	this->m_object_version = 1;
	this->m_max_object_version = 1;

	this->m_objects.OnCreate();
}

FastCollection::FastCollection(const FastCollection & bp)
{
	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);
}
FastCollection& FastCollection::operator=(const FastCollection& bp)
{
	if (this == &bp)
	{
		return *this;
	}

	dynamic_cast<Object*>(this)->Init(bp);
	this->Init(bp);

	return *this;
}

FastCollection::~FastCollection(void)
{
}

Object * FastCollection::AddObject(Primitive3D<CPoint3> * object)
{
//printf("FastCollection::AddObject\n");
	if (object)
	{
		this->m_objects.AddMsg(object);
		//this->m_objects_ObjectList.Init(this->m_objects, this);
		return &this->m_objects.GetLastMsg();
	}
	return NULL;
}
void FastCollection::InitObjectList()
{
	this->m_objects_ObjectList.Init(this->m_objects, this);
}

bool FastCollection::UpdateExtremums()
{
//printf("FastCollection::UpdateExtremums\n");
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

void FastCollection::Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean)
{
//printf("FastCollection::Zoom\n");	
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
HTREEITEM FastCollection::AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s)
{
    char szItemText[1024]; // label text of tree-view item 
	//====== Размеры изображаемого объекта
	UINT n_objects = this->m_objects.msgSize();	

	sprintf(szItemText, "\"%s\" FastCollection of %d objects",this->GetName().c_str(), n_objects );
	Object * pObject = dynamic_cast<Object *> (this);
	//=============================================================
	// Add the item to the tree-view control. 
	HTREEITEM h2 = AddItemToTree(hwndTV, szItemText, pObject, h1); 
	//=============================================================
	return h2;
}



void FastCollection::Draw()
{
	m_nglListNumber = DrawListArray::glNewList();
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().Drawing();
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	glEndList();
}

void FastCollection::ReDraw()
{
	if(this->m_pSurfDoc) this->ReDrawItem_OnTree(this->m_pSurfDoc->hwndTV);

	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
		::glNewList(m_nglListNumber, GL_COMPILE);
	}
	else
		m_nglListNumber = DrawListArray::glNewList();

	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().Drawing();
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	glEndList();
}

bool FastCollection::IsSelected(CPoint3 selected_view_pt, 
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

void FastCollection::EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM , LPARAM, void * ) )
{
	if ((this->*condition_fun)())
	{
		(* callback_fun)(this, wParam, lParam, p);
	}
	/*
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().EnumObjects(wParam,lParam,p,condition_fun, callback_fun);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}*/
}

void FastCollection::SetLayer(const Layer* layer)
{
	this->SetLayer_NonVirtual(layer);
	/*if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			this->m_objects.GetCurrentMsg().SetLayer(layer);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}*/
}
void FastCollection::FillContextMenu(HMENU& hMenu)
{
	this->Object::FillContextMenu(hMenu);
#if !VIEW_ONLY_VERSION
#endif /*!VIEW_ONLY_VERSION*/
}

bool FastCollection::SaveAs()
{
	bool status = false;
	TCHAR lpstrFile[256];
	TCHAR filter[] =    
		TEXT("Golden Software Data (*.dat)\0*.dat\0")
		TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("All Files (*.*)\0*.*\0");

	sprintf(lpstrFile, "%s\\%s", directory, this->GetName().c_str());
	sprintf(lpstrFile, "\0");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, lpstrFile, filter, nFilterIndex) != S_OK)
		return status;
	FILE *stream;
	stream = fopen(lpstrFile,"wt");
	if (!stream)
	{
		return status;
	}
	switch (nFilterIndex)
	{
	case 1:
		status = SaveAsDat(stream);
		break;
	case 2:
		status = SaveAsBln(stream);
		break;
	}
	fclose (stream);
	return status;
}

bool FastCollection::SaveAsDat(FILE * stream)
{
	bool status = false;
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			status = this->m_objects.GetCurrentMsg().SaveAsDat(stream);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	return status;
}
bool FastCollection::SaveAsBln(FILE * stream)
{
	bool status = false;
	if (this->m_objects.SetCurrentMsgOnFirst())
	{
		do
		{
			status = this->m_objects.GetCurrentMsg().SaveAsBln(stream);
		}
		while(this->m_objects.IncrementCurrentMsg());
	}
	return status;
}
void FastCollection::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "FastCollection" , 0);
}

bool FastCollection::ColorDialog(void)
{
	return false;
}

COLORREF FastCollection::GetColor(void)
{
	return COLORREF();
}

void FastCollection::SetColor(COLORREF color)
{
}

void FastCollection::CutAndDisvisible(bool positive, double a, double b, double c, double d)
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

void FastCollection::CutXYZandDisvisible(int subcube_number, double X, double Y, double Z)
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

Archive& operator <<(Archive& ar, FastCollection& ob)
{
//printf("Archive& operator <<(Archive& ar, FastCollection& ob)\n");
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
Archive& operator >>(Archive& ar, FastCollection& ob)
{
//printf("Archive& operator >>(Archive& ar, FastCollection& ob)\n");
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
//printf("Archive& operator >>(Archive& ar, FastCollection& ob) end\n");
	return ar;
}
