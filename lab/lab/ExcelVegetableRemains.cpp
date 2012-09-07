// ExcelVegetableRemains.cpp: implementation of the ExcelVegetableRemains class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelVegetableRemains.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"

#include "DlgRepeatings.h"

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

ExcelVegetableRemains::ExcelVegetableRemains()
{
}

ExcelVegetableRemains::~ExcelVegetableRemains()
{

}
void ExcelVegetableRemains::InitExt()
{
	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			ext					= "vrc";
			xl_filter_name		= "Vegetable Remains Content";
			xl_form				= "RastitelnyeOstatki";
		}
		break;
	case 3:
	case 6:
		{
			ext					= "vrc3";
			xl_filter_name		= "Vegetable Remains Content";
			xl_form				= "RastitelnyeOstatki3";
		}
		break;
	}
}

bool ExcelVegetableRemains::virCompute(bool)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	char S[64];
	char F[1024];

	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			int fr = 13;
			for (int r = 0; r <= 12; r++)
			{
				int row1 = fr + 2*r;
				int row2 = fr + 2*r + 1;

				sprintf(S, "C%d", row1);

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

				sprintf(S, "J%d", row1);
				sprintf(F, "=G%d-H%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.ReleaseDispatch();	

				// определяем занесена ли в таблицу вторая повторность
				bool use_row_2 = false;
				double v;
				sprintf(S, "G%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "H%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "I%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);

				if (use_row_2)
				{
					sprintf(S, "J%d", row2);
					sprintf(F, "=G%d-H%d", row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();
				}


				sprintf(S, "K%d", row1);
				sprintf(F, "=G%d-I%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.ReleaseDispatch();	

				if (use_row_2)
				{
					sprintf(S, "K%d", row2);
					sprintf(F, "=G%d-I%d", row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}


				sprintf(S, "L%d", row1);
				sprintf(F, "=J%d/K%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.ReleaseDispatch();	

				if (use_row_2)
				{
					sprintf(S, "L%d", row2);
					sprintf(F, "=J%d/K%d", row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}

				if (use_row_2)
				{
					sprintf(S, "M%d", row1);
					sprintf(F, "=0.5*(L%d+L%d)", row1, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}
				else
				{
					sprintf(S, "M%d", row1);
					sprintf(F, "=L%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}



				bool add_cut_from_db = false;
				bool add_compress_from_db = false;
				int nCutItem = 0;
				int nCompItem = 0;
				bool add_stat_zond_from_db = false;
				LabNumber * lab_number = this->m_lab_view->CreateLabNumber(lab_n, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
				if (lab_number)
				{
					LabTrial * lab_trial = lab_number ? lab_number->FindLabTrial(LabTrial::indication::chemical, -1) : NULL;
					if(!lab_trial)
					{
						lab_trial = lab_number ? lab_number->AddNewLabTrial(LabTrial::indication::chemical, 1) : NULL;
					}
					ChemicalLabTrial * chem_trial = dynamic_cast<ChemicalLabTrial *>(lab_trial);
					if (chem_trial)
					{
						double val;
						ChemicalLabTrial chem_lab_trial(1);		
						sprintf(S, "M%d", row1);
						if(ExcelRange_GetValue(m_excel, S, val))
						{
							//chem_lab_trial. = val;
							//chem_trial->vegetable_remains_content = val;
							chem_trial->organic_matters = val;

							ChemicalLabTrialResults * chem_result = dynamic_cast<ChemicalLabTrialResults *>(chem_trial->results);
							if (chem_result)
							{
								chem_result->CalcProperties();
								sprintf(S, "N%d", row1);
								ExcelRange_SetValue(m_excel, S, COleVariant(ChemicalLabTrialResults::ZatorfovannostToString(chem_result->m_zatorfovannost)));
							}
						}
					}
				}
			}
		}
		break;
	case 3:
		{
			int fr = 13;
			for (int r = 0; r <= 8; r++)
			{
				int row1 = fr + 3*r;
				int row2 = fr + 3*r + 1;
				int row3 = fr + 3*r + 2;

				sprintf(S, "C%d", row1);

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

				sprintf(S, "J%d", row1);
				sprintf(F, "=G%d-H%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.ReleaseDispatch();	

				double v;
				// определяем занесена ли в таблицу вторая повторность
				bool use_row_2 = false;
				sprintf(S, "G%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "H%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "I%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);

				// определяем занесена ли в таблицу вторая повторность
				bool use_row_3 = false;
				sprintf(S, "G%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "H%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "I%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);

				if (use_row_2)
				{
					sprintf(S, "J%d", row2);
					sprintf(F, "=G%d-H%d", row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();
				}

				if (use_row_3)
				{
					sprintf(S, "J%d", row3);
					sprintf(F, "=G%d-H%d", row3, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();
				}


				sprintf(S, "K%d", row1);
				sprintf(F, "=G%d-I%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.ReleaseDispatch();	

				if (use_row_2)
				{
					sprintf(S, "K%d", row2);
					sprintf(F, "=G%d-I%d", row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}

				if (use_row_3)
				{
					sprintf(S, "K%d", row3);
					sprintf(F, "=G%d-I%d", row3, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}


				sprintf(S, "L%d", row1);
				sprintf(F, "=J%d/K%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.ReleaseDispatch();	

				if (use_row_2)
				{
					sprintf(S, "L%d", row2);
					sprintf(F, "=J%d/K%d", row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}

				if (use_row_3)
				{
					sprintf(S, "L%d", row3);
					sprintf(F, "=J%d/K%d", row3, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}

				if (use_row_2 && use_row_3)
				{
					sprintf(S, "M%d", row1);
					sprintf(F, "=(L%d+L%d+L%d)/3.0", row1, row2, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}
				else if (use_row_2 && ! use_row_3)
				{
					sprintf(S, "M%d", row1);
					sprintf(F, "=0.5*(L%d+L%d)", row1, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}
				else
				{
					sprintf(S, "M%d", row1);
					sprintf(F, "=L%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.ReleaseDispatch();	
				}



				bool add_cut_from_db = false;
				bool add_compress_from_db = false;
				int nCutItem = 0;
				int nCompItem = 0;
				bool add_stat_zond_from_db = false;
				LabNumber * lab_number = this->m_lab_view->CreateLabNumber(lab_n, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
				if (lab_number)
				{
					LabTrial * lab_trial = lab_number ? lab_number->FindLabTrial(LabTrial::indication::chemical, -1) : NULL;
					if(!lab_trial)
					{
						lab_trial = lab_number ? lab_number->AddNewLabTrial(LabTrial::indication::chemical, 1) : NULL;
					}
					ChemicalLabTrial * chem_trial = dynamic_cast<ChemicalLabTrial *>(lab_trial);
					if (chem_trial)
					{
						double val;
						ChemicalLabTrial chem_lab_trial(1);		
						sprintf(S, "M%d", row1);
						if(ExcelRange_GetValue(m_excel, S, val))
						{
							//chem_lab_trial. = val;
							//chem_trial->vegetable_remains_content = val;
							chem_trial->organic_matters = val;

							ChemicalLabTrialResults * chem_result = dynamic_cast<ChemicalLabTrialResults *>(chem_trial->results);
							if (chem_result)
							{
								chem_result->CalcProperties();
								sprintf(S, "N%d", row1);
								ExcelRange_SetValue(m_excel, S, COleVariant(ChemicalLabTrialResults::ZatorfovannostToString(chem_result->m_zatorfovannost)));
							}
						}
					}
				}
			}
		}
		break;
	}
	return true;
}


void ExcelVegetableRemains::virSaveToDB()
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

		SetFizMeh setFizMeh(this->p_database);
		if ( !setFizMeh.Open(CRecordset::dynaset) )
			return;

		LPDISPATCH pRange; 
		Range10    m_range;

		char S[64];

		int fr, nr, m;
		switch (CDlgRepeatings::s_repeatings)
		{
		case 2:
			{
				fr = 13;
				nr = 12;
				m = 2;
			}
			break;
		case 3:
			{
				fr = 13;
				nr = 8;
				m = 3;
			}
			break;
		}

		for (int r = 0; r <= nr; r++)
		{
			int row1 = fr + m*r;

			sprintf(S, "C%d", row1);

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

			// ID_OBJ ID_KT ID_PROB ID_VYPROB

			long ID_KT = -1;
			long ID_PROB = -1;

			long ID_VYPROB = MEAN_PHYS_VYPROB;
			long ID_PARAM = 50;
			if (!setProbGr.IsBOF()) 
			{
				setProbGr.MoveFirst( );
				while(!setProbGr.IsEOF()) 
				{
					if(lab_n == setProbGr.m_LAB_N)
					{
						ID_KT = setProbGr.m_ID_KT;
						ID_PROB = setProbGr.m_ID_PROB;

						sprintf(S, "E%d", row1);
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
					sprintf(S, "D%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);			   
					m_range.SetValue(COleVariant(setKT.m_NAZVA));
					m_range.ReleaseDispatch();	
				}
			}

			SetFizMeh setFizMeh_2(this->p_database);
			setFizMeh_2.m_strFilter.Format(
				"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
				ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM);
			if ( !setFizMeh_2.Open(CRecordset::dynaset) )
				return;

			double val;						
			sprintf(S, "M%d", row1);
			if(ExcelRange_GetValue(m_excel, S, val))
			{
				int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, lab_n, 
					ID_PARAM, ID_VYPROB, val);
			}
		}

		int nProbGrItem = this->m_lab_view->GetProbGrItem();
		setProbGr.SetAbsolutePosition(nProbGrItem + 1);        
		CString where;
		where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
			ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
		this->m_lab_view->UpdateFizMehListCtrl(where, "ID_VYPROB");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}