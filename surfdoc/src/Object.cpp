// Object.cpp: implementation of the Object class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Object.h"
#include ".\archive.h"
#include "..\..\wintools\src\SelectLayerDlg.h"
#include "..\..\wintools\src\win32_dialog.h"
#include "winsurftree.h"

#include "SurfDoc.h"
#include "points.h"

extern HINSTANCE hInst;
/*
#ifdef _DEBUG
inline void * __cdecl operator new(size_t size)
{
	void *p = (void *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,size);
	printf("inline void * __cdecl operator new size_t size = %u\tp = 0x%08x\n",size, p);
	return (p);      
}  

inline void __cdecl operator delete(void *p)
{
	printf("inline void __cdecl operator delete(void *p) p = 0x%08x\n", p);
	HeapFree(GetProcessHeap(), 0, p);
}
#endif

*/

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD Object::s_UserID_forCompare = 0;
string Object::s_name_forCompare = "";
bool Object::s_canDisableDepthTest = false;
DWORD Object::s_max_base_version = 2;

const char * Object::ObjectTypeToString(object_type type)
{
	switch (type)
	{
	case object_type::undefined:
		return "Undefined";

	case object_type::object:
		return "object";
	case object_type::object_list:
		return "object_list";

	case object_type::geo_colomn:
		return "geo_colomn";
	case object_type::well_colomn:
		return "well_colomn";

	case object_type::primitive3d:
		return "primitive 3D";

	case object_type::thepoint3d:
		return "thepoint 3D";
	case object_type::line3d:
		return "Line 3D";
	case object_type::inter_wells_line_3d:
		return "Inter Wells Line 3D";		
	case object_type::surface3d:
		return "surface 3D";
	case object_type::cube4d:
		return "cube 4D";
	case object_type::triangle3d:
		return "triangle 3D";
	case object_type::poligon3d:
		return "poligon 3D";
	case object_type::sphere3d:
		return "sphere 3D";
	case object_type::string3d:
		return "string 3D";
	case object_type::well_3d:
		return "well_3D";
	case object_type::karotazh:
		return "karotazh";
	case object_type::bmp3d:
		return "bmp3D";

	case object_type::bln_profile3d:
		return "bln_profile 3D";
	case object_type::bln_profile_plane3d:
		return "bln_profile_plane3d";

	case object_type::broken_plane3d:
		return "broken_plane3d";
	case object_type::broken_line3d:
		return "broken_line3d";
	case object_type::broken_poligon3d:
		return "broken_poligon3d";
	case object_type::broken_poligon_3d:
		return "broken_poligon_3d";

	case object_type::grid_profile3d:
		return "grid_profile3d";
	case object_type::triangulated_grid3d:
		return "triangulated_grid3d";

	case object_type::geo_surface:
		return "Geo Surface";
	case object_type::geo_catch:
		return "Geo Catch";
	case object_type::grid_data:
		return "Grid Data";
	case object_type::collection:
		return "Collection";
	case object_type::auto_profile_building:
		return "auto_profile_building";

#if DFX_LAYER_FROM_OBJECT
	case object_type::dfx_layerdata:
		return "dfx_layerdata";
	case object_type::dfx_converter:
		return "dfx_converter";
#endif
	case object_type::fast_collection:
		return "fast_collection";


	case object_type::surf_doc:
		return "Surf Doc";

	default:
		return "";
	}
	return "";
}


void* Object::operator new  (size_t size, object_type type)
{
	//printf("Object::operator new(size_t size = %d, object_type type = %s\n", size, Object::ObjectTypeToString(type));
	switch (type)
	{
	case object_type::object_list:
		return reinterpret_cast<void*>(new ObjectList);

	case object_type::geo_colomn:
		return reinterpret_cast<void*>(new GeoColomn);
//	case object_type::well_colomn:
//		return reinterpret_cast<void*>(new WellColomn);

	case object_type::thepoint3d:
		return reinterpret_cast<void*>(new ThePoint3D);
	case object_type::line3d:
		return reinterpret_cast<void*>(new Line3D);
	case object_type::inter_wells_line_3d:
		return reinterpret_cast<void*>(new InterWellsLine3D );
	case object_type::surface3d:
		return reinterpret_cast<void*>(new Surface3D );
	case object_type::cube4d:
		return reinterpret_cast<void*>(new Cube4D );
	case object_type::triangle3d:
		return reinterpret_cast<void*>(new Triangle3D );
	case object_type::poligon3d:
		return reinterpret_cast<void*>(new Poligon3D );
	case object_type::sphere3d:
		return reinterpret_cast<void*>(new Sphere3D );
	case object_type::string3d:
		return reinterpret_cast<void*>(new String3D );
	case object_type::well_3d:
		return reinterpret_cast<void*>(new Well_3D );
	case object_type::karotazh:
		return reinterpret_cast<void*>(new Karotazh );
	case object_type::bmp3d:
		return reinterpret_cast<void*>(new Bmp3D );

	case object_type::bln_profile3d:
		return reinterpret_cast<void*>(new BlnProfile3D );
	case object_type::bln_profile_plane3d:
		return reinterpret_cast<void*>(new BlnProfilePlane3D );

	case object_type::broken_plane3d:
		return reinterpret_cast<void*>(new BrokenPlane3D );
	case object_type::broken_line3d:
		return reinterpret_cast<void*>(new BrokenLine3D );
	case object_type::broken_poligon3d:
		return reinterpret_cast<void*>(new BrokenPoligon3D );
	case object_type::broken_poligon_3d:
		return reinterpret_cast<void*>(new BrokenPoligon_3D );

	case object_type::grid_profile3d:
		return reinterpret_cast<void*>(new GridProfile3D );
	case object_type::triangulated_grid3d:
		return reinterpret_cast<void*>(new TriangulatedGrid3D );

	case object_type::geo_surface:
		return reinterpret_cast<void*>(new GeoSurface );
	case object_type::geo_catch:
		return reinterpret_cast<void*>(new GeoCatch );
	case object_type::grid_data:
		return reinterpret_cast<void*>(new GridData );
	case object_type::collection:
		return reinterpret_cast<void*>(new Collection );
	case object_type::auto_profile_building:
		return reinterpret_cast<void*>(new AutoBuildProfile );

#if DFX_LAYER_FROM_OBJECT
//	case object_type::dfx_layerdata:
//		return reinterpret_cast<void*>(new dxfLayerData );
	case object_type::dfx_converter:
		return reinterpret_cast<void*>(new dxfConverter );
#endif
	case object_type::fast_collection:
		return reinterpret_cast<void*>(new FastCollection );


	case object_type::surf_doc:
		return reinterpret_cast<void*>(new SurfDoc );

	default:
		return NULL;
	}
	return NULL;
}
void* Object::operator new[](size_t len, object_type type)
{
	//printf("Object::operator new[](size_t len = %d, object_type type = %s\n", len, Object::ObjectTypeToString(type));
	switch (type)
	{
	case object_type::object_list:
		return reinterpret_cast<void*>(new ObjectList[len]);

	case object_type::geo_colomn:
		return reinterpret_cast<void*>(new GeoColomn[len]);
//	case object_type::well_colomn:
//		return reinterpret_cast<void*>(new WellColomn[len]);

	case object_type::thepoint3d:
		return reinterpret_cast<void*>(new ThePoint3D[len]);
	case object_type::line3d:
		return reinterpret_cast<void*>(new Line3D[len]);
	case object_type::inter_wells_line_3d:
		return reinterpret_cast<void*>(new InterWellsLine3D[len]);
	case object_type::surface3d:
		return reinterpret_cast<void*>(new Surface3D[len]);
	case object_type::cube4d:
		return reinterpret_cast<void*>(new Cube4D[len]);
	case object_type::triangle3d:
		return reinterpret_cast<void*>(new Triangle3D[len]);
	case object_type::poligon3d:
		return reinterpret_cast<void*>(new Poligon3D[len]);
	case object_type::sphere3d:
		return reinterpret_cast<void*>(new Sphere3D[len]);
	case object_type::string3d:
		return reinterpret_cast<void*>(new String3D[len]);
	case object_type::well_3d:
		return reinterpret_cast<void*>(new Well_3D[len]);
	case object_type::karotazh:
		return reinterpret_cast<void*>(new Karotazh[len]);
	case object_type::bmp3d:
		return reinterpret_cast<void*>(new Bmp3D[len]);

	case object_type::bln_profile3d:
		return reinterpret_cast<void*>(new BlnProfile3D[len]);
	case object_type::bln_profile_plane3d:
		return reinterpret_cast<void*>(new BlnProfilePlane3D[len]);

	case object_type::broken_plane3d:
		return reinterpret_cast<void*>(new BrokenPlane3D[len]);
	case object_type::broken_line3d:
		return reinterpret_cast<void*>(new BrokenLine3D[len]);
	case object_type::broken_poligon3d:
		return reinterpret_cast<void*>(new BrokenPoligon3D[len]);
	case object_type::broken_poligon_3d:
		return reinterpret_cast<void*>(new BrokenPoligon_3D[len]);

	case object_type::grid_profile3d:
		return reinterpret_cast<void*>(new GridProfile3D[len]);
	case object_type::triangulated_grid3d:
		return reinterpret_cast<void*>(new TriangulatedGrid3D[len]);

	case object_type::geo_surface:
		return reinterpret_cast<void*>(new GeoSurface[len]);
	case object_type::geo_catch:
		return reinterpret_cast<void*>(new GeoCatch[len]);
	case object_type::grid_data:
		return reinterpret_cast<void*>(new GridData[len]);
	case object_type::collection:
		return reinterpret_cast<void*>(new Collection[len]);
	case object_type::auto_profile_building:
		return reinterpret_cast<void*>(new AutoBuildProfile[len]);

#if DFX_LAYER_FROM_OBJECT
//	case object_type::dfx_layerdata:
//		return reinterpret_cast<void*>(new dxfLayerData[len] );
	case object_type::dfx_converter:
		return reinterpret_cast<void*>(new dxfConverter[len] );
#endif
	case object_type::fast_collection:
		return reinterpret_cast<void*>(new FastCollection[len]);


	case object_type::surf_doc:
		return reinterpret_cast<void*>(new SurfDoc[len]);

	default:
		return NULL;
	}
	return NULL;
}



	
void Object::operator delete(void*p, object_type type)
{
	switch (type)
	{
	case object_type::object_list:
		::operator delete(reinterpret_cast<ObjectList*>(p));
		break;

	case object_type::geo_colomn:
		::operator delete(reinterpret_cast<GeoColomn*>(p));
		break;

//	case object_type::well_colomn:
//		::operator delete(reinterpret_cast<WellColomn*>(p));
//		break;

	case object_type::thepoint3d:
		::operator delete(reinterpret_cast<ThePoint3D*>(p));
		break;
	case object_type::line3d:
		::operator delete(reinterpret_cast<Line3D*>(p));
		break;
	case object_type::inter_wells_line_3d:
		::operator delete(reinterpret_cast<InterWellsLine3D*>(p));
		break;
	case object_type::surface3d:
		::operator delete(reinterpret_cast<Surface3D*>(p));
		break;
	case object_type::cube4d:
		::operator delete(reinterpret_cast<Cube4D*>(p));
		break;
	case object_type::triangle3d:
		::operator delete(reinterpret_cast<Triangle3D*>(p));
		break;
	case object_type::poligon3d:
		::operator delete(reinterpret_cast<Poligon3D*>(p));
		break;
	case object_type::sphere3d:
		::operator delete(reinterpret_cast<Sphere3D*>(p));
		break;
	case object_type::string3d:
		::operator delete(reinterpret_cast<String3D*>(p));
		break;
	case object_type::well_3d:
		::operator delete(reinterpret_cast<Well_3D*>(p));
		break;
	case object_type::karotazh:
		::operator delete(reinterpret_cast<Karotazh*>(p));
		break;
	case object_type::bmp3d:
		::operator delete(reinterpret_cast<Bmp3D*>(p));
		break;

	case object_type::bln_profile3d:
		::operator delete(reinterpret_cast<BlnProfile3D*>(p));
		break;
	case object_type::bln_profile_plane3d:
		::operator delete(reinterpret_cast<BlnProfilePlane3D*>(p));
		break;

	case object_type::broken_plane3d:
		::operator delete(reinterpret_cast<BrokenPlane3D*>(p));
		break;
	case object_type::broken_line3d:
		::operator delete(reinterpret_cast<BrokenLine3D*>(p));
		break;
	case object_type::broken_poligon3d:
		::operator delete(reinterpret_cast<BrokenPoligon3D*>(p));
		break;
	case object_type::broken_poligon_3d:
		::operator delete(reinterpret_cast<BrokenPoligon_3D*>(p));
		break;

	case object_type::grid_profile3d:
		::operator delete(reinterpret_cast<GridProfile3D*>(p));
		break;
	case object_type::triangulated_grid3d:
		::operator delete(reinterpret_cast<TriangulatedGrid3D*>(p));
		break;

	case object_type::geo_surface:
		::operator delete(reinterpret_cast<GeoSurface*>(p));
		break;
	case object_type::geo_catch:
		::operator delete(reinterpret_cast<GeoCatch*>(p));
		break;
	case object_type::grid_data:
		::operator delete(reinterpret_cast<GridData*>(p));
		break;
	case object_type::collection:
		::operator delete(reinterpret_cast<Collection*>(p));
		break;
	case object_type::auto_profile_building:
		::operator delete(reinterpret_cast<AutoBuildProfile*>(p));
		break;

#if DFX_LAYER_FROM_OBJECT
//	case object_type::dfx_layerdata:
//		::operator delete(reinterpret_cast<dxfLayerData*>(p));
//		break;
	case object_type::dfx_converter:
		::operator delete(reinterpret_cast<dxfConverter*>(p));
		break;
#endif
	case object_type::fast_collection:
		::operator delete(reinterpret_cast<FastCollection*>(p));
		break;


	case object_type::surf_doc:
		::operator delete(reinterpret_cast<SurfDoc*>(p));
		break;

	default:
		{
		}
	}
	return;
}



	
void Object::operator delete[](void*p, object_type type)
{
	switch (type)
	{
	case object_type::object_list:
		::operator delete(reinterpret_cast<ObjectList*>(p));
		break;

	case object_type::geo_colomn:
		::operator delete(reinterpret_cast<GeoColomn*>(p));
		break;

//	case object_type::well_colomn:
//		::operator delete(reinterpret_cast<WellColomn*>(p));
//		break;

	case object_type::thepoint3d:
		::operator delete[](reinterpret_cast<ThePoint3D*>(p));
		break;
	case object_type::line3d:
		::operator delete[](reinterpret_cast<Line3D*>(p));
		break;
	case object_type::inter_wells_line_3d:
		::operator delete[](reinterpret_cast<InterWellsLine3D*>(p));
		break;
	case object_type::surface3d:
		::operator delete[](reinterpret_cast<Surface3D*>(p));
		break;
	case object_type::cube4d:
		::operator delete[](reinterpret_cast<Cube4D*>(p));
		break;
	case object_type::triangle3d:
		::operator delete[](reinterpret_cast<Triangle3D*>(p));
		break;
	case object_type::poligon3d:
		::operator delete[](reinterpret_cast<Poligon3D*>(p));
		break;
	case object_type::sphere3d:
		::operator delete[](reinterpret_cast<Sphere3D*>(p));
		break;
	case object_type::string3d:
		::operator delete[](reinterpret_cast<String3D*>(p));
		break;
	case object_type::well_3d:
		::operator delete[](reinterpret_cast<Well_3D*>(p));
		break;
	case object_type::karotazh:
		::operator delete[](reinterpret_cast<Karotazh*>(p));
		break;
	case object_type::bmp3d:
		::operator delete[](reinterpret_cast<Bmp3D*>(p));
		break;

	case object_type::bln_profile3d:
		::operator delete[](reinterpret_cast<BlnProfile3D*>(p));
		break;
	case object_type::bln_profile_plane3d:
		::operator delete[](reinterpret_cast<BlnProfilePlane3D*>(p));
		break;

	case object_type::broken_plane3d:
		::operator delete[](reinterpret_cast<BrokenPlane3D*>(p));
		break;
	case object_type::broken_line3d:
		::operator delete[](reinterpret_cast<BrokenLine3D*>(p));
		break;
	case object_type::broken_poligon3d:
		::operator delete[](reinterpret_cast<BrokenPoligon3D*>(p));
		break;
	case object_type::broken_poligon_3d:
		::operator delete[](reinterpret_cast<BrokenPoligon_3D*>(p));
		break;

	case object_type::grid_profile3d:
		::operator delete[](reinterpret_cast<GridProfile3D*>(p));
		break;
	case object_type::triangulated_grid3d:
		::operator delete[](reinterpret_cast<TriangulatedGrid3D*>(p));
		break;

	case object_type::geo_surface:
		::operator delete[](reinterpret_cast<GeoSurface*>(p));
		break;
	case object_type::geo_catch:
		::operator delete[](reinterpret_cast<GeoCatch*>(p));
		break;
	case object_type::grid_data:
		::operator delete[](reinterpret_cast<GridData*>(p));
		break;
	case object_type::collection:
		::operator delete[](reinterpret_cast<Collection*>(p));
		break;
	case object_type::auto_profile_building:
		::operator delete[](reinterpret_cast<AutoBuildProfile*>(p));
		break;

#if DFX_LAYER_FROM_OBJECT
//	case object_type::dfx_layerdata:
//		::operator delete[](reinterpret_cast<dxfLayerData*>(p));
//		break;
	case object_type::dfx_converter:
		::operator delete[](reinterpret_cast<dxfConverter*>(p));
		break;
#endif
	case object_type::fast_collection:
		::operator delete[](reinterpret_cast<FastCollection*>(p));
		break;


	case object_type::surf_doc:
		::operator delete[](reinterpret_cast<SurfDoc*>(p));
		break;

	default:
		{
		}
	}
	return;
}

HWND Object::hPropertyWindow = NULL; 

void Object::Init()
{
	this->layerID = -1;
	this->pLayer = NULL;
	this->m_parent = NULL;
	this->m_base_version = 2;
	this->m_object_type = Object::object_type::object;

	this->m_object_version = 0;
	this->m_max_object_version = 0;

	this->m_UserID = 0;
	this->name = "";


	m_lParam			= 0;//user data
	m_nglListNumber		= 0;
	m_bChecked			= true;
	this->m_bExpanded	= true;

	m_bIsObjectList		= false;
	m_bIsPrimitive3		= false;
	m_bIsPrimitive4		= false;
	m_pObjectList		= NULL;
	this->myTreeItem	= NULL;

	this->m_toDisableDepthTest = false;

	this->m_pSurfDoc = NULL;
	this->m_parent = NULL;

	this->make_translit = true;
	this->name_translit = "";

}
Object::Object()
{

	this->Init();

	//printf("Object(%s)\n",ObjectTypeToString(this->m_object_type));

}
struct translit_map 
{
	char c;
	const char * s;
};
string Object::GetNameTranslit()
{
	size_t i, j;
	if (make_translit)
	{
		name_translit = "";

		translit_map stm[] = {
			{'А',"A"},
			{'а',"a"},
			{'Б',"B"},
			{'б',"b"},
			{'В',"V"},
			{'в',"v"},
			{'Г',"G"},
			{'г',"g"},
			{'Д',"D"},
			{'д',"d"},
			{'Е',"E"},
			{'е',"e"},
			{'Ё',"Jo"},
			{'ё',"jo"},
			{'Ж',"Zh"},
			{'ж',"zh"},
			{'З',"Z"},
			{'з',"z"},
			{'И',"I"},
			{'и',"i"},
			{'Й',"J"},
			{'й',"j"},
			{'К',"K"},
			{'к',"k"},
			{'Л',"L"},
			{'л',"l"},
			{'М',"M"},
			{'м',"m"},
			{'Н',"N"},
			{'н',"n"},
			{'О',"O"},
			{'о',"o"},
			{'П',"P"},
			{'п',"p"},
			{'Р',"R"},
			{'р',"r"},
			{'С',"S"},
			{'с',"s"},
			{'Т',"T"},
			{'т',"t"},
			{'У',"U"},
			{'у',"u"},
			{'Ф',"F"},
			{'ф',"f"},
			{'Х',"H"},
			{'х',"h"},
			{'Ц',"C"},
			{'ц',"c"},
			{'Ч',"Ch"},
			{'ч',"ch"},
			{'Ш',"Sh"},
			{'ш',"sh"},
			{'Щ',"Sch"},
			{'щ',"sch"},
			{'Ь',"I"},
			{'ь',"i"},
			{'Ы',"Y"},
			{'ы',"y"},
			{'Ъ',"Y"},
			{'ъ',"y"},
			{'Э',"E"},
			{'э',"e"},
			{'Ю',"Yu"},
			{'ю',"yu"},
			{'Я',"Ya"},
			{'я',"ya"},
			{' ',"_"},
			{'.',"_"},
			{',',"_"},
			{':',"_"},
			{';',"_"},
			{'+',"_"},
			{'-',"_"},
			{'І',"I"},
			{'і',"i"},
			{'Ї',"Ji"},
			{'ї',"ji"},
			{'Є',"E"},
			{'є',"e"},
			{'\t',"_"},
			{'\'',"_"},
			{'\"',"_"}
		};

		map<char, const char *> tm;
		size_t n = sizeof(stm)/sizeof(translit_map);
		for (i = 0; i < n; i++)
		{
			tm.insert(map<char, const char *>::value_type(stm[i].c,stm[i].s));
		}
		for (i = 0; i < this->name.size(); i++)
		{
			char c = name[i];			
			map<char, const char *>::iterator found = tm.find(c);
			if (found != tm.end())
			{
				name_translit += (*found).second;
			}
			else
			{
				name_translit += name[i];
			}
		}
		make_translit = false;
	}
	return name_translit;
}
void Object::OnDestroy()
{
//	if (this->m_pSurfDoc)
//		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);

	if (m_nglListNumber > 0)
	{
		::glDeleteLists(m_nglListNumber,1);
//printf("::glDeleteLists(%u,1)  ",m_nglListNumber);
	}
	m_nglListNumber = 0;

	/*printf("Object::OnDestroy()(%s)",ObjectTypeToString(this->m_object_type));
	if (this->GetParent())
	{
		printf("\tparent = %s\n", ObjectTypeToString(this->GetParent()->GetObjectType()));
	}
	else
		printf("\n");*/
}

Object::~Object()
{
	OnDestroy();
}

Object::Object(const Object &ob)
{
	this->Init(ob);
}

#define object_cast_1 dynamic_cast

//====== Операция присвоения
Object& Object::operator=(const Object& ob)
{
//printf("Object& Object::operator=(Object& ob)\n");
	if (this == &ob)
	{
		return *this;
	}

	Object::object_type type = ob.Object::GetObjectType();
	//Object::object_type type = ob.m_object_type;
	if(this->GetObjectType() != type)
	{
		char serror[1024];
		sprintf(serror, "this->GetObjectType(%s) != ob.GetObjectType(%s)",
			Object::ObjectTypeToString(this->GetObjectType()), 
			Object::ObjectTypeToString(type));
			MessageBox(0,serror, "Object& Object::operator=(Object& ob)", 0);
		return *this;
	}


	switch (type)
	{
	case object_type::object_list:
		(*object_cast_1<ObjectList*>(this)) = (*object_cast_1<const ObjectList*>(&ob));
		break;

	case object_type::geo_colomn:
		(*object_cast_1<GeoColomn*>(this)) = (*object_cast_1<const GeoColomn*>(&ob));
		break;

//	case object_type::well_colomn:
//		(*object_cast_1<WellColomn*>(this)) = (*object_cast_1<const WellColomn*>(&ob));
//		break;

	case object_type::thepoint3d:
		(*object_cast_1<ThePoint3D*>(this)) = (*object_cast_1<const ThePoint3D*>(&ob));
		break;
	case object_type::line3d:
		(*object_cast_1<Line3D*>(this)) = (*object_cast_1<const Line3D*>(&ob));
		break;
	case object_type::inter_wells_line_3d:
		(*object_cast_1<InterWellsLine3D*>(this)) = (*object_cast_1<const InterWellsLine3D*>(&ob));
		break;
	case object_type::surface3d:
		(*object_cast_1<Surface3D*>(this)) = (*object_cast_1<const Surface3D*>(&ob));
		break;
	case object_type::cube4d:
		(*object_cast_1<Cube4D*>(this)) = (*object_cast_1<const Cube4D*>(&ob));
		break;
	case object_type::triangle3d:
		(*object_cast_1<Triangle3D*>(this)) = (*object_cast_1<const Triangle3D*>(&ob));
		break;
	case object_type::poligon3d:
		(*object_cast_1<Poligon3D*>(this)) = (*object_cast_1<const Poligon3D*>(&ob));
		break;
	case object_type::sphere3d:
		(*object_cast_1<Sphere3D*>(this)) = (*object_cast_1<const Sphere3D*>(&ob));
		break;
	case object_type::string3d:
		(*object_cast_1<String3D*>(this)) = (*object_cast_1<const String3D*>(&ob));
		break;
	case object_type::well_3d:
		(*object_cast_1<Well_3D*>(this)) = (*object_cast_1<const Well_3D*>(&ob));
		break;
	case object_type::karotazh:
		(*object_cast_1<Karotazh*>(this)) = (*object_cast_1<const Karotazh*>(&ob));
		break;
	case object_type::bmp3d:
		(*object_cast_1<Bmp3D*>(this)) = (*object_cast_1<const Bmp3D*>(&ob));
		break;

	case object_type::bln_profile3d:
		(*object_cast_1<BlnProfile3D*>(this)) = (*object_cast_1<const BlnProfile3D*>(&ob));
		break;
	case object_type::bln_profile_plane3d:
		(*object_cast_1<BlnProfilePlane3D*>(this)) = (*object_cast_1<const BlnProfilePlane3D*>(&ob));
		break;

	case object_type::broken_plane3d:
		(*object_cast_1<BrokenPlane3D*>(this)) = (*object_cast_1<const BrokenPlane3D*>(&ob));
		break;
	case object_type::broken_line3d:
		(*object_cast_1<BrokenLine3D*>(this)) = (*object_cast_1<const BrokenLine3D*>(&ob));
		break;
	case object_type::broken_poligon3d:
		(*object_cast_1<BrokenPoligon3D*>(this)) = (*object_cast_1<const BrokenPoligon3D*>(&ob));
		break;
	case object_type::broken_poligon_3d:
		(*object_cast_1<BrokenPoligon_3D*>(this)) = (*object_cast_1<const BrokenPoligon_3D*>(&ob));
		break;

	case object_type::grid_profile3d:
		(*object_cast_1<GridProfile3D*>(this)) = (*object_cast_1<const GridProfile3D*>(&ob));
		break;
	case object_type::triangulated_grid3d:
		(*object_cast_1<TriangulatedGrid3D*>(this)) = (*object_cast_1<const TriangulatedGrid3D*>(&ob));
		break;

	case object_type::geo_surface:
		(*object_cast_1<GeoSurface*>(this)) = (*object_cast_1<const GeoSurface*>(&ob));
		break;
	case object_type::geo_catch:
		(*object_cast_1<GeoCatch*>(this)) = (*object_cast_1<const GeoCatch*>(&ob));
		break;
	case object_type::grid_data:
		(*object_cast_1<GridData*>(this)) = (*object_cast_1<const GridData*>(&ob));
		break;
	case object_type::collection:
		(*object_cast_1<Collection*>(this)) = (*object_cast_1<const Collection*>(&ob));
		break;
	case object_type::auto_profile_building:
		(*object_cast_1<AutoBuildProfile*>(this)) = (*object_cast_1<const AutoBuildProfile*>(&ob));
		break;

#if DFX_LAYER_FROM_OBJECT
	case object_type::dfx_layerdata:
		(*object_cast_1<dxfLayerData*>(this)) = (*object_cast_1<const dxfLayerData*>(&ob));
		break;
	case object_type::dfx_converter:
		(*object_cast_1<dxfConverter*>(this)) = (*object_cast_1<const dxfConverter*>(&ob));
		break;
#endif
	case object_type::fast_collection:
		(*object_cast_1<FastCollection*>(this)) = (*object_cast_1<const FastCollection*>(&ob));
		break;


	case object_type::surf_doc:
		(*object_cast_1<SurfDoc*>(this)) = (*object_cast_1<const SurfDoc*>(&ob));
		break;

	default:
		{
		}
	}

	return *this;
}
bool Object::UpdateExtremums(vector<CPoint3>& vptmax, vector<CPoint3>& vptmin)
{
	bool start = true;
	for( int i = 0; i< vptmax.size() && i < vptmin.size(); i++)
	{
		CPoint3 ptmax, ptmin;
		ptmax = vptmax[i];
		ptmin = vptmin[i];
		if (start)
		{
			start = false;
			// real x
			m_ptMax.x = ptmax.x;
			m_ptMin.x = ptmin.x;
			// real y
			m_ptMax.y = ptmax.y;
			m_ptMin.y = ptmin.y;
			// real z
			m_ptMax.z = ptmax.z;
			m_ptMin.z = ptmin.z;
		}
		else
		{
			// real x
			if (m_ptMax.x < ptmax.x) m_ptMax.x = ptmax.x;
			if (m_ptMin.x > ptmin.x) m_ptMin.x = ptmin.x;
			// real y
			if (m_ptMax.y < ptmax.y) m_ptMax.y = ptmax.y;
			if (m_ptMin.y > ptmin.y) m_ptMin.y = ptmin.y;
			// real z
			if (m_ptMax.z < ptmax.z) m_ptMax.z = ptmax.z;
			if (m_ptMin.z > ptmin.z) m_ptMin.z = ptmin.z;
		}
	}
	vptmin.clear();
	vptmax.clear();
	return !start;
}
void Object::Zooming()
{
	if (this->m_pSurfDoc)
	{
		this->Zoom(
			this->m_pSurfDoc->m_zoomX, 
			this->m_pSurfDoc->m_zoomY, 
			this->m_pSurfDoc->m_zoomZ, 
			this->m_pSurfDoc->m_xd_zoom_center, 
			this->m_pSurfDoc->m_yd_zoom_center, 
			this->m_pSurfDoc->m_zd_zoom_center);
	}
}
void Object::Init(const Object &ob)
{
//printf("Object::Init(Object &ob)\n");
	m_lParam			= ob.m_lParam;
	m_nglListNumber		= ob.m_nglListNumber;
	m_bChecked			= ob.m_bChecked;
	m_bIsObjectList		= ob.m_bIsObjectList;
	m_bIsPrimitive3		= ob.m_bIsPrimitive3;
	m_bIsPrimitive4		= ob.m_bIsPrimitive4;
	m_pObjectList		= ob.m_pObjectList;

	this->layerID			= ob.layerID;
	this->pLayer			= ob.pLayer;

	this->m_UserID			= ob.m_UserID;
	this->name				= ob.name;
    this->m_base_version	= ob.m_base_version;
	this->m_object_version	= ob.m_object_version;
	this->m_object_type		= ob.m_object_type;
		
	this->m_pSurfDoc		= ob.m_pSurfDoc;

	this->m_ptMax		= ob.m_ptMax;
	this->m_ptMin		= ob.m_ptMin;

	this->make_translit = ob.make_translit;
	this->name_translit = ob.name_translit;

}
bool Object::ToLayer()
{
	bool res = false;
	if (this->m_pSurfDoc)
	{
		new select_layer_dialog(this->m_pSurfDoc, "New Layer name");
		if (this->m_pSurfDoc->GetSelectedLayer())
		{
			this->SetLayer(this->m_pSurfDoc->GetSelectedLayer());
			res = true;
		}

		this->m_pSurfDoc->SetSelectedLayer(NULL);
	}
	return res;
}
/*virtual*/ 
void Object::FillContextMenu(HMENU& hMenu)
{
//printf("Object::FillContextMenu(HMENU& hMenu) %s\n", Object::ObjectTypeToString(this->GetObjectType()));
	AppendMenu( hMenu, MFT_STRING, ID_TREE_COLORDIALOG, "&Color" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_OBJECTSAVEAS, "&Save As..." );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_OBJECTDELETE, "&Delete" );
#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_STRING, ID_TREE_OBJECTTOLAYER, "to &Layer" );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_OBJECTSETNAME, "Set &Name" );
#endif /*#if !VIEW_ONLY_VERSION*/
	AppendMenu( hMenu, MFT_STRING, ID_TREE_OBJECTREDRAW, "ReDraw" );
	
	AppendMenu( hMenu, MFT_SEPARATOR, 0, NULL );

#if !VIEW_ONLY_VERSION
	AppendMenu( hMenu, MFT_STRING, ID_TREE_PROPERTIESDIALOG, "&Properties dialog..." );
	AppendMenu( hMenu, MFT_STRING, ID_TREE_PROPERTIES_WINDOW, "&Properties window..." );
#endif /*#if !VIEW_ONLY_VERSION*/
}
/*virtual*/ 
void Object::CreateContextMenu(HWND hWnd, LPARAM lParam) 
{
	HMENU hMenu = CreatePopupMenu();
	// call virtual FillContextMenu
	this->FillContextMenu(hMenu);
	
	TrackPopupMenu( hMenu, TPM_RIGHTBUTTON | 
		TPM_TOPALIGN |
		TPM_LEFTALIGN, 
		LOWORD( lParam ),
		HIWORD( lParam ), 0, hWnd, NULL );
	
	DestroyMenu( hMenu );
}
void Object::SetLayer_NonVirtual(const Layer* layer)
{
	pLayer = (Layer*)layer;
	if (pLayer)
	{
//printf("SetLayer_NonVirtual pLayer (0x%08x) = (Layer*)layer (0x%08x);\n", pLayer, layer);
		this->layerID = pLayer->GetID();
	}
	else
	{
//printf("SetLayer_NonVirtual pLayer (0x%08x) = (Layer*)layer (0x%08x);\n", pLayer, layer);
		this->layerID = -1;
	}
}
bool Object::SetNameDlg()
{
	bool rez = false;
	static char command[512] = "";
	strcpy(command, this->GetName().c_str());
	command_dialog * cmnd_dlg = new command_dialog(NULL, NULL, command, false);
	if (cmnd_dlg) strcpy (command, cmnd_dlg->command);

	if (cmnd_dlg && cmnd_dlg->WasOk())
	{
		this->SetName(command);
		rez = true;
	}

	if (cmnd_dlg)
	{
		delete cmnd_dlg;
		cmnd_dlg = NULL;
	}
	return rez;
}
void Object::ReDrawItem_OnTree(HWND hwndTV)
{
	if (this->m_pSurfDoc)
	{
		TreeView_DeleteMyItem(this->m_pSurfDoc->hwndTV, this->myTreeItem);
		this->AddItem_ToTree(this->m_pSurfDoc->hwndTV, this->parentTreeItem, "");
	}
}

bool Object::IsCheckedEx()
{
	if (!this->m_bChecked) return false;
	if (this->m_pObjectList && !this->m_pObjectList->m_bChecked) return false;
	if (this->pLayer && !this->pLayer->bChecked) return false;

	Object * parent;
	Object * ob = this;
	while ((parent = ob->GetParent()) != NULL)
	{
		if (!parent->m_bChecked) return false;
		if (parent->m_pObjectList && !parent->m_pObjectList->m_bChecked) return false;
		ob = parent;
	}
	return true;
}
template <class K, class T> void Object_Deleting_from_std_map(map<K,T> * m, T* ob) 
{
	if (m && ob)
	{
		for (map<K,T>::iterator it = m->begin(); it != m->end(); it++)
		{
			if ( ob == & (it->second))
			{
				m->erase(it);
				return;
			}
		}
	}

}
template <class T> void Object_Deleting_from_vect(vect<T> * v, T* ob) 
{
	//printf("Object_Deleting(vect<T> & v ) %s \n", Object::ObjectTypeToString(ob->GetObjectType()));
	if (v->SetCurrentMsgOnFirst())
	{
		do
		{
			if (ob == &v->GetCurrentMsg())
			{
				v->EraseCurrentMsg();
				break;
			}
		}
		while(v->IncrementCurrentMsg());
	}
};

bool Object::Delete()
{
	ObjectList * pObjectList;
	Object * parent = this->GetParent();
	void * pContainer;
	Object::container_type type_of_container;
	Object::object_type this_object_type = this->GetObjectType();
	Object *This = this;

	char str[1024];
	sprintf(str, "Вы действительно хотите удалить объект типа %s имя \"%s\" родитель %s \"%s\"?", 
		Object::ObjectTypeToString(this_object_type),

		this->GetName().c_str(),
		parent != NULL ? Object::ObjectTypeToString(parent->GetObjectType()) : "",
		parent != NULL ? parent->GetName().c_str() : "");

	if (IDNO == MessageBox(0, str, "Object::Delete()", MB_YESNO))
	{
		return false;
	}

	if (this->m_pObjectList)
	{
		pObjectList = this->m_pObjectList;
		pContainer = pObjectList->GetContainer();
		type_of_container = pObjectList->GetContainerType();
		if(type_of_container == Object::container_type::container_std_map)
		{
			switch(this_object_type)
			{
			case object_type::geo_colomn:
				Object_Deleting_from_std_map<string,GeoColomn>(
					reinterpret_cast<map<string, GeoColomn>*>(pContainer), 
					dynamic_cast<GeoColomn*>(This));
				pObjectList->Init_std_map(*reinterpret_cast<map<string, GeoColomn>*>(pContainer), parent);		
				return true;
			/*/case object_type::well_colomn:
				Object_Deleting_from_std_map<string,WellColomn>(
					reinterpret_cast<map<string, WellColomn>*>(pContainer), 
					dynamic_cast<WellColomn*>(This));
				pObjectList->Init_std_map(*reinterpret_cast<map<string, WellColomn>*>(pContainer), parent);		
				return true;*/
			}
		}
		if(type_of_container == Object::container_type::container_vect)
		{
			switch(this_object_type)
			{
			case object_type::object_list:
				Object_Deleting_from_vect<ObjectList>(
					reinterpret_cast<vect<ObjectList>*>(pContainer), 
					dynamic_cast<ObjectList*>(This));
				pObjectList->Init(*reinterpret_cast<vect<ObjectList>*>(pContainer), parent);		
				return true;

			case object_type::thepoint3d:
				{
					ThePoint3D * deleting = dynamic_cast<ThePoint3D*>(This);
					if (deleting)
					{
						Object * parent = deleting->GetObjectList()->GetParent();
						GridData * pGridData = dynamic_cast<GridData*>(parent);
						if (pGridData)
						{
							if (pGridData->ClearPointFromDB(true, deleting->id_point) == IDCANCEL)
							{
								return false;
							}
						}
					}

					Object_Deleting_from_vect<ThePoint3D>(
						reinterpret_cast<vect<ThePoint3D>*>(pContainer), 
						dynamic_cast<ThePoint3D*>(This));
					pObjectList->Init(*reinterpret_cast<vect<ThePoint3D>*>(pContainer), parent);		
					return true;
				}
				break;
			case object_type::line3d:
				Object_Deleting_from_vect<Line3D>(
					reinterpret_cast<vect<Line3D>*>(pContainer), 
					dynamic_cast<Line3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Line3D>*>(pContainer), parent);		
				return true;
			case object_type::inter_wells_line_3d:
				Object_Deleting_from_vect<InterWellsLine3D>(
					reinterpret_cast<vect<InterWellsLine3D>*>(pContainer), 
					dynamic_cast<InterWellsLine3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<InterWellsLine3D>*>(pContainer), parent);		
				return true;
			case object_type::surface3d:
				Object_Deleting_from_vect<Surface3D>(
					reinterpret_cast<vect<Surface3D>*>(pContainer), 
					dynamic_cast<Surface3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Surface3D>*>(pContainer), parent);		
				return true;
			case object_type::cube4d:
				Object_Deleting_from_vect<Cube4D>(
					reinterpret_cast<vect<Cube4D>*>(pContainer), 
					dynamic_cast<Cube4D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Cube4D>*>(pContainer), parent);		
				return true;
			case object_type::triangle3d:
				Object_Deleting_from_vect<Triangle3D>(
					reinterpret_cast<vect<Triangle3D>*>(pContainer), 
					dynamic_cast<Triangle3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Triangle3D>*>(pContainer), parent);		
				return true;
			case object_type::poligon3d:
				Object_Deleting_from_vect<Poligon3D>(
					reinterpret_cast<vect<Poligon3D>*>(pContainer), 
					dynamic_cast<Poligon3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Poligon3D>*>(pContainer), parent);		
				return true;
			case object_type::sphere3d:
				Object_Deleting_from_vect<Sphere3D>(
					reinterpret_cast<vect<Sphere3D>*>(pContainer), 
					dynamic_cast<Sphere3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Sphere3D>*>(pContainer), parent);		
				return true;
			case object_type::string3d:
				Object_Deleting_from_vect<String3D>(
					reinterpret_cast<vect<String3D>*>(pContainer), 
					dynamic_cast<String3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<String3D>*>(pContainer), parent);		
				return true;
			case object_type::well_3d:
				Object_Deleting_from_vect<Well_3D>(
					reinterpret_cast<vect<Well_3D>*>(pContainer), 
					dynamic_cast<Well_3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Well_3D>*>(pContainer), parent);		
				return true;
			case object_type::karotazh:
				Object_Deleting_from_vect<Karotazh>(
					reinterpret_cast<vect<Karotazh>*>(pContainer), 
					dynamic_cast<Karotazh*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Karotazh>*>(pContainer), parent);		
				return true;
			case object_type::bmp3d:
				Object_Deleting_from_vect<Bmp3D>(
					reinterpret_cast<vect<Bmp3D>*>(pContainer), 
					dynamic_cast<Bmp3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Bmp3D>*>(pContainer), parent);		
				return true;

			case object_type::bln_profile3d:
				{
					BlnProfile3D* deleting = dynamic_cast<BlnProfile3D*>(This);
					if (deleting)
					{
						if (deleting->ClearFromDB(true) == IDCANCEL)
						{
							return false;
						}
					}

					Object_Deleting_from_vect<BlnProfile3D>(
						reinterpret_cast<vect<BlnProfile3D>*>(pContainer), 
						dynamic_cast<BlnProfile3D*>(This));
					pObjectList->Init(*reinterpret_cast<vect<BlnProfile3D>*>(pContainer), parent);		
					return true;
				}
				break;

			case object_type::bln_profile_plane3d:
				Object_Deleting_from_vect<BlnProfilePlane3D>(
					reinterpret_cast<vect<BlnProfilePlane3D>*>(pContainer), 
					dynamic_cast<BlnProfilePlane3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<BlnProfilePlane3D>*>(pContainer), parent);		
				return true;

			case object_type::broken_plane3d:
				Object_Deleting_from_vect<BrokenPlane3D>(
					reinterpret_cast<vect<BrokenPlane3D>*>(pContainer), 
					dynamic_cast<BrokenPlane3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<BrokenPlane3D>*>(pContainer), parent);		
				return true;
			case object_type::broken_line3d:
				Object_Deleting_from_vect<BrokenLine3D>(
					reinterpret_cast<vect<BrokenLine3D>*>(pContainer), 
					dynamic_cast<BrokenLine3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<BrokenLine3D>*>(pContainer), parent);		
				return true;
			case object_type::broken_poligon3d:
				Object_Deleting_from_vect<BrokenPoligon3D>(
					reinterpret_cast<vect<BrokenPoligon3D>*>(pContainer), 
					dynamic_cast<BrokenPoligon3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<BrokenPoligon3D>*>(pContainer), parent);		
				return true;
			case object_type::broken_poligon_3d:
				Object_Deleting_from_vect<BrokenPoligon_3D>(
					reinterpret_cast<vect<BrokenPoligon_3D>*>(pContainer), 
					dynamic_cast<BrokenPoligon_3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<BrokenPoligon_3D>*>(pContainer), parent);		
				return true;

			case object_type::grid_profile3d:
				Object_Deleting_from_vect<GridProfile3D>(
					reinterpret_cast<vect<GridProfile3D>*>(pContainer), 
					dynamic_cast<GridProfile3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<GridProfile3D>*>(pContainer), parent);		
				return true;
			case object_type::triangulated_grid3d:
				Object_Deleting_from_vect<TriangulatedGrid3D>(
					reinterpret_cast<vect<TriangulatedGrid3D>*>(pContainer), 
					dynamic_cast<TriangulatedGrid3D*>(This));
				pObjectList->Init(*reinterpret_cast<vect<TriangulatedGrid3D>*>(pContainer), parent);		
				return true;

			case object_type::geo_surface:
				{
					GeoSurface* deleting = dynamic_cast<GeoSurface*>(This);
					if (deleting && deleting->m_surface.m_zflag == 0)
					{
						if (deleting->ClearFromDB(true) == IDCANCEL)
						{
							return false;
						}
						deleting->ClearFromOrderLists();
					}

					Object_Deleting_from_vect<GeoSurface>(
						reinterpret_cast<vect<GeoSurface>*>(pContainer), 
						dynamic_cast<GeoSurface*>(This));
					pObjectList->Init(*reinterpret_cast<vect<GeoSurface>*>(pContainer), parent);		
					return true;
				}
				break;
			case object_type::geo_catch:
				Object_Deleting_from_vect<GeoCatch>(
					reinterpret_cast<vect<GeoCatch>*>(pContainer), 
					dynamic_cast<GeoCatch*>(This));
				pObjectList->Init(*reinterpret_cast<vect<GeoCatch>*>(pContainer), parent);		
				return true;
			case object_type::grid_data:
				{
					GridData * deleting = dynamic_cast<GridData*>(This);
					if (deleting)
					{						
						if (deleting->ClearFromDB(true) == IDCANCEL)
						{
							return false;
						}
					}

					Object_Deleting_from_vect<GridData>(
						reinterpret_cast<vect<GridData>*>(pContainer), 
						dynamic_cast<GridData*>(This));
					pObjectList->Init(*reinterpret_cast<vect<GridData>*>(pContainer), parent);		
					return true;
				}
				break;
			case object_type::collection:
				Object_Deleting_from_vect<Collection>(
					reinterpret_cast<vect<Collection>*>(pContainer), 
					dynamic_cast<Collection*>(This));
				pObjectList->Init(*reinterpret_cast<vect<Collection>*>(pContainer), parent);		
				return true;
			case object_type::auto_profile_building:
				Object_Deleting_from_vect<AutoBuildProfile>(
					reinterpret_cast<vect<AutoBuildProfile>*>(pContainer), 
					dynamic_cast<AutoBuildProfile*>(This));
				pObjectList->Init(*reinterpret_cast<vect<AutoBuildProfile>*>(pContainer), parent);		
				return true;
#if DFX_LAYER_FROM_OBJECT
			case object_type::dfx_layerdata:
				Object_Deleting_from_vect<dxfLayerData>(
					reinterpret_cast<vect<dxfLayerData>*>(pContainer), 
					dynamic_cast<dxfLayerData*>(This));
				pObjectList->Init(*reinterpret_cast<vect<dxfLayerData>*>(pContainer), parent);		
				return true;
			case object_type::dfx_converter:
				Object_Deleting_from_vect<dxfConverter>(
					reinterpret_cast<vect<dxfConverter>*>(pContainer), 
					dynamic_cast<dxfConverter*>(This));
				pObjectList->Init(*reinterpret_cast<vect<dxfConverter>*>(pContainer), parent);		
				return true;
#endif
			case object_type::fast_collection:
				Object_Deleting_from_vect<FastCollection>(
					reinterpret_cast<vect<FastCollection>*>(pContainer), 
					dynamic_cast<FastCollection*>(This));
				pObjectList->Init(*reinterpret_cast<vect<FastCollection>*>(pContainer), parent);		
				return true;
			/*case object_type::surf_doc:
				Object_Deleting_from_vect<T>(
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
DWORD Object::Serialize(Archive& ar)
{
DWORD version = 0;
//printf("Object::Serialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		//ar << *this;
		//Archive& operator <<(Archive& ar, Object& ob)
		{
//printf("Archive& operator <<(Archive& ar, Object& ob)\n");
			//this->m_base_version;
			DWORD base_version = Object::s_max_base_version;
			ar << base_version;
//printf("base_version = %d\n", base_version);
			switch (base_version)
			{
			case 2:
				{
					ar << this->layerID;
//printf("this->layerID = %d\n", this->layerID );
				}
			case 1:
				{
					ar << this->m_UserID;
//printf("this->m_UserID = %d\n", this->m_UserID );
					ar << this->name;
//printf("this->name = %s\n", this->name.c_str() );
version = ar.m_use_object_version ? 
(ar.m_use_object_version > this->m_max_object_version ? this->m_max_object_version : ar.m_use_object_version) 
		: this->m_object_version;

					//ar << this->m_object_version;					
					ar << version;					
//printf("this->m_object_version = %d\n", this->m_object_version );

					int ob_type = this->m_object_type;
					ar << ob_type;
//printf("this->m_object_type = %s\n", Object::ObjectTypeToString(this->m_object_type) );

					ar << this->m_bChecked;
//printf("this->m_bChecked = %d\n", this->m_bChecked );
					ar << this->m_bExpanded;
//printf("this->m_bExpanded = %d\n", this->m_bExpanded );
					ar << this->m_lParam;
//printf("this->m_lParam = %d\n", this->m_lParam );
					//ar << this->m_nglListNumber
					//ar << this->m_pObjectList;
					//ar << this->myTreeItem;
					//ar << this->parentTreeItem;

					ar << this->m_ptMax;
					ar << this->m_ptMin;
				}
				break;
			default:
				{		
					throw VersionException(this->m_base_version, VersionException::cannot_store, this->m_object_type);
				}
				break;
			}
			//return ar;
		}
	}
	else
	{
		//ar >> *this;
		//Archive& operator >>(Archive& ar, Object& ob)
		{
//printf("Archive& operator >>(Archive& ar, Object& ob)\n");

			this->m_pSurfDoc = (SurfDoc *)ar.pDocument;
			ar >> this->m_base_version;

//printf("this->m_base_version = %d\n", this->m_base_version);

			this->layerID = -1;

			switch (this->m_base_version)
			{
			case 2:
				{
					ar >> this->layerID;
//printf("this->layerID = %d\n", this->layerID );
				}
			case 1:
				{
					ar >> this->m_UserID;
//printf("this->m_UserID = %d\n", this->m_UserID );
					ar >> this->name;

//printf("this->name = %s\n", this->name.c_str() );

					ar >> this->m_object_version;
//printf("this->m_object_version = %d\n", this->m_object_version );

					int ob_type;
					ar >> ob_type;
					this->m_object_type = (Object::object_type)ob_type ;

//printf("this->m_object_type = %s\n", Object::ObjectTypeToString(this->m_object_type) );

					ar >> this->m_bChecked;
//printf("this->m_bChecked = %d\n", this->m_bChecked );
					ar >> this->m_bExpanded;
//printf("this->m_bExpanded = %d\n", this->m_bExpanded );
					ar >> this->m_lParam;
//printf("this->m_lParam = %d\n", this->m_lParam );
					//ar >> this->m_nglListNumber
					//ar >> this->m_pObjectList;
					//ar >> this->myTreeItem;
					//ar >> this->parentTreeItem;

					ar >> this->m_ptMax;
					ar >> this->m_ptMin;
				}
				break;
			default:
				{
					throw VersionException(this->m_base_version, VersionException::cannot_load, this->m_object_type);
				}
				break;
			}
			//printf("Archive& operator >>(Archive& ar, Object& ob) end\n");
			//return ar;
		}			
	}
	//printf("Object::Serialize(Archive& ar) end %s LayerID = %d\n", Object::ObjectTypeToString(this->GetObjectType()), this->GetLayerID());
	return version;
}

Archive& operator <<(Archive& ar, Object& ob)
{
	//printf("Archive& operator <<(Archive& ar, Object& ob) %s\n", Object::ObjectTypeToString(ob.GetObjectType()));

	Object::object_type type = ob.GetObjectType();
	int ob_type = type;
	ar << ob_type;

	switch (type)
	{
	case Object::object_type::object_list:
		ar << (*reinterpret_cast<ObjectList*>(&ob));
		break;

	case Object::object_type::geo_colomn:
		ar << (*reinterpret_cast<GeoColomn*>(&ob));
		break;

//	case Object::object_type::well_colomn:
//		ar << (*reinterpret_cast<WellColomn*>(&ob));
//		break;

	case Object::object_type::thepoint3d:
		ar <<  (*reinterpret_cast<ThePoint3D*>(&ob));
		break;
	case Object::object_type::line3d:
		ar <<  (*reinterpret_cast<Line3D*>(&ob));
		break;
	case Object::object_type::inter_wells_line_3d:
		ar <<  (*reinterpret_cast<InterWellsLine3D*>(&ob));
		break;
	case Object::object_type::surface3d:
		ar <<  (*reinterpret_cast<Surface3D*>(&ob));
		break;
	case Object::object_type::cube4d:
		ar <<  (*reinterpret_cast<Cube4D*>(&ob));
		break;
	case Object::object_type::triangle3d:
		ar <<  (*reinterpret_cast<Triangle3D*>(&ob));
		break;
	case Object::object_type::poligon3d:
		ar <<  (*reinterpret_cast<Poligon3D*>(&ob));
		break;
	case Object::object_type::sphere3d:
		ar <<  (*reinterpret_cast<Sphere3D*>(&ob));
		break;
	case Object::object_type::string3d:
		ar <<  (*reinterpret_cast<String3D*>(&ob));
		break;
	case Object::object_type::well_3d:
		ar <<  (*reinterpret_cast<Well_3D*>(&ob));
		break;
	case Object::object_type::karotazh:
		ar <<  (*reinterpret_cast<Karotazh*>(&ob));
		break;
	case Object::object_type::bmp3d:
		ar <<  (*reinterpret_cast<Bmp3D*>(&ob));
		break;

	case Object::object_type::bln_profile3d:
		ar <<  (*reinterpret_cast<BlnProfile3D*>(&ob));
		break;
	case Object::object_type::bln_profile_plane3d:
		ar <<  (*reinterpret_cast<BlnProfilePlane3D*>(&ob));
		break;

	case Object::object_type::broken_plane3d:
		ar <<  (*reinterpret_cast<BrokenPlane3D*>(&ob));
		break;
	case Object::object_type::broken_line3d:
		ar <<  (*reinterpret_cast<BrokenLine3D*>(&ob));
		break;
	case Object::object_type::broken_poligon3d:
		ar <<  (*reinterpret_cast<BrokenPoligon3D*>(&ob));
		break;
	case Object::object_type::broken_poligon_3d:
		ar <<  (*reinterpret_cast<BrokenPoligon_3D*>(&ob));
		break;

	case Object::object_type::grid_profile3d:
		ar <<  (*reinterpret_cast<GridProfile3D*>(&ob));
		break;
	case Object::object_type::triangulated_grid3d:
		ar <<  (*reinterpret_cast<TriangulatedGrid3D*>(&ob));
		break;

	case Object::object_type::geo_surface:
		ar <<  (*reinterpret_cast<GeoSurface*>(&ob));
		break;
	case Object::object_type::geo_catch:
		ar <<  (*reinterpret_cast<GeoCatch*>(&ob));
		break;
	case Object::object_type::grid_data:
		ar <<  (*reinterpret_cast<GridData*>(&ob));
		break;
	case Object::object_type::collection:
		ar <<  (*reinterpret_cast<Collection*>(&ob));
		break;
	case Object::object_type::auto_profile_building:
		ar <<  (*reinterpret_cast<AutoBuildProfile*>(&ob));
		break;

#if DFX_LAYER_FROM_OBJECT
	case Object::object_type::dfx_layerdata:
		ar <<  (*reinterpret_cast<dxfLayerData*>(&ob));
		break;
	case Object::object_type::dfx_converter:
		ar <<  (*reinterpret_cast<dxfConverter*>(&ob));
		break;
#endif
	case Object::object_type::fast_collection:
		ar <<  (*reinterpret_cast<FastCollection*>(&ob));
		break;

	case Object::object_type::surf_doc:
		ar <<  (*reinterpret_cast<SurfDoc*>(&ob));
		break;

	default:
		{
		}
	}


	return ar;
}
Archive& operator >>(Archive& ar, Object& ob)
{
	//printf("Archive& operator >>(Archive& ar, Object& ob)\n");

	Object::object_type type;
	int ob_type;
	ar >> ob_type;
	type = (Object::object_type)ob_type ;

	//printf("Archive& operator >>(Archive& ar, Object& ob) %s\n", Object::ObjectTypeToString(type));

	switch (type)
	{
	case Object::object_type::object_list:
		ar >> (*reinterpret_cast<ObjectList*>(&ob));
		break;

	case Object::object_type::geo_colomn:
		ar >> (*reinterpret_cast<GeoColomn*>(&ob));
		break;

//	case Object::object_type::well_colomn:
//		ar >> (*reinterpret_cast<WellColomn*>(&ob));
//		break;

	case Object::object_type::thepoint3d:
		ar >>  (*reinterpret_cast<ThePoint3D*>(&ob));
		break;
	case Object::object_type::line3d:
		ar >>  (*reinterpret_cast<Line3D*>(&ob));
		break;
	case Object::object_type::inter_wells_line_3d:
		ar >>  (*reinterpret_cast<InterWellsLine3D*>(&ob));
		break;
	case Object::object_type::surface3d:
		ar >>  (*reinterpret_cast<Surface3D*>(&ob));
		break;
	case Object::object_type::cube4d:
		ar >>  (*reinterpret_cast<Cube4D*>(&ob));
		break;
	case Object::object_type::triangle3d:
		ar >>  (*reinterpret_cast<Triangle3D*>(&ob));
		break;
	case Object::object_type::poligon3d:
		ar >>  (*reinterpret_cast<Poligon3D*>(&ob));
		break;
	case Object::object_type::sphere3d:
		ar >>  (*reinterpret_cast<Sphere3D*>(&ob));
		break;
	case Object::object_type::string3d:
		ar >>  (*reinterpret_cast<String3D*>(&ob));
		break;
	case Object::object_type::well_3d:
		ar >>  (*reinterpret_cast<Well_3D*>(&ob));
		break;
	case Object::object_type::karotazh:
		ar >>  (*reinterpret_cast<Karotazh*>(&ob));
		break;
	case Object::object_type::bmp3d:
		ar >>  (*reinterpret_cast<Bmp3D*>(&ob));
		break;

	case Object::object_type::bln_profile3d:
		ar >>  (*reinterpret_cast<BlnProfile3D*>(&ob));
		break;
	case Object::object_type::bln_profile_plane3d:
		ar >>  (*reinterpret_cast<BlnProfilePlane3D*>(&ob));
		break;

	case Object::object_type::broken_plane3d:
		ar >>  (*reinterpret_cast<BrokenPlane3D*>(&ob));
		break;
	case Object::object_type::broken_line3d:
		ar >>  (*reinterpret_cast<BrokenLine3D*>(&ob));
		break;
	case Object::object_type::broken_poligon3d:
		ar >>  (*reinterpret_cast<BrokenPoligon3D*>(&ob));
		break;
	case Object::object_type::broken_poligon_3d:
		ar >>  (*reinterpret_cast<BrokenPoligon_3D*>(&ob));
		break;

	case Object::object_type::grid_profile3d:
		ar >>  (*reinterpret_cast<GridProfile3D*>(&ob));
		break;
	case Object::object_type::triangulated_grid3d:
		ar >>  (*reinterpret_cast<TriangulatedGrid3D*>(&ob));
		break;

	case Object::object_type::geo_surface:
		ar >>  (*reinterpret_cast<GeoSurface*>(&ob));
		break;
	case Object::object_type::geo_catch:
		ar >>  (*reinterpret_cast<GeoCatch*>(&ob));
		break;
	case Object::object_type::grid_data:
		ar >>  (*reinterpret_cast<GridData*>(&ob));
		break;
	case Object::object_type::collection:
		ar >>  (*reinterpret_cast<Collection*>(&ob));
		break;
	case Object::object_type::auto_profile_building:
		ar >>  (*reinterpret_cast<AutoBuildProfile*>(&ob));
		break;
#if DFX_LAYER_FROM_OBJECT
	case Object::object_type::dfx_layerdata:
		ar >>  (*reinterpret_cast<dxfLayerData*>(&ob));
		break;
	case Object::object_type::dfx_converter:
		ar >>  (*reinterpret_cast<dxfConverter*>(&ob));
		break;
#endif
	case Object::object_type::fast_collection:
		ar >>  (*reinterpret_cast<FastCollection*>(&ob));
		break;

	case Object::object_type::surf_doc:
		ar >>  (*reinterpret_cast<SurfDoc*>(&ob));
		break;

	default:
		{
		}
	}


	//printf("Archive& operator >>(Archive& ar, Object& ob) end\n");
	return ar;
}
void Object::OnPaint()
{
	bool toDisableDepthTest = Object::CanDisableDepthTest() && this->ToDisableDepthTest();
	if (m_nglListNumber > 0)
	{
		if (toDisableDepthTest) glDisable(GL_DEPTH_TEST);	// Turn Depth Testing Off
//printf("pre ::glCallList(List = %u)\n", m_nglListNumber);
		::glCallList(m_nglListNumber);
//printf("pst ::glCallList(List = %u)\n", m_nglListNumber);
		if (toDisableDepthTest) glEnable(GL_DEPTH_TEST);	// Turn Depth Testing On
	}
}

#include <dime/dxfwriter.h>

bool Object::SaveAsDxf(char * outfile, CrdTranslator * translator)
{
	return save_as_dxf(this, outfile, false, translator);
}

tagPOINT Object::property_window_pt;
LRESULT CALLBACK PropertyWndProc_1( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	static HWND hwndButton;

	static vector<fmtstr> text;
	static SIZE text_size;

	static RECT margin; 


	static bool		m_bCaptured;		// Признак захвата мыши
	static tagPOINT		m_pt;				// Текущая позиция мыши

	switch (message) 
	{
	case WM_CREATE :
		{
			text.clear();
			text_size.cx = 0;
			text_size.cy = 0;
			//##################################################
			margin.left = 10;
			margin.right = 10;
			margin.top = 10;
			margin.bottom = 10;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLong(hWnd,	GWLP_USERDATA,(LONG)pcs->lpCreateParams);
			//##################################################
			//##################################################
			Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
			if (selected_object)
				selected_object->PrintfProperties(text);
			hdc = GetWindowDC(hWnd);
			if (selected_object)
				selected_object->Paint(text, hWnd, hdc, margin, text_size, true);

			if (1)
			{
				RECT rect;
				GetWindowRect(hWnd, &rect);
				hwndButton = CreateWindow( 
					"BUTTON",   // predefined class 
					"X",       // button text 
					WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 				 
					// Size and position values are given explicitly, because 
					// the CW_USEDEFAULT constant gives zero values for buttons. 
					rect.right - rect.left - 15,         // starting x position 
					3,         // starting y position 
					10,        // button width 
					10,        // button height 
					hWnd,       // parent window 
					(HMENU)IDCANCEL,       // menu 
					hInst,//(HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), 
					NULL);      // pointer not needed 

			   ShowWindow( hwndButton, SW_SHOW );
			}
		}
		break;

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
				if (selected_object)
					selected_object->Paint(text, hWnd, hdc, margin, text_size, false);
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN :
			{
				GetCursorPos(&m_pt);
				ScreenToClient(hWnd, &m_pt);

				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				if (m_bCaptured)
				{
					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
//#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				RECT rect;
				GetWindowRect(hWnd,&rect);

				rect.top -= (long)yDelta;

				SetWindowPos(hWnd, HWND_TOP, 
					rect.left, 
					rect.top, 
					0, 0, SWP_NOSIZE);

				//GetClientRect(hWnd,&rect);
				//InvalidateRect(hWnd,&rect, true);
			}
			break;
//#endif
		case WM_MOUSEMOVE :
			{
				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						POINT pt;
						GetCursorPos(&pt);	

						Object::property_window_pt.x = pt.x - m_pt.x;
						Object::property_window_pt.y = pt.y - m_pt.y - 1;

						SetWindowPos(hWnd, HWND_TOP, 
							Object::property_window_pt.x, 
							Object::property_window_pt.y, 
							0, 0, SWP_NOSIZE);

						//RECT rect;
						//GetClientRect(hWnd,&rect);
						//InvalidateRect(hWnd,&rect, true);
					}
				}
			}
			break;
/*		case WM_RBUTTONDOWN:
			{
				Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
				if (selected_object)
					selected_object->CreateMyPopupMenu(hWnd);
			}
			break;*/

		case WM_CHAR :
			{
				if (wParam == 27)//Esc
				{
					Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
					if (selected_object)
						selected_object->DestroyPropertyWindow();
				}
			}
			break;
		case WM_COMMAND :
			{
			switch( LOWORD( wParam ) )
			{
			case IDCANCEL :
				{
					Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
					if (selected_object)
						selected_object->DestroyPropertyWindow();
				}
				break;
			default:
				SendMessage(::GetParent(hWnd), message, wParam, lParam);
			}
         }
         break;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
LRESULT CALLBACK PropertyWndProc_2( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;

	static HWND hwndButton;

	static vector<LabData> labdata;
	static SIZE text_size;
	static bool text_size_do_not_determined;

	static RECT margin;  

	static bool		m_bCaptured;		// Признак захвата мыши
	static tagPOINT		m_pt;				// Текущая позиция мыши

	switch (message) 
	{
	case WM_CREATE :
		{
			labdata.clear();
			text_size.cx = 0;
			text_size.cy = 0;
			text_size_do_not_determined = true;
			//##################################################
			margin.left = 10;
			margin.right = 10;
			margin.top = 10;
			margin.bottom = 10;
			//##################################################
			CREATESTRUCT *pcs = (CREATESTRUCT *)lParam;
			SetWindowLong(hWnd,	GWLP_USERDATA,(LONG)pcs->lpCreateParams);
			//##################################################
			//##################################################
			Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
			if (selected_object)
				selected_object->PrintfProperties(labdata);

			hdc = GetWindowDC(hWnd);
			if (selected_object)
				selected_object->Paint(labdata, hWnd, hdc, margin, text_size, true);

			if (1)
			{
				RECT rect;
				GetWindowRect(hWnd, &rect);
				hwndButton = CreateWindow( 
					"BUTTON",   // predefined class 
					"X",       // button text 
					WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // styles 				 
					// Size and position values are given explicitly, because 
					// the CW_USEDEFAULT constant gives zero values for buttons. 
					rect.right - rect.left - 15,         // starting x position 
					3,         // starting y position 
					10,        // button width 
					10,        // button height 
					hWnd,       // parent window 
					(HMENU)IDCANCEL,       // menu 
					hInst,//(HINSTANCE) GetWindowLong(hWnd, GWL_HINSTANCE), 
					NULL);      // pointer not needed 

			   ShowWindow( hwndButton, SW_SHOW );
			}
		}
		break;

		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
				if (selected_object)
					selected_object->Paint(labdata, hWnd, hdc, margin, text_size, false);
				EndPaint(hWnd, &ps);
			}
			break;
		case WM_LBUTTONDOWN :
			{
				GetCursorPos(&m_pt);
				ScreenToClient(hWnd, &m_pt);
				//====== Захватываем сообщения мыши,
				//====== направляя их в свое окно
				SetCapture(hWnd);
				//====== Запоминаем факт захвата
				m_bCaptured = true;
				//====== Запоминаем координаты курсора
				SetFocus(hWnd);
			}
			break;
		case WM_LBUTTONUP :
			{
				if (m_bCaptured)
				{
					//====== Снимаем флаг захвата мыши
					m_bCaptured = false;
					//====== Отпускаем сообщения мыши
					ReleaseCapture();
				}
			}
			break;
//#if (_WIN32_WINNT >= 0x0400) || (_WIN32_WINDOWS > 0x0400)
		case WM_MOUSEWHEEL :
			{
				float yDelta = (float)(int) wParam; // wheel rotation 
				yDelta /= 300000.f;

				RECT rect;
				GetWindowRect(hWnd,&rect);

				rect.top -= (long)yDelta;

				SetWindowPos(hWnd, HWND_TOP, 
					rect.left, 
					rect.top, 
					0, 0, SWP_NOSIZE);

				//GetClientRect(hWnd,&rect);
				//InvalidateRect(hWnd,&rect, true);
			}
			break;
//#endif
		case WM_MOUSEMOVE :
			{
				if( wParam &  MK_LBUTTON)
				{
					if (m_bCaptured)		// Если был захват,
					{
						POINT pt;
						GetCursorPos(&pt);				
					
						Object::property_window_pt.x = pt.x - m_pt.x;
						Object::property_window_pt.y = pt.y - m_pt.y - 1;

						SetWindowPos(hWnd, HWND_TOP, 
							Object::property_window_pt.x, 
							Object::property_window_pt.y,  
							0, 0, SWP_NOSIZE);

						//RECT rect;
						//GetClientRect(hWnd,&rect);
						//InvalidateRect(hWnd,&rect, true);
					}
				}
			}
			break;

/*		case WM_RBUTTONDOWN:
			{
				Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
				if (selected_object)
					selected_object->CreateMyPopupMenu(hWnd);
			}
			break;*/
		case WM_CHAR :
			{
				if (wParam == 27)//Esc
				{
					Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
					if (selected_object)
						selected_object->DestroyPropertyWindow();
				}
			}
			break;
		case WM_COMMAND :
			{
			switch( LOWORD( wParam ) )
			{
			case IDCANCEL :
				{
					Object * selected_object = (Object *)GetWindowLong(hWnd, GWLP_USERDATA);
					if (selected_object)
						selected_object->DestroyPropertyWindow();
				}
				break;
			default:
				SendMessage(::GetParent(hWnd), message, wParam, lParam);
			}
         }
         break;
	case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}
LPCTSTR lpszPropertyWindow_1   = "PropertyWindow_1";
LPCTSTR lpszPropertyWindow_2   = "PropertyWindow_2";
bool RegisterPropertyWindowClass(int type)
{
	WNDCLASSEX wc;
	// Регистрация класса главного окна приложения.
	//............................................
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	switch(type)
	{
	case 1:
		{
			wc.lpfnWndProc   = (WNDPROC)PropertyWndProc_1;
			wc.lpszClassName = lpszPropertyWindow_1;
		}
		break;
	case 2:
		{
			wc.lpfnWndProc   = (WNDPROC)PropertyWndProc_2;
			wc.lpszClassName = lpszPropertyWindow_2;
		}
		break;
	}
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInst;
	wc.hIcon         = NULL;//LoadIcon( hInst, lpszWinGeoidName );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName  = NULL;
	wc.cbSize        = sizeof(WNDCLASSEX);
	wc.hIconSm       = NULL;

	if ( !RegisterClassEx( &wc ) )
	{
		if(1410 != GetLastError())// класс уже существует
		{
			MessageBox(0,"!RegisterClassEx","ProrertyWindow",0);
			return( FALSE );
		}
	}
	return true;
}
//HWND Object::hPropertyWindow = NULL; 

bool Object::PropertyWindow(HWND hWndParent)
{					
	long x = Object::property_window_pt.x;
	long y = Object::property_window_pt.y; 

	if (x < 0)	x = 0;
	if (y < 0)	y = 0;

	if (hPropertyWindow)
	{
		DestroyWindow(hPropertyWindow);
		hPropertyWindow = NULL;
	}

	if (!hPropertyWindow)
	{
		hPropertyWindow = CreateWindow(Laboratory::context_with_plot ? lpszPropertyWindow_2 : lpszPropertyWindow_1,
			"",//    LPCTSTR lpWindowName,
			WS_POPUP | WS_BORDER,
			x,y,
			1,//int nWidth,
			1,//   int nHeight,
			hWndParent,
			NULL,//    HMENU hMenu,
			hInst,//HINSTANCE hInstance,
			LPVOID(this)//LPVOID lpParam
			);

		ShowWindow(hPropertyWindow, SW_SHOW);
	}

	return true;
}
void Object::ReCreatePropertyWindow()
{
	HWND hWndParent = ::GetParent(hPropertyWindow);
	RECT rect;
	GetWindowRect(hPropertyWindow, &rect);

	DestroyWindow(hPropertyWindow);
	hPropertyWindow = CreateWindow(Laboratory::context_with_plot ? lpszPropertyWindow_2 : lpszPropertyWindow_1,
		"",//    LPCTSTR lpWindowName,
		WS_POPUP | WS_BORDER, //DWORD dwStyle,
		rect.left,
		rect.top,
		1,//int nWidth,
		1,//   int nHeight,
		hWndParent,//this->hSurfWnd,//HWND hWndParent,
		NULL,//    HMENU hMenu,
		hInst,//HINSTANCE hInstance,
		LPVOID(this)//LPVOID lpParam
		);

	ShowWindow(hPropertyWindow, 1);
}

#if 0
void Object::SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY)
{
	int shift = 10;

	HWND hWndParent = ::GetParent(hWnd);
	RECT rectParentClient;
	GetClientRect(hWndParent, &rectParentClient);
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWndParent, &pt);


	if (pt.x + CX + shift > rectParentClient.right)
	{
		if (pt.x - CX - shift > rectParentClient.left + shift/2)
			pt.x -= CX + shift;
		else
			pt.x = rectParentClient.left + shift/2;
	}
	else
	{
		pt.x += shift;
	}

	if (pt.y + CY + shift > rectParentClient.bottom)
	{
		if (pt.y - CY - shift > rectParentClient.top+shift/2)
		{
			pt.y -= CY + shift;
		}
		else
			pt.y = rectParentClient.top+shift/2;
	}
	else
	{
		pt.y += shift;
	}
	SetWindowPos(hWnd, HWND_TOP, 0,0, CX, CY, SWP_NOMOVE);
	//SetWindowPos(hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
}
#else
void Object::SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY)
{
	int shift = 1;

	HWND hWndParent = ::GetParent(hWnd);
	RECT rectParentClient;
	GetClientRect(hWndParent, &rectParentClient);
	
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWndParent, &pt);


	if (pt.x + CX + shift > rectParentClient.right)
	{
		if (pt.x - CX - shift > rectParentClient.left + shift/2)
			pt.x -= CX + shift;
		else
			pt.x = rectParentClient.left + shift/2;
	}
	else
	{
		pt.x += shift;
	}

	if (pt.y + CY + shift > rectParentClient.bottom)
	{
		if (pt.y - CY - shift > rectParentClient.top+shift/2)
		{
			pt.y -= CY + shift;
		}
		else
			pt.y = rectParentClient.top+shift/2;
	}
	else
	{
		pt.y += shift;
	}
	SetWindowPos(hWnd, HWND_TOP, 0,0, CX, CY, SWP_NOMOVE);
	ClientToScreen(hWndParent, &pt);
	SetWindowPos(hWnd, HWND_TOP, pt.x, pt.y, 0, 0, SWP_NOSIZE);
}



#endif