#pragma once

#include "GeoElement.h"

class MyAcad;

class WellColomn;
class Profile3D;
class Well_3D;
class GridData;
struct wells_draw_list_item;

#define WELL_ELEMENT_DRAW_GDI_PLUS 0
struct GridDataPointRef
{
	long id_surf;
	long id_point;

	GridDataPointRef()
	{
		id_surf = -1;
		id_point = -1;
	}
};

class WellElement
{
	GLuint m_nglListNumber;
	DWORD m_base_wellelement_version;// верси€ класса родител€
protected:
	DWORD m_this_wellelement_version; // верси€ класса потомка
	double zk;//альтитуда кровли 
	double zp;//альтитуда подошвы 


	friend void To_GridData(WellColomn * pWellColomn, WellElement * pWellElem, GridData * pData, BYTE podoshva);


	WellColomn * well_colomn;
	string nameID;//им€ идентификатор
	friend class WellColomn;
	friend class project;
	WellElement();
	virtual ~WellElement();
public:

	GridDataPointRef grid_data_point_zk;
	GridDataPointRef grid_data_point_zp;

	void Init();
	enum type 
	{
		undefined_well_element	= 0,
		primitive_ref			= 10, 
		litho_podoshva			= 20, 
		IGE_podoshva			= 30, 
		isSand_podoshva			= 40, 
		hydro_projavlenie		= 50,
		laboratory_analizes		= 60
	};
	static const char * WellElementTypeToString(WellElement::type t);
	WellElement::type w_type;

	void * operator new  (size_t size){return ::operator new  (size);}
	void operator delete  (void * p)  {return ::operator delete  (p);}

	static void * operator new  (size_t size, WellElement::type);
	static void operator delete  (void * p, WellElement::type);

	void SetNameID(string ID){nameID = ID;}
	string GetNameID(){return nameID;}

	void SetWellColomn(WellColomn * wc){well_colomn = wc;}
	const WellColomn * GetWellColomn() const {return well_colomn;}	

	virtual void PrintfProperties() = 0;
	virtual void PrintfProperties(vector<fmtstr> & text) = 0;
	double GetZk(){return zk;}
	double GetZp(){return zp;}

	void WellElement_Serialize(Archive& ar);
	virtual void WellElementSerialize(Archive& ar) = 0;

	void Draw(Well_3D * well);
	void ReDraw(Well_3D * well);
	virtual void Drawing(Well_3D * well) = 0;
	virtual void OnPaint();

#if WELL_ELEMENT_DRAW_GDI_PLUS
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli) = 0;
#endif
	void EditLitoInDB(SurfDoc * pSurfDoc, long ID_KT, double ustje_z, double key_H0, bool edit_H0, bool edit_H1);


};

Archive& operator <<(Archive& ar, WellElement::type & tp);
Archive& operator >>(Archive& ar, WellElement::type & tp);

class Well_IGE_Podoshva : public WellElement
{
	string key;// ключ »√Ё
	long id_ige; // ID_IGE в базе 
	COLORREF color;
	long id_umpoz;
	string umpoz, hatchacad;
	double angle, scale;
	friend class Well_3D;
	friend class WellColomn;
public:
	Well_IGE_Podoshva();
	virtual ~Well_IGE_Podoshva();

	virtual void PrintfProperties();
	virtual void PrintfProperties(vector<fmtstr> & text);


	void SetColor(COLORREF c){color = c;}
	COLORREF GetColor(){return color;}

	void SetKey(string k){key = k;}
	string GetKey(){return key;}
	long Get_ID_IGE(){return id_ige;}

	virtual void Drawing(Well_3D * well);
#if WELL_ELEMENT_DRAW_GDI_PLUS
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
#endif
	virtual void WellElementSerialize(Archive& ar);
};

class Well_Litho_Podoshva : public WellElement
{
	string key;// ключ »√Ё
	long id_ige; // ID_IGE в базе 
	COLORREF color;
	long id_umpoz;
	string umpoz, hatchacad;
	double angle, scale;
	friend class Well_3D;
	friend class WellColomn;
public:
	Well_Litho_Podoshva();
	virtual ~Well_Litho_Podoshva();

	virtual void PrintfProperties();
	virtual void PrintfProperties(vector<fmtstr> & text);

	void SetColor(COLORREF c){color = c;}
	COLORREF GetColor(){return color;}

	void SetKey(string k){key = k;}
	string GetKey(){return key;}
	long Get_ID_IGE(){return id_ige;}
	virtual void Drawing(Well_3D * well);
#if WELL_ELEMENT_DRAW_GDI_PLUS
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
#endif
	virtual void WellElementSerialize(Archive& ar);
};
class Well_IsSand_Podoshva : public WellElement
{
	friend class Well_3D;
	//double z;//альтитуда подошвы 
	bool isSand;// песок или пылеватоглинистый грунт
public:
	bool IsSand(){return isSand;}
	Well_IsSand_Podoshva();
	virtual ~Well_IsSand_Podoshva();

	virtual void PrintfProperties();
	virtual void PrintfProperties(vector<fmtstr> & text);


	COLORREF GetColor()
	{
		if(isSand)
			return RGB(255,255,0);
		else
			return RGB(128,64,0);
	}
	virtual void Drawing(Well_3D * well);
#if WELL_ELEMENT_DRAW_GDI_PLUS
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
#endif
	virtual void WellElementSerialize(Archive& ar);

};

class Well_Hydro_Projavlenie : public WellElement
{
	//double z;//альтитуда гидропро€влени€ 
	bool ustanovlen;// установившийс€ ли уровень
	long horizont;
	friend class Well_3D;
public:
	bool Ustanovlen() {return ustanovlen;}
	long Horizont() {return horizont;}

	Well_Hydro_Projavlenie();
	virtual ~Well_Hydro_Projavlenie();

	virtual void PrintfProperties(vector<fmtstr> & text);


	virtual void PrintfProperties();
	virtual void WellElementSerialize(Archive& ar);
	virtual void Drawing(Well_3D * well);
#if WELL_ELEMENT_DRAW_GDI_PLUS
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
#endif
};

class LabNumber;

#include "../../laboratory/src/baselab.h"
#include "../../laboratory/src/lab.h"

class Well_Laboratory_Analize : public WellElement, public BaseLab
{

	LabNumber * lab_number;
	string Lab_Layer_ID;
	string Lab_Layer_Number;
	string Lab_Number_ID;


	friend class Well_3D;
	friend class WellColomn;
	friend class project;
public:
	enum label_type
	{
		undefined_label_type = 0,
		lab_layer_id,
		lab_layer_number,
		lab_number_id,
		soils_description,
		end
	};
	static label_type s_label_type;

	static const char * LabelTypeToString(Well_Laboratory_Analize::label_type lt);

	string GetLabel(Well_Laboratory_Analize::label_type lt);

	Well_Laboratory_Analize();
	virtual ~Well_Laboratory_Analize();

	void InitByLabNumber(LabNumber * ln, double ustje_z);
	void ReInitByOwnLabNumber();

	/*virtual*/ void PrintfProperties(vector<fmtstr> & text);
	/*virtual*/ void PrintfProperties(vector<LabData> & labdata);
	virtual void PrintfProperties();
	virtual void WellElementSerialize(Archive& ar);
	virtual void Properties();

	virtual void Drawing(Well_3D * well);
#if WELL_ELEMENT_DRAW_GDI_PLUS
	virtual void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
#endif
	bool LabLayerCheckDraw();
	void OnPaint();

	void PropSave(bool context_with_plot);
	void Passport();
	void Passport(const char * fn);
	static void FillPopupMenu(HMENU & hMenu, HMENU & hSubMenu, HMENU & hSubMenu2);
	void CreateMyPopupMenu(HWND hWnd);

    virtual void SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY);


};

inline Well_Laboratory_Analize::label_type operator++( Well_Laboratory_Analize::label_type &rs, int )
{
   return rs = (Well_Laboratory_Analize::label_type)(rs + 1);
}
/*
class WellElement : public BaseWellElement
{
	GeoElement * base;
	vector<float> geo_element_keys;
public:
	virtual void PrintfProperties() = 0;
};*/
class ParticularWellElement : public WellElement
{
	CGround * m_ground;
};

class LithoWellElement : public WellElement
{
	void Init();
public:
	LithoWellElement(){Init();}
	void PrintfProperties(){}
};
#define WELLS_DRAW_LIST_ITEM_VERSION 2

struct wells_draw_list_item
{
	DWORD version;
	WellElement::type w_type;
	bool check_draw;
	float draw_width;
	int id;
	string my_name;

	enum draw_mode_2d {right = 1, left = 2, both = 3};
	draw_mode_2d m_draw_mode_2d;
	bool draw2d_border;
	bool draw2d_label;
	bool draw2d_sloj_name;
	COLORREF border_color;



	wells_draw_list_item()
	{
		version = WELLS_DRAW_LIST_ITEM_VERSION;
		w_type = WellElement::type::undefined_well_element;
		check_draw = false;
		draw_width = 2.f;
		id = -1;
		my_name = "";

		m_draw_mode_2d = draw_mode_2d::both;
		draw2d_border = true;
		border_color = RGB(0,0,0);
	}
	wells_draw_list_item(WellElement::type t, bool check, float width, int _id, string name, wells_draw_list_item::draw_mode_2d drawmode2d)
	{
		version = WELLS_DRAW_LIST_ITEM_VERSION;
		w_type = t;
		check_draw = check;
		draw_width = width;
		id = _id;
		my_name = name;

		m_draw_mode_2d = drawmode2d;
		draw2d_border = true;
		draw2d_label = true;
		draw2d_sloj_name = false;
		border_color = RGB(0,0,0);
	}
	void Serialize(Archive& ar);

	friend Archive& operator <<(Archive& ar, wells_draw_list_item * ob);
	friend Archive& operator >>(Archive& ar, wells_draw_list_item *& ob);
};


class Well_3D;
// колонка гео элементов в скважине
class WellColomn
{

	friend class Well_3D;
	friend class project;
	DWORD well_colomn_version;

	SurfDoc * m_pSurfDoc;
	wells_draw_list_item * m_wdli;// указатель на €чейку из списка отрисовки скважины

	void Init();
	WellElement::type w_type;
	Well_3D * m_pWell;
	//map<string, WellElement*> well_elements;
	vector<WellElement*> well_elements;
	WellElement * CreateNewWellElement(WellElement::type t);
public:
	Well_3D * GetWell() {return m_pWell;}
	void clear()
	{
		for (vector<WellElement*>::iterator it = this->well_elements.begin();
			it !=  this->well_elements.end(); it++)
		{
			if (*it) delete (*it);
			(*it) = NULL;
		}
		this->well_elements.clear();
	}

	size_t GetWellElementSize()
	{
		return this->well_elements.size();
	}


	void Init(const WellColomn &wc)
	{
//		this->m_nglListNumber		= wc.m_nglListNumber;
		this->well_colomn_version	= wc.well_colomn_version;
		this->well_elements			= wc.well_elements;
		this->w_type				= wc.w_type;
		this->m_wdli_id				= wc.m_wdli_id;
		this->m_wdli				= wc.m_wdli;
		this->m_pWell				= wc.m_pWell;
		this->m_pSurfDoc			= wc.m_pSurfDoc;
	}
	WellColomn(const WellColomn& ob);
	WellColomn& operator=(const WellColomn& ob);

	int m_wdli_id;//идентификатор €чейки из списка отрисовки скважины

	WellElement::type GetType(){return w_type;}
	void InitDoc(SurfDoc *pSurfDoc)
	{
		m_pSurfDoc = pSurfDoc;
	}
	void InitWell(Well_3D * well){m_pWell = well;}
	WellElement::type GetWellElementType(){return w_type;}
	WellColomn();
	virtual ~WellColomn();

	WellColomn(WellElement::type t, Well_3D * well, wells_draw_list_item * wdli);
	virtual void PropertiesDialog();
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	bool IsWellElement(const WellElement * p1);

	WellElement * FindWellElement(string ID);
	WellElement * AddNewWellElement(string ID, WellElement * well_element);
	WellElement * AddNewWellElement(string ID);

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);


	void OnPaint(Well_3D * well);
private:
	//void Drawing(Well_3D * well);
public:
	void ReDraw(Well_3D * well);
	void Draw(Well_3D * well);

	//void Draw_Litho(Well_3D * well, wells_draw_list_item * wdli);
	//void Draw_IGE(Well_3D * well, wells_draw_list_item * wdli);
	//void Draw_Hydro(Well_3D * well, wells_draw_list_item * wdli);
	//void Draw_IsSand(Well_3D * well, wells_draw_list_item * wdli);
	//void Draw_LaboratoryAnalizes(Well_3D * well, wells_draw_list_item * wdli);

	void DrawGDIplus(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well);
#if !WELL_ELEMENT_DRAW_GDI_PLUS
	void DrawGDIplus_Litho(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
	void DrawGDIplus_IGE(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
	void DrawGDIplus_Hydro(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
	void DrawGDIplus_IsSand(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
	void DrawGDIplus_LaboratoryAnalizes(Graphics ** select_buffer, Graphics& graphics, map_view * v, Profile3D * on, Well_3D * well, wells_draw_list_item * wdli);
#endif

	void DrawAcad                   (MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well);

	void DrawAcad_Litho             (MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli);
	void DrawAcad_IGE               (MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli);
	void DrawAcad_Hydro             (MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli);
	void DrawAcad_IsSand            (MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli);
	void DrawAcad_LaboratoryAnalizes(MyAcad & m_acad, double xProfile, double w, double Height_lin, COLORREF color, double v_scale, double g_scale, double well_hatch_scale, Well_3D * well, wells_draw_list_item * wdli);

	void SetWellElementsIGEkeys();
	void SetColorFromIGE();
	void IGEZabojToGridData(string geo_element_key, GridData * pData);
	void IGEPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse);
	int IGEPodoshvaHowMany(string geo_element_key);

	void SetWellElementsLithoKeys();
	void SetColorFromLitho();
	void LithoPodoshvaToGridData(int isurf, BYTE podoshva, string geo_element_key, GridData * pData, bool reverse);
	int LithoPodoshvaHowMany(string geo_element_key);


	void HydroProjavlenieToGridData(long horizont, bool ust, GridData * pData);
	void HydroProjavlenieHowMany(map<long, long> &gorizonts, bool ust);


	void SaveIGEToDB(long ID_KT, double ustje_z);
	void SaveLitoToDB(long ID_KT, double ustje_z);


	friend Archive& operator <<(Archive& ar, WellColomn& ob);
	friend Archive& operator >>(Archive& ar, WellColomn& ob);
};


