// DlgIGEList.cpp : implementation file
//

#include "stdafx.h"
#include "lab.h"
#include "labDoc.h"
#include "labView.h"
#include "DlgIGEList.h"

#include "SetObject.h"
#include "SetGrunty.h"
#include "SetIGE.h"

#include "SetLito.h"
#include "SetPCK2Fiz_CalcMode.h"
#include "SetPolygons.h"
#include "SetProbGr.h"
#include "SetStZond.h"
#include "SetSurfIgeMapping.h"
#include "SetSurfLitoMapping.h"
#include "SetT_V.h"

void DeleteEndZeros(char * str);
void DeleteEndZeros(CString & str);


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString GetGruntName(CDatabase * database, long id_obj, long id_gr);

/////////////////////////////////////////////////////////////////////////////
// DlgIGEList dialog


DlgIGEList::DlgIGEList(CLabView * view, CLabDoc * doc, CDatabase * database, CWnd* pParent /*=NULL*/)
	: CDialog(DlgIGEList::IDD, pParent) , m_list_ige(database)
{
	//{{AFX_DATA_INIT(DlgIGEList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->m_view = view;
	this->m_doc = doc;
	this->p_database = database;

//	this->m_list_ige.m_view = view;

	m_ID_OBJ = -1;
}


void DlgIGEList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgIGEList)
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_LIST_IGE, m_list_ige);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgIGEList, CDialog)
	//{{AFX_MSG_MAP(DlgIGEList)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit1)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IGE, OnClickListIge)
	ON_WM_DRAWITEM()
	ON_CBN_KILLFOCUS(IDC_COMBO1, OnKillfocusCombo1)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_IGE, OnKeydownListIge)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgIGEList message handlers

BOOL DlgIGEList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_COMBO1),SW_HIDE);
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);

	this->m_list_ige.OnInitCtrl();

//	ListView_SetExtendedListViewStyle(::GetDlgItem 
//        (m_hWnd,IDC_LIST_IGE),LVS_EX_FULLROWSELECT | 
//        LVS_EX_GRIDLINES); 


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

	
	this->m_list_ige.m_ID_OBJ = this->m_ID_OBJ;
	this->m_list_ige.FillCtrlList();

	SetGrunty setGrunty(this->p_database);
	setGrunty.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setGrunty.m_strSort.Format("ID_GR");
	if (setGrunty.Open(CRecordset::dynaset) )
	{

		CString str;
		int nIndex = 0;
		if (!setGrunty.IsBOF()) 
		{
			setGrunty.MoveFirst( );
			while(!setGrunty.IsEOF()) 
			{
				long ID_GR = setGrunty.m_ID_GR;
				str = GetGruntName(this->p_database, m_ID_OBJ, ID_GR);
				this->m_combo1.AddString(str);
				this->m_combo1.SetItemData(nIndex++, ID_GR);

				setGrunty.MoveNext();
			}
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE	
}

void DlgIGEList::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(nIDCtl)
	{
	case IDC_LIST_IGE:
		this->m_list_ige.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
	
	//CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void DlgIGEList::OnKillfocusCombo1() 
{
    CString str;
	int index = this->m_combo1.GetCurSel();
	long ID_GR = long(this->m_combo1.GetItemData(index));

	this->m_combo1.GetLBText(index, str);
	//str = GetGruntName(this->p_database, m_ID_OBJ, ID_GR);

    //SetCell(::GetDlgItem (m_hWnd, IDC_LIST_IGE),
    //    str,nItem,nSubItem);
    TCHAR     szString [256];

    wsprintf(szString, str, 0);

    //Fill the LVITEM structure with the 

    //values given as parameters.

    LVITEM lvItem;
    lvItem.mask = LVIF_TEXT;
    lvItem.iItem = nItem;
    lvItem.pszText = szString;
    lvItem.iSubItem = 2;

    //set the value of listItem

    ::SendMessage(::GetDlgItem (m_hWnd, IDC_LIST_IGE),
		LVM_SETITEM, 
        (WPARAM)0,(WPARAM)&lvItem);

    lvItem.iSubItem = 6;

    //set the value of listItem

    ::SendMessage(::GetDlgItem (m_hWnd, IDC_LIST_IGE),
		LVM_SETITEM, 
        (WPARAM)0,(WPARAM)&lvItem);


	
	for (int unEdited = 0; unEdited < 2; ++unEdited)
	{
		SetIGE setIGE(unEdited, this->p_database);
		setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
		setIGE.m_strSort.Format("ID_IGE");
		if ( setIGE.Open(CRecordset::dynaset) )
		{	
			try
			{
				setIGE.SetAbsolutePosition(nItem + 1);

				setIGE.Edit();
				setIGE.m_ID_GR = ID_GR;
				setIGE.m_desc0 = str;
				setIGE.Update();

			}
			catch (CDBException* pe)
			{
				AfxMessageBox(pe->m_strError);
				pe->Delete();
			}	
		}
	}

	// TODO: Add your control notification handler code here
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_COMBO1),
        SW_HIDE);	

}
void DlgIGEList::OnKillfocusEdit1() 
{
    CString str;

    GetDlgItemText(IDC_EDIT1,str);

    //set the value in the listContorl with the

    //specified Item & SubItem values

    SetCell(::GetDlgItem (m_hWnd, IDC_LIST_IGE),
        str,nItem,nSubItem);

    ::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),
        SW_HIDE);	
}

void DlgIGEList::OnClickListIge(NMHDR* pNMHDR, LRESULT* pResult) 
{
    Invalidate();
    HWND hWnd1 =  ::GetDlgItem (m_hWnd, IDC_LIST_IGE);
    LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;
    RECT rect;
    //get the row number

    nItem = temp->iItem;
    //get the column number

    nSubItem = temp->iSubItem;
    if (nSubItem == 0 || nSubItem == -1 )
	{
        return;
	}    
	
	if (nItem == -1)
	{
		// 
		for (int unEdited = 0; unEdited < 2; ++unEdited)
		{
			SetIGE setIGE(unEdited, this->p_database);
			setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
			setIGE.m_strSort.Format("ID_IGE");
			if ( setIGE.Open(CRecordset::dynaset) )
			{
				long ID_IGE = 0;
				nItem = 0;
				if (!setIGE.IsBOF()) 
				{
					setIGE.MoveFirst( );
					while(!setIGE.IsEOF()) 
					{
						ID_IGE = setIGE.m_ID_IGE;
						++nItem;
						setIGE.MoveNext();
					}
				}
				++ID_IGE;	

				setIGE.AddNewRow(m_ID_OBJ, ID_IGE);
			}
		}

		this->m_list_ige.FillCtrlList();
	}
    //Retrieve the text of the selected subItem 

	long ID_GR = -1;

    //from the list
	// set edit box text to what that field's value is
	SetIGE setIGE(true, this->p_database);
	setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setIGE.m_strSort.Format("ID_IGE");
	CString str = "";
	if ( setIGE.Open(CRecordset::dynaset) )
	{	
		try
		{
			setIGE.SetAbsolutePosition(nItem + 1);
			switch (temp->iSubItem)
			{		
			case 0:
				{
					// str = "№";
					str.Format("%d", setIGE.m_ID_IGE);
				}
				break;		
			case 1:
				{
					//str = "ИГЭ";
					str.Format("%s", setIGE.m_IGE);
				}
				break;		
			case 2:
				{
					//str = "Грунт";
					//str.Format("%d", setIGE.m_ID_GR);
					ID_GR = setIGE.m_ID_GR;
					str = GetGruntName(this->p_database, m_ID_OBJ, setIGE.m_ID_GR);

				}
				break;
			case 3:
				{
					//str = "Mk природной влажности";
					str.Format("%f", setIGE.m_mk);
					DeleteEndZeros(str);
				}
				break;
			case 4:
				{
					//str = "Mk водонасыщенного грунта";
					str.Format("%f", setIGE.m_mkz);
					DeleteEndZeros(str);
				}
				break;
			case 5:
				{
					//str = "Стратиграфический индекс";
					str.Format("%s", setIGE.m_strat);
				}
				break;
			case 6:
				{
					//str = "Детальное описание грунта";
					str.Format("%s", setIGE.m_desc0);
				}
				break;
			default:
				str = "---";
			}
		}
		catch (CDBException* pe)
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return;
		}

	}
	this->m_list_ige.SetItemState(-1, 0, LVIS_SELECTED);
    RECT rect1,rect2;
    // this macro is used to retrieve the Rectanle 

    // of the selected SubItem

    RECT rect0, rect_h;
	ListView_GetViewRect(hWnd1, &rect0);
    ::GetWindowRect(ListView_GetHeader(hWnd1),&rect_h);

    ListView_GetSubItemRect(hWnd1,nItem,
        temp->iSubItem,LVIR_BOUNDS,&rect);
    //Get the Rectange of the listControl

    ::GetWindowRect(temp->hdr.hwndFrom,&rect1);
    //Get the Rectange of the Dialog

    ::GetWindowRect(m_hWnd,&rect2);

    int x=rect1.left-rect2.left;
    int y=rect1.top-rect2.top;
    


    if (nSubItem == 2)
	{
		int index = 0;	
		int cnt = m_combo1.GetCount();
		do
		{
			if (ID_GR == m_combo1.GetItemData(index))
			{
				m_combo1.SetCurSel(index);
				break;
			}
			++index;
		}
		while (index < cnt);


		RECT rect_combo;
		m_combo1.GetWindowRect(&rect_combo);

		::SetWindowPos(::GetDlgItem(m_hWnd,IDC_COMBO1),
			HWND_TOP,
			rect.left+x+4,//+x,
			rect.top + y - 29,//+4, 
			rect.right-rect.left - 5,
			rect_combo.bottom - rect_combo.top, SWP_SHOWWINDOW);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_COMBO1),SW_SHOW);
		::SetFocus(::GetDlgItem(m_hWnd,IDC_COMBO1));
		::SetActiveWindow(::GetDlgItem(m_hWnd,IDC_COMBO1));

		m_combo1.Invalidate();
		m_combo1.UpdateWindow();
	}  
	else
	{
		::SetWindowPos(::GetDlgItem(m_hWnd,IDC_EDIT1),
			HWND_TOP,
			rect.left+x+2,//+x,
			rect.top + y -27,//+4, 
			rect.right-rect.left - 5,
			rect.bottom-rect.top - 1, SWP_SHOWWINDOW);
		::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_SHOW);
		::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT1));
		//Draw a Rectangle around the SubItem

	//   ::Rectangle(::GetDC(temp->hdr.hwndFrom),
	//     rect.left+4,rect.top,rect.right-5,rect.bottom-1);
		//Set the listItem text in the EditBox

		::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),str);
		::SetActiveWindow(::GetDlgItem(m_hWnd,IDC_EDIT1));

		m_edit1.Invalidate();
		m_edit1.UpdateWindow();
	}
	
	*pResult = 0;
}
void DlgIGEList::SetCell(HWND hWnd1, 
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




		for (int unEdited = 0; unEdited < 2; ++unEdited)
		{
			SetIGE setIGE(unEdited, this->p_database);
			setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
			setIGE.m_strSort.Format("ID_IGE");
			if ( setIGE.Open(CRecordset::dynaset) )
			{	
				try
				{
					setIGE.SetAbsolutePosition(nRow + 1);
					switch(nCol) 
					{			
					case 0://первая колонка
						break;
					case 1://вторая колонка
						{
							setIGE.Edit();
							setIGE.m_IGE = value;
							setIGE.Update();
						}
						break;
					case 2://третья колонка
						{
							setIGE.Edit();
							///setIGE.m_ID_GR = atol(value);
							setIGE.Update();
						}
						break;
					case 3://4-я колонка
						{
							setIGE.Edit();
							setIGE.m_mk = atof(value);
							setIGE.Update();
						}
						break;
					case 4://5-я колонка
						{
							setIGE.Edit();
							setIGE.m_mkz = atof(value);
							setIGE.Update();
						}
						break;
					case 5://6-я колонка
						{
							setIGE.Edit();
							setIGE.m_strat = value;
							setIGE.Update();
						}
						break;
					case 6://7-я колонка
						{
							setIGE.Edit();
							setIGE.m_desc0 = value;
							setIGE.Update();
						}
						break;
					}	
				}
				catch (CDBException* pe)
				{
					AfxMessageBox(pe->m_strError);
					pe->Delete();
				}	
			}
		}
	}
}

static long GetSetSize(CRecordset * Set, long ID_OBJ, long ID_IGE, bool small_ige = false)
{
	long size = 0;

	if (small_ige)
		Set->m_strFilter.Format("ID_OBJ = %ld and id_ige = %ld", ID_OBJ, ID_IGE);
	else
		Set->m_strFilter.Format("ID_OBJ = %ld and ID_IGE = %ld", ID_OBJ, ID_IGE);

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
	}
	return size;
}


/*
//SetLito
//SetLito0
//SetPCK2Fiz_CalcMode
//SetPolygons
//SetProbGr
//SetStZond
//SetSurfIgeMapping
//SetSurfLitoMapping
//SetT_V
*/
bool used_ID_IGE(CDatabase * p_database, long ID_OBJ, long ID_IGE)
{
	return (
		GetSetSize(&SetProbGr(p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetPCK2Fiz_CalcMode(p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetStZond(p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetSurfIgeMapping(p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetSurfLitoMapping(p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetLito(true, p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetLito(false, p_database), ID_OBJ, ID_IGE)
		+
		GetSetSize(&SetPolygons(p_database), ID_OBJ, ID_IGE, true)
		+
		GetSetSize(&SetT_V(p_database), ID_OBJ, ID_IGE, true)
		) > 0;
}


void DlgIGEList::OnKeydownListIge(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			if (m_ID_OBJ == -1)
				return;

			int nIGEItem = this->m_list_ige.GetSelected();
			if (nIGEItem < 0)
			{
				return ;
			}	

			int ans_to_del = IDNO;

				
			for (int unEdited = 0; unEdited < 2; ++unEdited)
			{
				SetIGE setIGE(unEdited, this->p_database);
				setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
				setIGE.m_strSort.Format("ID_IGE");
				if (setIGE.Open(CRecordset::dynaset) )
				{				
					try
					{
						setIGE.SetAbsolutePosition(nIGEItem + 1);
						if (!used_ID_IGE(this->p_database, m_ID_OBJ, setIGE.m_ID_IGE))
						{
							if (!unEdited) ans_to_del = AfxMessageBox("Удалить IGE?", MB_YESNO);
							if (IDYES == ans_to_del)
								setIGE.Delete();
						}
						else
						{
							if (!unEdited) AfxMessageBox("Этот IGE удалить невозможно");
						}
					}
					catch (CDBException* pe) 
					{
						AfxMessageBox(pe->m_strError);
						pe->Delete();
					}
				}
					
				//Для видалення певного грунту з таблиці необхідно виділити необхідний рядок, 
				//клацнувши мишкою по номеру, і натиснути клавішу Del  на клавіатурі. 
				//Якщо виділений грунт зустрічаєьться в даних даного об’єкту (набір ІГЕ, 
				//літологія, проби грунту тощо) видалення рядка не відбудеться.

				long ID_IGE = 0;
				if (!setIGE.IsBOF()) 
				{
					setIGE.MoveFirst( );
					while(!setIGE.IsEOF()) 
					{
						ID_IGE++;
						if (setIGE.m_ID_IGE != ID_IGE)
						{
							if (!used_ID_IGE(this->p_database, m_ID_OBJ, setIGE.m_ID_IGE))
							{
								setIGE.Edit();
								setIGE.m_ID_IGE = ID_IGE;
								setIGE.Update();
							}
							else
								ID_IGE = setIGE.m_ID_IGE;
						}

						setIGE.MoveNext();
					}
				}

				this->m_list_ige.FillCtrlList();
			}


		}
		break;
	}	
	*pResult = 0;
}

void DlgIGEList::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here

	if (this->m_list_ige.m_hWnd)
		this->m_list_ige.MoveWindow(5,5, cx-10,cy-10);
	
}
