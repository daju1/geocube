#include "stdafx.h"
#include ".\whatselected.h"
#include "Object.h"
#include <algorithm>

WhatSelected::WhatSelected(void)
{
//	this->pContainer						= NULL;
//	this->m_container_type					= Object::container_type::container_none;
	this->m_ob								= NULL;
//	this->m_ob_list							= NULL;
	this->m_selected_objects_element_type	= selected_objects_element_type::sel_no_element;
	this->m_what_to_select					= selected_objects_element_type::sel_no_element;
	this->m_i_selected_element				= -1;
	this->m_i_selected_element2				= -1;
}

WhatSelected::~WhatSelected(void)
{
}
/*void WhatSelected::InitObjectList(
	void * p_container, 
	Object::container_type container_t,
	ObjectList * ob_list)
{
	this->pContainer						= p_container;
	this->m_container_type					= container_t;
	this->m_ob_list							= ob_list;
}*/
void WhatSelected::Init(
	Object * ob,
	WhatSelected::selected_objects_element_type selected_element_t,
	int i_selected_element,
	int i_selected_element2,
	CPoint3 pt_view
	//, CPoint3 pt_doc
	)
{
	this->m_ob								= ob;
//	this->pContainer						= NULL;
//	this->m_container_type					= Object::container_type::container_none;
	this->m_selected_objects_element_type	= selected_element_t;
	this->m_i_selected_element				= i_selected_element;
	this->m_i_selected_element2				= i_selected_element2;
	this->m_pt_view							= pt_view;
	//this->m_pt_doc							= pt_doc;
}
void WhatSelected::PrintInfo()
{
	printf(
		"WhatSelected::PrintInfo()"
		"m_ob = %x\n"
//		"pContainer = %x\n"
//		"m_container_type = %d\n"
		"m_selected_objects_element_type = %d\n"
		"this->m_i_selected_element = %d\n"
		"this->m_i_selected_element = %d\n"
		"m_pt_view = [%f %f %f]\n"
		,
		this->m_ob,
//		this->pContainer,
//		this->m_container_type,
		this->m_selected_objects_element_type,
		this->m_i_selected_element,
		this->m_i_selected_element2,
		this->m_pt_view.x,
		this->m_pt_view.y,
		this->m_pt_view.z
		);

   vector<fmtstr> text;
   this->m_ob->PrintfProperties(text);
   vector<fmtstr>::iterator it = text.begin();
   vector<fmtstr>::iterator end = text.end();
   for (; it != end;++it)
   {
      printf("%s\n", (*it).String().c_str());
   }
}
void WhatSelected::AddSelectedObject(Object * ob)
{
	if(ob)
		this->m_all_selected_objects.push_back(ob);
}
void WhatSelected::RemoveSelectedObject(Object * ob)
{
	if (ob)
	{
		vector<Object*>::iterator result = find(
			this->m_all_selected_objects.begin(),
			this->m_all_selected_objects.end(), ob);
		this->m_all_selected_objects.erase(result);

	}
}
