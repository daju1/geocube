// Object.h: interface for the Object class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBJECT_H__4ECD2B30_644C_4658_B548_041DDC56742B__INCLUDED_)
#define AFX_OBJECT_H__4ECD2B30_644C_4658_B548_041DDC56742B__INCLUDED_

#include "../../configure.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class WhatSelected;
//#include ".\whatselected.h"
#include "points.h"


class ObjectList;
class Archive;
class SurfDoc;
class Layer;

//#define UNICODE
#if defined (_MSC_VER) && !defined (QT_PROJECT)
#include <GL/gl.h>
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#else
#include <mywindows.h>
#endif

class map_view;

class dimeModel;
class dimeBlock;

class CrdTranslator;

class Line3D;

#define OBJECT_FLAG_INSIDE_BLANK_BIT 0x00000001
#define OBJECT_FLAG_SELECTED_BIT	 0x00000002
#define OBJECT_FLAG_THING_BIT		 0x00000004

#include "../../laboratory/src/BaseLab.h"

class Object : public BaseObject
{
	//- используется как ключ при поиске однотипных объектов
	static DWORD s_max_base_version;
	DWORD m_base_version;//версия класса-родителя Object
	friend class ObjectList;
	friend LRESULT CALLBACK DlgProcSurfIzolines2( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
	friend bool save_as_dxf(Object * ob, char * outfile, bool useblock, CrdTranslator * translator);
	friend void print_line(Line3D * line3D, dimeModel * model, dimeBlock * block, CrdTranslator * translator = NULL);
protected:
	bool m_toDisableDepthTest;
	static bool s_canDisableDepthTest;
	Object * m_parent;
	string name;//имя объекта, присваивоемое пользователем
	int m_UserID;// пользовательский идентифиатор объекта, 
	static DWORD s_UserID_forCompare;
	static string s_name_forCompare;
	int layerID;
	Layer * pLayer;
	CPoint3 m_ptMax;
	CPoint3 m_ptMin;
	SurfDoc* m_pSurfDoc;
	DWORD m_max_object_version;//версия объекта - потомка от класса Object которую надо использовать при сохранении той или иной версии документа
	DWORD m_object_version;//версия объекта - потомка от класса Object
	bool m_bIsObjectList;
	bool m_bIsPrimitive3;// if class is derived from Primitive<CPoint3>
	bool m_bIsPrimitive4;// if class is derived from Primitive<CPoint4>
	ObjectList * m_pObjectList;
	GLuint m_nglListNumber;
//	int typeID;
//	char * object_filename;
protected:
public:
	enum 
		container_type { 
		container_none = 0, 
		container_vect, 
		container_Vector, 
		container_Vector_Vector, 
		container_std_vector,
		container_std_vector_std_vector,
		container_std_map
	};
	static bool CanDisableDepthTest(){return Object::s_canDisableDepthTest;}
	static void CanDisableDepthTest(bool can){Object::s_canDisableDepthTest = can;}

	bool ToDisableDepthTest(){return this->m_toDisableDepthTest;}
	void DisableDepthTest(bool b){this->m_toDisableDepthTest = b;}

	Object * GetParent(){return m_parent;}
	void SetParent(Object * parent){this->m_parent = parent;}
	virtual void SetName(string s){this->name = s; this->make_translit = true;}
	string GetName(){return this->name;}

	string GetNameTranslit();
	bool make_translit;
	string name_translit;


	bool SetNameDlg();

	ObjectList * GetObjectList(){return m_pObjectList;}


	static void SetObjectUserID_forCompare(DWORD id){s_UserID_forCompare = id;}
	static void SetObjectName_forCompare(string s){s_name_forCompare = s;}
	bool IsTheSameUserID(){return this->m_UserID == Object::s_UserID_forCompare;}
	bool IsTheSameName(){return this->name == Object::s_name_forCompare;}
	int GetUserID(){return m_UserID;}
	void SetUserID(int id){m_UserID = id;}

	void SetLayer_NonVirtual(const Layer* layer);
	virtual void SetLayer(const Layer* layer)=0;
	Layer* GetLayer(){return pLayer;}
	int GetLayerID(){return layerID;}

	bool ReturnTrue(){return true;}
	bool IsSelected(){return 0 != (this->m_lParam & OBJECT_FLAG_SELECTED_BIT);}
	bool IsUnselected()
	{
		return 
			!(this->m_lParam & OBJECT_FLAG_SELECTED_BIT) && 
			!this->m_bIsObjectList && 
			(m_bIsPrimitive3 || m_bIsPrimitive4);
	}
	void Select(bool to_select)
	{
		if (to_select)
		{
			// SELECT OBJECT - включаем 2-й бит 
			// в пользовательских данных объекта 
			this->m_lParam |= OBJECT_FLAG_SELECTED_BIT;
		}
		else
		{
			// UN SELECT OBJECT - выключаем 2-й бит 
			// в пользовательских данных объекта
			this->m_lParam &= ~OBJECT_FLAG_SELECTED_BIT;
		}
	}

	bool IsPrimitive3(){return m_bIsPrimitive3;}
	bool IsPrimitive4(){return m_bIsPrimitive4;}
	void InitDoc(SurfDoc *pSurfDoc)
	{
		m_pSurfDoc = pSurfDoc;
	}
	const SurfDoc * GetDoc() const
	{ return m_pSurfDoc;}

	enum object_type { 
		undefined				= 0, 
		// объекты
		object					= 10,	
		object_list				= 20, 

		geo_colomn				= 22,
		well_colomn				= 24,
		// the primitive template
		primitive3d				= 30,
		// primitive template childrens
		thepoint3d				= 40,
		line3d					= 50,
		inter_wells_line_3d		= 51,
		surface3d				= 60,
		cube4d					= 65,
		triangle3d				= 70,
		poligon3d				= 80, 
		sphere3d				= 90,
		string3d				=100, // test string serialize  ????
		well_3d					=110, //not full serialized
		karotazh				=115, //not full serialized
		bmp3d					=120, // ---
		bmp_profile3d			=125, // ---

		// compound objects
		bln_profile3d			=140,
		bln_profile_plane3d		=150,

		broken_plane3d			=160,
		broken_line3d			=170,
		broken_poligon3d		=180,
		broken_poligon_3d		=190,

		grid_profile3d			=200,
		triangulated_grid3d		=210,

		//
		geo_surface				=220,
		geo_catch				=230,
		grid_data				=240,
		collection				=250,
		auto_profile_building	=260,
#if DFX_LAYER_FROM_OBJECT
		dfx_layerdata			=270,
		dfx_converter			=280,
#endif
		fast_collection			=285,


		//Document
		surf_doc				=300
	};

//	Object* operator->();

	void* operator new  (size_t size){return ::operator new  (size);}
	void* operator new[](size_t size){return ::operator new[](size);}
	void operator delete  (void *p)  {return ::operator delete  (p);}
	void operator delete[](void *p)  {return ::operator delete[](p);}

	static void* operator new  (size_t size, object_type);
	static void* operator new[](size_t size, object_type);
	static void operator delete  (void*p, object_type);//{::operator delete[](p);}
	static void operator delete[](void*p, object_type);//{::operator delete[](p);}

	virtual void OnDestroy();

	CPoint3 GetMin()
	{
		return m_ptMin;
	}
	CPoint3 GetMax()
	{
		return m_ptMax;
	}
	void SetMin(CPoint3& pt)
	{
		m_ptMin = pt;
	}
	void SetMax(CPoint3& pt)
	{
		m_ptMax = pt;
	}
protected:
	object_type m_object_type;
public:
	object_type GetObjectType() const {return m_object_type;}


	static const char * ObjectTypeToString(object_type type);

	DWORD GetVersion(){return m_object_version;}
	void SetVersion(DWORD version){m_object_version = version;}

	LPARAM m_lParam; // user data

	//HTREEITEM insertAfter;
	HTREEITEM parentTreeItem;
	HTREEITEM myTreeItem;

	bool m_bChecked;
	bool m_bExpanded; // for objectLists

	void Init(const Object& ob);
	Object(const Object& ob);
	//====== Операция присвоения
	Object& Object::operator=(const Object& ob);
	bool UpdateExtremums(vector<CPoint3>& vptmax, vector<CPoint3>& vptmin);
	virtual bool UpdateExtremums(CPoint2 & profile_min, CPoint2 & profile_max){return false;}
	void Zooming();
	//##########################################################
	// pure virtual functions
	virtual bool UpdateExtremums() = 0;
	virtual void Zoom(double zoomX, double zoomY, double zoomZ, double x_mean, double y_mean, double z_mean) = 0;
	virtual void CutAndDisvisible(bool positive, double a, double b, double c, double d) = 0;
	virtual void CutXYZandDisvisible(int subcube_number, double X, double Y, double Z) = 0;

	static tagPOINT property_window_pt;
	bool PropertyWindow(HWND hWndParent);
	void ReCreatePropertyWindow();
	static HWND hPropertyWindow; 
	void DestroyPropertyWindow(){DestroyWindow(hPropertyWindow); hPropertyWindow = NULL;}
	void SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY);
	virtual void PrintfProperties(vector<fmtstr> & text){}// = 0;
	virtual void PrintfProperties(vector<LabData> & labdata){}// = 0;



	virtual void PropertiesDialog() = 0;
	virtual bool ColorDialog() = 0;
	virtual COLORREF GetColor() = 0;
	virtual void SetColor(COLORREF color) = 0;

	virtual bool IsSelected(CPoint3 selected_view_pt, 
		double search_radius,
		WhatSelected& ws) = 0;

	virtual void EnumObjects(WPARAM wParam, LPARAM lParam, void * p,
		bool (Object::* condition_fun)(),
		void (* callback_fun)(Object*, WPARAM, LPARAM, void * ) ) = 0;

	virtual void ReDraw() = 0;
	virtual void Draw() = 0;
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s) = 0;

	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * ){}

	virtual bool SaveAs() = 0;
	virtual bool SaveAsBln(FILE * stream) = 0;
	virtual bool SaveAsBln(FILE * stream, CrdTranslator & translator){return false;}
	virtual bool SaveAsDat(FILE * stream) = 0;
	virtual bool SaveAsDxf(dimeModel * model, dimeBlock * block, CrdTranslator * translator){return false;}
	bool SaveAsDxf(char * outfile, CrdTranslator * translator);
	// end of pure virtual functions
	//##########################################################
	void ReDrawItem_OnTree(HWND hwndTV);
	bool IsCheckedEx();
	bool Delete();
	virtual /*void*/ DWORD Serialize(Archive& ar);
	bool ToLayer();//override in ObjectList

	virtual void FillContextMenu(HMENU& hMenu)/* = 0*/;
	void CreateContextMenu(HWND hWnd, LPARAM lParam);

	GLuint GetListNumber()
	{
		return m_nglListNumber;
	}
	virtual void OnPaint();

	void Init();
	Object();
	virtual ~Object();

	friend Archive& operator <<(Archive& ar, Object& ob);
	friend Archive& operator >>(Archive& ar, Object& ob);

};

#endif // !defined(AFX_OBJECT_H__4ECD2B30_644C_4658_B548_041DDC56742B__INCLUDED_)
