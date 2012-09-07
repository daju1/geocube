// ExcelArchiveGran.cpp: implementation of the ExcelPlotnostChastic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelArchiveGran.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"
#include "SetGranular.h"
#include "SetGranularAll_2.h"
#include "SetFizMehAllParam.h"

#include "../../excel_connect/src/ExcelColChar.h"

CString GetGranularFraction(CDatabase * database, long id_gran);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <math.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelArchiveGran::ExcelArchiveGran()
{
	m_to_fill_all_lab_numbers = false;


	rows_per_page = 35;
	cols_per_page = 10;
	first_letter = 'F';
/*
ID_PARAM	NAZVA_U	NAZVA_R	bDEFAULT	bIN
39	 ут природного укосу сухого грунту, град	”гол откоса сухого грунта, град	0	1
40	 ут природного укосу грунту п≥д водою, град	”гол откоса грунта под водой, град.	0	1
*/
	npar = 9;
	long _id_params[] = {2,3,1,8,6,50,35, 39, 40};
	long _param_rows[] = {8,9,10,12,13,15,17, 32, 33};

	memcpy(id_params, _id_params, npar*sizeof(long));
	memcpy(param_rows, _param_rows, npar*sizeof(long));

}

ExcelArchiveGran::~ExcelArchiveGran()
{

}
void ExcelArchiveGran::InitExt()
{
	ext					= "agd";
	xl_filter_name		= "јрхивные данные грансостава";
	xl_form				= "ArchiveGranData";
}
void ExcelArchiveGran::FillGranRowsMap(map<long, gran_row> & gran_rows)
{

	SetGranularAll_2 setGranularAll_2(this->p_database);
	setGranularAll_2.m_strFilter.Format("");
	setGranularAll_2.m_strSort.Format("ID_GRAN");
	if (setGranularAll_2.Open(CRecordset::dynaset) )
	{
		if (!setGranularAll_2.IsBOF()) 
		{
			setGranularAll_2.MoveFirst();
			while(!setGranularAll_2.IsEOF()) 
			{
				setGranularAll_2.MoveNext();
			}
		}						
	}

	// таблица сопоставлени€ ID_GRAN со номерами строк Excel таблицы ArchiveGranData - в структуре gran_row
	// если  в структуре gran_row определены две строки тогда необходимо объединение €чеек

	//GranularAll_2
	/*
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

	24	200.0-Е
	25	10.0-200.0
*/


	//	—одержание фракций в процентах размером в мм:	
	// таблица ArchiveGranData
	/*
	row     размер фракции
	19		>200												
	20		200 - 10												
	21		10 Ц 5											
	22		5 Ц 2											
	23		2 Ц 1											
	24		1 Ц 0,5											
	25		0,5 Ц 0,25											
	26		0,25 Ц 0,1											
	27		0,1 Ц 0,05											
	28		0,05 Ц 0,01											
	29		0,01 Ц 0,005											
	30		<0,005	
	*/

	

	gran_rows.insert(map<long, gran_row>::value_type(24, gran_row(19)));	
	gran_rows.insert(map<long, gran_row>::value_type(1, gran_row(19,20)));	
	gran_rows.insert(map<long, gran_row>::value_type(25, gran_row(20)));

	int fer = 21;
	gran_rows.insert(map<long, gran_row>::value_type(21, gran_row(fer++)));	//21
	gran_rows.insert(map<long, gran_row>::value_type(22, gran_row(fer++)));	//22
	gran_rows.insert(map<long, gran_row>::value_type(3, gran_row(fer++)));	//23
	gran_rows.insert(map<long, gran_row>::value_type(4, gran_row(fer++)));	//24
	gran_rows.insert(map<long, gran_row>::value_type(5, gran_row(fer++)));	//25
	gran_rows.insert(map<long, gran_row>::value_type(6, gran_row(fer++)));	//26
	gran_rows.insert(map<long, gran_row>::value_type(7, gran_row(fer++)));	//27
	gran_rows.insert(map<long, gran_row>::value_type(8, gran_row(fer++)));	//28
	gran_rows.insert(map<long, gran_row>::value_type(9, gran_row(fer++)));	//29
	gran_rows.insert(map<long, gran_row>::value_type(10, gran_row(fer++)));	//30

	gran_rows.insert(map<long, gran_row>::value_type(2, gran_row(21,22)));
	gran_rows.insert(map<long, gran_row>::value_type(23, gran_row(27,30)));
}
void ExcelArchiveGran::FillSetGran(map<long, gran_row> & gran_rows, SetGranular & setGranular, int & n, int & fr, char & letter, int & p)
{
	char S[64];


	if (!setGranular.IsBOF()) 
	{
		setGranular.MoveFirst();
		while(!setGranular.IsEOF()) 
		{

			long id_gran = setGranular.m_ID_GRAN;
			map<long, gran_row>::iterator found = gran_rows.find(id_gran);
			if (found != gran_rows.end())
			{
				if ((*found).second.row2)
				{
					sprintf(S, "%c%d:%c%d", letter, fr+(*found).second.row1, letter, fr+(*found).second.row2);
					ExcelRange_SetMerge(m_excel, S);
				}
				sprintf(S, "%c%d", letter, fr+(*found).second.row1);
				ExcelRange_SetValue(m_excel, S, COleVariant(setGranular.m_VAL));
			}
			setGranular.MoveNext();
		}
	}	

		//}

/*
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
	ExcelRange_SetValue(m_excel, S, COleVariant(setCilce.m_H));	*/
}
void ExcelArchiveGran::FillProbGrKT(long ID_OBJ, long ID_KT, long ID_PROB, int & n, int & fr, char & letter)
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
							kt_type = "“—«";
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
	/*if (use_2_colomns)
	{								
		bool list = (!((n+1)%cols_per_page));
		if (!list)
		{						
			sprintf(S, "%c%d:%c%d", letter, fr+3, letter + 1, fr+7);
			ExcelRange_SetMerge(m_excel, S, true);	
		}
	}*/
}
/*
void ExcelArchiveGran::FillReList(int & n, int & fr, char & letter)
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
}*/
void ExcelArchiveGran::FillIncrement(int & n, int & fr, char & letter)
{
/*	if (use_2_colomns)
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
	else*/
	{
		n++;letter++;
		if (!(n%cols_per_page))
		{
			fr += rows_per_page;
			letter = first_letter;
		}
	}
}



bool ExcelArchiveGran::virFill()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Ќе выбран объект");
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
		long gran_records = 0;
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
					SetGranular setGranular(this->p_database);
					setGranular.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
						ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB);
					setGranular.m_strSort.Format("ID_KT, ID_PROB");
					if (setGranular.Open(CRecordset::dynaset) )
					{
						if (!setGranular.IsBOF()) 
						{
							setGranular.MoveFirst();
							while(!setGranular.IsEOF()) 
							{
								setGranular.MoveNext();
							}
						}		 
						long record_count = setGranular.GetRecordCount();
						if (record_count > 0)							
						{
							gran_records ++;
						}
						if (record_count <= 0)
						{
							empty_labn_records++;
						}
					}
					setProbGr_all.MoveNext();
				}
			}	

			long Records = gran_records;
										
			if (this->m_to_fill_all_lab_numbers)
			{
				Records += empty_labn_records;
			}

			//≈сли число лабораторных номеров больше 35, надо скопировать таблицу на вторую страницу
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

			map<long, gran_row> gran_rows;
			FillGranRowsMap(gran_rows);

			
			char letter = first_letter;

			int n = 0;

			if (!setProbGr_all.IsBOF()) 
			{
				setProbGr_all.MoveFirst();
				while(!setProbGr_all.IsEOF()) 
				{
					SetGranular setGranular(this->p_database);
					setGranular.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
						ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB);
					setGranular.m_strSort.Format("ID_KT, ID_PROB");
					if (setGranular.Open(CRecordset::dynaset) )
					{
						if (!setGranular.IsBOF()) 
						{
							setGranular.MoveFirst( );
							while(!setGranular.IsEOF()) 
							{
								setGranular.MoveNext();
							}
						}
						long record_count = setGranular.GetRecordCount();
						if (record_count > 0)
						{
							//this->FillReList(n, fr, letter);
							this->FillSetGran(gran_rows, setGranular, n, fr, letter, p);
							this->FillProbGrKT(ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB, n, fr, letter);
							this->FillIncrement(n, fr, letter);
						}
						if (record_count <= 0 && this->m_to_fill_all_lab_numbers)
						{
							//this->FillReList(n, fr, letter);
							this->FillProbGrKT(ID_OBJ, setProbGr_all.m_ID_KT, setProbGr_all.m_ID_PROB, n, fr, letter);
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
void ExcelArchiveGran::virSaveToDB()
{
	int nObItem = this->m_lab_view->GetObjectItem();
	if (nObItem < 0)
	{
		AfxMessageBox("Ќе выбран объект");
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


		map<long, gran_row> gran_rows;
		FillGranRowsMap(gran_rows);

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
			/*bool is_merged_lab_n = ExcelRange_GetMergeCells(m_excel, S);

			long n_krivyh = 0;
			sprintf(S, "%c%d", letter, fr+16);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				n_krivyh = long(val);
			}
			n_krivyh;

			double 
				H = 0.0,
				D = 0.0;

			sprintf(S, "%c%d", letter, fr+17);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				D = val;
			}

			sprintf(S, "%c%d", letter, fr+18);							
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				H = val;
			}*/

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
							for (long ipar = 0; ipar < npar; ipar++)
							{
								long ID_PARAM = id_params[ipar];
								//sprintf(S, "%c%d",  letter, fr + param_rows[ipar]);
								sprintf(S, "%s%d",  ecc.Get(), fr + param_rows[ipar]);
								if (ExcelRange_GetValue(m_excel, S, val))
								{
									long ID_VYPROB = MEAN_PHYS_VYPROB;

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



							SetGranular setGranular(this->p_database);
							setGranular.m_strFilter.Format(
										"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
										ID_OBJ, ID_KT, ID_PROB);
							if (setGranular.Open(CRecordset::dynaset) )
							{
								int r1 = 19;

								GranVyprob gran_vyprob;
								//map<long, GranVyprobData1> gran_content;
								//gran_content.clear();

								for (int ir = 0; ir < 12; ir++)
								{
									int r = ir + r1;
									double content = 0.0;
									bool content_got = false;
									//sprintf(S, "%c%d", letter, fr+r);
									sprintf(S, "%s%d", ecc.Get(), fr+r);
									if (ExcelRange_GetValue(m_excel, S, val))
									{
										content = val;
										content_got = true;
									}

									long id_gran = 0;

									bool is_merged_content = ExcelRange_GetMergeCells(m_excel, S);
									if (is_merged_content)
									{
										CString adress = ExcelRange_GetMergeArea(m_excel, S);
										int i2p = adress.Find(':');
										CString left = adress.Mid(1, i2p-1);
										int ils = left.Find('$');
										CString left_letter = left.Left(ils);
										CString left_row = left.Mid(ils+1);
										int row_1 = atoi(left_row);
										int row1 = row_1 - fr;
										if (fr+r != row1)
										{
											CString s;
											s.Format("(fr(%d)+r(%d) %d != row1 %d)", fr, r, fr+r, row1);
											AfxMessageBox(s);
										}
										CString right = adress.Mid(i2p+1+1);
										int irs = right.Find('$');
										CString right_letter = right.Left(irs);
										CString right_row = right.Mid(irs+1);
										int row_2 = atoi(right_row);
										int row2 = row_2 - fr;

										
										for (map<long, gran_row>::iterator it = gran_rows.begin();
											it != gran_rows.end(); it++)
										{											
											if ((*it).second.row2)
											{
												if ((*it).second.row2 == row2 && (*it).second.row1 == row1)
												{
													id_gran = (*it).first;
												}
											}
										}

										if (!id_gran)
										{
											CString s;
											s.Format("ƒл€ объединени€ строк\n"
												"со строки %d по строку %d\n"
												"не найдена сооответствующа€ фракци€", 
												row1, row2);
											AfxMessageBox(s);
										}
										else
										{
										}


										//CString s;
										//s.Format("ir_pre = %d)", ir);
										//AfxMessageBox(s);

										ir = row2-r1;

										//s.Format("ir_post = %d)", ir);
										//AfxMessageBox(s);
									}
									else
									{									
										for (map<long, gran_row>::iterator it = gran_rows.begin();
											it != gran_rows.end(); it++)
										{											
											if (!(*it).second.row2)
											{
												if ((*it).second.row1 == r)
												{
													id_gran = (*it).first;
												}
											}
										}
										if (!id_gran)
										{
											CString s;
											s.Format("ƒл€ строки %d \n"
												"не найдена сооответствующа€ фракци€", 
												r);
											AfxMessageBox(s);
										}
									}

									if (id_gran && content_got)
									{
										//gran_content.insert(map<long, GranVyprobData1>::value_type(id_gran, GranVyprobData1(id_gran, GetGranularFraction(p_database, id_gran), content)));
										gran_vyprob.AddGranular(id_gran, GetGranularFraction(p_database, id_gran), content);
										/*CString s;
										s.Format("content of %s = %f)",
											GetGranularFraction(p_database, id_gran), content);
										AfxMessageBox(s);	*/								
									}
									
									//setGranular.AddNewRow(ID_OBJ, ID_KT, ID_PROB);
								}


								setGranular.ReplaceGranContent(ID_OBJ, ID_KT, ID_PROB, LAB_N, gran_vyprob);
							}
							break;
						}
						setProbGr.MoveNext();
					}
				}
			}


			if (!found_lab_n)
			{
				CString s;
				s.Format(
					"Ћабораторный номер %d не найден в базе,\n"
					"поэтому данные грансостава по нему не внесены", 
					LAB_N);
				AfxMessageBox(s);
			}

			//if (!is_merged_lab_n) // одним столбцом
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
					ecc.Init(first_letter);
				}
#endif
			}
			/*else // двум€ столбцами
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
			}*/



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