// SoilsList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "SoilsList.h"
#include "EnGeologyView.h"
#include "DlgProbGrunt.h"
#include "DlgProbGr_DblClickMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoilsList

CSoilsList::CSoilsList() 
{
}

CSoilsList::~CSoilsList()
{
}


BEGIN_MESSAGE_MAP(CSoilsList, CListCtrl)
	//{{AFX_MSG_MAP(CSoilsList)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoilsList message handlers
CString GetKTName(CDatabase * database, long id_obj, long id_kt);
void DeleteEndZeros(char * str);
void DeleteEndZeros(CString & str);

void CSoilsList::FillCtrlList(CRecordset * pRecordset)
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
				pRecordset->GetODBCFieldInfo(1, fi);
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(3, fi);
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(4, fi);
				break;
			case 3:
				pRecordset->GetODBCFieldInfo(5, fi);
				break;
			case 4:
				pRecordset->GetODBCFieldInfo(6, fi);
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

const char * _GetKodProbyGrunta(long val); //id_kodprob

CString GetKodProbyGrunta(long val) //id_kodprob
{
	CString str = _GetKodProbyGrunta(val);
	return str;
}


long GetKTIDType(CDatabase * database, long id_obj, long id_kt)
{
	long kt_idtyp;
	CString strQuery;
	strQuery.Format("select * from [KT]");	

	CString where;
	where.Format("ID_OBJ = %ld and ID_KT = %ld", id_obj, id_kt);

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
		kt_idtyp = -1;
		return kt_idtyp;
	}

	if (!_pRecordset->IsBOF())
	{
		_pRecordset->MoveFirst();
		
		CDBVariant _var; // must declare this inside the loop
		_pRecordset->GetFieldValue("ID_TYP", _var);

		kt_idtyp = _var.m_lVal;
	}	

	_pRecordset->Close();

	delete _pRecordset;

	return kt_idtyp;
}

CString GetGruntName(CDatabase * database, long id_obj, long id_gr)
{
	CString str;
	CString strQuery;
	strQuery.Format("select * from [Grunty]");	

	CString where;
	where.Format("ID_OBJ = %ld and ID_GR = %ld", id_obj, id_gr);

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

void CSoilsList::DrawDataRow(CRecordset * pRecordset)
{
	long id_obj;

	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		LV_ITEM         lvitem;
		CString strTime, str;
		int iActualItem = 0;
		{
			CDBVariant var; // must declare this inside the loop
			pRecordset->GetFieldValue(short(0), var);
			//ID_OBJ
			id_obj = var.m_lVal;
		}
		for (int iSubItem = 0; iSubItem < 5; iSubItem++) 
		{
			CDBVariant var; // must declare this inside the loop

			switch (iSubItem)
			{
			case 0:
				{
					pRecordset->GetFieldValue(1, var);
					str = GetKTName(&this->m_geo_view->GetDocument()->m_database, id_obj, var.m_lVal);
				}
				break;		
			case 1:
				{
					pRecordset->GetFieldValue(3, var);
					str = CMyListCtrl::GetFieldString(var);					
					DeleteEndZeros(str);
				}
				break;		
			case 2:
				{
					pRecordset->GetFieldValue(4, var);
					str = CMyListCtrl::GetFieldString(var);
				}
				break;		
			case 3:
				{
					pRecordset->GetFieldValue(5, var);
					str = GetKodProbyGrunta(var.m_lVal);
				}
				break;		
			case 4:
				{
					pRecordset->GetFieldValue(6, var);
					str = CMyListCtrl::GetFieldString(var);
				}
				break;		
			}
			if (iSubItem >= 0)
			{
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
}


void CSoilsList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;
#if 1
#if UPDATE_LISTS_ON_CLICK
	if (this->m_geo_view)
		this->m_geo_view->UpdateSoilRelatedLists();
#endif
#else
	if (this->m_geo_view && this->m_geo_view->GetDocument())
	{
		ATable * ProbGrTable = this->m_geo_view->GetDocument()->m_tables[table_key_ProbGr];
		if(ProbGrTable)
		{
			CDBVariant var0;
			CODBCFieldInfo fi0;

			CDBVariant var1;
			CODBCFieldInfo fi1;

			CDBVariant var2;
			CODBCFieldInfo fi2;

			if(ProbGrTable->m_pRecordset)
			{
				ProbGrTable->m_pRecordset->SetAbsolutePosition(r+1);

				ProbGrTable->m_pRecordset->GetFieldValue(short(0), var0);
				ProbGrTable->m_pRecordset->GetODBCFieldInfo(short(0), fi0);

				ProbGrTable->m_pRecordset->GetFieldValue(int(1), var1);
				ProbGrTable->m_pRecordset->GetODBCFieldInfo(int(1), fi1);

				ProbGrTable->m_pRecordset->GetFieldValue(int(2), var2);
				ProbGrTable->m_pRecordset->GetODBCFieldInfo(int(2), fi2);

				CString where;
				where.Format("%s = %d and %s = %d and %s = %d", 
					fi0.m_strName, var0.m_lVal, 
					fi1.m_strName, var1.m_lVal, 
					fi2.m_strName, var2.m_lVal
					);


				//KTTable->m_pRecordset->GetODBCFieldInfo(short(3), fi);
				CString order_by = "";
				//order_by.Format("H");
				
				//AfxMessageBox(where);

				long table_key = table_key_Granular;				
				m_geo_view->m_GranularList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				table_key = table_key_FizMeh;				
				m_geo_view->m_FizMehList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				table_key = table_key_Zriz;				
				m_geo_view->m_ZrizList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
				
				table_key = table_key_Compress;				
				m_geo_view->m_CompressList.Fill_Ctrl_List(this->m_geo_view->GetDocument()->m_tables[table_key], where, order_by);
			}
		}
	}	
#endif
	*pResult = 0;
}

void CSoilsList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	switch(CDlgProbGr_DblClickMode::selected_mode)
	{
	case 0:
		{
			long id_kt = -1;
			if (this->m_geo_view && this->m_geo_view->GetDocument())
			{
				ATable * ProbGrTable = this->m_geo_view->GetDocument()->m_tables[table_key_ProbGr];
				if(ProbGrTable)
				{
					CDBVariant var0;
					CODBCFieldInfo fi0;

					CDBVariant var1;
					CODBCFieldInfo fi1;

					CDBVariant var2;
					CODBCFieldInfo fi2;

					if(ProbGrTable->m_pRecordset)
					{
						ProbGrTable->m_pRecordset->SetAbsolutePosition(r+1);

						ProbGrTable->m_pRecordset->GetFieldValue(short(0), var0);
						ProbGrTable->m_pRecordset->GetODBCFieldInfo(short(0), fi0);

						ProbGrTable->m_pRecordset->GetFieldValue(int(1), var1);
						ProbGrTable->m_pRecordset->GetODBCFieldInfo(int(1), fi1);

						ProbGrTable->m_pRecordset->GetFieldValue(int(2), var2);
						ProbGrTable->m_pRecordset->GetODBCFieldInfo(int(2), fi2);

						CString where;
						where.Format("%s = %d and %s = %d and %s = %d", 
							fi0.m_strName, var0.m_lVal, 
							fi1.m_strName, var1.m_lVal, 
							fi2.m_strName, var2.m_lVal
							);	

						id_kt = var1.m_lVal;
					}
				}
			}	
			CDlgProbGrunt dialog(m_geo_view, m_geo_view->GetDocument(), false);
			dialog.r_SoilsList = r;
			dialog.id_kt = id_kt;
			dialog.is_geo = true;
			dialog.DoModal();
		}
		break;
	case 1:
		{
			this->m_geo_view->ProbgrSoilname();
		}
		break;
	}

	*pResult = 0;
}
