// UstList.cpp: implementation of the UstList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "UstList.h"

#include "SetUstanovka.h"


void DeleteEndZeros(char * str);
void DeleteEndZeros(CString & str);

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUstList::CUstList(CDatabase * database)
{
	this->p_database = database;
}
CUstList::~CUstList()
{

}

BEGIN_MESSAGE_MAP(CUstList, CListCtrl)
	//{{AFX_MSG_MAP(CUstList)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CUstList::OnInitCtrl()
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
	lStyle = LVS_REPORT | LVS_OWNERDRAWFIXED | LVS_SINGLESEL | LVS_SHOWSELALWAYS;
	//lStyle = LVS_LIST;

	lStyleOld = GetWindowLong(this->m_hWnd, GWL_STYLE);
	lStyleOld &= ~(LVS_TYPEMASK);  // turn off all the style (view mode) bits
	lStyleOld |= lStyle;        // Set the new style for the control
	SetWindowLong(this->m_hWnd, GWL_STYLE, lStyleOld);


	return FALSE;  // there is no change in any control focus stuff here.
}




void CUstList::FillCtrlList()
{
	CString str = "";
	CRect           rect;
	this->GetWindowRect(&rect);			
	this->DeleteAllItemsAndColomns();

	for(int i = 0; i < 9; i++) 
	{
		str = "";
		switch (i)
		{		
		case 0:
			{
				str = "№";
			}
			break;		
		case 1:
			{
				str = "Название";
			}
			break;		
		case 2:
			{
				str = "Тип зонда";
			}
			break;
		case 3:
			{
				str = "№ схемы";
			}
			break;
		case 4:
			{
				str = "Kg";
			}
			break;
		case 5:
			{
				str = "Kf";
			}
			break;
		case 6:
			{
				str = "Bg";
			}
			break;
		case 7:
			{
				str = "Bf";
			}
			break;
		case 8:
			{
				str = "shtanga_d";
			}
			break;
		default:
			str = "---";
		}
		LVCOLUMN col;

		col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		col.fmt = LVCFMT_LEFT;
		col.cx = rect.Width() / 9;
		col.pszText = str.GetBuffer(str.GetLength());
		col.iSubItem = -1;

		this->InsertColumn(i, &col);
	}

	int iActualItem = 0;

	SetUstanovka setUstanovka(this->p_database);
	setUstanovka.m_strFilter.Format("");
	setUstanovka.m_strSort.Format("");
	if ( !setUstanovka.Open(CRecordset::dynaset) )
		return;

	int npp = 1, iSubItem;

	if (!setUstanovka.IsBOF()) 
	{
		setUstanovka.MoveFirst( );
		while(!setUstanovka.IsEOF()) 
		{
			iSubItem = 0;
			
			str.Format("%d", npp++);
			str.Format("%d", setUstanovka.m_ID_UST);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%s", setUstanovka.m_NAZVA);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%d", setUstanovka.m_TYP_ZOND);
			InSertTheItem(str, iActualItem, iSubItem++);
		
			str.Format("%d", setUstanovka.m_N_SHEMA);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%f", setUstanovka.m_Kg);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%f", setUstanovka.m_Kf);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%f", setUstanovka.m_Bg);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%f", setUstanovka.m_Bf);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%f", setUstanovka.m_Shtanga_d);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			setUstanovka.MoveNext();

		}
	}
}

void CUstList::InSertTheItem(CString & str, int & iActualItem, int iSubItem)
{
	LV_ITEM         lvitem;
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




void CUstList::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;
	
}

