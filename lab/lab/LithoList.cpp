// LithoListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "LithoList.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLithoList
//IMPLEMENT_DYNCREATE(CLithoList, CMyList)


CLithoList::CLithoList()
{
}

CLithoList::~CLithoList()
{
}


BEGIN_MESSAGE_MAP(CLithoList, CListCtrl)
	//{{AFX_MSG_MAP(CLithoList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLithoList message handlers
CString GetIGEName(CDatabase * database, long id_obj, long id_ige);
void CLithoList::FillCtrlList(CRecordset * pRecordset)
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
				col.pszText = "¹";
				col.cx = 0.1*W;
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(2, fi);//ID_IGE
				col.pszText = "IGE";
				col.cx = 0.2*W;
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(3, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = 0.3*W;
				break;
			case 3:
				pRecordset->GetODBCFieldInfo(4, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = 0.3*W;
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


void CLithoList::DrawDataRow(CRecordset * pRecordset, int row)
{
	long id_obj;
	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		int iActualItem = 0;
		{
			CDBVariant var; // must declare this inside the loop
			pRecordset->GetFieldValue(short(0), var);
			//ID_OBJ
			id_obj = var.m_lVal;
		}
		for (int iSubItem = 0; iSubItem < 4; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop
			switch (iSubItem)
			{
			case 0:
				{
					//pRecordset->GetFieldValue(2, var);
					str.Format("%d", row);
				}
				break;		
			case 1:
				{
					pRecordset->GetFieldValue(2, var);
					str = GetIGEName(&this->m_geo_view->GetDocument()->m_database, id_obj, var.m_lVal);
				}
				break;		
			case 2:
				{
					pRecordset->GetFieldValue(3, var);
					str = CMyListCtrl::GetFieldString(var);
				}
				break;		
			case 3:
				{
					pRecordset->GetFieldValue(4, var);
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
}


void CLithoList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	*pResult = 0;
}

void CLithoList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
