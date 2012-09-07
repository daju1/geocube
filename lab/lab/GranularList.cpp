// GranularList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "GranularList.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGranularList

CGranularList::CGranularList()
{
}

CGranularList::~CGranularList()
{
}


BEGIN_MESSAGE_MAP(CGranularList, CListCtrl)
	//{{AFX_MSG_MAP(CGranularList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGranularList message handlers

void CGranularList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 3; i <= 4; i++) 
		{
			pRecordset->GetODBCFieldInfo(i, fi);

			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 2;
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

CString GetGranularFraction(CDatabase * database, long id_gran);

void CGranularList::DrawDataRow(CRecordset * pRecordset)
{

	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		int iActualItem = 0;
		for (int iSubItem = 0; iSubItem < 2; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop
			pRecordset->GetFieldValue(iSubItem+3, var);

			switch (iSubItem)
			{
			case 0:
				{
					str = GetGranularFraction(&this->m_geo_view->GetDocument()->m_database, var.m_lVal);
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
