// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
//#include "lab.h"
#include "MyListCtrl.h"
//#include "labDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl

CMyListCtrl::CMyListCtrl()
{
	m_bFullRowSel = FALSE;
	m_bClientWidthSel = TRUE;

	m_cxClient = 0;
	m_cxStateImageOffset = 0;

	m_clrText = ::GetSysColor(COLOR_WINDOWTEXT);
	m_clrTextBk = ::GetSysColor(COLOR_WINDOW);
	m_clrBkgnd = ::GetSysColor(COLOR_WINDOW);

	to_fill_colomns = true;

}



CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CMyListCtrl)
	ON_WM_PAINT()
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListCtrl message handlers
BOOL CMyListCtrl::OnInitCtrl()
{
//	CMailwriterApp     *pApp;
	CRect           rect;

//	CDialog::OnInitDialog();  // let the base class do the default work
//	UpdateData(TRUE);  // bring the information from the dialog.
//	pApp = (CMailwriterApp *)AfxGetApp();
//	srand((unsigned) time(NULL));  // start the random number generator

	// create image list for header items
//	m_pImageHdrSmall = new CImageList();
//	ASSERT(m_pImageHdrSmall != NULL);    // serious allocation failure checking
//	m_pImageHdrSmall->Create(16, 16, ILC_MASK, 2, 2);
//	m_pImageHdrSmall->Add(pApp->LoadIcon(IDI_HDRICON1));
//	m_pImageHdrSmall->Add(pApp->LoadIcon(IDI_HDRICON2));

	// fill in image lists
//	m_pImageList = new CImageList();
//	m_pImageListSmall = new CImageList();
//	ASSERT(m_pImageList != NULL && m_pImageListSmall != NULL);    // serious allocation failure checking
//	m_pImageList->Create(32, 32, TRUE,  4, 4);
//	m_pImageListSmall->Create(16, 16, TRUE, 4, 4);
//	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST1));
//	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST2));
//	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST3));
//	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST4));
//	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST1));
//	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST2));
//	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST3));
//	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST4));

	// initialize the standard and custom hot cursors
//	m_hMyHotCursor= pApp->LoadCursor(IDC_SPYGLASS);
	m_hStdHotCursor= this->GetHotCursor();

//	FillListCtrl();

	long        lStyle, lStyleOld;

	lStyle = LVS_ICON;
	//lStyle = LVS_SMALLICON;
	lStyle = LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_SHOWSELALWAYS ;
	//lStyle = LVS_LIST;

	lStyleOld = GetWindowLong(this->m_hWnd, GWL_STYLE);
	lStyleOld &= ~(LVS_TYPEMASK);  // turn off all the style (view mode) bits
	lStyleOld |= lStyle;        // Set the new style for the control
	SetWindowLong(this->m_hWnd, GWL_STYLE, lStyleOld);


	return FALSE;  // there is no change in any control focus stuff here.
}



void CMyListCtrl::ModifyHeaderItems(int ncol)
{
	HD_ITEM curItem;

	// retrieve embedded header control
	CHeaderCtrl* pHdrCtrl= NULL;
	pHdrCtrl = this->GetHeaderCtrl();

//	pHdrCtrl->SetImageList(m_pImageHdrSmall);
	// add bmaps to each header item

	memset(&curItem, 0, sizeof(curItem));
	for (int ic = 0; ic < ncol; ic ++)
	{

		pHdrCtrl->GetItem(ic, &curItem);
		curItem.mask= /*HDI_IMAGE |*/ HDI_FORMAT;
//		curItem.iImage = ic;
		curItem.fmt= HDF_LEFT /*| HDF_IMAGE*/ | HDF_STRING;
		pHdrCtrl->SetItem(ic, &curItem);
	}
/*
	pHdrCtrl->GetItem(1, &curItem);
	curItem.mask= HDI_IMAGE | HDI_FORMAT;
	curItem.iImage= 1;
	curItem.fmt= HDF_LEFT | HDF_IMAGE | HDF_STRING;
	pHdrCtrl->SetItem(1, &curItem);*/
}
/*CString CMyListCtrl::GetFieldString(CDBVariant & var)
{
	CString str;
	switch (var.m_dwType) 
	{
	case DBVT_STRING:
		str = *var.m_pstring; // narrow characters
		break;
	case DBVT_SHORT:
		str.Format("%d", (int) var.m_iVal);
		break;
	case DBVT_LONG:
		str.Format("%d", var.m_lVal);
		break;
	case DBVT_SINGLE:
		str.Format("%0.3f", (double) var.m_fltVal);
		break;
	case DBVT_DOUBLE:
		str.Format("%0.3f", var.m_dblVal);
		break;
	case DBVT_DATE:
		str.Format("%d/%d/%d", var.m_pdate->month, var.m_pdate->day, var.m_pdate->year);
		break;
	case DBVT_BOOL:
		str = (var.m_boolVal == 0) ? "FALSE" : "TRUE";
		break;
	case DBVT_UCHAR:
		str.Format("%u", var.m_chVal);
		break;
#if _MFC_VER >= 0x0700
	case DBVT_ASTRING:
		str = *var.m_pstringA; // narrow characters
		break;	
	case DBVT_WSTRING:
		str = *var.m_pstringW; // narrow characters
		break;
#endif
	case DBVT_NULL:
		str =  "";
		break;
	default:
		str.Format("Unk type %d\n", var.m_dwType);
		TRACE("Unknown type %d\n", var.m_dwType);
	}
	return str;
}
CString CMyListCtrl::GetFieldString2(CDBVariant & var)
{
	CString str, s;
	switch (var.m_dwType) 
	{
	case DBVT_STRING:
		s = *var.m_pstring; // narrow characters
		str.Format("STRING %s", s.GetBuffer(s.GetLength()));
		break;
	case DBVT_SHORT:
		str.Format("SHORT %d", (int) var.m_iVal);
		break;
	case DBVT_LONG:
		str.Format("LONG %d", var.m_lVal);
		break;
	case DBVT_SINGLE:
		str.Format("SINGLE %0.3f", (double) var.m_fltVal);
		break;
	case DBVT_DOUBLE:
		str.Format("DOUBLE %0.3f", var.m_dblVal);
		break;
	case DBVT_DATE:
		str.Format("DATE %d/%d/%d", var.m_pdate->month, var.m_pdate->day, var.m_pdate->year);
		break;
	case DBVT_BOOL:
		str = (var.m_boolVal == 0) ? "FALSE" : "TRUE";
		break;
	case DBVT_UCHAR:
		str.Format("UCHAR %u", var.m_chVal);
		break;
#if _MFC_VER >= 0x0700
	case DBVT_ASTRING:
		s = *var.m_pstringA; // narrow characters
		str.Format("ASTRING %s", s.GetBuffer(s.GetLength()));
		break;	
	case DBVT_WSTRING:
		s = *var.m_pstringW; // narrow characters
		str.Format("WSTRING %s", s.GetBuffer(s.GetLength()));
		break;
#endif
	case DBVT_NULL:
		str =  "NULL ----";
		break;
	default:
		str.Format("Unk type %d\n", var.m_dwType);
		TRACE("Unknown type %d\n", var.m_dwType);
	}
	return str;
}*/
void CMyListCtrl::DeleteAllItemsAndColomns()
{
	
	if (this->GetHeaderCtrl())
	{
		int nColumnCount = this->GetHeaderCtrl()->GetItemCount();
		// Delete all of the columns.
		for (int i=0; i < nColumnCount; i++)
		{
			this->DeleteColumn(0);
		}
	}
	DeleteAllItems();
}
// this function is used when a requested style
// LVS_NOLABELWRAP, LVS_NOCOLUMNHEADER, and LVS_NOSORTHEADER
// forces the current control to be re-created with the new style.
void CMyListCtrl::RenewListCtrl()
{
	DeleteAllItems();
//	FillListCtrl(); // repopulate with a new item group
}

/*void CMyListCtrl::Fill_Ctrl_List(ATable * atable, CString where, CString order_by)
{
	if (atable)
	{
		atable->Open_Recordset(this, where, order_by);
	}
}*/



void CMyListCtrl::FillCtrlList()
{
	if (this->to_fill_colomns)
	{
		CRect           rect;
		int nFields = 2;
		this->GetWindowRect(&rect);


		for(int i = 0; i < nFields; i++) 
		{
			CString str;
			switch (i)
			{
			case 0:
				{
					str = "Èìÿ";
				}
				break;
			case 1:
				{
					str = "email";
				}
				break;
			}

			this->InsertColumn(i, str, LVCFMT_LEFT,
				rect.Width() / nFields, -1);
		}
	//	this->ModifyHeaderItems();

		this->to_fill_colomns = false;
	}
	

	/*if (!pRecordset->IsBOF())
	{
		pRecordset->MoveFirst();
		while(!pRecordset->IsEOF()) {
			this->DrawDataRow(pRecordset);
			pRecordset->MoveNext(); // to validate record count
		}
	}*/
}
void CMyListCtrl::AddRow(CString str1, CString str2)
{
	int nColumnCount = 2;
	//if (this->GetHeaderCtrl())
	//	nColumnCount = this->GetHeaderCtrl()->GetItemCount();

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < nColumnCount; iSubItem++) 
	{
		CString str;
		switch (iSubItem)
		{
		case 0:
			{
				str = str1;
			}
			break;
		case 1:
			{
				str = str2;
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

void CMyListCtrl::DrawDataRow()
{
	int nColumnCount = 0;
	if (this->GetHeaderCtrl())
		nColumnCount = this->GetHeaderCtrl()->GetItemCount();

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < nColumnCount; iSubItem++) 
	{
		//CDBVariant var; // must declare this inside the loop
		//pRecordset->GetFieldValue(iSubItem, var);

		//str = CMyListCtrl::GetFieldString(var);
		//str = CMyListCtrl::GetFieldString2(var);

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

// this function is used when a requested style
// can be applied to the existing control, and demonstrated.
void CMyListCtrl::ChangeListCtrlStyle(DWORD dwStyle, BOOL bSetBits)
{
	CRect   rect;

	this->GetWindowRect(&rect);
	ScreenToClient(&rect);
	ASSERT(dwStyle != 0);  // watch out for LVS_foo DEFINITIONS which are 0.
	if (bSetBits)
		this->ModifyStyle(0, dwStyle);
	else
		this->ModifyStyle(dwStyle, 0);

	InvalidateRect(rect);
	UpdateData(FALSE);  // send information back to the dialog
}

void CMyListCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CListCtrl::OnPaint() for painting messages
	CListCtrl::OnPaint();

}

// offsets for first and other columns
#define OFFSET_FIRST    2
#define OFFSET_OTHER    6

void CMyListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CListCtrl& ListCtrl=*this;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rcItem(lpDrawItemStruct->rcItem);
	UINT uiFlags = ILD_TRANSPARENT;
	//CImageList* pImageList;
	int nItem = lpDrawItemStruct->itemID;
	BOOL bFocus = (GetFocus() == this);
	COLORREF clrTextSave = 0;
	COLORREF clrBkSave = 0;
	COLORREF clrImage = m_clrBkgnd;
	static _TCHAR szBuff[MAX_PATH];
	LPCTSTR pszText;

// get item data

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT /*| LVIF_IMAGE*/ | LVIF_STATE;
	lvi.iItem = nItem;
	lvi.iSubItem = 0;
	lvi.pszText = szBuff;
	lvi.cchTextMax = sizeof(szBuff);
	lvi.stateMask = 0xFFFF;     // get all state flags
	ListCtrl.GetItem(&lvi);

	BOOL bSelected = (bFocus || (GetStyle() & LVS_SHOWSELALWAYS)) && lvi.state & LVIS_SELECTED;
	bSelected = bSelected || (lvi.state & LVIS_DROPHILITED);

// set colors if item is selected

	CRect rcAllLabels;
	ListCtrl.GetItemRect(nItem, rcAllLabels, LVIR_BOUNDS);

	CRect rcLabel;
	ListCtrl.GetItemRect(nItem, rcLabel, LVIR_LABEL);

	rcAllLabels.left = rcLabel.left;
	if (m_bClientWidthSel && rcAllLabels.right<m_cxClient)
		rcAllLabels.right = m_cxClient;

	if (bSelected)
	{
		clrTextSave = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		clrBkSave = pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));

		CBrush cbr(::GetSysColor(COLOR_HIGHLIGHT));
		pDC->FillRect(rcAllLabels, &cbr);
	}
	else
	{
		CBrush cbr(m_clrTextBk);
		pDC->FillRect(rcAllLabels, &cbr);
	}
/*
// set color and mask for the icon

	if (lvi.state & LVIS_CUT)
	{
		clrImage = m_clrBkgnd;
		uiFlags |= ILD_BLEND50;
	}
	else if (bSelected)
	{
		clrImage = ::GetSysColor(COLOR_HIGHLIGHT);
		uiFlags |= ILD_BLEND50;
	}

// draw state icon

	UINT nStateImageMask = lvi.state & LVIS_STATEIMAGEMASK;
	if (nStateImageMask)
	{
		int nImage = (nStateImageMask>>12) - 1;
		pImageList = ListCtrl.GetImageList(LVSIL_STATE);
		if (pImageList)
		{
			pImageList->Draw(pDC, nImage,
				CPoint(rcItem.left, rcItem.top), ILD_TRANSPARENT);
		}
	}

// draw normal and overlay icon

	CRect rcIcon;
	ListCtrl.GetItemRect(nItem, rcIcon, LVIR_ICON);

	pImageList = ListCtrl.GetImageList(LVSIL_SMALL);
	if (pImageList)
	{
		UINT nOvlImageMask=lvi.state & LVIS_OVERLAYMASK;
		if (rcItem.left<rcItem.right-1)
		{
			ImageList_DrawEx(pImageList->m_hImageList, lvi.iImage,
					pDC->m_hDC,rcIcon.left,rcIcon.top, 16, 16,
					m_clrBkgnd, clrImage, uiFlags | nOvlImageMask);
		}
	}
*/
// draw item label

	ListCtrl.GetItemRect(nItem, rcItem, LVIR_LABEL);
	rcItem.right -= m_cxStateImageOffset;

	pszText = MakeShortString(pDC, szBuff,
				rcItem.right-rcItem.left, 2*OFFSET_FIRST);

	rcLabel = rcItem;
	rcLabel.left += OFFSET_FIRST;
	rcLabel.right -= OFFSET_FIRST;

	pDC->DrawText(pszText,-1,rcLabel,DT_LEFT | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);

// draw labels for extra columns

	LV_COLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH;

	for(int nColumn = 1; ListCtrl.GetColumn(nColumn, &lvc); nColumn++)
	{
		rcItem.left = rcItem.right;
		rcItem.right += lvc.cx;

		int nRetLen = ListCtrl.GetItemText(nItem, nColumn,
						szBuff, sizeof(szBuff));
		if (nRetLen == 0)
			continue;

		pszText = MakeShortString(pDC, szBuff,
			rcItem.right - rcItem.left, 2*OFFSET_OTHER);

		UINT nJustify = DT_LEFT;

		if(pszText == szBuff)
		{
			switch(lvc.fmt & LVCFMT_JUSTIFYMASK)
			{
			case LVCFMT_RIGHT:
				nJustify = DT_RIGHT;
				break;
			case LVCFMT_CENTER:
				nJustify = DT_CENTER;
				break;
			default:
				break;
			}
		}

		rcLabel = rcItem;
		rcLabel.left += OFFSET_OTHER;
		rcLabel.right -= OFFSET_OTHER;

		pDC->DrawText(pszText, -1, rcLabel,
			nJustify | DT_SINGLELINE | DT_NOPREFIX | DT_NOCLIP | DT_VCENTER);
	}

// draw focus rectangle if item has focus

	if (lvi.state & LVIS_FOCUSED && bFocus)
		pDC->DrawFocusRect(rcAllLabels);

// set original colors if item was selected

	if (bSelected)
	{
		pDC->SetTextColor(clrTextSave);
		pDC->SetBkColor(clrBkSave);
	}	
}
LPCTSTR CMyListCtrl::MakeShortString(CDC* pDC, LPCTSTR lpszLong, int nColumnLen, int nOffset)
{
	static const _TCHAR szThreeDots[] = _T("...");

	int nStringLen = lstrlen(lpszLong);

	if(nStringLen == 0 ||
		(pDC->GetTextExtent(lpszLong, nStringLen).cx + nOffset) <= nColumnLen)
	{
		return(lpszLong);
	}

	static _TCHAR szShort[MAX_PATH];

	lstrcpy(szShort,lpszLong);
	int nAddLen = pDC->GetTextExtent(szThreeDots,sizeof(szThreeDots)).cx;

	for(int i = nStringLen-1; i > 0; i--)
	{
		szShort[i] = 0;
		if((pDC->GetTextExtent(szShort, i).cx + nOffset + nAddLen)
			<= nColumnLen)
		{
			break;
		}
	}

	lstrcat(szShort, szThreeDots);
	return(szShort);
}

int CMyListCtrl::GetSelected()
{
	return this->GetSelectionMark();

	POSITION pos = this->GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		return -1;
	}
	else
	{
		while (pos)
		{
			
			int nItem = this->GetNextSelectedItem(pos);
			return nItem;
		}
	}
	
	return -1;
}
