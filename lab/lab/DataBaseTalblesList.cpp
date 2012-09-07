// DataBaseTalblesList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "DataBaseTalblesList.h"
#include "EnGeologyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataBaseTalblesList

CDataBaseTalblesList::CDataBaseTalblesList()
{
}

CDataBaseTalblesList::~CDataBaseTalblesList()
{
}


BEGIN_MESSAGE_MAP(CDataBaseTalblesList, CListCtrl)
	//{{AFX_MSG_MAP(CDataBaseTalblesList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataBaseTalblesList message handlers

void CDataBaseTalblesList::FillListCtrl()
{
	CRect           rect;
	int             iItem, iSubItem, iActualItem;
	LV_ITEM         lvitem;
	CString         strItem1= _T("DB Table");
	LPTSTR          pStrTemp1;
	CLabApp		    *pApp;
	
	iItem = iSubItem = iActualItem = 0;

	pApp = (CLabApp *)AfxGetApp();
//	this->SetImageList(m_pImageList, LVSIL_NORMAL);
//	this->SetImageList(m_pImageListSmall, LVSIL_SMALL);

	// insert two columns (REPORT mode) and modify the new header items
	this->GetWindowRect(&rect);
	this->InsertColumn(0, strItem1, LVCFMT_LEFT,
		rect.Width(), 0);

	ModifyHeaderItems(1);

	for (iItem = 0; iItem < int(names.size()); iItem++)  // insert the items and subitems into the list view.
		for (iSubItem = 0; iSubItem < 1; iSubItem++)
		{

			lvitem.mask = LVIF_TEXT/* | (iSubItem == 0? LVIF_IMAGE : 0)*/;
			lvitem.iItem = (iSubItem == 0)? iItem : iActualItem;
			lvitem.iSubItem = iSubItem;

			// calculate the main and sub-item strings for the current item
			pStrTemp1 = names[iItem].GetBuffer(names[iItem].GetLength());
			lvitem.pszText = pStrTemp1;

			//lvitem.iImage = iIcon;
			lvitem.iImage = 0;
			if (iSubItem == 0)
				iActualItem = this->InsertItem(&lvitem); // insert new item
			else
				this->SetItem(&lvitem); // modify existing item (the sub-item text)
		}
}

void CDataBaseTalblesList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;	
	int r = lpnmitem->iItem;
	if (r < 0) return;
#if 0
	/*int c = lpnmitem->iSubItem;

	char str[1024];
	sprintf(
		str, 
		"OnDblclk\n"
		"pNMHDR->code = %u\n"
		"pNMHDR->hwndFrom = %x\n"
		"pNMHDR->idFrom = %d\n"
		"r = %d c = %d\n"
		"%s"
		,
		pNMHDR->code,
		pNMHDR->hwndFrom,
		pNMHDR->idFrom,
		r,c,
		names[r].GetBuffer(names[r].GetLength())
		);*/

	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
#if 0
//		this->m_geo_view->GetDocument()->m_tables.insert(map<CString, ATable *>::value_type(names[r], new ATable(this->m_geo_view->GetDocument(), names[r])));
//		m_geo_view->m_ListView.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[names[r]], "", "");
 
#else

		m_geo_view->m_ListView.DeleteAllItemsAndColomns();
		ATable * a_table = new ATable(this->m_geo_view->GetDocument(), names[r]);
		m_geo_view->m_ListView.Fill_Ctrl_List(a_table, "", "");
		delete a_table;
#endif
	}
#endif

	*pResult = 0;
}

void CDataBaseTalblesList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;

	char str[1024];
	sprintf(
		str, 
		"OnDblclk\n"
		"pNMHDR->code = %u\n"
		"pNMHDR->hwndFrom = %x\n"
		"pNMHDR->idFrom = %d\n"
		"r = %d c = %d\n"
		"%s"
		,
		pNMHDR->code,
		pNMHDR->hwndFrom,
		pNMHDR->idFrom,
		r,c,
		names[r].GetBuffer(names[r].GetLength())
		);
	AfxMessageBox(str);
	
	*pResult = 0;
}
