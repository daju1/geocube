#include <windows.h>
#include "SoilDescriptionPtr.h"

#include <map>
using namespace std;
#include "lab.h"

SoilDescriptionPtr::SoilDescriptionPtr(SoilDescription * sd)
{
	psd = sd;
}
	
enum SoilDescriptionPtr::compare_mode 
SoilDescriptionPtr::s_compare_mode = SoilDescriptionPtr::compare_mode::by_ground_type;
enum SoilDescriptionPtr::compare_mode 
SoilDescriptionPtr::s_calculation_mode = SoilDescriptionPtr::compare_mode::by_plasticity_index;
			

bool Less(trial_t_value & this_v, trial_t_value & rhs_v)
{
	if (this_v.f && rhs_v.f)
		return this_v.v < rhs_v.v;
	else
	{
		if (this_v.f)
			return false;
		if (rhs_v.f)
			return true;
		return true;
	}
}

bool SoilDescriptionPtr::operator<(const SoilDescriptionPtr& rhs)
{
	switch(SoilDescriptionPtr::s_compare_mode)
	{
	case SoilDescriptionPtr::compare_mode::by_ground_type:
		{
			return psd->m_ground_type < rhs.psd->m_ground_type;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_plasticity_index:
		{
			if (psd->plasticity_index.f && rhs.psd->plasticity_index.f)
				return psd->plasticity_index.v < rhs.psd->plasticity_index.v;
			else
			{
				if (psd->plasticity_index.f)
					return false;
				if (rhs.psd->plasticity_index.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_nature:
		{
			if (psd->fluidity_index_nature.f && rhs.psd->fluidity_index_nature.f)
				return psd->fluidity_index_nature.v < rhs.psd->fluidity_index_nature.v;
			else
			{
				if (psd->fluidity_index_nature.f)
					return false;
				if (rhs.psd->fluidity_index_nature.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_water_saturated:
		{
			if (psd->fluidity_index_water_saturated.f && rhs.psd->fluidity_index_water_saturated.f)
				return psd->fluidity_index_water_saturated.v < rhs.psd->fluidity_index_water_saturated.v;
			else
			{
				if (psd->fluidity_index_water_saturated.f)
					return false;
				if (rhs.psd->fluidity_index_water_saturated.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_nature:
		{
			return psd->m_Consistencia_nature < rhs.psd->m_Consistencia_nature;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_water_saturated:
		{
			return psd->m_Consistencia_water_saturated < rhs.psd->m_Consistencia_water_saturated;
		}
		break;

	case SoilDescriptionPtr::compare_mode::by_e:
		{
			if (psd->e.f && rhs.psd->e.f)
				return psd->e.v < rhs.psd->e.v;
			else
			{
				if (psd->e.f)
					return false;
				if (rhs.psd->e.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_minimum_krupnosti_chastic:
		{
			if (psd->m_minimum_krupnosti_chastic.f && rhs.psd->m_minimum_krupnosti_chastic.f)
				return psd->m_minimum_krupnosti_chastic.v < rhs.psd->m_minimum_krupnosti_chastic.v;
			else
			{
				if (psd->m_minimum_krupnosti_chastic.f)
					return false;
				if (rhs.psd->m_minimum_krupnosti_chastic.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_soderzhanie_chastic:
		{
			if (psd->m_soderzhanie_chastic.f && rhs.psd->m_soderzhanie_chastic.f)
				return psd->m_soderzhanie_chastic.v < rhs.psd->m_soderzhanie_chastic.v;
			else
			{
				if (psd->m_soderzhanie_chastic.f)
					return false;
				if (rhs.psd->m_soderzhanie_chastic.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_sand_soil_class:
		{
			return psd->m_sand_soil_class < rhs.psd->m_sand_soil_class;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_soil_class:
		{
			return psd->m_clay_soil_class < rhs.psd->m_clay_soil_class;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_60:
		{
			if (psd->d_60.f && rhs.psd->d_60.f)
				return psd->d_60.v < rhs.psd->d_60.v;
			else
			{
				if (psd->d_60.f)
					return false;
				if (rhs.psd->d_60.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_10:
		{
			if (psd->d_10.f && rhs.psd->d_10.f)
				return psd->d_10.v < rhs.psd->d_10.v;
			else
			{
				if (psd->d_10.f)
					return false;
				if (rhs.psd->d_10.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_C_u:
		{
			if (psd->C_u.f && rhs.psd->C_u.f)
				return psd->C_u.v < rhs.psd->C_u.v;
			else
			{
				if (psd->C_u.f)
					return false;
				if (rhs.psd->C_u.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_frac_content:
		{
			if (psd->m_clay_frac_content.f && rhs.psd->m_clay_frac_content.f)
				return psd->m_clay_frac_content.v < rhs.psd->m_clay_frac_content.v;
			else
			{
				if (psd->m_clay_frac_content.f)
					return false;
				if (rhs.psd->m_clay_frac_content.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_pyl_frac_content:
		{
			if (psd->m_pyl_frac_content.f && rhs.psd->m_pyl_frac_content.f)
				return psd->m_pyl_frac_content.v < rhs.psd->m_pyl_frac_content.v;
			else
			{
				if (psd->m_pyl_frac_content.f)
					return false;
				if (rhs.psd->m_pyl_frac_content.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_neodnorodnost:
		{
			return psd->m_neodnorodnost < rhs.psd->m_neodnorodnost;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_S:
		{
			if (psd->S.f && rhs.psd->S.f)
				return psd->S.v < rhs.psd->S.v;
			else
			{
				if (psd->S.f)
					return false;
				if (rhs.psd->S.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_sand_vlazhnost:
		{
			return psd->m_sand_vlazhnost < rhs.psd->m_sand_vlazhnost;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_organic:
		{
			if (psd->organic.f && rhs.psd->organic.f)
				return psd->organic.v < rhs.psd->organic.v;
			else
			{
				if (psd->organic.f)
					return false;
				if (rhs.psd->organic.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_zatorfovannost:
		{
			return psd->m_zatorfovannost < rhs.psd->m_zatorfovannost;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_nachalnoe_prosadochnoe_davlenie:
		{
			if (psd->nachalnoe_prosadochnoe_davlenie.f && rhs.psd->nachalnoe_prosadochnoe_davlenie.f)
				return psd->nachalnoe_prosadochnoe_davlenie.v < rhs.psd->nachalnoe_prosadochnoe_davlenie.v;
			else
			{
				if (psd->nachalnoe_prosadochnoe_davlenie.f)
					return false;
				if (rhs.psd->nachalnoe_prosadochnoe_davlenie.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_prosadochnost:
		{
			return psd->m_prosadochnost < rhs.psd->m_prosadochnost;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_svobodnoe_otnositelnoe_nabuhanie:
		{
			if (psd->svobodnoe_otnositelnoe_nabuhanie.f && rhs.psd->svobodnoe_otnositelnoe_nabuhanie.f)
				return psd->svobodnoe_otnositelnoe_nabuhanie.v < rhs.psd->svobodnoe_otnositelnoe_nabuhanie.v;
			else
			{
				if (psd->svobodnoe_otnositelnoe_nabuhanie.f)
					return false;
				if (rhs.psd->svobodnoe_otnositelnoe_nabuhanie.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_davlenie_nabuhania:
		{
			if (psd->davlenie_nabuhania.f && rhs.psd->davlenie_nabuhania.f)
				return psd->davlenie_nabuhania.v < rhs.psd->davlenie_nabuhania.v;
			else
			{
				if (psd->davlenie_nabuhania.f)
					return false;
				if (rhs.psd->davlenie_nabuhania.f)
					return true;
				return true;
			}
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_nabuhanie:
		{
			return psd->m_nabuhanie < rhs.psd->m_nabuhanie;
		}
		break;
		// Срез
	case SoilDescriptionPtr::compare_mode::by_c:
		{
			return Less(this->psd->c, rhs.psd->c);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fi:
		{
			//return psd->fi;
			return Less(this->psd->fi, rhs.psd->fi);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_tgfi:
		{
			//return psd->tgfi;
			return Less(this->psd->tgfi, rhs.psd->tgfi);
		}
		break;
		//компрессия
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_01_02_interval:
		{
			//return psd->compression_module_e_in_01_02_interval;
			return Less(
				this->psd->compression_module_e_in_01_02_interval, 
				rhs.psd->compression_module_e_in_01_02_interval);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_01_02_interval:
		{
			//return psd->deformation_module_e_in_01_02_interval;
			return Less(
				this->psd->deformation_module_e_in_01_02_interval, 
				rhs.psd->deformation_module_e_in_01_02_interval);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_defined_interval:
		{
			//return psd->compression_module_e_in_defined_interval;
			return Less(
				this->psd->compression_module_e_in_defined_interval, 
				rhs.psd->compression_module_e_in_defined_interval);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_defined_interval:
		{
			//return psd->deformation_module_e_in_defined_interval;
			return Less(
				this->psd->deformation_module_e_in_defined_interval, 
				rhs.psd->deformation_module_e_in_defined_interval);
		}
		break;
		// гурвич
	case SoilDescriptionPtr::compare_mode::by_gurvich_Kp:
		{
			//return psd->gurvich_Kp;
			return Less(this->psd->gurvich_Kp, rhs.psd->gurvich_Kp);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval:
		{
			//return psd->gurvich_shtamp_deformation_module_in_01_02_interval;
			return Less(
				this->psd->gurvich_shtamp_deformation_module_in_01_02_interval, 
				rhs.psd->gurvich_shtamp_deformation_module_in_01_02_interval);
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval_Kp:
		{
			//return psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp;
			return Less(
				this->psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp, 
				rhs.psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp);
			/*if (psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.f && rhs.psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.f)
				return psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.v < rhs.psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.v;
			else
			{
				if (psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.f)
					return false;
				if (rhs.psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp.f)
					return true;
				return true;
			}*/
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval:
		{
			//return psd->gurvich_shtamp_deformation_module_in_defined_interval;
			return Less(
				this->psd->gurvich_shtamp_deformation_module_in_defined_interval, 
				rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval);
			/*if (psd->gurvich_shtamp_deformation_module_in_defined_interval.f && rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval.f)
				return psd->gurvich_shtamp_deformation_module_in_defined_interval.v < rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval.v;
			else
			{
				if (psd->gurvich_shtamp_deformation_module_in_defined_interval.f)
					return false;
				if (rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval.f)
					return true;
				return true;
			}*/
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval_Kp:
		{
			//return psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp;
			return Less(
				this->psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp, 
				rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp);
			/*if (psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.f && rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.f)
				return psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.v < rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.v;
			else
			{
				if (psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.f)
					return false;
				if (rhs.psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp.f)
					return true;
				return true;
			}*/
		}
		break;
		// стат зонд
	case SoilDescriptionPtr::compare_mode::by_pck:
		{
			return Less(this->psd->pck, rhs.psd->pck);
			/*if (psd->pck.f && rhs.psd->pck.f)
				return psd->pck.v < rhs.psd->pck.v;
			else
			{
				if (psd->pck.f)
					return false;
				if (rhs.psd->pck.f)
					return true;
				return true;
			}*/
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_pcb:
		{
			return Less(this->psd->pcb, rhs.psd->pcb);
			/*if (psd->pcb.f && rhs.psd->pcb.f)
				return psd->pcb.v < rhs.psd->pcb.v;
			else
			{
				if (psd->pcb.f)
					return false;
				if (rhs.psd->pcb.f)
					return true;
				return true;
			}*/
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_zond_type:
		{
			return psd->zond_type < rhs.psd->zond_type;
		}
		break;
	}
}

trial_t_value & SoilDescriptionPtr::GetValue()
{
	switch(SoilDescriptionPtr::s_calculation_mode)
	{
	/*case SoilDescriptionPtr::compare_mode::by_ground_type:
		{
			return psd->m_ground_type;
		}
		break;*/
	case SoilDescriptionPtr::compare_mode::by_plasticity_index:
		{
			return psd->plasticity_index;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_nature:
		{
			return psd->fluidity_index_nature;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_water_saturated:
		{
			return psd->fluidity_index_water_saturated;
		}
		break;
/*	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_nature:
		{
			return psd->m_Consistencia_nature;
		}
		break;*/
/*	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_water_saturated:
		{
			return psd->m_Consistencia_water_saturated;
		}
		break;*/

	case SoilDescriptionPtr::compare_mode::by_e:
		{
			return psd->e;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_minimum_krupnosti_chastic:
		{
			return psd->m_minimum_krupnosti_chastic;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_soderzhanie_chastic:
		{
			return psd->m_soderzhanie_chastic;
		}
		break;
/*	
	case SoilDescriptionPtr::compare_mode::by_m_sand_soil_class:
		{
			return psd->m_sand_soil_class;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_soil_class:
		{
			return psd->m_clay_soil_class;
		}
		break;
		
		*/
	case SoilDescriptionPtr::compare_mode::by_d_60:
		{
			return psd->d_60;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_10:
		{
			return psd->d_10;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_C_u:
		{
			return psd->C_u;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_frac_content:
		{
			return psd->m_clay_frac_content;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_pyl_frac_content:
		{
			return psd->m_pyl_frac_content;
		}
		break;
/*	case SoilDescriptionPtr::compare_mode::by_m_neodnorodnost:
		{
			return psd->m_neodnorodnost;
		}
		break;*/
	case SoilDescriptionPtr::compare_mode::by_S:
		{
			return psd->S;
		}
		break;
/*	case SoilDescriptionPtr::compare_mode::by_m_sand_vlazhnost:
		{
			return psd->m_sand_vlazhnost;
		}
		break;*/
	case SoilDescriptionPtr::compare_mode::by_organic:
		{
			return psd->organic;
		}
		break;
/*	case SoilDescriptionPtr::compare_mode::by_m_zatorfovannost:
		{
			return psd->m_zatorfovannost;
		}
		break;*/
	case SoilDescriptionPtr::compare_mode::by_nachalnoe_prosadochnoe_davlenie:
		{
			return psd->nachalnoe_prosadochnoe_davlenie;
		}
		break;
/*	case SoilDescriptionPtr::compare_mode::by_m_prosadochnost:
		{
			return psd->m_prosadochnost;
		}
		break;*/
	case SoilDescriptionPtr::compare_mode::by_svobodnoe_otnositelnoe_nabuhanie:
		{
			return psd->svobodnoe_otnositelnoe_nabuhanie;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_davlenie_nabuhania:
		{
			return psd->davlenie_nabuhania;
		}
		break;
/*	case SoilDescriptionPtr::compare_mode::by_m_nabuhanie:
		{
			return psd->m_nabuhanie;
		}
		break;*/
		// Срез
	case SoilDescriptionPtr::compare_mode::by_c:
		{
			return psd->c;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fi:
		{
			return psd->fi;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_tgfi:
		{
			return psd->tgfi;
		}
		break;
		//компрессия
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_01_02_interval:
		{
			return psd->compression_module_e_in_01_02_interval;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_01_02_interval:
		{
			return psd->deformation_module_e_in_01_02_interval;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_defined_interval:
		{
			return psd->compression_module_e_in_defined_interval;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_defined_interval:
		{
			return psd->deformation_module_e_in_defined_interval;
		}
		break;
		// гурвич
	case SoilDescriptionPtr::compare_mode::by_gurvich_Kp:
		{
			return psd->gurvich_Kp;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval:
		{
			return psd->gurvich_shtamp_deformation_module_in_01_02_interval;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval_Kp:
		{
			return psd->gurvich_shtamp_deformation_module_in_01_02_interval_Kp;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval:
		{
			return psd->gurvich_shtamp_deformation_module_in_defined_interval;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval_Kp:
		{
			return psd->gurvich_shtamp_deformation_module_in_defined_interval_Kp;
		}
		break;
		// стат зонд
	case SoilDescriptionPtr::compare_mode::by_pck:
		{
			return psd->pck;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_pcb:
		{
			return psd->pcb;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_zond_type:
		{
			return psd->zond_type;
		}
		break;
	}
}

bool SoilDescriptionPtr::Is_Trial_T_Value(compare_mode cm)
{
	switch(cm)
	{
	case SoilDescriptionPtr::compare_mode::by_ground_type:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_plasticity_index:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_nature:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_water_saturated:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_nature:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_water_saturated:
		{
			return false;
		}
		break;

	case SoilDescriptionPtr::compare_mode::by_e:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_minimum_krupnosti_chastic:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_soderzhanie_chastic:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_sand_soil_class:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_soil_class:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_60:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_10:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_C_u:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_frac_content:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_pyl_frac_content:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_neodnorodnost:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_S:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_sand_vlazhnost:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_organic:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_zatorfovannost:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_nachalnoe_prosadochnoe_davlenie:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_prosadochnost:
		{
			return false;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_svobodnoe_otnositelnoe_nabuhanie:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_davlenie_nabuhania:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_nabuhanie:
		{
			return false;
		}
		break;
		// Срез
	case SoilDescriptionPtr::compare_mode::by_c:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fi:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_tgfi:
		{
			return true;
		}
		break;
		//компрессия
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_01_02_interval:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_01_02_interval:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_defined_interval:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_defined_interval:
		{
			return true;
		}
		break;
		// гурвич
	case SoilDescriptionPtr::compare_mode::by_gurvich_Kp:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval_Kp:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval_Kp:
		{
			return true;
		}
		break;
		// стат зонд
	case SoilDescriptionPtr::compare_mode::by_pck:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_pcb:
		{
			return true;
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_zond_type:
		{
			return true;
		}
		break;
	}
	return false;
}

const char * SoilDescriptionPtr::CompareModeToString(compare_mode cm)
{
	switch(cm)
	{
	case SoilDescriptionPtr::compare_mode::by_ground_type:
		{
			return "тип грунта";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_plasticity_index:
		{
			return "число пластичности";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_nature:
		{
			return "показатель текучести в природном состоянии";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fluidity_index_water_saturated:
		{
			return "показатель текучести в водонасыщенном состоянии";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_nature:
		{
			return "консистенция в природном состоянии";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_Consistencia_water_saturated:
		{
			return "консистенция в водонасыщенном состоянии";
		}
		break;

	case SoilDescriptionPtr::compare_mode::by_e:
		{
			return "коэфф. пористости";
			return "e";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_minimum_krupnosti_chastic:
		{
			return "???минимум крупности частиц";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_soderzhanie_chastic:
		{
			return "содержание частиц";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_sand_soil_class:
		{
			return "класс песчаных и крупнообломочных грунтов";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_soil_class:
		{
			return "класс глинистых грунтов по содержанию глинистых частиц";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_60:
		{
			return "диам.частиц,мельче кот.в грунте сод.60% по массе";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_d_10:
		{
			return "диам.частиц,мельче кот.в грунте сод.10% по массе";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_C_u:
		{
			return "Коэффициент неоднородности";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_neodnorodnost:
		{
			return "класс неоднородности песков";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_clay_frac_content:
		{
			return "содержание глинистой фракции";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_pyl_frac_content:
		{
			return "содержание пылеватой фракции";
		}
		break;

	case SoilDescriptionPtr::compare_mode::by_S:
		{
			return "степень влажности";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_sand_vlazhnost:
		{
			return "класс влажности песчаного грунта";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_organic:
		{
			return "содержание органики";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_zatorfovannost:
		{
			return "заторфованность";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_nachalnoe_prosadochnoe_davlenie:
		{
			return "начаьное просадочное давление";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_prosadochnost:
		{
			return "просадочность";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_svobodnoe_otnositelnoe_nabuhanie:
		{
			return "свободное относительное набухание";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_davlenie_nabuhania:
		{
			return "давление набухания";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_m_nabuhanie:
		{
			return "набухание";
		}
		break;
		// Срез
	case SoilDescriptionPtr::compare_mode::by_c:
		{
			return "удельное сцепление";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_fi:
		{
			return "угол внутреннего трения";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_tgfi:
		{
			return "тангенс угла внутреннего трения";
		}
		break;
		//компрессия
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_01_02_interval:
		{
			return "компрессионный модуль в интервале 01 02";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_01_02_interval:
		{
			return "модуль деформации в интервале 01 02";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_compression_module_e_in_defined_interval:
		{
			return "компрессионный модуль в интервале defined";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_deformation_module_e_in_defined_interval:
		{
			return "модуль деформации в интервале defined";
		}
		break;
		// гурвич
	case SoilDescriptionPtr::compare_mode::by_gurvich_Kp:
		{
			return "коэффицинт Kp по Гурвичу";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval:
		{
			return "модуль деформации в интервале 01 02 прогн. штампа по Гурвичу";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_01_02_interval_Kp:
		{
			return "модуль деформации * Kp в интервале 01 02 прогн. штампа по Гурвичу";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval:
		{
			return "модуль деформации в интервале defined прогн. штампа по Гурвичу";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_gurvich_shtamp_deformation_module_in_defined_interval_Kp:
		{
			return "модуль деформации * Kp в интервале defined прогн. штампа по Гурвичу";
		}
		break;
		// стат зонд
	case SoilDescriptionPtr::compare_mode::by_pck:
		{
			return "pck";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_pcb:
		{
			return "pcb";
		}
		break;
	case SoilDescriptionPtr::compare_mode::by_zond_type:
		{
			return "тип зонда";
		}
		break;
	}
}
