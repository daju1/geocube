// ObjectList.h: interface for the ObjectList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECTLIST_H__E99C86F8_C8F8_447E_AC93_269A73F51C03__INCLUDED_)
#define AFX_OBJECTLIST_H__E99C86F8_C8F8_447E_AC93_269A73F51C03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../surfdefs.h"

#include "Object.h"
#include "../../array/src/Vector.h"
#include "../../array/src/vect.h"
#include "../../tools/src/filedlg.h"

class ObjectList;
#include <map>
#include <vector>
using namespace std;

class ObjectList  : public Object
{
	vector<Object *> oblist;
	void * pContainer;
	container_type m_container_type;

protected:
	void  Initialize(const ObjectList& obl );
public:
	void * GetContainer(){return pContainer;}
	container_type GetContainerType(){return m_container_type;}

	void clear(){this->oblist.clear();}
	ObjectList& operator=(const ObjectList &obl);
	ObjectList(const  ObjectList& obl );
	size_t size()
	{
		return oblist.size();
	}
	Object* operator[](size_t i)
	{
		return oblist[i];
	}
	virtual void PropertiesDialog();
	ObjectList();
	virtual ~ObjectList();

	bool SaveAs();
	bool SaveAsDat(FILE * stream)
	{
		return false;
	}
	bool SaveAsBln(FILE * stream)
	{
		return false;
	}
	virtual bool IsSelected(CPoint3 selected_view_pt, 
			double search_radius,
			WhatSelected& ws)
	{
		//search_radius = fabs(search_radius);
		return false;
	}
	virtual void Draw(){}
	virtual void ReDraw(){}

	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = NULL){return NULL;}
		

	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object* , WPARAM, LPARAM, void * ) ){}
	//template <class T> void Init0(T& ob);
	template <class T> void Init2(PLANE_MEMBERS_VECTOR<PLANE_MEMBERS_VECTOR<T> >& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_Vector_Vector;
		this->m_parent = parent;
		//number of objects in vector
		size_t n = ob.PLANE_MEMBERS_VECTOR_SIZE();
		size_t mn = 0;
		for (size_t i = 0; i < n; i++)
		{
			mn += ob[i].PLANE_MEMBERS_VECTOR_SIZE();
		}

		// resize 
		this->oblist.resize(mn);
		int k = 0;
		for (size_t i = 0; i < n; i++)
		{
			for ( size_t j = 0; j < ob[i].PLANE_MEMBERS_VECTOR_SIZE(); j++, k++)
			{
				this->oblist[k] = dynamic_cast<Object *>(&ob[i][j]);
				this->oblist[k]->m_pObjectList = this;
				this->oblist[k]->m_parent = parent;
			}
		}
	}
	template <class T> void Init2_std_vector_std_vector_ptr(std::vector<std::vector<T *> >& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_std_vector_std_vector;
		this->m_parent = parent;
		//number of objects in vector
		size_t n = ob.size();
		size_t mn = 0;
		for (size_t i = 0; i < n; i++)
		{
			for ( size_t j = 0; j < ob[i].size(); j++)
			{
				if (ob[i][j])
				{
                    ++mn;
				}
			}
		}

		// resize 
		this->oblist.resize(mn);
		int k = 0;
		for (size_t i = 0; i < n; i++)
		{
			for ( size_t j = 0; j < ob[i].size(); j++)
			{
				if (ob[i][j])
				{
					this->oblist[k] = dynamic_cast<Object *>(ob[i][j]);
					this->oblist[k]->m_pObjectList = this;
					this->oblist[k]->m_parent = parent;
					++k;
				}
			}
		}
	}
	template <class T> void Init2_SurfLineIntersectPoint(std::vector<std::vector<T> >& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_std_vector_std_vector;
		this->m_parent = parent;
		//number of objects in vector
		size_t n = ob.size();
		size_t mn = 0;
		for (size_t i = 0; i < n; i++)
		{
			mn += ob[i].size();
		}

		// resize 
		this->oblist.resize(mn);
		int k = 0;
		for (size_t i = 0; i < n; i++)
		{
			for ( size_t j = 0; j < ob[i].size(); j++, k++)
			{
				this->oblist[k] = dynamic_cast<Object *>(&ob[i][j].point);
				this->oblist[k]->m_pObjectList = this;
				this->oblist[k]->m_parent = parent;
			}
		}
	}
	template <class T> void Init_std_vector_Vector(vector<T>& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_std_vector_std_vector;
		this->m_parent = parent;
		//number of objects in vector
		size_t n = ob.size();
		size_t mn = 0;
		for (size_t i = 0; i < n; i++)
		{
			mn += ob[i].Size();
		}

		// resize 
		this->oblist.resize(mn);
		int k = 0;
		for (size_t i = 0; i < n; i++)
		{
			for ( size_t j = 0; j < ob[i].Size(); j++, k++)
			{
				this->oblist[k] = dynamic_cast<Object *>(&ob[i][j]);
				this->oblist[k]->m_pObjectList = this;
				this->oblist[k]->m_parent = parent;
			}
		}
	}
	template <class T> void Init1(PLANE_MEMBERS_VECTOR<T>& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_Vector;
		this->m_parent = parent;
		//number of objects in vector
		size_t n = ob.PLANE_MEMBERS_VECTOR_SIZE();
		// resize 
		this->oblist.resize(n);
		for (size_t i = 0; i < n; i++)
		{
			this->oblist[i] = dynamic_cast<Object *>(&ob[i]);
			this->oblist[i]->m_pObjectList = this;
			this->oblist[i]->m_parent = parent;
		}
	}
	template <class T> void Init_std_vector(vector<T>& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_std_vector;
		this->m_parent = parent;
		//number of objects in vector
		size_t n = ob.size();
		// resize 
		this->oblist.resize(n);
		for (size_t i = 0; i < n; i++)
		{
			this->oblist[i] = dynamic_cast<Object *>(&ob[i]);
			this->oblist[i]->m_pObjectList = this;
			this->oblist[i]->m_parent = parent;
		}
	}
	template <class K, class T> void Init_std_map(map<K,T>& m, Object * parent)
	{
		this->pContainer = &m;
		this->m_container_type = Object::container_type::container_std_map;
		this->m_parent = parent;
		//number of objects in map
		size_t n = m.size();
		// resize 
		this->oblist.resize(n);
		map <K, T>::iterator iter;
		size_t i;
		for ( iter = m.begin( ), i = 0; 
			iter != m.end( ) && i < this->oblist.size(); 
			iter++, i++ )
		{
			this->oblist[i] = dynamic_cast<Object *>(&(*iter).second);
			this->oblist[i]->m_pObjectList = this;
			this->oblist[i]->m_parent = parent;
		}
	}
	template <class T, class VITEM> void Init(vect<T, VITEM>& ob, Object * parent)
	{
		this->pContainer = &ob;
		this->m_container_type = Object::container_type::container_vect;
		this->m_parent = parent;
		this->oblist.clear();

		if ( ob.SetCurrentMsgOnFirst())
		{
			do
			{
				if (ob.CheckCurrentMsg())
				{
					T* ptr = ob.GetCurrentMsgPtr();
					//if (ptr)
					//{
						size_t len = ob.GetCurrentMsgLen();
						for(size_t i = 0;	i < len; i++)
						{
							this->oblist.push_back(dynamic_cast<Object *>(&ptr[i]));
							this->oblist.back()->m_pObjectList = this;
							this->oblist.back()->m_parent = parent;
						}
					//}
				}
			}
			while(ob.IncrementCurrentMsg());
		}
		if (ob.SetCurrentVectOnFirst())
		{
			do
			{
				this->Init(ob.GetCurrentVect(), parent);
			}
			while(ob.IncrementCurrentVect());
		}
	}

	virtual bool ColorDialog(void);
	virtual COLORREF GetColor(void);
	virtual void SetColor(COLORREF color);
	virtual void SetLayer(const Layer* layer);//override in ObjectList

	virtual bool UpdateExtremums(){return false;}
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean){}
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d){}
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z){}
	
	void FillContextMenu(HMENU& hMenu);
	bool DeleteChecked();
	bool DeleteUnchecked();

	friend Archive& operator <<(Archive& ar, ObjectList& ob);
	friend Archive& operator >>(Archive& ar, ObjectList& ob);

	bool SaveAsDxf(dimeModel * model, dimeBlock * block, CrdTranslator * translator);

	static SSaveProfData sprData;

template <class T> void DeletingChecked_from_vect(vect<T> * v, Object* parent); 
template <class T> void DeletingUnchecked_from_vect(vect<T> * v, Object* parent); 

};
#include "winsurftree.h"

template <class T> void ObjectList::DeletingChecked_from_vect(vect<T> * v, Object* parent) 
{
	// удаляем все отключенные и пустые объекты линий бланкования
	if (v->SetCurrentMsgOnFirst())
	{
		do
		{
e_start_of_objectlist_cicle:
			//if (!v->CheckCurrentMsg()) break; // may be continue;??? if will not erase all
			if (v->GetCurrentMsg().m_bChecked)
			{
				if (this->m_pSurfDoc)
					TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, 
					v->GetCurrentMsg().myTreeItem);
				if (v->EraseCurrentMsg())
						goto e_start_of_objectlist_cicle;
			}
		}
		while(v->IncrementCurrentMsg());
		this->Init(*v, parent);
	}
}

template <class T> void ObjectList::DeletingUnchecked_from_vect(vect<T> * v, Object* parent) 
{
	// удаляем все отключенные и пустые объекты линий бланкования
	if (v->SetCurrentMsgOnFirst())
	{
		do
		{
e_start_of_objectlist_cicle:
			if (!v->CheckCurrentMsg()) break; // may be continue;??? if will not erase all
			if (!v->GetCurrentMsg().m_bChecked)
			{
				if (this->m_pSurfDoc)
					TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, 
					v->GetCurrentMsg().myTreeItem);
				if (v->EraseCurrentMsg())
						goto e_start_of_objectlist_cicle;
			}
		}
		while(v->IncrementCurrentMsg());
		this->Init(*v, parent);
	}
}


#endif // !defined(AFX_OBJECTLIST_H__E99C86F8_C8F8_447E_AC93_269A73F51C03__INCLUDED_)
