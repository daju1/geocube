// KTListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "KTListCtrl.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKTList
//IMPLEMENT_DYNCREATE(CKTList, CMyList)
#if 0
void WriteRaporto(LPCTSTR s)
{
//	return;
	FILE *stream;

	if ((stream = fopen("D://C++/Lag/Win32/bin/raporto.log","at")) == NULL)
	//if ((stream = fopen("raporto.log","at")) == NULL)
	{
//		AfxMessageBox("Cannot open file for write.\n");
		return;
	}
	fprintf(stream, s);

	fclose(stream);
}
#endif

CKTList::CKTList()
{
}

CKTList::~CKTList()
{
}


BEGIN_MESSAGE_MAP(CKTList, CListCtrl)
	//{{AFX_MSG_MAP(CKTList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKTList message handlers

void CKTList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 1; i <= 7; i++) 
		{
			pRecordset->GetODBCFieldInfo(i, fi);

			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 6;
			col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
			col.iSubItem = -1;

			this->InsertColumn(i-1, &col);
		}
		
		//this->ModifyHeaderItems(6);

		this->to_fill_colomns = false;
	}


	if (!pRecordset->IsBOF())
	{
		pRecordset->MoveFirst();
		while(!pRecordset->IsEOF()) {
			this->DrawDataRow(pRecordset);
			pRecordset->MoveNext(); // to validate record count
		}
	}

}


CString GetBurType(long val)
{
	CString str;
	switch(val)
	{
	case 0:
		str = "Ударно-канатний";
		break;	
	case 1:
		str = "Шнековий";
		break;	
	case 2:
		str = "Колонковий";
		break;	
	case 3:
		str = "Ручний";
		break;	
	default : // -1
		str = "";//undefined
	}
	return str;

}

CString GetKTType(long val)
{
	CString str = "";
	switch(val)
	{
	case 0:
		str = "Свердловина";
		break;	
	case 1:
		str = "Свердловина розвідувальна";
		break;	
	case 2:
		str = "Свердловина технічна";
		break;	
	case 3:
		str = "Свердловина гідрологічна";
		break;
	case 4:
		str = "Шурф";
		break;
	case 5:
		str = "ТСЗ";
		break;
	case 6:
		str = "Точка випробування грунту";
		break;	
	}
	return str;

}

void CKTList::DrawDataRow(CRecordset * pRecordset)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 7; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem+1, var);

		switch (iSubItem)
		{		
		case 5:
			{
				str = GetKTType(var.m_lVal);
			}
			break;		
		case 6:
			{
				str = GetBurType(var.m_lVal);
			}
			break;
		default:
			str = CMyListCtrl::GetFieldString(var);
		}

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

}


void CKTList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;
#if 1
#if UPDATE_LISTS_ON_CLICK
	if (this->m_geo_view)
		this->m_geo_view->UpdateKTRelatedLists();
#endif
#else
	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		ATable * KTTable = this->m_geo_view->GetDocument()->m_tables[table_key_KT];
		if(KTTable)
		{
			CDBVariant var0;
			CODBCFieldInfo fi0;

			CDBVariant var1;
			CODBCFieldInfo fi1;

			if(KTTable->m_pRecordset)
			{
				KTTable->m_pRecordset->SetAbsolutePosition(r+1);



				KTTable->m_pRecordset->GetFieldValue(short(0), var0);
				KTTable->m_pRecordset->GetODBCFieldInfo(short(0), fi0);


				KTTable->m_pRecordset->GetFieldValue(int(1), var1);
				KTTable->m_pRecordset->GetODBCFieldInfo(int(1), fi1);

				CString where;
				where.Format("%s = %d and %s = %d", 
					fi0.m_strName, var0.m_lVal, 
					fi1.m_strName, var1.m_lVal
					);

				//AfxMessageBox(where);

				CString order_by;
				order_by.Format("ID_PROB");				
				
				long table_key = table_key_ProbGr;				
				m_geo_view->m_SoilsList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				order_by.Format("");	
				table_key = table_key_TSZ;				
				m_geo_view->m_TSZList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				order_by.Format("");	
				table_key = table_key_Palja;				
				m_geo_view->m_PaljaList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				order_by.Format("H1");	
				table_key = table_key_Litho;				
				m_geo_view->m_LithoList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				order_by.Format("");	
				table_key = table_key_Voda;				
				m_geo_view->m_VodaList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
			}
		}
	}	
#endif
	*pResult = 0;
}

void CKTList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
