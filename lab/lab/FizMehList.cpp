// GranularList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "FizMehList.h"
#include "SetFizMeh.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FizMehList

FizMehList::FizMehList()
{
}

FizMehList::~FizMehList()
{
}


BEGIN_MESSAGE_MAP(FizMehList, CListCtrl)
	//{{AFX_MSG_MAP(FizMehList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FizMehList message handlers

#if 1
void FizMehList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 3; i <= 5; i++) 
		{
			pRecordset->GetODBCFieldInfo(i, fi);

			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 3;
			col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
			col.iSubItem = -1;

			this->InsertColumn(i-2, &col);
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

#else
void FizMehList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 4; i <= 5; i++) 
		{
			pRecordset->GetODBCFieldInfo(i, fi);

			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 2;
			col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
			col.iSubItem = -1;

			this->InsertColumn(i-3, &col);
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

#endif
CString GetFizMehParam(CDatabase * database, long id_param);
#if 1
void FizMehList::DrawDataRow(CRecordset * pRecordset)
{
	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		long ID_OBJ = 0, ID_KT = 0, ID_PROB = 0;
		int iActualItem = 0;
		for (int iSubItem = 0; iSubItem < 6; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop
			pRecordset->GetFieldValue(iSubItem, var);

			switch (iSubItem)
			{
			case 0:
				{
					ID_OBJ = var.m_lVal;
				}
				break;
			case 1:
				{
					ID_KT = var.m_lVal;
				}
				break;
			case 2:
				{
					ID_PROB = var.m_lVal;
				}
				break;
			case 3:
				{	
					str =  GetPhysicalVyprobString(&this->m_geo_view->GetDocument()->m_database, 
						ID_OBJ, ID_KT, ID_PROB, var.m_lVal);
				}
				break;
			case 4:
				{
					str = GetFizMehParam(&this->m_geo_view->GetDocument()->m_database, var.m_lVal);
				}
				break;		
			case 5:
				{	
					str = CMyListCtrl::GetFieldString(var);
				}
				break;
			default:
				str = CMyListCtrl::GetFieldString(var);
			}

			if (iSubItem > 2)
			{
				int i_sub_item = iSubItem - 3;

				lvitem.mask = LVIF_TEXT;// | (iSubItem == 0 ? LVIF_IMAGE : 0);
				lvitem.iItem = (i_sub_item == 0) ? this->GetItemCount( ) : iActualItem;
				lvitem.iSubItem = i_sub_item;

				// calculate the main and sub-item strings for the current item
				lvitem.pszText = str.GetBuffer(str.GetLength());

				//lvitem.iImage = iIcon;
				lvitem.iImage = 0;
				if (i_sub_item == 0)
					iActualItem = this->InsertItem(&lvitem); // insert new item
				else
					this->SetItem(&lvitem); // modify existing item (the sub-item text)
			}
		}
	}
}

#else
void FizMehList::DrawDataRow(CRecordset * pRecordset)
{

	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		int iActualItem = 0;
		for (int iSubItem = 0; iSubItem < 2; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop
			pRecordset->GetFieldValue(iSubItem+4, var);

			switch (iSubItem)
			{
			case 0:
				{
					str = GetFizMehParam(&this->m_geo_view->GetDocument()->m_database, var.m_lVal);
				}
				break;		
			case 1:
				{	
					str = CMyListCtrl::GetFieldString(var);
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
}

#endif