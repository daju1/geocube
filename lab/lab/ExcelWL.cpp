// ExcelWL.cpp: implementation of the ExcelWL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelWL.h"
#include "labView.h"
#include "SetObject.h"
#include "SetProbGr.h"
#include "SetfizMeh.h"
#include "SetKT.h"

#include "DlgRepeatings.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelWL::ExcelWL()
{
}

ExcelWL::~ExcelWL()
{

}
void ExcelWL::InitExt()
{
	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			ext					= "wl";
			xl_filter_name		= "W текучести";
			xl_form				= "WL";
		}
		break;
	case 3:
		{
			ext					= "wl3";
			xl_filter_name		= "W текучести";
			xl_form				= "WL3";
		}
		break;
	}
}
bool ExcelWL::virCompute(bool)
{
	LPDISPATCH pRange; 
	Range10    m_range;

	char S[64];
	char F[1024];

	switch (CDlgRepeatings::s_repeatings)
	{
	case 2:
		{
			int fr = 13;

			for (int r = 0; r <= 21; r++)
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

				sprintf(S, "H%d", row1);
				sprintf(F, "=(E%d-F%d)/(F%d-G%d)", row1, row1, row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.SetNumberFormat(COleVariant("0.000"));
				m_range.ReleaseDispatch();	

				// определяем занесена ли в таблицу вторая повторность
				bool use_row_2 = false;
				double v;
				sprintf(S, "E%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "F%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "G%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);

				if (use_row_2)
				{
					sprintf(S, "H%d", row2);
					sprintf(F, "=(E%d-F%d)/(F%d-G%d)", row2, row2, row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

				if (use_row_2)
				{		
					sprintf(S, "I%d", row1);
					sprintf(F, "=0.5*(H%d+H%d)", row1, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
				else
				{
					sprintf(S, "I%d", row1);
					sprintf(F, "=H%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

				sprintf(S, "K%d", row1);
				sprintf(F, "=I%d-J%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.SetNumberFormat(COleVariant("0.000"));
				m_range.ReleaseDispatch();

			}
		}
		break;
	case 3:
		{
			int fr = 13;

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

				sprintf(S, "H%d", row1);
				sprintf(F, "=(E%d-F%d)/(F%d-G%d)", row1, row1, row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.SetNumberFormat(COleVariant("0.000"));
				m_range.ReleaseDispatch();	

				double v;
				// определяем занесена ли в таблицу вторая повторность
				bool use_row_2 = false;
				sprintf(S, "E%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "F%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "G%d", row2);
				use_row_2 |= ExcelRange_GetValue(m_excel, S, v);

				// определяем занесена ли в таблицу 3-ая повторность
				bool use_row_3 = false;
				sprintf(S, "E%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "F%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);
				sprintf(S, "G%d", row3);
				use_row_3 |= ExcelRange_GetValue(m_excel, S, v);

				if (use_row_2)
				{
					sprintf(S, "H%d", row2);
					sprintf(F, "=(E%d-F%d)/(F%d-G%d)", row2, row2, row2, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

				if (use_row_3)
				{
					sprintf(S, "H%d", row3);
					sprintf(F, "=(E%d-F%d)/(F%d-G%d)", row3, row3, row3, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

				if (use_row_2 && use_row_3)
				{
					sprintf(S, "I%d", row1);
					sprintf(F, "=(H%d+H%d+H%d)/3.0", row1, row2, row3);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
				else if (use_row_2 && ! use_row_3)
				{		
					sprintf(S, "I%d", row1);
					sprintf(F, "=0.5*(H%d+H%d)", row1, row2);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}
				else
				{
					sprintf(S, "I%d", row1);
					sprintf(F, "=H%d", row1);
					VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
					m_range.AttachDispatch(pRange);		
					m_range.SetValue(COleVariant(F));
					m_range.SetNumberFormat(COleVariant("0.000"));
					m_range.ReleaseDispatch();	
				}

				sprintf(S, "K%d", row1);
				sprintf(F, "=I%d-J%d", row1, row1);
				VERIFY(pRange = m_excel.m_worksheet.GetRange(COleVariant(S)));
				m_range.AttachDispatch(pRange);		
				m_range.SetValue(COleVariant(F));
				m_range.SetNumberFormat(COleVariant("0.000"));
				m_range.ReleaseDispatch();

			}
		}
		break;
	}
	return true;
}


void ExcelWL::virSaveToDB()
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
				fr = 13;
				nr = 21;
				m = 2;
			}
			break;
		case 3:
			{
				fr = 13;
				nr = 14;
				m = 3;
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

			long ID_VYPROB = MEAN_PHYS_VYPROB;
			long ID_PARAM_WL = 2;
			long ID_PARAM_WP = 3;
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

			if (true)
			{
				SetFizMeh setFizMeh_2(this->p_database);
				setFizMeh_2.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
					ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM_WL);
				if ( !setFizMeh_2.Open(CRecordset::dynaset) )
					return;

				double val;						
				sprintf(S, "I%d", row1);
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, lab_n, 
						ID_PARAM_WL, ID_VYPROB, val);
				}			
			}
			if (true)
			{
				SetFizMeh setFizMeh_2(this->p_database);
				setFizMeh_2.m_strFilter.Format(
					"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d and ID_VYPROB = %d and ID_PARAM = %d", 
					ID_OBJ, ID_KT, ID_PROB, ID_VYPROB, ID_PARAM_WP);
				if ( !setFizMeh_2.Open(CRecordset::dynaset) )
					return;

				double val;						
				sprintf(S, "J%d", row1);
				if(ExcelRange_GetValue(m_excel, S, val))
				{
					int res = setFizMeh_2.ReplaceParam(ID_OBJ, ID_KT, ID_PROB, lab_n, 
						ID_PARAM_WP, ID_VYPROB, val);
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