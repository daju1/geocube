// utExcel.cpp: implementation of the ExcelCut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelCut.h"

#include "labView.h"
#include "SetObject.h"
#include "SetZriz0.h"
#include "SetZriz.h"
#include "SetZriz_tbl.h"
#include "SetProbGr.h"
#include "SetKT.h"
#include "SetFizMeh.h"

#include "DlgRepeatings.h"

#include <math.h>

#include <map>
using namespace std;
#include "../../laboratory/src/lab.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelCut::ExcelCut()
{

	use_compute_for_save = true;
}

ExcelCut::~ExcelCut()
{

}
void ExcelCut::InitExt()
{
	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			ext					= "cut";
			xl_filter_name		= "Срез";
			xl_form				= "Cut3Zhurnal2";
		}
		break;
	case 3:
		{
			ext					= "cut";
			xl_filter_name		= "Срез";
			xl_form				= "Cut3Zhurnal2";
		}
		break;
	case 6:
		{
			ext					= "cut6";
			xl_filter_name		= "Срез";
			xl_form				= "Cut6Zhurnal2";
		}
		break;
	}

}
bool ExcelCut::virFill()
{
	try
	{
		int nObItem = this->m_lab_view->GetObjectItem();
		if (nObItem < 0)
		{
			AfxMessageBox("Не выбран объект");
			return false;
		}


		bool add_cut_from_db = true;
		bool add_compress_from_db = false;
		int nCutItem = 0;
		int nCompItem = 0;
		bool add_stat_zond_from_db = false;
		LabNumber * lab_number = this->m_lab_view->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
		if (!lab_number) return false;	

		/*if (!lab_number->HaveEnoughFor_e0(-1))
		{
			AfxMessageBox(
				"Для расчёта коэффициента пористости в выбранной пробе грунта недостаточно данных\n"
				"Необходимо определитть плотность грунта, плотность частиц грунта и влажность");
			return false;
		}*/

		long lab_n = lab_number->lab_n;
		ExcelRange_SetValue(m_excel, "LAB_N", COleVariant(lab_n));
		ExcelRange_SetValue(m_excel, "LAB_N_2", COleVariant(lab_n));
		if (CDlgRepeatings::s_repeatings == 6)
			ExcelRange_SetValue(m_excel, "LAB_N_3", COleVariant(lab_n));





		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		ExcelRange_SetValue(m_excel, "CONTRACT", COleVariant(setObject.m_CONTRACT));
		ExcelRange_SetValue(m_excel, "CONTRACT_2", COleVariant(setObject.m_CONTRACT));
		if (CDlgRepeatings::s_repeatings == 6)
			ExcelRange_SetValue(m_excel, "CONTRACT_3", COleVariant(setObject.m_CONTRACT));
		
		ExcelRange_SetValue(m_excel, "OBJECT", COleVariant(setObject.m_NAZVA));
		ExcelRange_SetValue(m_excel, "OBJECT_2", COleVariant(setObject.m_NAZVA));
		if (CDlgRepeatings::s_repeatings == 6)
			ExcelRange_SetValue(m_excel, "OBJECT_3", COleVariant(setObject.m_NAZVA));

		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return false;

		long ID_KT = -1;
		long ID_PROB = -1;
		double H;
		CString GRUNT_NAME = "";
		if (!setProbGr.IsBOF()) 
		{
			setProbGr.MoveFirst( );
			while(!setProbGr.IsEOF()) 
			{
				if(lab_n == setProbGr.m_LAB_N)
				{
					ID_KT = setProbGr.m_ID_KT;
					ID_PROB = setProbGr.m_ID_PROB;
					H = setProbGr.m_H;
					GRUNT_NAME = setProbGr.m_GRUNT_NAME;
					break;
				}
				setProbGr.MoveNext(); // to validate record count
			}
		}

		if (ID_KT < 0)
		{
			CString s;
			s.Format("Не найдена выработка соответствующая лабораторному номеру %d", lab_n);
			AfxMessageBox(s);
		}
		if (ID_PROB < 0)
		{
			CString s;
			s.Format("Не найдена проба грунта соответствующая лабораторному номеру %d", lab_n);
			AfxMessageBox(s);
		}

		if (ID_KT < 0 || ID_PROB < 0)
			return false;

		ExcelRange_SetValue(m_excel, "GRUNT_NAME", COleVariant(GRUNT_NAME));

		ExcelRange_SetValue(m_excel, "H", COleVariant(H));
		ExcelRange_SetValue(m_excel, "H_2", COleVariant(H));
		if (CDlgRepeatings::s_repeatings == 6)
			ExcelRange_SetValue(m_excel, "H_3", COleVariant(H));

		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			if(!setKT.IsEOF()) 
			{
				ExcelRange_SetValue(m_excel, "KT", COleVariant(setKT.m_NAZVA));
				ExcelRange_SetValue(m_excel, "KT_2", COleVariant(setKT.m_NAZVA));
				if (CDlgRepeatings::s_repeatings == 6)
					ExcelRange_SetValue(m_excel, "KT_3", COleVariant(setKT.m_NAZVA));
			}
		}

		long id_cut_vyprob = lab_number ? lab_number->GetCutVyprobMaxID() + 1 : 1;
		//long ID_PHYS_VYPROB_0 = 2 * (ID_VYPROB - 1) + 2;

		double m_grunta[6], m_kolca[6], m_kolca_s_gruntom[6];
			
		
		char S[64];

		long nk = 3;
		if (CDlgRepeatings::s_repeatings == 6) 
			nk = 6;
#define TO_FILL_W_do_AND_RO_do 0
#if TO_FILL_W_do_AND_RO_do
		double ID_STAN;
		//1	Природної вологості	Естественная влажность
		//2	Водонасичений	Водонасыщенный	
		/*
		double ID_HID;
		//1	Швидкий	Быстрый
		//2	Прискорений	Ускоренный
		//3	Повільний	Медленный
		//4	Плашка по плашці	Плашка по плашке
		double ID_SHEMA;
		//1	Неконсолідовано-недреноване	Неконсолидированно-недренированное
		//2	Консолідовано-недреноване	Консолидированно-недренированное
		//3	Консолідовано-дреноване	Консолидированно-дренированное
		*/
		// ID_OBJ ID_KT ID_PROB ID_GRAN		

		if(!ExcelRange_GetValue(m_excel, "ID_STAN", ID_STAN))
		{	
			AfxMessageBox("Введите идентификатор состояния образца");
			return false;
		}
		switch(long(ID_STAN))
		{
		case 1:
			ExcelRange_SetValue(m_excel, "STAN", COleVariant("При естественной влажности"));
			break;
		case 2:
			ExcelRange_SetValue(m_excel, "STAN", COleVariant("В водонасыщенном состоянии"));
			break;
		}
#endif
		for (long ik = 0; ik < nk; ik++)
		{
			long id_kolca = ik + 1;
			//long ID_PHYS_VYPROB = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);

			SetZriz0 setZriz0(this->p_database);
			setZriz0.m_strFilter.Format(
				"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_KOLCA = %d", 
				ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
			if ( !setZriz0.Open(CRecordset::dynaset) )
				return false;

			if (!setZriz0.IsBOF()) 
			{
				setZriz0.MoveFirst( );
				if(!setZriz0.IsEOF()) 
				{						
					if (setZriz0.m_H)
						ExcelRange_SetValue(m_excel, "H_KOLCA", COleVariant(setZriz0.m_H));
					if (setZriz0.m_D)
						ExcelRange_SetValue(m_excel, "D_KOLCA", COleVariant(setZriz0.m_D));
					
					m_kolca[ik] = setZriz0.m_M_KOLCA;
					if (m_kolca[ik])
					{
						sprintf(S, "M_KOLCA_%d", id_kolca);
						ExcelRange_SetValue(m_excel, S, COleVariant(setZriz0.m_M_KOLCA));
						
						m_grunta[ik] = setZriz0.m_M_GRUNTA;
						if (m_grunta[ik])
						{
							sprintf(S, "M_GRUNTA_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(setZriz0.m_M_GRUNTA));

							m_kolca_s_gruntom[ik] = m_grunta[ik] + m_kolca[ik];
							sprintf(S, "M_KOLCA_S_GRUNTOM_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(m_kolca_s_gruntom[ik]));
						}

						if (setZriz0.m_M_GRUNTA_VYSUSH)
						{
							double m_kolca_s_gruntom_vysush_ik = setZriz0.m_M_GRUNTA_VYSUSH + m_kolca[ik];
							sprintf(S, "M_KOLCA_S_GRUNTOM_POSLE_VYSUSH_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(m_kolca_s_gruntom_vysush_ik));
							sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(setZriz0.m_M_GRUNTA_VYSUSH));
						}
					}			
				}
			}
		}



		
		double h_kolca, d_kolca;
		double s_kolca, v_kolca;
		if(ExcelRange_GetValue(m_excel, "H_KOLCA", h_kolca) 
			&& 
			ExcelRange_GetValue(m_excel, "D_KOLCA", d_kolca))
		{	
			h_kolca *= 10.;
			d_kolca *= 10.;

			s_kolca = 0.01 * 0.25 * PI * d_kolca * d_kolca;
			ExcelRange_SetValue(m_excel, "S_KOLCA", COleVariant(s_kolca));
			v_kolca = 0.1 * s_kolca * h_kolca;
			ExcelRange_SetValue(m_excel, "V_KOLCA", COleVariant(v_kolca));
		}
		else
		{
			CString s;
			s.Format("Высота и диаметр кольца для срезного испытания номер %d не указаны", id_cut_vyprob);
			AfxMessageBox(s);
			return false;
		}

		if (lab_number)
		{
			LabTrial * lab_trial_0 = lab_number->FindLabTrial(LabTrial::indication::physical, MEAN_PHYS_VYPROB);
			PhysicalLabTrial * phys_lab_trial_0 = dynamic_cast<PhysicalLabTrial *>(lab_trial_0);
			for (long ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;
				long ID_PHYS_VYPROB = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
				
				LabTrial * lab_trial_ik = lab_number->FindLabTrial(LabTrial::indication::physical, ID_PHYS_VYPROB);
				PhysicalLabTrial * phys_lab_trial_ik = dynamic_cast<PhysicalLabTrial *>(lab_trial_ik);
				
#if TO_FILL_W_do_AND_RO_do
				switch(long(ID_STAN))
				{
				case 1:
					{
						//ExcelRange_SetValue(m_excel, "STAN", COleVariant("При естественной влажности"));
						sprintf(S, "W_do_%d", id_kolca);
						if (phys_lab_trial_ik && phys_lab_trial_ik->moisture_of_nature_large_exchange.f)
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_of_nature_large_exchange.v));
						}
						else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_of_nature_large_exchange.f)
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_of_nature_large_exchange.v));
						}
						sprintf(S, "RO_do_%d", id_kolca);
						if (phys_lab_trial_ik && phys_lab_trial_ik->density_of_ground.f)
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->density_of_ground.v));
						}
						else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground.f)
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->density_of_ground.v));
						}
					}
					break;
				case 2:
					{
						//ExcelRange_SetValue(m_excel, "STAN", COleVariant("В водонасыщенном состоянии"));
						/*sprintf(S, "W_do_%d", id_kolca);
						bool by_kolco = false;
						if (phys_lab_trial_ik)
						{
							LabTrialResults * lab_trial_res = phys_lab_trial_ik->results;
							PhysicalLabTrialResults * phys_lab_trial_res = dynamic_cast<PhysicalLabTrialResults *>(lab_trial_res);
							if (phys_lab_trial_res && phys_lab_trial_res->w_water_saturated.f)
							{
								ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_res->w_water_saturated.v));
								by_kolco = true;
							}
						}
						if (!by_kolco && phys_lab_trial_0)
						{
							LabTrialResults * lab_trial_res = phys_lab_trial_0->results;
							PhysicalLabTrialResults * phys_lab_trial_res = dynamic_cast<PhysicalLabTrialResults *>(lab_trial_res);
							if (phys_lab_trial_res && phys_lab_trial_res->w_water_saturated.f)
							{
								ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_res->w_water_saturated.v));
							}
						}

						sprintf(S, "RO_do_%d", id_kolca);
						by_kolco = false;
						if (phys_lab_trial_ik)
						{
							LabTrialResults * lab_trial_res = phys_lab_trial_ik->results;
							PhysicalLabTrialResults * phys_lab_trial_res = dynamic_cast<PhysicalLabTrialResults *>(lab_trial_res);
							if (phys_lab_trial_res && phys_lab_trial_res->density_of_water_saturated_ground.f)
							{
								ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_res->density_of_water_saturated_ground.v));
								by_kolco = true;
							}
						}
						if (!by_kolco && phys_lab_trial_0)
						{
							LabTrialResults * lab_trial_res = phys_lab_trial_0->results;
							PhysicalLabTrialResults * phys_lab_trial_res = dynamic_cast<PhysicalLabTrialResults *>(lab_trial_res);
							if (phys_lab_trial_res && phys_lab_trial_res->density_of_water_saturated_ground.f)
							{
								ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_res->density_of_water_saturated_ground.v));
								by_kolco = true;
							}						
						}*/
					}
					break;
				}				
#endif


				sprintf(S, "W_%d", id_kolca);
				if (phys_lab_trial_ik && phys_lab_trial_ik->moisture_of_nature_large_exchange.f)
				{
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_of_nature_large_exchange.v));
				}
				else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_of_nature_large_exchange.f)
				{
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_of_nature_large_exchange.v));
				}
				sprintf(S, "RO_%d", id_kolca);
				if (phys_lab_trial_ik && phys_lab_trial_ik->density_of_ground.f)
				{
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->density_of_ground.v));
				}
				else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground.f)
				{
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->density_of_ground.v));
				}


				if (phys_lab_trial_ik && phys_lab_trial_ik->density_of_ground_particles.f)
				{
					sprintf(S, "ROs_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->density_of_ground_particles.v));
					sprintf(S, "ROs_do_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->density_of_ground_particles.v));
					sprintf(S, "ROs_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->density_of_ground_particles.v));
					sprintf(S, "ROs_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->density_of_ground_particles.v));
				}
				else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground_particles.f)
				{
					sprintf(S, "ROs_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
					sprintf(S, "ROs_do_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
					sprintf(S, "ROs_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
					sprintf(S, "ROs_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
				}

				if (phys_lab_trial_ik && phys_lab_trial_ik->moisture_on_fluidity_border.f)
				{
					sprintf(S, "WL_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_fluidity_border.v));
					sprintf(S, "WL_do_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_fluidity_border.v));
					sprintf(S, "WL_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_fluidity_border.v));
					sprintf(S, "WL_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_fluidity_border.v));
				}
				else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_on_fluidity_border.f)
				{
					sprintf(S, "WL_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_fluidity_border.v));
					sprintf(S, "WL_do_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_fluidity_border.v));
					sprintf(S, "WL_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_fluidity_border.v));
					sprintf(S, "WL_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_fluidity_border.v));
				}

				if (phys_lab_trial_ik && phys_lab_trial_ik->moisture_on_plasticity_border.f)
				{
					sprintf(S, "WP_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_plasticity_border.v));
					sprintf(S, "WP_do_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_plasticity_border.v));
					sprintf(S, "WP_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_plasticity_border.v));
					sprintf(S, "WP_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_ik->moisture_on_plasticity_border.v));
				}
				else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_on_plasticity_border.f)
				{
					sprintf(S, "WP_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_plasticity_border.v));
					sprintf(S, "WP_do_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_plasticity_border.v));
					sprintf(S, "WP_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_plasticity_border.v));
					sprintf(S, "WP_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(phys_lab_trial_0->moisture_on_plasticity_border.v));
				}
			}
		}

		/*LabTrial * lab_trial_f = lab_number->FindLabTrial(LabTrial::indication::fractions, -1);
		FractionsLabTrial * frac_lab_trial = dynamic_cast<FractionsLabTrial *>(lab_trial_f);
		if (frac_lab_trial)			
		{
			frac_lab_trial->FillZhurnal(m_excel, 37, 38);
		}*/
	}


    catch (CException* pe) {
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
		return false;
    }

	return true;
}


bool ExcelCut::virCompute(bool toSavetoDB)
{
	double digits_epsilon = 1e-8;
	char S[64];
	try
	{
		int nObItem = this->m_lab_view->GetObjectItem();
		if (nObItem < 0)
		{
			AfxMessageBox("Не выбран объект");
			return false;
		}

		bool add_cut_from_db = false;
		bool add_compress_from_db = false;
		int nCutItem = 0;
		int nCompItem = 0;
		bool add_stat_zond_from_db = false;
		LabNumber * lab_number = this->m_lab_view->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
		if (!lab_number) return false;	
		long lab_n = lab_number->lab_n;


		add_cut_from_db = true;
		nCutItem = 0;
		nCompItem = 0;
		add_stat_zond_from_db = false;
		LabNumber * lab_number2 = this->m_lab_view->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem , add_stat_zond_from_db);
		long id_cut_vyprob = lab_number2 ? lab_number2->GetCutVyprobMaxID() + 1 : 1;

		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;


		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return false;

		SetZriz setZriz(this->p_database);
		if ( !setZriz.Open(CRecordset::dynaset) )
			return false;

		SetZriz_tbl setZriz_tbl(this->p_database);
		if ( !setZriz_tbl.Open(CRecordset::dynaset) )
			return false;

		long ID_KT = -1;
		long ID_PROB = -1;

		double H;
		if (!setProbGr.IsBOF()) 
		{
			setProbGr.MoveFirst( );
			while(!setProbGr.IsEOF()) 
			{
				if(lab_n == setProbGr.m_LAB_N)
				{
					ID_KT = setProbGr.m_ID_KT;
					ID_PROB = setProbGr.m_ID_PROB;
					H = setProbGr.m_H;
					break;
				}
				setProbGr.MoveNext(); // to validate record count
			}
		}

		if (ID_KT < 0)
		{
			CString s;
			s.Format("Не найдена выработка соответствующая лабораторному номеру %d", lab_n);
			AfxMessageBox(s);
		}
		if (ID_PROB < 0)
		{
			CString s;
			s.Format("Не найдена проба грунта соответствующая лабораторному номеру %d", lab_n);
			AfxMessageBox(s);
		}

		if (ID_KT < 0 || ID_PROB < 0)
			return false;


		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			if(!setKT.IsEOF()) 
			{
				//ExcelRange_SetValue(m_excel, "KT", COleVariant(setKT.m_NAZVA));
			}
		}

		double d_kolca = 0.0, h_kolca = 0.0;
		double s_kolca = 0.0, v_kolca = 0.0;
		if(ExcelRange_GetValue(m_excel, "H_KOLCA", h_kolca) 
			&& 
			ExcelRange_GetValue(m_excel, "D_KOLCA", d_kolca))
		{	
			h_kolca *= 10.;
			d_kolca *= 10.;

			s_kolca = 0.01 * 0.25 * PI * d_kolca * d_kolca;
			ExcelRange_SetValue(m_excel, "S_KOLCA", COleVariant(s_kolca));
			v_kolca = 0.1 * s_kolca * h_kolca;
			ExcelRange_SetValue(m_excel, "V_KOLCA", COleVariant(v_kolca));
		}
		else
		{
			CString s;
			s.Format("Высота и диаметр кольца для срезного испытания номер %d не указаны", id_cut_vyprob);
			AfxMessageBox(s);
			return false;
		}

		long nk = 3;
		if (CDlgRepeatings::s_repeatings == 6) 
			nk = 6;

		double ID_STAN;
		//1	Природної вологості	Естественная влажность
		//2	Водонасичений	Водонасыщенный	
		double ID_HID;
		//1	Швидкий	Быстрый
		//2	Прискорений	Ускоренный
		//3	Повільний	Медленный
		//4	Плашка по плашці	Плашка по плашке
		double ID_SHEMA;
		//1	Неконсолідовано-недреноване	Неконсолидированно-недренированное
		//2	Консолідовано-недреноване	Консолидированно-недренированное
		//3	Консолідовано-дреноване	Консолидированно-дренированное
		// ID_OBJ ID_KT ID_PROB ID_GRAN		
		
		if (true)//(to_add)
		{

			if(!ExcelRange_GetValue(m_excel, "ID_STAN", ID_STAN))
			{	
				AfxMessageBox("Введите идентификатор состояния образца");
				return false;
			}
			switch(long(ID_STAN))
			{
			case 1:
				ExcelRange_SetValue(m_excel, "STAN", COleVariant("При естественной влажности"));
				break;
			case 2:
				ExcelRange_SetValue(m_excel, "STAN", COleVariant("В водонасыщенном состоянии"));
				break;
			}

			if(!ExcelRange_GetValue(m_excel, "ID_HID", ID_HID))
			{	
				AfxMessageBox("Введите идентификатор хода испытания");
				return false;
			}
			switch(long(ID_HID))
			{
			case 1:
				ExcelRange_SetValue(m_excel, "HID", COleVariant("Быстрый"));
				break;
			case 2:
				ExcelRange_SetValue(m_excel, "HID", COleVariant("Ускоренный"));
				break;
			case 3:
				ExcelRange_SetValue(m_excel, "HID", COleVariant("Медленный"));
				break;
			case 4:
				ExcelRange_SetValue(m_excel, "HID", COleVariant("Плашка по плашке"));
				break;
			}
			if(!ExcelRange_GetValue(m_excel, "ID_SHEMA", ID_SHEMA))
			{			
				AfxMessageBox("Введите идентификатор схемы испытания");
				return false;
			}
			switch(long(ID_SHEMA))
			{
			case 1:
				ExcelRange_SetValue(m_excel, "SHEMA", COleVariant("Неконсолидированно-недренированное"));
				break;
			case 2:
				ExcelRange_SetValue(m_excel, "SHEMA", COleVariant("Консолидированно-недренированное"));
				break;
			case 3:
				ExcelRange_SetValue(m_excel, "SHEMA", COleVariant("Консолидированно-дренированное"));
				break;
			}	
		}

		double m_grunta_do[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double m_grunta_posle[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double m_grunta_posle_uplot[]  = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double m_grunta_zamoch[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double m_grunta_vysush[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

		if (!toSavetoDB)
		{
			for (int ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;

				double val;
				/*sprintf(S, "D_KOLCA");
				if(ExcelRange_GetValue(m_excel, S, val))
				{
				}							
				sprintf(S, "H_KOLCA");
				if(ExcelRange_GetValue(m_excel, S, val))
				{
				}*/
				double m_kolca = 0.0;
				sprintf(S, "M_KOLCA_%d", id_kolca);
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					m_kolca = val;
				}
				sprintf(S, "M_GRUNTA_%d", id_kolca);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_%d", id_kolca);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_%d", id_kolca);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						m_grunta_do[ik] = val - m_kolca;
					}
				}
				else
				{
					m_grunta_do[ik] = val;
				}

				sprintf(S, "M_GRUNTA_POSLE_%d", id_kolca);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_POSLE_%d", id_kolca);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_POSLE_%d", id_kolca);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						m_grunta_posle[ik] = val - m_kolca;
					}
				}
				else
				{
					m_grunta_posle[ik] = val;
				}

				sprintf(S, "M_GRUNTA_POSLE_UPLOT_%d", id_kolca);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_POSLE_UPLOT_%d", id_kolca);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_POSLE_UPLOT_%d", id_kolca);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						m_grunta_posle_uplot[ik] = val - m_kolca;
					}
				}
				else
				{
					m_grunta_posle_uplot[ik] = val;
				}

				sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", id_kolca);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_POSLE_VYSUSH_%d", id_kolca);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", id_kolca);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						m_grunta_vysush[ik] = val - m_kolca;
					}
				}
				else
				{
					m_grunta_vysush[ik] = val;
				}



				sprintf(S, "M_GRUNTA_ZAMOCH_%d", id_kolca);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_ZAMOCH_%d", id_kolca);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_ZAMOCH_%d", id_kolca);
						m_grunta_zamoch[ik] = val - m_kolca;
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
					}
				}
				else
					m_grunta_zamoch[ik] = val;

			}
		}


		double indikator_1[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double indikator_2[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double mean_indikator[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double popravka[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double m_dh[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

		if (!toSavetoDB)
		{
			for (int ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;

				double val;

				sprintf(S, "DH_%d", id_kolca);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "POPRAV_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						popravka[ik] = val;
					}

					sprintf(S, "MEAN_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						mean_indikator[ik] = val;
						m_dh[ik] = mean_indikator[ik] - popravka[ik];

						sprintf(S, "DH_%d", id_kolca);
						ExcelRange_SetValue(m_excel, S, COleVariant(m_dh[ik]));
					}
					else
					{
						bool ind1 = false;
						bool ind2 = false;

						sprintf(S, "IND1_%d", id_kolca);
						if(ExcelRange_GetValue(m_excel, S, val))
						{
							ind1 = true;
							indikator_1[ik] = val;
						}
						sprintf(S, "IND2_%d", id_kolca);
						if(ExcelRange_GetValue(m_excel, S, val))
						{
							ind2 = true;
							indikator_2[ik] = val;
						}

						if (ind1 && ind2)
						{
							mean_indikator[ik] = 0.5 * (indikator_1[ik] + indikator_2[ik]);

							m_dh[ik] = mean_indikator[ik] - popravka[ik];

							sprintf(S, "MEAN_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(mean_indikator[ik]));

							sprintf(S, "DH_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(m_dh[ik]));
						}
						else
						{
							if (ind1)
							{
								mean_indikator[ik] = indikator_1[ik];

								m_dh[ik] = mean_indikator[ik] - popravka[ik];

								sprintf(S, "MEAN_%d", id_kolca);
								ExcelRange_SetValue(m_excel, S, COleVariant(mean_indikator[ik]));

								sprintf(S, "DH_%d", id_kolca);
								ExcelRange_SetValue(m_excel, S, COleVariant(m_dh[ik]));
							}
							if (ind2)
							{
								mean_indikator[ik] = indikator_2[ik];

								m_dh[ik] = mean_indikator[ik] - popravka[ik];

								sprintf(S, "MEAN_%d", id_kolca);
								ExcelRange_SetValue(m_excel, S, COleVariant(mean_indikator[ik]));

								sprintf(S, "DH_%d", id_kolca);
								ExcelRange_SetValue(m_excel, S, COleVariant(m_dh[ik]));
							}						
						}
					}
				}
				else
				{
					m_dh[ik] = val;
				}
			}
		}



		double wlazhnost_do[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double plotnost_do[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

		double wlazhnost_zamoch[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double plotnost_zamoch[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

		double wlazhnost_posle[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double plotnost_posle[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

		double wlazhnost_posle_uplot[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
		double plotnost_posle_uplot[] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};


		if (!toSavetoDB)
		{
			for (int ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;
				switch(long(ID_STAN))
				{
				case 1:
					{
						//ExcelRange_SetValue(m_excel, "STAN", COleVariant("При естественной влажности"));
						if (m_grunta_do[ik] && m_grunta_vysush[ik])
						{
							wlazhnost_do[ik] = (m_grunta_do[ik] - m_grunta_vysush[ik]) / m_grunta_vysush[ik];
							sprintf(S, "W_do_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(wlazhnost_do[ik]));
						}

						if (m_grunta_do[ik] && v_kolca && h_kolca)
						{
							double epsilon_ik = 0.0;

							plotnost_do[ik] = m_grunta_do[ik] / (v_kolca * (1.0 - epsilon_ik));
							sprintf(S, "RO_do_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(plotnost_do[ik]));
						}
					}
					break;
				case 2:
					{
						//ExcelRange_SetValue(m_excel, "STAN", COleVariant("В водонасыщенном состоянии"));
						if (m_grunta_zamoch[ik] && m_grunta_vysush[ik])
						{
							wlazhnost_zamoch[ik] = (m_grunta_zamoch[ik] - m_grunta_vysush[ik]) / m_grunta_vysush[ik];
							sprintf(S, "W_do_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(wlazhnost_zamoch[ik]));
						}

						if (m_grunta_zamoch[ik] && v_kolca && h_kolca)
						{
							double epsilon_ik = 0.0;//m_dh_zamoch[ik] / h_kolca;

							plotnost_zamoch[ik] = m_grunta_zamoch[ik] / (v_kolca * (1.0 - epsilon_ik));
							sprintf(S, "RO_do_%d", id_kolca);
							ExcelRange_SetValue(m_excel, S, COleVariant(plotnost_zamoch[ik]));
						}
					}
					break;
				}



				if (m_grunta_posle[ik] && m_grunta_vysush[ik])
				{
					wlazhnost_posle[ik] = (m_grunta_posle[ik] - m_grunta_vysush[ik]) / m_grunta_vysush[ik];
					sprintf(S, "W_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(wlazhnost_posle[ik]));
				}

				if (m_grunta_posle[ik] && v_kolca && h_kolca)
				{
					double epsilon_ik = m_dh[ik] / h_kolca;

					plotnost_posle[ik] = m_grunta_posle[ik] / (v_kolca * (1.0 - epsilon_ik));
					sprintf(S, "RO_po_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(plotnost_posle[ik]));
				}

				if (m_grunta_posle_uplot[ik] && m_grunta_vysush[ik])
				{
					wlazhnost_posle_uplot[ik] = (m_grunta_posle_uplot[ik] - m_grunta_vysush[ik]) / m_grunta_vysush[ik];
					sprintf(S, "W_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(wlazhnost_posle_uplot[ik]));
				}

				if (m_grunta_posle_uplot[ik] && v_kolca && h_kolca)
				{
					double epsilon_ik = m_dh[ik] / h_kolca;

					plotnost_posle_uplot[ik] = m_grunta_posle_uplot[ik] / (v_kolca * (1.0 - epsilon_ik));
					sprintf(S, "RO_po_upl_%d", id_kolca);
					ExcelRange_SetValue(m_excel, S, COleVariant(plotnost_posle_uplot[ik]));
				}

			}
		}
		
		if (toSavetoDB)
		{
			//long ID_VYPROB_1 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 1);
			//long ID_VYPROB_2 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 2);

			for (int ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;
				long ID_PHYS_VYPROB = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
				
				SetZriz0 setZriz0(this->p_database);
				setZriz0.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_KOLCA = %d", 
					ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
				if ( !setZriz0.Open(CRecordset::dynaset) )
					return false;

				if (!setZriz0.IsBOF()) 
				{
					while(!setZriz0.IsEOF()) 
					{
						setZriz0.MoveNext(); // to validate record count
					}
				}
				long records = setZriz0.GetRecordCount();
				bool to_edit_cilce_0 = false;
				bool to_add_cilce_0 = false;
				if (records == 1)
				{
					if (!setZriz0.IsBOF()) 
					{
						setZriz0.MoveFirst();
						setZriz0.Edit();
						to_edit_cilce_0 = true;
						to_add_cilce_0 = true;
					}
				}
				else if (records == 0)
				{
					setZriz0.AddNew();

					setZriz0.m_ID_OBJ = ID_OBJ;
					setZriz0.m_ID_KT = ID_KT;
					setZriz0.m_ID_PROB = ID_PROB;
					setZriz0.m_ID_VYPROB = id_cut_vyprob;
					setZriz0.m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;
					to_add_cilce_0 = true;							
				}
				if(to_add_cilce_0)
				{
					double val;
					sprintf(S, "D_KOLCA");
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						setZriz0.m_D = val;
					}							
					sprintf(S, "H_KOLCA");
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						setZriz0.m_H = val;
					}
					double m_kolca = 0.0;
					sprintf(S, "M_KOLCA_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_M_KOLCA && fabs(setZriz0.m_M_KOLCA - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_M_KOLCA (%f)!= val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_M_KOLCA, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_M_KOLCA = val;
							m_kolca = val;
						}
					}
					sprintf(S, "M_GRUNTA_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA && fabs(setZriz0.m_M_GRUNTA - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_M_GRUNTA (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_M_GRUNTA, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_M_GRUNTA = val;
						}
					}

					sprintf(S, "M_GRUNTA_POSLE_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA_POSLE && fabs(setZriz0.m_M_GRUNTA_POSLE - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_M_GRUNTA_POSLE (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_M_GRUNTA_POSLE, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_M_GRUNTA_POSLE = val;
						}
					}

					sprintf(S, "M_GRUNTA_POSLE_UPLOT_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA_POSLE_UPLOT && fabs(setZriz0.m_M_GRUNTA_POSLE_UPLOT - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_M_GRUNTA_POSLE_UPLOT (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_M_GRUNTA_POSLE_UPLOT, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_M_GRUNTA_POSLE_UPLOT = val;
						}
					}


					sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA_VYSUSH && fabs(setZriz0.m_M_GRUNTA_VYSUSH - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_M_GRUNTA_VYSUSH (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_M_GRUNTA_VYSUSH, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_M_GRUNTA_VYSUSH = val;
						}
					}


					sprintf(S, "M_GRUNTA_ZAMOCH_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA_ZAMOCH && fabs(setZriz0.m_M_GRUNTA_ZAMOCH - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_M_GRUNTA_ZAMOCH (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_M_GRUNTA_ZAMOCH, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_M_GRUNTA_ZAMOCH = val;
						}
					}

					sprintf(S, "DH_%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setZriz0.m_DH_PO_UPL && fabs(setZriz0.m_DH_PO_UPL - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setZriz0.m_DH_PO_UPL (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
								setZriz0.m_DH_PO_UPL, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setZriz0.m_DH_PO_UPL = val;
						}
					}

					setZriz0.Update();
				}
			}
		}




		if (true)
		{

			int n_pressures = 0;
			for (long ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;

				double sigma;
				sprintf(S, "SIGMA0%d", id_kolca);
				if (ExcelRange_GetValue(m_excel, S, sigma))
				{
					double tau;
					sprintf(S, "TAU0%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, tau))
					{
						n_pressures++;
					}
				}
			}

			CutLabTrial::type cut_stan = CutLabTrial::type::undefined;
			switch(long(ID_STAN))
			{
			case 1:
				cut_stan = CutLabTrial::type::nature_condition;
				break;
			case 2:
				cut_stan = CutLabTrial::type::task_condition;
				break;
			}
			
			CutLabTrial cut_lab_trial(cut_stan, 1);

			cut_lab_trial.n_pressures = n_pressures;
			cut_lab_trial.pressures = new double [cut_lab_trial.n_pressures];
			cut_lab_trial.cut_resistances = new trial_value [cut_lab_trial.n_pressures];

			for (long ik = 0; ik < nk; ik++)
			{
				long id_kolca = ik + 1;

				long ID_PHYS_VYPROB = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
				
				double sigma = 0.0;
				sprintf(S, "SIGMA0%d", id_kolca);
				if (ExcelRange_GetValue(m_excel, S, sigma))
				{
					double tau;
					sprintf(S, "TAU0%d", id_kolca);
					if(ExcelRange_GetValue(m_excel, S, tau))
					{
						cut_lab_trial.pressures[ik] = sigma;
						cut_lab_trial.cut_resistances[ik] = tau;
						if (toSavetoDB) 
						{
							double W_do = 0.0;
							double Ro_do = 0.0;

							double W_po_upl = 0.0;
							double Ro_po_upl = 0.0;

							double W_after = 0.0;
							double Ro_after = 0.0;

							sprintf(S, "W_do_%d", id_kolca);
							if(ExcelRange_GetValue(m_excel, S, W_do))
							{
							}
							sprintf(S, "RO_do_%d", id_kolca);
							if(ExcelRange_GetValue(m_excel, S, Ro_do))
							{
							}

							sprintf(S, "W_po_upl_%d", id_kolca);
							if(ExcelRange_GetValue(m_excel, S, W_po_upl))
							{
							}
							sprintf(S, "RO_po_upl_%d", id_kolca);
							if(ExcelRange_GetValue(m_excel, S, Ro_po_upl))
							{
							}

							sprintf(S, "W_po_%d", id_kolca);
							if(ExcelRange_GetValue(m_excel, S, W_after))
							{
							}
							sprintf(S, "RO_po_%d", id_kolca);
							if(ExcelRange_GetValue(m_excel, S, Ro_after))
							{
							}

							setZriz_tbl.AddNewRow(ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca, sigma, tau, 
								W_do, Ro_do, 
								W_po_upl, Ro_po_upl, 
								W_after, Ro_after);
						}
					}
				}
			}

			CutLabTrialResults * cut_lab_trial_res = dynamic_cast<CutLabTrialResults *>(cut_lab_trial.results);
			if (cut_lab_trial_res)
			{
				cut_lab_trial_res->CalcProperties();
				ExcelRange_SetValue(m_excel, "TGFI", COleVariant(cut_lab_trial_res->tgfi.v));
				ExcelRange_SetValue(m_excel, "FI", COleVariant(cut_lab_trial_res->fi));
				ExcelRange_SetValue(m_excel, "C_MPa", COleVariant(cut_lab_trial_res->c.v));
				if (toSavetoDB) setZriz.AddNewRow(ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, long(ID_HID), long(ID_SHEMA), long(ID_STAN), cut_lab_trial_res->tgfi.v, cut_lab_trial_res->c.v,
					d_kolca, h_kolca);
			}
		}


		CString where;
		where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
			ID_OBJ, ID_KT, ID_PROB);

		this->m_lab_view->UpdateCutListCtrl(where, "ID_VYPROB");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
	return true;
}
