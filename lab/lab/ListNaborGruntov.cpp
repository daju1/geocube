// ListNaborGruntov.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "ListNaborGruntov.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListNaborGruntov

CListNaborGruntov::CListNaborGruntov()
{
}

CListNaborGruntov::~CListNaborGruntov()
{
}


BEGIN_MESSAGE_MAP(CListNaborGruntov, CListCtrl)
	//{{AFX_MSG_MAP(CListNaborGruntov)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListNaborGruntov message handlers
BOOL CListNaborGruntov::OnInitCtrl()
{
	CLabApp     *pApp;
	CRect           rect;

//	CDialog::OnInitDialog();  // let the base class do the default work
//	UpdateData(TRUE);  // bring the information from the dialog.
	pApp = (CLabApp *)AfxGetApp();
	srand((unsigned) time(NULL));  // start the random number generator

	m_hMyHotCursor= pApp->LoadCursor(IDC_SPYGLASS);
	m_hStdHotCursor= this->GetHotCursor();

//	FillListCtrl();

	long        lStyle, lStyleOld;

	lStyle = LVS_ICON;
	//lStyle = LVS_SMALLICON;
	//lStyle = LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_OWNERDATA | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
	lStyle = LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_SHOWSELALWAYS ;
	//lStyle = LVS_LIST;

	lStyleOld = GetWindowLong(this->m_hWnd, GWL_STYLE);
	lStyleOld &= ~(LVS_TYPEMASK);  // turn off all the style (view mode) bits
	lStyleOld |= lStyle;        // Set the new style for the control
	SetWindowLong(this->m_hWnd, GWL_STYLE, lStyleOld);


	return FALSE;  // there is no change in any control focus stuff here.
}





void CListNaborGruntov::FillCtrlList(CRecordset * pRecordset)
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = (int) pRecordset->GetODBCFieldCount();
		this->GetWindowRect(&rect);
		double W = rect.Width() - 10;


		CODBCFieldInfo fi;
		for(int i = 0; i < 3; i++) 
		{
			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.iSubItem = -1;

			switch(i)
			{
			case 0:
				pRecordset->GetODBCFieldInfo(1, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				//col.pszText = "Тип";
				col.cx = W * 0.1;
				break;
			case 1:
				pRecordset->GetODBCFieldInfo(2, fi);
				//col.pszText = "Сечение";
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = W * 0.45;
				break;
			case 2:
				pRecordset->GetODBCFieldInfo(3, fi);
				col.pszText = fi.m_strName.GetBuffer(fi.m_strName.GetLength());
				col.cx = W * 0.45;
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


void CListNaborGruntov::DrawDataRow(CRecordset * pRecordset)
{

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 3; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		switch (iSubItem)
		{
		case 0:
			{
				pRecordset->GetFieldValue(1, var);
				//switch(var.m_lVal)
				//{
				//case 1:
				//	str = "Круглая";
				//	break;
				//case 2:
				//	str = "Квадратная";
				//	break;
				//default:
                    str = CMyListCtrl::GetFieldString(var);
				//	break;
				//}
			}
			break;		
		case 1:
			{
				pRecordset->GetFieldValue(2, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
		case 2:
			{
				pRecordset->GetFieldValue(3, var);
				str = CMyListCtrl::GetFieldString(var);
			}
			break;		
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



