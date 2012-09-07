// VodaListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "VodaList.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVodaList
//IMPLEMENT_DYNCREATE(CVodaList, CMyList)


CVodaList::CVodaList()
{
}

CVodaList::~CVodaList()
{
}


BEGIN_MESSAGE_MAP(CVodaList, CListCtrl)
	//{{AFX_MSG_MAP(CVodaList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVodaList message handlers

void CVodaList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);
		double W = rect.Width() - 10;


		CODBCFieldInfo fi;
		for(int i = 0; i < 4; i++) 
		{
			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.iSubItem = -1;
			switch(i)
			{
			case 0:
				pRecordset->GetODBCFieldInfo(2, fi);
				col.cx = 0.25 * W;
				col.pszText = "Горизонт";
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(3, fi);
				col.cx = 0.25 * W;
				col.pszText = "Появился";
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(4, fi);
				col.cx = 0.25 * W;
				col.pszText = "Установился";
				break;
			case 3:
				pRecordset->GetODBCFieldInfo(5, fi);
				col.cx = 0.2 * W;
				col.pszText = "Дата";
				break;
			}
			


			this->InsertColumn(i, &col);
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


void CVodaList::DrawDataRow(CRecordset * pRecordset)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 4; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		switch (iSubItem)
		{
		case 0:
			{
				pRecordset->GetFieldValue(2, var);
			}
			break;		
		case 1:
			{
				pRecordset->GetFieldValue(3, var);
			}
			break;		
		case 2:
			{
				pRecordset->GetFieldValue(4, var);
			}
			break;		
		case 3:
			{
				pRecordset->GetFieldValue(5, var);
			}
			break;		
		}


		str = CMyListCtrl::GetFieldString(var);
	

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


void CVodaList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	*pResult = 0;
}

void CVodaList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
