#include "stdafx.h"
#include "Ground.h"
#include "Object.h"
#include "Archive.h"
#include "GeoElement.h"

char strend[] = "iI��\0";

void DeleteCenterNullTerminator(char * szBuff, int n)
{
		
	char * pend = NULL;
	pend = strchr(szBuff, '\n');
	if(pend == NULL)
	{
		char * p0;
		while ( p0 = strchr(szBuff, '\0'))
		{
			if (p0 - szBuff > n-2)
				break;		

			*p0 = ' ';		

			if (p0 - szBuff > n-3)
				break;		

			pend = strchr(p0+1, '\n');
			if (pend)
			{
				break;
			}
		}		
	}
}

bool CompareWords(char * wb, char * ws, size_t m)
{
	size_t lenb = strlen(wb);
	size_t lens = strlen(ws);
	size_t len = min (m, lens);	
	// ����� ����������� ��������
	size_t ret = _strnicmp(wb, ws, len);
	if (ret == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}
bool UseStrStr = false;
char * StrStr(char * buff, char * subs)
{
	char * buff2 = _strdup( buff );
	char * subs2 = _strdup( subs );
	char *token_buff;
	char *token_subs;
	vector <char *> buff_words;
	vector <char *> subs_words;
	char delims[]   = " ,.-";
	//printf( "Tokens:\n" );
	/* Establish string and get the first token: */
	token_buff = strtok( buff2, delims );
	if (token_buff) buff_words.push_back(token_buff);
	while( token_buff != NULL )
	{
		/* While there are tokens in "string" */
		//printf( " %s\n", token_buff );
		/* Get next token: */
		token_buff = strtok( NULL, delims );
		if (token_buff) buff_words.push_back(token_buff);
	}
	
	/* Establish string and get the first token: */
	token_subs = strtok( subs2, delims );
	if (token_subs) subs_words.push_back(token_subs);
	while( token_subs != NULL )
	{
		/* While there are tokens in "string" */
		//printf( "\t\t%s\n", token_subs );
		/* Get next token: */
		token_subs = strtok( NULL, delims );
		if (token_subs) subs_words.push_back(token_subs);
	}
	size_t ib = 0, is = 0;


	bool found_first_word = false;
	size_t m = 3;

	size_t ib0_max = 2; // ���� �� ������ ������� ����� - ������ ����� - ������������ �����

	for (; ib < buff_words.size() && is < subs_words.size() && ib < ib0_max; ib++)
	{
		if (CompareWords(buff_words[ib], subs_words[is], m))
		{
			found_first_word = true;
			break;
		}
	}

	if(!found_first_word) return NULL;
	size_t ib0 = ib;

	for (; is < subs_words.size(); ib++, is++)
	{
		if (ib >= buff_words.size()) return NULL;
		if (!CompareWords(buff_words[ib], subs_words[is], m))
		{
			return NULL;
		}
	}
	if (buff_words.size() - ib0 >= subs_words.size())
	{
		char * p = strstr (buff, buff_words[subs_words.size()-1 + ib0]);
		if (p)
		{
			p = strpbrk(p, delims);
			if (p)
			{
				if (*p != ' ')
					p = strchr(p,' ');
				if(p)
				{ 
					printf("StrStr() p = %s\n", p);
					return p;
				}
			}
		}
	}
	return NULL;

}

char * ParseSubStrings(char * szBuff, char * substr)
{
			
	OemToChar(szBuff, szBuff);


	setlocale( LC_ALL, "Russian" );
	char * buff = _strlwr( _strdup( szBuff ) );
	char * m = strchr(buff,'m'); if (m) *m = '�';
	char * subs = _strlwr( _strdup( substr ) );
	m = strchr(subs,'m'); if (m) *m = '�';
	setlocale( LC_ALL, "English" );

	int ans = IDNO;

	//ans = MessageBox(0, buff, subs , MB_YESNOCANCEL);

	CharToOem(szBuff,szBuff);
	CharToOem(buff,buff);
	CharToOem(subs,subs);

	if (ans == IDYES)
	{
		printf("buff = %s\n", buff);
		printf("subs = %s\n", subs);
	}

	char * p = strstr(buff, subs);
	if (p)
	{
		char * pss = strrchr(subs, ' ');
		// ��� ��� �� ��������� ����������
		if (pss) 
		{
			p = p + strlen(subs);
			// ������� ������� ���������
			int inonspace0 = -1;
			for (int i = 0; i < int(strlen(p)); i++)
			{
				if (p[i] != ' ')
				{
					inonspace0 = i;
				}
				else
					break;
			}
			if (inonspace0 >= 0)
				p += inonspace0 + 1;
		}
		else
		{
			char * ps = strchr(p, ' ');
			if(ps) 
				p = ps;
			else
				p = p + strlen(subs);
		}
	}
	if(!p && UseStrStr)	p = StrStr(buff, subs);

	if (p)
	{
		// ������� ������� �������
		int ispace0 = -1;
		for (int i = 0; i < int(strlen(p)); i++)
		{
			if (p[i] == ' ')
			{
				ispace0 = i;
			}
			else
				break;
		}
		if (ispace0 >= 0)
			p += ispace0 + 1;

		// �������� ������ �� ������ ������������ �����
#if 1
		char * p0 = strrchr(p, 179);
		if(p0) 
			*p0 = '\0';
		else
		{
			p0 = strrchr(p, 'I');
			if(p0) 
				*p0 = '\0';
			else
			{
				p0 = strrchr(p, 'i');
				if(p0) 
					*p0 = '\0';
				else
				{
					p0 = strrchr(p, '�');
					if(p0) 
						*p0 = '\0';
					else
					{
						p0 = strrchr(p, '�');
						if(p0) 
							*p0 = '\0';
					}
				}
			}
		}
#else
		char * pend = strpbrk(p0+1, strend);
		if (pend) *pend = '\0';
#endif

		// ������� ���������� �������
		for (int i = int(strlen(p)) - 1 ; i >= 0; i--)
		{
			if (p[i] == ' ')
			{
				p[i] = '\0';
			}
			else
				break;
		}		
	}
	if(!p) 
	{
		free(buff);
		if (ans == IDYES)
			printf("p = NULL\n");
	}
	else
	{
		//if (ans == IDYES)
			printf("p = %s\n", p);
		OemToChar(p,p);
	}

	free(subs);
	return p;
}


#if 0
char * ParseSubStrings_special(char * szBuff, char * substr)
{
			
	OemToChar(szBuff, szBuff);


	setlocale( LC_ALL, "Russian" );
	_strlwr( szBuff );
	char * m = strchr(szBuff,'m'); if (m) *m = '�';
	char * subs = _strlwr( substr );
	m = strchr(subs,'m'); if (m) *m = '�';
	setlocale( LC_ALL, "English" );

	int ans = IDNO;

	//ans = MessageBox(0, buff, subs , MB_YESNOCANCEL);

	CharToOem(szBuff,szBuff);
	CharToOem(subs,subs);

	if (ans == IDYES)
	{
		printf("szBuff = %s\n", szBuff);
		printf("subs = %s\n", subs);
	}

	char * p = strstr(szBuff, subs);

	if (p)
	{
		char * p0;
		while ( p0 = strchr(szBuff, '\0'))
		{
			*p0 = ' ';			
			char * pend = strpbrk(p0+1, strend);
			if (pend)
			{
				*pend = '\0';
				break;
			}
		}
		p = p + strlen(subs) + 1 + 2;
		// ������� ������� �������
		int ispace0 = -1;
		for (int i = 0; i < int(strlen(p)); i++)
		{
			if (p[i] == ' ')
			{
				ispace0 = i;
			}
			else
				break;
		}
		if (ispace0 >= 0)
			p += ispace0 + 1;
	}
	if(!p) 
	{
		if (ans == IDYES)
			printf("p = NULL\n");
	}
	else
	{
		OemToChar(p,p);
		if (ans == IDYES)
			printf("p = %s\n", p);
	}

	return p;
}



#endif

void * CGround::operator new  (size_t size, CGround::ground_type t)
{
	//printf("Object::operator new(size_t size = %d, GeoElement::type = %s\n", size, GeoElement::GeoElementTypeToString(t));
/*	// ��� ������
	enum ground_type
	{
					= 0,
		Sand						= 20,		//	�����
        SandyLoam					= 40,		//	������
		Loam						= 60,		//	��������
		Clay						= 80		//	�����
	};*/
	switch (t)
	{
	case CGround::ground_type::Undefined_ground:
		return NULL;
	case CGround::ground_type::Sand:
		return reinterpret_cast<void*>(new CSand);
	case CGround::ground_type::SandyLoam:
		return reinterpret_cast<void*>(new CSandyLoam);
	case CGround::ground_type::Loam:
		return reinterpret_cast<void*>(new CLoam);
	case CGround::ground_type::Clay:
		return reinterpret_cast<void*>(new CClay);
	default:
		return NULL;
	}
	return NULL;
}
void CGround::operator delete(void * p, CGround::ground_type t)
{
	switch (t)
	{
	case CGround::ground_type::Undefined_ground:
		return;
	case CGround::ground_type::Sand:
		::operator delete(reinterpret_cast<CSand*>(p));
		break;
	case CGround::ground_type::SandyLoam:
		::operator delete(reinterpret_cast<CSandyLoam*>(p));
		break;
	case CGround::ground_type::Loam:
		::operator delete(reinterpret_cast<CLoam*>(p));
		break;
	case CGround::ground_type::Clay:
		::operator delete(reinterpret_cast<CClay*>(p));
		break;
	default:
		return;
	}
}

CGround::Gender CGround::s_Gender = CGround::Gender::male;
CGround::Quantity CGround::s_Quantity = CGround::Quantity::singular;




const char * CGround::GrountTypeToString(CGround::ground_type t)
{
	switch (t)
	{
	case Undefined_ground:
		return "Undefined_ground";
	case Sand:		//	�����
		return "Sand";
	case SandyLoam:	//	������
		return "SandyLoam";
	case Loam:		//	��������
		return "Loam";
	case Clay:		//	�����
		return "Clay";
	default:
		return "";
	}
	return "";
}
const char * CGround::GrountTypeToStringRus(CGround::ground_type t)
{
	switch(CGround::s_Quantity)
	{
	case CGround::Quantity::singular:
		{
			switch (t)
			{
			case Undefined_ground:
				return "";
			case Sand:		//	�����
				return "�����";
			case SandyLoam:	//	������
				return "������";
			case Loam:		//	��������
				return "��������";
			case Clay:		//	�����
				return "�����";
			default:
				return "";
			}
		}
		break;
	case CGround::Quantity::plural:
		{
			switch (t)
			{
			case Undefined_ground:
				return "";
			case Sand:		//	�����
				return "�����";
			case SandyLoam:	//	������
				return "������";
			case Loam:		//	��������
				return "��������";
			case Clay:		//	�����
				return "�����";
			default:
				return "";
			}
		}
		break;
	}
	return "";
}

const char * CSandGround::SandTypeToString(CSandGround::sand_type t)
{
	switch (t)
	{
	case undefined_sand_type:
		return "undefined_sand_type";
	case gravelic:					// �����������
		return "gravelic";
	case coarse_grained:			// �������
		return "coarse_grained";
	case medium_grained:			// ������� ���������
		return "medium_grained";
	case small_grained:				// ������
		return "small_grained";
	case powdered:					// ���������
		return "powdered";
	default:
		return "";
	}
	return "";
}
const char * CSandGround::SandTypeToStringRus(CSandGround::sand_type t)
{
	switch (t)
	{
	case undefined_sand_type:
		return "undefined_sand_type";
	case gravelic:					// �����������
		return "�����������";
	case coarse_grained:			// �������
		return "�������";
	case medium_grained:			// ������� ���������
		return "������� ���������";
	case small_grained:				// ������
		return "������";
	case powdered:					// ���������
		return "���������";
	default:
		return "";
	}
	return "";
}
const char * CSandGround::SandStrengthToString(CSandGround::sand_strength s)
{
	switch (s)
	{
	case sand_strength::undefined_sand_strength:
		return "undefined_sand_strength";
	case sand_strength::dense:			// �������
		return "dense";
	case sand_strength::medium_dense:	// ������� ���������
		return "medium_dense";
	case sand_strength::looses:			// ������
		return "looses";
	default:
		return "";
	}
	return "";
}
const char * CSandGround::SandStrengthToStringRus(CSandGround::sand_strength s)
{
	switch (s)
	{
	case sand_strength::undefined_sand_strength:
		return "undefined_sand_strength";
	case sand_strength::dense:			// �������
		return "�������";
	case sand_strength::medium_dense:	// ������� ���������
		return "������� ���������";
	case sand_strength::looses:			// ������
		return "������";
	default:
		return "";
	}
	return "";
}
const char * CClayGround::ClaySolidityToString(CClayGround::clay_solidity s)
{
	switch (s)
	{
	case clay_solidity::undefined_clay_solidity:
		return "undefined_clay_solidity";
	case clay_solidity::solid:			// ������
		return "solid";
	case clay_solidity::medium_solid:	// ����������
		return "medium_solid";
	case clay_solidity::tight_plastic:		// ��������������
		return "tight_plastic";
	case clay_solidity::plastic:		// ���������� (������ ��� �������)
		return "plastic (only for sandyloam)";
	case clay_solidity::soft_plastic:		// ���������������
		return "soft_plastic";
	case clay_solidity::fliud_plastic:		// ����������������
		return "fliud_plastic";
	case clay_solidity::fliud:			// �������
		return "fliud";
	default:
		return "";
	}
	return "";
}
const char * CClayGround::ClaySolidityToStringRus(CClayGround::clay_solidity s)
{
	switch (s)
	{
	case clay_solidity::undefined_clay_solidity:
		return "undefined_clay_solidity";
	case clay_solidity::solid:			// ������
		return "������";
	case clay_solidity::medium_solid:	// ����������
		return "����������";
	case clay_solidity::tight_plastic:		// ��������������
		return "��������������";
	case clay_solidity::plastic:		// ���������� (������ ��� �������)
		return "���������� (������ ��� �������)";
	case clay_solidity::soft_plastic:		// ���������������
		return "���������������";
	case clay_solidity::fliud_plastic:		// ����������������
		return "����������������";
	case clay_solidity::fliud:			// �������
		return "�������";

	default:
		return "";
	}
	return "";
}
const char * CGround::IrrigationTypeToString(CGround::irrigation_type t)
{

	switch (t)
	{
	case undefined_irrigation_type:
		return "undefined_irrigation_type";
	case dry:// �����
		return "dry";	
	case little_moist:// �����������
		return "little_moist";
	case moist:// �������
		return "moist";
	case water_saturated:// ���������� �����
		return "water_saturated";
	default:
		return "";
	}
	return "";
}
const char * CGround::IrrigationTypeToStringRus(CGround::irrigation_type t)
{

	switch (t)
	{
	case undefined_irrigation_type:
		return "undefined_irrigation_type";
	case dry:// �����
		return "�����";
	case little_moist:// �����������
		return "�����������";
	case moist:// �������
		return "�������";
	case water_saturated:// ���������� �����
		return "���������� �����";
	default:
		return "";
	}
	return "";
}
void StrengthDescription::Init()
{
	// ������ ���������� ������
	deformation_modulus;
	deformation_modulus_defined								= false;

	// ���� ����������� ������
	internal_friction_angle;
	internal_friction_angle_defined							= false;

	// �������� ��������� ������
	specific_cohesion;
	specific_cohesion_defined								= false;

	m_strength_description_version = 1;
}
bool StrengthDescription::Defined()
{
	return (
		deformation_modulus_defined
		||
		internal_friction_angle_defined
		||
        specific_cohesion_defined
		);
}
void GroundDescription::Init()
{
	// �������� ��� ������ ������,��/�3                          26.68
	specific_gravity_of_ground_particles;
	specific_gravity_of_ground_particles_defined			= false;
	// �������� ��� ������,��/�3                                 18.15
	specific_gravity_of_ground;
	specific_gravity_of_ground_defined						= false;
	// �������� ��� ������ ������,��/�3                          15.30
	specific_gravity_of_dry_ground;
	specific_gravity_of_dry_ground_defined					= false;
	// �������� ��� ��������������� ������,��/�3                 19.33
	specific_gravity_of_water_saturated_ground;
	specific_gravity_of_water_saturated_ground_defined		= false;
	// �������� ��� ����������� � ���� ������,��/�3               9.64
	specific_gravity_of_suspended_in_water_ground;
	specific_gravity_of_suspended_in_water_ground_defined	= false;

	// ���������� (���� ��.)                                       .43
	porosity;
	porosity_defined										= false;
	// ����������� ���������� ���������� ����.���� ��.             .75
	natural_constitution_porosity_factor;
	natural_constitution_porosity_factor_defined			= false;

	// ��������� ��������� (���� ��.)                              .19
	natural_moisture;
	natural_moisture_defined								= false;
	// ��������� ������������� (���� ��.)                          .26    
	water_saturated_moisture;
	water_saturated_moisture_defined						= false;


	// ������� ���������                                           .69	
	degree_of_moisture;
	degree_of_moisture_defined								= false;
	// ���������� �������������(���� ��.)                          .07
	lack_of_water_saturating;
	lack_of_water_saturating_defined						= false;
	// ������ ������������                                         .28
	full_moisture_capacity;
	full_moisture_capacity_defined							= false;


	// ���������� ���������                                       -.08
	fluidity_index;
	fluidity_index_defined									= false;
	// ���������� ��������� ���������.������                       .48
	fluidity_index_of_water_saturated_ground;
	fluidity_index_of_water_saturated_ground_defined		= false;

	// ����� ������������                                          .13
	plasticity_index;
	plasticity_index_defined								= false;

	// ��������� �� ������� ��������� (���� ��.)                   .22
	moisture_on_fluidity_border;
	moisture_on_fluidity_border_defined						= false;
	
	// ��������� �� ������� ������������ (���� ��.)                .17
	moisture_on_plasticity_border;
	moisture_on_plasticity_border_defined					= false;


	this->strength_description.Init();
	this->strength_description_on_snip.Init();
	this->strength_description_water_saturated.Init();
	this->strength_description_in_task_condition.Init();
	this->strength_description_in_nature_condition.Init();



	m_ground_description_version = 1;
}
void CGround::Init()
{
	this->m_type = CGround::ground_type::Undefined_ground;
	this->m_irrigation_type = CGround::irrigation_type::undefined_irrigation_type;
	read_normative_description = true;

	this->normative_description.Init();	
	this->calculated_on_deformations_description.Init();	
	this->calculated_on_carry_ability_description.Init();

	m_cground_version = 1;

}
void CSandGround::Init()
{
	this->CGround::Init();
	this->m_sand_type = CSandGround::sand_type::undefined_sand_type;
	this->m_sand_strength = CSandGround::sand_strength::undefined_sand_strength;
	m_sand_ground_version = 1;
}
void CClayGround::Init()
{
	this->CGround::Init();
	this->m_clay_solidity = CClayGround::clay_solidity::undefined_clay_solidity;
	m_clay_ground_version = 1;
}
void CSand::Init()
{
	this->CSandGround::Init();
	this->m_type = CGround::ground_type::Sand;
	m_sand_version = 1;
}
void CSandyLoam::Init()
{
	this->CClayGround::Init();
	this->m_type = CGround::ground_type::SandyLoam;
	m_sandyloam_version = 1;
}
void CLoam::Init()
{
	this->CClayGround::Init();
	this->m_type = CGround::ground_type::Loam;
	m_loam_version = 1;
}
void CClay::Init()
{
	this->CClayGround::Init();
	this->m_type = CGround::ground_type::Clay;
	m_clay_version = 1;
}
void StrengthDescription::PrintfProperties()
{
	// ������ ���������� ������
	if (deformation_modulus_defined)
		printf("deformation_modulus = %f\n", deformation_modulus);

	// ���� ����������� ������
	if (internal_friction_angle_defined)
		printf("internal_friction_angle = %f\n", internal_friction_angle);

	// �������� ��������� ������
	if (specific_cohesion_defined)
		printf("specific_cohesion = %f\n", specific_cohesion);
}
void GroundDescription::PrintfProperties()
{
	// �������� ��� ������ ������,��/�3                          26.68
	if (specific_gravity_of_ground_particles_defined)
		printf("specific_gravity_of_ground_particles = %f\n", specific_gravity_of_ground_particles);
	// �������� ��� ������,��/�3                                 18.15
	if (specific_gravity_of_ground_defined)
		printf("specific_gravity_of_ground = %f\n", specific_gravity_of_ground);
	// �������� ��� ������ ������,��/�3                          15.30
	if (specific_gravity_of_dry_ground_defined)
		printf("specific_gravity_of_dry_ground = %f\n", specific_gravity_of_dry_ground);
	// �������� ��� ��������������� ������,��/�3                 19.33
	if (specific_gravity_of_water_saturated_ground_defined)
		printf("specific_gravity_of_water_saturated_ground = %f\n", specific_gravity_of_water_saturated_ground);
	// �������� ��� ����������� � ���� ������,��/�3               9.64
	if (specific_gravity_of_suspended_in_water_ground_defined)
		printf("specific_gravity_of_suspended_in_water_ground = %f\n", specific_gravity_of_suspended_in_water_ground);
	
	// ���������� (���� ��.)                                       .43
	if (porosity_defined)
		printf("porosity = %f\n", porosity);
	// ����������� ���������� ���������� ����.���� ��.             .75
	if (natural_constitution_porosity_factor_defined)
		printf("natural_constitution_porosity_factor = %f\n", natural_constitution_porosity_factor);
	
	// ��������� ��������� (���� ��.)                              .19
	if (natural_moisture_defined)
		printf("natural_moisture = %f\n", natural_moisture);
	// ��������� ������������� (���� ��.)                          .26    
	if (water_saturated_moisture_defined)
		printf("water_saturated_moisture = %f\n", water_saturated_moisture);
	// ������� ���������                                           .69	
	if (degree_of_moisture_defined)
		printf("degree_of_moisture = %f\n", degree_of_moisture);
	// ���������� �������������(���� ��.)                          .07
	if (lack_of_water_saturating_defined)
		printf("lack_of_water_saturating = %f\n", lack_of_water_saturating);
	// ������ ������������                                         .28
	if (full_moisture_capacity_defined)
		printf("full_moisture_capacity = %f\n", full_moisture_capacity);


	// ���������� ���������                                       -.08
	if (fluidity_index_defined)
		printf("fluidity_index = %f\n", fluidity_index);
	// ���������� ��������� ���������.������                       .48
	if (fluidity_index_of_water_saturated_ground_defined)
		printf("fluidity_index_of_water_saturated_ground = %f\n", fluidity_index_of_water_saturated_ground);

	// ����� ������������                                          .13
	if (plasticity_index_defined)
		printf("plasticity_index = %f\n", plasticity_index);

	// ��������� �� ������� ��������� (���� ��.)                   .22
	if (moisture_on_fluidity_border_defined)
		printf("moisture_on_fluidity_border = %f\n", moisture_on_fluidity_border);
	
	// ��������� �� ������� ������������ (���� ��.)                .17
	if (moisture_on_plasticity_border_defined)
		printf("moisture_on_plasticity_border = %f\n", moisture_on_plasticity_border);

	if (this->strength_description.Defined())
	{
		printf("strength_description:\n");
		this->strength_description.PrintfProperties();
	}	
	
	if (this->strength_description_on_snip.Defined())
	{
		printf("strength_description_on_snip:\n");
		this->strength_description_on_snip.PrintfProperties();
	}

	if (this->strength_description_water_saturated.Defined())
	{
		printf("strength_description_water_saturated:\n");
		this->strength_description_water_saturated.PrintfProperties();
	}

	if (this->strength_description_in_task_condition.Defined())
	{
		printf("strength_description_in_task_condition:\n");
		this->strength_description_in_task_condition.PrintfProperties();
	}

	if (this->strength_description_in_nature_condition.Defined())
	{
		printf("strength_description_in_nature_condition:\n");
		this->strength_description_in_nature_condition.PrintfProperties();
	}
}
void CGround::PrintfProperties()
{
	printf("ground type = \"%s\"\n", CGround::GrountTypeToString(this->m_type));
	printf("Irrigation type  = \"%s\"\n", CGround::IrrigationTypeToString(this->m_irrigation_type));

	printf("normative_description:\n");
	this->normative_description.PrintfProperties();
	
	printf("calculated_on_deformations_description:\n");
	this->calculated_on_deformations_description.PrintfProperties();
	
	printf("calculated_on_carry_ability_description:\n");
	this->calculated_on_carry_ability_description.PrintfProperties();

}
void CSandGround::PrintfProperties()
{
	printf("sand type  = \"%s\"\n", CSandGround::SandTypeToString(this->m_sand_type));
	printf("sand strength  = \"%s\"\n", CSandGround::SandStrengthToString(this->m_sand_strength));
	this->CGround::PrintfProperties();
}
void CClayGround::PrintfProperties()
{
	printf("clay solidity  = \"%s\"\n", CClayGround::ClaySolidityToString(this->m_clay_solidity));
	this->CGround::PrintfProperties();
}
void CGround::FillListViewTab(ListViewTabGE & tab)
{
	char str[1024];	 
		
	LPARAM lPar = CreateLParam(EngineerGeoElement::ValueType::ground_type, EngineerGeoElement::GroundDescriptionType::normative,EngineerGeoElement::StrengthDescriptionType::simple);
	tab.AddRow(lPar, NULL);
	size_t r = tab.Rows()-1;

	sprintf(str, "��� ������");
	tab.SetItemString(r,1,str);
	sprintf(str, "\"%s\"", CGround::GrountTypeToStringRus(this->m_type));
	tab.SetItemString(r,2,str);


	LPARAM lPar2 = CreateLParam(EngineerGeoElement::ValueType::irrigation_type, EngineerGeoElement::GroundDescriptionType::normative,EngineerGeoElement::StrengthDescriptionType::simple);
	tab.AddRow(lPar2, NULL);
	r = tab.Rows()-1;

	sprintf(str, "��� ����������");
	tab.SetItemString(r,1,str);
	sprintf(str, "\"%s\"", CGround::IrrigationTypeToStringRus(this->m_irrigation_type));
	tab.SetItemString(r,2,str);
}

void CSandGround::FillListViewTab(ListViewTabGE & tab)
{
	this->CGround::FillListViewTab(tab);

	char str[1024];	 
		
	LPARAM lPar = CreateLParam(EngineerGeoElement::ValueType::sand_type, EngineerGeoElement::GroundDescriptionType::normative,EngineerGeoElement::StrengthDescriptionType::simple);
	tab.AddRow(lPar, NULL);
	size_t r = tab.Rows()-1;

	sprintf(str, "��� ����� �� �����������");
	tab.SetItemString(r,1,str);
	sprintf(str, "\"%s\"", CSandGround::SandTypeToStringRus(this->m_sand_type));
	tab.SetItemString(r,2,str);

	LPARAM lPar2 = CreateLParam(EngineerGeoElement::ValueType::sand_strength, EngineerGeoElement::GroundDescriptionType::normative,EngineerGeoElement::StrengthDescriptionType::simple);
	tab.AddRow(lPar2, NULL);
	r = tab.Rows()-1;

	sprintf(str, "��������� �����");
	tab.SetItemString(r,1,str);
	sprintf(str, "\"%s\"", CSandGround::SandStrengthToStringRus(this->m_sand_strength));
	tab.SetItemString(r,2,str);


}

void CClayGround::FillListViewTab(ListViewTabGE & tab)
{
	this->CGround::FillListViewTab(tab);

	char str[1024];	 
		
	LPARAM lPar = CreateLParam(EngineerGeoElement::ValueType::clay_solidity, EngineerGeoElement::GroundDescriptionType::normative,EngineerGeoElement::StrengthDescriptionType::simple);
	tab.AddRow(lPar, NULL);
	size_t r = tab.Rows()-1;

	sprintf(str, "�������� ���������� ������");
	tab.SetItemString(r,1,str);
	sprintf(str, "\"%s\"", CClayGround::ClaySolidityToStringRus(this->m_clay_solidity));
	tab.SetItemString(r,2,str);

}

int CGround::ParseFileLine(char* szBuff, int type_line)
{
	//printf("ParseEGEFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);

	switch(type_line)
	{
		// ������������
	case 1:
		{
			char substr[] = " �����\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_irrigation_type = CGround::irrigation_type::dry;
				printf("this->m_irrigation_type = CGround::irrigation_type::dry;\n");
				return 0;
			}
		}
		break;
	case 2:
		{
			char substr[] = " �����������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_irrigation_type = CGround::irrigation_type::little_moist;
				printf("this->m_irrigation_type = CGround::irrigation_type::dry;\n");
				return 0;
			}
		}
		break;
	case 3:
		{
			char substr[] = " �������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_irrigation_type = CGround::irrigation_type::moist;
				printf("this->m_irrigation_type = CGround::irrigation_type::moist;\n");
				return 0;
			}
		}
		break;
	case 4:
		{
			char substr[] = " ���������� �����\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				this->m_irrigation_type = CGround::irrigation_type::water_saturated;
				printf("this->m_irrigation_type = CGround::irrigation_type::water_saturated;\n");
				return 0;
			}
		}
		break;
		// ����������� �������� �������������
	case 5:
		{
			char substr[] = "����������� �������� �������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				read_normative_description = true;
				return 0;
			}
		}
		break;
		// ��������� �������� �������������
	case 6:
		{
			char substr[] = "��������� �������� �������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{			
				read_normative_description = false;
				return 0;
			}
		}
		break;
		// �������� ���
	case 7:
		{
			char substr[] = "�������� ��� ������ ������,��/�3\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "�������� ��� ������ ������, ��/�3\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ������ ������,��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ������ ������, ��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.specific_gravity_of_ground_particles = atof(p);
					this->normative_description.specific_gravity_of_ground_particles_defined = true;
					printf("normative_description.specific_gravity_of_ground_particles = %f\n", this->normative_description.specific_gravity_of_ground_particles);
				}
				else
				{
					this->calculated_on_deformations_description.specific_gravity_of_ground_particles = atof(p);
					this->calculated_on_deformations_description.specific_gravity_of_ground_particles_defined = true;
					printf("calculated_on_deformations_description.specific_gravity_of_ground_particles = %f\n", this->calculated_on_deformations_description.specific_gravity_of_ground_particles);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.specific_gravity_of_ground_particles = atof(p);
						this->calculated_on_carry_ability_description.specific_gravity_of_ground_particles_defined = true;
						printf("calculated_on_carry_ability_description.specific_gravity_of_ground_particles = %f\n", this->calculated_on_carry_ability_description.specific_gravity_of_ground_particles);
					}
				}
				return 0;
			}
		}
		break;	
	case 8:
		{
			char substr[] = "�������� ��� ������,��/�3\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "�������� ��� ������, ��/�3\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ������,��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ������, ��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.specific_gravity_of_ground = atof(p);
					this->normative_description.specific_gravity_of_ground_defined = true;
					printf("normative_description.specific_gravity_of_ground = %f\n", this->normative_description.specific_gravity_of_ground);
				}
				else
				{
					this->calculated_on_deformations_description.specific_gravity_of_ground = atof(p);
					this->calculated_on_deformations_description.specific_gravity_of_ground_defined = true;
					printf("calculated_on_deformations_description.specific_gravity_of_ground = %f\n", calculated_on_deformations_description.specific_gravity_of_ground);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.specific_gravity_of_ground = atof(p);
						this->calculated_on_carry_ability_description.specific_gravity_of_ground_defined = true;
						printf("calculated_on_carry_ability_description.specific_gravity_of_ground = %f\n", this->calculated_on_carry_ability_description.specific_gravity_of_ground);
					}
				}
				return 0;
			}
		}
		break;
	case 9:
		{
			char substr[] = "�������� ��� ������ ������,��/�3\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "�������� ��� ������ ������, ��/�3\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ������ ������,��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ������ ������, ��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.specific_gravity_of_dry_ground = atof(p);
					this->normative_description.specific_gravity_of_dry_ground_defined = true;
					printf("normative_description.specific_gravity_of_dry_ground = %f\n", this->normative_description.specific_gravity_of_dry_ground);
				}
				else
				{
					this->calculated_on_deformations_description.specific_gravity_of_dry_ground = atof(p);
					this->calculated_on_deformations_description.specific_gravity_of_dry_ground_defined = true;
					printf("calculated_on_deformations_description.specific_gravity_of_dry_ground = %f\n", this->calculated_on_deformations_description.specific_gravity_of_dry_ground);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.specific_gravity_of_dry_ground = atof(p);
						this->calculated_on_carry_ability_description.specific_gravity_of_dry_ground_defined = true;
						printf("calculated_on_carry_ability_description.specific_gravity_of_dry_ground = %f\n", this->calculated_on_carry_ability_description.specific_gravity_of_dry_ground);
					}
				}
				return 0;
			}
		}
		break;
	case 10:
		{
			char substr[] = "�������� ��� ��������������� ������,��/�3\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "�������� ��� ��������������� ������, ��/�3\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ��������������� ������, ��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ��������������� ������,��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.specific_gravity_of_water_saturated_ground = atof(p);
					this->normative_description.specific_gravity_of_water_saturated_ground_defined = true;
					printf("normative_description.specific_gravity_of_water_saturated_ground = %f\n", this->normative_description.specific_gravity_of_water_saturated_ground);
				}
				else
				{
					this->calculated_on_deformations_description.specific_gravity_of_water_saturated_ground = atof(p);
					this->calculated_on_deformations_description.specific_gravity_of_water_saturated_ground_defined = true;
					printf("calculated_on_deformations_description.specific_gravity_of_water_saturated_ground = %f\n", this->calculated_on_deformations_description.specific_gravity_of_water_saturated_ground);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.specific_gravity_of_water_saturated_ground = atof(p);
						this->calculated_on_carry_ability_description.specific_gravity_of_water_saturated_ground_defined = true;
						printf("calculated_on_carry_ability_description.specific_gravity_of_water_saturated_ground = %f\n", this->calculated_on_carry_ability_description.specific_gravity_of_water_saturated_ground);
					}
				}
				return 0;
			}
		}
		break;
	case 11:
		{
			char substr[] = "�������� ��� ����������� � ���� ������,��/�3\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "�������� ��� ����������� � ���� ������, ��/�3\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ����������� � ���� ������, ��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (!p)
			{
				char substr[] = "�������� ��� ����������� � ���� ������,��/�  3\0";
				size_t len = strlen(substr);
				//substr[len-3] = 0;
				substr[len-2] = 4;
				p = ParseSubStrings/*_special*/(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.specific_gravity_of_suspended_in_water_ground = atof(p);
					this->normative_description.specific_gravity_of_suspended_in_water_ground_defined = true;
					printf("normative_description.specific_gravity_of_suspended_in_water_ground = %f\n", this->normative_description.specific_gravity_of_suspended_in_water_ground);
				}
				else
				{
					this->calculated_on_deformations_description.specific_gravity_of_suspended_in_water_ground = atof(p);
					this->calculated_on_deformations_description.specific_gravity_of_suspended_in_water_ground_defined = true;
					printf("calculated_on_deformations_description.specific_gravity_of_suspended_in_water_ground = %f\n", this->calculated_on_deformations_description.specific_gravity_of_suspended_in_water_ground);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.specific_gravity_of_suspended_in_water_ground = atof(p);
						this->calculated_on_carry_ability_description.specific_gravity_of_suspended_in_water_ground_defined = true;
						printf("calculated_on_carry_ability_description.specific_gravity_of_suspended_in_water_ground = %f\n", this->calculated_on_carry_ability_description.specific_gravity_of_suspended_in_water_ground);
					}
				}
				return 0;
			}
		}
		break;
		// ����������
	case 12:
		{
			char substr[] = "���������� (���� ��.)\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.porosity = atof(p);
					this->normative_description.porosity_defined = true;
					printf("normative_description.porosity = %f\n", this->normative_description.porosity);
				}
				else
				{
					this->calculated_on_deformations_description.porosity = atof(p);
					this->calculated_on_deformations_description.porosity_defined = true;
					printf("calculated_on_deformations_description.porosity = %f\n", this->calculated_on_deformations_description.porosity);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.porosity = atof(p);
						this->calculated_on_carry_ability_description.porosity_defined = true;
						printf("calculated_on_carry_ability_description.porosity = %f\n", this->calculated_on_carry_ability_description.porosity);
					}
				}
				return 0;
			}
		}
		break;
	case 13:
		{
			char substr[] = "����������� ���������� ���������� ����.���� ��.\0";
			char * p = ParseSubStrings(szBuff, substr);
			if(!p)
			{
				char substr[] = "����������� ���������� ���������� ����. (���� ��.)\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.natural_constitution_porosity_factor = atof(p);
					this->normative_description.natural_constitution_porosity_factor_defined = true;
					printf("normative_description.natural_constitution_porosity_factor = %f\n", this->normative_description.natural_constitution_porosity_factor);
				}
				else
				{
					this->calculated_on_deformations_description.natural_constitution_porosity_factor = atof(p);
					this->calculated_on_deformations_description.natural_constitution_porosity_factor_defined = true;
					printf("calculated_on_deformations_description.natural_constitution_porosity_factor = %f\n", this->calculated_on_deformations_description.natural_constitution_porosity_factor);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.natural_constitution_porosity_factor = atof(p);
						this->calculated_on_carry_ability_description.natural_constitution_porosity_factor_defined = true;
						printf("calculated_on_carry_ability_description.natural_constitution_porosity_factor = %f\n", this->calculated_on_carry_ability_description.natural_constitution_porosity_factor);
					}
				}
				return 0;
			}
		}
		break;
		// ���������
	case 14:
		{
			char substr[] = "��������� ��������� (���� ��.)\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.natural_moisture = atof(p);
					this->normative_description.natural_moisture_defined = true;
					printf("normative_description.natural_moisture = %f\n", this->normative_description.natural_moisture);
				}
				else
				{
					this->calculated_on_deformations_description.natural_moisture = atof(p);
					this->calculated_on_deformations_description.natural_moisture_defined = true;
					printf("calculated_on_deformations_description.natural_moisture = %f\n", this->calculated_on_deformations_description.natural_moisture);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.natural_moisture = atof(p);
						this->calculated_on_carry_ability_description.natural_moisture_defined = true;
						printf("calculated_on_carry_ability_description.natural_moisture = %f\n", this->calculated_on_carry_ability_description.natural_moisture);
					}
				}
				return 0;
			}
		}
		break;
	case 15:
		{
			char substr[] = "��������� ������������� (���� ��.)\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.water_saturated_moisture = atof(p);
					this->normative_description.water_saturated_moisture_defined = true;
					printf("normative_description.water_saturated_moisture = %f\n", this->normative_description.water_saturated_moisture);
				}
				else
				{
					this->calculated_on_deformations_description.water_saturated_moisture = atof(p);
					this->calculated_on_deformations_description.water_saturated_moisture_defined = true;
					printf("calculated_on_deformations_description.water_saturated_moisture = %f\n", this->calculated_on_deformations_description.water_saturated_moisture);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.water_saturated_moisture = atof(p);
						this->calculated_on_carry_ability_description.water_saturated_moisture_defined = true;
						printf("calculated_on_carry_ability_description.water_saturated_moisture = %f\n", this->calculated_on_carry_ability_description.water_saturated_moisture);
					}
				}
				return 0;
			}
		}
		break;
	case 16:
		{
			char substr[] = " ������� ���������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.degree_of_moisture = atof(p);
					this->normative_description.degree_of_moisture_defined = true;
					printf("normative_description.degree_of_moisture = %f\n", this->normative_description.degree_of_moisture);
				}
				else
				{
					this->calculated_on_deformations_description.degree_of_moisture = atof(p);
					this->calculated_on_deformations_description.degree_of_moisture_defined = true;
					printf("calculated_on_deformations_description.degree_of_moisture = %f\n", this->calculated_on_deformations_description.degree_of_moisture);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.degree_of_moisture = atof(p);
						this->calculated_on_carry_ability_description.degree_of_moisture_defined = true;
						printf("calculated_on_carry_ability_description.degree_of_moisture = %f\n", this->calculated_on_carry_ability_description.degree_of_moisture);
					}
				}
				return 0;
			}
		}
		break;
	case 17:
		{
			char substr[] = "���������� �������������(���� ��.)\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.lack_of_water_saturating = atof(p);
					this->normative_description.lack_of_water_saturating_defined = true;
					printf("normative_description.lack_of_water_saturating = %f\n", this->normative_description.lack_of_water_saturating);
				}
				else
				{
					this->calculated_on_deformations_description.lack_of_water_saturating = atof(p);
					this->calculated_on_deformations_description.lack_of_water_saturating_defined = true;
					printf("calculated_on_deformations_description.lack_of_water_saturating = %f\n", this->calculated_on_deformations_description.lack_of_water_saturating);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.lack_of_water_saturating = atof(p);
						this->calculated_on_carry_ability_description.lack_of_water_saturating_defined = true;
						printf("calculated_on_carry_ability_description.lack_of_water_saturating = %f\n", this->calculated_on_carry_ability_description.lack_of_water_saturating);
					}
				}
				return 0;
			}
		}
		break;	
	case 18:
		{
			char substr[] = "������ ������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.full_moisture_capacity = atof(p);
					this->normative_description.full_moisture_capacity_defined = true;
					printf("normative_description.full_moisture_capacity = %f\n", this->normative_description.full_moisture_capacity);
				}
				else
				{
					this->calculated_on_deformations_description.full_moisture_capacity = atof(p);
					this->calculated_on_deformations_description.full_moisture_capacity_defined = true;
					printf("calculated_on_deformations_description.full_moisture_capacity = %f\n", this->calculated_on_deformations_description.full_moisture_capacity);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.full_moisture_capacity = atof(p);
						this->calculated_on_carry_ability_description.full_moisture_capacity_defined = true;
						printf("calculated_on_carry_ability_description.full_moisture_capacity = %f\n", this->calculated_on_carry_ability_description.full_moisture_capacity);
					}
				}
				return 0;
			}
		}
		break;
		// ���������
	case 19:
		{
			char substr[] = "���������� ���������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.fluidity_index = atof(p);
					this->normative_description.fluidity_index_defined = true;
					printf("normative_description.fluidity_index = %f\n", this->normative_description.fluidity_index);
				}
				else
				{
					this->calculated_on_deformations_description.fluidity_index = atof(p);
					this->calculated_on_deformations_description.fluidity_index_defined = true;
					printf("calculated_on_deformations_description.fluidity_index = %f\n", this->calculated_on_deformations_description.fluidity_index);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.fluidity_index = atof(p);
						this->calculated_on_carry_ability_description.fluidity_index_defined = true;
						printf("calculated_on_carry_ability_description.fluidity_index = %f\n", this->calculated_on_carry_ability_description.fluidity_index);
					}
				}
				return 0;
			}
		}
		break;
	case 20:
		{
			char substr[] = "���������� ��������� ���������.������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.fluidity_index_of_water_saturated_ground = atof(p);
					this->normative_description.fluidity_index_of_water_saturated_ground_defined = true;
					printf("normative_description.fluidity_index_of_water_saturated_ground = %f\n", this->normative_description.fluidity_index_of_water_saturated_ground);
				}
				else
				{
					this->calculated_on_deformations_description.fluidity_index_of_water_saturated_ground = atof(p);
					this->calculated_on_deformations_description.fluidity_index_of_water_saturated_ground_defined = true;
					printf("calculated_on_deformations_description.fluidity_index_of_water_saturated_ground = %f\n", this->calculated_on_deformations_description.fluidity_index_of_water_saturated_ground);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.fluidity_index_of_water_saturated_ground = atof(p);
						this->calculated_on_carry_ability_description.fluidity_index_of_water_saturated_ground_defined = true;
						printf("calculated_on_carry_ability_description.fluidity_index_of_water_saturated_ground = %f\n", this->calculated_on_carry_ability_description.fluidity_index_of_water_saturated_ground);
					}
				}
				return 0;
			}
		}
		break;
	case 21:
		{
			char substr[] = "����� ������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.plasticity_index = atof(p);
					this->normative_description.plasticity_index_defined = true;
					printf("normative_description.plasticity_index = %f\n", this->normative_description.plasticity_index);
				}
				else
				{
					this->calculated_on_deformations_description.plasticity_index = atof(p);
					this->calculated_on_deformations_description.plasticity_index_defined = true;
					printf("calculated_on_deformations_description.plasticity_index = %f\n", this->calculated_on_deformations_description.plasticity_index);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.plasticity_index = atof(p);
						this->calculated_on_carry_ability_description.plasticity_index_defined = true;
						printf("calculated_on_carry_ability_description.plasticity_index = %f\n", this->calculated_on_carry_ability_description.plasticity_index);
					}
				}
				return 0;
			}
		}
		break;
	case 22:
		{
			char substr[] = "��������� �� ������� ��������� (���� ��.)\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.moisture_on_fluidity_border = atof(p);
					this->normative_description.moisture_on_fluidity_border_defined = true;
					printf("normative_description.moisture_on_fluidity_border = %f\n", this->normative_description.moisture_on_fluidity_border);
				}
				else
				{
					this->calculated_on_deformations_description.moisture_on_fluidity_border = atof(p);
					this->calculated_on_deformations_description.moisture_on_fluidity_border_defined = true;
					printf("calculated_on_deformations_description.moisture_on_fluidity_border = %f\n", this->calculated_on_deformations_description.moisture_on_fluidity_border);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.moisture_on_fluidity_border = atof(p);
						this->calculated_on_carry_ability_description.moisture_on_fluidity_border_defined = true;
						printf("calculated_on_carry_ability_description.moisture_on_fluidity_border = %f\n", this->calculated_on_carry_ability_description.moisture_on_fluidity_border);
					}
				}
				return 0;
			}
		}
		break;
	case 23:
		{
			char substr[] = "��������� �� ������� ������������ (���� ��.)\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.moisture_on_plasticity_border = atof(p);
					this->normative_description.moisture_on_plasticity_border_defined = true;
					printf("normative_description.moisture_on_plasticity_border = %f\n", this->normative_description.moisture_on_plasticity_border);
				}
				else
				{
					this->calculated_on_deformations_description.moisture_on_plasticity_border = atof(p);
					this->calculated_on_deformations_description.moisture_on_plasticity_border_defined = true;
					printf("calculated_on_deformations_description.moisture_on_plasticity_border = %f\n", this->calculated_on_deformations_description.moisture_on_plasticity_border);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.moisture_on_plasticity_border = atof(p);
						this->calculated_on_carry_ability_description.moisture_on_plasticity_border_defined = true;
						printf("calculated_on_carry_ability_description.moisture_on_plasticity_border = %f\n", this->calculated_on_carry_ability_description.moisture_on_plasticity_border);
					}
				}
				return 0;
			}
		}
		break;
	case 24:
		{
			char substr[] = "������ ���������� � ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "������ ����������, � ���\0";
				p = ParseSubStrings(szBuff, substr);
			}			
			if (!p)
			{
				char substr[] = "������ ����������  � ���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			
			if (!p)
			{
				char substr[] = "���� ����������� ������, ����.\0";
				p = ParseSubStrings(szBuff, substr);
			}

			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description.deformation_modulus = atof(p);
					this->normative_description.strength_description.deformation_modulus_defined = true;
					printf("normative_description.strength_description.deformation_modulus = %f\n", this->normative_description.strength_description.deformation_modulus);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description.deformation_modulus = atof(p);
					this->calculated_on_deformations_description.strength_description.deformation_modulus_defined = true;
					printf("calculated_on_deformations_description.strength_description.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description.deformation_modulus);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description.deformation_modulus = atof(p);
						this->calculated_on_carry_ability_description.strength_description.deformation_modulus_defined = true;
						printf("calculated_on_carry_ability_description.strength_description.deformation_modulus = %f\n", this->calculated_on_carry_ability_description.strength_description.deformation_modulus);
					}
				}
				return 0;
			}
		}
		break;
	case 25:
		{
			char substr[] = "���� ����������� ������,����\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description.internal_friction_angle = atof(p);
					this->normative_description.strength_description.internal_friction_angle_defined = true;
					printf("normative_description.strength_description.internal_friction_angle = %f\n", this->normative_description.strength_description.internal_friction_angle);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description.internal_friction_angle = atof(p);
					this->calculated_on_deformations_description.strength_description.internal_friction_angle_defined = true;
					printf("calculated_on_deformations_description.strength_description.internal_friction_angle = %f\n", this->calculated_on_deformations_description.strength_description.internal_friction_angle);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description.internal_friction_angle = atof(p);
						this->calculated_on_carry_ability_description.strength_description.internal_friction_angle_defined = true;
						printf("calculated_on_carry_ability_description.strength_description.internal_friction_angle = %f\n", this->calculated_on_carry_ability_description.strength_description.internal_friction_angle);
					}
				}
				return 0;
			}
		}
		break;		
	case 26:
		{
			char substr[] = "�������� ���������, ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description.specific_cohesion = atof(p);
					this->normative_description.strength_description.specific_cohesion_defined = true;
					printf("normative_description.strength_description.specific_cohesion = %f\n", this->normative_description.strength_description.specific_cohesion);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description.specific_cohesion = atof(p);
					this->calculated_on_deformations_description.strength_description.specific_cohesion_defined = true;
					printf("calculated_on_deformations_description.strength_description.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description.specific_cohesion);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description.specific_cohesion = atof(p);
						this->calculated_on_carry_ability_description.strength_description.specific_cohesion_defined = true;
						printf("calculated_on_carry_ability_description.strength_description.specific_cohesion = %f\n", this->calculated_on_carry_ability_description.strength_description.specific_cohesion);
					}
				}
				return 0;
			}
		}
		break;
	case 27:
		{
			char substr[] = "������ ���������� �� ���� 2.02.01-83 � ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_on_snip.deformation_modulus = atof(p);
					this->normative_description.strength_description_on_snip.deformation_modulus_defined = true;
					printf("normative_description.strength_description_on_snip.deformation_modulus = %f\n", this->normative_description.strength_description_on_snip.deformation_modulus);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_on_snip.deformation_modulus = atof(p);
					this->calculated_on_deformations_description.strength_description_on_snip.deformation_modulus_defined = true;
					printf("calculated_on_deformations_description.strength_description_on_snip.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_on_snip.deformation_modulus);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_on_snip.deformation_modulus = atof(p);
						this->calculated_on_carry_ability_description.strength_description_on_snip.deformation_modulus_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_on_snip.deformation_modulus = %f\n", this->calculated_on_carry_ability_description.strength_description_on_snip.deformation_modulus);
					}
				}
				return 0;
			}
		}
		break;
	case 28:
		{
			char substr[] = "���� ����������� ������ �� ���� 2.02.01-83,����\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_on_snip.internal_friction_angle = atof(p);
					this->normative_description.strength_description_on_snip.internal_friction_angle_defined = true;
					printf("normative_description.strength_description_on_snip.internal_friction_angle = %f\n", this->normative_description.strength_description_on_snip.internal_friction_angle);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_on_snip.internal_friction_angle = atof(p);
					this->calculated_on_deformations_description.strength_description_on_snip.internal_friction_angle_defined = true;
					printf("calculated_on_deformations_description.strength_description_on_snip.internal_friction_angle = %f\n", this->calculated_on_deformations_description.strength_description_on_snip.internal_friction_angle);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_on_snip.internal_friction_angle = atof(p);
						this->calculated_on_carry_ability_description.strength_description_on_snip.internal_friction_angle_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_on_snip.internal_friction_angle = %f\n", this->calculated_on_carry_ability_description.strength_description_on_snip.internal_friction_angle);
					}
				}
				return 0;
			}
		}
		break;		
	case 29:
		{
			char substr[] = "�������� ��������� �� ���� 2.02.01-83, ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_on_snip.specific_cohesion = atof(p);
					this->normative_description.strength_description_on_snip.specific_cohesion_defined = true;
					printf("normative_description.strength_description_on_snip.specific_cohesion = %f\n", this->normative_description.strength_description_on_snip.specific_cohesion);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_on_snip.specific_cohesion = atof(p);
					this->calculated_on_deformations_description.strength_description_on_snip.specific_cohesion_defined = true;
					printf("calculated_on_deformations_description.strength_description_on_snip.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_on_snip.specific_cohesion);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_on_snip.specific_cohesion = atof(p);
						this->calculated_on_carry_ability_description.strength_description_on_snip.specific_cohesion_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_on_snip.specific_cohesion = %f\n", this->calculated_on_carry_ability_description.strength_description_on_snip.specific_cohesion);
					}
				}
				return 0;
			}
		}
		break;
	case 30:
		{
			char substr[] = "������ ���������� ������ �����. �������.� ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if(!p)
			{
				char substr[] = "������ ���������� ������ �������.����., � ���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{			
				char substr[] = "������ ���������� ������ �������.�������.� ���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{			
				char substr[] = "������ ���������� �������. ��������� � ���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_water_saturated.deformation_modulus = atof(p);
					this->normative_description.strength_description_water_saturated.deformation_modulus_defined = true;
					printf("normative_description.strength_description_water_saturated.deformation_modulus = %f\n", this->normative_description.strength_description_water_saturated.deformation_modulus);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_water_saturated.deformation_modulus = atof(p);
					this->calculated_on_deformations_description.strength_description_water_saturated.deformation_modulus_defined = true;
					printf("calculated_on_deformations_description.strength_description_water_saturated.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_water_saturated.deformation_modulus);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_water_saturated.deformation_modulus = atof(p);
						this->calculated_on_carry_ability_description.strength_description_water_saturated.deformation_modulus_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_water_saturated.deformation_modulus = %f\n", this->calculated_on_carry_ability_description.strength_description_water_saturated.deformation_modulus);
					}
				}
				return 0;
			}
		}
		break;
	case 31:
		{
			char substr[] = "���� ����������� ������ � ���������. ����., ����.\0";
			char * p = ParseSubStrings(szBuff, substr);
			if(!p)
			{
				char substr[] = "���� ����������� ������ � ������. ����.,����.\0";
				p = ParseSubStrings(szBuff, substr);
			}			
			if(!p)
			{
				char substr[] = "���� ����������� ������ � ������.  ����.,����\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				char substr[] = "���� ����������� ������ � �������.����.,����.\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				char substr[] = "���� ����������� ������ � �������.����.,����\0";
				p = ParseSubStrings(szBuff, substr);
			}				
			if(!p)
			{
				char substr[] = "���� ����������� ������ � �������.����.,  ����.\0";
				p = ParseSubStrings(szBuff, substr);
			}			
			if(!p)
			{
				char substr[] = "���� ����������� ������ � �������.����.,  ����\0";
				p = ParseSubStrings(szBuff, substr);
			}	
			if(!p)
			{
				char substr[] = "���� ����������� ������ � �������.����., ����.\0";
				p = ParseSubStrings(szBuff, substr);
			}			
			if(!p)
			{
				char substr[] = "���� ����������� ������ � �������.����., ����\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_water_saturated.internal_friction_angle = atof(p);
					this->normative_description.strength_description_water_saturated.internal_friction_angle_defined = true;
					printf("normative_description.strength_description_water_saturated.internal_friction_angle = %f\n", this->normative_description.strength_description_water_saturated.internal_friction_angle);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_water_saturated.internal_friction_angle = atof(p);
					this->calculated_on_deformations_description.strength_description_water_saturated.internal_friction_angle_defined = true;
					printf("calculated_on_deformations_description.strength_description_water_saturated.internal_friction_angle = %f\n", this->calculated_on_deformations_description.strength_description_water_saturated.internal_friction_angle);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_water_saturated.internal_friction_angle = atof(p);
						this->calculated_on_carry_ability_description.strength_description_water_saturated.internal_friction_angle_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_water_saturated.internal_friction_angle = %f\n", this->calculated_on_carry_ability_description.strength_description_water_saturated.internal_friction_angle);
					}
				}
				return 0;
			}
		}
		break;		
	case 32:
		{
			char substr[] = "�������� ��������� ������ � �������. ����., ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if(!p)
			{
				char substr[] = "�������� ��������� ������ � �����. ����., ���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				char substr[] = "�������� ���������  ������ � ������. ����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				char substr[] = "�������� ��������� ������ � ������. ����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				char substr[] = "�������� ���������  ������ � �������.����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}			
			if(!p)
			{
				char substr[] = "�������� ��������� ������ � �������.����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				
				char substr[] = "�������� ��������� ������ � �������.����., ���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_water_saturated.specific_cohesion = atof(p);
					this->normative_description.strength_description_water_saturated.specific_cohesion_defined = true;
					printf("normative_description.strength_description_water_saturated.specific_cohesion = %f\n", this->normative_description.strength_description_water_saturated.specific_cohesion);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_water_saturated.specific_cohesion = atof(p);
					this->calculated_on_deformations_description.strength_description_water_saturated.specific_cohesion_defined = true;
					printf("calculated_on_deformations_description.strength_description_water_saturated.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_water_saturated.specific_cohesion);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_water_saturated.specific_cohesion = atof(p);
						this->calculated_on_carry_ability_description.strength_description_water_saturated.specific_cohesion_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_water_saturated.specific_cohesion = %f\n", this->calculated_on_carry_ability_description.strength_description_water_saturated.specific_cohesion);
					}
				}
				return 0;
			}
		}
		break;
	case 33:
		{
			char substr[] = "������ ���������� ������ ������.�������.� ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_in_task_condition.deformation_modulus = atof(p);
					this->normative_description.strength_description_in_task_condition.deformation_modulus_defined = true;
					printf("normative_description.strength_description_in_task_condition.deformation_modulus = %f\n", this->normative_description.strength_description_in_task_condition.deformation_modulus);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_in_task_condition.deformation_modulus = atof(p);
					this->calculated_on_deformations_description.strength_description_in_task_condition.deformation_modulus_defined = true;
					printf("calculated_on_deformations_description.strength_description_in_task_condition.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_in_task_condition.deformation_modulus);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_in_task_condition.deformation_modulus = atof(p);
						this->calculated_on_carry_ability_description.strength_description_in_task_condition.deformation_modulus_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_in_task_condition.deformation_modulus = %f\n", this->calculated_on_carry_ability_description.strength_description_in_task_condition.deformation_modulus);
					}
				}
				return 0;
			}
		}
		break;
	case 34:
		{
			char substr[] = "���� ����������� ������ � ��������  ����.,����.\0";
			char * p = ParseSubStrings(szBuff, substr);
			if(!p)
			{
				char substr[] = "���� ����������� ������ � ��������  ����.,����\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_in_task_condition.internal_friction_angle = atof(p);
					this->normative_description.strength_description_in_task_condition.internal_friction_angle_defined = true;
					printf("normative_description.strength_description_in_task_condition.internal_friction_angle = %f\n", this->normative_description.strength_description_in_task_condition.internal_friction_angle);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_in_task_condition.internal_friction_angle = atof(p);
					this->calculated_on_deformations_description.strength_description_in_task_condition.internal_friction_angle_defined = true;
					printf("calculated_on_deformations_description.strength_description_in_task_condition.internal_friction_angle = %f\n", this->calculated_on_deformations_description.strength_description_in_task_condition.internal_friction_angle);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_in_task_condition.internal_friction_angle = atof(p);
						this->calculated_on_carry_ability_description.strength_description_in_task_condition.internal_friction_angle_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_in_task_condition.internal_friction_angle = %f\n", this->calculated_on_carry_ability_description.strength_description_in_task_condition.internal_friction_angle);
					}
				}
				return 0;
			}
		}
		break;		
	case 35:
		{
			char substr[] = "�������� ��������� ������ � �������� ����.,���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{
				char substr[] = "�������� ��������� ������ � ������. ����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_in_task_condition.specific_cohesion = atof(p);
					this->normative_description.strength_description_in_task_condition.specific_cohesion_defined = true;
					printf("normative_description.strength_description_in_task_condition.specific_cohesion = %f\n", this->normative_description.strength_description_in_task_condition.specific_cohesion);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_in_task_condition.specific_cohesion = atof(p);
					this->calculated_on_deformations_description.strength_description_in_task_condition.specific_cohesion_defined = true;
					printf("calculated_on_deformations_description.strength_description_in_task_condition.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_in_task_condition.specific_cohesion);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_in_task_condition.specific_cohesion = atof(p);
						this->calculated_on_carry_ability_description.strength_description_in_task_condition.specific_cohesion_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_in_task_condition.specific_cohesion = %f\n", this->calculated_on_carry_ability_description.strength_description_in_task_condition.specific_cohesion);
					}
				}
				return 0;
			}
		}
		break;
	case 36:
		{
			char substr[] = "������ ���������� ������ ������.�������.� ���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_in_nature_condition.deformation_modulus = atof(p);
					this->normative_description.strength_description_in_nature_condition.deformation_modulus_defined = true;
					printf("normative_description.strength_description_in_nature_condition.deformation_modulus = %f\n", this->normative_description.strength_description_in_nature_condition.deformation_modulus);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_in_nature_condition.deformation_modulus = atof(p);
					this->calculated_on_deformations_description.strength_description_in_nature_condition.deformation_modulus_defined = true;
					printf("calculated_on_deformations_description.strength_description_in_nature_condition.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_in_nature_condition.deformation_modulus);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_in_nature_condition.deformation_modulus = atof(p);
						this->calculated_on_carry_ability_description.strength_description_in_nature_condition.deformation_modulus_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_in_nature_condition.deformation_modulus = %f\n", this->calculated_on_carry_ability_description.strength_description_in_nature_condition.deformation_modulus);
					}
				}
				return 0;
			}
		}
		break;
	case 37:
		{
			char substr[] = "���� ����������� ������ � ������. ����.,����.\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{				
				char substr[] = "���� ����������� ������ � ������.����., ����.\0";
				p = ParseSubStrings(szBuff, substr);
			}
			
			if (!p)
			{				
				char substr[] = "���� ����������� ������ � ������.����., ����\0";
				p = ParseSubStrings(szBuff, substr);
			}

			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_in_nature_condition.internal_friction_angle = atof(p);
					this->normative_description.strength_description_in_nature_condition.internal_friction_angle_defined = true;
					printf("normative_description.strength_description_in_nature_condition.internal_friction_angle = %f\n", this->normative_description.strength_description_in_nature_condition.internal_friction_angle);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_in_nature_condition.internal_friction_angle = atof(p);
					this->calculated_on_deformations_description.strength_description_in_nature_condition.internal_friction_angle_defined = true;
					printf("calculated_on_deformations_description.strength_description_in_nature_condition.internal_friction_angle = %f\n", this->calculated_on_deformations_description.strength_description_in_nature_condition.internal_friction_angle);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_in_nature_condition.internal_friction_angle = atof(p);
						this->calculated_on_carry_ability_description.strength_description_in_nature_condition.internal_friction_angle_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_in_nature_condition.internal_friction_angle = %f\n", this->calculated_on_carry_ability_description.strength_description_in_nature_condition.internal_friction_angle);
					}
				}
				return 0;
			}
		}
		break;		
	case 38:
		{
			char substr[] = "�������� ��������� ������ � ������. ����.,���\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (!p)
			{				
				char substr[] = "�������� ���������  ������ � �������.����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if(!p)
			{
				
				char substr[] = "�������� ��������� ������ � �������.����.,���\0";
				p = ParseSubStrings(szBuff, substr);
			}
			if (p && ISNUM(p) )
			{		
				cout << p << endl;
				if (read_normative_description)
				{
					this->normative_description.strength_description_in_nature_condition.specific_cohesion = atof(p);
					this->normative_description.strength_description_in_nature_condition.specific_cohesion_defined = true;
					printf("normative_description.strength_description_in_nature_condition.specific_cohesion = %f\n", this->normative_description.strength_description_in_nature_condition.specific_cohesion);
				}
				else
				{
					this->calculated_on_deformations_description.strength_description_in_nature_condition.specific_cohesion = atof(p);
					this->calculated_on_deformations_description.strength_description_in_nature_condition.specific_cohesion_defined = true;
					printf("calculated_on_deformations_description.strength_description_in_nature_condition.deformation_modulus = %f\n", this->calculated_on_deformations_description.strength_description_in_nature_condition.specific_cohesion);
					p = strchr(p, ' ');
					if(p)
					{
						this->calculated_on_carry_ability_description.strength_description_in_nature_condition.specific_cohesion = atof(p);
						this->calculated_on_carry_ability_description.strength_description_in_nature_condition.specific_cohesion_defined = true;
						printf("calculated_on_carry_ability_description.strength_description_in_nature_condition.specific_cohesion = %f\n", this->calculated_on_carry_ability_description.strength_description_in_task_condition.specific_cohesion);
					}
				}
				return 0;
			}
		}
		break;
	case 39:
		{
			char substr[] = "���������-������������� �������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{		
				cout << szBuff;
				cout << p << endl;
				return 2;
			}
		}
		break;	
	default :
		return 1;
	}

	return -1;
}




int CSandGround::ParseFileLine(char* szBuff, int type_line)
{
	//printf("ParseEGEFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);

	switch(type_line)
	{
	case 1:
		{
			char substr[] = " �����������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_type = CSandGround::sand_type::gravelic;
				printf("this->m_sand_type = CSandGround::sand_type::coarse_grained;\n");
				return 0;
			}
		}
		break;
	case 2:
		{
			char substr[] = " �������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_type = CSandGround::sand_type::coarse_grained;
				printf("this->m_sand_type = CSandGround::sand_type::coarse_grained;\n");
				return 0;
			}
		}
		break;
	case 3:
		{
			char substr[] = " ������� ���������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_type = CSandGround::sand_type::medium_grained;
				printf("this->m_sand_type = CSandGround::sand_type::medium_grained;\n");
				return 0;
			}
		}
		break;
	case 4:
		{
			char substr[] = " ������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_type = CSandGround::sand_type::small_grained;
				printf("this->m_sand_type = CSandGround::sand_type::small_grained;\n");
				return 0;
			}
		}
		break;
	case 5:
		{
			char substr[] = " ���������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_type = CSandGround::sand_type::powdered;
				printf("this->m_sand_type = CSandGround::sand_type::powdered;\n");
				return 0;
			}
		}
		break;
		// ��������� ������
	case 6:
		{
			char substr[] = " �������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_strength = CSandGround::sand_strength::dense;
				printf("this->m_sand_strength = CSandGround::sand_strength::dense;\n");
				return 0;
			}
		}
		break;
	case 7:
		{
			char substr[] = " ������� ���������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_strength = CSandGround::sand_strength::medium_dense;
				printf("this->m_sand_strength = CSandGround::sand_strength::medium_dense;\n");
				return 0;
			}
		}
		break;
	case 8:
		{
			char substr[] = " ������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_sand_strength = CSandGround::sand_strength::looses;
				printf("this->m_sand_strength = CSandGround::sand_strength::looses;\n");
				return 0;
			}
		}
		break;

	default :
		return 1;
	}

	return -1;
}

int CClayGround::ParseFileLine(char* szBuff, int type_line)
{
	//printf("ParseEGEFileLine(szBuff = \"%s\", type_line = %d)\)\n", szBuff, type_line);

	switch(type_line)
	{
		// �������� ����
	case 1:
		{
			char substr[] = " �������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::solid;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::solid;\n");
				return 0;
			}
		}
		break;
	case 2:
		{
			char substr[] = " �����������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::medium_solid;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::medium_solid;\n");
				return 0;
			}
		}
		break;
	case 3:
		{
			char substr[] = " ��������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			char substr2[] = "� �������������� ���������\0";
			char * p2 = ParseSubStrings(szBuff, substr2);
			if (p && !p2)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::tight_plastic;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::tight_plastic;\n");
				return 0;
			}
		}
		break;	
	case 4:
		{
			char substr[] = " ����������\0";
			char * p = ParseSubStrings(szBuff, substr);
			char substr2[] = "� �������������� ���������\0";
			char * p2 = ParseSubStrings(szBuff, substr2);
			if (p && !p2)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::plastic;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::plastic;\n");
				return 0;
			}
		}
		break;	
	case 5:
		{
			char substr[] = " ���������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			char substr2[] = "� �������������� ���������\0";
			char * p2 = ParseSubStrings(szBuff, substr2);
			if (p && !p2)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::soft_plastic;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::soft_plastic;\n");
				return 0;
			}
		}
		break;	
	case 6:
		{
			char substr[] = " ����������������\0";
			char * p = ParseSubStrings(szBuff, substr);
			char substr2[] = "� �������������� ���������\0";
			char * p2 = ParseSubStrings(szBuff, substr2);
			if (p && !p2)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::fliud_plastic;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::fliud_plastic;\n");
				return 0;
			}
		}
		break;		
	case 7:
		{
			char substr[] = " �������\0";
			char * p = ParseSubStrings(szBuff, substr);
			if (p)
			{				
				CharToOem(p,p);
				cout << p << endl;
				this->m_clay_solidity = CClayGround::clay_solidity::fliud;
				printf("this->m_clay_solidity = CClayGround::clay_solidity::fliud;\n");
				return 0;
			}
		}
		break;

	default :
		return 1;
	}

	return -1;
}

int CGround::ParsingFileLine(char* szBuff, bool use_str_str, FILE * log, bool & again_with_StrStr)
{
	bool to_base_parse_line = true;
	bool to_parse_line = false;
	again_with_StrStr = false;

	UseStrStr = use_str_str;		
	// ������� ��������� ������ �������� �������� ������
	for (int type_line = 1; to_base_parse_line; type_line++) 
	{            
		int base_res = this->CGround::ParseFileLine(szBuff, type_line);
		if (base_res == -1)
		{
			// ��������� ������ ������
		}
		else if (base_res == 0)
		{
			// ������� ������ ������
			to_base_parse_line = false;
			to_parse_line = false;
			cout << szBuff << endl;
		}
		else if (base_res == 1)
		{
			//��������� ��� ��������� ��������
			to_base_parse_line = false;
			to_parse_line = true;
		}					
		else if (base_res == 2)
		{
			// �����
			// ���������-������������� �������
			to_base_parse_line = false;
			to_parse_line = false;
			return 2;
		}			

	}
	// ����� ���� ���� ��������� ��� �� ������ �������� ������������ ������
	for (int type_line = 1; to_parse_line; type_line++) 
	{            
		int base_res = this->ParseFileLine(szBuff, type_line);
		if (base_res == -1)
		{
			// ��������� ������ ������
		}
		else if (base_res == 0)
		{
			// ������� ������ ������
			to_parse_line = false;
			cout << szBuff << endl;
		}
		else if (base_res == 1)
		{
			//��������� ��� ��������� ��������
			to_parse_line = false;
			again_with_StrStr = true;
#if LOG_UNPARSED
			if (log) fprintf(log,szBuff);
#endif
		}			

	}
	return 1;
}
int CGround::ReadingFile(FILE * stream,  char* szBuff, int n)
{
	char * ch;
#if LOG_UNPARSED
	FILE * log = fopen("unparsed.log","at");
#endif
	while (!feof(stream))
	{
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			DeleteCenterNullTerminator(szBuff, n);

			bool again_with_StrStr;
			int res = ParsingFileLine(szBuff, false, NULL, again_with_StrStr);
			if (again_with_StrStr)
			{
				res = ParsingFileLine(szBuff, true, log, again_with_StrStr);
			}
			UseStrStr = false;

			if (res == 2)
				return 2;
		}
		else 
		{
			//break;
		}
	}
#if LOG_UNPARSED
	if (log) fclose(log);
#endif
	return 1;
}
Archive& operator <<(Archive& ar, StrengthDescription & sd)
{
	ar << sd.m_strength_description_version;
	switch (sd.m_strength_description_version)
	{
	case 1:
		{
			// ������ ���������� ������
			ar << sd.deformation_modulus_defined;
			if(sd.deformation_modulus_defined)
				ar << sd.deformation_modulus;

			// ���� ����������� ������
			ar << sd.internal_friction_angle_defined;
			if(sd.internal_friction_angle_defined)
				ar << sd.internal_friction_angle;

			// �������� ��������� ������
			ar << sd.specific_cohesion_defined;
			if (sd.specific_cohesion_defined)
				ar << sd.specific_cohesion;
		}
		break;
	default:
		{
			throw VersionException(sd.m_strength_description_version, VersionException::cannot_store, Object::object_type::undefined);
		}
		break;
	}
	return ar;
}

void StrengthDescription::SavingAsDat(FILE * stream)
{
	char delim = '\t';
			// ������ ���������� ������
			//ar >> sd.deformation_modulus_defined;
			if(this->deformation_modulus_defined)
				fprintf(stream, "%s%c %f\n", "������ ���������� ������", delim, this->deformation_modulus);

			// ���� ����������� ������
			//ar >> this->internal_friction_angle_defined;
			if(this->internal_friction_angle_defined)
				fprintf(stream, "%s%c %f\n", "���� ����������� ������", delim, this->internal_friction_angle);

			// �������� ��������� ������
			//ar >> this->specific_cohesion_defined;
			if (this->specific_cohesion_defined)
				fprintf(stream, "%s%c %f\n", "�������� ��������� ������", delim, this->specific_cohesion);
}

Archive& operator >>(Archive& ar, StrengthDescription & sd)
{
	ar >> sd.m_strength_description_version;
	switch (sd.m_strength_description_version)
	{
	case 1:
		{
			// ������ ���������� ������
			ar >> sd.deformation_modulus_defined;
			if(sd.deformation_modulus_defined)
				ar >> sd.deformation_modulus;

			// ���� ����������� ������
			ar >> sd.internal_friction_angle_defined;
			if(sd.internal_friction_angle_defined)
				ar >> sd.internal_friction_angle;

			// �������� ��������� ������
			ar >> sd.specific_cohesion_defined;
			if (sd.specific_cohesion_defined)
				ar >> sd.specific_cohesion;
		}
		break;
	default:
		{
			throw VersionException(sd.m_strength_description_version, VersionException::cannot_load, Object::object_type::undefined);
		}
		break;
	}
	return ar;
}
void CGround::SavingAsDat(FILE * stream)
{
	fprintf(stream, "%s\n", "�����������");
	this->normative_description.SavingAsDat(stream);
	fprintf(stream, "%s\n", "��������� �� �����������");
	this->calculated_on_deformations_description.SavingAsDat(stream);
	fprintf(stream, "%s\n", "��������� �� ������� �����������");
	this->calculated_on_carry_ability_description.SavingAsDat(stream);
}

void GroundDescription::SavingAsDat(FILE * stream)
{
	char delim = '\t';
			// �������� ��� ������ ������,��/�3                          26.68
			if(this->specific_gravity_of_ground_particles_defined)
				fprintf(stream, "%s%c %f\n", "�������� ��� ������ ������,��/�3", delim, this->specific_gravity_of_ground_particles);
			// �������� ��� ������,��/�3                                 18.15
			if(this->specific_gravity_of_ground_defined)
				fprintf(stream, "%s%c %f\n", "�������� ��� ������,��/�3", delim, this->specific_gravity_of_ground);
			// �������� ��� ������ ������,��/�3                          15.30
			if(this->specific_gravity_of_dry_ground_defined)
				fprintf(stream, "%s%c %f\n", "�������� ��� ������ ������,��/�3", delim, this->specific_gravity_of_dry_ground);
			// �������� ��� ��������������� ������,��/�3                 19.33
			if(this->specific_gravity_of_water_saturated_ground_defined)
				fprintf(stream, "%s%c %f\n", "�������� ��� ��������������� ������,��/�3", delim, this->specific_gravity_of_water_saturated_ground);
			// �������� ��� ����������� � ���� ������,��/�3               9.64
			if(this->specific_gravity_of_suspended_in_water_ground_defined)
				fprintf(stream, "%s%c %f\n", "�������� ��� ����������� � ���� ������,��/�3", delim, this->specific_gravity_of_suspended_in_water_ground);

			// ���������� (���� ��.)                                       .43
			if(this->porosity_defined)
				fprintf(stream, "%s%c %f\n", "���������� (���� ��.)", delim, this->porosity);
			// ����������� ���������� ���������� ����.���� ��.             .75
			if(this->natural_constitution_porosity_factor_defined)
				fprintf(stream, "%s%c %f\n", "", delim, this->natural_constitution_porosity_factor);

			// ��������� ��������� (���� ��.)                              .19
			if(this->natural_moisture_defined)
				fprintf(stream, "%s%c %f\n", "��������� ��������� (���� ��.)", delim, this->natural_moisture);

			// ��������� ������������� (���� ��.)                          .26    
			if(this->water_saturated_moisture_defined)
				fprintf(stream, "%s%c %f\n", "��������� ������������� (���� ��.)", delim, this->water_saturated_moisture);

			// ������� ���������                                           .69	
			if(this->degree_of_moisture_defined)
				fprintf(stream, "%s%c %f\n", "������� ���������", delim, this->degree_of_moisture);
			// ���������� �������������(���� ��.)                          .07
			if(this->lack_of_water_saturating_defined)
				fprintf(stream, "%s%c %f\n", "���������� �������������(���� ��.)", delim, this->lack_of_water_saturating);
			// ������ ������������                                         .28
			if(this->full_moisture_capacity_defined)
				fprintf(stream, "%s%c %f\n", "������ ������������", delim, this->full_moisture_capacity);


			// ���������� ���������                                       -.08
			if(this->fluidity_index_defined)
				fprintf(stream, "%s%c %f\n", "���������� ���������", delim, this->fluidity_index);
			// ���������� ��������� ���������.������                       .48
			if(this->fluidity_index_of_water_saturated_ground_defined)
				fprintf(stream, "%s%c %f\n", "���������� ��������� ���������.������", delim, this->fluidity_index_of_water_saturated_ground);

			// ����� ������������                                          .13
			if(this->plasticity_index_defined)
				fprintf(stream, "%s%c %f\n", "����� ������������", delim, this->plasticity_index);

			// ��������� �� ������� ��������� (���� ��.)                   .22
			if(this->moisture_on_fluidity_border_defined)
				fprintf(stream, "%s%c %f\n", "��������� �� ������� ��������� (���� ��.)", delim, this->moisture_on_fluidity_border);
			
			// ��������� �� ������� ������������ (���� ��.)                .17
			if(this->moisture_on_plasticity_border_defined)
				fprintf(stream, "%s%c %f\n", "��������� �� ������� ������������ (���� ��.)", delim, this->moisture_on_plasticity_border);


			fprintf(stream, "%s\n", "����������� ��������������");
			this->strength_description.SavingAsDat(stream);
			fprintf(stream, "%s\n", "�� ����");
			this->strength_description_on_snip.SavingAsDat(stream);
			fprintf(stream, "%s\n", "��������������");
			this->strength_description_water_saturated.SavingAsDat(stream);
			fprintf(stream, "%s\n", "� �������� ��������");
			this->strength_description_in_task_condition.SavingAsDat(stream);
			fprintf(stream, "%s\n", "� ��������� ��������");
			this->strength_description_in_nature_condition.SavingAsDat(stream);
}



Archive& operator <<(Archive& ar, GroundDescription & gd)
{
	ar << gd.m_ground_description_version;
	switch (gd.m_ground_description_version)
	{
	case 1:
		{

			// �������� ��� ������ ������,��/�3                          26.68
			ar << gd.specific_gravity_of_ground_particles_defined;
			if(gd.specific_gravity_of_ground_particles_defined)
				ar << gd.specific_gravity_of_ground_particles;
			// �������� ��� ������,��/�3                                 18.15
			ar << gd.specific_gravity_of_ground_defined;
			if(gd.specific_gravity_of_ground_defined)
				ar << gd.specific_gravity_of_ground;
			// �������� ��� ������ ������,��/�3                          15.30
			ar << gd.specific_gravity_of_dry_ground_defined;
			if(gd.specific_gravity_of_dry_ground_defined)
				ar << gd.specific_gravity_of_dry_ground;
			// �������� ��� ��������������� ������,��/�3                 19.33
			ar << gd.specific_gravity_of_water_saturated_ground_defined;
			if(gd.specific_gravity_of_water_saturated_ground_defined)
				ar << gd.specific_gravity_of_water_saturated_ground;
			// �������� ��� ����������� � ���� ������,��/�3               9.64
			ar << gd.specific_gravity_of_suspended_in_water_ground_defined;
			if(gd.specific_gravity_of_suspended_in_water_ground_defined)
				ar << gd.specific_gravity_of_suspended_in_water_ground;

			// ���������� (���� ��.)                                       .43
			ar << gd.porosity_defined;
			if(gd.porosity_defined)
				ar << gd.porosity;
			// ����������� ���������� ���������� ����.���� ��.             .75
			ar << gd.natural_constitution_porosity_factor_defined;
			if(gd.natural_constitution_porosity_factor_defined)
				ar << gd.natural_constitution_porosity_factor;

			// ��������� ��������� (���� ��.)                              .19
			ar << gd.natural_moisture_defined;
			if(gd.natural_moisture_defined)
				ar << gd.natural_moisture;

			// ��������� ������������� (���� ��.)                          .26    
			ar << gd.water_saturated_moisture_defined;
			if(gd.water_saturated_moisture_defined)
				ar << gd.water_saturated_moisture;

			// ������� ���������                                           .69	
			ar << gd.degree_of_moisture_defined;
			if(gd.degree_of_moisture_defined)
				ar << gd.degree_of_moisture;
			// ���������� �������������(���� ��.)                          .07
			ar << gd.lack_of_water_saturating_defined;
			if(gd.lack_of_water_saturating_defined)
				ar << gd.lack_of_water_saturating;
			// ������ ������������                                         .28
			ar << gd.full_moisture_capacity_defined;
			if(gd.full_moisture_capacity_defined)
				ar << gd.full_moisture_capacity;


			// ���������� ���������                                       -.08
			ar << gd.fluidity_index_defined;
			if(gd.fluidity_index_defined)
				ar << gd.fluidity_index;
			// ���������� ��������� ���������.������                       .48
			ar << gd.fluidity_index_of_water_saturated_ground_defined;
			if(gd.fluidity_index_of_water_saturated_ground_defined)
				ar << gd.fluidity_index_of_water_saturated_ground;

			// ����� ������������                                          .13
			ar << gd.plasticity_index_defined;
			if(gd.plasticity_index_defined)
				ar << gd.plasticity_index;

			// ��������� �� ������� ��������� (���� ��.)                   .22
			ar << gd.moisture_on_fluidity_border_defined;
			if(gd.moisture_on_fluidity_border_defined)
				ar << gd.moisture_on_fluidity_border;
			
			// ��������� �� ������� ������������ (���� ��.)                .17
			ar << gd.moisture_on_plasticity_border_defined;
			if(gd.moisture_on_plasticity_border_defined)
				ar << gd.moisture_on_plasticity_border;


			ar << gd.strength_description;
			ar << gd.strength_description_on_snip;
			ar << gd.strength_description_water_saturated;
			ar << gd.strength_description_in_task_condition;
			ar << gd.strength_description_in_nature_condition;


		}
		break;
	default:
		{
			throw VersionException(gd.m_ground_description_version, VersionException::cannot_store, Object::object_type::undefined);
		}
		break;
	}
	return ar;
}
Archive& operator >>(Archive& ar, GroundDescription & gd)
{
	ar >> gd.m_ground_description_version;
	switch (gd.m_ground_description_version)
	{
	case 1:
		{
			// �������� ��� ������ ������,��/�3                          26.68
			ar >> gd.specific_gravity_of_ground_particles_defined;
			if(gd.specific_gravity_of_ground_particles_defined)
				ar >> gd.specific_gravity_of_ground_particles;
			// �������� ��� ������,��/�3                                 18.15
			ar >> gd.specific_gravity_of_ground_defined;
			if(gd.specific_gravity_of_ground_defined)
				ar >> gd.specific_gravity_of_ground;
			// �������� ��� ������ ������,��/�3                          15.30
			ar >> gd.specific_gravity_of_dry_ground_defined;
			if(gd.specific_gravity_of_dry_ground_defined)
				ar >> gd.specific_gravity_of_dry_ground;
			// �������� ��� ��������������� ������,��/�3                 19.33
			ar >> gd.specific_gravity_of_water_saturated_ground_defined;
			if(gd.specific_gravity_of_water_saturated_ground_defined)
				ar >> gd.specific_gravity_of_water_saturated_ground;
			// �������� ��� ����������� � ���� ������,��/�3               9.64
			ar >> gd.specific_gravity_of_suspended_in_water_ground_defined;
			if(gd.specific_gravity_of_suspended_in_water_ground_defined)
				ar >> gd.specific_gravity_of_suspended_in_water_ground;

			// ���������� (���� ��.)                                       .43
			ar >> gd.porosity_defined;
			if(gd.porosity_defined)
				ar >> gd.porosity;
			// ����������� ���������� ���������� ����.���� ��.             .75
			ar >> gd.natural_constitution_porosity_factor_defined;
			if(gd.natural_constitution_porosity_factor_defined)
				ar >> gd.natural_constitution_porosity_factor;

			// ��������� ��������� (���� ��.)                              .19
			ar >> gd.natural_moisture_defined;
			if(gd.natural_moisture_defined)
				ar >> gd.natural_moisture;

			// ��������� ������������� (���� ��.)                          .26    
			ar >> gd.water_saturated_moisture_defined;
			if(gd.water_saturated_moisture_defined)
				ar >> gd.water_saturated_moisture;

			// ������� ���������                                           .69	
			ar >> gd.degree_of_moisture_defined;
			if(gd.degree_of_moisture_defined)
				ar >> gd.degree_of_moisture;
			// ���������� �������������(���� ��.)                          .07
			ar >> gd.lack_of_water_saturating_defined;
			if(gd.lack_of_water_saturating_defined)
				ar >> gd.lack_of_water_saturating;
			// ������ ������������                                         .28
			ar >> gd.full_moisture_capacity_defined;
			if(gd.full_moisture_capacity_defined)
				ar >> gd.full_moisture_capacity;


			// ���������� ���������                                       -.08
			ar >> gd.fluidity_index_defined;
			if(gd.fluidity_index_defined)
				ar >> gd.fluidity_index;
			// ���������� ��������� ���������.������                       .48
			ar >> gd.fluidity_index_of_water_saturated_ground_defined;
			if(gd.fluidity_index_of_water_saturated_ground_defined)
				ar >> gd.fluidity_index_of_water_saturated_ground;

			// ����� ������������                                          .13
			ar >> gd.plasticity_index_defined;
			if(gd.plasticity_index_defined)
				ar >> gd.plasticity_index;

			// ��������� �� ������� ��������� (���� ��.)                   .22
			ar >> gd.moisture_on_fluidity_border_defined;
			if(gd.moisture_on_fluidity_border_defined)
				ar >> gd.moisture_on_fluidity_border;
			
			// ��������� �� ������� ������������ (���� ��.)                .17
			ar >> gd.moisture_on_plasticity_border_defined;
			if(gd.moisture_on_plasticity_border_defined)
				ar >> gd.moisture_on_plasticity_border;


			ar >> gd.strength_description;
			ar >> gd.strength_description_on_snip;
			ar >> gd.strength_description_water_saturated;
			ar >> gd.strength_description_in_task_condition;
			ar >> gd.strength_description_in_nature_condition;
		}
		break;
	default:
		{
			throw VersionException(gd.m_ground_description_version, VersionException::cannot_load, Object::object_type::undefined);
		}
		break;
	}
	return ar;
}



DWORD CSand::Serialize(Archive & ar)
{
	printf("CSand::Serialize(Archive& ar)\n");
	this->CSandGround::SandGround_Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_sand_version;
		switch (m_sand_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_sand_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_sand_version;
		switch (m_sand_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_sand_version, VersionException::cannot_load,  Object::object_type::undefined);
			}
			break;
		}
	}
	return 0;
}


DWORD CSandyLoam::Serialize(Archive & ar)
{
	printf("CSandyLoam::Serialize(Archive& ar)\n");
	this->CClayGround::ClayGround_Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_sandyloam_version;
		switch (m_sandyloam_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_sandyloam_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_sandyloam_version;
		switch (m_sandyloam_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_sandyloam_version, VersionException::cannot_load,  Object::object_type::undefined);
			}
			break;
		}
	}
	return 0;
}


DWORD CLoam::Serialize(Archive & ar)
{
	printf("CLoam::Serialize(Archive& ar)\n");
	this->CClayGround::ClayGround_Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_loam_version;
		switch (m_loam_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_loam_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_loam_version;
		switch (m_loam_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_loam_version, VersionException::cannot_load,  Object::object_type::undefined);
			}
			break;
		}
	}
	return 0;
}


DWORD CClay::Serialize(Archive & ar)
{
	printf("CClay::Serialize(Archive& ar)\n");
	this->CClayGround::ClayGround_Serialize(ar);
	if (ar.IsStoring())
	{
		ar << m_clay_version;
		switch (m_clay_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_clay_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_clay_version;
		switch (m_clay_version)
		{
		case 1:
			{
			}
			break;
		default:
			{
				throw VersionException(m_clay_version, VersionException::cannot_load,  Object::object_type::undefined);
			}
			break;
		}
	}
	return 0;
}



Archive& operator <<(Archive& ar, CSandGround::sand_type & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, CSandGround::sand_type & tp)
{
	int t;
	ar >> t;

	tp = (CSandGround::sand_type) t;

	return ar;
}

Archive& operator <<(Archive& ar, CSandGround::sand_strength & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, CSandGround::sand_strength & tp)
{
	int t;
	ar >> t;

	tp = (CSandGround::sand_strength) t;

	return ar;
}


Archive& operator <<(Archive& ar, CClayGround::clay_solidity & tp)
{
	int t = int  (tp);
	ar << t;

	return ar;
}
Archive& operator >>(Archive& ar, CClayGround::clay_solidity & tp)
{
	int t;
	ar >> t;

	tp = (CClayGround::clay_solidity) t;

	return ar;
}
void CSandGround::SandGround_Serialize(Archive& ar)
{
	printf("CSandGround::SandGround_Serialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		ar << m_sand_ground_version;
		switch (m_sand_ground_version)
		{
		case 1:
			{
				ar << m_sand_type;
				ar << m_sand_strength;
			}
			break;
		default:
			{
				throw VersionException(m_sand_ground_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_sand_ground_version;
		switch (m_sand_ground_version)
		{
		case 1:
			{
				ar >> m_sand_type;
				ar >> m_sand_strength;
			}
			break;
		default:
			{
				throw VersionException(m_sand_ground_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}

void CClayGround::ClayGround_Serialize(Archive& ar)
{
	printf("CClayGround::ClayGround_Serialize(Archive& ar)\n");
	if (ar.IsStoring())
	{
		ar << m_clay_ground_version;
		switch (m_clay_ground_version)
		{
		case 1:
			{
				ar << m_clay_solidity;
			}
			break;
		default:
			{
				throw VersionException(m_clay_ground_version, VersionException::cannot_store, Object::object_type::undefined);
			}
			break;
		}
	}
	else
	{
		ar >> m_clay_ground_version;
		switch (m_clay_ground_version)
		{
		case 1:
			{
				ar >> m_clay_solidity;
			}
			break;
		default:
			{
				throw VersionException(m_clay_ground_version, VersionException::cannot_load, Object::object_type::undefined);
			}
			break;
		}
	}
}

