// ObjectList.cpp: implementation of the ObjectList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjectList.h"
#include "..\..\tools\src\filedlg.h"
#include ".\objectlist.h"
#include ".\Archive.h"
#include "SurfDoc.h"



using namespace std;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern int ChooseSurfColor(HWND hwndOwner, COLORREF& color);

ObjectList::ObjectList()
{
	this->m_bIsObjectList = true;
	this->myTreeItem = NULL;
	this->m_bExpanded	= true;

	this->m_object_type = Object::object_type::object_list;
	this->m_object_version = 0;
	this->m_max_object_version = 0;
}

ObjectList::~ObjectList()
{

}

void ObjectList::PropertiesDialog()
{
	MessageBox(0, "PropertiesDialog", "ObjectList" , 0);

}
//====== Операция присвоения
ObjectList& ObjectList::operator=(const ObjectList &obl)
{
	if (this == &obl)
		return *this;

	dynamic_cast<Object*>(this)->Init(obl);
	this->Initialize(obl);

	return *this;
}	

ObjectList::ObjectList(const ObjectList &obl)
{
	dynamic_cast<Object*>(this)->Init(obl);
	this->Initialize(obl);
}

void ObjectList::Initialize(const ObjectList &obl)
{
	this->oblist = obl.oblist;
	for (vector<Object *>::iterator iter = this->oblist.begin();
		iter != this->oblist.end(); iter++)
	{
		(*iter)->m_pObjectList = this;
	}
}

bool ObjectList::ColorDialog(void)
{
	bool status = false;
	vector<Object *>::iterator iter;
	iter = this->oblist.begin();
	if (iter != this->oblist.end())
	{
		COLORREF color = (*iter)->GetColor();
		status = ChooseSurfColor(NULL, color) == 0;
		for (iter = this->oblist.begin() ;iter != this->oblist.end(); iter++)
		{
			(*iter)->SetColor(color);
		}
	}
	return status;
}

COLORREF ObjectList::GetColor(void)
{
	return COLORREF();
}

void ObjectList::SetColor(COLORREF color)
{
}

void ObjectList::SetLayer(const Layer* layer)
{
	this->Object::SetLayer_NonVirtual(layer);
	for (vector<Object *>::iterator iter = this->oblist.begin() ;iter != this->oblist.end(); iter++)
	{
		(*iter)->SetLayer(layer);
	}
}
SSaveProfData ObjectList::sprData;
// DIME: needed include files.
#include <dime/Model.h>
#include <dime/sections/BlocksSection.h>
#include <dime/tables/LayerTable.h>
#include <dime/dxfwriter.h>
#include "CrdTranslator.h"
bool ObjectList::SaveAsDxf(dimeModel * model, dimeBlock * block, CrdTranslator * translator)
{
	if (!model) return false;
	bool status = false;
	vector<Object *>::iterator iter;
	for (iter = this->oblist.begin() ;iter != this->oblist.end(); iter++)
	{
		if((*iter)->SaveAsDxf(model, block, translator))
			status = true;
	}
	return true;

}
bool ObjectList::SaveAs()
{
	bool status = false;
	TCHAR lpstrFile[256]; lpstrFile[0] = '\0';
	
	TCHAR filter[] =    
		TEXT("AutoCAD DXF(*.dxf)\0*.dxf\0")
		TEXT("Golden Software Blanking (*.bln)\0*.bln\0")
		TEXT("Golden Software Data (*.dat)\0*.dat\0")
		TEXT("All Files (*.*)\0*.*\0");

	//sprintf(lpstrFile, "%s\\razrez", directory);
	DWORD nFilterIndex = 0;
	if (SaveProfDlg(0, lpstrFile, filter, nFilterIndex, ObjectList::sprData) != S_OK)
		return status;

	CrdTranslator translator;

	if (!InitTranslator(translator, ObjectList::sprData))
	{
		MessageBox(0, "Can not save this projection\nSelect another", "ObjectList SaveAs", 0);
		return false;
	}
	if (nFilterIndex == 1)
	{
		status = this->Object::SaveAsDxf(lpstrFile,&translator);
	}
	else
	{		
		FILE *stream;
		stream = fopen(lpstrFile,"wt");
		if (!stream)
		{
			return status;
		}
		vector<Object *>::iterator iter;
		switch (nFilterIndex)
		{
		case 2:
			for (iter = this->oblist.begin() ;iter != this->oblist.end(); iter++)
			{
				status = (*iter)->SaveAsBln(stream, translator);
			}
			break;
		case 3:
			for (iter = this->oblist.begin() ;iter != this->oblist.end(); iter++)
			{
				status = (*iter)->SaveAsDat(stream);
			}
			break;
		}
		fclose (stream);

	}
	return status;
}

bool ObjectList::DeleteUnchecked()
{
	Object * parent = this->GetParent();
	void * pContainer;
	Object::container_type type_of_container;

	pContainer = this->GetContainer();
	type_of_container = this->GetContainerType();
	vector<Object*>::iterator it = oblist.begin();


	if (it != oblist.end() && (*it))
	{
		Object::object_type ob_object_type = (*it)->GetObjectType();
		char str[1024];
		sprintf(str, "Вы действительно хотите удалить выключенные объекты %s у родителя %s \"%s\"?", 
			Object::ObjectTypeToString(ob_object_type),
			parent != NULL ? Object::ObjectTypeToString(parent->GetObjectType()) : "",
			parent != NULL ? parent->GetName().c_str() : "");

		if (IDNO == MessageBox(0, str, "ObjectList::DeleteUnchecked()", MB_YESNO))
		{
			return false;
		}
		if(type_of_container == Object::container_type::container_vect)
		{
			switch(ob_object_type)
			{
			case object_type::object_list:
				DeletingUnchecked_from_vect<ObjectList>(
					reinterpret_cast<vect<ObjectList>*>(pContainer), 
					parent);
				return true;

			case object_type::thepoint3d:
				DeletingUnchecked_from_vect<ThePoint3D>(
					reinterpret_cast<vect<ThePoint3D>*>(pContainer), 
					parent);
				return true;
			case object_type::line3d:
				if(this->m_pSurfDoc) this->m_pSurfDoc->SetLineForDraw(NULL); 
				DeletingUnchecked_from_vect<Line3D>(
					reinterpret_cast<vect<Line3D>*>(pContainer), 
					parent);
				return true;
			case object_type::inter_wells_line_3d:
				DeletingUnchecked_from_vect<InterWellsLine3D>(
					reinterpret_cast<vect<InterWellsLine3D>*>(pContainer), 
					parent);
				return true;
			case object_type::surface3d:
				DeletingUnchecked_from_vect<Surface3D>(
					reinterpret_cast<vect<Surface3D>*>(pContainer), 
					parent);
				return true;
			case object_type::cube4d:
				DeletingUnchecked_from_vect<Cube4D>(
					reinterpret_cast<vect<Cube4D>*>(pContainer), 
					parent);
				return true;
			case object_type::triangle3d:
				DeletingUnchecked_from_vect<Triangle3D>(
					reinterpret_cast<vect<Triangle3D>*>(pContainer), 
					parent);
				return true;
			case object_type::poligon3d:
				DeletingUnchecked_from_vect<Poligon3D>(
					reinterpret_cast<vect<Poligon3D>*>(pContainer), 
					parent);
				return true;
			case object_type::sphere3d:
				DeletingUnchecked_from_vect<Sphere3D>(
					reinterpret_cast<vect<Sphere3D>*>(pContainer), 
					parent);
				return true;
			case object_type::string3d:
				DeletingUnchecked_from_vect<String3D>(
					reinterpret_cast<vect<String3D>*>(pContainer), 
					parent);
				return true;
			case object_type::well_3d:
				DeletingUnchecked_from_vect<Well_3D>(
					reinterpret_cast<vect<Well_3D>*>(pContainer), 
					parent);
				return true;
			case object_type::karotazh:
				DeletingUnchecked_from_vect<Karotazh>(
					reinterpret_cast<vect<Karotazh>*>(pContainer), 
					parent);
				return true;
			case object_type::bmp3d:
				DeletingUnchecked_from_vect<Bmp3D>(
					reinterpret_cast<vect<Bmp3D>*>(pContainer), 
					parent);
				return true;

			case object_type::bln_profile3d:
				DeletingUnchecked_from_vect<BlnProfile3D>(
					reinterpret_cast<vect<BlnProfile3D>*>(pContainer), 
					parent);
				return true;
			case object_type::bln_profile_plane3d:
				DeletingUnchecked_from_vect<BlnProfilePlane3D>(
					reinterpret_cast<vect<BlnProfilePlane3D>*>(pContainer), 
					parent);
				return true;

			case object_type::broken_plane3d:
				DeletingUnchecked_from_vect<BrokenPlane3D>(
					reinterpret_cast<vect<BrokenPlane3D>*>(pContainer), 
					parent);
				return true;
			case object_type::broken_line3d:
				DeletingUnchecked_from_vect<BrokenLine3D>(
					reinterpret_cast<vect<BrokenLine3D>*>(pContainer), 
					parent);
				return true;
			case object_type::broken_poligon3d:
				DeletingUnchecked_from_vect<BrokenPoligon3D>(
					reinterpret_cast<vect<BrokenPoligon3D>*>(pContainer), 
					parent);
				return true;
			case object_type::broken_poligon_3d:
				DeletingUnchecked_from_vect<BrokenPoligon_3D>(
					reinterpret_cast<vect<BrokenPoligon_3D>*>(pContainer), 
					parent);
				return true;

			case object_type::grid_profile3d:
				DeletingUnchecked_from_vect<GridProfile3D>(
					reinterpret_cast<vect<GridProfile3D>*>(pContainer), 
					parent);
				return true;
			case object_type::triangulated_grid3d:
				DeletingUnchecked_from_vect<TriangulatedGrid3D>(
					reinterpret_cast<vect<TriangulatedGrid3D>*>(pContainer), 
					parent);
				return true;

			case object_type::geo_surface:
				DeletingUnchecked_from_vect<GeoSurface>(
					reinterpret_cast<vect<GeoSurface>*>(pContainer), 
					parent);
				return true;
			case object_type::geo_catch:
				DeletingUnchecked_from_vect<GeoCatch>(
					reinterpret_cast<vect<GeoCatch>*>(pContainer), 
					parent);
				return true;
			case object_type::grid_data:
				if(this->m_pSurfDoc) this->m_pSurfDoc->SetGridDataForDraw(NULL); 
				DeletingUnchecked_from_vect<GridData>(
					reinterpret_cast<vect<GridData>*>(pContainer), 
					parent);
				return true;
			case object_type::collection:
				DeletingUnchecked_from_vect<Collection>(
					reinterpret_cast<vect<Collection>*>(pContainer), 
					parent);
				return true;
			case object_type::auto_profile_building:
				DeletingUnchecked_from_vect<AutoBuildProfile>(
					reinterpret_cast<vect<AutoBuildProfile>*>(pContainer), 
					parent);
				return true;
#if DFX_LAYER_FROM_OBJECT
			case object_type::dfx_layerdata:
				DeletingUnchecked_from_vect<dxfLayerData>(
					reinterpret_cast<vect<dxfLayerData>*>(pContainer), 
					parent);
				return true;
			case object_type::dfx_converter:
				DeletingUnchecked_from_vect<dxfConverter>(
					reinterpret_cast<vect<dxfConverter>*>(pContainer), 
					parent);
				return true;
#endif
			case object_type::fast_collection:
				DeletingUnchecked_from_vect<FastCollection>(
					reinterpret_cast<vect<FastCollection>*>(pContainer), 
					parent);
				return true;
			/*case object_type::surf_doc:
				DeletingUnchecked_from_vect<T>(
					reinterpret_cast<vect<T>*>(pContainer), 
					dynamic_cast<T*>(This));
				pObjectList->Init(*reinterpret_cast<vect<T>*>(pContainer), parent);		
				return true;*/

			default:
				{
					return false;
				}

			}
		}
	}
	return false;
}

void ObjectList::FillContextMenu(HMENU& hMenu)
{
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_STRING, ID_TREE_OBJECTLISTDELETEUNCHECKED, "&Delete Unchecked" );
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );
#endif /*#if !VIEW_ONLY_VERSION*/
	this->Object::FillContextMenu(hMenu);
}

Archive& operator <<(Archive& ar, ObjectList& ob)
{
	//ar << *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	DWORD version = ob.m_object_version;
	switch (version)
	{
	case 1:
		{
		}
		break;
	default:
		{
			//throw VersionException(version, VersionException::cannot_store, ob.m_object_type);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, ObjectList& ob)
{
	//ar >> *dynamic_cast<Object *>(&ob);
	ob.Object::Serialize(ar);
	switch (ob.m_object_version)
	{
	case 1:
		{
		}
		break;
	default:
		{
			//throw VersionException(ob.m_object_version, VersionException::cannot_load, ob.m_object_type);
		}
		break;
	}
	return ar;
}


