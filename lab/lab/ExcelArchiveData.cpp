// ExcelArchiveData.cpp: implementation of the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelArchiveData.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"
#include "SetFizMehAllParam.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelArchiveData::ExcelArchiveData()
{
	rows_per_page = 35;

	first_letter = 'E';	
	npar = 12;
	long _id_params[] = {2,3,1,52,23,24,8,6,50,35,25,26};
	memcpy(id_params, _id_params, npar*sizeof(long));
}

ExcelArchiveData::~ExcelArchiveData()
{

}
void ExcelArchiveData::InitExt()
{
	ext					= "ald";
	xl_filter_name		= "Архивные лабораторные данные";
	xl_form				= "ArchiveLabData";
}
bool ExcelArchiveData::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];
	int fr = 8;

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		setProbGr.m_strSort.Format("LAB_N");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return false;

		if (!setProbGr.IsBOF()) 
		{
			while(!setProbGr.IsEOF()) 
			{
				setProbGr.MoveNext();
			}
		}
		
		long records = setProbGr.GetRecordCount();

		//Если число лабораторных номеров больше 35, надо скопировать таблицу на вторую страницу
		double fpages = double (records) / double (rows_per_page);
		int pages = int(ceil(fpages));

		LPDISPATCH pRange; 
		Range10    m_range;

		sprintf(S, "A1:P42");
		VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
		m_range.AttachDispatch(pRange);		
		for (int p = 1; p < pages; p++)
		{
			int row1 = (rows_per_page + fr - 1) * p + 1;
			sprintf(S, "A%d", row1);
			m_range.Copy();

			LPDISPATCH pRange2; 
			Range10    m_range2;
			VERIFY(pRange2 = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range2.AttachDispatch(pRange2);	
			m_range2.Select();
			m_excel.m_worksheet.Paste();
			m_range2.ReleaseDispatch();	
		}			
		m_range.ReleaseDispatch();	


		int r = fr;
		int n = 0;
		if (!setProbGr.IsBOF()) 
		{
			setProbGr.MoveFirst( );
			while(!setProbGr.IsEOF()) 
			{
				SetKT setKT(this->p_database);
				setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, setProbGr.m_ID_KT);
				if ( setKT.Open(CRecordset::dynaset) )
				{
					if (!setKT.IsBOF()) 
					{
						setKT.MoveFirst( );
						if(!setKT.IsEOF()) 
						{
							sprintf(S, "C%d", r);
							ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));	
						}
					}
				}

				sprintf(S, "B%d", r);							
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_LAB_N));

				sprintf(S, "D%d", r);							
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_H));

				SetFizMeh setFizMeh(this->p_database);
				setFizMeh.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
				if ( !setFizMeh.Open(CRecordset::dynaset) )
					return false;



				double val_from_db; 
				double mean_of_vyprob;

				for (long ipar = 0; ipar < npar; ipar++)
				{
					long ID_PARAM = id_params[ipar];
					sprintf(S, "%c%d",  first_letter+ipar, r);

					int res = setFizMeh.GetMeanParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, 
						val_from_db, mean_of_vyprob);
#if FILL_VAL_FROM_DB
					if (res & 1)
						ExcelRange_SetValue(m_excel, S, COleVariant(val_from_db));

#else
					switch (res)
					{
					case 0:
						{

						}
						break;
					case 1:
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(val_from_db));
						}
						break;
					case 2:
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(mean_of_vyprob));
						}
						break;
					case 3:
						{
							ExcelRange_SetValue(m_excel, S, COleVariant(mean_of_vyprob));
						}
						break;
					}
#endif
				}


				setProbGr.MoveNext();
				
				n++;

				if (n%rows_per_page)
				{
					r++;
				}
				else
				{
					r += fr;
				}
			}
		}


	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
		
	return true;
}


void ExcelArchiveData::virSaveToDB()
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


		char S[64];

		int fr = 8;
		int r = fr;
		for (int n = 0; ; n++)
		{

			double val;

			long LAB_N;
			sprintf(S, "B%d", r);							
			if (!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}
			else
			{
				LAB_N = long(val);
			}

			SetProbGr setProbGr(this->p_database);
			setProbGr.m_strFilter.Format("ID_OBJ = %d and LAB_N = %d", ID_OBJ, LAB_N);
			setProbGr.m_strSort.Format("ID_KT, ID_PROB");
			setProbGr.m_strSort.Format("LAB_N");
			if (setProbGr.Open(CRecordset::dynaset) )
			{
				// ID_OBJ ID_KT ID_PROB ID_VYPROB

				long ID_KT = -1;
				long ID_PROB = -1;

				long ID_VYPROB = MEAN_PHYS_VYPROB;

				if (!setProbGr.IsBOF()) 
				{
					setProbGr.MoveFirst( );
					while(!setProbGr.IsEOF()) 
					{
						if(LAB_N == setProbGr.m_LAB_N)
						{
							ID_KT = setProbGr.m_ID_KT;
							ID_PROB = setProbGr.m_ID_PROB;
							for (long ipar = 0; ipar < npar; ipar++)
							{
								long ID_PARAM = id_params[ipar];
								sprintf(S, "%c%d",  first_letter+ipar, r);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									SetFizMeh setFizMeh_2(this->p_database);
									setFizMeh_2.m_strFilter.Format(
										"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
										ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM);
									if ( !setFizMeh_2.Open(CRecordset::dynaset) )
										return;

									int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, LAB_N, 
										ID_PARAM, ID_VYPROB, val);
								}
							}

							break;
						}
						setProbGr.MoveNext();
					}
				}
			}


			if ((n+1)%rows_per_page)
			{
				r++;
			}
			else
			{
				r += fr;
			}
		}
		/*int nProbGrItem = this->m_lab_view->GetProbGrItem();
		setProbGr.SetAbsolutePosition(nProbGrItem + 1);        
		CString where;
		where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
			ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
		this->m_lab_view->UpdateFizMehListCtrl(where, "ID_VYPROB");*/
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}