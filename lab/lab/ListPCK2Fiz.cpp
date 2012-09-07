// RaschetSvaiList.cpp: implementation of the RaschetSvaiList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "EnGeologyView.h"
#include "ListPCK2Fiz.h"
#include "SetPCK2Fiz_CalcParams.h"
#include "SetPCK2FizResults.h"
#include "SetKT.h"
#include "SetPtStZond.h"
#include "SetStZond.h"

#include "../../surfdoc/src/well_3d.h"


void DeleteEndZeros(char * str);
void DeleteEndZeros(CString & str);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListPCK2Fiz::CListPCK2Fiz(CDatabase * database)
{
	this->p_database = database;
	this->m_ID_OBJ = -1;
}
	


CListPCK2Fiz::~CListPCK2Fiz()
{

}

BEGIN_MESSAGE_MAP(CListPCK2Fiz, CListCtrl)
	//{{AFX_MSG_MAP(CListPCK2Fiz)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//кандидат на переход в базовый класс
void CListPCK2Fiz::InsertingColumn(int & icol, CString str, int width)
{
	LVCOLUMN col;
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = width;//rect.Width() / 6;
	col.pszText = str.GetBuffer(str.GetLength());
	col.iSubItem = -1;

	this->InsertColumn(icol++, &col);
}
void CListPCK2Fiz::InitHeaders()
{
	CString str = "";
	CRect           rect;
	this->GetWindowRect(&rect);			
	this->DeleteAllItemsAndColomns();

	int icol = 0;

	int d = 9;

	InsertingColumn(icol, "KT", rect.Width() / d);
	InsertingColumn(icol, "H", rect.Width() / d);
	InsertingColumn(icol, "»√Ё", rect.Width() / d);
	InsertingColumn(icol, "PCK", rect.Width() / d);


	SetPCK2Fiz_CalcParams setPCK2Fiz_CalcParams(this->p_database);
	setPCK2Fiz_CalcParams.m_strSort.Format("ID_CALC_PARAM");
	if ( !setPCK2Fiz_CalcParams.Open(CRecordset::dynaset) )
		return;

	if (!setPCK2Fiz_CalcParams.IsBOF()) 
	{
		setPCK2Fiz_CalcParams.MoveFirst( );
		while(!setPCK2Fiz_CalcParams.IsEOF()) 
		{
			str = setPCK2Fiz_CalcParams.m_CALC_PARAM;
			InsertingColumn(icol, str, rect.Width() / d);
			setPCK2Fiz_CalcParams.MoveNext();
		}
	}

}
void CListPCK2Fiz::AddString(int & iActualItem, int iSubItem, CString & str)
{
	InSertTheItem(str, iActualItem, iSubItem);
}
CString GetIGE(bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_IGE);

bool GetPCK2FizResult(CDatabase * database, long ID_OBJ, long ID_KT, long NPP, long ID_CALC_PARAM, double & param)
{
	SetPCK2FizResults setPCK2FizResults(database);
	setPCK2FizResults.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d and NPP = %d and ID_CALC_PARAM = %d", 
		ID_OBJ, ID_KT, NPP, ID_CALC_PARAM);
	setPCK2FizResults.m_strSort.Format("");
	if ( !setPCK2FizResults.Open(CRecordset::dynaset) )
		return false;

	if (!setPCK2FizResults.IsBOF()) 
	{
		setPCK2FizResults.MoveFirst( );
		if(!setPCK2FizResults.IsEOF()) 
		{
			param = setPCK2FizResults.m_param;
			return true;
		}
	}	
	return false;
}
bool CListPCK2Fiz::FillKT(int & iActualItem, long ID_KT, CString KT_NAME)
{
	CString str;
	long rec = 0;
	
	SetPtStZond setPtStZond(p_database);
	setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", m_ID_OBJ, ID_KT);
	setPtStZond.m_strSort.Format("");
	if ( setPtStZond.Open(CRecordset::dynaset) )
	{
		if (!setPtStZond.IsBOF()) 
		{
			setPtStZond.MoveFirst( );
			while(!setPtStZond.IsEOF()) 
			{
				setPtStZond.MoveNext();
			}
		}
	}
	rec = setPtStZond.GetRecordCount();

	if (rec)
	{

		SetStZond setStZond(p_database);
		setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", m_ID_OBJ, ID_KT);
		setStZond.m_strSort.Format("NPP");
		if ( setStZond.Open(CRecordset::dynaset) )
		{
			if (!setStZond.IsBOF()) 
			{
				setStZond.MoveFirst( );
				while(!setStZond.IsEOF()) 
				{
					int iSubItem = 0;

					str = KT_NAME;
					InSertTheItem(str, iActualItem, iSubItem++);

					str.Format("%f", setStZond.m_H);
					DeleteEndZeros(str);
					InSertTheItem(str, iActualItem, iSubItem++);

					bool bUnEdited = false;
					 
					str = GetIGE(bUnEdited, p_database, m_ID_OBJ, setStZond.m_ID_IGE);
					InSertTheItem(str, iActualItem, iSubItem++);

					str.Format("%f", setStZond.m_pck);
					DeleteEndZeros(str);
					InSertTheItem(str, iActualItem, iSubItem++);


					long NPP = setStZond.m_NPP;

					SetPCK2Fiz_CalcParams setPCK2Fiz_CalcParams(this->p_database);
					setPCK2Fiz_CalcParams.m_strSort.Format("ID_CALC_PARAM");
					if (setPCK2Fiz_CalcParams.Open(CRecordset::dynaset) )
					{
						if (!setPCK2Fiz_CalcParams.IsBOF()) 
						{
							setPCK2Fiz_CalcParams.MoveFirst( );
							while(!setPCK2Fiz_CalcParams.IsEOF()) 
							{
								double param;

								str = "";

								if (GetPCK2FizResult(p_database, 
									m_ID_OBJ, ID_KT, NPP, setPCK2Fiz_CalcParams.m_ID_CALC_PARAM, param))
								{
									str.Format("%f", param);
									DeleteEndZeros(str);
								}
								InSertTheItem(str, iActualItem, iSubItem++);
								setPCK2Fiz_CalcParams.MoveNext();
							}
						}
					}
					setStZond.MoveNext();
				}
			}
		}
	}
	else
	{
		// в этой KT нет статзондировани€
	}
	return true;

}


void CListPCK2Fiz::FillCtrlList()
{
	DeleteAllItems();

	CString str = "";
	int npp = 1, iSubItem;
	int iActualItem = 0;

	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
	if ( !setKT.Open(CRecordset::dynaset) )
		return;

	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		while(!setKT.IsEOF()) 
		{

			long ID_KT = setKT.m_ID_KT;
		
			iSubItem = 0;
			
			if(FillKT(iActualItem, ID_KT, setKT.m_NAZVA))
			{
			}

			setKT.MoveNext();
		}
	}
}

//кандидат на переход в базовый класс
void CListPCK2Fiz::InSertTheItem(CString & str, int & iActualItem, int iSubItem)
{
	LV_ITEM         lvitem;
	lvitem.mask = LVIF_TEXT;// | (iSubItem == 0 ? LVIF_IMAGE : 0);
	lvitem.iItem = (iSubItem == 0) ? this->GetItemCount( ) : iActualItem;
	lvitem.iSubItem = iSubItem;

	// calculate the main and sub-item strings for the current item
	lvitem.pszText = str.GetBuffer(str.GetLength());

	//lvitem.iImage = iIcon;
	lvitem.iImage = 0;
	if (iSubItem == 0)
		iActualItem = this->InsertItem(&lvitem); // insert new item
	else
		this->SetItem(&lvitem); // modify existing item (the sub-item text)
}


void CListPCK2Fiz::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;	
}

