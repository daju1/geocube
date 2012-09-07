// MyList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "MyList.h"
#include "labDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyList

IMPLEMENT_DYNCREATE(CMyList, CListViewEx)

CMyList::CMyList()
{
	this->m_lab_view = NULL;
}

CMyList::~CMyList()
{
	m_LargeImageList.Detach();
	m_SmallImageList.Detach();
	m_StateImageList.Detach();
}


BEGIN_MESSAGE_MAP(CMyList, CListViewEx)
	//{{AFX_MSG_MAP(CMyList)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyList drawing

void CMyList::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyList diagnostics

#ifdef _DEBUG
void CMyList::AssertValid() const
{
	CListView::AssertValid();
}

void CMyList::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyList message handlers


BOOL CMyList::OnInitCtrl()
{
	CLabApp     *pApp;
	CRect           rect;

	CListCtrl& ListCtrl = GetListCtrl();
//	CDialog::OnInitDialog();  // let the base class do the default work
//	UpdateData(TRUE);  // bring the information from the dialog.
	pApp = (CLabApp *)AfxGetApp();
	srand((unsigned) time(NULL));  // start the random number generator

	// create image list for header items
/*	m_pImageHdrSmall = new CImageList();
	ASSERT(m_pImageHdrSmall != NULL);    // serious allocation failure checking
	m_pImageHdrSmall->Create(16, 16, ILC_MASK, 2, 2);
	m_pImageHdrSmall->Add(pApp->LoadIcon(IDI_HDRICON1));
	m_pImageHdrSmall->Add(pApp->LoadIcon(IDI_HDRICON2));*/

	// fill in image lists
/*	m_pImageList = new CImageList();
	m_pImageListSmall = new CImageList();
	ASSERT(m_pImageList != NULL && m_pImageListSmall != NULL);    // serious allocation failure checking
	m_pImageList->Create(32, 32, TRUE,  4, 4);
	m_pImageListSmall->Create(16, 16, TRUE, 4, 4);
	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST1));
	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST2));
	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST3));
	m_pImageList->Add(pApp->LoadIcon(IDI_ICONLIST4));
	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST1));
	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST2));
	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST3));
	m_pImageListSmall->Add(pApp->LoadIcon(IDI_ICONLIST4));*/

/*	// initialize the standard and custom hot cursors
//	m_hMyHotCursor= pApp->LoadCursor(IDC_SPYGLASS);
//	m_hStdHotCursor= ListCtrl.GetHotCursor();*/

	FillListCtrl();

	long        lStyle, lStyleOld;

	lStyle = LVS_ICON;
	//lStyle = LVS_SMALLICON;
	//lStyle = LVS_LIST;
	lStyle = LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_SHOWSELALWAYS ;

	lStyleOld = GetWindowLong(ListCtrl.m_hWnd, GWL_STYLE);
	lStyleOld &= ~(LVS_TYPEMASK);  // turn off all the style (view mode) bits
	lStyleOld |= lStyle;        // Set the new style for the control
	SetWindowLong(ListCtrl.m_hWnd, GWL_STYLE, lStyleOld);


	return FALSE;  // there is no change in any control focus stuff here.
}
void CMyList::DeleteAllItemsAndColomns()
{
	CListCtrl& ListCtrl = GetListCtrl();
	if (ListCtrl.GetHeaderCtrl())
	{
		int nColumnCount = ListCtrl.GetHeaderCtrl()->GetItemCount();
		// Delete all of the columns.
		for (int i=0; i < nColumnCount; i++)
		{
			ListCtrl.DeleteColumn(0);
		}
	}
	ListCtrl.DeleteAllItems();
}

/*void CMyList::FillCtrlList(ATable * atable, CString where, CString order_by)
{
	if (atable)
	{
		atable->OpenRecordset(this, where, order_by);
	}
}*/
void CMyList::DrawDataRow(CRecordset * pRecordset)
{
	CListCtrl& ListCtrl = GetListCtrl();
	int nColumnCount = 0;
	if (ListCtrl.GetHeaderCtrl())
		nColumnCount = ListCtrl.GetHeaderCtrl()->GetItemCount();

	LV_ITEM         lvitem;
	CString strTime, str;
	int iActualItem = 0;
	for (int iSubItem = 0; iSubItem < nColumnCount; iSubItem++) 
	{
		CDBVariant var; // must declare this inside the loop
		pRecordset->GetFieldValue(iSubItem, var);
		switch (var.m_dwType) {
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
			str.Format("%10.3f", (double) var.m_fltVal);
			break;
		case DBVT_DOUBLE:
			str.Format("%10.3f", var.m_dblVal);
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
			
		case DBVT_NULL:
			str =  "----";
			break;
		default:
			str.Format("Unk type %d\n", var.m_dwType);
			TRACE("Unknown type %d\n", var.m_dwType);
		}

		lvitem.mask = LVIF_TEXT | (iSubItem == 0 ? LVIF_IMAGE : 0);
		lvitem.iItem = (iSubItem == 0) ? ListCtrl.GetItemCount( ) : iActualItem;
		lvitem.iSubItem = iSubItem;

		// calculate the main and sub-item strings for the current item
		lvitem.pszText = str.GetBuffer(str.GetLength());

		//lvitem.iImage = iIcon;
		lvitem.iImage = 0;
		if (iSubItem == 0)
			iActualItem = ListCtrl.InsertItem(&lvitem); // insert new item
		else
			ListCtrl.SetItem(&lvitem); // modify existing item (the sub-item text)
	}
}

void CMyList::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	CListViewEx::PostNcDestroy();
}

void CMyList::OnInitialUpdate() 
{
	CListViewEx::OnInitialUpdate();
	CListCtrl& ListCtrl = GetListCtrl();

	//=== Связывание списка с элементом управления деревом
	ListCtrl.SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	ListCtrl.SetImageList(&m_SmallImageList, LVSIL_SMALL);		
	ListCtrl.SetImageList(&m_StateImageList, LVSIL_STATE);

#if 0
// set image lists
	SHFILEINFO info;

	// Попытка получить описатель системного списка значков
	HIMAGELIST hImg1 = (HIMAGELIST)::SHGetFileInfo("C:\\",0,
							&info,sizeof(info),
							SHGFI_SYSICONINDEX | SHGFI_LARGEICON);

	//=== Приписываем описатель системного списка
	//=== изображений объекту CImageList
	if (!hImg1 || !m_LargeImageList.Attach(hImg1))
	{
		MessageBox(0,"Не могу получить System Image List!");
		return;
	}

	// Попытка получить описатель системного списка значков
	HIMAGELIST hImg2 = (HIMAGELIST)::SHGetFileInfo("C:\\",0,
							&info,sizeof(info),
							SHGFI_SYSICONINDEX | SHGFI_SMALLICON);

	//=== Приписываем описатель системного списка
	//=== изображений объекту CImageList
	if (!hImg2 || !m_SmallImageList.Attach(hImg2))
	{
		MessageBox(0,"Не могу получить System Image List!");
		return;
	}


	//=== Связывание списка с элементом управления деревом
	ListCtrl.SetImageList(&m_LargeImageList, LVSIL_NORMAL);
	ListCtrl.SetImageList(&m_SmallImageList, LVSIL_SMALL);

// insert columns

	int i;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		ListCtrl.InsertColumn(i,&lvc);
	}
#endif	
}

BOOL CMyList::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CListViewEx::PreCreateWindow(cs);
}
