// FizMehListLab.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SetFizMeh.h"
#include "FizMehListLab.h"
#include "laboratoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFizMehListLab

FizMehListLab::FizMehListLab()
{
}

FizMehListLab::~FizMehListLab()
{
}


BEGIN_MESSAGE_MAP(FizMehListLab, CListCtrl)
	//{{AFX_MSG_MAP(FizMehListLab)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFizMehListLab message handlers

void FizMehListLab::FillCtrlList(CRecordset * pRecordset)
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

CString GetFizMehParam(CDatabase * database, long id_param)
{
	CString str;
	CString strQuery;
	strQuery.Format("select * from [FizMehAllParam]");	

	CString where;
	where.Format("ID_PARAM = %ld", id_param);

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
		_pRecordset->GetFieldValue("NAZVA_R", _var);

		str = CMyListCtrl::GetFieldString(_var);
	}

	_pRecordset->Close();
	delete _pRecordset;

	return str;
}



void FizMehListLab::DrawDataRow(CRecordset * pRecordset)
{
	if (this->m_lab_view && this->m_lab_view->GetDocument())
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
					str =  GetPhysicalVyprobString(&this->m_lab_view->GetDocument()->m_database, 
						ID_OBJ, ID_KT, ID_PROB, var.m_lVal);
				}
				break;
			case 4:
				{
					str = GetFizMehParam(&this->m_lab_view->GetDocument()->m_database, var.m_lVal);
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
