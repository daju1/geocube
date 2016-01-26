// ExcelArchiveData.cpp: implementation of the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelArchiveCaspGeo.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"
#include "SetFizMehAllParam.h"
#include "SetGranular.h"
#include "../../excel_connect/src/ExcelColChar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelArchiveCaspGeo::ExcelArchiveCaspGeo()
{

	first_letter = 'A';	

	npar = 9;
	long _id_params[]     = {1,2,3,6, 8,30,53,27,29};
	memcpy(id_params, _id_params, npar*sizeof(long));
	size_t _letter_cols[] = {3,4,5,9,10,27,28,29,30};
	memcpy(letter_cols, _letter_cols, npar*sizeof(size_t));

	ngran = 11;
	long _id_grans[]           = { 1,21,22, 3, 4, 5, 6, 7, 8, 9,10};
	memcpy(id_grans, _id_grans, ngran*sizeof(long));
	size_t _letter_cols_gran[] = {16,17,18,19,20,21,22,23,24,25,26};
	memcpy(letter_cols_grans, _letter_cols_gran, ngran*sizeof(size_t));
}

ExcelArchiveCaspGeo::~ExcelArchiveCaspGeo()
{

}
void ExcelArchiveCaspGeo::InitExt()
{
	ext					= "casp";
	xl_filter_name		= "Архивные лабораторные данные";
	xl_form				= "ArchiveLabCaspGeo";
}
bool ExcelArchiveCaspGeo::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];
	int fr = 23;

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
							sprintf(S, "B%d", r);
							ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));	
						}
					}
				}

				sprintf(S, "A%d", r);							
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_LAB_N));

				sprintf(S, "C%d", r);							
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_H));

				SetFizMeh setFizMeh(this->p_database);
				setFizMeh.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
					ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
				if ( !setFizMeh.Open(CRecordset::dynaset) )
					return false;

				SetGranular setGranular(this->p_database);
				setGranular.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
					ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
				if (setGranular.Open(CRecordset::dynaset) )
					return false;


				double val_from_db; 
				double mean_of_vyprob;

				for (long ipar = 0; ipar < npar; ipar++)
				{
					long ID_PARAM = id_params[ipar];
					size_t letter_col   = this->letter_cols[ipar];

					ExcelColChar ecc(first_letter);
					sprintf(S, "%s%d",  ecc.Get(letter_col), r);

					int res = setFizMeh.GetMeanParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, 
						val_from_db, mean_of_vyprob);


					if (res & 1)
						ExcelRange_SetValue(m_excel, S, COleVariant(val_from_db));
				}

				for (long igran = 0; igran < ngran; igran++)
				{
					long ID_GRAN = id_grans[igran];
					size_t letter_col_gran   = this->letter_cols_grans[0];

					ExcelColChar ecc(first_letter);
					sprintf(S, "%s%d",  ecc.Get(letter_col_gran), r);

					int res = setGranular.GetGran(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_GRAN, 
						val_from_db);

					if (res & 1)
						ExcelRange_SetValue(m_excel, S, COleVariant(val_from_db));
				}


				setProbGr.MoveNext();
				
				n++;				
				r++;			
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


void ExcelArchiveCaspGeo::virSaveToDB()
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

		int fr = 23;
		int r = fr;
		for (int n = 0; ; n++)
		{

			double val;

			long LAB_N;
			sprintf(S, "A%d", r);							
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
								size_t letter_col   = this->letter_cols[ipar];

								ExcelColChar ecc(first_letter);
								sprintf(S, "%s%d",  ecc.Get(letter_col), r);

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


							for (long igran = 0; igran < ngran; igran++)
							{
								long ID_GRAN = id_grans[igran];
								size_t letter_col_gran   = this->letter_cols_grans[igran];

								ExcelColChar ecc(first_letter);
								sprintf(S, "%s%d",  ecc.Get(letter_col_gran), r);

								if (ExcelRange_GetValue(m_excel, S, val))
								{
									SetGranular setGranular(this->p_database);
									setGranular.m_strFilter.Format(
										"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_GRAN = %d", 
										ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_GRAN);
									if (!setGranular.Open(CRecordset::dynaset) )
										return;

									int res = setGranular.ReplaceGran(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, LAB_N, ID_GRAN, 
										val);
								}
							}


							break;
						}
						setProbGr.MoveNext();
					}
				}
			}


			r++;
		
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