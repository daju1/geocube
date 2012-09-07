// ExcelWlazhnost.cpp: implementation of the ExcelWlazhnost class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelWlazhnost.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"
#include "SetCilce0.h"
#include "SetZriz0.h"

#include "DlgRepeatings.h"

#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelWlazhnost::ExcelWlazhnost()
{
}

ExcelWlazhnost::~ExcelWlazhnost()
{

}
void ExcelWlazhnost::InitExt()
{
	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			ext					= "w";
			xl_filter_name		= "Wlazhnost";
			xl_form				= "W";
		}
		break;
	case 3:
		{
			ext					= "w3";
			xl_filter_name		= "Wlazhnost";
			xl_form				= "W3";
		}
		break;
	case 6:
		{
			ext					= "w6";
			xl_filter_name		= "Wlazhnost";
			xl_form				= "W6";
		}
		break;
	}
}
bool ExcelWlazhnost::virCompute(bool)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	char S[64];
	char F[1024];

	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			int fr = 12;
			for (int r = 0; r <= 22; r++)
			{
				int row1 = fr + 2*r;
				int row2 = fr + 2*r + 1;

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

				sprintf(S, "I%d", row1);
				sprintf(F, "=(F%d-G%d)/(G%d-H%d)", row1, row1, row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.SetNumberFormat(COleVariant("0.000"));
				m_range.ReleaseDispatch();	

				// определяем занесена ли в таблицу вторая повторность
				bool use_row_2 = false;
				double v;
				sprintf(S, "F%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "G%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "H%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);

				if (use_row_2)
				{
					sprintf(S, "I%d", row2);
					sprintf(F, "=(F%d-G%d)/(G%d-H%d)", row2, row2, row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();
				}

				if (use_row_2)
				{
					sprintf(S, "J%d", row1);
					sprintf(F, "=0.5*(I%d+I%d)", row1, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
				else
				{
					sprintf(S, "J%d", row1);
					sprintf(F, "=I%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

			}
		}
		break;
	case 3:
		{
			int fr = 12;
			for (int r = 0; r <= 14; r++)
			{
				int row1 = fr + 3*r;
				int row2 = fr + 3*r + 1;
				int row3 = fr + 3*r + 2;

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

				sprintf(S, "I%d", row1);
				sprintf(F, "=(F%d-G%d)/(G%d-H%d)", row1, row1, row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.SetNumberFormat(COleVariant("0.000"));
				m_range.ReleaseDispatch();	

				double v;

				// определяем занесена ли в таблицу вторая повторность
				bool use_row_2 = false;
				sprintf(S, "F%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "G%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "H%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);

				// определяем занесена ли в таблицу 3-я повторность
				bool use_row_3 = false;
				sprintf(S, "F%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "G%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "H%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);

				if (use_row_2)
				{
					sprintf(S, "I%d", row2);
					sprintf(F, "=(F%d-G%d)/(G%d-H%d)", row2, row2, row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();
				}
				if (use_row_3)
				{
					sprintf(S, "I%d", row3);
					sprintf(F, "=(F%d-G%d)/(G%d-H%d)", row3, row3, row3, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();
				}

				if (use_row_2 && use_row_3)
				{
					sprintf(S, "J%d", row1);
					sprintf(F, "=(I%d+I%d+I%d)/3.0", row1, row2, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
				else if (use_row_2 && ! use_row_3)
				{
					sprintf(S, "J%d", row1);
					sprintf(F, "=0.5*(I%d+I%d)", row1, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
				else
				{
					sprintf(S, "J%d", row1);
					sprintf(F, "=I%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

			}
		}
		break;
	case 6:
		{
			int fr = 12;
			for (int r = 0; r <= 7; r++)
			{
				int row1 = fr + 6*r;
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

				int row[6];
				bool use_row[6];
				CString mean_formula = "", s;
				int n = 0;
				for (int i = 0; i < 6; i++)
				{
					row[i] = fr + 6*r + i;

					double v;
					// определяем занесена ли в таблицу i-ая повторность
					use_row[i] = false;
					sprintf(S, "F%d", row[i]);
					use_row[i] |= ExcelRange_GetValue(m_excel, S, v);
					sprintf(S, "G%d", row[i]);
					use_row[i] |= ExcelRange_GetValue(m_excel, S, v);
					sprintf(S, "H%d", row[i]);
					use_row[i] |= ExcelRange_GetValue(m_excel, S, v);
					
					if (use_row[i])
					{
						sprintf(S, "I%d", row[i]);
						sprintf(F, "=(F%d-G%d)/(G%d-H%d)", row[i], row[i], row[i], row[i]);
						VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
						m_range.AttachDispatch(pRange);		
						m_range.SetValue(COleVariant(F));
						m_range.SetNumberFormat(COleVariant("0.000"));
						m_range.ReleaseDispatch();

						s.Format("I%d", row[i]);

						if (!n)
						{
							mean_formula = "=(" + s;
						}
						else
						{
							mean_formula +=  "+" + s;
						}
						n++;
					}
				}

				if (n)
				{
					mean_formula +=  ")";

					if (n > 1)
					{
						s.Format("/%d.0", n);
						mean_formula +=  s;
					}

					sprintf(S, "J%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(mean_formula));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
			}
		}
		break;
	}
	return true;
}


void ExcelWlazhnost::virSaveToDB()
{
	double digits_epsilon = 1e-8;
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
				fr = 12;
				nr = 22;
				m = 2;
			}
			break;
		case 3:
			{
				fr = 12;
				nr = 14;
				m = 3;
			}
			break;
		case 6:
			{
				fr = 12;
				nr = 7;
				m = 6;
			}
			break;
		}

		for (int r = 0; r <= nr; r++)
		{
			int row1 = fr + m*r;

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

			// ID_OBJ ID_KT ID_PROB ID_VYPROB

			long ID_KT = -1;
			long ID_PROB = -1;

			long ID_PARAM = 1;
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

			long ID_PHYS_VYPROB = MEAN_PHYS_VYPROB;
			int nv = this->save_different_vyprob ? m : 1;
			long id_compress_vyprob = 0;
			long id_cut_vyprob = 0;
			if (this->save_different_vyprob)
			{
				switch (CDlgRepeatings::s_repeatings)
				{
				case 2: // компрессия
					{
						bool add_cut_from_db = false;
						bool add_compress_from_db = true;
						long nCutItem = 0;
						long nCompItem = 0;
						bool add_stat_zond_from_db = false;
						LabNumber * lab_number2 = this->m_lab_view->CreateLabNumber(lab_n, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
						id_compress_vyprob = lab_number2 ? lab_number2->GetCompressVyprobMaxID() + 1 : 1;
						//ID_VYPROB = 2 * (id_compress_vyprob - 1) + 2 - 1;
					}
					break;
				case 3: // срез
				case 6: // срез
					{
						bool add_cut_from_db = true;
						bool add_compress_from_db = false;
						long nCutItem = 0;
						long nCompItem = 0;
						bool add_stat_zond_from_db = false;
						LabNumber * lab_number2 = this->m_lab_view->CreateLabNumber(lab_n, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db);
						id_cut_vyprob = lab_number2 ? lab_number2->GetCutVyprobMaxID() + 1 : 1;
						//ID_VYPROB = - 6 * (id_cut_vyprob - 1) - 6 + 1;
					}
					break;
				}
			}


			for (int iv = 0; iv < nv; iv++)
			{
				long id_kolca = iv + 1;
				if (this->save_different_vyprob)
				{
					switch (CDlgRepeatings::s_repeatings)
					{
					case 2: // компрессия
						{
							//ID_VYPROB++;
							ID_PHYS_VYPROB = GetFizMehVyprobForCompress(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, id_kolca);
						}
						break;
					case 3: // срез
					case 6: // срез
						{
							//ID_VYPROB--;
							ID_PHYS_VYPROB = GetFizMehVyprobForCut(this->p_database, ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
						}
						break;
					}
				}


				SetFizMeh setFizMeh_2(this->p_database);
				setFizMeh_2.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
					ID_OBJ, ID_KT, ID_PROB, ID_PHYS_VYPROB, ID_PARAM);
				if ( !setFizMeh_2.Open(CRecordset::dynaset) )
					return;

				if (this->save_different_vyprob)
				{
					double val;						
					sprintf(S, "I%d", row1 + iv);

					if(ExcelRange_GetValue(m_excel, S, val))
					{
						int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, lab_n, 
							ID_PARAM, ID_PHYS_VYPROB, val);

						switch (CDlgRepeatings::s_repeatings)
						{
						case 2: // компрессия
							{
								SetCilce0 setCilce0(this->p_database);
								setCilce0.m_strFilter.Format(
									"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_KOLCA = %d", 
									ID_OBJ, ID_KT, ID_PROB, id_compress_vyprob, id_kolca);
								if ( !setCilce0.Open(CRecordset::dynaset) )
									return;

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
									setCilce0.m_ID_KOLCA = id_kolca;
									setCilce0.m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;
									to_add_cilce_0 = true;							
								}
								if(to_add_cilce_0)
								{
									setCilce0.m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;

									double m_kolca = 0.0;
									sprintf(S, "H%d", row1 + iv);
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
									sprintf(S, "F%d", row1 + iv);
									if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
									{
										bool to_set = true;
										if (to_edit_cilce_0 && setCilce0.m_M_GRUNTA && fabs(setCilce0.m_M_GRUNTA - (val - m_kolca)) >= digits_epsilon)
										{
											CString s;
											s.Format(
												"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
												"setCilce0.m_M_GRUNTA (%f) != val (%f) - m_kolca(%f)"
												"\nЗаменить?"
												,
												lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
												setCilce0.m_M_GRUNTA, val, m_kolca);
											to_set = IDYES == AfxMessageBox(s, MB_YESNO);
										}
										if (to_set)
										{
											setCilce0.m_M_GRUNTA = val - m_kolca;
										}
									}
									sprintf(S, "G%d", row1 + iv);
									if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
									{
										bool to_set = true;
										if (to_edit_cilce_0 && setCilce0.m_M_GRUNTA_VYSUSH && fabs(setCilce0.m_M_GRUNTA_VYSUSH - (val - m_kolca)) >= digits_epsilon)
										{
											CString s;
											s.Format(
												"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
												"setCilce0.m_M_GRUNTA_VYSUSH (%f) != val (%f) - m_kolca(%f)"
												"\nЗаменить?"
												,
												lab_n, id_compress_vyprob, id_kolca, ID_PHYS_VYPROB,
												setCilce0.m_M_GRUNTA_VYSUSH, val, m_kolca);
											to_set = IDYES == AfxMessageBox(s, MB_YESNO);
										}
										if (to_set)
										{
											setCilce0.m_M_GRUNTA_VYSUSH = val - m_kolca;
										}
									}
									setCilce0.Update();
								}
							}
							break;
						case 3: // срез
						case 6: // срез
							{
								SetZriz0 setZriz0(this->p_database);
								setZriz0.m_strFilter.Format(
									"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_KOLCA = %d", 
									ID_OBJ, ID_KT, ID_PROB, id_cut_vyprob, id_kolca);
								if ( !setZriz0.Open(CRecordset::dynaset) )
									return;

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
									setZriz0.m_ID_KOLCA = id_kolca;
									setZriz0.m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;
									to_add_cilce_0 = true;							
								}
								if(to_add_cilce_0)
								{
									setZriz0.m_ID_PHYS_VYPROB = ID_PHYS_VYPROB;

									double m_kolca = 0.0;
									sprintf(S, "H%d", row1 + iv);
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
									sprintf(S, "F%d", row1 + iv);
									if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
									{
										bool to_set = true;
										if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA && fabs(setZriz0.m_M_GRUNTA - (val - m_kolca)) >= digits_epsilon)
										{
											CString s;
											s.Format(
												"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
												"setZriz0.m_M_GRUNTA (%f) != val (%f) - m_kolca(%f)"
												"\nЗаменить?"
												,
												lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
												setZriz0.m_M_GRUNTA, val, m_kolca);
											to_set = IDYES == AfxMessageBox(s, MB_YESNO);
										}
										if (to_set)
										{
											setZriz0.m_M_GRUNTA = val - m_kolca;
										}
									}
									sprintf(S, "G%d", row1 + iv);
									if(m_kolca && ExcelRange_GetValue(m_excel, S, val))
									{
										bool to_set = true;
										if (to_edit_cilce_0 && setZriz0.m_M_GRUNTA_VYSUSH && fabs(setZriz0.m_M_GRUNTA_VYSUSH - (val - m_kolca)) >= digits_epsilon)
										{
											CString s;
											s.Format(
												"lab_n = %d and ID_VYPROB = %d and ID_KOLCA = %d and ID_PHYS_VYPROB = %d\n"
												"setZriz0.m_M_GRUNTA_VYSUSH (%f) != val (%f) - m_kolca(%f)"
												"\nЗаменить?"
												,
												lab_n, id_cut_vyprob, id_kolca, ID_PHYS_VYPROB,
												setZriz0.m_M_GRUNTA_VYSUSH, val, m_kolca);
											to_set = IDYES == AfxMessageBox(s, MB_YESNO);
										}
										if (to_set)
										{
											setZriz0.m_M_GRUNTA_VYSUSH = val - m_kolca;
										}
									}
									setZriz0.Update();
								}
							}
							break;
						}
					}

				}
				else
				{
					double val;						
					sprintf(S, "J%d", row1);

					if(ExcelRange_GetValue(m_excel, S, val))
					{
						int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, lab_n, 
							ID_PARAM, ID_PHYS_VYPROB, val);
					}
				}	
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