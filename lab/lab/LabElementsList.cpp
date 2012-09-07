// LabElementsList.cpp: implementation of the CLabElementsList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "LabElementsList.h"
#include "DlgLabElements.h"

#include <map>
using namespace std;
#include "../../laboratory/src/lab.h"
#include "../../laboratory/src/LabElement.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLabElementsList::CLabElementsList(CDlgLabElements * dlg, LabElements * lab_elements)
{
	this->m_lab_elements = lab_elements;
	this->m_dlg = dlg;
}
CLabElementsList::~CLabElementsList()
{

}
BEGIN_MESSAGE_MAP(CLabElementsList, CListCtrl)
	//{{AFX_MSG_MAP(CLabElementsList)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CLabElementsList::FillCtrlList()
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		this->GetWindowRect(&rect);
			
		CString str = "";

		for(int i = 0; i < 2; i++) 
		{
			CString str = "";
			switch (i)
			{		
			case 0:
				{
					str = "Lab Element";
				}
				break;		
			case 1:
				{
					str = "size";
				}
				break;
			default:
				str = "---";
			}
			LVCOLUMN col;

			col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
			col.fmt = LVCFMT_LEFT;
			col.cx = rect.Width() / 3;
			col.pszText = str.GetBuffer(str.GetLength());
			col.iSubItem = -1;

			this->InsertColumn(i, &col);
		}

		this->to_fill_colomns = false;
	}

	this->DeleteAllItems();

	if(this->m_lab_elements)
	{
		for (vector<LabElement>::iterator it = this->m_lab_elements->vle.begin();
			it != this->m_lab_elements->vle.end(); it++)
		{
			this->DrawDataRow((*it));
		}
	}
}



void CLabElementsList::DrawDataRow(LabElement & le)
{

	LV_ITEM         lvitem;
	CString str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < 2; iSubItem++) 
	{
		str = "";

		switch (iSubItem)
		{		
		case 0:
			{
				str = LabElement::LabElementTypeToString(le.m_type);
			}
			break;	
		case 1:
			{
				str.Format("%d", le.vsdp.size());
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

void CLabElementsList::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
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
	//AfxMessageBox(str);

//	CDlgObject dialog(m_geo_view, m_geo_view->GetDocument(), false);
//	dialog.DoModal();

	*pResult = 0;
}



void CLabElementsList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;
	
	int r = lpnmitem->iItem;
	if (r < 0) return;

	if (r > -1 && r < this->m_lab_elements->vle.size())
	{
		this->m_dlg->m_list_lab_element.SetLabElement(&this->m_lab_elements->vle[r]);
		this->m_dlg->m_list_lab_element.FillCtrlList();
	}

	*pResult = 0;
}


void CLabElementsList::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;
	
}


