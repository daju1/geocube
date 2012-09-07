// GranularList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "CompressList.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CompressList

CompressList::CompressList()
{
}

CompressList::~CompressList()
{
}


BEGIN_MESSAGE_MAP(CompressList, CListCtrl)
	//{{AFX_MSG_MAP(CompressList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CompressList message handlers

void CompressList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 0; i < 5; i++) 
		{
			switch(i)
			{
			case 0:
				pRecordset->GetODBCFieldInfo(21, fi);
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(5, fi);
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(6, fi);
				break;
			case 3:
				pRecordset->GetODBCFieldInfo(13, fi);
				break;
			case 4:
				pRecordset->GetODBCFieldInfo(14, fi);
				break;
			}
			

			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 5;
			col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
			col.iSubItem = -1;

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

void CompressList::DrawDataRow(CRecordset * pRecordset)
{
	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		int iActualItem = 0;
		for (int iSubItem = 0; iSubItem < 5; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop

			switch (iSubItem)
			{
			case 0:
				{
					pRecordset->GetFieldValue(21, var);
				}
				break;		
			case 1:
				{
					pRecordset->GetFieldValue(5, var);
				}
				break;		
			case 2:
				{
					pRecordset->GetFieldValue(6, var);
				}
				break;		
			case 3:
				{
					pRecordset->GetFieldValue(13, var);
				}
				break;		
			case 4:
				{
					pRecordset->GetFieldValue(14, var);
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
}
