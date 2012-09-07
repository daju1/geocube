// EnGeoObjectsList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "LabObjectsList.h"
#include "LaboratoryView.h"
#include "SetObject.h"
#include "ObjectDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabObjectsList

CLabObjectsList::CLabObjectsList()
{

}

CLabObjectsList::~CLabObjectsList()
{
}


BEGIN_MESSAGE_MAP(CLabObjectsList, CListCtrl)
	//{{AFX_MSG_MAP(CLabObjectsList)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLabObjectsList message handlers

void CLabObjectsList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);


		CODBCFieldInfo fi;
		for(int i = 0; i < nFields; i++) 
		{
			pRecordset->GetODBCFieldInfo(i, fi);

			this->InsertColumn(i, fi.m_strName, LVCFMT_LEFT,
				rect.Width() / (nFields), -1);
		}
		
		//this->ModifyHeaderItems(3);

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

void CLabObjectsList::DrawDataRow(CRecordset * pRecordset)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 3; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem, var);

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

void CLabObjectsList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	/*LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;

	char str[1024];
	sprintf(
		str, 
		"OnDblclk\n"
		"pNMHDR->code = %u\n"
		"pNMHDR->hwndFrom = %x\n"
		"pNMHDR->idFrom = %d\n"
		"r = %d c = %d"
		,
		pNMHDR->code,
		pNMHDR->hwndFrom,
		pNMHDR->idFrom,
		r,c
		);*/
	CDlgObject dialog(m_lab_view, m_lab_view->GetDocument(), false);
	dialog.DoModal();
	
	*pResult = 0;
}

void CLabObjectsList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;
#if 1
#if UPDATE_LISTS_ON_CLICK
	if (this->m_lab_view)
		this->m_lab_view->UpdateObjectRelatedLists();
#endif
#else
	if (this->m_lab_view && this->m_lab_view->GetDocument())
	{
#if 0
		ATable * ObjectsTable = this->m_lab_view->GetDocument()->m_tables[table_key_Objects];
		if(ObjectsTable)
		{
			CDBVariant var;
			CODBCFieldInfo fi;
			if(ObjectsTable->m_pRecordset)
			{
				ObjectsTable->m_pRecordset->SetAbsolutePosition(r+1);
				ObjectsTable->m_pRecordset->GetFieldValue(short(0), var);
				ObjectsTable->m_pRecordset->GetODBCFieldInfo(short(0), fi);

				CString where;
				where.Format("%s = %d", fi.m_strName, var.m_lVal);

		
				CString order_by;
				order_by.Format("ID_TYP, ID_KT, DTBUR");
				order_by.Format("NAZVA");
		
		
				long table_key = table_key_KT;
				order_by.Format("ID_KT");					
				m_lab_view->m_KTLabList.Fill_Ctrl_List(this->m_lab_view->GetDocument()->m_tables[table_key], where, order_by);
				
				
				table_key = table_key_ProbGr;
				order_by.Format("ID_KT, ID_PROB");				
				m_lab_view->m_SoilsList.Fill_Ctrl_List(this->m_lab_view->GetDocument()->m_tables[table_key], where, order_by);
			}
		}
#else
		SetObject setObject(&this->m_lab_view->GetDocument()->m_database);
		if (!setObject.Open())
			return;
		setObject.SetAbsolutePosition(r+1);
		CString where;
		where.Format("ID_OBJ = %d", setObject.m_ID_OBJ);
		setObject.Close();


		CString order_by;
		order_by.Format("ID_TYP, ID_KT, DTBUR");
		order_by.Format("NAZVA");


		long table_key = table_key_KT;
		order_by.Format("ID_KT");					
		m_lab_view->m_KTLabList.Fill_Ctrl_List(this->m_lab_view->GetDocument()->m_tables[table_key], where, order_by);
		
		
		table_key = table_key_ProbGr;
		order_by.Format("ID_KT, ID_PROB");				
		m_lab_view->m_SoilsList.Fill_Ctrl_List(this->m_lab_view->GetDocument()->m_tables[table_key], where, order_by);
#endif
	}
#endif
	*pResult = 0;
}


void CLabObjectsList::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;
	
}
