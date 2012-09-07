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
// ����������� �������������� ������
struct StrengthDescription
{
	DWORD m_strength_description_version;

	void Init();
	void PrintfProperties();
	bool Defined();

	// ������ ���������� ������
	double deformation_modulus;
	bool deformation_modulus_defined;

	// ���� ����������� ������
	double internal_friction_angle;
	bool internal_friction_angle_defined;

	// �������� ��������� ������
	double specific_cohesion;
	bool specific_cohesion_defined;

	friend Archive& operator <<(Archive& ar, StrengthDescription & sd);
	friend Archive& operator >>(Archive& ar, StrengthDescription & sd);

	void SavingAsDat(FILE * stream);


};
// �������������� ������
struct GroundDescription
{
	DWORD m_ground_description_version;
	void Init();
	void PrintfProperties();

/*
// ��� ��� �����������
// ====================
// ��������� ��������� (���� ��.)                              .19

// �������� ��� ������ ������,��/�3                          26.68
// �������� ��� ������,��/�3                                 18.15

// ��� �������������� �� ��������
// ==============================
// ����� ������������                                          .13         ?

// ��������� ������������� (���� ��.)                          .26         ?
// ���������� ���������                                       -.08         ?
// ���������� ��������� ���������.������                       .48         ?

// �������� ��� ������ ������,��/�3                          15.30         ?
// �������� ��� ��������������� ������,��/�3                 19.33         ?
// �������� ��� ����������� � ���� ������,��/�3               9.64         ?
// ���������� (���� ��.)                                       .43         ?
// ����������� ���������� ���������� ����.���� ��.             .75         ?

// ������� ���������                                           .69         ?

// ���������� �������������(���� ��.)                          .07         ?
// ������ ������������                                         .28         ?

// � �������
 I ������ ���������� ������ �����. �������.� ���              7.0          I
 I ���� ����������� ������ � ���������. ����., ����.         24            I
 I �������� ��������� ������ � �������. ����., ���            0.017        I
 */

	// �������� ��� ������ ������,��/�3                          26.68
	double specific_gravity_of_ground_particles;
	bool specific_gravity_of_ground_particles_defined;
	// �������� ��� ������,��/�3                                 18.15
	double specific_gravity_of_ground;
	bool specific_gravity_of_ground_defined;
	// �������� ��� ������ ������,��/�3                          15.30
	double specific_gravity_of_dry_ground;
	bool specific_gravity_of_dry_ground_defined;
	// �������� ��� ��������������� ������,��/�3                 19.33
	double specific_gravity_of_water_saturated_ground;
	bool specific_gravity_of_water_saturated_ground_defined;
	// �������� ��� ����������� � ���� ������,��/�3               9.64
	double specific_gravity_of_suspended_in_water_ground;
	bool specific_gravity_of_suspended_in_water_ground_defined;

	// ���������� (���� ��.)                                       .43
	double porosity;
	bool porosity_defined;
	// ����������� ���������� ���������� ����.���� ��.             .75
	double natural_constitution_porosity_factor;
	bool natural_constitution_porosity_factor_defined;

	// ��������� ��������� (���� ��.)                              .19
	double natural_moisture;
	bool natural_moisture_defined;

	// ��������� ������������� (���� ��.)                          .26    
	double water_saturated_moisture;
	bool water_saturated_moisture_defined;

	// ������� ���������                                           .69	
	double degree_of_moisture;
	bool degree_of_moisture_defined;
	// ���������� �������������(���� ��.)                          .07
	double lack_of_water_saturating;
	bool lack_of_water_saturating_defined;
	// ������ ������������                                         .28
	double full_moisture_capacity;
	bool full_moisture_capacity_defined;


	// ���������� ���������                                       -.08
	double fluidity_index;
	bool fluidity_index_defined;
	// ���������� ��������� ���������.������                       .48
	double fluidity_index_of_water_saturated_ground;
	bool fluidity_index_of_water_saturated_ground_defined;

	// ����� ������������                                          .13
	double plasticity_index;
	bool plasticity_index_defined;

	// ��������� �� ������� ��������� (���� ��.)                   .22
	double moisture_on_fluidity_border;
	bool moisture_on_fluidity_border_defined;
	
	// ��������� �� ������� ������������ (���� ��.)                .17
	double moisture_on_plasticity_border;
	bool moisture_on_plasticity_border_defined;


/*
 � ������ ���������� �� ���� 2.02.01-83 � ���                27.0          �
 � ���� ����������� ������ �� ���� 2.02.01-83,����           34.           �
 � �������� ��������� �� ���� 2.02.01-83, ���                  .006        �

 I ������ ���������� ������ �����. �������.� ���              7.0          I
 I ���� ����������� ������ � ���������. ����., ����.         24            I
 I �������� ��������� ������ � �������. ����., ���            0.017        I
 
 � ������ ���������� ������ ������.�������.� ���              2.8          �
 � ���� ����������� ������ � ��������  ����.,����.           20.           �
 � �������� ��������� ������ � �������� ����.,���              .028        �

 � ������ ���������� ������ ������.�������.� ���              3.5          �
 
 � ����������� �� � ������ ������.������. �������.            1.00         �
 � ������� ������������ ����������� �� ������ ���.            1.25         �
 � ����������� �������� ���������� (����)                      .48         �
 � ����������� �� � ������ ������.�������.�������.            1.00         �

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
// �����
class CGround
{
	DWORD m_cground_version;
	friend class EngineerGeoElement;
protected:
	void Init();
public:
	// ��� ������
	enum ground_type
	{
		Undefined_ground			= 0,
		Sand						= 20,		//	�����
        SandyLoam					= 40,		//	������
		Loam						= 60,		//	��������
		Clay						= 80		//	�����
	};
	// Gender - ��� ������� male ������� female middle
	// Quantity - ����� �� singular, ���� plural

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
	// ��� ����������
	enum irrigation_type
	{
		undefined_irrigation_type	= 0,
		dry							= 20,	// ����� 
		little_moist				= 40,	// ����������� 
		moist						= 60,	// �������
		water_saturated				= 80	// ���������� �����
	};
	static const char * IrrigationTypeToString(CGround::irrigation_type t);
	static const char * IrrigationTypeToStringRus(CGround::irrigation_type t);

protected:

	ground_type m_type;
	irrigation_type m_irrigation_type;

	bool read_normative_description;

	//����������� �������� ������������� 
	GroundDescription normative_description;
	//��������� �������� �������������
	// ��� �������� ���������:          
	// �� �����������:
	GroundDescription calculated_on_deformations_description;
	// �� ������� �����������   
	GroundDescription calculated_on_carry_ability_description;

	// ����������� ��������������

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
// �������� �����
class CSandGround : public CGround
{
	DWORD m_sand_ground_version;
protected:
	void Init();
public:
	// ��� ����� �� �����������
	enum sand_type
	{
		undefined_sand_type			= 0,
		gravelic					= 10,   // �����������
		coarse_grained				= 20,	// �������
		medium_grained				= 30,	// ������� ���������
		small_grained				= 40,	// ������
		powdered					= 50	// ���������

	};
	static const char * SandTypeToString(CSandGround::sand_type t);
	static const char * SandTypeToStringRus(CSandGround::sand_type t);
	// ��������� ����� 
	enum sand_strength 
	{
		undefined_sand_strength		= 0,
		dense						= 20,	// �������
		medium_dense				= 40,	// ������� ���������
		looses						= 60	// ������
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
// ��������-��������� �����
class CClayGround : public CGround
{
	DWORD m_clay_ground_version;
protected:
	void Init();
public:
	// �������� ����
	enum clay_solidity
	{
		undefined_clay_solidity		= 0,
		solid						= 20,	// ������
		medium_solid				= 40,	// ����������
		tight_plastic				= 60,	// ��������������
		plastic						= 80,	// ���������� (������ ��� �������)
		soft_plastic				= 100,	// ���������������
		fliud_plastic				= 120,	// ����������������
		fliud						= 140	// �������
	};
	static const char * ClaySolidityToString(CClayGround::clay_solidity s);
	static const char * ClaySolidityToStringRus(CClayGround::clay_solidity s);
// ��� ��� �����������

/*
 ? ��������� �� ������� ��������� (���� ��.)                   .33         ? ��������� 
 ? ��������� �� ������� ������������ (���� ��.)                .20         ?��������� 
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
// �����
class CSand : public CSandGround
{
	DWORD m_sand_version;
	void Init();
public:
	CSand(){Init();}
	virtual DWORD Serialize(Archive & ar);
};
//	������
class CSandyLoam : public CClayGround
{
	DWORD m_sandyloam_version;
	void Init();
public:
	CSandyLoam(){Init();}
	virtual DWORD Serialize(Archive & ar);
};
//	��������
class CLoam : public CClayGround
{
	DWORD m_loam_version;
	void Init();
public:
	CLoam(){Init();}
	virtual DWORD Serialize(Archive & ar);
};
//	�����
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