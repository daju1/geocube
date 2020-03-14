#if !defined(AFX_OBJECT_H__4ECD2B30_7555_4658_B548_041DDC56742B__INCLUDED_)
#define AFX_OBJECT_H__4ECD2B30_7555_4658_B548_041DDC56742B__INCLUDED_

#pragma once
class ObjectList;
//class Object;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include "Object.h"
#endif
#include "points.h"

class WhatSelected
{
//	friend class project;
	Object * m_ob;// указатель на выбранный объет, тип объекта можно получить, использу€ этот указатель
//	ObjectList * m_ob_list;// указатель на выбранный объет, тип объекта можно получить, использу€ этот указатель
	CPoint3 m_pt_view;// точка выбора в 3-х мерном пространстве

	//CPoint3 m_pt_doc;// точка выбора в 3-х мерном пространстве
	int m_i_selected_element;
	int m_i_selected_element2;
//	void * pContainer;
//	Object::container_type m_container_type;

	vector<Object *> m_all_selected_objects;

public:
	CPoint3 GetViewPointOfSelection(){return  m_pt_view;}
	Object * GetObject(){return m_ob;}
	int GetIndex(){return m_i_selected_element;}
	enum selected_objects_element_type {
		sel_no_element = 0, 
		sel_point, 
		sel_lito_ige, 
		sel_line, 
		sel_tria_plane, 
		sel_quad_plane, 
		sel_poly_pane,
		sel_well, 
	};

	selected_objects_element_type m_selected_objects_element_type;
	selected_objects_element_type m_what_to_select;


	void AddSelectedObject(Object * ob);
	void RemoveSelectedObject(Object * ob);

	void Init(
		Object * ob, 		 
		WhatSelected::selected_objects_element_type selected_element_t, 
		int i_selected_element,
		int i_selected_element2,
		CPoint3 pt_view
		//, CPoint3 pt_doc
		); 
	/*void InitObjectList(
		void * p_container, 
		Object::container_type container_t,
		ObjectList * ob_list
		);*/
	void PrintInfo();

	WhatSelected(void);
	virtual ~WhatSelected(void);

	template <class T> void EraseSelectedObject(HWND hwndTV, Object::object_type ob_type) ;

};
template <class T> void WhatSelected::EraseSelectedObject(HWND hwndTV, Object::object_type ob_type) 
{
	this->PrintInfo();
	if (this->m_ob)
	{
		ObjectList * oblist = this->m_ob->GetObjectList();
		void * pContainer = this->m_ob->GetObjectList()->GetContainer();
		Object * parent = this->m_ob->GetObjectList()->GetParent();

		if (oblist && pContainer && parent && this->m_ob->GetObjectType() == ob_type)
		{
			T * pob = dynamic_cast<T*>(this->m_ob);
			if (pob && pContainer)
			{
				if (oblist->GetContainerType() == Object::container_type::container_vect)
				{
					vect<T> * pvect = reinterpret_cast<vect<T> *>(pContainer);
					if(TreeView_DeleteItem(hwndTV, pob->myTreeItem))
					{
						if (pvect->SetCurrentMsgOnFirst())
						{
							do
							{
								//if (!pvect->CheckCurrentMsg()) break;
								if (pob == &pvect->GetCurrentMsg())
								{
									pvect->EraseCurrentMsg();
									break;
								}
							}
							while(pvect->IncrementCurrentMsg());
						}
						oblist->Init(*pvect, parent);
					}
				}
			}
		}
	}
};

#endif
