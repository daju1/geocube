// ExcelAreometrGranular.cpp: implementation of the ExcelAreometrGranular class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelAreometrGranular.h"
#include "labView.h"
#include "SetObject.h"
#include "SetGranular.h"
#include "SetProbGr.h"
#include "SetKT.h"

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

ExcelAreometrGranular::ExcelAreometrGranular()
{
}

ExcelAreometrGranular::~ExcelAreometrGranular()
{

}
void ExcelAreometrGranular::InitExt()
{
	ext					= "agn";
	xl_filter_name		= "Areometr Granular";
	xl_form				= "ClaySoilGranular";
}

bool ExcelAreometrGranular::virCompute(bool)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	char S[64];
	char F[1024];

	int fr = 12;

	for (int r_ = 0; r_ <= 11; r_++)
	{
		int row1 = fr + 2*r_;
		int row2 = fr + 2*r_ + 1;

		sprintf(S, "B%d", row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);			   
		VARIANT labn = m_range.GetValue();
		m_range.ReleaseDispatch();	

		double lab_n = 0.0;
		if (labn.vt == VT_R8)
		{
			lab_n = labn.dblVal;
		}
		else
		{
			break;
		}

		sprintf(S, "G%d", row1);
		sprintf(F, "=(1 + E%d)/F%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetValue(COleVariant(F));
		m_range.SetNumberFormat(COleVariant("0.00E+00"));
		m_range.ReleaseDispatch();	

		sprintf(S, "H%d", row2);
		sprintf(F, "=H%d*G%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetValue(COleVariant(F));
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.ReleaseDispatch();	

		sprintf(S, "I%d", row2);
		sprintf(F, "=I%d*G%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetValue(COleVariant(F));
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.ReleaseDispatch();	

		sprintf(S, "J%d", row2);
		sprintf(F, "=J%d*G%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "L%d", row2);
		sprintf(F, "=L%d/(L%d-1)", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "O%d", row2);
		sprintf(F, "=(O%d+O36) * L%d * G%d", row1, row2, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "N%d", row2);
		sprintf(F, "=((N%d+N36) * L%d * G%d)-O%d", row1, row2, row1, row2);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "M%d", row2);
		sprintf(F, "=((M%d+M36) * L%d * G%d)-O%d-N%d", row1, row2, row1, row2, row2);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "K%d", row2);
		sprintf(F, "=(1-(H%d+I%d+J%d + M%d+N%d+O%d))", 
			row2, 
			row2, 
			row2, 
			row2, 
			row2, 
			row2);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	


		m_excel.m_app.Calculate();


		FractionsLabTrial frac_lab_trial(1);
		frac_lab_trial.n_fractions = 7;
#if USE_FRACTION_DIAMETERS_INTERVAL
		frac_lab_trial.fractions_diameters = new fraction_diameters_interval[frac_lab_trial.n_fractions];
#else
		frac_lab_trial.fractions_diameters = new double [frac_lab_trial.n_fractions];
#endif
		frac_lab_trial.fractions_content = new trial_value [frac_lab_trial.n_fractions];


			
		double val;
						
		sprintf(S, "H%d", row2);//1 - 0.5 мм
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[0].high = 1.0;
			frac_lab_trial.fractions_diameters[0].low = 0.5;
#else
			frac_lab_trial.fractions_diameters[0] = 0.5;
#endif
			frac_lab_trial.fractions_content[0] = 100. * val;
		}

		sprintf(S, "I%d", row2);//0.5-0.25мм
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[1].high = 0.5;
			frac_lab_trial.fractions_diameters[1].low = 0.25;
#else
			frac_lab_trial.fractions_diameters[1] = 0.25;
#endif
			frac_lab_trial.fractions_content[1] = 100. * val;
		}

		sprintf(S, "J%d", row2);//0.25-0.1мм
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[2].high = 0.25;
			frac_lab_trial.fractions_diameters[2].low = 0.1;
#else
			frac_lab_trial.fractions_diameters[2] = 0.1;
#endif
			frac_lab_trial.fractions_content[2] = 100. * val;
		}

		sprintf(S, "K%d", row2);//0.1-0.05мм
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[3].high = 0.1;
			frac_lab_trial.fractions_diameters[3].low = 0.05;
#else
			frac_lab_trial.fractions_diameters[3] = 0.05;
#endif
			frac_lab_trial.fractions_content[3] = 100. * val;
		}

		sprintf(S, "M%d", row2);//0,05 - 0,01 мм
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[4].high = 0.05;
			frac_lab_trial.fractions_diameters[4].low = 0.01;
#else
			frac_lab_trial.fractions_diameters[4] = 0.01;
#endif
			frac_lab_trial.fractions_content[4] = 100. * val;
		}

		sprintf(S, "N%d", row2);//0,01 - 0,005 мм
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[5].high = 0.01;
			frac_lab_trial.fractions_diameters[5].low = 0.005;
#else
			frac_lab_trial.fractions_diameters[5] = 0.005;
#endif
			frac_lab_trial.fractions_content[5] = 100. * val;
		}

		sprintf(S, "O%d", row2); //< 0,005
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[6].high = 0.005;
			frac_lab_trial.fractions_diameters[6].low = -DBL_MAX;
#else
			frac_lab_trial.fractions_diameters[6] = 0.005;
#endif
			frac_lab_trial.fractions_content[6] = 100. * val;
		}


		FractionsLabTrialResults * frac_lab_trial_res = dynamic_cast<FractionsLabTrialResults *>(frac_lab_trial.results);

		if (frac_lab_trial_res)
		{
			frac_lab_trial_res->CalcProperties();					

			char str[1024];
			sprintf(str, "%s %s %s",
				FractionsLabTrialResults::SandSoilsClassToString(frac_lab_trial_res->m_sand_soil_class),
				FractionsLabTrialResults::ClaySoilsClassToString(frac_lab_trial_res->m_clay_soil_class),
				FractionsLabTrialResults::NeodnorodnostToString(frac_lab_trial_res->m_neodnorodnost),
				frac_lab_trial_res->C_u.v);
			
			sprintf(S, "Q%d", row1);

			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant(str));
			m_range.ReleaseDispatch();	

			/*sprintf(S, "N%d:N%d", row1, row2);

			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetHorizontalAlignment(COleVariant("xlCenter"));
			m_range.SetVerticalAlignment(COleVariant("xlDistributed"));
			m_range.ReleaseDispatch();	*/


			sprintf(S, "R%d", row1);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant("C_u"));
			m_range.ReleaseDispatch();	

			sprintf(S, "R%d", row2);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant(frac_lab_trial_res->C_u.v));
			m_range.ReleaseDispatch();	

			sprintf(S, "S%d", row1);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant("d_10"));
			m_range.ReleaseDispatch();	

			sprintf(S, "S%d", row2);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant(frac_lab_trial_res->d_10.v));
			m_range.ReleaseDispatch();	

			sprintf(S, "T%d", row1);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant("d_60"));
			m_range.ReleaseDispatch();	
			
			sprintf(S, "T%d", row2);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant(frac_lab_trial_res->d_60.v));
			m_range.ReleaseDispatch();	
		}

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
			sprintf(dir2, "%s\\PasportsAreometrGranular", dir);
			CreateDirectory(dir2, NULL);


			char fn[4098];
			sprintf(fn, "%s\\%d", dir2, int(lab_n));
			frac_lab_trial.Passport(fn);
		}
	}

	return true;
}

void ExcelAreometrGranular::virSaveToDB()
{
	int nObItem = this->m_lab_view->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return;
	}
	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;

		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return;

		SetGranular setGranular(this->p_database);
		if ( !setGranular.Open(CRecordset::dynaset) )
			return;

		LPDISPATCH pRange; 
		Range10    m_range;

		char S[64];

		int fr = 12;

		for (int r_ = 0; r_ <= 11; r_++)
		{
			int row1 = fr + 2*r_;
			int row2 = fr + 2*r_ + 1;

			sprintf(S, "B%d", row1);

			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			VARIANT labn = m_range.GetValue();
			m_range.ReleaseDispatch();	

			long lab_n = 0;
			if (labn.vt == VT_R8)
			{
				lab_n = long(labn.dblVal);
			}
			else
			{
				break;
			}

			// ID_OBJ ID_KT ID_PROB ID_GRAN

			long ID_KT = -1;
			long ID_PROB = -1;
			if (!setProbGr.IsBOF()) 
			{
				setProbGr.MoveFirst( );
				while(!setProbGr.IsEOF()) 
				{
					if(lab_n == setProbGr.m_LAB_N)
					{
						ID_KT = setProbGr.m_ID_KT;
						ID_PROB = setProbGr.m_ID_PROB;

						sprintf(S, "D%d", row1);
						VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
						m_range.AttachDispatch(pRange);			   
						m_range.SetValue(COleVariant(setProbGr.m_H));
						m_range.ReleaseDispatch();

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
				continue;

			SetKT setKT(this->p_database);
			setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
			if ( !setKT.Open(CRecordset::dynaset) )
				return;
			if (!setKT.IsBOF()) 
			{
				setKT.MoveFirst( );
				if(!setKT.IsEOF()) 
				{
					sprintf(S, "C%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);			   
					m_range.SetValue(COleVariant(setKT.m_NAZVA));
					m_range.ReleaseDispatch();	
				}
			}

			SetGranular setGranular_2(this->p_database);
			setGranular_2.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, ID_KT, ID_PROB);
			if ( !setGranular_2.Open(CRecordset::dynaset) )
				return;

			CString sValues = "", sv;
			if (!setGranular_2.IsBOF()) 
			{
				setGranular_2.MoveFirst( );

				while(!setGranular_2.IsEOF()) 
				{
					sv.Format("ID_GRAN = %d %f\n", setGranular_2.m_ID_GRAN, setGranular_2.m_VAL); 
					sValues += sv;
					setGranular_2.MoveNext(); // to validate record count
				}
			}
			long Granular_RowCount = setGranular_2.GetRecordCount();

			bool to_add = false;

			if (Granular_RowCount)
			{
				CString s;
				s.Format("Данные грансостава по данной пробе грунта уже имеются в базе\n%s\n%s\nЗаменить?", 
					setGranular_2.m_strFilter, sValues);

				if (IDYES == MessageBox(0,s,"ExcelSandGranular::virSaveToDB()", MB_YESNO) )
				{
					if (!setGranular_2.IsBOF()) 
					{
						setGranular_2.MoveFirst( );

						while(!setGranular_2.IsEOF()) 
						{
							setGranular_2.Delete( );
							setGranular_2.MoveNext(); // to validate record count
						}
					}
					to_add = true;
				}
			}
			else
				to_add = true;

			if (to_add)
			{
				
				// ID_OBJ ID_KT ID_PROB ID_GRAN
				/*
				GranularAll_2
				ID_GRAN	NAZVA
				1	10.0-...
				2	2.0-10.0
				3	1.0-2.0
				4	0.5-1.0
				5	0.25-0.5
				6	0.1-0.25
				7	0.05-0.1
				8	0.01-0.05
				9	0.005-0.01
				10	<0.005
				21	5.0 - 10.0
				22	2.0 - 5.0
				23	<0.1
					*/

				double val;						
				sprintf(S, "H%d", row2);//1 - 0.5 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 4, 100. * val);	
				}

				sprintf(S, "I%d", row2);//0.5-0.25мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 5, 100. * val);	
				}

				sprintf(S, "J%d", row2);//0.25-0.1мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 6, 100. * val);	
				}

				sprintf(S, "K%d", row2);//0.1-0.05мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 7, 100. * val);	
				}

				sprintf(S, "M%d", row2);//0,05 - 0,01 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 8, 100. * val);	
				}

				sprintf(S, "N%d", row2);//0,01 - 0,005 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 9, 100. * val);	
				}

				sprintf(S, "O%d", row2); //< 0,005
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 10, 100. * val);	
				}
			}
		}
		int nProbGrItem = this->m_lab_view->GetProbGrItem();
		setProbGr.SetAbsolutePosition(nProbGrItem + 1);        
		CString where;
		where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
			ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
		this->m_lab_view->UpdateGranularListCtrl(where, "");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}