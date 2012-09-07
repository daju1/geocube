// ExcelArchiveCompression.cpp: implementation of the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelArchiveCompression.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"
#include "SetCilce.h"
#include "SetCilce0.h"
#include "SetCompress.h"
#include "SetFizMehAllParam.h"

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

ExcelArchiveCompression::ExcelArchiveCompression()
{
	m_to_fill_all_lab_numbers = false;
	m_to_fill_all_lab_numbers_as_2_vyprob = false;
	m_to_save_also_physical = false;


	rows_per_page = 42;
	cols_per_page = 10;
	first_letter = 'F';

	npar = 7;
	long _id_params[] = {2,3,1,8,6,50,35};
	long _param_rows[] = {8,9,10,12,13,14,15};

	memcpy(id_params, _id_params, npar*sizeof(long));
	memcpy(param_rows, _param_rows, npar*sizeof(long));

}

ExcelArchiveCompression::~ExcelArchiveCompression()
{

}
void ExcelArchiveCompression::InitExt()
{
	ext					= "aсd";
	xl_filter_name		= "Архивные данные компрессии";
	xl_form				= "ArchiveCompressData";
}
void ExcelArchiveCompression::FillSetCompress(SetCilce & setCilce, int & n, int & fr, char & letter, int & p)
{
	char S[64];
	map<long, double> m_min_sigma;// карта минимальных давлний по компрессионным ID_VYPROB

	SetCompress setCompress0(this->p_database);
	setCompress0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
		setCilce.m_ID_OBJ, setCilce.m_ID_KT, setCilce.m_ID_PROB, setCilce.m_ID_VYPROB);
	setCompress0.m_strSort.Format("ID_VYPROB, SIGMA");
	if (setCompress0.Open(CRecordset::dynaset) )
	{
		if (!setCompress0.IsBOF()) 
		{
			setCompress0.MoveFirst();
			while(!setCompress0.IsEOF()) 
			{
				long ID_VYPROB = setCompress0.m_ID_VYPROB;
				double sigma = setCompress0.m_SIGMA;

				if (sigma >= 0.0)
				{
					map<long, double>::iterator found = m_min_sigma.find(ID_VYPROB);
					if (found != m_min_sigma.end())
					{
						if ((*found).second > sigma)
							(*found).second = sigma;
					}
					else
					{
						m_min_sigma.insert(map<long,double>::value_type(ID_VYPROB, sigma));
					}
				}
				setCompress0.MoveNext();
			}
		}
	}
	map<long, double>::iterator found = m_min_sigma.find(setCilce.m_ID_VYPROB);
	if (found != m_min_sigma.end())
	{
		long ID_VYPROB = (*found).first;
		double min_sigma = (*found).second;

		SetCompress setCompress(this->p_database);
		setCompress.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d", 
			setCilce.m_ID_OBJ, setCilce.m_ID_KT, setCilce.m_ID_PROB, ID_VYPROB);
		setCompress.m_strSort.Format("ID_VYPROB, SIGMA");
		if (setCompress.Open(CRecordset::dynaset) )
		{
			int r1 = min_sigma == 0 ? fr + 18 : fr + 19;
			int r2 = min_sigma == 0 ? fr + 30 : fr + 31;

			if (false)
			{
e_correct_1:
				// очищаем не в том месте заполненные клетки
				r1 = min_sigma == 0 ? fr + 18 : fr + 19;
				r2 = min_sigma == 0 ? fr + 30 : fr + 31;
				if (!setCompress.IsBOF()) 
				{
					setCompress.MoveFirst();
					while(!setCompress.IsEOF()) 
					{
						if(setCompress.m_SIGMA >= 0.0)
						{
							switch (setCilce.m_ID_METHOD)
							{
							case 1:
								{
									if (setCompress.m_SIGMA != 0.0)
									{
										sprintf(S, "%c%d", letter, r1);
										ExcelRange_SetValue(m_excel, S, COleVariant(""));
									}
								}
								break;
							case 2:
								{
									if (setCompress.m_SIGMA != 0.0)
									{
										sprintf(S, "%c%d", letter, r1);
										ExcelRange_SetValue(m_excel, S, COleVariant(""));
									}

									bool list = (!((n+1)%cols_per_page));
									char Letter = this->save_different_vyprob ? (list ? first_letter : letter + 1) : letter;
									int R2 = this->save_different_vyprob ? (list ? r2 + rows_per_page : r2) : r2;

									sprintf(S, "%c%d", Letter, R2);
									ExcelRange_SetValue(m_excel, S, COleVariant(""));
								}
								break;
							case 3:
								{
									if (setCompress.m_DH1 && !setCompress.m_DH2)
									{
										if (setCompress.m_SIGMA != 0.0)
										{
											sprintf(S, "%c%d", letter, r1);
											ExcelRange_SetValue(m_excel, S, COleVariant(""));
										}
									}

									if (setCompress.m_DH1 && setCompress.m_DH2)
									{
										if (setCompress.m_SIGMA != 0.0)
										{
											sprintf(S, "%c%d", letter, r1);
											ExcelRange_SetValue(m_excel, S, COleVariant(""));
										}
										
										sprintf(S, "%c%d", letter, fr+29);
										ExcelRange_SetValue(m_excel, S, COleVariant(""));
									}

									if (!setCompress.m_DH1 && setCompress.m_DH2)
									{
										if (setCompress.m_SIGMA != 0.0)
										{
											sprintf(S, "%c%d", letter, r1);
											ExcelRange_SetValue(m_excel, S, COleVariant(""));
										}
									}
								}
								break;
							case 4:
								{
									sprintf(S, "%c%d", letter, r2);
									ExcelRange_SetValue(m_excel, S, COleVariant(""));
								}
								break;
							}
							r1++; r2++;
						}
						else
						{
							sprintf(S, "%c%d", letter, fr+29);
							ExcelRange_SetValue(m_excel, S, COleVariant(""));
						}
						setCompress.MoveNext();
					}
				}						
				// копируем дополниельно ещё одну таблицу из резервного временного файла
				ExcelArchiveCompression m_excel_temp;
				CString dir = m_excel.m_app.GetDefaultFilePath();
				CString fn_temp = "TempExcelArchiveCompression";
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
				r1 = min_sigma == 0 ? fr + 18 : fr + 19;
				r2 = min_sigma == 0 ? fr + 30 : fr + 31;
			}								

			double sigma;
			if (!setCompress.IsBOF()) 
			{
				setCompress.MoveFirst();
				while(!setCompress.IsEOF()) 
				{
					if(setCompress.m_SIGMA >= 0.0)
					{
						if (setCompress.m_SIGMA != 0.0)
						{
							sprintf(S, "D%d", r1);
							if (ExcelRange_GetValue(m_excel, S, sigma))
							{
								if (sigma != setCompress.m_SIGMA)
								{
									CString s;
									s.Format(
										"В лабораторном номере %d давление компрессии не соответствует строке таблицы\n"
										"sigma %f != setCompress.m_SIGMA %f",
										/*LAB_N*/-1, sigma, setCompress.m_SIGMA);
									//AfxMessageBox(s);
									goto e_correct_1;
								}
							}
							else
								ExcelRange_SetValue(m_excel, S, COleVariant(setCompress.m_SIGMA));
						}

						sprintf(S, "D%d", r2);
						if (ExcelRange_GetValue(m_excel, S, sigma))
						{
							if (sigma != setCompress.m_SIGMA)
							{
								CString s;
								s.Format(
									"В лабораторном номере %d давление компрессии не соответствует строке таблицы\n"
									"sigma %f != setCompress.m_SIGMA %f",
									/*LAB_N*/-1, sigma, setCompress.m_SIGMA);
								//AfxMessageBox(s);
								goto e_correct_1;
							}
						}
						else
							ExcelRange_SetValue(m_excel, S, COleVariant(setCompress.m_SIGMA));


						switch (setCilce.m_ID_METHOD)
						{
						case 1:
							{
								if (setCompress.m_SIGMA != 0.0)
								{
									sprintf(S, "%c%d", letter, r1);
									ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH1));
								}
							}
							break;
						case 2:
							{
								if (setCompress.m_SIGMA != 0.0)
								{
									sprintf(S, "%c%d", letter, r1);
									ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH1));
								}

								bool list = (!((n+1)%cols_per_page));
								char Letter = this->save_different_vyprob ? (list ? first_letter : letter + 1) : letter;
								int R2 = this->save_different_vyprob ? (list ? r2 + rows_per_page : r2) : r2;

								sprintf(S, "%c%d", Letter, R2);
								ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH2));
							}
							break;
						case 3:
							{
								if (setCompress.m_DH1 && !setCompress.m_DH2)
								{
									if (setCompress.m_SIGMA != 0.0)
									{
										sprintf(S, "%c%d", letter, r1);
										ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH1));
									}
								}

								if (setCompress.m_DH1 && setCompress.m_DH2)
								{
									if (setCompress.m_SIGMA != 0.0)
									{
										sprintf(S, "%c%d", letter, r1);
										ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH1));
									}

									sprintf(S, "D%d", fr+29);
									if (ExcelRange_GetValue(m_excel, S, sigma))
									{
										if (sigma != setCompress.m_SIGMA)
										{
											CString s;
											s.Format(
												"В лабораторном номере %d давление замачивания компрессии не соответствует строке таблицы\n"
												"sigma %f != setCompress.m_SIGMA %f",
												/*LAB_N*/-1, sigma, setCompress.m_SIGMA);
											//AfxMessageBox(s);
											goto e_correct_1;
										}
									}
									else
										ExcelRange_SetValue(m_excel, S, COleVariant(setCompress.m_SIGMA));
									
									sprintf(S, "%c%d", letter, fr+29);
									ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH2));
								}

								if (!setCompress.m_DH1 && setCompress.m_DH2)
								{
									if (setCompress.m_SIGMA != 0.0)
									{
										sprintf(S, "%c%d", letter, r1);
										ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH2));
									}
								}
							}
							break;
						case 4:
							{
								sprintf(S, "%c%d", letter, r2);
								ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH2));
							}
							break;
						}
						r1++; r2++;
					}
					else
					{
						sprintf(S, "D%d", fr+29);
						if (ExcelRange_GetValue(m_excel, S, sigma))
						{
							if (sigma != -setCompress.m_SIGMA)
							{
								CString s;
								s.Format(
									"В лабораторном номере %d давление замачивания компрессии не соответствует строке таблицы\n"
									"sigma %f != setCompress.m_SIGMA %f",
									/*LAB_N*/-1, sigma, -setCompress.m_SIGMA);
								//AfxMessageBox(s);
								goto e_correct_1;
							}
						}
						else
							ExcelRange_SetValue(m_excel, S, COleVariant(-setCompress.m_SIGMA));

						sprintf(S, "%c%d", letter, fr+29);
						ExcelRange_SetValue(m_excel, S, COleVariant(10. * setCompress.m_DH1));
					}

					setCompress.MoveNext();
				}
			}						
		}
	}

	switch (setCilce.m_ID_METHOD)
	{
	case 1:
		{
			sprintf(S, "%c%d", letter, fr+16);
			ExcelRange_SetValue(m_excel, S, COleVariant(long(1)));	
		}
		break;
	case 2:
		{
			sprintf(S, "%c%d", letter, fr+16);
			ExcelRange_SetValue(m_excel, S, COleVariant(long(2)));	
		}
		break;
	case 3:
		{
			sprintf(S, "%c%d", letter, fr+16);
			ExcelRange_SetValue(m_excel, S, COleVariant(long(1)));	
		}
		break;
	case 4:
		{
			sprintf(S, "%c%d", letter, fr+16);
			ExcelRange_SetValue(m_excel, S, COleVariant(long(1)));	
		}
		break;
	}
	sprintf(S, "%c%d", letter, fr+17);
	ExcelRange_SetValue(m_excel, S, COleVariant(setCilce.m_D));	

	sprintf(S, "%c%d", letter, fr+18);
	ExcelRange_SetValue(m_excel, S, COleVariant(setCilce.m_H));	
}
void ExcelArchiveCompression::FillProbGrKT(long ID_OBJ, long ID_KT, long ID_PROB, int & n, int & fr, char & letter, bool use_2_colomns, long id_compress_vyprob)
{
	char S[64];
	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
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

				sprintf(S, "%c%d", letter, fr+5);
				ExcelRange_SetValue(m_excel, S, COleVariant(kt_type));

				sprintf(S, "%c%d", letter, fr+6);
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
				sprintf(S, "%c%d", letter, fr+4);
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_LAB_N));
				LAB_N = setProbGr.m_LAB_N;

				sprintf(S, "%c%d", letter, fr+7);
				ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_H));


				SetFizMeh setFizMeh(this->p_database);
				setFizMeh.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
				if (setFizMeh.Open(CRecordset::dynaset) )
				{
					for (long ipar = 0; ipar < npar; ipar++)
					{
						long ID_PARAM = id_params[ipar];

						double val_from_db; 
						double mean_of_vyprob;
						if (use_2_colomns)
						{
							long ID_VYPROB_1 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, id_compress_vyprob, 1);
							long ID_VYPROB_2 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, id_compress_vyprob, 2);

							double val_1; 
							double val_2; 
							int res_1 = setFizMeh.GetParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, ID_VYPROB_1,
								val_1);
							int res_2 = setFizMeh.GetParam(ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, ID_PARAM, ID_VYPROB_2,
								val_2);

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

							if (!res_1 && !res_2)
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

								sprintf(S, "%c%d:%c%d", letter, r2, letter+1, r2);
								ExcelRange_SetMerge(m_excel, S, true);
							}
						}
						else
						{
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
						}
					}
				}
			}
		}						
	}
	if (use_2_colomns)
	{								
		bool list = (!((n+1)%cols_per_page));
		if (!list)
		{						
			sprintf(S, "%c%d:%c%d", letter, fr+3, letter + 1, fr+7);
			ExcelRange_SetMerge(m_excel, S, true);	
		}
	}
}
void ExcelArchiveCompression::FillReList(int & n, int & fr, char & letter, bool use_2_colomns)
{
#if 1
	if (use_2_colomns)
	{
		bool list = (!((n+1)%cols_per_page));
		if (list)// не переносим две кривые на след страницу
		{
			n = 0;
			fr += rows_per_page;
			letter = first_letter;
		}
	}
#else							
	if (use_2_colomns)
	{
		bool list = (!((n+1)%cols_per_page));
		if (list)// не переносим две кривые на след страницу
		{
			n++;letter++;
			if (!(n%cols_per_page))
			{
				fr += rows_per_page;
				letter = first_letter;
			}
		}
	}
#endif
}
void ExcelArchiveCompression::FillIncrement(int & n, int & fr, char & letter, bool use_2_colomns)
{
	if (use_2_colomns)
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



bool ExcelArchiveCompression::virFill()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбран объект");
		return false;
	}

	char S[64];
	int fr = 0;

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;


		long different_vyprob = 0;
		long cilce_records = 0;
		long empty_labn_records = 0;

		SetProbGr setProbGr_all(this->p_database);
		setProbGr_all.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr_all.m_strSort.Format("ID_KT, ID_PROB");
		setProbGr_all.m_strSort.Format("LAB_N");
		if (setProbGr_all.Open(CRecordset::dynaset) )
		{
			if (!setProbGr_all.IsBOF()) 
			{
				setProbGr_all.MoveFirst();
				while(!setProbGr_all.IsEOF()) 
				{
					SetCilce setCilce(this->p_database);
					setCilce.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
						ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB);
					setCilce.m_strSort.Format("ID_KT, ID_PROB");
					if (setCilce.Open(CRecordset::dynaset) )
					{
						if (!setCilce.IsBOF()) 
						{
							setCilce.MoveFirst();
							while(!setCilce.IsEOF()) 
							{
								switch (setCilce.m_ID_METHOD)
								{
								case 1:
									{
										different_vyprob++;
									}
									break;
								case 2:
									{
										
										different_vyprob++;
										int nn = different_vyprob + empty_labn_records;
										bool list = (!((nn+1)%cols_per_page));
										if (list) different_vyprob++; // не переносим две кривые на след страницу
										different_vyprob++;
									}
									break;
								case 3:
									{
										different_vyprob++;
									}
									break;
								case 4:
									{
										different_vyprob++;
									}
									break;
								}
								setCilce.MoveNext();
							}
						}		 
						long record_count = setCilce.GetRecordCount();
						if (record_count > -1)							
						{
							cilce_records += record_count;
						}
						if (record_count <= 0)
						{
							empty_labn_records++;
						}
					}
					setProbGr_all.MoveNext();
				}
			}	

			long Records = this->save_different_vyprob ? different_vyprob : cilce_records;
										
			if (this->m_to_fill_all_lab_numbers)
			{
				Records += empty_labn_records;
				if (m_to_fill_all_lab_numbers_as_2_vyprob)
					Records += empty_labn_records;
			}

			//Если число лабораторных номеров больше 35, надо скопировать таблицу на вторую страницу
			double fpages = double (Records) / double (cols_per_page);
			int pages = int(ceil(fpages));

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

			
			char letter = first_letter;

			int n = 0;

			if (!setProbGr_all.IsBOF()) 
			{
				setProbGr_all.MoveFirst();
				while(!setProbGr_all.IsEOF()) 
				{
					SetCilce setCilce(this->p_database);
					setCilce.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
						ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB);
					setCilce.m_strSort.Format("ID_KT, ID_PROB");
					if (setCilce.Open(CRecordset::dynaset) )
					{
						if (!setCilce.IsBOF()) 
						{
							setCilce.MoveFirst( );
							while(!setCilce.IsEOF()) 
							{
								
								bool use_2_colomns = this->save_different_vyprob && setCilce.m_ID_METHOD == 2;
								long id_compress_vyprob = setCilce.m_ID_VYPROB;

								this->FillReList(n, fr, letter, use_2_colomns);
								this->FillSetCompress(setCilce, n, fr, letter, p);
								this->FillProbGrKT(ID_OBJ, setCilce.m_ID_KT, setCilce.m_ID_PROB, n, fr, letter, use_2_colomns, id_compress_vyprob);
								this->FillIncrement(n, fr, letter, use_2_colomns);
							
								setCilce.MoveNext();
							}
						}
						long record_count = setCilce.GetRecordCount();
						if (record_count <= 0 && this->m_to_fill_all_lab_numbers)
						{
							bool use_2_colomns = m_to_fill_all_lab_numbers_as_2_vyprob;
							long id_compress_vyprob = 1;

							this->FillReList(n, fr, letter, use_2_colomns);
							this->FillProbGrKT(ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB, n, fr, letter, use_2_colomns, id_compress_vyprob);
							this->FillIncrement(n, fr, letter, use_2_colomns);							
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
void DeleteFilterRelatedDataFrom(CRecordset * set, CString filter);

void ExcelArchiveCompression::virSaveToDB()
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

		int fr = 0;
		for (int n = 0; ; )
		{
			double val;

			long LAB_N;
			//sprintf(S, "%c%d", letter, fr+4);
			sprintf(S, "%s%d", ecc.Get(), fr+4);
			if (!ExcelRange_GetValue(m_excel, S, val))
			{
				fr += rows_per_page;
				//letter = first_letter;
				ecc.Init(first_letter);
				n = 0;
				//sprintf(S, "%c%d", letter, fr+4);
				sprintf(S, "%s%d", ecc.Get(), fr+4);
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
			bool is_merged_lab_n = ExcelRange_GetMergeCells(m_excel, S);

			long n_krivyh = 0;
			//sprintf(S, "%c%d", letter, fr+16);							
			sprintf(S, "%s%d", ecc.Get(), fr+16);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				n_krivyh = long(val);
			}
			n_krivyh;

			double 
				H = 0.0,
				D = 0.0;

			//sprintf(S, "%c%d", letter, fr+17);							
			sprintf(S, "%s%d", ecc.Get(), fr+17);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				D = val;
			}

			//sprintf(S, "%c%d", letter, fr+18);							
			sprintf(S, "%s%d", ecc.Get(), fr+18);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				H = val;
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

							SetCilce setCilce(this->p_database);
							setCilce.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
								ID_OBJ, ID_KT, ID_PROB);
							setCilce.m_strSort.Format("ID_KT, ID_PROB");
							if (!setCilce.Open(CRecordset::dynaset) )
								return;

							long id_compress_vyprob = setCilce.GetNewKeyID();
							long ID_VYPROB_1 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 1);
							long ID_VYPROB_2 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 2);



							bool to_delete_compression = false;
							if (id_compress_vyprob > 1)
							{
								CString s;
								s.Format(
									"По лабораторному номеру %d в базе уже имеются компрессионные испытания,\n"
									"В связи с эти выберите следующие варианты действий:\n\n"

									"Если Вы хотите удалить из базы существующие данные компрессии \n"
									"по настоящему лабораторному номеру и вместо них внести новые,\n"
									"нажмите кнопку ДА\n\n"

									"Если Вы хотите внести данные компрессии под дополнительным идентификатором %d,\n"
									"нажмите кнопку НЕТ\n\n"

									"Если Вы хотите хотите по данному лабораторному номеру ниичего не делать\n"
									"в том числе не вносить также и физ.мех. свойства\n"
									"нажмите кнопку ОТМЕНА\n\n"
									, 
									LAB_N, id_compress_vyprob);

								int ans = AfxMessageBox(s,MB_YESNOCANCEL);
								switch(ans)
								{
								case IDYES:
									{
										to_delete_compression = true;
									}
									break;
								case IDNO:
									{
										to_delete_compression = false;
									}
									break;
								case IDCANCEL:
									{
										goto e_next_compress_prob_grunt;
									}
									break;
								}
							}
							if (to_delete_compression)
							{
								// удаляем данные из таблиц

								CString filter;
								filter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d",
                                    ID_OBJ, ID_KT, ID_PROB);

								SetCilce _setCilce(this->p_database);
								DeleteFilterRelatedDataFrom(&_setCilce, filter);

								//SetCilce0 _setCilce0(this->p_database);
								//DeleteFilterRelatedDataFrom(&_setCilce0, filter);

								SetCompress _setCompress(this->p_database);
								DeleteFilterRelatedDataFrom(&_setCompress, filter);

								id_compress_vyprob = _setCilce.GetNewKeyID();
								ID_VYPROB_1 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 1);
								ID_VYPROB_2 = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, 2);
							}
							else
							{
								// на всякий случай очищаем таблицу Compress от возможно лишних строк по ID_VYPROB которое мы будем вносить
								CString filter;
								filter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d",
                                    ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob);

								SetCompress _setCompress(this->p_database);
								DeleteFilterRelatedDataFrom(&_setCompress, filter);
							}

							if (m_to_save_also_physical)
							{
								for (long ipar = 0; ipar < npar; ipar++)
								{
									long ID_PARAM = id_params[ipar];
									//sprintf(S, "%c%d",  letter, fr + param_rows[ipar]);
									sprintf(S, "%s%d",  ecc.Get(), fr + param_rows[ipar]);
									bool is_merged_param = ExcelRange_GetMergeCells(m_excel, S);

									int max_iv = is_merged_lab_n ? (is_merged_param ? 1 : 2) : 1;
									for (int iv = 0; iv < max_iv; iv++)
									{
										//sprintf(S, "%c%d",  letter+iv, fr + param_rows[ipar]);	
										sprintf(S, "%s%d",  ecc.Get(iv), fr + param_rows[ipar]);	
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											long ID_VYPROB;
											if (is_merged_lab_n)
											{
												if (is_merged_param)
												{
													ID_VYPROB = MEAN_PHYS_VYPROB;
												}
												else
												{
													ID_VYPROB = ID_VYPROB_1 + iv;
												}
											}
											else
												ID_VYPROB = MEAN_PHYS_VYPROB;


											SetFizMeh setFizMeh_2(this->p_database);
											setFizMeh_2.m_strFilter.Format(
												"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
												ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM);
											if (setFizMeh_2.Open(CRecordset::dynaset) )
											{
												int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, LAB_N, 
													ID_PARAM, ID_VYPROB, val);
											}
										}
									}
								}
							}

							bool add_cut_from_db = false;
							bool add_compress_from_db = true;
							int nCutItem = 0;
							int nCompItem = 0;
							bool add_stat_zond_from_db = false;
							LabNumber * lab_number = this->m_lab_view->CreateLabNumber(LAB_N, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
							if (!lab_number) return;

							bool may_to_save = true;
							if (D && H)
							{
								if (!lab_number->HaveEnoughFor_e0(id_compress_vyprob))
								{
									CString s;
									s.Format(									
										"Для расчёта коэффициента пористости в лабораторном номере %d недостаточно данных\n"
										"(Необходимо определить плотность грунта, плотность частиц грунта и влажность)\n" 
										"Поэтому данные по компрессии по данному лабораторному номеру в базу не заносятся", 
										LAB_N);
									AfxMessageBox(s);
									may_to_save = false;
								}
							}

							if (may_to_save && D && H)
							{
								SetCompress setCompress(this->p_database);
								if ( !setCompress.Open(CRecordset::dynaset) )
									return;

								bool zamach = true;
								double p, dh = 0.0, dhw = 0.0;

								bool p_got = false;
								bool dh_got = false;

								sprintf(S, "D%d", fr+29);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									p = val;
									p_got = true;
								}

								//sprintf(S, "%c%d", letter, fr+29);
								sprintf(S, "%s%d", ecc.Get(), fr+29);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									dh = val;
									dh_got = true;
								}
								if (p_got && dh_got)
								{
									unsigned char voda  = 1;
									if (lab_number)	lab_number->AddCompress(id_compress_vyprob, zamach ? -p : p, dh, dhw, voda, 1);
									//if (toSavetoDB)
										setCompress.AddNewRow(ID_OBJ,ID_KT, ID_PROB, id_compress_vyprob, zamach ? -p : p, 0.1 * dh, 0.1 * dhw, voda, 1);

									// в базу - сантиметры, в lab_number - миллиметры!!!
								}

								int r1 = 18, r2 = 30;
								//char letter1 = letter;
								//char letter2 = is_merged_lab_n ? letter + 1 : letter;

								ExcelColChar ecc1 = ecc;
								ExcelColChar ecc2 = is_merged_lab_n ? ecc + 1 : ecc;


								zamach = false;

								for (int ir = 0; ir <= 10; ir++)
								{
									double p1 = 0.0, p2 = 0.0, p, dh = 0.0, dhw = 0.0;
									if (ir)
									{
										sprintf(S, "D%d", fr+r1+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											p1 = val;
										}

										//sprintf(S, "%c%d", letter1, fr+r1+ir);
										sprintf(S, "%s%d", ecc1.Get(), fr+r1+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											dh = val;
										}
									}
									else
									{
										p1 = 0.0;
										dh = 0.0; // при нуле давления в природном состоянии нет осадки
									}

									if (n_krivyh == 2 || n_krivyh == 4)
									{
										sprintf(S, "D%d", fr+r2+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											p2 = val;
										}	

										//sprintf(S, "%c%d", letter2, fr+r2+ir);
										sprintf(S, "%s%d", ecc2.Get(), fr+r2+ir);
										if (ExcelRange_GetValue(m_excel, S, val))
										{
											dhw = val;
										}	
									}

									p = 0;

									if (n_krivyh == 2 && p1!=p2)
									{
										CString s;
										s.Format(									
											"в лабораторном номере %d\n"
											"в методе двух кривых"
											"p1 (%f) не равно p2 (%f)", LAB_N, p1, p2);
										AfxMessageBox(s);
										return;
									}
									else
									{
										switch(n_krivyh)
										{
										case 1:
										case 2:
										case 3:
											p = p1;
											break;
										case 4:
											p = p2;
											break;
										}
									}

									if (p && (dh || dhw))
									{
										unsigned char voda  = 1;
										if (lab_number)	lab_number->AddCompress(id_compress_vyprob, zamach ? -p : p, dh, dhw, voda, 1);
										//if (toSavetoDB)
											setCompress.AddNewRow(ID_OBJ,ID_KT, ID_PROB, id_compress_vyprob, zamach ? -p : p, 0.1 * dh, 0.1 * dhw, voda, 1);
										// в базу - сантиметры, в lab_number - миллиметры!!!
									}
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

								unsigned char id_method = unsigned char (n_krivyh);
								unsigned char bStat = 1;
								unsigned char bStatV = 1;

								if (lab_number)	lab_number->AddCompress(id_compress_vyprob, 	
									// в базу - сантиметры, в lab_number - миллиметры!!!
									10*H, 10*D, 
									es_l1, es_r1, es_l2, es_r2,
									nju, nju_z,
									m01, E1, m02, E2,
									m01v, E1v, m02v, E2v,
									id_method, bStat, bStatV);

								if (lab_number)	lab_number->ApplyCompress(true, 0);
								if (lab_number)	lab_number->CalcProperties();


								LabTrial * lab_trial = lab_number ? lab_number->FindLabTrial(LabTrial::indication::compression_3, -1) : NULL;
								CompressionLabTrial3 * compression3 = dynamic_cast<CompressionLabTrial3 *>(lab_trial);
								if (compression3)
								{
									CompressionLabTrialResults * com_lab_res_1 = dynamic_cast<CompressionLabTrialResults *>(compression3->p_trial_1->results);
									CompressionLabTrialResults * com_lab_res_2 = dynamic_cast<CompressionLabTrialResults *>(compression3->p_trial_2->results);
									if(com_lab_res_1 && com_lab_res_2)
									{


										switch(id_method)
										{
										case 1: // одна кривая
											{
												//1-й Інтервал для визначення модуля деформації
												es_l1 = com_lab_res_1->def_module_01_02_pressure_interval[0];
												es_r1 = com_lab_res_1->def_module_01_02_pressure_interval[1];
												//2-й Інтервал для визначення модуля деформації
												es_l2 = com_lab_res_1->def_module_defined_pressure_interval[0];
												es_r2 = com_lab_res_1->def_module_defined_pressure_interval[1];



												//Коефіцієнт поперечної деформації
												nju = com_lab_res_1->nju_tab.v;
												//Коефіцієнт поперечної деформації у стані водонасичення
												nju_z = com_lab_res_1->nju_tab_ws.v;

												if (com_lab_res_1->a_in_01_02_interval.f)
												{
													//Коефіцієнт стисливості визначений по 1-му інтервалу, природна вологість
													m01 = com_lab_res_1->a_in_01_02_interval.v;
												}
												if (com_lab_res_1->a_in_defined_interval.f)
												{
													//Коефіцієнт стисливості визначений по 2-му інтервалу, природна вологість
													m02 = com_lab_res_1->a_in_defined_interval.v;
												}


												if (com_lab_res_1->deformation_module_e_in_01_02_interval.f)
												{
													//Модуль деформації  визначений по 1-му інтервалу, природна вологість
													E1 = com_lab_res_1->deformation_module_e_in_01_02_interval.v;
												}
												if (com_lab_res_1->deformation_module_e_in_defined_interval.f)
												{
													//Модуль деформації  визначений по 2-му інтервалу, природна вологість
													E2 = com_lab_res_1->deformation_module_e_in_defined_interval.v;
												}


											}
											break;
										case 2: //две кривые
											{
												es_l1 = com_lab_res_1->def_module_01_02_pressure_interval[0];
												es_r1 = com_lab_res_1->def_module_01_02_pressure_interval[1];
												es_l2 = com_lab_res_1->def_module_defined_pressure_interval[0];
												es_r2 = com_lab_res_1->def_module_defined_pressure_interval[1];

												nju = com_lab_res_1->nju_tab.v;
												nju_z = com_lab_res_2->nju_tab_ws.v;


												if (com_lab_res_1->a_in_01_02_interval.f)
												{
													//Коефіцієнт стисливості визначений по 1-му інтервалу, природна вологість
													m01 = com_lab_res_1->a_in_01_02_interval.v;
												}
												if (com_lab_res_1->a_in_defined_interval.f)
												{
													//Коефіцієнт стисливості визначений по 2-му інтервалу, природна вологість
													m02 = com_lab_res_1->a_in_defined_interval.v;
												}

												if (com_lab_res_2->a_in_01_02_interval.f)
												{
													//Коефіцієнт стисливості визначений по 1-му інтервалу, природна вологість
													m01v = com_lab_res_2->a_in_01_02_interval.v;
												}
												if (com_lab_res_2->a_in_defined_interval.f)
												{
													//Коефіцієнт стисливості визначений по 2-му інтервалу, природна вологість
													m02v = com_lab_res_2->a_in_defined_interval.v;
												}





												if (com_lab_res_1->deformation_module_e_in_01_02_interval.f)
												{
													//Модуль деформації  визначений по 1-му інтервалу, природна вологість
													E1 = com_lab_res_1->deformation_module_e_in_01_02_interval.v;
												}
												if (com_lab_res_1->deformation_module_e_in_defined_interval.f)
												{
													//Модуль деформації  визначений по 2-му інтервалу, природна вологість
													E2 = com_lab_res_1->deformation_module_e_in_defined_interval.v;
												}

												if (com_lab_res_2->deformation_module_e_in_01_02_interval.f)
												{
													//Модуль деформації  визначений по 1-му інтервалу,  водонасичений стан
													E1v = com_lab_res_2->deformation_module_e_in_01_02_interval.v;
												}
												if (com_lab_res_2->deformation_module_e_in_defined_interval.f)
												{
													//Модуль деформації  визначений по 2-му інтервалу,  водонасичений стан
													E2v = com_lab_res_2->deformation_module_e_in_defined_interval.v;
												}


											}
										case 3:// одна кривая с замачаванием
											{
												es_l1 = com_lab_res_1->def_module_01_02_pressure_interval[0];
												es_r1 = com_lab_res_1->def_module_01_02_pressure_interval[1];
												es_l2 = com_lab_res_1->def_module_defined_pressure_interval[0];
												es_r2 = com_lab_res_1->def_module_defined_pressure_interval[1];

												nju = com_lab_res_1->nju_tab.v;
												nju_z = com_lab_res_1->nju_tab_ws.v;

												if (com_lab_res_1->a_in_01_02_interval.f)
												{
													//Коефіцієнт стисливості визначений по 1-му інтервалу, природна вологість
													m01 = com_lab_res_1->a_in_01_02_interval.v;
												}
												if (com_lab_res_1->a_in_defined_interval.f)
												{
													//Коефіцієнт стисливості визначений по 2-му інтервалу, природна вологість
													m02 = com_lab_res_1->a_in_defined_interval.v;
												}

												if (com_lab_res_1->deformation_module_e_in_01_02_interval.f)
												{
													//Модуль деформації  визначений по 1-му інтервалу, природна вологість
													E1 = com_lab_res_1->deformation_module_e_in_01_02_interval.v;
												}
												if (com_lab_res_1->deformation_module_e_in_defined_interval.f)
												{
													//Модуль деформації  визначений по 2-му інтервалу, природна вологість
													E2 = com_lab_res_1->deformation_module_e_in_defined_interval.v;
												}

											}
											break;
										case 4:// метод одной кривой в водонасыщенном состоянии
											{
												es_l1 = com_lab_res_2->def_module_01_02_pressure_interval[0];
												es_r1 = com_lab_res_2->def_module_01_02_pressure_interval[1];
												es_l2 = com_lab_res_2->def_module_defined_pressure_interval[0];
												es_r2 = com_lab_res_2->def_module_defined_pressure_interval[1];

												nju = com_lab_res_2->nju_tab.v;
												nju_z = com_lab_res_2->nju_tab_ws.v;

												if (com_lab_res_2->a_in_01_02_interval.f)
												{
													//Коефіцієнт стисливості визначений по 1-му інтервалу, природна вологість
													m01v = com_lab_res_2->a_in_01_02_interval.v;
												}
												if (com_lab_res_2->a_in_defined_interval.f)
												{
													//Коефіцієнт стисливості визначений по 2-му інтервалу, природна вологість
													m02v = com_lab_res_2->a_in_defined_interval.v;
												}

												if (com_lab_res_2->deformation_module_e_in_01_02_interval.f)
												{
													//Модуль деформації  визначений по 1-му інтервалу,  водонасичений стан
													E1v = com_lab_res_2->deformation_module_e_in_01_02_interval.v;
												}
												if (com_lab_res_2->deformation_module_e_in_defined_interval.f)
												{
													//Модуль деформації  визначений по 2-му інтервалу,  водонасичений стан
													E2v = com_lab_res_2->deformation_module_e_in_defined_interval.v;
												}


											}
											break;
										}
									}
								}

								if (D && H)
								{

									if (es_l1 == es_r1)
									{
										CString s;
										s.Format(									
											"в лабораторном номере %d\n"
											"первый интервал расчёта модуля деформации\n"
											"[%f-%f]"
											"некорректен",
											LAB_N, es_l1, es_r1);
										AfxMessageBox(s);
									}

									if (es_l2 == es_r2)
									{
										CString s;
										s.Format(									
											"в лабораторном номере %d\n"
											"второй интервал расчёта модуля деформации\n"
											"[%f-%f]"
											"некорректен",
											LAB_N, es_l2, es_r2);
										AfxMessageBox(s);
									}

									setCilce.AddNewRow(ID_OBJ,ID_KT,ID_PROB, id_compress_vyprob, 
										H,D,				
										es_l1, es_r1, es_l2, es_r2,
										nju, nju_z,
										m01, E1, m02, E2,
										m01v, E1v, m02v, E2v,
										id_method, bStat, bStatV);
									// в базу - сантиметры, в lab_number - миллиметры!!!
								}
							}

							break;
						}
e_next_compress_prob_grunt:
						setProbGr.MoveNext();
					}
				}
			}


			if (!found_lab_n)
			{
				CString s;
				s.Format(
					"Лабораторный номер %d не найден в базе,\n"
					"поэтому данные компрессии по нему не внесены", 
					LAB_N);
				AfxMessageBox(s);
			}

			if (!is_merged_lab_n) // одним столбцом
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
			else // двумя столбцами
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