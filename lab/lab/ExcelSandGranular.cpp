// ExcelSandGranular.cpp: implementation of the ExcelSandGranular class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelSandGranular.h"
#include "labView.h"
#include "SetObject.h"
#include "SetGranular.h"
#include "SetProbGr.h"


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

ExcelSandGranular::ExcelSandGranular()
{
}

ExcelSandGranular::~ExcelSandGranular()
{

}
void ExcelSandGranular::InitExt()
{
	ext					= "sgn";
	xl_filter_name		= "Sand Granular";
	xl_form				= "SandSoilGranular";
}

bool ExcelSandGranular::virCompute(bool)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	char S[64];
	char F[1024];

	int fr = 12;

	for (int r_ = 0; r_ <= 12; r_++)
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

		sprintf(S, "E%d", row2);
		sprintf(F, "=E%d/C%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "F%d", row2);
		sprintf(F, "=F%d/C%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "G%d", row2);
		sprintf(F, "=G%d/C%d", row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "I%d", row1);
		sprintf(F, "=(1-(E%d + F%d + G%d)) / D%d", 
			row2, 
			row2, 
			row2, 
			row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetFormula(COleVariant(F));
		m_range.SetNumberFormat(COleVariant("0.00E+00"));
		m_range.ReleaseDispatch();	

		sprintf(S, "H%d", row2);
		sprintf(F, "=I%d*H%d", 
			row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "J%d", row2);
		sprintf(F, "=I%d*J%d", 
			row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "K%d", row2);
		sprintf(F, "=I%d*K%d", 
			row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "L%d", row2);
		sprintf(F, "=I%d*L%d", 
			row1, row1);

		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.SetValue(COleVariant(F));
		m_range.ReleaseDispatch();	

		sprintf(S, "M%d", row2);
#if 0
		sprintf(F, "=(1-(СУММ(E%d:H%d;J%d:L%d)))", 
			row2, 
			row2, 
			row2, 
			row2);
#else
		sprintf(F, "=(1-(E%d+F%d+G%d+H%d + J%d+K%d+L%d))", 
			row2, 
			row2, 
			row2, 
			row2, 
			row2, 
			row2, 
			row2);
#endif


		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		m_range.SetFormula(COleVariant(F));
		m_range.SetNumberFormat(COleVariant("0.00%"));
		m_range.ReleaseDispatch();	

		m_excel.m_app.Calculate();


		FractionsLabTrial frac_lab_trial(1);
		frac_lab_trial.n_fractions = 8;
#if USE_FRACTION_DIAMETERS_INTERVAL
		frac_lab_trial.fractions_diameters = new fraction_diameters_interval[frac_lab_trial.n_fractions];
#else
		frac_lab_trial.fractions_diameters = new double [frac_lab_trial.n_fractions];
#endif
		frac_lab_trial.fractions_content = new trial_value [frac_lab_trial.n_fractions];


			
		double val;
						
		sprintf(S, "E%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[0].high = DBL_MAX;
			frac_lab_trial.fractions_diameters[0].low = 10.0;
#else
			frac_lab_trial.fractions_diameters[0] = 10.0;
#endif
			frac_lab_trial.fractions_content[0] = 100. * val;
		}

		sprintf(S, "F%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[1].high = 10.0;
			frac_lab_trial.fractions_diameters[1].low = 5.0;
#else
			frac_lab_trial.fractions_diameters[1] = 5.0;
#endif
			frac_lab_trial.fractions_content[1] = 100. * val;
		}

		sprintf(S, "G%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[2].high = 5.0;
			frac_lab_trial.fractions_diameters[2].low = 2.0;
#else
			frac_lab_trial.fractions_diameters[2] = 2.0;
#endif
			frac_lab_trial.fractions_content[2] = 100. * val;
		}

		sprintf(S, "H%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[3].high = 2.0;
			frac_lab_trial.fractions_diameters[3].low = 1.0;
#else
			frac_lab_trial.fractions_diameters[3] = 1.0;
#endif
			frac_lab_trial.fractions_content[3] = 100. * val;
		}

		sprintf(S, "J%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[4].high = 1.0;
			frac_lab_trial.fractions_diameters[4].low = 0.5;
#else
			frac_lab_trial.fractions_diameters[4] = 0.5;
#endif
			frac_lab_trial.fractions_content[4] = 100. * val;
		}

		sprintf(S, "K%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[5].high = 0.5;
			frac_lab_trial.fractions_diameters[5].low = 0.25;
#else
			frac_lab_trial.fractions_diameters[5] = 0.25;
#endif
			frac_lab_trial.fractions_content[5] = 100. * val;
		}

		sprintf(S, "L%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[6].high = 0.25;
			frac_lab_trial.fractions_diameters[6].low = 0.1;
#else
			frac_lab_trial.fractions_diameters[6] = 0.1;
#endif
			frac_lab_trial.fractions_content[6] = 100. * val;
		}

		sprintf(S, "M%d", row2);
		if(ExcelRange_GetValue(m_excel, S, val))
		{
#if USE_FRACTION_DIAMETERS_INTERVAL
			frac_lab_trial.fractions_diameters[7].high = 0.1;
			frac_lab_trial.fractions_diameters[7].low = -DBL_MAX;
#else
			frac_lab_trial.fractions_diameters[7] = 0.1;
#endif
			frac_lab_trial.fractions_content[7] = 100. * val;
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
			
			sprintf(S, "N%d", row1);

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

			sprintf(S, "P%d", row1);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant("d_10"));
			m_range.ReleaseDispatch();	

			sprintf(S, "P%d", row2);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant(frac_lab_trial_res->d_10.v));
			m_range.ReleaseDispatch();	

			sprintf(S, "Q%d", row1);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.SetValue(COleVariant("d_60"));
			m_range.ReleaseDispatch();	
			
			sprintf(S, "Q%d", row2);
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
			sprintf(dir2, "%s\\PasportsSandGranular", dir);
			CreateDirectory(dir2, NULL);

			char fn[4098];
			sprintf(fn, "%s\\%d", dir2, int(lab_n));
			frac_lab_trial.Passport(fn);
		}
	}
	return true;
}
void ExcelSandGranular::virSaveToDB()
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

		for (int r_ = 0; r_ <= 12; r_++)
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
				break;

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
				sprintf(S, "E%d", row2);//> 10 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 1, 100. * val);	
				}

				sprintf(S, "F%d", row2);//10-5 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 21, 100. * val);	
				}

				sprintf(S, "G%d", row2);//5-2 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 22, 100. * val);	
				}

				sprintf(S, "H%d", row2);//2-1 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 3, 100. * val);	
				}

				sprintf(S, "J%d", row2);//1-0,5 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 4, 100. * val);	
				}

				sprintf(S, "K%d", row2);//0,5-0,25
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 5, 100. * val);	
				}

				sprintf(S, "L%d", row2);//0,25-0,1
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 6, 100. * val);	
				}

				sprintf(S, "M%d", row2);//< 0,1 мм
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB, 23, 100. * val);	
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