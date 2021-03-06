// ExcelLabNList.cpp: implementation of the ExcelLabNList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "ExcelLabNList.h"

#include "SetObject.h"
#include "SetKT.h"
#include "SetProbGr.h"

#include "labView.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ExcelLabNList::ExcelLabNList()
{
}

ExcelLabNList::~ExcelLabNList()
{

}
void ExcelLabNList::InitExt()
{
	ext					= "lbn";
	xl_filter_name		= "?????? ???????????? ???????";
	xl_form				= "LabNLabList";
}
bool ExcelLabNList::virFill()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("?? ?????? ??????");
		return false;
	}

	char S[64];
	int fr = 9;	

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;
		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("LAB_N");
		int r = fr;
		if (setProbGr.Open(CRecordset::dynaset))
		{
			if (!setProbGr.IsBOF()) 
			{
				setProbGr.MoveFirst( );
				while(!setProbGr.IsEOF()) 
				{
					sprintf(S, "B%d", r);
					ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_LAB_N));
					sprintf(S, "C%d", r);
					ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_H));
					sprintf(S, "D%d", r);
					ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_ID_KODPROB));
					sprintf(S, "E%d", r);
					ExcelRange_SetValue(m_excel, S, COleVariant(setProbGr.m_ID_KT));
					setProbGr.MoveNext();
					r++;
				}
			}
		}

		SetKT setKT(this->p_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setKT.Open(CRecordset::dynaset) )
			return false;

		r = fr;
		if (!setKT.IsBOF()) 
		{
			setKT.MoveFirst( );
			while(!setKT.IsEOF()) 
			{
				sprintf(S, "G%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_ID_KT));
				sprintf(S, "H%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));
				sprintf(S, "I%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_X));
				sprintf(S, "J%d", r);
				ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_Y));
				sprintf(S, "K%d", r);
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
long g_Get_id_ige(CLabView * lab_view, int nObjectItem, int nSoilsItem, int nCutItem, CDatabase * database)
{
	long id_ige = 0;

	SetObject setObject(database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return id_ige;
	setObject.SetAbsolutePosition(nObjectItem+1);
	long ID_OBJ = setObject.m_ID_OBJ;

	SetProbGr setProbGr(database);
	if(!lab_view->GetSetProbGrFilterStr(ID_OBJ, setProbGr.m_strFilter))
	{
		return id_ige;
	}
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return id_ige;
	setProbGr.SetAbsolutePosition(nSoilsItem+1);

/*	SetZriz setZriz(database);
	setZriz.m_strFilter.Format(
		"ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);
	if ( !setZriz.Open(CRecordset::dynaset) )
		return id_ige;
	setZriz.SetAbsolutePosition(nCutItem+1);
*/
/*	char str[1024];
	sprintf(str, 
		"?? ????????????? ?????? ??????? ????\n"
		"ID_OBJ = %d\n"
		"CONTRACT = %s\n"
		"NAZVA = %s\n"
		"ID_KT = %d\n"
		"ID_PROB = %d\n"
		"ID_VYPROB = %d\n"
		, 
		ID_OBJ, 
		setObject.m_CONTRACT, 
		setObject.m_NAZVA,
		setProbGr.m_ID_KT, 
		setProbGr.m_ID_PROB,
		setZriz.m_ID_VYPROB
		);
	*/
	//if (IDYES != MessageBox(0, str, "g_DeleteCut", MB_YESNO))
	//	return false;


	//SetZriz_tbl setZriz_tbl(database);
	//DeleteCutAndCompressRelatedDataFrom(&setZriz_tbl, ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB, setZriz.m_ID_VYPROB);
	//setZriz.Delete();

	CString where;
	where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", 
		ID_OBJ, setProbGr.m_ID_KT, setProbGr.m_ID_PROB);

	lab_view->UpdateCutListCtrl(where, "ID_VYPROB");
	return id_ige;
}



void ExcelLabNList::virSaveToDB()
{

	int nObItem = this->m_lab_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("?? ?????? ??????");
		return;
	}

//	LPDISPATCH pRange; 
//	Range10    m_range;

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

		SetProbGr setProbGr(this->p_database);
		setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setProbGr.m_strSort.Format("ID_KT, ID_PROB");
		if ( !setProbGr.Open(CRecordset::dynaset) )
			return;

		int perezapisano = 0;

		for (int r = fr; ;r++)
		{
			double val;
			long LAB_N;
			sprintf(S, "B%d", r);				
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				LAB_N = long(val);
			}
			else
			{
				char str[1028];
				sprintf(str, 
					"?????????? %d ????? ? ????????????? ????????\n"
					"????????? %d ???????????? ???????\n"
					"?? ?? ???????????? %d ???????????? ???????"
					, r-fr
					, r-fr-perezapisano
					, perezapisano);
				AfxMessageBox(str);
				break;
			}

			double H = 0.0;
			sprintf(S, "C%d", r);				
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				H = val;
			}
			else
			{
				char str[1028];
				sprintf(str, 
					"??????????? ??????? ? ?????? %d ??? ????????????? ?????? %d"
					, r, LAB_N);
				AfxMessageBox(str);
			}

			long ID_KODPROB = 0;
			sprintf(S, "D%d", r);				
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				ID_KODPROB = long(val);
			}

			long ID_KT = -1;
			sprintf(S, "E%d", r);				
			if (ExcelRange_GetValue(m_excel, S, val))
			{
				ID_KT = long(val);
			}
			else
			{
				char str[1028];
				sprintf(str, 
					"??????????? ID_KT ? ?????? %d ??? ????????????? ?????? %d"
					, r, LAB_N);
				AfxMessageBox(str);
			}

			bool found_id_kt = setKT.Have_ID_KT(ID_KT);
			if (!found_id_kt)
			{
				CString s;
				s.Format("ID ????????? %d ? ???? ??????"
					"???????????? ????? %d ?? ????? ??????", ID_KT, LAB_N);
				AfxMessageBox(s);

				continue;
			}


			long ID_GR = 0;
			CString GRUNT_NAME = "";

		
			long ID_PROB;
			bool found_lab_n = setProbGr.Have_LAB_N(LAB_N, ID_PROB);
			if (found_lab_n)
			{
				char str[1028];
				sprintf(str, "???????????? ????? (??????=%d) LAB_N=%d ID_PROB=%d \n??? ??????? ? ???? \n?? ????? ??????????????"
					,r , LAB_N, ID_PROB);
				AfxMessageBox(str);

				if (setProbGr.Having_LAB_N_Edit(LAB_N, ID_OBJ, ID_KT, ID_PROB,
					H, LAB_N, ID_KODPROB, ID_GR, GRUNT_NAME))
				{
					perezapisano++;
				}
			}
			else
			{
				ID_PROB = setProbGr.GetNewKeyID();
				setProbGr.AddNewRow(ID_OBJ, ID_KT, ID_PROB,
							H, LAB_N, ID_KODPROB, ID_GR, GRUNT_NAME);
			}
		}

		CString where;
		//if (this->is_geo)
		//	where.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, id_kt);
			
		//if (this->is_lab)
			where.Format("ID_OBJ = %d", ID_OBJ);
		this->m_lab_view->UpdateProbGruntListCtrl(where, "ID_KT, ID_PROB");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}