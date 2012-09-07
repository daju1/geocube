// KTLabList.cpp: implementation of the CKTLabList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "KTLabList.h"
#include "LaboratoryView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CString GetBurType(long val);
CString GetKTType(long val);

CKTLabList::CKTLabList()
{

}

CKTLabList::~CKTLabList()
{

}

BEGIN_MESSAGE_MAP(CKTLabList, CListCtrl)
	//{{AFX_MSG_MAP(CKTLabList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CKTLabList::FillCtrlList(CRecordset * pRecordset)
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
void CKTLabList::DrawDataRow(CRecordset * pRecordset)
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


