#pragma once

class SoilDescription;
struct trial_t_value;
class SoilDescriptionPtr
{
public:
	SoilDescription * psd;
	SoilDescriptionPtr(SoilDescription * sd);
	bool operator<(const SoilDescriptionPtr& rhs);
	enum compare_mode
	{
		by_ground_type = 0,
		by_plasticity_index,
		by_fluidity_index_nature,
		by_fluidity_index_water_saturated,
		by_m_Consistencia_nature,
		by_m_Consistencia_water_saturated,

		by_e,

		by_m_minimum_krupnosti_chastic,
		by_m_soderzhanie_chastic,
		by_m_sand_soil_class,
		by_m_clay_soil_class,
		by_m_clay_frac_content,
		by_m_pyl_frac_content,

		by_d_60,
		by_d_10,
		by_C_u,
		by_m_neodnorodnost,

		by_S,
		by_m_sand_vlazhnost,

		by_organic,
		by_m_zatorfovannost,

		by_nachalnoe_prosadochnoe_davlenie,
		by_m_prosadochnost, 

		by_svobodnoe_otnositelnoe_nabuhanie,
		by_davlenie_nabuhania,
		by_m_nabuhanie,

		// Срез
		by_c,
		by_fi,
		by_tgfi,

		//компрессия
		by_compression_module_e_in_01_02_interval,
		by_deformation_module_e_in_01_02_interval,

		by_compression_module_e_in_defined_interval,
		by_deformation_module_e_in_defined_interval,

		// гурвич
		by_gurvich_Kp,

		by_gurvich_shtamp_deformation_module_in_01_02_interval,
		by_gurvich_shtamp_deformation_module_in_01_02_interval_Kp,

		by_gurvich_shtamp_deformation_module_in_defined_interval,
		by_gurvich_shtamp_deformation_module_in_defined_interval_Kp,

		// стат.зондирование
		by_pck,
		by_pcb,
		by_zond_type

	};
	static SoilDescriptionPtr::compare_mode s_compare_mode;
	static SoilDescriptionPtr::compare_mode s_calculation_mode;
	trial_t_value & GetValue();
	static const char * CompareModeToString(compare_mode cm);
	static bool Is_Trial_T_Value(compare_mode cm);

};
inline SoilDescriptionPtr::compare_mode operator++( SoilDescriptionPtr::compare_mode &rs, int )
{
   return rs = (SoilDescriptionPtr::compare_mode)(rs + 1);
}