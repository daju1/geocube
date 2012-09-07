// GranularListLab.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "GranularListLab.h"
#include "laboratoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGranularListLab

GranularListLab::GranularListLab()
{
}

GranularListLab::~GranularListLab()
{
}


BEGIN_MESSAGE_MAP(GranularListLab, CListCtrl)
	//{{AFX_MSG_MAP(GranularListLab)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGranularListLab message handlers

void GranularListLab::FillCtrlList(CRecordset * pRecordset)
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

CString GetGranularFraction(CDatabase * database, long id_gran)
{
	CString str;
	CString strQuery;
	strQuery.Format("select * from [GranularAll_2]");	

	CString where;
	where.Format("ID_GRAN = %ld", id_gran);

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



void GranularListLab::DrawDataRow(CRecordset * pRecordset)
{
	if (this->m_lab_view && this->m_lab_view->GetDocument())
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
					str = GetGranularFraction(&this->m_lab_view->GetDocument()->m_database, var.m_lVal);
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
