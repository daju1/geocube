#pragma once

#include <float.h>
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <commctrl.h>
#endif
#include "BaseLab.h"
#include "../../surfdoc/src/Ground.h"

#define LABORATORY_WITH_SURFDOC 0
#define USE_LAB_TRIALS_VECTOR 1

#define MEAN_PHYS_VYPROB 1
#define MEAN_VYPROB 1

struct LabTrialValueType;
struct CompressionValueType;
class LabLayer;

class MyExcel;

class LabNumber;
class LabTrialResults;

#include "TrialDataDef.h"

#include "prop_value.h"

struct trial_value
{
	short f;
	double v;

	trial_value()
	{
		f = TRIAL_VALUE_UNDEFINED;
		v = -DBL_MAX;
	}

	trial_value(const double rs)
	{
		f = TRIAL_VALUE_DEFINED;
		v = rs;
	}

	trial_value& operator= (const double & rs)
	{
		f = TRIAL_VALUE_DEFINED;
		v = rs;
		return *this;
	}

	trial_value& operator=(const trial_value& ob)
	{
		f = ob.f;
		v = ob.v;
		return *this;
	}



};
bool inline operator>(trial_value& ob1, trial_value& ob2)
{
	return ob1.v > ob2.v;
}
bool inline operator>(const double& ob1, trial_value& ob2)
{
	return ob1 > ob2.v;
}
bool inline operator>(trial_value& ob1, const double& ob2)
{	
	return ob1.v > ob2;
}

bool inline operator<(trial_value& ob1, trial_value& ob2)
{
	return ob1.v < ob2.v;
}
bool inline operator<(const double& ob1, trial_value& ob2)
{
	return ob1 < ob2.v;
}
bool inline operator<(trial_value& ob1, const double& ob2)
{	
	return ob1.v < ob2;
}



bool inline operator>=(trial_value& ob1, trial_value& ob2)
{
	return ob1.v >= ob2.v;
}
bool inline operator>=(const double& ob1, trial_value& ob2)
{
	return ob1 >= ob2.v;
}
bool inline operator>=(trial_value& ob1, const double& ob2)
{	
	return ob1.v >= ob2;
}

bool inline operator<=(trial_value& ob1, trial_value& ob2)
{
	return ob1.v <= ob2.v;
}
bool inline operator<=(const double& ob1, trial_value& ob2)
{
	return ob1 <= ob2.v;
}
bool inline operator<=(trial_value& ob1, const double& ob2)
{	
	return ob1.v <= ob2;
}












trial_value inline operator+(trial_value& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v + ob2.v;
	return temp;
}
trial_value inline operator+(const double& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1 + ob2.v;
	return temp;
}
trial_value inline operator+(trial_value& ob1, const double& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v + ob2;
	return temp;
}





trial_value inline operator-(trial_value& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v - ob2.v;
	return temp;
}
trial_value inline operator-(const double& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1 - ob2.v;
	return temp;
}
trial_value inline operator-(trial_value& ob1, const double& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v - ob2;
	return temp;
}



trial_value inline operator*(trial_value& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v * ob2.v;
	return temp;
}
trial_value inline operator*(const double& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1 * ob2.v;
	return temp;
}
trial_value inline operator*(trial_value& ob1, const double& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v * ob2;
	return temp;
}




trial_value inline operator/(trial_value& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v / ob2.v;
	return temp;
}
trial_value inline operator/(const double& ob1, trial_value& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1 / ob2.v;
	return temp;
}
trial_value inline operator/(trial_value& ob1, const double& ob2)
{
	trial_value temp;
	temp.f = TRIAL_VALUE_DEFINED;
	temp.v = ob1.v / ob2;
	return temp;
}
struct trial_t_value : public trial_value
{
	double t;

	trial_t_value() : trial_value()
	{
		t = 0.0;
	}

	trial_t_value(const double rs) : trial_value(rs)
	{
		t = 0.0;
	}

	trial_t_value& operator= (const double & rs)
	{
		t = 0.0;
		f = TRIAL_VALUE_DEFINED;
		v = rs;
		return *this;
	}

	trial_t_value& operator=(const trial_value& ob)
	{
		t = 0.0;
		f = ob.f;
		v = ob.v;
		return *this;
	}
};
class Trial
{
public:
	virtual bool ExcludeConnected() = 0;
	virtual bool IncludeConnected() = 0;

};

struct trial_got_value
{
	short * pf;
	//const double * v;
	double v;
	LabNumber * lab_number;
	Trial * trial;

	trial_got_value()
	{
		pf = NULL;
		v = NULL;
		lab_number = NULL;
		trial = NULL;
	}

	trial_got_value(trial_value& rs)
	{
		pf = &rs.f;
		v = rs.v;
	}

	trial_got_value& operator= (trial_value& rs)
	{
		pf = &rs.f;
		v = rs.v;
		return *this;
	}
};
class SoilDescription;
class CompressionLabTrialResults;
class PhysicalLabTrial;
class CutLabTrial;
class LabTrial : public Trial
{
	friend void Passport_PhysMean(MyExcel & m_excel, PhysicalLabTrial * phys_trial_1, PhysicalLabTrial * phys_trial_2, const char * suffix);
	friend void Passport_Phys(MyExcel & m_excel, PhysicalLabTrial * phys_trial, trial_value & e0, const char * suffix, bool to_set_calculed);

	friend void PrintfPropE(CompressionLabTrialResults * res, vector<fmtstr> & text);
	friend void Passport_Graph(MyExcel & m_excel, CutLabTrial * cut_lab_trial);


	friend class CompressionLabTrial;
	friend class CompressionLabTrial3;
	friend class CompressionLabTrialResults;
	friend class CompressionLabTrialResults3;
	friend class FractionsLabTrialResults;
	friend class ChemicalLabTrialResults;
	friend class LabNumber;
	friend class LabLayer;
	friend class Gurvich;
	friend class CLaboratoryView;
	friend class ExcelSandGranular;
	friend class ExcelAreometrGranular;
	friend class ExcelCut;
	friend class ExcelCompression;
	friend class ExcelArchiveCompression;
	friend class ExcelArchiveCut;
	friend class ExcelVegetableRemains;
	friend class PhysicalLabTrial;
	
	
protected:
	LabNumber * lab_number;
	LabTrialResults * results;
public:

	void ReCalcProperties(bool labnumber_recalc_e_log_interp);

	virtual string GetSoilDescription() = 0;
	virtual void GetSoilDescription(SoilDescription & sd) = 0;



	void Init();
	LabTrial();
	~LabTrial();

	const LabNumber * GetLabNumber() {return lab_number;}


	void SetLabNumber(const LabNumber * labnumber){lab_number = (LabNumber *)labnumber;}
	// признаки испытаний
	// численные значения соответствуют таковым в формате файла LAB
	enum indication 
	{
		undefined_lab_trial_indication							= 0,
		physical												= 1, 
		chemical												= 2, 
		fractions												= 3,
		compression_nature_condition_absolute_deformation		= 4,
		compression_task_condition_absolute_deformation			= 5,
		compression_shrinkage_absolute_deformation				= 6,
		cut_resistance_nature_condition							= 7,
		cut_resistance_task_condition							= 8,
		pressing												= 9,
		filtration_coefficient_with_pressures					= 10, 
		filtration_coefficient_with_densities					= 11,
		compression_3,						
		end 
	};
	static const char * LabTrialTypeToString(LabTrial::indication t);
	static const char * LabTrialTypeToStringRus(LabTrial::indication t);
	LabTrial::indication trial_indication;
#if USE_LAB_TRIALS_VECTOR
	long m_id_vyprob;

	static void * operator new  (size_t size, LabTrial::indication, long id_vyprob);
	static void operator delete  (void * p, LabTrial::indication, long id_vyprob);
#else
	static void * operator new  (size_t size, LabTrial::indication);
	static void operator delete  (void * p, LabTrial::indication);
#endif
	void * operator new  (size_t size){return ::operator new  (size);}
	void operator delete  (void * p)  {return ::operator delete  (p);}


//	virtual void Normatives(vector<fmtstr> & text) = 0;

	virtual void PrintfProperties() = 0;
	virtual void Properties() = 0;
	virtual void PrintfProperties(vector<fmtstr> & text) = 0;
	virtual void PrintfProperties(vector<LabData> & labdata) = 0;

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v) = 0;
	virtual bool IncludeConnected(){return false;}
	virtual bool ExcludeConnected(){return false;}
	
	virtual void Passport(const char * fn) = 0;

};
inline LabTrial::indication operator++( LabTrial::indication &rs, int )
{
   return rs = (LabTrial::indication)(rs + 1);
}
enum lab_trial_vt
{
};

class LabTrialResults : public Trial
{
	friend class Gurvich;
	friend class CompressionLabTrialResults3;
	friend void PrintfPropE(CompressionLabTrialResults * res, vector<fmtstr> & text);
protected:
	LabTrial * lab_trial;
public:
	bool calculed;
	LabTrialResults(LabTrial * trial);
	~LabTrialResults();
	virtual void ReCalcProperties(bool labnumber_recalc_e_log_interp){calculed = false; CalcProperties();}
	virtual void CalcProperties() = 0;
	virtual void PrintfProperties(vector<fmtstr> & text) = 0;
	virtual void PrintfProperties(vector<LabData> & labdata) = 0;

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v) = 0;
};
class PhysicalLabTrial : public LabTrial
{
public:
	enum value_type
	{
		none = 0,
		// влажность на границе текучести (доли ед.)                   .22
		vt_moisture_on_fluidity_border,
		// влажность на границе раскатывания (пластичности) (доли ед.)                .17
		vt_moisture_on_plasticity_border,
		// влажность природного крупнообмена
		vt_moisture_of_nature_large_exchange,
		// влажность пробы заполнителя
		vt_moisture_of_aggregate_sample,
		// гигроскопическая влажность
		vt_hygroscopic_moisture,
		// максимальная молекулярная влагоёмкость
		vt_maximal_molecular_moisture_capacity,
		// плотность частиц грунта, г/см3                   2.71
		vt_density_of_ground_particles,
		// плотность грунта, г/см3                          2.00
		vt_density_of_ground,
		end
	};
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);
	static const char * ValueTypeToString(PhysicalLabTrial::value_type vt);
	static int GetSignForReliabilityK(PhysicalLabTrial::value_type vt);

	// влажность на границе текучести (доли ед.)                   .22
	trial_value moisture_on_fluidity_border;
	// влажность на границе раскатывания (пластичности) (доли ед.)                .17
	trial_value moisture_on_plasticity_border;
	// влажность природного крупнообмена
	trial_value moisture_of_nature_large_exchange;
	// влажность пробы заполнителя
	trial_value moisture_of_aggregate_sample;
	// гигроскопическая влажность
	trial_value hygroscopic_moisture;
	// максимальная молекулярная влагоёмкость
	trial_value maximal_molecular_moisture_capacity;
	// плотность частиц грунта,г/см3                   2.71
	trial_value density_of_ground_particles;
	// плотность грунта,г/см3                          2.00
	trial_value density_of_ground;


#if USE_LAB_TRIALS_VECTOR
	PhysicalLabTrial(long id_vyprob);
#else
	PhysicalLabTrial();
#endif
	~PhysicalLabTrial(){}

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();



		
	virtual void Passport(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);

};
inline PhysicalLabTrial::value_type operator++( PhysicalLabTrial::value_type &rs, int )
{
   return rs = (PhysicalLabTrial::value_type)(rs + 1);
}
class PhysicalLabTrialResults : public LabTrialResults
{
public:
	enum value_type
	{
		none = 0,
		//коэффициент пористости
		vt_e,
		// Полная влагоёмкость
		vt_water_full_capacity,
		// Влажность водонасыщения
		vt_w_water_saturated,
		// Недостаток водонасыщения
		vt_lack_of_water_saturating,
		// плотность сухого грунта
		vt_density_of_dry_ground,
		// плотность водонасыщенного грунта
		vt_density_of_water_saturated_ground,
		//плотность взвешенного в воде грунта
		vt_density_of_suspended_in_water_ground,
		//пористость	
		vt_n,
		//степень влажности 
		vt_S,
		vt_vlazhnost,
		// число пластичности	
		vt_plasticity_index,
		// определяем тип грунта
		vt_ground_type,
		// показатель текучести fluidity_index
		vt_fluidity_index_nature,
		vt_fluidity_index_water_saturated,

		// Супесь - консистенция
		// Суглинок и глина - консистенция
		vt_Consistencia_nature,
		vt_Consistencia_water_saturated,

		// удельный вес частиц грунта,г/см3                   2.71
		vt_specific_gravity_of_ground_particles,
		// удельный вес грунта,г/см3                          2.00
		vt_specific_gravity_of_ground,
		// удельный вес сухого грунта
		vt_specific_gravity_of_dry_ground,
		// удельный вес водонасыщенного грунта
		vt_specific_gravity_of_water_saturated_ground,
		// удельный вес взвешенного в воде грунта
		vt_specific_gravity_of_suspended_in_water_ground,



		end
	};
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);
 	static const char * ValueTypeToString(PhysicalLabTrialResults::value_type vt);
 	static int GetSignForReliabilityK(PhysicalLabTrialResults::value_type vt);

	
   
	//коэффициент пористости
	trial_value e;
	// Полная влагоёмкость
	trial_value water_full_capacity;
	// Влажность водонасыщения
	trial_value w_water_saturated;
	// Недостаток водонасыщения
	trial_value lack_of_water_saturating;
	// плотность сухого грунта
	trial_value density_of_dry_ground;
	// плотность водонасыщенного грунта
	trial_value density_of_water_saturated_ground;
	//плотность взвешенного в воде грунта
	trial_value density_of_suspended_in_water_ground;
	//пористость	
	trial_value n;
	//степень влажности 
	trial_value S;

	enum SandVlazhnost
	{
		undefined_vlazhnost = 0,
		malovlazhnyj,
		vlazhnyj,
		nasyschennyj_vodoj
	};
 	static const char * SandVlazhnostToString(PhysicalLabTrialResults::SandVlazhnost vzh);
 	static const char * SandVlazhnostToStringSmall(PhysicalLabTrialResults::SandVlazhnost vzh);
	SandVlazhnost m_sand_vlazhnost;

	// число пластичности	
	trial_value plasticity_index;
	// определяем тип грунта
	CGround::ground_type t;
	// показатель текучести fluidity_index
	trial_value fluidity_index_nature;
	trial_value fluidity_index_water_saturated;

	enum Consistencia
	{
		undefined_cons = 0,
		// Супесь - консистенция
		tverdaya,
		plastichnaya,
		tekuchaya,
		// Суглинок и глина - консистенция
		tverdye,
		polutverdye,
		tugoplastichnye,
		myagkoplastichye,
		tekucheplastichnye,
		tekuchie
	};
 	static const char * ConsistenciaToString(PhysicalLabTrialResults::Consistencia con);
 	static const char * ConsistenciaToStringSmall(PhysicalLabTrialResults::Consistencia con);

	Consistencia m_Consistencia_nature;
	Consistencia m_Consistencia_water_saturated;


	// удельный вес частиц грунта,г/см3                   2.71
	trial_value specific_gravity_of_ground_particles;
	// удельный вес грунта,г/см3                          2.00
	trial_value specific_gravity_of_ground;
	// удельный вес сухого грунта
	trial_value specific_gravity_of_dry_ground;
	// удельный вес водонасыщенного грунта
	trial_value specific_gravity_of_water_saturated_ground;
	// удельный вес взвешенного в воде грунта
	trial_value specific_gravity_of_suspended_in_water_ground;




	void Init();

	PhysicalLabTrialResults(LabTrial * trial);
	~PhysicalLabTrialResults(){}

	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	static double water_saturated_part_of_full_water_capacity;
	
	virtual bool IncludeConnected(){return false;}
	virtual bool ExcludeConnected(){return false;}
};

inline PhysicalLabTrialResults::value_type operator++( PhysicalLabTrialResults::value_type &rs, int )
{
   return rs = (PhysicalLabTrialResults::value_type)(rs + 1);
}

class ChemicalLabTrial : public LabTrial
{
public:
	enum value_type
	{
		none = 0,
		// общее содержание солей
		vt_common_salts_content,
		// легкорастворимые соли
		vt_well_solutable_salts,
		// содержание растительных остатков
		vt_vegetable_remains_content,
		// органические вещества
		vt_organic_matters,
		// водородный показатель
		vt_pH,
		// потери массы стали
		vt_steel_mass_loss,
		// азотистые вещества
		vt_nitrogenic_matters,
		// хлор ион
		vt_Cl_ion,
		// ион железа
		vt_Fe_ion,

		vt_gips,
		vt_carbonats,
		vt_gumus,

		end
	};
    
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);
	static const char * ChemicalLabTrial::ValueTypeToString(ChemicalLabTrial::value_type vt);
	static int ChemicalLabTrial::GetSignForReliabilityK(ChemicalLabTrial::value_type vt);

	// общее содержание солей
	trial_value common_salts_content;
	// легкорастворимые соли
	trial_value well_solutable_salts;
	// содержание растительных остатков
	trial_value vegetable_remains_content;
	// органические вещества
	trial_value organic_matters;
	// водородный показатель
	trial_value pH;
	// потери массы стали
	trial_value steel_mass_loss;
	// азотистые вещества
	trial_value nitrogenic_matters;
	// хлор ион
	trial_value Cl_ion;
	// ион железа
	trial_value Fe_ion;

	trial_value gips;
	trial_value carbonats;
	trial_value gumus;


#if USE_LAB_TRIALS_VECTOR
	ChemicalLabTrial(long id_vyprob);
#else
	ChemicalLabTrial();
#endif
	~ChemicalLabTrial(){}

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();

	virtual void Passport(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);
};
inline ChemicalLabTrial::value_type operator++( ChemicalLabTrial::value_type &rs, int )
{
   return rs = (ChemicalLabTrial::value_type)(rs + 1);
}
class ChemicalLabTrialResults : public LabTrialResults
{
public:
	enum value_type
	{
		none = 0,
		end
	};
	
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	ChemicalLabTrialResults(LabTrial * trial);
	~ChemicalLabTrialResults(){}

	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	virtual bool IncludeConnected(){return false;}
	virtual bool ExcludeConnected(){return false;}

	enum Zatorfovannost
	{
		undefined_zatorfovannost = 0,
		bez_rastitelnyh_ostatkov,
		s_primesju_rastitelnyh_ostatkov,
		slabo_zatorfovanny,
		sredne_zatorfovanny,
		silno_zatorfovanny,
		torf
	};
	static const char * ZatorfovannostToString(ChemicalLabTrialResults::Zatorfovannost zat);
	Zatorfovannost m_zatorfovannost;

};


inline ChemicalLabTrialResults::value_type operator++( ChemicalLabTrialResults::value_type &rs, int )
{
   return rs = (ChemicalLabTrialResults::value_type)(rs + 1);
}
#define USE_FRACTION_DIAMETERS_INTERVAL 1

#if USE_FRACTION_DIAMETERS_INTERVAL
#else
#endif

struct fraction_diameters_interval
{
	double low;
	double high;
	fraction_diameters_interval()
	{
		low = -DBL_MAX;
		high = DBL_MAX;
	}
};
class FractionsLabTrial : public LabTrial
{
public:
	int granular_passport_type;
	enum value_type
	{
		none = 0,
		vt_n_fractions,
#if USE_FRACTION_DIAMETERS_INTERVAL
		vt_fractions_diameter_low,
		vt_fractions_diameter_high,
#else
		vt_fractions_diameter,
#endif
		vt_fractions_content,
		// содержание фракций в пробе заполнителя
		vt_fractions_content_in_aggregate_sample,
		// содержание честиц ДМ > 2
		vt_particles_content_of_diameter_more_2,
		// содержание честиц ДМ < 1
		vt_particles_content_of_diameter_less_1,
		// окатанность
		vt_pourness,
		// угол откоса сухого грунта
		vt_slope_angle_of_dry_ground,
		// угол откоса под водой
		vt_slope_angle_under_water,
		end
	};
	static const char * ValueTypeToString(FractionsLabTrial::value_type vt);
	static int GetSignForReliabilityK(FractionsLabTrial::value_type vt);
	
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

#if USE_LAB_TRIALS_VECTOR
	FractionsLabTrial(long id_vyprob);
#else
	FractionsLabTrial();
#endif
	~FractionsLabTrial(){}

	// количество фракций, 
	int n_fractions;
#if !USE_LAB_LAYER_FRACTIONS
	// массив диаметров фракций
#if USE_FRACTION_DIAMETERS_INTERVAL
	fraction_diameters_interval * fractions_diameters;
#else
	double * fractions_diameters;
#endif
#endif
	// массив содержания фракций
	trial_value * fractions_content;


	// содержание фракций в пробе заполнителя
	trial_value fractions_content_in_aggregate_sample;
	// содержание честиц ДМ > 2
	trial_value particles_content_of_diameter_more_2;
	// содержание честиц ДМ < 1
	trial_value particles_content_of_diameter_less_1;
	// окатанность
	trial_value pourness;
	// угол откоса сухого грунта
	trial_value slope_angle_of_dry_ground;
	// угол откоса под водой
	trial_value slope_angle_under_water;


	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();

	void FillZhurnal(MyExcel & m_excel, int i16, int i17);

		
	virtual void Passport(const char * fn);
	void Passport_0(const char * fn);
	void Passport_1(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);

};
inline FractionsLabTrial::value_type operator++( FractionsLabTrial::value_type &rs, int )
{
   return rs = (FractionsLabTrial::value_type)(rs + 1);
}
class FractionsLabTrialResults : public LabTrialResults
{
public:
	//Классификация крупнообломочных и песчаных грунтов
	enum SandSoilsClass
	{
		undefined_sand_soil = 0,
		//Крупнообломочный
		valunnyj_or_glubovuj,
		galechnikovyj_or_schebenistyj,
		gravijnyj_or_dresvyanyj,
		// Песчаный
		gravelistyj,
		krupnyj,
		srednej_krupnosti,
		melkij,
		pylevatyj
	};
	static const char * SandSoilsClassToString(FractionsLabTrialResults::SandSoilsClass sand_soil_class);
	static const char * SandSoilsClassToStringSmall(FractionsLabTrialResults::SandSoilsClass sand_soil_class);
	
	// классификация глинистых грунтов по содержанию глинистых частиц (<0.005)
	enum ClaySoilsClass
	{
		undefined_clay_soil = 0,
		clay,		//	Глина  >30%
		loam,		//	суглинок 30-10%
        sandyLoam,	//	супесь 10-3%
		sand		// < 3%		
	};
	static const char * ClaySoilsClassToString(FractionsLabTrialResults::ClaySoilsClass clay_soil_class);
	static const char * ClaySoilsClassToStringSmall(FractionsLabTrialResults::ClaySoilsClass clay_soil_class);

	enum value_type
	{
		none = 0,
		vt_pyl_frac_content,
		vt_clay_frac_content,//m_soderzhanie_glinistyh_chastic
		vt_clay_soil_class,
		vt_sand_soil_class,
		vt_d_60,
		vt_d_10,
		vt_C_u,
		vt_neodnorodnost,
		end
	};
	static const char * ValueTypeToString(FractionsLabTrialResults::value_type vt);
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);


	FractionsLabTrialResults(LabTrial * trial);
	~FractionsLabTrialResults(){}
	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	virtual bool IncludeConnected(){return false;}
	virtual bool ExcludeConnected(){return false;}

	FractionsLabTrialResults::ClaySoilsClass m_clay_soil_class;
	trial_value m_clay_frac_content;//m_soderzhanie_glinistyh_chastic; // (<0.005mm)
	trial_value m_pyl_frac_content;// содержание пылеватой фракции (0.005-0.1)

	FractionsLabTrialResults::SandSoilsClass m_sand_soil_class;
	double m_minimum_krupnosti_chastic, m_soderzhanie_chastic;

	// Коэффициент неоднородности
	trial_value d_60;
	trial_value d_10;
	trial_value C_u;

	vector<double> v_diameters;
	vector<double> v_sum_content;

	enum Neodnorodnost
	{
		undefined_neodnorodnost = 0,
		odnorodnyj,
		neodnorodnyj
	};

	static const char * FractionsLabTrialResults::NeodnorodnostToStringSmall(FractionsLabTrialResults::Neodnorodnost no);
	static const char * FractionsLabTrialResults::NeodnorodnostToString(FractionsLabTrialResults::Neodnorodnost no);
	Neodnorodnost m_neodnorodnost;

};

inline FractionsLabTrialResults::value_type operator++( FractionsLabTrialResults::value_type &rs, int )
{
   return rs = (FractionsLabTrialResults::value_type)(rs + 1);
}

#define USE_LAB_LAYER_PRESSURES 0

class CompressionLabExperiment;
class CompressionLabTrial : public LabTrial
{
public:


	enum value_type
	{
		none = 0,
		vt_n_pressures,
		vt_pressure,
		vt_absolute_deformation,
		vt_relative_deformation,
		// тип прибора,	
		vt_apparatus_type,
		// диаметр кольца, 
		vt_hoop_diameter,
		// высота кольца, 
		vt_hoop_height,
		// метод испытания, 
		vt_trial_method,
		// заданная влажность, 
		vt_task_moisture,
		vt_task_moisture_v,
		// заданная плотность
		vt_task_density,
		vt_id_kolca,
		vt_id_phys_vyprob,

		vt_m_grunta,
		vt_m_grunta_zamoch,
		vt_m_grunta_posle,
		vt_m_grunta_vysush,
		end
	};

	static const char * ValueTypeToString(CompressionLabTrial::value_type vt);
	static int GetSignForReliabilityK(CompressionLabTrial::value_type vt);

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);
	virtual bool GetValue(CompressionValueType & vt, trial_got_value & v);

	enum type
	{
		undefined			= 0,
		nature_condition	= 1,
		task_condition		= 2, 
		shrinkage			= 3,
		tri
	};
	CompressionLabTrial::type com_type;

	static const char * CompressionLabTrialTypeToString(CompressionLabTrial::type comtype);
	static const char * CompressionLabTrialTypeToStringRus(CompressionLabTrial::type comtype);
	static const char * CompressionLabTrialTypeToStringRusSmall(CompressionLabTrial::type comtype);

#if USE_LAB_TRIALS_VECTOR
	CompressionLabTrial(CompressionLabTrial::type comtype, long id_vyprob);
	long id_phys_vyprob;
#else
	CompressionLabTrial(CompressionLabTrial::type comtype);
#endif
	~CompressionLabTrial(){}

	int n_pressures;
#if !USE_LAB_LAYER_PRESSURES
	double * pressures;
#endif
	trial_value * absolute_deformations;
	double hoop_height;
	double hoop_diameter;

	long id_kolca;

	trial_value m_grunta;
	trial_value m_grunta_zamoch;
	trial_value m_grunta_posle;
	trial_value m_grunta_vysush;

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();

		
	virtual void Passport(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);

};

class CompressionLabTrial3 : public LabTrial
{
public:


	int compression_passport_type;
	bool otnosit_def_on_graph;// какой график в паспорте: истина - относительное сжатие от давления, ложь - коэффициент пористости от давления

	long id_method;
	bool zamach;

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	void SetLabNumber();

	CompressionLabTrial * p_trial_1;
	CompressionLabTrial * p_trial_2;
	CompressionLabTrial * p_trial_3;

#if USE_LAB_TRIALS_VECTOR
	CompressionLabTrial3(long id_vyprob);
#else
	CompressionLabTrial3();
#endif

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();

	virtual void Passport(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);

	void Passport_1(const char * fn, bool ws = false);
	void Passport_1_new(bool otnosit_def_on_graph, const char * fn, bool ws = false);
	void Passport_2(const char * fn);
	void Passport_2_as_1(bool otnosit_def_on_graph, const char * fn);
	void Passport_2_as_mean(bool otnosit_def_on_graph, const char * fn);
	void Passport_2_as_diff_vyprob(bool otnosit_def_on_graph, const char * fn);
	void Passport_3(const char * fn);


};
inline CompressionLabTrial::value_type operator++( CompressionLabTrial::value_type &rs, int )
{
   return rs = (CompressionLabTrial::value_type)(rs + 1);
}

struct CompressionLogInterpolation
{
	int m_log;
	trial_value Sy_log;	
	trial_value minus_A;
	double x_0;
	trial_value m_C;

	size_t i1, i2;
	double p1, p2;
	double e1, e2;
	bool is_log;
	int interval;
};

class CompressionLabTrialResults;
struct x_compression
{
	double x;
	bool voda;
	x_compression()
	{
		x = 0.0;
		voda = false;
	}
	x_compression(double pressure, bool zamachivanie = false)
	{
		x = pressure;
		voda = zamachivanie;
	}
};
class Gurvich
{
	CompressionLabTrialResults * m_res;
public:
	Gurvich(CompressionLabTrialResults * res){m_res = res;}
	void SetParent(CompressionLabTrialResults * res){m_res = res;}
	~Gurvich(){}

	void CalcDeformationModuleOnShtampPrediction(
		const char * name, 
		int n,
		CompressionLabExperiment * compression, 
		// влажность
		double W,
		// влажность водонасыщения
		double W_sat,
		//коэффициент пористости
		double e,
		// число пластичности
		double Ip
		);

	
	int m_shtamp_lin_in_01_02_interval;
	trial_value Sy_shtamp_lin_in_01_02_interval;
	trial_value shtamp_lin_interp_a0_in_01_02_interval; 
	trial_value shtamp_lin_interp_a1_in_01_02_interval;

	int m_shtamp_lin_in_defined_interval;
	trial_value Sy_shtamp_lin_in_defined_interval;
	trial_value shtamp_lin_interp_a0_in_defined_interval; 
	trial_value shtamp_lin_interp_a1_in_defined_interval;




	vector<x_compression>		shtamp_vx;
	vector<trial_value>			shtamp_vy;

	void PrintGurvichShtamp(CompressionLabExperiment * compression, PhysicalLabTrial * phys, vector<fmtstr> * text, double W_sat, double & W);

	bool PrintShtampDeformationPrediction(
		CompressionLabExperiment * compression, 
		vector<fmtstr> * text,
		vector<LabData> * labdata);


	void PrintShtampDeformationPrediction(
		const char * name, 
		vector<fmtstr> * text,
		PlotData * plot_data
		);

	void CalcDeformationModuleOnShtampPrediction(
		CompressionLabExperiment * compression);

	double shtamp_deformation_module_01_02_pressure_interval[2];
	trial_value shtamp_deformation_module_in_01_02_interval;
	trial_value shtamp_deformation_module_in_01_02_interval_Kp;

	double shtamp_deformation_module_defined_pressure_interval[2];
	trial_value shtamp_deformation_module_in_defined_interval;
	trial_value shtamp_deformation_module_in_defined_interval_Kp;

	trial_value Kp;

	// диаметр штампа в прогнозе по Гурвичу	
	static double shtamp_diameter;	//см

	// предел второй производной кривой осадки после замачивания
	// для определения чётко-выраженного перегиба
	static double y_SecondDerivativeLimit;


	void Passport_Table1(MyExcel & m_excel, int fr, double & max_x, double & delta_x);

	void Passport_Table2(MyExcel & m_excel, int fr);

};

class CompressionLabTrialResults : public LabTrialResults
{		
	friend class Gurvich;

	CompressionLabTrial::type com_type;

public:

	static double e_SecondDerivativeLimit;

	bool zamachivanie;

	/*enum value_type0
	{
		none = 0,
		vt_ocenka_bytovogo_davlenia,

		vt_compression_module_y_in_01_02_interval,
		vt_S_lin_y_in_01_02_interval,
		vt_compression_module_y_in_defined_interval,
		vt_S_lin_y_in_defined_interval,

		vt_compression_module_e_in_01_02_interval,
		vt_S_lin_e_in_01_02_interval,
		vt_compression_module_e_in_defined_interval,
		vt_S_lin_e_in_defined_interval,

		vt_beta, 

		vt_deformation_module_y_in_01_02_interval,
		vt_deformation_module_y_in_defined_interval,

		vt_deformation_module_e_in_01_02_interval,
		vt_deformation_module_e_in_defined_interval,

		vt_mk, 

		vt_deformation_module_y_in_01_02_interval_mk,
		vt_deformation_module_e_in_01_02_interval_mk,

		vt_shtamp_deformation_module_in_01_02_interval,
		vt_shtamp_Sy_lin_in_01_02_interval,
		vt_shtamp_deformation_module_in_defined_interval,
		vt_shtamp_Sy_lin_in_defined_interval,
		vt_Kp, 
		vt_shtamp_deformation_module_in_01_02_interval_Kp,
		vt_shtamp_deformation_module_in_defined_interval_Kp,
		end
	};
*/
	enum value_type_0
	{
		none_0 = 0,
		vt_ocenka_bytovogo_davlenia,

		vt_nju_tab, 
		vt_nju_tab_ws,

		vt_beta_tab, 
		vt_beta_tab_ws, 
		//vt_beta_mavrodi, 
		vt_mk, 
		//vt_Kp,
		end_0
	};
#if USE_COMPR_PO_OTN_DEF	
	enum value_type_1
	{
		none_1 = 0,
		vt_compression_module_y_in_01_02_interval,
		vt_S_lin_y_in_01_02_interval,
		vt_compression_module_y_in_defined_interval,
		vt_S_lin_y_in_defined_interval,
		vt_deformation_module_y_in_01_02_interval,
		vt_deformation_module_y_in_defined_interval,
		vt_deformation_module_y_in_01_02_interval_mk,
		end_1
	};
#endif
	enum value_type_2
	{
		none_2 = 0,
		vt_a_in_01_02_interval,
		vt_a_in_defined_interval,
		vt_compression_module_e_in_01_02_interval,
		vt_S_lin_e_in_01_02_interval,
		vt_compression_module_e_in_defined_interval,
		vt_S_lin_e_in_defined_interval,
		vt_deformation_module_e_in_01_02_interval,
		vt_deformation_module_e_in_defined_interval,
		vt_deformation_module_e_in_01_02_interval_mk,
		end_2
	};

	enum value_type_3
	{
		none_3 = 0,
		vt_shtamp_deformation_module_in_01_02_interval,
		vt_shtamp_Sy_lin_in_01_02_interval,
		vt_shtamp_deformation_module_in_defined_interval,
		vt_shtamp_Sy_lin_in_defined_interval,
		vt_Kp, 
		vt_shtamp_deformation_module_in_01_02_interval_Kp,
		vt_shtamp_deformation_module_in_defined_interval_Kp,
		end_3
	};

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);
	bool GetValue(CompressionValueType & vt, trial_got_value & v);

	static const char * ValueTypeToString(CompressionLabTrialResults::value_type_0 vt, LabLayer * lablayer);
	static int GetSignForReliabilityK(CompressionLabTrialResults::value_type_0 vt);
#if USE_COMPR_PO_OTN_DEF
	static const char * ValueTypeToString(CompressionLabTrialResults::value_type_1 vt, LabLayer * lablayer, bool every);
	static int GetSignForReliabilityK(CompressionLabTrialResults::value_type_1 vt);
#endif
	static const char * ValueTypeToString(CompressionLabTrialResults::value_type_2 vt, LabLayer * lablayer, bool every);
	static int GetSignForReliabilityK(CompressionLabTrialResults::value_type_2 vt);

	static const char * ValueTypeToString(CompressionLabTrialResults::value_type_3 vt, LabLayer * lablayer, bool every);
	static int GetSignForReliabilityK(CompressionLabTrialResults::value_type_3 vt);

	trial_value mk;
#if !USE_GRINVICH_CLASS
	trial_value Kp;
#endif
	// коэффициент Пуассона
	trial_value nju_tab;
	trial_value nju_tab_ws;

	trial_value beta_tab;
	trial_value beta_tab_ws;

	//trial_value beta_mavrodi;
	trial_value ocenka_bytovogo_davlenia;

#if USE_COMPR_PO_OTN_DEF	

	int m_lin_y_in_01_02_interval;
	trial_value S_lin_y_in_01_02_interval;	
	trial_value lin_interp_y_a0_in_01_02_interval;
	trial_value lin_interp_y_a1_in_01_02_interval;


	int m_lin_y_in_defined_interval;
	trial_value S_lin_y_in_defined_interval;	
	trial_value lin_interp_y_a0_in_defined_interval;
	trial_value lin_interp_y_a1_in_defined_interval;
#endif

	int m_lin_e_in_01_02_interval;
	trial_value S_lin_e_in_01_02_interval;	
	trial_value lin_interp_e_a0_in_01_02_interval;
	trial_value lin_interp_e_a1_in_01_02_interval;

	// коэффициент уплотнения
	trial_value a_in_01_02_interval;


	int m_lin_e_in_defined_interval;
	trial_value S_lin_e_in_defined_interval;	
	trial_value lin_interp_e_a0_in_defined_interval;
	trial_value lin_interp_e_a1_in_defined_interval;

	// коэффициент уплотнения
	trial_value a_in_defined_interval;

							
	vector<x_compression> vx;
	vector<double> va;
	vector<trial_got_value> vy;
	vector<trial_got_value> ve;



	vector<CompressionLogInterpolation> v_e_log_interp;

	vector<x_compression>		meanX;
	vector<trial_got_value> minusDxDe;

	vector<double>		m2X;
	vector<trial_got_value> D2eDx2;

	double e_p;
	double a_p;
	double E_p;
	int p_interval;

	bool calc_e_log_interp;

	virtual void ReCalcProperties(bool labnumber_recalc_e_log_interp){calc_e_log_interp = labnumber_recalc_e_log_interp; calculed = false; CalcProperties();}


/*
	int m_sigma_0;
	trial_value S_sigma_0;
	trial_value exp_C_minus_A;
	trial_value sigma_0;

	int m_A_C;
	trial_value S_A_C;
	trial_value C;
	trial_value minus_A;
*/
	CompressionLabTrialResults(LabTrial * trial, CompressionLabTrial::type comtype);
	~CompressionLabTrialResults(){}

	void CalcProperties();

	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	Gurvich m_gurvich;

	
	//double deformation_module_pressure_interval[2];
	//trial_value deformation_module_01_02;
	
	//double shtamp_deformation_module_pressure_interval[2];
	//trial_value shtamp_deformation_module_01_02;

	static double deformation_module_01_02_pressure_interval[2]; //tranllated to global double g_CompressionLabTrialResults_deformation_module_01_02_pressure_interval[2];


	double def_module_01_02_pressure_interval[2];
#if USE_COMPR_PO_OTN_DEF	
	trial_value compression_module_y_in_01_02_interval;
	trial_value deformation_module_y_in_01_02_interval;
	trial_value deformation_module_y_in_01_02_interval_mk;
#endif
	trial_value compression_module_e_in_01_02_interval;
	trial_value deformation_module_e_in_01_02_interval;
	trial_value deformation_module_e_in_01_02_interval_mk;

	double def_module_defined_pressure_interval[2];
#if USE_COMPR_PO_OTN_DEF	
	trial_value compression_module_y_in_defined_interval;
	trial_value deformation_module_y_in_defined_interval;
#endif
	trial_value compression_module_e_in_defined_interval;
	trial_value deformation_module_e_in_defined_interval;


	virtual bool IncludeConnected();
	virtual bool ExcludeConnected();

	static bool compression_module_e_with_min_sq;
	//static bool use_mavrodi_beta;



};



class CompressionLabTrialResults3 : public LabTrialResults
{

public:
	CompressionLabTrialResults * p_result_1;
	CompressionLabTrialResults * p_result_2;
	CompressionLabTrialResults * p_result_3;

	CompressionLabTrialResults3(LabTrial * trial);


	virtual bool IncludeConnected();
	virtual bool ExcludeConnected();

	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void PrintfProperties_self(vector<fmtstr> & text);
	void PrintfProperties_self(vector<LabData> & labdata);
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);


	bool PrintDeformationModuleOnShtamp(
		CompressionLabExperiment * compression, 
		vector<fmtstr> * text,
		vector<LabData> * labdata);

	trial_value					gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_peregibu_vtoroj_krivoj;
	bool						gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_peregibu_vtoroj_krivoj_calculed;

	vector<double>				x_gurvich_shtamp_prosadka_po_dvum_krivym;
	vector<trial_value>			gurvich_shtamp_prosadka_po_dvum_krivym;
	vector<trial_value>			gurvich_shtamp_hdef_po_dvum_krivym;
	vector<trial_value>			gurvich_shtamp_otnosit_prosadochnost_po_dvum_krivym;
	bool gurvich_shtamp_prosadka_calculed_po_dvum_krivym;
	trial_value					gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_dvum_krivym;
	void PrintGurvichShtampProsadka_po_dvum_krivym(PlotData * plot_data);

	vector<double>				x_gurvich_shtamp_prosadka_po_odnoj_krivoj;
	vector<trial_value>			gurvich_shtamp_prosadka_po_odnoj_krivoj;
	vector<trial_value>			gurvich_shtamp_hdef_po_odnoj_krivoj;
	vector<trial_value>			gurvich_shtamp_otnosit_prosadochnost_po_odnoj_krivoj;
	bool gurvich_shtamp_prosadka_calculed_po_odnoj_krivoj;
	trial_value					gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_odnoj_krivoj;
	void PrintGurvichShtampProsadka_po_odnoj_krivoj(PlotData * plot_data);

	vector<double>				x_prosadka_po_dvum_krivym;
	vector<trial_value>			prosadka_po_dvum_krivym;
	vector<trial_value>			otnosit_prosadochnost_po_dvum_krivym;
	bool prosadka_calculed_po_dvum_krivym;
	trial_value					nachalnoe_prosadochnoe_davlenie_po_dvum_krivym;

	vector<double>				x_prosadka_po_odnoj_krivoj;
	vector<trial_value>			prosadka_po_odnoj_krivoj;
	vector<trial_value>			otnosit_prosadochnost_po_odnoj_krivoj;
	bool prosadka_calculed_po_odnoj_krivoj;
	trial_value					nachalnoe_prosadochnoe_davlenie_po_odnoj_krivoj;

	trial_value					svobodnoe_otnositelnoe_nabuhanie;
	trial_value					davlenie_nabuhania;
	//высота образца грунта при природной влажности и природном давлении (на глубине отбора образца)
	trial_value					h0;


	//вторая производная осадки после замачивания
	vector<double>		m2X;
	vector<trial_got_value> D2yDx2;
	bool D2yDx2_calculed;

	enum Prosadochnost
	{
		undefined_prosadocnist = 0,
		neprosadochnye,
		prosadochnye
	};
	static const char * ProsadochnostToString(CompressionLabTrialResults3::Prosadochnost pros);
	Prosadochnost m_prosadochnost; 


	enum Nabuhanie
	{
		undefined_nabuhanie = 0,
		nenabuhajuschie,
		nabuhajuschie
	};
	static const char * NabuhanieToString(CompressionLabTrialResults3::Nabuhanie nab);
	Nabuhanie m_nabuhanie; 

	/*double m_otzhatoj_vody = 0.0;
	double dejstvit_polnaja_osadka = 0.0;
	if (m_grunta_posle_2 && m_zamoch_grunta_2)
	{
		m_otzhatoj_vody = m_zamoch_grunta_2 - m_grunta_posle_2;
		dejstvit_polnaja_osadka = 10.0 * m_otzhatoj_vody / s_kolca;
	}

	double osadka_po_indikatory = 0.0;
	double popravochnyj_koefficient_alpha = 0.0;
	if (dejstvit_polnaja_osadka && osadka_po_indikatory)
	{
		popravochnyj_koefficient_alpha = dejstvit_polnaja_osadka / osadka_po_indikatory;
	}*/

	trial_value m_otzhatoj_vody;
	trial_value dejstvit_polnaja_osadka;
	trial_value popravochnyj_koefficient_alpha;


	enum value_type
	{
		none = 0,

		vt_gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_peregibu_vtoroj_krivoj,
		vt_gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_dvum_krivym,
		vt_gurvich_shtamp_nachalnoe_prosadochnoe_davlenie_po_odnoj_krivoj,

		vt_nachalnoe_prosadochnoe_davlenie_po_dvum_krivym,
		vt_nachalnoe_prosadochnoe_davlenie_po_odnoj_krivoj,


		vt_svobodnoe_otnositelnoe_nabuhanie,
		vt_davlenie_nabuhania,
		vt_h0,

		vt_popravochnyj_koefficient_alpha,
		vt_dejstvit_polnaja_osadka,
		vt_m_otzhatoj_vody,

		end
	};
	virtual bool GetValue(CompressionLabTrialResults3::value_type vt, trial_got_value & v);

	static const char * ValueTypeToString(CompressionLabTrialResults3::value_type vt);
	static int GetSignForReliabilityK(CompressionLabTrialResults3::value_type vt);

};
inline CompressionLabTrialResults::value_type_0 operator++( CompressionLabTrialResults::value_type_0 &rs, int )
{
   return rs = (CompressionLabTrialResults::value_type_0)(rs + 1);
}
inline CompressionLabTrialResults3::value_type operator++( CompressionLabTrialResults3::value_type &rs, int )
{
   return rs = (CompressionLabTrialResults3::value_type)(rs + 1);
}
#if USE_COMPR_PO_OTN_DEF	
inline CompressionLabTrialResults::value_type_1 operator++( CompressionLabTrialResults::value_type_1 &rs, int )
{
   return rs = (CompressionLabTrialResults::value_type_1)(rs + 1);
}
#endif
inline CompressionLabTrialResults::value_type_2 operator++( CompressionLabTrialResults::value_type_2 &rs, int )
{
   return rs = (CompressionLabTrialResults::value_type_2)(rs + 1);
}
inline CompressionLabTrialResults::value_type_3 operator++( CompressionLabTrialResults::value_type_3 &rs, int )
{
   return rs = (CompressionLabTrialResults::value_type_3)(rs + 1);
}
#define USE_LAB_LAYER_CUT_PRESSURES 0

class CutLabTrial : public LabTrial
{
public:
	int cut_passport_type;

	vector<ZrizVyprobData0> zriz_kolca0;
	vector<ZrizVyprobData1> zriz_kolca1;

	enum value_type
	{
		none = 0,
		vt_n_pressures,
		vt_pressure,
		vt_cut_resistance,
		// тип прибора,	
		vt_apparatus_type,
		// диаметр кольца, 
		vt_hoop_diameter,
		// высота кольца, 
		vt_hoop_height,
		// метод испытания, 
		vt_trial_method,
		// заданная влажность, 
		vt_task_moisture,
		vt_task_moisture_v,
		// заданная плотность
		vt_task_density,
		// 
		vt_hid, //Ход испытаний
		vt_shema, //Схема испытаний
		vt_stan, //Состояние грунта
		end
	};
	static const char * ValueTypeToString(CutLabTrial::value_type vt);
	static int GetSignForReliabilityK(CutLabTrial::value_type vt);

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);
	enum type
	{
		undefined			= 0,
		nature_condition	= 1,
		task_condition		= 2
	};
	CutLabTrial::type cut_type;

	static const char * CutLabTrialTypeToString(CutLabTrial::type cuttype);
	static const char * CutLabTrialTypeToStringRus(CutLabTrial::type cuttype);
	static const char * CutLabTrialTypeToStringRusSmall(CutLabTrial::type cuttype);

	long id_hid;
	long id_shema;
	long id_stan;

#if USE_LAB_TRIALS_VECTOR
	CutLabTrial(CutLabTrial::type cuttype, long id_vyprob);
#else
	CutLabTrial(CutLabTrial::type cuttype);
#endif
	~CutLabTrial(){}

	int n_pressures;
#if !USE_LAB_LAYER_CUT_PRESSURES
	double * pressures;
#endif
	trial_value * cut_resistances;

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();

	virtual void Passport(const char * fn);
	void Passport_0(const char * fn);
	void Passport_1(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);
};

inline CutLabTrial::value_type operator++( CutLabTrial::value_type &rs, int )
{
   return rs = (CutLabTrial::value_type)(rs + 1);
}
class CutLabTrialResults : public LabTrialResults
{
	CutLabTrial::type cut_type;
public:
	enum value_type
	{
		none = 0,
		vt_c,
		vt_tgfi,
		vt_fi,
		vt_Stau,
		end
	};
	static const char * ValueTypeToString(CutLabTrialResults::value_type vt, bool every);
	static int GetSignForReliabilityK(CutLabTrialResults::value_type vt);

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	trial_value c;
	trial_value tgfi;
	double fi;
	trial_value Stau;

	CutLabTrialResults(LabTrial * trial, CutLabTrial::type cuttype);
	~CutLabTrialResults(){}


	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	virtual bool IncludeConnected();
	virtual bool ExcludeConnected();
};

inline CutLabTrialResults::value_type operator++( CutLabTrialResults::value_type &rs, int )
{
   return rs = (CutLabTrialResults::value_type)(rs + 1);
}
class PressingLabTrial : public LabTrial
{
public:
	enum value_type
	{
		none = 0,
		vt_loads,
		vt_sections,
		end
	};

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

#if USE_LAB_TRIALS_VECTOR
	PressingLabTrial(long id_vyprob);
#else
	PressingLabTrial();
#endif
	~PressingLabTrial();

	// нагрузки
	double loads[3];
	// сечения
	double sections[3];

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();

		
	virtual void Passport(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);

};



inline PressingLabTrial::value_type operator++( PressingLabTrial::value_type &rs, int )
{
   return rs = (PressingLabTrial::value_type)(rs + 1);
}
class PressingLabTrialResults : public LabTrialResults
{
public:
	enum value_type
	{
		none = 0,
		end
	};
	
	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	PressingLabTrialResults(LabTrial * trial);
	~PressingLabTrialResults();

	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	virtual bool IncludeConnected(){return false;}
	virtual bool ExcludeConnected(){return false;}
};

inline PressingLabTrialResults::value_type operator++( PressingLabTrialResults::value_type &rs, int )
{
   return rs = (PressingLabTrialResults::value_type)(rs + 1);
}
class FiltrationLabTrial : public LabTrial
{
public:
	enum value_type
	{
		none = 0,
		vt_expenditures,
		vt_densities,
		end
	};

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	enum type
	{
		undefined			= 0,
		with_pressures		= 1,
		with_densities		= 2
	};
	FiltrationLabTrial::type filtr_type;

	static const char * FiltrationLabTrialTypeToString(FiltrationLabTrial::type filtrtype);
	static const char * FiltrationLabTrialTypeToStringRus(FiltrationLabTrial::type filtrtype);

#if USE_LAB_TRIALS_VECTOR
	FiltrationLabTrial(FiltrationLabTrial::type filtrtype, long id_vyprob);
#else
	FiltrationLabTrial(FiltrationLabTrial::type filtrtype);
#endif
	~FiltrationLabTrial(){}

	// расход
	double expenditures[3];
	// плотности
	double densities[3];

	void PrintfProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void Properties();
		
	virtual void Passport(const char * fn);
	virtual string GetSoilDescription();
	virtual void GetSoilDescription(SoilDescription & sd);
};

inline FiltrationLabTrial::value_type operator++( FiltrationLabTrial::value_type &rs, int )
{
   return rs = (FiltrationLabTrial::value_type)(rs + 1);
}
class FiltrationLabTrialResults : public LabTrialResults
{
public:
	enum value_type
	{
		none = 0,
		end
	};

	virtual bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	FiltrationLabTrialResults(LabTrial * trial, FiltrationLabTrial::type filtrtype);
	~FiltrationLabTrialResults(){}

	void CalcProperties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);

	virtual bool IncludeConnected(){return false;}
	virtual bool ExcludeConnected(){return false;}
};





inline FiltrationLabTrialResults::value_type operator++( FiltrationLabTrialResults::value_type &rs, int )
{
   return rs = (FiltrationLabTrialResults::value_type)(rs + 1);
}
#include "LabTrialValueType.h"
class LabParam
{
	friend HTREEITEM AddParamToTree(HWND hwndTV, LPSTR lpszItem, LabParam * lab_param, HTREEITEM hParent, HTREEITEM hInsertAfter);

	friend class Laboratory;
	friend class LabLayer;
	friend class CompressionLabParametersResults;
	friend class CompressionLabParametersResults1;
	friend class CompressionLabParametersResults2;
	friend class CompressionLabParametersResults3;
	friend class FractionsLabParametersInitial;
	friend class CompressionLabParametersInitial;
	friend class CutLabParametersInitial;

protected:
	LabLayer * lab_layer;
	bool m_bChecked_LabParam;
public:
	void SetLabLayer(LabLayer * ll)	{lab_layer = ll;}

	LabParam(LabLayer * ll) {m_bChecked_LabParam = true;lab_layer = ll;}

	bool m_bExpanded_LabParam; // for objectLists
	bool GetCheckedLabParam(){return m_bChecked_LabParam;}

	HTREEITEM parentTreeItem_LabParam;
	HTREEITEM myTreeItem_LabParam;
	
	virtual void FillContextMenuParamVirtual(HMENU& hMenu){}
	void Fill_Context_Menu_Param(HMENU& hMenu);
	void CreateContextMenuParam(HWND hWnd, LPARAM lParam);

	void Check(HWND hwndTV);
	void UnCheck(HWND hwndTV);

	virtual void ParamCheck(HWND hwndTV) = 0;
	virtual void ParamUnCheck(HWND hwndTV) = 0;
};


#define LAB_PARAMETERS_NEW 1

class LabParameters;
class LabParametersResults : public LabParam
{
protected:
	LabParameters * lab_parameters;
public:
	LabParametersResults(LabParameters * p, LabLayer * ll);
	virtual void FillLabParameters() = 0;
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1) = 0;

	virtual bool IsLabParam(const LabParam * p1) = 0;

	void GetChecked(vector<LabTrialValueType> & vvt);
	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result) = 0;

};

class LabParametersInitial : public LabParam
{
protected:
	LabParameters * lab_parameters;
protected:
public:
	LabParametersInitial(LabParameters * p, LabLayer * ll);
	virtual void FillLabParameters() = 0;

	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1) = 0;
	virtual bool IsLabParam(const LabParam * p1) = 0;

	void GetChecked(vector<LabTrialValueType> & vvt);
	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result) = 0;

};
class LabParameters : public LabParam
{
	friend class LabLayer;
	friend struct LabTrialValueType;
	friend class LabParametersInitial;
	friend class LabParametersResults;
	friend class CompressionLabTrialResults3;
	friend struct CompressionValueType;
protected:
	//LabParam initial;
	LabParametersInitial * parameters_initial;
	LabParametersResults * parameters_results;
	LabTrial::indication m_indication;
public:

	LabParameters::LabParameters(LabLayer * ll);


	void * operator new  (size_t size){return ::operator new  (size);}
	void operator delete  (void * p)  {return ::operator delete  (p);}

	static void * operator new  (size_t size, LabTrial::indication, LabLayer *);
	static void operator delete  (void * p, LabTrial::indication, LabLayer *);

	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);


	virtual void GetChecked(vector<LabTrialValueType> & vvt);

	virtual void FillLabParameters();
		
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

};
class LabParameter : public LabParam
{
	LabParam * lab_parameters;
public:
	LabTrialValueType m_vt;

	LabParameter(LabParam * p, LabLayer * ll, LabTrialValueType _vt) : LabParam (ll) {lab_parameters = p; m_vt = _vt;}
	virtual void LabParameter::FillContextMenuParamVirtual(HMENU& hMenu);

	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	//void AddCube();

};


class PhysicalLabParametersInitial : public LabParametersInitial
{
	map<PhysicalLabTrial::value_type, LabParameter*> m_params;
public:
	PhysicalLabParametersInitial(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(PhysicalLabTrial::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);

};

class PhysicalLabParametersResults : public LabParametersResults
{
	map<PhysicalLabTrialResults::value_type, LabParameter*> m_params;
public:
	PhysicalLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(PhysicalLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class ChemicalLabParametersInitial : public LabParametersInitial
{
	map<ChemicalLabTrial::value_type, LabParameter*> m_params;
public:
	ChemicalLabParametersInitial(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(ChemicalLabTrial::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};
class ChemicalLabParametersResults : public LabParametersResults
{
	map<ChemicalLabTrialResults::value_type, LabParameter*> m_params;
public:
	ChemicalLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(ChemicalLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};
#define FRACTION_LAB_PARAM_INITIAL_MAP 1
struct fraction_lab_param
{
#if !USE_FRACTION_DIAMETERS_INTERVAL
	double fraction_diameter;
#endif
	double fraction_diameter_high;
	double fraction_diameter_low;
	int n_fractions;
	int i_fraction;
	LabParameter* lab_param;

	fraction_lab_param();
};
class FractionsLabParametersInitial : public LabParametersInitial
{
#if FRACTION_LAB_PARAM_INITIAL_MAP
	map<FractionsLabTrial::value_type, LabParameter*> m_params;
#endif
	vector<fraction_lab_param> m_fractions_content;
public:
	FractionsLabParametersInitial(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

#if FRACTION_LAB_PARAM_INITIAL_MAP
	LabParameter * FindLabParameter(FractionsLabTrial::value_type t);
#endif
	LabParameter * FindLabParameter(LabTrialValueType & vt);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};
class FractionsLabParametersResults : public LabParametersResults
{
	map<FractionsLabTrialResults::value_type, LabParameter*> m_params;
public:
	FractionsLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(FractionsLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};
#if USE_COMPR_PO_OTN_DEF	
class CompressionLabParametersResults1 : public LabParametersResults
{		
	bool every;
	map<CompressionLabTrialResults::value_type_1, LabParameter*> m_params;
public:
	CompressionLabParametersResults1(LabParameters * p, LabLayer * , bool );
	virtual void FillLabParameters();
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CompressionLabTrialResults::value_type_1 t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

#endif
class CompressionLabParametersResults2 : public LabParametersResults
{		
	bool every;
	map<CompressionLabTrialResults::value_type_2, LabParameter*> m_params;
public:
	CompressionLabParametersResults2(LabParameters * p, LabLayer * , bool);
	virtual void FillLabParameters();
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CompressionLabTrialResults::value_type_2 t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class CompressionLabParametersResults3 : public LabParametersResults
{		
	bool every;
	map<CompressionLabTrialResults::value_type_3, LabParameter*> m_params;
public:
	CompressionLabParametersResults3(LabParameters * p, LabLayer * , bool);
	virtual void FillLabParameters();
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CompressionLabTrialResults::value_type_3 t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

struct compression_lab_param
{
	double compression_pressure;
	CompressionLabTrial::type com_type;
	int n_compression_pressures;
	int i_compression_pressure;
	LabParameter* lab_param;
	bool zamachivanie;
};
class CompressionLabParametersInitial : public LabParametersInitial
{
	vector<compression_lab_param> m_absolute_deformations;
public:
	CompressionLabParametersInitial(LabParameters * p, LabLayer * );//{type = t;}
	virtual void FillLabParameters();
	virtual bool IsLabParam(const LabParam * p1);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);

	LabParameter * FindLabParameter(LabTrialValueType & vt);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class CompressionLabParametersResults : public LabParametersResults
{		
	map<CompressionLabTrialResults::value_type_0, LabParameter*> m_params;
public:
	CompressionLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CompressionLabTrialResults::value_type_0 t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};
class CutLabParametersResults_common : public LabParametersResults
{
	// по общей совокупности опытов
	map<CutLabTrialResults::value_type, LabParameter*> m_params;
public:
	CutLabParametersResults_common(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CutLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};
#define CUT_LAB_PARAM_INITIAL_MAP 0
struct cut_lab_param
{
	double cut_pressure;
	CutLabTrial::type cut_type;
	int n_cut_pressures;
	int i_cut_pressure;
	LabParameter* lab_param;
};
class CutLabParametersInitial : public LabParametersInitial
{
	friend class LabLayer;
#if CUT_LAB_PARAM_INITIAL_MAP
	map<CutLabTrial::value_type, LabParameter*> m_params;
#endif
	vector<cut_lab_param> m_cut_resistance;
public:
	CutLabParametersInitial(LabParameters * p, LabLayer * );//{type = t;}
	virtual void FillLabParameters();
	virtual bool IsLabParam(const LabParam * p1);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);
#if CUT_LAB_PARAM_INITIAL_MAP
	LabParameter * FindLabParameter(CutLabTrial::value_type t);
#endif
	LabParameter * FindLabParameter(LabTrialValueType & vt);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class CutLabParametersResults : public LabParametersResults
{
	map<CutLabTrialResults::value_type, LabParameter*> m_params;
public:
	CutLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CutLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class PressingLabParametersInitial : public LabParametersInitial
{
	map<PressingLabTrial::value_type, LabParameter*> m_params;
public:
	PressingLabParametersInitial(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(PressingLabTrial::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class PressingLabParametersResults : public LabParametersResults
{
	map<PressingLabTrialResults::value_type, LabParameter*> m_params;
public:
	PressingLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(PressingLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class FiltrationLabParametersInitial : public LabParametersInitial
{
	map<FiltrationLabTrial::value_type, LabParameter*> m_params;
public:
	FiltrationLabParametersInitial(LabParameters * p, LabLayer * );//{type = t;}
	virtual void FillLabParameters();
	virtual void AddInitialParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(FiltrationLabTrial::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};

class FiltrationLabParametersResults : public LabParametersResults
{
	map<FiltrationLabTrialResults::value_type, LabParameter*> m_params;
public:
	FiltrationLabParametersResults(LabParameters * p, LabLayer * );
	virtual void FillLabParameters();
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(FiltrationLabTrialResults::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};



class PhysicalLabParameters : public LabParameters
{
public:
	PhysicalLabParameters(LabLayer *);
};

class ChemicalLabParameters : public LabParameters
{
public:
	ChemicalLabParameters(LabLayer *);
};
class FractionsLabParameters : public LabParameters
{
public:
	FractionsLabParameters(LabLayer *);
};
#define USE_COMPR_PO_OTN_DEF 0
class CompressionLabParameters : public LabParameters
{
	friend struct LabTrialValueType;
	friend class CompressionLabParameters3;

	friend class LabLayer;
	friend class CompressionLabParametersInitial;
	friend class CompressionLabParametersResults;
	friend class CompressionLabTrialResults;
	friend class CompressionLabTrialResults3;
	friend struct CompressionValueType;
protected:
	bool have_compression_3_parent;
	CompressionLabTrial::type type;
#if USE_COMPR_PO_OTN_DEF
	CompressionLabParametersResults1 * parameters_results1_every;
	CompressionLabParametersResults1 * parameters_results1_common;
#endif
	CompressionLabParametersResults2 * parameters_results2_every;
	CompressionLabParametersResults2 * parameters_results2_common;
	CompressionLabParametersResults3 * parameters_results3_every;
	CompressionLabParametersResults3 * parameters_results3_common;
public:
	CompressionLabParameters(CompressionLabTrial::type t, LabLayer *, bool have_parent);//{type = t;}
	virtual void FillLabParameters();
	virtual bool IsLabParam(const LabParam * p1);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);

	virtual void GetChecked(vector<LabTrialValueType> & vvt);

	bool Is_Used_Result_Parameter(int n_compression_value_type, int vt, bool every, LabTrialValueType & Vt);


};

class CompressionLabParametersResult_tri : public LabParametersResults
{		
	bool every;
	map<CompressionLabTrialResults3::value_type, LabParameter*> m_params;
public:
	CompressionLabParametersResult_tri(LabParameters * p, LabLayer * , bool);
	virtual void FillLabParameters();
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void AddResultParams_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual bool IsLabParam(const LabParam * p1);
	LabParameter * FindLabParameter(CompressionLabTrialResults3::value_type t);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);

	virtual void GetCheckedVirtual(vector<LabTrialValueType> & vvt, LabTrial::indication t, bool is_result);
};



class CompressionLabParameters3 : public LabParameters
{
public:
	CompressionLabParameters params_nature;
	CompressionLabParameters params_task;
	CompressionLabParameters params_shrinkage;
	CompressionLabParametersResult_tri params_tri;

	CompressionLabParameters3(LabLayer *);

	bool GetInitialCheckedLabParam()
	{
		if (params_nature.parameters_initial &&
			params_task.parameters_initial &&
			params_shrinkage.parameters_initial
			)
		{
			return 
				params_nature.parameters_initial->GetCheckedLabParam() || 
				params_task.parameters_initial->GetCheckedLabParam() || 
				params_shrinkage.parameters_initial->GetCheckedLabParam(); 
		}
		return false;
	}

	bool GetResultsCheckedLabParam()
	{
		if (params_nature.parameters_results &&
			params_task.parameters_results &&
			params_shrinkage.parameters_results
			)
		{
			return 
				params_nature.parameters_results->GetCheckedLabParam() || 
				params_task.parameters_results->GetCheckedLabParam() || 
				params_shrinkage.parameters_results->GetCheckedLabParam(); 
		}
		return false;
	}
#if USE_COMPR_PO_OTN_DEF
	bool GetResult1CommonCheckedLabParam()
	{
		if (params_nature.parameters_results1_common &&
			params_task.parameters_results1_common &&
			params_shrinkage.parameters_results1_common
			)
		{
			return 
				params_nature.parameters_results1_common->GetCheckedLabParam() || 
				params_task.parameters_results1_common->GetCheckedLabParam() || 
				params_shrinkage.parameters_results1_common->GetCheckedLabParam(); 
		}
		return false;
	}
	bool GetResult1EveryCheckedLabParam()
	{
		if (params_nature.parameters_results1_every &&
			params_task.parameters_results1_every &&
			params_shrinkage.parameters_results1_every
			)
		{
			return 
				params_nature.parameters_results1_every->GetCheckedLabParam() || 
				params_task.parameters_results1_every->GetCheckedLabParam() || 
				params_shrinkage.parameters_results1_every->GetCheckedLabParam(); 
		}
		return false;
	}
#endif
	bool GetResult2CommonCheckedLabParam()
	{
		if (params_nature.parameters_results2_common &&
			params_task.parameters_results2_common &&
			params_shrinkage.parameters_results2_common
			)
		{
			return 
				params_nature.parameters_results2_common->GetCheckedLabParam() || 
				params_task.parameters_results2_common->GetCheckedLabParam() || 
				params_shrinkage.parameters_results2_common->GetCheckedLabParam(); 
		}
		return false;
	}
	bool GetResult2EveryCheckedLabParam()
	{
		if (params_nature.parameters_results2_every &&
			params_task.parameters_results2_every &&
			params_shrinkage.parameters_results2_every
			)
		{
			return 
				params_nature.parameters_results2_every->GetCheckedLabParam() || 
				params_task.parameters_results2_every->GetCheckedLabParam() || 
				params_shrinkage.parameters_results2_every->GetCheckedLabParam(); 
		}
		return false;
	}
	bool GetResult3CommonCheckedLabParam()
	{
		if (params_nature.parameters_results3_common &&
			params_task.parameters_results3_common &&
			params_shrinkage.parameters_results3_common
			)
		{
			return 
				params_nature.parameters_results3_common->GetCheckedLabParam() || 
				params_task.parameters_results3_common->GetCheckedLabParam() || 
				params_shrinkage.parameters_results3_common->GetCheckedLabParam(); 
		}
		return false;
	}
	bool GetResult3EveryCheckedLabParam()
	{
		if (params_nature.parameters_results3_every &&
			params_task.parameters_results3_every &&
			params_shrinkage.parameters_results3_every
			)
		{
			return 
				params_nature.parameters_results3_every->GetCheckedLabParam() || 
				params_task.parameters_results3_every->GetCheckedLabParam() || 
				params_shrinkage.parameters_results3_every->GetCheckedLabParam(); 
		}
		return false;
	}
	virtual void FillLabParameters();
	virtual bool IsLabParam(const LabParam * p1);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);

	virtual void GetChecked(vector<LabTrialValueType> & vvt);
};

class CutLabParameters : public LabParameters
{
	friend class CutLabParametersInitial;
	friend class LabLayer;
	friend class CutLabParametersResults;
	friend class CutLabParametersResults_common;
	friend struct LabTrialValueType; 
protected:
	CutLabTrial::type type;
	CutLabParametersResults_common * parameters_results_common; // по общей совокупности опытов
public:
	CutLabParameters(CutLabTrial::type t, LabLayer *);//{type = t;}
	virtual void FillLabParameters();
	virtual bool IsLabParam(const LabParam * p1);
	virtual void ParamCheck(HWND hwndTV);
	virtual void ParamUnCheck(HWND hwndTV);
	virtual HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);

	virtual void GetChecked(vector<LabTrialValueType> & vvt);
};

class PressingLabParameters : public LabParameters
{
public:
	PressingLabParameters(LabLayer *);
};

class FiltrationLabParameters : public LabParameters
{
	FiltrationLabTrial::type type;
public:
	FiltrationLabTrial::type GetType(){return type;}
	FiltrationLabParameters(FiltrationLabTrial::type t, LabLayer *);//{type = t;}
};


class LabObject : public BaseLab
{
public:
	enum type
	{
		undefined = 0,
		laboratory_number,
		laboratory_layer
	};
	type lab_object_type;

	HTREEITEM parentTreeItem_LabObject;
	HTREEITEM myTreeItem_LabObject;
	
	bool m_bChecked_LabObject;
	bool m_bExpanded_LabObject; // for objectLists

	LabObject()
	{
		lab_object_type = LabObject::type::undefined;

		parentTreeItem_LabObject = NULL;
		myTreeItem_LabObject = NULL;
		
		m_bChecked_LabObject = true;
		m_bExpanded_LabObject = false; // for objectLists
	}



	virtual void FillContextMenu(HMENU& hMenu) = 0;
	void CreateContextMenu(HWND hWnd, LPARAM lParam);
	void CreateMyPopupMenu(HWND hWnd);

    virtual void SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY);

	virtual void SaveAs() = 0;

	virtual void DestroyContextWindow() = 0;

};

class SoilDescription
{
public:
	SoilDescription();
	virtual ~SoilDescription();

	LabNumber * lab_number;

	long lab_n;
	// определяем тип грунта
	CGround::ground_type m_ground_type;
	// или на основе числа платичности
	trial_t_value plasticity_index;
	trial_t_value fluidity_index_nature;
	trial_t_value fluidity_index_water_saturated;

	PhysicalLabTrialResults::Consistencia m_Consistencia_nature;
	PhysicalLabTrialResults::Consistencia m_Consistencia_water_saturated;

	/*void GetGroundTypeByPlasticityIndex()
	{
		if (		
			// на основе числа платичности (доли ед.) 
			plasticity_index.f)
		{
			// число пластичности						
			// определяем тип грунта
			m_ground_type = DefineGroundType(plasticity_index.v);

			switch (t)
			{
			case CGround::ground_type::SandyLoam:
				{
					if (fluidity_index_nature.f)
						this->m_Consistencia_nature = 
						Define_SandyLoam_Consistencia(fluidity_index_nature.v);
					if (fluidity_index_water_saturated.f)
						this->m_Consistencia_water_saturated = 
						Define_SandyLoam_Consistencia(fluidity_index_water_saturated.v);
				}
				break;
			case CGround::ground_type::Loam:
			case CGround::ground_type::Clay:
				{
					if (fluidity_index_nature.f)
						this->m_Consistencia_nature = 
						Define_ClayAndLoam_Consistencia(fluidity_index_nature.v);
					if (fluidity_index_water_saturated.f)
						this->m_Consistencia_water_saturated = 
						Define_ClayAndLoam_Consistencia(fluidity_index_water_saturated.v);
				}
				break;
			}
		}
		//else
		//{
		//	m_ground_type = CGround::ground_type::Sand;
		//}
	}*/


	// или на основе грансостава
		
	FractionsLabTrialResults::SandSoilsClass m_sand_soil_class;
	trial_t_value m_minimum_krupnosti_chastic, m_soderzhanie_chastic;

	FractionsLabTrialResults::ClaySoilsClass m_clay_soil_class;
	trial_t_value m_clay_frac_content;//m_soderzhanie_glinistyh_chastic;
	trial_t_value m_pyl_frac_content;// содержание пылеватой фракции;

	// Коэффициент неоднородности
	trial_t_value d_60;
	trial_t_value d_10;
	trial_t_value C_u;
	FractionsLabTrialResults::Neodnorodnost m_neodnorodnost;

	/*
	if (this->C_u < 3.0)
	{
		this->m_neodnorodnost = Neodnorodnost::odnorodnyj;
	}
	else
	{
		this->m_neodnorodnost = Neodnorodnost::neodnorodnyj;
	}
	*/

	//коэффициент пористости
	trial_t_value e;



	//степень влажности 
	trial_t_value S;
	PhysicalLabTrialResults::SandVlazhnost m_sand_vlazhnost;
	/*void GetSandVlaznost()
	{
		if (S < 0.5)
		{
			this->m_vlazhnost = PhysicalLabTrialResults::Vlazhnost::malovlazhnyj;
		}
		else if (0.5 <= S && S < 0.8)
		{
			this->m_vlazhnost = PhysicalLabTrialResults::Vlazhnost::vlazhnyj;
		}
		else
		{
			this->m_vlazhnost = PhysicalLabTrialResults::Vlazhnost::nasyschennyj_vodoj;
		}
	}
*/

	trial_t_value organic;
	//double v = 
	//	(chem_lab_trial->vegetable_remains_content.f ? chem_lab_trial->vegetable_remains_content.v : 0.0) + 
	//	(chem_lab_trial->organic_matters.f ? chem_lab_trial->organic_matters.v : 0.0);
	ChemicalLabTrialResults::Zatorfovannost	m_zatorfovannost;

	trial_t_value nachalnoe_prosadochnoe_davlenie;	
	CompressionLabTrialResults3::Prosadochnost m_prosadochnost;

	trial_t_value					svobodnoe_otnositelnoe_nabuhanie;
	trial_t_value					davlenie_nabuhania;
	CompressionLabTrialResults3::Nabuhanie m_nabuhanie;
	

	// Срез
	trial_t_value c;
	trial_t_value fi;
	trial_t_value tgfi;

	//// это в естественном состоянии
	//компрессия
	double def_module_01_02_pressure_interval[2];
	trial_t_value compression_module_e_in_01_02_interval;
	trial_t_value deformation_module_e_in_01_02_interval;

	double def_module_defined_pressure_interval[2];
	trial_t_value compression_module_e_in_defined_interval;
	trial_t_value deformation_module_e_in_defined_interval;

	// гурвич
	trial_t_value gurvich_Kp;

	double gurvich_shtamp_deformation_module_01_02_pressure_interval[2];
	trial_t_value gurvich_shtamp_deformation_module_in_01_02_interval;
	trial_t_value gurvich_shtamp_deformation_module_in_01_02_interval_Kp;

	double gurvich_shtamp_deformation_module_defined_pressure_interval[2];
	trial_t_value gurvich_shtamp_deformation_module_in_defined_interval;
	trial_t_value gurvich_shtamp_deformation_module_in_defined_interval_Kp;

	// добавить также компрессию и гурвич в водонасыщенном состоянии

	// стат.зондирование
	trial_t_value pck;
	trial_t_value pcb;
	trial_t_value zond_type;

	string GetSoilDescription(bool from_db);
};
class LabExperiment;
class LabNumber : public LabObject
{
	friend void PrintfPropE(CompressionLabTrialResults * res, vector<fmtstr> & text);
	static LabTrial::indication SetParam(long id_param, double val, PhysicalLabTrial * physical_trial, ChemicalLabTrial * chemical_trial, FractionsLabTrial * fractions_trial);
	LabLayer * lab_layer;
	friend class project;
	map<long, PropValue> m_prop_values;
	Zriz zriz;
	Compress compress;
	GranVyprob gran_vyprob;

public:
	virtual void DestroyContextWindow();

	long zond_type;
	trial_value pck;
	trial_value pcb;

	StatZond m_stat_zond;
	void AddStZond(
		long npp, long typgr,
		double h, double q0, double f0, 
		double dh, double fsr, 
		unsigned char bStat,
		long id_ige, double pck
		);
	void AddPtStZond(
		long id_ust,
		double glyb,
		const char * ust_name,
		long typ_zond, long n_shema,
		double Kg, double Kf, double Bg, double Bf, double shtanga_d
		);
	void ApplyStZond();

	virtual void SaveAs();
	int LabNumber::SaveLabInputFileLine(FILE * stream, char* szBuff, int & type_line, 
		Laboratory * m_laboratory, LabLayer * m_lablayer, LabExperiment *& m_lab_experiment, LabTrial *& m_lab_trial);
	bool LabNumber::SaveAsLabInputFile(char *file);
	void AddPrGrunt(long id_obj, long id_kt, const char * kt_name, long kt_idtyp, long id_prob, double depth,
		long lab_n, long id_kodprob, long id_gr, const char * soil_name, const char * grunt_name, long id_ige);

	void AddProp(long id_vyprob, long id_param, const char * param_name, double val);
	bool ApplyParams();
	bool HaveEnoughFor_e0(long id_compress_vyprob);
	long GetFizMehVyprobForCompress(long id_compress_vyprob, long id_kolca);
	long GetFizMehVyprobForCut(long id_cut_vyprob, long id_kolca);
	const char * GetPhysicalVyprobString(long id_phys_vyprob);


	void AddZriz0(long id_vyprob, long id_kolca, long id_phys_vyprob,
		double h, double d, double dh_po_upl,
		double m_kolca,
		double m_grunta,
		double m_grunta_zamoch,
		double m_grunta_posle_uplot,
		double m_grunta_posle,
		double m_grunta_vysush);
	void AddZriz_tbl(long id_vyprob, long id_kolca, double sigma, double tau, double w_do, double ro_do, double w_po_upl, double ro_po_upl, double w_after, double ro_after, unsigned char bStat);
	void AddZriz(long id_vyprob, long id_hid, long id_shema, long id_stan, double tgfi, double c, double d, double h, unsigned char bStat);
	bool ApplyZriz(int nCutItem);

	void AddCompress(long id_vyprob, 
		double sigma, double dh1, double dh2, unsigned char voda, unsigned char bStat);
	void AddCilce0(long id_vyprob, long id_kolca, long id_phys_vyprob,
		double h, double d,
		double m_kolca,
		double m_grunta,
		double m_grunta_zamoch,
		double m_grunta_posle,
		double m_grunta_vysush);
	void AddCompress(long id_vyprob,
		double h, double d, 
		double es_l1, double es_r1, double es_l2, double es_r2,
		double nju, double nju_z,
		double m01, double E1, double m02, double E2,
		double m01v, double E1v, double m02v, double E2v,
		unsigned char id_method, unsigned char bStat, unsigned char bStatV);

	long GetCompressVyprobMaxID();
	long GetCutVyprobMaxID();
	
	bool ApplyCompress(bool use_compression3, int nCompItem);
	bool ApplyCompress_3(int nCompItem);
	bool ApplyCompress_1();

	int GetCompressType(int nCompItem);


	bool AddGranular(long id_gran, const char * gran_name, double val);
	void ApplyGranular();



	LabNumber(LabLayer * lablayer);
	~LabNumber(){}

	const LabLayer * GetLabLayer(){return lab_layer;}


protected:
#if USE_LAB_TRIALS_VECTOR
	vector<LabTrial*> lab_trials;
#else
	map<LabTrial::indication, LabTrial*> lab_trials;
#endif

#if USE_LAB_TRIALS_VECTOR
	LabTrial * CreateNewLabTrial(LabTrial::indication t, long id_vyprob);
	LabTrial * AddNewLabTrial(LabTrial::indication t, LabTrial * lab_trial, long id_vyprob);
#else
	LabTrial * CreateNewLabTrial(LabTrial::indication t);
	LabTrial * AddNewLabTrial(LabTrial::indication t, LabTrial * lab_trial);
#endif

public:
#if USE_LAB_TRIALS_VECTOR
	LabTrial * FindLabTrial(LabTrial::indication t, long id_vyprob);
	LabTrial * AddNewLabTrial(LabTrial::indication t, long id_vyprob);
#else
	LabTrial * FindLabTrial(LabTrial::indication t);
	LabTrial * AddNewLabTrial(LabTrial::indication t);
#endif
public:
	// лабораторный идентификационный номер, 
	string ID;
	// наименование выработки, 
	string s_mine_working_type;
	enum mine_working_type
	{
		undefined	= 0,
		well		= 1,
		hole		= 2,
		tsz			= 3,
		tpg			= 4
	};
	mine_working_type m_mine_working_type;
	void ParseMineWorkingType();

	const char * MineWorkingTypeToStringRus(mine_working_type t);

// содержим номер выработки в char кодировке
#define CHAR_MINE_WORKING_NUMBER 1
	// номер выработки,
	string mine_working_number;
	long lab_n;
	long kt_idtyp;
	// глубина пробы, 
	double depth;
	long id_kodprob;
	long id_gr;

	long id_obj;		
	long id_kt; // ID комплексной точки
	long id_prob;
	string soil_name;// из WenGeo - исходя из id_gr
	string grunt_name;// Сгенерированное имя на основе свойств
	long id_ige;

	string GetSoilDescription(bool from_db);
	bool get_soil_description_from_db;

	SoilDescription GetSoilDescription();
	CGround::ground_type LabNumber::GetGroundType(
		FractionsLabTrialResults::SandSoilsClass & ssc,
		FractionsLabTrialResults::ClaySoilsClass & csc);




	// признаки испытания
	map <LabTrial::indication, LabTrial::indication> trial_indications;
	bool is_trial_indication_1;
	bool is_trial_indication_2;
	bool is_trial_indication_3;
	bool is_trial_indication_4;
	bool is_trial_indication_5;
	bool is_trial_indication_6;
	bool is_trial_indication_7;
	bool is_trial_indication_8;
	bool is_trial_indication_9;
	bool is_trial_indication_10;
	bool is_trial_indication_11;
	bool is_trial_indication_12;
	bool ParseTrialIndications();

	void CalcProperties();
	void PrintfProperties();

	bool GetValue(LabTrialValueType & vt, trial_got_value & v);

	virtual void Properties();
	void PrintfProperties(vector<fmtstr> & text);
	void PrintfProperties(vector<LabData> & labdata);
	void ReCalcProperties(bool labnumber_recalc_e_log_interp);

	HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void FillContextMenu(HMENU& hMenu);

	static bool context_with_results;

	void PropSave(bool context_with_plot);
	void Passport();
	void Passport(const char * fn);
#if USE_LAB_TRIALS_VECTOR
	void PassportCut(const char * fn, long id_vyprob, int cut_passport_type);
	void PassportCompress(const char * fn, long id_vyprob, int compression_passport_type, bool otnosit_def_on_graph);
#else
	void PassportCut(const char * fn);
	void PassportCompress(const char * fn);
#endif
	void PassportGranular(const char * fn, int granular_passport_type);

};


class LabExperiment
{
	LabLayer * lab_layer;
public:

	void Init();
	LabExperiment();
	~LabExperiment();

	void SetLabLayer(LabLayer * ll)	{lab_layer = ll;}

	enum type 
	{
		undefined_lab_experiment	= 0,
		compression					= 10, 
		cut							= 20, 
		filtration					= 30, 
		pressing					= 40, 
		fractions					= 50
	};
	static const char * LabExperimentTypeToString(LabExperiment::type t);
	LabExperiment::type exp_type;

	void * operator new  (size_t size){return ::operator new  (size);}
	void operator delete  (void * p)  {return ::operator delete  (p);}

	static void * operator new  (size_t size, LabExperiment::type);
	static void operator delete  (void * p, LabExperiment::type);

	virtual void PrintfProperties() = 0;
};
#define USE_LAB_LAYER_HOOP 0
class CompressionLabExperiment : public LabExperiment
{
public:

	void Init();
	CompressionLabExperiment();
	~CompressionLabExperiment();
				
	// тип прибора,	
	string apparatus_type;
#if USE_LAB_LAYER_HOOP
	// диаметр кольца, 
	double hoop_diameter;
	// высота кольца, 
	double hoop_height;

#else
	bool lab_layer_hoop_defined;
	// диаметр кольца, 
	double lab_layer_hoop_diameter;
	// высота кольца, 
	double lab_layer_hoop_height;
#endif
	// метод испытания, 
	string trial_method;
	// заданная влажность, 
	string task_moisture;
	double task_moisture_v;
	bool ParseTaskMoisture();
	// заданная плотность
	double task_density;


#if !USE_LAB_LAYER_PRESSURES
	// количество давлений в природном состоянии, 
	int lab_layer_n_pressures_in_nature_condition;
	// количество давлений в заданном состоянии, 
	int lab_layer_n_pressures_in_task_condition;
	// количество давлений на усадку
	int lab_layer_n_pressures_on_shrinkage;

	// массив давлений природного состояния
	double * lab_layer_pressures_in_nature_condition;
	// массив давлений заданного состояния
	double * lab_layer_pressures_in_task_condition;
	// массив давлений на усадку
	double * lab_layer_pressures_on_shrinkage;
#else
	// количество давлений в природном состоянии, 
	int n_pressures_in_nature_condition;
	// количество давлений в заданном состоянии, 
	int n_pressures_in_task_condition;
	// количество давлений на усадку
	int n_pressures_on_shrinkage;

	// массив давлений природного состояния
	double * pressures_in_nature_condition;
	// массив давлений заданного состояния
	double * pressures_in_task_condition;
	// массив давлений на усадку
	double * pressures_on_shrinkage;
#endif

	void PrintfProperties();

};
class CutLabExperiment : public LabExperiment
{
public:
	void Init();
	CutLabExperiment();
	~CutLabExperiment();
				
	// тип прибора,	
	string apparatus_type;
	// диаметр кольца, 
	double hoop_diameter;
	// высота кольца, 
	double hoop_height;
	// метод испытания, 
	string trial_method;
	// заданная влажность, 
	string task_moisture;
	double task_moisture_v;
	bool ParseTaskMoisture();
	// заданная плотность
	double task_density;
#if !USE_LAB_LAYER_CUT_PRESSURES
	// количество давлений в природном состоянии, 
	int lab_layer_n_pressures_in_nature_condition;
	// количество давлений в заданном состоянии, 
	int lab_layer_n_pressures_in_task_condition;

	// массив давлений природного состояния
	double * lab_layer_pressures_in_nature_condition;
	// массив давлений заданного состояния
	double * lab_layer_pressures_in_task_condition;
#else
	// количество давлений в природном состоянии, 
	int n_pressures_in_nature_condition;
	// количество давлений в заданном состоянии, 
	int n_pressures_in_task_condition;

	// массив давлений природного состояния
	double * pressures_in_nature_condition;
	// массив давлений заданного состояния
	double * pressures_in_task_condition;
#endif

	void PrintfProperties();
};
class FiltrationLabExperiment : public LabExperiment
{
public:
	void Init();
	FiltrationLabExperiment();
	~FiltrationLabExperiment();

	// тип прибора,	
	string apparatus_type;
	// диаметр трубки , 
	double tube_diameter;
	// длина трубки, 
	double tube_lenght;
	// высота напора жидкости, 
	double liquid_force_height;
	// заданная плотность
	double task_density;
	// давления
	double pressures[3];

	void PrintfProperties();
};
class PressingLabExperiment : public LabExperiment
{
public:
	void Init();
	PressingLabExperiment();
	~PressingLabExperiment();

	// тип прибора,	
	string apparatus_type;
	// заданная влажность, 
	string task_moisture;
	double task_moisture_v;
	bool ParseTaskMoisture();
	// плотность невыветрелого грунта
	double density;

	void PrintfProperties();
};
#define USE_LAB_LAYER_FRACTIONS 0

class FractionsLabExperiment : public LabExperiment
{
public:
	void Init();
	FractionsLabExperiment();
	~FractionsLabExperiment();

#if !USE_LAB_LAYER_FRACTIONS
	// количество фракций, 
	int lab_layer_n_fractions;
	// массив диаметров фракций
#if USE_FRACTION_DIAMETERS_INTERVAL
	fraction_diameters_interval * lab_layer_fractions_diameters;
#else
	double * lab_layer_fractions_diameters;
#endif
#else
	// количество фракций, 
	int n_fractions;
	// массив диаметров фракций
#if USE_FRACTION_DIAMETERS_INTERVAL
	fraction_diameters_interval * fractions_diameters;
#else
	double * fractions_diameters;
#endif
#endif

	void PrintfProperties();
};
class Laboratory;

//typedef void labCallbackFunc(LabTrialValueType & vt, int i, vector<double> & vv);
//typedef labCallbackFunc * labCallback;
//typedef void (*labCallback)(LabTrialValueType & vt, int i, vector<double> & vv);
//typedef labCallbackFunc * labCallback;
struct MinSqLinearStatParameters
{
	double x_min;
	double x_max;
	double x_mean;
	double SumCentralSqX;
	double G;
	double D;
	double lambda;
	double Kx_min;
	double Kx_max;
};
class LabNormatives;
class LabLayer : public LabObject, public LabParam
{
	friend class SurfDoc;
	friend class EngineerGeoElement;
	friend struct LabTrialValueType;
	friend class CDlgPCK2Fiz;
	LabNormatives * lab_normatives;
	Laboratory * p_laboratory;
public:
		
	CompressionLogInterpolation e_log_interp;
	CompressionLogInterpolation e_log_interp_95;
	double e_p, e_p_95;
	double a_p, a_p_95;
	double E_p, E_p_95;
	bool to_calc_e_log_interp;

	virtual void SaveAs();

	bool check_draw;
	LabLayer(Laboratory * p_lab, const char * fn);
	~LabLayer();
	const Laboratory * GetLaboratory(){return p_laboratory;}
	bool IsLabObject(const LabObject * p1);
	bool IsLabParam(const LabParam * p1);

	virtual void DestroyContextWindow();

	void ParamCheck(HWND hwndTV);
	void ParamUnCheck(HWND hwndTV);

	void GetChecked(vector<LabTrialValueType> & vvt);
// содержим номер слоя в char кодировке
#define CHAR_LAYER_NUMBER_ID 1 
	long id_ige;// из базы данных
	string ID;
	string layer_number;
	string filename;
	// схема испытания
	string experiments_scheme;
	bool is_compression;// компрессия
	bool is_cut; // срез
	bool is_filtracion;// фильтрация
	bool is_pressing;// одноосное сжатие
	bool is_fractions;// диаметры фракций (песок)
	bool ParseExperimentsScheme();
	void FormExperimentsScheme();
	void PrintfProperties();
	vector<LabNumber*> lab_numbers;
protected:
	map<LabExperiment::type, LabExperiment*> lab_experiments;
	map<LabTrial::indication, LabParameters*> lab_parameters;

	LabParameter * lab_parameter_depth;

	LabParameters * CreateNewLabParameters(LabTrial::indication t);
	LabParameters * AddNewLabParameters(LabTrial::indication t, LabParameters * lab_param);

	LabExperiment * CreateNewLabExperiment(LabExperiment::type t);
	LabExperiment * AddNewLabExperiment(LabExperiment::type t, LabExperiment * lab_experiment);
public:
	LabParameters * FindLabParameters(LabTrial::indication t);
	LabParameters * AddNewLabParameters(LabTrial::indication t);

	LabExperiment * FindLabExperiment(LabExperiment::type t);
	LabExperiment * AddNewLabExperiment(LabExperiment::type t);

	LabNumber * AddNewLabNumber();
	LabNumber * FindLabNumber(const char * id);
	LabNumber * FindLabNumber(long id_kt, long id_prob);

	HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	virtual void FillContextMenu(HMENU& hMenu);
	void FillContextMenuParamVirtual(HMENU& hMenu);

	bool LabLayer::CalcNormative(LabTrialValueType & vt, 
		vector<trial_got_value> & vv, 
		int & n, // количество определений
		trial_value & vn, // нормативное значение
		double & S, // среднеквадратическое отклонение 
		double & V  // коэффициент вариации
		);

	bool LabLayer::CalcNormative(
		vector<trial_got_value> & vv, 
		int & norm, // нормативное значение
		int & n
		);	

	void ApplyParams();
	void ApplyZriz();
	void ApplyCompress(bool use_compression3);
	void ApplyGranular();
	void ParseTrialIndications();

			
	bool excluded_list_filled;

	void Normatives(vector<fmtstr> * text, vector<LabData> * labdata);
	void CalcProperties();
	void ReCalcProperties(bool layer_recalc_e_log_interp, bool labnumber_recalc_e_log_interp);
	void CutNormatives_common(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
#if USE_COMPR_PO_OTN_DEF
	void CompressionNormatives_common_y(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
#endif
	void CompressionNormatives_common_e(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	void CompressionNormatives_common_gurvich(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
#if USE_COMPR_PO_OTN_DEF	
	void Compression3_Normatives_common_y(int ntrial, LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
#endif
	void Compression3_Normatives_common_e(int ntrial, LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	void Compression3_Normatives_common_gurvich(int ntrial, LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	
#if USE_COMPR_PO_OTN_DEF	
	void Compression3_Normatives_common_y(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
#endif
	void Compression3_Normatives_common_e(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	void Compression3_Normatives_common_gurvich(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	
#if USE_COMPR_PO_OTN_DEF	
	void Compression3Normatives_common_y(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
#endif
	void Compression3Normatives_common_e(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	void Compression3Normatives_common_gurvich(LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata);
	
	bool MinSqLinearStat(LabTrialValueType & vt, vector<x_compression> & x, vector<trial_got_value> & y, bool donot_shift, trial_value & a0, trial_value & a1, int & m, trial_value & Sy, MinSqLinearStatParameters & param);

		
	void FillLabParameters();


	void PrintLabNumbers(vector<fmtstr> * text);
	void PrintNormativeHeaders(vector<fmtstr> * text);

	bool GetValueCallBack(LabTrialValueType & vt, vector<fmtstr> * text);
	bool CorrelationCoefficient(LabTrialValueType & vt1, LabTrialValueType & vt2, vector<fmtstr> * text, vector<LabData> * labdata);
	bool PrintAndNormativesCallBack(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata);
	bool PrintCallBack(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata);
	bool NormativesCallBack(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata);
	bool NormativesCallBack_body(int sign, bool got, vector<trial_got_value> &vv, LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata);
	bool EvalCallBack(bool (LabLayer::*CallBack)(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata), LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata);
	bool EvalNormative2(LabTrialValueType & vt, vector<fmtstr> * text, vector<LabData> * labdata);

	virtual void PropSave(bool context_with_plot);

	virtual void Passport()
	{
		Passport_normatives(0);
		Passport_normatives(1);
		Passport_normatives(2);
		Passport_normatives(3);
		Passport_chastnye();
	}
	void Passport_normatives(int type);
	void Passport_chastnye();
	void Passport_normatives(const char * fn);
	void Passport_chastnye_or_normatives(int flag, const char * fn);

	bool HaveNormative(LabTrial::indication ind);
	void PassportFiz(const char * fn);
	void PassportComp0(const char * fn, bool every);// normative list as Fiz
	void PassportComp(const char * fn);// 
	void PassportZriz(const char * fn);// нормативные значения прочностных х-к (среза) включая все состояния
	void PassportZriz(const char * fn, LabTrial::indication ind);// нормативные значения прочностных х-к (среза) включая одно состояние
	void PassportZriz2(const char * fn, LabTrial::indication ind);
	virtual void PrintfProperties(vector<fmtstr> & text);
	virtual void PrintfProperties(vector<LabData> & labdata);
	virtual void Properties();

	void GetSoilDescription(vector<SoilDescription> & vsd);

	void HowManyIDs(LabTrialValueType & vt, map<long,long> &freq);


	static bool context_with_lab_number_trial_list;
	static bool context_with_normatives;
	static bool context_with_normatives_by_all_experiences;
	static bool context_with_korrelation;

	double deformation_module_defined_pressure_interval[2];
	double deformation_module_defined_pressure;
#if USE_COMPR_PO_OTN_DEF

	//y
	// interval_type: 0 - no, 1 - 01 - 02, 2 - defined
	bool calc_E(int interval_type, int ntrial, 
		LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata,
		const char * s, 
		int type,
		bool use_text, 
		bool use_text2, 
		vector<x_compression> & vx,
		vector<trial_got_value> & vy, double * pressure_interval);

	void FillCompressionData1(CompressionLabTrial * compression_lab_trial, 
		char * s,
		vector<x_compression> & vx,
		vector<trial_got_value> & vy,

		double * def_module_01_02_pressure_interval,
		vector<x_compression> & vx_01_02_interval,
		vector<trial_got_value> & vy_in_01_02_interval,

		double * def_module_defined_pressure_interval,
		vector<x_compression> & vx_defined_interval,
		vector<trial_got_value> & vy_in_defined_interval
		);
#endif
	//e
	bool calc_E2(int interval_type, int ntrial, 
		LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata,
		const char * s, 
		int type,
		bool use_text, 
		bool use_text2, 
		vector<x_compression> & vx,
		vector<trial_got_value> & ve, double * pressure_interval);

	void FillCompressionData2(CompressionLabTrial * compression_lab_trial, 
		double e0,
		char * s,
		vector<x_compression> & vx,
		vector<trial_got_value> & ve,

		double * def_module_01_02_pressure_interval,
		vector<x_compression> & vx_01_02_interval,
		vector<trial_got_value> & ve_in_01_02_interval,

		double * def_module_defined_pressure_interval,
		vector<x_compression> & vx_defined_interval,
		vector<trial_got_value> & ve_in_defined_interval
		);

	//e log interp
	bool calc_E2_(
		LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata,
		const char * s, 
		int type,
		bool use_text, 
		bool use_text2, 
		vector<x_compression> & vx,
		vector<trial_got_value> & ve, double * pressure_interval);

	//gurvich shtamp
	bool calc_E3(int interval_type, int ntrial, 
		LabTrial::indication t, vector<fmtstr> *& text, vector<LabData> * labdata,
		const char * s, 
		int type,
		bool use_text, 
		bool use_text2, 
		vector<x_compression> & vx,
		vector<trial_got_value> & vy, double * pressure_interval);

	void FillCompressionData3(CompressionLabTrial * compression_lab_trial, 
		char * s,
		vector<x_compression> & vx,
		vector<trial_got_value> & vy,

		double * def_module_01_02_pressure_interval,
		vector<x_compression> & vx_01_02_interval,
		vector<trial_got_value> & vy_in_01_02_interval,

		double * def_module_defined_pressure_interval,
		vector<x_compression> & vx_defined_interval,
		vector<trial_got_value> & vy_in_defined_interval
		);

	static bool DefModuleNewRaschotnMethod;
};

//here was struct LabTrialValueType;


struct normative_value
{
	int n;
	trial_value v_n;
	trial_value v_85;
	trial_value v_95;
	trial_value v_99;
	trial_value v_S;  // среднеквадратическое отклонение
	trial_value v_V;  // коэффициент вариации
	trial_value ro_85;// показатель точности
	trial_value ro_95;// показатель точности
	trial_value ro_99;// показатель точности

	trial_value gamma_g_tgfi_c;
	trial_value sigma_min;
	trial_value sigma_max;



	normative_value(int N, 
		trial_value vn, 
		trial_value v85, 
		trial_value v95, 
		trial_value v99,
		trial_value S = trial_value(),   // среднеквадратическое отклонение 
		trial_value V = trial_value(),   // коэффициент вариации
		trial_value ro85 = trial_value(),// показатель точности среднего значения
		trial_value ro95 = trial_value(),
		trial_value ro99 = trial_value(),
		trial_value gamma = trial_value(),
		trial_value sig_min = trial_value(),
		trial_value sig_max = trial_value()
		) 
	{
		n = N;
		v_n = vn;
		v_85 = v85;
		v_95 = v95;
		v_99 = v99;

		v_S = S;
		v_V = V;

		ro_85 = ro85;
		ro_95 = ro95;
		ro_99 = ro99;

		gamma_g_tgfi_c = gamma;
		sigma_min = sig_min;
		sigma_max = sig_max;
	}

	normative_value& operator=(const normative_value& ob)
	{
		n  = ob.n;
		v_n  = ob.v_n;
		v_85 = ob.v_85;
		v_95 = ob.v_95;
		v_99 = ob.v_99;

		v_S = ob.v_S;
		v_V = ob.v_V;

		ro_85 = ob.ro_85;
		ro_95 = ob.ro_95;
		ro_99 = ob.ro_99;

		gamma_g_tgfi_c = ob.gamma_g_tgfi_c;
		sigma_min = ob.sigma_min;
		sigma_max = ob.sigma_max;

		return *this;
	}
};


class LabNormatives
{
public:
	enum type
	{
		normative,
		raschotn_85,
		raschotn_95,
		raschotn_99,
		srednekvadratic_otklonenie,
		variacii_koefficient
	};
	static const char * TypeToString(LabNormatives::type t);
	map<LabTrialValueType, normative_value> values;
};

struct excluded_lab_trial
{
	string lab_layer_number;
	string labnumer_ID;
	LabNumber::mine_working_type m_mine_working_type;
	string mine_working_number;
	// глубина пробы, 
	double depth;
	// тип данных для определения вида характеристики грунта	 
	LabTrialValueType vt;
	double v;
	short * pf;
	Trial * trial;
	bool check_included;
	excluded_lab_trial()
	{
		check_included = false;
		m_mine_working_type = LabNumber::mine_working_type::undefined;
		pf = NULL;
		trial = NULL;
	}
};
#if LABORATORY_WITH_SURFDOC
class SurfDoc;
#endif
class Laboratory
{
public:
	long id_obj;
	// наименование объекта
	string object_name;
		
	// наименование договора
	string contract;
private:
#if LABORATORY_WITH_SURFDOC
	SurfDoc * m_doc;
#else
	void * m_doc;
#endif

	LabLayer * m_lablayer;
	LabExperiment * m_lab_experiment;
	LabNumber * m_lab_number;
	LabTrial * m_lab_trial;

	LabObject * selected_lab_object;
	int selected_lab_object_x;
	int selected_lab_object_y;

	void TestSelectedLabObject();

public:
	HWND hwndTV;
	HWND hwndTV2;

#if LABORATORY_WITH_SURFDOC
	Laboratory(SurfDoc * doc, double _pressure_interval_01_02_0);
	const SurfDoc * GetDoc() {return m_doc;}
#else
	Laboratory(void * doc, double _pressure_interval_01_02_0);
	void * GetDoc() {return m_doc;}
#endif

	static void Init(double _pressure_interval_01_02_0);

	bool IsLabObject(const LabObject * p1);
	bool IsLabParam(const LabParam * p1);

	void ParamCheck(HWND hwndTV);
	void ParamUnCheck(HWND hwndTV);

	HTREEITEM AddParam_ToTree(HWND hwndTV, HTREEITEM h1);
	HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1);
	mutable HWND hContextWindow; 

	void ApplyParams();
	void ApplyZriz();
	void ApplyCompress(bool use_compression3);
	void ApplyGranular();

	void ParseTrialIndications();

	void ReCalcProperties(bool layer_recalc_e_log_interp, bool labnumber_recalc_e_log_interp);
	void ReCreateContextWindow();
	void ReDrawContextWindow();

	static tagPOINT	context_window_pt;	// Текущая позиция context window

	bool SelectLabObject(long & x, long & y, const LabObject * p1, HWND hWndParent);
	void DestroyContextWindow();
	bool SelectLabObject(const LabObject * p1);

	bool SelectLabParam(const LabParam * p1, HWND hwndTV, HTREEITEM hTreeItem);
	bool SelectLabObject(const LabObject * p1, HWND hwndTV, HTREEITEM hTreeItem);

	bool LabWellElementProp();
	bool LabWellElementPropSave();
	bool LabWellElementPassport();
	bool LabWellElementPropFont(int wmId);
	bool LabWellElementPropPlotHeight();
	bool LabGurvichYSecondDerivativeLimit();
	bool LabCompressionESecondDerivativeLimit();
	bool LabCompressionPressure();
	bool LabCompressionPressureInterval();
	bool LabWaterSaturatedPartOfFullWaterCapacity();

	vector<LabLayer *> m_layers;
	// загрузка данных лабораторных анализов
	bool ReadLabInputFile(char *file);
	int ParseLabInputFileLine(char* szBuff, int & type_line, const char * fn, bool use_compression3);

	static vector<excluded_lab_trial> excluded_trials;		
	void UpdateExcluded();
	void Normatives();
	void FillLabParameters();

	LabNumber * FindLabNumber(const char * id);
	LabNumber * FindLabNumber(long id_kt, long id_prob);
	LabLayer * FindLabLayer(long id_ige);


	static bool context_with_plot;
	static string FormsDir;


};

struct error_of_add_new_well_colomn_laboratory_analizes
{
	string lab_layer_number;
	string labnumer_ID;
	LabNumber::mine_working_type m_mine_working_type;
	string mine_working_number;
	// глубина пробы, 
	double depth;
};

enum alpha_value
{
	av_085 = 1,
	av_090, 
	av_095,
	av_0975,
	av_098, 
	av_099
};

bool Get_t_alpha( alpha_value av, int K, double & t_alpha);
