// ExcelArchiveCut.cpp: implementation of the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelArchiveCut.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"
#include "SetZriz0.h"
#include "SetZriz.h"
#include "SetZriz_tbl.h"
#include "SetFizMehAllParam.h"

#include "../../excel_connect/src/ExcelColChar.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <math.h>


void DeleteFilterRelatedDataFrom(CRecordset * set, CString filter);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelArchiveCut::ExcelArchiveCut()
{
	m_to_save_also_physical = false;
	m_to_fill_all_lab_numbers = false;
	m_to_fill_all_lab_numbers_as_2_colomns = false;// если мы хотим в каждом лабораторном номере давать свои вертикальные нагрузки 
	m_to_fill_all_lab_numbers_as_3_vyprob = false;// если мы хотим каждое кольцо отобразить отдельно со своими физсвойствами
	rows_per_page = 43;
	cols_per_page = 10;
	first_letter = 'F';

	npar = 7;
	long _id_params[] = {2,3,1,8,6,50,35};
	long _param_rows[] = {7,8,9,10,11,12,13};

	memcpy(id_params, _id_params, npar*sizeof(long));
	memcpy(param_rows, _param_rows, npar*sizeof(long));
}

ExcelArchiveCut::~ExcelArchiveCut()
{

}
void ExcelArchiveCut::InitExt()
{
	ext					= "azd";
	xl_filter_name		= "Архивные данные среза";
	xl_form				= "ArchiveCutData";
}
void ExcelArchiveCut::FillReList(int & n, int & fr, char & letter)
{
	if (this->m_to_fill_all_lab_numbers_as_3_vyprob && !m_to_fill_all_lab_numbers_as_2_colomns)
	{
		bool list = (!((n+1)%cols_per_page));
		bool list3 = (!((n+2)%cols_per_page));

		if (list || list3)
		{
			n = 0;
			fr += rows_per_page;
			letter = first_letter;
		}
	}
	else if (m_to_fill_all_lab_numbers_as_2_colomns)
	{
		bool list = (!((n+1)%cols_per_page));
		if (list)// не переносим две кривые на след страницу
		{
			n = 0;
			fr += rows_per_page;
			letter = first_letter;
		}
	}
}
void ExcelArchiveCut::FillIncrement(int & n, int & fr, char & letter)
{
	if (m_to_fill_all_lab_numbers_as_3_vyprob && !m_to_fill_all_lab_numbers_as_2_colomns)
	{
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
	}
	else if (m_to_fill_all_lab_numbers_as_2_colomns)
	{
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
	}
	else
	{
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
	}
}
void ExcelArchiveCut::FillZriz_tbl(SetZriz & setZriz, int & n, int & fr, char & letter, int & p)
{
	char S[64];

	SetZriz_tbl setZriz_tbl(this->p_database);
	setZriz_tbl.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
		setZriz.m_ID_OBJ, setZriz.m_ID_KT, setZriz.m_ID_PROB, setZriz.m_ID_VYPROB);
	setZriz_tbl.m_strSort.Format("ID_VYPROB, SIGMA");
	if (setZriz_tbl.Open(CRecordset::dynaset) )
	{
		int r_TAU = fr + 23;

		int r_W_do = fr + 26;													
		int r_Ro_do = fr + 29;	

		int r_W_po_upl = fr + 32;													
		int r_Ro_po_upl = fr + 35;	

		int r_W_after = fr + 38;
		int r_Ro_after = fr + 41;

		if (false)
		{
e_correct_1:
			// очищаем не в том месте заполненные клетки
			r_TAU = /*min_sigma == 0 ? fr + 18 :*/ fr + 23;
			//r2 = min_sigma == 0 ? fr + 30 : fr + 31;
			if (!setZriz_tbl.IsBOF()) 
			{
				setZriz_tbl.MoveFirst();
				while(!setZriz_tbl.IsEOF()) 
				{
					if(setZriz_tbl.m_SIGMA >= 0.0)
					{

						if (setZriz_tbl.m_SIGMA != 0.0)
						{
							sprintf(S, "%c%d", letter, r_TAU);
							ExcelRange_SetValue(m_excel, S, COleVariant(""));
						}

						r_TAU++; //r2++;
					}
					/*else
					{
						sprintf(S, "%c%d", letter, fr+29);
						ExcelRange_SetValue(m_excel, S, COleVariant(""));
					}*/
					setZriz_tbl.MoveNext();
				}
			}						
			// копируем дополниельно ещё одну таблицу из резервного временного файла
			ExcelArchiveCut m_excel_temp;
			CString dir = m_excel.m_app.GetDefaultFilePath();
			CString fn_temp = "TempExcelArchiveCut";
			CString file_temp = m_excel_temp.LoadFormNew(dir, fn_temp);

			LPDISPATCH pRange_temp; 
			Range10    m_range_temp;

			sprintf(S, "A1:P%d", rows_per_page);
			VERIFY(pRange_temp = m_excel_temp.m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range_temp.AttachDispatch(pRange_temp);		
			m_range_temp.Copy();
			m_range_temp.ReleaseDispatch();	



			m_excel.m_worksheet.Activate();

			int row1 = rows_per_page * p + 1;
			sprintf(S, "A%d", row1);

			LPDISPATCH pRange2; 
			Range10    m_range2;
			VERIFY(pRange2 = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range2.AttachDispatch(pRange2);	
			m_range2.Select();
			m_excel.m_worksheet.Paste();
			m_range2.ReleaseDispatch();	

			m_excel_temp.m_excel.m_app.SetCutCopyMode(0);
			m_excel_temp.DisconnectExcel();


			DeleteFile(file_temp);


			// инкременируем страницу
			p++;

			// устанавливаем строки и колонки

			n=0;
			//if (!(n%cols_per_page))
			{
				fr += rows_per_page;
				letter = first_letter;
			}
			r_TAU = /*min_sigma == 0 ? fr + 18 :*/ fr + 23;
			//r2 = min_sigma == 0 ? fr + 30 : fr + 31;
		}								

		double sigma;
		int il = m_to_fill_all_lab_numbers_as_2_colomns ? 1 : 0;
		char letter_sigma = m_to_fill_all_lab_numbers_as_2_colomns ? letter : 'D';
		if (!setZriz_tbl.IsBOF()) 
		{
			setZriz_tbl.MoveFirst();
			while(!setZriz_tbl.IsEOF()) 
			{									
				sprintf(S, "%c%d", letter_sigma, r_TAU);
				if (ExcelRange_GetValue(m_excel, S, sigma))
				{
					if (sigma != setZriz_tbl.m_SIGMA)
					{
						CString s;
						s.Format(
							"В лабораторном номере %d нормальное давление среза не соответствует строке таблицы\n"
							"sigma %f != setZriz_tbl.m_SIGMA %f",
							/*LAB_N*/-1, sigma, setZriz_tbl.m_SIGMA);
						//AfxMessageBox(s);
						goto e_correct_1;
					}
				}
				else
					ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_SIGMA));
		



		
				sprintf(S, "%c%d", letter+il, r_TAU);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_TAU));
			

				sprintf(S, "%c%d", letter+il, r_W_do);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_W_do));
				
				sprintf(S, "%c%d", letter+il, r_W_po_upl);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_W_po_upl));				
				
				sprintf(S, "%c%d", letter+il, r_W_after);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_W_after));

				sprintf(S, "%c%d", letter+il, r_Ro_do);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_Ro_do));
				
				sprintf(S, "%c%d", letter+il, r_Ro_po_upl);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_Ro_po_upl));
				
				sprintf(S, "%c%d", letter+il, r_Ro_after);
				ExcelRange_SetValue(m_excel, S, COleVariant(setZriz_tbl.m_Ro_after));


				r_TAU++; //r2++;

				r_W_do++;													
				r_W_po_upl++;													
				r_W_after++;	

				r_Ro_do++;													
				r_Ro_po_upl++;													
				r_Ro_after++;
			
				if (m_to_fill_all_lab_numbers_as_3_vyprob 
					&& 
					!m_to_fill_all_lab_numbers_as_2_colomns) 
					il++;
				setZriz_tbl.MoveNext();
			}
		}
	}

	sprintf(S, "%c%d", letter, fr+16);
	ExcelRange_SetValue(m_excel, S, COleVariant(setZriz.m_ID_STAN));	

	sprintf(S, "%c%d", letter, fr+18);
	ExcelRange_SetValue(m_excel, S, COleVariant(setZriz.m_ID_HID));	

	sprintf(S, "%c%d", letter, fr+20);
	ExcelRange_SetValue(m_excel, S, COleVariant(setZriz.m_ID_SHEMA));	

	sprintf(S, "%c%d", letter, fr+14);
	ExcelRange_SetValue(m_excel, S, COleVariant(setZriz.m_D));	

	sprintf(S, "%c%d", letter, fr+15);
	ExcelRange_SetValue(m_excel, S, COleVariant(setZriz.m_H));	

}
void ExcelArchiveCut::FillProbGrKT(long ID_OBJ, long ID_KT, long ID_PROB, int & n, int & fr, char & letter, long id_cut_vyprob)
{
	char S[64];

	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", 
		ID_OBJ, ID_KT);
	if ( setKT.Open(CRecordset::dynaset) )
	{
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			if(!setKT.IsEOF()) 
			{
				CString nazva = "";
				int foof = setKT.m_NAZVA.FindOneOf("0123456789");
				if (foof > -1)
				{
					nazva = setKT.m_NAZVA.Mid(foof);
				}
				CString kt_type = "";
				if (foof == 0)
				{
					switch(setKT.m_ID_TYP)
					{
					case 1:
						{
							kt_type = "разв.скв.";
						}
						break;
					case 2:
						{
							kt_type = "техн.скв.";
						}
						break;
					case 3:
						{
							kt_type = "гидр.скв.";
						}
						break;
					case 4:
						{
							kt_type = "шурф";
						}
						break;
					case 5:
						{
							kt_type = "ТСЗ";
						}
						break;
					case 6:
						{
							kt_type = "тч.опр.гр.";
						}
						break;
					}
				}
				else if (foof > 0)
				{
					kt_type = setKT.m_NAZVA.Left(foof);
				}

				sprintf(S, "%c%d", letter, fr+4);
				ExcelRange_SetValue(m_excel, S, COleVariant(kt_type));	
				sprintf(S, "%c%d", letter, fr+5);
				ExcelRange_SetNumberFormat(m_excel, S, "@", false);
				ExcelRange_SetValue(m_excel, S, COleVariant(nazva));	

			}
		}
	}

	long LAB_N = -1;

	SetProbGr setProbGr(this->p_database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, ID_KT, ID_PROB);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	setProbGr.m_strSort.Format("LAB_N");
	if (setProbGr.Open(CRecordset::dynaset) )
	{
		if (!setProbGr.IsBOF()) 
		{
			setProbGr.MoveFirst();
			if(!setProbGr.IsEOF()) 
			{
				sprintf(S, "%c%d", letter, fr+3);
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_LAB_N));
				LAB_N = setProbGr.m_LAB_N;

				sprintf(S, "%c%d", letter, fr+6);
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_H));

				SetFizMeh setFizMeh(this->p_database);
				setFizMeh.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
					ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
				if (setFizMeh.Open(CRecordset::dynaset) )
				{
					for (long ipar = 0; ipar < npar; ipar++)
					{
						long ID_PARAM = id_params[ipar];

						double val_from_db; 
						double mean_of_vyprob;
						if (m_to_fill_all_lab_numbers_as_3_vyprob)
						{
							long ID_VYPROB_1 = GetFizMehVyprobForCut(this->p_database, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, id_cut_vyprob, 1);
							long ID_VYPROB_2 = GetFizMehVyprobForCut(this->p_database, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, id_cut_vyprob, 2);
							long ID_VYPROB_3 = GetFizMehVyprobForCut(this->p_database, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, id_cut_vyprob, 3);

							double val_1; 
							double val_2; 
							double val_3; 
							int res_1 = setFizMeh.GetParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, ID_VYPROB_1,
								val_1);
							int res_2 = setFizMeh.GetParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, ID_VYPROB_2,
								val_2);
							int res_3 = setFizMeh.GetParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, ID_VYPROB_3,
								val_3);

							bool list = (!((n+1)%cols_per_page));
							bool list3 = (!((n+2)%cols_per_page));

							if (list || list3)
							{
								n = 0;
								fr += rows_per_page;
								letter = first_letter;
							}


							int r2 = fr + param_rows[ipar];
							sprintf(S, "%c%d",  letter, r2);
							if (res_1)
							{
								ExcelRange_SetValue(m_excel, S, COleVariant(val_1));
							}

							sprintf(S, "%c%d",  letter + 1, r2);
							if (res_2)
							{							
								ExcelRange_SetValue(m_excel, S, COleVariant(val_2));
							}

							sprintf(S, "%c%d",  letter + 2, r2);
							if (res_3)
							{							
								ExcelRange_SetValue(m_excel, S, COleVariant(val_3));
							}

							if (!res_1 && !res_2 && !res_3)
							{
								sprintf(S, "%c%d",  letter, r2);
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

								sprintf(S, "%c%d:%c%d", letter, r2, letter+2, r2);
								ExcelRange_SetMerge(m_excel, S, true);
							}
						}
						else
						{
							int r2 = fr + param_rows[ipar];
							sprintf(S, "%c%d",  letter, fr + param_rows[ipar]);
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
							if (this->m_to_fill_all_lab_numbers_as_2_colomns)
							{
								sprintf(S, "%c%d:%c%d", letter, r2, letter+1, r2);
								ExcelRange_SetMerge(m_excel, S, true);
							}
						}
					}
				}
			}
		}						
	}


	if (m_to_fill_all_lab_numbers_as_3_vyprob)
	{								
		bool list = (!((n+1)%cols_per_page));
		bool list3 = (!((n+1)%cols_per_page));
		if (!list && !list3)
		{		
			// лаб номер и его атрибуты
			sprintf(S, "%c%d:%c%d", letter, fr+3, letter + 2, fr+6);
			ExcelRange_SetMerge(m_excel, S, true);
		}
	}
	if (this->m_to_fill_all_lab_numbers_as_3_vyprob)
	{
		//диаметр и высота кольца
		sprintf(S, "%c%d:%c%d", letter, fr+14, letter+2, fr+15);
		ExcelRange_SetMerge(m_excel, S, true);

		//ссостояние
		sprintf(S, "%c%d:%c%d", letter, fr+16, letter+2, fr+17);
		ExcelRange_SetMerge(m_excel, S);

		//ход
		sprintf(S, "%c%d:%c%d", letter, fr+18, letter+2, fr+19);
		ExcelRange_SetMerge(m_excel, S);

		//схема
		sprintf(S, "%c%d:%c%d", letter, fr+20, letter+2, fr+22);
		ExcelRange_SetMerge(m_excel, S);		
	}

	if (m_to_fill_all_lab_numbers_as_2_colomns)
	{								
		bool list = (!((n+1)%cols_per_page));
		if (!list)
		{						
			// лаб номер и его атрибуты
			sprintf(S, "%c%d:%c%d", letter, fr+3, letter + 1, fr+6);
			ExcelRange_SetMerge(m_excel, S, true);
		}
	}

	if (this->m_to_fill_all_lab_numbers_as_2_colomns)
	{
		//диаметр и высота кольца
		sprintf(S, "%c%d:%c%d", letter, fr+14, letter+1, fr+15);
		ExcelRange_SetMerge(m_excel, S, true);

		//ссостояние
		sprintf(S, "%c%d:%c%d", letter, fr+16, letter+1, fr+17);
		ExcelRange_SetMerge(m_excel, S);

		//ход
		sprintf(S, "%c%d:%c%d", letter, fr+18, letter+1, fr+19);
		ExcelRange_SetMerge(m_excel, S);

		//схема
		sprintf(S, "%c%d:%c%d", letter, fr+20, letter+1, fr+22);
		ExcelRange_SetMerge(m_excel, S);		
	}
}


bool ExcelArchiveCut::virFill()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;


		//long different_vyprob = 0;
		//long zriz_records = 0;
		//long empty_labn_records = 0;

		SetProbGr setProbGr_all(this->p_database);
		setProbGr_all.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr_all.m_strSort.Format("ID_KT, ID_PROB");
		setProbGr_all.m_strSort.Format("LAB_N");
		if (setProbGr_all.Open(CRecordset::dynaset) )
		{

			//long Records = 0;
			int n = 0;
			int pages = 1;


			if (!setProbGr_all.IsBOF()) 
			{
				setProbGr_all.MoveFirst();
				while(!setProbGr_all.IsEOF()) 
				{
					SetZriz setZriz(this->p_database);
					setZriz.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
						ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB);
					setZriz.m_strSort.Format("ID_KT, ID_PROB");
					if (setZriz.Open(CRecordset::dynaset) )
					{
						if (!setZriz.IsBOF()) 
						{
							setZriz.MoveFirst();
							while(!setZriz.IsEOF()) 
							{
								setZriz.MoveNext();
							}
						}		 
						long record_count = setZriz.GetRecordCount();
						if (record_count > -1)							
						{
							for (int irec = 0; irec < record_count; irec++)
							{
								int iv = 1;
								if (this->m_to_fill_all_lab_numbers_as_3_vyprob)
									iv = 3;
								if (this->m_to_fill_all_lab_numbers_as_2_colomns)
									iv = 2;
								for (int i = 0; i < iv; i++)
								{
									bool list = (!((n+1)%cols_per_page));

									if (list)
									{
										n = 0;
										pages++;
									}
									else
										n++;
								}
							}
						}
						if (record_count <= 0)
						{
							if (this->m_to_fill_all_lab_numbers)
							{
								int iv = 1;
								if (this->m_to_fill_all_lab_numbers_as_3_vyprob)
									iv = 3;
								if (this->m_to_fill_all_lab_numbers_as_2_colomns)
									iv = 2;
								for (int i = 0; i < iv; i++)
								{
									bool list = (!((n+1)%cols_per_page));

									if (list)
									{
										n = 0;
										pages++;
									}
									else
										n++;
								}
							}
						}
					}
					setProbGr_all.MoveNext();
				}
			}	

			//long Records = /*this->save_different_vyprob ? different_vyprob :*/ zriz_records;
										
			/*if (this->m_to_fill_all_lab_numbers)
			{
				Records += empty_labn_records;
				if (m_to_fill_all_lab_numbers_as_3_vyprob)
					Records += 2*empty_labn_records;
			}*/

	//sprintf(S, "R1");
	//ExcelRange_SetValue(m_excel, S, COleVariant(Records));	


			//Если число лабораторных номеров больше 35, надо скопировать таблицу на вторую страницу
			//double fpages = double (Records) / double (cols_per_page);
			//int pages = int(ceil(fpages));

			LPDISPATCH pRange; 
			Range10    m_range;

			sprintf(S, "A1:P%d", rows_per_page);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);		
			m_range.Copy();
			m_range.ReleaseDispatch();	


			int p = 1;
			for (p = 1; p < pages; p++)
			{
				int row1 = rows_per_page * p + 1;
				sprintf(S, "A%d", row1);

				LPDISPATCH pRange2; 
				Range10    m_range2;
				VERIFY(pRange2 = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range2.AttachDispatch(pRange2);	
				m_range2.Select();
				m_excel.m_worksheet.Paste();
				m_range2.ReleaseDispatch();	
			}


			m_excel.m_app.SetCutCopyMode(0);

			n = 0;
			
			char letter = first_letter;
			int fr = 0;

			if (!setProbGr_all.IsBOF()) 
			{
				setProbGr_all.MoveFirst();
				while(!setProbGr_all.IsEOF()) 
				{
					SetZriz setZriz(this->p_database);
					setZriz.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
						ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB);
					setZriz.m_strSort.Format("ID_KT, ID_PROB");
					if (setZriz.Open(CRecordset::dynaset) )
					{
						if (!setZriz.IsBOF()) 
						{
							setZriz.MoveFirst( );
							while(!setZriz.IsEOF()) 
							{							
								long ID_VYPROB = setZriz.m_ID_VYPROB;

								this->FillReList(n, fr, letter);
								this->FillZriz_tbl(setZriz, n, fr, letter, p);
								long id_cut_vyprob = setZriz.m_ID_VYPROB;
								this->FillProbGrKT(ID_OBJ, setZriz.m_ID_KT, setZriz.m_ID_PROB, n, fr, letter, id_cut_vyprob);
								this->FillIncrement(n, fr, letter);
								
								setZriz.MoveNext();
							}
						}
						long record_count = setZriz.GetRecordCount();
						if (record_count <= 0 && this->m_to_fill_all_lab_numbers)
						{			
							this->FillReList(n, fr, letter);
							long id_cut_vyprob = 1;
							this->FillProbGrKT(ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB, n, fr, letter, id_cut_vyprob);
							this->FillIncrement(n, fr, letter);

						}
					}
					setProbGr_all.MoveNext();
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


void ExcelArchiveCut::virSaveToDB()
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

		//char letter = first_letter;
		ExcelColChar ecc(first_letter);

		char S[64];
		CString str;
		bool Ro_po_upl_as_e = false;

		if (ExcelRange_GetStringValue(m_excel, "B36", str))
		{
			Ro_po_upl_as_e = false;
		}
		if (ExcelRange_GetStringValue(m_excel, "B37", str))
		{
			Ro_po_upl_as_e = true;
		}

		int fr = 0;
		for (int n = 0; ; )
		{
			double val;

			long LAB_N;
			//sprintf(S, "%c%d", letter, fr+3);
			sprintf(S, "%s%d", ecc.Get(), fr+3);
			if (!ExcelRange_GetValue(m_excel, S, val))
			{
				fr += rows_per_page;
				//letter = first_letter;
				ecc.Init(first_letter);

				n = 0;
				//sprintf(S, "%c%d", letter, fr+3);
				sprintf(S, "%s%d", ecc.Get(), fr+3);
				if (!ExcelRange_GetValue(m_excel, S, val))
				{
					break;
				}
				else
				{
					LAB_N = long(val);
				}
			}
			else
			{
				LAB_N = long(val);
			}
			int merged_cols = 1;
			int row1, col1, row2, col2;
			if (ExcelRange_GetMergeArea_and_parse_adress(m_excel, S, row1, col1, row2, col2))
			{
				merged_cols = col2 - col1 + 1;
			}



			double 
				H = 0.0,
				D = 0.0;

			bool H_got = false, D_got = false;

			//sprintf(S, "%c%d", letter, fr+14);							
			sprintf(S, "%s%d", ecc.Get(), fr+14);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				D = val;
				D_got = true;
			}

			//sprintf(S, "%c%d", letter, fr+15);							
			sprintf(S, "%s%d", ecc.Get(), fr+15);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				H = val;
				H_got = true;
			}

			bool found_lab_n = false;


			SetProbGr setProbGr(this->p_database);
			setProbGr.m_strFilter.Format("ID_OBJ = %d and LAB_N = %d", ID_OBJ, LAB_N);
			setProbGr.m_strSort.Format("LAB_N");
			if (setProbGr.Open(CRecordset::dynaset) )
			{
				long ID_KT = -1;
				long ID_PROB = -1;
				if (!setProbGr.IsBOF()) 
				{
					setProbGr.MoveFirst( );
					while(!setProbGr.IsEOF()) 
					{
						if(LAB_N == setProbGr.m_LAB_N)
						{
							found_lab_n = true;

							ID_KT = setProbGr.m_ID_KT;
							ID_PROB = setProbGr.m_ID_PROB;

							long cilce_records = 0;

							SetZriz setZriz(this->p_database);
							setZriz.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
								ID_OBJ, ID_KT, ID_PROB);
							setZriz.m_strSort.Format("ID_KT, ID_PROB");
							if (!setZriz.Open(CRecordset::dynaset) )
								return;

							long id_cut_vyprob = setZriz.GetNewKeyID();
							long ID_VYPROB_ [3];
							ID_VYPROB_[0] = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, 1);
							ID_VYPROB_[1] = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, 2);
							ID_VYPROB_[2] = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, 3);

							bool to_delete_cuts = false;
							if (id_cut_vyprob > 1)
							{
								CString s;
								s.Format(
									"По лабораторному номеру %d в базе уже имеются испытания грунта на срез,\n"
									"В связи с эти выберите следующие варианты действий:\n\n"

									"Если Вы хотите удалить из базы существующие данные среза \n"
									"по настоящему лабораторному номеру и вместо них внести новые,\n"
									"нажмите кнопку ДА\n\n"

									"Если Вы хотите внести данные среза под дополнительным идентификатором %d,\n"
									"нажмите кнопку НЕТ\n\n"

									"Если Вы хотите хотите по данному лабораторному номеру ниичего не делать\n"
									"в том числе не вносить также и физ.мех. свойства\n"
									"нажмите кнопку ОТМЕНА\n\n"
									, 
									LAB_N, id_cut_vyprob);

								int ans = AfxMessageBox(s,MB_YESNOCANCEL);
								switch(ans)
								{
								case IDYES:
									{
										to_delete_cuts = true;
									}
									break;
								case IDNO:
									{
										to_delete_cuts = false;
									}
									break;
								case IDCANCEL:
									{
										goto e_next_cut_prob_grunt;
									}
									break;
								}
							}

							if (to_delete_cuts)
							{
								// удаляем данные из таблиц

								CString filter;
								filter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d",
                                    ID_OBJ, ID_KT, ID_PROB);

								SetZriz0 _setZriz0(this->p_database);
								DeleteFilterRelatedDataFrom(&_setZriz0, filter);

								SetZriz _setZriz(this->p_database);
								DeleteFilterRelatedDataFrom(&_setZriz, filter);

								SetZriz_tbl _setZriz_tbl(this->p_database);
								DeleteFilterRelatedDataFrom(&_setZriz_tbl, filter);

								id_cut_vyprob = _setZriz.GetNewKeyID();
								ID_VYPROB_[0] = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, 1);
								ID_VYPROB_[1] = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, 2);
								ID_VYPROB_[2] = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, 3);
							}

							// for Ro_po_upl_as_e
							trial_value mean_ro, mean_ros, mean_w;
							double ro[3], ros[3], w[3];
							int n_ro_got_from_table = 0;
							int n_ros_got_from_table = 0;
							int n_w_got_from_table = 0;

							bool was_merged_param = false;

							if (m_to_save_also_physical)
							{
								for (long ipar = 0; ipar < npar; ipar++)
								{
									long ID_PARAM = id_params[ipar];
									//sprintf(S, "%c%d",  letter, fr + param_rows[ipar]);
									sprintf(S, "%s%d",  ecc.Get(), fr + param_rows[ipar]);
									bool is_merged_param = ExcelRange_GetMergeCells(m_excel, S);
									if (is_merged_param)
										was_merged_param = true;

									int max_iv = merged_cols == 3 ? (is_merged_param ? 1 : 3) : 1;
									for (int iv = 0; iv < max_iv; iv++)
									{
										//sprintf(S, "%c%d",  letter+iv, fr + param_rows[ipar]);	
										sprintf(S, "%s%d",  ecc.Get(iv), fr + param_rows[ipar]);	
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											long ID_VYPROB = MEAN_PHYS_VYPROB;
											switch (merged_cols)
											{
											case 1:
												{
													ID_VYPROB = MEAN_PHYS_VYPROB;
												}
												break;
											case 2:
												{
													ID_VYPROB = MEAN_PHYS_VYPROB;
												}
												break;
											case 3:
												{
													if (is_merged_param)
													{
														ID_VYPROB = MEAN_PHYS_VYPROB;
													}
													else
													{
														ID_VYPROB = ID_VYPROB_[iv];
													}
												}
												break;
											}


											SetFizMeh setFizMeh_2(this->p_database);
											setFizMeh_2.m_strFilter.Format(
												"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
												ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM);
											if (setFizMeh_2.Open(CRecordset::dynaset) )
											{
												int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, LAB_N, 
													ID_PARAM, ID_VYPROB, val);
											}
											// 6 Плотность грунта, г/см3
											// 8 Плотность частиц грунта, г/см3
											// 1 Природная влажность грунта, д.е.

											if (ID_PARAM == 6)
											{
												ro[iv] = val;
												n_ro_got_from_table = iv+1;
											}

											if (ID_PARAM == 8)
											{
												ros[iv] = val;
												n_ros_got_from_table = iv+1;
											}

											if (ID_PARAM == 1)
											{
												w[iv] = val;
												n_w_got_from_table = iv+1;
											}											
										}
									}
								}
							}

							if (was_merged_param && D && H)
							{
								SetZriz0 setZriz0(this->p_database);
								setZriz0.m_strFilter.Format(
									"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
									ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob);
								if ( setZriz0.Open(CRecordset::dynaset) )
								{
									for (int ir = 0; ir < 3; ir++)
									{
										double DH_PO_UPL = 0.0;
										setZriz0.AddNewRow(ID_OBJ,ID_KT,ID_PROB, id_cut_vyprob,
											ir+1, ID_VYPROB_[ir],
											H, D, DH_PO_UPL);	
									}
								}
							}

							bool add_cut_from_db = false;
							bool add_compress_from_db = false;
							int nCutItem = 0;
							int nCompItem = 0;
							bool add_stat_zond_from_db = false;
							LabNumber * lab_number = this->m_lab_view->CreateLabNumber(LAB_N, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
							if (!lab_number) return;

							if (Ro_po_upl_as_e)
							{
								LabTrial * lab_trial = lab_number ? lab_number->FindLabTrial(LabTrial::indication::physical, MEAN_PHYS_VYPROB) : NULL;
								PhysicalLabTrial * phys = dynamic_cast<PhysicalLabTrial *>(lab_trial);
								if (phys)
								{
									mean_ro = phys->density_of_ground;
									mean_w = phys->moisture_of_nature_large_exchange;
									mean_ros = phys->density_of_ground_particles;
								}
							}


							SetZriz_tbl setZriz_tbl(this->p_database);
							if ( !setZriz_tbl.Open(CRecordset::dynaset) )
								return;

							int r_TAU = 23;
							int 
								r_W_do = 26, 
								r_Ro_do = 29, 

								r_W_po_upl = 32, 
								r_Ro_po_upl = 35, 

								r_W_after = 38, 
								r_Ro_after = 41;

							//char letter_TAU = merged_cols == 2 ? letter + 1 : letter;
							//char letter_sigma = merged_cols == 2 ? letter : 'D';

							ExcelColChar ecc_TAU = merged_cols == 2 ? ecc + 1 : ecc;
							ExcelColChar ecc_sigma = merged_cols == 2 ? ecc : ExcelColChar('D');


							for (int ir = 0; ir < 3; ir++)
							{
								double sigma = 0.0, tau = 0.0;
								double 
									W_do = 0.0, 
									W_po_upl = 0.0, 
									W_after = 0.0, 
									Ro_do = 0.0, 
									Ro_po_upl = 0.0, 
									Ro_after = 0.0;

								//sprintf(S, "%c%d", letter_sigma, fr+r_TAU+ir);
								sprintf(S, "%s%d", ecc_sigma.Get(), fr+r_TAU+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									sigma = val;
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_TAU+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_TAU+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									tau = val;
								}
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_TAU+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_TAU+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											tau = val;
										}
									}
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_W_do+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_W_do+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									W_do = val;
								}	
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_W_do+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_W_do+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											W_do = val;
										}
									}
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_W_po_upl+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_W_po_upl+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									W_po_upl = val;
								}	
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_W_po_upl+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_W_po_upl+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											W_po_upl = val;
										}
									}
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_W_after+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_W_after+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									W_after = val;
								}	
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_W_after+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_W_after+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											W_after = val;
										}	
									}
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_Ro_do+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_Ro_do+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									Ro_do = val;
								}	
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_Ro_do+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_Ro_do+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											Ro_do = val;
										}	
									}
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_Ro_po_upl+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_Ro_po_upl+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									Ro_po_upl = val;
								}	
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_Ro_po_upl+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_Ro_po_upl+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											Ro_po_upl = val;
										}	
									}
								}

								if (Ro_po_upl_as_e && Ro_po_upl)
								{
									double _e = Ro_po_upl;
									double _ro = 0.0;
									double _ros = 0.0;
									double _w = 0.0;
									if (n_ro_got_from_table)
									{
										if (n_ro_got_from_table == 3)
										{
											_ro = ro[ir];
										}
										else
										{
											_ro = ro[0];
										}
									}
									else
									{
										if (mean_ro.f)
											_ro = mean_ro.v;
									}

									if (n_ros_got_from_table)
									{
										if (n_ros_got_from_table == 3)
										{
											_ros = ros[ir];
										}
										else
										{
											_ros = ros[0];
										}
									}
									else
									{
										if (mean_ros.f)
											_ros = mean_ros.v;
									}

									if (n_w_got_from_table)
									{
										if (n_w_got_from_table == 3)
										{
											_w = w[ir];
										}
										else
										{
											_w = w[0];
										}
									}
									else
									{
										if (mean_w.f)
											_w = mean_w.v;
									}
									if (W_po_upl)
										_w = W_po_upl;

									Ro_po_upl = _ros * (1.0 + _w) / (1.0 + _e);
								}

								//sprintf(S, "%c%d", letter_TAU, fr+r_Ro_after+ir);
								sprintf(S, "%s%d", ecc_TAU.Get(), fr+r_Ro_after+ir);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									Ro_after = val;
								}	
								else
								{
									if (merged_cols != 2)
									{
										//sprintf(S, "%c%d", letter, fr+r_Ro_after+ir);
										sprintf(S, "%s%d", ecc.Get(), fr+r_Ro_after+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											Ro_after = val;
										}
									}
								}

								if (merged_cols == 3)
								{
									//letter_TAU++;
									ecc_TAU.Increment();
								}

                                

								if (sigma && tau && D && H)
								{
									unsigned char bStat = 1;
									if (lab_number)	lab_number->AddZriz_tbl(id_cut_vyprob, ir+1, sigma, tau, W_do, Ro_do, W_po_upl, Ro_po_upl, W_after, Ro_after, bStat);
									setZriz_tbl.AddNewRow(ID_OBJ,ID_KT, ID_PROB, id_cut_vyprob, ir+1, sigma, tau, W_do, Ro_do, W_po_upl, Ro_po_upl, W_after, Ro_after);
								}
							}

							long ID_HID = 0, ID_SHEMA = 0, ID_STAN = 0;



							//sprintf(S, "%c%d", letter, fr+16);
							sprintf(S, "%s%d", ecc.Get(), fr+16);
							if (ExcelRange_GetValue(m_excel, S, val))
							{
								ID_STAN = long(val);
							}

							//sprintf(S, "%c%d", letter, fr+18);
							sprintf(S, "%s%d", ecc.Get(), fr+18);
							if (ExcelRange_GetValue(m_excel, S, val))
							{
								ID_HID = long(val);
							}

							//sprintf(S, "%c%d", letter, fr+20);
							sprintf(S, "%s%d", ecc.Get(), fr+20);
							if (ExcelRange_GetValue(m_excel, S, val))
							{
								ID_SHEMA = long(val);
							}

							double C = 0.0;
							double tgFi = 0.0;
							unsigned char bStat = 1;
							if (lab_number)	lab_number->AddZriz(id_cut_vyprob, 		
								ID_HID, ID_SHEMA, ID_STAN, tgFi, C, D, H, bStat);

							if (lab_number)	lab_number->ApplyZriz(0);
							if (lab_number)	lab_number->CalcProperties();

							LabTrial::indication ind = LabTrial::indication::undefined_lab_trial_indication;

							switch(ID_STAN)
							{
							case 1:
								{
									ind = LabTrial::indication::cut_resistance_nature_condition;
								}
								break;
							case 2:
								{
									ind = LabTrial::indication::cut_resistance_task_condition;
								}
								break;
							}

							LabTrial * lab_trial = lab_number ? lab_number->FindLabTrial(ind, -1) : NULL;
							CutLabTrial * cut = dynamic_cast<CutLabTrial *>(lab_trial);
							if (cut)
							{
								CutLabTrialResults * cut_lab_res = dynamic_cast<CutLabTrialResults *>(cut->results);
								if(cut_lab_res)
								{
									tgFi = cut_lab_res->tgfi.v;
									C = cut_lab_res->c.v;
								}
							}

							if (D && H)
							{
								setZriz.AddNewRow(ID_OBJ,ID_KT,ID_PROB, id_cut_vyprob,
									ID_HID, ID_SHEMA, ID_STAN, tgFi, C, D, H);
							}
			

							break;
						}
e_next_cut_prob_grunt:
						setProbGr.MoveNext();
					}
				}
			}


			if (!found_lab_n)
			{
				CString s;
				s.Format(
					"Лабораторный номер %d не найден в базе,\n"
					"поэтому данные среза по нему не внесены", 
					LAB_N);
				AfxMessageBox(s);
			}

			for  (int cl = 0; cl < merged_cols; cl++ ) 
			{
				n++;
				//letter++;
				ecc.Increment();
#if AUTO_NEW_PAGE_ON_ARCHIVES_WHEN_SAVE
				// выключаем автоматический переход на новую страницу при сохранении на случай, если пользователь увеличит число колонок
				if (!(n%cols_per_page))
				{
					fr += rows_per_page;
					letter = first_letter;
				}
#endif
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