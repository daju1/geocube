// DlgNaborGruntovSetting.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "labDoc.h"
#include "labView.h"
#include "DlgNaborGruntovSetting.h"

#include "SetObject.h"
#include "SetGrunty.h"
#include "SetGrMain.h"
#include "SetGenezis.h"
#include "SetGranSklad.h"

#include "SetProbGr.h"
#include "SetIGE.h"

extern HINSTANCE hInst;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNaborGruntovSetting dialog


CDlgNaborGruntovSetting::CDlgNaborGruntovSetting(CLabView * view, CLabDoc * doc, CDatabase * database, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNaborGruntovSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNaborGruntovSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->m_view = view;
	this->m_doc = doc;
	this->p_database = database;

	this->m_list_grunt.m_view = view;
	this->m_list_nabor_gruntov.m_view = view;
	this->m_list_grunt_gran.m_view = view;
	this->m_list_genezis.m_view = view;

	m_ID_OBJ = -1;

}


void CDlgNaborGruntovSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNaborGruntovSetting)
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_LIST_GRUNT, m_list_grunt);
	DDX_Control(pDX, IDC_LIST_NABOR_GRUNTOV, m_list_nabor_gruntov);
	DDX_Control(pDX, IDC_LIST_GRUNT_GRAN, m_list_grunt_gran);
	DDX_Control(pDX, IDC_LIST_GENEZIS, m_list_genezis);
	DDX_Control(pDX, IDC_COMBO_GRUNT_VID, m_combo_grunt_vid);
	DDX_Control(pDX, IDC_COMBO_GRUNT_TYP, m_combo_grunt_typ);
	DDX_Control(pDX, IDC_COMBO_GRUNT_RAZNOVIDNOST, m_combo_grunt_raznovidnost);
	DDX_Control(pDX, IDC_COMBO_GRUNT_PODGRUPPA, m_combo_grunt_podgruppa);
	DDX_Control(pDX, IDC_COMBO_GRUNT_GRUPPA, m_combo_grunt_gruppa);
	DDX_Control(pDX, IDC_COMBO_GRUNT_CLASS, m_combo_grunt_class);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNaborGruntovSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgNaborGruntovSetting)
	ON_CBN_EDITCHANGE(IDC_COMBO_GRUNT_CLASS, OnEditchangeComboGruntClass)
	ON_CBN_EDITCHANGE(IDC_COMBO_GRUNT_GRUPPA, OnEditchangeComboGruntGruppa)
	ON_CBN_EDITCHANGE(IDC_COMBO_GRUNT_PODGRUPPA, OnEditchangeComboGruntPodgruppa)
	ON_CBN_EDITCHANGE(IDC_COMBO_GRUNT_TYP, OnEditchangeComboGruntTyp)
	ON_CBN_EDITCHANGE(IDC_COMBO_GRUNT_VID, OnEditchangeComboGruntVid)
	ON_CBN_EDITCHANGE(IDC_COMBO_GRUNT_RAZNOVIDNOST, OnEditchangeComboGruntRaznovidnost)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON_SELECTED_GRUNT_TO_LIST, OnButtonSelectedGruntToList)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL_GRUNT_SELECTING, OnButtonCancelGruntSelecting)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST_NABOR_GRUNTOV, OnEndlabeleditListNaborGruntov)
	ON_NOTIFY(LVN_BEGINLABELEDIT, IDC_LIST_NABOR_GRUNTOV, OnBeginlabeleditListNaborGruntov)
	ON_WM_KEYDOWN()
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_NABOR_GRUNTOV, OnKeydownListNaborGruntov)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NABOR_GRUNTOV, OnClickListNaborGruntov)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NABOR_GRUNTOV, OnDblclkListNaborGruntov)
	ON_BN_CLICKED(IDOK, OK)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_WM_CHAR()
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNaborGruntovSetting message handlers
void CDlgNaborGruntovSetting::OK() 
{
	// TODO: Add your control notification handler code here

	CDialog::EndDialog (0);
	
}

void CDlgNaborGruntovSetting::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}


BOOL CDlgNaborGruntovSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	this->m_list_grunt.OnInitCtrl();
	this->m_list_genezis.OnInitCtrl();
	this->m_list_grunt_gran.OnInitCtrl();

	this->m_list_nabor_gruntov.OnInitCtrl();
//	ListView_SetExtendedListViewStyle(::GetDlgItem 
//        (m_hWnd,IDC_LIST_NABOR_GRUNTOV),LVS_EX_FULLROWSELECT | 
//        LVS_EX_GRIDLINES); 

	/*
#define table_key_Genezis		13
#define table_key_GranSklad		14
#define table_key_GrMain		15
#define table_key_Grunty		16
#define table_key_PodTypyGr		17
*/
	int nObItem = this->m_view->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return FALSE;
	}

	m_ID_OBJ = -1;

	try
	{
		SetObject setObject(this->p_database);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;

		setObject.SetAbsolutePosition(nObItem + 1);        
		m_ID_OBJ = setObject.m_ID_OBJ;
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}

	this->m_list_grunt.Fill_Ctrl_List(this->m_doc->m_tables[table_key_GrMain], "", "ID_GRMAIN");
	this->m_list_genezis.Fill_Ctrl_List(this->m_doc->m_tables[table_key_Genezis], "", "ID_GENEZIS");
	this->m_list_grunt_gran.Fill_Ctrl_List(this->m_doc->m_tables[table_key_GranSklad], "", "ID_ROZMIR");
	
	CString where;
	where.Format("ID_OBJ = %d", m_ID_OBJ);
	this->m_list_nabor_gruntov.Fill_Ctrl_List(this->m_doc->m_tables[table_key_Grunty], where, "ID_GR");
	//this->m_list_nabor_gruntov.FillCtrlList(this->p_database);

	


	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNaborGruntovSetting::OnEditchangeComboGruntClass() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNaborGruntovSetting::OnEditchangeComboGruntGruppa() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNaborGruntovSetting::OnEditchangeComboGruntPodgruppa() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNaborGruntovSetting::OnEditchangeComboGruntTyp() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNaborGruntovSetting::OnEditchangeComboGruntVid() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNaborGruntovSetting::OnEditchangeComboGruntRaznovidnost() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgNaborGruntovSetting::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(nIDCtl)
	{
	case IDC_LIST_GRUNT:
		this->m_list_grunt.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_GENEZIS:
		this->m_list_genezis.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_GRUNT_GRAN:
		this->m_list_grunt_gran.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_NABOR_GRUNTOV:
		this->m_list_nabor_gruntov.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
long GetSetSize(CRecordset * Set)
{
	long size = 0;

	if (!Set->IsBOF()) 
	{
		Set->MoveFirst();
		while(!Set->IsEOF()) 
		{
			size++;
			Set->MoveNext();
		}
	}
	//DWORD sz = Set->GetRowsetSize();//???

	return size;
}
static long GetSetSize(CRecordset * Set, long ID_OBJ, long ID_GR)
{
	long size = 0;
	//SET Set(p_database);
	Set->m_strFilter.Format("ID_OBJ = %ld and ID_GR = %ld", ID_OBJ, ID_GR);
	if ( Set->Open(CRecordset::dynaset) )
	{
		if (!Set->IsBOF()) 
		{
			Set->MoveFirst();
			while(!Set->IsEOF()) 
			{
				size++;
				Set->MoveNext();
			}
		}
		//DWORD sz = Set->GetRowsetSize();//???
	}
	return size;
}

bool used_ID_GR(CDatabase * p_database, long ID_OBJ, long ID_GR)
{
	return (GetSetSize(&SetProbGr(p_database), ID_OBJ, ID_GR)
		+
		GetSetSize(&SetIGE(true, p_database), ID_OBJ, ID_GR)
		+
		GetSetSize(&SetIGE(false, p_database), ID_OBJ, ID_GR)
		) > 0;
}
void CDlgNaborGruntovSetting::OnButtonSelectedGruntToList() 
{
	if (m_ID_OBJ == -1)
		return;

	int nGruntItem = this->m_list_grunt.GetSelected();
	if (nGruntItem < 0)
	{
		AfxMessageBox("Не выбран грунт");
		return ;
	}	
	
	int nGenezisItem = this->m_list_genezis.GetSelected();
	int nGranItem = this->m_list_grunt_gran.GetSelected();



	long ID_GRMAIN = -1;
	long TYPGR = -1;
	long TYPGR_PCK = -1;
	long ID_NJU = -1;
	long ID_GRCONS = -1;
	long ID_UMPOZ = -1;
	long ID_NORMATYV = -1;

	CString GrMainNazvaR = "";
	CString GrMainNazvaU = "";

	try
	{
		SetGrMain setGrMain(this->p_database);
		if ( !setGrMain.Open(CRecordset::dynaset) )
			return;

		setGrMain.SetAbsolutePosition(nGruntItem + 1); 

		ID_GRMAIN = setGrMain.m_ID_GRMAIN;
		TYPGR = setGrMain.m_TYPGR;
		TYPGR_PCK = setGrMain.m_TYPGR_PCK;
		ID_GRCONS = setGrMain.m_ID_GRCONS;
		ID_NJU = setGrMain.m_ID_NJU;
		ID_NORMATYV = setGrMain.m_ID_NORMATYV;
		ID_UMPOZ = setGrMain.m_ID_UMPOZ;
		GrMainNazvaR = setGrMain.m_NAZVA_R;
		GrMainNazvaU = setGrMain.m_NAZVA_U;

	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}

	CString GenezisNazvaR = "";
	CString GenezisNazvaU = "";

	long ID_GENEZIS = 0;
	if (nGenezisItem >= 0)
	{
		try
		{
			SetGenezis setGenezis(this->p_database);
			if ( !setGenezis.Open(CRecordset::dynaset) )
				return;

			setGenezis.SetAbsolutePosition(nGenezisItem + 1);        
			ID_GENEZIS = setGenezis.m_ID_GENEZIS;
			GenezisNazvaR = setGenezis.m_NAZVA_R;
			GenezisNazvaU = setGenezis.m_NAZVA_U;
			//setGenezis.m_ID_NORMATYV;
			//setGenezis.m_ID_GRMAIN;
			setGenezis.m_INDEX;
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
		}
	}

	CString GranSkladNazvaR = "";
	CString GranSkladNazvaU = "";

	long ID_UKLAD = 0;

	if (nGranItem >= 0 && ID_GRMAIN == 1/*sand*/)
	{
		try
		{
			SetGranSklad setGranSklad(this->p_database);
			if ( !setGranSklad.Open(CRecordset::dynaset) )
				return;

			setGranSklad.SetAbsolutePosition(nGranItem + 1); 
			setGranSklad.m_ID_ROZMIR;
			ID_UKLAD = setGranSklad.m_ID_UKLAD;
			if (ID_GRMAIN == 1 || ID_UMPOZ == 5) // if sand
				ID_UMPOZ = setGranSklad.m_ID_UMPOZ; // sand gran sklad
			GranSkladNazvaR = setGranSklad.m_NAZVA_R;
			GranSkladNazvaU = setGranSklad.m_NAZVA_U;
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
		}
	}
	
	SetGrunty setGrunty(this->p_database);
	setGrunty.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setGrunty.m_strSort.Format("ID_GR");
	if ( !setGrunty.Open(CRecordset::dynaset) )
		return;

	long ID_GR = 0;
	if (!setGrunty.IsBOF()) 
	{
		setGrunty.MoveFirst( );
		while(!setGrunty.IsEOF()) 
		{
			//setGrunty.Edit();
			ID_GR = setGrunty.m_ID_GR;
			//setGrunty.Update();

			setGrunty.MoveNext();
		}
	}
	ID_GR++;

	CString NAZVA_R = GrMainNazvaR + 
		(GranSkladNazvaR.GetLength() ? " " : "") + GranSkladNazvaR +
		(GenezisNazvaR.GetLength() ? " " : "") + GenezisNazvaR;

	CString NAZVA_U = GrMainNazvaU + 
		(GranSkladNazvaU.GetLength() ? " " : "") + GranSkladNazvaU +
		(GenezisNazvaU.GetLength() ? " " : "") + GenezisNazvaU;

	setGrunty.AddNewRow(m_ID_OBJ, 
		ID_GR, 
		NAZVA_U, 
		NAZVA_R, 
		TYPGR, 
		TYPGR_PCK, 
		ID_NORMATYV, 
		ID_GRCONS, 
		ID_UKLAD, 
		ID_NJU, 
		ID_GRMAIN, 
		ID_UMPOZ, 
		ID_GENEZIS);


	//this->m_list_nabor_gruntov.DeleteAllItemsAndColomns();
	CString where;
	where.Format("ID_OBJ = %d", m_ID_OBJ);
#if 0
	//Если произошло изменение в уже существующих данных, 
	// и заранее известно, какие именно элементы требуют 
	// перерисовки - можно использовать функцию  
	// BOOL CListCtrl::RedrawItems(int nFirst, int nLast). 
	// Но если произошло добавление/удаление данных - следует 
	// использовать void CListCtrl::SetItemCount(int nItems).
	this->m_list_nabor_gruntov.SetItemCount(GetSetSize(&setGrunty));
#else

	this->m_list_nabor_gruntov.Fill_Ctrl_List(this->m_doc->m_tables[table_key_Grunty], where, "ID_GR");
#endif

	this->m_list_genezis.SetSelectionMark(-1);
	this->m_list_grunt.SetSelectionMark(-1);
	this->m_list_grunt_gran.SetSelectionMark(-1);
#if 0

//	this->m_list_grunt.RedrawItems(nGruntItem, nGruntItem);
//	this->m_list_genezis.RedrawItems(nGenezisItem, nGenezisItem);
//	this->m_list_grunt_gran.RedrawItems(nGranItem, nGranItem);

	this->m_list_grunt.RedrawWindow();
	this->m_list_genezis.RedrawWindow();
	this->m_list_grunt_gran.RedrawWindow();

#else
	this->m_list_grunt.Fill_Ctrl_List(this->m_doc->m_tables[table_key_GrMain], "", "ID_GRMAIN");
	this->m_list_genezis.Fill_Ctrl_List(this->m_doc->m_tables[table_key_Genezis], "", "ID_GENEZIS");
	this->m_list_grunt_gran.Fill_Ctrl_List(this->m_doc->m_tables[table_key_GranSklad], "", "ID_ROZMIR");
#endif
}

void CDlgNaborGruntovSetting::OnButtonCancelGruntSelecting() 
{
	if (m_ID_OBJ == -1)
		return;

	int nNaborGruntovItem = this->m_list_nabor_gruntov.GetSelected();
	if (nNaborGruntovItem < 0)
	{
		return ;
	}	

	
	SetGrunty setGrunty(this->p_database);
	setGrunty.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setGrunty.m_strSort.Format("ID_GR");
	if ( !setGrunty.Open(CRecordset::dynaset) )
		return;
		
	try
	{
		setGrunty.SetAbsolutePosition(nNaborGruntovItem + 1);
		if (!used_ID_GR(this->p_database, m_ID_OBJ, setGrunty.m_ID_GR))
		{
			if (IDYES == AfxMessageBox("Удалить грунт?", MB_YESNO))
				setGrunty.Delete();
		}
		else
			AfxMessageBox("Этот грунт удалить невозможно");
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
		
	//Для видалення певного грунту з таблиці необхідно виділити необхідний рядок, 
	//клацнувши мишкою по номеру, і натиснути клавішу Del  на клавіатурі. 
	//Якщо виділений грунт зустрічаєьться в даних даного об’єкту (набір ІГЕ, 
	//літологія, проби грунту тощо) видалення рядка не відбудеться.

	long ID_GR = 0;
	if (!setGrunty.IsBOF()) 
	{
		setGrunty.MoveFirst( );
		while(!setGrunty.IsEOF()) 
		{
			ID_GR++;
			if (setGrunty.m_ID_GR != ID_GR)
			{
				if (!used_ID_GR(this->p_database, m_ID_OBJ, setGrunty.m_ID_GR))
				{
					setGrunty.Edit();
					setGrunty.m_ID_GR = ID_GR;
					setGrunty.Update();
				}
				else
					ID_GR = setGrunty.m_ID_GR;
			}

			setGrunty.MoveNext();
		}
	}
	//this->m_list_nabor_gruntov.DeleteAllItemsAndColomns();
	CString where;
	where.Format("ID_OBJ = %d", m_ID_OBJ);
	this->m_list_nabor_gruntov.Fill_Ctrl_List(this->m_doc->m_tables[table_key_Grunty], where, "ID_GR");
}

void CDlgNaborGruntovSetting::OnEndlabeleditListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	pDispInfo->hdr.code;
	
	*pResult = 0;
}

void CDlgNaborGruntovSetting::OnBeginlabeleditListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}



void CDlgNaborGruntovSetting::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString s;
	s.Format("OnKeyDown");
	AfxMessageBox(s);

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDlgNaborGruntovSetting::OnKeydownListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString s;
	s.Format("nChar = %u %c, nFlags = %d",
		pLVKeyDow->wVKey, pLVKeyDow->wVKey, pLVKeyDow->flags);
	AfxMessageBox(s);
	
	*pResult = 0;
}



void CDlgNaborGruntovSetting::SetCell(HWND hWnd1, 
        CString value, int nRow, int nCol)
{
    TCHAR     szString [256];
    wsprintf(szString,value ,0);

    //Fill the LVITEM structure with the 

    //values given as parameters.

    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nRow;
    lvItem.pszText = szString;
    lvItem.iSubItem = nCol;
    if(nCol >0)
	{
        //set the value of listItem

        ::SendMessage(hWnd1,LVM_SETITEM, 
            (WPARAM)0,(WPARAM)&lvItem);



		SetGrunty setGrunty(this->p_database);
		setGrunty.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
		setGrunty.m_strSort.Format("ID_GR");
		if ( setGrunty.Open(CRecordset::dynaset) )
		{	
			try
			{
				setGrunty.SetAbsolutePosition(nRow + 1);
				switch(nCol) 
				{			
				case 0://первая колонка
					break;
				case 1://вторая колонка
					{
						setGrunty.Edit();
						setGrunty.m_NAZVA_U = value;
						setGrunty.Update();
					}
					break;
				case 2://третья колонка
					{
						setGrunty.Edit();
						setGrunty.m_NAZVA_R = value;
						setGrunty.Update();
					}
					break;
				}	
			}
			catch (CDBException* pe)
			{
				AfxMessageBox(pe->m_strError);
				pe->Delete();
				//return;
			}	
		}
	}
//    else
//        //Insert the value into List
//
//        ListView_InsertItem(hWnd1,&lvItem);

}
//this function will returns the item 

//text depending on the item and SubItem Index

CString CDlgNaborGruntovSetting::GetItemText(
    HWND hWnd, int nItem, int nSubItem) const
{
    LVITEM lvi;
    memset(&lvi, 0, sizeof(LVITEM));
    lvi.iSubItem = nSubItem;
    CString str;
    int nLen = 128;
    int nRes;
   // do
   // {
        nLen *= 2;
        lvi.cchTextMax = nLen;
        lvi.pszText = str.GetBufferSetLength(nLen);
        nRes  = (int)::SendMessage(hWnd, 
            LVM_GETITEMTEXT, (WPARAM)nItem,
            (LPARAM)&lvi);
    str.ReleaseBuffer();
    return str;
}
void CDlgNaborGruntovSetting::OnClickListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult) 
{
    Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd, IDC_LIST_NABOR_GRUNTOV);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number

    nItem = temp->iItem;
    //get the column number

    nSubItem = temp->iSubItem;
    if(nSubItem == 0 || nSubItem == -1 || nItem == -1)
        return ;
    //Retrieve the text of the selected subItem 

    //from the list
	// set edit box text to what that field's value is
	SetGrunty setGrunty(this->p_database);
	setGrunty.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setGrunty.m_strSort.Format("ID_GR");
	CString str;
	if ( setGrunty.Open(CRecordset::dynaset) )
	{	
		try
		{
			setGrunty.SetAbsolutePosition(temp->iItem + 1);
			if(temp->iSubItem == 0) //первая колонка
			{			
				str.Format("%d", setGrunty.m_ID_GR);
			}
			else	
				if(temp->iSubItem == 1) //вторая колонка
				{
					str = setGrunty.m_NAZVA_U;
				}
				else
					if(temp->iSubItem == 2) // третья колонка
					{
						str = setGrunty.m_NAZVA_R;
					}	
		}
		catch (CDBException* pe)
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return;
		}

	}
	this->m_list_nabor_gruntov.SetItemState(-1, 0, LVIS_SELECTED);
    RECT rect1,rect2;
    // this macro is used to retrieve the Rectanle 

    // of the selected SubItem

    RECT rect0, rect_h;
	ListView_GetViewRect(hWnd1, &rect0);
    ::GetWindowRect(ListView_GetHeader(hWnd1),&rect_h);

    ListView_GetSubItemRect(hWnd1,temp->iItem,
        temp->iSubItem,LVIR_BOUNDS,&rect);
    //Get the Rectange of the listControl

    ::GetWindowRect(temp->hdr.hwndFrom,&rect1);
    //Get the Rectange of the Dialog

    ::GetWindowRect(m_hWnd,&rect2);

    int x=rect1.left-rect2.left;
    int y=rect1.top-rect2.top;
    
    if(nItem != -1) 
    ::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT1),
        HWND_TOP,
		rect.left+x+4,//+x,
		rect.top + y -27,//+4, 
        rect.right-rect.left - 5,
        rect.bottom-rect.top - 1, SWP_SHOWWINDOW);
    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_SHOW);
    ::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT1));
    //Draw a Rectangle around the SubItem

	::SetActiveWindow(::GetDlgItem(m_hWnd,IDC_EDIT1));

	m_edit1.Invalidate();
	m_edit1.UpdateWindow();

 //   ::Rectangle(::GetDC(temp->hdr.hwndFrom),
   //     rect.left+4,rect.top,rect.right-5,rect.bottom-1);
    //Set the listItem text in the EditBox

    ::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),str);
    *pResult = 0;
}
void CDlgNaborGruntovSetting::OnDblclkListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}




/*void CDlgNaborGruntovSetting::OnGetdispinfoListNaborGruntov(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
  NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
  LV_ITEM* pItem = &(pDispInfo)->item; // сразу получим указатель на LV_ITEM
  int iItemIndex = pItem->iItem; // и индекс, для наглядности

  //CListDataItem DataItem = m_arrMyData[iItemIndex];

	// от нас хотят текст? 
	if(pItem->mask & LVIF_TEXT)
	{
		SetGrunty setGrunty(this->p_database);
		setGrunty.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
		setGrunty.m_strSort.Format("ID_GR");
		if ( setGrunty.Open(CRecordset::dynaset) )
		{	
			try
			{
				setGrunty.SetAbsolutePosition(iItemIndex + 1);
				if(pItem->iSubItem == 0) //первая колонка
				{			
					CString s;s.Format("%d", setGrunty.m_ID_GR);
					lstrcpyn(pItem->pszText, s, pItem->cchTextMax);
				}
				else	
					if(pItem->iSubItem == 1) //вторая колонка
					{
						lstrcpyn(pItem->pszText, setGrunty.m_NAZVA_U, pItem->cchTextMax);
					}
					else
						if(pItem->iSubItem == 2) // третья колонка
						{
							lstrcpyn(pItem->pszText, setGrunty.m_NAZVA_R, pItem->cchTextMax);
						}	
			}
			catch (CDBException* pe)
			{
				AfxMessageBox(pe->m_strError);
				pe->Delete();
				//return;
			}
	
		}
	}
#if 0
	// от нас хотят изображение?
	if(pItem->mask & LVIF_IMAGE)
	{
		// Если у нас ListCtrl c иконками - то в pItem->iImage присваиваем номер иконки из 
		// CImageList для этого элемента массива данных
		pItem->iImage = DataItem.m_nIcon;

		// Чек-бокс у нас - тоже изображение, и  
		// чтобы использовать изображение чек-бокса, необходимо задействовать "state mask"
		pItem->mask |= LVIF_STATE;
		pItem->stateMask = LVIS_STATEIMAGEMASK;
		
		if(DataItem.m_bOn)
		{
			// если включен - отображать чек-бокс с галочкой
			pItem->state = INDEXTOSTATEIMAGEMASK(2);
		}
		else 
		{
			// иначе отображать пустой чек-бокс
			pItem->state = INDEXTOSTATEIMAGEMASK(1);
		}
	}
#endif
	
	*pResult = 0;
}
*/


// This function set the text in the specified 

// SubItem depending on the Row and Column values


void CDlgNaborGruntovSetting::OnKillfocusEdit1() 
{
    CString str;

    GetDlgItemText(IDC_EDIT1,str);

    //set the value in the listContorl with the

    //specified Item & SubItem values

    SetCell(::GetDlgItem (m_hWnd, IDC_LIST_NABOR_GRUNTOV),
        str,nItem,nSubItem);

    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),
        SW_HIDE);
	
}

void CDlgNaborGruntovSetting::OnOK() 
{
    CWnd* pwndCtrl = GetFocus();
    // get the control ID which is 

    // presently having the focus

    int ctrl_ID = pwndCtrl->GetDlgCtrlID();
    CString str;
    switch (ctrl_ID)
    {   //if the control is the EditBox 

        case IDC_EDIT1:
        //get the text from the EditBox

        //GetDlgItemText(IDC_EDIT1,str);

        //set the value in the listContorl with the

        //specified Item & SubItem values

//        SetCell(::GetDlgItem (m_hWnd, IDC_LIST_NABOR_GRUNTOV),
//            str,nItem,nSubItem);

        ::SendDlgItemMessage(m_hWnd,IDC_EDIT1,
            WM_KILLFOCUS,0,0);
        ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),
            SW_HIDE);
            break;     
        default:
            break;
    }	
	//CDialog::OnOK();
}

void CDlgNaborGruntovSetting::OnChangeEdit1() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
