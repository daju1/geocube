// ListGenezis.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "ListGenezis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListGenezis

CListGenezis::CListGenezis()
{
}

CListGenezis::~CListGenezis()
{
}


BEGIN_MESSAGE_MAP(CListGenezis, CListCtrl)
	//{{AFX_MSG_MAP(CListGenezis)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListGenezis message handlers
void CListGenezis::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 2; i < 3; i++) 
		{
			pRecordset->GetODBCFieldInfo(i, fi);

			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 1;
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


void CListGenezis::DrawDataRow(CRecordset * pRecordset)
{

	if (this->m_view)
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		int iActualItem = 0;
		for (int iSubItem = 0; iSubItem < 1; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop
			pRecordset->GetFieldValue(iSubItem+2, var);

			switch (iSubItem)
			{
			case 0:
				{
					str = CMyListCtrl::GetFieldString(var);
				}
				break;		
			case 1:
				{	
					//str = GetGranularFraction(&this->m_geo_view->GetDocument()->m_database, var.m_lVal);
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
