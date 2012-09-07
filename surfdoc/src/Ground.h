#pragma once

#include "../../tools/src/listviewtab.h"

#define USE_LISTVIEW_STANDART_GE 1
#if USE_LISTVIEW_STANDART_GE
#define ListViewTabGE ListViewTab
#else
#define ListViewTabGE ListViewTab2
#endif


#define LOG_UNPARSED 1

#define ISNUM(p) ( \
	( ( *p >= 48 && *p <= 57) || ( 46 == *p && *(p+1) >= 48 && *(p+1) <= 57 ) ) \
	|| \
	( \
	(*p == '-' || *p == '+') \
	&& \
	( ( *(p+1) >= 48 && *(p+1) <= 57 ) ||  (46 == *(p+1) && *(p+2) >= 48 && *(p+2) <= 57 ) )\
	) \
	)
class Archive;
// прочностные характеристики грунта
struct StrengthDescription
{
	DWORD m_strength_description_version;

	void Init();
	void PrintfProperties();
	bool Defined();

	// модуль деформации грунта
	double deformation_modulus;
	bool deformation_modulus_defined;

	// угол внутреннего трения
	double internal_friction_angle;
	bool internal_friction_angle_defined;

	// удельное сцепление грунта
	double specific_cohesion;
	bool specific_cohesion_defined;

	friend Archive& operator <<(Archive& ar, StrengthDescription & sd);
	friend Archive& operator >>(Archive& ar, StrengthDescription & sd);

	void SavingAsDat(FILE * stream);


};
// Характеристики грунта
struct GroundDescription
{
	DWORD m_ground_description_version;
	void Init();
	void PrintfProperties();

/*
// что даёт лаборатория
// ====================
// влажность природная (доли ед.)                              .19

// удельный вес частиц грунта,кн/м3                          26.68
// удельный вес грунта,кн/м3                                 18.15

// что рассчитывается по формулам
// ==============================
// число пластичности                                          .13         ?

// влажность водонасыщения (доли ед.)                          .26         ?
// показатель текучести                                       -.08         ?
// показатель текучести водонасыщ.грунта                       .48         ?

// удельный вес сухого грунта,кн/м3                          15.30         ?
// удельный вес водонасыщенного грунта,кн/м3                 19.33         ?
// удельный вес взвешенного в воде грунта,кн/м3               9.64         ?
// пористость (доли ед.)                                       .43         ?
// коэффициент пористости природного слож.доли ед.             .75         ?

// степень влажности                                           .69         ?

// недостаток водонасыщения(доли ед.)                          .07         ?
// полная влагоемкость                                         .28         ?

// в супесях
 I модуль деформации грунта водон. состоян.в мпа              7.0          I
 I угол внутреннего трения в водонасыщ. сост., град.         24            I
 I удельное сцепление грунта в водонас. сост., мпа            0.017        I
 */

	// удельный вес частиц грунта,кн/м3                          26.68
	double specific_gravity_of_ground_particles;
	bool specific_gravity_of_ground_particles_defined;
	// удельный вес грунта,кн/м3                                 18.15
	double specific_gravity_of_ground;
	bool specific_gravity_of_ground_defined;
	// удельный вес сухого грунта,кн/м3                          15.30
	double specific_gravity_of_dry_ground;
	bool specific_gravity_of_dry_ground_defined;
	// удельный вес водонасыщенного грунта,кн/м3                 19.33
	double specific_gravity_of_water_saturated_ground;
	bool specific_gravity_of_water_saturated_ground_defined;
	// удельный вес взвешенного в воде грунта,кн/м3               9.64
	double specific_gravity_of_suspended_in_water_ground;
	bool specific_gravity_of_suspended_in_water_ground_defined;

	// пористость (доли ед.)                                       .43
	double porosity;
	bool porosity_defined;
	// коэффициент пористости природного слож.доли ед.             .75
	double natural_constitution_porosity_factor;
	bool natural_constitution_porosity_factor_defined;

	// влажность природная (доли ед.)                              .19
	double natural_moisture;
	bool natural_moisture_defined;

	// влажность водонасыщения (доли ед.)                          .26    
	double water_saturated_moisture;
	bool water_saturated_moisture_defined;

	// степень влажности                                           .69	
	double degree_of_moisture;
	bool degree_of_moisture_defined;
	// недостаток водонасыщения(доли ед.)                          .07
	double lack_of_water_saturating;
	bool lack_of_water_saturating_defined;
	// полная влагоемкость                                         .28
	double full_moisture_capacity;
	bool full_moisture_capacity_defined;


	// показатель текучести                                       -.08
	double fluidity_index;
	bool fluidity_index_defined;
	// показатель текучести водонасыщ.грунта                       .48
	double fluidity_index_of_water_saturated_ground;
	bool fluidity_index_of_water_saturated_ground_defined;

	// число пластичности                                          .13
	double plasticity_index;
	bool plasticity_index_defined;

	// влажность на границе текучести (доли ед.)                   .22
	double moisture_on_fluidity_border;
	bool moisture_on_fluidity_border_defined;
	
	// влажность на границе пластичности (доли ед.)                .17
	double moisture_on_plasticity_border;
	bool moisture_on_plasticity_border_defined;


/*
 ¦ модуль деформации по снип 2.02.01-83 в мпа                27.0          ¦
 ¦ угол внутреннего трения по снип 2.02.01-83,град           34.           ¦
 ¦ удельное сцепление по снип 2.02.01-83, мпа                  .006        ¦

 I модуль деформации грунта водон. состоян.в мпа              7.0          I
 I угол внутреннего трения в водонасыщ. сост., град.         24            I
 I удельное сцепление грунта в водонас. сост., мпа            0.017        I
 
 ¦ модуль деформации грунта заданн.состоян.в мпа              2.8          ¦
 ¦ угол внутреннего трения в заданном  сост.,град.           20.           ¦
 ¦ удельное сцепление грунта в заданном сост.,мпа              .028        ¦

 ¦ модуль деформации грунта природ.состоян.в мпа              3.5          ¦
 
 ¦ коэффициент мк к модулю деформ.заданн. состоян.            1.00         ¦
 ¦ степень изменчивости сжимаемости по модулю деф.            1.25         ¦
 ¦ коэффициент бокового расширения (вета)                      .48         ¦
 ¦ коэффициент мк к модулю деформ.природн.состоян.            1.00         ¦

*/

	StrengthDescription  strength_description;
	StrengthDescription  strength_description_on_snip;
	StrengthDescription  strength_description_water_saturated;
	StrengthDescription  strength_description_in_task_condition;
	StrengthDescription  strength_description_in_nature_condition;



	friend Archive& operator <<(Archive& ar, GroundDescription & gd);
	friend Archive& operator >>(Archive& ar, GroundDescription & gd);

	void SavingAsDat(FILE * stream);


};
// грунт
class CGround
{
	DWORD m_cground_version;
	friend class EngineerGeoElement;
protected:
	void Init();
public:
	// тип грунта
	enum ground_type
	{
		Undefined_ground			= 0,
		Sand						= 20,		//	Песок
        SandyLoam					= 40,		//	супесь
		Loam						= 60,		//	суглинок
		Clay						= 80		//	Глина
	};
	// Gender - род мужской male женский female middle
	// Quantity - число ед singular, множ plural

	enum Gender
	{
		male = 0,
		female,
		middle
	};

	enum Quantity
	{
		singular = 0, 
		plural
	};

	static Gender s_Gender;
	static Quantity s_Quantity;

	static const char * GrountTypeToString(CGround::ground_type t);
	static const char * GrountTypeToStringRus(CGround::ground_type t);
	// тип обводнения
	enum irrigation_type
	{
		undefined_irrigation_type	= 0,
		dry							= 20,	// сухие 
		little_moist				= 40,	// маловлажные 
		moist						= 60,	// влажный
		water_saturated				= 80	// насыщенные водой
	};
	static const char * IrrigationTypeToString(CGround::irrigation_type t);
	static const char * IrrigationTypeToStringRus(CGround::irrigation_type t);

protected:

	ground_type m_type;
	irrigation_type m_irrigation_type;

	bool read_normative_description;

	//нормативные значения характеристик 
	GroundDescription normative_description;
	//расчетные значения характеристик
	// при расчетах оснований:          
	// по деформациям:
	GroundDescription calculated_on_deformations_description;
	// по несущей способности   
	GroundDescription calculated_on_carry_ability_description;

	// прочностные характеристики

public:

	void * operator new  (size_t size){return ::operator new  (size);}
	void operator delete  (void * p)  {return ::operator delete  (p);}

	static void * operator new  (size_t size, CGround::ground_type);
	static void operator delete  (void * p, CGround::ground_type);

	const ground_type GetGroungType() const {return m_type;}
	const irrigation_type GetIrrigationType() const {return m_irrigation_type;}




	CGround(){Init();}
	virtual void PrintfProperties() = 0;
	virtual void FillListViewTab(ListViewTabGE & tab) = 0;
	int ParsingFileLine(char* szBuff, bool use_str_str, FILE * log, bool & again_with_StrStr);
	virtual int ReadingFile(FILE * stream,  char* szBuff, int n);
	virtual int ParseFileLine(char* szBuff, int type_line) = 0;

	void Ground_Serialize(Archive & ar);
	virtual DWORD Serialize(Archive & ar) = 0;

	friend Archive& operator <<(Archive& ar, CGround * g);
	friend Archive& operator >>(Archive& ar, CGround *& g);

	void SavingAsDat(FILE * stream);


};

inline CGround::ground_type operator++( CGround::ground_type &rs, int )
{
   return rs = (CGround::ground_type)(rs + 20);
}
inline CGround::irrigation_type operator++( CGround::irrigation_type &rs, int )
{
   return rs = (CGround::irrigation_type)(rs + 20);
}
// песчаный грунт
class CSandGround : public CGround
{
	DWORD m_sand_ground_version;
protected:
	void Init();
public:
	// тип песка по зернистости
	enum sand_type
	{
		undefined_sand_type			= 0,
		gravelic					= 10,   // Гравелистые
		coarse_grained				= 20,	// Крупные
		medium_grained				= 30,	// Средней крупности
		small_grained				= 40,	// Мелкие
		powdered					= 50	// Пылеватые

	};
	static const char * SandTypeToString(CSandGround::sand_type t);
	static const char * SandTypeToStringRus(CSandGround::sand_type t);
	// плотность песка 
	enum sand_strength 
	{
		undefined_sand_strength		= 0,
		dense						= 20,	// плотные
		medium_dense				= 40,	// средней плотности
		looses						= 60	// рыхлые
	};
	static const char * SandStrengthToString(CSandGround::sand_strength s);
	static const char * SandStrengthToStringRus(CSandGround::sand_strength s);
protected:
	sand_type m_sand_type;
	sand_strength m_sand_strength;
public:
	sand_type GetSandType(){return m_sand_type;}
	sand_strength GetSandStrength(){return m_sand_strength;}
	void SetSandType(sand_type t){m_sand_type = t;}
	void SetSandStrength(sand_strength s){m_sand_strength = s;}
	int ParseFileLine(char* szBuff, int type_line);
	CSandGround(){Init();}
	virtual void PrintfProperties();
	virtual void FillListViewTab(ListViewTabGE & tab);

	void SandGround_Serialize(Archive & ar);
};
inline CSandGround::sand_type operator++( CSandGround::sand_type &rs, int )
{
   return rs = (CSandGround::sand_type)(rs + 10);
}
inline CSandGround::sand_strength operator++( CSandGround::sand_strength &rs, int )
{
   return rs = (CSandGround::sand_strength)(rs + 20);
}
// пылевато-глинистый грунт
class CClayGround : public CGround
{
	DWORD m_clay_ground_version;
protected:
	void Init();
public:
	// твёрдость глин
	enum clay_solidity
	{
		undefined_clay_solidity		= 0,
		solid						= 20,	// твёрдые
		medium_solid				= 40,	// полутвёрдые
		tight_plastic				= 60,	// тугопластичные
		plastic						= 80,	// пластичные (только для супесей)
		soft_plastic				= 100,	// мягкопластичные
		fliud_plastic				= 120,	// текучепластичные
		fliud						= 140	// текучие
	};
	static const char * ClaySolidityToString(CClayGround::clay_solidity s);
	static const char * ClaySolidityToStringRus(CClayGround::clay_solidity s);
// что даёт лаборатория

/*
 ? влажность на границе текучести (доли ед.)                   .33         ? глинистые 
 ? влажность на границе пластичности (доли ед.)                .20         ?глинистые 
 */
protected:
	clay_solidity m_clay_solidity;
public:
	clay_solidity GetClaySolidity() {return m_clay_solidity;}
	void SetClaySolidity(clay_solidity cs) {m_clay_solidity = cs;}

	int ParseFileLine(char* szBuff, int type_line);
	CClayGround(){Init();}
	virtual void PrintfProperties();
	virtual void FillListViewTab(ListViewTabGE & tab);
	void ClayGround_Serialize(Archive & ar);
};
inline CClayGround::clay_solidity operator++( CClayGround::clay_solidity &rs, int )
{
   return rs = (CClayGround::clay_solidity)(rs + 20);
}
// песок
class CSand : public CSandGround
{
	DWORD m_sand_version;
	void Init();
public:
	CSand(){Init();}
	virtual DWORD Serialize(Archive & ar);
};
//	супесь
class CSandyLoam : public CClayGround
{
	DWORD m_sandyloam_version;
	void Init();
public:
	CSandyLoam(){Init();}
	virtual DWORD Serialize(Archive & ar);
};
//	суглинок
class CLoam : public CClayGround
{
	DWORD m_loam_version;
	void Init();
public:
	CLoam(){Init();}
	virtual DWORD Serialize(Archive & ar);
};
//	Глина
class CClay : public CClayGround
{
	DWORD m_clay_version;
	void Init();
public:
	CClay(){Init();}
	virtual DWORD Serialize(Archive & ar);
};

char * ParseSubStrings(char * szBuff, char * substr);
void DeleteCenterNullTerminator(char * szBuff, int n);