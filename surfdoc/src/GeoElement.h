#pragma once

#include <map>
using namespace std ;

#include "GeoObject.h"
#include "Ground.h"

class GeoColomn;
// базовый класс для элементов геологической колонки (разбивки) в документе
class GeoElement : public GeoObject
{
	friend Archive& operator >>(Archive& ar, GeoColomn& ob);
	DWORD m_geoelement_version;
protected:
	GeoColomn * my_geo_colomn;
	map<string, GeoElement *> sub_elements;
	string my_key;
	long my_id_key;//id_ige
	bool my_key_read;
	virtual void Init(long id_key);
public:
	ListViewTabGE m_ListViewTab;
	void SetGeoColomn(GeoColomn * c){my_geo_colomn = c;}
	enum type 
	{
		undefined_geo_element	=  0,
		stratigrafical			= 10, 
		lithological			= 20, 
		engineer_geological		= 30, 
		hydro_geological		= 40, 
		laboratory_exploration	= 50, 
		field_exploration		= 60, 
		faults					= 70 
	};

	static const char * GeoElementTypeToString(GeoElement::type t);
	GeoElement::type m_type;



	void SetKey(string key){my_key = key;}
	string GetKey() {return my_key;}
	long GetKeyID() {return my_id_key;}
	bool KeyRead() {return my_key_read;}

	//virtual
	void * operator new  (size_t size){return ::operator new  (size);}
	void operator delete  (void * p)  {return ::operator delete  (p);}

	static void * operator new  (size_t size, GeoElement::type, long id_key);
	static void operator delete  (void * p, GeoElement::type, long id_key);

	virtual void PrintfProperties() = 0;
	virtual bool ReadFile(const char *file) {return false;} // do this pure virtual = 0;
	
	virtual void PropertiesDialog();
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	virtual void FillContextMenu(HMENU& hMenu);

	void GeoElement_Serialize(Archive& ar);
	virtual void GeoElementSerialize(Archive& ar) = 0;

	virtual void ToGridData(BYTE podoshva) = 0;
	virtual void AddEmptyGridData(BYTE podoshva) = 0;

	long id_umpoz;
};

Archive& operator <<(Archive& ar, GeoElement::type & tp);
Archive& operator >>(Archive& ar, GeoElement::type & tp);

// базовый класс для элементов геологической колонки (разбивки) в скважине
class StratigraficalGeoElement : public GeoElement
{
	void Init(long id_key);
public:
	StratigraficalGeoElement(long id_key){Init(id_key);}
	virtual void PrintfProperties(){}
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);
	void GeoElementSerialize(Archive& ar);
	virtual void ToGridData(BYTE podoshva){}
	virtual void AddEmptyGridData(BYTE podoshva){}
};
#define LITHO_GEO_ELEMENT_VERSION 2
class LithoGeoElement : public GeoElement
{
	DWORD m_litho_geoelement_version;
	void Init(long id_key);

public:
	LithoGeoElement(long id_key){Init(id_key);}

	virtual COLORREF GetColor(){return lith_color;}
	virtual void SetColor(COLORREF color){lith_color = color;}
	virtual bool ColorDialog();

	virtual void PrintfProperties();
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);

	void LithoGeoElement_Serialize(Archive& ar);

	void SetGrountType(CGround::ground_type gt){m_ground_type = gt;}
	
	HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void ToGridData(BYTE podoshva);
	virtual void AddEmptyGridData(BYTE podoshva);

protected:
	COLORREF lith_color;
	CGround::ground_type m_ground_type;
	void GeoElementSerialize(Archive& ar);
};
#define ENG_GEO_ELEMENT_VERSION 2
struct LabTrialValueType;
class LabLayer;
#include "../../laboratory/src/Lab.h"

class EngineerGeoElement : public LithoGeoElement
{
	bool to_print_if_any;

	CGround * m_ground;
	void Init(long id_key);

	LabLayer * m_lablayer;

public:
	CGround::ground_type GetGroungType();
	FractionsLabTrialResults::SandSoilsClass GetSandSoilClass();
	FractionsLabTrialResults::ClaySoilsClass GetClaySoilClass();

	bool GetNormativePorostyFactor(double & e);
	bool GetNormativeDegreeOfMoisture(double & degree_of_moisture);
	bool GetNormativeFluidityIndex(bool ws, double & IL);

	void GroundType();




	bool GetValue(LabTrialValueType & vt, LabNormatives::type lab_normatives_type,
		double & v);

	void SetLabLayer(LabLayer * _lablayer){m_lablayer = _lablayer;}
	LabLayer * GetLabLayer() const {return m_lablayer;}



	virtual bool ColorDialog();

	bool WaterSaturation_Checked;

	void SetGround(CGround::ground_type gt);
	void ResetGround(CGround::ground_type gt);
	enum ValueType 
	{
		name												= 0, 
		ground_type,
		irrigation_type,
		sand_type,
		sand_strength,
		clay_solidity,
		specific_gravity_of_ground_particles,
		specific_gravity_of_ground,
		specific_gravity_of_dry_ground,
		specific_gravity_of_water_saturated_ground,
		specific_gravity_of_suspended_in_water_ground,
		porosity,
		natural_constitution_porosity_factor,
		natural_moisture,
		water_saturated_moisture,
		degree_of_moisture,
		lack_of_water_saturating,
		full_moisture_capacity,
		fluidity_index,
		fluidity_index_of_water_saturated_ground,
		plasticity_index, 
		moisture_on_fluidity_border,
		moisture_on_plasticity_border, 
		deformation_modulus,
		internal_friction_angle,
		specific_cohesion

	};
	static const char * ValueTypeToStringRus(EngineerGeoElement::ValueType value_type);
	static const char * ValueTypeToString(EngineerGeoElement::ValueType value_type);
	static bool ValueTypeIsStrength(EngineerGeoElement::ValueType value_type);
	static bool ValueTypeIsNumeric(EngineerGeoElement::ValueType value_type);


	enum GroundDescriptionType
	{
		//нормативные значения характеристик 
		normative = 0,
		//расчетные значения характеристик
		// при расчетах оснований:          
		// по деформациям:
		calculated_on_deformations,
		// по несущей способности   
		calculated_on_carry_ability
	};
	static const char * EngineerGeoElement::GroundDescriptionTypeToString(EngineerGeoElement::GroundDescriptionType gdt);

	enum StrengthDescriptionType
	{
		simple = 0,
		on_snip,
		water_saturated,
		in_task_condition,
		in_nature_condition,
		any
	};

	static const char * StrengthDescriptionTypeToString(EngineerGeoElement::StrengthDescriptionType sdt);

	bool GetValue(EngineerGeoElement::ValueType value_type,
		EngineerGeoElement::GroundDescriptionType ground_description_type,
		EngineerGeoElement::StrengthDescriptionType strength_description_type, 
		double & v);

	bool Get_Value(EngineerGeoElement::ValueType value_type,
		EngineerGeoElement::GroundDescriptionType ground_description_type,
		EngineerGeoElement::StrengthDescriptionType strength_description_type, 
		double & v);

	bool SetValue(EngineerGeoElement::ValueType value_type,
		EngineerGeoElement::GroundDescriptionType ground_description_type,
		EngineerGeoElement::StrengthDescriptionType strength_description_type, 
		double v, bool defined = true);

	const CGround * GetGround () const { return m_ground;}
	CSand * GetSand ();
	CClayGround * GetClayGround ();
	void SetIrrigationType(const CGround::irrigation_type t){if (m_ground) m_ground->m_irrigation_type = t;}

	EngineerGeoElement(long id_key) : LithoGeoElement(id_key){Init(id_key);}
	virtual void PrintfProperties();

	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);

	int ReadingFile(FILE * stream,  char* szBuff, int n);
	int ParseFileLine(char* szBuff, int type_line);
	bool ReadFile(const char *file);
	bool ReadKey(char *szBuff);

	void GeoElementSerialize(Archive& ar);

	bool to_print_repeating_warning;

	void ToPrintIfAny(){to_print_if_any = true;}
	void UpdateProps();

	void FillListViewTab(bool to_resize);
	HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void ToGridData(BYTE podoshva);
	virtual void AddEmptyGridData(BYTE podoshva);

	virtual bool SaveAs();
	bool SaveGroundAsDat(const char * fn);


	enum Typ_Shtrihovki
	{
		ts_unknown = 0,
		ts_4_1,
		ts_4_2,
		ts_4_3,
		ts_4_4,
		ts_4_5,
		ts_4_6,
		ts_4_7
	};

	Typ_Shtrihovki Get_Typ_Shtrihovki();
};
// Define a postfix increment operator
inline EngineerGeoElement::ValueType operator++( EngineerGeoElement::ValueType &rs, int )
{
   return rs = (EngineerGeoElement::ValueType)(rs + 1);
}

inline EngineerGeoElement::StrengthDescriptionType operator++( EngineerGeoElement::StrengthDescriptionType &rs, int )
{
   return rs = (EngineerGeoElement::StrengthDescriptionType)(rs + 1);
}

inline EngineerGeoElement::GroundDescriptionType operator++( EngineerGeoElement::GroundDescriptionType &rs, int )
{
   return rs = (EngineerGeoElement::GroundDescriptionType)(rs + 1);
}
class HydroGeoElement : public GeoElement
{
public:
	bool ustanovlen;// установившийся ли уровень
	void Init(long id_key);
	HydroGeoElement(long id_key){Init(id_key);}
	virtual void PrintfProperties(){}
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);
	void GeoElementSerialize(Archive& ar);
	virtual void ToGridData(BYTE podoshva);
	virtual void AddEmptyGridData(BYTE podoshva);
};
class LabGeoElement : public GeoElement
{
	void Init(long id_key);
public:
	LabGeoElement(long id_key){Init(id_key);}
	virtual void PrintfProperties(){}
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);
	void GeoElementSerialize(Archive& ar);
	virtual void ToGridData(BYTE podoshva){}
	virtual void AddEmptyGridData(BYTE podoshva){}
};

class FieldGeoElement : public GeoElement
{
	void Init(long id_key);
public:
	FieldGeoElement(long id_key){Init(id_key);}
	virtual void PrintfProperties(){}
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);
	void GeoElementSerialize(Archive& ar);
	virtual void ToGridData(BYTE podoshva){}
	virtual void AddEmptyGridData(BYTE podoshva){}
};


class FaultGeoElement : public GeoElement
{
	void Init(long id_key);
public:
	FaultGeoElement(long id_key){Init(id_key);}
	virtual void PrintfProperties(){}
	//virtual void PropertiesDialog();
	//virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	//virtual void FillContextMenu(HMENU& hMenu);
	void GeoElementSerialize(Archive& ar);
	virtual void ToGridData(BYTE podoshva){}
	virtual void AddEmptyGridData(BYTE podoshva);
};





// колонка гео элементов в документе
class GeoColomn  : public GeoObject
{
	friend class GeoElement;
	friend class EngineerGeoElement;
	void Init();
public:
	GeoElement::type m_type;
	map<string, GeoElement*> geo_elements;
	long GetNewKeyID();
	GeoColomn(){this->Init(); m_type = GeoElement::type::undefined_geo_element;}
	GeoColomn(GeoElement::type t, SurfDoc * doc){this->Init(); m_type = t; this->m_pSurfDoc = doc;}
	virtual void PropertiesDialog();
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");
	virtual void FillContextMenu(HMENU& hMenu);

	GeoElement * CreateNewGeoElement(GeoElement::type t, long id_key);
	GeoElement * AddNewGeoElement(string key, GeoElement * geo_element);
	GeoElement * FindGeoElement(string key);
	GeoElement * FindGeoElement(long id_key);
	void AddNewGeoElement();
	void AddEmptyGeoElement();
	GeoElement * AddEmptyGeoElement(const char * key, CGround::ground_type gt, long id_key);

	void ToGridData(BYTE podoshva);

	friend Archive& operator <<(Archive& ar, GeoColomn& ob);
	friend Archive& operator >>(Archive& ar, GeoColomn& ob);
};

LPARAM CreateLParam(EngineerGeoElement::ValueType value_type,
					EngineerGeoElement::GroundDescriptionType ground_description_type,
					EngineerGeoElement::StrengthDescriptionType strength_description_type);
bool ParseLParam(LPARAM lParam,
				 EngineerGeoElement::ValueType & value_type,
				 EngineerGeoElement::GroundDescriptionType & ground_description_type,
				 EngineerGeoElement::StrengthDescriptionType & strength_description_type);
