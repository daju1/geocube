// UstList.cpp: implementation of the UstList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "IGE2List.h"

#include "SetIGE.h"


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

CIGE2List::CIGE2List(CDatabase * database)
{
	m_ID_OBJ = -1;
	this->p_database = database;
}
CIGE2List::~CIGE2List()
{

}

BEGIN_MESSAGE_MAP(CIGE2List, CListCtrl)
	//{{AFX_MSG_MAP(CIGE2List)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CIGE2List::OnInitCtrl()
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


CString GetGruntName(CDatabase * database, long id_obj, long id_gr);

void CIGE2List::FillCtrlList()
{
	CString str = "";
	CRect           rect;
	this->GetWindowRect(&rect);			
	this->DeleteAllItemsAndColomns();

	for(int i = 0; i < 7; i++) 
	{
		LVCOLUMN col;

		col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		col.fmt = LVCFMT_LEFT;
		str = "";
		switch (i)
		{		
		case 0:
			{
				str = "№";
				col.cx = int (0.03 * double(rect.Width()));
			}
			break;		
		case 1:
			{
				str = "ИГЭ";
				col.cx = int (0.03 * double(rect.Width()));
			}
			break;		
		case 2:
			{
				str = "Грунт";
				col.cx = int (0.17 * double(rect.Width()));
			}
			break;
		case 3:
			{
				str = "Mk природной влажности";
				col.cx = int (0.03 * double(rect.Width()));
			}
			break;
		case 4:
			{
				str = "Mk водонасыщенного грунта";
				col.cx = int (0.03 * double(rect.Width()));
			}
			break;
		case 5:
			{
				str = "Стратиграфический индекс";
				col.cx = int (0.10 * double(rect.Width()));
			}
			break;
		case 6:
			{
				str = "Детальное описание грунта";
				col.cx = int (1.00 * double(rect.Width()));
			}
			break;
		default:
			{
				str = "---";
				col.cx = int (0.03 * double(rect.Width()));
			}
		}
		col.pszText = str.GetBuffer(str.GetLength());
		col.iSubItem = -1;

		this->InsertColumn(i, &col);
	}


	int iActualItem = 0;

	SetIGE setIGE(true, this->p_database);
	setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setIGE.m_strSort.Format("ID_IGE");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return;

	int npp = 1, iSubItem;

	if (!setIGE.IsBOF()) 
	{
		setIGE.MoveFirst( );
		while(!setIGE.IsEOF()) 
		{
			iSubItem = 0;
			
			str.Format("%d", npp++);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%s", setIGE.m_IGE);
			InSertTheItem(str, iActualItem, iSubItem++);

			//str.Format("%d", setIGE.m_ID_GR);
			str = GetGruntName(this->p_database, m_ID_OBJ, setIGE.m_ID_GR);
			InSertTheItem(str, iActualItem, iSubItem++);
		
			str.Format("%f", setIGE.m_mk);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%f", setIGE.m_mkz);
			DeleteEndZeros(str);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%s", setIGE.m_strat);
			InSertTheItem(str, iActualItem, iSubItem++);

			str.Format("%s", setIGE.m_desc0);
			InSertTheItem(str, iActualItem, iSubItem++);



			setIGE.MoveNext();
		}
	}
}

void CIGE2List::InSertTheItem(CString & str, int & iActualItem, int iSubItem)
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

void CIGE2List::OnSize(UINT nType, int cx, int cy) 
{
	CMyListCtrl::OnSize(nType, cx, cy);
	
	m_cxClient = cx;
	
}

