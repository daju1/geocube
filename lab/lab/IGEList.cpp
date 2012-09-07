// IGEListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "IGEList.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIGEList
//IMPLEMENT_DYNCREATE(CIGEList, CMyList)


CIGEList::CIGEList()
{
}

CIGEList::~CIGEList()
{
}


BEGIN_MESSAGE_MAP(CIGEList, CListCtrl)
	//{{AFX_MSG_MAP(CIGEList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIGEList message handlers

void CIGEList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);
		double W = rect.Width() - 10;


		CODBCFieldInfo fi;
		for(int i = 0; i < 3; i++) 
		{
			LVCOLUMN col;
			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.iSubItem = -1;

			switch(i)
			{
			case 0:
				//pRecordset->GetODBCFieldInfo(1, fi);
				col.pszText = "¹";
				col.cx = 0.15 * W;
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(3, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = 0.2 * W;
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(7, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = 2 * W;
				break;

			}



			this->InsertColumn(i, &col);
		}

		
		//this->ModifyHeaderItems(6);

		this->to_fill_colomns = false;
	}

	int row = 1;

	if (!pRecordset->IsBOF())
	{
		pRecordset->MoveFirst();
		while(!pRecordset->IsEOF()) {
			this->DrawDataRow(pRecordset, row);
			pRecordset->MoveNext(); // to validate record count
			row++;
		}
	}

}


void CIGEList::DrawDataRow(CRecordset * pRecordset, int row)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 3; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		switch (iSubItem)
		{
		case 0:
			{
				//pRecordset->GetFieldValue(1, var);
				str.Format("%d", row);
			}
			break;		
		case 1:
			{
				pRecordset->GetFieldValue(3, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
		case 2:
			{
				pRecordset->GetFieldValue(7, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
	
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


void CIGEList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	*pResult = 0;
}

void CIGEList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
