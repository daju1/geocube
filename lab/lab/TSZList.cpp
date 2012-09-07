// TSZListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "TSZList.h"
#include "EnGeologyView.h"
#include "DlgStatZond.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTSZList
//IMPLEMENT_DYNCREATE(CTSZList, CMyList)


CTSZList::CTSZList()
{
}

CTSZList::~CTSZList()
{
}


BEGIN_MESSAGE_MAP(CTSZList, CListCtrl)
	//{{AFX_MSG_MAP(CTSZList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTSZList message handlers
CString GetUstanovkaName(CDatabase * database, long id_ust)
{
	CString str;
	CString strQuery;
	strQuery.Format("select * from [Ustanovka]");	

	CString where;
	where.Format("ID_UST = %ld", id_ust);

	CRecordset * _pRecordset = new CRecordset(database);

	try {
		_pRecordset->m_strFilter = where;
		_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly);
	}
	catch (CDBException* pe) {
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		_pRecordset->Close();
		delete _pRecordset;
		str = "";
		return str;
	}

	if (!_pRecordset->IsBOF())
	{
		_pRecordset->MoveFirst();
		
		CDBVariant _var; // must declare this inside the loop
		_pRecordset->GetFieldValue("NAZVA", _var);

		str = CMyListCtrl::GetFieldString(_var);
	}

	_pRecordset->Close();
	delete _pRecordset;

	return str;
}









void CTSZList::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);
		double W = rect.Width() - 10;


		CODBCFieldInfo fi;
		for(int i = 0; i < 2; i++) 
		{
			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.iSubItem = -1;
			switch(i)
			{
			case 0:
				pRecordset->GetODBCFieldInfo(2, fi);
				col.pszText = "Установка";
				col.cx = 0.45*W;
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(3, fi);
				col.pszText = "Глубина";
				col.cx = 0.50*W;
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


void CTSZList::DrawDataRow(CRecordset * pRecordset)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 2; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		switch (iSubItem)
		{
		case 0:
			{
				pRecordset->GetFieldValue(2, var);
				str = GetUstanovkaName(&this->m_geo_view->GetDocument()->m_database, var.m_lVal);
			}
			break;		
		case 1:
			{
				pRecordset->GetFieldValue(3, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
		}


		

		/*switch (iSubItem)
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
		}*/

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


void CTSZList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	*pResult = 0;
}

void CTSZList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	CDlgStatZond dialog(this->m_geo_view, this->m_geo_view->GetLabDoc(), &this->m_geo_view->GetLabDoc()->m_database);
	dialog.DoModal();

	
	*pResult = 0;
}
