// ExcelKTEnGeoList.cpp: implementation of the ExcelKTEnGeoList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelKTEnGeoList.h"

#include "SetObject.h"
#include "SetKT.h"
#include "SetIGE.h"
#include "SetLito.h"

#include "labView.h"
#include "../../excel_connect/src/ExcelColChar.h"
#include "EnGeologyView.h"

#include "DlgNRows.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelKTEnGeoList::ExcelKTEnGeoList()
{
	fc = 'L';
	to_rename_kt = false;
}

ExcelKTEnGeoList::~ExcelKTEnGeoList()
{

}
void ExcelKTEnGeoList::InitExt()
{
	ext					= "ktg";
	xl_filter_name		= "Список выработок";
	xl_form				= "KTEnGeoList";
}

void FillLitoHeader(MyExcel & m_excel, int r, char fc)
{
	char S[64];

	sprintf(S, "%c%d:%c%d", fc-2, r, fc-1, r);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("ИГЭ"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);

	sprintf(S, "%c%d:%c%d", fc-2, r+1, fc-1, r+1);
	ExcelRange_SetMerge(m_excel, S);
	ExcelRange_SetValue(m_excel, S, COleVariant("Глубина подошвы"));
	ExcelRange_SetThinContinuousBorders(m_excel, S);
	ExcelRange_CenterVerticalAlignment(m_excel, S);
	ExcelRange_CenterHorizontalAlignment(m_excel, S);
}

CString GetIGE(bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_IGE)
{
	SetIGE setIGE(bUnEdited, database);
	setIGE.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d", ID_OBJ, ID_IGE);
	setIGE.m_strSort.Format("");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return "";

	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		if(!setIGE.IsEOF()) 
		{
			return setIGE.m_IGE;
		}
	}
	return "";
}

long GetID_IGE(bool bUnEdited, CDatabase * database, long ID_OBJ, CString IGE);

void ClearLitho(bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_KT)
{
	SetLito setLito(bUnEdited, database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setLito.m_strSort.Format("");
	if ( !setLito.Open(CRecordset::dynaset) )
		return;	
	if (!setLito.IsBOF()) 
	{
		setLito.MoveFirst( );
		while (!setLito.IsEOF()) 
		{
			setLito.Delete();
			setLito.MoveNext();
		}
	}
}
void SaveLito(bool bUnEdited, CDatabase * database, MyExcel & m_excel, long ID_OBJ, long ID_KT, int r, char fc)
{
	ClearLitho(bUnEdited, database, ID_OBJ, ID_KT);

	SetLito setLito(bUnEdited, database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setLito.m_strSort.Format("");
	if ( !setLito.Open(CRecordset::dynaset) )
		return;	

	char S[64];
	ExcelColChar ecc(fc);
	double h0 = 0.0;
	while (true)
	{
		CString IGE;
		sprintf(S, "%s%d", ecc.Get(), r);
		if (!ExcelRange_GetStringValue(m_excel, S, IGE))
		{
			break;
		}
		long ID_IGE = GetID_IGE(bUnEdited, database, ID_OBJ, IGE);
		double h1;
		sprintf(S, "%s%d", ecc.Get(), r+1);
		if (!ExcelRange_GetValue(m_excel, S, h1))
		{
			break;
		}
		setLito.AddNewRow(ID_OBJ, ID_KT, ID_IGE, h0, h1);
		
		h0 = h1;
		ecc.Increment();
	}
}

void FormatLito(MyExcel & m_excel, int r, char fc)
{
	ExcelColChar ecc(fc);

	char SM1[32], SM2[32];
	sprintf(SM1, "%s%d:%IV%d", ecc.Get(), r, r);
	sprintf(SM2, "%s%d:%IV%d", ecc.Get(), r+1, r+1);

	// цифровой формат для строк с глубиной

	bool msg_if_catch = false;
	CString ds = m_excel.m_app.GetDecimalSeparator();
	if (ds == ",")
	{
		ExcelRange_SetNumberFormat(m_excel, SM2, "0,0", msg_if_catch);
	}
	if (ds == ".")
	{
		ExcelRange_SetNumberFormat(m_excel, SM2, "0.0", msg_if_catch);
	}


	// текстовый формат для строк с ИГЭ	
	ExcelRange_SetNumberFormat(m_excel, SM1, "@", msg_if_catch);
}


void FillLito(bool bUnEdited, CDatabase * database, MyExcel & m_excel, long ID_OBJ, long ID_KT, int r, char fc)
{
	char S[64];

	FillLitoHeader(m_excel, r, fc);

	ExcelColChar ecc(fc);

	SetLito setLito(bUnEdited, database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setLito.m_strSort.Format("");
	if ( !setLito.Open(CRecordset::dynaset) )
		return;	

	if (!setLito.IsBOF()) 
	{
		setLito.MoveFirst( );
		while (!setLito.IsEOF()) 
		{
			sprintf(S, "%s%d", ecc.Get(), r);
			ExcelRange_SetValue(m_excel, S, COleVariant(GetIGE(bUnEdited, database, ID_OBJ,setLito.m_ID_IGE)));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "%s%d", ecc.Get(), r+1);
			ExcelRange_SetValue(m_excel, S, COleVariant(setLito.m_H1));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			ecc.Increment();
			setLito.MoveNext();

		}
	}
}
bool ExcelKTEnGeoList::virFill()
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
	
	int max_rows_user_def = 0;

	CDlgNRows dialog;
	dialog.DoModal();
	if (dialog.ok_pressed)
	{
		max_rows_user_def = fr + 2 * atoi(dialog.m_edit);
	}

	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		bool bUnEdited = false;
		// Заполняем в таблицу нередактируемые ИГЗ, ?????
		// так как они взяты из данных бурения скважин ??????
		bUnEdited = IDNO == MessageBox(NULL, 
			"Какими даными по разбивке скважин заполняем таблицу?\n"
			"Редактируемыми (Да) или исходными - нередактируемыми (Нет)?\n"
			, "ExcelKTEnGeoList::virFill()", MB_YESNO);

		SetIGE setIGE(bUnEdited, this->p_database);
		setIGE.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setIGE.m_strSort.Format("ID_IGE");
		if ( !setIGE.Open(CRecordset::dynaset) )
			return false;

		ExcelColChar ecc(fc);
		CString sc1 = ecc.Get(), sc2 = sc1;
		bool to_fill_table = false;


		if (!setIGE.IsBOF()) 
		{
			setIGE.MoveFirst( );
			while(!setIGE.IsEOF()) 
			{
				to_fill_table = true;




				/*sprintf(S, "%s%d:%s%d", ecc.Get(), r1, ecc.Get(), r2);

				ExcelRange_SetMerge(m_excel, S);
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterVerticalAlignment(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);
				ExcelRange_WrapText(m_excel, S);*/


				sprintf(S, "%s%d", ecc.Get(), r2);
				ExcelRange_SetValue(m_excel, S, COleVariant(setIGE.m_IGE));
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);

				/*sprintf(S, "%s%d", ecc.Get(), r3);
				ExcelRange_SetValue(m_excel, S, COleVariant(setIGE.m_ID_IGE));
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);*/

				sc2 = ecc.Get();
				setIGE.MoveNext();
				ecc.Increment();
			}
		}


		if (to_fill_table)
		{
			sprintf(S, "%c%d:%s%d", fc-1, r0, sc2, r0);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);
			ExcelRange_WrapText(m_excel, S);
			ExcelRange_SetValue(m_excel, S, COleVariant("Справочная таблица ИГЭ"));


			sprintf(S, "%c%d", fc-1, r2);
			ExcelRange_SetValue(m_excel, S, COleVariant("ИГЭ"));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			/*sprintf(S, "%c%d", fc-1, r3);
			ExcelRange_SetValue(m_excel, S, COleVariant("ID_IGE"));
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);	*/		
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

				FormatLito(m_excel, r, fc);
				FillLito(bUnEdited, this->p_database, m_excel, ID_OBJ, setKT.m_ID_KT, r, fc);

				setKT.MoveNext();
				r+=2;
			}
		}


		int max_rows = max(max_rows_user_def, r);



		for( r = fr; r < max_rows; r+=2)
		{
			for (char c = 'B'; c <= 'I'; c++)
			{
				sprintf(S, "%c%d:%c%d", c, r, c, r+1);
				ExcelRange_SetMerge(m_excel, S);
				ExcelRange_SetThinContinuousBorders(m_excel, S);
				ExcelRange_CenterVerticalAlignment(m_excel, S);
				ExcelRange_CenterHorizontalAlignment(m_excel, S);
			}

			/*sprintf(S, "C%d:C%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "B%d:B%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "D%d:D%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "E%d:E%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "F%d:F%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "G%d:G%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "H%d:H%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);

			sprintf(S, "I%d:I%d", r, r+1);
			ExcelRange_SetMerge(m_excel, S);
			ExcelRange_SetThinContinuousBorders(m_excel, S);
			ExcelRange_CenterVerticalAlignment(m_excel, S);
			ExcelRange_CenterHorizontalAlignment(m_excel, S);*/

			FillLitoHeader(m_excel, r, fc);
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

void ExcelKTEnGeoList::virSaveToDB()
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


		for (int r = fr; ;r+=2)
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

			long id_for_new_KT = 0;

			SetKT setKT_2(this->p_database);
			if (to_rename_kt)
				setKT_2.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_kt);
			else
				setKT_2.m_strFilter.Format("ID_OBJ = %d and NAZVA = '%s'", ID_OBJ, nazva);

			if ( !setKT_2.Open(CRecordset::dynaset) )
				return;

			if (!setKT_2.IsBOF()) {
				while(!setKT_2.IsEOF()) {
					setKT_2.MoveNext(); // to validate record count
				}
			}

            bool found = setKT_2.GetRecordCount() > 0;

			if (!found)
			{
				id_for_new_KT = setKT.GetNewKeyID();

				setKT.AddNew();

				setKT.m_ID_OBJ = ID_OBJ;
				setKT.m_ID_KT = id_for_new_KT;
				setKT.m_NAZVA = nazva;
				setKT.m_X = X;
				setKT.m_Y = Y;
				setKT.m_Z = Z;
				setKT.m_ID_TYP = ID_kt_type;
				setKT.m_ID_BUR;
				setKT.m_D_BUR;
				setKT.m_DTBUR;

				setKT.Update();	
			}
			else
			{
				id_for_new_KT = setKT_2.m_ID_KT;


				if (!setKT_2.IsBOF()) 
				{
					setKT_2.MoveFirst( );

					if(!setKT_2.IsEOF()) 
					{
						setKT_2.Edit();

						if (to_rename_kt)
						{
							setKT_2.m_NAZVA = nazva;
							setKT_2.m_ID_TYP = ID_kt_type;
						}

						setKT_2.m_X = X;
						setKT_2.m_Y = Y;
						setKT_2.m_Z = Z;

						setKT_2.Update();	
						//setKT_2.MoveNext(); // to validate record count
					}
				}
			}

			sprintf(S, "E%d", r);
			ExcelRange_SetNumberFormat(m_excel, S, "@", false);
			ExcelRange_SetValue(m_excel, S, COleVariant(nazva));

			sprintf(S, "F%d", r);
			ExcelRange_SetValue(m_excel, S, COleVariant(id_for_new_KT));

			SaveLito(true, this->p_database, m_excel, ID_OBJ, ID_kt, r, fc);
			SaveLito(false, this->p_database, m_excel, ID_OBJ, ID_kt, r, fc);
			//OrderLito(this->p_database, m_excel, ID_OBJ, ID_kt);
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