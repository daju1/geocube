// PaljaListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "PaljaList.h"
#include "EnGeologyView.h"
#include "DlgPalja.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaljaList
//IMPLEMENT_DYNCREATE(CPaljaList, CMyList)


CPaljaList::CPaljaList()
{
}

CPaljaList::~CPaljaList()
{
}


BEGIN_MESSAGE_MAP(CPaljaList, CListCtrl)
	//{{AFX_MSG_MAP(CPaljaList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaljaList message handlers

void CPaljaList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);
		double W = rect.Width() - 10;


		CODBCFieldInfo fi;
		for(int i = 0; i < 6; i++) 
		{
			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.iSubItem = -1;

			switch(i)
			{
			case 0:
				pRecordset->GetODBCFieldInfo(2, fi);
				col.pszText = "Тип";
				col.cx = W / 7;
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(3, fi);
				col.pszText = "Сечение";
				col.cx = W / 7;
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(7, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = W / 7;
				break;
			case 3:
				pRecordset->GetODBCFieldInfo(8, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = W / 7;
				break;
			case 4:
				pRecordset->GetODBCFieldInfo(9, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = W / 7;
				break;
			case 5:
				pRecordset->GetODBCFieldInfo(10, fi);
				col.pszText =  "Ростверк";
				col.cx = W / 7;
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


void CPaljaList::DrawDataRow(CRecordset * pRecordset)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 6; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		switch (iSubItem)
		{
		case 0:
			{
				pRecordset->GetFieldValue(2, var);
				switch(var.m_lVal)
				{
				case 1:
					str = "Круглая";
					break;
				case 2:
					str = "Квадратная";
					break;
				default:
                    str = CMyListCtrl::GetFieldString(var);
					break;
				}
			}
			break;		
		case 1:
			{
				char s1[32], s2[32];
				CDBVariant var1; // must declare this inside the loop
				pRecordset->GetFieldValue(3, var1);
				sprintf(s1, "%f", var1.m_dblVal);
				DeleteEndZeros(s1);

				CDBVariant var2; // must declare this inside the loop
				pRecordset->GetFieldValue(4, var2);
				sprintf(s2, "%f", var2.m_dblVal);
				DeleteEndZeros(s2);

				str.Format("%sx%s", s1,s2);
			}
			break;		
	
		case 2:
			{
				pRecordset->GetFieldValue(7, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
		case 3:
			{
				pRecordset->GetFieldValue(8, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
		case 4:
			{
				pRecordset->GetFieldValue(9, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
		case 5:
			{
				pRecordset->GetFieldValue(10, var);
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


void CPaljaList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	*pResult = 0;
}

void CPaljaList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CDlgPalja dialog(this->m_geo_view, this->m_geo_view->GetLabDoc(), &this->m_geo_view->GetLabDoc()->m_database, false);
	dialog.DoModal();
	
	*pResult = 0;
}
