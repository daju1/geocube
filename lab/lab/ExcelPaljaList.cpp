// ExcelPaljaList.cpp: implementation of the ExcelPaljaList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelPaljaList.h"

#include "SetObject.h"
#include "SetKT.h"

#include "labView.h"

#include "EnGeologyView.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelPaljaList::ExcelPaljaList()
{
}

ExcelPaljaList::~ExcelPaljaList()
{

}
void ExcelPaljaList::InitExt()
{
	ext					= "ktg";
	xl_filter_name		= "Список выработок";
	xl_form				= "PaljaList";
}
bool ExcelPaljaList::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return false;
	}

//	LPDISPATCH pRange; 
//	Range10    m_range;

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
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

				setKT.MoveNext();
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

void ExcelPaljaList::virSaveToDB()
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


		for (int r = fr; ;r++)
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
			}

			if (!ID_kt_type_got && !kt_type_got)
				break;


			if (!kt_type_got)
			{
				//ID типа выработки (1-разв.скв., 2-техн.скв., 3-гидр.скв., 4-шурф, 5-ТСЗ, 6-тч.опр.гр.)
				switch(ID_kt_type)
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


			sprintf(S, "D%d", r);

			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			VARIANT kt = m_range.GetValue();
			m_range.ReleaseDispatch();


			CString nazva;
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

			double X,Y,Z;
							
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
				id_for_new_KT = ID_kt_got ? ID_kt : setKT.GetNewKeyID();

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

						setKT_2.m_X = X;
						setKT_2.m_Y = Y;
						setKT_2.m_Z = Z;

						setKT_2.Update();	
						//setKT_2.MoveNext(); // to validate record count
					}
				}
			}

			sprintf(S, "E%d", r);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			m_range.SetValue(COleVariant(nazva));
			m_range.ReleaseDispatch();

			sprintf(S, "F%d", r);
			VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
			m_range.AttachDispatch(pRange);			   
			m_range.SetValue(COleVariant(id_for_new_KT));
			m_range.ReleaseDispatch();
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