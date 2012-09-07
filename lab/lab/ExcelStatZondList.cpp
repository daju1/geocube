// ExcelStatZondList.cpp: implementation of the ExcelStatZondList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelStatZondList.h"
#include "EnGeologyView.h"

#include "DlgStatZond.h"

#include "SetObject.h"
#include "SetLito.h"
#include "SetIGE.h"
#include "SetKT.h"
#include "SetPtStZond.h"
#include "SetGrunty.h"
#include "SetStZond.h"
#include "SetUstanovka.h"

#include "labView.h"

void DeleteEndZeros(CString & str);


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelStatZondList::ExcelStatZondList()
{
	this->output = false;
}

ExcelStatZondList::~ExcelStatZondList()
{

}
void ExcelStatZondList::InitExt()
{
	if (this->output)
	{
		ext					= "tszp";
		xl_filter_name		= "Статическое зондирование";
		xl_form				= "StatZondOutput";
	}
	else
	{
		ext					= "tsz";
		xl_filter_name		= "Статическое зондирование";
		xl_form				= "StatZond";
	}

}
void Fill_Graph(MyExcel & m_excel,
				int fr, int nrows,
				double min_y, 
				double max_y,
				bool use_q10,
				long TYP_ZOND)
{

	if (true)			
	{							
		double x,y;

		LPDISPATCH pShapes; 
		Shapes10    m_shapes;
			
		VERIFY(pShapes = m_excel.m_worksheet.GetShapes());				
		m_shapes.AttachDispatch(pShapes);	

		long shapes_count = m_shapes.GetCount();
		printf("shapes_count = %d\n", shapes_count);

		int c1, c2, n_lines = 2;
		for (long ish = 1; ish <= shapes_count; ish++)
		{
			switch (ish)
			{
			case 1:// график 1
				{
					c1 = use_q10 ? 7 : 4;
					c2 = 5;
				}
				break;
			case 2:// график 2
				{
					c1 = 4;
					c2 = 14;
				}
				break;
			}

			switch (ish)
			{
			case 1:// график 1
			case 2:// график 2
				{
					LPDISPATCH pShape; 
					Shape10    m_shape;

					VERIFY(pShape = m_shapes.Item(COleVariant(long(ish))));				
					m_shape.AttachDispatch(pShape);	

					CString shape_name = m_shape.GetName();
					printf("%s\n", (LPCTSTR)shape_name);

					LPDISPATCH pChartObject; 
					ChartObject10    m_chart_object;

					VERIFY(pChartObject = m_excel.m_worksheet.ChartObjects(COleVariant(shape_name)));				
					m_chart_object.AttachDispatch(pChartObject);

					LPDISPATCH pChart;
					_Chart10    m_chart;

					VERIFY(pChart = m_chart_object.GetChart());
					m_chart.AttachDispatch(pChart); 
					
					bool use_table = true;
					if (use_table)
					{

						char sdataY[64];
						sprintf(sdataY, "=Лист1!R%dC1:R%dC1", fr, fr-1 + nrows);
						char sdataX[64];
						switch (n_lines)
						{
						case 2:
							{
								for (int isc = 1; isc <= n_lines; isc++)
								{
									switch (isc)
									{
									case 1:
										{
											sprintf(sdataX, "=Лист1!R%dC%d:R%dC%d", fr, c1, fr-1 + nrows, c1);
										}
										break;
									case 2:			
										{
											sprintf(sdataX, "=Лист1!R%dC%d:R%dC%d", fr, c2, fr-1 + nrows, c2);
										}
										break;
									}

									LPDISPATCH pSeries;
									Series10    m_series;
									VERIFY(pSeries = m_chart.SeriesCollection(COleVariant(long(isc))));
									m_series.AttachDispatch(pSeries);
									try
									{
										m_series.SetXValues(COleVariant(sdataX));
										m_series.SetValues(COleVariant(sdataY));
									}
									catch(...)
									{
										//MessageBox(0, sdataX, sdataY, 0);
									}

									if (ish == 1) // график 1
									{
										switch (TYP_ZOND)
										{
										case 1:
											{
												switch (isc)
												{
												case 1:
													{		
														if (use_q10)
															m_series.SetName("q*k, МПа");
														else
															m_series.SetName("q, МПа");
													}
													break;
												case 2:			
													{
														m_series.SetName("Qs, кН");
													}
													break;
												}											
											}
											break;
										case 2:
											{
												switch (isc)
												{
												case 1:
													{
														if (use_q10)
															m_series.SetName("q*k, МПа");
														else
															m_series.SetName("q, МПа");
													}
													break;
												case 2:			
													{
														m_series.SetName("f,кПа");
													}
													break;
												}										}
											break;
										}


									}
									m_series.ReleaseDispatch();
								}


							}
							break;
						}
						/*LPDISPATCH pAxes_x;
						VERIFY(pAxes_x = m_chart.Axes(COleVariant(long (1)), 1));//axis X - [AxisGroup As XlAxisGroup = xlPrimary];
						Axis10    m_axis_x;
						m_axis_x.AttachDispatch(pAxes_x);
						m_axis_x.SetMinimumScale(0.0);
						m_axis_x.SetMaximumScale(max_x + delta_x);
						m_axis_x.ReleaseDispatch();*/

						LPDISPATCH pAxes_y;
						VERIFY(pAxes_y = m_chart.Axes(COleVariant(long (2)), 1));
						Axis10    m_axis_y;
						m_axis_y.AttachDispatch(pAxes_y);
						m_axis_y.SetMinimumScale(min_y);
						m_axis_y.SetMaximumScale(max_y);
						m_axis_y.ReleaseDispatch();
					}

					m_chart.ReleaseDispatch();
					m_chart_object.ReleaseDispatch();				
					m_shape.ReleaseDispatch();
				}
				break;
			}

		}

		m_shapes.ReleaseDispatch();				
	}	
}
bool ExcelStatZondList::virFill()
{
	bool use_q10 = true;

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return false;
	}

	int nKTItem = this->m_lab_view->GetKTItem();

	if (nKTItem < 0)
	{
		AfxMessageBox("Не выбрано ни одной KT");
		return false;
	}

	char S[64];
	char F[64];
	int fr = 13;	

	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		setKT.SetAbsolutePosition(nKTItem + 1);        
		long ID_KT = setKT.m_ID_KT;

		SetPtStZond setPtStZond(this->p_database);
		setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		setPtStZond.m_strSort.Format("");
		if ( !setPtStZond.Open(CRecordset::dynaset) )
			return false;
		if (!setPtStZond.IsBOF()) 
		{
			setPtStZond.MoveFirst( );
			while(!setPtStZond.IsEOF()) 
			{
				setPtStZond.MoveNext();
			}
		}
		long rec = setPtStZond.GetRecordCount();

		long ID_UST = -1;

		if (rec)
		{
			if (!setPtStZond.IsBOF()) 
			{
				setPtStZond.MoveFirst( );
				if(!setPtStZond.IsEOF()) 
				{
					ID_UST = setPtStZond.m_ID_UST;
				}
			}
		}
		else
		{
			CDlgStatZond dialog(this->m_lab_view, this->m_lab_doc, this->p_database);
			dialog.DoModal();
			if (dialog.ok_pressed)
			{
				ID_UST = dialog.id_ust_selected;
			}
		}

		ExcelRange_SetValue(m_excel, "OBJECT", COleVariant(setObject.m_NAZVA));
		ExcelRange_SetValue(m_excel, "TSZ", COleVariant(setKT.m_NAZVA));
		
		SetUstanovka setUstanovka(this->p_database);
		setUstanovka.m_strFilter.Format("");
		setUstanovka.m_strSort.Format("");
		if ( !setUstanovka.Open(CRecordset::dynaset) )
			return false;

		int i_ust = 0;

		double Kg = 0.0;
		double Kf = 0.0;
		double Bg = 0.0;
		double Bf = 0.0;

		long TYP_ZOND = -1;


		double Shtanga_d = 0.0;

		if (!setUstanovka.IsBOF()) 
		{
			setUstanovka.MoveFirst( );
			while(!setUstanovka.IsEOF()) 
			{
				if (ID_UST == setUstanovka.m_ID_UST)
				{
					ExcelRange_SetValue(m_excel, "ID_UST", COleVariant(ID_UST));
					ExcelRange_SetValue(m_excel, "UST", COleVariant(setUstanovka.m_NAZVA));
					ExcelRange_SetValue(m_excel, "ZOND_TYPE", COleVariant(setUstanovka.m_TYP_ZOND));

					TYP_ZOND = setUstanovka.m_TYP_ZOND;

					switch (setUstanovka.m_TYP_ZOND)
					{
					case 1:
						{
							ExcelRange_SetValue(m_excel, "EQ2_NAME", COleVariant("Уравнение для расчёта Qs, кН"));
							ExcelRange_SetValue(m_excel, "COL3_NAME", COleVariant("Qo"));
							ExcelRange_SetValue(m_excel, "COL5_NAME", COleVariant("Qs, кН"));
						}
						break;
					case 2:
						{
							ExcelRange_SetValue(m_excel, "EQ2_NAME", COleVariant("Уравнение для расчёта f,кПа"));
							ExcelRange_SetValue(m_excel, "COL3_NAME", COleVariant("fo"));
							ExcelRange_SetValue(m_excel, "COL5_NAME", COleVariant("f,кПа"));
						}
						break;
					}
					
					Kg = setUstanovka.m_Kg;
					Kf = setUstanovka.m_Kf;
					Bg = setUstanovka.m_Bg;
					Bf = setUstanovka.m_Bf;

					Shtanga_d = setUstanovka.m_Shtanga_d;

					CString sKg, sKf, sBg, sBf;
					sKg.Format("%f", Kg);
					sKf.Format("%f", Kf);
					sBg.Format("%f", Bg);
					sBf.Format("%f", Bf);

					DeleteEndZeros(sKg);
					DeleteEndZeros(sKf);
					DeleteEndZeros(sBg);
					DeleteEndZeros(sBf);

					CString formula_1;	
					formula_1.Format("%s * q0 + %s", sKg, sBg);
					CString formula_2;
					switch (setUstanovka.m_TYP_ZOND)
					{
					case 1:
						{
							formula_2.Format("%s * Qo + %s", sKf, sBf);
						}
						break;
					case 2:
						{
							formula_2.Format("%s * fo + %s", sKf, sBf);
						}
						break;
					}
					
					ExcelRange_SetValue(m_excel, "EQUATION_1", COleVariant(formula_1));
					ExcelRange_SetValue(m_excel, "EQUATION_2", COleVariant(formula_2));

	
				}

				setUstanovka.MoveNext();
				i_ust++;
			}
		}

		SetStZond setStZond(this->p_database);
		setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		setStZond.m_strSort.Format("NPP");
		if ( !setStZond.Open(CRecordset::dynaset) )
			return false;

		vector<double> vh, vq, vf;


		if (use_q10)
		{
			ExcelRange_SetValue(m_excel, "G9", COleVariant("k="));
			ExcelRange_SetValue(m_excel, "H9", COleVariant(10.0));
			ExcelRange_RightHorizontalAlignment(m_excel, "G9");
			ExcelRange_LeftHorizontalAlignment(m_excel, "H9");
		}

		double min_y = DBL_MAX; 
		double max_y = - DBL_MAX; 

		int r = fr;
		int nrows = 0;
		if (!setStZond.IsBOF()) 
		{
			setStZond.MoveFirst( );
			while(!setStZond.IsEOF()) 
			{
				sprintf(S, "A%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setStZond.m_H));
				sprintf(S, "B%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setStZond.m_q0));
				sprintf(S, "C%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setStZond.m_f0));

				double q = setStZond.m_q0 * Kg + Bg;
				double f = setStZond.m_f0 * Kf + Bf;


				sprintf(S, "D%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(q));
				sprintf(S, "E%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(f));

				if (use_q10)
				{
					sprintf(S, "G%d", r);
					sprintf(F, "=D%d*H9", r);


					ExcelRange_SetValue(m_excel, S, COleVariant(F));
				}

				if (TYP_ZOND == 1)
				{
					vh.push_back(setStZond.m_H);
					vq.push_back(q);
					vf.push_back(f);
				}

				if (max_y < setStZond.m_H) max_y = setStZond.m_H; 
				if (min_y > setStZond.m_H) min_y = setStZond.m_H; 

				sprintf(S, "A%d:E%d", r, r);
				ExcelRange_SetThinContinuousBorders(m_excel, S);

				setStZond.MoveNext();
				r++;
				nrows++;
			}
		}

		if (TYP_ZOND == 1)
		{
			sprintf(S, "P9");
			ExcelRange_SetValue(m_excel, S, COleVariant(0.1));
			r = 11;
			sprintf(S, "L%d", r);
			ExcelRange_SetValue(m_excel, S, COleVariant("Псевдо PCB, кПа"));
			sprintf(S, "L%d:L%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);
			ExcelRange_WrapText(m_excel, S);
			for (int i = 1; i < int(vh.size())-1; i++)
			{
				//прирост сопротивления на боковой поверхности сваи
				double dQs = vf[i + 1] - vf[i - 1];//кН
				//соответствующий прирост глубины
				double dh =  vh[i + 1] - vh[i - 1];//м

				// периметр
				double P = PI * Shtanga_d;
				// приращение площади штанги
				double dS = dh * P;

				//ПсевдоPCB
				double pseudoPCB = dQs / dS;//кПа

				r = fr + i;
				sprintf(S, "L%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(pseudoPCB));

				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterVerticalAlignment(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);

				sprintf(S, "N%d", r);
				sprintf(F, "=L%d*P9", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(F));
			}
		}

		if (this->output)
		{
			Fill_Graph(m_excel,
				fr, nrows,
				min_y, 
				max_y,
				use_q10,
				TYP_ZOND);
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
bool ExcelStatZondList::virCompute(bool)
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return false;
	}

	int nKTItem = this->m_lab_view->GetKTItem();

	if (nKTItem < 0)
	{
		AfxMessageBox("Не выбрано ни одной KT");
		return false;
	}

	char S[64];
	int fr = 13;	

	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		setKT.SetAbsolutePosition(nKTItem + 1);        
		long ID_KT = setKT.m_ID_KT;

		long ID_UST = -1;
		double val;
		if(ExcelRange_GetValue(m_excel, "ID_UST", val))
		{
			ID_UST = long(val);
		}

		SetUstanovka setUstanovka(this->p_database);
		setUstanovka.m_strFilter.Format("");
		setUstanovka.m_strSort.Format("");
		if ( !setUstanovka.Open(CRecordset::dynaset) )
			return false;

		int i_ust = 0;

		double Kg = 0.0;
		double Kf = 0.0;
		double Bg = 0.0;
		double Bf = 0.0;

		long TYP_ZOND = 0;

		if (!setUstanovka.IsBOF()) 
		{
			setUstanovka.MoveFirst( );
			while(!setUstanovka.IsEOF()) 
			{
				if (ID_UST == setUstanovka.m_ID_UST)
				{

					TYP_ZOND = setUstanovka.m_TYP_ZOND;

					Kg = setUstanovka.m_Kg;
					Kf = setUstanovka.m_Kf;
					Bg = setUstanovka.m_Bg;
					Bf = setUstanovka.m_Bf;	
				}

				setUstanovka.MoveNext();
				i_ust++;
			}
		}

		for (int r = fr; ; r++)
		{
			sprintf(S, "A%d", r);
			if(!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}
			double H = val;
			sprintf(S, "B%d", r);
			if(!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}

			double q0 = val;

			sprintf(S, "C%d", r);
			if(!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}
			double f0 = val;

			sprintf(S, "D%d", r);
			ExcelRange_SetValue(m_excel, S, COleVariant(q0 * Kg + Bg));
			sprintf(S, "E%d", r);
			ExcelRange_SetValue(m_excel, S, COleVariant(f0 * Kf + Bf));	

			sprintf(S, "A%d:E%d", r, r);
			ExcelRange_SetThinContinuousBorders(m_excel, S);

		}

	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
	}
	return true;
}
long GetTypeGrunt(bool pck, bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_IGE);

long GetTypeGrunt(bool pck, bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_KT, double H, long & ID_IGE)
{
	long TYPGR = 0;

	SetLito setLito(bUnEdited, database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setLito.m_strSort.Format("H1");
	if ( !setLito.Open(CRecordset::dynaset) )
		return 0;

	ID_IGE = -1;

	if (!setLito.IsBOF()) 
	{
		setLito.MoveFirst( );
		while(!setLito.IsEOF()) 
		{
			if (H >= setLito.m_H0 && H <= setLito.m_H1)
			{
                ID_IGE = setLito.m_ID_IGE;
				break;
			}

			setLito.MoveNext();
		}
	}	
	return GetTypeGrunt(pck, bUnEdited, database, ID_OBJ, ID_IGE);
}
void ExcelStatZondList::Save(long ID_OBJ, long ID_KT)
{
	char S[64];
	int fr = 13;	
	try
	{
		long ID_UST = -1;
		double val;
		if(ExcelRange_GetValue(m_excel, "ID_UST", val))
		{
			ID_UST = long(val);
		}

		SetPtStZond setPtStZond(this->p_database);
		setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		setPtStZond.m_strSort.Format("");
		if ( !setPtStZond.Open(CRecordset::dynaset) )
			return;
		if (!setPtStZond.IsBOF()) 
		{
			setPtStZond.MoveFirst( );
			while(!setPtStZond.IsEOF()) 
			{
				setPtStZond.MoveNext();
			}
		}
		long rec = setPtStZond.GetRecordCount();


		SetStZond setStZond(this->p_database);
		setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
		setStZond.m_strSort.Format("NPP");
		if ( !setStZond.Open(CRecordset::dynaset) )
			return;

		if (!setStZond.IsBOF()) 
		{
			setStZond.MoveFirst( );
			while(!setStZond.IsEOF()) 
			{
				setStZond.Delete();
				setStZond.MoveNext();
			}
		}
		long NPP = 1;

		double H_pre, f0_pre, GLYB;

		double dH = 0.0;
		double fsr = 0.0;
		BYTE bSTAT = 1;

		for (int r = fr; ; r++, NPP++)
		{
			sprintf(S, "A%d", r);
			if(!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}
			double H = val;
			sprintf(S, "B%d", r);
			if(!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}
			long ID_IGE;
			//для вычислений несущей способности свай тип грунта берём из редактируемой лито-колонки
			bool bUnEdited = false;
			long TYPGR = GetTypeGrunt(false, bUnEdited, this->p_database, ID_OBJ, ID_KT, H, ID_IGE);

			double q0 = val;

			sprintf(S, "C%d", r);
			if(!ExcelRange_GetValue(m_excel, S, val))
			{
				break;
			}
			double f0 = val;

			if (NPP > 1)
			{
				dH = H - H_pre;
				fsr = 0.5 * (f0 + f0_pre);
			}			

			setStZond.AddNewRow_(ID_OBJ, ID_KT, NPP, TYPGR, H, q0, f0, dH, fsr, bSTAT, ID_IGE);

			H_pre = H;
			f0_pre = f0;
			GLYB = H;
		}

		if (rec)
		{
			if (!setPtStZond.IsBOF()) 
			{
				setPtStZond.MoveFirst( );
				if(!setPtStZond.IsEOF()) 
				{
					setPtStZond.Edit();
					setPtStZond.m_ID_UST = ID_UST;
					setPtStZond.m_GLYB = GLYB;
					setPtStZond.Update();					
				}
			}
		}
		else
		{
			setPtStZond.AddNewRow(ID_OBJ, ID_KT, ID_UST, GLYB);
		}		
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
	}
}
void ExcelStatZondList::virSaveToDB()
{
	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return;
	}

	int nKTItem = this->m_lab_view->GetKTItem();

	if (nKTItem < 0)
	{
		AfxMessageBox("Не выбрано ни одной KT");
		return;
	}


	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
		if ( !setKT.Open(CRecordset::dynaset) )
			return;

		setKT.SetAbsolutePosition(nKTItem + 1);        
		long ID_KT = setKT.m_ID_KT;

		this->Save(ID_OBJ, ID_KT);
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
	}
}