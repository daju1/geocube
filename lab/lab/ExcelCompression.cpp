// ExcelCompression.cpp: implementation of the ExcelCompression class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelCompression.h"

#include "labView.h"
#include "SetObject.h"
//#include "SetZriz.h"
//#include "SetZriz_tbl.h"
#include "SetProbGr.h"
#include "SetKT.h"
#include "SetFizMeh.h"
#include "SetCompress.h"
#include "SetCilce.h"
#include "SetCilce0.h"

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

ExcelCompression::ExcelCompression()
{
	use_compute_for_save = true;
}

ExcelCompression::~ExcelCompression()
{

}

void ExcelCompression::InitExt()
{
	ext					= "cmp";
	xl_filter_name		= "Сompression";
	xl_form				= "Comp2Zhurnal";
}
bool ExcelCompression::virFill()
{
	try
	{
		int nObItem = this->m_lab_view->GetObjectItem();
		if (nObItem < 0)
		{
			AfxMessageBox("Не выбран объект");
			return false;
		}


		bool add_cut_from_db = false;
		bool add_compress_from_db = true;
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





		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		ExcelRange_SetValue(m_excel, "CONTRACT", COleVariant(setObject.m_CONTRACT));
		ExcelRange_SetValue(m_excel, "OBJECT", COleVariant(setObject.m_NAZVA));

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

		ExcelRange_SetValue(m_excel, "H", COleVariant(H));
		ExcelRange_SetValue(m_excel, "GRUNT_NAME", COleVariant(GRUNT_NAME));

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
			}
		}

		long id_compress_vyprob = lab_number ? lab_number->GetCompressVyprobMaxID() + 1 : 1;

		double m_grunta_1, m_kolca_1, m_kolca_s_gruntom_1;
		double m_grunta_2, m_kolca_2, m_kolca_s_gruntom_2;
			
		
		
		

		for (long iv = 0; iv < 2; iv++)
		{
			long id_kolca = iv + 1;
			long ID_PHYS_VYPROB = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, id_kolca);


			SetCilce0 setCilce0(this->p_database);
			setCilce0.m_strFilter.Format(
				"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PHYS_VYPROB = %d", 
				ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, ID_PHYS_VYPROB);
			if ( !setCilce0.Open(CRecordset::dynaset) )
				return false;

			if (!setCilce0.IsBOF()) 
			{
				setCilce0.MoveFirst( );
				if(!setCilce0.IsEOF()) 
				{
					switch (iv)
					{
					case 0:
						{							
							if (setCilce0.m_H)
								ExcelRange_SetValue(m_excel, "H_KOLCA", COleVariant(setCilce0.m_H));
							if (setCilce0.m_D)
								ExcelRange_SetValue(m_excel, "D_KOLCA", COleVariant(setCilce0.m_D));
							
							m_kolca_1 = setCilce0.m_M_KOLCA;
							if (m_kolca_1)
							{
								ExcelRange_SetValue(m_excel, "M_KOLCA_1", COleVariant(setCilce0.m_M_KOLCA));
								
								m_grunta_1 = setCilce0.m_M_GRUNTA;
								if (m_grunta_1)
								{
									ExcelRange_SetValue(m_excel, "M_GRUNTA_1", COleVariant(setCilce0.m_M_GRUNTA));

									m_kolca_s_gruntom_1 = m_grunta_1 + m_kolca_1;
									ExcelRange_SetValue(m_excel, "M_KOLCA_S_GRUNTOM_1", COleVariant(m_kolca_s_gruntom_1));
								}

								if (setCilce0.m_M_GRUNTA_VYSUSH)
								{
									double m_kolca_s_gruntom_vysush_1 = setCilce0.m_M_GRUNTA_VYSUSH + m_kolca_1;
									ExcelRange_SetValue(m_excel, "M_KOLCA_S_GRUNTOM_POSLE_VYSUSH_1", COleVariant(m_kolca_s_gruntom_vysush_1));
									ExcelRange_SetValue(m_excel, "M_GRUNTA_POSLE_VYSUSH_1", COleVariant(setCilce0.m_M_GRUNTA_VYSUSH));
								}
							}
						}
						break;
					case 1:
						{
							m_kolca_2 = setCilce0.m_M_KOLCA;
							if (m_kolca_2)
							{
								ExcelRange_SetValue(m_excel, "M_KOLCA_2", COleVariant(setCilce0.m_M_KOLCA));
								
								m_grunta_2 = setCilce0.m_M_GRUNTA;
								if (m_grunta_2)
								{
									ExcelRange_SetValue(m_excel, "M_GRUNTA_2", COleVariant(setCilce0.m_M_GRUNTA));
								
									m_kolca_s_gruntom_2 = m_grunta_2 + m_kolca_2;
									ExcelRange_SetValue(m_excel, "M_KOLCA_S_GRUNTOM_2", COleVariant(m_kolca_s_gruntom_2));
								}

								if (setCilce0.m_M_GRUNTA_VYSUSH)
								{								
									double m_kolca_s_gruntom_vysush_2 = setCilce0.m_M_GRUNTA_VYSUSH + m_kolca_2;
									ExcelRange_SetValue(m_excel, "M_KOLCA_S_GRUNTOM_POSLE_VYSUSH_2", COleVariant(m_kolca_s_gruntom_vysush_2));
									ExcelRange_SetValue(m_excel, "M_GRUNTA_POSLE_VYSUSH_2", COleVariant(setCilce0.m_M_GRUNTA_VYSUSH));
								}
							}
						}
						break;
					}
				}
			}

			//

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
			AfxMessageBox("Высота и диаметр кольца не указаны");
			return false;
		}

		if (lab_number)
		{
			//long id_compress_vyprob = ID_VYPROB;
			long ID_VYPROB_1 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 1);
			long ID_VYPROB_2 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 2);

			LabTrial * lab_trial_0 = lab_number->FindLabTrial(LabTrial::indication::physical, MEAN_PHYS_VYPROB);
			PhysicalLabTrial * phys_lab_trial_0 = dynamic_cast<PhysicalLabTrial *>(lab_trial_0);
			
			LabTrial * lab_trial_1 = lab_number->FindLabTrial(LabTrial::indication::physical, ID_VYPROB_1);
			PhysicalLabTrial * phys_lab_trial_1 = dynamic_cast<PhysicalLabTrial *>(lab_trial_1);
			
			LabTrial * lab_trial_2 = lab_number->FindLabTrial(LabTrial::indication::physical, ID_VYPROB_2);
			PhysicalLabTrial * phys_lab_trial_2 = dynamic_cast<PhysicalLabTrial *>(lab_trial_2);

			if (phys_lab_trial_1 && phys_lab_trial_1->moisture_of_nature_large_exchange.f)
			{
				ExcelRange_SetValue(m_excel, "W_do_1", COleVariant(phys_lab_trial_1->moisture_of_nature_large_exchange.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_of_nature_large_exchange.f)
			{
				ExcelRange_SetValue(m_excel, "W_do_1", COleVariant(phys_lab_trial_0->moisture_of_nature_large_exchange.v));
			}

			if (phys_lab_trial_2 && phys_lab_trial_2->moisture_of_nature_large_exchange.f)
			{
				ExcelRange_SetValue(m_excel, "W_do_2", COleVariant(phys_lab_trial_2->moisture_of_nature_large_exchange.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_of_nature_large_exchange.f)
			{
				ExcelRange_SetValue(m_excel, "W_do_2", COleVariant(phys_lab_trial_0->moisture_of_nature_large_exchange.v));
			}

			if (phys_lab_trial_1 && phys_lab_trial_1->density_of_ground.f)
			{
				ExcelRange_SetValue(m_excel, "RO_do_1", COleVariant(phys_lab_trial_1->density_of_ground.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground.f)
			{
				ExcelRange_SetValue(m_excel, "RO_do_1", COleVariant(phys_lab_trial_0->density_of_ground.v));
			}

			if (phys_lab_trial_2 && phys_lab_trial_2->density_of_ground.f)
			{
				ExcelRange_SetValue(m_excel, "RO_do_2", COleVariant(phys_lab_trial_2->density_of_ground.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground.f)
			{
				ExcelRange_SetValue(m_excel, "RO_do_2", COleVariant(phys_lab_trial_0->density_of_ground.v));
			}

			if (phys_lab_trial_1 && phys_lab_trial_1->density_of_ground_particles.f)
			{
				ExcelRange_SetValue(m_excel, "ROs_do_1", COleVariant(phys_lab_trial_1->density_of_ground_particles.v));
				ExcelRange_SetValue(m_excel, "ROs_po_1", COleVariant(phys_lab_trial_1->density_of_ground_particles.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground_particles.f)
			{
				ExcelRange_SetValue(m_excel, "ROs_do_1", COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
				ExcelRange_SetValue(m_excel, "ROs_po_1", COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
			}

			if (phys_lab_trial_2 && phys_lab_trial_2->density_of_ground_particles.f)
			{
				ExcelRange_SetValue(m_excel, "ROs_do_2", COleVariant(phys_lab_trial_2->density_of_ground_particles.v));
				ExcelRange_SetValue(m_excel, "ROs_po_2", COleVariant(phys_lab_trial_2->density_of_ground_particles.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->density_of_ground_particles.f)
			{
				ExcelRange_SetValue(m_excel, "ROs_do_2", COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
				ExcelRange_SetValue(m_excel, "ROs_po_2", COleVariant(phys_lab_trial_0->density_of_ground_particles.v));
			}



			if (phys_lab_trial_1 && phys_lab_trial_1->moisture_on_fluidity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WL_do_1", COleVariant(phys_lab_trial_1->moisture_on_fluidity_border.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_on_fluidity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WL_do_1", COleVariant(phys_lab_trial_0->moisture_on_fluidity_border.v));
			}

			if (phys_lab_trial_2 && phys_lab_trial_2->moisture_on_fluidity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WL_do_2", COleVariant(phys_lab_trial_2->moisture_on_fluidity_border.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_on_fluidity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WL_do_2", COleVariant(phys_lab_trial_0->moisture_on_fluidity_border.v));
			}



			if (phys_lab_trial_1 && phys_lab_trial_1->moisture_on_plasticity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WP_do_1", COleVariant(phys_lab_trial_1->moisture_on_plasticity_border.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_on_plasticity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WP_do_1", COleVariant(phys_lab_trial_0->moisture_on_plasticity_border.v));
			}

			if (phys_lab_trial_2 && phys_lab_trial_2->moisture_on_plasticity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WP_do_2", COleVariant(phys_lab_trial_2->moisture_on_plasticity_border.v));
			}
			else if (phys_lab_trial_0 && phys_lab_trial_0->moisture_on_plasticity_border.f)
			{
				ExcelRange_SetValue(m_excel, "WP_do_2", COleVariant(phys_lab_trial_0->moisture_on_plasticity_border.v));
			}
		}

		LabTrial * lab_trial_f = lab_number->FindLabTrial(LabTrial::indication::fractions, -1);
		FractionsLabTrial * frac_lab_trial = dynamic_cast<FractionsLabTrial *>(lab_trial_f);
		if (frac_lab_trial)			
		{
			frac_lab_trial->FillZhurnal(m_excel, 37, 38);
		}
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

bool ExcelCompression::virCompute(bool toSavetoDB)
{
	double digits_epsilon = 1e-8;
	try
	{
		int nObItem = this->m_lab_view->GetObjectItem();
		if (nObItem < 0)
		{
			AfxMessageBox("Не выбран объект");
			return false;
		}


		char S[64];
		bool add_cut_from_db = false;
		bool add_compress_from_db = true;
		int nCutItem = 0;
		int nCompItem = 0;
		bool add_stat_zond_from_db = false;
		LabNumber * lab_number = this->m_lab_view->CreateLabNumber(-1, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
		if (!lab_number) return false;	
#if 0
		long id_vyprob = lab_number ? lab_number->GetCompressVyprobMaxID() + 1 : 1;
		long id_compress_vyprob = id_vyprob;
#else
		long id_compress_vyprob = lab_number ? lab_number->GetCompressVyprobMaxID() + 1 : 1;
#endif

		if (!lab_number->HaveEnoughFor_e0(id_compress_vyprob))
		{
			AfxMessageBox(
				"Для расчёта коэффициента пористости в выбранной пробе грунта недостаточно данных\n"
				"Необходимо определитть плотность грунта, плотность частиц грунта и влажность");
			return false;
		}

		long lab_n = lab_number->lab_n;
		ExcelRange_SetValue(m_excel, "LAB_N", COleVariant(lab_n));
		ExcelRange_SetValue(m_excel, "LAB_N_2", COleVariant(lab_n));

		double m_grunta_1, m_kolca_1, m_kolca_s_gruntom_1;
		if(!ExcelRange_GetValue(m_excel, "M_GRUNTA_1", m_grunta_1))
		{
			if(ExcelRange_GetValue(m_excel, "M_KOLCA_1", m_kolca_1)  
				&& ExcelRange_GetValue(m_excel, "M_KOLCA_S_GRUNTOM_1", m_kolca_s_gruntom_1))
			{	
				m_grunta_1 = m_kolca_s_gruntom_1 - m_kolca_1;
				ExcelRange_SetValue(m_excel, "M_GRUNTA_1", COleVariant(m_grunta_1));
			}
		}

		double m_grunta_2, m_kolca_2, m_kolca_s_gruntom_2;
		if(!ExcelRange_GetValue(m_excel, "M_GRUNTA_2", m_grunta_2))
		{
			if(ExcelRange_GetValue(m_excel, "M_KOLCA_2", m_kolca_2)  
				&& ExcelRange_GetValue(m_excel, "M_KOLCA_S_GRUNTOM_2", m_kolca_s_gruntom_2))
			{	
				m_grunta_2 = m_kolca_s_gruntom_2 - m_kolca_2;
				ExcelRange_SetValue(m_excel, "M_GRUNTA_2", COleVariant(m_grunta_2));
			}
		}

		double h_kolca, d_kolca;
		double s_kolca = 0.0, v_kolca = 0.0;
		if(ExcelRange_GetValue(m_excel, "H_KOLCA", h_kolca) 
			&& 
			ExcelRange_GetValue(m_excel, "D_KOLCA", d_kolca))
		{	
			// перевод из сантиметров в миллиметры
			h_kolca *= 10.;
			d_kolca *= 10.;

			s_kolca = 0.01 * 0.25 * PI * d_kolca * d_kolca;
			ExcelRange_SetValue(m_excel, "S_KOLCA", COleVariant(s_kolca));
			v_kolca = 0.1 * s_kolca * h_kolca;
			ExcelRange_SetValue(m_excel, "V_KOLCA", COleVariant(v_kolca));
		}
		else
		{
			AfxMessageBox("Высота и диаметр кольца не указаны");
			return false;
		}

		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		ExcelRange_SetValue(m_excel, "CONTRACT", COleVariant(setObject.m_CONTRACT));
		ExcelRange_SetValue(m_excel, "OBJECT", COleVariant(setObject.m_NAZVA));

		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
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

		ExcelRange_SetValue(m_excel, "H", COleVariant(H));

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
			}
		}

		SetCilce setCilce(this->p_database);
		if ( !setCilce.Open(CRecordset::dynaset) )
			return false;

		SetCompress setCompress(this->p_database);
		if ( !setCompress.Open(CRecordset::dynaset) )
			return false;

		double p0;
		sprintf(S, "A%d", 43);
		if(!ExcelRange_GetValue(m_excel, S, p0))
		{
			return false;
		}

		bool first_zero_pressure = p0 == 0.0;

		double e0_1;
		double e0_2;
		if(ExcelRange_GetValue(m_excel, "EO_do_1", e0_1))
		{
			if (!first_zero_pressure)
			{
				ExcelRange_SetValue(m_excel, "D62", COleVariant(e0_1));
			}
		}
		if(ExcelRange_GetValue(m_excel, "EO_do_2", e0_2))
		{
			if (!first_zero_pressure)
			{
				ExcelRange_SetValue(m_excel, "J62", COleVariant(e0_2));
			}
		}
		if (!first_zero_pressure)
		{
			ExcelRange_SetValue(m_excel, "A62", COleVariant(0.0));
			ExcelRange_SetValue(m_excel, "C62", COleVariant(0.0));
			ExcelRange_SetValue(m_excel, "I62", COleVariant(0.0));
		}

		double m_grunta_posle_1 = 0.0;
		double m_grunta_posle_2 = 0.0;

		double m_zamoch_grunta_2 = 0.0;

		double m_grunta_vysush_1 = 0.0;
		double m_grunta_vysush_2 = 0.0;

		if (!toSavetoDB)
		{
			for (int iv = 0; iv <= 1; iv++)
			{
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
				sprintf(S, "M_KOLCA_%d", 1 + iv);
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					m_kolca = val;
				}
				sprintf(S, "M_GRUNTA_%d", 1 + iv);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_%d", 1 + iv);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_%d", 1 + iv);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
					}
				}

				sprintf(S, "M_GRUNTA_POSLE_%d", 1 + iv);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_POSLE_%d", 1 + iv);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_POSLE_%d", 1 + iv);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						if (iv) m_grunta_posle_2 = val - m_kolca;
						else m_grunta_posle_1 = val - m_kolca;

					}
				}
				else
				{
					if (iv) m_grunta_posle_2 = val;
					else  m_grunta_posle_1 = val;
				}

				sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", 1 + iv);
				if(!ExcelRange_GetValue(m_excel, S, val))
				{
					sprintf(S, "M_KOLCA_S_GRUNTOM_POSLE_VYSUSH_%d", 1 + iv);
					if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", 1 + iv);
						ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						if (iv) m_grunta_vysush_2 = val - m_kolca;
						else m_grunta_vysush_1 = val - m_kolca;
					}
				}
				else
				{
					if (iv) m_grunta_vysush_2 = val;
					else  m_grunta_vysush_1 = val;
				}


				if (iv)
				{
					sprintf(S, "M_ZAMOCH_GRUNTA_%d", 1 + iv);
					if(!ExcelRange_GetValue(m_excel, S, val))
					{
						sprintf(S, "M_KOLCA_S_ZAMOCH_GRUNTOM_%d", 1 + iv);
						if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
						{
							sprintf(S, "M_ZAMOCH_GRUNTA_%d", 1 + iv);
							m_zamoch_grunta_2 = val - m_kolca;
							ExcelRange_SetValue(m_excel, S, COleVariant(val-m_kolca));
						}
					}
					else
						m_zamoch_grunta_2 = val;
				}
			}
		}


		double m_otzhatoj_vody = 0.0;
		double dejstvit_polnaja_osadka = 0.0;
		if (m_grunta_posle_2 && m_zamoch_grunta_2)
		{
			m_otzhatoj_vody = m_zamoch_grunta_2 - m_grunta_posle_2;
			dejstvit_polnaja_osadka = 10.0 * m_otzhatoj_vody / s_kolca;
		}

		double osadka_po_indikatory = 0.0;
	

		bool b1_all = true;
		bool b2_all = true;

		bool b1_any = false;
		bool b2_any = false;

		int fr2 = first_zero_pressure ? 62 : 63;

		bool zamach = false;
		bool water = false;
		bool zamach_pre = false;			
		double p_pre = 0.0;


		for (int r = 0; r < 15; r++)
		{
			int row = 43 + r;
			int row2 = fr2 + r;

			double p;
			sprintf(S, "A%d", row);
			if(!ExcelRange_GetValue(m_excel, S, p))
			{
				break;
			}

			sprintf(S, "A%d", row2);
			ExcelRange_SetValue(m_excel, S, COleVariant(p));

			double p_pre_;
			sprintf(S, "A%d", row-1);
			if(!ExcelRange_GetValue(m_excel, S, p_pre_))
			{
			}

			zamach = r ? p == p_pre_ : false;
			if (r && p == p_pre_) water = true;
			if (r && !zamach) p_pre = p_pre_;

//						sprintf(S, "O%d", row);
//						ExcelRange_SetValue(m_excel, S, COleVariant(long(zamach)));
//						sprintf(S, "O%d", row2);
//						ExcelRange_SetValue(m_excel, S, COleVariant(long(zamach)));

			double dh = 0.0, dhw = 0.0;

			bool b1 = false;
			
			if (true)
			{
				double i1, i2, i;
				sprintf(S, "D%d", row);
				if(!ExcelRange_GetValue(m_excel, S, i))
				{
					b1 = true;
					sprintf(S, "B%d", row);
					if(!ExcelRange_GetValue(m_excel, S, i1))
					{
						//CString s; s.Format("Не указано показание I индикатора\nдля давления %f", p);
						//AfxMessageBox(s);
						//return;
						b1 = false;
					}
					sprintf(S, "C%d", row);
					if(!ExcelRange_GetValue(m_excel, S, i2))
					{
						//CString s; s.Format("Не указано показание II индикатора\nдля давления %f", p);
						//AfxMessageBox(s);
						//return;
						b1 = false;
					}
					if(b1)
					{
						i = 0.5 * (i1 + i2);
						sprintf(S, "D%d", row);
						ExcelRange_SetValue(m_excel, S, COleVariant(i));
					}
				}
				else
					b1 = true;

				if(b1)
				{
					double d;
					sprintf(S, "E%d", row);
					if(!ExcelRange_GetValue(m_excel, S, d))
					{
						CString s; s.Format("Не указана поправка на деформацию прибора\nдля давления %f", p);
						AfxMessageBox(s);
						return false;
					}
					dh = i - d;
					sprintf(S, "F%d", row);
					ExcelRange_SetValue(m_excel, S, COleVariant(dh));

					sprintf(S, "B%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(dh));

					double epsilon = dh / h_kolca;
					sprintf(S, "G%d", row);
					ExcelRange_SetValue(m_excel, S, COleVariant(epsilon));
					sprintf(S, "C%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(epsilon));

					double modul_osadki = epsilon * 1000;
					sprintf(S, "D%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(modul_osadki));

					double e = e0_1 - (1+e0_1) * epsilon;
					sprintf(S, "E%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(e));

					double e_pre;
					sprintf(S, "E%d", row2-1);
					if(!zamach && !zamach_pre && ExcelRange_GetValue(m_excel, S, e_pre))
					{
						double a = (e_pre - e) / (p - p_pre);
						sprintf(S, "F%d", row2);
						ExcelRange_SetValue(m_excel, S, COleVariant(a));
					}

				}
			}

			if (!zamach)
			{
				b1_all &= b1;
				b1_any |= b1;
			}

			bool b2 = false;
			if (!zamach)
			{
				double i1w, i2w, iw;
				sprintf(S, "J%d", row);
				if(!ExcelRange_GetValue(m_excel, S, iw))
				{
					b2 = true;
					sprintf(S, "H%d", row);
					if(!ExcelRange_GetValue(m_excel, S, i1w))
					{
						//CString s; s.Format("Не указано показание I индикатора W\nдля давления %f", p);
						//AfxMessageBox(s);
						//return;
						b2 = false;
					}
					sprintf(S, "I%d", row);
					if(!ExcelRange_GetValue(m_excel, S, i2w))
					{
						//CString s; s.Format("Не указано показание II индикатора W\nдля давления %f", p);
						//AfxMessageBox(s);
						//return;
						b2 = false;
					}
					if(b2)
					{
						iw = 0.5 * (i1w + i2w);
						sprintf(S, "J%d", row);
						ExcelRange_SetValue(m_excel, S, COleVariant(iw));
					}
				}
				else
					b2 = true;

				if(b2)
				{
					double dw;
					sprintf(S, "K%d", row);
					if(!ExcelRange_GetValue(m_excel, S, dw))
					{
						CString s; s.Format("Не указана поправка на деформацию прибора W\nдля давления %f", p);
						AfxMessageBox(s);
						return false;
					}
					dhw = iw - dw;
					sprintf(S, "L%d", row);
					ExcelRange_SetValue(m_excel, S, COleVariant(dhw));
					sprintf(S, "H%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(dhw));

					osadka_po_indikatory = dhw;

					double epsilonw = dhw / h_kolca;
					sprintf(S, "M%d", row);
					ExcelRange_SetValue(m_excel, S, COleVariant(epsilonw));
					sprintf(S, "I%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(epsilonw));

					double modul_osadki_w = epsilonw * 1000;
					sprintf(S, "J%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(modul_osadki_w));

					double ew = e0_2 - (1+e0_2) * epsilonw;
					sprintf(S, "K%d", row2);
					ExcelRange_SetValue(m_excel, S, COleVariant(ew));

					double e_prew;
					sprintf(S, "K%d", row2-1-int(zamach_pre));
					if(ExcelRange_GetValue(m_excel, S, e_prew))
					{
						double aw = (e_prew - ew) / (p - p_pre);
						sprintf(S, "L%d", row2);
						ExcelRange_SetValue(m_excel, S, COleVariant(aw));
					}

				}
			}


			if (!zamach)
			{
				b2_all &= b2;
				b2_any |= b2;
			}
			unsigned char voda  = 1;
			if (lab_number)	lab_number->AddCompress(id_compress_vyprob, zamach ? -p : p, dh, dhw, voda, 1);
			if (toSavetoDB)
				setCompress.AddNewRow(ID_OBJ,ID_KT, ID_PROB, id_compress_vyprob, zamach ? -p : p, 0.1 * dh, 0.1 * dhw, voda, 1);

			zamach_pre = zamach;
		}

		double es_l1 = 0.1;
		double es_r1 = 0.2;
		double es_l2 = 0.2;
		double es_r2 = 0.3;
		double nju = 0.0;
		double nju_z = 0.0;
	    
		double m01 = 0.0;
		double E1 = 0.0;
		double m02 = 0.0;
		double E2 = 0.0;

		double m01v = 0.0;
		double E1v = 0.0;
		double m02v = 0.0;
		double E2v = 0.0;

		unsigned char id_method = 2;

		if( b1_all && b2_all)
		{
			id_method = 2;
		}
		else if (b1_all && !b2_any)
		{
			id_method = 1;			
		}
		else if (b2_all && !b1_any)
		{
			id_method = 4;			
		}
		else
		{
			id_method = 3;			
		}

		double popravochnyj_koefficient_alpha = 0.0;
		if (dejstvit_polnaja_osadka && osadka_po_indikatory)
		{
			popravochnyj_koefficient_alpha = dejstvit_polnaja_osadka / osadka_po_indikatory;
		}

		if (popravochnyj_koefficient_alpha)
		{
			long r61 = 61;

			sprintf(S, "N%d", 54);
			ExcelRange_SetValue(m_excel, S, COleVariant("Действительная полная осадка, мм"));
			sprintf(S, "O%d", 55);
			ExcelRange_SetValue(m_excel, S, COleVariant(dejstvit_polnaja_osadka));

			sprintf(S, "N%d", 56);
			ExcelRange_SetValue(m_excel, S, COleVariant("Поправочный коэффициент alpha"));
			sprintf(S, "O%d", 57);
			ExcelRange_SetValue(m_excel, S, COleVariant(popravochnyj_koefficient_alpha));

			sprintf(S, "N%d", r61);
			ExcelRange_SetValue(m_excel, S, COleVariant("Полная осадка по весу, мм"), true);
			sprintf(S, "O%d", r61);
			ExcelRange_SetValue(m_excel, S, COleVariant("Относительная деформация по весу"), true);
			sprintf(S, "P%d", r61);
			ExcelRange_SetValue(m_excel, S, COleVariant("Модуль осадки по весу"), true);
			sprintf(S, "Q%d", r61);
			ExcelRange_SetValue(m_excel, S, COleVariant("Коэффициент пористости по весу"), true);

			//if (!first_zero_pressure)
			//{
				ExcelRange_SetValue(m_excel, "N62", COleVariant(0.0), true);
				ExcelRange_SetValue(m_excel, "O62", COleVariant(0.0), true);
				ExcelRange_SetValue(m_excel, "P62", COleVariant(0.0), true);
				ExcelRange_SetValue(m_excel, "Q62", COleVariant(e0_2), true);
			//}
		}
		unsigned char bStat = 1;
		unsigned char bStatV = 1;

		if (lab_number)	lab_number->AddCompress(id_compress_vyprob, 		
			h_kolca, d_kolca, 
			es_l1, es_r1, es_l2, es_r2,
			nju, nju_z,
			m01, E1, m02, E2,
			m01v, E1v, m02v, E2v,
			id_method, bStat, bStatV);

		if (lab_number)	lab_number->ApplyCompress(true, 0);
		if (lab_number)	lab_number->CalcProperties();

		double epsilon1_max = 0.0;
		double epsilon2_max = 0.0;

		ExcelRange_SetValue(m_excel, "GRUNT_NAME", COleVariant(lab_number->GetSoilDescription(false).c_str()));

		LabTrial * lab_trial = lab_number ? lab_number->FindLabTrial(LabTrial::indication::compression_3, -1) : NULL;
		CompressionLabTrial3 * compression3 = dynamic_cast<CompressionLabTrial3 *>(lab_trial);
		if (compression3)
		{
			compression3->p_trial_1;
			compression3->p_trial_2;
			CompressionLabTrialResults * com_lab_res_1 = dynamic_cast<CompressionLabTrialResults *>(compression3->p_trial_1->results);
			CompressionLabTrialResults * com_lab_res_2 = dynamic_cast<CompressionLabTrialResults *>(compression3->p_trial_2->results);
			if(com_lab_res_1 && com_lab_res_2)
			{
				p_pre = 0.0;
				water = false;
				zamach = false;
				zamach_pre = false;
				for (int r = 0; r < 15; r++)
				{
					int row2 = 63 + r;
					//int row3 = 83 + r;

					double p;
					sprintf(S, "A%d", row2);
					if(!ExcelRange_GetValue(m_excel, S, p))
					{
						break;
					}

					double p_pre_;
					sprintf(S, "A%d", row2-1);
					if(!ExcelRange_GetValue(m_excel, S, p_pre_))
					{
					}

					zamach = r ? p == p_pre_ : false;
					if (r && p == p_pre_) water = true;
					if (r && !zamach) p_pre = p_pre_;



					if (!zamach && !zamach_pre)
					{
						bool calc_E = true;
						double epsilon;
						sprintf(S, "C%d", row2);
						if(!ExcelRange_GetValue(m_excel, S, epsilon))
						{
							calc_E = false;
						}

						double epsilon_pre;
						sprintf(S, "C%d", row2-1);
						if(!ExcelRange_GetValue(m_excel, S, epsilon_pre))
						{
							calc_E = false;
						}

						if(calc_E)
						{
							epsilon1_max = epsilon;
							switch(id_method)
							{
							case 1:
							case 2:
							case 3:
								{
									double E = (water ? com_lab_res_1->beta_tab_ws.v : com_lab_res_1->beta_tab.v) 
										* (p - p_pre) / (epsilon - epsilon_pre);
									sprintf(S, "G%d", row2);
									ExcelRange_SetValue(m_excel, S, COleVariant(E));
								}
								break;
							case 4:
								{
								}
								break;
							}
						}
					}

					if (true)
					{
						bool calc_E = true;
						double epsilonw;
						sprintf(S, "I%d", row2);
						if (!ExcelRange_GetValue(m_excel, S, epsilonw))
						{
							calc_E = false;
						}

						if (popravochnyj_koefficient_alpha && !zamach)
						{
							double dhw;
							sprintf(S, "H%d", row2);
							if (!ExcelRange_GetValue(m_excel, S, dhw))
							{
							}

							//sprintf(S, "G%d", row3);
							//ExcelRange_SetValue(m_excel, S, COleVariant(p));

							double dhpw = dhw*popravochnyj_koefficient_alpha;
							//sprintf(S, "H%d", row3);
							//ExcelRange_SetValue(m_excel, S, COleVariant(dhpw));

							sprintf(S, "N%d", row2);
							ExcelRange_SetValue(m_excel, S, COleVariant(dhpw), true);

							double epsilonpw = dhpw/h_kolca;
							//sprintf(S, "I%d", row3);
							//ExcelRange_SetValue(m_excel, S, COleVariant(epsilonpw));

							sprintf(S, "O%d", row2);
							ExcelRange_SetValue(m_excel, S, COleVariant(epsilonpw), true);

							double epsilonpw1000 = 1000*epsilonpw;
							//sprintf(S, "K%d", row3);
							//ExcelRange_SetValue(m_excel, S, COleVariant(epsilonpw1000));

							sprintf(S, "P%d", row2);
							ExcelRange_SetValue(m_excel, S, COleVariant(epsilonpw1000), true);

							double epw = e0_2 - (1+e0_2) * epsilonpw;
							//sprintf(S, "L%d", row3);
							//ExcelRange_SetValue(m_excel, S, COleVariant(epw));

							sprintf(S, "Q%d", row2);
							ExcelRange_SetValue(m_excel, S, COleVariant(epw), true);

						}

						double epsilon_prew;
						sprintf(S, "I%d", row2-1-int(zamach_pre));
						if(!ExcelRange_GetValue(m_excel, S, epsilon_prew))
						{
							calc_E = false;
						}

						if(calc_E)
						{
							epsilon2_max = epsilonw;
							switch(id_method)
							{
							case 1:
								{
								}
								break;
							case 2:
							case 4:
								{
									double Ew = com_lab_res_2->beta_tab_ws.v * (p - p_pre) / (epsilonw - epsilon_prew);
									sprintf(S, "M%d", row2);
									ExcelRange_SetValue(m_excel, S, COleVariant(Ew));
								}
								break;
							case 3:
								{
									double Ew = com_lab_res_1->beta_tab_ws.v * (p - p_pre) / (epsilonw - epsilon_prew);
									sprintf(S, "M%d", row2);
									ExcelRange_SetValue(m_excel, S, COleVariant(Ew));
								}
								break;

							}
						}
					}

					zamach_pre = zamach;
				}	

				switch(id_method)
				{
				case 1:
					{
						ExcelRange_SetValue(m_excel, "BETA", COleVariant(com_lab_res_1->beta_tab.v));
						nju = com_lab_res_1->nju_tab.v;
						nju_z = com_lab_res_1->nju_tab_ws.v;
					}
					break;
				case 2:
					{
						ExcelRange_SetValue(m_excel, "BETA", COleVariant(com_lab_res_1->beta_tab.v));
						ExcelRange_SetValue(m_excel, "BETA_WS", COleVariant(com_lab_res_2->beta_tab_ws.v));			
						nju = com_lab_res_1->nju_tab.v;
						nju_z = com_lab_res_2->nju_tab_ws.v;
					}
				case 3:
					{
						ExcelRange_SetValue(m_excel, "BETA", COleVariant(com_lab_res_1->beta_tab.v));
						ExcelRange_SetValue(m_excel, "BETA_WS", COleVariant(com_lab_res_1->beta_tab_ws.v));	
						nju = com_lab_res_1->nju_tab.v;
						nju_z = com_lab_res_1->nju_tab_ws.v;
					}
					break;
				case 4:
					{
						ExcelRange_SetValue(m_excel, "BETA_WS", COleVariant(com_lab_res_2->beta_tab_ws.v));			
						nju = com_lab_res_2->nju_tab.v;
						nju_z = com_lab_res_2->nju_tab_ws.v;
					}
					break;

				}
			}
			else
				MessageBox(0,"!(com_lab_res_1 && com_lab_res_2)", "ExcelCompression::virCompute()", 0);
			
			if (false)
			{
				char dir [4098];
				strcpy(dir, m_excel.m_workbook.GetFullName());
				char * p = NULL;
				if (p = strrchr(dir, '/'))
				{
					*p = '\0';
				}
				else if (p = strrchr(dir, '\\'))
				{
					*p = '\0';
				}

				char dir2[4098];
				sprintf(dir2, "%s\\PasportsCompress", dir);
				CreateDirectory(dir2, NULL);

				char fn[4098];
				sprintf(fn, "%s\\%d", dir2, int(lab_n));
				compression3->Passport_1(fn);

				sprintf(fn, "%s\\%d_W", dir2, int(lab_n));
				compression3->Passport_2(fn);
			}		
		}
		else
			MessageBox(0,"!compression3", "ExcelCompression::virCompute()", 0);
		
		if (!toSavetoDB)
		{
			if (m_grunta_posle_1 && m_grunta_vysush_1)
			{
				double wlazhnost_posle_1 = (m_grunta_posle_1 - m_grunta_vysush_1) / m_grunta_vysush_1;
				ExcelRange_SetValue(m_excel, "W_po_1", COleVariant(wlazhnost_posle_1));
			}
			if (m_grunta_posle_2 && m_grunta_vysush_2)
			{
				double wlazhnost_posle_2 = (m_grunta_posle_2 - m_grunta_vysush_2) / m_grunta_vysush_2;
				ExcelRange_SetValue(m_excel, "W_po_2", COleVariant(wlazhnost_posle_2));
			}
			if (m_grunta_posle_1 && v_kolca)
			{
				double plotnost_posle_1 = m_grunta_posle_1 / (v_kolca * (1.0 - epsilon1_max));
				ExcelRange_SetValue(m_excel, "RO_po_1", COleVariant(plotnost_posle_1));
			}
			if (m_grunta_posle_2 && v_kolca)
			{
				double plotnost_posle_2 = m_grunta_posle_2 / (v_kolca * (1.0 - epsilon2_max));
				ExcelRange_SetValue(m_excel, "RO_po_2", COleVariant(plotnost_posle_2));
			}
		}
		
		if (toSavetoDB)
		{
			long ID_VYPROB_1 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 1);
			long ID_VYPROB_2 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 2);

			for (int iv = 0; iv <= 1; iv++)
			{
				long id_kolca = iv + 1;
				long ID_PHYS_VYPROB = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, id_kolca);
				
				SetCilce0 setCilce0(this->p_database);
				setCilce0.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PHYS_VYPROB = %d", 
					ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, ID_PHYS_VYPROB);
				if ( !setCilce0.Open(CRecordset::dynaset) )
					return false;

				if (!setCilce0.IsBOF()) 
				{
					while(!setCilce0.IsEOF()) 
					{
						setCilce0.MoveNext(); // to validate record count
					}
				}
				long records = setCilce0.GetRecordCount();
				bool to_edit_cilce_0 = false;
				bool to_add_cilce_0 = false;
				if (records == 1)
				{
					if (!setCilce0.IsBOF()) 
					{
						setCilce0.MoveFirst();
						setCilce0.Edit();
						to_edit_cilce_0 = true;
						to_add_cilce_0 = true;
					}
				}
				else if (records == 0)
				{
					setCilce0.AddNew();

					setCilce0.m_ID_OBJ = ID_OBJ;
					setCilce0.m_ID_KT = ID_KT;
					setCilce0.m_ID_PROB = ID_PROB;
					setCilce0.m_ID_VYPROB = id_compress_vyprob;
					setCilce0.m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;
					to_add_cilce_0 = true;							
				}
				if(to_add_cilce_0)
				{
					double val;
					sprintf(S, "D_KOLCA");
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						setCilce0.m_D = val;
					}							
					sprintf(S, "H_KOLCA");
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						setCilce0.m_H = val;
					}
					double m_kolca = 0.0;
					sprintf(S, "M_KOLCA_%d", 1 + iv);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setCilce0.m_M_KOLCA && fabs(setCilce0.m_M_KOLCA - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setCilce0.m_M_KOLCA (%f)!= val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
								setCilce0.m_M_KOLCA, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setCilce0.m_M_KOLCA = val;
							m_kolca = val;
						}
					}
					sprintf(S, "M_GRUNTA_%d", 1 + iv);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setCilce0.m_M_GRUNTA && fabs(setCilce0.m_M_GRUNTA - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setCilce0.m_M_GRUNTA (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
								setCilce0.m_M_GRUNTA, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setCilce0.m_M_GRUNTA = val;
						}
					}

					sprintf(S, "M_GRUNTA_POSLE_%d", 1 + iv);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setCilce0.m_M_GRUNTA_POSLE && fabs(setCilce0.m_M_GRUNTA_POSLE - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setCilce0.m_M_GRUNTA_POSLE (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
								setCilce0.m_M_GRUNTA_POSLE, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setCilce0.m_M_GRUNTA_POSLE = val;
						}
					}

					sprintf(S, "M_GRUNTA_POSLE_VYSUSH_%d", 1 + iv);
					if(ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setCilce0.m_M_GRUNTA_VYSUSH && fabs(setCilce0.m_M_GRUNTA_VYSUSH - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setCilce0.m_M_GRUNTA_VYSUSH (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
								setCilce0.m_M_GRUNTA_VYSUSH, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setCilce0.m_M_GRUNTA_VYSUSH = val;
						}
					}


					sprintf(S, "M_ZAMOCH_GRUNTA_%d", 1 + iv);
					if(iv && ExcelRange_GetValue(m_excel, S, val))
					{
						bool to_set = true;
						if (to_edit_cilce_0 && setCilce0.m_M_GRUNTA_ZAMOCH && fabs(setCilce0.m_M_GRUNTA_ZAMOCH - val) >= digits_epsilon)
						{
							CString s;
							s.Format(
								"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
								"setCilce0.m_M_GRUNTA_ZAMOCH (%f) != val (%f)"
								"\nЗаменить?"
								,
								lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
								setCilce0.m_M_GRUNTA_ZAMOCH, val);
							to_set = IDYES == AfxMessageBox(s, MB_YESNO);
						}
						if (to_set)
						{
							setCilce0.m_M_GRUNTA_ZAMOCH = val;
						}
					}

					setCilce0.Update();
				}
			}
		}
		
		if (toSavetoDB)
			setCilce.AddNewRow(ID_OBJ,ID_KT, ID_PROB, id_compress_vyprob, 
				0.1 * h_kolca, 0.1 * d_kolca, 
				es_l1, es_r1, es_l2, es_r2,
				nju, nju_z,
				m01, E1, m02, E2,
				m01v, E1v, m02v, E2v,
				id_method, bStat, bStatV);

		CString where;
		where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
			ID_OBJ, ID_KT, ID_PROB);

		this->m_lab_view->UpdateCompressListCtrl(where, "ID_VYPROB");

		
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
