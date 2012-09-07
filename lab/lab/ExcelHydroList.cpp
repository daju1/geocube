// ExcelHydroList.cpp: implementation of the ExcelHydroList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelHydroList.h"

#include "SetObject.h"
#include "SetKT.h"
#include "SetIGE.h"
#include "SetVoda.h"

#include "labView.h"
#include "../../excel_connect/src/ExcelColChar.h"

#include "DlgNRows.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelHydroList::ExcelHydroList()
{
	fc = 'L';
}

ExcelHydroList::~ExcelHydroList()
{

}
void ExcelHydroList::InitExt()
{
	ext					= "kth";
	xl_filter_name		= "Список водопроявлений";
	xl_form				= "KTEnGeoList";
}

void FillVodaHeader(MyExcel & m_excel, int r, char fc)
{
	char S[64];

	sprintf(S, "%c%d:%c%d", fc-2, r, fc-1, r);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("Появился"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);

	sprintf(S, "%c%d:%c%d", fc-2, r+1, fc-1, r+1);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("Установился"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);

	sprintf(S, "%c%d:%c%d", fc-2, r+2, fc-1, r+2);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("Дата замера"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);


	ExcelColChar ecc(fc);
	for (int ic = 0; ic < 10; ic++) 
	{
		sprintf(S, "%s%d", ecc.Get(), r+2);
		//ExcelRange_SetNumberFormat(m_excel, S, "dd/mm/yyyy", false);
		ExcelRange_SetNumberFormat(m_excel, S, "dd.mm.yyyy", false);
		ExcelRange_SetNumberFormat(m_excel, S, "ДД.ММ.ГГГГ", false);
		
		ecc.Increment();
	}
}




void ClearVoda(CDatabase * database, long ID_OBJ, long ID_KT)
{
	SetVoda setVoda(database);
	setVoda.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setVoda.m_strSort.Format("");
	if ( !setVoda.Open(CRecordset::dynaset) )
		return;	
	if (!setVoda.IsBOF()) 
	{
		setVoda.MoveFirst( );
		while (!setVoda.IsEOF()) 
		{
			setVoda.Delete();
			setVoda.MoveNext();
		}
	}
}
void SaveVoda(CDatabase * database, MyExcel & m_excel, long ID_OBJ, long ID_KT, int r, char fc)
{
	ClearVoda(database, ID_OBJ, ID_KT);

	SetVoda setVoda(database);
	setVoda.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setVoda.m_strSort.Format("");
	if ( !setVoda.Open(CRecordset::dynaset) )
		return;	

	char S[64];
	ExcelColChar ecc(fc);
	double h0 = 0.0;
	for (long horizont = 1; horizont < 5; horizont++)
	{
		double hv_z;
		double hv_v;

		SetVoda setVoda_horizont(database);
		setVoda_horizont.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and HORIZONT = %d", ID_OBJ, ID_KT, horizont);
		setVoda_horizont.m_strSort.Format("");
		if ( !setVoda_horizont.Open(CRecordset::dynaset) )
			return;	

		int rows = 0;
		if (!setVoda_horizont.IsBOF()) 
		{
			setVoda_horizont.MoveFirst( );
			while (!setVoda_horizont.IsEOF()) 
			{
				setVoda_horizont.Edit();

				sprintf(S, "%s%d", ecc.Get(), r);
				if (ExcelRange_GetValue(m_excel, S, hv_z))
				{
					setVoda_horizont.m_HV_Z = hv_z;
				}

				sprintf(S, "%s%d", ecc.Get(), r+1);
				if (ExcelRange_GetValue(m_excel, S, hv_v))
				{
					setVoda_horizont.m_HV_V = hv_v;
				}

				CTime data;
				sprintf(S, "%s%d", ecc.Get(), r+2);
				if (ExcelRange_GetDateValue(m_excel, S, data))
				{
					setVoda_horizont.m_DV = data;
				}	

				setVoda_horizont.Update();



				rows++;
				setVoda_horizont.MoveNext();
			}
		}

		if (rows > 0)
		{					
		}
		else
		{
			bool hv_z_got = false;
			bool hv_v_got = false;

			sprintf(S, "%s%d", ecc.Get(), r);
			if (ExcelRange_GetValue(m_excel, S, hv_z))
			{
				hv_z_got =  true;
			}
			sprintf(S, "%s%d", ecc.Get(), r+1);
			if (ExcelRange_GetValue(m_excel, S, hv_v))
			{
				hv_v_got = true;
			}

			if (hv_z_got && hv_v_got)
			{
				CTime data;
				sprintf(S, "%s%d", ecc.Get(), r+2);
				if (ExcelRange_GetDateValue(m_excel, S, data))
				{
					setVoda.AddNewRow(ID_OBJ, ID_KT, horizont, hv_z, hv_v, data);
				}
				else
				{
					setVoda.AddNewRow(ID_OBJ, ID_KT, horizont, hv_z, hv_v);
				}
			}
		}
		ecc.Increment();
		
	}
}

void FillVoda(CDatabase * database, MyExcel & m_excel, long ID_OBJ, long ID_KT, int r, char fc)
{
	char S[64];

	FillVodaHeader(m_excel, r, fc);

	ExcelColChar ecc(fc);

	SetVoda setVoda(database);
	setVoda.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setVoda.m_strSort.Format("");
	if ( !setVoda.Open(CRecordset::dynaset) )
		return;	

	if (!setVoda.IsBOF()) 
	{
		setVoda.MoveFirst( );
		while (!setVoda.IsEOF()) 
		{
			sprintf(S, "%s%d", ecc.Get(), r);
			ExcelRange_SetValue(m_excel, S, COleVariant(setVoda.m_HV_Z));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "%s%d", ecc.Get(), r+1);
			ExcelRange_SetValue(m_excel, S, COleVariant(setVoda.m_HV_V));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			 

			sprintf(S, "%s%d", ecc.Get(), r+2);
			__time64_t m_time = setVoda.m_DV.GetTime();
			if (m_time)
			{
				ExcelRange_SetValue(m_excel, S, COleVariant(COleDateTime(m_time)));
				//ExcelRange_SetNumberFormat(m_excel, S, "m/d/yyyy");
				//ExcelRange_SetNumberFormat(m_excel, S, "d/m/yyyy;@", false);
				//ExcelRange_SetNumberFormat(m_excel, S, "dd/mm/yyyy", false);
				ExcelRange_SetNumberFormat(m_excel, S, "dd.mm.yyyy", false);
				ExcelRange_SetNumberFormat(m_excel, S, "ДД.ММ.ГГГГ", false);
			}
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);


			ecc.Increment();
			setVoda.MoveNext();

		}
	}
}
bool ExcelHydroList::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return false;
	}



	char S[64];
	int fr = 9;	
	int r0 = 4, r2 = 5, r3 = 6;		
	
	/*int max_rows_user_def = 0;

	CDlgNRows dialog;
	dialog.DoModal();
	if (dialog.ok_pressed)
	{
		max_rows_user_def = fr + 2 * atoi(dialog.m_edit);
	}*/

	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			

		{
			sprintf(S, "J4:K8");
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);
			ExcelRange_WrapText(m_excel, S);
			ExcelRange_SetValue(m_excel, S, COleVariant("Водопроявления"));

			sprintf(S, "L4:L8");
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);
			ExcelRange_WrapText(m_excel, S);
			ExcelRange_SetValue(m_excel, S, COleVariant("Горизонт 1, глубина, м"));

			sprintf(S, "M4:M8");
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);
			ExcelRange_WrapText(m_excel, S);
			ExcelRange_SetValue(m_excel, S, COleVariant("Горизонт 2 и т.д."));
		}

		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format("ID_KT");
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		int r = fr;
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			while(!setKT.IsEOF()) 
			{
				sprintf(S, "C%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_ID_TYP));

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
				else if (foof > -1)
				{
					kt_type = setKT.m_NAZVA.Left(foof);
				}

				sprintf(S, "B%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(kt_type));

				sprintf(S, "D%d", r);
				ExcelRange_SetNumberFormat(m_excel, S, "@", false);
				ExcelRange_SetValue(m_excel, S, COleVariant(nazva));

				sprintf(S, "E%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));

				sprintf(S, "F%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_ID_KT));

				sprintf(S, "G%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_X));

				sprintf(S, "H%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_Y));

				sprintf(S, "I%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_Z));

				FillVoda(this->p_database, m_excel, ID_OBJ, setKT.m_ID_KT, r, fc);

				setKT.MoveNext();
				r+=3;
			}
		}


		int max_rows = r;//max(max_rows_user_def, r);



		for( r = fr; r < max_rows; r+=3)
		{
			for (char c = 'B'; c <= 'I'; c++)
			{
				sprintf(S, "%c%d:%c%d", c, r, c, r+2);
				ExcelRange_SetMerge(m_excel, S);
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterVerticalAlignment(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);
			}

			FillVodaHeader(m_excel, r, fc);
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

void ExcelHydroList::virSaveToDB()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return;
	}

	LPDISPATCH pRange; 
	Range10    m_range;

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setKT.Open(CRecordset::dynaset) )
			return;


		for (int r = fr; ;r+=3)
		{
			sprintf(S, "C%d", r);

			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			VARIANT idkttype = m_range.GetValue();
			m_range.ReleaseDispatch();


			bool ID_kt_type_got = false;
			long ID_kt_type = 0;
			if (idkttype.vt == VT_R8)
			{
				ID_kt_type = long(idkttype.dblVal);
				ID_kt_type_got = true;
			}


			sprintf(S, "B%d", r);

			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			VARIANT kttype = m_range.GetValue();
			CString kt_type;
			bool kt_type_got = false;
			if (kttype.vt == VT_BSTR)
			{
				kt_type = kttype.bstrVal;
				kt_type_got = true;

				CString end_kt_type = kt_type.Right(1);
				if (end_kt_type != ' ' || end_kt_type != '.')
					kt_type += ' ';

			}

			if (!ID_kt_type_got && !kt_type_got)
				break;


			if (!kt_type_got)
			{
				//ID типа выработки (1-разв.скв., 2-техн.скв., 3-гидр.скв., 4-шурф, 5-ТСЗ, 6-тч.опр.гр.)
				switch(ID_kt_type)
				{
				case 0:
					{
						kt_type = "скв.";
					}
					break;
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
						kt_type = "шурф ";
					}
					break;
				case 5:
					{
						kt_type = "ТСЗ ";
					}
					break;
				case 6:
					{
						kt_type = "тч.опр.гр.";
					}
					break;
				}
				m_range.SetValue(COleVariant(kt_type));
			}
			m_range.ReleaseDispatch();


			CString nazva;
			sprintf(S, "E%d", r);
			if (!ExcelRange_GetStringValue(m_excel, S, nazva))
			{
				sprintf(S, "D%d", r);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);			   
				VARIANT kt = m_range.GetValue();
				m_range.ReleaseDispatch();

				if (kt.vt == VT_R8)
				{
					double Kt = kt.dblVal;
					nazva.Format("%s%d", kt_type, int(Kt));
				}			
				else if (kt.vt == VT_BSTR)
				{
					CString s = kt.bstrVal;
					nazva.Format("%s%s", kt_type, s);
				}
				else
				{
					break;
				}
			}

			double X = 0, Y = 0, Z = 0;
							
			sprintf(S, "G%d", r);
			if(ExcelRange_GetValue(m_excel, S, X))
			{
			}
			sprintf(S, "H%d", r);
			if(ExcelRange_GetValue(m_excel, S, Y))
			{
			}
			sprintf(S, "I%d", r);
			if(ExcelRange_GetValue(m_excel, S, Z))
			{
			}


			sprintf(S, "F%d", r);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			VARIANT idkt = m_range.GetValue();
			m_range.ReleaseDispatch();

			bool ID_kt_got = false;
			long ID_kt = -1;
			if (idkt.vt == VT_R8)
			{
				ID_kt = long(idkt.dblVal);
				ID_kt_got = true;
			}

			if (ID_kt_got)
				SaveVoda(this->p_database, m_excel, ID_OBJ, ID_kt, r, fc);
		}
		CString where; where.Format("ID_OBJ = %d", ID_OBJ);
		this->m_lab_view->UpdateKTListCtrl(where, CEnGeologyView::str_kt_list_order_by);
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}